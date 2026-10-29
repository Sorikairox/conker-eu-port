// P357 test of the input recorder the way a player uses it: ONE muted headless Chrome opens the page, ticks Options >
// "Input recorder", opens the Record panel, types a name, presses "Start recording", then plays with real key events
// (CDP Input.dispatchKeyEvent, the page's normal keyboard path) at real time while the game runs at its wall-paced 50 Hz,
// and finally presses "Stop and save"; the page's download lands in OUTDIR. Not the ?padf / det fast path: the input
// reaches the game whenever the key event arrives, as with a person at the keyboard.
//   node tools/port/scripts/e2e_record.js URL OUTDIR NAME 'STEPS'
//   STEPS: "RETRACE:down:CODE; RETRACE:up:CODE; RETRACE:hide; RETRACE:show; RETRACE:esc; RETRACE:stop" — each step is
//   sent once the game's retrace counter reached RETRACE (polled every ~10 ms); CODE = a KeyboardEvent code (Enter =
//   Start, KeyR = L, KeyW/A/S/D = stick, Space = A, KeyF = B ...). hide = another tab in front of the page (the page is
//   hidden: the game pauses), show:MS = back after MS ms of wall time; esc = the Pause button, unpause:MS =
//   the button again after MS ms of wall time (a paused or hidden game runs no retraces, so these wait on the clock).
// Logs OUTDIR/chrome.log; prints the downloaded file name.
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [url, out = '.', name = 'test', stepsArg = ''] = process.argv.slice(2);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'e2erec-'));
const port = 9300 + (process.pid % 500);
fs.mkdirSync(out, { recursive: true });
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, '--use-angle=metal',
  '--mute-audio', '--autoplay-policy=no-user-gesture-required', '--window-size=1400,1000', 'about:blank'], { stdio: 'ignore' });
const done = (code) => { try { ch.kill('SIGKILL'); } catch (e) {} fs.rmSync(dir, { recursive: true, force: true }); process.exit(code); };
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
setTimeout(() => { console.log('e2e_record: timeout'); done(2); }, +(process.env.TIMEOUT || 1800) * 1000);
async function connect(wsUrl, logFile) {
  const ws = new WebSocket(wsUrl);
  await new Promise((r) => ws.addEventListener('open', r));
  let id = 0; const pending = new Map();
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Runtime.consoleAPICalled' && logFile) fs.appendFileSync(logFile, d.params.args.map((a) => a.value ?? a.description ?? '').join(' ') + '\n');
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const call = (method, params) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  const ev = async (expr) => {
    const r = await call('Runtime.evaluate', { expression: expr, returnByValue: true, awaitPromise: true });
    if (r.result?.exceptionDetails) throw new Error(expr + ': ' + JSON.stringify(r.result.exceptionDetails).slice(0, 300));
    return r.result?.result?.value;
  };
  return { call, ev };
}
const keyInfo = (code) => {
  if (/^Key[A-Z]$/.test(code)) return { key: code[3].toLowerCase(), keyCode: code.charCodeAt(3) };
  return { Space: { key: ' ', keyCode: 32 }, Enter: { key: 'Enter', keyCode: 13 }, Escape: { key: 'Escape', keyCode: 27 },
    ArrowLeft: { key: 'ArrowLeft', keyCode: 37 }, ArrowUp: { key: 'ArrowUp', keyCode: 38 }, ArrowRight: { key: 'ArrowRight', keyCode: 39 },
    ArrowDown: { key: 'ArrowDown', keyCode: 40 }, ControlLeft: { key: 'Control', keyCode: 17 } }[code] || { key: code, keyCode: 0 };
};
(async () => {
  let ver;
  for (let i = 0; i < 50 && !ver; i++) { await sleep(300); try { ver = await (await fetch(`http://127.0.0.1:${port}/json/version`)).json(); } catch (e) {} }
  if (!ver) { console.log('e2e_record: no DevTools'); return done(2); }
  const br = await connect(ver.webSocketDebuggerUrl);
  const logFile = path.join(out, 'chrome.log'); fs.writeFileSync(logFile, '');
  const list = await (await fetch(`http://127.0.0.1:${port}/json`)).json();
  const tgt = list.find((x) => x.type === 'page');
  const pg = await connect(tgt.webSocketDebuggerUrl, logFile);
  await pg.call('Runtime.enable', {});
  await br.call('Browser.setDownloadBehavior', { behavior: 'allow', downloadPath: path.resolve(out), eventsEnabled: true });
  await pg.call('Page.navigate', { url });
  for (let i = 0; i < 100; i++) { if (await pg.ev("typeof romOk !== 'undefined' && romOk").catch(() => false)) break; await sleep(300); }
  // the player's clicks: Options > Input recorder, the Record button, the name, Start recording
  await pg.ev("document.getElementById('t-options').click(); if (!document.getElementById('opt-recorder').checked) document.getElementById('opt-recorder').click(); document.getElementById('t-options').click()");
  await pg.ev("document.getElementById('t-rec').click()");
  await pg.ev(`document.getElementById('rec-name').value = ${JSON.stringify(name)}; document.getElementById('rec-start').click()`);
  await sleep(1000);
  await pg.ev("document.getElementById('canvas').focus()");
  console.log(`e2e_record: recording started: ${await pg.ev("document.getElementById('rec-status').textContent")}`);
  const steps = stepsArg.split(';').map((x) => x.trim()).filter(Boolean).map((x) => { const [f, act, arg] = x.split(':'); return { f: +f, act, arg }; });
  let coverId = null, winId = null;
  const t0 = Date.now();
  const frame = async () => +(await pg.ev('window.Module && Module._port_net_frame ? Module._port_net_frame() : 0').catch(() => 0));
  for (const s of steps) {
    // a hidden page runs no retraces: steps after "hide" wait on the wall clock instead (arg = milliseconds)
    if (s.act === 'show' || s.act === 'unpause') { await sleep(+s.arg || 5000); }
    else for (;;) { const f = await frame(); if (f >= s.f) break; await sleep(f < s.f - 100 ? 200 : 8); }
    const f = await frame();
    if (s.act === 'down' || s.act === 'up') {
      const k = keyInfo(s.arg);
      await pg.call('Input.dispatchKeyEvent', { type: s.act === 'down' ? 'rawKeyDown' : 'keyUp', code: s.arg, key: k.key, windowsVirtualKeyCode: k.keyCode, nativeVirtualKeyCode: k.keyCode });
    } else if (s.act === 'esc' || s.act === 'unpause') {   // the Pause button (Escape's handler does the same setPaused; a
      await pg.ev("document.getElementById('pause').click(); document.getElementById('canvas').focus()");   // CDP Escape hid the headless tab)
    } else if (s.act === 'hide') {   // minimise the window (as netgroup.js HIDE); a tab in front if the page still shows
      winId = winId || (await br.call('Browser.getWindowForTarget', { targetId: tgt.id })).result?.windowId;
      await br.call('Browser.setWindowBounds', { windowId: winId, bounds: { windowState: 'minimized' } }); await sleep(500);
      if (await pg.ev('document.visibilityState') !== 'hidden') {
        coverId = (await br.call('Target.createTarget', { url: 'about:blank', windowId: winId })).result?.targetId;
        await br.call('Target.activateTarget', { targetId: coverId }); await sleep(300);
      }
    } else if (s.act === 'show') {
      if (coverId) { await br.call('Target.closeTarget', { targetId: coverId }); coverId = null; }
      await br.call('Browser.setWindowBounds', { windowId: winId, bounds: { windowState: 'normal' } });
      await br.call('Target.activateTarget', { targetId: tgt.id }); await sleep(500);
    } else if (s.act === 'stop') {
      await pg.ev("document.getElementById('rec-stop').click()");
    }
    console.log(`e2e_record ${((Date.now() - t0) / 1000).toFixed(1)} s: retrace ${f} (step at ${s.f}) ${s.act} ${s.arg || ''}` +
      (s.act === 'hide' || s.act === 'show' ? `, page ${await pg.ev('document.visibilityState')}` : '') +
      (['hide', 'show', 'esc', 'unpause'].includes(s.act) ? `, recorder: ${await pg.ev("document.getElementById('rec-status').textContent")}` : ''));
    if (s.act === 'stop') break;
  }
  for (let i = 0; i < 100; i++) { const f = fs.readdirSync(out).filter((x) => x.endsWith('.ckrec')); if (f.length) { await sleep(500); console.log('e2e_record: saved ' + path.join(out, f[0]) + ' ' + JSON.stringify(await pg.ev('__rec.status()'))); break; } await sleep(300); }
  console.log('e2e_record: ' + await pg.ev("document.getElementById('rec-status').textContent"));
  done(0);
})().catch((e) => { console.log('e2e_record: ' + e); done(3); });
