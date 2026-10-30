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
  return { load, ready, measure, draw, wrap, glyphsOf, save, restore, get count() { return F.n; } };
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
    prev: 0, repeatAt: 0, held: 0, helpPage: 0, helpAt: 0, helpSel: '', homePrev: false, mx: -1, my: -1,
    cap: null, note: '', noteAt: 0, eh: false, ehT: 0, ehUsed: false, from: '', row: -1,
    pre: false, saved: false, busy: '', err: '', errAt: 0, pick: { code: '', cx: 0, cy: 0 } };   // P365: pre = opened before boot; busy / err / pick: the ONLINE pages
  const cv = document.getElementById('gmenu');
  const ROW = 15, ROWS = 8, TOP = 46, X0 = 34, X1 = 286;   // row spacing / visible rows / list top / label x / value right edge (units)
  // P363 / P364: opened from an OPTIONS row in the game's own menus: the last row of the main page goes back there
  const BACK = { pause: ['Back to pause', 'Close this menu and go back to the game\'s pause menu (B, Esc or Start on this line).'],
    title: ['Back to title', 'Close this menu and go back to the title menu (B, Esc or Start on this line).'],
    pre: ['Back to the start screen', 'Close this menu (B, Esc or Start on this line); then Start boots the game.'] };
  const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', off: 'rgb(170,170,170)', dim: 'rgb(150,150,150)', lock: 'rgb(120,120,120)', head: 'rgb(255,200,60)' };
  const smooth = () => !!opt('smoothfont');
  const wanted = () => !!opt('nativemenu');
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
      { kind: 'action', label: 'Page menu (developer)', help: 'The page\'s own menu: the same settings plus manual online codes, the debug console and developer tools.', act: () => { close(); drawerSet(true); toggle('options', true); } },
      { kind: 'action', get label() { return BACK[backKey()] ? BACK[backKey()][0] : 'Back to game'; }, get help() { return BACK[backKey()] ? BACK[backKey()][1] : 'Close this menu (B, Esc or Start on this line).'; }, act: () => close() },
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
  const backKey = () => (U.pre ? 'pre' : U.from);
  const go = (id) => { U.stack.push({ id, sel: 0, top: 0 }); U.helpSel = ''; U.note = ''; U.err = ''; };
  function itemsOf(p) {
    if (p.id === 'main') return mainItems();
    if (p.id === 'online') return onlineItems();
    if (p.id === 'pick') return [];
    if (p.id === 'keys' || p.id === 'pad') return bindItems(p.id === 'keys' ? 'key' : 'pad');
    const backRow = { kind: 'action', label: 'Back', help: 'Back to the options.', act: () => back() };
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
  const TITLES = { main: 'Options', keys: 'Keyboard keys', pad: 'Gamepad buttons', saves: 'Saves', online: 'Online', pick: 'Join room' };
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
  function back() { U.note = ''; if (U.stack.length > 1) { U.stack.pop(); U.helpSel = ''; } else close(); }

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
  function fail(e) { U.err = String((e && e.message) || e || ''); U.errAt = performance.now(); U.helpSel = ''; log(`[gmenu] online: ${U.err}`); }
  async function reloadInto(step) {   // during a game: restart the page into the ONLINE page's step
    if (!GameFont.save(romSha1)) { note('This browser keeps no data for this page: reload it, then open the menu (Esc) before pressing Start.'); return; }
    try { sessionStorage.setItem('gmenu.online', step); } catch (e) { note('This browser keeps no data for this page: reload it, then open the menu (Esc) before pressing Start.'); return; }
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
    const st = onlineState(), t = NT(), backRow = { kind: 'action', label: 'Back', help: 'Back to the options (a room stays open).', act: () => back() };
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
        { kind: 'action', label: 'Manual codes (page menu)', help: 'Advanced: connect without the room server by copying long codes between the players (the page menu\'s Online panel).' + restart,
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
    if (P.code.length >= 5) { P.cx = 0; P.cy = PROWS; return; }
    P.code += c;
    if (P.code.length === 5) { P.cx = 0; P.cy = PROWS; }   // the code is complete: on JOIN
  }
  function pickDelete() { if (U.busy) return false; U.err = ''; if (!U.pick.code) return false; U.pick.code = U.pick.code.slice(0, -1); return true; }
  function pickChoose() {
    const c = pickCell(U.pick.cx, U.pick.cy);
    if (Q.get('gmenutest')) log(`[gmenu] picker: ${c} (code ${U.pick.code})`);
    if (c === 'JOIN') onlineJoin(); else if (c === 'DEL') pickDelete(); else pickType(c);
  }
  function pickMove(dx, dy) {
    const P = U.pick;
    if (dy) P.cy = (P.cy + dy + PROWS + 1) % (PROWS + 1);
    if (dx && P.cy < PROWS) P.cx = (P.cx + dx + PCOLS) % PCOLS;
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
    if (!c || v === undefined) { note('Not changed.'); return; }
    bindSet(c.kind, c.id, v);
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
    const eb = padMap.PHOTO, eh = eb !== undefined && raw(eb), on = wanted() && photo.state !== 2;
    if (eh && !U.eh) U.ehT = now;
    if (U.open) { if (eh && !U.eh && !U.ehUsed && !U.cap) { U.ehUsed = true; close(); } }
    else if (on && eh && !U.ehUsed && now - U.ehT >= HOLD_MS) { U.ehUsed = true; if (open('hold')) log('[gmenu] opened by holding the pad\'s photo button'); }
    else if (on && !eh && U.eh && !U.ehUsed && now - U.ehT < HOLD_MS) d.photo = true;   // a short press: photo mode (one frame's press)
    // the held pad button is no photo press (yet), also on the frame whose press closed the menu (pad 1 reaches photoPoll then)
    if (on && eh && !U.open) d.photo = !!(keyMap.PHOTO && keysDown.has(keyMap.PHOTO));
    if (!eh) U.ehUsed = false;
    U.eh = eh;
  }
  // P363: the "OPTIONS" row in the game's own pause menu (game_pause_update, game_eu_20B730.c); P364: the same row on
  // the title menu's save slot pages (title_slot_page) and MULTI mode pages (menu_mode_select_page). The page switches
  // the rows on (port_set_gmenu_row) only while this menu's option is on and the game is local: never online, while an
  // online session is being set up (a room / invite exists: PortNet.t.role), while recording or replaying, or under
  // ?netdet (the menus' state is hashed there; the C side checks the same again). Choosing a row leaves a request
  // (port_gmenu_take_request: 1 = pause menu, 2 = title menu) that opens this menu over the game's own menu; the A
  // press that chose it is masked by U.prev = -1 (the first poll after open only records the held buttons).
  const netBusy = () => !!(window.PortNet && PortNet.t && PortNet.t.role);
  function gameRows() {
    if (typeof M === 'undefined' || !M || !M._port_set_gmenu_row) return;
    const on = wanted() && running === 'game' && !netCfg && !recCfg && !NETDET && !netBusy() ? 1 : 0;
    if (on !== U.row) { U.row = on; M._port_set_gmenu_row(on); log(`[gmenu] game menu OPTIONS rows ${on ? 'on' : 'off'}`); }
    const req = M._port_gmenu_take_request();
    if (req && on && !U.open) {
      const how = req === 2 ? 'title' : 'pause';
      if (open(how)) log(`[gmenu] opened from the ${how} menu's OPTIONS row`);
    }
  }
  function poll(d) {
    gameRows();
    if (U.open && U.pre && running) close();   // P365: the game boots (an online match starts): the pages are done
    pendingOnline();
    const gp = (navigator.getGamepads ? Array.from(navigator.getGamepads()) : []).find((g) => g && g.connected);
    const raw = (i) => !!(gp && gp.buttons[i] && (gp.buttons[i].pressed || gp.buttons[i].value > 0.5));
    const now = performance.now();
    const home = raw(16);
    if (home && !U.homePrev && !U.cap) { U.homePrev = true; if (U.open) close(); else if (wanted()) open(); return U.open; }
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
    const btn = (x, letter, fill) => {
      ctx.save(); ctx.globalAlpha = 0.95 * fade;
      ctx.beginPath(); ctx.arc((ox + x) * k, (FY + 3.4) * k, 5.2 * k, 0, 2 * Math.PI); ctx.fillStyle = fill; ctx.fill();
      ctx.lineWidth = Math.max(1, 0.7 * k); ctx.strokeStyle = 'rgba(0,0,0,0.6)'; ctx.stroke(); ctx.restore();
      T(letter, x, FY + 0.6, { scale: 0.5, color: '#fff', align: 'center' });
      return 7;
    };
    const arrows = (x) => {   // a small D-pad cross with left / right arms lit
      const cy = FY + 3.4;
      ctx.save(); ctx.globalAlpha = 0.95 * fade; ctx.fillStyle = 'rgb(85,85,85)'; ctx.strokeStyle = 'rgba(0,0,0,0.6)'; ctx.lineWidth = Math.max(1, 0.5 * k);
      ctx.beginPath(); ctx.rect((ox + x - 5.4) * k, (cy - 1.9) * k, 10.8 * k, 3.8 * k); ctx.rect((ox + x - 1.9) * k, (cy - 5.4) * k, 3.8 * k, 10.8 * k); ctx.stroke(); ctx.fill();
      ctx.fillStyle = 'rgb(240,240,240)';
      for (const sx of [-1, 1]) { ctx.beginPath(); ctx.moveTo((ox + x + sx * 4.9) * k, cy * k); ctx.lineTo((ox + x + sx * 2.5) * k, (cy - 1.4) * k); ctx.lineTo((ox + x + sx * 2.5) * k, (cy + 1.4) * k); ctx.fill(); }
      ctx.restore();
      return 7;
    };
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
  // GUESTQ='&opt=nativemenu:1&gmenuopen=40' keeps it open on a guest during an online session)
  if (Q.get('gmenuopen')) {
    const at = performance.now() + 1000 * +Q.get('gmenuopen');
    const tryOpen = () => { if (performance.now() >= at && open()) log('[gmenu] opened by ?gmenuopen'); else setTimeout(tryOpen, 500); };
    setTimeout(tryOpen, 1000 * +Q.get('gmenuopen'));
  }

  // test aid ?gmenupad=S (P362): S seconds after load a fake standard gamepad holds Back (the photo button) 40 frames
  // (the hold entry opens the menu), goes to Controls > Gamepad buttons, back twice, and closes the menu with a Back
  // press; each step is logged. netpair GUESTQ='&opt=nativemenu:1&gmenupad=70' runs it on a guest online (page-only:
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

  return { open, close, back, poll, key, wanted, note, get isOpen() { return U.open; },
    state: () => ({ open: U.open, pre: U.pre, from: U.from, page: U.open ? page().id : null, sel: U.open ? page().sel : -1, item: U.open ? (itemsOf(page())[page().sel] || {}).label : null,
      online: onlineState(), code: NT() && NT().room ? NT().room.code : '', typed: U.pick.code, cursor: pickCell(U.pick.cx, U.pick.cy), joined: joinedCount(), busy: U.busy, err: U.err }) };
})();
window.GMenu = GMenu;

// ---------------------------------------------------------------- P365 online messages over the game (option nativemenu)
// The lockstep session's messages in the game's font instead of page text: "waiting for player 2…" while the game waits
// for a player's input (main.js's tick handler decides when, as for the page's #netwait), a player who left, the desync
// report, and other connection problems during the session. A canvas over the picture that takes no input; drawn only
// while a message is up. Page-only: it reads net.js's events and never touches the game.
const GNet = (() => {
  const cv = document.getElementById('gnet');
  const S = { wait: '', box: null, raf: 0, desync: '' };
  const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', dim: 'rgb(170,170,170)' };
  const wanted = () => !!opt('nativemenu');
  const kick = () => { if (!S.raf) S.raf = requestAnimationFrame(draw); };
  function wait(t) { if (t !== S.wait) { S.wait = t; kick(); } }
  function show(title, text, ms, color) { S.box = { title, text, until: performance.now() + ms, color: color || C.title, t0: performance.now() }; kick(); log(`[gnet] ${title}: ${text}`); }
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
      S.desync = `DESYNC AT RETRACE ${d.frame}: OPTIONS > ONLINE`;
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
window.GameFont = GameFont;
window.MenuModel = MenuModel;
