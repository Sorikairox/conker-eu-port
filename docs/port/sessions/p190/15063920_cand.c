/*
 * obj_hit_react_start: P190. For object record rec (D_800CC2D0, 0x32C bytes): its state block (+0x31C) gets
 * +0x78 = 0x3B and +0x11A = 2, animation 0x89 at speed 1 (func_15083568), rec +0x8A = 20, +0x89 = +0x83 = 0, and
 * func_1505E650(rec, 0x221, 1.0, 0, 0, 0, 0). The asm finds the block through the record index (rec - base) / 0x32C.
 */
void func_15063920(struct127 *rec) {
    s32 idx = ((u8 *)rec - (u8 *)D_800CC2D0) / 0x32C;
    u8 *state;

    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x78] = 0x3B;
    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x11A] = 2;
    func_15083568(rec, 0x89, 1.0f, 0);
    ((u8 *)rec)[0x8A] = 20;
    ((u8 *)rec)[0x89] = 0;
    ((u8 *)rec)[0x83] = 0;
    func_1505E650(rec, 0x221, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
