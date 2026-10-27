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
  // ---------------------------------------------------------------- P344: the WebRTC transport, 2 to 4 players
  // (P338 / P339 built it for 2 players; P344 generalises it, docs/design/ONLINE_MULTIPLAYER.md section 10.)
  // Players: the host is player 1 (controller channel 0) and gives every guest a fixed controller slot 2..4 (channel
  // 1..3) when it makes that guest's offer. Topology: full mesh. Every pair of players has its own RTCPeerConnection
  // (a "link") with two negotiated DataChannels: 'ctl' (reliable, ordered: setup, config, bye, desync report, drops)
  // and 'in' (unordered, maxRetransmits 0: input packets, pings). Each player sends its own input to every other
  // player. A guest-guest pair whose direct link does not open (strict NATs: no TURN server is used) sends through the
  // host instead (the host relays that pair's packets: one extra hop for that pair only).
  // Signaling: only the host <-> guest offer / answer is done by the players, through a signaler (N.signal below; the
  // copy-paste codes CK1.... wrap its payloads; a room-code signaler can carry the same payloads through a server).
  // Everything after a guest's link to the host is open goes over the host's 'ctl' channels (star): the host tells the
  // guests the roster, each guest makes an offer for every higher-numbered guest and the host forwards the offers /
  // answers between them, so a player still only exchanges codes with the host.
  // Input packet (little endian): u8 type 1 | u8 sender channel | u32 ack (the newest frame of the receiver's channel
  // this sender holds without gaps) | u32 first frame | u8 count | u32 input x count | u32 hash frame | u32 H | u32 S |
  // u32 the sender's last retrace | i16 the sender's input margin of the receiver's channel x 64 (time sync).
  // Packets are made per receiver (ack, first frame and margin differ), repeat every input the receiver has not
  // acknowledged (up to 64), so a lost packet costs nothing and only a burst longer than the input delay stalls.
  // Ping: u8 2 | u8 sender | f64 time; pong: u8 3 | u8 sender | f64 time. Relay: u8 4 | u8 receiver channel | packet
  // (sent to the host, which passes the inner packet on to that receiver).
  // P339 (kept): a packet leaves as soon as a local input is sampled (pc_net.c, start of each retrace), the same packet
  // goes out a second time ~8 ms later, a keep-alive every 30 ms; a packet that brings the input a stalled game waits
  // for runs the retrace at once (pc_sched.c port_net_kick).
  // Time sync (GGPO-style frame advantage), per pair: my input margin of player p = frames of p's input I hold beyond
  // the retrace I ran (time average, ~0.5 s); p sends me its margin of my input. If p's margin of my input is larger
  // than mine of its input, I run ahead of p; every 250 ms I slow down by half the largest such difference over all
  // players (pc_net.c port_net_slow). Nobody ever speeds up.
  // Lost player (decision 6: it stands still): the coordinator (the host; if the host itself is gone, the lowest
  // remaining player) asks every remaining player for the inputs of the lost player it holds, picks F = 1 + the newest
  // frame anyone holds, sends everybody the inputs up to F - 1 and F ('drop' {neutralFrom: F}); from F that controller reads neutral everywhere
  // (pc_net.c port_net_drop). So all remaining players run the same inputs and stay in lockstep.
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

  // test aids: ?netsim=lat:80,jit:20,loss:5 delays (ms, plus 0..jit), reorders and drops this page's input packets;
  // ?netfailto=4 (player numbers, comma separated): this page's direct link to that player never connects (the ICE
  // candidates are removed from both SDPs), so the pair falls back to the host relay
  const SIM = {};
  { const m = /[?&]netsim=([^&]*)/.exec(location.search); if (m) for (const kv of decodeURIComponent(m[1]).split(',')) { const [k, v] = kv.split(':'); SIM[k] = +v || 0; } }
  const FAIL_TO = new Set(((/[?&]netfailto=([^&]*)/.exec(location.search) || [])[1] || '').split(',').filter(Boolean).map((x) => +x - 1));

  const T = N.t = {
    role: null, myCh: 0, state: 'idle', started: false,
    links: {},          // ch -> link: the RTCPeerConnection to that player
    peers: {},          // ch -> lockstep state of that player (made on first use)
    slots: {},          // host: ch -> {state: invited|connecting|joined|left|failed, why}; shown by the panel
    roster: [],         // the session's channels (host: set at start; guest: from the config)
    routes: {},         // 'a-b' -> 'direct' | 'relay' (guest-guest pairs, reported to the host after the mesh setup)
    sent: 0, recv: 0, simDropped: 0, relayed: 0, left: false, quit: false, desync: null, desyncReport: null, rtt: 0, myHashSeen: 0,
    on: {},             // event handlers set by main.js: status(text, cls), config(cfg), roster(slots), desync, desyncReport, left(ch, why), tick
  };
  const emit = (ev, ...a) => { if (T.on[ev]) try { T.on[ev](...a); } catch (e) { N.log('[net] ' + ev + ' handler: ' + e, 'fail'); } };
  const status = (s, cls) => { T.state = s; emit('status', s, cls); N.log('[net] ' + s); };
  const pn = (ch) => `player ${ch + 1}`;
  function peer(ch) {
    return T.peers[ch] || (T.peers[ch] = { ch, recvTop: 0, peerAck: 0, pending: [], hash: new Map(), myMargin: 0, peerMargin: 0,
      peerFrame: 0, marginAt: 0, rtt: 0, lastRecv: 0, lastSendTop: 0, lastSendAt: 0, lastPacket: null, repeated: true,
      lost: false, suspect: false, dropping: false });
  }
  const others = () => T.roster.filter((c) => c !== T.myCh);
  const livePeers = () => others().map(peer).filter((p) => !p.lost);
  // the coordinator of a drop: the lowest channel among me and the players that are neither lost nor silent
  const amCoordinator = () => livePeers().every((p) => p.suspect || p.dropping || p.ch > T.myCh);

  // ---- links
  function stripCandidates(sdp) { return sdp.split(/\r\n/).filter((l) => !/^a=(candidate|end-of-candidates)/.test(l)).join('\r\n'); }
  function newLink(ch) {
    const old = T.links[ch]; if (old) try { old.pc.close(); } catch (e) { /* closed */ }
    const pc = new RTCPeerConnection({ iceServers: STUN });
    const L = { ch, pc, ctl: pc.createDataChannel('ctl', { negotiated: true, id: 0 }),
      inp: pc.createDataChannel('in', { negotiated: true, id: 1, ordered: false, maxRetransmits: 0 }), open: false, noDirect: FAIL_TO.has(ch) };
    L.inp.binaryType = 'arraybuffer';
    L.ctl.onopen = () => { L.open = true; linkOpened(L); };
    L.ctl.onmessage = (e) => onCtl(JSON.parse(e.data), ch);
    L.ctl.onclose = () => { if (T.links[ch] !== L) return; L.open = false; linkClosed(L, 'the connection closed'); };
    L.inp.onmessage = (e) => onPacket(e.data);
    L.inp.onopen = () => { if (T.meshWait) T.meshWait(); };   // 'in' can open after 'ctl' (the mesh waits for both)
    pc.oniceconnectionstatechange = () => {
      const s = pc.iceConnectionState;
      N.log(`[net] ICE ${s} (${pn(ch)})`);
      if (s === 'failed' && T.links[ch] === L) linkClosed(L, 'the network path failed');
    };
    T.links[ch] = L;
    return L;
  }
  const directOpen = (ch) => { const L = T.links[ch]; return !!(L && L.open && L.inp.readyState === 'open'); };
  function gathered(pc, ms = 8000) {
    return new Promise((res) => {
      if (pc.iceGatheringState === 'complete') return res();
      const t = setTimeout(res, ms);   // use what was gathered so far
      pc.addEventListener('icegatheringstatechange', () => { if (pc.iceGatheringState === 'complete') { clearTimeout(t); res(); } });
    });
  }
  async function makeOffer(L) {
    await L.pc.setLocalDescription(await L.pc.createOffer());
    await gathered(L.pc);
    return L.noDirect ? stripCandidates(L.pc.localDescription.sdp) : L.pc.localDescription.sdp;
  }
  async function takeOffer(L, sdp) {
    await L.pc.setRemoteDescription({ type: 'offer', sdp: L.noDirect ? stripCandidates(sdp) : sdp });
    await L.pc.setLocalDescription(await L.pc.createAnswer());
    await gathered(L.pc);
    return L.noDirect ? stripCandidates(L.pc.localDescription.sdp) : L.pc.localDescription.sdp;
  }
  async function takeAnswer(L, sdp) { await L.pc.setRemoteDescription({ type: 'answer', sdp: L.noDirect ? stripCandidates(sdp) : sdp }); }

  // ---- the signaler: the host <-> guest exchange. Payloads are plain objects: offer {t: 'o', ch, sdp} (made by the host
  // for the guest slot ch), answer {t: 'a', ch, sdp} (made by that guest). N.signal works on payloads; the copy-paste
  // codes below wrap them (N.host / N.invite / N.join / N.accept). A room-code signaler (next phase) posts the same
  // payloads to a room on a server instead and calls the same three functions; nothing else depends on how they travel.
  const setSlot = (ch, state, why) => { T.slots[ch] = Object.assign(T.slots[ch] || {}, { state, why: why || '' }); emit('roster', N.slots()); };
  N.signal = {
    async offer(ch) { const L = newLink(ch); setSlot(ch, 'invited'); return { t: 'o', ch, sdp: await makeOffer(L) }; },   // host
    async answer(o) {   // guest
      T.role = 'guest'; T.myCh = o.ch || 1;
      return { t: 'a', ch: T.myCh, sdp: await takeOffer(newLink(0), o.sdp) };
    },
    async accept(a) {   // host
      const ch = a.ch || 1, L = T.links[ch];
      if (!L || L.pc.signalingState !== 'have-local-offer') throw new Error(`no open invitation for ${pn(ch)} (make a new code for that player)`);
      await takeAnswer(L, a.sdp); setSlot(ch, 'connecting');
    },
  };
  // host: start hosting; returns the offer code for player 2. sessionFn({ping, mask, pairs}) -> the session config
  N.host = async function (sessionFn) {
    T.role = 'host'; T.myCh = 0; T.sessionFn = sessionFn;
    return N.invite();
  };
  // host: the offer code for the next free slot (players 2, 3, 4)
  N.invite = async function () {
    if (T.role !== 'host') throw new Error('host first');
    if (T.room && !T.room.closed) throw new Error('a room is open: the other players join with its code (reload the page to use manual codes)');
    if (T.started) throw new Error('the game has started: no more players can join');
    const ch = [1, 2, 3].find((c) => !T.slots[c] || T.slots[c].state === 'left' || T.slots[c].state === 'failed');
    if (ch === undefined) throw new Error('4 players at most');
    status(`making the code for ${pn(ch)}…`);
    const code = await packCode(await N.signal.offer(ch));
    status(`send the code to ${pn(ch)}, then paste the answer code`, 'ok');
    return { ch, code };
  };
  // guest: takes the host's offer code, returns the answer code
  N.join = async function (code) {
    const o = await unpackCode(code);
    if (o.t !== 'o') throw new Error('this is not an offer code (paste the code the host made)');
    status('gathering network addresses…');
    const a = await N.signal.answer(o);
    status(`you are ${pn(T.myCh)}: send the answer code to player 1, then wait`, 'ok');
    return packCode(a);
  };
  // host: takes a guest's answer code (it names the guest's slot)
  N.accept = async function (code) {
    const a = await unpackCode(code);
    if (a.t !== 'a') throw new Error('this is not an answer code (paste the code the guest sent back)');
    await N.signal.accept(a);
    status(`connecting to ${pn(a.ch || 1)}…`);
    return a.ch || 1;
  };
  // ---- P345 room codes (design section 11): the same payloads as the copy-paste codes, carried by the room server
  // (port/web/netlify/functions/room, POST N.roomApi). The host makes a room and polls it every second: for each guest
  // that joined (the server gives slots 2..4 in join order) it posts N.signal.offer(ch) and, when that guest's answer
  // is there, calls N.signal.accept. A guest joins with the code, polls until its offer is there, posts
  // N.signal.answer(offer). From then on everything is peer to peer as before; the host deletes the room when the game
  // starts (or when it leaves). The server compares build id / ROM SHA-256 at join (the host still checks 'hello').
  const ROOM_POLL_MS = 1000, ROOM_GUEST_WAIT_MS = 120000;
  N.roomApi = '/api/room';
  async function roomCall(body) {
    let r, j = null;
    try { r = await fetch(N.roomApi, { method: 'POST', headers: { 'content-type': 'application/json' }, body: JSON.stringify(body), cache: 'no-store' }); }
    catch (e) { throw new Error('the room server cannot be reached (check the internet connection, or use the manual codes)'); }
    try { j = await r.json(); } catch (e) { /* not json */ }
    if (!r.ok || !j || j.error) { const e = new Error((j && j.error) || `room server error ${r.status} (try the manual codes)`); e.code = j && j.code; throw e; }
    return j;
  }
  const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
  function roomStop(close) {   // host: stop polling; close = delete the room on the server
    const R = T.room; if (!R || R.closed) return;
    R.closed = true; if (R.timer) clearInterval(R.timer);
    if (close && R.secret) roomCall({ op: 'close', code: R.code, secret: R.secret }).then(() => N.log(`[net] room ${R.code} closed`), (e) => N.log(`[net] room close: ${e.message}`));
  }
  // host: make a room for up to max players; returns the room code. sessionFn as for N.host.
  N.roomCreate = async function (sessionFn, max = 4) {
    if (T.role) throw new Error(T.role === 'host' ? 'already hosting' : 'already joined a session');
    const j = await roomCall({ op: 'create', build: N.buildId, rom: N.romSha256, max });
    T.role = 'host'; T.myCh = 0; T.sessionFn = sessionFn;
    const R = T.room = { code: j.code, secret: j.secret, max: j.max, gens: {}, accepted: {}, fails: 0 };
    status(`room ${j.code} is open: tell the other players this code`, 'ok');
    R.timer = setInterval(roomHostPoll, ROOM_POLL_MS); roomHostPoll();
    return j.code;
  };
  async function roomHostPoll() {
    const R = T.room; if (!R || R.closed || R.busy) return;
    if (T.started) return roomStop(true);
    R.busy = true;
    try {
      const j = await roomCall({ op: 'host', code: R.code, secret: R.secret });
      for (const s of j.slots) {
        if (R.closed || T.started) break;
        if (R.gens[s.ch] !== s.gen) {   // a new guest in this slot: make its offer (ICE gathering, up to 8 s)
          R.gens[s.ch] = s.gen; delete R.accepted[s.ch];
          status(`${pn(s.ch)} joined the room: making the connection offer…`);
          const o = await N.signal.offer(s.ch);
          await roomCall({ op: 'offer', code: R.code, secret: R.secret, ch: s.ch, gen: s.gen, sdp: o.sdp });
          status(`room ${R.code}: waiting for ${pn(s.ch)}'s answer…`, 'ok');
        } else if (s.answer && !R.accepted[s.ch]) {
          R.accepted[s.ch] = true;
          await N.signal.accept({ t: 'a', ch: s.ch, sdp: s.answer });
          status(`connecting to ${pn(s.ch)}…`);
        }
      }
      R.fails = 0; R.ttl = j.ttl;
    } catch (e) {
      if (e.code === 'unknown') { roomStop(false); status(`room ${R.code} has expired (rooms last 10 minutes): reload the page and make a new room`, 'bad'); }
      else if (e.code === 'gone') N.log('[net] room: ' + e.message);
      else if (++R.fails === 5) status('room server: ' + e.message, 'bad');
      else N.log('[net] room poll: ' + e.message);
    } finally { R.busy = false; }
  }
  // guest: join a room by its code; resolves with my channel once my answer is posted (the link then opens by itself)
  N.roomJoin = async function (code) {
    if (T.role) throw new Error('already in a session (reload the page to join another room)');
    code = String(code || '').toUpperCase().replace(/[\s-]+/g, '');
    if (!code) throw new Error('type the room code player 1 gave you');
    status(`joining room ${code}…`);
    const j = await roomCall({ op: 'join', code, build: N.buildId, rom: N.romSha256 });
    const R = T.room = { code, ch: j.ch, token: j.token, guest: true };
    T.role = 'guest'; T.myCh = j.ch;
    status(`in room ${code}: you are ${pn(j.ch)}, waiting for player 1…`, 'ok');
    let offer = null;
    for (const t0 = Date.now(); !offer; await sleep(ROOM_POLL_MS)) {
      if (R.closed) throw new Error('left the room');
      if (Date.now() - t0 > ROOM_GUEST_WAIT_MS) throw new Error('player 1 did not answer (is the host page still open?)');
      try { offer = (await roomCall({ op: 'guest', code, ch: j.ch, token: j.token })).offer; }
      catch (e) { if (['unknown', 'token'].includes(e.code)) throw e; N.log('[net] room poll: ' + e.message); }
    }
    status('gathering network addresses…');
    const a = await N.signal.answer({ t: 'o', ch: j.ch, sdp: offer });
    await roomCall({ op: 'answer', code, ch: j.ch, token: j.token, sdp: a.sdp });
    R.closed = true;
    status(`you are ${pn(j.ch)}: connecting to player 1…`, 'ok');
    return j.ch;
  };
  // host: the slots for the panel: [{ch, state, rtt, why, route}]
  N.slots = () => [1, 2, 3].filter((c) => T.slots[c]).map((c) => {
    const p = T.peers[c], s = T.slots[c];
    const relayPairs = Object.entries(T.routes).filter(([k, v]) => v === 'relay' && k.split('-').map(Number).includes(c)).map(([k]) => k);
    return { ch: c, state: p && p.lost ? 'left' : s.state, why: s.why, rtt: Math.round((p && p.rtt) || s.rtt || 0), relay: relayPairs };
  });
  N.leave = function () {
    T.quit = true;
    if (T.room && !T.room.guest) roomStop(true); else if (T.room) T.room.closed = true;   // P345
    for (const c of Object.keys(T.links)) try { sendCtlTo(+c, { t: 'bye' }); } catch (e) { /* closed */ }
    setTimeout(() => { for (const L of Object.values(T.links)) try { L.pc.close(); } catch (e) { /* closed */ } }, 150);
  };

  // ---- 'ctl' messages: to a player with an open link directly, else (guest) through the host
  function ctlRaw(L, obj) { if (L && L.ctl.readyState === 'open') { L.ctl.send(JSON.stringify(obj)); return true; } return false; }
  function sendCtlTo(ch, m) {
    m.from = T.myCh;
    if (ctlRaw(T.links[ch], m)) return true;
    if (T.myCh !== 0 && ch !== 0) return ctlRaw(T.links[0], { t: 'fwd', to: ch, m });
    return false;
  }
  function sendCtlSimTo(ch, m) { const ms = (SIM.lat || 0) + Math.random() * (SIM.jit || 0); if (ms) setTimeout(() => sendCtlTo(ch, m), ms); else sendCtlTo(ch, m); }
  // P339 item 2, per pair since P344: PING_COUNT pings over 'ctl' (PING_GAP_MS apart, at most PING_WAIT_MS); under
  // ?netsim the pings and pongs get the same latency / jitter as the input packets (not the loss: 'ctl' is reliable)
  const PING_COUNT = 12, PING_GAP_MS = 40, PING_WAIT_MS = 2500;
  const pingWait = {};
  function measurePing(ch, count = PING_COUNT) {
    return new Promise((resolve) => {
      const w = pingWait[ch] = { rtts: [] };
      w.finish = () => { if (pingWait[ch] !== w) return; delete pingWait[ch]; const r = w.rtts.slice().sort((a, b) => a - b);
        resolve(r.length ? { n: r.length, min: r[0], median: r[r.length >> 1], p90: r[Math.min(r.length - 1, Math.floor(r.length * 0.9))] } : null); };
      w.got = () => { if (w.rtts.length >= count) w.finish(); };
      for (let i = 0; i < count; i++) setTimeout(() => sendCtlSimTo(ch, { t: 'ping', at: performance.now() }), i * PING_GAP_MS);
      setTimeout(w.finish, PING_WAIT_MS);
    });
  }
  // D = clamp(ceil((RTT / 2 + jitter margin) / 20 ms) + 1, 2, 8): RTT = the median round trip, jitter margin = half of
  // (90th percentile - median); the + 1 covers sending / scheduling and the loss of single packets. P344: the pair
  // with the largest D decides (every player waits for every other player's input).
  N.autoDelay = (p) => p ? Math.max(2, Math.min(8, Math.ceil((p.median / 2 + (p.p90 - p.median) / 2) / 20) + 1)) : 4;

  function linkOpened(L) {
    if (T.role === 'guest' && L.ch === 0) {
      status(`connected: you are ${pn(T.myCh)}, checking the game build…`, 'ok');
      sendCtlTo(0, { t: 'hello', build: N.buildId, rom: N.romSha256 });
    } else if (T.role === 'host') setSlot(L.ch, 'connected');
    else N.log(`[net] direct link to ${pn(L.ch)} open`);
    if (T.meshWait) T.meshWait();
  }
  function linkClosed(L, why) {
    N.log(`[net] link to ${pn(L.ch)}: ${why}`);
    if (T.quit) return;
    if (!T.started && T.role === 'host') { setSlot(L.ch, T.slots[L.ch] && T.slots[L.ch].state === 'joined' ? 'left' : 'failed', why); return; }
    if (!T.started && T.role === 'guest' && L.ch === 0) {
      status(why === 'the network path failed' ? 'Could not connect: the two networks do not allow a direct connection (no relay server is used). Try another network, e.g. a phone hotspot.' : 'the host closed the connection', 'bad');
      return;
    }
    if (!T.peers[L.ch] || !T.roster.includes(L.ch)) return;
    // in a session: a guest-guest link that closes is not a lost player (the pair goes on through the host); the
    // host's link to a guest (or, without a host, the coordinator's) is the player's only path
    const p = peer(L.ch);
    if (T.myCh === 0 || L.ch === 0) p.suspect = true;
    if (amCoordinator() && (T.myCh === 0 || p.suspect)) declareLost(L.ch, why);
  }

  async function onCtl(m, linkCh) {
    const from = m.from !== undefined ? m.from : linkCh;
    if (m.t === 'fwd') {   // a message between two guests, through the host
      if (m.to === T.myCh) return onCtl(m.m, m.m.from);
      if (T.myCh === 0) ctlRaw(T.links[m.to], m.m);   // the inner message keeps its sender
      return;
    }
    if (T.peers[from]) T.peers[from].lastRecv = performance.now();
    if (m.t === 'ping') { sendCtlSimTo(from, { t: 'pong', at: m.at }); return; }
    if (m.t === 'pong') { const w = pingWait[from]; if (w) { w.rtts.push(performance.now() - m.at); w.got(); } return; }
    if (m.t === 'hello' && T.role === 'host') {   // the guest's build and ROM must be ours
      if (m.build !== N.buildId) { sendCtlTo(from, { t: 'refuse', why: 'different game builds (reload both pages to get the latest version)' }); setSlot(from, 'failed', 'different build'); status(`refused: ${pn(from)} runs a different build`, 'bad'); return; }
      if (m.rom !== N.romSha256) { sendCtlTo(from, { t: 'refuse', why: 'different ROMs (the EU ROM is needed on every side)' }); setSlot(from, 'failed', 'different ROM'); status(`refused: ${pn(from)} has a different ROM`, 'bad'); return; }
      setSlot(from, 'joined');
      sendCtlTo(from, { t: 'welcome', ch: from });
      status(`${pn(from)} joined: invite more players or start the game`, 'ok');
      const ping = await measurePing(from, 5);   // for the panel
      if (ping && T.slots[from]) { T.slots[from].rtt = ping.median; emit('roster', N.slots()); }
    } else if (m.t === 'welcome' && T.role === 'guest') status(`joined as ${pn(T.myCh)}: waiting for player 1 to start the game`, 'ok');
    else if (m.t === 'mesh' && T.role === 'guest') buildMesh(m.roster);
    else if (m.t === 'sig' && T.role === 'guest') {   // a mesh offer / answer from another guest (through the host)
      if (m.kind === 'o') { const L = newLink(from); sendCtlTo(from, { t: 'sig', kind: 'a', sdp: await takeOffer(L, m.sdp) }); }
      else if (m.kind === 'a' && T.links[from]) await takeAnswer(T.links[from], m.sdp);
    } else if (m.t === 'meshdone' && T.role === 'host') { T.meshReports[from] = m; if (T.meshWait) T.meshWait(); }
    else if (m.t === 'config' && T.role === 'guest') {
      T.myCh = m.ch; T.roster = m.roster; T.started = true; T.routes = m.routes || {};
      if (m.ping) T.rtt = m.ping;
      emit('config', { mask: m.mask, local: 1 << m.ch, delay: m.delay, autoDelay: m.autoDelay, ping: m.ping, hashEvery: m.hashEvery,
        options: m.options, eeprom: m.eeprom ? unb64(m.eeprom) : null, ch: m.ch, roster: m.roster });
    } else if (m.t === 'refuse') status('the host refused: ' + m.why, 'bad');
    else if (m.t === 'bye') {
      N.log(`[net] ${pn(from)} left the session`);
      if (!T.started) { if (T.role === 'host') setSlot(from, 'left', 'left'); else if (from === 0) status('the host left', 'bad'); return; }
      if (T.peers[from]) { peer(from).suspect = true; if (amCoordinator()) declareLost(from, `${pn(from)} left`); }
    } else if (m.t === 'lost') onLost(m, from);
    else if (m.t === 'held') onHeld(m, from);
    else if (m.t === 'drop') applyDrop(m);
    else if (m.t === 'desync') { emit('desync', Object.assign({ remote: true }, m, { ch: from })); sendPages(m.frame, from); }
    else if (m.t === 'pages') comparePages(m, from);
  }

  // ---- P344 session setup (host): mesh between the guests, pings of every pair, config
  const MESH_WAIT_MS = 8000;
  N.start = async function () {
    if (T.role !== 'host') throw new Error('only player 1 starts the game');
    const guests = [1, 2, 3].filter((c) => T.slots[c] && T.slots[c].state === 'joined');
    if (!guests.length) throw new Error('no player has joined yet');
    T.started = true;
    roomStop(true);   // P345: the room is not needed any more (nobody can join a started game)
    T.roster = [0, ...guests];
    for (const c of [1, 2, 3]) if (!guests.includes(c) && T.links[c]) { try { T.links[c].pc.close(); } catch (e) { /* closed */ } delete T.links[c]; }
    T.meshReports = {};
    if (guests.length > 1) {
      status('connecting the players to each other…', 'ok');
      for (const g of guests) sendCtlTo(g, { t: 'mesh', roster: T.roster });
      await new Promise((res) => {
        const t = setTimeout(res, MESH_WAIT_MS + 8000);
        T.meshWait = () => { if (guests.every((g) => T.meshReports[g])) { clearTimeout(t); T.meshWait = null; res(); } };
      });
      T.meshWait = null;
    }
    status('measuring the ping…', 'ok');
    const pings = {};
    await Promise.all(guests.map(async (g) => { pings['0-' + g] = await measurePing(g); }));
    for (const g of guests) {
      const r = T.meshReports[g];
      for (const h of guests) if (h > g) {
        const k = g + '-' + h, a = r && r.pings && r.pings[h], b = T.meshReports[h] && T.meshReports[h].pings && T.meshReports[h].pings[g];
        pings[k] = a && b ? (a.median >= b.median ? a : b) : a || b || null;
        const ra = r && r.links && r.links[h], rb = T.meshReports[h] && T.meshReports[h].links && T.meshReports[h].links[g];
        T.routes[k] = ra === 'direct' && rb === 'direct' ? 'direct' : 'relay';
      }
    }
    // the worst pair decides the input delay
    let worst = null, worstKey = '';
    for (const [k, p] of Object.entries(pings)) {
      N.log(`[net] ping ${k.split('-').map((c) => 'P' + (+c + 1)).join('-')}${T.routes[k] ? ' (' + T.routes[k] + ')' : ''}: ` +
            (p ? `${p.n} round trips, min ${p.min.toFixed(1)} median ${p.median.toFixed(1)} p90 ${p.p90.toFixed(1)} ms -> auto input delay ${N.autoDelay(p)}` : 'no answer'));
      if (p && (!worst || N.autoDelay(p) > N.autoDelay(worst) || (N.autoDelay(p) === N.autoDelay(worst) && p.median > worst.median))) { worst = p; worstKey = k; }
    }
    for (const g of guests) if (pings['0-' + g] && T.slots[g]) T.slots[g].rtt = pings['0-' + g].median;
    if (worst) T.rtt = worst.median;
    const mask = T.roster.reduce((m, c) => m | 1 << c, 0);
    const cfg = await T.sessionFn({ ping: worst, mask, pairs: pings, worstPair: worstKey });
    cfg.mask = mask;
    cfg.ping = worst ? Math.round(worst.median) : 0;
    for (const g of guests)
      sendCtlTo(g, { t: 'config', mask, delay: cfg.delay, autoDelay: cfg.autoDelay, ping: cfg.ping, hashEvery: cfg.hashEvery, options: cfg.options,
        eeprom: cfg.eeprom ? b64(cfg.eeprom) : null, ch: g, roster: T.roster, routes: T.routes });
    emit('roster', N.slots());
    emit('config', Object.assign({}, cfg, { local: 1, ch: 0, roster: T.roster }));
  };
  // guest: make the direct links to the other guests (the lower channel offers), then report links + pings to the host
  async function buildMesh(roster) {
    T.roster = roster;
    const mates = roster.filter((c) => c !== 0 && c !== T.myCh);
    status('connecting to the other players…', 'ok');
    await Promise.all(mates.filter((c) => c > T.myCh).map(async (c) => { const L = newLink(c); sendCtlTo(c, { t: 'sig', kind: 'o', sdp: await makeOffer(L) }); }));
    await new Promise((res) => {
      const t = setTimeout(res, MESH_WAIT_MS);
      T.meshWait = () => { if (mates.every(directOpen)) { clearTimeout(t); T.meshWait = null; res(); } };
      T.meshWait();
    });
    T.meshWait = null;
    const links = {}, pings = {};
    for (const c of mates) links[c] = directOpen(c) ? 'direct' : 'relay';
    await Promise.all(mates.map(async (c) => { pings[c] = await measurePing(c); }));
    N.log(`[net] mesh: ${mates.map((c) => `${pn(c)} ${links[c]}${pings[c] ? ' ' + pings[c].median.toFixed(1) + ' ms' : ''}`).join(', ')}`);
    sendCtlTo(0, { t: 'meshdone', links, pings });
    status('waiting for player 1 to start the game', 'ok');
  }

  // ---- P339 desync report, per pair since P344: both peers swap the per-page hashes of the desync retrace
  // (pc_nethash.c keeps the last 16 hash points: 4 KB pages of the static region + one hash per game-thread stack) and
  // name the first page that differs, with the symbols in it (conker_netsyms.txt from port/tools/net_regions.py --syms).
  const pagesSent = new Set();
  function pageVector(frame) {
    const p = N.M._port_net_page_hashes(frame) >>> 0;
    if (!p) return null;
    const n = N.M._port_net_page_info(0) + N.M._port_net_page_info(1);
    return new Uint32Array(N.M.HEAPU8.buffer.slice(p, p + 4 * n));
  }
  function sendPages(frame, ch) {
    if (!frame || pagesSent.has(frame + ':' + ch)) return;
    pagesSent.add(frame + ':' + ch);
    const v = pageVector(frame);
    if (!v) { N.log(`[net] desync report: the page hashes of retrace ${frame} are no longer kept`, 'fail'); return; }
    sendCtlTo(ch, { t: 'pages', frame, h: b64(new Uint8Array(v.buffer)) });
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
  async function comparePages(m, from) {
    const mine = pageVector(m.frame);
    sendPages(m.frame, from);   // the other side needs mine too
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
    const report = { frame: m.frame, ch: from, where, pages: diff.length, firstPages: diff.slice(0, 8), stacks };
    T.desyncReport = report;
    N.log(`[net] DESYNC REPORT retrace ${m.frame} (this game vs ${pn(from)}): ${where}; ${diff.length} page(s) differ` +
          `${diff.length ? ' [' + diff.slice(0, 8).join(' ') + (diff.length > 8 ? ' …' : '') + ']' : ''}, thread stacks ${stacks.length ? stacks.join(' ') : 'none'}`, 'fail');
    emit('desyncReport', report);
  }

  // ---- P339: a hidden page's timers (the 4 ms main loop, the pump) are throttled to ~1 Hz by Chrome, even with a live
  // WebRTC connection, and the other players would wait. While hidden, a dedicated Worker posts a message every 4 ms
  // (worker timers are not throttled); each one runs a game tick (pc_sched.c port_net_kick) and the pump.
  let hiddenTicker = null, hiddenTicks = 0;
  N.background = function (hidden) {
    if (hidden && !hiddenTicker) {
      hiddenTicker = new Worker(URL.createObjectURL(new Blob(['setInterval(() => postMessage(0), 4);'], { type: 'text/javascript' })));
      hiddenTicker.onmessage = () => { hiddenTicks++; N.M._port_net_kick(); pump(); };
    } else if (!hidden && hiddenTicker) { hiddenTicker.terminate(); hiddenTicker = null; }
    N.log(`[net] page ${hidden ? 'hidden: the game ticks from a worker timer' : 'visible again'} (retrace ${N.frame()}, ${hiddenTicks} worker ticks so far)`);
  };

  // ---- session (after N.begin): the pump sends inputs, pings, checks for lost players
  N.startTransport = function () {
    const now = performance.now();
    for (const p of livePeers()) {
      for (const [f, v] of p.pending) N.put(f, p.ch, v);
      p.pending = [];
      p.recvTop = Math.max(p.recvTop, N.cfg.delay); p.peerAck = Math.max(p.peerAck, N.cfg.delay);   // frames 1..D are neutral
      advanceRecvTop(p);
      p.lastRecv = now;
    }
    status(`waiting for the other player${others().length > 1 ? 's' : ''}`, 'ok');
    N.afterTick = () => sendInputs(performance.now());   // P339
    setInterval(pump, 5);
    setInterval(timeSync, 250);
    if (document.hidden) N.background(true);   // P339: the page was hidden before the session started
    setInterval(() => {
      for (const p of livePeers()) { const b = new DataView(new ArrayBuffer(10)); b.setUint8(0, 2); b.setUint8(1, T.myCh); b.setFloat64(2, performance.now(), true); sendIn(p.ch, b.buffer); }
    }, 1000);
  };
  function advanceRecvTop(p) { while (N.has(p.recvTop + 1, p.ch)) p.recvTop++; }
  const inSession = () => N.M && N.base.input !== undefined;
  // one input packet for player p: every local input p has not acknowledged, the ack, the newest hash, retrace, margin
  function sendInputsTo(p, now) {
    const top = N.localTop();
    const first = Math.max(p.peerAck + 1, N.cfg.delay + 1, top - 63);
    const count = Math.max(0, top - first + 1);
    const dv = new DataView(new ArrayBuffer(11 + 4 * count + 18));
    dv.setUint8(0, 1); dv.setUint8(1, T.myCh); dv.setUint32(2, p.recvTop, true); dv.setUint32(6, first, true); dv.setUint8(10, count);
    for (let i = 0; i < count; i++) dv.setUint32(11 + 4 * i, N.get(first + i, T.myCh) >>> 0, true);
    const hs = N.hashes(), h = hs[hs.length - 1] || { f: 0, h: 0, s: 0 }, o = 11 + 4 * count;
    dv.setUint32(o, h.f, true); dv.setUint32(o + 4, h.h, true); dv.setUint32(o + 8, h.s, true);
    dv.setUint32(o + 12, N.frame(), true); dv.setInt16(o + 16, Math.max(-32768, Math.min(32767, Math.round(p.myMargin * 64))), true);
    sendIn(p.ch, dv.buffer);
    p.lastSendTop = top; p.lastSendAt = now; p.lastPacket = dv.buffer; p.repeated = false;
  }
  function sendInputs(now) { if (!T.quit) for (const p of livePeers()) sendInputsTo(p, now); }
  function pump() {
    if (T.quit) return;
    const now = performance.now(), lastRun = N.frame();
    let rtt = 0;
    for (const p of livePeers()) {
      // the input margin of p, time-averaged (exponential, time constant 500 ms)
      const margin = p.recvTop - lastRun;
      if (p.marginAt) { const a = Math.min(1, (now - p.marginAt) / 500); p.myMargin += (margin - p.myMargin) * a; } else p.myMargin = margin;
      p.marginAt = now;
      if (N.localTop() !== p.lastSendTop || now - p.lastSendAt > 30) sendInputsTo(p, now);   // new local input (normally sent by
      else if (!p.repeated && now - p.lastSendAt >= 8) { sendIn(p.ch, p.lastPacket); p.repeated = true; }   // afterTick) / keep-alive; the repeat
      if (p.rtt > rtt) rtt = p.rtt;
      if (now - p.lastRecv > 5000 && !p.dropping) {
        if (!p.suspect) { p.suspect = true; N.log(`[net] no data from ${pn(p.ch)} for 5 s`); }
        if (amCoordinator()) declareLost(p.ch, `no data from ${pn(p.ch)} for 5 s`);
      }
    }
    if (rtt) T.rtt = rtt;
    checkHashes();
    const waiting = !N.ready(lastRun + 1);
    if (!T.playing && lastRun > N.cfg.delay + 1) { T.playing = true; status('playing', 'ok'); }
    const lp = livePeers();
    emit('tick', { frame: lastRun, waiting, rtt: T.rtt, stalls: N.stat(8), margin: lp.length ? Math.min(...lp.map((p) => p.myMargin)) : 0,
      slowed: N.stat(7), peers: others().map((c) => { const p = peer(c); return { ch: c, rtt: Math.round(p.rtt), lost: p.lost, waiting: !N.has(lastRun + 1, c) && !p.lost }; }) });
  }
  // P339 time sync, every 250 ms: if this peer runs ahead of any player, slow down by half the largest difference
  let lastSyncLog = 0;
  function timeSync() {
    if (T.quit) return;
    let ahead = 0;
    for (const p of livePeers()) if (p.peerFrame) ahead = Math.max(ahead, (p.peerMargin - p.myMargin) / 2);
    T.slowAsked = ahead > 0.3 ? Math.min(15, ahead * 20 * 0.6) : 0;
    N.M._port_net_slow(T.slowAsked);
    const now = performance.now();
    if (now - lastSyncLog > 5000) {
      lastSyncLog = now;
      N.log(`[net] sync: retrace ${N.frame()}, ` + livePeers().map((p) => `${pn(p.ch)} ~${(p.peerFrame + p.rtt / 2 / 20).toFixed(1)} margin mine ${p.myMargin.toFixed(2)} theirs ${p.peerMargin.toFixed(2)} rtt ${Math.round(p.rtt)}`).join('; ') +
            `, slow ${T.slowAsked.toFixed(1)} ms, slowed ${N.stat(7)} ms total, stalled ticks ${N.stat(0)}`);
    }
  }
  // an 'in' packet to player ch: directly, or (guest, no direct link) through the host
  function sendRaw(chan, buf) {
    T.sent++;
    if (SIM.loss && Math.random() * 100 < SIM.loss) { T.simDropped++; return; }
    if (SIM.lat || SIM.jit) { setTimeout(() => { if (chan.readyState === 'open') chan.send(buf); }, (SIM.lat || 0) + Math.random() * (SIM.jit || 0)); return; }
    chan.send(buf);
  }
  function sendIn(ch, buf) {
    if (directOpen(ch)) return sendRaw(T.links[ch].inp, buf);
    if (T.myCh !== 0 && ch !== 0 && directOpen(0)) {
      const w = new Uint8Array(2 + buf.byteLength); w[0] = 4; w[1] = ch; w.set(new Uint8Array(buf), 2);
      T.relayed++; sendRaw(T.links[0].inp, w.buffer);
    }
  }
  function onPacket(buf) {
    T.recv++;
    const dv = new DataView(buf), type = dv.getUint8(0);
    if (type === 4) {   // relay: for me, or (host) pass it on
      const to = dv.getUint8(1), inner = buf.slice(2);
      if (to === T.myCh) return onPacket(inner);
      if (T.myCh === 0 && directOpen(to)) { T.relayed++; sendRaw(T.links[to].inp, inner); }
      return;
    }
    const from = dv.getUint8(1);
    if (from === T.myCh || from > 3) return;
    const p = peer(from);
    if (p.lost) return;
    p.lastRecv = performance.now();
    if (type === 2) { const r = new DataView(new ArrayBuffer(10)); r.setUint8(0, 3); r.setUint8(1, T.myCh); r.setFloat64(2, dv.getFloat64(2, true), true); sendIn(from, r.buffer); return; }
    if (type === 3) { const r = performance.now() - dv.getFloat64(2, true); p.rtt = p.rtt ? p.rtt * 0.8 + r * 0.2 : r; return; }
    if (type !== 1) return;
    const ack = dv.getUint32(2, true), first = dv.getUint32(6, true), count = dv.getUint8(10);
    if (ack > p.peerAck) p.peerAck = ack;
    const on = inSession();
    for (let i = 0; i < count; i++) {
      const f = first + i, v = dv.getUint32(11 + 4 * i, true);
      if (on) N.put(f, from, v); else p.pending.push([f, v]);
    }
    if (on && p.recvTop) {
      const lastRun = N.frame();
      advanceRecvTop(p);
      if (p.recvTop > lastRun && N.ready(lastRun + 1)) N.M._port_net_kick();   // P339: no need to wait for the next tick
    }
    const o = 11 + 4 * count, hf = dv.getUint32(o, true);
    if (hf) p.hash.set(hf, [dv.getUint32(o + 4, true), dv.getUint32(o + 8, true)]);
    const peerFrame = dv.getUint32(o + 12, true);   // P339 time sync: newer packets only (they arrive out of order)
    if (peerFrame >= p.peerFrame) { p.peerFrame = peerFrame; p.peerMargin = dv.getInt16(o + 16, true) / 64; }
  }
  function checkHashes() {
    if (T.desync) return;
    const mine = N.hashes();
    for (const p of livePeers()) {
      if (!p.hash.size) continue;
      for (const h of mine) {
        const q = p.hash.get(h.f);
        if (!q) continue;
        if (q[0] !== h.h || q[1] !== h.s) {
          T.desync = { frame: h.f, mine: [h.h, h.s], theirs: q, ch: p.ch };
          N.log(`[net] DESYNC at retrace ${h.f} with ${pn(p.ch)}: mine ${h.h.toString(16)} ${h.s.toString(16)}, theirs ${q[0].toString(16)} ${q[1].toString(16)}`, 'fail');
          sendCtlTo(p.ch, { t: 'desync', frame: h.f, mine: [h.h, h.s], theirs: q });
          emit('desync', T.desync);
          sendPages(h.f, p.ch);   // P339: the per-page hashes, to name where the two games differ
          return;
        }
        if (h.f > T.myHashSeen) T.myHashSeen = h.f;
        p.hash.delete(h.f);
      }
      if (p.hash.size > 256) for (const k of [...p.hash.keys()].slice(0, 128)) p.hash.delete(k);
    }
  }

  // ---- P344 lost player: every remaining player must run the same inputs, so the coordinator collects what everyone
  // holds of the lost player's input and fixes F (see the top of this section)
  function heldOf(ch) {   // the lost player's inputs this page holds (contiguous up to recvTop; the ring keeps 256 frames)
    const p = peer(ch), v = [], first = Math.max(N.cfg.delay + 1, p.recvTop - 200);
    for (let f = first; f <= p.recvTop; f++) v.push(N.get(f, ch));
    return { ch, top: p.recvTop, first, v };
  }
  function declareLost(ch, why) {
    const p = peer(ch);
    if (p.lost || p.dropping || !inSession()) return;
    p.dropping = true;
    N.log(`[net] ${pn(ch)} lost (${why}): collecting the inputs every player holds`);
    const ask = livePeers().filter((q) => q.ch !== ch && !q.suspect);
    T.drop = { ch, why, held: [heldOf(ch)], wait: new Set(ask.map((q) => q.ch)) };
    for (const q of ask) sendCtlTo(q.ch, { t: 'lost', ch });
    T.drop.timer = setTimeout(finishDrop, 2500);
    if (!ask.length) finishDrop();
  }
  function onLost(m) { const p = peer(m.ch); p.dropping = true; p.suspect = true; sendCtlTo(m.from, Object.assign({ t: 'held' }, heldOf(m.ch))); }
  function onHeld(m, from) {
    const d = T.drop;
    if (!d || d.ch !== m.ch) return;
    d.held.push(m); d.wait.delete(from);
    if (!d.wait.size) finishDrop();
  }
  function finishDrop() {
    const d = T.drop;
    if (!d || d.done) return;
    d.done = true; clearTimeout(d.timer);
    const neutralFrom = Math.max(...d.held.map((h) => h.top)) + 1, first = Math.min(...d.held.map((h) => h.first)), v = [];
    for (let f = first; f < neutralFrom; f++) {
      let x = -1;
      for (const h of d.held) if (f >= h.first && f <= h.top && h.v[f - h.first] !== -1) { x = h.v[f - h.first]; break; }
      v.push(x);
    }
    const m = { t: 'drop', ch: d.ch, neutralFrom, first, v, why: d.why };   // ('from' is the sender of every 'ctl' message)
    for (const q of livePeers()) if (q.ch !== d.ch) sendCtlTo(q.ch, Object.assign({}, m));
    applyDrop(m);
  }
  function applyDrop(m) {
    const p = peer(m.ch);
    if (p.lost) return;
    for (let i = 0; i < m.v.length; i++) if (m.v[i] !== -1) N.put(m.first + i, m.ch, m.v[i]);
    advanceRecvTop(p);
    N.M._port_net_drop(m.ch, m.neutralFrom);
    p.lost = true;
    if (T.slots[m.ch]) setSlot(m.ch, 'left', m.why);
    T.left = livePeers().length === 0;
    status(`${m.why || pn(m.ch) + ' left'}: controller ${m.ch + 1} stands still from retrace ${m.neutralFrom}`, 'bad');
    emit('left', m.ch, m.why);
    if (N.ready(N.frame() + 1)) N.M._port_net_kick();
  }

  window.PortNet = N;
})();
