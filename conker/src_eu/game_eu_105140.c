#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D7930(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D79EC(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D7A9C(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D7B40(s32 arg0) {
    if (arg0 == 0) {
        D_800D9D30 += D_800BE9E4 << 6;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7B6C.s")

#ifdef NON_MATCHING
s32 func_150889D8(struct127 *, s32);
s32 func_15088A68(s32, s32, s32);
s32 func_15088B08(s32, s32);

void func_150D7CA0(struct127 *arg0, s32 arg1) {
    s32 sp48;
    s32 sp40;
    s32 sp38;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_t0;
    struct126 *temp_v0;
    struct126 *temp_v0_5;
    struct126 *temp_v0_6;

    var_t0 = 0;
    temp_v0 = arg0->unk31C;
    if ((temp_v0 == NULL) || ((*(s8 *)((u8 *)temp_v0 + 0x1AE)) > 0)) {
        switch (arg1) {                             /* irregular */
        default:
            var_t0 = 1;
            if (arg1 != 0x33) {
                return;
            }
        case 50:
            temp_v1 = (var_t0 * 0x1E) + 0x1E;
            sp38 = temp_v1;
            temp_v0_2 = func_1506C460(arg0->unk40, 310.0f, 0.0f, 0.0f, (u8) temp_v1, 0xD, 0.0f, 1.0f, 0, 1, var_t0 == 0);
            if (temp_v0_2 != 0) {
                (*(s8 *)((u8 *)temp_v0_2 + 0x124)) = (s8) (D_800C3E78 + 1);
            }
            if ((temp_v0_2 != 0) && (temp_v1 != 0x1E)) {
                (*(s8 *)((u8 *)temp_v0_2 + 0x221)) = -1;
                sp40 = temp_v0_2;
                temp_v0_3 = func_150889D8(arg0, temp_v0_2);
                if (temp_v0_3 != -1) {
                    sp48 = temp_v0_3;
                    temp_v0_4 = func_15088B08(temp_v0_2, temp_v0_2);
                    if (temp_v0_4 != -1) {
                        func_15088A68(sp48, temp_v0_4, sp48);
                    }
                }
            }
            temp_v0_5 = arg0->unk31C;
            if (temp_v0_5 != NULL) {
                (*(s8 *)((u8 *)temp_v0_5 + 0x1AE)) = (s8) ((*(s8 *)((u8 *)temp_v0_5 + 0x1AE)) - 1);
            }
            break;
        case 48:
        case 49:
            if (temp_v0 != NULL) {
                (*(s16 *)((u8 *)temp_v0 + 0x12C)) = 0x78;
                temp_v0_6 = arg0->unk31C;
                (*(s8 *)((u8 *)temp_v0_6 + 0x1AE)) = (s8) ((*(s8 *)((u8 *)temp_v0_6 + 0x1AE)) - 1);
                func_10010154(0x628U, arg0, 0x7FFF, 0x1F4, 0x3E8U);
                return;
            }
            break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7CA0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7E38.s")
