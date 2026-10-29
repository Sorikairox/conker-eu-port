// P357 end-to-end replay driver: one input recording (.ckrec, port/web/main.js "input recorder") replayed in ONE muted
// headless Chrome as fast as the page can run it (?replay=URL: pc_net.c section 5 fast replay), compared checkpoint by
// checkpoint with the recording by the page itself (main.js e2eCheck). Called by tools/port/scripts/e2e_replay.sh.
//   node tools/port/scripts/e2e_replay.js URL OUTDIR [TIMEOUT_S]
// Writes OUTDIR/chrome.log (page console), OUTDIR/result.json (window.__e2e.status() at the end), OUTDIR/actual.png
// (the canvas when the replay stopped: at the first difference, or at ?replaystop) and prints one JSON line.
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [url, out = '.', tmo = '1800'] = process.argv.slice(2);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'e2e-'));
const port = 9300 + (process.pid % 500);
fs.mkdirSync(out, { recursive: true });
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, `--use-angle=${process.env.PROBE_ANGLE || 'metal'}`,
  '--enable-unsafe-swiftshader', '--mute-audio', '--autoplay-policy=no-user-gesture-required', '--window-size=1000,900',
  '--disable-background-timer-throttling', '--disable-renderer-backgrounding', '--disable-backgrounding-occluded-windows', url], { stdio: 'ignore' });
const done = (code) => { try { ch.kill('SIGKILL'); } catch (e) {} fs.rmSync(dir, { recursive: true, force: true }); process.exit(code); };
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
setTimeout(() => { console.log(JSON.stringify({ state: 'timeout' })); done(2); }, +tmo * 1000);
(async () => {
  let page;
  for (let i = 0; i < 50 && !page; i++) {
    await sleep(300);
    try { page = (await (await fetch(`http://127.0.0.1:${port}/json`)).json()).find((t) => t.type === 'page'); } catch (e) {}
  }
  if (!page) { console.log(JSON.stringify({ state: 'error', error: 'no DevTools page' })); return done(2); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
  await new Promise((r) => ws.addEventListener('open', r));
  let id = 0; const pending = new Map();
  const logFile = path.join(out, 'chrome.log'); fs.writeFileSync(logFile, '');
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Runtime.consoleAPICalled') fs.appendFileSync(logFile, d.params.args.map((a) => a.value ?? a.description ?? '').join(' ') + '\n');
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const call = (method, params) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  const ev = async (expr, ms = 15000) => {
    const r = await Promise.race([call('Runtime.evaluate', { expression: expr, returnByValue: true, awaitPromise: true }), sleep(ms).then(() => null)]);
    return r && r.result && r.result.result ? r.result.result.value : undefined;
  };
  await call('Runtime.enable', {});
  const t0 = Date.now();
  let st = null, lastShown = 0;
  for (;;) {
    await sleep(500);
    st = await ev('window.__e2e ? window.__e2e.status() : null');
    if (!st) continue;
    if (Date.now() - lastShown > 15000 && st.total) {
      lastShown = Date.now();
      process.stderr.write(`  ... retrace ${st.frame} / ${st.total} (${(100 * st.frame / st.total).toFixed(0)} %), ${((Date.now() - t0) / 1000).toFixed(0)} s\n`);
    }
    if (['done', 'mismatch', 'error'].includes(st.state) && (st.state !== 'mismatch' || st.endFrame || st.first)) break;
  }
  st.wall_s = (Date.now() - t0) / 1000;
  if (st.state !== 'error') {   // the canvas as the replay left it (paused at the first difference / its end)
    await sleep(300);
    const u = await ev("document.getElementById('canvas').toDataURL('image/png')");
    if (u) { fs.writeFileSync(path.join(out, 'actual.png'), Buffer.from(u.split(',')[1], 'base64')); st.shot = path.join(out, 'actual.png'); }
  }
  fs.writeFileSync(path.join(out, 'result.json'), JSON.stringify(st, null, 1));
  console.log(JSON.stringify(st));
  done(st.state === 'done' ? 0 : 1);
})();
