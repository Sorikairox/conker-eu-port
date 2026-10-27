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
      M.netAfterTick = () => { if (N.afterTick) N.afterTick(); };   // P339: pc_net.c, right after a local input is sampled
    },
    frame() { return N.M._port_net_frame() >>> 0; },          // the last retrace run
    ready(f) { return N.M._port_net_ready(f) !== 0; },          // may retrace f run (the frame barrier)
    stat(i) { return U32()[N.base.stat + i]; },          // 0 stalled ticks, 1 stalled retrace slots, 7 ms slowed (time sync)
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
  // ---------------------------------------------------------------- P338 item 2: the WebRTC transport
  // Two peers (host = controller 1, guest = controller 2). One RTCPeerConnection with two negotiated DataChannels:
  // 'ctl' (reliable, ordered: session setup, bye) and 'in' (unordered, maxRetransmits 0: input packets, pings).
  // Signaling is copy-paste: the host's offer code and the guest's answer code are the SDP after ICE gathering
  // (no trickle), deflate-compressed and base64url-encoded. Only public STUN, no TURN: a pair behind strict NATs
  // cannot connect, and the page says so.
  // Input packet (little endian): u8 type 1 | u8 channel | u32 ack (the newest frame of the receiver's channel this
  // sender holds without gaps) | u32 first frame | u8 count | u32 input x count | u32 hash frame | u32 H | u32 S |
  // u32 the sender's last retrace | i16 the sender's input margin x 64 (P339 time sync, below).
  // Every packet repeats all of the sender's inputs the receiver has not acknowledged (up to 64), so a lost packet
  // costs nothing and only a burst longer than the input delay stalls. Ping: u8 2 | f64 time; pong: u8 3 | f64 time.
  // P339: a packet leaves as soon as a local input is sampled (pc_net.c, start of each retrace), the same packet goes
  // out a second time ~8 ms later (one lost packet then costs nothing), and a keep-alive every 30 ms. A packet that
  // brings the input a stalled game waits for runs the retrace at once (pc_sched.c port_net_kick).
  // Time sync (GGPO-style frame advantage): the input margin = frames of the other player's input this peer holds
  // beyond the retrace it has run (time average, ~0.5 s). The peer that is ahead of the other one sees a small margin
  // (its retraces run early, the inputs arrive just in time or late); the other one sees a large margin. Every 250 ms
  // the peer whose margin is smaller by more than 0.3 frames asks the game to slow down by about half the difference
  // (pc_net.c port_net_slow: it delays retraces within the 50 Hz pacing), so both sit in the middle of the input window
  // and neither stalls. The faster peer never speeds up (catching up in bursts uses up the margin: P338).
  const STUN = [{ urls: 'stun:stun.l.google.com:19302' }, { urls: 'stun:stun.cloudflare.com:3478' }];
  const CODE_TAG = 'CK1.';
  async function packCode(obj) {
    const raw = new TextEncoder().encode(JSON.stringify(obj));
    const z = new Uint8Array(await new Response(new Blob([raw]).stream().pipeThrough(new CompressionStream('deflate-raw'))).arrayBuffer());
    let s = ''; for (let i = 0; i < z.length; i += 32768) s += String.fromCharCode.apply(null, z.subarray(i, i + 32768));
    return CODE_TAG + btoa(s).replace(/\+/g, '-').replace(/\//g, '_').replace(/=+$/, '');
  }
  async function unpackCode(code) {
    code = String(code).replace(/\s+/g, '');
    if (!code.startsWith(CODE_TAG)) throw new Error('not a connection code (it starts with ' + CODE_TAG + ')');
    const b = atob(code.slice(CODE_TAG.length).replace(/-/g, '+').replace(/_/g, '/'));
    const z = Uint8Array.from(b, (c) => c.charCodeAt(0));
    const raw = await new Response(new Blob([z]).stream().pipeThrough(new DecompressionStream('deflate-raw'))).arrayBuffer();
    return JSON.parse(new TextDecoder().decode(raw));
  }
  const b64 = (u8) => { let s = ''; for (let i = 0; i < u8.length; i += 32768) s += String.fromCharCode.apply(null, u8.subarray(i, i + 32768)); return btoa(s); };
  const unb64 = (s) => Uint8Array.from(atob(s), (c) => c.charCodeAt(0));

  // test aid: ?netsim=lat:80,jit:20,loss:5 delays (ms, plus 0..jit), reorders and drops this page's input packets
  const SIM = {};
  { const m = /[?&]netsim=([^&]*)/.exec(location.search); if (m) for (const kv of decodeURIComponent(m[1]).split(',')) { const [k, v] = kv.split(':'); SIM[k] = +v || 0; } }

  const T = N.t = {
    pc: null, ctl: null, inp: null, role: null, myCh: 0, peerCh: 1, state: 'idle',
    peerAck: 0,         // newest frame of my channel the peer holds
    recvTop: 0,         // newest frame of the peer's channel I hold without gaps
    pending: [],        // peer inputs that arrived before the session began [f, v]
    peerHash: new Map(), myHashSeen: 0, desync: null,
    rtt: 0, lastRecv: 0, sent: 0, recv: 0, simDropped: 0, left: false,
    myMargin: 0, peerMargin: 0, peerFrame: 0, marginAt: 0, slowAsked: 0,   // P339 time sync
    on: {},             // event handlers set by main.js: status(text, cls), config(cfg), desync(info), left()
  };
  const emit = (ev, ...a) => { if (T.on[ev]) try { T.on[ev](...a); } catch (e) { N.log('[net] ' + ev + ' handler: ' + e, 'fail'); } };
  const status = (s, cls) => { T.state = s; emit('status', s, cls); N.log('[net] ' + s); };

  function newPc() {
    const pc = new RTCPeerConnection({ iceServers: STUN });
    T.pc = pc;
    T.ctl = pc.createDataChannel('ctl', { negotiated: true, id: 0 });
    T.inp = pc.createDataChannel('in', { negotiated: true, id: 1, ordered: false, maxRetransmits: 0 });
    T.inp.binaryType = 'arraybuffer';
    T.ctl.onopen = () => { status('connected', 'ok'); if (T.role === 'guest') sendCtl({ t: 'hello', build: N.buildId, rom: N.romSha256 }); };
    T.ctl.onmessage = (e) => onCtl(JSON.parse(e.data));
    T.ctl.onclose = () => peerLost('the connection closed');
    T.inp.onmessage = (e) => onPacket(e.data);
    pc.oniceconnectionstatechange = () => {
      const s = pc.iceConnectionState;
      N.log('[net] ICE ' + s);
      if (s === 'failed') {
        if (T.state === 'playing') peerLost('the network path failed');
        else status('Could not connect: the two networks do not allow a direct connection (no relay server is used). Try another network, e.g. a phone hotspot.', 'bad');
      }
    };
    return pc;
  }
  function gathered(pc, ms = 8000) {
    return new Promise((res) => {
      if (pc.iceGatheringState === 'complete') return res();
      const t = setTimeout(res, ms);   // use what was gathered so far
      pc.addEventListener('icegatheringstatechange', () => { if (pc.iceGatheringState === 'complete') { clearTimeout(t); res(); } });
    });
  }
  // host: returns the offer code to send to the guest
  N.host = async function (sessionFn) {
    T.role = 'host'; T.myCh = 0; T.peerCh = 1; T.sessionFn = sessionFn;
    const pc = newPc();
    await pc.setLocalDescription(await pc.createOffer());
    status('gathering network addresses…');
    await gathered(pc);
    status('waiting for the answer code', 'ok');
    return packCode({ t: 'o', sdp: pc.localDescription.sdp });
  };
  // guest: takes the host's offer code, returns the answer code
  N.join = async function (code) {
    T.role = 'guest'; T.myCh = 1; T.peerCh = 0;
    const o = await unpackCode(code);
    if (o.t !== 'o') throw new Error('this is not an offer code (paste the code the host made)');
    const pc = newPc();
    await pc.setRemoteDescription({ type: 'offer', sdp: o.sdp });
    await pc.setLocalDescription(await pc.createAnswer());
    status('gathering network addresses…');
    await gathered(pc);
    status('send the answer code to the host, then wait', 'ok');
    return packCode({ t: 'a', sdp: pc.localDescription.sdp });
  };
  // host: takes the guest's answer code
  N.accept = async function (code) {
    const a = await unpackCode(code);
    if (a.t !== 'a') throw new Error('this is not an answer code (paste the code the guest sent back)');
    await T.pc.setRemoteDescription({ type: 'answer', sdp: a.sdp });
    status('connecting…');
  };
  N.leave = function () { try { sendCtl({ t: 'bye' }); } catch (e) { /* closed */ } setTimeout(() => { try { T.pc && T.pc.close(); } catch (e) { /* closed */ } }, 100); };

  function sendCtl(m) { if (T.ctl && T.ctl.readyState === 'open') T.ctl.send(JSON.stringify(m)); }
  // P339 item 2: before the session starts, the host pings the guest over 'ctl' (PING_COUNT pings, PING_GAP_MS apart,
  // at most PING_WAIT_MS) and picks the input delay from the round trips (N.autoDelay). Under ?netsim the pings and
  // pongs get the same latency / jitter as the input packets (not the loss: 'ctl' is reliable).
  const PING_COUNT = 12, PING_GAP_MS = 40, PING_WAIT_MS = 2000;
  let pingDone = null;
  const pingRtts = [];
  function sendCtlSim(m) { const ms = (SIM.lat || 0) + Math.random() * (SIM.jit || 0); if (ms) setTimeout(() => sendCtl(m), ms); else sendCtl(m); }
  function measurePing() {
    return new Promise((resolve) => {
      pingRtts.length = 0;
      const finish = () => { if (!pingDone) return; pingDone = null; const r = pingRtts.slice().sort((a, b) => a - b);
        resolve(r.length ? { n: r.length, min: r[0], median: r[r.length >> 1], p90: r[Math.min(r.length - 1, Math.floor(r.length * 0.9))] } : null); };
      pingDone = () => { if (pingRtts.length >= PING_COUNT) finish(); };
      for (let i = 0; i < PING_COUNT; i++) setTimeout(() => sendCtlSim({ t: 'ping', at: performance.now() }), i * PING_GAP_MS);
      setTimeout(finish, PING_WAIT_MS);
    });
  }
  // D = clamp(ceil((RTT / 2 + jitter margin) / 20 ms) + 1, 2, 8): RTT = the median round trip, jitter margin = half of
  // (90th percentile - median); the + 1 covers sending / scheduling and the loss of single packets
  N.autoDelay = (p) => p ? Math.max(2, Math.min(8, Math.ceil((p.median / 2 + (p.p90 - p.median) / 2) / 20) + 1)) : 4;
  async function onCtl(m) {
    if (m.t === 'ping') { sendCtlSim({ t: 'pong', at: m.at }); return; }
    if (m.t === 'pong') { if (pingDone) { pingRtts.push(performance.now() - m.at); pingDone(); } return; }
    if (m.t === 'hello' && T.role === 'host') {   // the guest's build and ROM must be ours
      if (m.build !== N.buildId) { sendCtl({ t: 'refuse', why: 'different game builds (reload both pages to get the latest version)' }); status('refused: the guest runs a different build', 'bad'); return; }
      if (m.rom !== N.romSha256) { sendCtl({ t: 'refuse', why: 'different ROMs (the EU ROM is needed on both sides)' }); status('refused: the guest has a different ROM', 'bad'); return; }
      status('measuring the ping…', 'ok');
      const ping = await measurePing();   // P339 item 2
      if (ping) { T.rtt = ping.median; N.log(`[net] ping over ${ping.n} round trips: min ${ping.min.toFixed(1)} median ${ping.median.toFixed(1)} p90 ${ping.p90.toFixed(1)} ms -> auto input delay ${N.autoDelay(ping)}`); }
      const cfg = await T.sessionFn(ping);   // {mask, delay, autoDelay, hashEvery, options, eeprom (Uint8Array|null)}
      cfg.ping = ping ? Math.round(ping.median) : 0;
      sendCtl({ t: 'config', mask: cfg.mask, delay: cfg.delay, autoDelay: cfg.autoDelay, ping: cfg.ping, hashEvery: cfg.hashEvery, options: cfg.options, eeprom: cfg.eeprom ? b64(cfg.eeprom) : null, ch: T.peerCh });
      emit('config', Object.assign({}, cfg, { local: 1 << T.myCh }));
    } else if (m.t === 'config' && T.role === 'guest') {
      T.myCh = m.ch;
      if (m.ping) T.rtt = m.ping;
      emit('config', { mask: m.mask, local: 1 << m.ch, delay: m.delay, autoDelay: m.autoDelay, ping: m.ping, hashEvery: m.hashEvery, options: m.options, eeprom: m.eeprom ? unb64(m.eeprom) : null });
    } else if (m.t === 'refuse') status('the host refused: ' + m.why, 'bad');
    else if (m.t === 'bye') peerLost('the other player left');
    else if (m.t === 'desync') { emit('desync', Object.assign({ remote: true }, m)); sendPages(m.frame); }
    else if (m.t === 'pages') comparePages(m);
  }
  // ---- P339 desync report: both peers swap the per-page hashes of the desync retrace (pc_nethash.c keeps the last 16
  // hash points: 4 KB pages of the static region + one hash per game-thread stack) and name the first page that
  // differs, with the symbols in it (conker_netsyms.txt from port/tools/net_regions.py --syms: wasm static symbols
  // and, inside the n64_rdram mirror, the game's N64 data symbols with their current names).
  const pagesSent = new Set();
  function pageVector(frame) {
    const p = N.M._port_net_page_hashes(frame) >>> 0;
    if (!p) return null;
    const n = N.M._port_net_page_info(0) + N.M._port_net_page_info(1);
    return new Uint32Array(N.M.HEAPU8.buffer.slice(p, p + 4 * n));
  }
  function sendPages(frame) {
    if (!frame || pagesSent.has(frame)) return;
    pagesSent.add(frame);
    const v = pageVector(frame);
    if (!v) { N.log(`[net] desync report: the page hashes of retrace ${frame} are no longer kept`, 'fail'); return; }
    sendCtl({ t: 'pages', frame, h: b64(new Uint8Array(v.buffer)) });
  }
  let symTable = null;
  async function symbols() {
    if (!symTable) {
      symTable = { W: [], N: [] };
      try {
        for (const l of (await (await fetch('conker_netsyms.txt')).text()).split('\n')) {
          const f = l.split(' ');
          if (f.length >= 4 && symTable[f[0]]) symTable[f[0]].push([parseInt(f[1], 16), parseInt(f[2], 16), f[3]]);
        }
      } catch (e) { /* no table: addresses only */ }
      for (const k of ['W', 'N']) symTable[k].sort((x, y) => x[0] - y[0]);
    }
    return symTable;
  }
  const hex = (x) => (x >>> 0).toString(16).toUpperCase().padStart(8, '0');
  async function comparePages(m) {
    const mine = pageVector(m.frame);
    sendPages(m.frame);   // the other side needs mine too
    if (!mine) return;
    const theirs = new Uint32Array(unb64(m.h).buffer), pages = N.M._port_net_page_info(0), slots = N.M._port_net_page_info(1);
    const diff = [], stacks = [];
    for (let i = 0; i < pages; i++) if (mine[i] !== theirs[i]) diff.push(i);
    for (let i = 0; i < slots; i++) if (mine[pages + i] !== theirs[pages + i]) stacks.push(i);
    const base = N.M._port_net_page_info(2) >>> 0, size = N.M._port_net_page_info(3), rdram = N.M._port_net_page_info(4) >>> 0;
    let where = 'no static page differs';
    if (diff.length) {
      const a = base + diff[0] * size, syms = await symbols();
      let list, label;
      if (a >= rdram && a < rdram + 0x800000) {
        const n64 = 0x80000000 + (a - rdram);
        label = `n64_rdram N64 ${hex(n64)}..${hex(n64 + size - 1)}`;
        list = syms.N.filter(([s, l]) => s < n64 + size && s + Math.max(l, 1) > n64);
      } else {
        label = `wasm ${hex(a)}..${hex(a + size - 1)}`;
        list = syms.W.filter(([s, l]) => s < a + size && s + Math.max(l, 1) > a);
      }
      where = `first different page ${diff[0]} (${label}${list.length ? `, ${list.length} symbol(s) in it: ` + list.slice(0, 6).map((x) => x[2]).join(', ') + (list.length > 6 ? ', …' : '') : ''})`;
    }
    const report = { frame: m.frame, where, pages: diff.length, firstPages: diff.slice(0, 8), stacks };
    T.desyncReport = report;
    N.log(`[net] DESYNC REPORT retrace ${m.frame}: ${where}; ${diff.length} page(s) differ` +
          `${diff.length ? ' [' + diff.slice(0, 8).join(' ') + (diff.length > 8 ? ' …' : '') + ']' : ''}, thread stacks ${stacks.length ? stacks.join(' ') : 'none'}`, 'fail');
    emit('desyncReport', report);
  }

  // ---- P339: a hidden page's timers (the 4 ms main loop, the pump) are throttled to ~1 Hz by Chrome, even with a live
  // WebRTC connection, and the other player would wait. While hidden, a dedicated Worker posts a message every 4 ms
  // (worker timers are not throttled); each one runs a game tick (pc_sched.c port_net_kick) and the pump.
  let hiddenTicker = null, hiddenTicks = 0;
  N.background = function (hidden) {
    if (hidden && !hiddenTicker) {
      hiddenTicker = new Worker(URL.createObjectURL(new Blob(['setInterval(() => postMessage(0), 4);'], { type: 'text/javascript' })));
      hiddenTicker.onmessage = () => { hiddenTicks++; N.M._port_net_kick(); pump(); };
    } else if (!hidden && hiddenTicker) { hiddenTicker.terminate(); hiddenTicker = null; }
    N.log(`[net] page ${hidden ? 'hidden: the game ticks from a worker timer' : 'visible again'} (retrace ${N.frame()}, ${hiddenTicks} worker ticks so far)`);
  };

  // ---- session (after N.begin): the pump sends inputs, pings, checks for a lost peer
  N.startTransport = function () {
    for (const [f, v] of T.pending) N.put(f, T.peerCh, v);
    T.recvTop = Math.max(T.recvTop, N.cfg.delay); T.peerAck = Math.max(T.peerAck, N.cfg.delay);   // frames 1..D are neutral
    T.pending = []; advanceRecvTop();
    T.lastRecv = performance.now();
    status('waiting for the other player', 'ok');
    N.afterTick = () => sendInputs(performance.now());   // P339
    setInterval(pump, 5);
    setInterval(timeSync, 250);
    if (document.hidden) N.background(true);   // P339: the page was hidden before the session started
    setInterval(() => { const b = new DataView(new ArrayBuffer(9)); b.setUint8(0, 2); b.setFloat64(1, performance.now(), true); sendIn(b.buffer); }, 1000);
  };
  function advanceRecvTop() { while (N.has(T.recvTop + 1, T.peerCh)) T.recvTop++; }
  let lastSendTop = 0, lastSendAt = 0, lastPacket = null, lastPacketRepeated = true, lastSyncLog = 0;
  // one input packet: every local input the peer has not acknowledged, the ack, the newest hash, retrace and margin
  function sendInputs(now) {
    const top = N.localTop();
    const first = Math.max(T.peerAck + 1, N.cfg.delay + 1, top - 63);
    const count = Math.max(0, top - first + 1);
    const dv = new DataView(new ArrayBuffer(11 + 4 * count + 18));
    dv.setUint8(0, 1); dv.setUint8(1, T.myCh); dv.setUint32(2, T.recvTop, true); dv.setUint32(6, first, true); dv.setUint8(10, count);
    for (let i = 0; i < count; i++) dv.setUint32(11 + 4 * i, N.get(first + i, T.myCh) >>> 0, true);
    const hs = N.hashes(), h = hs[hs.length - 1] || { f: 0, h: 0, s: 0 }, o = 11 + 4 * count;
    dv.setUint32(o, h.f, true); dv.setUint32(o + 4, h.h, true); dv.setUint32(o + 8, h.s, true);
    dv.setUint32(o + 12, N.frame(), true); dv.setInt16(o + 16, Math.max(-32768, Math.min(32767, Math.round(T.myMargin * 64))), true);
    sendIn(dv.buffer);
    lastSendTop = top; lastSendAt = now; lastPacket = dv.buffer; lastPacketRepeated = false;
  }
  function pump() {
    if (T.left) return;
    const now = performance.now(), lastRun = N.frame();   // P339 name: lastRun was f
    // the input margin, time-averaged (exponential, time constant 500 ms)
    const margin = T.recvTop - lastRun;
    if (T.marginAt) { const a = Math.min(1, (now - T.marginAt) / 500); T.myMargin += (margin - T.myMargin) * a; } else T.myMargin = margin;
    T.marginAt = now;
    if (N.localTop() !== lastSendTop || now - lastSendAt > 30) sendInputs(now);         // new local input (normally sent by
    else if (!lastPacketRepeated && now - lastSendAt >= 8) { sendIn(lastPacket); lastPacketRepeated = true; }   // afterTick) / keep-alive; the repeat
    checkHashes();
    const waiting = !N.ready(lastRun + 1);
    if (T.state !== 'playing' && lastRun > N.cfg.delay + 1) status('playing', 'ok');
    emit('tick', { frame: lastRun, waiting, rtt: T.rtt, stalls: N.stat(8), margin: T.myMargin, peerMargin: T.peerMargin, slowed: N.stat(7) });
    if (now - T.lastRecv > 5000 && T.state !== 'idle') peerLost('no data from the other player for 5 s');
  }
  // P339 time sync, every 250 ms: the peer that is ahead (smaller input margin) slows down by half the difference
  function timeSync() {
    if (T.left || !T.peerFrame) return;
    const ahead = (T.peerMargin - T.myMargin) / 2;   // frames this peer runs ahead of the middle of the input window
    T.slowAsked = ahead > 0.3 ? Math.min(15, ahead * 20 * 0.6) : 0;
    N.M._port_net_slow(T.slowAsked);
    const now = performance.now();
    if (now - lastSyncLog > 5000) {
      lastSyncLog = now;
      const remoteNow = T.peerFrame + T.rtt / 2 / 20;   // GGPO's estimate of the other peer's retrace now
      N.log(`[net] sync: retrace ${N.frame()}, peer ~${remoteNow.toFixed(1)}, margin mine ${T.myMargin.toFixed(2)} peer ${T.peerMargin.toFixed(2)}, ` +
            `slow ${T.slowAsked.toFixed(1)} ms, slowed ${N.stat(7)} ms total, stalled ticks ${N.stat(0)}, rtt ${Math.round(T.rtt)}`);
    }
  }
  function sendIn(buf) {
    if (!T.inp || T.inp.readyState !== 'open') return;
    T.sent++;
    if (SIM.loss && Math.random() * 100 < SIM.loss) { T.simDropped++; return; }
    if (SIM.lat || SIM.jit) { setTimeout(() => { if (T.inp.readyState === 'open') T.inp.send(buf); }, (SIM.lat || 0) + Math.random() * (SIM.jit || 0)); return; }
    T.inp.send(buf);
  }
  function onPacket(buf) {
    T.recv++; T.lastRecv = performance.now();
    const dv = new DataView(buf), type = dv.getUint8(0);
    if (type === 2) { const r = new DataView(new ArrayBuffer(9)); r.setUint8(0, 3); r.setFloat64(1, dv.getFloat64(1, true), true); sendIn(r.buffer); return; }
    if (type === 3) { const r = performance.now() - dv.getFloat64(1, true); T.rtt = T.rtt ? T.rtt * 0.8 + r * 0.2 : r; return; }
    if (type !== 1) return;
    const ch = dv.getUint8(1), ack = dv.getUint32(2, true), first = dv.getUint32(6, true), count = dv.getUint8(10);
    if (ch !== T.peerCh) return;
    if (ack > T.peerAck) T.peerAck = ack;
    for (let i = 0; i < count; i++) {
      const f = first + i, v = dv.getUint32(11 + 4 * i, true);
      if (N.M && N.base.input !== undefined) N.put(f, ch, v); else T.pending.push([f, v]);
    }
    if (N.M && N.base.input !== undefined && T.recvTop) {
      const lastRun = N.frame();
      advanceRecvTop();
      if (T.recvTop > lastRun && N.ready(lastRun + 1)) N.M._port_net_kick();   // P339: no need to wait for the next tick
    }
    const o = 11 + 4 * count, hf = dv.getUint32(o, true);
    if (hf) T.peerHash.set(hf, [dv.getUint32(o + 4, true), dv.getUint32(o + 8, true)]);
    const peerFrame = dv.getUint32(o + 12, true);   // P339 time sync: newer packets only (they arrive out of order)
    if (peerFrame >= T.peerFrame) { T.peerFrame = peerFrame; T.peerMargin = dv.getInt16(o + 16, true) / 64; }
  }
  function checkHashes() {
    if (T.desync || !T.peerHash.size) return;
    for (const h of N.hashes()) {
      const p = T.peerHash.get(h.f);
      if (!p) continue;
      if (p[0] !== h.h || p[1] !== h.s) {
        T.desync = { frame: h.f, mine: [h.h, h.s], theirs: p };
        N.log(`[net] DESYNC at retrace ${h.f}: mine ${h.h.toString(16)} ${h.s.toString(16)}, peer ${p[0].toString(16)} ${p[1].toString(16)}`, 'fail');
        sendCtl({ t: 'desync', frame: h.f, mine: [h.h, h.s], theirs: p });
        emit('desync', T.desync);
        sendPages(h.f);   // P339: the per-page hashes, to name where the two games differ
        return;
      }
      if (h.f > T.myHashSeen) T.myHashSeen = h.f;
      T.peerHash.delete(h.f);
    }
    if (T.peerHash.size > 256) for (const k of [...T.peerHash.keys()].slice(0, 128)) T.peerHash.delete(k);
  }
  // the other player is gone: its controller reads neutral from the first frame I do not hold, the game goes on
  function peerLost(why) {
    if (T.left) return;
    T.left = true;
    if (N.M && N.base.input !== undefined) N.M._port_net_drop(T.peerCh, T.recvTop + 1);
    status(`${why}: controller ${T.peerCh + 1} stands still from now on`, 'bad');
    emit('left', why);
  }

  window.PortNet = N;
})();
