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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8E94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA4C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA90C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB5AC.s")

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
