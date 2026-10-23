/* P69 runtime checks of port P65 / port-b P67 C (link-time wraps; only cross-TU calls are seen).
 *  ?p69attach=N  func_15030758 (attachment list D_800C3EE0, game_eu_5D910.c): on the first call the callback table
 *                D_80084550[1..24] as loaded (wasm table index, registered signature, port_n64_to_wasm of the ROM
 *                word: they must be equal), then the list (model, callback, sub-model, timer, mtx, target) whenever
 *                its shape changes, for the first N changes.
 *  ?p69look=N    func_1503AB20 (head / eye aim, called by func_1502C074): record, id, mode +0x276, timer +0x282,
 *                angles +0x27A..+0x280 before -> after, look target D_800C4408 and the call counter D_800C441A
 *                (written by func_15036FD8): first N calls, then every 128th and every angle change of record 0
 *                (first 200).
 *  ?p69tri=N     func_150028BC (per-model triangle tables, called by func_1503D210 / func_1503DD8C): id -> result.
 *  ?p69att=N     func_1505C7D8 (attack hit test, from func_1504CB98 when +0xD0 != 0), func_150D5F7C (debris burst),
 *                func_1507E7E4 (object animation start): every call up to N each, with the attacker's attack entry,
 *                health of the 25 records before -> after (hits), return value.
 *  ?p69floor=N   func_15046C6C (floor / wall probe pair; its func_150453BC call is in the same TU): position, max y,
 *                result, hit t and flags, first N calls. */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
const char *port_fsig_of(void *fp);
extern unsigned port_frame_count;
extern unsigned char D_800CC2D0[];
extern unsigned char D_80084550_[] __asm__("D_80084550");
extern unsigned char D_800C3EE0_[] __asm__("D_800C3EE0");
extern unsigned char D_800C4408_[] __asm__("D_800C4408");
extern unsigned char D_800C441A_[] __asm__("D_800C441A");
extern unsigned char D_800DD280_[] __asm__("D_800DD280");
static unsigned w_n;
/* ?p69stub=MASK DIAGNOSTIC (bisecting the respawn hang): skip the game C like the old asm stubs did: 1 func_1507E7E4,
 * 2 func_15030758, 4 func_150028BC (returns 0), 8 func_1503AB20, 16 func_15046C6C (returns 0), 32 func_15036FD8. */
static int fstub = -1;
static int stubbed(int b) { if (fstub < 0) fstub = port_flag("p69stub"); return fstub & b; }

#define REC 0x32C
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }
static unsigned W(const unsigned char *r, int o) { return *(const unsigned *)(r + o); }
static int recno(const void *r) { return (int)(((const unsigned char *)r - D_800CC2D0) / REC); }
static int flag(int *f, const char *n) { if (*f < 0) *f = port_flag(n); return *f; }

static const unsigned cb_rom[25] = {0, 0x150D87CC, 0x1503211C, 0x1503216C, 0x150F5C30, 0x150322B8, 0x1503356C,
    0x15033618, 0x150C78E0, 0x150334A8, 0x150C8C30, 0x15033730, 0x150E0350, 0x150337A8, 0x15033A7C, 0x15033AD4,
    0x15033B28, 0x15033CB8, 0x15033DC8, 0x150D88E8, 0x150340F0, 0x150F5FD4, 0x15033698, 0x150341FC, 0x15034260};

static int fa = -1, fl = -1, ft = -1, fk = -1, ff = -1, fd = -1, fw = -1;

static void p69_scan_lists(void);
void __real_func_15030758(void);
void __wrap_func_15030758(void) {
    if (stubbed(2)) return;
    static unsigned calls, changes, lastsig;
    const unsigned char *p;
    unsigned sig = 0, n = 0;
    p69_scan_lists();
    { void p69_watch_frame(void); p69_watch_frame(); }
    if (!flag(&fa, "p69attach")) { __real_func_15030758(); return; }
    if (calls++ == 0) {
        int i, bad = 0;
        for (i = 1; i <= 24; i++) {
            unsigned v = W(D_80084550_, i * 4), want = (unsigned)(uintptr_t)port_n64_to_wasm(cb_rom[i]);
            bad += v != want || v == 0;
            port_log("[p69] D_80084550[%2d] = #%u (%s) ROM %08X -> #%u %s\n", i, v, port_fsig_of((void *)(uintptr_t)v),
                     cb_rom[i], want, v == want && v ? "ok" : "BAD");
        }
        port_log("[p69] D_80084550 callback table: %s (%d bad of 24)\n", bad ? "FAIL" : "PASS", bad);
    }
    for (p = (const unsigned char *)(uintptr_t)W(D_800C3EE0_, 0); p && n < 64; p = (const unsigned char *)(uintptr_t)W(p, 0x54))
        sig = sig * 31 + (vbe_ld8(p) << 16 | vbe_ld8(p + 7) << 8 | vbe_ld16(p + 0x1E)) + 1, n++;
    if (sig != lastsig && changes++ < (unsigned)fa) {
        port_log("[p69] attach list frame %u: %u records\n", port_frame_count, n);
        for (p = (const unsigned char *)(uintptr_t)W(D_800C3EE0_, 0); p && n--; p = (const unsigned char *)(uintptr_t)W(p, 0x54))
            port_log("[p69]   rec %p model %d joint %d callback %d sub %d timer %d mtx %08X target %08X\n", (void *)p,
                     vbe_ld8(p), vbe_ld8(p + 2), vbe_ld8(p + 7), vbe_ld16(p + 0x1E), vbe_ld16(p + 0x1C), W(p, 0x34),
                     W(p, 0x48));
    }
    lastsig = sig;
    if (port_frame_count >= 900 && (port_frame_count / 2) % 300 == 0) {   /* object census, every ~600 frames */
        int i;
        for (i = 0; i < 25; i++) {
            const unsigned char *r = D_800CC2D0 + i * REC;
            if (vbe_ld8(r + 4) || vbe_ld8(r + 5))
                port_log("[p69] census frame %u: record %d id %02X state %d health %d pos %.0f %.0f %.0f anim %04X "
                         "+D0 %d\n", port_frame_count, i, vbe_ld8(r + 4), vbe_ld8(r + 5), vbe_ld8(r + 0x1CA), F(r, 0x14),
                         F(r, 0x18), F(r, 0x1C), vbe_ld16(r + 0x84), vbe_ld8(r + 0xD0));
        }
    }
    __real_func_15030758();
}

static void look_state(const unsigned char *r, int *o) {
    int i;
    o[0] = (signed char)vbe_ld8(r + 0x276);
    for (i = 0; i < 4; i++) o[1 + i] = (short)vbe_ld16(r + 0x27A + 2 * i);
    o[5] = vbe_ld16(r + 0x282);
}

void __real_func_1503AB20(void *obj);
void __wrap_func_1503AB20(void *obj) {
    if (stubbed(8)) return;
    static unsigned n, ch;
    int a[6], b[6], diff, i;
    const unsigned char *r = obj;
    if (!flag(&fl, "p69look") || !r) { __real_func_1503AB20(obj); return; }
    look_state(r, a);
    __real_func_1503AB20(obj);
    look_state(r, b);
    n++;
    for (diff = 0, i = 0; i < 6; i++) diff |= a[i] != b[i];
    if (n <= (unsigned)fl || n % 128 == 0 || (diff && recno(r) == 0 && ch++ < 200))
        port_log("[p69] look call %u frame %u: rec %d id %02X mode %d timer %d angles %d %d %d %d -> %d %d %d %d | "
                 "target %.1f %.1f %.1f count %d | pos %.1f %.1f %.1f\n", n, port_frame_count, recno(r),
                 vbe_ld8(r + 4), b[0], b[5], a[1], a[2], a[3], a[4], b[1], b[2], b[3], b[4], F(D_800C4408_, 0),
                 F(D_800C4408_, 4), F(D_800C4408_, 8), vbe_ld8(D_800C441A_), F(r, 0x14), F(r, 0x18), F(r, 0x1C));
}

int __real_func_150028BC(int id);
int __wrap_func_150028BC(int id) {
    if (stubbed(4)) return 0;
    static unsigned n;
    int v = __real_func_150028BC(id);
    if (flag(&ft, "p69tri") && n++ < (unsigned)ft)
        port_log("[p69] tri tables call %u frame %u: id %d -> %d\n", n, port_frame_count, id, v);
    return v;
}

static void healths(unsigned char *h) {
    int i;
    for (i = 0; i < 25; i++) h[i] = vbe_ld8(D_800CC2D0 + i * REC + 0x1CA);
}

int __real_func_1505C7D8(void *self, int skip);
int __wrap_func_1505C7D8(void *self, int skip) {
    if (stubbed(128)) return 0;
    static unsigned n;
    unsigned char h0[25], h1[25];
    const unsigned char *r = self;
    int v, i, d0;
    if (!flag(&fk, "p69att")) return __real_func_1505C7D8(self, skip);
    healths(h0);
    d0 = vbe_ld8(r + 0xD0);
    v = __real_func_1505C7D8(self, skip);
    healths(h1);
    if (n++ < (unsigned)fk) {
        port_log("[p69] attack call %u frame %u: rec %d id %02X skip %d +D0 %d -> %d anim %04X -> %d\n", n,
                 port_frame_count, recno(r), vbe_ld8(r + 4), skip, d0, vbe_ld8(r + 0xD0), vbe_ld16(r + 0x84), v);
        for (i = 0; i < 25; i++)
            if (h0[i] != h1[i])
                port_log("[p69]   hit: record %d id %02X health %d -> %d\n", i, vbe_ld8(D_800CC2D0 + i * REC + 4),
                         h0[i], h1[i]);
    }
    return v;
}

void __real_func_150D5F7C(void *obj, int a1, int a2);
void __wrap_func_150D5F7C(void *obj, int a1, int a2) {
    static unsigned n;
    if (stubbed(256)) return;
    if (flag(&fk, "p69att") && n++ < (unsigned)fk)
        port_log("[p69] debris call %u frame %u: rec %d id %02X args %d %d pos %.1f %.1f %.1f\n", n, port_frame_count,
                 recno(obj), vbe_ld8((unsigned char *)obj + 4), a1, a2, F(obj, 0x14), F(obj, 0x18), F(obj, 0x1C));
    __real_func_150D5F7C(obj, a1, a2);
}

void __real_func_1507E7E4(void *obj, int anim, int prio, int time, int a4);
void __wrap_func_1507E7E4(void *obj, int anim, int prio, int time, int a4) {
    if (stubbed(1)) return;
    static unsigned n;
    const unsigned char *r = obj;
    __real_func_1507E7E4(obj, anim, prio, time, a4);
    if (flag(&fk, "p69att") && n++ < (unsigned)fk)
        port_log("[p69] obj anim call %u frame %u: rec %d id %02X anim %d prio %d time %d a4 %d -> +6F %d +71 %d +72 %d\n",
                 n, port_frame_count, recno(r), vbe_ld8(r + 4), anim & 0xFF, prio & 0xFF, time & 0xFFFF, a4,
                 vbe_ld8(r + 0x6F), vbe_ld8(r + 0x71), vbe_ld16(r + 0x72));
}

int __real_func_15046C6C(void *pos, int a1, float maxY, void *hit);
int __wrap_func_15046C6C(void *pos, int a1, float maxY, void *hit) {
    if (stubbed(16)) return 0;
    static unsigned n;
    int v = __real_func_15046C6C(pos, a1, maxY, hit);
    if (flag(&ff, "p69floor") && n++ < (unsigned)ff)
        port_log("[p69] floor probe call %u frame %u: pos %.1f %.1f %.1f a1 %d maxY %.1f -> %d t %.2f flags %02X "
                 "type %08X\n", n, port_frame_count, F(pos, 0), F(pos, 4), F(pos, 8), a1 & 0xFFFF, maxY, v,
                 F(hit, 0), vbe_ld8((unsigned char *)hit + 0x1C), W(hit, 0x18));
    return v;
}

/*  ?p69free=1    func_10004074 (free): a block whose header tag is already 0 (free) is a double free: log it with the
 *                JS stack and the first words of the block; =2 also skips such frees (DIAGNOSTIC, keeps the heap). */
void port_js_stack(int skip, int n);
void __real_func_10004074(int p);
static void p69_watch(const char *where);
void __wrap_func_10004074(int p) {
    static unsigned n;
    if (fw > 0) p69_watch("free");
    if (fw > 0 && p >= 0x10000000 && W(D_800DD280_, 0x1A0) && W(D_800DD280_, 0x1A0) < 0x10000000u && w_n < 100) {
        w_n = 100;
        const unsigned char *q = (const unsigned char *)(uintptr_t)p;
        int i;
        port_log("[p69] free of node %08X with garbage next %08X frame %u: type %d group %d prev %08X, block size %X tag %02X\n",
                 p, W(q, 8), port_frame_count, vbe_ld8(q), vbe_ld8(q + 1), W(q, 4), W(q - 0xC, 8) & 0xFFFFFF, W(q - 0xC, 8) >> 24);
        for (i = 0; i < 0x80; i += 0x20)
            port_log("[p69]   +%02X: %08X %08X %08X %08X %08X %08X %08X %08X\n", i, W(q, i), W(q, i + 4), W(q, i + 8),
                     W(q, i + 12), W(q, i + 16), W(q, i + 20), W(q, i + 24), W(q, i + 28));
    }
    if (flag(&fd, "p69free") && p) {
        const unsigned *h = (const unsigned *)(uintptr_t)(p - 0xC);
        if ((h[2] >> 24) == 0) {
            if (n++ < 8) {
                port_log("[p69] DOUBLE FREE frame %u: block %08X size %X words %08X %08X %08X %08X (type byte %d)\n",
                         port_frame_count, p, h[2] & 0xFFFFFF, h[3], h[4], h[5], h[6],
                         vbe_ld8((const unsigned char *)(uintptr_t)p));
                port_js_stack(1, 12);
            }
            if (fd == 2) return;
        }
    }
    { /* P113 ?p113free=FRAME: from that frame on, log each free (block header) with a heap walk before it and the
       * JS stack (first 30) - finds the free that breaks the heap after the LogoScreen scene end */
        static int ff = -1, nf; extern __attribute__((weak)) int port_heap_check(void); extern unsigned port_frame_count;
        if (flag(&ff, "p113free") && port_frame_count >= (unsigned)ff && p && nf < 30) {
            const unsigned *h = (const unsigned *)(uintptr_t)(p - 0xC);
            nf++;
            port_log("[p113] free %08X frame %u: header next %08X prev %08X info %08X; heap before:\n", p, port_frame_count, h[0], h[1], h[2]);
            if (port_heap_check) port_heap_check();
            port_js_stack(1, 6);
        }
    }
    __real_func_10004074(p);
}

/* ?p69free also scans the object lists D_800DD280[2][104] once per frame (from the func_15030758 wrap): the first
 * node pointer outside wasm memory >= 0x10000000 is logged with its list and the node that links to it. */
static void p69_scan_lists(void) {
    static int done;
    int i, j, k;
    if (done || !flag(&fd, "p69free")) return;
    if (fd >= 3 && port_frame_count >= (unsigned)fd && port_frame_count < (unsigned)fd + 40) {   /* ?p69free=FRAME: dump */
        for (i = 0; i < 2; i++)
            for (j = 0; j < 104; j++) {
                unsigned node = W(D_800DD280_, (i * 104 + j) * 4), cnt = 0, freed = 0, first = node;
                for (k = 0; node >= 0x10000000u && node < 0x20000000u && k < 500; k++, cnt++) {
                    freed += (W((const unsigned char *)(uintptr_t)node - 0xC, 8) >> 24) == 0;
                    node = W((const unsigned char *)(uintptr_t)node, 8);
                }
                if (first)
                    port_log("[p69] lists frame %u: [%d][%d] head %08X nodes %u (%u in freed blocks)%s\n", port_frame_count,
                             i, j, first, cnt, freed, node ? " BAD END" : "");
            }
    }
    for (i = 0; i < 2; i++)
        for (j = 0; j < 104; j++) {
            unsigned prev = 0, node = W(D_800DD280_, (i * 104 + j) * 4);
            for (k = 0; node && k < 2000; k++) {
                if (node < 0x10000000u || node >= 0x20000000u) {
                    const unsigned char *pn = (const unsigned char *)(uintptr_t)prev;
                    port_log("[p69] BAD NODE frame %u: list [%d][%d] position %d node %08X, linked from %08X (type %d group %d "
                             "prev %08X words +C %08X %08X %08X %08X)\n", port_frame_count, i, j, k, node, prev,
                             pn ? vbe_ld8(pn) : -1, pn ? vbe_ld8(pn + 1) : -1, pn ? W(pn, 4) : 0, pn ? W(pn, 0xC) : 0,
                             pn ? W(pn, 0x10) : 0, pn ? W(pn, 0x14) : 0, pn ? W(pn, 0x18) : 0);
                    done = 1;
                    return;
                }
                prev = node;
                node = W((const unsigned char *)(uintptr_t)node, 8);
            }
        }
}

/* ?p69watch=N: poll the word D_800DD280[1][0] (list group 1, type 0; P69's garbage 0x243C head) at every asm-stub hit
 * (port_stub_trace_hook), free and per frame; log the first N changes with the JS stack and the last stub seen. */
extern void (*port_stub_trace_hook)(const char *name);
static const char *w_last = "-";
static unsigned w_val;
static void p69_watch(const char *where) {
    unsigned v = W(D_800DD280_, 0x1A0);
    if (v != w_val && w_n < (unsigned)fw) {
        w_n++;
        port_log("[p69] watch D_800DD280[1][0] frame %u at %s (last stub %s): %08X -> %08X\n", port_frame_count, where,
                 w_last, w_val, v);
        port_js_stack(1, 10);
    }
    w_val = v;
}
static void p69_hook(const char *name) { p69_watch("stub"); w_last = name; }
void p69_watch_frame(void) {
    if (fw < 0) { fw = port_flag("p69watch"); if (fw) port_stub_trace_hook = p69_hook; }
    if (fw) p69_watch("frame");
}

void __real_func_15036FD8(void);
void p81_look_hook(int pre);
void __wrap_func_15036FD8(void) { if (!stubbed(32)) { p81_look_hook(1); __real_func_15036FD8(); p81_look_hook(0); } }

/* func_150D71D4 (P67 debris piece; reached through a ROM function table, so the wrap also replaces the table entry):
 * ?p69att logs the first N calls; ?p69stub bit 64 skips it (returns 0). */
int __real_func_150D71D4(void *a0, int a1);
int __wrap_func_150D71D4(void *a0, int a1) {
    static unsigned n;
    int v;
    if (stubbed(64)) return 0;
    v = __real_func_150D71D4(a0, a1);
    if (flag(&fk, "p69att") && n++ < (unsigned)fk)
        port_log("[p69] debris piece call %u frame %u: obj %p a1 %d -> %d\n", n, port_frame_count, a0, a1, v);
    return v;
}
