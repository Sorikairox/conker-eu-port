// P375 offline play test (headless Chrome over CDP, node >= 22, no packages). Called by offline_test.sh.
//   node offline_test.js BASE_URL ROM_PATH OUTDIR [update]
// BASE_URL = the page's folder (http://localhost:PORT/app/ or https://conker-web-port.netlify.app/).
// Android phone emulation (412x915, DPR 3, touch, mobile UA), muted. Steps:
//  1 load the page online; wait until the worker controls it and its cache holds every precached file
//  2 pick the ROM through the page's own file input (DOM.setFileInputFiles: the real picker path, stored in IndexedDB)
//  3 network off: Network.emulateNetworkConditions offline on the page and on every service worker target (+ $OFFLINE_CMD,
//    e.g. stop the local server); prove it (a file that is not cached must fail)
//  4 reload: page + ROM picker / Press Start must load and see the stored ROM
//  5 load ?app=game&warp=29: the stored ROM boots into the game (frames advance), touch controls laid out
//  6 (update) network on ($ONLINE_CMD), $UPDATE_CMD makes build B, reg.update() while the game runs: the notice shows;
//    its Reload button: the page runs build B and only B's cache is left
//  6b (update) on the start page, $UPDATE_CMD makes build C, reg.update(): the notice shows, the page is not reloaded;
//    its Reload button: build C runs
//  7 (update) the option off: no worker, no cache, the ROM kept
const { spawn, execSync } = require('child_process');
const fs = require('fs'), os = require('os'), path = require('path');
const [base, romPath, out, mode] = process.argv.slice(2);
fs.mkdirSync(out, { recursive: true });
const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'offtest-'));
const port = 9300 + (process.pid % 500);
const ch = spawn(CH, ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, '--use-angle=metal', '--mute-audio',
  '--autoplay-policy=no-user-gesture-required', 'about:blank'], { stdio: 'ignore' });
const logf = path.join(out, 'chrome.log'); fs.writeFileSync(logf, '');
let fails = 0;
const done = (code) => { try { ch.kill('SIGKILL'); } catch (e) {} fs.rmSync(dir, { recursive: true, force: true }); process.exit(code); };
setTimeout(() => { console.log('offline_test: timeout'); done(2); }, 300000);
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
const check = (name, ok, detail) => { console.log(`${ok ? 'PASS' : 'FAIL'} ${name}${detail ? ': ' + detail : ''}`); if (!ok) fails++; };
(async () => {
  let page;
  for (let i = 0; i < 50 && !page; i++) { await sleep(300); try { page = (await (await fetch(`http://127.0.0.1:${port}/json`)).json()).find((t) => t.type === 'page'); } catch (e) {} }
  const bws = (await (await fetch(`http://127.0.0.1:${port}/json/version`)).json()).webSocketDebuggerUrl;
  const ws = new WebSocket(bws);
  await new Promise((r) => ws.addEventListener('open', r));
  let id = 0; const pending = new Map(); const swSessions = new Set(); let offline = false;
  const send = (method, params = {}, sessionId) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params, ...(sessionId ? { sessionId } : {}) })); });
  const net = (sid) => send('Network.enable', {}, sid).then(() => send('Network.emulateNetworkConditions', { offline, latency: 0, downloadThroughput: -1, uploadThroughput: -1 }, sid));
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Target.attachedToTarget' && d.params.targetInfo.type === 'service_worker') {
      swSessions.add(d.params.sessionId); net(d.params.sessionId); send('Runtime.runIfWaitingForDebugger', {}, d.params.sessionId);
    }
    if (d.method === 'Runtime.consoleAPICalled') fs.appendFileSync(logf, d.params.args.map((a) => a.value ?? a.description ?? '').join(' ') + '\n');
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const { result: { sessionId: ps } } = await send('Target.attachToTarget', { targetId: page.id, flatten: true });
  const call = (method, params) => send(method, params, ps);
  await send('Target.setDiscoverTargets', { discover: true });
  await send('Target.setAutoAttach', { autoAttach: true, waitForDebuggerOnStart: false, flatten: true });
  // service workers are not children of the page: attach to each one the browser reports
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Target.targetCreated' && d.params.targetInfo.type === 'service_worker') send('Target.attachToTarget', { targetId: d.params.targetInfo.targetId, flatten: true });
  });
  const ev = async (expr) => { const r = await call('Runtime.evaluate', { expression: expr, returnByValue: true, awaitPromise: true }); return r.result?.result?.value ?? r.result?.exceptionDetails?.exception?.description; };
  const shot = async (name) => { const r = await call('Page.captureScreenshot', { format: 'png' }); if (r.result) fs.writeFileSync(path.join(out, name + '.png'), Buffer.from(r.result.data, 'base64')); };
  const nav = async (q) => { await call('Page.navigate', { url: base + 'index.html' + q }); await sleep(2500); };
  const cacheState = `(async () => { const k = (await caches.keys()).filter((n) => n.startsWith('conker-offline-')); let n = 0; for (const x of k) n += (await (await caches.open(x)).keys()).length;
    const r = await navigator.serviceWorker.getRegistration(); return JSON.stringify({ caches: k, entries: n, controlled: !!navigator.serviceWorker.controller, waiting: !!(r && r.waiting) }); })()`;
  await call('Runtime.enable'); await call('Page.enable'); await call('DOM.enable'); await net(ps);
  await call('Emulation.setDeviceMetricsOverride', { width: 412, height: 915, deviceScaleFactor: 3, mobile: true, screenWidth: 412, screenHeight: 915, screenOrientation: { type: 'portraitPrimary', angle: 0 } });
  await call('Emulation.setTouchEmulationEnabled', { enabled: true, maxTouchPoints: 5 });
  await call('Emulation.setUserAgentOverride', { userAgent: 'Mozilla/5.0 (Linux; Android 14; Pixel 8) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Mobile Safari/537.36', platform: 'Linux armv8l' });

  // 1
  await nav('?mute=1');
  let st;
  for (let i = 0; i < 60; i++) { st = JSON.parse(await ev(cacheState)); if (st.entries >= 12 && st.controlled) break; await sleep(1000); }
  check('1 worker controls the page, cache complete', st.entries >= 12 && st.controlled, JSON.stringify(st));
  const cacheA = st.caches[0];
  check('1 manifest linked', (await ev("document.querySelector('link[rel=manifest]').href")).endsWith('manifest.webmanifest'));
  // 2
  const doc = await call('DOM.getDocument', { depth: 0 });
  const inp = await call('DOM.querySelector', { nodeId: doc.result.root.nodeId, selector: '#rom' });
  await call('DOM.setFileInputFiles', { nodeId: inp.result.nodeId, files: [romPath] });
  let romStored = false;
  for (let i = 0; i < 40 && !romStored; i++) { await sleep(1000); romStored = await ev("idb('rom', 'readonly', (s) => s.get('eu')).then((v) => !!v && romOk)"); }
  check('2 ROM picked and stored in IndexedDB', romStored === true);
  // 3
  offline = true;
  await net(ps); for (const s of swSessions) await net(s);
  if (process.env.OFFLINE_CMD) execSync(process.env.OFFLINE_CMD, { stdio: 'inherit' });
  const probe = await ev("fetch('BUILD.txt?probe=' + Date.now(), { cache: 'no-store' }).then((r) => 'reached ' + r.status, (e) => 'failed')");
  check('3 network is off (an uncached file fails)', probe === 'failed', `${probe}, worker sessions ${swSessions.size}`);
  // 4
  await nav('?mute=1'); await sleep(2500);
  const p4 = JSON.parse(await ev("JSON.stringify({ title: document.title, picker: !!document.getElementById('rom'), ready: !document.getElementById('ready').hidden, romOk, status: document.getElementById('status').textContent, controlled: !!navigator.serviceWorker.controller })"));
  check('4 offline reload: page, ROM picker and stored ROM', p4.picker && p4.romOk && p4.ready && p4.controlled, JSON.stringify(p4));
  await shot('a_offline_ready');
  // 5
  await nav('?mute=1&app=game&det=2&p103boot=1&warp=29');
  await sleep(25000);
  const p5 = JSON.parse(await ev(`JSON.stringify({ running, frames: (document.getElementById('console').textContent.match(/frame [0-9]+/g) || []).slice(-1)[0] || null,
    aborted: /Aborted|RuntimeError/.test(document.getElementById('console').textContent), touch: document.body.classList.contains('touch'),
    touchShown: getComputedStyle(document.getElementById('touch')).display !== 'none', aW: document.getElementById('tk-A').getBoundingClientRect().width,
    stickW: (document.getElementById('tk-stick') || document.querySelector('#touch .zone') || { getBoundingClientRect: () => ({ width: -1 }) }).getBoundingClientRect().width })`));
  check('5 offline boot of the stored ROM into the game', p5.running === 'game' && !!p5.frames && !p5.aborted, JSON.stringify(p5));
  check('5 touch controls laid out (phone emulation)', p5.touch && p5.touchShown && p5.aW > 0, `A width ${p5.aW}`);
  await shot('b_offline_game_touch');
  const offLog = fs.readFileSync(logf, 'utf8').split('\n').filter((l) => l.startsWith('[offline]'));
  console.log('page [offline] lines: ' + offLog.slice(-4).join(' | '));
  // 6
  if (mode === 'update') {
    offline = false; await net(ps); for (const s of swSessions) await net(s);
    if (process.env.ONLINE_CMD) execSync(process.env.ONLINE_CMD, { stdio: 'inherit' });
    execSync(process.env.UPDATE_CMD, { stdio: 'inherit' });
    await ev('navigator.serviceWorker.getRegistration().then((r) => r.update())');
    let shown = false;
    for (let i = 0; i < 40 && !shown; i++) { await sleep(1000); shown = await ev("!document.getElementById('offline-update').hidden"); }
    check('6 update B found while the game runs: notice shown', shown === true);
    await shot('c_update_notice');
    await ev("document.getElementById('offline-reload').click()");
    for (let i = 0; i < 30; i++) { await sleep(1000); st = JSON.parse(await ev(cacheState)); if (st.caches.length === 1 && st.caches[0] !== cacheA && st.controlled) break; }
    const marker = await ev("fetch('index.html').then((r) => r.text()).then((t) => t.includes('offline-test-build-B'))");
    check('6 after Reload: build B runs, A cache deleted', st.caches.length === 1 && st.caches[0] !== cacheA && st.controlled && marker === true, `A ${cacheA} -> ${JSON.stringify(st)}, B page ${marker}`);
  }
  // 6b (update) build C found on the start page (the game not started): the notice shows and the page is not reloaded
  //    by itself (it used to reload at once, in the middle of the player's ROM pick or menu clicks)
  if (mode === 'update') {
    await nav('?mute=1');
    await sleep(3000);
    const cacheB = JSON.parse(await ev(cacheState)).caches[0];
    await ev('window.offlineTestSamePage = 1');
    execSync(process.env.UPDATE_CMD, { stdio: 'inherit' });
    let shown = false;
    for (let i = 0; i < 40 && !shown; i++) {   // one check right after the load found nothing in the test: check again every 5 s
      if (i % 5 === 0) await ev('navigator.serviceWorker.getRegistration().then((r) => r.update()).then(() => 0, () => 0)');
      await sleep(1000); shown = await ev("!document.getElementById('offline-update').hidden");
    }
    const same = await ev('window.offlineTestSamePage === 1 && running === null');
    check('6b update C found before the game starts: notice shown, no automatic reload', shown === true && same === true, `notice ${shown}, same page ${same}`);
    await ev("document.getElementById('offline-reload').click()");
    for (let i = 0; i < 30; i++) { await sleep(1000); st = JSON.parse(await ev(cacheState)); if (st.caches.length === 1 && st.caches[0] !== cacheB && st.controlled) break; }
    const reloaded = await ev('window.offlineTestSamePage === undefined');
    check('6b after Reload: build C runs, B cache deleted', st.caches.length === 1 && st.caches[0] !== cacheB && st.controlled && reloaded === true, `B ${cacheB} -> ${JSON.stringify(st)}, reloaded ${reloaded}`);
  }
  // 7 the option off: worker unregistered, caches deleted (the ROM stays in IndexedDB)
  if (mode === 'update') {
    await ev("(setOption(OPTIONS.find((o) => o.key === 'offline'), false), new Promise((r) => setTimeout(r, 1500)))");
    const p7 = JSON.parse(await ev("(async () => JSON.stringify({ regs: (await navigator.serviceWorker.getRegistrations()).length, caches: (await caches.keys()).filter((n) => n.startsWith('conker-offline-')).length, rom: !!(await idb('rom', 'readonly', (s) => s.get('eu'))) }))()"));
    check('7 option off: worker unregistered, cache deleted, ROM kept', p7.regs === 0 && p7.caches === 0 && p7.rom, JSON.stringify(p7));
    await ev("setOption(OPTIONS.find((o) => o.key === 'offline'), true)");
  }
  console.log(fails ? `offline_test: ${fails} FAIL` : 'offline_test: ALL PASS');
  done(fails ? 1 : 0);
})().catch((e) => { console.log('offline_test: ' + e.stack); done(2); });
