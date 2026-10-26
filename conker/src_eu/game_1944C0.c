#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void render_group_layer_range(s32 arg0, s32 *arg1, s32 *arg2);
typedef struct { u8 pad0[0xC]; void (*fn0C)(struct_eu_node *); u8 pad10[0xC]; void (*fn)(struct_eu_node *, s32, u8); u8 pad20[0x14]; } Tbl9070;
extern Tbl9070 g_node_type_table[]; /* was D_8008B848 */


/* P95: per-frame update hooks: calls the +0x18 function of each of the 101 g_node_type_table entries that has one
 * (no arguments are set up: a0 is the caller's, unused by the hooks as far as known). */
/* was func_15167010 */
void node_types_run_frame_hooks(void) {
    Tbl9070 *p;

    for (p = g_node_type_table; p < (Tbl9070 *) ((u8 *) g_node_type_table + 0x1484); p++) {
        if (*(void (**)(void)) ((u8 *) p + 0x18) != NULL) {
            (*(void (**)(void)) ((u8 *) p + 0x18))();
        }
    }
}
// NON-MATCHING: EU table has 101 entries (g_node_type_update_fns = 0x8008B848 in EU); register/loop shape differs
// void node_types_run_frame_hooks(void) {
//     void (*func)(void);
//     struct115 *p;
//     s32 i;
//
//     p = g_node_type_update_fns;
//     for (i = 0; i < 101; i++, p++) {
//         func = (void (*)(void))p->unk18;
//         if (func != NULL) {
//             func();
//         }
//     }
// }

/* was func_1516706C */
void node_run_global_hooks(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (g_node_global_hooks[i] != NULL) {
            g_node_global_hooks[i]();
        }
    }
}
/* was func_151670C0 */
void node_lists_run_update(void) {
    s32 i;
    s32 j;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 101; j++) {
            if (g_node_type_update_fns[j].unk0 != NULL) {
                node = g_node_lists[i][j];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    g_node_type_update_fns[j].unk0((struct102 *)node);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            }
        }
    }
}
/* was func_151671E8 */
void node_lists_run_update2(void) {
    s32 i;
    s32 j;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 101; j++) {
            if (((void (**)(struct_eu_node *))&g_node_type_update_fns[j])[1] != NULL) {
                node = g_node_lists[i][j];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    ((void (**)(struct_eu_node *))&g_node_type_update_fns[j])[1](node);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            }
        }
    }
}
extern f32 D_800DD600[2];
extern f32 g_view_yaw_sin[4]; /* was D_800DD608 */
extern f32 g_view_yaw_cos[4]; /* was D_800DD618 */
/* was func_15167310 */
void node_lists_run_view_update(void) {
    s32 i;
    f32 a;
    s32 j;
    struct_eu_node *node;
    s32 k;

    for (k = 0; k < g_last_player_index + 1; k++) {
        a = *(f32 *)((u8 *)g_player_views + k * 0x9A0 + 0x3A0);
        g_view_yaw_sin[k] = sinf(a);
        g_view_yaw_cos[k] = cosf(a);
    }
    a = g_player_views->unk3A0;
    D_800DD600[0] = sinf(a);
    D_800DD600[1] = cosf(a);
dummy: ; // fakematch: label splits the block (permuter)
    for (j = 0; j < 0x68; j++) {
        for (i = 0; i < 2; i++) {
            if (g_node_lists[i][j] != NULL && g_node_type_table[j].fn0C != NULL) {
                node = g_node_lists[i][j];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    g_node_type_table[j].fn0C(node);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            }
        }
    }
}
/* The fields of a g_node_type_table render layer (0x34 bytes) that node_render_layers_draw uses. */
typedef struct {
    u8 pad0[0x8];
    Gfx *(*draw)(Gfx *, struct_eu_node *, s16); /* per node */
    void (*fn0C)(struct_eu_node *);
    Gfx *dlPre;
    Gfx *(*pre)(Gfx *, s32, s32, s16);
    u8 pad18[0x8];
    Gfx *(*post)(Gfx *, s32, s16);
    Gfx *dlPost;
    u8 pad28[0x8];
    s8 type; /* 0: dropped whole on DL overflow, 1: per-node overflow check */
    u8 pad31[0x3];
} RenderLayer;
extern struct_eu_node *g_node_iter_next[]; /* was D_800DD5C8 */
extern s8 g_node_iter_depth; /* was D_800DD5C0 */
extern struct_eu_node *g_node_lists[][104]; /* was D_800DD280 */
extern u8 g_sprite_keep_prim_colour; /* was D_800D31CB */
extern s32 g_tex_cache_last_addr; /* was D_800DD5E0 */
extern s32 D_800DD5E4;
extern s32 D_800DD5E8;
extern s16 g_sprite_last_other_mode; /* was D_800DD5EC */
extern s16 D_800DD5EE;
extern s16 g_gfx_prim_r_cached; /* was D_800DD5F0 */
extern s16 g_gfx_prim_g_cached; /* was D_800DD5F2 */
extern s16 g_gfx_prim_b_cached; /* was D_800DD5F4 */
extern s16 g_gfx_prim_a_cached; /* was D_800DD5F6 */
extern s16 g_gfx_env_r_cached; /* was D_800DD5F8 */
extern s16 g_gfx_env_g_cached; /* was D_800DD5FA */
extern s16 g_gfx_env_b_cached; /* was D_800DD5FC */
extern s16 g_gfx_env_a_cached; /* was D_800DD5FE */
extern s16 g_gfx_cached_state_628; /* was D_800DD628 */
extern s32 g_gfx_geom_set_cached; /* was D_800DD62C */
extern s32 g_gfx_geom_clear_cached; /* was D_800DD630 */
extern s16 g_gfx_prim_m_cached; /* was D_800DD634 */
extern s16 g_gfx_prim_l_cached; /* was D_800DD636 */
extern s32 g_gfx_tex_parm_a_cached; /* was D_800DD638 */
extern s32 g_gfx_tex_parm_b_cached; /* was D_800DD63C */
extern s32 g_gfx_tex_parm_c_cached; /* was D_800DD640 */
extern s32 g_gfx_tex_parm_d_cached; /* was D_800DD644 */
extern s32 g_gfx_othermode_hi_cached; /* was D_800DD648 */
extern s32 g_gfx_othermode_lo_cached; /* was D_800DD64C */
extern s32 g_layer_tex_scroll; /* was D_800DD650 */
extern s32 g_layer_tex_mode; /* was D_800DD654 */
extern s32 g_layer_tex; /* was D_800DD658 */
extern Gfx *D_800BEDE8[];
extern s32 g_dl_capacity; /* was D_800BEFC4 */
extern u8 g_identity_mtx[]; /* was D_80089810 */

#define DL_FULL(g) (g_dl_capacity < (g) - D_800BEDE8[g_dl_buf_index])

/* Draw the render layers of `group` (render_group_layer_range gives the index range) from node list `list`:
 * per layer the pre DL / callback, every node's draw callback, then the post DL / callback.
 * The node walk keeps its cursor in g_node_iter_next[depth] so a callback can unlink nodes. When the DL buffer
 * runs out, a type 1 layer drops the node that overflowed and a type 0 layer is dropped whole; the
 * layer's start is then returned with a G_SETGEOMETRYMODE(1) at the cut instead of the rest. */
/* was func_151674F8 */
void *node_render_layers_draw(void *arg0, s32 group, s16 arg2, s32 list) {
    Gfx *gdl = arg0;
    RenderLayer *layer;
    struct_eu_node **head;
    struct_eu_node *node;
    Gfx *before;
    Gfx *start0;
    Gfx *start1;
    s32 first;
    s32 last;
    s32 i;
    s32 dropped;
    Gfx *(*draw)(Gfx *, struct_eu_node *, s16);

    gSPMatrix(gdl++, g_identity_mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    render_group_layer_range(group, &first, &last);
    layer = &((RenderLayer *)g_node_type_table)[first];
    for (i = first; i < last; i++, layer++) {
        if (layer->draw == NULL) {
            continue;
        }
        head = &g_node_lists[list][i];
        if (*head == NULL) {
            continue;
        }
        g_dbg_crash_marker = (i & 0xFFFFFF) | 0x07000000;
        dropped = 0;
        if (layer->type == 0) {
            start0 = gdl;
        }
        if (layer->type == 1) {
            start1 = gdl;
        }
        g_sprite_keep_prim_colour = 0;
        g_layer_tex = 0;
        g_layer_tex_scroll = 0;
        g_layer_tex_mode = 2;
        g_tex_cache_last_addr = -1;
        D_800DD5E4 = -1;
        D_800DD5E8 = -1;
        g_sprite_last_other_mode = 0;
        D_800DD5EE = 0;
        g_gfx_prim_a_cached = -1;
        g_gfx_prim_b_cached = g_gfx_prim_a_cached;
        g_gfx_prim_g_cached = g_gfx_prim_b_cached;
        g_gfx_prim_r_cached = g_gfx_prim_g_cached;
        g_gfx_env_a_cached = -1;
        g_gfx_env_b_cached = g_gfx_env_a_cached;
        g_gfx_env_g_cached = g_gfx_env_b_cached;
        g_gfx_env_r_cached = g_gfx_env_g_cached;
        g_gfx_cached_state_628 = 0;
        g_gfx_geom_set_cached = 0;
        g_gfx_geom_clear_cached = 0;
        g_gfx_prim_m_cached = -1;
        g_gfx_prim_l_cached = -1;
        g_gfx_tex_parm_a_cached = -1;
        g_gfx_tex_parm_b_cached = -1;
        g_gfx_tex_parm_c_cached = -1;
        g_gfx_tex_parm_d_cached = 0;
        g_gfx_othermode_hi_cached = 0;
        g_gfx_othermode_lo_cached = 0;
        if (layer->dlPre != NULL) {
            gdl->words.w0 = 0xDE000000; /* G_DL */
            gdl->words.w1 = (u32)layer->dlPre;
            gdl++;
        }
        if (layer->pre != NULL) {
            gdl = layer->pre(gdl, i, list, arg2);
        }
        gSPClearGeometryMode(gdl++, G_LIGHTING);

        node = *head;
        g_node_iter_depth++;
        if (layer->type == 1) {
            while (node != NULL) {
                draw = layer->draw;
                g_node_iter_next[g_node_iter_depth] = node->next;
                before = gdl;
                gdl = draw(gdl, node, arg2);
                if (DL_FULL(gdl)) {
                    dropped = 1;
                    gdl = before;
                }
                node = g_node_iter_next[g_node_iter_depth];
            }
        } else {
            while (node != NULL) {
                draw = layer->draw;
                g_node_iter_next[g_node_iter_depth] = node->next;
                gdl = draw(gdl, node, arg2);
                node = g_node_iter_next[g_node_iter_depth];
            }
        }
        g_node_iter_depth--;

        if (layer->dlPost != NULL) {
            gdl->words.w0 = 0xDE000000; /* G_DL */
            gdl->words.w1 = (u32)layer->dlPost;
            gdl++;
        }
        if (layer->post != NULL) {
            gdl = layer->post(gdl, i, arg2);
        }
        if (dropped && DL_FULL(gdl)) {
            gSPSetGeometryMode(gdl, 1);
            return start1;
        }
        if (layer->type == 0 && DL_FULL(gdl)) {
            gSPSetGeometryMode(gdl, 1);
            return start0;
        }
        g_dbg_crash_marker = 0;
    }
    gSPSetGeometryMode(gdl++, 1);
    return gdl;
}
#undef DL_FULL
/* was func_15167A68 */
void *node_alloc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5) {
    struct_eu_node *node = (struct_eu_node *)heap_alloc_tagged(arg2, 1, arg3, 0, arg5);

    if (node != NULL) {
        node->unk1 = arg1;
        node_list_insert(node, arg0);
        ((u8 *)node)[0xC] = arg4;
    }
    return node;
}
/* was func_15167AD8 */
void node_spawn_sprite_quad(void *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0 = node_alloc(3, arg2, 0x28, 0, arg1, 1);

    if (temp_v0 != NULL) {
        bcopy(arg0, temp_v0 + 0x10, 0x18);
        temp_v0[0x23] = 0xFF;
    }
}
typedef struct {
    u8  pad0[0x10];
    u8 *unk10;
    s16 unk14;
    s16 unk16;
    u8  pad18[0xA];
    s8  unk22;
    u8  unk23;
    u8  unk24;
} struct_eu_15167B44;

/* was func_15167B44 */
void node_sprite_quad_update(struct_eu_15167B44 *arg0) {
    u8 idx = arg0->unk24;
    s32 step;
    s32 neg;

    if (idx != 0) {
        g_node_end_handlers[idx]();
    }
    step = arg0->unk22;
    if (step > 0) {
        if (step < arg0->unk23) {
            arg0->unk23 -= step;
        } else {
            arg0->unk14 = arg0->unk10[4] << 8;
        }
    } else {
        neg = -step; // fakematch: hoisted out of the step < 0 block (permuter)
        if (step < 0) {
            s16 cur = arg0->unk14;

            if (cur / 256 >= arg0->unk10[4] - 1) {
                if (neg < arg0->unk23) {
                    arg0->unk23 -= neg;
                    arg0->unk14 = cur - arg0->unk16;
                }
            }
        }
    }
    arg0->unk14 += arg0->unk16;
    if (arg0->unk14 / 256 >= arg0->unk10[4]) {
        node_destroy((struct102 *)arg0);
    }
}
Gfx *gfx_load_texture_cached(Gfx *gfx, s32 tex, s32 frame, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *flag, s32 argA);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);
Gfx *sprite_draw_at_world_depth(Gfx *gfx, u8 *quad);
extern s32 g_render_mode_pairs[]; /* render mode pairs (2 words each); was D_800A4EA8 */

// sprite_quad_draw: P210: render-layer draw callback (g_node_type_table layer 3): draws the textured quad of node `obj`.
/* Texture obj +0x10 (word 0 = its frame table, indexed by frame s16 obj +0x14 >> 8), quad position / size s16
 * obj +0x18..+0x20, byte obj +0x23 copied into the quad; render mode g_render_mode_pairs entry 3. Returns the display list end. */
/* was func_15167C58 */
s32 node_sprite_quad_draw(s32 gdl, u8 *obj, s16 player) {
    struct {
        s16 x, y, z;
        s16 w, h;
        u8 bA;
        u8 padB[2];
        u8 bD;
    } quad;
    u8 flag;
    u8 *tex = *(u8 **)(obj + 0x10);
    s16 frame = *(s16 *)(obj + 0x14);
    s32 *mode;
    Gfx *gfx;

    /* the asm stores the word 1 at the flag's address; the byte the callees read (big-endian) is 0 */
    flag = 0;
    gfx = gfx_load_texture_cached((Gfx *)gdl, (s32)tex, frame << 8, 2, 0x100, 0x100, (*(s32 **)tex)[frame >> 8], 5, (s32)&quad,
                        &flag, 3);
    quad.x = *(s16 *)(obj + 0x18);
    quad.y = *(s16 *)(obj + 0x1A);
    quad.z = *(s16 *)(obj + 0x1C);
    quad.w = *(s16 *)(obj + 0x1E);
    quad.h = *(s16 *)(obj + 0x20);
    quad.bA = obj[0x23];
    quad.bD = 0;
    /* the asm compares the s8 at obj +0x22 with 0xFF (entry 9), which never matches: always entry 3 */
    mode = &g_render_mode_pairs[3 * 2];
    gfx = gfx_other_mode_cached(gfx, 0x2C00, (mode[1] | mode[0]) | 4, &flag);
    return (s32)sprite_draw_at_world_depth(gfx, (u8 *)&quad);
}
/* was func_15167D84 */
void *node_spawn_sprite(void *arg0, s32 arg1, s32 arg2, s8 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;
    s32 type;

    if (arg1 == 0) {
        type = 5;
    } else {
        type = 0x42;
    }
    temp_v0 = node_alloc(type, arg5, arg2 + 0x50, 0, arg4, 1);
    if (temp_v0 == NULL) {
        return temp_v0;
    }
    bcopy(arg0, temp_v0 + 0x10, 0x38);
    temp_v0[0x48] = arg3;
    return temp_v0;
}
extern void (*g_node_sprite_behaviours[])(u8 *);  /* node behaviours, by s8 node +0x2F; was D_8008CD68 */
/* g_node_end_handlers (variables.h: void (*[])(void)): node end handlers void (u8 *), by s8 node +0x48 */

// sprite_node_update: P210: per-node update of render layers 5 / 59 / 66 (field 0 of their g_node_type_table records):
/* counts down the lifetime s16 +0x38 by the frame time g_frame_ticks (0x7FFF = forever) and fades the alpha +0x3F
 * by s8 +0x3A per frame; runs the behaviour g_node_sprite_behaviours[+0x2F]; while alive moves the 8.8 fixed-point position
 * (s16 +0x20 / +0x22 / +0x24 with fraction bytes +0x2C / +0x2E / +0x2D) by the velocity +0x26 / +0x30 / +0x28 (+0x30
 * accelerated by +0x32), and advances the animation frame +0x1C by speed +0x1E over the texture's (+0x10) byte 4
 * frames: past the end flag 0x20 ends the node, else 0x80 is set and flag 2 bounces (speed negated) or the frame
 * wraps; below 0 flag 0x40 ends it, flag 2 bounces, else it wraps. An ended node runs g_node_end_handlers[+0x48] and is
 * freed (node_destroy). */
/* was func_15167E0C */
void node_sprite_update(u8 *n) {
    s32 done = FALSE;
    s16 t = *(s16 *)(n + 0x38);
    s32 fade;
    s32 v;
    s32 speed;
    s32 last;
    s32 frame;
    u16 flags;

    if (t != 0x7FFF) {
        *(s16 *)(n + 0x38) = t - g_frame_ticks;
        if (*(s16 *)(n + 0x38) < 0) {
            *(s16 *)(n + 0x38) = 0;
            done = TRUE;
        }
    }
    fade = (s8)n[0x3A];
    if (fade > 0) {
        if (fade < n[0x3F]) {
            n[0x3F] -= fade;
        } else {
            *(s16 *)(n + 0x38) = 0;
            done = TRUE;
        }
    }
    if ((s8)n[0x2F] != -1 && g_node_sprite_behaviours[(s8)n[0x2F]] != NULL) {
        g_node_sprite_behaviours[(s8)n[0x2F]](n);
    }

    if (*(s16 *)(n + 0x38) == 0) {
        done = TRUE;
    } else {
        *(s16 *)(n + 0x30) += *(s16 *)(n + 0x32);
        speed = *(s16 *)(n + 0x1E);
        v = ((*(s16 *)(n + 0x22) << 8) | n[0x2E]) + *(s16 *)(n + 0x30) * g_frame_ticks;
        *(s16 *)(n + 0x22) = v >> 8;
        n[0x2E] = v;
        v = ((*(s16 *)(n + 0x20) << 8) | n[0x2C]) + *(s16 *)(n + 0x26) * g_frame_ticks;
        *(s16 *)(n + 0x20) = v >> 8;
        n[0x2C] = v;
        v = ((*(s16 *)(n + 0x24) << 8) | n[0x2D]) + *(s16 *)(n + 0x28) * g_frame_ticks;
        *(s16 *)(n + 0x24) = v >> 8;
        n[0x2D] = v;
        if (speed != 0) {
            last = ((*(u8 **)(n + 0x10))[4] << 8) - 1;
            *(s16 *)(n + 0x1C) += speed * g_frame_ticks;
            frame = *(s16 *)(n + 0x1C);
            if (last < frame) {
                flags = *(u16 *)(n + 0x44);
                if (flags & 0x20) {
                    *(s16 *)(n + 0x38) = 0;
                    done = TRUE;
                } else {
                    *(u16 *)(n + 0x44) = flags | 0x80;
                    if (flags & 2) {
                        *(s16 *)(n + 0x1C) = last - *(s16 *)(n + 0x1C) % last;
                        *(s16 *)(n + 0x1E) = -*(s16 *)(n + 0x1E);
                    } else {
                        do {
                            *(s16 *)(n + 0x1C) -= last;
                        } while (last < *(s16 *)(n + 0x1C));
                    }
                }
            } else if (frame < 0) {
                flags = *(u16 *)(n + 0x44);
                if (flags & 0x40) {
                    *(s16 *)(n + 0x38) = 0;
                    done = TRUE;
                } else if (flags & 2) {
                    *(s16 *)(n + 0x1C) = -frame % last;
                    *(s16 *)(n + 0x1E) = -speed;
                } else {
                    do {
                        *(s16 *)(n + 0x1C) += last;
                    } while (*(s16 *)(n + 0x1C) < 0);
                }
            }
        }
    }
    if (done) {
        if ((s8)n[0x48] != -1) {
            ((void (*)(u8 *))g_node_end_handlers[(s8)n[0x48]])(n);
        }
        node_destroy((struct102 *)n);
    }
}
/* P186 */
Gfx *gfx_load_texture_cached(Gfx *gfx, s32 tex, s32 frame, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *flag, s32 argA);
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear);
Gfx *gfx_set_combine_mode(Gfx *gfx, u8 combine, u8 *flag);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);
Gfx *gfx_prim_color_cached(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *flag);
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *flag);
Gfx *sprite_draw_at_world_depth(Gfx *gfx, u8 *quad);
extern s32 g_gfx_tlut_mode; /* was D_800D30BC */
extern s32 g_render_mode_pairs[]; /* render mode pairs (2 words each); was D_800A4EA8 */
extern u8 g_tex_billboard_blue_env[]; /* was D_80090BAC */
extern u8 g_tex_billboard_white_env[]; /* was D_800908EC */

/* billboard_sprite_draw: P186: draws the camera-facing sprite of object record obj for player view `player`.
 * Texture obj +0x10 (word 0 = the image, or above 0x10000000 a frame table indexed by frame obj +0x1C >> 8;
 * byte +0xA = kind), position s16 obj +0x20 / +0x22 / +0x24, size s16 obj +0x34 (width) / +0x36 (height).
 * A negative width is a size scaled by how much the sprite faces the camera: |camera yaw (view +0x380) +
 * obj[0x1B] * 1.40625| folded into 0..90 degrees, times -width / 90, at least 1024. A negative height is
 * |view +0x388| * (max(width, 0) + height) / 90 - height. Render mode: flag 0x100 in u16 obj +0x44 takes the
 * combiner byte / g_render_mode_pairs entry from obj +0x14 (bit 0x200: +0x100000), otherwise by texture kind (5 with
 * flag 0x10: combiner 13 / entry 18, 5: combiner 15 / entry 17 / +0x100000, other: combiner 13 / entry 3).
 * Primitive colour obj +0x3C..0x3F, environment colour obj +0x40..0x42 (flag 1) or by texture (g_tex_billboard_blue_env
 * (128, 128, 255), g_tex_billboard_white_env white, else black). Returns the display list end. */
/* was func_15168118 */
s32 node_billboard_draw(s32 gdl, u8 *obj, s16 player) {
    struct {
        s16 x, y, z;
        s16 w, h;
    } quad;
    u8 flag;
    Gfx *gfx = (Gfx *) gdl;
    u8 *tex = *(u8 **) (obj + 0x10);
    u8 *view = (u8 *) g_player_views + player * 0x9A0;
    u16 flags;
    s32 img;
    s32 w, h;
    s32 *mode;
    f32 ang;
    u8 r, g, b;

    flag = 1;
    img = *(s32 *) tex;
    if ((u32) img >= 0x10000000) {
        img = ((s32 *) img)[*(s16 *) (obj + 0x1C) >> 8];
    }
    gfx = gfx_load_texture_cached(gfx, (s32) tex, *(s16 *) (obj + 0x1C) << 8, 2, 0x100, 0x100, img, 5, (s32) &quad, &flag, 3);

    quad.x = *(s16 *) (obj + 0x20);
    quad.y = *(s16 *) (obj + 0x22);
    quad.z = *(s16 *) (obj + 0x24);

    w = *(s16 *) (obj + 0x34);
    if (w < 0) {
        ang = fabsf(*(f32 *) (view + 0x380) + (f32) obj[0x1B] * 1.40625f);
        while (ang >= 360.0f) {
            ang -= 360.0f;
        }
        if (ang >= 180.0f) {
            ang -= 180.0f;
        }
        if (ang >= 90.0f) {
            ang = 180.0f - ang;
        }
        w = (s32) ((f32) w * ang * (-1.0f / 90.0f));
        if (w < 0x400) {
            w = 0x400;
        }
    }
    quad.w = w;

    h = *(s16 *) (obj + 0x36);
    if (h < 0) {
        w = *(s16 *) (obj + 0x34);
        if (w < 0) {
            w = 0;
        }
        h = (s32) (fabsf(*(f32 *) (view + 0x388)) * (f32) (w + h) * (1.0f / 90.0f) - (f32) h);
    }
    quad.h = h;

    flags = *(u16 *) (obj + 0x44);
    if (flags & 0x100) {
        u8 combine = obj[0x15];
        u8 entry = obj[0x17];

        gfx = gfx_geometry_mode_cached(gfx, 5, 0);
        gfx = gfx_set_combine_mode(gfx, combine, &flag);
        mode = &g_render_mode_pairs[entry * 2];
        gfx = gfx_other_mode_cached(gfx, ((flags & 0x200) ? 0x100000 : 0) | g_gfx_tlut_mode | 0x2CA0,
                            (mode[1] | mode[0]) | 4, &flag);
    } else if (tex[0xA] != 5) {
        gfx = gfx_set_combine_mode(gfx, 13, &flag);
        gfx = gfx_other_mode_cached(gfx, g_gfx_tlut_mode | 0x2CA0, (g_render_mode_pairs[3 * 2 + 1] | g_render_mode_pairs[3 * 2]) | 4, &flag);
    } else if (flags & 0x10) {
        /* (the asm also holds an unreachable kind 3 branch here: combiner 14 / entry 3) */
        gfx = gfx_set_combine_mode(gfx, 13, &flag);
        gfx = gfx_other_mode_cached(gfx, g_gfx_tlut_mode | 0x2CA0, (g_render_mode_pairs[18 * 2 + 1] | g_render_mode_pairs[18 * 2]) | 4, &flag);
    } else {
        gfx = gfx_set_combine_mode(gfx, 15, &flag);
        gfx = gfx_other_mode_cached(gfx, g_gfx_tlut_mode | 0x100000 | 0x2CA0, (g_render_mode_pairs[17 * 2 + 1] | g_render_mode_pairs[17 * 2]) | 4,
                            &flag);
    }

    gfx = gfx_prim_color_cached(gfx, 1, 0, obj[0x3C], obj[0x3D], obj[0x3E], obj[0x3F], &flag);
    if (flags & 1) {
        r = obj[0x40];
        g = obj[0x41];
        b = obj[0x42];
    } else if (*(u8 **) (obj + 0x10) == g_tex_billboard_blue_env) {
        r = 128;
        g = 128;
        b = 255;
    } else if (*(u8 **) (obj + 0x10) == g_tex_billboard_white_env) {
        r = 255;
        g = 255;
        b = 255;
    } else {
        r = g = b = 0;
    }
    gfx = gfx_env_color_cached(gfx, r, g, b, 0, &flag);
    return (s32) sprite_draw_at_world_depth(gfx, (u8 *) &quad);
}
/* P125 */
extern u8 *g_sprite_tex_descs[]; /* was D_8008CDEC */

/* sprite_quad_init: fills the two 4-vertex quads at the start of a sprite spawn record (8 Vtx, 0x80 bytes) with
 * colour (r, g, b, a) and flag 0, and their texture coordinates from the texture g_sprite_tex_descs[rec[0xA0]] (u16 width
 * +6, height +8; S10.5 coordinates (size + 256) << 5, the other edge 256 << 5). Record flags u16 +0x98: 0x80 flips
 * t, 0x100 flips s. Also clears the s16 at +0x88, +0x9C and +0x9E. The colour parameters are bytes. Returns the
 * last t value (what the asm leaves in v0; the callers, declared s32, ignore it). */
/* was func_1516865C */
s32 sprite_vtx_quads_init(u8 *rec, s32 r, s32 g, s32 b, s32 a) {
    Vtx *v = (Vtx *) rec;
    u8 *tex;
    u16 flags;
    s16 s0, s1, t0, t1;
    s32 i;

    tex = g_sprite_tex_descs[rec[0xA0]];
    s0 = 0x2000;
    t0 = 0x2000;
    s1 = (*(u16 *) (tex + 6) + 0x100) << 5;
    t1 = (*(u16 *) (tex + 8) + 0x100) << 5;
    for (i = 0; i < 8; i++) {
        v[i].v.flag = 0;
        v[i].v.cn[0] = r;
        v[i].v.cn[1] = g;
        v[i].v.cn[2] = b;
        v[i].v.cn[3] = a;
    }
    flags = *(u16 *) (rec + 0x98);
    if (flags & 0x80) {
        t1 = 0x2000;
        t0 = (*(u16 *) (g_sprite_tex_descs[rec[0xA0]] + 8) + 0x100) << 5;
    }
    if (flags & 0x100) {
        s1 = 0x2000;
        s0 = (*(u16 *) (g_sprite_tex_descs[rec[0xA0]] + 6) + 0x100) << 5;
    }
    v[6].v.tc[0] = s0;
    v[7].v.tc[1] = t0;
    v[7].v.tc[0] = s1;
    v[1].v.tc[0] = v[5].v.tc[0] = v[2].v.tc[0] = v[6].v.tc[0];
    v[5].v.tc[1] = t1;
    *(s16 *) (rec + 0x88) = 0;
    v[2].v.tc[1] = v[6].v.tc[1] = v[3].v.tc[1] = v[7].v.tc[1];
    *(s16 *) (rec + 0x9C) = 0;
    *(s16 *) (rec + 0x9E) = 0;
    v[0].v.tc[0] = v[4].v.tc[0] = v[3].v.tc[0] = v[7].v.tc[0];
    v[0].v.tc[1] = v[4].v.tc[1] = v[1].v.tc[1] = v[5].v.tc[1];
    return t0;
}
/* was func_15168800 */
void *node_spawn_vtx_sprite(void *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0 = node_alloc(0xE, arg2, 0xB8, 1, arg1, 1);

    if (temp_v0 == NULL) {
        return NULL;
    }
    bcopy(arg0, temp_v0 + 0x10, 0xA8);
    return temp_v0;
}
extern u8 *g_sprite_tex_descs[]; /* was D_8008CDEC */
extern void (*g_node_sprite_behaviours[])(u8 *); /* was D_8008CD68 */

/* was func_15168870 */
void node_vtx_sprite_update(u8 *arg0) {
    s16 speed = *(s16 *)(arg0 + 0x9A);
    s32 len;
    s8 w;
    s32 t;

    if (speed != 0) {
        t = g_sprite_tex_descs[arg0[0xB0]][4];
        len = (t << 8) - 1;
        *(s16 *)(arg0 + 0x98) += speed * g_frame_ticks;
        if (*(s16 *)(arg0 + 0x98) > len) {
            if (*(u16 *)(arg0 + 0xA8) & 0x40) {
                *(s16 *)(arg0 + 0x98) = len - *(s16 *)(arg0 + 0x98) % len;
                *(s16 *)(arg0 + 0x9A) = -speed;
            } else if (*(u16 *)(arg0 + 0xA8) & 4) {
                *(s16 *)(arg0 + 0x98) = -1;
            } else {
                do {
                    *(s16 *)(arg0 + 0x98) -= len;
                } while (*(s16 *)(arg0 + 0x98) > len);
            }
        } else if (*(s16 *)(arg0 + 0x98) < 0) {
            if (*(u16 *)(arg0 + 0xA8) & 0x40) {
                *(s16 *)(arg0 + 0x98) = -*(s16 *)(arg0 + 0x98) % len;
                *(s16 *)(arg0 + 0x9A) = -speed;
            } else if (*(u16 *)(arg0 + 0xA8) & 4) {
                *(s16 *)(arg0 + 0x98) = -1;
            } else {
                do {
                    *(s16 *)(arg0 + 0x98) += len;
                } while (*(s16 *)(arg0 + 0x98) < 0);
            }
        }
    }
    w = arg0[0xB2];
    if (w != -1 && g_node_sprite_behaviours[w] != NULL) {
        g_node_sprite_behaviours[w](arg0);
    }
    if (*(s16 *)(arg0 + 0x98) == -1) {
        node_destroy((struct102 *)arg0);
    }
}
/* was func_15168A2C */
void node_move_to_list0(s32 arg0) {
    node_set_type(arg0, 0);
}
/* was func_15168A4C */
void node_list_insert(struct_eu_node *arg0, s32 arg1) {
    s32 group = arg0->unk1;
    struct_eu_node **head = &g_node_lists[group][arg1];

    arg0->next = *head;
    if (arg0->next != NULL) {
        arg0->next->prev = arg0;
    }
    arg0->unk0 = arg1;
    arg0->prev = NULL;
    *head = arg0;
}
/* was func_15168A9C */
void node_list_unlink(struct_eu_node *arg0) {
    s32 group = arg0->unk1;
    s32 idx = arg0->unk0;
    struct_eu_node **head = &g_node_lists[group][idx];

    if (arg0 == *head) {
        *head = arg0->next;
    }
    if (arg0->next != NULL) {
        arg0->next->prev = arg0->prev;
    }
    if (arg0->prev != NULL) {
        arg0->prev->next = arg0->next;
    }
}

/* was func_15168B10 */
void node_set_type(s32 arg0, s32 arg1) {
    node_list_unlink(arg0);
    node_list_insert(arg0, arg1);
}

/* was func_15168B44 */
void node_fade_delay_update(u8 *arg0) {
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v1;
    u8 temp_a2;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x14));
    temp_t6 = temp_v1 & 0xFFFF;
    if (temp_t6 != 0) {
        temp_t9 = temp_v1 & 0xFFFF0000;
        (*(s32 *)((u8 *)arg0 + 0x14)) = temp_t9;
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0x1E;
        (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (temp_t9 | ((temp_t6 - 1) & 0xFFFF));
        return;
    }
    temp_a2 = (*(u8 *)((u8 *)arg0 + 0x3F));
    temp_t2 = (temp_v1 >> 0x10) & 0xFFFF;
    if (temp_t2 < (s32) temp_a2) {
        (*(u8 *)((u8 *)arg0 + 0x3F)) = (u8) (temp_a2 - temp_t2);
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0x1E;
        return;
    }
    (*(s16 *)((u8 *)arg0 + 0x38)) = 0;
}
/* was func_15168BAC */
void node_run_end_callback(u8 *arg0) {
    u8 idx = arg0[0xE4];
    if (idx != 0) {
        g_node_end_handlers[idx]();
    }
}
/* was func_15168BE4 */
void node_spawn_model_fx(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0;

    if (((s32 *)arg0)[0x40 / 4] != 0) {
        temp_v0 = node_alloc(0x10, arg2, 0xF0, 1, arg1, 1);
        if (temp_v0 != NULL) {
            bcopy(arg0, temp_v0 + 0x90, 0x60);
        }
    }
}
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);
extern s16 g_gfx_prim_r_cached; /* was D_800DD5F0 */
extern s16 g_gfx_prim_g_cached; /* was D_800DD5F2 */
extern s16 g_gfx_prim_b_cached; /* was D_800DD5F4 */
extern s16 g_gfx_prim_a_cached; /* was D_800DD5F6 */

/* was func_15168C4C */
Gfx *node_model_fx_draw(Gfx *gfx, u8 *arg1, s32 arg2) {
    s32 pad; // fakematch: frame
    s32 mode;
    u8 flag;
    s32 pad2; // fakematch: frame

    mtx_build_rot_scale_trans(&((Mtx *)(arg1 + 0x10))[g_dl_buf_index], *(f32 *)(arg1 + 0x9C), *(f32 *)(arg1 + 0xA0), *(f32 *)(arg1 + 0xA4), *(f32 *)(arg1 + 0xC0), *(f32 *)(arg1 + 0xC4), *(f32 *)(arg1 + 0xC8), *(f32 *)(arg1 + 0x90), *(f32 *)(arg1 + 0x94), *(f32 *)(arg1 + 0x98));
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, arg1[0xE5]);
    g_gfx_prim_a_cached = arg1[0xE5];
    g_gfx_prim_r_cached = g_gfx_prim_g_cached = g_gfx_prim_b_cached = 0;
    gDPSetEnvColor(gfx++, 0, 0, 0, 0);
    gDPSetTileSize(gfx++, 0, 2, arg1[0xE6], 0x7E, 0xFE);
    switch (arg1[0xEC]) {
    case 1:
        mode = 0x552230;
        break;
    case 2:
        mode = 0x504A50;
        break;
    }
    flag = 0;
    gfx = gfx_other_mode_cached(gfx, 0x8ACA0, mode, &flag);
    if (arg1[0xED] == 1) {
        gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0);
    }
    gSPMatrix(gfx++, &((Mtx *)(arg1 + 0x10))[g_dl_buf_index], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, *(Gfx **)(arg1 + 0xD0));
    return gfx;
}
/* was func_15168E34 */
void gfx_addr_add_offset(s32 *arg0, s32 arg1) {
    s32 temp_v0 = *arg0;
    if (!(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
/* was func_15168E54 */
void gfx_dl_relocate(s8 *arg0, s32 arg1) {
    s32 var_s0;
    s8 *var_v1;
    s8 var_v0;

    var_s0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_v0 = *arg0;
        do {
            if ((var_v0 == 1) || ((var_v0 == -0x24) && ((*(u8 *)((u8 *)var_v1 + 3)) == 0xE))) {
                gfx_addr_add_offset(var_v1 + 4, arg1);
            }
            var_s0 += 1;
            var_v1 = (var_s0 * 8) + arg0;
            var_v0 = *var_v1;
        } while (var_v0 != -0x21);
    }
}
// NON-MATCHING: first cmd load is CSE'd in mine
// void gfx_dl_relocate(struct_eu_gfxcmd *arg0, s32 arg1) {
//     s32 i = 0;
//     struct_eu_gfxcmd *gfx = arg0;
//     s32 cmd = gfx->cmd;
//
//     while (cmd != -0x21) {
//         cmd = gfx->cmd;
//         if (cmd == 1 || (cmd == -0x24 && gfx->b3 == 0xE)) {
//             gfx_addr_add_offset(&gfx->w1, arg1);
//         }
//         i++;
//         gfx = &arg0[i];
//         cmd = gfx->cmd;
//     }
// }

/* was func_15168F08 */
void gfx_dl_rebase(struct_eu_gfxcmd *arg0, s32 arg1) {
    s32 i = 0;
    struct_eu_gfxcmd *gfx = arg0;

    while (gfx->cmd != -0x21) {
        i++;
        if (gfx->cmd == 1 || (gfx->cmd == -0x24 && gfx->b3 == 0xE)) {
            gfx->w1 &= 0xFFFFFF;
            gfx->w1 += arg1;
        }
        gfx = &arg0[i];
        goto next; // fakematch: label at the end of the loop body
    next:;
    }
}

/* was func_15168F84 */
void render_group_layer_range(s32 arg0, s32 *arg1, s32 *arg2) {
    if (arg0 == 0) {
        *arg1 = 1;
        *arg2 = 0x41;
    } else if (arg0 == 1) {
        *arg1 = 0x42;
        *arg2 = 0x4F;
    } else if (arg0 == 2) {
        *arg1 = 0x50;
        *arg2 = 0x58;
    } else if (arg0 == 3) {
        *arg1 = 0x59;
        *arg2 = 0x5C;
    } else if (arg0 == 5) {
        *arg1 = 0x61;
        *arg2 = 0x63;
    } else if (arg0 == 6) {
        *arg1 = 0x64;
        *arg2 = 0x65;
    } else {
        *arg1 = 0x5D;
        *arg2 = 0x60;
    }
}
/* was func_15169040 */
void node_broadcast_all(s32 arg0, u8 arg1) {
    node_broadcast_range(0, 0x68, arg0, arg1);
}
void node_free_if_owner_msg(struct102 *arg0, u8 *arg1, u8 arg2);
void clamp_range_to_bounds(s32 *, s32 *, s32, s32);
/* was func_15169070 */
void node_broadcast_range(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 j;
    s32 i;

    clamp_range_to_bounds(&arg0, &arg1, 2, 0x68);
    for (j = arg0; j < arg1; j++) {
        struct_eu_node *node;

        for (i = 0; i < 2; i++) {
            if (g_node_type_table[j].fn != NULL) {
                node = g_node_lists[i][j];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    node_free_if_owner_msg((struct102 *)node, (u8 *)arg2, arg3);
                    g_node_type_table[j].fn(node, arg2, arg3);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            } else {
                node = g_node_lists[i][j];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    node_free_if_owner_msg((struct102 *)node, (u8 *)arg2, arg3);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            }
        }
    }
}
/* P136 */
/*
 * node_lists_update_types: for each of the n type ids in types[] (arg0), walks that type's node lists in both rows of
 * g_node_lists and calls node_free_if_owner_msg(node, arg2, arg3) on every node, then the type's g_node_type_table handler (+0x1C)
 * when it has one. The next node is kept in g_node_iter_next[++g_node_iter_depth] (as node_broadcast_range) so a call may unlink or
 * free the current node or the saved next one.
 */
/* was func_15169260 */
void node_broadcast_types(void *arg0, s32 n, s32 arg2, u8 arg3) {
    s32 *types = arg0;
    struct_eu_node *node;
    s32 k;
    s32 i;

    for (k = 0; k < n; k++, types++) {
        for (i = 0; i < 2; i++) {
            if (g_node_type_table[*types].fn != NULL) {
                node = g_node_lists[i][*types];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    node_free_if_owner_msg((struct102 *) node, (u8 *) arg2, arg3);
                    g_node_type_table[*types].fn(node, arg2, arg3);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            } else {
                node = g_node_lists[i][*types];
                g_node_iter_depth++;
                while (node != NULL) {
                    g_node_iter_next[g_node_iter_depth] = node->next;
                    node_free_if_owner_msg((struct102 *) node, (u8 *) arg2, arg3);
                    node = g_node_iter_next[g_node_iter_depth];
                }
                g_node_iter_depth--;
            }
        }
    }
}
void node_free_if_owner_msg(struct102 *arg0, u8 *arg1, u8 arg2);
/* was func_1516944C */
void node_broadcast_type(s32 j, s32 arg1, u8 arg2) {
    s32 i;
    struct_eu_node *node;

    if (j >= 0x68) {
        j = 0x67;
    }
    for (i = 0; i < 2; i++) {
        if (g_node_type_table[j].fn != NULL) {
            node = g_node_lists[i][j];
            g_node_iter_depth++;
            while (node != NULL) {
                g_node_iter_next[g_node_iter_depth] = node->next;
                node_free_if_owner_msg((struct102 *)node, (u8 *)arg1, arg2);
                g_node_type_table[j].fn(node, arg1, arg2);
                node = g_node_iter_next[g_node_iter_depth];
            }
            g_node_iter_depth--;
        } else {
            node = g_node_lists[i][j];
            g_node_iter_depth++;
            while (node != NULL) {
                g_node_iter_next[g_node_iter_depth] = node->next;
                node_free_if_owner_msg((struct102 *)node, (u8 *)arg1, arg2);
                node = g_node_iter_next[g_node_iter_depth];
            }
            g_node_iter_depth--;
        }
    }
}
/* was func_151695F0 */
void node_broadcast_obj_all(u8 *arg0, u8 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    node_broadcast_all(&tmp, arg1);
}
/* was func_1516962C */
void node_broadcast_obj_type(s32 arg0, u8 *arg1, u8 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg1;
    tmp.unk4 = arg1[0x3B];
    node_broadcast_type(arg0, &tmp, arg2);
}
/* was func_15169668 */
s32 render_layer_pre_set_flag(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    g_sprite_keep_prim_colour = 1;
    return arg0;
}
/* was func_1516968C */
void node_free_if_owner_msg(struct102 *arg0, u8 *arg1, u8 arg2) {
    if ((arg2 == 15 || arg2 == 16) && *arg1 == ((u8 *)arg0)[0xC]) {
        node_destroy(arg0);
    }
}
/* was func_151696DC */
void node_walk_skip_node(struct_eu_node *arg0) {
    s8 i;

    for (i = 0; i < g_node_iter_depth; i++) {
        if (arg0 == g_node_iter_next[i]) {
            g_node_iter_next[i] = arg0->next;
        }
    }
}

/* was func_1516972C */
void node_destroy(struct102 *arg0) {
    void (*func)(struct102 *arg0);
    node_walk_skip_node(arg0);

    if (arg0->unk0 >= 2) {
        func = g_node_type_destroy_fns[arg0->unk0].unk0;
        if (func != NULL) {
            func(arg0);
            return;
        }
        node_retire(arg0);
    }
}

/* was func_1516979C */
void node_delete(struct102 *arg0) {
    void (*func)(struct102 *arg0);

    node_walk_skip_node(arg0);
    func = g_node_type_delete_fns[arg0->unk0].unk0;
    if (func != NULL) {
        func(arg0);
        return;
    }
    node_unlink_free(arg0);
}

/* was func_15169804 */
void node_retire(struct102 *arg0) {
    node_set_type(arg0, 1);
}

/* was func_15169824 */
void node_unlink_free(struct102 *arg0) {
    node_list_unlink(arg0);
    heap_free(arg0);
}

/* was func_15169850 */
s32 node_handle_link_message(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_v1;

    if (arg1 == 0) {
        if ((*(s32 *)(arg0 + 0) == *(s32 *)arg2) || (*(u8 *)(arg0 + 4) == *(u8 *)arg3)) {
            node_destroy((struct102 *)arg4);
        }
    } else if (arg1 == 0x2D) {
        temp_v1 = *(s32 *)(arg0 + 0);
        if (temp_v1 == *(s32 *)arg2) {
            *(s32 *)arg2 = *(s32 *)(arg0 + 4);
            *(u8 *)arg3 = *(u8 *)(arg0 + 9);
            return;
        }
        if (*(s32 *)(arg0 + 4) == *(s32 *)arg2) {
            *(s32 *)arg2 = temp_v1;
            *(u8 *)arg3 = *(u8 *)(arg0 + 8);
        }
    }
}
// NON-MATCHING: regalloc (v0/v1 swapped)
// void node_handle_link_message(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
//     s32 *a = (s32 *)arg0;
//     s32 *b = (s32 *)arg2;
//     u8 *c = (u8 *)arg3;
//
//     if (arg1 == 0) {
//         if (a[0] == *b || ((u8 *)a)[4] == *c) {
//             node_destroy((struct102 *)arg4);
//         }
//     } else if (arg1 == 0x2D) {
//         if (a[0] == *b) {
//             *b = a[1];
//             *c = ((u8 *)a)[9];
//         } else if (*b == a[1]) {
//             *b = a[0];
//             *c = ((u8 *)a)[8];
//         }
//     }
// }
