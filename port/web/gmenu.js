// P361 native menus (docs/design/NATIVE_MENUS.md, step "overlay renderer + the game's font"): a menu drawn over the game
// picture in the game's own font and driven like the game's menus. Loaded after main.js as a classic script: it uses
// main.js's globals (M, OPTIONS, opt, setOption, applyPreset, ...) and main.js calls it through window.GMenu.
//
// Three parts:
// 1. GameFont: font 0 of the running game (port_font_info / port_font_glyph in port/gfx/gfx_f3dex2.c). The game
//    decodes it from the player's ROM at boot (glyph_rle_to_texture); the page only reads that memory, so nothing
//    ROM-derived is ever shipped, saved or uploaded. Glyphs are I8 (16 levels), drawn like text_draw_string: colour =
//    the text colour, alpha = colour alpha x intensity, pen += x offset, rows 1..h and columns 0..w-1 of the glyph,
//    advance w - 1, space 4. Pixel look = the glyph magnified with bilinear filtering (the N64 picture); with the
//    option Smooth font (P356) each glyph is upsampled 8x with the same Catmull-Rom + smoothstep (0.45) cut as the
//    renderer's shader, so the menu matches the game's smooth text.
// 2. MenuModel: one model over main.js's OPTIONS table (sections, items, toggles, sliders, presets, help, locks), the
//    single source of truth; changes go through setOption / applyPreset like the drawer's inputs, which are refreshed.
// 3. GMenu: the overlay (canvas #gmenu over #screen, 240 units high like the N64 screen, 320-unit 4:3 column centred)
//    and its input: D-pad / stick / arrows move (with key repeat), left / right change values, A / Start / Enter /
//    Space choose, B / Esc / Backspace go back, gamepad Home opens / closes; mouse / touch: hover / tap rows, wheel,
//    right click = back.
//
// Online rule (NATIVE_MENUS.md section 5): the overlay never writes game memory. While it is open, pad 1 gives the game
// "no buttons" (pollInput zeroes it; online the lockstep gets an idle pad, in a recording the recorder records an idle
// pad), it never pauses an online session or a recording / replay (single player: it pauses like the drawer), and the
// host's game options are shown locked. No game sounds: playing the game's menu sound would go through the game's
// sound state (hashed online), so the overlay is silent.
'use strict';

const GameFont = (() => {
  const F = { t: 0, m: 0, n: 0, sig: '', glyphs: [], map: new Int16Array(256).fill(-1), atlas: {}, smooth: null, smoothSig: '' };
  const S = 8;   // smooth atlas: texels upsampled S x
  const CELL = 16;   // atlas cell (texels): glyphs are at most 12 x 13
  // (re)read the font from game memory; false while the game has not loaded it
  function load() {
    if (typeof M === 'undefined' || !M || !M._port_font_info) return false;
    const n = M._port_font_info(2), t = M._port_font_info(0), m = M._port_font_info(1);
    if (!n || n > 256) return false;
    const H = M.HEAPU8, B = (a) => H[a ^ 3];   // the N64 mirror keeps big-endian words: byte a is at a ^ 3
    const glyphs = [];
    let sig = n + ':';
    for (let g = 0; g < n; g++) {
      const w = B(m + g * 4), h = B(m + g * 4 + 1), xo = B(m + g * 4 + 2), yo = B(m + g * 4 + 3);
      if (w > CELL || h > CELL - 2) return false;   // not (yet) a font
      const st = (w + 7) & ~7, I = new Uint8Array(w * h);
      for (let r = 1; r <= h; r++) for (let x = 0; x < w; x++) I[(r - 1) * w + x] = B(t + g * 0xE0 + r * st + (x ^ (r & 1 ? 4 : 0)));
      let s = 0; for (let i = 0; i < I.length; i++) s = (s * 31 + I[i]) | 0;
      sig += `${w},${h},${xo},${yo},${s};`;
      glyphs.push({ w, h, xo, yo, I });
    }
    if (sig !== F.sig) {
      F.sig = sig; F.glyphs = glyphs; F.n = n; F.atlas = {};
      for (let c = 0; c < 256; c++) { const g = M._port_font_glyph(c); F.map[c] = g >= 0 && g < n ? g : g === 0x60 ? 0x60 : -1; }
    }
    return true;
  }
  const ready = () => F.glyphs.length > 0;
  // white atlas (alpha = intensity), pixel or smooth
  function whiteAtlas(smooth) {
    const k = smooth ? S : 1, c = document.createElement('canvas');
    c.width = 16 * CELL * k; c.height = Math.ceil(F.n / 16) * CELL * k;
    const x2 = c.getContext('2d'), img = x2.createImageData(c.width, c.height), D = img.data;
    F.glyphs.forEach((gl, g) => {
      const ox = (g % 16) * CELL * k, oy = Math.floor(g / 16) * CELL * k;
      const at = (x, y) => (x < 0 || y < 0 || x >= gl.w || y >= gl.h ? 0 : gl.I[y * gl.w + x] / 255);
      if (!smooth) {
        for (let y = 0; y < gl.h; y++) for (let x = 0; x < gl.w; x++) { const o = ((oy + y) * c.width + ox + x) * 4; D[o] = D[o + 1] = D[o + 2] = 255; D[o + 3] = gl.I[y * gl.w + x]; }
        return;
      }
      // P356's cut: bicubic (Catmull-Rom) intensity at each sub-texel, smoothstep around 0.45 of full scale whose
      // half-width is half the change per output pixel, times the glyph's own full intensity 0xF0 / 0xFF
      const cr = (p0, p1, p2, p3, t) => p1 + 0.5 * t * (p2 - p0 + t * (2 * p0 - 5 * p1 + 4 * p2 - p3 + t * (3 * (p1 - p2) + p3 - p0)));
      const W = gl.w * k, Hh = gl.h * k, V = new Float32Array((W + 1) * (Hh + 1));
      for (let y = 0; y <= Hh; y++) for (let x = 0; x <= W; x++) {
        const u = (x + 0.5) / k - 0.5, v = (y + 0.5) / k - 0.5, ix = Math.floor(u), iy = Math.floor(v), fx = u - ix, fy = v - iy, row = [];
        for (let j = -1; j <= 2; j++) row.push(cr(at(ix - 1, iy + j), at(ix, iy + j), at(ix + 1, iy + j), at(ix + 2, iy + j), fx));
        V[y * (W + 1) + x] = cr(row[0], row[1], row[2], row[3], fy);
      }
      for (let y = 0; y < Hh; y++) for (let x = 0; x < W; x++) {
        const v = V[y * (W + 1) + x], gx = V[y * (W + 1) + x + 1] - v, gy = V[(y + 1) * (W + 1) + x] - v;
        const hw = Math.max(0.02, 0.5 * Math.hypot(gx, gy) * 2), e0 = 0.45 - hw, e1 = 0.45 + hw;
        let a = Math.min(1, Math.max(0, (v - e0) / (e1 - e0))); a = a * a * (3 - 2 * a);
        const o = ((oy + y) * c.width + ox + x) * 4; D[o] = D[o + 1] = D[o + 2] = 255; D[o + 3] = Math.round(a * 0xF0);
      }
    });
    x2.putImageData(img, 0, 0);
    return c;
  }
  // a coloured atlas (cached per colour and look)
  function atlas(color, smooth) {
    const key = (smooth ? 's' : 'p') + color;
    if (F.atlas[key]) return F.atlas[key];
    const wk = smooth ? 'swhite' : 'pwhite';
    if (!F.atlas[wk]) F.atlas[wk] = whiteAtlas(smooth);
    const w = F.atlas[wk], c = document.createElement('canvas'); c.width = w.width; c.height = w.height;
    const x2 = c.getContext('2d'); x2.drawImage(w, 0, 0); x2.globalCompositeOperation = 'source-in'; x2.fillStyle = color; x2.fillRect(0, 0, c.width, c.height);
    return (F.atlas[key] = c);
  }
  // page text -> characters the font has (it is upper case; the game maps lower case itself)
  const FOLD = { '…': '...', '–': '-', '—': '-', '’': "'", '‘': "'", '“': '"', '”': '"', '×': 'X', '·': '-', '→': '>', '←': '<', '↑': '^', '↓': 'V', '°': '', '\n': ' ' };
  function glyphsOf(s) {
    const out = [];
    for (const ch of String(s)) {
      const f = FOLD[ch]; if (f !== undefined) { for (const c of f) out.push(F.map[c.charCodeAt(0)]); continue; }
      const c = ch.charCodeAt(0); out.push(c < 256 ? F.map[c] : -1);
    }
    return out;
  }
  // width in N64 units at text scale `scale` (1 = the game's normal text)
  function measure(s, scale = 1) {
    let x = 0;
    for (const g of glyphsOf(s)) { if (g === 0x60 || g < 0) x += 4; else { const gl = F.glyphs[g]; x += gl.xo + gl.w - 1; } }
    return x * scale;
  }
  // draw s at (x, y) N64 units (top of the line), k = canvas pixels per unit
  function draw(ctx, s, x, y, k, { scale = 1, color = '#fff', alpha = 1, align = 'left', smooth = false } = {}) {
    if (!ready()) return 0;
    const wdt = measure(s, scale);
    if (align === 'center') x -= wdt / 2; else if (align === 'right') x -= wdt;
    const A = atlas(color, smooth), sk = smooth ? S : 1;
    ctx.save(); ctx.globalAlpha = alpha; ctx.imageSmoothingEnabled = true; ctx.imageSmoothingQuality = 'high';
    for (const g of glyphsOf(s)) {
      if (g === 0x60 || g < 0) { x += 4 * scale; continue; }
      const gl = F.glyphs[g]; x += gl.xo * scale;
      ctx.drawImage(A, (g % 16) * CELL * sk, Math.floor(g / 16) * CELL * sk, gl.w * sk, gl.h * sk, x * k, (y + gl.yo * scale) * k, gl.w * scale * k, gl.h * scale * k);
      x += (gl.w - 1) * scale;
    }
    ctx.restore();
    return wdt;
  }
  // greedy word wrap to `width` units
  function wrap(s, width, scale = 1) {
    const lines = []; let line = '';
    for (const w of String(s).split(/\s+/)) {
      const t = line ? line + ' ' + w : w;
      if (measure(t, scale) <= width || !line) line = t; else { lines.push(line); line = w; }
    }
    if (line) lines.push(line);
    return lines;
  }
  return { load, ready, measure, draw, wrap, glyphsOf, get count() { return F.n; } };
})();

// ---------------------------------------------------------------- the menu model (one source: main.js OPTIONS)
const MenuModel = (() => {
  // sections of the options table (NATIVE_MENUS.md section 1 B); an option missing here lands in TOOLS
  const SECTIONS = [
    { id: 'picture', label: 'Picture', help: 'Widescreen, resolution, smooth motion, sharp menus and font.', keys: ['widescreen', 'fullres', 'hfr', 'hires2d', 'smoothfont'] },
    { id: 'hud', label: 'HUD and information', help: 'What the screen shows during play: save icon, health, cash, air meter, crosshair.', keys: ['saveicon', 'healthhud', 'cashhud', 'airbar', 'crosshair'] },
    { id: 'gameplay', label: 'Gameplay', help: 'Cutscene skipping, intro, breath, tail spin, ledges, motion blur, detail.', keys: ['skipcut', 'skipintro', 'longbreath', 'longspin', 'ledgegrab', 'nodrunk', 'conkerlod'] },
    { id: 'controls', label: 'Controls', help: 'Toggles for crouch, R-Look and walk, swimming direction, free camera, rumble. Key and pad bindings: page menu.', keys: ['togglecrouch', 'togglerlook', 'togglewalk', 'swiminvert', 'freecam', 'rumble'] },
    { id: 'sound', label: 'Sound', help: 'Music, sound effects and speech volumes.', keys: ['volmusic', 'volsfx', 'volspeech'] },
    { id: 'tools', label: 'Tools', help: 'Online play, the input recorder, photo mode and this menu.', keys: ['online', 'recorder', 'photomode', 'nativemenu'] },
  ];
  const TOOL_KEYS = ['online', 'recorder', 'photomode'];
  const optByKey = (k) => OPTIONS.find((o) => o.key === k);
  // why an option cannot change now ('' = it can)
  function lockReason(o) {
    if (optionsLocked && o.game !== undefined) return netCfg ? "Online: the game uses player 1's (the host's) options." : recCfg ? 'Fixed while recording (reload the page to change it).' : 'Fixed for this run.';
    if ((netCfg || recCfg || NETDET) && TOOL_KEYS.includes(o.key)) return 'Not during an online session or a recording.';
    return '';
  }
  function optionItem(o) {
    return {
      kind: o.range ? 'range' : 'toggle', key: o.key, label: o.label, help: o.help,
      get: () => opt(o.key),
      locked: () => lockReason(o),
      set: (v) => {
        if (lockReason(o)) return false;
        if (o.range) v = Math.max(0, Math.min(100, Math.round(v / 5) * 5));
        if (v === opt(o.key)) return false;
        setOption(o, v); optionPicked(o); showOptionValue(o);
        log(`[options] ${o.key} ${o.range ? v : v ? 'on' : 'off'} (game menu)`);
        return true;
      },
    };
  }
  const presetItem = () => ({
    kind: 'choice', key: 'preset', label: 'Preset', choices: ['classic', 'modern'], all: ['classic', 'modern', 'custom'],
    help: () => PRESETS[presetShown()].help,
    get: () => presetShown(), names: (v) => PRESETS[v].label,
    locked: () => (optionsLocked ? 'The game options are fixed for this session.' : ''),
    set: (v) => { if (optionsLocked || v === presetShown()) return false; applyPreset(v); return true; },
  });
  function sections() {
    const placed = new Set(SECTIONS.flatMap((s) => s.keys));
    return SECTIONS.map((s) => ({
      ...s,
      items: s.keys.concat(s.id === 'tools' ? OPTIONS.map((o) => o.key).filter((k) => !placed.has(k)) : []).map(optByKey).filter(Boolean).map(optionItem),
    }));
  }
  return { sections, presetItem, lockReason };
})();

// ---------------------------------------------------------------- the overlay
const GMenu = (() => {
  const U = { open: false, t0: 0, closing: 0, stack: [], hits: [], raf: 0, paused: false,
    prev: 0, repeatAt: 0, held: 0, helpPage: 0, helpAt: 0, helpSel: '', homePrev: false, mx: -1, my: -1 };
  const cv = document.getElementById('gmenu');
  const ROW = 15, ROWS = 8, TOP = 46, X0 = 34, X1 = 286;   // row spacing / visible rows / list top / label x / value right edge (units)
  const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', off: 'rgb(170,170,170)', dim: 'rgb(150,150,150)', lock: 'rgb(120,120,120)', head: 'rgb(255,200,60)' };
  const smooth = () => !!opt('smoothfont');
  const wanted = () => !!opt('nativemenu');
  const page = () => U.stack[U.stack.length - 1];

  // pages: main (preset, sections, page menu, back to game) and one per section
  function mainItems() {
    return [MenuModel.presetItem()].concat(MenuModel.sections().map((s) => ({ kind: 'link', label: s.label, help: s.help, section: s.id })), [
      { kind: 'action', label: 'Page menu (all settings)', help: 'The page menu: key and pad bindings, saves, online, the input recorder, fullscreen and debug.', act: () => { close(); drawerSet(true); toggle('options', true); } },
      { kind: 'action', label: 'Back to game', help: 'Close this menu (B, Esc or Start on this line).', act: () => close() },
    ]);
  }
  function itemsOf(p) {
    if (p.id === 'main') return mainItems();
    const s = MenuModel.sections().find((x) => x.id === p.id);
    return s.items.concat([{ kind: 'action', label: 'Back', help: 'Back to the options.', act: () => back() }]);
  }
  const titleOf = (p) => (p.id === 'main' ? 'Options' : MenuModel.sections().find((x) => x.id === p.id).label);

  function open() {
    if (U.open || typeof running === 'undefined' || running !== 'game') return false;
    if (photo.state === 2 || !GameFont.load()) return false;   // photo mode has the pad; no font yet: the drawer instead
    U.open = true; U.t0 = performance.now(); U.closing = 0; U.stack = [{ id: 'main', sel: 0, top: 0 }];
    U.prev = -1; U.held = 0; U.helpSel = '';
    document.body.classList.add('gmenu'); cv.hidden = false;
    // single player: pause like the drawer (never online, never while recording or replaying)
    if (!netCfg && !recCfg && !NETDET && !userPaused) { U.paused = true; setPaused(true); }
    if (document.pointerLockElement && document.exitPointerLock) document.exitPointerLock();
    log('[gmenu] open');
    frame();
    return true;
  }
  function close() {
    if (!U.open) return;
    U.open = false;
    document.body.classList.remove('gmenu'); cv.hidden = true;
    if (U.paused && userPaused) setPaused(false);
    U.paused = false;
    keysDown.clear();
    photo.maskB = 0xFFFF; photo.maskStick = true;   // held buttons / stick reach the game only once released (photoMaskAfter)
    $('canvas').focus();
    log('[gmenu] close');
  }
  function back() { if (U.stack.length > 1) { U.stack.pop(); U.helpSel = ''; } else close(); }

  // ---- actions on the selected item
  function moveSel(d) {
    const p = page(), n = itemsOf(p).length;
    p.sel = (p.sel + d + n) % n;
  }
  function change(item, d) {   // left / right
    if (!item || item.locked && item.locked()) return;
    if (item.kind === 'toggle') item.set(!item.get());
    else if (item.kind === 'range') item.set(item.get() + d * 5);
    else if (item.kind === 'choice') { const i = item.choices.indexOf(item.get()); item.set(item.choices[((i < 0 ? (d > 0 ? -1 : 0) : i) + d + item.choices.length) % item.choices.length]); }
  }
  function choose(item) {
    if (!item) return;
    if (item.kind === 'link') { U.stack.push({ id: item.section, sel: 0, top: 0 }); U.helpSel = ''; }
    else if (item.kind === 'action') item.act();
    else change(item, 1);
  }

  // ---- input: one call per animation frame from pollInput with pad 1 (keyboard + first gamepad + touch); true = the
  // menu has pad 1 (the game gets no buttons)
  function poll(d) {
    const gp = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).find((g) => g && g.connected);
    const raw = (i) => !!(gp && gp.buttons[i] && (gp.buttons[i].pressed || gp.buttons[i].value > 0.5));
    const home = raw(16);
    if (home && !U.homePrev) { U.homePrev = true; if (U.open) close(); else if (wanted()) open(); return U.open; }
    U.homePrev = home;
    if (!U.open) return false;
    const b = d.b | 0, now = performance.now();
    let bits = 0;
    if ((b & N64.DU) || d.y > 40) bits |= 1;
    if ((b & N64.DD) || d.y < -40) bits |= 2;
    if ((b & N64.DL) || d.x < -40) bits |= 4;
    if ((b & N64.DR) || d.x > 40) bits |= 8;
    if ((b & (N64.A | N64.START)) || raw(0)) bits |= 16;
    if ((b & N64.B) || raw(1)) bits |= 32;
    if (U.prev < 0) { U.prev = bits; return true; }   // the press that opened the menu does nothing in it
    const fresh = bits & ~U.prev;
    let dir = fresh & 15;
    if ((bits & 15) && (bits & 15) === (U.prev & 15)) { if (now >= U.repeatAt) { dir = bits & 15; U.repeatAt = now + 90; } }
    else U.repeatAt = now + 380;
    U.prev = bits;
    const item = itemsOf(page())[page().sel];
    if (dir & 1) moveSel(-1); else if (dir & 2) moveSel(1);
    if (dir & 4) change(item, -1); else if (dir & 8) change(item, 1);
    if (fresh & 16) choose(item);
    else if (fresh & 32) back();
    return true;
  }
  // keys the pad mapping does not cover (main.js keydown calls this first while the menu is open); true = used
  function key(e) {
    if (!U.open) return false;
    if (e.code === 'Escape' || e.code === 'Backspace') { back(); return true; }
    return false;
  }

  // ---- drawing
  function layout() {
    const r = cv.getBoundingClientRect(), dpr = Math.min(2, window.devicePixelRatio || 1);
    const w = Math.max(1, Math.round(r.width * dpr)), h = Math.max(1, Math.round(r.height * dpr));
    if (cv.width !== w || cv.height !== h) { cv.width = w; cv.height = h; }
    const k = h / 240;
    return { k, W: w / k, ox: (w / k - 320) / 2 };
  }
  function frame() {
    if (!U.open) return;
    U.raf = requestAnimationFrame(frame);
    if (!GameFont.load()) return;
    const ctx = cv.getContext('2d'), { k, W, ox } = layout(), now = performance.now();
    const fade = Math.min(1, (now - U.t0) / 160);   // like the game's page alpha (32 per tick)
    ctx.clearRect(0, 0, cv.width, cv.height);
    // backdrop: the picture darkened, a warmer, darker band behind the menu column
    ctx.fillStyle = `rgba(0,0,0,${0.45 * fade})`; ctx.fillRect(0, 0, cv.width, cv.height);
    const g = ctx.createLinearGradient((ox + 6) * k, 0, (ox + 314) * k, 0);
    g.addColorStop(0, 'rgba(20,10,4,0)'); g.addColorStop(0.12, `rgba(20,10,4,${0.62 * fade})`); g.addColorStop(0.88, `rgba(20,10,4,${0.62 * fade})`); g.addColorStop(1, 'rgba(20,10,4,0)');
    ctx.fillStyle = g; ctx.fillRect((ox + 6) * k, 8 * k, 308 * k, 224 * k);
    const T = (s, x, y, o) => GameFont.draw(ctx, s, ox + x, y, k, Object.assign({ smooth: smooth() }, o, { alpha: (o && o.alpha !== undefined ? o.alpha : 1) * fade }));
    U.hits = [];
    const p = page(), items = itemsOf(p);
    T(titleOf(p), 160, 18, { scale: 1.5, color: C.title, align: 'center' });
    // list (scrolls to keep the selection visible)
    if (p.sel < p.top) p.top = p.sel;
    if (p.sel >= p.top + ROWS) p.top = p.sel - ROWS + 1;
    const pulse = 0.75 + 0.25 * Math.sin(now / 160);
    for (let i = p.top; i < Math.min(items.length, p.top + ROWS); i++) {
      const it = items[i], y = TOP + (i - p.top) * ROW, sel = i === p.sel, lock = it.locked ? it.locked() : '';
      U.hits.push({ i, x0: ox + 20, x1: ox + 300, y0: y - 3, y1: y + ROW - 3 });
      if (sel) {
        const hb = ctx.createLinearGradient((ox + 20) * k, 0, (ox + 300) * k, 0);
        hb.addColorStop(0, 'rgba(255,60,30,0)'); hb.addColorStop(0.2, `rgba(255,60,30,${0.28 * fade})`); hb.addColorStop(0.8, `rgba(255,60,30,${0.28 * fade})`); hb.addColorStop(1, 'rgba(255,60,30,0)');
        ctx.fillStyle = hb; ctx.fillRect((ox + 20) * k, (y - 3) * k, 280 * k, (ROW - 1) * k);
        T('>', X0 - 12, y, { color: C.on, alpha: pulse });
      }
      const lc = lock ? C.lock : sel ? C.text : C.dim;
      T(it.label, X0, y, { color: lc, scale: 0.85 });
      let v = '', vc = sel ? C.text : C.dim;
      if (it.kind === 'toggle') { const on = it.get(); v = on ? 'ON' : 'OFF'; vc = lock ? C.lock : on ? C.on : C.off; }
      else if (it.kind === 'range') { v = it.get() + '%'; vc = lock ? C.lock : sel ? C.on : C.off; }
      else if (it.kind === 'choice') { v = it.names(it.get()); vc = lock ? C.lock : C.on; }
      else if (it.kind === 'link') v = '>';
      if (v) {
        if (sel && !lock && (it.kind === 'range' || it.kind === 'choice')) { T('<', X1 - GameFont.measure(v, 0.85) - 9, y, { color: vc, scale: 0.85, alpha: pulse }); T('>', X1 + 4, y, { color: vc, scale: 0.85, alpha: pulse }); }
        T(v, X1, y, { color: vc, scale: 0.85, align: 'right' });
      }
    }
    if (p.top > 0) T('^', 160, TOP - 11, { color: C.dim, align: 'center', scale: 0.8 });
    if (p.top + ROWS < items.length) T('V', 160, TOP + ROWS * ROW - 2, { color: C.dim, align: 'center', scale: 0.6 });
    // help for the selected line (pages of 4 lines, turning every 5 s)
    const it = items[p.sel], lock = it && it.locked ? it.locked() : '';
    const helpText = (lock ? lock + ' ' : '') + (it ? (typeof it.help === 'function' ? it.help() : it.help || '') : '');
    const sig = p.id + ':' + p.sel + ':' + helpText;
    if (sig !== U.helpSel) { U.helpSel = sig; U.helpPage = 0; U.helpAt = now; }
    const HS = 0.62;
    let lines = GameFont.wrap(helpText, 268, HS);
    if (lines.length > 4) lines = GameFont.wrap(helpText, 250, HS);   // leave room for the page counter
    const pages = Math.max(1, Math.ceil(lines.length / 4));
    if (now - U.helpAt > 5000) { U.helpAt = now; U.helpPage = (U.helpPage + 1) % pages; }
    ctx.fillStyle = `rgba(0,0,0,${0.35 * fade})`; ctx.fillRect((ox + 20) * k, 170 * k, 280 * k, 46 * k);
    lines.slice(U.helpPage * 4, U.helpPage * 4 + 4).forEach((l, j) => T(l, 26, 174 + j * 10, { scale: HS, color: lock && j === 0 && U.helpPage === 0 ? C.head : C.text, alpha: 0.9 }));
    if (pages > 1) T(`${U.helpPage + 1}/${pages}`, 296, 207, { scale: 0.5, color: C.dim, align: 'right' });
    // footer: what the buttons do (B / CLOSE are also mouse / touch targets)
    const FS = 0.55;
    T('A CHOOSE', 26, 224, { scale: FS, color: C.dim });
    const bw = T(U.stack.length > 1 ? 'B BACK' : 'B CLOSE', 160, 224, { scale: FS, color: C.dim, align: 'center' });
    U.hits.push({ act: 'back', x0: ox + 160 - bw / 2 - 4, x1: ox + 160 + bw / 2 + 4, y0: 220, y1: 236 });
    T('< > CHANGE', 294, 224, { scale: FS, color: C.dim, align: 'right' });
  }

  // ---- mouse / touch
  function hitAt(e) {
    const r = cv.getBoundingClientRect(), k = cv.height / 240 / (cv.height / r.height);
    const x = (e.clientX - r.left) / k, y = (e.clientY - r.top) / k;
    return U.hits.find((h) => x >= h.x0 && x <= h.x1 && y >= h.y0 && y <= h.y1);
  }
  cv.addEventListener('pointermove', (e) => { const h = hitAt(e); if (h && h.i !== undefined && (e.movementX || e.movementY)) page().sel = h.i; });
  cv.addEventListener('pointerdown', (e) => {
    e.preventDefault();
    if (e.button === 2) { back(); return; }
    const h = hitAt(e);
    if (!h) return;
    if (h.act === 'back') { back(); return; }
    const p = page(), it = itemsOf(p)[h.i];
    p.sel = h.i;
    const r = cv.getBoundingClientRect(), xu = (e.clientX - r.left) / (r.height / 240) - (r.width / (r.height / 240) - 320) / 2;
    if ((it.kind === 'range' || it.kind === 'choice') && xu > 200) change(it, xu < 250 ? -1 : 1); else choose(it);
  });
  cv.addEventListener('contextmenu', (e) => e.preventDefault());
  cv.addEventListener('wheel', (e) => { e.preventDefault(); moveSel(e.deltaY > 0 ? 1 : -1); }, { passive: false });

  // test aid ?gmenuopen=S: open the menu S seconds after the game started (page-only: nothing hashed changes; netpair
  // GUESTQ='&opt=nativemenu:1&gmenuopen=40' keeps it open on a guest during an online session)
  if (Q.get('gmenuopen')) {
    const at = performance.now() + 1000 * +Q.get('gmenuopen');
    const tryOpen = () => { if (performance.now() >= at && open()) log('[gmenu] opened by ?gmenuopen'); else setTimeout(tryOpen, 500); };
    setTimeout(tryOpen, 1000 * +Q.get('gmenuopen'));
  }

  return { open, close, back, poll, key, wanted, get isOpen() { return U.open; }, state: () => ({ open: U.open, page: U.open ? page().id : null, sel: U.open ? page().sel : -1, item: U.open ? (itemsOf(page())[page().sel] || {}).label : null }) };
})();
window.GMenu = GMenu;
window.GameFont = GameFont;
window.MenuModel = MenuModel;
