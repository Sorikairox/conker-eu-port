// obj_fog_alpha_gfx: with i == 0 and a non-zero alpha byte at obj +0x1B, appends func_1517F5FC's colour command
// (alpha * 63 / 256, colour 0, 0, 0, index 0) to gfx; returns the new display list end (gfx unchanged otherwise).
Gfx *func_15104A0C(Gfx *gfx, u8 *obj, s16 i) {
    if (i == 0 && obj[0x1B] != 0) {
        return func_1517F5FC(gfx, (obj[0x1B] * 63) >> 8, 0, 0, 0, i);
    }
    return gfx;
}
