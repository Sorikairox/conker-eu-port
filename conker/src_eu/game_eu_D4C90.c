#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* P122: vertex wave animators (hand asm in the ROM), readable C; called by vtx_anims_update. */
extern f32 D_8009A5E0[]; /* cos(i * 2pi / 256) for i = 0..64 (a quarter wave) */

/* vtx_wave_cos: cos(b * 2pi / 256) of the byte angle b (0..255) from the quarter-wave table (the hand-asm lookup,
 * also vtx_wave_cos_lookup). Macros, not functions: the hand asm makes no calls. */
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
/* was func_150A7480 */
void vtx_wave_y_per_vertex(Vtx *out, s32 count, u8 *state, u8 *phase, f32 *amp, Vtx *base) {
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

/* vtx_wave_y: out[i].y = base[i].y + rint(cos(phase[i] - shift) * amplitude) with the state's amplitude for every
 * vertex; shift = state phase >> 4. Hand asm; count >= 1. */
/* was func_150A75A0 */
void vtx_wave_y(Vtx *out, s32 count, u8 *state, u8 *phase, Vtx *base) {
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

/* vtx_wave_y_colour: as vtx_wave_y (state amplitude) and the vertex colour follows the wave:
 * channel c = colour[2c] + ((rint(cos * 1024) * colour[2c + 1]) >> 10) (base, swing bytes). Hand asm; count >= 1. */
/* was func_150A76A8 */
void vtx_wave_y_colour(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, Vtx *base) {
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

/* vtx_wave_y_colour_per_vertex: as vtx_wave_y_colour with a per-vertex amplitude amp[i]; where amp <= 0 (from there on phase / amp stay on that element: Rare advances them only for amp > 0) the
 * vertex gets the base colour (colour[0], [2], [4]) and no offset. Hand asm; count >= 1. */
/* was func_150A7840 */
void vtx_wave_y_colour_per_vertex(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, f32 *amp, Vtx *base) {
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

/* vtx_wave_y_normal_colour: per-vertex amplitude wave (as vtx_wave_y_per_vertex) whose colour is a direction:
 * with a = phase[i] - shift, t = rint(cos(a - 64) * 64), e = cos(t - 64) * 127 and h = hue[i]:
 * colour = (rint(e * cos(h - 64)), rint(cos(t) * 127), rint(e * cos(h))); (0, 0x7F, 0) and no offset where
 * amp <= 0 (from there on phase / amp stay on that element: Rare advances them only for amp > 0). Hand asm (the lookups go through vtx_wave_cos_lookup); count >= 1. */
/* was func_150A79FC */
void vtx_wave_y_normal_colour(Vtx *out, s32 count, u8 *state, u8 *hue, u8 *phase, f32 *amp, Vtx *base) {
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

/* P279: private entry of vtx_wave_y_normal_colour (sine lookup by quarter, t4/s6/s7 in, f8 out, returns via v0): folded into the VTX_WAVE_COS macro of vtx_wave_y_normal_colour's NM C */
