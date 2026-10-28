// P354 trailer: contact sheet of JPEG / PNG pictures (drawn in headless Chrome; no image packages on the host).
//   node tools/port/trailer/sheet.mjs OUT.jpg COLS THUMB_W FILE...      (labels = file names; env LABELS=0 to omit)
//   node tools/port/trailer/sheet.mjs OUT.jpg COLS THUMB_W DIR/f%05d.jpg FIRST LAST STEP   (a numbered sequence)
import fs from 'node:fs';
import path from 'node:path';
import { launch, serve } from './cdp.mjs';

const [out, cols, tw, ...rest] = process.argv.slice(2);
let files = rest;
if (rest.length === 4 && rest[0].includes('%05d')) {
  const [pat, a, z, st] = rest; files = [];
  for (let i = +a; i <= +z; i += +st) files.push(pat.replace('%05d', String(i).padStart(5, '0')));
}
files = files.filter((f) => fs.existsSync(f)).map((f) => path.resolve(f));
const outAbs = path.resolve(out); fs.mkdirSync(path.dirname(outAbs), { recursive: true });
const port = 8650 + (process.pid % 40);
const srv = await serve({ '/f/': '/' }, port, path.dirname(outAbs));
const b = await launch(`http://127.0.0.1:${port}/f${path.resolve('tools/port/trailer/blank.html')}`);
await new Promise((r) => setTimeout(r, 800));
const labels = process.env.LABELS !== '0';
const r = await b.ev(`(async () => {
  const files = ${JSON.stringify(files)}, cols = ${+cols}, tw = ${+tw};
  const imgs = [];
  for (const f of files) { const im = new Image(); im.src = '/f' + f; await im.decode(); imgs.push(im); }
  const th = Math.round(tw * imgs[0].naturalHeight / imgs[0].naturalWidth), lh = ${labels ? 16 : 0};
  const rows = Math.ceil(imgs.length / cols);
  const c = new OffscreenCanvas(cols * (tw + 4) + 4, rows * (th + lh + 4) + 4), g = c.getContext('2d');
  g.fillStyle = '#222'; g.fillRect(0, 0, c.width, c.height); g.font = '12px sans-serif'; g.fillStyle = '#ddd';
  imgs.forEach((im, i) => { const x = 4 + (i % cols) * (tw + 4), y = 4 + Math.floor(i / cols) * (th + lh + 4);
    g.drawImage(im, x, y + lh, tw, th); if (lh) g.fillText(files[i].split('/').slice(-2).join('/'), x + 2, y + 12); });
  const blob = await c.convertToBlob({ type: 'image/jpeg', quality: 0.88 });
  await fetch('/upload/${path.basename(outAbs)}', { method: 'POST', body: blob });
  return imgs.length + ' pictures, ' + c.width + 'x' + c.height;
})()`);
console.log(`${out}: ${r}`);
await b.close(); srv.close(); process.exit(0);
