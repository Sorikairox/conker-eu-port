#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151046F0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = node_alloc(0x64, 0, 0x20, 0, 0xFFU, 1U);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = 0xC;
        (*(s8 *)((u8 *)temp_v0 + 0x1A)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 0x1B)) = 0;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s32 *)((u8 *)temp_v0 + 0x14)) = arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x1C)) = (s8) arg0;
    }
}

#ifdef NON_MATCHING
extern s8 D_800BEE2C;

void func_15104764(struct102 *arg0) {
    u8 *sp34;
    u8 *sp30;
    u8 *sp28;
    s32 sp24;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 var_a0;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 temp_v0;
    u8 temp_v1;

    temp_v0 = arg0->pad1A[0];
    switch (temp_v0) {                              /* irregular */
    case 0:
        temp_v1 = (*(u8 *)((u8 *)arg0 + 0x1C));
        var_a0 = 0;
        if (temp_v1 == 0) {
            if ((*(f32 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x10))) + 0x2D0))) + 8)) >= 19.0f) {
                goto block_11;
            }
        } else if (temp_v1 == 1) {
            temp_v0_2 = (*(u16 *)((u8 *)arg0 + 0x18));
            if (D_800BE9E4 < (s32) temp_v0_2) {
                (*(u16 *)((u8 *)arg0 + 0x18)) = (u16) (temp_v0_2 - D_800BE9E4);
            } else {
block_11:
                var_a0 = 1;
            }
        }
        if (var_a0 != 0) {
            sp34 = (*(u8 **)((u8 *)arg0 + 0x14));
            sp30 = (*(u8 **)((u8 *)arg0 + 0x10));
            arg0->pad1A[0] = 1;
            D_800BEE2C = 1;
            func_100176C4();
            func_10010F30(0x5B2, 0x7FFFU, 0U, 0, 0U);
            func_10010F30(0x5B2, 0x7FFFU, 0x7FU, -0x64, 0U);
            func_10010F30(0x5B2, 0x7FFFU, 0U, 0, 0U);
            func_10010F30(0x5B2, 0x7FFFU, 0x7FU, -0x64, 0U);
            func_151D6CA0(0xD2, 2);
            camera_set_followed_obj((*(u8 **)((u8 *)sp30 + 0x318)), (*(u8 *)((u8 *)sp34 + 0x13F)));
            (*(f32 *)((u8 *)((*(u8 **)((u8 *)sp30 + 0x318))) + 0x674)) = 0.0f;
            return;
        }
        return;
    case 1:
        temp_v0_3 = arg0->pad1A[1] + (D_800BEA08 * 0xA);
        if (temp_v0_3 >= 0xFF) {
            arg0->pad1A[1] = 0xFF;
            arg0->pad1A[0] = 2;
            (*(u16 *)((u8 *)arg0 + 0x18)) = 0x96U;
            return;
        }
        arg0->pad1A[1] = (u8) temp_v0_3;
        return;
    case 2:
        temp_v0_4 = (*(u16 *)((u8 *)arg0 + 0x18));
        if (D_800BEA08 < (s32) temp_v0_4) {
            (*(u16 *)((u8 *)arg0 + 0x18)) = (u16) (temp_v0_4 - D_800BEA08);
            return;
        }
        D_800BEE2C = 0;
        sp28 = (*(u8 **)((u8 *)arg0 + 0x10));
        func_1000E2F4(0, arg0);
        camera_set_followed_obj((*(u8 **)((u8 *)sp28 + 0x318)), (*(u8 *)((u8 *)sp28 + 0x13F)));
        (*(f32 *)((u8 *)((*(u8 **)((u8 *)sp28 + 0x318))) + 0x674)) = 0.0f;
        arg0->pad1A[0] = 3;
        return;
    case 3:
        temp_v0_5 = arg0->pad1A[1] - (D_800BEA08 * 0xA);
        if (temp_v0_5 <= 0) {
            node_destroy(arg0);
            func_151D6CA0(0, 0);
            return;
        }
        sp24 = temp_v0_5;
        func_151D6CA0((s32) (temp_v0_5 * 0xD2) >> 8, 2, arg0);
        arg0->pad1A[1] = (u8) temp_v0_5;
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_15104764.s")
#endif
#ifdef NON_MATCHING
Gfx *func_1517F5FC(Gfx *gfx, s32 a, s32 r, s32 g, s32 b, s32 i);
#endif

#ifdef NON_MATCHING
// obj_fog_alpha_gfx: with i == 0 and a non-zero alpha byte at obj +0x1B, appends func_1517F5FC's colour command
// (alpha * 63 / 256, colour 0, 0, 0, index 0) to gfx; returns the new display list end (gfx unchanged otherwise).
Gfx *func_15104A0C(Gfx *gfx, u8 *obj, s16 i) {
    if (i == 0 && obj[0x1B] != 0) {
        return func_1517F5FC(gfx, (obj[0x1B] * 63) >> 8, 0, 0, 0, i);
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_15104A0C.s")
#endif

s32 func_151044F4(void) {
    u8 *temp_v1 = D_800CCA0C;
    s32 ret = 0;

    if (temp_v1 != NULL) {
        return temp_v1[0x7D];
    }
    return ret;
}
