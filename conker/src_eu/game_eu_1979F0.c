#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1979F0/func_1516A1E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1979F0/func_1516A964.s")

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
