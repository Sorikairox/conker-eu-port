#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct Node8D80 { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8D80 *uC; struct127 *u10; s32 u14; } Node8D80;
void *allocate_memory(s32, s32, s32, s32);
void heap_free(u8 *);
s32 model_joint_mtx_count(u8);
void afterimage_list_append();

// object_trail_start: starts (or extends) the trail effect of obj (scene event 5 / 0x2D): an existing node of the
// g_afterimage_lists list for obj gets the longer duration and the new style; else a 0x18-byte node (type 3, 0x14) with a
// zeroed buffer of 0x180 bytes per trail point of the object's kind (model_joint_mtx_count(kind), 0 = no trail) is appended.
/* was func_15188D80 */
void afterimage_start(struct127 *obj, s32 frames, s32 style) {
    Node8D80 *n;
    void *buf;
    s32 count;

    for (n = *(Node8D80 **) g_afterimage_lists; n != NULL; n = n->uC) {
        if (obj == n->u10) {
            if (n->u6 < frames) {
                n->u6 = frames;
            }
            n->u4 = style;
            return;
        }
    }
    n = allocate_memory(0x18, 1, 0, 0);
    if (n == NULL) {
        return;
    }
    count = model_joint_mtx_count(((u8 *) obj)[4]);
    if (count == 0) {
        heap_free((u8 *) n);
        return;
    }
    buf = allocate_memory(count * 0x180, 1, 1, 1);
    if (buf == NULL) {
        heap_free((u8 *) n);
        return;
    }
    n->u0 = 0;
    n->u1 = 3;
    n->u2 = 0;
    n->u3 = 0x14;
    n->u4 = style;
    n->u8_ = buf;
    n->u10 = obj;
    n->u14 = 0;
    n->u6 = frames;
    bzero(buf, count * 0x180);
    afterimage_list_append(n, g_afterimage_lists);
}

typedef struct Node8EBC { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8EBC *uC; s32 u10; } Node8EBC;
extern Node8EBC *g_afterimage_world_list; /* was D_800DFBFC */
void *allocate_memory(s32, s32, s32, s32);
// the definition is void; one signature for wasm
void heap_free(u8 *);
void afterimage_list_append();
/* was func_15188EBC */
void afterimage_start_world(s32 arg0, s32 arg1, s32 arg2) {
    Node8EBC *n;
    void *buf;

    for (n = g_afterimage_world_list; n != NULL; n = n->uC) {
        if (arg0 == n->u10) {
            if (n->u6 < arg1) {
                n->u6 = arg1;
            }
            n->u4 = arg2;
            return;
        }
    }
    n = allocate_memory(0x14, 1, 0, 0);
    if (n == NULL) {
        return;
    }
    buf = allocate_memory(0x180, 1, 1, 0);
    if (buf == NULL) {
        heap_free((u8 *)n);
        return;
    }
    n->u0 = 1;
    n->u1 = 3;
    n->u2 = 0;
    n->u3 = 0x14;
    n->u4 = arg2;
    n->u6 = arg1;
    n->u8_ = buf;
    n->u10 = arg0;
    bzero(buf, 0x180);
    afterimage_list_append(n, &g_afterimage_world_list);
}

typedef struct struct_15188FC8 {
    u8 pad0[0xC];
    struct struct_15188FC8 *unkC;
} struct_15188FC8;

/* was func_15188FC8 */
void afterimage_list_append(struct_15188FC8 *arg0, struct_15188FC8 **arg1) {
    struct_15188FC8 *var_v1;

    arg0->unkC = NULL;
    if (*arg1 != NULL) {
        for (var_v1 = *arg1; var_v1->unkC != NULL; var_v1 = var_v1->unkC) {
        }
        var_v1->unkC = arg0;
    } else {
        *arg1 = arg0;
    }
}

/* was func_1518900C */
void afterimage_stop(s32 arg0) {
    struct_eu_1B6590 *var_v0 = (struct_eu_1B6590 *)g_afterimage_lists[0];
    while (var_v0 != NULL) {
        if (arg0 == var_v0->unk10) {
            var_v0->unk6 = 0;
        }
        var_v0 = var_v0->unkC;
    }
}

// the definition is void; one signature for wasm
void heap_free(u8 *);

/* was func_15189040 */
void afterimage_remove_object(s32 arg0) {
    s32 temp_s0;
    s32 var_s1;
    u8 *var_s2;

    var_s1 = *g_afterimage_lists;
    var_s2 = NULL;
    if (var_s1 != 0) {
        do {
            temp_s0 = (*(s32 *)((u8 *)var_s1 + 0xC));
            if (arg0 == (*(s32 *)((u8 *)var_s1 + 0x10))) {
                if (var_s2 == NULL) {
                    *g_afterimage_lists = temp_s0;
                } else {
                    (*(s32 *)((u8 *)var_s2 + 0xC)) = temp_s0;
                }
                heap_set_block_tag((*(s32 **)((u8 *)var_s1 + 8)), 2U);
                heap_free((u8 *) var_s1);
            } else {
                var_s2 = (u8 *) var_s1;
            }
            var_s1 = temp_s0;
        } while (temp_s0 != 0);
    }
}

extern void (*g_afterimage_update_fns[])(struct_eu_1B6590 *); /* was D_8008D920 */
extern void (*g_afterimage_free_fns[])(struct_eu_1B6590 *); /* was D_8008D928 */
// the definition is void; one signature for wasm
void heap_free(u8 *);
/* was func_151890E4 */
void afterimage_list_update(s32 arg0) {
    struct_eu_1B6590 **head;
    struct_eu_1B6590 *n;
    struct_eu_1B6590 *next;
    struct_eu_1B6590 *prev;
    s32 v;

    head = (struct_eu_1B6590 **)&g_afterimage_lists[arg0];
    prev = NULL;
    for (n = *head; n != NULL; n = next) {
        next = n->unkC;
        if (n->unk6 != 0) {
            n->unk6 -= g_frame_ticks;
        }
        if (n->unk6 < 0) {
            n->unk6 = 0;
        }
        g_afterimage_update_fns[n->pad0[0]](n);
        v = n->pad0[3];
        if (n->unk6 != 0) {
            if (v != 0xFF) {
                v += g_frame_ticks * 16;
                if (v >= 0x100) {
                    v = 0xFF;
                }
                n->pad0[3] = v;
            }
            prev = n;
        } else if (v != 0) {
            v -= g_frame_ticks * 8;
            if (v < 0) {
                v = 0;
            }
            if (v == 0) {
                if (prev == NULL) {
                    *head = next;
                } else {
                    prev->unkC = next;
                }
                g_afterimage_free_fns[n->pad0[0]](n);
                heap_free((u8 *)n);
            } else {
                n->pad0[3] = v;
                prev = n;
            }
        }
    }
}

extern Gfx *(*g_afterimage_draw_fns[])(Gfx *, struct_eu_1B6590 *, s16); /* was D_8008D930 */
/* was func_15189270 */
Gfx *afterimage_list_draw(Gfx *gfx, s32 arg1, s16 arg2) {
    struct_eu_1B6590 *n;

    n = (struct_eu_1B6590 *)g_afterimage_lists[arg1];
    if (n == NULL) {
        return gfx;
    }
    gSPMatrix(gfx++, g_identity_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPGeometryMode(gfx++, 0, 0x200004);
    gSPGeometryMode(gfx++, 0x110000, 0);
    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetConvert(gfx++, 0, 0, 0, 0, 0, 0xFF);
    while (n != NULL) {
        gfx = g_afterimage_draw_fns[n->pad0[0]](gfx, n, arg2);
        n = n->unkC;
    }
    return gfx;
}

/* P249: readable C for afterimage_history_push (game_eu_1B6590, 79 insns). */
// trail_matrix_history_push: advances an object's motion-trail matrix history. The record holds rec[1] steps of
// `per` matrices (model_joint_mtx_count(object kind), 64 bytes each) in two halves of the buffer +8 (half g_dl_buf_index is
// written, the other half read): step j of this half = step j + 1 of the other half, and the last step = the
// object's current bone matrices (object +0x10, its +0x1D4); without matrices the filled count rec[2] is reset to 0
// and nothing else happens. Otherwise rec[2] counts up to rec[1].
s32 model_joint_mtx_count(u8);
/* was func_151893B8 */
void afterimage_history_push(u8 *rec) {
    s32 n, per, total, cur, prev, i, j;
    u8 *src;

    n = rec[1];
    per = model_joint_mtx_count((*(u8 **) (rec + 0x10))[4]);
    total = per * n;
    cur = g_dl_buf_index * total;
    prev = (g_dl_buf_index ^ 1) * total;
    j = 0;
    for (i = 1; i <= n; i++) {
        if (i == n) {
            src = *(u8 **) (*(u8 **) (rec + 0x10) + 0x1D4);
            if (src == NULL) {
                rec[2] = 0;
                return;
            }
        } else {
            src = *(u8 **) (rec + 8) + ((i * per + prev) << 6);
        }
        bcopy(src, *(u8 **) (rec + 8) + ((j * per + cur) << 6), per << 6);
        j = i;
    }
    if (rec[1] != rec[2]) {
        rec[2]++;
    }
}

extern u16 **g_world_vis_lists[];   /* per group: -> the group's entry list (4-byte entries, u16 record id first); was D_800895E0 */
extern Mtx **g_world_obj_mtx_bufs[2];  /* per DL buffer: -> the world-object matrix array (one Mtx per record id); was D_800895F0 */
extern u16 g_world_vis_counts[];     /* per group: entry count; was D_800DC318 */
// trail_matrix_history_push_world: P253. Like afterimage_history_push (same handler table), for an object with one matrix: the
// record holds rec[1] matrices (64 bytes each) in two halves of the buffer +8 (half g_dl_buf_index is written, the other
// half read): matrix j of this half = matrix j + 1 of the other half, and the last one = the object's world matrix
// (the object +0x10 is looked up in group 0's entry list by its record id, 0xA0-byte records at g_world_objs; matrix
// array of the current DL buffer). When the object is not in the list, the filled count rec[2] is reset to 0 and
// nothing else happens. Otherwise rec[2] counts up to rec[1].
/* was func_151894F4 */
void afterimage_history_push_world(u8 *rec) {
    s32 n = rec[1];
    s32 cur = g_dl_buf_index * n;
    s32 prev = (g_dl_buf_index ^ 1) * n;
    s32 k, i, j;
    Mtx *mtx;
    u8 *src;

    for (k = 0; k < g_world_vis_counts[0]; k++) {
        if (*(u8 **) (rec + 0x10) == (u8 *) g_world_objs + (*g_world_vis_lists[0])[k * 2] * 0xA0) {
            break;
        }
    }
    if (k == g_world_vis_counts[0]) {
        rec[2] = 0;
        return;
    }
    mtx = *g_world_obj_mtx_bufs[g_dl_buf_index] + (*g_world_vis_lists[0])[k * 2];
    j = 0;
    for (i = 1; i <= n; i++) {
        if (i == n) {
            src = (u8 *) mtx;
        } else {
            src = *(u8 **) (rec + 8) + (i + prev) * 64;
        }
        bcopy(src, *(u8 **) (rec + 8) + (cur + j) * 64, 64);
        j = i;
    }
    if (rec[1] != rec[2]) {
        rec[2]++;
    }
}

s32 model_joint_mtx_count(u8);

/* was func_15189688 */
void afterimage_clamp_spacing(s32 arg0) {
    f32 temp_f0;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f18_3;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f26_3;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 var_f30;
    s16 var_t5;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_f14;
    s32 temp_f16;
    s32 temp_t1;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a3;
    s32 var_s0;
    s32 var_t0;
    u8 temp_s1;
    u8 temp_t4;
    u8 *temp_a1_2;
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_v1;

    var_s0 = g_afterimage_lists[arg0];
    if (var_s0 != 0) {
        do {
            if ((*(u8 *)((u8 *)var_s0 + 4)) != 0) {
                temp_s1 = (*(u8 *)((u8 *)var_s0 + 1));
                temp_v0 = model_joint_mtx_count((*(u8 *)((u8 *)((*(u8 **)((u8 *)var_s0 + 0x10))) + 4)));
                temp_t4 = (*(u8 *)((u8 *)var_s0 + 4));
                temp_a2 = temp_v0;
                var_f30 = (f32) temp_t4;
                temp_t1 = g_dl_buf_index * temp_v0 * temp_s1;
                if ((s32) temp_t4 < 0) {
                    var_f30 += 4294967296.0f;
                }
                var_a3 = (*(u8 *)((u8 *)var_s0 + 2)) - 1;
                if (var_a3 >= 0) {
                    var_t0 = (var_a3 * temp_v0) + temp_t1;
loop_7:
                    temp_a1 = (*(s32 *)((u8 *)var_s0 + 8));
                    var_v1 = temp_a1 + (var_t0 << 6);
                    if ((var_a3 + 1) == (*(u8 *)((u8 *)var_s0 + 2))) {
                        temp_a1_2 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)var_s0 + 0x10))) + 0x1D4));
                        if (temp_a1_2 == NULL) {
                            (*(u8 *)((u8 *)var_s0 + 2)) = 0U;
                        } else {
                            var_a0 = temp_a1_2;
                            goto block_12;
                        }
                    } else {
                        var_a0 = temp_a1 + ((((var_a3 + 1) * temp_v0) + temp_t1) << 6);
block_12:
                        temp_f22 = ((f32) ((*(s16 *)((u8 *)var_v1 + 0x38)) + ((*(s16 *)((u8 *)var_v1 + 0x18)) << 0x10)) * 0.000015258789f) - ((f32) ((*(s16 *)((u8 *)var_a0 + 0x38)) + ((*(s16 *)((u8 *)var_a0 + 0x18)) << 0x10)) * 0.000015258789f);
                        temp_f26 = ((f32) ((*(s16 *)((u8 *)var_v1 + 0x3A)) + ((*(s16 *)((u8 *)var_v1 + 0x1A)) << 0x10)) * 0.000015258789f) - ((f32) ((*(s16 *)((u8 *)var_a0 + 0x3A)) + ((*(s16 *)((u8 *)var_a0 + 0x1A)) << 0x10)) * 0.000015258789f);
                        temp_f28 = ((f32) ((*(s16 *)((u8 *)var_v1 + 0x3C)) + ((*(s16 *)((u8 *)var_v1 + 0x1C)) << 0x10)) * 0.000015258789f) - ((f32) ((*(s16 *)((u8 *)var_a0 + 0x3C)) + ((*(s16 *)((u8 *)var_a0 + 0x1C)) << 0x10)) * 0.000015258789f);
                        temp_f0 = sqrtf((temp_f22 * temp_f22) + (temp_f26 * temp_f26) + (temp_f28 * temp_f28));
                        if ((var_f30 < temp_f0) && (temp_f0 != 0.0f)) {
                            temp_f22_2 = var_f30 / temp_f0;
                            if (temp_v0 > 0) {
                                var_a1 = 1;
                                var_t5 = (*(s16 *)((u8 *)var_v1 + 0x18));
                                if (temp_a2 != 1) {
                                    do {
                                        temp_f28_2 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x38)) + (var_t5 << 0x10)) * 0.000015258789f;
                                        temp_f26_2 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3A)) + ((*(s16 *)((u8 *)var_v1 + 0x1A)) << 0x10)) * 0.000015258789f;
                                        temp_f16 = (*(s16 *)((u8 *)var_a0 + 0x3A)) + ((*(s16 *)((u8 *)var_a0 + 0x1A)) << 0x10);
                                        temp_f20 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3C)) + ((*(s16 *)((u8 *)var_v1 + 0x1C)) << 0x10)) * 0.000015258789f;
                                        temp_f14 = (*(s16 *)((u8 *)var_a0 + 0x3C)) + ((*(s16 *)((u8 *)var_a0 + 0x1C)) << 0x10);
                                        var_a1 += 1;
                                        (*(s16 *)((u8 *)var_v1 + 0x38)) = 0;
                                        temp_f18 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x38)) + ((*(s16 *)((u8 *)var_a0 + 0x18)) << 0x10));
                                        (*(s16 *)((u8 *)var_v1 + 0x3A)) = 0;
                                        (*(s16 *)((u8 *)var_v1 + 0x3C)) = 0;
                                        var_v1 += 0x40;
                                        var_a0 += 0x40;
                                        temp_f18_2 = temp_f18 * 0.000015258789f;
                                        temp_f16_2 = (f32) temp_f16 * 0.000015258789f;
                                        temp_f14_2 = (f32) temp_f14 * 0.000015258789f;
                                        (*(s16 *)((u8 *)var_v1 + -0x26)) = (s16) (s32) (((temp_f26_2 - temp_f16_2) * temp_f22_2) + temp_f16_2);
                                        var_t5 = (*(s16 *)((u8 *)var_v1 + 0x18));
                                        (*(s16 *)((u8 *)var_v1 + -0x28)) = (s16) (s32) (((temp_f28_2 - temp_f18_2) * temp_f22_2) + temp_f18_2);
                                        (*(s16 *)((u8 *)var_v1 + -0x24)) = (s16) (s32) (((temp_f20 - temp_f14_2) * temp_f22_2) + temp_f14_2);
                                    } while (var_a1 != temp_a2);
                                }
                                temp_f28_3 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x38)) + (var_t5 << 0x10)) * 0.000015258789f;
                                temp_f26_3 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3A)) + ((*(s16 *)((u8 *)var_v1 + 0x1A)) << 0x10)) * 0.000015258789f;
                                (*(s16 *)((u8 *)var_v1 + 0x38)) = 0;
                                temp_f20_2 = (f32) ((*(s16 *)((u8 *)var_v1 + 0x3C)) + ((*(s16 *)((u8 *)var_v1 + 0x1C)) << 0x10));
                                (*(s16 *)((u8 *)var_v1 + 0x3A)) = 0;
                                (*(s16 *)((u8 *)var_v1 + 0x3C)) = 0;
                                temp_v1 = var_v1 + 0x40;
                                temp_f18_3 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x38)) + ((*(s16 *)((u8 *)var_a0 + 0x18)) << 0x10)) * 0.000015258789f;
                                temp_f16_3 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x3A)) + ((*(s16 *)((u8 *)var_a0 + 0x1A)) << 0x10)) * 0.000015258789f;
                                temp_f14_3 = (f32) ((*(s16 *)((u8 *)var_a0 + 0x3C)) + ((*(s16 *)((u8 *)var_a0 + 0x1C)) << 0x10)) * 0.000015258789f;
                                (*(s16 *)((u8 *)temp_v1 + -0x28)) = (s16) (s32) (((temp_f28_3 - temp_f18_3) * temp_f22_2) + temp_f18_3);
                                (*(s16 *)((u8 *)temp_v1 + -0x26)) = (s16) (s32) (((temp_f26_3 - temp_f16_3) * temp_f22_2) + temp_f16_3);
                                (*(s16 *)((u8 *)temp_v1 + -0x24)) = (s16) (s32) ((((temp_f20_2 * 0.000015258789f) - temp_f14_3) * temp_f22_2) + temp_f14_3);
                            }
                        }
                        var_a3 -= 1;
                        var_t0 += -temp_v0;
                        if (var_a3 >= 0) {
                            goto loop_7;
                        }
                    }
                }
            }
            var_s0 = (*(s32 *)((u8 *)var_s0 + 0xC));
        } while (var_s0 != 0);
    }
}
/* was func_15189B14 */
void afterimage_free_history(u8 *arg0) {
    heap_set_block_tag((*(s32 **)((u8 *)arg0 + 8)), 2U);
}

/* was func_15189B3C */
void afterimage_world_free_history(u8 *arg0) {
    heap_set_block_tag((*(s32 **)((u8 *)arg0 + 8)), 2U);
}

u8 obj_current_part_model_idx(struct127 *, s32 *);
s32 model_make_ready(struct127 *, u8, s32, s32);
u8 *obj_draw_part(u8 *, s32, s16, s32, s32);
extern u8 *D_800DFBF0; /* matrix list obj_draw_part draws the object with */
extern u8 D_800DFBF4;  /* alpha obj_draw_part draws the object with */
// trail_draw: P253. Draw handler (u8 *(u8 *gfx, u8 *rec, s16 arg2), same table as afterimage_history_push) of an object's
// motion trail: with filled steps (rec[2] != 0) it prepares the object +0x10 (obj_current_part_model_idx / model_make_ready), swaps
// the object's +0x94 for the record's +0x14 and draws the object (obj_draw_part, g_objects slot index, mode 4) once
// per filled step, each time with that step's matrices from the history buffer +8 (this half, g_dl_buf_index) and alpha
// rec[3] * (3 + step) * 32 / 256, then restores +0x94. Objects outside the 25 first g_objects slots are skipped.
/* was func_15189B64 */
u8 *afterimage_draw(u8 *gfx, u8 *rec, s16 arg2) {
    struct127 *obj = *(struct127 **) (rec + 0x10);
    s32 sp64;
    s32 n, alpha0, per, slot, count, i, m, a;
    s32 saved;
    u8 k;

    if (rec[2] == 0) {
        return gfx;
    }
    k = obj_current_part_model_idx(obj, &sp64);
    model_make_ready(*(struct127 **) (rec + 0x10), k, sp64, 1);
    n = rec[1];
    alpha0 = rec[3];
    per = model_joint_mtx_count(((u8 *) *(struct127 **) (rec + 0x10))[4]);
    obj = *(struct127 **) (rec + 0x10);
    m = g_dl_buf_index * per * n;
    count = rec[2];
    slot = ((u8 *) obj - (u8 *) g_objects) / 0x32C;
    if (slot < 0 || slot >= 25) {
        return gfx;
    }
    saved = *(s32 *) ((u8 *) obj + 0x94);
    *(s32 *) ((u8 *) obj + 0x94) = *(s32 *) (rec + 0x14);
    a = alpha0 * 3 * 32;
    for (i = 0; i < count; i++) {
        D_800DFBF0 = *(u8 **) (rec + 8) + m * 64;
        D_800DFBF4 = a >> 8;
        gfx = obj_draw_part(gfx, slot, arg2, 4, 1);
        a += alpha0 * 32;
        m += per;
    }
    *(s32 *) (*(u8 **) (rec + 0x10) + 0x94) = saved;
    return gfx;
}

s32 world_mesh_draw(s32, u8 *, s32, s16, s32, s32);

/* was func_15189D14 */
s32 afterimage_world_draw(s32 arg0, u8 *arg1, s16 arg2) {
    s32 sp44;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    u8 temp_a0;
    u8 temp_a3;

    var_s4 = arg0;
    temp_a3 = (*(u8 *)((u8 *)arg1 + 2));
    if (temp_a3 == 0) {
        return var_s4;
    }
    temp_a0 = (*(u8 *)((u8 *)arg1 + 3));
    var_s1 = temp_a0 * 0x60;
    var_s0 = 0;
    sp44 = (s32) (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x10))) + 0x8A));
    var_s2 = g_dl_buf_index * (*(u8 *)((u8 *)arg1 + 1));
    if ((s32) temp_a3 > 0) {
        do {
            (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x10))) + 0x8A)) = (u8) (var_s1 >> 8);
            temp_v0 = world_mesh_draw(var_s4, (*(u8 **)((u8 *)arg1 + 0x10)), (*(s32 *)((u8 *)arg1 + 8)) + (var_s2 << 6), arg2, 0, 0);
            var_s0 += 1;
            var_s1 += temp_a0 << 5;
            var_s2 += 1;
            var_s4 = temp_v0;
        } while (var_s0 != temp_a3);
    }
    (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x10))) + 0x8A)) = (s8) sp44;
    return var_s4;
}
/* was func_151898C0 */
void afterimage_set_skin(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = *g_afterimage_lists;
    if (var_v0 != 0) {
loop_1:
        if (arg0 == (*(s32 *)((u8 *)var_v0 + 0x10))) {
            (*(s32 *)((u8 *)var_v0 + 0x14)) = arg1;
            return;
        }
        var_v0 = (*(s32 *)((u8 *)var_v0 + 0xC));
        if (var_v0 == 0) {

        } else {
            goto loop_1;
        }
    }
}
