/* vtx_wave_y_normal_colour: per-vertex amplitude wave (as vtx_wave_y_per_vertex) whose colour is a direction:
 * with a = phase[i] - shift, t = rint(cos(a - 64) * 64), e = cos(t - 64) * 127 and h = hue[i]:
 * colour = (rint(e * cos(h - 64)), rint(cos(t) * 127), rint(e * cos(h))); (0, 0x7F, 0) and no offset where
 * amp <= 0 (from there on phase / amp stay on that element: Rare advances them only for amp > 0). Hand asm (the lookups go through func_150A7BD0); count >= 1. */
void func_150A79FC(Vtx *out, s32 count, u8 *state, u8 *hue, u8 *phase, f32 *amp, Vtx *base) {
    s32 shift = VTXWAVE_PHASE(state) >> 4;
    s32 b;
    s32 t;
    s32 d;
    f32 f;
    f32 g;
    f32 e;
    s32 i;
    s32 j = 0; /* phase / amp index: advances only on vertices with amp > 0 (as in the asm) */

    for (i = 0; i < count; i++) {
        if (0.0f < amp[j]) {
            b = (phase[j] - shift) & 0xFF;
            f = VTX_WAVE_COS(b) * amp[j];
            d = VTX_WAVE_RINT(f);
            b = (b - 0x40) & 0xFF;
            f = VTX_WAVE_COS(b) * 64.0f;
            t = VTX_WAVE_RINT(f) & 0xFF;
            g = VTX_WAVE_COS(t) * 127.0f;
            b = (t - 0x40) & 0xFF;
            e = VTX_WAVE_COS(b) * 127.0f;
            b = (hue[i] - 0x40) & 0xFF;
            f = e * VTX_WAVE_COS(b);
            out[i].v.cn[0] = VTX_WAVE_RINT(f);
            out[i].v.cn[1] = VTX_WAVE_RINT(g);
            b = hue[i];
            f = e * VTX_WAVE_COS(b);
            out[i].v.cn[2] = VTX_WAVE_RINT(f);
            j++;
        } else {
            out[i].v.cn[0] = 0;
            out[i].v.cn[1] = 0x7F;
            out[i].v.cn[2] = 0;
            d = 0;
        }
        out[i].v.ob[1] = base[i].v.ob[1] + d;
    }
    VTXWAVE_PHASE(state) = (VTXWAVE_PHASE(state) + VTXWAVE_SPEED(state)) & 0xFFF;
}
