/* May cutscene slot `slot` be skipped (called by func_1501E220 for a playing slot)? Level 0x1D: once after a
 * pending request (D_80090124, cleared here), else only when slot 0's scene is 5 (then as below). Level 0x21:
 * button 0x1000 held (D_800BEB30) with D_8000030C == 1 and slot 0 past frame 250. Other levels: button 0x20,
 * no D_800C40BC, and either D_800D3260 or a skippable scene (func_1501D330 with the slot's scene number) that is
 * forced (D_800C40B9) or still has more than 25 frames to run (D_800C39D0 + 25 < D_eu_800C3A60). The second
 * argument is not read. */
s32 func_1501E0C8(s32 slot, u8 *unused) {
    s32 level = D_800BE9F0;

    if (level == 0x1D) {
        if (D_80090124 != 0) {
            D_80090124 = 0;
            return 1;
        }
        if (D_800C3A08 != 5) {
            return 0;
        }
    }
    if (level == 0x21) {
        if ((D_800BEB30 & 0x1000) && D_8000030C == 1 && D_800C39D0 >= 0xFB) {
            return 1;
        }
        return 0;
    }
    if (!(D_800BEB30 & 0x20)) {
        return 0;
    }
    if (D_800C40BC != 0) {
        return 0;
    }
    if (D_800D3260 != 0) {
        return 1;
    }
    if (func_1501D330(level, (&D_800C3A08)[slot]) == 0) {
        return 0;
    }
    if (D_800C40B9 != 0) {
        return 1;
    }
    if ((&D_800C39D0)[slot] + 25 < (&D_eu_800C3A60)[slot]) {
        return 1;
    }
    return 0;
}
