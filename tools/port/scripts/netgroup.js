// P338 / P344: 2 to 4 online peers in ONE headless Chrome (one window each, so none is a hidden background tab),
// connected over WebRTC on this machine through the page's own Online code (window.__online in main.js: host / invite /
// join / accept / start, the same calls as the Online panel buttons; the copy-paste codes are passed by this driver).
// P344: was netpair.js (2 peers); the pages are named host, guest (player 2), guest3, guest4.
//   node tools/port/scripts/netgroup.js SECS OUTDIR URL_HOST URL_GUEST [URL_GUEST3 [URL_GUEST4]]
//   env UI=1: exchange the codes through the Online panel's buttons and text boxes; SHOTS="S1 S2": screenshots (s)
//   P339: HIDE=AT:FOR hides the guest's page at AT s for FOR s (window minimised; if the page still reports visible,
//   another tab is opened in front of it, as when the player switches tabs); REALBG=1 runs Chrome without the
//   --disable-background* switches, so hidden-page timer throttling is as in a normal Chrome
//   LEAVE=NAME (GUEST_LEAVE=1 = guest): that page leaves at the end, the others run on for 15 s
//   P345: ROOM=1 connects through a room code instead (host __online.roomCreate, guests __online.roomJoin in order; with
//   UI=1 through the panel's Create room / code field / Join room); the pages' ?roomapi names the room server.
//   ROMFILE=PATH gives each page the ROM through its file picker (for pages without ?romurl, e.g. the public site).
//   ROOMCHECK=1 (with ROOM=1) also tries an unknown code and, after everyone joined, one more player (ROOMMAX=N: the room
//   is made for N players, so with N = the page count it is full); prints the errors.
// Logs: OUTDIR/NAME.log (the page console). Prints a summary of the [net] lines.
const { spawn } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [secs = '60', out = '.', ...urls] = process.argv.slice(2);
const NAMES = ['host', 'guest', 'guest3', 'guest4'].slice(0, urls.length);
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'netgroup-'));
const port = 9300 + (process.pid % 500);
const bgSwitches = process.env.REALBG ? [] : ['--disable-background-timer-throttling', '--disable-renderer-backgrounding', '--disable-backgrounding-occluded-windows'];
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, '--use-angle=metal',
  '--mute-audio', '--autoplay-policy=no-user-gesture-required', '--window-size=1500,900',
  ...bgSwitches, 'about:blank'], { stdio: 'ignore' });
const done = (code) => { try { ch.kill('SIGKILL'); } catch (e) {} fs.rmSync(dir, { recursive: true, force: true }); process.exit(code); };
setTimeout(() => { console.log('netgroup: timeout'); done(2); }, (+secs + 240) * 1000);
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
  if (!ver) { console.log('netgroup: no DevTools'); return done(2); }
  const br = await connect(ver.webSocketDebuggerUrl);
  const pages = {}, targetIds = {};
  for (let i = 0; i < urls.length; i++) {
    const name = NAMES[i];
    fs.writeFileSync(path.join(out, name + '.log'), '');
    const t = await br.call('Target.createTarget', { url: 'about:blank', newWindow: true, width: 1500, height: 900 });
    const list = await (await fetch(`http://127.0.0.1:${port}/json`)).json();
    const pg = list.find((x) => x.id === t.result.targetId);
    targetIds[name] = t.result.targetId;
    pages[name] = await connect(pg.webSocketDebuggerUrl, path.join(out, name + '.log'));
    await pages[name].call('Runtime.enable', {});
    await pages[name].call('Page.navigate', { url: urls[i] });
  }
  if (process.env.ROMFILE) for (const n of NAMES) {   // P345: the ROM through the page's file picker (stays on this machine)
    for (let i = 0; i < 100; i++) { if (await pages[n].ev("!!document.getElementById('rom') && document.readyState === 'complete'").catch(() => false)) break; await sleep(300); }
    await pages[n].call('DOM.enable', {});
    const doc = await pages[n].call('DOM.getDocument', {});
    const q = await pages[n].call('DOM.querySelector', { nodeId: doc.result.root.nodeId, selector: '#rom' });
    await pages[n].call('DOM.setFileInputFiles', { nodeId: q.result.nodeId, files: [path.resolve(process.env.ROMFILE)] });
  }
  const host = pages.host, guests = NAMES.slice(1);
  const ready = async (p) => { for (let i = 0; i < 100; i++) { if (await p.ev('!!(window.__online && window.__online.ready())').catch(() => false)) return true; await sleep(300); } return false; };
  for (const n of NAMES) if (!(await ready(pages[n]))) { console.log(`netgroup: page ${n} not ready (ROM / net.js)`); return done(2); }
  const t0 = Date.now();
  const waitVal = async (p, id) => { for (let i = 0; i < 100; i++) { const v = await p.ev(`(document.getElementById('${id}') || {}).value`); if (v) return v; await sleep(200); } throw new Error('no code in #' + id); };
  const sizes = [];
  const evErr = (p, expr) => p.ev(`(${expr}).then(() => 'no error', (e) => 'error: ' + e.message)`);
  if (process.env.ROOM && process.env.ROOMCHECK) console.log(`netgroup: unknown code -> ${await evErr(pages[guests[0]], "__online.roomJoin('QQQQQ')")}`);
  if (process.env.ROOM) {   // P345: room code
    let code;
    if (process.env.UI) {
      for (const n of NAMES) await pages[n].ev("document.getElementById('t-online').click()");
      await host.ev("document.getElementById('net-room-create').click()");
      for (let i = 0; i < 100 && !code; i++) { code = await host.ev("document.getElementById('net-room-show').textContent"); if (!code) await sleep(200); }
    } else code = await host.ev(`__online.roomCreate(${+process.env.ROOMMAX || 4})`);
    console.log(`netgroup: room ${code} (${Date.now() - t0} ms)`);
    for (const g of guests) {
      const tj = Date.now();
      if (process.env.UI) {
        await pages[g].ev(`document.getElementById('net-room-code').value = ${JSON.stringify(code.toLowerCase())}; document.getElementById('net-room-join').click()`);
        for (let i = 0; i < 150; i++) { if (await pages[g].ev("/^(you are player|connected)/.test(document.getElementById('net-status').textContent)")) break; await sleep(200); }
      } else await pages[g].ev(`__online.roomJoin(${JSON.stringify(code)})`);
      console.log(`netgroup: ${g} joined room ${code} as ${JSON.stringify(await pages[g].ev('__online.room()'))} in ${Date.now() - tj} ms; status: ${await pages[g].ev("document.getElementById('net-status').textContent")}`);
    }
  } else if (process.env.UI) {   // through the Online panel: click the buttons, copy the textareas
    for (const n of NAMES) await pages[n].ev("document.getElementById('t-online').click()");
    for (let k = 0; k < guests.length; k++) {
      const slot = k + 2, g = pages[guests[k]];
      await host.ev(`document.getElementById('${k ? 'net-invite' : 'net-host'}').click()`);
      const offer = await waitVal(host, 'net-offer-' + slot);
      await g.ev(`document.getElementById('net-join').click(); document.getElementById('net-offer-in').value = ${JSON.stringify(offer)}; document.getElementById('net-answer-make').click()`);
      const answer = await waitVal(g, 'net-answer');
      await host.ev(`document.getElementById('net-answer-in-${slot}').value = ${JSON.stringify(answer)}; document.getElementById('net-accept-${slot}').click()`);
      sizes.push(offer.length, answer.length);
    }
  } else {
    for (let k = 0; k < guests.length; k++) {
      const offer = k ? (await host.ev('__online.invite()')).code : await host.ev('__online.host()');
      const answer = await pages[guests[k]].ev(`__online.join(${JSON.stringify(offer)})`);
      await host.ev(`__online.accept(${JSON.stringify(answer)})`);
      sizes.push(offer.length, answer.length);
    }
  }
  // all guests joined (hello checked by the host), then the host starts: mesh, pings, config
  let slots = [];
  for (let i = 0; i < 150; i++) { slots = await host.ev('__online.slots()'); if (slots.filter((s) => s.state === 'joined').length === guests.length) break; await sleep(200); }
  if (process.env.ROOM && process.env.ROOMCHECK) {   // one more page tries to join (with ROOMMAX = the player count the room is full)
    const code = await host.ev('__online.room().code');
    const t = await br.call('Target.createTarget', { url: 'about:blank', newWindow: true });
    const pg = (await (await fetch(`http://127.0.0.1:${port}/json`)).json()).find((x) => x.id === t.result.targetId);
    const extra = await connect(pg.webSocketDebuggerUrl, path.join(out, 'extra.log'));
    await extra.call('Runtime.enable', {}); await extra.call('Page.navigate', { url: urls[1] });
    if (process.env.ROMFILE) { await sleep(3000); await extra.call('DOM.enable', {}); const doc = await extra.call('DOM.getDocument', {});
      const q = await extra.call('DOM.querySelector', { nodeId: doc.result.root.nodeId, selector: '#rom' });
      await extra.call('DOM.setFileInputFiles', { nodeId: q.result.nodeId, files: [path.resolve(process.env.ROMFILE)] }); }
    if (await ready(extra)) console.log(`netgroup: one more player (player ${NAMES.length + 1}) joins room ${code} -> ${await evErr(extra, `__online.roomJoin(${JSON.stringify(code)})`)}`);
    await br.call('Target.closeTarget', { targetId: t.result.targetId });
  }
  console.log(`netgroup: ${NAMES.length} players, codes ${sizes.join('/')} chars, all joined in ${Date.now() - t0} ms: ${JSON.stringify(slots)}`);
  const ts = Date.now();
  if (process.env.UI) { await host.ev("document.getElementById('net-start').click()"); }
  else await host.ev('__online.start()');
  console.log(`netgroup: started (${Date.now() - ts} ms), routes ${JSON.stringify(await host.ev('PortNet.t.routes'))}; visibility ` +
    (await Promise.all(NAMES.map((n) => pages[n].ev('document.visibilityState')))).join(' '));
  const [hideAt, hideFor] = (process.env.HIDE || '').split(':').map(Number);
  let hideState = 0, coverId = null, winId = null;
  const guest = pages.guest;
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
    console.log(`netgroup ${Math.round((Date.now() - t1) / 1000)} s: guest page ${on ? 'hidden' : 'shown again'}` +
      `${on && coverId ? ' (a tab in front of it)' : ''}, visibilityState ${await guest.ev('document.visibilityState')}, frame ${await guest.ev('__online.stats().frame')}`);
  };
  const t1 = Date.now(), speed = [];   // [seconds, stats per page] every 10 s
  while (Date.now() - t1 < +secs * 1000) {
    await sleep(10000);
    const s = await Promise.all(NAMES.map((n) => pages[n].ev('__online.stats()'))).catch((e) => NAMES.map(() => null));
    const el = (Date.now() - t1) / 1000;
    if (hideAt && hideState === 0 && el >= hideAt) { hideState = 1; await hideGuest(true); }
    else if (hideAt && hideState === 1 && el >= hideAt + hideFor) { hideState = 2; await hideGuest(false); }
    if (s.every((x) => x && x.frame)) speed.push([el, s]);
    console.log(`netgroup ${Math.round(el)} s: ` + NAMES.map((n, i) => `${n} ${JSON.stringify(s[i])}`).join('  '));
    for (const t of (process.env.SHOTS || '').split(' ').filter(Boolean))   // SHOTS="60 120": screenshots of every window
      if (Math.abs(el - +t) < 5) for (const n of NAMES) {
        await pages[n].ev("document.getElementById('p-online').scrollIntoView()").catch(() => {});
        const r = await pages[n].call('Page.captureScreenshot', { format: 'png' });
        if (r.result) fs.writeFileSync(path.join(out, `${n}_${t}s.png`), Buffer.from(r.result.data, 'base64'));
      }
  }
  // P339: game speed = retraces per second / 50 from the first sample with the game running (>= 20 s) to the end
  const a = speed.find((x) => x[0] >= 20 && x[1][0].frame > 100), z = speed[speed.length - 1];
  if (a && z && z !== a) console.log(`netgroup speed ${a[0].toFixed(0)}..${z[0].toFixed(0)} s: ` + NAMES.map((n, i) =>
    `${n} ${((z[1][i].frame - a[1][i].frame) / (z[0] - a[0]) / 50 * 100).toFixed(1)} % (${z[1][i].waits - a[1][i].waits} waits, ${z[1][i].waitMs - a[1][i].waitMs} ms)`).join(', '));
  // optional: LEAVE=NAME (or GUEST_LEAVE=1: guest) closes that page's session at the end; the others run on for 15 s
  const leave = process.env.LEAVE || (process.env.GUEST_LEAVE ? 'guest' : '');
  if (leave && pages[leave]) {
    await pages[leave].ev('__online.leave()');
    await sleep(15000);
    for (const n of NAMES) if (n !== leave) console.log(`netgroup after ${leave} left: ${n} ` + JSON.stringify(await pages[n].ev('__online.stats()')));
  }
  done(0);
})().catch((e) => { console.log('netgroup: ' + e); done(3); });
