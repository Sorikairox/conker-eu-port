/* P61 ?p61check=N: runtime checks of port-b P59's converted C (link-time wraps, N = calls logged in detail per
 * function, then every 256th). Only cross-TU calls are wrapped (wasm-ld --wrap redirects undefined references), so
 * the intra-TU ones are seen through their cross-TU callees:
 *  - func_1507D4F8 (life lost: respawn / checkpoint restart / game over), its callee func_1501C710 (arguments);
 *  - func_1505D6F0 (record-vs-record contact pass): calls, and whether it moved the record (x / z before / after);
 *  - func_1508000C (floor-material effects, only called inside game_eu_AC770.c): seen through its sound calls
 *    func_1000D96C / func_1000DE1C (ambient loop ids 0x15..0x17, D_800D1CE4) and func_1000E7A0 / func_1000E8C4;
 *  - func_1507C170 (animation frame advance; called from game_eu_6CFB0.c): frame before / after, the end callback
 *    (anim +0), loops / holds. */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char D_800CC2D0[];
extern int D_800D1CE4;

#define REC 0x32C
static int fl = -1;
static int on(void) { if (fl < 0) fl = port_flag("p61check"); return fl; }
static int want(unsigned n) { return on() && (n <= (unsigned)fl || n % 256 == 0); }
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }
static int recno(const void *r) { return (int)(((const unsigned char *)r - D_800CC2D0) / REC); }

/* ---- func_1507D4F8 (life lost) and func_1501C710 */
static int in_d4f8;
void __real_func_1507D4F8(int idx);
void __wrap_func_1507D4F8(int idx) {
    static unsigned n;
    const unsigned char *r = D_800CC2D0 + idx * REC;
    float x = F(r, 0x14), y = F(r, 0x18), z = F(r, 0x1C);
    int st = *(const int *)r;
    n++;
    in_d4f8++;
    __real_func_1507D4F8(idx);
    in_d4f8--;
    if (want(n))
        port_log("[p61] func_1507D4F8 call %u frame %u: idx %d | state %d -> %d pos %.1f %.1f %.1f -> %.1f %.1f %.1f "
                 "+65 %02X +E4 %04X\n", n, port_frame_count, idx, st, *(const int *)r, x, y, z, F(r, 0x14), F(r, 0x18),
                 F(r, 0x1C), vbe_ld8(r + 0x65), vbe_ld16(r + 0xE4));
}
void __real_func_1501C710(int a0, int a1, int a2, int a3, int a4);
void __wrap_func_1501C710(int a0, int a1, int a2, int a3, int a4) {
    static unsigned n;
    n++;
    if (want(n))
        port_log("[p61] func_1501C710 call %u frame %u%s: a0 %d a1 %08X (%04X) a2 %d a3 %d a4 %d\n", n, port_frame_count,
                 in_d4f8 ? " (inside func_1507D4F8)" : "", a0, a1, a1 ? vbe_ld16((void *)(uintptr_t)a1) : 0, a2, a3, a4);
    __real_func_1501C710(a0, a1, a2, a3, a4);
}

/* ---- func_1505D6F0 (contact pass) */
void __real_func_1505D6F0(void *rec, int idx);
void __wrap_func_1505D6F0(void *rec, int idx) {
    static unsigned n, moved;
    const unsigned char *r = rec;
    float x = F(r, 0x14), z = F(r, 0x1C);
    n++;
    __real_func_1505D6F0(rec, idx);
    if (x != F(r, 0x14) || z != F(r, 0x1C)) moved++;
    if (want(n))
        port_log("[p61] func_1505D6F0 call %u frame %u: rec %d idx %d | x %.2f -> %.2f z %.2f -> %.2f | moved so far %u\n",
                 n, port_frame_count, recno(rec), idx, x, F(r, 0x14), z, F(r, 0x1C), moved);
}

/* ---- func_1508000C's sound calls */
void __real_func_1000D96C(int a0, int a1, int a2);
void __wrap_func_1000D96C(int a0, int a1, int a2) {
    static unsigned n;
    n++;
    if (want(n) || (a0 >= 0x15 && a0 <= 0x17 && on()))
        port_log("[p61] func_1000D96C (sound start) call %u frame %u: id %d (0x%X) %d %d | D_800D1CE4 %d\n", n,
                 port_frame_count, a0, a0, a1, a2, D_800D1CE4);
    __real_func_1000D96C(a0, a1, a2);
}
void __real_func_1000DE1C(int a0, int a1);
void __wrap_func_1000DE1C(int a0, int a1) {
    static unsigned n;
    n++;
    if (want(n) || (a0 >= 0x15 && a0 <= 0x17 && on()))
        port_log("[p61] func_1000DE1C (sound stop) call %u frame %u: id %d (0x%X) %d | D_800D1CE4 %d\n", n,
                 port_frame_count, a0, a0, a1, D_800D1CE4);
    __real_func_1000DE1C(a0, a1);
}
void __real_func_1000E7A0(unsigned a0, int a1);
void __wrap_func_1000E7A0(unsigned a0, int a1) {
    static unsigned n;
    n++;
    if (want(n)) port_log("[p61] func_1000E7A0 call %u frame %u: %u %d\n", n, port_frame_count, a0, a1);
    __real_func_1000E7A0(a0, a1);
}
void __real_func_1000E8C4(int a0);
void __wrap_func_1000E8C4(int a0) {
    static unsigned n;
    n++;
    if (want(n)) port_log("[p61] func_1000E8C4 call %u frame %u: %d\n", n, port_frame_count, a0);
    __real_func_1000E8C4(a0);
}

/* ---- P63 ?p63anim=N: per-call animation state of func_1507C170 (record 0's anim block): id (+4 low 15 bits,
 * 0x8000 hold), frame +8, speed +0x10, last frame +0x18, loop start +0x20, stream +0x28, previous id +6, blend step
 * +0x3A / countdown +0x3C, header bytes +0x40[3] (last) / [5] / [7]; marks LOOP (frame went back), END-CB (the end
 * callback window end-1 was crossed with a callback set) and NEW (id or stream changed inside the call = the callback
 * started another animation). N calls logged, then every 64th and every change of id. */
static int fl63 = -1;
extern unsigned char D_800CC69C_[] __asm__("D_800CC69C");
static void p63_anim_log(const unsigned char *a, float step, int rec, unsigned id0, unsigned s28, float f0, float last0,
                         unsigned cb) {
    static unsigned n, lastid = 0xFFFFFFFF, cbs, loops;
    unsigned id = vbe_ld16(a + 4);
    float f1 = F(a, 8);
    int crossed = cb && s28 && F(a, 0x10) >= 0 && f0 < last0 - 1.0f && (f1 >= last0 - 1.0f || f1 < f0);
    int changed = id != id0 || *(const unsigned *)(a + 0x28) != s28;
    if (fl63 < 0) fl63 = port_flag("p63anim");
    if (!fl63 || rec != 0) return;
    n++;
    if (crossed) cbs++;
    if (f1 < f0) loops++;
    if (n <= (unsigned)fl63 || n % 64 == 0 || id != lastid || changed || (crossed && cbs <= 16))
        port_log("[p63] anim call %u frame %u: id %04X prev %04X frame %.2f -> %.2f / last %.0f (loop %.0f) speed %.3f "
                 "step %.2f | +28 %08X blend step %d countdown %d | hdr[3] %02X [5] %02X [7] %02X | cb %08X%s%s%s "
                 "(loops %u cbs %u)\n", n, port_frame_count, id, vbe_ld16(a + 6), f0, f1, F(a, 0x18), F(a, 0x20),
                 F(a, 0x10), step, *(const unsigned *)(a + 0x28), (short)vbe_ld16(a + 0x3A),
                 (short)vbe_ld16(a + 0x3C), vbe_ld8(a + 0x43), vbe_ld8(a + 0x45), vbe_ld8(a + 0x47), cb,
                 f1 < f0 ? " LOOP" : "", crossed ? " END-CB" : "", changed ? " NEW" : "", loops, cbs);
    if (n <= (unsigned)fl63 || n % 64 == 0 || id != lastid || changed) {
        const unsigned char *r0 = D_800CC2D0;
        port_log("[p63]   rec 0: pos %.1f %.1f %.1f +28 %.2f xzv %.2f +44 %.2f | floor +184 %08X (slide class %u, kind %u) "
                 "+188 %08X +110 %d +162 %d D_800CC69C %d +83 %d +84 %04X | ctl +4E %02X +11A %02X\n",
                 F(r0, 0x14), F(r0, 0x18), F(r0, 0x1C), F(r0, 0x28), F(r0, 0x3C), F(r0, 0x44),
                 *(const unsigned *)(r0 + 0x184), (*(const unsigned *)(r0 + 0x184) >> 28) & 7,
                 (*(const unsigned *)(r0 + 0x184) >> 12) & 0xF, *(const unsigned *)(r0 + 0x188), vbe_ld8(r0 + 0x110),
                 vbe_ld8(r0 + 0x162), vbe_ld8(D_800CC69C_), vbe_ld8(r0 + 0x83), vbe_ld16(r0 + 0x84),
                 vbe_ld8(*(unsigned char **)(r0 + 0x31C) + 0x4E), vbe_ld8(*(unsigned char **)(r0 + 0x31C) + 0x11A));
    }
    lastid = id;
}


/* ---- P63: func_1505E650 (start animation `anim` of an object; game_83300.c, called from many TUs) under
 * ?p63anim: record 0's calls with id / speed / blend / frame / hold, logged when the id differs from the previous
 * call or every 64th; the first 3 calls of each new id get a JS stack (?p63stack=1). */
void port_js_stack(int skip, int n);
void __real_func_1505E650(void *obj, int id, float speed, float blend, float frame, float loop, int hold);
void __wrap_func_1505E650(void *obj, int id, float speed, float blend, float frame, float loop, int hold) {
    static unsigned n, last = 0xFFFFFFFF, same;
    static int stk = -1;
    if (fl63 < 0) fl63 = port_flag("p63anim");
    if (stk < 0) stk = port_flag("p63stack");
    if (fl63 && obj && recno(obj) == 0) {
        n++;
        if ((unsigned)(id & 0xFFFF) == last) same++;
        if ((unsigned)(id & 0xFFFF) != last || n % 64 == 0)
            port_log("[p63] start call %u frame %u: id %04X speed %.3f blend %.2f frame %.2f loop %.2f hold %d "
                     "(same id %u calls before) | rec y %.2f +28 %.2f +118 %.2f +20 %.2f xzv %.2f +44 %.2f +80 %d +81 %d +83 %d\n",
                     n, port_frame_count, id & 0xFFFF, speed, blend, frame, loop, hold,
                     (unsigned)(id & 0xFFFF) != last ? same : 0, F(obj, 0x18), F(obj, 0x28), F(obj, 0x118),
                     F(obj, 0x20), F(obj, 0x3C), F(obj, 0x44), vbe_ld8((unsigned char *)obj + 0x80),
                     vbe_ld8((unsigned char *)obj + 0x81), vbe_ld8((unsigned char *)obj + 0x83));
        if ((unsigned)(id & 0xFFFF) != last) {
            if (stk && n < 400) port_js_stack(1, 6);
            same = 0;
        }
        last = id & 0xFFFF;
    }
    __real_func_1505E650(obj, id, speed, blend, frame, loop, hold);
}


/* ---- P63 ?p63cb=N: proves that func_1507C170 calls the end-of-animation callback (anim +0) and with which argument:
 * for the first N end crossings of record 0's animation the callback word is swapped for p63cb_probe (logged with a
 * JS stack: the caller must be func_1507C170) and put back afterwards. DIAGNOSTIC: the game's own callback does
 * not run for those N calls (calling it from this non-vbe TU could trap on a signature mismatch). */
static unsigned p63cb_hits, p63cb_armed;
static void *p63cb_anim;
static void p63cb_probe(void *arg) {
    p63cb_hits++;
    port_log("[p63] END CALLBACK called (probe %u, frame %u): argument %08X (%s), game callback %08X skipped\n",
             p63cb_hits, port_frame_count, (unsigned)(uintptr_t)arg, arg == p63cb_anim ? "= the anim block" : "OTHER",
             p63cb_armed);
    port_js_stack(1, 4);
}
static int p63cb_arm(void *anim, unsigned cb) {
    static int fl = -1;
    const unsigned char *a = anim;
    if (fl < 0) fl = port_flag("p63cb");
    if (!fl || p63cb_hits >= (unsigned)fl || anim != (void *)(*(unsigned char **)(D_800CC2D0 + 0x2D0))) return 0;
    if (!(F(a, 0x10) >= 0 && F(a, 8) + F(a, 0x10) * 2.5f >= F(a, 0x18) - 1.0f)) return 0;  /* near the end only */
    p63cb_armed = cb;
    p63cb_anim = anim;
    *(unsigned *)anim = (unsigned)(uintptr_t)&p63cb_probe;
    return 1;
}
static void p63cb_disarm(void *anim, unsigned cb) {
    if (*(unsigned *)anim == (unsigned)(uintptr_t)&p63cb_probe) *(unsigned *)anim = cb;
}

/* ---- func_1507C170 (animation frame advance) */
void __real_func_1507C170(void *anim, float step, void *rec, int player);
void __wrap_func_1507C170(void *anim, float step, void *rec, int player) {
    static unsigned n, loops;
    const unsigned char *a = anim;
    unsigned cb = a ? *(const unsigned *)a : 0;
    float f0 = a ? F(a, 8) : 0;
    unsigned id0 = a ? vbe_ld16(a + 4) : 0, s28 = a ? *(const unsigned *)(a + 0x28) : 0;
    float last0 = a ? F(a, 0x18) : 0;
    n++;
    if (a && cb && p63cb_arm(anim, cb)) {
        __real_func_1507C170(anim, step, rec, player);
        p63cb_disarm(anim, cb);
    } else
        __real_func_1507C170(anim, step, rec, player);
    if (a) p63_anim_log(a, step, rec ? recno(rec) : -1, id0, s28, f0, last0, cb);
    if (a && F(a, 8) < f0) loops++;
    if (want(n) || (a && F(a, 8) < f0 && loops <= 8 && on()))
        port_log("[p61] func_1507C170 call %u frame %u: anim %08X step %g rec %d player %d | +28 %08X cb +0 %08X | "
                 "frame %g -> %g (+10 speed %g, +18 %g)%s\n", n, port_frame_count, (unsigned)(uintptr_t)anim, step,
                 rec ? recno(rec) : -1, player, a ? *(const unsigned *)(a + 0x28) : 0, cb, f0, a ? F(a, 8) : 0,
                 a ? F(a, 0x10) : 0, a ? F(a, 0x18) : 0, a && F(a, 8) < f0 ? " LOOP/END" : "");
}
