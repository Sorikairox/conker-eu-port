#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
void area_drift_emitter_create(void *, u8);
/* P18: D_80095B48/4C/50 are rodata f32 words (variables.h: u8[]); the body used to define them as u8[4] and read one byte */

/* was func_15008BF0 */
s32 area_drift_emitter_spawn(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        s16 u28;
        s16 u2A;
        s16 u2C;
        s16 u2E;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        s16 u6C;
        s16 u6E;
        s32 u70;
        s32 u74;
    } sp;

    (*(u8 *)((u8 *)arg0 + 0x16)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x16)) | 4);
    sp.u54 = 0.0f;
    sp.u50 = (f32) (*(s16 *)((u8 *)arg0 + 6)) * 0.19600001f * *(f32 *)D_80095B48;
    sp.u70 = 4;
    sp.u74 = 2;
    sp.u60 = 0x64;
    sp.u62 = 0x64;
    sp.u6C = 0x28;
    sp.u6E = 0x14;
    sp.u58 = 7.0f;
    sp.u5C = 6.0f;
    sp.u48 = *(f32 *)D_80095B4C;
    sp.u4C = 7.5f;
    sp.u64 = *(f32 *)D_80095B50;
    sp.u68 = 0.60700005f;
    sp.u2A = 0x14;
    sp.u28 = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x10)) * 0.7111111f);
    sp.u2E = 8;
    sp.u2C = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0xC)) * 0.7111111f) - 64.0f);
    vec2_from_angle_byte((s16) (sp.u28 - 0x40), (f32) (*(s16 *)((u8 *)arg0 + 6)), &sp.u20, &sp.u24);
    sp.u30 = (f32) (*(s16 *)((u8 *)arg0 + 0)) - sp.u20;
    sp.u34 = (f32) (*(s16 *)((u8 *)arg0 + 2));
    sp.u3C = 2.0f * sp.u20;
    sp.u40 = 0.0f;
    sp.u38 = (f32) (*(s16 *)((u8 *)arg0 + 4)) - sp.u24;
    sp.u44 = 2.0f * sp.u24;
    area_drift_emitter_create(&sp.u28, (*(u8 *)((u8 *)arg0 + 0x1B)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_360A0/area_drift_emitter_spawn.s")
#endif
// NON-MATCHING: absolute mess
// s32 area_drift_emitter_spawn(struct110 *arg0) {
//     struct109 tmp;
//     f32 foo;
//     f32 bar = D_80095B40;
//
//     arg0->unk16 |= 4;
//     foo = arg0->unk6 * D_80095B44 * D_80095B48;
//
//     tmp.unk54 = 0.0f;
//     tmp.unk50 = foo;
//
//     tmp.unk70 = 4;
//     tmp.unk74 = 2;
//     tmp.unk60 = 100;
//     tmp.unk62 = 100;
//     tmp.unk6C = 40;
//     tmp.unk6E = 20;
//     //
//     tmp.unk58 = 7.0f;
//     tmp.unk5C = 6.0f;
//     tmp.unk48 = D_80095B4C;
//     tmp.unk4C = 7.5f;
//     tmp.unk64 = D_80095B50;
//     tmp.unk68 = D_80095B54;
//     tmp.unk2A = 20;
//     tmp.unk28 = arg0->unk10 * bar;
//     tmp.unk2E = 8;
//     tmp.unk2C = ((arg0->unkC * bar) - 64.0f);
//
//     vec2_from_angle_byte(tmp.unk28 - 64, arg0->unk6, &tmp.unk20, &tmp.unk24);
//
//     tmp.unk30 = arg0->unk0 - tmp.unk20;
//     tmp.unk34 = arg0->unk2;
//     tmp.unk3C = tmp.unk20 + tmp.unk20;
//     tmp.unk40 = 0.0f;
//     tmp.unk38 = arg0->unk4 - tmp.unk24;
//     tmp.unk44 = tmp.unk24 + tmp.unk24;
//
//     func_15189900(&tmp, arg0->unk1B);
//
//     return 1;
// }
