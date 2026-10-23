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

void p103_frame(void) {
    static int lmode = -1, llevel = -1;
    int m = vbe_ld8(&D_800E0B94), l = D_800BE9F0;
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
    __real_func_1501D348(level, scene, slot, cb, cbarg);
}
