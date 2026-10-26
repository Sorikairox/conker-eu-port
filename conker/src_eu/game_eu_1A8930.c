#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted: player_morph_cache_age calls it before player_morph_blend's block
void heap_free(s32);


typedef struct {
    s32 h;
    u8 t;
} EntABB0;
typedef struct {
    u8 type;
    u8 n;
    u8 pad[6];
} DescABB0;
extern DescABB0 g_player_morph_descs[]; /* was D_800A7610 */
extern u16 g_model_part_counts[]; /* was D_800C4730 */
/* was func_1517ABB0 */
void player_morph_cache_age(void) {
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        if (((EntABB0 ***)g_player_morph_caches)[i] != NULL) {
            for (j = 0; j < g_model_part_counts[g_player_morph_descs[i].type]; j++) {
                for (k = 0; k < g_player_morph_descs[i].n; k++) {
                    if (((EntABB0 ***)g_player_morph_caches)[i][j][k].h != 0) {
                        if (((EntABB0 ***)g_player_morph_caches)[i][j][k].t != 0) {
                            ((EntABB0 ***)g_player_morph_caches)[i][j][k].t--;
                        } else {
                            heap_free(((EntABB0 ***)g_player_morph_caches)[i][j][k].h);
                            ((EntABB0 ***)g_player_morph_caches)[i][j][k].h = 0;
                        }
                    }
                }
            }
        }
    }
}

u8 obj_current_part_model(struct127 *);
s32 asset_load(s32 *arg0, s32 arg1, ...);
void os_writeback_dcache(void *, s32); /* osWritebackDCache */
s32 allocate_memory(s32, s32, s32, s32);
extern s32 D_800C4440;

/* blend state at player +0x260 */
typedef struct {
    f32 t;     /* 0 .. 1 */
    f32 rate;  /* per tick */
    u8 prev;
    u8 cur;    /* 0xFF = none yet */
    u8 hold;   /* ticks the finished blend is kept */
} Blend1A8930;

/*
 * player_morph_blend: blends player `idx`'s (g_objects) morph target from the previous shape to shape `target`
 * over `frames` ticks. The shape set g_player_morph_descs[i] is picked by the player's type (obj_current_part_model); a player with
 * +0x1C8 set and no vertex buffer (+0x28C[g_dl_buf_index]) or no D_800D19A0 entry only advances the blend factor. On
 * a new target the old one becomes `prev` and t restarts at 0. Shape vertex sets (one per part j, loaded on demand
 * with asset_load and cached in g_player_morph_caches[i][j][shape]) are lerped s16 x / y / z by t into the player's vertex
 * buffer at the part's index D_800C4440[type][j] (16-byte vertices), then written back from the cache. The finished
 * blend (t == 1) counts +0xA down; returns 0, or -1 when nothing was written.
 */
/* was func_1517B270 */
s32 player_morph_blend(s32 target, s32 frames, s32 idx) {
    u8 *ply = (u8 *)g_objects + idx * 0x32C;
    DescABB0 *desc;
    Blend1A8930 *b;
    EntABB0 ***cache;
    EntABB0 *ents;
    s16 *from;
    s16 *to;
    s16 *dst;
    u8 *vtx;
    s32 type;
    s32 found;
    s32 fail;
    s32 i;
    s32 j;
    s32 k;
    s32 cnt;
    s32 args[4];

    type = ply[4];
    found = obj_current_part_model((struct127 *)ply);
    desc = NULL;
    for (i = 0; i < 2; i++) {
        if (found == g_player_morph_descs[i].type) {
            desc = &g_player_morph_descs[i];
            break;
        }
    }
    if (desc == NULL) {
        return -1;
    }
    b = *(Blend1A8930 **)(ply + 0x260);
    if (ply[0x1C8] != 0) {
        type = found;
        if (*(s32 *)(ply + 0x28C + g_dl_buf_index * 4) == 0 || (&D_800D19A0)[found] == 0) {
            /* nothing to draw into: only advance the blend */
            if (target == b->cur) {
                if (!g_game_paused) {
                    b->t += b->rate * g_frame_ticks;
                }
                if (1.0f < b->t) {
                    b->t = 1.0f;
                }
            } else {
                if (b->cur != 0xFF) {
                    b->prev = b->cur;
                }
                b->cur = target;
                b->t = 0.0f;
                if (frames <= 0) {
                    frames = 1;
                }
                b->rate = 1.0f / frames;
            }
            b->hold = 3;
            return -1;
        }
    }
    if ((&D_800D19A0)[type] == 0) {
        return -1;
    }
    if (*(s32 *)(ply + 0x28C + g_dl_buf_index * 4) == 0) {
        return -1;
    }
    if (target == b->cur && b->hold == 0) {
        b->prev = b->cur;
        return 0;
    }
    if (target != b->cur) {
        if (b->cur != 0xFF) {
            b->prev = b->cur;
        }
        b->cur = target;
        b->t = 0.0f;
        if (frames <= 0) {
            frames = 1;
        }
        b->hold = 3;
        b->rate = 1.0f / frames;
    }

    cache = &((EntABB0 ***)g_player_morph_caches)[i];
    if (*cache == NULL) {
        *cache = (EntABB0 **)allocate_memory(g_model_part_counts[desc->type] * 4, 1, 0, 2);
        if (*cache == NULL) {
            return -1;
        }
        fail = 0;
        for (j = 0; j < g_model_part_counts[desc->type]; j++) {
            (*cache)[j] = (EntABB0 *)allocate_memory(desc->n * 8, 1, 0, 2);
            if ((*cache)[j] != NULL) {
                bzero((*cache)[j], desc->n * 8);
            } else {
                fail = 1;
            }
        }
        if (fail) {
            for (j = 0; j < g_model_part_counts[desc->type]; j++) {
                if ((*cache)[j] != NULL) {
                    heap_free((s32)(*cache)[j]);
                }
            }
            return -1;
        }
    }

    if (!g_game_paused) {
        b->t += b->rate * g_frame_ticks;
    }
    if (1.0f < b->t) {
        b->t = 1.0f;
    }
    vtx = *(u8 **)(ply + 0x28C + g_dl_buf_index * 4);
    for (j = 0; j < g_model_part_counts[desc->type]; j++) {
        ents = (*cache)[j];
        if (ents[b->cur].h == 0) {
            ents[b->cur].h = asset_load(args, 4, 0x13, i, j, b->cur);
            ents = (*cache)[j];
            if (ents[b->cur].h == 0) {
                return -1;
            }
        }
        if (ents[b->prev].h == 0) {
            ents[b->prev].h = asset_load(args, 4, 0x13, i, j, b->prev);
            ents = (*cache)[j];
            if (ents[b->prev].h == 0) {
                heap_free(ents[b->cur].h);
                (*cache)[j][b->cur].h = 0;
                return -1;
            }
        }
        ents[b->cur].t = 3;
        (*cache)[j][b->prev].t = 3;
        ents = (*cache)[j];
        from = (s16 *)ents[b->prev].h;
        to = (s16 *)ents[b->cur].h;
        dst = (s16 *)(vtx + ((s32 **)&D_800C4440)[type][j] * 16);
        cnt = ((u16 *)((u8 *)desc + 2))[j];
        for (k = 0; k < cnt; k++) {
            dst[k * 8 + 0] = (s32)(((f32)to[k * 3 + 0] - (f32)from[k * 3 + 0]) * b->t + (f32)from[k * 3 + 0]);
            dst[k * 8 + 1] = (s32)(((f32)to[k * 3 + 1] - (f32)from[k * 3 + 1]) * b->t + (f32)from[k * 3 + 1]);
            dst[k * 8 + 2] = (s32)(((f32)to[k * 3 + 2] - (f32)from[k * 3 + 2]) * b->t + (f32)from[k * 3 + 2]);
        }
        os_writeback_dcache(dst, cnt * 16);
    }
    if (1.0f == b->t) {
        b->hold--;
    } else {
        b->hold = 3;
    }
    return 0;
}
