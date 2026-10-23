/* Free-camera reset countdown (called by func_1512B2C4): while +0x5FC (frames) is set, mark +0x5F8, fill the first
 * ceil(n) halfwords of the +0x8BC buffer with 0xFFFC (n = +4 of the camera's player entry in D_800BE628, 0x180
 * bytes each), clear +0x60C and count +0x5FC down; returns 1 then, else 0. */
s32 func_1512BAAC(u8 *cam) {
    s32 i;

    if (*(s16 *)(cam + 0x5FC) == 0) {
        return 0;
    }
    *(s16 *)(cam + 0x5F8) = 1;
    for (i = 0; (f32)i < *(f32 *)((u8 *)D_800BE628 + cam[0x23D] * 0x180 + 4); i++) {
        (*(s16 **)(cam + 0x8BC))[i] = 0xFFFC;
    }
    *(f32 *)(cam + 0x60C) = 0.0f;
    *(s16 *)(cam + 0x5FC) -= 1;
    return 1;
}
