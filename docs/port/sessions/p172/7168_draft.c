extern u8 *D_80082F4C;
// save_data_reset: clears the save data D_800BE710 (0x68 bytes) and gives its ten records their defaults: bytes
// +1 / +2 / +3 / +4 = 3 / 10 / 2 / 1, +9 = 0 and per record (asm jump table jtbl_80095DB0) +5 = 3 (records 0, 8,
// 9), 5 (1, 2) or 20 (5, 7), record 5 also +2 = 0; records 3, 4, 6 keep +5 = 0. Takes no arguments (the C caller
// func_1500727C used to pass two that the asm never reads).
void func_15007168(void) {
    u8 *p;
    u8 *rec;
    s32 i;

    for (p = (u8 *) &D_800BE710; p < (u8 *) &D_800BE710 + 0x68; p++) {
        *p = 0;
    }
    for (i = 0; i < 10; i++) {
        rec = D_80082F4C + i * 10;
        rec[1] = 3;
        rec[3] = 2;
        rec[4] = 1;
        rec[2] = 10;
        switch (i) {
            case 0:
            case 8:
            case 9:
                rec[5] = 3;
                break;
            case 1:
            case 2:
                rec[5] = 5;
                break;
            case 5:
                rec[5] = 20;
                rec[2] = 0;
                break;
            case 7:
                rec[5] = 20;
                break;
        }
        rec[9] = 0;
    }
}
