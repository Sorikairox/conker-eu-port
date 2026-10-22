extern u8 D_800C3970[];

/* Adds `id` to sequence slot `slot`'s id list (D_800C3970, 30 bytes per slot, count D_800C396A[slot]) unless it
 * is already there. Returns i + 1 for an id found at index i, else the old count (the loop counter, as the
 * original). The list is not bounded. */
s32 func_150226E8(u8 id, s32 slot) {
    u8 *list = &D_800C3970[slot * 30];
    s32 count = D_800C396A[slot];
    s32 i = 0;

    while (i < count) {
        i++;
        if (list[i - 1] == id) {
            return i;
        }
    }
    list[count] = id;
    D_800C396A[slot] = count + 1;
    return i;
}
