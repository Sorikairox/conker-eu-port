#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7450/func_151B9C40.s")

#ifdef NON_MATCHING
extern f32 D_800AA964;
extern f32 D_800AA968;
f32 func_150489B0(u8);
s32 func_151722BC(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_151B9F14(u8 *arg0) {
    f32 sp5C;
    s16 sp5A;
    s32 sp50;
    u8 sp4F;
    s16 temp_a1;
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v1;
    s32 var_v0;
    u8 temp_t9;

    temp_a2 = (*(s32 *)((u8 *)arg0 + 0x18));
    if (temp_a2 == 1) {
        temp_t9 = ((*(u8 *)((u8 *)arg0 + 0x3B)) + (D_800BE9E4 * 4) + (D_800BE9E4 * 2)) & 0xFF;
        (*(u8 *)((u8 *)arg0 + 0x3B)) = temp_t9;
        (*(s16 *)((u8 *)arg0 + 0x2A)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x2A)) * D_800AA964);
        sp50 = temp_a2;
        sp4F = temp_t9;
        sp5C = (f32) (*(s16 *)((u8 *)arg0 + 0x2A));
        (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) (s32) ((func_15048A40(temp_t9) + 3.0f) * sp5C * D_800AA968);
        (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) (s32) ((func_150489B0(sp4F) + 3.0f) * sp5C * D_800AA968);
    } else {
        temp_a1 = (*(s16 *)((u8 *)arg0 + 0x34));
        temp_a0 = (s32) (*(s32 *)((u8 *)arg0 + 0x14)) >> 0x10;
        if (temp_a0 != temp_a1) {
            var_v0 = temp_a1 - (D_800BE9E4 * 4);
            if (var_v0 < temp_a0) {
                var_v0 = temp_a0;
            }
            (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) var_v0;
            (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) var_v0;
        }
    }
    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x22));
    if ((s16) (*(s32 *)((u8 *)arg0 + 0x14)) >= temp_v0) {
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0;
        if (temp_a2 == 0) {
            sp5A = (s16) (*(s32 *)((u8 *)arg0 + 0x14));
            if ((func_150ADA20() & 0xFF) < 0x40) {
                func_151722BC((f32) (*(s16 *)((u8 *)arg0 + 0x20)), (f32) sp5A, (f32) (*(s16 *)((u8 *)arg0 + 0x24)), 0xA, 0, 0x13, 0.0f, 0, 0x32, 0xF, 0x100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
            if ((func_150ADA20() & 0xFF) < 0xF) {
                func_150ADA20();
                func_10010F88(0x70, 0x1388U, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x20)), (s16) (s32) sp5A, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x24)), 0x1F4, 0x7D0);
            }
        }
    } else {
        temp_v1 = temp_v0 - (s16) (*(s32 *)((u8 *)arg0 + 0x14));
        if (((*(s16 *)((u8 *)arg0 + 0x30)) < 0) && (temp_v1 < 0x40)) {
            (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (temp_v1 * 4);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7450/func_151B9F14.s")
#endif
void func_151BA1A0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB, s16 argC, s32 argD, u8 argE, s32 argF) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(7, argF, 0x2C, 0, (u8) (s32) argE, 1U);
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0x14)) = (s8) arg0;
        (*(s8 *)((u8 *)temp_v0 + 0x15)) = (s8) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x16)) = arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = arg3;
        (*(s16 *)((u8 *)temp_v0 + 0x1A)) = arg4;
        (*(s16 *)((u8 *)temp_v0 + 0x1C)) = arg5;
        (*(s16 *)((u8 *)temp_v0 + 0x1E)) = arg6;
        (*(s16 *)((u8 *)temp_v0 + 0x20)) = arg7;
        (*(s16 *)((u8 *)temp_v0 + 0x22)) = arg8;
        (*(s16 *)((u8 *)temp_v0 + 0x24)) = arg9;
        (*(s16 *)((u8 *)temp_v0 + 0x26)) = argA;
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = argB;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = argC;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = argD;
    }
}

#ifdef NON_MATCHING
void func_151B9C40(u8, u8, s16, s16, s16, s32, f32, s32, s32, s32, s32, s32, s32, s32, s32, u8, u8);

// burst_emitter_finish: emits the object's burst at its anchor (the f32 position at obj+0x10 if any, else the s16
// position at obj+0x16): obj+0x28 shots with the parameters at obj+0x1C..0x26, then 4 more with the first two
// widened (x1.5 / x2), all through func_151B9C40 (types obj+0x14 / 0x15, angle -80, spread 360, life 15). Then counts
// obj+0x2A down by the frame step D_800BE9E4 and frees the object when it goes negative (func_1516972C).
void func_151BA260(u8 *obj) {
    f32 *anchor = *(f32 **) (obj + 0x10);
    s16 x;
    s16 y;
    s16 z;
    s32 i;
    s32 t;

    if (anchor == NULL) {
        x = *(s16 *) (obj + 0x16);
        y = *(s16 *) (obj + 0x18);
        z = *(s16 *) (obj + 0x1A);
    } else {
        x = (s32) anchor[0];
        y = (s32) anchor[1];
        z = (s32) anchor[2];
    }
    for (i = 0; i < *(s16 *) (obj + 0x28); i++) {
        func_151B9C40(obj[0x14], obj[0x15], x, y, z, -0x50, 0.0f, 0x168, *(s16 *) (obj + 0x1C), *(s16 *) (obj + 0x1E),
                      *(s16 *) (obj + 0x20), *(s16 *) (obj + 0x22), 0xF, *(s16 *) (obj + 0x24), *(s16 *) (obj + 0x26),
                      obj[0xC], obj[1]);
    }
    for (i = 0; i < 4; i++) {
        func_151B9C40(obj[0x14], obj[0x15], x, y, z, -0x50, 0.0f, 0x168, (*(s16 *) (obj + 0x1C) * 3) / 2,
                      *(s16 *) (obj + 0x1E) * 2, *(s16 *) (obj + 0x20), *(s16 *) (obj + 0x22), 0xF,
                      *(s16 *) (obj + 0x24), *(s16 *) (obj + 0x26), obj[0xC], obj[1]);
    }
    t = *(s16 *) (obj + 0x2A) - D_800BE9E4;
    if (t < 0) {
        func_1516972C((struct102 *) obj);
    } else {
        *(s16 *) (obj + 0x2A) = t;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7450/func_151BA260.s")
#endif
