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
import { mkdirSync, readFileSync, writeFileSync } from 'node:fs';
import { homedir } from 'node:os';
import { join, resolve } from 'node:path';

const [out, host, rom, actions = 'open,frame:200,state'] = process.argv.slice(2);
if (!out || !host || !rom) { console.error('usage: rtw_e2e.mjs OUTDIR HOST_URL ROM ACTIONS'); process.exit(2); }
const RTW = process.env.RETROWSER_DIR || join(homedir(), 'Code/retrowser');
const { chromium } = await import(join(RTW, 'node_modules/playwright-core/index.mjs'));
const { startMockGithub } = await import(join(RTW, 'tools/mock-github.ts'));
const DIST = resolve(new URL('../../../port/build/rtw/dist', import.meta.url).pathname);
const REPO = 'sorikairox/conker-eu-port', COMMIT = 'c0ffee0000000000000000000000000000000376';
mkdirSync(out, { recursive: true });
const t0 = Date.now(), say = (s) => console.log(`[${((Date.now() - t0) / 1000).toFixed(1)}s] ${s}`);

const mock = await startMockGithub({ [REPO]: { refs: { main: COMMIT }, commits: [{ sha: COMMIT, dir: DIST }] } });
const chrome = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const args = ['--mute-audio', '--use-angle=metal', '--autoplay-policy=no-user-gesture-required'];
const profile = process.env.RTW_PROFILE;
const context = profile
  ? await chromium.launchPersistentContext(profile, { executablePath: chrome, headless: true, args, viewport: { width: 1280, height: 800 }, acceptDownloads: true })
  : await (await chromium.launch({ executablePath: chrome, headless: true, args })).newContext({ viewport: { width: 1280, height: 800 }, acceptDownloads: true });
const browser = context.browser();
await context.addInitScript(([ep, opts]) => {
  try {
    if (location.hostname !== 'localhost') return;
    localStorage.setItem('rtw:test-endpoints', ep);
    if (opts) localStorage.setItem('rtw:options:conker-eu', opts);
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
  await page.goto(`${host}/g/${REPO}`);
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

let fails = 0;
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
        await dl.saveAs(join(out, name)); say(`fetched ${name}`);
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
    } else { say('unknown action ' + a); fails++; }
  }
} catch (e) { say('ERROR ' + (e && e.stack || e)); fails++; }
clearTimeout(timer);
say(fails ? `${fails} failure(s)` : 'done');
await finish(fails ? 1 : 0);
