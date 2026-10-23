// save_slots_reset: marks the three save-slot summaries D_800BE818 empty (+8 = -1, +0xE = -1), clears the current slot
// D_800BE7FC / D_800BE7FE, sets D_80082F50, clears the 27 bytes at D_800D2E4C (pointer) and the 9 save bits
// D_800D2E60, and sets the four bytes D_800BE7F8[0..3] to -1. Mode 3 (menu) calls it on its first frame.
void func_15007778(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800BE818[i].unk8 = -1;
    }
    for (i = 0; i < 3; i++) {
        D_800BE818[i].unkE = -1;
    }
    D_800BE7FC = -1;
    D_800BE7FE = 0;
    D_80082F50 = 1;
    for (i = 0; i < 0x1B; i++) {
        ((u8 *) D_800D2E4C)[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        D_800D2E60[i] = 0;
    }
    D_800BE7F8[3] = -1;
    D_800BE7F8[2] = -1;
    D_800BE7F8[1] = -1;
    D_800BE7F8[0] = -1;
}
