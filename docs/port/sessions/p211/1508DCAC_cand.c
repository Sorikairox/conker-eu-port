extern s16 D_800876C0[];
extern s8 D_80087688[];
extern f32 D_8009DE5C;
extern s8 D_800E1000;
void func_1508EFEC(s32, s32, s32);
f32 func_150ADA68(void);

// rail_rival_pace: script command 14 (func_1509E3D4). Object `i` of D_800CC2D0 races towards the object in its rail
// slot +0x11C (copied to its record's +0x129). The distance band to it (0 far = beyond D_8009DE5C, 1 beyond 2000,
// 2 close) and the difficulty D_800E1000 pick a step limit from D_800876C0; once the slot's counter +0x29C passes it,
// the counter restarts (and when the target's bit 16 + target is set in the slot's mask +0x16C0, func_1508EFEC
// sends message 0x61). On a zero counter the record's boost flag +0x12A is set when 100 * random beats D_80087688.
// Returns the band while the counter runs, 0 otherwise: no event script reads command 14's result (P211 scan), the
// asm leaves the random helper's v0 there.
s32 func_1508DCAC(s32 i) {
    struct127 *obj = &D_800CC2D0[i];
    u8 *rail = (u8 *) D_800D27D0;
    s32 *target = (s32 *) (rail + 0x11C) + i;
    s32 *count = (s32 *) (rail + 0x29C) + i;
    struct127 *other;
    f32 dx;
    f32 dz;
    f32 d;
    s32 band;

    *((u8 *) obj->unk31C + 0x129) = *target;
    if (*target < 0) {
        return 0;
    }
    other = &D_800CC2D0[*target];
    dx = other->x_position - obj->x_position;
    dz = other->z_position - obj->z_position;
    d = sqrtf(dx * dx + dz * dz);
    if (D_8009DE5C < d) {
        band = 0;
    } else if (2000.0f < d) {
        band = 1;
    } else {
        band = 2;
    }
    if (D_800876C0[D_800E1000 * 3 + band] < *count) {
        *count = 0;
        if ((0x10000 << *target) & *(s32 *) ((u8 *) D_800D27D0 + i * 4 + 0x16C0)) {
            func_1508EFEC(i, 0x61, 0x2000);
        }
    }
    if (*count != 0) {
        return band;
    }
    *((u8 *) obj->unk31C + 0x12A) = 0;
    if (D_80087688[D_800E1000] < (s32) (func_150ADA68() * 100.0f)) {
        *((u8 *) obj->unk31C + 0x12A) = 1;
    }
    return 0;
}
