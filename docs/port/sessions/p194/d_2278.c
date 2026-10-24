s32 func_150EBA04(u8 *arg0, f32 *arg1, s32 arg2);
void func_150D779C(f32 *normal, f32 *pos, f32 *dir, s32 arg3, s32 arg4);
void func_15104B88(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
void func_150B5C38(u8 *arg0, u8 arg1, s32 arg2);
void func_150B6C34(u8 arg0, s32 arg1);
void func_150D7630(u8 *arg0, u8 arg1, s32 arg2);
extern u8 D_80099E84[];   /* per weapon kind: the hit-effect id passed to func_1505D024 */
extern f32 D_8009CFF8;    /* 65536 / 360 */
/* the hit record a ray cast fills (func_15081A90); only the fields used here */
typedef struct {
    u8 *target;          /* 0x00: the object hit */
    f32 dist;            /* 0x04 */
    f32 pos[3];          /* 0x08 */
    f32 floorY;          /* 0x14: unused here */
    f32 f18;             /* 0x18 */
    f32 u1C;
    f32 v20[3];          /* 0x20 */
    f32 u2C[3];
    f32 dir[3];          /* 0x38 */
    f32 normal[3];       /* 0x44 */
    u8 pad50[6];
    u16 part;            /* 0x56: the body part hit */
    u8 sub;              /* 0x58: hit detail (10 = head?) */
    u8 type;             /* 0x59: 0 nothing, 1 world, 2 / 3 objects */
    u8 u5A;              /* 0x5A */
} Hit15082278;
/* the stack block func_150335C8 gets (only the fields set here; the rest is stack garbage on N64 too) */
typedef struct {
    u8 pad0[0x14];
    f32 pos[3];          /* 0x14 */
    u8 pad20[0x40 - 0x20];
    f32 yaw;             /* 0x40: hit direction + 180 */
    u8 pad44[0xB8 - 0x44];
    f32 pitch;           /* 0xB8 */
    u8 padBC[0xC4 - 0xBC];
    f32 uC4;             /* 0xC4 */
    u8 padC8[0x14C - 0xC8];
    f32 u14C[2];         /* 0x14C: copied from the target */
    u8 pad154[0x32C - 0x154];
} Reaction15082278;

// shot_hit_apply: P194. Applies a weapon ray hit `h` (filled by func_15081A90) of shooter obj with weapon kind `kind`;
// counts the shot in the shooter's controller (+0x31C, +0x1AA). Returns 0 when nothing was hit. World hits (type 1):
// per-kind impact effect func_151D3A30 (kind 2: 1, 6: 0, 7: 5, 11: 3, 12: 2, 18: 4, others 5); kind 13 a decal
// func_150D779C instead, kinds 5 / 9 / 10 a ricochet (func_15104B88, an empty function, and func_1506B04C(obj, 2)),
// with on level 0xE kind 5 also the probe func_150EBA04 5 units around the point; returns 1.
// Object hits (types 2 / 3, target h->target): kinds 5 / 9 / 10 call func_1506B04C(obj, 3); a target that is
// invulnerable (+0x125 / +0x104) and already reacting (+0x1CA) is skipped (return 2). Type 2: target type 0x94 gets
// func_150B5C38 / func_150B6C34 and no blood (func_15137610). Type 3: with sub 10 (head shot) and no earlier head shot
// (controller +0x1AD) the target dies (func_1507DE4C, its sounds 0x2E3.. / func_15138C80 / sound 0xAA, effect 0x20 /
// 0x3D) or, for kinds 2 / 11 / 12 / 18, only plays sound 0x107; targets 0x9F / 0xA0 (unless D_800BE616) farther than
// 1000 call func_1508220C instead. Kinds 2 / 18 / 12 / 11 start the reaction func_150335C8 (0x2A / 0x22 / 0x6B / 0x6D)
// while +0x1CA < 2. Then the blood / sparks func_15137610, kind 13 func_150D7630, and when the target was already
// reacting, func_1505D024(target, effect | 0x80000, (direction - 90) as a u16 angle, shooter player index). Returns 2.
s32 func_15082278(u8 *obj, u8 *hit, s32 kind) {
    Hit15082278 *h = (Hit15082278 *) hit;
    Reaction15082278 r;
    u8 *target;
    u8 *ctrl;
    f32 yaw, pitch;
    f32 a[3], b[3];
    s32 probe;
    s32 fresh;
    s32 effect;
    s32 far;
    s32 reaction;
    s32 blood = TRUE;
    f32 f;
    u32 angle;

    if (*(u8 **) (obj + 0x31C) != NULL) {
        (*(s16 *) (*(u8 **) (obj + 0x31C) + 0x1AA))++;
    }
    if (h->type == 0) {
        return 0;
    }
    if (h->type == 1) {
        switch (kind) {
            case 18: effect = 4; break;
            case 6: effect = 0; break;
            case 2: effect = 1; break;
            case 7: effect = 5; break;
            case 11: effect = 3; break;
            case 12: effect = 2; break;
            case 13:
                effect = -1;
                func_150D779C(h->normal, h->pos, h->dir, 0xFF, 1);
                break;
            case 5:
                if (D_800BE9F0 == 0xE) {
                    a[0] = h->pos[0] + h->dir[0] * 5.0f;
                    a[1] = h->pos[1] + h->dir[1] * 5.0f;
                    a[2] = h->pos[2] + h->dir[2] * 5.0f;
                    b[0] = h->pos[0] - h->dir[0] * 5.0f;
                    b[1] = h->pos[1] - h->dir[1] * 5.0f;
                    b[2] = h->pos[2] - h->dir[2] * 5.0f;
                    func_150EBA04((u8 *) a, b, (s32) &probe);
                }
                /* fallthrough */
            case 9:
            case 10:
                effect = -1;
                func_15104B88(h->pos[0], h->pos[1], *(s32 *) &h->pos[2], obj[0x124]);
                func_1506B04C((struct127 *) obj, 2, NULL);
                break;
            default:
                effect = 5;
                break;
        }
        if (effect != -1) {
            func_151D3A30(h->pos, h->dir, (s32) h->normal, effect & 0xFF, 0xFF, 1);
        }
        return 1;
    }

    target = h->target;
    if (kind == 5 || kind == 9 || kind == 10) {
        func_1506B04C((struct127 *) obj, 3, NULL);
    }
    fresh = (target[0x1CA] == 0);
    if ((target[0x125] != 0 || target[0x104] != 0) && !fresh) {
        return 2;
    }
    effect = D_80099E84[kind];
    if (kind == 7 && D_800BE9F0 == 0x2B) {
        effect = 0x27;
    }
    func_15145974(h->dir, &yaw, &pitch);
    if (h->type == 2) {
        if (target[4] == 0x94) {
            blood = FALSE;
            func_150B5C38(h->pos, 0xFF, 1);
            func_150B6C34(0xFF, 1);
        }
    } else if (h->type == 3) {
        far = FALSE;
        if (D_800BE616 == 0 && (target[4] == 0x9F || target[4] == 0xA0) && 1000.0f < h->dist) {
            far = TRUE;
        }
        ctrl = *(u8 **) (target + 0x31C);
        if (h->sub == 10 && (ctrl == NULL || ctrl[0x1AD] == 0) && !far) {
            if (kind == 2 || kind == 18 || kind == 11 || kind == 12) {
                func_15060A30(0x107, (struct127 *) target);
            } else {
                func_1507DE4C((struct127 *) target);
                if (*(u8 **) (target + 0x31C) != NULL) {
                    (*(u8 **) (target + 0x31C))[0x1AD] = 1;
                }
                if (target[4] == 0x80 && h->u5A == 0 && h->f18 < h->pos[1] - 5.5f) {
                    func_15060A9C((func_150ADA20() & 7) + 0x2E3, (struct127 *) target);
                }
                func_15138C80((struct127 *) target, 0xFF, 1);
                effect = 0x20;
                if ((target[4] == 0x9F || target[4] == 0xA0) && *(s32 *) (target + 0x2EC) != 0) {
                    effect = 0x3D;
                }
                func_15060A30(0xAA, (struct127 *) target);
            }
            if (kind != 11 && kind != 12 && target[0x1CA] != 0) {
                target[0x1CA] = 1;
            }
        } else if (target[4] == 0x9F || target[4] == 0xA0) {
            func_1508220C(target, h->sub, far);
        }
        switch (kind) {
            case 2: reaction = 0x2A; break;
            case 11: reaction = 0x6D; break;
            case 12: reaction = 0x6B; break;
            case 18: reaction = 0x22; break;
            default: reaction = 0; break;
        }
        if (reaction != 0 && target[0x1CA] < 2) {
            r.pos[0] = h->pos[0];
            r.pos[1] = h->pos[1];
            r.yaw = yaw + 180.0f;
            r.pitch = pitch;
            r.pos[2] = h->pos[2];
            r.uC4 = 0.0f;
            r.u14C[0] = *(f32 *) (target + 0x14C);
            r.u14C[1] = *(f32 *) (target + 0x150);
            func_150335C8((u8 *) &r, target, reaction, h->part, 1, 0);
            if (h->sub == 10) {
                effect = 0x20;
            }
        }
    }
    if (blood) {
        func_15137610(h->target, h->pos, h->v20, h->dir, 0xFF, 1);
    }
    if (kind == 13) {
        func_150D7630((u8 *) h->pos, 0xFF, 1);
    }
    if (!fresh) {
        /* (u32) of the angle the IDO way: truncation, values >= 2^31 through the -2^31 retry, negatives -> -1 */
        f = (yaw - 90.0f) * D_8009CFF8;
        if (f >= 2147483648.0f) {
            f -= 2147483648.0f;
            angle = (f >= 2147483648.0f) ? 0xFFFFFFFF : ((u32) (s32) f | 0x80000000);
        } else if (f > -1.0f) {
            angle = (s32) f;
        } else {
            angle = 0xFFFFFFFF;
        }
        func_1505D024((struct127 *) target, effect | 0x80000, angle & 0xFFFF,
                      (obj - (u8 *) D_800CC2D0) / 0x32C);
    }
    return 2;
}
