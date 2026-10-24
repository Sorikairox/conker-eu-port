/* P222: readable C for func_15083E90 (game_eu_AF2A0, 72 words); replaces the m2c-style NM body (goto loop). */
// object_find_by_id: returns the live object (word +0 != 0) of D_800CC2D0 whose id byte +0x3B is `id`, scanning all
// 26 slots (the asm peels slots 0 and 1 and unrolls the rest by 4); NULL for id 0 or when none matches.
struct127 *func_15083E90(u8 id) {
    struct127 *o;
    s32 i;

    if (id == 0) {
        return NULL;
    }
    for (i = 0, o = D_800CC2D0; i < 26; i++, o++) {
        if (o->interaction_state != 0 && id == o->unique_id) {
            return o;
        }
    }
    return NULL;
}
