#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
u8 *func_15140410(u8 *arg0, u8 *arg1, u8 *arg2, s16 arg3);
#endif

// copies the colours of 4 vertices
typedef struct {
    s16 c[4];
    u16 flag;
} struct_eu_vtxcol;

void func_1513FFF4(Vtx *arg0, u8 arg1, u8 arg2);
void func_151400D0(Vtx *arg0, struct_eu_vtxcol *arg1);
s32 func_1515D9B0(void);
s32 func_1515D9F0(s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C060.s")

struct210 *func_1513C350(struct210 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, struct167 *arg7, s32 arg8, u8 arg9, s32 argA) {
    struct210 *temp_v0;
    u8 phi_v0;
    s32 i;

    if (arg1 == 0) {
        arg1 = (s32)&D_800A4AA0;
    }
    if (arg0->unk0 & 0x40000) {
        phi_v0 = 0x4A;
    } else {
        phi_v0 = 0x1B;
    }
    temp_v0 = func_15167A68(phi_v0, argA, arg8 + 0xB0, 1, arg9, 1);
    if (temp_v0 == 0) {
        return NULL;
    }
    memcpy(&temp_v0->unk18.i.unk0, arg0, 0x28); // memcpy
    func_1513FFF4((Vtx *)&temp_v0->unk40, temp_v0->unk1E, arg4);
    func_151400D0((Vtx *)&temp_v0->unk40, (struct_eu_vtxcol *)arg1);
    temp_v0->unk80 = arg2;
    temp_v0->unk81 = arg3;
    temp_v0->unk84 = arg5;
    temp_v0->unk10 = 1;
    temp_v0->unk14 = 0;
    temp_v0->unkA0 = arg6;
    for (i = 0; i < 4; i++) {
        temp_v0->unk8C[i] = 0;
    }

    temp_v0->unk9C = 0;
    if (arg5) {
        for (i = 0; i <= D_80082FA0; i++) {
            temp_v0->unk8C[i] = func_1515D9F0(arg5);
        }
        temp_v0->unk9C = func_1515D9B0();
    }
    if (arg7) {
        *(struct167 *)temp_v0->unkA4 = *arg7;
    }
    return temp_v0;
}

struct210 *func_1513C4EC(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF) {
    s32 temp_v0;
    struct17 tmp;

    tmp.unk0 = arg4;
    tmp.unk4 = arg5;
    tmp.unk8 = arg6;
    temp_v0 = func_1513C350(arg0, arg1, arg2, arg3, argA, argB, argC, &tmp, argD, argE, argF);
    if (temp_v0 == 0) {
        return 0;
    }
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, arg9);
    return temp_v0;
}

struct210 *func_1513C5B0(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD) {
    s32 tmp = func_1513C350(arg0, arg1, arg2, arg3, argA, 0, 0, 0, argB, argC, argD);
    if (tmp == 0) {
        return 0;
    }
    func_1513E13C(tmp, arg4, arg5, arg6, arg7, arg8, arg9);
    return tmp;
}

struct210 *func_1513C650(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF) {
    s32 temp_v0;
    struct17 tmp;

    tmp.unk0 = arg4;
    tmp.unk4 = arg5;
    tmp.unk8 = arg6;

    temp_v0 = func_1513C350(arg0, 0, arg1, arg2, argA, argB, argC, &tmp, argD, argE, argF);
    if (temp_v0 == 0) {
        return 0;
    }

    if (func_1513E2AC(temp_v0, 0, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}

struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD) {
    s32 tmp = func_1513C350(arg0, 0, arg1, arg2, argA, 0, 0, 0, argB, argC, argD);
    if (tmp == 0) {
        return 0;
    }

    if (func_1513E2AC(tmp, 0, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        func_1516972C(tmp);
        return 0;
    }
    return tmp;
}

struct210 *func_1513C804(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    s32 tmp = func_1513C350(arg0, 0, arg2, arg3, argB, 0, 0, 0, argC, argD, argE);
    if (tmp == 0) {
        return 0;
    }
    if (func_1513E2AC(tmp, 0, arg4, arg5, arg6, arg7, arg8, arg9, argA) == 0) {
        func_1516972C(tmp);
        return 0;
    }
    return tmp;
}

void func_1513C8D4(struct210 *arg0) {
    func_1513C92C(arg0);
    func_15169804(arg0);
}

void func_1513C900(struct210 *arg0) {
    func_1513C92C(arg0);
    func_15169824(arg0);
}

void func_1513C92C(struct210 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (arg0->unk8C[i]) {
            func_100043B4(arg0->unk8C[i], 4);
        }
    }
    if (arg0->unk9C != 0) {
        func_100043B4(arg0->unk9C, 4);
    }
}

void func_1513C9B0(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk18.i.unk0 & 0x1000) != 0) {
        idx = arg0->unk1F;
    } else {
        idx = 0;
    }
    D_80089EE8[idx]();
}

void func_1513C9FC(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk18.i.unk0 & 0x1000) != 0) {
        idx = arg0->unk1F;
    } else {
        idx = 0;
    }
    D_80089EF0[idx]();
}

void func_1513CA48(struct210 *arg0) {
    func_151D5E30(&arg0->unk100);
}

void func_1513CA6C(struct210 *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169804(arg0);
}

void func_1513CAA0(struct210 *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169824(arg0);
}

void func_1513CAD4(struct210 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (arg0->unkA4[i]) {
            func_100043B4(arg0->unkA4[i], 4);
        }
    }
    if (arg0->unkB4 != 0) {
        func_100043B4(arg0->unkB4, 4);
    }
}

// is this really struct210?
void func_1513CB58(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk58 & 0x400000) != 0) {
        idx = arg0->unk18.b.unk1; //unk19;
    } else {
        idx = 0;
    }
    D_80089EF8[idx]();
}

void func_1513CBA4(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk58 & 0x400000) != 0) {
        idx = arg0->unk18.b.unk1; //unk19;
    } else {
        idx = 0;
    }
    D_80089F2C[idx]();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CBF0.s")

void func_1513CF9C(s32 arg0, s32 arg1, u8 arg2) {
    D_80089F60[0](arg0, arg1, arg2);
}

void func_1513CFD0(s32 arg0, s32 arg1, s32 arg2) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CFE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D2F0.s")

void func_1513D4B8(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    func_1513D2F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 0, arg7, arg8, arg9);
}

void func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    func_1513D2F0(arg0, &D_800A4AA0, arg1, arg2, arg3, arg4, arg5, 0, 0, arg6, arg7, arg8);
}

s32 func_1513D594(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, u8 argD, s32 argE, u8 argF, s32 arg10) {
    struct210 *temp_v0;

    if (arg1 == 0) {
        arg1 = &D_800A4AA0;
    }
    temp_v0 = func_1513D2F0(arg0, arg1, arg2, arg3, arg4, 0xC, arg5, argB, argC, argE + 0x18, argF, arg10);
    if ((temp_v0 != 0) && (func_1513D6FC(&temp_v0->unk110, arg6, arg7, arg8, arg9, argA, argD) == 0)) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}

void func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    func_1513D594(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, 0, 0, argB, argC, argD, argE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D6FC.s")
// s32 func_1513D6FC(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
//     f32 spBC;
//     f32 spB8;
//     f32 spB4;
//     s32 spB0;
//     f32 spAC;
//     s32 spA8;
//     f32 spA4;
//     s32 spA0;
//     s32 sp9C;
//     s32 sp98;
//     s32 sp94;
//     s32 sp90;
//     f32 sp8C;
//     f32 sp88;
//     f32 sp84;
//     s32 sp80;
//     f32 sp7C;
//     f32 sp78;
//     f32 sp74;
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     f32 sp60;
//     s32 sp5C;
//     s32 sp58;
//     s32 sp54; // ?
//     s32 sp50; // ?
//     s32 sp4C; // ?
//     s32 sp48; // ?
//     s32 sp44; // ?
//     s32 sp40; // ?
//     s32 sp3C; // ?
//     s32 sp38; // ?
//     s32 sp34; // ?
//     s32 sp30; // ?
//     f32 sp2C;
//     f32 sp28;
//     f32 sp24;
//
//     f32 temp_f0;
//     f32 temp_f16;
//     f32 temp_f18;
//     f32 phi_f12;
//     f32 phi_f14;
//     f32 phi_f12_2;
//
//     if (arg6 != 0) {
//         spB4 = func_151423D8(arg1 - 64);
//         temp_f0 = func_151423D8(arg1);
//         spAC = arg2 * temp_f0;
//         spA4 = arg3 * temp_f0;
//         if (func_1510E388(arg4, arg5, &spBC, &spB8) == 0) {
//             return 0;
//         }
//         temp_f18 = spA4 * spB8;
//         sp2C = fabsf(spA4);
//         temp_f16 = arg3 * spB4;
//         sp28 = sqrtf((spA4 * spA4) + (temp_f18 * temp_f18));
//         if (temp_f16 != 0.0f) {
//             sp8C = temp_f16 * spBC;
//             sp88 = fabsf(temp_f16) / sqrtf((temp_f16 * temp_f16) + (sp8C * sp8C));
//         } else {
//             sp8C = 0.0f;
//             sp88 = 0.0f;
//         }
//         if (spA4 != 0.0f) {
//             sp84 = temp_f18;
//             phi_f12 = sp2C / sp28;
//         } else {
//             sp84 = 0.0f;
//             phi_f12 = 0.0f;
//         }
//         arg0->unk0 = sp88 * temp_f16;
//         arg0->unk8 = phi_f12 * spA4;
//         arg0->unk4 = (sp88 * sp8C) + (phi_f12 * sp84) + 0.5f;
//         temp_f18 = -(arg2 * spB4);
//         temp_f16 = temp_f18 * spB8;
//         sp28 = fabsf(temp_f18);
//         sp2C = temp_f16;
//         sp24 = sqrtf((temp_f18 * temp_f18) + (temp_f16 * temp_f16));
//         if (spAC != 0.0f) {
//             temp_f0 = spAC * spBC;
//             sp8C = temp_f0;
//             phi_f14 = fabsf(spAC) / sqrtf((spAC * spAC) + (temp_f0 * temp_f0));
//         } else {
//             sp8C = 0.0f;
//             sp88 = 0.0f;
//             phi_f14 = 0.0f;
//         }
//         if (temp_f18 != 0.0f) {
//             sp84 = sp2C;
//             phi_f12_2 = sp28 / sp24;
//         } else {
//             sp84 = 0.0f;
//             phi_f12_2 = 0.0f;
//         }
//         arg0->unkC = phi_f14 * spAC;
//         arg0->unk14 = phi_f12_2 * temp_f18;
//         arg0->unk10 = (phi_f14 * sp8C) + (phi_f12_2 * sp84) + 0.5f;
//     } else {
//         sp7C = func_151423D8(arg1 - 64);
//         sp78 = func_151423D8(arg1);
//         if (func_15144E80(arg5, &sp6C, &sp60, &sp54) == 0) {
//             return 0;
//         }
//         if (func_15145128(&sp6C, &sp6C, &sp50, &sp4C) == 0) {
//             return 0;
//         }
//         if (func_15145128(&sp60, &sp60, &sp50, &sp4C) == 0) {
//             return 0;
//         }
//         temp_f0 = arg2 * sp78;
//         temp_f18 = arg2 * sp7C;
//         arg0->unk0 = (temp_f0 * sp6C) + (temp_f18 * sp60);
//         arg0->unk4 = (temp_f0 * sp70) + (temp_f18 * sp64);
//         arg0->unk8 = (temp_f0 * sp74) + (temp_f18 * sp68);
//         temp_f0 = -arg3 * sp7C;
//         temp_f18 = arg3 * sp78;
//         arg0->unkC = (temp_f0 * sp6C) + (temp_f18 * sp60);
//         arg0->unk10 = (temp_f0 * sp70) + (temp_f18 * sp64);
//         arg0->unk14 = (temp_f0 * sp74) + (temp_f18 * sp68);
//     }
//     return 1;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DB00.s")

// jump table
extern s32 (*D_8008A304[])(u8 *, s32, u8);

void func_1513DF9C(u8 *arg0, s32 arg1, u8 arg2) {
    s32 idx;

    if (!(*(s32 *)(arg0 + 0x58) & 0x400000)) {
        idx = 0;
    } else {
        switch (arg0[0x19]) {
        case 12: idx = 10; break;
        case 11: idx = 9; break;
        case 0:
        case 2: idx = 0; break;
        case 1: idx = 1; break;
        case 5: idx = 2; break;
        case 6: idx = 3; break;
        case 3: idx = 4; break;
        case 7: idx = 5; break;
        case 8: idx = 6; break;
        case 9: idx = 7; break;
        case 4: idx = 8; break;
        default: idx = 0; break;
        }
    }
    D_8008A304[idx](arg0, arg1, arg2);
}

void func_1513E070(s32 arg0, s32 arg1, s32 arg2) {
}

void func_1513E084(struct210 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = &arg0->unk110;
    if (arg2 == 0x1A) {
        if ((temp_v0->unk0 == arg1->unk0) || (temp_v0->unk4.b.unk0 == arg1->unk4.b.unk0)) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = &arg0->unk110;
        if (arg2 == 0x2D) {
            if (temp_v0->unk0 == arg1->unk0) {
                temp_v0->unk0 = arg1->unk4.i.unk0;
                temp_v0->unk4.b.unk0 = arg1->unk9;
            } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
                temp_v0->unk0 = arg1->unk0;
                temp_v0->unk4.b.unk0 = arg1->unk8;
            }
        }
    }
}

void func_1513E134(void) {
}

// positions a 4-vertex quad of half-size (arg4, arg5) at (arg1, arg2, arg3), rotated by angle arg6
#ifdef NON_MATCHING
void func_1513E13C(struct210 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    f32 sp48;
    f32 sp30;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f8;
    f32 temp_f8_2;
    s32 temp_f10;

    sp48 = func_151423D8((arg6 - 0x40) & 0xFF);
    temp_f0 = func_151423D8(arg6);
    temp_f14 = arg4 * temp_f0;
    temp_f12 = arg5 * sp48;
    temp_f18 = arg1 + temp_f14;
    arg0->unk40 = (s16) (s32) (temp_f18 - temp_f12);
    temp_f10 = (s32) arg2;
    arg0->unk42 = (s16) temp_f10;
    temp_f16 = arg5 * temp_f0;
    temp_f2 = arg4 * sp48;
    temp_f8 = arg3 + temp_f16;
    sp1C = temp_f8;
    arg0->unk44 = (s16) (s32) (temp_f8 + temp_f2);
    temp_f8_2 = arg1 - temp_f14;
    sp30 = temp_f8_2;
    arg0->unk52 = (s16) temp_f10;
    arg0->unk50 = (s16) (s32) (temp_f8_2 - temp_f12);
    arg0->unk54 = (s16) (s32) (sp1C - temp_f2);
    arg0->unk62 = (s16) temp_f10;
    arg0->unk60 = (s16) (s32) (sp30 + temp_f12);
    temp_f10_2 = arg3 - temp_f16;
    sp30 = temp_f10_2;
    arg0->unk72 = (s16) temp_f10;
    arg0->unk70 = (s16) (s32) (temp_f18 + temp_f12);
    arg0->unk64 = (s16) (s32) (temp_f10_2 - temp_f2);
    arg0->unk74 = (s16) (s32) (sp30 + temp_f2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E13C.s")
#endif
// NON-MATCHING: arg0 lives in a1 and stack layout differs (frame 0x50)
// void func_1513E13C(struct210 *arg0_, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
//     Vtx *arg0 = (Vtx *)&arg0_->unk40;
//     f32 s = func_151423D8(arg6 - 0x40);
//     f32 c = func_151423D8(arg6);
//     s32 y;
//
//     arg0[0].v.ob[0] = (arg1 + arg4 * c) - arg5 * s;
//     arg0[0].v.ob[1] = y = arg2;
//     arg0[0].v.ob[2] = (arg3 + arg5 * c) + arg4 * s;
//     arg0[1].v.ob[1] = y;
//     arg0[1].v.ob[0] = (arg1 - arg4 * c) - arg5 * s;
//     arg0[1].v.ob[2] = (arg3 + arg5 * c) - arg4 * s;
//     arg0[2].v.ob[1] = y;
//     arg0[2].v.ob[0] = (arg1 - arg4 * c) + arg5 * s;
//     arg0[3].v.ob[1] = y;
//     arg0[3].v.ob[0] = (arg1 + arg4 * c) + arg5 * s;
//     arg0[2].v.ob[2] = (arg3 - arg5 * c) - arg4 * s;
//     arg0[3].v.ob[2] = (arg3 - arg5 * c) + arg4 * s;
// }

void func_1513E2A4(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E2AC.s")

typedef struct {
    u8  pad0[0x8];
    f32 unk8[3];
    f32 unk14[3];
    f32 unk20[3];
    f32 unk2C;
} struct_eu_1513E6E8_vel;

typedef struct {
    u8  pad0[0x34];
    f32 unk34[3];
    f32 unk40[3];
    f32 unk4C[3];
    s32 unk58;
    u8  pad5C;
    u8  unk5D;
    u8  pad5E[0xB2];
    struct_eu_1513E6E8_vel unk110;
} struct_eu_1513E6E8;

s32 func_1513E6E8(struct_eu_1513E6E8 *arg0) {
    struct_eu_1513E6E8_vel *vel = &arg0->unk110;

    if (arg0->unk58 & 0x20) {
        vel->unk8[1] += vel->unk2C * D_800BE9A4;
    }
    if (arg0->unk58 & 0x40) {
        arg0->unk34[0] += vel->unk8[0] * D_800BE9A4;
        arg0->unk34[1] += vel->unk8[1] * D_800BE9A4;
        arg0->unk34[2] += vel->unk8[2] * D_800BE9A4;
    }
    if (arg0->unk58 & 0x80) {
        arg0->unk40[0] += vel->unk14[0] * D_800BE9A4;
        arg0->unk40[1] += vel->unk14[1] * D_800BE9A4;
        arg0->unk40[2] += vel->unk14[2] * D_800BE9A4;
    }
    if (arg0->unk58 & 0x100) {
        arg0->unk4C[0] += vel->unk20[0] * D_800BE9A4;
        arg0->unk4C[1] += vel->unk20[1] * D_800BE9A4;
        arg0->unk4C[2] += vel->unk20[2] * D_800BE9A4;
    }
    arg0->unk5D = 0xFF;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E83C.s")
// ???
#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_1513EAD8(u8 *arg0, u8 arg1, s16 arg2) {
    struct {
        u8 u37;
        u8 pad38[0x10];
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s16 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s16 u5E;
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp30;
    s32 sp2C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f6;
    s32 temp_f6_2;
    s32 temp_f8;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg2, 0x40, &sp.u64, &sp.u37);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg2 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg2 * 4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x30));
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        temp_f14 = *(&D_800DD608 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        temp_f16 = *(&D_800DD618 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x50)) * temp_f12;
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        temp_f6 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f16);
        sp.u48 = (s16) temp_f6;
        sp.u5A = (s16) temp_f6;
        temp_f4 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f2);
        sp.u4A = (s16) temp_f4;
        sp.u50 = (s16) temp_f4;
        temp_f10 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f14);
        sp.u4C = (s16) temp_f10;
        sp.u5E = (s16) temp_f10;
        temp_f8 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f16);
        sp.u4E = (s16) temp_f8;
        sp.u54 = (s16) temp_f8;
        temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (temp_f12 - temp_f2));
        sp.u56 = (s16) temp_f6_2;
        sp.u5C = (s16) temp_f6_2;
        temp_f4_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f14);
        sp.u52 = (s16) temp_f4_2;
        sp.u58 = (s16) temp_f4_2;
        if (arg1 != 0) {
            (*(s16 *)((u8 *)sp.u64 + 0)) = sp.u4E;
            (*(s16 *)((u8 *)sp.u64 + 2)) = sp.u50;
            (*(s16 *)((u8 *)sp.u64 + 4)) = sp.u52;
            (*(s16 *)((u8 *)sp.u64 + 0x10)) = sp.u54;
            (*(s16 *)((u8 *)sp.u64 + 0x12)) = sp.u56;
            (*(s16 *)((u8 *)sp.u64 + 0x14)) = sp.u58;
            (*(s16 *)((u8 *)sp.u64 + 0x20)) = sp.u5A;
            (*(s16 *)((u8 *)sp.u64 + 0x22)) = sp.u5C;
            (*(s16 *)((u8 *)sp.u64 + 0x24)) = sp.u5E;
            (*(s16 *)((u8 *)sp.u64 + 0x30)) = sp.u48;
            (*(s16 *)((u8 *)sp.u64 + 0x32)) = sp.u4A;
            (*(s16 *)((u8 *)sp.u64 + 0x34)) = sp.u4C;
        } else {
            (*(s16 *)((u8 *)sp.u64 + 0)) = sp.u48;
            (*(s16 *)((u8 *)sp.u64 + 2)) = sp.u4A;
            (*(s16 *)((u8 *)sp.u64 + 4)) = sp.u4C;
            (*(s16 *)((u8 *)sp.u64 + 0x10)) = sp.u4E;
            (*(s16 *)((u8 *)sp.u64 + 0x12)) = sp.u50;
            (*(s16 *)((u8 *)sp.u64 + 0x14)) = sp.u52;
            (*(s16 *)((u8 *)sp.u64 + 0x20)) = sp.u54;
            (*(s16 *)((u8 *)sp.u64 + 0x22)) = sp.u56;
            (*(s16 *)((u8 *)sp.u64 + 0x24)) = sp.u58;
            (*(s16 *)((u8 *)sp.u64 + 0x30)) = sp.u5A;
            (*(s16 *)((u8 *)sp.u64 + 0x32)) = sp.u5C;
            (*(s16 *)((u8 *)sp.u64 + 0x34)) = sp.u5E;
        }
        return sp.u60;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EAD8.s")
#endif
void func_1513EDB4(s32 arg0, s16 arg1) {
    func_1513EAD8(arg0, 0, arg1);
}

s32 func_1513EDE4(s32 arg0, s16 arg1) {
    return func_1513EAD8(arg0, 1, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EE14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F114.s")

void func_1513F4B0(struct210 *arg0, s16 arg1) {
    func_15140410(arg0, &arg0->unk110, &arg0->unk11C, arg1);
}

// emits gDPSetCombineLERP for combine mode arg1 (table D_800A4F88), preceded by a pipe sync if *arg2 == 1
Gfx *func_1513F4E4(Gfx *arg0, u8 arg1, u8 *arg2) {
    s32 mode = func_15143044(arg1, 0);

    if (mode != D_800DD5EE) {
        if (*arg2 == 1) {
            gDPPipeSync(arg0++);
            *arg2 = 0;
        }
#define CC(i) D_800A4F88[arg1][i]
        // fakematch: w0 and w1 on one line (statement scheduling)
        { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = _SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(GCCc0w0(CC(0), CC(2), CC(4), CC(6)) | GCCc1w0(CC(8), CC(10)), 0, 24); _g->words.w1 = (unsigned int)(GCCc0w1(CC(1), CC(3), CC(5), CC(7)) | GCCc1w1(CC(9), CC(12), CC(14), CC(11), CC(13), CC(15))); }
#undef CC
        D_800DD5EE = mode;
    }
    return arg0;
}

void func_1513F680(struct171 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    arg0->unk70 = arg1;
    arg0->unk71 = arg2;
    arg0->unk72 = arg3;
    arg0->unk73 = arg4;
}

void func_1513F6C0(struct210 *arg0, u8 arg1, u8 arg2) {
    arg0->unk80 = arg1;
    arg0->unk81 = arg2;
}

s32 func_1513F6E8(struct210 *arg0) {
    f32 temp_f0 = ((f32 *)arg0)[0x128 / 4];
    arg0->unk2C += temp_f0 * D_800BE9A4;
    arg0->unk30 += temp_f0 * D_800BE9A4;
    return 1;
}

#ifdef NON_MATCHING
s32 func_1513F728(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x4];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f16;
    f32 var_f18;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_v1;

    temp_v1 = arg0 + 0x110;
    (*(f32 *)((u8 *)(&sp.u20) + 0)) = (*(f32 *)((u8 *)temp_v1 + 0));
    (*(f32 *)((u8 *)(&sp.u20) + 4)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)(&sp.u20) + 8)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    var_v0 = D_800BE9E4;
    if (var_v0 != 0) {
        temp_a2 = -(var_v0 & 3);
        temp_a1 = temp_a2 + var_v0;
        if (temp_a2 != 0) {
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
            if (temp_a1 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
                    var_v0 -= 1;
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0);
                } while (temp_a1 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0);
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0_2 = var_v0 - 4;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f16;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f16;
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0_2);
        }
    }
    (*(f32 *)((u8 *)temp_v1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4)) + ((*(f32 *)((u8 *)temp_v1 + 0xC)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((sp.u20 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 0)) - sp.u20) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((sp.u24 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 4)) - sp.u24) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((sp.u28 + (0.5f * (((*(f32 *)((u8 *)temp_v1 + 8)) - sp.u28) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + ((*(f32 *)((u8 *)temp_v1 + 0x14)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + ((*(f32 *)((u8 *)temp_v1 + 0x18)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F728.s")
#endif
void func_1513FA2C(s32 arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4(arg0, 0, sp18, arg1);
}

void func_1513FA70(s32 arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4(arg0, 1, sp18, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513FAB4.s")

// sets the texture coordinates of a 4-vertex quad, flipping s/t according to arg2 bits 0/1
void func_1513FFF4(Vtx *arg0, u8 arg1, u8 arg2) {
    struct_eu_80090F10 *entry;
    u16 w;
    u16 h;

    if (arg1 != 0xFF) {
        entry = &D_80090F10[arg1];
        w = entry->unk6 - 1;
        h = entry->unk8 - 1;
        arg0[0].v.tc[0] = arg0[3].v.tc[0] = (arg2 & 1) ? w << 6 : 0;
        arg0[1].v.tc[0] = arg0[2].v.tc[0] = (arg2 & 1) ? 0 : w << 6;
        arg0[0].v.tc[1] = arg0[1].v.tc[1] = (arg2 & 2) ? h << 6 : 0;
        arg0[2].v.tc[1] = arg0[3].v.tc[1] = (arg2 & 2) ? 0 : h << 6;
    }
}


void func_151400D0(Vtx *arg0, struct_eu_vtxcol *arg1) {
    s32 i;

    for (i = 0; i < 4; i++, arg0++, arg1++) {
        arg0->v.flag = arg1->flag;
        arg0->v.cn[0] = arg1->c[0];
        arg0->v.cn[1] = arg1->c[1];
        arg0->v.cn[2] = arg1->c[2];
        arg0->v.cn[3] = arg1->c[3];
        arg0->v.flag = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140190.s")

void func_151403A8(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5168, 4, arg0, arg1);
}

void func_151403DC(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5178, 3, arg0, arg1);
}

#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);

u8 *func_15140410(u8 *arg0, u8 *arg1, u8 *arg2, s16 arg3) {
    struct {
        u8 u47;
        u8 pad48[0x18];
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp40;
    s32 sp3C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    s32 temp_a1;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg3, 0x40, &sp.u64, &sp.u47);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u47 != 0) {
            temp_v0 = arg0 + (arg3 * 4);
            temp_a1 = arg0 + 0xC0;
            sp3C = temp_a1;
            sp40 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f12 = (*(f32 *)((u8 *)arg1 + 0)) * temp_f0;
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f14 = (*(f32 *)((u8 *)arg1 + 4)) * temp_f0;
        temp_f16 = (*(f32 *)((u8 *)arg1 + 8)) * temp_f0;
        temp_f18 = (*(f32 *)((u8 *)arg2 + 0)) * temp_f2;
        temp_f20 = (*(f32 *)((u8 *)arg2 + 4)) * temp_f2;
        temp_f22 = (*(f32 *)((u8 *)arg2 + 8)) * temp_f2;
        (*(s16 *)((u8 *)sp.u64 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12 + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14 + temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f16 + temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x10)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12) + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x12)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f14) + temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 0x14)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f16) + temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x20)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f14) - temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 0x24)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f16) - temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x30)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x32)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14) - temp_f20);
        (*(s16 *)((u8 *)sp.u64 + 0x34)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f16) - temp_f22);
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        return sp.u60;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140410.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_151406AC.s")
