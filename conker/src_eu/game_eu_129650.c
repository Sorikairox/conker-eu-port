#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct127 *player_find_owned_object(struct127 *, struct127 *, s32);
void mtx_transform_points(f32 **src, f32 **dst, u8 *bone, s32 n);
s32 tracer_spawn(f32 *, f32 *, f32 *, f32 *, s32, s32, f32, f32, f32, f32, f32, s32, u8 *, s32, s32, s32, s32, s32,
                  s32, s32, s32, f32, s32, s32, s32, s32, s32);
void attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void sprite2d_spawn(void *, s32, s32, s32, s32, s32, s32);
extern f32 g_gun_shot_muzzle_pts[2][3];   /* per side: muzzle offsets (non-0x23 characters); was D_800A21A4 */
extern f32 g_gun_shot_spark_end_pts[2][3]; /* was D_800A21BC */
extern f32 g_gun_shot_aim_pts[2][3]; /* was D_800A21D4 */
extern f32 g_gun_shot_third_pts[2][3]; /* was D_800A21EC */
extern f32 g_gun_shot_muzzle_pts_c23[2][3];   /* the same for character 0x23; was D_800A2208 */
extern f32 g_gun_shot_spark_end_pts_c23[2][3]; /* was D_800A2220 */
extern f32 g_gun_shot_aim_pts_c23[2][3]; /* was D_800A2238 */
extern f32 g_gun_shot_third_pts_c23[2][3]; /* was D_800A2250 */
extern u8 g_gun_shot_hand_bones[2];       /* per side: hand bone index ({ 5, 7 }); was D_800A21A0 */
extern u8 g_gun_shot_hand_bones_c23[2];       /* the same for character 0x23 ({ 3, 2 }); was D_800A2204 */
static const f32 gunfire_tracer_k[1] = { 0.003968254f };   /* D_800A2268 */
static const f32 gunfire_shell_v1m[1] = { 2.4350002f };    /* D_800A226C */
static const f32 gunfire_shell_v1a[1] = { 3.5340002f };    /* D_800A2270 */
static const f32 gunfire_shell_v0m[1] = { 43.4f };         /* D_800A2274 */
static const f32 gunfire_shell_v0a[1] = { 48.4f };         /* D_800A2278 */
static const f32 gunfire_shell_life[1] = { 1497.0f };      /* D_800A227C */

typedef struct {
    f32 pos[2];       /* 0x00 screen offset */
    f32 size[2];      /* 0x08 */
    u8 b10;           /* 0x10 */
    u8 pad11;
    s16 h12;          /* 0x12 */
    s16 h14;          /* 0x14 */
    s16 h16;          /* 0x16 */
    s16 h18;          /* 0x18 */
    u8 b1A[10];       /* 0x1A */
    s32 w24[7];       /* 0x24 */
    u8 b40;           /* 0x40 */
    u8 b41;           /* 0x41 */
    u8 pad42[2];
    u8 mask;          /* 0x44 */
} GunfireFlash;       /* sprite2d_spawn's spec */

// gun_fire_effects: muzzle flash, tracer and shells for one shot of `obj`'s gun on hand `side` (0 / 1), `dt` into the
// frame. Unless `noOwner`, the shooter is player_find_owned_object(obj) (no shooter -> nothing); `aimed` = its record's 0x197.
// mtx_transform_points places the muzzle point / direction points from the hand bone (obj+0x1D4, 64-byte bones; character
// 0x23 has its own tables). Aimed shots project onto the shooter's aim line (unk31C 0x13C point, 0x130 direction).
// tracer_spawn spawns the tracer (kind 5 in levels 0x34 / 0x26, else 4; hidden from the shooter's own camera); unless
// obj+0x74's low nibble is 0xF a 1-in-8 spark (light_create_with_ctrl) and a 1-in-2 shell (attached_particle_spawn) follow; aimed shots
// with a camera also get the screen flash (sprite2d_spawn) and sprite2d_broadcast event 0x37.
/* was func_150FBE40 */
void gun_shot_effects(u8 *obj, u8 side, f32 dt, u8 noOwner, s32 fxflag, s32 fxowner) {
    struct127 *owner;
    u8 aimed;
    f32 *tbl[3];
    f32 *out[3];
    f32 alt[3];
    f32 pos[3];
    f32 side0[3];
    f32 side1[3];
    f32 tip[3];
    f32 norm[3];
    f32 hit[3];
    f32 dir[3];
    u8 *bone;
    u8 *aim;
    f32 *p;
    f32 t;
    s32 sgn;
    u8 mask;
    s8 kind;
    f32 r1;
    f32 r2;
    u32 r3;
    struct {
        u8 b0;
        u8 b1;
        s16 h2;
        u8 b4;
    } spark;
    s32 ipos[3];
    f32 vel[2];
    u32 r4;
    u32 r5;
    GunfireFlash flash;
    struct {
        u8 side;
        void *camera;
    } ev;

    if (obj == NULL || side >= 2) {
        return;
    }
    if (noOwner) {
        owner = NULL;
        aimed = 0;
    } else {
        /* the asm leaves side / dt's bits in a1 / a2 (player_find_owned_object ignores both) */
        owner = player_find_owned_object((struct127 *)obj, (struct127 *)(u32)side, *(s32 *)&dt);
        if (owner == NULL || owner->unk31C == NULL) {
            return;
        }
        aimed = (*((u8 *)owner->unk31C + 0x197) != 0) ? 1 : 0;
    }
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        return;
    }
    if (obj[4] == 0x23) {
        tbl[0] = g_gun_shot_muzzle_pts_c23[side];
        tbl[1] = aimed ? g_gun_shot_aim_pts_c23[side] : g_gun_shot_spark_end_pts_c23[side];
        tbl[2] = g_gun_shot_third_pts_c23[side];
        bone = *(u8 **)(obj + 0x1D4) + g_gun_shot_hand_bones_c23[side] * 64;
    } else {
        r1 = random_float();
        sgn = side ? -1 : 1;
        alt[0] = (f32)sgn * (13.0f - (1.0f + r1 * 6.0f));
        alt[1] = g_gun_shot_spark_end_pts[side][1];
        alt[2] = g_gun_shot_spark_end_pts[side][2];
        tbl[0] = g_gun_shot_muzzle_pts[side];
        tbl[1] = aimed ? g_gun_shot_aim_pts[side] : alt;
        tbl[2] = g_gun_shot_third_pts[side];
        bone = *(u8 **)(obj + 0x1D4) + g_gun_shot_hand_bones[side] * 64;
    }
    out[0] = pos;
    out[1] = aimed ? side0 : tip;
    out[2] = side1;
    mtx_transform_points(tbl, out, bone, aimed ? 3 : 2);
    if (aimed) {
        aim = (u8 *)owner->unk31C;
        p = (f32 *)(aim + 0x13C);
        side0[0] -= pos[0];
        side0[1] -= pos[1];
        side0[2] -= pos[2];
        side1[0] -= pos[0];
        side1[1] -= pos[1];
        side1[2] -= pos[2];
        vec3_cross((struct17 *)side0, (struct17 *)side1, (struct17 *)norm);
        aim = (u8 *)owner->unk31C;
        t = (norm[0] * (pos[0] - p[0]) + norm[1] * (pos[1] - p[1]) + norm[2] * (pos[2] - p[2])) /
            (norm[0] * *(f32 *)(aim + 0x130) + norm[1] * *(f32 *)(aim + 0x134) + norm[2] * *(f32 *)(aim + 0x138));
        hit[0] = p[0] + t * *(f32 *)(aim + 0x130);
        hit[1] = p[1] + t * *(f32 *)((u8 *)owner->unk31C + 0x134);
        hit[2] = p[2] + t * *(f32 *)((u8 *)owner->unk31C + 0x138);
        dir[0] = *(f32 *)((u8 *)owner->unk31C + 0x130);
        dir[1] = *(f32 *)((u8 *)owner->unk31C + 0x134);
        dir[2] = *(f32 *)((u8 *)owner->unk31C + 0x138);
    } else {
        tip[0] -= pos[0];
        tip[1] -= pos[1];
        tip[2] -= pos[2];
    }
    if (aimed && owner->camera != NULL) {
        mask = ~(1 << *((u8 *)owner->camera + 0x23D));
    } else {
        mask = 0xFF;
    }
    kind = (g_level_id == 0x34 || g_level_id == 0x26) ? 5 : 4;
    r1 = random_float();
    r2 = random_float();
    r3 = random_int();
    tracer_spawn(pos, aimed ? NULL : tip, aimed ? hit : NULL, aimed ? dir : NULL, aimed ? 1 : 0, 0, 252.0f,
                  gunfire_tracer_k[0], r1 * 20.0f + 75.0f, r2 * 250.0f + 502.0f, 50.0f, r3 % 31 + 225,
                  (owner != NULL) ? (u8 *)owner : obj, 1, 1, D_800BE616 ? 0 : 1, 50, 0, 1, kind, 0x2C, dt, mask, 0,
                  0, (u8)fxflag, fxowner);
    if ((obj[0x74] & 0xF) != 0xF) {
        if ((random_int() & 7) == 0) {
            spark.b0 = 3;
            spark.b1 = 0xFF;
            spark.h2 = (u32)random_int() % 5 + 4;
            ipos[0] = pos[0];
            ipos[1] = pos[1];
            ipos[2] = pos[2];
            spark.b4 = 0;
            light_create_with_ctrl((Header *)&spark, (Header2 *)ipos, (u32)random_int() % 31 + 0x46, 0xFF, 0xFF, 0xFF, 0xFF,
                          0, 0, (u8)fxflag, fxowner);
        }
        if ((random_int() & 1) == 0) {
            vel[1] = random_float() * gunfire_shell_v1m[0] + gunfire_shell_v1a[0];
            vel[0] = random_float() * gunfire_shell_v0m[0] + gunfire_shell_v0a[0];
            if (aimed && owner->camera != NULL) {
                mask = ~(1 << *((u8 *)owner->camera + 0x23D));
            } else {
                mask = 0xFF;
            }
            r4 = random_int();
            r5 = random_int();
            r1 = random_float();
            if (obj[4] == 0x23) {
                attached_particle_spawn(obj, g_gun_shot_hand_bones_c23[side], g_gun_shot_muzzle_pts_c23[side], g_gun_shot_spark_end_pts_c23[side], vel, r4 % 3 + 4,
                              r5 % 101 + 0x9B, r1 * 1012.0f + gunfire_shell_life[0], pos, mask, 0, -1,
                              (u8)fxflag, fxowner);
            } else {
                attached_particle_spawn(obj, g_gun_shot_hand_bones[side], g_gun_shot_muzzle_pts[side], g_gun_shot_spark_end_pts[side], vel, r4 % 3 + 4,
                              r5 % 101 + 0x9B, r1 * 1012.0f + gunfire_shell_life[0], pos, mask, 0, -1,
                              (u8)fxflag, fxowner);
            }
        }
    }
    if (!aimed || owner->camera == NULL) {
        return;
    }
    flash.pos[0] = side ? -59.0f : 59.0f;
    flash.pos[1] = 68.0f;
    flash.size[0] = random_float() * 20.0f + 40.0f;
    flash.size[1] = random_float() * 20.0f + 80.0f;
    flash.b10 = 0x80;
    flash.h12 = (random_int() & 3) + 5;
    flash.h14 = (side ? 2 : 0) | 0x39;
    flash.h16 = 3;
    flash.h18 = 0x55;
    flash.b1A[0] = 0;
    flash.b1A[1] = 0xFF;
    flash.b1A[2] = 0xFF;
    flash.b1A[3] = 0xFF;
    flash.b1A[4] = (u32)random_int() % 56 + 0xC8;
    flash.b1A[5] = 0xFF;
    flash.b1A[6] = 0xFF;
    flash.b1A[7] = 0xFF;
    flash.b1A[8] = 0xFF;
    flash.b1A[9] = 0xFF;
    flash.w24[0] = 0;
    flash.w24[1] = 0x200004;
    flash.w24[2] = 0x1F0601;
    flash.w24[3] = 3;
    flash.w24[4] = 0x22;
    flash.w24[5] = 0x80;
    flash.w24[6] = 0x20;
    flash.b40 = 0;
    flash.b41 = 7;
    flash.mask = *((u8 *)owner->camera + 0x23D);
    sprite2d_spawn(&flash, 0, 0, 0, 0, 0, fxowner);
    ev.side = side;
    ev.camera = owner->camera;
    sprite2d_broadcast(&ev, 0x37);
}

/* was func_150FC8E8 */
void tracer_draw_masked(u8 *arg0) {
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x1A0));
    if ((temp_v0 == NULL) || ((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) == 0xFF) || ((*(u8 *)((u8 *)arg0 + 0x1A4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || (temp_v1 = (*(u8 **)((u8 *)temp_v0 + 0x31C)), (temp_v1 == NULL)) || ((*(u8 *)((u8 *)temp_v1 + 0x84)) != 0) || ((*(u8 *)((u8 *)temp_v0 + 0x127)) == 0xFF) || (temp_v1_2 = (*(u8 **)((u8 *)temp_v0 + 0x318)), (temp_v1_2 == NULL))) {
        var_v0 = 0xFF;
    } else {
        var_v0 = ~(1 << (*(u8 *)((u8 *)temp_v1_2 + 0x23D))) & 0xFF;
    }
    surface_impact_effects((s32) arg0, 1.0f, 1.0f, 0.6f, 0.0f, 0xFFU, 0xFFU, (u8) var_v0);
}
extern f32 g_gunfire_burst_k_2280, g_gunfire_burst_k_2284, g_gunfire_burst_k_2288, g_gunfire_burst_k_228c, g_gunfire_burst_k_2290, g_gunfire_burst_k_2294, g_gunfire_burst_k_2298, g_gunfire_burst_k_229c, g_gunfire_burst_k_22a0; /* was D_800A2280; was D_800A2284; was D_800A2288; was D_800A228C; was D_800A2290; was D_800A2294; was D_800A2298; was D_800A229C; was D_800A22A0 */
u8 *cam_wobble_spawn(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);

// effect27_spawn_with_screen_effect: starts an effect record of kind 0x27 (300 frames, effect_node_create) whose 32-byte
// data (rec + 0x28) holds `obj` and its id (+0x3B), the flag `a`, `other`, its id (0xFF without one) and its player
// (+0x318 -> +0x23D, -1 without one) and the value `b`. When `other` has a player record, a kind-4 screen effect of
// 300 frames for that player is started too (cam_wobble_spawn, scales 12 / 20 / 19 and the g_gunfire_burst_k_2280.. table); its record
// goes to data + 0x10. Called by the B-pad item action player_item_action and by objfx_fc438 (game_981E0).
/* was func_150FC438 */
void gunfire_burst_spawn(struct127 *obj, struct127 *other, u8 a, u8 b) {
    struct {
        u8 kind;    // 0x00
        s8 u1;      // 0x01
        s8 u2;      // 0x02
        s16 time;   // 0x04
        u8 player;  // 0x06
        f32 f[12];  // 0x08
    } fx;
    struct {
        struct127 *obj;   // 0x00
        u8 objId;         // 0x04
        f32 f8;           // 0x08
        u8 uC;            // 0x0C
        u8 a;             // 0x0D
        s32 screen;       // 0x10: the screen effect record
        s16 u14;          // 0x14
        s8 player;        // 0x16
        struct127 *other; // 0x18
        u8 otherId;       // 0x1C
        u8 b;             // 0x1D
    } data;
    u8 *rec;
    u8 *pl;

    data.obj = obj;
    data.objId = ((u8 *) obj)[0x3B];
    data.f8 = 0.0f;
    data.uC = 0;
    data.a = a;
    data.screen = 0;
    data.u14 = 0;
    data.b = b;
    if (other != NULL && (pl = *(u8 **) ((u8 *) other + 0x318)) != NULL) {
        data.player = pl[0x23D];
    } else {
        data.player = -1;
    }
    data.other = other;
    data.otherId = (other != NULL) ? ((u8 *) other)[0x3B] : 0xFF;

    rec = (u8 *) effect_node_create(0x12C, -1, 0x27, -1, 0, 0x25, (struct37 *) 0x20, 0xFF, 1);
    if (rec == NULL) {
        return;
    }
    memcpy(rec + 0x28, &data, 0x20);
    if (other == NULL || *(u8 **) ((u8 *) other + 0x318) == NULL) {
        return;
    }
    fx.kind = 4;
    fx.u1 = -1;
    fx.u2 = -1;
    fx.time = 0x12C;
    fx.player = (*(u8 **) ((u8 *) other + 0x318))[0x23D];
    fx.f[0] = 12.0f;
    fx.f[1] = 20.0f;
    fx.f[2] = 19.0f;
    fx.f[3] = g_gunfire_burst_k_2280;
    fx.f[4] = g_gunfire_burst_k_2284;
    fx.f[5] = g_gunfire_burst_k_2288;
    fx.f[6] = g_gunfire_burst_k_228c;
    fx.f[7] = g_gunfire_burst_k_2290;
    fx.f[8] = g_gunfire_burst_k_2294;
    fx.f[9] = g_gunfire_burst_k_2298;
    fx.f[10] = g_gunfire_burst_k_229c;
    fx.f[11] = g_gunfire_burst_k_22a0;
    *(u8 **) (rec + 0x28 + 0x10) = cam_wobble_spawn((u8 *) &fx, 0, 0xFF, 1);
}

void gun_shot_effects(u8 *, u8, f32, u8, s32, s32);

/* was func_150FCB94 */
void gunfire_burst_update(u8 *arg0) {
    struct {
        s8 u50;
        u8 pad51[0x1];
        s16 u52;
        s8 u54;
        s8 u55;
        s8 u56;
    } sp;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x28));
    if (((*(s32 *)((u8 *)temp_s1 + 0)) == 0) || (temp_s0 = arg0 + 0x28, ((*(u8 *)((u8 *)temp_s1 + 4)) == 0xFF)) || ((*(u8 *)((u8 *)temp_s0 + 4)) != (*(u8 *)((u8 *)temp_s1 + 0x3B))) || (D_800C35EA == 1)) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if ((*(u8 *)((u8 *)temp_s0 + 0x1D)) != (*(u16 *)((u8 *)temp_s1 + 0x84))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) - g_frame_step_f);
    if ((*(f32 *)((u8 *)temp_s0 + 8)) < 0.0f) {
        do {
            gun_shot_effects(temp_s1, (*(u8 *)((u8 *)temp_s0 + 0xC)), -(*(f32 *)((u8 *)temp_s0 + 8)), (*(u8 *)((u8 *)temp_s0 + 0xD)), (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            temp_v1 = (*(u8 **)((u8 *)temp_s0 + 0x18));
            (*(u8 *)((u8 *)temp_s0 + 0xC)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0xC)) ^ 1);
            if (temp_v1 != NULL) {
                temp_v0 = (*(u8 **)((u8 *)temp_v1 + 0x31C));
                if (temp_v0 != NULL) {
                    (*(s16 *)((u8 *)temp_v0 + 0x1AA)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0x1AA)) + 1);
                }
            }
            (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) + (4.0f + (random_float() * 4.0f)));
        } while ((*(f32 *)((u8 *)temp_s0 + 8)) < 0.0f);
    }
    if ((*(s8 *)((u8 *)temp_s0 + 0x16)) != -1) {
        (*(s16 *)((u8 *)temp_s0 + 0x14)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0x14)) - g_frame_ticks);
        if ((*(s16 *)((u8 *)temp_s0 + 0x14)) < 0) {
            sp.u50 = 1;
            random_int();
            sp.u52 = 0x1E;
            sp.u55 = 1 << (*(s8 *)((u8 *)temp_s0 + 0x16));
            sp.u54 = (random_int() % 6U) + 3;
            sp.u56 = -1;
            rumble_request((structEU_151D8E18 *) &sp.u50, 0, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            random_int();
            (*(s16 *)((u8 *)temp_s0 + 0x14)) = 0xFA;
        }
    }
}
/* was func_150FCD98 */
void gunfire_burst_handle_event(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 new_var; // fakematch: permuter temp
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == (new_var = *(s32 *)v) || arg1[4] == v[4]) {
            node_destroy(arg0);
        } else if (*(s32 *)(v + 0x18) != 0) {
            if (t == *(s32 *)(v + 0x18) || arg1[4] == v[0x1C]) {
                node_destroy(arg0);
            }
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        } else if (*(s32 *)(v + 0x18) != 0) {
            if (*(s32 *)arg1 == *(s32 *)(v + 0x18)) {
                *(s32 *)(v + 0x18) = *(s32 *)(arg1 + 4);
                v[0x1C] = arg1[9];
            } else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x18)) {
                *(s32 *)(v + 0x18) = *(s32 *)arg1;
                v[0x1C] = arg1[8];
            }
        }
    }
}

/* was func_150FCEB0 */
s32 gunfire_target_filter(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x12:
        case 0x23:
        case 0x73:
        case 0x8A:
            return 0;
        default:
            return 1;
    }
}

/* was func_150FCEF4 */
void gunfire_burst_free(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x38) != 0) {
        node_destroy(*(struct102 **)(arg0 + 0x38));
    }
}

/* was func_150FCF24 */
void gunfire_burst_retire(void *arg0) {
    gunfire_burst_free(arg0);
    effect_node_retire(arg0);
}

/* was func_150FCF50 */
void gunfire_burst_delete(void *arg0) {
    gunfire_burst_free(arg0);
    effect_node_free(arg0);
}
