#include <ultra64.h>
#include "functions.h"
#include "variables.h"

const char rodata_pre_193D00[] = "\xff"; // fakematch: unreferenced leading rodata word


/* was func_151664F0 */
void water_ring_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8)
{
  s32 i;
  u8 *temp_v0;
  temp_v0 = node_alloc(4, arg8, 0xA8, 1, (u8) ((s32) arg7), 1U);
  if (temp_v0 != 0)
  {
    if (arg0 == (-1))
    {
      for (i = 0; i != 2; i++)
      {
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x12)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x22)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x32)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x42)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x16)) = 0;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x26)) = 0;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x36)) = 0;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x46)) = 0;
      }

      *((s8 *) (((u8 *) temp_v0) + 0x95)) = 0;
    }
    else
    {
      *((s8 *) (((u8 *) temp_v0) + 0x91)) = (s8) ((s32) (sinf(((f32) arg0) * 0.017453292f) * 127.0f));
      i = (s32) ((-cosf(((f32) arg0) * 0.017453292f)) * 127.0f);
      *((s8 *) (((u8 *) temp_v0) + 0x90)) = (s8) i;
      *((s8 *) (((u8 *) temp_v0) + 0x95)) = 1;
    }
    for (i = 0; i != 2; i++)
    {
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x18)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x1A)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x28)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x2A)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x38)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x3A)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x48)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x4A)) = 0x2800;
    }

    *((s16 *) (((u8 *) temp_v0) + 0x9A)) = arg2;
    *((s16 *) (((u8 *) temp_v0) + 0x9E)) = 1;
    *((s8 *) (((u8 *) temp_v0) + 0x92)) = (s8) arg5;
    *((s8 *) (((u8 *) temp_v0) + 0x93)) = (s8) arg5;
    *((s16 *) (((u8 *) temp_v0) + 0x98)) = (s16) arg1;
    *((s16 *) (((u8 *) temp_v0) + 0x9C)) = (s16) arg3;
    *((s16 *) (((u8 *) temp_v0) + 0x96)) = (s16) arg4;
    *((s8 *) (((u8 *) temp_v0) + 0x94)) = (s8) arg6;
    ambient_flare_point_set(arg1, arg2, arg3, temp_v0);
  }
}

/* was func_15166688 */
void water_ring_spawn_ex(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9)
{
  u32 i;
  u8 *temp_v0;
  temp_v0 = node_alloc(4, arg9, 0xA8, 1, (u8) ((s32) arg8), 1U);
  if (temp_v0 != 0)
  {
    *((s8 *) (((u8 *) temp_v0) + 0x95)) = 2;
    for (i = 0; i != 2; i++)
    {
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x18)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x1A)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x28)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x2A)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x38)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x3A)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x48)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x4A)) = 0x2800;
    }

    *((s16 *) (((u8 *) temp_v0) + 0x9E)) = 1;
    *((s8 *) (((u8 *) temp_v0) + 0x92)) = (s8) arg6;
    *((s8 *) (((u8 *) temp_v0) + 0x93)) = (s8) arg6;
    *((s16 *) (((u8 *) temp_v0) + 0x98)) = (s16) arg2;
    *((s16 *) (((u8 *) temp_v0) + 0x9A)) = (s16) arg3;
    *((s16 *) (((u8 *) temp_v0) + 0x9C)) = (s16) arg4;
    *((s16 *) (((u8 *) temp_v0) + 0x96)) = (s16) arg5;
    *((s8 *) (((u8 *) temp_v0) + 0x94)) = (s8) arg7;
    *((s8 *) (((u8 *) temp_v0) + 0xA0)) = (s8) arg0;
    *((s8 *) (((u8 *) temp_v0) + 0xA1)) = (s8) arg1;
    ambient_flare_point_set(arg2, arg3, arg4);
  }
}

/* was func_15166774 */
void water_ring_update(struct102 *arg0) {
    s32 temp_v0;

    *(s16 *)((u8 *)arg0 + 0x9E) += *(s16 *)((u8 *)arg0 + 0x96) * g_frame_ticks;
    temp_v0 = *(u8 *)((u8 *)arg0 + 0x92);
    temp_v0 -= g_frame_ticks;
    if (temp_v0 <= 0) {
        node_destroy(arg0);
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x92) = temp_v0;
}

f32 math_cos_u8(u8);

/* was func_151667D8 */
u8 *water_ring_draw(u8 *arg0, u8 *arg1, s32 arg2) {
    struct {
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        u8 padB4[0x14];
        s32 uC8;
        u8 padCC[0x4];
        s32 uD0;
        s32 uD4;
        s32 uD8;
    } sp;
    f32 sp7C;
    f32 sp78;
    f32 *temp_v0_6;
    f32 *var_v0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f4_4;
    f32 var_f10;
    f32 var_f12;
    f32 var_f14;
    f32 var_f8;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a2;
    s16 temp_t0;
    s16 temp_t0_2;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t3;
    s16 temp_t4;
    s16 temp_t5;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v1_2;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t7;
    s32 var_v1;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v1;
    u8 *temp_a3;
    u8 *temp_a3_2;
    u8 *temp_a3_3;
    u8 *temp_a3_4;
    u8 *temp_t8;
    u8 *var_a3;

    var_a3 = arg0;
    temp_v0 = (*(u8 *)((u8 *)arg1 + 0x92));
    if (temp_v0 != 0) {
        temp_t4 = (*(s16 *)((u8 *)arg1 + 0x98));
        sp.uD4 = (s32) (*(s16 *)((u8 *)arg1 + 0x9A));
        temp_v1 = (*(u8 *)((u8 *)arg1 + 0x93));
        temp_t5 = (*(s16 *)((u8 *)arg1 + 0x9C));
        temp_a2 = (*(s16 *)((u8 *)arg1 + 0x9E));
        temp_t7 = (s32) (temp_v1 * 3) / 4;
        if ((s32) temp_v0 < ((s32) temp_v1 >> 1)) {
            (*(s16 *)((u8 *)arg1 + 0x96)) = (s16) ((s32) ((*(s16 *)((u8 *)arg1 + 0x96)) * 0xE) / 15);
            if ((*(s16 *)((u8 *)arg1 + 0x96)) <= 0) {
                (*(s16 *)((u8 *)arg1 + 0x96)) = 1;
            }
        }
        temp_v0_2 = (*(u8 *)((u8 *)arg1 + 0x92));
        if ((s32) temp_v0_2 < temp_t7) {
            sp.uC8 = (s32) (temp_v0_2 * 0xFF) / temp_t7;
        } else {
            sp.uC8 = 0xFF;
        }
        temp_v0_3 = (*(u8 *)((u8 *)arg1 + 0x95));
        if (temp_v0_3 == 0) {
            temp_v0_4 = temp_t4 - temp_a2;
            temp_v1_2 = temp_t5 - temp_a2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x10)) = temp_v0_4;
            temp_a1 = temp_t4 + temp_a2;
            temp_t0 = temp_t5 + temp_a2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x14)) = temp_v1_2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x20)) = temp_a1;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x24)) = temp_v1_2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x30)) = temp_a1;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x34)) = temp_t0;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x40)) = temp_v0_4;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x44)) = temp_t0;
        } else if (temp_v0_3 == 1) {
            temp_lo = (s32) ((*(s8 *)((u8 *)arg1 + 0x90)) * temp_a2) / 127;
            temp_t0_2 = temp_t4 - temp_lo;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x10)) = temp_t0_2;
            temp_t2 = temp_t4 + temp_lo;
            temp_lo_2 = (s32) ((*(s8 *)((u8 *)arg1 + 0x91)) * temp_a2) / 127;
            temp_t1 = temp_t5 - temp_lo_2;
            temp_a1_2 = sp.uD4 + temp_a2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x12)) = temp_a1_2;
            temp_t3 = temp_t5 + temp_lo_2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x14)) = temp_t1;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x20)) = temp_t2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x22)) = temp_a1_2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x24)) = temp_t3;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x30)) = temp_t2;
            temp_v0_5 = sp.uD4 - temp_a2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x32)) = temp_v0_5;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x34)) = temp_t3;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x40)) = temp_t0_2;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x42)) = temp_v0_5;
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6))) + 0x44)) = temp_t1;
        } else {
            sp.u8C = 0.0f;
            temp_f0 = (f32) -temp_a2;
            sp.u98 = 0.0f;
            sp.uA4 = 0.0f;
            sp.uB0 = 0.0f;
            temp_f2 = (f32) temp_a2;
            sp.u84 = temp_f0;
            sp.uA0 = temp_f0;
            sp.uA8 = temp_f0;
            sp.uAC = temp_f0;
            sp.u88 = temp_f2;
            sp.u90 = temp_f2;
            sp.u94 = temp_f2;
            sp.u9C = temp_f2;
            sp.uD0 = (s32) temp_t5;
            sp.uD8 = (s32) temp_t4;
            temp_f20 = math_sin_u8((*(u8 *)((u8 *)arg1 + 0xA0)));
            sp78 = math_sin_u8((*(u8 *)((u8 *)arg1 + 0xA1)));
            sp7C = math_cos_u8((*(u8 *)((u8 *)arg1 + 0xA0)));
            temp_f0_2 = math_cos_u8((*(u8 *)((u8 *)arg1 + 0xA1)));
            temp_f22 = (f32) temp_t4;
            temp_f24 = (f32) sp.uD4;
            var_v0 = &sp.u84;
            var_v1 = 0;
            temp_f26 = (f32) temp_t5;
            temp_f4 = (*(f32 *)((u8 *)var_v0 + 4));
            var_f14 = (*(f32 *)((u8 *)var_v0 + 8));
            var_f10 = sp7C * temp_f4;
            var_f8 = temp_f20 * temp_f4;
            var_f12 = sp7C * var_f14;
            if (0 != 0x30) {
                do {
                    temp_f4_2 = var_f12 + var_f8;
                    temp_f2_2 = *var_v0;
                    var_v0 = (f32 *)((u8 *)var_v0 + (0xC));
                    (*(f32 *)((u8 *)var_v0 + -8)) = (f32) (var_f10 - (temp_f20 * var_f14));
                    (*(f32 *)((u8 *)var_v0 + -0xC)) = (f32) ((temp_f0_2 * temp_f2_2) - (sp78 * temp_f4_2));
                    (*(f32 *)((u8 *)var_v0 + -4)) = (f32) ((temp_f0_2 * temp_f4_2) + (sp78 * temp_f2_2));
                    (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6) + var_v1)) + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)var_v0 + -0xC)) + temp_f22);
                    (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6) + var_v1)) + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)var_v0 + -8)) + temp_f24);
                    temp_t8 = arg1 + (g_dl_buf_index << 6) + var_v1;
                    var_v1 += 0x10;
                    (*(s16 *)((u8 *)temp_t8 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)var_v0 + -4)) + temp_f26);
                    temp_f4_3 = (*(f32 *)((u8 *)var_v0 + 4));
                    var_f14 = (*(f32 *)((u8 *)var_v0 + 8));
                    var_f10 = sp7C * temp_f4_3;
                    var_f8 = temp_f20 * temp_f4_3;
                    var_f12 = sp7C * var_f14;
                } while (var_v1 != 0x30);
            }
            temp_f2_3 = *var_v0;
            temp_f4_4 = var_f12 + var_f8;
            temp_v0_6 = ((f32 *)((u8 *)var_v0 + 0xC));
            (*(f32 *)((u8 *)temp_v0_6 + -8)) = (f32) (var_f10 - (temp_f20 * var_f14));
            (*(f32 *)((u8 *)temp_v0_6 + -0xC)) = (f32) ((temp_f0_2 * temp_f2_3) - (sp78 * temp_f4_4));
            (*(f32 *)((u8 *)temp_v0_6 + -4)) = (f32) ((temp_f0_2 * temp_f4_4) + (sp78 * temp_f2_3));
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6) + var_v1)) + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_6 + -0xC)) + temp_f22);
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6) + var_v1)) + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_6 + -8)) + temp_f24);
            (*(s16 *)((u8 *)((arg1 + (g_dl_buf_index << 6) + var_v1)) + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_6 + -4)) + temp_f26);
        }
        (*(s32 *)((u8 *)var_a3 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_a3 + 4)) = 0;
        temp_a3 = var_a3 + 8;
        (*(s32 *)((u8 *)temp_a3 + 0)) = 0xFA000000;
        temp_a3_2 = temp_a3 + 8;
        (*(s32 *)((u8 *)temp_a3 + 4)) = (s32) ((sp.uC8 & 0xFF) | ~0xFF);
        (*(s32 *)((u8 *)temp_a3_2 + 0)) = 0x01004008;
        temp_a3_3 = temp_a3_2 + 8;
        (*(u8 **)((u8 *)temp_a3_2 + 4)) = (u8 *) (arg1 + (g_dl_buf_index << 6) + 0x10);
        (*(s32 *)((u8 *)temp_a3_3 + 0)) = 0x05000204;
        temp_a3_4 = temp_a3_3 + 8;
        (*(s32 *)((u8 *)temp_a3_3 + 4)) = 0;
        (*(s32 *)((u8 *)temp_a3_4 + 0)) = 0x05000406;
        (*(s32 *)((u8 *)temp_a3_4 + 4)) = 0;
        var_a3 = temp_a3_4 + 8;
    }
    return var_a3;
}
extern s16 g_layer_tex_scroll_pos; /* was D_800DD270 */
extern s32 g_layer_tex_scroll; /* was D_800DD650 */
extern s32 g_layer_tex_mode; /* was D_800DD654 */
extern s32 g_layer_tex; /* was D_800DD658 */
extern u8 g_layer_tex_sprite[]; /* was D_800DD660 */
extern u8 g_layer_scroll_texture[]; /* was D_800907A4 */
extern s32 g_gfx_tlut_mode; /* was D_800D30BC */
extern s32 g_render_mode_pairs[]; /* render mode pairs (2 words each); was D_800A4EA8 */
u8 *sprite_load_texture(u8 *, s32 *, s32, s32 *, s32, s32, s32, s32, s32);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);

/* layer_pre_scroll_texture: P238: `pre` callback of render layer 4 (g_node_type_table + 0xE4, RenderLayer +0x14; called as
 * pre(gdl, layer, list, arg2) by node_render_layers_draw, the other arguments are unused). Advances the s16 scroll g_layer_tex_scroll_pos by
 * 0x80 (back to 0 once it reaches 0x500), records texture g_layer_scroll_texture / the old scroll / 1 in g_layer_tex / 650 / 654,
 * emits the texture through sprite_load_texture(gdl, g_layer_tex, g_layer_tex_scroll, g_layer_tex_sprite, 0, 0, 0, 1, 3) and returns the
 * render mode set by gfx_other_mode_cached(gdl, g_gfx_tlut_mode | 0x82CA0, render modes 3 (g_render_mode_pairs words 7 | 6), &1). */
/* was func_15166E28 */
Gfx *layer_pre_scroll_texture(Gfx *gdl, s32 layer, s32 list, s16 arg3) {
    u8 one = 1;
    s16 prev = g_layer_tex_scroll_pos;

    g_layer_tex_scroll_pos = prev + 0x80;
    g_layer_tex = (s32) g_layer_scroll_texture;
    g_layer_tex_scroll = prev;
    if (g_layer_tex_scroll_pos >= 0x500) {
        g_layer_tex_scroll_pos = 0;
    }
    g_layer_tex_mode = 1;
    gdl = (Gfx *) sprite_load_texture((u8 *) gdl, (s32 *) g_layer_tex, g_layer_tex_scroll, (s32 *) g_layer_tex_sprite, 0, 0, 0, 1, 3);
    return gfx_other_mode_cached(gdl, g_gfx_tlut_mode | 0x82CA0, g_render_mode_pairs[7] | g_render_mode_pairs[6], &one);
}
