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
//   - P377: the page's overlays (customisation settings, autosave icon, hold-L ring, photo HUD and Pose & Outfit panel)
//     are drawn in the worker by rtw_overlay.js (object rtwOverlay); this tick hands it pad 1 first (rtwOverlay.input).
//   - P378 standard 1.1: the right analog stick (rtw_rstick, option 113) is the free camera's stick / photo mode's look
//     stick as in main.js gamepadPad (the host still sets the C buttons from it; those stay C buttons elsewhere); the
//     mouse wheel (rtw_wheel, option 114) zooms in photo mode as main.js's canvas wheel and moves the customisation
//     settings' rows as gmenu.js's.
// Left out (no host interface in retrowser v1): online play (net.js, W11), recording replays (no way to hand a file to
// the game).
var rtwGlue = (function () {
  'use strict';
  const N64 = { A: 0x8000, B: 0x4000, Z: 0x2000, START: 0x1000, DU: 0x0800, DD: 0x0400, DL: 0x0200, DR: 0x0100,
    L: 0x0020, R: 0x0010, CU: 0x0008, CD: 0x0004, CL: 0x0002, CR: 0x0001 };
  const C_BITS = N64.CU | N64.CD | N64.CL | N64.CR;
  // controls.extra in retrowser.json (bits 16..31 of rtw_input's buttons)
  const EXTRA = { PHOTO: 1 << 16, CAMZOOM: 1 << 17, CAMBACK: 1 << 18, HALF: 1 << 19, RECSAVE: 1 << 20, MENU: 1 << 21 };   // P377: MENU
  // rtw_option ids: the game options are the PORT_OPT_* ids (port/ultra/port_options.h, main.js `game:`), the
  // page-side ones start at 100 (pc_rtw.c RTW_PAGE_OPT_BASE)
  const OPT = { FREECAM: 15, PHOTOMODE: 16, HIRES2D: 100, SMOOTHFONT: 101, WIDESCREEN: 102, FULLRES: 103, HFR: 104,
    TOGGLECROUCH: 105, TOGGLERLOOK: 106, TOGGLEWALK: 107, RECORDER: 108, RSTICK: 113, WHEEL: 114 };   // P378: RSTICK, WHEEL
  // main.js OPTIONS keys of the game options, for the recording's header (e2e_replay.js applies them by key)
  const GAME_OPTION_KEYS = { 0: 'skipcut', 1: 'skipintro', 2: 'healthhud', 3: 'cashhud', 4: 'longbreath', 5: 'longspin',
    17: 'ledgegrab', 6: 'nodrunk', 7: 'conkerlod', 8: 'airbar', 13: 'rumble', 14: 'crosshair', 15: 'freecam',
    16: 'photomode', 12: 'swiminvert', 9: 'volmusic', 10: 'volsfx', 11: 'volspeech' };
  const RANGE_OPTIONS = new Set([9, 10, 11]);
  const PAGE_OPTION_KEYS = { 100: 'hires2d', 101: 'smoothfont', 102: 'widescreen', 103: 'fullres', 104: 'hfr',
    105: 'togglecrouch', 106: 'togglerlook', 107: 'togglewalk' };
  const STICK = 80;   // typical full deflection of an N64 stick (main.js)

  const optionValues = {};   // id -> value the game uses (the host's, or one chosen in the customisation settings: rtwOverlay.hostOption)
  const GAME_OPTION_COUNT = 18;   // PORT_OPT_COUNT (port/ultra/port_options.h): ids below it are game options
  const opt = (id) => optionValues[id] | 0;
  const view = { width: 640, height: 480, dpr100: 100 };
  let started = false, glUp = false, hostPaused = false, pointerLocked = false, gameOptionsLocked = false;

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
  // P378 standard 1.1 right stick (rtw_rstick, option 113): main.js gamepadPad's analog right stick (radial dead zone 0.2,
  // rescaled, 80 counts at full) -> [rx, ry] in N64 counts, y up. [0, 0] with the option off (v1: C buttons only).
  function rightStick(rawRx, rawRy) {
    if (!opt(OPT.RSTICK)) return [0, 0];
    let x = Math.max(-1, Math.min(1, rawRx / 127)), y = Math.max(-1, Math.min(1, rawRy / 127));
    const m = Math.hypot(x, y);
    if (m < 0.2) return [0, 0];
    const k = Math.min(1, (m - 0.2) / 0.8) / m;
    return [Math.round(x * k * STICK), Math.round(y * k * STICK)];
  }
  // the C buttons the host made from that stick (its axis past 0.5, i.e. |raw| >= 63 after its rounding): they are the
  // stick's, not a key's or a face button's, so the analog stick stands in for them where main.js uses it
  function rightStickCBits(rawRx, rawRy) {
    if (!opt(OPT.RSTICK)) return 0;
    return (rawRx >= 63 ? N64.CR : 0) | (rawRx <= -63 ? N64.CL : 0) | (rawRy >= 63 ? N64.CU : 0) | (rawRy <= -63 ? N64.CD : 0);
  }
  const photoModeOn = () => !!opt(OPT.PHOTOMODE) && !rec.active;
  // one host pad (rtw_input: active-high N64 bits, extras in bits 16.., stick -127..127, up positive; P378 rtw_rstick:
  // rawRx / rawRy) -> main.js's pad object (P378: rx / ry = main.js `look`, photo mode's analog look stick)
  function hostPad(buttons, sx, sy, rawRx, rawRy) {
    let b = buttons & 0xFFFF;
    let [x, y] = octagon(Math.max(-1, Math.min(1, sx / 127)), Math.max(-1, Math.min(1, sy / 127)));
    const half = (buttons & EXTRA.HALF) !== 0;
    if (half && !opt(OPT.TOGGLEWALK)) { x = Math.round(x / 2); y = Math.round(y / 2); }   // latched: see applyLatches
    let cx = 0, cy = 0;
    const [rx, ry] = rightStick(rawRx | 0, rawRy | 0);   // P378
    if (freeCameraOn()) {   // P347: the C buttons (the host's right stick or C keys) become the camera stick
      const keyC = b & ~rightStickCBits(rawRx | 0, rawRy | 0);   // P378: C keys / buttons; the analog stick wins (main.js k.cx || g.cx)
      cx = rx || ((keyC & N64.CR) ? STICK : 0) - ((keyC & N64.CL) ? STICK : 0);
      cy = ry || ((keyC & N64.CU) ? STICK : 0) - ((keyC & N64.CD) ? STICK : 0);
      b = (b & ~C_BITS) | ((buttons & EXTRA.CAMZOOM) ? N64.CU : 0) | ((buttons & EXTRA.CAMBACK) ? N64.CD : 0);
    }
    return { b, x, y, half, cx, cy, rx, ry, photo: (buttons & EXTRA.PHOTO) !== 0, recSave: (buttons & EXTRA.RECSAVE) !== 0, menu: (buttons & EXTRA.MENU) !== 0 };
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
  function inputTick() {   // P377 name (was tick)
    scheduleTick();
    if (!started || hostPaused) return;
    const now = performance.now(), raw = wasm('port_rtw_raw_state')() >> 2;
    // pad 1 = the host's port 0 (keyboard, touch and the first gamepad); ports 1-3 count as plugged in while the host
    // keeps sending them (further gamepads)
    const pads = [null, null, null, null];
    for (let i = 0; i < 4; i++) {
      const calls = HEAP32[raw + i * 4];
      if (calls !== portCalls[i]) { portCalls[i] = calls; portSeenAt[i] = now; }
      if (i === 0 || (portSeenAt[i] && now - portSeenAt[i] < 1000)) pads[i] = hostPad(HEAP32[raw + i * 4 + 1], HEAP32[raw + i * 4 + 2], HEAP32[raw + i * 4 + 3],
        HEAP32[raw + 20 + i * 2], HEAP32[raw + 21 + i * 2]);   // P378: rtw_rstick (pc_rtw.c RTW_RAW_RSTICK)
    }
    const mouseDx = HEAP32[raw + 16], mouseDy = HEAP32[raw + 17];
    HEAP32[raw + 16] = 0; HEAP32[raw + 17] = 0;
    const wheel = opt(OPT.WHEEL) ? HEAP32[raw + 28] : 0;   // P378 rtw_wheel (pc_rtw.c RTW_RAW_WHEEL), 1/100 notch
    HEAP32[raw + 28] = 0;
    let pad1 = pads[0];   // P377 name (was p0)
    if (pad1.recSave && !recSavePrev) recStop('the Save recording button');
    recSavePrev = pad1.recSave;
    // P377: the customisation settings have pad 1 while open (the game, and a recording, get an idle pad)
    const menuHasPad = rtwOverlay.input(pad1, now);
    if (menuHasPad) pads[0] = pad1 = { b: 0, x: 0, y: 0, half: false, cx: 0, cy: 0, rx: 0, ry: 0, photo: false, recSave: false, menu: false };
    if (photo.state === 2) { photo.mx += mouseDx; photo.my += mouseDy; }   // P348 photo camera
    if (wheel && !rtwOverlay.wheel(wheel) && photo.state === 2) photo.wheel += wheel;   // P378: a menu's rows, else photo zoom
    const photoHasInput = photoPoll(pad1);
    const wantLock = freeCameraOn() || photo.state === 2;
    if (wantLock !== pointerLocked) { pointerLocked = wantLock; wasm('port_rtw_set_pointer_lock')(wantLock ? 1 : 0); }
    wasm('port_gfx_hfr_vsync')();
    if (photoHasInput) return;   // P348: photo mode takes pad 1's input
    if (!menuHasPad) photoMaskAfter(pad1);   // P377: not on the idle pad of the tick a menu closed in (its mask would end there)
    applyLatches(pad1);
    if (rec.active) { recSetPad(pad1); return; }   // P357: the recorded pad (pc_net.c samples it at the next retrace)
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
  function scheduleTick() { tickQueued = true; raf(() => { tickQueued = false; inputTick(); }); }

  // ------------------------------------------------------------------ photo mode (main.js photoPoll / photoCapture, P348)
  const photo = { state: 0, prevB: 0, prevKey: false, hud: false, mx: 0, my: 0, wheel: 0, last: 0, busy: false, asked: 0,   // P378 wheel
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
    if (st === 2 && was !== 2) { photo.hud = false; photo.mx = photo.my = photo.wheel = 0; photo.prevB = d.b; photo.last = now; log('[photo] on'); rtwOverlay.photoShown(true); }
    if (st !== 2 && was === 2) { photo.maskB = d.b; photo.maskStick = true; log('[photo] off'); rtwOverlay.photoShown(false); }
    if (st < 0 && photo.asked) { log(`[photo] not started: ${PHOTO_WHY[-st] || 'photo mode did not start'}`); photo.asked = 0; }
    if (st === 2) photo.asked = 0;
    if (st !== 2) return st === 1 || st === 3;
    const dt = Math.min(0.1, (now - photo.last) / 1000);
    let heldButtons = d.b, newButtons = heldButtons & ~photo.prevB;   // P377 names (were b, fresh)
    photo.last = now; photo.prevB = heldButtons;
    const panel = rtwOverlay.photoTick(dt, d, newButtons);   // P377 (main.js lookTick): the Pose & Outfit panel's bits, not the camera's
    heldButtons &= ~panel; newButtons &= ~panel;
    if (newButtons & N64.START) { photoRequest(false); return true; }
    if (newButtons & N64.A) photoCapture();
    let flags = 0;
    if ((newButtons & N64.B) || photo.viewReq) flags |= 2;   // back to the game's view (P377 viewReq: GPhoto's footer)
    photo.viewReq = false;
    if (newButtons & N64.L) photo.hud = !photo.hud;
    if (photo.hud) flags |= 1;
    // look: the free camera's stick (C buttons with that option), else the analog right stick (P378, main.js d.rx), else
    // the C buttons
    const lx = d.cx || d.rx || ((heldButtons & N64.CR) ? STICK : 0) - ((heldButtons & N64.CL) ? STICK : 0);
    const ly = d.cy || d.ry || ((heldButtons & N64.CU) ? STICK : 0) - ((heldButtons & N64.CD) ? STICK : 0);
    const fwd = d.y / STICK * 500 * dt, right = d.x / STICK * 500 * dt;
    const up = (((heldButtons & N64.R) ? 1 : 0) - ((heldButtons & N64.Z) ? 1 : 0)) * 350 * dt;
    const dyaw = lx / STICK * 90 * dt + photo.mx * 0.15, dpitch = ly / STICK * 60 * dt - photo.my * 0.15;
    const droll = (((heldButtons & N64.DR) ? 1 : 0) - ((heldButtons & N64.DL) ? 1 : 0)) * 45 * dt;
    const zoom = Math.exp((((heldButtons & N64.DD) ? 1 : 0) - ((heldButtons & N64.DU) ? 1 : 0)) * 0.9 * dt) * Math.pow(1.1, photo.wheel / 100);   // P378 wheel as main.js
    photo.mx = photo.my = photo.wheel = 0;
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
    wasm('port_rtw_overlay_restore')();   // P377: the photo menus are not in the picture (photo.busy keeps them off meanwhile)
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
    rtwOverlay.photoToast(r ? `the host refused the picture (${r})` : `saved ${name}`);
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
    wasm('port_rtw_lock_game_options')(); gameOptionsLocked = true;   // main.js optionsLocked: the game options stay fixed for the recording
    rtwOverlay.setRecording(true);   // P377: the customisation settings show them locked, no game rows, no menu sounds
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
  const glue = {
    start() {   // rtw_start, before main()
      loadExclusions();
      layout();
      if (opt(OPT.RECORDER)) {
        const romPtr = wasm('port_rtw_rom_ptr')(), romSize = wasm('port_rtw_rom_size')();
        if (romPtr && romSize) romForHash = HEAPU8.slice(romPtr, romPtr + romSize);
        recBegin();
      }
      rtwOverlay.attach(overlayApi);   // P377
      started = true;
      if (!tickQueued) scheduleTick();
      // test aid (tools/port/scripts/rtw_e2e.mjs reads the game's state from the worker); the worker is the sandbox's own
      globalThis.__rtwConker = { Module, photoState: () => photo.state, rec: () => ({ active: rec.active, frames: rec.frames, checks: rec.checks.length }),
        audioDrained: () => Module['_port_rtw_audio_drained']() >>> 0, saveGeneration: () => Module['_rtw_save_generation'](),
        overlay: () => rtwOverlay.state(), options: () => Object.assign({}, optionValues),   // P377
        cam: () => { const cp = wasm('port_cam_state')() >> 2; return Array.from(HEAP32.subarray(cp, cp + 16)); },   // P378: the camera sticks
        photoinfo: () => ({ state: photo.state, fov: +wasm('port_photo_info')(7).toFixed(3) }) };   // P378: photo camera's field of view
      log(`[rtw] started: options ${Object.entries(optionValues).map(([k, v]) => `${k}=${v}`).join(' ')}`);
    },
    beforeGl() { layout(); },   // the drawing buffer the renderer starts with (gfx_init reads the viewport)
    glReady() { glUp = true; layout(); },
    option(id, value) {   // rtw_option (pc_rtw.c already set the game options to the host's value)
      // P377: a value chosen in the customisation settings may win over the host's at start (rtwOverlay.hostOption)
      const effective = rtwOverlay.hostOption(id, value, started);
      if (effective !== value) {
        if (id < GAME_OPTION_COUNT && !gameOptionsLocked) wasm('port_set_option')(id, effective);
        log(`[settings] option ${id}: ${effective} (chosen in the customisation settings; the host sent ${value})`);
      }
      applyOption(id, effective);
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
      if (!on) rtwOverlay.hostResumed();   // P377: the customisation settings still hold the game
    },
    get glUp() { return glUp; },
  };
  // an option's value for the game and this glue (from the host, or from the customisation settings)
  function applyOption(id, value) {
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
  }
  // P377: what rtw_overlay.js may use of this glue
  const overlayApi = {
    log,
    value: (id, def) => (optionValues[id] !== undefined ? optionValues[id] : def),
    setOption(id, value) {   // a change in the customisation settings (MenuModel rows, presets)
      if (id < GAME_OPTION_COUNT) { if (gameOptionsLocked) return false; wasm('port_set_option')(id, value); }
      applyOption(id, value);
      return true;
    },
    started: () => started, hostPaused: () => hostPaused,
    photo, photoRequest: (on) => photoRequest(on), photoCapture: () => photoCapture(), photoBusy: () => photo.busy,
    maskHeld() { photo.maskB = 0xFFFF; photo.maskStick = true; },   // main.js GMenu close: held inputs wait for a release
    exportSave: () => exportFile('conker-eu.eep', 'application/octet-stream', eepromBytes()),
  };
  return glue;
})();
