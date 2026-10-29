// P354 trailer tooling overview (tools/port/trailer). Outputs go to port_work/trailer/ (gitignored: pictures, sounds and
// the font are ROM-derived, never commit them). No ffmpeg: WebCodecs in headless Chrome. Local npm tooling (not committed):
//   cd port_work/trailer/npm && npm init -y && npm install mp4-muxer@5.2.2 mp4box@0.5.3
// 1. node tools/port/trailer/fontdump.mjs                     game font 0 -> font/font.json
// 2. tools/port/trailer/net4.sh port_work/trailer/net4 210    real 4-player online session: panel shots + pads.env
// 3. node tools/port/trailer/capture.mjs music run29 run29_30 run29_n64 ledge13 spin_off spin_on pause_hi pause_lo freecam photo mp4
// 4. node tools/port/trailer/pagecap.mjs site ; node tools/port/trailer/pagecap.mjs options
// 5. node tools/port/trailer/render.mjs [preview F,F,...]      edit + encode (compose.js) -> out/trailer.mp4
// 6. node tools/port/trailer/verify.mjs [mp4] [times]          demux + decode check, contact frames, loudness
// Capture (shim.js, injected before the page's scripts; page and conker.wasm unchanged): with ?det=1 the main loop runs one
// VI retrace per animation frame, so queuing requestAnimationFrame steps the game retrace by retrace at any speed; 60 fps
// pictures at retrace position start + i * 50 / 60 with the High frame rate interpolation (port_gfx_hfr_test); the wasm
// import __port_web_audio_open is replaced, so no AudioContext opens and the game's PCM ring is drained every retrace.
// P354 trailer: run the compositor (compose.html / compose.js) in headless Chrome.
//   node tools/port/trailer/render.mjs                 the MP4 -> port_work/trailer/out/trailer.mp4
//   node tools/port/trailer/render.mjs small           2.6 Mbit/s copy (~28 MB for 79 s) -> out/trailer_small.mp4
//   node tools/port/trailer/render.mjs preview F,F,..  only these frames (60 fps timeline) -> out/key_NNNNN.jpg
//   node tools/port/trailer/render.mjs audio speech|1  only the edited speech / the whole soundtrack -> out/speech.wav, audio.wav
//   env Q='&k=v...' adds compositor options: pixelfont=1 (the old blocky titles), music=FILE (port_work/trailer/music/FILE,
//   an open-licensed track instead of the game's), credit=TEXT (end card "MUSIC: TEXT"), downbeat=S (a downbeat of FILE),
//   out=NAME.mp4
// P355: the ROM is served read-only at /rom.z64: the compositor decodes Conker's "good" from its MP3 voice clip.
// Needs: mp4-muxer installed under port_work/trailer/npm (npm install mp4-muxer@5.2.2, local tooling, not committed),
// the shots (capture.mjs), pages (pagecap.mjs), net4/ (net4.sh) and font/font.json (fontdump.mjs).
import fs from 'node:fs';
import path from 'node:path';
import { launch, serve, sleep } from './cdp.mjs';

const ROOT = path.resolve(path.dirname(new URL(import.meta.url).pathname), '../../..');
process.chdir(ROOT);
const outDir = path.resolve('port_work/trailer/out'); fs.mkdirSync(outDir, { recursive: true });
const port = 8670 + (process.pid % 10);
const srv = await serve({ '/t/': 'tools/port/trailer', '/w/': 'port_work/trailer',
  '/rom.z64': 'baserom.eu.z64',
  '/npm/mp4-muxer.js': 'port_work/trailer/npm/node_modules/mp4-muxer/build/mp4-muxer.js' }, port, outDir);
const q = (process.argv[2] === 'preview' ? `?preview=${process.argv[3]}`
  : process.argv[2] === 'audio' ? `?audio=${process.argv[3] || 1}`
  : process.argv[2] === 'small' ? '?br=2600000&out=trailer_small.mp4' : '?') + (process.env.Q || '');
const b = await launch(`http://127.0.0.1:${port}/t/compose.html${q}`, { log: path.join(outDir, 'compose.log') });
try {
  for (let i = 0; i < 100; i++) { if (await b.ev('typeof window.__run === "function"').catch(() => false)) break; await sleep(200); }
  const t0 = Date.now();
  const tick = setInterval(() => { const l = fs.readFileSync(path.join(outDir, 'compose.log'), 'utf8').trim().split('\n').pop(); process.stdout.write(`\r${l}            `); }, 5000);
  const r = await b.ev('window.__run()', 3600000);
  clearInterval(tick);
  console.log(`\n${r} (${((Date.now() - t0) / 1000).toFixed(0)} s wall)`);
} finally { await b.close(); srv.close(); }
process.exit(0);
