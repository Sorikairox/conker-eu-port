extern u8 *D_8008CDEC[];

void func_1502C8F8(s32 arg0) {
    s32 lim;
    s16 a;
    s16 b;

    if (D_800BEAC0 == 0) {
        a = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60);
        b = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x62);
        if (D_800CC2D0[arg0].unk7 != 0) {
            lim = D_8008CDEC[func_1502C6AC(arg0)][4] << 8;
            a = a + b;
            if (a >= lim) {
                a = a - lim;
            } else if (a < 0) {
                a = a + lim;
            }
            *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60) = a;
        }
    }
}
