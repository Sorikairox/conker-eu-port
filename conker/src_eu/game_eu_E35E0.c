#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_800CC76A;

u8 *func_150B5DD0(u8 *arg0, s32 arg1) {
    if (D_800C35EA == 1) {
        return arg0;
    }
    (*(s16 *)arg0) = 0x1A;
    (*(u16 *)((u8 *)arg0 + 2)) = *(u16 *)((u8 *)&D_800CC76A + (arg1 * 0x32C));
    return arg0 + 4;
}
void func_150B5F1C(f32 *, u8, u8);
void func_150B60E0(u8 *, u8 *);
void func_150B5E30(u8 *arg0) {
    s32 pad; // fakematch: frame/spill slot padding
    f32 sp28[3];
    u8 *a3;
    a3 = *(u8 **)(arg0 + 0x28);
    if (*(s32 *)a3 == 0 || arg0[0x2C] != a3[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(a3 + 0x1D4) != 0) {
        if (func_150ADA68() < 0.10824f) {
            sp28[0] = *(f32 *)(a3 + 0x14);
            sp28[1] = *(f32 *)(a3 + 0x18);
            sp28[2] = *(f32 *)(a3 + 0x1C);
            func_150B5F1C(sp28, arg0[0xC], arg0[1]);
        }
        if (func_150ADA68() < 0.10824f) {
            func_150B60E0(a3, (u8 *)sp28);
            func_150B5F1C(sp28, arg0[0xC], arg0[1]);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B5F1C.s")

typedef struct { s32 x, y, z; } V3i;
void func_150B64E0(u8 *arg0, u8 arg1, s32 arg2);
s32 func_150B6314(u8 *, u8, s32);
s32 func_151530A8(s32 *, u8, s32);

void func_150B5C38(u8 *arg0, u8 arg1, s32 arg2) {

    struct {
        s32 u1C;
        s32 u20;
        s32 u24;
        u8 pad28[0x8];
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s8 u5E;
        s8 u5F;
        s8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        u8 u69;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        u8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 0xD;
    sp.u20 = 8;
    *(V3i *) &sp.u24 = *(V3i *) arg0;
    sp.u30 = 15.88f;
    sp.u34 = 36.1f;
    sp.u38 = -3.6030002f;
    sp.u3C = 2.1660001f;
    sp.u40 = 152.0f;
    sp.u44 = 100.0f;
    sp.u48 = 0;
    sp.u4A = 0xFF;
    sp.u4C = -0x14;
    sp.u4E = 0x32;
    sp.u50 = 3;
    sp.u54 = 2;
    sp.u58 = 0x14;
    sp.u5A = 0xF;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u61 = 0xFF;
    sp.u62 = 0xFF;
    sp.u63 = 0xB4;
    sp.u64 = 0xFF;
    sp.u65 = 0;
    sp.u66 = 0;
    sp.u67 = 0;
    sp.u68 = 0;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xB4;
    sp.u6C = 0xFF;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u71 = 0xFF;
    sp.u72 = 0;
    sp.u73 = 3;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 8;
    sp.u82 = 0x1F;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u88 = 1.0f;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    func_151530A8(&sp.u1C, arg1, arg2);
    func_150B6314(arg0, arg1, arg2);
    func_150B64E0(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B6314.s")

void func_150B64E0(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 9U) + 3;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

void func_150B60E0(u8 *arg0, u8 *arg1) {
    func_15143134(D_800A0000, arg1, (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x140);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B65F0.s")

void func_150B6930(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4A) {
        func_1516972C(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B696C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B6BBC.s")

s32 func_15182BE0(u8, u8, u8, s32, s16, u8, u8, s32);

void func_150B6C34(u8 arg0, s32 arg1) {
    s32 pad;
    u32 sp28;

    sp28 = func_150ADA20();
    func_15182BE0(0xCC, 0xCC, 0xFF, ((sp28 % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 11U) + 0xF, 0, (s32) arg0, arg1);
}
