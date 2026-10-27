// P338: two online peers in ONE headless Chrome (two windows, so neither is a hidden background tab), connected over
// WebRTC on this machine through the page's own Online code (window.__online in main.js: host / join / accept, the
// same calls as the Online panel buttons; the copy-paste codes are passed by this driver).
//   node tools/port/scripts/netpair.js URL_HOST URL_GUEST SECS OUTDIR
//   env UI=1: exchange the codes through the Online panel's buttons and text boxes; SHOTS="S1 S2": screenshots (s)
//   P339: HIDE=AT:FOR hides the guest's page at AT s for FOR s (window minimised; if the page still reports visible,
//   another tab is opened in front of it, as when the player switches tabs); REALBG=1 runs Chrome without the
//   --disable-background* switches, so hidden-page timer throttling is as in a normal Chrome
// Logs: OUTDIR/host.log, OUTDIR/guest.log (the page console). Prints a summary of the [net] lines.
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [urlHost, urlGuest, secs = '60', out = '.'] = process.argv.slice(2);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'netpair-'));
const port = 9300 + (process.pid % 500);
const bgSwitches = process.env.REALBG ? [] : ['--disable-background-timer-throttling', '--disable-renderer-backgrounding', '--disable-backgrounding-occluded-windows'];
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, '--use-angle=metal',
  '--mute-audio', '--autoplay-policy=no-user-gesture-required', '--window-size=1500,900',
  ...bgSwitches, 'about:blank'], { stdio: 'ignore' });
const done = (code) => { try { ch.kill('SIGKILL'); } catch (e) {} fs.rmSync(dir, { recursive: true, force: true }); process.exit(code); };
setTimeout(() => { console.log('netpair: timeout'); done(2); }, (+secs + 180) * 1000);
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
async function connect(wsUrl, logFile) {
  const ws = new WebSocket(wsUrl);
  await new Promise((r) => ws.addEventListener('open', r));
  let id = 0; const pending = new Map();
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Runtime.consoleAPICalled' && logFile)
      fs.appendFileSync(logFile, d.params.args.map((a) => a.value ?? a.description ?? '').join(' ') + '\n');
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const call = (method, params) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  const ev = async (expr) => {
    const r = await call('Runtime.evaluate', { expression: expr, returnByValue: true, awaitPromise: true });
    if (r.result?.exceptionDetails) throw new Error(expr + ': ' + JSON.stringify(r.result.exceptionDetails).slice(0, 400));
    return r.result?.result?.value;
  };
  return { call, ev };
}
(async () => {
  let ver;
  for (let i = 0; i < 50 && !ver; i++) { await sleep(300); try { ver = await (await fetch(`http://127.0.0.1:${port}/json/version`)).json(); } catch (e) {} }
  if (!ver) { console.log('netpair: no DevTools'); return done(2); }
  const br = await connect(ver.webSocketDebuggerUrl);
  const pages = {}, targetIds = {};
  for (const [name, url] of [['host', urlHost], ['guest', urlGuest]]) {
    fs.writeFileSync(path.join(out, name + '.log'), '');
    const t = await br.call('Target.createTarget', { url: 'about:blank', newWindow: true, width: 1500, height: 900 });
    const list = await (await fetch(`http://127.0.0.1:${port}/json`)).json();
    const pg = list.find((x) => x.id === t.result.targetId);
    targetIds[name] = t.result.targetId;
    pages[name] = await connect(pg.webSocketDebuggerUrl, path.join(out, name + '.log'));
    await pages[name].call('Runtime.enable', {});
    await pages[name].call('Page.navigate', { url });
  }
  const { host, guest } = pages;
  const ready = async (p) => { for (let i = 0; i < 100; i++) { if (await p.ev('!!(window.__online && window.__online.ready())').catch(() => false)) return true; await sleep(300); } return false; };
  if (!(await ready(host)) || !(await ready(guest))) { console.log('netpair: pages not ready (ROM / net.js)'); return done(2); }
  const t0 = Date.now();
  let offer, answer;
  const waitVal = async (p, id) => { for (let i = 0; i < 100; i++) { const v = await p.ev(`document.getElementById('${id}').value`); if (v) return v; await sleep(200); } throw new Error('no code in #' + id); };
  if (process.env.UI) {   // through the Online panel: click the buttons, copy the textareas
    for (const p of [host, guest]) await p.ev("document.getElementById('t-online').click()");
    await host.ev("document.getElementById('net-host').click()");
    offer = await waitVal(host, 'net-offer');
    await guest.ev(`document.getElementById('net-join').click(); document.getElementById('net-offer-in').value = ${JSON.stringify(offer)}; document.getElementById('net-answer-make').click()`);
    answer = await waitVal(guest, 'net-answer');
    await host.ev(`document.getElementById('net-answer-in').value = ${JSON.stringify(answer)}; document.getElementById('net-accept').click()`);
  } else {
    offer = await host.ev('__online.host()');
    answer = await guest.ev(`__online.join(${JSON.stringify(offer)})`);
    await host.ev(`__online.accept(${JSON.stringify(answer)})`);
  }
  console.log(`netpair: page visibility host ${await host.ev('document.visibilityState')} guest ${await guest.ev('document.visibilityState')}`);
  console.log(`netpair: offer ${offer.length} chars, answer ${answer.length} chars, codes exchanged in ${Date.now() - t0} ms`);
  const [hideAt, hideFor] = (process.env.HIDE || '').split(':').map(Number);
  let hideState = 0, coverId = null, winId = null;
  const hideGuest = async (on) => {   // P339: minimise the guest's window (or cover its tab), then restore
    if (!winId) winId = (await br.call('Browser.getWindowForTarget', { targetId: targetIds.guest })).result?.windowId;
    if (on) {
      await br.call('Browser.setWindowBounds', { windowId: winId, bounds: { windowState: 'minimized' } });
      await sleep(500);
      if (await guest.ev('document.visibilityState') !== 'hidden') {
        coverId = (await br.call('Target.createTarget', { url: 'about:blank', windowId: winId })).result?.targetId;
        if (coverId) await br.call('Target.activateTarget', { targetId: coverId });
        await sleep(500);
      }
    } else {
      if (coverId) { await br.call('Target.closeTarget', { targetId: coverId }); coverId = null; }
      await br.call('Browser.setWindowBounds', { windowId: winId, bounds: { windowState: 'normal' } });
      await br.call('Target.activateTarget', { targetId: targetIds.guest });
      await sleep(500);
    }
    console.log(`netpair ${Math.round((Date.now() - t1) / 1000)} s: guest page ${on ? 'hidden' : 'shown again'}` +
      `${on && coverId ? ' (a tab in front of it)' : ''}, visibilityState ${await guest.ev('document.visibilityState')}, frame ${await guest.ev('__online.stats().frame')}`);
  };
  const t1 = Date.now(), speed = [];   // P339: [seconds, host / guest frame, host / guest retraces that waited, host / guest ms waited] every 10 s
  while (Date.now() - t1 < +secs * 1000) {
    await sleep(10000);
    const s = await Promise.all([host.ev('__online.stats()'), guest.ev('__online.stats()')]).catch((e) => [String(e), '']);
    const el = (Date.now() - t1) / 1000;
    if (hideAt && hideState === 0 && el >= hideAt) { hideState = 1; await hideGuest(true); }
    else if (hideAt && hideState === 1 && el >= hideAt + hideFor) { hideState = 2; await hideGuest(false); }
    if (s[0] && s[1] && s[0].frame) speed.push([(Date.now() - t1) / 1000, s[0].frame, s[1].frame, s[0].waits, s[1].waits, s[0].waitMs, s[1].waitMs]);
    console.log(`netpair ${Math.round((Date.now() - t1) / 1000)} s: host ${JSON.stringify(s[0])}  guest ${JSON.stringify(s[1])}`);
    for (const t of (process.env.SHOTS || '').split(' ').filter(Boolean))   // SHOTS="60 120": screenshots of both windows
      if (Math.abs((Date.now() - t1) / 1000 - +t) < 5) for (const [n, p] of [['host', host], ['guest', guest]]) {
        await p.ev("document.getElementById('p-online').scrollIntoView()").catch(() => {});
        const r = await p.call('Page.captureScreenshot', { format: 'png' });
        if (r.result) fs.writeFileSync(path.join(out, `${n}_${t}s.png`), Buffer.from(r.result.data, 'base64'));
      }
  }
  // P339: game speed = retraces per second / 50 from the first sample with the game running (>= 20 s) to the end
  const a = speed.find((x) => x[0] >= 20 && x[1] > 100), z = speed[speed.length - 1];
  if (a && z && z !== a) console.log(`netpair speed ${a[0].toFixed(0)}..${z[0].toFixed(0)} s: host ${((z[1] - a[1]) / (z[0] - a[0]) / 50 * 100).toFixed(1)} %` +
    ` guest ${((z[2] - a[2]) / (z[0] - a[0]) / 50 * 100).toFixed(1)} %, retraces that waited for input host ${z[3] - a[3]} (${z[5] - a[5]} ms) guest ${z[4] - a[4]} (${z[6] - a[6]} ms)`);
  // optional: GUEST_LEAVE=1 closes the guest at the end and lets the host run on alone for 15 s
  if (process.env.GUEST_LEAVE) {
    await guest.ev('__online.leave()');
    await sleep(15000);
    console.log('netpair after the guest left: host ' + JSON.stringify(await host.ev('__online.stats()')));
  }
  done(0);
})().catch((e) => { console.log('netpair: ' + e); done(3); });
