s32 func_150FD140(s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
extern s32 func_1000EC24;

void func_150FCFB0(void) {
    struct { s8 u44; s8 u45; s16 u46; s8 u48; s8 u49; s8 u4A; } sp;
    s32 var_s0;

    func_150FD140(0);
    func_150FD140(1);
    func_150FD140(2);
    func_1000FA64(0x2B8U, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, (u8 *)0x2D, 0, 0, 0);
    func_1000FA64(0x2B7U, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, NULL, 0, 0, 0);
    func_1000FA64(0x2B6U, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, (u8 *)0x5A, 0, 0, 0);
    var_s0 = 0;
    if ((D_80082FA0 + 1) > 0) {
        do {
            func_1516547C(4, var_s0 & 0xFF, 0, 0xFF, 1);
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
    sp.u44 = 1;
    sp.u46 = 0x64;
    sp.u49 = 0xF;
    sp.u48 = 8;
    sp.u4A = -1;
    func_151D8E18((structEU_151D8E18 *) &sp, 0, 0xFFU, 0);
}
