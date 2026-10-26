#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 interaction_mode_for_level(u32 arg0);
#endif


/* was func_15141970 */
void interact_fx_detach(struct37 *arg0) {
    func_1514EDF0(arg0, arg0->unk2C);
}

/* was func_15141990 */
void interact_fx_destroy(void *arg0) {
    interact_fx_detach(arg0);
}

/* was func_151419B0 */
void interact_fx_delete(void *arg0) {
    interact_fx_detach(arg0);
}

#ifdef NON_MATCHING
/* was func_151419D0 */
void interact_fx_handle_message(struct102 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0_2;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        temp_v0 = ((struct102 *)((u8 *)arg0 + 0x28));
        if (((*(s32 *)((u8 *)arg1 + 0)) == (*(s32 *)((u8 *)temp_v0 + 4))) || ((*(u8 *)((u8 *)temp_v0 + 8)) == (*(u8 *)((u8 *)arg1 + 4)))) {
            node_destroy(arg0);
        }
    } else {
        temp_v0_2 = &arg0->unk28;
        if (temp_t6 == 0x2D) {
            temp_a0 = (*(s32 *)((u8 *)temp_v0_2 + 4));
            temp_v1 = (*(s32 *)((u8 *)arg1 + 0));
            if (temp_v1 == temp_a0) {
                (*(s32 *)((u8 *)temp_v0_2 + 4)) = (s32) (*(u8 *)((u8 *)arg1 + 4));
                (*(u8 *)((u8 *)temp_v0_2 + 8)) = (u8) (*(u8 *)((u8 *)arg1 + 9));
                return;
            }
            if ((s32) (*(u8 *)((u8 *)arg1 + 4)) == temp_a0) {
                (*(s32 *)((u8 *)temp_v0_2 + 4)) = temp_v1;
                (*(u8 *)((u8 *)temp_v0_2 + 8)) = (u8) (*(u8 *)((u8 *)arg1 + 8));
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/interact_fx_handle_message.s")
#endif
// NON-MATCHING: one operand swap in the last compare (bnel a0,t2 vs t2,a0)
// void interact_fx_handle_message(struct_eu_151419D0 *arg0, struct_eu_151419D0_msg *arg1, u8 arg2) {
//     struct_eu_151419D0_sub *sub = &arg0->unk28;
//     s32 id;
//     s32 cur;
//
//     if (arg2 == 0) {
//         id = arg1->unk0;
//         if ((id == sub->unk4) || (sub->unk8 == *(u8 *)&arg1->unk4)) {
//             node_destroy((struct102 *)arg0);
//         }
//     } else if (arg2 == 0x2D) {
//         cur = sub->unk4;
//         id = arg1->unk0;
//         if (id == cur) {
//             sub->unk4 = arg1->unk4;
//             sub->unk8 = arg1->unk9;
//         } else if (arg1->unk4 == cur) {
//             sub->unk4 = id;
//             sub->unk8 = arg1->unk8;
//         }
//     }
// }
#ifdef NON_MATCHING
u32 floor_flags_surface_type(s32);
s32 obj_interaction_category(struct127 *);

/* was func_15141A7C */
void obj_interaction_update(struct127 *arg0, s32 arg1) {
    struct_eu_link *sp3C;
    s32 temp_v0;
    s32 temp_v0_2;
    struct32 *temp_v1;
    struct_eu_attached *temp_v0_3;
    struct_eu_link *temp_a0;
    struct_eu_link *temp_t8;

    if (D_800BE616 == 0) {
        temp_v0 = obj_interaction_category(arg0);
        if (D_8008A084[temp_v0] != 0) {
            temp_v0_2 = ((s32 (*)(s32, struct127 *)) D_8008A084[temp_v0])(interaction_mode_for_level(floor_flags_surface_type(arg0->unk184)), arg0);
            if (temp_v0_2 != -1) {
                temp_v1 = &D_8008A0B4[temp_v0_2];
                if (temp_v1->unk0 != 0) {
                    if (temp_v1->unk4 > 0) {
                        obj_interaction_attach_timed(arg0, temp_v0_2);
                    } else {
                        /* P317: the entries are `void (obj, s32, s32)`; the asm leaves the index in a3, no entry reads it */
                        ((void (*)(struct127 *, s32, s32)) D_8008A0B4[temp_v0_2].unk0)(arg0, arg1, 0);
                    }
                }
            }
        }
        temp_a0 = arg0->unk2F4;
        sp3C = temp_a0;
        if (func_1514F250(temp_a0, 0x1A, &sp3C) != 0) {
            do {
                temp_v0_3 = sp3C->unk10;
                if (D_8008A0B4[temp_v0_3->unk28].unk0 != 0) {
                    ((void (*)(struct127 *, s32, s32)) D_8008A0B4[temp_v0_3->unk28].unk0)(arg0, arg1, temp_v0_3->unkE);
                }
                temp_t8 = sp3C->unk14;
                sp3C = temp_t8;
            } while (func_1514F250(temp_t8, 0x1A, &sp3C) != 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/obj_interaction_update.s")
#endif
// requires jump table
#ifdef NON_MATCHING
/* Category of object `obj` for the interaction tables D_8008A084 / D_8008A0B4 (obj_interaction_update), from its type id
 * (+0x04). Jump tables jtbl_800A55F8 (ids 121..165) and D_eu_800A56AC (ids 0..88); anything else is 11. */
/* was func_15141C0C */
s32 obj_interaction_category(struct127 *obj) {
    switch (obj->id) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 150:
            return 0;
        case 16:
        case 145:
            return 1;
        case 43:
            return 2;
        case 69:
            return 3;
        case 75:
            return 4;
        case 84:
            return 5;
        case 54:
        case 83:
        case 165:
            return 6;
        case 88:
            return 7;
        case 123:
            return 8;
        case 33:
            return 9;
        case 121:
            return 10;
        default:
            return 11;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/obj_interaction_category.s")
#endif
/* was func_15141CC0 */
s32 interaction_mode_for_level(u32 arg0) {
    if (D_800BE9F0 == 0x2F) {
        return 6;
    }
    if (D_800BE9F0 == 0x42) {
        return 7;
    }
    if (D_800BE9F0 == 0x27) {
        return 8;
    }
    if (D_800BE9F0 == 0x19) {
        return 5;
    }
    switch (arg0) {
    case 10:
        return 0;
    case 7:
        return 2;
    case 11:
        return 1;
    case 15:
        return 3;
    case 2:
    case 8:
    case 12:
        if (D_800BE9F0 == 2) {
            return 7;
        }
        return 4;
    case 5:
        if (D_800BE9F0 == 0x14) {
            return 5;
        }
        return 9;
    case 0:
        return 9;
    default:
        return 9;
    }
}

/* was func_15141DA4 */
void obj_interaction_start_timed(void *arg0, s32 arg1, s32 arg2) {
    if ((arg1 < 12) && (arg1 >= 0) &&
        (arg2 < 20) && (arg2 >= 0) &&
        (D_800BE616 == 0) &&
        (D_8008A084[arg1] != 0) && (arg2 != -1)) {
        if ((D_8008A0B4[arg2].unk0 != 0) && (D_8008A0B4[arg2].unk4 > 0)) {
            obj_interaction_attach_timed(arg0, arg2);
        }
    }
}

#ifdef NON_MATCHING
s32 memcpy(u8 *, s32 *, s32);

/* was func_15141E38 */
void obj_interaction_attach_timed(struct127 *arg0, s32 arg1) {
    struct_eu_link *sp58;
    struct { s32 id; struct127 *owner; u8 uid; } rec;   /* sp40: 0xC bytes copied to the new object +0x28 */
    struct260 *temp_v0_2;
    struct_eu_attached *temp_v0;
    struct_eu_link *temp_a0;
    struct_eu_link *temp_t4;
    struct_eu_link *var_s1;

    var_s1 = NULL;
    temp_a0 = arg0->unk2F4;
    sp58 = temp_a0;
    if (func_1514F250(temp_a0, 0x1A, &sp58) != 0) {
        do {
            temp_v0 = sp58->unk10;
            if (arg1 == temp_v0->unk28) {
                var_s1 = sp58;
                temp_v0->unkE = (s16) D_8008A0B4[arg1].unk4;
            }
            temp_t4 = sp58->unk14;
            sp58 = temp_t4;
        } while (func_1514F250(temp_t4, 0x1A, &sp58) != 0);
    }
    if (var_s1 == NULL) {
        rec.id = arg1;
        rec.owner = arg0;
        rec.uid = arg0->unique_id;
        temp_v0_2 = func_15149130((*(s16 *)((u8 *)(&D_8008A0B4[arg1]) + 6)), -1, -1, -1, 1U, 0x32U, (struct37 *)0xC, 0xFFU, 1);
        if (temp_v0_2 != NULL) {
            memcpy((u8 *)temp_v0_2 + 0x28, (s32 *)&rec, 0xC);
            func_1514F18C(temp_v0_2, arg0, 0x1A);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/obj_interaction_attach_timed.s")
#endif
// NON-MATCHING: stack layout (sp40 should be at 0x40, list cursor at 0x58) and loop temp
// void obj_interaction_attach_timed(struct127 *arg0, s32 arg1) {
//     struct_eu_link *sp58;
//     struct_eu_link *temp;
//     struct {
//         s32 unk0;
//         struct127 *unk4;
//         u8 unk8;
//     } sp40;
//     struct_eu_link *found;
//     struct260 *temp_v0;
//
//     found = NULL;
//     sp58 = arg0->unk2F4;
//     if (func_1514F250(sp58, 0x1A, &sp58)) {
//         do {
//             if (arg1 == sp58->unk10->unk28) {
//                 found = sp58;
//                 sp58->unk10->unkE = D_8008A0B4[arg1].unk4;
//             }
//             temp = sp58->unk14;
//             sp58 = temp;
//         } while (func_1514F250(temp, 0x1A, &sp58));
//     }
//     if (found == NULL) {
//         sp40.unk0 = arg1;
//         sp40.unk4 = arg0;
//         sp40.unk8 = arg0->unique_id;
//         temp_v0 = func_15149130(D_8008A0B4[arg1].unk4, -1, -1, -1, 1, 0x32, 0xC, 0xFF, 1);
//         if (temp_v0 != NULL) {
//             memcpy((u8 *)temp_v0 + 0x28, &sp40, 0xC);
//             func_1514F18C(temp_v0, arg0, 0x1A);
//         }
//     }
// }
typedef struct {
    s32 u0;
    s16 u4;
    u8 u6;
    u8 u7;
    s32 u8_;
    s32 uC;
    u8 u10[8];
    s32 u18;
    s32 u1C;
    u8 u20;
    s16 u22;
    s16 u24;
} Spawn41F78;
/* was func_15141F78 */
void fx_spawn_impact_particle(u8 arg0, u8 *arg1, f32 arg2, u8 arg3, u8 *arg4, u8 arg5) {
    Spawn41F78 sp;
    f32 f;
    s32 v;

    sp.u6 = arg0;
    sp.u7 = 0;
    sp.u0 = 0x6F701;
    sp.u4 = random_int() % 61U + 100;
    sp.u8_ = 0;
    sp.uC = 0;
    sp.u10[0] = (random_int() & 0x7F) + 0x80;
    sp.u10[1] = 0xFF;
    sp.u10[2] = 0xFF;
    sp.u10[3] = 0xFF;
    sp.u10[4] = 0xFF;
    sp.u10[5] = 0xFF;
    sp.u18 = 0x3B0002;
    sp.u10[6] = 0;
    sp.u10[7] = 7;
    sp.u20 = 0xFF;
    sp.u1C = *(s32 *)(arg1 + 0x18);
    sp.u22 = 0x28;
    sp.u24 = 6;
    f = (random_float() * 5.0f + 10.0f) * arg2;
    if (arg5 == 2) {
        v = 1;
    } else {
        v = 0;
    }
    sprite_fx_spawn_cam_at((s32)&sp, 0, 0, (s32)(arg1 + 4), *(f32 *)(arg4 + 0), *(f32 *)(arg1 + 0), *(f32 *)(arg4 + 8), f, f, arg3, v, 3, 1, 0, 0xFF, 1);
}
// NON-MATCHING: need to determine arguments
// void sprite_fx_spawn_cam_at(s32, s32, s32, u16, s32, s32, s32, f32, f32, s32, s32, s32, s32, s32, u8, s32);
// s32 sprite_fx_spawn_cam_at(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
// void fx_spawn_impact_particle(u8 arg0, struct157 *arg1, f32 arg2, s32 arg3, struct157 *arg4, u8 arg5) {
//     struct157 tmp;
//     f32 temp_f2;
//     s32 phi_v0;
//
//     tmp.unk6 = arg0;
//     tmp.unk7 = 0;
//     tmp.unk0 = 0x6F701;
//     tmp.unk4 = (random_int() % 61U) + 100;
//     tmp.unk8 = 0;
//     tmp.unkC = 0;
//     tmp.unk10 = (random_int() & 0x7F) + 128;
//     tmp.unk11 = 0xFF;
//     tmp.unk12 = 0xFF;
//     tmp.unk13 = 0xFF;
//     tmp.unk14 = 0xFF;
//     tmp.unk15 = 0xFF;
//     tmp.unk18 = 0x3B0002;
//     tmp.unk16 = 0;
//     tmp.unk17 = 7;
//     tmp.unk20 = 0xFF;
//     tmp.unk1C = arg1->unk18;
//     tmp.unk22 = 0x28;
//     tmp.unk24 = 6;
//     temp_f2 = ((random_float() * 5.0f) + 10.0f) * arg2;
//     // --- matching to here ---
//     if (arg5 == 2) {
//         phi_v0 = 1;
//     } else {
//         phi_v0 = 0;
//     }
//     sprite_fx_spawn_cam_at(&tmp, 0, 0, arg1->unk4, arg4->unk0, arg1->unk0, arg4->unk8, temp_f2, temp_f2, arg3, phi_v0, 3, 1, 0, 0xFF, 1);
// }

/* was func_151420F8 */
s32 obj_query_table6(struct127 *arg0) {
    struct_eu_words6 sp18 = D_800A55E0;

    if (func_150A2FCC(arg0 - D_800CC2D0, 6, &sp18, arg0) == -1) {
        return 0;
    }
    return 1;
}
/* was func_15142180 */
void fx_spawn_impact_burst(u8 arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4) {
    struct_eu_15154488 sp24;

    sp24.unk8 = *arg1;
    sp24.unk14 = 2.5f * arg3;
    sp24.unk18 = 2 * arg3;
    sp24.unk1C = 0.108f;
    sp24.unk20 = 0.20500001f;
    sp24.unk24 = 3.0f * arg4;
    sp24.unk28 = 3.5f * arg4;
    sp24.unk2C = 3;
    sp24.unk2E = 3;
    sp24.unk2 = 0xFF;
    sp24.unk4 = -25;
    sp24.unk6 = 10;
    sp24.unk30 = 3;
    sp24.unk0 = 0;
    sp24.unk32 = 1;
    sp24.unk34 = 9;
    sp24.unk36 = 15;
    sp24.unk38 = 180;
    sp24.unk3A = 75;
    sp24.unk44 = 12;
    sp24.unk46 = 21;
    sp24.unk40 = 0.0f;
    sp24.unk48 = arg2;
    sp24.unk3C = arg0;
    func_15154488(&sp24, &sp24.unk8, 0, 0xFF, 1);
}

/* was func_151422C0 */
s32 debug_tweak_int_mid(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5) {
    return (arg3 + arg2) >> 1;
}

/* was func_151422DC */
s32 debug_tweak_int(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    return arg4;
}

/* was func_151422F8 */
s32 debug_tweak_value(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}

/* was func_15142314 */
void mtx_get_translation(Mtx *arg0, s32 arg1, struct17 *arg2) {
    if (D_800C42B0 != 0) {
        s16 *m = ((s16 (*)[32])arg0)[arg1];

        arg2->unk0 = ((f32)(m[0xC] << 16) + (f32)m[0x1C]) * 0.0000152587890625f;
        arg2->unk4 = ((f32)(m[0xD] << 16) + (f32)m[0x1D]) * 0.0000152587890625f;
        arg2->unk8 = ((f32)(m[0xE] << 16) + (f32)m[0x1E]) * 0.0000152587890625f;
    } else {
        f32 *mf = ((f32 (*)[16])arg0)[arg1];

        arg2->unk0 = mf[12];
        arg2->unk4 = mf[13];
        arg2->unk8 = mf[14];
    }
}
extern f32 D_8009A5E0[];

/* was func_151423D8 */
f32 angle_byte_cos(u8 arg0) {
    s32 idx;
    u8 q;

    if (arg0 & 0x40) {
        idx = 0x40 - (arg0 & 0x3F);
    } else {
        idx = arg0 & 0x3F;
    }
    q = arg0 & 0xC0;
    if ((q == 0) || (q == 0xC0)) {
        return D_8009A5E0[idx];
    }
    return -D_8009A5E0[idx];
}
/* was func_15142444 */
struct127 *obj_resolve_with_model(u8 arg0, struct127 *arg1) {
    struct127 *temp_v0;

    if (arg0 == 0xFF) {
        if (arg1->unk1D4 != NULL) {
            return arg1;
        }
        return NULL;
    }
    if ((arg1 != NULL) && (arg1->interaction_state != 0) && (arg1->unique_id == arg0)) {
        if (arg1->unk1D4 != NULL) {
            return arg1;
        }
        return NULL;
    }
    temp_v0 = func_15083E90(arg0);
    if ((temp_v0 != NULL) && (temp_v0->unk1D4 != NULL)) {
        return temp_v0;
    }
    return NULL;
}
/* was func_151424F4 */
void mtx_rot_scale_trans_l(Mtx *m, f32 s1, f32 s2, f32 rx, f32 ry, f32 rz, f32 sx, f32 sy, f32 sz, f32 tx, f32 ty, f32 tz) {
    f32 mf[4][4];

    mtxf_rotate_xyz_deg(mf, rx, ry, rz);
    mf[3][0] = tx;
    mf[3][1] = ty;
    mf[3][2] = tz;
    mf[0][0] *= sx * s1;
    mf[0][1] *= sy * s1;
    mf[0][2] *= sz * s1;
    mf[1][0] *= sx * s2;
    mf[1][1] *= sy * s2;
    mf[1][2] *= sz * s2;
    mf[2][0] *= sx * s1;
    mf[2][1] *= sy * s1;
    mf[2][2] *= sz * s1;
    guMtxF2L(mf, m);
}
#ifdef NON_MATCHING
// mtx_look_along_scaled: P208: builds in `m` (guMtxF2L) the matrix that puts a model at (x0, y0, z0) facing
// (x1, y1, z1): row 2 is the unit direction, row 0 the horizontal side vector (dir.z, 0, -dir.x) normalised, row 1
// the up vector dir x side normalised; every row is scaled per column by (sx, sy, sz), rows 0 / 2 also by `scale`
// and row 1 by `up_scale`. No result (P210: void, as game_eu_E66D0's prototype since port P209).
/* was func_15142600 */
void mtx_look_along_scaled(Mtx *m, f32 scale, f32 up_scale, f32 sx, f32 sy, f32 sz, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1,
                  f32 z1) {
    f32 mf[4][4];
    f32 dx, dy, dz, inv, fx, fy, fz, rx, rz, ux, uy, uz;

    dx = x1 - x0;
    dy = y1 - y0;
    dz = z1 - z0;
    inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    fx = dx * inv;
    fy = dy * inv;
    fz = dz * inv;
    inv = 1.0f / sqrtf(fz * fz + -fx * -fx);
    rx = fz * inv;
    rz = -fx * inv;
    ux = fy * rz;
    uy = fz * rx - fx * rz;
    uz = -fy * rx;
    inv = 1.0f / sqrtf(ux * ux + uy * uy + uz * uz);

    mf[0][0] = rx * sx * scale;
    mf[0][1] = 0.0f;
    mf[0][2] = rz * sz * scale;
    mf[0][3] = 0.0f;
    mf[1][0] = ux * inv * sx * up_scale;
    mf[1][1] = uy * inv * sy * up_scale;
    mf[1][2] = uz * inv * sz * up_scale;
    mf[1][3] = 0.0f;
    mf[2][0] = fx * sx * scale;
    mf[2][1] = fy * sy * scale;
    mf[2][2] = fz * sz * scale;
    mf[2][3] = 0.0f;
    mf[3][0] = x0;
    mf[3][1] = y0;
    mf[3][2] = z0;
    mf[3][3] = 1.0f;
    guMtxF2L(mf, m);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/mtx_look_along_scaled.s")
#endif
/* was func_15142838 */
void mtx_rot_scale2_trans_l(Mtx *m, f32 sx, f32 sy, f32 rx, f32 ry, f32 rz, f32 tx, f32 ty, f32 tz) {
    f32 mf[4][4];

    mtxf_rotate_xyz_deg(mf, rx, ry, rz);
    mf[3][0] = tx;
    mf[3][1] = ty;
    mf[3][2] = tz;
    mf[0][0] *= sx;
    mf[0][1] *= sx;
    mf[0][2] *= sx;
    mf[1][0] *= sy;
    mf[1][1] *= sy;
    mf[1][2] *= sy;
    mf[2][0] *= sx;
    mf[2][1] *= sx;
    mf[2][2] *= sx;
    guMtxF2L(mf, m);
}
/* was func_15142914 */
void mtxf_rot_scale2_trans(f32 mf[4][4], f32 sx, f32 sy, f32 rx, f32 ry, f32 rz, f32 tx, f32 ty, f32 tz) {
    mtxf_rotate_xyz_deg(mf, rx, ry, rz);
    mf[3][0] = tx;
    mf[3][1] = ty;
    mf[3][2] = tz;
    mf[0][0] *= sx;
    mf[0][1] *= sx;
    mf[0][2] *= sx;
    mf[1][0] *= sy;
    mf[1][1] *= sy;
    mf[1][2] *= sy;
    mf[2][0] *= sx;
    mf[2][1] *= sx;
    mf[2][2] *= sx;
}
