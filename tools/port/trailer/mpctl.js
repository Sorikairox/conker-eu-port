// P370 v6 trailer: a closed-loop "bot" for the 4-player Bunker match, run in the ?netdet replay (capture.mjs shot
// 'mpbot'): the pads' ?padf scripts hand every channel to the page at 5990 (F:P), and from then on this bot writes the
// port's pad buffer (Module._port_pad_state: present, buttons, x, y per channel -- the buffer the page itself writes
// when not under ?netdet) before every animation frame (= one retrace with ?det=1). It steers a hunter towards a prey
// from the players' positions in game memory (objects at N64 0x800CC6F0, 0x32C each, position floats +0x14 / +0x18 /
// +0x1C; read only) and then attacks. Every input is recorded with the retrace that reads it, so the run is replayed
// exactly as plain ?padf scripts (C.padf(ch), mpkill.py) without the bot. N64 units, y up; bits A 8000, B 4000,
// Z 2000, R 0010, C-down 0004.
//   __mpctl.install(); __mpctl.start({ hunter: 0, prey: 1, from: 5990, sign: 1, both: true })   __mpctl.dump()
(() => {
  const C = window.__mpctl = { on: false, rec: [new Map(), new Map(), new Map(), new Map()], log: [], st: [{}, {}, {}, {}], hist: [[], [], [], []], plan: new Map() };
  const mem = () => { const b = Module._port_net_page_info(4) >>> 0; return { b, f: new Float32Array(Module.HEAPU8.buffer), u: new Uint32Array(Module.HEAPU8.buffer) }; };
  const pos = (m, j) => { const q = m.b + 0xCC6F0 + j * 0x32C; return [m.f[(q + 0x14) >> 2], m.f[(q + 0x18) >> 2], m.f[(q + 0x1C) >> 2], m.u[q >> 2], m.f[(q + 0x40) >> 2]]; };   // [4] = facing, degrees (0 = +z: atan2(dx, dz))
  const ang = (a) => Math.atan2(Math.sin(a), Math.cos(a));
  const pack = (b, x, y) => ((b & 0xFFFF) << 16 | (x & 0xFF) << 8 | (y & 0xFF)) >>> 0;
  let lastF = -1;
  const sample = () => {   // the players' positions at the last retrace run (once per retrace)
    const f = Module._port_net_frame() >>> 0;
    if (f === lastF) return;
    lastF = f;
    const m = mem();
    for (let j = 0; j < 4; j++) { C.hist[j].push(pos(m, j)); if (C.hist[j].length > 80) C.hist[j].shift(); }
  };
  // heading = direction of the last ~8 retraces' motion; stick x turns (C.cfg.sign: which way), y pushes forward
  const steer = (i, t) => {
    const h = C.hist[i], n = h.length, P = h[n - 1], st = C.st[i];
    const dx = t[0] - P[0], dz = t[2] - P[2], dist = Math.hypot(dx, dz);
    if (n >= 9) { const a = h[n - 9]; const vx = P[0] - a[0], vz = P[2] - a[2]; if (Math.hypot(vx, vz) > 15) st.head = Math.atan2(vz, vx); }
    if (st.head === undefined) return { x: 0, y: 80, dist, e: 0 };
    const e = ang(Math.atan2(dz, dx) - st.head);
    const moved = n >= 40 ? Math.hypot(P[0] - h[n - 40][0], P[2] - h[n - 40][2]) : 999;
    st.stuck = moved < 60 ? (st.stuck || 0) + 1 : 0;
    if (st.stuck > 0 && st.stuck < 50) return { x: 80 * (st.slide || 1), y: 30, dist, e };   // against a wall: slide along it
    if (st.stuck >= 50) { st.slide = -(st.slide || 1); st.stuck = 1; }
    const x = Math.round(Math.max(-80, Math.min(80, C.cfg.sign * e * 110)));
    return { x, y: Math.round(80 * Math.max(0.4, Math.cos(e))), dist, e };
  };
  // the inputs of every channel for retrace f, decided once (from the state at the last retrace run)
  const decide = (f) => {
    if (C.plan.has(f)) return C.plan.get(f);
    sample();
    const cfg = C.cfg, H = cfg.hunter, V = cfg.prey, out = [0, 0, 0, 0];
    const Ph = C.hist[H][C.hist[H].length - 1], Pv = C.hist[V][C.hist[V].length - 1];
    const s = steer(H, Pv);
    if (C.phase === 'chase') {
      if (s.dist < cfg.near) { C.phase = 'aim'; C.log.push(`${f} near ${s.dist.toFixed(0)} e ${s.e.toFixed(2)}`); }
      else out[H] = pack(0, s.x, s.y);
      if (cfg.both && s.dist > cfg.near * 1.8) { const v = steer(V, Ph); out[V] = pack(0, v.x, v.y); }
    }
    if (C.phase === 'aim') {   // turn on the spot until the hunter FACES the prey (+0x40 facing), then the attack
      const ye = ang(Math.atan2(Pv[0] - Ph[0], Pv[2] - Ph[2]) - Ph[4] * Math.PI / 180);   // facing 0 = +z, = atan2(dx, dz)
      if (!C.aimAt) C.aimAt = f;
      if (f % 25 === 0) C.log.push(`${f} aim facing ${Ph[4].toFixed(0)} err ${(ye * 180 / Math.PI).toFixed(0)}`);
      if (Math.abs(ye) > cfg.aimTol && f - C.aimAt < 150) out[H] = pack(0, Math.round(Math.max(-80, Math.min(80, cfg.aimSign * ye * 90))), cfg.aimPush);
      else { C.phase = 'fire'; C.fireAt = f; C.log.push(`${f} fire, facing err ${(ye * 180 / Math.PI).toFixed(0)} dist ${s.dist.toFixed(0)}`); }
    }
    if (C.phase === 'fire') {
      const k = f - C.fireAt;
      if (cfg.attack) out[H] = cfg.attack(k, s) ?? out[H];
      if (k > (cfg.fireLen || 240)) { C.phase = 'done'; C.log.push(`${f} done`); }
    }
    C.plan.set(f, out);
    if (C.plan.size > 400) C.plan.delete(C.plan.keys().next().value);
    return out;
  };
  C.install = () => {   // before every animation frame: the inputs of the coming retrace into the pad buffer
    const ot = __trailer.tick;
    __trailer.tick = () => {
      if (C.on) {
        const f = (Module._port_net_frame() >>> 0) + 1 + (C.cfg.recShift || 0), v = decide(f), p = Module._port_pad_state() >> 2, H = Module.HEAP32;
        for (let ch = 0; ch < 4; ch++) {
          const b = v[ch] >>> 16, x = (v[ch] >> 8 & 0xFF) << 24 >> 24, y = (v[ch] & 0xFF) << 24 >> 24;
          H[p + ch * 4 + 1] = b; H[p + ch * 4 + 2] = x; H[p + ch * 4 + 3] = y;
          C.rec[ch].set(f, v[ch] >>> 0);
        }
      }
      ot();
    };
    return 'installed';
  };
  C.start = (cfg) => {
    C.cfg = Object.assign({ hunter: 0, prey: 1, from: 5990, near: 350, aimTol: 0.12, sign: 1, aimSign: 1, aimPush: 20, both: true,
      attack: (k) => (k < 6 || (k >= 60 && k < 66) ? pack(0x0004, 0, 0) : 0) }, cfg);   // default attack: two grenades (C-down)
    C.on = true; C.phase = 'chase'; return 'started';
  };
  C.padf = (ch) => {   // changes only, ?padf syntax, from the recorded inputs of the bot's part (the channels' own scripts before)
    const out = []; let last = ''; const fs = [...C.rec[ch].keys()].sort((a, b) => a - b);
    for (const f of fs) {
      const v = C.rec[ch].get(f), b = v >>> 16, x = (v >> 8 & 0xFF) << 24 >> 24, y = (v & 0xFF) << 24 >> 24;
      const s = `${b.toString(16).toUpperCase()}:${x}:${y}`; if (s !== last) { out.push(`${f}:${s}`); last = s; }
    }
    return out.join(',');
  };
  C.dump = () => JSON.stringify({ log: C.log, phase: C.phase, padf: [0, 1, 2, 3].map(C.padf) });
})();
