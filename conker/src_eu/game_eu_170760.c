#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_151429E0(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *temp_v1 = &D_8008A500[(func_150ADA20() & 3) * 3 + arg0 * 12];

    *arg1 = temp_v1[0];
    *arg2 = temp_v1[1];
    *arg3 = temp_v1[2];
}
s32 func_15142A5C(struct127 *arg0) {
    u8 *temp_v0 = (u8 *)arg0->unk2D0;
    if (*(s16 *)(temp_v0 + 0x3C) > 0) {
        return 1;
    }
    return 0;
}
f32 func_15142A80(f32 arg0) {
    return (1.0f - arg0) * (arg0 - 2.0f) * arg0 * 0.16666667f;
}
f32 func_15142AC0(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f) * 0.5f;
}
f32 func_15142B04(f32 arg0) {
    return (2.0f - arg0) * (arg0 + 1.0f) * arg0 * 0.5f;
}
f32 func_15142B44(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * arg0 * 0.16666667f;
}
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear) {
    if (~D_800DD630 & clear) {
        gSPClearGeometryMode(gfx++, clear);
        D_800DD630 |= clear;
    }
    if (~D_800DD62C & set) {
        gSPSetGeometryMode(gfx++, set);
        D_800DD62C |= set;
    }
    return gfx;
}
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5) {
    if ((r != D_800DD5F8) || (g != D_800DD5FA) || (b != D_800DD5FC) || (a != D_800DD5FE)) {
        if (*arg5 == 1) {
            gDPPipeSync(gfx++);
            *arg5 = 0;
        }
        gDPSetEnvColor(gfx++, r, g, b, a);
        D_800DD5F8 = r;
        D_800DD5FA = g;
        D_800DD5FC = b;
        D_800DD5FE = a;
    }
    return gfx;
}
Gfx *func_15142CF0(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *arg7) {
    if ((m != D_800DD634) || (l != D_800DD636) || (r != D_800DD5F0) || (g != D_800DD5F2) || (b != D_800DD5F4) || (a != D_800DD5F6)) {
        if (*arg7 == 1) {
            gDPPipeSync(gfx++);
            *arg7 = 0;
        }
        gDPSetPrimColor(gfx++, m, l, r, g, b, a);
        D_800DD634 = m;
        D_800DD636 = l;
        D_800DD5F0 = r;
        D_800DD5F2 = g;
        D_800DD5F4 = b;
        D_800DD5F6 = a;
    }
    return gfx;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15142E24.s")
Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3) {
    if ((arg1 != D_800DD648) || (arg2 != D_800DD64C)) {
        if (*arg3 == 1) {
            gDPPipeSync(gfx++);
            *arg3 = 0;
        }
        gDPSetOtherMode(gfx++, arg1 | 0xF, arg2);
        D_800DD648 = arg1;
        D_800DD64C = arg2;
    }
    return gfx;
}
s16 func_15143044(u8 arg0, s32 arg1) {
    return 0x7FFF - arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514306C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15143134.s")
// NON-MATCHING: only the delay slot of the first branch differs (stage 4 store vs copied stage 0 store)
// void func_15143134(void *arg0, void *arg1, void *arg2) {
//     f32 mf[4][4];
//
//     D_800DCE30 = 1;
//     if ((arg0 != NULL) && ((((struct17 *)arg0)->unk0 != 0.0f) || (((struct17 *)arg0)->unk4 != 0.0f) || (((struct17 *)arg0)->unk8 != 0.0f))) {
//         D_800DCE30 = 2;
//         D_800DCE38 = ((struct17 *)arg0)->unk0;
//         D_800DCE3C = ((struct17 *)arg0)->unk4;
//         D_800DCE40 = ((struct17 *)arg0)->unk8;
//         if (D_800C42B0 != 0) {
//             D_800DCE30 = 3;
//             D_800DCE34 = arg2;
//             guMtxL2F(mf, arg2);
//             func_150A7E40(mf, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
//                           &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
//             D_800DCE30 = 4;
//         } else {
//             D_800DCE30 = 5;
//             D_800DCE34 = arg2;
//             func_150A7E40(arg2, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
//                           &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
//             D_800DCE30 = 6;
//         }
//     } else {
//         D_800DCE30 = 7;
//         func_15142314(arg2, 0, arg1);
//         D_800DCE30 = 8;
//     }
//     D_800DCE30 = 0;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151432BC.s")

// void func_151432BC(struct208 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
//     struct209 tmp;
//     f32 temp_f2;
//     f32 temp_f6;
//     f32 temp_ret;
//     s32 temp_t6;
//     u8 temp_a0;
//
//     temp_t6 = (arg0->unk15) & 3;
//     if (temp_t6 == 0) {
//         tmp.unk1B = func_150ADA20();
//         tmp.unk14 = func_151423D8((tmp.unk1B - 64) & 0xFF);
//         tmp.unk10 = func_151423D8(tmp.unk1B);
//         temp_ret = func_150ADA68();
//         temp_f2 = temp_ret * arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk10));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk14));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = arg0->unk2;
//     } else if (temp_t6 != 1) {
//         if (temp_t6 == 2) {
//             tmp.unk2F = (u32) (arg0->unk10 * D_800A5644); // 0.7111111283302307
//             tmp.unk28 = func_151423D8((tmp.unk2F - 64));
//             tmp.unk24 = func_151423D8(tmp.unk2F);
//             tmp.unk20 = (func_150ADA68() * (2.0f * (f32) arg0->unk6)) + (f32) -(s32) arg0->unk6;
//             temp_f2 = (func_150ADA68() * (2.0f * (f32) arg0->unkA)) + (f32) -(s32) arg0->unkA;
//             temp_f6 = temp_f2 * tmp.unk24;
//             *arg1 = (arg0->unk0 + ((tmp.unk20 * tmp.unk24) + (temp_f2 * tmp.unk28)));
//             *arg2 = (arg0->unk4 + (temp_f6 - (tmp.unk20 * tmp.unk28)));
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = arg0->unk2;
//         } else {
//             *arg1 = arg0->unk0;
//             *arg2 = arg0->unk4;
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = (arg0->unk2 - arg0->unk8);
//         }
//     } else {
//         tmp.unkB = func_150ADA20();
//         tmp.unk4 = func_151423D8((tmp.unkB - 64));
//         tmp.unk0 = func_151423D8(tmp.unkB);
//         temp_ret = func_150ADA68();
//         temp_f2 = temp_ret * (f32) arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk0));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk4));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = (arg0->unk2 - arg0->unk8);
//     }
// }


void func_151436B4(f32 arg0, f32 arg1, f32 arg2, struct17 *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f2;

    sp24 = cosf(arg0);
    sp20 = sinf(arg0);
    sp1C = cosf(arg1);
    temp_f0 = sinf(arg1);
    temp_f2 = arg2 * sp1C;
    arg3->unk0 = temp_f2 * sp20;
    arg3->unk4 = -arg2 * temp_f0;
    arg3->unk8 = temp_f2 * sp24;
}
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 c = cosf(arg0);
    f32 s = sinf(arg0);
    *arg2 = arg1 * s;
    *arg3 = arg1 * c;
}
void func_15143794(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f2;

    sp24 = func_151423D8(arg0);
    sp20 = func_151423D8(arg0 - 0x40);
    sp1C = func_151423D8(arg1);
    temp_f0 = func_151423D8(arg1 - 0x40);
    temp_f2 = arg2 * sp1C;
    arg3->unk0 = temp_f2 * sp20;
    arg3->unk4 = -arg2 * temp_f0;
    arg3->unk8 = temp_f2 * sp24;
}
void func_15143834(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3) {
    func_15143794(arg0, arg1, arg2, arg3);
}
void func_15143874(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C = func_151423D8(arg0);
    f32 s = func_151423D8(arg0 - 0x40);
    *arg2 = arg1 * s;
    *arg3 = arg1 * sp1C;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151438D8.s")
void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    if (arg3 < arg2) {
        arg2 ^= arg3 ^= arg2 ^= arg3;
    }
    if (*arg1 < *arg0) {
        *arg0 ^= *arg1 ^= *arg0 ^= *arg1;
    }
    if (*arg0 < arg2) {
        *arg0 = arg2;
    }
    if (arg3 < *arg1) {
        *arg1 = arg3;
    }
}
s32 func_15143DA8(s32 *arg0, s32 arg1, s32 arg2) {
    if (arg2 < arg1) {
        arg1 ^= arg2 ^= arg1 ^= arg2;
    }
    if (*arg0 < arg1) {
        *arg0 = arg1;
        return 1;
    }
    if (arg2 < *arg0) {
        *arg0 = arg2;
        return 2;
    }
    return 0;
}

s32 func_15143E08(struct127 *arg0) {
    return (((s32) arg0->unk7A >> 8) + 64) & 0xFF;
}

s16 func_15143E24(struct127 *arg0) {
    if (arg0->unk31C != NULL) {
        return (arg0->unk7A - arg0->unk31C->unk12) >> 8;
    }
    return arg0->unk7A >> 8;
}
f32 func_15143E64(struct17 *arg0) {
    return sqrtf((arg0->unk0 * arg0->unk0) + (arg0->unk4 * arg0->unk4) + (arg0->unk8 * arg0->unk8));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15143E94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514401C.s")
// NON-MATCHING: regalloc only (flags copy in v0, limit in t0)
// s32 func_1514401C(u8 arg0, s32 *arg1, s32 *arg2, u8 arg3) {
//     s32 max;
//     s32 pos;
//     s32 ret;
//
//     ret = 0;
//     max = (D_80090F14[arg0][0] << 16) - 1;
//     *arg2 += *arg1 * D_800BE9E4;
//     pos = *arg2;
//     if (max < pos) {
//         if (arg3 & 1) {
//             ret = 1;
//         } else if (arg3 & 2) {
//             *arg1 = 0;
//             *arg2 = max;
//         } else if (arg3 & 4) {
//             *arg2 = max - (pos % max);
//             *arg1 = -*arg1;
//         } else {
//             do {
//                 pos = *arg2 = pos - max;
//             } while (max < pos);
//         }
//     } else if ((pos < 0) && !(arg3 & 8)) {
//         if (arg3 & 0x10) {
//             *arg1 = 0;
//             *arg2 = 0;
//         } else if (arg3 & 4) {
//             *arg2 = -pos % max;
//             *arg1 = -*arg1;
//         } else {
//             do {
//                 pos = *arg2 = pos + max;
//             } while (pos < 0);
//         }
//     }
//     return ret;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151441A4.s")
void func_151442FC(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    switch (argD) {
    case 2:
    case 3:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg7;
        return;
    case 13:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = 0;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = 0;
        return;
    case 7:
    case 12:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) argB;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg7;
        return;
    case 4:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    case 5:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    case 6:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) argB;
        return;
    case 10:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) argB;
        return;
    case 11:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) arg7;
        return;
    case 9:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) argB;
        return;
    default:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    }
}
s32 func_151444DC(s32 arg0, s32 arg1, s32 arg2) {
    s32 range;

    if (arg1 < arg0) {
        range = (arg1 - arg2) + 1;
        do {
            arg0 -= range;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        range = (arg1 - arg2) + 1;
        do {
            arg0 += range;
        } while (arg0 < arg2);
    }
    return arg0;
}
f32 func_15144528(f32 arg0, f32 arg1, f32 arg2) {
    while (arg1 < arg0) {
        arg0 -= arg1 - arg2;
    }
    while (arg0 < arg2) {
        arg0 += arg1 - arg2;
    }
    return arg0;
}
f32 func_15144598(struct_eu_15144598 *arg0) {
    f32 var_f2;

    switch (arg0->unk15 & 3) {
    case 2:
        var_f2 = (arg0->unk6 * arg0->unkA) * 4.0f;
        break;
    case 0:
    case 1:
        var_f2 = (arg0->unk6 * arg0->unk6) * 3.1415927f;
        break;
    default:
        var_f2 = 1.0f;
        break;
    }
    return var_f2;
}
f32 func_1514462C(struct_eu_15144598 *arg0) {
    f32 var_f2;

    switch (arg0->unk15 & 3) {
    case 2:
        var_f2 = arg0->unk6 * arg0->unk8 * arg0->unkA;
        break;
    case 0:
        var_f2 = (arg0->unk6 * arg0->unk6) * 3.1415927f * arg0->unk8;
        break;
    case 1:
        var_f2 = (f32)arg0->unk6 * 1.0471976f * (f32)arg0->unk6 * (f32)arg0->unk6;
        break;
    default:
        var_f2 = 1.0f;
        break;
    }
    return var_f2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514470C.s")
f32 func_15144A74(struct17 *arg0, struct17 *arg1) {
    return (arg0->unk0 * arg1->unk0) + (arg0->unk4 * arg1->unk4) + (arg0->unk8 * arg1->unk8);
}
f32 func_15144AA8(s32 arg0) {
    f32 var_f2 = D_800DBFF0[arg0].unk380;

    while (var_f2 > 360.0f) {
        var_f2 -= 360.0f;
    }
    while (var_f2 < 0.0f) {
        var_f2 += 360.0f;
    }
    return var_f2;
}
f32 *func_15144B34(s32 arg0) {
    return &D_800DBFF0[arg0].unk2F8;
}
f32 func_15144B68(f32 arg0) {
    f32 var_f2;

    var_f2 = arg0;
    if (arg0 > 6.2831855f) {
        do {
            var_f2 -= 6.2831855f;
        } while (var_f2 > 6.2831855f);
    }
    if (var_f2 < 0.0f) {
        do {
            var_f2 += 6.2831855f;
        } while (var_f2 < 0.0f);
    }
    return var_f2;
}
f32 func_15144BC8(f32 arg0) {
    f32 var_f2 = arg0;

    while (var_f2 > 360.0f) {
        var_f2 -= 360.0f;
    }
    while (var_f2 < 0.0f) {
        var_f2 += 360.0f;
    }
    return var_f2;
}

s32 func_15144C2C(s16 arg0) {
    s16 tmp1 = arg0;

    while (tmp1 >= 256)
    {
        tmp1 -= 255;
    }
    while (tmp1 < 0)
    {
        tmp1 += 255;
    }

    return tmp1;
}

f32 func_15144C8C(f32 arg0, f32 arg1) {
    f32 tmp;

    arg0 = func_15144B68(arg0);
    tmp = fabsf(arg0 - func_15144B68(arg1));
    if (3.1415927f < tmp) {
        tmp = 6.2831855f - tmp;
    }
    return tmp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15144CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15144E80.s")

void func_151450B4(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk4 * arg1->unk8 - arg0->unk8 * arg1->unk4;
    arg2->unk4 = arg0->unk8 * arg1->unk0 - arg0->unk0 * arg1->unk8;
    arg2->unk8 = arg0->unk0 * arg1->unk4 - arg0->unk4 * arg1->unk0;
}

s32 func_15145128(struct17 *arg0, struct17 *arg1, f32 *arg2, f32 *arg3) {
    f32 lenSq;
    f32 sp0;

    if (arg3 == NULL) {
        arg3 = &sp0;
    }
    lenSq = (arg0->unk0 * arg0->unk0) + (arg0->unk4 * arg0->unk4) + (arg0->unk8 * arg0->unk8);
    if (lenSq == 0.0f) {
        return 0;
    }
    if (arg2 != NULL) {
        *arg2 = sqrtf(lenSq);
        *arg3 = 1.0f / *arg2;
    } else {
        *arg3 = 1.0f / sqrtf(lenSq);
    }
    arg1->unk0 = *arg3 * arg0->unk0;
    arg1->unk4 = *arg3 * arg0->unk4;
    arg1->unk8 = *arg3 * arg0->unk8;
    return 1;
}
s32 func_151451F0(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, f32 *arg7, f32 *arg8) {
    if (func_151452C4(arg0, arg1, arg2, arg3, arg5, arg6, arg7, arg8)) {
        if ((*arg7 < 0.0f) && (*arg8 < 0.0f)) {
            return 0;
        }
        if ((*arg7 >= 0.0f) && (*arg8 < 0.0f)) {
            return 1;
        }
        if (*arg7 < arg4) {
            return 1;
        }
        return 0;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151452C4.s")

s32 func_151454BC(u8 arg0, f32 arg1, struct17 *arg2) {
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;
    struct17 *temp_v0;

    temp_v0 = func_15144B34(arg0);
    tmp1 = arg2->unk0 - temp_v0->unk0;
    tmp2 = arg2->unk4 - temp_v0->unk4;
    tmp3 = arg2->unk8 - temp_v0->unk8;

    if ((arg1 * arg1) < ((tmp1 * tmp1) + (tmp2 * tmp2) + (tmp3 * tmp3))) {
        return 0;
    }
    return 1;
}

void func_15145548(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    f32 sp24;

    if (arg4 == NULL) {
        arg4 = &sp24;
    }
    if (func_1514563C(arg0, arg1, arg2, arg3, arg4)) {
        if (*arg4 < 0.0f) {
            *arg3 = *arg0;
        } else if (*arg4 > 1.0f) {
            arg3->unk0 = arg0->unk0 + arg1->unk0;
            arg3->unk4 = arg0->unk4 + arg1->unk4;
            arg3->unk8 = arg0->unk8 + arg1->unk8;
        }
    } else {
        *arg3 = *arg0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514563C.s")
// NON-MATCHING: t is also stored to an unused stack slot at sp+0 (frame 0x20); closest draft:
// s32 func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
//     f32 sp10;
//     f32 lenSq;
//     f32 dotO;
//     f32 dotP;
//     f32 t;
//
//     if (arg4 == NULL) {
//         arg4 = &sp10;
//     }
//     lenSq = (arg1->unk0 * arg1->unk0) + (arg1->unk4 * arg1->unk4) + (arg1->unk8 * arg1->unk8);
//     if (lenSq == 0.0f) {
//         return 0;
//     }
//     dotO = (arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk4) + (arg1->unk8 * arg0->unk8);
//     dotP = (arg1->unk0 * arg2->unk0) + (arg1->unk4 * arg2->unk4) + (arg1->unk8 * arg2->unk8);
//     *arg4 = t = (dotP - dotO) / lenSq;
//     arg3->unk0 = (t * arg1->unk0) + arg0->unk0;
//     arg3->unk4 = (*arg4 * arg1->unk4) + arg0->unk4;
//     arg3->unk8 = (*arg4 * arg1->unk8) + arg0->unk8;
//     return 1;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15145740.s")
// NON-MATCHING: 90% there
// void func_15145740(struct127 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 arg4) {
//     struct194 tmp;
//     f32 temp_f6;
//     s16 phi_v1;
//     s16 phi_t0;
//
//     if ((arg0->unk4 == 0x96) && ((arg0->unk31C->unk7D != 0))) {
//         phi_t0 = arg0->unk7A + arg0->unk31C->unk80;
//     } else {
//         if (arg0->unk31C != 0) {
//             phi_t0 = arg0->unk7A - arg0->unk31C->unk12;
//         } else {
//             phi_t0 = arg0->unk7A;
//         }
//     }
//     if ((arg0->unk4 == 0x96) && (arg0->unk31C->unk7D != 0)) {
//         phi_v1 = arg0->unk31C->unk82 + 1024;
//     } else {
//         phi_v1 = arg0->unk1D1 * 200;
//     }
//     tmp.unk14 = phi_t0;
//     tmp.unk10 = phi_v1 * 0.005493164f;
//     tmp.unk0 = tmp.unk10 * D_800A56B4;
//     func_1505A184(phi_t0, 2000.0f, tmp.unk10, &arg1->unk0, &arg1->unk8, &arg1->unk4);
//     if (arg2 != 0) {
//         arg2->unk4 = cosf(tmp.unk0) * 1000.0f;
//         temp_f6 = sinf(tmp.unk0) * 1000.0f;
//         tmp.unk8 = temp_f6;
//         tmp.unk4 = phi_t0 * D_800A56B8;
//         arg2->unk0 = cosf(tmp.unk4) * tmp.unk8;
//         arg2->unk8 = sinf(tmp.unk4) * -temp_f6;
//         if (arg3 != 0) {
//             tmp.unkC = tmp.unk0 + arg4;
//             arg3->unk4 = cosf(tmp.unkC) * 1000.0f;
//             tmp.unk8 = sinf(tmp.unkC) * 1000.0f;
//             arg3->unk0 = cosf(tmp.unk4) * tmp.unk8;
//             arg3->unk8 = sinf(tmp.unk4) * -tmp.unk8;
//         }
//     }
// }

void func_15145974(struct17 *arg0, f32 *arg1, f32 *arg2) {
    *arg1 = func_150484A0(arg0->unk0, arg0->unk8) * 57.295776f;
    if (arg2 != NULL) {
        *arg2 = (func_150484A0(sqrtf(arg0->unk0 * arg0->unk0 + arg0->unk8 * arg0->unk8), arg0->unk4) * 57.295776f) - 90.0f;
    }
}

f32 func_15145A0C(f32 arg0, f32 arg1, f32 arg2) {
    return D_800A548C[(s32)(arg0 * arg2 * 100.0f)] * arg1;
}


void func_15145A50(struct127 *arg0) {
    arg0->unk5 = 3;
    if (D_800BE9F0 != 51) {
        if ((D_800BE616 != 0) || (arg0->interaction_state == 5) || (arg0->interaction_state == 1) || (arg0->interaction_state == 21)) {
            arg0->interaction_state = 5;
            if (arg0->unk31C != NULL) {
                arg0->unk31C->unk78 = 0;
            }
        } else {
            func_15053694(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15145AD8.s")

u8 func_15145C90(s32 arg0) {
    if (arg0 < 0) {
        return 1;
    } else {
        return (D_800DBEF4[arg0].unk6F & 0x80) == 0x80;
    }
}

void func_15145CD0(struct_eu_xform *arg0, struct17 **arg1, struct17 **arg2, s32 arg3) {
    f32 mf[4][4];
    s32 i;

    func_150A8050(mf, arg0->unk0, arg0->unk4, arg0->unk8);
    mf[3][0] = arg0->unk10;
    mf[3][1] = arg0->unk12;
    mf[3][2] = arg0->unk14;
    for (i = 0; arg3 > 0; arg3--, i++) {
        func_150A7E40(mf, arg1[i]->unk0, arg1[i]->unk4, arg1[i]->unk8, &arg2[i]->unk0, &arg2[i]->unk4, &arg2[i]->unk8);
    }
}
void func_15145DB4(struct_eu_xform *arg0, struct17 *arg1, struct17 *arg2, s32 arg3) {
    f32 mf[4][4];
    s32 i;

    func_150A8050(mf, arg0->unk0, arg0->unk4, arg0->unk8);
    mf[3][0] = arg0->unk10;
    mf[3][1] = arg0->unk12;
    mf[3][2] = arg0->unk14;
    for (i = 0; arg3 > 0; arg3--, i++) {
        func_150A7E40(mf, arg1[i].unk0, arg1[i].unk4, arg1[i].unk8, &arg2[i].unk0, &arg2[i].unk4, &arg2[i].unk8);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15145EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15146078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151462C8.s")
u8 func_151464B8(s16 *arg0) {
    s32 i;
    s16 mask;

    for (i = 0, mask = 0; i <= D_80082FA0; i++) {
        mask |= 1 << i;
    }
    return !(arg0[1] & mask);
}

void func_15146508(struct127 *arg0, struct127 *arg1) {
    struct193 tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg1;
    tmp.unk8 = arg0->unique_id;
    tmp.unk9 = arg1->unique_id;
    func_15169040(&tmp, 45, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514654C.s")

s32 func_1514672C(u8 *arg0) {
    f32 temp_f0;

    if ((fabsf((*(f32 *)((u8 *)arg0 + 0))) > 19500.0f) || (fabsf((*(f32 *)((u8 *)arg0 + 8))) > 19500.0f) || (temp_f0 = (*(f32 *)((u8 *)arg0 + 4)), (temp_f0 > 19500.0f)) || (temp_f0 < -9500.0f)) {
        return 0;
    }
    return 1;
}
// NON-MATCHING: JUSTREG: first 3 statements are out of order
// s32 func_1514672C(struct17 *arg0) {
//     if ((D_800A56C4 < fabsf(arg0->unk0)) || (D_800A56C4 < fabsf(arg0->unk8)) || (D_800A56C4 < arg0->unk4) || (arg0->unk4 < D_800A56C8)) {
//         return 0;
//     } else {
//         return 1;
//     }
// }

void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    *arg0 = *arg0 - D_800BE9A4;
    if (*arg0 < 0.0f) {
        *arg0 = func_150ADA68() * arg1;
        if ((func_150ADA20() & 3) != 0) {
            *arg2 = (func_150ADA68() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (func_150ADA68() * (arg5 - arg4)) + arg4;
        }
    }
    *arg7 = ((*arg2 - *arg7) * arg6) + *arg7;
}
