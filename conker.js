// This code implements the `-sMODULARIZE` settings by taking the generated
// JS program code (INNER_JS_CODE) and wrapping it in a factory function.

// When targetting node and ES6 we use `await import ..` in the generated code
// so the outer function needs to be marked as async.
async function createConker(moduleArg = {}) {
  var moduleRtn;

// include: shell.js
// The Module object: Our interface to the outside world. We import
// and export values on it. There are various ways Module can be used:
// 1. Not defined. We create it here
// 2. A function parameter, function(moduleArg) => Promise<Module>
// 3. pre-run appended it, var Module = {}; ..generated code..
// 4. External script tag defines var Module.
// We need to check if Module already exists (e.g. case 3 above).
// Substitution will be replaced with actual code on later stage of the build,
// this way Closure Compiler will not mangle it (e.g. case 4. above).
// Note that if you want to run closure, and also to use Module
// after the generated code, you will need to define   var Module = {};
// before the code. Then that object will be used in the code, and you
// can continue to use Module afterwards as well.
var Module = moduleArg;

// Determine the runtime environment we are in. You can customize this by
// setting the ENVIRONMENT setting at compile time (see settings.js).

var ENVIRONMENT_IS_WEB = false;
var ENVIRONMENT_IS_WORKER = true;
var ENVIRONMENT_IS_NODE = false;
var ENVIRONMENT_IS_SHELL = false;

// --pre-jses are emitted after the Module integration code, so that they can
// refer to Module (if they choose; they can also define Module)
// include: web/rtw/rtw_glue.js
// P376 retrowser.app build: the worker-side half of port/web/main.js (Emscripten --pre-js, only in the rtw build).
// The game runs in the host's dedicated worker (no DOM): the host calls conker.wasm's rtw_* exports (port/ultra/pc_rtw.c)
// and this object does what the page's JS did around them:
//   - the input tick (main.js pollInput, once per animation frame of the worker): raw host pads (N64 OSContPad bits +
//     the manifest's extra buttons) -> octagonal stick gate, toggle latches, free camera stick, photo mode camera,
//     the PIF pads (port_pad_state / port_cam_state) or the recorder's pad (port_net_addr(3));
//   - photo mode (main.js photoPoll / photoCapture): PHOTO button, camera, A = PNG at twice the picture's resolution
//     (OffscreenCanvas.convertToBlob) -> rtw_export_file ("Saved files" in the host);
//   - picture size (main.js layoutScreen) from rtw_resize and the Widescreen / Full-resolution options;
//   - the input recorder (main.js rec*): option "Input recorder" records from power-on; the extra button "Save
//     recording" (or turning the option off) ends it and hands the .ckrec file to the host (rtw_export_file);
//   - conker_netx.txt (files.data) -> port_net_exclude before the first retrace (photo mode's snapshot, the recorder's hash).
// Left out (no host interface in retrowser v1): online play (net.js, W11), the page overlays (game-style menus, save
// icon, hold-L ring, photo Pose / Outfit panel), recording replays (no way to hand a file to the game).
var rtwGlue = (function () {
  'use strict';
  const N64 = { A: 0x8000, B: 0x4000, Z: 0x2000, START: 0x1000, DU: 0x0800, DD: 0x0400, DL: 0x0200, DR: 0x0100,
    L: 0x0020, R: 0x0010, CU: 0x0008, CD: 0x0004, CL: 0x0002, CR: 0x0001 };
  const C_BITS = N64.CU | N64.CD | N64.CL | N64.CR;
  // controls.extra in retrowser.json (bits 16..31 of rtw_input's buttons)
  const EXTRA = { PHOTO: 1 << 16, CAMZOOM: 1 << 17, CAMBACK: 1 << 18, HALF: 1 << 19, RECSAVE: 1 << 20 };
  // rtw_option ids: the game options are the PORT_OPT_* ids (port/ultra/port_options.h, main.js `game:`), the
  // page-side ones start at 100 (pc_rtw.c RTW_PAGE_OPT_BASE)
  const OPT = { FREECAM: 15, PHOTOMODE: 16, HIRES2D: 100, SMOOTHFONT: 101, WIDESCREEN: 102, FULLRES: 103, HFR: 104,
    TOGGLECROUCH: 105, TOGGLERLOOK: 106, TOGGLEWALK: 107, RECORDER: 108 };
  // main.js OPTIONS keys of the game options, for the recording's header (e2e_replay.js applies them by key)
  const GAME_OPTION_KEYS = { 0: 'skipcut', 1: 'skipintro', 2: 'healthhud', 3: 'cashhud', 4: 'longbreath', 5: 'longspin',
    17: 'ledgegrab', 6: 'nodrunk', 7: 'conkerlod', 8: 'airbar', 13: 'rumble', 14: 'crosshair', 15: 'freecam',
    16: 'photomode', 12: 'swiminvert', 9: 'volmusic', 10: 'volsfx', 11: 'volspeech' };
  const RANGE_OPTIONS = new Set([9, 10, 11]);
  const PAGE_OPTION_KEYS = { 100: 'hires2d', 101: 'smoothfont', 102: 'widescreen', 103: 'fullres', 104: 'hfr',
    105: 'togglecrouch', 106: 'togglerlook', 107: 'togglewalk' };
  const STICK = 80;   // typical full deflection of an N64 stick (main.js)

  const optionValues = {};   // id -> value, as the host set them
  const opt = (id) => optionValues[id] | 0;
  const view = { width: 640, height: 480, dpr100: 100 };
  let started = false, glUp = false, hostPaused = false, pointerLocked = false;

  const wasm = (name) => Module['_' + name];
  function log(text) {
    try {
      if (!wasm('port_rtw_log') || !wasm('malloc')) { out(text); return; }
      const p = stringToNewUTF8(String(text));
      wasm('port_rtw_log')(p);
      wasm('free')(p);
    } catch (e) { out(String(text)); }
  }
  // a file for the player: the bytes are copied into wasm memory and go through env.rtw_export_file (pc_rtw.c)
  function exportFile(name, mime, bytes) {
    const p = wasm('malloc')(bytes.length || 1), n = stringToNewUTF8(name), m = stringToNewUTF8(mime);
    try {
      HEAPU8.set(bytes, p);
      return wasm('port_rtw_export_file')(n, m, p, bytes.length);
    } finally { wasm('free')(p); wasm('free')(n); wasm('free')(m); }
  }
  const hex = (u8) => Array.from(u8, (b) => b.toString(16).padStart(2, '0')).join('');
  const digestHex = async (algo, bytes) => hex(new Uint8Array(await crypto.subtle.digest(algo, bytes)));
  const b64enc = (u8) => { let t = ''; for (let i = 0; i < u8.length; i += 32768) t += String.fromCharCode.apply(null, u8.subarray(i, i + 32768)); return btoa(t); };
  const stamp = (t) => { const p2 = (n) => String(n).padStart(2, '0'); return `${t.getFullYear()}${p2(t.getMonth() + 1)}${p2(t.getDate())}-${p2(t.getHours())}${p2(t.getMinutes())}${p2(t.getSeconds())}`; };

  // ------------------------------------------------------------------ picture size (main.js layoutScreen)
  // Off: 640 x 480. Widescreen: 480 rows, the view's aspect between 4:3 and 21:9. Full-resolution: the picture's size in
  // the view times devicePixelRatio, at most 2560 x 1440. The host shows the buffer with object-fit: contain.
  function layout() {
    const canvas = Module['canvas'];
    if (!canvas || photo.busy) return;
    let aspect = 4 / 3, w = 640, h = 480;
    if (opt(OPT.WIDESCREEN)) {
      aspect = Math.max(4 / 3, Math.min(64 / 27, view.height > 0 ? view.width / view.height : 16 / 9));
      w = Math.round(h * aspect / 2) * 2;
    }
    if (opt(OPT.FULLRES) && view.width > 0 && view.height > 0) {
      const dpr = Math.max(1, view.dpr100 / 100);
      let fw = Math.min(view.width, view.height * aspect) * dpr, fh = fw / aspect;
      const k = Math.min(1, 2560 / fw, 1440 / fh);
      fw *= k; fh *= k;
      if (fh >= 240) { w = Math.round(fw / 2) * 2; h = Math.round(fh / 2) * 2; }
    }
    if (canvas.width !== w || canvas.height !== h) {
      canvas.width = w; canvas.height = h;
      wasm('port_gfx_resize')(w, h);
      log(`[widescreen] canvas ${w} x ${h} (aspect ${aspect.toFixed(3)})`);
    }
    wasm('port_gfx_widescreen')(opt(OPT.WIDESCREEN) ? 1 : 0);
  }

  // ------------------------------------------------------------------ input (main.js keyboardPad / gamepadPad / pollInput)
  // unit-disc vector -> N64 counts inside the octagonal gate: 80 on the axes, (70, 70) at the corners
  function octagon(x, y) {
    const m = Math.min(1, Math.hypot(x, y)), ax = Math.abs(x), ay = Math.abs(y), mx = Math.max(ax, ay);
    if (m < 1e-6) return [0, 0];
    const k = m * STICK * (1 - 0.125 * Math.min(ax, ay) / mx) / mx;
    return [Math.round(x * k), Math.round(y * k)];
  }
  const freeCameraOn = () => !!opt(OPT.FREECAM) && !rec.active;   // P357: never while recording
  const photoModeOn = () => !!opt(OPT.PHOTOMODE) && !rec.active;
  // one host pad (rtw_input: active-high N64 bits, extras in bits 16.., stick -127..127, up positive) -> main.js's pad object
  function hostPad(buttons, sx, sy) {
    let b = buttons & 0xFFFF;
    let [x, y] = octagon(Math.max(-1, Math.min(1, sx / 127)), Math.max(-1, Math.min(1, sy / 127)));
    const half = (buttons & EXTRA.HALF) !== 0;
    if (half && !opt(OPT.TOGGLEWALK)) { x = Math.round(x / 2); y = Math.round(y / 2); }   // latched: see applyLatches
    let cx = 0, cy = 0;
    if (freeCameraOn()) {   // P347: the C buttons (the host's right stick or C keys) become the camera stick
      cx = ((b & N64.CR) ? STICK : 0) - ((b & N64.CL) ? STICK : 0);
      cy = ((b & N64.CU) ? STICK : 0) - ((b & N64.CD) ? STICK : 0);
      b = (b & ~C_BITS) | ((buttons & EXTRA.CAMZOOM) ? N64.CU : 0) | ((buttons & EXTRA.CAMBACK) ? N64.CD : 0);
    }
    return { b, x, y, half, cx, cy, photo: (buttons & EXTRA.PHOTO) !== 0, recSave: (buttons & EXTRA.RECSAVE) !== 0 };
  }
  // P324 toggle options (crouch / R-Look / walk): a new press of the bound input flips a latch that holds it
  const LATCHES = [{ id: OPT.TOGGLECROUCH, bit: N64.Z }, { id: OPT.TOGGLERLOOK, bit: N64.R }, { id: OPT.TOGGLEWALK, bit: 0 }];
  const latchOn = {}, latchPrev = {};
  function applyLatches(p) {
    for (const l of LATCHES) {
      const raw = l.bit ? (p.b & l.bit) !== 0 : p.half;
      if (!opt(l.id)) latchOn[l.id] = false;
      else if (raw && !latchPrev[l.id]) latchOn[l.id] = !latchOn[l.id];
      latchPrev[l.id] = raw;
      if (!opt(l.id)) continue;
      if (l.bit) p.b = latchOn[l.id] ? p.b | l.bit : p.b & ~l.bit;
      else if (latchOn[l.id]) { p.x = Math.round(p.x / 2); p.y = Math.round(p.y / 2); }
    }
  }
  const portCalls = [0, 0, 0, 0], portSeenAt = [0, 0, 0, 0];
  let recSavePrev = false;
  function tick() {
    scheduleTick();
    if (!started || hostPaused) return;
    const now = performance.now(), raw = wasm('port_rtw_raw_state')() >> 2;
    // pad 1 = the host's port 0 (keyboard, touch and the first gamepad); ports 1-3 count as plugged in while the host
    // keeps sending them (further gamepads)
    const pads = [null, null, null, null];
    for (let i = 0; i < 4; i++) {
      const calls = HEAP32[raw + i * 4];
      if (calls !== portCalls[i]) { portCalls[i] = calls; portSeenAt[i] = now; }
      if (i === 0 || (portSeenAt[i] && now - portSeenAt[i] < 1000)) pads[i] = hostPad(HEAP32[raw + i * 4 + 1], HEAP32[raw + i * 4 + 2], HEAP32[raw + i * 4 + 3]);
    }
    const mouseDx = HEAP32[raw + 16], mouseDy = HEAP32[raw + 17];
    HEAP32[raw + 16] = 0; HEAP32[raw + 17] = 0;
    const p0 = pads[0];
    if (p0.recSave && !recSavePrev) recStop('the Save recording button');
    recSavePrev = p0.recSave;
    if (photo.state === 2) { photo.mx += mouseDx; photo.my += mouseDy; }   // P348 photo camera
    const photoHasInput = photoPoll(p0);
    const wantLock = freeCameraOn() || photo.state === 2;
    if (wantLock !== pointerLocked) { pointerLocked = wantLock; wasm('port_rtw_set_pointer_lock')(wantLock ? 1 : 0); }
    wasm('port_gfx_hfr_vsync')();
    if (photoHasInput) return;   // P348: photo mode takes pad 1's input
    photoMaskAfter(p0);
    applyLatches(p0);
    if (rec.active) { recSetPad(p0); return; }   // P357: the recorded pad (pc_net.c samples it at the next retrace)
    const pp = wasm('port_pad_state')() >> 2;
    for (let i = 0; i < 4; i++) {
      const d = pads[i];
      HEAP32[pp + i * 4] = d ? 1 : 0;
      HEAP32[pp + i * 4 + 1] = d ? d.b : 0; HEAP32[pp + i * 4 + 2] = d ? d.x : 0; HEAP32[pp + i * 4 + 3] = d ? d.y : 0;
    }
    const cp = wasm('port_cam_state')() >> 2;   // P347 free camera: camera stick per pad, mouse summed until the game reads it
    for (let i = 0; i < 4; i++) { const d = pads[i]; HEAP32[cp + i * 4] = d ? d.cx : 0; HEAP32[cp + i * 4 + 1] = d ? d.cy : 0; }
    if (freeCameraOn() && photo.state !== 2) { HEAP32[cp + 2] += mouseDx; HEAP32[cp + 3] += mouseDy; }
  }
  const raf = typeof requestAnimationFrame === 'function' ? requestAnimationFrame.bind(globalThis) : (f) => setTimeout(f, 16);
  let tickQueued = false;
  function scheduleTick() { tickQueued = true; raf(() => { tickQueued = false; tick(); }); }

  // ------------------------------------------------------------------ photo mode (main.js photoPoll / photoCapture, P348)
  const photo = { state: 0, prevB: 0, prevKey: false, hud: false, mx: 0, my: 0, last: 0, busy: false, asked: 0,
    maskB: 0, maskStick: false, scale: 2 };
  const PHOTO_WHY = { 1: 'Photo mode is off in Options', 2: 'no photo mode online', 3: 'photo mode needs the 3D view of a single-player game (not a menu, the pause screen, split screen or loading)',
    4: 'photo mode is not available (conker_netx.txt did not load)', 5: 'not enough memory for photo mode' };
  function photoRequest(on) {
    if (on && (!photoModeOn() || hostPaused)) return;
    const r = wasm('port_photo_request')(on ? 1 : 0);
    log(`[photo] ${on ? 'start' : 'leave'} requested (state ${r})`);
    if (on) photo.asked = performance.now();
  }
  // one animation frame of pad 1 while photo mode may be on; true = photo mode has the input
  function photoPoll(d) {
    const st = wasm('port_photo_status')(), was = photo.state, now = performance.now();
    if (d.photo && !photo.prevKey) photoRequest(!(st === 2 || st === 1));
    photo.prevKey = d.photo;
    photo.state = st;
    if (st === 2 && was !== 2) { photo.hud = false; photo.mx = photo.my = 0; photo.prevB = d.b; photo.last = now; log('[photo] on'); }
    if (st !== 2 && was === 2) { photo.maskB = d.b; photo.maskStick = true; log('[photo] off'); }
    if (st < 0 && photo.asked) { log(`[photo] not started: ${PHOTO_WHY[-st] || 'photo mode did not start'}`); photo.asked = 0; }
    if (st === 2) photo.asked = 0;
    if (st !== 2) return st === 1 || st === 3;
    const dt = Math.min(0.1, (now - photo.last) / 1000);
    const b = d.b, fresh = b & ~photo.prevB;
    photo.last = now; photo.prevB = b;
    if (fresh & N64.START) { photoRequest(false); return true; }
    if (fresh & N64.A) photoCapture();
    let flags = 0;
    if (fresh & N64.B) flags |= 2;   // back to the game's view
    if (fresh & N64.L) photo.hud = !photo.hud;
    if (photo.hud) flags |= 1;
    // look: the free camera's stick (C buttons with that option), else the C buttons
    const lx = d.cx || ((b & N64.CR) ? STICK : 0) - ((b & N64.CL) ? STICK : 0);
    const ly = d.cy || ((b & N64.CU) ? STICK : 0) - ((b & N64.CD) ? STICK : 0);
    const fwd = d.y / STICK * 500 * dt, right = d.x / STICK * 500 * dt;
    const up = (((b & N64.R) ? 1 : 0) - ((b & N64.Z) ? 1 : 0)) * 350 * dt;
    const dyaw = lx / STICK * 90 * dt + photo.mx * 0.15, dpitch = ly / STICK * 60 * dt - photo.my * 0.15;
    const droll = (((b & N64.DR) ? 1 : 0) - ((b & N64.DL) ? 1 : 0)) * 45 * dt;
    const zoom = Math.exp((((b & N64.DD) ? 1 : 0) - ((b & N64.DU) ? 1 : 0)) * 0.9 * dt);
    photo.mx = photo.my = 0;
    wasm('port_photo_input')(fwd, right, up, dyaw, dpitch, droll, zoom, flags);
    return true;
  }
  function photoMaskAfter(d) {   // after photo mode: held buttons / a deflected stick stay off until released
    if (photo.maskB) { photo.maskB &= d.b; d.b &= ~photo.maskB; }
    if (photo.maskStick) {
      if (Math.abs(d.x) < 10 && Math.abs(d.y) < 10 && !d.cx && !d.cy) photo.maskStick = false;
      else { d.x = d.y = 0; d.cx = d.cy = 0; }
    }
  }
  // A: the picture as a PNG at twice the canvas resolution (the photo frame drawn again at that size, then the canvas
  // set back), handed to the host's "Saved files"
  async function photoCapture() {
    if (photo.busy || photo.state !== 2) return;
    photo.busy = true;
    const canvas = Module['canvas'], w0 = canvas.width, h0 = canvas.height, k = photo.scale;
    let blob = null;
    try {
      if (k !== 1) { canvas.width = w0 * k; canvas.height = h0 * k; wasm('port_gfx_resize')(canvas.width, canvas.height); }
      wasm('port_photo_render')();   // switches fibers (asyncify): ask port_photo_info(9) whether it drew
      const drawn = wasm('port_photo_info')(9) > 0, ms = wasm('port_photo_info')(10);
      blob = await canvas.convertToBlob({ type: 'image/png' });
      log(`[photo] picture ${canvas.width} x ${canvas.height}${drawn ? '' : ' (no new frame drawn)'} in ${ms.toFixed(0)} ms: ${blob ? blob.size : 0} bytes`);
    } catch (e) {
      log('[photo] the picture could not be made: ' + e);
    } finally {
      if (k !== 1) { canvas.width = w0; canvas.height = h0; wasm('port_gfx_resize')(w0, h0); wasm('port_photo_render')(); }
      photo.busy = false;
    }
    if (!blob) return;
    const name = `conker-photo-${stamp(new Date())}.png`;
    const r = exportFile(name, 'image/png', new Uint8Array(await blob.arrayBuffer()));
    log(`[photo] saved ${name} (${w0 * k} x ${h0 * k})${r ? ` (the host refused it: ${r})` : ''}`);
  }

  // ------------------------------------------------------------------ input recorder (main.js rec*, P357; docs/port/E2E.md)
  // Same file as the page's (.ckrec: gzip of the JSON recording). build = the first 16 hex of SHA-256 of conker.wasm (as
  // the page), rtw_build = the host's build id (SHA-256 of retrowser.json, env.rtw_build_id). No drafts in storage:
  // the host keeps only what rtw_export_file hands it, so an unsaved recording is lost with the page.
  const REC_FORMAT = 'conker-e2e-recording', REC_CHECK_EVERY = 50, REC_G_EVERY = 10;
  const rec = { active: false, runs: [], lastV: -1, frames: 0, g: [], checks: [], gaps: 0, header: null, headerReady: null,
    t0: 0, pausedMs: 0, pauseSince: 0 };
  function recEncodeRuns(runs) {   // [[value, count], ...] -> u32 LE value + LEB128 count per run
    const o8 = new Uint8Array(runs.length * 9); let o = 0;
    for (const [v, n] of runs) {
      o8[o++] = v & 255; o8[o++] = (v >>> 8) & 255; o8[o++] = (v >>> 16) & 255; o8[o++] = (v >>> 24) & 255;
      let c = n; while (c >= 128) { o8[o++] = (c & 127) | 128; c = Math.floor(c / 128); } o8[o++] = c;
    }
    return o8.subarray(0, o);
  }
  const u32enc = (arr) => { const b = new Uint8Array(arr.length * 4), dv = new DataView(b.buffer); arr.forEach((v, i) => dv.setUint32(i * 4, v >>> 0, true)); return b; };
  function eepromBytes() { const p = wasm('port_eeprom_ptr')(), n = wasm('port_eeprom_size')(); return HEAPU8.slice(p, p + n); }
  function recBegin() {
    Module['recInput'] = (f, v) => {
      if (!rec.active) return;
      if (f !== rec.frames + 1) { rec.gaps++; if (rec.gaps < 5) log(`[rec] input of retrace ${f} after ${rec.frames}`); }
      rec.frames = f;
      if (v === rec.lastV && rec.runs.length) rec.runs[rec.runs.length - 1][1]++; else { rec.runs.push([v, 1]); rec.lastV = v; }
    };
    Module['recG'] = (f, g) => { if (rec.active) rec.g.push(g); };
    Module['recCheck'] = (f, h, s, g, level, mode, kind, x, y, z) => {
      if (rec.active) rec.checks.push([f, h, s, g, level, mode, kind, +x.toFixed(3), +y.toFixed(3), +z.toFixed(3)]);
    };
    Module['recEnd'] = () => {};
    const options = {}, viewOptions = {};
    for (const id in GAME_OPTION_KEYS) options[GAME_OPTION_KEYS[id]] = RANGE_OPTIONS.has(+id) ? opt(+id) : !!opt(+id);
    options.freecam = false; options.photomode = false;   // not part of the recorded input
    for (const id in PAGE_OPTION_KEYS) viewOptions[PAGE_OPTION_KEYS[id]] = !!opt(+id);
    const buildIdPtr = wasm('malloc')(32);
    wasm('port_rtw_build_id')(buildIdPtr);
    const rtwBuild = hex(HEAPU8.slice(buildIdPtr, buildIdPtr + 32));
    wasm('free')(buildIdPtr);
    rec.header = { format: REC_FORMAT, version: 1, name: 'retrowser', created: new Date().toISOString(), build: 'unknown',
      rtw_build: rtwBuild, rom_sha1: 'unknown', start: 'power-on', slot: 'retrowser', eeprom: b64enc(eepromBytes()), options,
      view: viewOptions, check_every: REC_CHECK_EVERY, g_every: REC_G_EVERY, user_agent: navigator.userAgent };
    rec.headerReady = (async () => {
      try { if (Module['wasmBinary']) rec.header.build = (await digestHex('SHA-256', Module['wasmBinary'])).slice(0, 16); } catch (e) { /* keep unknown */ }
      try { if (romForHash) rec.header.rom_sha1 = await digestHex('SHA-1', romForHash); } catch (e) { /* keep unknown */ }
    })();
    wasm('port_set_option')(OPT.FREECAM, 0); wasm('port_set_option')(OPT.PHOTOMODE, 0);
    wasm('port_rtw_lock_game_options')();   // main.js optionsLocked: the game options stay fixed for the recording
    wasm('port_rec_session')(1, REC_CHECK_EVERY, REC_G_EVERY, 0, 0, 0, 0);
    rec.active = true; rec.t0 = performance.now();
    log(`[rec] recording from power-on: build id ${rtwBuild.slice(0, 16)}, options ` +
        Object.entries(options).map(([k, v]) => `${k}=${+v}`).join(' '));
  }
  function recSetPad(p) {   // every animation frame while recording: pad 1 as the game will sample it at the next retrace
    const a = wasm('port_net_addr')(3) >> 2;
    HEAP32[a] = 1; HEAP32[a + 1] = p.b; HEAP32[a + 2] = p.x; HEAP32[a + 3] = p.y;
  }
  async function recStop(why) {
    if (!rec.active) { if (why) log('[rec] no recording runs (turn on the option "Input recorder": it records from the next start)'); return; }
    wasm('port_rec_checkpoint_now')();   // the last checkpoint: the state after the last recorded retrace
    rec.active = false;
    const now = performance.now(), paused = rec.pausedMs + (rec.pauseSince ? now - rec.pauseSince : 0);
    await rec.headerReady;
    const doc = Object.assign({}, rec.header, { retraces: rec.frames, inputs: b64enc(recEncodeRuns(rec.runs)), g: b64enc(u32enc(rec.g)),
      checks: rec.checks, complete: true, gaps: rec.gaps, wall_s: Math.round((now - rec.t0) / 100) / 10, paused_s: Math.round(paused / 100) / 10 });
    const json = new Blob([JSON.stringify(doc)], { type: 'application/json' });
    const packed = typeof CompressionStream === 'function' ? await new Response(json.stream().pipeThrough(new CompressionStream('gzip'))).blob() : json;
    const bytes = new Uint8Array(await packed.arrayBuffer());
    const name = `conker-rec-retrowser-${stamp(new Date(doc.created))}.ckrec`;
    const r = exportFile(name, packed.type === 'application/json' ? 'application/json' : 'application/gzip', bytes);
    log(`[rec] stopped by ${why} after retrace ${doc.retraces} (${doc.checks.length} checkpoints, ${rec.runs.length} input runs): ${name}, ${bytes.length} bytes` +
        (r ? ` (the host refused it: ${r})` : '') + '. The game goes on in the recording mode; restart it to play normally.');
  }

  // ------------------------------------------------------------------ hooks from pc_rtw.c / pc_video.c (rtw_lib.js)
  let romForHash = null;
  function loadExclusions() {   // main.js netLoadExclusions: conker_netx.txt from files.data
    const files = Module['files'] || {}, bytes = files['conker_netx.txt'];
    if (!bytes) { log('[nethash] conker_netx.txt not in files.data: photo mode and the recorder are off'); return; }
    let n = 0;
    for (const line of new TextDecoder().decode(bytes).split('\n')) {
      const f = line.split(' ');
      if (f.length >= 2) { wasm('port_net_exclude')(parseInt(f[0], 16), parseInt(f[1], 16)); n++; }
    }
    log(`[nethash] ${n} excluded static ranges from conker_netx.txt`);
  }
  return {
    start() {   // rtw_start, before main()
      loadExclusions();
      layout();
      if (opt(OPT.RECORDER)) {
        const romPtr = wasm('port_rtw_rom_ptr')(), romSize = wasm('port_rtw_rom_size')();
        if (romPtr && romSize) romForHash = HEAPU8.slice(romPtr, romPtr + romSize);
        recBegin();
      }
      started = true;
      if (!tickQueued) scheduleTick();
      // test aid (tools/port/scripts/rtw_e2e.mjs reads the game's state from the worker); the worker is the sandbox's own
      globalThis.__rtwConker = { Module, photoState: () => photo.state, rec: () => ({ active: rec.active, frames: rec.frames, checks: rec.checks.length }),
        audioDrained: () => Module['_port_rtw_audio_drained']() >>> 0, saveGeneration: () => Module['_rtw_save_generation']() };
      log(`[rtw] started: options ${Object.entries(optionValues).map(([k, v]) => `${k}=${v}`).join(' ')}`);
    },
    beforeGl() { layout(); },   // the drawing buffer the renderer starts with (gfx_init reads the viewport)
    glReady() { glUp = true; layout(); },
    option(id, value) {   // rtw_option (pc_rtw.c already set the game options)
      const was = optionValues[id];
      optionValues[id] = value;
      if (id === OPT.HIRES2D) wasm('port_gfx_hires_2d')(value ? 1 : 0);
      else if (id === OPT.SMOOTHFONT) wasm('port_gfx_smooth_font')(value ? 1 : 0);
      else if (id === OPT.HFR) wasm('port_gfx_hfr')(value ? 1 : 0);
      else if (id === OPT.WIDESCREEN || id === OPT.FULLRES) layout();
      else if (id === OPT.PHOTOMODE && !value && photo.state === 2) photoRequest(false);
      else if (id === OPT.RECORDER && started && value !== was) {
        if (!value) recStop('turning the option off');
        else log('[rec] the recorder starts with the next start of the game (from power-on)');
      }
    },
    resize(width, height, dpr100) {   // rtw_resize: CSS pixels of the view, devicePixelRatio x 100
      view.width = width; view.height = height; view.dpr100 = dpr100 || 100;
      layout();
    },
    pause(on) {   // rtw_pause (pc_rtw.c already paused the game)
      hostPaused = !!on;
      const now = performance.now();
      if (on && !rec.pauseSince) rec.pauseSince = now;
      if (!on && rec.pauseSince) { rec.pausedMs += now - rec.pauseSince; rec.pauseSince = 0; }
    },
    get glUp() { return glUp; },
  };
})();
// end include: web/rtw/rtw_glue.js


var arguments_ = [];
var thisProgram = './this.program';
var quit_ = (status, toThrow) => {
  throw toThrow;
};

var _scriptName;

if (ENVIRONMENT_IS_WORKER) {
  _scriptName = self.location.href;
}

// `/` should be present at the end if `scriptDirectory` is not empty
var scriptDirectory = '';
function locateFile(path) {
  if (Module['locateFile']) {
    return Module['locateFile'](path, scriptDirectory);
  }
  return scriptDirectory + path;
}

// Hooks that are implemented differently in different runtime environments.
var readAsync, readBinary;

if (ENVIRONMENT_IS_SHELL) {

  const isNode = typeof process == 'object' && process.versions?.node && process.type != 'renderer';
  if (isNode || typeof window == 'object' || typeof WorkerGlobalScope != 'undefined') throw new Error('not compiled for this environment (did you build to HTML and try to run it not on the web, or set ENVIRONMENT to something - like node - and run it someplace else - like on the web?)');

} else

// Note that this includes Node.js workers when relevant (pthreads is enabled).
// Node.js workers are detected as a combination of ENVIRONMENT_IS_WORKER and
// ENVIRONMENT_IS_NODE.
if (ENVIRONMENT_IS_WEB || ENVIRONMENT_IS_WORKER) {
  try {
    scriptDirectory = new URL('.', _scriptName).href; // includes trailing slash
  } catch {
    // Must be a `blob:` or `data:` URL (e.g. `blob:http://site.com/etc/etc`), we cannot
    // infer anything from them.
  }

  if (!(typeof window == 'object' || typeof WorkerGlobalScope != 'undefined')) throw new Error('not compiled for this environment (did you build to HTML and try to run it not on the web, or set ENVIRONMENT to something - like node - and run it someplace else - like on the web?)');

  {
// include: web_or_worker_shell_read.js
if (ENVIRONMENT_IS_WORKER) {
    readBinary = (url) => {
      var xhr = new XMLHttpRequest();
      xhr.open('GET', url, false);
      xhr.responseType = 'arraybuffer';
      xhr.send(null);
      return new Uint8Array(/** @type{!ArrayBuffer} */(xhr.response));
    };
  }

  readAsync = async (url) => {
    assert(!isFileURI(url), "readAsync does not work with file:// URLs");
    var response = await fetch(url, { credentials: 'same-origin' });
    if (response.ok) {
      return response.arrayBuffer();
    }
    throw new Error(response.status + ' : ' + response.url);
  };
// end include: web_or_worker_shell_read.js
  }
} else
{
  throw new Error('environment detection error');
}

var out = console.log.bind(console);
var err = console.error.bind(console);

var IDBFS = 'IDBFS is no longer included by default; build with -lidbfs.js';
var PROXYFS = 'PROXYFS is no longer included by default; build with -lproxyfs.js';
var WORKERFS = 'WORKERFS is no longer included by default; build with -lworkerfs.js';
var FETCHFS = 'FETCHFS is no longer included by default; build with -lfetchfs.js';
var ICASEFS = 'ICASEFS is no longer included by default; build with -licasefs.js';
var JSFILEFS = 'JSFILEFS is no longer included by default; build with -ljsfilefs.js';
var OPFS = 'OPFS is no longer included by default; build with -lopfs.js';

var NODEFS = 'NODEFS is no longer included by default; build with -lnodefs.js';

// perform assertions in shell.js after we set up out() and err(), as otherwise
// if an assertion fails it cannot print the message

assert(!ENVIRONMENT_IS_WEB, 'web environment detected but not enabled at build time.  Add `web` to `-sENVIRONMENT` to enable.');

assert(!ENVIRONMENT_IS_NODE, 'node environment detected but not enabled at build time.  Add `node` to `-sENVIRONMENT` to enable.');

assert(!ENVIRONMENT_IS_SHELL, 'shell environment detected but not enabled at build time.  Add `shell` to `-sENVIRONMENT` to enable.');

// end include: shell.js

// include: preamble.js
// === Preamble library stuff ===

// Documentation for the public APIs defined in this file must be updated in:
//    site/source/docs/api_reference/preamble.js.rst
// A prebuilt local version of the documentation is available at:
//    site/build/text/docs/api_reference/preamble.js.txt
// You can also build docs locally as HTML or other formats in site/
// An online HTML version (which may be of a different version of Emscripten)
//    is up at http://kripken.github.io/emscripten-site/docs/api_reference/preamble.js.html

var wasmBinary;

if (typeof WebAssembly != 'object') {
  err('no native wasm support detected');
}

// Wasm globals

//========================================
// Runtime essentials
//========================================

// whether we are quitting the application. no code should run after this.
// set in exit() and abort()
var ABORT = false;

// set by exit() and abort().  Passed to 'onExit' handler.
// NOTE: This is also used as the process return code code in shell environments
// but only when noExitRuntime is false.
var EXITSTATUS;

// In STRICT mode, we only define assert() when ASSERTIONS is set.  i.e. we
// don't define it at all in release modes.  This matches the behaviour of
// MINIMAL_RUNTIME.
// TODO(sbc): Make this the default even without STRICT enabled.
/** @type {function(*, string=)} */
function assert(condition, text) {
  if (!condition) {
    abort('Assertion failed' + (text ? ': ' + text : ''));
  }
}

// We used to include malloc/free by default in the past. Show a helpful error in
// builds with assertions.

/**
 * Indicates whether filename is delivered via file protocol (as opposed to http/https)
 * @noinline
 */
var isFileURI = (filename) => filename.startsWith('file://');

// include: runtime_common.js
// include: runtime_stack_check.js
// end include: runtime_stack_check.js
// include: runtime_exceptions.js
// end include: runtime_exceptions.js
// include: runtime_debug.js
var runtimeDebug = true; // Switch to false at runtime to disable logging at the right times

// Used by XXXXX_DEBUG settings to output debug messages.
function dbg(...args) {
  if (!runtimeDebug && typeof runtimeDebug != 'undefined') return;
  // TODO(sbc): Make this configurable somehow.  Its not always convenient for
  // logging to show up as warnings.
  console.warn(...args);
}

// Endianness check
(() => {
  var h16 = new Int16Array(1);
  var h8 = new Int8Array(h16.buffer);
  h16[0] = 0x6373;
  if (h8[0] !== 0x73 || h8[1] !== 0x63) abort('Runtime error: expected the system to be little-endian! (Run with -sSUPPORT_BIG_ENDIAN to bypass)');
})();

function consumedModuleProp(prop) {
  if (!Object.getOwnPropertyDescriptor(Module, prop)) {
    Object.defineProperty(Module, prop, {
      configurable: true,
      set() {
        abort(`Attempt to set \`Module.${prop}\` after it has already been processed.  This can happen, for example, when code is injected via '--post-js' rather than '--pre-js'`);

      }
    });
  }
}

function makeInvalidEarlyAccess(name) {
  return () => assert(false, `call to '${name}' via reference taken before Wasm module initialization`);

}

function ignoredModuleProp(prop) {
  if (Object.getOwnPropertyDescriptor(Module, prop)) {
    abort(`\`Module.${prop}\` was supplied but \`${prop}\` not included in INCOMING_MODULE_JS_API`);
  }
}

// forcing the filesystem exports a few things by default
function isExportedByForceFilesystem(name) {
  return name === 'FS_createPath' ||
         name === 'FS_createDataFile' ||
         name === 'FS_createPreloadedFile' ||
         name === 'FS_preloadFile' ||
         name === 'FS_unlink' ||
         name === 'addRunDependency' ||
         // The old FS has some functionality that WasmFS lacks.
         name === 'FS_createLazyFile' ||
         name === 'FS_createDevice' ||
         name === 'removeRunDependency';
}

function missingLibrarySymbol(sym) {

  // Any symbol that is not included from the JS library is also (by definition)
  // not exported on the Module object.
  unexportedRuntimeSymbol(sym);
}

function unexportedRuntimeSymbol(sym) {
  if (!Object.getOwnPropertyDescriptor(Module, sym)) {
    Object.defineProperty(Module, sym, {
      configurable: true,
      get() {
        var msg = `'${sym}' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the Emscripten FAQ)`;
        if (isExportedByForceFilesystem(sym)) {
          msg += '. Alternatively, forcing filesystem support (-sFORCE_FILESYSTEM) can export this for you';
        }
        abort(msg);
      }
    });
  }
}

// end include: runtime_debug.js
var readyPromiseResolve, readyPromiseReject;

// Memory management

var wasmMemory;

var
/** @type {!Int8Array} */
  HEAP8,
/** @type {!Uint8Array} */
  HEAPU8,
/** @type {!Int16Array} */
  HEAP16,
/** @type {!Uint16Array} */
  HEAPU16,
/** @type {!Int32Array} */
  HEAP32,
/** @type {!Uint32Array} */
  HEAPU32,
/** @type {!Float32Array} */
  HEAPF32,
/** @type {!Float64Array} */
  HEAPF64;

// BigInt64Array type is not correctly defined in closure
var
/** not-@type {!BigInt64Array} */
  HEAP64,
/* BigUint64Array type is not correctly defined in closure
/** not-@type {!BigUint64Array} */
  HEAPU64;

var runtimeInitialized = false;



function updateMemoryViews() {
  var b = wasmMemory.buffer;
  HEAP8 = new Int8Array(b);
  HEAP16 = new Int16Array(b);
  Module['HEAPU8'] = HEAPU8 = new Uint8Array(b);
  HEAPU16 = new Uint16Array(b);
  Module['HEAP32'] = HEAP32 = new Int32Array(b);
  Module['HEAPU32'] = HEAPU32 = new Uint32Array(b);
  HEAPF32 = new Float32Array(b);
  HEAPF64 = new Float64Array(b);
  HEAP64 = new BigInt64Array(b);
  HEAPU64 = new BigUint64Array(b);
}

// include: memoryprofiler.js
// end include: memoryprofiler.js
// end include: runtime_common.js
assert(typeof Int32Array != 'undefined' && typeof Float64Array !== 'undefined' && Int32Array.prototype.subarray != undefined && Int32Array.prototype.set != undefined,
       'JS engine does not provide full typed array support');

function preRun() {
  if (Module['preRun']) {
    if (typeof Module['preRun'] == 'function') Module['preRun'] = [Module['preRun']];
    while (Module['preRun'].length) {
      addOnPreRun(Module['preRun'].shift());
    }
  }
  consumedModuleProp('preRun');
  // Begin ATPRERUNS hooks
  callRuntimeCallbacks(onPreRuns);
  // End ATPRERUNS hooks
}

function initRuntime() {
  assert(!runtimeInitialized);
  runtimeInitialized = true;

  // No ATINITS hooks

  wasmExports['__wasm_call_ctors']();

  // No ATPOSTCTORS hooks
}

function preMain() {
  // No ATMAINS hooks
}

function postRun() {
   // PThreads reuse the runtime from the main thread.

  if (Module['postRun']) {
    if (typeof Module['postRun'] == 'function') Module['postRun'] = [Module['postRun']];
    while (Module['postRun'].length) {
      addOnPostRun(Module['postRun'].shift());
    }
  }
  consumedModuleProp('postRun');

  // Begin ATPOSTRUNS hooks
  callRuntimeCallbacks(onPostRuns);
  // End ATPOSTRUNS hooks
}

/** @param {string|number=} what */
function abort(what) {
  Module['onAbort']?.(what);

  what = 'Aborted(' + what + ')';
  // TODO(sbc): Should we remove printing and leave it up to whoever
  // catches the exception?
  err(what);

  ABORT = true;

  if (what.indexOf('RuntimeError: unreachable') >= 0) {
    what += '. "unreachable" may be due to ASYNCIFY_STACK_SIZE not being large enough (try increasing it)';
  }

  // Use a wasm runtime error, because a JS error might be seen as a foreign
  // exception, which means we'd run destructors on it. We need the error to
  // simply make the program stop.
  // FIXME This approach does not work in Wasm EH because it currently does not assume
  // all RuntimeErrors are from traps; it decides whether a RuntimeError is from
  // a trap or not based on a hidden field within the object. So at the moment
  // we don't have a way of throwing a wasm trap from JS. TODO Make a JS API that
  // allows this in the wasm spec.

  // Suppress closure compiler warning here. Closure compiler's builtin extern
  // definition for WebAssembly.RuntimeError claims it takes no arguments even
  // though it can.
  // TODO(https://github.com/google/closure-compiler/pull/3913): Remove if/when upstream closure gets fixed.
  /** @suppress {checkTypes} */
  var e = new WebAssembly.RuntimeError(what);

  readyPromiseReject?.(e);
  // Throw the error whether or not MODULARIZE is set because abort is used
  // in code paths apart from instantiation where an exception is expected
  // to be thrown when abort is called.
  throw e;
}

// show errors on likely calls to FS when it was not included
var FS = {
  error() {
    abort('Filesystem support (FS) was not included. The problem is that you are using files from JS, but files were not used from C/C++, so filesystem support was not auto-included. You can force-include filesystem support with -sFORCE_FILESYSTEM');
  },
  init() { FS.error() },
  createDataFile() { FS.error() },
  createPreloadedFile() { FS.error() },
  createLazyFile() { FS.error() },
  open() { FS.error() },
  mkdev() { FS.error() },
  registerDevice() { FS.error() },
  analyzePath() { FS.error() },

  ErrnoError() { FS.error() },
};


function createExportWrapper(name, nargs) {
  return (...args) => {
    assert(runtimeInitialized, `native function \`${name}\` called before runtime initialization`);
    var f = wasmExports[name];
    assert(f, `exported native function \`${name}\` not found`);
    // Only assert for too many arguments. Too few can be valid since the missing arguments will be zero filled.
    assert(args.length <= nargs, `native function \`${name}\` called with ${args.length} args but expects ${nargs}`);
    return f(...args);
  };
}

var wasmBinaryFile;

function findWasmBinary() {
    return locateFile('conker.wasm');
}

function getBinarySync(file) {
  if (file == wasmBinaryFile && wasmBinary) {
    return new Uint8Array(wasmBinary);
  }
  if (readBinary) {
    return readBinary(file);
  }
  // Throwing a plain string here, even though it not normally adviables since
  // this gets turning into an `abort` in instantiateArrayBuffer.
  throw 'both async and sync fetching of the wasm failed';
}

async function getWasmBinary(binaryFile) {
  // If we don't have the binary yet, load it asynchronously using readAsync.
  if (!wasmBinary) {
    // Fetch the binary using readAsync
    try {
      var response = await readAsync(binaryFile);
      return new Uint8Array(response);
    } catch {
      // Fall back to getBinarySync below;
    }
  }

  // Otherwise, getBinarySync should be able to get it synchronously
  return getBinarySync(binaryFile);
}

async function instantiateArrayBuffer(binaryFile, imports) {
  try {
    var binary = await getWasmBinary(binaryFile);
    var instance = await WebAssembly.instantiate(binary, imports);
    return instance;
  } catch (reason) {
    err(`failed to asynchronously prepare wasm: ${reason}`);

    // Warn on some common problems.
    if (isFileURI(binaryFile)) {
      err(`warning: Loading from a file URI (${binaryFile}) is not supported in most browsers. See https://emscripten.org/docs/getting_started/FAQ.html#how-do-i-run-a-local-webserver-for-testing-why-does-my-program-stall-in-downloading-or-preparing`);
    }
    abort(reason);
  }
}

async function instantiateAsync(binary, binaryFile, imports) {
  if (!binary
     ) {
    try {
      var response = fetch(binaryFile, { credentials: 'same-origin' });
      var instantiationResult = await WebAssembly.instantiateStreaming(response, imports);
      return instantiationResult;
    } catch (reason) {
      // We expect the most common failure cause to be a bad MIME type for the binary,
      // in which case falling back to ArrayBuffer instantiation should work.
      err(`wasm streaming compile failed: ${reason}`);
      err('falling back to ArrayBuffer instantiation');
      // fall back of instantiateArrayBuffer below
    };
  }
  return instantiateArrayBuffer(binaryFile, imports);
}

function getWasmImports() {
  // instrumenting imports is used in asyncify in two ways: to add assertions
  // that check for proper import use, and for ASYNCIFY=2 we use them to set up
  // the Promise API on the import side.
  Asyncify.instrumentWasmImports(wasmImports);
  // prepare imports
  return {
    'env': wasmImports,
    'wasi_snapshot_preview1': wasmImports,
  }
}

// Create the wasm instance.
// Receives the wasm imports, returns the exports.
async function createWasm() {
  // Load the wasm module and create an instance of using native support in the JS engine.
  // handle a generated wasm instance, receiving its exports and
  // performing other necessary setup
  /** @param {WebAssembly.Module=} module*/
  function receiveInstance(instance, module) {
    wasmExports = instance.exports;

    wasmExports = Asyncify.instrumentWasmExports(wasmExports);

    

    wasmMemory = wasmExports['memory'];
    Module['wasmMemory'] = wasmMemory;
    assert(wasmMemory, 'memory not found in wasm exports');
    updateMemoryViews();

    assignWasmExports(wasmExports);
    return wasmExports;
  }

  // Prefer streaming instantiation if available.
  // Async compilation can be confusing when an error on the page overwrites Module
  // (for example, if the order of elements is wrong, and the one defining Module is
  // later), so we save Module and check it later.
  var trueModule = Module;
  function receiveInstantiationResult(result) {
    // 'result' is a ResultObject object which has both the module and instance.
    // receiveInstance() will swap in the exports (to Module.asm) so they can be called
    assert(Module === trueModule, 'the Module object should not be replaced during async compilation - perhaps the order of HTML elements is wrong?');
    trueModule = null;
    // TODO: Due to Closure regression https://github.com/google/closure-compiler/issues/3193, the above line no longer optimizes out down to the following line.
    // When the regression is fixed, can restore the above PTHREADS-enabled path.
    return receiveInstance(result['instance']);
  }

  var info = getWasmImports();

  // User shell pages can write their own Module.instantiateWasm = function(imports, successCallback) callback
  // to manually instantiate the Wasm module themselves. This allows pages to
  // run the instantiation parallel to any other async startup actions they are
  // performing.
  // Also pthreads and wasm workers initialize the wasm instance through this
  // path.
  if (Module['instantiateWasm']) {
    return new Promise((resolve, reject) => {
      try {
        Module['instantiateWasm'](info, (mod, inst) => {
          resolve(receiveInstance(mod, inst));
        });
      } catch(e) {
        err(`Module.instantiateWasm callback failed with error: ${e}`);
        reject(e);
      }
    });
  }

  wasmBinaryFile ??= findWasmBinary();
  var result = await instantiateAsync(wasmBinary, wasmBinaryFile, info);
  var exports = receiveInstantiationResult(result);
  return exports;
}

// end include: preamble.js

// Begin JS library code


  class ExitStatus {
      name = 'ExitStatus';
      constructor(status) {
        this.message = `Program terminated with exit(${status})`;
        this.status = status;
      }
    }

  var callRuntimeCallbacks = (callbacks) => {
      while (callbacks.length > 0) {
        // Pass the module as the first argument.
        callbacks.shift()(Module);
      }
    };
  var onPostRuns = [];
  var addOnPostRun = (cb) => onPostRuns.push(cb);

  var onPreRuns = [];
  var addOnPreRun = (cb) => onPreRuns.push(cb);


  var dynCalls = {
  };
  var dynCallLegacy = (sig, ptr, args) => {
      sig = sig.replace(/p/g, 'i')
      assert(sig in dynCalls, `bad function pointer type - sig is not in dynCalls: '${sig}'`);
      if (args?.length) {
        // j (64-bit integer) is fine, and is implemented as a BigInt. Without
        // legalization, the number of parameters should match (j is not expanded
        // into two i's).
        assert(args.length === sig.length - 1);
      } else {
        assert(sig.length == 1);
      }
      var f = dynCalls[sig];
      return f(ptr, ...args);
    };
  var dynCall = (sig, ptr, args = [], promising = false) => {
      assert(!promising, 'async dynCall is not supported in this mode')
      var rtn = dynCallLegacy(sig, ptr, args);
  
      function convert(rtn) {
        return rtn;
      }
  
      return convert(rtn);
    };

  
    /**
     * @param {number} ptr
     * @param {string} type
     */
  function getValue(ptr, type = 'i8') {
    if (type.endsWith('*')) type = '*';
    switch (type) {
      case 'i1': return HEAP8[ptr];
      case 'i8': return HEAP8[ptr];
      case 'i16': return HEAP16[((ptr)>>1)];
      case 'i32': return HEAP32[((ptr)>>2)];
      case 'i64': return HEAP64[((ptr)>>3)];
      case 'float': return HEAPF32[((ptr)>>2)];
      case 'double': return HEAPF64[((ptr)>>3)];
      case '*': return HEAPU32[((ptr)>>2)];
      default: abort(`invalid type for getValue: ${type}`);
    }
  }

  var noExitRuntime = true;

  var ptrToString = (ptr) => {
      assert(typeof ptr === 'number');
      // Convert to 32-bit unsigned value
      ptr >>>= 0;
      return '0x' + ptr.toString(16).padStart(8, '0');
    };

  
    /**
     * @param {number} ptr
     * @param {number} value
     * @param {string} type
     */
  function setValue(ptr, value, type = 'i8') {
    if (type.endsWith('*')) type = '*';
    switch (type) {
      case 'i1': HEAP8[ptr] = value; break;
      case 'i8': HEAP8[ptr] = value; break;
      case 'i16': HEAP16[((ptr)>>1)] = value; break;
      case 'i32': HEAP32[((ptr)>>2)] = value; break;
      case 'i64': HEAP64[((ptr)>>3)] = BigInt(value); break;
      case 'float': HEAPF32[((ptr)>>2)] = value; break;
      case 'double': HEAPF64[((ptr)>>3)] = value; break;
      case '*': HEAPU32[((ptr)>>2)] = value; break;
      default: abort(`invalid type for setValue: ${type}`);
    }
  }

  var stackRestore = (val) => __emscripten_stack_restore(val);

  var stackSave = () => _emscripten_stack_get_current();

  var warnOnce = (text) => {
      warnOnce.shown ||= {};
      if (!warnOnce.shown[text]) {
        warnOnce.shown[text] = 1;
        err(text);
      }
    };

  var __abort_js = () =>
      abort('native code called abort()');

  var readEmAsmArgsArray = [];
  var readEmAsmArgs = (sigPtr, buf) => {
      // Nobody should have mutated _readEmAsmArgsArray underneath us to be something else than an array.
      assert(Array.isArray(readEmAsmArgsArray));
      // The input buffer is allocated on the stack, so it must be stack-aligned.
      assert(buf % 16 == 0);
      readEmAsmArgsArray.length = 0;
      var ch;
      // Most arguments are i32s, so shift the buffer pointer so it is a plain
      // index into HEAP32.
      while (ch = HEAPU8[sigPtr++]) {
        var chr = String.fromCharCode(ch);
        var validChars = ['d', 'f', 'i', 'p'];
        // In WASM_BIGINT mode we support passing i64 values as bigint.
        validChars.push('j');
        assert(validChars.includes(chr), `Invalid character ${ch}("${chr}") in readEmAsmArgs! Use only [${validChars}], and do not specify "v" for void return argument.`);
        // Floats are always passed as doubles, so all types except for 'i'
        // are 8 bytes and require alignment.
        var wide = (ch != 105);
        wide &= (ch != 112);
        buf += wide && (buf % 8) ? 4 : 0;
        readEmAsmArgsArray.push(
          // Special case for pointers under wasm64 or CAN_ADDRESS_2GB mode.
          ch == 112 ? HEAPU32[((buf)>>2)] :
          ch == 106 ? HEAP64[((buf)>>3)] :
          ch == 105 ?
            HEAP32[((buf)>>2)] :
            HEAPF64[((buf)>>3)]
        );
        buf += wide ? 8 : 4;
      }
      return readEmAsmArgsArray;
    };
  var runEmAsmFunction = (code, sigPtr, argbuf) => {
      var args = readEmAsmArgs(sigPtr, argbuf);
      assert(ASM_CONSTS.hasOwnProperty(code), `No EM_ASM constant found at address ${code}.  The loaded WebAssembly file is likely out of sync with the generated JavaScript.`);
      return ASM_CONSTS[code](...args);
    };
  var _emscripten_asm_const_int = (code, sigPtr, argbuf) => {
      return runEmAsmFunction(code, sigPtr, argbuf);
    };

  var runAndAbortIfError = (func) => {
      try {
        return func();
      } catch (e) {
        abort(e);
      }
    };
  
  var handleException = (e) => {
      // Certain exception types we do not treat as errors since they are used for
      // internal control flow.
      // 1. ExitStatus, which is thrown by exit()
      // 2. "unwind", which is thrown by emscripten_unwind_to_js_event_loop() and others
      //    that wish to return to JS event loop.
      if (e instanceof ExitStatus || e == 'unwind') {
        return EXITSTATUS;
      }
      quit_(1, e);
    };
  
  
  var runtimeKeepaliveCounter = 0;
  var keepRuntimeAlive = () => noExitRuntime || runtimeKeepaliveCounter > 0;
  var _proc_exit = (code) => {
      EXITSTATUS = code;
      if (!keepRuntimeAlive()) {
        Module['onExit']?.(code);
        ABORT = true;
      }
      quit_(code, new ExitStatus(code));
    };
  
  
  /** @suppress {duplicate } */
  /** @param {boolean|number=} implicit */
  var exitJS = (status, implicit) => {
      EXITSTATUS = status;
  
      checkUnflushedContent();
  
      // if exit() was called explicitly, warn the user if the runtime isn't actually being shut down
      if (keepRuntimeAlive() && !implicit) {
        var msg = `program exited (with status: ${status}), but keepRuntimeAlive() is set (counter=${runtimeKeepaliveCounter}) due to an async operation, so halting execution but not exiting the runtime or preventing further async execution (you can use emscripten_force_exit, if you want to force a true shutdown)`;
        readyPromiseReject?.(msg);
        err(msg);
      }
  
      _proc_exit(status);
    };
  var _exit = exitJS;
  
  
  var maybeExit = () => {
      if (!keepRuntimeAlive()) {
        try {
          _exit(EXITSTATUS);
        } catch (e) {
          handleException(e);
        }
      }
    };
  var callUserCallback = (func) => {
      if (ABORT) {
        err('user callback triggered after runtime exited or application aborted.  Ignoring.');
        return;
      }
      try {
        func();
        maybeExit();
      } catch (e) {
        handleException(e);
      }
    };
  
  var runtimeKeepalivePush = () => {
      runtimeKeepaliveCounter += 1;
    };
  
  var runtimeKeepalivePop = () => {
      assert(runtimeKeepaliveCounter > 0);
      runtimeKeepaliveCounter -= 1;
    };
  
  
  var Asyncify = {
  instrumentWasmImports(imports) {
        var importPattern = /^(invoke_.*|__asyncjs__.*)$/;
  
        for (let [x, original] of Object.entries(imports)) {
          if (typeof original == 'function') {
            let isAsyncifyImport = original.isAsync || importPattern.test(x);
            imports[x] = (...args) => {
              var originalAsyncifyState = Asyncify.state;
              try {
                return original(...args);
              } finally {
                // Only asyncify-declared imports are allowed to change the
                // state.
                // Changing the state from normal to disabled is allowed (in any
                // function) as that is what shutdown does (and we don't have an
                // explicit list of shutdown imports).
                var changedToDisabled =
                      originalAsyncifyState === Asyncify.State.Normal &&
                      Asyncify.state        === Asyncify.State.Disabled;
                // invoke_* functions are allowed to change the state if we do
                // not ignore indirect calls.
                var ignoredInvoke = x.startsWith('invoke_') &&
                                    true;
                if (Asyncify.state !== originalAsyncifyState &&
                    !isAsyncifyImport &&
                    !changedToDisabled &&
                    !ignoredInvoke) {
                  abort(`import ${x} was not in ASYNCIFY_IMPORTS, but changed the state`);
                }
              }
            };
          }
        }
      },
  instrumentFunction(original) {
        var wrapper = (...args) => {
          Asyncify.exportCallStack.push(original);
          try {
            return original(...args);
          } finally {
            if (!ABORT) {
              var top = Asyncify.exportCallStack.pop();
              assert(top === original);
              Asyncify.maybeStopUnwind();
            }
          }
        };
        Asyncify.funcWrappers.set(original, wrapper);
        return wrapper;
      },
  instrumentWasmExports(exports) {
        var ret = {};
        for (let [x, original] of Object.entries(exports)) {
          if (typeof original == 'function') {
            var wrapper = Asyncify.instrumentFunction(original);
            ret[x] = wrapper;
  
         } else {
            ret[x] = original;
          }
        }
        return ret;
      },
  State:{
  Normal:0,
  Unwinding:1,
  Rewinding:2,
  Disabled:3,
  },
  state:0,
  StackSize:65536,
  currData:null,
  handleSleepReturnValue:0,
  exportCallStack:[],
  callstackFuncToId:new Map,
  callStackIdToFunc:new Map,
  funcWrappers:new Map,
  callStackId:0,
  asyncPromiseHandlers:null,
  sleepCallbacks:[],
  getCallStackId(func) {
        assert(func);
        if (!Asyncify.callstackFuncToId.has(func)) {
          var id = Asyncify.callStackId++;
          Asyncify.callstackFuncToId.set(func, id);
          Asyncify.callStackIdToFunc.set(id, func);
        }
        return Asyncify.callstackFuncToId.get(func);
      },
  maybeStopUnwind() {
        if (Asyncify.currData &&
            Asyncify.state === Asyncify.State.Unwinding &&
            Asyncify.exportCallStack.length === 0) {
          // We just finished unwinding.
          // Be sure to set the state before calling any other functions to avoid
          // possible infinite recursion here (For example in debug pthread builds
          // the dbg() function itself can call back into WebAssembly to get the
          // current pthread_self() pointer).
          Asyncify.state = Asyncify.State.Normal;
          
          // Keep the runtime alive so that a re-wind can be done later.
          runAndAbortIfError(_asyncify_stop_unwind);
          if (typeof Fibers != 'undefined') {
            Fibers.trampoline();
          }
        }
      },
  whenDone() {
        assert(Asyncify.currData, 'Tried to wait for an async operation when none is in progress.');
        assert(!Asyncify.asyncPromiseHandlers, 'Cannot have multiple async operations in flight at once');
        return new Promise((resolve, reject) => {
          Asyncify.asyncPromiseHandlers = { resolve, reject };
        });
      },
  allocateData() {
        // An asyncify data structure has three fields:
        //  0  current stack pos
        //  4  max stack pos
        //  8  id of function at bottom of the call stack (callStackIdToFunc[id] == wasm func)
        //
        // The Asyncify ABI only interprets the first two fields, the rest is for the runtime.
        // We also embed a stack in the same memory region here, right next to the structure.
        // This struct is also defined as asyncify_data_t in emscripten/fiber.h
        var ptr = _malloc(12 + Asyncify.StackSize);
        Asyncify.setDataHeader(ptr, ptr + 12, Asyncify.StackSize);
        Asyncify.setDataRewindFunc(ptr);
        return ptr;
      },
  setDataHeader(ptr, stack, stackSize) {
        HEAPU32[((ptr)>>2)] = stack;
        HEAPU32[(((ptr)+(4))>>2)] = stack + stackSize;
      },
  setDataRewindFunc(ptr) {
        var bottomOfCallStack = Asyncify.exportCallStack[0];
        assert(bottomOfCallStack, 'exportCallStack is empty');
        var rewindId = Asyncify.getCallStackId(bottomOfCallStack);
        HEAP32[(((ptr)+(8))>>2)] = rewindId;
      },
  getDataRewindFunc(ptr) {
        var id = HEAP32[(((ptr)+(8))>>2)];
        var func = Asyncify.callStackIdToFunc.get(id);
        assert(func, `id ${id} not found in callStackIdToFunc`);
        return func;
      },
  doRewind(ptr) {
        var original = Asyncify.getDataRewindFunc(ptr);
        var func = Asyncify.funcWrappers.get(original);
        assert(original);
        assert(func);
        // Once we have rewound and the stack we no longer need to artificially
        // keep the runtime alive.
        
        return func();
      },
  handleSleep(startAsync) {
        assert(Asyncify.state !== Asyncify.State.Disabled, 'Asyncify cannot be done during or after the runtime exits');
        if (ABORT) return;
        if (Asyncify.state === Asyncify.State.Normal) {
          // Prepare to sleep. Call startAsync, and see what happens:
          // if the code decided to call our callback synchronously,
          // then no async operation was in fact begun, and we don't
          // need to do anything.
          var reachedCallback = false;
          var reachedAfterCallback = false;
          startAsync((handleSleepReturnValue = 0) => {
            assert(!handleSleepReturnValue || typeof handleSleepReturnValue == 'number' || typeof handleSleepReturnValue == 'boolean'); // old emterpretify API supported other stuff
            if (ABORT) return;
            Asyncify.handleSleepReturnValue = handleSleepReturnValue;
            reachedCallback = true;
            if (!reachedAfterCallback) {
              // We are happening synchronously, so no need for async.
              return;
            }
            // This async operation did not happen synchronously, so we did
            // unwind. In that case there can be no compiled code on the stack,
            // as it might break later operations (we can rewind ok now, but if
            // we unwind again, we would unwind through the extra compiled code
            // too).
            assert(!Asyncify.exportCallStack.length, 'Waking up (starting to rewind) must be done from JS, without compiled code on the stack.');
            Asyncify.state = Asyncify.State.Rewinding;
            runAndAbortIfError(() => _asyncify_start_rewind(Asyncify.currData));
            if (typeof MainLoop != 'undefined' && MainLoop.func) {
              MainLoop.resume();
            }
            var asyncWasmReturnValue, isError = false;
            try {
              asyncWasmReturnValue = Asyncify.doRewind(Asyncify.currData);
            } catch (err) {
              asyncWasmReturnValue = err;
              isError = true;
            }
            // Track whether the return value was handled by any promise handlers.
            var handled = false;
            if (!Asyncify.currData) {
              // All asynchronous execution has finished.
              // `asyncWasmReturnValue` now contains the final
              // return value of the exported async WASM function.
              //
              // Note: `asyncWasmReturnValue` is distinct from
              // `Asyncify.handleSleepReturnValue`.
              // `Asyncify.handleSleepReturnValue` contains the return
              // value of the last C function to have executed
              // `Asyncify.handleSleep()`, where as `asyncWasmReturnValue`
              // contains the return value of the exported WASM function
              // that may have called C functions that
              // call `Asyncify.handleSleep()`.
              var asyncPromiseHandlers = Asyncify.asyncPromiseHandlers;
              if (asyncPromiseHandlers) {
                Asyncify.asyncPromiseHandlers = null;
                (isError ? asyncPromiseHandlers.reject : asyncPromiseHandlers.resolve)(asyncWasmReturnValue);
                handled = true;
              }
            }
            if (isError && !handled) {
              // If there was an error and it was not handled by now, we have no choice but to
              // rethrow that error into the global scope where it can be caught only by
              // `onerror` or `onunhandledpromiserejection`.
              throw asyncWasmReturnValue;
            }
          });
          reachedAfterCallback = true;
          if (!reachedCallback) {
            // A true async operation was begun; start a sleep.
            Asyncify.state = Asyncify.State.Unwinding;
            // TODO: reuse, don't alloc/free every sleep
            Asyncify.currData = Asyncify.allocateData();
            if (typeof MainLoop != 'undefined' && MainLoop.func) {
              MainLoop.pause();
            }
            runAndAbortIfError(() => _asyncify_start_unwind(Asyncify.currData));
          }
        } else if (Asyncify.state === Asyncify.State.Rewinding) {
          // Stop a resume.
          Asyncify.state = Asyncify.State.Normal;
          runAndAbortIfError(_asyncify_stop_rewind);
          _free(Asyncify.currData);
          Asyncify.currData = null;
          // Call all sleep callbacks now that the sleep-resume is all done.
          Asyncify.sleepCallbacks.forEach(callUserCallback);
        } else {
          abort(`invalid state: ${Asyncify.state}`);
        }
        return Asyncify.handleSleepReturnValue;
      },
  handleAsync:(startAsync) => Asyncify.handleSleep((wakeUp) => {
        // TODO: add error handling as a second param when handleSleep implements it.
        startAsync().then(wakeUp);
      }),
  };
  
  
  
  var Fibers = {
  nextFiber:0,
  trampolineRunning:false,
  trampoline() {
        if (!Fibers.trampolineRunning && Fibers.nextFiber) {
          Fibers.trampolineRunning = true;
          do {
            var fiber = Fibers.nextFiber;
            Fibers.nextFiber = 0;
            Fibers.finishContextSwitch(fiber);
          } while (Fibers.nextFiber);
          Fibers.trampolineRunning = false;
        }
      },
  finishContextSwitch(newFiber) {
        var stack_base = HEAPU32[((newFiber)>>2)];
        var stack_max =  HEAPU32[(((newFiber)+(4))>>2)];
        _emscripten_stack_set_limits(stack_base, stack_max);
  
        stackRestore(HEAPU32[(((newFiber)+(8))>>2)]);
  
        var entryPoint = HEAPU32[(((newFiber)+(12))>>2)];
  
        if (entryPoint !== 0) {
          Asyncify.currData = null;
          HEAPU32[(((newFiber)+(12))>>2)] = 0;
  
          var userData = HEAPU32[(((newFiber)+(16))>>2)];
          ((a1) => dynCall_vi(entryPoint, a1))(userData);
        } else {
          var asyncifyData = newFiber + 20;
          Asyncify.currData = asyncifyData;
  
          Asyncify.state = Asyncify.State.Rewinding;
          _asyncify_start_rewind(asyncifyData);
          Asyncify.doRewind(asyncifyData);
        }
      },
  };
  
  var _emscripten_fiber_swap = (oldFiber, newFiber) => {
      if (ABORT) return;
      if (Asyncify.state === Asyncify.State.Normal) {
        Asyncify.state = Asyncify.State.Unwinding;
  
        var asyncifyData = oldFiber + 20;
        Asyncify.setDataRewindFunc(asyncifyData);
        Asyncify.currData = asyncifyData;
  
        _asyncify_start_unwind(asyncifyData);
  
        var stackTop = stackSave();
        HEAPU32[(((oldFiber)+(8))>>2)] = stackTop;
  
        Fibers.nextFiber = newFiber;
      } else {
        assert(Asyncify.state === Asyncify.State.Rewinding);
        Asyncify.state = Asyncify.State.Normal;
        _asyncify_stop_rewind();
        Asyncify.currData = null;
      }
    };
  _emscripten_fiber_swap.isAsync = true;

  var _emscripten_get_now = () => performance.now();

  var getHeapMax = () =>
      // Stay one Wasm page short of 4GB: while e.g. Chrome is able to allocate
      // full 4GB Wasm memories, the size will wrap back to 0 bytes in Wasm side
      // for any code that deals with heap sizes, which would require special
      // casing all heap size related code to treat 0 specially.
      2147483648;
  
  var alignMemory = (size, alignment) => {
      assert(alignment, "alignment argument is required");
      return Math.ceil(size / alignment) * alignment;
    };
  
  var growMemory = (size) => {
      var oldHeapSize = wasmMemory.buffer.byteLength;
      var pages = ((size - oldHeapSize + 65535) / 65536) | 0;
      try {
        // round size grow request up to wasm page size (fixed 64KB per spec)
        wasmMemory.grow(pages); // .grow() takes a delta compared to the previous size
        updateMemoryViews();
        return 1 /*success*/;
      } catch(e) {
        err(`growMemory: Attempted to grow heap from ${oldHeapSize} bytes to ${size} bytes, but got error: ${e}`);
      }
      // implicit 0 return to save code size (caller will cast "undefined" into 0
      // anyhow)
    };
  var _emscripten_resize_heap = (requestedSize) => {
      var oldSize = HEAPU8.length;
      // With CAN_ADDRESS_2GB or MEMORY64, pointers are already unsigned.
      requestedSize >>>= 0;
      // With multithreaded builds, races can happen (another thread might increase the size
      // in between), so return a failure, and let the caller retry.
      assert(requestedSize > oldSize);
  
      // Memory resize rules:
      // 1.  Always increase heap size to at least the requested size, rounded up
      //     to next page multiple.
      // 2a. If MEMORY_GROWTH_LINEAR_STEP == -1, excessively resize the heap
      //     geometrically: increase the heap size according to
      //     MEMORY_GROWTH_GEOMETRIC_STEP factor (default +20%), At most
      //     overreserve by MEMORY_GROWTH_GEOMETRIC_CAP bytes (default 96MB).
      // 2b. If MEMORY_GROWTH_LINEAR_STEP != -1, excessively resize the heap
      //     linearly: increase the heap size by at least
      //     MEMORY_GROWTH_LINEAR_STEP bytes.
      // 3.  Max size for the heap is capped at 2048MB-WASM_PAGE_SIZE, or by
      //     MAXIMUM_MEMORY, or by ASAN limit, depending on which is smallest
      // 4.  If we were unable to allocate as much memory, it may be due to
      //     over-eager decision to excessively reserve due to (3) above.
      //     Hence if an allocation fails, cut down on the amount of excess
      //     growth, in an attempt to succeed to perform a smaller allocation.
  
      // A limit is set for how much we can grow. We should not exceed that
      // (the wasm binary specifies it, so if we tried, we'd fail anyhow).
      var maxHeapSize = getHeapMax();
      if (requestedSize > maxHeapSize) {
        err(`Cannot enlarge memory, requested ${requestedSize} bytes, but the limit is ${maxHeapSize} bytes!`);
        return false;
      }
  
      // Loop through potential heap size increases. If we attempt a too eager
      // reservation that fails, cut down on the attempted size and reserve a
      // smaller bump instead. (max 3 times, chosen somewhat arbitrarily)
      for (var cutDown = 1; cutDown <= 4; cutDown *= 2) {
        var overGrownHeapSize = oldSize * (1 + 0.2 / cutDown); // ensure geometric growth
        // but limit overreserving (default to capping at +96MB overgrowth at most)
        overGrownHeapSize = Math.min(overGrownHeapSize, requestedSize + 100663296 );
  
        var newSize = Math.min(maxHeapSize, alignMemory(Math.max(requestedSize, overGrownHeapSize), 65536));
  
        var replacement = growMemory(newSize);
        if (replacement) {
  
          return true;
        }
      }
      err(`Failed to grow the heap from ${oldSize} bytes to ${newSize} bytes, not enough memory!`);
      return false;
    };

  
  
  var _emscripten_set_main_loop_timing = (mode, value) => {
      MainLoop.timingMode = mode;
      MainLoop.timingValue = value;
  
      if (!MainLoop.func) {
        err('emscripten_set_main_loop_timing: Cannot set timing mode for main loop since a main loop does not exist! Call emscripten_set_main_loop first to set one up.');
        return 1; // Return non-zero on failure, can't set timing mode when there is no main loop.
      }
  
      if (!MainLoop.running) {
        
        MainLoop.running = true;
      }
      if (mode == 0) {
        MainLoop.scheduler = function MainLoop_scheduler_setTimeout() {
          var timeUntilNextTick = Math.max(0, MainLoop.tickStartTime + value - _emscripten_get_now())|0;
          setTimeout(MainLoop.runner, timeUntilNextTick); // doing this each time means that on exception, we stop
        };
        MainLoop.method = 'timeout';
      } else if (mode == 1) {
        MainLoop.scheduler = function MainLoop_scheduler_rAF() {
          MainLoop.requestAnimationFrame(MainLoop.runner);
        };
        MainLoop.method = 'rAF';
      } else if (mode == 2) {
        if (typeof MainLoop.setImmediate == 'undefined') {
          if (typeof setImmediate == 'undefined') {
            // Emulate setImmediate. (note: not a complete polyfill, we don't emulate clearImmediate() to keep code size to minimum, since not needed)
            var setImmediates = [];
            var emscriptenMainLoopMessageId = 'setimmediate';
            /** @param {Event} event */
            var MainLoop_setImmediate_messageHandler = (event) => {
              // When called in current thread or Worker, the main loop ID is structured slightly different to accommodate for --proxy-to-worker runtime listening to Worker events,
              // so check for both cases.
              if (event.data === emscriptenMainLoopMessageId || event.data.target === emscriptenMainLoopMessageId) {
                event.stopPropagation();
                setImmediates.shift()();
              }
            };
            addEventListener("message", MainLoop_setImmediate_messageHandler, true);
            MainLoop.setImmediate = /** @type{function(function(): ?, ...?): number} */((func) => {
              setImmediates.push(func);
              if (ENVIRONMENT_IS_WORKER) {
                Module['setImmediates'] ??= [];
                Module['setImmediates'].push(func);
                postMessage({target: emscriptenMainLoopMessageId}); // In --proxy-to-worker, route the message via proxyClient.js
              } else postMessage(emscriptenMainLoopMessageId, "*"); // On the main thread, can just send the message to itself.
            });
          } else {
            MainLoop.setImmediate = setImmediate;
          }
        }
        MainLoop.scheduler = function MainLoop_scheduler_setImmediate() {
          MainLoop.setImmediate(MainLoop.runner);
        };
        MainLoop.method = 'immediate';
      }
      return 0;
    };
  var MainLoop = {
  running:false,
  scheduler:null,
  method:"",
  currentlyRunningMainloop:0,
  func:null,
  arg:0,
  timingMode:0,
  timingValue:0,
  currentFrameNumber:0,
  queue:[],
  preMainLoop:[],
  postMainLoop:[],
  pause() {
        MainLoop.scheduler = null;
        // Incrementing this signals the previous main loop that it's now become old, and it must return.
        MainLoop.currentlyRunningMainloop++;
      },
  resume() {
        MainLoop.currentlyRunningMainloop++;
        var timingMode = MainLoop.timingMode;
        var timingValue = MainLoop.timingValue;
        var func = MainLoop.func;
        MainLoop.func = null;
        // do not set timing and call scheduler, we will do it on the next lines
        setMainLoop(func, 0, false, MainLoop.arg, true);
        _emscripten_set_main_loop_timing(timingMode, timingValue);
        MainLoop.scheduler();
      },
  updateStatus() {
        if (Module['setStatus']) {
          var message = Module['statusMessage'] || 'Please wait...';
          var remaining = MainLoop.remainingBlockers ?? 0;
          var expected = MainLoop.expectedBlockers ?? 0;
          if (remaining) {
            if (remaining < expected) {
              Module['setStatus'](`{message} ({expected - remaining}/{expected})`);
            } else {
              Module['setStatus'](message);
            }
          } else {
            Module['setStatus']('');
          }
        }
      },
  init() {
        Module['preMainLoop'] && MainLoop.preMainLoop.push(Module['preMainLoop']);
        Module['postMainLoop'] && MainLoop.postMainLoop.push(Module['postMainLoop']);
      },
  runIter(func) {
        if (ABORT) return;
        for (var pre of MainLoop.preMainLoop) {
          if (pre() === false) {
            return; // |return false| skips a frame
          }
        }
        callUserCallback(func);
        for (var post of MainLoop.postMainLoop) {
          post();
        }
      },
  nextRAF:0,
  fakeRequestAnimationFrame(func) {
        // try to keep 60fps between calls to here
        var now = Date.now();
        if (MainLoop.nextRAF === 0) {
          MainLoop.nextRAF = now + 1000/60;
        } else {
          while (now + 2 >= MainLoop.nextRAF) { // fudge a little, to avoid timer jitter causing us to do lots of delay:0
            MainLoop.nextRAF += 1000/60;
          }
        }
        var delay = Math.max(MainLoop.nextRAF - now, 0);
        setTimeout(func, delay);
      },
  requestAnimationFrame(func) {
        if (typeof requestAnimationFrame == 'function') {
          requestAnimationFrame(func);
        } else {
          MainLoop.fakeRequestAnimationFrame(func);
        }
      },
  };
  
  
  
  
    /**
     * @param {number=} arg
     * @param {boolean=} noSetTiming
     */
  var setMainLoop = (iterFunc, fps, simulateInfiniteLoop, arg, noSetTiming) => {
      assert(!MainLoop.func, 'emscripten_set_main_loop: there can only be one main loop function at once: call emscripten_cancel_main_loop to cancel the previous one before setting a new one with different parameters.');
      MainLoop.func = iterFunc;
      MainLoop.arg = arg;
  
      var thisMainLoopId = MainLoop.currentlyRunningMainloop;
      function checkIsRunning() {
        if (thisMainLoopId < MainLoop.currentlyRunningMainloop) {
          
          maybeExit();
          return false;
        }
        return true;
      }
  
      // We create the loop runner here but it is not actually running until
      // _emscripten_set_main_loop_timing is called (which might happen a
      // later time).  This member signifies that the current runner has not
      // yet been started so that we can call runtimeKeepalivePush when it
      // gets it timing set for the first time.
      MainLoop.running = false;
      MainLoop.runner = function MainLoop_runner() {
        if (ABORT) return;
        if (MainLoop.queue.length > 0) {
          var start = Date.now();
          var blocker = MainLoop.queue.shift();
          blocker.func(blocker.arg);
          if (MainLoop.remainingBlockers) {
            var remaining = MainLoop.remainingBlockers;
            var next = remaining%1 == 0 ? remaining-1 : Math.floor(remaining);
            if (blocker.counted) {
              MainLoop.remainingBlockers = next;
            } else {
              // not counted, but move the progress along a tiny bit
              next = next + 0.5; // do not steal all the next one's progress
              MainLoop.remainingBlockers = (8*remaining + next)/9;
            }
          }
          MainLoop.updateStatus();
  
          // catches pause/resume main loop from blocker execution
          if (!checkIsRunning()) return;
  
          setTimeout(MainLoop.runner, 0);
          return;
        }
  
        // catch pauses from non-main loop sources
        if (!checkIsRunning()) return;
  
        // Implement very basic swap interval control
        MainLoop.currentFrameNumber = MainLoop.currentFrameNumber + 1 | 0;
        if (MainLoop.timingMode == 1 && MainLoop.timingValue > 1 && MainLoop.currentFrameNumber % MainLoop.timingValue != 0) {
          // Not the scheduled time to render this frame - skip.
          MainLoop.scheduler();
          return;
        } else if (MainLoop.timingMode == 0) {
          MainLoop.tickStartTime = _emscripten_get_now();
        }
  
        if (MainLoop.method === 'timeout' && Module['ctx']) {
          warnOnce('Looks like you are rendering without using requestAnimationFrame for the main loop. You should use 0 for the frame rate in emscripten_set_main_loop in order to use requestAnimationFrame, as that can greatly improve your frame rates!');
          MainLoop.method = ''; // just warn once per call to set main loop
        }
  
        MainLoop.runIter(iterFunc);
  
        // catch pauses from the main loop itself
        if (!checkIsRunning()) return;
  
        MainLoop.scheduler();
      }
  
      if (!noSetTiming) {
        if (fps > 0) {
          _emscripten_set_main_loop_timing(0, 1000.0 / fps);
        } else {
          // Do rAF by rendering each frame (no decimating)
          _emscripten_set_main_loop_timing(1, 1);
        }
  
        MainLoop.scheduler();
      }
  
      if (simulateInfiniteLoop) {
        throw 'unwind';
      }
    };
  var _emscripten_set_main_loop = (func, fps, simulateInfiniteLoop) => {
      var iterFunc = (() => dynCall_v(func));
      setMainLoop(iterFunc, fps, simulateInfiniteLoop);
    };


  var GLctx;
  
  var webgl_enable_WEBGL_draw_instanced_base_vertex_base_instance = (ctx) =>
      // Closure is expected to be allowed to minify the '.dibvbi' property, so not accessing it quoted.
      !!(ctx.dibvbi = ctx.getExtension('WEBGL_draw_instanced_base_vertex_base_instance'));
  
  var webgl_enable_WEBGL_multi_draw_instanced_base_vertex_base_instance = (ctx) => {
      // Closure is expected to be allowed to minify the '.mdibvbi' property, so not accessing it quoted.
      return !!(ctx.mdibvbi = ctx.getExtension('WEBGL_multi_draw_instanced_base_vertex_base_instance'));
    };
  
  var webgl_enable_EXT_polygon_offset_clamp = (ctx) =>
      !!(ctx.extPolygonOffsetClamp = ctx.getExtension('EXT_polygon_offset_clamp'));
  
  var webgl_enable_EXT_clip_control = (ctx) =>
      !!(ctx.extClipControl = ctx.getExtension('EXT_clip_control'));
  
  var webgl_enable_WEBGL_polygon_mode = (ctx) =>
      !!(ctx.webglPolygonMode = ctx.getExtension('WEBGL_polygon_mode'));
  
  var webgl_enable_WEBGL_multi_draw = (ctx) =>
      // Closure is expected to be allowed to minify the '.multiDrawWebgl' property, so not accessing it quoted.
      !!(ctx.multiDrawWebgl = ctx.getExtension('WEBGL_multi_draw'));
  
  var getEmscriptenSupportedExtensions = (ctx) => {
      // Restrict the list of advertised extensions to those that we actually
      // support.
      var supportedExtensions = [
        // WebGL 2 extensions
        'EXT_color_buffer_float',
        'EXT_conservative_depth',
        'EXT_disjoint_timer_query_webgl2',
        'EXT_texture_norm16',
        'NV_shader_noperspective_interpolation',
        'WEBGL_clip_cull_distance',
        // WebGL 1 and WebGL 2 extensions
        'EXT_clip_control',
        'EXT_color_buffer_half_float',
        'EXT_depth_clamp',
        'EXT_float_blend',
        'EXT_polygon_offset_clamp',
        'EXT_texture_compression_bptc',
        'EXT_texture_compression_rgtc',
        'EXT_texture_filter_anisotropic',
        'KHR_parallel_shader_compile',
        'OES_texture_float_linear',
        'WEBGL_blend_func_extended',
        'WEBGL_compressed_texture_astc',
        'WEBGL_compressed_texture_etc',
        'WEBGL_compressed_texture_etc1',
        'WEBGL_compressed_texture_s3tc',
        'WEBGL_compressed_texture_s3tc_srgb',
        'WEBGL_debug_renderer_info',
        'WEBGL_debug_shaders',
        'WEBGL_lose_context',
        'WEBGL_multi_draw',
        'WEBGL_polygon_mode'
      ];
      // .getSupportedExtensions() can return null if context is lost, so coerce to empty array.
      return (ctx.getSupportedExtensions() || []).filter(ext => supportedExtensions.includes(ext));
    };
  
  
  var UTF8Decoder = typeof TextDecoder != 'undefined' ? new TextDecoder() : undefined;
  
  var findStringEnd = (heapOrArray, idx, maxBytesToRead, ignoreNul) => {
      var maxIdx = idx + maxBytesToRead;
      if (ignoreNul) return maxIdx;
      // TextDecoder needs to know the byte length in advance, it doesn't stop on
      // null terminator by itself.
      // As a tiny code save trick, compare idx against maxIdx using a negation,
      // so that maxBytesToRead=undefined/NaN means Infinity.
      while (heapOrArray[idx] && !(idx >= maxIdx)) ++idx;
      return idx;
    };
  
  
    /**
     * Given a pointer 'idx' to a null-terminated UTF8-encoded string in the given
     * array that contains uint8 values, returns a copy of that string as a
     * Javascript String object.
     * heapOrArray is either a regular array, or a JavaScript typed array view.
     * @param {number=} idx
     * @param {number=} maxBytesToRead
     * @param {boolean=} ignoreNul - If true, the function will not stop on a NUL character.
     * @return {string}
     */
  var UTF8ArrayToString = (heapOrArray, idx = 0, maxBytesToRead, ignoreNul) => {
  
      var endPtr = findStringEnd(heapOrArray, idx, maxBytesToRead, ignoreNul);
  
      // When using conditional TextDecoder, skip it for short strings as the overhead of the native call is not worth it.
      if (endPtr - idx > 16 && heapOrArray.buffer && UTF8Decoder) {
        return UTF8Decoder.decode(heapOrArray.subarray(idx, endPtr));
      }
      var str = '';
      while (idx < endPtr) {
        // For UTF8 byte structure, see:
        // http://en.wikipedia.org/wiki/UTF-8#Description
        // https://www.ietf.org/rfc/rfc2279.txt
        // https://tools.ietf.org/html/rfc3629
        var u0 = heapOrArray[idx++];
        if (!(u0 & 0x80)) { str += String.fromCharCode(u0); continue; }
        var u1 = heapOrArray[idx++] & 63;
        if ((u0 & 0xE0) == 0xC0) { str += String.fromCharCode(((u0 & 31) << 6) | u1); continue; }
        var u2 = heapOrArray[idx++] & 63;
        if ((u0 & 0xF0) == 0xE0) {
          u0 = ((u0 & 15) << 12) | (u1 << 6) | u2;
        } else {
          if ((u0 & 0xF8) != 0xF0) warnOnce('Invalid UTF-8 leading byte ' + ptrToString(u0) + ' encountered when deserializing a UTF-8 string in wasm memory to a JS string!');
          u0 = ((u0 & 7) << 18) | (u1 << 12) | (u2 << 6) | (heapOrArray[idx++] & 63);
        }
  
        if (u0 < 0x10000) {
          str += String.fromCharCode(u0);
        } else {
          var ch = u0 - 0x10000;
          str += String.fromCharCode(0xD800 | (ch >> 10), 0xDC00 | (ch & 0x3FF));
        }
      }
      return str;
    };
  
    /**
     * Given a pointer 'ptr' to a null-terminated UTF8-encoded string in the
     * emscripten HEAP, returns a copy of that string as a Javascript String object.
     *
     * @param {number} ptr
     * @param {number=} maxBytesToRead - An optional length that specifies the
     *   maximum number of bytes to read. You can omit this parameter to scan the
     *   string until the first 0 byte. If maxBytesToRead is passed, and the string
     *   at [ptr, ptr+maxBytesToReadr[ contains a null byte in the middle, then the
     *   string will cut short at that byte index.
     * @param {boolean=} ignoreNul - If true, the function will not stop on a NUL character.
     * @return {string}
     */
  var UTF8ToString = (ptr, maxBytesToRead, ignoreNul) => {
      assert(typeof ptr == 'number', `UTF8ToString expects a number (got ${typeof ptr})`);
      return ptr ? UTF8ArrayToString(HEAPU8, ptr, maxBytesToRead, ignoreNul) : '';
    };
  var GL = {
  counter:1,
  buffers:[],
  programs:[],
  framebuffers:[],
  renderbuffers:[],
  textures:[],
  shaders:[],
  vaos:[],
  contexts:[],
  offscreenCanvases:{
  },
  queries:[],
  samplers:[],
  transformFeedbacks:[],
  syncs:[],
  stringCache:{
  },
  stringiCache:{
  },
  unpackAlignment:4,
  unpackRowLength:0,
  recordError:(errorCode) => {
        if (!GL.lastError) {
          GL.lastError = errorCode;
        }
      },
  getNewId:(table) => {
        var ret = GL.counter++;
        for (var i = table.length; i < ret; i++) {
          table[i] = null;
        }
        return ret;
      },
  genObject:(n, buffers, createFunction, objectTable
        ) => {
        for (var i = 0; i < n; i++) {
          var buffer = GLctx[createFunction]();
          var id = buffer && GL.getNewId(objectTable);
          if (buffer) {
            buffer.name = id;
            objectTable[id] = buffer;
          } else {
            GL.recordError(0x502 /* GL_INVALID_OPERATION */);
          }
          HEAP32[(((buffers)+(i*4))>>2)] = id;
        }
      },
  getSource:(shader, count, string, length) => {
        var source = '';
        for (var i = 0; i < count; ++i) {
          var len = length ? HEAPU32[(((length)+(i*4))>>2)] : undefined;
          source += UTF8ToString(HEAPU32[(((string)+(i*4))>>2)], len);
        }
        return source;
      },
  createContext:(/** @type {HTMLCanvasElement} */ canvas, webGLContextAttributes) => {
  
        var ctx = canvas.getContext("webgl2", webGLContextAttributes);
  
        if (!ctx) return 0;
  
        var handle = GL.registerContext(ctx, webGLContextAttributes);
  
        return handle;
      },
  registerContext:(ctx, webGLContextAttributes) => {
        // without pthreads a context is just an integer ID
        var handle = GL.getNewId(GL.contexts);
  
        var context = {
          handle,
          attributes: webGLContextAttributes,
          version: webGLContextAttributes.majorVersion,
          GLctx: ctx
        };
  
        // Store the created context object so that we can access the context
        // given a canvas without having to pass the parameters again.
        if (ctx.canvas) ctx.canvas.GLctxObject = context;
        GL.contexts[handle] = context;
        if (typeof webGLContextAttributes.enableExtensionsByDefault == 'undefined' || webGLContextAttributes.enableExtensionsByDefault) {
          GL.initExtensions(context);
        }
  
        return handle;
      },
  makeContextCurrent:(contextHandle) => {
  
        // Active Emscripten GL layer context object.
        GL.currentContext = GL.contexts[contextHandle];
        // Active WebGL context object.
        Module['ctx'] = GLctx = GL.currentContext?.GLctx;
        return !(contextHandle && !GLctx);
      },
  getContext:(contextHandle) => {
        return GL.contexts[contextHandle];
      },
  deleteContext:(contextHandle) => {
        if (GL.currentContext === GL.contexts[contextHandle]) {
          GL.currentContext = null;
        }
        if (typeof JSEvents == 'object') {
          // Release all JS event handlers on the DOM element that the GL context is
          // associated with since the context is now deleted.
          JSEvents.removeAllHandlersOnTarget(GL.contexts[contextHandle].GLctx.canvas);
        }
        // Make sure the canvas object no longer refers to the context object so
        // there are no GC surprises.
        if (GL.contexts[contextHandle]?.GLctx.canvas) {
          GL.contexts[contextHandle].GLctx.canvas.GLctxObject = undefined;
        }
        GL.contexts[contextHandle] = null;
      },
  initExtensions:(context) => {
        // If this function is called without a specific context object, init the
        // extensions of the currently active context.
        context ||= GL.currentContext;
  
        if (context.initExtensionsDone) return;
        context.initExtensionsDone = true;
  
        var GLctx = context.GLctx;
  
        // Detect the presence of a few extensions manually, ction GL interop
        // layer itself will need to know if they exist.
  
        // Extensions that are available in both WebGL 1 and WebGL 2
        webgl_enable_WEBGL_multi_draw(GLctx);
        webgl_enable_EXT_polygon_offset_clamp(GLctx);
        webgl_enable_EXT_clip_control(GLctx);
        webgl_enable_WEBGL_polygon_mode(GLctx);
        // Extensions that are available from WebGL >= 2 (no-op if called on a WebGL 1 context active)
        webgl_enable_WEBGL_draw_instanced_base_vertex_base_instance(GLctx);
        webgl_enable_WEBGL_multi_draw_instanced_base_vertex_base_instance(GLctx);
  
        // On WebGL 2, EXT_disjoint_timer_query is replaced with an alternative
        // that's based on core APIs, and exposes only the queryCounterEXT()
        // entrypoint.
        if (context.version >= 2) {
          GLctx.disjointTimerQueryExt = GLctx.getExtension("EXT_disjoint_timer_query_webgl2");
        }
  
        // However, Firefox exposes the WebGL 1 version on WebGL 2 as well and
        // thus we look for the WebGL 1 version again if the WebGL 2 version
        // isn't present. https://bugzilla.mozilla.org/show_bug.cgi?id=1328882
        if (context.version < 2 || !GLctx.disjointTimerQueryExt)
        {
          GLctx.disjointTimerQueryExt = GLctx.getExtension("EXT_disjoint_timer_query");
        }
  
        getEmscriptenSupportedExtensions(GLctx).forEach((ext) => {
          // WEBGL_lose_context, WEBGL_debug_renderer_info and WEBGL_debug_shaders
          // are not enabled by default.
          if (!ext.includes('lose_context') && !ext.includes('debug')) {
            // Call .getExtension() to enable that extension permanently.
            GLctx.getExtension(ext);
          }
        });
      },
  };
  var _emscripten_webgl_make_context_current = (contextHandle) => {
      var success = GL.makeContextCurrent(contextHandle);
      return success ? 0 : -5;
    };

  var SYSCALLS = {
  varargs:undefined,
  getStr(ptr) {
        var ret = UTF8ToString(ptr);
        return ret;
      },
  };
  var _fd_close = (fd) => {
      abort('fd_close called without SYSCALLS_REQUIRE_FILESYSTEM');
    };

  var INT53_MAX = 9007199254740992;
  
  var INT53_MIN = -9007199254740992;
  var bigintToI53Checked = (num) => (num < INT53_MIN || num > INT53_MAX) ? NaN : Number(num);
  function _fd_seek(fd, offset, whence, newOffset) {
    offset = bigintToI53Checked(offset);
  
  
      return 70;
    ;
  }

  var printCharBuffers = [null,[],[]];
  
  var printChar = (stream, curr) => {
      var buffer = printCharBuffers[stream];
      assert(buffer);
      if (curr === 0 || curr === 10) {
        (stream === 1 ? out : err)(UTF8ArrayToString(buffer));
        buffer.length = 0;
      } else {
        buffer.push(curr);
      }
    };
  
  var flush_NO_FILESYSTEM = () => {
      // flush anything remaining in the buffers during shutdown
      _fflush(0);
      if (printCharBuffers[1].length) printChar(1, 10);
      if (printCharBuffers[2].length) printChar(2, 10);
    };
  
  
  var _fd_write = (fd, iov, iovcnt, pnum) => {
      // hack to support printf in SYSCALLS_REQUIRE_FILESYSTEM=0
      var num = 0;
      for (var i = 0; i < iovcnt; i++) {
        var ptr = HEAPU32[((iov)>>2)];
        var len = HEAPU32[(((iov)+(4))>>2)];
        iov += 8;
        for (var j = 0; j < len; j++) {
          printChar(fd, HEAPU8[ptr+j]);
        }
        num += len;
      }
      HEAPU32[((pnum)>>2)] = num;
      return 0;
    };

  var _glActiveTexture = (x0) => GLctx.activeTexture(x0);

  var _glAttachShader = (program, shader) => {
      GLctx.attachShader(GL.programs[program], GL.shaders[shader]);
    };

  
  var _glBindAttribLocation = (program, index, name) => {
      GLctx.bindAttribLocation(GL.programs[program], index, UTF8ToString(name));
    };

  var _glBindBuffer = (target, buffer) => {
  
      if (target == 0x88EB /*GL_PIXEL_PACK_BUFFER*/) {
        // In WebGL 2 glReadPixels entry point, we need to use a different WebGL 2
        // API function call when a buffer is bound to
        // GL_PIXEL_PACK_BUFFER_BINDING point, so must keep track whether that
        // binding point is non-null to know what is the proper API function to
        // call.
        GLctx.currentPixelPackBufferBinding = buffer;
      } else if (target == 0x88EC /*GL_PIXEL_UNPACK_BUFFER*/) {
        // In WebGL 2 gl(Compressed)Tex(Sub)Image[23]D entry points, we need to
        // use a different WebGL 2 API function call when a buffer is bound to
        // GL_PIXEL_UNPACK_BUFFER_BINDING point, so must keep track whether that
        // binding point is non-null to know what is the proper API function to
        // call.
        GLctx.currentPixelUnpackBufferBinding = buffer;
      }
      GLctx.bindBuffer(target, GL.buffers[buffer]);
    };

  var _glBindFramebuffer = (target, framebuffer) => {
  
      GLctx.bindFramebuffer(target, GL.framebuffers[framebuffer]);
  
    };

  var _glBindTexture = (target, texture) => {
      GLctx.bindTexture(target, GL.textures[texture]);
    };

  var _glBindVertexArray = (vao) => {
      GLctx.bindVertexArray(GL.vaos[vao]);
    };

  var _glBlendFunc = (x0, x1) => GLctx.blendFunc(x0, x1);

  var _glBlitFramebuffer = (x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) => GLctx.blitFramebuffer(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9);

  var _glBufferData = (target, size, data, usage) => {
  
      if (true) {
        // If size is zero, WebGL would interpret uploading the whole input
        // arraybuffer (starting from given offset), which would not make sense in
        // WebAssembly, so avoid uploading if size is zero. However we must still
        // call bufferData to establish a backing storage of zero bytes.
        if (data && size) {
          GLctx.bufferData(target, HEAPU8, usage, data, size);
        } else {
          GLctx.bufferData(target, size, usage);
        }
        return;
      }
    };

  var _glClear = (x0) => GLctx.clear(x0);

  var _glClearColor = (x0, x1, x2, x3) => GLctx.clearColor(x0, x1, x2, x3);

  var _glColorMask = (red, green, blue, alpha) => {
      GLctx.colorMask(!!red, !!green, !!blue, !!alpha);
    };

  var _glCompileShader = (shader) => {
      GLctx.compileShader(GL.shaders[shader]);
    };

  var _glCopyTexSubImage2D = (x0, x1, x2, x3, x4, x5, x6, x7) => GLctx.copyTexSubImage2D(x0, x1, x2, x3, x4, x5, x6, x7);

  var _glCreateProgram = () => {
      var id = GL.getNewId(GL.programs);
      var program = GLctx.createProgram();
      // Store additional information needed for each shader program:
      program.name = id;
      // Lazy cache results of
      // glGetProgramiv(GL_ACTIVE_UNIFORM_MAX_LENGTH/GL_ACTIVE_ATTRIBUTE_MAX_LENGTH/GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH)
      program.maxUniformLength = program.maxAttributeLength = program.maxUniformBlockNameLength = 0;
      program.uniformIdCounter = 1;
      GL.programs[id] = program;
      return id;
    };

  var _glCreateShader = (shaderType) => {
      var id = GL.getNewId(GL.shaders);
      GL.shaders[id] = GLctx.createShader(shaderType);
  
      return id;
    };

  var _glDepthFunc = (x0) => GLctx.depthFunc(x0);

  var _glDepthMask = (flag) => {
      GLctx.depthMask(!!flag);
    };

  var _glDisable = (x0) => GLctx.disable(x0);

  var _glDrawArrays = (mode, first, count) => {
  
      GLctx.drawArrays(mode, first, count);
  
    };

  var _glEnable = (x0) => GLctx.enable(x0);

  var _glEnableVertexAttribArray = (index) => {
      GLctx.enableVertexAttribArray(index);
    };

  var _glFinish = () => GLctx.finish();

  var _glFramebufferTexture2D = (target, attachment, textarget, texture, level) => {
      GLctx.framebufferTexture2D(target, attachment, textarget,
                                      GL.textures[texture], level);
    };

  var _glGenBuffers = (n, buffers) => {
      GL.genObject(n, buffers, 'createBuffer', GL.buffers
        );
    };

  var _glGenFramebuffers = (n, ids) => {
      GL.genObject(n, ids, 'createFramebuffer', GL.framebuffers
        );
    };

  var _glGenTextures = (n, textures) => {
      GL.genObject(n, textures, 'createTexture', GL.textures
        );
    };

  var _glGenVertexArrays = (n, arrays) => {
      GL.genObject(n, arrays, 'createVertexArray', GL.vaos
        );
    };

  var _glGetError = () => {
      var error = GLctx.getError() || GL.lastError;
      GL.lastError = 0/*GL_NO_ERROR*/;
      return error;
    };

  var readI53FromI64 = (ptr) => {
      return HEAPU32[((ptr)>>2)] + HEAP32[(((ptr)+(4))>>2)] * 4294967296;
    };
  
  var readI53FromU64 = (ptr) => {
      return HEAPU32[((ptr)>>2)] + HEAPU32[(((ptr)+(4))>>2)] * 4294967296;
    };
  var writeI53ToI64 = (ptr, num) => {
      HEAPU32[((ptr)>>2)] = num;
      var lower = HEAPU32[((ptr)>>2)];
      HEAPU32[(((ptr)+(4))>>2)] = (num - lower)/4294967296;
      var deserialized = (num >= 0) ? readI53FromU64(ptr) : readI53FromI64(ptr);
      var offset = ((ptr)>>2);
      if (deserialized != num) warnOnce(`writeI53ToI64() out of range: serialized JS Number ${num} to Wasm heap as bytes lo=${ptrToString(HEAPU32[offset])}, hi=${ptrToString(HEAPU32[offset+1])}, which deserializes back to ${deserialized} instead!`);
    };
  
  
  var webglGetExtensions = () => {
      var exts = getEmscriptenSupportedExtensions(GLctx);
      exts = exts.concat(exts.map((e) => "GL_" + e));
      return exts;
    };
  
  var emscriptenWebGLGet = (name_, p, type) => {
      // Guard against user passing a null pointer.
      // Note that GLES2 spec does not say anything about how passing a null
      // pointer should be treated.  Testing on desktop core GL 3, the application
      // crashes on glGetIntegerv to a null pointer, but better to report an error
      // instead of doing anything random.
      if (!p) {
        GL.recordError(0x501 /* GL_INVALID_VALUE */);
        return;
      }
      var ret = undefined;
      switch (name_) { // Handle a few trivial GLES values
        case 0x8DFA: // GL_SHADER_COMPILER
          ret = 1;
          break;
        case 0x8DF8: // GL_SHADER_BINARY_FORMATS
          if (type != 0 && type != 1) {
            GL.recordError(0x500); // GL_INVALID_ENUM
          }
          // Do not write anything to the out pointer, since no binary formats are
          // supported.
          return;
        case 0x87FE: // GL_NUM_PROGRAM_BINARY_FORMATS
        case 0x8DF9: // GL_NUM_SHADER_BINARY_FORMATS
          ret = 0;
          break;
        case 0x86A2: // GL_NUM_COMPRESSED_TEXTURE_FORMATS
          // WebGL doesn't have GL_NUM_COMPRESSED_TEXTURE_FORMATS (it's obsolete
          // since GL_COMPRESSED_TEXTURE_FORMATS returns a JS array that can be
          // queried for length), so implement it ourselves to allow C++ GLES2
          // code get the length.
          var formats = GLctx.getParameter(0x86A3 /*GL_COMPRESSED_TEXTURE_FORMATS*/);
          ret = formats ? formats.length : 0;
          break;
  
        case 0x821D: // GL_NUM_EXTENSIONS
          if (GL.currentContext.version < 2) {
            // Calling GLES3/WebGL2 function with a GLES2/WebGL1 context
            GL.recordError(0x502 /* GL_INVALID_OPERATION */);
            return;
          }
          ret = webglGetExtensions().length;
          break;
        case 0x821B: // GL_MAJOR_VERSION
        case 0x821C: // GL_MINOR_VERSION
          if (GL.currentContext.version < 2) {
            GL.recordError(0x500); // GL_INVALID_ENUM
            return;
          }
          ret = name_ == 0x821B ? 3 : 0; // return version 3.0
          break;
      }
  
      if (ret === undefined) {
        var result = GLctx.getParameter(name_);
        switch (typeof result) {
          case "number":
            ret = result;
            break;
          case "boolean":
            ret = result ? 1 : 0;
            break;
          case "string":
            GL.recordError(0x500); // GL_INVALID_ENUM
            return;
          case "object":
            if (result === null) {
              // null is a valid result for some (e.g., which buffer is bound -
              // perhaps nothing is bound), but otherwise can mean an invalid
              // name_, which we need to report as an error
              switch (name_) {
                case 0x8894: // ARRAY_BUFFER_BINDING
                case 0x8B8D: // CURRENT_PROGRAM
                case 0x8895: // ELEMENT_ARRAY_BUFFER_BINDING
                case 0x8CA6: // FRAMEBUFFER_BINDING or DRAW_FRAMEBUFFER_BINDING
                case 0x8CA7: // RENDERBUFFER_BINDING
                case 0x8069: // TEXTURE_BINDING_2D
                case 0x85B5: // WebGL 2 GL_VERTEX_ARRAY_BINDING, or WebGL 1 extension OES_vertex_array_object GL_VERTEX_ARRAY_BINDING_OES
                case 0x8F36: // COPY_READ_BUFFER_BINDING or COPY_READ_BUFFER
                case 0x8F37: // COPY_WRITE_BUFFER_BINDING or COPY_WRITE_BUFFER
                case 0x88ED: // PIXEL_PACK_BUFFER_BINDING
                case 0x88EF: // PIXEL_UNPACK_BUFFER_BINDING
                case 0x8CAA: // READ_FRAMEBUFFER_BINDING
                case 0x8919: // SAMPLER_BINDING
                case 0x8C1D: // TEXTURE_BINDING_2D_ARRAY
                case 0x806A: // TEXTURE_BINDING_3D
                case 0x8E25: // TRANSFORM_FEEDBACK_BINDING
                case 0x8C8F: // TRANSFORM_FEEDBACK_BUFFER_BINDING
                case 0x8A28: // UNIFORM_BUFFER_BINDING
                case 0x8514: { // TEXTURE_BINDING_CUBE_MAP
                  ret = 0;
                  break;
                }
                default: {
                  GL.recordError(0x500); // GL_INVALID_ENUM
                  return;
                }
              }
            } else if (result instanceof Float32Array ||
                       result instanceof Uint32Array ||
                       result instanceof Int32Array ||
                       result instanceof Array) {
              for (var i = 0; i < result.length; ++i) {
                switch (type) {
                  case 0: HEAP32[(((p)+(i*4))>>2)] = result[i]; break;
                  case 2: HEAPF32[(((p)+(i*4))>>2)] = result[i]; break;
                  case 4: HEAP8[(p)+(i)] = result[i] ? 1 : 0; break;
                }
              }
              return;
            } else {
              try {
                ret = result.name | 0;
              } catch(e) {
                GL.recordError(0x500); // GL_INVALID_ENUM
                err(`GL_INVALID_ENUM in glGet${type}v: Unknown object returned from WebGL getParameter(${name_})! (error: ${e})`);
                return;
              }
            }
            break;
          default:
            GL.recordError(0x500); // GL_INVALID_ENUM
            err(`GL_INVALID_ENUM in glGet${type}v: Native code calling glGet${type}v(${name_}) and it returns ${result} of type ${typeof(result)}!`);
            return;
        }
      }
  
      switch (type) {
        case 1: writeI53ToI64(p, ret); break;
        case 0: HEAP32[((p)>>2)] = ret; break;
        case 2:   HEAPF32[((p)>>2)] = ret; break;
        case 4: HEAP8[p] = ret ? 1 : 0; break;
      }
    };
  
  var _glGetIntegerv = (name_, p) => emscriptenWebGLGet(name_, p, 0);

  var _glGetProgramiv = (program, pname, p) => {
      if (!p) {
        // GLES2 specification does not specify how to behave if p is a null
        // pointer. Since calling this function does not make sense if p == null,
        // issue a GL error to notify user about it.
        GL.recordError(0x501 /* GL_INVALID_VALUE */);
        return;
      }
  
      if (program >= GL.counter) {
        GL.recordError(0x501 /* GL_INVALID_VALUE */);
        return;
      }
  
      program = GL.programs[program];
  
      if (pname == 0x8B84) { // GL_INFO_LOG_LENGTH
        var log = GLctx.getProgramInfoLog(program);
        if (log === null) log = '(unknown error)';
        HEAP32[((p)>>2)] = log.length + 1;
      } else if (pname == 0x8B87 /* GL_ACTIVE_UNIFORM_MAX_LENGTH */) {
        if (!program.maxUniformLength) {
          var numActiveUniforms = GLctx.getProgramParameter(program, 0x8B86/*GL_ACTIVE_UNIFORMS*/);
          for (var i = 0; i < numActiveUniforms; ++i) {
            program.maxUniformLength = Math.max(program.maxUniformLength, GLctx.getActiveUniform(program, i).name.length+1);
          }
        }
        HEAP32[((p)>>2)] = program.maxUniformLength;
      } else if (pname == 0x8B8A /* GL_ACTIVE_ATTRIBUTE_MAX_LENGTH */) {
        if (!program.maxAttributeLength) {
          var numActiveAttributes = GLctx.getProgramParameter(program, 0x8B89/*GL_ACTIVE_ATTRIBUTES*/);
          for (var i = 0; i < numActiveAttributes; ++i) {
            program.maxAttributeLength = Math.max(program.maxAttributeLength, GLctx.getActiveAttrib(program, i).name.length+1);
          }
        }
        HEAP32[((p)>>2)] = program.maxAttributeLength;
      } else if (pname == 0x8A35 /* GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH */) {
        if (!program.maxUniformBlockNameLength) {
          var numActiveUniformBlocks = GLctx.getProgramParameter(program, 0x8A36/*GL_ACTIVE_UNIFORM_BLOCKS*/);
          for (var i = 0; i < numActiveUniformBlocks; ++i) {
            program.maxUniformBlockNameLength = Math.max(program.maxUniformBlockNameLength, GLctx.getActiveUniformBlockName(program, i).length+1);
          }
        }
        HEAP32[((p)>>2)] = program.maxUniformBlockNameLength;
      } else {
        HEAP32[((p)>>2)] = GLctx.getProgramParameter(program, pname);
      }
    };

  var stringToUTF8Array = (str, heap, outIdx, maxBytesToWrite) => {
      assert(typeof str === 'string', `stringToUTF8Array expects a string (got ${typeof str})`);
      // Parameter maxBytesToWrite is not optional. Negative values, 0, null,
      // undefined and false each don't write out any bytes.
      if (!(maxBytesToWrite > 0))
        return 0;
  
      var startIdx = outIdx;
      var endIdx = outIdx + maxBytesToWrite - 1; // -1 for string null terminator.
      for (var i = 0; i < str.length; ++i) {
        // For UTF8 byte structure, see http://en.wikipedia.org/wiki/UTF-8#Description
        // and https://www.ietf.org/rfc/rfc2279.txt
        // and https://tools.ietf.org/html/rfc3629
        var u = str.codePointAt(i);
        if (u <= 0x7F) {
          if (outIdx >= endIdx) break;
          heap[outIdx++] = u;
        } else if (u <= 0x7FF) {
          if (outIdx + 1 >= endIdx) break;
          heap[outIdx++] = 0xC0 | (u >> 6);
          heap[outIdx++] = 0x80 | (u & 63);
        } else if (u <= 0xFFFF) {
          if (outIdx + 2 >= endIdx) break;
          heap[outIdx++] = 0xE0 | (u >> 12);
          heap[outIdx++] = 0x80 | ((u >> 6) & 63);
          heap[outIdx++] = 0x80 | (u & 63);
        } else {
          if (outIdx + 3 >= endIdx) break;
          if (u > 0x10FFFF) warnOnce('Invalid Unicode code point ' + ptrToString(u) + ' encountered when serializing a JS string to a UTF-8 string in wasm memory! (Valid unicode code points should be in range 0-0x10FFFF).');
          heap[outIdx++] = 0xF0 | (u >> 18);
          heap[outIdx++] = 0x80 | ((u >> 12) & 63);
          heap[outIdx++] = 0x80 | ((u >> 6) & 63);
          heap[outIdx++] = 0x80 | (u & 63);
          // Gotcha: if codePoint is over 0xFFFF, it is represented as a surrogate pair in UTF-16.
          // We need to manually skip over the second code unit for correct iteration.
          i++;
        }
      }
      // Null-terminate the pointer to the buffer.
      heap[outIdx] = 0;
      return outIdx - startIdx;
    };
  var stringToUTF8 = (str, outPtr, maxBytesToWrite) => {
      assert(typeof maxBytesToWrite == 'number', 'stringToUTF8(str, outPtr, maxBytesToWrite) is missing the third parameter that specifies the length of the output buffer!');
      return stringToUTF8Array(str, HEAPU8, outPtr, maxBytesToWrite);
    };
  
  var _glGetShaderInfoLog = (shader, maxLength, length, infoLog) => {
      var log = GLctx.getShaderInfoLog(GL.shaders[shader]);
      if (log === null) log = '(unknown error)';
      var numBytesWrittenExclNull = (maxLength > 0 && infoLog) ? stringToUTF8(log, infoLog, maxLength) : 0;
      if (length) HEAP32[((length)>>2)] = numBytesWrittenExclNull;
    };

  var _glGetShaderiv = (shader, pname, p) => {
      if (!p) {
        // GLES2 specification does not specify how to behave if p is a null
        // pointer. Since calling this function does not make sense if p == null,
        // issue a GL error to notify user about it.
        GL.recordError(0x501 /* GL_INVALID_VALUE */);
        return;
      }
      if (pname == 0x8B84) { // GL_INFO_LOG_LENGTH
        var log = GLctx.getShaderInfoLog(GL.shaders[shader]);
        if (log === null) log = '(unknown error)';
        // The GLES2 specification says that if the shader has an empty info log,
        // a value of 0 is returned. Otherwise the log has a null char appended.
        // (An empty string is falsey, so we can just check that instead of
        // looking at log.length.)
        var logLength = log ? log.length + 1 : 0;
        HEAP32[((p)>>2)] = logLength;
      } else if (pname == 0x8B88) { // GL_SHADER_SOURCE_LENGTH
        var source = GLctx.getShaderSource(GL.shaders[shader]);
        // source may be a null, or the empty string, both of which are falsey
        // values that we report a 0 length for.
        var sourceLength = source ? source.length + 1 : 0;
        HEAP32[((p)>>2)] = sourceLength;
      } else {
        HEAP32[((p)>>2)] = GLctx.getShaderParameter(GL.shaders[shader], pname);
      }
    };

  var lengthBytesUTF8 = (str) => {
      var len = 0;
      for (var i = 0; i < str.length; ++i) {
        // Gotcha: charCodeAt returns a 16-bit word that is a UTF-16 encoded code
        // unit, not a Unicode code point of the character! So decode
        // UTF16->UTF32->UTF8.
        // See http://unicode.org/faq/utf_bom.html#utf16-3
        var c = str.charCodeAt(i); // possibly a lead surrogate
        if (c <= 0x7F) {
          len++;
        } else if (c <= 0x7FF) {
          len += 2;
        } else if (c >= 0xD800 && c <= 0xDFFF) {
          len += 4; ++i;
        } else {
          len += 3;
        }
      }
      return len;
    };
  
  
  var stringToNewUTF8 = (str) => {
      var size = lengthBytesUTF8(str) + 1;
      var ret = _malloc(size);
      if (ret) stringToUTF8(str, ret, size);
      return ret;
    };
  
  
  var _glGetString = (name_) => {
      var ret = GL.stringCache[name_];
      if (!ret) {
        switch (name_) {
          case 0x1F03 /* GL_EXTENSIONS */:
            ret = stringToNewUTF8(webglGetExtensions().join(' '));
            break;
          case 0x1F00 /* GL_VENDOR */:
          case 0x1F01 /* GL_RENDERER */:
          case 0x9245 /* UNMASKED_VENDOR_WEBGL */:
          case 0x9246 /* UNMASKED_RENDERER_WEBGL */:
            var s = GLctx.getParameter(name_);
            if (!s) {
              GL.recordError(0x500/*GL_INVALID_ENUM*/);
            }
            ret = s ? stringToNewUTF8(s) : 0;
            break;
  
          case 0x1F02 /* GL_VERSION */:
            var webGLVersion = GLctx.getParameter(0x1F02 /*GL_VERSION*/);
            // return GLES version string corresponding to the version of the WebGL context
            var glVersion = `OpenGL ES 2.0 (${webGLVersion})`;
            if (true) glVersion = `OpenGL ES 3.0 (${webGLVersion})`;
            ret = stringToNewUTF8(glVersion);
            break;
          case 0x8B8C /* GL_SHADING_LANGUAGE_VERSION */:
            var glslVersion = GLctx.getParameter(0x8B8C /*GL_SHADING_LANGUAGE_VERSION*/);
            // extract the version number 'N.M' from the string 'WebGL GLSL ES N.M ...'
            var ver_re = /^WebGL GLSL ES ([0-9]\.[0-9][0-9]?)(?:$| .*)/;
            var ver_num = glslVersion.match(ver_re);
            if (ver_num !== null) {
              if (ver_num[1].length == 3) ver_num[1] = ver_num[1] + '0'; // ensure minor version has 2 digits
              glslVersion = `OpenGL ES GLSL ES ${ver_num[1]} (${glslVersion})`;
            }
            ret = stringToNewUTF8(glslVersion);
            break;
          default:
            GL.recordError(0x500/*GL_INVALID_ENUM*/);
            // fall through
        }
        GL.stringCache[name_] = ret;
      }
      return ret;
    };

  /** @suppress {checkTypes} */
  var jstoi_q = (str) => parseInt(str);
  
  /** @noinline */
  var webglGetLeftBracePos = (name) => name.slice(-1) == ']' && name.lastIndexOf('[');
  
  var webglPrepareUniformLocationsBeforeFirstUse = (program) => {
      var uniformLocsById = program.uniformLocsById, // Maps GLuint -> WebGLUniformLocation
        uniformSizeAndIdsByName = program.uniformSizeAndIdsByName, // Maps name -> [uniform array length, GLuint]
        i, j;
  
      // On the first time invocation of glGetUniformLocation on this shader program:
      // initialize cache data structures and discover which uniforms are arrays.
      if (!uniformLocsById) {
        // maps GLint integer locations to WebGLUniformLocations
        program.uniformLocsById = uniformLocsById = {};
        // maps integer locations back to uniform name strings, so that we can lazily fetch uniform array locations
        program.uniformArrayNamesById = {};
  
        var numActiveUniforms = GLctx.getProgramParameter(program, 0x8B86/*GL_ACTIVE_UNIFORMS*/);
        for (i = 0; i < numActiveUniforms; ++i) {
          var u = GLctx.getActiveUniform(program, i);
          var nm = u.name;
          var sz = u.size;
          var lb = webglGetLeftBracePos(nm);
          var arrayName = lb > 0 ? nm.slice(0, lb) : nm;
  
          // Assign a new location.
          var id = program.uniformIdCounter;
          program.uniformIdCounter += sz;
          // Eagerly get the location of the uniformArray[0] base element.
          // The remaining indices >0 will be left for lazy evaluation to
          // improve performance. Those may never be needed to fetch, if the
          // application fills arrays always in full starting from the first
          // element of the array.
          uniformSizeAndIdsByName[arrayName] = [sz, id];
  
          // Store placeholder integers in place that highlight that these
          // >0 index locations are array indices pending population.
          for (j = 0; j < sz; ++j) {
            uniformLocsById[id] = j;
            program.uniformArrayNamesById[id++] = arrayName;
          }
        }
      }
    };
  
  
  
  var _glGetUniformLocation = (program, name) => {
  
      name = UTF8ToString(name);
  
      if (program = GL.programs[program]) {
        webglPrepareUniformLocationsBeforeFirstUse(program);
        var uniformLocsById = program.uniformLocsById; // Maps GLuint -> WebGLUniformLocation
        var arrayIndex = 0;
        var uniformBaseName = name;
  
        // Invariant: when populating integer IDs for uniform locations, we must
        // maintain the precondition that arrays reside in contiguous addresses,
        // i.e. for a 'vec4 colors[10];', colors[4] must be at location
        // colors[0]+4.  However, user might call glGetUniformLocation(program,
        // "colors") for an array, so we cannot discover based on the user input
        // arguments whether the uniform we are dealing with is an array. The only
        // way to discover which uniforms are arrays is to enumerate over all the
        // active uniforms in the program.
        var leftBrace = webglGetLeftBracePos(name);
  
        // If user passed an array accessor "[index]", parse the array index off the accessor.
        if (leftBrace > 0) {
          arrayIndex = jstoi_q(name.slice(leftBrace + 1)) >>> 0; // "index]", coerce parseInt(']') with >>>0 to treat "foo[]" as "foo[0]" and foo[-1] as unsigned out-of-bounds.
          uniformBaseName = name.slice(0, leftBrace);
        }
  
        // Have we cached the location of this uniform before?
        // A pair [array length, GLint of the uniform location]
        var sizeAndId = program.uniformSizeAndIdsByName[uniformBaseName];
  
        // If an uniform with this name exists, and if its index is within the
        // array limits (if it's even an array), query the WebGLlocation, or
        // return an existing cached location.
        if (sizeAndId && arrayIndex < sizeAndId[0]) {
          arrayIndex += sizeAndId[1]; // Add the base location of the uniform to the array index offset.
          if ((uniformLocsById[arrayIndex] = uniformLocsById[arrayIndex] || GLctx.getUniformLocation(program, name))) {
            return arrayIndex;
          }
        }
      }
      else {
        // N.b. we are currently unable to distinguish between GL program IDs that
        // never existed vs GL program IDs that have been deleted, so report
        // GL_INVALID_VALUE in both cases.
        GL.recordError(0x501 /* GL_INVALID_VALUE */);
      }
      return -1;
    };

  var _glLinkProgram = (program) => {
      program = GL.programs[program];
      GLctx.linkProgram(program);
      // Invalidate earlier computed uniform->ID mappings, those have now become stale
      program.uniformLocsById = 0; // Mark as null-like so that glGetUniformLocation() knows to populate this again.
      program.uniformSizeAndIdsByName = {};
  
    };

  var _glPolygonOffset = (x0, x1) => GLctx.polygonOffset(x0, x1);

  var heapObjectForWebGLType = (type) => {
      // Micro-optimization for size: Subtract lowest GL enum number (0x1400/* GL_BYTE */) from type to compare
      // smaller values for the heap, for shorter generated code size.
      // Also the type HEAPU16 is not tested for explicitly, but any unrecognized type will return out HEAPU16.
      // (since most types are HEAPU16)
      type -= 0x1400;
      if (type == 0) return HEAP8;
  
      if (type == 1) return HEAPU8;
  
      if (type == 2) return HEAP16;
  
      if (type == 4) return HEAP32;
  
      if (type == 6) return HEAPF32;
  
      if (type == 5
        || type == 28922
        || type == 28520
        || type == 30779
        || type == 30782
        )
        return HEAPU32;
  
      return HEAPU16;
    };
  
  var toTypedArrayIndex = (pointer, heap) =>
      pointer >>> (31 - Math.clz32(heap.BYTES_PER_ELEMENT));
  
  var _glReadPixels = (x, y, width, height, format, type, pixels) => {
      if (true) {
        if (GLctx.currentPixelPackBufferBinding) {
          GLctx.readPixels(x, y, width, height, format, type, pixels);
          return;
        }
        var heap = heapObjectForWebGLType(type);
        var target = toTypedArrayIndex(pixels, heap);
        GLctx.readPixels(x, y, width, height, format, type, heap, target);
        return;
      }
    };

  var _glScissor = (x0, x1, x2, x3) => GLctx.scissor(x0, x1, x2, x3);

  var _glShaderSource = (shader, count, string, length) => {
      var source = GL.getSource(shader, count, string, length);
  
      GLctx.shaderSource(GL.shaders[shader], source);
    };

  var computeUnpackAlignedImageSize = (width, height, sizePerPixel) => {
      function roundedToNextMultipleOf(x, y) {
        return (x + y - 1) & -y;
      }
      var plainRowSize = (GL.unpackRowLength || width) * sizePerPixel;
      var alignedRowSize = roundedToNextMultipleOf(plainRowSize, GL.unpackAlignment);
      return height * alignedRowSize;
    };
  
  var colorChannelsInGlTextureFormat = (format) => {
      // Micro-optimizations for size: map format to size by subtracting smallest
      // enum value (0x1902) from all values first.  Also omit the most common
      // size value (1) from the list, which is assumed by formats not on the
      // list.
      var colorChannels = {
        // 0x1902 /* GL_DEPTH_COMPONENT */ - 0x1902: 1,
        // 0x1906 /* GL_ALPHA */ - 0x1902: 1,
        5: 3,
        6: 4,
        // 0x1909 /* GL_LUMINANCE */ - 0x1902: 1,
        8: 2,
        29502: 3,
        29504: 4,
        // 0x1903 /* GL_RED */ - 0x1902: 1,
        26917: 2,
        26918: 2,
        // 0x8D94 /* GL_RED_INTEGER */ - 0x1902: 1,
        29846: 3,
        29847: 4
      };
      return colorChannels[format - 0x1902]||1;
    };
  
  
  
  var emscriptenWebGLGetTexPixelData = (type, format, width, height, pixels, internalFormat) => {
      var heap = heapObjectForWebGLType(type);
      var sizePerPixel = colorChannelsInGlTextureFormat(format) * heap.BYTES_PER_ELEMENT;
      var bytes = computeUnpackAlignedImageSize(width, height, sizePerPixel);
      return heap.subarray(toTypedArrayIndex(pixels, heap), toTypedArrayIndex(pixels + bytes, heap));
    };
  
  
  
  var _glTexImage2D = (target, level, internalFormat, width, height, border, format, type, pixels) => {
      if (true) {
        if (GLctx.currentPixelUnpackBufferBinding) {
          GLctx.texImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
          return;
        }
        if (pixels) {
          var heap = heapObjectForWebGLType(type);
          var index = toTypedArrayIndex(pixels, heap);
          GLctx.texImage2D(target, level, internalFormat, width, height, border, format, type, heap, index);
          return;
        }
      }
      var pixelData = pixels ? emscriptenWebGLGetTexPixelData(type, format, width, height, pixels, internalFormat) : null;
      GLctx.texImage2D(target, level, internalFormat, width, height, border, format, type, pixelData);
    };

  var _glTexParameteri = (x0, x1, x2) => GLctx.texParameteri(x0, x1, x2);

  var webglGetUniformLocation = (location) => {
      var p = GLctx.currentProgram;
  
      if (p) {
        var webglLoc = p.uniformLocsById[location];
        // p.uniformLocsById[location] stores either an integer, or a
        // WebGLUniformLocation.
        // If an integer, we have not yet bound the location, so do it now. The
        // integer value specifies the array index we should bind to.
        if (typeof webglLoc == 'number') {
          p.uniformLocsById[location] = webglLoc = GLctx.getUniformLocation(p, p.uniformArrayNamesById[location] + (webglLoc > 0 ? `[${webglLoc}]` : ''));
        }
        // Else an already cached WebGLUniformLocation, return it.
        return webglLoc;
      } else {
        GL.recordError(0x502/*GL_INVALID_OPERATION*/);
      }
    };
  
  var _glUniform1f = (location, v0) => {
      GLctx.uniform1f(webglGetUniformLocation(location), v0);
    };

  
  var _glUniform1i = (location, v0) => {
      GLctx.uniform1i(webglGetUniformLocation(location), v0);
    };

  
  var _glUniform2f = (location, v0, v1) => {
      GLctx.uniform2f(webglGetUniformLocation(location), v0, v1);
    };

  
  var _glUniform4f = (location, v0, v1, v2, v3) => {
      GLctx.uniform4f(webglGetUniformLocation(location), v0, v1, v2, v3);
    };

  
  var _glUniform4i = (location, v0, v1, v2, v3) => {
      GLctx.uniform4i(webglGetUniformLocation(location), v0, v1, v2, v3);
    };

  var _glUseProgram = (program) => {
      program = GL.programs[program];
      GLctx.useProgram(program);
      // Record the currently active program so that we can access the uniform
      // mapping table of that program.
      GLctx.currentProgram = program;
    };

  var _glVertexAttribPointer = (index, size, type, normalized, stride, ptr) => {
      GLctx.vertexAttribPointer(index, size, type, !!normalized, stride, ptr);
    };

  var _glViewport = (x0, x1, x2, x3) => GLctx.viewport(x0, x1, x2, x3);

  var _port_rtw_gl_create = () => {
      const canvas = Module['canvas'];
      if (!canvas) { err('[video] the host gave no OffscreenCanvas'); return 0; }
      rtwGlue.beforeGl();
      return GL.createContext(canvas, {
        majorVersion: 2, minorVersion: 0, alpha: false, depth: true, stencil: false, antialias: false,
        premultipliedAlpha: true, preserveDrawingBuffer: true, powerPreference: 'default',
        failIfMajorPerformanceCaveat: false, enableExtensionsByDefault: true,
      });
    };

  var _port_rtw_gl_ready = () => rtwGlue.glReady();

  var _port_rtw_glue_option = (id, value) => rtwGlue.option(id, value);

  var _port_rtw_glue_pause = (on) => rtwGlue.pause(on);

  var _port_rtw_glue_resize = (width, height, dpr100) => rtwGlue.resize(width, height, dpr100);

  var _port_rtw_glue_start = () => rtwGlue.start();

  var _rtw_build_id = (ptr) => {
      const host = Module['rtw'];
      if (host && host['rtw_build_id']) return host['rtw_build_id'](ptr) | 0;
      HEAPU8.fill(0, ptr, ptr + 32);   // no host: an all-zero id
      return 0;
    };

  var _rtw_export_file = (namePtr, mimePtr, ptr, len) => {
      const host = Module['rtw'];
      return host && host['rtw_export_file'] ? host['rtw_export_file'](namePtr, mimePtr, ptr, len) | 0 : -1;
    };

  
  var _rtw_log = (ptr, len) => {
      const host = Module['rtw'];
      if (host && host['rtw_log']) return host['rtw_log'](ptr, len) | 0;
      out(UTF8ToString(ptr, len));
      return 0;
    };

  var _rtw_pointer_lock = (on) => {
      const host = Module['rtw'];
      return host && host['rtw_pointer_lock'] ? host['rtw_pointer_lock'](on) | 0 : 0;
    };

  var _rtw_rumble = (port, on) => {
      const host = Module['rtw'];
      return host && host['rtw_rumble'] ? host['rtw_rumble'](port, on) | 0 : 0;
    };





      Module['requestAnimationFrame'] = MainLoop.requestAnimationFrame;
      Module['pauseMainLoop'] = MainLoop.pause;
      Module['resumeMainLoop'] = MainLoop.resume;
      MainLoop.init();;
// End JS library code

// include: postlibrary.js
// This file is included after the automatically-generated JS library code
// but before the wasm module is created.

{

  // Begin ATMODULES hooks
  if (Module['noExitRuntime']) noExitRuntime = Module['noExitRuntime'];
if (Module['print']) out = Module['print'];
if (Module['printErr']) err = Module['printErr'];
if (Module['wasmBinary']) wasmBinary = Module['wasmBinary'];

Module['FS_createDataFile'] = FS.createDataFile;
Module['FS_createPreloadedFile'] = FS.createPreloadedFile;

  // End ATMODULES hooks

  checkIncomingModuleAPI();

  if (Module['arguments']) arguments_ = Module['arguments'];
  if (Module['thisProgram']) thisProgram = Module['thisProgram'];

  // Assertions on removed incoming Module JS APIs.
  assert(typeof Module['memoryInitializerPrefixURL'] == 'undefined', 'Module.memoryInitializerPrefixURL option was removed, use Module.locateFile instead');
  assert(typeof Module['pthreadMainPrefixURL'] == 'undefined', 'Module.pthreadMainPrefixURL option was removed, use Module.locateFile instead');
  assert(typeof Module['cdInitializerPrefixURL'] == 'undefined', 'Module.cdInitializerPrefixURL option was removed, use Module.locateFile instead');
  assert(typeof Module['filePackagePrefixURL'] == 'undefined', 'Module.filePackagePrefixURL option was removed, use Module.locateFile instead');
  assert(typeof Module['read'] == 'undefined', 'Module.read option was removed');
  assert(typeof Module['readAsync'] == 'undefined', 'Module.readAsync option was removed (modify readAsync in JS)');
  assert(typeof Module['readBinary'] == 'undefined', 'Module.readBinary option was removed (modify readBinary in JS)');
  assert(typeof Module['setWindowTitle'] == 'undefined', 'Module.setWindowTitle option was removed (modify emscripten_set_window_title in JS)');
  assert(typeof Module['TOTAL_MEMORY'] == 'undefined', 'Module.TOTAL_MEMORY has been renamed Module.INITIAL_MEMORY');
  assert(typeof Module['ENVIRONMENT'] == 'undefined', 'Module.ENVIRONMENT has been deprecated. To force the environment, use the ENVIRONMENT compile-time option (for example, -sENVIRONMENT=web or -sENVIRONMENT=node)');
  assert(typeof Module['STACK_SIZE'] == 'undefined', 'STACK_SIZE can no longer be set at runtime.  Use -sSTACK_SIZE at link time')
  // If memory is defined in wasm, the user can't provide it, or set INITIAL_MEMORY
  assert(typeof Module['wasmMemory'] == 'undefined', 'Use of `wasmMemory` detected.  Use -sIMPORTED_MEMORY to define wasmMemory externally');
  assert(typeof Module['INITIAL_MEMORY'] == 'undefined', 'Detected runtime INITIAL_MEMORY setting.  Use -sIMPORTED_MEMORY to define wasmMemory dynamically');

  if (Module['preInit']) {
    if (typeof Module['preInit'] == 'function') Module['preInit'] = [Module['preInit']];
    while (Module['preInit'].length > 0) {
      Module['preInit'].shift()();
    }
  }
  consumedModuleProp('preInit');
}

// Begin runtime exports
  Module['wasmMemory'] = wasmMemory;
  Module['stringToNewUTF8'] = stringToNewUTF8;
  var missingLibrarySymbols = [
  'writeI53ToI64Clamped',
  'writeI53ToI64Signaling',
  'writeI53ToU64Clamped',
  'writeI53ToU64Signaling',
  'convertI32PairToI53',
  'convertI32PairToI53Checked',
  'convertU32PairToI53',
  'stackAlloc',
  'getTempRet0',
  'setTempRet0',
  'zeroMemory',
  'withStackSave',
  'strError',
  'inetPton4',
  'inetNtop4',
  'inetPton6',
  'inetNtop6',
  'readSockaddr',
  'writeSockaddr',
  'runMainThreadEmAsm',
  'getExecutableName',
  'autoResumeAudioContext',
  'getDynCaller',
  'asyncLoad',
  'asmjsMangle',
  'mmapAlloc',
  'HandleAllocator',
  'getNativeTypeSize',
  'getUniqueRunDependency',
  'addRunDependency',
  'removeRunDependency',
  'addOnInit',
  'addOnPostCtor',
  'addOnPreMain',
  'addOnExit',
  'STACK_SIZE',
  'STACK_ALIGN',
  'POINTER_SIZE',
  'ASSERTIONS',
  'ccall',
  'cwrap',
  'convertJsFunctionToWasm',
  'getEmptyTableSlot',
  'updateTableMap',
  'getFunctionAddress',
  'addFunction',
  'removeFunction',
  'intArrayFromString',
  'intArrayToString',
  'AsciiToString',
  'stringToAscii',
  'UTF16ToString',
  'stringToUTF16',
  'lengthBytesUTF16',
  'UTF32ToString',
  'stringToUTF32',
  'lengthBytesUTF32',
  'stringToUTF8OnStack',
  'writeArrayToMemory',
  'registerKeyEventCallback',
  'maybeCStringToJsString',
  'findEventTarget',
  'getBoundingClientRect',
  'fillMouseEventData',
  'registerMouseEventCallback',
  'registerWheelEventCallback',
  'registerUiEventCallback',
  'registerFocusEventCallback',
  'fillDeviceOrientationEventData',
  'registerDeviceOrientationEventCallback',
  'fillDeviceMotionEventData',
  'registerDeviceMotionEventCallback',
  'screenOrientation',
  'fillOrientationChangeEventData',
  'registerOrientationChangeEventCallback',
  'fillFullscreenChangeEventData',
  'registerFullscreenChangeEventCallback',
  'JSEvents_requestFullscreen',
  'JSEvents_resizeCanvasForFullscreen',
  'registerRestoreOldStyle',
  'hideEverythingExceptGivenElement',
  'restoreHiddenElements',
  'setLetterbox',
  'softFullscreenResizeWebGLRenderTarget',
  'doRequestFullscreen',
  'fillPointerlockChangeEventData',
  'registerPointerlockChangeEventCallback',
  'registerPointerlockErrorEventCallback',
  'requestPointerLock',
  'fillVisibilityChangeEventData',
  'registerVisibilityChangeEventCallback',
  'registerTouchEventCallback',
  'fillGamepadEventData',
  'registerGamepadEventCallback',
  'registerBeforeUnloadEventCallback',
  'fillBatteryEventData',
  'registerBatteryEventCallback',
  'setCanvasElementSize',
  'getCanvasElementSize',
  'jsStackTrace',
  'getCallstack',
  'convertPCtoSourceLocation',
  'getEnvStrings',
  'checkWasiClock',
  'wasiRightsToMuslOFlags',
  'wasiOFlagsToMuslOFlags',
  'initRandomFill',
  'randomFill',
  'safeSetTimeout',
  'setImmediateWrapped',
  'safeRequestAnimationFrame',
  'clearImmediateWrapped',
  'registerPostMainLoop',
  'registerPreMainLoop',
  'getPromise',
  'makePromise',
  'idsToPromises',
  'makePromiseCallback',
  'ExceptionInfo',
  'findMatchingCatch',
  'Browser_asyncPrepareDataCounter',
  'isLeapYear',
  'ydayFromDate',
  'arraySum',
  'addDays',
  'getSocketFromFD',
  'getSocketAddress',
  'FS_createPreloadedFile',
  'FS_preloadFile',
  'FS_modeStringToFlags',
  'FS_getMode',
  'FS_stdin_getChar',
  'FS_mkdirTree',
  '_setNetworkCallback',
  'emscriptenWebGLGetUniform',
  'emscriptenWebGLGetVertexAttrib',
  '__glGetActiveAttribOrUniform',
  'writeGLArray',
  'registerWebGlEventCallback',
  'emscriptenWebGLGetIndexed',
  'ALLOC_NORMAL',
  'ALLOC_STACK',
  'allocate',
  'writeStringToMemory',
  'writeAsciiToMemory',
  'demangle',
  'stackTrace',
];
missingLibrarySymbols.forEach(missingLibrarySymbol)

  var unexportedSymbols = [
  'run',
  'out',
  'err',
  'callMain',
  'abort',
  'wasmExports',
  'HEAPF32',
  'HEAPF64',
  'HEAP8',
  'HEAP16',
  'HEAPU16',
  'HEAP64',
  'HEAPU64',
  'writeI53ToI64',
  'readI53FromI64',
  'readI53FromU64',
  'INT53_MAX',
  'INT53_MIN',
  'bigintToI53Checked',
  'stackSave',
  'stackRestore',
  'ptrToString',
  'exitJS',
  'getHeapMax',
  'growMemory',
  'ENV',
  'ERRNO_CODES',
  'DNS',
  'Protocols',
  'Sockets',
  'timers',
  'warnOnce',
  'readEmAsmArgsArray',
  'readEmAsmArgs',
  'runEmAsmFunction',
  'jstoi_q',
  'dynCallLegacy',
  'dynCall',
  'handleException',
  'keepRuntimeAlive',
  'runtimeKeepalivePush',
  'runtimeKeepalivePop',
  'callUserCallback',
  'maybeExit',
  'alignMemory',
  'wasmTable',
  'noExitRuntime',
  'addOnPreRun',
  'addOnPostRun',
  'freeTableIndexes',
  'functionsInTableMap',
  'setValue',
  'getValue',
  'PATH',
  'PATH_FS',
  'UTF8Decoder',
  'UTF8ArrayToString',
  'UTF8ToString',
  'stringToUTF8Array',
  'stringToUTF8',
  'lengthBytesUTF8',
  'UTF16Decoder',
  'JSEvents',
  'specialHTMLTargets',
  'findCanvasEventTarget',
  'currentFullscreenStrategy',
  'restoreOldWindowedStyle',
  'UNWIND_CACHE',
  'ExitStatus',
  'flush_NO_FILESYSTEM',
  'emSetImmediate',
  'emClearImmediate_deps',
  'emClearImmediate',
  'promiseMap',
  'uncaughtExceptionCount',
  'exceptionLast',
  'exceptionCaught',
  'Browser',
  'requestFullscreen',
  'requestFullScreen',
  'setCanvasSize',
  'getUserMedia',
  'createContext',
  'getPreloadedImageData__data',
  'wget',
  'MONTH_DAYS_REGULAR',
  'MONTH_DAYS_LEAP',
  'MONTH_DAYS_REGULAR_CUMULATIVE',
  'MONTH_DAYS_LEAP_CUMULATIVE',
  'SYSCALLS',
  'preloadPlugins',
  'FS_stdin_getChar_buffer',
  'FS_unlink',
  'FS_createPath',
  'FS_createDevice',
  'FS_readFile',
  'FS',
  'FS_root',
  'FS_mounts',
  'FS_devices',
  'FS_streams',
  'FS_nextInode',
  'FS_nameTable',
  'FS_currentPath',
  'FS_initialized',
  'FS_ignorePermissions',
  'FS_filesystems',
  'FS_syncFSRequests',
  'FS_readFiles',
  'FS_lookupPath',
  'FS_getPath',
  'FS_hashName',
  'FS_hashAddNode',
  'FS_hashRemoveNode',
  'FS_lookupNode',
  'FS_createNode',
  'FS_destroyNode',
  'FS_isRoot',
  'FS_isMountpoint',
  'FS_isFile',
  'FS_isDir',
  'FS_isLink',
  'FS_isChrdev',
  'FS_isBlkdev',
  'FS_isFIFO',
  'FS_isSocket',
  'FS_flagsToPermissionString',
  'FS_nodePermissions',
  'FS_mayLookup',
  'FS_mayCreate',
  'FS_mayDelete',
  'FS_mayOpen',
  'FS_checkOpExists',
  'FS_nextfd',
  'FS_getStreamChecked',
  'FS_getStream',
  'FS_createStream',
  'FS_closeStream',
  'FS_dupStream',
  'FS_doSetAttr',
  'FS_chrdev_stream_ops',
  'FS_major',
  'FS_minor',
  'FS_makedev',
  'FS_registerDevice',
  'FS_getDevice',
  'FS_getMounts',
  'FS_syncfs',
  'FS_mount',
  'FS_unmount',
  'FS_lookup',
  'FS_mknod',
  'FS_statfs',
  'FS_statfsStream',
  'FS_statfsNode',
  'FS_create',
  'FS_mkdir',
  'FS_mkdev',
  'FS_symlink',
  'FS_rename',
  'FS_rmdir',
  'FS_readdir',
  'FS_readlink',
  'FS_stat',
  'FS_fstat',
  'FS_lstat',
  'FS_doChmod',
  'FS_chmod',
  'FS_lchmod',
  'FS_fchmod',
  'FS_doChown',
  'FS_chown',
  'FS_lchown',
  'FS_fchown',
  'FS_doTruncate',
  'FS_truncate',
  'FS_ftruncate',
  'FS_utime',
  'FS_open',
  'FS_close',
  'FS_isClosed',
  'FS_llseek',
  'FS_read',
  'FS_write',
  'FS_mmap',
  'FS_msync',
  'FS_ioctl',
  'FS_writeFile',
  'FS_cwd',
  'FS_chdir',
  'FS_createDefaultDirectories',
  'FS_createDefaultDevices',
  'FS_createSpecialDirectories',
  'FS_createStandardStreams',
  'FS_staticInit',
  'FS_init',
  'FS_quit',
  'FS_findObject',
  'FS_analyzePath',
  'FS_createFile',
  'FS_createDataFile',
  'FS_forceLoadFile',
  'FS_createLazyFile',
  'FS_absolutePath',
  'FS_createFolder',
  'FS_createLink',
  'FS_joinPath',
  'FS_mmapAlloc',
  'FS_standardizePath',
  'MEMFS',
  'TTY',
  'PIPEFS',
  'SOCKFS',
  'tempFixedLengthArray',
  'miniTempWebGLFloatBuffers',
  'miniTempWebGLIntBuffers',
  'heapObjectForWebGLType',
  'toTypedArrayIndex',
  'webgl_enable_WEBGL_multi_draw',
  'webgl_enable_EXT_polygon_offset_clamp',
  'webgl_enable_EXT_clip_control',
  'webgl_enable_WEBGL_polygon_mode',
  'GL',
  'emscriptenWebGLGet',
  'computeUnpackAlignedImageSize',
  'colorChannelsInGlTextureFormat',
  'emscriptenWebGLGetTexPixelData',
  'webglGetUniformLocation',
  'webglPrepareUniformLocationsBeforeFirstUse',
  'webglGetLeftBracePos',
  'AL',
  'GLUT',
  'EGL',
  'GLEW',
  'IDBStore',
  'runAndAbortIfError',
  'Asyncify',
  'Fibers',
  'SDL',
  'SDL_gfx',
  'webgl_enable_WEBGL_draw_instanced_base_vertex_base_instance',
  'webgl_enable_WEBGL_multi_draw_instanced_base_vertex_base_instance',
  'allocateUTF8',
  'allocateUTF8OnStack',
  'print',
  'printErr',
  'jstoi_s',
];
unexportedSymbols.forEach(unexportedRuntimeSymbol);

  // End runtime exports
  // Begin JS library exports
  // End JS library exports

// end include: postlibrary.js

function checkIncomingModuleAPI() {
  ignoredModuleProp('fetchSettings');
}
var ASM_CONSTS = {
  268713968: () => { return typeof location !== 'undefined' ? 1 : 0; },  
 268714020: ($0, $1) => { if (Module['recInput']) Module['recInput']($0, $1 >>> 0); },  
 268714082: () => { if (Module['netAfterTick']) Module['netAfterTick'](); },  
 268714140: ($0, $1, $2, $3, $4, $5, $6, $7, $8, $9) => { if (Module['recCheck']) Module['recCheck']($0, $1 >>> 0, $2 >>> 0, $3 >>> 0, $4, $5, $6, $7, $8, $9); },  
 268714246: ($0, $1) => { if (Module['recG']) Module['recG']($0, $1 >>> 0); },  
 268714300: ($0) => { if (Module['recEnd']) Module['recEnd']($0); },  
 268714348: ($0, $1, $2) => { if (typeof process !== 'undefined' && process.env && process.env.AUDTEST_WAV) { const fs = require('fs'); fs.writeFileSync(process.env.AUDTEST_WAV, Buffer.concat([Buffer.from(HEAPU8.subarray($0, $0 + 44)), Buffer.from(HEAPU8.subarray($1, $1 + $2))])); console.log('[audtest] wrote ' + process.env.AUDTEST_WAV); } }
};
function __port_flag_js(name) { var n = UTF8ToString(name), v = null; if (typeof location !== 'undefined') { var m = new RegExp('[?&]' + n + '(=([^&]*))?(&|$)').exec(location.search); if (m) v = m[2] === undefined ? '1' : m[2]; } else if (typeof process !== 'undefined' && process.env) { var e = process.env['PORT_' + n.toUpperCase()]; if (e !== undefined) v = e; } return v === null ? 0 : (parseInt(v, 0) || (v === '' ? 1 : 0)); }
function __port_flag_hex_js(name) { var n = UTF8ToString(name), v = null; if (typeof location !== 'undefined') { var m = new RegExp('[?&]' + n + '(=([^&]*))?(&|$)').exec(location.search); if (m) v = m[2] === undefined ? '1' : m[2]; } else if (typeof process !== 'undefined' && process.env) { var e = process.env['PORT_' + n.toUpperCase()]; if (e !== undefined) v = e; } return v === null ? 0 : (parseInt(v, 16) || (v === '' ? 1 : 0)); }
function __port_js_stack(skip,n) { var l = new Error().stack.split('\n').slice(1 + skip, 1 + skip + n); out(l.map(function (x) { x = x.trim(); var i = x.indexOf(' ('); return '    ' + (i > 0 ? x.slice(0, i) : x); }).join('\n')); }
function __port_padf_char(ch,i) { var v = null, k = ch ? 'padf' + ch : 'padf'; if (typeof location !== 'undefined') { var m = new RegExp('[?&]' + k + '=([^&]*)').exec(location.search); if (m) v = decodeURIComponent(m[1]); } else if (typeof process !== 'undefined' && process.env && process.env['PORT_' + k.toUpperCase()] !== undefined) v = process.env['PORT_' + k.toUpperCase()]; return v === null || i >= v.length ? 0 : v.charCodeAt(i); }
function __port_padrec_push(f,b,x,y) { var g = typeof window !== 'undefined' ? window : globalThis; (g.__padrec = g.__padrec || []).push(f + ':' + b.toString(16).toUpperCase() + ':' + x + ':' + y); }
function __port_net_det_js() { if (typeof location !== 'undefined') return /[?&]netdet(=1)?(&|$)/.test(location.search) ? 1 : 0; if (typeof process !== 'undefined' && process.env && process.env.PORT_NETDET) return 1; return 0; }
function __photo_move_field(k) { if (typeof location === 'undefined') return 0; var v = new URLSearchParams(location.search).get('photomove'); return v ? (parseFloat(v.split(':')[k]) || 0) : 0; }
function __port_p205_goto_char(i) { var v = null; if (typeof location !== 'undefined') { var m = /[?&]p205goto=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); } else if (typeof process !== 'undefined' && process.env && process.env.PORT_P205GOTO !== undefined) v = process.env.PORT_P205GOTO; return v === null || i >= v.length ? 0 : v.charCodeAt(i); }
function __port_p240_steer() { var v = null; if (typeof location !== 'undefined') { var m = /[?&]p240steer=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); } else if (typeof process !== 'undefined' && process.env && process.env.PORT_P240STEER !== undefined) v = process.env.PORT_P240STEER; if (v === null) return -1; var a = v.split(':'); return ((parseInt(a[0], 10) || 0) * 4 + ((parseInt(a[1] || '1', 10) || 1) & 3)) * 128 + Math.min(127, parseInt(a[2] || '50', 10)); }
function __port_p240_start() { var v = null; if (typeof location !== 'undefined') { var m = /[?&]p240steer=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); } else if (typeof process !== 'undefined' && process.env && process.env.PORT_P240STEER !== undefined) v = process.env.PORT_P240STEER; if (v === null) return 0; return parseInt(v.split(':')[3] || '0', 10) || 0; }
function __port_p352_hang_char(i) { var v = null; if (typeof location !== 'undefined') { var m = /[?&]p352hang=([^&]*)/.exec(location.search); if (m) v = decodeURIComponent(m[1]); } return v === null || i >= v.length ? 0 : v.charCodeAt(i); }
function __port_web_audio_open(rate,ring,rdp,wrp,mask,urp) { try { var G = globalThis, C = G.AudioContext || G.webkitAudioContext; if (!C) return 0; var ctx; try { ctx = new C({ sampleRate: rate }); } catch (e) { ctx = new C(); } var node = ctx.createScriptProcessor(2048, 0, 2); var src = ctx.sampleRate === rate ? 1 : rate / ctx.sampleRate; var pos = 0, started = 0; node.onaudioprocess = function (e) { var L = e.outputBuffer.getChannelData(0), R = e.outputBuffer.getChannelData(1); var r = HEAPU32[rdp >> 2], w = HEAPU32[wrp >> 2], base = ring >> 1; for (var i = 0; i < L.length; i++) { if (r === w) { L[i] = R[i] = 0; if (started) HEAPU32[urp >> 2]++; continue; } started = 1; L[i] = HEAP16[base + 2 * r] / 32768; R[i] = HEAP16[base + 2 * r + 1] / 32768; pos += src; while (pos >= 1 && r !== w) { pos -= 1; r = (r + 1) & mask; } } HEAPU32[rdp >> 2] = r; }; var gain = ctx.createGain(); gain.gain.value = typeof G.portVolume === 'number' ? G.portVolume : 1; node.connect(gain); gain.connect(ctx.destination); globalThis.portAudio = { ctx: ctx, node: node, gain: gain }; if (ctx.state !== 'running') ctx.resume().catch(function () {}); if (typeof G.portAudioReady === 'function') G.portAudioReady(ctx); return ctx.sampleRate | 0; } catch (e) { globalThis.portAudioErr = String(e && e.stack || e); return -1; } }

// Imports from the Wasm binary.
var _main = Module['_main'] = makeInvalidEarlyAccess('_main');
var _free = Module['_free'] = makeInvalidEarlyAccess('_free');
var _port_net_kick = Module['_port_net_kick'] = makeInvalidEarlyAccess('_port_net_kick');
var _port_net_ready = Module['_port_net_ready'] = makeInvalidEarlyAccess('_port_net_ready');
var _port_dump_threads = Module['_port_dump_threads'] = makeInvalidEarlyAccess('_port_dump_threads');
var _port_dump_stubs = Module['_port_dump_stubs'] = makeInvalidEarlyAccess('_port_dump_stubs');
var _malloc = Module['_malloc'] = makeInvalidEarlyAccess('_malloc');
var _fflush = makeInvalidEarlyAccess('_fflush');
var _port_set_rom = Module['_port_set_rom'] = makeInvalidEarlyAccess('_port_set_rom');
var _port_set_paused = Module['_port_set_paused'] = makeInvalidEarlyAccess('_port_set_paused');
var _port_set_option = Module['_port_set_option'] = makeInvalidEarlyAccess('_port_set_option');
var _port_set_gmenu_row = Module['_port_set_gmenu_row'] = makeInvalidEarlyAccess('_port_set_gmenu_row');
var _port_gmenu_take_request = Module['_port_gmenu_take_request'] = makeInvalidEarlyAccess('_port_gmenu_take_request');
var _port_skip_progress = Module['_port_skip_progress'] = makeInvalidEarlyAccess('_port_skip_progress');
var _port_pad_state = Module['_port_pad_state'] = makeInvalidEarlyAccess('_port_pad_state');
var _port_cam_state = Module['_port_cam_state'] = makeInvalidEarlyAccess('_port_cam_state');
var _port_eeprom_ptr = Module['_port_eeprom_ptr'] = makeInvalidEarlyAccess('_port_eeprom_ptr');
var _port_eeprom_size = Module['_port_eeprom_size'] = makeInvalidEarlyAccess('_port_eeprom_size');
var _port_eep_test = Module['_port_eep_test'] = makeInvalidEarlyAccess('_port_eep_test');
var _port_net_force_det = Module['_port_net_force_det'] = makeInvalidEarlyAccess('_port_net_force_det');
var _port_net_session = Module['_port_net_session'] = makeInvalidEarlyAccess('_port_net_session');
var _port_net_addr = Module['_port_net_addr'] = makeInvalidEarlyAccess('_port_net_addr');
var _port_net_frame = Module['_port_net_frame'] = makeInvalidEarlyAccess('_port_net_frame');
var _port_net_script_input = Module['_port_net_script_input'] = makeInvalidEarlyAccess('_port_net_script_input');
var _port_net_drop = Module['_port_net_drop'] = makeInvalidEarlyAccess('_port_net_drop');
var _port_net_slow = Module['_port_net_slow'] = makeInvalidEarlyAccess('_port_net_slow');
var _port_rec_checkpoint_ms = Module['_port_rec_checkpoint_ms'] = makeInvalidEarlyAccess('_port_rec_checkpoint_ms');
var _port_rec_session = Module['_port_rec_session'] = makeInvalidEarlyAccess('_port_rec_session');
var _port_rec_checkpoint_now = Module['_port_rec_checkpoint_now'] = makeInvalidEarlyAccess('_port_rec_checkpoint_now');
var _port_net_exclude = Module['_port_net_exclude'] = makeInvalidEarlyAccess('_port_net_exclude');
var _port_net_region = Module['_port_net_region'] = makeInvalidEarlyAccess('_port_net_region');
var _port_net_page_hashes = Module['_port_net_page_hashes'] = makeInvalidEarlyAccess('_port_net_page_hashes');
var _port_net_page_info = Module['_port_net_page_info'] = makeInvalidEarlyAccess('_port_net_page_info');
var _port_photo_input = Module['_port_photo_input'] = makeInvalidEarlyAccess('_port_photo_input');
var _port_photo_request = Module['_port_photo_request'] = makeInvalidEarlyAccess('_port_photo_request');
var _port_photo_status = Module['_port_photo_status'] = makeInvalidEarlyAccess('_port_photo_status');
var _port_photo_render = Module['_port_photo_render'] = makeInvalidEarlyAccess('_port_photo_render');
var _port_photo_info = Module['_port_photo_info'] = makeInvalidEarlyAccess('_port_photo_info');
var _port_photo_look_set = Module['_port_photo_look_set'] = makeInvalidEarlyAccess('_port_photo_look_set');
var _port_photo_look_info = Module['_port_photo_look_info'] = makeInvalidEarlyAccess('_port_photo_look_info');
var _port_sfx_info = Module['_port_sfx_info'] = makeInvalidEarlyAccess('_port_sfx_info');
var _port_sfx_pcm = Module['_port_sfx_pcm'] = makeInvalidEarlyAccess('_port_sfx_pcm');
var _port_sfx_decode = Module['_port_sfx_decode'] = makeInvalidEarlyAccess('_port_sfx_decode');
var _port_rtw_raw_state = Module['_port_rtw_raw_state'] = makeInvalidEarlyAccess('_port_rtw_raw_state');
var _port_rtw_lock_game_options = Module['_port_rtw_lock_game_options'] = makeInvalidEarlyAccess('_port_rtw_lock_game_options');
var _port_rtw_log = Module['_port_rtw_log'] = makeInvalidEarlyAccess('_port_rtw_log');
var _port_rtw_export_file = Module['_port_rtw_export_file'] = makeInvalidEarlyAccess('_port_rtw_export_file');
var _port_rtw_build_id = Module['_port_rtw_build_id'] = makeInvalidEarlyAccess('_port_rtw_build_id');
var _port_rtw_set_pointer_lock = Module['_port_rtw_set_pointer_lock'] = makeInvalidEarlyAccess('_port_rtw_set_pointer_lock');
var _rtw_rom_buffer = Module['_rtw_rom_buffer'] = makeInvalidEarlyAccess('_rtw_rom_buffer');
var _port_rtw_rom_ptr = Module['_port_rtw_rom_ptr'] = makeInvalidEarlyAccess('_port_rtw_rom_ptr');
var _port_rtw_rom_size = Module['_port_rtw_rom_size'] = makeInvalidEarlyAccess('_port_rtw_rom_size');
var _rtw_save_ptr = Module['_rtw_save_ptr'] = makeInvalidEarlyAccess('_rtw_save_ptr');
var _rtw_save_size = Module['_rtw_save_size'] = makeInvalidEarlyAccess('_rtw_save_size');
var _rtw_save_generation = Module['_rtw_save_generation'] = makeInvalidEarlyAccess('_rtw_save_generation');
var _rtw_save_load = Module['_rtw_save_load'] = makeInvalidEarlyAccess('_rtw_save_load');
var _rtw_start = Module['_rtw_start'] = makeInvalidEarlyAccess('_rtw_start');
var _rtw_pause = Module['_rtw_pause'] = makeInvalidEarlyAccess('_rtw_pause');
var _rtw_input = Module['_rtw_input'] = makeInvalidEarlyAccess('_rtw_input');
var _rtw_mouse = Module['_rtw_mouse'] = makeInvalidEarlyAccess('_rtw_mouse');
var _rtw_resize = Module['_rtw_resize'] = makeInvalidEarlyAccess('_rtw_resize');
var _rtw_audio_rate = Module['_rtw_audio_rate'] = makeInvalidEarlyAccess('_rtw_audio_rate');
var _rtw_audio_drain = Module['_rtw_audio_drain'] = makeInvalidEarlyAccess('_rtw_audio_drain');
var _rtw_audio_buffer = Module['_rtw_audio_buffer'] = makeInvalidEarlyAccess('_rtw_audio_buffer');
var _rtw_option = Module['_rtw_option'] = makeInvalidEarlyAccess('_rtw_option');
var _port_gfx_hires_2d = Module['_port_gfx_hires_2d'] = makeInvalidEarlyAccess('_port_gfx_hires_2d');
var _port_gfx_smooth_font = Module['_port_gfx_smooth_font'] = makeInvalidEarlyAccess('_port_gfx_smooth_font');
var _port_gfx_widescreen = Module['_port_gfx_widescreen'] = makeInvalidEarlyAccess('_port_gfx_widescreen');
var _port_gfx_ownview = Module['_port_gfx_ownview'] = makeInvalidEarlyAccess('_port_gfx_ownview');
var _port_gfx_ownview_state = Module['_port_gfx_ownview_state'] = makeInvalidEarlyAccess('_port_gfx_ownview_state');
var _port_gfx_resize = Module['_port_gfx_resize'] = makeInvalidEarlyAccess('_port_gfx_resize');
var _port_font_info = Module['_port_font_info'] = makeInvalidEarlyAccess('_port_font_info');
var _port_font_glyph = Module['_port_font_glyph'] = makeInvalidEarlyAccess('_port_font_glyph');
var _port_gfx_hfr = Module['_port_gfx_hfr'] = makeInvalidEarlyAccess('_port_gfx_hfr');
var _port_gfx_hfr_vsync = Module['_port_gfx_hfr_vsync'] = makeInvalidEarlyAccess('_port_gfx_hfr_vsync');
var _port_gfx_hfr_frame = Module['_port_gfx_hfr_frame'] = makeInvalidEarlyAccess('_port_gfx_hfr_frame');
var _port_gfx_hfr_test = Module['_port_gfx_hfr_test'] = makeInvalidEarlyAccess('_port_gfx_hfr_test');
var _emscripten_stack_get_current = makeInvalidEarlyAccess('_emscripten_stack_get_current');
var _port_rtw_audio_drained = Module['_port_rtw_audio_drained'] = makeInvalidEarlyAccess('_port_rtw_audio_drained');
var _strerror = makeInvalidEarlyAccess('_strerror');
var _emscripten_stack_set_limits = makeInvalidEarlyAccess('_emscripten_stack_set_limits');
var __emscripten_stack_restore = makeInvalidEarlyAccess('__emscripten_stack_restore');
var __emscripten_stack_alloc = makeInvalidEarlyAccess('__emscripten_stack_alloc');
var dynCall_v = makeInvalidEarlyAccess('dynCall_v');
var dynCall_vii = makeInvalidEarlyAccess('dynCall_vii');
var dynCall_i = makeInvalidEarlyAccess('dynCall_i');
var dynCall_viii = makeInvalidEarlyAccess('dynCall_viii');
var dynCall_vi = makeInvalidEarlyAccess('dynCall_vi');
var dynCall_ii = makeInvalidEarlyAccess('dynCall_ii');
var dynCall_vif = makeInvalidEarlyAccess('dynCall_vif');
var dynCall_iii = makeInvalidEarlyAccess('dynCall_iii');
var dynCall_viiii = makeInvalidEarlyAccess('dynCall_viiii');
var dynCall_if = makeInvalidEarlyAccess('dynCall_if');
var dynCall_iiii = makeInvalidEarlyAccess('dynCall_iiii');
var dynCall_iiiii = makeInvalidEarlyAccess('dynCall_iiiii');
var dynCall_viiiii = makeInvalidEarlyAccess('dynCall_viiiii');
var dynCall_iiffffi = makeInvalidEarlyAccess('dynCall_iiffffi');
var dynCall_iifffi = makeInvalidEarlyAccess('dynCall_iifffi');
var dynCall_iiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiii');
var dynCall_iiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiii');
var dynCall_iiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiii');
var dynCall_ff = makeInvalidEarlyAccess('dynCall_ff');
var dynCall_fff = makeInvalidEarlyAccess('dynCall_fff');
var dynCall_ffff = makeInvalidEarlyAccess('dynCall_ffff');
var dynCall_iifffffffff = makeInvalidEarlyAccess('dynCall_iifffffffff');
var dynCall_iiiiii = makeInvalidEarlyAccess('dynCall_iiiiii');
var dynCall_viiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiii');
var dynCall_iiifiifiiifiiii = makeInvalidEarlyAccess('dynCall_iiifiifiiifiiii');
var dynCall_vffffffi = makeInvalidEarlyAccess('dynCall_vffffffi');
var dynCall_vffii = makeInvalidEarlyAccess('dynCall_vffii');
var dynCall_fi = makeInvalidEarlyAccess('dynCall_fi');
var dynCall_vifffiiiiiiii = makeInvalidEarlyAccess('dynCall_vifffiiiiiiii');
var dynCall_iiifii = makeInvalidEarlyAccess('dynCall_iiifii');
var dynCall_vifii = makeInvalidEarlyAccess('dynCall_vifii');
var dynCall_iffiiiiiiiii = makeInvalidEarlyAccess('dynCall_iffiiiiiiiii');
var dynCall_vfiiiiiiii = makeInvalidEarlyAccess('dynCall_vfiiiiiiii');
var dynCall_viiiiii = makeInvalidEarlyAccess('dynCall_viiiiii');
var dynCall_viiiifiiiiii = makeInvalidEarlyAccess('dynCall_viiiifiiiiii');
var dynCall_viiiifi = makeInvalidEarlyAccess('dynCall_viiiifi');
var dynCall_viiiifiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiifiiiiiiii');
var dynCall_viifiii = makeInvalidEarlyAccess('dynCall_viifiii');
var dynCall_iiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiii');
var dynCall_iiiiifffffiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiifffffiiiiiii');
var dynCall_vifffffi = makeInvalidEarlyAccess('dynCall_vifffffi');
var dynCall_iiiiifffffiiiii = makeInvalidEarlyAccess('dynCall_iiiiifffffiiiii');
var dynCall_iiiifffffi = makeInvalidEarlyAccess('dynCall_iiiifffffi');
var dynCall_iiiiiifffffiiiii = makeInvalidEarlyAccess('dynCall_iiiiiifffffiiiii');
var dynCall_iiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiiii');
var dynCall_iiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiii');
var dynCall_iiiiiiiiffiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiffiiiiiiii');
var dynCall_iiiffiii = makeInvalidEarlyAccess('dynCall_iiiffiii');
var dynCall_iiiiiiiiffiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiffiiiiii');
var dynCall_viiiiff = makeInvalidEarlyAccess('dynCall_viiiiff');
var dynCall_viiiff = makeInvalidEarlyAccess('dynCall_viiiff');
var dynCall_iiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiii');
var dynCall_vifffffffffff = makeInvalidEarlyAccess('dynCall_vifffffffffff');
var dynCall_viffffffff = makeInvalidEarlyAccess('dynCall_viffffffff');
var dynCall_iiiiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiiiiiiii');
var dynCall_iiiiifiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiifiiiiiiiiiii');
var dynCall_iiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiiiii');
var dynCall_iiiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiiiiiii');
var dynCall_iiiifiififfiiiiii = makeInvalidEarlyAccess('dynCall_iiiifiififfiiiiii');
var dynCall_vifiiiii = makeInvalidEarlyAccess('dynCall_vifiiiii');
var dynCall_iifiiiiiiiii = makeInvalidEarlyAccess('dynCall_iifiiiiiiiii');
var dynCall_iiffiiiiii = makeInvalidEarlyAccess('dynCall_iiffiiiiii');
var dynCall_iiiiffffiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiffffiiiiiii');
var dynCall_iiifiifiiffiiiiiiii = makeInvalidEarlyAccess('dynCall_iiifiifiiffiiiiiiii');
var dynCall_iiiiifi = makeInvalidEarlyAccess('dynCall_iiiiifi');
var dynCall_viffiiiiiii = makeInvalidEarlyAccess('dynCall_viffiiiiiii');
var dynCall_iifiiiii = makeInvalidEarlyAccess('dynCall_iifiiiii');
var dynCall_vifffiii = makeInvalidEarlyAccess('dynCall_vifffiii');
var dynCall_vf = makeInvalidEarlyAccess('dynCall_vf');
var dynCall_vifffffffff = makeInvalidEarlyAccess('dynCall_vifffffffff');
var dynCall_viffffff = makeInvalidEarlyAccess('dynCall_viffffff');
var dynCall_vifff = makeInvalidEarlyAccess('dynCall_vifff');
var dynCall_vifi = makeInvalidEarlyAccess('dynCall_vifi');
var dynCall_vfff = makeInvalidEarlyAccess('dynCall_vfff');
var dynCall_viffiii = makeInvalidEarlyAccess('dynCall_viffiii');
var dynCall_viiffffi = makeInvalidEarlyAccess('dynCall_viiffffi');
var dynCall_fii = makeInvalidEarlyAccess('dynCall_fii');
var dynCall_iffi = makeInvalidEarlyAccess('dynCall_iffi');
var dynCall_vfffii = makeInvalidEarlyAccess('dynCall_vfffii');
var dynCall_ffiffi = makeInvalidEarlyAccess('dynCall_ffiffi');
var dynCall_viff = makeInvalidEarlyAccess('dynCall_viff');
var dynCall_viiff = makeInvalidEarlyAccess('dynCall_viiff');
var dynCall_fffffi = makeInvalidEarlyAccess('dynCall_fffffi');
var dynCall_ifffiiiii = makeInvalidEarlyAccess('dynCall_ifffiiiii');
var dynCall_viifffffi = makeInvalidEarlyAccess('dynCall_viifffffi');
var dynCall_viifffffifffff = makeInvalidEarlyAccess('dynCall_viifffffifffff');
var dynCall_fiiiii = makeInvalidEarlyAccess('dynCall_fiiiii');
var dynCall_iiiif = makeInvalidEarlyAccess('dynCall_iiiif');
var dynCall_iiiiiiiiffffi = makeInvalidEarlyAccess('dynCall_iiiiiiiiffffi');
var dynCall_viiifi = makeInvalidEarlyAccess('dynCall_viiifi');
var dynCall_viiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiii');
var dynCall_viiif = makeInvalidEarlyAccess('dynCall_viiif');
var dynCall_fifi = makeInvalidEarlyAccess('dynCall_fifi');
var dynCall_iffffiiffiii = makeInvalidEarlyAccess('dynCall_iffffiiffiii');
var dynCall_iiiifffffffi = makeInvalidEarlyAccess('dynCall_iiiifffffffi');
var dynCall_viifi = makeInvalidEarlyAccess('dynCall_viifi');
var dynCall_f = makeInvalidEarlyAccess('dynCall_f');
var dynCall_iiiffffffiififii = makeInvalidEarlyAccess('dynCall_iiiffffffiififii');
var dynCall_iiifffiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiifffiiiiiiiiii');
var dynCall_viifii = makeInvalidEarlyAccess('dynCall_viifii');
var dynCall_viif = makeInvalidEarlyAccess('dynCall_viif');
var dynCall_iiffffffii = makeInvalidEarlyAccess('dynCall_iiffffffii');
var dynCall_iiffffffffffiiiiiiiiiiiffffff = makeInvalidEarlyAccess('dynCall_iiffffffffffiiiiiiiiiiiffffff');
var dynCall_viiiiffffffiiii = makeInvalidEarlyAccess('dynCall_viiiiffffffiiii');
var dynCall_viiiiffffffiiiffif = makeInvalidEarlyAccess('dynCall_viiiiffffffiiiffif');
var dynCall_iiiiiiiififffii = makeInvalidEarlyAccess('dynCall_iiiiiiiififffii');
var dynCall_iiiiiif = makeInvalidEarlyAccess('dynCall_iiiiiif');
var dynCall_iiiiiiiiif = makeInvalidEarlyAccess('dynCall_iiiiiiiiif');
var dynCall_ifffiiii = makeInvalidEarlyAccess('dynCall_ifffiiii');
var dynCall_vfffiiii = makeInvalidEarlyAccess('dynCall_vfffiiii');
var dynCall_iiifffiiiiii = makeInvalidEarlyAccess('dynCall_iiifffiiiiii');
var dynCall_iifiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iifiiiiiiiiii');
var dynCall_vfiiiiiiiiii = makeInvalidEarlyAccess('dynCall_vfiiiiiiiiii');
var dynCall_iifii = makeInvalidEarlyAccess('dynCall_iifii');
var dynCall_vfiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_vfiiiiiiiiiii');
var dynCall_viiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiii');
var dynCall_fifffff = makeInvalidEarlyAccess('dynCall_fifffff');
var dynCall_fif = makeInvalidEarlyAccess('dynCall_fif');
var dynCall_viiifffiiii = makeInvalidEarlyAccess('dynCall_viiifffiiii');
var dynCall_viiiiiifffiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiifffiiiiiiiiiii');
var dynCall_iiffffffi = makeInvalidEarlyAccess('dynCall_iiffffffi');
var dynCall_viiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiiii');
var dynCall_iiiiiiiiiffffiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiffffiii');
var dynCall_ifiiiiiiiii = makeInvalidEarlyAccess('dynCall_ifiiiiiiiii');
var dynCall_iiiiiiiifiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiifiiiiii');
var dynCall_viifiiii = makeInvalidEarlyAccess('dynCall_viifiiii');
var dynCall_ifffi = makeInvalidEarlyAccess('dynCall_ifffi');
var dynCall_iiiiifiii = makeInvalidEarlyAccess('dynCall_iiiiifiii');
var dynCall_iiiiiiffiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiffiiiii');
var dynCall_iiiiiiiiffiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiffiiiii');
var dynCall_iifffffffii = makeInvalidEarlyAccess('dynCall_iifffffffii');
var dynCall_viffff = makeInvalidEarlyAccess('dynCall_viffff');
var dynCall_viifffff = makeInvalidEarlyAccess('dynCall_viifffff');
var dynCall_viiiiiiffffiiff = makeInvalidEarlyAccess('dynCall_viiiiiiffffiiff');
var dynCall_iiiiiiiiffffiiffi = makeInvalidEarlyAccess('dynCall_iiiiiiiiffffiiffi');
var dynCall_viiiiiiffffii = makeInvalidEarlyAccess('dynCall_viiiiiiffffii');
var dynCall_viiiiiiffffiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiffffiiiii');
var dynCall_iffff = makeInvalidEarlyAccess('dynCall_iffff');
var dynCall_viifff = makeInvalidEarlyAccess('dynCall_viifff');
var dynCall_iiiiiiiiiifffiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiifffiiiiiiiiiiiii');
var dynCall_vifffi = makeInvalidEarlyAccess('dynCall_vifffi');
var dynCall_iiiiff = makeInvalidEarlyAccess('dynCall_iiiiff');
var dynCall_vififf = makeInvalidEarlyAccess('dynCall_vififf');
var dynCall_fiff = makeInvalidEarlyAccess('dynCall_fiff');
var dynCall_vfffi = makeInvalidEarlyAccess('dynCall_vfffi');
var dynCall_viiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiii');
var dynCall_iiiiffiiii = makeInvalidEarlyAccess('dynCall_iiiiffiiii');
var dynCall_iiiifiiii = makeInvalidEarlyAccess('dynCall_iiiifiiii');
var dynCall_iifi = makeInvalidEarlyAccess('dynCall_iifi');
var dynCall_viiiif = makeInvalidEarlyAccess('dynCall_viiiif');
var dynCall_vififfffi = makeInvalidEarlyAccess('dynCall_vififfffi');
var dynCall_vifffiiififfi = makeInvalidEarlyAccess('dynCall_vifffiiififfi');
var dynCall_vffffiffffiii = makeInvalidEarlyAccess('dynCall_vffffiffffiii');
var dynCall_iiiiiifffiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiifffiiiiiiiiii');
var dynCall_iffffiiiiifii = makeInvalidEarlyAccess('dynCall_iffffiiiiifii');
var dynCall_vfffffffiifii = makeInvalidEarlyAccess('dynCall_vfffffffiifii');
var dynCall_vffffiiiiifii = makeInvalidEarlyAccess('dynCall_vffffiiiiifii');
var dynCall_vffffiiiiiifii = makeInvalidEarlyAccess('dynCall_vffffiiiiiifii');
var dynCall_viiiifii = makeInvalidEarlyAccess('dynCall_viiiifii');
var dynCall_iiiiiiiiiiifiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiifiiii');
var dynCall_viiiifiii = makeInvalidEarlyAccess('dynCall_viiiifiii');
var dynCall_iiffffii = makeInvalidEarlyAccess('dynCall_iiffffii');
var dynCall_iifffii = makeInvalidEarlyAccess('dynCall_iifffii');
var dynCall_iiifiiiii = makeInvalidEarlyAccess('dynCall_iiifiiiii');
var dynCall_iiiifiiiii = makeInvalidEarlyAccess('dynCall_iiiifiiiii');
var dynCall_iiiffifiiiii = makeInvalidEarlyAccess('dynCall_iiiffifiiiii');
var dynCall_iiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiiiiii');
var dynCall_vfi = makeInvalidEarlyAccess('dynCall_vfi');
var dynCall_fiiiif = makeInvalidEarlyAccess('dynCall_fiiiif');
var dynCall_viififfii = makeInvalidEarlyAccess('dynCall_viififfii');
var dynCall_viiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiii');
var dynCall_viiifii = makeInvalidEarlyAccess('dynCall_viiifii');
var dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiii');
var dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii');
var dynCall_viiiiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiiiiii');
var dynCall_viffifiiiii = makeInvalidEarlyAccess('dynCall_viffifiiiii');
var dynCall_vffffifiiii = makeInvalidEarlyAccess('dynCall_vffffifiiii');
var dynCall_viifffffffiifii = makeInvalidEarlyAccess('dynCall_viifffffffiifii');
var dynCall_vifffffiiiifii = makeInvalidEarlyAccess('dynCall_vifffffiiiifii');
var dynCall_vfffiiifiiiiiii = makeInvalidEarlyAccess('dynCall_vfffiiifiiiiiii');
var dynCall_iiffffiii = makeInvalidEarlyAccess('dynCall_iiffffiii');
var dynCall_vfffiiiiiiiiii = makeInvalidEarlyAccess('dynCall_vfffiiiiiiiiii');
var dynCall_iiiffffii = makeInvalidEarlyAccess('dynCall_iiiffffii');
var dynCall_ifffiii = makeInvalidEarlyAccess('dynCall_ifffiii');
var dynCall_viiiiiiffi = makeInvalidEarlyAccess('dynCall_viiiiiiffi');
var dynCall_viiiiiiiiff = makeInvalidEarlyAccess('dynCall_viiiiiiiiff');
var dynCall_viiiiiiiiiiiiiiiffi = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiiiiffi');
var dynCall_viiiiififiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiififiiiiiiii');
var dynCall_viiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiii');
var dynCall_vfiiii = makeInvalidEarlyAccess('dynCall_vfiiii');
var dynCall_iiiiifiiiii = makeInvalidEarlyAccess('dynCall_iiiiifiiiii');
var dynCall_viiifiii = makeInvalidEarlyAccess('dynCall_viiifiii');
var dynCall_ifffii = makeInvalidEarlyAccess('dynCall_ifffii');
var dynCall_iiiiffi = makeInvalidEarlyAccess('dynCall_iiiiffi');
var dynCall_fiiffff = makeInvalidEarlyAccess('dynCall_fiiffff');
var dynCall_vfffiiiff = makeInvalidEarlyAccess('dynCall_vfffiiiff');
var dynCall_iifiiiiii = makeInvalidEarlyAccess('dynCall_iifiiiiii');
var dynCall_iiifiiffiiiiii = makeInvalidEarlyAccess('dynCall_iiifiiffiiiiii');
var dynCall_viffii = makeInvalidEarlyAccess('dynCall_viffii');
var dynCall_viffiiii = makeInvalidEarlyAccess('dynCall_viffiiii');
var dynCall_iiiiif = makeInvalidEarlyAccess('dynCall_iiiiif');
var dynCall_iiiiffiffiiiifffiii = makeInvalidEarlyAccess('dynCall_iiiiffiffiiiifffiii');
var dynCall_iiifiiififiiii = makeInvalidEarlyAccess('dynCall_iiifiiififiiii');
var dynCall_iiiffff = makeInvalidEarlyAccess('dynCall_iiiffff');
var dynCall_viiiffi = makeInvalidEarlyAccess('dynCall_viiiffi');
var dynCall_vfffffiiiiifiiiiiifiiiiiiiiii = makeInvalidEarlyAccess('dynCall_vfffffiiiiifiiiiiifiiiiiiiiii');
var dynCall_vfffiffii = makeInvalidEarlyAccess('dynCall_vfffiffii');
var dynCall_iiiifffiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiifffiiiiiiiiiii');
var dynCall_iiiifffiffffiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiifffiffffiiiiiiiii');
var dynCall_iiiiifffiffffiiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiifffiffffiiiiiiiiii');
var dynCall_viiffiffffiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiffiffffiiiiiiiii');
var dynCall_ifiiiiiiii = makeInvalidEarlyAccess('dynCall_ifiiiiiiii');
var dynCall_iiiiiffifiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiffifiiiiiii');
var dynCall_viiiiffiii = makeInvalidEarlyAccess('dynCall_viiiiffiii');
var dynCall_viffiiiiii = makeInvalidEarlyAccess('dynCall_viffiiiiii');
var dynCall_iifiii = makeInvalidEarlyAccess('dynCall_iifiii');
var dynCall_vifffii = makeInvalidEarlyAccess('dynCall_vifffii');
var dynCall_viiiiiifiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiifiiiiiiiiii');
var dynCall_viiiiiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiiiiii');
var dynCall_iiiiifiiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiifiiiiiiiii');
var dynCall_iiiiiiifffffiiiiiiiiiifiiiii = makeInvalidEarlyAccess('dynCall_iiiiiiifffffiiiiiiiiiifiiiii');
var dynCall_iiiiiifiiiiifiiiiii = makeInvalidEarlyAccess('dynCall_iiiiiifiiiiifiiiiii');
var dynCall_iiif = makeInvalidEarlyAccess('dynCall_iiif');
var dynCall_viffffiii = makeInvalidEarlyAccess('dynCall_viffffiii');
var dynCall_viiffiifiiii = makeInvalidEarlyAccess('dynCall_viiffiifiiii');
var dynCall_iiiiiiiiiiiiiiiiiiiiffiii = makeInvalidEarlyAccess('dynCall_iiiiiiiiiiiiiiiiiiiiffiii');
var dynCall_vifffiiii = makeInvalidEarlyAccess('dynCall_vifffiiii');
var dynCall_iiiifiii = makeInvalidEarlyAccess('dynCall_iiiifiii');
var dynCall_iiiiiiifi = makeInvalidEarlyAccess('dynCall_iiiiiiifi');
var dynCall_iiifff = makeInvalidEarlyAccess('dynCall_iiifff');
var dynCall_vifffffff = makeInvalidEarlyAccess('dynCall_vifffffff');
var dynCall_iijjii = makeInvalidEarlyAccess('dynCall_iijjii');
var dynCall_j = makeInvalidEarlyAccess('dynCall_j');
var dynCall_ifff = makeInvalidEarlyAccess('dynCall_ifff');
var dynCall_vifiiii = makeInvalidEarlyAccess('dynCall_vifiiii');
var dynCall_viiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiii');
var dynCall_viiiiiifffffffffffii = makeInvalidEarlyAccess('dynCall_viiiiiifffffffffffii');
var dynCall_viiffffffff = makeInvalidEarlyAccess('dynCall_viiffffffff');
var dynCall_viiiiiiiiiiiii = makeInvalidEarlyAccess('dynCall_viiiiiiiiiiiii');
var dynCall_iiiifffifii = makeInvalidEarlyAccess('dynCall_iiiifffifii');
var dynCall_viifffi = makeInvalidEarlyAccess('dynCall_viifffi');
var dynCall_iiiiifiiiiii = makeInvalidEarlyAccess('dynCall_iiiiifiiiiii');
var dynCall_viiiiiffi = makeInvalidEarlyAccess('dynCall_viiiiiffi');
var dynCall_viiiiffi = makeInvalidEarlyAccess('dynCall_viiiiffi');
var dynCall_viffi = makeInvalidEarlyAccess('dynCall_viffi');
var dynCall_iiffiiiiiffi = makeInvalidEarlyAccess('dynCall_iiffiiiiiffi');
var dynCall_iffiiii = makeInvalidEarlyAccess('dynCall_iffiiii');
var dynCall_iiifi = makeInvalidEarlyAccess('dynCall_iiifi');
var dynCall_viifffffffff = makeInvalidEarlyAccess('dynCall_viifffffffff');
var dynCall_vififff = makeInvalidEarlyAccess('dynCall_vififff');
var dynCall_fiif = makeInvalidEarlyAccess('dynCall_fiif');
var dynCall_fiifi = makeInvalidEarlyAccess('dynCall_fiifi');
var dynCall_fiffif = makeInvalidEarlyAccess('dynCall_fiffif');
var dynCall_fifiiiiiiii = makeInvalidEarlyAccess('dynCall_fifiiiiiiii');
var dynCall_iiffii = makeInvalidEarlyAccess('dynCall_iiffii');
var dynCall_iiffif = makeInvalidEarlyAccess('dynCall_iiffif');
var dynCall_iiffiii = makeInvalidEarlyAccess('dynCall_iiffiii');
var dynCall_iiffffffifiiiiii = makeInvalidEarlyAccess('dynCall_iiffffffifiiiiii');
var dynCall_ffffff = makeInvalidEarlyAccess('dynCall_ffffff');
var dynCall_iif = makeInvalidEarlyAccess('dynCall_iif');
var dynCall_vffff = makeInvalidEarlyAccess('dynCall_vffff');
var dynCall_ifffiiiif = makeInvalidEarlyAccess('dynCall_ifffiiiif');
var dynCall_iiifffiiii = makeInvalidEarlyAccess('dynCall_iiifffiiii');
var dynCall_iiiff = makeInvalidEarlyAccess('dynCall_iiiff');
var dynCall_iiiffffiiiiii = makeInvalidEarlyAccess('dynCall_iiiffffiiiiii');
var dynCall_viiij = makeInvalidEarlyAccess('dynCall_viiij');
var dynCall_iifff = makeInvalidEarlyAccess('dynCall_iifff');
var dynCall_iffiii = makeInvalidEarlyAccess('dynCall_iffiii');
var dynCall_iifffiii = makeInvalidEarlyAccess('dynCall_iifffiii');
var dynCall_iiffffff = makeInvalidEarlyAccess('dynCall_iiffffff');
var dynCall_iiiffffff = makeInvalidEarlyAccess('dynCall_iiiffffff');
var dynCall_vfiii = makeInvalidEarlyAccess('dynCall_vfiii');
var dynCall_iffii = makeInvalidEarlyAccess('dynCall_iffii');
var dynCall_iiiifiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiifiiiiiiii');
var dynCall_iiiiifiiiiiiii = makeInvalidEarlyAccess('dynCall_iiiiifiiiiiiii');
var dynCall_iiifif = makeInvalidEarlyAccess('dynCall_iiifif');
var dynCall_vffi = makeInvalidEarlyAccess('dynCall_vffi');
var dynCall_vijj = makeInvalidEarlyAccess('dynCall_vijj');
var dynCall_vj = makeInvalidEarlyAccess('dynCall_vj');
var dynCall_ji = makeInvalidEarlyAccess('dynCall_ji');
var dynCall_jjj = makeInvalidEarlyAccess('dynCall_jjj');
var dynCall_viiji = makeInvalidEarlyAccess('dynCall_viiji');
var dynCall_viifiiiifii = makeInvalidEarlyAccess('dynCall_viifiiiifii');
var dynCall_iffffff = makeInvalidEarlyAccess('dynCall_iffffff');
var dynCall_iiiifff = makeInvalidEarlyAccess('dynCall_iiiifff');
var dynCall_iffffffiiiiiiiif = makeInvalidEarlyAccess('dynCall_iffffffiiiiiiiif');
var dynCall_iiiffffi = makeInvalidEarlyAccess('dynCall_iiiffffi');
var dynCall_viiiiifiiiii = makeInvalidEarlyAccess('dynCall_viiiiifiiiii');
var dynCall_viiffff = makeInvalidEarlyAccess('dynCall_viiffff');
var dynCall_vdi = makeInvalidEarlyAccess('dynCall_vdi');
var dynCall_vd = makeInvalidEarlyAccess('dynCall_vd');
var dynCall_dd = makeInvalidEarlyAccess('dynCall_dd');
var dynCall_vfffffffi = makeInvalidEarlyAccess('dynCall_vfffffffi');
var dynCall_d = makeInvalidEarlyAccess('dynCall_d');
var dynCall_jiji = makeInvalidEarlyAccess('dynCall_jiji');
var dynCall_iidiiii = makeInvalidEarlyAccess('dynCall_iidiiii');
var _asyncify_start_unwind = makeInvalidEarlyAccess('_asyncify_start_unwind');
var _asyncify_stop_unwind = makeInvalidEarlyAccess('_asyncify_stop_unwind');
var _asyncify_start_rewind = makeInvalidEarlyAccess('_asyncify_start_rewind');
var _asyncify_stop_rewind = makeInvalidEarlyAccess('_asyncify_stop_rewind');

function assignWasmExports(wasmExports) {
  Module['_main'] = _main = createExportWrapper('main', 2);
  Module['_free'] = _free = createExportWrapper('free', 1);
  Module['_port_net_kick'] = _port_net_kick = createExportWrapper('port_net_kick', 0);
  Module['_port_net_ready'] = _port_net_ready = createExportWrapper('port_net_ready', 1);
  Module['_port_dump_threads'] = _port_dump_threads = createExportWrapper('port_dump_threads', 0);
  Module['_port_dump_stubs'] = _port_dump_stubs = createExportWrapper('port_dump_stubs', 1);
  Module['_malloc'] = _malloc = createExportWrapper('malloc', 1);
  _fflush = createExportWrapper('fflush', 1);
  Module['_port_set_rom'] = _port_set_rom = createExportWrapper('port_set_rom', 2);
  Module['_port_set_paused'] = _port_set_paused = createExportWrapper('port_set_paused', 1);
  Module['_port_set_option'] = _port_set_option = createExportWrapper('port_set_option', 2);
  Module['_port_set_gmenu_row'] = _port_set_gmenu_row = createExportWrapper('port_set_gmenu_row', 1);
  Module['_port_gmenu_take_request'] = _port_gmenu_take_request = createExportWrapper('port_gmenu_take_request', 0);
  Module['_port_skip_progress'] = _port_skip_progress = createExportWrapper('port_skip_progress', 0);
  Module['_port_pad_state'] = _port_pad_state = createExportWrapper('port_pad_state', 0);
  Module['_port_cam_state'] = _port_cam_state = createExportWrapper('port_cam_state', 0);
  Module['_port_eeprom_ptr'] = _port_eeprom_ptr = createExportWrapper('port_eeprom_ptr', 0);
  Module['_port_eeprom_size'] = _port_eeprom_size = createExportWrapper('port_eeprom_size', 0);
  Module['_port_eep_test'] = _port_eep_test = createExportWrapper('port_eep_test', 2);
  Module['_port_net_force_det'] = _port_net_force_det = createExportWrapper('port_net_force_det', 0);
  Module['_port_net_session'] = _port_net_session = createExportWrapper('port_net_session', 4);
  Module['_port_net_addr'] = _port_net_addr = createExportWrapper('port_net_addr', 1);
  Module['_port_net_frame'] = _port_net_frame = createExportWrapper('port_net_frame', 0);
  Module['_port_net_script_input'] = _port_net_script_input = createExportWrapper('port_net_script_input', 2);
  Module['_port_net_drop'] = _port_net_drop = createExportWrapper('port_net_drop', 2);
  Module['_port_net_slow'] = _port_net_slow = createExportWrapper('port_net_slow', 1);
  Module['_port_rec_checkpoint_ms'] = _port_rec_checkpoint_ms = createExportWrapper('port_rec_checkpoint_ms', 0);
  Module['_port_rec_session'] = _port_rec_session = createExportWrapper('port_rec_session', 7);
  Module['_port_rec_checkpoint_now'] = _port_rec_checkpoint_now = createExportWrapper('port_rec_checkpoint_now', 0);
  Module['_port_net_exclude'] = _port_net_exclude = createExportWrapper('port_net_exclude', 2);
  Module['_port_net_region'] = _port_net_region = createExportWrapper('port_net_region', 2);
  Module['_port_net_page_hashes'] = _port_net_page_hashes = createExportWrapper('port_net_page_hashes', 1);
  Module['_port_net_page_info'] = _port_net_page_info = createExportWrapper('port_net_page_info', 1);
  Module['_port_photo_input'] = _port_photo_input = createExportWrapper('port_photo_input', 8);
  Module['_port_photo_request'] = _port_photo_request = createExportWrapper('port_photo_request', 1);
  Module['_port_photo_status'] = _port_photo_status = createExportWrapper('port_photo_status', 0);
  Module['_port_photo_render'] = _port_photo_render = createExportWrapper('port_photo_render', 0);
  Module['_port_photo_info'] = _port_photo_info = createExportWrapper('port_photo_info', 1);
  Module['_port_photo_look_set'] = _port_photo_look_set = createExportWrapper('port_photo_look_set', 3);
  Module['_port_photo_look_info'] = _port_photo_look_info = createExportWrapper('port_photo_look_info', 2);
  Module['_port_sfx_info'] = _port_sfx_info = createExportWrapper('port_sfx_info', 0);
  Module['_port_sfx_pcm'] = _port_sfx_pcm = createExportWrapper('port_sfx_pcm', 0);
  Module['_port_sfx_decode'] = _port_sfx_decode = createExportWrapper('port_sfx_decode', 2);
  Module['_port_rtw_raw_state'] = _port_rtw_raw_state = createExportWrapper('port_rtw_raw_state', 0);
  Module['_port_rtw_lock_game_options'] = _port_rtw_lock_game_options = createExportWrapper('port_rtw_lock_game_options', 0);
  Module['_port_rtw_log'] = _port_rtw_log = createExportWrapper('port_rtw_log', 1);
  Module['_port_rtw_export_file'] = _port_rtw_export_file = createExportWrapper('port_rtw_export_file', 4);
  Module['_port_rtw_build_id'] = _port_rtw_build_id = createExportWrapper('port_rtw_build_id', 1);
  Module['_port_rtw_set_pointer_lock'] = _port_rtw_set_pointer_lock = createExportWrapper('port_rtw_set_pointer_lock', 1);
  Module['_rtw_rom_buffer'] = _rtw_rom_buffer = createExportWrapper('rtw_rom_buffer', 1);
  Module['_port_rtw_rom_ptr'] = _port_rtw_rom_ptr = createExportWrapper('port_rtw_rom_ptr', 0);
  Module['_port_rtw_rom_size'] = _port_rtw_rom_size = createExportWrapper('port_rtw_rom_size', 0);
  Module['_rtw_save_ptr'] = _rtw_save_ptr = createExportWrapper('rtw_save_ptr', 0);
  Module['_rtw_save_size'] = _rtw_save_size = createExportWrapper('rtw_save_size', 0);
  Module['_rtw_save_generation'] = _rtw_save_generation = createExportWrapper('rtw_save_generation', 0);
  Module['_rtw_save_load'] = _rtw_save_load = createExportWrapper('rtw_save_load', 2);
  Module['_rtw_start'] = _rtw_start = createExportWrapper('rtw_start', 0);
  Module['_rtw_pause'] = _rtw_pause = createExportWrapper('rtw_pause', 1);
  Module['_rtw_input'] = _rtw_input = createExportWrapper('rtw_input', 4);
  Module['_rtw_mouse'] = _rtw_mouse = createExportWrapper('rtw_mouse', 3);
  Module['_rtw_resize'] = _rtw_resize = createExportWrapper('rtw_resize', 3);
  Module['_rtw_audio_rate'] = _rtw_audio_rate = createExportWrapper('rtw_audio_rate', 0);
  Module['_rtw_audio_drain'] = _rtw_audio_drain = createExportWrapper('rtw_audio_drain', 0);
  Module['_rtw_audio_buffer'] = _rtw_audio_buffer = createExportWrapper('rtw_audio_buffer', 0);
  Module['_rtw_option'] = _rtw_option = createExportWrapper('rtw_option', 2);
  Module['_port_gfx_hires_2d'] = _port_gfx_hires_2d = createExportWrapper('port_gfx_hires_2d', 1);
  Module['_port_gfx_smooth_font'] = _port_gfx_smooth_font = createExportWrapper('port_gfx_smooth_font', 1);
  Module['_port_gfx_widescreen'] = _port_gfx_widescreen = createExportWrapper('port_gfx_widescreen', 1);
  Module['_port_gfx_ownview'] = _port_gfx_ownview = createExportWrapper('port_gfx_ownview', 1);
  Module['_port_gfx_ownview_state'] = _port_gfx_ownview_state = createExportWrapper('port_gfx_ownview_state', 0);
  Module['_port_gfx_resize'] = _port_gfx_resize = createExportWrapper('port_gfx_resize', 2);
  Module['_port_font_info'] = _port_font_info = createExportWrapper('port_font_info', 1);
  Module['_port_font_glyph'] = _port_font_glyph = createExportWrapper('port_font_glyph', 1);
  Module['_port_gfx_hfr'] = _port_gfx_hfr = createExportWrapper('port_gfx_hfr', 1);
  Module['_port_gfx_hfr_vsync'] = _port_gfx_hfr_vsync = createExportWrapper('port_gfx_hfr_vsync', 0);
  Module['_port_gfx_hfr_frame'] = _port_gfx_hfr_frame = createExportWrapper('port_gfx_hfr_frame', 0);
  Module['_port_gfx_hfr_test'] = _port_gfx_hfr_test = createExportWrapper('port_gfx_hfr_test', 1);
  _emscripten_stack_get_current = wasmExports['emscripten_stack_get_current'];
  Module['_port_rtw_audio_drained'] = _port_rtw_audio_drained = createExportWrapper('port_rtw_audio_drained', 0);
  _strerror = createExportWrapper('strerror', 1);
  _emscripten_stack_set_limits = wasmExports['emscripten_stack_set_limits'];
  __emscripten_stack_restore = wasmExports['_emscripten_stack_restore'];
  __emscripten_stack_alloc = wasmExports['_emscripten_stack_alloc'];
  dynCalls['v'] = dynCall_v = createExportWrapper('dynCall_v', 1);
  dynCalls['vii'] = dynCall_vii = createExportWrapper('dynCall_vii', 3);
  dynCalls['i'] = dynCall_i = createExportWrapper('dynCall_i', 1);
  dynCalls['viii'] = dynCall_viii = createExportWrapper('dynCall_viii', 4);
  dynCalls['vi'] = dynCall_vi = createExportWrapper('dynCall_vi', 2);
  dynCalls['ii'] = dynCall_ii = createExportWrapper('dynCall_ii', 2);
  dynCalls['vif'] = dynCall_vif = createExportWrapper('dynCall_vif', 3);
  dynCalls['iii'] = dynCall_iii = createExportWrapper('dynCall_iii', 3);
  dynCalls['viiii'] = dynCall_viiii = createExportWrapper('dynCall_viiii', 5);
  dynCalls['if'] = dynCall_if = createExportWrapper('dynCall_if', 2);
  dynCalls['iiii'] = dynCall_iiii = createExportWrapper('dynCall_iiii', 4);
  dynCalls['iiiii'] = dynCall_iiiii = createExportWrapper('dynCall_iiiii', 5);
  dynCalls['viiiii'] = dynCall_viiiii = createExportWrapper('dynCall_viiiii', 6);
  dynCalls['iiffffi'] = dynCall_iiffffi = createExportWrapper('dynCall_iiffffi', 7);
  dynCalls['iifffi'] = dynCall_iifffi = createExportWrapper('dynCall_iifffi', 6);
  dynCalls['iiiiiiiiii'] = dynCall_iiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiii', 10);
  dynCalls['iiiiiiiii'] = dynCall_iiiiiiiii = createExportWrapper('dynCall_iiiiiiiii', 9);
  dynCalls['iiiiiiii'] = dynCall_iiiiiiii = createExportWrapper('dynCall_iiiiiiii', 8);
  dynCalls['ff'] = dynCall_ff = createExportWrapper('dynCall_ff', 2);
  dynCalls['fff'] = dynCall_fff = createExportWrapper('dynCall_fff', 3);
  dynCalls['ffff'] = dynCall_ffff = createExportWrapper('dynCall_ffff', 4);
  dynCalls['iifffffffff'] = dynCall_iifffffffff = createExportWrapper('dynCall_iifffffffff', 11);
  dynCalls['iiiiii'] = dynCall_iiiiii = createExportWrapper('dynCall_iiiiii', 6);
  dynCalls['viiiiiii'] = dynCall_viiiiiii = createExportWrapper('dynCall_viiiiiii', 8);
  dynCalls['iiifiifiiifiiii'] = dynCall_iiifiifiiifiiii = createExportWrapper('dynCall_iiifiifiiifiiii', 15);
  dynCalls['vffffffi'] = dynCall_vffffffi = createExportWrapper('dynCall_vffffffi', 8);
  dynCalls['vffii'] = dynCall_vffii = createExportWrapper('dynCall_vffii', 5);
  dynCalls['fi'] = dynCall_fi = createExportWrapper('dynCall_fi', 2);
  dynCalls['vifffiiiiiiii'] = dynCall_vifffiiiiiiii = createExportWrapper('dynCall_vifffiiiiiiii', 13);
  dynCalls['iiifii'] = dynCall_iiifii = createExportWrapper('dynCall_iiifii', 6);
  dynCalls['vifii'] = dynCall_vifii = createExportWrapper('dynCall_vifii', 5);
  dynCalls['iffiiiiiiiii'] = dynCall_iffiiiiiiiii = createExportWrapper('dynCall_iffiiiiiiiii', 12);
  dynCalls['vfiiiiiiii'] = dynCall_vfiiiiiiii = createExportWrapper('dynCall_vfiiiiiiii', 10);
  dynCalls['viiiiii'] = dynCall_viiiiii = createExportWrapper('dynCall_viiiiii', 7);
  dynCalls['viiiifiiiiii'] = dynCall_viiiifiiiiii = createExportWrapper('dynCall_viiiifiiiiii', 12);
  dynCalls['viiiifi'] = dynCall_viiiifi = createExportWrapper('dynCall_viiiifi', 7);
  dynCalls['viiiifiiiiiiii'] = dynCall_viiiifiiiiiiii = createExportWrapper('dynCall_viiiifiiiiiiii', 14);
  dynCalls['viifiii'] = dynCall_viifiii = createExportWrapper('dynCall_viifiii', 7);
  dynCalls['iiiiiiiiiiii'] = dynCall_iiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiiii', 12);
  dynCalls['iiiiifffffiiiiiii'] = dynCall_iiiiifffffiiiiiii = createExportWrapper('dynCall_iiiiifffffiiiiiii', 17);
  dynCalls['vifffffi'] = dynCall_vifffffi = createExportWrapper('dynCall_vifffffi', 8);
  dynCalls['iiiiifffffiiiii'] = dynCall_iiiiifffffiiiii = createExportWrapper('dynCall_iiiiifffffiiiii', 15);
  dynCalls['iiiifffffi'] = dynCall_iiiifffffi = createExportWrapper('dynCall_iiiifffffi', 10);
  dynCalls['iiiiiifffffiiiii'] = dynCall_iiiiiifffffiiiii = createExportWrapper('dynCall_iiiiiifffffiiiii', 16);
  dynCalls['iiiiiiiiiiiii'] = dynCall_iiiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiiiii', 13);
  dynCalls['iiiiiiiiiii'] = dynCall_iiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiii', 11);
  dynCalls['iiiiiiiiffiiiiiiii'] = dynCall_iiiiiiiiffiiiiiiii = createExportWrapper('dynCall_iiiiiiiiffiiiiiiii', 18);
  dynCalls['iiiffiii'] = dynCall_iiiffiii = createExportWrapper('dynCall_iiiffiii', 8);
  dynCalls['iiiiiiiiffiiiiii'] = dynCall_iiiiiiiiffiiiiii = createExportWrapper('dynCall_iiiiiiiiffiiiiii', 16);
  dynCalls['viiiiff'] = dynCall_viiiiff = createExportWrapper('dynCall_viiiiff', 7);
  dynCalls['viiiff'] = dynCall_viiiff = createExportWrapper('dynCall_viiiff', 6);
  dynCalls['iiiiiii'] = dynCall_iiiiiii = createExportWrapper('dynCall_iiiiiii', 7);
  dynCalls['vifffffffffff'] = dynCall_vifffffffffff = createExportWrapper('dynCall_vifffffffffff', 13);
  dynCalls['viffffffff'] = dynCall_viffffffff = createExportWrapper('dynCall_viffffffff', 10);
  dynCalls['iiiiiiiiiiiiiiiii'] = dynCall_iiiiiiiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiiiiiiiii', 17);
  dynCalls['iiiiifiiiiiiiiiii'] = dynCall_iiiiifiiiiiiiiiii = createExportWrapper('dynCall_iiiiifiiiiiiiiiii', 17);
  dynCalls['iiiiiiiiiiiiii'] = dynCall_iiiiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiiiiii', 14);
  dynCalls['iiiiiiiiiiiiiiii'] = dynCall_iiiiiiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiiiiiiii', 16);
  dynCalls['iiiifiififfiiiiii'] = dynCall_iiiifiififfiiiiii = createExportWrapper('dynCall_iiiifiififfiiiiii', 17);
  dynCalls['vifiiiii'] = dynCall_vifiiiii = createExportWrapper('dynCall_vifiiiii', 8);
  dynCalls['iifiiiiiiiii'] = dynCall_iifiiiiiiiii = createExportWrapper('dynCall_iifiiiiiiiii', 12);
  dynCalls['iiffiiiiii'] = dynCall_iiffiiiiii = createExportWrapper('dynCall_iiffiiiiii', 10);
  dynCalls['iiiiffffiiiiiii'] = dynCall_iiiiffffiiiiiii = createExportWrapper('dynCall_iiiiffffiiiiiii', 15);
  dynCalls['iiifiifiiffiiiiiiii'] = dynCall_iiifiifiiffiiiiiiii = createExportWrapper('dynCall_iiifiifiiffiiiiiiii', 19);
  dynCalls['iiiiifi'] = dynCall_iiiiifi = createExportWrapper('dynCall_iiiiifi', 7);
  dynCalls['viffiiiiiii'] = dynCall_viffiiiiiii = createExportWrapper('dynCall_viffiiiiiii', 11);
  dynCalls['iifiiiii'] = dynCall_iifiiiii = createExportWrapper('dynCall_iifiiiii', 8);
  dynCalls['vifffiii'] = dynCall_vifffiii = createExportWrapper('dynCall_vifffiii', 8);
  dynCalls['vf'] = dynCall_vf = createExportWrapper('dynCall_vf', 2);
  dynCalls['vifffffffff'] = dynCall_vifffffffff = createExportWrapper('dynCall_vifffffffff', 11);
  dynCalls['viffffff'] = dynCall_viffffff = createExportWrapper('dynCall_viffffff', 8);
  dynCalls['vifff'] = dynCall_vifff = createExportWrapper('dynCall_vifff', 5);
  dynCalls['vifi'] = dynCall_vifi = createExportWrapper('dynCall_vifi', 4);
  dynCalls['vfff'] = dynCall_vfff = createExportWrapper('dynCall_vfff', 4);
  dynCalls['viffiii'] = dynCall_viffiii = createExportWrapper('dynCall_viffiii', 7);
  dynCalls['viiffffi'] = dynCall_viiffffi = createExportWrapper('dynCall_viiffffi', 8);
  dynCalls['fii'] = dynCall_fii = createExportWrapper('dynCall_fii', 3);
  dynCalls['iffi'] = dynCall_iffi = createExportWrapper('dynCall_iffi', 4);
  dynCalls['vfffii'] = dynCall_vfffii = createExportWrapper('dynCall_vfffii', 6);
  dynCalls['ffiffi'] = dynCall_ffiffi = createExportWrapper('dynCall_ffiffi', 6);
  dynCalls['viff'] = dynCall_viff = createExportWrapper('dynCall_viff', 4);
  dynCalls['viiff'] = dynCall_viiff = createExportWrapper('dynCall_viiff', 5);
  dynCalls['fffffi'] = dynCall_fffffi = createExportWrapper('dynCall_fffffi', 6);
  dynCalls['ifffiiiii'] = dynCall_ifffiiiii = createExportWrapper('dynCall_ifffiiiii', 9);
  dynCalls['viifffffi'] = dynCall_viifffffi = createExportWrapper('dynCall_viifffffi', 9);
  dynCalls['viifffffifffff'] = dynCall_viifffffifffff = createExportWrapper('dynCall_viifffffifffff', 14);
  dynCalls['fiiiii'] = dynCall_fiiiii = createExportWrapper('dynCall_fiiiii', 6);
  dynCalls['iiiif'] = dynCall_iiiif = createExportWrapper('dynCall_iiiif', 5);
  dynCalls['iiiiiiiiffffi'] = dynCall_iiiiiiiiffffi = createExportWrapper('dynCall_iiiiiiiiffffi', 13);
  dynCalls['viiifi'] = dynCall_viiifi = createExportWrapper('dynCall_viiifi', 6);
  dynCalls['viiiiiiii'] = dynCall_viiiiiiii = createExportWrapper('dynCall_viiiiiiii', 9);
  dynCalls['viiif'] = dynCall_viiif = createExportWrapper('dynCall_viiif', 5);
  dynCalls['fifi'] = dynCall_fifi = createExportWrapper('dynCall_fifi', 4);
  dynCalls['iffffiiffiii'] = dynCall_iffffiiffiii = createExportWrapper('dynCall_iffffiiffiii', 12);
  dynCalls['iiiifffffffi'] = dynCall_iiiifffffffi = createExportWrapper('dynCall_iiiifffffffi', 12);
  dynCalls['viifi'] = dynCall_viifi = createExportWrapper('dynCall_viifi', 5);
  dynCalls['f'] = dynCall_f = createExportWrapper('dynCall_f', 1);
  dynCalls['iiiffffffiififii'] = dynCall_iiiffffffiififii = createExportWrapper('dynCall_iiiffffffiififii', 16);
  dynCalls['iiifffiiiiiiiiii'] = dynCall_iiifffiiiiiiiiii = createExportWrapper('dynCall_iiifffiiiiiiiiii', 16);
  dynCalls['viifii'] = dynCall_viifii = createExportWrapper('dynCall_viifii', 6);
  dynCalls['viif'] = dynCall_viif = createExportWrapper('dynCall_viif', 4);
  dynCalls['iiffffffii'] = dynCall_iiffffffii = createExportWrapper('dynCall_iiffffffii', 10);
  dynCalls['iiffffffffffiiiiiiiiiiiffffff'] = dynCall_iiffffffffffiiiiiiiiiiiffffff = createExportWrapper('dynCall_iiffffffffffiiiiiiiiiiiffffff', 29);
  dynCalls['viiiiffffffiiii'] = dynCall_viiiiffffffiiii = createExportWrapper('dynCall_viiiiffffffiiii', 15);
  dynCalls['viiiiffffffiiiffif'] = dynCall_viiiiffffffiiiffif = createExportWrapper('dynCall_viiiiffffffiiiffif', 18);
  dynCalls['iiiiiiiififffii'] = dynCall_iiiiiiiififffii = createExportWrapper('dynCall_iiiiiiiififffii', 15);
  dynCalls['iiiiiif'] = dynCall_iiiiiif = createExportWrapper('dynCall_iiiiiif', 7);
  dynCalls['iiiiiiiiif'] = dynCall_iiiiiiiiif = createExportWrapper('dynCall_iiiiiiiiif', 10);
  dynCalls['ifffiiii'] = dynCall_ifffiiii = createExportWrapper('dynCall_ifffiiii', 8);
  dynCalls['vfffiiii'] = dynCall_vfffiiii = createExportWrapper('dynCall_vfffiiii', 8);
  dynCalls['iiifffiiiiii'] = dynCall_iiifffiiiiii = createExportWrapper('dynCall_iiifffiiiiii', 12);
  dynCalls['iifiiiiiiiiii'] = dynCall_iifiiiiiiiiii = createExportWrapper('dynCall_iifiiiiiiiiii', 13);
  dynCalls['vfiiiiiiiiii'] = dynCall_vfiiiiiiiiii = createExportWrapper('dynCall_vfiiiiiiiiii', 12);
  dynCalls['iifii'] = dynCall_iifii = createExportWrapper('dynCall_iifii', 5);
  dynCalls['vfiiiiiiiiiii'] = dynCall_vfiiiiiiiiiii = createExportWrapper('dynCall_vfiiiiiiiiiii', 13);
  dynCalls['viiiiiiiii'] = dynCall_viiiiiiiii = createExportWrapper('dynCall_viiiiiiiii', 10);
  dynCalls['fifffff'] = dynCall_fifffff = createExportWrapper('dynCall_fifffff', 7);
  dynCalls['fif'] = dynCall_fif = createExportWrapper('dynCall_fif', 3);
  dynCalls['viiifffiiii'] = dynCall_viiifffiiii = createExportWrapper('dynCall_viiifffiiii', 11);
  dynCalls['viiiiiifffiiiiiiiiiii'] = dynCall_viiiiiifffiiiiiiiiiii = createExportWrapper('dynCall_viiiiiifffiiiiiiiiiii', 21);
  dynCalls['iiffffffi'] = dynCall_iiffffffi = createExportWrapper('dynCall_iiffffffi', 9);
  dynCalls['viiiiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiiiii', 16);
  dynCalls['iiiiiiiiiffffiii'] = dynCall_iiiiiiiiiffffiii = createExportWrapper('dynCall_iiiiiiiiiffffiii', 16);
  dynCalls['ifiiiiiiiii'] = dynCall_ifiiiiiiiii = createExportWrapper('dynCall_ifiiiiiiiii', 11);
  dynCalls['iiiiiiiifiiiiii'] = dynCall_iiiiiiiifiiiiii = createExportWrapper('dynCall_iiiiiiiifiiiiii', 15);
  dynCalls['viifiiii'] = dynCall_viifiiii = createExportWrapper('dynCall_viifiiii', 8);
  dynCalls['ifffi'] = dynCall_ifffi = createExportWrapper('dynCall_ifffi', 5);
  dynCalls['iiiiifiii'] = dynCall_iiiiifiii = createExportWrapper('dynCall_iiiiifiii', 9);
  dynCalls['iiiiiiffiiiii'] = dynCall_iiiiiiffiiiii = createExportWrapper('dynCall_iiiiiiffiiiii', 13);
  dynCalls['iiiiiiiiffiiiii'] = dynCall_iiiiiiiiffiiiii = createExportWrapper('dynCall_iiiiiiiiffiiiii', 15);
  dynCalls['iifffffffii'] = dynCall_iifffffffii = createExportWrapper('dynCall_iifffffffii', 11);
  dynCalls['viffff'] = dynCall_viffff = createExportWrapper('dynCall_viffff', 6);
  dynCalls['viifffff'] = dynCall_viifffff = createExportWrapper('dynCall_viifffff', 8);
  dynCalls['viiiiiiffffiiff'] = dynCall_viiiiiiffffiiff = createExportWrapper('dynCall_viiiiiiffffiiff', 15);
  dynCalls['iiiiiiiiffffiiffi'] = dynCall_iiiiiiiiffffiiffi = createExportWrapper('dynCall_iiiiiiiiffffiiffi', 17);
  dynCalls['viiiiiiffffii'] = dynCall_viiiiiiffffii = createExportWrapper('dynCall_viiiiiiffffii', 13);
  dynCalls['viiiiiiffffiiiii'] = dynCall_viiiiiiffffiiiii = createExportWrapper('dynCall_viiiiiiffffiiiii', 16);
  dynCalls['iffff'] = dynCall_iffff = createExportWrapper('dynCall_iffff', 5);
  dynCalls['viifff'] = dynCall_viifff = createExportWrapper('dynCall_viifff', 6);
  dynCalls['iiiiiiiiiifffiiiiiiiiiiiii'] = dynCall_iiiiiiiiiifffiiiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiifffiiiiiiiiiiiii', 26);
  dynCalls['vifffi'] = dynCall_vifffi = createExportWrapper('dynCall_vifffi', 6);
  dynCalls['iiiiff'] = dynCall_iiiiff = createExportWrapper('dynCall_iiiiff', 6);
  dynCalls['vififf'] = dynCall_vififf = createExportWrapper('dynCall_vififf', 6);
  dynCalls['fiff'] = dynCall_fiff = createExportWrapper('dynCall_fiff', 4);
  dynCalls['vfffi'] = dynCall_vfffi = createExportWrapper('dynCall_vfffi', 5);
  dynCalls['viiiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiiii', 15);
  dynCalls['iiiiffiiii'] = dynCall_iiiiffiiii = createExportWrapper('dynCall_iiiiffiiii', 10);
  dynCalls['iiiifiiii'] = dynCall_iiiifiiii = createExportWrapper('dynCall_iiiifiiii', 9);
  dynCalls['iifi'] = dynCall_iifi = createExportWrapper('dynCall_iifi', 4);
  dynCalls['viiiif'] = dynCall_viiiif = createExportWrapper('dynCall_viiiif', 6);
  dynCalls['vififfffi'] = dynCall_vififfffi = createExportWrapper('dynCall_vififfffi', 9);
  dynCalls['vifffiiififfi'] = dynCall_vifffiiififfi = createExportWrapper('dynCall_vifffiiififfi', 13);
  dynCalls['vffffiffffiii'] = dynCall_vffffiffffiii = createExportWrapper('dynCall_vffffiffffiii', 13);
  dynCalls['iiiiiifffiiiiiiiiii'] = dynCall_iiiiiifffiiiiiiiiii = createExportWrapper('dynCall_iiiiiifffiiiiiiiiii', 19);
  dynCalls['iffffiiiiifii'] = dynCall_iffffiiiiifii = createExportWrapper('dynCall_iffffiiiiifii', 13);
  dynCalls['vfffffffiifii'] = dynCall_vfffffffiifii = createExportWrapper('dynCall_vfffffffiifii', 13);
  dynCalls['vffffiiiiifii'] = dynCall_vffffiiiiifii = createExportWrapper('dynCall_vffffiiiiifii', 13);
  dynCalls['vffffiiiiiifii'] = dynCall_vffffiiiiiifii = createExportWrapper('dynCall_vffffiiiiiifii', 14);
  dynCalls['viiiifii'] = dynCall_viiiifii = createExportWrapper('dynCall_viiiifii', 8);
  dynCalls['iiiiiiiiiiifiiii'] = dynCall_iiiiiiiiiiifiiii = createExportWrapper('dynCall_iiiiiiiiiiifiiii', 16);
  dynCalls['viiiifiii'] = dynCall_viiiifiii = createExportWrapper('dynCall_viiiifiii', 9);
  dynCalls['iiffffii'] = dynCall_iiffffii = createExportWrapper('dynCall_iiffffii', 8);
  dynCalls['iifffii'] = dynCall_iifffii = createExportWrapper('dynCall_iifffii', 7);
  dynCalls['iiifiiiii'] = dynCall_iiifiiiii = createExportWrapper('dynCall_iiifiiiii', 9);
  dynCalls['iiiifiiiii'] = dynCall_iiiifiiiii = createExportWrapper('dynCall_iiiifiiiii', 10);
  dynCalls['iiiffifiiiii'] = dynCall_iiiffifiiiii = createExportWrapper('dynCall_iiiffifiiiii', 12);
  dynCalls['iiiiiiiiiiiiiii'] = dynCall_iiiiiiiiiiiiiii = createExportWrapper('dynCall_iiiiiiiiiiiiiii', 15);
  dynCalls['vfi'] = dynCall_vfi = createExportWrapper('dynCall_vfi', 3);
  dynCalls['fiiiif'] = dynCall_fiiiif = createExportWrapper('dynCall_fiiiif', 6);
  dynCalls['viififfii'] = dynCall_viififfii = createExportWrapper('dynCall_viififfii', 9);
  dynCalls['viiiiiiiiii'] = dynCall_viiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiii', 11);
  dynCalls['viiifii'] = dynCall_viiifii = createExportWrapper('dynCall_viiifii', 7);
  dynCalls['viiiiiiiiiiiiiiiiiiiiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiii', 32);
  dynCalls['viiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii', 50);
  dynCalls['viiiiiiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiiiiiii', 18);
  dynCalls['viffifiiiii'] = dynCall_viffifiiiii = createExportWrapper('dynCall_viffifiiiii', 11);
  dynCalls['vffffifiiii'] = dynCall_vffffifiiii = createExportWrapper('dynCall_vffffifiiii', 11);
  dynCalls['viifffffffiifii'] = dynCall_viifffffffiifii = createExportWrapper('dynCall_viifffffffiifii', 15);
  dynCalls['vifffffiiiifii'] = dynCall_vifffffiiiifii = createExportWrapper('dynCall_vifffffiiiifii', 14);
  dynCalls['vfffiiifiiiiiii'] = dynCall_vfffiiifiiiiiii = createExportWrapper('dynCall_vfffiiifiiiiiii', 15);
  dynCalls['iiffffiii'] = dynCall_iiffffiii = createExportWrapper('dynCall_iiffffiii', 9);
  dynCalls['vfffiiiiiiiiii'] = dynCall_vfffiiiiiiiiii = createExportWrapper('dynCall_vfffiiiiiiiiii', 14);
  dynCalls['iiiffffii'] = dynCall_iiiffffii = createExportWrapper('dynCall_iiiffffii', 9);
  dynCalls['ifffiii'] = dynCall_ifffiii = createExportWrapper('dynCall_ifffiii', 7);
  dynCalls['viiiiiiffi'] = dynCall_viiiiiiffi = createExportWrapper('dynCall_viiiiiiffi', 10);
  dynCalls['viiiiiiiiff'] = dynCall_viiiiiiiiff = createExportWrapper('dynCall_viiiiiiiiff', 11);
  dynCalls['viiiiiiiiiiiiiiiffi'] = dynCall_viiiiiiiiiiiiiiiffi = createExportWrapper('dynCall_viiiiiiiiiiiiiiiffi', 19);
  dynCalls['viiiiififiiiiiiii'] = dynCall_viiiiififiiiiiiii = createExportWrapper('dynCall_viiiiififiiiiiiii', 17);
  dynCalls['viiiiiiiiiii'] = dynCall_viiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiii', 12);
  dynCalls['vfiiii'] = dynCall_vfiiii = createExportWrapper('dynCall_vfiiii', 6);
  dynCalls['iiiiifiiiii'] = dynCall_iiiiifiiiii = createExportWrapper('dynCall_iiiiifiiiii', 11);
  dynCalls['viiifiii'] = dynCall_viiifiii = createExportWrapper('dynCall_viiifiii', 8);
  dynCalls['ifffii'] = dynCall_ifffii = createExportWrapper('dynCall_ifffii', 6);
  dynCalls['iiiiffi'] = dynCall_iiiiffi = createExportWrapper('dynCall_iiiiffi', 7);
  dynCalls['fiiffff'] = dynCall_fiiffff = createExportWrapper('dynCall_fiiffff', 7);
  dynCalls['vfffiiiff'] = dynCall_vfffiiiff = createExportWrapper('dynCall_vfffiiiff', 9);
  dynCalls['iifiiiiii'] = dynCall_iifiiiiii = createExportWrapper('dynCall_iifiiiiii', 9);
  dynCalls['iiifiiffiiiiii'] = dynCall_iiifiiffiiiiii = createExportWrapper('dynCall_iiifiiffiiiiii', 14);
  dynCalls['viffii'] = dynCall_viffii = createExportWrapper('dynCall_viffii', 6);
  dynCalls['viffiiii'] = dynCall_viffiiii = createExportWrapper('dynCall_viffiiii', 8);
  dynCalls['iiiiif'] = dynCall_iiiiif = createExportWrapper('dynCall_iiiiif', 6);
  dynCalls['iiiiffiffiiiifffiii'] = dynCall_iiiiffiffiiiifffiii = createExportWrapper('dynCall_iiiiffiffiiiifffiii', 19);
  dynCalls['iiifiiififiiii'] = dynCall_iiifiiififiiii = createExportWrapper('dynCall_iiifiiififiiii', 14);
  dynCalls['iiiffff'] = dynCall_iiiffff = createExportWrapper('dynCall_iiiffff', 7);
  dynCalls['viiiffi'] = dynCall_viiiffi = createExportWrapper('dynCall_viiiffi', 7);
  dynCalls['vfffffiiiiifiiiiiifiiiiiiiiii'] = dynCall_vfffffiiiiifiiiiiifiiiiiiiiii = createExportWrapper('dynCall_vfffffiiiiifiiiiiifiiiiiiiiii', 29);
  dynCalls['vfffiffii'] = dynCall_vfffiffii = createExportWrapper('dynCall_vfffiffii', 9);
  dynCalls['iiiifffiiiiiiiiiii'] = dynCall_iiiifffiiiiiiiiiii = createExportWrapper('dynCall_iiiifffiiiiiiiiiii', 18);
  dynCalls['iiiifffiffffiiiiiiiii'] = dynCall_iiiifffiffffiiiiiiiii = createExportWrapper('dynCall_iiiifffiffffiiiiiiiii', 21);
  dynCalls['iiiiifffiffffiiiiiiiiii'] = dynCall_iiiiifffiffffiiiiiiiiii = createExportWrapper('dynCall_iiiiifffiffffiiiiiiiiii', 23);
  dynCalls['viiffiffffiiiiiiiii'] = dynCall_viiffiffffiiiiiiiii = createExportWrapper('dynCall_viiffiffffiiiiiiiii', 19);
  dynCalls['ifiiiiiiii'] = dynCall_ifiiiiiiii = createExportWrapper('dynCall_ifiiiiiiii', 10);
  dynCalls['iiiiiffifiiiiiii'] = dynCall_iiiiiffifiiiiiii = createExportWrapper('dynCall_iiiiiffifiiiiiii', 16);
  dynCalls['viiiiffiii'] = dynCall_viiiiffiii = createExportWrapper('dynCall_viiiiffiii', 10);
  dynCalls['viffiiiiii'] = dynCall_viffiiiiii = createExportWrapper('dynCall_viffiiiiii', 10);
  dynCalls['iifiii'] = dynCall_iifiii = createExportWrapper('dynCall_iifiii', 6);
  dynCalls['vifffii'] = dynCall_vifffii = createExportWrapper('dynCall_vifffii', 7);
  dynCalls['viiiiiifiiiiiiiiii'] = dynCall_viiiiiifiiiiiiiiii = createExportWrapper('dynCall_viiiiiifiiiiiiiiii', 18);
  dynCalls['viiiiiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiiiiii', 17);
  dynCalls['iiiiifiiiiiiiii'] = dynCall_iiiiifiiiiiiiii = createExportWrapper('dynCall_iiiiifiiiiiiiii', 15);
  dynCalls['iiiiiiifffffiiiiiiiiiifiiiii'] = dynCall_iiiiiiifffffiiiiiiiiiifiiiii = createExportWrapper('dynCall_iiiiiiifffffiiiiiiiiiifiiiii', 28);
  dynCalls['iiiiiifiiiiifiiiiii'] = dynCall_iiiiiifiiiiifiiiiii = createExportWrapper('dynCall_iiiiiifiiiiifiiiiii', 19);
  dynCalls['iiif'] = dynCall_iiif = createExportWrapper('dynCall_iiif', 4);
  dynCalls['viffffiii'] = dynCall_viffffiii = createExportWrapper('dynCall_viffffiii', 9);
  dynCalls['viiffiifiiii'] = dynCall_viiffiifiiii = createExportWrapper('dynCall_viiffiifiiii', 12);
  dynCalls['iiiiiiiiiiiiiiiiiiiiffiii'] = dynCall_iiiiiiiiiiiiiiiiiiiiffiii = createExportWrapper('dynCall_iiiiiiiiiiiiiiiiiiiiffiii', 25);
  dynCalls['vifffiiii'] = dynCall_vifffiiii = createExportWrapper('dynCall_vifffiiii', 9);
  dynCalls['iiiifiii'] = dynCall_iiiifiii = createExportWrapper('dynCall_iiiifiii', 8);
  dynCalls['iiiiiiifi'] = dynCall_iiiiiiifi = createExportWrapper('dynCall_iiiiiiifi', 9);
  dynCalls['iiifff'] = dynCall_iiifff = createExportWrapper('dynCall_iiifff', 6);
  dynCalls['vifffffff'] = dynCall_vifffffff = createExportWrapper('dynCall_vifffffff', 9);
  dynCalls['iijjii'] = dynCall_iijjii = createExportWrapper('dynCall_iijjii', 6);
  dynCalls['j'] = dynCall_j = createExportWrapper('dynCall_j', 1);
  dynCalls['ifff'] = dynCall_ifff = createExportWrapper('dynCall_ifff', 4);
  dynCalls['vifiiii'] = dynCall_vifiiii = createExportWrapper('dynCall_vifiiii', 7);
  dynCalls['viiiiiiiiiiii'] = dynCall_viiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiii', 13);
  dynCalls['viiiiiifffffffffffii'] = dynCall_viiiiiifffffffffffii = createExportWrapper('dynCall_viiiiiifffffffffffii', 20);
  dynCalls['viiffffffff'] = dynCall_viiffffffff = createExportWrapper('dynCall_viiffffffff', 11);
  dynCalls['viiiiiiiiiiiii'] = dynCall_viiiiiiiiiiiii = createExportWrapper('dynCall_viiiiiiiiiiiii', 14);
  dynCalls['iiiifffifii'] = dynCall_iiiifffifii = createExportWrapper('dynCall_iiiifffifii', 11);
  dynCalls['viifffi'] = dynCall_viifffi = createExportWrapper('dynCall_viifffi', 7);
  dynCalls['iiiiifiiiiii'] = dynCall_iiiiifiiiiii = createExportWrapper('dynCall_iiiiifiiiiii', 12);
  dynCalls['viiiiiffi'] = dynCall_viiiiiffi = createExportWrapper('dynCall_viiiiiffi', 9);
  dynCalls['viiiiffi'] = dynCall_viiiiffi = createExportWrapper('dynCall_viiiiffi', 8);
  dynCalls['viffi'] = dynCall_viffi = createExportWrapper('dynCall_viffi', 5);
  dynCalls['iiffiiiiiffi'] = dynCall_iiffiiiiiffi = createExportWrapper('dynCall_iiffiiiiiffi', 12);
  dynCalls['iffiiii'] = dynCall_iffiiii = createExportWrapper('dynCall_iffiiii', 7);
  dynCalls['iiifi'] = dynCall_iiifi = createExportWrapper('dynCall_iiifi', 5);
  dynCalls['viifffffffff'] = dynCall_viifffffffff = createExportWrapper('dynCall_viifffffffff', 12);
  dynCalls['vififff'] = dynCall_vififff = createExportWrapper('dynCall_vififff', 7);
  dynCalls['fiif'] = dynCall_fiif = createExportWrapper('dynCall_fiif', 4);
  dynCalls['fiifi'] = dynCall_fiifi = createExportWrapper('dynCall_fiifi', 5);
  dynCalls['fiffif'] = dynCall_fiffif = createExportWrapper('dynCall_fiffif', 6);
  dynCalls['fifiiiiiiii'] = dynCall_fifiiiiiiii = createExportWrapper('dynCall_fifiiiiiiii', 11);
  dynCalls['iiffii'] = dynCall_iiffii = createExportWrapper('dynCall_iiffii', 6);
  dynCalls['iiffif'] = dynCall_iiffif = createExportWrapper('dynCall_iiffif', 6);
  dynCalls['iiffiii'] = dynCall_iiffiii = createExportWrapper('dynCall_iiffiii', 7);
  dynCalls['iiffffffifiiiiii'] = dynCall_iiffffffifiiiiii = createExportWrapper('dynCall_iiffffffifiiiiii', 16);
  dynCalls['ffffff'] = dynCall_ffffff = createExportWrapper('dynCall_ffffff', 6);
  dynCalls['iif'] = dynCall_iif = createExportWrapper('dynCall_iif', 3);
  dynCalls['vffff'] = dynCall_vffff = createExportWrapper('dynCall_vffff', 5);
  dynCalls['ifffiiiif'] = dynCall_ifffiiiif = createExportWrapper('dynCall_ifffiiiif', 9);
  dynCalls['iiifffiiii'] = dynCall_iiifffiiii = createExportWrapper('dynCall_iiifffiiii', 10);
  dynCalls['iiiff'] = dynCall_iiiff = createExportWrapper('dynCall_iiiff', 5);
  dynCalls['iiiffffiiiiii'] = dynCall_iiiffffiiiiii = createExportWrapper('dynCall_iiiffffiiiiii', 13);
  dynCalls['viiij'] = dynCall_viiij = createExportWrapper('dynCall_viiij', 5);
  dynCalls['iifff'] = dynCall_iifff = createExportWrapper('dynCall_iifff', 5);
  dynCalls['iffiii'] = dynCall_iffiii = createExportWrapper('dynCall_iffiii', 6);
  dynCalls['iifffiii'] = dynCall_iifffiii = createExportWrapper('dynCall_iifffiii', 8);
  dynCalls['iiffffff'] = dynCall_iiffffff = createExportWrapper('dynCall_iiffffff', 8);
  dynCalls['iiiffffff'] = dynCall_iiiffffff = createExportWrapper('dynCall_iiiffffff', 9);
  dynCalls['vfiii'] = dynCall_vfiii = createExportWrapper('dynCall_vfiii', 5);
  dynCalls['iffii'] = dynCall_iffii = createExportWrapper('dynCall_iffii', 5);
  dynCalls['iiiifiiiiiiii'] = dynCall_iiiifiiiiiiii = createExportWrapper('dynCall_iiiifiiiiiiii', 13);
  dynCalls['iiiiifiiiiiiii'] = dynCall_iiiiifiiiiiiii = createExportWrapper('dynCall_iiiiifiiiiiiii', 14);
  dynCalls['iiifif'] = dynCall_iiifif = createExportWrapper('dynCall_iiifif', 6);
  dynCalls['vffi'] = dynCall_vffi = createExportWrapper('dynCall_vffi', 4);
  dynCalls['vijj'] = dynCall_vijj = createExportWrapper('dynCall_vijj', 4);
  dynCalls['vj'] = dynCall_vj = createExportWrapper('dynCall_vj', 2);
  dynCalls['ji'] = dynCall_ji = createExportWrapper('dynCall_ji', 2);
  dynCalls['jjj'] = dynCall_jjj = createExportWrapper('dynCall_jjj', 3);
  dynCalls['viiji'] = dynCall_viiji = createExportWrapper('dynCall_viiji', 5);
  dynCalls['viifiiiifii'] = dynCall_viifiiiifii = createExportWrapper('dynCall_viifiiiifii', 11);
  dynCalls['iffffff'] = dynCall_iffffff = createExportWrapper('dynCall_iffffff', 7);
  dynCalls['iiiifff'] = dynCall_iiiifff = createExportWrapper('dynCall_iiiifff', 7);
  dynCalls['iffffffiiiiiiiif'] = dynCall_iffffffiiiiiiiif = createExportWrapper('dynCall_iffffffiiiiiiiif', 16);
  dynCalls['iiiffffi'] = dynCall_iiiffffi = createExportWrapper('dynCall_iiiffffi', 8);
  dynCalls['viiiiifiiiii'] = dynCall_viiiiifiiiii = createExportWrapper('dynCall_viiiiifiiiii', 12);
  dynCalls['viiffff'] = dynCall_viiffff = createExportWrapper('dynCall_viiffff', 7);
  dynCalls['vdi'] = dynCall_vdi = createExportWrapper('dynCall_vdi', 3);
  dynCalls['vd'] = dynCall_vd = createExportWrapper('dynCall_vd', 2);
  dynCalls['dd'] = dynCall_dd = createExportWrapper('dynCall_dd', 2);
  dynCalls['vfffffffi'] = dynCall_vfffffffi = createExportWrapper('dynCall_vfffffffi', 9);
  dynCalls['d'] = dynCall_d = createExportWrapper('dynCall_d', 1);
  dynCalls['jiji'] = dynCall_jiji = createExportWrapper('dynCall_jiji', 4);
  dynCalls['iidiiii'] = dynCall_iidiiii = createExportWrapper('dynCall_iidiiii', 7);
  _asyncify_start_unwind = createExportWrapper('asyncify_start_unwind', 1);
  _asyncify_stop_unwind = createExportWrapper('asyncify_stop_unwind', 0);
  _asyncify_start_rewind = createExportWrapper('asyncify_start_rewind', 1);
  _asyncify_stop_rewind = createExportWrapper('asyncify_stop_rewind', 0);
}
var wasmImports = {
  /** @export */
  __photo_move_field,
  /** @export */
  __port_flag_hex_js,
  /** @export */
  __port_flag_js,
  /** @export */
  __port_js_stack,
  /** @export */
  __port_net_det_js,
  /** @export */
  __port_p205_goto_char,
  /** @export */
  __port_p240_start,
  /** @export */
  __port_p240_steer,
  /** @export */
  __port_p352_hang_char,
  /** @export */
  __port_padf_char,
  /** @export */
  __port_padrec_push,
  /** @export */
  _abort_js: __abort_js,
  /** @export */
  emscripten_asm_const_int: _emscripten_asm_const_int,
  /** @export */
  emscripten_fiber_swap: _emscripten_fiber_swap,
  /** @export */
  emscripten_get_now: _emscripten_get_now,
  /** @export */
  emscripten_resize_heap: _emscripten_resize_heap,
  /** @export */
  emscripten_set_main_loop: _emscripten_set_main_loop,
  /** @export */
  emscripten_set_main_loop_timing: _emscripten_set_main_loop_timing,
  /** @export */
  emscripten_webgl_make_context_current: _emscripten_webgl_make_context_current,
  /** @export */
  fd_close: _fd_close,
  /** @export */
  fd_seek: _fd_seek,
  /** @export */
  fd_write: _fd_write,
  /** @export */
  glActiveTexture: _glActiveTexture,
  /** @export */
  glAttachShader: _glAttachShader,
  /** @export */
  glBindAttribLocation: _glBindAttribLocation,
  /** @export */
  glBindBuffer: _glBindBuffer,
  /** @export */
  glBindFramebuffer: _glBindFramebuffer,
  /** @export */
  glBindTexture: _glBindTexture,
  /** @export */
  glBindVertexArray: _glBindVertexArray,
  /** @export */
  glBlendFunc: _glBlendFunc,
  /** @export */
  glBlitFramebuffer: _glBlitFramebuffer,
  /** @export */
  glBufferData: _glBufferData,
  /** @export */
  glClear: _glClear,
  /** @export */
  glClearColor: _glClearColor,
  /** @export */
  glColorMask: _glColorMask,
  /** @export */
  glCompileShader: _glCompileShader,
  /** @export */
  glCopyTexSubImage2D: _glCopyTexSubImage2D,
  /** @export */
  glCreateProgram: _glCreateProgram,
  /** @export */
  glCreateShader: _glCreateShader,
  /** @export */
  glDepthFunc: _glDepthFunc,
  /** @export */
  glDepthMask: _glDepthMask,
  /** @export */
  glDisable: _glDisable,
  /** @export */
  glDrawArrays: _glDrawArrays,
  /** @export */
  glEnable: _glEnable,
  /** @export */
  glEnableVertexAttribArray: _glEnableVertexAttribArray,
  /** @export */
  glFinish: _glFinish,
  /** @export */
  glFramebufferTexture2D: _glFramebufferTexture2D,
  /** @export */
  glGenBuffers: _glGenBuffers,
  /** @export */
  glGenFramebuffers: _glGenFramebuffers,
  /** @export */
  glGenTextures: _glGenTextures,
  /** @export */
  glGenVertexArrays: _glGenVertexArrays,
  /** @export */
  glGetError: _glGetError,
  /** @export */
  glGetIntegerv: _glGetIntegerv,
  /** @export */
  glGetProgramiv: _glGetProgramiv,
  /** @export */
  glGetShaderInfoLog: _glGetShaderInfoLog,
  /** @export */
  glGetShaderiv: _glGetShaderiv,
  /** @export */
  glGetString: _glGetString,
  /** @export */
  glGetUniformLocation: _glGetUniformLocation,
  /** @export */
  glLinkProgram: _glLinkProgram,
  /** @export */
  glPolygonOffset: _glPolygonOffset,
  /** @export */
  glReadPixels: _glReadPixels,
  /** @export */
  glScissor: _glScissor,
  /** @export */
  glShaderSource: _glShaderSource,
  /** @export */
  glTexImage2D: _glTexImage2D,
  /** @export */
  glTexParameteri: _glTexParameteri,
  /** @export */
  glUniform1f: _glUniform1f,
  /** @export */
  glUniform1i: _glUniform1i,
  /** @export */
  glUniform2f: _glUniform2f,
  /** @export */
  glUniform4f: _glUniform4f,
  /** @export */
  glUniform4i: _glUniform4i,
  /** @export */
  glUseProgram: _glUseProgram,
  /** @export */
  glVertexAttribPointer: _glVertexAttribPointer,
  /** @export */
  glViewport: _glViewport,
  /** @export */
  port_rtw_gl_create: _port_rtw_gl_create,
  /** @export */
  port_rtw_gl_ready: _port_rtw_gl_ready,
  /** @export */
  port_rtw_glue_option: _port_rtw_glue_option,
  /** @export */
  port_rtw_glue_pause: _port_rtw_glue_pause,
  /** @export */
  port_rtw_glue_resize: _port_rtw_glue_resize,
  /** @export */
  port_rtw_glue_start: _port_rtw_glue_start,
  /** @export */
  rtw_build_id: _rtw_build_id,
  /** @export */
  rtw_export_file: _rtw_export_file,
  /** @export */
  rtw_log: _rtw_log,
  /** @export */
  rtw_pointer_lock: _rtw_pointer_lock,
  /** @export */
  rtw_rumble: _rtw_rumble
};


// include: postamble.js
// === Auto-generated postamble setup entry stuff ===

var calledRun;

function callMain() {
  assert(typeof onPreRuns === 'undefined' || onPreRuns.length == 0, 'cannot call main when preRun functions remain to be called');

  var entryFunction = _main;

  var argc = 0;
  var argv = 0;

  try {

    var ret = entryFunction(argc, argv);

    // if we're not running an evented main loop, it's time to exit
    exitJS(ret, /* implicit = */ true);
    return ret;
  } catch (e) {
    return handleException(e);
  }
}

function run() {

  preRun();

  function doRun() {
    // run may have just been called through dependencies being fulfilled just in this very frame,
    // or while the async setStatus time below was happening
    assert(!calledRun);
    calledRun = true;
    Module['calledRun'] = true;

    if (ABORT) return;

    initRuntime();

    preMain();

    readyPromiseResolve?.(Module);
    Module['onRuntimeInitialized']?.();
    consumedModuleProp('onRuntimeInitialized');

    var noInitialRun = Module['noInitialRun'] || true;
    if (!noInitialRun) callMain();

    postRun();
  }

  if (Module['setStatus']) {
    Module['setStatus']('Running...');
    setTimeout(() => {
      setTimeout(() => Module['setStatus'](''), 1);
      doRun();
    }, 1);
  } else
  {
    doRun();
  }
}

function checkUnflushedContent() {
  // Compiler settings do not allow exiting the runtime, so flushing
  // the streams is not possible. but in ASSERTIONS mode we check
  // if there was something to flush, and if so tell the user they
  // should request that the runtime be exitable.
  // Normally we would not even include flush() at all, but in ASSERTIONS
  // builds we do so just for this check, and here we see if there is any
  // content to flush, that is, we check if there would have been
  // something a non-ASSERTIONS build would have not seen.
  // How we flush the streams depends on whether we are in SYSCALLS_REQUIRE_FILESYSTEM=0
  // mode (which has its own special function for this; otherwise, all
  // the code is inside libc)
  var oldOut = out;
  var oldErr = err;
  var has = false;
  out = err = (x) => {
    has = true;
  }
  try { // it doesn't matter if it fails
    flush_NO_FILESYSTEM();
  } catch(e) {}
  out = oldOut;
  err = oldErr;
  if (has) {
    warnOnce('stdio streams had content in them that was not flushed. you should set EXIT_RUNTIME to 1 (see the Emscripten FAQ), or make sure to emit a newline when you printf etc.');
    warnOnce('(this may also be due to not including full filesystem support - try building with -sFORCE_FILESYSTEM)');
  }
}

var wasmExports;

// In modularize mode the generated code is within a factory function so we
// can use await here (since it's not top-level-await).
wasmExports = await (createWasm());

run();

// end include: postamble.js

// include: postamble_modularize.js
// In MODULARIZE mode we wrap the generated code in a factory function
// and return either the Module itself, or a promise of the module.
//
// We assign to the `moduleRtn` global here and configure closure to see
// this as and extern so it won't get minified.

if (runtimeInitialized)  {
  moduleRtn = Module;
} else {
  // Set up the promise that indicates the Module is initialized
  moduleRtn = new Promise((resolve, reject) => {
    readyPromiseResolve = resolve;
    readyPromiseReject = reject;
  });
}

// Assertion for attempting to access module properties on the incoming
// moduleArg.  In the past we used this object as the prototype of the module
// and assigned properties to it, but now we return a distinct object.  This
// keeps the instance private until it is ready (i.e the promise has been
// resolved).
for (const prop of Object.keys(Module)) {
  if (!(prop in moduleArg)) {
    Object.defineProperty(moduleArg, prop, {
      configurable: true,
      get() {
        abort(`Access to module property ('${prop}') is no longer possible via the module constructor argument; Instead, use the result of the module constructor.`)
      }
    });
  }
}
// end include: postamble_modularize.js



  return moduleRtn;
}

// Export using a UMD style export, or ES6 exports if selected
if (typeof exports === 'object' && typeof module === 'object') {
  module.exports = createConker;
  // This default export looks redundant, but it allows TS to import this
  // commonjs style module.
  module.exports.default = createConker;
} else if (typeof define === 'function' && define['amd'])
  define([], () => createConker);

