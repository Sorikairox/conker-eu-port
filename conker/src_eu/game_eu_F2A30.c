#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150C5220(u8 *arg0) {
    f32 sp44;
    s32 sp38;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    f32 var_f2;
    s32 temp_f4;
    s32 var_v0;

    var_f0 = (*(f32 *)((u8 *)arg0 + 0));
    if (var_f0 > 180.0f) {
        var_f0 -= 360.0f;
    }
    var_v0 = (*(s32 *)((u8 *)arg0 + 0x7C)) + D_800BE9E4;
    temp_f12 = (f32) var_v0;
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x60)) - (var_f0 * 0.009f);
    if (temp_f12 >= 256.0f) {
        temp_f4 = (s32) (temp_f12 - 256.0f);
        sp44 = temp_f2;
        sp38 = temp_f4;
        func_10010F88(0xF, 0x55F0U, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x12)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x14)), 0x1F4, 0x3E8);
        var_v0 = temp_f4;
    }
    (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v0;
    sp44 = temp_f2;
    var_f2 = temp_f2 + (func_15048A40(var_v0 & 0xFF) * 0.1f);
    if (((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) == 4) {
        var_f2 += 0.1f;
    }
    temp_f2_2 = var_f2 * 0.8f;
    (*(f32 *)((u8 *)arg0 + 0x60)) = temp_f2_2;
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + temp_f2_2);
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
    if (temp_f0 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 - 360.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C5220.s")
#endif
#ifdef NON_MATCHING
u8 *allocate_memory(s32, s32, s32, s32);
s32 func_1510D66C(s32 *, s32 *, s32, s32);
void func_1510DDF4(s32, s32, s32, s32, s32);
s32 func_1511A998(s32, u8 *);
extern s32 D_1C0;
extern s32 D_2C1;

void func_150C539C(u8 *arg0) {
    struct {
        s32 u50;
        s32 * u54;
    } sp;
    s32 sp48;
    u8 *sp44;
    s32 sp40;
    f32 temp_f0;
    f32 temp_f0_2;
    s16 temp_t2;
    s16 temp_t7;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    u8 temp_t4;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_t0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x7C));
    temp_t6 = (*(u8 *)((u8 *)arg0 + 0x73)) & 3;
    var_v1 = temp_t6;
    if (temp_v0 == NULL) {
        sp40 = temp_t6;
        temp_v0_2 = allocate_memory(0x10, 1, 0, 0);
        (*(u8 **)((u8 *)arg0 + 0x7C)) = temp_v0_2;
        sp44 = temp_v0_2;
        func_1511A998((*(s32 *)((u8 *)arg0 + 0x1C)), temp_v0_2);
        var_t0 = sp44;
        var_v1 = sp40;
        (*(f32 *)((u8 *)var_t0 + 8)) = 0.0f;
        (*(s16 *)((u8 *)var_t0 + 4)) = (s16) (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x28))) + 0xA));
        (*(f32 *)((u8 *)var_t0 + 0xC)) = 0.0f;
    } else {
        var_t0 = temp_v0;
    }
    if ((var_v1 == 0) || (var_v1 == 2)) {
        sp.u54 = &D_2C1;
    } else {
        sp.u54 = &D_1C0;
    }
    if ((var_v1 == 0) || (var_v1 == 3)) {
        (*(f32 *)((u8 *)var_t0 + 8)) = 0.0f;
        (*(f32 *)((u8 *)var_t0 + 0xC)) = 0.0f;
    } else if (var_v1 == 2) {
        temp_f0 = (*(f32 *)((u8 *)var_t0 + 8));
        if (temp_f0 < 300.0f) {
            (*(f32 *)((u8 *)var_t0 + 8)) = (f32) (temp_f0 + (25.0f * (f32) D_800BE9E4));
        } else {
            (*(f32 *)((u8 *)var_t0 + 8)) = 300.0f;
        }
    } else if (var_v1 == 1) {
        temp_f0_2 = (*(f32 *)((u8 *)var_t0 + 8));
        if (temp_f0_2 > 100.0f) {
            (*(f32 *)((u8 *)var_t0 + 8)) = (f32) (temp_f0_2 - (25.0f * (f32) D_800BE9E4));
        } else {
            (*(f32 *)((u8 *)var_t0 + 8)) = 100.0f;
            temp_t8 = (s16) (*(s16 *)((u8 *)((*(u8 **)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20))) + 0xA)) % 1024;
            var_v1_2 = temp_t8;
            if (temp_t8 < 0) {
                do {
                    var_v1_2 += 0x400;
                } while (var_v1_2 < 0);
            }
            temp_t9 = (s16) (*(s16 *)((u8 *)var_t0 + 4)) % 1024;
            var_v0 = temp_t9;
            if (temp_t9 < 0) {
                do {
                    var_v0 += 0x400;
                } while (var_v0 < 0);
            }
            if ((var_v1_2 >= var_v0) && (((f32) var_v1_2 - (*(f32 *)((u8 *)var_t0 + 8))) <= (f32) var_v0)) {
                (*(f32 *)((u8 *)var_t0 + 8)) = (f32) (var_v1_2 - var_v0);
                temp_t4 = (*(u8 *)((u8 *)arg0 + 0x73)) & 0xFFFC;
                (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t4;
                (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) (temp_t4 | 3);
            }
        }
    }
    if ((*(f32 *)((u8 *)var_t0 + 8)) != 0.0f) {
        var_a0 = 0;
        var_v0_2 = 0;
        if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
            do {
                var_a0 += 1;
                temp_v1 = (*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20)) + var_v0_2;
                temp_t2 = (*(s16 *)((u8 *)temp_v1 + 0xA));
                var_v0_2 += 0x10;
                (*(s16 *)((u8 *)temp_v1 + 0xA)) = (s16) (s32) ((f32) temp_t2 - (*(f32 *)((u8 *)var_t0 + 8)));
            } while (var_a0 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
        }
    }
    if ((*(s16 *)((u8 *)((*(u8 **)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20))) + 0xA)) < -0x2800) {
        var_a0_2 = 0;
        var_v0_3 = 0;
        if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
            do {
                var_a0_2 += 1;
                temp_v1_2 = (*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20)) + var_v0_3;
                temp_t7 = (*(s16 *)((u8 *)temp_v1_2 + 0xA));
                var_v0_3 += 0x10;
                (*(s16 *)((u8 *)temp_v1_2 + 0xA)) = (s16) (temp_t7 + 0x2800);
            } while (var_a0_2 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
        }
    }
    sp48 = 0;
    sp44 = var_t0;
    temp_v0_3 = func_1510D66C(sp.u54, &sp.u50, 3, 0);
    var_a2 = sp48;
    if ((*(s32 *)((u8 *)sp44 + 0)) != 0) {
        var_a2 = (sp.u50 + temp_v0_3) - 0x200;
    }
    func_1510DDF4(arg0, temp_v0_3, var_a2, 4, 5);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C539C.s")
#endif
extern struct102 *D_800D9CF0[];
void func_150C572C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_800D9CF0[i] != 0) {
            func_1516972C(D_800D9CF0[i]);
        }
        D_800D9CF0[i] = 0;
    }
}

s32 func_150C5780(void) {
    if ((D_800C35EA == 1) && ((D_800C3A08 == 0xB) || (D_800C3A08 == 0xC) || (D_800C3A08 == 0xD))) {
        return 1;
    }
    return 0;
}

s32 func_150C5780(void);

s32 func_150C57CC(s32 arg0) {
    if (func_150C5780() != 0) {
        return 0;
    }
    return D_8008B148(arg0);
}

s32 func_150C5780();

s32 func_150C5810(u8 *arg0) {
    if (func_150C5780() != 0) {
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x60)) | 0x20000);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x60)) & 0xFFFDFFFF);
    }
    return 1;
}
