#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* gun_muzzle_smoke_spawn's .s owned this rodata (bone-space muzzle points); the NM link drops it, so NM gets copies.
   g_gun_sparks_end_pt is the second point of g_gun_smoke_start_pt (read by gun_muzzle_sparks_spawn); game_eu_51190 has its own copy. */
static const f32 g_gun_smoke_start_pt[6] = { -113.828796f, -14.0823936f, 14.5422001f, -124.648605f, -14.0823936f, 14.5422001f }; /* was D_800AAE70 */
static const f32 g_gun_sparks_end_pt[3] = { -124.648605f, -14.0823936f, 14.5422001f }; /* was D_800AAE7C */
static const f32 g_gun_smoke_end_pt[3] = { 7.31999874f, -14.0823936f, 4.54220057f }; /* was D_800AAE88 */
static const f32 g_gun_smoke_dir_scale[1] = { 0.00100000005f }; /* 0x3A83126F (arrays: IDO puts scalar float statics in .data); was D_800AAE94 */
static const f32 g_gun_smoke_tracer_k[1] = { 0.00333333341f }; /* 0x3B5A740E; was D_800AAE98 */

void obj_get_aim_vectors(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
u8 *attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);
s32 model_node_points_to_world(u8 *, u8 *, s32, f32 **, f32 **, s32);
void gun_muzzle_sparks_spawn(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4);
void gun_muzzle_flash_light(u8 *arg0, u8 arg1, s32 arg2);
u8 *tracer_spawn(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                  f32 argA, u8 argB, u8 *argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, s8 arg13,
                  s32 arg14, f32 arg15, u8 arg16, s8 arg17, s32 arg18, u8 arg19, s32 arg1A);

// gun_muzzle_smoke_spawn: smoke trail from object `obj`'s gun. Direction = the object's facing vector
// (obj_get_aim_vectors) * 0.001. With a model (+0x1D4) the two muzzle points g_gun_smoke_start_pt / g_gun_smoke_end_pt are taken through
// attachment 0x46 (attachment_find_by_slot / model_node_points_to_world; bail out when either fails), then sparks (gun_muzzle_flash_light) and, on a
// random odd value, a flash (gun_muzzle_sparks_spawn); without a model the start is the object position (+0x14) raised by 106
// and pushed 120 along the direction, the end 82 back. Then the smoke stream tracer_spawn (alpha 0xFF with a model,
// else 0x80; mode -1 when D_800BE616 is set, else 2). `flag` / `arg2` are passed on.
/* was func_151C5280 */
void gun_muzzle_smoke_spawn(u8 *obj, u8 flag, s32 arg2) {
    f32 *in[2];
    f32 *out[2];
    f32 a, b;
    u32 r;
    f32 start[3];
    f32 end[3];
    f32 dir[3];
    f32 side[3];
    u8 *att;

    if (obj == NULL) {
        return;
    }
    obj_get_aim_vectors((struct127 *) obj, (s32) dir, (s32) side, 0, 0.0f);
    dir[0] *= g_gun_smoke_dir_scale[0];
    dir[1] *= g_gun_smoke_dir_scale[0];
    dir[2] *= g_gun_smoke_dir_scale[0];
    if (*(u8 **) (obj + 0x1D4) != NULL) {
        in[0] = (f32 *) g_gun_smoke_start_pt;
        in[1] = (f32 *) g_gun_smoke_end_pt;
        out[0] = start;
        out[1] = end;
        att = attachment_find_by_slot(obj, 0x46, 0);
        if (att == NULL) {
            return;
        }
        if (model_node_points_to_world(obj, att, 0, in, out, 2) == 0) {
            return;
        }
        gun_muzzle_flash_light((u8 *) start, flag, arg2);
        if (random_int() & 1) {
            gun_muzzle_sparks_spawn((s32) obj, (s32) start, 0x46, flag, arg2);
        }
    } else {
        start[0] = *(f32 *) (obj + 0x14);
        start[1] = *(f32 *) (obj + 0x18) + 106.0f;
        start[2] = *(f32 *) (obj + 0x1C);
        end[0] = dir[0] * -82.0f + start[0];
        end[1] = dir[1] * -82.0f + start[1];
        end[2] = dir[2] * -82.0f + start[2];
        start[0] -= dir[0] * -120.0f;
        start[1] -= dir[1] * -120.0f;
        start[2] -= dir[2] * -120.0f;
    }
    a = random_float();
    b = random_float();
    r = random_int();
    tracer_spawn((u8 *) start, NULL, (u8 *) end, (u8 *) dir, 1, 0, 300.0f, g_gun_smoke_tracer_k[0], a * 10.0f + 25.0f,
                  b * 150.0f + 400.0f, 80.0f, r % 56 + 200, obj, 1, 1, 0, *(u8 **) (obj + 0x1D4) != NULL ? 0xFF : 0x80,
                  0, 1, 0, 0x1A, 0.0f, 0xFF, D_800BE616 ? -1 : 2, 0, flag, arg2);
}

s32 attached_particle_spawn(s32, s32, f32 *, f32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);

/* was func_151C5B38 */
void gun_muzzle_sparks_spawn(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    f32 s[2];

    s[1] = ((random_float() * 1001.0f) + 604.0f) * 0.01f;
    s[0] = ((random_float() * 59.0f) + 141.0f) * 0.1f;
    attached_particle_spawn(arg0, 0, g_gun_smoke_start_pt, g_gun_sparks_end_pt, s, (random_int() & 3) + 6, (random_int() % 1U) + 0xFF /* fakematch: rand % 1 range-0 rand (folded, call + spill kept) */, (random_float() * 270.0f) + 359.0f, arg1, 0xFF, 0, arg2, arg3, arg4);
}

/* was func_151C5C54 */
void gun_muzzle_flash_light(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (random_int() % 3U) + 3;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    light_create_with_ctrl(sp48, sp3C, (random_int() & 1) + 6, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

s32 particle_spawn_ex(s32 *, s32, s32, s32, s32, s32);
s32 impact_setup_segment(s32 *, s32 *, f32 *, f32 *, f32 *, s32, s32, s32);
void vec3_from_angles_byte(s16, s16, f32, void *);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
s32 impact_spark_spawn(s32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 impact_glow_spawn(s32 *, f32, s32, s16, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

/* was func_151C5D2C */
void impact_glow_sparks_spawn(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    struct {
        f32 uB8;
        s32 uBC;
        s32 uC0;
        s16 uC4;
        s16 uC6;
        s32 uC8;
        s32 uCC;
        s8 uD0;
        s8 uD1;
        s8 uD2;
        s8 uD3;
        s8 uD4;
        s8 uD5;
        s8 uD6;
        s8 uD7;
        s8 uD8;
        s8 uD9;
        s16 uDA;
        s16 uDC;
        s16 uDE;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        u8 padF0[0x8];
        f32 uF8;
        f32 uFC;
        f32 u100;
        s32 u104;
        u8 pad108[0x8];
        f32 u110;
        s32 u114;
        u8 pad118[0x4];
        s8 u11C;
        s8 u11D;
        s8 u11E;
        s8 u11F;
        s8 u120;
        s8 u121;
        u8 pad122[0xE];
        f32 u130;
        f32 u134;
        f32 u138;
        u8 pad13C[0x8];
        f32 u144;
        f32 u148;
        f32 u14C;
        f32 u150;
        f32 u154;
        u8 pad158[0x4];
        f32 u15C;
        f32 u160;
        f32 u164;
        f32 u168;
        f32 u16C;
        f32 u170;
        f32 u174;
        f32 u178;
        f32 u17C;
        s32 u180;
        u8 pad184[0x8];
        s32 u18C;
    } sp;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s16 temp_v1;
    s16 var_s2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_s1_4;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2_2;
    s32 var_s2_3;
    u32 temp_hi;

    if (impact_setup_segment(&sp.u18C, &sp.u180, &sp.u174, &sp.u168, &sp.u15C, arg0, arg1, arg2) != 0) {
        temp_f22 = random_float();
        temp_s1 = random_int();
        impact_glow_spawn(&sp.u18C, (temp_f22 * 24.0f) + 168.0f, (((u32) temp_s1 % 101U) + 0x9B) & 0xFF, (s16) ((random_int() & 7) + 0xF), 1, (s32) arg6, arg7);
        if (arg4 != 0) {
            temp_v1 = (random_int() % 3U) + 5;
            var_s2 = temp_v1;
            if (temp_v1 != 0) {
                do {
                    temp_f20 = ((random_float() * 33.0f) + 60.0f) * 0.1f;
                    vec2_from_angle_byte((s16) (random_int() & 0xFF), temp_f20, &sp.u150, &sp.u154);
                    sp.u144 = (sp.u168 * sp.u150) + (sp.u15C * sp.u154);
                    sp.u148 = (sp.u16C * sp.u150) + (sp.u160 * sp.u154);
                    sp.u14C = (sp.u170 * sp.u150) + (sp.u164 * sp.u154);
                    temp_f20_2 = random_float();
                    temp_s0 = random_int();
                    temp_s1_2 = random_int();
                    temp_f22_2 = random_float();
                    random_int();
                    impact_spark_spawn(&sp.u18C, &sp.u144, (temp_f20_2 * 0.162f) + 0.193f, (s16) (((u32) temp_s0 % 9U) + 0x12), ((u32) temp_s1_2 % 156U) + 0x64, (temp_f22_2 * 4.0f) + 4.0f, 3, 0, 1.0f, 1.0f, 1, 1, 0, 0x10, 0xF, 0, (s32) arg6, arg7);
                    var_s2 -= 1;
                } while (var_s2 != 0);
            }
        }
        if (arg3 != 0) {
            var_s2_2 = (random_int() % 6U) + 5;
            if (var_s2_2 != 0) {
                do {
                    temp_f2 = ((random_float() * 150.0f) + 200.0f) * 0.1f;
                    sp.u130 = sp.u174 * temp_f2;
                    sp.u134 = sp.u178 * temp_f2;
                    sp.u138 = sp.u17C * temp_f2;
                    temp_f20_3 = random_float();
                    temp_s1_3 = random_int();
                    temp_s0_2 = random_int();
                    impact_dust_cloud_spawn(&sp.u180, &sp.u130, 1U, (temp_f20_3 * 0.68200004f) + -0.41200003f, (s16) (((u32) temp_s1_3 % 11U) + 5), (u8) (((u32) temp_s0_2 % 156U) + 0x64), (random_float() * 60.0f) + 80.0f, 0U, 1.0f, 1.0f, 1U, 0, 1U, 0U, (u8) (s32) arg6, arg7);
                    var_s2_2 -= 1;
                } while (var_s2_2 != 0);
            }
        }
        if (arg5 != 0) {
            temp_hi = random_int() % 7U;
            sp.uD9 = 0x6C;
            sp.uC4 = 0x5103;
            sp.uBC = 0x200005;
            sp.uDA = 0x14;
            sp.uDC = 0xC;
            sp.u114 = 0x80D207;
            sp.u11C = 8;
            sp.u11D = 6;
            sp.u11E = 0x10;
            sp.u120 = -1;
            sp.uC0 = 0;
            sp.uC8 = 0;
            sp.uCC = 0;
            sp.u11F = -1;
            sp.u121 = 0;
            sp.uDE = 1;
            sp.uE0 = 1.0f;
            sp.uD0 = 0xE2;
            sp.uD1 = 0xB2;
            sp.uD2 = 0x60;
            sp.uD3 = 0xFF;
            sp.uD4 = 0x39;
            sp.uD5 = 0xF;
            sp.uD6 = 0;
            sp.uD8 = 0xFF;
            sp.uB8 = 0.950865f;
            (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u180) + 0));
            var_s2_3 = temp_hi + 3;
            (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u180) + 4));
            (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u180) + 8));
            sp.uF8 = 0.0f;
            sp.uFC = 0.0f;
            sp.u100 = 0.0f;
            if (var_s2_3 > 0) {
                do {
                    temp_s1_4 = random_int();
                    temp_s0_3 = random_int();
                    vec3_from_angles_byte((s16) (temp_s1_4 & 0xFF), (s16) ((temp_s0_3 & 0x3F) * -1), (random_float() * 7.0f) + 2.0f, &sp.u104);
                    temp_f16 = random_float() * 117.0f;
                    sp.u114 &= ~0xC0;
                    sp.u110 = (temp_f16 + -197.0f) * 0.001f;
                    var_s1 = 0;
                    if (random_int() & 1) {
                        var_s1 = 0x80;
                    }
                    if (random_int() & 1) {
                        var_s0 = 0x40;
                    } else {
                        var_s0 = 0;
                    }
                    sp.u114 |= var_s0 | var_s1;
                    sp.uD7 = (random_int() % 66U) + 0xBE;
                    sp.uC6 = (random_int() % 45U) + 0x2C;
                    temp_f2_2 = (random_float() * 122.0f) + 77.0f;
                    sp.uE4 = temp_f2_2;
                    sp.uE8 = temp_f2_2;
                    temp_v0 = particle_spawn_ex(&sp.uBC, 1, 0, 4, (s32) arg6, arg7);
                    if (temp_v0 != 0) {
                        memcpy(temp_v0 + 0xA8, &sp.uB8, 4);
                    }
                    var_s2_3 -= 1;
                } while (var_s2_3 != 0);
            }
        }
    }
}
void bone_emitter_spark_params(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);
/* was func_151C6424 */
void bone_emitter_dust_emit(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 sp54[3];
    f32 sp50;
    s16 sp4E;
    u8 sp4D;
    f32 sp48;

    bone_emitter_spark_params(arg0, arg1, arg2, arg3, arg4, arg5, sp6C, sp60, sp54, &sp50, &sp4E, &sp4D, &sp48);
    impact_dust_cloud_spawn(sp6C, sp54, 1, sp50, sp4E, sp4D, sp48, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}

/* particle_spawn_ex's sprite particle template (same layout as SprTmpl5268 in game_eu_101080) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 flags;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[8]; /* 7 bytes, alpha */
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 sprite;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 u3C[3];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 mode;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[7];
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 u68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 u6C;
} SprTmpl64F4;

/* the 8-byte record copied to the particle's +0xB0 */
typedef struct {
    u8 u0;
    u8 u1;
    u8 pad2[2];
    f32 u4;
} DebrisExtra64F4;

// debris_sprite_spawn: spawns one tumbling debris sprite (sprite 0x6C, colour E2 B2 60 FF 39 0F 00 + alpha) with
// particle_spawn_ex at *pos moving with *vel. arg2 goes to template +0x54, spin is stored at the particle's +0xA8,
// the record {1, 0, 0.703} at +0xB0. life -1 = 300 frames (and no mode bit 1), size sets both size fields, bright
// selects u60[2] 0x1D / 0xA; random flip bits 0x40 / 0x80. Callers ignore the returned particle (void here, as in
// every prototype).
/* was func_151C64F4 */
void debris_sprite_spawn(s32 pos, f32 *vel, f32 arg2, f32 spin, s32 alpha, s32 life, f32 size, s32 bright, s32 room,
                   u8 kind, s32 owner) {
    /* one frame record, laid out like the asm's stack (sp30 extra, sp3C spin copy, sp40 template) */
    struct {
        DebrisExtra64F4 extra;
        s32 pad8;
        f32 spin;
        SprTmpl64F4 t;
    } f;
    s32 bit40;
    s32 bit1;
    s32 bit80;
    s32 p;

    f.spin = spin;
    f.t.sprite = 0x6C;
    f.t.flags = 0x5103;
    f.t.u0 = 0x200005;
    f.t.u4 = 0;
    f.t.uC = 0;
    f.t.u10 = 0;
    f.t.u1E = 0x14;
    f.t.u20 = 0xC;
    bit40 = (random_int() & 1) ? 0x40 : 0;
    bit1 = ((s16) life == -1) ? 0 : 1;
    bit80 = (random_int() & 1) ? 0x80 : 0;
    f.t.mode = bit80 | bit1 | 6 | bit40 | 0xC200 | 0x800000;
    f.t.u60[0] = 8;
    f.t.u60[1] = 6;
    f.t.u60[2] = (u8) bright ? 0x1D : 0xA;
    f.t.u22 = 1;
    f.t.u60[3] = 0xFF;
    f.t.u60[4] = 0xFF;
    f.t.u60[5] = 0;
    f.extra.u0 = 1;
    f.extra.u1 = 0;
    f.t.colour[0] = 0xE2;
    f.t.colour[1] = 0xB2;
    f.t.colour[2] = 0x60;
    f.t.colour[3] = 0xFF;
    f.t.colour[4] = 0x39;
    f.t.colour[5] = 0x0F;
    f.t.colour[6] = 0;
    f.t.u1C = 0xFF;
    f.t.u24 = 1.0f;
    f.extra.u4 = 0.703f;
    f.t.pos[0] = ((f32 *) pos)[0];
    f.t.pos[1] = ((f32 *) pos)[1];
    f.t.pos[2] = ((f32 *) pos)[2];
    f.t.u3C[0] = 0.0f;
    f.t.u3C[1] = 0.0f;
    f.t.u3C[2] = 0.0f;
    f.t.vel[0] = vel[0];
    f.t.vel[1] = vel[1];
    f.t.vel[2] = vel[2];
    f.t.u54 = arg2;
    f.t.colour[7] = (u8) alpha;
    if ((s16) life == -1) {
        f.t.life = 300;
    } else {
        f.t.life = (s16) life;
    }
    f.t.size[1] = size;
    f.t.size[0] = size;
    p = particle_spawn_ex((s32 *) &f.t, 1, room, 0x10, kind, owner);
    if (p != 0) {
        memcpy(p + 0xA8, &f.spin, 4);
        memcpy(p + 0xB0, (f32 *) &f.extra, 8);
    }
}

typedef struct {
    s16 n0; s16 n1; s32 p; s16 c; s16 a; s16 d; s16 e;
    f32 f0; f32 f1; f32 f2; f32 f3; f32 f4;
    u8 b0; u8 b1; s16 h0; s16 h1; s16 pad;
    f32 g0; f32 g1; f32 g2; s32 q;
} SpawnC6750;
void emit_rings_random_yaw(SpawnC6750 *, u8, s32);
/* was func_151C6750 */
void hit_debris_ring_burst(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    SpawnC6750 s;

    s.f0 = 5.0f;
    s.n0 = 10;
    s.f1 = 7.0f;
    s.n1 = 4;
    s.p = arg0;
    s.c = 0;
    s.d = 255;
    s.a = -24;
    s.e = 25;
    s.b0 = 0xBE;
    s.b1 = 0x41;
    s.h0 = 0xC8;
    s.h1 = 0x96;
    s.f2 = -0.208f;
    s.f3 = 0.085f;
    s.f4 = 0.970632f;
    s.g0 = 96.0f;
    s.g1 = 109.0f;
    s.g2 = 1.0f;
    s.q = arg1;
    emit_rings_random_yaw(&s, arg2, arg3);
}

/* was func_151C6840 */
s32 obj_kind_can_take_hit(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x5A:
        case 0x74:
        case 0x7A:
            return 0;
        default:
            return 1;
    }
}
