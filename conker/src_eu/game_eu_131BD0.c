#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_1504715C(s32 *, struct127 *);
s32 func_15046F70(f32 *, s32, f32, s32 *);
f32 random_float(void);
s32 random_int(void);
void func_15055A2C(s32, f32, f32, f32, s32);
void fx_scorch_decal_spawn(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void func_151D5404(struct17 *, f32, f32, f32, s16, s16, s32, s32);
void func_151D58E4(struct17 *, f32, f32, f32, s16, s32, s32);
s32 func_151D5AC4(struct17 *, u8, s32);
void func_151D45A4(struct17 *, u8, s32);
void fx_debris_emitter_spawn(struct17 *, s16, u8, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
s32 func_151D4684(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags);

// ground_explosion: an explosion at pos (gated by src != NULL), as func_151C9740 object_explode: func_151D45A4,
// a scorch mark (fx_scorch_decal_spawn) where a ray from 100 above to 100 below pos hits a floor with flag 1 (floor of obj,
// func_1504715C / func_15046F70), the sparks fx_debris_emitter_spawn (at the scorch point when there is one), the blast
// effects func_151D5404 / func_151D58E4 / func_151D5AC4, for kind 1 / 2 the blast damage func_151D4684 (sounds
// 0x2B / 0x2A or 0x42 / 0x41), the sound func_15055A2C and the flash func_15154728.
// Called by func_1506AF3C / func_1506AF84 (effect handlers 11 / 14 of func_1506B04C, kind 1 / 2) and objfx_hit_at_self
// (game_981E0, kind = its argument).
/* was func_151043C0 */
void ground_explosion(struct127 *src, struct127 *obj, f32 *pos, u8 kind, s32 flags, u8 arg5, s32 arg6) {
    s32 ground[9];  /* floor query (func_1504715C / func_15046F70): f32 height at +0, flags byte +0x1C */
    struct17 probe;
    struct17 mark;
    u8 scorched;
    s32 sound1;
    s32 sound2;
    f32 r;
    u32 a;
    u32 b;
    struct17 *at;

    at = (struct17 *) pos;
    if (src == NULL) {
        return;
    }
    scorched = 0;
    func_151D45A4(at, arg5, arg6);
    probe.unk0 = at->unk0;
    probe.unk4 = at->unk4 + 100.0f;
    probe.unk8 = at->unk8;
    func_1504715C(ground, obj);
    if (func_15046F70((f32 *) &probe, 0, at->unk4 - 100.0f, ground) != 0 && (((u8 *) ground)[0x1C] & 1)) {
        mark.unk0 = probe.unk0;
        mark.unk4 = *(f32 *) &ground[0];
        mark.unk8 = probe.unk8;
        scorched = 1;
        r = random_float();
        a = random_int();
        b = random_int();
        fx_scorch_decal_spawn(r * 125.0f + 204.0f, a % 101 + 155, &ground[1], (f32 *) &mark, b % 302 + 500, 0, 1, 0, 0, 0,
                      arg5, 0);
    }
    fx_debris_emitter_spawn(scorched ? &mark : at, (u32) random_int() % 62 + 120, arg5, arg6);
    func_151D5404(at, 506.0f, 1013.0f, 0.000987166888f, 15, 20, arg5, arg6);
    func_151D58E4(at, 506.0f, 1013.0f, 0.000987166888f, 5, arg5, arg6);
    func_151D5AC4(at, arg5, arg6);
    if (kind != 0) {
        if (kind == 2) {
            sound1 = 0x42;
            sound2 = 0x41;
        } else {
            sound1 = 0x2B;
            sound2 = 0x2A;
        }
        func_151D4684(pos, NULL, src, obj, 0, sound1, sound2, flags);
    }
    func_15055A2C(0, at->unk0, at->unk4, at->unk8, 1);
    r = random_float();
    func_15154728(pos, r * 4.0f + 12.0f, 1.6409999f, (u32) random_int() % 56 + 200, 0.0f, arg5, arg6);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131BD0/ground_explosion.s")
#endif
