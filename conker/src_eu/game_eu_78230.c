#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 *D_800CC6A4;
s32 func_1504C8BC(struct127 *);
void func_1504C0E8(struct127 *arg0, s32 arg1, f32 arg2);
#endif


f32 func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
s32 func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);

#ifdef NON_MATCHING
/* P38: per-frame object update (UNVERIFIED parts: see P38.md) */
void func_1504AF10(struct127 *, s32, s32);
void func_15061B4C(void);
void func_1507D4F8(s32); /* P59: void in the NM definition */
void func_1507EB1C(struct127 *);
void func_15081064(void);
void func_15082D5C(s32, s32, s32);
void func_150A16A4(struct127 *);
s32 func_150A2C6C(struct127 *);
extern s32 D_800863A4;
extern s32 D_800863AC;
extern u16 D_8009015C;
extern s8 D_800BEE0C;
extern s32 D_800CC1C0;
extern s32 D_800CC670;
extern u8 D_800CC69C;
extern s32 D_800CC6A0;
extern s32 D_800CC6DC;
extern s32 D_800D1968;
extern u8 D_800D39FC;
extern s32 D_800DC3C4;

void func_1504A730(void) {
    s32 sp5C[2];
    f32 temp_f0;
    f32 temp_f18;
    f32 var_f0;
    f32 var_f20;
    s32 temp_v0;
    s32 var_s3;
    s32 var_t0;
    s8 var_v1;
    struct108 *temp_v0_4;
    struct126 *temp_a0;
    struct126 *temp_v0_2;
    struct126 *temp_v0_3;
    struct127 *var_a1;
    struct127 *var_s0;
    u16 *temp_a2;
    u16 temp_a3;
    u8 temp_v0_5;
    u8 temp_v0_7;
    u8 temp_v0_9;
    u8 var_s1;
    u8 var_s2;
    void (*temp_v0_6)(struct127 *);
    u8 *temp_v1;

    D_800BEE0C = 0;
    D_800D1968 += 1;
    D_800CC670 += D_800BE9A0;
    D_800C3E78 = 0;
    D_800CC6DC = 0;
    func_15082D5C(D_800BE9F0, 0, 0);
    D_800CC6D8 ^= 1;
    var_s0 = D_800CC2D0;
    var_s1 = 0;
    do {
        if (var_s0->interaction_state == 0) {
            var_s2 = var_s1 + 1;
        } else {
            var_s0->unk274 = 0;
            var_s0->unk300 = 0;
            var_s0->unkF4 &= 0xFFEE5FFF;
            D_800C3E78 = var_s1;
            if (var_s0->y_position <= (f32) (*(s16 *)((u8 *)var_s0 + 0x38))) {
                if (var_s0->unk127 == 0xFF) {
                    func_15060F28(var_s0, 0);
                    var_s2 = var_s1 + 1;
                } else if (D_800BE616 == 0) {
                    func_1507D4F8(var_s1);
                    var_s2 = var_s1 + 1;
                } else {
                    goto block_8;
                }
            } else {
block_8:
                if (var_s0->unk2FA == 0) {
                    var_s2 = var_s1 + 1;
                } else {
                    D_800D154C = var_s0;
                    var_s2 = var_s1 + 1;
                    (*(u16 *)((u8 *)var_s0 + 0x12)) = (u16) ((*(u16 *)((u8 *)var_s0 + 0x12)) + 1);
                    D_800D39FC = var_s2;
                    D_800CC6DA = 0;
                    var_s3 = 0;
                    if ((D_800BE616 == 0) || (temp_v0 = func_1504C8BC(var_s0), var_s3 = temp_v0, (temp_v0 != 0))) {
                        var_f20 = 2.0f;
                        if ((s32) var_s1 < D_8008FD8C) {
                            temp_v0_2 = var_s0->unk31C;
                            temp_v0_2->unk195 = (s8) temp_v0_2->unk195 - D_800BE9E4;
                            temp_v0_3 = var_s0->unk31C;
                            if ((s8) temp_v0_3->unk195 < 0) {
                                temp_v0_3->unk195 = 0;
                            }
                            var_s0->unk31C->unk57 = 0;
                            if ((s32) var_s1 < 4) {
                                D_800CC6A4 = (u8 *) ((s32 *) D_800BE728[0])[var_s1];
                            } else {
                                bzero(sp5C, 6);
                                D_800CC6A4 = (u8 *) sp5C;
                            }
                        }
                        temp_v0_4 = var_s0->camera;
                        if (temp_v0_4 != NULL) {
                            temp_f0 = temp_v0_4->unk384;
                            if (temp_f0 == 999.0f) {
                                D_800CC6A0 = (s32) (temp_v0_4->unk37C * 182.04445f);
                            } else {
                                D_800CC6A0 = (s32) (temp_f0 * 182.04445f);
                            }
                        } else {
                            D_800CC6A0 = 0;
                        }
                        if (var_s0->unk127 != 0xFF) {
                            func_150A16A4(var_s0);
                        } else if (var_s0->unkF8 & 0x400000) {
                            func_150A2C6C(var_s0);
                        }
                        var_s0->old_x_position = var_s0->x_position;
                        var_s0->old_y_position = var_s0->y_position;
                        var_s0->old_z_position = var_s0->z_position;
                        D_800CC69C = ((u32) var_s0->unk184 >> 0x1C) & 7;
                        var_f0 = D_800BE9A4;
                        if ((D_800BE616 != 0) && (D_8009015C & 0x100)) {
                            var_f20 = 5.0f;
                        }
                        if (var_f20 < var_f0) {
                            var_f0 = var_f20;
                        }
                        temp_f18 = var_s0->unk48 * var_f0 * 1.2f;
                        *D_800D1550 = temp_f18;
                        D_800CC264 = (s16) (s32) (temp_f18 * 100.0f);
                        if ((s32) D_800CC69C >= 6) {
                            D_800CC69C = 0;
                        }
                        temp_v0_5 = D_800B0DF0->unk49;
                        if (temp_v0_5 != 0) {
                            ((void (**)(struct127 *)) &D_800863A4)[temp_v0_5](var_s0);
                        }
                        if (!(var_s0->unk25C & 0x200)) {
                            temp_v0_6 = (void (*)(struct127 *)) D_800863B4[var_s0->interaction_state];
                            if (temp_v0_6 != NULL) {
                                temp_v0_6(var_s0);
                            }
                        }
                        if (var_s0->interaction_state != 0) {
                            func_1507EB1C(var_s0);
                            func_1504AF10(var_s0, 0, 0);
                            if (((s32) var_s1 < D_8008FD8C) && (D_800D18A8 == 0)) {
                                func_15085710((s16) var_s0->unk127, 5, (s32) var_s0->health);
                            }
                        }
                        var_s0->unk2FF = 1;
                        if (var_s3 == 2) {
                            D_800BE9E4 = (s32) (u16) D_800CC6DA;
                            D_800BE9A4 = (f32) (u16) D_800CC6DA * 0.5f;
                            if (D_800BE9A4 != 0.0f) {
                                D_800BEDC8 = 1.0f / D_800BE9A4;
                            } else {
                                D_800BEDC8 = 0.0f;
                            }
                        }
                        if ((var_s0->x_position != var_s0->old_x_position) || (var_s0->y_position != var_s0->old_y_position) || (var_s0->z_position != var_s0->old_z_position)) {
                            var_s0->unk300 = 1;
                        }
                        temp_v0_7 = D_800B0DF0->unk4A;
                        if (temp_v0_7 != 0) {
                            ((void (**)(struct127 *)) &D_800863AC)[temp_v0_7](var_s0);
                        }
                    }
                }
            }
        }
        var_s1 = var_s2;
        var_s0++;
    } while (var_s2 != 0x19);
    var_v1 = D_8008FD8C;
    var_a1 = D_800CC2D0;
    var_t0 = 0;
    if (var_v1 > 0) {
        do {
            if (var_a1->interaction_state != 0) {
                temp_a0 = var_a1->unk31C;
                if (temp_a0 != NULL) {
                    temp_a2 = (u16 *) &D_800CC1C0 + var_t0;
                    if (var_a1->unk137 != 0) {
                        temp_a3 = *temp_a2;
                        if (temp_a3 != 0) {
                            temp_v1 = (u8 *) D_800DBEF4 + temp_a3 * 0xA0;
                            temp_v1[-0x51] |= 0x84;
                            ((s32 *) D_800DC3C4)[*temp_a2 - 1] |= 1 << var_t0;
                        }
                        var_a1->unk31C->pad56 = 5;
                        goto block_64;
                    }
                    temp_v0_9 = temp_a0->pad56;
                    if (temp_v0_9 != 0) {
                        temp_a0->pad56 = temp_v0_9 - 1;
block_64:
                        var_v1 = D_8008FD8C;
                    }
                }
            }
            var_t0 += 1;
            var_a1++;
        } while (var_t0 < var_v1);
    }
    func_15061B4C();
    func_15081064();
    D_800D154C = D_800CC2D0;
    D_800C3E78 = 0;
    D_800D39FC = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504A730.s")
#endif
// void func_1504A730(void) {
//     u8 sp5C[6];
//     f32 temp_f0;
//     f32 temp_f0_2;
//     f32 temp_f0_3;
//     s32 temp_t0;
//     s32 temp_v0;
//     s8 temp_s2;
//     s8 temp_v1;
//     u16 temp_a3;
//     u16 temp_t8;
//     u8 temp_v0_5;
//     u8 temp_v0_7;
//     u8 temp_v0_9;
//     void *temp_a0;
//     void *temp_a2;
//     struct126 *temp_v0_2;
//     struct126 *temp_v0_3;
//     struct108 *temp_v0_4;
//     void *temp_v0_6;
//     void *temp_v0_8;
//     void *temp_v1_2;
//     struct127 *phi_s0;
//     s32 phi_s1;
//     f32 phi_f20;
//     f32 phi_f0;
//     s32 phi_s3;
//     s8 phi_s2;
//     void *phi_a1;
//     s32 phi_t0;
//     s32 phi_v1;
//
//     D_800BE9EC = (u8)0;
//     D_800D1548 += 1; //(s32) (D_800D1548 + 1);
//     D_800CC250 += D_800BE9A0; //(s32) (D_800CC250 + D_800BE9A0);
//     D_800C3E78 = (u8)0;
//     D_800CC2BC = 0;
//     func_1508295C(D_800BE9F0, 0, 0);
//     D_800CC2B8 ^= 1; //(u8) (D_800CC2B8 ^ 1);
//
//     // phi_s1 = (u8)0;
//     for (phi_s1 = 0; phi_s1 < 25; phi_s1++) {
//         phi_s0 = &D_800CC2D0[phi_s1];
//         if (phi_s0 == 0) {
//             phi_s2 = phi_s1 + 1;
//         } else {
//             phi_s0->unk274 = (u8)0;
//             phi_s0->unk300 = (u8)0;
//             phi_s0->unkF4 = (s32) (phi_s0->unkF4 & 0xFFEE5FFF);
//             D_800C3E78 = phi_s1;
//             if (phi_s0->y_position <= (f32) phi_s0->unk38) {
//                 if (phi_s0->unk127 == 0xFF) {
//                     func_15060F28(phi_s0, 0);
//                     phi_s2 = phi_s1 + 1;
//                 } else if (D_800BE616 == 0) {
//                     func_1507D4F8(phi_s1);
//                     phi_s2 = phi_s1 + 1;
//                 } else {
// block_8:
//                     if (phi_s0->unk2FA == 0) {
//                         phi_s2 = phi_s1 + 1;
//                     } else {
//                         D_800D154C = phi_s0;
//                         temp_s2 = phi_s1 + 1;
//                         phi_s0->unk12 += 1; // (u16) (phi_s0->unk12 + 1);
//                         D_800D35DC = temp_s2;
//                         D_800CC2BA = (u16)0;
//                         phi_s3 = 0;
//                         if ((D_800BE616 == 0) || (temp_v0 = func_1504C8BC(phi_s0), phi_s3 = temp_v0, phi_s2 = temp_s2, (temp_v0 != 0))) {
//                             if ((s32) phi_s1 < (s32) D_8008FD8C) {
//                                 temp_v0_2 = phi_s0->unk31C;
//                                 temp_v0_2->unk195 = (s8) (temp_v0_2->unk195 - D_800BE9E4);
//                                 temp_v0_3 = phi_s0->unk31C;
//                                 if ((s32) temp_v0_3->unk195 < 0) {
//                                     temp_v0_3->unk195 = (u8)0;
//                                 }
//                                 phi_s0->unk31C->unk57 = (u8)0;
//                                 if ((s32) phi_s1 < 4) {
//                                     D_800CC284 = (s32) D_800BE728[phi_s1]; // * 4));
//                                 } else {
//                                     bzero(&sp5C, 6);
//                                     D_800CC284 = &sp5C;
//                                 }
//                             }
//                             temp_v0_4 = phi_s0->camera;
//                             if (temp_v0_4 != 0) {
//                                 temp_f0 = temp_v0_4->unk384;
//                                 if (D_800991A8 == temp_f0) {
//                                     D_800CC280 = (s32) (temp_v0_4->unk37C * D_800991AC);
//                                 } else {
//                                     D_800CC280 = (s32) (temp_f0 * D_800991B0);
//                                 }
//                             } else {
//                                 D_800CC280 = 0;
//                             }
//                             if (phi_s0->unk127 != 0xFF) {
//                                 func_150A11C4(phi_s0);
//                             } else if (phi_s0->unkF8 & 0x400000) {
//                                 func_150A278C(phi_s0);
//                             }
//                             phi_s0->unk2C = (f32) phi_s0->unk14;
//                             phi_s0->unk30 = (f32) phi_s0->y_position;
//                             phi_s0->unk34 = (f32) phi_s0->unk1C;
//                             D_800CC27C = (s8) (((u32) phi_s0->unk184 >> 0x1C) & 7);
//                             temp_f0_2 = D_800BE9A4;
//                             phi_f20 = 2.0f;
//                             if (D_800BE616 != 0) {
//                                 phi_f20 = 2.0f;
//                                 if ((D_8008FDBC & 0x100) != 0) {
//                                     phi_f20 = 5.0f;
//                                 }
//                             }
//                             phi_f0 = temp_f0_2;
//                             if (phi_f20 < temp_f0_2) {
//                                 phi_f0 = phi_f20;
//                             }
//                             D_800D1550[0] = (f32) (phi_s0->unk48 * phi_f0);
//                             D_800CC264 = (s16) (s32) (D_800D1550[1364] * 100.0f); // wtf?
//                             if ((s32) D_800CC27C >= 6) {
//                                 D_800CC27C = (u8)0;
//                             }
//                             temp_v0_5 = (D_800B0DF0)->unk49;
//                             if (temp_v0_5 != 0) {
//                                 D_80086004[temp_v0_5](phi_s0);
//                             }
//                             if ((phi_s0->unk25C & 0x200) == 0) {
//                                 // temp_v0_6 = D_80086014[phi_s0->unk0];
//                                 if (D_80086014[phi_s0->unk0] != 0) {
//                                     D_80086014[phi_s0->unk0](phi_s0);
//                                 }
//                             }
//                             if (phi_s0->unk0 != 0) {
//                                 func_1507E73C(phi_s0);
//                                 func_1504AF10(phi_s0, 0, 0);
//                                 if (((s32) phi_s1 < (s32) D_8008FD8C) && (D_800D18A8 == 0)) {
//                                     func_15085710(phi_s0->unk127, 5, phi_s0->health);
//                                 }
//                             }
//                             phi_s0->unk2FF = (u8)1;
//                             if (phi_s3 == 2) {
//                                 temp_t8 = D_800CC2BA;
//                                 D_800BE9E4 = (s32) temp_t8;
//                                 D_800BE9A4 = (f32) ((f32) temp_t8 * 0.5f);
//                                 temp_f0_3 = D_800BE9A4;
//                                 if (temp_f0_3 != 0.0f) {
//                                     D_800BE9A8 = (f32) (1.0f / temp_f0_3);
//                                 } else {
//                                     D_800BE9A8 = 0.0f;
//                                 }
//                             }
//                             if ((phi_s0->unk14 != phi_s0->unk2C) || (phi_s0->unk18 != phi_s0->unk30) || (phi_s0->unk1C != phi_s0->unk34)) {
//                                 phi_s0->unk300 = (u8)1;
//                             }
//                             temp_v0_7 = (D_800B0DF0)->unk4A;
//                             phi_s2 = temp_s2;
//                             if (temp_v0_7 != 0) {
//                                 D_8008600C[temp_v0_7](phi_s0);
//                                 phi_s2 = temp_s2;
//                             }
//                         }
//                     }
//                 }
//             } else {
//                 goto block_8;
//             }
//         }
//     }
// //     temp_v1 = D_8008FD8C;
// //     if ((s32) temp_v1 > 0) {
// //         phi_a1 = &D_800CC2D0;
// //         phi_t0 = 0;
// //         phi_v1 = (s32) temp_v1;
// // loop_56:
// //         if (phi_a1->unk0 != 0) {
// //             temp_a0 = phi_a1->unk31C;
// //             if (temp_a0 != 0) {
// //                 temp_a2 = &D_800CBDA0 + (phi_t0 * 2);
// //                 if (phi_a1->unk137 != 0) {
// //                     temp_a3 = *temp_a2;
// //                     if (temp_a3 != 0) {
// //                         temp_v0_8 = D_800DBEF4 + (temp_a3 * 0xA0);
// //                         temp_v0_8->unk-51 = (u8) (temp_v0_8->unk-51 | 0x84);
// //                         temp_v1_2 = D_800DBF94 + (*temp_a2 * 4);
// //                         temp_v1_2->unk-4 = (s32) (temp_v1_2->unk-4 | (1 << phi_t0));
// //                     }
// //                     phi_a1->unk31C->unk56 = (u8)5;
// // block_64:
// //                     phi_v1 = (s32) D_8008FD8C;
// //                 } else {
// //                     temp_v0_9 = temp_a0->unk56;
// //                     if (temp_v0_9 != 0) {
// //                         temp_a0->unk56 = (u8) (temp_v0_9 - 1);
// //                         goto block_64;
// //                     }
// //                 }
// //             }
// //         }
// //         temp_t0 = phi_t0 + 1;
// //         phi_a1 = phi_a1 + 0x32C;
// //         phi_t0 = temp_t0;
// //         if (temp_t0 < phi_v1) {
// //             goto loop_56;
// //         }
// //     }
//     func_15061B4C();
//     func_15080C64();
//     D_800D154C = &D_800CC2D0;
//     D_800C3E78 = (u8)0;
//     D_800D35DC = (u8)0;
// }

#ifdef NON_MATCHING
/* Per-frame pass over the 25 object records outside cutscenes (D_800C35EA != 1): sets the current object
 * (D_800C3E78 index, D_800D154C pointer), its controller (D_800CC6A4: pad i of D_800BE728 for the first four
 * players, a zeroed 6-byte pad otherwise; only for i < D_8008FD8C) and runs func_150EDAF8 for objects 0x28 / 0x77.
 * As in the asm, the zeroed pad is a local of this function (D_800CC6A4 keeps pointing at it afterwards). */
void func_1504ADD0(void) {
    u8 pad[8];
    struct127 *obj;
    s32 i;

    if (D_800C35EA == 1) {
        return;
    }
    for (i = 0; i < 25; i++) {
        obj = &D_800CC2D0[i];
        if (*(s32 *)obj == 0) {
            continue;
        }
        D_800C3E78 = i;
        D_800D154C = obj;
        if (i < D_8008FD8C) {
            if (i < 4) {
                D_800CC6A4 = (u8 *)((s32 *)D_800BE728[0])[i];
            } else {
                bzero(pad, 6);
                D_800CC6A4 = pad;
            }
        }
        if ((((u8 *)obj)[4] == 0x28) || (((u8 *)obj)[4] == 0x77)) {
            func_150EDAF8((u8 *)obj);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504ADD0.s")
#endif
// NON-MATCHING: whats up with sp48
// void func_1504ADD0(void) {
//     struct127 *tmp;
//     s32 i;
//     u8 *ptr;
//     u8 *sp48;
//
//     if (D_800C35EA != 1) {
//         for (i = 0; i < 25; i++) {
//             tmp = &D_800CC2D0[i];
//             if (tmp->unk0 != 0) {
//                 D_800C3E78 = i;
//                 D_800D154C = tmp;
//                 if (i < D_8008FD8C) {
//                     if (i < 4) {
//                         D_800CC284 = D_800BE728[i];
//                     } else {
//                         bzero(sp48, 6);
//                         D_800CC284 = sp48;
//                     }
//                 }
//                 if ((tmp->id == 0x28) || (tmp->id == 0x77)) {
//                     func_150ED578(tmp);
//                 }
//             }
//         }
//     }
// }

s32 func_1504AEF4(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    return 0;
}

// bleurgh
#ifdef NON_MATCHING
// P45: carried-object link of a record. +0x92 = (kind << 12) | index (bit 15 = only with arg1). Kind 0: resolve
// through func_1504AEF4. Kind 3 (an entry of D_800DBEF4, 0xA0 bytes each): arg2 releases it (+0x4E = 0, link
// cleared); else +0x4E = record index + 100 (arg1: 0 instead) and, without arg1, the entry follows the record
// (+0x4F bits 5..6 = 1, +0x10/+0x12/+0x14 = position, y + s16 +0x90).
void func_1504AF10(struct127 *rec, s32 arg1, s32 arg2) {
    u8 *arg0 = (u8 *)rec;
    s32 sp28;
    s32 kind;
    s32 r;
    u16 v;
    u8 *e;

    v = *(u16 *)(arg0 + 0x92);
    if (v == 0) {
        return;
    }
    if (arg1 == 0 && ((s32)v >> 15) != 0) {
        return;
    }
    kind = ((s32)v >> 12) & 7;
    if (kind == 0) {
        r = func_1504AEF4(v & 0x7FFF, (s32)&sp28);
        kind = r;
        if (r != 0) {
            *(u16 *)(arg0 + 0x92) = (r << 12) | sp28;
        }
    }
    sp28 = *(u16 *)(arg0 + 0x92) & 0xFFF;
    if (kind != 3) {
        return;
    }
    if (arg2 != 0) {
        ((u8 *)D_800DBEF4)[(u32)sp28 * 0xA0 + 0x4E] = 0;
        *(u16 *)(arg0 + 0x92) = 0;
        return;
    }
    ((u8 *)D_800DBEF4)[(u32)sp28 * 0xA0 + 0x4E] = (s32)(rec - D_800CC2D0) + 100;
    if (arg1 != 0) {
        ((u8 *)D_800DBEF4)[(u32)sp28 * 0xA0 + 0x4E] = 0;
        return;
    }
    e = (u8 *)D_800DBEF4 + (u32)sp28 * 0xA0;
    e[0x4F] &= 0xFF9F;
    e = (u8 *)D_800DBEF4 + (u32)sp28 * 0xA0;
    e[0x4F] |= 0x20;
    *(s16 *)((u8 *)D_800DBEF4 + (u32)sp28 * 0xA0 + 0x10) = (s32)*(f32 *)(arg0 + 0x14);
    *(s16 *)((u8 *)D_800DBEF4 + (u32)sp28 * 0xA0 + 0x12) = (s32)(*(f32 *)(arg0 + 0x18) + (f32)*(s16 *)(arg0 + 0x90));
    *(s16 *)((u8 *)D_800DBEF4 + (u32)sp28 * 0xA0 + 0x14) = (s32)*(f32 *)(arg0 + 0x1C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504AF10.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504B0FC.s")
#ifdef NON_MATCHING
void func_1504BA38(struct127 *arg0) {
    s8 temp_a1;
    s8 temp_v0;
    u8 *temp_v1;

    if (arg0->unk28 > 10.0f) {
        arg0->unkCE = 0;
        return;
    }
    temp_v1 = ((arg0->unk184 & 0x1F) * 3) + ((u8 *)&D_800994F0);
    temp_a1 = (*(s8 *)((u8 *)temp_v1 + 2));
    if ((temp_a1 != 0) && (arg0->unkAA == 0)) {
        arg0->unkAA = (u8) temp_a1;
    }
    temp_v0 = (*(s8 *)((u8 *)temp_v1 + 1));
    if (temp_v0 == 0) {
        arg0->unkCE = (s16) (*(s8 *)((u8 *)temp_v1 + 0));
        return;
    }
    arg0->unkCE = (s16) (s32) ((f32) temp_v0 * 0.1f * ((f32) (*(s8 *)((u8 *)temp_v1 + 0)) - arg0->xz_velocity));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504BA38.s")
#endif
// NON-MATCHING: starts to fall apart towards the end
// void func_1504BA38(struct127 *arg0) {
//     s8 temp_a1;
//     s8 temp_v0;
//     s8 *temp_v1;
//
//     if (arg0->unk28 > 10.0f) {
//         arg0->unkCE = 0;
//     } else {
//         temp_v1 = &D_80099140[(arg0->unk184 & 0x1f) * 3]; // length 3 items
//         temp_a1 = temp_v1[2];
//         if ((temp_a1 != 0) && (arg0->unkAA == 0)) {
//             arg0->unkAA = temp_a1;
//         }
//         temp_v0 = temp_v1[1];
//         if (temp_v0 == 0) {
//             arg0->unkCE = temp_v1[0];
//         } else {
//             arg0->unkCE = (s16) (s32) (temp_v0 * D_800991D4 * ((f32) temp_v1[0] - arg0->unk3C));
//         }
//     }
// }

void func_1504BAF0(struct127 *arg0) {
    s16 temp_t7;
    u8 temp_v0;
    struct127 *temp_v1;

    temp_t7 = arg0->unk13C - 100;
    if (temp_t7 >= 0) {
        temp_v1 = &D_800CC2D0[temp_t7];
        if (temp_v1->unk13D >= 100) {
            temp_v0 = temp_v1->id;
            if ((temp_v0 == 168) || (temp_v0 == 169)) {
                D_800D1580 = 3;
                func_1507490C();
            }
        }
    }
    func_1506EBC0();
}

void func_1504BB88(struct127 *arg0) {
    if ((arg0->unk25C & 0x10)) {
        arg0->unk83 = 0xFF;
        arg0->disable_run = 0xFF;
        if (arg0->interaction_state == 1) {
            func_1505E650(arg0, 0xD6, 1.149999976158142f, 3.0f, 0.0f, 0.0f, 0);
        }
        arg0->unk25C &= ~0x10;
    }

    if ((arg0->unk25C & 2)) {
        if (arg0->unk13C) {
            func_1504BAF0(arg0);
        }
        arg0->unk25C &= ~2;
    }
}

void func_1504BC38(struct127 *arg0) {

    if ((arg0->disable_run != 0) && (arg0->disable_run < 0xFA)) {
        if (arg0->disable_run <= D_800BE9A0) {
            arg0->disable_run = 0U;
        } else {
            arg0->disable_run -= D_800BE9A0;
        }
    }
    if (arg0->unk228) {
        if (arg0->unk228 <= D_800BE9A0) {
            arg0->unk228 = 0U;
        } else {
            arg0->unk228 -= D_800BE9A0;
        }
    }
    if (arg0->unkAE) {
        arg0->unkAE -= 1;
    }
    if (arg0->disable_jump != 0xFF) {
        if (arg0->disable_jump <= D_800BE9A0) {
            arg0->disable_jump = 0U;
        } else {
            arg0->disable_jump -= D_800BE9A0;
        }
    }
    if (arg0->immune != 0xFF) {
        if (arg0->immune <= D_800BE9A0) {
            arg0->immune = 0U;
        } else {
            arg0->immune -= D_800BE9A0;
        }
    }
    if (arg0->unk31C->chased > 0) {
        arg0->unk31C->chased -= D_800BE9A0;
    }
    if (arg0->unk31C->chasing > 0) {
        arg0->unk31C->chasing -= D_800BE9A0;
    }
    if (arg0->unk31C->unk44 > 0) {
        arg0->unk31C->unk44 -= D_800BE9A0;
    }
    if (arg0->unk107 != 0) {
        arg0->unk107 -= 1;
    }
    if (arg0->unk1D0 > 0) {
        arg0->unk1D0 -= D_800BE9A0;
    }
    if (arg0->unk31C->unk54 > 0) {
        arg0->unk31C->unk54 -= D_800BE9A0;
    }
    if (arg0->unk31C->unk55 != 0) {
        arg0->unk31C->unk55 -= 1;
    }

    arg0->unk31C->unk52 >>= 1;

    if (arg0->unk31C->unk19E != 0) {
        if (arg0->unk31C->unk19E > D_800BE9E4) {
            arg0->unk31C->unk19E -= D_800BE9E4;
        } else {
            arg0->unk31C->unk19E = 0U;
        }
    }
    if (arg0->unk31C->unk1A0 != 0) {
        if (arg0->unk31C->unk1A0 > D_800BE9E4) {
            arg0->unk31C->unk1A0 -= D_800BE9E4;
        } else {
            arg0->unk31C->unk1A0 = 0U;
        }
    }
}

#ifdef NON_MATCHING
extern u8 *D_800CC6A4;
extern u16 D_800CC6D2;
extern f32 D_800CC6D4;

void func_1504BE2C(u8 *arg0, u16 *arg1, f32 *arg2, s8 *arg3) {
    f32 sp1C;
    f32 temp_f12;
    f32 var_f6;
    u16 temp_v0_2;
    u8 temp_t7;
    u8 temp_v1;
    u8 *temp_v0;
    u8 *var_v0;

    temp_t7 = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0xB));
    var_f6 = (f32) temp_t7;
    if ((s32) temp_t7 < 0) {
        var_f6 += 4294967296.0f;
    }
    temp_f12 = var_f6 * 0.024543693f;
    D_800CC6D4 = 16.0f;
    var_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    temp_v1 = (*(u8 *)((u8 *)var_v0 + 0x16));
    if ((temp_v1 != 0) && (temp_v1 == 0)) {
        sp1C = temp_f12;
        func_1507EF0C(temp_f12);
        (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 8)) = 0;
        var_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    }
    if ((*(u16 *)((u8 *)var_v0 + 0xE)) == 0) {
        (*(u16 *)((u8 *)var_v0 + 0xE)) = 0xA6U;
        var_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    }
    (*(s8 *)((u8 *)var_v0 + 0x3C)) = 5;
    if ((*arg2 > 4.0f) && ((*(u16 *)((u8 *)arg0 + 0x84)) == 0xAA)) {
        (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x3C)) = 1;
        (*(u16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x10)) = (u16) *arg1;
    }
    func_150AD78C(temp_f12);
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    (*(u8 *)((u8 *)temp_v0 + 0xB)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0xB)) + 2);
    if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x16)) != 0) {
        (*(s8 *)((u8 *)arg0 + 0xAA)) = 0x19;
    } else if ((*(u16 *)((u8 *)arg0 + 0x84)) == 0xA7) {
        (*(s8 *)((u8 *)arg0 + 0xAA)) = 0x32;
    } else {
        (*(s8 *)((u8 *)arg0 + 0xAA)) = 0x20;
    }
    temp_v0_2 = (*(u16 *)((u8 *)arg0 + 0x84));
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x54)) * 0.5f);
    if ((temp_v0_2 == 0x2C) || (temp_v0_2 == 0xE0)) {
        *arg3 = (s8) ((s8) (*(s8 *)((u8 *)D_800CC6A4 + 3)) >> 1);
    } else {
        if (!(func_150ADA20() & 0x3F)) {
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x14)) = (s16) ((func_150ADA20() % 25000U) - 0x30D4);
        }
        D_800CC6D2 = (*(u16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x14));
        if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x16)) != 0) {
            D_800CC6D2 = (u16) ((s16) D_800CC6D2 / 3);
        }
    }
    if ((D_800C35EA == 0) && ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x16)) == 0)) {
        (*(s16 *)((u8 *)arg0 + 0x282)) = 0x1E;
        (*(s8 *)((u8 *)arg0 + 0x276)) = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504BE2C.s")
#endif
s32 func_1504C078(void) {
    if (D_800D154C->unk31C->unk58 != 1) {
        D_800D154C->unk31C->unk59 = 0;
        func_1507F640();
    }
    return 999;
}

s32 func_1504C0B8(void) {
    if (D_800BE9F0 == 27 || D_800BE9F0 == 30) {
        return 395;
    }
    return 27;
}

#ifdef NON_MATCHING
s32 func_15064F50(struct127 *, f32, f32, s32, f32);
extern u8 D_800CC69C;
extern u8 D_800CC6D1;
extern f32 D_800CC6D4;
extern s32 D_800CC6DC;

void func_1504C0E8(struct127 *arg0, s32 arg1, f32 arg2) {
    u8 temp_v0_4;
    u8 temp_a1;
    struct126 *var_v1;
    struct126 *temp_v1_4;
    struct126 *temp_v1_3;
    struct126 *temp_v1_2;
    struct126 *temp_v1;
    s32 var_t0;
    s32 temp_v0_3;
    s32 temp_t8;
    s16 temp_v0_2;
    s16 temp_v0;
    f32 var_f2;
    f32 var_f12_2;
    f32 var_f12;
    f32 temp_f0_2;
    f32 temp_f0;
    s32 sp28;
    f32 sp2C;
    f32 sp34;
    f32 sp38;
    f32 sp3C;

    if ((((s16) D_800CC6D2) == 0) && (temp_v1 = arg0->unk31C, temp_v0 = temp_v1->unk12, ((temp_v0 < -0x1D) == 0)) && (temp_v0 < 0x1E)) {
        temp_v1->unk12 = 0;
    } else {
        temp_v1_2 = arg0->unk31C;
        temp_v0_2 = temp_v1_2->unk12;
        temp_v1_2->unk12 = temp_v0_2 + (s32) ((*D_800D1550 / D_800CC6D4) * (f32) (((s16) D_800CC6D2) - temp_v0_2));
    }
    temp_v1_3 = arg0->unk31C;
    if (temp_v1_3->unk6B == 0) {
        var_t0 = 0x3E7;
        if ((arg0->unk65 != 0) && (arg0->stunned == 0)) {
            func_15064DD0(arg0);
            return;
        }
        if ((arg0->unk81 == 0) && (arg0->stunned == 0) && (arg0->in_water == 0)) {
            if ((arg0->unk83 == 0) && (temp_v1_3->unk11A != 3)) {
                arg0->unk80 = 1;
                arg0->unk100 &= 0xF3;
                D_800CC6DC |= 0x80;
                sp38 = 0.0f;
                sp3C = 4.0f;
                var_v1 = arg0->unk31C;
                var_f12 = 1.0f;
                var_f2 = (arg0->xz_velocity * 0.4f) + (arg2 * 0.6f);
                if (((*(s16 *)((u8 *)var_v1 + 0x46)) > 0) || (var_v1->unk4E != 0) || ((s32) arg0->unk13C >= 0x64) || (arg1 != 0) || ((*(u16 *)((u8 *)var_v1 + 0x32)) & 3) || (var_v1->unk78 != 0) || (var_v1->pad17[3] != 0) || (var_v1->unk8 > 0) || (var_v1->pad17[0] != 0)) {
                    sp28 = 0x3E7;
                    sp34 = var_f2;
                    sp2C = 1.0f;
                    temp_v0_3 = func_15064F50(arg0, var_f2, var_f2, arg1, arg2);
                    var_t0 = sp28;
                    var_f2 = sp34;
                    var_f12 = sp2C;
                    if (temp_v0_3 == 0) {
                        var_v1 = arg0->unk31C;
                        goto block_25;
                    }
                } else {
block_25:
                    temp_t8 = *(u16 *)D_800CC6A4 & 0x2000;
                    if ((temp_t8 == 0) || (D_800CC6D1 != 0) || (var_v1->unk78 != 0) || ((var_v1->unk4E & 0xF) == 1)) {
                        if (arg0->xz_velocity > 4.0f) {
                            var_v1->pad37 = 0;
                            var_v1 = arg0->unk31C;
                        }
                        temp_a1 = var_v1->unk4E;
                        if (((temp_a1 == 1) || (temp_a1 == 0x81)) && (var_f2 > 1.0f)) {
                            arg2 = 10.0f;
                            temp_f0 = arg0->xz_velocity;
                            var_t0 = 0x302;
                            var_f12_2 = (temp_f0 / 7.0f) + 0.2f;
                            if (temp_f0 > 23.0f) {
                                var_t0 = 0x303;
                                var_f12_2 = (temp_f0 / 23.0f) + 0.3f;
                            }
                        } else if ((var_v1->chased > 0) && (var_f2 >= 5.0f)) {
                            var_t0 = 0x2B;
                            var_f12_2 = var_f2 / 12.0f;
                        } else if ((var_v1->chasing > 0) && (var_f2 >= 5.0f)) {
                            var_t0 = 0xDF;
                            var_f12_2 = var_f2 / 12.0f;
                        } else {
                            temp_f0_2 = arg0->unk118;
                            if ((temp_f0_2 != -10000.0f) && (arg0->y_position < temp_f0_2) && (arg0->xz_velocity >= 1.0f) && (temp_a1 == 0)) {
                                var_t0 = 0x8B;
                                arg0->unkAA = 0x4B;
                                var_f12_2 = (var_f2 / 18.0f) + 0.2f;
                            } else if (var_f2 > 14.0f) {
                                var_t0 = 0x1B2;
                                if (D_800BE9F0 != 4) {
                                    var_t0 = 2;
                                }
                                var_f12_2 = (var_f2 / 23.0f) + 0.8f;
                            } else if ((var_f2 > 6.0f) || ((arg2 < 1.0f) && (arg0->xz_velocity > 1.0f))) {
                                var_t0 = 1;
                                var_f12_2 = (var_f2 * 0.125f) + 0.3f;
                            } else if (var_f2 > 1.0f) {
                                var_t0 = 0;
                                sp3C = 15.0f;
                                if (arg0->id == 0x80) {
                                    var_t0 = 1;
                                }
                                var_f12_2 = (var_f2 * 0.125f) + 0.1f;
                            } else {
                                sp2C = var_f12;
                                var_f12_2 = sp2C;
                                var_t0 = func_1504C078();
                            }
                        }
                        if ((arg0->unk28 > 60.0f) && (arg0->unk31C->unk4E == 0)) {
                            var_f12_2 = 0.5f;
                            var_t0 = 0x38;
                            arg0->unk100 |= 0x10;
                        }
                        if (arg0->xz_velocity > 18.0f) {
                            temp_v0_4 = arg0->unk31C->unk11A;
                            if ((temp_v0_4 != 1) && (temp_v0_4 != 3) && (arg2 == 0.0f) && (arg0->unk28 == 0.0f) && (D_800CC69C == 0)) {
                                var_f12_2 = 0.5f;
                                var_t0 = 0x21;
                                sp3C = 3.0f;
                                arg0->disable_run = 8;
                                arg0->unk83 = 0x11;
                            }
                        }
                        goto block_78;
                    }
                    sp2C = var_f12;
                    if (temp_t8 != 0) {
                        if (arg0->xz_velocity < 3.0f) {
                            var_v1->pad37 = 1;
                        }
                        if ((arg0->unk44 > 2.6f) && (temp_v1_4 = arg0->unk31C, (temp_v1_4->pad37 != 0))) {
                            (*(s32 *)((u8 *)temp_v1_4 + 4)) = 1;
                            arg0->unkAA = 0x28;
                            sp3C = 5.0f;
                            sp2C = (arg0->unk44 / 15.0f) + 0.5f;
                            var_t0 = func_1504C0B8();
                        } else {
                            var_f12_2 = 1.5f;
                            var_t0 = 0x16;
                            sp3C = 6.0f;
block_78:
                            sp2C = var_f12_2;
                        }
                    }
                    goto block_79;
                }
            } else {
block_79:
                if (var_t0 != 0x3E7) {
                    func_1505E650(arg0, var_t0 & 0xFFFF, sp2C, sp3C, sp38, 0.0f, 0);
                }
            }
        } else if ((arg0->unk84.uh == 0x21) && (D_800CC6D1 == 0) && (arg0->unk44 == 0.0f) && (*(u16 *)D_800CC6A4 & 0x2000)) {
            func_1505E650(arg0, 0x16U, 1.5f, 6.0f, 0.0f, 0.0f, 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504C0E8.s")
#endif
void func_1504C854(struct127 *arg0) {
    D_800CC288 = arg0->unk31C->unk8C;

    if (arg0->unk31C->unk8E > 0) {
        arg0->unk31C->unk8E -= D_800BE9A0;
    } else {
        arg0->unk31C->unk8A = 0;
    }
    if (arg0->unk31C->unk8F > 0) {
        arg0->unk31C->unk8F -= D_800BE9A0;
    } else {
        arg0->unk31C->unk8C = 0;
    }
}

s32 func_1504C8BC(struct127 *arg0) {
    struct126 *temp_v1 = arg0->unk31C;

    if (temp_v1 == NULL) {
        return 1;
    }
    if ((arg0->unk1D4 != NULL) || (D_800BE9F0 == 0x33) || (arg0->interaction_state == 0x25)) {
        temp_v1->unk1A8 = 0;
        return 1;
    }
    if ((arg0->unk127 & 1) == D_800CC6D8) {
        if (temp_v1->unk1A8 != 0) {
            D_800CC6DA = D_800BE9E4;
            D_800BE9E4 += arg0->unk31C->unk1A8;
            D_800BE9A4 = D_800BE9E4 * 0.5f;
            if (D_800BE9A4 != 0.0f) {
                D_800BEDC8 = 1.0f / D_800BE9A4;
            } else {
                D_800BEDC8 = 0.0f;
            }
            arg0->unk31C->unk1A8 = 0;
            return 2;
        }
        return 1;
    }
    temp_v1->unk1A8 += D_800BE9E4;
    return 0;
}

void func_1504C9E4(struct127 *arg0, s8 arg1, u8 arg2) {
    u8 phi_a2;
    s32 tmp0;
    s32 tmp1;

    tmp0 = (u8)(arg0->unk1D1 - arg1);

    if (tmp0) {
        phi_a2 = 3;
        if (arg2 == 16) {
            phi_a2 = 6;
        }

        tmp1 = tmp0;
        if (tmp0 >= 128) {
            arg0->unk1D1 += phi_a2;
        }
        else {
            arg0->unk1D1 -= phi_a2;
        }

        tmp0 = tmp1;
        tmp0 ^= arg0->unk1D1 - arg1;
        if ((u8)tmp0 & 0x80)
        {
            arg0->unk1D1 = arg1;
        }
    }
}

void func_1504CA60(struct127 *arg0) {
    f32 var_f12;
    f32 var_f2;
    f32 temp_f0;

    temp_f0 = arg0->unk28;
    var_f12 = 18.0f;
    var_f2 = arg0->unk180 + 20.0f;
    arg0->unk1CC = arg0->y_position;
    if (temp_f0 > 30.0f) {
        var_f12 = 80.0f;
    }
    if (arg0->unk81 != 0) {
        var_f12 = 80.0f;
        var_f2 -= 30.0f;
        if ((temp_f0 < 5.0f) && (arg0->y_velocity < 0.0f)) {
            arg0->unk81 = 0;
            arg0->y_velocity = 45.0f;
        }
    } else if (temp_f0 < 20.0f) {
        if (!(func_150ADA20() & 0x3F)) {
            arg0->y_velocity = 25.0f;
        }
    }
    func_15058EA4(arg0, var_f2, 3.8f, var_f2, -3.5f, 80.0f, -var_f12);
    arg0->unk80 = 1;
}
#ifdef NON_MATCHING
u16 func_1505A630(f32, f32, s32);
f32 func_150AD78C(f32);
s32 func_150585F0(struct127 *, s32);
void func_15056B08(struct127 *);
void func_15021834(struct127 *, s32, s32);
void func_1505250C(struct127 *arg0, s32 arg1);
void func_15052260(struct127 *arg0);
void func_1505A770(struct127 *);
s32 func_1000F568(s32, s32);
f32 func_1504B0FC(struct127 *, f32);
void func_1504C0E8(struct127 *, s32, f32);
void func_15051558(struct127 *, f32, f32, u16); /* P60: void (the asm leaves no result) */
void func_15059C84(struct127 *);
s32 func_1505C7D8(struct127 *, u8);
void func_15060A30(s32, struct127 *);
s32 func_1506E46C(struct127 *, s32 *, s32);
s32 func_1507CD64(struct127 *, s32);
void func_1502ECFC(struct127 *, s32, s32, s32, s32, s32); 
void func_1502ED40(struct127 *);                 
s32 func_15044670(f32, f32, s32, struct127 *, s32, s32); // P47: arg 2 = f32 bits in a2 
void func_15055E50(struct127 *, u8);             
s32 func_150599C8(struct127 *, u8, u16);            
f32 func_1505A3A8(f32, struct127 *, f32, f32, u8); // P47: a1 = the record (left in a1 by the asm) 
void func_1505A9AC(struct127 *, f32);
s32 func_1505D024(struct127 *, s32, u16, s32); 
void func_1505D6F0(struct127 *, s32); /* P59: void in the NM definition */
void func_1505F298(struct127 *, struct49 *); /* P64: void in the NM definition */
void func_1506045C(struct127 *, s32, s32, f32, s32); /* P102: arg3 f32 */
void func_15063168(struct127 *);                 
void func_150802A8(struct127 *);                 
s32 func_150882C4(u8, struct127 *);             
s32 func_150A44A4(f32, f32, s32, f32 *, f32 *);     
void func_150D5F7C(struct127 *, s32, s32); 
void func_150D7CA0(struct127 *, s32);            
void func_1510EE3C(s32 *, f32 *, f32 *, f32 *, s32 *, u8 *, f32, f32, f32, f32, s32, struct127 *, s32, s32, s32); // P47: args 12/13 are f32 bits 
void func_15121A00(struct127 *, struct49 *);     
s32 func_151279A0(struct127 *, struct49 *);     
void func_151AE814(u8 *);
extern u16 D_8009952C[];
extern u8 D_800B89C4[];
extern u16 D_800BEB30[];
extern u8 D_800BEE2C;
extern f32 D_800CC1B0;
extern f32 D_800CC1B4;
extern f32 D_800CC1B8;
extern s8 D_800CC1F3;
extern s8 D_800CC1F4;
extern u8 D_800CC68C;
extern f32 D_800CC690;
extern f32 D_800CC694;
extern f32 D_800CC698;
extern u16 D_800CC69E;
extern s32 D_800CC6AC;
extern s32 D_800CC6B0;
extern u8 D_800CC6D1;

void func_1504CB98(struct127 *arg0) {
    u16 sp1C6;
    u16 sp1C4;
    u8 sp1C2;
    u8 sp1C1;
    f32 sp1BC;
    f32 sp1B0;
    s32 sp1A0;
    s8 sp19F;
    f32 sp198;
    f32 sp194;
    s32 sp190;
    u16 sp188[3];
    s32 sp184;
    f32 sp180;
    s32 sp17C;
    u32 sp160;
    struct127 *sp12C;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    s32 sp108;
    f32 sp104;
    s16 spFE;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    u8 spD3;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    s16 sp96;
    f32 sp8C;
    f32 sp88;
    s32 sp84;
    f32 *sp64;
    s32 sp5C;
    s32 var_a1_2;
    f32 *temp_a1_2;
    f32 *temp_a3;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_19;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f2_8;
    f32 temp_f2_9;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f14_3;
    f32 var_f14_4;
    f32 var_f14_5;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f16_3;
    f32 var_f18;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f8;
    s16 temp_v0_17;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v1_5;
    s16 var_v0_2;
    s32 *var_a2;
    s32 temp_a0;
    s32 temp_a0_6;
    s32 temp_a1_3;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f4;
    s32 temp_lo;
    s32 temp_t0_5;
    s32 temp_t5_3;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t8_2;
    s32 temp_v0_35;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a2_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1_6;
    s32 var_v1_8;
    s8 temp_a0_2;
    s8 temp_t6_2;
    s32 temp_t9;
    s8 temp_v0_12;
    s8 temp_v0_13;
    s8 temp_v0_28;
    s8 temp_v1_2;
    s32 var_a1_3;
    s8 var_t1_2;
    s8 var_v1_3;
    s8 var_v1_4;
    struct108 *temp_v0_14;
    struct108 *temp_v0_25;
    struct108 *temp_v0_26;
    struct108 *temp_v0_39;
    struct126 *temp_t0;
    struct126 *temp_t0_10;
    struct126 *temp_t0_11;
    struct126 *temp_t0_12;
    struct126 *temp_t0_13;
    struct126 *temp_t0_14;
    struct126 *temp_t0_15;
    struct126 *temp_t0_16;
    struct126 *temp_t0_17;
    struct126 *temp_t0_18;
    struct126 *temp_t0_19;
    struct126 *temp_t0_20;
    struct126 *temp_t0_21;
    struct126 *temp_t0_22;
    struct126 *temp_t0_23;
    struct126 *temp_t0_24;
    struct126 *temp_t0_25;
    struct126 *temp_t0_26;
    struct126 *temp_t0_27;
    struct126 *temp_t0_28;
    struct126 *temp_t0_29;
    struct126 *temp_t0_2;
    struct126 *temp_t0_30;
    struct126 *temp_t0_31;
    struct126 *temp_t0_32;
    struct126 *temp_t0_33;
    struct126 *temp_t0_34;
    struct126 *temp_t0_35;
    struct126 *temp_t0_36;
    struct126 *temp_t0_37;
    struct126 *temp_t0_38;
    struct126 *temp_t0_3;
    struct126 *temp_t0_4;
    struct126 *temp_t0_6;
    struct126 *temp_t0_7;
    struct126 *temp_t0_8;
    struct126 *temp_t0_9;
    struct127 *temp_v0_21;
    struct127 *temp_v0_29;
    struct127 *temp_v0_31;
    struct127 *temp_v0_32;
    struct127 *temp_v0_33;
    struct127 *temp_v0_34;
    struct127 *var_v0_7;
    u16 temp_a0_3;
    u16 temp_a0_5;
    u16 temp_a1;
    u16 temp_a2_2;
    u16 temp_a2_3;
    u16 temp_t1;
    u16 temp_t4;
    u16 temp_t5;
    u16 temp_t5_2;
    u16 temp_t6;
    u16 temp_t8;
    u16 temp_t9_2;
    u16 temp_t9_3;
    u16 temp_v0_23;
    u16 temp_v0_30;
    u16 temp_v0_36;
    u16 temp_v0_3;
    u16 temp_v0_40;
    u16 temp_v0_41;
    u16 temp_v0_46;
    u16 temp_v0_8;
    u16 temp_v1_7;
    u16 var_v0_6;
    u16 var_v1_2;
    u32 var_v1;
    u8 temp_a2;
    u8 temp_a2_4;
    u8 temp_t9_4;
    u8 temp_v0;
    u8 temp_v0_10;
    u8 temp_v0_11;
    u8 temp_v0_15;
    u8 temp_v0_16;
    u8 temp_v0_18;
    u8 temp_v0_19;
    u8 temp_v0_20;
    u8 temp_v0_22;
    u8 temp_v0_24;
    u8 temp_v0_27;
    u8 temp_v0_2;
    u8 temp_v0_37;
    u8 temp_v0_38;
    u8 temp_v0_42;
    u8 temp_v0_43;
    u8 temp_v0_44;
    u8 temp_v0_45;
    u8 temp_v0_4;
    u8 temp_v0_5;
    u8 temp_v0_9;
    u8 temp_v1;
    u8 temp_v1_10;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_6;
    u8 temp_v1_9;
    u8 var_a0_3;
    u8 var_a2_3;
    u8 var_a2_4;
    u8 var_t1;
    u8 var_v0;
    u8 var_v0_3;
    u8 var_v1_5;
    u8 var_v1_7;
    void *temp_a0_4;
    void *temp_v1_8;

    sp1BC = 0.0f;
    sp1A0 = 0;
    sp19F = 0;
    D_800CC6AC = (s32) D_800BEB30[D_800C3E78];
    D_800CC6B0 = (s32) (u16) ((struct49 *)D_800CC6A4)->unk0;
    D_800CC6D1 = 0;
    D_800CC6D2 = 0;
    D_800CC6D4 = 4.0f;
    sp184 = 0;
    sp1C6 = arg0->unk76;
    sp188[0] = ((u16 *)D_800CC6A4)[0]; sp188[1] = ((u16 *)D_800CC6A4)[1];
    sp188[2] = (u16) (*(u16 *)((u8 *)(D_800CC6A4) + 4));
    D_800CC6DC = 1;
    (*(u8 *)((u8 *)(arg0->unk31C) + 0x1B3)) = 0U;
    temp_t0 = arg0->unk31C;
    if (temp_t0->unk84 != 0) {
        if (arg0->stunned == 0) {
            func_15056B08(arg0);
        }
        sp188[0] = ((u16 *)D_800CC6A4)[0]; sp188[1] = ((u16 *)D_800CC6A4)[1];
        sp188[2] = (u16) (*(u16 *)((u8 *)(D_800CC6A4) + 4));
        ((struct49 *)D_800CC6A4)->unk2 = (s8) arg0->unk31C->pad85[0];
        ((struct49 *)D_800CC6A4)->unk3 = (s8) arg0->unk31C->pad85[1];
        ((struct49 *)D_800CC6A4)->unk0 = (s16) (u16) arg0->unk31C->unk8A;
        D_800CC288 = (s32) arg0->unk31C->unk8C;
        sp190 = (s32) (u16) arg0->unk31C->unk8A;
        if (arg0->camera == NULL) {
            func_151279A0(arg0, D_800CC6A4);
            func_15121A00(arg0, D_800CC6A4);
        }
        func_1504C854(arg0);
    } else {
        temp_t0->unk8A = (s16) (u16) ((struct49 *)D_800CC6A4)->unk0;
        D_800CC288 = (s32) D_800BEB30[D_800C3E78];
        sp190 = (s32) (u16) arg0->unk31C->unk8A;
    }
    if ((D_80082FA0 >= (s32) D_800C3E78) && ((&D_800DDE3C)[(s32) D_800C3E78] != 0) && ((&D_800DDDC8)[(s32) D_800C3E78] > 0.75f) && (D_800E0B94 != 2)) {
        ((struct49 *)D_800CC6A4)->unk2 = 0;
        ((struct49 *)D_800CC6A4)->unk3 = 0;
        ((struct49 *)D_800CC6A4)->unk0 = 0;
        D_800CC288 = 0;
        sp184 = 1;
        D_800CC6DC |= 2;
    }
    if ((arg0->stunned != 0) && (arg0->health != 0) && (((temp_v0 = (u8) arg0->unk31C->unk26, ((temp_v0 & 1) != 0)) && (D_800CC288 & 0x8000)) || ((temp_v0 & 2) && (func_1505A5CC(D_800CC6A4) > 15.0f)))) {
        arg0->unk10C = 0;
        arg0->unk105 = 3;
        func_150585F0(arg0, 0x3D4CCCCD);
    }
    temp_t0_2 = arg0->unk31C;
    if (D_800BE616 != 0) {
        temp_v1 = (*(u8 *)((u8 *)(temp_t0_2) + 0x1B1));
        if ((s32) D_800BE9A0 < (s32) temp_v1) {
            (*(u8 *)((u8 *)(temp_t0_2) + 0x1B1)) = (u8) (temp_v1 - D_800BE9A0);
            if (arg0->unkA4 != 4) {
                func_1502ECFC(arg0, 0xFF, 0xFF, 0xFF, 0xBF, 4);
            }
        } else if (arg0->unkA4 == 4) {
            (*(u8 *)((u8 *)(temp_t0_2) + 0x1B1)) = 0U;
            func_1502ED40(arg0);
        }
        if (((D_800BE9F0 == 0x2D) || (D_800BE9F0 == 0x30) || (D_800BE9F0 == 0x34) || (D_800BE9F0 == 0x1A) || (D_800BE9F0 == 0x3F)) && (D_800CC288 & 4) && !(D_800CC288 & 0xC000) && ((s32) arg0->unk28 == 0) && (arg0->y_velocity < 0.0f) && (arg0->disable_run == 0) && (arg0->unk13C == 0) && (arg0->unk31C->unk19B == 0) && (arg0->unk31C->unk78 == 0) && ((arg0->unk31C->unk75 & ~0x80) != 3) && (arg0->unk31C->grenade_count != 0)) {
            if ((arg0->id == 0x3B) || (D_800BE9F0 == 0x1A) || (D_800BE9F0 == 0x3F)) {
                arg0->unk31C->unk19B = 5;
            } else {
                arg0->unk31C->unk19B = 1;
            }
        }
    }
    arg0->unk31C->unk38 = (s32) (u16) ((struct49 *)D_800CC6A4)->unk0;
    if (D_800C3638 != 0) {
        ((struct49 *)D_800CC6A4)->unk2 = 0;
        ((struct49 *)D_800CC6A4)->unk3 = 0;
        ((struct49 *)D_800CC6A4)->unk0 = 0;
        D_800CC288 = 0;
        D_800CC6DC |= 4;
    }
    func_150802A8(arg0);
    func_1504BB88(arg0);
    func_1504BA38(arg0);
    if ((arg0->unk228 != 0) || (arg0->unk2F8 & 0x10)) {
        (*(s8 *)((u8 *)(D_800CC6A4) + 2)) = 0;
        (*(s8 *)((u8 *)(D_800CC6A4) + 3)) = 0;
        (*(s16 *)((u8 *)(D_800CC6A4) + 0)) = 0;
        D_800CC288 = 0;
        sp184 = 1;
        D_800CC6DC |= 8;
    }
    var_a2 = &D_800CC6DC;
    if (arg0->health == 0) {
        arg0->disable_run = 0x14;
        if ((arg0->stunned == 0) && (arg0->unk31C->unk120 == 0)) {
            temp_t7 = arg0->unk184 & 0x1F;
            if (temp_t7 == 0xE) {
                func_1507CD64(arg0, 0xD);
            } else if (temp_t7 == 0x13) {
                func_1507CD64(arg0, 0xD);
            } else {
                func_1507CD64(arg0, 0);
            }
            var_a2 = &D_800CC6DC;
        }
    }
    temp_t0_3 = arg0->unk31C;
    temp_v0_2 = temp_t0_3->unk78;
    if (temp_v0_2 != 0x1B) {
        if (((temp_t0_3->unk198 == 0) || (temp_v0_2 == 3)) && (temp_v0_2 != 0x12) && (temp_v0_2 != 2) && (temp_v0_2 != 0x13) && (temp_v0_2 != 0xA) && (temp_v0_2 != 0x34)) {
            sp17C = (s32) temp_v0_2;
            D_800CC6DC |= 0x10;
            sp1C4 = func_1505A630((f32) ((struct49 *)D_800CC6A4)->unk2, (f32) ((struct49 *)D_800CC6A4)->unk3, 0);
            sp1BC = func_1505A5CC(D_800CC6A4);
            temp_t0_4 = arg0->unk31C;
            var_v0 = temp_t0_4->unk4E;
            if (var_v0 == 2) {
                var_f0 = (f32) ((struct49 *)D_800CC6A4)->unk3 * 0.6f;
                var_v0_2 = ((struct49 *)D_800CC6A4)->unk2 * D_800CC264;
                if (var_f0 > 45.0f) {
                    var_f0 = 45.0f;
                }
                if (var_f0 < -35.0f) {
                    var_f0 = -35.0f;
                }
                temp_v1_2 = (s8) temp_t0_4->pad4F[1];
                if (temp_v1_2 > 0) {
                    temp_t0_4->pad4F[1] = temp_v1_2 - D_800BE9A0;
                    var_v0_2 = (s16) (var_v0_2 / 3);
                    arg0->disable_jump = 6;
                    var_f0 -= 60.0f;
                } else if ((arg0->unk28 > 100.0f) || (arg0->unk83 != 0)) {
                    var_v0_2 = (s16) (var_v0_2 / 2);
                }
                sp1BC = 135.0f + var_f0;
                arg0->unk239 = 0x29;
                if (arg0->unk31C->unk84 == 0) {
                    if (arg0->disable_run == 0) {
                        arg0->unk76 -= var_v0_2 / 9;
                    } else {
                        sp1BC = 0.0f;
                    }
                    func_150882C4(D_800C3E78, arg0);
                    sp1C4 = arg0->unk76 - D_800CC6A0;
                }
                var_v0 = arg0->unk31C->unk4E;
            }
            if (var_v0 == 0x81) {
                var_a0 = 0x6000;
                arg0->unk76 -= (s16) (((struct49 *)D_800CC6A4)->unk2 * D_800CC264) / 8;
                if (D_800BE9F0 == 6) {
                    sp1BC = 42.0f;
                    var_a0 = func_1505A630(2540.0f - arg0->x_position, arg0->z_position - -160.0f, 0) & 0xFFFF;
                    var_a1 = 0xF000;
                    var_a2_2 = 0x8000;
                } else {
                    var_a1 = 0xB000;
                    var_a2_2 = 0x2000;
                    sp1BC = 65.0f;
                }
                temp_t0_5 = (arg0->unk76 - var_a0) & 0xFFFF;
                if (var_a1 < temp_t0_5) {
                    arg0->unk76 = var_a0 + var_a1;
                }
                if (temp_t0_5 < var_a2_2) {
                    arg0->unk76 = var_a0 + var_a2_2;
                }
                sp1C4 = arg0->unk76 - D_800CC6A0;
                temp_v0_3 = arg0->unk76;
                arg0->unk78 = temp_v0_3;
                arg0->unk7A = temp_v0_3;
            }
            if (arg0->unk31C->unk197 != 0) {
                sp1BC = 0.1f;
                temp_f10 = (s32) ((*(f32 *)((u8 *)(arg0->unk31C) + 0x16C)) * 182.04445f);
                arg0->unk7A = (u16) temp_f10;
                sp1C4 = temp_f10 - D_800CC6A0;
                if (arg0->unk31C->unk84 != 0) {
                    arg0->unk76 = arg0->unk7A;
                }
                var_f0_2 = (*(f32 *)((u8 *)(arg0->unk31C) + 0x170));
                if (var_f0_2 > 180.0f) {
                    var_f0_2 -= 360.0f;
                }
                sp19F = (s8) (s32) (var_f0_2 * 0.91022223f);
                if ((D_800BE616 != 0) && ((temp_v0_4 = arg0->id, (temp_v0_4 == 0x3B)) || (temp_v0_4 == 0x80)) && ((sp17C == 0x18) || (sp17C == 0x41) || (sp17C == 0x23) || (sp17C == 0x24)) && ((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x2000) && ((temp_t0_6 = arg0->unk31C, temp_v0_5 = temp_t0_6->padAE[0x5B], (temp_v0_5 == 3)) || (temp_v0_5 == 2))) {
                    var_v1 = 0;
                    if ((s32) temp_t0_6->padAE[1] < 0x32) {
                        var_v1 = 0x30;
                    }
                    sp160 = var_v1;
                    if ((func_10010894(arg0) == 0) && (sp160 >= (u32) (func_150ADA20() & 0x5F))) {
                        if (arg0->id == 0x80) {
                            if ((sp17C == 0x23) && !(func_150ADA20() & 7)) {
                                func_15060A30(0x586, arg0);
                            } else {
                                var_a1_2 = 5;
                                if (sp17C == 0x23) {
                                    var_a1_2 = 4;
                                }
                                func_15060A30(func_1000F568(0x574, var_a1_2), arg0);
                            }
                        } else if (((u16) ((struct49 *)D_800CC6A4)->unk0 & 8) && !(func_150ADA20() & 1)) {
                            func_15060A30(0x532, arg0);
                        } else {
                            temp_t0_7 = arg0->unk31C;
                            if ((temp_t0_7->padAE[0x5B] == 3) && (temp_t0_7->padAE[0x5A] == 0xA) && !(func_150ADA20() & 3)) {
                                func_15060A30(0x533, arg0);
                            } else {
                                func_15060A30((func_150ADA20() & 3) + 0x534, arg0);
                            }
                        }
                    }
                    arg0->unk31C->padAE[1] = 0x64;
                }
                temp_t0_8 = arg0->unk31C;
                temp_v1_3 = temp_t0_8->padAE[1];
                if (temp_v1_3 != 0) {
                    if (D_800BE9E4 < (s32) temp_v1_3) {
                        temp_t0_8->padAE[1] = temp_v1_3 - D_800BE9E4;
                    } else {
                        temp_t0_8->padAE[1] = 0;
                    }
                }
            } else {
                arg0->unk31C->padAE[1] = 0;
            }
            temp_v0_6 = (*(s16 *)((u8 *)(arg0->unk31C) + 0x48));
            if (temp_v0_6 > 0) {
                (*(s16 *)((u8 *)(arg0->unk31C) + 0x48)) = (s16) (temp_v0_6 - D_800CC264);
                sp1C4 = arg0->unk76 - D_800CC6A0;
            }
            temp_v0_7 = (*(s16 *)((u8 *)(arg0->unk31C) + 0x46));
            if (temp_v0_7 > 0) {
                (*(s16 *)((u8 *)(arg0->unk31C) + 0x46)) = (s16) (temp_v0_7 - D_800CC264);
                if (D_800CC288 & 0xC000) {
                    if (arg0->unk28 == 0.0f) {
                        D_800D1580 = -0xFCFE90;
                        arg0->y_velocity = 10.0f;
                        arg0->gravity = 5.0f;
                        arg0->xz_velocity *= 0.4f;
                    }
                    temp_t0_9 = arg0->unk31C;
                    (*(s16 *)((u8 *)(temp_t0_9) + 0x46)) = (s16) ((*(s16 *)((u8 *)(temp_t0_9) + 0x46)) - 0x190);
                }
                if (arg0->disable_run == 0) {
                    if (sp1BC < 5.0f) {
                        sp1C4 = arg0->unk76 - D_800CC6A0;
                    }
                    sp1BC = 28.0f;
                    arg0->unk31C->pad3C[0] = 4;
                    temp_t0_10 = arg0->unk31C;
                    temp_f6 = func_150AD78C((f32) ((D_800CC670 * 0xC) & 0xFF) * 0.024543693f) * 10240.0f;
                    temp_t0_10->padA[1] += 0x10;
                    (*(s16 *)((u8 *)(arg0->unk31C) + 0x10)) = (s16) (s32) temp_f6;
                }
            }
            temp_v0_8 = arg0->unk84.uh;
            if ((temp_v0_8 == 0xBF) || (temp_v0_8 == 0xC1)) {
                sp19F = (s8) ((s8) ((struct49 *)D_800CC6A4)->unk3 / 2);
            }
            temp_t0_11 = arg0->unk31C;
            if (temp_t0_11->unk78 == 0x38) {
                sp19F -= (s32) (*(u16 *)((u8 *)(temp_t0_11) + 0x1A2)) >> 8;
            }
        } else {
            sp1C4 = 0;
            sp1BC = 0.0f;
            *var_a2 |= 0x20;
            var_v0_3 = arg0->unk31C->unk78;
            if ((var_v0_3 == 2) || (var_v0_3 == 0x12) || (var_v0_3 == 0x13) || (var_v0_3 == 0x10) || (var_v0_3 == 0xA) || (var_v0_3 == 0x34) || (((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x10) && (var_v0_3 == 0x16)) || (var_v0_3 == 9) || (var_v0_3 == 0x38) || (var_v0_3 == 0x39) || (var_v0_3 == 0x37) || (var_v0_3 == 0x3B) || (var_v0_3 == 0x15) || (var_v0_3 == 0x26) || (var_v0_3 == 0x3A)) {
                if ((var_v0_3 == 0x10) || (var_v0_3 == 0x14) || (var_v0_3 == 0x3F)) {
                    sp19F = (s8) ((s8) ((struct49 *)D_800CC6A4)->unk3 / 2);
                    var_v0_3 = arg0->unk31C->unk78;
                }
                if ((var_v0_3 == 0xC) || (var_v0_3 == 0x16) || (var_v0_3 == 0x15) || (var_v0_3 == 0x38) || (var_v0_3 == 0x39) || (var_v0_3 == 0x37) || (var_v0_3 == 0x3B) || (var_v0_3 == 0x12) || (var_v0_3 == 9)) {
                    var_f0_3 = (*(f32 *)((u8 *)(arg0->unk31C) + 0x170));
                    if (var_f0_3 > 180.0f) {
                        var_f0_3 -= 360.0f;
                    }
                    sp19F = (s8) (s32) (var_f0_3 * 0.91022223f);
                    temp_t0_12 = arg0->unk31C;
                    var_v0_3 = temp_t0_12->unk78;
                    if (var_v0_3 == 0x38) {
                        sp19F -= (s32) (*(u16 *)((u8 *)(temp_t0_12) + 0x1A2)) >> 8;
                        var_v0_3 = arg0->unk31C->unk78;
                    }
                }
                if ((var_v0_3 != 9) && (var_v0_3 != 0x38) && (var_v0_3 != 0x39) && (var_v0_3 != 0x37) && (var_v0_3 != 0x3B) && (var_v0_3 != 0x15) && (var_v0_3 != 0x26) && (var_v0_3 != 0x3A)) {
                    temp_f4 = (s32) (((*(f32 *)((u8 *)(arg0->unk31C) + 0x16C)) + 90.0f) * 182.04445f);
                    arg0->unk7A = (u16) temp_f4;
                    arg0->unk76 = (u16) temp_f4;
                    goto block_197;
                }
            } else if ((var_v0_3 != 0x14) && (var_v0_3 != 0x3F)) {
                D_800CC6DC |= 0x100;
                ((struct49 *)D_800CC6A4)->unk0 = (u16) ((struct49 *)D_800CC6A4)->unk0 & 0xDFFF;
                D_800CC288 &= ~0x2000;
block_197:
                var_v0_3 = arg0->unk31C->unk78;
            }
            if (var_v0_3 != 9) {
                D_800CC6DC |= 0x200;
                ((struct49 *)D_800CC6A4)->unk0 = (u16) ((struct49 *)D_800CC6A4)->unk0 & 0x7FFF;
                D_800CC288 &= 0xFFFF7FFF;
            }
        }
    }
    if (!(arg0->unk31C->unk4E & 0xF) && (arg0->health != 0) && (arg0->stunned == 0) && (arg0->unk28 == 0.0f) && ((D_800BE616 != 0) || ((temp_v0_9 = arg0->unk31C->unk78, (temp_v0_9 == 9)) && (arg0->unk31C->matrix_physics == 0)) || (temp_v0_9 == 0x16) || (temp_v0_9 == 0x3B)) && ((temp_v0_10 = arg0->unk31C->unk11A, (temp_v0_10 == 2)) || (temp_v0_10 == 0))) {
        temp_a2 = arg0->unk31C->unk78;
        var_v0_4 = 3;
        if ((temp_a2 != 0) && ((arg0->unk31C->unk197 == 0) || (temp_a2 == 0x16)) && (arg0->unk31C->unk19B == 0)) {
            var_v0_4 = 0xF;
        }
        temp_a0 = (u16) ((struct49 *)D_800CC6A4)->unk0 & var_v0_4;
        if (temp_a0 != 0) {
            var_v0_5 = temp_a0;
            if ((arg0->unk31C->unk197 == 0) && (arg0->unk31C->unk198 == 0)) {
                temp_a0_2 = ((struct49 *)D_800CC6A4)->unk3;
                if (temp_a0_2 >= 6) {
                    var_v0_5 |= 8;
                } else if (temp_a0_2 < -5) {
                    var_v0_5 |= 4;
                }
            }
            temp_a0_3 = D_8009952C[var_v0_5];
            arg0->unk31C->unk52 = 2;
            if (temp_a0_3 != 0xFFFF) {
                temp_v0_11 = arg0->unkAA;
                if ((temp_v0_11 == 0) || ((s32) temp_v0_11 >= 0x42)) {
                    arg0->unkAA = 0x41;
                }
                if (arg0->xz_velocity > 12.0f) {
                    arg0->unk31C->pad3C[0] = 4;
                }
                if (arg0->unk7A != arg0->unk76) {
                    arg0->unk31C->pad3C[0] = 0;
                }
                temp_t5 = arg0->unk7A - ((s32) (((struct49 *)D_800CC6A4)->unk2 * D_800CC264) >> 4);
                arg0->unk7A = temp_t5;
                temp_t8 = (((temp_t5 & 0xFFFF) + temp_a0_3) - arg0->unk31C->unk12) - D_800CC6A0;
                sp1C4 = temp_t8;
                sp1BC = 34.0f;
                if (arg0->unk31C->unk197 != 0) {
                    arg0->unk76 = temp_t8 + D_800CC6A0;
                }
                (*(s8 *)((u8 *)(arg0->unk31C) + 0x1B3)) = 1;
            } else {
                arg0->xz_velocity = 0.0f;
            }
        } else if (arg0->unk31C->unk52 != 0) {
            arg0->unk76 = arg0->unk7A;
            if (arg0->unk31C->unk197 != 0) {
                arg0->xz_velocity = 0.0f;
            }
        }
    }
    if ((s8) arg0->unk31C->pad17[0xC] > 0) {
        arg0->disable_run = 0;
        arg0->unk83 = 0;
        sp1BC = 18.0f;
        sp1C4 = arg0->unk76 - D_800CC6A0;
        ((struct49 *)D_800CC6A4)->unk2 = 0;
        ((struct49 *)D_800CC6A4)->unk3 = 0;
        ((struct49 *)D_800CC6A4)->unk0 = 0;
        D_800CC288 = 0;
        sp184 = 1;
        temp_t0_13 = arg0->unk31C;
        temp_t0_13->pad17[0xC] = (s8) temp_t0_13->pad17[0xC] - D_800BE9A0;
        D_800CC6DC |= 0x40;
    }
    if (arg0->unk31C->unk6B != 0) {
        func_15052260(arg0);
    }
    temp_f2 = arg0->unk118;
    var_f12 = temp_f2 - arg0->unk11C;
    if (fabsf(var_f12) > 30.0f) {
        var_f12 = 0.0f;
    }
    arg0->unk11C = temp_f2;
    if (arg0->unk31C->unk84 == 0) {
        arg0->unk31C->unk8A = (u16) ((struct49 *)D_800CC6A4)->unk0;
        arg0->unk31C->unk8C = (u16) D_800CC288;
    }
    if ((arg0->unk84.uh == 0) && (arg0->animation_speed == 0.0f)) {
        sp1B0 = var_f12;
        func_1505E650(arg0, 0x24U, 1.0f, 1.0f, 0.0f, 0.0f, 0);
        var_f12 = sp1B0;
    }
    if (((struct49 *)D_800CC6A4)->unk3 == 0) {
        arg0->unk31C->pad53 = 0;
    }
    if (arg0->unk137 == 0xFF) {
        arg0->unk137 = 0;
    }
    sp1C1 = 0xC;
    temp_t0_14 = arg0->unk31C;
    if (((s16) temp_t0_14->unk8 > 0) || (var_a2_3 = temp_t0_14->unk78, (var_a2_3 == 3))) {
        sp1B0 = var_f12;
        func_1504BE2C((u8 *)arg0, &sp1C4, &sp1BC, &sp19F);
        var_f12 = sp1B0;
        var_a2_3 = arg0->unk31C->unk78;
    }
    sp1B0 = var_f12;
    func_1504C9E4(arg0, sp19F, var_a2_3);
    if (arg0->stunned == 0) {
        if (arg0->unk31C->unk84 != 0) {
            sp1C4 = arg0->unk78;
            sp1BC = arg0->unk44;
        }
        if (sp1BC > 0.0f) {
            arg0->unk31C->unk4C = sp1C4 + D_800CC6A0;
            temp_t0_15 = arg0->unk31C;
            if ((*(u16 *)((u8 *)(temp_t0_15) + 0x32)) & 2) {
                temp_a1 = (*(u16 *)((u8 *)(temp_t0_15) + 0x34));
                var_v0_6 = temp_t0_15->unk4C;
                var_v1_2 = temp_a1;
                var_a0_2 = temp_a1 - var_v0_6;
                if (!((var_a0_2 + 0x2000) & 0xC000)) {
                    temp_t0_15->unk4C = temp_a1;
                    temp_t0_16 = arg0->unk31C;
                    var_v1_2 = (*(u16 *)((u8 *)(temp_t0_16) + 0x34));
                    var_v0_6 = temp_t0_16->unk4C;
                    var_a0_2 = var_v1_2 - var_v0_6;
                }
                if (!((var_a0_2 + 0xA000) & 0xC000)) {
                    arg0->unk31C->unk4C = var_v1_2 + 0x8000;
                    var_v0_6 = arg0->unk31C->unk4C;
                }
                sp1C4 = var_v0_6 - D_800CC6A0;
            }
        } else {
            arg0->unk31C->unk4C = arg0->unk7A;
        }
        if (arg0->in_water != 0) {
            temp_f0 = func_1504B0FC(arg0, sp1B0);
            sp1C4 = arg0->unk31C->unk4C;
            temp_t0_17 = arg0->unk31C;
            temp_v0_12 = (s8) temp_t0_17->pad17[0xB];
            if (temp_v0_12 >= 0) {
                temp_t0_17->pad17[0xB] = temp_v0_12 - D_800BE9A0;
                temp_t0_18 = arg0->unk31C;
                temp_v0_13 = (s8) temp_t0_18->pad17[0xB];
                if ((temp_v0_13 >= 0x5B) && (temp_v0_13 < 0x64)) {
                    temp_t0_18->pad17[0xB] = 0;
                }
            }
            if (arg0->unk31C->pad17[0xA] == 0) {
                sp1BC = temp_f0;
                sp1C4 = arg0->unk76;
                if (!((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x4000)) {
                    temp_t0_19 = arg0->unk31C;
                    if (((s8) temp_t0_19->pad17[0xB] <= 0) && (((arg0->unk118 - 60.0f) - 30.0f) < arg0->y_position)) {
                        temp_t0_19->pad17[0xA] = 1;
                        arg0->disable_run = 0xC;
                    }
                }
            } else {
                if ((D_800CC288 & 0x4000) && (D_800BE616 == 0) && (D_800BE9F0 != 0x29)) {
                    temp_v0_14 = arg0->camera;
                    if ((temp_v0_14 != NULL) && (temp_v0_14->unk2C != 0x100) && !(arg0->unk31C->pad17[9] & 1)) {
                        arg0->unk31C->pad17[0xA] = 0;
                        arg0->unk31C->pad17[0xB] = 0x76;
                        if (((arg0->unk118 - 60.0f) - 30.0f) < arg0->y_position) {
                            arg0->unkB8 = 20.0f;
                        }
                        func_15060A30(0x66F, arg0);
                    }
                }
                arg0->unk31C->pad3C[0] = 4;
                arg0->unkAA = 0x28;
            }
        } else {
            sp1C4 += D_800CC6A0;
        }
        D_800CC69E = sp1C4;
        temp_v0_15 = arg0->unkAA;
        arg0->unk44 = sp1BC;
        if (temp_v0_15 != 0) {
            var_f8 = (f32) temp_v0_15;
            if ((s32) temp_v0_15 < 0) {
                var_f8 += 4294967296.0f;
            }
            sp1BC *= var_f8 * 0.01f;
        }
        if ((s32) arg0->unk13C >= 0x64) {
            sp1BC *= 0.8f;
        }
        if ((arg0->disable_run != 0) || ((s32) arg0->unk81 >= 0x79)) {
            sp1BC = 0.0f;
        }
        func_1504BC38(arg0);
        var_f16 = 4.0f;
        var_f14 = 0.0f;
        if ((arg0->in_water != 0) && (arg0->unk31C->pad17[0xA] == 0)) {
            if ((arg0->stunned == 0) && (arg0->unk84.uh != 0x262)) {
                var_f14 = (f32) ((s8) ((struct49 *)D_800CC6A4)->unk2 / 2);
            }
        } else {
            temp_t0_20 = arg0->unk31C;
            temp_v0_16 = temp_t0_20->unk78;
            if ((temp_v0_16 == 2) || (temp_v0_16 == 0x13) || (temp_v0_16 == 0xA) || (temp_v0_16 == 0x34)) {
                if (temp_t0_20->unk198 != 0) {
                    temp_f0_2 = -(*(f32 *)((u8 *)(temp_t0_20) + 0x170));
                    if ((temp_v0_16 == 2) || (temp_v0_16 == 0x13)) {
                        var_f0_4 = temp_f0_2 + 30.0f;
                    } else {
                        var_f0_4 = -temp_f0_2;
                    }
                    var_f14 = (f32) (s8) (s32) var_f0_4;
                } else {
                    var_f14 = (f32) ((s8) ((struct49 *)D_800CC6A4)->unk3 / 2);
                }
            } else {
                if (arg0->disable_run != 0xFF) {
                    temp_f12 = arg0->unk28;
                    temp_v0_17 = sp1C4 - sp1C6;
                    if ((temp_f12 < 20.0f) && (arg0->xz_velocity < 1.5f)) {
                        var_f14 = arg0->unk44 * 0.3f;
                    } else {
                        var_f14 = arg0->unk44 * 1.75f;
                        var_f2 = fabsf((f32) temp_v0_17 * 0.00390625f * 5.0f);
                        if (var_f2 > 50.0f) {
                            var_f2 = 50.0f;
                        }
                        if (var_f2 < var_f14) {
                            var_f14 = var_f2;
                        }
                        if (temp_f12 > 30.0f) {
                            var_f14 *= 0.6f;
                        }
                        if (temp_v0_17 >= 0) {
                            var_f14 = 0.0f - var_f14;
                        }
                    }
                }
                if (((arg0->unk13C != 0) && (D_800B89C4[D_800D154C->unk13C * 0x32C] != 0x57)) || (temp_t0_20->unk198 != 0) || ((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x2000)) {
                    var_f14 = 0.0f;
                }
            }
        }
        if (arg0->unk31C->pad17[0] != 0) {
            if (arg0->unk84.uh == 0x279) {
                if (arg0->disable_run == 0) {
                    if ((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x8000) {
                        arg0->gravity = 1.1f;
                    } else {
                        temp_f0_3 = arg0->y_velocity;
                        if (temp_f0_3 > 0.0f) {
                            arg0->y_velocity = temp_f0_3 * 0.85f;
                        }
                        arg0->gravity = 2.5f;
                    }
                }
                if (arg0->unk28 > 0.0f) {
                    temp_f0_4 = arg0->unkC4;
                    arg0->unkC4 = temp_f0_4 + (((arg0->unk54 * 4.0f) - temp_f0_4) * 0.15f);
                    arg0->unkB8 = arg0->xz_velocity * 1.5f;
                }
                arg0->unkAA = 0x3C;
                arg0->unk80 = 1;
                arg0->unk83 = 0xFF;
            }
            var_f16 = 12.0f;
            var_f14 *= 0.6f;
        }
        if ((arg0->unk110 == 2) || (arg0->unk84.uh == 0xCD)) {
            var_f14 = -var_f14;
        }
        var_f14_2 = (var_f14 - arg0->unk54) / (var_f16 / *D_800D1550);
        if ((arg0->unk28 < 30.0f) || (arg0->unk31C->pad17[0] != 0)) {
            if (((var_f14_2 > 0.0f) && ((*(f32 *)((u8 *)(arg0->unk31C) + 0x40)) < 0.0f)) || ((temp_f2_2 = (*(f32 *)((u8 *)(arg0->unk31C) + 0x40)), (var_f14_2 < 0.0f)) && (temp_f2_2 > 0.0f))) {
                var_f14_2 = 0.0f;
            } else if (fabsf(var_f14_2 - temp_f2_2) > 2.0f) {
                if (temp_f2_2 < var_f14_2) {
                    var_f14_2 = temp_f2_2 + 2.0f;
                } else {
                    var_f14_2 = temp_f2_2 - 2.0f;
                }
            }
        }
        (*(f32 *)((u8 *)(arg0->unk31C) + 0x40)) = var_f14_2;
        if ((D_800BEAC0 == 0) && (D_800BEE2C == 0)) {
            arg0->unk54 += var_f14_2;
        }
        if (sp1BC != 0.0f) {
            temp_a2_2 = arg0->unk76;
            if (temp_a2_2 != sp1C4) {
                temp_f0_5 = arg0->xz_velocity;
                if (temp_f0_5 < 5.0f) {
                    var_v1_3 = 0x19;
                } else {
                    temp_f10_2 = (s32) ((64.0f - temp_f0_5) * 0.25f);
                    var_v1_3 = (s8) temp_f10_2;
                    if ((s32) arg0->unk31C->unk31 >= 3) {
                        var_v1_3 = (s8) temp_f10_2 + 1;
                    } else if ((s32) arg0->unk81 > 0) {
                        var_v1_3 = (s8) (s32) ((51.0f - temp_f0_5) / 13.0f);
                        if (arg0->y_velocity < -10.0f) {
                            var_v1_3 = 0;
                        }
                    }
                }
                temp_t9 = ((s32) (sp1C4 - temp_a2_2) >> 8) & 0xFF;
                var_a1_3 = temp_t9;
                if (temp_t9 >= 0x80) {
                    var_a1_3 = -temp_t9 & 0xFF;
                }
                if (arg0->unk102 != 0) {
                    var_v1_3 = 5;
                } else if ((var_a1_3 >= 0x51) && (arg0->in_water == 0)) {
                    temp_t0_21 = arg0->unk31C;
                    if (((*(s16 *)((u8 *)(temp_t0_21) + 0x46)) <= 0) && ((s16) temp_t0_21->unk8 <= 0)) {
                        if ((temp_t0_21->unk4E & 0xF) == 1) {
                            if (temp_f0_5 > 7.0f) {
                                var_v1_3 = 0;
                                arg0->xz_velocity = temp_f0_5 - 3.5f;
                            } else {
                                var_v1_3 = 6;
                            }
                        } else if (temp_f0_5 < 7.0f) {
                            if (temp_f0_5 > 3.0f) {
                                var_v1_3 = 0xC;
                                arg0->xz_velocity = 0.0f;
                                if ((s32) arg0->unk83 >= 5) {
                                    temp_v0_18 = arg0->unk31C->unk11A;
                                    if ((temp_v0_18 != 1) && (temp_v0_18 != 3)) {
                                        arg0->unk83 = 4;
                                    }
                                }
                            }
                        } else {
                            sp1BC = 0.0f;
                            var_v1_3 = 0;
                            if (arg0->unkAE == 0) {
                                arg0->xz_velocity -= 2.0f;
                            }
                        }
                    }
                }
                temp_a2_3 = arg0->unk76;
                temp_lo = (s32) (var_v1_3 * D_800CC264) / 100;
                var_v1_4 = (s8) temp_lo;
                if ((s32) arg0->unk13C >= 0x64) {
                    var_v1_4 = (s8) ((s32) ((s8) temp_lo * 2) / 3);
                } else if (arg0->unk110 != 0) {
                    var_v1_4 = 2;
                }
                if (arg0->in_water != 0) {
                    var_v1_4 = (s8) (var_v1_4 / 4);
                }
                temp_v0_19 = arg0->unk31C->pad3C[0];
                if (temp_v0_19 != 0) {
                    var_v1_4 = (s8) ((s32) (temp_v0_19 * D_800CC264) / 100);
                }
                if (var_a1_3 < var_v1_4) {
                    var_v1_4 = var_a1_3;
                }
                if (temp_t9 & 0x80) {
                    arg0->unk76 = temp_a2_3 - (var_v1_4 << 8);
                } else {
                    arg0->unk76 = temp_a2_3 + (var_v1_4 << 8);
                }
            }
        }
        arg0->unk31C->pad3C[0] = 0;
        temp_v0_20 = arg0->unk110;
        if (temp_v0_20 != 0) {
            sp1C1 = 0x10;
            if (temp_v0_20 & 1) {
                sp1C4 = (*(u16 *)((u8 *)(arg0->unk31C) + 0x3E));
            } else {
                sp1C4 = (*(u16 *)((u8 *)(arg0->unk31C) + 0x3E)) ^ 0x8000;
            }
        } else if ((sp1BC == 0.0f) || (arg0->in_water != 0) || (arg0->unk31C->pad17[0] != 0) || (arg0->unk28 < 50.0f)) {
            sp1C4 = arg0->unk76;
        }
        var_t1 = 0;
        if (arg0->unk31C->matrix_physics != 0) {
            sp1C4 = 0x4000;
            sp1C1 = 0x14;
        } else if ((arg0->unk31C->pad17[0] != 0) && (arg0->unk13C == 0)) {
            sp1C2 = 0;
            temp_v0_21 = func_15083E90(6U);
            var_t1 = sp1C2;
            if (temp_v0_21 != NULL) {
                sp12C = temp_v0_21;
                var_t1 = sp1C2;
                if (func_1505A6F8(temp_v0_21, arg0) < 600.0f) {
                    var_t1 = sp1C2;
                    sp1C4 = func_1505A630(sp12C->x_position - arg0->x_position, arg0->z_position - sp12C->z_position, 0);
                } else {
                    arg0->unk31C->pad3C[0] = 5;
                }
            }
        }
        if (arg0->unk31C->unk52 == 0) {
            var_t1 = func_150599C8(arg0, sp1C1, sp1C4) & 0xFF;
        }
        if (((s32) var_t1 >= 0x5B) && (arg0->xz_velocity > 12.0f) && (arg0->in_water == 0) && (arg0->unk81 == 0)) {
            sp1BC = 0.0f;
        }
        if (arg0->unk7A == arg0->unk76) {
            arg0->unk80 = 0;
        }
        temp_t0_22 = arg0->unk31C;
        var_f0_5 = 0.0f;
        temp_v0_22 = temp_t0_22->unk4E;
        if ((temp_v0_22 & 0xF) == 1) {
            var_v1_5 = temp_t0_22->matrix_physics;
            if (temp_t0_22->pad4F[0] != 0) {
                var_f0_5 = 0.27f;
            } else {
                var_f0_5 = 0.8f;
                if (temp_v0_22 == 0x81) {
                    var_f0_5 = 0.2f;
                }
            }
            var_f14_3 = 0.65f;
        } else {
            var_f14_3 = 2.5f;
            if (arg0->unk84.uh == 0x16) {
                var_f14_3 = 3.2f;
                if ((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x2000) {
                    sp1BC = 0.0f;
                }
                var_v1_5 = arg0->unk31C->matrix_physics;
            } else if (arg0->unk13C != 0) {
                var_v1_5 = temp_t0_22->matrix_physics;
                if (arg0->id == 0x13) {
                    var_f14_3 = 0.75f;
                }
                var_f0_5 = 0.75f;
            } else if (arg0->unk110 != 0) {
                sp1BC = 0.0f;
                var_f14_3 = 2.0f;
                var_v1_5 = arg0->unk31C->matrix_physics;
            } else {
                var_v1_5 = temp_t0_22->matrix_physics;
                if ((*(s16 *)((u8 *)(temp_t0_22) + 0x46)) > 0) {
                    var_f0_5 = 4.0f;
                } else {
                    var_f0_5 = 1.0f;
                }
            }
            if (((s16 *)arg0->unk31C)[4] > 0) {
                var_f0_5 = 1.0f;
                var_f14_3 = 2.0f;
            }
        }
        if (var_v1_5 != 0) {
            var_f14_3 = 0.0f;
        }
        func_1505A3A8(sp1BC, arg0, var_f0_5, var_f14_3, var_t1);
        func_1505F298(arg0, D_800CC6A4);
    } else {
        if (arg0->in_water != 0) {
            func_1504B0FC(arg0, sp1B0);
        }
        if (arg0->stunned != 0xFF) {
            func_1506045C(arg0, (u16) ((struct49 *)D_800CC6A4)->unk0, D_800CC288, arg0->unk28, 0);
            temp_v0_23 = arg0->unk84.uh;
            arg0->unk54 = 0.0f;
            arg0->disable_run = 0;
            arg0->unk83 = 0;
            if (((temp_v0_23 == 0xF1) || (temp_v0_23 == 0xF6)) && (arg0->unk28 == 0.0f)) {
                arg0->y_velocity = 0.0f;
                arg0->gravity = 0.0f;
                arg0->unkF8 |= 0x01008000;
            }
            if (!(arg0->unk10B & 1) && (arg0->xz_velocity < 2.0f) && ((s32) arg0->stunned < 0xD2) && (arg0->unk28 < 10.0f) && (arg0->y_velocity < 0.5f)) {
                arg0->stunned = 1;
                arg0->unk10C = 1;
                arg0->unk105 = 3;
            }
            func_150585F0(arg0, 0x3DCCCCCD);
            temp_v0_24 = arg0->unk10B;
            if (temp_v0_24 & 0x40) {
                var_f0_6 = arg0->y_position - D_800CC698;
                if (var_f0_6 < 400.0f) {
                    if (var_f0_6 < 10.0f) {
                        var_f0_6 = 10.0f;
                    }
                    temp_t6 = arg0->unk76 + ((s32) (D_800CC264 * 0x1400) / 100);
                    arg0->unk76 = temp_t6;
                    arg0->xz_velocity = 3.0f;
                    arg0->y_velocity = (var_f0_6 * 0.06f) + 6.0f;
                    func_1505A184(temp_t6 & 0xFFFF, var_f0_6, 0.0f, &sp120, &sp11C, &sp118);
                    *(f32 *)&arg0->unk31C->unk28 = (sp120 + D_800CC690);
                    *(f32 *)&arg0->unk31C->unk2C = (sp11C + D_800CC694);
                    arg0->unk31C->unk30 = 2;
                } else {
                    arg0->unk10B = temp_v0_24 & 0xFFBF;
                    arg0->xz_velocity = 30.0f;
                    arg0->y_velocity = 90.0f;
                    arg0->gravity = 4.0f;
                }
            }
            if (arg0->unk10B & 0x80) {
                arg0->unk228 = 0;
                arg0->immune = 0x5A;
                if ((arg0->unk28 == 0.0f) && (arg0->y_velocity < 24.0f)) {
                    arg0->unk10C = 0;
                    if (arg0->unk10B & 0x20) {
                        (*(s16 *)((u8 *)(arg0->unk31C) + 0x46)) = 0xFA0;
                    }
                }
                if (sp1BC > 5.0f) {
                    sp1C4 += D_800CC6A0;
                    arg0->unk80 = 1;
                    func_150599C8(arg0, 6U, sp1C4);
                    func_1505A184(sp1C4, sp1BC, 0.0f, &sp114, &sp110, &sp10C);
                    temp_f0_6 = arg0->unk16C;
                    temp_f2_3 = arg0->unk170;
                    arg0->unk16C = temp_f0_6 + ((sp114 - temp_f0_6) * 0.1f);
                    arg0->unk76 = arg0->unk7A;
                    arg0->unk170 = temp_f2_3 + ((sp110 - temp_f2_3) * 0.1f);
                }
            }
        }
    }
    temp_t0_23 = arg0->unk31C;
    if ((temp_t0_23->pad98[0] != 0) && (arg0->stunned == 0)) {
        var_t1_2 = ((struct49 *)D_800CC6A4)->unk2;
        temp_t0_23->unk31 = 0;
        arg0->unk54 = 0.0f;
        arg0->disable_run = 0xFF;
        temp_v0_25 = arg0->camera;
        arg0->y_velocity = 0.0f;
        arg0->gravity = 0.0f;
        arg0->unk81 = 1;
        var_f2_2 = (f32) ((struct49 *)D_800CC6A4)->unk3;
        arg0->xz_velocity *= 0.95f;
        if ((temp_v0_25 != NULL) && (temp_v0_25->unk2C == 0x100)) {
            var_f2_2 = 0.0f;
            var_t1_2 = 0;
        }
        var_f14_4 = var_f2_2;
        if ((var_f2_2 == 0.0f) || (var_f2_2 < -40.0f)) {
            var_f14_4 = 40.0f;
            var_v1_6 = 0xA4;
            if (var_f2_2 < -40.0f) {
                var_f2_2 *= 2.0f;
            }
        } else {
            var_v1_6 = 0x16A;
            if (var_f2_2 > 0.0f) {
                var_v1_6 = 0x98;
            } else {
                var_f14_4 = -var_f2_2;
            }
        }
        temp_t0_24 = arg0->unk31C;
        (*(f32 *)((u8 *)(temp_t0_24) + 0xA0)) = (f32) ((*(f32 *)((u8 *)(temp_t0_24) + 0xA0)) + (var_f2_2 * (0.08f / (*(f32 *)((u8 *)((*(void **)((u8 *)(temp_t0_24) + 0x9C))) + 0x2C))) * *D_800D1550));
        temp_t0_25 = arg0->unk31C;
        temp_f12_2 = (*(f32 *)((u8 *)(temp_t0_25) + 0xA0));
        if (temp_f12_2 > 1.0f) {
            (*(f32 *)((u8 *)(temp_t0_25) + 0xA0)) = 1.0f;
        } else if (temp_f12_2 < 0.0f) {
            sp108 = var_v1_6;
            spFE = (s16) var_t1_2;
            sp104 = var_f14_4;
            func_151AE814((u8 *) arg0);
            var_v1_6 = sp108;
            var_t1_2 = (s8) spFE;
            var_f14_4 = sp104;
            arg0->gravity = 5.0f;
        }
        arg0->unk1CC = arg0->y_position;
        arg0->unk31C->unk54 = 8;
        temp_t5_2 = arg0->unk76 + ((s32) (var_t1_2 * D_800CC264) / 5);
        arg0->unk78 = temp_t5_2;
        arg0->unk7A = temp_t5_2;
        arg0->unk76 = temp_t5_2;
        func_1505E650(arg0, var_v1_6 & 0xFFFF, var_f14_4 * 0.025f, 6.0f, 0.0f, 0.0f, 0);
    }
    temp_v1_4 = arg0->unk31C->unk95;
    if ((temp_v1_4 != 0) && (arg0->stunned == 0)) {
        temp_v0_26 = arg0->camera;
        if ((temp_v0_26 != NULL) && (temp_v0_26->unk2C != 0x100)) {
            temp_a0_4 = (((temp_v1_4 & ~0x80) - 1) * 0x34) + D_800D34B8;
            var_f0_7 = (f32) ((struct49 *)D_800CC6A4)->unk3;
            if ((arg0->in_water != 0) && (arg0->y_position < arg0->unk118)) {
                arg0->unk31C->pad96 = 8;
            }
            temp_v0_27 = arg0->unk31C->pad96;
            if (temp_v0_27 != 0) {
                arg0->unk31C->pad96 = temp_v0_27 - 1;
                var_f0_7 = 60.0f;
            }
            *(f32 *)&arg0->unk31C->unk28 = (f32) (*(s16 *)((u8 *)(temp_a0_4) + 0));
            *(f32 *)&arg0->unk31C->unk2C = (f32) (*(s16 *)((u8 *)(temp_a0_4) + 4));
            arg0->unk31C->unk30 = 0xA;
            arg0->unk31C->unk31 = 0;
            arg0->xz_velocity = 0.0f;
            arg0->unk54 = 0.0f;
            arg0->disable_run = 0xFF;
            arg0->gravity = 0.0f;
            arg0->unk81 = 1;
            arg0->unk80 = 1;
            arg0->unk76 = (s32) ((*(f32 *)((u8 *)(temp_a0_4) + 0x10)) * 182.04445f) - 0x4000;
            arg0->y_velocity = var_f0_7 * 0.14f;
            if (arg0->unk31C->unk97 != 0) {
                arg0->y_velocity = 0.0f;
            }
            arg0->unk1CC = arg0->y_position;
            arg0->unk31C->unk54 = 8;
        }
    }
    if (arg0->unk31C->unk6B == 0) {
        func_15059C84(arg0);
        temp_t0_26 = arg0->unk31C;
        temp_v0_28 = (s8) temp_t0_26->unk30;
        if (temp_v0_28 > 0) {
            temp_t0_26->unk30 = temp_v0_28 - D_800BE9A0;
            temp_t0_27 = arg0->unk31C;
            temp_f0_7 = arg0->x_position;
            temp_f2_4 = arg0->z_position;
            arg0->x_position = temp_f0_7 + (((*(f32 *)&temp_t0_27->unk28) - temp_f0_7) * 0.2f);
            arg0->z_position = temp_f2_4 + (((*(f32 *)&temp_t0_27->unk2C) - temp_f2_4) * 0.2f);
        }
        func_15021834(arg0, 0, -1);
        func_1505A770(arg0);
        func_1505D6F0(arg0, D_800C3E78);
        if ((D_800CC68C != 0) && ((s16) arg0->unk31C->unk8 <= 0) && (arg0->unk13C == 0)) {
            temp_v0_29 = &D_800CC2D0[D_800CC68C];
            temp_v0_30 = func_1505A630(temp_v0_29->x_position - arg0->x_position, arg0->z_position - temp_v0_29->z_position, 0);
            if ((arg0->unk28 == 0.0f) && (sp1BC > 15.0f) && (((D_800CC69E - temp_v0_30) - 0x4000) & 0x8000)) {
                var_f14_5 = 0.1f;
                var_a0_3 = 1;
                temp_v0_31 = &D_800CC2D0[D_800CC68C];
                if (temp_v0_31->id == 0x61) {
                    if (arg0->unk84.uh == 0x7A) {
                        temp_a0_5 = temp_v0_31->unk7A;
                        temp_t5_3 = ((arg0->unk76 - temp_a0_5) + 0x2000) & 0xC000;
                        temp_t9_2 = temp_a0_5 + temp_t5_3;
                        if (temp_t5_3 & 0x4000) {
                            temp_v0_31->unk218 = NULL;
                            temp_v0_31->unk232 = 2;
                            temp_v0_31->unk76 = temp_t9_2;
                            arg0->unk76 = temp_t9_2;
                            arg0->unk31C->pad3C[0] = 1;
                            arg0->unk54 *= 0.4f;
                        }
                    }
                } else {
                    var_f16_2 = 0.3f;
                    var_f18 = 0.5f;
                    temp_f0_8 = fabsf(arg0->y_position - temp_v0_31->y_position);
                    spE0 = temp_f0_8;
                    if (temp_f0_8 > 30.0f) {
                        spE0 = 30.0f;
                    }
                    spE0 = (2.0f * (f32) temp_v0_31->unkE4) - spE0;
                    arg0->unk54 *= 0.6f;
                    arg0->xz_velocity = D_800CC2D0[D_800CC68C].unk44;
                    temp_v0_32 = &D_800CC2D0[D_800CC68C];
                    temp_f12_3 = temp_v0_32->unk44;
                    temp_f2_5 = temp_v0_32->xz_velocity;
                    if (temp_f12_3 < temp_f2_5) {
                        spDC = temp_f2_5;
                    } else {
                        spDC = temp_f12_3;
                    }
                    arg0->unk31C->pad3C[0] = (u8) (u32) ((32.0f - spDC) * 0.125f);
                    var_v0_7 = &D_800CC2D0[D_800CC68C];
                    if (var_v0_7->id == 0x34) {
                        if (var_v0_7->unk251 != 1) {
                            var_a0_3 = 0;
                        }
                        sp1A0 = 0x23;
                        arg0->unk31C->pad3C[0] = 2;
                        var_f14_5 = 0.3f;
                        if (arg0->xz_velocity > 5.0f) {
                            var_f14_5 = 0.6f;
                        }
                        var_v0_7 = &D_800CC2D0[D_800CC68C];
                    } else {
                        sp1A0 = 0x18;
                    }
                    if ((sp1A0 != arg0->unk84.uh) && (var_v0_7->id != 0x17)) {
                        D_800D1580 = -0xF7FED5;
                        spD3 = var_a0_3;
                        spD4 = var_f14_5;
                        spCC = 0.3f;
                        spC8 = 0.5f;
                        func_1506E8D8();
                        var_v0_7 = &D_800CC2D0[D_800CC68C];
                        var_a0_3 = spD3;
                        var_f14_5 = spD4;
                        var_f16_2 = spCC;
                        var_f18 = spC8;
                    }
                    temp_v1_5 = (s16) var_v0_7->unk224;
                    if (temp_v1_5 != 0) {
                        var_f16_2 = (f32) temp_v1_5 * 0.01f;
                    }
                    if (var_a0_3 != 0) {
                        temp_f6_2 = spE0 * 1.2f;
                        spE0 = temp_f6_2;
                        spC8 = var_f18;
                        spCC = var_f16_2;
                        spD4 = var_f14_5;
                        func_1505A184(arg0->unk76, temp_f6_2, 0.0f, &spE0, &spDC, &spD8);
                        temp_f0_9 = arg0->x_position;
                        var_f16_2 = spCC;
                        var_f18 = spC8;
                        temp_f2_6 = arg0->z_position;
                        temp_v0_33 = &D_800CC2D0[D_800CC68C];
                        arg0->x_position = temp_f0_9 + ((((temp_v0_33->x_position - spE0) + temp_v0_33->unkBC) - temp_f0_9) * spD4);
                        temp_v0_34 = &D_800CC2D0[D_800CC68C];
                        arg0->z_position = temp_f2_6 + ((((temp_v0_34->z_position - spDC) + temp_v0_34->unk148) - temp_f2_6) * spD4);
                        var_v0_7 = &D_800CC2D0[D_800CC68C];
                        var_v0_7->unk76 = arg0->unk76;
                    }
                    var_v0_7->unk87 = 1;
                    var_v1_7 = var_v0_7->id;
                    spE0 = arg0->unk44 * var_f16_2;
                    if (var_v1_7 == 0x25) {
                        var_f18 = 1.0f;
                        spE0 = arg0->unk44 * 0.6f;
                        temp_t0_28 = arg0->unk31C;
                        arg0->xz_velocity += 2.0f;
                        temp_t0_28->pad3C[0] += 3;
                        var_v0_7 = &D_800CC2D0[D_800CC68C];
                        var_v1_7 = var_v0_7->id;
                    }
                    if (var_v1_7 != 0x34) {
                        temp_f2_7 = var_v0_7->xz_velocity;
                        if (temp_f2_7 < spE0) {
                            var_v0_7->xz_velocity = temp_f2_7 + (var_f18 * D_800BE9A4);
                        }
                    } else {
                        arg0->xz_velocity = var_v0_7->xz_velocity;
                    }
                }
            }
        }
    }
    if ((D_800BE616 != 0) && (D_800CC268 != 0) && ((*(u8 *)((u8 *)(arg0->unk31C) + 0x1AC)) != 0)) {
        func_15063168(arg0);
    }
    arg0->unk40 = (f32) (arg0->unk7A + 0x4000) * 0.005493164f;
    func_15021834(arg0, 0, -1);
    sp198 = arg0->x_position;
    sp194 = arg0->z_position;
    if (!(arg0->unkF8 & 0x8000)) {
        func_15055E50(arg0, arg0->unk1E4);
        if (arg0->unkF4 & 0x100000) {
            sp180 = 30000.0f;
        } else {
            sp180 = arg0->old_y_position;
        }
        if ((arg0->unk118 != -10000.0f) || (temp_a3 = &arg0->unk18C, ((arg0->unkF8 & 2) == 0)) || (sp64 = temp_a3, (func_150A44A4(arg0->x_position, arg0->z_position, arg0->unk188, temp_a3, &spC4) == 0))) {
            temp_f0_10 = arg0->y_position;
            temp_a1_2 = &arg0->unk18C;
            sp64 = temp_a1_2;
            func_1510EE3C(&arg0->unk188, temp_a1_2, &spC4, &arg0->unk118, &arg0->unk184, arg0->pad1A2, arg0->x_position, temp_f0_10, arg0->z_position, sp180, 0, arg0, (s32) 0xC61C4000 /* -10000.0f */, *(s32 *)&temp_f0_10, arg0->unkF8 & 0x04000000);
            temp_f0_11 = (f32) (*(s16 *)((u8 *)(arg0) + 0x120));
            if (arg0->unk118 < temp_f0_11) {
                arg0->unk118 = temp_f0_11;
            }
        }
        temp_f0_12 = arg0->y_position;
        if (temp_f0_12 < spC4) {
            spC0 = 30.0f;
        } else {
            spC0 = 15.0f;
        }
        temp_v0_35 = arg0->unkF8;
        if ((temp_v0_35 & 4) && (temp_t0_29 = arg0->unk31C, (temp_t0_29->unk54 <= 0)) && (temp_t0_29->unk6B == 0) && (arg0->unk137 == 0) && (arg0->unk65 == 0) && ((temp_t0_29->unk84 == 0) || (arg0->old_x_position != arg0->x_position) || (arg0->old_y_position != temp_f0_12) || (arg0->old_z_position != arg0->z_position))) {
            if (temp_v0_35 & 0x08000000) {
                D_800CC1F3 = 1;
            }
            if (arg0->unk31C->unk4E == 2) {
                D_800CC1F4 = 1;
            }
            spBC = arg0->y_velocity;
            func_15044670(arg0->old_x_position, arg0->old_y_position, *(s32 *)&arg0->old_z_position, arg0, 1, 1);
            D_800CC1F4 = 0;
            D_800CC1F3 = 0;
            if ((arg0->stunned != 0) && (arg0->y_velocity == 0.0f) && (spBC < 0.0f) && (spBC > -20.0f)) {
                arg0->y_velocity = spBC;
            }
        } else {
            D_800CC218 = -32768.0f;
            D_800CC214 = -32768.0f;
        }
        if ((sp198 != arg0->x_position) || (sp194 != arg0->z_position)) {
            arg0->unkF4 |= 0x10000;
            if ((arg0->unk118 == -10000.0f) && (spC4 == -10000.0f) && (arg0->unkF8 & 2)) {
                if (func_150A44A4(arg0->x_position, arg0->z_position, arg0->unk188, sp64, &spC4) == 0) {
                    goto block_593;
                }
            } else {
block_593:
                temp_f0_13 = arg0->y_position;
                func_1510EE3C(&arg0->unk188, sp64, &spC4, &arg0->unk118, &arg0->unk184, arg0->pad1A2, arg0->x_position, temp_f0_13, arg0->z_position, sp180, 0, arg0, (s32) 0xC61C4000 /* -10000.0f */, *(s32 *)&temp_f0_13, arg0->unkF8 & 0x04000000);
                temp_f0_14 = (f32) (*(s16 *)((u8 *)(arg0) + 0x120));
                if (arg0->unk118 < temp_f0_14) {
                    arg0->unk118 = temp_f0_14;
                }
            }
            temp_v0_36 = func_1505A630(arg0->x_position - sp198, sp194 - arg0->z_position, 0);
            temp_t0_30 = arg0->unk31C;
            var_a2_4 = temp_t0_30->unk4E;
            temp_a1_3 = arg0->unk76 - temp_v0_36;
            temp_a0_6 = temp_a1_3 & 0xFFFF;
            temp_t1 = temp_v0_36;
            if (var_a2_4 == 2) {
                if ((temp_a0_6 >= 0x1E01) && (temp_a0_6 < 0xE200)) {
                    temp_t8_2 = (temp_a1_3 - 0x8000) & 0xFFFF;
                    if (temp_t8_2 & 0x8000) {
                        var_v1_8 = ((temp_t8_2 >> 2) + 0x9800) & 0xFFFF;
                    } else {
                        var_v1_8 = ((temp_t8_2 >> 2) + 0x2800) & 0xFFFF;
                    }
                    arg0->unk76 = temp_t1 - var_v1_8;
                    if (temp_t0_30->unk44 <= 0) {
                        temp_v0_37 = arg0->health;
                        if ((temp_v0_37 == 1) || ((temp_a0_6 >= 0x5E01) && (temp_a0_6 < 0xA200))) {
                            arg0->health = 0;
                            sp5C = temp_a0_6;
                            func_150D5F7C(arg0, 0xFF, 1);
                            func_1507CD64(arg0, 8);
                        } else if (temp_v0_37 != 0) {
                            if (D_800BE616 == 0) {
                                D_800D1580 = -0xFDFE2A;
                                sp5C = temp_a0_6;
                                func_1506E9D8();
                            }
                            arg0->health -= 1;
                        }
                        arg0->unk31C->unk44 = 0x14;
                    }
                }
                temp_f0_15 = arg0->xz_velocity;
                if (temp_f0_15 > 30.0f) {
                    arg0->disable_run = 0xC;
                    arg0->xz_velocity = temp_f0_15 * 0.7f;
                }
                if ((arg0->health != 0) && (func_100107F8(arg0) == 0)) {
                    D_800D1580 = -0xF7FCF6;
                    func_1506E5FC();
                }
            } else {
                temp_v1_6 = arg0->in_water;
                if (temp_v1_6 == 0) {
                    if (arg0->unk28 > 60.0f) {
                        if ((temp_a0_6 >= 0x5E01) && (temp_a0_6 < 0xA200) && (temp_v1_6 != 0x64) && (arg0->xz_velocity > 14.0f)) {
                            arg0->xz_velocity = 14.0f;
                        }
                    } else if ((temp_t0_30->pad17[0] == 0) && ((*(u8 *)((u8 *)(temp_t0_30) + 0x1B3)) == 0) && (arg0->unk13C == 0) && (temp_a0_6 >= 0x5E01) && (temp_a0_6 < 0xA200) && ((temp_f0_16 = arg0->xz_velocity, (temp_f0_16 > 10.0f)) || (((*(s32 *)((u8 *)(temp_t0_30) + 4)) == 0) && (temp_f0_16 > 2.0f)))) {
                        if (temp_f0_16 > 14.0f) {
                            arg0->xz_velocity = 14.0f;
                            var_a2_4 = arg0->unk31C->unk4E;
                        }
                        if ((var_a2_4 == 0) && (arg0->unk31C->unk11A == 0)) {
                            sp1A0 = 0x7A;
                            if ((arg0->unk81 == 0) && (arg0->unk83 == 0)) {
                                arg0->unk40 = (f32) (temp_t1 - 0x4000) * 0.005493164f;
                            }
                        }
                    }
                }
            }
        }
        temp_t6_2 = ((u32) arg0->unk184 >> 0x1C) & 7;
        D_800CC69C = temp_t6_2;
        if ((temp_t6_2 & 0xFF) >= 7) {
            D_800CC69C = 0;
        }
        arg0->unk180 = spC4;
        arg0->unk31C->pad4F[0] = 0;
        temp_v0_38 = arg0->unk31C->unk4E;
        if ((temp_v0_38 & 0xF) == 1) {
            if (arg0->gravity < 1.0f) {
                arg0->gravity = 5.0f;
            }
            if ((spC4 + 45.0f) < arg0->unk118) {
                arg0->unk31C->pad4F[0] = 1;
                spC0 = 0.0f;
            }
        } else if (temp_v0_38 == 2) {
            if (spC4 == -10000.0f) {
                arg0->health = 0;
                func_150D5F7C(arg0, 0xFF, 1);
                func_1507CD64(arg0, 8);
            }
            if ((s8) arg0->unk31C->pad4F[1] <= 0) {
                func_1504CA60(arg0);
            }
            arg0->unkCC = 0x1E;
            arg0->unkCE = arg0->unkCC;
            temp_v1_7 = (*(u16 *)((u8 *)(arg0->unk31C) + 0x12C));
            if ((D_800BE9E4 < (s32) temp_v1_7) && (arg0->health != 0)) {
                (*(u16 *)((u8 *)(arg0->unk31C) + 0x12C)) = (u16) (temp_v1_7 - D_800BE9E4);
                arg0->xz_velocity = 254.0f;
            } else {
                (*(u16 *)((u8 *)(arg0->unk31C) + 0x12C)) = 0U;
            }
            temp_t0_31 = arg0->unk31C;
            if ((temp_t0_31->unk8C & 0x2000) && (arg0->health != 0)) {
                func_150D7CA0(arg0, temp_t0_31->unk75 & 0x7F);
            }
        }
        if ((arg0->y_position < (spC4 + spC0)) && (arg0->y_velocity < 0.0f) && ((spC0 > 20.0f) || (arg0->unk28 == 0.0f))) {
            arg0->y_position = spC4 - 1.0f;
        }
        temp_t0_32 = arg0->unk31C;
        if ((temp_t0_32->unk4E == 2) || (temp_t0_32->matrix_physics != 0)) {
            func_1505B5F8(arg0, arg0->unk180);
        } else {
            func_1505A9AC(arg0, arg0->unk180);
        }
        if ((u8) arg0->unk31C->unk95 != 0) {
            arg0->unkB8 = 0.0f;
            if (arg0->stunned == 0) {
                temp_v0_39 = arg0->camera;
                if ((temp_v0_39 != NULL) && (temp_v0_39->unk2C != 0x100)) {
                    temp_t0_33 = arg0->unk31C;
                    temp_v1_8 = ((((u8) temp_t0_33->unk95 & ~0x80) - 1) * 0x34) + D_800D34B8;
                    var_f2_3 = (f32) ((struct49 *)D_800CC6A4)->unk3;
                    if (temp_t0_33->pad96 != 0) {
                        var_f2_3 = 60.0f;
                    }
                    temp_f0_17 = arg0->y_position;
                    temp_f12_4 = var_f2_3 * 0.025f;
                    arg0->unk1CC = temp_f0_17;
                    var_f16_3 = temp_f12_4;
                    temp_f14 = (f32) ((*(s16 *)((u8 *)(temp_v1_8) + 2)) + (*(s16 *)((u8 *)(temp_v1_8) + 8)));
                    if (temp_t0_33->unk97 != 0) {
                        var_f16_3 = 1.0f;
                        arg0->unk83 = 0xFF;
                        arg0->disable_run = 0xC;
                        arg0->unk100 |= 0x20;
                        var_v0_8 = 0x31A;
                    } else {
                        if ((temp_f14 <= temp_f0_17) && (var_f2_3 >= 0.0f)) {
                            var_f16_3 = 1.0f;
                            var_v0_8 = 0x206;
                        } else {
                            var_v0_8 = 0x297;
                            if (var_f2_3 >= 0.0f) {
                                var_v0_8 = 0x193;
                            } else {
                                var_f16_3 = -temp_f12_4;
                            }
                        }
                        temp_t7_2 = arg0->unk184 & ~0x1F;
                        arg0->unk184 = temp_t7_2;
                        if (D_800BE9F0 == 0x23) {
                            arg0->unk184 = temp_t7_2 | 9;
                        } else {
                            arg0->unk184 |= 3;
                        }
                        temp_f0_18 = arg0->y_position;
                        if ((temp_f14 - 80.0f) <= temp_f0_18) {
                            temp_t0_34 = arg0->unk31C;
                            if (!((u8) temp_t0_34->unk95 & 0x80)) {
                                arg0->unk137 = 2;
                                var_f16_3 = 3.0f;
                                var_v0_8 = 0x262;
                                temp_t0_34->unk95 = 0;
                            } else if (temp_f14 <= temp_f0_18) {
                                var_f16_3 = 1.0f;
                                var_v0_8 = 0x206;
                                arg0->y_velocity = 0.0f;
                                arg0->y_position = temp_f14;
                            }
                        } else if (temp_f0_18 < (f32) (*(s16 *)((u8 *)(temp_v1_8) + 2))) {
                            arg0->disable_run = 0;
                            arg0->unk31C->unk95 = 0;
                            arg0->gravity = 4.0f;
                        }
                        if (((u8) arg0->unk31C->unk95 == 0) && (arg0->in_water != 0)) {
                            arg0->gravity = 0.0f;
                        }
                    }
                    if (var_v0_8 != -1) {
                        func_1505E650(arg0, var_v0_8 & 0xFFFF, var_f16_3, 6.0f, 0.0f, 0.0f, 0);
                    }
                }
            }
            if (arg0->unk28 == 0.0f) {
                temp_t0_35 = arg0->unk31C;
                if (temp_t0_35->unk97 == 0) {
                    temp_t0_35->unk95 = 0;
                    arg0->disable_run = 6;
                    arg0->gravity = 4.0f;
                }
            }
        }
    }
    if ((arg0->unk28 == 0.0f) && (arg0->unk31C->unk4E != 2) && (arg0->health != 0) && ((arg0->unk184 & 0x1F) == 0xE)) {
        func_1505D024(arg0, 1, arg0->unk7A, -1);
        arg0->unk10B |= 0x80;
    }
    if ((arg0->unk180 < -9000.0f) && (arg0->y_velocity < -120.0f)) {
        arg0->unk31C->unk36 += D_800BE9A0;
        if ((s32) arg0->unk31C->unk36 >= 0x24) {
            func_1506D538();
        }
    } else {
        arg0->unk31C->unk36 = 0;
    }
    func_15051558(arg0, sp198, sp194, sp1C4);
    temp_t0_36 = arg0->unk31C;
    temp_a2_4 = temp_t0_36->unk4E;
    if (temp_a2_4 == 0) {
        if ((arg0->unk28 > 5.0f) && (arg0->unk137 == 0) && (arg0->disable_run == 0) && (temp_t0_36->unk78 == 0) && (temp_t0_36->pad17[0] == 0) && (arg0->stunned == 0) && ((*(s16 *)((u8 *)(temp_t0_36) + 0x46)) == 0) && (arg0->in_water == 0) && (arg0->unk13C == 0) && (arg0->unk180 != -10000.0f) && (arg0->health != 0) && ((s16) temp_t0_36->unk8 == 0) && (temp_a2_4 == 0) && (arg0->unk110 == 0) && ((arg0->unk1CC - arg0->y_position) < 450.0f)) {
            var_v0_9 = 0;
            if (D_800CC214 != -32768.0f) {
                sp8C = D_800CC214;
                var_v0_9 = 1;
                sp96 = (s16) (s32) (((arg0->unk40 + D_800CC1B4) - 90.0f) / 1.40625f);
            } else if ((D_800CC218 != -32768.0f) && (arg0->xz_velocity < 10.0f)) {
                sp8C = D_800CC218;
                var_v0_9 = 2;
                sp96 = (s16) (s32) ((arg0->unk40 + D_800CC1B8 + 90.0f) / 1.40625f);
            }
            if (var_v0_9 != 0) {
                temp_t4 = sp96 << 8;
                arg0->unk76 = temp_t4;
                arg0->unk7A = temp_t4;
                arg0->y_position = sp8C - 25.0f;
                arg0->x_position = D_800CC21C;
                arg0->z_position = D_800CC1B0;
                temp_t0_36->pad53 = 1;
                arg0->unk31C->unk55 = 0;
                arg0->disable_run = 0xFF;
                arg0->unk137 = 1;
                arg0->unk81 = 1;
                arg0->xz_velocity = 0.0f;
                arg0->y_velocity = 0.0f;
                arg0->gravity = 0.0f;
                arg0->unk1CC = arg0->y_position;
                func_1505E650(arg0, 0x42U, 1.0f, 1.0f, 0.0f, 0.0f, 0);
                arg0->unk31C->unk44 = 0xC;
            }
        }
        if (arg0->y_velocity < 5.0f) {
            temp_f2_8 = arg0->unk118;
            if ((temp_f2_8 != -10000.0f) && (arg0->y_position < (temp_f2_8 - 60.0f)) && (arg0->in_water != 1)) {
                var_f0_8 = 4.0f;
                arg0->unk31C->unk55 = 0;
                arg0->unk31C->unk31 = 0;
                arg0->in_water = 1;
                arg0->unk164 = 0.0f;
                arg0->unk168 = 0.0f;
                arg0->unk162 = 0;
                arg0->unk1CC = arg0->y_position;
                arg0->xz_velocity *= 0.5f;
                arg0->unk76 = arg0->unk7A;
                arg0->unk31C->pad17[0xB] = 0;
                if (D_800BE9B4 == 0) {
                    arg0->unk31C->pad17[0xA] = 1;
                    arg0->unkB2 = 0;
                }
                if ((arg0->unk31C->pad17[9] & 1) && (D_800BE616 == 0)) {
                    sp88 = 4.0f;
                    func_15083568(arg0, 0x38, 0.0f, 0);
                    var_f0_8 = sp88;
                }
                if (arg0->unk110 == 2) {
                    temp_t9_3 = arg0->unk76 ^ 0x8000;
                    arg0->unk76 = temp_t9_3;
                    arg0->unk7A = temp_t9_3;
                    arg0->xz_velocity = 20.0f;
                    arg0->unkB8 = -30.0f;
                }
                temp_v0_40 = arg0->unk84.uh;
                arg0->unk110 = 0;
                if ((temp_v0_40 == 0x3C) || (temp_v0_40 == 0x3B)) {
                    var_f0_8 = 0.0f;
                    arg0->y_velocity *= 0.5f;
                    arg0->gravity = -2.4f;
                    arg0->unkB8 = 89.0f;
                } else {
                    arg0->gravity = -3.0f;
                    arg0->y_velocity *= 0.4f;
                }
                arg0->stunned = 0;
                arg0->target_speed = 0.0f;
                arg0->unk81 = 0;
                arg0->unkA9 = 0;
                if (((u8) arg0->unk31C->unk95 == 0) && (arg0->health != 0)) {
                    func_1506B100(0xD1, 2.0f, var_f0_8);
                    arg0->disable_run = 0;
                }
                if (arg0->health == 0) {
                    arg0->disable_run = 0xFF;
                    func_1507CD64(arg0, 4);
                    arg0->stunned = 0xFF;
                }
            }
        }
    }
    func_1505250C(arg0, 1);
    if (arg0->unkCC < -0x5D) {
        arg0->health = 0;
        func_1507CD64(arg0, 3);
    }
    if (arg0->unkD0 != 0) {
        func_1505C7D8(arg0, D_800C3E78);
    }
    if ((s32) arg0->unk7F >= 9) {
        arg0->unk80 = 1;
    }
    temp_v1_9 = arg0->unk83;
    if (temp_v1_9 != 0) {
        if (temp_v1_9 != 0xFF) {
            if ((s32) D_800BE9A0 >= (s32) temp_v1_9) {
                arg0->unk83 = 0;
            } else {
                arg0->unk83 = temp_v1_9 - D_800BE9A0;
            }
        }
        temp_v0_41 = arg0->unk84.uh;
        if ((temp_v0_41 == 0x36) || (temp_v0_41 == 0x19D)) {
            temp_f0_19 = arg0->xz_velocity;
            if ((temp_f0_19 > 8.0f) && (arg0->disable_run == 0)) {
                arg0->unk83 = 0;
                sp1BC = temp_f0_19;
            }
        }
    } else {
        arg0->unkAA = 0;
    }
    temp_v0_42 = arg0->unkA8;
    if (temp_v0_42 != 0) {
        arg0->unkA8 = temp_v0_42 - 1;
    }
    temp_v0_43 = arg0->unk102;
    temp_t9_4 = temp_v0_43 - 1;
    if (temp_v0_43 != 0) {
        arg0->unk102 = temp_t9_4;
        arg0->gravity = 5.0f;
        if (!(temp_t9_4 & 0xFF)) {
            func_1506AF74();
        }
    }
    temp_v1_10 = arg0->unk100;
    if (temp_v1_10 & 1) {
        temp_t0_37 = arg0->unk31C;
        if (temp_t0_37->unk78 == 0) {
            temp_v0_44 = temp_t0_37->unk11A;
            if ((temp_v0_44 != 1) && (temp_v0_44 != 3) && (arg0->in_water == 0) && (arg0->stunned == 0) && (D_800CC6D1 == 0) && ((arg0->disable_run == 0) || (arg0->unk84.uh == 0x279)) && ((s16) temp_t0_37->unk8 <= 0) && (arg0->unk28 == 0.0f) && ((u16) ((struct49 *)D_800CC6A4)->unk0 & 0x2000)) {
                arg0->unk81 = 0;
                arg0->unk83 = 0;
                arg0->unk100 = temp_v1_10 & 0xFE;
                arg0->unk76 = arg0->unk7A;
            }
        }
    }
    temp_t0_38 = arg0->unk31C;
    if (((arg0->unk1CC - arg0->y_position) > 600.0f) && (temp_t0_38->unk120 == 0)) {
        temp_v0_45 = temp_t0_38->unk11A;
        if ((temp_v0_45 != 1) && (temp_v0_45 != 3) && (arg0->unk118 == -10000.0f)) {
            temp_v0_46 = arg0->unk84.uh;
            if ((temp_v0_46 != 0x101) && (arg0->in_water == 0)) {
                if (temp_v0_46 != 0xCF) {
                    sp84 = 0x2007E5;
                    if (func_1506E46C(arg0, &sp84, 1) != 0) {
                        func_15060A30(sp84, arg0);
                    }
                }
                arg0->unk31C->unk31 = 0;
                func_1505E650(arg0, 0xCFU, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                arg0->unk83 = 0xC8;
            }
        }
    }
    (*(s32 *)((u8 *)(arg0->unk31C) + 4)) = 0;
    func_1504C0E8(arg0, sp1A0, sp1BC);
    temp_f2_9 = arg0->x_position - arg0->old_x_position;
    temp_f12_5 = arg0->z_position - arg0->old_z_position;
    (*(f32 *)((u8 *)(arg0->unk31C) + 0)) = (f32) (2.0f * sqrtf((temp_f2_9 * temp_f2_9) + (temp_f12_5 * temp_f12_5)));
    (*(u16 *)((u8 *)(arg0->unk31C) + 0x32)) = 0U;
    if ((arg0->unk31C->unk84 != 0) || (sp184 != 0)) {
        ((u16 *)D_800CC6A4)[0] = sp188[0]; ((u16 *)D_800CC6A4)[1] = sp188[1];
        (*(u16 *)((u8 *)(D_800CC6A4) + 4)) = (u16) sp188[2];
    }
    arg0->unk31C->unk88 = (s16) sp190;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1504CB98.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_150511E8.s")
#ifdef NON_MATCHING
s32 func_15088360(s32, struct127 *);
void func_1510FDA0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6);
extern f32 D_80099490[];
void func_1505A250(f32, f32, f32, f32 *, f32 *);
f32 func_1505210C(u8 *, f32, f32, f32 *, f32);

/* P60: per-frame ground push / slide of a walking record (x / z = the position it moved to this frame, angle = the
 * stick direction). On land: the floor's push (func_1510FDA0: conveyor / slope force fx / fz, its speed and the
 * slide dx / dz) when standing (height +0x28 <= 0) or sliding (+0x110), or always on ice (ctl +0x4E == 2). A slide
 * starts (D_800CC69C = 1) on a strong push or floor kind 4 (not kind 3, not while carried by record ids 8 / 0x49):
 * the record then turns to the slope (+0x112), sets the slide mode +0x110 (3 = jump-off slide 0x28E, 1 = slide
 * forward 0x101, 2 = backwards 0xD0) and its animation; the speed +0x3C and heading are rebuilt when the slide
 * flag +0x162 changes. The push goes through func_1505A250 into +0x164 / +0x168, the slide decays (+0x16C / +0x170,
 * x 0.85); a backwards slide that stops turns the record around (animation 0xA5). The landing tilt (+0xC4 / +0xB8)
 * follows the push (func_1505210C) and, on ice, a wobble with a sound at > 70. In water: the float bob only. */
/* ctl (struct126) fields not in the header: +0 f32 / +4 s32 (pad0), +0x24 s16 wobble sound latch (pad17[0xD]),
 * +0x3E u16 slide heading (pad3C[2]), +0x4F (pad4F[0]). */
void func_15051558(struct127 *rec, f32 x, f32 z, u16 angle) {
    struct126 *ctl;
    f32 dx = 0.0f;
    f32 dz = 0.0f;
    f32 rate = 0.2f;
    f32 h = rec->unk28;
    f32 fx, fz, push;
    f32 ddx, ddy, ddz, moved, m, bob, wob, anim_speed;
    s32 slide_start = 0;
    s32 was_sliding;
    s32 carrier;
    s32 kind;
    s32 anim;
    u16 heading, ref, turn;

    if (rec->in_water == 0) {
        fx = 0.0f;
        fz = 0.0f;
        was_sliding = rec->unk162;
        push = 3.0f;
        ctl = rec->unk31C;
        kind = ctl->unk4E;
        if (kind == 2) {
            func_1510FDA0(rec->unk188, (s32) &rec->unk18C, &fx, &fz, (s32) &push, &dx, &dz);
            m = dx * dx + dz * dz;
            if (1.4f < m && m < 1000.0f) {
                rec->disable_jump = 6;
                if (h < 80.0f && rec->disable_run == 0) {
                    func_15088360(D_800C3E78, rec);
                }
            }
            if (0.0f <= h) {
                fx = 0.0f;
                fz = 0.0f;
                dx = 0.0f;
                dz = 0.0f;
                push = 3.0f;
            }
            ctl = rec->unk31C;
            kind = ctl->unk4E;
        } else if ((h <= 0.0f || rec->unk110 != 0) && ctl->pad4F[0] == 0) {
            func_1510FDA0(0, (s32) &rec->unk18C, &fx, &fz, (s32) &push, &dx, &dz);
            ctl = rec->unk31C;
            kind = ctl->unk4E;
        }
        if (kind == 0 && ctl->unk84 == 0) {
            if (D_800CC69C == 0 ? (dx * dx + dz * dz > 1.0f || ((rec->unk184 >> 12) & 0xF) == 4)
                                : ctl->pad17[0] != 0) {
                if (((rec->unk184 >> 12) & 0xF) != 3) {
                    D_800CC69C = 1;
                    slide_start = 1;
                }
            }
        }
        /* unk274 = carrying record + 1 */
        carrier = (rec->unk274 != 0) ? D_800CC2D0[rec->unk274 - 1].id : -1;
        if (D_800CC69C == 0) {
            fx = 0.0f;
            fz = 0.0f;
            push = 3.0f;
        }
        if (carrier == 8 || carrier == 0x49) {
            slide_start = 0;
        }
        if (D_800CC69C != 0 && rec->unk28 < 5.0f && rec->unk110 != 0) {
            rec->unk162 = 1;
            if (rec->disable_run != 0xFE) {
                rec->disable_run = D_800BE9A0 + 1;
            }
        } else {
            rec->unk162 = 0;
        }

        ddx = x - rec->old_x_position;
        ddy = rec->y_position - rec->old_y_position;
        ddz = z - rec->old_z_position;
        moved = (sqrtf(ddx * ddx + ddy * ddy + ddz * ddz) * 2.0f) * D_800BEDC8;
        if (rec->unk162 != was_sliding) {
            if (rec->unk162 != 0) {
                rec->unk164 = ddx * D_800BEDC8;
                rec->xz_velocity = 0.0f;
                rec->unk168 = ddz * D_800BEDC8;
            } else {
                rec->xz_velocity = moved;
                if (moved < 22.0f) {
                    rec->xz_velocity = 22.0f;
                }
                if (rec->unk110 == 3) {
                    rec->unk110 = 0;
                    if (rec->disable_run != 0xFE) {
                        rec->disable_run = 0;
                    }
                    rec->xz_velocity = 17.9f;
                }
                rec->unk76 = func_1505A630(x - rec->old_x_position, rec->old_z_position - z, 0);
                rec->unk164 = 0.0f;
                rec->unk168 = 0.0f;
                rec->unk16C = 0.0f;
                rec->unk170 = 0.0f;
            }
        }

        if (D_800CC69C != 0 && rec->unk28 < 5.0f) {
            anim_speed = 1.0f;
            rec->disable_jump = D_800BE9A0 + 8;
            rec->unk112 = func_1505A630(-fx, fz, 0);
            heading = func_1505A630(rec->x_position - rec->old_x_position, rec->old_z_position - rec->z_position, 0);
            D_800CC69C = 1;
            if (rec->unk110 == 0) {
                push = (&D_80099470)[1];
                turn = rec->unk112;
                if (((((s32) (turn - heading) >> 8) + 0x30) & 0xFF) < 0x60) {
                    anim = 0x28E;
                    ref = (rec->unk44 > 8.0f) ? angle : rec->unk7A;
                    if (slide_start) {
                        rec->unk110 = 3;
                        anim_speed = 2.0f;
                    } else {
                        anim = 0xD0;
                        if (((((s32) (turn - ref) >> 8) + 0x58) & 0xFF) < 0xB0) {
                            rec->unk110 = 1;
                            anim = 0x101;
                        } else {
                            rec->unk110 = 2;
                        }
                    }
                    if (rec->stunned == 0 && rec->unk13C == 0 && rec->disable_run != 0xFF && rec->unk83 < 0xFA) {
                        ctl = rec->unk31C;
                        if (ctl->unk11A != 1 && ctl->unk11A != 3 && ctl->unk120 == 0 && ctl->unk19B == 0) {
                            func_1505E650(rec, anim, anim_speed, 6.0f, 0.0f, 0.0f, 0);
                        }
                    }
                }
            } else {
                push = D_80099490[D_800CC69C];
            }
        }

        func_1505A250(-fx, -fz, push, &rec->unk164, &rec->unk168);
        rec->unk16C = rec->unk16C + (0.0f - rec->unk16C) * 0.15f;
        rec->unk170 = rec->unk170 + (0.0f - rec->unk170) * 0.15f;
        if (rec->unk110 != 0) {
            *(u16 *) &rec->unk31C->pad3C[2] = func_1505A630(rec->x_position - rec->old_x_position,
                                               rec->old_z_position - rec->z_position, 0);
            anim = rec->unk84.uh;
            if (anim == 0x28E || anim == 0x101 || anim == 0xD0) {
                if (rec->unk31C->unk11A != 1 && rec->unk31C->unk11A != 3) {
                    rec->unk83 = D_800BE9A0 + 1;
                }
            }
            if (D_800CC69C == 0) {
                if (rec->unk110 == 2) {
                    rec->unk76 = rec->unk112;
                    *(u16 *) &rec->unk31C->pad3C[2] = rec->unk112;
                    if (rec->xz_velocity < 2.0f && 0.0f == rec->unk28) {
                        if (rec->stunned == 0) {
                            func_1505E650(rec, 0xA5, 1.4f, 5.0f, 0.0f, 0.0f, 0);
                            turn = rec->unk76 ^ 0x8000;
                            rec->unk83 = 0x3C;
                            rec->disable_run = 0x3C;
                            rec->disable_jump = 0x1E;
                            rec->unk76 = turn;
                            rec->unk7A = turn;
                            rec->unk100 |= 0x20;
                        }
                        rec->unk110 = 0;
                    }
                } else if (rec->xz_velocity < 12.0f) {
                    rec->unk110 = 0;
                }
            }
        }

        if (h <= 0.0f) {
            dx = func_1505210C((u8 *) rec, dx, dz, &dz, 50.0f);
            ctl = rec->unk31C;
            kind = ctl->unk4E;
            if (kind != 2) {
                if (*(s32 *) &ctl->pad0[4] == 0 && rec->unk110 == 0 && (kind & 0xF) != 1) {
                    dx = dx * (*(f32 *) &ctl->pad0[0] * 0.009f + 0.2f);
                    dz = dz * (*(f32 *) &rec->unk31C->pad0[0] * 0.014f + 0.2f);
                } else {
                    dx = dx * 0.8f;
                    dz = dz * 0.8f;
                    if ((rec->unk31C->unk4E & 0xF) == 1) {
                        dz = 0.0f;
                        dx = dx * 0.5f;
                    }
                }
            }
        }
        if (rec->unk31C->unk4E == 2) {
            bob = rec->unk54 * 6.0f;
            if (rec->y_velocity < -30.0f) {
                dz = dz - -30.0f;
            } else {
                dz = dz - rec->y_velocity;
            }
            rate = 0.4f;
            ctl = rec->unk31C;
            if (ctl->unk44 > 0) {
                rate = 0.25f;
                bob += (s16) ((s16) ((D_800CC670 & 4) - 2) * (ctl->unk44 * 2));
            }
            wob = fabsf(rec->unkC4);
            if (70.0f < wob && D_800BE616 == 0 && rec->health != 0 && *(s16 *) &ctl->pad17[0xD] == 0) {
                D_800D1580 = 0xFF020146;
                func_1506E8D8();
                *(s16 *) &rec->unk31C->pad17[0xD] = 1;
                wob = fabsf(rec->unkC4);
            }
            if (wob < 20.0f) {
                *(s16 *) &rec->unk31C->pad17[0xD] = 0;
            }
            dx = dx + bob;
        }
        rec->unkB8 = rec->unkB8 + (dz - rec->unkB8) * rate;
    } else {
        m = ((rec->unk118 - 30.0f) - rec->y_position) + rec->xz_velocity * 6.0f;
        m = (250.0f < m) ? 2.5f : m * 0.01f;
        if (fabsf(rec->unkB8) < 35.0f && 0.0f < m) {
            dx = 0.0f + rec->unk54 * m;
        }
        func_1505A250(0.0f, 0.0f, 0.3f, &rec->unk164, &rec->unk168);
    }
    rec->unkC4 = rec->unkC4 + (dx - rec->unkC4) * rate;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_15051558.s")
#endif
#ifdef NON_MATCHING
f32 func_1505210C(u8 *arg0, f32 arg1, f32 arg2, f32 *arg3, f32 arg4) {
    f32 sp34;
    f32 sp2C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f20;
    f32 var_f22;

    temp_f20 = -arg2;
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x40)) * 0.017453292f;
    sp2C = temp_f12;
    sp34 = func_150AD780(temp_f12);
    temp_f0 = func_150AD78C(temp_f12);
    var_f22 = func_150484A0((arg1 * sp34) + (temp_f20 * temp_f0), 1.0f) * 57.295776f;
    temp_f2 = func_150484A0((-arg1 * temp_f0) + (temp_f20 * sp34), 1.0f) * 57.295776f;
    var_f20 = temp_f2;
    if (var_f22 >= 180.0f) {
        var_f22 -= 360.0f;
    }
    if (temp_f2 >= 180.0f) {
        var_f20 = temp_f2 - 360.0f;
    }
    temp_f0_2 = -arg4;
    if (arg4 < var_f22) {
        var_f22 = arg4;
    }
    if (var_f22 < temp_f0_2) {
        var_f22 = temp_f0_2;
    }
    if (arg4 < var_f20) {
        var_f20 = arg4;
    }
    if (var_f20 < temp_f0_2) {
        var_f20 = temp_f0_2;
    }
    *arg3 = var_f20;
    return var_f22;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1505210C.s")
#endif
void func_1505A770(struct127 *);

void func_15052260(struct127 *arg0) {
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f12;
    struct126 *temp_v0;
    u8 temp_v1;

    temp_v0 = arg0->unk31C;
    temp_v1 = temp_v0->unk6B;
    if ((temp_v1 == 1) || (temp_v1 == 3)) {
        var_f12 = 0.4f;
    } else {
        var_f12 = 1.0f;
    }
    temp_f14 = arg0->y_position;
    arg0->unk1CC = temp_f14;
    if ((s32) temp_v0->unk6B < 4) {
        arg0->x_position += (*(s16 *)((u8 *)temp_v0 + 0x6C) - arg0->x_position) * var_f12;
        arg0->y_position += ((*(s16 *)((u8 *)temp_v0 + 0x6E)) - 0x50 - arg0->y_position) * var_f12;
        arg0->z_position += (*(s16 *)((u8 *)temp_v0 + 0x70) - arg0->z_position) * var_f12;
        func_1505E650(arg0, 0x14U, 1.0f, 6.0f, 0.0f, 0.0f, 0);
        arg0->y_velocity = -10.0f;
    } else {
        if ((s32) arg0->unk28 == 0) {
            temp_v0->unk6B = 0;
        } else {
            func_1505E650(arg0, 0x38U, 1.0f, 6.0f, 0.0f, 0.0f, 0);
        }
        func_1505A770(arg0);
    }
    arg0->gravity = 6.2f;
    if (arg0->y_position < arg0->unk118) {
        arg0->gravity = 0.0f;
        arg0->y_velocity = 0.0f;
        arg0->unk31C->unk6B = 0;
        arg0->unk83 = 0;
        arg0->in_water = 1;
    }
}

void func_15052408(struct127 *arg0) {
    arg0->unkB2 = 0;
    arg0->unk31C->unk95 = 0;
    if (arg0->health != 0) { // if health not zero
        arg0->unk81 = 0;
        arg0->unk83 = 0;
        arg0->disable_run = 6;
    }
    arg0->in_water = 0;
    arg0->gravity = 4.0f;
    arg0->unkB8 = 0.0f;
    arg0->xz_velocity = 15.0f;
}

void func_15052458(s32 arg0) {
}

void func_15052464(struct127 *arg0) {
    if (arg0->health == 0) {
        func_15060F28(arg0, 1);
    }
}

void func_15052490(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3) {
    arg3 *= D_800D1550[0];

    arg0->unk40 = (arg0->unk7A + 16384) * 0.005493164f;

    if (((arg1 - arg0->unk7A + 16384) & 0x8000) != 0) {
        arg0->unkB8 -= arg2 * arg3;
    } else {
        arg0->unkB8 += arg2 * arg3;
    }
}

void func_1505250C(struct127 *arg0, s32 arg1) {
    s16 temp_v0 = arg0->unkCE;
    s16 temp_v1 = arg0->unkCC;

    if (temp_v0 != temp_v1) {
        if (temp_v1 < temp_v0) {
            arg0->unkCC = temp_v1 + ((temp_v0 - temp_v1) / 0xC) + 1;
            if (temp_v0 < arg0->unkCC) {
                arg0->unkCC = temp_v0;
            }
        } else {
            arg0->unkCC = (temp_v1 + ((temp_v0 - temp_v1) / 0xC)) - 1;
            if (arg0->unkCC < temp_v0) {
                arg0->unkCC = temp_v0;
            }
        }
    }
}

void func_15053750(struct127 *arg0);
s32 func_150535F4(struct127 *arg0);
void func_15021834(struct127 *, s32, s32);
s32 func_15022A8C(struct127 *);
void func_15054F74(struct127 *);
s32 func_150562FC(struct127 *);
void func_15056B08(struct127 *);
s32 func_150585F0(struct127 *, s32);
s32 func_150597FC(struct127 *);
s32 func_150B0148(u8, s32, s32, s32, s32, s32);
extern u8 D_800C3A78;

void func_15052590(struct127 *arg0) {
    f32 temp_f0;
    s32 temp_v0;

    temp_v0 = arg0->unk25C;
    if (temp_v0 & 0x80) {
        arg0->unk25C = temp_v0 & ~0x80;
        func_150B0148(D_800C3E78, 3, 0x3FC, 6, 0xFF, 0);
        func_150B0148(D_800C3E78, 2, 0x3FC, 6, 0xFF, 0);
    }
    if ((D_800C35EA != 1) || ((D_800C3A78 != 0) && (func_15022A8C(arg0) == 0))) {
        func_15053750(arg0);
        func_1504BB88(arg0);
        arg0->unk80 = 0xA;
        if (arg0->stunned == 0) {
            func_15056B08(arg0);
        } else if (arg0->unk13D == 0) {
            func_150585F0(arg0, 0x3D4CCCCD);
        }
        arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
        func_15059140(arg0);
        if ((arg0->unk28 == 0.0f) && ((arg0->unk184 & 0x1F) == 0xE)) {
            arg0->health = 0;
        }
        func_150597FC(arg0);
        if (arg0->unk13D != 0) {
            func_150562FC(arg0);
        } else {
            temp_f0 = arg0->unkC4;
            arg0->unkC4 = arg0->unkC4 + ((0.0f - arg0->unkC4) * 0.2f);
        }
        func_15054F74(arg0);
        if (func_150535F4(arg0) == 0) {
            func_15021834(arg0, 0, -1);
        }
    }
}
#ifdef NON_MATCHING
extern f32 D_80099700;
extern f32 D_80099704;
void func_15052760(struct127 *arg0, u16 arg1) {
    f32 temp_f2;
    f32 var_f0;
    s32 temp_a1;
    s32 var_a1;
    s32 var_v0;
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = arg0->id;
    var_v0 = (s32) ((s16) ((arg1) - arg0->unk76) * 0x64) / (s16) D_800CC264;
    if (((temp_v1 == 0x29) || (temp_v1 != 8)) && !(arg0->unk22C & 8)) {
        var_f0 = D_80099700;
        var_a1 = 7;
        if (temp_v1 == 0xA) {
            var_a1 = 0x28;
        }
        if (arg0->unk226 == 0xFF) {
            temp_a1 = var_v0 >> 8;
            if ((arg0->unk87 ^ (s8) temp_a1) & 0x80) {
                var_v0 = 0;
            }
            var_f0 = D_80099704;
            var_a1 = 4;
            arg0->unk87 = (u8) (s8) temp_a1;
        }
        temp_v1_2 = arg0->unk1E5;
        if (temp_v1_2 != 0) {
    s32 pad;
            temp_f2 = arg0->unkC4;
            arg0->unkC4 = temp_f2 + (((f32) (var_v0 / (s32) (temp_v1_2 * var_a1)) - temp_f2) * var_f0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_15052760.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_150528C8.s")

void func_15052EF0(struct127 *arg0) {
    arg0->immune = 100;
    arg0->unk40 =  ((s16) (arg0->unk7A + 16384)) * 0.005493164f;
    func_1505E650(arg0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

struct127 *func_15052F58(s32 arg0, s32 arg1) {
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    temp_v0->unk13C = (u8)0;
    temp_v0->unk218 = 0;
    temp_v0->unk232 = arg1;
    return temp_v0;
}

#ifdef NON_MATCHING
/* P128 */
u8 *func_15034174(u8 *arg0);

// object_catch_player: lands / catches the player record D_800CC2D0[obj->unk124] on object obj (lift, platform,
// carrier). Unless `force`, it only fires when the player is below obj's top (obj y + height * obj->y_scale) and
// falling. Then: obj->unk13C = player + 100, optional sound event D_800D1580 = sound (func_1506E5FC), the player
// remembers its y (+0x1CC) and faces obj's angle, its state block mode is cleared. Objects in state 0x20 stop both
// vertical speeds and align the player to obj's angle (+0x40 in degrees); type 0x48 objects carrying partner 0x7A
// (func_15034174) start the ride animation 5 / 0x79 and call func_15060F28(obj, 0) at the end, other objects squash
// (y_scale 0.75) and snap the player to obj's y (state 1, 0x81 in level 6). Other states hand the player over
// (unk65 = D_800C3E78 + 1, unk5C = anim, unk101 |= flags). Finally immune = immune, unk239 = arg7, obj->unk232 =
// timer; `reset` calls func_1506160C(player, 1, 0, 0, 0) and sets player flag 0x40. The asm returns nothing; the f32
// return type matches the callers' prototypes (0).
f32 func_15052F9C(struct127 *obj, f32 height, s32 anim, s32 flags, s32 reset, s32 timer, s32 immune, s32 arg7,
                  s32 force, s32 sound) {
    struct127 *pl;
    s32 partner;
    s32 ride;
    s32 state;
    u16 angle;

    ride = 0;
    partner = -1;
    if (obj->id == 0x48) {
        u8 *other = func_15034174((u8 *) obj);
        if (other != NULL) {
            partner = other[6];
        }
    }
    pl = &D_800CC2D0[obj->unk124];
    if (force != 0 ||
        (pl->y_position < obj->y_position + height * obj->y_scale && pl->y_velocity < 0.0f)) {
        obj->unk13C = obj->unk124 + 100;
        if (sound != 0) {
            D_800D1580 = sound;
            func_1506E5FC();
        }
        pl->unk1CC = pl->y_position;
        pl->unk76 = obj->unk7A;
        pl->unk31C->unk30 = 0;
        if (obj->interaction_state == 0x20) {
            pl->y_velocity = 0.0f;
            obj->y_velocity = 0.0f;
            if (obj->id == 0x48) {
                state = 2;
                if (partner == 0x7A) {
                    obj->unk65 = obj->unk124 + 1;
                    obj->unk5C = anim;
                    obj->unk101 |= flags;
                    func_1505E650(pl, 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
                    func_15083568(pl, 0x79, 1.0f, 0);
                    ride = 1;
                }
            } else {
                obj->y_scale = 0.75f;
                pl->y_position = obj->y_position;
                state = 1;
                if (D_800BE9F0 == 6) {
                    state = 0x81;
                }
            }
            angle = obj->unk7A;
            pl->unk76 = angle;
            pl->unk78 = angle;
            pl->unk7A = angle;
            pl->unk40 = (s16) (angle + 0x4000) * 0.0054931640625f; /* 360 / 65536 */
            pl->unk31C->unk4E = state;
            pl->unk83 = 0;
            pl->disable_run = 0;
        } else {
            pl->unk65 = D_800C3E78 + 1;
            pl->unk5C = anim;
            pl->disable_run = 0;
            pl->unk101 |= flags;
        }
        pl->immune = immune;
        pl->unk239 = arg7;
        pl->unk31C->unk27 = 0;
        obj->unk218 = NULL;
        obj->unk232 = timer;
        if (reset != 0) {
            func_1506160C(pl, 1, 0, 0, 0);
            pl->unk101 |= 0x40;
        }
    }
    if (ride != 0) {
        func_15060F28(obj, 0);
    }
    return 0.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_15052F9C.s")
#endif
// NON-MATCHING: plenty still to do here
// void func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
//     s32 sp40;
//     s32 sp3C;
//     f32 temp_ret;
//     u16 temp_v0_3;
//     u8 idx;
//     struct127 *temp_a0;
//     struct05 *temp_v0;
//     s32 phi_a1;
//     s8 phi_v1;
//     struct127 *phi_a0;
//     // f32 phi_return;
//
//     sp3C = 0;
//     phi_a1 = -1;
//     if (arg0->id == 72) {
//         sp40 = -1;
//         temp_v0 = func_15033E84(arg0, -1);
//         phi_a1 = -1;
//         if (temp_v0 != 0) {
//             phi_a1 = temp_v0->unk6;
//         }
//     }
//     idx = arg0->unk124;
//     temp_a0 = &D_800CC2D0[idx];
//     if (arg8 == 0) {
//         // phi_return = idx; // bitwise (f32)
//         if (temp_a0->y_position < (arg0->y_position + (arg1 * arg0->unk150))) {
//             // phi_return = 0.0f;
//             if (temp_a0->y_velocity < 0.0f) { // stick an || here
//                 arg0->unk13C = (idx + 0x64);
//                 if (arg9 != 0) {
//                     D_800D1580 = arg9;
//                     sp40 = phi_a1;
//                     func_1506E5FC(temp_a0, phi_a1);
//                 }
//                 D_800CC2D0[idx].unk1CC = D_800CC2D0[idx].y_position;
//                 D_800CC2D0[idx].unk76 = arg0->unk7A;
//                 D_800CC2D0[idx].unk31C->unk30 = 0;
//                 if (arg0->interaction_state == 0x20) {
//                     D_800CC2D0[idx].y_velocity = 0.0f;
//                     arg0->y_velocity = 0.0f;
//                     if (arg0->id == 0x48) {
//                         phi_v1 = (s8) 2;
//                         if (phi_a1 == 0x7A) {
//                             arg0->unk65 = (arg0->unk124 + 1);
//                             arg0->unk5C = arg2;
//                             arg0->unk101 = (arg0->unk101 | arg3);
//                             func_1505E650(&D_800CC2D0[idx], 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
//                             func_15083568(&D_800CC2D0[idx], 0x79, 1.0f, 0);
//                             sp3C = 1;
//                             phi_v1 = (s8) 2;
//                         }
//                     } else {
//                         arg0->unk150 = 0.75f;
//                         D_800CC2D0[idx].y_position = arg0->y_position;
//                         phi_v1 = 1;
//                         if (D_800BE9F0 == 6) {
//                             phi_v1 = 0x81;
//                         }
//                     }
//                     D_800CC2D0[idx].unk76 = arg0->unk7A;
//                     D_800CC2D0[idx].unk78 = arg0->unk7A;
//                     D_800CC2D0[idx].unk7A = arg0->unk7A;
//                     D_800CC2D0[idx].unk40 = (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
//                     D_800CC2D0[idx].unk31C->unk4E = phi_v1;
//                     D_800CC2D0[idx].unk83 = 0;
//                     D_800CC2D0[idx].disable_run = 0;
//                     phi_a0 = &D_800CC2D0[idx];
//                     // phi_return = arg0->unk7A; // bitwise ( f32)
//                 } else {
//                     D_800CC2D0[idx].unk65 = D_800C3E78 + 1;
//                     D_800CC2D0[idx].unk5C = arg2;
//                     D_800CC2D0[idx].disable_run = 0;
//                     D_800CC2D0[idx].unk101 =  (D_800CC2D0[idx].unk101 | arg3);
//                     phi_a0 = &D_800CC2D0[idx];
//                 }
//                 phi_a0->immune =  arg6;
//                 phi_a0->unk239 = arg7;
//                 phi_a0->unk31C->unk27 = 0;
//                 arg0->unk218 = 0;
//                 arg0->unk232 =  arg5;
//                 if (arg4 != 0) {
//                     temp_ret = func_1506160C(phi_a0, 1, 0, 0, 0);
//                     phi_a0->unk101 = (u8) (phi_a0->unk101 | 0x40);
//                     // phi_return = temp_ret;
//                 }
//             }
//         }
//     } else {
//     //    goto block_6;
//     }
//     if (sp3C != 0) {
//         // phi_return =
//         func_15060F28(arg0, 0);
//     }
//     // return phi_return;
// }


#ifdef NON_MATCHING
/* P128 */
// object_launch_player: launches the player record D_800CC2D0[obj->unk124] off object obj (a spring / bounce pad):
// unless the player is already airborne-locked (disable_run) or stunned, or its state block forbids it (+0x6B), sets
// immune / unk83 / disable_run to 0xFF, vertical speed vy and gravity, faces it along obj's angle, starts animation
// 0x32 (speed 1.3, blend 4), clears obj->unk218, sets obj->unk232 = timer and aims the state block at obj's x / z
// (or, when obj has a path table unk1D4 and point != -1, at path point `point` read by func_15043FF0), with mode 70
// and flag +0x27 = 1. The asm returns nothing; the s32 return type matches the callers' prototypes (0).
s32 func_1505327C(struct127 *obj, f32 vy, f32 gravity, s32 timer, s32 point) {
    struct127 *pl;
    vertex target;

    pl = &D_800CC2D0[obj->unk124];
    if (pl->disable_run != 0 || pl->stunned != 0) {
        return 0;
    }
    if (pl->unk31C != NULL && pl->unk31C->unk6B != 0) {
        return 0;
    }
    pl->immune = 0xFF;
    pl->y_velocity = vy;
    pl->gravity = gravity;
    pl->unk83 = 0xFF;
    pl->disable_run = 0xFF;
    pl->unk76 = obj->unk7A;
    obj->unk218 = NULL;
    obj->unk232 = timer;
    func_1505E650(pl, 0x32, 1.3f, 4.0f, 0.0f, 0.0f, 0);
    D_800CC2D0[obj->unk124].unk31C->unk30 = 70;
    *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk28 = obj->x_position;
    *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk2C = obj->z_position;
    if (obj->unk1D4 != NULL && point != -1) {
        func_15043FF0(&target, (struct113 *) ((u8 *) obj->unk1D4 + (point << 6)));
        *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk28 = target.x;
        *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk2C = target.z;
    }
    D_800CC2D0[obj->unk124].unk31C->unk27 = 1;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1505327C.s")
#endif
// NON-MATCHING: plenty still to do here
// void func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
//     // s32 sp44;
//     f32 sp3C;
//     struct127 *temp_s0;
//     struct126 *temp_v0;
//
//     temp_s0 = &D_800CC2D0[arg0->unk124];
//     if ((temp_s0->disable_run == 0) && (temp_s0->stunned == 0)) {
//         temp_v0 = temp_s0->unk31C;
//         if ((temp_v0 == 0) || (temp_v0->unk6B == 0)) {
//             temp_s0->immune = 0xFFU;
//             temp_s0->y_velocity = arg1;
//             temp_s0->gravity = arg2;
//             temp_s0->unk83 = 0xFFU;
//             temp_s0->disable_run = 0xFFU;
//             temp_s0->unk76 = arg0->unk7A;
//             arg0->unk218 = 0;
//             arg0->unk232 = arg3;
//             // func_1505E650(arg1, arg2, temp_s0, 0x32, 1.2999999523162842f, 4.0f, 0.0f, 0.0f, 0);
//             func_1505E650(arg0, 50, 0x3FA66666, 4.0f, 0.0f, 0.0f, 0);
//             D_800CC2D0[arg0->unk124].unk31C->unk30 = 70;
//             D_800CC2D0[arg0->unk124].unk31C->unk28 = arg0->unk14;
//             D_800CC2D0[arg0->unk124].unk31C->unk2C = arg0->unk1C;
//             if ((arg0->unk1D4 != 0) && (arg4 != -1)) {
//                 func_15043FF0(&sp3C, arg0->unk1D4 + (arg4 << 6));
//                 D_800CC2D0[arg0->unk124].unk31C->unk28 = sp3C;
//                 // D_800CC2D0[arg0->unk124].unk31C->unk2C = sp44;
//             }
//             D_800CC2D0[arg0->unk124].unk31C->unk27 = 1;
//         }
//     }
// }

#ifdef NON_MATCHING
s32 func_15053430(struct127 *);   /* P77: the asm reads a0 (the object) */
#else
s32 func_15053430(void);
#endif
#ifdef NON_MATCHING
/* P136 */
s32 func_1507D754(struct127 *);
void func_15055B0C(struct127 *, s32);

/*
 * object_death_resolve: what happens to a dead object (called by func_150535F4 and the event natives). id 0xFF:
 * func_15060F28(obj, 1). Death timer +0x10E in 1..0xEF: func_1505D2B8(obj, 9), returns 0. Else by the type's
 * death flags (byte +0x28 of D_800D1C90[id]): 0x20 (timer < 0xF0) puffs an effect at the object (func_15166F10,
 * 50 above it, scale 0.5); 0x04 asks func_1507D754 for a result (1 / 0 below); then the first of 0x02 (state
 * 0x2A), 0x80 (func_15055B0C(obj, 1000)), 0x01 (func_15053694), 0x40 (respawn timer D_800D2530[+0x13F] = 1250 and
 * func_15060F28(obj, 1)); without those, result 1 -> func_150536D0, result 0 -> func_15060F28(obj, 1).
 * Returns 1.
 */
s32 func_15053430(struct127 *obj) {
    u8 flags;
    s32 res;

    if (obj->id == 0xFF) {
        func_15060F28(obj, 1);
        return 1;
    }
    flags = *((u8 *) D_800D1C90[obj->id] + 0x28);
    if (obj->unk10E != 0 && obj->unk10E < 0xF0) {
        func_1505D2B8(obj, 9);
        return 0;
    }
    res = 0;
    if (obj->unk10E < 0xF0 && (flags & 0x20)) {
        func_15166F10((s32) obj->x_position, (s32) (obj->y_position + 50.0f), (s32) obj->z_position, 0.5f, 0xFF, 0);
    }
    if (flags & 4) {
        res = func_1507D754(obj);
    }
    if (flags & 2) {
        obj->interaction_state = 0x2A;
        return 1;
    }
    if (flags & 0x80) {
        func_15055B0C(obj, 1000);
        return 1;
    }
    if (flags & 1) {
        func_15053694(obj);
        return 1;
    }
    if (flags & 0x40) {
        D_800D2530[obj->unk13F] = 1250;
        func_15060F28(obj, 1);
        return 1;
    }
    if (res == 1) {
        func_150536D0(obj);
        return 1;
    }
    if (res == 0) {
        func_15060F28(obj, 1);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_15053430.s")
#endif

s32 func_150535F4(struct127 *arg0) {
    u8 tmp;

    if (arg0->health == 0) {
        if (arg0->id == 0xFF) {
            func_15060F28(arg0, 1);
            return 1;
        }
        tmp = D_800D1C90[arg0->id]->data.i.unk0;
        if (((tmp & 0x10) != 0) ||
            (((tmp & 8) != 0) && (arg0->unk28 == 0.0f)) ||
            (arg0->unk10F == 0)) {
#ifdef NON_MATCHING
            return func_15053430(arg0);
#else
            return func_15053430();
#endif
        }
    }
    return 0;
}


void func_15053694(struct127 *arg0) {
    arg0->interaction_state = 8;
    arg0->unkE4 = 0;
    arg0->unkE6 = 0;
    func_1506160C(arg0, 6, 0, 0, 0);
}

void func_150536D0(struct127 *arg0) {
    arg0->interaction_state = 13;
    arg0->unkE4 = 0;
    arg0->unkE6 = 0;
}

void func_150536E8(struct127 *arg0) {
    arg0->unk40 = ((s16) (arg0->unk7A + 16384)) * 0.005493164f;
}

void func_1505371C(struct127 *arg0) {
    arg0->unk40 = ((s16) (arg0->unk7A + 16384)) * 0.005493164f;
}

// ???
void func_15053750(struct127 *arg0) {
    f32 diff;

    diff = arg0->unk154 - arg0->xz_scale;
    if (diff != 0.0f) {
        if (fabsf(diff) < arg0->unk15C) {
            func_15062BDC(arg0, arg0->unk154, arg0->y_scale);
        } else {
            func_15062BDC(arg0, ((diff < 0.0f ? -1 : 1) * arg0->unk15C) + arg0->xz_scale, arg0->y_scale);
        }
    }
    diff = arg0->unk158 - arg0->y_scale;
    if (diff != 0.0f) {
        if (fabsf(diff) < arg0->unk15C) {
            func_15062BDC(arg0, arg0->xz_scale, arg0->unk158);
        } else {
            func_15062BDC(arg0, arg0->xz_scale, ((diff < 0.0f ? -1 : 1) * arg0->unk15C) + arg0->y_scale);
        }
    }
}

void func_15053894(struct127 *arg0) {
    arg0->unk7F += 1;
    if (arg0->unk7F >= 0x1F) {
        func_15060F28(arg0, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_150538CC.s")

void func_150548D8(s32 arg0) {
}

void func_150548E4(struct127 *arg0) {
    struct127 *temp_s0;
    struct127 *phi_s2;
    s32 phi_v0;
    s32 i;

    temp_s0 = &D_800CC2D0[arg0->unk65 - 1];

    for (i = 0; i < D_8008FD8C; i++) {
        phi_s2 = &D_800CC2D0[i];

        if ((phi_s2->unk274 == (((s32) ((s32)arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127)) + 1)) && (temp_s0->unk232 == 1)) {
            temp_s0->unk218 = 0;
            if ((func_150ADA20() & 1) != 0) {
                temp_s0->unk232 = (u8)2U;
                phi_v0 = 0x1DB;
            } else {
                temp_s0->unk232 = (u8)3U;
                phi_v0 = 0x1DC;
            }
            func_10010344(phi_v0, temp_s0, 0x7D00, 0x1F4, 0x9C4);
        }
    }
}

void func_15054A0C(struct127 *arg0) {
    if (arg0->unk2D0 != 0) {
        if ((arg0->unk2D0->unk18 - 1.0f) <= arg0->unk2D0->unk8) {
            func_15060F28(arg0, 0);
        }
    }
}

void func_15054A5C(struct127 *arg0, struct127 *arg1) {
    arg1->unk31C->unk11A = 0;
    func_151027E8(arg1);
    func_15060F28(arg0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_15054A94.s")

#ifdef NON_MATCHING
/* P125 */
f32 func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
s32 func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
u16 func_1505A630(f32 arg0, f32 arg1, s32 arg2);
u16 func_10010154(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
void func_1505A184(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_1508B20C(f32, f32, f32, f32);

/* menu_object_update: per-frame extras of some menu / scene objects by id.
 * 0x0C: unless the object's target (D_800CC2D0[unk124]) has +0x65 == D_800C3E78 + 1: in state 0x12 run the
 *   func_15052F9C move step (speed 50); else on odd D_800CC268 frames with flag 0x400 retarget to object 0 and
 *   start func_1505327C (39, 3, state 0x12).
 * 0x4B: point unk2EC (packed s16 x << 16 | s16 z) 500 units behind its facing, turn a third of the way towards
 *   object 0 (or 0x800 off its facing when unk84 is 0xF), scale 2 and unk40 90.
 * 0x1B / 0x7E with a timer unk2E4: optional func_1508B20C at its position; the timer counts down by the frame
 *   step D_800BE9E4 (sound 0x3A1 when it passes 100); when it runs out, state 6 and unk218 = NULL. */
void func_15054F74(struct127 *arg0) {
    f32 dx, dz, dy;
    f32 x, z;
    s16 angle;
    s32 step;

    if (arg0->id == 0xC) {
        if ((D_800C3E78 + 1) != D_800CC2D0[arg0->unk124].unk65) {
            if (arg0->unk232 == 0x12) {
                func_15052F9C(arg0, 50.0f, 0, 4, 0, 0xC, 0, 8, 0, 0);
            } else if ((D_800CC268 & 1) && (arg0->unk25C & 0x400)) {
                arg0->unk124 = 0;
                func_1505327C(arg0, 39.0f, 3.0f, 0x12, 0);
            }
        }
    } else if (arg0->id == 0x4B) {
        func_1505A184(arg0->unk7A ^ 0x8000, 500.0f, 0.0f, &dx, &dz, &dy);
        x = arg0->x_position;
        z = arg0->z_position;
        arg0->unk2EC = ((s32) ((s16) x + dx) << 16) | ((s32) ((s16) z + dz) & 0xFFFF);
        if (arg0->unk84.uh != 0xF) {
            angle = func_1505A630(D_800CC2D0->x_position - x, z - D_800CC2D0->z_position, 0);
        } else {
            angle = arg0->unk7A - 0x800;
        }
        arg0->unk7A += (s16) (angle - arg0->unk7A) / 3;
        arg0->xz_scale = 2.0f;
        arg0->y_scale = 2.0f;
        arg0->unk40 = 90.0f;
    } else if ((arg0->id == 0x1B || arg0->id == 0x7E) && arg0->unk2E4 != 0) {
        if (D_800BE616 != 0) {
            func_1508B20C(arg0->x_position, arg0->y_position, arg0->z_position, 900.0f);
        }
        step = D_800BE9E4;
        if (step < arg0->unk2E4) {
            if (arg0->unk2E4 >= 100 && arg0->unk2E4 < step + 100) {
                func_10010154(0x3A1, arg0, 0x7D00, 500, 1000);
            }
            arg0->unk2E4 -= step;
        } else {
            arg0->unk232 = 6;
            arg0->unk218 = NULL;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_15054F74.s")
#endif
// void func_15054F74(struct127 *arg0) {
//     s16 phi_v1;
//
//     f32 sp50;
//     f32 sp4C;
//     f32 sp48;
//
//     f32 temp_f2;
//     f32 temp_f0;
//
//     if (arg0->id == 12) {
//         if ((D_800C3E78 + 1) != D_800CC2D0[arg0->unk124].unk65) {
//             if (arg0->unk232 == 18) {
//                 func_15052F9C(arg0, 50.f, 0, 4, 0, 12, 0, 8, 0, 0);
//             } else if ((D_800CC268 & 1) != 0) {
//                 if ((arg0->unk25C & 0x400) != 0) {
//                     arg0->unk124 = 0;
//                     func_1505327C(arg0, 39.0f, 3.0f, 18, 0);
//                 }
//             }
//         }
//     } else {
//         if (arg0->id == 0x4B) {
//             func_1505A184(arg0->unk7A ^ 0x8000, 500.0f, 0, &sp50, &sp48, &sp4C);
//             temp_f0 = arg0->unk14;
//             temp_f2 = arg0->unk1C;
//             arg0->unk2EC = (((s32) ((f32) (s16) (s32) temp_f0 + sp50) << 0x10) | ((s32) ((f32) (s16) (s32) temp_f2 + sp48) & 0xFFFF));
//             if (arg0->unk84.uh  != 0xF) {
//                 phi_v1 = func_1505A630(D_800CC2D0->unk14 - temp_f0, temp_f2 - D_800CC2D0->unk1C, 0);
//             } else {
//                 phi_v1 = (s16) (arg0->unk7A - 0x800);
//             }
//             arg0->unk7A += (s16) (phi_v1 - arg0->unk7A) / 3;
//             arg0->unk14C = 2.0f;
//             arg0->unk150 = 2.0f;
//             arg0->unk40 = 90.0f;
//         } else if (((arg0->id == 0x1B) || ((arg0->id == 0x7E))) && (arg0->unk2E4 != 0)) {
//             if (D_800BE616 != 0) {
//                 func_1508B20C(arg0->unk14, arg0->unk18, 500.0f, 900.0f);
//             }
//             if ((arg0->unk2E4 > D_800BE9E4) && (arg0->unk2E4 >= 0x78) && (arg0->unk2E4 < (D_800BE9E4 + 0x78))) {
//                 func_10010154(0x3A1, arg0, 0x7D00, 0x1F4, 0x3E8);
//                 arg0->unk2E4 -= D_800BE9E4;
//             } else {
//                 arg0->unk232 = 6U;
//                 arg0->unk218 = 0;
//             }
//         }
//     }
// }

void func_15055260(s32 arg0, s32 arg1, s32 arg2) {
    func_150335C8(arg0, arg1, 0x4D, arg2, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_78230/func_1505528C.s")
// NON-MATCHING: 80% there
// void func_1505528C(struct127 *arg0) {
//     f32 sp84;
//     f32 sp80;
//     f32 sp7C;
//     s32 sp74;
//     f32 sp70;
//     s32 sp6C;
//     s32 sp64;
//
//     struct17 tmp0;
//
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f2;
//     f32 temp_f6;
//     s32 temp_v0;
//     u16 temp_t6;
//     u8 temp_t3;
//     u8 temp_v1;
//     s32 temp_a0;
//     struct108 *temp_a0_2;
//     f32 phi_f0;
//     s32 phi_a2;
//
//     sp74 = (u16)arg0->unk278;
//     sp6C = 0;
//     sp70 = 0.0f;
//
//     switch (sp74) {
//         case 0x1F:
//             arg0->unkB8 = (arg0->unkB8 + (arg0->xz_velocity * (f32) D_800BE9E4));
//             if (arg0->unk2E4 == 1) {
//                 func_10010344(0x230, arg0, 0x7D00, 0x1F4, 0x9C4);
//                 arg0->unk2E4 = 0;
//             }
//             break;
//         case 0x35:
//             arg0->unkB8 = (arg0->unkB8 + (f32) (D_800BE9E4 * 0x10));
//             break;
//         case 0x42:
//             sp70 = 25.0f;
//             if (arg0->gravity != 0.0f) {
//                 temp_f12 = arg0->y_velocity;
//                 if ((temp_f12 > 0.0f) || (arg0->unk28 > 25.0f)) {
//                     arg0->unkB8 = (-func_150484A0(temp_f12, arg0->xz_velocity) * D_80099408);
//                 }
//             }
//             temp_v0 = func_15081574(arg0, 40.0f, 10.0f, &sp64, 0xF, 0x53);
//             if (temp_v0 != 0) {
//                 func_15055260(arg0, sp64, temp_v0 - 1);
//                 func_15060F28(arg0, 1);
//                 return;
//             }
//             break;
//         case 0x4E:
//             sp70 = 25.0f;
//             if (arg0->unk28 > 25.0f) {
//                 arg0->unkB8 = (arg0->unkB8 + (f32) (D_800BE9E4 * 3));
//             }
//             break;
//         case 0x88:
//             temp_f6 = -func_150484A0(arg0->y_velocity, arg0->xz_velocity) * D_8009940C;
//             arg0->unkD0 = 0x10;
//             arg0->unkB8 = temp_f6;
//             if (func_1505C7D8(arg0, D_800C3E78) != 0) {
//                 func_15060F28(arg0, 1);
//                 return;
//             }
//     }
//     func_15059C84(arg0);
//     arg0->stunned = 1;
//     func_1505A770(arg0);
//     sp84 = arg0->unk14;
//     sp80 = arg0->unk18;
//     sp7C = arg0->unk1C;
//     func_15058898(arg0, arg0->unk30);
//     temp_f0 = arg0->unk118;
//     if ((temp_f0 != D_80099410) && (arg0->unk18 <= temp_f0) && (temp_f0 <= *(f32*)&arg0->unk30)) {
//         arg0->unk2E4 = 2;
//         arg0->gravity = 0.0f;
//         arg0->y_velocity = -3.0f;
//         arg0->xz_velocity *= D_80099414;
//     } else if ((sp84 != arg0->unk14) || (sp80 != arg0->unk18) || (sp7C != arg0->unk1C)) {
//         sp6C = 1;
//         if ((sp74 == 0x1F) && (arg0->unk2E4 != 2)) {
//             func_10010344(((func_150ADA20() % 5U) + 0x3A4), arg0, 0x7D00, 0x1F4, 0x9C4);
//         }
//     }
//     func_1505B5F8(arg0, arg0->unk180);
//     if (arg0->unk28 <= sp70) {
//         temp_a0 = arg0->unk14;
//         arg0->unk7F = (u8) (arg0->unk7F + 1);
//         sp6C = sp6C | 2;
//         if ((arg0->unk184 & 0x1F) == 0xE) {
//             func_1514AD9C(temp_a0, 0xFF, 0); // actually f32?
//             func_15060F28(arg0, 1);
//             return;
//         }
//         if (sp74 == 0x42) {
//             D_800D1580 = 0xFF0100B0; // ?
//             if (arg0->gravity != 0.0f) {
//                 func_1506E5FC();
//             }
//             arg0->gravity = 0.0f;
//             temp_f12 = *(f32*)&arg0->unk30;
//             temp_f0 = arg0->unk18 - temp_f12;
//             arg0->y_velocity = 0.0f;
//             arg0->xz_velocity = 0.0f;
//             arg0->unk18 = (*(f32*)&arg0->unk180 + sp70);
//             if (temp_f0 != 0.0f) {
//                 phi_f0 = (arg0->unk18 - temp_f12) / temp_f0;
//             } else {
//                 phi_f0 = 0.0f;
//             }
//             temp_f2 = arg0->unk2C;
//             temp_f12 = arg0->unk34;
//             arg0->unk14 = temp_f2 + ((arg0->unk14 - temp_f2) * phi_f0);
//             arg0->unk1C = temp_f12 + ((arg0->unk1C - temp_f12) * phi_f0);
//         } else if (arg0->unk18 < arg0->unk118) {
//             arg0->gravity = 0.0f;
//             arg0->y_velocity = 0.0f;
//             arg0->xz_velocity = 0.0f;
//         } else if ((arg0->y_velocity > 5.0f) && (sp74 == 0x1F) && (arg0->unk2E4 != 2)) {
//             func_10010344(0x39E, arg0, 0x7D00, 0x1F4, 0x9C4);
//             arg0->unk2E4 = 2;
//         }
//     }
//     arg0->unk40 = ((arg0->unk76 + 0x4000) * 0.005493164f);
//     if ((sp6C != 0) && (sp74 == 0x35)) {
//         func_10010630(0x360, arg0, 0x4E20, 0x1F4, 0x9C4);
//         if (arg0->unk118 < arg0->unk18) {
//             tmp0.unk0 = arg0->unk14;
//             tmp0.unk4 = arg0->unk18 + 20.0f;
//             tmp0.unk8 = arg0->unk1C;
//             func_151DCDE0(&tmp0, 0xFF, 1);
//         }
//         func_15060F28(arg0, 1);
//         return;
//     }
//     temp_t3 = arg0->unk83 - 1;
//     temp_v0 = temp_t3 & 0xFF;
//     arg0->unk83 = temp_t3;
//     if ((temp_v0 == 0) || (arg0->unk7F >= 0x1F)) {
//         func_15060F28(arg0, 1);
//         return;
//     }
//
//     temp_v1 = arg0->unk7F;
//     if (temp_v0 < 0xA) {
//         phi_a2 = (s32) (temp_v0 * 0xFF) / 0xA;
//     } else {
//         phi_a2 = 0xFF;
//         if (temp_v1 >= 0x15) {
//             phi_a2 = (s32) ((-(s32) temp_v1 * 0xFF) + 0x1DE2) / 0xA;
//         }
//     }
//     func_1503192C(arg0, sp74, phi_a2, 0);
//     if (sp74 == 0x1F) {
//         temp_a0_2 = D_800DBFF0;
//         temp_f0 = temp_a0_2->unk2F8 - arg0->unk14;
//         temp_f2 = temp_a0_2->unk2FC - arg0->unk18;
//         temp_f12 = temp_a0_2->unk300 - arg0->unk1C;
//         temp_f14 = (temp_f0 * temp_f0) + (temp_f2 * temp_f2) + (temp_f12 * temp_f12);
//         if (temp_f14 < 900.0f) {
//             func_1512D748(temp_f12, temp_f14, temp_a0_2, 8, 0);
//             func_10010F88(0x2E1, 0x6D60, 0, 0, 0, arg0->unk14, arg0->unk18, arg0->unk1C, 0x1F4, 0x3E8);
//             func_10010A3C(arg0);
//             func_15060F28(arg0, 1);
//         }
//     }
// }

void func_15055A2C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    s32 phi_a0 = 1549;
    s32 phi_v1 = 1000;

    if (arg4 == 1) {
        phi_a0 = 1549;
        phi_v1 = 100;
    } else {
        phi_a0 = D_8009919C[func_150ADA20() % 6U];
    }
    func_10010F88(phi_a0, 32700, func_150ADA20() % 500U, 0, 0, arg1,  arg2, arg3, phi_v1, 3000);
}

void func_15055B0C(struct127 *arg0, s32 arg1) {
    arg0->interaction_state = 39;
    func_1505E650(arg0, arg0->unk84.uh, 0, 0.0f, 0.0f, 0.0f, 0);
    arg0->unkE4 = 0;
    arg0->unkE6 = 0;
    arg0->unk21C = arg1;
}

void func_15055B64(struct127 *arg0) {
    arg0->unk40 = (s16)(arg0->unk7A + 16384) * 0.005493164f;
    arg0->unkF8 |= 0x1000000;

    if (D_800BE9A0 < arg0->unk21C) {
        arg0->unk21C -= D_800BE9E4;
    } else {
        arg0->unk21C = 0;
        if (arg0->unk1D4 == 0) {
            func_15060F28(arg0, 1);
        }
    }
}

void func_15055BF8(struct127 *arg0) {
    arg0->unk40 = (s16)(arg0->unk7A + 16384) * 0.005493164f;
    arg0->unkF8 |= 0x1000000;
    arg0->y_position -= D_800BE9A4;

    if (arg0->y_position < (arg0->unk180 - 100.0f)) {
        func_15060F28(arg0, 0);
    }
}

void func_15055C88(struct127 *arg0) {
    s32 sp2C = 2099172; // 0x2007E4;
    if (((arg0->unk9C & 0x1000) == 0) && func_1506E46C(arg0, &sp2C, 1)) {
        func_15060A30(sp2C, arg0);
    }
    arg0->unk31C->unk36 = 100;
    func_1506160C(arg0, 2, 0, 6, 0);
    if (0) {};
    arg0->disable_run = 200;
    arg0->unk83 = 200;
    arg0->unk1CC = 70000.0f;
    arg0->interaction_state = 41;
    arg0->gravity = 0.0f;
    arg0->y_velocity = 0.0f;
    arg0->xz_velocity = 0.0f;
    func_1507CD64(arg0, 9);
}

void func_15055D48(struct127 *arg0) {
    f32 temp_f0;

    arg0->unk31C->unk36 += D_800BE9A0;
    if (arg0->unk31C->unk36 >= 0x8D) {
        D_800D18A0 |= (1 << (((s32)arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127)));
        if (D_800D18A0 != 0) {
            arg0->immune = 0xFF;
            arg0->stunned = 0xFF;
            arg0->disable_run = 0xFF;
            arg0->unkF8 |= 0x200;
            arg0->unkE4 = 0;
            arg0->unkE6 = 0;
            arg0->unk7 = 0;
            arg0->health = 0;
            arg0->interaction_state = 5;
            arg0->xz_velocity = 0.0f;
            arg0->y_velocity = 0.0f;
            arg0->gravity = 0.0f;
            return;
        }
        func_1506D538();
    }
    temp_f0 = 0.95f;
    arg0->health = 0;
    arg0->xz_scale *= temp_f0;
    arg0->y_scale *= temp_f0;
    arg0->xz_velocity *= temp_f0;
}
