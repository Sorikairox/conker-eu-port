/* vtx_wave_y: out[i].y = base[i].y + rint(cos(phase[i] - shift) * amplitude) with the state's amplitude for every
 * vertex; shift = state phase >> 4. Hand asm; count >= 1. */
void func_150A75A0(Vtx *out, s32 count, u8 *state, u8 *phase, Vtx *base) {
    s32 shift = VTXWAVE_PHASE(state) >> 4;
    f32 amp = VTXWAVE_AMP(state);
    s32 b;
    f32 f;
    s32 i;

    for (i = 0; i < count; i++) {
        b = (phase[i] - shift) & 0xFF;
        f = VTX_WAVE_COS(b) * amp;
        out[i].v.ob[1] = base[i].v.ob[1] + VTX_WAVE_RINT(f);
    }
    VTXWAVE_PHASE(state) = (VTXWAVE_PHASE(state) + VTXWAVE_SPEED(state)) & 0xFFF;
}
