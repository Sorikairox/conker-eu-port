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

/* ---- func_1507C170 (animation frame advance) */
void __real_func_1507C170(void *anim, float step, void *rec, int player);
void __wrap_func_1507C170(void *anim, float step, void *rec, int player) {
    static unsigned n, loops;
    const unsigned char *a = anim;
    unsigned cb = a ? *(const unsigned *)a : 0;
    float f0 = a ? F(a, 8) : 0;
    n++;
    __real_func_1507C170(anim, step, rec, player);
    if (a && F(a, 8) < f0) loops++;
    if (want(n) || (a && F(a, 8) < f0 && loops <= 8 && on()))
        port_log("[p61] func_1507C170 call %u frame %u: anim %08X step %g rec %d player %d | +28 %08X cb +0 %08X | "
                 "frame %g -> %g (+10 speed %g, +18 %g)%s\n", n, port_frame_count, (unsigned)(uintptr_t)anim, step,
                 rec ? recno(rec) : -1, player, a ? *(const unsigned *)(a + 0x28) : 0, cb, f0, a ? F(a, 8) : 0,
                 a ? F(a, 0x10) : 0, a ? F(a, 0x18) : 0, a && F(a, 8) < f0 ? " LOOP/END" : "");
}
