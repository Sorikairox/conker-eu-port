#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void light_remove(s32);

struct_eu_node *head_icon_find(s32 arg0);


s32 shared_dl_acquire(s32);
/* was func_15155CF0 */
struct_eu_node *head_icon_create(s32 arg0, s32 arg1)
{
  struct_eu_node *temp_v0;
  temp_v0 = node_alloc(0x50, 0, 0xA0, 1, (u8) arg1, 1U);
  if (temp_v0 == 0)
  {
    return temp_v0;
  }
  *((s8 *) (((u8 *) temp_v0) + 0x10)) = (s8) arg0;
  *((s8 *) (((u8 *) temp_v0) + 0x11)) = 0;
  *((s32 *) (((u8 *) temp_v0) + 0x14)) = 0;
  *((f32 *) (((u8 *) temp_v0) + 0x98)) = 0.0f;
  shared_dl_acquire(0xA6);
  return temp_v0;
}

struct_eu_node *head_icon_create(s32, s32);

/* was func_15155D6C */
void head_icon_show_timed(s32 arg0, s32 arg1, f32 arg2) {
    struct_eu_node *var_v0;

    var_v0 = head_icon_find(arg0);
    if (var_v0 == NULL) {
        var_v0 = head_icon_create(arg0, 0xFF);
    }
    if (var_v0 != NULL) {
        (*(f32 *)((u8 *)var_v0 + 0x98)) = arg2;
        if (*(&g_objects_in_water + (arg0 * 0x32C)) != 0) {
            (*(s16 *)((u8 *)var_v0 + 0xE)) = 0;
            (*(s8 *)((u8 *)var_v0 + 0x11)) = 0;
            return;
        }
        (*(s8 *)((u8 *)var_v0 + 0x11)) = 3;
        (*(s16 *)((u8 *)var_v0 + 0xE)) = (s16) arg1;
    }
}

u8 *light_add_point(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

/* was func_15155E0C */
void head_icon_update(u8 *arg0) {
    struct127 *sp48;
    f32 sp38;
    f32 var_f2;
    s16 temp_v0;
    s16 var_v0_2;
    struct126 *temp_v1_2;
    struct127 *temp_t0;
    u8 temp_a2;
    u8 temp_v1;
    u8 var_v0;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_a1_3;
    u8 *temp_a1_4;
    u8 *var_v0_3;

    temp_a2 = (*(u8 *)((u8 *)arg0 + 0x10));
    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x11));
    temp_t0 = &g_objects[temp_a2];
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v1_2 = g_objects[temp_a2].unk31C;
        var_v0 = 0;
        if (temp_v1_2 != NULL) {
            var_v0 = temp_v1_2->pad_kind;
        }
        if (!(var_v0 & 0x80) && (var_v0 != 0x2A) && (var_v0 != 0x2B) && ((var_v0 != 0x42) || !(g_hints_seen_b8 & 4)) && (var_v0 != 0x2C) && (temp_v1_2->aim_state == 0) && (var_v0 != 0) && (var_v0 != 0x1F) && (temp_t0->in_water == 0)) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 1U;
            (*(s16 *)((u8 *)arg0 + 0xE)) = 0x78;
            sound_play_2d(0x1EB, 0x7FFFU, 0x40U, 0, 0U);
            return;
        }
        temp_a1 = (*(u8 **)((u8 *)arg0 + 0x14));
        if (temp_a1 != NULL) {
            light_remove((s32) temp_a1);
            (*(u8 **)((u8 *)arg0 + 0x14)) = NULL;
            return;
        }
        return;
    case 1:
        var_v0_2 = (*(s16 *)((u8 *)arg0 + 0xE)) - g_frame_ticks;
        if ((var_v0_2 <= 0) || (g_objects[temp_a2].unk31C->pad_kind == 0)) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 2U;
            var_v0_2 = 0;
        }
        (*(s16 *)((u8 *)arg0 + 0xE)) = var_v0_2;
        temp_a1_2 = (*(u8 **)((u8 *)arg0 + 0x14));
        (*(u8 *)((u8 *)arg0 + 0x12)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x12)) + (g_frame_ticks * 2));
        if (temp_a1_2 != NULL) {
            if (g_objects[temp_a2].unk31C->pad_kind == 5) {
                var_f2 = 85.0f;
            } else {
                var_f2 = 0.0f;
            }
            (*(s16 *)((u8 *)temp_a1_2 + 0xE)) = (s16) (s32) temp_t0->x_position;
            sp38 = var_f2;
            sp48 = temp_t0;
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x10)) = (s16) (s32) ((math_sin_u8((*(u8 *)((u8 *)arg0 + 0x12))) * 15.0f) + (temp_t0->y_position + 160.0f + (*(f32 *)((u8 *)arg0 + 0x98)) + var_f2));
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x12)) = (s16) (s32) temp_t0->z_position;
            return;
        }
        var_v0_3 = light_add_point(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
block_38:
        (*(u8 **)((u8 *)arg0 + 0x14)) = var_v0_3;
        break;
    case 2:
        if (g_objects[temp_a2].unk31C->pad_kind == 0) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 0U;
        }
        temp_a1_3 = (*(u8 **)((u8 *)arg0 + 0x14));
        if (temp_a1_3 != NULL) {
            light_remove((s32) temp_a1_3);
            (*(u8 **)((u8 *)arg0 + 0x14)) = NULL;
            return;
        }
        break;
    case 3:
        temp_v0 = (*(s16 *)((u8 *)arg0 + 0xE)) - g_frame_ticks;
        if (temp_v0 <= 0) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 2U;
            (*(s16 *)((u8 *)arg0 + 0xE)) = 0;
            return;
        }
        (*(s16 *)((u8 *)arg0 + 0xE)) = temp_v0;
        temp_a1_4 = (*(u8 **)((u8 *)arg0 + 0x14));
        (*(u8 *)((u8 *)arg0 + 0x12)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x12)) + (g_frame_ticks * 2));
        if (temp_a1_4 != NULL) {
            (*(s16 *)((u8 *)temp_a1_4 + 0xE)) = (s16) (s32) temp_t0->x_position;
            sp48 = temp_t0;
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x10)) = (s16) (s32) ((math_sin_u8((*(u8 *)((u8 *)arg0 + 0x12))) * 15.0f) + (temp_t0->y_position + 160.0f));
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x12)) = (s16) (s32) temp_t0->z_position;
            return;
        }
        var_v0_3 = light_add_point(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
        goto block_38;
    }
}
extern Gfx **g_head_icon_dl; /* was D_800E0810 */
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ u8 obj;
    /* 0x11 */ u8 mode;
    /* 0x12 */ u8 ang;
    /* 0x13 */ u8 pad13[5];
    /* 0x18 */ Mtx mtx[2];
    /* 0x98 */ f32 yoff;
} Unk1515626C;
Gfx *sprite_gfx_begin_alt(Gfx *arg0);

/* was func_1515626C */
Gfx *head_icon_draw(Gfx *gdl, Unk1515626C *arg1, s16 arg2) {
    u8 mode;
    u8 obj;
    struct127 *p;

    mode = arg1->mode;
    obj = arg1->obj;
    if (mode == 1 || mode == 3) {
        f32 rot;
        s32 pad; // fakematch: slot 0x58 between rot and h
        f32 h;

        p = &g_objects[obj];
        if (p->unk31C->pad_kind == 5) {
            h = 85.0f;
        } else {
            h = 0.0f;
        }
        rot = g_player_views[arg2].unk380;
        gdl = sprite_gfx_begin_alt(gdl);
        mtx_build_rot_scale_trans(&arg1->mtx[g_dl_buf_index], 0.0f, rot, 0.0f, 2.25f, 2.25f, 2.25f, p->x_position,
                      math_sin_u8(arg1->ang) * 15.0f + (p->y_position + 160.0f + h + arg1->yoff), p->z_position);
        gSPMatrix(gdl++, &arg1->mtx[g_dl_buf_index], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPClearGeometryMode(gdl++, G_ZBUFFER);
        gSPDisplayList(gdl++, *g_head_icon_dl);
        gSPSetGeometryMode(gdl++, G_ZBUFFER);
    }
    return gdl;
}

void light_remove(s32);
s32 shared_dl_release(s32);
/* was func_15156468 */
void head_icon_free(struct102 *arg0)
{
  u8 *p = (u8 *) arg0;
  s32 temp_a2;
  temp_a2 = *((s32 *) (p + 0x14));
  if (temp_a2 != 0)
  {
    light_remove(temp_a2);
  }
  if (((!arg0) && (!arg0)) && (!arg0)) // fakematch: dead test from the permuter
  {
  }
  node_retire(p);
  shared_dl_release(0xA6);
}

/* was func_151564AC */
void head_icon_hide_current(void) {
    u8 *temp_v0 = (u8 *)head_icon_find(g_cur_obj_index);

    if (temp_v0 != NULL) {
        if (temp_v0[0x11] == 2) {
            temp_v0[0x11] = 0;
        } else if (temp_v0[0x11] == 3) {
            temp_v0[0x11] = 2;
        }
    }
}

/* was func_15156500 */
void head_icon_set_bobbing(void) {
    u8 *temp_v0 = (u8 *)head_icon_find(g_cur_obj_index);

    if ((temp_v0 != NULL) && (temp_v0[0x11] == 3)) {
        temp_v0[0x11] = 1;
    }
}

/* was func_15156544 */
struct_eu_node *head_icon_find(s32 arg0) {
    s32 i;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (node = g_node_lists[i][80]; node != NULL; node = node->next) {
            if (arg0 == ((u8 *)node)[0x10]) {
                return node;
            }
        }
    }
    return NULL;
}

/* was func_15156598 */
void head_icon_on_message(u8 *arg0, struct127 **arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 a;
        a = arg1[0] - g_objects;
        if ((a >= 0) && (a < 25) && (a == arg0[0x10])) {
            node_destroy((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        s32 a;
        s32 b;
        a = arg1[0] - g_objects;
        b = arg1[1] - g_objects;
        if ((a >= 0) && (a < 25) && (b >= 0) && (b < 25)) {
            if (a == arg0[0x10]) { arg0[0x10] = b; }
            else if (b == arg0[0x10]) { arg0[0x10] = a; }
        }
    }
}
