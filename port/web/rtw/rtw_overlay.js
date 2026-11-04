// P377 retrowser.app build: the page's overlays drawn inside the worker (Emscripten --pre-js, only in the rtw build; the
// page build never loads these files). In the page build they are page elements over the game's canvas: the game-style
// menus ("customisation settings", gmenu.js GMenu, with the game's menu sounds GSound), the autosave icon and the hold-L
// ring (index.html SVGs + main.js), photo mode's HUD and Pose & Outfit panel (gmenu.js GPhoto). The worker has no page,
// so this layer draws them on its own OffscreenCanvas 2D, in the game's own font read from game memory (gmenu.js GameFont:
// the game decoded font 0 from the player's ROM at boot; nothing ROM-derived is shipped or stored), and gfx_f3dex2.c
// port_rtw_overlay_composite lays that canvas over the WebGL frame once per main-loop tick (pc_sched.c
// rtw_main_loop_tick, after the game drew; the game's own picture is put back before the next tick, so the game never
// reads the overlay back).
//
// One object, rtwOverlay, made of this file (the layer, the page-code stand-ins, the buttons, the tick) and one file per
// feature, each behind its manifest option (all on by default in this build, they are the game's normal UI here):
//   rtw_saveicon.js  109 Autosave icon (the page's option 'saveicon', P324)
//   rtw_ring.js      111 Hold-L skip ring (P321)
//   rtw_menu.js      110 Customisation settings: the menus, the game's CUSTOMISATION rows, the menu sounds, the
//                    settings record that keeps a change made there (see that file)
//   rtw_photo.js     112 Photo mode menus: the HUD and the Pose & Outfit panel (P358 / P366)
// port/tools/rtw_page_extract.py joins them (port/build/rtw/gen/rtw_overlay.js, the @RTW_FEATURES@ place below) and copies
// in the page code they reuse verbatim from port/web/main.js and gmenu.js (the @RTW_PAGE ...@ places): GameFont, GFace
// here; OPTIONS, PRESETS, MenuModel in rtw_menu.js; the photo name tables, `look`, GPhoto in rtw_photo.js. The small
// `document` / `window` / `requestAnimationFrame` stand-ins below give that code the one canvas it draws on (this layer)
// and swallow its page listeners (no pointer events in a worker: everything works with the host's buttons).
//
// Input: only rtw_input (N64 buttons + the manifest's controls.extra) through rtw_glue.js's tick, which hands pad 1 to
// rtwOverlay.input first. The buttons (below): the extra button "Menu" (bit 21) and the "Photo mode" button (bit 16,
// the gamepad's Back): while a feature uses them, a short press of Photo is photo mode on its release, holding it half a
// second is the menus' entry (the page's hold-Back), and Menu reports press / tap / hold.
var rtwOverlay = (function () {
  'use strict';
  const M = Module;
  const N64 = { A: 0x8000, B: 0x4000, Z: 0x2000, START: 0x1000, DU: 0x0800, DD: 0x0400, DL: 0x0200, DR: 0x0100,
    L: 0x0020, R: 0x0010, CU: 0x0008, CD: 0x0004, CL: 0x0002, CR: 0x0001 };
  const STICK = 80;
  const FEATURE = { SAVEICON: 109, MENUS: 110, RING: 111, PHOTOMENUS: 112 };
  let glue = null;   // rtw_glue.js's side (attach): option values, photo state / camera, the recorder, log, export
  const log = (s) => (glue ? glue.log(s) : out(String(s)));
  const featureOn = (id) => (glue ? glue.value(id, 1) : 1) !== 0;   // the four features default to on (retrowser.json)
  // the feature files' hooks (each an array, called in file order)
  const hooks = { attach: [], input: [], draw: [], hostResumed: [], wheel: [], state: {} };   // P378 wheel
  // rtw_menu.js: the menu sounds (silent without it), a host option's effective value (the host's without it)
  let snd = () => {};
  let hostOption = (id, value) => value;
  // rtw_photo.js: photo mode's menus (none without it)
  let photoTick = () => 0, photoShown = () => {}, photoToast = () => {};

  // ---------------------------------------------------------------- the layer (an OffscreenCanvas the size of the picture)
  const layer = { canvas: null, ctx: null, w: 0, h: 0 };
  function layerFit() {
    const c = M['canvas'], w = c ? c.width : 640, h = c ? c.height : 480;
    if (!layer.canvas) { layer.canvas = new OffscreenCanvas(w, h); layer.ctx = layer.canvas.getContext('2d'); }
    if (layer.canvas.width !== w || layer.canvas.height !== h) { layer.canvas.width = w; layer.canvas.height = h; }
    layer.w = w; layer.h = h;
  }
  // stand-ins for the page code: one canvas element (this layer), no page listeners, rAF = once per overlay tick
  const rafQueue = [];
  const requestAnimationFrame = (f) => { rafQueue.push(f); return rafQueue.length; };
  const layerElement = {
    hidden: true,
    get width() { return layer.w; }, set width(v) { /* the layer follows the picture */ },
    get height() { return layer.h; }, set height(v) { /* idem */ },
    getContext: () => layer.ctx,
    getBoundingClientRect: () => ({ left: 0, top: 0, width: layer.w, height: layer.h }),
    addEventListener() { /* no pointer in the worker */ },
  };
  const noClass = { add() {}, remove() {}, toggle() {}, contains: () => false };
  const document = { createElement: () => new OffscreenCanvas(1, 1), getElementById: () => layerElement, body: { classList: noClass } };
  const window = { addEventListener() {}, devicePixelRatio: 1 };
  const navigator = { getGamepads: () => [] };   // the host's pads arrive as rtw_input
  // the page's session flags: no online play and no ?netdet in this build; recCfg = the recorder runs
  const netCfg = null, NETDET = false;
  let recCfg = null, optionsLocked = false;
  // main.js photo mode, bound to rtw_glue.js's photo object / functions at attach()
  let photo = { state: 0, hud: false, viewReq: false };
  let photoRequest = () => {}, photoCapture = () => {};
  // main.js opt(key) over the glue's values: main.js OPTIONS key -> rtw_option id (retrowser.json; the game options are
  // PORT_OPT_*, the page-side ones 100..)
  const KEY_ID = { skipcut: 0, skipintro: 1, healthhud: 2, cashhud: 3, longbreath: 4, longspin: 5, nodrunk: 6, conkerlod: 7,
    airbar: 8, volmusic: 9, volsfx: 10, volspeech: 11, swiminvert: 12, rumble: 13, crosshair: 14, freecam: 15, photomode: 16,
    ledgegrab: 17, hires2d: 100, smoothfont: 101, widescreen: 102, fullres: 103, hfr: 104, togglecrouch: 105,
    togglerlook: 106, togglewalk: 107, recorder: 108, saveicon: 109 };
  const RANGE_IDS = new Set([9, 10, 11]);
  const opt = (key) => {
    const id = KEY_ID[key];
    if (id === undefined) return false;
    const v = glue ? glue.value(id, RANGE_IDS.has(id) ? 100 : 0) : 0;
    return RANGE_IDS.has(id) ? v : !!v;
  };

  // ---------------------------------------------------------------- page code (gmenu.js GameFont, GFace)
  /* @RTW_PAGE GameFont,GFace@ */

  // ---------------------------------------------------------------- the buttons (pad 1's extras, before the features)
  // d.photo: with a feature that uses the buttons on (`buttonsWanted`), the raw Photo button becomes a short press, one
  // frame on its release; d.photoHold: one frame when it has been held HOLD_MS. d.menuPress / d.menuTap / d.menuHold:
  // the Menu button's press, its release before HOLD_MS, one frame when held HOLD_MS.
  const HOLD_MS = 500;
  const btn = { menuPrev: false, menuAt: 0, menuHeld: false, photoPrev: false, photoAt: 0, photoHeld: false };
  let buttonsWanted = () => false;
  function buttons(d, now) {
    const menu = !!d.menu;
    d.menuPress = menu && !btn.menuPrev;
    if (d.menuPress) { btn.menuAt = now; btn.menuHeld = false; }
    d.menuHold = menu && !btn.menuHeld && now - btn.menuAt >= HOLD_MS;
    if (d.menuHold) btn.menuHeld = true;
    d.menuTap = !menu && btn.menuPrev && !btn.menuHeld;
    btn.menuPrev = menu;
    if (!buttonsWanted()) { btn.photoPrev = !!d.photo; return; }
    const raw = !!d.photo;
    if (raw && !btn.photoPrev) { btn.photoAt = now; btn.photoHeld = false; }
    d.photoHold = raw && !btn.photoHeld && now - btn.photoAt >= HOLD_MS;
    if (d.photoHold) btn.photoHeld = true;
    d.photo = !raw && btn.photoPrev && !btn.photoHeld;
    btn.photoPrev = raw;
  }
  // rtw_glue.js tick: pad 1 before the game, photo mode and the recorder get it; true = a menu has it (the game gets an
  // idle pad)
  function input(d, now) {
    if (!glue) return false;
    buttons(d, now);
    let taken = false;
    for (const f of hooks.input) taken = f(d, now) || taken;
    return taken;
  }

  /* @RTW_FEATURES@ */

  // ---------------------------------------------------------------- P378 a notice on the picture (the replay's messages)
  // up to 3 lines of the game's font on a dark band at the bottom of the picture, over every feature's drawing; also
  // logged. ms 0 = until the next notice (the end of a replay, which stays paused).
  const noticeState = { text: '', until: 0, drawnTicks: 0 };
  function notice(text, ms) {
    log(`[notice] ${text}`);
    noticeState.text = String(text || ''); noticeState.until = ms > 0 ? performance.now() + ms : Infinity;
  }
  function drawNotice(ctx, now) {
    if (!noticeState.text) return false;
    if (now > noticeState.until) { noticeState.text = ''; return false; }
    if (!GameFont.load()) return false;
    const k = layer.h / 240, W = layer.w / k, ox = (W - 320) / 2, S = 0.7, LH = 10.5;
    const lines = GameFont.wrap(noticeState.text, 280, S).slice(0, 3), top = 234 - lines.length * LH - 6;
    ctx.fillStyle = 'rgba(0,0,0,0.72)'; ctx.fillRect((ox + 14) * k, top * k, 292 * k, (lines.length * LH + 6) * k);
    lines.forEach((l, j) => GameFont.draw(ctx, l, ox + 160, top + 3 + j * LH, k, { scale: S, color: '#fff', align: 'center', smooth: !!opt('smoothfont') }));
    noticeState.drawnTicks++;
    return true;
  }

  // ---------------------------------------------------------------- the overlay tick (pc_sched.c, after the game's frame)
  let tickErrors = 0, composited = 0;
  function tick() {
    if (!glue || !glue.started() || glue.photoBusy()) return;
    try {
      const now = performance.now();
      layerFit();
      layer.ctx.clearRect(0, 0, layer.w, layer.h);
      const q = rafQueue.splice(0);   // the page code's own animation frames (GPhoto draws the whole layer)
      for (const f of q) f(now);
      let drawn = false;
      for (const f of hooks.draw) drawn = f(layer.ctx, now) || drawn;
      drawn = drawNotice(layer.ctx, now) || drawn;   // P378
      if (drawn && M._port_rtw_overlay_composite()) composited++;
    } catch (e) {
      if (tickErrors++ < 3) log(`[overlay] ${e && e.stack || e}`);
    }
  }
  // gfx_f3dex2.c: the layer into its texture (bound to unit 0 now), straight alpha
  function upload() {
    const gl = GL.currentContext.GLctx;
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, false);
    gl.pixelStorei(gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL, false);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, layer.canvas);
  }

  return {
    attach(api) {   // rtw_glue.js start(), before the game boots
      glue = api;
      photo = api.photo; photoRequest = api.photoRequest; photoCapture = api.photoCapture;
      for (const f of hooks.attach) f();
      log(`[overlay] retrowser overlay layer: ${Object.keys(hooks.state).join(', ') || 'no features'}`);
    },
    hostOption: (id, value, started) => hostOption(id, value, started),
    input, tick, upload,
    wheel(dy) { for (const f of hooks.wheel) if (f(dy)) return true; return false; },   // P378 rtw_wheel: true = a menu took it
    photoTick: (dt, d, fresh) => photoTick(dt, d, fresh), photoShown: (on) => photoShown(on), photoToast: (text) => photoToast(text),
    setRecording(on) { recCfg = on ? { mode: 'record' } : null; optionsLocked = !!on; },
    hostResumed() { for (const f of hooks.hostResumed) f(); },   // rtw_pause(0)
    notice,   // P378
    state() {
      const s = { composited, font: GameFont.ready(), notice: { text: noticeState.text, drawnTicks: noticeState.drawnTicks } };   // P378 notice
      for (const [k, f] of Object.entries(hooks.state)) s[k] = f();
      return s;
    },
  };
})();
