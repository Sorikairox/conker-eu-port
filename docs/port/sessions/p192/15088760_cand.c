// player_place_gap: finds the other player whose place (+0x29) is `player`'s place + `delta` and returns the absolute
// track-progress gap to it (lap +0x24 * 16 + segment +8 * 16) << 8 | its index; 16 when there is none.
s32 func_15088760(s32 player, s32 delta) {
    struct_eu_80087640 *me;
    struct_eu_80087640 *other;
    s32 place;
    s32 gap;
    s32 i;

    if (D_80087640 == NULL) {
        return 16;
    }
    me = &D_80087640[player];
    place = *(s8 *)((u8 *)me + 0x29) + delta;
    for (i = 0, other = D_80087640; i < D_800D27B8; i++, other++) {
        if (place == *(s8 *)((u8 *)other + 0x29) && i != player) {
            gap = me->unk24 * 16 + (s32)(me->unk8 * 16.0f) - other->unk24 * 16 - (s32)(other->unk8 * 16.0f);
            if (gap < 0) {
                gap = -gap;
            }
            return (gap << 8) | i;
        }
    }
    return 16;
}
