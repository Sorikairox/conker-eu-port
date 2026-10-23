extern f32 D_8009A5E0[]; /* cos(i * 2pi / 256) for i = 0..64 (a quarter wave) */

/* vtx_wave_cos: cos(b * 2pi / 256) of the byte angle b (0..255) from the quarter-wave table (the hand-asm lookup,
 * also func_150A7BD0). Macros, not functions: the hand asm makes no calls. */
#define VTX_WAVE_COS(b)                                                                                    \
    ((b) <= 0x40 ? D_8009A5E0[b] : (b) <= 0x80 ? -D_8009A5E0[0x80 - (b)]                                   \
     : (b) <= 0xC0 ? -D_8009A5E0[(b) - 0x80] : D_8009A5E0[0x100 - (b)])

/* vtx_wave_rint: cvt.w.s in the default FCSR mode (round to nearest, ties to even), for |f| < 2^31 */
#define VTX_WAVE_RINT(f)                                                                                   \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32) (f)                                                 \
     : ((f) >= 0.0f) ? (s32) (((f) + 8388608.0f) - 8388608.0f)                                            \
                     : -(s32) ((-(f) + 8388608.0f) - 8388608.0f))

/* Wave state (the animation record + 4): f32 amplitude at +0x4, u16 phase at +0x10 (12 bits; the byte angle
 * offset is phase >> 4), s8 phase speed at +0x12. Each wave function advances the phase by the speed (mod 0x1000)
 * after its vertex loop. */
#define VTXWAVE_AMP(st) (*(f32 *) ((st) + 4))
#define VTXWAVE_PHASE(st) (*(u16 *) ((st) + 0x10))
#define VTXWAVE_SPEED(st) (*(s8 *) ((st) + 0x12))
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
