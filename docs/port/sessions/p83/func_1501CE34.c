/* Length of cutscene slot `slot` (P84 browser blocker: func_1501E364 waits for it): the end frame of the first
 * camera track when it has one (record +0x12 != -9999 and the slot's first camera word >= 4), else the latest end
 * (+0x0A) of the camera tracks of the active actors, else the last key (frame at -2 of key k, D_800C39F0 count)
 * of their actor tracks. D_800C3A68 = the length in 60 Hz frames, D_eu_800C3A60[slot] = it in 50 Hz frames
 * (EU: * 50 / 60). */
void func_1501CE34(s32 slot) {
    s32 *len = &(&D_eu_800C3A60)[slot];
    u16 *cams;
    u8 n;
    s32 i;
    s32 found;
    s32 end;
    s32 v;
    u16 k;

    *len = 0;
    D_800C3A68 = 0;
    n = D_800C3A5A[slot];
    if (n == 0) {
        return;
    }
    cams = D_800C39F8[slot];
    if (cams[0] >= 4) {
        v = *(s16 *)((u8 *)D_800C3AA8[slot][0] + 0x12);
        if (v != -9999) {
            D_800C3A68 = v;
            *len = v * 50 / 60;
            return;
        }
    }
    found = FALSE;
    for (i = 0; i < n; i++) {
        if (D_800C39E8[slot][i] != 0 && cams[i] != 0) {
            v = *(s16 *)((u8 *)D_800C3AA8[slot][i] + 0xA);
            if (*len < v) {
                *len = v;
                found = TRUE;
            }
        }
    }
    if (found) {
        end = *len;
        D_800C3A68 = end;
        *len = end * 50 / 60;
        return;
    }
    end = *len;
    for (i = 0; i < n; i++) {
        if (D_800C39E8[slot][i] != 0) {
            k = D_800C39F0[slot][i];
            if (k != 0) {
                v = *(s16 *)((u8 *)D_800C3B98[slot][i] + k * 8 - 2);
                if (end < v) {
                    *len = v;
                    end = v;
                }
            }
        }
    }
    D_800C3A68 = end;
    *len = end * 50 / 60;
}
