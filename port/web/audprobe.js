// P14: drive headless Chrome over the DevTools protocol (node >= 22: global WebSocket, no packages)
// and poll the page's audio probe (main.js installAudioProbe) in real time.
//   node port/web/audprobe.js URL [seconds]   (port/web/audprobe.sh serves the build and calls this)
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [url, secs = '12'] = process.argv.slice(2);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'audprobe-'));
const port = 9300 + (process.pid % 500);
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, `--use-angle=${process.env.PROBE_ANGLE || 'swiftshader'}`,
  '--enable-unsafe-swiftshader', ...(process.env.PROBE_NOAUTOPLAY ? [] : ['--autoplay-policy=no-user-gesture-required']), '--window-size=1000,900', url], { stdio: 'ignore' });
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
  let paused = null, maxLat = 0;
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Debugger.paused') paused = d.params;
    // P21: stream the page console (main.js log() -> console.log) to PROBE_LOG as it happens, so a page
    // that stops answering still leaves its log
    if (d.method === 'Runtime.consoleAPICalled' && process.env.PROBE_LOG)
      fs.appendFileSync(process.env.PROBE_LOG, d.params.args.map((a) => a.value ?? a.description ?? '').join(' ') + '\n');
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const call = (method, params) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  const ev = async (expr) => {
    const te = Date.now();  // P21: PROBE_EVAL_TIMEOUT (ms, default 4000); the slowest answer is reported at the end
    const r = await Promise.race([call('Runtime.evaluate', { expression: expr, returnByValue: true }), sleep(+(process.env.PROBE_EVAL_TIMEOUT || 4000)).then(() => 'timeout')]);
    if (r !== 'timeout') { maxLat = Math.max(maxLat, Date.now() - te); return r.result?.result?.value; }
    // main thread busy: pause it and print where it is (diagnostic for a page that never yields)
    console.log('audprobe: page main thread does not respond; pausing it for a stack');
    call('Debugger.enable', {}); await sleep(500);
    // P21: several samples (pause, print, resume) tell a tight loop from slow progress
    const nsamp = +(process.env.PROBE_SAMPLES || 1);
    for (let k = 0; k < nsamp; k++) {
      paused = null; call('Debugger.pause', {});
      for (let i = 0; i < 20 && !paused; i++) await sleep(250);
      if (paused) console.log(`sample ${k + 1}:\n` + paused.callFrames.slice(0, +(process.env.PROBE_DEPTH || 25)).map((f) => '  at ' + (f.functionName || '?') + ' ' + f.url.split('/').pop() + ':' + f.location.lineNumber + ':' + f.location.columnNumber).join('\n'));
      else { console.log('audprobe: no pause event'); break; }
      call('Debugger.resume', {}); await sleep(400);
    }
    done(3);
  };
  if (process.env.PROBE_LOG) { fs.writeFileSync(process.env.PROBE_LOG, ''); call('Runtime.enable', {}); }
  // P21: PROBE_PROFILE=MS: CPU profile of the first MS ms, top self-time functions (waits for a busy page)
  if (process.env.PROBE_PROFILE) {
    await call('Profiler.enable', {}); await call('Profiler.setSamplingInterval', { interval: 1000 }); await call('Profiler.start', {});
    await sleep(+process.env.PROBE_PROFILE);
    const r = await Promise.race([call('Profiler.stop', {}), sleep(60000).then(() => null)]);
    const prof = r && r.result && r.result.profile;
    if (!prof) console.log('profile: no answer');
    else {
      const self = new Map(), byId = new Map(prof.nodes.map((n) => [n.id, n]));
      const dt = prof.timeDeltas, smp = prof.samples;
      for (let i = 0; i < smp.length; i++) { const n = byId.get(smp[i]); const k = n.callFrame.functionName || '(' + n.callFrame.url.split('/').pop() + ')'; self.set(k, (self.get(k) || 0) + (dt[i + 1] || 0)); }
      const tot = [...self.values()].reduce((a, b) => a + b, 0);
      console.log(`profile: ${(tot / 1000).toFixed(0)} ms sampled; top self time:`);
      for (const [k, v] of [...self.entries()].sort((a, b) => b[1] - a[1]).slice(0, +(process.env.PROBE_TOP || 20))) console.log(`  ${(v / 1000).toFixed(0).padStart(6)} ms  ${k}`);
    }
  }
  let last = null; const t0 = Date.now();
  // P27: PROBE_STEPS="MS:click; MS:keydown:CODE; MS:keyup:CODE; MS:nav:QUERY; MS:eval:EXPR" (MS from now).
  // Input goes through Input.dispatch*Event, so it counts as a real user gesture (audio resume test).
  // PROBE_NOAUTOPLAY=1 keeps Chrome's default autoplay policy (a context starts suspended).
  const keyInfo = (code) => {
    if (/^Key[A-Z]$/.test(code)) return { key: code[3].toLowerCase(), keyCode: code.charCodeAt(3) };
    return { Space: { key: ' ', keyCode: 32 }, Enter: { key: 'Enter', keyCode: 13 }, Escape: { key: 'Escape', keyCode: 27 },
      ArrowLeft: { key: 'ArrowLeft', keyCode: 37 }, ArrowUp: { key: 'ArrowUp', keyCode: 38 }, ArrowRight: { key: 'ArrowRight', keyCode: 39 },
      ArrowDown: { key: 'ArrowDown', keyCode: 40 }, ControlLeft: { key: 'Control', keyCode: 17 } }[code] || { key: code, keyCode: 0 };
  };
  for (const st of (process.env.PROBE_STEPS || '').split(';').map((x) => x.trim()).filter(Boolean)) {
    const [ms, act, ...rest] = st.split(':'); const arg = rest.join(':');
    setTimeout(async () => {
      console.log(`step t=${((Date.now() - t0) / 1000).toFixed(1)}s ${act} ${arg}`);
      if (act === 'click') {
        for (const type of ['mousePressed', 'mouseReleased']) await call('Input.dispatchMouseEvent', { type, x: 300, y: 300, button: 'left', clickCount: 1 });
      } else if (act === 'keydown' || act === 'keyup') {
        const k = keyInfo(arg);
        await call('Input.dispatchKeyEvent', { type: act === 'keydown' ? 'rawKeyDown' : 'keyUp', code: arg, key: k.key, windowsVirtualKeyCode: k.keyCode, nativeVirtualKeyCode: k.keyCode });
      } else if (act === 'nav') await call('Page.navigate', { url: url.replace(/\?.*$/, '?' + arg) });
      else if (act === 'eval') console.log('eval:', await ev(arg));
    }, +ms);
  }
  if (process.env.PROBE_EVAL) { await sleep(+(process.env.PROBE_AT || 3000)); console.log('eval:', await ev(process.env.PROBE_EVAL)); }
  for (let t = 0; t < +secs; t++) {
    await sleep(1000);
    const s = await ev('window.audprobe ? JSON.stringify(window.audprobe) : null');
    if (s) { last = JSON.parse(s); console.log(`t=${t + 1}s (${((Date.now() - t0) / 1000).toFixed(1)}s) ` + s); }
  }
  if (process.env.PROBE_SHOT) {  // P19: real-time screenshot over CDP (--virtual-time-budget never ends now)
    const r = await Promise.race([call('Page.captureScreenshot', { format: 'png' }), sleep(10000).then(() => null)]);
    const b64 = r && (r.result ? r.result.data : r.data);
    if (b64) { require('fs').writeFileSync(process.env.PROBE_SHOT, Buffer.from(b64, 'base64')); console.log('screenshot:', process.env.PROBE_SHOT); }
    else console.log('screenshot: no answer');
  }
  // P21: PROBE_GREP=regex [PROBE_TAIL=n] selects which page console lines to print (default: audio lines)
  const grep = JSON.stringify(process.env.PROBE_GREP || '\\[aud|\\[audtest|\\[voicetest|fail');
  const tail = +(process.env.PROBE_TAIL || 8);
  const lines = await ev(`Array.from(document.querySelectorAll('#console *')).map(e => e.textContent).filter(l => new RegExp(${grep}).test(l)).slice(-${tail}).join('\\n')`);
  if (lines) console.log(lines);
  console.log(`evaluate: slowest answer ${maxLat} ms`);
  if (process.env.PROBE_NOAUDIO) return done(0);  // P27: input / save / screenshot runs
  const ok = last && last.frames > 0 && last.nonzero > 1000 && last.sq / last.nonzero > 1e-5;
  console.log(ok ? `[audprobe] PASS: Web Audio pulled ${last.frames} frames, ${last.nonzero} non-zero samples`
                 : '[audprobe] FAIL: no audible samples reached the Web Audio graph');
  done(ok ? 0 : 1);
})();
