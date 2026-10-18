#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150F9BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA738.s")

void func_150FA9E8(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_t6;

    temp_t6 = arg2;
    if (temp_t6 == 0x4C) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0U, 0U, 0U, 0xFF);
        return;
    }
    if (temp_t6 == 0x4D) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = 0x1E;
        return;
    }
    if (temp_t6 == 0x4E) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        return;
    }
    if (temp_t6 == 0x4F) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0xFFU, 0xFFU, 0xFFU, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA520.s")

extern u8 D_80088F00;

void func_150FAFC0(u8 arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 *unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    if (D_80088F00 == 0) {
        tmp.unk0 = D_800D34B8 + 0x71C;
        tmp.unk4 = D_800D34B8 + 0x6E8;
        tmp.unk8 = 0.0f;
        temp_v0 = func_15149130(300, -1, 0x57, -1, 0, 0x46, 0xC, arg0, arg1);
        if (temp_v0 != NULL) {
            D_80088F00 = 1;
        }
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB06C.s")

void func_150FB264(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}

void func_150FB2A8(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x30);
    func_151494E0(0, 0x4D);
}

void func_150FB2F8(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x31);
    func_151494E0(0, 0x4C);
}

void func_150FB348(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x53) {
        *(s32 *)(arg0 + 0x58) |= 2;
    } else if (arg2 == 0x54) {
        *(s32 *)(arg0 + 0x58) &= ~2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB398.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB708.s")

s32 func_151584F0(s32, s32, s32, s32, s32);
s32 func_151D76BC(s32, s32, s32, s32, s32);
void func_150FB768(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_151584F0(func_151D76BC(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}

void func_150FB7C0(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((arg2 - arg3) < arg1) {
        *arg0 = (arg2 - arg1) * arg4;
        return;
    }
    *arg0 = 0xFF;
}

s32 func_150FB81C(u8 *arg0) {
    func_150FB7C0(arg0 + 0x43, *(s16 *)(arg0 + 0x16), *(s16 *)(arg0 + 0x120), *(s16 *)(arg0 + 0x64), *(s16 *)(arg0 + 0x66));
    return 1;
}

s32 func_150FB860(u8 *arg0) {
    func_150FB7C0(arg0 + 0x2E, *(s16 *)(arg0 + 0x22), *(s16 *)(arg0 + 0x70), *(s16 *)(arg0 + 0x26), *(s16 *)(arg0 + 0x28));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB8A4.s")
