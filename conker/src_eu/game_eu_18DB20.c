#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_15160310.s")

u8 *func_151604E4(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x34, arg3, arg1 + 0x18, 1, (u8) (s32) arg2, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0xE, arg0, 8);
    return temp_v0;
}

extern s32 (*D_8008B470[])(void);
void func_1516055C(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0xE] & 1) != 0) {
        *(s16 *)(arg0 + 0x12) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x12) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0xF) != -1) && (D_8008B470[*(s8 *)(arg0 + 0xF)]() == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}

void func_eu_15160600(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_8008B484[arg0[0x14]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

s32 func_15160648(u8 *arg0) {
    s32 i;
    f32 *p;

    i = 0;
    p = (f32 *)(arg0 + 0x18);
    p[0] = func_151422DC(i++, "pos s", -2000, 2000, 0, "../Effects/ColourFrameBuffer/colourframebuffer.c", 452) * 0.001f;
    p[1] = func_151422DC(i++, "pos t", -2000, 2000, 0, "../Effects/ColourFrameBuffer/colourframebuffer.c", 457) * 0.001f;
    p[2] = func_151422DC(i++, "size s", 0, 2000, 500, "../Effects/ColourFrameBuffer/colourframebuffer.c", 462) * 0.001f;
    p[3] = func_151422DC(i++, "size t", 0, 2000, 500, "../Effects/ColourFrameBuffer/colourframebuffer.c", 467) * 0.001f;
    *(s32 *)&p[4] = func_151422DC(i++, "pixelation", 0, 0x10000, 0x10000, "../Effects/ColourFrameBuffer/colourframebuffer.c", 473);
    return 1;
}

void func_151607E4(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x34};

    func_15169260(sp1C, 0x1, arg0, arg1);
}
