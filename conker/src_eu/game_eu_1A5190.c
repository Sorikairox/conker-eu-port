#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5190/func_15177410.s")

#ifdef NON_MATCHING
/* P122 */
u8 *func_151149AC(u8 id);
void func_15114E8C(f32 (*mf)[4], u8 *model);
void func_150A7E40(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
void func_150A7480(Vtx *out, s32 count, u8 *state, u8 *phase, f32 *amp, Vtx *base);
void func_150A75A0(Vtx *out, s32 count, u8 *state, u8 *phase, Vtx *base);
void func_150A76A8(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, Vtx *base);
void func_150A7840(Vtx *out, s32 count, u8 *state, u8 *colour, u8 *phase, f32 *amp, Vtx *base);
void func_150A79FC(Vtx *out, s32 count, u8 *state, u8 *hue, u8 *phase, f32 *amp, Vtx *base);

/* Model record (func_151149AC(id)): f32 position +0x0..+0x8, s16 integer offset +0x10..+0x14, u16 vertex count
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
 * matrix (func_15114E8C) applied to (base x, wave y, base z), truncated. */
void func_15178004(void) {
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
        model = func_151149AC(anim[0]);
        if (!(model[0x6F] & 0xF)) {
            continue;
        }
        src = (anim[2] == 0) ? VTXANIM_BASE(model) : VTXANIM_FRAME(model);
        mode = anim[1];
        switch (mode & 3) {
            case 1:
                if ((mode & 4) == 4) {
                    func_150A7840(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, anim + 0x18,
                                  *(u8 **) (anim + 0x24), *(f32 **) (anim + 0x20), src);
                } else {
                    func_150A76A8(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, anim + 0x18,
                                  *(u8 **) (anim + 0x24), src);
                }
                break;
            case 0:
                if ((mode & 4) == 4) {
                    func_150A7480(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, *(u8 **) (anim + 0x24),
                                  *(f32 **) (anim + 0x20), src);
                } else {
                    func_150A75A0(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, *(u8 **) (anim + 0x24), src);
                }
                break;
            case 2:
                if ((mode & 4) == 4) {
                    func_150A79FC(VTXANIM_FRAME(model), VTXANIM_COUNT(model), anim + 4, *(u8 **) (anim + 0x28),
                                  *(u8 **) (anim + 0x24), *(f32 **) (anim + 0x20), src);
                }
                break;
        }
    }

    for (i = 0; i < D_800DD418; i++) {
        anim = ((u8 **) D_800DD410)[i];
        if (!(func_151149AC(anim[0])[0x6F] & 0xF) || anim[2] != 0) {
            continue;
        }
        model = func_151149AC(anim[0]);
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
            func_15114E8C(mf, model);
            for (j = 0; j < VTXANIM_COUNT(model); j++) {
                base = &VTXANIM_BASE(model)[j];
                func_150A7E40(mf, base->v.ob[0], VTXANIM_FRAME(model)[j].v.ob[1], base->v.ob[2], &x, &y, &z);
                VTXANIM_FRAME(model)[j].v.ob[0] = (s32) x;
                VTXANIM_FRAME(model)[j].v.ob[1] = (s32) y;
                VTXANIM_FRAME(model)[j].v.ob[2] = (s32) z;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5190/func_15178004.s")
#endif
