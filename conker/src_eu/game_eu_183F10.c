#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15157734(u8 *arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156700.s")

s32 func_15156700(s32, u8, s32, u8, s32);
void func_151568F8(s32 arg0, u8 arg1, s32 arg2) {
    func_15156700(arg0, arg1, arg2, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15156A68.s")

s32 func_151308E4(void *, s32, s32, u8, s32);
typedef struct { f32 x, y, z; } V3_6E68;
typedef struct { s32 a, b; } V2_6E68;
void func_15156E68(u8 *arg0, u8 arg1) {
    struct {
        s16 u98;
        s16 u9A;
        V3_6E68 u9C;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        u8 uC0;
        u8 uC1;
        u8 uC2;
        u8 uC3;
        u8 uC4;
        u8 uC5;
        u8 uC6;
        u8 uC7;
        u8 uC8;
        u8 padC9[0x1];
        s16 uCA;
        s16 uCC;
        u16 uCE;
        f32 uD0;
        f32 uD4;
        u8 uD8;
        u8 uD9;
        s16 uDA;
        s16 uDC;
        u8 uDE;
        u8 padDF[0x1];
    } B;
    struct {
        s32 u28;
        s32 u2C;
        u16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        u8 u3C;
        u8 u3D;
        u8 u3E;
        u8 u3F;
        u8 u40;
        u8 u41;
        u8 u42;
        u8 u43;
        u8 u44;
        u8 u45;
        s16 u46;
        s16 u48;
        s16 u4A;
        f32 u4C;
        V2_6E68 u50;
        V3_6E68 u58;
        u8 pad64[0xC];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s32 u80;
        u8 pad84[0x4];
        u8 u88;
        u8 u89;
        s8 u8A;
        s8 u8B;
        u8 pad8C[0xC];
    } sp;

    B.u98 = *(s16 *)(arg0 + 0xC);
    B.u9A = *(s16 *)(arg0 + 0xE);
    B.u9C = *(V3_6E68 *)(arg0 + 0x0);
    B.uA8 = *(s16 *)(arg0 + 0x10);
    B.uAC = *(s16 *)(arg0 + 0x14);
    B.uAA = *(s16 *)(arg0 + 0x12);
    B.uAE = *(s16 *)(arg0 + 0x16);
    B.uB0 = *(f32 *)(arg0 + 0x18);
    B.uB4 = *(f32 *)(arg0 + 0x1C);
    B.uB8 = *(f32 *)(arg0 + 0x20);
    B.uBC = *(f32 *)(arg0 + 0x24);
    B.uC0 = *(u8 *)(arg0 + 0x28);
    B.uC1 = *(u8 *)(arg0 + 0x29);
    B.uC2 = *(u8 *)(arg0 + 0x2A);
    B.uC3 = *(u8 *)(arg0 + 0x2B);
    B.uC4 = *(u8 *)(arg0 + 0x2C);
    B.uC5 = *(u8 *)(arg0 + 0x2D);
    B.uC6 = *(u8 *)(arg0 + 0x2E);
    B.uC7 = *(u8 *)(arg0 + 0x2F);
    B.uC8 = *(u8 *)(arg0 + 0x30);
    B.uCA = *(s16 *)(arg0 + 0x32);
    B.uCC = *(s16 *)(arg0 + 0x34);
    B.uCE = *(u16 *)(arg0 + 0x36);
    B.uD0 = *(f32 *)(arg0 + 0x38);
    B.uD4 = *(f32 *)(arg0 + 0x3C);
    B.uD8 = *(u8 *)(arg0 + 0x40);
    B.uD9 = *(u8 *)(arg0 + 0x41);
    B.uDA = *(s16 *)(arg0 + 0x42);
    B.uDC = *(s16 *)(arg0 + 0x44);
    B.uDE = *(u8 *)(arg0 + 0x46);
    func_15153F24(&B, arg1);
    sp.u45 = *(u8 *)(arg0 + 0x47);
    sp.u30 = *(u16 *)(arg0 + 0x48);
    sp.u2C = *(s32 *)(arg0 + 0x50);
    sp.u28 = *(s32 *)(arg0 + 0x4C);
    sp.u34 = *(s32 *)(arg0 + 0x58);
    sp.u38 = *(s32 *)(arg0 + 0x5C);
    sp.u3C = *(u8 *)(arg0 + 0x60);
    sp.u3D = *(u8 *)(arg0 + 0x61);
    sp.u3E = *(u8 *)(arg0 + 0x62);
    sp.u3F = *(u8 *)(arg0 + 0x63);
    sp.u40 = *(u8 *)(arg0 + 0x64);
    sp.u41 = *(u8 *)(arg0 + 0x65);
    sp.u42 = *(u8 *)(arg0 + 0x66);
    sp.u58 = *(V3_6E68 *)(arg0 + 0x0);
    sp.u80 = *(s32 *)(arg0 + 0x80);
    sp.u43 = *(u8 *)(arg0 + 0x67);
    sp.u44 = *(u8 *)(arg0 + 0x68);
    sp.u8A = *(s8 *)(arg0 + 0x86);
    sp.u8B = *(s8 *)(arg0 + 0x87);
    sp.u46 = *(s16 *)(arg0 + 0x74);
    sp.u48 = *(s16 *)(arg0 + 0x76);
    sp.u88 = *(u8 *)(arg0 + 0x84);
    sp.u89 = *(u8 *)(arg0 + 0x85);
    sp.u4A = *(s16 *)(arg0 + 0x78);
    sp.u4C = *(f32 *)(arg0 + 0x7C);
    sp.u32 = *(s16 *)(arg0 + 0x54);
    sp.u50 = *(V2_6E68 *)(arg0 + 0x6C);
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    func_151308E4(&sp, arg0[0x88], 0, arg1, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_151570C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157294.s")

void func_15157504(s32 arg0) {
    func_151D5E30(arg0 + 0x88, arg0);
}

void func_15157528(struct102 *arg0) {
    func_15157504(arg0);
    func_15169804(arg0);
}

void func_15157554(struct102 *arg0) {
    func_15157504(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183F10/func_15157580.s")

void func_15157734(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0x104))[i]) {
            func_100043B4(((s32 *)(arg0 + 0x104))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0x114) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0x114), 4);
    }
}

void func_151577B8(struct102 *arg0) {
    func_15157734(arg0);
    func_1518CF74(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503FAA8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169804(arg0);
}

void func_151577FC(struct102 *arg0) {
    func_15157734(arg0);
    func_1518CF74(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503FAA8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169824(arg0);
}
