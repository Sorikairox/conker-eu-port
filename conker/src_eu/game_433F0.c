#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s8 func_151E6758(s16);
extern s32 D_800BEE08;

/* was func_15015F40 */
void mp_set_mode_for_level(s16 arg0, s32 arg1) {
    switch (arg1) {
    case 0x1A:
    case 0x24:
    case 0x2B:
    case 0x2D:
    case 0x30:
    case 0x33:
    case 0x34:
    case 0x3F:
        D_800BE616 = 1;
        D_800BEE08 = func_151E6758(arg0) - 1;
        return;
    default:
        D_800BE616 = 0;
        D_800BEE08 = arg0 - 1;
        return;
    }
}

#ifdef NON_MATCHING
extern s32 D_800BEA58;
extern s32 D_800BEA5C;
extern s32 D_800BEA70;
extern s32 D_800BEA74;
extern s32 D_800BEA78;
extern s32 D_800BEA7C;
extern s32 D_800BEA80;
extern s32 D_800BEA84;
extern s32 D_800BEA88;

/* was func_15015FBC */
void screen_setup_viewports(s32 arg0, s32 arg1) {
    s32 *var_a1;
    s32 *var_v1;
    s16 temp_lo;
    s16 temp_lo_2;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;

    D_800BEA58 = arg0;
    var_a1 = &D_800BEA74;
    var_v1 = &D_800BEA5C;
    D_800BEA70 = arg1;
    do {
        (*(s32 *)((u8 *)var_v1 + 0)) = arg0;
        (*(s32 *)((u8 *)var_a1 + 0)) = arg1;
        if ((u32) var_a1 < (u32) &D_800BEA80) {
            if ((u32) var_a1 >= (u32) &D_800BEA78) {
                (*(s32 *)((u8 *)var_v1 + 0)) = (s32) (arg0 >> 1);
            }
            if ((u32) var_a1 >= (u32) &D_800BEA74) {
                (*(s32 *)((u8 *)var_a1 + 0)) = (s32) ((s32) (*(s32 *)((u8 *)var_a1 + 0)) >> 1);
            }
        }
        (*(s32 *)((u8 *)var_v1 + 4)) = arg0;
        (*(s32 *)((u8 *)var_a1 + 4)) = arg1;
        if ((u32) var_a1 < (u32) &D_800BEA7C) {
            if ((u32) var_a1 >= (u32) &D_800BEA74) {
                (*(s32 *)((u8 *)var_v1 + 4)) = (s32) (arg0 >> 1);
            }
            if ((u32) var_a1 >= (u32) &D_800BEA70) {
                (*(s32 *)((u8 *)var_a1 + 4)) = (s32) ((s32) (*(s32 *)((u8 *)var_a1 + 4)) >> 1);
            }
        }
        var_a1 = (s32 *)((u8 *)var_a1 + (8));
        var_v1 = (s32 *)((u8 *)var_v1 + (8));
    } while (var_a1 != &D_800BEA84);
    temp_a3 = arg1 >> 2;
    temp_lo = temp_a3 * 3;
    temp_v1 = arg0 >> 2;
    temp_v0 = arg0 >> 1;
    temp_a1 = arg1 >> 1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 2)) = (s16) temp_a1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 4)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 6)) = (s16) temp_a1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 8)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0xA)) = (s16) temp_a1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0xC)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0xE)) = (s16) temp_a1;
    temp_lo_2 = temp_v1 * 3;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x10)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x12)) = (s16) temp_a1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x14)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x16)) = (s16) temp_a3;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x18)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x1A)) = temp_lo;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x1C)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x1E)) = (s16) temp_a1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x20)) = 0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x22)) = 0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x24)) = 0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x26)) = 0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x28)) = (s16) temp_v1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x2A)) = (s16) temp_a3;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x2C)) = temp_lo_2;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x2E)) = (s16) temp_a3;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x30)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x32)) = temp_lo;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x34)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x36)) = (s16) temp_a1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x38)) = 0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x3A)) = 0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x3C)) = (s16) temp_v1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x3E)) = (s16) temp_a3;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x40)) = temp_lo_2;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x42)) = (s16) temp_a3;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x44)) = (s16) temp_v1;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x46)) = temp_lo;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x48)) = temp_lo_2;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x4A)) = temp_lo;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x4C)) = (s16) temp_v0;
    (*(s16 *)((u8 *)(&D_800BEA88) + 0x4E)) = (s16) temp_a1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_433F0/screen_setup_viewports.s")
#endif
// s32 screen_setup_viewports(s32 arg0, s32 arg1) {
//     s16 temp_lo;
//     s16 temp_lo_2;
//     s32 temp_a1_2;
//     s32 temp_a3;
//     s32 temp_v0;
//     s32 temp_v1;
//     u32 temp_a1;
//     void *phi_v1;
//     u32 phi_a1;
//
//     D_800BE638 = arg0;
//     D_800BE650 = arg1;
//     phi_v1 = D_800BE63C;
//     phi_a1 = D_800BE654;
// loop_1:
//     phi_v1->unk0 = arg0;
//     phi_a1->unk0 = arg1;
//     if (phi_a1 < D_800BE660) {
//         if (phi_a1 >= D_800BE658) {
//             phi_v1->unk0 = (s32) (arg0 >> 1);
//         }
//         if (phi_a1 >= D_800BE654) {
//             phi_a1->unk0 = (s32) ((s32) phi_a1->unk0 >> 1);
//         }
//     }
//     phi_v1->unk4 = arg0;
//     phi_a1->unk4 = arg1;
//     if (phi_a1 < D_800BE65C) {
//         if (phi_a1 >= D_800BE654) {
//             phi_v1->unk4 = (s32) (arg0 >> 1);
//         }
//         if (phi_a1 >= D_800BE650) {
//             phi_a1->unk4 = (s32) ((s32) phi_a1->unk4 >> 1);
//         }
//     }
//     temp_a1 = phi_a1 + 8;
//     phi_v1 = phi_v1 + 8;
//     phi_a1 = temp_a1;
//     if (temp_a1 != D_800BE664) {
//         goto loop_1;
//     }
//     temp_a3 = arg1 >> 2;
//     temp_lo = temp_a3 * 3;
//     temp_v1 = arg0 >> 2;
//     temp_v0 = arg0 >> 1;
//     temp_a1_2 = arg1 >> 1;
//     D_800BE668->unk0 = (s16) temp_v0;
//     D_800BE668->unk2 = (s16) temp_a1_2;
//     D_800BE668->unk4 = (s16) temp_v0;
//     D_800BE668->unk6 = (s16) temp_a1_2;
//     D_800BE668->unk8 = (s16) temp_v0;
//     D_800BE668->unkA = (s16) temp_a1_2;
//     D_800BE668->unkC = (s16) temp_v0;
//     D_800BE668->unkE = (s16) temp_a1_2;
//     temp_lo_2 = temp_v1 * 3;
//     D_800BE668->unk10 = (s16) temp_v0;
//     D_800BE668->unk12 = (s16) temp_a1_2;
//     D_800BE668->unk14 = (s16) temp_v0;
//     D_800BE668->unk16 = (s16) temp_a3;
//     D_800BE668->unk18 = (s16) temp_v0;
//     D_800BE668->unk1A = temp_lo;
//     D_800BE668->unk1C = (s16) temp_v0;
//     D_800BE668->unk1E = (s16) temp_a1_2;
//     D_800BE668->unk20 = (u16)0;
//     D_800BE668->unk22 = (u16)0;
//     D_800BE668->unk24 = (u16)0;
//     D_800BE668->unk26 = (u16)0;
//     D_800BE668->unk28 = (s16) temp_v1;
//     D_800BE668->unk2A = (s16) temp_a3;
//     D_800BE668->unk2C = temp_lo_2;
//     D_800BE668->unk2E = (s16) temp_a3;
//     D_800BE668->unk30 = (s16) temp_v0;
//     D_800BE668->unk32 = temp_lo;
//     D_800BE668->unk34 = (s16) temp_v0;
//     D_800BE668->unk36 = (s16) temp_a1_2;
//     D_800BE668->unk38 = (u16)0;
//     D_800BE668->unk3A = (u16)0;
//     D_800BE668->unk3C = (s16) temp_v1;
//     D_800BE668->unk3E = (s16) temp_a3;
//     D_800BE668->unk40 = temp_lo_2;
//     D_800BE668->unk42 = (s16) temp_a3;
//     D_800BE668->unk44 = (s16) temp_v1;
//     D_800BE668->unk46 = temp_lo;
//     D_800BE668->unk48 = temp_lo_2;
//     D_800BE668->unk4A = temp_lo;
//     D_800BE668->unk4C = (s16) temp_v0;
//     D_800BE668->unk4E = (s16) temp_a1_2;
//     return temp_v0;
// }
