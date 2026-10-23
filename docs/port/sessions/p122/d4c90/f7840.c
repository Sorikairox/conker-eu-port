/* vtx_wave_y_colour_per_vertex: as vtx_wave_y_colour with a per-vertex amplitude amp[i]; where amp <= 0 (from there on phase / amp stay on that element: Rare advances them only for amp > 0) the
 * vertex gets the base colour (colour[0], [2], [4]) and no offset. Hand asm; count >= 1. */
void func_150A7840(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, f32 *amp, Vtx *base) {
    s32 shift = VTXWAVE_PHASE(state) >> 4;
    s32 b;
    f32 c;
    f32 f;
    s32 d;
    s32 k;
    s32 i;
    s32 j = 0; /* phase / amp index: advances only on vertices with amp > 0 (as in the asm) */
    /* the colour bytes are read once, before the loop */
    u8 r0 = colour[0], r1 = colour[1], g0 = colour[2], g1 = colour[3], b0 = colour[4], b1 = colour[5];

    for (i = 0; i < count; i++) {
        if (0.0f < amp[j]) {
            b = (phase[j] - shift) & 0xFF;
            c = VTX_WAVE_COS(b);
            f = c * amp[j];
            d = VTX_WAVE_RINT(f);
            f = c * 1024.0f;
            k = VTX_WAVE_RINT(f);
            out[i].v.cn[0] = r0 + ((k * r1) >> 10);
            out[i].v.cn[1] = g0 + ((k * g1) >> 10);
            out[i].v.cn[2] = b0 + ((k * b1) >> 10);
            j++;
        } else {
            out[i].v.cn[0] = r0;
            out[i].v.cn[1] = g0;
            out[i].v.cn[2] = b0;
            d = 0;
        }
        out[i].v.ob[1] = base[i].v.ob[1] + d;
    }
    VTXWAVE_PHASE(state) = (VTXWAVE_PHASE(state) + VTXWAVE_SPEED(state)) & 0xFFF;
}
