#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void hitinfo_from_obj_floor(s32 *, struct127 *);
s32 collision_floor_probe(f32 *, s32, f32, s32 *);
f32 random_float(void);
s32 random_int(void);
void explosion_sfx_play(s32, f32, f32, f32, s32);
void fx_scorch_decal_spawn(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void rumble_all_players_at(struct17 *, f32, f32, f32, s16, s16, s32, s32);
void cam_shake_all_players(struct17 *, f32, f32, f32, s16, s32, s32);
s32 smoke_cloud_spawn(struct17 *, u8, s32);
void explosion_light_spawn(struct17 *, u8, s32);
void fx_debris_emitter_spawn(struct17 *, s16, u8, s32);
s32 spark_shower_spawn(f32 *, f32, f32, f32, f32, s32, s32);
s32 object_effects_at(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags);

// ground_explosion: an explosion at pos (gated by src != NULL), as object_explode_big object_explode: explosion_light_spawn,
// a scorch mark (fx_scorch_decal_spawn) where a ray from 100 above to 100 below pos hits a floor with flag 1 (floor of obj,
// hitinfo_from_obj_floor / collision_floor_probe), the sparks fx_debris_emitter_spawn (at the scorch point when there is one), the blast
// effects rumble_all_players_at / cam_shake_all_players / smoke_cloud_spawn, for kind 1 / 2 the blast damage object_effects_at (sounds
// 0x2B / 0x2A or 0x42 / 0x41), the sound explosion_sfx_play and the flash spark_shower_spawn.
// Called by obj_effect_ground_blast / obj_effect_ground_blast_alt (effect handlers 11 / 14 of obj_effect_run_handler, kind 1 / 2) and objfx_hit_at_self
// (game_981E0, kind = its argument).
/* was func_151043C0 */
void ground_explosion(struct127 *src, struct127 *obj, f32 *pos, u8 kind, s32 flags, u8 arg5, s32 arg6) {
    s32 ground[9];  /* floor query (hitinfo_from_obj_floor / collision_floor_probe): f32 height at +0, flags byte +0x1C */
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
    explosion_light_spawn(at, arg5, arg6);
    probe.unk0 = at->unk0;
    probe.unk4 = at->unk4 + 100.0f;
    probe.unk8 = at->unk8;
    hitinfo_from_obj_floor(ground, obj);
    if (collision_floor_probe((f32 *) &probe, 0, at->unk4 - 100.0f, ground) != 0 && (((u8 *) ground)[0x1C] & 1)) {
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
    rumble_all_players_at(at, 506.0f, 1013.0f, 0.000987166888f, 15, 20, arg5, arg6);
    cam_shake_all_players(at, 506.0f, 1013.0f, 0.000987166888f, 5, arg5, arg6);
    smoke_cloud_spawn(at, arg5, arg6);
    if (kind != 0) {
        if (kind == 2) {
            sound1 = 0x42;
            sound2 = 0x41;
        } else {
            sound1 = 0x2B;
            sound2 = 0x2A;
        }
        object_effects_at(pos, NULL, src, obj, 0, sound1, sound2, flags);
    }
    explosion_sfx_play(0, at->unk0, at->unk4, at->unk8, 1);
    r = random_float();
    spark_shower_spawn(pos, r * 4.0f + 12.0f, 1.6409999f, (u32) random_int() % 56 + 200, 0.0f, arg5, arg6);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131BD0/ground_explosion.s")
#endif
