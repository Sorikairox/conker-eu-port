// P354 trailer tooling: a tiny headless-Chrome driver over the DevTools protocol (node >= 22, no packages) and a
// static file server. Same Chrome flags as port/web/audprobe.js (muted, autoplay allowed, ANGLE metal), but the
// caller drives the page itself (evaluate, screenshots, scripts injected before the page's own scripts).
//   import { launch, serve } from './cdp.mjs'
//   const srv = await serve({ '/app/': 'port/build/web', '/dev/rom.z64': 'baserom.eu.z64' }, 8590)
//   const b = await launch(url, { width, height, init: 'js run before the page', log: 'file' })
//   await b.ev('1 + 1'); await b.close(); srv.close()
import { spawn } from 'node:child_process';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import http from 'node:http';

const CH = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome';
export const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

const MIME = { '.html': 'text/html', '.js': 'text/javascript', '.mjs': 'text/javascript', '.wasm': 'application/wasm',
  '.json': 'application/json', '.png': 'image/png', '.jpg': 'image/jpeg', '.css': 'text/css', '.txt': 'text/plain',
  '.wav': 'audio/wav', '.mp4': 'video/mp4', '.webm': 'video/webm', '.svg': 'image/svg+xml' };

// mounts: { urlPrefix: localPath } (a prefix ending in '/' serves a directory, else one file). POST /upload/NAME
// writes the request body to uploadDir/NAME (the compositor page saves its output that way).
export function serve(mounts, port, uploadDir) {
  const srv = http.createServer((req, res) => {
    const u = decodeURIComponent(req.url.split('?')[0]);
    if (req.method === 'POST' && u.startsWith('/upload/') && uploadDir) {
      const f = path.join(uploadDir, path.basename(u)); const out = fs.createWriteStream(f);
      req.pipe(out); out.on('finish', () => { res.writeHead(200); res.end('ok'); });
      return;
    }
    for (const [pre, loc] of Object.entries(mounts)) {
      let f = null;
      if (pre.endsWith('/') && u.startsWith(pre)) f = path.join(loc, u.slice(pre.length) || 'index.html');
      else if (u === pre) f = loc;
      if (!f) continue;
      fs.stat(f, (e, st) => {
        if (e || !st.isFile()) { res.writeHead(404); res.end(); return; }
        res.writeHead(200, { 'Content-Type': MIME[path.extname(f)] || 'application/octet-stream', 'Content-Length': st.size,
          'Cache-Control': 'no-store' });
        fs.createReadStream(f).pipe(res);
      });
      return;
    }
    res.writeHead(404); res.end();
  });
  return new Promise((r) => srv.listen(port, '127.0.0.1', () => r(srv)));
}

export async function launch(url, opt = {}) {
  const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'trailer-chrome-'));
  const port = opt.debugPort || 9600 + (process.pid % 300);
  const args = ['--headless=new', `--user-data-dir=${dir}`, `--remote-debugging-port=${port}`, `--use-angle=${opt.angle || 'metal'}`,
    '--enable-unsafe-swiftshader', '--mute-audio', '--autoplay-policy=no-user-gesture-required', '--hide-scrollbars',
    '--disable-background-timer-throttling', '--disable-renderer-backgrounding', '--disable-backgrounding-occluded-windows',
    `--window-size=${opt.width || 1000},${opt.height || 900}`, ...(opt.args || []), 'about:blank'];
  const ch = spawn(CH, args, { stdio: 'ignore' });
  console.log(`chrome pid ${ch.pid}`);
  let closed = false;
  process.on('exit', () => { if (!closed) try { ch.kill('SIGKILL'); } catch (e) {} });
  for (const sig of ['SIGTERM', 'SIGINT', 'SIGHUP']) process.once(sig, () => process.exit(128));   // P370: a kill of the driver runs the exit handler too   // never leave a Chrome behind (a caller's uncaught error)
  const close = async () => { if (closed) return; closed = true; try { ch.kill('SIGKILL'); } catch (e) {} await sleep(300); fs.rmSync(dir, { recursive: true, force: true }); };
  let page;
  for (let i = 0; i < 60 && !page; i++) {
    await sleep(300);
    try { page = (await (await fetch(`http://127.0.0.1:${port}/json`)).json()).find((t) => t.type === 'page'); } catch (e) {}
  }
  if (!page) { await close(); throw new Error('no DevTools page'); }
  const ws = new WebSocket(page.webSocketDebuggerUrl);
  await new Promise((r) => ws.addEventListener('open', r));
  let id = 0; const pending = new Map(); const listeners = [];
  if (opt.log) fs.writeFileSync(opt.log, '');
  ws.addEventListener('message', (m) => {
    const d = JSON.parse(m.data);
    if (d.method === 'Runtime.consoleAPICalled' && opt.log)
      fs.appendFileSync(opt.log, d.params.args.map((a) => a.value ?? a.description ?? '').join(' ') + '\n');
    if (d.method === 'Runtime.exceptionThrown' && opt.log)
      fs.appendFileSync(opt.log, 'EXCEPTION ' + JSON.stringify(d.params.exceptionDetails).slice(0, 2000) + '\n');
    if (d.method) for (const l of listeners) l(d);
    if (pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); }
  });
  const call = (method, params = {}) => new Promise((r) => { pending.set(++id, r); ws.send(JSON.stringify({ id, method, params })); });
  // evaluate an expression (awaits promises); throws on exceptions
  const ev = async (expr, timeoutMs = 600000) => {
    const r = await Promise.race([call('Runtime.evaluate', { expression: expr, returnByValue: true, awaitPromise: true }),
      sleep(timeoutMs).then(() => ({ timeout: true }))]);
    if (r.timeout) throw new Error('evaluate timeout: ' + expr.slice(0, 120));
    if (r.error) throw new Error('evaluate error: ' + JSON.stringify(r.error));
    if (r.result.exceptionDetails) throw new Error('page exception: ' + (r.result.exceptionDetails.exception?.description || JSON.stringify(r.result.exceptionDetails)).slice(0, 1500));
    return r.result.result.value;
  };
  await call('Runtime.enable');
  await call('Page.enable');
  if (opt.viewport) await call('Emulation.setDeviceMetricsOverride', { width: opt.viewport[0], height: opt.viewport[1], deviceScaleFactor: opt.dpr || 1, mobile: !!opt.mobile });
  if (opt.mobile) await call('Emulation.setTouchEmulationEnabled', { enabled: true, maxTouchPoints: 5 });   // P370: a phone (touch screen) for the page's touch detection
  if (opt.init) await call('Page.addScriptToEvaluateOnNewDocument', { source: opt.init });
  if (url) await call('Page.navigate', { url });
  const screenshot = async (file, params = {}) => {
    const r = await call('Page.captureScreenshot', { format: 'png', ...params });
    fs.writeFileSync(file, Buffer.from(r.result.data, 'base64'));
  };
  const key = async (type, code, key, keyCode) => call('Input.dispatchKeyEvent', { type, code, key, windowsVirtualKeyCode: keyCode, nativeVirtualKeyCode: keyCode });
  const click = async (x, y) => { for (const type of ['mousePressed', 'mouseReleased']) await call('Input.dispatchMouseEvent', { type, x, y, button: 'left', clickCount: 1 }); };
  // P370: one touch point down / move / up at (x, y) CSS pixels (Input.dispatchTouchEvent, real touch events)
  const touch = async (type, x, y, id = 1) => call('Input.dispatchTouchEvent', { type, touchPoints: type === 'touchEnd' ? [] : [{ x, y, id, radiusX: 8, radiusY: 8, force: 1 }] });
  return { call, ev, close, screenshot, key, click, touch, pid: ch.pid, on: (f) => listeners.push(f) };
}
