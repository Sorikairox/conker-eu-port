/* P65: head / eye aim state of an object (byte offsets; the struct127 field types there do not match the asm) */
#define LOOK_MODE(o)      (*(u8 *) ((u8 *) (o) + 0x276))
#define LOOK_PHASE(o)     (*(u16 *) ((u8 *) (o) + 0x278))
#define LOOK_ANGLE(o, i)  (((s16 *) ((u8 *) (o) + 0x27A))[i])  /* 0: -yaw1, 1: yaw0, 2: pitch1, 3: pitch0 */
#define LOOK_TIMER(o)     (*(u16 *) ((u8 *) (o) + 0x282))
#define LOOK_OFS(o, i)    (((s8 *) ((u8 *) (o) + 0x284))[i])   /* added to angles 0, 2, 1, 3 */

extern s32 D_800C43F0;      /* f32 x, y, z: default aim point */
extern u8 D_800C43FC;       /* one-shot: use D_800C4400 / D_800C4404 as the angles */
extern f32 D_800C4400;
extern f32 D_800C4404;
s32 func_150220CC(f32 *, f32 *, s32, s32);
f32 func_150489B0(u8);
u8 *func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);

/* move *cur toward target by at most step */
#define LOOK_STEP(cur, target, step)                         \
    {                                                        \
        s32 d_ = (target) - (cur);                           \
        if (((d_ < 0) ? -d_ : d_) < (step)) {                \
            (cur) = (target);                                \
        } else {                                             \
            (cur) = (cur) + (step) * ((d_ < 0) ? -1 : 1);    \
        }                                                    \
    }

/*
 * P65: head / eye aiming for the objects with a look joint (by id: Conker 0..4, 0x82, 0x96 use joint 12 and keep
 * D_800C43F0; others ask func_15037CCC for the target in D_800C4408). The joint matrix is made affine; while the
 * timer +0x282 runs, mode +0x276 animates the angles (0: circling offsets, 1: growing offsets, 2: aim at sub-model
 * 0x2B's point, 3: aim at joint +0x278, 4: nodding for model 0x26, 5: scaled offsets, 6: fixed pose); otherwise
 * the angles come from the target in joint space (atan2, in degrees), func_150220CC may override them, they are
 * clamped (yaw +-45, pitch -15..30), scaled by the per-id limits D_800D1C90[id] +0x2C..+0x2F and approached by
 * 8 (or 4 without target) per call in +0x27A..+0x280. UNVERIFIED parts: see P65.md.
 */
void func_1503AB20(struct127 *obj) {
    f32 *joint;
    u8 *sub;
    u8 *mtxs;
    u8 *limits;
    u8 id;
    s32 index;
    s32 jointNo;
    s32 lookFlags;
    s32 callTarget;
    s32 step;
    s32 aim;          /* compute the angles toward D_800C4408 */
    s32 aimAllowed;   /* cleared when mode 2 found its point */
    s32 useOffsets;   /* the angles are exactly the +0x284 offsets */
    s32 clamp;
    s32 mirror;       /* eye 1 copies eye 0 */
    s32 a, b, n;
    u16 phase;
    f32 k;
    f32 s, c;
    f32 yaw0, pitch0, yaw1, pitch1;
    f32 dx, dy, dz;
    f32 jx, jy, jz;
    f32 tYaw0, tYaw1, tPitch0, tPitch1;

    if (obj->unk1D4 == NULL) {
        return;
    }
    D_800C4408[0] = ((f32 *) &D_800C43F0)[0];
    D_800C4408[1] = ((f32 *) &D_800C43F0)[1];
    D_800C4408[2] = ((f32 *) &D_800C43F0)[2];

    id = obj->id;
    step = 8;
    lookFlags = 0x100;
    callTarget = TRUE;
    mirror = TRUE;
    clamp = TRUE;
    useOffsets = FALSE;
    aim = TRUE;
    aimAllowed = TRUE;
    switch (id) {
        case 0x9A:
            jointNo = 13;
            break;
        case 0x92:
        case 0x15:
        case 0x45:
            jointNo = 3;
            break;
        case 0x52:
            jointNo = 0;
            break;
        case 0x54:
            jointNo = 29;
            break;
        case 0x18:
        case 0x1E:
            jointNo = 2;
            if (id == 0x1E) {
                lookFlags = 0x22;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 0x82:
        case 0x96:
            jointNo = 12;
            callTarget = FALSE;
            break;
        default:
            return;
    }
    if (callTarget) {
        func_15037CCC(D_800C4408, jointNo, jointNo, obj - D_800CC2D0, 90.0f, lookFlags, 0);
    }

    index = obj - D_800CC2D0;
    joint = (f32 *) ((u8 *) D_800CC2D0[index].unk1D4 + jointNo * 64);
    joint[15] = 1.0f;
    joint[11] = 0.0f;
    joint[7] = 0.0f;
    joint[3] = 0.0f;
    yaw0 = 0.0f;
    pitch0 = 0.0f;

    if (LOOK_TIMER(obj) == 0) {
        LOOK_PHASE(obj) = 0;
        LOOK_OFS(obj, 0) = 0;
        LOOK_OFS(obj, 1) = 0;
        LOOK_OFS(obj, 2) = 0;
        LOOK_OFS(obj, 3) = 0;
    }
    if (LOOK_TIMER(obj) != 0) {
        aim = FALSE;
        switch (LOOK_MODE(obj)) {
            case 0:
                /* circling: remove last offsets, advance the two phase bytes, new offsets of radius 11 (fading in
                 * over the last 30 frames) */
                LOOK_ANGLE(obj, 0) -= LOOK_OFS(obj, 0);
                LOOK_ANGLE(obj, 2) -= LOOK_OFS(obj, 1);
                LOOK_ANGLE(obj, 1) -= LOOK_OFS(obj, 2);
                LOOK_ANGLE(obj, 3) -= LOOK_OFS(obj, 3);
                phase = LOOK_PHASE(obj);
                b = (phase >> 8) - D_800BE9E4 * 4;
                a = (phase & 0xFF) + D_800BE9E4 * 3;
                LOOK_PHASE(obj) = (b << 8) | a;
                k = (LOOK_TIMER(obj) < 30) ? LOOK_TIMER(obj) / 30.0f : 1.0f;
                k = 11.0f * k;
                s = func_15048A40(a & 0xFF);
                c = func_150489B0(a & 0xFF);
                LOOK_OFS(obj, 0) = s * k;
                LOOK_OFS(obj, 1) = c * k;
                s = func_15048A40(b & 0xFF);
                c = func_150489B0(b & 0xFF);
                LOOK_OFS(obj, 2) = s * k;
                LOOK_OFS(obj, 3) = c * k;
                break;
            case 1:
                if (LOOK_PHASE(obj) == 0) {
                    LOOK_PHASE(obj) = 1;
                    LOOK_OFS(obj, 3) += (u32) func_150ADA20() % 20;
                }
                n = (LOOK_TIMER(obj) < 0xAE) ? LOOK_TIMER(obj) / 6 + 1 : 30;
                LOOK_OFS(obj, 0) = 0;
                LOOK_OFS(obj, 1) += n;
                LOOK_OFS(obj, 3) += n;
                LOOK_OFS(obj, 2) = LOOK_OFS(obj, 0);
                useOffsets = TRUE;
                yaw0 = LOOK_OFS(obj, 0);
                pitch0 = LOOK_OFS(obj, 1);
                yaw1 = LOOK_OFS(obj, 2);
                pitch1 = LOOK_OFS(obj, 3);
                break;
            case 2:
                aim = TRUE;
                sub = func_15031C4C((u8 *) obj, 0x2B, 0);
                if (sub != NULL) {
                    mtxs = *(u8 **) (sub + 0x48);
                    if (mtxs != NULL && ((s32 *) (mtxs + 0x3E8))[D_800BE9C0] != 0) {
                        func_15043FF0((vertex *) D_800C4408,
                                      (struct113 *) (((s32 *) (mtxs + 0x3E8))[D_800BE9C0] + 0x80));
                        aimAllowed = FALSE;
                    }
                }
                break;
            case 3:
                /* aim at another joint of the model (the "none" test compares the u16 with -1: never true) */
                if (LOOK_PHASE(obj) != -1 && obj->unk1D4 != NULL) {
                    f32 *j = (f32 *) ((u8 *) obj->unk1D4 + LOOK_PHASE(obj) * 64);

                    D_800C4408[0] = j[12];
                    D_800C4408[1] = j[13];
                    D_800C4408[2] = j[14];
                }
                break;
            case 4:
                if (*(u16 *) ((u8 *) obj + 0x84) == 0x26) {
                    /* nod between -20 and 20 */
                    if (LOOK_PHASE(obj) == 0) {
                        LOOK_OFS(obj, 0) -= D_800BE9E4;
                        if (LOOK_OFS(obj, 0) < -20) {
                            LOOK_OFS(obj, 0) = -20;
                            LOOK_PHASE(obj) = 1;
                        }
                    } else {
                        LOOK_OFS(obj, 0) += D_800BE9E4 * 3;
                        if (LOOK_OFS(obj, 0) >= 21) {
                            LOOK_OFS(obj, 0) = 20;
                            LOOK_PHASE(obj) = 0;
                        }
                    }
                    LOOK_OFS(obj, 3) = 0;
                    LOOK_OFS(obj, 2) = LOOK_OFS(obj, 0);
                    LOOK_OFS(obj, 1) = LOOK_OFS(obj, 3);
                    useOffsets = TRUE;
                } else {
                    LOOK_TIMER(obj) = 0;
                    aim = TRUE;
                }
                break;
            case 5:
                yaw0 = LOOK_OFS(obj, 0) * 0.35433072f;
                yaw1 = LOOK_OFS(obj, 2) * 0.35433072f;
                pitch0 = LOOK_OFS(obj, 1) * 0.23622048f;
                clamp = FALSE;
                mirror = FALSE;
                pitch1 = LOOK_OFS(obj, 3) * 0.23622048f;
                break;
            case 6:
                if (*((u8 *) obj->unk31C + 0x78) == 0x2A) {
                    pitch0 = 30.0f;
                    yaw0 = -6.0f;
                    yaw1 = 6.0f;
                } else {
                    yaw0 = 0.0f;
                    yaw1 = 0.0f;
                    pitch0 = 0.0f;
                    if (LOOK_ANGLE(obj, 2) == 0) {
                        LOOK_MODE(obj) = 0;
                    }
                }
                mirror = FALSE;
                pitch1 = pitch0;
                break;
        }
        if (LOOK_TIMER(obj) != 0xFFFF) {
            if (LOOK_TIMER(obj) < D_800BE9E4) {
                LOOK_TIMER(obj) = 0;
            } else {
                LOOK_TIMER(obj) = LOOK_TIMER(obj) - D_800BE9E4;
            }
        }
    }

    if (aim) {
        if ((obj->unk2FB & 4) && aimAllowed) {
            yaw0 = 0.0f;
            pitch0 = 0.0f;
        } else if (D_800C4408[0] == -99999.0f && D_800C4408[1] == -99999.0f && D_800C4408[2] == -99999.0f) {
            step = 4;   /* no target: keep the angles, turn slowly */
        } else if (D_800C43FC != 0) {
            D_800C43FC = 0;
            yaw0 = D_800C4400;
            pitch0 = D_800C4404;
        } else {
            /* target relative to the joint, in joint space */
            dx = D_800C4408[0] - joint[12];
            dy = D_800C4408[1] - joint[13];
            dz = D_800C4408[2] - joint[14];
            jx = joint[2] * dz + (dx * joint[0] + dy * joint[1]);
            jy = joint[6] * dz + (dx * joint[4] + dy * joint[5]);
            jz = joint[10] * dz + (dx * joint[8] + dy * joint[9]);
            yaw0 = func_150484A0(jx, jz) * 57.29578f;
            pitch0 = func_150484A0(jy, sqrtf(jx * jx + jz * jz)) * 57.29578f;
            if (yaw0 > 180.0f) {
                yaw0 -= 360.0f;
            }
            if (pitch0 > 180.0f) {
                pitch0 -= 360.0f;
            }
        }
    }

    if (LOOK_TIMER(obj) == 0 && func_150220CC(&yaw0, &pitch0, index, 0) != 0) {
        clamp = TRUE;
        mirror = FALSE;
        useOffsets = FALSE;
        step = 8;
    }

    if (clamp) {
        if (yaw0 < -45.0f) {
            yaw0 = -45.0f;
        } else if (yaw0 > 45.0f) {
            yaw0 = 45.0f;
        }
        if (pitch0 < -15.0f) {
            pitch0 = -15.0f;
        } else if (pitch0 > 31.0f) {
            pitch0 = 30.0f;
        }
        if (yaw1 < -45.0f) {
            yaw1 = -45.0f;
        } else if (yaw1 > 45.0f) {
            yaw1 = 45.0f;
        }
        if (pitch1 < -15.0f) {
            pitch1 = -15.0f;
        } else if (pitch1 > 30.0f) {
            pitch1 = 30.0f;
        }
    }
    if (mirror) {
        pitch1 = pitch0;
        yaw1 = yaw0;
    }

    limits = (u8 *) D_800D1C90[id];
    if (limits == NULL) {
        return;
    }
    /* scale to the per-id limits: +0x2C / +0x2D yaw (one per side), +0x2E up, +0x2F down */
    tYaw0 = (yaw0 >= 0.0f) ? yaw0 * (s8) limits[0x2D] / 45.0f : yaw0 * (s8) limits[0x2C] / -45.0f;
    tYaw1 = (yaw1 >= 0.0f) ? yaw1 * (s8) limits[0x2C] / 45.0f : yaw1 * (s8) limits[0x2D] / -45.0f;
    tYaw1 = -tYaw1;
    tPitch0 = (pitch0 >= 0.0f) ? pitch0 * (s8) limits[0x2E] / 30.0f : pitch0 * (s8) limits[0x2F] / -15.0f;
    tPitch1 = (pitch1 >= 0.0f) ? pitch1 * (s8) limits[0x2E] / 30.0f : pitch1 * (s8) limits[0x2F] / -15.0f;

    LOOK_STEP(LOOK_ANGLE(obj, 0), (s32) tYaw1, step);
    LOOK_STEP(LOOK_ANGLE(obj, 1), (s32) tYaw0, step);
    LOOK_STEP(LOOK_ANGLE(obj, 2), (s32) tPitch1, step);
    LOOK_STEP(LOOK_ANGLE(obj, 3), (s32) tPitch0, step);

    if (useOffsets) {
        LOOK_ANGLE(obj, 0) = LOOK_OFS(obj, 0);
        LOOK_ANGLE(obj, 2) = LOOK_OFS(obj, 1);
        LOOK_ANGLE(obj, 1) = LOOK_OFS(obj, 2);
        LOOK_ANGLE(obj, 3) = LOOK_OFS(obj, 3);
    }
    if (LOOK_TIMER(obj) != 0 && LOOK_MODE(obj) == 0) {
        LOOK_ANGLE(obj, 0) += LOOK_OFS(obj, 0);
        LOOK_ANGLE(obj, 2) += LOOK_OFS(obj, 1);
        LOOK_ANGLE(obj, 1) += LOOK_OFS(obj, 2);
        LOOK_ANGLE(obj, 3) += LOOK_OFS(obj, 3);
    }
}
