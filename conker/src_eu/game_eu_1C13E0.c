#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15152A90(f32, f32, s32 *);

void func_15193660(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u28;
        u8 pad2C[0x8];
        s16 u34;
        s16 u36;
        s16 u38;
        s16 u3A;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        s8 u91;
        s16 u92;
        s16 u94;
    } sp;
    s32 sp24;
    s32 sp20;
    s32 temp_v0;

    if ((arg0 != NULL) && ((*(s32 *)((u8 *)arg0 + 0)) != 0)) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x1D4));
        if (temp_v0 != 0) {
            func_15142314(temp_v0, 0xA, &sp.u28);
            sp20 = 8;
            sp.u3C = 12.403001f;
            sp24 = 7;
            sp.u38 = -0x21;
            sp.u3A = 0x18;
            sp.u50 = 0x28;
            sp.u52 = 0x23;
            sp.u54 = 0xA0;
            sp.u58 = 0x13;
            sp.u90 = 0x21;
            sp.u88 = 0xFF;
            sp.u34 = 0;
            sp.u36 = 0xFF;
            sp.u5C = 0;
            sp.u89 = 0xFF;
            sp.u8A = 0xFF;
            sp.u8B = 0xFF;
            sp.u8C = 0xFF;
            sp.u8D = 0xFF;
            sp.u8E = 0xFF;
            sp.u8F = 0xFF;
            sp.u91 = 0xF;
            sp.u92 = 0x19;
            sp.u94 = 0xA;
            sp.u78 = -12.86f;
            sp.u70 = -12.86f;
            sp.u84 = 25.38f;
            sp.u7C = 25.38f;
            sp.u40 = 5.039f;
            sp.u44 = 0.908871f;
            sp.u48 = -0.707f;
            sp.u4C = 0.261f;
            sp.u64 = 1.96f;
            sp.u60 = 0.0f;
            sp.u6C = 0.0f;
            sp.u74 = 0.0f;
            sp.u80 = 0.0f;
            sp.u68 = 0.307f;
            func_15152A90(0, 25.38f, arg2);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C13E0/func_15193660.s")
#endif
typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} SpA3C;
s32 func_15134DAC(SpA3C *, s32, ...);
extern f32 D_800A85C4;

void func_151937F4(u8 *arg0, s32 arg1, s32 arg2) {
    SpA3C s;

    if (arg0 != NULL && *(s32 *)arg0 != 0) {
        s.u0 = arg0[0x3B];
        s.u4 = arg0;
        s.u8_ = 0;
        s.uC = -28.0f;
        s.u10 = 6.0f;
        s.u14 = 1.0f;
        s.u18 = -58.0f;
        s.u1C = -3.0f;
        s.u20 = -31.0f;
        s.u24 = 2;
        s.u26 = 30;
        s.u28 = 25;
        s.u2A = 750;
        s.u2E = 3;
        s.u2F = 3;
        s.u30 = -1;
        s.u34 = D_800A85C4;
        s.u38 = 4;
        s.u39 = -1;
        func_15134DAC(&s, 0, arg0);
    }
}

s32 func_15193E54(struct102 *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = D_800A85C8;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C13E0/func_15193E6C.s")
