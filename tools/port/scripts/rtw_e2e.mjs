// P376 end-to-end driver of the retrowser.app build (tools/eu_port/build_rtw.sh output) in the real retrowser host.
//   node tools/port/scripts/rtw_e2e.mjs OUTDIR HOST_URL ROM 'ACTION,ACTION,...'
// HOST_URL: a running retrowser host on localhost (`npm run dev` in ~/Code/retrowser = http://localhost:5173, or its
// Worker handler on dist, tools/serve-worker.ts). The game repo is served by retrowser's own GitHub mock
// (tools/mock-github.ts) from port/build/rtw/dist as sorikairox/conker-eu-port. One muted headless Chrome
// (--use-angle=metal), started and killed here; the ROM is only handed to the host's file input (never copied).
// Env: RETROWSER_DIR (default ~/Code/retrowser), RTW_OPTIONS='{"16":1,...}' (stored game options),
// RTW_PROFILE (a Chrome user-data dir kept between runs: saves, stored ROM and the host's offline cache survive).
// Actions:
//   open                 game page -> Download -> ROM (file input, or the stored ROM) -> wait until frames run
//   frame:N              wait until the game ran N retraces (port_net_frame in the worker)
//   wait:MS  shot:NAME   sleep / screenshot OUTDIR/NAME.png
//   key:CODE:MS          hold a key (KeyboardEvent.code, the host's keymap) for MS ms; down:CODE / up:CODE
//   reload               reload the page (then `open` again)
//   files                open the menu's "Saved files", print the names, close it; fetchfile:PREFIX saves the newest such file
//   offline / online     cut / restore the network of the page, the sandbox frame and their workers (CDP)
//   stopservers          stop the GitHub mock (with offline: nothing left to fetch)
//   state                print the game state (retrace, photo mode, audio, last log lines)
//   pos                  print Conker's position (record 0 of g_objects, address from port/build/rtw/conker.map)
//   P377 overlays: ov (the overlay layer's state: menu page / row, photo panel, ring, icon, sounds, settings record),
//   opts (the option values the game uses), press:CODE[:N] (N short presses of a key, 90 ms each, 160 ms apart),
//   dismiss (the host's storage notice), hostopt:ID:V (change option ID in the host's own menu: Menu -> its checkbox / field -> Back to game),
//   expect:PATH:VALUE (a field of `ov` / `opts`, e.g. expect:menu.page:hud, expect:opts.102:1, expect:ring.progress:>0; counts a failure if not),
//   waitfor:PATH:VALUE[:MS] (the same, polled until it matches; default 20 s)
//   P378 standard 1.1: pad:AX2:AY3 (a fake standard gamepad, navigator.getGamepads in the host page, with these right
//   stick axes, -1..1, down positive; pad:off removes it), wheel:DY (the mouse over the game, one wheel event of DY px),
//   askfile:FILE|last (the host's file prompt the game opened: pick FILE / the last fetchfile), openingame:PREFIX (Saved
//   files: Open in game), click (on the picture until the host captured the mouse), unlock (document.exitPointerLock), PATH roots cam (the camera stick per pad the glue wrote, [cx0, cy0, mdx0, mdy0, cx1, ...]), photoinfo
//   ({ state, fov }) and other __rtwConker readouts (replay, optsync), hoststored (the host's stored option values,
//   localStorage) and hostmenu (the values its options menu shows: opens and closes it). RTW_OPTIONS is stored only on a
//   first load (P378), so the host's own stored values survive a reload as for a player.
// Env RTW_SERVE=PORT: serve retrowser's built dist (tools/serve-worker.ts) in this process on PORT; HOST_URL is then
// ignored (use "-"), so nothing is left running after the run.
import { mkdirSync, readFileSync, writeFileSync } from 'node:fs';
import { homedir } from 'node:os';
import { join, resolve } from 'node:path';

const [out, host, rom, actions = 'open,frame:200,state'] = process.argv.slice(2);
if (!out || !host || !rom) { console.error('usage: rtw_e2e.mjs OUTDIR HOST_URL ROM ACTIONS'); process.exit(2); }
const RTW = process.env.RETROWSER_DIR || join(homedir(), 'Code/retrowser');
const { chromium } = await import(join(RTW, 'node_modules/playwright-core/index.mjs'));
const { startMockGithub } = await import(join(RTW, 'tools/mock-github.ts'));
const DIST = process.env.RTW_DIST ? resolve(process.env.RTW_DIST) : resolve(new URL('../../../port/build/rtw/dist', import.meta.url).pathname);   // P377: RTW_DIST = another dist
const REPO = 'sorikairox/conker-eu-port', COMMIT = 'c0ffee0000000000000000000000000000000376';
mkdirSync(out, { recursive: true });
const t0 = Date.now(), say = (s) => console.log(`[${((Date.now() - t0) / 1000).toFixed(1)}s] ${s}`);

const mock = await startMockGithub({ [REPO]: { refs: { main: COMMIT }, commits: [{ sha: COMMIT, dir: DIST }] } });
let served = null, hostUrl = host;
if (process.env.RTW_SERVE) {   // P377: the host's Worker handler on its built dist, in this process
  const { serveWorker } = await import(join(RTW, 'tools/serve-worker.ts'));
  served = await serveWorker(Number(process.env.RTW_SERVE));
  hostUrl = `http://localhost:${process.env.RTW_SERVE}`;
}
const chrome = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const args = ['--mute-audio', '--use-angle=metal', '--autoplay-policy=no-user-gesture-required'];
const profile = process.env.RTW_PROFILE;
const context = profile
  ? await chromium.launchPersistentContext(profile, { executablePath: chrome, headless: true, args, viewport: { width: 1280, height: 800 }, acceptDownloads: true })
  : await (await chromium.launch({ executablePath: chrome, headless: true, args })).newContext({ viewport: { width: 1280, height: 800 }, acceptDownloads: true });
const browser = context.browser();
await context.addInitScript(([ep, opts]) => {
  // P378: a fake standard gamepad for pad:X:Y (the host polls navigator.getGamepads)
  try { window.__rtwFakePad = null; Object.defineProperty(navigator, 'getGamepads', { configurable: true, value: () => (window.__rtwFakePad ? [window.__rtwFakePad] : []) }); } catch { /* ignore */ }
  try {
    if (location.hostname !== 'localhost') return;
    localStorage.setItem('rtw:test-endpoints', ep);
    if (opts && localStorage.getItem('rtw:options:conker-eu') === null) localStorage.setItem('rtw:options:conker-eu', opts);   // P378: only on a first load (the host keeps its own after)
  } catch { /* ignore */ }
}, [JSON.stringify(mock.endpoints), process.env.RTW_OPTIONS || '']);
const page = context.pages()[0] || await context.newPage();
const pageErrors = [];
page.on('pageerror', (e) => pageErrors.push(e.message));
let mockUp = true;
const finish = async (code) => {
  try { writeFileSync(join(out, 'host_log.txt'), (await hostLog().catch(() => '')) + '\n'); } catch { /* ignore */ }
  if (pageErrors.length) say('page errors: ' + pageErrors.slice(0, 5).join(' | '));
  await context.close().catch(() => {});
  if (browser) await browser.close().catch(() => {});
  if (mockUp) await mock.close();
  if (served) await new Promise((ok) => { served.closeAllConnections?.(); served.close(ok); });
  process.exit(code);
};
const timer = setTimeout(() => { say('TIMEOUT'); finish(3); }, Number(process.env.RTW_TIMEOUT || 900000));

const hostLog = () => page.getAttribute('[data-state=playing]', 'data-log', { timeout: 2000 }).then((v) => v || '');
const gameWorker = async () => {
  for (const w of page.workers()) {
    try { if (await w.evaluate(() => typeof globalThis.__rtwConker === 'object')) return w; } catch { /* gone */ }
  }
  for (const f of page.frames()) {
    // playwright lists dedicated workers per page; frames are only searched for completeness
    void f;
  }
  return null;
};
// g_objects (26 character records, 0x32C bytes; record 0 = Conker, position floats at +0x14) in this build's link map
const OBJECTS = (() => { const m = /^([0-9a-f]+)\s+\S+\s+\S+\s+g_objects$/m.exec(readFileSync(join(DIST, '../conker.map'), 'utf8')); return m ? parseInt(m[1], 16) : 0; })();
const conkerPos = async () => {
  const w = await gameWorker();
  return w ? w.evaluate((a) => { const M = globalThis.__rtwConker.Module, d = new DataView(M.HEAPU8.buffer); return [0, 4, 8].map((k) => +d.getFloat32(a + 0x14 + k, true).toFixed(1)); }, OBJECTS) : null;
};
const gameState = async () => {
  const w = await gameWorker();
  if (!w) return null;
  return w.evaluate(() => {
    const c = globalThis.__rtwConker, M = c.Module;
    return { retrace: M._port_net_frame() >>> 0, photo: c.photoState(), rec: c.rec(), canvas: `${M.canvas.width}x${M.canvas.height}`, audioDrained: c.audioDrained(), saveGeneration: c.saveGeneration() };
  });
};
async function open() {
  await page.goto(`${hostUrl}/g/${REPO}`);
  const download = page.locator('[data-action=download]');
  const stored = page.locator('[data-action=use-stored]');
  const rompick = page.locator('[data-field=rom]');
  const playing = page.locator('[data-state=playing]');
  await Promise.race([download.waitFor({ timeout: 60000 }), playing.waitFor({ timeout: 60000 }), stored.waitFor({ timeout: 60000 }), rompick.waitFor({ timeout: 60000 })]);
  if (await download.isVisible().catch(() => false)) { say('download'); await download.click(); }
  await Promise.race([stored.waitFor({ timeout: 120000 }), rompick.waitFor({ timeout: 120000 }), playing.waitFor({ timeout: 120000 })]);
  if (await stored.isVisible().catch(() => false)) { say('use the stored ROM'); await stored.first().click(); }
  else if (await rompick.count()) { say('ROM through the file input'); await rompick.setInputFiles(rom); }
  await page.waitForFunction(() => Number(document.querySelector('[data-state=playing]')?.getAttribute('data-frames') ?? 0) > 10, null, { timeout: 120000 });
  say('playing');
  await page.click('[data-state=persist-warning] button', { timeout: 1000 }).catch(() => {});
}
let cdp = null;
async function network(offline) {
  cdp = cdp || await context.newCDPSession(page);
  // the page, then every target the browser has (the sandbox iframe, its worker, service workers)
  await cdp.send('Network.enable');
  await cdp.send('Network.emulateNetworkConditions', { offline, latency: 0, downloadThroughput: -1, uploadThroughput: -1 });
  for (const f of page.frames()) {
    if (f === page.mainFrame()) continue;
    try { const s = await context.newCDPSession(f); await s.send('Network.enable'); await s.send('Network.emulateNetworkConditions', { offline, latency: 0, downloadThroughput: -1, uploadThroughput: -1 }); } catch { /* same process */ }
  }
  context.setOffline(offline);
}

let fails = 0, lastFetched = '';
try {
  for (const a of actions.split(',').map((s) => s.trim()).filter(Boolean)) {
    const [cmd, x, y] = a.split(':');
    if (cmd === 'open') await open();
    else if (cmd === 'wait') await page.waitForTimeout(Number(x));
    else if (cmd === 'shot') { await page.screenshot({ path: join(out, `${x}.png`) }); say(`shot ${x}`); }
    else if (cmd === 'frame') {
      const want = Number(x), until = Date.now() + Number(y || 600000);
      let st = null;
      while (Date.now() < until) { st = await gameState(); if (st && st.retrace >= want) break; await page.waitForTimeout(500); }
      say(`retrace ${st ? st.retrace : '?'} (wanted ${want})`);
      if (!st || st.retrace < want) fails++;
    } else if (cmd === 'key') { await page.keyboard.down(x); await page.waitForTimeout(Number(y || 100)); await page.keyboard.up(x); }
    else if (cmd === 'down') await page.keyboard.down(x);
    else if (cmd === 'up') await page.keyboard.up(x);
    else if (cmd === 'reload') { await page.reload(); say('reloaded'); }
    else if (cmd === 'files') {
      const btn = page.locator('[data-action=files]');
      if (await btn.count()) {
        await btn.click();
        await page.waitForTimeout(500);
        const names = await page.$$eval('[data-file]', (els) => els.map((e) => e.getAttribute('data-file')));
        say('saved files: ' + JSON.stringify(names));
        await page.screenshot({ path: join(out, 'files.png') });
      } else say('saved files: none (no Files button)');
      await page.click('[data-action=close-menu]').catch(() => {});
    } else if (cmd === 'offline') { await network(true); say('network off'); }
    else if (cmd === 'online') { await network(false); say('network on'); }
    else if (cmd === 'stopservers') { await mock.close(); mockUp = false; say('GitHub mock stopped'); }
    else if (cmd === 'hostsave') {   // the host's stored EEPROM for this game id (IndexedDB 'retrowser', store 'saves')
      const r = await page.evaluate(async () => {
        const db = await new Promise((ok, no) => { const q = indexedDB.open('retrowser'); q.onsuccess = () => ok(q.result); q.onerror = () => no(q.error); });
        const keys = await new Promise((ok) => { const q = db.transaction('saves').objectStore('saves').getAllKeys(); q.onsuccess = () => ok(q.result); });
        const v = await new Promise((ok) => { const q = db.transaction('saves').objectStore('saves').get('conker-eu:eeprom'); q.onsuccess = () => ok(q.result); });
        db.close();
        const b = v && (v.bytes || v);
        let nz = 0, h = 2166136261; if (b && b.length) for (const x of b) { if (x) nz++; h = Math.imul(h ^ x, 16777619) >>> 0; }
        return { keys, size: b ? b.length : 0, nonzero: nz, fnv: h.toString(16) };
      }).catch((e) => String(e));
      say('host save ' + JSON.stringify(r));
    }
    else if (cmd === 'modsave') {   // the module's EEPROM image (rtw_save_ptr / rtw_save_size) as the game holds it now
      const w = await gameWorker();
      const r = w && await w.evaluate(() => {
        const M = globalThis.__rtwConker.Module, p = M._rtw_save_ptr() >>> 0, n = M._rtw_save_size();
        const b = M.HEAPU8.subarray(p, p + n); let nz = 0, h = 2166136261;
        for (const x of b) { if (x) nz++; h = Math.imul(h ^ x, 16777619) >>> 0; }
        return { size: n, nonzero: nz, fnv: h.toString(16), generation: M._rtw_save_generation() };
      });
      say('module save ' + JSON.stringify(r));
    }
    else if (cmd === 'grep') {   // host log lines matching x
      const re = new RegExp(x); say(`log /${x}/: ` + (await hostLog()).split('\n').filter((l) => re.test(l)).slice(-6).join(' | '));
    }
    else if (cmd === 'fetchfile') {   // Saved files: the newest entry whose name starts with x, through the host's Save button -> OUTDIR
      await page.click('[data-action=files]');
      const name = (await page.$$eval('[data-file]', (els) => els.map((e) => e.getAttribute('data-file')))).filter((n) => n.startsWith(x)).pop();
      if (!name) { say(`no saved file ${x}*`); fails++; }
      else {
        const [dl] = await Promise.all([page.waitForEvent('download'), page.click(`[data-file="${name}"] [data-action=file-save]`)]);
        await dl.saveAs(join(out, name)); say(`fetched ${name}`); lastFetched = join(out, name);
      }
      await page.click('[data-action=close-menu]').catch(() => {});
    }
    else if (cmd === 'pos') say(`conker at ${JSON.stringify(await conkerPos())}`);
    else if (cmd === 'state') {
      const st = await gameState();
      const audio = await page.getAttribute('[data-state=playing]', 'data-audio').catch(() => null);
      const lines = (await hostLog().catch(() => '')).split('\n');
      say(`state ${JSON.stringify(st)} audio ${audio}`);
      say('log tail:\n  ' + lines.slice(-12).join('\n  '));
    } else if (cmd === 'ov' || cmd === 'opts' || ['cam', 'photoinfo', 'replay', 'optsync'].includes(cmd)) {   // P377 (P378: cam, photoinfo, replay)
      const w = await gameWorker();
      const v = w && await w.evaluate((c) => (c === 'ov' ? globalThis.__rtwConker.overlay() : c === 'opts' ? globalThis.__rtwConker.options() : globalThis.__rtwConker[c]()), cmd);
      say(`${cmd} ${JSON.stringify(v)}`);
    } else if (cmd === 'hostmenu') {   // the host's menu open for MS ms (the host pauses the game: rtw_pause)
      await page.click('[data-action=menu]'); await page.waitForTimeout(Number(x || 1000)); await page.click('[data-action=close-menu]').catch(() => {});
    } else if (cmd === 'dismiss') {   // the host's "may delete saved games" notice (it covers the picture's top)
      await page.click('[data-state=persist-warning] button', { timeout: 2000 }).catch(() => {});
    } else if (cmd === 'press') {
      for (let i = 0; i < Number(y || 1); i++) { await page.keyboard.down(x); await page.waitForTimeout(90); await page.keyboard.up(x); await page.waitForTimeout(160); }
    } else if (cmd === 'expect' || cmd === 'waitfor') {   // waitfor:PATH:VALUE[:MS] polls every 100 ms (default 20 s)
      const field = async () => {
        const [root, ...path] = x.split('.');
        if (root === 'hoststored' || root === 'hostmenu') {   // P378: the host's stored options / what its menu shows
          let v;
          if (root === 'hoststored') v = await page.evaluate(() => JSON.parse(localStorage.getItem('rtw:options:conker-eu') || '{}'));
          else {
            await page.click('[data-action=menu]');
            await page.locator('[data-option]').first().waitFor({ timeout: 5000 });
            v = await page.$$eval('[data-option]', (rows) => Object.fromEntries(rows.map((r) => {
              const box = r.querySelector('input[type=checkbox]'), f = r.querySelector('input, select');
              return [r.getAttribute('data-option'), box ? (box.checked ? 1 : 0) : f ? Number(f.value) : null];
            })));
            await page.click('[data-action=close-menu]', { timeout: 2000 }).catch(() => {});
          }
          let got = v;
          for (const k of path) got = got == null ? got : got[k];
          return got;
        }
        const w = await gameWorker();
        const own = ['opts', 'cam', 'photoinfo', 'replay', 'optsync'].includes(root);   // P378: cam, photoinfo, replay, optsync
        const v = w && await w.evaluate(([r, o]) => (r === 'opts' ? globalThis.__rtwConker.options() : o ? globalThis.__rtwConker[r]() : globalThis.__rtwConker.overlay()), [root, own]);
        let got = own ? v : v && v[root];
        for (const k of path) got = got == null ? got : got[k];
        return got;
      };
      const match = (v) => (String(y).startsWith('>') ? Number(v) > Number(String(y).slice(1)) : String(v) === String(y));   // VALUE '>N': more than N
      let got = await field();
      const until = Date.now() + Number(a.split(':')[3] || 20000);
      while (cmd === 'waitfor' && !match(got) && Date.now() < until) { await page.waitForTimeout(100); got = await field(); }
      const ok = match(got);
      say(`${cmd} ${x} = ${y}: ${ok ? 'ok' : `FAIL (got ${JSON.stringify(got)})`}`);
      if (!ok) fails++;
    } else if (cmd === 'wheel') {   // P378 wheel:DY: the mouse over the middle of the game frame, one wheel event of DY pixels
      const box = await page.locator('iframe').first().boundingBox();
      await page.mouse.move(box.x + box.width / 2, box.y + box.height / 2);
      await page.mouse.wheel(0, Number(x)); await page.waitForTimeout(150);
      say(`wheel ${x}`);
    } else if (cmd === 'click') {   // P378 a click on the middle of the picture (the host's "Click to use the mouse": pointer lock)
      const box = await page.locator('iframe').first().boundingBox();
      let locked = 'no catcher';
      for (let i = 0; i < 4 && locked !== '1'; i++) {   // headless Chrome sometimes refuses the first request
        await page.mouse.click(box.x + box.width / 2, box.y + box.height / 2); await page.waitForTimeout(400);
        locked = await page.getAttribute('[data-field=mouse-catch]', 'data-locked', { timeout: 1000 }).catch(() => 'no catcher');
      }
      say(`clicked the picture (mouse captured: ${locked})`);
    } else if (cmd === 'askfile') {   // P378 the host's prompt after rtw_request_file: pick FILE (last = the last fetchfile)
      await page.locator('[data-state=file-request]').waitFor({ timeout: 10000 });
      const file = x === 'last' ? lastFetched : resolve(x);
      await page.setInputFiles('[data-field=file-request-input]', file);
      say(`host file prompt: picked ${file.split('/').pop()}`);
    } else if (cmd === 'openingame') {   // P378 Saved files: "Open in game" next to the newest file whose name starts with x
      await page.click('[data-action=files]');
      const name = (await page.$$eval('[data-file]', (els) => els.map((e) => e.getAttribute('data-file')))).filter((n) => n.startsWith(x)).pop();
      if (!name) { say(`no saved file ${x}*`); fails++; }
      else { await page.click(`[data-file="${name}"] [data-action=file-open]`); say(`open in game: ${name}`); }
      await page.waitForTimeout(300);
      await page.click('[data-action=close-menu]', { timeout: 1000 }).catch(() => {});   // (Open in game closes the menu)
    } else if (cmd === 'unlock') {   // P378 give the mouse back (Esc does not in headless Chrome)
      await page.evaluate(() => document.exitPointerLock()); await page.waitForTimeout(300); say('mouse released');
    } else if (cmd === 'pad') {   // P378
      await page.evaluate(([ax, ay]) => {
        window.__rtwFakePad = ax === 'off' ? null : { id: 'rtw_e2e fake pad', index: 0, connected: true, mapping: 'standard', timestamp: performance.now(),
          buttons: Array.from({ length: 17 }, () => ({ pressed: false, touched: false, value: 0 })), axes: [0, 0, Number(ax), Number(ay || 0)] };
      }, [x, y]);
      say(`fake gamepad ${x === 'off' ? 'off' : `right stick ${x}, ${y || 0}`}`);
    } else if (cmd === 'hostopt') {   // the host's own options menu
      await page.click('[data-action=menu]');
      const row = page.locator(`[data-option="${x}"]`);
      await row.waitFor({ timeout: 5000 });
      const box = row.locator('input[type=checkbox]');
      if (await box.count()) { if ((await box.isChecked()) !== (y === '1')) await box.click(); }
      else { const f = row.locator('input, select').first(); await f.fill(String(y)).catch(async () => f.selectOption(String(y))); await f.dispatchEvent('change'); }
      await page.waitForTimeout(300);
      await page.click('[data-action=close-menu]').catch(() => {});
      say(`host option ${x} = ${y}`);
    } else { say('unknown action ' + a); fails++; }
  }
} catch (e) {
  say('ERROR ' + (e && e.stack || e)); fails++;
  await page.click('text=Details', { timeout: 1000 }).catch(() => {});
  await page.screenshot({ path: join(out, 'error.png') }).catch(() => {});
  say('page text: ' + (await page.evaluate(() => document.body.innerText).catch(() => '')).replace(/\s+/g, ' ').slice(0, 3000));
}
clearTimeout(timer);
say(fails ? `${fails} failure(s)` : 'done');
await finish(fails ? 1 : 0);
