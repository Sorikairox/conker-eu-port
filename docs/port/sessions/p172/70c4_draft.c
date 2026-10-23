// level_entry_data_load: allocates and clears the per-entry block pointers D_800D2104 and kind bytes D_800D2528 for
// the D_800D2520 setup entries; each player slot (i < D_8008FD8C) gets a zeroed 16-byte block of kind 2. Then the
// level's asset (2, 0x10, level) gives 8-byte records {offset, kind} for the entries from D_800D2521 on: a record
// with a non-zero offset sets the entry's kind (low byte) and its block = asset + offset.
void func_150170C4(s32 level) {
    u8 *asset = NULL;
    u32 *rec;
    s32 n = D_800D2520;
    s32 i;
    u8 **blocks;

    D_800D2104 = allocate_memory(n * 4, 1, 0, 0);
    D_800D2528 = allocate_memory(n, 1, 0, 0);
    bzero(D_800D2104, n * 4);
    bzero(D_800D2528, n);
    for (i = 0; i < D_8008FD8C; i++) {
        blocks = (u8 **) D_800D2104;
        blocks[i] = allocate_memory(0x10, 1, 2, 0);
        bzero(((u8 **) D_800D2104)[i], 0x10);
        D_800D2528[i] = 2;
    }
    if (func_1502B7F0((s32 *) &asset, 2, 0x10, level) == 0) {
        return;
    }
    for (i = D_800D2521; i < D_800D2520; i++) {
        rec = (u32 *) (asset + (i - D_800D2521) * 8);
        if (rec[0] != 0) {
            D_800D2528[i] = rec[1];
            ((u8 **) D_800D2104)[i] = asset + rec[0];
        }
    }
}
