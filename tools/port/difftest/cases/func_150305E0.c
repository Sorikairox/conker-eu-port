/* P241 selftest: a candidate longer than the reference (8 words, matched C, no .s) that calls the function right
 * after it (func_15030600). The extra test reads D_800C3EE0 only; both paths make the same call. */
s32 func_15030600(u8 *arg0, s32 arg1, s32 arg2);
extern s32 D_800C3EE0;
void func_150305E0(s32 arg0, s32 arg1) {
    if (D_800C3EE0 == 0x5A5A1234) {
        func_15030600((u8 *) arg0, arg1, 0xFF);
        return;
    }
    func_15030600((u8 *) arg0, arg1, 0xFF);
}
