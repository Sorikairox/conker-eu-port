#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
u8 impact_current_kind(void);
#endif


s32 collision_floor_dynamic_b_full(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
void debris_burst_spawn(struct17 *, s32 *, s32, u8, s32);
void sound_play_for_actor(s32, s32, s32, s32, s32, u8 *);
void char_broadcast_msg_c(u8 *);
void char_ground_hit_trail(u8 *, u8 *);
extern f32 D_800A9354;
/* was func_151A9F80 */
void char_ground_debris_3(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9354 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 3, arg0[0xC], arg0[1]);
    }
}

extern f32 D_800A9358;
/* was func_151AA054 */
void char_ground_debris_3_sound(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9358 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 3, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 17, 21000, 0, 0, obj);
    }
    char_broadcast_msg_c(obj);
}

extern f32 D_800A935C;
/* was func_151AA150 */
void char_ground_debris_1_sound(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A935C < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 1, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 17, 21000, 0, 0, obj);
    }
}

extern f32 D_800A9360;
/* was func_151AA250 */
void char_ground_debris_1_heavy(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if (*(u8 **)(obj + 0x31C) != NULL && (*(u8 **)(obj + 0x31C))[0x95] != 0) {
        return;
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9360 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 1, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 8, 27000, 0, 0, obj);
    }
    char_ground_hit_trail(obj, arg0 + 0x34);
    char_broadcast_msg_c(obj);
}

extern f32 D_800A9364;
/* was func_151AA370 */
void char_ground_debris_2_sound(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9364 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 2, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 17, 21000, 0, 0, obj);
    }
}

extern f32 D_800A9368;
/* was func_151AA470 */
void char_ground_debris_2_heavy(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9368 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 2, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 8, 27000, 0, 0, obj);
    }
    char_ground_hit_trail(obj, arg0 + 0x34);
    char_broadcast_msg_c(obj);
}

extern f32 D_800A936C;
/* was func_151AA578 */
void char_ground_debris_4(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A936C < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 4, arg0[0xC], arg0[1]);
    }
}

extern f32 D_800A9370;
/* was func_151AA64C */
void char_ground_debris_4_b(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9370 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 4, arg0[0xC], arg0[1]);
    }
}

/* was func_151AA720 */
void char_handler_nop_a(s32 arg0) {
}

/* was func_151AA72C */
void char_foot_trails_restart(u8 *arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
    } sp1C;

    temp_v0 = *(s32 *)(arg0 + 0x18);
    sp1C.unk0 = temp_v0;
    sp1C.unk4 = arg0[0x1C];
    fxrec_broadcast((s32)&sp1C, 0xA);
    effect_nodes_broadcast((s32)&sp1C, 0xA);
    foot_trails_start(arg0);
}

/* was func_151AA780 */
void char_foot_trails_stop(u8 *arg0) {   /* P76: callback; a0 passes through */
    foot_trails_stop(arg0);
}

/* was func_151AA7A0 */
void char_foot_trails_stop_b(u8 *arg0) {   /* P76: callback; a0 passes through */
    foot_trails_stop(arg0);
}

/* was func_151AA7C0 */
void char_foot_trails_restart_b(u8 *arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
    } sp1C;

    temp_v0 = *(s32 *)(arg0 + 0x18);
    sp1C.unk0 = temp_v0;
    sp1C.unk4 = arg0[0x1C];
    fxrec_broadcast((s32)&sp1C, 0xA);
    effect_nodes_broadcast((s32)&sp1C, 0xA);
    foot_trails_start(arg0);
}

#ifdef NON_MATCHING
s32 emitter_trail_spawn(s32 *, s32, s32, s32);

/* was func_151AA814 */
void char_ground_hit_trail(u8 *arg0, u8 *arg1) {
    struct {
        s32 u18;
        s32 u1C;
        u8 u20;
        u8 pad21[0x3];
        u8 * u24;
        s8 u28;
        u8 pad29[0x3];
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        s16 u40;
        s8 u42;
        s8 u43;
        s8 u44;
        s8 u45;
    } sp;

    if ((*(u8 *)((u8 *)arg1 + 0x1C)) & 1) {
        sp.u18 = 0;
        sp.u1C = 0;
        sp.u28 = 1;
        sp.u40 = 0x1E;
        sp.u42 = 0xE;
        sp.u43 = 2;
        sp.u44 = -1;
        sp.u45 = 0;
        sp.u24 = arg0;
        sp.u20 = (*(u8 *)((u8 *)arg0 + 0x3B));
        sp.u2C = 0.0f;
        sp.u30 = 0.0f;
        sp.u34 = 0.0f;
        sp.u38 = 25.0f;
        sp.u3C = 1.21244f;
        emitter_trail_spawn(&sp.u18, 0, 0xFF, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/char_ground_hit_trail.s")
#endif
extern f32 D_800A9378;
extern f32 D_800A937C;
extern f32 D_800A9380;
#ifdef NON_MATCHING
s32 smoke_puff_spawn_grounded(f32 *arg0, u8 *arg1, f32 arg2, f32 arg3, u8 *arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);
#else
void smoke_puff_spawn_grounded(f32 *, f32 *, f32, s32, s32, f32, s32, s32, s32, s32, s32);
#endif
s32 move_watch_get_data(u8 *, s32 *);
/* was func_151AA8BC */
void ground_drip_particle_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 pos[3];
    f32 vel[3];
    u8 *obj;
    s32 sp48;

    obj = *(u8 **)(arg6 + 0x1C);
    if (!(*(f32 *)(obj + 0x118) < arg1)) {
        if (move_watch_get_data(obj, &sp48) == 0) {
            sp48 = 0;
        }
        vel[0] = 0.0f;
        vel[1] = -((random_float() * 196.0f + 199.0f) * D_800A9378 * arg4);
        vel[2] = 0.0f;
        pos[0] = arg0;
        pos[1] = arg1;
        pos[2] = arg2;
#ifdef NON_MATCHING
        smoke_puff_spawn_grounded(pos, vel, (random_float() * D_800A937C + 454.0f) * D_800A9380, 0.972683f /* 0x3F7901C1 */, (u8 *) sp48,
            random_float() * 101.0f + 101.0f, random_int() % 31U + 0x32, random_int() % 101U + 0x64, 1, arg6[0xC], arg6[1]);
#else
        smoke_puff_spawn_grounded(pos, vel, (random_float() * D_800A937C + 454.0f) * D_800A9380, 0x3F7901C1, sp48,
            random_float() * 101.0f + 101.0f, random_int() % 31U + 0x32, random_int() % 101U + 0x64, 1, arg6[0xC], arg6[1]);
#endif
    }
}

typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} SpA3C;
typedef struct {
    s32 a;
    u8 b;
    s32 c;
    s32 d;
    f32 e;
    f32 f;
} SpB3C;
s32 bone_emitter_spawn(SpA3C *, s32, ...);
extern f32 D_800A9384;
extern f32 D_800A9388;

/* was func_151AAA3C */
s32 char_bone_emitter_spawn(u8 *arg0, s32 arg1) {
    SpA3C s;
    s32 v;
    SpB3C b;

    b.a = arg1;
    b.b = 1;
    s.u0 = arg0[0x3B];
    s.u4 = arg0;
    s.u8_ = 15;
    s.uC = -11.0f;
    s.u10 = -2.0f;
    s.u14 = 8.0f;
    s.u18 = -11.0f;
    s.u1C = -2.0f;
    s.u20 = 20.0f;
    s.u24 = 0;
    s.u26 = 60;
    s.u28 = 60;
    s.u2A = 300;
    s.u2E = 1;
    s.u2F = 0;
    s.u30 = 1;
    s.u34 = 0.5f;
    s.u38 = 1;
    s.u39 = 0;
    b.c = 0;
    b.d = 0x11111;
    b.e = D_800A9384;
    b.f = D_800A9388;
    v = bone_emitter_spawn(&s, 0x18);
    if (v != 0) {
        memcpy((void *)(v + 0x80), &b, 0x18);
    }
    return v;
}

s32 game_gu_random();

/* was func_151AAB54 */
s32 char_emitter_random_sound(u8 *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x88)) = 0;
    if (random_int() & 1) {
        sound_play_at(0xA, 0x55F0U, (s16) ((game_gu_random() % 1200) - 0x258), 0U, 0, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x58)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x5C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x60)), 0x1F4, 0x9C4);
    } else {
        sound_play_at(0xB, 0x55F0U, (s16) ((game_gu_random() % 1200) - 0x258), 0U, 0, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x58)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x5C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x60)), 0x1F4, 0x9C4);
    }
    return 1;
}

#ifdef NON_MATCHING
/* was func_151AAC88 */
void char_emitter_particle_emit(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    struct {
        f32 u1C;
        s8 u20;
        s8 u21;
        s8 u22;
        s8 u23;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        s8 u34;
        s8 u35;
        s8 u36;
        s8 u37;
        f32 u38;
        f32 u3C;
        u8 pad40[0x8];
        s32 u48;
        s32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s16 u66;
        s16 u68;
        s16 u6A;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x4];
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
    } sp;
    f32 temp_f2;
    f32 temp_f4;
    s32 temp_v0;

    sp.u65 = 0x2F;
    sp.u50 = 0xC01;
    sp.u48 = 0x200005;
    sp.u4C = 0;
    sp.u62 = 0;
    sp.u61 = 0;
    sp.u60 = 0;
    sp.u5F = 0;
    sp.u5E = 0;
    sp.u5D = 0;
    sp.u5C = 0;
    sp.u58 = 0;
    sp.u54 = 0;
    sp.u64 = 0xFF;
    sp.u6A = 0;
    sp.u6C = 0.0f;
    sp.uA0 = 0x1207;
    sp.uA8 = 5;
    sp.uA9 = 5;
    sp.uAA = 4;
    sp.uAB = -1;
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u66 = 0x14;
    sp.u68 = 0xC;
    sp.u20 = 0;
    sp.u21 = 0;
    sp.u34 = 0;
    sp.u35 = 0;
    sp.u2C = 3.5f;
    sp.u30 = 0.2857143f;
    temp_f4 = ((*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0))) * (*(f32 *)((u8 *)arg5 + 0x74));
    sp.u90 = temp_f4;
    sp.u94 = ((*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4))) * (*(f32 *)((u8 *)arg5 + 0x74));
    sp.u98 = ((*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8))) * (*(f32 *)((u8 *)arg5 + 0x74));
    (*(f32 *)((u8 *)(&sp.u78) + 0)) = (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.u78) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.u78) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    sp.u78 += temp_f4 * arg4;
    sp.u7C += sp.u94 * arg4;
    sp.u80 += sp.u98 * arg4;
    if (random_int() & 1) {
        sp.uA0 |= 0x40;
    }
    if (random_int() & 1) {
        sp.uA0 |= 0x80;
    }
    sp.u52 = (random_int() % 51U) + 0x32;
    sp.u63 = (random_int() % 101U) + 0x64;
    temp_f2 = (random_float() * 39.0f) + 31.0f;
    sp.u70 = temp_f2;
    sp.u1C = temp_f2;
    sp.u74 = temp_f2;
    sp.u22 = (random_int() % 5U) + 4;
    sp.u23 = (random_int() % 5U) + 4;
    sp.u24 = ((random_float() * 0.25f) + 0.15f) * sp.u1C;
    sp.u28 = ((random_float() * 0.25f) + 0.15f) * sp.u1C;
    sp.u36 = (random_int() % 5U) + 4;
    sp.u37 = (random_int() % 5U) + 4;
    sp.u38 = ((random_float() * 0.1f) + 0.08f) * sp.u1C;
    sp.u3C = ((random_float() * 0.1f) + 0.08f) * sp.u1C;
    sp.u9C = ((random_float() * 70.0f) + 73.0f) * 0.001f;
    temp_v0 = particle_spawn_default(&sp.u48, 2, 0x28);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0xA8, &sp.u1C, 0x28);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/char_emitter_particle_emit.s")
#endif
/* was func_151AAFFC */
f32 char_emitter_wobble(u8 *arg0) {
    u8 **q;
    u8 *p;
    f32 r;

    q = &arg0;
    r = angle_byte_cos((((u32) (*(u32 *)((u8 *)arg0 + 0x88)) >> 0x10) - 0x40));
    p = *q;
    r = (*(f32 *)((u8 *)p + 0x90)) + ((*(f32 *)((u8 *)p + 0x94)) * (0, r)); // fakematch: (0, x) comma flips commutative operand order
    p += 0x80;
    *(s32 *)(p + 8) = (*(s32 *)((u8 *)p + 0xC)) * D_800BE9E4 + (*(u32 *)((u8 *)p + 8));
    return r;
}

#ifdef NON_MATCHING
s32 character_spawn_ring_fx(u8 *, u8 *, u8 *);

/* was func_151AB06C */
void char_emitters_refresh(u8 *arg0) {
    u8 *sp2C;
    u8 *sp1C;
    s32 temp_a0;
    u8 *temp_a2;
    u8 *var_v1;

    temp_a2 = (*(u8 **)((u8 *)arg0 + 0x18));
    var_v1 = arg0 + 0x58;
    if ((*(s32 *)((u8 *)arg0 + 0x6C)) != 0) {
        (*(s8 *)((u8 *)(((*(s32 *)((u8 *)var_v1 + 0x14)) + 0x80)) + 4)) = 1;
    } else {
        sp2C = temp_a2;
        var_v1 = arg0 + 0x58;
        (*(s32 *)((u8 *)var_v1 + 0x14)) = char_bone_emitter_spawn(temp_a2, (s32) arg0);
    }
    temp_a0 = (*(s32 *)((u8 *)var_v1 + 0x1C));
    if (temp_a0 != 0) {
        (*(s8 *)((u8 *)((temp_a0 + 0x58)) + 4)) = 1;
        return;
    }
    sp1C = var_v1;
    (*(s32 *)((u8 *)var_v1 + 0x1C)) = character_spawn_ring_fx(temp_a2, arg0, temp_a2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/char_emitters_refresh.s")
#endif
/* was func_151AB100 */
void char_bone_emitter_retire(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    bone_emitter_retire(arg0);
}

/* was func_151AB128 */
void char_bone_emitter_free(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    bone_emitter_free(arg0);
}

/* was func_151AB150 */
s32 fx_alive_flag_check(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x84] == 0) {
        ret = 0;
    }
    arg0[0x84] = 0;
    return ret;
}

#ifdef NON_MATCHING
/* P191 */
void mtx_get_translation(Mtx *arg0, s32 arg1, struct17 *arg2);
s32 collision_floor_all(f32 *, s32, f32, f32 *);
void hitinfo_from_obj_floor(void *, u8 *);
extern u8 D_800A9350[];   /* bone of each foot: 5, 10, 19, 23 */
extern f32 D_800A93AC[5]; /* splash ring parameters (unk18..unk28 of the emit_sparks_in_angle_range block) */
/* ground probe result of hitinfo_from_obj_floor / collision_floor_all (HitInfo in game_eu_71E70.c) */
typedef struct {
    f32 y;          /* 0x00: ground height */
    s16 pos[9];     /* 0x04 */
    s32 unk18;
    u8 flags;
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
} FootHitAABC4;

// footstep_splash: P191: footstep effect of the player p for foot `foot` (0..3, animation event callbacks
// objfx_1aabc4_0 ... in game_981E0): when p has a model (+0x1D4), takes the foot bone's position (mtx_get_translation, bone
// D_800A9350[foot]), probes the ground from 50 above to 50 below it (hitinfo_from_obj_floor / collision_floor_all) and, on a hit,
// spawns a splash sprite at (bone x, ground y, bone z) (impact_dust_particle_spawn: light, size 40, 150, the hit's surface) and a
// ring burst there (emit_sparks_in_angle_range with D_800A93AC's five parameters). s32 although the asm leaves no defined result:
// game_981E0 calls it without a prototype (implicitly int), so the port needs the int signature; it returns 0.
/* was func_151AABC4 */
s32 footstep_splash(struct127 *p, s32 foot) {
    struct_eu_15154488 ring;
    struct17 at;
    f32 probe[3];
    FootHitAABC4 hit;
    f32 bone[3];
    u8 light;

    if (p == NULL || *(Mtx **) ((u8 *) p + 0x1D4) == NULL) {
        return 0;
    }
    light = impact_current_kind();
    mtx_get_translation(*(Mtx **) ((u8 *) p + 0x1D4), D_800A9350[foot & 0xFF], (struct17 *) bone);
    hitinfo_from_obj_floor(&hit, (u8 *) p);
    probe[0] = bone[0];
    probe[1] = bone[1] + 50.0f;
    probe[2] = bone[2];
    if (collision_floor_all(probe, 0, probe[1] - 100.0f, (f32 *) &hit) == 0) {
        return 0;
    }
    at.unk0 = bone[0];
    at.unk4 = hit.y;
    at.unk8 = bone[2];
    impact_dust_particle_spawn(light, 40.0f, 150, (s32) hit.pos, &at, 0xFF, 1);
    ring.unk8 = at;
    ring.unk2E = 3;
    ring.unk14 = 2.5f;
    ring.unk2C = 3;
    ring.unk2 = 0xFF;
    ring.unk4 = -0x40;
    ring.unk6 = 0x1A;
    ring.unk0 = 0;
    ring.unk30 = 3;
    ring.unk32 = 1;
    ring.unk34 = 30;
    ring.unk36 = 20;
    ring.unk38 = 155;
    ring.unk3A = 100;
    ring.unk44 = 0x10;
    ring.unk46 = 0xF;
    ring.unk48 = 0;
    ring.unk18 = D_800A93AC[0];
    ring.unk1C = D_800A93AC[1];
    ring.unk20 = D_800A93AC[2];
    ring.unk24 = D_800A93AC[3];
    ring.unk28 = D_800A93AC[4];
    ring.unk3C = light;
    ring.unk40 = 0.0f;
    emit_sparks_in_angle_range(&ring, &ring.unk8, (s32) &hit, 0xFF, 1);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/footstep_splash.s")
#endif

/* was func_151AB36C */
s32 fx_alpha_fade_by_life16(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) << 4;
    if (temp_v1 >= 0x100) {
        temp_v1 = 0xFF;
    }
    if (temp_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = temp_v1;
    }
    return 1;
}

#ifdef NON_MATCHING
extern s32 D_800AB7F4;

/* was func_151AB3A8 */
void char_ground_glow_refresh(u8 *arg0) {
    struct {
        u8 * u60;
        s8 u64;
        u8 pad65[0x3];
        f32 u68;
        f32 u6C;
        f32 u70;
        s16 u74;
        s16 u76;
        s16 u78;
        u8 pad7A[0x2];
        f32 u7C;
        s32 u80;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        s32 u88;
        s32 u8C;
        s8 u90;
        s8 u91;
        u8 u92;
        u8 u93;
        u8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s32 u98;
        u8 pad9C[0xC];
        f32 uA8;
        f32 uAC;
        f32 uB0;
    } sp;
    f32 sp5C;
    u8 sp5B;
    s32 sp50;
    s32 sp4C;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f6;
    struct210 *temp_v0_3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((*(s32 *)((u8 *)arg0 + 0x70)) != 0) {
        (*(s8 *)((u8 *)(((*(s32 *)((u8 *)arg0 + 0x70)) + 0xB0)) + 4)) = 1;
        return;
    }
    sp.uA8 = (*(f32 *)((u8 *)temp_v0 + 0x14));
    temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x118));
    if (temp_f0 > -9500.0f) {
        sp.uAC = temp_f0 + 100.0f;
    } else {
        sp.uAC = (*(f32 *)((u8 *)temp_v0 + 0x18)) + 150.0f;
    }
    sp.uB0 = (*(f32 *)((u8 *)temp_v0 + 0x1C));
    if (collision_floor_dynamic_b_full((u8 *) &sp.uA8, 0U, sp.uAC - 300.0f, arg0 + 0x34) != 0) {
        sp5B = impact_current_kind();
        temp_f18 = (*(f32 *)((u8 *)arg0 + 0x34));
        sp.uAC = temp_f18;
        temp_f6 = random_float() * 30.0f;
        sp.u64 = 1;
        sp5C = temp_f6 + 50.0f;
        sp.u76 = 0xA;
        sp.u78 = 0xA;
        temp_v0_2 = (u8 *) &D_800AB7F4 + sp5B * 3;
        sp.u86 = 0x38;
        sp.u84 = 0x12C;
        sp.u8C = (s32) ((32768.0f * 0.5f) + 26214.4f);
        sp.u80 = 0x60300;
        sp.u90 = 0x96;
        sp.u60 = arg0;
        sp.u74 = 0;
        sp.u88 = 0;
        sp.u91 = 0xFF;
        sp.u95 = 0xFF;
        sp.u98 = 0x440001;
        sp.u96 = 0;
        sp.u97 = 6;
        sp.u68 = 26214.4f;
        sp.u6C = 32768.0f;
        sp.u7C = 0.231f;
        sp.u70 = 0.0f;
        sp.u92 = (*(u8 *)((u8 *)temp_v0_2 + 0));
        sp.u93 = (*(u8 *)((u8 *)temp_v0_2 + 1));
        sp.u94 = (*(u8 *)((u8 *)temp_v0_2 + 2));
        sp4C = random_int();
        sp50 = random_int();
        temp_v0_3 = sprite_fx_spawn_cam((s32) &sp.u80, 7U, 1U, (s32) (arg0 + 0x38), sp.uA8, temp_f18, sp.uB0, sp5C, sp5C, (u8) (sp4C & 0xFF), (u8) (((random_int() & 1) * 2) + (sp50 & 1)), 0x20, 0xFFU, 1);
        (*(struct210 **)((u8 *)((arg0 + 0x58)) + 0x18)) = temp_v0_3;
        if (temp_v0_3 != NULL) {
            memcpy(&temp_v0_3->unkA4[3], &sp.u60, 0x20);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/char_ground_glow_refresh.s")
#endif
typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 pad1A;
    f32 unk1C;
} struct_C630;
/* was func_151AB640 */
s8 char_ground_glow_update(u8 *arg0) {
    s8 ret;
    struct_C630 *p;
    ret = 1;
    p = (struct_C630 *)(arg0 + 0xB0);
    if (p->unk4 == 0) {
        ret = 0;
    }
    p->unk4 = 0;
    p->unk14 -= D_800BE9E4;
    if (p->unk14 < 0) {
        p->unk14 = ((u32)random_int() % (u32)(p->unk18 + 1)) + p->unk16;
        p->unk10 = (random_float() * p->unkC) + p->unk8;
    }
    *(s32 *)(arg0 + 0x24) += (s32)((p->unk10 - (f32)*(s32 *)(arg0 + 0x24)) * p->unk1C);
    return ret;
}

s32 sprite_fx_set_handlers(u8 *, s32, s32);
/* was func_151AB730 */
s32 char_ground_glow_free(u8 *arg0)
{
  u8 *p;
  p = *((u8 **) (arg0 + 0xB0));
  p += 0x59;  // fakematch: keeps the dead addiu (p += K+1; p--;)
  p--;  // fakematch: pairs with p += K+1
  *((s32 *) (p + 0x18)) = 0;
  *((s32 *) (arg0 + 0xB0)) = 0;
  *((s32 *) (arg0 + 0x18)) = (*((s32 *) (arg0 + 0x18))) | 2;
  sprite_fx_set_handlers(arg0, 0, 0);
  return 0;
}

extern f32 D_800A93CC;
/* was func_151AB774 */
void char_ground_debris_3_heavy(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A93CC < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 3, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 17, 21000, 0, 0, obj);
    }
    char_ground_hit_trail(obj, arg0 + 0x34);
}

#ifdef NON_MATCHING
/* character_spawn_ring_fx: P238: called by char_emitters_refresh (which stores the result at its record +0x1C) as
 * (character, owner, character). Creates effect type 0xC (emitter_trail_spawn(&spawn, 0xC, 0xFF, 0)) from a 0x2E-byte
 * spawn block: character + its id byte +0x3B, flag 1, offset (0, 0, 0), radius 25, scale 0.26497 (D_800A93D0,
 * 0x3E87AA26), life 300, bytes 10 / 3 / 0 / 1. On success the effect's +0x58 gets a 12-byte record (owner, 1, s16 0,
 * the character's f32 +0x118). Returns the effect (or NULL). The third argument is unused. */
/* was func_151AB874 */
s32 character_spawn_ring_fx(u8 *chr, u8 *owner, u8 *unused) {
    struct {
        u8 *owner;
        u8 one;
        s16 zero;
        f32 height;
    } rec;
    struct {
        s32 u0;
        s32 u4;
        u8 id;
        u8 *chr;
        u8 one;
        f32 offset[3];
        f32 radius;
        f32 scale;
        s16 life;
        u8 b2A;
        u8 b2B;
        u8 b2C;
        u8 b2D;
    } spawn;
    u8 *fx;

    rec.zero = 0;
    rec.one = 1;
    rec.owner = owner;
    rec.height = *(f32 *) (chr + 0x118);
    spawn.u0 = 0;
    spawn.u4 = 0;
    spawn.id = chr[0x3B];
    spawn.chr = chr;
    spawn.one = 1;
    spawn.offset[0] = 0.0f;
    spawn.offset[1] = 0.0f;
    spawn.offset[2] = 0.0f;
    spawn.radius = 25.0f;
    spawn.scale = 0.26497f;
    spawn.life = 300;
    spawn.b2A = 10;
    spawn.b2B = 3;
    spawn.b2C = 0;
    spawn.b2D = 1;
    fx = (u8 *) emitter_trail_spawn((s32 *) &spawn, 0xC, 0xFF, 0);
    if (fx != NULL) {
        memcpy(fx + 0x58, &rec, 0xC);
    }
    return (s32) fx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/character_spawn_ring_fx.s")
#endif

#ifdef NON_MATCHING
/* was func_151AB954 */
void char_emitter_particle_emit_b(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    struct {
        f32 u1C;
        s8 u20;
        s8 u21;
        s8 u22;
        s8 u23;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        s8 u34;
        s8 u35;
        s8 u36;
        s8 u37;
        f32 u38;
        f32 u3C;
        f32 u40;
        u8 pad44[0x4];
        s32 u48;
        s32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s16 u66;
        s16 u68;
        s16 u6A;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x4];
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
    } sp;
    f32 temp_f2;
    s32 temp_v0;

    sp.u50 = 0xC01;
    sp.u65 = 0x2F;
    sp.u48 = 0x200005;
    sp.u4C = 0;
    sp.u62 = 0;
    sp.u61 = 0;
    sp.u60 = 0;
    sp.u5F = 0;
    sp.u5E = 0;
    sp.u5D = 0;
    sp.u5C = 0;
    sp.u58 = 0;
    sp.u54 = 0;
    sp.u64 = 0xFF;
    sp.u6A = 0;
    sp.u6C = 0.0f;
    sp.uA0 = 0x3207;
    sp.uA8 = 5;
    sp.uA9 = 5;
    sp.uAA = 4;
    sp.uAB = -1;
    sp.u78 = arg0;
    sp.u7C = arg1;
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u66 = 0x1E;
    sp.u68 = 8;
    sp.u80 = arg2;
    sp.u40 = (*(f32 *)((u8 *)arg6 + 0x60));
    sp.u2C = 4.0f;
    sp.u30 = 0.25f;
    sp.u20 = 0;
    sp.u21 = 0;
    sp.u34 = 0;
    sp.u35 = 0;
    sp.u90 = -arg3 * 0.2f;
    sp.u94 = 0.0f;
    sp.u98 = -arg5 * 0.2f;
    if (random_int() & 1) {
        sp.uA0 |= 0x40;
    }
    if (random_int() & 1) {
        sp.uA0 |= 0x80;
    }
    sp.u52 = (random_int() % 51U) + 0x6A;
    sp.u63 = (random_int() % 101U) + 0x64;
    temp_f2 = (random_float() * 62.0f) + 41.0f;
    sp.u70 = temp_f2;
    sp.u1C = temp_f2;
    sp.u74 = temp_f2;
    sp.u22 = (random_int() % 5U) + 4;
    sp.u23 = (random_int() % 5U) + 4;
    sp.u24 = ((random_float() * 0.25f) + 0.15f) * sp.u1C;
    sp.u28 = ((random_float() * 0.25f) + 0.15f) * sp.u1C;
    sp.u36 = (random_int() % 5U) + 4;
    sp.u37 = (random_int() % 5U) + 4;
    sp.u38 = ((random_float() * 0.1f) + 0.08f) * sp.u1C;
    sp.u3C = ((random_float() * 0.1f) + 0.08f) * sp.u1C;
    sp.u9C = ((random_float() * 60.0f) + 21.0f) * 0.001f;
    temp_v0 = particle_spawn_default(&sp.u48, 2, 0x28);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0xA8, &sp.u1C, 0x28);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/char_emitter_particle_emit_b.s")
#endif
typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5;
    u16 unk6;
} SndC68;

/* was func_151ABC68 */
u8 char_loop_sound_update(u8 *arg0) {
    u8 ret;
    SndC68 *s;

    ret = 1;
    s = (SndC68 *)(arg0 + 0x58);
    if (s->unk6 != 0 && !(D_800DBFF0->unk5F0 & 1)) {
        sound_voice_stop(*(s16 *)&s->unk6);
        s->unk6 = 0;
    } else if (s->unk6 == 0 && (D_800DBFF0->unk5F0 & 1)) {
        s->unk6 = sound_play_2d(0x355, 0x7D00, 0x40, 0, 0);
    }
    if (s->unk4 == 0) {
        ret = 0;
    }
    s->unk4 = 0;
    return ret;
}

#ifdef NON_MATCHING
s32 object_list_move_1(u8 *);
s32 object_list_free(u8 *);

/* D_80089E40 table entries 4 / 14 (s32 (*)(obj), see emitter_trail_update): stop the object's sound (+0x5E), clear the
 * data's word +0x74, then return object_list_move_1 / object_list_free's result (the asm tail value). */
/* was func_151ABD38 */
s32 char_sound_obj_retire(u8 *arg0) {
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        sound_voice_stop(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    return object_list_move_1(arg0);
}

/* was func_151ABD88 */
s32 char_sound_obj_free(u8 *arg0) {
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        sound_voice_stop(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    return object_list_free(arg0);
}
#else
void char_sound_obj_retire(u8 *arg0) {
    s32 pad;
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        sound_voice_stop(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    object_list_move_1(arg0);
}

void char_sound_obj_free(u8 *arg0) {
    s32 pad;
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        sound_voice_stop(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    object_list_free(arg0);
}
#endif

/* was func_151ABDD8 */
void char_start_interaction_4(void **arg0) {
    obj_interaction_start_timed(arg0[0x18 / 4], 0, 4);
}

#ifdef NON_MATCHING
u8 *model_drip_create(void *, s32, u8, s32);

// character_spawn_aura: for characters of type 0..4 or 0x96 (arg0's data +0x18), spawns the 12-byte-template effect
// model_drip_create (character, its +0x3B, life 300, mode 3 for type 0x96 else 0) and, when the character has a
// partner (+0x127 != 0xFF), sets the partner's +0x66 timer to 500. P124: one struct instead of m2c's 6 locals.
/* was func_151ABE04 */
void character_spawn_aura(u8 *arg0) {
    struct {
        u8 *u0;
        u8 u4;
        s16 u6;
        s8 u8;
        s8 u9;
        s8 uA;
    } t;
    u8 *chr;
    u8 type;

    chr = *(u8 **)(arg0 + 0x18);
    type = chr[4];
    if (type == 0 || type == 1 || type == 2 || type == 3 || type == 4 || type == 0x96) {
        t.u0 = chr;
        t.u6 = 300;
        t.u8 = 0;
        t.u9 = 0;
        t.u4 = chr[0x3B];
        if (chr[4] == 0x96) {
            t.uA = 3;
        } else {
            t.uA = 0;
        }
        if (chr[0x127] != 0xFF) {
            *(s16 *)(*(u8 **)(chr + 0x31C) + 0x66) = 500;
        }
        model_drip_create(&t, 0, arg0[0xC], arg0[1]);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/character_spawn_aura.s")
#endif
/* was func_151AB920 */
void char_handler_nop_b(s32 arg0, s32 arg1) {
}

u8 impact_current_kind(void);
extern f32 D_800A93F4;

/* was func_151AB930 */
void char_state_fx_start(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        s32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        u8 unk18;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = *(u16 *)(arg0 + 0x84);
    tmp.unkC = 0.0f;
    tmp.unk10 = D_800A93F4;
    tmp.unk14 = 3.0f;
    tmp.unk18 = impact_current_kind();
    temp_v0 = effect_node_create_nodraw(0x3C, -1, 0xE, 1, 9, 0x1C, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x1C);
    }
}

#ifdef NON_MATCHING
void hitinfo_from_obj_floor(void *, u8 *);

/* was func_151ABF78 */
void char_state_fx_update(u8 *arg0) {
    struct {
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        u8 padF0[0x23];
        u8 u113;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f2;
    s16 temp_s0;
    s16 temp_t5;
    s32 temp_s0_2;
    s32 temp_s2;
    u8 var_v1;
    u8 *temp_s1;
    u8 *temp_s1_2;
    u8 *temp_v0;

    var_v1 = 0;
    temp_s1 = arg0 + 0x28;
    if (*(*(s32 **)((u8 *)arg0 + 0x28)) == 0) {
        goto block_5;
    }
    temp_v0 = (*(u8 **)((u8 *)temp_s1 + 0));
    if ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) {
        goto block_5;
    }
    if ((*(s32 *)((u8 *)temp_s1 + 8)) != (*(u16 *)((u8 *)temp_v0 + 0x84))) {
block_5:
        var_v1 = 1;
    }
    sp.u113 = var_v1;
    if (var_v1 == 0) {
        temp_s1_2 = arg0 + 0x28;
        sp.u113 = var_v1;
        (*(f32 *)((u8 *)temp_s1_2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1_2 + 0xC)) + (((*(f32 *)((u8 *)temp_s1_2 + 0x10)) + (random_float() * (*(f32 *)((u8 *)temp_s1_2 + 0x14)))) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s1_2 + 0xC)) > 1.0f) {
            hitinfo_from_obj_floor(&sp.uEC, (*(u8 **)((u8 *)temp_s1_2 + 0)));
            do {
                temp_s0 = random_int() & 0xFF;
                temp_t5 = (random_int() % 46U) - 0x3F;
                temp_f20 = angle_byte_cos(temp_t5 & 0xFF);
                temp_f22 = angle_byte_cos((temp_t5 - 0x40) & 0xFF);
                temp_f24 = angle_byte_cos(temp_s0 & 0xFF);
                temp_f26 = angle_byte_cos((temp_s0 - 0x40) & 0xFF);
                temp_f0 = random_float();
                temp_f12 = 30.0f * temp_f20;
                sp.uE0 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_s1_2 + 0))) + 0x14)) + (temp_f12 * temp_f26);
                sp.uE4 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_s1_2 + 0))) + 0x18)) - (75.0f * temp_f22);
                sp.uE8 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_s1_2 + 0))) + 0x1C)) + (temp_f12 * temp_f24);
                temp_f2 = ((temp_f0 * 713.0f) + 500.0f) * 0.01f;
                temp_f14 = temp_f2 * temp_f20;
                sp.uD4 = temp_f14 * temp_f26;
                sp.uD8 = -temp_f2 * temp_f22;
                sp.uDC = temp_f14 * temp_f24;
                temp_f20_2 = random_float();
                temp_s0_2 = random_int();
                temp_s2 = random_int();
                impact_dust_cloud_spawn(&sp.uE0, &sp.uD4, (*(u8 *)((u8 *)temp_s1_2 + 0x18)), (temp_f20_2 * 0.5f) + -1.0f, (s16) (((u32) temp_s0_2 % 26U) + 0x20), (u8) (((u32) temp_s2 % 101U) + 0x64), (random_float() * 34.0f) + 52.0f, 1U, 1.0f, 1.0f, 1U, (s32) &sp.uEC, 1U, 0U, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s1_2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1_2 + 0xC)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1_2 + 0xC)) > 1.0f);
        }
    }
    if (sp.u113 != 0) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/char_state_fx_update.s")
#endif
/* was func_151AC304 */
void char_state_fx_handle_msg(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            node_destroy(arg0);
        }
    } else {
        v = arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}

/* was func_151AC3B0 */
void char_broadcast_msg_c(u8 *arg0)
{
  struct { u8 *unk0; u8 unk4; } sp18;
  sp18.unk0 = arg0;
  sp18.unk4 = arg0[0x3B];
  node_broadcast_type(0x20, (s32) &sp18, 0xCU);
}
