#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_15150258(u8 *, u8, s32);
void func_151C0AA8(u8 *, u8, s32);
void func_151C0B54(s32, u8, s32);
void func_151C0BA0(void *, u8, s32);

void func_150D7630(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s16 u1C;
        s16 u1E;
        s16 u20;
        s16 u22;
        s32 u24;
        s32 u28;
        s32 u2C;
        u8 pad30[0x8];
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s32 u50;
        s32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        s16 u72;
        s8 u74;
    } sp;

    func_151C0AA8(arg0, arg1, arg2);
    func_151C0B54(arg0, arg1, arg2);
    func_151C0BA0(arg0, arg1, arg2);
    sp.u1C = 0;
    sp.u1E = 0xFF;
    sp.u20 = -0x40;
    sp.u22 = 0x47;
    sp.u24 = 6;
    sp.u28 = 4;
    (*(s32 *)((u8 *)(&sp.u2C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u2C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u2C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u38 = 23.0f;
    sp.u3C = 30.0f;
    sp.u40 = 45.0f;
    sp.u44 = 53.0f;
    sp.u50 = 7;
    sp.u54 = 3;
    sp.u68 = 0x19;
    sp.u6A = 0xF;
    sp.u6C = 0x64;
    sp.u6E = 0x64;
    sp.u70 = 0xC;
    sp.u72 = 0x14;
    sp.u74 = 0;
    sp.u48 = 203.0f;
    sp.u4C = 414.0f;
    sp.u58 = 15.0f;
    sp.u5C = 0.87200004f;
    sp.u60 = -0.39800003f;
    sp.u64 = 0.36400002f;
    func_15150258(&sp.u1C, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_104E40/func_150D7630.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_104E40/func_150D779C.s")
