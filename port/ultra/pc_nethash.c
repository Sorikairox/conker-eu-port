/* P337: online multiplayer phase 0, part 2: per-retrace state hash and the rollback measurements. The overview of the
 * harness (flags, what is hashed and why) is at the top of pc_net.c. Inert unless ?nethash / ?nethashstop / ?netprof /
 * ?netsnap is given: pc_sched.c retrace() calls the hooks only when port_net_hooks is set. */
#include <emscripten.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void port_log(const char *fmt, ...);
int port_flag(const char *name);
int port_net_det(void);
extern unsigned port_frame_count;
void port_set_paused(int p);
int port_sched_stack(int i, void **cstack, unsigned *clen, void **astack, unsigned *alen); /* pc_sched.c */
extern int port_net_hooks;

/* ---------------- 2. state hash ---------------- */
extern unsigned char __global_base, __data_end;   /* wasm-ld: start of static data (GLOBAL_BASE) and end of bss */
#define NET_PAGE 4096u
#define NET_MAX_EXCL 1024
#define NET_MAX_GPU 32
static struct { uintptr_t a, b; } net_excl[NET_MAX_EXCL];   /* [a, b) static ranges from conker_netx.txt */
static int net_nexcl, net_excl_sorted;
static struct { uintptr_t a, b; } net_gpu[NET_MAX_GPU];      /* RDRAM ranges written from GPU pixels */
static int net_ngpu;
/* the page loads conker_netx.txt (port/tools/net_regions.py) through this before callMain */
EMSCRIPTEN_KEEPALIVE void port_net_exclude(unsigned addr, unsigned len) {
    if (net_nexcl < NET_MAX_EXCL && len) { net_excl[net_nexcl].a = addr; net_excl[net_nexcl].b = addr + len; net_nexcl++; net_excl_sorted = 0; }
}
static int net_gpujunk = -1;
/* gfx_f3dex2.c: the renderer is about to write len bytes of GPU pixels into game memory at p (off_writeback P137,
 * fbc_check_timg P161). Returns 1 when ?netgpujunk asks for a fixed pattern instead of the pixels. */
int port_net_gpu_write(void *p, unsigned len) {
    uintptr_t a = (uintptr_t)p, b = a + len;
    int i;
    for (i = 0; i < net_ngpu; i++) if (net_gpu[i].a == a && net_gpu[i].b == b) break;
    if (i == net_ngpu && net_ngpu < NET_MAX_GPU) {
        net_gpu[net_ngpu].a = a; net_gpu[net_ngpu].b = b; net_ngpu++;
        if (port_net_hooks) port_log("[nethash] retrace %u: GPU write-back range %08X +%X excluded from the hash\n", port_frame_count, (unsigned)a, len);
    }
    if (net_gpujunk < 0) net_gpujunk = port_flag("netgpujunk");
    return net_gpujunk > 0;
}

/* included segments of the static region: [global_base, data_end) minus net_excl, built once */
#define NET_MAX_SEG (NET_MAX_EXCL + 2)
static struct { uintptr_t a, b; } net_seg[NET_MAX_SEG];
static int net_nseg;
static uint64_t *net_page_hash;     /* per 4 KB page of the static region (for the changed-page count) */
static unsigned net_npages;
static int net_hash_from = -1, net_stop_at = -1, net_prof = -1, net_snap = -1;
static int excl_cmp(const void *x, const void *y) {
    uintptr_t a = *(const uintptr_t *)x, b = *(const uintptr_t *)y;
    return a < b ? -1 : a > b;
}
static void net_build_segments(void) {
    uintptr_t lo = (uintptr_t)&__global_base, hi = (uintptr_t)&__data_end, at = lo;
    qsort(net_excl, net_nexcl, sizeof net_excl[0], excl_cmp);
    net_excl_sorted = 1; net_nseg = 0;
    for (int i = 0; i < net_nexcl && net_nseg < NET_MAX_SEG - 1; i++) {
        uintptr_t a = net_excl[i].a < lo ? lo : net_excl[i].a, b = net_excl[i].b > hi ? hi : net_excl[i].b;
        if (b <= at) continue;
        if (a > at) { net_seg[net_nseg].a = at; net_seg[net_nseg].b = a; net_nseg++; }
        at = b;
    }
    if (at < hi) { net_seg[net_nseg].a = at; net_seg[net_nseg].b = hi; net_nseg++; }
    net_npages = (unsigned)((hi - lo + NET_PAGE - 1) / NET_PAGE);
    net_page_hash = calloc(net_npages, sizeof *net_page_hash);
    uintptr_t n = 0; for (int i = 0; i < net_nseg; i++) n += net_seg[i].b - net_seg[i].a;
    port_log("[nethash] static region %08X..%08X (%u KB), %d exclusions, %d included segments (%u KB), %u pages\n",
             (unsigned)lo, (unsigned)hi, (unsigned)((hi - lo) >> 10), net_nexcl, net_nseg, (unsigned)(n >> 10), net_npages);
}
/* 64-bit multiply-xorshift over bytes [a, b), word-wise where aligned */
static uint64_t net_mix(uint64_t h, const unsigned char *a, const unsigned char *b) {
    const uint64_t K = 0x9E3779B97F4A7C15ull;
    while (a < b && ((uintptr_t)a & 7)) { h = (h ^ *a++) * K; h ^= h >> 29; }
    for (; a + 8 <= b; a += 8) { uint64_t w; memcpy(&w, a, 8); h = (h ^ w) * K; h ^= h >> 29; }
    while (a < b) { h = (h ^ *a++) * K; h ^= h >> 29; }
    return h;
}
static int net_in_gpu(uintptr_t a, uintptr_t b, uintptr_t *cut_a, uintptr_t *cut_b) {
    for (int i = 0; i < net_ngpu; i++)
        if (net_gpu[i].a < b && net_gpu[i].b > a) { *cut_a = net_gpu[i].a; *cut_b = net_gpu[i].b; return 1; }
    return 0;
}
/* hash of [a, b) minus the GPU write-back ranges */
static uint64_t net_mix_range(uint64_t h, uintptr_t a, uintptr_t b) {
    uintptr_t ca, cb;
    while (a < b && net_in_gpu(a, b, &ca, &cb)) {
        if (ca > a) h = net_mix(h, (const unsigned char *)a, (const unsigned char *)ca);
        a = cb;
    }
    if (a < b) h = net_mix(h, (const unsigned char *)a, (const unsigned char *)b);
    return h;
}
static unsigned net_changed_pages;
static uint64_t net_hash_static(void) {
    uintptr_t lo = (uintptr_t)&__global_base;
    uint64_t total = 0x243F6A8885A308D3ull;
    unsigned changed = 0;
    int s = 0;
    for (unsigned pg = 0; pg < net_npages; pg++) {
        uintptr_t pa = lo + (uintptr_t)pg * NET_PAGE, pb = pa + NET_PAGE;
        uint64_t h = pg;
        while (s < net_nseg && net_seg[s].b <= pa) s++;
        for (int k = s; k < net_nseg && net_seg[k].a < pb; k++) {
            uintptr_t a = net_seg[k].a > pa ? net_seg[k].a : pa, b = net_seg[k].b < pb ? net_seg[k].b : pb;
            if (a < b) h = net_mix_range(h, a, b);
        }
        if (h != net_page_hash[pg]) { changed++; net_page_hash[pg] = h; }
        total = (total ^ h) * 0x9E3779B97F4A7C15ull; total ^= total >> 31;
    }
    net_changed_pages = changed;
    return total;
}
static uint64_t net_hash_stacks(unsigned *bytes) {
    uint64_t h = 0x13198A2E03707344ull; unsigned n = 0;
    void *cs, *as; unsigned cl, al;
    for (int i = 0; port_sched_stack(i, &cs, &cl, &as, &al) >= 0; i++) {
        if (!cs) continue;
        h = net_mix(h ^ (uint64_t)i, cs, (const unsigned char *)cs + cl);
        h = net_mix(h, as, (const unsigned char *)as + al);
        n += cl + al;
    }
    *bytes = n;
    return h;
}

/* ---------------- 3. measurements ---------------- */
int port_net_hooks;          /* pc_sched.c retrace() calls the begin / end hooks only when set (one test per retrace) */
int port_net_nogfx = -1;     /* pc_os.c osSpTaskStartGo: skip the gfx task (?netnogfx) */
double port_net_task_ms[2];  /* pc_os.c: gfx / audio task time in the current retrace (?netprof) */
static double net_t_begin;
static struct { unsigned n; double all, all_max, gfx, aud, hash; double v[250]; } np;
static unsigned char *net_shadow;   /* ?netsnap: copy of the included static segments + stacks */
static size_t net_shadow_len;
static struct { unsigned n; double save, restore, save_max, restore_max; unsigned long long bytes, pages; unsigned bytes_max, pages_max; } ns;
static int dcmp(const void *x, const void *y) { double a = *(const double *)x, b = *(const double *)y; return a < b ? -1 : a > b; }
static void net_prof_report(void) {
    if (!np.n) return;
    qsort(np.v, np.n, sizeof np.v[0], dcmp);
    port_log("[netprof] retraces %u..%u: retrace %.2f ms mean (p50 %.2f, p95 %.2f, max %.2f), gfx task %.2f, audio task %.2f, "
             "rest (game + scheduler) %.2f, hash %.2f ms\n", port_frame_count - np.n + 1, port_frame_count,
             np.all / np.n, np.v[np.n / 2], np.v[np.n * 95 / 100], np.all_max, np.gfx / np.n, np.aud / np.n,
             (np.all - np.gfx - np.aud) / np.n, np.hash / np.n);
    memset(&np, 0, sizeof np);
}
static size_t net_snap_regions(int restore) {   /* copy in (save) or out (restore) of the shadow; returns bytes */
    size_t o = 0;
    for (int i = 0; i < net_nseg; i++) {
        size_t n = net_seg[i].b - net_seg[i].a;
        if (restore) memcpy((void *)net_seg[i].a, net_shadow + o, n); else memcpy(net_shadow + o, (void *)net_seg[i].a, n);
        o += n;
    }
    void *cs, *as; unsigned cl, al;
    for (int i = 0; port_sched_stack(i, &cs, &cl, &as, &al) >= 0; i++) {
        if (!cs) continue;
        if (restore) { memcpy(cs, net_shadow + o, cl); memcpy(as, net_shadow + o + cl, al); }
        else { memcpy(net_shadow + o, cs, cl); memcpy(net_shadow + o + cl, as, al); }
        o += cl + al;
    }
    return o;
}
static unsigned net_count_changed_bytes(void) {   /* before the save: bytes that differ from the last snapshot */
    size_t o = 0; unsigned d = 0;
    for (int i = 0; i < net_nseg; i++) {
        const unsigned char *p = (const unsigned char *)net_seg[i].a; size_t n = net_seg[i].b - net_seg[i].a;
        for (size_t k = 0; k < n; k++) d += p[k] != net_shadow[o + k];
        o += n;
    }
    return d;
}
static void net_snap_step(void) {
    unsigned stk; void *cs, *as; unsigned cl, al;
    if (!net_shadow) {
        size_t n = 0;
        for (int i = 0; i < net_nseg; i++) n += net_seg[i].b - net_seg[i].a;
        net_hash_stacks(&stk); n += stk + (4u << 20);   /* room for threads created later */
        net_shadow = malloc(n); net_shadow_len = n;
        port_log("[netsnap] shadow of %u KB (static %u KB + stacks %u KB)\n", (unsigned)(n >> 10), (unsigned)((n - stk - (4u << 20)) >> 10), stk >> 10);
        net_snap_regions(0);
        return;
    }
    (void)cs; (void)as; (void)cl; (void)al;
    unsigned d = net_count_changed_bytes();
    double t0 = emscripten_get_now();
    size_t len = net_snap_regions(0);
    double t1 = emscripten_get_now();
    net_snap_regions(1);   /* restore the snapshot just taken: same bytes, so harmless, and timed like a real rollback */
    double t2 = emscripten_get_now();
    ns.n++; ns.save += t1 - t0; ns.restore += t2 - t1; ns.bytes += d; ns.pages += net_changed_pages;
    if (t1 - t0 > ns.save_max) ns.save_max = t1 - t0;
    if (t2 - t1 > ns.restore_max) ns.restore_max = t2 - t1;
    if (d > ns.bytes_max) ns.bytes_max = d;
    if (net_changed_pages > ns.pages_max) ns.pages_max = net_changed_pages;
    if (ns.n == 250) {
        port_log("[netsnap] retraces %u..%u: snapshot %u KB, save %.2f ms mean (max %.2f), restore %.2f ms (max %.2f); changed per retrace: "
                 "%llu bytes mean (max %u) in %llu of %u static pages mean (max %u)\n", port_frame_count - 249, port_frame_count,
                 (unsigned)(len >> 10), ns.save / ns.n, ns.save_max, ns.restore / ns.n, ns.restore_max, ns.bytes / ns.n, ns.bytes_max,
                 ns.pages / ns.n, net_npages, ns.pages_max);
        memset(&ns, 0, sizeof ns);
    }
}

/* ---------------- retrace hooks (pc_sched.c retrace) ---------------- */
void port_net_init(void) {   /* pc_sched.c port_run, before boot */
    net_hash_from = port_flag("nethash");
    net_stop_at = port_flag("nethashstop");
    net_prof = port_flag("netprof");
    net_snap = port_flag("netsnap");
    port_net_nogfx = port_flag("netnogfx");
    port_net_hooks = net_hash_from > 0 || net_stop_at > 0 || net_prof > 0 || net_snap > 0;
    if (port_net_det()) port_log("[netdet] forced online determinism: det clock, no frame budget, virtual AI queue, flags whitelisted\n");
    if (port_net_hooks) port_log("[nethash] from %d, stop %d, prof %d, snap %d, nogfx %d\n", net_hash_from, net_stop_at, net_prof, net_snap, port_net_nogfx);
}
void port_net_retrace_begin(void) {
    port_net_task_ms[0] = port_net_task_ms[1] = 0;
    if (net_prof > 0) net_t_begin = emscripten_get_now();
}
void port_net_retrace_end(void) {
    double t_end = net_prof > 0 ? emscripten_get_now() : 0;
    if (!net_page_hash) net_build_segments();
    if ((net_hash_from > 0 && port_frame_count >= (unsigned)net_hash_from) || net_snap > 0) {
        unsigned stk;
        uint64_t h = net_hash_static(), s = net_hash_stacks(&stk);
        if (net_hash_from > 0 && port_frame_count >= (unsigned)net_hash_from)
            port_log("[nethash] %u %08X%08X %08X%08X\n", port_frame_count, (unsigned)(h >> 32), (unsigned)h, (unsigned)(s >> 32), (unsigned)s);
    }
    if (net_snap > 0) net_snap_step();
    if (net_prof > 0) {
        double ms = t_end - net_t_begin;
        np.v[np.n++] = ms; np.all += ms; if (ms > np.all_max) np.all_max = ms;
        np.gfx += port_net_task_ms[0]; np.aud += port_net_task_ms[1]; np.hash += emscripten_get_now() - t_end;
        if (np.n == 250) net_prof_report();
    }
    if (net_stop_at > 0 && port_frame_count == (unsigned)net_stop_at) {
        port_log("[nethash] stopped after retrace %u (window.__netdump)\n", port_frame_count);
        port_set_paused(1);
    }
}

/* the regions the page dumps at the stop: 0 = static region, then per thread slot its C stack and its asyncify stack.
 * port_net_region(i, 0) = address, (i, 1) = length (0 for a free slot); -1 past the last region. */
EMSCRIPTEN_KEEPALIVE int port_net_region(int i, int want_len) {
    if (i == 0) return want_len ? (int)((uintptr_t)&__data_end - (uintptr_t)&__global_base) : (int)(uintptr_t)&__global_base;
    void *cs, *as; unsigned cl, al;
    if (port_sched_stack((i - 1) >> 1, &cs, &cl, &as, &al) < 0) return -1;
    if ((i - 1) & 1) return want_len ? (int)al : (int)(uintptr_t)as;
    return want_len ? (int)cl : (int)(uintptr_t)cs;
}

/* P338: the online session's desync check (pc_net.c port_net_retrace_done, every K retraces): the same H / S hashes as
 * ?nethash, folded to 32 bits each. */
/* P339 desync report: every session hash also keeps the per-page hashes of the static region (4 KB pages, folded to
 * 32 bits) and one hash per game-thread stack, for the last NET_PAGE_RING hash points. After a desync both peers swap
 * the vector of the reported retrace (net.js) and name the first page that differs (the symbols in it come from
 * conker_netsyms.txt, port/tools/net_regions.py --syms). */
#define NET_PAGE_RING 16
#define NET_STACK_SLOTS 32
static uint32_t *net_page_ring;                    /* [NET_PAGE_RING][net_npages + NET_STACK_SLOTS] */
static uint32_t net_page_ring_frame[NET_PAGE_RING];
static unsigned net_page_ring_next;
void port_net_hash_now(uint32_t *hash_static, uint32_t *hash_stacks) {
    unsigned stk;
    if (!net_page_hash) net_build_segments();
    uint64_t h = net_hash_static(), s = net_hash_stacks(&stk);
    *hash_static = (uint32_t)(h ^ (h >> 32));
    *hash_stacks = (uint32_t)(s ^ (s >> 32));
    if (!net_page_ring) net_page_ring = calloc((size_t)NET_PAGE_RING * (net_npages + NET_STACK_SLOTS), sizeof *net_page_ring);
    if (!net_page_ring) return;
    unsigned slot = net_page_ring_next++ % NET_PAGE_RING;
    uint32_t *row = net_page_ring + (size_t)slot * (net_npages + NET_STACK_SLOTS);
    for (unsigned pg = 0; pg < net_npages; pg++) row[pg] = (uint32_t)(net_page_hash[pg] ^ (net_page_hash[pg] >> 32));
    void *cs, *as; unsigned cl, al;
    for (int i = 0; i < NET_STACK_SLOTS; i++) {
        uint64_t t = 0;
        if (port_sched_stack(i, &cs, &cl, &as, &al) >= 0 && cs)
            t = net_mix(net_mix(0x13198A2E03707344ull ^ (uint64_t)i, cs, (const unsigned char *)cs + cl), as, (const unsigned char *)as + al);
        row[net_npages + i] = (uint32_t)(t ^ (t >> 32));
    }
    net_page_ring_frame[slot] = port_frame_count;
}
/* the page / stack hashes of a retrace still in the ring (u32 [pages + 32 stacks]), or 0 */
EMSCRIPTEN_KEEPALIVE uint32_t *port_net_page_hashes(unsigned retrace) {
    for (int i = 0; i < NET_PAGE_RING; i++)
        if (net_page_ring && net_page_ring_frame[i] == retrace) return net_page_ring + (size_t)i * (net_npages + NET_STACK_SLOTS);
    return 0;
}
/* 0 = pages, 1 = stack slots, 2 = wasm address of page 0 (__global_base), 3 = page size, 4 = wasm address of n64_rdram */
EMSCRIPTEN_KEEPALIVE uintptr_t port_net_page_info(int which) {
    extern unsigned char n64_rdram[];
    switch (which) {
    case 0: return net_npages; case 1: return NET_STACK_SLOTS; case 2: return (uintptr_t)&__global_base;
    case 3: return NET_PAGE; default: return (uintptr_t)n64_rdram;
    }
}
