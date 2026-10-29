// P354 trailer compositor + encoder ("Conker's Good Fur Day"). Runs in headless Chrome (render.mjs serves it):
//   /t/compose.html                     encode the whole trailer: H.264 (WebCodecs VideoEncoder) + AAC (AudioEncoder) in
//                                       an MP4 (mp4-muxer), POSTed to /upload/trailer.mp4
//   /t/compose.html?preview=0,120,...   only these frames as JPEGs (/upload/key_NNNNN.jpg), no encoding
// Inputs (all ROM-derived, local only, served from port_work/trailer under /w/): the captured shots (capture.mjs:
// shots/NAME/f*.jpg + audio.pcm + meta.json), the page pictures (pagecap.mjs: pages/NAME/), the online session's
// screenshots (net4.sh: net4/), the game's font (fontdump.mjs: font/font.json).
// P355 edit: (1) the game's own opening monologue (Conker on the throne, its music, his voice) with title cards landing in
// his pauses, "bad" replaced by his "good" from another voice clip, the big title word by word on "good fur day"; (2) the
// features cut on the beat of a livelier track (a captured game track by default, or ?music=FILE). Titles: smooth
// upscaled game font (?pixelfont=1: the old pixels). ?audio=speech|1 renders only the soundtrack (render.mjs audio).
// Titles use the game's own font: the glyph bitmaps the game decoded from the ROM (font 0, the text_draw_string font),
// upscaled with nearest-neighbour pixels and drawn white / tinted with a dark outline like the game's on-screen text.
'use strict';
const W = 1920, H = 1080, FPS = 60;
const Q = new URLSearchParams(location.search);
// P355 edit: part 1 = the game's opening monologue (shot 'intro', start retrace 8240), part 2 = the features cut on the beat
// of the features music. Times measured from the captures (musicstat.mjs, the speech envelope of 'intro_speech'):
//   speech pcm second p plays at timeline p - 1.05 (pcmTime of picture 0); "a" 39.0, "bad" 39.53 - 40.07, "fur" 40.63,
//   "day" 41.03 - 41.43; the game's own "Bad Fur Day" logo fades in from retrace ~10225 (timeline 39.7): part 1 freezes on
//   picture FREEZE before it.
const BEAT = 0.6182;                 // features music: 97.06 BPM (music_0c, musicstat.mjs --beats)
const TF = 42.6;                     // the cut to the features, on a downbeat of the features music
const FREEZE = 2370;                 // last 'intro' picture used (retrace 10215)
const T = { browser: TF, wide: TF + 8 * BEAT, ledge: TF + 16 * BEAT, spin: TF + 23 * BEAT, online: TF + 30 * BEAT,
  more: TF + 38 * BEAT, end: TF + 46 * BEAT };
const DUR = +(TF + 54 * BEAT + 0.4).toFixed(2), NFR = Math.round(DUR * FPS);
// the features music: a captured game track (default) or an open-licensed file (?music=FILE under port_work/trailer/music/,
// &credit=TEXT for the end card). MUSIC_DOWNBEAT: the pcm second of a downbeat, placed on TF.
const MUSIC = Q.get('music') || '', MUSIC_CREDIT = Q.get('credit') || '';
const MUSIC_DOWNBEAT = +(Q.get('downbeat') || (MUSIC ? 0 : 4.155 + 2 * 4 * BEAT));
const OUT = Q.get('out') || 'trailer.mp4';   // ?br=BITS&out=NAME.mp4: a smaller copy
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
// P355 smooth titles (user request): each glyph's 16-level alpha is treated as a sampled shape, upscaled UP times with
// a Catmull-Rom (bicubic) filter and thresholded with a narrow smoothstep around 0.45, so the letters keep the game
// font's shapes but get clean, anti-aliased curves instead of big square pixels (a distance-field style render).
// ?pixelfont=1 draws the old way (nearest-neighbour font pixels), for before / after comparisons.
const PIXELFONT = Q.get('pixelfont') === '1', UP = PIXELFONT ? 1 : 8;
const smoothCv = {};
function cubic(p0, p1, p2, p3, t) { return p1 + 0.5 * t * (p2 - p0 + t * (2 * p0 - 5 * p1 + 4 * p2 - p3 + t * (3 * (p1 - p2) + p3 - p0))); }
function smoothGlyph(k) {
  if (smoothCv[k]) return smoothCv[k];
  const gl = FONT.glyphs[k], B = 1, W0 = gl.w + 2 * B, H0 = gl.h + 2 * B;
  const a = (x, y) => { x -= B; y -= B; return x < 0 || y < 0 || x >= gl.w || y >= gl.h ? 0 : gl.px[y * gl.w + x] / 255; };
  const cw = W0 * UP, ch = H0 * UP, c = new OffscreenCanvas(cw, ch), g = c.getContext('2d'), id = g.createImageData(cw, ch);
  const T0 = 0.45, E = 0.09;
  for (let oy = 0; oy < ch; oy++) {
    const sy = (oy + 0.5) / UP - 0.5, y = Math.floor(sy), ty = sy - y;
    for (let ox = 0; ox < cw; ox++) {
      const sx = (ox + 0.5) / UP - 0.5, x = Math.floor(sx), tx = sx - x;
      const r = [];
      for (let j = -1; j <= 2; j++) r.push(cubic(a(x - 1, y + j), a(x, y + j), a(x + 1, y + j), a(x + 2, y + j), tx));
      const v = cubic(r[0], r[1], r[2], r[3], ty), q = clamp((v - (T0 - E)) / (2 * E)), al = q * q * (3 - 2 * q);
      const o = 4 * (oy * cw + ox); id.data[o] = id.data[o + 1] = id.data[o + 2] = 255; id.data[o + 3] = Math.round(255 * al);
    }
  }
  g.putImageData(id, 0, 0);
  return (smoothCv[k] = { c, B });
}
// the string at UP times the font's pixel size: { canvas (outline + fill), w, h (in font pixels), P, k = UP }; letter
// spacing as the game (x += x offset before, x += width - 1 after), line height 12
const textCache = new Map();
function textBitmap(str, fill, outline = 'rgba(10,8,6,0.92)', spacing = 0) {
  const key = str + '|' + fill + '|' + outline + '|' + spacing;
  if (textCache.has(key)) return textCache.get(key);
  let w = 0;
  for (const ch of str) { const k = glyphOf(ch), gl = FONT.glyphs[k]; w += gl ? gl.xo + gl.w - 1 + spacing : 5 + spacing; }
  const P = 2, cw = w + 2 * P + 2, ch = 13 + 2 * P, U = UP;
  const mask = new OffscreenCanvas(cw * U, ch * U), m = mask.getContext('2d');
  let x = P;
  for (const c of str) {
    const k = glyphOf(c), gl = FONT.glyphs[k];
    if (!gl) { x += 5 + spacing; continue; }
    if (PIXELFONT) m.drawImage(glyphCv[k], x + gl.xo, P + gl.yo);
    else { const sg = smoothGlyph(k); m.drawImage(sg.c, (x + gl.xo - sg.B) * U, (P + gl.yo - sg.B) * U); }
    x += gl.xo + gl.w - 1 + spacing;
  }
  const out = new OffscreenCanvas(cw * U, ch * U), o = out.getContext('2d');
  if (outline) {   // ~1 font pixel of dark outline around the letters (the game's text has a dark rim), a bit more below
    const sh = new OffscreenCanvas(cw * U, ch * U), s = sh.getContext('2d');
    s.drawImage(mask, 0, 0); s.globalCompositeOperation = 'source-in'; s.fillStyle = outline; s.fillRect(0, 0, cw * U, ch * U);
    const offs = PIXELFONT ? [[-1, 0], [1, 0], [0, -1], [0, 1], [-1, -1], [1, -1], [-1, 1], [1, 1], [0, 2], [1, 2]] : [];
    if (!PIXELFONT) {
      for (let i = 0; i < 20; i++) { const an = i * Math.PI / 10; offs.push([1.1 * Math.cos(an), 1.1 * Math.sin(an)]); }
      for (const [dx, dy] of [[0, 1.8], [0.5, 1.9], [-0.4, 1.7], [0.8, 1.5]]) offs.push([dx, dy]);
    }
    for (const [dx, dy] of offs) o.drawImage(sh, dx * U, dy * U);
  }
  const fl = new OffscreenCanvas(cw * U, ch * U), f = fl.getContext('2d');
  f.drawImage(mask, 0, 0); f.globalCompositeOperation = 'source-in';
  if (Array.isArray(fill)) { const gr = f.createLinearGradient(0, P * U, 0, (P + 11) * U); fill.forEach((c, i) => gr.addColorStop(i / (fill.length - 1), c)); f.fillStyle = gr; }
  else f.fillStyle = fill;
  f.fillRect(0, 0, cw * U, ch * U);
  o.drawImage(fl, 0, 0);
  const r = { canvas: out, w: cw, h: ch, P, k: U };
  textCache.set(key, r);
  return r;
}
// draw text with the font scaled s times, anchored at (x, y) = top of the cap height
function text(g, str, x, y, s, { fill = '#fff', outline, align = 'left', alpha = 1, spacing = 0, shadow = true } = {}) {
  const t = textBitmap(str, fill, outline, spacing);
  const w = t.w * s, h = t.h * s;
  const dx = align === 'center' ? x - w / 2 : align === 'right' ? x - w : x;
  g.save(); g.globalAlpha *= alpha;
  g.imageSmoothingEnabled = !PIXELFONT; g.imageSmoothingQuality = 'high';
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

// A. the opening monologue (Conker on the throne), with title cards landing in the pauses of his speech:
//   7.3 after "Well... there I am."                          FAN MADE PORT
//   13.0 after "King of all the land."                      PLAY ANYWHERE
//   17.8 after "...I hear you say."                         + ON ANYTHING WITH A BROWSER
//   22.6 after "...that surround my throne?"                NOT AFFILIATED
//   39.60 "a GOOD" / 40.63 "FUR" / 41.03 "DAY"               CONKER'S GOOD FUR DAY, word by word on his words
const CARDS = [
  { at: 7.3, out: 12.6, lines: ['FAN MADE PORT'] },
  { at: 13.0, out: 22.3, lines: ['PLAY ANYWHERE', 'ON ANYTHING WITH A BROWSER'], at2: 17.8 },
  { at: 22.6, out: 28.2, lines: ['NOT AFFILIATED'] },
];
const W_GOOD = 39.6, W_FUR = 40.63, W_DAY = 41.03;
function card(g, t, c) {
  if (t < c.at - 0.05 || t > c.out + 0.5) return;
  const a = clamp((t - c.at) / 0.3) * clamp((c.out + 0.45 - t) / 0.45), y = 820;
  // a soft dark band under the words, the cutscene stays visible above
  const gr = g.createLinearGradient(0, y - 140, 0, H);
  gr.addColorStop(0, 'rgba(0,0,0,0)'); gr.addColorStop(0.5, `rgba(0,0,0,${0.5 * a})`); gr.addColorStop(1, `rgba(0,0,0,${0.62 * a})`);
  g.fillStyle = gr; g.fillRect(0, y - 140, W, H - y + 140);
  const pop = 1 + 0.12 * (1 - easeOut((t - c.at) / 0.35));
  text(g, c.lines[0], W / 2, y, 7.2 * pop, { align: 'center', fill: ['#fff7d6', ACCENT, ORANGE], alpha: a, spacing: 1 });
  if (c.lines[1]) {
    const b = clamp((t - c.at2) / 0.3) * a, pop2 = 1 + 0.12 * (1 - easeOut((t - c.at2) / 0.35));
    text(g, c.lines[1], W / 2, y + 120, 4.4 * pop2, { align: 'center', fill: '#fff', alpha: b });
  }
}
seg(0, TF, 1.0, 0, async (g, lt) => {
  const pic = Math.min(FREEZE, lt * 60), frozen = Math.max(0, lt - FREEZE / 60);
  if (frozen > 0) {   // the frozen frame slowly pushes in and darkens under the big title
    const z = 1 + 0.05 * ease(frozen / 3), d = ease((lt - W_GOOD) / 0.6);
    g.filter = `blur(${(4 * d).toFixed(2)}px) brightness(${(1 - 0.5 * d).toFixed(3)})`;
    g.drawImage(await shotPic('intro', FREEZE), W / 2 - W * z / 2, H / 2 - H * z / 2, W * z, H * z);
    g.filter = 'none';
  } else g.drawImage(await shotPic('intro', pic), 0, 0, W, H);
  vignette(g, 0.45);
  for (const c of CARDS) card(g, lt, c);
  if (lt >= W_GOOD - 0.02) {   // the big title on his words
    const word = (t0) => clamp((lt - t0) / 0.12), pop = (t0) => 1 + 0.18 * (1 - easeOut((lt - t0) / 0.3));
    const s = 10.5, y = 470, f = ['#fff4c2', ACCENT, ORANGE];
    const inner = (w) => textW(w, s, 1) - 6 * s, sp = 7 * s;   // a word's ink width (textW includes 2 x 3 font px of margin)
    const wG = inner('GOOD') + sp, wF = inner('FUR') + sp, wD = inner('DAY'), x0 = W / 2 - (wG + wF + wD) / 2;
    text(g, "CONKER'S", W / 2, 330, 6.2 * pop(W_GOOD), { align: 'center', fill: '#fff', alpha: word(W_GOOD) });
    const big = (str, x, t0, w) => text(g, str, x + w / 2, y + 6.5 * s * (1 - pop(t0)), s * pop(t0), { align: 'center', fill: f, alpha: word(t0), spacing: 1 });
    big('GOOD', x0, W_GOOD, wG - sp);
    big('FUR', x0 + wG, W_FUR, wF - sp);
    big('DAY', x0 + wG + wF, W_DAY, wD);
    text(g, 'A FAN-MADE BROWSER PORT', W / 2, 700, 3.8, { align: 'center', fill: '#e9e3d6', alpha: clamp((lt - W_DAY - 0.5) / 0.4) });
  }
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
seg(T.browser, T.wide + 0.1, 0.06, 0.1, async (g, lt) => {
  const bg = g.createRadialGradient(W / 2, H * 0.55, 100, W / 2, H * 0.55, 1100); bg.addColorStop(0, '#2b2517'); bg.addColorStop(1, '#0b0b0d');
  g.fillStyle = bg; g.fillRect(0, 0, W, H);
  const tDrop = 1.55, tRom = 1.95, dur = T.wide - T.browser;
  let page;
  if (lt < tDrop) page = await img('/w/pages/site/still_0_drop.jpg');
  else if (lt < tRom) page = await img('/w/pages/site/still_1_rom.jpg');
  else page = await img(`/w/pages/site/f${pad5(Math.min(299, Math.round((lt - tRom) * 60)))}.jpg`);
  const ww = 1360, wx = (W - ww) / 2, wy = 150;
  const r = browserWindow(g, page, wx, wy, ww, Math.floor(lt * 30));
  // the ROM file dragged onto the page's drop zone, then the cursor clicks Start
  const cx = r.x + 640 * r.k, cy = r.y + 330 * r.k;
  if (lt < tDrop + 0.1) {
    const p = easeOut((lt - 0.45) / 0.85), fx = 1700 - p * (1700 - (cx - 115)), fy = 1060 - p * (1060 - (cy - 27));
    if (p > 0.97) { g.strokeStyle = ACCENT; g.lineWidth = 4; g.setLineDash([14, 10]); roundRect(g, r.x + 18 * r.k, r.y + 18 * r.k, 1228 * r.k, 544 * r.k, 10); g.stroke(); g.setLineDash([]); }
    fileChip(g, fx, fy, clamp((lt - 0.35) / 0.2) * clamp((tDrop + 0.1 - lt) / 0.15));
    cursor(g, fx + 150, fy + 34, 1.4);
  } else if (lt < tRom + 0.25) {
    const sx = r.x + 150 * r.k, sy = r.y + 26 * r.k, p = easeOut((lt - tDrop) / 0.45);
    cursor(g, cx + (sx - cx) * p, cy + (sy - cy) * p, 1.4);
  }
  caption(g, lt, dur + 0.1, 'PLAYS IN YOUR BROWSER', null, { x: 70, y: 40, s: 6 });
  urlPill(g, 1150, 42, Math.floor((lt - 0.15) * 30), clamp((lt - 0.1) / 0.25) * clamp((2.0 - lt) / 0.3));
  const b = clamp((lt - tRom) / 0.3) * clamp((dur + 0.1 - lt) / 0.25);
  if (b > 0) { text(g, 'NO INSTALL', 1240, 58, 5.4, { fill: ['#fff7d6', ACCENT], alpha: b }); }
  if (b > 0) text(g, 'JUST BRING YOUR OWN ROM', W / 2, 1022, 3.4, { align: 'center', fill: '#fff', alpha: b });
});

// C. widescreen: the original 4:3 picture (640 x 480, every option off), then the same moment in 16:9, full resolution
seg(T.wide, T.ledge + 0.1, 0.06, 0.1, async (g, lt) => {
  const i = 300 + lt * 60, tw = 4 * BEAT, tr = 0.6, dur = T.ledge - T.wide;
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
  caption(g, lt - tw - 0.15, dur + 0.1 - tw - 0.15, 'WIDESCREEN', 'FULL RESOLUTION - SHARP HI-RES 2D');
});

// D. ledge grab (level 0x13 crates): jump, catch the edge, hang, pull up
seg(T.ledge, T.spin + 0.1, 0.06, 0.1, async (g, lt) => {
  g.drawImage(await shotPic('ledge13', 66 + lt * 60), 0, 0, W, H);
  vignette(g, 0.35);
  caption(g, lt - 0.15, T.spin - T.ledge - 0.15 + 0.1, 'LEDGE GRAB', 'CATCH THE EDGE - PULL YOURSELF UP');
});

// E. longer tail spin: the same jump with the option off (left) and on (right)
seg(T.spin, T.online + 0.1, 0.06, 0.1, async (g, lt) => {
  g.fillStyle = '#0c0c0f'; g.fillRect(0, 0, W, H);
  const i = 110 + lt * 60, w = 940, h = w * 9 / 16, y = 250;
  const zc = 1.3, cw = W / zc, chh = H / zc, cx = (W - cw) / 2, cy = (H - chh) / 2 + 40;   // a little closer to Conker
  g.drawImage(await shotPic('spin_off', i), cx, cy, cw, chh, 13, y, w, h);
  g.drawImage(await shotPic('spin_on', i), cx, cy, cw, chh, W - 13 - w, y, w, h);
  text(g, 'ORIGINAL', 13 + w / 2, y - 64, 4, { align: 'center', fill: '#e9e3d6' });
  text(g, 'WITH THE OPTION', W - 13 - w / 2, y - 64, 4, { align: 'center', fill: ACCENT });
  caption(g, lt - 0.1, T.online - T.spin + 0.1 - 0.1, 'LONGER TAIL SPIN', 'HOVER TWICE AS LONG', { y: 878 });
});

// F. online: the 4-player split screen of a real online session (Bunker)
seg(T.online, T.more + 0.1, 0.06, 0.1, async (g, lt) => {
  g.drawImage(await shotPic('mp4', 30 + lt * 60), 0, 0, W, H);
  caption(g, lt - 0.1, T.more - T.online + 0.1 - 0.1, 'ONLINE MULTIPLAYER', 'UP TO 4 PLAYERS - ROOM CODES', { y: 800 });
});

// G. and more: a list of the other options over a dimmed, blurred run, the lines coming in one by one
const MORE = [
  'HIGH FRAME RATE', 'HI-RES MENUS AND 2D', 'PHOTO MODE', 'FREE CAMERA', 'CLASSIC / MODERN PRESETS',
  'SKIP CUTSCENES', 'HEALTH AND CASH ALWAYS ON', 'AIR METER', 'SEPARATE VOLUMES', 'GAMEPAD RUMBLE',
  'TOUCH CONTROLS', 'SAVE IMPORT / EXPORT',
];
seg(T.more, T.end + 0.1, 0.06, 0.1, async (g, lt) => {
  g.filter = 'blur(9px) brightness(0.32) saturate(1.1)';
  g.drawImage(await shotPic('run29', 400 + lt * 40), -40, -22, W + 80, H + 44);
  g.filter = 'none'; vignette(g, 0.7);
  const a = clamp(lt / 0.3);
  text(g, 'AND MORE...', W / 2, 120, 7.5, { align: 'center', fill: ['#fff7d6', ACCENT, ORANGE], alpha: a });
  const rows = MORE.length / 2, x = [210, 1010], y0 = 330, dy = 100, step = BEAT / 4;
  MORE.forEach((m, k) => {
    const col = Math.floor(k / rows), row = k % rows, t = lt - 0.35 - (row * 2 + col) * step, ak = clamp(t / 0.25);
    if (ak <= 0) return;
    const sx = (1 - easeOut(t / 0.35)) * -40, y = y0 + row * dy;
    g.fillStyle = ACCENT; g.globalAlpha = ak; g.fillRect(x[col] + sx, y + 10, 18, 18); g.globalAlpha = 1;
    text(g, m, x[col] + 44 + sx, y, 3.6, { fill: '#f4efe6', alpha: ak });
  });
  text(g, 'ALL OPTIONAL - TURN ON WHAT YOU LIKE', W / 2, 960, 3, { align: 'center', fill: ACCENT, alpha: clamp((lt - 6 * BEAT) / 0.3) });
});

// H. end card
seg(T.end, DUR, 0.06, 0, async (g, lt) => {
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
  if (MUSIC_CREDIT) text(g, 'MUSIC: ' + MUSIC_CREDIT, W / 2, 1000, 2.6, { align: 'center', fill: '#bdb6a8', alpha: a(1.9) });
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
// P355: Conker's "bad" -> "good". The speech is captured alone ('intro_speech': music and effects off; 'intro' has the
// music and effects without speech; their sum equals the full mix 'intro_full' to -43 dB). In the speech track the word
// "bad" (pcm 40.55 - 41.66, up to "fur") is muted, and Conker's "good" from his line "Oh my giddy aunt. This is not good."
// is laid in: an MP3 voice clip in the ROM (the game's voice clips are plain MPEG-2 layer III, 22050 Hz mono), decoded by
// Chrome, its last word cut out by its envelope, pitched down a little (playback rate GOOD_RATE: 230 -> ~200 Hz, the
// stressed pitch of the line's own words is 128 - 147 Hz), level-matched per channel to the captured "bad", with a short
// synthetic room tail like the recording's own ring (~-22 dB, 0.6 s).
const GOOD_CLIP = { offset: 0x1723cfd, length: 13839 };   // "Oh my giddy aunt. This is not good." (clip 100 of the ROM scan)
const GOOD_RATE = +(Q.get("goodrate") || 0.88), GOOD_GAIN = +(Q.get("goodgain") || 1.15), GOOD_DELAY = +(Q.get("gooddelay") || 0.05), BAD_PCM = [40.55, 41.66], GOOD_PCM = 40.582;
function bufRms(b, ch, t0, t1, voicedOnly) {
  const d = b.getChannelData(ch), r = b.sampleRate, hop = Math.round(r / 100), fr = [];
  for (let i = Math.round(t0 * r); i + hop <= Math.min(d.length, Math.round(t1 * r)); i += hop) { let e = 0; for (let k = i; k < i + hop; k++) e += d[k] * d[k]; fr.push(e / hop); }
  const mx = Math.max(...fr), use = voicedOnly ? fr.filter((v) => v > 0.1 * mx) : fr;
  return Math.sqrt(use.reduce((a, v) => a + v, 0) / use.length);
}
// the clip's MPEG frames only: the voice data has a few bytes between runs of frames, where Chrome's decoder would stop
function mp3Frames(u) {
  const BR = [0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160], SR = [22050, 24000, 16000];
  const len = (i) => {   // MPEG-2 layer III frame length at i, or 0
    if (u[i] !== 0xFF || (u[i + 1] & 0xFE) !== 0xF2) return 0;
    const bi = u[i + 2] >> 4, si = (u[i + 2] >> 2) & 3;
    return bi && bi < 15 && si < 3 ? Math.floor(72 * BR[bi] * 1000 / SR[si]) + ((u[i + 2] >> 1) & 1) : 0;
  };
  const parts = []; let i = 0, skipped = 0, n = 0;
  while (i < u.length - 4) {
    const L = len(i);
    if (L && i + L <= u.length) { parts.push(u.subarray(i, i + L)); i += L; n++; } else { i++; skipped++; }
  }
  if (!n) throw new Error('no MP3 frames in the good clip');
  const out = new Uint8Array(parts.reduce((a, p) => a + p.length, 0)); let o = 0; for (const p of parts) { out.set(p, o); o += p.length; }
  log(`good clip: ${n} frames, ${skipped} bytes between them skipped`);
  return out.buffer;
}
async function goodWord(ctx) {
  const rom = await (await fetch('/rom.z64')).arrayBuffer();
  const mp3 = rom.slice(GOOD_CLIP.offset, GOOD_CLIP.offset + GOOD_CLIP.length);
  const b = await ctx.decodeAudioData(mp3Frames(new Uint8Array(mp3))), d = b.getChannelData(0), r = b.sampleRate, hop = Math.round(r / 100);
  const env = []; for (let i = 0; i + hop <= d.length; i += hop) { let e = 0; for (let k = i; k < i + hop; k++) e += d[k] * d[k]; env.push(Math.sqrt(e / hop)); }
  const mx = Math.max(...env), th = 0.06 * mx;
  let end = env.length - 1; while (end > 0 && env[end] < th) end--;
  let st = end; while (st > 0 && !(env[st] < th && env[st - 1] < th && env[st - 2] < th)) st--;   // back to a 30 ms gap
  const t0 = Math.max(0, st / 100 - 0.01), t1 = Math.min(b.duration, (end + 1) / 100 + 0.04);
  log(`good: clip ${b.duration.toFixed(2)} s, word ${t0.toFixed(3)} - ${t1.toFixed(3)} s`);
  const n = Math.round((t1 - t0) * r), out = ctx.createBuffer(1, n, r), o = out.getChannelData(0), f = Math.round(0.006 * r);
  for (let i = 0; i < n; i++) o[i] = d[Math.round(t0 * r) + i] * Math.min(1, i / f, (n - 1 - i) / f);
  return out;
}
function roomIR(ctx, secs = 0.6) {   // decaying noise, -60 dB at `secs`, a little darker as it decays
  const r = ctx.sampleRate, n = Math.round(secs * r), b = ctx.createBuffer(2, n, r);
  for (let c = 0; c < 2; c++) { const d = b.getChannelData(c); let lp = 0; let seed = 12345 + c;
    for (let i = 0; i < n; i++) { seed = (seed * 1103515245 + 12345) & 0x7fffffff; const x = seed / 0x3fffffff - 1; lp += (x - lp) * (0.5 - 0.35 * i / n); d[i] = lp * Math.pow(10, -3 * i / n); } }
  return b;
}
// the edited speech into `dest`, timeline start t0 (seconds), returns { gainL, gainR } for the log
async function speechInto(ctx, dest, t0) {
  const { b, m } = await pcmBuffer(ctx, 'intro_speech');
  const r = b.sampleRate, gL = bufRms(b, 0, GOOD_PCM, GOOD_PCM + 0.5, true), gR = bufRms(b, 1, GOOD_PCM, GOOD_PCM + 0.5, true);
  for (let c = 0; c < 2; c++) {   // mute "bad" and its ring, 15 ms ramps
    const d = b.getChannelData(c), a = Math.round(BAD_PCM[0] * r), z = Math.round(BAD_PCM[1] * r), f = Math.round(0.015 * r);
    for (let i = a - f; i < z + f; i++) d[i] *= i < a ? (a - i) / f : i >= z ? (i - z) / f : 0;
  }
  const src = ctx.createBufferSource(); src.buffer = b; src.connect(dest); src.start(t0, pcmTime(m, 0));
  const good = await goodWord(ctx), gw = bufRms(good, 0, 0, good.duration, true);
  const st = ctx.createBuffer(2, good.length, good.sampleRate);
  st.getChannelData(0).set(good.getChannelData(0).map((v) => v * GOOD_GAIN * gL / gw)); st.getChannelData(1).set(good.getChannelData(0).map((v) => v * GOOD_GAIN * gR / gw));
  const gs = ctx.createBufferSource(); gs.buffer = st; gs.playbackRate.value = GOOD_RATE;
  const conv = ctx.createConvolver(); conv.normalize = true; conv.buffer = roomIR(ctx);
  const wet = ctx.createGain(); wet.gain.value = +(Q.get("goodwet") || 0.6);
  gs.connect(dest); gs.connect(conv); conv.connect(wet); wet.connect(dest);
  const at = t0 + GOOD_PCM - pcmTime(m, 0) + GOOD_DELAY;
  gs.start(at);
  log(`speech: "bad" muted pcm ${BAD_PCM.join('-')}, "good" at timeline ${at.toFixed(3)} (rate ${GOOD_RATE}), gain L ${(gL / gw).toFixed(3)} R ${(gR / gw).toFixed(3)}`);
}
async function musicBuffer(ctx) {
  if (!MUSIC) return (await pcmBuffer(ctx, 'music_0c')).b;
  return ctx.decodeAudioData(await (await fetch('/w/music/' + MUSIC)).arrayBuffer());
}
async function buildAudio(only) {
  const ctx = new OfflineAudioContext(2, Math.ceil(DUR * 48000), 48000);
  const master = ctx.createGain(), comp = ctx.createDynamicsCompressor();
  comp.threshold.value = -20; comp.knee.value = 8; comp.ratio.value = 3; comp.attack.value = 0.01; comp.release.value = 0.2;
  master.connect(comp); comp.connect(ctx.destination);
  if (only === 'speech') { await speechInto(ctx, master, 0); }
  else {
    // part 1: the cutscene's music and effects + the edited speech, out at the cut
    const intro = await pcmBuffer(ctx, 'intro');
    const bus = ctx.createGain(); bus.connect(master);
    bus.gain.setValueAtTime(0, 0); bus.gain.linearRampToValueAtTime(1, 0.6);
    bus.gain.setValueAtTime(1, TF - 0.5); bus.gain.linearRampToValueAtTime(0, TF + 0.05);
    { const src = ctx.createBufferSource(); src.buffer = intro.b; src.connect(bus); src.start(0, pcmTime(intro.m, 0)); }
    await speechInto(ctx, bus, 0);
    // part 2: the features music, a downbeat on the cut; two beats of lead-in rising under the title
    const mb = await musicBuffer(ctx), mg = ctx.createGain(); mg.connect(master);
    const lead = 2 * BEAT, MV = MUSIC ? 0.9 : 1.0;
    mg.gain.setValueAtTime(0, TF - lead); mg.gain.linearRampToValueAtTime(0.45 * MV, TF - 0.05); mg.gain.linearRampToValueAtTime(MV, TF + 0.02);
    mg.gain.setValueAtTime(MV, DUR - 2.2); mg.gain.linearRampToValueAtTime(0, DUR - 0.1);
    { const src = ctx.createBufferSource(); src.buffer = mb; src.connect(mg); src.start(TF - lead, Math.max(0, MUSIC_DOWNBEAT - lead)); }
    // sound effects of the shots under their segments: [shot, timeline start, duration, first picture, gain]
    const SFX = [['run29', T.wide, T.ledge - T.wide, 300, 0.45], ['ledge13', T.ledge, T.spin - T.ledge, 66, 0.7], ['spin_on', T.spin, T.online - T.spin, 110, 0.5]];
    for (const [shot, t0, dur, pic, gain] of SFX) {
      const { b, m } = await pcmBuffer(ctx, shot);
      const src = ctx.createBufferSource(), gn = ctx.createGain(); src.buffer = b; src.connect(gn); gn.connect(master);
      gn.gain.setValueAtTime(0, t0); gn.gain.linearRampToValueAtTime(gain, t0 + 0.05);
      gn.gain.setValueAtTime(gain, t0 + dur - 0.1); gn.gain.linearRampToValueAtTime(0, t0 + dur);
      src.start(t0, pcmTime(m, pic), dur);
    }
  }
  // loudness: normalise the peak to -1 dBFS after the gentle compressor
  const out = await ctx.startRendering();
  let pk = 0; for (let c = 0; c < 2; c++) { const d = out.getChannelData(c); for (let i = 0; i < d.length; i++) pk = Math.max(pk, Math.abs(d[i])); }
  const k = pk > 0 ? 0.89 / pk : 1;
  for (let c = 0; c < 2; c++) { const d = out.getChannelData(c); for (let i = 0; i < d.length; i++) d[i] *= k; }
  log(`audio peak ${pk.toFixed(3)} -> gain ${k.toFixed(2)}`);
  return out;
}
// ?audio=1: only the soundtrack as a WAV (/upload/audio.wav), ?audio=speech: only the edited speech (for checking the splice)
function wav(b, from = 0, to = b.duration) {
  const r = b.sampleRate, i0 = Math.round(from * r), n = Math.round(to * r) - i0, out = new DataView(new ArrayBuffer(44 + 4 * n));
  const w4 = (o, s) => { for (let i = 0; i < 4; i++) out.setUint8(o + i, s.charCodeAt(i)); };
  w4(0, 'RIFF'); out.setUint32(4, 36 + 4 * n, true); w4(8, 'WAVE'); w4(12, 'fmt '); out.setUint32(16, 16, true); out.setUint16(20, 1, true); out.setUint16(22, 2, true);
  out.setUint32(24, r, true); out.setUint32(28, 4 * r, true); out.setUint16(32, 4, true); out.setUint16(34, 16, true); w4(36, 'data'); out.setUint32(40, 4 * n, true);
  const L = b.getChannelData(0), R = b.getChannelData(1);
  for (let i = 0; i < n; i++) { out.setInt16(44 + 4 * i, Math.max(-32768, Math.min(32767, L[i0 + i] * 32767)), true); out.setInt16(46 + 4 * i, Math.max(-32768, Math.min(32767, R[i0 + i] * 32767)), true); }
  return out.buffer;
}
async function audioOnly(kind) {
  const b = await buildAudio(kind === 'speech' ? 'speech' : undefined);
  await upload(kind === 'speech' ? 'speech.wav' : 'audio.wav', wav(b));
  return `audio ${kind} ${b.duration.toFixed(2)} s`;
}

// ---------------------------------------------------------------- encode
async function upload(name, data) { const r = await fetch('/upload/' + name, { method: 'POST', body: data }); return r.ok; }
async function preview(list) {
  await loadFont();
  for (const fi of list) {
    const c = await renderFrame(fi);
    // ?tag=NAME: key_NAME_NNNNN.jpg; ?crop=X,Y,W,H: only that part, at 1:1 (before / after comparisons)
    const tag = Q.get('tag') ? Q.get('tag') + '_' : '', cr = Q.get('crop') ? Q.get('crop').split(',').map(Number) : null;
    let pic = c;
    if (cr) { pic = new OffscreenCanvas(cr[2], cr[3]); pic.getContext('2d').drawImage(c, cr[0], cr[1], cr[2], cr[3], 0, 0, cr[2], cr[3]); }
    await upload(`key_${tag}${pad5(fi)}.jpg`, await pic.convertToBlob({ type: 'image/jpeg', quality: 0.92 }));
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
  venc.configure({ codec: 'avc1.640032', width: W, height: H, bitrate: Number(Q.get('br') || 14_000_000), framerate: FPS, latencyMode: 'quality', avc: { format: 'avc' } });
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
  await upload(OUT, buf);
  return `${OUT} ${(buf.byteLength / 1e6).toFixed(1)} MB, ${NFR} frames, ${((performance.now() - t0) / 1000).toFixed(0)} s`;
}
window.__run = () => (Q.get('audio') ? audioOnly(Q.get('audio')) : Q.get('preview') ? preview(Q.get('preview').split(',').map(Number)) : encode());
window.__segments = () => T;
