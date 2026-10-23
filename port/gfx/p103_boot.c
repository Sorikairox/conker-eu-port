/* P103 DIAGNOSTICS (off by default): the boot sequence and the level-start event list.
 *
 * ?p103boot=1 : one line per change of the game mode D_800E0B94 or the level D_800BE9F0 (called from the
 *               func_151E5928 wrap in p84_checks.c): mode, previous mode D_800E0FC5, mode timer D_800E0EC0,
 *               osTvType D_80000300, world objects D_800DC320, level events D_800D2F3C, scene slot 0 D_800C35EA.
 *               Also logs every func_1509B4A0 call (level-start event pass: the event ids D_800D2F40[0..n-1], their
 *               D_800877D0 record, and what the asm func_1509CBD4 would answer, computed here from its asm), every
 *               func_1509B5AC call (start one event) and every func_1501D348 call (scene load).
 * ?p103ev=1   : TEST ONLY. func_1509CBD4 (game_eu_CA630.c, still an asm stub = always 0) answers with the C below, so
 *               func_1509B4A0 goes on to func_1509B5AC (also an asm stub). Shows which events the stub suppresses.
 *
 * func_1509CBD4(id) from the asm: the u16 list D_800877D0[id] + 0xC (0xFFFF-terminated) holds prerequisite event ids;
 * for each one p, recurse on p, then require save flag bit p (D_800D2E4C byte p >> 3, bit p & 7) and the recursion's
 * result; an empty list answers 1. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;

extern unsigned char D_800E0B94, D_800E0FC5, D_800D2F3C, D_800C35EA;
extern int D_800BE9F0, D_800E0EC0, D_80000300, D_800DC320;
extern unsigned char *D_800D2F40;  /* u16 ids */
extern unsigned char *D_800D2E4C;  /* save flags (pointer) */
extern unsigned char D_800877D0[]; /* 0x14-byte records */

static int fboot = -1, fev = -1;
static int flag(int *f, const char *n) { if (*f < 0) *f = port_flag(n); return *f; }

static int memok(const void *p) { uintptr_t a = (uintptr_t)p; return a >= 0x100 && a < 0x20000000u; }

static int p103_prereq(int id, int depth) {
    const unsigned char *rec = D_800877D0 + id * 0x14;
    const unsigned char *p = (const unsigned char *)(uintptr_t)*(const unsigned *)(rec + 0xC);
    const unsigned char *save = D_800D2E4C;
    unsigned e;
    if (depth > 16 || !memok(p) || !memok(save)) return -1;
    e = vbe_ld16(p);
    while (e != 0xFFFF) {
        int ok = p103_prereq(e, depth + 1);
        e = vbe_ld16(p);
        if (!(vbe_ld8(save + (e >> 3)) & (1u << (e & 7))) || ok <= 0) return 0;
        p += 2;
        e = vbe_ld16(p);
    }
    return 1;
}

void p123_gates(void);
void p103_frame(void) {
    static int lmode = -1, llevel = -1;
    p123_gates();
    int m = vbe_ld8(&D_800E0B94), l = D_800BE9F0;
    if (flag(&fboot, "p103boot") && m == 3) { /* P121: menu record D_80090174 (P117 map): +8 page fade f32, +0x2C titlePage,
                                                * +0x3E menu, +0x3F mainPage; on change of the bytes, else every 240 frames */
        extern unsigned char *D_80090174; extern unsigned char D_800E0FC6, D_80090114, D_800E0EC4;
        static unsigned lastkey = ~0u, nl, next;
        const unsigned char *r = D_80090174;
        if (memok(r) && nl < 60) {
            unsigned fw = *(const unsigned *)(r + 8), key = vbe_ld8(r + 0x2C) | vbe_ld8(r + 0x3E) << 8 | vbe_ld8(r + 0x3F) << 16 |
                (unsigned)vbe_ld8(&D_80090114) << 24;
            float fade; memcpy(&fade, &fw, 4);
            static unsigned lastfw;
            if (key != lastkey || fw != lastfw || port_frame_count >= next) {
                nl++; lastkey = key; lastfw = fw; next = port_frame_count + 240;
                port_log("[p121] menu frame %u: rec %08X fade %g titlePage %d menu %d mainPage %d input %04X | overlay D_800E0FC6 %u speed D_80090114 %u page alpha D_800E0EC4 %u\n", port_frame_count,
                         (unsigned)(uintptr_t)r, fade, (signed char)vbe_ld8(r + 0x2C), (signed char)vbe_ld8(r + 0x3E),
                         (signed char)vbe_ld8(r + 0x3F), vbe_ld16(r + 0x20),
                         vbe_ld8(&D_800E0FC6), vbe_ld8(&D_80090114), vbe_ld8(&D_800E0EC4));
                { /* camera 0: non-finite floats, target */
                    extern unsigned char *D_800DBFF0; const unsigned *c = (const unsigned *)D_800DBFF0; int o, bad = 0, first = -1;
                    if (memok(c))
                    for (o = 0; o < 0x9A0 / 4; o++) if (((c[o] >> 23) & 0xFF) == 0xFF) { bad++; if (first < 0) first = o * 4; }
                    port_log("[p121]   camera 0: %d non-finite words (first +%X) target +3D4 %08X +5F0 %08X +18C %08X %08X %08X\n",
                             bad, first, c[0x3D4 / 4], c[0x5F0 / 4],
                             c[0x18C / 4], c[0x190 / 4], c[0x194 / 4]);
                }
            }
        }
    }
    if (!flag(&fboot, "p103boot") || (m == lmode && l == llevel)) return;
    port_log("[p103] frame %u: mode %d (prev %d) level %X timer %d tv %d | objects %d events %u scene0 %u\n",
             port_frame_count, m, vbe_ld8(&D_800E0FC5), l, D_800E0EC0, D_80000300, D_800DC320, vbe_ld8(&D_800D2F3C),
             vbe_ld8(&D_800C35EA));
    lmode = m; llevel = l;
}

int __real_func_1509CBD4(int id);
int __wrap_func_1509CBD4(int id) {
    if (flag(&fev, "p103ev")) {
        int r = p103_prereq(id, 0);
        return r > 0;
    }
    return __real_func_1509CBD4(id);
}

void __real_func_1509B4A0(int a0, int a1);
void __wrap_func_1509B4A0(int a0, int a1) {
    if (flag(&fboot, "p103boot")) {
        int n = vbe_ld8(&D_800D2F3C), i;
        port_log("[p103] func_1509B4A0(%d, %d) frame %u level %X mode %d: %d level events, save flags %08X\n", a0, a1,
                 port_frame_count, D_800BE9F0, vbe_ld8(&D_800E0B94), n, (unsigned)(uintptr_t)D_800D2E4C);
        for (i = 0; i < n && i < 32 && memok(D_800D2F40); i++) {
            int id = (short)vbe_ld16(D_800D2F40 + 2 * i);
            const unsigned *r = (const unsigned *)(D_800877D0 + id * 0x14);
            const unsigned char *pl = (const unsigned char *)(uintptr_t)r[3];
            char pre[64]; int k, o = 0;
            for (k = 0; k < 6 && memok(pl); k++) {
                unsigned e = vbe_ld16(pl + 2 * k);
                o += snprintf(pre + o, sizeof pre - o, "%X ", e);
                if (e == 0xFFFF) break;
            }
            pre[o] = 0;
            port_log("[p103]   event %d: id %X rec %08X %08X %08X %08X %08X prereqs [%s] -> asm would answer %d\n", i, id,
                     r[0], r[1], r[2], r[3], r[4], pre, p103_prereq(id, 0));
        }
    }
    __real_func_1509B4A0(a0, a1);
}

void *__real_func_1509B5AC(int id, int a1);
void *__wrap_func_1509B5AC(int id, int a1) {
    if (flag(&fboot, "p103boot"))
        port_log("[p103] func_1509B5AC(%X, %d) frame %u (start event)\n", id, a1, port_frame_count);
    { /* P110 TEST ONLY ?p110noev=1: do not start events (= the pre-P106 asm stub, returns 0). Since port P106 the
       * LogoScreen event 0xC9 starts a 1416-frame scene on level 0x21; at its end object removal (stubs
       * func_150849C0 / func_15060D54) corrupts the heap. This keeps the old walk / death / 0x2C test path. */
        static int fnoev = -1;
        if (flag(&fnoev, "p110noev")) return 0;
    }
    return __real_func_1509B5AC(id, a1);
}

void __real_func_1501D348(int level, int scene, int slot, int cb, int cbarg);
void __wrap_func_1501D348(int level, int scene, int slot, int cb, int cbarg) {
    if (flag(&fboot, "p103boot"))
        port_log("[p103] func_1501D348(level %X, scene %d, slot %d, cb %d, %d) frame %u mode %d\n", level, scene, slot, cb,
                 cbarg, port_frame_count, vbe_ld8(&D_800E0B94));
    { /* P123 TEST ONLY ?p123noscene=1: do not start the menu level's scene (mode 3), as when func_151DEDD0 was a stub */
        static int fns = -1;
        if (flag(&fns, "p123noscene") && vbe_ld8(&D_800E0B94) == 3) { port_log("[p123] menu scene start skipped\n"); return; }
    }
    __real_func_1501D348(level, scene, slot, cb, cbarg);
}

/* P113 DIAGNOSTIC: on a ?p113watch hit, list the words of the camera records D_800DBFF0 (struct108 *, 2 x 0x800+)
 * that point within +-0x400 of the watched address (a stale camera target into a freed block). */
extern unsigned char *D_800DBFF0;
extern void (*p113_watch_hook)(unsigned addr);
static void p113_cam_scan(unsigned a) {
    unsigned o;
    for (o = 0; o < 0x1000; o += 4) {
        unsigned v = *(const unsigned *)(D_800DBFF0 + o);
        if (v + 0x400 - a < 0x800) port_log("[p113w]   D_800DBFF0+%03X = %08X (ADDR%+d)\n", o, v, (int)(v - a));
    }
}

/* P113 OPT-IN emulation ?p113g84=1 (remove when func_15084814 is game C): func_15084814 (game_eu_AF2A0, asm stub) is the
 * part-reference release under the object removal chain func_15060F28 -> func_150849C0 (C since port P112) ->
 * func_150847B4 (C). The stub left the object's part words +0x28C + j*8 set, the shared-block reference counts
 * D_800D1F80[slot] up and the private copies allocated, and the heap was corrupt right after the LogoScreen scene
 * end (frame 2133-2137). This wrap does what the asm does (EU asm read by hand, 0x60 bytes): for both words of
 * part j: word == D_800D19A0[slot] -> D_800D1F80[slot]--, else func_100043B4(word, 3); then the word = 0.
 * Result: it is NOT the cause of the heap corruption (same corruption with it), so it is opt-in; default = the stub. */
extern unsigned D_800D19A0[];
extern unsigned char D_800D1F80[];
void func_100043B4(int *p, unsigned tag);
void __real_func_15084814(unsigned char *obj, int j);
void __wrap_func_15084814(unsigned char *obj, int j) {
    static int fnog = -1, n;
    p113_watch_hook = p113_cam_scan; /* (set here: a constructor would pull game data into the scheduler demo) */
    unsigned *w = (unsigned *)(obj + 0x28C + j * 8);
    unsigned slot;
    int k;
    if (flag(&fboot, "p103boot") && n++ < 40)
        port_log("[p113] func_15084814(obj %08X, part %d) frame %u: words %08X %08X\n", (unsigned)(uintptr_t)obj, j,
                 port_frame_count, w[0], w[1]);
    if (!flag(&fnog, "p113g84")) { __real_func_15084814(obj, j); return; }
    if (w[0] == 0 && w[1] == 0) return;
    slot = (*(unsigned char **)(obj + 0x2C4))[j];
    for (k = 0; k < 2; k++) {
        if (w[k] == 0) continue;
        if (w[k] == D_800D19A0[slot]) D_800D1F80[slot]--;
        else func_100043B4((int *)(uintptr_t)w[k], 3);
        w[k] = 0;
    }
}

/* P113 DIAGNOSTIC: checkpoints of the ?p113watch write watch (pc_sched.c) around the calls of func_15019130 between its
 * func_10004250 and func_151670C0, to find the stale writer after the LogoScreen scene end (pass-through wraps). */
void p113_watch(const char *where);
#define P113W0(f) void __real_##f(void); void __wrap_##f(void) { p113_watch(#f " in"); __real_##f(); p113_watch(#f " out"); }
#define P113W1(f) void __real_##f(int); void __wrap_##f(int a) { p113_watch(#f " in"); __real_##f(a); p113_watch(#f " out"); }
#define P113W2(f) void __real_##f(int, int); void __wrap_##f(int a, int b) { p113_watch(#f " in"); __real_##f(a, b); p113_watch(#f " out"); }
P113W0(func_15035210)
P113W0(func_1510BC10)
P113W1(func_1510F800)
P113W0(func_15113700)
P113W0(func_15044D18)
/* P116: func_1502457C also logs, when slot 0's +0x65 (parent) changed during the call, the scene events it queued in
 * D_800C4170 ({event ptr, time << 8, s8 track, s16 index}, 0xC bytes) this frame (first 8 entries). */
void __real_func_1502457C(int, int);
void __wrap_func_1502457C(int a, int b) {
    extern unsigned char D_800CC2D0[];
    extern unsigned char *D_800C4170;
    static unsigned nlog;
    unsigned before = vbe_ld8(D_800CC2D0 + 0x65), after;
    p113_watch("func_1502457C in");
    __real_func_1502457C(a, b); /* (P121: the P116 test-only ?p116walk copy is gone: the game C has the fix since P117) */
    p113_watch("func_1502457C out");
    { /* P121 (?p103boot): log queued events of the scene's last track (13: camera switch 3/0xD, exit 5/0x67) and any
       * type-3 / 5-0x67 event, first 24 hits */
        static int fb = -1; static unsigned n121; static const unsigned char *lastev;
        int i;
        if (flag(&fb, "p103boot") && D_800C4170)
            for (i = 0; i < 16 && n121 < 24; i++) {
                const unsigned char *e = D_800C4170 + i * 0xC;
                const unsigned char *ev = (const unsigned char *)(uintptr_t)*(const unsigned *)e;
                int tr = (signed char)vbe_ld8(e + 8);
                if (!memok(ev)) break;
                if (ev == lastev) continue;
                if (tr == 13 || (vbe_ld8(ev) == 3 && vbe_ld16(ev + 2) == 0xD) || (vbe_ld8(ev) == 5 && vbe_ld16(ev + 2) == 0x67)) {
                    lastev = ev; n121++;
                    port_log("[p121] walker(%d, %d) frame %u queued ev %08X time %d track %d: type %02X id %04X b4 %d b5 %d w6 %d\n",
                             a, b, port_frame_count, (unsigned)(uintptr_t)ev, *(const int *)(e + 4) >> 8, tr, vbe_ld8(ev),
                             vbe_ld16(ev + 2), (signed char)vbe_ld8(ev + 4), (signed char)vbe_ld8(ev + 5), (short)vbe_ld16(ev + 6));
                }
            }
    }
    after = vbe_ld8(D_800CC2D0 + 0x65);
    if (after != before && nlog++ < 8) {
        int i;
        port_log("[p116] slot 0 +0x65 %02X -> %02X in func_1502457C(%d, %d) frame %u; queue:\n", before, after, a, b,
                 port_frame_count);
        if (nlog == 1) { /* the slot-0 scene tables: event track i -> events pointer / count, and its ref entry */
            extern int D_800C3AA8[][30]; extern unsigned short *D_800C39F8[]; extern unsigned char *D_800C3A10[];
            extern unsigned char D_800C3A5A[];
            int n = vbe_ld8(D_800C3A5A);
            for (i = 0; i < n && i < 30; i++) {
                const unsigned char *rf = D_800C3A10[0] + i * 8;
                port_log("[p116]   track %d: events %08X n %d | ref kind %d id %d\n", i, (unsigned)D_800C3AA8[0][i],
                         D_800C39F8[0] ? vbe_ld16(&D_800C39F8[0][i]) : -1, vbe_ld16(rf), vbe_ld8(rf + 2));
            }
        }
        for (i = 0; i < 8 && D_800C4170; i++) {
            const unsigned char *e = D_800C4170 + i * 0xC;
            const unsigned char *ev = (const unsigned char *)(uintptr_t)*(const unsigned *)e;
            if (!memok(ev)) break;
            port_log("[p116]   ev %08X time %d track %d idx %d: type %02X delta %02X id %04X b4 %d b5 %d w6 %d\n",
                     (unsigned)(uintptr_t)ev, *(const int *)(e + 4) >> 8, (signed char)vbe_ld8(e + 8), (short)vbe_ld16(e + 0xA),
                     vbe_ld8(ev), vbe_ld8(ev + 1), vbe_ld16(ev + 2), (signed char)vbe_ld8(ev + 4), (signed char)vbe_ld8(ev + 5),
                     (short)vbe_ld16(ev + 6));
        }
    }
}
P113W1(func_1501ECA4)
P113W1(func_15020F6C)
P113W1(func_1501E364)
P113W0(func_15122AE0)
P113W0(func_1504ADD0)
P113W1(func_151101B4)
P113W2(func_15174F68)
P113W0(func_1501C860)
P113W1(func_1511FC20)
P113W1(func_151890E4)
P113W0(func_1502C494)
P113W0(func_15114208)
P113W1(func_15173E34)

/* P113 TEMPORARY guard (remove when the scene end retargets the camera itself): after the LogoScreen scene on level
 * 0x21 ends (frame 2133) the object removal func_15060F28 (from func_1502298C) frees the removed object's +0x31C
 * record, but camera record D_800DBFF0[i] (struct108, 0x9A0 bytes) keeps it as its target unk3D4 (set by
 * func_1512868C from D_800CC2D0[unk23D].unk31C). func_15122AE0 -> func_15122C5C then writes floats into the freed
 * block (+0x138..) and the next heap walk / alloc traps (frame 2137). On N64 the scene VM func_15024910 (asm stub
 * here) ends LogoScreen with opcode 0x67 -> func_151DECB4 -> mode 3 before that; the stub never does, so the producer
 * that should retarget / drop the camera is in the stubbed scene path. Guard: a camera whose unk3D4 is the freed
 * record is pointed at a zeroed parking record instead. ?p113noguard=1 / PORT_P113NOGUARD=1 turns it off.
 * P121: since the P117 walker fix track 13 runs (3/0xD, 5/0x5C, 5/0x67 -> func_151DECB4 at frame 2133) and the
 * 2133 case is harmless without the guard (mode 3 at 2139, no trap); but the menu level's scene 1 (916 frames) ends
 * at 3053 with the same stale target (camera 0, object 105DF6F0) and without the guard node traps 4 frames later in
 * func_1508F0D4 (particle list). Guard KEPT for that case. */
extern int D_80082FA0;
static unsigned p113_park[0x200] __attribute__((aligned(16)));
void __real_func_15060F28(unsigned char *obj, int mode);
void __wrap_func_15060F28(unsigned char *obj, int mode) {
    static int fng = -1, n;
    unsigned rec = *(unsigned *)(obj + 0x31C);
    int i;
    __real_func_15060F28(obj, mode);
    if (rec == 0) return;
    for (i = 0; i <= D_80082FA0 && i < 4; i++) {
        unsigned *t = (unsigned *)(D_800DBFF0 + i * 0x9A0 + 0x3D4);
        if (*t == rec && flag(&fng, "p113noguard")) { /* P121: report the stale target with the guard off too */
            if (n++ < 16)
                port_log("[p113] NO GUARD: camera %d target %08X freed with object %08X (mode %d) frame %u\n", i, rec,
                         (unsigned)(uintptr_t)obj, mode, port_frame_count);
        } else if (*t == rec) {
            if (n++ < 16)
                port_log("[p113] guard: camera %d target %08X freed with object %08X (mode %d) frame %u -> parking record\n", i, rec,
                         (unsigned)(uintptr_t)obj, mode, port_frame_count);
            *t = (unsigned)(uintptr_t)p113_park;
        }
    }
}

/* P116 (?p103boot): log every setup command list run (func_15083568, called from scene handler A func_15024910 for
 * type 0xD b4 0 and from other TUs): owner slot, list n, result. */
int __real_func_15083568(void *obj, int n, float f, int a3);
int __wrap_func_15083568(void *obj, int n, float f, int a3) {
    static unsigned cnt;
    extern unsigned char D_800CC2D0[];
    int r = __real_func_15083568(obj, n, f, a3);
    if (flag(&fboot, "p103boot") && cnt++ < 60) {
        long so = ((unsigned char *)obj - D_800CC2D0), sr = ((unsigned char *)(uintptr_t)(unsigned)r - D_800CC2D0);
        port_log("[p116] func_15083568(obj %08X slot %ld, list %d, %g, %d) frame %u -> %08X slot %ld (+65 %02X)\n",
                 (unsigned)(uintptr_t)obj, so / 0x32C, n, f, a3, port_frame_count, (unsigned)r, sr / 0x32C,
                 r ? vbe_ld8((unsigned char *)(uintptr_t)(unsigned)r + 0x65) : 0);
    }
    return r;
}

/* P116 (?p116find=1): log the object lookups by setup id of the scene handlers (func_15083E90 / func_15083FB0, called
 * from game_eu_51190.c): id -> slot, first 80 calls whose answer changes per id. */
void *__real_func_15083E90(unsigned char id);
int __real_func_15083FB0(unsigned char id);
static int ffind = -1;
static void p116_find_log(const char *fn, unsigned id, long slot) {
    static long last[256]; static int init; static unsigned n;
    if (!init) { int i; for (i = 0; i < 256; i++) last[i] = -1000; init = 1; }
    if (!flag(&ffind, "p116find") || n >= 80 || last[id & 0xFF] == slot) return;
    last[id & 0xFF] = slot; n++;
    port_log("[p116] %s(%u) frame %u -> slot %ld\n", fn, id, port_frame_count, slot);
}
void *__wrap_func_15083E90(unsigned char id) {
    extern unsigned char D_800CC2D0[];
    void *r = __real_func_15083E90(id);
    p116_find_log("func_15083E90", id, r ? ((unsigned char *)r - D_800CC2D0) / 0x32C : -1);
    return r;
}
int __wrap_func_15083FB0(unsigned char id) {
    int r = __real_func_15083FB0(id);
    p116_find_log("func_15083FB0", id, r);
    return r;
}

/* P121 (?p103boot): log the scene-end menu request (func_151DECB4, from scene handler A event 5/0x67). */
void __real_func_151DECB4(void);
void __wrap_func_151DECB4(void) {
    static int fb = -1;
    if (flag(&fb, "p103boot")) port_log("[p121] func_151DECB4 (5/0x67 menu request) frame %u\n", port_frame_count);
    __real_func_151DECB4();
}

/* P121 TEST ONLY ?p121spr=1: run the copy of func_151EE704 without the KSEG0 OR (port/boot/p69_pcold.c). */
void __real_func_151EE704(void);
void __wrap_func_151EE704(void) {
    static int fs = -1;
    void p121_sprites_fixed(void);
    if (flag(&fs, "p121spr")) p121_sprites_fixed(); else __real_func_151EE704();
}

/* P123 DIAGNOSTIC ?p123fade=1: every screen-colour/fade request func_1517F3B0(r, g, b, frames, dir, player) with the
 * frame and the JS stack, and (from p103_frame, mode 3 and every 120 frames) the world-render gates of
 * func_15019464 / func_150195A0: D_800BEAC0, D_80084810, func_1517F51C(0) (fade level 0xFF = skip), D_800D18A0. */
void p123_requests_stack(void);
void __real_func_1517F3B0(int r, int g, int b, int n, int dir, int pl);
void __wrap_func_1517F3B0(int r, int g, int b, int n, int dir, int pl) {
    static int ff = -1, nl;
    if (flag(&ff, "p123fade") && nl++ < 80) {
        void port_js_stack(int skip, int n);
        port_log("[p123] func_1517F3B0(rgb %d %d %d, frames %d, dir %d, player %d) frame %u mode %d\n", r, g, b, n,
                 (signed char)dir, pl, port_frame_count, vbe_ld8(&D_800E0B94));
        port_js_stack(1, 4);
    }
    __real_func_1517F3B0(r, g, b, n, dir, pl);
}
void p123_gates(void) {
    static int ff = -1; static unsigned next;
    extern unsigned char D_800BEAC0, D_800DDDAC, D_800DE1F0[]; extern int D_80084810; extern unsigned short D_800D18A0;
    extern int D_800DDDB0, D_800DDE28; int func_1517F470(int);
    if (!flag(&ff, "p123fade") || port_frame_count < next) return;
    next = port_frame_count + 120;
    port_log("[p123] gates frame %u mode %d level %X: D_800BEAC0 %u D_80084810 %d D_800D18A0 %X | fade level %d (dir %d timer %d/%d forced %u)\n",
             port_frame_count, vbe_ld8(&D_800E0B94), D_800BE9F0, vbe_ld8(&D_800BEAC0), D_80084810, vbe_ld16(&D_800D18A0),
             func_1517F470(0), (signed char)vbe_ld8(&D_800DDDAC), D_800DDDB0, D_800DDE28, vbe_ld8(&D_800DE1F0[0]));
}


/* P123 ?p123fadeev (TEST-ONLY wrap of handler C func_15029EA8, 5/1 fade branch) removed in P126: port P124 converted
 * func_15029EA8 to C and the menu fades in by itself. */
