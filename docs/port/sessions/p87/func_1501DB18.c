/* Start of cutscene slot `slot`: scans the sound / event track (D_800C3AA8[slot][i] + 0x18) of every actor with
 * func_15023C60 (type 5) for the event codes 0x1E, 0x0E, 0x68, 0x44 (flags D_800C40B9, D_800C40BC, D_800C39CA,
 * D_800C39C9), 0x77 (start position D_800C40AE = its frame) and 1 (the earliest one sets the screen colour
 * func_1517F3B0 from the RGB row D_800844A0[key[5]], key +6 == 1: with fade). The script position
 * D_800C39D0[slot] starts at D_800C40AE. */
void func_1501DB18(s32 slot) {
    u8 *found;
    u8 *rec;
    u8 *rgb;
    s32 best;
    s32 v;
    s32 i;

    D_800C40B9 = 0;
    D_800C39C9 = 0;
    D_800C40BC = 0;
    D_800C39CA = 0;
    D_800C40AE = 0;
    best = -1;
    for (i = 0; i < D_800C3A5A[slot]; i++) {
        rec = (u8 *)D_800C3AA8[slot][i];
        if (rec == NULL) {
            continue;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x1E, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C40B9 = 1;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0xE, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C40BC = 1;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x68, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C39CA = 1;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x44, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C39C9 = 1;
        }
        found = NULL;
        v = func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x77, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C40AE = v;
        }
        found = NULL;
        v = func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 1, 1, 0, 0, 0, slot);
        if (found != NULL && (best == -1 || v < best)) {
            best = v;
            rgb = D_800844A0[(s8)found[5]];
            if (*(s16 *)(found + 6) == 1) {
                func_1517F3B0(rgb[0], rgb[1], rgb[2], 0, 1, 0);
            } else {
                func_1517F3B0(rgb[0], rgb[1], rgb[2], 0, 0, 0);
            }
        }
    }
    (&D_800C39D0)[slot] = D_800C40AE;
}
