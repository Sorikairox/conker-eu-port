#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
s32 memcpy(s32, void *, s32);


void hitinfo_from_obj_floor(void *, u8 *);
void vec3_from_angles_byte(s16, s16, f32, void *);
void obj_get_fx_point_b(u8 *, f32 *, f32 *, f32 *);

/* was func_150CF650 */
void obj_dust_emitter_update(u8 *arg0) {
    struct {
        f32 uBC;
        u8 padC0[0x8];
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s32 uDC;
        u8 padE0[0x20];
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
    } sp;
    f32 temp_f20;
    s16 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s1;
    u8 *temp_s0;
    u8 *temp_s2;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s2 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s2 + 4)) != (*(u8 *)((u8 *)temp_s0 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if ((*(s32 *)((u8 *)temp_s0 + 0x1D4)) != 0) {
        (*(f32 *)((u8 *)temp_s2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 8)) + ((0.06f + (random_float() * 0.0704f)) * D_800BE9A4));
        obj_get_fx_point_b(temp_s0, &sp.u104, &sp.uD8, &sp.uD4);
        sp.u100 = (sp.uD8 + sp.uD4) * 0.5f;
        hitinfo_from_obj_floor(&sp.uDC, temp_s0);
        if ((*(f32 *)((u8 *)temp_s2 + 8)) > 1.0f) {
            do {
                temp_s0_2 = random_int() & 0xFF;
                vec3_from_angles_byte(temp_s0_2, (s16) ((random_int() % 76U) - 0x40), sp.u100, &sp.uC8);
                sp.uC8 += sp.u104;
                sp.uCC += sp.u108;
                sp.uD0 += sp.u10C;
                temp_s0_3 = random_int();
                vec3_from_angles_byte(temp_s0_2, (s16) (((u32) temp_s0_3 % 54U) - 0x38), (random_float() * 1.4430001f) + 2.2680001f, &sp.uBC);
                temp_f20 = random_float();
                temp_s1 = random_int();
                temp_s0_4 = random_int();
                impact_dust_cloud_spawn(&sp.uC8, &sp.uBC, 5U, (temp_f20 * 0.286f) + -0.78700006f, (s16) (((u32) temp_s1 % 21U) + 0x1E), (u8) (((u32) temp_s0_4 % 156U) + 0x64), (random_float() * 50.0f) + 48.0f, 1U, 1.0f, 1.0f, 0U, (s32) &sp.uDC, 1U, 0U, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s2 + 8)) > 1.0f);
        }
    }
}
/* was func_150CF994 */
void obj_dust_emitter_handle_event(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            node_destroy(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
    }
}

void ground_fx_spawn_random(struct127 *, f32, f32); /* P95: f32 parameter */

/* was func_150CFA40 */
void ground_fx_spawn_above_player(s32 arg0) {
    ground_fx_spawn_random(g_objects, g_objects->y_position + 300.0f, -10000.0f); /* P95: float literal (asm passes the bits 0xC61C4000) */
}

extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
/* was func_150CFA88 */
void tex_scroll_step_offsets(s32 arg0) {
    s32 temp_v1;
    D_80088C30 += D_800BE9E4 * 0x1A;
    temp_v1 = D_800BE9E4 * 0x1C;
    D_80088C34 -= temp_v1;
    D_80088C38 -= temp_v1;
}

extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
extern s32 D_80088C3C;

/* was func_150CFAF8 */
Gfx *tex_scroll_set_tile_sizes(Gfx *gdl) {
    gDPSetTileSize(gdl++, 0, D_80088C30 >> 7, D_80088C34 >> 7, 0x47E, 0x47E);
    gDPSetTileSize(gdl++, 1, D_80088C38 >> 7, D_80088C3C >> 7, 0x47E, 0x47E);
    return gdl;
}

s32 sprite2d_spawn(s32 *, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x11 */ u8 pad11;
    /* 0x12 */ s16 span;
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ u8 u1A;
    /* 0x1B */ u8 col[9];
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ s32 u2C;
    /* 0x30 */ s32 u30;
    /* 0x34 */ s32 u34;
    /* 0x38 */ s32 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ u8 player;
    /* 0x45 */ u8 pad45[3];
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpawnSpecCFB90; // size 0x58

typedef struct {
    u8 u0;
    u8 pad1[3];
    f32 u4;
    f32 u8;
    f32 uC;
} SpawnExtraCFB90; // copied to the record's +0x70

// screen_bar_spawn: spawns effect kind 0xC1 at (-300, 72), scale 7.5, with `span` at +0x12 (+0x14 = 0x31, white
// colour bytes, flags 0x200004 / 0x9F0601 and fixed defaults, current player D_80082FA0) through sprite2d_spawn (list
// 0xC, `flag`, `arg2`) and copies the extra block (0, 0, -300, 0) to the new record's +0x70.
/* was func_150CFB90 */
void screen_bar_spawn(s16 span, u8 flag, s32 arg2) {
    SpawnExtraCFB90 extra;
    SpawnSpecCFB90 spec;
    s32 rec;
    s32 i;

    extra.u0 = 0;
    extra.u4 = 0.0f;
    extra.u8 = -300.0f;
    extra.uC = 0.0f;
    spec.x = -300.0f;
    spec.y = 72.0f;
    spec.scaleA = 7.5f;
    spec.scaleB = 7.5f;
    spec.kind = 0xC1;
    spec.span = span;
    spec.u14 = 0x31;
    spec.u16 = 1;
    spec.u18 = 0xFF;
    spec.u1A = 8;
    for (i = 0; i < 9; i++) {
        spec.col[i] = 0xFF;
    }
    spec.u24 = 0;
    spec.u28 = 0x200004;
    spec.u2C = 0x9F0601;
    spec.u30 = 0x17;
    spec.u34 = 0x44;
    spec.u38 = 0x80;
    spec.u3C = 0x20;
    spec.u40 = 0;
    spec.u41 = 0xA;
    spec.player = D_80082FA0;
    spec.u48 = 1.0f;
    spec.u4C = 1.0f;
    spec.u50 = 0.0f;
    spec.u54 = 0.0f;
    rec = sprite2d_spawn((s32 *) &spec, 0xC, 0, 0, 0x10, flag, arg2);
    if (rec != 0) {
        memcpy(rec + 0x70, &extra, 0x10);
    }
}

void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
s32 sprite2d_spawn(s32 *, s32, s32, s32, s32, s32, s32);
extern s32 g_impact_dust_tex_fns; /* was D_80090070 */

/* was func_150CFD10 */
s32 screen_bar_update_burst(u8 *arg0) {
    struct {
        s32 u9C;
        s32 uA0;
        f32 uA4;
        f32 uA8;
        s32 uAC;
        u8 padB0[0x4];
        f32 uB4;
        f32 uB8;
        s8 uBC;
        u8 padBD[0x1];
        s16 uBE;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s8 uC6;
        s8 uC7;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        s8 uCD;
        s8 uCE;
        s8 uCF;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s32 uE0;
        s32 uE4;
        s32 uE8;
        s8 uEC;
        s8 uED;
        u8 padEE[0x2];
        s8 uF0;
        u8 padF1[0x3];
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
    } sp;
    u8 *sp84;
    f32 temp_f2;
    f32 var_f0;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s8 temp_t0;
    s8 temp_v1;
    s8 var_s2;
    u8 *var_v0;

    if ((*(u8 *)((u8 *)arg0 + 0x70)) & 1) {
        var_v0 = arg0 + 0x70;
        (*(f32 *)((u8 *)var_v0 + 4)) = (f32) ((*(f32 *)((u8 *)var_v0 + 4)) + (0.19000001f * D_800BE9A4));
        var_f0 = (*(f32 *)((u8 *)var_v0 + 4));
        if (var_f0 >= 1.0f) {
            (*(f32 *)((u8 *)var_v0 + 4)) = 1.0f;
            (*(u8 *)((u8 *)var_v0 + 0)) = (u8) ((*(u8 *)((u8 *)var_v0 + 0)) & 0xFFFE);
            sp84 = var_v0;
            temp_v1 = (random_int() & 3) + 2;
            temp_t0 = temp_v1;
            sp.uA8 = (*(f32 *)((u8 *)arg0 + 0x14)) + 15.0f;
            var_s2 = temp_t0;
            (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
            (*(f32 *)((u8 *)(&sp.uAC) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
            sp.uCD = 0xFF;
            sp.uC2 = 0xC;
            sp.uC4 = 0x15;
            sp.uCE = 0xFF;
            sp.uC7 = 0xFF;
            sp.uC8 = 0xFF;
            sp.uC9 = 0xFF;
            sp.uCB = 0xFF;
            sp.uCC = 0xFF;
            sp.uCF = 0xFF;
            sp.uC6 = 0;
            sp.uD0 = 0;
            sp.uD4 = 0x200004;
            sp.uD8 = 0x9F0601;
            sp.uEC = 0;
            sp.uED = 0xA;
            sp.uDC = 0x17;
            sp.uE0 = 0x44;
            sp.uE4 = 0x80;
            sp.uE8 = 0x20;
            sp.uF4 = 1.0f;
            sp.uF8 = 1.0f;
            sp.u100 = 0.0f;
            sp.uFC = 0.0f;
            sp.uF0 = (s8) D_80082FA0;
            if (temp_v1 > 0) {
                do {
                    sp.uCA = (random_int() % 101U) + 0x9B;
                    sp.uBC = (*(s8 (**)())((u8 *)(&g_impact_dust_tex_fns) + 8))();
                    temp_s0 = random_int();
                    vec2_from_angle_byte((s16) (((u32) temp_s0 % 65U) - 0xA0), (random_float() * 2.0f) + 2.5f, &sp.u9C, &sp.uA0);
                    sp.uA4 = (random_float() * 0.333f) + 0.404f;
                    temp_f2 = (random_float() * 1.79f) + 1.6999999f;
                    sp.uB4 = temp_f2;
                    sp.uB8 = temp_f2;
                    sp.uBE = (random_int() % 26U) + 0x1E;
                    var_s1 = 0;
                    if (random_int() & 1) {
                        var_s1 = 2;
                    }
                    if (random_int() & 1) {
                        var_s0 = 4;
                    } else {
                        var_s0 = 0;
                    }
                    sp.uC0 = var_s0 | 1 | var_s1 | 0x38;
                    temp_v0 = sprite2d_spawn(&sp.uAC, 0xD, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                    if (temp_v0 != 0) {
                        memcpy(temp_v0 + 0x70, &sp.u9C, 0x10);
                    }
                    var_s2 -= 1;
                } while (var_s2 > 0);
            }
            var_v0 = sp84;
            var_f0 = (*(f32 *)((u8 *)var_v0 + 4));
        }
        (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) ((*(f32 *)((u8 *)var_v0 + 8)) + (var_f0 * (*(f32 *)((u8 *)var_v0 + 0xC))));
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((sinf((*(f32 *)((u8 *)var_v0 + 4)) * 3.1415927f) * -17.5f) + 72.0f);
    }
    return 1;
}
/* was func_150D00FC */
void bouncing_sprite_handle_drop(u8 *arg0, f32 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if (arg2 == 0x52) {
        temp_v0[0] |= 1;
        *(f32 *)(temp_v0 + 4) = 0.0f;
        *(f32 *)(temp_v0 + 8) = *(f32 *)(arg0 + 0x10);
        *(f32 *)(temp_v0 + 0xC) = *arg1 - *(f32 *)(arg0 + 0x10);
    }
}

/* was func_150D0148 */
void bouncing_sprites_broadcast_drop(f32 arg0) {
    f32 sp1C = arg0;
    sprite2d_broadcast(&sp1C, 0x52);
}

/* was func_150D0170 */
s32 bouncing_sprite_update(u8 *arg0) {
    f32 *v = (f32 *)(arg0 + 0x70);

    *(f32 *)(arg0 + 0x10) += v[0] * D_800BE9A4;
    *(f32 *)(arg0 + 0x14) += v[1] * D_800BE9A4 + 0.5f * v[2] * D_800BE9A4 * D_800BE9A4;
    v[1] += v[2] * D_800BE9A4;
    if (v[3] < *(f32 *)(arg0 + 0x14)) {
        *(f32 *)(arg0 + 0x14) = v[3];
        v[0] *= 0.3f;
        v[1] = fabsf(v[1]) * -0.15f;
    }
    return 1;
}

/* was func_150D0230 */
u8 *text_find_line_end(u8 *arg0) {
    while ((*arg0 != 0xBD) && (*arg0 != 0)) {
        arg0++;
    }
    return arg0;
}

/* was func_150D026C */
u8 *text_find_string_end(u8 *arg0) {
    while (*arg0 != 0) {
        arg0++;
    }
    return arg0;
}

/* was func_150D0294 */
s32 text_line_length(u8 *arg0, u8 **arg1) {
    u8 *temp_v0 = text_find_line_end(arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}

/* was func_150D02C8 */
s32 text_max_line_length(u8 *arg0)
{
  u8 *end;
  s32 best = 0;
  u8 *next;
  end = text_find_string_end(arg0);
  while (arg0 < end) {
    s32 v;
    v = text_line_length(arg0, &next);
    if (best < v) {
      best = v;
    }
    arg0 = next + 1;
  }
  return best;
}

s32 memcpy(s32, void *, s32);
/* was func_150D034C */
void text_pager_copy_line(u8 *arg0)
{
  u8 *p = arg0;
  u8 *q;
  memcpy(*((s32 *) ((p + ((*((u8 *) (p + 0x3D))) << 2)) + ((0, 0x40)))), *((void **) (p + 0x34)), *((u8 *) (p + 0x3C)));
  q = p + 0x28;
  p = q;
  *((*((u8 **) ((p + ((*((u8 *) (p + 0x15))) << 2)) + 0x18))) + (*((u8 *) (p + 0x14)))) = 0;
}

/* was func_150D03A8 */
void text_pager_next_line(u8 *arg0) {
    u8 *v = arg0 + 0x28;

    if (**(u8 **)(arg0 + 0x38) != 0) {
        *(u8 **)(v + 0xC) = *(u8 **)(v + 0x10) + 1;
        *(u8 *)(v + 0x14) = text_line_length(*(u8 **)(v + 0xC), (u8 **)(v + 0x10));
        *(u8 *)(v + 0x15) = *(u8 *)(v + 0x15) ^ 1;
        text_pager_copy_line(arg0);
        *(u8 *)(v + 8) = *(u8 *)(v + 8) | 1;
    }
}

s32 text_max_line_length(u8 *);
void text_pager_copy_line(u8 *);
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s8 unk8;
    /* 0x0C */ u8 *unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
    /* 0x18 */ u8 *unk18;
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ s8 unk24;
    /* 0x25 */ u8 unk25;
} struct150D0420; /* size 0x28 */

/* was func_150D0420 */
u8 *text_pager_spawn(u8 arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct150D0420 sp40;
    u8 *sp3C;
    s32 sp38;
    struct150D0420 *dst;
    s32 n;

    sp40.unk15 = 0;
    sp40.unk8 = 1;
    sp40.unk4 = (u8 *)arg1;
    sp40.unkC = (u8 *)arg1;
    sp40.unk25 = (u8)arg5;
    sp40.unk24 = (s8)arg4;
    sp40.unk0 = arg0;
    sp40.unk14 = text_line_length((u8 *)arg1, &sp40.unk10);
    sp40.unk18 = NULL;
    sp40.unk1C = NULL;
    sp40.unk20 = NULL;
    n = text_max_line_length((u8 *)arg1);
    sp38 = n + 1;
    sp3C = (u8 *)effect_node_create(arg2, -1, -1, 5, 3, 0x47, (struct37 *)(arg3 + n * 2 + 0x2A), arg6, arg7);
    if (sp3C != NULL) {
        dst = (struct150D0420 *)(sp3C + 0x28);
        memcpy((s32)dst, &sp40, sizeof(struct150D0420));
        dst->unk20 = (u8 *)dst + 0x28;
        dst->unk18 = dst->unk20 + arg3;
        dst->unk1C = dst->unk18 + sp38;
        *dst->unk18 = 0;
        *dst->unk1C = 0;
        text_pager_copy_line(sp3C);
    }
    return sp3C;
}
extern s32 D_80088C40[];

/* was func_150D0544 */
s32 text_pager_update(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *v = arg1 + 0x28;

    if ((*(s8 *)(arg1 + 0x4C) != -1) && (((s32 (**)(u8 *))D_80088C40)[*(volatile s8 *)(arg1 + 0x4C)](arg1) == 0)) { // fakematch: volatile forces the second lb of the index, v defined first so addiu is rematerialised
        *(s16 *)(arg1 + 0xE) = -1;
        return arg0;
    }
    *(u8 *)(v + 8) &= 0xFFFE;
    return arg0;
}

extern void (*D_80088C50[])(u8 *, u8 *, u8);
void text_pager_next_line(u8 *);
/* was func_150D05D0 */
void text_pager_handle_event(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (arg2 == 0x51) {
        if (arg0[0x28] == arg1[0]) {
            text_pager_next_line(arg0);
        }
    } else {
        f = D_80088C50[arg0[0x4D]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

u8 *text_pager_spawn(u8, s32, s16, s32, s32, s32, u8, s32);
s32 memcpy(s32, void *, s32);
/* was func_150D0644 */
void text_pager_spawn_caption(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s32 sfpad;
    s8 sp30[4];
    u8 *temp_v0;
    sp30[0] = 0;
    temp_v0 = text_pager_spawn(arg0, arg1, arg2, 8, 0, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0 + 0x48)), sp30, 1);
    }
}
