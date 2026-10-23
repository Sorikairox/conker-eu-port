/*
 * orbit_object_step: per-frame motion of an object on two oscillators (record at obj + 0xA8). Advances the byte
 * phases +0xAC / +0xAD by the signed speeds +0xAE / +0xAF times the frame step D_800BE9E4; obj +0x38 / +0x3C =
 * base +0xA8 + amplitude +0xB0 / +0xB4 times sin(phase - 0x40) (func_151423D8 = byte-angle sine; both use the base
 * +0xA8, as the asm). While obj +0x5C > 0 it is clamped to the limit +0xB8, and a second pair of phases +0xC0 /
 * +0xC1 (unsigned speeds +0xC2 / +0xC3) gives obj +0x4C / +0x54 = +0xC4 / +0xC8 * sin(phase - 0x40) * +0x5C * +0xBC.
 * Returns 0 when flag 0x2000 of +0x68 is set and +0xCC < obj +0x50 + obj +0x44, else 1.
 */
s32 func_15159C2C(u8 *obj, u8 *arg1) {
    u8 *rec = obj + 0xA8;
    u8 ok = 1;
    f32 s0, s1, k;

    obj[0xAC] += (s8) obj[0xAE] * D_800BE9E4;
    obj[0xAD] += (s8) obj[0xAF] * D_800BE9E4;
    s0 = func_151423D8((obj[0xAC] - 0x40) & 0xFF);
    s1 = func_151423D8((rec[5] - 0x40) & 0xFF);
    *(f32 *) (obj + 0x38) = *(f32 *) (rec + 0) + *(f32 *) (rec + 8) * s0;
    *(f32 *) (obj + 0x3C) = *(f32 *) (rec + 0) + *(f32 *) (rec + 0xC) * s1;
    if (*(f32 *) (obj + 0x5C) > 0.0f) {
        if (*(f32 *) (rec + 0x10) < *(f32 *) (obj + 0x5C)) {
            *(f32 *) (obj + 0x5C) = *(f32 *) (rec + 0x10);
        }
        k = *(f32 *) (obj + 0x5C) * *(f32 *) (rec + 0x14);
        rec[0x18] += rec[0x1A] * D_800BE9E4;
        rec[0x19] += rec[0x1B] * D_800BE9E4;
        s0 = func_151423D8((rec[0x18] - 0x40) & 0xFF);
        s1 = func_151423D8((rec[0x19] - 0x40) & 0xFF);
        *(f32 *) (obj + 0x4C) = *(f32 *) (rec + 0x1C) * s0 * k;
        *(f32 *) (obj + 0x54) = *(f32 *) (rec + 0x20) * s1 * k;
    }
    if ((*(s32 *) (obj + 0x68) & 0x2000) && *(f32 *) (rec + 0x24) < *(f32 *) (obj + 0x50) + *(f32 *) (obj + 0x44)) {
        ok = 0;
    }
    return ok;
}
