// Page glue for the Conker wasm32 port. The ROM is supplied by the user and never leaves the browser
// (cached in IndexedDB). Two wasm apps: the scheduler demo and the game; one per page load.
// P27: ROM drop zone, input (keyboard + Gamepad API -> PIF pad state), EEPROM saves in IndexedDB,
// fullscreen / pause / volume, debug console behind a toggle, audio resume on the first gesture.
'use strict';
const EU_SHA1 = 'ee7bc6656fd1e1d9ffb3d19add759f28b88df710';
const $ = (id) => document.getElementById(id);
const Q = new URLSearchParams(location.search);
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
  $('side').hidden = ['controls', 'saves', 'debug'].every((n) => $('p-' + n).hidden);
  if (name === 'debug') { store.set('debug', on); if (on) out.scrollTop = out.scrollHeight; }
}
for (const n of ['controls', 'saves', 'debug']) $('t-' + n).onclick = () => toggle(n);
if (Q.get('debug') === '1' || (Q.get('debug') !== '0' && store.get('debug', false))) toggle('debug', true);

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
  if (on('HALF')) { sx = Math.round(sx / 2); sy = Math.round(sy / 2); }
  return { present: true, b, x: sx, y: sy };
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
let lastPadText = '';
function pollInput() {
  const gps = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).filter((g) => g && g.connected);
  if (listening && listening[0] === 'pad') {
    for (const gp of gps) gp.buttons.forEach((bt, i) => { if (bt.pressed && listening) finishListen(i); });
  }
  // pad 0 = keyboard merged with the first gamepad; pads 1-3 = further gamepads
  const pads = [keyboardPad(), null, null, null];
  gps.forEach((gp, i) => {
    const g = gamepadPad(gp);
    if (i === 0) { const k = pads[0]; pads[0] = { present: true, b: k.b | g.b, x: k.x || g.x, y: k.y || g.y }; }
    else if (i < 4) pads[i] = g;
  });
  const txt = gps.length ? gps.map((g, i) => `pad ${i + 1}: ${g.id.slice(0, 40)}${g.mapping === 'standard' ? '' : ' (non-standard mapping)'}`).join('\n') : 'no gamepad (press a button on it to connect)';
  if (txt !== lastPadText) { $('pads').textContent = txt; lastPadText = txt; }
  if (M && M._port_pad_state) {
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
  const s = $('screen');
  if (document.fullscreenElement) document.exitFullscreen();
  else if (s.requestFullscreen) s.requestFullscreen().catch((e) => log('fullscreen: ' + e.message, 'fail'));
}
$('fullscreen').onclick = fullscreen;
$('canvas').addEventListener('dblclick', fullscreen);

let userPaused = false, hiddenPaused = false;
function applyPause() {
  const p = userPaused || hiddenPaused;
  if (M && M._port_set_paused) M._port_set_paused(p ? 1 : 0);
  const a = window.portAudio;
  if (a && a.ctx) { if (p) a.ctx.suspend().catch(() => {}); else if (gestured) a.ctx.resume().catch(() => {}); }
  $('paused').hidden = !p || running !== 'game';
  $('pause').setAttribute('aria-pressed', String(userPaused));
  $('pause').textContent = userPaused ? 'Resume' : 'Pause';
}
function setPaused(p) { userPaused = p; applyPause(); }
$('pause').onclick = () => setPaused(!userPaused);
document.addEventListener('visibilitychange', () => {
  if (Q.get('nohidepause')) return;  // dev flag: keep running in a background tab
  hiddenPaused = document.hidden; applyPause();
  log(`[page] tab ${document.hidden ? 'hidden: paused' : 'visible: resumed'}`);
});

window.portVolume = store.get('volume', 80) / 100;
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
let gestured = false;
function onGesture() {
  gestured = true;
  const a = window.portAudio;
  if (a && a.ctx && a.ctx.state !== 'running' && !(userPaused || hiddenPaused)) {
    a.ctx.resume().then(() => log('[audio] context resumed by user gesture: ' + a.ctx.state)).catch(() => {});
  }
  updateSoundHint();
}
for (const ev of ['pointerdown', 'keydown', 'touchend']) window.addEventListener(ev, onGesture, true);
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
  const [js, factory] = app === 'demo' ? ['sched_demo.js', 'createSchedDemo'] : ['conker.js', 'createConker'];
  log(`-- loading ${js}`);
  await loadScript(js);
  const Mod = await window[factory]({
    canvas: $('canvas'),
    print: (s) => log(s),
    printErr: (s) => log(s, 'fail'),
    onAbort: (w) => { log('Aborted: ' + w, 'fail'); status('crashed (open Debug)', 'bad'); },
    portEepDirty: () => { eepWrites++; if (!eepTimer) eepTimer = setTimeout(persistEeprom, 400); },
  });
  window.Module = M = Mod;
  if (app === 'game' && romBytes) {
    const p = M._malloc(romBytes.length);
    M.HEAPU8.set(romBytes, p);
    M._port_set_rom(p, romBytes.length);
    await loadEeprom(M);
  }
  $('threads').disabled = false;
  $('threads').onclick = () => M._port_dump_threads();
  $('pause').disabled = app !== 'game';
  // &audonly=1 (P14, audprobe.sh): data segments only, no game threads; for the audio tests
  if (Q.get('audonly')) log('audonly: game memory ' + (M._port_audio_prepare() > 0 ? 'loaded' : 'FAILED') + ', game not started');
  else try { M.callMain([]); } catch (e) { if (e !== 'unwind') log(String(e), 'fail'); }
  if (app === 'game') status('running', 'ok');
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
  // not cached. Used by the headless browser tests with a read-only mount (docs/port/sessions/P4.md).
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
