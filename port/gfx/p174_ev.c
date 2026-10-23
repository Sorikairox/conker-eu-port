/* P174 DIAGNOSTIC ?p174ev=1 / PORT_P174EV=1: event-script queries / actions of the first room (level 0x22, event 0xCA
 * "First Death"). Wraps the VM natives func_150AE5F8 (native 5 = D_80088838 queries) and func_150AE60C (native 6 =
 * D_80088874 actions), reached through D_80088A44 (n64mem_tab refs -> --wrap applies). Logs every change of
 * (id, arg, result) per id, and every native-6 action. For table entry 0 (func_1509CBD8, scene queries) and entry 13 /
 * id 0x19 (func_1509DFCC, "no object in lists D_800A6440[0..2] has +0x48 == 2") it also computes what the asm answers.
 *
 * ?p174fix=1 everywhere, =2 only on level 0x22, =3 only inside event 0xCA (TEST, behind the flag): return the asm answer for those two handlers instead of the converted C's:
 *  - func_1509CBD8 (game_eu_CA060.c NON_MATCHING) is `void` and returns nothing; the asm returns 0 / 1 / D_800C3A92
 *    per case (jtbl_8009E828). Called through an s32 table, the port gets 0 for every scene query.
 *  - func_1509DFCC (game_eu_CA630.c NON_MATCHING) case 0x19/4 reads +0x48 of node->next (skips each list's first node
 *    and reads NULL+0x48 at the end); the asm reads +0x48 of every node. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../ultra/pc_mem.h"
typedef int32_t s32; typedef uint8_t u8; typedef uint16_t u16;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern u8 D_800C35C4, D_800C35EA, D_800C40B8, D_800C3A08, D_800C3A92;
extern u8 *D_800DD280[][104];
extern u8 D_800A6440[];
extern s32 D_800BE9F0;
static int on(void) { static int f = -1; if (f < 0) f = port_flag("p174ev"); return f; }
static int fixon(void) { static int f = -1; if (f < 0) f = port_flag("p174fix"); return f; }

static s32 asm_CBD8(s32 a0, s32 a1) {
    unsigned c4 = vbe_ld8(&D_800C35C4), ea = vbe_ld8(&D_800C35EA), sc = vbe_ld8(&D_800C40B8), s2 = vbe_ld8(&D_800C3A08);
    switch (a1) {
    case 1: if (c4) return 0; if (!ea) return 1; return (unsigned)a0 == sc ? 0 : 1;
    case 2: return ea == 1 && (unsigned)a0 == sc;
    case 3: return ea == 1 && (unsigned)a0 == s2;
    case 4: return ea != 1;
    case 5: return vbe_ld8(&D_800C3A92);
    case 6: return ea == 1 && (unsigned)a0 == s2;
    }
    return 0;
}
/* the asm walk of func_1509DFCC case 0x19 / 4 (every node's +0x48); logs the nodes when the summary changes */
static s32 asm_DFCC19(void) {
    static unsigned lastkey = ~0u;
    char buf[768]; int k = 0, r = 1; unsigned key = 2166136261u;
    buf[0] = 0;
    for (int g = 0; g < 2; g++)
        for (int i = 0; i < 3; i++) {
            unsigned li = *(unsigned *)(D_800A6440 + 4 * i);
            u8 *n = D_800DD280[g][li];
            int cnt = 0;
            while (n && cnt < 32) {
                unsigned st = vbe_ld8(n + 0x48);
                if (st == 2) r = 0;
                key = (key ^ (unsigned)(uintptr_t)n ^ (st << 24)) * 16777619u;
                if (k < 700) k += snprintf(buf + k, sizeof buf - k, "g%d/L%02X %08x s%u pos %.0f %.0f %.0f; ", g, li,
                                           (unsigned)(uintptr_t)n, st, *(float *)(n + 0x54), *(float *)(n + 0x58), *(float *)(n + 0x5C));
                n = *(u8 **)(n + 8); cnt++;
            }
        }
    static unsigned lastf;
    if (key != lastkey || port_frame_count - lastf >= 500) {
        lastkey = key; lastf = port_frame_count;
        port_log("[p174ev] frame %u lists 36/4C/5B: %s-> asm answer %d (null+0x48 byte %u)\n", port_frame_count,
                 buf[0] ? buf : "(empty) ", r, vbe_ld8((void *)0x48));
    }
    return r;
}

/* the running event block (func_150ADFD0 = event VM, called from game_C8950.c) */
static int cur_ev = -1;
void __real_func_150ADFD0(void *blk, s32 entry);
void __wrap_func_150ADFD0(void *blk, s32 entry) {
    int sv = cur_ev;
    /* blk is the script block (no id in it): tell the events of this route apart by their entry offsets +0x10 / +0x12
     * (ROM headers: CA 003E 0114, BF 00A0 01DC, CB 0190 01E0) */
    unsigned h8 = blk ? vbe_ld16((u8 *)blk + 0x10) : 0, h9 = blk ? vbe_ld16((u8 *)blk + 0x12) : 0;
    cur_ev = h8 == 0x3E && h9 == 0x114 ? 0xCA : h8 == 0xA0 && h9 == 0x1DC ? 0xBF : h8 == 0x190 && h9 == 0x1E0 ? 0xCB : 0x1000 | h8;
    __real_func_150ADFD0(blk, entry);
    cur_ev = sv;
}
/* native 5: D_80088838[n - 1](id & 0xFFFF0FFF, args[1], args) */
s32 __real_func_150AE5F8(s32 *args);
s32 __wrap_func_150AE5F8(s32 *args) {
    if (!on() && !fixon()) return __real_func_150AE5F8(args);
    s32 id = args[0], arg = args[1], n = (id & 0xF000) >> 12;
    s32 r = __real_func_150AE5F8(args), ra = r, fixed = 0;
    if (n == 1) { ra = asm_CBD8(id & 0xFFF, arg); }
    else if (n == 14 && (id & 0xFFF) == 0x19 && arg == 4) { ra = asm_DFCC19(); }
    /* p174fix=1: everywhere; p174fix=2: only on level 0x22 (keeps the port's route into the death room: with =1 the
     * intro event BF starts scene 3 of level 0x18 at 10725 and traps at 10733 in func_150623F4, NULL D_800D2104) */
    if (ra != r && (fixon() == 1 || (fixon() == 2 && D_800BE9F0 == 0x22) || (fixon() == 3 && cur_ev == 0xCA))) { fixed = 1; }
    if (on()) {
        /* one line per (id, arg) whenever its result (C or asm) changes */
        static s32 kid[64], karg[64], kr[64], kra[64]; static int nk; static unsigned nlog;
        s32 kk = id ^ (cur_ev << 20);
        int j; for (j = 0; j < nk; j++) if (kid[j] == kk && karg[j] == arg) break;
        if (j == nk && nk < 64) { kid[nk] = kk; karg[nk] = arg; kr[nk] = 0x7FFFFFFF; kra[nk] = 0x7FFFFFFF; nk++; }
        if (j < 64 && (kr[j] != r || kra[j] != ra) && nlog++ < 600) {
            port_log("[p174ev] frame %u ev %X q5 id %04X arg %d -> C %d asm %d%s (EA %u C4 %u scene 40B8 %u 3A08 %u 3A92 %u)\n",
                     port_frame_count, cur_ev, id & 0xFFFF, arg, r, ra, fixed ? " FIXED" : "", vbe_ld8(&D_800C35EA),
                     vbe_ld8(&D_800C35C4), vbe_ld8(&D_800C40B8), vbe_ld8(&D_800C3A08), vbe_ld8(&D_800C3A92));
            kr[j] = r; kra[j] = ra;
        }
    }
    return fixed ? ra : r;
}
/* native 6: game-state actions D_80088874[n - 1](id & 0xFFFF0FFF, args[1], args) */
s32 __real_func_150AE60C(s32 *args);
s32 __wrap_func_150AE60C(s32 *args) {
    s32 r = __real_func_150AE60C(args);
    if (on()) {
        static unsigned nlog; static s32 lid[64], la1[64]; static int nl;
        /* one line per (id, arg1) pair seen first (the menu's 0x2000 action runs every 4 retraces) */
        int j; for (j = 0; j < nl; j++) if (lid[j] == args[0] && la1[j] == args[1]) break;
        if (j == nl && nl < 64) { lid[nl] = args[0]; la1[nl] = args[1]; nl++; } else if (j < nl && (args[0] & 0xF000) == 0x2000) j = -1;
        if (j >= 0 && nlog++ < 400)
            port_log("[p174ev] frame %u act6 id %04X args %d %d %d -> %d\n", port_frame_count, args[0] & 0xFFFF, args[1],
                     args[2], args[3], r);
    }
    return r;
}

/* P174 ?p174ev: pointer probe before func_150619A8 (game_83300.c; it calls func_150623F4 per active object): the
 * pointers func_150623F4 dereferences (obj +0x144, D_800D2104[obj +0x13F] if D_800D2528[obj +0x13F], D_800D1C90[id]),
 * logged when outside the wasm memory (raw N64 addresses / garbage) - the trap at 10732 with ?p174fix (scene 3 of
 * level 0x18). Up to 40 lines. */
extern u8 D_800CC2D0[];
extern s32 *D_800D2104;
extern u8 *D_800D2528;
extern u8 *D_800D1C90[];
extern s32 D_80082FA0;
static int badp(unsigned p) { return p != 0 && (p < 0x1000 || p >= 0x16000000u); }
void __real_func_150619A8(void);
void __wrap_func_150619A8(void) {
    if (on()) {
        static unsigned nlog, nfr;
        if (port_frame_count >= 10731 && nfr < 16) {
            char b[1600]; int k = 0;
            for (int i = 0; i < 0x19; i++) { u8 *o = D_800CC2D0 + 0x32C * i; if (*(s32 *)o) k += snprintf(b + k, sizeof b - k, " %d:id%u/74=%x/13F=%u/on%u/p%08x", i, vbe_ld8(o + 4), vbe_ld8(o + 0x74), vbe_ld8(o + 0x13F), D_800D2528 ? vbe_ld8(D_800D2528 + vbe_ld8(o + 0x13F)) : 99, D_800D2104 ? (unsigned)D_800D2104[vbe_ld8(o + 0x13F)] : 0); }
            k += snprintf(b + k, sizeof b - k, " | D2528 %08x D2104 %08x", (unsigned)(uintptr_t)D_800D2528, (unsigned)(uintptr_t)D_800D2104);
            nfr++; port_log("[p174ptr] frame %u D_80082FA0 %d objs%s\n", port_frame_count, D_80082FA0, b);
        }
        for (int i = 0; i < 0x19 && nlog < 40; i++) {
            u8 *o = D_800CC2D0 + 0x32C * i;
            if (*(s32 *)o == 0) continue;
            unsigned id = vbe_ld8(o + 4), k = vbe_ld8(o + 0x13F), p144 = *(unsigned *)(o + 0x144);
            unsigned on2528 = D_800D2528 ? vbe_ld8(D_800D2528 + k) : 0xFFFF, p2104 = D_800D2104 ? (unsigned)D_800D2104[k] : 0;
            unsigned p1c90 = (unsigned)(uintptr_t)D_800D1C90[id];
            if (badp(p144) || badp(p1c90) || badp((unsigned)(uintptr_t)D_800D2528) || badp((unsigned)(uintptr_t)D_800D2104) ||
                (on2528 && on2528 != 0xFFFF && badp(p2104)))
                nlog++, port_log("[p174ptr] frame %u obj %d state %d id %u +144 %08x 13F %u D2528 %08x [%u] D2104 %08x [%08x] D1C90[id] %08x\n",
                                 port_frame_count, i, *(s32 *)o, id, p144, k, (unsigned)(uintptr_t)D_800D2528, on2528,
                                 (unsigned)(uintptr_t)D_800D2104, p2104, p1c90);
        }
    }
    __real_func_150619A8();
}
