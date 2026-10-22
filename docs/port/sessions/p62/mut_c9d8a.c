void func_15083C3C(s32, s32, s32);
u8 func_15084E08(struct127 *);

/*
 * P62: model level of detail. For object i (not hidden by +0x1C9, not state 7) with +0x2C8 levels: pick a level from
 * the squared distance to the camera record D_800DBFF0[cam] (a pointer; +0x2F8 / +0x2FC / +0x300): < 500 -> 0, < 730 -> 1,
 * < 1500 -> 2, < 2000 -> 3, else 4; one level finer when slow (xz_velocity < 3). Overrides: func_15084E08's
 * code 0x5A at level 0, or no code while D_800BE616 is set, -> 1; D_800C35EA == 1 -> 0. Clamped to the last level.
 * A new level loads model ((u8 *)+0x2C4)[level] through func_15083C3C and is stored in +0x1C8.
 */
void func_1502C9D8(s32 i, s16 cam, s32 unused) {
    struct127 *obj = &D_800CC2D0[i];
    struct108 *view = &D_800DBFF0[cam];
    f32 near0 = 500.0f;
    f32 near1 = 731.0f;
    f32 near2 = 1500.0f;
    f32 near3 = 2000.0f;
    s32 last;
    s32 code;
    s32 level;
    f32 dx, dy, dz, d2;

    if (obj->unk1C9 != 0 || obj->unk5 == 7) {
        return;
    }
    last = obj->unk2C8 - 1;
    if (last == -1) {
        return;
    }
    code = func_15084E08(obj);
    dx = view->unk2F8 - obj->x_position;
    dy = view->unk2FC - obj->y_position;
    dz = view->unk300 - obj->z_position;
    d2 = dx * dx + dy * dy + dz * dz;
    if (d2 < near0 * near0) {
        level = 0;
    } else if (d2 < near1 * near1) {
        level = 1;
    } else if (d2 < near2 * near2) {
        level = 2;
    } else if (d2 < near3 * near3) {
        level = 3;
    } else {
        level = 4;
    }
    if (level >= 2 && obj->xz_velocity < 3.0f) {
        level--;
    }
    if (code != 0) {
        if (code == 0x5A && level == 0) {
            level = 1;
        }
    } else if (D_800BE616 != 0) {
        level = 1;
    }
    if (D_800C35EA == 1) {
        level = 0;
    }
    if (last < level) {
        level = last < 0 ? 0 : last;
    }
    if (level != -1 && level != obj->unk1C8) {
        func_15083C3C(i, ((u8 *)obj->unk2C4)[level], 0);
        obj->unk1C8 = level;
    }
}
