#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15036F60 */
void look_record_alloc(u8 *arg0) {
    s32 i;

    *(f32 **)(arg0 + 0x324) = allocate_memory(0x48, 1, 0, 0);
    bzero(*(f32 **)(arg0 + 0x324), 0x48);
    for (i = 0; i < 3; i++) {
        (*(f32 **)(arg0 + 0x324))[i] = -99999.0f;
        (*(f32 **)(arg0 + 0x324))[i + 3] = -99999.0f;
    }
}

#ifdef NON_MATCHING
void look_find_target(f32 *, s32, s32, s32, f32, s32, s32);
void look_turn_joint(s32, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800C441A;
extern f32 D_800C4408[3];

/*
 * P65: per-frame callback of the current object D_800CC2D0[D_800C3E78] (called twice per frame for Conker).
 * D_800C441A counts the calls of this frame: the first call of a frame is skipped (only sets the counter to 1) for
 * object ids 0x3B / 0x75 / 0x80 / ... (jump table jtbl_80098604, a .late_rodata table: not code), when D_800C35EA == 1,
 * or when the record +0x324 still holds the -99999 "unset" x. Otherwise point D_800C4408 is filled by look_find_target
 * (or set to -99999 on a first call without D_800D154C->unk2F8 & 0x100) and passed to look_turn_joint.
 */
/* was func_15036FD8 */
void look_frame_cb_current(void) {
    struct127 *obj = &D_800CC2D0[D_800C3E78];
    u8 *rec = obj->unk324;
    s32 kind;
    s32 first;
    s32 later;

    if (rec == NULL) {
        return;
    }
    switch (obj->id) {
        case 0x3B:
        case 0x75: case 0x80: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C:
        case 0x9D: case 0x9F: case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
            if (D_800C441A == 0) {
                D_800C441A = 1;
                return;
            }
            break;
    }
    if (D_800C35EA == 1 && D_800C441A == 0) {
        D_800C441A = 1;
        return;
    }

    first = FALSE;
    later = TRUE;
    if (D_800C441A == 0) {
        kind = 7;
        first = TRUE;
        later = FALSE;
        if (D_800D154C->unk2F8 & 0x100) {
            *(s16 *)(rec + 0x3A) = 0x2D;
            *(s16 *)(rec + 0x40) = 0x40;
        } else if (*(f32 *)rec == -99999.0f) {
            D_800C441A = 1;
            return;
        }
    } else {
        kind = 12;
    }

    if (D_800C441A == 0 && !(D_800D154C->unk2F8 & 0x100)) {
        D_800C4408[0] = -99999.0f;
        D_800C4408[1] = -99999.0f;
        D_800C4408[2] = -99999.0f;
    } else {
        look_find_target(D_800C4408, kind, 0, D_800C3E78, 90.0f, 0xFF, 0);
    }
    look_turn_joint(kind, 0, D_800C4408, D_800C3E78, first, 0, D_800C441A, 3, 0, 0, 0, later, 0);
    D_800C441A++;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_frame_cb_current.s")
#endif

#ifdef NON_MATCHING
extern u8 D_800C441A;
extern f32 D_800C4408[3];
void look_find_target_simple(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void look_turn_joint(s32, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

/*
 * P76: head / body look of the current object D_800CC2D0[D_800C3E78] by object kind (+4; jump table jtbl_80098714,
 * .late_rodata data: now a C switch; kinds without a case do nothing). Each kind picks the joint / parent joint pair
 * (slot D_800C441A = 0 / 1 / 2 may differ), the look limit row lookArg, follow factors limits, keepMask, wrap
 * (passed as the force flag of the joint range test), postMul, the target search options (needVisible, anyRange, mode, prefer) and a
 * y offset. The target D_800C4408 comes from look_find_target_simple on the first slot or when `always` is set (range: the sum
 * of floats 0 and 4 of row lookArg - 1 of D_80098418), or is cleared (-99999) for `noTarget`; then look_turn_joint
 * turns the joint and D_800C441A counts up.
 */
/* was func_15037224 */
void look_head_body_by_kind(void) {
    u8 *self = (u8 *) &D_800CC2D0[D_800C3E78];
    s32 prefer = 0x100;
    s32 joint, parent;
    s32 limits = 1;
    s32 lookArg = 2;
    s32 keepMask = 3;
    s32 always = FALSE;
    s32 wrap = FALSE;
    s32 needVisible = FALSE;
    s32 postMul = FALSE;
    s32 anyRange = FALSE;
    s32 mode = 0;
    s32 later = TRUE;
    s32 noTarget = FALSE;
    f32 yOfs = 0.0f;
    f32 best = 1.6e9f;

    switch (self[4]) {
        case 0x82:
            joint = 0xC;
            parent = 1;
            break;
        case 0x0C: case 0x16: case 0x22: case 0x34: case 0x58: case 0x5B: case 0x5E: case 0x69: case 0x76:
        case 0x7D: case 0x87: case 0x97: case 0xA2: case 0xA4: case 0xB3: case 0xB5:
            joint = 4;
            parent = 3;
            break;
        case 0x31:
            joint = 5;
            parent = 4;
            break;
        case 0x8B:
            joint = 0x21;
            parent = 0x20;
            break;
        case 0x11: case 0x14: case 0x86: case 0x99:
            parent = 3;
            joint = 5;
            if (D_800C441A == 0) {
                joint = 4;
                limits = 10;
            } else {
                parent = 4;
            }
            break;
        case 0x79:
            joint = 0x1B;
            parent = 0x1A;
            break;
        case 0x21:
            joint = 0x19;
            parent = 0x18;
            break;
        case 0x7B:
            joint = 3;
            parent = 2;
            if (D_800C441A == 0) {
                anyRange = TRUE;
                break;
            }
            yOfs = -165.0f;
            lookArg = 10;
            limits = 7;
            if (*(u16 *) (self + 0x84) == 7 || *(u16 *) (self + 0x84) == 9) {
                needVisible = TRUE;
            } else if (*(u16 *) (self + 0x84) == 0x14) {
                prefer = 0x7E;
                yOfs = 0.0f;
                limits = 9;
                lookArg = 0xB;
            } else {
                noTarget = TRUE;
            }
            if (D_800C441A == 1) {
                joint = 0x16;
                parent = 0x16;
                mode = 2;
                always = TRUE;
            } else {
                joint = 0x1A;
                parent = 0x1A;
                mode = 1;
            }
            anyRange = TRUE;
            break;
        case 0x7C:
            joint = 1;
            parent = 0;
            needVisible = TRUE;
            mode = 3;
            break;
        case 0x6C:
            joint = 0x11;
            parent = 0x10;
            break;
        case 0x8A:
            if (D_800BE616 != 0) {
                return;
            }
            joint = 4;
            parent = 0;
            if (*(s32 *) (self + 0x2E8) == 1) {
                return;
            }
            yOfs = -100.0f;
            keepMask = 2;
            lookArg = 0xC;
            break;
        case 0x20: case 0x5A: case 0x5F: case 0x74: case 0x7A: case 0x8C: case 0x8D: case 0x93:
            joint = (self[4] == 0x20 || self[4] == 0x8C || self[4] == 0x93) ? 2 : 3;
            parent = joint - 1;
            break;
        case 0x54:
            joint = 0x1D;
            parent = 0x1C;
            needVisible = TRUE;
            break;
        case 0x29:
            joint = 2;
            parent = 1;
            break;
        case 0x4B:
            joint = 0x2C;
            parent = 4;
            needVisible = TRUE;
            if (D_800C441A == 0) {
                joint = 0x2B;
                limits = 6;
                later = FALSE;
            }
            anyRange = TRUE;
            break;
        case 0x50: case 0x9A: case 0x9B:
            joint = 0xD;
            parent = 2;
            break;
        case 0x47: case 0x4A:
            joint = 1;
            parent = 0;
            keepMask = 1;
            wrap = TRUE;
            break;
        case 0x44:
            joint = 3;
            parent = 3;
            break;
        case 0x28:
            joint = 3;
            parent = 2;
            keepMask = 2;
            if (D_800C441A == 0) {
                joint = 2;
                parent = 0;
                keepMask = 1;
            }
            postMul = TRUE;
            wrap = TRUE;
            limits = 4;
            break;
        case 0x2B:
            joint = 1;
            parent = 0;
            lookArg = 3;
            limits = 3;
            keepMask = 1;
            wrap = TRUE;
            needVisible = TRUE;
            break;
        case 0x3A: case 0x3D:
            joint = 5;
            parent = 4;
            lookArg = 5;
            break;
        case 0x53: case 0xA5:
            joint = 5;
            parent = 0;
            lookArg = 7;
            break;
        case 0x36:
            joint = 4;
            parent = 3;
            lookArg = 4;
            break;
        case 0x2D:
            joint = 5;
            parent = 4;
            needVisible = TRUE;
            break;
        case 0x05: case 0xAD: case 0xAE: case 0xAF:
            parent = 0;
            joint = 0x10;
            if (D_800C441A == 0) {
                joint = 1;
                limits = 2;
                later = FALSE;
            } else {
                parent = 1;
            }
            break;
        case 0x12:
            keepMask = 2;
            lookArg = 8;
            anyRange = TRUE;
            parent = 0;
            joint = (D_800C441A == 0) ? 1 : (D_800C441A == 1) ? 3 : 5;
            needVisible = TRUE;
            break;
        default:
            return;
    }
    if (noTarget) {
        D_800C4408[0] = D_800C4408[1] = D_800C4408[2] = -99999.0f;
    } else if (D_800C441A == 0 || always) {
        look_find_target_simple((u8 *) D_800C4408, joint, parent, D_800C3E78,
                      ((f32 *) D_80098418[lookArg - 1])[4] + ((f32 *) D_80098418[lookArg - 1])[0], prefer,
                      (s32) &best, wrap, needVisible, anyRange, mode);
        D_800C4408[1] += yOfs;
    }
    look_turn_joint(joint, parent, D_800C4408, D_800C3E78, lookArg, limits, D_800C441A, keepMask, wrap, postMul, 0,
                  later, mode);
    D_800C441A++;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_head_body_by_kind.s")
#endif

#ifdef NON_MATCHING
void look_angles_to_point(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);

/*
 * P71: is point (x, y, z) inside the range of joint j2 of object id? The joint matrices are
 * D_800CC2D0[id].unk1D4 (64 bytes each). The translation column of joints j1 and j2 is cleared (w = 1), the point
 * relative to j1's origin is rotated by j2's rows and look_angles_to_point measures it (with mode); when the measure is
 * within (-lim, lim) the point is copied to out and 1 returned. force skips the test (copies, returns 1); no
 * matrices: 0. (The asm also saves j1's second row to an unused local.)
 */
/* was func_15037988 */
s32 look_point_in_joint_range(s32 id, s32 j1, s32 j2, f32 x, f32 y, f32 z, f32 *out, f32 lim, s32 force, s32 mode) {
    f32 *mtx;
    f32 *a;
    f32 *b;
    f32 dx, dy, dz;
    f32 dist;
    f32 unused;

    if (force) {
        out[0] = x;
        out[1] = y;
        out[2] = z;
        return 1;
    }
    mtx = (f32 *) D_800CC2D0[id].unk1D4;
    if (mtx == NULL) {
        return 0;
    }
    a = mtx + j1 * 16;
    b = mtx + j2 * 16;
    b[11] = b[7] = b[3] = 0.0f;
    a[3] = a[7] = a[11] = 0.0f;
    b[15] = 1.0f;
    a[15] = 1.0f;
    dx = x - a[12];
    dy = y - a[13];
    dz = z - a[14];
    look_angles_to_point(&dist, &unused, dx * b[0] + dy * b[1] + b[2] * dz, dx * b[4] + dy * b[5] + b[6] * dz,
                  dx * b[8] + dy * b[9] + b[10] * dz, mode);
    if (dist < lim && -lim < dist) {
        out[0] = x;
        out[1] = y;
        out[2] = z;
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_point_in_joint_range.s")
#endif
extern s32 D_800C4414;

/* was func_15037B70 */
s32 look_get_fixed_target(s32 arg0, u8 *arg1) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t8;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    temp_t8 = temp_v0->unk2F8 & 7;
    if (temp_t8 == 1) {
        (*(f32 *)arg1) = (f32) D_800DBFF0->unk2F8;
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) D_800DBFF0->unk2FC;
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) D_800DBFF0->unk300;
        return 1;
    }
    if (temp_t8 == 2) {
        if (temp_v0->unk5 == 4) {
            temp_f0 = temp_v0->x_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
            temp_f2 = temp_v0->z_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
            if (62500.0f < ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
                return 1;
            }
        }
        (*(f32 *)arg1) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 2));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
        return 1;
    }
    if (temp_t8 == 3) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
/* P76: look point table (D_800C6A70[D_800C6A74], 0x14-byte records; look_point_remove marks removed ones with unk6 = 2) */
typedef struct {
    s16 x, y, z;    /* 0x00: the point (+50 is added to y for the joint range test) */
    u16 unk6;       /* 0x06: nonzero = not usable */
    u32 range2;     /* 0x08: squared reach */
    s16 unkC;
    s16 xMax;       /* 0x0E: the looker's x must lie in (xMin, xMax) */
    s16 xMin;       /* 0x10 */
    s16 anim;       /* 0x12: 1 + animation to play when chosen, 0: none */
} LookPoint;
extern LookPoint *D_800C6A70;
extern u32 D_800C6A74;
extern u32 D_80084790;      /* round-robin start into D_800C6A70 (the last chosen point) */
extern s32 D_80084770[8];   /* the node list indices searched in D_800DD280[0..1] */
extern s32 D_800C43F0;      /* f32 x, y, z: default aim point */
u8 *attachment_find_by_slot_any(s32, u8 *);
void face_anim_stub(u8 *, s32);
s32 look_get_fixed_target(s32, u8 *);
s32 look_search_nearest_object(u8 *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);
s32 look_point_in_joint_range(s32, s32, s32, f32, f32, f32, f32 *, f32, s32, s32);

/*
 * P76: look target of object id (out = point, -99999 when there is none; D_800C43F0 is reset to -99999 too).
 * Nothing during cutscenes (D_800C35EA / D_800C35EB). Fixed targets first: a sub-object +0x318 with +0x2C == 0x100
 * and a +0x73C flag gives its point +0x740; look_get_fixed_target (look modes 1..3). Object 0 in state 0x81 (+0x84) aims at
 * the object of its attachment 0x1F (+0x48 matrices +0x3E8[D_800BE9C0], enabled by +0x3F6): its position for kind
 * 5, else that matrix's point. Otherwise the nearest candidate that passes the joint range test look_point_in_joint_range wins
 * (squared distance from the object, with x truncated to s16): the object search look_search_nearest_object (from 1.6e9), the
 * look points of D_800C6A70 (round robin from D_80084790, within each point's x window and reach) and the nodes of
 * the D_80084770 lists in both D_800DD280 groups (within 500; lists 25 and 72 use +0x38 when +0x66 is 0, the
 * others +0x98). An object or a look point with an animation then starts it on id (face_anim_stub).
 */
/* was func_15037CCC */
void look_find_target(f32 *out, s32 j1, s32 j2, s32 id, f32 lim, s32 prefer, s32 mode) {
    u8 *self;
    u8 *ext;
    u8 *sub;
    u8 *mtxs;
    s32 mtx;
    u8 *other;
    u8 *node;
    f32 pt[3];
    f32 best;
    f32 d2;
    f32 dx, dy, dz;
    s32 found;      /* 1: object, 2: look point, 3: node */
    s32 objRet;
    s32 sx;
    u32 i;
    s32 bestPoint;
    LookPoint *lp;
    s32 g, k, idx;

    out[0] = out[1] = out[2] = -99999.0f;
    ((f32 *) &D_800C43F0)[0] = ((f32 *) &D_800C43F0)[1] = ((f32 *) &D_800C43F0)[2] = -99999.0f;
    if ((&D_800C35EA)[0] == 1 || (&D_800C35EA)[1] == 1) {
        return;
    }
    self = (u8 *) &D_800CC2D0[id];
    ext = *(u8 **) (self + 0x318);
    if (ext != NULL && *(s32 *) (ext + 0x2C) == 0x100 && *(s16 *) (ext + 0x73C) != 0) {
        out[0] = *(f32 *) (ext + 0x740);
        out[1] = *(f32 *) (ext + 0x744);
        out[2] = *(f32 *) (ext + 0x748);
        return;
    }
    if (look_get_fixed_target(id, (u8 *) out) != 0) {
        return;
    }
    if (id == 0 && *(u16 *) (self + 0x84) == 0x81) {
        sub = attachment_find_by_slot_any(0x1F, self);
        if (sub != NULL && (mtxs = *(u8 **) (sub + 0x48)) != NULL && mtxs[0x3F6] != 0
            && (mtx = ((s32 *) (mtxs + 0x3E8))[D_800BE9C0]) != 0) {
            other = (u8 *) obj_find_by_setup_id(sub[0]);
            if (other != NULL) {
                if (other[5] == 5) {
                    pt[0] = *(f32 *) (other + 0x14);
                    pt[1] = *(f32 *) (other + 0x18);
                    pt[2] = *(f32 *) (other + 0x1C);
                } else {
                    vec_from_fixed_pos((vertex *) pt, (struct113 *) mtx);
                }
                if (look_point_in_joint_range(id, j1, j2, pt[0], pt[1], pt[2], out, lim, 0, mode) != 0) {
                    return;
                }
            }
        }
    }

    sx = (s16) *(f32 *) (self + 0x14);
    best = 1.6e9f;
    found = 0;
    objRet = look_search_nearest_object((u8 *) out, j1, j2, id, lim, prefer, (s32) &best, 0, 0, 0, mode);
    if (objRet != 0 && best != 1.6e9f) {
        found = 1;
    }

    if (D_80084790 >= D_800C6A74) {
        D_80084790 = 0;
    }
    if (D_800C6A74 != 0) {
        bestPoint = -1;
        i = D_80084790;
        do {
            lp = &D_800C6A70[i];
            if (sx < lp->xMax && lp->xMin < sx && lp->unk6 == 0) {
                dx = (f32) sx - lp->x;
                dz = *(f32 *) (self + 0x1C) - lp->z;
                dy = *(f32 *) (self + 0x18) - lp->y;
                d2 = dx * dx + dz * dz + dy * dy;
                if (d2 < (f32) lp->range2 && d2 < best
                    && look_point_in_joint_range(id, j1, j2, lp->x, lp->y + 50.0f, lp->z, out, lim, 0, mode) != 0) {
                    bestPoint = i;
                    best = d2;
                }
            }
            i++;
            if (i == D_800C6A74) {
                i = 0;
            }
        } while (i != D_80084790);
        if (bestPoint != -1) {
            D_80084790 = bestPoint;
            found = 2;
        }
    }

    for (g = 0; g < 2; g++) {
        for (k = 0; k < 8; k++) {
            idx = D_80084770[k];
            for (node = (u8 *) D_800DD280[g][idx]; node != NULL; node = *(u8 **) (node + 8)) {
                if (idx == 25 || idx == 72) {
                    if (*(u16 *) (node + 0x66) != 0) {
                        continue;
                    }
                    pt[0] = *(f32 *) (node + 0x38);
                    pt[1] = *(f32 *) (node + 0x3C);
                    pt[2] = *(f32 *) (node + 0x40);
                } else {
                    pt[0] = *(f32 *) (node + 0x98);
                    pt[1] = *(f32 *) (node + 0x9C);
                    pt[2] = *(f32 *) (node + 0xA0);
                }
                dz = *(f32 *) (self + 0x1C) - pt[2];
                dy = *(f32 *) (self + 0x18) - pt[1];
                dx = (f32) sx - pt[0];
                d2 = dx * dx + dz * dz + dy * dy;
                if (d2 < 250000.0f && d2 < best
                    && look_point_in_joint_range(id, j1, j2, pt[0], pt[1], pt[2], out, lim, 0, mode) != 0) {
                    found = 3;
                    best = d2;
                }
            }
        }
    }

    if (found == 1) {
        face_anim_stub(self, objRet - 1);
    } else if (found == 2 && D_800C6A70[bestPoint].anim != 0) {
        face_anim_stub(self, D_800C6A70[bestPoint].anim - 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_find_target.s")
#endif

#ifdef NON_MATCHING
s32 look_point_in_joint_range(s32 id, s32 j1, s32 j2, f32 x, f32 y, f32 z, f32 *out, f32 lim, s32 force, s32 mode);

/*
 * P71: look target search of object id: the nearest other active object (of the first 25; not 0xFF kinds) whose
 * look point (+0x1A4 / +0x1AA / +0x1A8, s16) lies within the joint range test look_point_in_joint_range (j1, j2, lim, force,
 * mode). Candidates: closer than the sight range (squared: (+0x23D * 8)^2, or 1.6e9 with anyRange) and than *best,
 * or of kind prefer (+4) at any distance; a found object of kind prefer ends the search. Skipped: objects linked to
 * each other by +0x65 (index + 1), the same kind (except for kinds 5 / 0xAD..0xAF), kind 0x2C for 0x2D, and by
 * +0x127 == 0xFF when needVisible or look mode (+0x2F8 & 7) 4, or +0x127 != 0xFF in look mode 5. The current
 * target (+0x222 with +0x223 1 / 0xC) counts as distance 0. Returns the found object's +0x13B + 1 (out = the look
 * point), else 0 with out = -99999 (also during cutscenes, D_800C35EA / D_800C35EB).
 */
/* was func_150383B0 */
s32 look_search_nearest_object(u8 *outp, s32 j1, s32 j2, s32 id, f32 lim, s32 prefer, s32 bestp, s32 force, s32 needVisible,
                  s32 anyRange, s32 mode) {
    f32 *out = (f32 *) outp;     /* the parameter types of the declaration used by look_find_target_simple */
    f32 *best = (f32 *) bestp;
    u8 *self;
    u8 *o;
    s32 kind;
    s32 sameKindOk;
    s32 exclKind;
    s32 found;
    s32 i;
    f32 range2;
    f32 r;
    f32 dx, dy, dz;
    f32 d2;

    if ((&D_800C35EA)[0] == 1 || (&D_800C35EA)[1] == 1) {
        out[0] = out[1] = out[2] = -99999.0f;
        return 0;
    }
    self = (u8 *) &D_800CC2D0[id];
    kind = self[4];
    sameKindOk = !(kind == 5 || kind == 0xAD || kind == 0xAE || kind == 0xAF);
    exclKind = (kind == 0x2D) ? 0x2C : -1;
    if (anyRange == 0) {
        r = self[0x23D] * 8;
        range2 = r * r;
    } else {
        range2 = 1.6e9f;
    }
    found = -1;
    for (i = 0; i != 25; i++) {
        o = (u8 *) &D_800CC2D0[i];
        if (*(s32 *) o == 0 || o[4] == 0xFF || i == id) {
            continue;
        }
        if (o[0x65] == id + 1 || self[0x65] == i + 1) {
            continue;
        }
        if ((!sameKindOk && kind == o[4]) || exclKind == o[4]) {
            continue;
        }
        if ((needVisible != 0 || (*(u16 *) (self + 0x2F8) & 7) == 4) && o[0x127] == 0xFF) {
            continue;
        }
        if ((*(u16 *) (self + 0x2F8) & 7) == 5 && o[0x127] != 0xFF) {
            continue;
        }
        dx = *(f32 *) (self + 0x14) - *(f32 *) (o + 0x14);
        dz = *(f32 *) (self + 0x1C) - *(f32 *) (o + 0x1C);
        dy = *(f32 *) (self + 0x18) - *(f32 *) (o + 0x18);
        d2 = dx * dx + dz * dz + dy * dy;
        if (self[0x222] == i && (self[0x223] == 1 || self[0x223] == 0xC)) {
            d2 = 0.0f;
        }
        if (!(d2 < range2 && d2 < *best) && prefer != o[4]) {
            continue;
        }
        if (look_point_in_joint_range(id, j1, j2, *(s16 *) (o + 0x1A4), *(s16 *) (o + 0x1AA), *(s16 *) (o + 0x1A8), out, lim,
                          force, mode) != 0) {
            *best = d2;
            found = i;
            if (prefer == o[4]) {
                break;
            }
        }
    }
    if (found != -1) {
        return ((u8 *) &D_800CC2D0[found])[0x13B] + 1;
    }
    out[0] = out[1] = out[2] = -99999.0f;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_search_nearest_object.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800989F8;
/* was func_15038758 */
void look_angles_to_point(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f0;

    switch (arg5) {                                 /* irregular */
    case 0:
        *arg0 = math_atan2f(arg2, arg4);
        var_f0 = math_atan2f(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
block_9:
        *arg1 = var_f0;
        break;
    case 1:
        *arg0 = math_atan2f(-arg4, arg2);
        var_f0 = math_atan2f(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 2:
        *arg0 = math_atan2f(arg4, -arg2);
        var_f0 = math_atan2f(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 3:
        *arg0 = math_atan2f(arg4, -arg3);
        var_f0 = math_atan2f(-arg2, sqrtf((arg3 * arg3) + (arg4 * arg4)));
        goto block_9;
    }
    *arg0 *= D_800989F8;
    *arg1 *= D_800989F8;
    temp_f0 = *arg0;
    if (temp_f0 > 180.0f) {
        *arg0 = temp_f0 - 360.0f;
    }
    temp_f0_2 = *arg1;
    if (temp_f0_2 > 180.0f) {
    s32 pad;
        *arg1 = temp_f0_2 - 360.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_angles_to_point.s")
#endif
#ifdef NON_MATCHING
/* P76: per-object look state (object +0x324, look_record_alloc: 0x48 bytes), three slots (D_800C441A) */
typedef struct {
    f32 yaw[3];       /* 0x00: current angles (degrees), -99999 = unset */
    f32 pitch[3];     /* 0x0C */
    f32 yawVel[3];    /* 0x18: per-frame steps */
    f32 pitchVel[3];  /* 0x24 */
    u8 hold[3];       /* 0x30: frames the last target is still held (40 while there is one) */
    u8 fade[3];       /* 0x33: blend frames (10 = start of a blend toward / away from the target) */
    u8 flag4[3];      /* 0x36: the object's +0x2FB & 4 of the previous call */
    u8 pad39;
    s16 yawOfs[3];    /* 0x3A: extra angles, decay by D_800BE9E4 * 10 per call */
    s16 pitchOfs[3];  /* 0x40 */
    u8 pad46[2];
} LookTrack;
extern s32 D_800C43F0;      /* f32 x, y, z: default aim point */
extern u8 D_800BEE2C;
extern u8 D_800BEAC0;
extern u8 D_800BE9B4;
extern s32 D_800BE9E4;
extern u8 D_800C43FC;
extern f32 D_800C4400;
extern f32 D_800C4404;
extern f32 D_80098550[][4];  /* per limit set: yaw / pitch follow factors, yaw / pitch max steps */
s32 cutscene_player_look_target(f32 *, f32 *, f32 *, f32 *, s32, s32);
void look_angles_to_point(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void look_clamp_angles(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 arg5, f32 arg6, s32 arg7);
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void quat_align_hemisphere(f32 q1[4], f32 q2[4]);
void quat_from_mtx(f32 mtx[4][4], f32 arg1[4]);
void quat_slerp(f32 q1[4], f32 q2[4], f32 t, f32 result[4]);
void quat_to_mtx(f32 quat[4], f32 mtx[4][4]);

/*
 * P76: turn joint `joint` of object id toward target (x, y, z; all -99999 = no target). The angles (yaw, pitch,
 * degrees) of the target relative to the joint come from look_angles_to_point in the frame of joint `parent` (axis picks
 * the joint axis that should point at it, 0..3), unless cutscene_player_look_target supplies fixed angles. Look state slot
 * `slot` of the object's LookTrack (+0x324) follows them: with a blend running (fade / hold) by the factors of
 * D_80098550[limits] scaled toward 1, else by per-frame velocity steps limited by its max steps. keepMask bit 0 / 1
 * keeps the new yaw / pitch (else the raw ones), wrap keeps yaw continuous across +-180 and skips look_clamp_angles
 * (look limits), postMul multiplies the rotation onto the joint matrix instead of replacing it, yawBias is taken off
 * the yaw. The rotation (yawOfs / pitchOfs added) is rotation matrix * parent's matrix; during a blend it is slerped
 * (quaternions) from the joint's current orientation by the fade factor and the column scales are kept. Also
 * sets the aim point D_800C43F0 (target pushed 100x out from the joint), the object +0x2CA byte angle (slot 0) and,
 * for fixed angles, D_800C43FC / D_800C4400 / D_800C4404. The 9th argument of the asm's look_clamp_angles calls (slot)
 * is not read by look_clamp_angles and is left out.
 */
/* was func_15038910 */
void look_turn_joint(s32 joint, s32 parent, f32 *target, s32 id, s32 lookArg, s32 limits, s32 slot, s32 keepMask,
                   s32 wrap, s32 postMul, s32 yawBias, s32 unused, s32 axis) {
    u8 *self;
    LookTrack *lt;
    f32 *mtx;
    f32 (*P)[4];
    f32 (*J)[4];
    f32 yaw, pitch, roll;
    f32 fixedYaw, fixedPitch;
    f32 rawYaw, rawPitch;
    f32 lim0, lim1;     /* look_clamp_angles outputs */
    f32 ax, ay, az;
    f32 d[3];
    f32 wx, wy, wz;
    s32 fixed;
    s32 noTarget;
    s32 flag4;
    s32 expired;
    s32 blend;          /* 0: steps, 1: hold blend, 2: fade blend */
    f32 t;
    f32 kYaw, kPitch, stepYaw, stepPitch;
    f32 dYaw, dPitch;
    f32 a, b;
    s32 n;
    s32 i, k;
    s32 step;
    s32 v;
    f32 len, inv;
    f32 scale[3];
    f32 rot1[4][4];
    f32 rot2[4][4];
    f32 rot[4][4];
    f32 res[4][4];
    f32 q1[4], q2[4], q[4];

    self = (u8 *) &D_800CC2D0[id];
    lt = *(LookTrack **) (self + 0x324);
    if (lt == NULL) {
        return;
    }
    yaw = pitch = roll = 0.0f;
    if (D_800C441A == 0) {
        self[0x2CA] = 0;
    }
    fixed = cutscene_player_look_target(&yaw, &pitch, &roll, target, id, 0);
    if (fixed) {
        fixedYaw = yaw;
        fixedPitch = pitch;
    }
    blend = 0;
    D_800C43FC = 0;
    lim1 = 0.0f;
    lim0 = 0.0f;
    noTarget = target[0] == -99999.0f && target[1] == -99999.0f && target[2] == -99999.0f;
    if (noTarget && !fixed && lt->hold[slot] == 0) {
        lt->yawVel[slot] = 0.0f;
        lt->pitchVel[slot] = 0.0f;
        lt->fade[slot] = 10;
        lt->yaw[slot] = -99999.0f;
        lt->pitch[slot] = -99999.0f;
        lt->yawOfs[slot] = 0;
        lt->pitchOfs[slot] = 0;
        return;
    }
    flag4 = self[0x2FB] & 4;
    if (!fixed && flag4) {
        if (lt->flag4[slot] == 0) {
            lt->fade[slot] = 10;
        }
        if (lt->fade[slot] == 0) {
            lt->yawVel[slot] = 0.0f;
            lt->pitchVel[slot] = 0.0f;
            lt->yaw[slot] = -99999.0f;
            lt->pitch[slot] = -99999.0f;
            lt->yawOfs[slot] = 0;
            lt->pitchOfs[slot] = 0;
            return;
        }
    }
    expired = FALSE;
    lt->flag4[slot] = flag4;
    if (lt->fade[slot] < 2 && lt->hold[slot] > 0) {
        n = lt->hold[slot];
        if (D_800BEAC0 == 0 && D_800BEE2C == 0) {
            n = --lt->hold[slot];
        }
        if (n == 0) {
            expired = TRUE;
        }
    }
    if (!noTarget) {
        n = lt->hold[slot];
        if (n != 0 && n < 10) {
            lt->fade[slot] = (100 - n * 10) / 10.0f;
            lt->hold[slot] = 0;
        }
    }

    ay = 0.0f;
    switch (axis) {
        case 0:
            ax = 0.0f;
            az = 1.0f;
            break;
        case 1:
            az = 0.0f;
            ax = 1.0f;
            break;
        case 2:
            az = 0.0f;
            ax = -1.0f;
            break;
        case 3:
            ax = 0.0f;
            az = 0.0f;
            ay = -1.0f;
            break;
    }
    mtx = *(f32 **) (self + 0x1D4);
    P = (f32 (*)[4]) (mtx + parent * 16);
    J = (f32 (*)[4]) (mtx + joint * 16);
    P[2][3] = P[1][3] = P[0][3] = 0.0f;
    J[2][3] = J[1][3] = J[0][3] = 0.0f;
    P[3][3] = 1.0f;
    J[3][3] = 1.0f;
    if (!fixed) {
        /* the joint's current axis direction, as angles in the parent's frame */
        wx = ax * J[0][0] + ay * J[1][0] + J[2][0] * az;
        wy = ax * J[0][1] + ay * J[1][1] + J[2][1] * az;
        wz = ax * J[0][2] + ay * J[1][2] + J[2][2] * az;
        look_angles_to_point(&yaw, &pitch, wx * P[0][0] + wy * P[0][1] + P[0][2] * wz,
                      wx * P[1][0] + wy * P[1][1] + P[1][2] * wz, wx * P[2][0] + wy * P[2][1] + P[2][2] * wz, axis);
    }
    if (yaw > 180.0f) {
        yaw -= 360.0f;
    }
    if (pitch > 180.0f) {
        pitch -= 360.0f;
    }
    if (lt->yaw[slot] == -99999.0f) {
        lt->yaw[slot] = yaw;
        lt->yawVel[slot] = 0.0f;
        lt->pitchVel[slot] = 0.0f;
        lt->pitch[slot] = pitch;
    }
    if (D_800C441A == 0) {
        self[0x2CA] = (s32) (yaw * 0.7111111f);
    }
    rawYaw = yaw;
    rawPitch = pitch;
    if ((expired && !fixed) || D_800BE9B4 != 0) {
        look_clamp_angles(lookArg, &yaw, &pitch, &lim1, &lim0, rawYaw, rawPitch, id);
        lt->yawVel[slot] = 0.0f;
        lt->pitchVel[slot] = 0.0f;
        lt->yaw[slot] = yaw;
        lt->fade[slot] = 10;
        lt->yaw[slot] = -99999.0f;
        lt->pitch[slot] = -99999.0f;
        return;
    }

    d[0] = target[0] - J[3][0];
    d[1] = target[1] - J[3][1];
    d[2] = target[2] - J[3][2];
    if (noTarget && !fixed) {
        yaw = rawYaw;
        pitch = rawPitch;
    } else {
        if (!fixed) {
            look_angles_to_point(&yaw, &pitch, d[0] * P[0][0] + d[1] * P[0][1] + P[0][2] * d[2],
                          d[0] * P[1][0] + d[1] * P[1][1] + P[1][2] * d[2],
                          d[0] * P[2][0] + d[1] * P[2][1] + P[2][2] * d[2], axis);
            if (yaw > 0.0f) {
                yaw -= yawBias;
            } else if (yaw < 0.0f) {
                yaw += yawBias;
            }
        } else {
            D_800C43FC = 1;
            D_800C4400 = yaw;
            D_800C4404 = pitch;
        }
        {
            u8 *ext = *(u8 **) ((u8 *) &D_800CC2D0[D_800C3E78] + 0x318);

            /* behind the player's sub-object: look at the mirrored point 20 up instead */
            if (ext != NULL && *(s32 *) (ext + 0x2C) == 0x100 && (yaw > 100.0f || yaw < -100.0f)) {
                d[0] = -d[0];
                d[1] = 20.0f - d[1];
                d[2] = -d[2];
                look_angles_to_point(&yaw, &pitch, d[0] * P[0][0] + d[1] * P[0][1] + P[0][2] * d[2],
                              d[0] * P[1][0] + d[1] * P[1][1] + P[1][2] * d[2],
                              d[0] * P[2][0] + d[1] * P[2][1] + P[2][2] * d[2], axis);
            }
        }
        ((f32 *) &D_800C43F0)[0] = d[0] * 100.0f + J[3][0];
        ((f32 *) &D_800C43F0)[1] = d[1] * 100.0f + J[3][1];
        ((f32 *) &D_800C43F0)[2] = d[2] * 100.0f + J[3][2];
        if (!wrap) {
            look_clamp_angles(lookArg, &yaw, &pitch, &lim1, &lim0, rawYaw, rawPitch, id);
        }
    }

    if (D_800BEAC0 == 0 && D_800BEE2C == 0) {
        kYaw = D_80098550[limits][0];
        kPitch = D_80098550[limits][1];
        stepYaw = D_80098550[limits][2];
        stepPitch = D_80098550[limits][3];
        if (D_800C35EA == 1) {
            stepYaw = stepPitch = 5.0f;
            kPitch = 1.0f;
            kYaw = kPitch;
        }
        if (lt->fade[slot] > 0) {
            t = (f32) (10 - lt->fade[slot]) / 10.0f;
            blend = 2;
            if (!flag4) {
                t = 1.0f - t;
            }
        } else {
            n = lt->hold[slot];
            if (n != 0 && n < 10) {
                t = (f32) (10 - n) / 10.0f;
                blend = 1;
            }
        }
        if (blend == 1) {
            kYaw += (1.0f - kYaw) * t;
            kPitch += (1.0f - kPitch) * t;
        }
        if (wrap) {
            if (yaw > 90.0f) {
                if (lt->yaw[slot] < -90.0f) {
                    lt->yaw[slot] += 360.0f;
                }
            } else if (yaw < -90.0f) {
                if (lt->yaw[slot] > 90.0f) {
                    lt->yaw[slot] -= 360.0f;
                }
            }
        }
        dYaw = (yaw - lt->yaw[slot]) * kYaw;
        dPitch = (pitch - lt->pitch[slot]) * kPitch;
        if (blend) {
            yaw = lt->yaw[slot] + dYaw;
            pitch = lt->pitch[slot] + dPitch;
        } else {
            if (fabsf(dYaw) < fabsf(lt->yawVel[slot]) + stepYaw) {
                lt->yawVel[slot] = dYaw;
            } else {
                lt->yawVel[slot] += stepYaw * (f32) ((dYaw < 0.0f) ? -1 : 1);
            }
            if (fabsf(dPitch) < fabsf(lt->pitchVel[slot]) + stepPitch) {
                lt->pitchVel[slot] = dPitch;
            } else {
                lt->pitchVel[slot] += stepPitch * (f32) ((dPitch < 0.0f) ? -1 : 1);
            }
            yaw = lt->yawVel[slot] + lt->yaw[slot];
            pitch = lt->pitchVel[slot] + lt->pitch[slot];
        }
        if (!wrap) {
            look_clamp_angles(lookArg, &yaw, &pitch, NULL, NULL, rawYaw, rawPitch, id);
        }
    } else {
        yaw = lt->yaw[slot];
        pitch = lt->pitch[slot];
    }
    if (!(keepMask & 1)) {
        yaw = rawYaw;
    }
    if (!(keepMask & 2)) {
        pitch = rawPitch;
    }
    if (fixed) {
        blend = 0;
        yaw = fixedYaw;
        pitch = fixedPitch;
    }
    if (D_800C441A == 0) {
        self[0x2CA] = (s32) (yaw * 0.7111111f);
    }

    a = lt->yawOfs[slot] + yaw;
    b = lt->pitchOfs[slot] + pitch;
    switch (axis) {
        case 0:
            mtxf_rotate_xyz_deg(rot1, 0.0f, 0.0f, roll);
            mtxf_rotate_xyz_deg(rot2, -b, a, 0.0f);
            break;
        case 1:
            mtxf_rotate_xyz_deg(rot1, 0.0f, 0.0f, b);
            mtxf_rotate_xyz_deg(rot2, roll, a, 0.0f);
            break;
        case 2:
            mtxf_rotate_xyz_deg(rot1, 0.0f, 0.0f, -b);
            mtxf_rotate_xyz_deg(rot2, roll, a, 0.0f);
            break;
        case 3:
            mtxf_rotate_xyz_deg(rot1, 0.0f, 0.0f, -b);
            mtxf_rotate_xyz_deg(rot2, -a, roll, 0.0f);
            break;
    }
    mtxf_mul(rot1, rot2, rot);
    mtxf_mul(rot, P, res);
    res[3][0] = J[3][0];    /* keep the joint's position */
    res[3][1] = J[3][1];
    res[3][2] = J[3][2];
    if (blend) {
        /* slerp from the joint's orientation (columns normalised by the row lengths) toward the new one */
        bcopy(J, rot1, sizeof(rot1));
        bcopy(res, rot2, sizeof(rot2));
        for (i = 0; i < 3; i++) {
            len = sqrtf(J[i][0] * J[i][0] + J[i][1] * J[i][1] + J[i][2] * J[i][2]);
            scale[i] = len;
            inv = 1.0f / len;
            for (k = 0; k < 3; k++) {
                rot1[k][i] = J[k][i] * inv;
            }
            len = sqrtf(res[i][0] * res[i][0] + res[i][1] * res[i][1] + res[i][2] * res[i][2]);
            inv = 1.0f / len;
            for (k = 0; k < 3; k++) {
                rot2[k][i] = res[k][i] * inv;
            }
        }
        quat_from_mtx(rot2, q1);
        quat_from_mtx(rot1, q2);
        quat_align_hemisphere(q1, q2);
        quat_slerp(q1, q2, t, q);
        quat_to_mtx(q, res);
    } else {
        scale[0] = scale[1] = scale[2] = 1.0f;
    }
    if (postMul) {
        mtxf_mul(rot, J, rot1);
        bcopy(rot1, J, sizeof(rot1));
    } else {
        bcopy(res, J, sizeof(res));
        if (blend) {
            for (i = 0; i < 3; i++) {
                if (scale[i] != 1.0f) {
                    J[0][i] *= scale[i];
                    J[1][i] *= scale[i];
                    J[2][i] *= scale[i];
                }
            }
        }
    }
    lt->yaw[slot] = yaw;
    lt->pitch[slot] = pitch;
    if (D_800BEAC0 == 0 && D_800BEE2C == 0 && lt->fade[slot] > 0) {
        lt->fade[slot]--;
    }
    if (!noTarget) {
        lt->hold[slot] = 40;
    }
    step = D_800BE9E4 * 10;
    v = lt->yawOfs[slot];
    if (step < ((v < 0) ? -v : v)) {
        lt->yawOfs[slot] = v - step * ((v < 0) ? -1 : 1);
    } else {
        lt->yawOfs[slot] = 0;
    }
    v = lt->pitchOfs[slot];
    if (step < ((v < 0) ? -v : v)) {
        lt->pitchOfs[slot] = v - step * ((v < 0) ? -1 : 1);
    } else {
        lt->pitchOfs[slot] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_turn_joint.s")
#endif

/* was func_15039D44 */
void *look_get_limits(s32 arg0, s32 arg1) {
    return &D_80098418[arg1];
}

#ifdef NON_MATCHING
/*
 * P71: limits of the look angles (*yaw, *pitch) of object id, set 0 of look_get_limits: f[0] / f[1] yaw max / min,
 * f[2] / f[3] pitch max / min, f[4] / f[5] yaw / pitch margins. Without a camera record (+0x318) or in camera
 * mode 0x100 both are clamped. Else an angle beyond its range by more than the margin resets to rest (restYaw /
 * restPitch; a reset yaw also resets the pitch and copies both to *outYaw / *outPitch); otherwise the incoming
 * angles go to *outYaw / *outPitch (when given) and are clamped.
 */
/* was func_15039D68 */
void look_clamp_default(f32 *yaw, f32 *pitch, f32 *outYaw, f32 *outPitch, f32 restYaw, f32 restPitch, s32 id) {
    u8 *cam = *(u8 **) ((u8 *) &D_800CC2D0[id] + 0x318);
    f32 *lim = look_get_limits(id, 0);

    if (cam != NULL && *(s32 *) (cam + 0x2C) != 0x100) {
        if (lim[0] + lim[4] < *yaw || *yaw < lim[1] - lim[4]) {
            *yaw = restYaw;
            *pitch = restPitch;
            if (outYaw != NULL) {
                *outYaw = *yaw;
                *outPitch = *pitch;
            }
            return;
        }
        if (outYaw != NULL) {
            *outYaw = *yaw;
            *outPitch = *pitch;
        }
        if (*yaw < lim[1]) {
            *yaw = lim[1];
        } else {
            *yaw = (lim[0] < *yaw) ? lim[0] : *yaw;
        }
        if (lim[2] + lim[5] < *pitch || *pitch < lim[3] - lim[5]) {
            *pitch = restPitch;
        } else if (*pitch < lim[3]) {
            *pitch = lim[3];
        } else {
            *pitch = (lim[2] < *pitch) ? lim[2] : *pitch;
        }
        return;
    }
    if (*yaw < lim[1]) {
        *yaw = lim[1];
    } else {
        *yaw = (lim[0] < *yaw) ? lim[0] : *yaw;
    }
    if (*pitch < lim[3]) {
        *pitch = lim[3];
    } else {
        *pitch = (lim[2] < *pitch) ? lim[2] : *pitch;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_clamp_default.s")
#endif

#ifdef NON_MATCHING
extern u8 D_800BE9B4;
extern u8 D_8009822C[];
extern u8 D_80098400[];
extern u16 *D_80084710[];

/*
 * P70: look-at record setup and the "no look" flag (bit 2 of +0x2FB), after obj_set_kind_look_flags.
 * With a look record (+0x324): object 0x53 in animation 0x15, or D_800BE9B4 set, resets the three look slots
 * (+0x30.. = 40, +0x33.. = 0, +0x36.. = 4). Then, for object ids with a list (D_8009822C[id] = list number + 1;
 * D_80098400 = list lengths, D_80084710 = u16 lists of +0x84 values), a listed +0x84 sets the flag.
 * Otherwise the flag is set in state 1 when the health is 0, or (in water and xz speed < 5) or +0x31C[0x197] != 0
 * or xz speed > 20; in the other states when the health is 0.
 */
/* was func_15039CC8 */
void look_record_setup(struct127 *obj) {
    u8 *rec = obj->unk324;
    s32 list;
    s32 n;
    s32 i;
    u16 *ids;

    if (rec == NULL) {
        return;
    }
    if ((obj->id == 0x53 && obj->unk84.uh == 0x15) || D_800BE9B4 != 0) {
        for (i = 0; i < 3; i++) {
            rec[0x30 + i] = 40;
            rec[0x33 + i] = 0;
            rec[0x36 + i] = 4;
        }
    }
    list = D_8009822C[obj->id];
    if (list == 0) {
        return;
    }
    list--;
    n = D_80098400[list];
    ids = D_80084710[list];
    for (i = 0; i < n; i++) {
        if (obj->unk84.uh == ids[i]) {
            obj->unk2FB |= 4;
            return;
        }
    }
    if (obj->interaction_state == 1) {
        if (obj->health == 0
            || (obj->in_water && obj->xz_velocity < 5.0f)
            || ((u8 *) obj->unk31C)[0x197] != 0
            || obj->xz_velocity > 20.0f) {
            obj->unk2FB |= 4;
        }
    } else if (obj->health == 0) {
        obj->unk2FB |= 4;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_record_setup.s")
#endif

#ifdef NON_MATCHING
void look_clamp_default(f32 *, f32 *, f32 *, f32 *, f32, f32, s32);

/* was func_1503A1C0 */
void look_clamp_angles(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 var_f2;
    f32 var_f2_2;
    u8 *temp_v0;

    if (arg0 == 0) {
        look_clamp_default(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return;
    }
    temp_v0 = look_get_limits(arg7, arg0);
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x10));
    temp_f0 = *arg1;
    if ((((*(f32 *)((u8 *)temp_v0 + 0)) + temp_f12) < temp_f0) || (var_f2 = (*(f32 *)((u8 *)temp_v0 + 4)), (temp_f0 < (var_f2 - temp_f12)))) {
        *arg1 = arg5;
        *arg2 = arg6;
        if (arg3 != NULL) {
            *arg3 = *arg1;
            *arg4 = *arg2;
        }
    } else {
        if (arg3 != NULL) {
            *arg3 = temp_f0;
            *arg4 = *arg2;
            var_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
        }
        if (*arg1 < var_f2) {

        } else {
            temp_f12_2 = (*(f32 *)((u8 *)temp_v0 + 0));
            if (temp_f12_2 < *arg1) {
                var_f2 = temp_f12_2;
            } else {
                var_f2 = *arg1;
            }
        }
        *arg1 = var_f2;
        temp_f12_3 = (*(f32 *)((u8 *)temp_v0 + 8));
        temp_f14 = (*(f32 *)((u8 *)temp_v0 + 0x14));
        temp_f0_2 = *arg2;
        if (((temp_f12_3 + temp_f14) < temp_f0_2) || (var_f2_2 = (*(f32 *)((u8 *)temp_v0 + 0xC)), (temp_f0_2 < (var_f2_2 - temp_f14)))) {
            *arg2 = arg6;
            return;
        }
        if (temp_f0_2 < var_f2_2) {

        } else if (temp_f12_3 < temp_f0_2) {
            var_f2_2 = temp_f12_3;
        } else {
            var_f2_2 = temp_f0_2;
        }
        *arg2 = var_f2_2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_clamp_angles.s")
#endif
#ifdef NON_MATCHING
s32 model_header_load(s32 arg0, s32 arg1);
s32 obj_collision_cylinder(struct127 *, s16 *, s16 *, s16 *); /* s32: P59 definition returns 0 */
/* obj_bounds_from_skeleton (P57, from the m2c draft): object bounds from the skeleton. With a skeleton (+0x1D4) and a model
 * header D_800D1C90[type] (model_header_load(type, 0) == 0): joint header+0x26's matrix rows scaled to the header
 * radii (+0x3A u8, +0 s16, +0x30 s8) * y scale +0x150 give the box +0x1A4..+0x1B6 (s16) and the direction bytes
 * +0x1B8..+0x1BA; without: from the position, obj_collision_cylinder's height and header +0 * y scale. */
/* was func_1503A37C */
void obj_bounds_from_skeleton(struct127 *arg0) {
    u8 *temp_v0_2;
    u8 temp_v0;
    u8 temp_t4;
    struct124 *temp_v1_2;
    struct124 *temp_v1;
    s16 var_t0;
    s16 temp_v1_3;
    s16 temp_v0_3;
    s16 temp_a0;
    f32 var_f8;
    f32 var_f2_4;
    f32 var_f2_3;
    f32 var_f2_2;
    f32 var_f2;
    f32 var_f16;
    f32 var_f14;
    f32 var_f12;
    f32 temp_f6;
    f32 temp_f2;
    f32 temp_f18_4;
    f32 temp_f18_3;
    f32 temp_f18_2;
    f32 temp_f18;
    f32 temp_f16_3;
    f32 temp_f16_2;
    f32 temp_f16;
    f32 temp_f14_3;
    f32 temp_f14_2;
    f32 temp_f14;
    f32 temp_f12_3;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 temp_f0_5;
    f32 temp_f0_4;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp28;
    s32 sp2C;
    s16 sp32;
    s16 sp34;
    s16 sp36;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
    f32 sp50;
    f32 sp54;

    temp_v0 = ((u8 *)arg0)[4];
    if (temp_v0 != 0xFF) {
        if (((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) && (D_800D1C90[temp_v0] != NULL)) {
            if (model_header_load(temp_v0, 0) == 0) {
                temp_v1 = D_800D1C90[((u8 *)arg0)[4]];
                sp28 = (*(f32 *)((u8 *)arg0 + 0x150));
                temp_t4 = (*(u8 *)((u8 *)temp_v1 + 0x3A));
                temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x1D4)) + ((*(u8 *)((u8 *)temp_v1 + 0x26)) << 6);
                var_f8 = (f32) temp_t4;
                if ((s32) temp_t4 < 0) {
                    var_f8 += 4294967296.0f;
                }
                temp_f6 = var_f8 * sp28;
                sp48 = temp_f6;
                if (temp_f6 != 0.0f) {
                    temp_f12 = (*(f32 *)((u8 *)temp_v0_2 + 0));
                    temp_f14 = (*(f32 *)((u8 *)temp_v0_2 + 4));
                    temp_f16 = (*(f32 *)((u8 *)temp_v0_2 + 8));
                    temp_f18 = (temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16);
                    var_f2 = temp_f18;
                    if (temp_f18 != 0.0f) {
                        var_f2 = sqrtf(temp_f18);
                    }
                    if (var_f2 != 0.0f) {
                        var_f2 = sp48 / var_f2;
                    }
                    sp54 = temp_f12 * var_f2;
                    sp50 = temp_f14 * var_f2;
                    sp4C = temp_f16 * var_f2;
                } else {
                    sp4C = 0.0f;
                    sp50 = 0.0f;
                    sp54 = 0.0f;
                }
                temp_f18_2 = (f32) (*(s16 *)((u8 *)temp_v1 + 0)) * sp28;
                if (temp_f18_2 != 0.0f) {
                    temp_f12_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x10));
                    temp_f14_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x14));
                    temp_f16_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x18));
                    temp_f0 = sqrtf((temp_f12_2 * temp_f12_2) + (temp_f14_2 * temp_f14_2) + (temp_f16_2 * temp_f16_2));
                    var_f2_2 = temp_f0;
                    if (temp_f0 != 0.0f) {
                        var_f2_2 = temp_f18_2 / temp_f0;
                    }
                    sp44 = temp_f12_2 * var_f2_2;
                    sp40 = temp_f14_2 * var_f2_2;
                    sp3C = temp_f16_2 * var_f2_2;
                } else {
                    sp3C = 0.0f;
                    sp40 = 0.0f;
                    sp44 = 0.0f;
                }
                temp_f12_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x20));
                temp_f14_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x24));
                temp_f16_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x28));
                temp_f18_3 = (f32) (*(s8 *)((u8 *)temp_v1 + 0x30)) * sp28;
                if (temp_f18_3 != 0.0f) {
                    temp_f0_2 = sqrtf((temp_f12_3 * temp_f12_3) + (temp_f14_3 * temp_f14_3) + (temp_f16_3 * temp_f16_3));
                    var_f2_3 = temp_f0_2;
                    if (temp_f0_2 != 0.0f) {
                        var_f2_3 = temp_f18_3 / temp_f0_2;
                    }
                    temp_f0_3 = 127.0f / temp_f18_3;
                    var_f12 = temp_f12_3 * var_f2_3;
                    var_f14 = temp_f14_3 * var_f2_3;
                    var_f16 = temp_f16_3 * var_f2_3;
                    ((u8 *)arg0)[0x1B8] = (u8) (s32) (var_f12 * temp_f0_3);
                    ((u8 *)arg0)[0x1B9] = (u8) (s32) (var_f14 * temp_f0_3);
                    ((u8 *)arg0)[0x1BA] = (u8) (s32) (var_f16 * temp_f0_3);
                } else {
                    temp_f0_4 = sqrtf((temp_f12_3 * temp_f12_3) + (temp_f14_3 * temp_f14_3) + (temp_f16_3 * temp_f16_3));
                    var_f2_4 = temp_f0_4;
                    if (temp_f0_4 != 0.0f) {
                        var_f2_4 = 127.0f / temp_f0_4;
                    }
                    var_f14 = 0.0f;
                    var_f12 = 0.0f;
                    var_f16 = 0.0f;
                    ((u8 *)arg0)[0x1B8] = (u8) (s32) (temp_f12_3 * var_f2_4);
                    ((u8 *)arg0)[0x1B9] = (u8) (s32) (temp_f14_3 * var_f2_4);
                    ((u8 *)arg0)[0x1BA] = (u8) (s32) (temp_f16_3 * var_f2_4);
                }
                (*(s16 *)((u8 *)arg0 + 0x1A4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x30)) + var_f12);
                (*(s16 *)((u8 *)arg0 + 0x1A6)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x34)) + var_f14);
                (*(s16 *)((u8 *)arg0 + 0x1A8)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) + var_f16);
                temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A4));
                (*(s16 *)((u8 *)arg0 + 0x1AA)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x34)) + sp40);
                temp_f18_4 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A6));
                (*(s16 *)((u8 *)arg0 + 0x1AC)) = (s16) (s32) (temp_f2 + sp54 + sp44);
                temp_f0_5 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A8));
                (*(s16 *)((u8 *)arg0 + 0x1AE)) = (s16) (s32) (temp_f18_4 + sp50 + sp40);
                (*(s16 *)((u8 *)arg0 + 0x1B0)) = (s16) (s32) (temp_f0_5 + sp4C + sp3C);
                (*(s16 *)((u8 *)arg0 + 0x1B2)) = (s16) (s32) ((temp_f2 - sp54) + sp44);
                (*(s16 *)((u8 *)arg0 + 0x1B4)) = (s16) (s32) ((temp_f18_4 - sp50) + sp40);
                (*(s16 *)((u8 *)arg0 + 0x1B6)) = (s16) (s32) ((temp_f0_5 - sp4C) + sp3C);
            }
        } else {
            temp_v1_2 = D_800D1C90[temp_v0];
            if (temp_v1_2 != NULL) {
                var_t0 = *(s16 *)temp_v1_2;
            } else {
                var_t0 = 0;
            }
            sp2C = (s32) var_t0;
            obj_collision_cylinder(arg0, &sp36, &sp34, &sp32);
            (*(s16 *)((u8 *)arg0 + 0x1A4)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14));
            temp_v0_3 = (*(s16 *)((u8 *)arg0 + 0x1A4));
            ((u8 *)arg0)[0x2CA] = 0;
            (*(s16 *)((u8 *)arg0 + 0x1AC)) = (s16) temp_v0_3;
            (*(s16 *)((u8 *)arg0 + 0x1B2)) = (s16) temp_v0_3;
            (*(s16 *)((u8 *)arg0 + 0x1A6)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x18)) + (f32) ((s32) (sp36 * 7) / 8));
            (*(s16 *)((u8 *)arg0 + 0x1A8)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C));
            temp_a0 = (*(s16 *)((u8 *)arg0 + 0x1A8));
            (*(s16 *)((u8 *)arg0 + 0x1B0)) = (s16) temp_a0;
            (*(s16 *)((u8 *)arg0 + 0x1B6)) = (s16) temp_a0;
            (*(s16 *)((u8 *)arg0 + 0x1AA)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x1A6)) + ((f32) sp2C * (*(f32 *)((u8 *)arg0 + 0x150))));
            temp_v1_3 = (*(s16 *)((u8 *)arg0 + 0x1AA));
            (*(s16 *)((u8 *)arg0 + 0x1AE)) = (s16) temp_v1_3;
            (*(s16 *)((u8 *)arg0 + 0x1B4)) = (s16) temp_v1_3;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/obj_bounds_from_skeleton.s")
#endif

/* was func_1503A8FC */
void obj_cb_pin_joint1_position(void) {
    u8 *p;
    p = (u8 *)D_800CC2D0[D_800C3E78].unk1D4 + 0x40;
    *(f32 *)(p + 0x30) = *(f32 *)((u8 *)&D_800CC2D0[D_800C3E78] + 0x174);
    *(f32 *)(p + 0x34) = D_800CC2D0[D_800C3E78].y_position;
    *(f32 *)(p + 0x38) = *(f32 *)((u8 *)&D_800CC2D0[D_800C3E78] + 0x178);
}

#ifdef NON_MATCHING
#define OBJ_U8(obj, off) (*(u8 *) ((u8 *) (obj) + (off)))
extern u8 D_800C441A;
extern u8 D_80084794[];
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/*
 * P70: per-frame joint callback of object 0x22 (D_800CC2D0[D_800C3E78]): scales joint D_80084794[n] (n = the
 * call counter D_800C441A of this frame) by f = 1 + +0x20A / 64 in x and z on the first call, by 1 / f on the
 * later ones, keeping the joint's translation, then counts the call.
 */
/* was func_1503A968 */
void obj22_cb_scale_joint(void) {
    struct127 *obj = &D_800CC2D0[D_800C3E78];
    f32 (*m)[4];
    f32 tmp[4][4];
    f32 out[4][4];
    f32 pos[3];
    f32 f;
    union {
        f32 f;
        s32 bits;
    } sx, sy, sz; /* functions.h declares mtxf_scale (scale matrix) with s32 arguments: f32 bit patterns */

    if (obj->id != 0x22) {
        return;
    }
    f = (f32) OBJ_U8(obj, 0x20A) * 0.015625f + 1.0f;
    if (D_800C441A == 0) {
        sx.f = f;
        sy.f = 1.0f;
        sz.f = f;
    } else {
        sy.f = 1.0f;
        sx.f = 1.0f / f;
        sz.f = 1.0f / f;
    }
    m = (f32 (*)[4]) ((u8 *) obj->unk1D4 + D_80084794[D_800C441A] * 0x40);
    pos[0] = m[3][0];
    m[3][3] = 1.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    pos[1] = m[3][1];
    pos[2] = m[3][2];
    guMtxIdentF(tmp);
    mtxf_scale(tmp, sx.bits, sy.bits, sz.bits);
    mtxf_mul(m, tmp, out);
    bcopy(out, m, 0x40);
    m[3][0] = pos[0];
    m[3][1] = pos[1];
    m[3][2] = pos[2];
    D_800C441A++;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/obj22_cb_scale_joint.s")
#endif

void look_head_body_by_kind(void);
void obj22_cb_scale_joint(void);
extern u8 D_800C441A;

/* was func_1503AAE0 */
void look_joint_cb_combined(void) {
    s32 sp1C;

    sp1C = D_800C441A;
    D_800C441A = 0;
    look_head_body_by_kind();
    D_800C441A = sp1C;
    obj22_cb_scale_joint();
}

#ifdef NON_MATCHING
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
s32 cutscene_player_look_limits(f32 *, f32 *, s32, s32);
f32 math_cos_u8(u8);
u8 *attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);

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
 * D_800C43F0; others ask look_find_target for the target in D_800C4408). The joint matrix is made affine; while the
 * timer +0x282 runs, mode +0x276 animates the angles (0: circling offsets, 1: growing offsets, 2: aim at sub-model
 * 0x2B's point, 3: aim at joint +0x278, 4: nodding for model 0x26, 5: scaled offsets, 6: fixed pose); otherwise
 * the angles come from the target in joint space (atan2, in degrees), cutscene_player_look_limits may override them, they are
 * clamped (yaw +-45, pitch -15..30), scaled by the per-id limits D_800D1C90[id] +0x2C..+0x2F and approached by
 * 8 (or 4 without target) per call in +0x27A..+0x280. UNVERIFIED parts: see P65.md.
 */
/* was func_1503AB20 */
void look_aim_head_eyes(struct127 *obj) {
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
        look_find_target(D_800C4408, jointNo, jointNo, obj - D_800CC2D0, 90.0f, lookFlags, 0);
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
                s = math_sin_u8(a & 0xFF);
                c = math_cos_u8(a & 0xFF);
                LOOK_OFS(obj, 0) = s * k;
                LOOK_OFS(obj, 1) = c * k;
                s = math_sin_u8(b & 0xFF);
                c = math_cos_u8(b & 0xFF);
                LOOK_OFS(obj, 2) = s * k;
                LOOK_OFS(obj, 3) = c * k;
                break;
            case 1:
                if (LOOK_PHASE(obj) == 0) {
                    LOOK_PHASE(obj) = 1;
                    LOOK_OFS(obj, 3) += (u32) random_int() % 20;
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
                sub = attachment_find_by_slot((u8 *) obj, 0x2B, 0);
                if (sub != NULL) {
                    mtxs = *(u8 **) (sub + 0x48);
                    if (mtxs != NULL && ((s32 *) (mtxs + 0x3E8))[D_800BE9C0] != 0) {
                        vec_from_fixed_pos((vertex *) D_800C4408,
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
            yaw0 = math_atan2f(jx, jz) * 57.29578f;
            pitch0 = math_atan2f(jy, sqrtf(jx * jx + jz * jz)) * 57.29578f;
            if (yaw0 > 180.0f) {
                yaw0 -= 360.0f;
            }
            if (pitch0 > 180.0f) {
                pitch0 -= 360.0f;
            }
        }
    }

    if (LOOK_TIMER(obj) == 0 && cutscene_player_look_limits(&yaw0, &pitch0, index, 0) != 0) {
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
        } else if (pitch0 > 30.0f) {
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/look_aim_head_eyes.s")
#endif

s32 look_search_nearest_object(u8 *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800C43F0;

/* was func_1503B9F8 */
void look_find_target_simple(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    (*(f32 *)((u8 *)arg0 + 0)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 4)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 8)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 0)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 4)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 8)) = -99999.0f;
    if (look_get_fixed_target(arg3, arg0) == 0) {
        look_search_nearest_object(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    }
}
