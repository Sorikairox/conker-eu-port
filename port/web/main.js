// Page glue for the Conker wasm32 port. The ROM is supplied by the user and never leaves the browser
// (cached in IndexedDB). Two wasm apps: the scheduler demo and the game; one per page load.
// P27: ROM drop zone, input (keyboard + Gamepad API -> PIF pad state), EEPROM saves in IndexedDB,
// fullscreen / pause / volume, debug console behind a toggle, audio resume on the first gesture.
'use strict';
const EU_SHA1 = 'ee7bc6656fd1e1d9ffb3d19add759f28b88df710';
const $ = (id) => document.getElementById(id);
const Q = new URLSearchParams(location.search);
// P337 online multiplayer phase 0: ?netdet=1 = forced online determinism (port/ultra/pc_net.c). The page then writes no
// pad state (pads come from the ?padf scripts / the input ring only), sends the default options vector once (no ?opt, no
// saved options, no changes during the run) and boots with a blank EEPROM that is never persisted.
const NETDET = /[?&]netdet(=1)?(&|$)/.test(location.search);
// P338 online multiplayer phase 1: netCfg = the lockstep session this page boots into (port/web/net.js, pc_net.c), or
// null (the normal game). { mask: channels in the session, local: this peer's channels, delay: D retraces, hashEvery: K,
// options: the host's game options {key: value}, eeprom: the host's EEPROM image (Uint8Array) or null = blank,
// loop: loopback test peer {lat, loss} }. Test aid: ?netloop=1[&netmask=HEX][&netd=D][&netlat=MS][&netloss=PCT] runs a
// session against a loopback peer in this page that plays the ?padf1..3 scripts (with &netscript=1 pad 1 plays ?padf).
let netCfg = null;
if (Q.get('netloop')) netCfg = { mask: parseInt(Q.get('netmask') || 'F', 16), local: 1, delay: +(Q.get('netd') || 3), hashEvery: 10,
  options: null, eeprom: null, loop: { lat: +(Q.get('netlat') || 0), loss: +(Q.get('netloss') || 0) } };
const out = $('console');
let romBytes = null, romSha1 = null, romOk = false;
let running = null, M = null;

function log(s, cls) {
  const line = document.createElement('div');
  line.textContent = s;
  if (cls) line.className = cls;
  else if (/^PASS|\] PASS/.test(s)) line.className = 'pass';
  else if (/^FAIL|\] FAIL|RuntimeError|Aborted/.test(s)) line.className = 'fail';
  else if (/^\[stub/.test(s)) line.className = 'stub';
  out.appendChild(line);
  if (out.childNodes.length > 5000) out.removeChild(out.firstChild);
  if (!$('p-debug').hidden) out.scrollTop = out.scrollHeight;
  console.log(s);
}
const status = (s, cls) => { const e = $('status'); e.textContent = s; e.className = cls || ''; };
const store = {   // localStorage can throw (private mode, blocked storage): never required
  get(k, d) { try { const v = localStorage.getItem(k); return v === null ? d : JSON.parse(v); } catch (e) { return d; } },
  set(k, v) { try { localStorage.setItem(k, JSON.stringify(v)); } catch (e) { /* ignore */ } },
};

// ---------------------------------------------------------------- panels
function toggle(name, on) {
  const b = $('t-' + name), p = $('p-' + name);
  on = on === undefined ? p.hidden : on;
  p.hidden = !on; b.setAttribute('aria-pressed', String(on));
  $('side').hidden = ['controls', 'saves', 'options', 'online', 'debug'].every((n) => $('p-' + n).hidden);
  if (name === 'debug') { store.set('debug', on); if (on) out.scrollTop = out.scrollHeight; }
}
for (const n of ['controls', 'saves', 'options', 'online', 'debug']) $('t-' + n).onclick = () => toggle(n);
if (Q.get('debug') === '1' || (Q.get('debug') !== '0' && store.get('debug', false))) toggle('debug', true);

// ---------------------------------------------------------------- options (P324)
// Every port-only feature is optional. One row per option: key (localStorage 'opt.KEY'), label, default, help text,
// and `game`: the PORT_OPT_* id (port/ultra/port_options.h) when game C reads the option through port_option(id);
// those are pushed to the game with port_set_option before it starts and on every change. Defaults off = the
// original game, except where the user asked otherwise.
// Test aid: ?opt=KEY:1,KEY:0 overrides options for this page load (not saved).
const OPTIONS = [
  { key: 'online', label: 'Online multiplayer (experimental)', def: false,
    help: 'Shows the Online button: two players on two computers play a multiplayer match together (copy-paste connection codes, no server).' },
  { key: 'skipcut', label: 'Skippable cutscenes (hold L)', def: true, game: 0,
    help: 'Hold L for 3 s to skip any cutscene, even one not seen yet (also Start on the boot intro). Off: the N64 rules (only scenes already seen, L skips at once).' },
  { key: 'saveicon', label: 'Autosave icon',  def: false,
    help: 'A small save icon blinks in the top right corner of the picture for 1.5 s whenever the game writes its save.' },
  { key: 'togglecrouch', label: 'Toggle crouch', def: false,
    help: 'Z (key, pad button or touch button) latches: one press crouches and keeps crouching, the next press stands up.' },
  { key: 'togglerlook', label: 'Toggle R-Look', def: false,
    help: 'R latches the same way: one press turns R-Look on, the next press turns it off.' },
  { key: 'togglewalk', label: 'Toggle walk (half tilt)', def: false,
    help: 'The half-tilt key latches: one press walks (half stick), the next press runs again. Applies to every stick input of pad 1.' },
  { key: 'skipintro', label: 'Skip intro', def: false, game: 1,
    help: 'Start straight at the title menu: no boot logos, legal pages or intro. Takes effect at the next start.' },
  { key: 'healthhud', label: 'Health always visible', def: false, game: 2,
    help: 'The chocolate (health) pieces stay on screen during play. Off: as on the N64, they slide in only when your health changes.' },
  { key: 'cashhud', label: 'Always show cash', def: false, game: 3,
    help: 'Your cash total stays in the top right corner during play, drawn with the pause screen\'s $ and digit images. Off: as on the N64, it only pops up above Conker when he gets cash (and on the pause screen).' },
  { key: 'longbreath', label: 'Longer breath', def: false, game: 4,
    help: 'Conker can stay under water about twice as long before he starts to drown (the air meter empties at half speed). Off: the N64 air time.' },
  { key: 'longspin', label: 'Longer tail spin', def: false, game: 5,
    help: 'Holding A during the helicopter tail spin (A, then A again in the air) keeps Conker hovering about twice as long before he drops. Off: the N64 hover time.' },
  { key: 'nodrunk', label: 'No motion blur / drunk sway', def: false, game: 6,
    help: 'Turns off the frame-blend motion blur (the hangover wake-up after the opening, a slow-motion camera cut) and the drunk camera sway and screen stretching (drunk Conker, the title menu). The under-water wobble stays. Off: as on the N64.' },
  { key: 'conkerlod', label: 'Conker always full detail', def: false, game: 7,
    help: 'Conker is always drawn with his most detailed model. Off: as on the N64, he switches to simpler models once the camera is more than 500 units away (the normal follow camera is often 450 to 650 units behind him, more while running).' },
  { key: 'airbar', label: 'Underwater air meter', def: false, game: 8,
    help: 'While Conker is under water, a bar at the top of the screen shows the air he has left: full when he dives, red in the last quarter, empty when he starts to drown. Works with Longer breath. Off: as on the N64, only the wobbly air bubble meter, which appears after about 2 s and already looks empty at half the air.' },
  { key: 'rumble', label: 'Rumble (gamepad vibration)', def: false, game: 13,
    help: 'The game sees a Rumble Pak in each controller and your gamepad vibrates when the N64 one would (hits, explosions, heavy landings), if the browser supports gamepad vibration (Chrome / Edge with most Xbox and PlayStation pads). Takes effect at the next level or area load. Off: as now, no Rumble Pak. Saves are not affected.' },
  { key: 'crosshair', label: 'Aiming crosshair', def: false, game: 14,
    help: 'Shows the game\'s small crosshair in the middle of the screen in the first-person aim views that have none (R with the weapon kind 0x18), where the shots go. Takes effect the next time you aim. Off: as on the N64, no crosshair there; the other weapons keep their own reticles.' },
  { key: 'swiminvert', label: 'Inverted swimming', def: false, game: 12,
    help: 'Under water, pushing the stick up makes Conker swim up and pulling it down makes him dive. Off: as on the N64, which steers like a plane: up dives, down rises.' },
  // P332: sliders (range: true): the value 0..100 (%) goes to the game through the same port_set_option channel.
  { key: 'volmusic', label: 'Music volume', def: 100, range: true, game: 9,
    help: 'Volume of the music (the sequenced songs), 0 to 100 %. 100 % = as on the N64.' },
  { key: 'volsfx', label: 'Sound effects volume', def: 100, range: true, game: 10,
    help: 'Volume of the sound effects (footsteps, hits, ambience, short grunts), 0 to 100 %. 100 % = as on the N64.' },
  { key: 'volspeech', label: 'Speech volume', def: 100, range: true, game: 11,
    help: 'Volume of the spoken dialogue (the MP3 voice streams), 0 to 100 %. 100 % = as on the N64.' },
];
const optOverride = {};
for (const kv of (Q.get('opt') || '').split(',')) {
  const [k, v] = kv.split(':'), o = OPTIONS.find((x) => x.key === k);
  if (k) optOverride[k] = o && o.range ? Math.max(0, Math.min(100, parseInt(v, 10) || 0)) : v === '1';
}
const optCache = {};   // opt() is read every animation frame by the input code: cache, refreshed on change
const opt = (key) => {
  if (key in optCache) return optCache[key];
  const o = OPTIONS.find((x) => x.key === key);
  if (NETDET) return (optCache[key] = o.def);   // P337: the session's fixed options vector
  if (netCfg && o.game !== undefined) return (optCache[key] = netCfg.options && key in netCfg.options ? netCfg.options[key] : o.def);   // P338: the host's
  return (optCache[key] = key in optOverride ? optOverride[key] : store.get('opt.' + key, o.def));
};
let optionsLocked = false;   // P337: under ?netdet the vector is sent once before callMain, never changed afterwards
function sendOption(o) {
  if (optionsLocked) return;
  if (o.game !== undefined && M && M._port_set_option) M._port_set_option(o.game, o.range ? opt(o.key) | 0 : opt(o.key) ? 1 : 0);
}
const optionChanged = {};   // key -> callback for page-side options that need to react at once
(function renderOptions() {
  for (const o of OPTIONS) {
    const l = document.createElement('label'), c = document.createElement('input'), t = document.createElement('span');
    if (o.range) {   // P332 slider: 0..100 %, sent while dragging, saved on release
      c.type = 'range'; c.min = 0; c.max = 100; c.step = 5; c.value = opt(o.key); c.id = 'opt-' + o.key;
      const pct = document.createElement('b'); pct.textContent = ` ${c.value} %`;
      c.oninput = () => { delete optOverride[o.key]; optCache[o.key] = +c.value; pct.textContent = ` ${c.value} %`; sendOption(o); };
      c.onchange = () => { store.set('opt.' + o.key, +c.value); log(`[options] ${o.key} ${c.value}`); };
      t.textContent = o.label; t.appendChild(pct);
      const h = document.createElement('small'); h.textContent = o.help; t.appendChild(h);
      l.append(t, c); $('options').appendChild(l);
      continue;
    }
    c.type = 'checkbox'; c.checked = opt(o.key); c.id = 'opt-' + o.key;
    c.onchange = () => {
      delete optOverride[o.key]; store.set('opt.' + o.key, c.checked); optCache[o.key] = c.checked;
      sendOption(o); if (optionChanged[o.key]) optionChanged[o.key](c.checked);
      log(`[options] ${o.key} ${c.checked ? 'on' : 'off'}`);
    };
    t.textContent = o.label;
    const h = document.createElement('small'); h.textContent = o.help; t.appendChild(h);
    l.append(c, t); $('options').appendChild(l);
  }
})();

// ---------------------------------------------------------------- IndexedDB (ROM cache, saves)
let dbp = null;
function db() {
  if (!dbp) dbp = new Promise((res, rej) => {
    const r = indexedDB.open('conker-port', 2);
    r.onupgradeneeded = () => {
      const d = r.result;
      if (!d.objectStoreNames.contains('rom')) d.createObjectStore('rom');
      if (!d.objectStoreNames.contains('saves')) d.createObjectStore('saves');
    };
    r.onerror = () => rej(r.error);
    r.onsuccess = () => res(r.result);
  });
  return dbp;
}
async function idb(storeName, mode, fn) {
  const d = await db();
  return new Promise((res, rej) => {
    const tx = d.transaction(storeName, mode);
    const q = fn(tx.objectStore(storeName));
    tx.oncomplete = () => res(q && q.result);
    tx.onerror = () => rej(tx.error);
  });
}

// ---------------------------------------------------------------- ROM: byte order, SHA-1, drop zone
function toZ64(b) {
  const m = (b[0] << 24 | b[1] << 16 | b[2] << 8 | b[3]) >>> 0;
  if (m === 0x80371240) return b;
  const o = new Uint8Array(b.length);
  if (m === 0x37804012) { for (let i = 0; i < b.length; i += 2) { o[i] = b[i + 1]; o[i + 1] = b[i]; } return o; } // .v64
  if (m === 0x40123780) { for (let i = 0; i < b.length; i += 4) { o[i] = b[i + 3]; o[i + 1] = b[i + 2]; o[i + 2] = b[i + 1]; o[i + 3] = b[i]; } return o; } // .n64
  throw new Error('not an N64 ROM (magic ' + m.toString(16) + ')');
}
async function sha1(b) {
  if (!crypto.subtle) return '?';
  const h = new Uint8Array(await crypto.subtle.digest('SHA-1', b));
  return Array.from(h, (x) => x.toString(16).padStart(2, '0')).join('');
}
async function setRom(bytes, from) {
  romBytes = toZ64(bytes);
  romSha1 = await sha1(romBytes);
  romOk = romSha1 === EU_SHA1;
  const mb = (romBytes.length / 1048576).toFixed(0);
  if (romOk) status(`ROM: Conker EU, SHA-1 ok (${mb} MB, ${from})`, 'ok');
  else status(`ROM SHA-1 ${romSha1.slice(0, 12)}… is not the EU ROM (${from})`, 'bad');
  $('drop').hidden = romOk;
  $('start').disabled = !!running || !romOk;
  $('eep-export').disabled = !romOk;
  return romOk;
}
async function takeFile(f) {
  if (!f) return;
  try {
    const ok = await setRom(new Uint8Array(await f.arrayBuffer()), f.name);
    if (ok) await idb('rom', 'readwrite', (s) => s.put(romBytes, 'eu')).catch(() => {});
  } catch (err) { status('ROM: ' + err.message, 'bad'); log('ROM: ' + err.message, 'fail'); }
}
$('rom').addEventListener('change', (e) => takeFile(e.target.files[0]));
// iOS greys out files whose extension has no known type (.z64 / .n64 / .eep), so no filter there;
// the ROM is checked by SHA-1 anyway
const IOS = /iPad|iPhone|iPod/.test(navigator.userAgent) || (navigator.platform === 'MacIntel' && navigator.maxTouchPoints > 1);
if (IOS) {
  for (const id of ['rom', 'eep-import']) $(id).removeAttribute('accept');
}
{
  const dz = $('drop');
  const over = (on) => (e) => { e.preventDefault(); dz.classList.toggle('over', on); };
  document.addEventListener('dragover', over(true));
  document.addEventListener('dragleave', (e) => { if (!e.relatedTarget) dz.classList.remove('over'); });
  document.addEventListener('drop', (e) => {
    e.preventDefault(); dz.classList.remove('over');
    const f = e.dataTransfer && e.dataTransfer.files[0];
    if (!f) return;
    if (/\.eep$/i.test(f.name)) importEep(f); else if (!running) takeFile(f);
  });
}

// ---------------------------------------------------------------- input -> PIF pad state
// N64 button bits (PR/os_cont.h)
const N64 = { A: 0x8000, B: 0x4000, Z: 0x2000, START: 0x1000, DU: 0x0800, DD: 0x0400, DL: 0x0200, DR: 0x0100,
              L: 0x0020, R: 0x0010, CU: 0x0008, CD: 0x0004, CL: 0x0002, CR: 0x0001 };
const INPUTS = [  // [id, label]; stick directions are pseudo-buttons
  ['UP', 'Stick up'], ['DOWN', 'Stick down'], ['LEFT', 'Stick left'], ['RIGHT', 'Stick right'], ['HALF', 'Half tilt'],
  ['A', 'A'], ['B', 'B'], ['Z', 'Z'], ['L', 'L'], ['R', 'R'], ['START', 'Start'],
  ['CU', 'C up'], ['CD', 'C down'], ['CL', 'C left'], ['CR', 'C right'],
  ['DU', 'D-pad up'], ['DD', 'D-pad down'], ['DL', 'D-pad left'], ['DR', 'D-pad right'],
];
const DEFAULT_KEYS = { UP: 'KeyW', DOWN: 'KeyS', LEFT: 'KeyA', RIGHT: 'KeyD', HALF: 'ControlLeft',
  A: 'Space', B: 'KeyF', Z: 'KeyQ', L: 'KeyR', R: 'KeyE', START: 'Enter',
  CU: 'KeyI', CD: 'KeyK', CL: 'KeyJ', CR: 'KeyL', DU: 'ArrowUp', DD: 'ArrowDown', DL: 'ArrowLeft', DR: 'ArrowRight' };
// W3C Standard Gamepad: 0 A/cross, 1 B/circle, 2 X/square, 3 Y/triangle, 4 LB, 5 RB, 6 LT, 7 RT,
// 8 back, 9 start, 12-15 d-pad. Left stick = N64 stick, right stick = C-buttons (always on).
const DEFAULT_PAD = { A: 0, B: 2, Z: 6, L: 4, R: 5, START: 9, CD: 1, CL: 3, DU: 12, DD: 13, DL: 14, DR: 15 };
let keyMap = Object.assign({}, DEFAULT_KEYS, store.get('keys', {}));
let padMap = Object.assign({}, DEFAULT_PAD, store.get('padbuttons', {}));
const keysDown = new Set();
let listening = null; // [kind, id, button] while remapping

const STICK = 80;   // typical full deflection of an N64 stick (raw range about +-85)
// unit-disc vector -> N64 counts inside the octagonal gate: 80 on the axes, (70, 70) at the corners
function octagon(x, y) {
  const m = Math.min(1, Math.hypot(x, y)), ax = Math.abs(x), ay = Math.abs(y), mx = Math.max(ax, ay);
  if (m < 1e-6) return [0, 0];
  const k = m * STICK * (1 - 0.125 * Math.min(ax, ay) / mx) / mx;
  return [Math.round(x * k), Math.round(y * k)];
}
function keyboardPad() {
  let b = 0, x = 0, y = 0;
  const on = (id) => keyMap[id] && keysDown.has(keyMap[id]);
  for (const [id] of INPUTS) if (N64[id] && on(id)) b |= N64[id];
  x = (on('RIGHT') ? 1 : 0) - (on('LEFT') ? 1 : 0);
  y = (on('UP') ? 1 : 0) - (on('DOWN') ? 1 : 0);
  let [sx, sy] = octagon(x, y);
  if (on('HALF') && !opt('togglewalk')) { sx = Math.round(sx / 2); sy = Math.round(sy / 2); }  // latched: see applyLatches
  return { present: true, b, x: sx, y: sy, half: !!on('HALF') };
}
function gamepadPad(gp) {
  let b = 0;
  const pressed = (i) => gp.buttons[i] && (gp.buttons[i].pressed || gp.buttons[i].value > 0.5);
  for (const id in padMap) if (N64[id] && pressed(padMap[id])) b |= N64[id];
  const ax = (i) => (gp.axes[i] || 0);
  // left stick: radial dead zone 0.15, rescaled, N64 y is up-positive
  let x = ax(0), y = -ax(1), m = Math.hypot(x, y);
  if (m < 0.15) { x = y = 0; } else { const s = Math.min(1, (m - 0.15) / 0.85) / m; x *= s; y *= s; }
  const [sx, sy] = octagon(x, y);
  // right stick -> C-buttons
  if (ax(2) > 0.5) b |= N64.CR; if (ax(2) < -0.5) b |= N64.CL;
  if (ax(3) > 0.5) b |= N64.CD; if (ax(3) < -0.5) b |= N64.CU;
  return { present: true, b, x: sx, y: sy };
}
// ---------------------------------------------------------------- touch controls (phones / tablets)
// Floating stick: the first touch in the left zone sets the centre, dragging up to STICK_PX gives full tilt.
// Buttons hold their bit while touched; each uses its own pointer, so several can be held at once.
const touch = { b: 0, x: 0, y: 0, stickId: null, cx: 0, cy: 0 };
const STICK_PX = 50;
function setTouch(on) {
  $('touch').hidden = !on;
  document.body.classList.toggle('touch', on);
  $('t-touch').setAttribute('aria-pressed', String(on));
  store.set('touch', on);
  if (!on) { touch.b = touch.x = touch.y = 0; touch.stickId = null; }
}
const capture = (el, e) => { try { el.setPointerCapture(e.pointerId); } catch (_) { /* synthetic or already gone */ } };
(function initTouch() {
  for (const el of document.querySelectorAll('#touch .tb')) {
    const bit = N64[el.id.slice(3)];
    const ids = new Set();
    const down = (e) => {
      e.preventDefault(); capture(el, e); ids.add(e.pointerId);
      touch.b |= bit; el.classList.add('on'); if (navigator.vibrate) navigator.vibrate(8);
    };
    const up = (e) => { ids.delete(e.pointerId); if (!ids.size) { touch.b &= ~bit; el.classList.remove('on'); } };
    el.addEventListener('pointerdown', down);
    for (const ev of ['pointerup', 'pointercancel', 'lostpointercapture']) el.addEventListener(ev, up);
  }
  const zone = $('tk-stick'), base = $('tk-base'), knob = $('tk-knob');
  const place = (x, y) => { const r = zone.getBoundingClientRect(); base.style.left = (x - r.left) + 'px'; base.style.top = (y - r.top) + 'px'; };
  const rest = () => { const r = zone.getBoundingClientRect(); place(r.left + 90, r.top + r.height - 80); knob.style.transform = ''; };
  const move = (e) => {
    if (e.pointerId !== touch.stickId) return;
    let dx = e.clientX - touch.cx, dy = e.clientY - touch.cy;
    const m = Math.hypot(dx, dy);
    if (m > STICK_PX) { dx *= STICK_PX / m; dy *= STICK_PX / m; }
    knob.style.transform = `translate(${dx}px, ${dy}px)`;
    let x = dx / STICK_PX, y = -dy / STICK_PX;
    if (Math.hypot(x, y) < 0.12) x = y = 0;   // small dead zone
    [touch.x, touch.y] = octagon(x, y);
  };
  zone.addEventListener('pointerdown', (e) => {
    e.preventDefault();
    if (touch.stickId !== null) return;
    capture(zone, e);
    touch.stickId = e.pointerId; touch.cx = e.clientX; touch.cy = e.clientY;
    place(e.clientX, e.clientY); knob.style.transform = '';
  });
  zone.addEventListener('pointermove', move);
  const end = (e) => { if (e.pointerId !== touch.stickId) return; touch.stickId = null; touch.x = touch.y = 0; rest(); };
  for (const ev of ['pointerup', 'pointercancel', 'lostpointercapture']) zone.addEventListener(ev, end);
  window.addEventListener('resize', () => { if (touch.stickId === null) rest(); });
  $('touch').addEventListener('contextmenu', (e) => e.preventDefault());
  $('t-touch').onclick = () => { setTouch($('touch').hidden); if (!$('touch').hidden) rest(); };
  const coarse = window.matchMedia && matchMedia('(pointer: coarse)').matches;
  setTouch(Q.get('touch') ? Q.get('touch') === '1' : store.get('touch', coarse));
  rest();
})();

// ---------------------------------------------------------------- P324 toggle options (crouch / R-Look / walk)
// With a toggle option on, the bound input of pad 1 (keyboard, first gamepad and touch merged) latches: each new
// press (raw input goes from up to down) flips the latch, and the game sees the button held / the stick at half
// tilt for as long as the latch is on, whatever the raw input does in between. Off: the raw input passes through
// unchanged and any latch is dropped. Small labels in #latches show which latches are on.
const LATCHES = [
  { key: 'togglecrouch', bit: N64.Z, name: 'Crouch' },
  { key: 'togglerlook', bit: N64.R, name: 'R-Look' },
  { key: 'togglewalk', bit: 0, name: 'Walk' },   // bit 0 = the half-tilt pseudo-button (stick at half)
];
const latch = {}, latchPrev = {};
let latchText = '';
function applyLatches(p, halfHeld) {
  for (const l of LATCHES) {
    const raw = l.bit ? (p.b & l.bit) !== 0 : halfHeld;
    if (!opt(l.key)) latch[l.key] = false;
    else if (raw && !latchPrev[l.key]) latch[l.key] = !latch[l.key];
    latchPrev[l.key] = raw;
    if (!opt(l.key)) continue;
    if (l.bit) p.b = latch[l.key] ? p.b | l.bit : p.b & ~l.bit;
    else if (latch[l.key]) { p.x = Math.round(p.x / 2); p.y = Math.round(p.y / 2); }
  }
  const txt = LATCHES.filter((l) => latch[l.key]).map((l) => l.name).join(' ');
  if (txt !== latchText) {
    latchText = txt; $('latches').textContent = '';
    for (const n of txt ? txt.split(' ') : []) { const e = document.createElement('span'); e.textContent = n; $('latches').appendChild(e); }
    $('latches').hidden = !txt;
    for (const l of LATCHES) if (l.bit) { const tb = $('tk-' + (l.bit === N64.Z ? 'Z' : 'R')); tb.classList.toggle('latched', !!latch[l.key]); }
  }
  return p;
}

const SKIP_ARC = 2 * Math.PI * 27;
$('skiparc').style.strokeDasharray = String(SKIP_ARC);
let lastPadText = '';
function pollInput() {
  const gps = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).filter((g) => g && g.connected);
  if (listening && listening[0] === 'pad') {
    for (const gp of gps) gp.buttons.forEach((bt, i) => { if (bt.pressed && listening) finishListen(i); });
  }
  // pad 0 = keyboard merged with the first gamepad; pads 1-3 = further gamepads
  const pads = [keyboardPad(), null, null, null];
  const halfHeld = pads[0].half;   // the half-tilt key (P324 walk toggle)
  if (touch.b || touch.x || touch.y) { const k = pads[0]; pads[0] = { present: true, b: k.b | touch.b, x: k.x || touch.x, y: k.y || touch.y }; }
  gps.forEach((gp, i) => {
    const g = gamepadPad(gp);
    if (i === 0) { const k = pads[0]; pads[0] = { present: true, b: k.b | g.b, x: k.x || g.x, y: k.y || g.y }; }
    else if (i < 4) pads[i] = g;
  });
  applyLatches(pads[0], halfHeld);
  const txt = gps.length ? gps.map((g, i) => `pad ${i + 1}: ${g.id.slice(0, 40)}${g.mapping === 'standard' ? '' : ' (non-standard mapping)'}`).join('\n') : 'no gamepad (press a button on it to connect)';
  if (txt !== lastPadText) { $('pads').textContent = txt; lastPadText = txt; }
  if (M && M._port_skip_progress) {  // P321: ring while L is held over a skippable cutscene
    const pr = M._port_skip_progress(), ring = $('skipring');
    if (pr > 0) $('skiparc').style.strokeDashoffset = String(SKIP_ARC * (1 - Math.min(1, pr)));
    if (ring.hasAttribute('hidden') !== !(pr > 0)) ring.toggleAttribute('hidden', !(pr > 0));  // SVG: no .hidden property
  }
  if (netCfg && window.PortNet && PortNet.M) PortNet.setLocalPad(pads[0].b, pads[0].x, pads[0].y);   // P338: this peer's pad -> the ring
  else if (M && M._port_pad_state && !NETDET) {   // P337: under ?netdet the pads come only from the frame-indexed scripts
    const p = M._port_pad_state() >> 2, H = M.HEAP32;
    for (let i = 0; i < 4; i++) {
      const d = pads[i];
      H[p + i * 4] = i === 0 || d ? 1 : 0;
      H[p + i * 4 + 1] = d ? d.b : 0; H[p + i * 4 + 2] = d ? d.x : 0; H[p + i * 4 + 3] = d ? d.y : 0;
    }
  }
  requestAnimationFrame(pollInput);
}
requestAnimationFrame(pollInput);
const boundCodes = () => new Set(Object.values(keyMap));
const typing = (e) => /^(INPUT|TEXTAREA|SELECT)$/.test(e.target.tagName) && e.target.type !== 'range';
window.addEventListener('keydown', (e) => {
  if (listening && listening[0] === 'key') { e.preventDefault(); if (e.code !== 'Escape') finishListen(e.code); else finishListen(null); return; }
  if (typing(e)) return;
  if (e.code === 'F11' || (e.code === 'KeyF' && e.altKey)) { e.preventDefault(); fullscreen(); return; }
  if (e.code === 'Escape' && running === 'game' && !document.fullscreenElement) { setPaused(!userPaused); return; }
  keysDown.add(e.code);
  if (running && boundCodes().has(e.code)) e.preventDefault();  // no page scrolling on Space / arrows
});
window.addEventListener('keyup', (e) => { keysDown.delete(e.code); });
window.addEventListener('blur', () => keysDown.clear());

// remap panel
const keyName = (c) => !c ? '—' : c.replace(/^(Key|Digit)/, '').replace(/^Arrow/, 'Arrow ');
const padName = (i) => i === undefined || i === null ? '—' : ['A', 'B', 'X', 'Y', 'LB', 'RB', 'LT', 'RT', 'Back', 'Start', 'LS', 'RS', 'D↑', 'D↓', 'D←', 'D→', 'Home'][i] || 'btn ' + i;
function renderBinds() {
  const tb = $('binds');
  tb.textContent = '';
  for (const [id, label] of INPUTS) {
    const tr = document.createElement('tr');
    const k = document.createElement('button'), g = document.createElement('button');
    k.textContent = keyName(keyMap[id]);
    k.onclick = () => startListen('key', id, k);
    const stickDir = ['UP', 'DOWN', 'LEFT', 'RIGHT', 'HALF'].includes(id);
    g.textContent = stickDir ? (id === 'HALF' ? '—' : 'left stick') : padName(padMap[id]);
    g.disabled = stickDir;
    if (!stickDir) g.onclick = () => startListen('pad', id, g);
    const td0 = document.createElement('td'); td0.textContent = label;
    const td1 = document.createElement('td'), td2 = document.createElement('td');
    td1.appendChild(k); td2.appendChild(g);
    tr.append(td0, td1, td2); tb.appendChild(tr);
  }
}
function startListen(kind, id, btn) {
  if (listening) listening[2].classList.remove('listen');
  listening = [kind, id, btn];
  btn.classList.add('listen');
  btn.textContent = kind === 'key' ? 'press a key… (Esc clears)' : 'press a pad button…';
}
function finishListen(v) {
  const [kind, id] = listening;
  listening = null;
  if (kind === 'key') {
    for (const k in keyMap) if (v && keyMap[k] === v) delete keyMap[k];   // one N64 input per key
    if (v) keyMap[id] = v; else delete keyMap[id];
    store.set('keys', diff(keyMap, DEFAULT_KEYS));
  } else {
    for (const k in padMap) if (padMap[k] === v) delete padMap[k];
    padMap[id] = v;
    store.set('padbuttons', diff(padMap, DEFAULT_PAD));
  }
  renderBinds();
}
function diff(m, d) {  // stored = differences from the defaults (null = unbound)
  const o = {};
  for (const k of new Set([...Object.keys(m), ...Object.keys(d)])) if (m[k] !== d[k]) o[k] = m[k] === undefined ? null : m[k];
  return o;
}
function cleanMap(m) { for (const k in m) if (m[k] === null) delete m[k]; return m; }
cleanMap(keyMap); cleanMap(padMap);
$('bind-reset').onclick = () => { keyMap = Object.assign({}, DEFAULT_KEYS); padMap = Object.assign({}, DEFAULT_PAD); store.set('keys', {}); store.set('padbuttons', {}); renderBinds(); };
renderBinds();

// ---------------------------------------------------------------- EEPROM saves
const slot = Q.get('slot') || '0';
const saveKey = () => `${romSha1}/eeprom/${slot}`;
let eepTimer = null, eepWrites = 0;
const eepStatus = (s) => { $('eep-status').textContent = s; };
function eepBytes() {
  const n = M._port_eeprom_size(), p = M._port_eeprom_ptr();
  return M.HEAPU8.slice(p, p + n);
}
// P324 option "Autosave icon": the game wrote an EEPROM block (portEepDirty, once per block): show the icon and keep
// it up until 1.5 s after the last block of this save.
let saveIconTimer = null;
function flashSaveIcon() {
  if (!opt('saveicon')) return;
  $('saveicon').toggleAttribute('hidden', false);  // SVG: no .hidden property
  clearTimeout(saveIconTimer);
  saveIconTimer = setTimeout(() => $('saveicon').toggleAttribute('hidden', true), 1500);
}
async function persistEeprom() {
  eepTimer = null;
  if (!M || !romSha1 || saveBlocked) return;
  const b = eepBytes();
  if (Q.get('eepdump')) log(`[eepdump] ${eepWrites} ${Array.from(b, (x) => x.toString(16).padStart(2, '0')).join('')}`);  // P240 TEST: hex image per save (feed back with ?eephex=)
  try { await idb('saves', 'readwrite', (s) => s.put(b, saveKey())); log(`[eep] saved ${b.length} bytes to IndexedDB (${saveKey()}), ${eepWrites} block writes`); eepStatus(`Saved ${new Date().toLocaleTimeString()} (slot ${slot}).`); }
  catch (e) { log('[eep] save failed: ' + e, 'fail'); eepStatus('Save failed: ' + e); }
}
let saveBlocked = false;  // set when the save could not be read: never overwrite it with a blank EEPROM
async function loadEeprom(Mod) {
  try {
    const hx = Q.get('eephex');   // P240 TEST ?eephex=HEX (4096 hex digits, e.g. from an [eepdump] line): boot with this EEPROM
    if (hx) {
      const n = Mod._port_eeprom_size(), p = Mod._port_eeprom_ptr(), m = Math.min(n, hx.length >> 1);
      for (let i = 0; i < m; i++) Mod.HEAPU8[p + i] = parseInt(hx.substr(i * 2, 2), 16);
      log(`[eep] loaded ${m} bytes from ?eephex`); return;
    }
    // IndexedDB can stall (headless --virtual-time-budget, blocked storage): do not hold the boot on it
    const b = await Promise.race([idb('saves', 'readonly', (s) => s.get(saveKey())),
      new Promise((_, rej) => setTimeout(() => rej(new Error('IndexedDB did not answer in 3 s')), 3000))]);
    if (b && b.length) {
      const n = Mod._port_eeprom_size(), p = Mod._port_eeprom_ptr();
      Mod.HEAPU8.set(b.subarray(0, n), p);
      log(`[eep] loaded ${b.length} bytes from IndexedDB (${saveKey()})`);
      eepStatus(`Loaded the save of slot ${slot}.`);
    } else log(`[eep] no save for ${saveKey()}: blank EEPROM`);
  } catch (e) {
    saveBlocked = true;
    log('[eep] load failed: ' + e.message + '; saving is off for this session', 'fail');
    eepStatus('Could not read the save storage: saving is off for this session (export still works).');
  }
}
$('eep-export').onclick = async () => {
  let b = M ? eepBytes() : await idb('saves', 'readonly', (s) => s.get(saveKey())).catch(() => null);
  if (!b) { eepStatus('No save yet.'); return; }
  const a = document.createElement('a');
  a.href = URL.createObjectURL(new Blob([b], { type: 'application/octet-stream' }));
  a.download = `conker-eu-slot${slot}.eep`;
  document.body.appendChild(a); a.click(); a.remove();
  setTimeout(() => URL.revokeObjectURL(a.href), 5000);
};
async function importEep(f) {
  if (!f) return;
  if (!romSha1) { eepStatus('Load the ROM first.'); return; }
  const raw = new Uint8Array(await f.arrayBuffer());
  if (raw.length !== 2048 && raw.length !== 512) { eepStatus(`Not an EEPROM image (${raw.length} bytes; expected 2048).`); return; }
  const b = new Uint8Array(2048); b.set(raw);
  await idb('saves', 'readwrite', (s) => s.put(b, saveKey()));
  log(`[eep] imported ${f.name} (${raw.length} bytes) into ${saveKey()}`);
  if (running === 'game') { eepStatus('Imported. Reloading so the game reads it at boot…'); setTimeout(() => location.reload(), 600); }
  else eepStatus(`Imported ${f.name}; it loads when the game starts.`);
}
$('eep-import').addEventListener('change', (e) => importEep(e.target.files[0]));

// ---------------------------------------------------------------- fullscreen, pause, volume, audio
function fullscreen() {
  // with touch controls on, the whole page goes fullscreen (the controls live outside #screen)
  const s = document.body.classList.contains('touch') ? document.documentElement : $('screen');
  if (document.fullscreenElement) document.exitFullscreen();
  else if (s.requestFullscreen) {
    s.requestFullscreen().then(() => {
      if (s === document.documentElement && screen.orientation && screen.orientation.lock) screen.orientation.lock('landscape').catch(() => {});
    }).catch((e) => log('fullscreen: ' + e.message, 'fail'));
  }
}
document.addEventListener('fullscreenchange', () => {
  document.body.classList.toggle('fs', document.fullscreenElement === document.documentElement);
});
$('fullscreen').onclick = fullscreen;
$('canvas').addEventListener('dblclick', fullscreen);

// P333 option "Rumble": pc_pif.c answers the game's Rumble Pak commands and calls Module.portRumble(channel, on) when
// the motor starts / stops (on the N64 the game pulses it: on for a few frames, off for a few, by strength). Channel 0
// is the keyboard + first gamepad, channel i the gamepad i. Chrome: vibrationActuator.playEffect('dual-rumble');
// Firefox-style: hapticActuators[0].pulse. A long effect is started on "start" and cut by reset() on "stop", so the
// gamepad follows the motor's on / off pattern. window.portRumbleStats counts what happened (headless tests).
const rumbleStats = window.portRumbleStats = { start: 0, stop: 0, played: 0, logged: 0 };
const rumbleMotor = [false, false, false, false];
// Test aid ?p333pad=1: a fake standard gamepad with a vibrationActuator that only counts and logs the calls, so a
// headless run (no real gamepad) shows the playEffect / reset calls the option makes.
if (Q.get('p333pad') === '1') {
  const fake = { id: 'P333 test pad (fake vibrationActuator)', index: 0, connected: true, mapping: 'standard', timestamp: 0,
    buttons: Array.from({ length: 17 }, () => ({ pressed: false, touched: false, value: 0 })), axes: [0, 0, 0, 0],
    vibrationActuator: { type: 'dual-rumble',
      playEffect: (type, p) => { rumbleStats.fakePlay = (rumbleStats.fakePlay || 0) + 1; if (rumbleStats.fakePlay <= 12) log(`[rumble-page] playEffect('${type}', ${JSON.stringify(p)}) #${rumbleStats.fakePlay}`); return Promise.resolve('complete'); },
      reset: () => { rumbleStats.fakeReset = (rumbleStats.fakeReset || 0) + 1; if (rumbleStats.fakeReset <= 12) log(`[rumble-page] reset() #${rumbleStats.fakeReset}`); return Promise.resolve('complete'); } } };
  navigator.getGamepads = () => [fake];
}
function rumbleGamepad(ch) {
  const gps = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).filter((g) => g && g.connected);
  return gps[ch] || null;
}
function rumbleSet(ch, on) {
  const gp = rumbleGamepad(ch), act = gp && gp.vibrationActuator, hap = gp && gp.hapticActuators && gp.hapticActuators[0];
  let played = false;
  try {
    if (on && act && act.playEffect) { act.playEffect('dual-rumble', { startDelay: 0, duration: 5000, strongMagnitude: 1.0, weakMagnitude: 0.6 }).catch(() => {}); played = true; }
    else if (on && hap && hap.pulse) { hap.pulse(1.0, 5000); played = true; }
    else if (!on && act) { if (act.reset) act.reset().catch(() => {}); else act.playEffect('dual-rumble', { duration: 0, strongMagnitude: 0, weakMagnitude: 0 }).catch(() => {}); }
    else if (!on && hap && hap.pulse) hap.pulse(0, 1);
  } catch (e) { /* no vibration support */ }
  return played;
}
function portRumble(ch, on) {
  rumbleMotor[ch] = !!on;
  const paused = userPaused || hiddenPaused;
  const played = on && !paused ? rumbleSet(ch, true) : (rumbleSet(ch, false), false);
  if (on) rumbleStats.start++; else rumbleStats.stop++;
  if (played) rumbleStats.played++;
  if (rumbleStats.logged++ < 40) log(`[rumble-page] ch ${ch} ${on ? 'start' : 'stop'}: gamepad ${rumbleGamepad(ch) ? 'yes' : 'none'}, effect ${played ? 'played' : 'not played'} (starts ${rumbleStats.start}, stops ${rumbleStats.stop}, played ${rumbleStats.played})`);
}
function rumbleStopAll() { for (let ch = 0; ch < 4; ch++) if (rumbleMotor[ch]) rumbleSet(ch, false); }
optionChanged.rumble = (on) => { if (!on) { rumbleStopAll(); rumbleMotor.fill(false); } };

let userPaused = false, hiddenPaused = false;
function applyPause() {
  const p = userPaused || hiddenPaused;
  if (M && M._port_set_paused) M._port_set_paused(p ? 1 : 0);
  if (p) rumbleStopAll();   // P333: no vibration while the page is paused
  const a = window.portAudio;
  if (a && a.ctx) { if (p) a.ctx.suspend().catch(() => {}); else if (gestured) a.ctx.resume().catch(() => {}); }
  $('paused').hidden = !p || running !== 'game';
  $('pause').setAttribute('aria-pressed', String(userPaused));
  $('pause').textContent = userPaused ? 'Resume' : 'Pause';
}
function setPaused(p) { userPaused = p; applyPause(); }
$('pause').onclick = () => setPaused(!userPaused);
document.addEventListener('visibilitychange', () => {
  if (netCfg && window.PortNet && PortNet.M) {   // P338: never pause a session; P339: net.js ticks the game from a worker
    PortNet.background(document.hidden);          // while the page is hidden (hidden pages' timers are throttled to ~1 Hz)
    if (hiddenPaused) { hiddenPaused = false; applyPause(); }
    return;
  }
  if (Q.get('nohidepause')) return;  // dev flag: keep running in a background tab
  hiddenPaused = document.hidden; applyPause();
  log(`[page] tab ${document.hidden ? 'hidden: paused' : 'visible: resumed'}`);
});

window.portVolume = store.get('volume', 80) / 100;
if (Q.get('mute')) window.portVolume = 0;  // P271: test runs pass ?mute=1 (audprobe.sh does by default): gain 0
$('volume').value = Math.round(window.portVolume * 100);
$('volume').addEventListener('input', (e) => {
  window.portVolume = e.target.value / 100;
  store.set('volume', +e.target.value);
  const a = window.portAudio;
  if (a && a.gain) a.gain.gain.value = window.portVolume;
});

// Browsers start an AudioContext only after a user gesture. The game opens its context at the first
// audio buffer (port/audio/aud_out.c); the first click / key press resumes it, and a context opened
// after that gesture starts at once (sticky activation).
// iOS (every iOS browser is WebKit) keeps a context created outside a gesture suspended for good, and
// mutes Web Audio when the ring switch is on silent. So on iOS: mark the page as media playback, create
// the context inside the first tap, unlock it with a silent buffer, and hand that context to the game
// when it asks for one (port/audio/aud_out.c resamples if the rate differs).
let preCtx = null;
if (IOS) {
  try { if (navigator.audioSession) navigator.audioSession.type = 'playback'; } catch (e) { /* older iOS */ }
  for (const k of ['AudioContext', 'webkitAudioContext']) {
    const Orig = window[k];
    if (!Orig) continue;
    window[k] = function (opts) { if (preCtx) { const c = preCtx; preCtx = null; return c; } return new Orig(opts); };
    window[k].prototype = Orig.prototype;
  }
}
function unlockIosAudio() {
  if (!IOS || window.portAudio) return;
  if (preCtx) { if (preCtx.state !== 'running') preCtx.resume().catch(() => {}); return; }
  const C = (window.AudioContext || window.webkitAudioContext).prototype.constructor;
  try {
    const c = new C();
    const b = c.createBuffer(1, 1, 22050), src = c.createBufferSource();
    src.buffer = b; src.connect(c.destination); src.start(0);
    c.resume().catch(() => {});
    preCtx = c;
    log('[audio] iOS: context unlocked by tap: ' + c.state);
  } catch (e) { log('[audio] iOS unlock failed: ' + e, 'fail'); }
}
let gestured = false;
function onGesture() {
  gestured = true;
  unlockIosAudio();
  const a = window.portAudio;
  if (a && a.ctx && a.ctx.state !== 'running' && !(userPaused || hiddenPaused)) {
    a.ctx.resume().then(() => log('[audio] context resumed by user gesture: ' + a.ctx.state)).catch(() => {});
  }
  updateSoundHint();
}
for (const ev of ['pointerdown', 'pointerup', 'keydown', 'touchend', 'click']) window.addEventListener(ev, onGesture, true);
function updateSoundHint() {
  const a = window.portAudio;
  $('soundhint').hidden = !(a && a.ctx && a.ctx.state !== 'running' && !(userPaused || hiddenPaused));
}
window.portAudioReady = (ctx) => {
  log(`[audio] context created: ${ctx.state}${gestured ? ' (after a gesture)' : ''}`);
  ctx.addEventListener('statechange', updateSoundHint);
  if (gestured && ctx.state !== 'running') ctx.resume().catch(() => {});
  updateSoundHint();
};

// ---------------------------------------------------------------- P337 online multiplayer phase 0
// The state hash (port/ultra/pc_nethash.c) leaves out the port-only static ranges listed in conker_netx.txt
// (port/tools/net_regions.py, written by the build next to conker.wasm). window.__netdump reads the hashed memory after
// ?nethashstop paused the game (port/web/audprobe.js PROBE_DUMP -> tools/port/nethash_diff.py).
async function netLoadExclusions(Mod) {
  try {
    const t = await (await fetch('conker_netx.txt')).text(); let n = 0;
    for (const l of t.split('\n')) { const f = l.split(' '); if (f.length >= 2) { Mod._port_net_exclude(parseInt(f[0], 16), parseInt(f[1], 16)); n++; } }
    log(`[nethash] ${n} excluded static ranges from conker_netx.txt`);
  } catch (e) { log('[nethash] conker_netx.txt not loaded: ' + e, 'fail'); }
}
window.__netdump = {
  info() {
    const regions = [];
    for (let i = 0; M._port_net_region(i, 0) !== -1; i++) {
      const a = M._port_net_region(i, 0) >>> 0, l = M._port_net_region(i, 1);
      if (l) regions.push({ i, addr: a, len: l });
    }
    const fm = /\bnethashstop=(\d+)/.exec(location.search);
    return { frame: fm ? +fm[1] : 0, regions };
  },
  chunk(addr, len) {
    const b = M.HEAPU8.subarray(addr, addr + len); let s = '';
    for (let i = 0; i < b.length; i += 32768) s += String.fromCharCode.apply(null, b.subarray(i, i + 32768));
    return btoa(s);
  },
};

// ---------------------------------------------------------------- P338 online session (port/web/net.js)
// window.__online is what the Online panel's buttons call (and tools/port/scripts/netpair.js, which plays both sides
// of a session in one browser). Host = controller 1; P344: up to 3 guests, each with the controller slot (2..4) the host
// gave it with its code. The host dictates the session: game options, its EEPROM image (user save data, never ROM
// bytes), the input delay. The host checks every guest's build id (SHA-256 of conker.wasm) and ROM SHA-256 before
// anything starts. Test aids: ?netd=D input delay (host), ?neteep=blank.
const netEvents = { status: [], tick: [], desync: [], desyncReport: [], left: [], roster: [] };   // the Online panel subscribes here
const sha256hex = async (buf) => Array.from(new Uint8Array(await crypto.subtle.digest('SHA-256', buf)), (b) => b.toString(16).padStart(2, '0')).join('');
async function netLoad() {
  if (!window.PortNet) await loadScript('net.js');
  if (!PortNet.buildId) {
    PortNet.buildId = (await sha256hex(await (await fetch('conker.wasm')).arrayBuffer())).slice(0, 16);
    PortNet.romSha256 = await sha256hex(romBytes);
    PortNet.log = log;
    for (const ev of Object.keys(netEvents)) PortNet.t.on[ev] = (...a) => { for (const f of netEvents[ev]) f(...a); };
    PortNet.t.on.config = (cfg) => {   // both peers: boot the game into the session
      netCfg = cfg;
      for (const k of Object.keys(optCache)) delete optCache[k];
      log(`[net] session config: channels ${cfg.mask} (players ${(cfg.roster || []).map((c) => c + 1).join(' ')}), mine ${cfg.local}, delay ${cfg.delay}${cfg.autoDelay ? ` (auto, ping ${cfg.ping} ms)` : ''}, EEPROM ${cfg.eeprom ? 'host image' : 'blank'}`);
      start('game');
    };
  }
}
// ---- the Online panel (shown by the option "Online multiplayer")
const showOnlineButton = (on) => { $('t-online').hidden = !on; if (!on && !$('p-online').hidden) toggle('online', false); };
optionChanged.online = showOnlineButton;
showOnlineButton(opt('online') || !!Q.get('netpanel'));
const netStatus = (s, cls) => { $('net-status').textContent = s; $('net-status').className = cls || ''; };
const copyCode = (id) => { const t = $(id); t.select(); (navigator.clipboard ? navigator.clipboard.writeText(t.value) : Promise.reject()).catch(() => document.execCommand('copy')); };
const netGuard = async (fn) => { try { await fn(); } catch (e) { netStatus(String(e.message || e), 'bad'); log('[net] ' + e, 'fail'); } };
$('net-delay').value = store.get('netdelay', 3);
$('net-delay').onchange = () => store.set('netdelay', Math.max(1, Math.min(16, +$('net-delay').value | 0)));
$('net-delay-auto').checked = store.get('netdelayauto', true);   // P339: automatic input delay from the measured ping
$('net-delay').disabled = $('net-delay-auto').checked;
$('net-delay-auto').onchange = () => { store.set('netdelayauto', $('net-delay-auto').checked); $('net-delay').disabled = $('net-delay-auto').checked; };
// P344: the host's panel lists the guest slots (players 2..4): each with its offer code, the answer box and its state
$('net-host').onclick = () => netGuard(async () => {
  netNeedRom();   // before the buttons are disabled, so the player can load the ROM and try again
  $('net-step-host').hidden = false; $('net-step-join').hidden = true; $('net-host').disabled = $('net-join').disabled = true;
  netShowSlot(await window.__online.invite());
});
$('net-invite').onclick = () => netGuard(async () => { $('net-invite').disabled = true; try { netShowSlot(await window.__online.invite()); } finally { $('net-invite').disabled = false; } });
$('net-start').onclick = () => netGuard(async () => { $('net-start').disabled = $('net-invite').disabled = true; await window.__online.start(); });
function netSlotBox(ch) {
  let e = $('net-slot-' + (ch + 1));
  if (e) return e;
  const n = ch + 1;
  e = document.createElement('div'); e.className = 'netslot'; e.id = 'net-slot-' + n;
  e.innerHTML = `<div class="row"><b>Player ${n}</b><span id="net-slot-${n}-state" class="netslotstate">invited</span></div>
    <div id="net-slot-${n}-codes"><label>1. Send this code to player ${n} <button id="net-offer-copy-${n}">Copy</button></label>
    <textarea id="net-offer-${n}" readonly rows="2"></textarea>
    <label>2. Paste player ${n}'s answer code here</label>
    <textarea id="net-answer-in-${n}" rows="2"></textarea>
    <div class="row"><button id="net-accept-${n}" class="primary">Connect player ${n}</button></div></div>`;
  $('net-slots').appendChild(e);
  $('net-offer-copy-' + n).onclick = () => copyCode('net-offer-' + n);
  $('net-accept-' + n).onclick = () => netGuard(async () => { await window.__online.accept($('net-answer-in-' + n).value); $('net-accept-' + n).disabled = true; });
  return e;
}
function netShowSlot({ ch, code }) {
  netSlotBox(ch);
  const n = ch + 1;
  $('net-slot-' + n + '-codes').hidden = false; $('net-accept-' + n).disabled = false;
  $('net-offer-' + n).value = code; $('net-answer-in-' + n).value = '';
}
const NET_SLOT_TEXT = { invited: 'invited: waiting for the answer code', connecting: 'connecting…', connected: 'connected, checking the game build…',
  joined: 'joined', left: 'left', failed: 'could not connect' };
netEvents.roster.push((slots) => {   // host
  let joined = 0;
  for (const s of slots) {
    netSlotBox(s.ch);
    const n = s.ch + 1;
    if (s.state === 'joined') joined++;
    $('net-slot-' + n + '-codes').hidden = !['invited', 'connecting', 'failed'].includes(s.state);
    $('net-slot-' + n + '-state').textContent = (NET_SLOT_TEXT[s.state] || s.state) + (s.why && s.state !== 'joined' ? ` (${s.why})` : '') +
      (s.rtt && s.state === 'joined' ? ` · ping ${s.rtt} ms` : '') + (s.relay && s.relay.length ? ` · through player 1 with ${s.relay.map((k) => k.split('-').filter((c) => +c !== s.ch).map((c) => 'player ' + (+c + 1))).join(', ')}` : '');
  }
  if (!window.PortNet || !PortNet.t.started) { $('net-start').disabled = !joined; $('net-start').textContent = `Start the game (${joined + 1} players)`; }
  else $('net-host-actions').hidden = true;   // the game started: no more invitations
  $('net-invite').disabled = slots.length >= 3 && slots.every((s) => !['left', 'failed'].includes(s.state));
});
$('net-join').onclick = () => { $('net-step-join').hidden = false; $('net-step-host').hidden = true; $('net-host').disabled = $('net-join').disabled = true; };
$('net-answer-make').onclick = () => netGuard(async () => { netNeedRom(); $('net-answer-make').disabled = true; $('net-answer').value = await window.__online.join($('net-offer-in').value); });
$('net-answer-copy').onclick = () => copyCode('net-answer');
$('net-leave').onclick = () => { window.__online.leave(); $('net-leave').hidden = true; };
netEvents.status.push((s, cls) => {
  netStatus(s, cls);
  if (/^(connected|joined as)/.test(s) || (window.PortNet && PortNet.t.started)) { $('net-step-join').hidden = true; $('net-leave').hidden = false; }
});
let netWaitSince = 0;
netEvents.tick.push((t) => {   // ~100 Hz from net.js
  const now = performance.now();
  if (!t.waiting) netWaitSince = 0; else if (!netWaitSince) netWaitSince = now;
  $('netwait').hidden = !(netWaitSince && now - netWaitSince > 400);
  if (!$('netwait').hidden) {   // P344: name the players the game waits for
    const w = (t.peers || []).filter((p) => p.waiting).map((p) => 'player ' + (p.ch + 1));
    $('netwait').textContent = `waiting for ${w.length ? w.join(', ') : 'the other players'}…`;
  }
  if (now - (netEvents.lastInfo || 0) > 500) {
    netEvents.lastInfo = now;
    $('net-info').textContent = `you are player ${PortNet.t.myCh + 1} · retrace ${t.frame} · waits ${t.stalls} · input delay ${netCfg ? netCfg.delay * 20 + ' ms' + (netCfg.autoDelay ? ' (auto)' : '') : '–'}`;
    // P344: every other player's ping (and who the game waits for)
    $('net-peers').textContent = (t.peers || []).map((p) => `player ${p.ch + 1}: ${p.lost ? 'left (stands still)' : (p.rtt ? 'ping ' + p.rtt + ' ms' : 'ping –') +
      (PortNet.t.routes && Object.entries(PortNet.t.routes).some(([k, v]) => v === 'relay' && k.split('-').map(Number).includes(p.ch) && k.split('-').map(Number).includes(PortNet.t.myCh)) ? ' (through player 1)' : '') +
      (p.waiting ? ' · waiting' : '')}`).join(' · ');
  }
});
netEvents.desync.push((d) => {
  const e = $('net-desync'); if (!e.hidden) return;   // P339: reported once (both peers detect it)
  e.hidden = false;
  e.textContent = `Desync at retrace ${d.frame} with player ${(d.ch || 0) + 1}: this game ${d.mine.map((x) => (x >>> 0).toString(16)).join(' ')}, the other ${d.theirs.map((x) => (x >>> 0).toString(16)).join(' ')}. ` +
    'The two games no longer show the same thing; please report it (open Debug for the log).';
});
netEvents.desyncReport.push((r) => {   // P339: where the two games differ (net.js comparePages)
  const e = $('net-desync'); e.hidden = false;
  e.textContent += ` Where: ${r.where}; ${r.pages} memory page(s) and ${r.stacks.length} thread stack(s) differ.`;
});
netEvents.left.push(() => { if (PortNet.t.left) { $('netwait').hidden = true; $('net-leave').hidden = true; } });   // P344: alone now
// Host / Join compare ROM hashes, so the ROM must be loaded first (without it the hash call failed with a
// SubtleCrypto "not an ArrayBuffer" error).
function netNeedRom() {
  if (!romBytes) throw new Error('load your ROM first ("Choose ROM file…" or drop the file on the page), then Host / Join');
  if (!romOk) throw new Error('this ROM is not the Conker EU ROM; both players need the EU ROM');
  if (!crypto.subtle) throw new Error('this page needs a secure (https) connection for online play');
}
window.__online = {
  ready: () => !!romBytes && !running,
  // host: start hosting, returns player 2's offer code (P344: __online.invite() for players 3 and 4, then start())
  async host() { return (await window.__online.invite()).code; },
  async invite() {   // host: {ch, code} for the next free slot
    if (window.PortNet && PortNet.t.role === 'host') return PortNet.invite();
    if (running) throw new Error('the game already runs: reload the page, then host before pressing Start');
    netNeedRom();
    await netLoad();
    return PortNet.host(async ({ ping, mask }) => {   // ping: {n, min, median, p90} ms of the slowest pair (or null)
      const options = {};
      for (const o of OPTIONS) if (o.game !== undefined) options[o.key] = opt(o.key);
      let eeprom = null;
      if (Q.get('neteep') !== 'blank') try { const b = await idb('saves', 'readonly', (s) => s.get(saveKey())); if (b && b.length) eeprom = new Uint8Array(b); } catch (e) { /* no save */ }
      // P339: input delay automatic from the measured ping (panel checkbox, default on) or the panel's field;
      // ?netd=D / ?netd=auto (tests) wins
      const auto = Q.get('netd') ? Q.get('netd') === 'auto' : $('net-delay-auto').checked;
      const d = auto ? PortNet.autoDelay(ping) : +(Q.get('netd') || $('net-delay').value || 3);
      return { mask, delay: Math.max(1, Math.min(16, d | 0)), autoDelay: auto, hashEvery: 10, options, eeprom };
    });
  },
  async join(code) {
    if (running) throw new Error('the game already runs: reload the page, then join before pressing Start');
    netNeedRom();
    await netLoad();
    return PortNet.join(code);
  },
  accept: (code) => PortNet.accept(code),   // host: a guest's answer code; returns its channel
  start: () => PortNet.start(),             // host: P344 start the game with every joined player
  slots: () => window.PortNet ? PortNet.slots() : [],
  leave: () => window.PortNet && PortNet.t && PortNet.leave(),
  stats() {
    if (!window.PortNet || !PortNet.t) return null;
    const t = PortNet.t, on = PortNet.M && PortNet.base.input !== undefined;
    const hs = on ? PortNet.hashes() : [], h = hs[hs.length - 1];
    return { state: t.state, me: t.myCh + 1, frame: on ? PortNet.frame() : 0, rtt: Math.round(t.rtt), stalledTicks: on ? PortNet.stat(0) : 0,
      stalledSlots: on ? PortNet.stat(1) : 0, sent: t.sent, recv: t.recv, relayed: t.relayed, simDropped: t.simDropped, hashChecked: t.myHashSeen,
      lastHash: h ? `${h.f}:${h.h.toString(16)}:${h.s.toString(16)}` : '', desync: t.desync, desyncReport: t.desyncReport || null, left: t.left,
      slowedMs: on ? PortNet.stat(7) : 0, waits: on ? PortNet.stat(8) : 0, waitMs: on ? PortNet.stat(9) : 0,
      peers: Object.values(t.peers).map((p) => ({ p: p.ch + 1, rtt: Math.round(p.rtt), m: +p.myMargin.toFixed(2), pm: +p.peerMargin.toFixed(2), lost: p.lost })),
      routes: t.routes };   // P339 time sync, P344 per player
  },
};

// ---------------------------------------------------------------- wasm apps
function loadScript(src) {
  return new Promise((res, rej) => {
    const s = document.createElement('script');
    s.src = src; s.onload = res; s.onerror = () => rej(new Error('cannot load ' + src));
    document.head.appendChild(s);
  });
}
async function start(app) {
  if (running) { location.search = '?app=' + app; return; } // one module per page
  running = app;
  $('demo').disabled = $('start').disabled = true;
  $('drop').hidden = true;
  status(app === 'game' ? 'starting…' : 'scheduler demo', 'ok');
  if (netCfg && app === 'game' && !window.PortNet) await loadScript('net.js');   // P338 (the Online panel loaded it already)
  const [js, factory] = app === 'demo' ? ['sched_demo.js', 'createSchedDemo'] : ['conker.js', 'createConker'];
  log(`-- loading ${js}`);
  await loadScript(js);
  const Mod = await window[factory]({
    canvas: $('canvas'),
    print: (s) => log(s),
    printErr: (s) => log(s, 'fail'),
    onAbort: (w) => { log('Aborted: ' + w, 'fail'); status('crashed (open Debug)', 'bad'); },
    portRumble: (ch, on) => portRumble(ch, on),   // P333 option "Rumble" (pc_pif.c)
    portEepDirty: () => { eepWrites++; if (!eepTimer) eepTimer = setTimeout(persistEeprom, 400); flashSaveIcon(); },
  });
  window.Module = M = Mod;
  for (const o of OPTIONS) sendOption(o);   // before callMain: the game reads them from its first frame
  optionsLocked = NETDET || !!netCfg;
  log('[options] ' + OPTIONS.map((o) => `${o.key}=${o.range ? opt(o.key) : opt(o.key) ? 1 : 0}`).join(' '));
  if (app === 'game' && romBytes) {
    const p = M._malloc(romBytes.length);
    M.HEAPU8.set(romBytes, p);
    M._port_set_rom(p, romBytes.length);
    if (NETDET) { saveBlocked = true; log('[netdet] blank EEPROM, saves stay in this session'); }   // P337 sandbox
    else if (netCfg) {   // P338: the host's EEPROM image (or blank); saves stay in this session
      saveBlocked = true;
      if (netCfg.eeprom) M.HEAPU8.set(netCfg.eeprom.subarray(0, M._port_eeprom_size()), M._port_eeprom_ptr());
      log(`[net] ${netCfg.eeprom ? "host's" : 'blank'} EEPROM, saves stay in this session`);
    } else await loadEeprom(M);
  }
  $('threads').disabled = false;
  $('threads').onclick = () => M._port_dump_threads();
  $('pause').disabled = app !== 'game';
  // &audonly=1 (P14, audprobe.sh): data segments only, no game threads; for the audio tests
  if (Q.get('audonly')) log('audonly: game memory ' + (M._port_audio_prepare() > 0 ? 'loaded' : 'FAILED') + ', game not started');
  else {
    if (netCfg || /[?&](nethash|nethashstop|netsnap)=/.test(location.search)) await netLoadExclusions(M);   // P337
    if (netCfg) PortNet.begin(M, netCfg, log);   // P338: session before the first retrace
    try { M.callMain([]); } catch (e) { if (e !== 'unwind') log(String(e), 'fail'); }
  }
  if (app === 'game') status('running', 'ok');
  if (netCfg && netCfg.loop) PortNet.loopback(netCfg.loop);   // P338 test peer
  else if (netCfg) PortNet.startTransport();                    // P338 online: send / receive inputs
  if (netCfg && hiddenPaused) { hiddenPaused = false; applyPause(); }   // P339: the page was hidden before the session
                                                                        // (a covered window): a session never pauses
  applyPause();
  $('canvas').focus();
  // &audtest=HEX[:FRAMES]: n_audio synth + audio HLE test (port/audio/aud_test.c);
  // &voicetest=HEX[:CALLS] (P14): voice clip through the stream handler, MP3 decoder and MP3 ABI.
  // Without &audprobe they run on the next click (a user gesture, so the audio can start).
  const at = Q.get('audtest'), vt = Q.get('voicetest');
  const run = at ? () => { const [r, f] = at.split(':'); M._port_audio_test(parseInt(r, 16), +(f || 150)); }
            : vt ? () => { const [r, f] = vt.split(':'); M._port_voice_test(parseInt(r, 16), +(f || 2000)); } : null;
  if (app === 'game' && run) {
    if (Q.get('audprobe')) { log('audprobe: starting the audio test without a click'); setTimeout(run, 500); }
    else {
      log('audio test: click the page to synthesise and play it');
      document.addEventListener('click', run, { once: true });
    }
  }
  // &eeptest=w:SEED / r:SEED (P27 test aid): EEPROM write / read-back through the PIF commands, 2 s after start
  const et = Q.get('eeptest');
  if (app === 'game' && et) setTimeout(() => M._port_eep_test(et[0] === 'w' ? 1 : 2, parseInt(et.slice(2), 10) || 1), 2000);
}

// &audprobe=1 (P14, test aid): count what the Web Audio graph actually pulls. Every
// ScriptProcessorNode's onaudioprocess is wrapped; after the original handler fills outputBuffer, the
// probe counts callbacks, frames and non-zero samples and the rms, and logs a summary line
// ("[audprobe] ...") every second. port/web/audprobe.sh.
function installAudioProbe() {
  const st = { ctx: 0, nodes: 0, calls: 0, frames: 0, nonzero: 0, sq: 0, peak: 0, rate: 0, state: '' };
  window.audprobe = st;
  for (const name of ['AudioContext', 'webkitAudioContext']) {
    const C = window[name];
    if (!C || C.prototype.__probed) continue;
    C.prototype.__probed = true;
    const orig = C.prototype.createScriptProcessor;
    C.prototype.createScriptProcessor = function (...a) {
      const node = orig.apply(this, a), ctx = this;
      st.nodes++; st.rate = ctx.sampleRate;
      ctx.addEventListener('statechange', () => { st.state = ctx.state; });
      let user = null;
      const wrapped = (e) => {
        if (user) user.call(node, e);
        st.calls++; st.state = ctx.state;
        const b = e.outputBuffer;
        st.frames += b.length;
        for (let c = 0; c < b.numberOfChannels; c++) {
          const d = b.getChannelData(c);
          for (let i = 0; i < d.length; i++) {
            const v = d[i];
            if (v !== 0) { st.nonzero++; st.sq += v * v; if (Math.abs(v) > st.peak) st.peak = Math.abs(v); }
          }
        }
      };
      Object.defineProperty(node, 'onaudioprocess', {
        get: () => user, set: (f) => { user = f; node.addEventListener('audioprocess', wrapped); }, configurable: true,
      });
      return node;
    };
    const Orig = C;
    window[name] = function (...a) { st.ctx++; const c = new Orig(...a); st.state = c.state; return c; };
    window[name].prototype = Orig.prototype;
  }
  setInterval(() => {
    if (!st.calls && !st.ctx) return;
    const rms = st.nonzero ? Math.sqrt(st.sq / st.nonzero) : 0;
    log(`[audprobe] contexts ${st.ctx} nodes ${st.nodes} rate ${st.rate} state ${st.state}: ${st.calls} callbacks, ` +
        `${st.frames} frames pulled, ${st.nonzero} non-zero samples, rms ${rms.toFixed(4)} peak ${st.peak.toFixed(3)}`);
  }, 1000);
}
if (Q.get('audprobe')) installAudioProbe();
$('demo').onclick = () => start('demo');
$('start').onclick = () => start('game');

(async () => {
  if (!Q.get('romurl')) try {
    const cached = await idb('rom', 'readonly', (s) => s.get('eu'));
    if (cached) await setRom(new Uint8Array(cached), 'cached in this browser');
  } catch (e) { /* no IndexedDB: fine */ }
  // dev/test aid: &romurl=PATH fetches the ROM from the (local) server instead of the picker; it is
  // not cached. Used by the headless browser tests with a read-only mount (docs/port/design/P4.md).
  if (Q.get('romurl')) {
    try { await setRom(new Uint8Array(await (await fetch(Q.get('romurl'))).arrayBuffer()), 'dev romurl'); }
    catch (e) { log('romurl: ' + e.message, 'fail'); }
  }
  // &dump=MS: dump threads + the ranked stub-hit list after MS milliseconds
  if (Q.get('dump')) setTimeout(() => window.Module && window.Module._port_dump_threads(), +Q.get('dump'));
  const app = Q.get('app');
  if (app === 'demo' || (app === 'game' && romBytes)) start(app);
})();

// P19: show the wasm stack of an uncaught error on the page (the console text alone has no stack)
window.addEventListener('error', (e) => {
  log(String(e.message || e), 'fail');
  const st = e.error && e.error.stack ? String(e.error.stack).split('\n').slice(0, 12).join('\n') : '';
  if (st) try { log('[error] ' + st, 'fail'); } catch (_) { console.error(st); }
});
