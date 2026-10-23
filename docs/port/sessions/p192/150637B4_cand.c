/*
 * obj_knockdown_start: for object record rec (D_800CC2D0, 0x32C bytes): its state block (+0x31C) gets +0x78 = 9,
 * animations 0x1D then 0x1E at speed 1 (func_15083568), rec +0x8A = 20, +0x89 = +0x83 = 0, the block's +0x24 timer
 * = 60 and +0x11A = 2, then func_1505E650(rec, 0x7F, 1.0, 0, 0, 0, 0). As func_15063920, the asm finds the block
 * through the record index (rec - base) / 0x32C.
 */
void func_150637B4(struct127 *rec) {
    s32 idx = ((u8 *)rec - (u8 *)D_800CC2D0) / 0x32C;
    u8 *state;

    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x78] = 9;
    func_15083568(rec, 0x1D, 1.0f, 0);
    func_15083568(rec, 0x1E, 1.0f, 0);
    ((u8 *)rec)[0x8A] = 20;
    ((u8 *)rec)[0x89] = 0;
    ((u8 *)rec)[0x83] = 0;
    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    *(s16 *)(state + 0x24) = 60;
    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x11A] = 2;
    func_1505E650(rec, 0x7F, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
