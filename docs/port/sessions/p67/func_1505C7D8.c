//HOIST s32 func_1505C7D8(struct127 *self, s32 skip);
extern f32 D_800998E4; /* pi / 180 */
extern struct127 D_800B30F0[];
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
f32 func_15143E64(f32 *vec);

/* P67: one attack descriptor (0x28 bytes) of the table func_1505C1A4 returns; rec->unkD0 - 1 is the active one. */
typedef struct {
    /* 0x00 */ u8  pad0[9];
    /* 0x09 */ u8  angle;   /* sphere: high byte of the angle offset from the facing; box: half length / 5 */
    /* 0x0A */ u8  dist;    /* sphere: distance in front (/ 0.125 scale); box: half width / 5 */
    /* 0x0B */ u8  padB;
    /* 0x0C */ s16 height;  /* height of the hit point (/ 0.25 scale) */
    /* 0x0E */ u8  radius;  /* sphere: radius / 4 (scale); box: s8 forward offset / 5 */
    /* 0x0F */ u8  padF[0x15];
    /* 0x24 */ u16 flags;   /* 0x80 box, 0x1000 may hit unk124, 0x2000 line of sight, 4 keep unk21C, 0x800 keep */
    /* 0x26 */ u8  pad26[2];
} AttackBox;

/* P67: attack hit test. Tests the active attack (sphere in front of the attacker, or a box in its frame) against
 * every live, vulnerable record except `skip`, optionally checks the line of sight (ray cast from the eyes), and
 * calls func_1505C1E4 for each hit. Returns func_1505C1E4's last result (0 = no hit). */
s32 func_1505C7D8(struct127 *self, s32 skip) {
    AttackBox *boxes;
    AttackBox *box;
    struct127 *target;
    s32 cur;
    s32 i;
    s32 count;
    s32 hits = 0;
    f32 hitX = 0.0f; /* the asm leaves these unset in box mode (reads its stack slot) */
    f32 hitY;
    f32 hitZ = 0.0f;
    f32 radius = 0.0f;
    f32 dx, dy, dz, ofs;
    f32 dist, limit;

    if (self->unk114 < 254.0f) {
        self->unk114 -= D_800D1550[0];
    }
    if (self->unk114 < 0.0f) {
        self->unkD0 = 0;
        return 0;
    }
    if (D_800C35EA == 1) {
        return 0;
    }
    skip = (skip & 0x7F) + 1;
    cur = self->unkD0 - 1;
    boxes = (AttackBox *)func_1505C1A4(self);
    box = &boxes[cur];

    /* the hit point: sphere centre in front of the attacker */
    if (box->flags & 0x80) {
        hitY = self->y_position;
    } else {
        func_1505A184(((box->angle << 8) + self->unk7A) & 0xFFFF, box->dist * (self->xz_scale / 0.125f), 0.0f,
                      &hitX, &hitZ, &hitY);
        hitX += self->x_position;
        hitY += self->y_position;
        hitZ += self->z_position;
        radius = box->radius;
        radius *= self->xz_scale * 4.0f;
    }
    hitY += box->height * (self->y_scale / 0.25f);

    count = (self->unkF8 & 0x100) ? 4 : 26;
    for (i = 1; i < count; i++) {
        target = &D_800CC2D0[i - 1];
        if (target->interaction_state == 0 || i == skip || target->health == 0 || target->immune != 0) {
            continue;
        }
        box = &boxes[cur];
        if (i == self->unk124 && !(box->flags & 0x1000)) {
            continue;
        }
        if (box->flags & 0x80) {
            /* box: target position in the attacker's frame (forward / side / up) */
            f32 angle, s, c, fwd, side, halfY, halfF, halfS;

            dx = target->x_position - self->x_position;
            dz = target->z_position - self->z_position;
            if (target->unkD8 != 0 || target->unkDA != 0) {
                dx += func_1505D34C(target->unk40, target->unkDA, target->unkD8, 1.0f, &ofs);
                dz += ofs;
            }
            angle = -((self->unk40 - 90.0f) * D_800998E4);
            s = func_150AD780(angle);
            c = func_150AD78C(angle);
            fwd = (dx * s + dz * c) - (s16)((s8)box->radius * 5) * self->xz_scale;
            side = -dx * c + dz * s;
            dy = hitY - (target->y_position + target->unkD6);
            halfY = target->unkD4 + 25.0f;
            halfF = box->angle * 5 * self->xz_scale + target->unkD2;
            halfS = box->dist * 5 * self->xz_scale + target->unkD2;
            if (!(-halfY < dy && dy < halfY && -halfF < fwd && fwd < halfF && -halfS < side && side < halfS)) {
                continue;
            }
        } else {
            /* sphere against the target's ellipsoid (radius unkD2, half height unkD4) */
            f32 r, h, k;

            dx = hitX - target->x_position;
            dz = hitZ - target->z_position;
            if (target->unkD8 != 0 || target->unkDA != 0) {
                dx -= func_1505D34C(target->unk40, target->unkDA, target->unkD8, 1.0f, &ofs);
                dz -= ofs;
            }
            dy = hitY - (target->y_position + target->unkD6);
            h = target->unkD4;
            r = target->unkD2;
            if (h == 0.0f) {
                continue;
            }
            limit = (r + radius) * (r + radius);
            k = h / (radius + h);
            dy *= (r / h) * k + (1.0f - k);
            dist = dx * dx + dy * dy + dz * dz;
            if (!(dist < limit)) {
                continue;
            }
        }

        if ((box->flags & 0x2000) && i != self->unk13D) {
            /* line of sight: ray from the attacker's eyes to the target's middle */
            f32 eye[3];
            f32 ray[3];
            f32 hx, hy, hz, t;
            f32 aim;
            s16 eyeH;

            if (self->unk2F4 != NULL) {
                eye[0] = ((f32 *)self->unk2F4)[0];
                eye[1] = ((f32 *)self->unk2F4)[1];
                eye[2] = ((f32 *)self->unk2F4)[2];
            } else {
                func_1507C7C0(self, &eyeH, NULL, NULL);
                eye[0] = self->x_position;
                eye[1] = self->y_position + (eyeH >> 1);
                eye[2] = self->z_position;
            }
            if (target->unk31C != NULL) {
                aim = (s16)target->unk31C->unk114 * 0.5f;
            } else {
                aim = 20.0f;
            }
            ray[0] = target->x_position - eye[0];
            ray[1] = (aim + target->y_position) - eye[1];
            ray[2] = target->z_position - eye[2];
            if (func_150ACEA0(eye[0], eye[1], eye[2], ray[0], ray[1], ray[2], 0, 0, &hx, &hy, &hz, &t, 0, 0, 0.0f) != 0
                && t < func_15143E64(ray)) {
                continue; /* blocked */
            }
        }

        D_800CC2C0 = hitX;
        D_800CC2C4 = hitY;
        D_800CC2C8 = hitZ;
        hits = func_1505C1E4(self, target, boxes, cur, i, hits, 15);
        cur = self->unkD0 - 1;
    }

    if (hits != 0) {
        box = &boxes[cur];
        if (D_800B30F0[self->unk108].interaction_state == 1 && self->unk254 != 0) {
            self->unk232 = self->unk254;
            self->unk218 = NULL;
        }
        if (!(box->flags & 4)) {
            self->unk21C = 0;
        }
        if (!(box->flags & 0x800)) {
            self->unkD0 = 0;
        }
    }
    return hits;
}
