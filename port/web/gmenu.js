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
// host's game options are shown locked. P367: the game's own menu sounds through GSound (decoded from the ROM by the
// page, never through the game's hashed sound state; silent online, in recordings / replays and under ?netdet).
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
  // P362: "." and "," (at most 3 x 3 texels) advance only 2 units after a 1-unit offset, so a dot between two digits sat
  // inside the next digit's lower-left curve ("1.5" read "15"); they get TINY_PAD units more
  const TINY_PAD = 1.5, tiny = (gl) => gl.w <= 3 && gl.h <= 3;
  // width in N64 units at text scale `scale` (1 = the game's normal text)
  function measure(s, scale = 1) {
    let x = 0;
    for (const g of glyphsOf(s)) { if (g === 0x60 || g < 0) x += 4; else { const gl = F.glyphs[g]; x += gl.xo + gl.w - 1 + (tiny(gl) ? TINY_PAD : 0); } }
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
      // P362: a tiny glyph drawn below 0.85 x is drawn at 0.85 x, bottom-aligned, at its own centre, so it does not
      // fade into the bilinear filter at the help text's size
      const ts = !smooth && tiny(gl) && scale < 0.85 ? 0.85 : scale;
      const dx = (gl.w * (scale - ts)) / 2, dy = gl.h * (scale - ts);
      ctx.drawImage(A, (g % 16) * CELL * sk, Math.floor(g / 16) * CELL * sk, gl.w * sk, gl.h * sk, (x + dx) * k, (y + gl.yo * scale + dy) * k, gl.w * ts * k, gl.h * ts * k);
      x += (gl.w - 1 + (tiny(gl) ? TINY_PAD : 0)) * scale;
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
  // P365: the ONLINE pages run before the game boots (an online match starts from power-on), when no game memory holds
  // the font yet. So the page keeps a copy of font 0 (glyph sizes, offsets, intensities and the character map) in this
  // browser's localStorage, keyed by the ROM's SHA-1, like the ROM itself sits in IndexedDB: it never leaves the
  // browser. save() after the game decoded it, restore() before boot (false: no copy for this ROM yet).
  const STORE = 'gmenu.font0';
  function save(key) {
    if (!ready() || !key) return false;
    try {
      const b64 = (u8) => btoa(String.fromCharCode.apply(null, u8));
      localStorage.setItem(STORE, JSON.stringify({ key, map: Array.from(F.map), g: F.glyphs.map((x) => [x.w, x.h, x.xo, x.yo, b64(x.I)]) }));
      return true;
    } catch (e) { return false; }
  }
  function restore(key) {
    if (ready()) return true;
    try {
      const j = JSON.parse(localStorage.getItem(STORE) || 'null');
      if (!j || !key || j.key !== key || !Array.isArray(j.g) || !j.g.length) return false;
      F.glyphs = j.g.map(([w, h, xo, yo, b]) => ({ w, h, xo, yo, I: Uint8Array.from(atob(b), (c) => c.charCodeAt(0)) }));
      F.n = F.glyphs.length; F.map = Int16Array.from(j.map); F.atlas = {}; F.sig = 'stored';
      return true;
    } catch (e) { return false; }
  }
  return { load, ready, measure, draw, wrap, glyphsOf, save, restore, get count() { return F.n; }, get sig() { return F.sig; } };
})();

// ---------------------------------------------------------------- the menu model (one source: main.js OPTIONS)
const MenuModel = (() => {
  // sections of the options table (NATIVE_MENUS.md section 1 B); an option missing here lands in TOOLS
  const SECTIONS = [
    { id: 'picture', label: 'Picture', help: 'Widescreen, resolution, smooth motion, sharp menus and font.', keys: ['widescreen', 'fullres', 'hfr', 'hires2d', 'smoothfont'] },
    { id: 'hud', label: 'HUD and information', help: 'What the screen shows during play: save icon, health, cash, air meter, crosshair.', keys: ['saveicon', 'healthhud', 'cashhud', 'airbar', 'crosshair'] },
    { id: 'gameplay', label: 'Gameplay', help: 'Cutscene skipping, intro, breath, tail spin, ledges, motion blur, detail.', keys: ['skipcut', 'skipintro', 'longbreath', 'longspin', 'ledgegrab', 'nodrunk', 'conkerlod'] },
    { id: 'controls', label: 'Controls', help: 'Keyboard keys and gamepad buttons, touch controls, toggles for crouch, R-Look and walk, swimming direction, free camera, rumble.', keys: ['togglecrouch', 'togglerlook', 'togglewalk', 'swiminvert', 'freecam', 'rumble'] },
    { id: 'sound', label: 'Sound', help: 'Master volume, music, sound effects and speech volumes.', keys: ['volmusic', 'volsfx', 'volspeech'] },
    { id: 'tools', label: 'Tools', help: 'Online play, the input recorder and photo mode.', keys: ['online', 'recorder', 'photomode'] },
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

// ---------------------------------------------------------------- P366 footer button faces (GMenu and GPhoto)
// The N64's round buttons (blue A, green B, red Start ...) and the D-pad cross as shapes: the game's own button icons are
// sprites, not font glyphs (P361). x, y in N64 units relative to ox (y = the top of the footer's text line); T draws text
// (GameFont.draw bound to the canvas). Each returns the width it took.
const GFace = {
  round(ctx, T, k, ox, x, y, letter, fill, fade) {
    ctx.save(); ctx.globalAlpha = 0.95 * fade;
    ctx.beginPath(); ctx.arc((ox + x) * k, (y + 3.4) * k, 5.2 * k, 0, 2 * Math.PI); ctx.fillStyle = fill; ctx.fill();
    ctx.lineWidth = Math.max(1, 0.7 * k); ctx.strokeStyle = 'rgba(0,0,0,0.6)'; ctx.stroke(); ctx.restore();
    T(letter, x, y + 0.6, { scale: 0.5, color: '#fff', align: 'center' });
    return 7;
  },
  // arms: 'lr' (left / right lit), 'ud' (up / down lit), 'all'
  dpad(ctx, k, ox, x, y, arms, fade) {
    const cy = y + 3.4;
    ctx.save(); ctx.globalAlpha = 0.95 * fade; ctx.fillStyle = 'rgb(85,85,85)'; ctx.strokeStyle = 'rgba(0,0,0,0.6)'; ctx.lineWidth = Math.max(1, 0.5 * k);
    ctx.beginPath(); ctx.rect((ox + x - 5.4) * k, (cy - 1.9) * k, 10.8 * k, 3.8 * k); ctx.rect((ox + x - 1.9) * k, (cy - 5.4) * k, 3.8 * k, 10.8 * k); ctx.stroke(); ctx.fill();
    ctx.fillStyle = 'rgb(240,240,240)';
    if (arms !== 'ud') for (const sx of [-1, 1]) { ctx.beginPath(); ctx.moveTo((ox + x + sx * 4.9) * k, cy * k); ctx.lineTo((ox + x + sx * 2.5) * k, (cy - 1.4) * k); ctx.lineTo((ox + x + sx * 2.5) * k, (cy + 1.4) * k); ctx.fill(); }
    if (arms !== 'lr') for (const sy of [-1, 1]) { ctx.beginPath(); ctx.moveTo((ox + x) * k, (cy + sy * 4.9) * k); ctx.lineTo((ox + x - 1.4) * k, (cy + sy * 2.5) * k); ctx.lineTo((ox + x + 1.4) * k, (cy + sy * 2.5) * k); ctx.fill(); }
    ctx.restore();
    return 7;
  },
  // a page input (a key or a gamepad button the N64 never had: O, H, RS, RT ...): a grey key cap with its name
  cap(ctx, T, k, ox, x, y, name, fade) {
    const w = Math.max(9, GameFont.measure(name, 0.45) + 5);
    ctx.save(); ctx.globalAlpha = 0.95 * fade; ctx.fillStyle = 'rgb(85,85,85)'; ctx.strokeStyle = 'rgba(0,0,0,0.6)'; ctx.lineWidth = Math.max(1, 0.5 * k);
    ctx.beginPath();
    if (ctx.roundRect) ctx.roundRect((ox + x) * k, (y - 1.2) * k, w * k, 9.2 * k, 2 * k); else ctx.rect((ox + x) * k, (y - 1.2) * k, w * k, 9.2 * k);
    ctx.fill(); ctx.stroke(); ctx.restore();
    T(name, x + w / 2, y + 0.8, { scale: 0.45, color: '#fff', align: 'center' });
    return w;
  },
};

// ---------------------------------------------------------------- P368 touch controls in the game's style
// With the game-style menu on and the game's font at hand (the running game's, or the copy kept for this ROM before boot),
// the on-screen buttons get the faces of GMenu's footer (GFace): the N64's blue A, green B, yellow C buttons with their
// arrows, red Start, grey shoulder caps, letters in the game's font with a hard drop shadow; the stick a dark ring with
// a grey knob. Translucent at rest, bright while held. Only the look changes: each .tb div keeps its size, place and
// pointer handlers (main.js initTouch), a canvas inside it (pointer-events: none) carries the face. body.gtouch switches
// the page's CSS faces off. No font yet: the page's own faces. Re-drawn when the font,
// the Smooth font look or the screen's pixel ratio change (checked twice a second; nothing is drawn per frame).
const GTouch = (() => {
  let sig = '';
  const BLUE = 'rgb(40,90,230)', GREEN = 'rgb(30,160,60)', YELLOW = 'rgb(235,190,25)', RED = 'rgb(200,40,40)', GREY = 'rgb(95,95,95)';
  // id -> [label, fill, shape, arrow direction for C buttons]
  const FACES = { A: ['A', BLUE, 'round'], B: ['B', GREEN, 'round'], CU: ['', YELLOW, 'round', 'u'], CD: ['', YELLOW, 'round', 'd'],
    CL: ['', YELLOW, 'round', 'l'], CR: ['', YELLOW, 'round', 'r'], START: ['START', RED, 'pill'], L: ['L', GREY, 'cap'], Z: ['Z', GREY, 'cap'], R: ['R', GREY, 'cap'] };
  const fontOk = () => GameFont.load() || (typeof romSha1 !== 'undefined' && !!romSha1 && GameFont.restore(romSha1));
  function face(el, [label, fill, shape, arrow], smooth, dpr) {
    let cv = el.querySelector('canvas.gt');
    if (!cv) { cv = document.createElement('canvas'); cv.className = 'gt'; el.appendChild(cv); }
    const w = Math.round(el.clientWidth * dpr), h = Math.round(el.clientHeight * dpr);
    cv.width = w; cv.height = h;
    const ctx = cv.getContext('2d'), lw = Math.max(1.5, 2 * dpr);
    ctx.clearRect(0, 0, w, h);
    ctx.beginPath();
    if (shape === 'round') ctx.arc(w / 2, h / 2, Math.min(w, h) / 2 - lw, 0, 2 * Math.PI);
    else { const r = shape === 'pill' ? h / 2 - lw : Math.min(w, h) * 0.28; if (ctx.roundRect) ctx.roundRect(lw, lw, w - 2 * lw, h - 2 * lw, r); else ctx.rect(lw, lw, w - 2 * lw, h - 2 * lw); }
    ctx.fillStyle = fill; ctx.fill();
    const g = ctx.createLinearGradient(0, 0, 0, h);   // the plastic's sheen: lighter on top, darker below
    g.addColorStop(0, 'rgba(255,255,255,0.28)'); g.addColorStop(0.5, 'rgba(255,255,255,0)'); g.addColorStop(1, 'rgba(0,0,0,0.25)');
    ctx.fillStyle = g; ctx.fill();
    ctx.lineWidth = lw; ctx.strokeStyle = 'rgba(0,0,0,0.65)'; ctx.stroke();
    if (arrow) {   // the C buttons' arrows (the game's font has no triangles)
      const c = Math.min(w, h) / 2, a = c * 0.42, b = c * 0.3;
      const pts = { u: [[0, -a], [-b, a * 0.45], [b, a * 0.45]], d: [[0, a], [-b, -a * 0.45], [b, -a * 0.45]], l: [[-a, 0], [a * 0.45, -b], [a * 0.45, b]], r: [[a, 0], [-a * 0.45, -b], [-a * 0.45, b]] }[arrow];
      for (const [col, off] of [['rgba(0,0,0,0.8)', lw], ['rgb(60,45,0)', 0]]) {
        ctx.beginPath(); pts.forEach(([x, y], i) => (i ? ctx.lineTo : ctx.moveTo).call(ctx, w / 2 + x + off, h / 2 + y + off)); ctx.closePath(); ctx.fillStyle = col; ctx.fill();
      }
      return;
    }
    // the label in the game's font, white with the game's hard black drop shadow, about 45 % of the face's height
    const k = (h * (shape === 'pill' ? 0.42 : 0.4)) / 11, cx = w / 2 / k, ty = (h / 2) / k - 6;
    const sc = shape === 'pill' ? Math.min(1, (w * 0.8 / k) / Math.max(1, GameFont.measure(label, 1))) : 1;
    GameFont.draw(ctx, label, cx + 0.8, ty + 0.8 + (1 - sc) * 6, k, { scale: sc, color: '#000', alpha: 0.85, align: 'center', smooth });
    GameFont.draw(ctx, label, cx, ty + (1 - sc) * 6, k, { scale: sc, color: '#fff', align: 'center', smooth });
  }
  function check() {
    const on = !$('touch').hidden && fontOk();   // P369: the game-style menus are always on (no option)
    const dpr = Math.min(3, window.devicePixelRatio || 1), smooth = on && !!opt('smoothfont');
    const nsig = on ? `${smooth}:${dpr}:${GameFont.count}:${innerWidth}x${innerHeight}` : 'off';
    if (nsig === sig) return;
    sig = nsig;
    document.body.classList.toggle('gtouch', on);
    if (!on) return;
    for (const [id, f] of Object.entries(FACES)) { const el = $('tk-' + id); if (el) face(el, f, smooth, dpr); }
    log(`[gtouch] game-style touch controls (${smooth ? 'smooth' : 'pixel'} font, dpr ${dpr})`);
  }
  setInterval(check, 500);
  return { check };
})();
window.GTouch = GTouch;

// ---------------------------------------------------------------- P368 boot screens in the game's style
// With the game-style menu on, the screens before the game boots look like the game: once this browser has the game's
// font for the cached ROM (GameFont.save: kept when a game-style menu first opened in a game), the Press Start screen is
// drawn on #gboot (inside the picture box, under the menus) in the game's font: CONKER'S in the game's yellow, BAD FUR
// DAY in its red, PRESS START pulsing, ANOTHER ROM, the footer's button faces, over a warm dark backdrop. The same
// backdrop (without the texts) is behind the ONLINE pages before boot (body.gmenu, P365), which were drawn over black.
// No title art: P368 found no cheap, reliable moment to take a clean picture of the title from the game's canvas (the
// menu record g_menu_state's page byte already reads "slot page" during the intro cutscene and its fade word read 0, and
// on the slot page the game draws its own texts into the same frame); decoding the title's models from the ROM is not
// cheap, and nothing ROM-derived may ship. Without the font (first visit, another browser) the page's own
// screens stay, clean and dark by CSS (body.gboot). Page-only: nothing here touches the game.
const GBoot = (() => {
  const cv = document.getElementById('gboot');
  const B = { raf: 0, t0: performance.now(), hits: [], sel: 0, mode: '' };
  const C = { title: 'rgb(255,50,50)', on: 'rgb(255,255,0)', text: '#ffffff', dim: 'rgb(170,170,170)' };
  const sha = () => (typeof romSha1 !== 'undefined' ? romSha1 : null);
  const fontOk = () => GameFont.ready() || (!!sha() && GameFont.restore(sha()));
  // which screen: 'ready' (the Press Start screen), 'menu' (the game-style menu before boot: only the backdrop), ''
  function mode() {
    if (running || typeof romOk === 'undefined' || !romOk || !fontOk()) return '';
    if (window.GMenu && GMenu.isOpen) return 'menu';
    return !$('ready').hidden ? 'ready' : '';
  }
  function tick() {
    const m = mode();
    document.body.classList.add('gboot');   // P369: always (was: option nativemenu)
    document.body.classList.toggle('gbootfont', m === 'ready');
    if (m !== B.mode) { B.mode = m; cv.hidden = !m; if (m) { B.t0 = performance.now(); log(`[gboot] ${m === 'ready' ? 'Press Start' : 'menu backdrop'} in the game's style`); } }
    if (m && !B.raf) B.raf = requestAnimationFrame(draw);
  }
  function draw() {
    B.raf = 0;
    if (!B.mode) return;
    B.raf = requestAnimationFrame(draw);
    const r = cv.getBoundingClientRect(), dpr = Math.min(2, window.devicePixelRatio || 1);
    const w = Math.max(1, Math.round(r.width * dpr)), h = Math.max(1, Math.round(r.height * dpr));
    if (cv.width !== w || cv.height !== h) { cv.width = w; cv.height = h; }
    const k = h / 240, W = w / k, ox = (W - 320) / 2, ctx = cv.getContext('2d'), now = performance.now();
    const fade = Math.min(1, (now - B.t0) / 300);
    const T = (s, x, y, o) => GameFont.draw(ctx, s, ox + x, y, k, Object.assign({ smooth: !!opt('smoothfont') }, o, { alpha: (o && o.alpha !== undefined ? o.alpha : 1) * fade }));
    ctx.fillStyle = '#000'; ctx.fillRect(0, 0, w, h);
    {   // a warm glow in the middle, like the game's firelit title (no picture of it: see above)
      const g = ctx.createRadialGradient(w / 2, h * 0.45, 0, w / 2, h * 0.45, h * 0.75);
      g.addColorStop(0, `rgba(70,40,12,${0.9 * fade})`); g.addColorStop(1, 'rgba(0,0,0,1)'); ctx.fillStyle = g; ctx.fillRect(0, 0, w, h);
    }
    B.hits = [];
    if (B.mode !== 'ready') return;
    ctx.fillStyle = 'rgba(0,0,0,0.35)'; ctx.fillRect(0, 0, w, h);
    const band = (y, hh, a) => {
      const g = ctx.createLinearGradient((ox + 10) * k, 0, (ox + 310) * k, 0);
      g.addColorStop(0, 'rgba(20,10,4,0)'); g.addColorStop(0.15, `rgba(20,10,4,${a * fade})`); g.addColorStop(0.85, `rgba(20,10,4,${a * fade})`); g.addColorStop(1, 'rgba(20,10,4,0)');
      ctx.fillStyle = g; ctx.fillRect((ox + 10) * k, y * k, 300 * k, hh * k);
    };
    band(14, 50, 0.6);
    T("CONKER'S", 160, 18, { scale: 1.2, color: C.on, align: 'center' });
    T('BAD FUR DAY', 160, 34, { scale: 2, color: C.title, align: 'center' });
    const pulse = 0.55 + 0.45 * Math.sin(now / 260);
    band(142, 22, 0.55);
    T('PRESS START', 160, 146, { scale: 1.4, color: C.on, align: 'center', alpha: pulse });
    B.hits.push({ act: 'start', x0: ox + 70, x1: ox + 250, y0: 140, y1: 166 });
    const aw = GameFont.measure('ANOTHER ROM', 0.75), hov = B.sel === 1;
    if (hov) { ctx.fillStyle = `rgba(255,60,30,${0.28 * fade})`; ctx.fillRect((ox + 160 - aw / 2 - 8) * k, 176 * k, (aw + 16) * k, 12 * k); }
    T('ANOTHER ROM', 160, 178, { scale: 0.75, color: hov ? C.text : C.dim, align: 'center' });
    B.hits.push({ act: 'rom', x0: ox + 160 - aw / 2 - 8, x1: ox + 160 + aw / 2 + 8, y0: 174, y1: 190 });
    // footer: the buttons, as on the game-style menu's (not with the touch controls: their shoulder buttons and Start
    // lie over the picture's bottom edge there, and a tap on PRESS START plays)
    if (document.body.classList.contains('touch')) return;
    const FY = 222, FS = 0.55;
    ctx.fillStyle = `rgba(0,0,0,${0.4 * fade})`; ctx.fillRect((ox + 20) * k, (FY - 4) * k, 280 * k, 15 * k);
    GFace.round(ctx, T, k, ox, 34, FY, 'S', 'rgb(200,40,40)', fade); T('PLAY', 42, FY + 1, { scale: FS, color: C.dim });
    T('ESC OR HOLD BACK: OPTIONS', 290, FY + 1, { scale: FS, color: C.dim, align: 'right' });
  }
  // mouse / touch on the Press Start screen (#ready lies over the window: its own elements are hidden, gbootfont)
  function hit(e) {
    const r = cv.getBoundingClientRect(); if (!r.height) return null;
    const k = r.height / 240, x = (e.clientX - r.left) / k, y = (e.clientY - r.top) / k;
    return B.hits.find((t) => x >= t.x0 && x <= t.x1 && y >= t.y0 && y <= t.y1) || null;
  }
  $('ready').addEventListener('click', (e) => {
    if (B.mode !== 'ready') return;
    const t = hit(e);
    if (t && t.act === 'rom') { snd('choose'); $('ready-rom').click(); }
    else if (t) start('game');
  });
  $('ready').addEventListener('pointermove', (e) => { if (B.mode === 'ready') { const t = hit(e); B.sel = t && t.act === 'rom' ? 1 : 0; $('ready').style.cursor = t ? 'pointer' : ''; } });
  setInterval(tick, 250);
  return { tick, get mode() { return B.mode; } };
})();
window.GBoot = GBoot;

// ---------------------------------------------------------------- P367 the game's menu sounds (GMenu, GPhoto, GNet)
// The game's own menus have three sounds (game_eu_20B730.c): 0x62D the pause menu's / save slot pages' cursor, 0x500
// choose, 0x4FF the settings list's move / value change (B is silent there). GSound plays them for the game-style
// menus: move = 0x62D, choose = 0x500, change = 0x4FF; back and error, which the game never needed, are the same
// sounds lower (back = choose 5 semitones down, error = the change blip 10 semitones down).
// Not through the game's sound player (sound_play_2d): its voices, event queue and bank cache are game memory, hashed
// online, checked by replays and restored by photo mode; and the game's AudioContext is suspended while the page pauses
// the game for this menu. Instead port/ultra/pc_sfx.c port_sfx_decode reads the sound's record and VADPCM samples from
// the player's ROM (read-only: nothing in game memory changes; decoded again for every sound, kept nowhere) and hands
// the page float PCM with the game's volume (sample / envelope / the sound group's level = the game's and the port's
// sound-effects volume); the page plays it on its own small AudioContext through the master volume (window.portVolume:
// the drawer slider / Sound > Master volume; ?mute=1 keeps it 0 = no sound at all).
// Silent (and never decoding) during an online session or while one is set up, a recording / replay and under
// ?netdet, whatever the option says, so those runs cannot change through it; also before the game runs (no bank).
// Test aid: with ?audprobe=1 an AnalyserNode after the gain measures each sound's output peak ("[gsound] heard ...").
const GSound = (() => {
  const KIND = { move: [0x62D, 0x5DC0, 0], choose: [0x500, 0x5DC0, 0], change: [0x4FF, 0x4650, 0],
    back: [0x500, 0x4650, -500], error: [0x4FF, 0x5DC0, -1000] };   // [game sound id, play volume (of 0x7FFF), cents]
  const S = { ctx: null, gain: null, an: null, live: [], n: { played: 0, silent: 0, muted: 0, none: 0 }, last: '' };
  const silentWhy = () => (netCfg ? 'online session' : window.PortNet && PortNet.t && PortNet.t.role ? 'online room'
    : recCfg ? (recCfg.mode === 'replay' ? 'replay' : 'recording') : NETDET ? 'netdet' : '');
  function buffer(kind) {
    const [id, vol, cents] = KIND[kind];
    const n = M._port_sfx_decode(id, cents);   // every time (a few thousand frames): follows the sound-effects volume
    if (!n) return null;   // the bank is not loaded yet (boot): try again next time
    const inf = new Float32Array(M.HEAPU8.buffer, M._port_sfx_info(), 4), pcm = new Float32Array(M.HEAPU8.buffer, M._port_sfx_pcm(), n);
    const b = S.ctx.createBuffer(1, n, Math.max(3000, Math.min(96000, Math.round(inf[0]))));
    const d = b.getChannelData(0), g = vol / 0x7FFF;
    for (let i = 0; i < n; i++) d[i] = pcm[i] * g;
    return b;
  }
  function measure(kind, t0) {   // ?audprobe: the loudest output sample over the sound's length
    const a = new Float32Array(S.an.fftSize);
    let peak = 0, polls = 0;
    const id = setInterval(() => {
      S.an.getFloatTimeDomainData(a);
      for (const v of a) peak = Math.max(peak, Math.abs(v));
      if (++polls >= 16) { clearInterval(id); log(`[gsound] heard ${kind}: output peak ${peak.toFixed(3)} (context ${S.ctx.state}, ${Math.round(performance.now() - t0)} ms)`); }
    }, 25);
  }
  function play(kind) {
    if (!KIND[kind]) return;
    const why = silentWhy();
    if (why) { if (S.n.silent++ < 3) log(`[gsound] silent (${why}): ${kind}`); return; }
    if (!(window.portVolume > 0)) { S.n.muted++; return; }   // ?mute=1 / master volume 0: nothing is decoded or played
    if (typeof M === 'undefined' || !M || !M._port_sfx_decode || running !== 'game') { S.n.none++; return; }
    try {
      if (!S.ctx) {
        const C = window.AudioContext || window.webkitAudioContext;
        S.ctx = new C(); S.gain = S.ctx.createGain(); S.gain.connect(S.ctx.destination);
        if (window.audprobe) { S.an = S.ctx.createAnalyser(); S.an.fftSize = 2048; S.gain.disconnect(); S.gain.connect(S.an); S.an.connect(S.ctx.destination); }
      }
      if (S.ctx.state !== 'running') S.ctx.resume().catch(() => {});
      const b = buffer(kind);
      if (!b) { S.n.none++; return; }
      S.gain.gain.value = window.portVolume;
      S.live = S.live.filter((x) => !x.done);
      if (S.live.length >= 4) { const o = S.live.shift(); try { o.stop(); } catch (e) { /* ended */ } }   // never a pile of clicks
      const src = S.ctx.createBufferSource();
      src.buffer = b; src.connect(S.gain); src.onended = () => { src.done = true; };
      src.start(); S.live.push(src);
      S.n.played++; S.last = kind;
      if (window.audprobe) {   // + roughness = mean |x[i] - x[i-1]| / mean |x| (white noise ~1.4, a decoded tone far less)
        const d = b.getChannelData(0); let sa = 0, sd = 0;
        for (let i = 1; i < d.length; i++) { sa += Math.abs(d[i]); sd += Math.abs(d[i] - d[i - 1]); }
        log(`[gsound] play ${kind} 0x${KIND[kind][0].toString(16).toUpperCase()} (${b.length} frames at ${b.sampleRate} Hz, volume ${window.portVolume}, roughness ${(sd / (sa || 1)).toFixed(2)})`);
        measure(kind, performance.now());
      }
    } catch (e) { if (S.n.none++ < 3) log(`[gsound] ${e}`); }
  }
  const stats = () => Object.assign({ last: S.last, ctx: S.ctx ? S.ctx.state : 'none' }, S.n);
  return { play, stats, silentWhy };
})();
window.GSound = GSound;
const snd = (kind) => GSound.play(kind);

// ---------------------------------------------------------------- the overlay
const GMenu = (() => {
  const U = { open: false, t0: 0, closing: 0, stack: [], hits: [], raf: 0, paused: false,
    prev: 0, repeatAt: 0, held: 0, helpPage: 0, helpAt: 0, helpSel: '', homePrev: false, mx: -1, my: -1,
    cap: null, note: '', noteAt: 0, eh: false, ehT: 0, ehUsed: false, from: '', row: -1,
    pre: false, saved: false, keepAt: 0, keepSig: '', busy: '', err: '', errAt: 0, pick: { code: '', cx: 0, cy: 0 } };   // P365: pre = opened before boot; busy / err / pick: the ONLINE pages
  const cv = document.getElementById('gmenu');
  const ROW = 15, ROWS = 8, TOP = 46, X0 = 34, X1 = 286;   // row spacing / visible rows / list top / label x / value right edge (units)
  // P363 / P364: opened from an OPTIONS row in the game's own menus: the last row of the main page goes back there
  const BACK = { pause: ['Back to pause', 'Close this menu and go back to the game\'s pause menu (B, Esc or Start on this line).'],
    title: ['Back to title', 'Close this menu and go back to the title menu (B, Esc or Start on this line).'],
    pre: ['Back to the start screen', 'Close this menu (B, Esc or Start on this line); then Start boots the game.'] };
  const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', off: 'rgb(170,170,170)', dim: 'rgb(150,150,150)', lock: 'rgb(120,120,120)', head: 'rgb(255,200,60)' };
  const smooth = () => !!opt('smoothfont');
  const page = () => U.stack[U.stack.length - 1];

  // pages: main (preset, sections, saves, fullscreen, photo / online / record, tools, page menu, back to game), one per
  // section (Controls and Sound get page-side rows too) and P362's Keyboard keys / Gamepad buttons / Saves pages
  const activated = () => !navigator.userActivation || navigator.userActivation.isActive;   // file pickers and fullscreen need a key press or click (a gamepad press is no user gesture)
  const GESTURE = 'The browser allows this only right after a key press or a click: press Enter or click this line.';
  // a tool row: turns its option on if needed, then opens its panel / flow (lockReason: online, recording)
  // (lock: a function giving the reason it cannot open now, default the option's lockReason)
  function toolAction(key, label, help, go, lock) {
    const o = OPTIONS.find((x) => x.key === key);
    const why = lock || (() => (o ? MenuModel.lockReason(o) : ''));
    return { kind: 'action', label, help, locked: why,
      act: () => {
        if (why()) return;
        if (o && !opt(key)) { setOption(o, true); optionPicked(o); showOptionValue(o); log(`[options] ${key} on (game menu)`); }
        close(); go();
      } };
  }
  function mainItems() {
    return [MenuModel.presetItem()].concat(MenuModel.sections().filter((s) => s.id !== 'tools').map((s) => ({ kind: 'link', label: s.label, help: s.help, page: s.id })), [
      { kind: 'link', label: 'Saves', help: 'Your save is kept in this browser automatically. Export it to a file or import one.', page: 'saves' },
      { kind: 'toggle', label: 'Fullscreen', help: 'The whole screen (also F11, Alt+F or a double click on the picture). In fullscreen Esc leaves fullscreen: open this menu with the corner button or the gamepad.',
        get: () => !!document.fullscreenElement, set: () => { if (!activated()) { note(GESTURE); return false; } fullscreen(); return true; } },
      toolAction('photomode', 'Photo mode', 'Freeze the game and move a free camera; A saves a picture, Start leaves (P or a short press of the gamepad\'s Back button also start it). Single player only.', () => setTimeout(() => photoRequest(true), 50)),
      // P365: the ONLINE pages (were: the page panel); during a session: the players, pings and Leave
      { kind: 'action', label: 'Online', help: 'Play a multiplayer match with friends on their own computers: make a room or join one with its 5-letter code.',
        locked: () => (recCfg || (NETDET && !netCfg) ? 'Not during a recording.' : ''),
        act: () => {
          const o = OPTIONS.find((x) => x.key === 'online');
          if (o && !opt('online')) { setOption(o, true); optionPicked(o); showOptionValue(o); log('[options] online on (game menu)'); }
          go('online');
        } },
      toolAction('recorder', 'Record', 'The input recorder: record a play session from power-on for the developers\' automatic replay tests (opens the page panel).', () => { drawerSet(true); toggle('rec', true); recShowList(); },
        () => (netCfg ? 'Not during an online session.' : '')),   // while recording: Stop and save
      { kind: 'link', label: 'Tools', help: MenuModel.sections().find((s) => s.id === 'tools').help, page: 'tools' },
      // P368: the page drawer is the developer menu now (debug console, recorder details, manual online codes)
      { kind: 'action', label: 'Developer tools', help: 'The page\'s developer menu: the debug console, the input recorder\'s details and the manual (copy-paste) online codes. Players never need it.', act: () => { close(); drawerSet(true); } },
      { kind: 'action', get label() { return BACK[backKey()] ? BACK[backKey()][0] : 'Back to game'; }, get help() { return BACK[backKey()] ? BACK[backKey()][1] : 'Close this menu (B, Esc or Start on this line).'; }, act: () => { snd('back'); close(); } },
    ]);
  }
  // key / button binding rows (INPUTS, keyMap, padMap, keyName, padName, bindSet, bindReset: main.js)
  const STICK_IDS = ['UP', 'DOWN', 'LEFT', 'RIGHT', 'HALF'];
  function bindItems(kind) {
    const rows = INPUTS.map(([id, label]) => {
      const stick = kind === 'pad' && STICK_IDS.includes(id);
      return { kind: 'bind', bkind: kind, id, label,
        help: stick ? 'The gamepad\'s left stick (half tilt: tilt it less).'
          : kind === 'key' ? 'Choose, then press the new key: Esc cancels, Backspace leaves it unbound. A key does one thing: it leaves its old input.'
          : 'Choose, then press the new button on the gamepad (nothing for 6 s, or Esc: cancel). A button does one thing: it leaves its old input.' + (id === 'PHOTO' ? ' Holding this button for half a second also opens this menu.' : ''),
        locked: () => (stick ? 'The left stick.' : ''),
        value: () => (stick ? (id === 'HALF' ? '-' : 'LEFT STICK') : kind === 'key' ? keyName(keyMap[id]) : padName(padMap[id])) };
    });
    return rows.concat([
      { kind: 'action', label: 'Defaults (keys and buttons)', help: 'Every key and gamepad button back to its default.', act: () => { bindReset(); note('Keys and buttons are back to the defaults.'); } },
      { kind: 'action', label: 'Back', help: 'Back to the controls.', act: () => back() },
    ]);
  }
  // P368: which gamepads the browser sees (the drawer's Controls panel listed them): an information row, no action
  function padsItem() {
    const gps = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).filter((g) => g && g.connected);
    return { kind: 'info', label: 'Connected gamepads', value: () => (gps.length ? String(gps.length) : 'NONE'),
      help: gps.length ? gps.map((g, i) => `Pad ${i + 1}: ${g.id.replace(/\s*\(.*$/, '').slice(0, 40)}${g.mapping === 'standard' ? '' : ' (non-standard mapping: rebind its buttons here)'}.`).join(' ')
        : 'No gamepad yet: connect one and press a button on it (browsers only show a gamepad after a press).' };
  }
  const backKey = () => (U.pre ? 'pre' : U.from);
  const go = (id) => { U.stack.push({ id, sel: 0, top: 0 }); U.helpSel = ''; U.note = ''; U.err = ''; };
  function itemsOf(p) {
    if (p.id === 'main') return mainItems();
    if (p.id === 'online') return onlineItems();
    if (p.id === 'pick') return [];
    if (p.id === 'keys') return bindItems('key');
    if (p.id === 'pad') return [padsItem()].concat(bindItems('pad'));   // P368: the connected pads (were: the drawer's Controls panel)
    const backRow = { kind: 'action', label: 'Back', help: 'Back to the customisation settings.', act: () => back() };
    if (p.id === 'saves') return [
      { kind: 'action', label: 'Export save', help: 'Download your save as a file (conker-eu-slot0.eep) to keep it or move it to another browser.', act: () => $('eep-export').click() },
      { kind: 'action', label: 'Import save', help: 'Replace this browser\'s save with a .eep file (the game restarts to read it). ' + GESTURE.replace('this', 'the file picker'),
        locked: () => (netCfg || recCfg || NETDET ? 'Not during an online session or a recording.' : ''),
        act: () => { if (netCfg || recCfg || NETDET) return; if (!activated()) { note(GESTURE); return; } $('eep-import').click(); } },
      backRow,
    ];
    const s = MenuModel.sections().find((x) => x.id === p.id);
    let pre = [];
    if (p.id === 'controls') pre = [
      { kind: 'link', label: 'Keyboard keys', help: 'Which key does what.', page: 'keys' },
      { kind: 'link', label: 'Gamepad buttons', help: 'Which gamepad button does what (the left stick is the N64 stick, the right stick the C buttons or the free camera).', page: 'pad' },
      { kind: 'toggle', label: 'Touch controls', help: 'On-screen stick and buttons for phones and tablets (they show by themselves on a touch screen).',
        get: () => !$('touch').hidden, set: () => { $('t-touch').click(); return true; } },
    ];
    else if (p.id === 'sound') pre = [
      { kind: 'range', label: 'Master volume', help: 'The volume of everything (this browser only; online each player has their own).',
        locked: () => (Q.get('mute') ? 'Muted for this test run (?mute=1).' : ''),
        get: () => Math.round(window.portVolume * 100), set: (v) => setVolume(Math.round(v / 5) * 5) },
    ];
    return pre.concat(s.items, [backRow]);
  }
  const TITLES = { main: 'Customisation settings', keys: 'Keyboard keys', pad: 'Gamepad buttons', saves: 'Saves', online: 'Online', pick: 'Join room' };
  const titleOf = (p) => TITLES[p.id] || MenuModel.sections().find((x) => x.id === p.id).label;
  // a short message in the help box (save export / import results, gesture hints)
  function note(s) { U.note = String(s || ''); U.noteAt = performance.now(); }

  // the font: from the running game, else (before boot) the copy kept for this ROM (GameFont.save / restore)
  const fontOk = () => GameFont.load() || (typeof romSha1 !== 'undefined' && GameFont.restore(romSha1));
  function open(how) {
    if (U.open || typeof running === 'undefined') return false;
    // P365: also before boot (the Press Start screen, a good ROM, the font kept from an earlier run): the ONLINE pages
    // must run there, because an online match starts from power-on
    const pre = !running;
    if (pre ? !romOk : running !== 'game') return false;
    if (photo.state === 2 || !fontOk()) return false;   // photo mode has the pad; no font yet: the drawer instead
    if (!pre && !U.saved) U.saved = GameFont.save(romSha1);   // P365: for the ONLINE pages before the next boot
    U.open = true; U.t0 = performance.now(); U.closing = 0; U.stack = [{ id: 'main', sel: 0, top: 0 }];
    U.prev = -1; U.held = 0; U.helpSel = ''; U.cap = null; U.note = ''; U.err = '';
    U.pre = pre; U.from = BACK[how] && how !== 'pre' ? how : '';
    document.body.classList.add('gmenu'); cv.hidden = false;
    // single player: pause like the drawer (never online, never while recording or replaying). P363: opened from the
    // game's own pause menu (its OPTIONS row) the game is paused already and keeps running its pause menu underneath
    // (with an idle pad 1), so the page does not pause on top. P364: opened from the title menu's OPTIONS row the page
    // does not pause either: the title (music, Conker's animation, the 3D scene) keeps running with an idle pad 1
    if (!U.from && !pre && !netCfg && !recCfg && !NETDET && !userPaused) { U.paused = true; setPaused(true); }
    if (document.pointerLockElement && document.exitPointerLock) document.exitPointerLock();
    log(`[gmenu] open${U.from ? ` (from the game's ${U.from} menu)` : ''}${pre ? ' (before boot)' : ''}`);
    if (!U.from) snd('choose');   // P367 (from a game row the game played its own choose sound)
    frame();
    return true;
  }
  function close() {
    if (!U.open) return;
    U.open = false; U.cap = null; U.pre = false;
    document.body.classList.remove('gmenu'); cv.hidden = true;
    if (U.paused && userPaused) setPaused(false);
    U.paused = false;
    keysDown.clear();
    photo.maskB = 0xFFFF; photo.maskStick = true;   // held buttons / stick reach the game only once released (photoMaskAfter)
    $('canvas').focus();
    log('[gmenu] close');
  }
  function back() { U.note = ''; snd('back'); if (U.stack.length > 1) { U.stack.pop(); U.helpSel = ''; } else close(); }

  // ---- P365 the ONLINE pages (docs/design/NATIVE_MENUS.md section 7, docs/design/ONLINE_MULTIPLAYER.md section 11).
  // Every step calls the same functions as the page panel's buttons (main.js netRoomCreate / netRoomJoin / netStartGame
  // / netLeave -> window.__online -> net.js), so the panel and these pages are one path (netpair.sh UI=1 tests the panel,
  // UI=gmenu these pages). An online match starts from power-on on every computer, so a room is made / joined before the
  // game boots: chosen during a game, the page reloads first (sessionStorage 'gmenu.online' = the step to continue with)
  // and these pages open by themselves on the Press Start screen, drawn with the font kept by GameFont.save. Nothing
  // here writes game memory: before boot there is none, during a session the pages only read net.js's state.
  // The room code alphabet of the room server (port/web/netlify/functions/room/core.mjs: no 0/O 1/I/L 2/Z 5/S 6/G 8/B)
  const ALPHA = 'ACDEFHJKMNPQRTUVWXY3479', PCOLS = 8, PROWS = 3;   // letter picker: 3 rows of 8 (the last cell = DEL) + JOIN
  const pickCell = (cx, cy) => (cy >= PROWS ? 'JOIN' : cy * PCOLS + cx < ALPHA.length ? ALPHA[cy * PCOLS + cx] : 'DEL');
  const NT = () => (window.PortNet && PortNet.t) || null;   // net.js's session state
  // setup (no room yet), host / guest (in a room, before the start), session (the game runs online)
  function onlineState() {
    const t = NT();
    if (netCfg || (t && t.started)) return 'session';
    if (t && t.role) return t.role;
    return 'setup';
  }
  function fail(e) { U.err = String((e && e.message) || e || ''); U.errAt = performance.now(); U.helpSel = ''; snd('error'); log(`[gmenu] online: ${U.err}`); }
  async function reloadInto(step) {   // during a game: restart the page into the ONLINE page's step
    if (!GameFont.save(romSha1)) { note('This browser keeps no data for this page: reload it, then open the customisation settings (Esc) before pressing Start.'); return; }
    try { sessionStorage.setItem('gmenu.online', step); } catch (e) { note('This browser keeps no data for this page: reload it, then open the customisation settings (Esc) before pressing Start.'); return; }
    U.busy = 'reload'; note('Restarting the game for the online match…');
    log(`[gmenu] online: reloading the page into the ONLINE page (${step})`);
    if (typeof eepTimer !== 'undefined' && eepTimer) { clearTimeout(eepTimer); try { await persistEeprom(); } catch (e) { /* logged */ } }   // a save still waiting to be written
    setTimeout(() => location.reload(), 150);
  }
  async function onlineCreate() {
    if (U.busy) return;
    U.busy = 'create'; U.err = '';
    const e = await netGuard(netRoomCreate);
    U.busy = '';
    if (e) fail(e); else log(`[gmenu] online: room ${$('net-room-show').textContent} made`);
  }
  async function onlineJoin() {
    const code = U.pick.code;
    if (U.busy) return;
    if (code.length < 5) { fail('The room code has 5 letters.'); return; }
    U.busy = 'join'; U.err = '';
    log(`[gmenu] online: joining room ${code} (letter picker)`);
    const e = await netGuard(() => netRoomJoin(code));
    U.busy = '';
    if (e) { fail(e); return; }
    if (page().id === 'pick') { U.stack.pop(); U.helpSel = ''; }   // the ONLINE page shows the room now
  }
  async function onlineStart() {
    if (U.busy) return;
    U.busy = 'start'; U.err = '';
    log('[gmenu] online: start');
    const e = await netGuard(netStartGame);
    if (e) { U.busy = ''; fail(e); }   // else busy until the game boots (the menu closes then)
  }
  function onlineLeave() {
    const st = onlineState();
    log(`[gmenu] online: leave (${st})`);
    netLeave();
    if (st !== 'session') { U.busy = 'reload'; note('Leaving the room…'); setTimeout(() => location.reload(), 400); }   // a clean page for the next room
  }
  const joinedCount = () => (window.PortNet ? PortNet.slots().filter((x) => x.state === 'joined').length : 0);
  function delayItem() {   // the panel's input delay ("automatic" box + frames field), read by netSessionConfig at Start
    const CH = ['auto', '2', '3', '4', '5', '6', '8'];
    return { kind: 'choice', label: 'Input delay', choices: CH, all: CH,
      help: 'How far ahead each computer sends its buttons (1 frame = 20 ms). Automatic measures the ping at the start; more delay hides a slow connection, less feels quicker. Player 1 chooses.',
      locked: () => (onlineState() === 'guest' || onlineState() === 'session' ? 'Player 1 (the host) chooses the input delay.' : ''),
      get: () => ($('net-delay-auto').checked ? 'auto' : String($('net-delay').value)),
      names: (v) => (v === 'auto' ? 'AUTOMATIC' : `${v} (${v * 20} MS)`),
      set: (v) => {
        $('net-delay-auto').checked = v === 'auto'; $('net-delay-auto').onchange();
        if (v !== 'auto') { $('net-delay').value = v; $('net-delay').onchange(); }
        return true;
      } };
  }
  function onlineItems() {
    const st = onlineState(), t = NT(), backRow = { kind: 'action', label: 'Back', help: 'Back to the customisation settings (a room stays open).', act: () => back() };
    const busy = (what) => () => (U.busy === what ? 'One moment…' : U.busy ? 'One moment…' : '');
    if (st === 'setup') {
      const ingame = !!running;
      const restart = ingame ? ' The game restarts first: an online match starts from power-on on every computer (your save is kept).' : '';
      return [
        { kind: 'action', label: 'Create room', help: 'Make a room for 2 to 4 players: you are player 1 and get a 5-letter code to give your friends.' + restart,
          locked: busy('create'), act: () => (ingame ? reloadInto('create') : onlineCreate()) },
        { kind: 'action', label: 'Join room', help: 'Join a friend\'s room with the 5-letter code they give you (pick the letters with the pad or type them).' + restart,
          locked: busy('join'), act: () => (ingame ? reloadInto('join') : (U.pick = { code: '', cx: 0, cy: 0 }, go('pick'))) },
        delayItem(),
        { kind: 'action', label: 'Manual codes (developer tools)', help: 'Advanced: connect without the room server by copying long codes between the players (the Online panel of the page\'s developer tools).' + restart,   // P368: was "Manual codes (page menu)"
          locked: busy('x'), act: () => {
            if (ingame) { reloadInto('manual'); return; }
            close(); drawerSet(true); toggle('online', true); $('net-manual').checked = true; $('net-manual').onchange();
          } },
        backRow,
      ];
    }
    if (st === 'host') {
      const n = joinedCount();
      return [
        { kind: 'action', get label() { return n ? `Start the game (${n + 1} players)` : 'Start the game'; },
          help: 'Everyone in the room boots the game together; player 1 leads the menus. Nobody can join after this.',
          locked: () => (U.busy === 'start' ? 'Starting…' : !n ? 'Wait until another player joined the room.' : ''), act: onlineStart },
        delayItem(),
        { kind: 'action', label: 'Leave the room', help: 'Close the room (the players in it are told) and start over.', act: onlineLeave },
        backRow,
      ];
    }
    if (st === 'guest') return [
      { kind: 'action', label: 'Leave the room', help: 'Leave this room and start over.', act: onlineLeave },
      backRow,
    ];
    return [   // session
      { kind: 'action', label: 'Leave the session', help: 'Stop playing online: the others go on without you (your controller stands still for them).',
        locked: () => (t && (t.quit || t.left) ? 'You are no longer in the session.' : ''), act: onlineLeave },
      backRow,
    ];
  }
  // the picker's input: a cell, typing, delete, join
  function pickType(c) {
    const P = U.pick;
    if (U.busy) return;
    U.err = '';
    if (P.code.length >= 5) { P.cx = 0; P.cy = PROWS; snd('error'); return; }
    P.code += c; snd('choose');
    if (P.code.length === 5) { P.cx = 0; P.cy = PROWS; }   // the code is complete: on JOIN
  }
  function pickDelete() { if (U.busy) return false; U.err = ''; if (!U.pick.code) return false; U.pick.code = U.pick.code.slice(0, -1); snd('back'); return true; }
  function pickChoose() {
    const c = pickCell(U.pick.cx, U.pick.cy);
    if (Q.get('gmenutest')) log(`[gmenu] picker: ${c} (code ${U.pick.code})`);
    if (c === 'JOIN') onlineJoin(); else if (c === 'DEL') pickDelete(); else pickType(c);
  }
  function pickMove(dx, dy) {
    const P = U.pick, was = P.cx + ',' + P.cy;
    if (dy) P.cy = (P.cy + dy + PROWS + 1) % (PROWS + 1);
    if (dx && P.cy < PROWS) P.cx = (P.cx + dx + PCOLS) % PCOLS;
    if (P.cx + ',' + P.cy !== was) snd('move');
  }
  function pickKey(e) {   // keyboard on the picker: letters / digits type (others are refused), Backspace deletes
    const k = e.key && e.key.length === 1 ? e.key.toUpperCase() : '';
    if (e.ctrlKey || e.metaKey || e.altKey) return false;   // Ctrl+V: the paste event below
    if (k && /[A-Z0-9]/.test(k)) {
      if (!e.repeat) { if (ALPHA.includes(k)) pickType(k); else fail(`Room codes have no ${k} (they use ${ALPHA.split('').join(' ')}).`); }
      return true;
    }
    if (e.code === 'Backspace') { if (!e.repeat && !pickDelete()) back(); return true; }
    if (e.code === 'Escape') { if (!e.repeat) back(); return true; }
    if (e.code === 'Enter' || e.code === 'NumpadEnter') { if (!e.repeat) { if (U.pick.code.length === 5) onlineJoin(); else pickChoose(); } return true; }
    if (e.code === 'ArrowUp') pickMove(0, -1); else if (e.code === 'ArrowDown') pickMove(0, 1);
    else if (e.code === 'ArrowLeft') pickMove(-1, 0); else if (e.code === 'ArrowRight') pickMove(1, 0);
    else return /^(Key|Digit|Numpad)/.test(e.code);   // no game keys while typing a code
    return true;
  }
  window.addEventListener('paste', (e) => {
    if (!U.open || page().id !== 'pick' || U.busy) return;
    const t = (e.clipboardData && e.clipboardData.getData('text')) || '';
    const c = t.toUpperCase().split('').filter((x) => ALPHA.includes(x)).join('').slice(0, 5);
    if (c) { e.preventDefault(); U.pick.code = ''; for (const x of c) pickType(x); }
  });
  // after the reload: continue with the step chosen during the game (on the Press Start screen, with a good ROM)
  function pendingOnline() {
    if (U.open || running || !romOk || typeof romSha1 === 'undefined' || !romSha1) return;
    let step = null;
    try { step = sessionStorage.getItem('gmenu.online'); } catch (e) { return; }
    if (!step) return;
    try { sessionStorage.removeItem('gmenu.online'); } catch (e) { /* ignore */ }
    log(`[gmenu] online: after the reload: ${step}`);
    if (step === 'manual') { drawerSet(true); toggle('online', true); $('net-manual').checked = true; $('net-manual').onchange(); return; }
    if (!open('pre')) { drawerSet(true); toggle('online', true); return; }   // no font kept: the page panel
    go('online');
    if (step === 'create') onlineCreate();
    else if (step === 'join') { U.pick = { code: '', cx: 0, cy: 0 }; go('pick'); }
  }

  // ---- actions on the selected item
  function moveSel(d) {
    const p = page(), n = itemsOf(p).length;
    if (!n) return;   // P365: the letter picker has no rows
    const was = p.sel;
    p.sel = (p.sel + d + n) % n;
    if (p.sel !== was) snd('move');
  }
  function change(item, d) {   // left / right
    if (!item) return;
    if (item.locked && item.locked()) { if (item.get) snd('error'); return; }
    if (!item.get) return;
    const was = item.get(), r = changeValue(item, d);
    // P367: refused (set returned false: fullscreen without a key press) or nothing moved (a slider at its end) = error;
    // true = done although the value shows later (fullscreen is asynchronous)
    snd(r === false || (r !== true && item.get() === was) ? 'error' : 'change');
  }
  function changeValue(item, d) {
    if (item.kind === 'toggle') return item.set(!item.get());
    if (item.kind === 'range') return item.set(item.get() + d * 5);
    if (item.kind === 'choice') { const i = item.choices.indexOf(item.get()); return item.set(item.choices[((i < 0 ? (d > 0 ? -1 : 0) : i) + d + item.choices.length) % item.choices.length]); }
  }
  function choose(item) {
    if (!item || item.kind === 'info') return;   // P368: an information row does nothing
    // P367: the choose sound (error if locked); a Back row sounds like going back (its back() plays it; "Back to game" closes)
    if (/^Back/.test(item.label)) { /* its act plays the back sound */ }
    else if (item.kind !== 'toggle' && item.kind !== 'range' && item.kind !== 'choice') snd(item.locked && item.locked() ? 'error' : 'choose');
    if (item.kind === 'link') { U.stack.push({ id: item.page, sel: 0, top: 0 }); U.helpSel = ''; U.note = ''; }
    else if (item.kind === 'bind') capture(item);
    else if (item.kind === 'action') item.act();
    else change(item, 1);
  }

  // ---- P362 key / button capture for a binding row: U.cap = { kind, id, t0, armed } until a key / button comes
  function capture(item) {
    if (item.locked && item.locked()) return;
    U.cap = { kind: item.bkind, id: item.id, t0: performance.now(), armed: false };
    log(`[gmenu] capture ${item.bkind} ${item.id}`);
  }
  function captureDone(v) {   // undefined = cancelled, null = unbound
    const c = U.cap; U.cap = null;
    if (!c || v === undefined) { note('Not changed.'); snd('back'); return; }
    bindSet(c.kind, c.id, v); snd('choose');
    note(v === null ? 'Unbound.' : `Now: ${c.kind === 'key' ? keyName(v) : padName(v)}.` + (c.kind === 'pad' && padMap.PHOTO === undefined ? ' Photo mode now has no gamepad button (holding it opened this menu): give it one again.' : ''));
    U.prev = -1;   // the capturing press does nothing in the menu
  }

  // ---- input: one call per animation frame from pollInput with pad 1 (keyboard + first gamepad + touch); true = the
  // menu has pad 1 (the game gets no buttons)
  // P362 pad entry that works in every browser (Home is often taken by the OS or the browser): hold the gamepad button
  // bound to Photo mode (Back / Select by default) for half a second. That button is a page input, never an N64 one
  // (one input per button), so holding it cannot reach the game, its lockstep input online or a recording. With this
  // menu on, a short press of it starts photo mode on release instead of on press; a press while the menu is open
  // closes it. The keyboard's Photo key keeps its own behaviour.
  const HOLD_MS = 500;
  function entry(d, raw, now) {
    const eb = padMap.PHOTO, eh = eb !== undefined && raw(eb), on = photo.state !== 2;
    if (eh && !U.eh) U.ehT = now;
    if (U.open) { if (eh && !U.eh && !U.ehUsed && !U.cap) { U.ehUsed = true; snd('back'); close(); } }
    else if (on && eh && !U.ehUsed && now - U.ehT >= HOLD_MS) { U.ehUsed = true; if (open('hold')) log('[gmenu] opened by holding the pad\'s photo button'); }
    else if (on && !eh && U.eh && !U.ehUsed && now - U.ehT < HOLD_MS) d.photo = true;   // a short press: photo mode (one frame's press)
    // the held pad button is no photo press (yet), also on the frame whose press closed the menu (pad 1 reaches photoPoll then)
    if (on && eh && !U.open) d.photo = !!(keyMap.PHOTO && keysDown.has(keyMap.PHOTO));
    if (!eh) U.ehUsed = false;
    U.eh = eh;
  }
  // P363: the "OPTIONS" row in the game's own pause menu (game_pause_update, game_eu_20B730.c); P364: the same row on
  // the title menu's save slot pages (title_slot_page) and MULTI mode pages (menu_mode_select_page). The page switches
  // the rows on (port_set_gmenu_row) only while the game is local (P369: no option any more): never online, while an
  // online session is being set up (a room / invite exists: PortNet.t.role), while recording or replaying, or under
  // ?netdet (the menus' state is hashed there; the C side checks the same again). Choosing a row leaves a request
  // (port_gmenu_take_request: 1 = pause menu, 2 = title menu) that opens this menu over the game's own menu; the A
  // press that chose it is masked by U.prev = -1 (the first poll after open only records the held buttons).
  const netBusy = () => !!(window.PortNet && PortNet.t && PortNet.t.role);
  function gameRows() {
    if (typeof M === 'undefined' || !M || !M._port_set_gmenu_row) return;
    const on = running === 'game' && !netCfg && !recCfg && !NETDET && !netBusy() ? 1 : 0;
    if (on !== U.row) { U.row = on; M._port_set_gmenu_row(on); log(`[gmenu] game menu customisation rows ${on ? 'on' : 'off'}`); }
    const req = M._port_gmenu_take_request();
    if (req && on && !U.open) {
      const how = req === 2 ? 'title' : 'pause';
      if (open(how)) log(`[gmenu] opened from the ${how} menu's customisation row`);
    }
  }
  // P369: keep the game's font for this ROM as soon as the game has booted once (P365 kept it on the first menu open), so
  // the customisation settings open on the Press Start screen of the next visit too, even for a first-time player who
  // never opened them. Checked once a second while the game runs; saved when the font reads the same twice in a row
  // (fully decoded), once per page load.
  function fontKeep(now) {
    if (U.saved || typeof running === 'undefined' || running !== 'game' || now < U.keepAt) return;
    U.keepAt = now + 1000;
    if (!GameFont.load()) { U.keepSig = ''; return; }
    if (GameFont.sig === U.keepSig && (U.saved = GameFont.save(romSha1))) log('[gmenu] game font kept for this ROM (the customisation settings can open before boot from now on)');
    U.keepSig = GameFont.sig;
  }
  function poll(d) {
    fontKeep(performance.now());
    gameRows();
    if (U.open && U.pre && running) close();   // P365: the game boots (an online match starts): the pages are done
    pendingOnline();
    const gp = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).find((g) => g && g.connected);
    const raw = (i) => !!(gp && gp.buttons[i] && (gp.buttons[i].pressed || gp.buttons[i].value > 0.5));
    const now = performance.now();
    const home = raw(16);
    if (home && !U.homePrev && !U.cap) { U.homePrev = true; if (U.open) { snd('back'); close(); } else open(); return U.open; }
    U.homePrev = home;
    entry(d, raw, now);
    if (!U.open) return false;
    if (U.cap) {   // binding capture: the menu does not move meanwhile
      if (U.cap.kind === 'pad') {
        const down = gp ? gp.buttons.map((_, i) => raw(i)) : [];
        if (!U.cap.armed) U.cap.armed = !down.some(Boolean);   // first every button up (the press that chose the row)
        else { const i = down.findIndex(Boolean); if (i >= 0) { U.ehUsed = true; captureDone(i); return true; } }   // ehUsed: the captured press (maybe the new entry button) must not close the menu
      }
      if (U.cap && now - U.cap.t0 > 6000) captureDone(undefined);
      U.prev = -1;
      return true;
    }
    const b = d.b | 0;
    let bits = 0;
    if ((b & N64.DU) || d.y > 40) bits |= 1;
    if ((b & N64.DD) || d.y < -40) bits |= 2;
    if ((b & N64.DL) || d.x < -40) bits |= 4;
    if ((b & N64.DR) || d.x > 40) bits |= 8;
    if ((b & (N64.A | N64.START)) || raw(0)) bits |= 16;
    if ((b & N64.B) || raw(1)) bits |= 32;
    if (b & N64.START) bits |= 64;   // P365: the letter picker's JOIN
    if (U.prev < 0) { U.prev = bits; return true; }   // the press that opened the menu does nothing in it
    const fresh = bits & ~U.prev;
    let dir = fresh & 15;
    if ((bits & 15) && (bits & 15) === (U.prev & 15)) { if (now >= U.repeatAt) { dir = bits & 15; U.repeatAt = now + 90; } }
    else U.repeatAt = now + 380;
    U.prev = bits;
    if (page().id === 'pick') {   // P365: the letter picker: the D-pad / stick moves over the letters, A types, B deletes, Start joins
      if (dir & 1) pickMove(0, -1); else if (dir & 2) pickMove(0, 1);
      if (dir & 4) pickMove(-1, 0); else if (dir & 8) pickMove(1, 0);
      if (fresh & 64) onlineJoin(); else if (fresh & 16) pickChoose(); else if (fresh & 32) { if (!pickDelete()) back(); }
      return true;
    }
    const item = itemsOf(page())[page().sel];
    if (dir & 1) moveSel(-1); else if (dir & 2) moveSel(1);
    if (dir & 4) change(item, -1); else if (dir & 8) change(item, 1);
    if (fresh & 16) choose(item);
    else if (fresh & 32) back();
    return true;
  }
  // keys while the menu is open (main.js keydown calls this first); true = used. The arrows, Enter, Esc and Backspace
  // always work here, whatever the bindings (P362: so a rebinding can never lock the keyboard out of the menu); other
  // bound keys (WASD, Space, F ...) reach the menu through pad 1. During a capture every key goes to the capture.
  function key(e) {
    if (!U.open) return false;
    if (U.cap) {
      if (U.cap.kind === 'key' && !e.repeat) { if (e.code === 'Escape') captureDone(undefined); else if (e.code === 'Backspace') captureDone(null); else captureDone(e.code); }
      else if (e.code === 'Escape') captureDone(undefined);
      return true;
    }
    if (page().id === 'pick') return pickKey(e);   // P365
    if (e.code === 'Escape' || e.code === 'Backspace') { if (!e.repeat) back(); return true; }
    const item = itemsOf(page())[page().sel];
    if (e.code === 'ArrowUp') moveSel(-1);
    else if (e.code === 'ArrowDown') moveSel(1);
    else if (e.code === 'ArrowLeft') change(item, -1);
    else if (e.code === 'ArrowRight') change(item, 1);
    else if (e.code === 'Enter' || e.code === 'NumpadEnter') { if (!e.repeat) choose(item); }
    else return false;
    return true;
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
    if (!fontOk()) return;
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
    const pulse = 0.75 + 0.25 * Math.sin(now / 160);
    // P365: the ONLINE pages draw the room / players above their rows; the letter picker has no rows
    const top0 = p.id === 'online' ? drawOnline(ctx, T, k, ox, now, pulse) : p.id === 'pick' ? drawPick(ctx, T, k, ox, now, pulse, fade) : TOP;
    const rows = Math.max(1, Math.floor((172 - top0) / ROW));
    if (p.sel >= items.length) p.sel = Math.max(0, items.length - 1);   // P365: the ONLINE page's rows change with the room's state
    // list (scrolls to keep the selection visible)
    if (p.sel < p.top) p.top = p.sel;
    if (p.sel >= p.top + rows) p.top = p.sel - rows + 1;
    for (let i = p.top; i < Math.min(items.length, p.top + rows); i++) {
      const it = items[i], y = top0 + (i - p.top) * ROW, sel = i === p.sel, lock = it.locked ? it.locked() : '';
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
      else if (it.kind === 'info') v = it.value();   // P368
      else if (it.kind === 'bind') {
        const cap = U.cap && U.cap.id === it.id && U.cap.kind === it.bkind;
        v = cap ? (it.bkind === 'key' ? 'PRESS A KEY' : 'PRESS A BUTTON') : it.value();
        vc = cap ? C.on : lock ? C.lock : sel ? C.text : C.dim;
        if (cap) { T(v, X1, y, { color: vc, scale: 0.85, align: 'right', alpha: pulse }); v = ''; }
      }
      if (v) {
        if (sel && !lock && (it.kind === 'range' || it.kind === 'choice')) { T('<', X1 - GameFont.measure(v, 0.85) - 9, y, { color: vc, scale: 0.85, alpha: pulse }); T('>', X1 + 4, y, { color: vc, scale: 0.85, alpha: pulse }); }
        T(v, X1, y, { color: vc, scale: 0.85, align: 'right' });
      }
    }
    if (p.top > 0) T('^', 160, top0 - 11, { color: C.dim, align: 'center', scale: 0.8 });
    if (p.top + rows < items.length) T('V', 160, top0 + rows * ROW - 2, { color: C.dim, align: 'center', scale: 0.6 });
    // help for the selected line (pages of 4 lines, turning every 5 s)
    const it = items[p.sel], lock = it && it.locked ? it.locked() : '';
    if (U.note && now - U.noteAt > 4000 && U.busy !== 'reload') U.note = '';
    // P365: on the ONLINE pages an error, else net.js's status line, comes first
    const net = p.id === 'online' || p.id === 'pick' ? U.err || (U.busy === 'create' ? 'Making the room…' : U.busy === 'join' ? 'Joining the room…' : '') || (onlineState() !== 'setup' && NT() ? NT().state : '') : '';
    const head = U.cap ? (U.cap.kind === 'key' ? 'Press the new key (Esc: cancel, Backspace: unbound).' : 'Press the new gamepad button (Esc or 6 s: cancel).') : U.note || net || lock;
    const pickHelp = p.id === 'pick' ? 'Pick the 5 letters player 1 gave you (or type them), then JOIN. A types, B deletes, Start joins.' : '';
    const itemHelp = it && !U.cap && !U.note ? (typeof it.help === 'function' ? it.help() : it.help || '') : '';
    const helpText = (head ? head + (/[.!?…:]$/.test(head) ? ' ' : '. ') : '') + (p.id === 'pick' ? (U.err ? '' : pickHelp) : itemHelp);
    const sig = p.id + ':' + p.sel + ':' + helpText;
    if (sig !== U.helpSel) { U.helpSel = sig; U.helpPage = 0; U.helpAt = now; }
    // P362: help at 0.7 (P361: 0.62, where the 3 x 3 "." of the pixel look nearly vanished: "1.5 S" read "15 S"); tiny
    // glyphs also get a minimum size in GameFont.draw
    const HS = 0.7;
    let lines = GameFont.wrap(helpText, 272, HS);
    if (lines.length > 4) lines = GameFont.wrap(helpText, 256, HS);   // leave room for the page counter
    const pages = Math.max(1, Math.ceil(lines.length / 4));
    if (now - U.helpAt > 5000) { U.helpAt = now; U.helpPage = (U.helpPage + 1) % pages; }
    ctx.fillStyle = `rgba(0,0,0,${0.35 * fade})`; ctx.fillRect((ox + 20) * k, 170 * k, 280 * k, 46 * k);
    lines.slice(U.helpPage * 4, U.helpPage * 4 + 4).forEach((l, j) => T(l, 24, 173 + j * 10.5, { scale: HS, color: head && j === 0 && U.helpPage === 0 ? C.head : C.text, alpha: 0.92 }));
    if (pages > 1) T(`${U.helpPage + 1}/${pages}`, 296, 207, { scale: 0.5, color: C.dim, align: 'right' });
    // footer: what the buttons do, with the N64's button faces drawn as shapes (blue A, green B; the D-pad's arrows) and
    // the letters in the game's font (B / CLOSE is also a mouse / touch target)
    const FS = 0.55, FY = 224;
    const btn = (x, letter, fill) => GFace.round(ctx, T, k, ox, x, FY, letter, fill, fade);   // P366: shared with GPhoto
    const arrows = (x) => GFace.dpad(ctx, k, ox, x, FY, 'lr', fade);   // a small D-pad cross with left / right arms lit
    const pk = p.id === 'pick';   // P365: the letter picker's buttons
    const bText = pk ? 'DELETE' : U.stack.length > 1 ? 'BACK' : 'CLOSE';
    btn(30, 'A', 'rgb(40,90,230)'); T(pk ? 'TYPE' : 'CHOOSE', 38, FY, { scale: FS, color: C.dim });
    const bw = GameFont.measure(bText, FS) + 14, bx = 160 - bw / 2;
    btn(bx + 5, 'B', 'rgb(30,160,60)'); T(bText, bx + 13, FY, { scale: FS, color: C.dim });
    U.hits.push({ act: 'back', x0: ox + bx - 4, x1: ox + bx + bw + 4, y0: 218, y1: 236 });
    if (pk) { const jw = GameFont.measure('JOIN', FS); btn(290 - jw - 8, 'S', 'rgb(200,40,40)'); T('JOIN', 290, FY, { scale: FS, color: C.dim, align: 'right' }); return; }
    const cw = GameFont.measure('CHANGE', FS);
    arrows(290 - cw - 8); T('CHANGE', 290, FY, { scale: FS, color: C.dim, align: 'right' });
  }
  // P365: the room code in big letters (in the game's yellow, spaced like the game's big numbers)
  function bigCode(T, code, y, scale, color) {
    const sp = 9 * scale, x0 = 160 - (sp * (code.length - 1)) / 2;
    for (let i = 0; i < code.length; i++) T(code[i], x0 + i * sp, y, { scale, color, align: 'center' });
  }
  // the ONLINE page above its rows: the room code and its players (host / guest), the session's players and pings;
  // returns the y of the first row
  function drawOnline(ctx, T, k, ox, now, pulse) {
    const st = onlineState(), t = NT(), S = 0.72, L = 74, R = 246;
    const line = (y, a, b, ca, cb) => { T(a, L, y, { scale: S, color: ca || C.text }); if (b) T(b, R, y, { scale: S, color: cb || C.dim, align: 'right' }); };
    if (st === 'setup') return TOP;
    if (st === 'host' || st === 'guest') {
      const code = t.room ? t.room.code : '';
      T('ROOM CODE', 160, 37, { scale: 0.6, color: C.dim, align: 'center' });
      bigCode(T, code, 46, 2.1, C.on);
      let y = 76;
      if (st === 'host') {
        line(y, 'PLAYER 1', 'YOU', C.text, C.on); y += 10;
        const slots = PortNet.slots(), max = (t.room && t.room.max) || 4;
        for (let ch = 1; ch < max; ch++) {
          const sl = slots.find((x) => x.ch === ch);
          const stx = !sl ? ['FREE', C.lock] : sl.state === 'joined' ? [sl.rtt ? `PING ${sl.rtt} MS` : 'JOINED', C.on]
            : sl.state === 'left' || sl.state === 'failed' ? [sl.state === 'left' ? 'LEFT' : 'COULD NOT CONNECT', C.title] : ['CONNECTING…', C.text];
          line(y, `PLAYER ${ch + 1}`, stx[0], sl ? C.text : C.lock, stx[1]); y += 10;
        }
      } else {
        line(y, 'PLAYER 1', 'HOST', C.text, C.dim); y += 10;
        line(y, `PLAYER ${t.myCh + 1}`, 'YOU', C.text, C.on); y += 10;
      }
      return Math.max(y + 4, 120);
    }
    // session: every player with the ping, the input delay
    let y = 40;
    const me = t ? t.myCh : 0, roster = (t && t.roster && t.roster.length ? t.roster : [0, 1]);
    for (const ch of roster) {
      const pe = t && t.peers[ch];
      const v = ch === me ? ['YOU', C.on] : pe && pe.lost ? ['LEFT (STANDS STILL)', C.title] : [pe && pe.rtt ? `PING ${Math.round(pe.rtt)} MS` : 'PING -', C.text];
      line(y, `PLAYER ${ch + 1}`, v[0], C.text, v[1]); y += 10;
    }
    if (netCfg) { line(y + 2, 'INPUT DELAY', `${netCfg.delay} (${netCfg.delay * 20} MS${netCfg.autoDelay ? ', AUTO' : ''})`, C.dim, C.dim); y += 12; }
    if (t && t.desync) { T(`DESYNC AT RETRACE ${t.desync.frame}`, 160, y + 2, { scale: S, color: C.title, align: 'center', alpha: pulse }); y += 12; }
    return Math.max(y + 6, 92);
  }
  // the letter picker: 5 boxes for the code, the room server's 23 letters in 3 rows of 8 (DEL in the last cell), JOIN
  const PX0 = 48, PCW = 28, PY0 = 84, PCH = 17;
  function drawPick(ctx, T, k, ox, now, pulse, fade) {
    const P = U.pick;
    T('ROOM CODE', 160, 36, { scale: 0.6, color: C.dim, align: 'center' });
    for (let i = 0; i < 5; i++) {
      const x = 160 - 2.5 * 30 + i * 30 + 3, y = 46, cur = i === P.code.length;
      ctx.fillStyle = `rgba(0,0,0,${0.5 * fade})`; ctx.fillRect((ox + x) * k, y * k, 24 * k, 28 * k);
      ctx.strokeStyle = cur ? `rgba(255,255,0,${pulse * fade})` : `rgba(150,150,150,${0.7 * fade})`; ctx.lineWidth = Math.max(1, (cur ? 1 : 0.6) * k);
      ctx.strokeRect((ox + x) * k, y * k, 24 * k, 28 * k);
      if (P.code[i]) T(P.code[i], x + 12, y + 5, { scale: 1.6, color: C.on, align: 'center' });
    }
    for (let cy = 0; cy <= PROWS; cy++) {
      const y = PY0 + cy * PCH;
      if (cy === PROWS) {   // JOIN: the whole width
        const sel = P.cy === PROWS, ok = P.code.length === 5;
        if (sel) { ctx.fillStyle = `rgba(255,60,30,${0.32 * fade})`; ctx.fillRect((ox + PX0) * k, (y - 3) * k, PCW * PCOLS * k, (PCH - 2) * k); }
        T(U.busy === 'join' ? 'JOINING…' : 'JOIN', 160, y, { scale: 0.95, color: sel ? C.text : ok ? C.on : C.lock, align: 'center', alpha: sel ? pulse : 1 });
        U.hits.push({ act: 'cell', cx: 0, cy, x0: ox + PX0, x1: ox + PX0 + PCW * PCOLS, y0: y - 3, y1: y + PCH - 5 });
        continue;
      }
      for (let cx = 0; cx < PCOLS; cx++) {
        const x = PX0 + cx * PCW, sel = P.cy === cy && P.cx === cx, c = pickCell(cx, cy);
        if (sel) { ctx.fillStyle = `rgba(255,60,30,${0.32 * fade})`; ctx.fillRect((ox + x + 2) * k, (y - 3) * k, (PCW - 4) * k, (PCH - 2) * k); }
        T(c, x + PCW / 2, c === 'DEL' ? y + 2 : y, { scale: c === 'DEL' ? 0.6 : 1, color: sel ? C.text : C.dim, align: 'center', alpha: sel ? 0.75 + 0.25 * pulse : 1 });
        U.hits.push({ act: 'cell', cx, cy, x0: ox + x, x1: ox + x + PCW, y0: y - 3, y1: y + PCH - 3 });
      }
    }
    return 168;
  }

  // ---- mouse / touch
  function hitAt(e) {
    const r = cv.getBoundingClientRect(), k = cv.height / 240 / (cv.height / r.height);
    const x = (e.clientX - r.left) / k, y = (e.clientY - r.top) / k;
    return U.hits.find((h) => x >= h.x0 && x <= h.x1 && y >= h.y0 && y <= h.y1);
  }
  cv.addEventListener('pointermove', (e) => {
    const h = hitAt(e);
    if (h && h.act === 'cell' && (e.movementX || e.movementY)) { U.pick.cx = h.cx; U.pick.cy = h.cy; return; }   // P365: the letter picker
    if (h && h.i !== undefined && (e.movementX || e.movementY)) page().sel = h.i;
  });
  cv.addEventListener('pointerdown', (e) => {
    e.preventDefault();
    if (e.button === 2) { back(); return; }
    const h = hitAt(e);
    if (!h) return;
    if (h.act === 'back') { if (page().id !== 'pick' || !pickDelete()) back(); return; }
    if (h.act === 'cell') { U.pick.cx = h.cx; U.pick.cy = h.cy; pickChoose(); return; }   // P365
    const p = page(), it = itemsOf(p)[h.i];
    p.sel = h.i;
    const r = cv.getBoundingClientRect(), xu = (e.clientX - r.left) / (r.height / 240) - (r.width / (r.height / 240) - 320) / 2;
    if ((it.kind === 'range' || it.kind === 'choice') && xu > 200) change(it, xu < 250 ? -1 : 1); else choose(it);
  });
  cv.addEventListener('contextmenu', (e) => e.preventDefault());
  cv.addEventListener('wheel', (e) => { e.preventDefault(); if (page().id === 'pick') pickMove(0, e.deltaY > 0 ? 1 : -1); else moveSel(e.deltaY > 0 ? 1 : -1); }, { passive: false });

  // test aid ?gmenuopen=S: open the menu S seconds after the game started (page-only: nothing hashed changes; netpair
  // GUESTQ='&gmenuopen=40' keeps it open on a guest during an online session)
  if (Q.get('gmenuopen')) {
    const at = performance.now() + 1000 * +Q.get('gmenuopen');
    const tryOpen = () => { if (performance.now() >= at && open()) log('[gmenu] opened by ?gmenuopen'); else setTimeout(tryOpen, 500); };
    setTimeout(tryOpen, 1000 * +Q.get('gmenuopen'));
  }

  // test aid ?gmenupad=S (P362): S seconds after load a fake standard gamepad holds Back (the photo button) 40 frames
  // (the hold entry opens the menu), goes to Controls > Gamepad buttons, back twice, and closes the menu with a Back
  // press; each step is logged. netpair GUESTQ='&gmenupad=70' runs it on a guest online (page-only:
  // with ?netscript the lockstep input comes from the pad scripts, so the session proves nothing hashed changed).
  if (Q.get('gmenupad')) setTimeout(() => {
    const fp = { id: 'gmenupad test pad', index: 0, connected: true, mapping: 'standard', axes: [0, 0, 0, 0], buttons: Array.from({ length: 17 }, () => ({ pressed: false, value: 0 })) };
    navigator.getGamepads = () => [fp];
    const seq = [[8, 40], [13, 6], [13, 6], [13, 6], [13, 6], [0, 6], [13, 6], [0, 6], [1, 6], [1, 6], [8, 6]];
    let i = 0, f = 0;
    const st = () => JSON.stringify({ open: U.open, page: U.open ? page().id : null, sel: U.open ? page().sel : -1 });
    log(`[gmenu] gmenupad start ${st()}`);
    const pump = () => {
      const q = seq[i];
      fp.buttons.forEach((b, j) => { b.pressed = !!q && f < q[1] && j === q[0]; b.value = b.pressed ? 1 : 0; });
      if (!q) { log(`[gmenu] gmenupad done ${st()}`); return; }
      if (++f >= q[1] + 30) { i++; f = 0; log(`[gmenu] gmenupad step ${i} (button ${q[0]}): ${st()}`); }
      requestAnimationFrame(pump);
    };
    pump();
  }, 1000 * +Q.get('gmenupad'));

  // P365 test aid ?gmenutest=1: a fake standard gamepad driven by a queue of presses [[button, frames held, frames after]]
  // (window.__gmenuTest.press), and pickPath(code) = the presses that pick a room code on the letter picker from where its
  // cursor is (D-pad moves, A types each letter, Start joins). Used by tools/port/scripts/netgroup.js UI=gmenu.
  if (Q.get('gmenutest')) {
    const fp = { id: 'gmenutest pad', index: 0, connected: true, mapping: 'standard', axes: [0, 0, 0, 0], buttons: Array.from({ length: 17 }, () => ({ pressed: false, value: 0 })) };
    navigator.getGamepads = () => [fp];
    const q = []; let f = 0;
    const pump = () => {
      const st = q[0];
      fp.buttons.forEach((b, j) => { b.pressed = !!st && f < st[1] && j === st[0]; b.value = b.pressed ? 1 : 0; });
      if (st && ++f >= st[1] + (st[2] === undefined ? 8 : st[2])) { q.shift(); f = 0; }
      requestAnimationFrame(pump);
    };
    pump();
    const pickPath = (code, join = true) => {
      let { cx, cy } = U.pick; const out = [];
      for (const c of String(code).toUpperCase()) {
        const i = ALPHA.indexOf(c); if (i < 0) continue;
        const tx = i % PCOLS, ty = Math.floor(i / PCOLS);
        for (; cy !== ty; cy += ty > cy ? 1 : -1) out.push([ty > cy ? 13 : 12, 4]);
        for (; cx !== tx; cx += tx > cx ? 1 : -1) out.push([tx > cx ? 15 : 14, 4]);
        out.push([0, 4]);
      }
      if (join) out.push([9, 4]);   // Start: JOIN
      return out;
    };
    window.__gmenuTest = { press: (seq) => { q.push(...seq); return q.length; }, idle: () => !q.length, pickPath };
    log('[gmenu] ?gmenutest: fake gamepad installed');
  }

  // P368: would open() work now (the game runs, or before boot with a good ROM, and the font is there)? main.js makes the
  // page drawer the developer menu only then (else the drawer stays the whole menu: the fallback)
  const available = () => typeof running !== 'undefined' && (running ? running === 'game' : romOk) && photo.state !== 2 && fontOk();
  return { open, close, back, poll, key, note, available, get isOpen() { return U.open; },
    state: () => ({ open: U.open, pre: U.pre, from: U.from, page: U.open ? page().id : null, sel: U.open ? page().sel : -1, item: U.open ? (itemsOf(page())[page().sel] || {}).label : null,
      online: onlineState(), code: NT() && NT().room ? NT().room.code : '', typed: U.pick.code, cursor: pickCell(U.pick.cx, U.pick.cy), joined: joinedCount(), busy: U.busy, err: U.err }) };
})();
window.GMenu = GMenu;

// ---------------------------------------------------------------- P365 online messages over the game
// The lockstep session's messages in the game's font instead of page text: "waiting for player 2…" while the game waits
// for a player's input (main.js's tick handler decides when, as for the page's #netwait), a player who left, the desync
// report, and other connection problems during the session. A canvas over the picture that takes no input; drawn only
// while a message is up. Page-only: it reads net.js's events and never touches the game.
const GNet = (() => {
  const cv = document.getElementById('gnet');
  const S = { wait: '', box: null, raf: 0, desync: '' };
  const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', dim: 'rgb(170,170,170)' };
  // P369: the game-style menus are always on; GNet draws whenever the game's font is at hand (else the page's #netwait)
  const wanted = () => GameFont.ready() || GameFont.load();
  const kick = () => { if (!S.raf) S.raf = requestAnimationFrame(draw); };
  function wait(t) { if (t !== S.wait) { S.wait = t; kick(); } }
  function show(title, text, ms, color) { S.box = { title, text, until: performance.now() + ms, color: color || C.title, t0: performance.now() }; kick(); snd('error'); log(`[gnet] ${title}: ${text}`); }   // P367: the error sound (silent online: GSound)
  function draw() {
    S.raf = 0;
    const now = performance.now();
    if (S.box && S.box.until < now) S.box = null;
    const on = wanted() && (S.wait || S.box || S.desync) && GameFont.load();
    cv.hidden = !on;
    if (!on) return;
    S.raf = requestAnimationFrame(draw);
    const r = cv.getBoundingClientRect(), dpr = Math.min(2, window.devicePixelRatio || 1);
    const w = Math.max(1, Math.round(r.width * dpr)), h = Math.max(1, Math.round(r.height * dpr));
    if (cv.width !== w || cv.height !== h) { cv.width = w; cv.height = h; }
    const k = h / 240, ox = (w / k - 320) / 2, ctx = cv.getContext('2d'), sm = !!opt('smoothfont');
    const T = (s, x, y, o) => GameFont.draw(ctx, s, ox + x, y, k, Object.assign({ smooth: sm }, o));
    ctx.clearRect(0, 0, w, h);
    const pulse = 0.7 + 0.3 * Math.sin(now / 200);
    const band = (y, hh, a) => {   // a dark band fading out at both ends, like the game-style menu's
      const g = ctx.createLinearGradient((ox + 30) * k, 0, (ox + 290) * k, 0);
      g.addColorStop(0, 'rgba(10,5,2,0)'); g.addColorStop(0.15, `rgba(10,5,2,${a})`); g.addColorStop(0.85, `rgba(10,5,2,${a})`); g.addColorStop(1, 'rgba(10,5,2,0)');
      ctx.fillStyle = g; ctx.fillRect((ox + 30) * k, y * k, 260 * k, hh * k);
    };
    if (S.wait) { band(5, 16, 0.7); T(S.wait.toUpperCase(), 160, 8.5, { scale: 0.85, color: C.text, align: 'center', alpha: pulse }); }
    if (S.box) {
      const a = Math.min(1, (now - S.box.t0) / 160, (S.box.until - now) / 300);
      const lines = GameFont.wrap(S.box.text, 240, 0.7).slice(0, 4);
      const hh = 24 + lines.length * 10.5;
      const y0 = 186 - hh / 2;   // the lower third: the game's own menus and titles stay readable
      ctx.globalAlpha = a; band(y0, hh, 0.78); ctx.globalAlpha = 1;
      T(S.box.title, 160, y0 + 5, { scale: 1.1, color: S.box.color, align: 'center', alpha: a });
      lines.forEach((l, i) => T(l, 160, y0 + 20 + i * 10.5, { scale: 0.7, color: C.text, align: 'center', alpha: a }));
    }
    if (S.desync && !S.box) T(S.desync, 160, 226, { scale: 0.55, color: C.title, align: 'center', alpha: 0.85 });   // stays small after the box
  }
  if (typeof netEvents !== 'undefined') {
    netEvents.left.push((ch) => {
      if (!wanted() || !window.PortNet) return;
      if (PortNet.t.left) wait('');
      show(`PLAYER ${ch + 1} LEFT`, `Controller ${ch + 1} stands still from now on; the match goes on.`, 7000);
    });
    netEvents.desync.push((d) => {
      if (!wanted() || S.desync) return;
      S.desync = `DESYNC AT RETRACE ${d.frame}: CUSTOMISATION SETTINGS > ONLINE`;
      show('DESYNC', `At retrace ${d.frame} this game and player ${(d.ch || 0) + 1}'s no longer match: they show different things from here. Please report it (the page menu's Debug log has the details).`, 15000);
    });
    netEvents.status.push((s, cls) => {   // other problems during the session (before it, the ONLINE page shows them)
      if (!wanted() || cls !== 'bad' || !netCfg || /: controller \d stands still/.test(s)) return;
      show('ONLINE', s, 9000);
    });
  }
  return { wanted, wait, show };
})();
window.GNet = GNet;

// ---------------------------------------------------------------- P366 photo mode in the game's style
// With the game-style menu on, photo mode's HUD (bottom left), its Pose & Outfit panel (right) and its messages are drawn
// on the canvas #gphoto in the game's font, with GMenu's look (dark bands, the red title, the selected row on a red band
// with a pulsing ">", ON / values in the game's yellow, the footer's button faces) instead of the page's boxes (#photo,
// #photo-look and #photo-toast hide: body.gphoto). No font yet: the page's own photo boxes (P369: no option any more).
//
// Same choices, same path: every row changes main.js's `look` (P358) and calls lookChanged() / lookSave() like the
// page panel's inputs did, so pc_photo.c gets the same port_photo_look_set calls; the page panel is still built (hidden)
// and keeps the material records and lookUi's signature. Nothing here touches game memory: the hashed-state snapshot
// taken when photo mode starts is restored on leaving it as before (pc_photo.c), whatever was chosen.
//
// Input, like GMenu's and the old panel's: O / the right stick click (CAMBACK, "nav") gives the panel the focus; then
// the D-pad (arrows) moves (hold: repeats, faster after a second), left / right change a value (on a list: a page), A
// (Space, Enter) chooses, B (F, Esc, Backspace) goes back (on the first page: the camera gets the D-pad again); the stick,
// C buttons, R / Z, L and Start keep working the camera, the HUD and leaving photo mode. Long lists (857 animations,
// 187 models, 63 item lists) open as their own page: one page per left / right, Page Up / Down, Home / End, held
// up / down speeds up to 5 then 25 rows a step, the mouse wheel, and the scroll bar (click or drag). The mouse: a click on
// a row chooses it (on a value: its left / right half steps it), right click goes back; clicks elsewhere still capture
// the mouse for looking around. H / the gamepad's RT (PHOTOUI, rebindable) hides every menu for a clean view; the same
// button (or Esc, or O) shows them again. Esc with the panel unfocused and the menus shown leaves photo mode.
const GPhoto = (() => {
  const cv = document.getElementById('gphoto');
  const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', off: 'rgb(170,170,170)', dim: 'rgb(150,150,150)', lock: 'rgb(120,120,120)', head: 'rgb(255,200,60)' };
  const S = { shown: false, focus: false, hidden: false, hidAt: 0, stack: [], hits: [], raf: 0, prevBits: -1, repeatAt: 0, holdT: 0,
    prevNav: true, prevHide: true, toast: '', toastAt: 0, helpSig: '', helpAt: 0, helpPage: 0, hudAt: 0, hudPage: 0, cache: null,
    rowsVis: 12, drag: null, downHit: false, keyHold: { code: '', t: 0 }, info: '', infoAt: 0, t0: 0 };
  const fontOk = () => GameFont.ready() || GameFont.load();
  const active = () => S.shown && photo.state === 2 && fontOk();
  const page = () => S.stack[S.stack.length - 1];
  const smooth = () => !!opt('smoothfont');
  const MASK = N64.DU | N64.DD | N64.DL | N64.DR | N64.A | N64.B;
  // the name of a page input's key or button: the gamepad's when one is connected, else the keyboard's
  const padOn = () => (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).some((g) => g && g.connected);
  const inputName = (id) => {
    const v = padOn() ? padMap[id] : keyMap[id];
    if (v === undefined || v === null) return '-';
    return padOn() ? padName(v).replace('D↑', 'D-UP').replace('D↓', 'D-DOWN').replace('D←', 'D-LEFT').replace('D→', 'D-RIGHT') : keyName(v);
  };

  // ---- what Conker's data offers (main.js lkInfo / animLabel / modelLabel / itemLabel), cached until it changes
  function lists() {
    const sig = [lookUi.matSig, lkInfo(LR.ANIM_COUNT), lkInfo(LR.ANIM_GAME), lkInfo(LR.MODEL), lkInfo(LR.GROUP_N), lkInfo(LR.DRAWN_MODEL)].join('|');
    if (S.cache && S.cache.sig === sig) return S.cache;
    const anims = [[-1, 'original pose (' + animLabel(lkInfo(LR.ANIM_GAME)) + ')']];
    for (let i = 0, n = lkInfo(LR.ANIM_COUNT); i < n; i++) if (!lkInfo(LR.ANIM_BAD, i)) anims.push([i, animLabel(i)]);
    const g = []; for (let i = 0; i < lkInfo(LR.GROUP_N); i++) g.push(lkInfo(LR.GROUP, i));
    const own = lkInfo(LR.MODEL), models = [[-1, 'his own: ' + modelLabel(own)]];
    for (const m of g) if (m !== own) models.push([m, modelLabel(m)]);
    for (let m = 0; m < 187; m++) if (!g.includes(m)) models.push([m, modelLabel(m) + ' (own skeleton)']);
    const items = [[0, 'none']];
    for (let i = 1; i <= 63; i++) if (lkInfo(LR.ITEM_KIND, i)) items.push([i, itemLabel(i)]);
    const tex = [];
    for (let i = 0, n = lkInfo(LR.TEX_N); i < n; i++) tex.push({ i, id: lkInfo(LR.TEX_ID, i), w: lkInfo(LR.TEX_WH, i) >> 16, h: lkInfo(LR.TEX_WH, i) & 0xFFFF });
    const att = []; for (let i = 0, n = lkInfo(LR.ATT_N); i < n; i++) att.push(lkInfo(LR.ATT, i));
    const mats = []; for (let i = 0, n = lkInfo(LR.MAT_N); i < n; i++) mats.push({ key: lkInfo(LR.MAT_KEY, i), tris: lkInfo(LR.MAT_TRIS, i) });
    return (S.cache = { sig, anims, models, items, tex, att, mats, drawn: lkInfo(LR.DRAWN_MODEL), ndl: lkInfo(LR.DL_N) });
  }
  const labelOf = (opts, v) => (opts.find((o) => o[0] === v) || opts[0] || [0, ''])[1];
  function step(opts, v, d) {   // the next / previous entry of a choice (wraps)
    if (!opts.length) return v;
    const i = opts.findIndex((o) => o[0] === v);
    return opts[((i < 0 ? 0 : i) + d + opts.length) % opts.length][0];
  }
  const faceOpts = (L, s) => {   // a face slot: the game's texture, or another of the same size (as the page panel)
    const cur = lkInfo(LR.FACE, s), t = L.tex[cur];
    return [[-1, 'the game\'s (texture ' + (t ? t.id : '?') + ')'], ...L.tex.filter((x) => !t || (x.w === t.w && x.h === t.h)).map((x) => [x.i, 'texture ' + x.id + ' (' + x.w + 'x' + x.h + ')'])];
  };
  const matRec = (drawn, key) => {
    const mats = (look.mats[drawn] = look.mats[drawn] || {});
    return (mats[key] = mats[key] || { hide: false, tint: '#ff3030', amt: 0, tex: -1 });
  };
  const PALETTE = [['RED', '#ff3030'], ['ORANGE', '#ff8000'], ['YELLOW', '#ffe000'], ['GREEN', '#30d030'], ['CYAN', '#00d0d0'], ['BLUE', '#3050ff'],
    ['PURPLE', '#a040ff'], ['PINK', '#ff60c0'], ['BROWN', '#8b5a2b'], ['WHITE', '#ffffff'], ['GREY', '#808080'], ['BLACK', '#000000']];
  const hex2 = (n) => n.toString(16).padStart(2, '0');

  // ---- the pages' rows. kind: head (a section title, not selectable), toggle, choice (opts; list: A opens it as a page),
  // range (change(d), text), link (a page), action. value() = [text, colour]; help; locked() = why not now ('' = can)
  function itemsOf(p) {
    const L = lists();
    const backRow = { kind: 'action', label: 'Back', help: 'Back to the previous page (B).', act: () => back() };
    if (p.id === 'main') {
      const it = [{ kind: 'head', label: 'Pose' },
        { kind: 'choice', tall: true, label: 'Animation', list: 'anims', opts: () => L.anims, get: () => look.anim,
          set: (v) => { look.anim = v; look.frame = 0; lookChanged(); },
          help: `Conker's animation (${L.anims.length - 1} with data). Left / right: the previous / next one; A: the whole list.` },
        { kind: 'toggle', label: 'Play', get: () => look.play, set: (v) => { look.play = v; lookSave(); lookRefreshValues(); }, names: ['PAUSED', 'PLAYING'],
          locked: () => (look.anim < 0 ? 'Choose an animation first.' : ''), help: 'Play the animation in a loop (at the speed below).' },
        { kind: 'range', label: 'Frame', text: () => (look.anim >= 0 ? `${Math.floor(look.frame)} / ${Math.max(0, lookUi.frames - 1)}` : '-'),
          change: (d) => {
            if (d > 0) { look.frame = Math.floor(look.frame) + d; if (lookUi.frames && look.frame >= lookUi.frames) look.frame = d > 1 ? lookUi.frames - 1 : 0; }
            else look.frame = Math.max(0, Math.floor(look.frame) + d);
            look.play = false; lookChanged();
          },
          locked: () => (look.anim < 0 ? 'Choose an animation first.' : ''), help: 'The animation frame: left / right one frame (hold: faster); stops playing. A plays / pauses.',
          act: () => { look.play = !look.play; lookSave(); lookRefreshValues(); } },
        { kind: 'choice', label: 'Speed', opts: () => [[0.25, '1/4 X'], [0.5, '1/2 X'], [1, '1 X'], [2, '2 X']], get: () => look.speed, set: (v) => { look.speed = v; lookSave(); },
          help: 'How fast Play runs the animation.' },
        { kind: 'head', label: 'Outfit' },
        { kind: 'choice', tall: true, label: 'Model', list: 'models', opts: () => L.models, get: () => look.model,
          set: (v) => { look.model = v; look.dlHide = look.dlShow = 0; lookChanged(); },
          help: 'Models that share Conker\'s skeleton and animations come first (loaded from the ROM for the photo only); "own skeleton" models move with their own animation numbers.' }];
      for (let s = 0; s < 4; s++) it.push({ kind: 'choice', tall: true, label: 'Item ' + (s + 1), list: 'items:' + s, opts: () => L.items, get: () => look.items[s],
        set: (v) => { look.items[s] = v; lookChanged(); }, help: 'Held items / gear: the game\'s attachment lists, put on Conker for the photo (up to 4).' });
      if (L.att.length) it.push({ kind: 'head', label: 'He carries' });
      L.att.forEach((key) => it.push({ kind: 'toggle', label: `Model ${key >> 8} (list ${key & 255})`, names: ['HIDDEN', 'SHOWN'],
        get: () => !look.attHide.includes(key),
        set: (v) => { look.attHide = look.attHide.filter((x) => x !== key); if (!v) look.attHide.push(key); lookChanged(); },
        help: 'What he carries in the game right now (an attachment): show or hide it in the photo.' }));
      it.push({ kind: 'head', label: 'Face and parts' });
      ['Eyelids 1', 'Eyelids 2', 'Eye 1', 'Eye 2'].forEach((label, s) => it.push({ kind: 'choice', label, opts: () => faceOpts(L, s), get: () => look.face[s],
        set: (v) => { look.face[s] = v; lookChanged(); }, help: 'The face texture the game puts into this slot every frame, or another of the same size.' }));
      if (L.ndl > 1) it.push({ kind: 'link', label: 'Parts', page: 'parts', help: 'The drawn model\'s display lists (parts): show or hide each, also the ones the game hides.',
        text: () => { let n = 0; for (let k = 0; k < L.ndl && k < 32; k++) if (dlShown(k)) n++; return `${n} OF ${Math.min(32, L.ndl)}`; } });
      if (L.mats.length) it.push({ kind: 'link', label: 'Materials', page: 'mats', help: 'Each material (texture) of ' + modelLabel(L.drawn) + ': show / hide, another texture, a tint.',
        text: () => String(L.mats.length) });
      it.push({ kind: 'head', label: '' },
        { kind: 'action', label: 'Reset', help: 'Back to the game\'s own pose and outfit.', act: () => { const m = look.min; Object.assign(look, LOOK_DEFAULT(), { min: m }); lookPush(); lookBuild(); S.cache = null; log('[gphoto] reset'); } },
        { kind: 'toggle', label: 'Fold when not editing', get: () => !!look.min, set: (v) => { look.min = v; lookSave(); lookBuild(); },
          help: 'While the camera has the controls, show only this panel\'s title.' },
        { kind: 'action', label: 'Done', help: 'Give the D-pad back to the camera (also B on this page, or O / the right stick click).', act: () => setFocus(false) });
      return it;
    }
    if (p.id === 'parts') {
      const it = [];
      for (let k = 0; k < L.ndl && k < 32; k++) {
        const byGame = (lkInfo(LR.DL_MASK) >> k) & 1;
        it.push({ kind: 'toggle', label: 'Part ' + k + (byGame ? ' (game hides)' : ''), names: ['HIDDEN', 'SHOWN'], get: () => dlShown(k),
          set: (v) => { const b = 1 << k; if (byGame) look.dlShow = v ? look.dlShow | b : look.dlShow & ~b; else look.dlHide = v ? look.dlHide & ~b : look.dlHide | b; lookChanged(); },
          help: 'Display list ' + k + ' of ' + modelLabel(L.drawn) + (byGame ? ': the game hides it; show it for the photo.' : '.') });
      }
      return it.concat([backRow]);
    }
    if (p.id === 'mats') return L.mats.map(({ key, tris }) => ({ kind: 'link', label: matLabel(L.drawn, key), page: 'mat:' + key, help: `${tris} triangles. A: show / hide it, another texture, a tint.`,
      text: () => { const m = matRec(L.drawn, key); return [m.hide ? 'HIDDEN' : '', m.tex >= 0 ? 'TEX' : '', m.amt > 0 ? `TINT ${m.amt}%` : ''].filter(Boolean).join(' ') || '>'; } })).concat([backRow]);
    if (p.id.startsWith('mat:')) {
      const key = +p.id.slice(4), m = matRec(L.drawn, key), t = key < 64 ? L.tex[key] : null;
      const texOpts = [[-1, 'its own (' + matLabel(L.drawn, key) + ')']];
      if (t) for (const x of L.tex) if (x.i !== key && x.w === t.w && x.h === t.h) texOpts.push([x.i, 'texture ' + x.id]);
      const rgb = () => parseInt((m.tint || '#ff3030').slice(1), 16);
      const setRgb = (c) => { m.tint = '#' + hex2((c >> 16) & 255) + hex2((c >> 8) & 255) + hex2(c & 255); if (!m.amt) m.amt = 60; lookChanged(); };   // as the colour input: a colour with no tint gets 60 %
      const chan = (label, sh) => ({ kind: 'range', label, text: () => String((rgb() >> sh) & 255),
        change: (d) => { const v = Math.max(0, Math.min(255, ((rgb() >> sh) & 255) + d * 15)); setRgb((rgb() & ~(255 << sh)) | (v << sh)); },
        help: 'The tint colour\'s ' + label.toLowerCase() + ' (0 to 255; hold for bigger steps).' });
      return [
        { kind: 'toggle', label: 'Shown', get: () => !m.hide, set: (v) => { m.hide = !v; lookChanged(); }, help: 'Draw this material or leave it out.' },
        { kind: 'choice', label: 'Texture', opts: () => texOpts, get: () => m.tex, set: (v) => { m.tex = v; lookChanged(); },
          locked: () => (texOpts.length < 2 ? (t ? 'No other texture has its size.' : 'Face slots and untextured parts keep their texture.') : ''),
          help: 'Draw it with another texture of the same size.' },
        { kind: 'range', label: 'Tint', text: () => m.amt + '%', change: (d) => { m.amt = Math.max(0, Math.min(100, m.amt + 5 * Math.sign(d) * Math.min(4, Math.abs(d)))); lookChanged(); },
          help: 'How strongly the tint colour colours it (0 = not at all); its light and shade stay.' },
        { kind: 'choice', label: 'Colour', opts: () => { const cur = (m.tint || '').toLowerCase(), o = PALETTE.map(([n, c]) => [c, n]); if (!o.some((x) => x[0] === cur)) o.unshift([cur, cur.toUpperCase()]); return o; },
          get: () => (m.tint || '').toLowerCase(), set: (v) => { m.tint = v; if (!m.amt) m.amt = 60; lookChanged(); }, help: 'The tint colour (or set red, green and blue below).' },
        chan('Red', 16), chan('Green', 8), chan('Blue', 0),
        backRow];
    }
    return [backRow];
  }
  const dlShown = (k) => { const byGame = (lkInfo(LR.DL_MASK) >> k) & 1; return byGame ? !!((look.dlShow >> k) & 1) : !((look.dlHide >> k) & 1); };
  // a list page: { title, opts, get, set }
  function listOf(p) {
    const L = lists();
    if (p.id === 'anims') return { title: 'Animations', opts: L.anims, get: () => look.anim, set: (v) => { look.anim = v; look.frame = 0; lookChanged(); } };
    if (p.id === 'models') return { title: 'Models', opts: L.models, get: () => look.model, set: (v) => { look.model = v; look.dlHide = look.dlShow = 0; lookChanged(); } };
    if (p.id.startsWith('items:')) { const s = +p.id.slice(6); return { title: 'Item ' + (s + 1), opts: L.items, get: () => look.items[s], set: (v) => { look.items[s] = v; lookChanged(); } }; }
    return null;
  }
  const TITLES = { main: 'Pose & outfit', parts: 'Parts', mats: 'Materials' };
  const titleOf = (p) => (listOf(p) ? listOf(p).title : p.id.startsWith('mat:') ? matLabel(lists().drawn, +p.id.slice(4)) : TITLES[p.id] || '');
  const selectable = (it) => it && it.kind !== 'head';
  const lockOf = (it) => (it && it.locked ? it.locked() : '');

  // ---- actions
  function setFocus(on, quiet) {
    if (S.focus === on) return;
    if (!quiet) snd(on ? 'choose' : 'back');   // P367
    S.focus = on; S.prevBits = -1; S.helpSig = '';
    if (!on) S.stack = [S.stack[0]];
    log(`[gphoto] panel ${on ? 'focus (the D-pad works the panel)' : 'unfocused (the D-pad works the camera)'}`);
  }
  function setHidden(on) {
    S.hidden = on; S.hidAt = performance.now();
    snd('change');   // P367
    if (on) setFocus(false, true);
    log(`[gphoto] menus ${on ? 'hidden' : 'shown'}`);
  }
  function go(id) {
    const p = { id, sel: 0, top: 0 };
    const l = listOf(p);
    if (l) { p.sel = Math.max(0, l.opts.findIndex((o) => o[0] === l.get())); p.top = Math.max(0, p.sel - 5); }
    else { const it = itemsOf(p); while (p.sel < it.length - 1 && !selectable(it[p.sel])) p.sel++; }
    S.stack.push(p); S.helpSig = '';
    log(`[gphoto] page ${id}`);
  }
  function back() { if (S.stack.length > 1) { snd('back'); S.stack.pop(); S.helpSig = ''; } else setFocus(false); }
  function moveSel(d, clamp) {   // P367: the move sound when the selection moved
    const was = page().sel;
    moveSelBy(d, clamp);
    if (page().sel !== was) snd('move');
  }
  function moveSelBy(d, clamp) {
    const p = page(), l = listOf(p);
    if (l) {
      const n = l.opts.length; if (!n) return;
      p.sel = clamp || Math.abs(d) > 1 ? Math.max(0, Math.min(n - 1, p.sel + d)) : (p.sel + d + n) % n;
      return;
    }
    const it = itemsOf(p), n = it.length; if (!n) return;
    let i = p.sel;
    for (let c = 0; c < Math.min(n, Math.abs(d)); c++) {
      let j = i;
      for (let t = 0; t < n; t++) { j = clamp ? Math.max(0, Math.min(n - 1, j + Math.sign(d))) : (j + Math.sign(d) + n) % n; if (selectable(it[j])) break; }
      if (selectable(it[j])) i = j;
    }
    p.sel = i;
  }
  function change(it, d) {
    if (!it || !(it.kind === 'toggle' || it.kind === 'choice' || it.kind === 'range')) return;
    if (lockOf(it)) { snd('error'); return; }
    const val = () => (it.text ? it.text() : it.get ? it.get() : null), was = val();   // P367: change, or error if nothing moved
    if (it.kind === 'toggle') it.set(!it.get());
    else if (it.kind === 'choice') it.set(step(it.opts(), it.get(), Math.sign(d)));
    else if (it.kind === 'range') it.change(d);
    snd(val() !== was ? 'change' : 'error');
  }
  function choose(it) {
    if (!it || !selectable(it)) return;
    if (it.kind === 'link') { snd('choose'); go(it.page); return; }
    if (it.kind === 'action') { if (lockOf(it)) snd('error'); else if (!/^(Back|Done)$/.test(it.label)) snd('choose'); it.act(); return; }   // Back / Done: their own back sound
    if (lockOf(it)) { snd('error'); return; }
    if (it.kind === 'choice' && it.list) { snd('choose'); go(it.list); return; }
    if (it.kind === 'range') { if (it.act) { snd('choose'); it.act(); } return; }
    change(it, 1);
  }
  function pick(i) {   // a list page's entry: chosen, back to the row
    const p = page(), l = listOf(p);
    if (!l || !l.opts[i]) return;
    l.set(l.opts[i][0]);
    log(`[gphoto] picked ${p.id}: ${l.opts[i][1]}`);
    snd('choose'); S.stack.pop(); S.helpSig = '';   // back to the row (one sound)
  }
  function chooseSel() { const p = page(); if (listOf(p)) pick(p.sel); else choose(itemsOf(p)[p.sel]); }
  // a direction (1 up, 2 down, 4 left, 8 right) taken mult times (held: 5, 25)
  function nav(dir, mult) {
    const p = page(), l = listOf(p);
    if (dir & 1) moveSel(-mult, mult > 1); else if (dir & 2) moveSel(mult, mult > 1);
    if (l) { if (dir & 4) moveSel(-S.rowsVis, true); else if (dir & 8) moveSel(S.rowsVis, true); return; }
    const it = itemsOf(p)[p.sel];
    if (dir & 12) change(it, ((dir & 8) ? 1 : -1) * (it && it.kind === 'range' ? mult : 1));
  }
  const holdMult = (held) => (held > 2200 ? 25 : held > 900 ? 5 : 1);

  // ---- pad 1 while photo mode is on (main.js lookTick from photoPoll): the bits the camera must not see
  function input(d, fresh, dt) {
    const now = performance.now(), b = d.b | 0;
    if (d.hide && !S.prevHide) setHidden(!S.hidden);
    S.prevHide = !!d.hide;
    if (d.nav && !S.prevNav) { if (S.hidden) { setHidden(false); setFocus(true, true); } else setFocus(!S.focus); if (S.focus && look.min) { /* folded: opens while focused */ } }
    S.prevNav = !!d.nav;
    if (!S.focus) return 0;
    const bits = ((b & N64.DU) ? 1 : 0) | ((b & N64.DD) ? 2 : 0) | ((b & N64.DL) ? 4 : 0) | ((b & N64.DR) ? 8 : 0) | ((b & N64.A) ? 16 : 0) | ((b & N64.B) ? 32 : 0);
    if (S.prevBits < 0) { S.prevBits = bits; return MASK; }   // what was held when the focus came does nothing here
    const fr = bits & ~S.prevBits;
    let dir = fr & 15, mult = 1;
    if ((bits & 15) && (bits & 15) === (S.prevBits & 15)) { if (now >= S.repeatAt) { dir = bits & 15; S.repeatAt = now + 90; mult = holdMult(now - S.holdT); } }
    else { S.repeatAt = now + 380; S.holdT = now; }
    S.prevBits = bits;
    if (dir) nav(dir, mult);
    if (fr & 16) chooseSel(); else if (fr & 32) back();
    return MASK;
  }
  // keys (main.js keydown, after GMenu.key): with the focus on the panel the arrows, Enter, Esc, Backspace, Page Up /
  // Down, Home and End work it whatever the bindings (they never reach the camera then); Esc otherwise shows the hidden
  // menus or leaves photo mode
  function key(e) {
    if (!active()) return false;
    const c = e.code;
    if (c === keyMap.PHOTOUI) { if (!e.repeat) setHidden(!S.hidden); return true; }   // on the key event itself (a short tap can fall between two polled frames)
    if (!S.focus) {
      if (c !== 'Escape') return false;
      if (!e.repeat) { if (S.hidden) setHidden(false); else { log('[gphoto] Esc: leave photo mode'); photoRequest(false); } }
      return true;
    }
    if (c === 'Escape' || c === 'Backspace') { if (!e.repeat) back(); return true; }
    if (c === 'Enter' || c === 'NumpadEnter') { if (!e.repeat) chooseSel(); return true; }
    const AR = { ArrowUp: 1, ArrowDown: 2, ArrowLeft: 4, ArrowRight: 8 };
    if (AR[c]) {
      const now = performance.now();
      if (!e.repeat || S.keyHold.code !== c) S.keyHold = { code: c, t: now };
      nav(AR[c], e.repeat ? holdMult(now - S.keyHold.t) : 1);
      return true;
    }
    if (c === 'PageUp' || c === 'PageDown') { const d = c === 'PageUp' ? -1 : 1; moveSel(d * (listOf(page()) ? S.rowsVis : 5), true); return true; }
    if (c === 'Home' || c === 'End') { moveSel(c === 'Home' ? -1e6 : 1e6, true); return true; }
    return false;
  }

  // ---- drawing (units: the picture is 240 high; W = its width in units, 320 at 4:3, more with Widescreen)
  const PW = 132, RH = 9.5, RS = 0.55;
  function layout() {
    const r = cv.getBoundingClientRect(), dpr = Math.min(2, window.devicePixelRatio || 1);
    const w = Math.max(1, Math.round(r.width * dpr)), h = Math.max(1, Math.round(r.height * dpr));
    if (cv.width !== w || cv.height !== h) { cv.width = w; cv.height = h; }
    const k = h / 240;
    return { k, W: w / k };
  }
  function fit(s, w, scale) {   // s cut to w units (with "...")
    s = String(s);
    if (GameFont.measure(s, scale) <= w) return s;
    while (s.length > 1 && GameFont.measure(s + '...', scale) > w) s = s.slice(0, -1);
    return s.trimEnd() + '...';
  }
  // a dark band fading out at the ends (GMenu's backdrop band, horizontal fades at the given ends)
  function band(ctx, k, x, y, w, h, a, fl, fr) {
    const g = ctx.createLinearGradient(x * k, 0, (x + w) * k, 0);
    g.addColorStop(0, fl ? 'rgba(20,10,4,0)' : `rgba(20,10,4,${a})`); g.addColorStop(fl ? 0.08 : 0, `rgba(20,10,4,${a})`);
    g.addColorStop(fr ? 0.92 : 1, `rgba(20,10,4,${a})`); g.addColorStop(1, fr ? 'rgba(20,10,4,0)' : `rgba(20,10,4,${a})`);
    ctx.fillStyle = g; ctx.fillRect(x * k, y * k, w * k, h * k);
  }
  function selBand(ctx, k, x, y, w, h, fade) {   // the selected row: GMenu's red band
    const hb = ctx.createLinearGradient(x * k, 0, (x + w) * k, 0);
    hb.addColorStop(0, 'rgba(255,60,30,0)'); hb.addColorStop(0.15, `rgba(255,60,30,${0.3 * fade})`); hb.addColorStop(0.85, `rgba(255,60,30,${0.3 * fade})`); hb.addColorStop(1, 'rgba(255,60,30,0)');
    ctx.fillStyle = hb; ctx.fillRect(x * k, y * k, w * k, h * k);
  }
  function frame() {
    S.raf = 0;
    if (!S.shown || photo.state !== 2) { document.body.classList.remove('gphoto'); cv.hidden = true; return; }
    S.raf = requestAnimationFrame(frame);
    const on = active();
    document.body.classList.toggle('gphoto', on);
    cv.hidden = !on;
    if (on) draw();
  }
  function draw() {
    const ctx = cv.getContext('2d'), { k, W } = layout(), now = performance.now();
    const fade = Math.min(1, (now - S.t0) / 160), pulse = 0.75 + 0.25 * Math.sin(now / 160);
    const T = (s, x, y, o) => GameFont.draw(ctx, s, x, y, k, Object.assign({ smooth: smooth() }, o, { alpha: (o && o.alpha !== undefined ? o.alpha : 1) * fade }));
    ctx.clearRect(0, 0, cv.width, cv.height);
    S.hits = [];
    if (S.toast && now - S.toastAt > 2600) S.toast = '';
    if (S.toast) {   // a message (saved picture, ...) at the top, like the page's toast: centred left of the panel
      const a = Math.min(1, (2600 - (now - S.toastAt)) / 300), right = S.hidden ? W : W - PW - 6;
      const tw = Math.min(260, right - 12), cx = right / 2, lines = GameFont.wrap(S.toast.toUpperCase(), tw - 16, 0.55).slice(0, 2);
      ctx.globalAlpha = a; band(ctx, k, cx - tw / 2, 5, tw, 6 + lines.length * 9, 0.72, true, true); ctx.globalAlpha = 1;
      lines.forEach((l, j) => T(l, cx, 8 + j * 9, { scale: 0.55, color: C.text, align: 'center', alpha: a }));
    }
    if (S.hidden) {   // a clean view: only a short hint how to get the menus back, fading out
      const a = 1 - (now - S.hidAt) / 1800;
      if (a > 0) T(`${inputName('PHOTOUI')}: SHOW THE MENUS`, W - 8, 8, { scale: 0.5, color: C.dim, align: 'right', alpha: a });
      return;
    }
    const folded = !S.focus && look.min;
    const px = W - PW - 6;
    drawPanel(ctx, T, k, px, fade, pulse, now, folded);
    drawHud(ctx, T, k, W, folded ? W - 12 : px - 12, fade, now);
  }
  function drawPanel(ctx, T, k, px, fade, pulse, now, folded) {
    const p = page(), l = listOf(p), focus = S.focus;
    const bottom = folded ? 22 : 234;
    band(ctx, k, px, 6, PW, bottom - 6, focus ? 0.7 : 0.5, true, false);
    S.hits.push({ act: 'title', x0: px, x1: px + PW, y0: 6, y1: 20 });
    T(fit(titleOf(p).toUpperCase(), PW - (focus ? 14 : 36), 0.75), px + 8, 9, { scale: 0.75, color: C.title, alpha: focus ? 1 : 0.85 });
    if (!focus) {   // how to get the focus
      const nm = inputName('CAMBACK'), w = GameFont.measure(nm, 0.45) + 5;
      GFace.cap(ctx, T, k, 0, px + PW - 24 - w, 9.5, nm, fade); T('EDIT', px + PW - 4, 10, { scale: 0.45, color: C.dim, align: 'right' });
    }
    if (folded) { S.hits.push({ act: 'bg', x0: px, x1: px + PW, y0: 6, y1: bottom }); return; }
    const top = 23, listBottom = focus ? 172 : 230;
    if (l) drawList(ctx, T, k, px, top, listBottom, l, p, fade, pulse);
    else drawRows(ctx, T, k, px, top, listBottom, p, fade, pulse);
    if (focus) {
      drawDetail(ctx, T, k, px, now, l, p);
      // footer: A CHOOSE, B BACK / DONE, the D-pad CHANGE / PAGE (GMenu's faces)
      const FY = 222, FS = 0.45;
      let x = px + 10;
      GFace.round(ctx, T, k, 0, x, FY, 'A', 'rgb(40,90,230)', fade); T('CHOOSE', x + 8, FY + 1, { scale: FS, color: C.dim });
      x += 44;
      const bt = S.stack.length > 1 ? 'BACK' : 'DONE';
      GFace.round(ctx, T, k, 0, x, FY, 'B', 'rgb(30,160,60)', fade); T(bt, x + 8, FY + 1, { scale: FS, color: C.dim });
      S.hits.push({ act: 'back', x0: x - 6, x1: x + 10 + GameFont.measure(bt, FS), y0: FY - 3, y1: FY + 10 });
      x += 36;
      GFace.dpad(ctx, k, 0, x, FY, l ? 'all' : 'lr', fade); T(l ? 'PAGE' : 'CHANGE', x + 8, FY + 1, { scale: FS, color: C.dim });
    }
    S.hits.push({ act: 'bg', x0: px, x1: px + PW, y0: 6, y1: bottom });
  }
  function drawRows(ctx, T, k, px, top, bottom, p, fade, pulse) {
    const it = itemsOf(p), focus = S.focus;
    if (p.sel >= it.length) p.sel = Math.max(0, it.length - 1);
    if (!selectable(it[p.sel])) moveSel(1);
    const hOf = (x) => (x.tall ? 2 * RH - 1 : x.kind === 'head' ? RH - 0.5 : RH);
    // scroll: the selected row (and a head above it) visible; unfocused, the panel shows its first rows
    if (!focus) p.top = 0;
    else if (p.sel < p.top) p.top = p.sel;
    if (p.top > 0 && p.top === p.sel && it[p.top - 1] && it[p.top - 1].kind === 'head') p.top--;
    for (; focus;) { let y = top; for (let i = p.top; i <= p.sel; i++) y += hOf(it[i]); if (y <= bottom || p.top >= p.sel) break; p.top++; }
    let y = top, last = p.top;
    for (let i = p.top; i < it.length; i++) {
      const x = it[i], h = hOf(x);
      if (y + h > bottom) break;
      last = i;
      const sel = focus && i === p.sel, lock = lockOf(x);
      if (x.kind === 'head') { if (x.label) T(x.label.toUpperCase(), px + 8, y + 1.5, { scale: 0.45, color: C.head, alpha: 0.9 }); y += h; continue; }
      S.hits.push({ act: 'row', i, x0: px, x1: px + PW, y0: y - 1, y1: y + h - 1, xv: px + PW * 0.55 });
      if (sel) { selBand(ctx, k, px + 2, y - 1.5, PW - 4, h, 1); T('>', px + 3, y, { color: C.on, alpha: pulse, scale: RS }); }
      const lc = lock ? C.lock : sel ? C.text : focus ? C.dim : C.off;
      let v = '', vc = sel ? C.text : C.dim;
      if (x.kind === 'toggle') { const on = !!x.get(); v = x.names ? x.names[on ? 1 : 0] : on ? 'ON' : 'OFF'; vc = lock ? C.lock : on ? C.on : C.off; }
      else if (x.kind === 'choice') { v = labelOf(x.opts(), x.get()); vc = lock ? C.lock : x.get() === -1 || x.get() === 0 && x.list ? (sel ? C.text : C.dim) : C.on; }
      else if (x.kind === 'range') { v = x.text(); vc = lock ? C.lock : sel ? C.on : C.off; }
      else if (x.kind === 'link') v = x.text ? x.text() : '>';
      const arrows = sel && !lock && (x.kind === 'choice' || x.kind === 'range');
      if (x.tall) {   // the label, then the value on its own line (long names)
        T(x.label.toUpperCase(), px + 10, y, { scale: RS, color: lc });
        const vw = PW - 22 - (arrows ? 10 : 0);
        T(fit(v.toUpperCase(), vw, 0.5), px + 14 + (arrows ? 6 : 0), y + RH - 0.5, { scale: 0.5, color: vc });
        if (arrows) { T('<', px + 12, y + RH - 0.5, { scale: 0.5, color: vc, alpha: pulse }); T('>', px + PW - 8, y + RH - 0.5, { scale: 0.5, color: vc, alpha: pulse }); }
      } else {
        const lw = GameFont.measure(x.label.toUpperCase(), RS);
        T(fit(x.label.toUpperCase(), PW - 20, RS), px + 10, y, { scale: RS, color: lc });
        if (v) {
          const right = px + PW - (arrows ? 10 : 5), vw = Math.max(16, right - (px + 10 + lw + 6) - (arrows ? 8 : 0));
          const vt = fit(v.toUpperCase(), vw, 0.5);
          if (arrows) { T('<', right - GameFont.measure(vt, 0.5) - 7, y + 0.5, { scale: 0.5, color: vc, alpha: pulse }); T('>', right + 3, y + 0.5, { scale: 0.5, color: vc, alpha: pulse }); }
          T(vt, right, y + 0.5, { scale: 0.5, color: vc, align: 'right' });
        }
      }
      y += h;
    }
    const more = (s, yy) => T(s, px + PW / 2, yy, { color: C.dim, align: 'center', scale: 0.5 });
    if (p.top > 0) more('^', top - 4);
    if (last < it.length - 1) more('V', bottom - 3);
  }
  function drawList(ctx, T, k, px, top, bottom, l, p, fade, pulse) {
    const n = l.opts.length, LH = 9, rows = Math.max(1, Math.floor((bottom - top - 8) / LH)), cur = l.get();
    S.rowsVis = rows;
    p.sel = Math.max(0, Math.min(n - 1, p.sel));
    if (p.sel < p.top) p.top = p.sel;
    if (p.sel >= p.top + rows) p.top = p.sel - rows + 1;
    p.top = Math.max(0, Math.min(Math.max(0, n - rows), p.top));
    T(`${p.sel + 1} OF ${n}   PAGE ${Math.floor(p.sel / rows) + 1}/${Math.ceil(n / rows)}`, px + 10, top, { scale: 0.42, color: C.dim });
    const y0 = top + 8;
    for (let i = p.top; i < Math.min(n, p.top + rows); i++) {
      const y = y0 + (i - p.top) * LH, sel = i === p.sel, isCur = l.opts[i][0] === cur;
      S.hits.push({ act: 'entry', i, x0: px, x1: px + PW - 8, y0: y - 1, y1: y + LH - 1 });
      if (sel) { selBand(ctx, k, px + 2, y - 1.5, PW - 10, LH, 1); T('>', px + 3, y, { color: C.on, alpha: pulse, scale: 0.5 }); }
      if (isCur) { ctx.fillStyle = `rgba(255,255,0,${fade})`; ctx.beginPath(); ctx.moveTo((px + 11) * k, (y + 3) * k); ctx.lineTo((px + 13.5) * k, (y + 0.5) * k); ctx.lineTo((px + 16) * k, (y + 3) * k); ctx.lineTo((px + 13.5) * k, (y + 5.5) * k); ctx.fill(); }   // the current one: a yellow diamond (font 0 has no '*')
      T(fit(l.opts[i][1].toUpperCase(), PW - 28, 0.5), px + (isCur ? 18 : 10), y, { scale: 0.5, color: isCur ? C.on : sel ? C.text : C.dim });
    }
    // the scroll bar (click / drag)
    const bx = px + PW - 7, by = y0 - 1, bh = rows * LH;
    ctx.fillStyle = `rgba(255,255,255,${0.12 * fade})`; ctx.fillRect(bx * k, by * k, 2.5 * k, bh * k);
    const th = Math.max(6, bh * Math.min(1, rows / n)), ty = by + (n > rows ? (bh - th) * (p.top / (n - rows)) : 0);
    ctx.fillStyle = `rgba(255,200,60,${0.85 * fade})`; ctx.fillRect(bx * k, ty * k, 2.5 * k, th * k);
    S.hits.push({ act: 'bar', x0: bx - 3, x1: bx + 6, y0: by, y1: by + bh, by, bh });
  }
  // below the rows: the selected row's whole value (yellow) or why it cannot change, the game's report, then its help
  function drawDetail(ctx, T, k, px, now, l, p) {
    const y0 = 175, HS = 0.45;
    ctx.fillStyle = 'rgba(0,0,0,0.35)'; ctx.fillRect((px + 4) * k, y0 * k, (PW - 8) * k, 41 * k);
    let head = '', help = '';
    const err = ['', 'That model could not be loaded here.', 'That animation could not start.', ''][lkInfo(LR.ERR)] || '';
    if (l) { const o = l.opts[p.sel]; head = o ? o[1] : ''; help = 'A: choose. Left / right: a page. Hold up / down to go faster.'; }
    else {
      const it = itemsOf(p)[p.sel];
      if (it) {
        const lock = lockOf(it);
        head = lock || (it.kind === 'choice' ? labelOf(it.opts(), it.get()) : '');
        help = typeof it.help === 'function' ? it.help() : it.help || '';
      }
    }
    if (err) head = err + (head ? ' ' + head : '');
    const text = (head ? head + (/[.!?:]$/.test(head) ? ' ' : '. ') : '') + help;
    const lines = GameFont.wrap(text, PW - 14, HS), per = lines.length > 4 ? 3 : 4, pages = Math.max(1, Math.ceil(lines.length / per));   // paged: 3 lines + the counter
    const sig = p.id + ':' + p.sel + ':' + text;
    if (sig !== S.helpSig) { S.helpSig = sig; S.helpPage = 0; S.helpAt = now; }
    if (now - S.helpAt > 5000) { S.helpAt = now; S.helpPage = (S.helpPage + 1) % pages; }
    const hl = head ? GameFont.wrap(head + (/[.!?:]$/.test(head) ? ' ' : '. '), PW - 14, HS).length : 0;
    lines.slice(S.helpPage * per, S.helpPage * per + per).forEach((t, j) => T(t, px + 8, y0 + 2.5 + j * 9.5, { scale: HS, color: S.helpPage * per + j < hl ? (err && j === 0 && S.helpPage === 0 ? C.title : C.head) : C.text, alpha: 0.92 }));
    if (pages > 1) T(`${S.helpPage + 1}/${pages}`, px + PW - 6, y0 + 34, { scale: 0.4, color: C.dim, align: 'right' });
  }
  // the photo HUD (bottom left): title, the camera's numbers, the controls (paged), the buttons (also mouse targets)
  const HELP = 'Stick / WASD move. C buttons / right stick / IJKL / mouse look. R Z / E Q up and down. D-pad / arrows: left right roll, up down zoom (wheel too). B / F the game\'s view. L / R the game\'s HUD. A / Space save a PNG. P / Start / Enter back to the game.';
  function drawHud(ctx, T, k, W, maxW, fade, now) {
    const HW = Math.max(150, Math.min(232, maxW)), x0 = 6, HH = 64, y0 = 234 - HH;
    band(ctx, k, x0, y0, HW, HH, 0.62, false, true);
    S.hits.push({ act: 'bg', x0, x1: x0 + HW, y0, y1: y0 + HH });
    T('PHOTO MODE', x0 + 6, y0 + 4, { scale: 0.85, color: C.title });
    T('THE GAME IS FROZEN', x0 + HW - 10, y0 + 6, { scale: 0.42, color: C.dim, align: 'right' });
    if (now - S.infoAt > 200 && M && M._port_photo_info) {
      S.infoAt = now;
      const I = (i) => M._port_photo_info(i);
      S.info = `VIEW ${I(7).toFixed(0)}   ROLL ${I(5).toFixed(0)}   ${I(8).toFixed(0)} UNITS AWAY   HUD ${photo.hud ? 'ON' : 'OFF'}`;
    }
    T(fit(S.info, HW - 14, 0.48), x0 + 6, y0 + 17, { scale: 0.48, color: C.text });
    const lines = GameFont.wrap(HELP, HW - 18, 0.42), pages = Math.max(1, Math.ceil(lines.length / 2));
    if (now - S.hudAt > 5000) { S.hudAt = now; S.hudPage = (S.hudPage + 1) % pages; }
    S.hudPage %= pages;
    lines.slice(S.hudPage * 2, S.hudPage * 2 + 2).forEach((t, j) => T(t, x0 + 6, y0 + 26.5 + j * 8, { scale: 0.42, color: C.dim }));
    if (pages > 1) T(`${S.hudPage + 1}/${pages}`, x0 + HW - 10, y0 + 34.5, { scale: 0.38, color: C.dim, align: 'right' });
    // buttons: A SAVE, B VIEW, L HUD, START EXIT; then the panel's and the hide button's keys
    const FS = 0.45, F1 = y0 + 43, F2 = y0 + 54;
    let x = x0 + 12;
    const entry = (face, label, act, fy) => {
      const w0 = face(x, fy), lw = GameFont.measure(label, FS);
      T(label, x + w0 + 1, fy + 1, { scale: FS, color: C.dim });
      S.hits.unshift({ act: 'foot', fn: act, x0: x - 6, x1: x + w0 + 2 + lw, y0: fy - 3, y1: fy + 10 });
      x += w0 + lw + 9;
    };
    const round = (letter, fill) => (xx, fy) => GFace.round(ctx, T, k, 0, xx, fy, letter, fill, fade) + 1;
    const cap = (id) => (xx, fy) => GFace.cap(ctx, T, k, 0, xx - 4, fy, inputName(id), fade) - 2;
    entry(round('A', 'rgb(40,90,230)'), 'SAVE', () => photoCapture(), F1);
    entry(round('B', 'rgb(30,160,60)'), 'VIEW', () => { photo.viewReq = true; }, F1);
    entry(round('L', 'rgb(110,110,110)'), 'HUD', () => { photo.hud = !photo.hud; }, F1);
    entry(round('S', 'rgb(200,40,40)'), 'EXIT', () => photoRequest(false), F1);
    x = x0 + 12;
    entry(cap('CAMBACK'), 'POSE & OUTFIT', () => setFocus(!S.focus), F2);   // the same label either way: the buttons never move
    entry(cap('PHOTOUI'), 'HIDE MENUS', () => setHidden(true), F2);
  }

  // ---- mouse / touch: the overlay takes no pointer events itself (a click on the picture captures the mouse to look
  // around); these capture-phase listeners take the events that land on its rows first
  function unitXY(e) { const r = cv.getBoundingClientRect(); const k = r.height / 240; return { x: (e.clientX - r.left) / k, y: (e.clientY - r.top) / k }; }
  const hitAt = (x, y) => S.hits.find((h) => x >= h.x0 && x <= h.x1 && y >= h.y0 && y <= h.y1);
  function dragTo(y) {
    const h = S.drag, p = page(), l = listOf(p);
    if (!h || !l) return;
    const n = l.opts.length, f = Math.max(0, Math.min(1, (y - h.by) / h.bh));
    p.sel = Math.round(f * (n - 1)); p.top = Math.max(0, p.sel - Math.floor(S.rowsVis / 2));
  }
  function click(h, x, button) {
    if (button === 2) { if (S.focus) back(); return; }
    if (h.act === 'foot') { h.fn(); return; }
    if (h.act === 'title') { setFocus(!S.focus); return; }
    if (h.act === 'back') { back(); return; }
    if (h.act === 'bg') return;
    setFocus(true, true);   // P367: the row's own sound follows
    if (h.act === 'bar') { S.drag = h; dragTo(unitXYLast.y); return; }
    if (h.act === 'entry') { page().sel = h.i; pick(h.i); return; }
    if (h.act === 'row') {
      const p = page(), it = itemsOf(p)[h.i];
      p.sel = h.i;
      if ((it.kind === 'choice' || it.kind === 'range') && x > h.xv && !it.tall) change(it, x < h.xv + (h.x1 - h.xv) / 2 ? -1 : 1);
      else choose(it);
    }
  }
  let unitXYLast = { x: 0, y: 0 };
  function onPointer(e) {
    if (!active() || S.hidden || document.pointerLockElement) return;
    const u = unitXY(e); unitXYLast = u;
    if (e.type === 'pointermove') {
      if (S.drag) { dragTo(u.y); e.stopPropagation(); return; }
      const h = hitAt(u.x, u.y);
      if (S.focus && h && (e.movementX || e.movementY)) { if (h.act === 'row' || h.act === 'entry') page().sel = h.i; }
      return;
    }
    if (e.type === 'pointerup') { if (S.drag) { S.drag = null; e.stopPropagation(); } return; }
    const h = hitAt(u.x, u.y);
    if (e.type === 'pointerdown') { S.downHit = !!h; if (!h) return; e.preventDefault(); e.stopPropagation(); click(h, u.x, e.button); return; }
    if (h || (S.downHit && e.type === 'click')) { e.preventDefault(); e.stopPropagation(); if (e.type === 'click') S.downHit = false; }
  }
  for (const t of ['pointerdown', 'pointermove', 'pointerup', 'mousedown', 'mouseup', 'click', 'dblclick', 'contextmenu']) window.addEventListener(t, onPointer, true);
  window.addEventListener('wheel', (e) => {
    if (!active() || S.hidden || document.pointerLockElement) return;
    const u = unitXY(e), h = hitAt(u.x, u.y);
    if (!h || h.act === 'foot') return;
    e.preventDefault(); e.stopPropagation();
    if (!S.focus) setFocus(true, true);
    moveSel((e.deltaY > 0 ? 1 : -1) * (listOf(page()) ? 3 : 1), true);
  }, { capture: true, passive: false });

  // ---- main.js hooks
  function show(on) {
    if (on) {
      S.shown = true; S.focus = false; S.hidden = false; S.stack = [{ id: 'main', sel: 1, top: 0 }]; S.cache = null;
      S.prevNav = S.prevHide = true; S.prevBits = -1; S.t0 = performance.now(); S.toast = ''; S.drag = null;
      if (!S.raf) S.raf = requestAnimationFrame(frame);
      log('[gphoto] game-style photo mode');
    } else { S.shown = false; S.focus = false; document.body.classList.remove('gphoto'); cv.hidden = true; }
  }
  // a message: true = shown here (photo mode in the game's style), else the page shows it (GNet, in the game's font,
  // when the game-style menu is on and photo mode did not start)
  function toast(text) {
    if (active()) { S.toast = String(text); S.toastAt = performance.now(); snd(/^saved /.test(S.toast) ? 'choose' : 'error'); log(`[gphoto] ${text}`); return true; }
    if (window.GNet && fontOk() && photo.state !== 2) { GNet.show('PHOTO MODE', String(text), 3500, C.on); return true; }
    return false;
  }
  window.__gphoto = {   // test aid (tools/port/scripts/photo_menu_shots.sh)
    state: () => { const p = S.stack.length ? page() : null, l = p && listOf(p), it = p && !l ? itemsOf(p)[p.sel] : null;
      return { active: active(), focus: S.focus, hidden: S.hidden, page: p && p.id, sel: p && p.sel, top: p && p.top,
        item: l ? (l.opts[p.sel] || [])[1] : it && it.label, look: { anim: look.anim, frame: look.frame, play: look.play, model: look.model, items: look.items, attHide: look.attHide, face: look.face, dlHide: look.dlHide, dlShow: look.dlShow } }; },
    go: (id) => { setFocus(true); go(id); },
  };
  return { show, input, key, toast, active };
})();
window.GPhoto = GPhoto;
window.GameFont = GameFont;
window.MenuModel = MenuModel;
