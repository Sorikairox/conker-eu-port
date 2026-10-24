extern s8 D_800D27C8;

// player_face_track_side: turns the object (+0x76 yaw) a quarter turn (+0x3600 / +0x4A00) from the direction of
// player `player`'s track vector (+0x10 / +0xC, func_1505A630), the side picked by the track position +0 against 0.5
// (mirrored when D_800D27C8 is set). Returns that direction (0 without player records); the one caller ignores it.
s32 func_15088360(s32 player, struct127 *obj) {
    struct_eu_80087640 *rec;
    u16 dir;

    if (D_80087640 == NULL) {
        return 0;
    }
    rec = &D_80087640[player];
    dir = func_1505A630(*(f32 *)((u8 *)rec + 0x10), *(f32 *)((u8 *)rec + 0xC), 0);
    if (D_800D27C8 == 0) {
        if (rec->unk0 < 0.5f) {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x4A00;
        } else {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x3600;
        }
    } else {
        if (0.5f <= rec->unk0) {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x4A00;
        } else {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x3600;
        }
    }
    return dir;
}
