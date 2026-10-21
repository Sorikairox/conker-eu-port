#include <ultra64.h>
#include "functions.h"
#include "variables.h"


Gfx *func_151ED998(Gfx *gdl);
void func_15042D94(s32, s32, s32, void *);
extern Gfx *(*D_800903A4[])(Gfx *);
extern u8 D_800BEB60;

Gfx *func_151E8C60(Gfx *gdl) {
    s32 msg;
    Gfx *(*fn)(Gfx *);

    D_8003C8E0 = 0x09000001;
    msg = 0;
    gdl = func_151ED998(gdl);
    fn = D_800903A4[D_800E0B94];
    if (fn != NULL) {
        gdl = fn(gdl);
    }
    if (D_80000300 == 0) {
        if (D_800BE616 != 0 && D_80090130 >= 2) {
            if ((D_800BEB60 & 0xF) == 0) {
                if (D_800E1003 == 1) {
                    msg = 0x33;
                } else if (D_800E1003 == 2) {
                    msg = 0x16;
                }
            }
        } else if ((D_800BEB60 & 1) == 0) {
            if (D_800E1003 == 1) {
                msg = 0x32;
            } else if (D_800E1003 == 2) {
                msg = 0x15;
            }
        }
    }
    if (msg != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x94, 0xC8, 0x81, ((void **)D_800E1008)[msg]);
    }
    D_8003C8E0 = 0;
    return gdl;
}

extern Gfx *(*D_80090370[])(Gfx *);
extern s32 D_80090408;
extern s32 D_800BEFC4;
extern s16 D_800E10A8;
Gfx *func_151E8620(Gfx *arg0) {
    Gfx *(*temp_a1)(Gfx *);
    Gfx *temp_a2;
    s32 var_v0;
    u8 temp_v1;
    temp_v1 = D_800E0B94;
    temp_a2 = arg0;
    D_8003C8E0 = 0x09000000;
    temp_a1 = D_80090370[temp_v1];
    if (temp_a1 != NULL) {
        arg0 = temp_a1(arg0);
    }
    if (D_800E0B94 != 0) {
        D_80090408 = 0;
        D_800E10A8 = 0;
    }
    D_8003C8E0 = 0;
    if (D_800BEFC4 < (arg0 - D_800BEDE8[D_800BE9C0])) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        return temp_a2;
    }
    return arg0;
}

#ifdef NON_MATCHING
extern f32 D_800901BC;
extern f32 D_800901C0;

u8 *func_151E8E94(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s16 var_t1_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_a2;
    s32 var_t1_3;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_a0;
    u8 *temp_a0_2;

    var_a2 = arg2;
    if (D_800901BC != 1.0f) {
        arg1 = (s32) ((f32) arg1 * D_800901BC);
        arg3 = (s32) ((f32) arg3 * D_800901BC);
        var_a2 = (s32) ((f32) var_a2 * D_800901C0);
        arg4 = (s32) ((f32) arg4 * D_800901C0);
        arg8 = (s32) ((f32) arg8 / D_800901BC);
        arg9 = (s32) ((f32) arg9 / D_800901C0);
    }
    temp_a0_2 = arg0 + 8;
    if ((s16) arg3 > 0) {
        var_t0 = (s16) arg3;
    } else {
        var_t0 = 0;
    }
    if ((s16) arg4 > 0) {
        var_t1 = (s16) arg4;
    } else {
        var_t1 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = (s32) ((var_t1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
    if ((s16) arg1 > 0) {
        var_t0_2 = (s16) arg1;
    } else {
        var_t0_2 = 0;
    }
    if ((s16) var_a2 > 0) {
        var_t1_2 = (s16) var_a2;
    } else {
        var_t1_2 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((var_t1_2 & 0xFFF) | ((arg5 & 7) << 0x18) | ((var_t0_2 & 0xFFF) << 0xC));
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE1000000;
    temp_a0 = temp_a0_2 + 8;
    if ((s16) arg1 < 0) {
        if ((s16) arg8 < 0) {
            temp_t5 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t5 > 0) {
                var_t2 = temp_t5;
            } else {
                var_t2 = 0;
            }
        } else {
            var_v0 = 0;
            temp_t4 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t4 < 0) {
                var_v0 = temp_t4;
            }
            var_t2 = var_v0;
        }
    } else {
        var_t2 = 0;
    }
    if (var_a2 < 0) {
        if ((s16) arg9 < 0) {
            temp_t7 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t7 > 0) {
                var_t1_3 = temp_t7;
            } else {
                var_t1_3 = 0;
            }
        } else {
            var_v0_2 = 0;
            temp_t6 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t6 < 0) {
                var_v0_2 = temp_t6;
            }
            var_t1_3 = var_v0_2;
        }
    } else {
        var_t1_3 = 0;
    }
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) (((arg7 - var_t1_3) & 0xFFFF) | ((arg6 - var_t2) << 0x10));
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xF1000000;
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((arg8 << 0x10) | (arg9 & 0xFFFF));
    return temp_a0 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8E94.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA4C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA90C.s")

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E8E94(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090424;
extern s32 D_8009044C;

u8 *func_151EB5AC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        s32 u7C;
        u8 pad80[0x14];
        s32 u94;
    } sp;
    s32 *var_s1;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *var_s0;

    var_s0 = arg0;
    var_s3 = arg3;
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0xC)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0xC));
    (*(s32 *)((u8 *)(&sp.u7C) + 0x10)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x10));
    temp_t4 = arg2 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x18)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x18));
    var_s2 = arg1 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x14)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x14));
    if (var_s3 >= 0x989680) {
        var_s3 = 0x98967F;
    }
    var_s4 = 0;
    if (var_s3 < 0) {
        var_s3 = 0;
    }
    var_s1 = &sp.u94;
    do {
        temp_v0 = *var_s1;
        temp_v1 = var_s3 / temp_v0;
        var_s3 = var_s3 % temp_v0;
        if ((temp_v1 > 0) || (var_s4 != 0) || (var_s1 == &sp.u7C)) {
            var_s4 = 1;
            temp_v0_2 = func_1510D66C(*(s32 *)((u8 *)&D_80090424 + (temp_v1 * 4)), 0, 3, 0);
            if (temp_v0_2 != 0x80000000) {
                (*(s32 *)((u8 *)var_s0 + 0)) = 0xFD180000;
                (*(s32 *)((u8 *)var_s0 + 4)) = temp_v0_2;
                temp_s0 = var_s0 + 8;
                (*(s32 *)((u8 *)temp_s0 + 0)) = 0xF5180000;
                (*(s32 *)((u8 *)temp_s0 + 4)) = 0x07094250;
                temp_s0_2 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xE6000000;
                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
                temp_s0_3 = temp_s0_2 + 8;
                (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x073FF000;
                (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xF3000000;
                temp_s0_4 = temp_s0_3 + 8;
                (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0;
                temp_s0_5 = temp_s0_4 + 8;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5181000;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x94250;
                temp_s0_6 = temp_s0_5 + 8;
                (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF2000000;
                (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x7C07C;
                var_s0 = func_151E8E94(temp_s0_6 + 8, var_s2, temp_t4, var_s2 + 0x80, temp_t4 + 0x80, 0, 0, 0, 0x400, 0x400);
            }
            var_s2 += 0x60;
        }
        var_s1 = (s32 *)((u8 *)var_s1 - (4));
    } while ((u32) var_s1 >= (u32) &sp.u7C);
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB5AC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB81C.s")

s32 func_151EC0E0(s32 arg0) {
    if (D_8009016C != 0) {
        arg0 = func_151EA90C(arg0, 0x6A, D_8009016C, 0);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC11C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC300.s")

#ifdef NON_MATCHING
s32 func_151EC928(s32 arg0) {
    s32 temp_t6;
    s32 var_v0;

    if (D_800E0EC0 >= 0x5DD) {
        temp_t6 = (D_800E0EC0 - 0x5DC) * 8;
        var_v0 = temp_t6;
        if (temp_t6 >= 0x100) {
            var_v0 = 0xFF;
        }
        func_1504332C(0xFFU, 0xFFU, 0xFFU, var_v0 & 0xFF);
        func_15042D94(0xDC, 0x130, 1, (*(u8 **)((u8 *)D_800E1008 + 0x1D0)));
    }
    return arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC928.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC9A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECB98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECE00.s")

void func_15096D44(Gfx *);
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx D_800903D8[];
extern u8 D_80091BCC[];
extern u8 D_80091BD8[];

void func_151ED854(Gfx *gdl) {
    s32 a;

    gSPDisplayList(gdl++, D_800903D8);
    a = D_800E0EC0 * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
    gdl = func_151EDBE8(gdl, D_80091BCC, 0x92, 0x6C, 8, 3, 1.0f, 0);
    gDPPipeSync(gdl++);
    gDPSetCombine(gdl++, 0xFFD3FF, 0xFFA6FF7F);
    gDPSetEnvColor(gdl++, 0xFF, 0x80, 0x20, ((u8)D_800E0FC7 * (a + 1)) >> 8);
    func_15096D44(func_151EDBE8(gdl, D_80091BD8, 0x92, 0x6C, 8, 3, 1.0f, 0));
}

u8 *func_1501A6CC(u8 *, s32, s32, s32, s32);
Gfx *func_151ED998(Gfx *gdl) {
    if ((u8)D_800E0FC6 == 0) {
        return gdl;
    }
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, (u8)D_800E0FC6);
    return (Gfx *)func_1501A6CC((u8 *)gdl, 0, 0, D_800BE620, D_800BE624);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDA54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE0C4.s")

void func_151EE310(u8 *arg0) {
    s32 i;

    if (arg0 != NULL) {
        func_1503FAA8(*(s32 *)(arg0 + 0x24));
        func_100043B4(arg0, 4);
        for (i = 0; i < arg0[0x14]; i++) {
            func_100043B4(((s32 **)(arg0 + 4))[i], 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE93C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EF3A0.s")
