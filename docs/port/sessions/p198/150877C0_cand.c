extern s8 D_800D27B0;
extern f32 D_800D27BC;
extern f32 D_800D27C0;
extern f32 D_800D27C4;
extern s8 D_800D27C9;
f32 func_15049AD0(s32 *, s32, f32);
f32 func_15049B94(s32 *, s32, f32, s32 *);
s32 func_15088E84(struct_eu_80087640 *, f32);
s32 func_150893AC(struct_eu_80087640 *, s32 *, s32 *, s32 *);
s32 func_1508849C(struct_eu_80087640 *, struct127 *, s32);
void func_15042D78(u8);

// rail_track_update: moves `player`'s rail record (D_80087640 + player * 0x84) along its spline to the point nearest
// the player object (D_800CC2D0 + rec[0x31]): the step +0 (start 0.5 when +0x30 is 0, else eased toward +4 by 1/8,
// clamped to +-0.06) is used, then up to 11 times the player's distance from the plane through the spline point
// (normal = the tangent, stored at +0xC / +0x10) is turned into a parameter step for func_15088E84 (halved when it
// grows). +0x14 gets the speed along the track ((previous - current distance) * 4 / frames). With +0x30 set it
// computes the camera point D_800D27BC / C0 / C4 on a copy moved 2 * `speed` ahead (human players: or 300 units
// behind player 0's yaw when `mode` is 0, written to the player's camera D_800D2104[obj[0x13F]] +8 / +A / +C, mode
// to obj +0x44, fov +0x20 by D_800D27B0); otherwise +0 becomes the step to the next point. Sets D_800D27C9 (rail
// cameras on), counts frames off-track in +0x1C, records state 2+ via func_1508849C (0xD) and, for player 0, ranks
// all D_800D27B8 records (score = t + segment, + 30000 - 1000 * place while +0x2A != 0x7F, - 10000 for the D_800D18A0
// players) and stores each record's place in +0x29.
void func_150877C0(s32 player, s32 mode, f32 speed) {
    struct_eu_80087640 *rec;
    u8 *r;
    u8 *obj;
    f32 px;
    f32 pz;
    f32 xs[4];
    f32 ys[4];
    f32 zs[4];
    f32 dx;
    f32 dz;
    f32 len;
    f32 seg;
    f32 sx;
    f32 sz;
    f32 c;
    f32 d;
    f32 prev;
    f32 ad;
    f32 gain;
    f32 step;
    f32 inv;
    s8 ok;
    s8 tries;
    s32 again;
    u8 copy[0x84];
    f32 score[16];
    s8 order[16];
    s32 n;
    s32 i;
    s32 sorted;
    f32 tf;
    s8 tb;

    tries = 0;
    if (D_80087640 == NULL) {
        return;
    }
    rec = &D_80087640[player];
    r = (u8 *) rec;
    obj = (u8 *) &D_800CC2D0[(s8) r[0x31]];
    px = *(f32 *) (obj + 0x14);
    pz = *(f32 *) (obj + 0x1C);
    D_800D27B0 = 0;
    if ((s8) r[0x30] == 0) {
        rec->unk0 = 0.5f;
    } else {
        step = (rec->unk4 - rec->unk0) * 0.125f;
        if (0.06f < step) {
            step = 0.06f;
        }
        if (step < -0.06f) {
            step = -0.06f;
        }
        rec->unk0 = rec->unk0 + step;
    }
    gain = 0.75f;
    ok = 1;
    prev = 10000.0f;
    do {
        again = 0;
        if (ok) {
            func_150893AC(rec, (s32 *) xs, (s32 *) ys, (s32 *) zs);
            dx = xs[2] - xs[1];
            dz = zs[2] - zs[1];
            seg = sqrtf(dx * dx + dz * dz);
        }
        sx = func_15049B94((s32 *) xs, 0, rec->unk8, (s32 *) &dx);
        sz = func_15049B94((s32 *) zs, 0, rec->unk8, (s32 *) &dz);
        inv = -1.0f / sqrtf(dx * dx + dz * dz);
        dx *= inv;
        dz *= inv;
        *(f32 *) (r + 0xC) = dx;
        *(f32 *) (r + 0x10) = dz;
        c = -(sx * dx + sz * dz);
        d = dx * px + dz * pz + c;
        if (d < -50.0f || 50.0f < d) {
            ad = d;
            if (d < 0.0f) {
                ad = -d;
            }
            if (prev < ad) {
                gain *= 0.5f;
            }
            prev = ad;
            again = 1;
            step = d * gain / seg;
            if (step < -0.5f) {
                step = -0.5f;
            }
            if (0.5f < step) {
                step = 0.5f;
            }
            ok = func_15088E84(rec, -step);
        }
        tries++;
        if (tries >= 11) {
            again = 0;
        }
    } while (again);

    func_15042D78(0x80);
    r[0x32] = r[0x33];
    r[0x33] = D_800BE9E4;
    rec->unk14 = ((*(f32 *) (obj + 0x2C) * dx + *(f32 *) (obj + 0x34) * dz + c) - d) * 4.0f / (s8) r[0x32];
    if ((s8) r[0x30] != 0) {
        bcopy(rec, copy, 0x84);
        func_15088E84((struct_eu_80087640 *) copy, speed + speed);
        func_150893AC((struct_eu_80087640 *) copy, (s32 *) xs, (s32 *) ys, (s32 *) zs);
        D_800D27BC = func_15049AD0((s32 *) xs, 0, ((struct_eu_80087640 *) copy)->unk8);
        D_800D27C0 = func_15049AD0((s32 *) ys, 0, ((struct_eu_80087640 *) copy)->unk8);
        D_800D27C4 = func_15049AD0((s32 *) zs, 0, ((struct_eu_80087640 *) copy)->unk8);
        if (player < D_800D27B8) {
            if (mode == 0) {
                // player 0's yaw (D_800CC2D0[0] +0x40) in degrees (Rare's 0.01745 for pi / 180)
                f32 ang = *(f32 *) ((u8 *) D_800CC2D0 + 0x40) * 0.01745;

                D_800D27BC = sinf(ang) * 300.0f + *(f32 *) (obj + 0x14);
                D_800D27C0 = *(f32 *) (obj + 0x18);
                D_800D27C4 = cosf(ang) * 300.0f + *(f32 *) (obj + 0x1C);
            }
            *(s16 *) ((u8 *) D_800D2104[obj[0x13F]] + 8) = D_800D27BC;
            *(s16 *) ((u8 *) D_800D2104[obj[0x13F]] + 0xA) = D_800D27C0;
            *(s16 *) ((u8 *) D_800D2104[obj[0x13F]] + 0xC) = D_800D27C4;
            *(f32 *) (obj + 0x44) = mode;
            if (D_800D27B0 == 1) {
                *(f32 *) (obj + 0x20) = 75.0f;
            } else if (D_800D27B0 == 2) {
                *(f32 *) (obj + 0x20) = 55.0f;
            } else if (D_800D27B0 == 3) {
                *(f32 *) (obj + 0x20) = 65.0f;
            }
            obj[0x21E] = 0;
        }
    } else {
        rec->unk0 = 0.0f;
        func_150893AC(rec, (s32 *) xs, (s32 *) ys, (s32 *) zs);
        sx = func_15049AD0((s32 *) xs, 0, rec->unk8);
        sz = func_15049AD0((s32 *) zs, 0, rec->unk8);
        rec->unk0 = 1.0f;
        func_150893AC(rec, (s32 *) xs, (s32 *) ys, (s32 *) zs);
        dx = func_15049AD0((s32 *) xs, 0, rec->unk8) - sx;
        dz = func_15049AD0((s32 *) zs, 0, rec->unk8) - sz;
        len = sqrtf(dx * dx + dz * dz);
        if (1.0f < len) {
            inv = 1.0f / len;
            dx *= inv;
            dz *= inv;
            rec->unk0 = ((dx * px + dz * pz) - (dx * sx + dz * sz)) * inv;
        } else {
            rec->unk0 = 0.0f;
        }
    }
    r[0x48] = mode;
    D_800D27C9 = 1;
    if ((s8) r[0x30] == 0 && r[0x48] != 0 && !(D_800D18A0 & (1 << (s8) r[0x31]))) {
        *(s32 *) (r + 0x1C) += D_800BE9E4;
    }
    if ((s8) r[0x30] >= 2 && (*(u8 **) (obj + 0x31C))[0x84] == 0) {
        func_1508849C(rec, (struct127 *) obj, 0xD);
    }
    if (player != 0) {
        return;
    }

    n = D_800D27B8;
    for (i = 0; i < n; i++) {
        order[i] = i;
        score[i] = D_80087640[i].unk8 + D_80087640[i].unk24;
        if ((s8) D_80087640[i].pad28[2] != 0x7F) {
            score[i] += 30000.0f - (s8) D_80087640[i].pad28[2] * 1000.0f;
        }
        if (D_800D18A0 & (1 << (s8) D_80087640[i].unk31)) {
            score[i] -= 10000.0f;
        }
    }
    do {
        sorted = 1;
        for (i = 0; i < n - 1; i++) {
            if (score[i] < score[i + 1]) {
                tb = order[i];
                order[i] = order[i + 1];
                order[i + 1] = tb;
                tf = score[i];
                score[i] = score[i + 1];
                score[i + 1] = tf;
                sorted = 0;
            }
        }
    } while (!sorted);
    if (n > 0) {
        for (i = 0; i < D_800D27B8; i++) {
            D_80087640[order[i]].pad28[1] = i + 1;
        }
    }
}
