#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_1512DD50(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x14];
        f32 u40;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f4;
    f32 var_f6;
    s32 temp_t0;
    s32 temp_t1;
    u8 *temp_v0;
    u8 *temp_v1;

    sp.u40 = (f32) (*(s16 *)((u8 *)arg0 + 0x710));
    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x712));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x720)) * temp_f2;
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x724)) * temp_f2;
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x728)) * temp_f0;
    temp_f14 = -temp_f0 * (*(f32 *)((u8 *)arg0 + 0x72C));
    (*(f32 *)((u8 *)arg0 + 0x878)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0x70E)) - temp_f12);
    (*(f32 *)((u8 *)arg0 + 0x874)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0x70C)) - temp_f0_2);
    (*(f32 *)((u8 *)arg0 + 0x87C)) = (f32) (sp.u40 - temp_f14);
    sp.u20 = 2.0f * temp_f0_2;
    sp.u24 = 2.0f * temp_f12;
    sp.u28 = 2.0f * temp_f14;
    temp_f2_2 = 1.0f / func_150AD930(&sp.u20);
    temp_v0 = arg0 + 0x870;
    temp_v1 = arg0 + 0x6FC;
    (*(f32 *)((u8 *)temp_v0 + 0x1C)) = temp_f2_2;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) (temp_f2_2 * sp.u20);
    (*(f32 *)((u8 *)temp_v0 + 0x14)) = (f32) (temp_f2_2 * sp.u24);
    (*(f32 *)((u8 *)temp_v0 + 0x18)) = (f32) (temp_f2_2 * sp.u28);
    temp_t0 = (*(s32 *)((u8 *)temp_v1 + 0x20));
    var_f6 = (f32) temp_t0;
    if (temp_t0 < 0) {
        var_f6 += 4294967296.0f;
    }
    (*(f32 *)((u8 *)temp_v0 + 0x20)) = var_f6;
    temp_t1 = (*(s32 *)((u8 *)temp_v1 + 8));
    var_f4 = (f32) temp_t1;
    if (temp_t1 < 0) {
        var_f4 += 4294967296.0f;
    }
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = var_f4;
    (*(f32 *)((u8 *)temp_v0 + 0x28)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x2C)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0)) = (s8) (*(s32 *)((u8 *)temp_v1 + 0x1C));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/func_1512DD50.s")
#endif
// void func_1512DD50(struct108 *arg0) {
//     s32 pad;
//     struct17 tmp;
//
//     f32 temp_f0;
//     f32 temp_f0_2;
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f2;
//
//     struct127 *temp_v0;
//     struct164 *temp_v1;
//
//     temp_f2 = arg0->unk712;
//     temp_f0 = arg0->unk720 * temp_f2;
//     temp_f12 = arg0->unk724 * temp_f2;
//     temp_f0_2 = arg0->unk728 * temp_f0;
//     temp_f14 = -temp_f0 * arg0->unk72C;
//
//     arg0->unk874 = arg0->unk70C - temp_f0_2;
//     arg0->unk878 = arg0->unk70E - temp_f12;
//     arg0->unk87C = arg0->unk710 - temp_f14;
//
//     tmp.unk0 = 2.0f * temp_f0_2;
//     tmp.unk4 = 2.0f * temp_f12;
//     tmp.unk8 = 2.0f * temp_f14;
//
//     temp_f2 = 1.0f / func_150AD930(&tmp);
//     temp_v0 = arg0->unk870;
//     temp_v0->unk1C = temp_f2;
//     temp_v0->unk10 = temp_f2 * tmp.unk0;
//     temp_v0->unk14 = temp_f2 * tmp.unk4;
//     temp_v0->unk18 = temp_f2 * tmp.unk8;
//     temp_v1 = arg0->unk6FC;
//     temp_v0->unk20 = temp_v1->unk20;
//     temp_v0->unk24 = temp_v1->unk8;
//     temp_v0->unk28 = 0.0f;
//     temp_v0->unk2C = 0.0f;
//     temp_v0->unk0 = (s8) temp_v1->unk1C;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/func_1512DEA4.s")
