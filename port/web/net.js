// P338 online multiplayer, phase 1 (docs/design/ONLINE_MULTIPLAYER.md): the page side of the lockstep session.
// Loaded by main.js only when a session is used (the Online panel or the ?netloop test); without it nothing here runs.
// The game side is port/ultra/pc_net.c: an input ring of 256 frames x 4 channels in wasm memory, a frame barrier in
// pc_sched.c frame() (retrace N runs only when every session channel's input for N is in the ring), input delay D
// (the local input for frame N + D is sampled at the start of retrace N), and a state hash every K retraces.
// This file reads the local entries out of the ring (to send them), writes the peers' entries in, and reads the hashes.
'use strict';
(function () {
  const RING = 256;
  let u32 = null;   // HEAPU32 is not exported by conker.js: a view on the same memory, renewed if it grows
  const U32 = () => { if (!u32 || u32.buffer !== N.M.HEAPU8.buffer) u32 = new Uint32Array(N.M.HEAPU8.buffer); return u32; };
  const N = {
    M: null, cfg: null, base: {}, log: (s) => console.log(s),
    // ---- the game side (port/ultra/pc_net.c)
    begin(M, cfg, log) {   // before callMain: cfg = { mask, local, delay, hashEvery }
      N.M = M; N.cfg = cfg; if (log) N.log = log;
      M._port_net_session(cfg.mask, cfg.local, cfg.delay, cfg.hashEvery);
      for (const [k, i] of [['input', 0], ['frame', 1], ['hash', 2], ['pad', 3], ['stat', 4]]) N.base[k] = M._port_net_addr(i) >>> 2;
    },
    frame() { return N.M._port_net_frame() >>> 0; },          // the last retrace run
    stat(i) { return U32()[N.base.stat + i]; },          // 0 stalled ticks, 1 stalled retrace slots
    has(f, ch) { return U32()[N.base.frame + (f % RING) * 4 + ch] === f; },
    get(f, ch) { return N.has(f, ch) ? U32()[N.base.input + (f % RING) * 4 + ch] : -1; },
    put(f, ch, v) {   // a peer's input for frame f (packed: buttons << 16 | (u8)x << 8 | (u8)y)
      if (f <= N.frame() || N.has(f, ch)) return false;      // already run / already there (packets repeat inputs)
      const i = (f % RING) * 4 + ch, H = U32();
      H[N.base.input + i] = v >>> 0; H[N.base.frame + i] = f;
      return true;
    },
    localTop() { return N.frame() + N.cfg.delay; },            // newest local frame sampled so far
    setLocalPad(b, x, y) { const H = N.M.HEAP32, p = N.base.pad; H[p] = 1; H[p + 1] = b; H[p + 2] = x; H[p + 3] = y; },
    hashes() {   // [{f, h, s}] of the hash ring, oldest first
      const H = U32(), out = [];
      for (let i = 0; i < 64; i++) { const p = N.base.hash + i * 3; if (H[p]) out.push({ f: H[p], h: H[p + 1], s: H[p + 2] }); }
      return out.sort((a, b) => a.f - b.f);
    },
    // ---- test: a loopback peer in the same page (?netloop=1). It owns every session channel that is not local and
    // plays the channel's ?padf script, as a remote peer at the same retrace would: the input for frame f leaves when
    // this page has sampled its own frame f (f <= frame + D) and arrives lat ms later; with loss % of the sends lost,
    // a lost input is sent again with the next packet (every 20 ms), as the real transport repeats unacked inputs.
    loopback({ lat = 0, loss = 0 } = {}) {
      const remote = [0, 1, 2, 3].filter((ch) => (N.cfg.mask >> ch & 1) && !(N.cfg.local >> ch & 1));
      let next = N.cfg.delay + 1, sent = 0, lost = 0, lastLog = 0;
      const q = [];
      setInterval(() => {
        const now = performance.now(), top = N.localTop();
        for (; next <= top; next++) for (const ch of remote) q.push({ t: now + lat, f: next, ch, v: N.M._port_net_script_input(ch, next) });
        for (let i = 0; i < q.length;) {
          const e = q[i];
          if (e.t > now) { i++; continue; }
          sent++;
          if (loss && Math.random() * 100 < loss) { lost++; e.t = now + 20 + lat; i++; continue; }
          N.put(e.f, e.ch, e.v); q.splice(i, 1);
        }
        const f = N.frame();
        if (f >= lastLog + 500) {
          lastLog = f - f % 500;
          const hs = N.hashes(), h = hs[hs.length - 1];
          N.log(`[net] retrace ${f}: stalled ticks ${N.stat(0)} (${N.stat(1)} retrace slots), loopback sends ${sent} lost ${lost}` +
                (h ? `, hash ${h.f} ${h.h.toString(16)} ${h.s.toString(16)}` : ''));
        }
      }, 4);
      N.log(`[net] loopback peer: channels ${remote.join(',')}, latency ${lat} ms, loss ${loss} %`);
    },
  };
  window.PortNet = N;
})();
