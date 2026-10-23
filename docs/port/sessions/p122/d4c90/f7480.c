/* vtx_wave_y_per_vertex: out[i].y = base[i].y + rint(cos(phase[i] - shift) * amp[i]) for the count vertices
 * (no offset where amp[i] <= 0); shift = state phase >> 4. Hand asm; count >= 1 (the asm loop wraps at 0). */
void func_150A7480(Vtx *out, s32 count, u8 *state, u8 *phase, f32 *amp, Vtx *base) {
    s32 shift = VTXWAVE_PHASE(state) >> 4;
    s32 b;
    f32 f;
    s32 d;
    s32 i;

    for (i = 0; i < count; i++) {
        d = 0;
        if (0.0f < amp[i]) {
            b = (phase[i] - shift) & 0xFF;
            f = VTX_WAVE_COS(b) * amp[i];
            d = VTX_WAVE_RINT(f);
        }
        out[i].v.ob[1] = base[i].v.ob[1] + d;
    }
    VTXWAVE_PHASE(state) = (VTXWAVE_PHASE(state) + VTXWAVE_SPEED(state)) & 0xFFF;
}
