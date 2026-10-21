// P14: drive headless Chrome over the DevTools protocol (node >= 22: global WebSocket, no packages)
// and poll the page's audio probe (main.js installAudioProbe) in real time.
//   node port/web/audprobe.js URL [seconds]   (port/web/audprobe.sh serves the build and calls this)
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [url, secs = '12'] = process.argv.slice(2);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'audprobe-'));
const port = 9300 + (process.pid % 500);
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, '--use-angle=swiftshader',
  '--enable-unsafe-swiftshader', '--autoplay-policy=no-user-gesture-required', '--window-size=1000,900', url], { stdio: 'ignore' });
const done = (code) => { try { ch.kill('SIGKILL'); } catch (e) {} fs.rmSync(dir, { recursive: true, force: true }); process.exit(code); };
setTimeout(() => { console.log('audprobe: timeout'); done(2); }, (+secs + 90) * 1000);
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
(async () => {
  let page;
  for (let i = 0; i < 50 && !page; i++) {
    await sleep(300);
    try { page = (await (await fetch(`http://127.0.0.1:${port}/json`)).json()).find((t) => t.type === 'page'); } catch (e) {}
  }
  if (!page) { console.log('audprobe: no DevTools page'); return done(2); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
  await new Promise((r) => ws.addEventListener('open', r));
  let id = 0; const pending = new Map();
  let paused = null;
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Debugger.paused') paused = d.params;
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const call = (method, params) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  const ev = async (expr) => {
    const r = await Promise.race([call('Runtime.evaluate', { expression: expr, returnByValue: true }), sleep(4000).then(() => 'timeout')]);
    if (r !== 'timeout') return r.result?.result?.value;
    // main thread busy: pause it and print where it is (diagnostic for a page that never yields)
    console.log('audprobe: page main thread does not respond; pausing it for a stack');
    call('Debugger.enable', {}); await sleep(500); call('Debugger.pause', {});
    for (let i = 0; i < 20 && !paused; i++) await sleep(250);
    if (paused) console.log(paused.callFrames.slice(0, 25).map((f) => '  at ' + (f.functionName || '?') + ' ' + f.url.split('/').pop() + ':' + f.location.lineNumber).join('\n'));
    else console.log('audprobe: no pause event');
    done(3);
  };
  let last = null; const t0 = Date.now();
  if (process.env.PROBE_EVAL) { await sleep(+(process.env.PROBE_AT || 3000)); console.log('eval:', await ev(process.env.PROBE_EVAL)); }
  for (let t = 0; t < +secs; t++) {
    await sleep(1000);
    const s = await ev('window.audprobe ? JSON.stringify(window.audprobe) : null');
    if (s) { last = JSON.parse(s); console.log(`t=${t + 1}s (${((Date.now() - t0) / 1000).toFixed(1)}s) ` + s); }
  }
  const lines = await ev(`Array.from(document.querySelectorAll('#console *')).map(e => e.textContent).filter(l => /\\[aud|\\[audtest|\\[voicetest|fail/.test(l)).slice(-8).join('\\n')`);
  if (lines) console.log(lines);
  const ok = last && last.frames > 0 && last.nonzero > 1000 && last.sq / last.nonzero > 1e-5;
  console.log(ok ? `[audprobe] PASS: Web Audio pulled ${last.frames} frames, ${last.nonzero} non-zero samples`
                 : '[audprobe] FAIL: no audible samples reached the Web Audio graph');
  done(ok ? 0 : 1);
})();
