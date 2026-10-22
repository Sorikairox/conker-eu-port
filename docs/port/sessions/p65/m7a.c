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
                            func_150A8050(xform, 0.0f, 0.0f, rec->spin * (360.0f / 65536.0f));
                            func_150A7A48(xform, m, res);
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
                } else if (D_800BE9E4 <= t) {
                    rec->timer = t - D_800BE9E4;
                } else {
                    rec->timer = 0;
                }
            }
        }
    }
}
