#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15102EA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_151030B8.s")

void func_151032D0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#ifdef NON_MATCHING
s32 func_15031C4C(u8 *, s16, s32);
void func_15145EA4(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3);
s32 func_1514654C(u8 *, s32, s32, u8 **, u8 **, s32);

s32 func_15103310(u8 *arg0) {
    u8 *sp44;
    u8 *sp40;
    u8 *sp3C;
    u8 *sp38;
    s16 temp_a1;
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x110));
    (*(u8 *)((u8 *)arg0 + 0x124)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x124)) & 0xFFFE);
    if (((*(u8 *)((u8 *)arg0 + 0x114)) != (*(u8 *)((u8 *)temp_s1 + 0x3B))) || ((*(s32 *)((u8 *)temp_s1 + 0)) == 0)) {
        return 0;
    }
    if (((*(s32 *)((u8 *)temp_s1 + 0x1D4)) == 0) || (((*(u8 *)((u8 *)temp_s1 + 0x74)) & 0xF) == 0xF)) {
        return 1;
    }
    temp_s0 = arg0 + 0x110;
    sp40 = arg0 + 0x34;
    sp44 = arg0 + 0x40;
    sp38 = temp_s0 + 0x18;
    sp3C = temp_s0 + 0x24;
    temp_a1 = (*(s16 *)((u8 *)temp_s0 + 0xC));
    if (temp_a1 != -1) {
        temp_v0 = func_15031C4C(temp_s1, temp_a1, 0);
        if (temp_v0 == 0) {
            return 0;
        }
        if (func_1514654C(temp_s1, temp_v0, (*(s32 *)((u8 *)temp_s0 + 0x10)), &sp40, &sp38, 2) == 0) {
            return 0;
        }
        goto block_12;
    }
    func_15145EA4(&sp40, &sp38, (*(s32 *)((u8 *)temp_s1 + 0x1D4)) + (*(s32 *)((u8 *)temp_s0 + 8)), 2);
block_12:
    (*(u8 *)((u8 *)temp_s0 + 0x14)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0x14)) | 1);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15103310.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15103438.s")

#ifdef NON_MATCHING
s32 func_151308E4(s32 *, s32, s32, u8, s32);
extern s32 D_80088F70;

void func_151037D4(s16 arg0, u8 arg1, f32 arg2, u8 *arg3, u8 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u2C;
        s32 u30;
        s16 u34;
        s16 u36;
        s32 u38;
        s32 u3C;
        s8 u40;
        s8 u41;
        s8 u42;
        s8 u43;
        s8 u44;
        s8 u45;
        s8 u46;
        u8 u47;
        s8 u48;
        s8 u49;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
        u8 pad88[0x4];
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        s8 u91;
        u8 u92;
    } sp;
    s32 sp24;
    s32 temp_t8;
    s32 var_v0;
    s32 var_v1;

    temp_t8 = *(((s32 *)((u8 *)&D_80088F70 + ((func_150ADA20() & 3) * 4))));
    sp.u30 = 0x20000;
    sp.u40 = 0xFF;
    sp.u34 = 0x2203;
    sp.u2C = 0x200005;
    sp.u49 = (s8) temp_t8;
    sp.u36 = arg0 + 1;
    sp.u38 = 0;
    sp.u3C = 0;
    sp.u41 = 0xFF;
    sp.u42 = 0xFF;
    sp.u43 = 0xFF;
    sp.u44 = 0xFF;
    sp.u45 = 0xFF;
    sp.u46 = 0xFF;
    sp.u48 = 0xFF;
    sp.u58 = arg2;
    sp.u54 = arg2;
    sp.u47 = arg1;
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)arg3 + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)arg3 + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)arg3 + 8));
    sp.u4A = 3;
    sp.u4C = 0x55;
    sp.u4E = 1;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    sp.u80 = 0.0f;
    sp.u50 = 1.0f;
    var_v1 = 0;
    if (func_150ADA20() & 1) {
        var_v1 = 0x40;
    }
    sp24 = var_v1;
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    sp.u84 = var_v0 | 1 | var_v1 | 0xC200 | 0x40000 | 0x800000;
    sp.u8C = 6;
    sp.u8D = 8;
    sp.u8E = -1;
    sp.u8F = -1;
    sp.u90 = -1;
    sp.u91 = 0;
    sp.u92 = arg4;
    func_151308E4(&sp.u2C, 1, 0, arg5, arg6);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_151037D4.s")
#endif