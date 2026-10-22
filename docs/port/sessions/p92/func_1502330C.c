/* Camera actor of cutscene slot `slot`: of the slot's sound / event records D_800C3AA8[slot][i] (i < the actor
 * count D_800C3A5A[slot]) asks func_15023C60 (type 3) for the nearest event; the record it reports with the
 * smallest distance gives the actor (s16 at +2). Without one the first actor with entry type 1 (u16 at
 * D_800C3A10[slot] + i * 8), else 0. `pos` (the script position) is not read. */
s32 func_1502330C(s32 slot, s32 pos) {
    u8 *found;
    s32 best;
    s32 dist;
    s32 actor;
    s32 i;

    best = 99999;
    actor = -1;
    for (i = 0; i < D_800C3A5A[slot]; i++) {
        if (D_800C3AA8[slot][i] != 0) {
            found = NULL;
            dist = func_15023C60(D_800C3AA8[slot][i] + 0x18, 3, i, &found, 0, 0, 0, 0, 0, 0, slot);
            if (found != NULL && dist < best) {
                best = dist;
                actor = *(s16 *)(found + 2);
            }
        }
    }
    if (actor == -1) {
        actor = 0;
        for (i = 0; i < D_800C3A5A[slot]; i++) {
            if (*(u16 *)(D_800C3A10[slot] + i * 8) == 1) {
                actor = i;
                break;
            }
        }
    }
    return actor;
}
