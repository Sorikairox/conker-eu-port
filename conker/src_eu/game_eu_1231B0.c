#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void rain_update(s32);
void screen_overlay_update_alpha(u8 *arg0);
extern u8 D_800A1EE8[];
extern u8 D_800A1EF4[];
void mtx_transform_points(f32 **, f32 **, void *, s32);
extern u8 D_800A1ED0[];
extern u8 D_800A1EDC[];
extern u8 D_800A5860[];


typedef struct {
    void *u0;
    s32 u4;
    s32 u8;
    s32 uC;
    s32 u10;
    s16 u14;
    s16 u16;
    s16 u18;
    s16 pad1A;
    f32 u1C;
    f32 u20;
    s16 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s16 u2E;
    u8 u30;
    u8 u31;
    u8 u32;
    u8 u33;
    u8 u34;
    u8 u35;
    u8 u36;
    u8 u37;
    u8 u38;
    u8 u39;
    u8 pad3A[2];
} S59A0;
extern u8 D_80091CF8[];
extern u8 D_80091CE0[];
extern u8 D_80091CEC[];
extern u8 D_80091BA8[];
s32 image_fx_spawn_template(S59A0 *);
/* was func_150F59A0 */
void screen_overlay_show_timed(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    S59A0 s;
    s32 sum;

    if (arg3 != 0) {
        if (arg3 == 2) {
            s.u2C = 0xF0;
            s.u2E = 0xBA;
            s.u0 = D_80091CF8;
        } else {
            s.u2C = 0x10E;
            s.u2E = 0x7C;
            if (arg3 == 1) {
                s.u0 = D_80091CE0;
            } else {
                s.u0 = D_80091CEC;
            }
        }
        s.u30 = 9;
        s.u39 = 0x10;
        s.u28 = 0;
        s.u2A = 0;
        s.u36 = 8;
    } else {
        s.u0 = D_80091BA8;
        s.u30 = 0xA;
        s.u2C = 0xA0;
        s.u2E = 0xC0;
        s.u39 = 0x20;
        s.u28 = 0x1000;
        s.u2A = 0x1000;
        s.u36 = 0x18;
    }
    s.u8 = (arg0 << 16) | arg1;
    sum = arg0 + arg1 + arg2;
    s.uC = (arg2 << 16) | sum;
    s.u10 = 10000;
    s.u14 = sum;
    s.u18 = 0;
    s.u24 = 0;
    s.u26 = 0;
    s.u31 = 1;
    s.u32 = 0xFF;
    s.u33 = 0xFF;
    s.u34 = 0xFF;
    s.u37 = 0x11;
    s.u35 = 0;
    s.u16 = 0;
    s.u1C = 146.0f;
    s.u20 = 100.0f;
    image_fx_spawn_template(&s);
}

/* was func_150F5B10 */
void screen_overlay_update_scale(u8 *arg0) {
    s32 temp_v0 = 0x1000 - *(s16 *)(arg0 + 0x24) * 4;

    *(s16 *)(arg0 + 0x38) = temp_v0;
    *(s16 *)(arg0 + 0x3A) = *(s16 *)(arg0 + 0x38);
    screen_overlay_update_alpha(arg0);
}

/* was func_150F5B48 */
void screen_overlay_update_alpha(u8 *arg0) {
    s16 temp_t2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x1C));
    temp_a2 = (*(s32 *)((u8 *)arg0 + 0x18));
    temp_t2 = (*(s16 *)((u8 *)arg0 + 0x24));
    temp_v0 = temp_v1 & 0xFFFF;
    temp_a1 = temp_a2 >> 0x10;
    temp_t1 = temp_v0 - temp_a1;
    if (temp_t1 < temp_t2) {
        (*(s8 *)((u8 *)arg0 + 0x45)) = (s8) ((s32) ((temp_v0 - temp_t2) * 0xFF) / temp_a1);
        return;
    }
    if ((temp_t1 - (temp_a2 & 0xFFFF)) < temp_t2) {
        (*(s8 *)((u8 *)arg0 + 0x45)) = 0xFF;
        return;
    }
    (*(s8 *)((u8 *)arg0 + 0x45)) = (s8) ((s32) (temp_t2 * 0xFF) / (s32) (temp_v1 >> 0x10));
}
/* was func_150F5C0C */
void screen_overlay_on_end(s32 arg0) {
    rain_update(0);
}

extern s32 D_80090624;

/* was func_150F5C30 */
s32 model_anim_texture_frame_cb(u8 *arg0, u8 *arg1) {
    f32 temp_f2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg1 + 0x2D0));
    if (temp_v0 == NULL) {
        return 0;
    }
    var_v1 = 6;
    if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0xAE) {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 8));
        if ((temp_f2 >= 36.0f) && (temp_f2 <= 51.0f)) {
            var_v1 = (s32) (6.0f * (1.0f - ((temp_f2 - 36.0f) * 0.0625f)));
        } else if ((temp_f2 > 51.0f) && (temp_f2 <= 54.0f)) {
            var_v1 = 0;
        } else if ((temp_f2 > 54.0f) && (temp_f2 <= 60.0f)) {
            var_v1 = (s32) (6.0f * ((temp_f2 - 54.0f) * 0.14285715f));
        } else {
            if ((temp_f2 > 60.0f) && (temp_f2 <= 65.0f)) {
                var_v1_2 = (s32) (2.0f * ((temp_f2 - 60.0f) * 0.16666667f));
                goto block_30;
            }
            if ((temp_f2 > 65.0f) && (temp_f2 <= 67.0f)) {
                var_v1_2 = (s32) (2.0f * (1.0f - ((temp_f2 - 65.0f) * 0.33333334f)));
                goto block_30;
            }
            if ((temp_f2 > 67.0f) && (temp_f2 <= 70.0f)) {
                var_v1 = (s32) (2.0f * (1.0f - ((temp_f2 - 67.0f) * 0.25f))) + 4;
            } else if ((temp_f2 > 70.0f) && (temp_f2 <= 74.0f)) {
                var_v1 = (s32) (2.0f * ((temp_f2 - 70.0f) * 0.2f)) + 4;
            } else {
                if ((temp_f2 > 74.0f) && (temp_f2 <= 119.0f)) {
                    var_v1_2 = (s32) (2.0f * ((temp_f2 - 74.0f) * 0.02173913f));
                    goto block_30;
                }
                if ((temp_f2 > 119.0f) && (temp_f2 <= 150.0f)) {
                    var_v1_2 = (s32) (2.0f * (1.0f - ((temp_f2 - 119.0f) * 0.03125f)));
block_30:
                    var_v1 = var_v1_2 + 7;
                }
            }
        }
    }
    (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) *(s32 *)((u8 *)&D_80090624 + (var_v1 * 4));
    return 0;
}
/* P204 */
// model_tile_fade_cb: model-node callback (D_800845xx table, s32 (u8 *, u8 *)) for node n of the character pl:
// does nothing while pl +0x2D0 is NULL. State n +0x38: 0 = start (becomes 1 once pl +0x84 is 5, else the tile is
// reset to t 2), 1 = shown (fade 1), 2 = gone (fade 0). While pl +0x84 is 5 the fade follows the height
// (+0x2D0)->+8: 1 below 69, 0 above 84 (state 2), linear in between. The first G_SETTILESIZE of the node's
// display list (*(n +0x24)) gets ult = 44 + 58 * fade (uls 2). Returns 0.
// Rare leaves the fade uninitialised for a state other than 0..2 when pl +0x84 is not 5 (asm: a stack slot); 0 here.
/* was func_150F5FD4 */
s32 model_tile_fade_cb(u8 *n, u8 *pl) {
    u8 *ref = *(u8 **) (pl + 0x2D0);
    Gfx *dl;
    s32 reset;
    f32 fade = 0.0f;
    f32 y;
    s32 i;
    s32 t;

    if (ref == NULL) {
        return 0;
    }
    dl = **(Gfx ***) (n + 0x24);
    reset = FALSE;
    switch (*(s32 *) (n + 0x38)) {
        case 0:
            if (*(u16 *) (pl + 0x84) == 5) {
                *(s32 *) (n + 0x38) = 1;
                fade = 1.0f;
            } else {
                reset = TRUE;
            }
            break;
        case 1:
            fade = 1.0f;
            break;
        case 2:
            fade = 0.0f;
            break;
    }
    if (*(u16 *) (pl + 0x84) == 5) {
        y = *(f32 *) (ref + 8);
        if (y < 69.0f) {
            fade = 1.0f;
        } else if (y > 84.0f) {
            fade = 0.0f;
            *(s32 *) (n + 0x38) = 2;
        } else {
            fade = 1.0f - (y - 69.0f) / 15.0f;
        }
    }
    for (i = 0; (s8) (dl[i].words.w0 >> 24) != (s8) G_SETTILESIZE; i++) {
    }
    if (reset) {
        t = 2;
    } else {
        t = (s32) (58.0f * fade + 44.0f);
    }
    dl[i].words.w0 = (G_SETTILESIZE << 24) | (2 << 12) | (t & 0xFFF);
    return 0;
}

/* was func_150F6188 */
void obj_bone_glow_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = effect_node_create(arg1, -1, 0x51, -1, 1, 0x3E, 0xC, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

s32 particle_spawn_ex(s32 *, s32, s32, s32, s32, s32);

/* was func_150F6218 */
void obj_bone_glow_emitter_update(u8 *arg0) {
    struct {
        f32 * u98;
        f32 * u9C;
        s32 * uA0;
        s32 * uA4;
        u8 padA8[0xC];
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        s32 uD0;
        s32 uD4;
        s16 uD8;
        s16 uDA;
        s32 uDC;
        s32 uE0;
        s8 uE4;
        s8 uE5;
        s8 uE6;
        s8 uE7;
        s8 uE8;
        s8 uE9;
        s8 uEA;
        s8 uEB;
        s8 uEC;
        s8 uED;
        s16 uEE;
        s16 uF0;
        s16 uF2;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        s32 u10C;
        u8 pad110[0x8];
        f32 u118;
        f32 u11C;
        f32 u120;
        f32 u124;
        s32 u128;
        s32 u12C;
        s8 u130;
        s8 u131;
        s8 u132;
        s8 u133;
        s8 u134;
        s8 u135;
        s8 u136;
        u8 pad137[0x1];
        s16 u138;
        u8 pad13A[0x2];
        f32 u13C;
    } sp;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    s16 temp_v1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_t8;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s1 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s0 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if ((*(s32 *)((u8 *)temp_s0 + 0x1D4)) != 0) {
        (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((0.26000002f + (random_float() * 0.19500001f)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f) {
            sp.uE4 = 0xFF;
            sp.uE5 = 0xFF;
            sp.uE6 = 0xFF;
            sp.uE8 = 0xB4;
            sp.uE9 = 0xB4;
            sp.uEA = 0xB4;
            sp.uA0 = ((u8 *)&D_800A1ED0);
            sp.uA4 = ((u8 *)&D_800A1EDC);
            sp.u98 = &sp.uC0;
            sp.u9C = &sp.uB4;
            mtx_transform_points(&sp.uA0, &sp.u98, (*(s32 *)((u8 *)temp_s0 + 0x1D4)) + 0x140, 2);
            temp_t8 = ((u8 *)&D_800A5860);
            sp.uED = 0x6C;
            sp.uD8 = 0x5103;
            sp.uD0 = 0x200005;
            sp.uD4 = 0x9F0600;
            sp.uDC = 0;
            sp.uE0 = 0;
            sp.uE7 = 0xFF;
            sp.uEC = 0xFF;
            (*(s32 *)((u8 *)(&sp.u10C) + 0)) = (s32) (*(s32 *)((u8 *)temp_t8 + 0));
            (*(s32 *)((u8 *)(&sp.u10C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
            (*(s32 *)((u8 *)(&sp.u10C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
            sp.u128 = 0x84CE07;
            sp.u130 = 8;
            sp.u131 = 6;
            sp.u132 = 0x10;
            sp.u133 = -1;
            sp.u134 = -1;
            sp.u135 = 0;
            sp.u12C = 0;
            sp.u136 = 0xFF;
            sp.u138 = 0x3E8;
            sp.u13C = 1000.0f;
            sp.uCC = 0.973034f;
            sp.uF4 = 1.022472f;
            do {
                temp_v1 = (random_int() % 21U) + 0x14;
                sp.uF2 = temp_v1;
                sp.uEE = temp_v1;
                sp.uF0 = (s16) (0xFF / temp_v1);
                sp.uDA = temp_v1;
                sp.uEB = (random_int() % 26U) + 8;
                temp_f2 = (random_float() * 70.0f) + 148.0f;
                sp.uF8 = temp_f2;
                sp.uFC = temp_f2;
                sp.u124 = (random_float() * 0.21900001f) + 0.086f;
                temp_f2_2 = (random_float() * 0.041f) + 0.078f;
                sp.u118 = (sp.uB4 - sp.uC0) * temp_f2_2;
                sp.u11C = (sp.uB8 - sp.uC4) * temp_f2_2;
                sp.u120 = (sp.uBC - sp.uC8) * temp_f2_2;
                temp_f2_3 = random_float() * D_800BE9A4;
                sp.u128 &= ~0xC0;
                sp.u100 = (sp.u118 * temp_f2_3) + sp.uC0;
                sp.u104 = (sp.u11C * temp_f2_3) + sp.uC4;
                sp.u108 = (sp.u120 * temp_f2_3) + sp.uC8;
                var_s0 = 0;
                if (random_int() & 1) {
                    var_s0 = 0x80;
                }
                if (random_int() & 1) {
                    var_v0 = 0x40;
                } else {
                    var_v0 = 0;
                }
                sp.u128 |= var_v0 | var_s0;
                temp_v0 = particle_spawn_ex(&sp.uD0, 1, 0, 4, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0 != 0) {
                    memcpy(temp_v0 + 0xA8, &sp.uCC, 4);
                }
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f);
        }
    }
}
/* was func_150F66B8 */
void obj_bone_glow_emitter_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    effect_node_link_message(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

void mtx_transform_points(f32 **, f32 **, void *, s32);

/* was func_150F66F8 */
void obj_bone_fx_pair_update(u8 *arg0) {
    struct {
        f32 * u38;
        s32 * u3C;
        s32 * u40;
        s32 * u44;
        s32 u48;
        u8 pad4C[0x8];
        f32 u54;
        f32 u58;
        f32 u5C;
    } sp;
    u8 *sp1C;
    s32 temp_v1_3;
    s32 temp_v1_5;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_4;
    u8 *var_t0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x28));
    var_t0 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)var_t0 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if (((*(s32 *)((u8 *)temp_v0 + 0x1D4)) != 0) && !((*(s32 *)((u8 *)temp_v0 + 0x94)) & 2)) {
        sp.u40 = ((u8 *)&D_800A1EE8);
        sp.u44 = ((u8 *)&D_800A1EF4);
        sp.u38 = &sp.u54;
        sp.u3C = &sp.u48;
        sp1C = var_t0;
        mtx_transform_points(&sp.u40, &sp.u38, (*(s32 *)((u8 *)temp_v0 + 0x1D4)), 2);
        var_t0 = sp1C;
        temp_v1 = (*(u8 **)((u8 *)var_t0 + 8));
        if (temp_v1 != NULL) {
            (*(u8 *)((u8 *)temp_v1 + 0x168)) = (u8) ((*(u8 *)((u8 *)temp_v1 + 0x168)) | 1);
            (*(f32 *)((u8 *)temp_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)(&sp.u54) + 0));
            (*(s32 *)((u8 *)temp_v1 + 0x38)) = (s32) (*(s32 *)((u8 *)(&sp.u54) + 4));
            (*(s32 *)((u8 *)temp_v1 + 0x3C)) = (s32) (*(s32 *)((u8 *)(&sp.u54) + 8));
            (*(s32 *)((u8 *)temp_v1 + 0x40)) = (s32) (*(s32 *)((u8 *)(&sp.u48) + 0));
            (*(s32 *)((u8 *)temp_v1 + 0x44)) = (s32) (*(s32 *)((u8 *)(&sp.u48) + 4));
            (*(s32 *)((u8 *)temp_v1 + 0x48)) = (s32) (*(s32 *)((u8 *)(&sp.u48) + 8));
        }
        temp_v1_2 = (*(u8 **)((u8 *)var_t0 + 0xC));
        if (temp_v1_2 != NULL) {
            temp_v0_2 = (*(u8 **)((u8 *)temp_v1_2 + 0x14));
            (*(s8 *)((u8 *)temp_v0_2 + 9)) = 0;
            (*(s16 *)((u8 *)temp_v0_2 + 0xE)) = (s16) (s32) sp.u54;
            (*(s16 *)((u8 *)temp_v0_2 + 0x10)) = (s16) (s32) sp.u58;
            (*(s16 *)((u8 *)temp_v0_2 + 0x12)) = (s16) (s32) sp.u5C;
        }
    } else {
        temp_v1_3 = (*(s32 *)((u8 *)var_t0 + 8));
        temp_v0_3 = temp_v1_3 + 0x110;
        if (temp_v1_3 != 0) {
            (*(u8 *)((u8 *)temp_v0_3 + 0x58)) = (u8) ((*(u8 *)((u8 *)temp_v0_3 + 0x58)) & 0xFFFE);
        }
        temp_v1_4 = (*(u8 **)((u8 *)var_t0 + 0xC));
        if (temp_v1_4 != NULL) {
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v1_4 + 0x14))) + 9)) = 1;
        }
    }
    temp_v1_5 = (*(s32 *)((u8 *)var_t0 + 8));
    if (temp_v1_5 != 0) {
        temp_v0_4 = temp_v1_5 + 0x110;
        (*(f32 *)((u8 *)temp_v0_4 + 0x48)) = 4.0f;
        (*(f32 *)((u8 *)temp_v0_4 + 0x4C)) = 8.0f;
    }
}
/* was func_150F689C */
void obj_bone_fx_pair_destroy_children(u8 *arg0) {
    struct102 *temp_a0;

    if (*(s32 *)(arg0 + 0x30) != 0) {
        node_destroy(*(struct102 **)(arg0 + 0x30));
    }
    temp_a0 = *(struct102 **)(arg0 + 0x34);
    if (temp_a0 != NULL) {
        node_destroy(temp_a0);
    }
}

/* was func_150F68E8 */
void obj_bone_fx_pair_retire(void *arg0) {
    obj_bone_fx_pair_destroy_children(arg0);
    effect_node_retire(arg0);
}

/* was func_150F6914 */
void obj_bone_fx_pair_free(void *arg0) {
    obj_bone_fx_pair_destroy_children(arg0);
    effect_node_free(arg0);
}

/* was func_150F6940 */
void obj_bone_fx_pair_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

/* was func_150F6980 */
void obj_bone_fx_child_detach(u8 *arg0)
{
  int new_var;
  s32 *new_var3;
  int new_var2;
  new_var3 = &(*((s32 *) (((u8 *) arg0) + 0x160)));
  if ((*((s32 *) (((u8 *) arg0) + 0x160))) != 0)
  {
    new_var = 0x28;
    *((s32 *) (((u8 *) (new_var2 = (*new_var3) + new_var)) + 8)) = 0;
  }
}

/* was func_150F69A0 */
void obj_bone_fx_child_retire(void *arg0) {
    obj_bone_fx_child_detach(arg0);
    effect3d_retire(arg0);
}

/* was func_150F69CC */
void obj_bone_fx_child_free(void *arg0) {
    obj_bone_fx_child_detach(arg0);
    effect3d_free(arg0);
}

/* was func_150F69F8 */
void obj_bone_fx_light_detach(s32 arg0) {
}

/* was func_150F6A04 */
void obj_bone_fx_light_retire(void *arg0) {
    obj_bone_fx_light_detach(arg0);
    effect_free_buffers_retire(arg0);
}

/* was func_150F6A30 */
void obj_bone_fx_light_free(void *arg0) {
    obj_bone_fx_light_detach(arg0);
    effect_free_buffers_delete(arg0);
}

s32 object_arc_from_point_spawn(u8 *, s32, f32 *, s16, s32, s32, s32, f32, f32, s32, s32, u8 *, u8, u8);
extern f32 D_800A1F00[];

typedef struct {
    u8 *o;
    u8 id;
    u8 pad5;
    s16 t6;
} Sub6A5C;

/* was func_150F6A5C */
void obj_electric_zap_emitter_update(u8 *arg0) {
    Sub6A5C *s;
    u8 *obj;
    s8 n;
    f32 pos[3];
    Header header;
    Header2 header2;
    u8 col[4];

    s = (Sub6A5C *)(arg0 + 0x28);
    obj = s->o;
    if ((*(s32 *)obj == 0) || (s->id != obj[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if ((*(s32 *)(obj + 0x1D4) != 0) && !(*(s32 *)(obj + 0x94) & 2)) {
        s->t6 -= D_800BE9E4;
        if (s->t6 < 0) {
            sound_play_at(0x679, 0x18CE, 0, 0, 0, *(f32 *)(obj + 0x14), *(f32 *)(obj + 0x18), *(f32 *)(obj + 0x1C), 0x7918, 0x7D00);
            n = (random_int() & 1) + 2;
            goto lbl; // fakematch: scheduling barrier (permuter)
            lbl:
            mtx_transform_point_or_origin(D_800A1F00, pos, *(u8 **)(obj + 0x1D4));
            header.unk0 = 3;
            header.unk1 = -1;
            header.unk2 = (random_int() % 9U) + 0xA;
            header.unk4 = 0;
            header2.unk0 = pos[0];
            header2.unk4 = pos[1];
            header2.unk8 = pos[2];
            light_create_with_ctrl(&header, &header2, (random_int() % 61U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0[0xC], arg0[1]);
            do {
                col[0] = 0xA0;
                col[1] = 0xA0;
                col[2] = 0xFF;
                col[3] = (random_int() % 101U) + 0x9B;
                object_arc_from_point_spawn(obj, 0, D_800A1F00, random_int() & 0xFF, (random_int() % 43U) - 0x32, (random_int() % 18U) + 5, 4, 27.0f, (random_float() * 16.0f) + 20.0f, 0, 2, col, arg0[0xC], arg0[1]);
                n--;
            } while (n > 0);
            s->t6 = (random_int() % 91U) + 0x5A;
        }
    }
}

/* was func_150F6DD0 */
void obj_electric_zap_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

extern f32 D_800A1F40;
s32 bone_emitter_spawn(void *, s32, u8 *, s16);

/* was func_150F6E10 */
void obj_bone_spark_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, u8 arg3) {
    struct {
        u8 u2C;
        u8 *u30;
        u8 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        u8 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        u8 u5A;
        u8 u5B;
        s8 u5C;
        f32 u60;
        u8 u64;
        s8 u65;
    } sp;

    sp.u2C = arg0[0x3B];
    sp.u30 = arg0;
    sp.u34 = 3;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    sp.u40 = 0.0f;
    sp.u44 = 0.0f;
    sp.u50 = 2;
    sp.u52 = 0x28;
    sp.u54 = 0x10;
    sp.u56 = arg1;
    sp.u5A = 5;
    sp.u5B = 8;
    sp.u5C = -1;
    sp.u64 = 0;
    sp.u65 = -1;
    sp.u58 = 0;
    sp.u48 = D_800A1F40;
    sp.u4C = 8.5f;
    sp.u60 = 1.0f;
    bone_emitter_spawn(&sp, 0, arg0, arg1);
}

void bone_emitter_spark_params(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5, f32 *arg6, f32 *arg7, f32 *arg8,
                   f32 *arg9, s16 *argA, u8 *argB, f32 *argC);
void hitinfo_from_obj_floor(void *, u8 *);

// spark_burst_spawn: effect handler of the bone_emitter_dust_emit table (`void (f32 *, f32 *, f32 *, f32 *, f32, u8 *)`):
// bone_emitter_spark_params turns the inputs into a position / direction / size / angle / alpha; the size is scaled by
// 1..3 (random). With chance 0.6 the particle gets a floor record from hitinfo_from_obj_floor for the object (+0x1C) and
// then bounces with chance 0.5; otherwise the record says "no floor" (height -10000). Spawned by impact_dust_cloud_spawn
// with gravity 1.8, the effect's colour (+0xC) and layer (+1) bytes.
/* was func_150F6EDC */
void fx_bone_spark_dust_spawn(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5) {
    struct {
        f32 floor_y;
        s32 unk4[5];
        s32 unk18;
        u8 unk1C;
        u8 unk1D;
        s32 unk20;
    } floor;
    f32 pos[3];
    f32 unused[3];
    f32 dir[3];
    f32 speed;
    s16 angle;
    u8 alpha;
    f32 size;
    u8 hit;
    u8 bounce;
    f32 r;

    bone_emitter_spark_params(arg0, arg1, arg2, arg3, arg4, arg5, pos, unused, dir, &speed, &angle, &alpha, &size);
    r = random_float();
    size *= 1.0f + (r + r);
    hit = (random_float() < 0.6f) ? 1 : 0;
    if (hit) {
        hitinfo_from_obj_floor(&floor, *(u8 **) (arg5 + 0x1C));
    } else {
        floor.unk18 = 0;
        floor.unk1C = 0;
        floor.unk1D = 0;
        floor.unk20 = 0;
        floor.floor_y = -10000.0f;
    }
    bounce = 0;
    if (hit) {
        if (random_float() < 0.5f) {
            bounce = 1;
        }
    }
    impact_dust_cloud_spawn(pos, dir, 1, speed, angle, alpha, size, hit, 1.8f, 1.8f, 1, (s32) &floor, 1, bounce, arg5[0xC],
                  arg5[1]);
}
