// rail_state_reset: script command 10 (func_1509E3D4): marks the D_800D27D0 slots +0xEB0 free (-1, +0x10 of them)
// and resets the per-entry tables (+0xEA4 entries): +0xF70 = -1, +0xFF0 = 0, +0x10F0 = -1, +0x1070 = 1,
// +0x12F4 = 0. The counts are re-read through D_800D27D0 on every pass, the tables stay on the block it pointed to
// at entry. Returns what the asm leaves in v0 for the script runner: the end of the +0xF70 table, or the +0xEB0
// table when there are no entries (never 0).
s32 func_1508DE78(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 *slots = (s32 *) (rail + 0xEB0);
    s32 *link = (s32 *) (rail + 0xF70);
    s32 *count = (s32 *) (rail + 0xFF0);
    s32 *one = (s32 *) (rail + 0x1070);
    s32 *prev = (s32 *) (rail + 0x10F0);
    s32 *extra = (s32 *) (rail + 0x12F4);
    s32 i;

    for (i = 0; i < *(s32 *) ((u8 *) D_800D27D0 + 0x10); i++) {
        slots[i] = -1;
    }
    for (i = 0; i < *(s32 *) ((u8 *) D_800D27D0 + 0xEA4); i++) {
        link[i] = -1;
        count[i] = 0;
        prev[i] = -1;
        one[i] = 1;
        extra[i] = 0;
    }
    if (i > 0) {
        return (s32) &link[i];
    }
    return (s32) slots;
}
