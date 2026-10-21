#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF950/func_150D2140.s")

#ifdef NON_MATCHING
void func_150D247C(struct102 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_t6;
    u8 *temp_t4;
    u8 *temp_v0_2;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x32) {
        temp_v0 = arg0 + 0x28;
        (*(s32 *)((u8 *)temp_v0 + 0x18)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
        (*(s32 *)((u8 *)temp_v0 + 0x1C)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
        (*(s32 *)((u8 *)temp_v0 + 0x20)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
        (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) (*(f32 *)((u8 *)arg1 + 0xC));
        return;
    }
    if ((temp_t6 == 0x30) || (temp_t6 == 0x31)) {
        temp_v0_2 = &arg0->unk28;
        if ((s32)arg1 == (s32)((*(s32 *)((u8 *)(s32)temp_v0_2 + 0x40)))) {
            if (temp_t6 == 0x30) {
                (*(u8 *)((u8 *)temp_v0_2 + 0x44)) = (u8) ((*(u8 *)((u8 *)temp_v0_2 + 0x44)) | 1);
                return;
            }
            (*(u8 *)((u8 *)temp_v0_2 + 0x44)) = (u8) ((*(u8 *)((u8 *)temp_v0_2 + 0x44)) & 0xFFFE);
        }
    } else {
        temp_t4 = ((u8 *)&D_800A5860);
        if (temp_t6 == 0x4E) {
            (*(s32 *)((u8 *)arg0 + 0x40)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
            (*(s32 *)((u8 *)arg0 + 0x44)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
            (*(s32 *)((u8 *)arg0 + 0x48)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
            return;
        }
        if (temp_t6 == 0x4F) {
            func_1516972C(arg0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF950/func_150D247C.s")
#endif
void func_150D2564(u8 *arg0) {
    u8 *base = arg0 + 0x28;
    u8 i;

    for (i = 0; i < 6; i++) {
        struct102 *p = ((struct102 **)(base + 0x24))[i];

        if (p != NULL) {
            func_1516972C(p);
        }
    }
}

void func_150D25C0(struct260 *arg0) {
    func_150D2564(arg0);
    func_15149368(arg0);
}

void func_150D25EC(struct260 *arg0) {
    func_150D2564(arg0);
    func_1514933C(arg0);
}
