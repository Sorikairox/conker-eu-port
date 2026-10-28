// P354 trailer compositor + encoder ("Conker's Good Fur Day"). Runs in headless Chrome (render.mjs serves it):
//   /t/compose.html                     encode the whole trailer: H.264 (WebCodecs VideoEncoder) + AAC (AudioEncoder) in
//                                       an MP4 (mp4-muxer), POSTed to /upload/trailer.mp4
//   /t/compose.html?preview=0,120,...   only these frames as JPEGs (/upload/key_NNNNN.jpg), no encoding
// Inputs (all ROM-derived, local only, served from port_work/trailer under /w/): the captured shots (capture.mjs:
// shots/NAME/f*.jpg + audio.pcm + meta.json), the page pictures (pagecap.mjs: pages/NAME/), the online session's
// screenshots (net4.sh: net4/), the game's font (fontdump.mjs: font/font.json).
// Titles use the game's own font: the glyph bitmaps the game decoded from the ROM (font 0, the text_draw_string font),
// upscaled with nearest-neighbour pixels and drawn white / tinted with a dark outline like the game's on-screen text.
'use strict';
const W = 1920, H = 1080, FPS = 60, DUR = 43.0, NFR = Math.round(DUR * FPS);
const Q = new URLSearchParams(location.search);
const logEl = document.getElementById('log');
const log = (s) => { console.log(s); const d = document.createElement('div'); d.textContent = s; logEl.appendChild(d); };
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
const clamp = (x, a = 0, b = 1) => Math.max(a, Math.min(b, x));
const ease = (x) => { x = clamp(x); return x * x * (3 - 2 * x); };
const easeOut = (x) => 1 - Math.pow(1 - clamp(x), 3);
const pad5 = (i) => String(i).padStart(5, '0');
const ACCENT = '#f2b233', ORANGE = '#e8742a';

// ---------------------------------------------------------------- pictures
const cache = new Map();
async function img(url) {
  if (cache.has(url)) { const v = cache.get(url); cache.delete(url); cache.set(url, v); return v; }
  const r = await fetch(url); if (!r.ok) throw new Error('missing ' + url);
  const bm = await createImageBitmap(await r.blob());
  cache.set(url, bm);
  while (cache.size > 90) { const [k, v] = cache.entries().next().value; v.close(); cache.delete(k); }
  return bm;
}
const metas = {};
async function meta(shot) { if (!metas[shot]) metas[shot] = await (await fetch(`/w/shots/${shot}/meta.json`)).json(); return metas[shot]; }
// picture i of a captured shot (clamped to the captured range)
async function shotPic(shot, i) { const m = await meta(shot); return img(`/w/shots/${shot}/f${pad5(clamp(Math.round(i), 0, m.frames.length - 1))}.jpg`); }
function cover(g, bm, x, y, w, h, sx = 0, sy = 0, sw = bm.width, sh = bm.height) { g.drawImage(bm, sx, sy, sw, sh, x, y, w, h); }

// ---------------------------------------------------------------- the game's font
let FONT = null; const glyphCv = {};
async function loadFont() {
  FONT = await (await fetch('/w/font/font.json')).json();
  for (const [k, gl] of Object.entries(FONT.glyphs)) {
    const c = new OffscreenCanvas(gl.w, gl.h), x = c.getContext('2d'), id = x.createImageData(gl.w, gl.h);
    for (let i = 0; i < gl.w * gl.h; i++) { const v = gl.px[i]; id.data[4 * i] = id.data[4 * i + 1] = id.data[4 * i + 2] = 255; id.data[4 * i + 3] = v; }
    x.putImageData(id, 0, 0); glyphCv[k] = c;
  }
}
function glyphOf(ch) {   // text_char_to_glyph: lower case -> upper case, ' ' = 0x60, else the index in g_text_glyph_chars
  let c = ch.charCodeAt(0);
  if (c >= 0x61 && c <= 0x7A) c -= 0x20;
  if (c === 0x20) return 0x60;
  const i = FONT.chars.indexOf(c);
  return i < 0 ? 0x60 : i;
}
// the string at the font's own pixel size: { canvas (outline + fill), w, h, base } ; letter spacing as the game
// (x += x offset before, x += width - 1 after), line height 12
const textCache = new Map();
function textBitmap(str, fill, outline = 'rgba(10,8,6,0.92)', spacing = 0) {
  const key = str + '|' + fill + '|' + outline + '|' + spacing;
  if (textCache.has(key)) return textCache.get(key);
  let w = 0;
  for (const ch of str) { const k = glyphOf(ch), gl = FONT.glyphs[k]; w += gl ? gl.xo + gl.w - 1 + spacing : 5 + spacing; }
  const P = 2, cw = w + 2 * P + 2, ch = 13 + 2 * P;
  const mask = new OffscreenCanvas(cw, ch), m = mask.getContext('2d');
  let x = P;
  for (const c of str) {
    const k = glyphOf(c), gl = FONT.glyphs[k];
    if (!gl) { x += 5 + spacing; continue; }
    m.drawImage(glyphCv[k], x + gl.xo, P + gl.yo); x += gl.xo + gl.w - 1 + spacing;
  }
  const out = new OffscreenCanvas(cw, ch), o = out.getContext('2d');
  if (outline) {   // 1 font pixel of dark outline around the letters (the game's text has a dark rim)
    const sh = new OffscreenCanvas(cw, ch), s = sh.getContext('2d');
    s.drawImage(mask, 0, 0); s.globalCompositeOperation = 'source-in'; s.fillStyle = outline; s.fillRect(0, 0, cw, ch);
    for (const [dx, dy] of [[-1, 0], [1, 0], [0, -1], [0, 1], [-1, -1], [1, -1], [-1, 1], [1, 1], [0, 2], [1, 2]]) o.drawImage(sh, dx, dy);
  }
  const fl = new OffscreenCanvas(cw, ch), f = fl.getContext('2d');
  f.drawImage(mask, 0, 0); f.globalCompositeOperation = 'source-in';
  if (Array.isArray(fill)) { const gr = f.createLinearGradient(0, P, 0, P + 11); fill.forEach((c, i) => gr.addColorStop(i / (fill.length - 1), c)); f.fillStyle = gr; }
  else f.fillStyle = fill;
  f.fillRect(0, 0, cw, ch);
  o.drawImage(fl, 0, 0);
  const r = { canvas: out, w: cw, h: ch, P };
  textCache.set(key, r);
  return r;
}
// draw text with the font scaled s times (nearest neighbour), anchored at (x, y) = top of the cap height
function text(g, str, x, y, s, { fill = '#fff', outline, align = 'left', alpha = 1, spacing = 0, shadow = true } = {}) {
  const t = textBitmap(str, fill, outline, spacing);
  const w = t.w * s, h = t.h * s;
  const dx = align === 'center' ? x - w / 2 : align === 'right' ? x - w : x;
  g.save(); g.globalAlpha *= alpha; g.imageSmoothingEnabled = false;
  if (shadow) { g.shadowColor = 'rgba(0,0,0,0.55)'; g.shadowBlur = 3 * s; g.shadowOffsetY = s; }
  g.drawImage(t.canvas, Math.round(dx - t.P * s), Math.round(y - t.P * s), Math.round(w), Math.round(h));
  g.restore();
  return w;
}
const textW = (str, s, spacing = 0) => textBitmap(str, '#fff', undefined, spacing).w * s;

// ---------------------------------------------------------------- building blocks
function vignette(g, a = 0.55) {
  const gr = g.createRadialGradient(W / 2, H / 2, H * 0.35, W / 2, H / 2, H * 0.95);
  gr.addColorStop(0, 'rgba(0,0,0,0)'); gr.addColorStop(1, `rgba(0,0,0,${a})`);
  g.fillStyle = gr; g.fillRect(0, 0, W, H);
}
// feature caption: a big title + a smaller line, bottom left, sliding in; a dark band under it for contrast
function caption(g, lt, dur, title, sub, { x = 90, y = 862, s = 7, s2 = 3.2 } = {}) {
  const a = clamp(lt / 0.35) * clamp((dur - lt) / 0.3);
  if (a <= 0) return;
  const gr = g.createLinearGradient(0, y - 120, 0, H);
  gr.addColorStop(0, 'rgba(0,0,0,0)'); gr.addColorStop(0.55, `rgba(0,0,0,${0.55 * a})`); gr.addColorStop(1, `rgba(0,0,0,${0.7 * a})`);
  g.fillStyle = gr; g.fillRect(0, y - 120, W, H - y + 120);
  const slide = (1 - easeOut(lt / 0.45)) * -60;
  text(g, title, x + slide, y, s, { fill: ['#fff7d6', ACCENT, ORANGE], alpha: a });
  if (sub) text(g, sub, x + slide * 0.6, y + 13 * s + 14, s2, { fill: '#f4efe6', alpha: clamp((lt - 0.25) / 0.35) * a });
}
function label(g, str, x, y, s = 3, opts = {}) {   // a small tag on a dark pill
  const w = textW(str, s) + 26, h = 13 * s + 14;
  g.fillStyle = 'rgba(12,12,14,0.72)'; roundRect(g, x - (opts.align === 'center' ? w / 2 : 0), y, w, h, 10); g.fill();
  text(g, str, x + (opts.align === 'center' ? 0 : 13), y + 9, s, { ...opts, shadow: false });
}
function roundRect(g, x, y, w, h, r) { g.beginPath(); g.roundRect(x, y, w, h, r); }
// a desktop Chrome window (dark theme) around a page picture: tab strip, address bar with the site's URL
function browserWindow(g, page, x, y, w, urlChars = 1e9) {
  const kk = w / 1280, bar = 78 * kk, ph = w * page.height / page.width;
  g.save();
  g.shadowColor = 'rgba(0,0,0,0.6)'; g.shadowBlur = 40; g.shadowOffsetY = 12;
  g.fillStyle = '#202124'; roundRect(g, x, y, w, bar + ph, 12); g.fill();
  g.restore();
  g.save(); roundRect(g, x, y, w, bar + ph, 12); g.clip();
  const k = kk;
  g.fillStyle = '#202124'; g.fillRect(x, y, w, 36 * k);
  // tab
  g.fillStyle = '#35363a'; roundRect(g, x + 78 * k, y + 6 * k, 250 * k, 32 * k, 8 * k); g.fill();
  g.fillStyle = ACCENT; g.beginPath(); g.arc(x + 96 * k, y + 22 * k, 6 * k, 0, 7); g.fill();
  g.fillStyle = '#e8eaed'; g.font = `${13 * k}px system-ui, sans-serif`; g.fillText('Conker port', x + 110 * k, y + 27 * k);
  g.fillStyle = '#9aa0a6'; g.fillText('×', x + 308 * k, y + 27 * k);
  for (const [i, c] of [['#ff5f57'], ['#febc2e'], ['#28c840']].entries()) { g.fillStyle = c[0]; g.beginPath(); g.arc(x + (18 + i * 18) * k, y + 20 * k, 6 * k, 0, 7); g.fill(); }
  // toolbar + address field
  g.fillStyle = '#35363a'; g.fillRect(x, y + 38 * k, w, 40 * k);
  g.fillStyle = '#9aa0a6'; g.font = `${18 * k}px system-ui, sans-serif`;
  g.fillText('←', x + 16 * k, y + 64 * k); g.fillText('→', x + 46 * k, y + 64 * k); g.fillText('↻', x + 78 * k, y + 64 * k);
  g.fillStyle = '#202124'; roundRect(g, x + 110 * k, y + 44 * k, w - 170 * k, 28 * k, 14 * k); g.fill();
  // lock
  g.strokeStyle = '#bdc1c6'; g.lineWidth = 1.6 * k; g.beginPath(); g.arc(x + 130 * k, y + 55 * k, 3.5 * k, Math.PI, 0); g.stroke();
  g.fillStyle = '#bdc1c6'; g.fillRect(x + 125 * k, y + 55 * k, 10 * k, 8 * k);
  const url = 'conker-web-port.netlify.app'.slice(0, Math.max(0, urlChars));
  g.font = `${15 * k}px system-ui, sans-serif`; g.fillStyle = '#e8eaed'; g.fillText(url, x + 146 * k, y + 63 * k);
  if (urlChars < 27 && Math.floor(performanceNow * 2) % 2 === 0) { const tw = g.measureText(url).width; g.fillRect(x + 147 * k + tw, y + 50 * k, 1.5 * k, 17 * k); }
  g.drawImage(page, x, y + bar, w, ph);
  g.restore();
  return { x, y: y + bar, w, h: ph, k: w / page.width };
}
let performanceNow = 0;   // the timeline time of the frame being drawn (for blinking carets)
function cursor(g, x, y, s = 1) {
  g.save(); g.translate(x, y); g.scale(s, s);
  g.beginPath(); g.moveTo(0, 0); g.lineTo(0, 26); g.lineTo(7, 20); g.lineTo(12, 31); g.lineTo(17, 29); g.lineTo(12, 18); g.lineTo(21, 18); g.closePath();
  g.fillStyle = '#fff'; g.fill(); g.strokeStyle = '#000'; g.lineWidth = 1.5; g.stroke(); g.restore();
}
function fileChip(g, x, y, a = 1) {
  g.save(); g.globalAlpha = a;
  g.fillStyle = '#2b2f37'; g.strokeStyle = ACCENT; g.lineWidth = 2; roundRect(g, x, y, 230, 54, 10); g.fill(); g.stroke();
  g.fillStyle = '#e8eaed'; g.fillRect(x + 14, y + 10, 26, 34); g.fillStyle = '#2b2f37'; g.fillRect(x + 32, y + 10, 8, 8);
  g.fillStyle = '#e8eaed'; g.font = '600 17px system-ui, sans-serif'; g.fillText('your-game.z64', x + 52, y + 26);
  g.fillStyle = '#9aa0a6'; g.font = '13px system-ui, sans-serif'; g.fillText('64 MB · your own ROM', x + 52, y + 44);
  g.restore();
}

// ---------------------------------------------------------------- the edit (seconds on the timeline)
// Each segment draws itself into its own layer; layers overlap for the cross-fades (fade in / out seconds).
const SEG = [];
const seg = (a, b, fin, fout, draw) => SEG.push({ a, b, fin, fout, draw });
const T = { title: 0, browser: 3.8, wide: 9.6, ledge: 15.0, spin: 20.2, online: 25.4, more: 32.6, end: 38.1 };

// A. title card over a dimmed, blurred run on level 0x29
seg(T.title, T.browser + 0.3, 0.8, 0.3, async (g, lt) => {
  g.filter = 'blur(7px) brightness(0.42) saturate(1.1)';
  g.drawImage(await shotPic('run29', 200 + lt * 60), -40, -22, W + 80, H + 44);
  g.filter = 'none'; vignette(g, 0.7);
  const a = clamp((lt - 0.35) / 0.5), sc = 9 * (0.92 + 0.08 * easeOut((lt - 0.35) / 0.8));
  text(g, "CONKER'S", W / 2, 330 - 6 * sc + 40, sc * 0.62, { align: 'center', fill: '#fff', alpha: a });
  text(g, 'GOOD FUR DAY', W / 2, 430, sc, { align: 'center', fill: ['#fff4c2', ACCENT, ORANGE], alpha: a, spacing: 1 });
  const b = clamp((lt - 1.5) / 0.5);
  text(g, 'A FAN-MADE BROWSER PORT', W / 2, 600, 3.6, { align: 'center', fill: '#e9e3d6', alpha: b });
});

// B. plays in your browser: the real page in a Chrome window: drop screen, the ROM picked, the game running
function urlPill(g, x, y, chars, a) {   // the address bar, magnified: lock + the site's URL being typed
  if (a <= 0) return;
  g.save(); g.globalAlpha = a;
  const url = 'conker-web-port.netlify.app', shown = url.slice(0, Math.max(0, chars));
  g.font = '500 34px system-ui, sans-serif'; const tw = g.measureText(url).width;
  g.shadowColor = 'rgba(0,0,0,0.6)'; g.shadowBlur = 24;
  g.fillStyle = '#202124'; g.strokeStyle = 'rgba(242,178,51,0.9)'; g.lineWidth = 3; roundRect(g, x, y, tw + 110, 66, 33); g.fill(); g.stroke();
  g.shadowColor = 'transparent';
  g.strokeStyle = '#bdc1c6'; g.lineWidth = 3; g.beginPath(); g.arc(x + 42, y + 30, 7, Math.PI, 0); g.stroke();
  g.fillStyle = '#bdc1c6'; g.fillRect(x + 32, y + 30, 20, 15);
  g.fillStyle = '#e8eaed'; g.fillText(shown, x + 72, y + 45);
  if (chars < url.length || Math.floor(performanceNow * 2.5) % 2 === 0) { const w2 = g.measureText(shown).width; g.fillRect(x + 74 + w2, y + 17, 3, 34); }
  g.restore();
}
seg(T.browser, T.wide + 0.25, 0.3, 0.25, async (g, lt) => {
  const bg = g.createRadialGradient(W / 2, H * 0.55, 100, W / 2, H * 0.55, 1100); bg.addColorStop(0, '#2b2517'); bg.addColorStop(1, '#0b0b0d');
  g.fillStyle = bg; g.fillRect(0, 0, W, H);
  const tDrop = 2.0, tRom = 2.55;
  let page;
  if (lt < tDrop) page = await img('/w/pages/site/still_0_drop.jpg');
  else if (lt < tRom) page = await img('/w/pages/site/still_1_rom.jpg');
  else page = await img(`/w/pages/site/f${pad5(Math.min(299, Math.round((lt - tRom) * 60)))}.jpg`);
  const ww = 1360, wx = (W - ww) / 2, wy = 150;
  const r = browserWindow(g, page, wx, wy, ww, Math.floor(lt * 30));
  // the ROM file dragged onto the page's drop zone, then the cursor clicks Start
  const cx = r.x + 640 * r.k, cy = r.y + 330 * r.k;
  if (lt < tDrop + 0.1) {
    const p = easeOut((lt - 0.6) / 1.0), fx = 1700 - p * (1700 - (cx - 115)), fy = 1060 - p * (1060 - (cy - 27));
    if (p > 0.97) { g.strokeStyle = ACCENT; g.lineWidth = 4; g.setLineDash([14, 10]); roundRect(g, r.x + 18 * r.k, r.y + 18 * r.k, 1228 * r.k, 544 * r.k, 10); g.stroke(); g.setLineDash([]); }
    fileChip(g, fx, fy, clamp((lt - 0.5) / 0.2) * clamp((tDrop + 0.1 - lt) / 0.15));
    cursor(g, fx + 150, fy + 34, 1.4);
  } else if (lt < tRom + 0.25) {
    const sx = r.x + 150 * r.k, sy = r.y + 26 * r.k, p = easeOut((lt - tDrop) / 0.45);
    cursor(g, cx + (sx - cx) * p, cy + (sy - cy) * p, 1.4);
  }
  caption(g, lt, 5.8 + 0.25, 'PLAYS IN YOUR BROWSER', null, { x: 70, y: 40, s: 6 });
  urlPill(g, 1150, 42, Math.floor((lt - 0.25) * 22), clamp((lt - 0.2) / 0.3) * clamp((2.6 - lt) / 0.3));
  const b = clamp((lt - tRom) / 0.4) * clamp((6.05 - lt) / 0.3);
  if (b > 0) { text(g, 'NO INSTALL', 1240, 58, 5.4, { fill: ['#fff7d6', ACCENT], alpha: b }); }
  if (b > 0) text(g, 'JUST BRING YOUR OWN ROM', W / 2, 1022, 3.4, { align: 'center', fill: '#fff', alpha: b });
});

// C. widescreen: the original 4:3 picture (640 x 480, every option off), then the same moment in 16:9, full resolution
seg(T.wide, T.ledge + 0.25, 0.25, 0.25, async (g, lt) => {
  const i = 300 + lt * 60, tw = 2.1, tr = 0.8;
  const p = ease((lt - tw) / tr);
  g.fillStyle = '#000'; g.fillRect(0, 0, W, H);
  // the modern picture under, revealed from the 4:3 frame outwards
  const modern = await shotPic('run29', i), old = await shotPic('run29_n64', i);
  const halfW = 720 + (W / 2 - 720) * p;
  if (p > 0) { g.save(); g.beginPath(); g.rect(W / 2 - halfW, 0, 2 * halfW, H); g.clip(); g.drawImage(modern, 0, 0, W, H); g.restore(); }
  if (p < 1) {
    g.save(); g.globalAlpha = 1 - clamp((lt - tw - tr * 0.5) / (tr * 0.5)); g.imageSmoothingEnabled = true;
    g.drawImage(old, 240, 0, 1440, 1080); g.restore();
  }
  if (p > 0 && p < 1) { g.fillStyle = `rgba(242,178,51,${0.9 * (1 - p)})`; g.fillRect(W / 2 - halfW - 3, 0, 6, H); g.fillRect(W / 2 + halfW - 3, 0, 6, H); }
  if (lt < tw + 0.2) label(g, 'ORIGINAL: 4:3, 640 X 480', 260, 40, 3, { fill: '#fff', alpha: clamp(lt / 0.3) * clamp((tw + 0.2 - lt) / 0.2) });
  else label(g, 'PORT: 16:9, 1920 X 1080', 60, 40, 3, { fill: ACCENT, alpha: clamp((lt - tw - 0.4) / 0.3) });
  caption(g, lt - tw - 0.15, 5.4 + 0.25 - tw - 0.15, 'WIDESCREEN', 'FULL RESOLUTION - SHARP HI-RES 2D');
});

// D. ledge grab (level 0x13 crates): jump, catch the edge, hang, pull up
seg(T.ledge, T.spin + 0.25, 0.25, 0.25, async (g, lt) => {
  g.drawImage(await shotPic('ledge13', 36 + lt * 60), 0, 0, W, H);
  vignette(g, 0.35);
  caption(g, lt - 0.3, 5.2 - 0.3 + 0.25, 'LEDGE GRAB', 'CATCH THE EDGE - PULL YOURSELF UP');
});

// E. longer tail spin: the same jump with the option off (left) and on (right)
seg(T.spin, T.online + 0.25, 0.25, 0.25, async (g, lt) => {
  g.fillStyle = '#0c0c0f'; g.fillRect(0, 0, W, H);
  const i = 90 + lt * 60, w = 940, h = w * 9 / 16, y = 250;
  const zc = 1.3, cw = W / zc, chh = H / zc, cx = (W - cw) / 2, cy = (H - chh) / 2 + 40;   // a little closer to Conker
  g.drawImage(await shotPic('spin_off', i), cx, cy, cw, chh, 13, y, w, h);
  g.drawImage(await shotPic('spin_on', i), cx, cy, cw, chh, W - 13 - w, y, w, h);
  text(g, 'ORIGINAL', 13 + w / 2, y - 64, 4, { align: 'center', fill: '#e9e3d6' });
  text(g, 'WITH THE OPTION', W - 13 - w / 2, y - 64, 4, { align: 'center', fill: ACCENT });
  caption(g, lt - 0.1, 5.2 + 0.25 - 0.1, 'LONGER TAIL SPIN', 'HOVER TWICE AS LONG', { y: 878 });
});

// F. online: the Online panel of the host's page (real 4-window session: room code, players 2 to 4 join), then the
// 4-player split screen
seg(T.online, T.more + 0.25, 0.25, 0.25, async (g, lt) => {
  const tp = 2.6;
  if (lt < tp) {
    g.fillStyle = '#0d0e11'; g.fillRect(0, 0, W, H);
    g.filter = 'blur(10px) brightness(0.35)'; g.drawImage(await shotPic('mp4', 0), -40, -20, W + 80, H + 40); g.filter = 'none';
    const k = Math.min(3, Math.floor(lt / 0.62)), pic = await img(`/w/net4/host_join${k}.png`);
    const sx = 1124, sy = 236, sw = 361, sh = 330, s = 2.3, dw = sw * s, dh = sh * s, dx = W - dw - 150, dy = (H - dh) / 2 - 40;
    g.save(); g.shadowColor = 'rgba(0,0,0,0.7)'; g.shadowBlur = 40; g.fillStyle = '#1b1e24'; roundRect(g, dx - 18, dy - 18, dw + 36, dh + 36, 16); g.fill(); g.restore();
    g.drawImage(pic, sx, sy, sw, sh, dx, dy, dw, dh);
    text(g, 'CREATE A ROOM', 130, 300, 6, { fill: '#fff', alpha: clamp(lt / 0.3) });
    text(g, 'SHARE THE CODE', 130, 420, 6, { fill: '#fff', alpha: clamp((lt - 0.6) / 0.3) });
    text(g, 'FRIENDS JOIN', 130, 540, 6, { fill: ACCENT, alpha: clamp((lt - 1.2) / 0.3) });
  } else {
    g.drawImage(await shotPic('mp4', 30 + (lt - tp) * 60), 0, 0, W, H);
  }
  caption(g, lt - tp - 0.1, 7.2 + 0.25 - tp - 0.1, 'ONLINE MULTIPLAYER', 'UP TO 4 PLAYERS - ROOM CODES', { y: 800 });
});

// G. and more: quick cuts (high frame rate, hi-res 2D, photo mode, free camera, presets)
const MORE = [
  { name: 'HIGH FRAME RATE', sub: 'SMOOTH 60 FPS MOTION', draw: async (g, lt) => {
    const i = 560 + lt * 60;
    g.drawImage(await shotPic('run29_30', i), 0, 0, W / 2, H, 0, 0, W / 2, H);
    g.drawImage(await shotPic('run29', i), W / 2, 0, W / 2, H, W / 2, 0, W / 2, H);
    g.fillStyle = ACCENT; g.fillRect(W / 2 - 3, 0, 6, H);
    label(g, 'GAME FRAMES', W / 4, 40, 3, { align: 'center', fill: '#fff' });
    label(g, 'HIGH FRAME RATE', 3 * W / 4, 40, 3, { align: 'center', fill: ACCENT });
  } },
  { name: 'HI-RES MENUS AND 2D', sub: 'PAUSE SCREEN, TEXT, HUD', draw: async (g, lt) => {
    const lo = await shotPic('pause_lo', 40), hi = await shotPic('pause_hi', 40);
    // zoom into the middle of the pause screen, the original half (left) against the option (right)
    const z = 1.0 + 0.5 * ease(lt / 1.1), cw = W / z, ch = H / z, cx = (W - cw) / 2, cy = (H - ch) / 2 - 60 * (z - 1);
    g.save(); g.beginPath(); g.rect(0, 0, W / 2, H); g.clip(); g.imageSmoothingEnabled = true; g.drawImage(lo, cx * lo.width / W, cy * lo.height / H, cw * lo.width / W, ch * lo.height / H, 0, 0, W, H); g.restore();
    g.save(); g.beginPath(); g.rect(W / 2, 0, W / 2, H); g.clip(); g.drawImage(hi, cx, cy, cw, ch, 0, 0, W, H); g.restore();
    g.fillStyle = ACCENT; g.fillRect(W / 2 - 3, 0, 6, H);
    label(g, 'ORIGINAL', W / 4, 40, 3, { align: 'center', fill: '#fff' });
    label(g, 'HI-RES 2D', 3 * W / 4, 40, 3, { align: 'center', fill: ACCENT });
  } },
  { name: 'PHOTO MODE', sub: 'FREEZE, FLY, SNAP', draw: async (g, lt) => {
    g.drawImage(await shotPic('photo', 20 + lt * 60), 0, 0, W, H);
    // viewfinder corners
    g.strokeStyle = 'rgba(255,255,255,0.85)'; g.lineWidth = 5;
    for (const [x, y, dx, dy] of [[70, 70, 1, 1], [W - 70, 70, -1, 1], [70, H - 70, 1, -1], [W - 70, H - 70, -1, -1]]) { g.beginPath(); g.moveTo(x, y + dy * 70); g.lineTo(x, y); g.lineTo(x + dx * 70, y); g.stroke(); }
    if (lt > 0.85 && lt < 1.05) { g.fillStyle = `rgba(255,255,255,${0.8 * (1 - (lt - 0.85) / 0.2)})`; g.fillRect(0, 0, W, H); }
  } },
  { name: 'FREE CAMERA', sub: 'RIGHT STICK OR MOUSE', draw: async (g, lt) => { g.drawImage(await shotPic('freecam', 30 + lt * 90), 0, 0, W, H); } },
  { name: 'CLASSIC / MODERN PRESETS', sub: 'EVERY EXTRA IS OPTIONAL', draw: async (g, lt) => {
    const page = await img('/w/pages/options/still_2_running.jpg');   // 1600 x 900
    // from the whole page (1600 x 900 -> 1920 x 1080) towards the Options panel and its preset buttons
    const k = ease(lt / 1.1), zEnd = 1.6, fx = 1400, fy = 330;
    const s2 = 1.2 + (zEnd - 1.2) * k, x0 = (W * 0.6 - fx * zEnd) * k, y0 = (H * 0.42 - fy * zEnd) * k;
    g.fillStyle = '#121418'; g.fillRect(0, 0, W, H);
    g.drawImage(page, x0, y0, 1600 * s2, 900 * s2);
  } },
];
{
  const step = (T.end - T.more) / MORE.length;
  MORE.forEach((m, k) => seg(T.more + k * step, T.more + (k + 1) * step + (k === MORE.length - 1 ? 0.25 : 0.06), 0.06, 0.06, async (g, lt) => {
    await m.draw(g, lt);
    const gr = g.createLinearGradient(0, H - 300, 0, H); gr.addColorStop(0, 'rgba(0,0,0,0)'); gr.addColorStop(1, 'rgba(0,0,0,0.75)');
    g.fillStyle = gr; g.fillRect(0, H - 300, W, 300);
    text(g, 'AND MORE...', 90, H - 230, 4, { fill: '#e9e3d6' });
    text(g, m.name, 90, H - 170, 6.5, { fill: ['#fff7d6', ACCENT, ORANGE] });
    text(g, m.sub, 92, H - 78, 3, { fill: '#f4efe6', alpha: clamp((lt - 0.1) / 0.2) });
  }));
}

// H. end card
seg(T.end, DUR, 0.35, 0, async (g, lt) => {
  g.filter = 'blur(9px) brightness(0.3)';
  g.drawImage(await shotPic('run29', 700 + lt * 40), -40, -22, W + 80, H + 44);
  g.filter = 'none'; vignette(g, 0.75);
  const a = (d) => clamp((lt - d) / 0.4);
  text(g, "CONKER'S", W / 2, 150, 5, { align: 'center', fill: '#fff', alpha: a(0.1) });
  text(g, 'GOOD FUR DAY', W / 2, 225, 8, { align: 'center', fill: ['#fff4c2', ACCENT, ORANGE], alpha: a(0.1), spacing: 1 });
  text(g, 'PLAY NOW IN YOUR BROWSER - NO INSTALL.', W / 2, 440, 4.4, { align: 'center', fill: '#fff', alpha: a(0.5) });
  text(g, 'BRING YOUR OWN ROM.', W / 2, 520, 4.4, { align: 'center', fill: '#fff', alpha: a(0.8) });
  const ua = a(1.2);
  if (ua > 0) {
    const s = 5.6, w = textW('CONKER-WEB-PORT.NETLIFY.APP', s) + 70;
    g.save(); g.globalAlpha = ua; g.fillStyle = 'rgba(242,178,51,0.14)'; g.strokeStyle = ACCENT; g.lineWidth = 3;
    roundRect(g, (W - w) / 2, 640, w, 13 * s + 40, 18); g.fill(); g.stroke(); g.restore();
    text(g, 'CONKER-WEB-PORT.NETLIFY.APP', W / 2, 660, s, { align: 'center', fill: ['#fff4c2', ACCENT], alpha: ua });
  }
  text(g, 'FAN PROJECT. REQUIRES YOUR OWN COPY OF THE GAME.', W / 2, 900, 2.6, { align: 'center', fill: '#bdb6a8', alpha: a(1.7) });
  text(g, 'NOT AFFILIATED WITH OR ENDORSED BY THE RIGHTS HOLDERS.', W / 2, 950, 2.6, { align: 'center', fill: '#bdb6a8', alpha: a(1.7) });
  // fade to black at the very end
  const f = clamp((lt - (DUR - T.end - 0.7)) / 0.7);
  if (f > 0) { g.fillStyle = `rgba(0,0,0,${f})`; g.fillRect(0, 0, W, H); }
});

// ---------------------------------------------------------------- frame rendering
const main = new OffscreenCanvas(W, H), mg = main.getContext('2d');
const layer = new OffscreenCanvas(W, H), lg = layer.getContext('2d');
async function renderFrame(fi) {
  const t = fi / FPS; performanceNow = t;
  mg.globalAlpha = 1; mg.fillStyle = '#000'; mg.fillRect(0, 0, W, H);
  for (const s of SEG) {
    if (t < s.a || t >= s.b) continue;
    const lt = t - s.a, a = (s.fin ? clamp(lt / s.fin) : 1) * (s.fout ? clamp((s.b - t) / s.fout) : 1);
    lg.save(); lg.globalAlpha = 1; lg.filter = 'none'; lg.clearRect(0, 0, W, H); lg.imageSmoothingEnabled = true; lg.imageSmoothingQuality = 'high';
    await s.draw(lg, lt, t);
    lg.restore();
    mg.globalAlpha = a; mg.drawImage(layer, 0, 0); mg.globalAlpha = 1;
  }
  return main;
}

// ---------------------------------------------------------------- audio: one music track + the shots' sound effects
const LAT = 3300;   // game audio frames between a retrace and its sound reaching the speaker (the AI queue, aud_out.c)
async function pcmBuffer(ctx, shot) {
  const m = await meta(shot), raw = new Int16Array(await (await fetch(`/w/shots/${shot}/audio.pcm`)).arrayBuffer());
  const n = raw.length / 2, b = ctx.createBuffer(2, n, m.audio.rate), L = b.getChannelData(0), R = b.getChannelData(1);
  for (let i = 0; i < n; i++) { L[i] = raw[2 * i] / 32768; R[i] = raw[2 * i + 1] / 32768; }
  return { b, m };
}
// seconds into the shot's pcm where the sound of picture `pic` plays
function pcmTime(m, pic) {
  const start = m.start, map = m.audio.map, r = start + pic * 50 / m.fps;
  let s = 0; for (const [f, n] of map) { if (f <= r) s = n; else break; }
  return Math.max(0, (s - LAT) / m.audio.rate);
}
async function buildAudio() {
  const ctx = new OfflineAudioContext(2, Math.ceil(DUR * 48000), 48000);
  const master = ctx.createGain(), comp = ctx.createDynamicsCompressor();
  comp.threshold.value = -20; comp.knee.value = 8; comp.ratio.value = 3; comp.attack.value = 0.01; comp.release.value = 0.2;
  master.connect(comp); comp.connect(ctx.destination);
  // music: the title sequence's music (captured with the sound effects off), from its first note, faded out at the end
  const mus = await pcmBuffer(ctx, 'music');
  { const src = ctx.createBufferSource(), gn = ctx.createGain(); src.buffer = mus.b; src.connect(gn); gn.connect(master);
    gn.gain.setValueAtTime(0.0, 0); gn.gain.linearRampToValueAtTime(1.0, 0.25);
    gn.gain.setValueAtTime(1.0, DUR - 2.6); gn.gain.linearRampToValueAtTime(0.0, DUR - 0.2);
    src.start(0, 0.78); }
  // sound effects of the shots under their segments: [shot, timeline start, duration, first picture, gain]
  const SFX = [['run29', T.wide, T.ledge - T.wide, 300, 0.55], ['ledge13', T.ledge, T.spin - T.ledge, 36, 0.8], ['spin_on', T.spin, T.online - T.spin, 90, 0.6],
    ['photo', T.more + 2 * (T.end - T.more) / 5, 0.0, 0, 0], ['freecam', T.more + 3 * (T.end - T.more) / 5, (T.end - T.more) / 5, 30, 0.5]];
  for (const [shot, t0, dur, pic, gain] of SFX) {
    if (dur <= 0 || gain <= 0) continue;
    const { b, m } = await pcmBuffer(ctx, shot);
    const src = ctx.createBufferSource(), gn = ctx.createGain(); src.buffer = b; src.connect(gn); gn.connect(master);
    gn.gain.setValueAtTime(0, t0); gn.gain.linearRampToValueAtTime(gain, t0 + 0.12);
    gn.gain.setValueAtTime(gain, t0 + dur - 0.2); gn.gain.linearRampToValueAtTime(0, t0 + dur);
    src.start(t0, pcmTime(m, pic), dur);
  }
  // loudness: normalise the peak to -1 dBFS after the gentle compressor
  const out = await ctx.startRendering();
  let pk = 0; for (let c = 0; c < 2; c++) { const d = out.getChannelData(c); for (let i = 0; i < d.length; i++) pk = Math.max(pk, Math.abs(d[i])); }
  const k = pk > 0 ? 0.89 / pk : 1;
  for (let c = 0; c < 2; c++) { const d = out.getChannelData(c); for (let i = 0; i < d.length; i++) d[i] *= k; }
  log(`audio peak ${pk.toFixed(3)} -> gain ${k.toFixed(2)}`);
  return out;
}

// ---------------------------------------------------------------- encode
async function upload(name, data) { const r = await fetch('/upload/' + name, { method: 'POST', body: data }); return r.ok; }
async function preview(list) {
  await loadFont();
  for (const fi of list) {
    const c = await renderFrame(fi);
    await upload(`key_${pad5(fi)}.jpg`, await c.convertToBlob({ type: 'image/jpeg', quality: 0.9 }));
    log(`preview ${fi}`);
  }
  return 'previews ' + list.length;
}
async function encode() {
  await loadFont();
  const t0 = performance.now();
  const audio = await buildAudio();
  log(`audio ${audio.duration.toFixed(2)} s rendered`);
  const muxer = new Mp4Muxer.Muxer({ target: new Mp4Muxer.ArrayBufferTarget(), fastStart: 'in-memory', firstTimestampBehavior: 'offset',
    video: { codec: 'avc', width: W, height: H, frameRate: FPS }, audio: { codec: 'aac', numberOfChannels: 2, sampleRate: 48000 } });
  let verr = null;
  const venc = new VideoEncoder({ output: (c, m) => muxer.addVideoChunk(c, m), error: (e) => { verr = e; } });
  venc.configure({ codec: 'avc1.640032', width: W, height: H, bitrate: 14_000_000, framerate: FPS, latencyMode: 'quality', avc: { format: 'avc' } });
  const aenc = new AudioEncoder({ output: (c, m) => muxer.addAudioChunk(c, m), error: (e) => { verr = e; } });
  aenc.configure({ codec: 'mp4a.40.2', numberOfChannels: 2, sampleRate: 48000, bitrate: 192000 });
  // audio first (small), in 1024-frame planar chunks
  const L = audio.getChannelData(0), R = audio.getChannelData(1), N = audio.length;
  for (let o = 0; o < N; o += 1024) {
    const n = Math.min(1024, N - o), d = new Float32Array(2 * n); d.set(L.subarray(o, o + n), 0); d.set(R.subarray(o, o + n), n);
    const ad = new AudioData({ format: 'f32-planar', sampleRate: 48000, numberOfFrames: n, numberOfChannels: 2, timestamp: Math.round(o / 48000 * 1e6), data: d });
    aenc.encode(ad); ad.close();
  }
  await aenc.flush();
  const keys = [];
  for (let fi = 0; fi < NFR; fi++) {
    const c = await renderFrame(fi);
    // the frame from the pixels (a VideoFrame made straight from the canvas reached the encoder black in headless Chrome)
    const px = mg.getImageData(0, 0, W, H).data;
    const vf = new VideoFrame(px, { format: 'RGBX', codedWidth: W, codedHeight: H, timestamp: Math.round(fi * 1e6 / FPS), duration: Math.round(1e6 / FPS) });
    venc.encode(vf, { keyFrame: fi % 120 === 0 }); vf.close();
    while (venc.encodeQueueSize > 8) await sleep(2);
    if (verr) throw verr;
    if (fi % 60 === 0) log(`frame ${fi}/${NFR} (${((performance.now() - t0) / 1000).toFixed(0)} s)`);
  }
  await venc.flush();
  muxer.finalize();
  const buf = muxer.target.buffer;
  await upload('trailer.mp4', buf);
  return `trailer.mp4 ${(buf.byteLength / 1e6).toFixed(1)} MB, ${NFR} frames, ${((performance.now() - t0) / 1000).toFixed(0)} s`;
}
window.__run = () => (Q.get('preview') ? preview(Q.get('preview').split(',').map(Number)) : encode());
window.__segments = () => T;
