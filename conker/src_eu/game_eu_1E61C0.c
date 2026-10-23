#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void *memcpy(void *, const void *, s32);
extern u8 D_800AA870[];
typedef struct { f32 x, y, z; } V3_151B89B0;

typedef struct {
    u8 u0;
    s8 u1;
    s16 u2;
    s16 u4;
    s16 pad6;
    s32 u8;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    V3_151B89B0 u1C;
    V3_151B89B0 u28;
    f32 u34[3];
    s32 u40;
    u8 u44;
    u8 u45;
    s8 u46;
    s8 u47;
    s32 u48;
    u8 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
} Blk58_89B0;

u8 *func_151B89B0(u8 *arg0) {
    s32 pad; // fakematch: 4-byte hole above tmp
    u8 *tmp;
    Blk58_89B0 blk;
    V3_151B89B0 pos;
    u8 *temp_v0;

    tmp = arg0;
    blk.u0 = 0xFF;
    blk.u1 = 0;
    blk.u2 = 0x5901;
    blk.u4 = 0x32;
    blk.u8 = 0;
    blk.uC = 0;
    blk.u10[0] = 0xFF;
    blk.u10[1] = 0xE6;
    blk.u10[2] = 0xB6;
    blk.u10[3] = 0xFF;
    blk.u14 = 9.0f;
    blk.u18 = 1.0f;
    pos = *(V3_151B89B0 *)(arg0 + 0x38);
    blk.u28 = pos;
    blk.u1C = pos;
    blk.u34[0] = *(f32 *)(arg0 + 0x44) * 0.25f;
    blk.u34[1] = *(f32 *)(arg0 + 0x48) * 0.25f;
    blk.u34[2] = *(f32 *)(arg0 + 0x4C) * 0.25f;
    blk.u40 = 0x0CCC0000;
    blk.u44 = 0xC8;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 6;
    blk.u48 = 0;
    blk.u4C = 0xFF;
    blk.u50 = 0;
    blk.u54 = 0x32;
    blk.u56 = 5;
    temp_v0 = func_1513D2F0(&blk, (s32)D_800AA870, 0x1B, 0, 0, 0x19, 0, 0, 0, 4, arg0[0xC], arg0[1]);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x110, &tmp, 4);
    }
    return temp_v0;
}

s32 func_151B8B5C(u8 *arg0)
{
    u8 *p = *(u8 **)(arg0 + 0x110);
    if (p != NULL) {
        *(vertex *)(arg0 + 0x34) = *(vertex *)(p + 0x38);
        *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x44) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
        *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    } else {
        *(s32 *)(arg0 + 0x58) |= 1;
    }
    return 1;
}

void func_151B8BEC(s32 arg0, s16 arg1) {
    func_1513FA70(arg0, arg1);
}

extern f32 D_800DCE54;
void func_151B8C18(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *p;
    struct_eu_EF410 sp18;

    p = arg0;

    sp18.unk0 = (s32) (p + 0x38);
    sp18.unk4 = (s32) (p + 0x3C);
    sp18.unk8 = (s32) (p + 0x40);
    sp18.unkC = 10.0f;
    sp18.unk10 = 0.2075f * D_800DCE54;
    sp18.unk14 = 300;
    sp18.unk16 = 0;
    sp18.unk17 = 3;
    sp18.unk18 = 0;
    func_15134908(&sp18, 0, arg1, arg2);
}

void func_15143794(s16, s16, f32, void *);
#ifdef NON_MATCHING
s32 func_151A2C9C(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */
#else
s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif

void func_151B8CA4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    func_15143794((s16) (func_150ADA20() & 0xFF), (s16) ((func_150ADA20() % 65U) - 0x20), func_150ADA68() * 945.0f * 0.01f, &sp6C[3]);
    temp_f2 = (func_150ADA68() * 157.0f) + 604.0f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = temp_f2 * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
#ifdef NON_MATCHING
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 1.0f, ((func_150ADA68() * 157.0f) + -151.0f) * 0.001f, (func_150ADA68() * 55.0f) + 75.0f, (func_150ADA20() % 26U) + 0x19, (func_150ADA20() % 101U) + 0x64, 0xA, 0x19, 0, -1, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1))); /* P95: float literal (asm passes the bits 0x3F800000) */
#else
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 0x3F800000, ((func_150ADA68() * 157.0f) + -151.0f) * 0.001f, (func_150ADA68() * 55.0f) + 75.0f, (func_150ADA20() % 26U) + 0x19, (func_150ADA20() % 101U) + 0x64, 0xA, 0x19, 0, -1, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
#endif
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E61C0/func_151B8EB8.s")
