#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15031D40(u8 *arg0, u8 *arg1);
f32 *allocate_memory(s32, s32, s32, s32);
s32 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
s32 func_1510D3E0(s32, s32, s32, s32, s32 *);
void func_15168E54(s32, s32 *);
void func_100043B4(s32 *arg0, u32 arg1);
void func_10004074(s32);
void func_15031F04(u8 *);
void func_1503FAA8(s32);
void func_1518CF74(s32);
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
/* P71: a word of an attachment record (the list D_800C3EE0, see func_15030758) */
#define ATT_W(rec, off) (*(s32 *) ((rec) + (off)))
s32 func_15033ECC();   /* P71: C under NON_MATCHING (else an extern s32 below, as the matching code uses it) */
s32 func_1000FD38(s32 *, u8 *, u8 *);
#endif

s32 func_1503F8A8(u8 *, s32, s32, s32, f32, s32);

void func_15030448(struct127 *, s32);

s32 func_15030600(u8 *, s32, s32);


#ifdef NON_MATCHING
/*
 * P71: reference-counted load of asset (9, idx) with several display lists (the one-list variant is
 * func_1518C900; func_1518CF74 releases both). Header words: +0 the display-list offset table (+4 >> 2 entries),
 * +8, +0xC (>> 4), +0x10, the data from +0x18. First use: func_1502B6BC(0, 0, 0, 2, 9, idx) (none: return 1),
 * each table entry is relocated by the header address, func_1510D3E0 resolves its segments
 * (&D_800DFDE8[idx] keeps the list), func_15168E54 patches its addresses; the header is kept in D_800E0578[idx].
 * The count D_800DFC00[idx] is not saturated here. Returns 0 once loaded.
 */
s32 func_15030100(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC) {
    u8 *refs = &D_800DFC00[idx];
    s32 *hdr;
    s32 i;

    if (*refs == 0) {
        hdr = func_1502B6BC(0, 0, 0, 2, 9, idx);
        if (hdr == NULL) {
            return 1;
        }
        *dls = (s32 *) hdr[0];
        *count = (u32) hdr[1] >> 2;
        for (i = 0; i < *count; i++) {
            (*dls)[i] += (s32) hdr;
            func_1510D3E0((*dls)[i], 0, 1, 0x3E, &D_800DFDE8[idx]);
            func_15168E54((*dls)[i], hdr);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030100.s")
#endif

#ifdef NON_MATCHING
s32 func_15030100(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC);
s32 func_1503F91C(s32, s32, u8 *, u8 *, s32 *, u8 *, u8 *);

/*
 * P71: loads the model of attachment record rec (once: +0x24 set means loaded). +0x17 == -1: asset 9 entry +1
 * (func_15030100, display lists to +0x24 / count +0x14 / +0x30), else entry (+1, +0x17) of func_1503F91C (also
 * +0x48). Failure returns 1. The vertex data runs from the returned data pointer up to the list table (+0x24).
 * Records without bit 0x10 of +4 whose owner has (obj[0x66] & 0xC) == 8 and a +0x30 get two private copies of it
 * (+0x28 / +0x2C, +8 = 1 so func_15030448 frees them), the others share it. Marks the record loaded (+9).
 */
s32 func_150302C8(struct127 *arg0, u8 *obj) {
    u8 *rec = (u8 *) arg0;
    s32 data;
    s32 size;

    if (ATT_W(rec, 0x24) != 0) {
        return 0;
    }
    if ((s8) rec[0x17] == -1) {
        if (func_15030100(rec[1], (s32 **) (rec + 0x24), rec + 0x14, &data, (s32 *) (rec + 0x30), NULL, NULL)) {
            return 1;
        }
    } else if (func_1503F91C(rec[1], (s8) rec[0x17], rec + 0x24, rec + 0x14, &data, rec + 0x30, rec + 0x48)) {
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
            func_10004074(ATT_W(rec, 0x28));
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150302C8.s")
#endif

#ifdef NON_MATCHING
/*
 * P70: frees an attachment record of the list D_800C3EE0 (see func_15030758). now != 0 frees its buffers at
 * once (func_10004074), else they are released deferred (func_100043B4(buf, 4)) after func_15031F04.
 * Loaded records (+9) drop the two vertex copies +0x28 / +0x2C when they were made (+8), the +0x48 handle
 * (func_1503FAA8) and their asset (func_1518CF74(+1)). Then +0x34, +0x44 (always at once), +0x4C, +0x50, the
 * unlink from the doubly linked list (+0x54 next, +0x58 prev; the head D_800C3EE0) and the record itself.
 */
void func_15030448(struct127 *arg0, s32 now) {
    u8 *rec = (u8 *) arg0;
    u8 *next;
    u8 *prev;

    if (!now) {
        func_15031F04(rec);
    }
    if (rec[9] != 0) {
        if (rec[8] != 0) {
            if (now) {
                func_10004074(ATT_W(rec, 0x28));
                func_10004074(ATT_W(rec, 0x2C));
            } else {
                func_100043B4((s32 *) ATT_W(rec, 0x28), 4);
                func_100043B4((s32 *) ATT_W(rec, 0x2C), 4);
            }
        }
        if (ATT_W(rec, 0x48) != 0) {
            func_1503FAA8(ATT_W(rec, 0x48));
        }
        func_1518CF74(rec[1]);
    }
    if (ATT_W(rec, 0x34) != 0) {
        if (now) {
            func_10004074(ATT_W(rec, 0x34));
        } else {
            func_100043B4((s32 *) ATT_W(rec, 0x34), 4);
        }
    }
    if (ATT_W(rec, 0x44) != 0) {
        func_10004074(ATT_W(rec, 0x44));
    }
    if (ATT_W(rec, 0x4C) != 0) {
        if (now) {
            func_10004074(ATT_W(rec, 0x4C));
        } else {
            func_100043B4((s32 *) ATT_W(rec, 0x4C), 4);
        }
    }
    if (ATT_W(rec, 0x50) != 0) {
        if (now) {
            func_10004074(ATT_W(rec, 0x50));
        } else {
            func_100043B4((s32 *) ATT_W(rec, 0x50), 4);
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
    func_10004074((s32) rec);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030448.s")
#endif

void func_150305E0(s32 arg0, s32 arg1) {
    func_15030600(arg0, arg1, 0xFF);
}

#ifdef NON_MATCHING
s32 func_15030600(u8 *arg0, s32 arg1, s32 arg2) {
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
            func_15030448((struct127 *) var_a0, 0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030600.s")
#endif
s32 func_150306D4(u8 *arg0) {
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
                func_15030448((u8 *) var_a0, 0);
            }
            var_a0 = temp_s0;
        } while (temp_s0 != 0);
    }
    return var_s1;
}

#ifdef NON_MATCHING
/* P65: the attachment records of the D_800C3EE0 list (offsets read from func_15030758's asm). */
typedef struct Attach {
    /* 0x00 */ u8 model;            /* model id for func_15083E90 */
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
    /* 0x1E */ u16 subModel;        /* != 0: attached through func_15031C4C / func_15031360 (second pass) */
    /* 0x20 */ u16 subMtx;
    /* 0x22 */ s16 spin;            /* extra rotation (65536 = 360 degrees) */
    /* 0x24 */ u8 pad24[0x10];
    /* 0x34 */ Mtx *mtx;            /* two Mtx, one per DL buffer D_800BE9C0 */
    /* 0x38 */ u8 pad38[8];
    /* 0x40 */ f32 scale;
    /* 0x44 */ f32 *transform;      /* x, y, z, then rotation angles at +0xC / +0x10 / +0x14 */
    /* 0x48 */ u8 *target;          /* gets the matrix pointer at +0x3E0[D_800BE9C0], then func_1503F7A0 */
    /* 0x4C */ u8 pad4C[8];
    /* 0x54 */ struct Attach *next;
} Attach;

extern s32 (*D_80084550[])(Attach *, u8 *);
s32 func_15031360(u8 *, u8 *, s32 *, s32 *);
u8 *func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
void func_1503F7A0(u8 *);
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/*
 * P65: per-frame update of the attachments (D_800C3EE0 list). Pass 0 handles the records without +0x1E (and notes
 * whether any has one), pass 1, only when needed, those attached to a sub-model. For each: its model (func_15083E90)
 * must exist and the optional callback D_80084550[+7] must return 0, else the record is freed (func_15030448).
 * With a matrix buffer (+0x34) or a target (+0x48), the joint matrix (the model's joint +2, or the sub-model matrix
 * from func_15031360 as f32) gives the record's matrix for this DL buffer: transformed by +0x44 (rotation, scale +0x40,
 * translation) / scaled to +0x40 (mode 4) / as is, then rotated by +0x22. The target gets the pointer. Records whose
 * owner ids no longer match the model's +0x84, or whose timer runs out, are freed.
 */
void func_15030758(void) {
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

            model = (u8 *) func_15083E90(rec->model);
            rec->seen = 1;
            if (model == NULL) {
                func_15030448((struct127 *) rec, 0);
                continue;
            }
            if (rec->callback != 0 && D_80084550[rec->callback](rec, model) != 0) {
                func_15030448((struct127 *) rec, 0);
                continue;
            }

            src = NULL;
            out = NULL;
            if (rec->mtx != NULL || rec->target != NULL) {
                joints = *(u8 **) (model + 0x1D4);
                if (joints != NULL) {
                    if (rec->subModel != 0) {
                        sub = func_15031C4C(model, rec->subModel, 0);
                        if (sub == NULL) {
                            func_15030448((struct127 *) rec, 0);
                            continue;
                        }
                        if (func_15031360(sub, model, &subMtx, &unused) == 0) {
                            func_15030448((struct127 *) rec, 0);
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
                            func_150A9B0C(xform, rec->transform[3], rec->transform[4], rec->transform[5],
                                          rec->scale, rec->scale, rec->scale);
                            xform[0][3] = 0.0f;
                            xform[1][3] = 0.0f;
                            xform[2][3] = 0.0f;
                            xform[3][0] = rec->transform[0];
                            xform[3][1] = rec->transform[1];
                            xform[3][2] = rec->transform[2];
                            xform[3][3] = 1.0f;
                            func_150A7A48(xform, norm, res);
                            guMtxF2L(res, out);
                        } else if (rec->spin != 0) {
                            /* extra rotation by spin (65536 = 360 degrees) */
                            func_150A8050(rot, 0.0f, 0.0f, rec->spin * (360.0f / 65536.0f));
                            func_150A7A48(rot, m, res);
                            guMtxF2L(res, out);
                        } else {
                            guMtxF2L(m, out);
                        }
                    }
                }
            }

            if (rec->target != NULL) {
                ((void **) (rec->target + 0x3E0))[D_800BE9C0] = (rec->mtx != NULL) ? (void *) out : (void *) src;
                func_1503F7A0(rec->target);
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
                    func_15030448((struct127 *) rec, 0);
                    continue;
                }
            }

            t = rec->timer;
            if (t != 0xFFFF) {
                if (t == 0) {
                    func_15030448((struct127 *) rec, 0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030758.s")
#endif

#ifdef NON_MATCHING
s32 func_150302C8(struct127 *, u8 *);

struct127 *func_15030DE4(u8 *arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9, s32 argA, s32 argB, s32 argC) {
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
        var_t1 |= func_150302C8(temp_v0, arg0);
    }
    if (var_t1 != 0) {
        func_15030448(temp_v0, 1);
        return NULL;
    }
    func_15031D40(temp_v0, arg0);
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15030DE4.s")
#endif
#ifdef NON_MATCHING
f32 *allocate_memory(s32, s32, s32, s32);

void func_15031044(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031044.s")
#endif
#ifdef NON_MATCHING
s32 func_150314B4(s32, u8 *, struct127 *, s32, s32);

s32 func_150310F8(s32 arg0, s32 arg1, s32 arg2) {
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
                temp_v0 = func_15083E90((*(u8 *)((u8 *)var_s0 + 0)));
                if ((temp_v0 == NULL) || (temp_v0->unk1D4 == NULL) || (temp_v1 = 1 << arg1, (temp_v1 == (temp_v0->unk74 & temp_v1)))) {

                } else if (arg2 == 2) {
                    if (temp_v0->unk5 != 7) {

                    } else {
                        goto block_19;
                    }
                } else {
                    temp_v0_2 = func_1506196C(temp_v0, arg1);
                    if (arg2 == 1) {
                        if (!((*(u8 *)((u8 *)var_s0 + 4)) & 2) && (temp_v0_2 == 0xFF) && (temp_v0->unk5 != 1)) {

                        } else {
                            goto block_19;
                        }
                    } else if (((*(u8 *)((u8 *)var_s0 + 4)) & 2) || (temp_v0_2 < 0xFF) || (temp_v0->unk5 == 1)) {

                    } else {
block_19:
                        var_s6 = func_150314B4(var_s6, (u8 *) var_s0, temp_v0, arg1, 0);
                    }
                }
            }
            var_s0 = temp_s2;
        } while (var_s0 != 0);
    }
    return var_s6;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150310F8.s")
#endif
#ifdef NON_MATCHING
#ifndef NON_MATCHING
s32 func_150314B4(s32, u8 *, u8 *, s32, s32);
#endif

s32 func_15031284(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
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
                    var_s3 = func_150314B4(var_s3, (u8 *) var_s0, arg1, arg2, arg3);
                }
                var_s0 = temp_s1;
            } while (var_s0 != 0);
        }
    }
    return var_s3;
}
#else
#ifdef NON_MATCHING
s32 func_15031284(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
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
                    var_s3 = func_150314B4(var_s3, (u8 *) var_s0, arg1, arg2, arg3);
                }
                var_s0 = temp_s1;
            } while (var_s0 != 0);
        }
    }
    return var_s3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031284.s")
#endif
#endif
#ifdef NON_MATCHING
u8 * func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);

s32 func_15031360(u8 *arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
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
        temp_v0_4 = func_15031C4C(arg1, temp_v0_3, 0);
        if (temp_v0_4 == NULL) {
            return 0;
        }
        if (func_15031360(temp_v0_4, arg1, arg2, arg3) == 0) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031360.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150314B4.s")

void func_15031C1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0 = func_15031C4C(arg0, arg1, arg3);
    if (temp_v0 != NULL) {
        temp_v0[3] = arg2;
    }
}

#ifdef NON_MATCHING
u8 * func_15031C4C(u8 *arg0, s32 arg1, s32 arg2) {
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
            var_a2 -= 1;
            if (var_a2 != 0) {
                goto block_8;
            }
            return (u8 *) var_v1;
        }
block_8:
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031C4C.s")
#endif
u8 *func_15031CBC(s32 arg0, u8 *arg1) {
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
s32 func_150D3870(u8 *, s32, s32);
void func_150D5950(u8 *, u8, s32);
void func_15100734(u8 *);
s32 func_15163BE8(u8 *, s32, s32);
s32 func_151BDDD8(u8 *, s32, s32);
void func_151D7A60(u8 *, u8, s8, u8, s32);
extern s32 D_800905D8;
extern s32 D_800905DC;

void func_15031D40(u8 *arg0, u8 *arg1) {
    u8 temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 1));
    switch ((s32) temp_v0) {                        /* switch 2; irregular */
    default:                                        /* switch 2 */
        if ((u32) (temp_v0 - 0x82) < 0xFU) {
            switch (temp_v0) {                      /* switch 1 */
            case 0x37:                              /* switch 2 */
            case 0x91:                              /* switch 1 */
                func_15100734(arg1);
                return;
            case 0x5A:                              /* switch 2 */
            case 0xB4:                              /* switch 1 */
                temp_v0_2 = (*(u8 **)((u8 *)arg1 + 0x31C));
                if (temp_v0_2 != NULL) {
                    (*(u16 *)((u8 *)temp_v0_2 + 0x1A6)) = (u16) ((*(u16 *)((u8 *)temp_v0_2 + 0x1A6)) + 0xAA);
                    return;
                }
                break;
            case 0x90:                              /* switch 1 */
                (*(s32 *)((u8 *)arg1 + 0x9C)) = (s32) ((*(s32 *)((u8 *)arg1 + 0x9C)) | 0x70);
                return;
            case 0x8F:                              /* switch 1 */
                (*(s32 *)((u8 *)arg1 + 0x9C)) = (s32) ((*(s32 *)((u8 *)arg1 + 0x9C)) | 0xE00);
                return;
            case 0x49:                              /* switch 2 */
            case 0xA3:                              /* switch 1 */
                func_15163BE8(arg1, 0xFF, 1);
                return;
            case 0x5D:                              /* switch 2 */
            case 0xB7:                              /* switch 1 */
                func_150D3870(arg1, 0xFF, 1);
                func_150D5950(arg1, 0xFF, 1);
                return;
            case 0x3D:                              /* switch 2 */
            case 0x97:                              /* switch 1 */
                func_151BDDD8(arg1, 0xFF, 1);
                return;
            case 0x5E:                              /* switch 2 */
            case 0x85:                              /* switch 1 */
            case 0xB8:                              /* switch 1 */
                (*(s32 *)((u8 *)arg1 + 0x9C)) = (s32) ((*(s32 *)((u8 *)arg1 + 0x9C)) | 0x6000);
                return;
            case 0x8D:                              /* switch 1 */
                if (func_150859AC(0, 6) < 0x64) {
                    (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) D_800905D8;
                    return;
                }
                (*(s16 *)((u8 *)arg0 + 0x18)) = (s16) D_800905DC;
                return;
            case 0x82:                              /* switch 1 */
                func_151D7A60(arg1, 6, -1, 0xFF, 1);
                break;
            }
        } else {
            return;
        }
        break;
    case 0x1D:                                      /* switch 2 */
        func_151D7A60(arg1, 0, 2, 0xFF, 1);
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031D40.s")
#endif
#ifdef NON_MATCHING
struct127 *func_15083E90(u8);
void func_15100700(u8 *);
void func_151616D0(u8, u8, s32);
void func_151482D4(s32, u8);
void func_151494E0(s32, u8);
void func_151BDDA4(u8 *);
void func_151D4668(u8 *);
void func_151D7A2C(u8 *);
void func_151027E8(u8 *);

/*
 * P71: undoes what attachment record rec (model id +1) did to its owner object (func_15083E90(+0), none: nothing):
 * flag bits of +0x9C are cleared per model (0x90: 0x70, 0x8F: 0xE00, 0x85 / 0x5E: 0x6000), models 0x37 / 0x4B / 0x4C
 * queue func_15033ECC (func_1000FD38; 0x37 also func_15100700), 0x49 / 0x5D send messages with the owner and its
 * +0x3B, 0x5A lowers +0x31C->+0x1A6 by 0xAA; others call per-model handlers. Records of kind +6 = 0x16 / 0x63 /
 * 0x89 also call func_151027E8 and func_151D4668.
 */
void func_15031F04(u8 *rec) {
    struct {
        u8 *obj;
        u8 id;
    } msg;
    u8 *obj;
    u8 *p;

    obj = (u8 *) func_15083E90(rec[0]);
    if (obj == NULL) {
        return;
    }
    switch (rec[1]) {
        case 0x82:
        case 0x1D:
            func_151D7A2C(obj);
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
            func_151D4668(obj);
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
            func_1000FD38((s32 *) func_15033ECC, rec, obj);
            if (rec[1] == 0x37) {
                func_15100700(obj);
            }
            break;
        case 0x49:
            msg.obj = obj;
            msg.id = obj[0x3B];
            func_151616D0(0x10, 0x29, (s32) &msg);
            break;
        case 0x5D:
            msg.obj = obj;
            msg.id = obj[0x3B];
            func_151482D4((s32) &msg, 0x2E);
            func_151494E0((s32) &msg, 0x2F);
            break;
        case 0x3D:
            func_151BDDA4(obj);
            break;
    }
    if (rec[6] == 0x16 || rec[6] == 0x63 || rec[6] == 0x89) {
        func_151027E8(obj);
        func_151D4668(obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15031F04.s")
#endif

s32 func_1503211C(u8 *arg0, s32 arg1) {
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
s32 func_1503216C(u8 *arg0, struct127 *obj) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_1503216C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150322B8.s")

s32 func_150334A8(u8 *arg0, u8 *arg1) {
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
        func_1503F8A8(s, 0, t, 0x3F800000, 0.0f, 1);
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


s32 func_1503356C(u8 *arg0, s32 arg1) {
    u8 *var_s0;

    var_s0 = *(u8 **)(arg0 + 0x48);
    if (var_s0 == NULL) {
        return 0;
    }
    if ((*(u16 *)(var_s0 + 4) & 0x8000) != 0x8000) {
        func_1503F8A8(var_s0, 0, 0, 0x3F800000, 0.0f, 1);
        var_s0 = *(u8 **)(arg0 + 0x48);
    }
    if ((*(f32 *)(var_s0 + 0x18) - 1.0f) <= *(f32 *)(var_s0 + 8)) {
        return 1;
    }
    return 0;
}

s32 func_15033618(u8 *arg0, u8 *arg1)
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

s32 func_15033698(u8 *arg0, u8 *arg1) {
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

s32 func_15033730(u8 *arg0, u8 *arg1)
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
s32 func_150337A8(u8 *arg0, u8 *arg1) {
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
                if (*(s32 *)((var_a0 * 8) + var_v0) != -0xE) {
                    do {
                        var_a0 += 1;
                    } while (*(s32 *)((var_a0 * 8) + var_v0) != -0xE);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_150337A8.s")
#endif
void func_15031044(s32, f32, f32, f32, f32, f32, f32);
void func_1503E5F8(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
s32 func_150335C8(u8 *arg0, struct127 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
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
    ret = func_15083568(arg1, arg2, 1.0f, 0);
    if (ret != 0) {
        *(s8 *)(ret + 2) = arg3;
        *(f32 *)(ret + 0x40) = *(f32 *)(arg0 + 0x14C);
        if (arg4 != 0) {
            *(u8 *)(ret + 0x16) &= ~4;
        } else {
            *(u8 *)(ret + 0x16) |= 4;
        }
        guMtxL2F(m1, (Mtx *)((u8 *)arg1->unk1D4 + (arg3 << 6)));
        func_15048B10((s32)m1, (s32)m2);
        func_150A9B0C(m3, *(f32 *)(arg0 + 0xB8), *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0xC4), *(f32 *)(arg0 + 0x14C), *(f32 *)(arg0 + 0x150), *(f32 *)(arg0 + 0x14C));
        m3[3][0] = *(f32 *)(arg0 + 0x14);
        m3[3][1] = *(f32 *)(arg0 + 0x18);
        m3[3][2] = *(f32 *)(arg0 + 0x1C);
        m3[0][3] = 0.0f;
        m3[1][3] = 0.0f;
        m3[2][3] = 0.0f;
        m3[3][3] = 1.0f;
        func_150A7A48(m3, m2, m4);
        func_1503E5F8((f32 *)m4, &x, &y, &z, &r0, &r1, &r2, &u0, &u1, &u2);
        if (arg5 != 0) {
            z = 0.0f;
            y = 0.0f;
            x = 0.0f;
        }
        func_15031044(ret, x, y, z, r0, r1, r2);
        return ret;
    }
    return 0;
}

s32 func_15033A7C(u8 *arg0, u8 *arg1) {
    u16 temp_v0;

    temp_v0 = (*(u16 *)((u8 *)arg1 + 0x84));
    if (((*(u8 *)((u8 *)arg0 + 1)) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}

s32 func_15033AD4(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x38) += D_800BE9E4;
    if (*(s32 *)(arg0 + 0x38) >= 16) {
        *(s32 *)(arg0 + 0x38) = 0;
        *(s32 *)(arg0 + 0x3C) ^= 1;
    }
    *(s16 *)(arg0 + 0x18) = D_800906AC[*(s32 *)(arg0 + 0x3C)];
    return 0;
}

#ifdef NON_MATCHING
void func_151027E8(u8 *);
s32 func_15102C3C(u8 *, s32, s32, s32, s32, s32);

s32 func_15033B28(u8 *arg0, u8 *arg1) {
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
            func_15102C3C(arg1, -1, var_a2, 1, 0xFF, 1);
        }
    } else if ((var_v1 == 0) || (temp_v0_4 = (*(u8 **)((u8 *)arg1 + 0x31C)), (((*(u16 *)((u8 *)temp_v0_4 + 0x8A)) & 0x2000) == 0)) || (((*(u8 *)((u8 *)temp_v0_4 + 0x197)) == 0) && (var_a2 != 6))) {
        (*(s32 *)((u8 *)arg0 + 0x38)) = 0;
        func_151027E8(arg1);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033B28.s")
#endif
#ifndef NON_MATCHING
extern s32 func_15033ECC;
#endif
s32 func_1000FD38(s32 *, u8 *, u8 *);
s32 func_150337A8(u8 *, u8 *);
extern u8 D_800BEE2C;
s32 func_15033CB8(u8 *arg0, u8 *arg1) {
    func_150337A8(arg0, arg1);
    if (D_800C35EA != 1) {
        if (D_800BEE2C != 0) {
            if (*(s32 *)(arg0 + 0x3C) != 0) {
                func_1000FD38(&func_15033ECC, arg0, arg1);
            }
            *(s32 *)(arg0 + 0x3C) = 0;
        } else if (*(s32 *)(arg0 + 0x3C) == 0) {
            *(s32 *)(arg0 + 0x3C) = func_1000FA64(0x448U, (s16) (s32) (*(f32 *)(arg1 + 0x14)), (s16) (s32) (*(f32 *)(arg1 + 0x18)), (s16) (s32) (*(f32 *)(arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &func_15033ECC, arg0, (s32) arg1, 0, 0) | 0x80000000;
        }
    }
    return 0;
}

#ifndef NON_MATCHING
extern s32 func_15033ECC;
#endif

s32 func_15033DC8(u8 *arg0, u8 *arg1) {
    s32 temp_v0;

    if (D_800BE616 != 0) {
        func_1508B20C((*(f32 *)((u8 *)arg1 + 0x14)), (*(f32 *)((u8 *)arg1 + 0x18)), (*(f32 *)((u8 *)arg1 + 0x1C)), 900.0f);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x38)) == 0) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if (temp_v0 < 0x19) {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) (temp_v0 + D_800BE9E4);
        } else {
            (*(s32 *)((u8 *)arg0 + 0x3C)) = func_1000FA64(0x513U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x1C)), 0x7D00, 0x3E8U, 0x1F4, (s32) &func_15033ECC, arg0, (s32) arg1, 0, 0);
            (*(s32 *)((u8 *)arg0 + 0x38)) = 0x513;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
s32 func_150ADA20(void);
void func_10010FFC(s32, s32, s32, s32, s32, u8 *);

/*
 * P71: sound callback of the attachment sounds (func_1000FA64 / func_1000FD38 with rec, owner; voice +0x18 / +0x1C).
 * Missing record / owner (or owner state 0): 1. Keeps the voice at the owner's position (+2 / +4 / +6). Playing
 * (*playing): model 0x37 follows the owner's animation +0x84 (on a change to 0x15F one of sounds 0x444..0x447
 * starts, func_10010FFC) and returns 0; others: when the owner's +0x31C->+0x19C < 100 the looping 0x513 sound
 * becomes a new 0x3A1 voice (rec +0x38 / +0x3C, returns 1), else 0. Stopped: model 0x37 stops its +0x24 voice and
 * clears *out (0), others return 1.
 */
s32 func_15033ECC(u8 *voice, s32 arg1, s32 *playing, s32 arg3, s32 arg4, s32 arg5, u16 *out) {
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
            func_100111C8(*(u16 *) (voice + 0x24));
            *(u16 *) (voice + 0x24) = 0;
        }
        *out = 0;
        return 0;
    }
    if (rec[1] == 0x37) {
        snd = -1;
        if ((*(s32 *) (rec + 0x38) & 0xFFFF) != *(u16 *) (obj + 0x84) && *(u16 *) (obj + 0x84) == 0x15F) {
            snd = (func_150ADA20() & 3) + 0x444;
        }
        if (snd != -1) {
            func_10010FFC(0, snd, 0x5DC0, 0, 0, obj);
        }
        *(s32 *) (rec + 0x38) = *(u16 *) (obj + 0x84);
        return 0;
    }
    p = *(u8 **) (obj + 0x31C);
    if (p != NULL && *(u16 *) (p + 0x19C) < 100 && *(s32 *) (rec + 0x38) == 0x513) {
        *(s32 *) (rec + 0x38) = 0x3A1;
        *(s32 *) (rec + 0x3C) = func_1000FA64(0x3A1, (s32) *(f32 *) (obj + 0x14), (s32) *(f32 *) (obj + 0x18),
                                              (s32) *(f32 *) (obj + 0x1C), 0x7D00, 0x3E8, 0x1F4,
                                              (s32) func_15033ECC, rec, (s32) obj, 0, 0);
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_5D910/func_15033ECC.s")
#endif

s32 func_150340F0(s32 arg0, u8 *arg1) {
    if (arg1[5] == 3) {
        return 1;
    }
    return 0;
}

s32 func_15034118(u8 *arg0, s32 *arg1) {
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

u8 *func_15034174(u8 *arg0) {
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

void func_150341B4(s32 arg0, s32 arg1) {
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

s32 func_150341FC(s32 arg0, u8 *arg1) {
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

s32 func_15034260(s32 arg0, u8 *arg1) {
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
