/* P222: readable C for func_1506401C (game_eu_90F50, 145 words). */
// object_find_held: returns the first live object (word +0 != 0) of kind `kind` (+0x4) whose holder byte +0x65 is
// owner's slot + 1, or NULL. Scans all 25 objects of D_800CC2D0 (the asm peels slot 0).
struct127 *func_1506401C(struct127 *owner, s32 kind) {
    struct127 *o;
    s32 i;

    for (i = 0, o = D_800CC2D0; i < 25; i++, o++) {
        if (*(s32 *) o != 0 && kind == *((u8 *) o + 4) && (owner - D_800CC2D0) + 1 == *((u8 *) o + 0x65)) {
            return o;
        }
    }
    return NULL;
}
