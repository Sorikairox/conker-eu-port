#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB7E0/func_150ADFD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB7E0/func_150AE760.s")

s32 func_150AE83C(s32 arg0) {
    return 1;
}

#ifdef NON_MATCHING
void func_15142914(s32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_150AE84C(u8 *arg0, s16 arg1) {
    struct {
        u8 u43;
        u8 * u44;
        u8 pad48[0x44];
        f32 u8C;
        f32 u90;
        f32 u94;
        u8 pad98[0x8];
        u8 * uA0;
        u8 * uA4;
    } sp;
    u8 *sp3C;                                     /* compiler-managed */
    s32 sp38;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f18;
    s32 temp_f18_2;
    s32 temp_f4;
    s32 temp_f8;
    u8 *temp_v0;
    u8 *temp_v0_2;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.uA4, &sp.u43);
    sp.uA0 = sp.uA4;
    if (sp.uA4 != NULL) {
        if (sp.u43 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp38 = temp_a1;
            sp3C = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x160));
        sp3C = arg1 * 4;
        func_15142914((f32 (*)[4]) &sp.u44[0], (*(s32 *)((u8 *)temp_v0_2 + 0x18)), (*(s32 *)((u8 *)temp_v0_2 + 0x1C)), (*(s32 *)((u8 *)temp_v0_2 + 0x20)), (*(f32 *)((u8 *)temp_v0_2 + 0x24)), (*(f32 *)((u8 *)temp_v0_2 + 0x28)), (*(f32 *)((u8 *)temp_v0_2 + 0x38)), (*(f32 *)((u8 *)temp_v0_2 + 0x3C)), (*(f32 *)((u8 *)temp_v0_2 + 0x40)));
        func_150A7E40((f32 (*)[4]) &sp.u44[0], (*(f32 *)((u8 *)arg0 + 0x34)), (*(f32 *)((u8 *)arg0 + 0x38)), (*(f32 *)((u8 *)arg0 + 0x3C)), &sp.u8C, &sp.u90, &sp.u94);
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        (*(s16 *)((u8 *)sp.uA4 + 6)) = 0;
        temp_f2 = *(s32 *)((s32)&D_800DD618 + (s32)sp3C) * (s32)temp_f0;
        (*(s16 *)((u8 *)sp.uA4 + 0x16)) = 0;
        temp_f12 = *(s32 *)((s32)&D_800DD608 + (s32)sp3C) * (s32)temp_f0;
        (*(s16 *)((u8 *)sp.uA4 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.uA4 + 0x36)) = 0;
        temp_f10 = (s32) (sp.u8C + temp_f2);
        (*(s16 *)((u8 *)sp.uA4 + 0x30)) = (s16) temp_f10;
        (*(s16 *)((u8 *)sp.uA4 + 0)) = (s16) temp_f10;
        temp_f18 = (s32) sp.u90;
        (*(s16 *)((u8 *)sp.uA4 + 0x12)) = (s16) temp_f18;
        (*(s16 *)((u8 *)sp.uA4 + 2)) = (s16) temp_f18;
        temp_f8 = (s32) (sp.u94 - temp_f12);
        (*(s16 *)((u8 *)sp.uA4 + 0x34)) = (s16) temp_f8;
        (*(s16 *)((u8 *)sp.uA4 + 4)) = (s16) temp_f8;
        temp_f18_2 = (s32) (sp.u8C - temp_f2);
        (*(s16 *)((u8 *)sp.uA4 + 0x20)) = (s16) temp_f18_2;
        (*(s16 *)((u8 *)sp.uA4 + 0x10)) = (s16) temp_f18_2;
        temp_f10_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) + sp.u90);
        (*(s16 *)((u8 *)sp.uA4 + 0x32)) = (s16) temp_f10_2;
        (*(s16 *)((u8 *)sp.uA4 + 0x22)) = (s16) temp_f10_2;
        temp_f4 = (s32) (sp.u94 + temp_f12);
        (*(s16 *)((u8 *)sp.uA4 + 0x24)) = (s16) temp_f4;
        (*(s16 *)((u8 *)sp.uA4 + 0x14)) = (s16) temp_f4;
        return sp.uA0;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB7E0/func_150AE84C.s")
#endif