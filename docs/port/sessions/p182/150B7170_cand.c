// hud_box_reset: removes the old box object D_800D9CB4 (func_1516972C), creates a new one (func_151A5580(0, 0, 0xFF,
// 0, 0, D_800BEE08, 0, 0)), sets state D_800D9CB0 = 3 and clears the 10 words D_800D9CB8.
void func_150B7170(void) {
    s32 i;

    if (D_800D9CB4 != 0) {
        func_1516972C((struct102 *) D_800D9CB4);
    }
    D_800D9CB4 = (s32) func_151A5580(0, 0, 0xFF, 0, 0, D_800BEE08, 0, 0);
    D_800D9CB0 = 3;
    for (i = 0; i < 10; i++) {
        D_800D9CB8[i] = 0;
    }
}
