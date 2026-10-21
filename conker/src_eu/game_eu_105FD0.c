#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D87C0(s32 arg0) {
}

#ifdef NON_MATCHING
extern s32 D_80090648;

s32 func_150D87CC(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    s32 *temp_a0;
    s32 temp_f6;
    s32 var_a1;
    s32 var_a2;
    s8 *temp_v1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg1 + 0x2D0));
    if (temp_v0 == NULL) {
        return 0;
    }
    (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) (*(s32 *)((u8 *)(&D_80090648) + 0x18));
    if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0xD) {
        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 8));
        if ((temp_f0 >= 23.0f) && (temp_f0 <= 40.0f)) {
            (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) (*(s32 *)((u8 *)(&D_80090648) + 0x1C));
            temp_v1 = *(*(s8 ***)((u8 *)arg0 + 0x24));
            var_a1 = 0;
            if (*temp_v1 != -0xE) {
                do {
                    var_a1 += 1;
                } while (*((var_a1 * 8) + temp_v1) != -0xE);
            }
            temp_a0 = temp_v1 + (var_a1 * 8);
            temp_f6 = (s32) ((70.0f * (((*(f32 *)((u8 *)temp_v0 + 8)) - 23.0f) * 0.05882353f)) + 2.0f);
            var_a2 = temp_f6;
            if (temp_f6 < 0) {
                var_a2 = temp_f6 + (((s32) *temp_a0 >> 0xC) & 0xFFF);
            }
            *temp_a0 = ((var_a2 & 0xFFF) << 0xC) | 0xF2000000 | 2;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D87CC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D88E8.s")

s16 *func_150D8AA0(s16 *arg0, s32 arg1) {
    arg0[0] = 0x42;
    arg0[1] = 0;
    return arg0 + 2;
}

#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_1504715C(void *, u8 *);
void func_150E856C(f32, s32, s32 *, f32 *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E892C(void *, s16, u8, s32);
s32 func_15153BA4(s16 *, s32, s32, s32);

void func_150D8ABC(struct127 *arg0) {
    struct {
        s16 u48;
        s16 u4A;
        s8 u4C;
        u8 pad4D[0x1];
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s32 u5C;
        s32 u60;
        s8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        s8 u69;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s16 u6E;
        s16 u70;
        s16 u72;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s16 u8C;
        s16 u8E;
        s16 u90;
        s16 u92;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s32 uA4;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        u8 padAD[0x3];
        f32 uB0;
        f32 uB4;
        s32 uB8;
        u8 padBC[0x14];
        s32 uD0;
        u8 padD4[0x4];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
    } sp;
    s32 sp40;
    f32 sp3C;

    sp.uE4 = arg0->x_position;
    sp.uE8 = arg0->unk180;
    sp.uEC = arg0->z_position;
    sp.uD8 = sp.uE4;
    sp.uE0 = sp.uEC;
    sp.uDC = sp.uE8 + 100.0f;
    func_1504715C(&sp.uB4, arg0);
    if ((func_15046F70(&sp.uD8, 0, sp.uE8 - 200.0f, &sp.uB4) != 0) && (sp.uD0 & 1)) {
        sp.uE4 = sp.uD8;
        sp.uE8 = sp.uB4;
        sp.uEC = sp.uE0;
        sp3C = func_150ADA68();
        sp40 = func_150ADA20();
        func_150E856C((sp3C * 109.0f) + 140.0f, (((u32) sp40 % 86U) + 0xAA) & 0xFF, &sp.uB8, &sp.uE4, (func_150ADA20() % 251U) + 0x1F4, 0, 1, 0, 0, 0, 0xFF, 0);
    }
    func_150E892C(&sp.uE4, (s16) ((func_150ADA20() % 62U) + 0x78), 0xFF, 1);
    sp.u7C = 298.0f;
    sp.u4E = 0x5103;
    sp.u74 = 1.022876f;
    sp.u80 = sp.uE4;
    sp.u48 = 0x1A;
    sp.u4A = 7;
    sp.u4C = 0x6C;
    sp.u50 = 0x200005;
    sp.u58 = 0x1E;
    sp.u5A = 0xA;
    sp.u67 = 0xFF;
    sp.u64 = 0xB9;
    sp.u6A = 0x7E;
    sp.u78 = 150.0f;
    sp.u65 = 0xC7;
    sp.u66 = 0xC4;
    sp.u68 = 0x95;
    sp.u69 = 0x91;
    sp.u6B = 0x64;
    sp.u6C = 0x9B;
    sp.u6D = 0xFF;
    sp.u6E = 0x1E;
    sp.u70 = 8;
    sp.u54 = 0;
    sp.u5C = 0;
    sp.u60 = 0;
    sp.u72 = 0x1E;
    sp.u84 = sp.uE8 + 35.0f;
    sp.u8C = 0;
    sp.u8E = -0x10;
    sp.u90 = 0xFF;
    sp.u92 = 0x14;
    sp.u94 = 18.0f;
    sp.u98 = 18.0f;
    sp.uA4 = 0x840E07;
    sp.uA8 = 0x10;
    sp.uA9 = -1;
    sp.uAA = 8;
    sp.uAB = 6;
    sp.uAC = 1;
    sp.u9C = 0.093f;
    sp.uA0 = 0.30200002f;
    sp.u88 = sp.uEC;
    sp.uB0 = 0.905482f;
    func_15153BA4(&sp.u48, 0xFF, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8ABC.s")
#endif
s32 func_150D8DBC(u8 *arg0) {
    if ((*(u8 **)(arg0 + 0x18))[0x6F] != 0) {
        (*(u8 **)(arg0 + 0x14))[9] = 0;
    } else {
        (*(u8 **)(arg0 + 0x14))[9] = 1;
    }
    return 1;
}

s32 func_150D8DF0(f32 *arg0, u8 *arg1, u8 arg2) {
    s32 idx;
    f32 x;
    f32 y;
    f32 z;

    switch (arg2) {
    case 3:
        idx = 0x12;
        x = -7.0f;
        z = 30.0f;
        break;
    case 4:
        idx = 0x15;
        x = -4.0f;
        z = 35.0f;
        break;
    case 5:
        idx = 0xF;
        x = 5.0f;
        z = 20.0f;
        break;
    case 6:
        idx = 0x18;
        x = 5.0f;
        z = 31.0f;
        break;
    }
    y = 0.0f;
    func_150A7E40((f32 (*)[4]) (*(u8 **)(arg1 + 0x1D4) + (idx << 6)), x, 0.0f, z, &x, &y, &z);
    arg0[0] = x;
    arg0[1] = y;
    arg0[2] = z;
    return 1;
}

s32 func_150D8F30(s32 arg0, s32 arg1) {
    return 8;
}

#ifdef NON_MATCHING
void func_151664F0(s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_15187B50(f32, f32, f32, s32, s32, s32, f32, f32);

void func_150D8F44(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 u34;
        f32 u38;
        f32 u3C;
    } sp;

    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        func_150D8DF0(&sp.u34, arg0, arg1);
        func_15187B50(sp.u34, sp.u38, sp.u3C, 0x1E, 0xF, 7, 0.1f, 0.03f);
        func_151664F0(-1, (s32) sp.u34, (s32) ((*(f32 *)((u8 *)arg0 + 0x180)) + 4.0f), (s32) sp.u3C, 4, 0x32, 0, 0xFF, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8F44.s")
#endif