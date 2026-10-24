#ifdef NON_MATCHING
// P231 (P230 implicit_scan): func_15131EC8 takes (f32 *, f32); the matching C below calls it without a prototype and
// passes the f32's bit pattern as an int (lands in a1 either way on N64, wrong type on the port). Same fix as
// func_150AFBC4 (game_eu_DCEF0, P230).
void func_15131D98(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void func_15131EC8(f32 *arg0, f32 arg1);
s32 func_151D52B4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8((f32 *)(arg0 + 0x58), *(f32 *)(p + 0xC));
    return 1;
}
#else
s32 func_151D52B4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}
#endif
