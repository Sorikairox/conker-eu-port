#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4AF0.s")

#ifdef NON_MATCHING
void func_1514373C(f32, f32, f32 *, f32 *);

u8 *func_150F4E50(u8 *arg0) {
    struct {
        f32 u1C;
        f32 u20;
    } sp;
    u8 *sp18;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    (*(f32 *)((u8 *)arg0 + 0x170)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x170)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) <= 0.0f) {
        return NULL;
    }
    sp18 = temp_v0;
    func_1514373C((*(f32 *)((u8 *)temp_v0 + 0x10)), (*(f32 *)((u8 *)temp_v0 + 0x20)), &sp.u1C, &sp.u20);
    (*(f32 *)((u8 *)sp18 + 0x10)) = (f32) ((*(f32 *)((u8 *)sp18 + 0x10)) + ((*(f32 *)((u8 *)sp18 + 0x14)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 4)) = (f32) ((*(f32 *)((u8 *)sp18 + 4)) + ((*(f32 *)((u8 *)arg0 + 0x44)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 8)) = (f32) ((*(f32 *)((u8 *)sp18 + 8)) + ((*(f32 *)((u8 *)arg0 + 0x48)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) + ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)sp18 + 4)) + (sp.u1C * (*(f32 *)((u8 *)sp18 + 0x18))));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)sp18 + 8)) + sp.u20);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) - (sp.u1C * (*(f32 *)((u8 *)sp18 + 0x1C))));
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x20)) + ((*(f32 *)((u8 *)arg0 + 0x50)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x24)) + ((*(f32 *)((u8 *)arg0 + 0x54)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x28)) + ((*(f32 *)((u8 *)arg0 + 0x58)) * D_800BE9A4));
    return sp18;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4E50.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4FB8.s")

void func_150F527C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *v = arg0 + 0x170;

    if (arg2 == 0x4E) {
        arg0[0x71] = 0;
        v[0x24] |= 5;
    } else if (arg2 == 0x4F) {
        func_1516972C(arg0);
    }
}

void func_150F4D5C(u8 *arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 *unk0;
        f32 unk4;
        s8 unk8;
        u8 unk9;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg1;
    tmp.unk9 = arg2;
    temp_v0 = func_15149130(300, -1, 0x56, -1, 0, 0, 0xC, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F536C.s")
