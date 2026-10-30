// P354 trailer capture shim, injected into the game page before its own scripts (capture.mjs, CDP
// Page.addScriptToEvaluateOnNewDocument). The page and conker.wasm are not changed; this only takes over the clock
// and the audio sink from the outside:
//  - requestAnimationFrame is queued instead of run: window.__trailer.tick() runs one animation frame. With ?det=1 the
//    game's main loop runs exactly one VI retrace per animation frame (pc_sched.c frame(), pacing mode 0), so the
//    capture steps the game retrace by retrace, as slowly as it needs, and the result does not depend on wall time.
//  - the wasm import __port_web_audio_open (port/audio/aud_out.c) is replaced: no AudioContext is opened; the ring's
//    address and read / write indices are kept, and __trailer.drainAudio() copies what the game pushed since the last
//    call (stereo s16 at the game's rate, 22020 Hz PAL) into __trailer.pcm.
//  - __trailer.grab(url, w, h, quality) reads the WebGL canvas (preserveDrawingBuffer) into a JPEG and POSTs it to
//    the capture server (cdp.mjs serve, /upload/NAME).
(() => {
  const T = window.__trailer = { manual: true, q: [], now: 0, ticks: 0, aud: null, pcm: [], pcmFrames: 0, capAudio: false };
  // P370 ?trailerclock=1: performance.now() follows the stepped clock (20 ms per animation frame = one retrace), so the
  // page's own animations and timers read through it (customisation settings fade / cursor pulse / key repeat, boot
  // screens, photo mode HUD) move with the game, frame by frame, whatever the wall time of the capture
  if (/[?&]trailerclock=1/.test(location.search)) {
    const realNow = performance.now.bind(performance), clockBase = realNow();
    performance.now = () => clockBase + T.now;
    // the page's status toasts ("ROM: Conker EU, SHA-1 ok ...") are page messages, not the game's look: hidden in the film
    document.addEventListener('DOMContentLoaded', () => { const st = document.createElement('style'); st.textContent = '#toast { display: none !important; }'; document.head.appendChild(st); });
  }
  const realRAF = window.requestAnimationFrame.bind(window);
  window.requestAnimationFrame = (cb) => { if (!T.manual) return realRAF(cb); T.q.push(cb); return T.q.length; };
  window.cancelAnimationFrame = () => {};
  T.tick = () => {
    const q = T.q; T.q = []; T.now += 20; T.ticks++;
    for (const cb of q) { try { cb(T.now); } catch (e) { if (e !== 'unwind') console.log('[trailer] tick exception ' + e); } }
    T.drainAudio();
    if (T.capAudio) T.audMap.push([T.frame(), T.pcmFrames]);
  };
  T.audMap = [];
  // one output picture at retrace position pos (fractional): run the game up to floor(pos); with the High frame rate
  // option, redraw the newest game frame interpolated at t = (pos - newest) / interval (the option's own rule,
  // gfx_f3dex2.c port_gfx_hfr_present) through the test export port_gfx_hfr_test; then upload the canvas as a JPEG
  T.hf = { rnew: 0, ival: 2 };
  T.step = async (pos, hfr, url, w, h, q, ticks) => {
    const f = Math.floor(pos);
    if (ticks) for (let k = 0; k < ticks; k++) T.tick();   // photo mode: no retraces run, each tick draws a photo frame
    else while (T.frame() < f) T.tick();
    let t = -1, res = null;
    if (hfr && Module._port_gfx_hfr_frame) {
      const rn = Module._port_gfx_hfr_frame();
      if (rn !== T.hf.rnew) { if (T.hf.rnew && rn > T.hf.rnew && rn - T.hf.rnew <= 8) T.hf.ival = rn - T.hf.rnew; T.hf.rnew = rn; }
      t = Math.max(0, Math.min(1, (pos - rn) / T.hf.ival));
      res = Module._port_gfx_hfr_test(t);
    }
    const size = url ? await T.grab(url, w, h, q) : 0;
    return { frame: T.frame(), t: +t.toFixed(3), res, size };
  };
  T.frame = () => (window.Module && Module._port_net_frame ? Module._port_net_frame() : -1);
  // run animation frames until the game's retrace counter reaches f (at most max ticks per call)
  T.runTo = (f, max = 25) => { for (let i = 0; i < max && T.frame() < f; i++) T.tick(); return T.frame(); };
  T.drainAudio = () => {
    const a = T.aud; if (!a || !window.Module || !Module.HEAPU8) return 0;
    const buf = Module.HEAPU8.buffer;   // only HEAPU8 is exported: own views on its buffer (new ones after a memory growth)
    if (T.vbuf !== buf) { T.vbuf = buf; T.U32 = new Uint32Array(buf); T.S16 = new Int16Array(buf); }
    const U = T.U32, S = T.S16;
    let r = U[a.rdp >> 2]; const w = U[a.wrp >> 2], base = a.ring >> 1;
    const n = (w - r) & a.mask;
    if (n && T.capAudio) {
      const out = new Int16Array(2 * n);
      for (let i = 0; i < n; i++) { out[2 * i] = S[base + 2 * r]; out[2 * i + 1] = S[base + 2 * r + 1]; r = (r + 1) & a.mask; }
      T.pcm.push(out); T.pcmFrames += n;
    }
    U[a.rdp >> 2] = w;
    return n;
  };
  T.takePcm = () => {
    const all = new Int16Array(T.pcmFrames * 2); let o = 0;
    for (const c of T.pcm) { all.set(c, o); o += c.length; }
    T.pcm = []; T.pcmFrames = 0; return all;
  };
  const patch = (imp) => {
    if (!imp || !imp.env || !imp.env.__port_web_audio_open) return;
    imp.env.__port_web_audio_open = (rate, ring, rdp, wrp, mask, urp) => {
      T.aud = { rate, ring, rdp, wrp, mask };
      console.log(`[trailer] audio sink: ring ${ring} at ${rate} Hz (captured, not played)`);
      return rate;
    };
  };
  const oi = WebAssembly.instantiate, ois = WebAssembly.instantiateStreaming;
  WebAssembly.instantiate = function (src, imp) { patch(imp); return oi.call(this, src, imp); };
  if (ois) WebAssembly.instantiateStreaming = function (src, imp) { patch(imp); return ois.call(this, src, imp); };
  let oc = null;
  T.grab = async (url, w, h, quality = 0.93, sel = 'canvas') => {
    const c = document.getElementById(sel);
    w = w || c.width; h = h || c.height;
    if (!oc || oc.width !== w || oc.height !== h) oc = new OffscreenCanvas(w, h);
    const g = oc.getContext('2d');
    g.imageSmoothingQuality = 'high';
    g.drawImage(c, 0, 0, w, h);
    const blob = await oc.convertToBlob({ type: 'image/jpeg', quality });
    const r = await fetch(url, { method: 'POST', body: blob });
    return r.ok ? blob.size : -1;
  };
  T.upload = async (url, data) => (await fetch(url, { method: 'POST', body: data })).ok;
})();
