#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_8009FB60[];
#endif

u8 *func_151149AC(u8);

// The callee (game_eu_1FB080.c) takes only the first three arguments.
void func_151CFE48(s32 arg0, f32 arg1, f32 arg2, s16 *arg3);


extern s32 * D_800DC3C4;
void func_150AF6E0(s32 arg0, u8 arg1) {
    s32 i;
    if (D_800CC3D4[0] == 0) {
        i = (struct131 *)func_151149AC(arg0) - D_800DBEF4;
        if (D_800DC3C4[i] & 1) {
            func_1505D024(D_800CC2D0, 0x3F, 0x6E00, -1);
            return;
        }
        i = (struct131 *)func_151149AC(arg1) - D_800DBEF4;
        if (D_800DC3C4[i] & 1) {
            func_1505D024(D_800CC2D0, 0x3F, 0xEE00, -1);
        }
    }
}

void func_150AF7C0(s32 arg0, s16 *arg1) {
    func_151CFE48(arg0, (f32)(arg1[4] + arg1[1]), (f32)arg1[1], arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AF808.s")

s32 func_150AFBC4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}

u8 * func_151604E4(void *arg0, s32 arg1, u8 arg2, s32 arg3);

void func_150AFC18(s16 arg0, u8 arg1, s32 arg2) {
    struct {
        s8 unk0;
        s8 unk1;
        s8 unk2;
        s16 unk4;
        s8 unk6;
    } sp18;

    sp18.unk0 = 1;
    sp18.unk1 = -1;
    sp18.unk2 = 2;
    sp18.unk6 = 0;
    sp18.unk4 = arg0;
    func_151604E4(&sp18, 0, arg1, arg2);
}

void func_150AFC70(s32 arg0, s32 arg1) {
    func_150B2290(arg1, arg1 + 0x1ECC0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AFCA4.s")

s32 func_150B00D4(u8 *arg0) {
    u8 *v = arg0 + 0x70;
    *(f32 *)(arg0 + 0x78) = *(f32 *)(arg0 + 0x7C) * D_800BE9A4 + *(f32 *)(arg0 + 0x78);
    *(f32 *)(v + 8) = func_15144B68(*(f32 *)(arg0 + 0x78));
    *(f32 *)(arg0 + 0x10) = *(f32 *)v + *(f32 *)(v + 4) * sinf(*(f32 *)(v + 8));
    return 1;
}

s32 func_1516DF0C(s16, s16, s16, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, s16, s16, s16, s16, u16, u8, u8, u8, u8, s16, u16, u16, u8, u8, u8, u8, u8, s32, u8, u8, u8, s32);

void func_150B0148(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516DF0C(1, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 1, 0, 0, 0, 0, 0xAA, 0xAA, 0xAA, 0xAA, arg2, arg3, 0, arg0, 0xF0, 0x50, 0x50, 1, 4, 0, 1, 0, 0, 0, arg1, 0, (s32) arg4, arg5);
}

extern struct_eu_node *D_800DD2C4;
void func_150B0290(void) {
    struct_eu_node *node;

    node = D_800DD2C4;
    D_800DD5C0++;
    while (node != NULL) {
        D_800DD5C8[D_800DD5C0] = node->next;
        if (D_800C3E78 == ((u8 *)node)[0x3F]) {
            func_1516972C((struct102 *)node);
        }
        node = D_800DD5C8[D_800DD5C0];
    }
    D_800DD5C0--;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0344.s")

void func_150B051C(s32 arg0) {
    if (D_800BE9F0 == 6) {
        func_15179008(0);
        func_150AF6E0(0xE2, 0xE1);
    } else {
        func_150AF6E0(0xDF, 0xDE);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0574.s")

void func_150B07A0(struct102 **arg0) {
    if (*(s32 *)&arg0[0x170 / 4] != 0) {
        func_1516972C(arg0[0x170 / 4]);
    }
}

void func_150B07D0(u8 *arg0) {
    func_150B07A0(arg0);
    func_15132AE0(arg0);
}

void func_150B07FC(u8 *arg0) {
    func_150B07A0(arg0);
    func_15132B0C(arg0);
}

#ifdef NON_MATCHING
s32 func_15153BA4(s16 *, s32, u8, s32);
extern s32 D_8009FB74;

void func_150B0828(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u2C;
        s32 u30;
        s32 u34;
        u8 pad38[0x8];
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s8 u6C;
        u8 pad6D[0x1];
        s16 u6E;
        s32 u70;
        s32 u74;
        s16 u78;
        s16 u7A;
        s32 u7C;
        s32 u80;
        s8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s16 u8E;
        s16 u90;
        s16 u92;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x8];
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        u8 padCD[0x3];
        f32 uD0;
        s32 uD4;
        f32 uD8;
        f32 uDC;
    } sp;

    sp.uD4 = (*(s32 *)((u8 *)arg0 + 0x14));
    sp.uD8 = (*(f32 *)((u8 *)arg0 + 0x18)) + 30.0f;
    sp.uDC = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u68 = 0xA;
    sp.u6A = 7;
    sp.u6C = 0x6C;
    sp.u6E = 0x5103;
    sp.u70 = 0x200005;
    sp.u78 = 0x1E;
    sp.u7A = 0xF;
    sp.u87 = 0xFF;
    sp.u84 = 0x7F;
    sp.u86 = 6;
    sp.u74 = 0;
    sp.u7C = 0;
    sp.u80 = 0;
    sp.u85 = 0x4B;
    sp.u88 = 0x80;
    sp.u89 = 0x53;
    sp.u8A = 0;
    sp.u8B = 0x64;
    sp.u8C = 0x64;
    sp.u8D = 0xFF;
    sp.u8E = 0x20;
    sp.u90 = 7;
    sp.u92 = 0x20;
    sp.u94 = 1.025729f;
    sp.u98 = 351.0f;
    sp.u9C = 200.0f;
    (*(s32 *)((u8 *)(&sp.uA0) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 0));
    (*(s32 *)((u8 *)(&sp.uA0) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 4));
    (*(s32 *)((u8 *)(&sp.uA0) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 8));
    sp.uAC = 0;
    sp.uAE = -0x19;
    sp.uB0 = 0xFF;
    sp.uB2 = 0x15;
    sp.uC4 = 0x40E07;
    sp.uC8 = 0x10;
    sp.uC9 = -1;
    sp.uCA = 8;
    sp.uCB = 6;
    sp.uCC = 1;
    sp.uB4 = 5.0f;
    sp.uB8 = 25.0f;
    sp.uBC = 0.008f;
    sp.uC0 = 0.266f;
    sp.uD0 = 0.938608f;
    func_15153BA4(&sp.u68, 0xFF, arg1, arg2);
    sp.u2C = 0x24;
    sp.u30 = 0xA;
    (*(s32 *)((u8 *)(&sp.u34) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 0));
    (*(s32 *)((u8 *)(&sp.u34) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 4));
    (*(s32 *)((u8 *)(&sp.u34) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 8));
    sp.u48 = 11.0f;
    sp.u4C = 8.0f;
    sp.u40 = 0;
    sp.u42 = 0xFF;
    sp.u44 = -0x28;
    sp.u46 = 0x14;
    sp.u58 = 0x22;
    sp.u5A = 0xF;
    sp.u50 = -1.09f;
    sp.u54 = 0.37100002f;
    sp.u5C = 0.30200002f;
    sp.u60 = 0.31800002f;
    sp.u64 = 9.687f;
    func_15152700(&sp.u2C, ((u8 *)&D_8009FB60), &D_8009FB74, 5, 65.0f, 0U, (u8) (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0828.s")
#endif
s32 func_150B0AEC(u8 arg0, u8 *arg1) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = func_151149AC(arg0);
    (*(u8 **)((u8 *)arg1 + 8)) = temp_v0;
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 8));
    (*(f32 *)((u8 *)arg1 + 0)) = -150.0f;
    (*(f32 *)((u8 *)arg1 + 4)) = 4.5f;
    (*(f32 *)((u8 *)arg1 + 0xC)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x12));
    (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x14));
    return 1;
}
