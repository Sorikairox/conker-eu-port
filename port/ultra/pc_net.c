/* P337: online multiplayer, phase 0 (docs/design/ONLINE_MULTIPLAYER.md): the determinism harness.
 * Everything here is inert unless a test flag is given; the normal game never takes these paths.
 *
 * 1. Forced online determinism: ?netdet=1 (node PORT_NETDET=1), later the online boot (port_net_force_det() before
 *    callMain). It pins the design's nondeterminism sources:
 *      - port_flag("det") reads 2: the det clock (pc_os.c det_now), no 40 ms frame budget (pc_sched.c port_sched_run),
 *        the virtual AI queue (aud_out.c det_vq), the wall-paced 50 Hz VI kept (pc_sched.c frame mode 1);
 *      - every other URL / environment flag reads 0, except the whitelist below (test tools that are part of the
 *        session, or logging that never writes game state);
 *      - the page (main.js) writes no pad state, sends the default options vector once and never again, and boots
 *        with a blank EEPROM that is never persisted; pc_pif.c suppresses the EEPROM dirty callback;
 *      - controller presence comes from ?padmask (pc_pif.c), the same on every peer.
 * 2. (pc_nethash.c) Per-retrace state hash: ?nethash=F logs "[nethash] N H S" from retrace F on (H = hashed static memory, S = the game
 *    threads' fiber stacks; port_net_retrace_end). Memory hashed: the wasm static region (rodata + data + bss:
 *    __global_base .. __data_end, which holds the n64_rdram / n64_seg16 mirrors and every C global) minus the port-only
 *    ranges the page loads from conker_netx.txt (port/tools/net_regions.py, from the linker map), minus RDRAM ranges the
 *    renderer wrote from GPU read-backs (port_net_gpu_write); plus the fiber C / asyncify stacks of the game threads.
 *    ?nethashstop=N pauses the game right after retrace N so the page can dump the memory (window.__netdump).
 * 3. (pc_nethash.c) Measurements: ?netprof=1 logs the retrace cost (all, gfx task, audio task) every 250 retraces;
 *    ?netsnap=1 keeps a shadow copy of the hashed memory and logs changed pages / bytes per retrace and the
 *    save / restore cost of a full snapshot; ?netnogfx=1 skips the gfx task (resimulation without rendering).
 *    ?netgpujunk=1 fills the renderer's RDRAM write-backs with a pattern instead of the GPU pixels (proves game
 *    logic never reads them as data). */
#include <emscripten.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void port_log(const char *fmt, ...);
int port_flag(const char *name);
extern unsigned port_frame_count;



/* ---------------- 1. forced online determinism ---------------- */
EM_JS(int, __port_net_det_js, (void), {
    if (typeof location !== 'undefined') return /[?&]netdet(=1)?(&|$)/.test(location.search) ? 1 : 0;
    if (typeof process !== 'undefined' && process.env && process.env.PORT_NETDET) return 1;
    return 0;
});
static int net_det_on = -1;
int port_net_det(void) { if (net_det_on < 0) net_det_on = __port_net_det_js(); return net_det_on; }
/* phase 1: the online boot calls this before callMain instead of using the URL flag */
EMSCRIPTEN_KEEPALIVE void port_net_force_det(void) { net_det_on = 1; }

/* Flags still read under net det. "det" is answered by port_flag itself (2). padf / padf1..3 / padmask are the session's
 * input script and presence mask (pc_pif.c reads padf* directly); the others only log or pace the main loop. */
static const char *const net_flag_whitelist[] = {
    "netdet", "nethash", "nethashstop", "netprof", "netsnap", "netnogfx", "netgpujunk", "padmask",
    "timer",       /* main-loop pacing (setTimeout period): wall speed only, retraces stay input-indexed */
    "p103boot",    /* mode / level change log */
    "padlog",      /* pad log line limit */
    "netscript",   /* P338 test session: the local input comes from the ?padf scripts */
    0 };
int port_net_flag_allowed(const char *name) {
    for (int i = 0; net_flag_whitelist[i]; i++)
        if (!strcmp(name, net_flag_whitelist[i])) return 1;
    return 0;
}


/* ---------------- 4. the lockstep session (P338, phase 1) ----------------
 * Every peer runs the same retraces with the same inputs. Retrace N reads, for every channel of the session, the input
 * stored for frame N in the ring below; pc_sched.c frame() runs retrace N only when port_net_ready(N) (the frame
 * barrier). The local player's input for frame N + D is sampled at the start of retrace N (input delay D retraces),
 * from the page's local pad (port_net_addr(3), written by main.js like port_pads today) or, in a test session
 * (?netscript=1), from the channel's ?padf script. Frames 1..D are neutral for everyone. The page (net.js) reads the
 * local entries out of the ring after each tick and sends them; it writes the peers' entries in as they arrive.
 * Packed input: buttons << 16 | (u8)stick_x << 8 | (u8)stick_y. All of this lives in pc_net.o, which the state hash
 * leaves out (port/tools/net_regions.py), so peers whose ring timing differs still hash the same. */
#define NET_RING 256              /* frames; the page never runs more than D + 32 frames ahead of the slowest peer */
#define NET_HASHES 64             /* the last 64 desync-check hashes */
static struct {
    uint32_t input[NET_RING][4];  /* packed input of frame f in slot f % NET_RING, per channel */
    uint32_t frame[NET_RING][4];  /* the frame the slot holds (0 = empty) */
    uint32_t hash[NET_HASHES][3]; /* {retrace, H, S} every net_hash_every retraces, slot (retrace / every) % NET_HASHES */
    int32_t local_pad[4];         /* the page's local pad: present, buttons, stick x, stick y */
    uint32_t stat[8];             /* see port_net_addr */
} net;
int port_net_on;                  /* a session runs: pc_sched.c barrier, pc_pif.c input source */
static int net_mask;              /* channels in the session (= presence mask) */
static int net_local_mask;        /* channels whose input this peer produces */
static unsigned net_delay = 3;    /* D */
static unsigned net_drop_from[4]; /* a lost player's channel reads neutral from this frame on (0 = not dropped) */
static int net_hash_every = 10;
static int net_script;            /* ?netscript=1: local input from the ?padf script (tests) */

void port_padf_value(int ch, unsigned frame, int *buttons, int *stick_x, int *stick_y);   /* pc_pif.c */
void port_pads_set_mask(int mask);                                                         /* pc_pif.c */
void port_net_hash_now(uint32_t *hash_static, uint32_t *hash_stacks);                      /* pc_nethash.c */
static uint32_t net_pack(int buttons, int stick_x, int stick_y) {
    return ((uint32_t)buttons & 0xFFFF) << 16 | (uint32_t)(uint8_t)(int8_t)stick_x << 8 | (uint8_t)(int8_t)stick_y;
}

/* Called by the page before callMain. present_mask = channels in the session (bit i = controller i + 1, the game sees
 * exactly these plugged in), local_mask = the channels this peer feeds, delay = D (>= 1), hash_every = K (0 = no hash).
 * It also forces online determinism (section 1). */
EMSCRIPTEN_KEEPALIVE void port_net_session(int present_mask, int local_mask, int delay, int hash_every) {
    port_net_force_det();
    port_net_on = 1;
    net_mask = present_mask & 0xF;
    net_local_mask = local_mask & net_mask;
    net_delay = delay < 1 ? 1 : delay > 32 ? 32 : (unsigned)delay;
    net_hash_every = hash_every < 0 ? 0 : hash_every;
    net_script = port_flag("netscript") > 0;
    port_pads_set_mask(net_mask);
    port_log("[net] session: channels %X, local %X, input delay %u, hash every %d retraces%s\n", net_mask, net_local_mask,
             net_delay, net_hash_every, net_script ? ", local input from the ?padf scripts" : "");
}
/* 0 = input ring (u32 [256][4]), 1 = frame tags (u32 [256][4]), 2 = hash ring (u32 [64][3]), 3 = local pad (s32 [4]),
 * 4 = stats (u32 [8]: 0 stalled ticks, 1 stalled retrace slots, 2 last retrace run, 3 input delay, 4 hash every K,
 *     5 channel mask, 6 local mask) */
EMSCRIPTEN_KEEPALIVE uintptr_t port_net_addr(int which) {
    net.stat[2] = port_frame_count; net.stat[3] = net_delay; net.stat[4] = (uint32_t)net_hash_every;
    net.stat[5] = (uint32_t)net_mask; net.stat[6] = (uint32_t)net_local_mask;
    switch (which) {
    case 0: return (uintptr_t)net.input; case 1: return (uintptr_t)net.frame; case 2: return (uintptr_t)net.hash;
    case 3: return (uintptr_t)net.local_pad; default: return (uintptr_t)net.stat;
    }
}
EMSCRIPTEN_KEEPALIVE unsigned port_net_frame(void) { return port_frame_count; }   /* the last retrace run */
/* a hidden tab gets no requestAnimationFrame: the page switches the main loop to a 10 ms timer while hidden, so the
 * session does not stall for the other player (browsers may still slow timers in background tabs) */
EMSCRIPTEN_KEEPALIVE void port_net_background(int hidden) {
    if (hidden) emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 10);
    else emscripten_set_main_loop_timing(EM_TIMING_RAF, 1);
}
/* the page's loopback peer and tests: the ?padf script's packed input of a channel at a frame */
EMSCRIPTEN_KEEPALIVE uint32_t port_net_script_input(int ch, unsigned frame) {
    int b, x, y;
    port_padf_value(ch & 3, frame, &b, &x, &y);
    return net_pack(b, x, y);
}
/* a lost player: its channel reads neutral input from `from_frame` on (all peers must agree on the frame) */
EMSCRIPTEN_KEEPALIVE void port_net_drop(int ch, unsigned from_frame) {
    net_drop_from[ch & 3] = from_frame ? from_frame : 1;
    port_log("[net] channel %d neutral from retrace %u (player left)\n", ch & 3, from_frame);
}

static int net_has(unsigned f, int ch) {
    return f <= net_delay || (net_drop_from[ch] && f >= net_drop_from[ch]) || net.frame[f % NET_RING][ch] == f;
}
/* the frame barrier (pc_sched.c frame): may retrace f run? */
EMSCRIPTEN_KEEPALIVE int port_net_ready(unsigned f) {
    for (int ch = 0; ch < 4; ch++)
        if ((net_mask >> ch & 1) && !net_has(f, ch)) return 0;
    return 1;
}
void port_net_stalled(int slots) { net.stat[0]++; net.stat[1] += (uint32_t)slots; }

/* start of retrace N (pc_sched.c retrace): sample the local input for frame N + D */
void port_net_retrace_start(void) {
    unsigned f = port_frame_count + net_delay, slot = f % NET_RING;
    for (int ch = 0; ch < 4; ch++) {
        if (!(net_local_mask >> ch & 1)) continue;
        int b = net.local_pad[1], x = net.local_pad[2], y = net.local_pad[3];
        if (net_script) port_padf_value(ch, f, &b, &x, &y);
        net.input[slot][ch] = net_pack(b, x, y);
        net.frame[slot][ch] = f;
    }
}
/* pc_pif.c osContStartReadData: this retrace's buttons / sticks for every session channel ([present, b, x, y] x 4) */
void port_net_fill_pads(int32_t *pads) {
    unsigned f = port_frame_count, slot = f % NET_RING;
    for (int ch = 0; ch < 4; ch++) {
        if (!(net_mask >> ch & 1)) continue;
        uint32_t v = f > net_delay && !(net_drop_from[ch] && f >= net_drop_from[ch]) && net.frame[slot][ch] == f ? net.input[slot][ch] : 0;
        pads[ch * 4 + 1] = (int32_t)(v >> 16); pads[ch * 4 + 2] = (int8_t)(v >> 8); pads[ch * 4 + 3] = (int8_t)v;
    }
}
/* end of retrace N: the desync-check hash every K retraces */
void port_net_retrace_done(void) {
    if (net_hash_every <= 0 || port_frame_count % (unsigned)net_hash_every) return;
    uint32_t *e = net.hash[(port_frame_count / (unsigned)net_hash_every) % NET_HASHES];
    port_net_hash_now(&e[1], &e[2]);
    e[0] = port_frame_count;
}
