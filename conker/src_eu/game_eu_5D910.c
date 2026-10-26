#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void attachment_apply_kind_effects(u8 *arg0, u8 *arg1);
f32 *allocate_memory(s32, s32, s32, s32);
s32 *asset_load_with_subfiles(s32, s32, s32, s32, s32, s32);
s32 texture_resolve_dl_ids(s32, s32, s32, s32, s32 *);
void gfx_dl_relocate(s32, s32 *);
void heap_set_block_tag(s32 *arg0, u32 arg1);
void heap_free(s32);
void attachment_undo_kind_effects(u8 *);
void animmodel_free(s32);
void shared_dl_release(s32);
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
/* P71: a word of an attachment record (the list D_800C3EE0, see attachment_update_all) */
#define ATT_W(rec, off) (*(s32 *) ((rec) + (off)))
s32 attachment_sound_cb();   /* P71: C under NON_MATCHING (else an extern s32 below, as the matching code uses it) */
s32 sfx_emitter_stop_by_callback(s32 *, u8 *, u8 *);
#endif

#ifdef NON_MATCHING
s32 animmodel_start_anim(u8 *, s32, s32, f32, f32, s32); /* P95: f32 parameter */
#else
s32 animmodel_start_anim(u8 *, s32, s32, s32, f32, s32);
#endif

void attachment_free(struct127 *, s32);

s32 attachment_remove_by_slot_n(u8 *, s32, s32);


#ifdef NON_MATCHING
/*
 * P71: reference-counted load of asset (9, idx) with several display lists (the one-list variant is
 * shared_dl_acquire; shared_dl_release releases both). Header words: +0 the display-list offset table (+4 >> 2 entries),
 * +8, +0xC (>> 4), +0x10, the data from +0x18. First use: asset_load_with_subfiles(0, 0, 0, 2, 9, idx) (none: return 1),
 * each table entry is relocated by the header address, texture_resolve_dl_ids resolves its segments
 * (&D_800DFDE8[idx] keeps the list), gfx_dl_relocate patches its addresses; the header is kept in D_800E0578[idx].
 * The count D_800DFC00[idx] is not saturated here. Returns 0 once loaded.
 */
/* was func_15030100 */
s32 model_asset9_load_refcounted(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC) {
    u8 *refs = &D_800DFC00[idx];
    s32 *hdr;
    s32 i;

    if (*refs == 0) {
        hdr = asset_load_with_subfiles(0, 0, 0, 2, 9, idx);
        if (hdr == NULL) {
            return 1;
        }
        *dls = (s32 *) hdr[0];
        *count = (u32) hdr[1] >> 2;
        for (i = 0; i < *count; i++) {
            (*dls)[i] += (s32) hdr;
            texture_resolve_dl_ids((*dls)[i], 0, 1, 0x3E, &D_800DFDE8[idx]);
            gfx_dl_relocate((*dls)[i], hdr);
        }
        D_800E0578[idx] = hdr;
    } else {
        hdr = D_800E0578[idx];
        *dls = (s32 *) hdr[0];
        *count = (u32) hdr[1] >> 2;
    }
    (*refs)++;
    *data = (s32) (hdr + 6);
    if (out10 != NULL) {
        *out10 = hdr[4];
    }
    if (out8 == NULL) {
        return 0;
    }
    *out8 = hdr[2];
    if (outC != NULL) {
        *outC = (u32) hdr[3] >> 4;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/model_asset9_load_refcounted.s")
#endif

#ifdef NON_MATCHING
s32 model_asset9_load_refcounted(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC);
s32 animmodel_create(s32, s32, u8 *, u8 *, s32 *, u8 *, u8 *);

/*
 * P71: loads the model of attachment record rec (once: +0x24 set means loaded). +0x17 == -1: asset 9 entry +1
 * (model_asset9_load_refcounted, display lists to +0x24 / count +0x14 / +0x30), else entry (+1, +0x17) of animmodel_create (also
 * +0x48). Failure returns 1. The vertex data runs from the returned data pointer up to the list table (+0x24).
 * Records without bit 0x10 of +4 whose owner has (obj[0x66] & 0xC) == 8 and a +0x30 get two private copies of it
 * (+0x28 / +0x2C, +8 = 1 so attachment_free frees them), the others share it. Marks the record loaded (+9).
 */
/* was func_150302C8 */
s32 attachment_load_model(struct127 *arg0, u8 *obj) {
    u8 *rec = (u8 *) arg0;
    s32 data;
    s32 size;

    if (ATT_W(rec, 0x24) != 0) {
        return 0;
    }
    if ((s8) rec[0x17] == -1) {
        if (model_asset9_load_refcounted(rec[1], (s32 **) (rec + 0x24), rec + 0x14, &data, (s32 *) (rec + 0x30), NULL, NULL)) {
            return 1;
        }
    } else if (animmodel_create(rec[1], (s8) rec[0x17], rec + 0x24, rec + 0x14, &data, rec + 0x30, rec + 0x48)) {
        return 1;
    }
    size = ATT_W(rec, 0x24) - data;
    if (!(rec[4] & 0x10) && (obj[0x66] & 0xC) == 8 && ATT_W(rec, 0x30) != 0) {
        ATT_W(rec, 0x28) = (s32) allocate_memory(size, 1, 2, 2);
        if (ATT_W(rec, 0x28) == 0) {
            return 1;
        }
        ATT_W(rec, 0x2C) = (s32) allocate_memory(size, 1, 2, 2);
        if (ATT_W(rec, 0x2C) == 0) {
            heap_free(ATT_W(rec, 0x28));
            ATT_W(rec, 0x28) = 0;
            return 1;
        }
        bcopy((void *) data, (void *) ATT_W(rec, 0x28), size);
        bcopy((void *) data, (void *) ATT_W(rec, 0x2C), size);
        rec[8] = 1;
    } else {
        ATT_W(rec, 0x28) = data;
        ATT_W(rec, 0x2C) = data;
    }
    rec[9] = 1;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_load_model.s")
#endif

#ifdef NON_MATCHING
/*
 * P70: frees an attachment record of the list D_800C3EE0 (see attachment_update_all). now != 0 frees its buffers at
 * once (heap_free), else they are released deferred (heap_set_block_tag(buf, 4)) after attachment_undo_kind_effects.
 * Loaded records (+9) drop the two vertex copies +0x28 / +0x2C when they were made (+8), the +0x48 handle
 * (animmodel_free) and their asset (shared_dl_release(+1)). Then +0x34, +0x44 (always at once), +0x4C, +0x50, the
 * unlink from the doubly linked list (+0x54 next, +0x58 prev; the head D_800C3EE0) and the record itself.
 */
/* was func_15030448 */
void attachment_free(struct127 *arg0, s32 now) {
    u8 *rec = (u8 *) arg0;
    u8 *next;
    u8 *prev;

    if (!now) {
        attachment_undo_kind_effects(rec);
    }
    if (rec[9] != 0) {
        if (rec[8] != 0) {
            if (now) {
                heap_free(ATT_W(rec, 0x28));
                heap_free(ATT_W(rec, 0x2C));
            } else {
                heap_set_block_tag((s32 *) ATT_W(rec, 0x28), 4);
                heap_set_block_tag((s32 *) ATT_W(rec, 0x2C), 4);
            }
        }
        if (ATT_W(rec, 0x48) != 0) {
            animmodel_free(ATT_W(rec, 0x48));
        }
        shared_dl_release(rec[1]);
    }
    if (ATT_W(rec, 0x34) != 0) {
        if (now) {
            heap_free(ATT_W(rec, 0x34));
        } else {
            heap_set_block_tag((s32 *) ATT_W(rec, 0x34), 4);
        }
    }
    if (ATT_W(rec, 0x44) != 0) {
        heap_free(ATT_W(rec, 0x44));
    }
    if (ATT_W(rec, 0x4C) != 0) {
        if (now) {
            heap_free(ATT_W(rec, 0x4C));
        } else {
            heap_set_block_tag((s32 *) ATT_W(rec, 0x4C), 4);
        }
    }
    if (ATT_W(rec, 0x50) != 0) {
        if (now) {
            heap_free(ATT_W(rec, 0x50));
        } else {
            heap_set_block_tag((s32 *) ATT_W(rec, 0x50), 4);
        }
    }
    if ((u8 *) D_800C3EE0 == rec) {
        D_800C3EE0 = ATT_W(rec, 0x54);
    }
    prev = (u8 *) ATT_W(rec, 0x58);
    if (prev != NULL) {
        ATT_W(prev, 0x54) = ATT_W(rec, 0x54);
    }
    next = (u8 *) ATT_W(rec, 0x54);
    if (next != NULL) {
        ATT_W(next, 0x58) = ATT_W(rec, 0x58);
    }
    heap_free((s32) rec);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_free.s")
#endif

/* was func_150305E0 */
void attachment_remove_by_slot(s32 arg0, s32 arg1) {
    attachment_remove_by_slot_n(arg0, arg1, 0xFF);
}

#ifdef NON_MATCHING
/* was func_15030600 */
s32 attachment_remove_by_slot_n(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;
    s32 var_a0;
    s32 var_s0;
    s32 var_s5;

    var_s0 = arg2;
    if ((*(u8 *)((u8 *)arg0 + 0x3B)) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s5 = 0;
    if (var_a0 != 0) {
loop_3:
        temp_s1 = (*(s32 *)((u8 *)var_a0 + 0x54));
        if (((*(u8 *)((u8 *)arg0 + 0x3B)) == (*(u8 *)((u8 *)var_a0 + 0))) && (arg1 == (*(u8 *)((u8 *)var_a0 + 6)))) {
            if ((var_s0 != 0xFF) && (var_s0 != 0)) {
                var_s0 -= 1;
                var_a0 = temp_s1;
                goto block_10;
            }
            var_s5 = 1;
            attachment_free((struct127 *) var_a0, 0);
            if (var_s0 != 0) {
                goto block_9;
            }
        } else {
block_9:
            var_a0 = temp_s1;
block_10:
            if (var_a0 != 0) {
                goto loop_3;
            }
        }
    }
    return var_s5;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_remove_by_slot_n.s")
#endif
/* was func_150306D4 */
s32 attachment_remove_all_of_owner(u8 *arg0) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_s1;

    if ((*(u8 *)((u8 *)arg0 + 0x3B)) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s1 = 0;
    if (var_a0 != 0) {
        do {
            temp_s0 = (*(s32 *)((u8 *)var_a0 + 0x54));
            if ((*(u8 *)((u8 *)arg0 + 0x3B)) == (*(u8 *)var_a0)) {
                var_s1 = 1;
                attachment_free((u8 *) var_a0, 0);
            }
            var_a0 = temp_s0;
        } while (temp_s0 != 0);
    }
    return var_s1;
}

#ifdef NON_MATCHING
/* P65: the attachment records of the D_800C3EE0 list (offsets read from attachment_update_all's asm). */
typedef struct Attach {
    /* 0x00 */ u8 model;            /* model id for obj_find_by_setup_id */
    /* 0x01 */ u8 pad1;
    /* 0x02 */ u8 joint;            /* joint matrix of the model (64 bytes each) */
    /* 0x03 */ u8 pad3[2];
    /* 0x05 */ u8 seen;
    /* 0x06 */ u8 pad6;
    /* 0x07 */ u8 callback;         /* index into D_80084550, 0 = none */
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u16 ownerIds[3];     /* kept only while the model's +0x84 matches one of them (0 = unused) */
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u8 mode;             /* 4: scale the joint rotation by +0x40 */
    /* 0x17 */ u8 pad17[5];
    /* 0x1C */ u16 timer;           /* 0xFFFF = forever, else frames left (D_800BE9E4 per call) */
    /* 0x1E */ u16 subModel;        /* != 0: attached through attachment_find_by_slot / attachment_get_matrices (second pass) */
    /* 0x20 */ u16 subMtx;
    /* 0x22 */ s16 spin;            /* extra rotation (65536 = 360 degrees) */
    /* 0x24 */ u8 pad24[0x10];
    /* 0x34 */ Mtx *mtx;            /* two Mtx, one per DL buffer D_800BE9C0 */
    /* 0x38 */ u8 pad38[8];
    /* 0x40 */ f32 scale;
    /* 0x44 */ f32 *transform;      /* x, y, z, then rotation angles at +0xC / +0x10 / +0x14 */
    /* 0x48 */ u8 *target;          /* gets the matrix pointer at +0x3E0[D_800BE9C0], then animmodel_update_matrices */
    /* 0x4C */ u8 pad4C[8];
    /* 0x54 */ struct Attach *next;
} Attach;

extern s32 (*D_80084550[])(Attach *, u8 *);
s32 attachment_get_matrices(u8 *, u8 *, s32 *, s32 *);
u8 *attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);
void animmodel_update_matrices(u8 *);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/*
 * P65: per-frame update of the attachments (D_800C3EE0 list). Pass 0 handles the records without +0x1E (and notes
 * whether any has one), pass 1, only when needed, those attached to a sub-model. For each: its model (obj_find_by_setup_id)
 * must exist and the optional callback D_80084550[+7] must return 0, else the record is freed (attachment_free).
 * With a matrix buffer (+0x34) or a target (+0x48), the joint matrix (the model's joint +2, or the sub-model matrix
 * from attachment_get_matrices as f32) gives the record's matrix for this DL buffer: transformed by +0x44 (rotation, scale +0x40,
 * translation) / scaled to +0x40 (mode 4) / as is, then rotated by +0x22. The target gets the pointer. Records whose
 * owner ids no longer match the model's +0x84, or whose timer runs out, are freed.
 */
/* was func_15030758 */
void attachment_update_all(void) {
    Attach *rec;
    Attach *next;
    u8 *model;
    u8 *sub;
    u8 *joints;
    f32 (*src)[4];
    Mtx *out;
    s32 pass;
    s32 deferred;
    s32 subMtx;
    s32 unused;
    s32 keep;
    s32 i, r, c;
    u16 t;
    f32 k;
    f32 (*m)[4];
    f32 local[4][4];
    f32 norm[4][4];
    f32 xform[4][4];
    f32 rot[4][4];
    f32 res[4][4];

    deferred = FALSE;
    for (pass = 0; pass < 2; pass++) {
        if (pass == 1 && !deferred) {
            return;
        }
        for (rec = (Attach *) D_800C3EE0; rec != NULL; rec = next) {
            next = rec->next;
            if (pass == 0) {
                if (rec->subModel != 0) {
                    deferred = TRUE;
                    continue;
                }
            } else if (rec->subModel == 0) {
                continue;
            }

            model = (u8 *) obj_find_by_setup_id(rec->model);
            rec->seen = 1;
            if (model == NULL) {
                attachment_free((struct127 *) rec, 0);
                continue;
            }
            if (rec->callback != 0 && D_80084550[rec->callback](rec, model) != 0) {
                attachment_free((struct127 *) rec, 0);
                continue;
            }

            src = NULL;
            out = NULL;
            if (rec->mtx != NULL || rec->target != NULL) {
                joints = *(u8 **) (model + 0x1D4);
                if (joints != NULL) {
                    if (rec->subModel != 0) {
                        sub = attachment_find_by_slot(model, rec->subModel, 0);
                        if (sub == NULL) {
                            attachment_free((struct127 *) rec, 0);
                            continue;
                        }
                        if (attachment_get_matrices(sub, model, &subMtx, &unused) == 0) {
                            attachment_free((struct127 *) rec, 0);
                            continue;
                        }
                        src = local;
                        if (*(s32 *) (sub + 0x48) != 0) {
                            subMtx += rec->subMtx * sizeof(Mtx);
                        }
                        guMtxL2F(local, (Mtx *) subMtx);
                    } else {
                        src = (f32 (*)[4]) (joints + rec->joint * 64);
                    }

                    if (rec->mtx != NULL) {
                        out = &rec->mtx[D_800BE9C0];
                        if (rec->transform != NULL || rec->mode == 4) {
                            /* rotation rows scaled to length 1 (transform) or +0x40 (mode 4), column 3 cleared,
                             * translation row kept */
                            for (r = 0; r < 3; r++) {
                                k = ((rec->transform != NULL) ? 1.0f : rec->scale) /
                                    sqrtf(src[r][0] * src[r][0] + src[r][1] * src[r][1] + src[r][2] * src[r][2]);
                                for (c = 0; c < 3; c++) {
                                    norm[r][c] = src[r][c] * k;
                                }
                                norm[r][3] = 0.0f;
                                norm[3][r] = src[3][r];
                            }
                            norm[3][3] = 1.0f;
                            m = norm;
                        } else {
                            /* the joint matrix itself, made affine in place */
                            src[0][3] = 0.0f;
                            src[1][3] = 0.0f;
                            src[2][3] = 0.0f;
                            src[3][3] = 1.0f;
                            m = src;
                        }
                        if (rec->transform != NULL) {
                            /* rotation +0xC..+0x14 and scale +0x40, then translation +0..+8, applied first */
                            mtx_rotate_scale_3x3(xform, rec->transform[3], rec->transform[4], rec->transform[5],
                                          rec->scale, rec->scale, rec->scale);
                            xform[0][3] = 0.0f;
                            xform[1][3] = 0.0f;
                            xform[2][3] = 0.0f;
                            xform[3][0] = rec->transform[0];
                            xform[3][1] = rec->transform[1];
                            xform[3][2] = rec->transform[2];
                            xform[3][3] = 1.0f;
                            mtxf_mul(xform, norm, res);
                            guMtxF2L(res, out);
                        } else if (rec->spin != 0) {
                            /* extra rotation by spin (65536 = 360 degrees) */
                            mtxf_rotate_xyz_deg(rot, 0.0f, 0.0f, rec->spin * (360.0f / 65536.0f));
                            mtxf_mul(rot, m, res);
                            guMtxF2L(res, out);
                        } else {
                            guMtxF2L(m, out);
                        }
                    }
                }
            }

            if (rec->target != NULL) {
                ((void **) (rec->target + 0x3E0))[D_800BE9C0] = (rec->mtx != NULL) ? (void *) out : (void *) src;
                animmodel_update_matrices(rec->target);
            }

            if (rec->ownerIds[0] != 0) {
                keep = FALSE;
                for (i = 0; i < 3; i++) {
                    if (rec->ownerIds[i] != 0 && *(u16 *) (model + 0x84) == rec->ownerIds[i]) {
                        keep = TRUE;
                        break;
                    }
                }
                if (!keep) {
                    attachment_free((struct127 *) rec, 0);
                    continue;
                }
            }

            t = rec->timer;
            if (t != 0xFFFF) {
                if (t == 0) {
                    attachment_free((struct127 *) rec, 0);
                } else if (D_800BE9E4 < t) {
                    rec->timer = t - D_800BE9E4;
                } else {
                    rec->timer = 0;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_update_all.s")
#endif

#ifdef NON_MATCHING
s32 attachment_load_model(struct127 *, u8 *);

/* was func_15030DE4 */
struct127 *attachment_create(u8 *arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9, s32 argA, s32 argB, s32 argC) {
    s32 sp24;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_t1;
    struct127 *temp_v0;
    struct127 *temp_v0_3;
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x3B));
    if (temp_v1 == 0) {
        return NULL;
    }
    if (!(arg3 & 8)) {
        var_s0 = D_800C3EE0;
        if (var_s0 != 0) {
loop_4:
            temp_v0_2 = (*(s32 *)((u8 *)var_s0 + 0x54));
            if ((temp_v1 == (*(u8 *)((u8 *)var_s0 + 0))) && (arg7 == (*(u8 *)((u8 *)var_s0 + 6))) && (arg1 == (*(u8 *)((u8 *)var_s0 + 1)))) {
                return NULL;
            }
            var_s0 = temp_v0_2;
            if (temp_v0_2 == 0) {
                goto block_9;
            }
            goto loop_4;
        }
    }
block_9:
    temp_v0 = allocate_memory(0x5C, 1, 0, 2);
    if (temp_v0 == NULL) {
        return NULL;
    }
    var_t1 = 0;
    if (D_800C3EE0 != 0) {
        (*(struct127 **)((u8 *)D_800C3EE0 + 0x58)) = temp_v0;
    }
    temp_v0->unk54 = (*(f32 *)&(D_800C3EE0));
    temp_v0->unk58 = 0;
    D_800C3EE0 = (s32) temp_v0;
    (*(s8 *)((u8 *)temp_v0 + 1)) = arg1;
    (*(u8 *)((u8 *)temp_v0 + 0)) = (u8) (*(u8 *)((u8 *)arg0 + 0x3B));
    temp_v0->gravity = 0.0f;
    temp_v0->unk28 = 0.0f;
    temp_v0->old_x_position = 0.0f;
    temp_v0->old_y_position = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 3)) = 0xFF;
    temp_v0->unk44 = 0.0f;
    temp_v0->id = (u8) arg3;
    temp_v0->unk6 = (u8) arg7;
    temp_v0->unk40 = 1.0f;
    (*(s8 *)((u8 *)temp_v0 + 2)) = (s8) arg2;
    (*(s32 *)((u8 *)temp_v0 + 0x38)) = 0;
    temp_v0->xz_velocity = 0.0f;
    temp_v0->unk8 = 0;
    temp_v0->unk9 = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x18)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x1A)) = 0;
    temp_v0->unk7 = (u8) arg8;
    (*(u16 *)((u8 *)temp_v0 + 0xA)) = (u16) (*(u16 *)((u8 *)arg9 + 0));
    (*(u16 *)((u8 *)temp_v0 + 0xC)) = (u16) (*(u16 *)((u8 *)arg9 + 2));
    temp_v0->unkE.h = (s16) (*(u16 *)((u8 *)arg9 + 4));
    temp_v0->unk48 = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0x17)) = (s8) argA;
    (*(s8 *)((u8 *)temp_v0 + 0x16)) = (s8) arg5;
    (*(s8 *)((u8 *)temp_v0 + 0x15)) = (s8) arg4;
    (*(s16 *)((u8 *)temp_v0 + 0x1E)) = (s16) argB;
    temp_v0->unk13 = 0;
    temp_v0->animation_speed = 0.0f;
    temp_v0->unk50 = NULL;
    temp_v0->unk5 = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x22)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x20)) = (s16) argC;
    if ((arg5 == 4) || (arg3 & 4)) {
        sp24 = 0;
        temp_v0_3 = allocate_memory(0x80, 1, 2, 2);
        var_t1 = 0;
        temp_v0->old_z_position = (*(f32 *)&(temp_v0_3));
        if (temp_v0_3 == NULL) {
            var_t1 = 1;
        }
    } else {
        temp_v0->old_z_position = 0.0f;
    }
    if (arg6 == 0) {
        (*(s16 *)((u8 *)temp_v0 + 0x1C)) = 0xFFFF;
    } else {
        (*(s16 *)((u8 *)temp_v0 + 0x1C)) = (s16) arg6;
    }
    if (var_t1 == 0) {
        sp24 = var_t1;
        var_t1 |= attachment_load_model(temp_v0, arg0);
    }
    if (var_t1 != 0) {
        attachment_free(temp_v0, 1);
        return NULL;
    }
    attachment_apply_kind_effects(temp_v0, arg0);
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_create.s")
#endif
#ifdef NON_MATCHING
f32 *allocate_memory(s32, s32, s32, s32);

/* was func_15031044 */
void attachment_set_local_transform(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 *temp_v0;

    temp_v0 = allocate_memory(0x18, 1, 0, 2);
    (*(f32 **)((u8 *)arg0 + 0x44)) = temp_v0;
    if (temp_v0 != NULL) {
        *temp_v0 = arg1;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 4)) = arg2;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 8)) = arg3;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 0xC)) = arg4;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 0x10)) = arg5;
        (*(f32 *)((u8 *)((*(f32 **)((u8 *)arg0 + 0x44))) + 0x14)) = arg6;
        if ((*(f32 **)((u8 *)arg0 + 0x34)) == NULL) {
            (*(f32 **)((u8 *)arg0 + 0x34)) = allocate_memory(0x80, 1, 2, 2);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_set_local_transform.s")
#endif
#ifdef NON_MATCHING
s32 attachment_draw(s32, u8 *, struct127 *, s32, s32);

/* was func_150310F8 */
s32 attachment_draw_all_for_player(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s6;
    struct127 *temp_v0;

    var_s6 = arg0;
    var_s0 = D_800C3EE0;
    if (var_s0 != 0) {
        do {
            temp_s2 = (*(s32 *)((u8 *)var_s0 + 0x54));
            if ((*(u8 *)((u8 *)var_s0 + 3)) == 0) {

            } else {
                temp_v0 = obj_find_by_setup_id((*(u8 *)((u8 *)var_s0 + 0)));
                if ((temp_v0 == NULL) || (temp_v0->unk1D4 == NULL) || (temp_v1 = 1 << arg1, (temp_v1 == (temp_v0->unk74 & temp_v1)))) {

                } else if (arg2 == 2) {
                    if (temp_v0->unk5 != 7) {

                    } else {
                        goto block_19;
                    }
                } else {
                    temp_v0_2 = obj_get_player_alpha(temp_v0, arg1);
                    if (arg2 == 1) {
                        if (!((*(u8 *)((u8 *)var_s0 + 4)) & 2) && (temp_v0_2 == 0xFF) && (temp_v0->unk5 != 1)) {

                        } else {
                            goto block_19;
                        }
                    } else if (((*(u8 *)((u8 *)var_s0 + 4)) & 2) || (temp_v0_2 < 0xFF) || (temp_v0->unk5 == 1)) {

                    } else {
block_19:
                        var_s6 = attachment_draw(var_s6, (u8 *) var_s0, temp_v0, arg1, 0);
                    }
                }
            }
            var_s0 = temp_s2;
        } while (var_s0 != 0);
    }
    return var_s6;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_draw_all_for_player.s")
#endif
#ifdef NON_MATCHING
#ifndef NON_MATCHING
s32 attachment_draw(s32, u8 *, u8 *, s32, s32);
#endif

/* was func_15031284 */
s32 attachment_draw_for_object(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;
    s32 var_s0;
    s32 var_s3;

    var_s3 = arg0;
    if ((arg1 == NULL) || ((*(s32 *)((u8 *)arg1 + 0x1D4)) == 0) || ((*(u8 *)((u8 *)arg1 + 0x3B)) == 0)) {

    } else {
        var_s0 = D_800C3EE0;
        if (var_s0 != 0) {
            do {
                temp_s1 = (*(s32 *)((u8 *)var_s0 + 0x54));
                if (((*(u8 *)((u8 *)arg1 + 0x3B)) != (*(u8 *)((u8 *)var_s0 + 0))) || ((*(u8 *)((u8 *)var_s0 + 3)) == 0)) {

                } else {
                    var_s3 = attachment_draw(var_s3, (u8 *) var_s0, arg1, arg2, arg3);
                }
                var_s0 = temp_s1;
            } while (var_s0 != 0);
        }
    }
    return var_s3;
}
#else
#ifdef NON_MATCHING
s32 attachment_draw_for_object(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;
    s32 var_s0;
    s32 var_s3;

    var_s3 = arg0;
    if ((arg1 == NULL) || ((*(s32 *)((u8 *)arg1 + 0x1D4)) == 0) || ((*(u8 *)((u8 *)arg1 + 0x3B)) == 0)) {

    } else {
        var_s0 = D_800C3EE0;
        if (var_s0 != 0) {
            do {
                temp_s1 = (*(s32 *)((u8 *)var_s0 + 0x54));
                if (((*(u8 *)((u8 *)arg1 + 0x3B)) != (*(u8 *)((u8 *)var_s0 + 0))) || ((*(u8 *)((u8 *)var_s0 + 3)) == 0)) {

                } else {
                    var_s3 = attachment_draw(var_s3, (u8 *) var_s0, arg1, arg2, arg3);
                }
                var_s0 = temp_s1;
            } while (var_s0 != 0);
        }
    }
    return var_s3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_draw_for_object.s")
#endif
#endif
#ifdef NON_MATCHING
u8 * attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);

/* was func_15031360 */
s32 attachment_get_matrices(u8 *arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_t9;
    s32 temp_v0_2;
    s32 var_t3;
    u16 temp_v0_3;
    u8 *temp_v0;
    u8 *temp_v0_4;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x48));
    if (temp_v0 != NULL) {
        if ((*(u8 *)((u8 *)temp_v0 + 0x3F6)) == 0) {
            return 0;
        }
        *arg2 = (*(s32 *)((u8 *)((temp_v0 + (D_800BE9C0 * 4))) + 0x3E8));
        *arg3 = (*(s32 *)((u8 *)(((*(u8 **)((u8 *)arg0 + 0x48)) + (D_800BE9C0 * 4))) + 0x3E0));
        goto block_14;
    }
    temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x34));
    if (temp_v0_2 != 0) {
        *arg2 = temp_v0_2 + (D_800BE9C0 << 6);
        var_t3 = (*(s32 *)((u8 *)arg1 + 0x1D4)) + ((*(u8 *)((u8 *)arg0 + 2)) << 6);
        goto block_13;
    }
    temp_v0_3 = (*(u16 *)((u8 *)arg0 + 0x1E));
    if (temp_v0_3 != 0) {
        temp_v0_4 = attachment_find_by_slot(arg1, temp_v0_3, 0);
        if (temp_v0_4 == NULL) {
            return 0;
        }
        if (attachment_get_matrices(temp_v0_4, arg1, arg2, arg3) == 0) {
            return 0;
        }
        *arg2 += (*(u16 *)((u8 *)arg0 + 0x20)) << 6;
        goto block_14;
    }
    temp_t9 = (*(s32 *)((u8 *)arg1 + 0x1D4));
    *arg2 = temp_t9;
    var_t3 = temp_t9 + ((*(u8 *)((u8 *)arg0 + 2)) << 6);
    *arg2 = var_t3;
block_13:
    *arg3 = var_t3;
block_14:
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_get_matrices.s")
#endif
#ifdef NON_MATCHING
extern u8 D_80083350[];     /* segment 8: blended (alpha < 0xFF) material set */
extern u8 D_800834D0[];     /* segment 8: opaque material set */
extern u8 D_800DD714[];     /* fog colour r, g, b when the level fogs (header +0x3E) */
extern u8 D_800DA248[];
extern s32 D_800BEFC4;      /* display list capacity (commands) */
s32 attachment_get_matrices(u8 *, u8 *, s32 *, s32 *);
void obj_ambient_colour(s32 arg0, u8 *arg1);
void obj_fog_alpha(u8 *rec, s32 *col, s32 view);
void obj_unpack_light_colours(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8,
                   s32 *arg9, s32 *argA, s32 *argB, s32 *argC, s32 *argD);
void obj_alloc_light_bufs(u8 *);
u8 *light_write_light_cmds(u8 *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4);
Gfx *light_apply_object_lights(Gfx *, s32, s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, u8 *, s32, u8 *);
s32 texture_cache_lookup(s32, s32 *, s32, s32);
u8 *reflect_emit_entries_dl(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);

/* one display list command */
#define ATT_DL(g, a, b)              \
    {                                \
        ((u32 *) (g))[0] = (a);      \
        ((u32 *) (g))[1] = (u32) (b); \
        (g)++;                       \
    }

/*
 * P76: draw attachment att (+3 alpha, +5 visible, +0x13 / +0x14 hidden-part mask / part count, +0x18 / +0x1A
 * texture ids for segments 6 / 7, +0x24 part display lists, +0x28 per-buffer segment 1) of object obj for player
 * view `player`: alpha scaled by obj_get_player_alpha, segment 8 = blended or opaque material set, matrix (segment 3) from
 * attachment_get_matrices (nothing drawn without one), fog / tint colours from obj_ambient_colour / obj_fog_alpha / obj_unpack_light_colours,
 * lighting by the object's +0x66 mode (lights +0x304[player] built by obj_alloc_light_bufs on demand, light_write_light_cmds /
 * light_apply_object_lights), then the parts (or reflect_emit_entries_dl when special != 0). When the display list would overflow
 * (D_800BEFC4 commands from D_800BEDE8[D_800BE9C0]) the commands are dropped (the start pointer is returned).
 */
/* was func_150314B4 */
s32 attachment_draw(s32 gfxp, u8 *att, struct127 *objp, s32 player, s32 special) {
    Gfx *start = (Gfx *) gfxp;
    Gfx *gfx = start;
    u8 *obj = (u8 *) objp;
    s32 alpha;
    s32 v;
    s32 mtx;
    s32 unused110;
    s32 col[4];
    s32 i;
    s32 lit;
    s32 created;
    s32 lights;
    s32 fogs;
    s32 size;
    s32 fogA, primR, primG, primB, envR, envG, envB, fogR, fogG, fogB;

    if (att[5] == 0) {
        return (s32) gfx;
    }
    ATT_DL(gfx, 0xE7000000, 0);     /* pipe sync */
    alpha = att[3];
    v = obj_get_player_alpha(objp, player);
    if (v != 0xFF) {
        alpha = (v * alpha) >> 8;
    }
    if (alpha < 0xFF) {
        ATT_DL(gfx, 0xDB060020, D_80083350);
    } else {
        ATT_DL(gfx, 0xDB060020, D_800834D0);
    }
    if (attachment_get_matrices(att, obj, &mtx, &unused110) == 0) {
        return (s32) gfx;
    }
    i = (obj - (u8 *) D_800CC2D0) / (s32) sizeof(struct127);
    obj_ambient_colour(i, (u8 *) col);
    if (*(s16 *) ((u8 *) D_800B0DF0 + 0x3E) != 0) {
        obj_fog_alpha((u8 *) &D_800CC2D0[i], col, player);
    } else {
        col[3] = 0xFF;
    }
    obj_unpack_light_colours(obj, player, alpha, (u8 *) col, &primR, &primG, &primB, &envR, &envG, &envB, &fogR, &fogG, &fogB,
                  &fogA);
    fogs = *(s16 *) ((u8 *) D_800B0DF0 + 0x3E);

    lit = TRUE;
    if ((obj[0x66] & 0xC) == 0xC) {
        ATT_DL(gfx, 0xD9FFFFFF, 0x20000);
        ATT_DL(gfx, 0xD9BFFFFF, 0);
    } else if ((obj[0x66] & 0xC) != 8 && !(att[4] & 1)) {
        ATT_DL(gfx, 0xD9BDFFFF, 0);
        lit = FALSE;
    } else if (D_800DCD7C != 0) {
        ATT_DL(gfx, 0xD9FFFFFF, 0x420000);
    } else {
        ATT_DL(gfx, 0xD9BDFFFF, 0);
        lit = FALSE;
    }
    if (lit) {
        created = FALSE;
        lights = *(s32 *) (obj + 0x304 + player * 4);
        if (lights == 0) {
            obj_alloc_light_bufs(obj);
            created = TRUE;
            lights = *(s32 *) (obj + 0x304 + player * 4);
        }
        if (lights != 0) {
            size = (obj[0x2FD] != 0 || created) ? 10 : 2;
            if (obj[5] != 5 && obj[0x302] != 0 && (obj[0x66] & 0xC) != 0 && !created) {
                gfx = (Gfx *) light_write_light_cmds((u8 *) gfx, lights, obj[0x301], obj[0x302],
                                            *(s32 *) (obj + 0x314) + D_800BE9C0 * 8);
            } else {
                gfx = light_apply_object_lights(gfx, player, *(f32 *) (obj + 0x14), *(f32 *) (obj + 0x18), *(f32 *) (obj + 0x1C),
                                    *(s32 *) (obj + 0x184), lights, obj[0x301],
                                    (u8 *) (*(s32 *) (obj + 0x314) + D_800BE9C0 * 8), obj + 0x302, 2, obj + 0x1DD,
                                    size, D_800DA248);
            }
        }
    }
    if (fogs == 0) {
        ATT_DL(gfx, 0xF8000000, (fogR << 24) | ((fogG & 0xFF) << 16) | ((fogB & 0xFF) << 8) | (fogA & 0xFF));
    } else {
        ATT_DL(gfx, 0xF8000000, (D_800DD714[0] << 24) | (D_800DD714[1] << 16) | (D_800DD714[2] << 8) | (fogA & 0xFF));
    }
    ATT_DL(gfx, 0xF8000000, (fogR << 24) | ((fogG & 0xFF) << 16) | ((fogB & 0xFF) << 8) | (fogA & 0xFF));
    ATT_DL(gfx, 0xFA00F200, (primR << 24) | ((primG & 0xFF) << 16) | ((primB & 0xFF) << 8));
    ATT_DL(gfx, 0xFB000000, (envR << 24) | ((envG & 0xFF) << 16) | ((envB & 0xFF) << 8) | (alpha & 0xFF));
    ATT_DL(gfx, 0xDB06000C, mtx);
    ATT_DL(gfx, 0xDB060004, *(s32 *) (att + 0x28 + D_800BE9C0 * 4));
    if (*(u16 *) (att + 0x18) != 0) {
        v = texture_cache_lookup(*(u16 *) (att + 0x18), &size, 0x3E, 0);
        ATT_DL(gfx, 0xDB060018, v);
    }
    if (*(u16 *) (att + 0x1A) != 0) {
        v = texture_cache_lookup(*(u16 *) (att + 0x1A), &size, 0x3E, 0);
        ATT_DL(gfx, 0xDB06001C, v);
    }
    if (!special) {
        ATT_DL(gfx, 0xD9FFFFFF, 0x400);
        for (i = 0; i < att[0x14]; i++) {
            if (!(att[0x13] & (1 << i))) {
                ATT_DL(gfx, 0xDE000000, (*(s32 **) (att + 0x24))[i]);
            }
        }
    } else {
        ATT_DL(gfx, 0xD9FFFFFF, 0x200);
        gfx = (Gfx *) reflect_emit_entries_dl((u8 *) gfx, att, envR, envG, envB);
    }
    if (gfx - D_800BEDE8[D_800BE9C0] > D_800BEFC4) {
        return (s32) start;
    }
    return (s32) gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_draw.s")
#endif

/* was func_15031C1C */
void attachment_set_alpha_by_slot(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0 = attachment_find_by_slot(arg0, arg1, arg3);
    if (temp_v0 != NULL) {
        temp_v0[3] = arg2;
    }
}

#ifdef NON_MATCHING
// attachment_find_nth: returns the arg2-th (0 = first) entry of the D_800C3EE0 list whose owner id (+0) is obj+0x3B
// and whose sub id (+6) is arg1, or NULL.
/* was func_15031C4C */
u8 * attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_a2;
    s32 var_v1;
    u8 temp_v0;

    var_a2 = arg2;
    temp_v0 = (*(u8 *)((u8 *)arg0 + 0x3B));
    if (temp_v0 == 0) {
        return NULL;
    }
    var_v1 = D_800C3EE0;
    if (var_v1 != 0) {
loop_3:
        if ((temp_v0 == (*(u8 *)((u8 *)var_v1 + 0))) && (arg1 == (*(u8 *)((u8 *)var_v1 + 6)))) {
            /* P272: the asm tests a2 == 0 before the decrement (beqz in front of the
               delay-slot addiu), so a2 = 0 returns the first match. */
            if (var_a2 == 0) {
                return (u8 *) var_v1;
            }
            var_a2 -= 1;
        }
        var_v1 = (*(s32 *)((u8 *)var_v1 + 0x54));
        if (var_v1 == 0) {
            /* Duplicate return node #9. Try simplifying control flow for better match */
            return NULL;
        }
        goto loop_3;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_find_by_slot.s")
#endif
/* was func_15031CBC */
u8 *attachment_find_by_slot_any(s32 arg0, u8 *arg1) {
    u8 *n;
    u8 *next;

    if (arg1 != NULL) {
        n = (u8 *)D_800C3EE0;
        if (n != NULL) {
            do {
                next = *(u8 **)(n + 0x54);
                if (arg1[0x3B] == n[0] && arg0 == n[6]) {
                    return n;
                }
                n = next;
            } while (n != NULL);
        }
    }
    n = (u8 *)D_800C3EE0;
    if (n != NULL) {
        do {
            next = *(u8 **)(n + 0x54);
            if (arg0 == n[6]) {
                return n;
            }
            n = next;
        } while (n != NULL);
    }
    return NULL;
}

#ifdef NON_MATCHING
s32 object_fire_spawn(u8 *, s32, s32);
void fire_smoke_trail_spawn(u8 *, u8, s32);
void obj_timer_link_spawn(u8 *);
s32 light_create_joint_pulse(u8 *, s32, s32);
s32 aura_burst_group_spawn(u8 *, s32, s32);
void char_glow_trail_spawn(u8 *, u8, s8, u8, s32);
extern s32 D_800905D8;
extern s32 D_800905DC;

// attachment_start_effect: runs the start effect of an attachment record by its kind (rec[1]): two jump tables
// in the asm, kinds 0x82..0x90 (jtbl_800972F0) and 0x37..0x5E (jtbl_8009732C), plus kind 0x1D. P272 rewrite: the
// m2c C nested the low kinds inside the 0x82..0x90 branch, so they never ran.
/* was func_15031D40 */
void attachment_apply_kind_effects(u8 *arg0, u8 *arg1) {
    u8 kind = arg0[1];
    u8 *other;

    if (kind >= 0x5F) {
        switch (kind) {
        case 0x82:
            char_glow_trail_spawn(arg1, 6, -1, 0xFF, 1);
            break;
        case 0x85:
            *(s32 *)(arg1 + 0x9C) |= 0x6000;
            break;
        case 0x8D:
            if (player_stat_get(0, 6) < 0x64) {
                *(s16 *)(arg0 + 0x18) = (s16) D_800905D8;
            } else {
                *(s16 *)(arg0 + 0x18) = (s16) D_800905DC;
            }
            break;
        case 0x8F:
            *(s32 *)(arg1 + 0x9C) |= 0xE00;
            break;
        case 0x90:
            *(s32 *)(arg1 + 0x9C) |= 0x70;
            break;
        }
        return;
    }
    if (kind == 0x1D) {
        char_glow_trail_spawn(arg1, 0, 2, 0xFF, 1);
        return;
    }
    switch (kind) {
    case 0x37:
        obj_timer_link_spawn(arg1);
        break;
    case 0x3D:
        aura_burst_group_spawn(arg1, 0xFF, 1);
        break;
    case 0x49:
        light_create_joint_pulse(arg1, 0xFF, 1);
        break;
    case 0x5A:
        other = *(u8 **)(arg1 + 0x31C);
        if (other != NULL) {
            *(u16 *)(other + 0x1A6) += 0xAA;
        }
        break;
    case 0x5D:
        object_fire_spawn(arg1, 0xFF, 1);
        fire_smoke_trail_spawn(arg1, 0xFF, 1);
        break;
    case 0x5E:
        *(s32 *)(arg1 + 0x9C) |= 0x6000;
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_apply_kind_effects.s")
#endif
#ifdef NON_MATCHING
struct127 *obj_find_by_setup_id(u8);
void obj_timer_link_post_remove(u8 *);
void light_ctrl_broadcast(u8, u8, s32);
void fxrec_broadcast(s32, u8);
void effect_nodes_broadcast(s32, u8);
void obj_aura_burst_stop(u8 *);
void obj_point_fx_broadcast_kill(u8 *);
void char_glow_broadcast_kill(u8 *);
void obj_glow_post_remove_event(u8 *);

/*
 * P71: undoes what attachment record rec (model id +1) did to its owner object (obj_find_by_setup_id(+0), none: nothing):
 * flag bits of +0x9C are cleared per model (0x90: 0x70, 0x8F: 0xE00, 0x85 / 0x5E: 0x6000), models 0x37 / 0x4B / 0x4C
 * queue attachment_sound_cb (sfx_emitter_stop_by_callback; 0x37 also obj_timer_link_post_remove), 0x49 / 0x5D send messages with the owner and its
 * +0x3B, 0x5A lowers +0x31C->+0x1A6 by 0xAA; others call per-model handlers. Records of kind +6 = 0x16 / 0x63 /
 * 0x89 also call obj_glow_post_remove_event and obj_point_fx_broadcast_kill.
 */
/* was func_15031F04 */
void attachment_undo_kind_effects(u8 *rec) {
    struct {
        u8 *obj;
        u8 id;
    } msg;
    u8 *obj;
    u8 *p;

    obj = (u8 *) obj_find_by_setup_id(rec[0]);
    if (obj == NULL) {
        return;
    }
    switch (rec[1]) {
        case 0x82:
        case 0x1D:
            char_glow_broadcast_kill(obj);
            break;
        case 0x85:
        case 0x5E:
            *(s32 *) (obj + 0x9C) &= ~0x6000;
            break;
        case 0x8F:
            *(s32 *) (obj + 0x9C) &= ~0xE00;
            break;
        case 0x90:
            *(s32 *) (obj + 0x9C) &= ~0x70;
            break;
        case 0x1A:
        case 0x1B:
        case 0x5F:
        case 0x65:
        case 0x66:
            obj_point_fx_broadcast_kill(obj);
            break;
        case 0x5A:
            p = *(u8 **) (obj + 0x31C);
            if (p != NULL) {
                *(u16 *) (p + 0x1A6) -= 0xAA;
            }
            break;
        case 0x37:
        case 0x4B:
        case 0x4C:
            sfx_emitter_stop_by_callback((s32 *) attachment_sound_cb, rec, obj);
            if (rec[1] == 0x37) {
                obj_timer_link_post_remove(obj);
            }
            break;
        case 0x49:
            msg.obj = obj;
            msg.id = obj[0x3B];
            light_ctrl_broadcast(0x10, 0x29, (s32) &msg);
            break;
        case 0x5D:
            msg.obj = obj;
            msg.id = obj[0x3B];
            fxrec_broadcast((s32) &msg, 0x2E);
            effect_nodes_broadcast((s32) &msg, 0x2F);
            break;
        case 0x3D:
            obj_aura_burst_stop(obj);
            break;
    }
    if (rec[6] == 0x16 || rec[6] == 0x63 || rec[6] == 0x89) {
        obj_glow_post_remove_event(obj);
        obj_point_fx_broadcast_kill(obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_undo_kind_effects.s")
#endif

/* was func_1503211C */
s32 attachment_cb_texture_pingpong(u8 *arg0, s32 arg1) {
    s32 var_v0 = *(s32 *)(arg0 + 0x38);

    if (*(s32 *)(arg0 + 0x38) >= 3) {
        var_v0 = 5 - var_v0;
    }
    *(s16 *)(arg0 + 0x18) = D_8009066C[var_v0];
    (*(s32 *)(arg0 + 0x38))++;
    if (*(s32 *)(arg0 + 0x38) >= 6) {
        *(s32 *)(arg0 + 0x38) = 0;
    }
    return 0;
}

#ifdef NON_MATCHING
extern f32 D_8009748C; /* 1 / 60 */

/*
 * P70: model callback: animates the tile size of a texture by the height +0x08 of the record +0x2D0 of obj.
 * arg0 +0x24 points at the display list pointer; its 4th G_SETTILESIZE (0xF2) command gets s = 25 * t + 2 in
 * its first word (t = 1 in animation 0x55, 0 in 0x56, else 1 - y / 60 for y in 0..120, 0 outside).
 * Returns 0 (also when there is no record or display list).
 */
/* was func_1503216C */
s32 attachment_cb_tile_by_height(u8 *arg0, struct127 *obj) {
    u8 *rec = (u8 *) obj->unk2D0;
    u32 *dl;
    f32 t;
    f32 y;
    s32 i;
    s32 left;

    if (rec == NULL) {
        return 0;
    }
    dl = **(u32 ***) (arg0 + 0x24);
    if (dl == NULL) {
        return 0;
    }
    if (obj->unk84.uh == 0x55) {
        t = 1.0f;
    } else if (obj->unk84.uh == 0x56) {
        t = 0.0f;
    } else {
        y = *(f32 *) (rec + 8);
        if (0.0f <= y && y <= 120.0f) {
            t = 1.0f - y * D_8009748C;
        } else {
            t = 0.0f;
        }
    }
    /* find the 4th G_SETTILESIZE (first byte 0xF2) of the list */
    i = 0;
    left = 4;
    do {
        left--;
        while (*(s8 *) &dl[i * 2] != -14) {
            i++;
        }
        if (left != 0) {
            i++;
        }
    } while (left != 0);
    dl[i * 2] = 0xF2002000 | ((s32) (25.0f * t + 2.0f) & 0xFFF);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_cb_tile_by_height.s")
#endif

#ifdef NON_MATCHING
extern s32 D_80090680;      /* att+0x18 for kinds 0x5A / 0x74 / 0x7A when obj+0x2E8 == 0 */
extern s32 D_80090684;      /* ... and when obj+0x2E8 != 0 */
void anim_state_snapshot(u8 *);

/* Tables of attachment_cb_sync_animation: animation index by animation id, generated from the ROM's jump tables by
 * docs/port/sessions/p80/gen_150322B8.py (do not edit by hand). 0 = the model's default animation. */
static const u8 sAnim_8009751C[0x2B] = {
    /* 0x000 */ 0x05, 0x03, 0x06, 0x06, 0x09, 0x0A, 0x07, 0x02, 0x10, 0x06, 0x04, 0x06, 0x06, 0x06, 0x06, 0x08,
    /* 0x010 */ 0x0B, 0x06, 0x06, 0x0D, 0x0E, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x08, 0x06,
    /* 0x020 */ 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0F, 0x0F, 0x06, 0x06, 0x03,
};

static const u8 sAnim_8009763C[0x10] = {
    /* 0x014 */ 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
};

static const u8 sAnim_8009767C[0x1CF] = {
    /* 0x17F */ 0x1A, 0x1B, 0x1C, 0x1D, 0x00, 0x00, 0x00, 0x1E, 0x1F, 0x00, 0x20, 0x00, 0x00, 0x21, 0x22, 0x23,
    /* 0x18F */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x19F */ 0x00, 0x24, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x1AF */ 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x2D,
    /* 0x1BF */ 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x00, 0x00, 0x00, 0x00,
    /* 0x1CF */ 0x00, 0x00, 0x3A, 0x3B, 0x3C, 0x00, 0x3D, 0x7F, 0x86, 0x85, 0x3E, 0x3F, 0x40, 0x00, 0x00, 0x00,
    /* 0x1DF */ 0x00, 0x00, 0x00, 0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x47, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x1EF */ 0x00, 0x48, 0x49, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x00,
    /* 0x1FF */ 0x00, 0x50, 0x4B, 0x4D, 0x4E, 0x4F, 0x51, 0x00, 0x00, 0x52, 0x53, 0x54, 0x55, 0x56, 0x00, 0x00,
    /* 0x20F */ 0x00, 0x00, 0x57, 0x58, 0x00, 0x00, 0x00, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x6F, 0x00, 0x00,
    /* 0x21F */ 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63,
    /* 0x22F */ 0x64, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x66, 0x67, 0x00, 0x00,
    /* 0x23F */ 0x00, 0xE9, 0x70, 0x00, 0x00, 0x00, 0x68, 0x69, 0x00, 0x6A, 0x6B, 0x6C, 0x6D, 0x00, 0x6E, 0x00,
    /* 0x24F */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x72, 0x73,
    /* 0x25F */ 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x76, 0x77, 0x78, 0x79, 0x00, 0x7A, 0x7B, 0x7C, 0x7D, 0x00,
    /* 0x26F */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x80, 0x81, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x27F */ 0x83, 0x84, 0x87, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x28F */ 0x00, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x00, 0x00, 0x8F, 0x00, 0x90, 0x91, 0x92, 0x93, 0x00,
    /* 0x29F */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0x95, 0x00, 0x96, 0x97, 0x98,
    /* 0x2AF */ 0x99, 0x9A, 0x00, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0x00, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,
    /* 0x2BF */ 0xA7, 0xA8, 0xA9, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x2CF */ 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xAC, 0xAD, 0xAF, 0xAE, 0x00,
    /* 0x2DF */ 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xB7, 0xB8,
    /* 0x2EF */ 0xB9, 0xBA, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x2FF */ 0x00, 0x00, 0xBE, 0x00, 0x00, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
    /* 0x30F */ 0xCA, 0x00, 0x00, 0x00, 0x00, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0x00, 0x00, 0xD1, 0xD2, 0xD3,
    /* 0x31F */ 0xD5, 0xD4, 0xD6, 0xD7, 0xD8, 0xD9, 0x00, 0xDA, 0xDB, 0xDC, 0x00, 0x00, 0xDD, 0xDE, 0xDF, 0xE0,
    /* 0x32F */ 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x33F */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0,
};

static const u8 sAnim_80097DB8[0x4E] = {
    /* 0x104 */ 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x114 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00,
    /* 0x124 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x134 */ 0x09, 0x0A, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00,
    /* 0x144 */ 0x00, 0x0F, 0x10, 0x12, 0x13, 0x14, 0x15, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
};

/*
 * P80: attachment callback 5. Chooses the animation of attachment att's animation state (att+0x48) from the owner
 * object's kind (obj[4]), the attachment's model id (att[1]) and the object's animation id (obj+0x84), setting the
 * attachment's mode att[2] (and +0x18 / +0x1E / +0x20 for some models) on the way. The index starts the animation
 * (animmodel_start_anim); then the attachment's frame follows the object's animation obj+0x2D0 (frame +8, and +0x3A / +0x3C
 * unless model 0x9E), clamped below the last frame (+0x18 - 1). Returns 1 (and changes nothing) for an animation id
 * some models (0x83, 0x87, 0x89, 0x8E, 0x98) do not know, else 0. Index -1 = keep the current animation.
 */
/* was func_150322B8 */
s32 attachment_cb_sync_animation(u8 *att, u8 *obj) {
    u8 *anim = *(u8 **) (att + 0x48);
    u8 *src = *(u8 **) (obj + 0x2D0);
    s32 idx = -1;
    s32 sync = 1;
    s32 cur;
    s32 kind;
    s32 id;
    f32 last;

    if (anim == NULL) {
        return 0;
    }
    cur = *(u16 *) (anim + 4) & ~0x8000;
    kind = obj[4];
    id = *(u16 *) (obj + 0x84);
    switch (kind) {                                    /* jtbl_80097490 */
        case 0x58:
            if (att[1] == 0x9B) {
                att[2] = 0x12;
            }
            switch (id) {
                case 2:    idx = 1; break;
                case 3:    idx = 0; break;
                case 0x27: idx = 3; break;
                case 0x28: idx = 4; break;
                default:   idx = (att[1] == 0x9B) ? 3 : 0; break;
            }
            break;
        case 0x5B:
            idx = 0;
            break;
        case 0x5A:
        case 0x74:
        case 0x7A:
            *(s16 *) (att + 0x18) = (*(s32 *) (obj + 0x2E8) != 0) ? D_80090684 : D_80090680;
            if (id < 0x2B) {
                idx = sAnim_8009751C[id];
            } else if (id == 0x50) {
                idx = 0x13;
            } else if (id == 0x51) {
                idx = 0x14;
            } else {
                idx = 6;
            }
            break;
        default:
            switch (att[1]) {                          /* jtbl_800975C8 */
                case 0x83:
                    switch (id) {
                        case 0x5E: idx = 0; break;
                        case 0x5F:
                        case 0xFA: idx = 1; break;
                        case 0x60: idx = 2; break;
                        case 0xB3: idx = 3; break;
                        default:   return 1;
                    }
                    break;
                case 0x85:
                    if (id == 0x13E) {
                        idx = 5;
                    } else if (id == 0x13F) {
                        idx = 4;
                    } else if (id == 0x7C) {
                        idx = 2;
                    } else {
                        idx = (*(f32 *) (obj + 0x3C) > 0.0f) ? 1 : 0;
                    }
                    break;
                case 0x87:
                    switch (id) {                      /* jtbl_80097EF0 */
                        case 0x171: case 0x173: idx = 0x01; break;
                        case 0x172: idx = 0x00; break;
                        case 0x174: idx = 0x02; break;
                        case 0x175: case 0x176: case 0x177: case 0x178: case 0x179: return 1;
                        case 0x17A: idx = 0x03; break;
                        default: return 1;
                    }
                    break;
                case 0x88:
                    idx = (id == 0x11) ? 0 : (id == 0x26) ? 1 : 2;
                    break;
                case 0x89:
                    idx = 3;
                    if (obj[5] == 5) {
                        att[2] = 0;
                        break;
                    }
                    switch (id) {
                        case 0x47: idx = 1; att[2] = 9; break;
                        case 0x49: idx = 0; att[2] = 9; break;
                        case 0x81: idx = 2; att[2] = 0x13; break;
                        default:   return 1;
                    }
                    break;
                case 0x8D:
                    idx = (id == 0x323) ? 1 : (id == 0x324) ? 2 : 0;
                    break;
                case 0x8E:
                    switch (id) {
                        case 0xB4: idx = 0; break;
                        case 0xB5: idx = 2; break;
                        case 0xB6: idx = 1; break;
                        case 0xDD:
                        case 0xDE: idx = 3; break;
                        default:   return 1;
                    }
                    break;
                case 0x8F:
                case 0x90:
                    if (id >= 0x104 && id < 0x104 + 0x4E) {
                        idx = sAnim_80097DB8[id - 0x104];
                    } else if (id >= 0x17F && id < 0x17F + 0x1CF) {
                        idx = sAnim_8009767C[id - 0x17F];
                    } else if (id == 0xA8) {
                        idx = 0x5F;
                    } else if (id == 0xAE) {
                        idx = 2;
                    } else if (id == 0xB9) {
                        idx = 1;
                    } else if (id == 0xDA) {
                        idx = 3;
                    } else {
                        idx = 0;
                    }
                    break;
                case 0x91:
                    if (obj[5] == 5) {
                        att[2] = 0;
                        idx = (*(f32 *) (obj + 0x24) == 0.0f) ? 3 : 0;
                    } else {
                        att[2] = 0xE;
                        idx = (id == 0x10) ? 1 : (id == 0x12) ? 2 : 4;
                    }
                    break;
                case 0x98:
                    if (kind == 0x8B) {
                        att[2] = 6;
                        idx = 5;
                        break;
                    }
                    switch (id) {
                        case 0x12C: idx = 0; break;
                        case 0x12D: idx = 3; break;
                        case 0x12E:
                        case 0x358: idx = 2; break;
                        case 0x142: idx = 4; break;
                        case 0x2AA: idx = 6; break;
                        default:    return 1;
                    }
                    break;
                case 0x9A:
                    if (kind == 0x87) {
                        att[2] = 0x12;
                        idx = (id == 1) ? 1 : (id == 5) ? 2 : 0;
                    } else if (kind == 0x99) {
                        att[2] = 0x15;
                        idx = (id >= 0x14 && id < 0x14 + 0x10) ? sAnim_8009763C[id - 0x14] : 0;
                    }
                    break;
                case 0x9B:
                    idx = 0;
                    if (obj[5] == 5) {
                        att[2] = 0;
                    } else if (kind == 0x8B) {
                        att[2] = 6;
                        if (id == 0xC) {
                            idx = 6;
                        } else if (id == 0x13) {
                            idx = 7;
                        }
                    } else {
                        att[2] = 9;
                        if (id == 0x1B7) {
                            idx = 1;
                        } else if (id == 0x1B8) {
                            idx = 2;
                        } else if (id == 0x22E) {
                            idx = 5;
                        }
                    }
                    break;
                case 0x9C:
                    idx = 8;
                    break;
                case 0x9D:
                    idx = 0;
                    if (obj[5] == 5) {
                        att[2] = 0;
                    } else if (kind == 0x8B) {
                        att[2] = 6;
                        if (id == 0x13 || id == 0x20) {
                            idx = 4;
                        } else if (id == 0x22) {
                            idx = 3;
                        }
                    } else {
                        att[2] = 9;
                        if (id == 0x21C) {
                            idx = 1;
                        } else if (id == 0x241) {
                            idx = 2;
                        }
                    }
                    break;
                case 0x9E:
                    att[2] = 9;
                    *(s16 *) (att + 0x1E) = 0x41;
                    *(s16 *) (att + 0x20) = 1;
                    switch (id) {
                        case 0x1D6: idx = 1; break;
                        case 0x1D7: idx = 2; att[2] = 0x13; break;
                        case 0x1D8: idx = 3; break;
                        case 0x257: idx = 4; att[2] = 0x13; break;
                        case 0x275: idx = 5; att[2] = 0x13; break;
                    }
                    sync = 0;
                    if (att[2] == 0x13) {
                        *(s16 *) (att + 0x1E) = 0;
                    }
                    break;
                case 0x9F:
                    idx = 0;
                    if (obj[5] == 5) {
                        att[2] = 0;
                    } else if (kind == 0xB5) {
                        att[2] = 0x12;
                        if (id >= 0x34 && id <= 0x37) {
                            idx = id - 0x33;
                        }
                    } else {
                        att[2] = 9;
                    }
                    break;
            }
            break;
    }

    if (idx != -1) {
        animmodel_start_anim(*(u8 **) (att + 0x48), 0, idx, 0, 0.0f, 1);
    }
    if (src != NULL) {
        anim = *(u8 **) (att + 0x48);
        if (idx == cur && *(s16 *) (src + 0x3C) == 0x3FF) {
            anim_state_snapshot(anim);
            anim = *(u8 **) (att + 0x48);
        }
        *(f32 *) (anim + 8) = *(f32 *) (src + 8);
        anim = *(u8 **) (att + 0x48);
        if (sync && (*(s8 *) (anim + 0x39) != 0 || anim[0x215] == 0)) {
            *(s16 *) (anim + 0x3A) = *(s16 *) (src + 0x3A);
            *(s16 *) (*(u8 **) (att + 0x48) + 0x3C) = *(s16 *) (src + 0x3C);
            anim = *(u8 **) (att + 0x48);
        }
        last = *(f32 *) (anim + 0x18) - 1.0f;
        if (last <= *(f32 *) (anim + 8)) {
            *(f32 *) (anim + 8) = last;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_cb_sync_animation.s")
#endif

/* was func_150334A8 */
s32 attachment_cb_anim_from_owner(u8 *arg0, u8 *arg1) {
    u8 *v;
    u8 *s;
    f32 f;
    s32 t;
    v = *(u8 **)(arg1 + 0x2D0);
    s = *(u8 **)(arg0 + 0x48);
    if (s == NULL) {
        return 0;
    }
    t = *(s32 *)(arg1 + 0x2E4) & 0xFF;
    if (t != 0xFF) {
#ifdef NON_MATCHING
        animmodel_start_anim(s, 0, t, 1.0f, 0.0f, 1); /* P95: float literal (asm passes the bits 0x3F800000) */
#else
        animmodel_start_anim(s, 0, t, 0x3F800000, 0.0f, 1);
#endif
    }
    if (v != NULL) {
        *(f32 *)(*(u8 **)(arg0 + 0x48) + 8) = *(f32 *)(v + 8);
        s = *(u8 **)(arg0 + 0x48);
        f = *(f32 *)(s + 0x18);
        if (f <= *(f32 *)(s + 8)) {
            *(f32 *)(s + 8) = f - 1.0f;
        }
    }
    return 0;
}


/* was func_1503356C */
s32 attachment_cb_play_anim_once(u8 *arg0, s32 arg1) {
    u8 *var_s0;

    var_s0 = *(u8 **)(arg0 + 0x48);
    if (var_s0 == NULL) {
        return 0;
    }
    if ((*(u16 *)(var_s0 + 4) & 0x8000) != 0x8000) {
#ifdef NON_MATCHING
        animmodel_start_anim(var_s0, 0, 0, 1.0f, 0.0f, 1); /* P95: float literal (asm passes the bits 0x3F800000) */
#else
        animmodel_start_anim(var_s0, 0, 0, 0x3F800000, 0.0f, 1);
#endif
        var_s0 = *(u8 **)(arg0 + 0x48);
    }
    if ((*(f32 *)(var_s0 + 0x18) - 1.0f) <= *(f32 *)(var_s0 + 8)) {
        return 1;
    }
    return 0;
}

/* was func_15033618 */
s32 attachment_cb_expire_timer(u8 *arg0, u8 *arg1)
{
  s32 temp_a1;
  if (D_800C35EA == 1)
  {
    return 0;
  }
  if (((*((u8 *) (((u8 *) arg1) + 0xAD))) == 0) && ((*((f32 *) (((u8 *) arg1) + 0x118))) < (*((f32 *) (((u8 *) arg1) + 0x180)))))
  {
    ;
    if (D_800BE9E4 < (*((s32 *) (((u8 *) arg0) + 0x38))))
    {
      *((s32 *) (((u8 *) arg0) + 0x38)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x38))) - D_800BE9E4);
      return 0;
    }
    return 1;
  }
  *((s32 *) (((u8 *) arg0) + 0x38)) = 0x19;
  return 0;
}

/* was func_15033698 */
s32 attachment_cb_expire_on_flag(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    f32 new_var;
    u8 *temp_v0;
    new_var = -10000.0f; // fakematch: constant in a variable swaps the c.eq.s operands
    if (D_800C35EA == 1) {
        return 0;
    }
    if (arg1[0xAD] != 0) {
        temp_v0 = *(u8 **)(arg1 + 0x31C);
        if (temp_v0 != NULL) {
            temp_v0[0x11A] = 0;
        }
        return 1;
    }
    temp_f0 = *(f32 *)(arg1 + 0x118);
    if (temp_f0 != (0, new_var) && *(f32 *)(arg1 + 0x18) < temp_f0 + 300.0f) {
        arg0[3] = 0;
    } else {
        arg0[3] = 0xFF;
    }
    return 0;
}

/* was func_15033730 */
s32 attachment_cb_spin_in_state5(u8 *arg0, u8 *arg1)
{
  switch (arg0[1]) {
  case 0x27:
  case 0x35:
    if (arg1[5] == 5) {
      arg0[2] = 0;
      *(s16 *)(arg0 + 0x22) += D_800BE9E4 * 0xAAA;
    }
    break;
  case 0x29:
    if (arg1[5] == 5) {
      arg0[2] = 0;
    }
    break;
  }
  return 0;
}

#ifdef NON_MATCHING
/* was func_150337A8 */
s32 attachment_tile_scroll_update(u8 *arg0, u8 *arg1) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_t1;
    s32 var_t3;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a2;

    var_v0 = 0;
    var_v1 = 0;
    var_a1 = 0;
    if ((*(u8 *)((u8 *)arg0 + 1)) == 0x37) {
        var_v1 = 4;
        var_a1 = -0x64;
        var_v0 = *(*(s32 **)((u8 *)arg0 + 0x24));
    }
    if (var_v0 != 0) {
        var_a0 = 0;
        if (var_v1 != 0) {
            do {
                var_v1 -= 1;
                if (*(s8 *)((var_a0 * 8) + var_v0) != -0xE /* P117: lb (G_SETTILESIZE opcode 0xF2), was a word */) {
                    do {
                        var_a0 += 1;
                    } while (*(s8 *)((var_a0 * 8) + var_v0) != -0xE);
                }
                if (var_v1 != 0) {
                    var_a0 += 1;
                }
            } while (var_v1 != 0);
        }
        temp_a2 = var_v0 + (var_a0 * 8);
        temp_v1 = (*(s32 *)((u8 *)temp_a2 + 0));
        temp_a3 = (*(s32 *)((u8 *)temp_a2 + 4));
        temp_t2 = ((temp_v1 >> 0xC) & 0xFFF) + var_a1;
        temp_t0 = ((temp_a3 >> 0xC) & 0xFFF) + 2;
        temp_t4 = temp_v1 & 0xFFF;
        var_t1 = temp_t2;
        var_t3 = temp_t4;
        if (temp_t2 >= temp_t0) {
            var_t1 = temp_t2 - temp_t0;
        }
        if (var_t1 < 0) {
            var_t1 += temp_t0;
        }
        temp_v0 = (temp_a3 & 0xFFF) + 2;
        if (temp_t4 >= temp_v0) {
            var_t3 = temp_t4 - temp_v0;
        }
        if (var_t3 < 0) {
            var_t3 += temp_v0;
        }
        (*(s32 *)((u8 *)temp_a2 + 0)) = (s32) (((var_t1 & 0xFFF) << 0xC) | 0xF2000000 | (var_t3 & 0xFFF));
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_tile_scroll_update.s")
#endif
void attachment_set_local_transform(s32, f32, f32, f32, f32, f32, f32);
void mtxf_decompose(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void mtxf_mul(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
/* was func_150335C8 */
s32 attachment_spawn_at_joint(u8 *arg0, struct127 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 ret;
    f32 m1[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    f32 m4[4][4];
    f32 x;
    f32 y;
    f32 z;
    f32 u0;
    f32 u1;
    f32 u2;
    f32 r0;
    f32 r1;
    f32 r2;

    if (arg1->unk1D4 == NULL) {
        return 0;
    }
    ret = obj_setup_run(arg1, arg2, 1.0f, 0);
    if (ret != 0) {
        *(s8 *)(ret + 2) = arg3;
        *(f32 *)(ret + 0x40) = *(f32 *)(arg0 + 0x14C);
        if (arg4 != 0) {
            *(u8 *)(ret + 0x16) &= ~4;
        } else {
            *(u8 *)(ret + 0x16) |= 4;
        }
        guMtxL2F(m1, (Mtx *)((u8 *)arg1->unk1D4 + (arg3 << 6)));
        obj_build_inverse_mtx((s32)m1, (s32)m2);
        mtx_rotate_scale_3x3(m3, *(f32 *)(arg0 + 0xB8), *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0xC4), *(f32 *)(arg0 + 0x14C), *(f32 *)(arg0 + 0x150), *(f32 *)(arg0 + 0x14C));
        m3[3][0] = *(f32 *)(arg0 + 0x14);
        m3[3][1] = *(f32 *)(arg0 + 0x18);
        m3[3][2] = *(f32 *)(arg0 + 0x1C);
        m3[0][3] = 0.0f;
        m3[1][3] = 0.0f;
        m3[2][3] = 0.0f;
        m3[3][3] = 1.0f;
        mtxf_mul(m3, m2, m4);
        mtxf_decompose((f32 *)m4, &x, &y, &z, &r0, &r1, &r2, &u0, &u1, &u2);
        if (arg5 != 0) {
            z = 0.0f;
            y = 0.0f;
            x = 0.0f;
        }
        attachment_set_local_transform(ret, x, y, z, r0, r1, r2);
        return ret;
    }
    return 0;
}

/* was func_15033A7C */
s32 attachment_cb_keep_during_anims(u8 *arg0, u8 *arg1) {
    u16 temp_v0;

    temp_v0 = (*(u16 *)((u8 *)arg1 + 0x84));
    if (((*(u8 *)((u8 *)arg0 + 1)) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}

/* was func_15033AD4 */
s32 attachment_cb_blink_texture(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x38) += D_800BE9E4;
    if (*(s32 *)(arg0 + 0x38) >= 16) {
        *(s32 *)(arg0 + 0x38) = 0;
        *(s32 *)(arg0 + 0x3C) ^= 1;
    }
    *(s16 *)(arg0 + 0x18) = D_800906AC[*(s32 *)(arg0 + 0x3C)];
    return 0;
}

#ifdef NON_MATCHING
void obj_glow_post_remove_event(u8 *);
s32 object_effect_start(u8 *, s32, s32, s32, s32, s32);

/* was func_15033B28 */
s32 attachment_cb_slot_anim_check(u8 *arg0, u8 *arg1) {
    s32 var_a2;
    s32 var_v1;
    u16 temp_v0_2;
    u8 temp_v0;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    var_v1 = 0;
    temp_v0 = (*(u8 *)((u8 *)arg0 + 6));
    if (temp_v0 == 0x16) {
        var_a2 = 4;
        if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0x165) {
            goto block_10;
        }
    } else if (temp_v0 == 0x89) {
        var_a2 = 6;
        temp_v0_2 = (*(u16 *)((u8 *)arg1 + 0x84));
        if (((temp_v0_2 == 0x221) || (temp_v0_2 == 0x223) || (temp_v0_2 == 0x31B)) && ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x31C))) + 0x198)) == 2)) {
            goto block_10;
        }
    } else {
        var_a2 = 5;
        if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0x157) {
block_10:
            var_v1 = 1;
        }
    }
    if ((*(s32 *)((u8 *)arg0 + 0x38)) == 0) {
        if ((var_v1 != 0) && ((temp_v0_3 = (*(u8 **)((u8 *)arg1 + 0x31C)), ((*(u8 *)((u8 *)temp_v0_3 + 0x197)) != 0)) || (var_a2 == 6)) && (((*(u16 *)((u8 *)temp_v0_3 + 0x8A)) & 0x2000) == 0x2000) && ((*(u16 *)((u8 *)temp_v0_3 + 0x19E)) == 0)) {
            (*(s32 *)((u8 *)arg0 + 0x38)) = 1;
            object_effect_start(arg1, -1, var_a2, 1, 0xFF, 1);
        }
    } else if ((var_v1 == 0) || (temp_v0_4 = (*(u8 **)((u8 *)arg1 + 0x31C)), (((*(u16 *)((u8 *)temp_v0_4 + 0x8A)) & 0x2000) == 0)) || (((*(u8 *)((u8 *)temp_v0_4 + 0x197)) == 0) && (var_a2 != 6))) {
        (*(s32 *)((u8 *)arg0 + 0x38)) = 0;
        obj_glow_post_remove_event(arg1);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_cb_slot_anim_check.s")
#endif
#ifndef NON_MATCHING
extern s32 attachment_sound_cb;
#endif
s32 sfx_emitter_stop_by_callback(s32 *, u8 *, u8 *);
s32 attachment_tile_scroll_update(u8 *, u8 *);
extern u8 D_800BEE2C;
/* was func_15033CB8 */
s32 attachment_cb_loop_sound(u8 *arg0, u8 *arg1) {
    attachment_tile_scroll_update(arg0, arg1);
    if (D_800C35EA != 1) {
        if (D_800BEE2C != 0) {
            if (*(s32 *)(arg0 + 0x3C) != 0) {
                sfx_emitter_stop_by_callback(&attachment_sound_cb, arg0, arg1);
            }
            *(s32 *)(arg0 + 0x3C) = 0;
        } else if (*(s32 *)(arg0 + 0x3C) == 0) {
            *(s32 *)(arg0 + 0x3C) = sfx_emitter_start(0x448U, (s16) (s32) (*(f32 *)(arg1 + 0x14)), (s16) (s32) (*(f32 *)(arg1 + 0x18)), (s16) (s32) (*(f32 *)(arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &attachment_sound_cb, arg0, (s32) arg1, 0, 0) | 0x80000000;
        }
    }
    return 0;
}

#ifndef NON_MATCHING
extern s32 attachment_sound_cb;
#endif

/* was func_15033DC8 */
s32 attachment_cb_delayed_sound(u8 *arg0, u8 *arg1) {
    s32 temp_v0;

    if (D_800BE616 != 0) {
        rail_event_add((*(f32 *)((u8 *)arg1 + 0x14)), (*(f32 *)((u8 *)arg1 + 0x18)), (*(f32 *)((u8 *)arg1 + 0x1C)), 900.0f);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x38)) == 0) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if (temp_v0 < 0x19) {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) (temp_v0 + D_800BE9E4);
        } else {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = sfx_emitter_start(0x513U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &attachment_sound_cb, arg0, (s32) arg1, 0, 0);
            (*(s32 *)((u8 *)arg0 + 0x38)) = 0x513;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
s32 random_int(void);
void sound_play_for_actor(s32, s32, s32, s32, s32, u8 *);

/*
 * P71: sound callback of the attachment sounds (sfx_emitter_start / sfx_emitter_stop_by_callback with rec, owner; voice +0x18 / +0x1C).
 * Missing record / owner (or owner state 0): 1. Keeps the voice at the owner's position (+2 / +4 / +6). Playing
 * (*playing): model 0x37 follows the owner's animation +0x84 (on a change to 0x15F one of sounds 0x444..0x447
 * starts, sound_play_for_actor) and returns 0; others: when the owner's +0x31C->+0x19C < 100 the looping 0x513 sound
 * becomes a new 0x3A1 voice (rec +0x38 / +0x3C, returns 1), else 0. Stopped: model 0x37 stops its +0x24 voice and
 * clears *out (0), others return 1.
 */
/* was func_15033ECC */
s32 attachment_sound_cb(u8 *voice, s32 arg1, s32 *playing, s32 arg3, s32 arg4, s32 arg5, u16 *out) {
    u8 *rec = *(u8 **) (voice + 0x18);
    u8 *obj = *(u8 **) (voice + 0x1C);
    u8 *p;
    s32 snd;

    if (rec == NULL || obj == NULL || *(s32 *) obj == 0) {
        return 1;
    }
    *(s16 *) (voice + 2) = *(f32 *) (obj + 0x14);
    *(s16 *) (voice + 4) = *(f32 *) (obj + 0x18);
    *(s16 *) (voice + 6) = *(f32 *) (obj + 0x1C);
    if (*playing == 0) {
        if (rec[1] != 0x37) {
            return 1;
        }
        if (*(u16 *) (voice + 0x24) != 0) {
            sound_voice_stop(*(u16 *) (voice + 0x24));
            *(u16 *) (voice + 0x24) = 0;
        }
        *out = 0;
        return 0;
    }
    if (rec[1] == 0x37) {
        snd = -1;
        if ((*(s32 *) (rec + 0x38) & 0xFFFF) != *(u16 *) (obj + 0x84) && *(u16 *) (obj + 0x84) == 0x15F) {
            snd = (random_int() & 3) + 0x444;
        }
        if (snd != -1) {
            sound_play_for_actor(0, snd, 0x5DC0, 0, 0, obj);
        }
        *(s32 *) (rec + 0x38) = *(u16 *) (obj + 0x84);
        return 0;
    }
    p = *(u8 **) (obj + 0x31C);
    if (p != NULL && *(u16 *) (p + 0x19C) < 100 && *(s32 *) (rec + 0x38) == 0x513) {
        *(s32 *) (rec + 0x38) = 0x3A1;
        *(s32 *) (rec + 0x3C) = sfx_emitter_start(0x3A1, (s32) *(f32 *) (obj + 0x14), (s32) *(f32 *) (obj + 0x18),
                                              (s32) *(f32 *) (obj + 0x1C), 0x7D00, 0x3E8, 0x1F4,
                                              (s32) attachment_sound_cb, rec, (s32) obj, 0, 0);
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/attachment_sound_cb.s")
#endif

/* was func_150340F0 */
s32 attachment_cb_free_in_state3(s32 arg0, u8 *arg1) {
    if (arg1[5] == 3) {
        return 1;
    }
    return 0;
}

/* was func_15034118 */
s32 attachment_list_for_owner(u8 *arg0, s32 *arg1) {
    s32 n;
    u8 *p;
    u8 *next;
    n = 0;
    if (D_800C3EE0 == 0) {
        return 0;
    }
    p = (u8 *)D_800C3EE0;
    if (p != NULL) {
        do {
            next = *(u8 **)(p + 0x54);
            if (arg0[0x3B] == p[0]) {
                arg1[n] = (s32)p;
                n += 1;
            }
            p = next;
        } while (next != NULL);
    }
    return n;
}

/* was func_15034174 */
u8 *attachment_find_first_of_owner(u8 *arg0) {
    u8 *var_v1;
    u8 *next;
    for (var_v1 = (u8 *)D_800C3EE0; var_v1 != NULL; var_v1 = next) {
        next = *(u8 **)(var_v1 + 0x54);
        if (arg0[0x3B] == var_v1[0]) {
            return var_v1;
        }
    }
    return NULL;
}

/* was func_150341B4 */
void attachment_swap_owner_ids(s32 arg0, s32 arg1) {
    u8 *var_v0;
    u8 *next;
    for (var_v0 = (u8 *)D_800C3EE0; var_v0 != NULL; var_v0 = next) {
        next = *(u8 **)(var_v0 + 0x54);
        if (arg0 == var_v0[0]) {
            var_v0[0] = arg1;
        } else if (arg1 == var_v0[0]) {
            var_v0[0] = arg0;
        }
    }
}

/* was func_150341FC */
s32 attachment_cb_release_link(s32 arg0, u8 *arg1) {
    u8 *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x31C));
    if ((temp_v1 != NULL) && ((*(u8 *)((u8 *)temp_v1 + 0x78)) != 9) && ((*(u8 *)((u8 *)temp_v1 + 0x11A)) != 3)) {
        (*(u8 *)((u8 *)temp_v1 + 0x11A)) = 0U;
        return 1;
    }
    return 0;
}

/* was func_15034260 */
s32 attachment_cb_release_link2(s32 arg0, u8 *arg1) {
    u8 temp_v0;
    u8 *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x31C));
    if (temp_v1 != NULL) {
        temp_v0 = (*(u8 *)((u8 *)temp_v1 + 0x78));
        if ((temp_v0 != 0xC) && (temp_v0 != 0x16) && ((*(u8 *)((u8 *)temp_v1 + 0x11A)) != 3)) {
            (*(u8 *)((u8 *)temp_v1 + 0x11A)) = 0U;
            return 1;
        }
    }
    return 0;
}
