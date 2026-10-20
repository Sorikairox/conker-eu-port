#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x1C9];
    /* 0x1C9 */ u8 unk1C9;
    /* 0x1CA */ u8 pad1CA[0xFA];
    /* 0x2C4 */ u8 *unk2C4;
    /* 0x2C8 */ u8 unk2C8;
} struct_eu_AF2A0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15081A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082020.s")

void func_1507DF10(u8 *, s32, u8);
void func_1508220C(u8 *arg0, u16 v, u8 arg2) {
    if (D_800BE616 == 0) {
        if (arg0[0x1CA] != 0) {
            arg0[0x1CA] = 7;
        }
        if (arg2 == 0 || v != 10) {
            func_1507DF10(arg0, v, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150829C0.s")

s32 func_150829C0(s32, s32);
extern u8 D_800D2520;
extern u8 D_800D2521;
void func_15082D5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 lo;
    s32 hi;
    s32 i;
    if (arg2 != 0) {
        lo = 0;
        hi = D_800D2521;
    } else {
        lo = D_800D2521;
        hi = D_800D2520;
    }
    i = lo;
    if (lo < hi) {
        do {
            func_150829C0(i, arg1);
            i += 1;
        } while (i != hi);
    }
}

void func_15082DD8(u8 *arg0) {
    u8 *temp_v0;

    *(s32 *)(arg0 + 0xF8) &= 0xF7FFFFFD;
    temp_v0 = *(u8 **)(arg0 + 0x31C);
    *(s32 *)(arg0 + 0xF8) |= 4;
    if ((temp_v0 != NULL) && (temp_v0[0x56] == 0)) {
        switch (D_800BE9F0) {
        case 0x0:
        case 0xA:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x19:
        case 0x1B:
        case 0x2C:
        case 0x3C:
        case 0x3D:
        case 0x42:
        case 0x43:
        case 0x44:
            break;
        default:
            *(s32 *)(arg0 + 0xF8) |= 2;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150836AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083568.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150836CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083D54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083F30.s")

s32 func_15084208(void) {
    s32 id;
    s32 i;
    id = 1;
    i = 0;
    if (D_800D2520 > 0) {
        do {
            if (id == *((u8 *)D_800D20FC + i * 0x30 + 0x28)) {
                id++;
                i = 0;
            }
            i++;
        } while (i < D_800D2520);
    }
    if (id >= 0x100) {
        id = 0xFF;
    }
    return id;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E90.s")

s32 func_15083FB0(u8 arg0) {
    struct127 *p = func_15083E90(arg0);

    if (p != NULL) {
        return p - D_800CC2D0;
    }
    return -1;
}

s32 func_15084000(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 *temp_v0 = func_1505EEF4(arg0, arg1, arg2, arg3);

    if (temp_v0 != NULL) {
        return temp_v0 - D_800CC2D0;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150844AC.s")

void func_15084814(struct127 *, s32);

void func_150847B4(u8 *arg0) {
    s32 var_s0;
    u8 var_s1;

    var_s1 = (*(u8 *)((u8 *)arg0 + 0x2C9));
    if (var_s1 == 0) {
        var_s1 = 1;
    }
    var_s0 = 0;
    if ((s32) var_s1 > 0) {
        do {
            func_15084814(arg0, var_s0);
            var_s0 += 1;
        } while (var_s0 != var_s1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084814.s")

s32 func_1503D950(s32, s32);
s32 func_1503DA64(s32, s32);
extern s32 D_8008704C;

void func_150848F0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s1;
    struct124 *temp_v0;
    u8 *var_s0;
    u8 *var_v1;
    u8 temp_s0;
    s32 var_s2;

    temp_s0 = arg0[4];
    if (temp_s0 != 0xFF) {
        func_1503DA64(temp_s0, arg2);
        temp_v0 = D_800D1C90[temp_s0];
        var_v1 = arg0 + 4;
        var_s2 = temp_v0->unk4;
        if (var_s2 == 0) {
            var_s2 = 1;
        } else {
            var_v1 = *(u8 **)(&D_8008704C + (u8) temp_v0->unk5);
        }
        var_s1 = 0;
        var_s0 = var_v1;
        var_s2 += *(u8 *)((u8 *)temp_v0 + 0x38);
        if (var_s2 > 0) {
            do {
                func_1503DA64(*var_s0, arg2);
                func_1503D950(*var_s0, arg2);
                var_s1 += 1;
                var_s0 += 1;
            } while (var_s1 != var_s2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150849C0.s")

u8 func_15084E08(struct_eu_AF2A0 *arg0) {
    s32 temp_v1 = arg0->unk1C9;

    if (temp_v1 != 0) {
        return arg0->unk2C4[temp_v1 - 1];
    }
    return arg0->unk2C4[0];
}

u8 func_15084E34(struct_eu_AF2A0 *arg0, s32 *arg1) {
    s32 temp_v1;

    if (arg0->unk1C9 != 0) {
        temp_v1 = arg0->unk1C9 - 1;
    } else {
        temp_v1 = (arg0->unk2C8 != 0) ? arg0->unk2C8 - 1 : 0;
    }
    if (arg1 != NULL) {
        *arg1 = temp_v1;
    }
    return arg0->unk2C4[temp_v1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084E80.s")

void func_15085098(u8 *arg0) {
    u8 *p;
    f32 r;
    if (arg0[4] == 0x94) {
        p = *(u8 **)(arg0 + 0x2D0);
        r = (f32)((u32)func_150ADA20() % (u32)(s32)*(f32 *)(p + 0x18));
        *(f32 *)(p + 8) = r;
    }
}

extern u8 D_800BE9B0;
extern u16 D_800BE9B8[];
s32 func_15085118(s32 arg0) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < D_800BE9B0; i++) {
        if (arg0 == D_800BE9B8[i]) {
            ret = i;
            break;
        }
    }
    return ret;
}
