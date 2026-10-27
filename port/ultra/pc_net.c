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
    0 };
int port_net_flag_allowed(const char *name) {
    for (int i = 0; net_flag_whitelist[i]; i++)
        if (!strcmp(name, net_flag_whitelist[i])) return 1;
    return 0;
}

