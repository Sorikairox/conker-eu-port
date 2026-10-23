extern s32 D_800B1268[];  /* texture cache: expanded data per texture id */
void func_10004074(s16 *);  /* free (as the file's other callers) */

// texture_cache_release: drops one reference to texture id (D_800DA388[id]); when the last one goes and the
// texture is cached (D_800BC860[id] != 0), frees its data (and first the block its first word points to when
// D_800BC860[id] & 0x40) and empties the slot (D_800B1268[id] = -1, D_800BC860[id] = 0).
// s32 with three parameters for game_eu_6AA20.c's prototype (its only caller passes id, id, a u16 and ignores the
// result; the asm reads a0 only and leaves v0 undefined): returns 0. Verified as the void (s32 id) variant.
s32 func_1510DD2C(s32 id, s32 unused1, u16 unused2) {
    s8 state = D_800BC860[id];

    if (state == 0 || D_800DA388[id] == 0) {
        return 0;
    }
    if (--D_800DA388[id] != 0) {
        return 0;
    }
    if (state & 0x40) {
        func_10004074(*(s16 **) D_800B1268[id]);
    }
    func_10004074((s16 *) D_800B1268[id]);
    D_800B1268[id] = -1;
    D_800BC860[id] = 0;
    return 0;
}
