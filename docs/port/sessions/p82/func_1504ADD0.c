/* Per-frame pass over the 25 object records outside cutscenes (D_800C35EA != 1): sets the current object
 * (D_800C3E78 index, D_800D154C pointer), its controller (D_800CC6A4: pad i of D_800BE728 for the first four
 * players, a zeroed 6-byte pad otherwise; only for i < D_8008FD8C) and runs func_150EDAF8 for objects 0x28 / 0x77.
 * As in the asm, the zeroed pad is a local of this function (D_800CC6A4 keeps pointing at it afterwards). */
void func_1504ADD0(void) {
    u8 pad[8];
    struct127 *obj;
    s32 i;

    if (D_800C35EA == 1) {
        return;
    }
    for (i = 0; i < 25; i++) {
        obj = &D_800CC2D0[i];
        if (*(s32 *)obj == 0) {
            continue;
        }
        D_800C3E78 = i;
        D_800D154C = obj;
        if (i < D_8008FD8C) {
            if (i < 4) {
                D_800CC6A4 = (u8 *)((s32 *)D_800BE728[0])[i];
            } else {
                bzero(pad, 6);
                D_800CC6A4 = pad;
            }
        }
        if ((((u8 *)obj)[4] == 0x28) || (((u8 *)obj)[4] == 0x77)) {
            func_150EDAF8((u8 *)obj);
        }
    }
}
