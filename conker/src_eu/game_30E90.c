#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
s32 asset_load_with_subfiles(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 asset_load_ptr(s32 *arg0, s32 arg1, ...);
s32 texture_resolve_dl_ids(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
s32 world_object_alloc_id(s32 arg0);
void gfx_dl_relocate_seg_e(Gfx *arg0, s32 arg1);
void world_object_calc_radius(u8 *arg0, s32 arg1);
extern u16 g_world_obj_radius_small_cnt; /* was D_800BE6C0 */
extern u16 g_world_obj_radius_set_cnt; /* was D_800BE6C2 */
extern u16 g_world_obj_radius_ok_cnt; /* was D_800BE6C4 */
extern s32 D_80089030[][3];        /* per object type: callback +0x38, +0x78, byte +0x92 */
extern u8 g_world_obj_model_records[];            /* per model id: 12-byte display records (multiplayer objects); was D_800A2A90 */
extern u8 **g_level_model_entries;            /* level model segments, 8-byte entries: word 0 = segment; was D_800B1260 */
extern void *g_world_obj_view_words[4]; /* was D_800DC300 */
extern void *g_world_obj_mtx_a; /* was D_800DC310 */
extern void *g_world_obj_mtx_b; /* was D_800DC314 */
extern u8 g_world_obj_state_3b8; /* was D_800DC3B8 */
extern s32 *g_world_obj_rider_masks; /* was D_800DC3C4 */
extern s32 g_world_obj_mp_count; /* was D_800DC3C8 */

#define WOBJ(i) ((u8 *) g_world_objs + (i) * 0xA0)
#define W8(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define W16(p, o) (*(u16 *) ((u8 *) (p) + (o)))
#define S16(p, o) (*(s16 *) ((u8 *) (p) + (o)))
#define W32(p, o) (*(s32 *) ((u8 *) (p) + (o)))
#define WPTR(p, o) (*(u8 **) ((u8 *) (p) + (o)))
#define WF32(p, o) (*(f32 *) ((u8 *) (p) + (o)))

/* world_objects_load: builds the level's world objects (0xA0-byte records at g_world_objs, count g_world_obj_count) from
 * the level's two 0x44-byte placement lists (asset 2/0xB/level: g_world_obj_level_count level objects, asset 3/0xC/level/2:
 * g_world_obj_mp_count multiplayer objects). Per object: position (s16 +0x10..), origin floats, scale, the type's callback
 * table D_80089030 (types < 0xFFFF; 0x28 / 0x42 set the +0x70 bit 2 and keep it for the next multiplayer ones, type
 * 0x16 = "has a callback"), its model: an earlier object with the same key (+0xC / +0x10) shares its vertices /
 * display list, else the model is loaded (asset_load_with_subfiles 3/id, kind 0 in +0x1C) or taken from the level segments
 * g_level_model_entries (kind 1 / 2). Then the vertex buffers (+0x20 / +0x24 copies for moving objects, bit 0 of +0x70),
 * the per-object arrays g_world_obj_mtx_a / 314 / 328 / 32C / 300[4] / 3C4, and object ids +0x72 (world_object_alloc_id).
 * arg1 is unused. Literal quirks kept: the model segment `seg` is only loaded for kind-0 objects but is also passed
 * to gfx_dl_relocate_seg_e for kind 1 / 2 / other objects without a shared model (the asm keeps it in s6 from the previous
 * kind-0 object; uninitialised stack before the first one: NULL here); a type >= 0xFFFF is stored as the callback. */
/* was func_150039E0 */
void world_objects_load(s32 arg0, s32 arg1) {
    s32 bufA;          /* sp+0xA0: level placement list */
    s32 bufB;          /* sp+0x9C: multiplayer placement list */
    s32 found;         /* sp+0xA8 */
    u8 *base;          /* s7: list base so that base + i * 0x44 is object i's placement record */
    u8 *src;
    u8 *obj;
    u8 *prev;
    u8 *seg = NULL;    /* s6 */
    u8 *lseg = NULL;   /* fp */
    u8 *e;
    u8 *s;
    s32 i, j, k;
    s32 link;          /* s4: index + 1 of the object whose model is shared, 0 = none */
    s32 hasCb;         /* sp+0x84 */
    s8 keepBit2;       /* sp+0x8B */
    s32 type;
    s32 id;
    s32 kind;
    s32 nA, nB;

    g_world_obj_state_3b8 = 0xFF;
    g_world_obj_radius_set_cnt = 0;
    g_world_obj_radius_ok_cnt = 0;
    bufA = 0;
    bufB = 0;
    keepBit2 = 0;
    g_world_obj_radius_small_cnt = 0;
    nA = (u32) asset_load_ptr(&bufA, 2, 0xB, arg0) / 0x44;
    g_world_obj_level_count = nA;
    g_world_obj_count = g_world_obj_level_count;
    nB = (u32) asset_load_ptr(&bufB, 3, 0xC, arg0, 2) / 0x44;
    g_world_obj_mp_count = nB;
    g_world_obj_count = g_world_obj_count + nB;
    g_world_objs = allocate_memory(g_world_obj_count * 0xA0, 1, 2, 0);
    if (g_world_objs == NULL) {
        g_world_obj_count = 0;
        g_world_obj_mp_count = 0;
        g_world_obj_level_count = 0;
        return;
    }

    base = (u8 *) bufA;
    for (i = 0; i < g_world_obj_count; i++) {
        link = 0;
        hasCb = 0;
        if (i == g_world_obj_level_count) {
            base = (u8 *) bufB - i * 0x44;
        }
        obj = WOBJ(i);
        src = base + i * 0x44;
        S16(obj, 0x10) = S16(src, 0);
        S16(obj, 0x12) = S16(src, 2);
        S16(obj, 0x14) = S16(src, 4);
        WF32(obj, 0) = S16(src, 6);
        WF32(obj, 4) = S16(src, 8);
        WF32(obj, 8) = S16(src, 0xA);
        WF32(obj, 0x2C) = WF32(src, 0x20);
        WF32(obj, 0x30) = WF32(src, 0x24);
        WF32(obj, 0x34) = WF32(src, 0x28);
        W32(obj, 0x1C) = W32(src, 0xC);
        W16(obj, 0x88) = 0;
        W8(obj, 0x70) = W8(src, 0x3C) & ~8;
        W8(obj, 0x6E) = W8(src, 0x34);
        W32(obj, 0x3C) = W32(src, 0x18);
        type = W32(src, 0x14);
        if ((u32) type < 0xFFFF) {
            if (type == 0x28 || type == 0x42) {
                W8(obj, 0x70) |= 4;
                keepBit2 = 1;
            }
            W32(obj, 0x38) = D_80089030[W32(src, 0x14)][0];
            W32(obj, 0x78) = D_80089030[W32(src, 0x14)][1];
            W8(obj, 0x92) = D_80089030[W32(src, 0x14)][2];
            if (W32(src, 0x14) == 0x16) {
                hasCb = 1;
            }
        } else {
            W32(obj, 0x38) = type;
            W32(obj, 0x78) = 0;
        }
        S16(obj, 0x5A) = 0;
        S16(obj, 0x5C) = 0;
        S16(obj, 0x5E) = 0;
        W32(obj, 0x7C) = 0;
        W32(obj, 0x80) = 0;
        W32(obj, 0x84) = 0;
        W16(obj, 0x74) = 0;
        W8(obj, 0x4E) = 0;
        W16(obj, 0x6C) = 0;
        W8(obj, 0x73) = 4;
        WF32(obj, 0x60) = 0.0f;
        WF32(obj, 0x64) = 0.0f;
        WF32(obj, 0x68) = 0.0f;
        WF32(obj, 0x18) = 0.0f;
        W8(obj, 0x8A) = 0xFF;
        W8(obj, 0x8E) = 0xFF;
        W8(obj, 0x8D) = 0xFF;
        W8(obj, 0x8C) = 0xFF;
        W8(obj, 0x8B) = 0xFF;
        W8(obj, 0x71) = i;
        W32(obj, 0x94) = 0;
        W32(obj, 0x98) = 0;
        W32(obj, 0x40) = W32(src, 0x38);
        kind = W32(obj, 0x1C);
        if (kind == 0) {
            /* loaded model: share an earlier multiplayer object's model with the same key */
            id = W32(src, 0x10);
            for (j = g_world_obj_level_count; j < i; j++) {
                s = base + j * 0x44;
                if (W32(s, 0xC) == W32(src, 0xC) && W32(s, 0x10) == id && W32(WOBJ(j), 0x1C) != 0) {
                    link = j + 1;
                    break;
                }
            }
            if (link == 0) {
                seg = (u8 *) asset_load_with_subfiles(&found, 0, NULL, 2, 3, id);
                WPTR(obj, 0xC) = seg;
            }
            if (link != 0) {
                prev = WOBJ(link - 1);
                WPTR(obj, 0x28) = WPTR(prev, 0x28);
                W32(obj, 0x1C) = W32(prev, 0x1C);
                W32(obj, 0x9C) = W32(prev, 0x9C);
                W16(obj, 0x16) = W16(prev, 0x16);
                W32(obj, 0x44) = W32(prev, 0x44);
            } else {
                WPTR(obj, 0x28) = seg + 0x28;
                W32(obj, 0x1C) = W32(seg, 0);
                W16(obj, 0x16) = (s32) (W32(seg, 0) - (s32) (seg + 0x28)) >> 4;
                W32(obj, 0x9C) = W32(seg, 8);
                W32(obj, 0x44) = W32(seg, 0x10);
            }
            if (i >= g_world_obj_level_count) {
                e = g_world_obj_model_records + id * 12;
                W8(obj, 0x4C) = e[0];
                W8(obj, 0x4D) = e[1];
                S16(obj, 0x50) = S16(e, 4);
                S16(obj, 0x52) = S16(e, 2);
                W8(obj, 0x4F) = e[8];
                W8(obj, 0x70) = e[9] & ~8;
                W16(obj, 0x6C) = W16(e, 0xA);
                if (keepBit2 != 0) {
                    W8(obj, 0x70) = (e[9] & ~8) | 4;
                }
                W16(obj, 0x90) = W16(e, 6);
                W8(obj, 0x72) = W8(src, 0x33);
            } else {
                W16(obj, 0x50) = W16(src, 0x2E);
                W16(obj, 0x52) = W16(src, 0x30);
                W8(obj, 0x4F) = W8(src, 0x32);
                W8(obj, 0x4C) = W8(src, 0x2C);
                W8(obj, 0x4D) = W8(src, 0x2D);
                W16(obj, 0x90) = W16(src, 0x40);
                if (W8(src, 0x33) != 0) {
                    W8(obj, 0x72) = W8(src, 0x33);
                } else {
                    W8(obj, 0x72) = world_object_alloc_id(1);
                }
            }
            if (id == 0x71) {
                W32(obj, 0x40) = 0xE;
            }
            if (W32(obj, 0x38) == 0 && hasCb == 0) {
                W8(obj, 0x6F) = 0x80;
            } else if (W8(obj, 0x6E) == 0) {
                W8(obj, 0x6F) = 0xF;
            } else {
                W8(obj, 0x6F) = 0;
            }
            W16(obj, 0x54) = id;
        } else {
            W16(obj, 0x54) = W32(src, 0x10) | 0x8000;
            if (kind == 1 || kind == 2) {
                /* level-segment model: share an earlier object's with the same key */
                for (j = 0; j < i; j++) {
                    s = base + j * 0x44;
                    if (W32(s, 0xC) == W32(src, 0xC) && W32(s, 0x10) == W32(src, 0x10) && W32(WOBJ(j), 0x1C) != 0) {
                        link = j + 1;
                        break;
                    }
                }
                if (link == 0) {
                    lseg = g_level_model_entries[W32(src, 0x10) * 2];
                    WPTR(obj, 0x28) = lseg + 0x28;
                    W16(obj, 0x16) = (u32) (W32(lseg, 0) - (s32) (lseg + 0x28)) >> 4;
                    W32(obj, 0x44) = W32(lseg, 0x10);
                    W32(obj, 0x9C) = W32(lseg, 8);
                } else {
                    prev = WOBJ(link - 1);
                    W16(obj, 0x16) = W16(prev, 0x16);
                    WPTR(obj, 0x28) = WPTR(prev, 0x28);
                    W32(obj, 0x44) = W32(prev, 0x44);
                    W32(obj, 0x9C) = W32(prev, 0x9C);
                }
                if (W32(obj, 0x1C) == 2) {
                    W8(obj, 0x6F) = 0;
                } else {
                    W8(obj, 0x6F) = 0x80;
                }
                if (link == 0) {
                    W32(obj, 0x1C) = W32(lseg, 0);
                } else {
                    W32(obj, 0x1C) = W32(WOBJ(link - 1), 0x1C);
                }
                W32(obj, 0xC) = 0;
                W16(obj, 0x6C) = W16(src, 0x3E);
            }
            W16(obj, 0x50) = W16(src, 0x2E);
            W16(obj, 0x52) = W16(src, 0x30);
            W8(obj, 0x4F) = W8(src, 0x32);
            W8(obj, 0x4C) = W8(src, 0x2C);
            W8(obj, 0x4D) = W8(src, 0x2D);
            W16(obj, 0x90) = W16(src, 0x40);
            if (W8(src, 0x33) != 0) {
                W8(obj, 0x72) = W8(src, 0x33);
            } else {
                W8(obj, 0x72) = world_object_alloc_id(1);
            }
        }
        world_object_calc_radius(obj, (s32) src);
        if (W32(obj, 0x38) == 0 && hasCb == 0) {
            W8(obj, 0x6F) |= 0x20;
        }
        if (link == 0) {
            texture_resolve_dl_ids((Gfx *) WPTR(obj, 0x1C), 0, 1, 0x3F, NULL);
            gfx_dl_relocate_seg_e((Gfx *) WPTR(obj, 0x1C), (s32) seg);
        }
    }

    /* vertex buffers: moving objects (+0x70 bit 0) get two private copies, the others use the model's */
    for (i = 0; i < g_world_obj_count; i++) {
        obj = WOBJ(i);
        if (WPTR(obj, 0x28) == NULL) {
            continue;
        }
        if ((W8(obj, 0x70) & 1) == 1) {
            WPTR(obj, 0x20) = allocate_memory(W16(obj, 0x16) << 4, 1, 2, 0);
            WPTR(obj, 0x24) = allocate_memory(W16(obj, 0x16) << 4, 1, 2, 0);
        } else {
            WPTR(obj, 0x24) = WPTR(obj, 0x28);
            WPTR(obj, 0x20) = WPTR(obj, 0x28);
        }
        if (WPTR(obj, 0x28) != WPTR(obj, 0x20)) {
            for (k = 0; k < W16(obj, 0x16); k++) {
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[0] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[0];
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[1] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[1];
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[2] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[2];
                ((u32 *) (WPTR(obj, 0x20) + k * 0x10))[3] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[3];
            }
            if (WPTR(obj, 0x20) != WPTR(obj, 0x24)) {
                for (k = 0; k < W16(obj, 0x16); k++) {
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[0] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[0];
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[1] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[1];
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[2] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[2];
                    ((u32 *) (WPTR(obj, 0x24) + k * 0x10))[3] = ((u32 *) (WPTR(obj, 0x28) + k * 0x10))[3];
                }
            }
        }
    }

    g_world_obj_mtx_a = allocate_memory(g_world_obj_count << 6, 1, 2, 0);
    g_world_obj_mtx_b = allocate_memory(g_world_obj_count << 6, 1, 2, 0);
    g_world_obj_blocks = allocate_memory(g_world_obj_count * 4, 1, 0, 0);
    g_world_obj_block_timers = allocate_memory(g_world_obj_count, 1, 0, 0);
    for (k = 0; k < 4; k++) {
        g_world_obj_view_words[k] = allocate_memory(g_world_obj_count * 4, 1, 0, 0);
    }
    g_world_obj_rider_masks = allocate_memory(g_world_obj_count * 4, 1, 0, 0);
    for (k = 0; k < g_world_obj_count; k++) {
        g_world_obj_rider_masks[k] = 0;
    }
    for (k = g_world_obj_level_count; k < g_world_obj_count; k++) {
        if (W8(WOBJ(k), 0x72) == 0) {
            W8(WOBJ(k), 0x72) = world_object_alloc_id(0);
        }
    }
}
#undef WOBJ
#undef W8
#undef W16
#undef S16
#undef W32
#undef WPTR
#undef WF32

// FIXME: matches but something isnt right
/* was func_15004574 */
void world_object_cache_selected(void) {
    if (g_world_obj_selected != 0xFF) {
        g_world_obj_selected_1c = g_world_objs[g_world_obj_selected].unk1C;
        g_world_obj_selected_28 = g_world_objs[g_world_obj_selected].unk28;
    }
}

/* was func_150045BC */
void world_objects_noop(void) {
}

void world_objects_clear_arrays(void);
void world_record_build_matrix(f32 (*arg0)[4], u8 *arg1);
void mtxf_transform_point(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
void collision_select_area(s32 arg0);
s32 world_objects_transform_mesh(s32 count, s32 *idList, s32 force);
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
void scenery_handler_noop();
void scenery_uv_scroll_update();
void scenery_start_pending_anim();
extern f32 D_800DC338[4][4];
extern f32 g_world_obj_identity_mtx[4][4]; /* was D_800DC378 */
extern Mtx **g_world_obj_mtx_bufs[2];       /* per DL buffer: -> the world-object matrix array (0x40 each); was D_800895F0 */
extern u16 D_800D3C00;

/* Level start for the g_world_obj_count world objects (0xA0-byte records at g_world_objs): reset, identity camera matrices,
 * then per object: kind 3 for no/known callbacks, its matrix (world_record_build_matrix) into both DL buffers' g_world_obj_mtx_bufs
 * arrays unless static (+0x70 bit 0); static objects get their vertices (+0x28, 0x10 stride) transformed once into
 * +0x20 and copied to +0x24; world_objects_transform_mesh for flagged ones. Second pass: collision_find_floor per visible object
 * (bounds from +0x10/+0x12/+0x14, range -10000..20000) into +0x80/+0x84. arg0 (the level) is unused. */
/* was func_150045C4 */
void world_objects_level_start(s32 arg0) {
    f32 mf[4][4];     /* sp+0x98 */
    f32 ox, oy, oz;   /* sp+0x84, 0x80, 0x7C */
    s32 out0;         /* sp+0x88 */
    f32 out1;         /* sp+0x8C */
    s32 out2;         /* sp+0x90 */
    u8 *r;
    s16 *v;
    s16 *w;
    s32 i, j;
    s32 b;
    void *cb;

    world_objects_clear_arrays();
    guMtxIdentF(D_800DC338);
    guMtxIdentF(g_world_obj_identity_mtx);
    for (i = 0; i < g_world_obj_count; i++) {
        r = (u8 *)g_world_objs + i * 0xA0;
        cb = *(void **)(r + 0x38);
        if (cb == NULL || cb == (void *)scenery_uv_scroll_update || cb == (void *)scenery_start_pending_anim) {
            r[0x4E] = 3;
        }
        if (!(r[0x70] & 1)) {
            world_record_build_matrix(mf, r);
            guMtxF2L(mf, *g_world_obj_mtx_bufs[g_dl_buf_index] + i);
            b = g_dl_buf_index;
            bcopy(*g_world_obj_mtx_bufs[b] + i, *g_world_obj_mtx_bufs[b == 0] + i, 0x40);
        }
        if (*(void **)(r + 0x38) == (void *)scenery_handler_noop) {
            *(void **)(r + 0x38) = NULL;
        }
        if ((r[0x70] & 1) == 1) {
            world_record_build_matrix(mf, r);
            for (j = 0; j < *(u16 *)(r + 0x16); j++) {
                v = (s16 *)(*(u8 **)(r + 0x28) + j * 0x10);
                mtxf_transform_point(mf, v[0], v[1], v[2], &ox, &oy, &oz);
                w = (s16 *)(*(u8 **)(r + 0x20) + j * 0x10);
                w[0] = (s32)ox;
                w = (s16 *)(*(u8 **)(r + 0x20) + j * 0x10);
                w[1] = (s32)oy;
                w = (s16 *)(*(u8 **)(r + 0x20) + j * 0x10);
                w[2] = (s32)oz;
            }
            bcopy(*(void **)(r + 0x20), *(void **)(r + 0x24), *(u16 *)(r + 0x16) << 4);
        }
        collision_select_area(2);
        if ((r[0x6F] & 0x80) == 0x80 && (r[0x4F] & 0x60) != 0x20) {
            D_800D3C00 = i;
            world_objects_transform_mesh(1, (s32 *)&D_800D3C00, 1);
        }
    }
    for (i = 0; i < g_world_obj_count; i++) {
        r = (u8 *)g_world_objs + i * 0xA0;
        if (r[0x6E] == 1) {
            continue;
        }
        if ((r[0x6F] & 0x20) != 0x20) {
            continue;
        }
        collision_find_floor((s32)&out0, 0, (s32)&out1, 0, (s32)&out2, 0, *(s16 *)(r + 0x10), *(s16 *)(r + 0x12),
                      *(s16 *)(r + 0x14), *(s16 *)(r + 0x12), i + 1, 0, -10000.0f, 20000.0f);
        *(s32 *)(r + 0x80) = out0;
        *(f32 *)(r + 0x84) = out1;
    }
}
/* was func_150049A4 */
void gfx_dl_relocate_segments(Gfx *arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; ((struct_eu_cmd8 *)&arg0[i])->cmd != -0x21; i++) {
        switch (((struct_eu_cmd8 *)&arg0[i])->cmd) {
            case 0xDE:
                ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg1;
                break;
            case 1:
                ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg1;
                break;
            case -0x24:
                if (((struct_eu_cmd8 *)&arg0[i])->unk3 == 0xE) {
                    ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg2;
                }
                break;
        }
    }
}
/* was func_15004A4C */
void world_objects_clear_arrays(void) {
    s32 i;

    for (i = 0; i < g_world_obj_count; i++) {
        g_world_obj_blocks[i] = 0;
        g_world_obj_block_timers[i] = 0;
    }
}

extern u16 g_world_obj_radius_small_cnt; /* was D_800BE6C0 */
extern u16 g_world_obj_radius_set_cnt; /* was D_800BE6C2 */
extern u16 g_world_obj_radius_ok_cnt; /* was D_800BE6C4 */

/* was func_15004AAC */
void world_object_calc_radius(u8 *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_f8;
    s32 var_a2;
    s32 var_v0;
    u16 temp_a1;
    u16 temp_v1;
    u8 *var_a3;

    temp_a1 = (*(u16 *)((u8 *)arg0 + 0x16));
    var_v0 = 0;
    var_a2 = 0;
    if ((s32) temp_a1 > 0) {
        var_a3 = (*(u8 **)((u8 *)arg0 + 0x28));
        do {
            var_a2 += 0x10;
            temp_f2 = (f32) (*(s16 *)((u8 *)var_a3 + 4)) * (*(f32 *)((u8 *)arg0 + 0x34));
            temp_f14 = (f32) (*(s16 *)((u8 *)var_a3 + 0)) * (*(f32 *)((u8 *)arg0 + 0x2C));
            temp_f18 = (f32) (*(s16 *)((u8 *)var_a3 + 2)) * (*(f32 *)((u8 *)arg0 + 0x30));
            temp_f10 = (s32) ((temp_f2 * temp_f2) + ((temp_f14 * temp_f14) + (temp_f18 * temp_f18)));
            if (var_v0 < temp_f10) {
                var_v0 = temp_f10;
            }
            var_a3 += 0x10;
        } while (var_a2 < (temp_a1 * 0x10));
    }
    if (var_v0 != 0) {
        temp_v1 = (*(u16 *)((u8 *)arg0 + 0x50));
        temp_f0 = sqrtf((f32) var_v0);
        if (temp_v1 == 0) {
            temp_f4 = (s32) temp_f0;
            (*(u16 *)((u8 *)arg0 + 0x50)) = (u16) temp_f4;
            (*(u16 *)((u8 *)arg0 + 0x52)) = (u16) temp_f4;
            g_world_obj_radius_set_cnt += 1;
            return;
        }
        temp_f8 = (s32) temp_f0;
        if (((s32) temp_v1 < temp_f8) || ((s32) (*(u16 *)((u8 *)arg0 + 0x52)) < temp_f8)) {
            g_world_obj_radius_small_cnt += 1;
            return;
        }
        g_world_obj_radius_ok_cnt += 1;
    }
}
/* was func_15004BF0 */
s32 world_object_alloc_id(s32 arg0) {
    s32 i;
    s32 id;
    s32 first;

    if (arg0 == 0) {
        id = 1;
        for (i = g_world_obj_level_count; i < g_world_obj_count; i++) {
            if (id == g_world_objs[i].pad70[2]) {
                id++;
                i = g_world_obj_level_count - 1;
            }
            if (id >= 0x100) {
                id = 0xFF;
                break;
            }
        }
    } else {
        first = 0xFF - g_world_obj_level_count;
        id = first;
        for (i = 0; i < g_world_obj_count; i++) {
            if (id == g_world_objs[i].pad70[2]) {
                id--;
                i = -1;
            }
            if (id <= 0) {
                id = first;
                break;
            }
        }
    }
    return id;
}
/* was func_15004CE0 */
void gfx_dl_relocate_seg_e(Gfx *arg0, s32 arg1) {
    s32 i;
    struct_eu_cmd8 *p;

    for (i = 0; ((struct_eu_cmd8 *)&arg0[i])->cmd != -0x21; i++) {
        p = (struct_eu_cmd8 *)&arg0[i];
        if (p->cmd == -0x24 && p->unk3 == 0xE && p->unk4 < 0x80000000) {
            p->unk4 += arg1;
        }
    }
}
