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

#ifdef NON_MATCHING
void func_150A7E40(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
/* searchlight_light_update: P237. D_8008B0F0 handler of the swinging searchlight (object at effect +0x18, which
 * func_151B97C4 swings: angle +0x170, position +0x38, scale +0x18 / +0x1C). The lamp point (0, -150, 0) of the
 * object's model matrix (func_151B98C0's matrix: rotation by +0x170, x / z scaled by +0x18, y by +0x1C, at +0x38)
 * becomes the light position (+0xE / +0x10 / +0x12 of effect +0x14). When the effect has a beam record (+0x1C), its
 * two points run from the object along the direction object -> lamp (scaled by effect +0x20 / 150): the first at
 * 65 * y scale from the object, the second 500 further. Returns 1. */
#define B9B8_BEAM (*(u8 **) ((u8 *) arg0 + 0x1C))
s32 func_151B99B8(struct225 *arg0) {
    u8 *obj = *(u8 **) ((u8 *) arg0 + 0x18);
    f32 mf[4][4];
    f32 x, y, z;
    f32 k, s, dx, dy, dz;

    func_150A8050(mf, 0.0f, 0.0f, *(f32 *) (obj + 0x170));
    mf[3][0] = *(f32 *) (obj + 0x38);
    mf[3][1] = *(f32 *) (obj + 0x3C);
    mf[3][2] = *(f32 *) (obj + 0x40);
    mf[0][0] *= *(f32 *) (obj + 0x18);
    mf[0][1] *= *(f32 *) (obj + 0x18);
    mf[0][2] *= *(f32 *) (obj + 0x18);
    mf[1][0] *= *(f32 *) (obj + 0x1C);
    mf[1][1] *= *(f32 *) (obj + 0x1C);
    mf[1][2] *= *(f32 *) (obj + 0x1C);
    mf[2][0] *= *(f32 *) (obj + 0x18);
    mf[2][1] *= *(f32 *) (obj + 0x18);
    mf[2][2] *= *(f32 *) (obj + 0x18);
    func_150A7E40(mf, 0.0f, -150.0f, 0.0f, &x, &y, &z);
    arg0->unk14->unkE = x;
    arg0->unk14->unk10 = y;
    arg0->unk14->unk12 = z;
    if (B9B8_BEAM == NULL) {
        return 1;
    }
    k = *(f32 *) (obj + 0x1C) * 65.0f;
    s = *(f32 *) ((u8 *) arg0 + 0x20) * -0.0066666668f; /* D_800AA948 */
    dx = -(x - *(f32 *) (obj + 0x38)) * s;
    dy = -(y - *(f32 *) (obj + 0x3C)) * s;
    dz = -(z - *(f32 *) (obj + 0x40)) * s;
    /* the beam pointer is re-read for every store, as in the asm */
    *(f32 *) (B9B8_BEAM + 0x34) = *(f32 *) (obj + 0x38) + dx * k;
    *(f32 *) (B9B8_BEAM + 0x38) = *(f32 *) (obj + 0x3C) + dy * k;
    *(f32 *) (B9B8_BEAM + 0x3C) = *(f32 *) (obj + 0x40) + dz * k;
    *(f32 *) (B9B8_BEAM + 0x40) = *(f32 *) (B9B8_BEAM + 0x34) + dx * 500.0f;
    *(f32 *) (B9B8_BEAM + 0x44) = *(f32 *) (B9B8_BEAM + 0x38) + dy * 500.0f;
    *(f32 *) (B9B8_BEAM + 0x48) = *(f32 *) (B9B8_BEAM + 0x3C) + dz * 500.0f;
    return 1;
}
#undef B9B8_BEAM
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B99B8.s")
#endif

void func_151B9C10(f32 *arg0) {
    arg0[0x188 / 4] = 5.0f;
    arg0[0x18C / 4] = D_800AA94C;
    arg0[0x190 / 4] = D_800AA950;
}
