// Page glue for the Conker wasm32 port. The ROM is supplied by the user and never leaves the browser
// (cached in IndexedDB). Two wasm apps: the scheduler demo and the game; one per page load.
'use strict';
const EU_SHA1 = 'ee7bc6656fd1e1d9ffb3d19add759f28b88df710';
const $ = (id) => document.getElementById(id);
const out = $('console');
let romBytes = null;
let running = null;

function log(s, cls) {
  const line = document.createElement('div');
  line.textContent = s;
  if (cls) line.className = cls;
  else if (/^PASS/.test(s)) line.className = 'pass';
  else if (/^FAIL|RuntimeError|Aborted/.test(s)) line.className = 'fail';
  else if (/^\[stub/.test(s)) line.className = 'stub';
  out.appendChild(line);
  out.scrollTop = out.scrollHeight;
  console.log(s);
}
const status = (s) => { $('status').textContent = s; };

// ---- ROM: byte order, SHA1, IndexedDB cache
function toZ64(b) {
  const m = (b[0] << 24 | b[1] << 16 | b[2] << 8 | b[3]) >>> 0;
  if (m === 0x80371240) return b;
  const o = new Uint8Array(b.length);
  if (m === 0x37804012) { for (let i = 0; i < b.length; i += 2) { o[i] = b[i + 1]; o[i + 1] = b[i]; } return o; } // .v64
  if (m === 0x40123780) { for (let i = 0; i < b.length; i += 4) { o[i] = b[i + 3]; o[i + 1] = b[i + 2]; o[i + 2] = b[i + 1]; o[i + 3] = b[i]; } return o; } // .n64
  throw new Error('not an N64 ROM (magic ' + m.toString(16) + ')');
}
async function sha1(b) {
  if (!crypto.subtle) return '?';
  const h = new Uint8Array(await crypto.subtle.digest('SHA-1', b));
  return Array.from(h, (x) => x.toString(16).padStart(2, '0')).join('');
}
function idb(mode, fn) {
  return new Promise((res, rej) => {
    const r = indexedDB.open('conker-port', 1);
    r.onupgradeneeded = () => r.result.createObjectStore('rom');
    r.onerror = () => rej(r.error);
    r.onsuccess = () => {
      const tx = r.result.transaction('rom', mode);
      const q = fn(tx.objectStore('rom'));
      tx.oncomplete = () => res(q && q.result);
      tx.onerror = () => rej(tx.error);
    };
  });
}
async function setRom(bytes, from) {
  romBytes = toZ64(bytes);
  const h = await sha1(romBytes);
  const ok = h === EU_SHA1;
  status(`ROM ${(romBytes.length / 1048576).toFixed(0)} MB from ${from}: ${ok ? 'Conker EU (sha1 ok)' : 'sha1 ' + h + ' (not the EU ROM)'}`);
  $('game').disabled = !!running;
  return ok;
}
$('rom').addEventListener('change', async (e) => {
  const f = e.target.files[0];
  if (!f) return;
  try {
    const ok = await setRom(new Uint8Array(await f.arrayBuffer()), f.name);
    if (ok) await idb('readwrite', (s) => s.put(romBytes, 'eu')).catch(() => {});
  } catch (err) { log('ROM: ' + err.message, 'fail'); }
});

// ---- wasm apps
function loadScript(src) {
  return new Promise((res, rej) => {
    const s = document.createElement('script');
    s.src = src; s.onload = res; s.onerror = () => rej(new Error('cannot load ' + src));
    document.head.appendChild(s);
  });
}
async function start(app) {
  if (running) { location.search = '?app=' + app; return; } // one module per page
  running = app;
  $('demo').disabled = $('game').disabled = true;
  const [js, factory] = app === 'demo' ? ['sched_demo.js', 'createSchedDemo'] : ['conker.js', 'createConker'];
  log(`-- loading ${js}`);
  await loadScript(js);
  const M = await window[factory]({
    canvas: $('canvas'),
    print: (s) => log(s),
    printErr: (s) => log(s, 'fail'),
    onAbort: (w) => log('Aborted: ' + w, 'fail'),
  });
  window.Module = M;
  if (app === 'game' && romBytes) {
    const p = M._malloc(romBytes.length);
    M.HEAPU8.set(romBytes, p);
    M._port_set_rom(p, romBytes.length);
  }
  $('threads').disabled = false;
  $('threads').onclick = () => M._port_dump_threads();
  try { M.callMain([]); } catch (e) { if (e !== 'unwind') log(String(e), 'fail'); }
}
window.addEventListener('error', (e) => log(String(e.message || e), 'fail'));
$('demo').onclick = () => start('demo');
$('game').onclick = () => start('game');

(async () => {
  try {
    const cached = await idb('readonly', (s) => s.get('eu'));
    if (cached) await setRom(new Uint8Array(cached), 'IndexedDB cache');
  } catch (e) { /* no IndexedDB: fine */ }
  const app = new URLSearchParams(location.search).get('app');
  if (app === 'demo' || (app === 'game' && romBytes)) start(app);
})();
