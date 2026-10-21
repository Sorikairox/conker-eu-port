#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_151037D4(s16, u8, f32, u8 *, u8, u8, s32);
s32 func_151506E8(s16 *, s32 *, s32, u8, s32);
s32 func_15182BE0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_151D44C4(u8 *, u8, s32);

void func_151DCC50(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s16 u38;
        s16 u3A;
        s16 u3C;
        s16 u3E;
        s32 u40;
        u8 pad44[0x8];
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        s8 u64;
        s8 u65;
        u8 pad66[0x2];
        f32 u68;
        f32 u6C;
        s8 u70;
        s8 u71;
        u8 pad72[0x2];
        f32 u74;
        s8 u78;
        u8 pad79[0x3];
        f32 u7C;
    } sp;
    s32 sp30;
    s32 sp2C;

    sp2C = func_150ADA20();
    sp30 = func_150ADA20();
    func_151037D4((s16) (((u32) sp2C % 5U) + 0xC), (((u32) sp30 % 56U) + 0xC8) & 0xFF, (func_150ADA68() * 600.0f) + 1700.0f, arg0, 0xFF, (s32) arg1, arg2);
    (*(s32 *)((u8 *)(&sp.u40) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u40) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u40) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u50 = 8.0f;
    sp.u4E = 7;
    sp.u54 = 10.0f;
    sp.u4C = 0xC;
    sp.u38 = 0;
    sp.u3A = 0xFF;
    sp.u3C = -0x40;
    sp.u3E = 0x3C;
    sp.u58 = 0x24;
    sp.u5A = 0x3C;
    sp.u64 = 0xC8;
    sp.u65 = 0x37;
    sp.u70 = 0;
    sp.u71 = 0xC;
    sp.u78 = 1;
    sp.u5C = -1.097f;
    sp.u60 = 0.37f;
    sp.u68 = 280.0f;
    sp.u6C = 390.0f;
    sp.u74 = 0.6f;
    sp.u7C = 1.0f;
    func_151506E8(&sp.u38, &sp.u40, 0, arg1, arg2);
    func_151D44C4(arg0, arg1, arg2);
    sp2C = func_150ADA20();
    func_15182BE0(0xFF, 0xFF, 0xFF, (((u32) sp2C % 51U) + 0x96) & 0xFF, (func_150ADA20() % 5U) + 8, 0, (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20A460/func_151DCC50.s")
#endif
void func_151DCC50(u8 *arg0, u8 arg1, s32 arg2);

void func_151DCE6C(u8 *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    typedef struct {
        s32 w[3];
    } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
        u8 unk10;
    } tmp;
    struct260 *temp_v0;

    if (arg2 != 0) {
        func_151DCC50(arg0, arg4, arg5);
    }
    tmp.unk0 = *(Blk12 *)arg0;
    tmp.unkC = 0.0f;
    tmp.unk10 = arg3;
    temp_v0 = func_15149130(arg1, -1, 0x5B, -1, 1, 0, 0x14, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20A460/func_151DCF2C.s")
