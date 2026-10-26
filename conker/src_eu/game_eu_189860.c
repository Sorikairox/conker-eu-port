#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_render_mode_pairs[]; /* was D_800A4EA8 */


extern s32 (*D_8008B418[])(u8 *);
extern s32 (*D_8008B41C[])(u8 *);
u8 sprite_anim_advance(u8, u8 *, u8 *, u8);
/* was func_1515C050 */
void quad_fx_update(u8 *arg0) {
    s32 pad; // fakematch: frame pad puts the flag spill at 0x23
    u8 flag;

    flag = 0;
    if (arg0[0x11] & 1) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            flag = 1;
        }
    }
    if (flag == 0) {
        if (((s8 *)arg0)[0x38] != -1) {
            if (D_8008B418[((s8 *)arg0)[0x38]](arg0) == 0) {
                flag = 1;
            }
        }
        if (*(s32 *)(arg0 + 0x1C) != 0) {
            flag = sprite_anim_advance(arg0[0x10], arg0 + 0x1C, arg0 + 0x18, arg0[0x12]);
        }
    }
    if (flag != 0) {
        if (((s8 *)arg0)[0x39] != -1) {
            if (D_8008B41C[((s8 *)arg0)[0x39]](arg0) != 0) {
                node_destroy((struct102 *)arg0);
            }
        } else {
            node_destroy((struct102 *)arg0);
        }
    }
}

s32 gfx_set_combine_mode(s32, u8, s8 *);
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear);
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
s32 gfx_prim_color_cached(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 gfx_load_texture_cached(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void fx_calc_color_mode_a(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void fx_calc_color_mode_b(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern s32 D_800D30BC;

/* was func_1515C160 */
u8 *quad_fx_draw(s32 arg0, u8 *arg1, s32 arg2) {
    struct {
        s16 u62;
        s16 u64;
        s16 u66;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        u8 pad72[0x1];
        s8 u73;
    } sp;
    s32 temp_a0;
    s32 var_v1;
    u8 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    sp.u73 = 1;
    fx_calc_color_mode_a(&sp.u70, &sp.u6E, &sp.u6C, &sp.u6A, (s32) (*(u8 *)((u8 *)arg1 + 0x20)), (s32) (*(u8 *)((u8 *)arg1 + 0x21)), (s32) (*(u8 *)((u8 *)arg1 + 0x22)), (s32) (*(u8 *)((u8 *)arg1 + 0x23)), (s32) (*(u8 *)((u8 *)arg1 + 0x24)), (s32) (*(u8 *)((u8 *)arg1 + 0x25)), (s32) (*(u8 *)((u8 *)arg1 + 0x26)), (s32) (*(u8 *)((u8 *)arg1 + 0x27)), (s32) (*(u8 *)((u8 *)arg1 + 0x28)), (s32) (*(u8 *)((u8 *)arg1 + 0x29)));
    fx_calc_color_mode_b(&sp.u68, &sp.u66, &sp.u64, &sp.u62, (s32) (*(u8 *)((u8 *)arg1 + 0x20)), (s32) (*(u8 *)((u8 *)arg1 + 0x21)), (s32) (*(u8 *)((u8 *)arg1 + 0x22)), (s32) (*(u8 *)((u8 *)arg1 + 0x23)), (s32) (*(u8 *)((u8 *)arg1 + 0x24)), (s32) (*(u8 *)((u8 *)arg1 + 0x25)), (s32) (*(u8 *)((u8 *)arg1 + 0x26)), (s32) (*(u8 *)((u8 *)arg1 + 0x27)), (s32) (*(u8 *)((u8 *)arg1 + 0x28)), (s32) (*(u8 *)((u8 *)arg1 + 0x2A)));
    temp_v1 = (*(u8 *)((u8 *)arg1 + 0x10));
    temp_a0 = gfx_set_combine_mode(gfx_load_texture_cached(gfx_prim_color_cached(gfx_env_color_cached(gfx_geometry_mode_cached(arg0, (*(s32 *)((u8 *)arg1 + 0x30)), (*(s32 *)((u8 *)arg1 + 0x34))), sp.u68, sp.u66, sp.u64, (s32) sp.u62, &sp.u73), 0, 0, sp.u70, (s32) sp.u6E, (s32) sp.u6C, (s32) sp.u6A, &sp.u73), &D_80090F10[temp_v1], (*(s32 *)((u8 *)arg1 + 0x18)), 0, 0, 0, (s32) temp_v1, 0, 0, &sp.u73, 3), (*(u8 *)((u8 *)arg1 + 0x2C)), &sp.u73);
    if ((*(u8 *)((u8 *)arg1 + 0x11)) & 2) {
        var_v1 = 0x100000;
    } else {
        var_v1 = 0;
    }
    temp_v0_2 = ((*(u8 *)((u8 *)arg1 + 0x2B)) * 8) + ((u8 *)&g_render_mode_pairs);
    temp_v0 = gfx_other_mode_cached(temp_a0, var_v1 | 0x80000 | D_800D30BC | 0x2CA0, (*(s32 *)((u8 *)temp_v0_2 + 4)) | (*(s32 *)((u8 *)temp_v0_2 + 0)), &sp.u73);
    (*(u8 **)((u8 *)temp_v0 + 4)) = (u8 *) (arg1 + 0x50);
    (*(s32 *)((u8 *)temp_v0 + 0)) = 0x01004008;
    (*(s32 *)((u8 *)temp_v0 + 8)) = 0x05000204;
    (*(s32 *)((u8 *)temp_v0 + 0xC)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 0x05000406;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    return temp_v0 + 0x18;
}
s32 memcpy(u8 *, u8 **, s32);

/* was func_1515C3C0 */
u8 *motion_track_spawn(u8 **arg0, s32 arg1, u8 arg2, s32 arg3)
{
  u8 *temp_v0;
  u8 *sp2C;
  if ((*arg0) == 0)
  {
    return 0;
  }
  temp_v0 = node_alloc(0x32, arg3, arg1 + 0x50, 1, (u8) ((s32) arg2), 1U);
  if (temp_v0 == 0)
  {
    return 0;
  }
  sp2C = temp_v0; // fakematch: copy of the result in its own local
  memcpy(temp_v0 + 0x18, arg0, 8);
  *((f32 *) (((u8 *) sp2C) + 0x20)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x14)));
  *((f32 *) (((u8 *) sp2C) + 0x24)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x18)));
  *((f32 *) (((u8 *) sp2C) + 0x28)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x1C)));
  *((f32 *) (((u8 *) sp2C) + 0x2C)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x14)));
  *((f32 *) (((u8 *) sp2C) + 0x30)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x18)));
  *((f32 *) (((u8 *) sp2C) + 0x34)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x1C)));
  *((s32 *) (((u8 *) sp2C) + 0x44)) = 0;
  *((s32 *) (((u8 *) sp2C) + 0x48)) = -1;
  *((s32 *) (((u8 *) sp2C) + 0x10)) = 1;
  *((s32 *) (((u8 *) sp2C) + 0x14)) = 0;
  *((f32 *) (((u8 *) sp2C) + 0x38)) = 0.0f;
  *((f32 *) (((u8 *) sp2C) + 0x3C)) = 0.0f;
  *((f32 *) (((u8 *) sp2C) + 0x40)) = 0.0f;
  return sp2C;
}

/* was func_1515C4C0 */
void motion_track_retire(struct102 *arg0) {
    char_fx_detach_effect(arg0, ((s32 *)arg0)[0x18 / 4]);
    node_retire(arg0);
}

/* was func_1515C4EC */
void motion_track_free(struct102 *arg0) {
    char_fx_detach_effect(arg0, ((s32 *)arg0)[0x18 / 4]);
    node_unlink_free(arg0);
}

typedef struct { f32 x, y, z; } V3C518;
/* was func_1515C518 */
void motion_track_update(u8 *arg0) {
    s32 flag;
    u8 *o;
    V3C518 *cur;
    V3C518 *prev;
    V3C518 *d;

    flag = 0;
    if (arg0[0x1D] & 1) {
        *(s16 *)(arg0 + 0x1E) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x1E) < 0) {
            flag = 1;
        }
    }
    o = *(u8 **)(arg0 + 0x18);
    if (*(s32 *)o == 0 || arg0[0x1C] != o[0x3B]) {
        flag = 1;
    }
    if (flag == 0) {
        cur = (V3C518 *)(arg0 + 0x20);
        prev = (V3C518 *)(arg0 + 0x2C);
        d = (V3C518 *)(arg0 + 0x38);
        *prev = *cur;
        cur->x = ((V3C518 *)(*(u8 **)(arg0 + 0x18) + 0x14))->x;
        cur->y = ((V3C518 *)(*(u8 **)(arg0 + 0x18) + 0x14))->y;
        cur->z = ((V3C518 *)(*(u8 **)(arg0 + 0x18) + 0x14))->z;
        d->x = (prev->x - cur->x) * D_800BEDC8;
        d->y = (prev->y - cur->y) * D_800BEDC8;
        d->z = (prev->z - cur->z) * D_800BEDC8;
    }
    if (flag != 0) {
        node_destroy((struct102 *)arg0);
    }
}

/* was func_1515C628 */
void motion_track_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, (s32)(arg0 + 0x18), (s32)(arg0 + 0x1C), (s32)arg0);
}

/* was func_1515C668 */
s32 motion_track_get_delta(u8 *arg0, u8 **arg1)
{
  struct_eu_link *sp1C;
  struct_eu_attached *new_var;
  do
  {
    if (arg0 == 0)
    {
      dummy_label_135635:
      ;

      ;
      goto block_4;
    }
    if (char_fx_find_slot(*((struct_eu_link **) (((u8 *) arg0) + 0x2F4)), 0x16, &sp1C) != 0)
    {
      new_var = sp1C->unk10;
      *arg1 = (u8 *) new_var + 0x38;
      return 1;
    }
  }
  while (0);
  block_4:
  return 0;

}

/* was func_1515C6C8 */
void motion_track_reset_all(void) {
    s32 i;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (node = g_node_lists[i][50]; node != NULL; node = node->next) {
            *(s32 *)((u8 *)node + 0x44) = 0;
            *(s32 *)((u8 *)node + 0x48) = -1;
        }
    }
}

/* was func_1515C710 */
void obj_get_fx_point_a(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 t;
    t = arg0[4];
    if (t < 0xBB && t != 0xFF) {
        *arg2 = *(s16 *)(arg0 + 0xD2);
        *arg3 = *(s16 *)(arg0 + 0xD4);
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(s16 *)(arg0 + 0xD6) + *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    } else {
        *arg2 = 1.0f;
        *arg3 = 1.0f;
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    }
}

/* was func_1515C7B4 */
void obj_get_fx_point_b(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 t;
    t = arg0[4];
    if (t < 0xBB && t != 0xFF) {
        *arg2 = *(s16 *)(arg0 + 0xE4);
        *arg3 = *(s16 *)(arg0 + 0xE6);
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(s16 *)(arg0 + 0xE8) + *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    } else {
        *arg2 = 1.0f;
        *arg3 = 1.0f;
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    }
}
