#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B8EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B9424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B9A40.s")

s32 func_150B9ADC(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 32) {
        arg0[0x5C] = temp_v0 * 8;
    }
    return 1;
}

s32 func_150B9AFC(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 64) {
        arg0->unk28 = temp_v0 * 4;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E66D0/func_150B9B1C.s")

s32 func_15142600(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_150BA1F4(s32 arg0, u8 *arg1) {
    func_15142600(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40), *(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28));
    return 1;
}

typedef struct { s32 u0; s16 u4; u8 u6; s32 u8; s32 uC; u8 u10; u8 u11; u8 u12; u8 u13; u8 u14; u8 u15; s32 u18; u8 pad[16]; } BA_S;
void func_150BA26C(u8 *arg0) {
    BA_S s;
    s32 c;
    s32 b;
    s32 a;

    if (*(s16 *)(arg0 + 0x98) == -1) {
        s.u6 = 4;
        s.u8 = 0;
        s.uC = 0;
        s.u0 = 0x11;
        s.u4 = 0x64;
        s.u10 = 0xFF;
        s.u11 = *(s32 *)(arg0 + 0x90);
        s.u12 = 0;
        s.u13 = 0;
        s.u14 = 0;
        s.u15 = 0xFF;
        s.u18 = 0x30001;
        a = func_150ADA20();
        b = func_150ADA20();
        c = func_150ADA20();
        func_1513C4EC((s32)&s, 0, 2, 0, *(s16 *)(arg0 + 0x9C), *(s16 *)(arg0 + 0xA6) + 2, *(s16 *)(arg0 + 0xA0), *(s16 *)(arg0 + 0xA2), *(s16 *)(arg0 + 0xA2), a & 0xFF, (u8)((b & 1) + (c & 1) * (a = 2)) /* fakematch: permuter, reuses a's register */, 3, 0xFF, 0, arg0[0xC], arg0[1]);
    }
}
