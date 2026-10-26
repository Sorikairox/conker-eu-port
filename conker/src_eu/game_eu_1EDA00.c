#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void impact_debris_emitter_spawn(s32 arg0, u8 arg1, s32 arg2);
void impact_scorch_decal_spawn(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void bullet_hit_mark_spawn(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4);
void explosion_ground_effects(u8 *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4);
// hoisted forward declaration(s) for impact_spark_flash_spawn
s32 spark_shower_spawn(u8 *, f32, f32, f32, f32, u8, s32); /* P95: f32 parameter */
// hoisted forward declaration(s) for impact_effects_basic
void impact_flash_light_spawn(u8 *, u8, s32);
void impact_rumble_spawn(s32, u8, s32);
void impact_cam_shake_spawn(struct17 *, u8, s32);
void emit_spray_along_normal(f32 *, u8, s32);
void impact_spray_params_init(f32 *, f32 *);
void impact_spark_flash_spawn(u8 *, u8, s32);


extern f32 g_impact_spray_param_14; /* was D_800AAD5C */
extern f32 g_impact_spray_param_18; /* was D_800AAD60 */
extern f32 g_impact_spray_param_38; /* was D_800AAD64 */
extern f32 g_impact_spray_param_3c; /* was D_800AAD68 */
extern f32 g_impact_spray_param_40; /* was D_800AAD6C */
/* was func_151C01F0 */
void impact_spray_params_init(f32 *arg0, f32 *arg1) {
    s32 var_v0;
    s32 var_v0_2;

    (*(f32 *)((u8 *)arg0 + 0)) = 4e-45f;
    if (g_last_player_index >= 2) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) (4 >> var_v0);
    *arg1 = 494.0f;
    (*(f32 *)((u8 *)arg0 + 0x14)) = g_impact_spray_param_14;
    (*(s32 *)((u8 *)arg0 + 0x2C)) = 7;
    (*(f32 *)((u8 *)arg0 + 0x18)) = g_impact_spray_param_18;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = 45.0f;
    (*(f32 *)((u8 *)arg0 + 0x20)) = 53.0f;
    (*(f32 *)((u8 *)arg0 + 0x24)) = 203.0f;
    (*(f32 *)((u8 *)arg0 + 0x28)) = 414.0f;
    if ((g_last_player_index >= 2) || (var_v0_2 = 0, ((g_player_count < 8) == 0))) {
        var_v0_2 = 1;
    }
    (*(s32 *)((u8 *)arg0 + 0x30)) = (s32) (3 >> var_v0_2);
    (*(f32 *)((u8 *)arg0 + 0x34)) = 15.0f;
    (*(f32 *)((u8 *)arg0 + 0x38)) = g_impact_spray_param_38;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = g_impact_spray_param_3c;
    (*(s16 *)((u8 *)arg0 + 0x44)) = 0x19;
    (*(s16 *)((u8 *)arg0 + 0x46)) = 0xF;
    (*(s16 *)((u8 *)arg0 + 0x48)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4A)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4C)) = 0xC;
    (*(s16 *)((u8 *)arg0 + 0x4E)) = 0x14;
    (*(f32 *)((u8 *)arg0 + 0x40)) = g_impact_spray_param_40;
    if ((g_last_player_index >= 2) || (g_player_count >= 8)) {
    s32 pad;
        (*(s8 *)((u8 *)arg0 + 0x50)) = -1;
        return;
    }
    (*(s8 *)((u8 *)arg0 + 0x50)) = 0;
}
typedef struct { s32 a[3]; } V3_151C0350;
/* was func_151C0350 */
void impact_effects_basic(u8 *arg0, f32 *arg1, u8 arg2, u8 arg3, s32 arg4) {
    f32 pad[16]; // fakematch: unused frame space
    f32 sp24[9];

    impact_flash_light_spawn(arg0, arg3, arg4);
    impact_spark_flash_spawn(arg0, arg3, arg4);
    impact_rumble_spawn((s32)arg0, arg3, arg4);
    impact_cam_shake_spawn((struct17 *)arg0, arg3, arg4);
    if (arg2 != 0) {
        sp24[0] = -arg1[0];
        sp24[1] = -arg1[1];
        sp24[2] = -arg1[2];
        impact_spray_params_init(&sp24[4], &sp24[3]);
        *(V3_151C0350 *)&sp24[6] = *(V3_151C0350 *)arg0;
        emit_spray_along_normal(sp24, arg3, arg4);
    }
}

/* P159 */
s32 tri_calc_normal(u8 *, f32 *, f32 *, f32 *);
void emit_spray_from_surface(void *, u8, s32);
// impact_effects_spawn: the effects of a hit at pos (impact_flash_light_spawn, impact_spark_flash_spawn, impact_rumble_spawn, impact_cam_shake_spawn).
// With `full` set: when hit (an 0x12-byte surface record) has a downward-facing third axis (tri_calc_normal) also
// impact_debris_emitter_spawn, a burst along it (impact_scorch_decal_spawn), and a spray against dir (emit_spray_from_surface with the surface, else
// emit_spray_along_normal without one), its parameters from impact_spray_params_init.
/* was func_151C0434 */
void impact_effects_spawn(u8 *hit, f32 *pos, f32 *dir, u8 full, u8 arg4, s32 arg5) {
    typedef struct {
        f32 u0;
        s32 u4;
        f32 pos[3];
        u8 rest[0x40];
    } SprayParams; /* filled by impact_spray_params_init (0x54 bytes) */
    struct {
        f32 dir[3];
        u8 hit[0x12];
        u8 pad1E[2];
        f32 range;
        SprayParams p;
    } a; /* emit_spray_from_surface */
    struct {
        f32 dir[3];
        f32 range;
        SprayParams p;
    } b; /* emit_spray_along_normal */
    f32 ax0[3];
    f32 ax1[3];
    f32 ax2[3];
    s32 i;

    impact_flash_light_spawn((u8 *)pos, arg4, arg5);
    impact_spark_flash_spawn((u8 *)pos, arg4, arg5);
    impact_rumble_spawn((s32)pos, arg4, arg5);
    impact_cam_shake_spawn((struct17 *)pos, arg4, arg5);
    if (hit != NULL && full != 0) {
        if (tri_calc_normal(hit, ax0, ax1, ax2) != 0 && ax2[1] < 0.0f) {
            impact_debris_emitter_spawn((s32)pos, arg4, arg5);
        }
    }
    if (hit != NULL && full != 0) {
        impact_scorch_decal_spawn((s32)hit, (s32)pos, arg4, arg5);
    }
    if (full == 0) {
        return;
    }
    if (hit != NULL) {
        a.dir[0] = -dir[0];
        a.dir[1] = -dir[1];
        a.dir[2] = -dir[2];
        for (i = 0; i < 0x12; i++) {
            a.hit[i] = hit[i];
        }
        a.p.pos[0] = pos[0];
        a.p.pos[1] = pos[1];
        a.p.pos[2] = pos[2];
        impact_spray_params_init((f32 *)&a.p, &a.range);
        emit_spray_from_surface(&a, arg4, arg5);
    } else {
        b.dir[0] = -dir[0];
        b.dir[1] = -dir[1];
        b.dir[2] = -dir[2];
        impact_spray_params_init((f32 *)&b.p, &b.range);
        b.p.pos[0] = pos[0];
        b.p.pos[1] = pos[1];
        b.p.pos[2] = pos[2];
        emit_spray_along_normal((f32 *)&b, arg4, arg5);
    }
}

s32 collision_floor_probe(s32 *, s32, f32, f32 *);
void hitinfo_from_obj_floor(void *, u8 *);
void emit_random_sprites(u8 *, u8, s32);

/* was func_151C0648 */
void explosion_ground_effects(u8 *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4) {
    struct {
        s32 u28;
        f32 u2C;
        s32 u30;
        f32 u34;
        s32 u38;
        u8 pad3C[0x1C];
        s32 u58;
        f32 u5C;
        s32 u60;
        s16 u64;
        s16 u66;
        s16 u68;
        s16 u6A;
        s32 u6C;
        s32 u70;
        s32 u74;
        u8 pad78[0x8];
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        s32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        s16 uB0;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        s16 uB8;
        s16 uBA;
        s8 uBC;
    } sp;
    s32 temp_s1;

    temp_s1 = arg3 & 0xFF;
    impact_flash_light_spawn(arg0, temp_s1 & 0xFF, arg4);
    impact_spark_flash_spawn(arg0, temp_s1 & 0xFF, arg4);
    impact_rumble_spawn((s32) arg0, temp_s1 & 0xFF, arg4);
    impact_cam_shake_spawn((struct17 *) arg0, temp_s1 & 0xFF, arg4);
    if (arg2 != 0) {
        sp.u64 = 0;
        sp.u66 = 0xFF;
        sp.u68 = -0x40;
        sp.u6A = 0x47;
        sp.u6C = 6;
        sp.u70 = 4;
        (*(s32 *)((u8 *)(&sp.u74) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)(&sp.u74) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
        (*(s32 *)((u8 *)(&sp.u74) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
        sp.u80 = 23.0f;
        sp.u84 = 30.0f;
        sp.u88 = 45.0f;
        sp.u8C = 53.0f;
        sp.u98 = 7;
        sp.u9C = 3;
        sp.uB0 = 0x19;
        sp.uB2 = 0xF;
        sp.uB4 = 0x64;
        sp.uB6 = 0x64;
        sp.uB8 = 0xC;
        sp.uBA = 0x14;
        sp.uBC = 0;
        sp.u90 = 203.0f;
        sp.u94 = 414.0f;
        sp.uA0 = 15.0f;
        sp.uA4 = 0.87200004f;
        sp.uA8 = -0.39800003f;
        sp.uAC = 0.36400002f;
        emit_random_sprites(&sp.u64, temp_s1 & 0xFF, arg4);
    }
    if ((arg2 != 0) && (arg1 != 0)) {
        sp.u58 = (*(s32 *)((u8 *)arg0 + 0));
        sp.u5C = (*(f32 *)((u8 *)arg0 + 4)) + 100.0f;
        sp.u60 = (*(s32 *)((u8 *)arg0 + 8));
        hitinfo_from_obj_floor(&sp.u34, arg1);
        if (collision_floor_probe(&sp.u58, 0, (*(f32 *)((u8 *)arg0 + 4)) - 1000.0f, &sp.u34) != 0) {
            sp.u28 = sp.u58;
            sp.u2C = sp.u34;
            sp.u30 = sp.u60;
            impact_scorch_decal_spawn((s32) &sp.u38, (s32) &sp.u28, temp_s1 & 0xFF, arg4);
            impact_debris_emitter_spawn((s32) arg0, temp_s1 & 0xFF, arg4);
        }
    }
}
/* was func_151C0894 */
s32 obj_not_listed_check(u8 *arg0, u8 *arg1, s32 arg2, u8 **arg3) {
    u8 i;
    for (i = 0; i < arg2; i++) {
        if (arg0 == arg3[i]) {
            return 0;
        }
    }
    if (arg0 == arg1) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0)) == 0) {
        return 0;
    }
    if ((*(u8 *)((u8 *)arg0 + 4)) == 0xFF) {
        return 0;
    }
    return 1;
}

void fx_scorch_decal_spawn(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);

/* was func_151C0910 */
void impact_scorch_decal_spawn(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = random_float();
    sp40 = random_int();
    fx_scorch_decal_spawn((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (random_int() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

/* was func_151C09C8 */
void impact_flash_light_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (random_int() % 11U) + 0x14;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    light_create_with_ctrl(sp48, sp3C, (random_int() % 121U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

/* was func_151C0AA8 */
void impact_spark_flash_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    f32 temp_f12;
    f32 sp28;
    s32 temp_t7;
    sp28 = random_float();
    temp_t7 = (random_int() % 56U) + 0xC8;
    temp_f12 = sp28 * 4.0f + 14.0f;
    spark_shower_spawn(arg0, temp_f12, 1.1820899f, (f32) (u32) temp_t7, 0.0f, arg1, arg2); /* P95: float literal (asm passes the bits 0x3F974EB9) */
}

void cam_shake_all_players(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);

/* was func_151C0B54 */
void impact_rumble_spawn(s32 arg0, u8 arg1, s32 arg2) {
    cam_shake_all_players(arg0, 800.0f, 2000.0f, 0.0005f, 5, arg1, arg2);
}

/* was func_151C0BA0 */
void impact_cam_shake_spawn(struct17 *arg0, u8 arg1, s32 arg2) {
    rumble_all_players_at(arg0, 800.0f, 2000.0f, 0.0005f, 0xF, 0x14, (s32) arg1, arg2);
}

void fx_debris_emitter_spawn(s32, s16, u8, s32);

/* was func_151C0BF4 */
void impact_debris_emitter_spawn(s32 arg0, u8 arg1, s32 arg2) {
    fx_debris_emitter_spawn(arg0, (s16) ((random_int() % 62U) + 0x78), arg1, arg2);
}

/* P220: readable C for projectile_fire (game_eu_1EDA00, 669 words; analysis P213.md section 3). */
void gun_muzzle_point_get(u8 *arg0, u8 *arg1);
f32 camera_get_yaw_deg(s32 arg0);
s32 objects_hit_by_segment(u8 *, s32 *, u8 *, s8, s32);
s32 bullet_trace_path(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void vec3_to_yaw_pitch_deg(f32 *, f32 *, f32 *);
s32 mdl_particle_spawn(f32 *, s32, s32, s32, s32, s32);
void *memcpy(void *, const void *, s32);
s32 bullet_smoke_puff_spawn(u8 *obj);
u8 *bullet_glow_spawn(u8 *arg0);
s32 bullet_smoke_emitter_spawn(u8 *arg0, u8 arg1, s32 arg2);
u16 sfx_emitter_start(u16, s16, s16, s16, s32, u16, s16, s32, void *, s32, s32, s32);
s32 bullet_sound_pos_update(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6);
void mtx_transform_points(f32 **, f32 **, void *, s32);
s32 attached_particle_spawn(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void flip_sprite_particle_spawn(s16, u8, f32, u8 *, u8, u8, s32);
void muzzle_flash_light_spawn(u8 *, u8, s32);
f32 random_float(void);
s32 random_int(void);
f32 sinf(f32);
f32 cosf(f32);
extern f32 g_proj_muzzle_pt1[3]; /* muzzle flash points in the gun model's space: {3, 125, 35}; was D_800AAD10 */
extern f32 g_proj_muzzle_pt2[3]; /* {6, -50, 35}; was D_800AAD1C */
extern f32 g_proj_muzzle_pt3[3]; /* {3, 200, 35}; was D_800AAD28 */

#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define SH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

// projectile_fire: fires a bullet from obj (aimed at target's / obj's aim point, or along obj's facing): finds the
// muzzle position, traces the shot (objects_hit_by_segment + bullet_trace_path), spawns the bullet particle (mdl_particle_spawn, kind 3)
// with a 0xD0-byte payload at particle +0x170 (path state, owner, the arg2 record, sound / smoke / trail handles), then
// shows the muzzle flash on obj's gun model. arg3 is stored at payload +0x92; arg4 / arg5 are the usual layer args.
// Returns 0 (the asm returns a callee's leftover v0; the callers ignore it).
/* was func_151C0698 */
s32 projectile_fire(struct127 *obj, struct127 *target, s32 *arg2, u8 arg3, u8 arg4, s32 arg5) {
    f32 pos[3];        /* sp260: muzzle */
    f32 aim[3];        /* sp248: aim point (aimer's ctl +0x13C) */
    f32 aimDir[3];     /* sp23C: aimer's ctl +0x130 */
    f32 dir[3];        /* sp254: facing direction (no aimer) */
    f32 unused[5];     /* sp218: obj_get_aim_vectors's second output */
    s32 head[0x19];    /* sp2A4: 0x64 bytes of path state from bullet_trace_path */
    s32 hit[9];        /* sp270 */
    f32 hitPos[3];     /* sp294 */
    f32 hitDist = 0.0f; /* sp2A0 */
    s32 payload[0x34]; /* sp148: 0xD0 bytes copied to the particle at +0x170 */
    s32 spec[0x1F];    /* spCC: 0x7C-byte spawn spec for mdl_particle_spawn */
    u8 *ctl;
    struct127 *aimer;
    s32 aiming;
    s32 trace;
    u8 *particle;

    if (g_mp_mode_active != 0) {
        if (W(obj, 0x1D4) != 0) {
            gun_muzzle_point_get((u8 *)obj, (u8 *)pos);
        } else {
            pos[0] = F(obj, 0x14);
            pos[1] = F(obj, 0x18) + 65.0f;
            pos[2] = F(obj, 0x1C);
        }
    } else {
        u8 *held = (u8 *)W(obj, 0x318);
        f32 *hand;
        ctl = (u8 *)W(obj, 0x31C);
        hand = (f32 *)(ctl + 0x13C);
        if (held != NULL && B(obj, 0x65) != 0) {
            pos[0] = hand[0];
            pos[1] = hand[1] + -13.0f;
            pos[2] = hand[2];
        } else if (held != NULL && B(ctl, 0x197) != 0) {
            f32 a = camera_get_yaw_deg(B(held, 0x23D)) * 0.017453292f; /* D_800AAD7C */
            pos[0] = cosf(a) * 25.0f + hand[0];
            pos[1] = hand[1];
            pos[2] = hand[2] - sinf(a) * 25.0f;
        } else if (W(obj, 0x1D4) != 0) {
            gun_muzzle_point_get((u8 *)obj, (u8 *)pos);
        } else {
            pos[0] = F(obj, 0x14);
            pos[1] = F(obj, 0x18) + 65.0f;
            pos[2] = F(obj, 0x1C);
        }
    }

    ctl = (u8 *)W(obj, 0x31C);
    if ((ctl != NULL && B(ctl, 0x197) != 0) || target != NULL) {
        aimer = (target != NULL) ? target : obj;
        aiming = 1;
        ctl = (u8 *)W(aimer, 0x31C);
        W(aim, 0) = W(ctl, 0x13C);
        W(aim, 4) = W(ctl, 0x140);
        W(aim, 8) = W(ctl, 0x144);
        aimDir[0] = F(ctl, 0x130);
        aimDir[1] = F(ctl, 0x134);
        aimDir[2] = F(ctl, 0x138);
    } else {
        obj_get_aim_vectors(obj, (s32)dir, (s32)unused, 0, 0.0f);
        dir[0] *= 0.001f; /* D_800AAD80 */
        dir[1] *= 0.001f;
        dir[2] *= 0.001f;
        aiming = 0;
    }

    if (g_level_id == 0x24) {
        trace = 0;
    } else {
        trace = objects_hit_by_segment(aiming ? (u8 *)aim : (u8 *)pos, aiming ? (s32 *)aimDir : (s32 *)dir, (u8 *)obj, 3,
                              (s32)arg2);
    }
    if (bullet_trace_path((u8 *)head, (u8 *)pos, aiming ? NULL : (u8 *)dir, aiming ? (u8 *)aim : NULL,
                      aiming ? (u8 *)aimDir : NULL, (s32)obj, (s32)arg2, (s32)hitPos, (s32)&hitDist, (s32)hit,
                      trace) == 0) {
        return 0;
    }

    /* payload (sp148) */
    {
        s32 i;
        for (i = 0; i < 0x19; i++) {
            payload[i] = head[i];
        }
    }
    W(payload, 0xCC) = trace; /* the objects_hit_by_segment hit (bullet_update passes it to ray_cast_world) */
    W(payload, 0x80) = 0; /* sound */
    W(payload, 0x84) = 0; /* smoke */
    /* spawn spec (spCC) */
    F(spec, 0x00) = 1.0f;
    F(spec, 0x04) = 1.0f;
    F(spec, 0x08) = 0.047000002f; /* D_800AAD84 (0x3D408313) */
    F(spec, 0x0C) = 0.047000002f;
    F(spec, 0x10) = 0.0f;
    F(spec, 0x14) = 0.0f;
    F(spec, 0x18) = 0.0f;
    F(spec, 0x1C) = 1.0f;
    F(spec, 0x20) = 1.0f;
    F(spec, 0x24) = 1.0f;
    W(spec, 0x28) = W(pos, 0);
    W(spec, 0x2C) = W(pos, 4);
    W(spec, 0x30) = W(pos, 8);
    F(spec, 0x4C) = 0.0f;
    W(spec, 0x50) = 0x500920;
    SH(spec, 0x54) = 0x12C;
    SH(spec, 0x56) = 0x2F;
    B(spec, 0x58) = 1;
    W(payload, 0x6C) = (s32)obj;
    W(payload, 0x70) = arg2[0];
    W(payload, 0x74) = arg2[1];
    W(payload, 0x78) = arg2[2];
    W(payload, 0x7C) = arg2[3];
    F(payload, 0x94) = hitDist * 0.005f; /* D_800AAD88 */
    W(payload, 0x98) = W(hitPos, 0);
    W(payload, 0x9C) = W(hitPos, 4);
    W(payload, 0xA0) = W(hitPos, 8);
    B(payload, 0xC8) = (hitDist == 0.0f) ? 0 : 1;
    {
        s32 i;
        for (i = 0; i < 9; i++) {
            W(payload, 0xA4 + i * 4) = hit[i];
        }
    }
    F(payload, 0x68) = 200.0f; /* speed */
    F(spec, 0x34) = F(payload, 0x38) * 200.0f;
    F(spec, 0x38) = F(payload, 0x3C) * 200.0f;
    F(spec, 0x3C) = F(payload, 0x40) * 200.0f;
    vec3_to_yaw_pitch_deg((f32 *)((u8 *)spec + 0x34), (f32 *)((u8 *)spec + 0x14), (f32 *)((u8 *)spec + 0x10));
    F(spec, 0x18) = 0.0f;
    F(payload, 0x64) = F(payload, 0x04) * 0.005f; /* D_800AAD8C */
    W(spec, 0x5C) = 0;
    B(spec, 0x60) = 0xFF;
    B(spec, 0x61) = 0xA;
    B(spec, 0x62) = 0;
    B(spec, 0x63) = 0;
    B(spec, 0x64) = 0;
    B(spec, 0x65) = 0;
    B(spec, 0x66) = 0;
    B(spec, 0x67) = 0;
    B(spec, 0x68) = 2;
    B(spec, 0x6A) = 2;
    W(spec, 0x6C) = 0;
    B(spec, 0x70) = 0;
    SH(spec, 0x72) = 1;
    SH(spec, 0x74) = 0xFF;
    F(spec, 0x40) = 0.0f;
    F(spec, 0x44) = 0.0f;
    F(spec, 0x48) = 0.0f;
    B(payload, 0x92) = arg3;

    particle = (u8 *)mdl_particle_spawn((f32 *)spec, 3, 0xFF, 0xD0, arg4, arg5);
    if (particle != NULL) {
        u8 *p = particle + 0x170;
        s32 hdr[2];     /* spBC: 8-byte particle header */
        s32 hpos[3];    /* spB0 */
        s32 r;
        memcpy(p, payload, 0xD0);
        hpos[0] = (s32)pos[0];
        hpos[1] = (s32)pos[1];
        hpos[2] = (s32)pos[2];
        B(hdr, 0) = 2;
        B(hdr, 1) = 0xFF;
        SH(hdr, 2) = 0x12C;
        B(hdr, 4) = 0;
        W(p, 0x80) = (s32)light_create_with_ctrl((Header *)hdr, (Header2 *)hpos, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg4, arg5);
        W(p, 0x84) = bullet_smoke_puff_spawn(particle);
        r = random_int();
        H(p, 0x90) = sfx_emitter_start((u32)r % 3 + 0x2EE, (s16)(s32)pos[0], (s16)(s32)pos[1], (s16)(s32)pos[2], 0x7530,
                                   0x3E8, 0x1F4, (s32)bullet_sound_pos_update, particle, 0, 4, 0);
        W(p, 0x88) = (s32)bullet_glow_spawn(particle);
        if (g_last_player_index < 2 && g_player_count < 4) {
            W(p, 0x8C) = bullet_smoke_emitter_spawn(particle, arg4, arg5);
        } else {
            W(p, 0x8C) = 0;
        }
    } else {
        /* the payload's handles are still 0 here: never taken */
        if (W(payload, 0x80) != 0) {
            node_destroy((struct102 *)W(payload, 0x80));
        }
        if (W(payload, 0x84) != 0) {
            node_destroy((struct102 *)W(payload, 0x84));
        }
    }

    /* muzzle flash on the gun model (obj +0x1D4, matrix at +0x240) */
    if (W(obj, 0x1D4) == 0 || (B(obj, 0x74) & 0xF) == 0xF || B(obj, 4) == 0x77 || B(obj, 4) == 0x28) {
        return 0;
    }
    {
        f32 c1[3], c2[3], c3[3]; /* spA4, sp98, sp8C */
        f32 size[2];             /* sp84 */
        f32 w1[3], w2[3];        /* sp78, sp6C: c1 / c2 in world space */
        f32 *in[2];              /* sp64 */
        f32 *out[2];             /* sp5C */
        s32 r1, r2;
        f32 rf;
        c1[0] = g_proj_muzzle_pt1[0]; c1[1] = g_proj_muzzle_pt1[1]; c1[2] = g_proj_muzzle_pt1[2];
        c2[0] = g_proj_muzzle_pt2[0]; c2[1] = g_proj_muzzle_pt2[1]; c2[2] = g_proj_muzzle_pt2[2];
        c3[0] = g_proj_muzzle_pt3[0]; c3[1] = g_proj_muzzle_pt3[1]; c3[2] = g_proj_muzzle_pt3[2];
        size[0] = random_float() * 10.0f + 25.0f;
        size[1] = random_float() * 1.0090001f + 2.013f; /* D_800AAD90 (0x3F8126EA), D_800AAD94 */
        in[0] = c1;
        in[1] = c2;
        out[0] = w1;
        out[1] = w2;
        mtx_transform_points(in, out, (u8 *)W(obj, 0x1D4) + 0x240, 2);
        r1 = random_int();
        r2 = random_int();
        rf = random_float();
        attached_particle_spawn(obj, 9, (u8 *)c1, (s32 *)c3, size, (u32)r1 % 3 + 8, (u32)r2 % 0x38 + 0xC8,
                      rf * 204.0f + 601.0f /* D_800AAD98 */, w1, 0xFF, 0, -1, arg4, arg5);
        r1 = random_int();
        r2 = random_int();
        rf = random_float();
        flip_sprite_particle_spawn((u32)r1 % 3 + 8, (u32)r2 % 0x38 + 0xC8, rf * 204.0f + 601.0f /* D_800AAD9C */, (u8 *)w2, 0xFF,
                      arg4, arg5);
        muzzle_flash_light_spawn((u8 *)w2, arg4, arg5);
    }
    return 0;
}
#undef B
#undef H
#undef SH
#undef W
#undef F

/* was func_151C16BC */
s32 bullet_sound_pos_update(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && (*arg2 != 0)) {
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x38));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x3C));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x40));
        return 0;
    }
    *arg6 = 0;
    return 0;
}

void explosion_sfx_play(s32, f32, f32, f32, s32);
s32 ray_cast_world(s32, f32, f32, f32, f32, f32, f32, s32 *, f32, s32, s32, s32, s32, u8 *, s32);
void debris_burst_spawn(u8 *, u8 *, s32, u8, s32);
void impact_effects_spawn(u8 *, f32 *, f32 *, u8, u8, s32);

/* was func_151C1730 */
s32 bullet_update(u8 *arg0) {
    struct {
        s32 u64;
        u8 pad68[0x4];
        s32 u6C;
        s32 u70;
        s32 u74;
        u8 pad78[0x45];
        s32 uBD;
        u8 padC1[0x7];
        s32 uC8;
        s32 uCC;
        s32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
    } sp;
    f32 *sp54;
    u8 *sp50;
    f32 *temp_a1;
    f32 *temp_v0;
    f32 temp_f0;
    f32 var_f0;
    u8 *temp_a0;
    u8 *temp_v0_2;
    u8 *temp_v1;
    u8 *var_s0;

    var_s0 = arg0 + 0x170;
    if ((*(f32 *)((u8 *)arg0 + 0x1D4)) < g_frame_step_f) {
        var_s0 = arg0 + 0x170;
        var_f0 = (*(f32 *)((u8 *)var_s0 + 0x68)) * (*(f32 *)((u8 *)var_s0 + 0x64));
    } else {
        var_f0 = (*(f32 *)((u8 *)var_s0 + 0x68)) * g_frame_step_f;
    }
    sp.uD4 = (*(f32 *)((u8 *)var_s0 + 0x38)) * var_f0;
    sp.uD8 = (*(f32 *)((u8 *)var_s0 + 0x3C)) * var_f0;
    sp.uDC = (*(f32 *)((u8 *)var_s0 + 0x40)) * var_f0;
    if (g_level_bullet_hit_cb != NULL) {
        sp.uE0 = var_f0;
        var_f0 = sp.uE0;
        if (((s32 (*)(u8 *, f32 *, s32 *)) g_level_bullet_hit_cb)(arg0 + 0x38, &sp.uD4, &sp.uC8) != 0) {
            explosion_sfx_play(0, sp.uC8, sp.uCC, sp.uD0, 0);
            temp_a1 = var_s0 + 0x38;
            sp54 = temp_a1;
            bullet_hit_mark_spawn((u8 *) &sp.uC8, (s32) temp_a1, (*(s32 *)((u8 *)var_s0 + 0x6C)), (*(u8 *)((u8 *)var_s0 + 0x92)), 0);
            impact_effects_basic((u8 *) &sp.uC8, sp54, (((*(u8 *)((u8 *)var_s0 + 0xC8)) & 1) == 0) & 0xFF, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            return 0;
        }
    }
    if (var_f0 != 0.0f) {
        ray_cast_world((*(s32 *)((u8 *)var_s0 + 0x6C)), (*(f32 *)((u8 *)arg0 + 0x38)), (*(f32 *)((u8 *)arg0 + 0x3C)), (*(f32 *)((u8 *)arg0 + 0x40)), sp.uD4, sp.uD8, sp.uDC, &sp.u64, var_f0, 1, 0, 1, 3, var_s0 + 0x70, (*(s32 *)((u8 *)var_s0 + 0xCC)));
        if ((s32) sp.uBD >= 2) {
            explosion_sfx_play(1, sp.u6C, sp.u70, sp.u74, 0);
            bullet_hit_mark_spawn((u8 *) &sp.u6C, (s32) (var_s0 + 0x38), (*(s32 *)((u8 *)var_s0 + 0x6C)), (*(u8 *)((u8 *)var_s0 + 0x92)), 0);
            explosion_ground_effects(&sp.u6C, sp.u64, (((*(u8 *)((u8 *)var_s0 + 0xC8)) & 1) == 0) & 0xFF, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            return 0;
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x44)) * g_frame_step_f));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x48)) * g_frame_step_f));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + ((*(f32 *)((u8 *)arg0 + 0x4C)) * g_frame_step_f));
    if ((*(u8 *)((u8 *)var_s0 + 0xC8)) & 1) {
        temp_f0 = (*(f32 *)((u8 *)var_s0 + 0x94));
        if (temp_f0 > 0.0f) {
            (*(f32 *)((u8 *)var_s0 + 0x94)) = (f32) (temp_f0 - g_frame_step_f);
            if ((*(f32 *)((u8 *)var_s0 + 0x94)) <= 0.0f) {
                debris_burst_spawn(var_s0 + 0x98, var_s0 + 0xA4, 2, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
        }
    }
    (*(f32 *)((u8 *)var_s0 + 0x64)) = (f32) ((*(f32 *)((u8 *)var_s0 + 0x64)) - g_frame_step_f);
    if ((*(f32 *)((u8 *)var_s0 + 0x64)) <= 0.0f) {
        if ((*(u8 *)((u8 *)var_s0 + 0x59)) == 1) {
            explosion_sfx_play(0, (*(s32 *)((u8 *)var_s0 + 8)), (*(s32 *)((u8 *)var_s0 + 0xC)), (*(s32 *)((u8 *)var_s0 + 0x10)), 0);
            temp_a0 = var_s0 + 8;
            temp_v0 = var_s0 + 0x44;
            sp54 = temp_v0;
            sp50 = temp_a0;
            bullet_hit_mark_spawn(temp_a0, (s32) (var_s0 + 0x38), (*(s32 *)((u8 *)var_s0 + 0x6C)), (*(u8 *)((u8 *)var_s0 + 0x92)), (s32) temp_v0);
            impact_effects_spawn((u8 *) sp54, (f32 *) sp50, (f32 *) (arg0 + 0x44), (((*(u8 *)((u8 *)var_s0 + 0xC8)) & 1) == 0) & 0xFF, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        }
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)var_s0 + 0x80));
    if (temp_v1 != NULL) {
        (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0x14))) + 0xE)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0x14))) + 0x10)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x3C));
        (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0x14))) + 0x12)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x40));
    }
    temp_v0_2 = (*(u8 **)((u8 *)var_s0 + 0x84));
    if (temp_v0_2 != NULL) {
        (*(f32 *)((u8 *)temp_v0_2 + 0x40)) = (f32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(f32 *)((u8 *)temp_v0_2 + 0x44)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
        (*(f32 *)((u8 *)temp_v0_2 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x40));
    }
    return 1;
}
void sfx_emitter_stop_by_callback(s32, s32, s32);

/* was func_151C1B20 */
void bullet_free_attachments(void * arg0_p) {
    u8 * arg0 = (u8 *) arg0_p;
    u8 *sp1C;
    s32 temp_v1;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    struct102 *temp_t7;
    u8 *temp_a1;

    temp_t7 = (*(struct102 **)((u8 *)arg0 + 0x1F0));
    if (temp_t7 != NULL) {
        node_destroy(temp_t7);
    }
    temp_a0 = (*(struct102 **)((u8 *)arg0 + 0x1F4));
    temp_a1 = arg0 + 0x170;
    if (temp_a0 != NULL) {
        sp1C = temp_a1;
        node_destroy(temp_a0);
    }
    temp_v1 = (*(s32 *)((u8 *)temp_a1 + 0x88));
    if (temp_v1 != 0) {
        *(s32 *)(temp_v1 + 0x110) = 0;
    }
    temp_a0_2 = (*(struct102 **)((u8 *)temp_a1 + 0x8C));
    if (temp_a0_2 != NULL) {
        node_destroy(temp_a0_2);
    }
    sfx_emitter_stop_by_callback(bullet_sound_pos_update, arg0, 0);
}
void bullet_free_attachments(void *arg0);
void mdl_particle_die_retire(void *arg0);
void mdl_particle_die_free(void *arg0);

/* was func_151C1BAC */
void bullet_retire(void *arg0) {
    bullet_free_attachments(arg0);
    mdl_particle_die_retire(arg0);
}

/* was func_151C1BD8 */
void bullet_delete(void *arg0) {
    bullet_free_attachments(arg0);
    mdl_particle_die_free(arg0);
}

s32 object_effects_at(u8 *, s32, s32, s32, s32, s32, s32, s32);
void object_effect_at(u8 *, s32, s32, s32, s32);
extern s32 (*g_level_point_hit_cb)(s32, s32, s32); /* was D_800E0D64 */

/* was func_151C1C04 */
void bullet_hit_mark_spawn(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    if (g_level_point_hit_cb != NULL) {
        g_level_point_hit_cb((s32) (*(f32 *)((u8 *)arg0 + 0)), (s32) (*(f32 *)((u8 *)arg0 + 4)), (s32) (*(f32 *)((u8 *)arg0 + 8)));
    }
    switch (arg3) {                                 /* irregular */
    case 1:
        object_effect_at(arg0, arg1, arg2, arg4, 0x24);
        return;
    case 2:
        object_effect_at(arg0, arg1, arg2, arg4, 0x25);
        return;
    case 3:
        object_effects_at(arg0, arg1, arg2, 0, arg4, 0x16, 0x26, 0);
        return;
    default:
    case 0:
        object_effects_at(arg0, arg1, arg2, 0, arg4, 0x16, 0x15, 0);
        return;
    }
}

extern u8 g_gun_muzzle_bones[]; /* was D_800AAD34 */
extern u8 g_gun_muzzle_offsets[][12]; /* was D_800AAD38 */
/* was func_151C1D48 */
void gun_muzzle_point_get(u8 *arg0, u8 *arg1) {
    s32 var_v0;
    u8 temp_v0;
    u8 *p = arg0;
    temp_v0 = p[4];
    if (temp_v0 != 0x28) {
        if (temp_v0 != 0x77) {
            var_v0 = 0;
        } else {
            var_v0 = 1;
        }
    } else {
        var_v0 = 2;
    }
    mtx_transform_point_or_origin(g_gun_muzzle_offsets[var_v0], arg1, *(s32 *)(p + 0x1D4) + (g_gun_muzzle_bones[var_v0] << 6));
}

/* was func_151C1DC4 */
void bullet_on_obj_replaced(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 *temp_v0 = (s32 *)(arg0 + 0x170);

    if (arg2 == 0x2D) {
        if (arg1[0] == temp_v0[0x1B]) {
            temp_v0[0x1B] = arg1[1];
        } else if (arg1[1] == temp_v0[0x1B]) {
            temp_v0[0x1B] = arg1[0];
        }
    }
}

/* was func_151C1E10 */
void muzzle_flash_light_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (random_int() % 5U) + 5;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    light_create_with_ctrl(sp48, sp3C, (random_int() % 11U) + 5, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

s32 obj_not_listed_check();

/* P159 */
// object_filter_not_listed: target filter 3 of g_ray_filter_fns (objects_hit_by_segment, ray_cast_world): returns obj_not_listed_check's
// result (the N64 code leaves it in v0; the matching C is void, which breaks a call through the s32 table on wasm).
/* was func_151C1EF0 */
s32 object_filter_not_listed(s32 arg0, s32 arg1, s32 *arg2) {
    return obj_not_listed_check(arg0, arg1, *arg2, arg2 + 1);
}

s32 vec3_normalize_len(u8 *, u8 *, u8 *, s32);
s32 ray_cast_through_passable(s32, u8 *, f32 *, u8 *, f32, s32, s32, s32, s8, u8 *, f32 *, f32 *, u8 *, s32);

/* was func_151C1F1C */
s32 bullet_trace_path(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    u8 sp57;
    u8 sp56;
    s32 var_at;
    s32 var_v1;
    u8 *temp_v0;
    u8 *var_s2;
    u8 *var_s3;
    u8 *var_v1_2;

    var_v1 = 1;
    sp56 = 0;
    if ((arg3 != NULL) && (arg4 != NULL)) {
        var_s2 = arg0 + 0x2C;
        var_s3 = arg0 + 0x38;
        (*(f32 *)((u8 *)var_s2 + 0)) = (f32) (*(f32 *)((u8 *)arg3 + 0));
        (*(f32 *)((u8 *)var_s2 + 4)) = (f32) (*(f32 *)((u8 *)arg3 + 4));
        (*(f32 *)((u8 *)var_s2 + 8)) = (f32) (*(f32 *)((u8 *)arg3 + 8));
        (*(s32 *)((u8 *)var_s3 + 0)) = (s32) (*(s32 *)((u8 *)arg4 + 0));
        (*(s32 *)((u8 *)var_s3 + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
        (*(s32 *)((u8 *)var_s3 + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
        sp57 = 1;
        ray_cast_through_passable(arg5, var_s2, (f32 *)var_s3, arg0, 0.0f, 0, 0, 1, 3, (u8 *)arg6, (f32 *)arg7, (f32 *)arg8, (u8 *)arg9, argA);
        var_v1 = 1;
        if ((*(u8 *)((u8 *)arg0 + 0x59)) == 0) {
            if (((*(f32 *)((u8 *)arg0 + 0x2C)) != (*(f32 *)((u8 *)arg1 + 0))) || ((*(f32 *)((u8 *)arg0 + 0x30)) != (*(f32 *)((u8 *)arg1 + 4))) || ((*(f32 *)((u8 *)arg0 + 0x34)) != (*(f32 *)((u8 *)arg1 + 8)))) {
                (*(f32 *)((u8 *)var_s2 + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
                (*(f32 *)((u8 *)var_s2 + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
                (*(f32 *)((u8 *)var_s2 + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
                (*(s32 *)((u8 *)var_s3 + 0)) = (s32) (*(s32 *)((u8 *)arg4 + 0));
                (*(s32 *)((u8 *)var_s3 + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
                var_at = (*(s32 *)((u8 *)arg4 + 8));
                goto block_14;
            }
            var_v1 = 0;
            goto block_15;
        }
        if (((*(f32 *)((u8 *)arg0 + 0x2C)) != (*(f32 *)((u8 *)arg1 + 0))) || ((*(f32 *)((u8 *)arg0 + 0x30)) != (*(f32 *)((u8 *)arg1 + 4))) || ((*(f32 *)((u8 *)arg0 + 0x34)) != (*(f32 *)((u8 *)arg1 + 8)))) {
            (*(f32 *)((u8 *)var_s2 + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
            (*(f32 *)((u8 *)var_s2 + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
            (*(f32 *)((u8 *)var_s2 + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
            (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 8)) - (*(f32 *)((u8 *)arg1 + 0)));
            (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xC)) - (*(f32 *)((u8 *)arg1 + 4)));
            (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) - (*(f32 *)((u8 *)arg1 + 8)));
            sp57 = 1;
            var_v1 = 1;
            if (vec3_normalize_len(var_s3, var_s3, arg0 + 4, 0) == 0) {
                return 0;
            }
        }
        goto block_15;
    }
    var_s2 = arg0 + 0x2C;
    var_s3 = arg0 + 0x38;
    (*(f32 *)((u8 *)var_s2 + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
    (*(f32 *)((u8 *)var_s2 + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)var_s2 + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
    (*(s32 *)((u8 *)var_s3 + 0)) = (s32) (*(s32 *)((u8 *)arg2 + 0));
    (*(s32 *)((u8 *)var_s3 + 4)) = (s32) (*(s32 *)((u8 *)arg2 + 4));
    var_at = (*(s32 *)((u8 *)arg2 + 8));
block_14:
    (*(s32 *)((u8 *)var_s3 + 8)) = var_at;
block_15:
    if (var_v1 != 0) {
        ray_cast_through_passable(arg5, var_s2, (f32 *)var_s3, arg0, 0.0f, 0, 1, 1, 3, (u8 *)arg6, (f32 *)arg7, (f32 *)arg8, (u8 *)arg9, argA);
        if ((*(u8 *)((u8 *)arg0 + 0x59)) != 0) {
            sp56 = 1;
        }
    }
    if (sp56 == 0) {
        (*(s32 *)((u8 *)arg0 + 0)) = 0;
        (*(f32 *)((u8 *)arg0 + 4)) = 5000.0f;
        (*(f32 *)((u8 *)var_s2 + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
        (*(f32 *)((u8 *)var_s2 + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
        (*(f32 *)((u8 *)var_s2 + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
        var_v1_2 = arg2;
        if (arg4 != NULL) {
            var_v1_2 = arg4;
        }
        temp_v0 = arg0 + 8;
        (*(s32 *)((u8 *)var_s3 + 0)) = (s32) (*(s32 *)((u8 *)var_v1_2 + 0));
        (*(s32 *)((u8 *)var_s3 + 4)) = (s32) (*(s32 *)((u8 *)var_v1_2 + 4));
        (*(s32 *)((u8 *)var_s3 + 8)) = (s32) (*(s32 *)((u8 *)var_v1_2 + 8));
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x2C)) + ((*(f32 *)((u8 *)arg0 + 0x38)) * 5000.0f));
        (*(f32 *)((u8 *)arg0 + 0xC)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x30)) + ((*(f32 *)((u8 *)arg0 + 0x3C)) * 5000.0f));
        (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x40)) * 5000.0f));
        (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0));
        (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
        (*(s32 *)((u8 *)arg0 + 0x1C)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
        (*(s32 *)((u8 *)arg0 + 0x20)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0));
        (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
        (*(s16 *)((u8 *)arg0 + 0x56)) = 0;
        (*(s8 *)((u8 *)arg0 + 0x58)) = 0;
        (*(u8 *)((u8 *)arg0 + 0x59)) = 0U;
        (*(s8 *)((u8 *)arg0 + 0x5A)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x5C)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x60)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x28)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
    }
    return 1;
}
/* P160 */
s32 ray_cast_world(s32, f32, f32, f32, f32, f32, f32, s32 *, f32, s32, s32, s32, s32, u8 *, s32);
extern f32 g_ray_pass_step; /* was D_800AADA4 */

typedef struct { f32 x, y, z; } V3_151C230C;
typedef struct { u16 h[9]; } Blk12_151C230C; /* 0x12 bytes, 2-byte aligned */

// ray_cast_through_passable: casts the ray `dir` from `start` (ray_cast_world, hit record `hit`) and, while the hit
// object has (obj[0x4F] & 0x60) == 0x40 (a see-through object), records that object (its hit point in passPos,
// the distance so far in passDist, and a 0x24-byte pass record) and casts again from just behind it
// (g_ray_pass_step along the hit normal). Finally restores the record's start (hit+0x2C) and stores the total distance
// in hit+4. Always returns 0.
/* was func_151C230C */
s32 ray_cast_through_passable(s32 arg0, u8 *start, f32 *dir, u8 *hit, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s8 arg8,
                  u8 *arg9, f32 *passPos, f32 *passDist, u8 *pass, s32 argD) {
    V3_151C230C pos;
    f32 dist;
    f32 step;
    u8 *obj;
    s32 again;

    dist = 0.0f;
    *passDist = 0.0f;
    pos = *(V3_151C230C *)start;
    step = g_ray_pass_step;
    do {
        ray_cast_world(arg0, pos.x, pos.y, pos.z, dir[0], dir[1], dir[2], (s32 *)hit, arg4, arg5, arg6, arg7, arg8,
                      arg9, argD);
        obj = *(u8 **)(hit + 0x5C);
        dist += *(f32 *)(hit + 4);
        again = 0;
        if (obj != NULL && (obj[0x4F] & 0x60) == 0x40) {
            pos.x = *(f32 *)(hit + 0x8) + *(f32 *)(hit + 0x38) * step;
            pos.y = *(f32 *)(hit + 0xC) + *(f32 *)(hit + 0x3C) * step;
            pos.z = *(f32 *)(hit + 0x10) + *(f32 *)(hit + 0x40) * step;
            *(V3_151C230C *)passPos = *(V3_151C230C *)(hit + 8);
            *passDist = dist;
            dist += step;
            *(f32 *)(pass + 0) = *(f32 *)(hit + 0xC);
            *(Blk12_151C230C *)(pass + 4) = *(Blk12_151C230C *)(hit + 0x44);
            *(s32 *)(pass + 0x18) = *(s32 *)(hit + 0x60);
            pass[0x1C] = 7;
            pass[0x1D] = 3;
            *(u8 **)(pass + 0x20) = obj;
            again = 1;
        }
    } while (again);
    *(V3_151C230C *)(hit + 0x2C) = *(V3_151C230C *)start;
    *(f32 *)(hit + 4) = dist;
    return 0;
}

/* was func_151C1FB8 */
void obj_rider_cam_shake(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = (random_int() & 7) + 0xD;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        sp18[4] = ((u32)random_int() % 3) + 6;
        sp18[6] = -1;
        rumble_request(sp18, 0, 0xFF, 1);
    }
}
