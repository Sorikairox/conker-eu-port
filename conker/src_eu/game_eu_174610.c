#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 collision_floor_probe(f32 *, s32, f32, s32);
s32 hitinfo_from_obj_floor(s32, struct127 *);
s32 mtx_get_translation(s32, s32, f32 *, u8);

/* was func_15146E00 */
s32 obj_fx_point_probe_floor(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    if ((arg3 != 1) && ((u32)arg3 != 2)) { // fakematch: unsigned cast keeps the compare on a3 (permuter)
        return 0;
    }
    var_a1 = (arg3 == 1) ? 0x13 : 0x17;
    mtx_get_translation(*(s32 *)(arg1 + 0x1D4), var_a1, arg0, arg3);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    hitinfo_from_obj_floor(arg2, arg1);
    return collision_floor_probe(sp2C, 0, arg0[1] - 50.0f, arg2);
}

#ifdef NON_MATCHING
s32 obj_query_table6(struct127 *);
s32 trigger_first_touched(u32, s32, s32 *);

/* Interaction hook (D_8008A084 table, called by obj_interaction_update with the mode from interaction_mode_for_level and the object):
 * maps mode 0..8 to an entry of D_8008A0B4, -1 = none. Mode 1 in level 4 (D_800BE9F0) asks obj_query_table6; mode 6
 * looks the object up with the five ids 0x401D..0x4021 (D_800A5AB0) through trigger_first_touched. */
/* was func_15146EE0 */
s32 interaction_hook_map_mode(s32 mode, struct127 *obj) {
    s32 ids[5];

    switch (mode) {
        case 0:
            return 0;
        case 1:
            if (D_800BE9F0 == 4) {
                if (obj_query_table6(obj) != 0) {
                    return 6;
                }
                return 3;
            }
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 6:
            /* D_800A5AB0; filled by hand: an initialised local array lands in .data, which the NM link drops */
            ids[0] = 0x401D;
            ids[1] = 0x401E;
            ids[2] = 0x401F;
            ids[3] = 0x4020;
            ids[4] = 0x4021;
            if (trigger_first_touched(obj - D_800CC2D0, 5, ids) == -1) {
                return -1;
            }
            return 6;
        case 7:
            return 15;
        case 8:
            return 16;
        default:
            return -1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/interaction_hook_map_mode.s")
#endif

typedef struct { f32 x, y, z; } V3_15147008;
typedef struct {
    s32 a;
    s32 b;
    V3_15147008 pos;
    f32 f2C;
    f32 f30;
    s16 s34;
    s16 s36;
    s16 s38;
    s16 s3A;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    u8 b54;
    s16 s56;
    s16 s58;
} Spawn_15147008;
void emit_tumbling_pieces(u8 *arg0, u8 arg1, u8 arg2, s32 arg3);
/* was func_15147008 */
void obj_fx_point_spawn_burst(u8 *arg0, int arg1, s32 arg2) {
    V3_15147008 p;
    Spawn_15147008 s;

    if (*(s32 *)(arg0 + 0x1D4)) {
        if (0) // fakematch: empty if keeps the arg0 reload schedule
        {
        }
        obj_fx_point_probe_floor((f32 *)&p, arg0, 0, arg1);
        s.a = 5;
        s.b = 0x16;
        s.pos = p;
        s.f2C = 0.024999999f;
        s.f30 = 0.0199f;
        s.s34 = 0;
        s.s36 = 0xFF;
        s.s38 = -20;
        s.s3A = 14;
        s.f3C = 6.0f;
        s.f40 = 3.0f;
        s.f44 = 7.9760003f;
        s.f48 = -0.40300003f;
        s.f4C = 0.284f;
        s.f50 = 0.95355f;
        s.b54 = 3;
        s.s56 = 25;
        s.s58 = 25;
        emit_tumbling_pieces((u8 *)&s, 0, 0xFF, 1);
    }
}

/* was func_15147128 */
void obj_fx_point_impact_b(s32 arg0, s32 arg1, s32 arg2) {
    obj_fx_point_impact(arg0, arg1, arg2, 0);
}

/* was func_15147148 */
void obj_fx_point_impact_c(s32 arg0, s32 arg1, s32 arg2) {
    obj_fx_point_impact(arg0, arg1, arg2, 1);
}

void fx_spawn_impact_particle(u8, s32 *, f32, s32, f32 *, u8);
void fx_spawn_impact_burst(u8, f32 *, s32, f32, f32);
int obj_fx_point_impact(arg0, arg1, arg2, arg3)
    u8 *arg0;
    int arg1;
    s32 arg2;
    u8 arg3;
{
    f32 sp4C[3];
    s32 sp28[9];

    if (*(s32 *)(arg0 + 0x1D4)) {
        if (0) // fakematch: empty if keeps the arg0 reload schedule
        {
        }
        if (obj_fx_point_probe_floor(sp4C, arg0, (s32)sp28, arg1) != 0) {
            fx_spawn_impact_particle(arg3 ? 0xC : 0xB, sp28, arg2 * 0.0076923077f, (u8)(*(f32 *)(arg0 + 0x40) * 0.7111111f), sp4C, arg1);
            if (arg2 >= 0x73) {
                fx_spawn_impact_burst(2, sp4C, sp28[6], 1.0f, 1.0f);
            }
        }
    }
}

#ifdef NON_MATCHING
/* P243: readable C for obj_fx_point_effect10 (game_eu_174610, 73 insns). */
// object_effect10_spawn: for an object with a model (+0x1D4), obj_fx_point_probe_floor finds the point `id` of obj (position into
// pt, a record into rec); when found, spawns effect kind 10 through fx_spawn_impact_particle with size arg2 * (1 / 85) and the
// byte (u32) (obj+0x40 scale * 0.7111111) (late rodata D_800A5B08 / D_800A5B0C), the point and the id. Twin of
// footstep_dust_spawn (game_eu_118CE0, which uses obj_foot_pos_probe_ground). No caller in the decomp (no jal, no data word): void, as
// the twin; the asm returns no defined value. (fx_spawn_impact_particle: the declaration above obj_fx_point_impact's caller block.)

/* was func_151472D0 */
void obj_fx_point_effect10(u8 *obj, u8 id, s32 arg2) {
    struct {
        s32 rec[9];
        f32 pt[3];
    } sp;

    if (*(s32 *)(obj + 0x1D4) != 0) {
        if (obj_fx_point_probe_floor(sp.pt, obj, (s32) sp.rec, id) != 0) {
            fx_spawn_impact_particle(10, sp.rec, (f32) arg2 * 0.011764706f, (u8) (u32) (*(f32 *)(obj + 0x40) * 0.7111111f), sp.pt,
                          id);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/obj_fx_point_effect10.s")
#endif

#ifdef NON_MATCHING
u8 impact_current_kind(void);
void fx_spawn_impact_burst(u8, f32 *, s32, f32, f32);
void impact_splash_ring_spawn(u8, f32, u8, f32 *, u8, u8, s32);

// object_splash_spawn: effect handler of the same table as obj_fx_point_effect10 (entry {0x50, fn}, `void (u8 *obj, u8 id,
// s32 strength)`). For an object with a model (+0x1D4), obj_fx_point_probe_floor finds point `id` and probes the surface below
// it (rec[0] = surface height, f32). Takes an effect slot (impact_current_kind); strength >= 0x47 also spawns the
// fx_spawn_impact_burst effect at the point (rec[6]). Then, at (pt x, surface, pt z), one of two random effects: a ring
// impact_debris_spawn (size 10..20, alpha 100..200, life 80..120) or a burst impact_splash_ring_spawn (size 5..13, alpha 100..200).
/* was func_151473F4 */
void obj_fx_point_splash(u8 *obj, u8 id, s32 strength) {
    struct {
        s32 rec[9];
        f32 pt[3];
    } sp;
    f32 pos[3];
    u8 slot;
    f32 r;
    u32 a;
    u32 b;

    if (*(s32 *) (obj + 0x1D4) != 0) {
        if (obj_fx_point_probe_floor(sp.pt, obj, (s32) sp.rec, id) != 0) {
            slot = impact_current_kind();
            if (strength >= 0x47) {
                fx_spawn_impact_burst(slot, sp.pt, sp.rec[6], 1.0f, 1.0f);
            }
            pos[0] = sp.pt[0];
            pos[1] = *(f32 *) &sp.rec[0];
            pos[2] = sp.pt[2];
            if (random_int() & 1) {
                r = random_float();
                a = random_int();
                b = random_int();
                impact_debris_spawn(slot, r * 10.0f + 10.0f, a % 101 + 100, (s32) &sp.rec[1], (struct17 *) pos,
                              b % 41 + 80, 1, 1, 0, 0xFF, 1);
            } else {
                r = random_float();
                a = random_int();
                impact_splash_ring_spawn(slot, r * 8.0f + 5.0f, a % 101 + 100, pos, 1, 0xFF, 1);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/obj_fx_point_splash.s")
#endif

s32 obj_fx_point_probe_floor(f32 *, u8 *, s32, u8);
#ifdef NON_MATCHING
void spawn_circle_random_emit(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#else
s32 spawn_circle_random_emit(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#endif
/* was func_151475B0 */
void obj_fx_point_spawn_sparkle(u8 *arg0, volatile u8 arg1, s32 arg2) {
    f32 sp44[3];
    s16 sp42;
    u8 **q = &arg0; // fakematch: arg0 reloaded from its home slot
    if (*(s32 *)(*q + 0x1D4) != 0) {
        do {} while (0); // fakematch: permuter
        obj_fx_point_probe_floor(sp44, *q, 0, arg1);
        sp42 = (random_int() % 11U) + 5;
#ifdef NON_MATCHING
        spawn_circle_random_emit(sp44[0], sp44[1], sp44[2], random_float() * 11.0f, 0, 0xFF, sp42, 0x16, 0, 0.0f, 0, 0xFF);
#else
        spawn_circle_random_emit(sp44[0], sp44[1], *(s32 *)&sp44[2], random_float() * 11.0f, 0, 0xFF, sp42, 0x16, 0, 0.0f, 0, 0xFF);
#endif
    }
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 particle_spawn_basic(void *, s32, s32, u8, s32);
/* was func_1514766C */
s32 fx_spawn_dust_puff(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    s32 obj;
    f32 scale;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (random_int() & 0xF) + 0x14;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (random_int() % 101U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (random_float() * 95.0f) + 101.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    vec3_from_angles_byte(arg8, (s16) ((random_int() % 11U) - 0xB), ((random_float() * 396.0f) + 202.0f) * 0.01f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 0xA;
    sp.u97 = -1;
    sp.u52 = 0x14;
    sp.u54 = 0xC;
    sp.u56 = 0x1B;
    sp.u58 = 1.02f;
    scale = 0.94000006f;
    obj = particle_spawn_basic(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

extern u8 (*D_800900A4)(void);
void fx_spawn_impact_particle(u8, s32 *, f32, s32, f32 *, u8);
void fx_spawn_impact_burst(u8, f32 *, s32, f32, f32);
/* was func_15147888 */
void obj_fx_point_impact_a4(u8 *arg0, int arg1, s32 arg2) {
    f32 sp4C[3];
    s32 sp28[9];

    if (*(s32 *)(arg0 + 0x1D4)) {
        if (0) // fakematch: empty if keeps the arg0 reload schedule
        {
        }
        if (obj_fx_point_probe_floor(sp4C, arg0, (s32)sp28, arg1) != 0) {
            if (arg2 >= 0x73) {
                fx_spawn_impact_burst(0, sp4C, sp28[6], 1.0f, 1.0f);
            }
            fx_spawn_impact_particle(D_800900A4(), sp28, arg2 * 0.0076923077f, (u8)(*(f32 *)(arg0 + 0x40) * 0.7111111f), sp4C, arg1);
        }
    }
}

void fx_spawn_impact_particle(u8, s32 *, f32, s32, f32 *, u8);
void fx_spawn_impact_burst(u8, f32 *, s32, f32, f32);
extern u8 (*D_800900BC)(void);
/* was func_151479E8 */
void obj_fx_point_impact_bc(u8 *arg0, int arg1, s32 arg2)
{
  f32 sp4C[3];
  s32 sp28[9];
  if (*((s32 *) (arg0 + 0x1D4)))
  {
    if (0) // fakematch: empty if keeps the arg0 reload schedule (DIFF2 without)
    {
    }
    if (obj_fx_point_probe_floor(sp4C, arg0, (s32) sp28, arg1) != 0)
    {
      fx_spawn_impact_particle(D_800900BC(), sp28, arg2 * 0.0076923077f, (u8) ((*((f32 *) (arg0 + 0x40))) * 0.7111111f), sp4C, arg1);
      if (arg2 >= 0x73)
      {
        fx_spawn_impact_burst(6, sp4C, sp28[6], 1.0f, 1.0f);
      }
    }
  }
}

#ifdef NON_MATCHING
extern u8 (*D_800900D0)(void);
extern f32 D_800A5B2C;
extern f32 D_800A5B30;
// impact_effect_c: P250. Effect table handler (u8 *obj, kind, level) like its table neighbour obj_fx_point_impact_bc (records
// {handler, 0x82} at ELF file offset 0x24A4D4): when the object has a model (+0x1D4) and obj_fx_point_probe_floor finds the
// effect point (pos + hit record), spawns the effect whose id D_800900D0() returns (fx_spawn_impact_particle: strength level *
// D_800A5B2C, size +0x40 * D_800A5B30 as a byte) and, for level >= 0x73, effect 0xB (fx_spawn_impact_burst) with the hit
// record's word 6.
/* was func_15147B48 */
void obj_fx_point_impact_d0(u8 *obj, s32 kind, s32 level) {
    f32 pos[3];
    s32 hit[9];

    if (*(s32 *) (obj + 0x1D4) != 0 && obj_fx_point_probe_floor(pos, obj, (s32) hit, (u8) kind) != 0) {
        fx_spawn_impact_particle(D_800900D0(), hit, (f32) level * D_800A5B2C, (u8) (u32) (*(f32 *) (obj + 0x40) * D_800A5B30),
                      pos, (u8) kind);
        if (level >= 0x73) {
            fx_spawn_impact_burst(0xB, pos, hit[6], 1.0f, 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/obj_fx_point_impact_d0.s")
#endif
