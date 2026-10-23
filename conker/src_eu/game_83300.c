#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15049350(s32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
s32 func_15022A8C(struct127 *);
extern u8 D_800C3A78;
s32 func_1505E0C4(struct127 *, s32, u8 *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
void func_15059C84(struct127 *);
void func_1505A770(struct127 *);
void func_15060A9C(s32 arg0, struct127 *arg1);
void func_1505D6F0(struct127 *, s32);
s32 func_1505C7D8(struct127 *self, s32 skip);
void func_15060F28(struct127 *obj, s32 mode);
void func_150849C0(struct127 *);
void func_150626EC(struct127 *, s32);
void func_15060D54(struct127 *);
void func_1504AF10(struct127 *, s32, s32);
void func_1503E550(s32 arg0);
void func_10004074(s32 arg0);
s32 func_1514D880(u8 *arg0);
void func_151695F0(u8 *arg0, u8 arg1);
s32 func_150306D4(u8 *arg0);
void func_15189040(s32 arg0);
extern u8 *D_800D252C;
void func_15061B4C(void);
void func_15062D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_15062E24(s32, s32, s32, s32, s32, s32, s32);
void func_15062FC0(u8 *, s32, s32, s32, s32, s32, s32, s32);
s32 func_150ADA20(void);
f32 func_150489B0(u8);
void func_eu_1501B640(struct127 *, f32 *, s32);
void func_eu_150F2230(u8 *arg0);
extern s32 D_800997EC[];
extern s32 D_80086490;
extern s32 D_800C4440;
extern s32 D_800CC298;
extern s32 D_800D121C;
extern s32 D_800BE9F0;
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

#ifdef NON_MATCHING
/* Hit reaction of an object: row D_80099DFC[row] gives an animation per strength (a1 above row[7]: heavy,
 * above row[2]: medium, else light) and side (front / back from the angles +0x76 / +0x78); 0xFF = none. Starts
 * it: health +0x218 -5, stun timer +0x21C, state 13, speed +0x44 = 0, move flags +0xF4 = 4, faces +0x76. */
void func_15056A00(struct127 *obj, s32 arg1, u8 row) {
    u8 *o = (u8 *)obj;
    u8 strength = arg1;
    u8 *anims = D_80099DFC[row];
    u8 idx;
    u16 angle;

    idx = 0;
    if (anims[7] < strength) {
        idx = 5;
    } else if (anims[2] < strength) {
        idx = 2;
    }
    angle = *(u16 *)(o + 0x76);
    if ((*(u16 *)(o + 0x78) - angle) & 0x8000) {
        idx += 3;
    } else {
        idx += 4;
    }
    if (anims[idx] != 0xFF) {
        *(s32 *)(o + 0x218) -= 5;
        *(s16 *)(o + 0x21C) = 20000;
        o[0x223] = 13;
        *(f32 *)(o + 0x44) = 0.0f;
        *(s32 *)(o + 0xF4) = (*(s32 *)(o + 0xF4) & ~0xE) | 4;
        *(u16 *)(o + 0x78) = angle;
        *(u16 *)(o + 0x7A) = angle;
        o[0x138] = 0;
        *(s16 *)(o + 0x244) = anims[idx];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056A00.s")
#endif
#ifdef NON_MATCHING
void func_15047680(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_15059B54(struct127 *arg0, u16 arg1);
struct216 *func_1507BB28(s32, s32);
extern f32 D_800CC704;
extern f32 D_800CC70C;
extern s32 D_800D1968;

void func_15056B08(struct127 *arg0) {
    f32 sp98[4][4];
    u8 *temp_v0_13;
    u8 var_v1_4;
    u8 var_v1_2;
    u8 var_v1;
    u8 var_t0_2;
    u8 var_t0;
    u8 temp_v1_7;
    u8 temp_v1_6;
    u8 temp_v1_5;
    u8 temp_v1_2;
    u8 temp_v0_9;
    u8 temp_v0_8;
    u8 temp_v0_5;
    u8 temp_v0_4;
    u8 temp_v0_2;
    u8 temp_v0_17;
    u8 temp_v0_16;
    u8 temp_v0_15;
    u8 temp_v0_11;
    u8 temp_v0;
    u8 temp_t9;
    u8 temp_t8_2;
    u8 temp_t8;
    u8 temp_t6;
    u8 temp_t5;
    u8 temp_t4;
    u8 temp_t1_2;
    u8 temp_t1;
    u8 temp_a0_2;
    u8 temp_a0;
    u16 var_v0_2;
    u16 var_a2_3;
    u16 temp_v1_3;
    u16 temp_v0_10;
    u16 temp_t3;
    u16 temp_a1;
    struct216 *var_v0;
    struct127 *var_a2;
    struct127 *var_a0;
    struct127 *temp_v1_4;
    struct127 *temp_v0_18;
    struct127 *temp_v0_14;
    struct127 *temp_v0_12;
    struct126 *temp_v0_7;
    struct126 *temp_v0_6;
    s8 temp_v1_8;
    s32 var_v1_3;
    s32 var_a3;
    s32 var_a2_2;
    s32 var_a1;
    s32 temp_v1;
    s32 temp_v0_3;
    s32 temp_v0_19;
    s32 temp_t7;
    s32 temp_hi;
    f32 var_f8_3;
    f32 var_f8_2;
    f32 var_f8;
    f32 var_f6_3;
    f32 var_f6_2;
    f32 var_f6;
    f32 var_f4;
    f32 var_f2_3;
    f32 var_f2_2;
    f32 var_f2;
    f32 var_f16_2;
    f32 var_f16;
    f32 var_f14;
    f32 var_f12;
    f32 var_f10_2;
    f32 var_f10;
    f32 var_f0_3;
    f32 var_f0_2;
    f32 var_f0;
    f32 temp_f8_2;
    f32 temp_f8;
    f32 temp_f4_5;
    f32 temp_f4_4;
    f32 temp_f4_3;
    f32 temp_f4_2;
    f32 temp_f4;
    f32 temp_f2_5;
    f32 temp_f2_4;
    f32 temp_f2_3;
    f32 temp_f2_2;
    f32 temp_f2;
    f32 temp_f18;
    f32 temp_f16;
    f32 temp_f14_3;
    f32 temp_f14_2;
    f32 temp_f14;
    f32 temp_f12_6;
    f32 temp_f12_5;
    f32 temp_f12_4;
    f32 temp_f12_3;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 temp_f10;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp3C;
    struct127 *sp48;
    s32 sp4C;
    f32 sp60;
    f32 sp64;
    f32 sp68;
    u16 sp78;
    f32 sp7C;
    f32 sp80;
    f32 sp84;
    s32 sp88;
    f32 sp8C;
    f32 sp90;
    f32 sp94;
    f32 spE0;
    f32 spE4;
    u8 spEB;
    s32 spF0;
    f32 spF4;
    f32 sp100;
    s32 sp104;
    s32 sp108;
    s32 sp10C;
    f32 sp11C;
    f32 sp120;
    f32 sp124;
    f32 sp12C;
    f32 sp130;
    struct124 *sp134;
    u8 sp13B;
    f32 sp13C;
    f32 sp144;
    u8 sp149;
    u16 sp14A;
    f32 sp14C;
    u8 sp153;
    f32 sp154;
    f32 sp158;
    u8 sp15F;
    f32 sp160;
    f32 sp164;
    f32 sp16C;
    f32 sp170;
    f32 sp174;

    sp13B = 1;
    temp_v0 = arg0->unk23A;
    if (temp_v0 != 0) {
        arg0->unk218 = func_1507BB28(4, temp_v0);
        arg0->unk21C = 0;
        arg0->unk23A = 0;
    }
    if ((D_800C3638 == 0) || (func_15022A8C(arg0) == 0)) {
        if ((arg0->unkF4 & 0x1000) && (arg0->unk28 < 0.2f)) {
            arg0->unk21C = 0;
        }
        func_1507BC14(arg0);
        var_v1 = arg0->unk223;
        var_t0 = var_v1;
        if ((var_v1 == 0xE) || (var_v1 == 0xF) || (var_v1 == 0x10)) {
            var_v1 = 1;
            var_t0 = 1;
        }
        if (var_t0 == 0x11) {
            var_v1 = 0;
        }
        if (arg0->stunned == 0) {
            sp14A = (u16) ((s32) (((arg0->unk1E5 << 8) + arg0->unk1E7) * D_800CC264) / 100);
            sp149 = arg0->unk1E6;
            temp_v0_2 = arg0->unk13F;
            if (D_800D2528[temp_v0_2] == 0) {
                arg0->xz_velocity = 0.0f;
                func_1505841C(arg0, 0.0f);
                return;
            }
            var_t0_2 = var_v1;
            sp134 = D_800D1C90[arg0->id];
            temp_a0 = arg0->unk23D;
            if (temp_a0 == 0xFF) {
                sp164 = 1e9f;
            } else {
                temp_f4 = (f32) (temp_a0 * 8);
                sp164 = temp_f4;
                sp164 = temp_f4 * temp_f4;
            }
            temp_v1 = D_800D2104[temp_v0_2];
            if ((*(u16 *)((u8 *)temp_v1 + 6)) != 0) {
                sp174 = (f32) (*(s16 *)((u8 *)temp_v1 + 0)) - arg0->x_position;
                sp170 = (f32) (*(s16 *)((u8 *)temp_v1 + 4)) - arg0->z_position;
            }
            temp_v0_3 = arg0->unk25C;
            if ((temp_v0_3 & 4) && !(temp_v0_3 & 1) && ((var_t0_2 == 1) || (var_t0_2 == 3))) {
                arg0->unk21C = 0;
            }
            if ((arg0->unk25C & 1) && ((var_t0_2 == 0) || (var_t0_2 == 5))) {
                sp4C = (s32) var_t0_2;
                var_t0_2 = (u8) sp4C;
                if (func_1505693C(arg0, (s32) arg0->unk25B) != 0) {
                    sp4C = (s32) var_t0_2;
                    temp_v1_2 = arg0->unk25B;
                    var_t0_2 = (u8) sp4C;
                    arg0->unk218 = func_1507BB28(1, arg0->unk233);
                    arg0->unk21C = 0;
                    arg0->unkA8 = temp_v1_2 | 0x80;
                    arg0->unk222 = temp_v1_2;
                }
            }
            temp_v0_4 = arg0->unk25A;
            if (temp_v0_4 != 0) {
                var_f10 = (f32) temp_v0_4;
                if ((s32) temp_v0_4 < 0) {
                    var_f10 += 4294967296.0f;
                }
                arg0->unk44 = var_f10;
            }
            if ((var_t0_2 == 1) || (var_t0_2 == 0xC) || (var_t0_2 == 2) || (var_t0_2 == 3) || (var_t0_2 == 9) || (var_t0_2 == 0xA) || ((var_t0_2 == 6) && !(arg0->unk22C & 1))) {
                var_v1_2 = arg0->unk222;
                var_a2 = &D_800CC2D0[var_v1_2];
                sp174 = var_a2->x_position;
                sp170 = var_a2->z_position;
                sp16C = var_a2->y_position;
                if (arg0->unk223 == 0x10) {
                    sp15F = var_v1_2;
                    sp48 = var_a2;
                    sp4C = (s32) var_t0_2;
                    temp_f0 = func_1505A72C(var_a2, arg0);
                    sp120 = temp_f0;
                    temp_t6 = arg0->unk231;
                    var_f8 = (f32) temp_t6;
                    if ((s32) temp_t6 < 0) {
                        var_f8 += 4294967296.0f;
                    }
                    temp_f4_2 = sp48->xz_velocity * (temp_f0 / var_f8);
                    sp124 = temp_f4_2;
                    func_1505A184(sp48->unk76, temp_f4_2, 0.0f, &sp124, &sp120, &sp11C);
                    var_v1_2 = sp15F;
                    var_t0_2 = (u8) sp4C;
                    var_a2 = sp48;
                    sp174 += sp124;
                    sp170 += sp120;
                }
                temp_f8 = sp174 - arg0->x_position;
                sp130 = temp_f8;
                var_f16 = sp170 - arg0->z_position;
                var_f12 = sqrtf((temp_f8 * temp_f8) + (var_f16 * var_f16));
                if ((var_t0_2 == 1) && (arg0->unk44 > 1.0f) && (sqrtf(sp164) < (var_f12 * 0.8f))) {
                    arg0->unk21C = 0;
                }
                temp_v0_5 = arg0->id;
                if (temp_v0_5 != 0x16) {
                    if ((var_t0_2 == 1) && (arg0->unk234 != 0) && ((var_f12 < 370.0f) || (temp_v0_5 == 0x21)) && ((s32) var_v1_2 < 4) && ((arg0->xz_velocity > 15.0f) || (temp_v0_5 == 0x53))) {
                        temp_v0_6 = var_a2->unk31C;
                        if (temp_v0_6 != NULL) {
                            temp_v0_6->chased = 0xA;
                        }
                    }
                    if ((var_t0_2 == 2) && (var_f12 < 470.0f) && ((s32) var_v1_2 < 4) && (((arg0->unk76 - var_a2->unk76) - 0x4000) & 0x8000)) {
                        temp_v0_7 = var_a2->unk31C;
                        if (temp_v0_7 != NULL) {
                            temp_v0_7->chasing = 6;
                        }
                    }
                }
                switch (var_t0_2) {                 /* irregular */
                case 9:
                    break;
                default:
                    sp13B = 0;
                    /* fallthrough */
                case 10:
                case 12:
                    if ((arg0->unk22C & 0x80) && (fabsf((arg0->y_position - arg0->unk28) - (var_a2->y_position - var_a2->unk28)) > 30.0f)) {
                        arg0->unk21C = 0;
                    }
                    sp48 = var_a2;
                    if (arg0->unk223 != 0xF) {
                        sp12C = var_f16;
                        sp160 = var_f12;
                        sp4C = (s32) var_t0_2;
                        sp48 = var_a2;
                        var_t0_2 = (u8) sp4C;
                        var_f12 = sp160;
                        var_f16 = sp12C;
                        if (func_1505693C(arg0, (s32) arg0->unk222) == 0) {
                            arg0->unk21C = 0;
                        }
                    }
                    if ((u16) arg0->unk22E != 0) {
                        var_f2 = 0.0f;
                    } else {
                        temp_v0_8 = arg0->unk236;
                        if (temp_v0_8 == 0) {
                            var_f2 = (f32) (arg0->unk23C * 8);
                        } else if (temp_v0_8 == 0xFF) {
                            var_f2 = 3000000.0f;
                        } else {
                            var_f2 = (f32) (temp_v0_8 * 8);
                        }
                    }
                    if (((var_t0_2 == 1) || (var_t0_2 == 6) || (var_t0_2 == 0xA)) && (arg0->unk234 != 0) && (var_f12 < var_f2)) {
                        var_v1_3 = 1;
                        if ((arg0->id == 8) && (var_f2 < fabsf(arg0->y_position - sp48->y_position))) {
                            var_v1_3 = 0;
                        }
                        temp_v0_9 = arg0->unk22A;
                        if (temp_v0_9 != 0) {
                            var_f4 = (f32) temp_v0_9;
                            if ((s32) temp_v0_9 < 0) {
                                var_f4 += 4294967296.0f;
                            }
                            if ((D_800C3E78 != 0) && (fabsf(arg0->y_position - *D_800CC2E8) < (var_f4 * 8.0f))) {
                                var_v1_3 = 0;
                            }
                        }
                        if (var_v1_3 != 0) {
                            sp4C = (s32) var_t0_2;
                            temp_v0_10 = func_1505A630(sp130, -var_f16, 0);
                            temp_a0_2 = arg0->unk237;
                            var_t0_2 = (u8) sp4C;
                            if ((temp_a0_2 != 0) && (((((s32) (arg0->unk76 - temp_v0_10) >> 8) + ((s32) temp_a0_2 / 2)) & 0xFF) < (s32) temp_a0_2)) {
                                sp4C = (s32) var_t0_2;
                                var_t0_2 = (u8) sp4C;
                                arg0->unk218 = func_1507BB28(2, arg0->unk234);
                                arg0->unk21C = 0;
                            }
                        }
                    }
                    break;
                }
            }
            if (sp13B != 0) {
                temp_v1_3 = (u16) arg0->unk22E;
                if (arg0->unk235 != 0) {
                    sp10C = 0;
                } else {
                    sp10C = 1;
                }
                if (temp_v1_3 != 0) {
                    if ((s32) D_800BE9A0 >= (s32) temp_v1_3) {
                        arg0->unk22E = 0;
                    } else {
                        arg0->unk22E = temp_v1_3 - D_800BE9A0;
                    }
                }
                if (arg0->unk241 != 0) {
                    var_a3 = 0;
                    var_a0 = D_800CC2D0;
                    var_a1 = 0;
                    var_f16_2 = (f32) (arg0->unk23F * 8);
                    do {
                        if ((var_a0->interaction_state != 0) && (arg0->unk240 == var_a0->id) && (var_a0->unk2FA != 0)) {
                            temp_f12 = var_a0->x_position - arg0->x_position;
                            temp_f14 = arg0->z_position - var_a0->z_position;
                            temp_f2 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14));
                            if (temp_f2 < var_f16_2) {
                                sp100 = var_f16_2;
                                spF4 = temp_f2;
                                spF0 = (s32) (sp134->unk17 * 3) / 2;
                                sp4C = (s32) var_t0_2;
                                sp104 = var_a3;
                                sp108 = var_a1;
                                sp48 = var_a0;
                                var_a0 = sp48;
                                var_a1 = sp108;
                                var_a3 = sp104;
                                var_t0_2 = (u8) sp4C;
                                var_f16_2 = sp100;
                                if ((((((s32) arg0->unk7A >> 8) - (func_1505A630(temp_f12, temp_f14, 0) >> 8)) + (spF0 / 2)) & 0xFF) < spF0) {
                                    var_a3 = var_a1 + 1;
                                    var_f16_2 = spF4;
                                }
                            }
                        }
                        var_a1 += 1;
                        var_a0 += 1;
                    } while (var_a1 != 0x19);
                    if (var_a3 != 0) {
                        sp4C = (s32) var_t0_2;
                        sp104 = var_a3;
                        var_t0_2 = (u8) sp4C;
                        arg0->unk218 = func_1507BB28(0, arg0->unk241);
                        arg0->unk21C = 0;
                        arg0->unk222 = sp104 - 1;
                        arg0->unkA8 = sp104 + 0x7F;
                        arg0->unk22E = 5;
                        if (arg0->unk242 != 0) {
                            temp_v1_4 = &D_800CC2D0[sp104];
                            D_800D154C = temp_v1_4 - 1;
                            sp4C = (s32) var_t0_2;
                            sp48 = temp_v1_4;
                            (*(struct216 **)((u8 *)sp48 + -0x114)) = func_1507BB28(0, arg0->unk242);
                            (*(s16 *)((u8 *)sp48 + -0x110)) = 0;
                            var_t0_2 = (u8) sp4C;
                            (*(u8 *)((u8 *)sp48 + -0x10A)) = (u8) D_800C3E78;
                            D_800D154C = arg0;
                        }
                    }
                }
                if (((u16) arg0->unk22E == 0) && (var_t0_2 != 4) && (var_t0_2 != 7) && (((sp10C == 0) && (arg0->unk235 != 0)) || ((sp10C == 1) && (arg0->unk233 != 0) && !(arg0->unk25C & 4)))) {
                    temp_t8 = (*(u8 *)((u8 *)sp134 + 0x18));
                    var_f10_2 = (f32) temp_t8;
                    if ((s32) temp_t8 < 0) {
                        var_f10_2 += 4294967296.0f;
                    }
                    if (var_f10_2 <= arg0->xz_velocity) {
                        sp4C = (s32) var_t0_2;
                        var_t0_2 = (u8) sp4C;
                        if (func_1505693C(arg0, 0) != 0) {
                            spEB = 0;
                            temp_f12_2 = D_800CC704 - (f32) arg0->unk1A4;
                            temp_f14_2 = (f32) arg0->unk1A8 - D_800CC70C;
                            if ((arg0->id == 0x9E) && (arg0->unk2E4 == 0)) {
                                sp164 = 129600.0f;
                            }
                            temp_f0_2 = (temp_f12_2 * temp_f12_2) + (temp_f14_2 * temp_f14_2);
                            if ((temp_f0_2 < sp164) && (temp_f0_2 < 1e8f)) {
                                sp4C = (s32) var_t0_2;
                                spE4 = temp_f12_2;
                                spE0 = temp_f14_2;
                                var_t0_2 = (u8) sp4C;
                                if (func_1505693C(arg0, 0) != 0) {
                                    temp_v0_11 = arg0->unk229;
                                    if (temp_v0_11 == 0xFF) {
                                        var_f2_2 = sqrtf(sp164);
                                    } else {
                                        var_f6 = (f32) temp_v0_11;
                                        if ((s32) temp_v0_11 < 0) {
                                            var_f6 += 4294967296.0f;
                                        }
                                        var_f2_2 = var_f6 * 8.0f;
                                    }
                                    if ((D_800C3E78 != 0) && ((temp_v0_11 == 0) || (fabsf(arg0->y_position - *D_800CC2E8) < var_f2_2))) {
                                        if (arg0->id == 0x9E) {
                                            sp4C = (s32) var_t0_2;
                                            func_1505A184(arg0->unk7A, 9000.0f, arg0->unkB8, &sp94, &sp90, &sp8C);
                                            temp_f10 = sp94 + arg0->x_position;
                                            sp94 = temp_f10;
                                            temp_f8_2 = sp90 + arg0->z_position;
                                            sp90 = temp_f8_2;
                                            temp_f4_3 = sp8C + arg0->y_position;
                                            sp8C = temp_f4_3;
                                            func_15047680(sp98, arg0->x_position, arg0->y_position, arg0->z_position, temp_f10, temp_f4_3, temp_f8_2, 0.0f, 1.0f, 0.0f);
                                            var_t0_2 = (u8) sp4C;
                                            if (func_15049440(sp98, D_800CC704, *D_800CC2E8, D_800CC70C, 80.0f, 80.0f, 0.0f, 4000.0f, 320.0f, 320.0f) != 0) {
                                                spEB = 1;
                                            }
                                        } else {
                                            var_v1_4 = sp134->unk17;
                                            if (sp10C == 0) {
                                                var_v1_4 *= 3;
                                            }
                                            sp88 = (s32) var_v1_4;
                                            sp4C = (s32) var_t0_2;
                                            var_t0_2 = (u8) sp4C;
                                            if (((((((s32) arg0->unk7A >> 8) + arg0->unk2CA) - (func_1505A630(spE4, spE0, 0) >> 8)) + (sp88 / 2)) & 0xFF) < sp88) {
                                                spEB = 1;
                                            }
                                        }
                                    }
                                }
                            }
                            if (spEB != 0) {
                                if (sp10C == 0) {
                                    sp4C = (s32) var_t0_2;
                                    var_v0 = func_1507BB28(3, arg0->unk235);
                                    var_t0_2 = (u8) sp4C;
                                } else {
                                    sp4C = (s32) var_t0_2;
                                    var_v0 = func_1507BB28(1, arg0->unk233);
                                    var_t0_2 = (u8) sp4C;
                                }
                                arg0->unk218 = var_v0;
                                arg0->unk21C = 0;
                                arg0->unk222 = spEB - 1;
                                arg0->unkA8 = spEB + 0x7F;
                            }
                        }
                    }
                }
                if (var_t0_2 != 9) {
                    if ((var_t0_2 == 6) || (var_t0_2 == 0xC)) {
                        temp_v0_12 = &D_800CC2D0[arg0->unk222];
                        sp174 = temp_v0_12->x_position;
                        sp170 = temp_v0_12->z_position;
                        sp16C = temp_v0_12->y_position;
                    } else {
                        temp_v0_13 = D_800D2104[arg0->unk13F] + (arg0->unk21E * 8);
                        sp174 = (f32) (*(s16 *)((u8 *)temp_v0_13 + 8));
                        sp170 = (f32) (*(s16 *)((u8 *)temp_v0_13 + 0xC));
                        sp16C = (f32) (*(s16 *)((u8 *)temp_v0_13 + 0xA));
                    }
                    if ((var_t0_2 == 5) || (var_t0_2 == 6)) {
                        if ((var_t0_2 == 6) && (arg0->unk22C & 1)) {
                            arg0->unk86 = (u8) (D_800CC2D0[arg0->unk222].unk7A >> 8);
                        }
                        temp_t4 = arg0->unk258;
                        arg0->unk86 += arg0->unk257;
                        var_f8_2 = (f32) temp_t4;
                        if ((s32) temp_t4 < 0) {
                            var_f8_2 += 4294967296.0f;
                        }
                        temp_f4_4 = var_f8_2 * 16.0f;
                        sp84 = temp_f4_4;
                        sp4C = (s32) var_t0_2;
                        func_1505A184((arg0->unk86 << 8) & 0xFFFF, temp_f4_4, 0.0f, &sp84, &sp80, &sp7C);
                        var_t0_2 = (u8) sp4C;
                        sp174 += sp84;
                        sp170 += sp80;
                    }
                }
            }
            temp_f12_3 = arg0->unk44;
            sp14C = temp_f12_3;
            if ((var_t0_2 != 7) && (var_t0_2 != 8)) {
                temp_f16 = arg0->x_position;
                temp_f4_5 = sp174 - temp_f16;
                sp174 = temp_f4_5;
                temp_f18 = arg0->z_position;
                sp170 = temp_f18 - sp170;
                sp16C = arg0->y_position - sp16C;
                if ((var_t0_2 == 6) && (arg0->unk22C & 1) && ((fabsf(sp170) + fabsf(temp_f4_5)) < 100.0f)) {
                    sp14C = 0.0f;
                    sp4C = (s32) var_t0_2;
                    temp_v0_14 = &D_800CC2D0[arg0->unk222];
                    sp174 = temp_v0_14->x_position - temp_f16;
                    sp170 = temp_f18 - temp_v0_14->z_position;
                    var_v0_2 = func_1505A630(sp174, sp170, 0);
                    var_t0_2 = (u8) sp4C;
                    goto block_182;
                }
                if ((temp_f12_3 >= 0.5f) && !(arg0->unkF4 & 0x40)) {
                    sp4C = (s32) var_t0_2;
                    var_v0_2 = func_1505A630(sp174, sp170, 0);
                    var_t0_2 = (u8) sp4C;
block_182:
                    arg0->unk78 = var_v0_2;
                }
            }
            temp_t8_2 = arg0->unk247;
            var_f6_2 = (f32) temp_t8_2;
            if ((s32) temp_t8_2 < 0) {
                var_f6_2 += 4294967296.0f;
            }
            sp158 = var_f6_2 / 10.0f;
            temp_f12_4 = (sp174 * sp174) + (sp170 * sp170);
            var_f2_3 = temp_f12_4;
            if (arg0->unk22C & 8) {
                var_f2_3 = temp_f12_4 + (sp16C * sp16C);
            }
            temp_f2_2 = sqrtf(var_f2_3);
            if ((var_t0_2 != 4) && (var_t0_2 != 7) && (var_t0_2 != 8)) {
                sp78 = arg0->unk76;
                if (var_t0_2 == 2) {
                    temp_t3 = arg0->unk78 ^ 0x8000;
                    arg0->unk78 = temp_t3;
                    if (!(arg0->unkF4 & 0x4000)) {
                        arg0->unk78 = temp_t3 + (((((s32) arg0->unk21C / 100) & 0x20) - 0x10) << 8);
                    }
                }
                if (arg0->unk223 == 0x11) {
                    arg0->unk78 += ((((s32) arg0->unk21C / 100) & 0x10) - 8) << 9;
                }
                if ((arg0->unkF4 & 0x200) && (arg0->unk1F4 < 3.0f)) {
                    sp14A = 0;
                    sp149 = 0;
                }
                sp3C = temp_f12_4;
                sp144 = temp_f2_2;
                sp4C = (s32) var_t0_2;
                sp13C = (f32) (arg0->unk23E * 8);
                temp_v0_15 = func_15059B54(arg0, sp14A);
                sp153 = temp_v0_15;
                if (sp4C != 0xD) {
                    temp_v1_5 = (u8) arg0->unk24F;
                    if ((temp_v1_5 != 0) && ((sp4C != 0) || (sp13C < sp144))) {
                        temp_t9 = (temp_v1_5 - 1) & 0xFF;
                        if ((s32) *D_80099DFC[temp_t9] < (temp_v0_15 & 0xFF)) {
                            arg0->unk76 = sp78;
                            func_15056A00(arg0, (s32) sp153, temp_t9);
                        }
                    }
                }
                if (sp4C == 0xD) {
                    sp14A = 0;
                    sp149 = 0;
                }
                if (((s32) (*(u8 *)((u8 *)sp134 + 0x19)) < (s32) sp153) && (sp4C != 2)) {
                    sp14C = 0.0f;
                    temp_v0_16 = arg0->unk24A;
                    if ((temp_v0_16 != 0) && (arg0->xz_velocity > 15.0f)) {
                        arg0->unk218 = func_1507BB28(6, temp_v0_16);
                        arg0->unk21C = 0;
                        arg0->unk222 = 0;
                    }
                }
                if (((sp4C == 0) || (sp4C == 0xA)) && (sp144 < sp13C)) {
                    temp_v0_17 = arg0->unk13F;
                    temp_v1_6 = arg0->unk21F;
                    var_a2_2 = (D_800D2528[temp_v0_17] - 1) & 0xFF;
                    if (temp_v1_6 != 0) {
                        var_a2_2 = temp_v1_6 & 0xFF;
                    }
                    temp_a1 = arg0->unk22C;
                    if (temp_a1 & 4) {
                        temp_t7 = arg0->unk21E * 8;
                        arg0->x_position = (f32) (*(s16 *)((u8 *)((D_800D2104[temp_v0_17] + temp_t7)) + 8));
                        arg0->unk1FC |= 8;
                        arg0->z_position = (f32) (*(s16 *)((u8 *)((D_800D2104[temp_v0_17] + temp_t7)) + 0xC));
                        if (temp_a1 & 8) {
                            arg0->y_position = (f32) (*(s16 *)((u8 *)((D_800D2104[temp_v0_17] + temp_t7)) + 0xA));
                        }
                    }
                    if (!(arg0->unkF4 & 0x10)) {
                        arg0->unk21C = 0;
                    }
                    temp_v1_7 = arg0->unk220;
                    temp_t5 = arg0->unk21E + arg0->unk221;
                    temp_t1 = (temp_t5 & 0xFF) + var_a2_2;
                    temp_hi = (s32) (temp_t1 & 0xFF) % var_a2_2;
                    arg0->unk21E = temp_t5;
                    arg0->unk21E = temp_t1;
                    arg0->unk21E = (u8) temp_hi;
                    if ((temp_hi & 0xFF) < (s32) temp_v1_7) {
                        arg0->unk21E = temp_v1_7;
                    }
                }
                var_a2_3 = arg0->unk78;
                if (arg0->unkF4 & 0x20000) {
                    temp_v0_18 = &D_800CC2D0[arg0->unk222];
                    var_a2_3 = func_1505A630(temp_v0_18->x_position - arg0->x_position, arg0->z_position - temp_v0_18->z_position, 0) & 0xFFFF;
                }
                sp153 = func_150599C8(arg0, sp149, var_a2_3);
                temp_t1_2 = arg0->unk248;
                var_f6_3 = (f32) temp_t1_2;
                if ((s32) temp_t1_2 < 0) {
                    var_f6_3 += 4294967296.0f;
                }
                sp154 = var_f6_3 / 10.0f;
                temp_v1_8 = arg0->unk3A;
                if ((temp_v1_8 != 0) && (arg0->unk28 == 0.0f) && !(temp_v1_8 & 3 & D_800D1968)) {
                    arg0->unk84.uh = 0xFF;
                    arg0->y_velocity = (f32) temp_v1_8;
                }
                temp_v0_19 = arg0->unkF4;
                if (temp_v0_19 & 1) {
                    sp14C = 0.0f;
                }
                if ((arg0->unk22C & 0x10) && (arg0->unk28 == 0.0f)) {
                    sp14C = 0.0f;
                    sp158 = 1.0f;
                }
                if (arg0->interaction_state == 1) {
                    arg0->unk44 = sp14C;
                    return;
                }
                if (temp_v0_19 & 0x80000) {
                    temp_f0_3 = sp16C + 70.0f;
                    var_f14 = temp_f0_3;
                    if (D_800BE9F0 == 0x26) {
                        var_f14 = temp_f0_3 - (45.0f * arg0->y_scale);
                    }
                    func_1504C9E4(arg0, (s8) ((s16) func_1505A630(sqrtf(sp3C), var_f14, 0) / 200), 0);
                } else if (arg0->unk1D1 != 0) {
                    func_1504C9E4(arg0, 0, 0);
                }
                if (arg0->unkF8 & 0x40000) {
                    sp14C = arg0->unk44;
                    func_1505A184(arg0->unk78, sp14C, 0.0f, &sp68, &sp64, &sp60);
                    if ((sp14C < 1.0f) || (var_f0 = sp158, ((((sp78 - arg0->unk78) + 0x4000) & 0x8000) != 0))) {
                        var_f0 = sp154;
                    }
                    func_1505A250(sp68, sp64, var_f0, &arg0->unk174, &arg0->unk178);
                    temp_f2_3 = arg0->unk174;
                    temp_f12_5 = arg0->unk178;
                    arg0->unk76 = func_1505A630(arg0->unk174, -arg0->unk178, 0);
                    arg0->xz_velocity = 2.0f * sqrtf((temp_f2_3 * temp_f2_3) + (temp_f12_5 * temp_f12_5));
                } else {
                    func_1505A3A8(sp14C, arg0, sp158, sp154, (u8) (s32) sp153);
                }
                goto block_251;
            }
            sp3C = temp_f12_4;
            func_150599C8(arg0, arg0->unk1E6, arg0->unk78);
            arg0->unk76 = arg0->unk78;
            arg0->xz_velocity = sp14C;
block_251:
            func_1505841C(arg0, sp158);
            if ((arg0->unk22C & 8) && !(arg0->unk1FC & 8)) {
                temp_f2_4 = (f32) func_1505A630(sqrtf(sp3C), sp16C, 0) * 0.005493164f;
                var_f0_2 = temp_f2_4;
                if (temp_f2_4 > 180.0f) {
                    var_f0_2 = temp_f2_4 - 360.0f;
                }
                temp_f12_6 = arg0->unkB8;
                var_f0_3 = (var_f0_2 - temp_f12_6) * 0.25f;
                var_f8_3 = (f32) sp14A;
                if ((s32) sp14A < 0) {
                    var_f8_3 += 4294967296.0f;
                }
                temp_f2_5 = var_f8_3 * 0.005493164f;
                temp_f14_3 = -temp_f2_5;
                if (temp_f2_5 < var_f0_3) {
                    var_f0_3 = temp_f2_5;
                }
                if (var_f0_3 < temp_f14_3) {
                    var_f0_3 = temp_f14_3;
                }
                arg0->unkB8 = temp_f12_6 + var_f0_3;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056B08.s")
#endif
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

#ifdef NON_MATCHING
extern f32 D_800CC630;
extern f32 D_800CC634;
extern f32 D_800CC638;
extern s32 D_800D1968;

void func_15059C84(struct127 *rec) {
    u8 *arg0 = (u8 *) rec;
    f32 tri[9];
    s32 i;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    u16 sp76;
    s32 sp74;
    s32 sp50;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f12;
    s16 var_t5;
    u16 temp_t5;
    u8 temp_v0;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v1;
    u8 *var_v0;
    u8 *var_v1;

    var_f12 = (*(f32 *)((u8 *)arg0 + 0x3C));
    sp76 = (*(u16 *)((u8 *)arg0 + 0x76));
    if (D_800D1968 != 1) {
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x1FC));
        if (temp_v0 & 8) {
            (*(u8 *)((u8 *)arg0 + 0x1FC)) = (u8) (temp_v0 & 0xFFF7);
            return;
        }
        if ((*(u8 *)((u8 *)arg0 + 0x127)) != 0xFF) {
            temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x31C));
            if ((*(s16 *)((u8 *)temp_v0_2 + 0x46)) > 0) {
                temp_t5 = sp76 + (*(u16 *)((u8 *)temp_v0_2 + 0x10));
                sp76 = temp_t5;
                (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t5;
            }
        }
        if (((*(f32 *)((u8 *)arg0 + 0x3C)) < 1.0f) && ((*(f32 *)((u8 *)arg0 + 0x3C)) >= 0.0f) && !((*(u8 *)((u8 *)arg0 + 0x1FC)) & 1)) {
            temp_v0_3 = (*(u8 *)((u8 *)arg0 + 0x7E));
            if ((s32) temp_v0_3 < 0xFA) {
                (*(u8 *)((u8 *)arg0 + 0x7E)) = (u8) (temp_v0_3 + 1);
            }
            if (((*(f32 *)((u8 *)arg0 + 0x164)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x168)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x16C)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x170)) == 0.0f)) {
                (*(f32 *)((u8 *)arg0 + 0x1F4)) = 0.0f;
                return;
            }
            goto block_17;
        }
        (*(u8 *)((u8 *)arg0 + 0x7E)) = 0U;
block_17:
        if ((((*(u8 *)((u8 *)arg0 + 0xAD)) != 0) && ((temp_v0_4 = (*(u8 **)((u8 *)arg0 + 0x31C)), (temp_v0_4 == NULL)) || ((*(u8 *)((u8 *)temp_v0_4 + 0x21)) == 0))) || ((*(u16 *)((u8 *)arg0 + 0x22C)) & 8)) {
            sp84 = (*(f32 *)((u8 *)arg0 + 0xB8));
            if (sp84 > 90.0f) {
                sp84 = 90.0f;
            } else if (sp84 < -90.0f) {
                sp84 = -90.0f;
            }
        } else {
            sp84 = 0.0f;
        }
        temp_v0_5 = (*(u8 *)((u8 *)arg0 + 0x1FC));
        if (temp_v0_5 & 1) {
            (*(u8 *)((u8 *)arg0 + 0x1FC)) = (u8) (temp_v0_5 & 0xFFFE);
            if (*D_800D1550 != 0.0f) {
                var_f12 = 2.0f * (((*(f32 *)((u8 *)arg0 + 0x1F4)) * (*(f32 *)((u8 *)arg0 + 0x14C))) / *D_800D1550);
            }
            (*(f32 *)((u8 *)arg0 + 0x1F4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
            sp76 = (*(u16 *)((u8 *)arg0 + 0x7A));
        }
        (*(f32 *)((u8 *)arg0 + 0x1F4)) = var_f12;
        func_1505A184(sp76, var_f12, sp84, &sp84, &sp80, &sp7C);
        sp84 += (*(f32 *)((u8 *)arg0 + 0x164)) + (*(f32 *)((u8 *)arg0 + 0x16C));
        sp80 += (*(f32 *)((u8 *)arg0 + 0x168)) + (*(f32 *)((u8 *)arg0 + 0x170));
        if ((*(u8 *)((u8 *)arg0 + 0xAD)) == 0xA) {
            sp7C = 0.0f;
        }
        if ((((*(s32 *)((u8 *)arg0 + 0)) != 1) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x4F)) == 0)) && ((*(f32 *)((u8 *)arg0 + 0x28)) <= 0.0f) && ((*(u8 *)((u8 *)arg0 + 0xAD)) == 0)) {
            if (!((*(u16 *)((u8 *)arg0 + 0x22C)) & 8)) {
                for (i = 0; i < 9; i++) {
                    tri[i] = (f32) (*(s16 *)((u8 *)arg0 + 0x18C + i * 2));
                }
                /* P77: the nine floats as arguments (the asm passes them in a0..a3 and the stack; the old call
                 * passed one 36-byte struct, a single argument in the port) */
                func_15049350(*(s32 *)&tri[0], tri[1], tri[2], tri[3], tri[4], tri[5], tri[6], tri[7], tri[8]);
                if ((D_800CC634 != 0.0f) && ((temp_f12 = ((-D_800CC630 * sp84) - (D_800CC638 * sp80)) / D_800CC634, (temp_f12 > 4.0f)) || ((*(s32 *)((u8 *)arg0 + 0)) != 1) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x4E)) != 2))) {
                    temp_f14 = (sp84 * sp84) + (sp80 * sp80);
                    temp_f2 = sqrtf(temp_f14 + (temp_f12 * temp_f12));
                    if (temp_f2 != 0.0f) {
                        temp_f0 = sqrtf(temp_f14);
                        sp84 = (sp84 * temp_f0) / temp_f2;
                        sp7C = (temp_f12 * temp_f0) / temp_f2;
                        sp80 = (sp80 * temp_f0) / temp_f2;
                    }
                }
            }
        }
        temp_f8 = sp84 * *D_800D1550;
        temp_f6 = sp80 * *D_800D1550;
        temp_f10 = sp7C * *D_800D1550;
        sp84 = temp_f8;
        sp80 = temp_f6;
        sp7C = temp_f10;
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + temp_f8);
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x1C)) + temp_f6);
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + temp_f10);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059C84.s")
#endif
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

#ifdef NON_MATCHING
/* P50: gravity. Airborne (+0x28 height != 0 or rising): D_800D1550 / 0.1 steps of vy -= g * 0.1, y += vy * 0.05
 * (IDO unrolled this loop by 4); on the ground: one step of the whole frame. vy is clamped at -500. */
void func_1505A770(struct127 *rec) {
    u8 *arg0 = (u8 *) rec;
    f32 g;
    s32 n;
    s32 i;
    f32 v;

    if (((*(f32 *)(arg0 + 0x28)) != 0.0f) || ((*(f32 *)(arg0 + 0x20)) > 0.0f)) {
        g = (*(f32 *)(arg0 + 0x24)) * 0.1f;
        n = (s32) (*D_800D1550 / 0.1f);
        for (i = 0; i < n; i++) {
            *(f32 *)(arg0 + 0x20) = *(f32 *)(arg0 + 0x20) - g;
            *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (*(f32 *)(arg0 + 0x20) * 0.05f);
        }
        if ((*(f32 *)(arg0 + 0x20)) < -500.0f) {
            *(f32 *)(arg0 + 0x20) = -500.0f;
        }
    } else {
        *(f32 *)(arg0 + 0x20) = *(f32 *)(arg0 + 0x20) - ((*(f32 *)(arg0 + 0x24)) * *D_800D1550);
        v = *(f32 *)(arg0 + 0x20);
        *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (v * *D_800D1550 * 0.5f);
        if (v < -500.0f) {
            *(f32 *)(arg0 + 0x20) = -500.0f;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A770.s")
#endif
// a big one, but could be ok
#ifdef NON_MATCHING
void func_15055C88(struct127 *);
s32 func_1507CD64(struct127 *, s32);
void func_1513783C(struct127 *, s32, s32);
extern u8 D_800CC69C;

void func_1505A9AC(struct127 *arg0, f32 arg1) {
    u8 sp6F;
    u8 sp6E;
    u8 sp63;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    f32 sp50;
    s32 sp4C;
    u8 sp4B;
    s32 sp3C;
    s32 *temp_v0_4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f2;
    f32 var_f2_2;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 var_a3;
    s32 var_t0;
    s32 var_t0_3;
    s32 var_t1;
    s32 var_t2;
    s32 var_v1;
    struct126 *temp_v0;
    struct126 *temp_v0_5;
    u16 temp_v0_8;
    u8 temp_a0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_6;
    u8 temp_v0_7;
    u8 temp_v0_9;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 var_t0_2;

    sp6F = 0;
    sp6E = 1;
    var_f2 = arg0->y_position - arg1;
    if (arg0->unk31C->pad4F[0] != 0) {
        if (var_f2 < 0.0f) {
            arg0->unk1CC = arg1;
            var_f2 = 0.0f;
        }
        arg0->unk28 = var_f2;
        temp_f2 = arg0->y_position - (arg0->unk118 - 34.0f);
        if (temp_f2 < 70.0f) {
            temp_f0 = arg0->y_velocity;
            if (temp_f0 < 18.0f) {
                if (temp_f0 > -25.0f) {
                    arg0->unk31C->pad4F[0] = 2;
                }
                if (temp_f2 < 0.0f) {
                    if (arg0->y_velocity < -12.0f) {
                        arg0->unk81 = 0;
                        if (arg0->y_velocity < -25.0f) {
                            arg0->y_velocity = -30.0f;
                            arg0->xz_velocity *= 0.4f;
                        }
                        arg0->y_velocity *= 0.85f;
                    }
                    arg0->gravity = -1.9f;
                    return;
                }
                if ((arg0->y_velocity > 10.0f) && (arg0->y_velocity < 25.0f)) {
                    arg0->y_velocity = 10.0f;
                }
                arg0->gravity = 2.2f;
            }
        }
    } else {
        if (arg0->unk65 != 0) {
            if (var_f2 < 0.0f) {
                arg0->unk1CC = arg1;
                var_f2 = 0.0f;
                arg0->y_position = arg1;
            }
            goto block_172;
        }
        if (var_f2 < 0.0f) {
            sp63 = 0;
            if (arg0->in_water == 0) {
                arg0->unk137 = 0;
                arg0->gravity = 5.0f;
            }
            if (arg0->in_water == 0) {
                arg0->unk31C->unk55 = 4;
            }
            if (arg0->unk28 > 0.0f) {
                arg0->unk31C->pad4F[2] = 1;
                arg0->unk31C->unk31 = 0;
            }
            arg0->unk100 &= 0xFD;
            if ((((u32) arg0->unk184 >> 0xC) & 0xF) == 1) {
                if (D_800BE9F0 == 0x14) {
                    func_1513783C(arg0, 0xFF, 1);
                    func_1507CD64(arg0, 8);
                    return;
                }
                func_15055C88(arg0);
                return;
            }
            if (D_800BE9F0 == 0x43) {
                var_f2_2 = 1000.0f;
            } else {
                var_f2_2 = 600.0f * 3.0f;
            }
            if ((arg0->unk1CC - arg0->y_position) > 600.0f) {
                temp_v0 = arg0->unk31C;
                if ((temp_v0->unk120 == 0) && (temp_v0->unk78 != 1)) {
                    var_f12 = 1.3f;
                    temp_v0->unk95 = 0;
                    var_t2 = 0;
                    arg0->unk31C->pad4F[2] = 2;
                    var_t1 = 0;
                    var_a3 = 0;
                    var_t0 = 0x30;
                    if (D_800BE9F0 != 0x29) {
                        temp_v1 = arg0->unk184;
                        if (((((u32) temp_v1 >> 0xC) & 0xF) == 2) || ((temp_v1 == 0x13) & 0x1F)) {
                            sp58 = 0xC8;
                            sp54 = 0;
                            sp5C = 0;
                            func_15060B70(0x1B8, arg0);
                            var_f12 = 1.0f;
                            var_t0 = 0xC8;
                            var_t1 = 0;
                            var_t2 = 0;
                        } else {
                            temp_v0_2 = arg0->health;
                            if (temp_v0_2 != 0) {
                                if (arg0->unk31C->unk78 == 0x21) {
                                    var_t1 = 1;
                                }
                                if (arg0->id == 0x75) {
                                    var_t1 |= 2;
                                }
                            }
                            temp_f0_2 = arg0->unk1CC;
                            if ((temp_f0_2 < 90000.0f) && (var_f2_2 < (temp_f0_2 - arg0->y_position))) {
                                if (!(var_t1 & 2)) {
                                    arg0->health = 0;
                                    if ((temp_v1 & 0x1F) != 0xE) {
                                        sp4C = 0;
                                        sp58 = 0x30;
                                        sp54 = var_t1;
                                        sp50 = 1.3f;
                                        func_1513783C(arg0, 0xFF, 1);
                                        var_a3 = 0;
                                        var_t0 = 0x30;
                                        var_f12 = 1.3f;
                                        var_t2 = 1;
                                    }
                                } else {
                                    var_a3 = 1;
                                    if (temp_v0_2 != 0) {
                                        arg0->health = temp_v0_2 - 1;
                                    }
                                }
                            }
                            if (var_t1 == 0) {
                                temp_v0_3 = arg0->health;
                                arg0->stunned = 8;
                                if (temp_v0_3 != 0) {
                                    arg0->health = temp_v0_3 - 1;
                                }
                            }
                            if (var_t1 & 1) {
                                var_f12 = 1.0f;
                                var_t0 = 0x19D;
                            } else if (var_t1 & 2) {
                                if (var_a3 != 0) {
                                    goto block_64;
                                }
                                var_t0 = 9;
                            } else if (arg0->health != 0) {
block_64:
                                var_t0 = 0x27;
                            }
                            if ((var_t0 == 0x27) && (arg0->unk31C->unk78 == 0x25)) {
                                var_t0 = 0x1AA;
                            }
                        }
                    }
                    if (var_t2 == 0) {
                        sp54 = var_t1;
                        sp5C = var_t2;
                        func_1505E650(arg0, var_t0 & 0xFFFF, var_f12, 2.0f, 6.0f, 0.0f, 0);
                    }
                    arg0->stunned = 0;
                    arg0->unk83 = 0xFF;
                    arg0->disable_run = 0xFE;
                    if (var_t1 != 0) {
                        arg0->unk228 = 0xA;
                    } else {
                        arg0->unk228 = 0x1E;
                    }
                    arg0->unk28 = 0.0f;
                    arg0->unk100 &= 0x8B;
                    arg0->unk76 = arg0->unk7A;
                    arg0->unkA9 = 0;
                    arg0->y_position = arg1;
                    arg0->y_velocity = -4.0f;
                    arg0->unk1CC = arg1;
                    if (var_t2 == 0) {
                        func_15174690((s32) D_800C3E78, 0, 0x1F, 0, 0x199, 4, 0xAA, 0xFFU, 0);
                        return;
                    }
                    func_1507CD64(arg0, 8);
                    return;
                }
            }
            arg0->unk1CC = arg1;
            if (arg0->in_water != 0) {
                arg0->unk28 = 0.0f;
                arg0->y_position = arg1;
                return;
            }
            if (arg0->stunned == 0) {
                if ((arg0->unk7F == 0) && (arg0->xz_velocity < 9.0f)) {
                    arg0->unk76 = arg0->unk7A;
                }
                temp_t5 = ((s32) (arg0->unk76 - arg0->unk7A) >> 8) & 0xFF;
                var_v1 = temp_t5;
                if (temp_t5 >= 0x81) {
                    var_v1 = -temp_t5 & 0xFF;
                }
                if ((arg0->unk7F == 0) && (var_v1 < 0x50)) {
                    arg0->unk7F = 0xA;
                }
                if (arg0->unkA9 == 2) {
                    temp_v1_2 = arg0->unk274;
                    var_t0_2 = 0;
                    if (temp_v1_2 != 0) {
                        temp_v0_4 = &(*(s32 *)((u8 *)(&D_800CC2D0[temp_v1_2]) + -0x32C));
                        temp_a0 = (*(u8 *)((u8 *)temp_v0_4 + 0x24C));
                        if (temp_a0 != 0) {
                            var_t0_2 = 1;
                            (*(s32 *)((u8 *)temp_v0_4 + 0x218)) = 0;
                            (*(u8 *)((u8 *)temp_v0_4 + 0x232)) = temp_a0;
                        }
                    }
                    arg0->xz_velocity = 0.0f;
                    arg0->unk83 = 0xFF;
                    sp63 = 0xFF;
                    sp4B = var_t0_2;
                    func_1505E650(arg0, 0x4BU, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                    if ((s32) D_800C3E78 < 4) {
                        arg0->unk31C->unk57 = 1;
                    }
                    if (var_t0_2 == 0) {
                        func_15060A9C(0x19, arg0);
                    }
                } else {
                    var_t0_3 = 0;
                    if ((s32) arg0->unk28 > 0) {
                        temp_v0_5 = arg0->unk31C;
                        temp_v1_3 = temp_v0_5->unk11A;
                        if ((temp_v1_3 != 1) && (temp_v1_3 != 3) && (temp_v0_5->unk4E == 0) && ((temp_v0_6 = arg0->unk100, temp_v1_4 = temp_v0_6 & 0x10, (temp_v1_4 != 0)) || (!(temp_v0_6 & 8) && (((arg0->unk44 == 0.0f) && (arg0->unkA8 == 0)) || (temp_v0_6 & 4))))) {
                            if (temp_v1_4 != 0) {
                                arg0->unk83 = 8;
                                if (!(temp_v0_6 & 0x40)) {
                                    arg0->xz_velocity = 0.0f;
                                    arg0->unk83 = 0xD;
                                    sp63 = 5;
                                }
                            } else if (temp_v0_6 & 4) {
                                arg0->unk83 = 0x14;
                                arg0->xz_velocity *= 0.7f;
                            } else {
                                arg0->xz_velocity = 0.0f;
                                arg0->unk83 = 0x10;
                            }
                            temp_v0_7 = arg0->unk31C->unk78;
                            if (temp_v0_7 == 0x21) {
                                var_t0_3 = 0x19D;
                            } else {
                                var_t0_3 = 0x36;
                                if (temp_v0_7 == 0x25) {
                                    var_t0_3 = 0xD8;
                                }
                            }
                        }
                    }
                    temp_v0_8 = arg0->unk84.uh;
                    if ((temp_v0_8 == 0x3B) || (temp_v0_8 == 0x3C)) {
                        sp63 = 0xFE;
                        sp6E = 0;
                        temp_t3 = arg0->unk184 & 0x1F;
                        arg0->unk83 = 0xFF;
                        if ((temp_t3 == 0xA) || (temp_t3 == 0xB) || (temp_t3 == 0xC) || (temp_t3 == 0xF) || (temp_t3 == 0x13)) {
                            sp3C = 0xC8;
                            func_15060B70(0x1B8, arg0);
                        } else if ((temp_t3 == 1) || (temp_t3 == 2) || (temp_t3 == 7) || (temp_t3 == 0x11)) {
                            sp3C = 0xC8;
                            func_15060B70(0xA7, arg0);
                        } else {
                            sp3C = 0x27;
                            func_15060B70(0xA7, arg0);
                        }
                        var_t0_3 = sp3C;
                    }
                    if ((var_t0_3 != 0) && !(arg0->unk100 & 0x20)) {
                        func_1505E650(arg0, var_t0_3 & 0xFFFF, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                    }
                    if (!(arg0->unk100 & 0x80)) {
                        arg0->unk100 = 1;
                    }
                    if (sp6E == 0) {
                        arg0->unk100 = 0x90;
                    }
                }
                if ((arg0->unk28 > 0.0f) && !(arg0->unk100 & 8)) {
                    if (D_800CC69C != 0) {
                        if (arg0->xz_velocity > 20.0f) {
                            arg0->xz_velocity = 20.0f;
                        }
                    } else if (arg0->unk110 == 0) {
                        arg0->unk164 = 0.0f;
                        arg0->unk168 = 0.0f;
                    }
                    arg0->disable_run = sp63;
                    if ((arg0->unk31C->unk4E == 1) && (arg0->y_velocity < -10.0f)) {
                        sp6F = 2;
                    }
                }
                arg0->unkA9 = 0;
            }
            if (!(arg0->unk100 & 8)) {
                var_f2 = 0.0f;
            } else {
                var_f2 = 0.1f;
            }
            arg0->y_position = arg1;
            if ((arg0->stunned == 0) && !(sp6F & 2)) {
                arg0->y_velocity = -4.0f;
            } else {
                if (arg0->unkF4 & 0x80) {
                    arg0->y_velocity = -20.0f;
                } else {
                    temp_f0_3 = arg0->y_velocity;
                    if (temp_f0_3 > -10.0f) {
                        arg0->y_velocity = 0.0f;
                    } else {
                        arg0->y_velocity = temp_f0_3 * -0.5f;
                        if (arg0->y_velocity > 28.0f) {
                            arg0->y_velocity = 28.0f;
                        }
                    }
                }
                if (arg0->unk109 != 0) {
                    arg0->xz_velocity *= 0.6f;
                }
            }
            temp_v0_9 = arg0->unk7F;
            arg0->unk81 = 0;
            if ((s32) temp_v0_9 < 0xFA) {
                arg0->unk7F = temp_v0_9 + 1;
            }
            arg0->unk100 &= 0x9F;
            goto block_168;
        }
        if ((var_f2 < 1.0f) && (arg0->unk28 > 0.0f)) {
            var_f2 = 1.0f;
        }
block_168:
        if (var_f2 > 20.0f) {
            arg0->unk7F = 0;
        }
        if (arg0->in_water != 0) {
            arg0->unk1CC = arg0->y_position;
        }
block_172:
        arg0->unk28 = var_f2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A9AC.s")
#endif
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
#ifdef NON_MATCHING
extern f32 D_800998E4; /* pi / 180 */
extern struct127 D_800B30F0[];
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
f32 func_15143E64(f32 *vec);

/* P67: one attack descriptor (0x28 bytes) of the table func_1505C1A4 returns; rec->unkD0 - 1 is the active one. */
typedef struct {
    /* 0x00 */ u8  pad0[9];
    /* 0x09 */ u8  angle;   /* sphere: high byte of the angle offset from the facing; box: half length / 5 */
    /* 0x0A */ u8  dist;    /* sphere: distance in front (/ 0.125 scale); box: half width / 5 */
    /* 0x0B */ u8  padB;
    /* 0x0C */ s16 height;  /* height of the hit point (/ 0.25 scale) */
    /* 0x0E */ u8  radius;  /* sphere: radius / 4 (scale); box: s8 forward offset / 5 */
    /* 0x0F */ u8  padF[0x15];
    /* 0x24 */ u16 flags;   /* 0x80 box, 0x1000 may hit unk124, 0x2000 line of sight, 4 keep unk21C, 0x800 keep */
    /* 0x26 */ u8  pad26[2];
} AttackBox;

/* P67: attack hit test. Tests the active attack (sphere in front of the attacker, or a box in its frame) against
 * every live, vulnerable record except `skip`, optionally checks the line of sight (ray cast from the eyes), and
 * calls func_1505C1E4 for each hit. Returns func_1505C1E4's last result (0 = no hit). */
s32 func_1505C7D8(struct127 *self, s32 skip) {
    AttackBox *boxes;
    AttackBox *box;
    struct127 *target;
    s32 cur;
    s32 i;
    s32 count;
    s32 hits = 0;
    f32 hitX = 0.0f; /* the asm leaves these unset in box mode (reads its stack slot) */
    f32 hitY;
    f32 hitZ = 0.0f;
    f32 radius = 0.0f;
    f32 dx, dy, dz, ofs;
    f32 dist, limit;

    if (self->unk114 < 254.0f) {
        self->unk114 -= D_800D1550[0];
    }
    if (self->unk114 < 0.0f) {
        self->unkD0 = 0;
        return 0;
    }
    if (D_800C35EA == 1) {
        return 0;
    }
    skip = (skip & 0x7F) + 1;
    cur = self->unkD0 - 1;
    boxes = (AttackBox *)func_1505C1A4(self);
    box = &boxes[cur];

    /* the hit point: sphere centre in front of the attacker */
    if (box->flags & 0x80) {
        hitY = self->y_position;
    } else {
        func_1505A184(((box->angle << 8) + self->unk7A) & 0xFFFF, box->dist * (self->xz_scale / 0.125f), 0.0f,
                      &hitX, &hitZ, &hitY);
        hitX += self->x_position;
        hitY += self->y_position;
        hitZ += self->z_position;
        radius = box->radius;
        radius *= self->xz_scale * 4.0f;
    }
    hitY += box->height * (self->y_scale / 0.25f);

    count = (self->unkF8 & 0x100) ? 4 : 26;
    for (i = 1; i < count; i++) {
        target = &D_800CC2D0[i - 1];
        if (target->interaction_state == 0 || i == skip || target->health == 0 || target->immune != 0) {
            continue;
        }
        box = &boxes[cur];
        if (i == self->unk124 && !(box->flags & 0x1000)) {
            continue;
        }
        if (box->flags & 0x80) {
            /* box: target position in the attacker's frame (forward / side / up) */
            f32 angle, s, c, fwd, side, halfY, halfF, halfS;

            dx = target->x_position - self->x_position;
            dz = target->z_position - self->z_position;
            if (target->unkD8 != 0 || target->unkDA != 0) {
                dx += func_1505D34C(target->unk40, target->unkDA, target->unkD8, 1.0f, &ofs);
                dz += ofs;
            }
            angle = -((self->unk40 - 90.0f) * D_800998E4);
            s = func_150AD780(angle);
            c = func_150AD78C(angle);
            fwd = (dx * s + dz * c) - (s16)((s8)box->radius * 5) * self->xz_scale;
            side = -dx * c + dz * s;
            dy = hitY - (target->y_position + target->unkD6);
            halfY = target->unkD4 + 25.0f;
            halfF = box->angle * 5 * self->xz_scale + target->unkD2;
            halfS = box->dist * 5 * self->xz_scale + target->unkD2;
            if (!(-halfY < dy && dy < halfY && -halfF < fwd && fwd < halfF && -halfS < side && side < halfS)) {
                continue;
            }
        } else {
            /* sphere against the target's ellipsoid (radius unkD2, half height unkD4) */
            f32 r, h, k;

            dx = hitX - target->x_position;
            dz = hitZ - target->z_position;
            if (target->unkD8 != 0 || target->unkDA != 0) {
                dx -= func_1505D34C(target->unk40, target->unkDA, target->unkD8, 1.0f, &ofs);
                dz -= ofs;
            }
            dy = hitY - (target->y_position + target->unkD6);
            h = target->unkD4;
            r = target->unkD2;
            if (h == 0.0f) {
                continue;
            }
            limit = (r + radius) * (r + radius);
            k = h / (radius + h);
            dy *= (r / h) * k + (1.0f - k);
            dist = dx * dx + dy * dy + dz * dz;
            if (!(dist < limit)) {
                continue;
            }
        }

        if ((box->flags & 0x2000) && i != self->unk13D) {
            /* line of sight: ray from the attacker's eyes to the target's middle */
            f32 eye[3];
            f32 ray[3];
            f32 hx, hy, hz, t;
            f32 aim;
            s16 eyeH;

            if (self->unk2F4 != NULL) {
                eye[0] = ((f32 *)self->unk2F4)[0];
                eye[1] = ((f32 *)self->unk2F4)[1];
                eye[2] = ((f32 *)self->unk2F4)[2];
            } else {
                func_1507C7C0(self, &eyeH, NULL, NULL);
                eye[0] = self->x_position;
                eye[1] = self->y_position + (eyeH >> 1);
                eye[2] = self->z_position;
            }
            if (target->unk31C != NULL) {
                aim = (s16)target->unk31C->unk114 * 0.5f;
            } else {
                aim = 20.0f;
            }
            ray[0] = target->x_position - eye[0];
            ray[1] = (aim + target->y_position) - eye[1];
            ray[2] = target->z_position - eye[2];
            if (func_150ACEA0(eye[0], eye[1], eye[2], ray[0], ray[1], ray[2], 0, 0, &hx, &hy, &hz, &t, 0, 0, 0.0f) != 0
                && t < func_15143E64(ray)) {
                continue; /* blocked */
            }
        }

        D_800CC2C0 = hitX;
        D_800CC2C4 = hitY;
        D_800CC2C8 = hitZ;
        hits = func_1505C1E4(self, target, boxes, cur, i, hits, 15);
        cur = self->unkD0 - 1;
    }

    if (hits != 0) {
        box = &boxes[cur];
        if (D_800B30F0[self->unk108].interaction_state == 1 && self->unk254 != 0) {
            self->unk232 = self->unk254;
            self->unk218 = NULL;
        }
        if (!(box->flags & 4)) {
            self->unk21C = 0;
        }
        if (!(box->flags & 0x800)) {
            self->unkD0 = 0;
        }
    }
    return hits;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")
#endif
#ifdef NON_MATCHING
struct252 *func_1505C1A4(struct127 *arg0);
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
u8 func_1505B9C4(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
extern s16 D_800D16B6; /* the asm's name for this halfword (D_800D1296 in the US list) */

// object_send_hit: sends a hit / message of kind `flags & 0xFF` to the object `obj` from the current object.
/* Nothing (returns 0) while D_800C35EA is 1, or when the object is immune (flag 0x20000), stunned (0x40000) or has
 * no health (unless flag 0x100000). Sets the parameter D_800D1340 (arg3 + 1, 0 for -1) and the value `val` in
 * D_800D1292 / D_800D16B6. The sender record is D_8009A9F8, or func_1505C1A4(D_800D154C) with flag 0x10000.
 * Flag 0x80000 uses func_1505C1E4 and returns its result; else func_1505B9C4 and returns the object's bit
 * (1 << its index in D_800CC2D0). */
s32 func_1505D024(struct127 *obj, s32 flags, u16 val, s32 arg3) {
    struct252 *from = &D_8009A9F8;
    s32 idx;
    s32 bit;

    if (D_800C35EA == 1) {
        return 0;
    }
    if ((flags & 0x20000) && obj->immune != 0) {
        return 0;
    }
    if ((flags & 0x40000) && obj->stunned != 0) {
        return 0;
    }
    if (!(flags & 0x100000) && obj->health == 0) {
        return 0;
    }
    if (arg3 == -1) {
        D_800D1340 = 0;
    } else {
        D_800D1340 = arg3 + 1;
    }
    D_800D1292 = val;
    D_800D16B6 = val;
    if (flags & 0x10000) {
        from = func_1505C1A4(D_800D154C);
    }
    idx = ((s32)obj - (s32)D_800CC2D0) / 0x32C;
    bit = 1 << idx;
    if (flags & 0x80000) {
        return func_1505C1E4((struct127 *)&D_800D121C, obj, from, flags & 0xFF, idx + 1, 0, 7);
    }
    func_1505B9C4((struct127 *)&D_800D121C, obj, (s32)from, (s32)from, flags & 0xFF, idx + 1, 7);
    return bit;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
#endif
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
#ifdef NON_MATCHING
f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4);
void func_1505D408(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);

/* Box test of record `rec` (at x, y, z; height `scale`, radius `radius`) against object `o` (id 0x34, called by
 * func_1505D6F0): o's box has radius r and height h (scaled by o +0x14C / +0x150), centre offset (ox, oz) turned
 * by o's heading (func_1505D34C) and height cy (scaled by +0x150). The vertical distance is scaled by
 * (scale + r / h) / 2; inside the sphere of radius radius + r: func_1505D408 (push out). */
void func_1505D5D0(struct127 *rec, struct127 *o, f32 x, f32 y, f32 z, f32 scale, f32 radius, s32 i, f32 r, f32 h,
                   f32 cy, f32 ox, f32 oz) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2;
    f32 lim;

    dx = func_1505D34C(o->unk40, ox, oz, *(f32 *)((u8 *)o + 0x14C), &oz);
    r = r * *(f32 *)((u8 *)o + 0x14C);
    h = h * *(f32 *)((u8 *)o + 0x150);
    dx = x - (o->x_position + dx);
    dz = z - (o->z_position + oz);
    dy = y - (o->y_position + cy * *(f32 *)((u8 *)o + 0x150));
    dy = dy * ((scale + r / h) * 0.5f);
    d2 = dx * dx + dy * dy + dz * dz;
    lim = radius + r;
    if (d2 < lim * lim) {
        func_1505D408(rec, o, dx, dy, dz, d2, lim, i);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D5D0.s")
#endif
#ifdef NON_MATCHING
void func_1505D408(struct127 *, struct127 *, f32, f32, f32, f32, f32, s32);
void func_1505D5D0(struct127 *, struct127 *, f32, f32, f32, f32, f32, s32, f32, f32, f32, f32, f32);
extern s8 D_800CC68C;
extern s8 D_800CC68D;

/* Record-vs-record push / contact pass for record idx (rec = &D_800CC2D0[idx]): clears the contact mask
 * D_800CC268 and the D_800CC68C / 68D flags, then tests rec's cylinder (radius unkE4, height offset unkE8, vertical
 * scale unkEC) against the other 25 records (only record 0 when rec->unkF8 has 0x02000000). Overlaps go to
 * func_1505D408; record id 0x34 gets the special box test func_1505D5D0. In multiplayer, a player close to
 * another team's player who holds the flag (+0x78 in the controller) sets its own chase timer (+0x4A = 20). */
void func_1505D6F0(struct127 *rec, s32 idx) {
    struct127 *o;
    u8 *ctl;
    s32 i;
    s32 count;
    f32 radius, scale, x, y, z;
    f32 dx, dy, dz, d2, reach;
    s16 oradius;

    D_800CC268 = 0;
    D_800CC68C = 0;
    D_800CC68D = 0;
    count = 25;
    if (rec->interaction_state == 1) {
        ctl = (u8 *)D_800CC2D0[idx].unk31C;
        if (ctl[0x4E] != 0 || ctl[0x27] != 0) {
            return;
        }
    }
    if (rec->unk13D >= 100 || rec->unkE4 == 0 || rec->unk65 != 0) {
        return;
    }
    if ((rec->unkF8 & 0x01000000) || (rec->unkF8 & 0x4000)) {
        return;
    }
    scale = rec->unkEC;
    x = rec->x_position;
    z = rec->z_position;
    radius = rec->unkE4;
    y = rec->y_position + (s16)rec->unkE8;
    if (rec->unkF8 & 0x02000000) {
        count = 1;
    }
    for (i = 0, o = D_800CC2D0; i < count; i++, o++) {
        if (o->interaction_state == 0) {
            continue;
        }
        oradius = o->unkE4;
        if (oradius < 2) {
            continue;
        }
        if ((o->unkF8 & 0x02000000) && rec->unk127 == 0xFF) {
            continue;
        }
        if ((o->unkF8 & 0x01000000) || i == idx || o->unk65 == idx + 1 || o->unk13D >= 100 || o->unk2FA == 0) {
            continue;
        }
        dx = x - o->x_position;
        dz = z - o->z_position;
        dy = (y - (o->y_position + (s16)o->unkE8)) * ((scale + o->unkEC) * 0.5f);
        if (D_800BE616 != 0 && dx * dx + dy * dy + dz * dz < 30000.0f && rec->interaction_state == 1 &&
            o->interaction_state == 1 && o->unk128 != rec->unk128) {
            ctl = (u8 *)rec->unk31C;
            if (ctl[0x78] == 0 && ((u8 *)o->unk31C)[0x78] != 0) {
                ctl[0x4A] = 20;
            }
        }
        reach = radius + oradius;
        d2 = dx * dx + dy * dy + dz * dz;
        if (d2 < reach * reach) {
            func_1505D408(rec, o, dx, dy, dz, d2, reach, i);
        }
        if (o->id == 0x34) {
            if (o->unk251 == 2) {
                func_1505D5D0(rec, o, x, y, z, scale, radius, i, 120.0f, 250.0f, 120.0f, -130.0f, 0.0f);
            } else {
                func_1505D5D0(rec, o, x, y, z, scale, radius, i, 130.0f, 140.0f, 250.0f, -50.0f, 0.0f);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D6F0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DADC.s")
#ifdef NON_MATCHING
f32 func_1505DF10(u8 *arg0, u8 arg1, u16 *arg2, f32 *arg3, f32 *arg4);

/* First player 0..D_80082FA0 (live object in D_800CC2D0) that `rec` sees: closer than rec +0x3C * scale / 2
 * (func_1505DF10 gives the squared distance and the direction) and within the cone of width `cone` around rec's
 * heading +0x76 ((u16)(heading - dir + cone / 2) < cone). Returns the player number, -1 for none. (The asm also
 * stores a 6th argument 0 for func_1505DF10, which its definition does not take; `unused` is not read.) */
s32 func_1505DDA8(struct127 *rec, s32 unused, u16 cone, f32 scale) {
    s32 i;
    f32 r;
    f32 d;
    u16 dir;
    f32 dy;
    f32 h;

    for (i = 0; i <= D_80082FA0; i = (u8)(i + 1)) {
        if (D_800CC2D0[i].interaction_state == 0) {
            continue;
        }
        r = rec->xz_velocity * scale * 0.5f;
        d = func_1505DF10((u8 *)rec, i, &dir, &dy, &h);
        if (d < r * r && (u16)(*(u16 *)((u8 *)rec + 0x76) - dir + cone / 2) < cone) {
            return (s8)i;
        }
    }
    return -1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
#endif
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
#ifdef NON_MATCHING
s32 *func_1502AF04(s32, u8 *, s32, s32);
s32 func_1502B110(u8 *, s32, s32, u32, ...);
extern s32 D_800866AC[];
extern u16 D_800997B8[];

/* P60: start / restart animation `id` on the animation state `anim` (struct_eu_anim) of object `obj` (may be NULL;
 * func_1503F8A8 passes NULL / NULL). entry: the object's animation table entry (u16 file id, u16 callback index,
 * s32 value for obj +0x1C4), NULL = file id 2 * id.
 * The animation restarts when `restart` is set (no blend then), the id differs from anim +4 (low 15 bits) or, with
 * an object, from obj +0x84 (or that is 0xFFFF, or obj +0x103 is set). Else only the speed and the hold flag change
 * (and the frame, when D_800C35EA == 1 and the animation holds).
 * Restart: the previous animation is kept for blending (anim +6..+0x2C and the 0x1D0 block copied to +0x210) unless
 * the blend countdown +0x3C is >= 600; the countdown restarts at 0x3FF (blend >= 1: step +0x3A = 500 / blend; a
 * blend into the same animation reverses the countdown); the animation header (file `entry[0]`, 2 words: data
 * address / size, +0x28 = the next word) is looked up with func_1502AF04 (object model +0x58) or func_1502B110,
 * then DMAed to anim +0x40 (no header: func_1505DFDC). +0x18 = last frame (header byte 3; 0xFF: per type).
 * With an object, its contact / flag state is reset and func_150627D4(obj) runs. */
s32 func_1505E0C4(struct127 *obj, s32 entry_addr, u8 *anim_addr, s32 unused, s32 restart, s32 id, s32 set,
                  f32 speed, f32 blend, f32 frame, f32 loop_start, s32 hold) {
    struct_eu_anim *anim = (struct_eu_anim *) anim_addr;
    u16 *entry = (u16 *) entry_addr;
    s32 start = 0;
    s32 kind;
    s32 index;
    s32 file;
    s32 *hdr;
    s32 data = 0;
    s32 size = 0;
    s16 count;
    s32 size16;
    u32 flags;
    u8 buf[0x38];

    if (restart != 0) {
        start = 1;
        blend = 0.0f;
    } else if (id != (anim->unk4 & 0x7FFF)) {
        start = 1;
    } else if (obj != NULL && (id != obj->unk84.uh || obj->unk84.uh == 0xFFFF || obj->unk103 != 0)) {
        start = 1;
    }

    if (start == 0) {
        if (obj != NULL) {
            obj->animation_speed = speed;
        }
        anim->unk10 = speed;
        if (hold != 0) {
            anim->unk4 |= 0x8000;
        } else {
            anim->unk4 &= 0x7FFF;
        }
        if (D_800C35EA == 1 && (anim->unk4 & 0x8000)) {
            anim->unk8 = frame;
        }
    } else {
        kind = 10;
        if (obj != NULL) {
            index = (s32) ((u8 *) obj - (u8 *) D_800CC2D0) / (s32) sizeof(struct127);
            set = obj->unk6;
            kind = 2;
        }
        file = (entry != NULL) ? entry[0] : id * 2;
        if (obj != NULL) {
            obj->unk84.uh = id;
            obj->animation_speed = speed;
            obj->unk138 = 0;
            obj->unk103 = 0;
            obj->unkB4 = 0.0f;
            obj->unk1C4 = *(s32 *) (entry + 2);
            if (index < D_8008FD8C) {
                D_800CC2D0[index].unk31C->unk58 = 0;
                D_800CC2D0[index].unk31C->unk5A = 0;
                D_800CC2D0[index].unk31C->unk59 = 0;
            }
        }
        if (anim->unk28 != 0) {
            count = anim->unk3C;
            if (1.0f <= blend) {
                anim->unk3A = 500 / (s16) (s32) blend;
                if (anim->unk3C > 0 && id == (anim->unk6 & 0x7FFF)) {
                    anim->unk3C = 0x3FF - anim->unk3C;
                    count = 0;
                } else if (count < 600) {
                    anim->unk3C = 0x3FF;
                }
            } else {
                anim->unk3C = 0;
            }
            if (count < 600) {
                anim->unk6 = anim->unk4;
                anim->unkC = anim->unk8;
                anim->unk14 = anim->unk10;
                anim->unk24 = anim->unk20;
                anim->unk1C = anim->unk18;
                anim->unk39 = anim->unk38;
                anim->unk2C = anim->unk28;
                bcopy(anim->unk40, anim->unk210, 0x1D0);
            }
        }
        anim->unk4 = id;
        if (hold != 0) {
            anim->unk4 = id | 0x8000;
        }
        anim->unk8 = frame;
        anim->unk10 = speed;
        anim->unk20 = loop_start;
        anim->unk0 = (entry != NULL) ? D_800866AC[entry[1]] : 0;

        if (obj != NULL && obj->unk58 != 0) {
            hdr = func_1502AF04(obj->unk58, buf, file, 2);
        } else {
            hdr = (s32 *) func_1502B110(NULL, 2, (s32) buf, 3, kind, set, file);
        }
        /* asm: with no header, data / size are stack leftovers; 0 here (= no animation) */
        if (hdr != NULL) {
            anim->unk28 = hdr[2];
            size = hdr[1];
            data = hdr[0];
        }
        if (size == 0) {
            func_1505DFDC(obj);
            return 0;
        }
        size16 = (size + 15) & ~15;
        if (size16 < 200) {
            func_1000480C(data, anim->unk40, size16);
        } else {
            func_10004514(data, anim->unk40, size16, 1);
        }

        anim->unk18 = anim->unk40[3];
        if (anim->unk40[3] == 0xFF && obj != NULL) {
            switch (obj->id) {
                case 0x92:
                    anim->unk18 = D_800997B8[obj->unk84.uh];
                    break;
                case 0xB7:
                case 0xB8:
                case 0xB9:
                    anim->unk18 = 641.0f;
                    break;
            }
        }
        if (obj != NULL) {
            obj->unk24E = 0;
            obj->unk1FC = (obj->unk1FC | 2) & ~1;
            flags = (obj->stunned == 0) ? 0x30B : 0x303;
            obj->unkF4 &= ~flags;
            if (obj->unkF4 & 0x20) {
                obj->unkF4 |= 2;
                obj->unkF4 &= ~0x20;
            }
            obj->unk1FD = (anim->unk40[7] & 0x20) ? anim->unk40[0xB] : 0;
        }
        if (anim->unk40[5] == 0) {
            anim->unk28 = 1;
        }
    }
    if (obj != NULL && start != 0) {
        func_150627D4(obj);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
#endif
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
#ifdef NON_MATCHING
void func_1506045C(struct127 *, s32, s32, f32, s32); /* P102: arg3 = height, f32 */
s32 func_1506E46C(struct127 *, s32 *, s32);
void func_151AE814(u8 *);
void func_151C7450(u8 *, u8, s32);
void func_15060A30(s32, struct127 *);
void func_15052408(struct127 *);
void func_1506160C(struct127 *, u8, u8, u8, u8);
void func_1506AF74(void);
void func_100109D0(struct127 *);
extern s32 D_800CC3C8;
extern u8 D_800CC69C;
extern char D_800997E8[];
s32 func_1000EFB4(struct_eu_sfx *, s32, s32 *, struct11 *, s32, s32 *, u16 *);


/* P64: the jump / swim / glide handler of a walking record, once per walk-handler call (func_1505A9AC family).
 * `pad` = the controller: +0 buttons (0x8000 = A / jump, 0x4000 = B, 0x2000 = Z, 0x10), +3 stick y (s8).
 * D_800CC288 = the buttons pressed this frame. ctl = rec->unk31C. Sections:
 *   1. guards: stunned / dead stop the record (target speed 0); nothing while ctl +0x46 > 0, ctl +0x36 >= 100 or
 *      ctl +0x6B. `height` = rec +0x28 (ground clearance), -150 with ctl +0x4E == 2 (carried state), 0 with
 *      ctl +0x4F == 2, +50 while rising.
 *   2. in water (rec +0xAD, not ctl +0x95, anim != 0x262): surface jump-out (A near the surface), B / swim
 *      strokes, treading water; animation and func_1506045C (in-water move); returns.
 *   3. rec +0x137 == 1 (hanging): stick up climbs (0xEA), stick down drops (0x38), A / ctl +0x84 lets go (0x40);
 *      returns when an animation was started.
 *   4. jump start: riding a record of id 0x28 (not level 0x23) / 0x8A / 0x23 (rec +0x65), or on the ground / ctl
 *      +0x55: A starts a jump (0x32, the run jump 0x37 / 0x19E, the high jump 0x279 with ctl +0x17, the item jump
 *      0x43 with ctl +8, the super jump with ctl +0x1A, the Z long jump 0xEB) with floor-kind and D_800CC69C
 *      (low gravity) adjustments; a ride is left (func_15052F58) with a push-off speed.
 *   5. func_1506045C (air move), then the double jump (ctl +0x98 / +0x95: 0x37 again), the high-fall 0x3B, and
 *      the helicopter glide (ctl +0x31: start 0xE9 with the sound 0x61E, then the spin-down counter); the
 *      animation; the sound of section 4 (func_15060A30); releasing A cuts a rising jump (gravity 6.2). */
void func_1505F298(struct127 *rec, u8 *pad) {
    struct126 *ctl;
    s32 sound = 0;         /* sp88: sound id resolved by func_1506E46C */
    f32 speed = 1.0f;      /* sp84: animation speed */
    f32 jump_v;            /* sp80 */
    u8 glide = rec->unk31C->unk31;
    f32 blend = 0.0f;      /* f12 */
    f32 height;            /* f14 */
    s32 buttons;           /* sp68 */
    s32 anim;
    s32 ride;              /* id + 1 of the ridden record */
    s32 ride_jump;
    s32 jumped;
    u16 a;

    /* 1. guards */
    if (rec->stunned != 0 || rec->health == 0) {
        rec->target_speed = 0.0f;
        return;
    }
    ctl = rec->unk31C;
    if (*(s16 *)((u8 *)ctl + 0x46) > 0 || ctl->unk36 >= 100 || ctl->unk6B != 0) {
        return;
    }
    height = rec->unk28;
    if (ctl->unk4E == 2) {
        height = height - 150.0f;
    } else if (ctl->pad4F[0] == 2) {
        height = 0.0f;
    } else if (rec->y_velocity > 0.0f) {
        height += 50.0f;
    }
    if (rec->unk110 != 0) {
        buttons = *(u16 *)pad & ~0x2000;
    } else {
        buttons = *(u16 *)pad;
    }

    /* 2. in water */
    if (rec->in_water != 0 && ctl->unk95 == 0 && rec->unk84.uh != 0x262) {
        anim = 0; /* the asm reads a stack slot here when in_water != 1 (never written on that path): UNVERIFIED */
        if (rec->in_water == 1) {
            blend = 2.0f;
            anim = 0;
            if ((D_800CC288 & 0x8000) && (D_800BE9F0 != 0x29 || (s16)ctl->unk8 <= 0)
                && rec->unk118 - 60.0f - 30.0f < rec->y_position) {
                /* jump out of the water */
                func_15052408(rec);
                rec->unk31C->unk31 = 0;
                ctl = rec->unk31C;
                anim = 0x32;
                blend = 0.0f;
                if (ctl->pad79[2] != 7 && ctl->pad79[2] != 8) {
                    ctl->unk31 = 1;
                }
                ctl = rec->unk31C;
                a = ctl->unk4C;
                rec->unk78 = a;
                rec->unk7A = a;
                rec->unk76 = a;
                if (*(u16 *)((u8 *)ctl + 0x68) != 0 && (((a - *(u16 *)((u8 *)ctl + 0x68)) + 0x4000) & 0x8000)) {
                    rec->xz_velocity = 0.0f;
                    rec->disable_run = 0xFF;
                }
                rec->unkAE = 0xC;
                rec->y_velocity = 46.0f;
                rec->unk81 = 2;
                rec->unk83 = 0;
                rec->gravity = 3.3f;
            }
            rec->target_speed = 0.0f;
            if ((D_800CC288 & 0x4000) && !(*(u16 *)pad & 0x10)) {
                ctl = rec->unk31C;
                if ((s8)ctl->pad17[0xB] < 0x69) {
                    ctl->pad17[0xB] = 0xF;
                }
            }
            ctl = rec->unk31C;
            if ((rec->xz_velocity > 2.0f && ctl->pad17[0xA] != 0)
                || (ctl->pad17[0xA] == 0
                    && ((s8)ctl->pad17[0xB] > 0 || (!(*(u16 *)pad & 0x10) && (*(u16 *)pad & 0x4000))))) {
                if (anim != 0x32) {
                    /* swim stroke */
                    blend = 9.0f;
                    rec->unk83 = 0;
                    if (rec->unk118 - 60.0f < rec->y_position) {
                        speed = 1.2f;
                        anim = 0x22;
                        rec->target_speed = 15.0f;
                    } else {
                        speed = 1.2f;
                        anim = 0xCE;
                        rec->target_speed = 23.0f;
                    }
                }
            }
        }
        if (anim == 0) {
            /* treading water */
            blend = 10.0f;
            speed = 1.2f;
            anim = 0xD1;
            if (rec->unk118 - rec->y_position < 70.0f) {
                anim = 0xCC;
                speed = 0.9f;
            }
            rec->target_speed -= 0.2f;
            if (rec->target_speed < 0.0f) {
                rec->target_speed = 0.0f;
            }
        }
        ctl = rec->unk31C;
        if (rec->in_water != 0 && rec->unk13C != 0) {
            blend = 7.0f;
            anim = 0xCB;
        }
        if (ctl->unk11A != 0 || (ctl->unk78 != 0 && ctl->unk78 != 0x27)) {
            func_1506045C(rec, 0, 0, height, 1);
        }
        if (anim != 0) {
            func_1505E650(rec, anim, speed, blend, 0.0f, 0.0f, 0);
        }
        return;
    }

    /* 3. hanging */
    if (rec->unk137 == 1) {
        anim = 0;
        if (ctl->pad53 == 0) {
            if ((s8)pad[3] > 0x32) {
                speed = 2.2f;
                ctl->unk54 = 0xC;
                anim = 0xEA;
                rec->unk137 = 0;
                rec->disable_run = 0x10;
                rec->unk81 = 1;
                rec->gravity = 5.0f;
                rec->y_velocity = 48.0f;
            } else if ((s8)pad[3] < -0x32) {
                anim = 0x38;
                rec->unk137 = 0;
                rec->gravity = 3.5f;
            }
        }
        if ((D_800CC288 & 0x8000) || rec->unk31C->unk84 != 0) {
            rec->unk137 = 2;
            anim = 0x40;
            speed = 3.0f;
        }
        if (anim != 0) {
            func_1505E650(rec, anim, speed, 4.0f, 0.0f, 0.0f, 0);
            return;
        }
    }

    /* 4. jump start */
    ride = 0;
    ride_jump = 0;
    anim = 0;
    if (rec->unk65 != 0) {
        u8 id = ((u8 *)&D_800CC3C8)[rec->unk65 * 0x32C]; /* = D_800CC2D0[rec->unk65 - 1].id */
        if ((id == 0x28 && D_800BE9F0 != 0x23) || id == 0x8A || id == 0x23) {
            ride = id + 1;
            ride_jump = 1;
        }
    }
    if (ride != 0 || height <= 0.0f || rec->unk31C->unk55 != 0) {
        rec->unk137 = 0;
        jumped = 0;
        jump_v = 0.0f;
        if ((D_800CC288 & 0x8000) && rec->unk31C->unk11A != 1 && rec->unk31C->unk11A != 3
            && (ride != 0 || (rec->unk13C < 100 && rec->disable_jump == 0 && rec->disable_run != 0xFF))) {
            jumped = 1;
            jump_v = 15.0f;
            rec->unk100 &= 0xFE;
            if (ride_jump != 0) {
                func_1506160C(rec, 1, 0xFF, 0, 0);
            }
            ctl = rec->unk31C;
            if (ctl->pad17[0] != 0) {
                /* high jump */
                jump_v = 0.0f;
                anim = 0x279;
                speed = 1.25f;
                rec->unk84.uh = 0;
                rec->disable_jump = 0xA;
                rec->disable_run = 0xFF;
                rec->unk83 = 0xFF;
            } else if ((s16)ctl->unk8 != 0) {
                /* item jump */
                rec->unk83 = 0xFF;
                rec->disable_run = 0xFF;
                func_1505E650(rec, 0x43, 1.3f, 2.0f, 0.0f, 0.0f, 0);
                anim = 0;
                jumped = 0;
            } else {
                anim = 0x32;
                if (ctl->pad17[3] != 0) {
                    /* super jump */
                    jump_v = 0.0f;
                    rec->disable_run = 0xFF;
                    rec->unk81 = 1;
                    rec->y_velocity = 47.0f;
                    rec->gravity = 6.0f;
                } else if (!(buttons & 0x2000) || ctl->pad79[2] == 7 || ctl->pad79[2] == 8) {
                    /* normal / run jump */
                    if (rec->disable_run != 0) {
                        rec->disable_run = 0;
                        a = ctl->unk4C;
                        rec->unk76 = a;
                        rec->unk7A = a;
                    }
                    anim = 0x32;
                    if (rec->xz_velocity < 9.0f) {
                        jump_v = 0.0f;
                        ctl->unk31 = 1;
                    } else {
                        speed = 0.8f;
                        ctl->unk31 = 2;
                        anim = 0x37;
                        if (rec->unk31C->unk78 == 0x21) {
                            anim = 0x19E;
                            speed = 1.4f;
                        }
                    }
                    if (rec->unk31C->pad79[2] == 7 || rec->unk31C->pad79[2] == 8) {
                        rec->unk31C->unk31 = 0;
                    }
                    if (rec->unk31C->unk4E == 1) {
                        rec->y_velocity = 40.0f;
                    } else {
                        rec->y_velocity = 59.0f;
                    }
                    if (rec->unk31C->unk4E == 2) {
                        rec->y_velocity = 80.0f;
                        sound = 0x7E2;
                    }
                    rec->gravity = 4.0f;
                    if ((rec->unk184 & 0x1F) == 0xC) {
                        rec->y_velocity *= 0.7f;
                    }
                    if ((rec->unk184 & 0x1F) == 0x13) {
                        anim = 0x32;
                        rec->y_velocity *= 0.55f;
                    }
                    if (D_800CC69C != 0) {
                        rec->unk81 = 0x82;
                    } else {
                        rec->unk81 = 2;
                    }
                } else {
                    /* Z long jump */
                    if (D_800CC69C == 0) {
                        rec->unk81 = 1;
                    } else {
                        rec->unk81 = 0x81;
                    }
                    jump_v = 0.0f;
                    speed = 1.08f;
                    rec->disable_run = 0x17;
                    rec->unk83 = 0x64;
                    anim = 0xEB;
                    if (D_800CC69C != 0) {
                        rec->xz_velocity = rec->xz_velocity;
                        rec->y_velocity *= 1.4f;
                        rec->gravity = 3.8f;
                    }
                }
            }
        }
        if (jumped != 0) {
            if (sound != 0 && func_1506E46C(rec, &sound, 1) != 0) {
                func_15060A30(sound, rec);
            }
            glide = 0;
            if (ride != 0) {
                /* push off the ridden record */
                rec->xz_velocity = 20.0f;
                if (ride == 0x29) {
                    func_15052F58(rec->unk65 - 1, 0xE);
                } else if (ride == 0x8B) {
                    func_15052F58(rec->unk65 - 1, 5);
                    rec->xz_velocity = 30.0f;
                    if (D_800BE616 != 0) {
                        rec->unk7A = 0x3000;
                        if (rec->z_position > 0.0f) {
                            rec->unk7A = 0xB000;
                        }
                    }
                } else if (ride == 0x24) {
                    func_15052F58(rec->unk65 - 1, 0xE);
                    rec->xz_velocity = 27.0f;
                }
                rec->unk31C->unk30 = 0;
                rec->immune = 0x14;
                rec->unk76 = rec->unk7A + 0x1200;
                rec->unk65 = 0;
                rec->disable_run = 0xFF;
                rec->y_velocity = 30.0f;
                rec->unk31C->unk31 = 0;
            }
            sound = 0;
            rec->unk31C->unk55 = 0;
            if (rec->unk31C->unk4E != 0) {
                rec->unkA9 = 5;
            }
            if (anim != 0xEB && anim != 0x279) {
                rec->unk83 = 0;
                rec->unk28 = 80.0f;
            }
            if (rec->unk31C->unk4E != 2) {
                func_1505E650(rec, anim, speed, 2.0f, jump_v, 0.0f, 0);
            }
            height = 25.0f;
            rec->unkB8 = 0.0f;
            rec->unk110 = 0;
            rec->unk100 &= 0x53;
        }
    }

    /* 5. in the air */
    func_1506045C(rec, buttons, D_800CC288, height, 0);
    anim = 0;
    ctl = rec->unk31C;
    blend = 2.0f;
    if ((ctl->pad98[0] != 0 || ctl->unk95 != 0) && rec->disable_jump == 0 && (D_800CC288 & 0x8000)) {
        /* double jump */
        a = ctl->unk4C;
        rec->unk7A = a;
        rec->unk76 = a;
        ctl->unk31 = 1;
        rec->unk80 = 0xA;
        rec->unk83 = 0;
        rec->unk100 |= 8;
        rec->disable_run = 0;
        rec->unk100 &= 0xDE;
        anim = 0x37;
        speed = 1.3f;
        if (rec->in_water == 0) {
            rec->y_velocity = 40.0f;
            rec->gravity = 3.2f;
        }
        rec->xz_velocity = rec->unk44 * 0.6f + 15.0f;
        if (rec->unk44 < 4.0f) {
            rec->unk7A = rec->unk76 = rec->unk76 + 0x8000;
        }
        rec->unk31C->unk95 = 0;
        rec->unk31C->unk97 = 0;
        if (rec->unk31C->pad98[0] != 0) {
            func_151AE814((u8 *)rec);
            anim = 0x37;
            blend = 2.0f;
        }
        rec->unk31C->unk54 = 0;
    } else if ((D_800CC288 & 0x8000) && ctl->unk4E == 0) {
        /* high fall */
        if (rec->unk84.uh != 0x3B && rec->unk84.uh != 0x3C && rec->unk137 == 0 && rec->unk13C == 0
            && ctl->unk95 == 0 && ctl->unk31 == 0 && height > 55.0f) {
            if (rec->unk118 != -10000.0f && rec->unk118 - rec->unk180 > 100.0f) {
                rec->unk81 = 1;
                rec->disable_run = 0x78;
                rec->unk137 = 0;
                anim = 0x3B;
                rec->gravity = 6.0f;
                rec->unk1CC = rec->y_position;
            }
        }
    }
    if (D_800BE616 == 0 && glide != 0 && rec->in_water == 0 && rec->unk13C <= 100 && rec->id != 0x96) {
        ctl = rec->unk31C;
        if (ctl->unk31 != 0 && ctl->unk4E == 0) {
            if (ctl->unk31 < 3) {
                /* helicopter glide start */
                if ((D_800CC288 & 0x8000) && rec->unk28 > 1.0f) {
                    blend = 6.0f;
                    anim = 0xE9;
                    rec->xz_velocity *= 0.3f;
                    ctl->unk31 = 3;
                    rec->y_velocity = 0.0f;
                    rec->unk81 = 1;
                    rec->gravity = 1.0f;
                    rec->unk1CC = rec->y_position;
                    if (rec->unk84.uh != 0xE9) {
                        func_100109D0(rec);
                        func_1000FA64(0x61E, rec->x_position, rec->y_position, rec->z_position, 0x7FFF, 0x1F4, 0xC8,
                                      (s32)func_1000EFB4, rec, (s32)D_800997E8, 0, 0);
                        func_151C7450((u8 *)rec, 0xFF, 1);
                        anim = 0xE9;
                        blend = 6.0f;
                    }
                }
            } else {
                /* gliding: count up; A held keeps it to 0x3E frames, else 0x13 */
                ctl->unk31 += D_800BE9A0;
                if (rec->unk31C->unk31 < 0xD) {
                    rec->y_velocity = 8.0f;
                }
                if (rec->unk31C->unk31 < 0x11) {
                    rec->animation_speed += 0.25f;
                } else {
                    rec->animation_speed += (0.6f - rec->animation_speed) * 0.1f;
                }
                anim = 0xE9;
                speed = rec->animation_speed;
                rec->unk31C->pad3C[0] = 6;
                if ((!(*(u16 *)pad & 0x8000) && rec->unk31C->unk31 >= 0x13) || rec->unk31C->unk31 >= 0x3E) {
                    rec->disable_run = 0xFF;
                    rec->unk100 = 0x55;
                    rec->unk31C->unk31 = 0;
                    rec->gravity = 4.5f;
                    func_1506AF74();
                    blend = 2.0f;
                    anim = 0;
                } else {
                    rec->unk80 = 1;
                    rec->unkAA = 0x4B;
                    rec->unk83 = 1;
                    if (rec->y_velocity < -8.0f) {
                        rec->y_velocity = -8.0f;
                    }
                }
            }
        }
    }
    if (anim != 0) {
        func_1505E650(rec, anim, speed, blend, 0.0f, 0.0f, 0);
    }
    if (sound != 0) {
        func_15060A30(sound, rec);
    }
    if ((rec->unk81 & 7) == 2 && !(*(u16 *)pad & 0x8000)) {
        rec->unk81 = rec->unk81 - 1;
        rec->gravity = 6.2f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F298.s")
#endif
#ifdef NON_MATCHING
s32 func_15064668(struct127 *, s32, f32, s32, s32); /* P102: arg2 = height (f32, was float bits in s32) */
s32 func_15065E18(struct127 *, s32, s32, f32, s32, s32, s32, s32, s32); /* P102: arg3 = height */
s32 func_15080B38(u8);
extern s32 D_800CC3C8;
extern u16 *D_800CC6A4;

void func_1506045C(struct127 *arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
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
            temp_v0_3 = *((u8 *)&D_800CC3C8 + (temp_a0 * 0x32C));
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
#ifdef NON_MATCHING
// object_forget_target: clear the target byte +0x65 (object index + 1) of the first 25 live objects that point
// at `obj` (called by the object removal func_15060F28).
void func_15060D54(struct127 *obj) {
    s32 idx = obj - D_800CC2D0;
    u8 *o;
    s32 i;

    for (i = 0; i < 25; i++) {
        o = (u8 *) &D_800CC2D0[i];
        if (*(s32 *) o != 0 && o[0x65] == idx + 1) {
            o[0x65] = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060D54.s")
#endif
#ifdef NON_MATCHING
/* Removal of an object (struct127, ends its fade mode 5 / 6 in func_150617BC). mode 0 = plain, 1 = killed
 * (func_1504AF10(obj, 1, 0) and func_1503E550(slot)), 2 = removed without a trace (marker byte cleared).
 * Releases its model / sound / effect, gives back the map marker byte D_800D252C[+0x13F] (kept as 0x80 or
 * cleared, depending on the marker record +0x144), frees the buffers +0x260.. and the per-player handles +0x304. */
void func_15060F28(struct127 *obj, s32 mode) {
    u8 *o = (u8 *)obj;
    u8 *rec;
    u8 *p;
    u8 slot;
    s32 i;

    func_1514D880(o);
    func_151695F0(o, 0);
    if (o[5] != 2 && o[5] != 3) {
        func_150849C0(obj);
        func_150626EC(obj, mode);
    }
    if (mode == 1) {
        func_1504AF10(obj, 1, 0);
        func_1503E550(obj - D_800CC2D0);
    }
    slot = o[0x13F];
    if (slot != 0xFF) {
        if (mode == 2) {
            D_800D252C[slot] = 0;
        } else {
            rec = *(u8 **)(o + 0x144);
            if (rec == NULL) {
                D_800D252C[slot] &= 0x80;
            } else if (*(u16 *)rec & 0x20) {
                rec[2] = 1;
                D_800D252C[o[0x13F]] = 0;
            } else if (*(u16 *)rec & 1) {
                D_800D252C[slot] = 0;
            } else {
                rec[2] = 1;
                p = D_800D252C + o[0x13F];
                *p &= 0x80;
            }
        }
    }
    if (*(s32 *)(o + 0x260) != 0) {
        func_10004074(*(s32 *)(o + 0x260));
    }
    if (*(s32 *)(o + 0x264) != 0) {
        func_10004074(*(s32 *)(o + 0x264));
    }
    if (*(s32 *)(o + 0x268) != 0) {
        func_10004074(*(s32 *)(o + 0x268));
    }
    if (*(s32 *)(o + 0x26C) != 0) {
        func_10004074(*(s32 *)(o + 0x26C));
    }
    if (*(s32 *)(o + 0x1D8) != 0) {
        func_10004074(*(s32 *)(o + 0x1D8));
    }
    if (*(s32 *)(o + 0x2D4) != 0) {
        func_1516972C(*(struct102 **)(o + 0x2D4));
    }
    /* per-player handles: only the first one is tested */
    if (*(s32 *)(o + 0x304) != 0) {
        for (i = 0; i <= D_80082FA0; i = (i + 1) & 0xFF) {
            func_100043B4(*(s32 **)(o + 0x304 + i * 4), 4);
        }
    }
    if (*(s32 *)(o + 0x314) != 0) {
        func_100043B4(*(s32 **)(o + 0x314), 4);
    }
    if (*(s32 *)(o + 0x2D0) != 0) {
        func_10004074(*(s32 *)(o + 0x2D0));
    }
    if (*(s32 *)(o + 0x324) != 0) {
        func_10004074(*(s32 *)(o + 0x324));
    }
    if (*(u8 **)(o + 0x31C) != NULL && *(s32 *)(*(u8 **)(o + 0x31C) + 0x11C) != 0) {
        func_10004074(*(s32 *)(*(u8 **)(o + 0x31C) + 0x11C));
    }
    func_10010AA8(obj);
    func_150306D4(o);
    func_15060D54(obj);
    func_15189040((s32)obj);
    if (*(s32 *)(o + 0x31C) != 0) {
        func_10004074(*(s32 *)(o + 0x31C));
    }
    func_1505F188(obj);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060F28.s")
#endif
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

#ifdef NON_MATCHING
/* Fade / visibility command for an object (struct127). Commands >= 8 work on player p's visibility:
 * 8 = hide (bit p of +0x0F set, target 0), 10 = hide at once (bit p + 4 set), others = show (bit p cleared,
 * target 0xFF); a pending "at once" bit p + 4 sets the byte +0x0B + p and is cleared; the byte also jumps to the
 * target when +0x2FD or D_800DBFF4[p] is set. Commands < 8 start an alpha fade (+0x0A mode, +0x07 alpha,
 * +0x08 target, +0x09 step) unless a fade of a higher mode runs: 4 = fade in from 0, 5 / 6 = fade out (then
 * removal, func_150617BC), 2 = fade to a2 by a3, 1 = set alpha a2 and stop. With D_800DBFF4 set the alpha
 * jumps to the target. */
void func_1506160C(struct127 *obj, u8 cmd, u8 a2, u8 a3, u8 p) {
    u8 *o = (u8 *)obj;
    u8 target;
    s32 bit;

    if (cmd >= 8) {
        if (cmd == 10) {
            o[0xF] |= (1 << p) << 4;
            target = 0;
        } else {
            bit = 1 << p;
            if (cmd == 8) {
                o[0xF] |= bit;
                target = 0;
            } else {
                o[0xF] &= ~bit;
                target = 0xFF;
            }
            if (o[0xF] & (bit << 4)) {
                o[0xB + p] = target;
            }
            o[0xF] &= ~(bit << 4);
        }
        if (o[0x2FD] != 0 || D_800DBFF4[p] != 0) {
            o[0xB + p] = target;
        }
        return;
    }
    if (cmd < o[0xA]) {
        return;
    }
    switch (cmd) {
        case 4:
            o[0xA] = cmd;
            o[7] = 0;
            o[8] = 0xFF;
            o[9] = 0x20;
            break;
        case 5:
            o[0xA] = cmd;
            o[8] = 0;
            o[9] = 0x20;
            break;
        case 6:
            o[0xA] = cmd;
            o[8] = 0;
            o[9] = 8;
            break;
        case 2:
            o[0xA] = cmd;
            o[8] = a2;
            o[9] = a3;
            break;
        case 1:
            o[0xA] = 0;
            o[7] = a2;
            o[8] = a2;
            break;
    }
    if (*(s32 *)D_800DBFF4 != 0) {
        o[7] = o[8];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
#endif
#ifdef NON_MATCHING
/* Per-frame fades of an object (struct127): per player i (0..D_80082FA0) the visibility byte +0x0B + i moves by
 * 50 towards 0 when bit i of +0x0F is set, else towards 0xFF (jumps there when D_800DBFF4[i] is set). With a
 * fade mode (+0x0A) the alpha +0x07 steps by +0x09 towards +0x08; on arrival mode 6 / 5 calls
 * func_15060F28(obj, 1 / 2), any other mode ends (+0x0A = 0). */
void func_150617BC(struct127 *obj) {
    u8 *o = (u8 *)obj;
    s32 i;
    s32 bit;
    s32 v;

    if (*(s32 *)o == 0) {
        return;
    }
    for (i = 0, bit = 1; i <= D_80082FA0; i++, bit <<= 1) {
        v = o[0xB + i];
        if (o[0xF] & bit) {
            if (v > 0) {
                if (D_800DBFF4[i] != 0) {
                    v = 0;
                } else {
                    v -= 50;
                    if (v < 0) {
                        v = 0;
                    }
                }
                o[0xB + i] = v;
            }
        } else if (v < 0xFF) {
            if (D_800DBFF4[i] != 0) {
                v = 0xFF;
            } else {
                v += 50;
                if (v > 0xFF) {
                    v = 0xFF;
                }
            }
            o[0xB + i] = v;
        }
    }
    if (o[0xA] == 0) {
        return;
    }
    if (o[8] != o[7]) {
        if (o[7] < o[8]) {
            v = o[7] + o[9];
            if (v > o[8]) {
                v = o[8];
            }
        } else {
            v = o[7] - o[9];
            if (v < o[8]) {
                v = o[8];
            }
        }
        o[7] = v;
    }
    if (o[8] != o[7]) {
        return;
    }
    if (o[0xA] == 6) {
        func_15060F28(obj, 1);
    } else if (o[0xA] == 5) {
        func_15060F28(obj, 2);
    } else {
        o[0xA] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150617BC.s")
#endif
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
void func_150617BC(struct127 *);
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
#ifdef NON_MATCHING
/* Shared animation state of some object kinds (D_800CC298, 0x18 bytes). */
struct ObjAnimShared {
    /* 0x00 */ f32 scrollU;   /* kind 0x24: texture scroll, degrees */
    /* 0x04 */ f32 scrollV;
    /* 0x08 */ s8 jitter;     /* kind 0x24: random -2..2 */
    /* 0x09 */ s8 pulse;      /* kind 0x2C: 0..41 ping-pong */
    /* 0x0A */ s8 pulseStep;
    /* 0x0B */ u8 phase[4];   /* kind 0x3A: colour phases, stepped by the bytes of D_80086490 */
    /* 0x0F */ u8 frameTimer; /* kind 0x4B */
    /* 0x10 */ u8 glow;       /* kind 0x54: 0..255 */
};
#define OBJ_ANIM (*(struct ObjAnimShared *)&D_800CC298)

/* Per-frame texture / colour animation of the live objects (D_800CC2D0[], +0x2FA visible), by kind (+0x04).
 * Effects shared by every object of one kind (func_15062D10 texture scroll, func_15062E24, func_eu_1501B640
 * colours) run for the first such object only (done[]). */
void func_15061B4C(void) {
    u8 done[10];
    u8 *obj;
    u8 type;
    s32 i;
    s32 v;
    u8 steps[4];
    f32 colours[4];
    f32 glow;
    s32 **tex;

    bzero(done, sizeof(done));
    for (obj = (u8 *)D_800CC2D0; obj != (u8 *)&D_800D121C; obj += sizeof(struct127)) {
        if (*(s32 *)obj == 0 || obj[0x2FA] == 0) {
            continue;
        }
        type = obj[4];
        switch (type) {
            case 0x13:
                if (!done[0]) {
                    func_15062D10(type, 0x5E, 0, -1, 0, 0);
                    func_15062D10(type, 0x60, 0, -1, 0, 0);
                    func_15062D10(type, 0x62, 0, -1, 0, 0);
                    func_15062D10(type, 0x64, 0, -1, 0, 0);
                    done[0] = 1;
                }
                break;
            case 0x23:
                if (!done[1]) {
                    func_15062D10(type, 0x1E9, 0, -1, 0, 0);
                    func_15062D10(type, 0x1EB, 0, -1, 0, 0);
                    func_15062D10(type, 0x1ED, 0, -1, 0, 0);
                    func_15062D10(type, 0x1EF, 0, -1, 0, 0);
                    done[1] = 1;
                }
                break;
            case 0x24:
                if (!done[2]) {
                    if ((u32)func_150ADA20() % 1000 < 300) {
                        OBJ_ANIM.jitter = (u32)func_150ADA20() % 5 - 2;
                    }
                    func_15062D10(type, 4, -4, OBJ_ANIM.jitter, 0, 0);
                    tex = &((s32 **)&D_800C4440)[type];
                    if (*tex != NULL) {
                        func_15062E24(type, (*tex)[0], 0x37, 0, (s32)OBJ_ANIM.scrollV, 2, 1);
                        func_15062E24(type, (*tex)[1], 0x27, 0x37, (s32)OBJ_ANIM.scrollU, 1, 0);
                    }
                    OBJ_ANIM.scrollU += -4.0f * (f32)D_800BE9E4;
                    if (OBJ_ANIM.scrollU <= 0.0f) {
                        OBJ_ANIM.scrollU += 360.0f;
                    }
                    OBJ_ANIM.scrollV += -0.5f * (f32)D_800BE9E4;
                    if (OBJ_ANIM.scrollV <= 0.0f) {
                        OBJ_ANIM.scrollV += 360.0f;
                    }
                    done[2] = 1;
                }
                break;
            case 0x2C:
                if (!done[3]) {
                    v = OBJ_ANIM.pulse;
                    if (v > 40) {
                        OBJ_ANIM.pulseStep = -1;
                    } else if (v <= 0) {
                        OBJ_ANIM.pulseStep = 1;
                    }
                    OBJ_ANIM.pulse = v + OBJ_ANIM.pulseStep;
                    func_15062D10(type, 0xAA, OBJ_ANIM.pulse, 0, 0, 1);
                    done[3] = 1;
                }
                break;
            case 0x3A:
                if (!done[4]) {
                    *(s32 *)steps = D_80086490;
                    if (*(s32 *)(obj + 0x1D4) != 0) {
                        for (i = 0; i < 4; i++) {
                            colours[i] = (func_150489B0(OBJ_ANIM.phase[i]) + 1.0f) * 0.5f;
                            OBJ_ANIM.phase[i] += steps[i];
                        }
                        func_eu_1501B640((struct127 *)obj, colours, 1);
                        done[4] = 1;
                    }
                }
                break;
            case 0x3F:
                if (!done[5]) {
                    func_15062D10(type, 4, 0, -4, 0, 0);
                    done[5] = 1;
                }
                break;
            case 0x4B:
                if (!done[6]) {
                    done[6] = 1;
                    func_15062D10(type, 0x173, -4, 0, 0, 0);
                    func_15062D10(type, 0x175, -2, 0, 0, 0);
                    func_15062D10(type, 0x177, -1, 0, 0, 0);
                }
                /* frame +0x68 cycles 15, 16, 17, 18, 17, 16 (+0x69 = 0..5), one step every 4 ticks */
                if (OBJ_ANIM.frameTimer >= 4) {
                    OBJ_ANIM.frameTimer = 0;
                    if (obj[0x69] == 5) {
                        obj[0x69] = 0;
                    } else {
                        obj[0x69]++;
                    }
                    if (obj[0x69] >= 3) {
                        obj[0x68] = 5 - obj[0x69];
                    } else {
                        obj[0x68] = obj[0x69];
                    }
                    obj[0x68] += 15;
                } else {
                    OBJ_ANIM.frameTimer += D_800BE9E4;
                }
                break;
            case 0x45:
                v = obj[0x6D];
                obj[0x68] = (v >= 10) ? v - 10 : v * 2 + 6;
                break;
            case 0x5B:
                for (i = 0; i < 2; i++) {
                    v = obj[0x6C + i];
                    obj[0x68 + i] = (v >= 10) ? v - 10 : D_800997EC[v];
                }
                break;
            case 0x54:
                if (*(s32 *)(obj + 0x2EC) != 0) {
                    OBJ_ANIM.glow = (OBJ_ANIM.glow < 0xEB) ? OBJ_ANIM.glow + 20 : 0xFF;
                } else {
                    OBJ_ANIM.glow = (OBJ_ANIM.glow <= 20) ? 0 : OBJ_ANIM.glow - 20;
                }
                glow = OBJ_ANIM.glow * (1.0f / 255.0f);
                func_eu_1501B640((struct127 *)obj, &glow, 0);
                break;
            case 0x8A:
                if (D_800BE9F0 != 0x30) {
                    if (*(u16 *)(obj + 0x84) == 1) {
                        func_15062D10(type, 0x253, 0, 0x10, 0, 0);
                        func_15062D10(type, 0x255, 0, 8, 0, 0);
                        func_15062D10(type, 0x257, 0, 4, 0, 0);
                    }
                } else {
                    func_15062FC0(obj, 0, 0, 0x1000, 0x1000, 0xC, 0,
                                  (*(u16 *)(obj + 0x84) == 1) ? -D_800BE9E4 * 40 : 0);
                }
                break;
            case 0x42:
                v = *(u16 *)(obj + 0x84);
                if (v == 2 || v == 1) {
                    if (obj[0x68] == 0xD) {
                        obj[0x68] = 0xC;
                    }
                    if ((func_150ADA20() & 3) == 0) {
                        obj[0x68] = (obj[0x68] == 0x15) ? 0xC : 0x15;
                    }
                } else {
                    obj[0x68] = 0xD;
                }
                break;
            case 0x7B:
                func_eu_150F2230(obj);
                break;
            case 0x92:
                if (!done[9]) {
                    func_15062D10(type, 4, 0, -2, 0, 0);
                    func_15062D10(type, 0x13B, 0, -2, 0, 0);
                    func_15062D10(type, 0x20D, 0, -2, 0, 0);
                    done[9] = 1;
                }
                break;
            case 0x43:
                func_15062D10(type, 4, 0x14, 8, 0, 0);
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
#endif
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
        do {  /* P117: bytes +0xB .. +0xB + D_80082FA0 (was a struct127 stride) */
            temp_t1 = var_v0_2->unkB;
            var_v0_2 = (struct127 *) ((u8 *) var_v0_2 + 1);
            var_a0 += temp_t1;
        } while ((u32) ((u8 *) arg0 + D_80082FA0) >= (u32) var_v0_2);
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
                var_v0_3 += 1; /* P117: next object (was 0x32C objects) */
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
            var_s1 = (s32 *) ((u8 *) var_s1 + 0x40); /* P117: 0x40 bytes (was 0x40 words) */
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
#ifdef NON_MATCHING
/* Removes the objects attached to obj (+0x65 = obj's slot + 1, +0x127 = 0xFF) with func_15060F28(child, mode). */
void func_150626EC(struct127 *obj, s32 mode) {
    struct127 *o;

    for (o = D_800CC2D0; o != (struct127 *)&D_800D121C; o++) {
        if (*(s32 *)o != 0 && ((u8 *)o)[0x65] == (obj - D_800CC2D0) + 1 && ((u8 *)o)[0x127] == 0xFF) {
            func_15060F28(o, mode);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")
#endif

void func_150627D4(struct127 *arg0) {
    arg0->unk2FB = 0;
    func_1503B840(arg0);
    func_15039CC8(arg0);
}
