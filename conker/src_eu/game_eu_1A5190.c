#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P188 */
void *allocate_memory(s32, s32, s32, s32);
u8 *world_record_find(u8 id);
/* P188: IDO's f32 -> u32 conversion kept to a byte: values <= -1 give 0xFFFFFFFF */
#define P188_F2U8(v) (((v) <= -1.0f) ? 0xFF : (u8) (u32) (v))

/*
 * model_light_create: P188: creates a light record (44 bytes, allocate_memory) for the model `id`
 * (world_record_find: origin s16 +0x10..+0x14, vertex count u16 +0x16, vertices +0x28, 16 bytes each, s16 x / y / z) and
 * appends it to the list D_800DD410 (count D_800DD418). Record: +0 id, +1 flags, +2 another light of the same model
 * was there before, +4 1 / (range * 0.01)^2 (0 for range 0), +8 intensity, +0xC range, +0xE..+0x12 light position
 * relative to the model origin, +0x14 0, +0x16 / +0x17 the two s8 factors, +0x18..+0x1D six colour bytes (kind 1).
 * Per vertex, with d = the vertex distance to the light * 0.01 (flag 0x10: the signed distance along the direction
 * `angle` degrees in the x / z plane): +0x24[i] = scale * d; flag 4: +0x20[i] = falloff * intensity * t^2 when
 * t = d - range * 0.01 is negative, else 0; kind 2: +0x28[i] = the direction byte (flag 0x10: angle * 256 / 360,
 * else func_150484A0 (atan2) of the squared x / z offsets * 128 / pi, as Rare wrote it).
 */
/* was func_15177410 */
void vtx_anim_light_create(u8 flags, u8 id, s16 x, s16 y, s16 z, f32 angle, u16 range, f32 intensity, s8 arg8, s8 scale,
                   u8 r0, u8 g0, u8 b0, u8 r1, u8 g1, u8 b1) {
    u8 *light;
    u8 *model;
    u8 found;
    s32 kind;
    s32 dir;
    s32 i, n;
    s32 d, ad, t;
    f32 dx, dy, dz;
    f32 ox, oz;
    f32 k, f;
    f32 s, c;
    u8 dirbyte;
    s16 *v;

    light = allocate_memory(44, 1, 0, 0);
    if (light == NULL) {
        return;
    }
    ((u8 **) D_800DD410)[D_800DD418] = light;
    D_800DD418++;
    model = world_record_find(id);
    light[1] = flags;
    light[0] = id;
    found = 0;
    n = D_800DD418 - 1;
    for (i = 0; i < n; i++) {
        if (((u8 **) D_800DD410)[i][0] == id) {
            found = 1;
            break;
        }
    }
    light[2] = found;
    dx = (f32) (x - *(s16 *) (model + 0x10));
    dy = (f32) (y - *(s16 *) (model + 0x12));
    dz = (f32) (z - *(s16 *) (model + 0x14));
    kind = flags & 3;
    *(s16 *) (light + 0xE) = (s32) dx;
    *(s16 *) (light + 0x10) = (s32) dy;
    *(u16 *) (light + 0xC) = range;
    *(s16 *) (light + 0x12) = (s32) dz;
    *(s16 *) (light + 0x14) = 0;
    *(f32 *) (light + 8) = intensity;
    *(s8 *) (light + 0x16) = arg8;
    *(s8 *) (light + 0x17) = scale;
    k = 0.01f;
    if (range != 0) {
        f = range * k;
        *(f32 *) (light + 4) = 1.0f / (f * f);
    } else {
        *(f32 *) (light + 4) = 0.0f;
    }
    if (kind == 1) {
        light[0x18] = r0;
        light[0x19] = g0;
        light[0x1A] = b0;
        light[0x1B] = r1;
        light[0x1C] = g1;
        light[0x1D] = b1;
    }
    *(u8 **) (light + 0x24) = allocate_memory(*(u16 *) (model + 0x16), 1, 0, 0);
    if (kind == 2) {
        *(u8 **) (light + 0x28) = allocate_memory(*(u16 *) (model + 0x16), 1, 0, 0);
    }
    if ((flags & 4) == 4) {
        *(f32 **) (light + 0x20) = allocate_memory(*(u16 *) (model + 0x16) * 4, 1, 0, 0);
    }
    dir = flags & 0x10;
    if (dir == 0x10) {
        s = sinf(-angle * 0.017453292f);
        c = cosf(-angle * 0.017453292f);
        dirbyte = P188_F2U8(angle * 0.7111111f);
    }
    for (i = 0; i < *(u16 *) (model + 0x16); i++) {
        v = (s16 *) (*(u8 **) (model + 0x28) + i * 0x10);
        if (dir == 0) {
            ox = v[0] - dx;
            f = v[1] - dy;
            oz = v[2] - dz;
            ox = ox * ox;
            oz = oz * oz;
            d = (s32) (sqrtf(ox + f * f + oz) * k);
            ad = d;
        } else {
            ox = v[0] - dx;
            oz = v[2] - dz;
            oz = -ox * s + oz * c;
            d = (s32) (oz * k);
            ad = (d < 0) ? -d : d;
        }
        (*(u8 **) (light + 0x24))[i] = scale * d;
        if ((flags & 4) == 4) {
            t = (s32) (ad - range * k);
            if (t >= 0) {
                (*(f32 **) (light + 0x20))[i] = 0.0f;
            } else {
                (*(f32 **) (light + 0x20))[i] = *(f32 *) (light + 4) * intensity * (f32) (t * t);
            }
        }
        if (kind == 2) {
            if (dir == 0x10) {
                (*(u8 **) (light + 0x28))[i] = dirbyte;
            } else {
                f = func_150484A0(ox, oz) * 40.743664f;
                (*(u8 **) (light + 0x28))[i] = P188_F2U8(f);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5190/vtx_anim_light_create.s")
#endif

#ifdef NON_MATCHING
/* P122 */
u8 *world_record_find(u8 id);
void world_record_build_matrix(f32 (*mf)[4], u8 *model);
void mtxf_transform_point(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
void vtx_wave_y_per_vertex(Vtx *out, s32 count, u8 *state, u8 *phase, f32 *amp, Vtx *base);
void vtx_wave_y(Vtx *out, s32 count, u8 *state, u8 *phase, Vtx *base);
void vtx_wave_y_colour(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, Vtx *base);
void vtx_wave_y_colour_per_vertex(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, f32 *amp, Vtx *base);
void vtx_wave_y_normal_colour(Vtx *out, s32 count, u8 *state, u8 *hue, u8 *phase, f32 *amp, Vtx *base);

/* Model record (world_record_find(id)): f32 position +0x0..+0x8, s16 integer offset +0x10..+0x14, u16 vertex count
 * +0x16, Vtx *frame[2] +0x20 (the buffer drawn in frame D_800BE9C0), Vtx *base +0x28, f32 scale +0x2C..+0x34,
 * u8 flags +0x6F (low nibble: visible). */
#define VTXANIM_COUNT(m) (*(u16 *) ((m) + 0x16))
#define VTXANIM_FRAME(m) (((Vtx **) ((m) + 0x20))[D_800BE9C0])
#define VTXANIM_BASE(m) (*(Vtx **) ((m) + 0x28))
#define VTXANIM_F32(m, o) (*(f32 *) ((m) + (o)))
#define VTXANIM_S16(m, o) (*(s16 *) ((m) + (o)))

/* vtx_anims_update: per frame, for the D_800DD418 vertex animations D_800DD410[i] (u8 model id +0, u8 mode +1,
 * u8 +2 != 0: wave on top of the current frame buffer instead of the base vertices, wave state +4, colour bytes
 * +0x18, f32 *amp +0x20, u8 *phase +0x24, u8 *hue +0x28) of visible models: the wave animator of mode & 3
 * (0: height, 1: height + colour, 2: height + direction colour; bit 2: per-vertex amplitudes, required for 2)
 * writes the model's frame buffer. Then the animations on the base vertices are moved to the model's place:
 * the integer offset +0x10 when the model is not moved / scaled (x, z from the base, y added), else the model
 * matrix (world_record_build_matrix) applied to (base x, wave y, base z), truncated. */
/* was func_15178004 */
void vtx_anims_update(void) {
    u8 *anim;
    u8 *model;
    Vtx *src;
    Vtx *out;
    Vtx *base;
    f32 mf[4][4];
    f32 x, y, z;
    s32 mode;
    s32 i;
    s32 j;

    for (i = 0; i < D_800DD418; i++) {
        anim = ((u8 **) D_800DD410)[i];
        model = world_record_find(anim[0]);
        if (!(model[0x6F] & 0xF)) {
            continue;
        }
        src = (anim[2] == 0) ? VTXANIM_BASE(model) : VTXANIM_FRAME(model);
        mode = anim[1];
        switch (mode & 3) {
            case 1:
                if ((mode & 4) == 4) {
                    vtx_wave_y_colour_per_vertex(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, anim + 0x18,
                                  *(u8 **) (anim + 0x24), *(f32 **) (anim + 0x20), src);
                } else {
                    vtx_wave_y_colour(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, anim + 0x18,
                                  *(u8 **) (anim + 0x24), src);
                }
                break;
            case 0:
                if ((mode & 4) == 4) {
                    vtx_wave_y_per_vertex(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, *(u8 **) (anim + 0x24),
                                  *(f32 **) (anim + 0x20), src);
                } else {
                    vtx_wave_y(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, *(u8 **) (anim + 0x24), src);
                }
                break;
            case 2:
                if ((mode & 4) == 4) {
                    vtx_wave_y_normal_colour(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, *(u8 **) (anim + 0x28),
                                  *(u8 **) (anim + 0x24), *(f32 **) (anim + 0x20), src);
                }
                break;
        }
    }

    for (i = 0; i < D_800DD418; i++) {
        anim = ((u8 **) D_800DD410)[i];
        if (!(world_record_find(anim[0])[0x6F] & 0xF) || anim[2] != 0) {
            continue;
        }
        model = world_record_find(anim[0]);
        if (VTXANIM_F32(model, 0) == 0.0f && VTXANIM_F32(model, 4) == 0.0f && VTXANIM_F32(model, 8) == 0.0f &&
            VTXANIM_F32(model, 0x2C) == 1.0f && VTXANIM_F32(model, 0x30) == 1.0f &&
            VTXANIM_F32(model, 0x34) == 1.0f) {
            for (j = 0; j < VTXANIM_COUNT(model); j++) {
                base = VTXANIM_BASE(model);
                VTXANIM_FRAME(model)[j].v.ob[0] = base[j].v.ob[0] + VTXANIM_S16(model, 0x10);
                out = &VTXANIM_FRAME(model)[j];
                out->v.ob[1] += VTXANIM_S16(model, 0x12);
                VTXANIM_FRAME(model)[j].v.ob[2] = VTXANIM_BASE(model)[j].v.ob[2] + VTXANIM_S16(model, 0x14);
            }
        } else {
            world_record_build_matrix(mf, model);
            for (j = 0; j < VTXANIM_COUNT(model); j++) {
                base = &VTXANIM_BASE(model)[j];
                mtxf_transform_point(mf, base->v.ob[0], VTXANIM_FRAME(model)[j].v.ob[1], base->v.ob[2], &x, &y, &z);
                VTXANIM_FRAME(model)[j].v.ob[0] = (s32) x;
                VTXANIM_FRAME(model)[j].v.ob[1] = (s32) y;
                VTXANIM_FRAME(model)[j].v.ob[2] = (s32) z;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5190/vtx_anims_update.s")
#endif
