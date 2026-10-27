// P338: two online peers in ONE headless Chrome (two windows, so neither is a hidden background tab), connected over
// WebRTC on this machine through the page's own Online code (window.__online in main.js: host / join / accept, the
// same calls as the Online panel buttons; the copy-paste codes are passed by this driver).
//   node tools/port/scripts/netpair.js URL_HOST URL_GUEST SECS OUTDIR
// Logs: OUTDIR/host.log, OUTDIR/guest.log (the page console). Prints a summary of the [net] lines.
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [urlHost, urlGuest, secs = '60', out = '.'] = process.argv.slice(2);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'netpair-'));
const port = 9300 + (process.pid % 500);
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, '--use-angle=metal',
  '--mute-audio', '--autoplay-policy=no-user-gesture-required', '--window-size=900,800',
  '--disable-background-timer-throttling', '--disable-renderer-backgrounding', '--disable-backgrounding-occluded-windows',
  'about:blank'], { stdio: 'ignore' });
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
  const pages = {};
  for (const [name, url] of [['host', urlHost], ['guest', urlGuest]]) {
    fs.writeFileSync(path.join(out, name + '.log'), '');
    const t = await br.call('Target.createTarget', { url: 'about:blank', newWindow: true });
    const list = await (await fetch(`http://127.0.0.1:${port}/json`)).json();
    const pg = list.find((x) => x.id === t.result.targetId);
    pages[name] = await connect(pg.webSocketDebuggerUrl, path.join(out, name + '.log'));
    await pages[name].call('Runtime.enable', {});
    await pages[name].call('Page.navigate', { url });
  }
  const { host, guest } = pages;
  const ready = async (p) => { for (let i = 0; i < 100; i++) { if (await p.ev('!!(window.__online && window.__online.ready())').catch(() => false)) return true; await sleep(300); } return false; };
  if (!(await ready(host)) || !(await ready(guest))) { console.log('netpair: pages not ready (ROM / net.js)'); return done(2); }
  const t0 = Date.now();
  const offer = await host.ev('__online.host()');
  const answer = await guest.ev(`__online.join(${JSON.stringify(offer)})`);
  await host.ev(`__online.accept(${JSON.stringify(answer)})`);
  console.log(`netpair: offer ${offer.length} chars, answer ${answer.length} chars, codes exchanged in ${Date.now() - t0} ms`);
  const t1 = Date.now();
  while (Date.now() - t1 < +secs * 1000) {
    await sleep(10000);
    const s = await Promise.all([host.ev('__online.stats()'), guest.ev('__online.stats()')]).catch((e) => [String(e), '']);
    console.log(`netpair ${Math.round((Date.now() - t1) / 1000)} s: host ${JSON.stringify(s[0])}  guest ${JSON.stringify(s[1])}`);
  }
  // optional: GUEST_LEAVE=1 closes the guest at the end and lets the host run on alone for 15 s
  if (process.env.GUEST_LEAVE) {
    await guest.ev('__online.leave()');
    await sleep(15000);
    console.log('netpair after the guest left: host ' + JSON.stringify(await host.ev('__online.stats()')));
  }
  done(0);
})().catch((e) => { console.log('netpair: ' + e); done(3); });
