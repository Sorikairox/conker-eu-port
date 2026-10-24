/*
 * player_next_active: P190. Round-robin over the D_8008FD8C player records (D_800CC2D0) from the one after the
 * cursor D_800D27D0[0x1702]: returns the first record that is live (+0), has a state block (+0x31C) with +0x84 set
 * and whose bit in D_800D18A0 is clear (-1 if none); the cursor is left on the last record examined.
 */
s32 func_1508CE28(void) {
    s32 n = D_8008FD8C;
    s32 found = -1;
    s32 tries = 0;
    s32 i = D_800D27D0[0x1702] + 1;
    u8 *rec;
    u8 *state;

    for (;;) {
        i = (s8)i;
        if (i >= n) {
            i = 0;
        }
        rec = (u8 *)D_800CC2D0 + i * 0x32C;
        if (*(s32 *)rec != 0) {
            state = *(u8 **)(rec + 0x31C);
            if (state != NULL && state[0x84] != 0 && !(D_800D18A0 & (1 << i))) {
                tries = n;
                found = i;
            }
        }
        tries++;
        if (tries >= n) {
            break;
        }
        i++;
    }
    D_800D27D0[0x1702] = i;
    return found;
}
