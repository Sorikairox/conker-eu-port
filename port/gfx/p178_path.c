/* P178 TEST ?p178fix=1 / PORT_P178FIX=1 (log only: ?p178ev=1): C body for the asm stub func_150170C4
 * (game_eu_44010.c GLOBAL_ASM), the only writer of D_800D2104 (EU 0x800D2524) and D_800D2528 (EU 0x800D2528) in the
 * whole ELF (port_work/p178/stscan.py). Called by func_15016950 (level setup load) after the spawn records
 * D_800D20FC[0..D_800D2520) are built (D_800D2521 = number of fixed player-slot records at the front).
 *
 * level_load_spawn_paths: per spawn record i, D_800D2104[i] = pointer to its path (s16[4] points: the readers in
 * game_A28B0.c / game_83300.c use +4/+5/+6 = x/y/z) and D_800D2528[i] = point count.
 *  - both tables allocated (arena 0) and cleared, one entry per record;
 *  - the first D_8008FD8C (player) records get a fresh cleared 0x10-byte path (arena 2), count 2;
 *  - level asset (2, 0x10, level) = 8-byte entries {s32 offset, s32 count} for the level's own records
 *    (record D_800D2521 + j uses entry j); offset 0 = no path; else path = asset + offset, count = low byte.
 * Written from the asm (EU 0x150170C4..0x150172A4). The asm leaves v0 = garbage; the caller ignores it. */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../ultra/pc_mem.h"
typedef int32_t s32; typedef uint8_t u8; typedef int8_t s8;
int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern s32 *D_800D2104;
extern u8 *D_800D2528;
extern u8 D_800D2520, D_800D2521;
extern s8 D_8008FD8C;
void *allocate_memory(s32, s32, s32, s32);
s32 func_1502B7F0(s32 *, s32, ...);
s32 __real_func_150170C4(s32);

static s32 c_150170C4(s32 level) {
    s32 asset = 0;
    unsigned n = vbe_ld8(&D_800D2520), i, first;
    s32 players = (s8)vbe_ld8(&D_8008FD8C);
    D_800D2104 = (s32 *)allocate_memory(n * 4, 1, 0, 0);
    D_800D2528 = (u8 *)allocate_memory(n, 1, 0, 0);
    bzero(D_800D2104, n * 4);
    bzero(D_800D2528, n);
    for (i = 0; (s32)i < players; i++) {
        D_800D2104[i] = (s32)(uintptr_t)allocate_memory(0x10, 1, 2, 0);
        bzero((void *)(uintptr_t)D_800D2104[i], 0x10);
        vbe_st8(D_800D2528 + i, 2);
    }
    if (func_1502B7F0(&asset, 2, 0x10, level) == 0) return 0;
    first = vbe_ld8(&D_800D2521);
    for (i = first; i < vbe_ld8(&D_800D2520); i++) {
        s32 *e = (s32 *)(uintptr_t)(asset + (s32)(i - first) * 8);
        if (e[0] != 0) {
            vbe_st8(D_800D2528 + i, (unsigned)e[1]);
            D_800D2104[i] = e[0] + asset;
        }
    }
    return 0;
}

s32 __wrap_func_150170C4(s32 level) {
    static int fx = -1, ev = -1;
    s32 r;
    if (fx < 0) fx = port_flag("p178fix"), ev = port_flag("p178ev");
    r = fx ? c_150170C4(level) : __real_func_150170C4(level);
    if (fx || ev) {
        unsigned n = vbe_ld8(&D_800D2520), i;
        char b[900]; int k = 0;
        b[0] = 0;
        for (i = 0; i < n && k < 800; i++) {
            unsigned c = D_800D2528 ? vbe_ld8(D_800D2528 + i) : 0;
            s32 p = D_800D2104 ? D_800D2104[i] : 0;
            if (c || p) {
                k += snprintf(b + k, sizeof b - k, " %u:%u@%08x", i, c, (unsigned)p);
                if (p && c) {
                    const s32 *w = (const s32 *)(uintptr_t)p;
                    k += snprintf(b + k, sizeof b - k, "(%d,%d,%d,%d)", (int16_t)vbe_ld16((const u8 *)w), (int16_t)vbe_ld16((const u8 *)w + 2), (int16_t)vbe_ld16((const u8 *)w + 4), (int16_t)vbe_ld16((const u8 *)w + 6));
                }
            }
        }
        port_log("[p178path] frame %u level 0x%x %s: records %u (fixed %u) players %d D2104 %08x D2528 %08x;%s\n",
                 port_frame_count, (unsigned)level, fx ? "C" : "stub", n, vbe_ld8(&D_800D2521), (s8)vbe_ld8(&D_8008FD8C),
                 (unsigned)(uintptr_t)D_800D2104, (unsigned)(uintptr_t)D_800D2528, b);
    }
    return r;
}
