#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15036F60(u8 *arg0) {
    s32 i;

    *(f32 **)(arg0 + 0x324) = allocate_memory(0x48, 1, 0, 0);
    bzero(*(f32 **)(arg0 + 0x324), 0x48);
    for (i = 0; i < 3; i++) {
        (*(f32 **)(arg0 + 0x324))[i] = -99999.0f;
        (*(f32 **)(arg0 + 0x324))[i + 3] = -99999.0f;
    }
}

#ifdef NON_MATCHING
void func_15037CCC(f32 *, s32, s32, s32, f32, s32, s32);
void func_15038910(s32, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800C441A;
extern f32 D_800C4408[3];

/*
 * P65: per-frame callback of the current object D_800CC2D0[D_800C3E78] (called twice per frame for Conker).
 * D_800C441A counts the calls of this frame: the first call of a frame is skipped (only sets the counter to 1) for
 * object ids 0x3B / 0x75 / 0x80 / ... (jump table jtbl_80098604, a .late_rodata table: not code), when D_800C35EA == 1,
 * or when the record +0x324 still holds the -99999 "unset" x. Otherwise point D_800C4408 is filled by func_15037CCC
 * (or set to -99999 on a first call without D_800D154C->unk2F8 & 0x100) and passed to func_15038910.
 */
void func_15036FD8(void) {
    struct127 *obj = &D_800CC2D0[D_800C3E78];
    u8 *rec = obj->unk324;
    s32 kind;
    s32 first;
    s32 later;

    if (rec == NULL) {
        return;
    }
    switch (obj->id) {
        case 0x3B:
        case 0x75: case 0x80: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C:
        case 0x9D: case 0x9F: case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
            if (D_800C441A == 0) {
                D_800C441A = 1;
                return;
            }
            break;
    }
    if (D_800C35EA == 1 && D_800C441A == 0) {
        D_800C441A = 1;
        return;
    }

    first = FALSE;
    later = TRUE;
    if (D_800C441A == 0) {
        kind = 7;
        first = TRUE;
        later = FALSE;
        if (D_800D154C->unk2F8 & 0x100) {
            *(s16 *)(rec + 0x3A) = 0x2D;
            *(s16 *)(rec + 0x40) = 0x40;
        } else if (*(f32 *)rec == -99999.0f) {
            D_800C441A = 1;
            return;
        }
    } else {
        kind = 12;
    }

    if (D_800C441A == 0 && !(D_800D154C->unk2F8 & 0x100)) {
        D_800C4408[0] = -99999.0f;
        D_800C4408[1] = -99999.0f;
        D_800C4408[2] = -99999.0f;
    } else {
        func_15037CCC(D_800C4408, kind, 0, D_800C3E78, 90.0f, 0xFF, 0);
    }
    func_15038910(kind, 0, D_800C4408, D_800C3E78, first, 0, D_800C441A, 3, 0, 0, 0, later, 0);
    D_800C441A++;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15036FD8.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037988.s")
extern s32 D_800C4414;

s32 func_15037B70(s32 arg0, u8 *arg1) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t8;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    temp_t8 = temp_v0->unk2F8 & 7;
    if (temp_t8 == 1) {
        (*(f32 *)arg1) = (f32) D_800DBFF0->unk2F8;
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) D_800DBFF0->unk2FC;
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) D_800DBFF0->unk300;
        return 1;
    }
    if (temp_t8 == 2) {
        if (temp_v0->unk5 == 4) {
            temp_f0 = temp_v0->x_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
            temp_f2 = temp_v0->z_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
            if (62500.0f < ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
                return 1;
            }
        }
        (*(f32 *)arg1) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 2));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
        return 1;
    }
    if (temp_t8 == 3) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037CCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_150383B0.s")

#ifdef NON_MATCHING
extern f32 D_800989F8;
void func_15038758(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f0;

    switch (arg5) {                                 /* irregular */
    case 0:
        *arg0 = func_150484A0(arg2, arg4);
        var_f0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
block_9:
        *arg1 = var_f0;
        break;
    case 1:
        *arg0 = func_150484A0(-arg4, arg2);
        var_f0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 2:
        *arg0 = func_150484A0(arg4, -arg2);
        var_f0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 3:
        *arg0 = func_150484A0(arg4, -arg3);
        var_f0 = func_150484A0(-arg2, sqrtf((arg3 * arg3) + (arg4 * arg4)));
        goto block_9;
    }
    *arg0 *= D_800989F8;
    *arg1 *= D_800989F8;
    temp_f0 = *arg0;
    if (temp_f0 > 180.0f) {
        *arg0 = temp_f0 - 360.0f;
    }
    temp_f0_2 = *arg1;
    if (temp_f0_2 > 180.0f) {
    s32 pad;
        *arg1 = temp_f0_2 - 360.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15038758.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15038910.s")

void *func_15039D44(s32 arg0, s32 arg1) {
    return &D_80098418[arg1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15039D68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15039CC8.s")

#ifdef NON_MATCHING
s32 func_15039D68(f32 *, f32 *, f32 *, f32 *, f32, f32, s32);

void func_1503A1C0(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 var_f2;
    f32 var_f2_2;
    u8 *temp_v0;

    if (arg0 == 0) {
        func_15039D68(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return;
    }
    temp_v0 = func_15039D44(arg7, arg0);
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x10));
    temp_f0 = *arg1;
    if ((((*(f32 *)((u8 *)temp_v0 + 0)) + temp_f12) < temp_f0) || (var_f2 = (*(f32 *)((u8 *)temp_v0 + 4)), (temp_f0 < (var_f2 - temp_f12)))) {
        *arg1 = arg5;
        *arg2 = arg6;
        if (arg3 != NULL) {
            *arg3 = *arg1;
            *arg4 = *arg2;
        }
    } else {
        if (arg3 != NULL) {
            *arg3 = temp_f0;
            *arg4 = *arg2;
            var_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
        }
        if (*arg1 < var_f2) {

        } else {
            temp_f12_2 = (*(f32 *)((u8 *)temp_v0 + 0));
            if (temp_f12_2 < *arg1) {
                var_f2 = temp_f12_2;
            } else {
                var_f2 = *arg1;
            }
        }
        *arg1 = var_f2;
        temp_f12_3 = (*(f32 *)((u8 *)temp_v0 + 8));
        temp_f14 = (*(f32 *)((u8 *)temp_v0 + 0x14));
        temp_f0_2 = *arg2;
        if (((temp_f12_3 + temp_f14) < temp_f0_2) || (var_f2_2 = (*(f32 *)((u8 *)temp_v0 + 0xC)), (temp_f0_2 < (var_f2_2 - temp_f14)))) {
            *arg2 = arg6;
            return;
        }
        if (temp_f0_2 < var_f2_2) {

        } else if (temp_f12_3 < temp_f0_2) {
            var_f2_2 = temp_f12_3;
        } else {
            var_f2_2 = temp_f0_2;
        }
        *arg2 = var_f2_2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A1C0.s")
#endif
#ifdef NON_MATCHING
s32 func_1503DA64(s32 arg0, s32 arg1);
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *); /* s32: P59 definition returns 0 */
/* func_1503A37C (P57, from the m2c draft): object bounds from the skeleton. With a skeleton (+0x1D4) and a model
 * header D_800D1C90[type] (func_1503DA64(type, 0) == 0): joint header+0x26's matrix rows scaled to the header
 * radii (+0x3A u8, +0 s16, +0x30 s8) * y scale +0x150 give the box +0x1A4..+0x1B6 (s16) and the direction bytes
 * +0x1B8..+0x1BA; without: from the position, func_1507C7C0's height and header +0 * y scale. */
void func_1503A37C(struct127 *arg0) {
    u8 *temp_v0_2;
    u8 temp_v0;
    u8 temp_t4;
    struct124 *temp_v1_2;
    struct124 *temp_v1;
    s16 var_t0;
    s16 temp_v1_3;
    s16 temp_v0_3;
    s16 temp_a0;
    f32 var_f8;
    f32 var_f2_4;
    f32 var_f2_3;
    f32 var_f2_2;
    f32 var_f2;
    f32 var_f16;
    f32 var_f14;
    f32 var_f12;
    f32 temp_f6;
    f32 temp_f2;
    f32 temp_f18_4;
    f32 temp_f18_3;
    f32 temp_f18_2;
    f32 temp_f18;
    f32 temp_f16_3;
    f32 temp_f16_2;
    f32 temp_f16;
    f32 temp_f14_3;
    f32 temp_f14_2;
    f32 temp_f14;
    f32 temp_f12_3;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 temp_f0_5;
    f32 temp_f0_4;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp28;
    s32 sp2C;
    s16 sp32;
    s16 sp34;
    s16 sp36;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
    f32 sp50;
    f32 sp54;

    temp_v0 = ((u8 *)arg0)[4];
    if (temp_v0 != 0xFF) {
        if (((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) && (D_800D1C90[temp_v0] != NULL)) {
            if (func_1503DA64(temp_v0, 0) == 0) {
                temp_v1 = D_800D1C90[((u8 *)arg0)[4]];
                sp28 = (*(f32 *)((u8 *)arg0 + 0x150));
                temp_t4 = (*(u8 *)((u8 *)temp_v1 + 0x3A));
                temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x1D4)) + ((*(u8 *)((u8 *)temp_v1 + 0x26)) << 6);
                var_f8 = (f32) temp_t4;
                if ((s32) temp_t4 < 0) {
                    var_f8 += 4294967296.0f;
                }
                temp_f6 = var_f8 * sp28;
                sp48 = temp_f6;
                if (temp_f6 != 0.0f) {
                    temp_f12 = (*(f32 *)((u8 *)temp_v0_2 + 0));
                    temp_f14 = (*(f32 *)((u8 *)temp_v0_2 + 4));
                    temp_f16 = (*(f32 *)((u8 *)temp_v0_2 + 8));
                    temp_f18 = (temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16);
                    var_f2 = temp_f18;
                    if (temp_f18 != 0.0f) {
                        var_f2 = sqrtf(temp_f18);
                    }
                    if (var_f2 != 0.0f) {
                        var_f2 = sp48 / var_f2;
                    }
                    sp54 = temp_f12 * var_f2;
                    sp50 = temp_f14 * var_f2;
                    sp4C = temp_f16 * var_f2;
                } else {
                    sp4C = 0.0f;
                    sp50 = 0.0f;
                    sp54 = 0.0f;
                }
                temp_f18_2 = (f32) (*(s16 *)((u8 *)temp_v1 + 0)) * sp28;
                if (temp_f18_2 != 0.0f) {
                    temp_f12_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x10));
                    temp_f14_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x14));
                    temp_f16_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x18));
                    temp_f0 = sqrtf((temp_f12_2 * temp_f12_2) + (temp_f14_2 * temp_f14_2) + (temp_f16_2 * temp_f16_2));
                    var_f2_2 = temp_f0;
                    if (temp_f0 != 0.0f) {
                        var_f2_2 = temp_f18_2 / temp_f0;
                    }
                    sp44 = temp_f12_2 * var_f2_2;
                    sp40 = temp_f14_2 * var_f2_2;
                    sp3C = temp_f16_2 * var_f2_2;
                } else {
                    sp3C = 0.0f;
                    sp40 = 0.0f;
                    sp44 = 0.0f;
                }
                temp_f12_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x20));
                temp_f14_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x24));
                temp_f16_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x28));
                temp_f18_3 = (f32) (*(s8 *)((u8 *)temp_v1 + 0x30)) * sp28;
                if (temp_f18_3 != 0.0f) {
                    temp_f0_2 = sqrtf((temp_f12_3 * temp_f12_3) + (temp_f14_3 * temp_f14_3) + (temp_f16_3 * temp_f16_3));
                    var_f2_3 = temp_f0_2;
                    if (temp_f0_2 != 0.0f) {
                        var_f2_3 = temp_f18_3 / temp_f0_2;
                    }
                    temp_f0_3 = 127.0f / temp_f18_3;
                    var_f12 = temp_f12_3 * var_f2_3;
                    var_f14 = temp_f14_3 * var_f2_3;
                    var_f16 = temp_f16_3 * var_f2_3;
                    ((u8 *)arg0)[0x1B8] = (u8) (s32) (var_f12 * temp_f0_3);
                    ((u8 *)arg0)[0x1B9] = (u8) (s32) (var_f14 * temp_f0_3);
                    ((u8 *)arg0)[0x1BA] = (u8) (s32) (var_f16 * temp_f0_3);
                } else {
                    temp_f0_4 = sqrtf((temp_f12_3 * temp_f12_3) + (temp_f14_3 * temp_f14_3) + (temp_f16_3 * temp_f16_3));
                    var_f2_4 = temp_f0_4;
                    if (temp_f0_4 != 0.0f) {
                        var_f2_4 = 127.0f / temp_f0_4;
                    }
                    var_f14 = 0.0f;
                    var_f12 = 0.0f;
                    var_f16 = 0.0f;
                    ((u8 *)arg0)[0x1B8] = (u8) (s32) (temp_f12_3 * var_f2_4);
                    ((u8 *)arg0)[0x1B9] = (u8) (s32) (temp_f14_3 * var_f2_4);
                    ((u8 *)arg0)[0x1BA] = (u8) (s32) (temp_f16_3 * var_f2_4);
                }
                (*(s16 *)((u8 *)arg0 + 0x1A4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x30)) + var_f12);
                (*(s16 *)((u8 *)arg0 + 0x1A6)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x34)) + var_f14);
                (*(s16 *)((u8 *)arg0 + 0x1A8)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) + var_f16);
                temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A4));
                (*(s16 *)((u8 *)arg0 + 0x1AA)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x34)) + sp40);
                temp_f18_4 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A6));
                (*(s16 *)((u8 *)arg0 + 0x1AC)) = (s16) (s32) (temp_f2 + sp54 + sp44);
                temp_f0_5 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A8));
                (*(s16 *)((u8 *)arg0 + 0x1AE)) = (s16) (s32) (temp_f18_4 + sp50 + sp40);
                (*(s16 *)((u8 *)arg0 + 0x1B0)) = (s16) (s32) (temp_f0_5 + sp4C + sp3C);
                (*(s16 *)((u8 *)arg0 + 0x1B2)) = (s16) (s32) ((temp_f2 - sp54) + sp44);
                (*(s16 *)((u8 *)arg0 + 0x1B4)) = (s16) (s32) ((temp_f18_4 - sp50) + sp40);
                (*(s16 *)((u8 *)arg0 + 0x1B6)) = (s16) (s32) ((temp_f0_5 - sp4C) + sp3C);
            }
        } else {
            temp_v1_2 = D_800D1C90[temp_v0];
            if (temp_v1_2 != NULL) {
                var_t0 = *(s16 *)temp_v1_2;
            } else {
                var_t0 = 0;
            }
            sp2C = (s32) var_t0;
            func_1507C7C0(arg0, &sp36, &sp34, &sp32);
            (*(s16 *)((u8 *)arg0 + 0x1A4)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14));
            temp_v0_3 = (*(s16 *)((u8 *)arg0 + 0x1A4));
            ((u8 *)arg0)[0x2CA] = 0;
            (*(s16 *)((u8 *)arg0 + 0x1AC)) = (s16) temp_v0_3;
            (*(s16 *)((u8 *)arg0 + 0x1B2)) = (s16) temp_v0_3;
            (*(s16 *)((u8 *)arg0 + 0x1A6)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x18)) + (f32) ((s32) (sp36 * 7) / 8));
            (*(s16 *)((u8 *)arg0 + 0x1A8)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C));
            temp_a0 = (*(s16 *)((u8 *)arg0 + 0x1A8));
            (*(s16 *)((u8 *)arg0 + 0x1B0)) = (s16) temp_a0;
            (*(s16 *)((u8 *)arg0 + 0x1B6)) = (s16) temp_a0;
            (*(s16 *)((u8 *)arg0 + 0x1AA)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x1A6)) + ((f32) sp2C * (*(f32 *)((u8 *)arg0 + 0x150))));
            temp_v1_3 = (*(s16 *)((u8 *)arg0 + 0x1AA));
            (*(s16 *)((u8 *)arg0 + 0x1AE)) = (s16) temp_v1_3;
            (*(s16 *)((u8 *)arg0 + 0x1B4)) = (s16) temp_v1_3;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A37C.s")
#endif

void func_1503A8FC(void) {
    u8 *p;
    p = (u8 *)D_800CC2D0[D_800C3E78].unk1D4 + 0x40;
    *(f32 *)(p + 0x30) = *(f32 *)((u8 *)&D_800CC2D0[D_800C3E78] + 0x174);
    *(f32 *)(p + 0x34) = D_800CC2D0[D_800C3E78].y_position;
    *(f32 *)(p + 0x38) = *(f32 *)((u8 *)&D_800CC2D0[D_800C3E78] + 0x178);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A968.s")

s32 func_15037224();
s32 func_1503A968();
extern u8 D_800C441A;

void func_1503AAE0(void) {
    s32 sp1C;

    sp1C = D_800C441A;
    D_800C441A = 0;
    func_15037224();
    D_800C441A = sp1C;
    func_1503A968();
}

#ifdef NON_MATCHING
/* P65: head / eye aim state of an object (byte offsets; the struct127 field types there do not match the asm) */
#define LOOK_MODE(o)      (*(u8 *) ((u8 *) (o) + 0x276))
#define LOOK_PHASE(o)     (*(u16 *) ((u8 *) (o) + 0x278))
#define LOOK_ANGLE(o, i)  (((s16 *) ((u8 *) (o) + 0x27A))[i])  /* 0: -yaw1, 1: yaw0, 2: pitch1, 3: pitch0 */
#define LOOK_TIMER(o)     (*(u16 *) ((u8 *) (o) + 0x282))
#define LOOK_OFS(o, i)    (((s8 *) ((u8 *) (o) + 0x284))[i])   /* added to angles 0, 2, 1, 3 */

extern s32 D_800C43F0;      /* f32 x, y, z: default aim point */
extern u8 D_800C43FC;       /* one-shot: use D_800C4400 / D_800C4404 as the angles */
extern f32 D_800C4400;
extern f32 D_800C4404;
s32 func_150220CC(f32 *, f32 *, s32, s32);
f32 func_150489B0(u8);
u8 *func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);

/* move *cur toward target by at most step */
#define LOOK_STEP(cur, target, step)                         \
    {                                                        \
        s32 d_ = (target) - (cur);                           \
        if (((d_ < 0) ? -d_ : d_) < (step)) {                \
            (cur) = (target);                                \
        } else {                                             \
            (cur) = (cur) + (step) * ((d_ < 0) ? -1 : 1);    \
        }                                                    \
    }

/*
 * P65: head / eye aiming for the objects with a look joint (by id: Conker 0..4, 0x82, 0x96 use joint 12 and keep
 * D_800C43F0; others ask func_15037CCC for the target in D_800C4408). The joint matrix is made affine; while the
 * timer +0x282 runs, mode +0x276 animates the angles (0: circling offsets, 1: growing offsets, 2: aim at sub-model
 * 0x2B's point, 3: aim at joint +0x278, 4: nodding for model 0x26, 5: scaled offsets, 6: fixed pose); otherwise
 * the angles come from the target in joint space (atan2, in degrees), func_150220CC may override them, they are
 * clamped (yaw +-45, pitch -15..30), scaled by the per-id limits D_800D1C90[id] +0x2C..+0x2F and approached by
 * 8 (or 4 without target) per call in +0x27A..+0x280. UNVERIFIED parts: see P65.md.
 */
void func_1503AB20(struct127 *obj) {
    f32 *joint;
    u8 *sub;
    u8 *mtxs;
    u8 *limits;
    u8 id;
    s32 index;
    s32 jointNo;
    s32 lookFlags;
    s32 callTarget;
    s32 step;
    s32 aim;          /* compute the angles toward D_800C4408 */
    s32 aimAllowed;   /* cleared when mode 2 found its point */
    s32 useOffsets;   /* the angles are exactly the +0x284 offsets */
    s32 clamp;
    s32 mirror;       /* eye 1 copies eye 0 */
    s32 a, b, n;
    u16 phase;
    f32 k;
    f32 s, c;
    f32 yaw0, pitch0, yaw1, pitch1;
    f32 dx, dy, dz;
    f32 jx, jy, jz;
    f32 tYaw0, tYaw1, tPitch0, tPitch1;

    if (obj->unk1D4 == NULL) {
        return;
    }
    D_800C4408[0] = ((f32 *) &D_800C43F0)[0];
    D_800C4408[1] = ((f32 *) &D_800C43F0)[1];
    D_800C4408[2] = ((f32 *) &D_800C43F0)[2];

    id = obj->id;
    step = 8;
    lookFlags = 0x100;
    callTarget = TRUE;
    mirror = TRUE;
    clamp = TRUE;
    useOffsets = FALSE;
    aim = TRUE;
    aimAllowed = TRUE;
    switch (id) {
        case 0x9A:
            jointNo = 13;
            break;
        case 0x92:
        case 0x15:
        case 0x45:
            jointNo = 3;
            break;
        case 0x52:
            jointNo = 0;
            break;
        case 0x54:
            jointNo = 29;
            break;
        case 0x18:
        case 0x1E:
            jointNo = 2;
            if (id == 0x1E) {
                lookFlags = 0x22;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 0x82:
        case 0x96:
            jointNo = 12;
            callTarget = FALSE;
            break;
        default:
            return;
    }
    if (callTarget) {
        func_15037CCC(D_800C4408, jointNo, jointNo, obj - D_800CC2D0, 90.0f, lookFlags, 0);
    }

    index = obj - D_800CC2D0;
    joint = (f32 *) ((u8 *) D_800CC2D0[index].unk1D4 + jointNo * 64);
    joint[15] = 1.0f;
    joint[11] = 0.0f;
    joint[7] = 0.0f;
    joint[3] = 0.0f;
    yaw0 = 0.0f;
    pitch0 = 0.0f;

    if (LOOK_TIMER(obj) == 0) {
        LOOK_PHASE(obj) = 0;
        LOOK_OFS(obj, 0) = 0;
        LOOK_OFS(obj, 1) = 0;
        LOOK_OFS(obj, 2) = 0;
        LOOK_OFS(obj, 3) = 0;
    }
    if (LOOK_TIMER(obj) != 0) {
        aim = FALSE;
        switch (LOOK_MODE(obj)) {
            case 0:
                /* circling: remove last offsets, advance the two phase bytes, new offsets of radius 11 (fading in
                 * over the last 30 frames) */
                LOOK_ANGLE(obj, 0) -= LOOK_OFS(obj, 0);
                LOOK_ANGLE(obj, 2) -= LOOK_OFS(obj, 1);
                LOOK_ANGLE(obj, 1) -= LOOK_OFS(obj, 2);
                LOOK_ANGLE(obj, 3) -= LOOK_OFS(obj, 3);
                phase = LOOK_PHASE(obj);
                b = (phase >> 8) - D_800BE9E4 * 4;
                a = (phase & 0xFF) + D_800BE9E4 * 3;
                LOOK_PHASE(obj) = (b << 8) | a;
                k = (LOOK_TIMER(obj) < 30) ? LOOK_TIMER(obj) / 30.0f : 1.0f;
                k = 11.0f * k;
                s = func_15048A40(a & 0xFF);
                c = func_150489B0(a & 0xFF);
                LOOK_OFS(obj, 0) = s * k;
                LOOK_OFS(obj, 1) = c * k;
                s = func_15048A40(b & 0xFF);
                c = func_150489B0(b & 0xFF);
                LOOK_OFS(obj, 2) = s * k;
                LOOK_OFS(obj, 3) = c * k;
                break;
            case 1:
                if (LOOK_PHASE(obj) == 0) {
                    LOOK_PHASE(obj) = 1;
                    LOOK_OFS(obj, 3) += (u32) func_150ADA20() % 20;
                }
                n = (LOOK_TIMER(obj) < 0xAE) ? LOOK_TIMER(obj) / 6 + 1 : 30;
                LOOK_OFS(obj, 0) = 0;
                LOOK_OFS(obj, 1) += n;
                LOOK_OFS(obj, 3) += n;
                LOOK_OFS(obj, 2) = LOOK_OFS(obj, 0);
                useOffsets = TRUE;
                yaw0 = LOOK_OFS(obj, 0);
                pitch0 = LOOK_OFS(obj, 1);
                yaw1 = LOOK_OFS(obj, 2);
                pitch1 = LOOK_OFS(obj, 3);
                break;
            case 2:
                aim = TRUE;
                sub = func_15031C4C((u8 *) obj, 0x2B, 0);
                if (sub != NULL) {
                    mtxs = *(u8 **) (sub + 0x48);
                    if (mtxs != NULL && ((s32 *) (mtxs + 0x3E8))[D_800BE9C0] != 0) {
                        func_15043FF0((vertex *) D_800C4408,
                                      (struct113 *) (((s32 *) (mtxs + 0x3E8))[D_800BE9C0] + 0x80));
                        aimAllowed = FALSE;
                    }
                }
                break;
            case 3:
                /* aim at another joint of the model (the "none" test compares the u16 with -1: never true) */
                if (LOOK_PHASE(obj) != -1 && obj->unk1D4 != NULL) {
                    f32 *j = (f32 *) ((u8 *) obj->unk1D4 + LOOK_PHASE(obj) * 64);

                    D_800C4408[0] = j[12];
                    D_800C4408[1] = j[13];
                    D_800C4408[2] = j[14];
                }
                break;
            case 4:
                if (*(u16 *) ((u8 *) obj + 0x84) == 0x26) {
                    /* nod between -20 and 20 */
                    if (LOOK_PHASE(obj) == 0) {
                        LOOK_OFS(obj, 0) -= D_800BE9E4;
                        if (LOOK_OFS(obj, 0) < -20) {
                            LOOK_OFS(obj, 0) = -20;
                            LOOK_PHASE(obj) = 1;
                        }
                    } else {
                        LOOK_OFS(obj, 0) += D_800BE9E4 * 3;
                        if (LOOK_OFS(obj, 0) >= 21) {
                            LOOK_OFS(obj, 0) = 20;
                            LOOK_PHASE(obj) = 0;
                        }
                    }
                    LOOK_OFS(obj, 3) = 0;
                    LOOK_OFS(obj, 2) = LOOK_OFS(obj, 0);
                    LOOK_OFS(obj, 1) = LOOK_OFS(obj, 3);
                    useOffsets = TRUE;
                } else {
                    LOOK_TIMER(obj) = 0;
                    aim = TRUE;
                }
                break;
            case 5:
                yaw0 = LOOK_OFS(obj, 0) * 0.35433072f;
                yaw1 = LOOK_OFS(obj, 2) * 0.35433072f;
                pitch0 = LOOK_OFS(obj, 1) * 0.23622048f;
                clamp = FALSE;
                mirror = FALSE;
                pitch1 = LOOK_OFS(obj, 3) * 0.23622048f;
                break;
            case 6:
                if (*((u8 *) obj->unk31C + 0x78) == 0x2A) {
                    pitch0 = 30.0f;
                    yaw0 = -6.0f;
                    yaw1 = 6.0f;
                } else {
                    yaw0 = 0.0f;
                    yaw1 = 0.0f;
                    pitch0 = 0.0f;
                    if (LOOK_ANGLE(obj, 2) == 0) {
                        LOOK_MODE(obj) = 0;
                    }
                }
                mirror = FALSE;
                pitch1 = pitch0;
                break;
        }
        if (LOOK_TIMER(obj) != 0xFFFF) {
            if (LOOK_TIMER(obj) < D_800BE9E4) {
                LOOK_TIMER(obj) = 0;
            } else {
                LOOK_TIMER(obj) = LOOK_TIMER(obj) - D_800BE9E4;
            }
        }
    }

    if (aim) {
        if ((obj->unk2FB & 4) && aimAllowed) {
            yaw0 = 0.0f;
            pitch0 = 0.0f;
        } else if (D_800C4408[0] == -99999.0f && D_800C4408[1] == -99999.0f && D_800C4408[2] == -99999.0f) {
            step = 4;   /* no target: keep the angles, turn slowly */
        } else if (D_800C43FC != 0) {
            D_800C43FC = 0;
            yaw0 = D_800C4400;
            pitch0 = D_800C4404;
        } else {
            /* target relative to the joint, in joint space */
            dx = D_800C4408[0] - joint[12];
            dy = D_800C4408[1] - joint[13];
            dz = D_800C4408[2] - joint[14];
            jx = joint[2] * dz + (dx * joint[0] + dy * joint[1]);
            jy = joint[6] * dz + (dx * joint[4] + dy * joint[5]);
            jz = joint[10] * dz + (dx * joint[8] + dy * joint[9]);
            yaw0 = func_150484A0(jx, jz) * 57.29578f;
            pitch0 = func_150484A0(jy, sqrtf(jx * jx + jz * jz)) * 57.29578f;
            if (yaw0 > 180.0f) {
                yaw0 -= 360.0f;
            }
            if (pitch0 > 180.0f) {
                pitch0 -= 360.0f;
            }
        }
    }

    if (LOOK_TIMER(obj) == 0 && func_150220CC(&yaw0, &pitch0, index, 0) != 0) {
        clamp = TRUE;
        mirror = FALSE;
        useOffsets = FALSE;
        step = 8;
    }

    if (clamp) {
        if (yaw0 < -45.0f) {
            yaw0 = -45.0f;
        } else if (yaw0 > 45.0f) {
            yaw0 = 45.0f;
        }
        if (pitch0 < -15.0f) {
            pitch0 = -15.0f;
        } else if (pitch0 > 30.0f) {
            pitch0 = 30.0f;
        }
        if (yaw1 < -45.0f) {
            yaw1 = -45.0f;
        } else if (yaw1 > 45.0f) {
            yaw1 = 45.0f;
        }
        if (pitch1 < -15.0f) {
            pitch1 = -15.0f;
        } else if (pitch1 > 30.0f) {
            pitch1 = 30.0f;
        }
    }
    if (mirror) {
        pitch1 = pitch0;
        yaw1 = yaw0;
    }

    limits = (u8 *) D_800D1C90[id];
    if (limits == NULL) {
        return;
    }
    /* scale to the per-id limits: +0x2C / +0x2D yaw (one per side), +0x2E up, +0x2F down */
    tYaw0 = (yaw0 >= 0.0f) ? yaw0 * (s8) limits[0x2D] / 45.0f : yaw0 * (s8) limits[0x2C] / -45.0f;
    tYaw1 = (yaw1 >= 0.0f) ? yaw1 * (s8) limits[0x2C] / 45.0f : yaw1 * (s8) limits[0x2D] / -45.0f;
    tYaw1 = -tYaw1;
    tPitch0 = (pitch0 >= 0.0f) ? pitch0 * (s8) limits[0x2E] / 30.0f : pitch0 * (s8) limits[0x2F] / -15.0f;
    tPitch1 = (pitch1 >= 0.0f) ? pitch1 * (s8) limits[0x2E] / 30.0f : pitch1 * (s8) limits[0x2F] / -15.0f;

    LOOK_STEP(LOOK_ANGLE(obj, 0), (s32) tYaw1, step);
    LOOK_STEP(LOOK_ANGLE(obj, 1), (s32) tYaw0, step);
    LOOK_STEP(LOOK_ANGLE(obj, 2), (s32) tPitch1, step);
    LOOK_STEP(LOOK_ANGLE(obj, 3), (s32) tPitch0, step);

    if (useOffsets) {
        LOOK_ANGLE(obj, 0) = LOOK_OFS(obj, 0);
        LOOK_ANGLE(obj, 2) = LOOK_OFS(obj, 1);
        LOOK_ANGLE(obj, 1) = LOOK_OFS(obj, 2);
        LOOK_ANGLE(obj, 3) = LOOK_OFS(obj, 3);
    }
    if (LOOK_TIMER(obj) != 0 && LOOK_MODE(obj) == 0) {
        LOOK_ANGLE(obj, 0) += LOOK_OFS(obj, 0);
        LOOK_ANGLE(obj, 2) += LOOK_OFS(obj, 1);
        LOOK_ANGLE(obj, 1) += LOOK_OFS(obj, 2);
        LOOK_ANGLE(obj, 3) += LOOK_OFS(obj, 3);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503AB20.s")
#endif

s32 func_150383B0(u8 *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800C43F0;

void func_1503B9F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    (*(f32 *)((u8 *)arg0 + 0)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 4)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 8)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 0)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 4)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 8)) = -99999.0f;
    if (func_15037B70(arg3, arg0) == 0) {
        func_150383B0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    }
}
