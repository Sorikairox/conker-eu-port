#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// mesh_effect_spawn: spawns an animated mesh effect record (P195). The 0x3C-byte spawn block p (copied to rec + 0x10) names
// a model by its +0x30 / +0x34 words (asset_load_with_subfiles, kind 2 lookup); the model header starts with its display list
// pointer, followed at +0x28 by the vertex block (size = dl - header - 0x28). The record (kind 0x54 when arg1 != 0,
// else 0x38; node_alloc with group arg4 and priority arg3) gets D_80082FA0 + 1 double-buffered vertex copies at
// +0xF8 (+0x58[i] / +0x68[i] point at the two halves), +0x4C = header, +0x50 = the copies' size, +0x54 = the display
// list, which is registered with texture_resolve_dl_ids (age 0x3E). arg2 extra bytes follow the copies. Returns NULL when the
// pool is full. Callers: level_obj_init_debris_table (ambient fires), swing_lamp_spawn, water_effect_spawn, game_eu_1E7CC0.
s32 asset_load_with_subfiles(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 texture_resolve_dl_ids(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
void *node_alloc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5);
void *memcpy(void *, const void *, s32);

/* was func_1513B5E0 */
struct102 *mesh_effect_spawn(void *p, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 found;
    s32 count;
    u8 *hdr;
    u8 *rec;
    u8 *dst;
    s32 size;
    s32 total;
    s32 i;

    hdr = (u8 *) asset_load_with_subfiles(&found, 0, &count, 2, *(s32 *) ((u8 *) p + 0x30), *(s32 *) ((u8 *) p + 0x34));
    size = *(s32 *) hdr - (s32) hdr - 0x28;
    total = size * 2 * (D_80082FA0 + 1);
    rec = node_alloc(arg1 ? 0x54 : 0x38, arg4, arg2 + total + 0xF8, 2, arg3, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, p, 0x3C);
    *(u8 **) (rec + 0x4C) = hdr;
    dst = rec + 0xF8;
    for (i = 0; i <= D_80082FA0; i++) {
        ((u8 **) (rec + 0x58))[i] = dst;
        ((u8 **) (rec + 0x68))[i] = dst + size;
        memcpy(dst, hdr + 0x28, size);
        memcpy(((u8 **) (rec + 0x68))[i], hdr + 0x28, size);
        dst += size * 2;
    }
    *(s32 *) (rec + 0x54) = *(s32 *) hdr;
    *(s32 *) (rec + 0x50) = total;
    texture_resolve_dl_ids(*(Gfx **) hdr, 0, 1, 0x3E, NULL);
    return (struct102 *) rec;
}
/* was func_1513B798 */
void mesh_effect_update(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0x10] & 1) != 0) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0x11) != -1) && (g_mesh_effect_tick_fns[*(s8 *)(arg0 + 0x11)](arg0) == 0)) {
        ret = 1;
    }
    if (ret) {
        node_destroy(arg0);
    }
}
// NON-MATCHING: only the stack slot of done differs (0x1B vs 0x1F)
// void mesh_effect_update(struct_eu_168A90 *arg0) {
//     u8 done;
//
//     done = FALSE;
//     if (arg0->unk10 & 1) {
//         arg0->unk14 -= D_800BE9E4;
//         if (arg0->unk14 < 0) {
//             done = TRUE;
//         }
//     }
//     if (!done) {
//         if (arg0->unk11 != -1) {
//             if (g_mesh_effect_tick_fns[arg0->unk11](arg0) == 0) {
//                 done = TRUE;
//             }
//         }
//     }
//     if (done) {
//         node_destroy(arg0);
//     }
// }
extern s32 g_mesh_effect_draw_fns; /* was D_80089FC8 */

/* was func_1513B83C */
u8 *mesh_effect_draw(u8 *arg0, u8 *arg1, s16 arg2) {
    s16 var_a2;
    s32 temp_v0_2;
    s8 temp_v0;
    u8 *temp_a3;
    u8 *temp_a3_2;

    var_a2 = arg2;
    if (((*(u8 *)((u8 *)arg1 + 0x10)) & 2) && !((*(u8 *)((u8 *)arg1 + 0x49)) & (1 << var_a2))) {
        return arg0;
    }
    temp_v0 = (*(s8 *)((u8 *)arg1 + 0x12));
    if (temp_v0 != -1) {
        arg2 = var_a2;
        // P250: the handlers (sky_dome_project_uv, object_screen_uv_project) are s32 (u8 *, s32); a2 / a3 are only leftovers in the asm
        temp_v0_2 = ((s32 (**)(u8 *, s32)) &g_mesh_effect_draw_fns)[temp_v0](arg1, var_a2);
        var_a2 = arg2;
        if (temp_v0_2 == 0) {
            return arg0;
        }
    }
    (*(s32 *)((u8 *)arg0 + 0)) = 0xDA380003;
    temp_a3_2 = arg0 + 8;
    (*(u8 **)((u8 *)arg0 + 4)) = (u8 *) (arg1 + (D_800BE9C0 << 6) + 0x78);
    (*(s32 *)((u8 *)temp_a3_2 + 0)) = 0xDB060004;
    temp_a3 = temp_a3_2 + 8;
    (*(s32 *)((u8 *)temp_a3_2 + 4)) = (s32) (*(s32 *)((u8 *)((arg1 + (D_800BE9C0 * 0x10) + (var_a2 * 4))) + 0x58));
    (*(s32 *)((u8 *)temp_a3 + 0)) = 0xDE000000;
    (*(s32 *)((u8 *)temp_a3 + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 0x54));
    return temp_a3 + 8;
}
/* was func_1513B968 */
s32 mesh_effect_load_identity(s32 arg0, s32 arg1) {
    // FIXME: &arg0->unk_120[D_800BE9C0]
    mtx_set_identity(arg0 + 120 + (D_800BE9C0 << 6));
    return 1;
}

/* was func_1513B9A8 */
void mesh_effect_retire(struct132 *arg0) {
    heap_set_block_tag(arg0->unk4C, 4);
    node_retire(arg0);
}

/* was func_1513B9DC */
void mesh_effect_free(struct132 *arg0) {
    heap_set_block_tag(arg0->unk4C, 4);
    node_unlink_free(arg0);
}

// object_mode_dispatch_a: runs the g_object_mode_fns_a handler picked by the object's +0x48 byte on the object. The asm leaves
// the object in a0 at the jalr; every entry (mesh_effect_retire x4) is void (struct132 *), so no result is passed on.
/* was func_1513BA10 */
void object_mode_dispatch_a(struct132 *arg0) {
    ((void (*)(struct132 *)) g_object_mode_fns_a[arg0->unk48])(arg0);
}

// object_mode_dispatch_b: as object_mode_dispatch_a with the table g_object_mode_fns_b (mesh_effect_free x4).
/* was func_1513BA44 */
void object_mode_dispatch_b(struct132 *arg0) {
    ((void (*)(struct132 *)) g_object_mode_fns_b[arg0->unk48])(arg0);
}

/* was func_1513BA78 */
void mesh_effect_on_msg(u8 *arg0, s32 arg1, u8 arg2) {
    switch (arg0[0x48]) {
    case 1:
        swing_lamp_handle_event(arg0, arg1, arg2);
        break;
    case 2:
        screen_uv_mesh_handle_message(arg0, arg1, arg2);
        break;
    }
}

/* was func_1513BAD4 */
s32 mesh_effect_handler_false(s32 arg0, s32 arg1) {
    return 0;
}

typedef struct { u8 pad[0x50]; s32 off; u8 pad54[0xA4]; u8 data[1]; } BAE8Obj;
typedef struct {
    s8 b0; s8 b1; s8 b2; s8 pad3;
    s16 h4; s16 pad6;
    s32 w8; s32 wC; s32 w10; s32 w14; s32 w18; s32 w1C; s32 w20;
    s8 b24; s8 b25; s8 pad26[2];
    s32 w28; s32 w2C;
    s32 w30; s32 w34;
    s8 b38; s8 pad39[3];
} BAE8Params;
void *memcpy(void *, const void *, s32);
/* was func_1513BAE8 */
struct102 *water_effect_spawn(void) {
    struct102 *p;
    BAE8Params s;
    f32 f[5];

    s.b1 = 2;
    s.b2 = 5;
    s.h4 = 0x12C;
    s.w30 = 9;
    f[0] = 0.0f;
    f[1] = 0.0f;
    f[3] = 0.0f;
    f[4] = 0.0f;
    f[2] = 0.0f;
    s.b0 = 0;
    s.w34 = 0x1AE;
    s.w8 = 1;
    s.wC = 0x220205;
    s.w10 = 0x40600;
    s.b24 = 0;
    s.b25 = 0;
    s.w14 = 1;
    s.w18 = 0x36;
    s.w1C = 0x80;
    s.w20 = 0x20;
    s.b38 = 3;
    p = mesh_effect_spawn(&s, 1, 0x14, 0xFF, 1);
    if (p != NULL) {
        if (*(s32 *)((u8 *)p + 0x50) != 0x1180) {
            node_destroy(p);
        } else {
            memcpy(&((BAE8Obj *)p)->data[((BAE8Obj *)p)->off], f, 0x14);
        }
    }
    return p;
}
float sqrtf(float);
extern f32 g_water_proj_centres[9][3];    // the nine texture-projection centres /* was D_800A4DA0 */
extern s32 g_water_proj_vtx_ranges[9][2];    // their vertex ranges { first, count } /* was D_800A4E0C */
extern f32 g_water_s_scale_amp;          // 1.21f /* was D_800A4E54 */
extern f32 g_water_s_scale_base;          // 2.854f /* was D_800A4E58 */
extern f32 g_water_t_scale_amp;          // 1.994f /* was D_800A4E5C */
extern f32 g_water_t_scale_base;          // 8.328f /* was D_800A4E60 */

// water_texcoords_update: object-type handler (table g_mesh_effect_draw_fns + 0x14). Calls mesh_effect_load_identity first, then rewrites the
// texture coordinates of the nine vertex groups of the object's current vertex buffer (obj + 0x58 + D_800BE9C0 * 16
// + part * 4) so each group's texture faces the player camera point (camera_get_pos(part)) seen from its centre
// g_water_proj_centres[k]: s = horizontal offset along the camera direction * (sin(rec + 0xC) * 1.21 + 2.854) - scroll u,
// t = height * (sin(rec + 0x10) * 1.994 + 8.328) - scroll v, where rec = obj + obj[0x50] + 0xF8 holds the scroll
// (+0 / +4, taken mod 1024) and the two wave phases. Returns 1.
/* was func_1513BBFC */
s32 water_texcoords_update(s32 obj, s16 part) {
    f32 *rec;
    f32 *cam;
    f32 scaleS;
    f32 scaleT;
    f32 scrollS;
    f32 scrollT;
    f32 dx;
    f32 dz;
    f32 inv;
    f32 dirX;
    f32 dirZ;
    Vtx_t *v;
    s32 k;
    s32 n;

    mesh_effect_load_identity(obj, part);
    rec = (f32 *) (obj + *(s32 *) (obj + 0x50) + 0xF8);
    scaleS = sinf(rec[3]) * g_water_s_scale_amp + g_water_s_scale_base;
    scaleT = sinf(rec[4]) * g_water_t_scale_amp + g_water_t_scale_base;
    cam = camera_get_pos(part);
    scrollS = rec[0] - (f32) (s32) (rec[0] * (1.0f / 1024.0f)) * 1024.0f;
    scrollT = rec[1] - (f32) (s32) (rec[1] * (1.0f / 1024.0f)) * 1024.0f;
    for (k = 0; k < 9; k++) {
        dx = g_water_proj_centres[k][0] - cam[0];
        dz = g_water_proj_centres[k][2] - cam[2];
        if (dx == 0.0f && dz == 0.0f) {
            dirX = 1.0f;
            dirZ = 0.0f;
        } else {
            inv = 1.0f / sqrtf(dx * dx + dz * dz);
            dirX = dz * inv;
            dirZ = -dx * inv;
        }
        for (n = g_water_proj_vtx_ranges[k][0]; n < g_water_proj_vtx_ranges[k][0] + g_water_proj_vtx_ranges[k][1]; n++) {
            v = (Vtx_t *) (*(u8 **) (obj + 0x58 + D_800BE9C0 * 16 + part * 4) + n * 16);
            v->tc[0] = (s32) ((((f32) v->ob[0] - g_water_proj_centres[k][0]) * dirX + ((f32) v->ob[2] - g_water_proj_centres[k][2]) * dirZ) *
                                  scaleS - scrollS);
            v->tc[1] = (s32) (((f32) v->ob[1] - g_water_proj_centres[k][1]) * scaleT - scrollT);
        }
    }
    return 1;
}
extern f32 g_water_wave_rate_c; // 0.037f (file does not own .rodata) /* was D_800A4E64 */
extern f32 g_water_wave_rate_a; // 1.9f /* was D_800A4E68 */
extern f32 g_water_wave_amp_b; // 77.3f /* was D_800A4E6C */
extern f32 g_water_wave_rate_d; // 0.019f /* was D_800A4E70 */
extern f32 g_water_wave_rate_e; // 0.01f /* was D_800A4E74 */
typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
} Wave1513BEB0;

/* was func_1513BEB0 */
s32 water_wave_update(u8 *arg0) {
    f32 f;
    Wave1513BEB0 *w = (Wave1513BEB0 *)(arg0 + *(s32 *)(arg0 + 0x50) + (0, 0xF8)); // fakematch: comma keeps addu a0,t6 order

    w->c += g_water_wave_rate_c * D_800BE9A4;
    f = wrap_angle_rad(w->c);
    w->c = f;
    w->a += g_water_wave_rate_a * D_800BE9A4;
    w->b = sinf(f) * g_water_wave_amp_b;
    w->d += g_water_wave_rate_d * D_800BE9A4;
    w->e += g_water_wave_rate_e * D_800BE9A4;
    w->d = wrap_angle_rad(w->d);
    w->e = wrap_angle_rad(w->e);
    while (w->a > 4096.0f) {
        w->a -= 4096.0f;
    }
    while (w->a < 0.0f) {
        w->a += 4096.0f;
    }
    while (w->b > 4096.0f) {
        w->b -= 4096.0f;
    }
    while (w->b < 0.0f) {
        w->b += 4096.0f;
    }
    return 1;
}
