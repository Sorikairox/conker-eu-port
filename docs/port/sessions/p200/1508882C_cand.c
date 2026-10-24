// rail_find_ahead: the nearest other racer in front of player `player`'s object along its rail record's track
// direction (+0xC / +0x10, reversed when `dir` >= 0): among the D_800D27B8 records whose player (+0x31) is not the
// object's own (obj[0x124] - 1) and, when the record's alt +0x2F is set, with the same alt, the one with the smallest
// positive distance (< 10000) from the plane through the player's position. Stores that record's +0 in `*t` and its
// alt in `*alt` and returns its object (D_800CC2D0 + +0x31); NULL when there is none or no records.
struct127 *func_1508882C(s32 player, s32 dir, f32 *t, s32 *alt) {
    struct_eu_80087640 *rec;
    struct_eu_80087640 *other;
    struct127 *obj;
    struct127 *found;
    f32 sign;
    f32 nx;
    f32 nz;
    f32 c;
    f32 d;
    f32 best;
    s8 self;
    s8 want;
    s8 id;
    s32 i;

    if (D_80087640 == NULL) {
        return NULL;
    }
    rec = &D_80087640[player];
    if (dir >= 0) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    nx = *(f32 *) ((u8 *) rec + 0xC) * sign;
    nz = *(f32 *) ((u8 *) rec + 0x10) * sign;
    obj = &D_800CC2D0[(s8) rec->unk31];
    want = ((u8 *) rec)[0x2F];
    self = ((u8 *) obj)[0x124] - 1;
    found = NULL;
    best = 10000.0f;
    c = -(nx * *(f32 *) ((u8 *) obj + 0x14) + nz * *(f32 *) ((u8 *) obj + 0x1C));
    for (i = 0; i < D_800D27B8; i++) {
        other = &D_80087640[i];
        id = other->unk31;
        if (self == id) {
            continue;
        }
        if (want != 0 && want != (s8) ((u8 *) other)[0x2F]) {
            continue;
        }
        obj = &D_800CC2D0[id];
        d = nx * *(f32 *) ((u8 *) obj + 0x14) + nz * *(f32 *) ((u8 *) obj + 0x1C) + c;
        if (0.0f < d && d < best) {
            best = d;
            *t = other->unk0;
            *alt = (s8) ((u8 *) other)[0x2F];
            found = &D_800CC2D0[(s8) other->unk31];
        }
    }
    return found;
}
