#ifdef NON_MATCHING
f32 func_15144528(f32 value, f32 range, f32 base);
// tank_track_record: entry 17 of D_8008A5DC (`s32 (*)(u8 *)`, result tested by the path updater). Once per frame
// (D_800BE9E4 > 0) records the owner object's (**(arg0 + 0x98)) position (+0x40..+0x48) as the path's new head
// point (also copied to +0x10, flag 4 of +0x1E set): ring of +0x25 points of 0x28 bytes at +0x94 with +0x0C speed
// (object +0x58), +0x10 = 1 / |velocity xz| (object +0x4C / +0x54; 1 when 0), +0x14 alpha 255, +0x18 texture t
// (owner +0x04, which then advances by speed * 21.85 wrapped at 8192 by func_15144528), +0x1C width 100,
// +0x20 / +0x24 side direction (-vz, vx) / |v|. The head +0x2E and count +0x2C advance; when the ring is full the
// current point +0x2D moves on. With 3+ points, the side direction of the point before the new one is smoothed to
// the normalised perpendicular of its two neighbours' directions (0 when shorter than 1e-4). Returns 1.
s32 func_151D1B80(u8 *arg0) {
    u8 *owner;
    u8 *points;
    u8 *obj;
    f32 *rec;
    f32 *mid;
    f32 *prev;
    f32 len;
    f32 ax;
    f32 az;
    f32 bx;
    f32 bz;
    f32 dx;
    f32 dz;
    f32 d2;
    f32 inv;
    s16 i;
    s16 j;

    if (D_800BE9E4 <= 0) {
        return 1;
    }
    owner = *(u8 **) (arg0 + 0x98);
    points = *(u8 **) (arg0 + 0x94);
    obj = *(u8 **) owner;
    *(s32 *) (arg0 + 0x10) = *(s32 *) (obj + 0x40);
    *(s32 *) (arg0 + 0x14) = *(s32 *) (obj + 0x44);
    *(s32 *) (arg0 + 0x18) = *(s32 *) (obj + 0x48);
    *(u16 *) (arg0 + 0x1E) |= 4;
    rec = (f32 *) (points + *(s8 *) (arg0 + 0x2E) * 0x28);
    ((s32 *) rec)[0] = *(s32 *) (arg0 + 0x10);
    ((s32 *) rec)[1] = *(s32 *) (arg0 + 0x14);
    ((s32 *) rec)[2] = *(s32 *) (arg0 + 0x18);
    rec[3] = *(f32 *) (obj + 0x58);
    len = sqrtf(*(f32 *) (obj + 0x4C) * *(f32 *) (obj + 0x4C) + *(f32 *) (obj + 0x54) * *(f32 *) (obj + 0x54));
    if (len == 0.0f) {
        rec[4] = 1.0f;
    } else {
        rec[4] = 1.0f / len;
    }
    rec[7] = 100.0f;
    ((u8 *) rec)[0x14] = 0xFF;
    rec[6] = *(f32 *) (owner + 4);
    *(f32 *) (owner + 4) = *(f32 *) (owner + 4) + rec[3] * 21.85f;
    *(f32 *) (owner + 4) = func_15144528(*(f32 *) (owner + 4), 8192.0f, 0.0f);
    if (len == 0.0f) {
        rec[8] = 0.0f;
        rec[9] = 0.0f;
    } else {
        rec[8] = -*(f32 *) (obj + 0x54) * rec[4];
        rec[9] = *(f32 *) (obj + 0x4C) * rec[4];
    }

    (*(s8 *) (arg0 + 0x2E))++;
    if (arg0[0x25] == *(s8 *) (arg0 + 0x2E)) {
        *(s8 *) (arg0 + 0x2E) = 0;
    }
    (*(s8 *) (arg0 + 0x2C))++;
    if (*(s8 *) (arg0 + 0x2D) == *(s8 *) (arg0 + 0x2E)) {
        (*(s8 *) (arg0 + 0x2D))++;
        if (arg0[0x25] == *(s8 *) (arg0 + 0x2D)) {
            *(s8 *) (arg0 + 0x2D) = 0;
        }
        (*(s8 *) (arg0 + 0x2C))--;
    }
    if (*(s8 *) (arg0 + 0x2C) < 3) {
        return 1;
    }

    /* i = the point before the new one, j = the one before i */
    i = *(s8 *) (arg0 + 0x2E) - 1;
    if (i < 0) {
        i = arg0[0x25] - 1;
    }
    i = i - 1;
    if (i < 0) {
        i = arg0[0x25] - 1;
    }
    j = i - 1;
    if (j < 0) {
        j = arg0[0x25] - 1;
    }
    if (rec[3] == 0.0f) {
        return 1;
    }
    mid = (f32 *) (points + i * 0x28);
    if (mid[3] == 0.0f) {
        return 1;
    }
    prev = (f32 *) (points + j * 0x28);
    ax = (rec[0] - mid[0]) * rec[4];
    az = (rec[2] - mid[2]) * rec[4];
    bx = (prev[0] - mid[0]) * mid[4];
    bz = (prev[2] - mid[2]) * mid[4];
    dx = -(az - bz);
    dz = ax - bx;
    d2 = dx * dx + dz * dz;
    if (1e-4f < d2) {
        inv = 1.0f / sqrtf(d2);
        mid[8] = dx * inv;
        mid[9] = dz * inv;
    } else {
        mid[8] = 0.0f;
        mid[9] = 0.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1B80.s")
#endif
