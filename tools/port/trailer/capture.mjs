// P354 trailer: capture one gameplay shot from the port, frame by frame (deterministic, independent of wall time).
//   node tools/port/trailer/capture.mjs SHOT [more shots...]      (shots: tools/port/trailer/shots.mjs)
//   env OUT=dir (default port_work/trailer/shots), ONLYSTILL=1 (one JPEG at the shot's start, to frame a shot),
//       FRAMES=N (capture only the first N pictures), MAXWALL=S (give up after S s wall, e.g. a level that traps)
// The game page (port/build/web, unchanged) is served with the ROM at /dev/rom.z64 and opened with ?det=1 (one VI
// retrace per animation frame) + the shot's query; shim.js takes over requestAnimationFrame and the audio sink.
// Output per shot in OUT/NAME/: f00000.jpg ... (fps pictures per second; with hfr the High frame rate option's
// interpolation between game frames), audio.pcm (stereo s16 at the game's rate from 'audioFrom' retraces before the
// first picture), meta.json (per picture: retrace, t; audio map retrace -> pcm frames, rate).
// Muted (no audio device is opened at all), one headless Chrome. Never commit the output (ROM-derived pictures).
import fs from 'node:fs';
import path from 'node:path';
import { launch, serve, sleep } from './cdp.mjs';
import { SHOTS } from './shots.mjs';

const ROOT = path.resolve(path.dirname(new URL(import.meta.url).pathname), '../../..');
process.chdir(ROOT);
const OUT = process.env.OUT || 'port_work/trailer/shots';
const MAXWALL = +(process.env.MAXWALL || 0);   // seconds: give up (and close Chrome) when the game stops advancing
const SHIM = fs.readFileSync('tools/port/trailer/shim.js', 'utf8');

async function captureShot(name) {
  // adhoc[_TAG]: a trial shot from the environment (SHOTQ query, SHOTSTART, SHOTSECS, SHOTCANVAS, SHOTHFR=0, SHOTFPS)
  const s = name.startsWith('adhoc') ? { query: process.env.SHOTQ, start: +(process.env.SHOTSTART || 215), secs: +(process.env.SHOTSECS || 8),
    canvas: process.env.SHOTCANVAS, hfr: process.env.SHOTHFR !== '0', fps: +(process.env.SHOTFPS || 60) } : { ...SHOTS[name] };
  if (s && process.env.PADSHIFT) s.padShift = +process.env.PADSHIFT;   // trials
  if (s && process.env.START) s.start = +process.env.START;
  if (!s) throw new Error('unknown shot ' + name + ' (shots.mjs: ' + Object.keys(SHOTS).join(' ') + ')');
  const dir = path.join(OUT, name); fs.rmSync(dir, { recursive: true, force: true }); fs.mkdirSync(dir, { recursive: true });
  const port = 8590 + (process.pid % 50);
  const srv = await serve({ '/app/': s.web || 'port/build/web', '/dev/rom.z64': 'baserom.eu.z64' }, port, dir);
  const fps = s.fps || 60, n = process.env.ONLYSTILL ? 1 : Math.min(+(process.env.FRAMES || 1e9), Math.round(s.secs * fps));
  const [cw, ch] = (s.canvas || '1920x1080').split('x').map(Number);
  const [ow, oh] = s.out || [cw, ch];
  let padq = '';
  if (s.padsEnv) {   // PADF0..PADF3 lines of net4.sh's pads.env -> ?padf / ?padf1..3
    const env = Object.fromEntries(fs.readFileSync(s.padsEnv, 'utf8').split('\n').filter(Boolean).map((l) => [l.slice(0, 5), l.slice(6)]));
    // padShift: the online session applies each pad sample D retraces later (input delay; net4: auto delay 2)
    const sh = (v) => v.split(',').map((e) => { const p = e.split(':'); p[0] = String(+p[0] + (s.padShift || 0)); return p.join(':'); }).join(',');
    padq = `&padf=${sh(env.PADF0)}&padf1=${sh(env.PADF1)}&padf2=${sh(env.PADF2)}&padf3=${sh(env.PADF3)}`;
  }
  const url = `http://127.0.0.1:${port}/app/index.html?app=game&det=1&p103boot=1&mute=1&romurl=../dev/rom.z64&canvas=${cw}x${ch}${s.query}${padq}`;
  const log = path.join(dir, 'chrome.log');
  const b = await launch(url, { init: SHIM, log, width: 1400, height: 1000 });
  const t0 = Date.now();
  try {
    for (let i = 0; i < 200; i++) { if ((await b.ev('__trailer.q.length && __trailer.frame() >= 0 ? 1 : 0')) === 1) break; await sleep(250); }
    const start = s.start, audioFrom = start - (s.audioFrom ?? 40);
    // run to the audio start, then to the first picture (with any scripted page actions on the way)
    const steps = (s.steps || []).slice().sort((a, b2) => a.at - b2.at);
    const runTo = async (f) => {
      while (true) {
        const next = steps.length && steps[0].at <= f ? steps[0].at : f;
        let cur;
        do {
          cur = await b.ev(`__trailer.runTo(${next}, 40)`);
          if (MAXWALL && Date.now() - t0 > MAXWALL * 1000) throw new Error(`${name}: MAXWALL ${MAXWALL} s reached at retrace ${cur}`);
        } while (cur < next);
        if (steps.length && steps[0].at <= cur && steps[0].at <= f) { const st = steps.shift(); console.log(`  step @${cur}: ${st.eval.slice(0, 80)} -> ${JSON.stringify(await b.ev(st.eval))}`); continue; }
        if (cur >= f) return cur;
      }
    };
    await runTo(audioFrom);
    await b.ev('__trailer.capAudio = true; __trailer.audMap.push([__trailer.frame(), 0]); 1');
    await runTo(start);
    console.log(`${name}: at retrace ${start} after ${((Date.now() - t0) / 1000).toFixed(0)} s; ${n} pictures ${ow}x${oh} @${fps}`);
    const meta = { name, fps, canvas: [cw, ch], out: [ow, oh], start, query: s.query, frames: [] };
    const k = 50 / fps;   // PAL: 50 retraces per second
    for (let i = 0; i < n; i++) {
      const pos = start + i * k;
      if (!s.ticksPerPic) while (steps.length && steps[0].at <= Math.floor(pos)) { await runTo(steps[0].at); }
      const r = await b.ev(`__trailer.step(${pos}, ${s.hfr ? 1 : 0}, '/upload/f${String(i).padStart(5, '0')}.jpg', ${ow}, ${oh}, ${s.quality || 0.92}, ${i && s.ticksPerPic ? s.ticksPerPic : 0})`);
      meta.frames.push([r.frame, r.t, r.res]);
      if (i % 60 === 0) console.log(`  pic ${i}/${n} retrace ${r.frame} t ${r.t} res ${r.res} ${(r.size / 1024).toFixed(0)} KB (${((Date.now() - t0) / 1000).toFixed(0)} s)`);
    }
    // audio: a little past the last picture (the sink runs ~150 ms behind the retrace that pushed it)
    if (!s.ticksPerPic) await runTo(Math.floor(start + n * k) + 20);
    const a = JSON.parse(await b.ev(`(async () => { const p = __trailer.takePcm(); await __trailer.upload('/upload/audio.pcm', p.buffer);
      return JSON.stringify({ rate: __trailer.aud ? __trailer.aud.rate : 0, map: __trailer.audMap }); })()`));
    meta.audio = { rate: a.rate, from: audioFrom, map: a.map.filter((x, i, A) => i === 0 || x[0] !== A[i - 1][0]) };
    fs.writeFileSync(path.join(dir, 'meta.json'), JSON.stringify(meta));
    const traps = fs.readFileSync(log, 'utf8').split('\n').filter((l) => /Aborted|RuntimeError|EXCEPTION/.test(l));
    console.log(`${name}: done, ${n} pictures, audio ${(fs.statSync(path.join(dir, 'audio.pcm')).size / 4 / (a.rate || 1)).toFixed(1)} s at ${a.rate} Hz, traps ${traps.length}, ${((Date.now() - t0) / 1000).toFixed(0)} s wall`);
    if (traps.length) console.log(traps.slice(0, 3).join('\n'));
  } finally { await b.close(); srv.close(); srv.closeAllConnections?.(); }
}

for (const name of process.argv.slice(2)) await captureShot(name);
process.exit(0);
