#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_15022A8C(struct127 *);
extern u8 D_800C3A78;
s32 func_1505E0C4(struct127 *, s32, u8 *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
#endif


void func_15058F24(struct127 *arg0, f32, f32);
void func_1505F188(struct127 *arg0);
u8   func_150599C8(struct127 *arg0, u8 arg1, u16 arg2);
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
f32  func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);

u8  func_1505B9C4(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

#ifdef NON_MATCHING
extern u8 *D_800D1CD0;

void func_15055E50(struct127 *arg0, s32 arg1) {
    f32 sp40;
    f32 sp3C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f2;
    f32 var_f30;
    s16 temp_a1;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_v0;
    s32 var_v1;
    u16 temp_a1_2;
    u16 temp_t1;
    u16 temp_t2;
    u8 *temp_t0;
    u8 *var_a2;
    u8 *var_t0;

    var_v0 = 1;
    var_v1 = 0;
    if (arg0->id == 0x3A) {
        if (arg0->x_position > 1200.0f) {
            arg0->x_position = 1200.0f;
        }
        if (arg0->x_position < -1200.0f) {
            arg0->x_position = -1200.0f;
        }
        if (arg0->z_position > 1200.0f) {
            arg0->z_position = 1200.0f;
        }
        if (arg0->z_position < -1200.0f) {
            arg0->z_position = -1200.0f;
        }
    }
    if ((arg1 != 0) && (D_800D1CD0 != NULL) && ((s32) arg0->unk13D < 0x64)) {
        var_f30 = 1e9f;
        var_a3 = 0;
        if (arg1 != (*(u16 *)((u8 *)D_800D1CD0 + 6))) {
            var_t0 = D_800D1CD0;
loop_14:
            if ((*(s32 *)((u8 *)var_t0 + 0)) != 0) {
                temp_t2 = (*(u16 *)((u8 *)var_t0 + 0xE));
                var_a3 += 1;
                var_t0 += 8;
                if (arg1 == temp_t2) {
                    goto block_16;
                }
                goto loop_14;
            }
        } else {
block_16:
            temp_t0 = D_800D1CD0 + (var_a3 * 8);
            temp_t1 = (*(u16 *)((u8 *)temp_t0 + 4));
            var_a3_2 = 0;
            var_a2 = (*(u8 **)((u8 *)temp_t0 + 0));
            if ((s32) temp_t1 > 0) {
                do {
                    var_a3_2 += 1;
                    if ((var_v0 != 0) || ((*(u16 *)((u8 *)var_a2 + 8)) & 0x8000)) {
                        temp_a1 = (*(s16 *)((u8 *)var_a2 + 4));
                        temp_f0 = arg0->y_position;
                        if (((f32) temp_a1 <= temp_f0) && (temp_f0 <= (f32) ((*(s16 *)((u8 *)var_a2 + 6)) + temp_a1))) {
                            temp_a1_2 = (*(u16 *)((u8 *)var_a2 + 8));
                            temp_f24 = (f32) (*(s16 *)((u8 *)var_a2 + 0));
                            temp_f20 = (f32) (*(s16 *)((u8 *)var_a2 + 2));
                            temp_f2 = (f32) (temp_a1_2 & 0x7FFF);
                            temp_f16 = arg0->x_position - temp_f24;
                            temp_f18 = arg0->z_position - temp_f20;
                            if (temp_a1_2 & 0x8000) {
                                temp_f12 = (temp_f16 * temp_f16) + (temp_f18 * temp_f18) + 0.1f;
                                if (temp_f12 < (temp_f2 * temp_f2)) {
                                    temp_f14 = 1.0f / sqrtf(temp_f12);
                                    arg0->x_position = temp_f24 + (temp_f16 * temp_f14 * temp_f2);
                                    arg0->unkF4 |= 0x2000;
                                    arg0->z_position = (f32) (*(s16 *)((u8 *)var_a2 + 2)) + (temp_f18 * temp_f14 * temp_f2);
                                }
                            } else {
                                var_v1 = 1;
                                temp_f12_2 = (temp_f16 * temp_f16) + (temp_f18 * temp_f18) + 0.1f;
                                if (temp_f12_2 < (temp_f2 * temp_f2)) {
                                    var_v0 = 0;
                                } else {
                                    temp_f22 = sqrtf(temp_f12_2);
                                    if ((temp_f22 - temp_f2) < var_f30) {
                                        temp_f14_2 = 1.0f / temp_f22;
                                        var_f30 = temp_f22 - temp_f2;
                                        sp40 = temp_f24 + (temp_f16 * temp_f14_2 * temp_f2);
                                        sp3C = temp_f20 + (temp_f18 * temp_f14_2 * temp_f2);
                                    }
                                }
                            }
                        }
                    }
                    var_a2 += 0xA;
                } while (var_a3_2 != temp_t1);
            }
            if ((var_v0 != 0) && (var_v1 != 0)) {
                arg0->x_position = sp40;
                arg0->unkF4 |= 0x2000;
                arg0->z_position = sp3C;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15055E50.s")
#endif
void func_15056150(struct127 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    s16 *temp_v1;

    if (arg0->unk2E8 != 0) {
        temp_v1 = D_800D2104[arg0->unk13F];
        temp_f2 = temp_v1[4];
        temp_f12 = temp_v1[6];
        temp_f14 = temp_v1[5];
        temp_f16 = arg0->unk2E8;
        temp_f16 = temp_f16 * 8.0f;
        temp_f18 = arg0->x_position - temp_f2;
        temp_f20 = arg0->z_position - temp_f12;
        temp_f22 = arg0->y_position - temp_f14;
        temp_f0 = sqrtf((temp_f18 * temp_f18) + (temp_f20 * temp_f20) + (temp_f22 * temp_f22) + 0.1f);
        temp_f18 *= 1.0f / temp_f0;
        temp_f20 *= 1.0f / temp_f0;
        temp_f22 *= 1.0f / temp_f0;
        if (temp_f16 < temp_f0) {
            arg0->x_position = temp_f18 * temp_f16 + temp_f2;
            arg0->z_position = temp_f20 * temp_f16 + temp_f12;
            arg0->y_position = temp_f22 * temp_f16 + temp_f14;
        }
    }
}

void func_15056258(struct127 *arg0) {
    f32 temp_f2;
    f32 temp_f4;
    f32 phi_f12;

    temp_f4 = arg0->unk11C;
    temp_f2 = arg0->unk118 - arg0->unk11C;
    arg0->unk11C = arg0->unk118;
    phi_f12 = 2.0f * (arg0->y_position - ((arg0->unk118 - 60.0f) - 170.0f));
    if (!(phi_f12 < 0.0f)) {
        if (!(fabsf(temp_f2) > 30.0f)) {
            if (phi_f12 > 300.0f) {
                phi_f12 = 300.0f;
            }
            arg0->y_position += (phi_f12 * temp_f2 * 0.002997f);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150562FC.s")
// NON-MATCHING: 10% of the way there...
// void func_150562FC(struct127 *arg0) {
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     u8 sp63;
//     s32 sp54;
//     f32 sp4C;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f14;
//
//     s32 *temp_a3;
//     // s32 temp_t1;
//     s32 temp_t1_2;
//     s32 temp_t2;
//     s32 temp_t9;
//     s32 temp_v0_6;
//     struct255 *temp_v1_2;
//     u16 temp_v0_2;
//     u16 temp_v0_3;
//     u16 temp_v0_4;
//     u16 temp_v0_5;
//     u16 temp_v0_7;
//     u16 temp_v0_8;
//     u16 temp_v1;
//     u8 temp_v0;
//     struct127 *temp_t0;
//     struct127 *temp_t0_2;
//     u8 *temp_v0_11;
//     s32 phi_a2;
//     s32 phi_t1;
//     s32 phi_t1_2;
//     s32 phi_t1_3;
//     s32 phi_a2_2;
//     f32 phi_f18;
//     s32 phi_t1_4;
//     f32 phi_f0;
//     s32 phi_t1_5;
//     s32 phi_t2;
//
//     sp63 = arg0->unk13D - 0x64;
//     sp54 = 0;
//     sp4C = 5.0f;
//     arg0->immune = (u8)0x1E;
//     temp_t0 = &D_800CC2D0[sp63];
//     arg0->unk180 = (f32) temp_t0->unk180;
//     arg0->unk1CC = (f32) arg0->y_position;
//     arg0->gravity = 4.5f;
//     arg0->y_velocity = 0.0f;
//     if ((s32) arg0->unk21C < 0x1E) {
//         arg0->unk21C += D_800BE9A0;
//     }
//     temp_v0 = arg0->id;
//     if (temp_v0 == 0x57) {
//         arg0->unk5C = 9;
//         if ((s32) arg0->unk21C >= 0xA) {
//             temp_v0_2 = temp_t0->unk84.uh;
//             sp54 = 1;
//             phi_a2 = 0xD;
//             if (temp_v0_2 == 0x114) {
//                 phi_a2 = 0x24;
//             }
//             phi_t1 = 0;
//             if (temp_v0_2 == 0x116) {
//                 phi_t1 = 1;
//             }
//             if (temp_v0_2 == 0x117) {
//                 phi_t1 = 2;
//             }
//             func_150649A0(sp63, D_800C3E78, phi_a2);
//             phi_t1_3 = phi_t1;
//             phi_a2_2 = phi_a2;
//         } else if (temp_v0 == 0x8C) {
//             arg0->unk5C = 4;
//             if ((s32) arg0->unk21C >= 0xA) {
//                 temp_v0_2 = temp_t0->unk84.uh;
//                 sp54 = 1;
//                 phi_t1_2 = 0;
//                 if (temp_v0_2 == 0x1A6) {
//                     phi_t1_2 = 1;
//                 }
//                 if (temp_v0_2 == 0x1A7) {
//                     phi_t1_2 = 2;
//                 }
//                 func_150649A0(sp63, D_800C3E78, 0xD);
//                 phi_t1_3 = phi_t1_2;
//                 phi_a2_2 = 0xD;
//             }
//         } else {
//             if ((temp_v0 == 0xA8) || (temp_v0 == 0xA9)) {
//                 arg0->unk5C = 9;
//                 temp_v0_2 = temp_t0->unk84.uh;
//                 sp54 = 1;
//                 phi_t1_3 = 0;
//                 if (temp_v0_2 == 0x1B0) {
//                     phi_t1_3 = 1;
//                 }
//                 phi_a2_2 = 0xD;
//                 if (temp_v0_2 == 0x1B1) {
//                     phi_t1_3 = 2;
//                     phi_a2_2 = 0xD;
//                 }
//             } else {
//                 phi_t1_3 = 0;
//                 phi_a2_2 = 0xD;
//                 if (temp_v0 == 0x5E) {
//                     arg0->unk5C = 9;
//                     temp_v0_2 = temp_t0->unk84.uh;
//                     sp54 = 1;
//                     sp4C = 16.0f;
//                     phi_t1_3 = 0;
//                     if (temp_v0_2 == 0x286) {
//                         phi_t1_3 = 2;
//                     }
//                     phi_a2_2 = 0xD;
//                     if (temp_v0_2 == 0x27E) {
//                         phi_t1_3 = 1;
//                         phi_a2_2 = 0xD;
//                     }
//                 }
//             }
//         }
//         temp_v0_6 = func_1505E7CC(phi_a2_2, arg0); //, phi_a2_2);
//         temp_t0_2 = &D_800CC2D0[sp63];
//         phi_t1_4 = phi_t1_3;
//         temp_t2 = temp_v0_6;
//         temp_a3 = D_800D1588[arg0->id] - 8;
//         if (temp_t0_2->interaction_state == 1) {
//             if (temp_t0_2->in_water != 0) {
//                 temp_t9 = temp_v0_6 * 3;
//                 arg0->unk5C = 4;
//                 sp54 = 1;
//                 if (((temp_a3 + (temp_t9 * 8)) + 14) != 0) { // unkE
//                     phi_t1_4 = 1;
//                 }
//             }
//         }
//         if ((s32) arg0->unk21C < 0x14) {
//             phi_f18 = (f32) (u32) arg0->unk21C / 50.0f;
//             if (D_800BE9B4 != 0) {
//                 phi_f18 = 1.0f;
//             }
//         } else {
//             phi_f18 = D_80099448;
//         }
//
//         sp70 = (f32) arg0->unk10F;
//
//         func_150599C8(arg0, 0x10, (temp_t0_2->unk7A + (arg0->unk13E << 8)) & 0xFFFF); //, temp_a3);
//         temp_t1_2 = phi_t1_4;
//         temp_v1_2 = temp_t0_2->unk1D4;
//         if (temp_v1_2 != 0) {
//             temp_f0 = (f32) ((s32) arg0->unk10C / 0x64);
//             if (temp_t0_2->interaction_state != 0x15) {
//                 temp_v0_8 = arg0->unk21C;
//                 if ((s32) temp_v0_8 >= 7) {
//                     arg0->y_position = (f32) temp_v1_2->unk240->unk1A;
//                     if ((s32) temp_v0_8 < 0xE) {
//                         // temp_f6 = (f32) temp_v0_8;
//                         temp_f0 = (temp_v0_8 / 14.0f) * temp_f0;
//                     }
//                     arg0->y_position = (f32) (arg0->y_position + temp_f0);
//                 }
//                 if (arg0->id == 0xE) {
//                     arg0->unkC4 = 0.0f;
//                 } else if (arg0->id == 0x13) {
//                     sp70 = 204.0f;
//                     arg0->unkC4 = 0.0f;
//                 }
//             }
//         }
//         phi_t1_5 = phi_t1_4;
//         phi_t2 = temp_t2;
//         if (temp_t0_2->interaction_state == 0x15) {
//             phi_t2 = func_1505E7CC(0x39, arg0);
//             arg0->unk7A = (u16) temp_t0_2->unk7A;
//             arg0->y_position = (f32) (temp_t0_2->y_position - 10.0f);
//             if ((arg0->unk28 > 100.0f) && ((s32) arg0->unk21C >= 0x15)) {
//                 phi_t1_5 = 1;
//             } else {
//                 sp4C = 0.0f;
//                 phi_t1_5 = phi_t1_4;
//             }
//             sp70 = 0.0f;
//             temp_f0 = arg0->unkC4;
//             arg0->xz_velocity = 0.0f;
//             arg0->unkC4 = (f32) (temp_f0 + ((temp_t0_2->unkC4 - temp_f0) * D_8009944C));
//         }
//         func_1505A184(D_800CC2D0[sp63].unk7A,  sp70, 0, &sp70, &sp6C, &sp68);
//         temp_t0_2 = &D_800CC2D0[sp63];
//         temp_f12 = temp_t0_2->x_position + sp70;
//
//         temp_f14 = temp_t0_2->z_position + sp6C;
//         arg0->x_position = (f32) (arg0->x_position + ((temp_f12 - arg0->x_position) * phi_f18));
//         arg0->z_position = (f32) (arg0->z_position + ((temp_f14 - arg0->z_position) * phi_f18));
//         temp_v0_11 = temp_a3 + (phi_t2 * 0x18) + (phi_t1_5 * 4);
//         func_1505E650(arg0, temp_v0_11[0xA],  temp_v0_11[0xC] / 100.0f, sp4C, 0.0f, 0.0f, 0);
//         if (sp54 != 0) {
//             arg0->unk65 = (s8) (sp63 + 1);
//             arg0->unk101 = (u8) (arg0->unk101 | 4);
//         } else {
//             arg0->unk65 = (u8)0;
//         }
//     }
// }

s32 func_1505693C(struct127 *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    u16 *temp_v0 = (u16*)D_800D2104[(u16)arg0->unk13F];

    if (temp_v0[3] == 0) {
        return 1;
    }

    temp_f0 = temp_v0[3] * 8;
    temp_f0 = temp_f0 * temp_f0;
    temp_f2 = (s16)temp_v0[0] - D_800CC2D0[arg1].x_position;
    temp_f12 = (s16)temp_v0[2] - D_800CC2D0[arg1].z_position;

    if ((temp_f2 * temp_f2) + (temp_f12 * temp_f12) < temp_f0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056B08.s")
#ifdef NON_MATCHING
extern f32 D_80099828;
extern f32 D_8009982C;
extern f32 D_80099830;
extern f32 D_80099838;
extern f32 D_8009983C;
extern s32 D_80041C50;
extern u8 D_80041D40;

void func_1505841C(struct127 *arg0, f32 arg1) {
    f32 temp_f12;
    f32 var_f0;
    f32 var_f0_2;
    struct197 *temp_v0_2;
    u8 temp_v0;

    temp_v0 = arg0->unk246;
    var_f0 = (f32) (((temp_v0 & 0x1F) << 8) + arg0->unk249) * D_80099828;
    if (!(temp_v0 & 0x80)) {
        temp_f12 = arg0->xz_velocity;
        if ((temp_f12 <= 1.0f) || ((arg0->unk22C & 0x10) && (arg0->unk28 == 0.0f))) {
            var_f0 = arg1;
        } else {
            var_f0 = ((temp_f12 * (0.5f / arg0->xz_scale)) / (var_f0 * 10.0f)) + D_8009982C;
            if (!(temp_v0 & 0x20)) {
                var_f0 += D_80099830;
            }
        }
    }
    if (arg0->unk223 == 0xD) {
        var_f0 = (f32) (arg0->unk250 & 0x7F) * D_8009982C;
    }
    if (temp_v0 == 0xFF) {
        var_f0 = 0.0f;
    }
    func_1505E650(arg0, (u16) arg0->unk244, var_f0, (f32) arg0->unk1D0, 0.0f, 0.0f, 0);
    if (arg0->unk246 == 0xFF) {
        var_f0_2 = ((f32) *(&D_80041C50 + (D_80041D40 << 6)) - D_80099838) * D_8009983C;
        if (var_f0_2 < 0.0f) {
            var_f0_2 = 0.0f;
        }
        temp_v0_2 = arg0->unk2D0;
        temp_v0_2->unk8 = ((temp_v0_2->unk18 - 1.0f) * (32768.0f - var_f0_2)) / 32768.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505841C.s")
#endif
// NON-MATCHING: JUSTREG
// void func_1505841C(struct127 *arg0, f32 arg1) {
//     struct197 *temp_v0_2;
//     f32 temp_f0;
//     f32 temp_f1;
//     s32 idx;
//
//     temp_f0 = (((arg0->unk246 & 0x1F) << 8) + arg0->unk249) * D_80099468;
//     if ((arg0->unk246 & 0x80) == 0) {
//         if ((arg0->xz_velocity <= 1.0f) || (((arg0->unk22C & 0x10) != 0) && (arg0->unk28 == 0.0f))) {
//             temp_f0 = arg1;
//         } else {
//             // regalloc off here
//             temp_f1 = (arg0->xz_velocity * (0.5f / arg0->xz_scale));
//             temp_f0 = temp_f1 / (temp_f0 * 10.0f);
//             temp_f0 += D_8009946C;
//
//             if ((arg0->unk246 & 0x20) == 0) {
//                 temp_f0 += D_80099470;
//             }
//         }
//     }
//     if (arg0->unk223 == 0xD) {
//         temp_f0 = (arg0->unk250 & 0x7F) * D_80099474;
//     }
//     if (arg0->unk246 == 0xFF) {
//         temp_f0 = 0.0f;
//     }
//     func_1505E650(arg0, arg0->unk244, temp_f0, arg0->unk1D0, 0.0f, 0.0f, 0);
//
//     if (arg0->unk246 == 0xFF) {
//         // regalloc off here
//         idx = D_800419A0 << 4;
//         temp_f0 = D_800418B0[idx];
//         if (temp_f0 >= 0.0f) {
//             temp_v0_2 = arg0->unk2D0;
//             temp_v0_2->unk8 = (f32) ((temp_v0_2->unk18 * (32768.0f - temp_f0)) / 32768.0f);
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150585F0.s")
// NON-MATCHING: 80% there
// void func_150585F0(struct127 *arg0) {
//     f32 temp_f0;
//     u16 phi_a2;
//
//     func_1505A3A8(arg0->unk109 * D_80099478, arg0, 1.0f, arg0->unk109 * D_80099478, 0);
//     if (arg0->unk1CC < D_8009947C) {
//         arg0->unk1CC = arg0->y_position;
//     }
//     if ((arg0->in_water != 0) && ((s32) arg0->in_water < 0xA)) {
//         arg0->gravity = 0.0f;
//         if (arg0->y_velocity < 60.0f) {
//             arg0->y_velocity *= D_80099480;
//         }
//         if (((arg0->unk118 - 60.0f) + 40.0f) < arg0->y_position) {
//             arg0->unk81 = (u8)0;
//             arg0->unk83 = (u8)0;
//             arg0->in_water = (u8)0U;
//             arg0->unkB8 = 0.0f;
//             arg0->gravity = 4.0f;
//         }
//     }
//     if ((D_800BE616 == 0) || (arg0->interaction_state != 1)) {
//         arg0->unk21C = (u16)0;
//     }
//     if (arg0->stunned != 0xFF) {
//         if (arg0->stunned != 0xFE) {
//             if ((arg0->health != 0) || (1 != arg0->interaction_state)) {
//                 arg0->stunned -= 1;
//             }
//         }
//         arg0->unk10C -= D_800CC264;
//         if ((arg0->unk28 < D_80099484) && ((arg0->unkF4 & 0x100) != 0)) {
//             arg0->unk10C = (u16)0;
//         }
//         if ((s32) arg0->unk10C <= 0) {
//             if (arg0->unk31C != 0) {
//                 arg0->unk31C->matrix_physics = (u8)0;
//             }
//             arg0->unk10C = (u16)0;
//             func_1505E874(0.0f, D_800C3E78);
//         }
//         if (arg0->stunned == 0) {
//             arg0->xz_velocity = 0.0f;
//             arg0->unk81 = (u8)0;
//             arg0->unk76 = arg0->unk78 = arg0->unk7A;
//             if (arg0->in_water != 0) {
//                 arg0->y_velocity = 0.0f;
//                 if (arg0->interaction_state == 1) {
//                     func_1506B078();
//                 }
//             } else if (arg0->interaction_state == 1) {
//                 arg0->unkF8 &= 0xFFFF7FFF;
//                 arg0->gravity = 4.0f;
//             }
//             if (arg0->unk238 != 0) {
//                 arg0->unk23A = arg0->unk238;
//             }
//         } else {
//             if ((arg0->unk10B & 2) == 0) {
//                 phi_a2 = arg0->unk76;
//                 if ((arg0->unk10B & 4) != 0) {
//                     phi_a2 ^= 0x8000;
//                 }
//                 arg0->unk80 = (u8)0xA;
//                 func_150599C8(arg0, 12, phi_a2);
//             }
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058898.s")

void func_15058EA4(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    if (arg1 < arg0->y_position) {
        arg0->gravity = arg2;
    } else if (arg0->y_position < arg3) {
        arg0->gravity = arg4;
    }
    if (arg5 < arg0->y_velocity) {
        arg0->y_velocity = arg5;
    } else if (arg0->y_velocity < arg6) {
        arg0->y_velocity = arg6;
    }
}

#ifdef NON_MATCHING
void func_15058F24(struct127 *arg0, f32 arg1, f32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 var_f20;

    var_f20 = arg1;
    temp_f12 = var_f20;
    temp_f16 = 0.5f - var_f20;
    if (var_f20 >= 0.5f) {
        var_f20 -= 0.5f;
    }
    temp_f2 = arg0->y_position;
    temp_f14 = arg0->unk118 + 9.0f;
    if ((temp_f2 < temp_f14) || ((s32) arg0->in_water >= 0x64)) {
        if (arg0->in_water == 0) {
            arg0->y_position = temp_f14;
            arg0->in_water = 0x64;
            arg0->gravity = temp_f16 * -6.0f;
            arg0->y_velocity *= temp_f12;
        } else {
            if ((temp_f14 + 100.0f) < temp_f2) {
                arg0->in_water = 0;
            }
            if (temp_f16 < 0.0f) {
                arg0->gravity = temp_f16 * -6.0f;
            } else {
                temp_f2_2 = arg0->y_position;
                temp_f12_2 = temp_f2_2 - ((temp_f14 + 10.0f) - (120.0f * var_f20));
                if ((fabsf(temp_f12_2) < 2.0f) && (fabsf(arg0->y_velocity) < 2.0f)) {
                    arg0->y_velocity = 0.0f;
                    arg0->gravity = 1.0f;
                    arg0->y_position = temp_f2_2 - (temp_f12_2 * 0.6f);
                } else {
                    temp_f0 = arg0->y_velocity;
                    if (temp_f12_2 > 0.0f) {
                        if (temp_f0 > 0.0f) {
                            arg0->gravity = temp_f16 * 6.0f;
                            arg0->y_velocity = temp_f0 * 0.5f;
                        }
                    } else {
                        temp_f2_3 = temp_f16 * 80.0f;
                        if (temp_f2_3 < temp_f0) {
                            arg0->y_velocity = temp_f2_3;
                        }
                        arg0->gravity = temp_f16 * -6.0f;
                    }
                }
            }
        }
        temp_f2_4 = -100.0f * var_f20;
        if (arg0->y_velocity < temp_f2_4) {
            arg0->y_velocity = temp_f2_4;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058F24.s")
#endif
// NON-MATCHING: besides missing mov.s, its just a few regallocs
// void func_15058F24(struct127 *arg0, f32 arg1, f32 arg2) {
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 tmp;
//     f32 temp_f16;
//
//     temp_f16 = 0.5f - arg1;
//     if (arg1 >= 0.5f) {
//         arg1 -= 0.5f;
//     }
//     temp_f14 = arg0->unk118 + 9.0f;
//     if ((arg0->y_position < temp_f14) || ((arg0->in_water < 0x64) == 0)) {
//
//         if (0) {};
//
//         if (arg0->in_water == 0) {
//             arg0->y_position = temp_f14;
//             arg0->in_water = (u8)0x64U;
//             arg0->gravity = temp_f16 * -6.0f;
//             arg0->y_velocity *= arg1;
//         } else {
//             if ((temp_f14 + 100.0f) < arg0->y_position) {
//                 arg0->in_water = (u8)0U;
//             }
//             if (temp_f16 < 0.0f) {
//                 arg0->gravity = temp_f16 * -6.0f;
//             } else {
//                 temp_f12 = arg0->y_position - ((temp_f14 + 10.0f) - (120.0f * arg1));
//                 if ((fabsf(temp_f12) < 2.0f) && (fabsf(arg0->y_velocity) < 2.0f)) {
//                     tmp = temp_f12 * D_800994A4;
//                     arg0->gravity = 1.0f;
//                     arg0->y_velocity = 0.0f;
//                     arg0->y_position -= tmp;
//                 } else {
//                     if (temp_f12 > 0.0f) {
//                         if (arg0->y_velocity > 0.0f) {
//                             arg0->gravity = temp_f16 * 6.0f;
//                             arg0->y_velocity *= 0.5f;
//                         }
//                     } else {
//                         temp_f12 = temp_f16 * 80.0f;
//                         if (arg0->y_velocity > temp_f12) {
//                             arg0->y_velocity = temp_f12;
//                         }
//                         arg0->gravity = temp_f16 * -6.0f;
//                     }
//                 }
//             }
//         }
//         temp_f12 = -100.0f * arg1;
//         if (arg0->y_velocity < temp_f12) {
//             arg0->y_velocity = temp_f12;
//         }
//     }
// }

void func_15059140(struct127 *arg0) {
    f32 sp2C;

    sp2C = 0.5f;
    D_800CC268 = 0;
    if ((arg0->unk13D == 0) || ((s32) arg0->unk21C < 0x10)) {
        if (arg0->unk223 != 8) {
            func_15059C84(arg0);
            func_1505A770(arg0);
        }
    }
    func_1505D6F0(arg0, D_800C3E78);
    func_15055E50(arg0, arg0->unk1E4);
    if (arg0->id == 8) {
        func_15056150(arg0);
    }
    if (arg0->unk13D < 0x64) {
        func_15058898(arg0, arg0->old_y_position);
    }
    if (arg0->unkF4 & 0x40000) {
        if (((arg0->unkF4 & 0x12000) != 0) || (D_800CC268 != 0)) {
            arg0->unk21C = 0U;
        }
    }
    if (arg0->unkB0 != 0) {
        func_15058F24(arg0, arg0->unkB0 * 0.01f, 1.0f);
    }
    if (arg0->unkF8 & 0x20000) {
        func_15056258(arg0);
    }
    if (arg0->in_water != 0) {
        func_15059444(arg0);
    }
    if (arg0->id == 0xA) {
        arg0->unk180 = -5000.0f;
    }
    if ((arg0->unkF8 & 0x180000) != 0) {
        func_150511E8(arg0);
    }
    func_1505B5F8(arg0, arg0->unk180);
    if (((arg0->unkF4 & 0x1000) != 0) && (arg0->unk28 < 0.2f)) {
        func_15056B08(arg0);
    }
    if (arg0->unkF8 & 0x80000) {
        sp2C = 0.15f;
    }
    func_1505A250(0, 0, sp2C, &arg0->unk164, &arg0->unk168);
    if (arg0->unkD0 != 0) {
        func_1505C7D8(arg0, D_800C3E78);
    }
    if (arg0->unk13D == 0) {
        if (D_800BE9A0 >= arg0->unk10F) {
            arg0->unk10F = 0U;
        } else {
            arg0->unk10F -= D_800BE9A0;
        }
    }
    if (arg0->unk107 != 0) {
        arg0->unk107 -= 1;
    }
    if (arg0->immune != 0xFF) {
        if (D_800BE9A0 >= arg0->immune) {
            arg0->immune = 0U;
        } else {
            arg0->immune -= D_800BE9A0;
        }
    }
}

void func_150593C4(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    func_1505A184(arg1, arg2, 0, &sp2C, &sp28, &sp24);
    arg0->unk16C += (sp2C - arg0->unk16C) * arg3;
    arg0->unk170 += (sp28 - arg0->unk170) * arg3;
}

void func_15059444(struct127 *arg0) {
    s32 sp1C;
    s32 phi_v0;
    s32 tmp;

    sp1C = -1;

    switch (D_800BE9F0) {
        case 4:
            func_150593C4(arg0, 0x4000, 50.0f, 0.05999999865889549f);
            break;
        case 6:
            sp1C = func_15083E0C(28);
            break;
        case 41:
            if (func_150A29C8(D_800C3E78, 0x4028) == 0) {
                phi_v0 = 12;
            } else if (func_150A29C8(D_800C3E78, 0x400E) == 0) {
                phi_v0 = 10;
            } else if (func_150A29C8(D_800C3E78, 0x400D) == 0) {
                phi_v0 = 9;
            } else {
                phi_v0 = 6;
            }
            sp1C = func_15083E0C(phi_v0);
            // FIXME: fakematch to force regalloc
            dummy_label_858530:;
            break;
        case 43:
            sp1C = func_15083E0C(18);
            break;
        case 65:
            if (func_150A29C8(D_800C3E78, 0x401F) == 0) {
                phi_v0 = 27;
            } else {
                phi_v0 = 26;
            }
            sp1C = func_15083E0C(phi_v0);
            break;
    }

    if (sp1C != -1) {
        func_150611E8(arg0, sp1C);
    }
}

void func_1505959C(struct127 *arg0, s32 arg1) {
    struct252 *temp_v0;
    s32 *temp_v1;
    s32 phi_v1;

    arg0->unkF8 &= 0xFF7FFFFF;
    arg0->unk13D = arg1 + 100;
    arg0->unk21C = 0;
    arg0->gravity = 4.0f;
    arg0->unk25C &= ~8;

    D_800CC2D0[arg1].unk83 = 0xFF;
    D_800CC2D0[arg1].disable_run = 0xFF;
    phi_v1 = 0;
    if (arg0->id == 0x57) {
        phi_v1 = 1;
    }
    if (D_800CC2D0[arg1].id == 0x9B) {
        phi_v1 = 2;
    }
    if (arg0->id == 0x5E) {
        phi_v1 = 3;
    }
    if (arg0->id == 0x3C) {
        phi_v1 = 4;
        D_800CC2D0[arg1].unk13C = (u8)0;
        D_800CC2D0[arg1].unk76 = func_1505A630(arg0->x_position - D_800CC2D0[arg1].x_position, D_800CC2D0[arg1].z_position - arg0->z_position, 0);
    }
    if (arg0->id == 0x89) {
        phi_v1 = 5;
    }
    func_1505E650(&D_800CC2D0[arg1], D_800860C0[phi_v1], D_800860CC[phi_v1], 0.0f, 0.0f, 0.0f, 0);
    arg0->stunned = 0xFE;
    arg0->unk105 = 0;
    arg0->unk106 = func_1505E7CC(D_800860E4[phi_v1], arg0);
    arg0->unk84.uh = 0xFFFF;
    func_1505E874(D_800C3E78, arg0);
    temp_v1 = (s32*)D_800D1588[arg0->id];
    if (temp_v1 != 0) {
        temp_v0 = (struct252 *)*(temp_v1 - 2);
        if ((temp_v0 != 0) && ((temp_v0[arg0->unk106].unk15 & 2) != 0)) {
            arg0->unk7A = D_800CC2D0[arg1].unk7A;
        }
        if ((temp_v0 == 0) || ((temp_v0[arg0->unk106].unk15 & 1) == 0)) {
            arg0->unk13E = (arg0->unk7A - D_800CC2D0[arg1].unk7A) >> 8;
        } else {
            arg0->unk13E = 0;
        }
    } else {
        arg0->unk13E = (arg0->unk7A - D_800CC2D0[arg1].unk7A) >> 8;
    }
}

void func_150597FC(struct127 *arg0)
{
  s32 var_a1;
  struct126 *temp_a2;
  s32 new_var;
  struct127 *temp_v0;
  struct127 *temp_v0_2;
  int temp_v1;
  new_var = D_800CC268;
  var_a1 = 0;
  // fakematch: s32 blk_t; block-local declarations below are basic-block boundaries (blkvar, s69)
  if (D_8008FD8C > 0)
  {
    s32 blk_t;
    loop_2:
    if ((((((!((1 << var_a1) & new_var)) || ((temp_v0 = &D_800CC2D0[var_a1], temp_v0->unk13C != 0))) || (temp_v0->disable_run != 0)) || (temp_v0->interaction_state != 1)) || (temp_v0->stunned != 0)) || (temp_v0->unk127 == 0xFF))
    {
      s32 blk_t;
      var_a1 += 1;
      if (var_a1 < D_8008FD8C)
      {
        s32 blk_t;
        if (1) { } // fakematch: permuter empty if (BB split)
        goto loop_2;
      }
      if (!arg0->unk28) { } // fakematch: permuter empty if (BB split)
    }

  }
  if (var_a1 != D_8008FD8C)
  {
    s32 blk_t;
    temp_v0_2 = &D_800CC2D0[var_a1];
    if (temp_v0_2->unk13C == 0)
    {
      s32 blk_t;
      temp_a2 = temp_v0_2->unk31C;
      if ((((((((((temp_a2->unk27 == 0) && (temp_v0_2->health != 0)) && (arg0->unk13D == 0)) && (((arg0->stunned != 0) || (arg0->unk25C & 0x1000)) || (arg0->id == 0x57))) && (arg0->unk28 == 0.0f)) && (temp_v0_2->unk28 == 0.0f)) && (arg0->unk25C & 8)) && (temp_a2->unk19B == 0)) && (((temp_v1 = arg0->id, temp_v1 != 0xA9)) || ((*((u8 *) (((u8 *) temp_v0_2) + 0x128))) == 0))) && ((temp_v1 != 0xA8) || ((*((u8 *) (((u8 *) temp_v0_2) + 0x128))) != 0)))
      {
        s32 blk_t;
        temp_v0_2->unk13C = D_800C3E78 + 0x64;
        temp_v0_2->xz_velocity = 0.0f;
        *((s16 *) (((u8 *) temp_a2) + 0x18)) = 0;
        func_1505959C(arg0, var_a1);
      }
    }
  }
}
#ifdef NON_MATCHING
u8 func_150599C8(struct127 *arg0, u8 arg1, u16 arg2) {
    s16 temp_a2;
    s16 temp_t3;
    s16 temp_v1;
    s16 var_a3;
    s32 temp_lo;
    s32 var_v0;
    u16 temp_t0;
    u16 temp_t1;
    u16 temp_t2;

    temp_t0 = arg0->unk7A;
    temp_t1 = arg0->unk1EA;
    var_a3 = (arg2 & 0xFFFF) - temp_t0;
    var_v0 = (s32) ((((arg1 & 0xFF) << 8) + arg0->unk1E8) * D_800CC264) / 100;
    if (temp_t1 != 0) {
        temp_t2 = arg0->unk1EC;
        temp_lo = (s32) (temp_t1 * D_800CC264) / 100;
        temp_a2 = temp_t2 + temp_lo;
        temp_t3 = temp_t2 - temp_lo;
        if (temp_a2 < var_a3) {
            var_a3 = temp_a2;
        }
        if (var_a3 < temp_t3) {
            var_a3 = temp_t3;
        }
    }
    temp_v1 = var_a3;
    if (var_a3 < 0) {
        var_a3 ^= 0xFFFF;
    }
    if (var_a3 < var_v0) {
        var_v0 = (s32) var_a3;
    }
    if (!(arg0->unkF4 & 1) && (arg0->unk80 != 0)) {
        if (temp_v1 < 0) {
            arg0->unk7A = temp_t0 - var_v0;
        } else {
            arg0->unk7A = temp_t0 + var_v0;
        }
    }
    return (var_a3 >> 8) & 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150599C8.s")
#endif
#ifdef NON_MATCHING
s32 func_15059B54(struct127 *arg0, u16 arg1) {
    s16 temp_a1_2;
    s16 temp_t0;
    s16 temp_t2;
    s16 temp_v0;
    s16 var_a2;
    s16 var_v0;
    s32 temp_lo;
    u16 temp_a1;
    u16 temp_t1;
    u16 temp_v1;

    temp_v1 = arg0->unk76;
    temp_v0 = arg0->unk78 - temp_v1;
    var_v0 = temp_v0;
    var_a2 = temp_v0;
    if (temp_v0 < 0) {
        var_a2 = temp_v0 ^ 0xFFFF;
    }
    temp_a1 = arg0->unk1EA;
    if (temp_a1 != 0) {
        temp_t1 = arg0->unk1EC;
        temp_lo = (s32) (temp_a1 * D_800CC264) / 100;
        temp_t0 = temp_t1 + temp_lo;
        temp_t2 = temp_t1 - temp_lo;
        if (temp_t0 < var_v0) {
            var_v0 = temp_t0;
        }
        if (var_v0 < temp_t2) {
            var_v0 = temp_t2;
        }
    }
    temp_a1_2 = var_v0;
    if (var_v0 < 0) {
        var_v0 ^= 0xFFFF;
    }
    if (var_v0 < (s32) arg1) {
        arg1 = (u16) var_v0;
    }
    if (!(arg0->unkF4 & 1)) {
        if (temp_a1_2 < 0) {
            arg0->unk76 = temp_v1 - arg1;
            arg0->unk1EC = (u16) -(s32) arg1;
        } else {
            arg0->unk76 = temp_v1 + arg1;
            arg0->unk1EC = arg1;
        }
    }
    return (var_a2 >> 8) & 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059B54.s")
#endif
// NON-MATCHING: 90% there, missing an s16 cast
// u8 func_15059B54(struct127 *arg0, u16 arg1) {
//     s16 temp_t8;
//     s16 temp_t8_2;
//     s16 temp_t2;
//     s32 temp_lo;
//     s16 phi_a2;
//
//     temp_t8 = arg0->unk78 - arg0->unk76;
//     phi_a2 = temp_t8;
//     if (phi_a2 < 0) {
//         phi_a2 = phi_a2 ^ 0xFFFF;
//     }
//     if (arg0->unk1EA != 0) {
//         temp_lo = (s32) (arg0->unk1EA * D_800CC264) / 0x64;
//         temp_t8_2 = arg0->unk1EC + temp_lo;
//         temp_t2 = arg0->unk1EC - temp_lo;
//         if (temp_t8_2 < temp_t8) {
//             temp_t8 = temp_t8_2;
//         }
//         if (temp_t8 < temp_t2) {
//             temp_t8 = temp_t2;
//         }
//     }
//
//     if (temp_t8 < 0) {
//         temp_t8 ^= 0xFFFF;
//     }
//     if (temp_t8 < arg1) {
//         arg1 = temp_t8;
//     }
//     if ((arg0->unkF4 & 1) == 0) {
//         if (temp_t8 < 0) {
//             arg0->unk76 -= arg1;
//             arg0->unk1EC = -arg1;
//         } else {
//             arg0->unk76 += arg1;
//             arg0->unk1EC = arg1;
//         }
//     }
//     return phi_a2 >> 8;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059C84.s")
#ifdef NON_MATCHING
extern f32 D_80099880;
extern f32 D_80099884;
void func_1505A184(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 var_f18;
    f32 temp_f20_2;
    f32 temp_f20;
    f32 temp_f16;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 sp20;
    f32 sp2C;

    temp_f20 = arg1 * 0.5f;
    temp_f12 = arg2 * D_80099880;
    arg2 = temp_f12;
    *arg5 = func_150AD78C(temp_f12) * -temp_f20;
    temp_f20_2 = func_150AD780(arg2) * temp_f20;
    var_f18 = (f32) arg0;
    if ((s32) arg0 < 0) {
        var_f18 += 4294967296.0f;
    }
    temp_f12_2 = var_f18 * D_80099884;
    sp20 = temp_f12_2;
    sp2C = func_150AD780(temp_f12_2);
    temp_f16 = -func_150AD78C(sp20);
    *arg3 = sp2C * temp_f20_2;
    *arg4 = temp_f16 * temp_f20_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A184.s")
#endif
#ifdef NON_MATCHING
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4) {
    f32 sp4;
    f32 sp0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;

    temp_f16 = *arg3;
    temp_f2 = arg0 - temp_f16;
    temp_f18 = arg1 - *arg4;
    if ((temp_f2 != 0.0f) || (temp_f18 != 0.0f)) {
        temp_f10 = arg2 * *D_800D1550;
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f18 * temp_f18));
        arg2 = temp_f10;
        sp4 = temp_f0;
        sp0 = fabsf((temp_f2 / temp_f0) * temp_f10);
        temp_f0_2 = fabsf((temp_f18 / sp4) * temp_f10);
        if (temp_f2 >= 0.0f) {
            *arg3 = temp_f16 + sp0;
            if (arg0 < *arg3) {
                goto block_6;
            }
        } else {
            *arg3 = temp_f16 - sp0;
            if (*arg3 < arg0) {
block_6:
                *arg3 = arg0;
            }
        }
        if (temp_f18 >= 0.0f) {
            *arg4 += temp_f0_2;
            if (arg1 < *arg4) {
                goto block_11;
            }
        } else {
            *arg4 -= temp_f0_2;
            if (*arg4 < arg1) {
block_11:
                *arg4 = arg1;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A250.s")
#endif
#ifdef NON_MATCHING
extern f32 D_80099888;
extern f32 D_8009988C;
extern f32 D_80099890;
extern f32 D_80099894;
extern f32 D_80099898;
extern u8 D_800CC69C;

f32 func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4) {
    f32 var_f12;
    f32 var_f14;
    f32 var_f20;
    u8 temp_v0;

    var_f12 = arg0;
    var_f20 = arg2 * *D_800D1550;
    var_f14 = arg3 * *D_800D1550;
    if ((D_800CC69C != 0) && (arg1->unk28 < 5.0f) && (arg1->interaction_state != 0x1E)) {
        var_f20 = 0.0f;
    }
    if (arg1->interaction_state == 1) {
        if (arg1->in_water != 0) {
            var_f20 = 2.0f;
            var_f14 *= D_80099888;
        }
        if (arg1->unkA8 != 0) {
            var_f14 *= 0.25f;
        }
        temp_v0 = arg1->unk81;
        if (temp_v0 != 0) {
            if (temp_v0 & 0x40) {
                if (temp_v0 & 0x20) {
                    var_f14 = 0.0f;
                } else {
                    var_f14 = D_8009988C;
                }
            } else {
                var_f14 *= D_80099890;
                if ((s32) arg4 >= 0x2E) {
                    var_f20 *= 0.5f;
                }
                if ((s32) arg4 >= 0x5B) {
                    var_f12 *= 0.5f;
                }
            }
        }
        if (arg1->unkAE != 0) {
            var_f14 *= D_80099894;
        }
    }
    if (var_f12 < 0.0f) {
        if (arg1->xz_velocity > 0.0f) {
            var_f14 += var_f20;
        } else {
            var_f14 = var_f20;
        }
    } else if (arg1->xz_velocity < 0.0f) {
        var_f20 += var_f14;
    }
    if (var_f12 < arg1->xz_velocity) {
        arg1->xz_velocity -= var_f14;
        if (arg1->xz_velocity < var_f12) {
            goto block_32;
        }
    } else {
        if ((var_f12 - 1.0f) < arg1->xz_velocity) {
            var_f20 *= D_80099898;
        }
        arg1->xz_velocity += var_f20;
        if (var_f12 < arg1->xz_velocity) {
block_32:
            arg1->xz_velocity = var_f12;
        }
    }
    return arg1->xz_velocity;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A3A8.s")
#endif
f32 func_1505A5CC(struct49 *arg0) {
    f32 x, y;
    f32 ret;

    // regalloc nonsense
    ret = arg0->unk2;
    x = ret;
    y = arg0->unk3;

    x = sqrtf(x*x + y*y) * 0.6f;
    ret = x;

    if (ret > 35.0f) {
        ret = 35.0f;
    }

    return ret;
}

u16 func_1505A630(f32 arg0, f32 arg1, s32 arg2) {
    return ((u16) (u32) (func_150484A0(-arg0, arg1) * 10430.378f)) + 16384;
}

f32 func_1505A6F8(struct127 *arg0, struct127 *arg1) {
    f32 x, z;

    x = arg0->x_position - arg1->x_position;
    x *= x;
    z = arg0->z_position - arg1->z_position;
    z *= z;
    return sqrtf(x + z);
}

// distance between two objects?
f32 func_1505A72C(struct127 *arg0, struct127 *arg1) {
    f32 x, y, z;

    x = arg0->x_position - arg1->x_position;
    x *= x;
    z = arg0->z_position - arg1->z_position;
    z *= z;
    y = arg0->y_position - arg1->y_position;
    y *= y;
    return sqrtf(x + z + y);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A770.s")
// a big one, but could be ok
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A9AC.s")

#ifdef NON_MATCHING
void func_1505B5F8(struct127 *arg0, f32 arg1) {
    f32 sp3C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f16;
    s32 temp_v0_4;
    struct129 *temp_v1;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    var_f16 = arg0->unk28;
    if (!(arg0->unkF8 & 0x8000)) {
        temp_v0 = arg0->unk252;
        if ((temp_v0 != 0) && ((f32) (arg0->unk253 * 8) < (arg0->unk1CC - arg0->y_position)) && (arg0->stunned == 0)) {
            arg0->stunned = 0xFE;
            arg0->unk105 = 0;
            sp3C = var_f16;
            arg0->unk106 = func_1505E7CC((s32) temp_v0, arg0);
            arg0->unk84.uh = 0xFF;
            func_1505E874(D_800C3E78, arg0);
            arg0->y_position = arg0->old_y_position;
        }
        temp_f0 = arg0->y_position;
        arg0->unk28 = temp_f0 - arg1;
        if (temp_f0 <= arg1) {
            arg0->unkF4 |= 0x8000;
            temp_v0_2 = D_800B0DF0->unk13;
            if ((temp_v0_2 != 0) && (var_f16 != 0.0f)) {
                sp3C = var_f16;
                func_15174690((s32) D_800C3E78, 0, 0x1000 / (s32) temp_v0_2, 0, 0x199, 4, 0xAA, 0xFFU, 0);
            }
            arg0->y_position = arg1;
            arg0->unk28 = 0.0f;
            if ((arg0->stunned != 0) || !(arg0->unkF8 & 0x10000)) {
                if (arg0->interaction_state == 1) {
                    if (arg0->y_velocity < -6.0f) {
                        arg0->y_velocity = -6.0f;
                    }
                } else {
                    if ((arg0->unk1CC - arg0->y_position) > 450.0f) {
                        temp_v0_3 = arg0->health;
                        if ((s32) temp_v0_3 > 0) {
                            temp_v1 = arg0->unk144;
                            if ((temp_v1 != NULL) && !(temp_v1->unkE & 0x80)) {
                                arg0->health = temp_v0_3 - 1;
                            }
                        }
                    }
                    arg0->unk1CC = arg1;
                    if ((arg0->stunned == 0) && (temp_f2 = arg0->gravity, (temp_f2 > 0.5f))) {
                        if ((arg0->unkF8 & 0x800) && (var_f16 != 0.0f) && (temp_f0_2 = arg0->y_velocity, (temp_f0_2 < (-4.0f * temp_f2 * *D_800D1550)))) {
                            temp_v0_4 = arg0->unk2CC;
                            arg0->y_velocity = (0.0f - temp_f0_2) * ((f32) arg0->unk2CB * 0.01f);
                            if ((temp_v0_4 != 0) && (arg0->y_velocity > 5.0f)) {
                                D_800D1580 = temp_v0_4;
                                func_1506E5FC();
                            }
                        } else if (arg0->interaction_state != 7) {
                            arg0->y_velocity = -4.0f * *D_800D1550;
                        }
                    } else {
                        if (arg0->unkF4 & 0x80) {
                            var_f10 = -4.0f;
                            goto block_35;
                        }
                        if ((var_f16 == 0.0f) || (temp_f0_3 = arg0->y_velocity, ((-1.5f * arg0->gravity * *D_800D1550) < temp_f0_3))) {
                            arg0->y_velocity = 0.0f;
                        } else {
                            var_f10 = (0.0f - temp_f0_3) * ((f32) arg0->unk2CB * 0.01f);
block_35:
                            arg0->y_velocity = var_f10;
                        }
                        arg0->xz_velocity *= 0.9f;
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B5F8.s")
#endif
// void func_1505B5F8(struct127 *arg0, f32 arg1) {
//     f32 tmp;
//     u8 temp_v0_2;
//
//     if ((arg0->unkF8 & 0x8000) == 0) {
//         if (arg0->unk252 != 0) {
//             if ((arg0->unk253 * 8) < (arg0->unk1CC - arg0->y_position)) {
//                 if (arg0->stunned == 0) {
//                     arg0->stunned = (u8)0xFEU;
//                     arg0->unk105 = (u8)0;
//                     arg0->unk106 = func_1505E7CC(arg0->unk252, arg0);
//                     arg0->unk84.uh = (u16)0xFF;
//                     func_1505E874(D_800C3E78, arg0);
//                     arg0->y_position = (f32) arg0->old_y_position;
//                 }
//             }
//         }
//         arg0->unk28 = arg0->y_position - arg1;
//         if (arg0->y_position <= arg1) {
//             arg0->unkF4 |= 0x8000;
//             temp_v0_2 = D_800B0DF0->unk13;
//             if (temp_v0_2 != 0) {
//                 if (arg0->unk28 != 0.0f) {
//                     func_15174690(D_800C3E78, 0, 0x1000 / (s32) temp_v0_2, 0, 0x199, 4, 0xAA, 0xFF, 0); // 0.0f, arg1,
//                 }
//             }
//             arg0->y_position = arg1;
//             tmp = arg0->unk28;
//             arg0->unk28 = 0.0f;
//             if ((arg0->stunned != 0) || ((arg0->unkF8 << 0xF) >= 0)) {
//                 if (arg0->interaction_state == 1) {
//                     if (arg0->y_velocity < -6.0f) {
//                         arg0->y_velocity = -6.0f;
//                     }
//                 } else {
//                     if ((arg0->unk1CC - arg0->y_position) > 450.0f) {
//                         if (arg0->health > 0) {
//                             if ((arg0->unk144 != 0) && ((arg0->unk144->unkE & 0x80) == 0)) {
//                                 arg0->health = (u8) (arg0->health - 1);
//                             }
//                         }
//                     }
//                     arg0->unk1CC = arg1;
//                     if ((arg0->stunned == 0) && (arg0->gravity > 0.5f)) {
//                         if (((arg0->unkF8 & 0x800) != 0) && (tmp != 0.0f) && ((arg0->y_velocity < (-4.0f * arg0->gravity * D_800D1550[0])))) {
//                             arg0->y_velocity = ((0.0f - arg0->y_velocity) * ((f32) arg0->unk2CB * D_8009950C));
//                             if ((arg0->unk2CC != 0) && (arg0->y_velocity > 5.0f)) {
//                                 D_800D1580 = arg0->unk2CC;
//                                 func_1506E5FC();
//                             }
//                         } else if (arg0->interaction_state != 7) {
//                             arg0->y_velocity = -4.0f * D_800D1550[0];
//                         }
//                     } else {
//                         if ((arg0->unkF4 & 0x80) != 0) {
//                             arg0->y_velocity = -4.0f;
//                         } else if ((tmp == 0.0f) || (((-1.5f * arg0->gravity * D_800D1550[0]) < arg0->y_velocity))) {
//                             arg0->y_velocity = 0.0f;
//                         } else {
//                             arg0->y_velocity = (0.0f - arg0->y_velocity) * ((f32) arg0->unk2CB * D_80099510);
//                         }
//                         arg0->xz_velocity *= D_80099514;
//                     }
//                 }
//             }
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B9C4.s")

s16 func_1505C140(struct127 *arg0, struct127 *arg1) {
    s16 ret = func_1505A630(arg0->x_position - arg1->x_position, arg1->z_position - arg0->z_position, 0);
    ret -= arg1->unk7A;

    if (ret < 0) {
        ret = -ret;
    }
    return ret;
}

struct252 *func_1505C1A4(struct127 *arg0) {
    s32 *temp_v1;
    struct252 *ret;

    if ((arg0->id != 0xFF) && (D_800D1588[arg0->id] != 0)) {
        temp_v1 = (s32*)D_800D1588[arg0->id] - 3;
        ret = *temp_v1;
    } else {
        ret = &D_8009A9F8;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
// NON-MATCHING: 1 line + regalloc
// s32 func_1505D024(struct127 *arg0, s32 arg1, u16 arg2, s32 arg3) {
//     s32 pad;
//     s32 ret;
//     s32 temp_lo;
//     struct252 *sp30;
//
//     sp30 = &D_8009A9F8;
//     if (D_800C35EA == 1) {
//         return 0;
//     }
//     if ((arg1 & 0x20000) && (arg0->immune != 0)) {
//         return 0;
//     }
//     if ((arg1 & 0x40000) && (arg0->stunned != 0)) {
//         return 0;
//     }
//     if (((arg1 << 0xB) >= 0) && (arg0->health == 0)) {
//         return 0;
//     }
//     if (arg3 == -1) {
//         D_800D1340 = (u8)0;
//     } else {
//         D_800D1340 = arg3 + 1;
//     }
//     D_800D1292 = arg2;
//     D_800D1296 = arg2;
//     if (arg1 & 0x10000) {
//         sp30 = func_1505C1A4(D_800D154C);
//     }
//
//     temp_lo = ((s32)arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127);
//     ret = 1 << temp_lo;
//     if (arg1 & 0x80000) {
//         // lw instead of move.
//         ret = func_1505C1E4(&D_800D121C, arg0, sp30, arg1 & 0xFF, temp_lo + 1, 0, 7);
//     } else {
//         func_1505B9C4(&D_800D121C, arg0, sp30, sp30, arg1 & 0xFF, temp_lo + 1, 7);
//     }
//     return ret;
// }

void func_1505D1C4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7) {
    s32 pad;
    s32 tmp;

    tmp = D_800C3E78;
    func_1505F188(&D_800D121C);
    D_800D1230 = arg0;
    D_800D1234 = arg1;
    D_800D1238 = arg2;
    D_800D1340 = arg4 + 1;
    D_800D1359 = arg6;
    D_800D1292 = arg5;
    D_800C3E78 = 25;
    D_800D1510 = arg7;
    D_800D1330 = 100.0f;
    D_800D12EC = (arg3 & 0xFFFF) + 1;
    D_800D1368 = 0.5f;
    D_800D136C = 0.5f;
    func_1505C7D8(&D_800D121C, 25);
    D_800C3E78 = tmp;
}

void func_1505D2B8(struct127 *arg0, u8 arg1) {
    struct253 *temp_v0;

    temp_v0 = &D_8009A6D8[arg1];
    arg0->y_velocity = temp_v0->unk18;
    arg0->xz_velocity = temp_v0->unk14;
    arg0->gravity = temp_v0->unk1C;
    arg0->stunned = 0xFE;
    arg0->unk105 = 0;
    arg0->unk106 = func_1505E7CC(arg0->unk10E & 0x7F, arg0);
    arg0->unk10E = 0xFF;
    func_1505E874(D_800C3E78, arg0);
}

f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 sp24;
    f32 temp_f0;
    f32 temp_f12;

    if (arg3 != 1.0f) {
        arg1 = arg1 * arg3;
        arg2 = arg2 * arg3;
    }
    temp_f12 = (arg0 - 90.0f) * 0.017453292f; // 0.01745329238474369f;
    sp24 = func_150AD780(temp_f12);
    temp_f0 = func_150AD78C(temp_f12);
    *arg4 = (-arg1 * temp_f0) + (arg2 * sp24);
    return (arg1 * sp24) + arg2 * temp_f0;
}

#ifdef NON_MATCHING
extern s8 D_800CC68C;
extern s8 D_800CC68D;

void func_1505D408(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f18;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 temp_a2;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;

    var_f14 = arg2;
    var_f12 = arg5;
    var_f2 = 0.4f;
    var_v0 = 0;
    var_v1 = 0;
    if (var_f12 < 1.0f) {
        var_f12 = 1.2f;
    }
    if ((var_f14 == 0.0f) && (arg4 == 0.0f)) {
        var_f14 = 1.0f;
    }
    D_800CC268 |= 1 << arg7;
    if (!(arg1->unkF8 & 0x10) || (D_800CC68C = (s8) arg7, var_f2 = 0.8f, (arg1->id != 0x61)) || (arg0->interaction_state != 1)) {
        temp_t0 = arg0->unkF8;
        temp_a2 = arg1->unkF8;
        if (temp_t0 & 1) {
            var_v0 = 1;
        }
        if (temp_t0 & 0x200) {
            var_v0 = (var_v0 | 2) & 0xFF;
        }
        if (temp_a2 & 1) {
            var_v1 = 1;
        }
        if (temp_a2 & 0x200) {
            var_v1 = (var_v1 | 2) & 0xFF;
        }
        if (var_v1 >= var_v0) {
            if ((temp_a2 & 0x400) && (arg1->unk28 == 0.0f)) {
                D_800CC68D = arg7 + 0x64;
            }
            temp_f0 = sqrtf(var_f12);
            temp_f18 = 1.0f / temp_f0;
            temp_f8 = arg6 - temp_f0;
            arg6 = temp_f8;
            temp_f10 = temp_f8 * var_f2;
            arg3 *= temp_f18;
            arg6 = temp_f10;
            arg0->x_position += temp_f10 * (var_f14 * temp_f18);
            arg0->z_position += arg6 * (arg4 * temp_f18);
            arg0->y_position += arg6 * arg3;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D408.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D5D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D6F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DADC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
#ifdef NON_MATCHING
f32 func_1505DF10(u8 *arg0, u8 arg1, u16 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f2;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg1];
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x18)) - temp_v0->y_position;
    temp_f12_2 = temp_v0->x_position - (*(f32 *)((u8 *)arg0 + 0x14));
    *arg4 = temp_f2;
    temp_f14_2 = (*(f32 *)((u8 *)arg0 + 0x1C)) - temp_v0->z_position;
    sp20 = temp_f12_2;
    sp1C = temp_f2;
    sp18 = temp_f14_2;
    temp_f12 = temp_f12_2 * temp_f12_2;
    *arg2 = func_1505A630(temp_f12_2, temp_f14_2, 0);
    temp_f14 = temp_f14_2 * temp_f14_2;
    *arg3 = temp_f12 + temp_f14;
    return temp_f12 + (temp_f2 * temp_f2) + temp_f14;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DF10.s")
#endif
void func_1505DFDC(struct127 *arg0) {
    s32 id;
    struct_eu_anim *anim = (struct_eu_anim *)arg0->unk2D0;

    arg0->unk84.uh = 0xFFFF;
    if (anim != NULL) {
        id = arg0->id;
        anim->unk28 = 0;
        bzero(anim->unk40, 0x3A0);
        anim->unk40[1] = D_800C52F0[id] + 1;
        anim->unk210[1] = D_800C52F0[id] + 1;
        anim->unk30 = 0;
        anim->unk34 = 0;
    }
}
void func_1505E060(struct_eu_anim *arg0) {
    arg0->unk6 = arg0->unk4;
    arg0->unkC = arg0->unk8;
    arg0->unk14 = arg0->unk10;
    arg0->unk24 = arg0->unk20;
    arg0->unk1C = arg0->unk18;
    arg0->unk39 = arg0->unk38;
    arg0->unk2C = arg0->unk28;
    bcopy(arg0->unk40, arg0->unk210, 0x1D0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
#ifdef NON_MATCHING
/* P38: start animation `anim` of an object (+4 = type): skipped when the cutscene flag D_800C3638 is set and
 * D_800C3A78 is clear or func_15022A8C(obj) says so, for type 0xFF, a type without animations (D_800C5A90[type] == 0),
 * no model (+0x2D0) or anim out of range. No table D_800D1588[type] or an entry id >= 30000: func_1505DFDC(obj).
 * Entry id 999 (or table[0] == 999): nothing. Else func_1505E0C4(obj, &table[anim], model, 0, 0, anim, 0, speed,
 * arg3 (0 unless +0x2FF), arg4, arg5, arg6). */
void func_1505E650(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    u8 *obj = (u8 *) arg0;
    s32 type = obj[4];
    s32 anim = arg1;
    s32 n;
    s32 model;
    u16 *tbl;
    u16 *e;

    if (D_800C3638 != 0) {
        if (D_800C3A78 == 0) {
            return;
        }
        if (func_15022A8C(arg0) != 0) {
            return;
        }
    }
    if (obj[4] == 0xFF) {
        return;
    }
    n = (u16) D_800C5A90[obj[4]];
    if (n == 0) {
        return;
    }
    model = *(s32 *) (obj + 0x2D0);
    if (model == 0) {
        return;
    }
    if (anim >= n) {
        return;
    }
    tbl = (u16 *) D_800D1588[type];
    if (tbl == NULL) {
        func_1505DFDC(arg0);
        return;
    }
    if (anim >= (u16) D_800C5A90[type]) {
        return;
    }
    if (tbl[0] == 999) {
        return;
    }
    e = tbl + anim * 4;
    if (*e == 999) {
        return;
    }
    if (*e >= 30000) {
        func_1505DFDC(arg0);
        return;
    }
    if (obj[0x2FF] == 0) {
        arg3 = 0.0f;
    }
    func_1505E0C4(arg0, (s32) e, (u8 *) model, 0, 0, anim, 0, arg2, arg3, arg4, arg5, arg6);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
#endif
u32 func_1505E7CC(s32 arg0, struct127 *arg1)
{
  s32 temp_v1;
  u32 temp_v0_2;
  u32 var_v1;
  u8 *temp_a0;
  u8 *var_a1;
  u8 temp_v0;
  temp_v0 = arg1->id;
  if (temp_v0 == 0xFF)
  {
    return 0U;
  }
  temp_v1 = D_800D1588[temp_v0];
  if (temp_v1 == 0)
  {
    return 0U;
  }
  temp_v0_2 = *((u32 *) (((u8 *) temp_v1) + (-4)));
  if (temp_v0_2 == 0)
  {
    return 0U;
  }
  temp_v0_2 = temp_v0_2 / 24U;
  temp_a0 = *((u8 **) (((u8 *) temp_v1) + (-8)));
  if (temp_a0 == 0)
  {
    return 0U;
  }
  var_v1 = 0;
  if (temp_v0_2 != 0)
  {
    var_a1 = temp_a0;
    loop_10:
    if (arg0 == (*var_a1))
    {
      return var_v1;
    }
    var_v1 += 1;
    var_a1 += 0x18;
    if (var_v1 < temp_v0_2)
    {
      goto loop_10;
    }
  }
  return 0U;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E874.s")
#ifdef NON_MATCHING
extern s32 D_800CC8C4;

struct127 *func_1505ED34(void) {
    s32 sp1C;
    struct127 *sp18;
    s32 var_v0;
    struct127 *var_a0;

    var_v0 = 0;
    var_a0 = D_800CC2D0;
    if (D_800CC2D0->interaction_state != 0) {
loop_1:
        var_v0 += 1;
        var_a0 = (struct127 *)((u8 *)var_a0 + (0x32C));
        if (var_v0 < 0x19) {
            if (var_a0->interaction_state != 0) {
                goto loop_1;
            }
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = D_800CC2D0;
        var_v0 = 0;
        if ((D_800CC2D0->interaction_state != 0x27) || (D_800CC8C4 != 0)) {
loop_6:
            var_v0 += 1;
            var_a0 = (struct127 *)((u8 *)var_a0 + (0x32C));
            if (var_v0 < 0x19) {
                if ((var_a0->interaction_state != 0x27) || (var_a0->unk1D4 != NULL)) {
                    goto loop_6;
                }
            }
        }
        if ((var_v0 != 0x19) && (var_a0->interaction_state != 0)) {
            sp1C = var_v0;
            sp18 = var_a0;
            func_15060F28(var_a0, 0);
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = D_800CC2D0;
        var_v0 = 0;
        if (D_800CC2D0->interaction_state != 0x27) {
loop_14:
            var_v0 += 1;
            var_a0 = (struct127 *)((u8 *)var_a0 + (0x32C));
            if (var_v0 < 0x19) {
                if (var_a0->interaction_state != 0x27) {
                    goto loop_14;
                }
            }
        }
        if ((var_v0 != 0x19) && (var_a0->interaction_state != 0)) {
            sp1C = var_v0;
            sp18 = var_a0;
            func_15060F28(var_a0, 0);
        }
    }
    if ((var_v0 == 0x19) && (var_a0->interaction_state != 0)) {
        sp18 = var_a0;
        func_15060F28(var_a0, 0);
    }
    sp18 = var_a0;
    func_1505F188(var_a0);
    return sp18;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505ED34.s")
#endif
struct127 *func_1505EEB0(s32 state, s32 *arg1) {
    struct127 *tmp;
    s32 i;

    for (tmp = D_800CC2D0, i = 0; i < 25 && state != tmp->interaction_state; tmp++, i++) {
    }
    *arg1 = i;
    return tmp;
}

struct127 *func_1505EEF4(s32 arg0) {
    s32 i;
    struct127 *p = D_800CC2D0;
    for (i = 0; i < 25; i++) {
        if (p->interaction_state != 0 && p->unk13F == arg0) {
            return p;
        }
        p++;
    }
    return NULL;
}
struct127 *func_1505EFD0(s32 arg0) {
    s32 i;
    struct127 *p = D_800CC2D0;
    for (i = 0; i < 25; i++) {
        if (p->interaction_state != 0 && p->unk127 == arg0) {
            return p;
        }
        p++;
    }
    return NULL;
}
struct127 *func_1505F0AC(s32 arg0) {
    s32 i;
    struct127 *p = D_800CC2D0;
    for (i = 0; i < 25; i++) {
        if (p->interaction_state != 0 && p->id == arg0) {
            return p;
        }
        p++;
    }
    return NULL;
}
#ifdef NON_MATCHING
void func_1505F188(struct127 *arg0) {
    struct127 *temp_v1;
    struct127 *var_v0;

    temp_v1 = ((struct127 *)((u8 *)arg0 + 0x32C));
    var_v0 = arg0;
    if ((u32) arg0 < (u32) temp_v1) {
        do {
            var_v0 = (struct127 *)((u8 *)var_v0 + (4));
            (*(s32 *)((u8 *)var_v0 + -4)) = 0;
        } while ((u32) var_v0 < (u32) temp_v1);
    }
    arg0->unk2FD = 2;
    (*(s16 *)((u8 *)arg0 + 0x38)) = -0x2710;
    arg0->xz_scale = 1.0f;
    arg0->y_scale = 1.0f;
    arg0->unk118 = -10000.0f;
    arg0->unk180 = -10000.0f;
    arg0->unk1DC = 0xFF;
    arg0->unk127 = 0xFF;
    arg0->unk84.uh = 0xFFFF;
    arg0->unk13F = 0xFF;
    arg0->unk2C4 = (s32) &arg0->id;
    arg0->unk2C8 = 1;
    arg0->unk2C9 = 1;
    arg0->id = 0xFF;
    arg0->unk2CB = 0x32;
    arg0->unk48 = 1.0f;
    arg0->gravity = 3.3f;
    arg0->unk6E = (func_150ADA20() % 50U) + 0x32;
    func_150615DC(arg0);
    arg0->unk1DD = 0xFF;
    arg0->unk1DE = 0xFF;
    arg0->unk1DF = 0xFF;
    (*(s16 *)((u8 *)arg0 + 0x18C)) = 0;
    (*(s16 *)((u8 *)arg0 + 0x18E)) = 0;
    arg0->unk190 = 0;
    arg0->unk192 = 0;
    arg0->unk194 = 0;
    (*(s16 *)((u8 *)arg0 + 0x196)) = 0xA;
    (*(s16 *)((u8 *)arg0 + 0x198)) = 0xA;
    (*(s16 *)((u8 *)arg0 + 0x19A)) = 0;
    arg0->unk19C = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F188.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F298.s")
#ifdef NON_MATCHING
s32 func_15064668(struct127 *, s32, s32, s32, s32);
s32 func_15065E18(struct127 *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15080B38(u8);
extern s32 D_800CC3C8;
extern u16 *D_800CC6A4;

void func_1506045C(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp4C;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 var_t1;
    s32 var_t2;
    s32 var_t4;
    struct126 *temp_v1;
    struct126 *temp_v1_2;
    u16 temp_v0;
    u8 temp_a0;
    u8 temp_t0;
    u8 temp_t8;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 var_s0;

    var_t4 = 0;
    if (D_800C35EA != 1) {
        sp40 = 0;
        temp_v1 = arg0->unk31C;
        var_t1 = 0;
        var_t2 = 0;
        temp_v0 = (*(u16 *)((u8 *)temp_v1 + 0x72));
        if ((temp_v0 != 0) && (arg4 == 0)) {
            if (D_800BE9E4 < (s32) temp_v0) {
                (*(u16 *)((u8 *)temp_v1 + 0x72)) = (u16) (temp_v0 - D_800BE9E4);
            } else {
                (*(u16 *)((u8 *)temp_v1 + 0x72)) = 0U;
                var_t2 = 1;
            }
        }
        temp_v0_2 = arg0->unk31C->pad79[3];
        temp_t8 = arg0->unk31C->unk75 & ~0x80;
        var_s0 = temp_t8;
        if ((temp_v0_2 != 0) && (temp_t8 == 0)) {
            var_s0 = temp_v0_2;
        }
        if ((D_800BE9F0 != 0x29) && (D_800BE9F0 != 0x2E) && (arg0->unk31C->unk78 == 0) && (*D_800CC6A4 & 0x20)) {
            sp4C = 0;
            sp44 = var_t2;
            sp3C = 0;
            var_t1 = 0;
            var_t4 = 0;
            if (func_15080B38(var_s0) != 0) {
                var_s0 = 0x1A;
            }
        }
        temp_v1_2 = arg0->unk31C;
        temp_t0 = temp_v1_2->unk78;
        if (temp_t0 == 0x1A) {
            var_s0 = 0x1A;
        }
        if (temp_t0 == 0x2A) {
            var_s0 = 0x2A;
        }
        if ((arg0->unk13C != 0) || (arg0->unk137 != 0)) {
            if (arg4 == 0) {
                var_s0 = 0;
            } else {
                sp40 = 1;
            }
        }
        temp_a0 = arg0->unk65;
        if ((temp_a0 != 0) && (arg4 == 0)) {
            temp_v0_3 = *(s32 *)((u8 *)&D_800CC3C8 + (temp_a0 * 0x32C));
            if (temp_v0_3 != 0xC) {
                if (temp_v0_3 != 0x23) {
                    var_s0 = 0;
                    if (temp_v0_3 != 0x28) {
                        if (temp_v0_3 != 0x8A) {
                            var_s0 = 0xE;
                        } else {
                            goto block_32;
                        }
                    }
                } else {
block_32:
                    var_s0 = 0x1B;
                }
            } else {
                var_s0 = 8;
            }
        }
        if (temp_v1_2->pad17[0] != 0) {
            var_s0 = 0x3C;
        }
        if ((arg4 == 0) && (temp_t0 != 0) && (var_s0 != (temp_t0 & ~0x80))) {
            sp38 = (s32) temp_v1_2->unk75;
            temp_v1_2->unk75 = temp_t0;
            sp3C = 0;
            sp44 = var_t2;
            sp4C = 0;
            func_1506045C(arg0, arg1, arg2, arg3, 1);
            var_t1 = 0;
            var_t4 = 0;
            arg0->unk31C->unk75 = (u8) sp38;
            arg0->unk31C->unk78 = 0;
        }
        if (arg0->stunned != 0) {
            var_t1 = 1;
            arg2 = 0;
            arg1 = 0;
        }
        if ((var_s0 != 0) && (arg0->unk31C->unk4E == 0)) {
            var_t4 = func_15065E18(arg0, arg1, arg2, arg3, arg4, (s32) var_s0, var_t1, var_t2, sp40);
        }
        if ((arg0->unk31C->pad79[2] != 0) || (arg2 & 0x4000)) {
            func_15064668(arg0, arg2, arg3, sp40, var_t4);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506045C.s")
#endif
#ifdef NON_MATCHING
void func_15060778(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 sp54;
    u16 *sp4C;
    s32 sp44;
    s32 temp_a0;
    s32 temp_t2;
    s32 var_a0;
    s32 var_t0;
    u16 *var_t1;
    u16 temp_v1;
    u16 var_v0;

    var_t1 = NULL;
    if (arg6 & 8) {
        var_t0 = 0;
    } else {
        var_t0 = ((u32) arg1->unk184 >> 3) & 0x30;
    }
    temp_t2 = arg6 & 3;
    switch (temp_t2) {                              /* irregular */
    default:
        var_a0 = 0 & 0xFFFF;
block_15:
        if (arg6 & 4) {
            sp4C = var_t1;
            var_v0 = func_10010E78((u16) var_a0, arg0, (arg2 + (var_t0 * 0x32)) & 0xFFFF, (s16) arg3, (u8) var_t0, 0, (s16) (s32) arg1->x_position, (s16) (s32) arg1->y_position, (s16) (s32) arg1->z_position, (s16) arg4, (s16) arg5);
        } else {
            sp4C = var_t1;
            var_v0 = func_10010BE8((u16) var_a0, arg0, (arg2 + (var_t0 * 0x32)) & 0xFFFF, 0x40U, (s16) arg3, (u8) var_t0, 1U);
        }
        if (sp4C != NULL) {
            *sp4C = var_v0;
        }
        return;
    case 1:
        var_t1 = &arg1->unk8C;
        var_a0 = (s32) arg1->unk8C;
        goto block_15;
    case 2:
    case 3:
        var_t1 = &arg1->unk8E;
        temp_v1 = arg1->unk8E;
        if (temp_t2 == 2) {
            var_a0 = temp_v1 & 0xFFFF;
            goto block_15;
        }
        temp_a0 = temp_v1 & 0xFFFF;
        sp44 = temp_a0;
        sp54 = var_t0;
        sp4C = var_t1;
        var_a0 = temp_a0;
        if ((func_1001147C((u16) temp_a0) == arg0) & 0x7FFF) {
            if (arg6 & 4) {
                func_1000F91C((u16) var_a0, (arg2 + (var_t0 * 0x32)) & 0xFFFF, (s16) ((arg1->unk13F * 0xA) + arg3), var_t0 & 0xFF, 0, (s16) (s32) arg1->x_position, (s16) (s32) arg1->y_position, (s16) (s32) arg1->z_position, (s16) arg4, (s16) arg5);
                return;
            }
            sp44 = var_a0;
            sp54 = var_t0;
            func_1000F85C((u16) var_a0, 0x10, arg3);
            func_1000F85C((u16) var_a0, 8, arg2 + (var_t0 * 0x32));
            return;
        }
        arg0 |= 0x8000;
        goto block_15;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060778.s")
#endif
void func_15060A30(s32 arg0, struct127 *arg1) {
    if (arg1->camera == NULL) {
        func_10010344(arg0, arg1, 28000, 500, 2500);
    } else {
        func_15060778(arg0, arg1, 24000, 0, 500, 2500, 1);
    }
}
void func_15060A9C(s32 arg0, struct127 *arg1) {
    if (arg1->camera == NULL) {
        func_10010630(arg0, arg1, 24000, 500, 2500);
    } else {
        func_15060778(arg0, arg1, 24000, 0, 500, 2500, 0);
    }
}

void func_15060B04(s32 arg0, struct127 *arg1, s32 arg2) {
    if (arg1->camera == NULL) {
        func_10010630(arg0, arg1, arg2, 500, 2500);
    } else {
        func_15060778(arg0, arg1, arg2, 0, 500, 2500, 0);
    }
}

void func_15060B70(s32 arg0, void *arg1) {
    func_10010154(arg0, arg1, 0x6D60, 0x1F4, 0x9C4);
}

s32 func_15060BA4(struct127 *arg0, s32 arg1) {
    if (arg0->health == 6) {
        return 0;
    }
    arg0->health += arg1;
    if (arg0->health >= 7) {
        arg0->health = 6;
    }
    return 1;
}
#ifdef NON_MATCHING
void func_15060BE0(u8 *arg0) {
    f32 sp4;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f18;
    f32 var_f2;
    s32 temp_a1;
    s32 var_v0;
    struct124 *temp_v0;
    u8 temp_v1;
    u8 *temp_a2;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 4));
    var_v0 = 0;
    if (temp_v1 != 0xFF) {
        temp_a1 = (*(s32 *)((u8 *)arg0 + 0x1D4));
        if ((temp_a1 != 0) && (D_800C42B0 == 0)) {
            temp_v0 = D_800D1C90[temp_v1];
            temp_a2 = temp_a1 + ((*(u8 *)((u8 *)temp_v0 + 0x27)) << 6);
            temp_f2 = (f32) (*(s16 *)((u8 *)temp_v0 + 0x14)) * (*(f32 *)((u8 *)arg0 + 0x150));
            if (temp_f2 != 0.0f) {
                temp_f12 = (*(f32 *)((u8 *)temp_a2 + 0x10));
                temp_f14 = (*(f32 *)((u8 *)temp_a2 + 0x14));
                temp_f16 = (*(f32 *)((u8 *)temp_a2 + 0x18));
                temp_f0 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16));
                var_f18 = temp_f0;
                if (temp_f0 != 0.0f) {
                    var_f18 = temp_f2 / temp_f0;
                }
                var_f0 = temp_f12 * var_f18;
                var_f2 = temp_f14 * var_f18;
                sp4 = temp_f16 * var_f18;
            } else {
                var_f0 = 0.0f;
                sp4 = 0.0f;
                var_f2 = 0.0f;
            }
            var_v0 = 1;
            (*(s16 *)((u8 *)arg0 + 0x1BC)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a2 + 0x30)) + var_f0);
            (*(s16 *)((u8 *)arg0 + 0x1BE)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a2 + 0x34)) + var_f2);
            (*(s16 *)((u8 *)arg0 + 0x1C0)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a2 + 0x38)) + sp4);
        }
    }
    if (var_v0 == 0) {
        (*(s16 *)((u8 *)arg0 + 0x1BC)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14));
        (*(s16 *)((u8 *)arg0 + 0x1BE)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18));
        (*(s16 *)((u8 *)arg0 + 0x1C0)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060BE0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060D54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060F28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")

// TODO: is this really struct127?
void func_150615DC(struct127 *arg0) {
    arg0->unk7 = 0xFF;
    arg0->unk8 = 0xFF;
    arg0->unk9 = 0;
    arg0->unkA = 0;
    arg0->unkE.ub[1] = 0;
    arg0->unkB = arg0->unkC = arg0->unkD = arg0->unkE.ub[0] = 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150617BC.s")
// ???
s32 func_1506196C(struct127 *arg0, s32 arg1) {
    s32 v = (&arg0->unkB)[arg1] * arg0->unk7;

    if (v == 0xFE01) {
        v = 0xFF;
    } else {
        v = v >> 8;
    }
    return v;
}

#ifdef NON_MATCHING
s32 func_150617BC(struct127 *);
s32 func_150623F4(struct127 *);

void func_150619A8(void) {
    struct {
        u8 u5C;
    } sp;
    s32 var_s0_2;
    s32 var_s4_2;
    s32 var_s6;
    struct127 *temp_s3;
    struct127 *temp_v0_2;
    struct127 *var_s0;
    struct127 *var_s1;
    u8 *var_s5;
    u8 temp_a0;
    u8 temp_v0;
    u8 var_s4;

    var_s6 = 0;
    var_s0 = D_800CC2D0;
    var_s4 = 0;
    do {
        if (var_s0->interaction_state != 0) {
            temp_v0 = var_s0->unk2FD;
            if (temp_v0 != 0) {
                var_s0->unk2FD = temp_v0 - 1;
            }
            func_150617BC(var_s0);
            if (func_150623F4(var_s0) != 0) {
                var_s0->unk2FA |= 1;
            } else {
                var_s0->unk2FA &= ~1;
                if ((var_s0->unk20B != 0) || (var_s0->unk20C != 0) || (var_s0->unk20D != 0) || (var_s0->unk20E != 0)) {
                    (&sp.u5C)[var_s6] = var_s4;
                    var_s6 += 1;
                }
            }
        }
        var_s4 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while ((s32) var_s4 < 0x19);
    if (var_s6 != 0) {
        var_s4_2 = 0;
        if (var_s6 > 0) {
            var_s5 = &sp.u5C;
            do {
                temp_s3 = &D_800CC2D0[*var_s5];
                var_s1 = temp_s3;
                var_s0_2 = 0;
loop_16:
                temp_a0 = var_s1->unk20B;
                if ((temp_a0 != 0) && (temp_v0_2 = func_15083E90(temp_a0), (temp_v0_2 != NULL)) && (temp_v0_2->unk2FA & 1)) {
                    temp_s3->unk2FA |= 1;
                } else {
                    var_s0_2 += 1;
                    var_s1 = (struct127 *)((u8 *)var_s1 + (1));
                    if (var_s0_2 != 4) {
                        goto loop_16;
                    }
                }
                var_s4_2 += 1;
                var_s5 += 1;
            } while (var_s4_2 != var_s6);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150619A8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
#ifdef NON_MATCHING
s32 func_15022A8C(struct127 *);
s32 func_150A6840(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern s32 D_800DA030;

s32 func_150623F4(struct127 *arg0) {
    s32 sp54;
    s32 sp4C;
    s32 *var_s1;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f22;
    s32 temp_t9;
    s32 var_a0;
    s32 var_s0;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    struct127 *var_v0_2;
    struct127 *var_v0_3;
    struct129 *temp_v0;
    u16 temp_t6;
    u16 temp_t7;
    u8 temp_a2;
    u8 temp_t1;

    temp_v0 = arg0->unk144;
    if (temp_v0 != NULL) {
        temp_t6 = (*(u16 *)((u8 *)temp_v0 + 0x2A));
        var_f22 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f22 += 4294967296.0f;
        }
    } else {
        var_f22 = 0.0f;
    }
    if (var_f22 == 0.0f) {
        return 1;
    }
    if (arg0->unk127 != 0xFF) {
        return 1;
    }
    if ((D_800C3638 != 0) && (func_15022A8C(arg0) != 0)) {
        return 1;
    }
    if (arg0->interaction_state == 0x27) {
        return 1;
    }
    var_a0 = 0;
    var_v0_2 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_t1 = var_v0_2->unkB;
            var_v0_2 += 1;
            var_a0 += temp_t1;
        } while ((u32) (D_80082FA0 + arg0) >= (u32) var_v0_2);
    }
    if (var_a0 == 0) {
        return 0;
    }
    if ((arg0->unk74 & 0xF) != 0xF) {
        return 1;
    }
    temp_a2 = arg0->unk13F;
    if (D_800D2528[temp_a2] != 0) {
        var_t0 = 1;
        var_v1 = 0;
        if (D_8008FD8C > 0) {
            temp_t9 = D_800D2104[temp_a2];
            var_v0_3 = D_800CC2D0;
            temp_t7 = (*(u16 *)((u8 *)temp_t9 + 6));
loop_22:
            var_v1 += 1;
            temp_f0 = (f32) (*(s16 *)((u8 *)temp_t9 + 0)) - var_v0_3->x_position;
            temp_f2 = (f32) (*(s16 *)((u8 *)temp_t9 + 4)) - var_v0_3->z_position;
            if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) < (f32) (temp_t7 * temp_t7)) {
                var_t0 = 0;
            } else {
                var_v0_3 += 0x32C;
                if (var_v1 < D_8008FD8C) {
                    goto loop_22;
                }
            }
        }
        sp4C = var_t0;
        if (var_t0 == 0) {
            return 1;
        }
        goto block_27;
    }
block_27:
    var_t0_2 = sp4C;
    var_s1 = &D_800DA030;
    var_v1_2 = 0;
    var_s0 = 0;
    temp_f20 = (f32) (*(s16 *)((u8 *)(D_800D1C90[arg0->id]) + 0x10)) * arg0->y_scale;
    if (D_80082FA0 >= 0) {
        sp4C = 1;
loop_29:
        sp54 = var_v1_2;
        if (func_150A6840(var_s0 + D_800BE628, var_s1, arg0->x_position, arg0->y_position + temp_f20, arg0->z_position, var_f22, var_f22, 20000.0f) != 0) {
            sp4C = 0;
            var_t0_2 = 0;
        } else {
            var_v1_2 += 1;
            var_s0 += 0x180;
            var_s1 += 0x40;
            if (D_80082FA0 < var_v1_2) {
                var_t0_2 = sp4C;
            } else {
                goto loop_29;
            }
        }
    }
    var_v0 = 0;
    if (var_t0_2 == 0) {
        var_v0 = 1;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150623F4.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")

void func_150627D4(struct127 *arg0) {
    arg0->unk2FB = 0;
    func_1503B840(arg0);
    func_15039CC8(arg0);
}
