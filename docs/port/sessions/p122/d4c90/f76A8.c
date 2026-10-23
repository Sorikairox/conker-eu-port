/* vtx_wave_y_colour: as vtx_wave_y (state amplitude) and the vertex colour follows the wave:
 * channel c = colour[2c] + ((rint(cos * 1024) * colour[2c + 1]) >> 10) (base, swing bytes). Hand asm; count >= 1. */
void func_150A76A8(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, Vtx *base) {
    s32 shift = VTXWAVE_PHASE(state) >> 4;
    f32 amp = VTXWAVE_AMP(state);
    s32 b;
    f32 c;
    f32 f;
    s32 d;
    s32 k;
    s32 i;
    /* the colour bytes are read once, before the loop */
    u8 r0 = colour[0], r1 = colour[1], g0 = colour[2], g1 = colour[3], b0 = colour[4], b1 = colour[5];

    for (i = 0; i < count; i++) {
        b = (phase[i] - shift) & 0xFF;
        c = VTX_WAVE_COS(b);
        f = c * amp;
        d = VTX_WAVE_RINT(f);
        f = c * 1024.0f;
        k = VTX_WAVE_RINT(f);
        out[i].v.cn[0] = r0 + ((k * r1) >> 10);
        out[i].v.cn[1] = g0 + ((k * g1) >> 10);
        out[i].v.cn[2] = b0 + ((k * b1) >> 10);
        out[i].v.ob[1] = base[i].v.ob[1] + d;
    }
    VTXWAVE_PHASE(state) = (VTXWAVE_PHASE(state) + VTXWAVE_SPEED(state)) & 0xFFF;
}
