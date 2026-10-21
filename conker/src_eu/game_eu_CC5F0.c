#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509EDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F254.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509F4D0.s")

s32 func_1509F728(s32 arg0, s32 *arg1) {
    if (arg0 != 0) {
        func_100111C8((arg1[0] & 0xFFFF0000) >> 16);
    }
    return 1;
}

void func_1509FB40(s32, s32);
s32 func_1509FC5C();
s32 func_1509F764(s32 arg0, s32 arg1, s32 *arg2) {
    switch (arg1) {
    case 1:
        func_1509FB40(arg2[2] & 0xFFF, 0);
        return 1;
    case 0:
        func_1509FB40(arg2[2] & 0xFFF, 1);
        return 1;
    case 2:
        func_1509FC5C((u32)(arg2[0] & 0xFFFF0000) >> 16, arg2[2] & 0xFFF, arg2[3], arg2[4], arg2[5]);
        return 1;
    }
    return 0;
}

s32 func_1509F81C(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

u32 func_1509F834(s32 arg0, s32 arg1, u32 mask, u32 arg3, s32 arg4, s16 arg5, s32 arg6) {
    struct127 *p;
    u8 n;
    u8 r;

    p = func_1505EEF4(arg4);
    if (arg3 >= 0x8000U) {
        arg3 = 0x7FFF;
    }
    if (p == NULL) {
        return mask;
    }
    if (func_10010894(p) == 0) {
        if (mask == 0) {
            mask = -1U >> (32 - (u8)(arg1 - arg0 + 1));
        }
        n = arg1 - arg0 + 1;
        do {
            r = func_150ADA20() % (u32)n;
        } while (!((1 << r) & mask));
        if (func_10010344((u16)(r + arg0), p, arg3, arg5, arg6) != 0) {
            mask ^= 1 << r;
        }
    }
    return mask;
}

s32 func_1000F568(s32, s32);
s32 func_151149AC(u8);
s32 func_151152A4(s32, s32, s32, s16, s16, s32);

void func_1509F95C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4, s32 arg5) {
    s32 sp24;

    sp24 = func_151149AC(arg3);
    func_151152A4(sp24, func_1000F568(arg0, ((arg1 - arg0) + 1) & 0xFF), arg2, arg4, arg5, 0);
}

void func_1509F9C8(s32 arg0, s32 arg1, u16 arg2, s32 arg3, u32 arg4) {
    u8 *temp_v1;
    s32 temp_t0;
    u8 *sp34;

    temp_v1 = (arg3 * 0x34) + D_800D34B8;
    temp_t0 = (*(s16 *)((u8 *)temp_v1 + 6));
    if (arg4 >= (u32) temp_t0) {
        arg4 = temp_t0 - 1;
    }
    sp34 = temp_v1;
    func_10010F88(func_1000F568(arg0, ((arg1 - arg0) + 1) & 0xFF), arg2, 0, 0U, 0, (s16) (s32) (*(s16 *)temp_v1), (s16) (s32) (*(s16 *)((u8 *)temp_v1 + 2)), (s16) (s32) (*(s16 *)((u8 *)temp_v1 + 4)), (s16) arg4, (s16) (s32) temp_t0);
}

void func_1509FA88(s32 arg0, s32 arg1, s32 arg2) {
    func_10010F30(func_1000F568(arg0, (u8)(arg1 - arg0 + 1)), arg2, 0x40, 0, 0);
}

void func_1509FAD4(u16 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    struct127 *obj = func_1505EEF4(arg2);

    if (obj != NULL) {
        if (arg5 || func_10010894(obj) == 0) {
            func_10010344(arg0, obj, arg1, arg3, (u16) arg4);
        }
    }
}

void func_1509FB40(s32 arg0, s32 arg1) {
    struct127 *temp_v0 = func_1505EEF4(arg0);

    if (temp_v0 != NULL) {
        if (arg1 != 0) {
            func_10010A3C(temp_v0);
        } else {
            func_100109D0(temp_v0);
        }
    }
}

void func_1509FB90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_10010F30(arg0, arg1, arg3, arg2, 0);
}

#ifdef NON_MATCHING
void func_1509FBC8(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4) {
    struct127 *temp_v0;

    temp_v0 = func_1505EEF4(arg1);
    if (temp_v0 == NULL) {
        return;
    }
    func_10010F88(arg0, arg2, 0, 0U, 0, (s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, (s16) arg3, (s16) arg4);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509FBC8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC5F0/func_1509FC5C.s")

s32 func_1509FCE0(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

s32 func_150ADC50();

s32 func_1509FCF8(s32 arg0, s32 arg1, s32 arg2) {
    func_150ADC50();
    return 0;
}
