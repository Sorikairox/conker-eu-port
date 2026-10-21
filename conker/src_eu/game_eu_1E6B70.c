#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B8DB0.s")

#ifdef NON_MATCHING
extern f32 D_800AA944;   /* ~0.0234f (rodata) */
s32 func_151B97C4(u8 *arg0) {
    u8 *temp_v0;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f0_2;
    f32 temp_f0;
    u8 *sp18;

    (*(f32 *)((u8 *)arg0 + 0x178)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x178)) + ((*(f32 *)((u8 *)arg0 + 0x17C)) * D_800BE9A4));
    temp_f0 = func_15144B68((*(f32 *)((u8 *)arg0 + 0x178)));
    temp_v0 = arg0 + 0x170;
    (*(f32 *)((u8 *)temp_v0 + 8)) = temp_f0;
    sp18 = temp_v0;
    temp_f2 = (*(f32 *)((u8 *)sp18 + 4));
    temp_f12 = (*(f32 *)((u8 *)sp18 + 0x18));
    (*(f32 *)((u8 *)sp18 + 0)) = (f32) (sinf(temp_f0) * temp_f2);
    if (temp_f12 > 0.0f) {
        (*(f32 *)((u8 *)sp18 + 0x18)) = (f32) (temp_f12 - D_800BE9A4);
        (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) + ((*(f32 *)((u8 *)sp18 + 0x20)) * D_800BE9A4));
        (*(f32 *)((u8 *)sp18 + 4)) = (f32) (temp_f2 + ((*(f32 *)((u8 *)sp18 + 0x1C)) * D_800BE9A4));
    } else {
        temp_f0_2 = (*(f32 *)((u8 *)sp18 + 0xC));
        (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)sp18 + 0x14)) - temp_f0_2) * D_800AA944));
        (*(f32 *)((u8 *)sp18 + 4)) = (f32) (temp_f2 + (((*(f32 *)((u8 *)sp18 + 0x10)) - temp_f2) * D_800AA944));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B97C4.s")
#endif
s32 func_151B98C0(Mtx *arg0, u8 *arg1) {
    f32 mf[4][4];
    u8 *p;

    p = arg1;
    func_150A8050(mf, 0.0f, 0.0f, *(f32 *)(p + 0x170));
    mf[3][0] = *(f32 *)(p + 0x38);
    mf[3][1] = *(f32 *)(p + 0x3C);
    mf[3][2] = *(f32 *)(p + 0x40);
    mf[0][0] *= *(f32 *)(p + 0x18);
    mf[0][1] *= *(f32 *)(p + 0x18);
    mf[0][2] *= *(f32 *)(p + 0x18);
    mf[1][0] *= *(f32 *)(p + 0x1C);
    mf[1][1] *= *(f32 *)(p + 0x1C);
    mf[1][2] *= *(f32 *)(p + 0x1C);
    mf[2][0] *= *(f32 *)(p + 0x18);
    mf[2][1] *= *(f32 *)(p + 0x18);
    mf[2][2] *= *(f32 *)(p + 0x18);
    guMtxF2L(mf, arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B99B8.s")

void func_151B9C10(f32 *arg0) {
    arg0[0x188 / 4] = 5.0f;
    arg0[0x18C / 4] = D_800AA94C;
    arg0[0x190 / 4] = D_800AA950;
}
