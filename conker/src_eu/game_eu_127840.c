#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150F9BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA738.s")

void func_150FA9E8(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_t6;

    temp_t6 = arg2;
    if (temp_t6 == 0x4C) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0U, 0U, 0U, 0xFF);
        return;
    }
    if (temp_t6 == 0x4D) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = 0x1E;
        return;
    }
    if (temp_t6 == 0x4E) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        return;
    }
    if (temp_t6 == 0x4F) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0xFFU, 0xFFU, 0xFFU, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA520.s")

extern u8 D_80088F00;

void func_150FAFC0(u8 arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 *unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    if (D_80088F00 == 0) {
        tmp.unk0 = D_800D34B8 + 0x71C;
        tmp.unk4 = D_800D34B8 + 0x6E8;
        tmp.unk8 = 0.0f;
        temp_v0 = func_15149130(300, -1, 0x57, -1, 0, 0x46, 0xC, arg0, arg1);
        if (temp_v0 != NULL) {
            D_80088F00 = 1;
        }
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB06C.s")

void func_150FB264(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}

void func_150FB2A8(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x30);
    func_151494E0(0, 0x4D);
}

void func_150FB2F8(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x31);
    func_151494E0(0, 0x4C);
}

void func_150FB348(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x53) {
        *(s32 *)(arg0 + 0x58) |= 2;
    } else if (arg2 == 0x54) {
        *(s32 *)(arg0 + 0x58) &= ~2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB398.s")

#ifdef NON_MATCHING
void func_1515835C(u8 *arg0, u8 *arg1);

s32 func_150FB708(u8 *arg0) {
    struct {
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
    } sp;

    (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x54)) = -95.0f;
    (*(f32 *)((u8 *)arg0 + 0x58)) = -80.0f;
    sp.u1C = 0.0f;
    sp.u20 = 0.0f;
    sp.u24 = 0.0f;
    sp.u28 = 0.3f;
    sp.u2C = 0.3f;
    func_1515835C(arg0, &sp.u1C);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB708.s")
#endif
s32 func_151584F0(s32, s32, s32, s32, s32);
s32 func_151D76BC(s32, s32, s32, s32, s32);
void func_150FB768(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_151584F0(func_151D76BC(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}

void func_150FB7C0(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((arg2 - arg3) < arg1) {
        *arg0 = (arg2 - arg1) * arg4;
        return;
    }
    *arg0 = 0xFF;
}

s32 func_150FB81C(u8 *arg0) {
    func_150FB7C0(arg0 + 0x43, *(s16 *)(arg0 + 0x16), *(s16 *)(arg0 + 0x120), *(s16 *)(arg0 + 0x64), *(s16 *)(arg0 + 0x66));
    return 1;
}

s32 func_150FB860(u8 *arg0) {
    func_150FB7C0(arg0 + 0x2E, *(s16 *)(arg0 + 0x22), *(s16 *)(arg0 + 0x70), *(s16 *)(arg0 + 0x26), *(s16 *)(arg0 + 0x28));
    return 1;
}

#ifdef NON_MATCHING
void func_150FF1A8(s32, u8, s32, s32, s32, u8, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
extern s32 D_800A2100;
extern s32 D_800A210C;
extern s32 D_800A2118;
extern s32 D_800A2124;

void func_150FB8A4(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 * u2C;
        f32 * u30;
        f32 * u34;
        s32 * u38;
        s32 * u3C;
        s32 * u40;
        s32 u44;
        u8 pad48[0x8];
        s32 u50;
        u8 pad54[0x8];
        s32 u5C;
        u8 pad60[0x8];
        s32 u68;
        u8 pad6C[0xC];
        s32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        s32 u94;
    } sp;
    s32 temp_a2;

    (*(s32 *)((u8 *)(&sp.u68) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 0));
    (*(s32 *)((u8 *)(&sp.u68) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 4));
    (*(s32 *)((u8 *)(&sp.u68) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 8));
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 8));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 0));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 4));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 8));
    (*(s32 *)((u8 *)(&sp.u44) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 0));
    (*(s32 *)((u8 *)(&sp.u44) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 4));
    (*(s32 *)((u8 *)(&sp.u44) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 8));
    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        sp.u38 = &sp.u68;
        sp.u3C = &sp.u50;
        sp.u40 = &sp.u44;
        sp.u2C = &sp.u94;
        sp.u30 = &sp.u88;
        sp.u34 = &sp.u7C;
        temp_a2 = (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x380;
        sp.u78 = temp_a2;
        func_15145EA4(&sp.u38, &sp.u2C, temp_a2, 3);
        sp.u7C -= sp.u88;
        sp.u80 -= sp.u8C;
        sp.u84 -= sp.u90;
        func_150FF1A8(arg0, 0xE, &sp.u68, &sp.u5C, &sp.u94, (s32) arg1, arg2);
        func_151D49B8(&sp.u88, &sp.u7C, sp.u78, arg0, 1.0f, (s32) arg1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB8A4.s")
#endif