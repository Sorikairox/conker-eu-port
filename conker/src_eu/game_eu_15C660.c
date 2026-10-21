#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15C660/func_1512EE50.s")

#ifdef NON_MATCHING
void func_15130370(struct108 *arg0, s32 arg1) {
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t9;

    switch (arg1) {
    case 1:
        func_15123934(arg0, arg0->unk2C, 0, 0, 7);
        return;
    case 2:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 &= ~8;
        return;
    case 3:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x10000000;
        return;
    case 8:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x80;
        return;
    case 9:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        temp_t9 = arg0->unk84 & ~8;
        arg0->unk84 = temp_t9;
        arg0->unk84 = temp_t9 | 0x80;
        return;
    case 11:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x4000;
        return;
    case 12:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x8000;
        return;
    case 13:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x20000;
        return;
    case 16:
        func_15123934(arg0, 8, 0, arg0->unk134, 7);
        return;
    case 14:
        func_15123934(arg0, 2, 0, arg0->unk134, 7);
        return;
    case 18:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x100000;
        return;
    case 19:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x400000;
        return;
    case 21:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk190 = 0.0f;
        return;
    case 22:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x800;
        arg0->unk190 = -30.0f;
        return;
    case 25:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x40;
        return;
    case 23:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x01000000;
        return;
    case 24:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x80000000;
        return;
    case 26:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x10;
        return;
    case 27:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x20;
        return;
    case 28:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        temp_t0 = arg0->unk84 | 0x10;
        arg0->unk84 = temp_t0;
        arg0->unk84 = temp_t0 & ~8;
        return;
    case 29:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        temp_t5 = arg0->unk84 | 0x01000010;
        arg0->unk84 = temp_t5;
        arg0->unk84 = temp_t5 & ~8;
        return;
    case 30:
        func_15128774(arg0, arg0->unk3D0);
        /* fallthrough */
    default:
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15C660/func_15130370.s")
#endif