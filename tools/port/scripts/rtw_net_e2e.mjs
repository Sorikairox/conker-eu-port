// P380 online play of the retrowser build (standard 1.2) end to end: 2-4 pages (one browser context each) in ONE muted
// headless Chrome join one room on the retrowser host's local room server and play a lockstep session.
//   node tools/port/scripts/rtw_net_e2e.mjs OUTDIR ROM
// The host is retrowser's built dist served in this process (tools/serve-worker.ts: the Worker handler + the room server
// in memory, like its e2e/net.test.ts); the game repo (port/build/rtw/dist, or RTW_DIST) is served by retrowser's GitHub
// mock as sorikairox/conker-eu-port. Host candidates only (no STUN: localStorage rtw:test-net {"ice":[]}).
// Env: PLAYERS (2..4, default 2), FRAMES (retraces of play with inputs before the checks, default 600), PORT (default
// 8795), RETROWSER_DIR, DROP=1 (close the last player's page: the others agree on its neutral frame and go on, hashes
// compared after the drop too), DESYNC=1 (at the end: flip one byte of game memory on player 2 -> both report it),
// LEAVE=1 (then player 1 leaves the session: its game restarts alone), SOLO=1 (afterwards: a fresh page plays alone), RTW_OPTIONS_HOST (stored options of player 1, default
// {"1":1,"2":1,"9":70,"105":1,"113":0}: skip intro (a start-up option) and four inGame options, P382) and RTW_OPTIONS_GUEST
// (of the others, default the opposite values: the session must use player 1's, start-up and inGame alike).
// P383: the defaults include Widescreen 102 / High frame rate 104 (inGame: the room host's in a session; the widescreen
// picture is 16:9 on every peer, fixed: the guest's menu row says "Set by the room host during online play.", its
// change is refused). COSMETIC (default 1): before the session every player sets Hi-res menus 100 / Smooth font 101 /
// Full-resolution 103 in the customisation settings (their record; player 1 100=1 101=0 103=0, the others the
// opposite): in the session each keeps its own. LEAVE=2: player 2 leaves (its game restarts alone): its own
// Widescreen / High frame rate (stored by the host, untouched by the session) and its own record values are back.
// Prints PASS / FAIL lines and "ALL PASS" at the end; exit code 0 only then.
import { mkdirSync, writeFileSync } from 'node:fs';
import { homedir } from 'node:os';
import { join, resolve } from 'node:path';

const [out, rom] = process.argv.slice(2);
if (!out || !rom) { console.error('usage: rtw_net_e2e.mjs OUTDIR ROM'); process.exit(2); }
const RTW = process.env.RETROWSER_DIR || join(homedir(), 'Code/retrowser');
const { chromium } = await import(join(RTW, 'node_modules/playwright-core/index.mjs'));
const { startMockGithub } = await import(join(RTW, 'tools/mock-github.ts'));
const { serveWorker } = await import(join(RTW, 'tools/serve-worker.ts'));
const DIST = process.env.RTW_DIST ? resolve(process.env.RTW_DIST) : resolve(new URL('../../../port/build/rtw/dist', import.meta.url).pathname);
const REPO = 'sorikairox/conker-eu-port', COMMIT = 'c0ffee0000000000000000000000000000000380';
const PLAYERS = Math.max(2, Math.min(4, Number(process.env.PLAYERS || 2)));
const FRAMES = Number(process.env.FRAMES || 600), PORT = Number(process.env.PORT || 8795);
mkdirSync(out, { recursive: true });
const t0 = Date.now(), say = (s) => console.log(`[${((Date.now() - t0) / 1000).toFixed(1)}s] ${s}`);
let fails = 0;
const check = (ok, what) => { say(`${ok ? 'PASS' : 'FAIL'} ${what}`); if (!ok) fails++; return ok; };

const mock = await startMockGithub({ [REPO]: { refs: { main: COMMIT }, commits: [{ sha: COMMIT, dir: DIST }] } });
const served = await serveWorker(PORT);
const site = `http://localhost:${PORT}`;
const chrome = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
const browser = await chromium.launch({ executablePath: chrome, headless: true,
  args: ['--mute-audio', '--use-angle=metal', '--autoplay-policy=no-user-gesture-required', '--disable-features=WebRtcHideLocalIpsWithMdns'] });
const players = [];
const finish = async (code) => {
  for (const p of players) {
    try { writeFileSync(join(out, `host_log_p${p.n}.txt`), (await hostLog(p).catch(() => '')) + '\n'); } catch { /* ignore */ }
    if (p.errors.length) say(`P${p.n} page errors: ${p.errors.slice(0, 3).join(' | ')}`);
  }
  await browser.close().catch(() => {});
  await mock.close();
  await new Promise((ok) => { served.closeAllConnections?.(); served.close(ok); });
  process.exit(code);
};
const timer = setTimeout(() => { say('TIMEOUT'); fails++; finish(3); }, Number(process.env.RTW_TIMEOUT || 540000));

async function newPlayer(n, options) {
  const vw = process.env.VARY_VIEW === '1' ? [960, 700, 1280, 820][(n - 1) % 4] : 960;   // VARY_VIEW=1: a different page size per player
  const ctx = await browser.newContext({ viewport: { width: vw, height: Math.round(vw * 2 / 3) } });
  await ctx.addInitScript(([ep, opts]) => {
    try {
      if (location.hostname !== 'localhost') return;
      localStorage.setItem('rtw:test-endpoints', ep);
      localStorage.setItem('rtw:test-net', '{"ice":[]}');
      if (opts) localStorage.setItem('rtw:options:conker-eu', opts);
    } catch { /* ignore */ }
  }, [JSON.stringify(mock.endpoints), options]);
  const page = await ctx.newPage();
  const p = { n, ctx, page, errors: [] };
  page.on('pageerror', (e) => p.errors.push(e.message));
  players.push(p);
  return p;
}
const hostLog = (p) => p.page.getAttribute('[data-state=playing]', 'data-log', { timeout: 2000 }).then((v) => v || '');
async function worker(p) {   // the game's worker (the sandbox's dedicated worker with __rtwConker); a new one after a restart
  for (const w of p.page.workers()) {
    try { if (await w.evaluate(() => typeof globalThis.__rtwConker === 'object')) return w; } catch { /* gone */ }
  }
  return null;
}
async function inWorker(p, fn, arg) { const w = await worker(p); return w ? w.evaluate(fn, arg).catch(() => null) : null; }
const net = (p) => inWorker(p, () => globalThis.__rtwConker.net());
const frameOf = (p) => inWorker(p, () => globalThis.__rtwConker.Module._port_net_frame() >>> 0);
async function open(p) {
  await p.page.goto(`${site}/g/${REPO}`);
  await p.page.click('[data-action=download]', { timeout: 60000 });
  await p.page.locator('[data-field=rom]').setInputFiles(rom, { timeout: 120000 });
  await p.page.waitForFunction(() => Number(document.querySelector('[data-state=playing]')?.getAttribute('data-frames') ?? 0) > 10, null, { timeout: 120000 });
  await p.page.click('[data-state=persist-warning] button', { timeout: 1000 }).catch(() => {});
}
async function until(what, fn, ms = 60000, every = 250) {
  const end = Date.now() + ms;
  for (;;) {
    const v = await fn().catch(() => null);
    if (v) return v;
    if (Date.now() > end) throw new Error(`timeout: ${what}`);
    await new Promise((r) => setTimeout(r, every));
  }
}
// hash agreement over the given players: for every retrace in all their hash rings, are {H, S} equal?
async function compareHashes(list, label) {
  const sts = await Promise.all(list.map(net));
  const rings = sts.map((s) => new Map((s ? s.hashes : []).map((h) => [h.f, h])));
  let same = 0, differ = 0, first = 0, last = 0;
  for (const [f, h] of rings[0]) {
    if (!rings.every((r) => r.has(f))) continue;
    if (rings.every((r) => r.get(f).h === h.h && r.get(f).s === h.s)) { same++; first = first || f; last = Math.max(last, f); } else differ++;
  }
  if (differ) {   // diagnostics: the renderer's GPU write-back ranges (excluded from the hash) and where the reported page differs now
    const MAPF = join(DIST, '../conker.map'), map = (await import('node:fs')).readFileSync(MAPF, 'utf8');
    const gpuAt = parseInt((/^([0-9a-f]+)\s+\S+\s+\S+\s+net_gpu$/m.exec(map) || [])[1] || '0', 16), ngpuAt = parseInt((/^([0-9a-f]+)\s+\S+\s+\S+\s+net_ngpu$/m.exec(map) || [])[1] || '0', 16);
    const rep = sts.find((x) => x && x.desyncReport);
    const page = rep ? rep.desyncReport.firstPages[0] : -1;
    const dumps = await Promise.all(list.map((p) => inWorker(p, ([g, ng, pg]) => {
      const M = globalThis.__rtwConker.Module, H = new Uint32Array(M.HEAPU8.buffer), rd = M._port_net_page_info(4) >>> 0, base = M._port_net_page_info(2) >>> 0;
      const n = H[ng >> 2], ranges = [];
      for (let i = 0; i < n && i < 32; i++) { const a = H[(g >> 2) + i * 2], b = H[(g >> 2) + i * 2 + 1]; ranges.push(a >= rd && a < rd + 0x800000 ? `N64 ${(0x80000000 + a - rd).toString(16)}+${(b - a).toString(16)}` : `wasm ${a.toString(16)}+${(b - a).toString(16)}`); }
      const bytes = pg >= 0 ? Array.from(M.HEAPU8.subarray(base + pg * 4096, base + pg * 4096 + 4096)) : [];
      return { ranges, bytes, frame: M._port_net_frame() >>> 0 };
    }, [gpuAt, ngpuAt, page])));
    const lines = dumps.map((d, i) => `P${list[i].n} retrace ${d && d.frame} gpu write-backs: ${d ? d.ranges.join(', ') : '?'}`);
    if (page >= 0 && dumps.every(Boolean)) {
      const diffAt = []; for (let k = 0; k < 4096; k++) if (dumps.some((d) => d.bytes[k] !== dumps[0].bytes[k])) diffAt.push(k);
      lines.push(`page ${page}: ${diffAt.length} byte offsets differ now, first ${diffAt.slice(0, 16).map((k) => k.toString(16)).join(' ')}`);
    }
    writeFileSync(join(out, 'desync_diag.txt'), lines.join('\n') + '\n');
    say(lines.join('\n'));
  }
  check(same >= 10 && differ === 0, `${label}: ${same} common hash points equal (retraces ${first}..${last}), ${differ} differ; ` +
    sts.map((s, i) => `P${list[i].n} matched ${s ? s.hashesMatched : '?'} to ${s ? s.hashChecked : '?'}, desync ${s && s.desync ? s.desync.frame : 'none'}`).join(', '));
  return { same, differ };
}
const KEYS = ['Enter', 'ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', 'KeyX', 'KeyC', 'KeyZ', 'KeyA'];
async function playInputs(list, target) {   // random presses on every page until each ran `target` retraces
  let i = 0, best = -1, bestAt = Date.now();
  for (;;) {
    const fs = await Promise.all(list.map(frameOf));
    if (fs.every((f) => f >= target)) return fs;
    const low = Math.min(...fs);
    if (low > best) { best = low; bestAt = Date.now(); }
    else if (Date.now() - bestAt > 20000) {   // stalled: keep what explains it
      const st = await Promise.all(list.map(net));
      for (const p of list) await inWorker(p, () => globalThis.__rtwConker.Module._port_dump_threads());
      writeFileSync(join(out, 'stall.json'), JSON.stringify(st, null, 1));
      for (const p of list) writeFileSync(join(out, `stall_log_p${p.n}.txt`), (await hostLog(p).catch(() => '')) + '\n');
      throw new Error(`stalled at retraces ${fs.join(' ')} for 20 s (stall.json)`);
    }
    if (++i % 20 === 0) say(`retraces ${fs.join(' ')}`);
    await Promise.all(list.map(async (p, k) => {
      const key = KEYS[(i * 7 + k * 3 + Math.floor(Math.random() * KEYS.length)) % KEYS.length];
      await p.page.keyboard.down(key); await p.page.waitForTimeout(60 + 40 * k); await p.page.keyboard.up(key);
    }));
    await new Promise((r) => setTimeout(r, 150));
  }
}

try {
  const hostOpts = process.env.RTW_OPTIONS_HOST || '{"1":1,"2":1,"9":70,"105":1,"113":0,"102":1,"104":1}',   // P382: + inGame options (P383: 102, 104)
    guestOpts = process.env.RTW_OPTIONS_GUEST || '{"1":0,"2":0,"9":100,"105":0,"113":1,"102":0,"104":0}';
  for (let n = 1; n <= PLAYERS; n++) await newPlayer(n, n === 1 ? hostOpts : guestOpts);
  for (const p of players) { await open(p); say(`P${p.n} plays alone`); }
  // P383 helpers: the picture's aspect, the record's own picture options per player
  const aspectOf = (p) => inWorker(p, () => { const c = globalThis.__rtwConker.Module.canvas; return c.width / c.height; });
  const isWide = (a) => a > 1.7 && a < 1.8, is43 = (a) => Math.abs(a - 4 / 3) < 0.01;
  const COSMETIC = process.env.COSMETIC !== '0', COSMETIC_IDS = [100, 101, 103];
  const cosmeticOf = (p) => (p.n === 1 ? { 100: 1, 101: 0, 103: 0 } : { 100: 0, 101: 1, 103: 1 });
  {
    const want = (p) => JSON.parse(p.n === 1 ? hostOpts : guestOpts);
    const o = await Promise.all(players.map((p) => inWorker(p, () => globalThis.__rtwConker.options())));
    check(players.every((p, i) => o[i] && [102, 104].every((k) => want(p)[k] === undefined || o[i][k] === want(p)[k])),
      `alone, every player has its own stored Widescreen / High frame rate (${players.map((p, i) => `P${p.n} ${o[i] && o[i][102]}/${o[i] && o[i][104]}`).join(', ')})`);
  }
  if (COSMETIC) {
    for (const p of players) await inWorker(p, (vals) => { for (const [k, v] of Object.entries(vals)) globalThis.__rtwConker.menuSet(+k, v); }, cosmeticOf(p));
    await new Promise((r) => setTimeout(r, 1000));   // the record is written 250 ms after a change
    const o = await Promise.all(players.map((p) => inWorker(p, () => globalThis.__rtwConker.options())));
    check(players.every((p, i) => o[i] && COSMETIC_IDS.every((k) => o[i][k] === cosmeticOf(p)[k])),
      `alone, each player set its own Hi-res menus / Smooth font / Full-resolution (${players.map((p, i) => `P${p.n} ${COSMETIC_IDS.map((k) => o[i] && o[i][k]).join('/')}`).join(', ')})`);
  }
  check((await Promise.all(players.map(net))).every((s) => s && !s.active), 'before the session nobody is in one');
  if (process.env.ALONE === '1') {   // diagnostics: the same pages and inputs, every game alone (no session)
    const fs = await playInputs(players, FRAMES);
    check(true, `${PLAYERS} games alone played to retraces ${fs.join(' ')}`);
    throw new Error('ALONE run done');
  }
  const A = players[0];
  await A.page.click('[data-action=online]');
  await A.page.click('[data-action=net-create]');
  await A.page.waitForSelector('[data-field=room-code]');
  const code = (await A.page.textContent('[data-field=room-code]')).trim();
  say(`room ${code}`);
  for (const p of players.slice(1)) {
    await p.page.click('[data-action=online]');
    await p.page.fill('[data-field=net-code]', code);
    await p.page.click('[data-action=net-join]');
  }
  await until('every guest connected and matched', async () => (await A.page.$$('[data-field=net-players] li[data-match=ok][data-net-state="1"]')).length >= PLAYERS - 1, 60000);
  await A.page.waitForSelector('[data-action=net-start]:not([disabled])');
  await A.page.waitForTimeout(2500);   // ping reports for the boot's shared table
  await A.page.click('[data-action=net-start]');
  say('start pressed');
  const sts = await until('every player in the session', async () => {
    const s = await Promise.all(players.map(net));
    return s.every((x) => x && x.active && x.frame > 5) ? s : null;
  }, 120000);
  check(sts.every((s, i) => s.me === i && s.players === PLAYERS), `session indexes ${sts.map((s) => `${s.me}/${s.players}`).join(' ')}`);
  check(new Set(sts.map((s) => s.delay)).size === 1, `the same input delay everywhere: ${sts.map((s) => `${s.delay}${s.autoDelay ? ' auto (worst p90 ' + s.worst + ' ms)' : ''}`).join(', ')}`);
  const opts = await Promise.all(players.map((p) => inWorker(p, () => globalThis.__rtwConker.options())));
  check(opts.every((o) => o && o[1] === 1), `every player boots with the room host's options (skip intro: ${opts.map((o) => o && o[1]).join(' ')})`);
  {   // P382: the room host's inGame options (hidden in the host's menu, kept from rtw_option_changed) on every peer too
    const want = JSON.parse(hostOpts), ids = Object.keys(want).filter((k) => k !== '1');
    check(opts.every((o) => o && ids.every((k) => o[k] === want[k])),
      `every player gets the room host's inGame options (${ids.map((k) => `${k}: ${opts.map((o) => o && o[k]).join('/')}`).join(', ')})`);
  }
  check(sts.every((s) => s.beganAt === 0), `the session is set before the first retrace (lockstep boot): ${sts.map((s) => s.beganAt).join(' ')}`);
  {   // P383: Widescreen follows the room host (16:9 on every peer, or 4:3 on every peer); the cosmetic options stay each player's own
    const hostWide = JSON.parse(hostOpts)[102];
    if (hostWide !== undefined) {
      const as = await until('every picture laid out', async () => { const a = await Promise.all(players.map(aspectOf)); return a.every((x) => x) ? a : null; }, 20000);
      check(as.every((a) => (hostWide ? isWide(a) : is43(a))), `every peer draws the room host's Widescreen ${hostWide ? 'on (16:9)' : 'off (4:3)'}: aspects ${as.map((a) => a.toFixed(3)).join(' ')}`);
    }
    if (COSMETIC) check(players.every((p, i) => opts[i] && COSMETIC_IDS.every((k) => opts[i][k] === cosmeticOf(p)[k])),
      `in the session each player keeps its own Hi-res menus / Smooth font / Full-resolution (${players.map((p, i) => `P${p.n} ${COSMETIC_IDS.map((k) => opts[i] && opts[i][k]).join('/')}`).join(', ')})`);
    // the guest's own menu: the Widescreen row is locked with the reason, a change refused; Full-resolution is not locked
    const tap = async (p, key, after = 200) => { await p.page.keyboard.down(key); await p.page.waitForTimeout(120); await p.page.keyboard.up(key); await p.page.waitForTimeout(after); };
    const B = players[1], ws0 = opts[1] && opts[1][102];
    await tap(B, 'Digit6', 300);
    await until('the guest\'s menu open', () => inWorker(B, () => globalThis.__rtwConker.overlay().menu.open), 10000);
    await tap(B, 'ArrowDown', 150);
    await tap(B, 'KeyX', 300);
    const m1 = await inWorker(B, () => globalThis.__rtwConker.overlay().menu);
    await tap(B, 'KeyX', 400);
    const ws1 = await inWorker(B, () => globalThis.__rtwConker.options()[102]);
    const refusedSet = await inWorker(B, (v) => { globalThis.__rtwConker.menuSet(102, v); globalThis.__rtwConker.menuSet(104, v); const o = globalThis.__rtwConker.options(); return [o[102], o[104]]; }, ws0 ? 0 : 1);
    await tap(B, 'ArrowDown', 150);
    const m2 = await inWorker(B, () => globalThis.__rtwConker.overlay().menu);
    await tap(B, 'KeyC', 150); await tap(B, 'KeyC', 300);
    const mc = await inWorker(B, () => globalThis.__rtwConker.overlay().menu.open);
    if (mc) { await tap(B, 'Digit6', 300); }
    check(m1 && m1.page === 'picture' && m1.item === 'Widescreen' && m1.lock === 'Set by the room host during online play.' && ws1 === ws0 &&
      refusedSet && refusedSet[0] === ws0 && refusedSet[1] === (opts[1] && opts[1][104]),
      `guest's Widescreen row locked ("${m1 && m1.lock}"), A on it and a menu change refused (102 ${ws0} -> ${ws1}, set -> ${refusedSet && refusedSet.join('/')})`);
    check(m2 && /Full/.test(m2.item || '') && m2.lock === '', `guest's ${m2 && m2.item} row is not locked`);
  }
  const fs = await playInputs(players, FRAMES);
  say(`played to retraces ${fs.join(' ')}`);
  await new Promise((r) => setTimeout(r, 1500));
  await compareHashes(players, `${PLAYERS} players after ${FRAMES} retraces with inputs`);
  // the remote inputs that arrived = what the sender sampled (ring of player 2's channel on player 1 vs on player 2)
  {
    const B = players[1], lo = Math.max(10, FRAMES - 200), hi = FRAMES - 10;
    const [ra, rb] = await Promise.all([inWorker(A, ([a, b]) => globalThis.__rtwConker.netRing(1, a, b), [lo, hi]), inWorker(B, ([a, b]) => globalThis.__rtwConker.netRing(1, a, b), [lo, hi])]);
    const both = ra && rb ? ra.filter((v, i) => v !== -1 && v === rb[i]).length : 0, pressed = rb ? rb.filter((v) => v > 0).length : 0;
    check(both > 50 && pressed > 0, `player 2's inputs on player 1 = player 2's own: ${both} of ${hi - lo + 1} ring frames still kept equal, ${pressed} with buttons / stick`);
  }
  say('canvas sizes: ' + (await Promise.all(players.map((p) => inWorker(p, () => { const c = globalThis.__rtwConker.Module.canvas; return `${c.width}x${c.height}`; })))).join(' '));
  const st2 = await Promise.all(players.map(net));
  say('stats: ' + st2.map((s) => `P${s.me + 1} sent ${s.sent} recv ${s.recv} refused ${s.refused} bad ${s.bad} waits ${s.waits} (${s.waitMs} ms) slowed ${s.slowedMs} ms kicks ${s.kicks}`).join('; '));
  check(st2.every((s) => s.bad === 0 && s.refused === 0), 'no bad or refused packets');
  writeFileSync(join(out, 'net_status.json'), JSON.stringify(st2, null, 1));

  if (process.env.DROP === '1') {
    const gone = players[PLAYERS - 1], rest = players.slice(0, -1);
    say(`closing P${gone.n}'s page (no goodbye)`);
    await gone.page.close();
    const ds = await until('the others agreed on the drop', async () => {
      const s = await Promise.all(rest.map(net));
      return s.every((x) => x && x.drops.some((d) => d.ch === gone.n - 1)) ? s : null;
    }, 60000);
    const nf = ds.map((s) => s.drops.find((d) => d.ch === gone.n - 1).neutralFrom);
    check(new Set(nf).size === 1, `drop of player ${gone.n} agreed: controller ${gone.n} neutral from retrace ${nf.join(' / ')}`);
    const f0 = Math.max(...(await Promise.all(rest.map(frameOf))));
    const fs2 = await playInputs(rest, f0 + 300);
    check(fs2.every((f) => f > f0 + 250), `the others go on after the drop (retraces ${f0} -> ${fs2.join(' ')})`);
    await new Promise((r) => setTimeout(r, 1500));
    if (rest.length > 1) await compareHashes(rest, `the ${rest.length} remaining players after the drop`);
    players.splice(PLAYERS - 1, 1);
    await gone.ctx.close();
  }

  if (process.env.DESYNC === '1' && players.length > 1) {
    const B = players[1];
    await inWorker(B, () => { const M = globalThis.__rtwConker.Module; const a = M._port_net_page_info(4) >>> 0; M.HEAPU8[a + 0x200000] ^= 1; });   // n64_rdram + 2 MB, as ?netdesync
    say('flipped one byte of n64_rdram on player 2');
    const rs = await until('both report the desync', async () => {
      const s = await Promise.all([net(A), net(B)]);
      return s.every((x) => x && x.desync && x.desyncReport) ? s : null;
    }, 30000);
    check(rs.every((s) => /n64_rdram N64 80200000/.test(s.desyncReport.where)), `desync report: ${rs.map((s) => `P${s.me + 1} retrace ${s.desync.frame}: ${s.desyncReport.where}`).join(' | ')}`);
  }

  if (process.env.LEAVE === '1') {   // the room host leaves the session: the host restarts its game alone (own save)
    await A.page.click('[data-action=online]');
    await A.page.click('[data-action=net-leave]');
    const f = await until('player 1 alone again', async () => { const s = await net(A); const x = await frameOf(A); return s && !s.active && x > 100 ? x : null; }, 60000);
    check(true, `player 1 left the session and plays alone (${f} retraces, no session)`);
  }

  if (process.env.LEAVE === '2') {   // P383: a guest leaves: its own options are back (the session overwrote nothing)
    const B = players[1], own = JSON.parse(guestOpts);
    await B.page.click('[data-action=online]');
    await B.page.click('[data-action=net-leave]');
    const f = await until('player 2 alone again', async () => { const s = await net(B); const x = await frameOf(B); return s && !s.active && x > 100 ? x : null; }, 60000);
    await B.page.click('[data-action=online]').catch(() => {});   // close the panel again (harmless if it is not a toggle)
    const o = await inWorker(B, () => globalThis.__rtwConker.options()), a = await aspectOf(B);
    const stored = JSON.parse(await B.page.evaluate(() => localStorage.getItem('rtw:options:conker-eu') || '{}'));
    check(o && [102, 104].every((k) => own[k] === undefined || o[k] === own[k]) && (own[102] ? !is43(a) : is43(a)),
      `player 2 left (${f} retraces alone): its own Widescreen ${o && o[102]} / High frame rate ${o && o[104]} are back (aspect ${a && a.toFixed(3)})`);
    check([102, 104].every((k) => own[k] === undefined || +stored[k] === own[k]), `player 2's stored options untouched by the session (102 ${stored[102]}, 104 ${stored[104]})`);
    if (COSMETIC) check(o && COSMETIC_IDS.every((k) => o[k] === cosmeticOf(B)[k]), `player 2's own record values still there (${COSMETIC_IDS.map((k) => o && o[k]).join('/')})`);
  }

  if (process.env.SOLO === '1') {
    const S = await newPlayer(9, '');
    await open(S);
    const f = await until('solo retraces', async () => { const x = await frameOf(S); return x > 250 ? x : null; }, 60000);
    const s = await net(S);
    check(s && !s.active && f > 250, `single player: ${f} retraces, no session`);
    await S.ctx.close(); players.splice(players.indexOf(S), 1);
  }
} catch (e) {
  say('ERROR ' + (e && e.stack || e)); fails++;
}
clearTimeout(timer);
say(fails ? `${fails} FAIL` : 'ALL PASS');
await finish(fails ? 1 : 0);
