#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_asinf_poly_p[]; /* was D_800993D0 */
extern u8 g_asinf_near1_p[]; /* was D_800993FC */

#if 0
f32 g_asinf_poly_p_old[] = { 0.0, 3.619550943374634, -6.466859817504883, 3.5107080936431885, -0.5643919706344604, 0.005872000008821487 }; /* was D_80099020 */
f32 g_asinf_poly_q_old[] = { 21.717304229736328, -48.572906494140625, 37.104923248291016, -11.031848907470703, 1.0 }; /* was D_80099038 */
f32 g_asinf_near1_p_old[] = { 0.0, -3.1845738887786865, 3.210297107696533, -0.6077240109443665 }; /* was D_8009904C */
f32 g_asinf_near1_q_old[] = { -19.107446670532227, 27.860130310058594, -11.065337181091309, 1.0, 0.0 }; /* was D_8009905C */

f32 g_heading_rad_to_deg_a = 57.2957763671875; /* was D_80099070 */
f32 g_heading_rad_to_deg_b = 57.2957763671875; /* was D_80099074 */
#endif

extern f32 g_asinf_poly_p_old[]; /* was D_80099020 */
extern f32 g_asinf_poly_q_old[]; /* was D_80099038 */
extern f32 g_asinf_near1_p_old[]; /* was D_8009904C */
extern f32 g_asinf_near1_q_old[]; /* was D_8009905C */
extern f32 g_heading_rad_to_deg_a; /* was D_80099070 */
extern f32 g_heading_rad_to_deg_b; /* was D_80099074 */


/* was func_15048B10 */
void obj_build_inverse_mtx(s32 arg0, s32 arg1) {
    struct191 tmp;

    mtxf_decompose(arg0, &tmp.unk194, &tmp.unk190, &tmp.unk18C, &tmp.unk17C, &tmp.unk178, &tmp.unk174, &tmp.unk188, &tmp.unk184, &tmp.unk180);
    guMtxIdentF(&tmp.unk80);
    tmp.unkA4 = -tmp.unk194;
    tmp.unkA8 = -tmp.unk190;
    tmp.unkAC = -tmp.unk18C;

    mtxf_rotate_xyz_deg(&tmp.unk134, -tmp.unk17C,           0,           0);
    mtxf_rotate_xyz_deg(&tmp.unkF4,            0, -tmp.unk178,           0);
    mtxf_rotate_xyz_deg(&tmp.unkB4,            0,           0, -tmp.unk174);

    mtxf_mul(&tmp.unk80,  &tmp.unkB4, &tmp.unk40);
    mtxf_mul(&tmp.unk40,  &tmp.unkF4, &tmp.unk0);
    mtxf_mul(&tmp.unk0,  &tmp.unk134, arg1);
}

extern f32 g_asinf_one; /* was D_80086370 */
extern f32 g_asinf_neg_one; /* was D_80086374 */
extern f32 g_asinf_quarter_pi; /* was D_80086378 */
extern f32 g_asinf_half_pi; /* was D_8008637C */
extern f32 g_asinf_neg_quarter_pi; /* was D_80086380 */
extern f32 g_asinf_neg_half_pi; /* was D_80086384 */
extern f32 g_asinf_mid_threshold; /* was D_80086388 */
extern s32 g_asinf_poly_q; /* was D_800993E8 */

/* was func_15048C30 */
f32 math_asinf(f32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_t6;

    temp_t6 = ((*(s32 *)&(arg0)) >> 0x17) & 0xFF;
    if (temp_t6 < 0x7E) {
        if (temp_t6 >= 0x63) {
            temp_f2 = arg0 * arg0;
            temp_v1 = ((u8 *)&g_asinf_poly_p);
            return ((temp_f2 * ((*(f32 *)((u8 *)temp_v1 + 4)) + ((((((((*(f32 *)((u8 *)temp_v1 + 0x14)) * temp_f2) + (*(f32 *)((u8 *)temp_v1 + 0x10))) * temp_f2) + (*(f32 *)((u8 *)temp_v1 + 0xC))) * temp_f2) + (*(f32 *)((u8 *)temp_v1 + 8))) * temp_f2)) * arg0) / ((*(f32 *)((u8 *)(&g_asinf_poly_q) + 0)) + ((((((temp_f2 + (*(f32 *)((u8 *)(&g_asinf_poly_q) + 0xC))) * temp_f2) + (*(f32 *)((u8 *)(&g_asinf_poly_q) + 8))) * temp_f2) + (*(f32 *)((u8 *)(&g_asinf_poly_q) + 4))) * temp_f2))) + arg0;
        }
        return arg0;
    }
    if (temp_t6 < 0x7F) {
        temp_f2_2 = fabsf(arg0);
        if (temp_f2_2 < g_asinf_mid_threshold) {
            temp_v1_2 = ((u8 *)&g_asinf_poly_p);   /* P18: the asm uses g_asinf_poly_p here (was D_800993FC) */
            temp_f16 = (2.0f * (arg0 * arg0)) - g_asinf_one;
            temp_f18_2 = temp_f16 * temp_f16;
            temp_f12 = (*(f32 *)((u8 *)temp_v1_2 + 4)) + ((((((((*(f32 *)((u8 *)temp_v1_2 + 0x14)) * temp_f18_2) + (*(f32 *)((u8 *)temp_v1_2 + 0x10))) * temp_f18_2) + (*(f32 *)((u8 *)temp_v1_2 + 0xC))) * temp_f18_2) + (*(f32 *)((u8 *)temp_v1_2 + 8))) * temp_f18_2);
            temp_f14 = (*(f32 *)((u8 *)(&g_asinf_poly_q) + 0)) + ((((((temp_f18_2 + (*(f32 *)((u8 *)(&g_asinf_poly_q) + 0xC))) * temp_f18_2) + (*(f32 *)((u8 *)(&g_asinf_poly_q) + 8))) * temp_f18_2) + (*(f32 *)((u8 *)(&g_asinf_poly_q) + 4))) * temp_f18_2);
            if ((*(s32 *)&(arg0)) > 0) {
                return (0.5f * (((temp_f18_2 * temp_f12 * temp_f16) / temp_f14) + temp_f16)) + g_asinf_quarter_pi;
            }
            return g_asinf_neg_quarter_pi - (0.5f * (((temp_f18_2 * temp_f12 * temp_f16) / temp_f14) + temp_f16));
        }
        temp_v1_3 = ((u8 *)&g_asinf_near1_p);
        temp_f16_2 = (g_asinf_one - temp_f2_2) * 0.5f;
        temp_f0 = sqrtf(temp_f16_2);
        temp_f18 = ((temp_f16_2 * ((*(f32 *)((u8 *)temp_v1_3 + 4)) + ((((*(f32 *)((u8 *)temp_v1_3 + 0xC)) * temp_f16_2) + (*(f32 *)((u8 *)temp_v1_3 + 8))) * temp_f16_2)) * temp_f0) / ((*(f32 *)((u8 *)(&g_asinf_near1_q) + 0)) + ((((temp_f16_2 + (*(f32 *)((u8 *)(&g_asinf_near1_q) + 8))) * temp_f16_2) + (*(f32 *)((u8 *)(&g_asinf_near1_q) + 4))) * temp_f16_2))) + temp_f0;
        if ((*(s32 *)&(arg0)) > 0) {
            return g_asinf_half_pi - (2.0f * temp_f18);
        }
        return (2.0f * temp_f18) + g_asinf_neg_half_pi;
    }
    if (arg0 != arg0) {
        return 0.0f;
    }
    if (arg0 == g_asinf_one) {
        return g_asinf_half_pi;
    }
    if (arg0 == g_asinf_neg_one) {
        return g_asinf_neg_half_pi;
    }
    return 0.0f;
}
// NON-MATCHING: regs and ordering needs fixing
// f32 math_asinf(f32 arg0) {
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f16;
//     f32 temp_f18;
//     f32 temp_f2;
//     f32 temp_f2_3;
//
//     s32 temp_t6;
//     s32 temp_v0;
//
//     temp_v0 = *(s32*)&arg0;
//     temp_t6 = (temp_v0 >> 0x17) & 0xFF;
//     if (temp_t6 < 0x7E) {
//         if (temp_t6 >= 0x63) {
//             temp_f2 = arg0 * arg0;
//             return (
//               (temp_f2 * (g_asinf_poly_p_old[1] + (((((((g_asinf_poly_p_old[5] * temp_f2) + g_asinf_poly_p_old[4]) * temp_f2) + g_asinf_poly_p_old[3]) * temp_f2) + g_asinf_poly_p_old[2]) * temp_f2)) * arg0)
//              / (g_asinf_poly_q_old[0] + ((((((temp_f2 + g_asinf_poly_q_old[3]) * temp_f2) + g_asinf_poly_q_old[2]) * temp_f2) + g_asinf_poly_q_old[1]) * temp_f2))) + arg0;
//         } else {
//             return arg0;
//         }
//     }
//     if (temp_t6 < 0x7F) {
//         temp_f2 = fabsf(arg0);
//         if (temp_f2 < D_80085FE8) {
//             temp_f2_3 = arg0 * arg0;
//             temp_f16 = (temp_f2_3 + temp_f2_3) - D_80085FD0;
//             temp_f18 = temp_f16 * temp_f16;
//             temp_f12 = g_asinf_poly_p_old[1] + (temp_f18 * (g_asinf_poly_p_old[2] + (temp_f18 * (g_asinf_poly_p_old[3] + (temp_f18 * (g_asinf_poly_p_old[4] + (temp_f18 * g_asinf_poly_p_old[5])))))));
//             temp_f14 = g_asinf_poly_q_old[0] + (temp_f18 * (g_asinf_poly_q_old[1] + (temp_f18 * (g_asinf_poly_q_old[2] + (temp_f18 * (g_asinf_poly_q_old[3] + temp_f18))))));
//             if (temp_v0 > 0) {
//                 return (0.5f * (((temp_f18 * temp_f12 * temp_f16) / temp_f14) + temp_f16)) + D_80085FD8;
//             } else {
//                 return D_80085FE0 - (0.5f * (((temp_f18 * temp_f12 * temp_f16) / temp_f14) + temp_f16));
//             }
//         }
//         temp_f16 = (D_80085FD0 - temp_f2) * 0.5f;
//         temp_f0 = sqrtf(temp_f16);
//         temp_f18 = ((temp_f16 * (g_asinf_near1_p_old[1] + (((g_asinf_near1_p_old[3] * temp_f16) + g_asinf_near1_p_old[2]) * temp_f16)) * temp_f0) / (g_asinf_near1_q_old[0] + ((((temp_f16 + g_asinf_near1_q_old[2]) * temp_f16) + g_asinf_near1_q_old[1]) * temp_f16))) + temp_f0;
//         if (temp_v0 > 0) {
//             return D_80085FDC - (temp_f18 + temp_f18);
//         } else {
//             return temp_f18 + temp_f18 + D_80085FE4;
//         }
//     }
//     if (arg0 != arg0) { // NaN check
//         return 0.0f;
//     }
//     if (arg0 == D_80085FD0) {
//         return D_80085FDC;
//     }
//     if (arg0 == D_80085FD4) {
//         return D_80085FE4;
//     }
//     return 0.0f;
// }

/* was func_15048F20 */
void vec3_add(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk0 + arg1->unk0;
    arg2->unk4 = arg0->unk4 + arg1->unk4;
    arg2->unk8 = arg0->unk8 + arg1->unk8;
}

/* was func_15048F58 */
void vec3_sub(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk0 - arg1->unk0;
    arg2->unk4 = arg0->unk4 - arg1->unk4;
    arg2->unk8 = arg0->unk8 - arg1->unk8;
}

/* was func_15048F90 */
void vec3_diff(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg1->unk0 - arg0->unk0;
    arg2->unk4 = arg1->unk4 - arg0->unk4;
    arg2->unk8 = arg1->unk8 - arg0->unk8;
}

/* was func_15048FC8 */
f32 vec3_heading_deg(struct17 *arg0) {
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;

    tmp1 = sqrtf((arg0->unk0 * arg0->unk0) + (arg0->unk8 * arg0->unk8));
    if (tmp1 == 0.0f) {
        return 0.0f;
    }

    tmp2 = -arg0->unk0 / tmp1;
    tmp2 = math_asinf(tmp2);

    if (arg0->unk8 > 0.0f) {
        tmp2 = 270.0f - (tmp2 * g_heading_rad_to_deg_a);
    } else {
        tmp2 = 90.0f + (tmp2 * g_heading_rad_to_deg_b);
    }

    tmp2 -= 90.0f;

    if (tmp2 < 0.0f) {
        tmp2 += 360.0f;
    }
    return tmp2;
}

/* was func_150490A8 */
s32 vec3_heading_u8(struct17 *arg0) {
    f32 temp_f12;
    s32 phi_v1;

    temp_f12 = sqrtf((arg0->unk0 * arg0->unk0) + (arg0->unk8 * arg0->unk8));

    if (temp_f12 == 0.0f) {
        return 0;
    }

    temp_f12 = arg0->unk0 / temp_f12;
    phi_v1 = math_asin_u8(temp_f12);

    if (0.0f < arg0->unk8) {
        if (phi_v1 < 64) {
            phi_v1 = 128 - phi_v1;
        } else {
            phi_v1 = 384 - phi_v1;
        }
    }
    return phi_v1;
}

/* was func_15049148 */
void vec3_scale(struct17 *arg0, f32 arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk0 * arg1;
    arg2->unk4 = arg0->unk4 * arg1;
    arg2->unk8 = arg0->unk8 * arg1;
}

/* was func_1504917C */
void vec3_normalize(struct17 *arg0, struct17 *arg1) {
    f32 tmp = vec3f_magnitude(arg0);
    if (tmp != 0.0f) {
        tmp = 1.0f / tmp;
    }
    arg1->unk0 = arg0->unk0 * tmp;
    arg1->unk4 = arg0->unk4 * tmp;
    arg1->unk8 = arg0->unk8 * tmp;
}

/* was func_150491EC */
void vec3_dir_to(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg1->unk0 - arg0->unk0;
    arg2->unk4 = arg1->unk4 - arg0->unk4;
    arg2->unk8 = arg1->unk8 - arg0->unk8;
    vec3_normalize(arg2, arg2);
}
