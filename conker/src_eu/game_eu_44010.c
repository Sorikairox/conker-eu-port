#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void *allocate_memory(s32, s32, s32, s32);
u32 func_1502B8E0(u8 *, s32, s32, s32, s32);
s32 func_1502B9B4(s32, s32, s32);
s32 func_150170C4(s32);
u8 func_15084208(s32, s32);
void func_15082D5C(s32, s32, s32);
s32 func_15173218(s32);
extern u8 D_1A3750[];
extern u8 D_1A3840[];
extern u8 D_1A3B40[];
extern s32 D_800D1968;
extern u8 D_800D2521;
extern u8 *D_800D252C;
#endif


#ifdef NON_MATCHING
extern u8 D_800BE9B0;
extern u16 D_800BE9B8;
extern s32 D_800BE9C8;
extern u8 D_800D2520;

void func_15016800(void) {
    struct {
        s32 u50;
    } sp;
    s32 var_a1;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    u16 *var_v1_2;
    u8 temp_a2;
    u8 temp_s0;

    D_800BE9B0 = 0;
    temp_a2 = D_800D2520;
    sp.u50 = 0;
    var_s1 = 0;
    if ((s32) temp_a2 > 0) {
        do {
            var_a1 = 0;
            temp_s0 = D_800D20FC->pad4[var_s1];
            var_v0 = 0;
            if ((s32) D_800BE9B0 > 0) {
                var_v1_2 = &D_800BE9B8;
loop_4:
                var_v0 += 1;
                if (temp_s0 == *var_v1_2) {
                    var_a1 = 1;
                } else {
                    var_v1_2 += 2;
                    if (var_v0 < (s32) D_800BE9B0) {
                        goto loop_4;
                    }
                }
            }
            if (var_a1 != 0) {
                var_v1 = temp_a2 * 0x30;
            } else {
                if ((s32) temp_s0 < 0xBB) {
                    func_1502B7F0(&sp.u50, 2, 0x12, temp_s0);
                }
                var_v1 = temp_a2 * 0x30;
                if (sp.u50 != 0) {
                    *(s32 *)((u8 *)&D_800BE9C8 + (D_800BE9B0 * 4)) = sp.u50;
                    (&D_800BE9B8)[D_800BE9B0] = (u16) temp_s0;
                    D_800BE9B0 += 1;
                }
            }
            var_s1 += 0x30;
        } while (var_s1 < var_v1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_44010/func_15016800.s")
#endif
#ifdef NON_MATCHING
/* P36: level setup load (level arg0). DMAs the fixed player-slot setup table (ROM D_1A3840..D_1A3B40 for the
 * multiplayer-style levels 0x1A / 0x24 / 0x2B / 0x2D / 0x30 / 0x33 / 0x34 / 0x3F, else D_1A3750..D_1A3840) into
 * D_800D20FC (allocated with room for the level's setup asset (2, 0xE, level) from func_1502B9B4), D_800D2521 =
 * D_800D2520 = its entry count (0x30 bytes each), then appends the level's entries (func_1502B8E0) and counts them in
 * D_800D2520; func_150170C4(level); allocates + clears D_800D252C (spawned flags, 1 byte each) and D_800D2530 (respawn
 * timers, u16); D_800D1968 = 0. Each player slot i < D_8008FD8C enabled in the mask D_800D2340 gets e[2] = 0, a type
 * byte e[4] (and extra fields) from its character func_150859AC(i, 1), flag 0x4000000 in levels 0x32 / 0x33, and the
 * position / angle of object D_800CC2D0[i]; disabled slots get e[2] = 1. func_15016800(); entries with e[0x28] == 0
 * get func_15084208(count, i). Finally the player slots are spawned (func_15082D5C(level, 1, 1)), func_15173218(0),
 * then the other entries (func_15082D5C(level, 1, 0)). */
void func_15016950(s32 arg0) {
    u8 *tbl;
    u8 *tblEnd;
    u32 size;
    u32 n;
    s32 cnt;
    s32 i;
    s32 off;
    s32 ch;
    u8 *e;
    u8 *obj;

    func_15004F30();
    switch (arg0) {
        case 0x1A:
        case 0x24:
        case 0x2B:
        case 0x2D:
        case 0x30:
        case 0x33:
        case 0x34:
        case 0x3F:
            tbl = D_1A3840;
            tblEnd = D_1A3B40;
            break;
        default:
            tbl = D_1A3750;
            tblEnd = D_1A3840;
            break;
    }
    size = tblEnd - tbl;
    D_800D20FC = allocate_memory(func_1502B9B4(2, 0xE, arg0) + size, 1, 2, 0);
    func_10004514((s32) tbl, (void *) D_800D20FC, size, 1);
    n = size / 0x30;
    D_800D2520 = n;
    D_800D2521 = n & 0xFF;
    D_800D2520 += func_1502B8E0((u8 *) D_800D20FC + (n & 0xFF) * 0x30, 0, 2, 0xE, arg0) / 0x30;
    func_150170C4(arg0);
    cnt = D_800D2520;
    D_800D252C = allocate_memory(cnt, 1, 0, 0);
    D_800D2530 = allocate_memory(cnt * 2, 1, 0, 0);
    bzero(D_800D252C, cnt);
    bzero(D_800D2530, cnt * 2);
    D_800D1968 = 0;
    for (i = 0, off = 0; i < D_8008FD8C; i++, off += 0x30) {
        if (((1 << i) & (u16) D_800D2340) == 0) {
            ((u8 *) D_800D20FC)[off + 2] = 1;
            continue;
        }
        ch = func_150859AC((s16) i, 1);
        e = (u8 *) D_800D20FC + off;
        e[2] = 0;
        if ((u32) ch < 41) {
            switch (ch) {
                case 0:
                    if (D_800BE9F0 == 0x36 || D_800BE9F0 == 0x3A || D_800BE9F0 == 0x40) {
                        e[4] = 0x96;
                    } else {
                        e[4] = 0;
                    }
                    break;
                case 16:
                    e[4] = 0x96;
                    break;
                case 1:
                    e[4] = 0x3B;
                    break;
                case 2:
                    e[4] = 0x98;
                    break;
                case 3:
                    e[4] = 0x75;
                    break;
                case 4:
                    e[4] = 0x80;
                    break;
                case 37:
                    e[4] = 0xB0;
                    *(f32 *) (e + 0x24) = 0.6f;
                    *(f32 *) (e + 0x20) = *(f32 *) (e + 0x24);
                    break;
                case 38:
                    e[4] = 0xB1;
                    *(f32 *) (e + 0x24) = 0.6f;
                    *(f32 *) (e + 0x20) = *(f32 *) (e + 0x24);
                    break;
                case 39:
                    e[4] = 0xB2;
                    break;
                case 40:
                    e[4] = 0xB4;
                    break;
                case 33:
                    e[4] = 0x9F;
                    break;
                case 34:
                    e[4] = 0xA0;
                    break;
                case 11:
                    e[4] = 0x88;
                    break;
                case 35:
                    e[4] = 0x9B;
                    e[3] = 0x15;
                    break;
                case 36:
                    e[4] = 0x9A;
                    e[3] = 0x15;
                    break;
                case 17: case 18: case 19: case 20: case 21: case 22:
                case 23: case 24: case 25: case 26: case 27: case 28:
                    e[4] = 0x9C;
                    break;
                case 29: case 30: case 31: case 32:
                    e[4] = 0x9D;
                    break;
                case 12: case 13: case 14: case 15:
                    e[4] = 0x90;
                    if (i < D_80090130) {
                        e[3] = 1;
                    } else {
                        e[3] = 0xC;
                    }
                    *(s32 *) (e + 0x18) |= 4;
                    e[0xD] = 0xD;
                    break;
                case 8:
                    e[4] = 0x77;
                    e[3] = 0x1E;
                    e[0x10] = 0xAA;
                    if (i < D_80090130) {
                        e[0xD] = 1;
                    } else {
                        e[0xD] = 3;
                    }
                    *(s32 *) (e + 0x18) |= 0x180000;
                    e[0xE] |= 0x80;
                    break;
                case 10:
                    e[4] = 0x77;
                    e[3] = 0x25;
                    e[0x10] = 0xA8;
                    e[0xD] = 3;
                    *(s32 *) (e + 0x18) |= 0x100000;
                    break;
                case 9:
                    e[4] = 0x53;
                    e[3] = 0x1F;
                    e[0x10] = 0xA8;
                    e[0xD] = 2;
                    *(f32 *) (e + 0x20) = 0.7f;
                    *(f32 *) (e + 0x24) = 0.7f;
                    *(s32 *) (e + 0x18) |= 1;
                    break;
            }
        }
        if (D_800BE9F0 == 0x33 || D_800BE9F0 == 0x32) {
            *(s32 *) (e + 0x18) |= 0x4000000;
        }
        obj = (u8 *) D_800CC2D0 + i * 0x32C;
        *(s16 *) (e + 6) = (s32) *(f32 *) (obj + 0x14);
        *(s16 *) (e + 8) = (s32) *(f32 *) (obj + 0x18);
        *(s16 *) (e + 0xA) = (s32) *(f32 *) (obj + 0x1C);
        e[0xC] = *(u16 *) (obj + 0x76) >> 8;
    }
    func_15016800();
    for (i = 0, off = 0; i < D_800D2520; i++, off += 0x30) {
        if (((u8 *) D_800D20FC)[off + 0x28] == 0) {
            ((u8 *) D_800D20FC)[off + 0x28] = func_15084208(D_800D2520, i);
        }
    }
    func_15082D5C(arg0, 1, 1);
    func_15173218(0);
    func_15082D5C(arg0, 1, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_44010/func_15016950.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_44010/func_150170C4.s")
