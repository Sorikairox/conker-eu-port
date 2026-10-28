// P354 trailer: the game's own text font, read from game memory at run time (decoded by the game from the user's ROM:
// glyph_set_load_rom -> glyph_rle_to_texture, game_eu_430D0.c), for the trailer's titles.
//   node tools/port/trailer/fontdump.mjs [OUT.json]      (default port_work/trailer/font/font.json; ROM-derived, never commit)
// Font 0 = what text_draw_string (game_eu_6EDC0.c) draws: g_font_textures[0] (was D_80085D20; 0xE0 bytes per glyph, I8,
// rows of (w + 7) & ~7 bytes, odd rows stored with the TMEM swap x ^ 4) and g_font_metrics[0] (was D_80085D24; 4 bytes per
// glyph: width + 1, height + 1, x offset, y offset). Characters map to glyphs through text_char_to_glyph: lower case ->
// upper case, ' ' = 0x60, else the index of the character in g_text_glyph_chars (0x80085CC0, 0x60 bytes).
// Game memory is "virtual big-endian" (port/ultra/pc_mem.h): a byte at N64 offset o is at host n64_rdram + (o ^ 3);
// pointers are native wasm addresses.
import fs from 'node:fs';
import path from 'node:path';
import { launch, serve, sleep } from './cdp.mjs';

const ROOT = path.resolve(path.dirname(new URL(import.meta.url).pathname), '../../..');
process.chdir(ROOT);
const out = process.argv[2] || 'port_work/trailer/font/font.json';
fs.mkdirSync(path.dirname(out), { recursive: true });
const port = 8640 + (process.pid % 10);
const srv = await serve({ '/app/': 'port/build/web', '/dev/rom.z64': 'baserom.eu.z64' }, port);
const b = await launch(`http://127.0.0.1:${port}/app/index.html?app=game&det=1&p103boot=1&mute=1&romurl=../dev/rom.z64&opt=skipintro:1`,
  { init: fs.readFileSync('tools/port/trailer/shim.js', 'utf8'), log: path.join(path.dirname(out), 'chrome.log') });
try {
  for (let i = 0; i < 200; i++) { if ((await b.ev('__trailer.q.length && __trailer.frame() >= 0 ? 1 : 0')) === 1) break; await sleep(250); }
  while ((await b.ev('__trailer.runTo(400, 50)')) < 400);
  const r = await b.ev(`(() => {
    const line = Array.from(document.querySelectorAll('#console *')).map((e) => e.textContent).find((l) => /n64_rdram 0x/.test(l));
    const rd = parseInt(/n64_rdram (0x[0-9a-f]+)/.exec(line)[1], 16);
    const H = Module.HEAPU8, U = new Uint32Array(H.buffer);
    const b8 = (o) => H[rd + (o ^ 3)];                       // N64 offset -> byte (virtual big-endian)
    const w32 = (o) => U[(rd + o) >> 2];                     // aligned word (native)
    const at = (p, k) => H[(p + k) ^ 3];                      // byte k of a wasm-pointer object in game memory
    const chars = []; for (let i = 0; i < 0x60; i++) chars.push(b8(0x85CC0 + i));
    const sets = [];
    for (let s = 0; s < 4; s++) {
      const tex = w32(0x85D20 + 8 * s), met = w32(0x85D24 + 8 * s);
      sets.push({ tex, met });
    }
    const tex = sets[0].tex, met = sets[0].met, glyphs = {};
    for (let g = 0; g < 0x61; g++) {
      const w = at(met, g * 4), h = at(met, g * 4 + 1), xo = at(met, g * 4 + 2), yo = at(met, g * 4 + 3);
      if (!w || !h) continue;
      const stride = (w + 7) & ~7, px = [];
      for (let y = 0; y < h; y++) for (let x = 0; x < w; x++) px.push(at(tex, g * 224 + y * stride + (y & 1 ? x ^ 4 : x)));
      glyphs[g] = { w, h, xo: xo > 127 ? xo - 256 : xo, yo: yo > 127 ? yo - 256 : yo, px };
    }
    return JSON.stringify({ rdram: rd, sets, chars, glyphs });
  })()`);
  const f = JSON.parse(r);
  fs.writeFileSync(out, r);
  const names = f.chars.map((c, i) => (f.glyphs[i] ? String.fromCharCode(c) : '')).join('');
  console.log(`font: rdram 0x${f.rdram.toString(16)}, sets ${JSON.stringify(f.sets.map((s) => [s.tex.toString(16), s.met.toString(16)]))}`);
  console.log(`chars (${Object.keys(f.glyphs).length} glyphs): ${JSON.stringify(names)}`);
  const g = f.glyphs[f.chars.indexOf(65)];
  if (g) { console.log(`'A' ${g.w}x${g.h} offset ${g.xo},${g.yo}:`); for (let y = 0; y < g.h; y++) console.log('  ' + g.px.slice(y * g.w, y * g.w + g.w).map((v) => ' .:-=+*#%@'[Math.min(9, v >> 4 >> 0 === 0 ? 0 : Math.ceil(v / 28))]).join('')); }
} finally { await b.close(); srv.close(); }
process.exit(0);
