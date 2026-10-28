// P354 trailer: the real page (port/build/web/index.html, unchanged) as a visitor sees it, for the "plays in your browser"
// beat: viewport screenshots (CDP Page.captureScreenshot, JPEG) while the game is stepped frame by frame (shim.js).
//   node tools/port/trailer/pagecap.mjs NAME      (NAME: a key of PAGESHOTS below)    env OUT (default port_work/trailer/pages)
// Output OUT/NAME/: still_*.jpg (single pictures of the steps) and f00000.jpg ... (pictures at fps while the game runs).
import fs from 'node:fs';
import path from 'node:path';
import { launch, serve, sleep } from './cdp.mjs';

const ROOT = path.resolve(path.dirname(new URL(import.meta.url).pathname), '../../..');
process.chdir(ROOT);
const OUT = process.env.OUT || 'port_work/trailer/pages';
const RUN29 = 'padf=100:0:0:0,130:0:0:80,250:0:30:80,330:8000:30:80,338:0:30:80,420:0:-50:70,520:0:0:80,600:8000:0:80,608:0:0:80,700:0:60:60,800:0:0:80,900:0:-60:60,1000:0:0:0';
const PAGESHOTS = {
  // a visitor's first load: the ROM drop screen, the ROM picked (stays on this computer), Start, the game in the page
  // (level 0x29 through the ?warp test aid so that the shot is short; the query is not visible in the pictures)
  site: { query: `warp=29&det=1&p103boot=1&mute=1&opt=hires2d:1,widescreen:1,fullres:1,hfr:1,volmusic:0&${RUN29}`,
    viewport: [1280, 720], rom: true, start: 230, secs: 5, fps: 60, hfr: true },
  // the Options panel with the presets (Modern picked), next to the running game
  options: { query: `warp=29&det=1&p103boot=1&mute=1&panel=options&opt=volmusic:0&${RUN29}`, viewport: [1600, 900], rom: true,
    preset: 'modern', start: 200, secs: 0.5, fps: 2, hfr: true },
};

const name = process.argv[2]; const s = PAGESHOTS[name];
if (!s) { console.log('shots: ' + Object.keys(PAGESHOTS).join(' ')); process.exit(2); }
const dir = path.join(OUT, name); fs.rmSync(dir, { recursive: true, force: true }); fs.mkdirSync(dir, { recursive: true });
const port = 8620 + (process.pid % 10);
const srv = await serve({ '/app/': 'port/build/web', '/dev/rom.z64': 'baserom.eu.z64' }, port, dir);
const [vw, vh] = s.viewport;
const b = await launch(`http://127.0.0.1:${port}/app/index.html?${s.query}`, { init: fs.readFileSync('tools/port/trailer/shim.js', 'utf8'),
  log: path.join(dir, 'chrome.log'), viewport: s.viewport, width: vw, height: vh });
const shot = async (file) => {
  const r = await b.call('Page.captureScreenshot', { format: 'jpeg', quality: 92 });
  fs.writeFileSync(path.join(dir, file), Buffer.from(r.result.data, 'base64'));
};
try {
  for (let i = 0; i < 100; i++) { if (await b.ev("document.readyState === 'complete' && !!document.getElementById('rom')")) break; await sleep(200); }
  await sleep(1500);
  await shot('still_0_drop.jpg');
  if (s.rom) {   // the ROM through the page's own file picker
    await b.call('DOM.enable', {});
    const doc = await b.call('DOM.getDocument', {});
    const q = await b.call('DOM.querySelector', { nodeId: doc.result.root.nodeId, selector: '#rom' });
    await b.call('DOM.setFileInputFiles', { nodeId: q.result.nodeId, files: [path.resolve('baserom.eu.z64')] });
    for (let i = 0; i < 100; i++) { if (!(await b.ev("document.getElementById('start').disabled"))) break; await sleep(200); }
    await sleep(800);
    await shot('still_1_rom.jpg');
    await b.ev("document.getElementById('start').click(), 1");
  }
  for (let i = 0; i < 200; i++) { if ((await b.ev('__trailer.q.length && __trailer.frame() >= 0 ? 1 : 0')) === 1) break; await sleep(250); }
  if (s.preset) await b.ev(`document.getElementById('preset-${s.preset}').click(), 1`);
  while ((await b.ev(`__trailer.runTo(${s.start}, 40)`)) < s.start);
  await sleep(500);
  await shot('still_2_running.jpg');
  const n = Math.round(s.secs * s.fps), k = 50 / s.fps;
  for (let i = 0; i < n; i++) {
    await b.ev(`__trailer.step(${s.start + i * k}, ${s.hfr ? 1 : 0}, null)`);
    await shot(`f${String(i).padStart(5, '0')}.jpg`);
    if (i % 60 === 0) console.log(`  ${name} pic ${i}/${n}`);
  }
  console.log(`${name}: done, ${n} pictures ${vw}x${vh}, traps ${fs.readFileSync(path.join(dir, 'chrome.log'), 'utf8').split('\n').filter((l) => /Aborted|RuntimeError/.test(l)).length}`);
} finally { await b.close(); srv.close(); }
process.exit(0);
