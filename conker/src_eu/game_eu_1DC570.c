#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 collision_floor_dynamic_b_full(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
void debris_burst_spawn(struct17 *, s32 *, s32, u8, s32);
void sound_play_for_actor(s32, s32, s32, s32, s32, u8 *);

typedef struct {
    s32 u24;
    s32 u28;
    u8 u2C;
    u8 *u30;
    s8 u34;
    f32 u38;
    f32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    s16 u4C;
    s8 u4E;
    s8 u4F;
    s8 u50;
    s8 u51;
} SpawnAED60;
/* was func_151AED60 */
s32 obj_smoke_trail_start(u8 *arg0, f32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s32 pad;
    SpawnAED60 sp;
    s16 *p2;

    if (arg0 == NULL) {
        return 0;
    }
    node_broadcast_obj_type(0x28, arg0, 0x11);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 1;
    sp.u4E = 2;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    if (arg0) {} // fakematch: with p2 below, puts arg2 in v0
    sp.u40 = 0.0f;
    sp.u44 = 15.400001f;
    sp.u48 = arg1;
    p2 = &arg2; // fakematch: address-taken arg2 (loaded into v0 from its home slot)
    if (*p2 != 0) {
        sp.u4C = *p2;
        sp.u4E = 6;
    } else {
        sp.u4C = 0x12C;
    }
    sp.u4F = 6;
    sp.u50 = -1;
    sp.u51 = 5;
    return emitter_trail_spawn(&sp, 0, arg3, arg4);
}

void smoke_trail_ember_spark(); // K&R: the ref passes the flag unmasked (definition is K&R too)
void smoke_trail_dust_puff(u8 *, f32, f32, f32, u8, u8);

/* was func_151AEE40 */
void smoke_trail_item_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 v[3];
    f32 r;
    s32 a;
    s32 b;

    v[0] = arg0;
    v[1] = arg1;
    v[2] = arg2;
    r = random_float();
    if (!(r < 0.15f)) {
        if (r < 0.25f) {
            a = (random_float() > 0.0f) ? 1 : 0;
            smoke_trail_ember_spark(v, a, arg6[0xC]);
        } else {
            b = (random_float() > 0.80500007f) ? 1 : 0;
            smoke_trail_dust_puff((u8 *)v, arg3, arg4, arg5, b, arg6[0xC]);
        }
    }
}

/* was func_151AEF34 */
void smoke_trail_dust_puff(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s32 pad; // fakematch
    f32 v[3];

    v[0] = -arg1 * 0.10300001f;
    v[1] = -arg2 * 0.10300001f;
    v[2] = -arg3 * 0.10300001f;
    impact_dust_cloud_spawn(arg0, v, 0, (random_float() * 0.60200006f) + -1.0450001f, ((u32)random_int() % 31) + 0x3C, ((u32)random_int() % 101) + 0x9B, (random_float() * 219.0f) + 77.0f, arg4, 1.0f, 1.0f, 0, 0, 1, 0, arg5, 1);
}

s32 impact_spark_spawn(s32, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

void smoke_trail_ember_spark(arg0, arg1, arg2)
    s32 arg0;
    u8 arg1;
    u8 arg2;
{
  f32 sp88[4];
  u8 sp87;
  u8 sp86;
  f32 temp_f12;
  f32 sp7C;
  f32 sp78;
  f32 sp74;
  f32 sp70;
  f32 temp_f2;
  f32 sp68;
  s32 sp64;
  s32 sp60;
  f32 sp5C;
  sp87 = random_int();
  sp86 = ((random_int() & 0x7F) & 0xFFFF) - 0x3F;
  sp7C = angle_byte_cos(sp87);
  sp78 = angle_byte_cos(sp87 - 0x40);
  sp74 = angle_byte_cos(sp86);
  sp70 = angle_byte_cos(sp86 - 0x40);
  temp_f2 = ((random_float() * 80.0f) + 20.0f) * 0.1f;
  temp_f12 = temp_f2 * sp74;
  sp88[0] = temp_f12 * sp78;
  sp88[1] = (-temp_f2) * sp70;
  sp88[2] = temp_f12 * sp7C;
 dummy_label_888456: ; // fakematch: permuter label (splits the basic block before the rand() calls)
  sp5C = random_float();
  sp60 = random_int();
  sp64 = random_int();
  sp68 = random_float();
  impact_spark_spawn(arg0, sp88, (sp5C * 0.40600002f) + 0.21000001f, (s16) ((((u32) sp60) % 41U) + 0x3C), (((u32) sp64) % 101U) + 0x9B, (sp68 * 4.0f) + 3.1000001f, (random_int() % 5U) + 3, (s32) arg1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, (s32) arg2, 1);
}

void hitinfo_from_obj_floor(void *, u8 *);
void emit_sparks_in_angle_range(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
s32 collision_floor_probe(f32 *, s32, f32, f32 *);
s32 impact_debris_spawn(u8 arg0, f32 arg1, u8 arg2, s32 arg3, struct17 *arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);
void impact_splash_ring_spawn(u8, f32, u8, f32 *, u8, u8, s32);
s32 fx_splash_spawn(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);

// ground_burst_spawn: spawns a burst effect at obj's position (+0x14): the emit_sparks_in_angle_range cloud (sizes 5.08 / 3.02,
// alpha 0.807 / 0.701, speeds 18 / 11.8), then 7..12 debris pieces in a ring of radius 90..149 at a random angle,
// each dropped onto the floor below (collision_floor_probe from 100 above down to 500 below; stops on no floor or floor type
// 3): odd random -> impact_debris_spawn (size 15..19.5, alpha 155..255, on the floor normal), even -> impact_splash_ring_spawn (size
// 6.1..12), and finally one fx_splash_spawn splash on the floor under obj (scale (90..120) / 1000, colour 155..255 /
// 100..200, life 70..125). room / owner are passed to every spawn.
/* was func_151AECA0 */
void ground_burst_spawn(u8 *obj, u8 room, s32 owner) {
    f32 floor[9];          // floor probe: height, normal (+4), type byte +0x1D
    struct_eu_15154488 fx;
    f32 probe[3];
    f32 piece[3];
    f32 base[3];
    f32 under[3];
    f32 size;
    f32 shade;
    s32 r;
    u32 a;
    u32 b;
    u32 c;
    u32 n;

    if (obj == NULL) {
        return;
    }
    hitinfo_from_obj_floor(floor, obj);
    fx.unk8.unk0 = *(f32 *) (obj + 0x14);
    fx.unk8.unk4 = *(f32 *) (obj + 0x18);
    fx.unk8.unk8 = *(f32 *) (obj + 0x1C);
    fx.unk14 = 5.08f;
    fx.unk18 = 3.02f;
    fx.unk1C = 0.80700004f; // 0x3F4E978E
    fx.unk20 = 0.70100003f; // 0x3F3374BD
    fx.unk24 = 18.0f;
    fx.unk28 = 11.8f;
    fx.unk2C = 0xA;
    fx.unk2E = 0;
    fx.unk0 = 0;
    fx.unk2 = 0xFF;
    fx.unk4 = -0x3F;
    fx.unk6 = 0x2D;
    fx.unk30 = 3;
    fx.unk32 = 2;
    fx.unk34 = 0x28;
    fx.unk36 = 0x14;
    fx.unk38 = 0x9B;
    fx.unk3A = 0x64;
    fx.unk44 = 0x10;
    fx.unk46 = 0xF;
    fx.unk48 = 0;
    fx.unk3C = 0;
    fx.unk40 = 0.5f;
    emit_sparks_in_angle_range(&fx, &fx.unk8, (s32) floor, 0xFF, 1);

    n = (u32) random_int() % 6 + 7;
    probe[1] = *(f32 *) (obj + 0x18) + 100.0f;
    for (; n != 0; n--) {
        r = random_int();
        vec2_from_angle_byte(r & 0xFF, random_float() * 59.0f + 90.0f, &piece[0], &piece[2]);
        piece[0] += *(f32 *) (obj + 0x14);
        probe[0] = piece[0];
        piece[2] += *(f32 *) (obj + 0x1C);
        probe[2] = piece[2];
        if (collision_floor_probe(probe, 0, *(f32 *) (obj + 0x18) - 500.0f, floor) == 0 || ((u8 *) floor)[0x1D] == 3) {
            return;
        }
        piece[1] = floor[0] + 10.0f;
        if (random_int() & 1) {
            size = random_float();
            shade = random_float();
            impact_debris_spawn(0, size * 4.5f + 15.0f, (u32) (shade * 100.0f + 155.0f), (s32) &floor[1], (struct17 *) piece,
                          100, 0, 1, 0, room, owner);
        } else {
            size = random_float();
            shade = random_float();
            impact_splash_ring_spawn(0, size * 5.9f + 6.1f, (u32) (shade * 100.0f + 155.0f), piece, 1, room, owner);
        }
    }
    base[0] = *(f32 *) (obj + 0x14);
    base[1] = *(f32 *) (obj + 0x18);
    base[2] = *(f32 *) (obj + 0x1C);
    under[0] = base[0];
    under[1] = base[1] + 100.0f;
    under[2] = base[2];
    if (collision_floor_probe(under, 0, base[1] - 500.0f, floor) == 0 || ((u8 *) floor)[0x1D] == 3) {
        return;
    }
    base[1] = floor[0] + 10.0f;
    size = random_float();
    shade = random_float();
    a = random_int();
    b = random_int();
    c = random_int();
    fx_splash_spawn((size * 30.0f + 90.0f) * 0.001f, (shade * 103.0f + 103.0f) * 1e-05f, a % 101 + 0x9B, b % 101 + 100,
                  c % 0x38 + 0x46, (s32) &floor[1], (struct17 *) base, 0, 1, room, owner);
}

// obj_steam_puff_spawn: plays sound 0x16 on the object (node_broadcast_obj_type) and spawns a 9.8 / 0.143 effect of type 1
// attached to it (emitter_trail_spawn: life 0x140, flags 6 / 10 / -1 / 9) with arg1 / arg2 passed through; NULL object: 0.
/* was func_151AF820 */
s32 obj_steam_puff_spawn(u8 *obj, u8 arg1, s32 arg2) {
    SpawnAED60 sp;

    if (obj == NULL) {
        return 0;
    }
    node_broadcast_obj_type(0x28, obj, 0x16);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = obj[0x3B];
    sp.u30 = obj;
    sp.u34 = 1;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    sp.u40 = 0.0f;
    sp.u44 = 9.8f;
    sp.u48 = 0.143f;
    sp.u4C = 0x140;
    sp.u4E = 6;
    sp.u4F = 10;
    sp.u50 = -1;
    sp.u51 = 9;
    return emitter_trail_spawn(&sp, 0, arg1, arg2);
}

s32 steam_puff_dust_spawn(void *, f32, f32, f32, u8);

/* was func_151AF8E8 */
void steam_puff_item_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6)
{
  f32 new_var[2];
  f32 sp24;
  sp24 = arg0;
  new_var[0] = arg1;
  new_var[1] = arg2;
  steam_puff_dust_spawn(&sp24, arg3, arg4, arg5, (s32) (*((u8 *) (((u8 *) arg6) + 0xC))));
}

/* was func_151AF938 */
s32 steam_puff_dust_spawn(void *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    s32 pad; // fakematch
    f32 v[3];
    u8 flag;
    s32 pad2; // fakematch
    s32 r2;
    s32 r1;
    f32 rf;

    v[0] = -arg1 * 0.13000001f;
    v[1] = -arg2 * 0.13000001f;
    v[2] = -arg3 * 0.13000001f;
    if (random_int() & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    rf = random_float();
    r1 = random_int();
    r2 = random_int();
    return impact_dust_cloud_spawn(arg0, v, 0, (rf * 0.126f) + -0.702f, (r1 & 0xF) + 0xA, ((u32)r2 % 45) + 0x89, (random_float() * 202.0f) + 142.0f, flag, 1.7f, 1.7f, 0, 0, 1, 0, arg4, 1);
}
