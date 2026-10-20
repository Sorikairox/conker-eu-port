#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_1507C8E0(struct127 *arg0, s32 arg1) {
    arg0->unk31C->unk120 = (u8)2;
    arg0->unk31C->unk124 = arg1;
}

// "goto" hell
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507C8FC.s")

void func_1507CD0C(struct127 *arg0) {
    s32 temp_lo = ((s32)arg0 - (s32)&D_800CC2D0) / (s32)sizeof(struct127);

    arg0->unk31C->unk120 = 3;

    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
void func_1507D158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 tmp = D_800CC82F[arg0 * 812];
    func_1509BFB0(3, tmp | 0x2000, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D1D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D4F8.s")
// NON-MATCHING: pretty far away!
// void func_1507D4F8(s16 arg0) { // struct126 *
//     // ?32 sp24;
//     struct127 *temp_a0;
//
//     if ((D_8008FDBC & 1) == 0) {
//         func_15085710(arg0, 4, 1);
//     }
//     // sp24 = (?32) arg0;
//     if (func_150859AC(arg0, 3) != 0) {
//         func_15085710(arg0, 5, D_8008726C); //temp_ret =
//         temp_a0 = &D_800CC2D0[arg0];
//         temp_a0->unkB2 = (u16)0;
//         if (D_800BE616 == 0) {
//             D_800D18A8 = (u8)1;
//             if (((D_800D2E4C->unk19 & 4) != 0) || (D_8008FDA8 < 0)) {
//                 func_1501C730(2, D_800BE3DF, D_800BE3E0, 0, 0);
//                 return;
//             }
//             func_1501C730(1, 0x22, 0, 0, 0);
//             return;
//         }
//         if (D_800E0C20 != 0) {
//             temp_a0->unk31C->unk120 = (u8)0xA;
//             return; // temp_ret;
//         }
//         func_1507D1D8(temp_a0);
//         return;
//     }
//     if (D_800BE616 == 0) {
//         D_800D2E43 = (u8)1;
//         func_1509C3A0();
//         D_800D18A8 = (u8)1;
//         func_15085710(arg0, 5, D_8008726C);
//         func_15085710(arg0, 2, D_80087260);
//         func_1501C730(1, 0x18, 0, 0, 0);
//     } else {
//         D_800D18A0 = (u16) (D_800D18A0 | (1 << (s32) arg0));
//     }
//     // temp_a0 = &D_800CC2D0[arg0];
//     if (temp_a0->unk31C->unk84 == 0) {
//         D_8008FD94 -= 1; //(s8) (D_8008FD94 - 1);
//     }
//     temp_a0->unk31C->unk120 = (u8)0xA;
//     D_800BE618 -= 1; //(s8) (D_800BE618 - 1);
//     //return temp_a0_2->unk31C;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")

void func_1507DB44(s32 arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

void func_1507DB64(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")

void func_1507DE4C(struct127 *arg0) {

    if (arg0->interaction_state == 1) {
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        arg0->unk9C |= 0xF000;
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        return;
    }

    switch(arg0->id) {
        case 0x9F:
        case 0xa0:
            arg0->unk9C |= 0xF000;
            break;
        case 0x5A:
        case 0x74:
        case 0x7A:
            arg0->unk9C |= 0xFF8;
            break;
    }
}


void func_1507DF10(u8 *arg0, s32 arg1) {
    switch (arg1) {
    case 9:
        *(s32 *)(arg0 + 0x94) |= 0x20;
        *(s32 *)(arg0 + 0x9C) |= 0x78;
        *(s32 *)(arg0 + 0x2E4) = 1;
        break;
    case 8:
        *(s32 *)(arg0 + 0x94) |= 0x40;
        *(s32 *)(arg0 + 0x94) &= ~0x200;
        *(s32 *)(arg0 + 0x9C) |= 0xF00;
        *(s32 *)(arg0 + 0x2E4) = 2;
        break;
    case 6:
    case 7:
        *(s32 *)(arg0 + 0x94) |= 0xE;
        *(s32 *)(arg0 + 0x94) &= ~0x410;
        *(s32 *)(arg0 + 0x9C) |= 0xEE0000;
        *(s32 *)(arg0 + 0x2E4) = 4;
        break;
    case 4:
    case 5:
        *(s32 *)(arg0 + 0x94) |= 0x80;
        *(s32 *)(arg0 + 0x94) &= ~0x500;
        *(s32 *)(arg0 + 0x2E4) = 8;
        break;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DFE4.s")
s32 func_1507E114(s32 arg0) {
    s32 sp5C;
    s32 sp54[2];
    s32 sp48[3];
    s32 sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;

    if (D_800D18A8 == 0) {
        return 0;
    }
    if ((s32)D_800BE9F4 == 0x22 || (s32)D_800BE9F4 == 0x18) {
        return 0;
    }
    D_800BE9F4 = (u16 *)(s32)(s8)D_800BE3DF;
    func_150851E0(0, D_800BE800, 1, sp54, sp48, &sp43, &sp42, &sp44, &sp3C, 1, &sp5C);
    return sp5C + 1;
}
void func_1507E1D0(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 *var_a2;
    f32 sp28[3];
    f32 sp1C[3];
    if ((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) {
        s32 temp_v0;
        sp28[0] = 0.0f;
        sp28[1] = (*(f32 *)((u8 *)arg0 + 0x150)) * 30.0f;
        sp28[2] = 0.0f;
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0));
        var_a2 = (*(u8 **)((u8 *)arg0 + 0x1D4));
        if (temp_v0 == 1) {
            var_a2 += 0x300;
        } else if (temp_v0 == 0x1E) {
            var_a2 += 0xC0;
        }
        func_15143134(sp28, sp1C, var_a2);
        *arg1 = sp1C[0];
        *arg2 = sp1C[1];
        *arg3 = sp1C[2];
    } else {
    *arg1 = (*(f32 *)((u8 *)arg0 + 0x14));
    *arg2 = (*(f32 *)((u8 *)arg0 + 0x18));
    *arg3 = (*(f32 *)((u8 *)arg0 + 0x1C));
    }
}
