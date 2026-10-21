#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1979F0/func_1516A1E0.s")

#ifdef NON_MATCHING
extern f32 D_800A70A8;
s32 func_1510FE58(s16, s16, s16, s32);
extern s32 D_8008CE7C;

void func_1516A964(u8 *arg0) {
    struct {
        s32 u2C;
        s16 u30;
        s16 u32;
        s16 u34;
        s16 u36;
        s16 u38;
        s16 u3A;
        s16 u3C;
        s8 u3E;
        u8 pad3F[0x1];
        s8 u40;
        u8 u41;
        u8 pad42[0x6];
        s32 u48;
    } sp;
    u8 temp_v0_2;
    s32 var_v1;
    s32 var_t0;
    s32 temp_v0;
    s16 temp_v1;

    var_v1 = (*(s32 *)((u8 *)arg0 + 0x14));
    var_t0 = (*(s16 *)((u8 *)arg0 + 0x22)) + (*(s16 *)((u8 *)arg0 + 0x2A));
    if (var_v1 >= var_t0) {
        sp.u48 = var_t0;
        func_1510F800(0);
        temp_v0 = func_1510FE58((*(s16 *)((u8 *)arg0 + 0x20)), (*(s16 *)((u8 *)arg0 + 0x22)), (*(s16 *)((u8 *)arg0 + 0x24)), 0);
        var_t0 = sp.u48;
        (*(s32 *)((u8 *)arg0 + 0x14)) = temp_v0;
        var_v1 = temp_v0;
    }
    if (var_v1 >= var_t0) {
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0;
        if ((var_t0 - var_v1) < 0x32) {
            sp.u30 = 0;
            sp.u32 = 0x100;
            sp.u2C = D_8008CE7C;
            sp.u34 = (*(s16 *)((u8 *)arg0 + 0x20));
            sp.u36 = (*(s32 *)((u8 *)arg0 + 0x14)) + 0xA;
            sp.u38 = (*(s16 *)((u8 *)arg0 + 0x24));
            temp_v0_2 = (*(u8 *)((u8 *)arg0 + 0x3B));
            sp.u3E = 0;
            sp.u40 = 3;
            temp_v1 = ((s32) (temp_v0_2 << 0xC) / 5100) + 0xCC;
            sp.u3A = temp_v1;
            sp.u3C = temp_v1;
            sp.u41 = temp_v0_2;
            func_15167AD8(&sp.u2C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
        }
    } else {
        (*(s16 *)((u8 *)arg0 + 0x26)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x26)) * D_800A70A8);
        (*(s16 *)((u8 *)arg0 + 0x28)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x28)) * D_800A70A8);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1979F0/func_1516A964.s")
#endif
s32 func_151722BC(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_1516AAA8(u8 *arg0) {
    s32 pad; // fakematch: frame slot
    u32 sp48;
    s32 sp44;

    if ((*(s16 *)((u8 *)arg0 + 0x14)) >= 0x300) {
        sp48 = func_150ADA20() % 3U;
        sp44 = (s32) (*(u8 *)((u8 *)arg0 + 0x25));
        func_151722BC((f32) (*(s16 *)((u8 *)arg0 + 0x18)), (f32) ((*(s16 *)((u8 *)arg0 + 0x1A)) - 0xA), (f32) (*(s16 *)((u8 *)arg0 + 0x1C)), 0x64, 0, sp48 + 0x20, (f32) (func_150ADA20() % 360U), 0, ((s32) (sp44 * 0x19) / 255) + 0x19, 0, 0x100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    }
}

s32 func_1516ABB8(u8 *arg0) {
    s32 a;
    s32 h;

    a = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (a != 0xFF) {
            a += D_800BE9E4 * 16;
            if (a >= 0x100) {
                a = 0xFF;
            }
            arg0[0x1F] = a;
        }
    } else if (a != 0) {
        a -= D_800BE9E4 * 4;
        if (a < 0) {
            a = 0;
        }
        arg0[0x1F] = a;
    }
    if (arg0[0x24] == 0 && a == 0) {
        return 1;
    }
    *(s16 *)(arg0 + 0x18) -= 300;
    func_1516FDD4(arg0);
    h = func_1510FE58(*(s16 *)(arg0 + 0xE), *(s16 *)(arg0 + 0x10), *(s16 *)(arg0 + 0x12), 0) + 10;
    arg0[0x2C] = h >> 8;
    arg0[0x2D] = h & 0xFF;
    if (*(s16 *)(arg0 + 0x10) < h) {
        *(s16 *)(arg0 + 0x10) = h;
        *(s16 *)(arg0 + 0x18) = *(s16 *)(arg0 + 0x18) * -0.5f;
        func_1516FEBC(arg0, 0xE6);
    }
    return 0;
}
