#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A2720[];
#endif


void func_15103C10(s32 arg0) {
    func_15103828();
}

#ifdef NON_MATCHING
extern s32 D_800A2724;

void func_15103C34(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u2C;
        s32 u30;
        s32 u34;
        s32 u38;
        s32 u3C;
        u8 pad40[0x8];
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
    } sp;

    sp.u30 = *((u8 *)&D_800A2720);
    sp.u2C = D_800A2724;
    sp.u34 = 8;
    sp.u38 = 4;
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u50 = 8.0f;
    sp.u54 = 4.0f;
    sp.u48 = 0;
    sp.u4A = 0xFF;
    sp.u4C = -0x40;
    sp.u4E = 0x5D;
    sp.u60 = 0x14;
    sp.u62 = 0xA;
    sp.u58 = -0.70600003f;
    sp.u5C = 0.32200003f;
    sp.u64 = 0.25100002f;
    sp.u68 = 0.19900002f;
    sp.u6C = 30.696001f;
    func_15152700(&sp.u34, &sp.u30, &sp.u2C, 1, 0.0f, 1U, (u8) (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131420/func_15103C34.s")
#endif
s32 func_15103D5C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}
