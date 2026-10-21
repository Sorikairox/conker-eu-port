#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include "libc/math.h"


#ifdef NON_MATCHING
s32 allocate_memory(s32, s32, s32, s32);
s32 func_150006E0(s32);
s32 func_1501A8C0(s32, s32, s32, s32);
void func_1510B5F0(s32);
extern s8 D_800BEA34;
extern s8 D_800BEA37;
extern s32 D_800BEA4C;
extern s8 D_800BEA55;
extern s32 D_800BEA5C;
extern f32 D_800BEAD8;

void func_1501A220(s32 arg0, s32 arg1) {
    f32 temp_f0;
    s32 temp_f16;
    s32 temp_s1;
    s32 var_s0;
    s32 var_s0_2;

    D_80082FA0 = arg0;
    if (arg0 == 0) {
        var_s0 = 1;
    } else {
        var_s0 = arg0 + 2;
    }
    D_800BE628 = allocate_memory(var_s0 * 0x180, 1, 1, 0);
    D_800BEA4C = allocate_memory(var_s0 * 0x10, 1, 1, 0);
    if (D_80082FA0 == 1) {
        temp_f0 = (f32) D_800BEA5C - 2.0f;
        temp_f16 = (s32) (temp_f0 * 0.8f);
        D_800BEAD8 = (f32) (temp_f16 - (temp_f16 % 4)) / temp_f0;
    }
    func_150006E0(D_800BE9F0);
    temp_s1 = D_80082FA0;
    var_s0_2 = 0;
    if (temp_s1 >= 0) {
        do {
            func_1501A8C0(var_s0_2, temp_s1, 0x3FF, 0);
            var_s0_2 += 1;
        } while (D_80082FA0 >= var_s0_2);
    }
    if (temp_s1 != 0) {
        func_1501A8C0(var_s0_2, 0, 0x3FF, 0);
    }
    D_800BEA37 = 1;
    D_800BEA34 = 1;
    D_800BEA55 = 0;
    func_1510B5F0(arg1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A220.s")
#endif
// NON-MATCHING: 80% there
// void func_1501A220(s32 arg0, s32 arg1) {
//     s32 phi_s0;
//     s32 i;
//
//     f32 temp_f0;
//     s32 temp_f16;
//
//     D_80082FA0 = arg0;
//
//     if (arg0 == 0) {
//         phi_s0 = 1;
//     } else {
//         phi_s0 = arg0 + 2;
//     }
//     D_800BE628 = allocate_memory((phi_s0 * 3) << 7, 1, 1, 0);
//     D_800BE62C = allocate_memory(phi_s0 * 16, 1, 1, 0);
//     if (D_80082FA0 == 1) {
//         temp_f0 = D_800BE63C - 2.0f;
//         temp_f16 = temp_f0 * D_800968E0;
//         phi_s0 = temp_f16 & 3;
//         if ((temp_f16 < 0) && ((temp_f16 & 3) != 0)) {
//             phi_s0 -= 4;
//         }
//         D_800BE6B8 = (temp_f16 - phi_s0) / temp_f0;
//     }
//
//     func_150006E0(D_800BE9F0);
//
//     for(i = 0; i <= D_80082FA0; i++) {
//         func_1501A8C0(i, D_80082FA0, 1023, 0);
//     }
//     if (D_80082FA0 != 0) {
//         func_1501A8C0(i, 0, 1023, 0);
//     }
//
//     D_800BE617 = 1;
//     D_800BE614 = 1;
//     D_800BE635 = 0;
//     func_1510B070(arg1);
// }

void func_1501A39C(void) {
    s32 i;
    Gfx *gfx;

    for (i = 0; i < 2; i++) {
        gfx = D_800BEDE8[i];
        gSPSegment(gfx++, 0, 0);
        gSPSegment(gfx++, 0, 0);
        gSPDisplayList(gfx++, D_8002CC90);
        gDPSetDepthImage(gfx++, D_800BEDE4);
        gSPViewport(gfx++, &((struct_eu_BE628 *)D_800BE628)->unk40[i]);
        D_800BE9D8[i] = (s32)gfx;
    }
}
// NON-MATCHING: something along these lines
// extern Gfx* D_800BE9C8;
// extern s32 D_8002C930;
// Gfx *func_1501A39C(void) {
//     s32 i;
//     Gfx *tmp = D_800BE9C8;
//     for (i = 0; i < 3; i++) {
//         gSPSegment(tmp++, 0x00, 0x00000000);
//         gSPSegment(tmp++, 0x00, 0x00000000);
//         gSPDisplayList(tmp++, D_8002C930);
//         gDPSetDepthImage(tmp++, D_800BE9C4);
//         gSPViewport(tmp++, D_800BE628 + i + 0x40);
//     }
//     return tmp;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A490.s")

Gfx *func_1501A680(Gfx *arg0) {
    gDPSetColorImage(arg0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_800BE620, D_8002AAE8[D_800BE9C0]);
    return arg0;
}

Gfx *func_1501A6CC(Gfx *arg0, s32 a, s32 b, s32 c, s32 d) {
    if (a < 3) {
        a = 2;
    }
    if (b <= 0) {
        b = 0;
    }
    if (c >= (D_800BE620 - 2)) {
        c = D_800BE620 - 2;
    }
    if (d >= D_800BE624) {
        d = D_800BE624;
    }

    gDPFillRectangle(arg0++, a, b, c, d);
    return arg0;
}

void func_150A7A00(f32 arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32* arg6, f32* arg7, f32* arg8, f32* arg9);
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A764.s")
// void func_1501A764(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
//     f32 sp34;
//     f32 sp30;
//     f32 sp2C;
//     f32 sp28;
//     struct140 *temp_v0_2;
//
//     func_150A7A00(arg1, arg2, &D_800D9D10 + (arg0 << 6), arg1, arg2, arg3, &sp34, &sp30, &sp2C, &sp28);
//     sp28 = 1.0f / sp28;
//     // temp_v1 = arg0 * 0x180;
//     temp_v0_2 = &D_800BE628[arg0];
//     // sp28 = temp_f8;
//     *arg4 = (((temp_v0_2->unkC + 5.0f) * sp34 * sp28) + temp_v0_2->unk34);
//     temp_v0_2 = &D_800BE628 [arg0];
//     *arg5 = (temp_v0_2->unk38 - ((temp_v0_2->unk10 + 5.0f) * sp30 * sp28));
//     temp_v0_2 = &D_800BE628[arg0].unk50[D_800BE9C0];  // (D_800BE9C0 * 0x10);
//     *arg6 = (((f32) temp_v0_2->unk4C + (sp2C * sp28 * (f32) temp_v0_2->unk44)) * 32.0f);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A8C0.s")

s32 func_1501AE94(s32 arg0) {
    f32 w = (f32)D_800BE620 - 2.0f;
    f32 h = D_800BE624;
    struct_eu_BE628 *e = &((struct_eu_BE628 *)D_800BE628)[arg0];

    if (e->unk2C < 2.0f || w < e->unk30) {
        return 0;
    }
    if (e->unk24 < 0.0f || h < e->unk28) {
        return 0;
    }
    return 1;
}

void func_1501AF44(f32 *x0, f32 *y0, f32 *x1, f32 *y1) {
    f32 tmp;

    if (*x0 < 2.0f) {
        *x0 = 2.0f;
    } else {
        tmp = ((f32)D_800BE620 - 2.0f < *x0) ? (f32)D_800BE620 - 2.0f : *x0;
        *x0 = tmp;
    }
    if (*x1 < 2.0f) {
        *x1 = 2.0f;
    } else {
        tmp = ((f32)D_800BE620 - 2.0f < *x1) ? (f32)D_800BE620 - 2.0f : *x1;
        *x1 = tmp;
    }
    if (*y0 < 0.0f) {
        *y0 = 0.0f;
    } else {
        tmp = ((f32)D_800BE624 < *y0) ? (f32)D_800BE624 : *y0;
        *y0 = tmp;
    }
    if (*y1 < 0.0f) {
        *y1 = 0.0f;
    } else {
        tmp = ((f32)D_800BE624 < *y1) ? (f32)D_800BE624 : *y1;
        *y1 = tmp;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B0A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B22C.s")
// JUSTREG: I think?
// void func_1501B22C(s32 arg0) {
//     f32 tmp0;
//     f32 tmp1;
//     f32 tmp2;
//     f32 tmp3;
//     f32 tmp4;
//     f32 tmp5;
//     f32 tmp6;
//     f32 tmp7;
//
//     struct259 *temp_s0;
//
//     temp_s0 = D_800BE628 + (arg0 * 0x180);
//     tmp0 = temp_s0->unk74 * 0.5f;
//     tmp7 = -tmp0;
//     tmp5 = temp_s0->unk78 * 0.5f;
//     tmp7 *= D_80096900;
//     tmp3 = cosf(tmp7);
//     tmp7 = sinf(tmp7);
//     temp_s0->unk9C = tmp7;
//     temp_s0->unk90 = tmp7;
//     tmp3 = -tmp3;
//     temp_s0->unk88 = -tmp3;
//     temp_s0->unk94 = tmp3;
//     temp_s0->unk98 = 0.0f;
//     temp_s0->unk8C = 0.0f;
//     tmp6 = tmp5 * D_80096904;
//     tmp2 = cosf(tmp6);
//     tmp0 = sinf(tmp6);
//     tmp4 = -tmp2;
//     tmp0 = -tmp0;
//     temp_s0->unkA0 = 0.0f;
//     temp_s0->unkB0 = -tmp4;
//     temp_s0->unkA8 = tmp0;
//     temp_s0->unkB4 = tmp0;
//     temp_s0->unkAC = 0.0f;
//     temp_s0->unkA4 = tmp4;
// }
