#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
typedef struct {
    u8 u0;          /* 0xC0 */
    s8 u1;
    u8 u2;
    u8 u3;
    u8 u4;
    u8 pad5;
    s16 u6;
    s32 texture;    /* +0x08 */
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    s32 u24;
    s32 u28;
    u8 u2C;
    u8 u2D;
    u8 pad2E[2];
    u8 color[8];    /* +0x30 */
    u8 u38;
    u8 pad39[3];
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    f32 x;          /* +0x44 */
    f32 y;
    f32 z;
    s32 u50;        /* room (life_pickup_spawn); unset by the lives pop-up */
    s16 u54;
    s16 u56;
} LivesSprite;      /* 0x58 bytes, argument of anim_model_fx_spawn */
s32 player_slot_is_active(u8 *arg0);

/* P142 */
void collision_select_area(s32);
s32 zone_tree_find_leaf(s32 x, s32 z);
void vec3_from_angles_rad(f32 yaw, f32 pitch, f32 dist, struct17 *out);
s32 anim_model_fx_spawn(void *sprite, s32, f32 alpha, s32, s32, s32 depth, s32, s32);
s32 life_pickup_ring_spawn(f32 yaw, s32 posArg, s32 arg2, u8 arg3, s32 colour, s32 flag, s32 arg6, s32 arg7, s32 arg8);
s32 memcpy(void *, void *, s32);
/* marker_sprite_spawn: spawns a marker at pos facing `angle` (degrees). size 0..2 (3 or more: nothing,
 * returns 0). In the level types with D_800D2E4C->unk19 & 4, or for size 2, it is a HUD-style sprite (texture
 * 0xA2, anim_model_fx_spawn) placed 39 units out along the angle and 40 lower, with sprite size {3, 1, 2}[size], flag
 * 0x10 set when `flag`; the angle, that position and `kind` go to the sprite object + 0x120 (life_pickup_spin_matrix
 * turns it). Otherwise the 3D ring particle life_pickup_ring_spawn. Returns the object (0 when none). arg5 / arg6 unused. */
/* was func_151BEE00 */
s32 life_pickup_spawn(f32 *pos, f32 angle, u8 kind, u8 flag, u8 size, s32 arg5, s32 arg6) {
    static const u8 sizes[3] = { 3, 1, 2 };
    struct {
        u8 pad50[4];
        f32 angle;      // +0x54: the 0x18 bytes from here go to the sprite object + 0x120
        f32 pos[3];
        u8 kind;
        u8 pad65[3];
        LivesSprite spr; // +0x68
    } sp;
    f32 dir[3];
    s32 room;
    s32 obj;

    collision_select_area(0);
    room = zone_tree_find_leaf((s32) pos[0], (s32) pos[2]);
    if (size >= 3) {
        return 0;
    }
    if ((D_800D2E4C->unk19 & 4) || size == 2) {
        sp.angle = angle;
        sp.spr.u3C = 0;
        sp.spr.u40 = 0;
        sp.spr.u41 = 0;
        sp.spr.x = pos[0];
        sp.spr.y = pos[1];
        sp.spr.z = pos[2];
        sp.kind = kind;
        sp.spr.u50 = room;
        vec3_from_angles_rad(angle * 0.017453292f, 0.0f, 39.0f, (struct17 *) dir);
        sp.pos[0] = pos[0] + dir[0];
        sp.pos[1] = pos[1] + dir[1] - 40.0f;
        sp.pos[2] = pos[2] + dir[2];
        sp.spr.u38 = sizes[size];
        sp.spr.u0 = (flag ? 0x10 : 0) | 0xE;
        sp.spr.u1 = 1;
        if (g_level_id == 7) {
            sp.spr.u2 = 6;
        } else {
            sp.spr.u2 = 2;
        }
        sp.spr.u4 = 0xFF;
        sp.spr.u6 = 300;
        sp.spr.texture = 0xA2;
        sp.spr.u14 = 0x620405;
        sp.spr.uC = 8;
        sp.spr.u18 = 0x40200;
        sp.spr.u1C = 0x14;
        sp.spr.u20 = 0x37;
        sp.spr.u24 = 0x80;
        sp.spr.u28 = 0x20;
        sp.spr.u2D = 8;
        sp.spr.color[0] = 0xFF;
        sp.spr.color[2] = 0xFF;
        sp.spr.u3 = 0;
        sp.spr.u10 = 0;
        sp.spr.u2C = 0;
        sp.spr.color[1] = 0xFF;
        sp.spr.color[3] = 0xFF;
        sp.spr.color[4] = 0xFF;
        sp.spr.color[5] = 0xFF;
        sp.spr.color[6] = 0xFF;
        sp.spr.color[7] = 0xFF;
        obj = anim_model_fx_spawn(&sp.spr, 0, 1.0f, 3, 0xFF, 0x18, 0xFF, 1);
        if (obj != 0) {
            memcpy((u8 *) obj + 0x120, &sp.angle, 0x18);
        }
        return obj;
    }
    return life_pickup_ring_spawn(angle, (s32) pos, 3, 0xFF, size, flag, room, 0xFF, 1);
}

/* was func_151BF0D0 */
s32 life_pickup_spin_matrix(u8 *arg0) {
    mtxf_rotate_xyz_deg(((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0], 0.0f, *(f32 *)(arg0 + 0x120), 0.0f);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][0] = *(f32 *)(arg0 + 0x54);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][1] = *(f32 *)(arg0 + 0x58);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][2] = *(f32 *)(arg0 + 0x5C);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][2] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][2] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][2] *= 0.92300004f;
    return 1;
}

/* was func_151BF244 */
s32 gfx_passthrough_flag(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    *arg4 = 1;
    return arg0;
}

f32 vec3_length(f32 *);
void obj_get_fx_point_a(u8 *, f32 *, f32 *, f32 *);
s32 life_pickup_ring_spawn(f32, s32, s32, u8, s32, s32, s32, s32, s32);
void pickup_burst_spawn(f32 *);
void lives_popup_spawn(u8, s32);
extern s32 g_obj_update_counter; /* was D_800D1968 */

/* was func_151BF268 */
s32 life_pickup_check_collect(u8 *arg0) {
    struct {
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        f32 u9C;
    } sp;
    s32 var_s5;
    s32 var_v1;
    struct127 *var_s3;
    u8 temp_v0;
    u8 *temp_s1;

    var_s5 = 1;
    var_s3 = g_objects;
    do {
        if (player_slot_is_active((u8 *) var_s3) != 0) {
            temp_s1 = arg0 + 0x120;
            obj_get_fx_point_a((u8 *) var_s3, &sp.u8C, &sp.u9C, &sp.u98);
            sp.u80 = sp.u8C - (*(f32 *)((u8 *)temp_s1 + 4));
            sp.u84 = sp.u90 - (*(f32 *)((u8 *)temp_s1 + 8));
            sp.u88 = sp.u94 - (*(f32 *)((u8 *)temp_s1 + 0xC));
            if ((vec3_length(&sp.u80) - sp.u9C) < 43.0f) {
                var_s5 = 0;
                player_stat_modify((s16) var_s3->unk127, 3, (s32) (*(u8 *)((u8 *)temp_s1 + 0x10)));
                sound_play_2d(0x511, 0x7D00U, 0x40U, 0, 0U);
                lives_popup_spawn((*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
                pickup_burst_spawn((f32 *) (temp_s1 + 4));
                temp_v0 = (*(u8 *)((u8 *)arg0 + 0x48));
                var_v1 = 0;
                switch (temp_v0) {                  /* irregular */
                case 0:
                    break;
                default:
                    var_v1 = 0;
                    if (temp_v0 != 3) {

                    }
                    break;
                case 1:
                    var_v1 = 1;
                    break;
                case 2:
                    var_v1 = 2;
                    break;
                }
                life_pickup_ring_spawn((*(f32 *)((u8 *)temp_s1 + 0)), arg0 + 0x54, (*(s32 *)((u8 *)arg0 + 0xFC)), (*(u8 *)((u8 *)arg0 + 0x11B)), var_v1, (*(u8 *)((u8 *)arg0 + 0x10)) & 0x10, (*(s32 *)((u8 *)arg0 + 0x60)), (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
        }
        var_s3 = (struct127 *)((u8 *)var_s3 + (0x32C));
    } while ((s32)var_s3 != (s32)&g_obj_update_counter);
    return var_s5;
}
/* was func_151BF444 */
s32 player_slot_is_active(u8 *arg0) {
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

/* P139 */
/* P139: particle request passed to mdl_particle_spawn (0x7C bytes; layout as game_eu_103160.c's DebrisParticle). */
typedef struct {
    /* 0x00 */ f32 scale[4];
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 one[3];
    /* 0x28 */ s32 pos[3];      /* copied as words */
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spin[3];
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8 colour;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 alpha;
    /* 0x61 */ u8 u61;
    /* 0x62 */ u8 u62[6];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6C */ void *owner;
    /* 0x70 */ u8 ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} ParticleReq1EC;

extern u8 D_8008FF60[3];   /* colours per index 0..2: 4, 2, 3 */
s32 mdl_particle_spawn(void *req, s32, s32, s32, s32, s32);
s32 mdl_particle_mtx_rot_scale3(s32 arg0, u8 *arg1);

/*
 * ring_particle_spawn: spawns one ring particle (sprite 0x26, life 300, scale (1, 1, 0.923, 0.923; 0x3F6C49BB), rotated by
 * yaw about y, no motion) at the 3 words at pos (copied as they are), colour D_8008FF60[colour] (only colours 0..2;
 * else nothing and 0), flags 0xC1D00 | 0x4000 when flag (u8) is set, +0x5C = arg6, +0x61 = 0x18 in game mode 7
 * (g_level_id). Request (arg2, (u8) arg3, 0, (u8) arg7, arg8). On success mdl_particle_mtx_rot_scale3(p + 0x90 + 0x40 * k, p)
 * for k = 0, 1. Returns the particle (0 on failure).
 */
/* was func_151BF490 */
s32 life_pickup_ring_spawn(f32 yaw, s32 posArg, s32 arg2, u8 arg3, s32 colour, s32 flag, s32 arg6, s32 arg7, s32 arg8) {
    s32 *pos = (s32 *) posArg;
    ParticleReq1EC req;
    u8 *p;
    s32 k;

    if ((u8) colour >= 3) {
        return 0;
    }
    req.scale[0] = 1.0f;
    req.scale[1] = 1.0f;
    req.scale[3] = 0.92300004f;
    req.scale[2] = 0.92300004f;
    req.rot[0] = 0.0f;
    req.rot[1] = yaw;
    req.rot[2] = 0.0f;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.pos[0] = pos[0];
    req.pos[1] = pos[1];
    req.pos[2] = pos[2];
    req.vel[0] = 0.0f;
    req.vel[1] = 0.0f;
    req.vel[2] = 0.0f;
    req.spin[0] = 0.0f;
    req.spin[1] = 0.0f;
    req.spin[2] = 0.0f;
    req.gravity = 0.0f;
    req.flags = ((u8) flag != 0 ? 0x4000 : 0) | 0x1D00 | 0x80000 | 0x40000;
    req.life = 300;
    req.sprite = 0x26;
    req.alpha = 0xFF;
    req.colour = D_8008FF60[(u8) colour];
    req.u5C = arg6;
    req.u61 = (g_level_id == 7) ? 0x18 : 0;
    req.u62[0] = 0;
    req.u62[1] = 0;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 2;
    req.u6A = 0;
    req.owner = NULL;
    req.ownerId = 0;
    req.u72 = 1;
    req.u74 = 0xFF;
    p = (u8 *) mdl_particle_spawn(&req, arg2, arg3, 0, (u8) arg7, arg8);
    if (p != NULL) {
        for (k = 0; k != 0x80; k += 0x40) {
            mdl_particle_mtx_rot_scale3((s32) (p + 0x90 + k), p);
        }
    }
    return (s32) p;
}

/* P142 */
void emit_tumbling_pieces(u8 *req, u8, u8, s32);
void emit_particle_burst_req(u8 *req, s32, s32, s32);
// pickup_burst_spawn: the burst played when a pickup at pos is collected: a debris spray (emit_tumbling_pieces request:
// 24..34 pieces) and a flash particle (emit_particle_burst_req request, the same layout as in explosion_ground_effect).
/* was func_151BF678 */
void pickup_burst_spawn(f32 *pos) {
    struct {
        s16 u0;
        s16 u2;
        u8 u4;
        u8 pad5;
        s16 u6;
        s32 u8;
        s32 uC;
        s16 u10;
        s16 u12;
        s32 u14;
        s32 u18;
        u8 u1C;
        u8 u1D;
        u8 u1E;
        u8 u1F;
        u8 u20;
        u8 u21;
        u8 u22;
        u8 u23;
        u8 u24;
        u8 u25;
        s16 u26;
        s16 u28;
        s16 u2A;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 pos[3];
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
        u8 u60;
        s8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        u8 pad65[3];
        f32 u68;
    } flash;
    struct {
        s32 countMin;   // pieces: countMin + rand % (countRand + 1)
        s32 countRand;
        f32 pos[3];
        f32 scaleMin;   // + rand * scaleRand
        f32 scaleRand;
        s16 angleA;     // direction angles: base, random range
        s16 angleARand;
        s16 angleB;
        s16 angleBRand;
        f32 speedMin;
        f32 speedRand;
        f32 spread;     // horizontal start offset -spread..spread
        f32 u30;
        f32 u34;
        f32 u38;
        u8 u3C;
        u8 pad3D;
        s16 lifeMin;
        s16 lifeRand;
        u8 pad42[2];
    } debris;

    debris.countMin = 24;
    debris.countRand = 10;
    debris.pos[0] = pos[0];
    debris.pos[1] = pos[1];
    debris.pos[2] = pos[2];
    debris.angleA = 0;
    debris.angleARand = 0xFF;
    debris.angleB = -50;
    debris.angleBRand = 60;
    debris.speedMin = 13.0f;
    debris.speedRand = 13.0f;
    debris.u3C = 3;
    debris.lifeMin = 65;
    debris.lifeRand = 30;
    debris.scaleMin = 0.0626f;
    debris.scaleRand = 0.0581f;
    debris.spread = 10.376f;
    debris.u30 = -1.0480001f;
    debris.u34 = 0.99500006f;
    debris.u38 = 0.942411f;
    emit_tumbling_pieces((u8 *) &debris, 1, 0xFF, 1);

    flash.u0 = 20;
    flash.u1E = 6;
    flash.u2 = 8;
    flash.u4 = 0x6C;
    flash.u6 = 0x5103;
    flash.u8 = 0x200005;
    flash.u10 = 40;
    flash.u12 = 40;
    flash.u1F = 0xFF;
    flash.u1C = 0xFF;
    flash.uC = 0;
    flash.u14 = 0;
    flash.u18 = 0;
    flash.u1D = 0x91;
    flash.u20 = 0xFF;
    flash.u21 = 0xFF;
    flash.u22 = 0;
    flash.u23 = 0x14;
    flash.u24 = 0xC8;
    flash.u25 = 0xFF;
    flash.u26 = 50;
    flash.u28 = 5;
    flash.u2A = 50;
    flash.u2C = 1.017731f;
    flash.u30 = 175.0f;
    flash.u34 = 160.0f;
    flash.pos[0] = pos[0];
    flash.pos[1] = pos[1];
    flash.pos[2] = pos[2];
    flash.u44 = 0;
    flash.u46 = -51;
    flash.u48 = 0xFF;
    flash.u4A = 0x50;
    flash.u5C = 0x840E07;
    flash.u60 = 0x10;
    flash.u61 = -1;
    flash.u62 = 8;
    flash.u63 = 6;
    flash.u64 = 1;
    flash.u4C = 4.0f;
    flash.u50 = 13.0f;
    flash.u54 = -0.007f;
    flash.u58 = -0.006f;
    flash.u68 = 0.941177f;
    emit_particle_burst_req((u8 *) &flash, 0xFF, 0xFF, 1);
}

/* Lives pop-up (called when a life pickup is collected, after sound 0x511): a HUD object (effect_node_create, type
 * 0x60, 0x18 bytes of state) holding a sprite (texture 0xA3) and the number of lives left, one or two digit
 * sprites from the glyph table D_800AAC94. Lives = player_stat_get(0, 3) minus the current one, at most 99.
 * D_800D2458 (set by the 4:3 / wide screen code) moves the sprite and the digits. `arg0` / `arg1` are passed
 * through as the last two arguments of every HUD call (0xFF / 1 at the level start). */
s32 anim_model_fx_spawn(void *sprite, s32, f32 alpha, s32, s32, s32 depth, s32, s32); /* P97: f32 like the P95 definition */
s32 sprite2d_spawn(void *digit, s32, s32, s32, s32, s32, s32);
extern s32 D_800AAC94[10];

typedef struct {
    s32 sprite;     /* anim_model_fx_spawn handle */
    s32 digit[2];   /* sprite2d_spawn handles (digit[1] stays 0 for one digit) */
    f32 x;
    f32 angle;
    u8 done;
} LivesPopup;       /* the 0x18 bytes copied to the HUD object + 0x28 */


typedef struct {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u8 glyph;       /* +0x10 */
    u8 pad11;
    s16 u12;
    s16 u14;
    s16 u16;
    s16 u18;
    u8 u1A;
    u8 color[9];    /* +0x1B */
    s32 u24;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s32 u38;
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    u8 u44;
    u8 pad45[3];
    f32 scaleX;     /* +0x48 */
    f32 scaleY;
    f32 u50;
    f32 u54;
} LivesDigit;       /* 0x58 bytes, argument of sprite2d_spawn */

typedef struct {
    f32 pos[3];
    f32 scaleX;
    f32 scaleY;
} LivesSpritePos;   /* copied to the sprite + 0x120 */

/* was func_151BF8F0 */
void lives_popup_spawn(u8 arg0, s32 arg1) {
    LivesSprite spr;
    LivesSpritePos pos;
    LivesDigit dig;
    s32 glyphs[10];
    s32 digits[2];  /* tens, units */
    LivesPopup rec;
    s32 lives;
    s32 i;
    u8 *hud;
    LivesPopup *popup;

    effect_nodes_broadcast(0, 0x57);
    lives = player_stat_get(0, 3);
    if (lives != 0) {
        lives -= 1;
    }
    if (lives >= 100) {
        lives = 99;
    }
    digits[0] = lives / 10;
    digits[1] = lives % 10;

    rec.sprite = 0;
    bzero(rec.digit, sizeof(rec.digit));
    rec.x = 110.0f;
    rec.angle = sinf(1.9050001f);
    rec.done = 0;
    hud = (u8 *)effect_node_create(300, -1, 0x60, -1, 0, 0x49, (struct37 *)sizeof(LivesPopup), arg0, arg1);
    if (hud == NULL) {
        return;
    }
    popup = (LivesPopup *)(hud + 0x28);
    memcpy(popup, &rec, sizeof(LivesPopup));

    /* the sprite */
    spr.texture = 0xA3;
    spr.u0 = 0xC0;
    spr.u1 = -1;
    spr.u2 = 5;
    spr.u3 = 3;
    spr.u6 = 300;
    spr.uC = 8;
    spr.u10 = 0x100000;
    spr.u18 = 0x60601;
    spr.u2D = 8;
    spr.u1C = 1;
    spr.u20 = 0x38;
    spr.u24 = 0x80;
    spr.u28 = 0x20;
    spr.u38 = 0;
    spr.u4 = 0;
    spr.u14 = 0x200004;
    spr.u2C = 0;
    spr.color[0] = 0xFF;
    spr.color[1] = 0xFF;
    spr.color[2] = 0xFF;
    spr.color[3] = 0xFF;
    spr.color[4] = 0xFF;
    spr.color[5] = 0xFF;
    spr.color[6] = 0xFF;
    spr.color[7] = 0xFF;
    spr.u3C = 0;
    spr.u40 = 0;
    spr.u41 = 1;
    spr.u54 = 1;
    spr.u56 = 0xFF;
    spr.x = 300.0f;
    spr.y = (D_800D2458 != 0) ? 32.0f : 79.0f;
    spr.z = 0.0f;
    pos.pos[0] = ((f32 *)D_800A5860)[0];
    pos.pos[1] = ((f32 *)D_800A5860)[1];
    pos.pos[2] = ((f32 *)D_800A5860)[2];
    pos.scaleX = 0.30100003f;
    pos.scaleY = 0.30100003f;
    popup->sprite = anim_model_fx_spawn(&spr, 0, 1.0f /* P96: f32 parameter (was its float bits) */, 0, 0, 0x14, arg0, arg1);
    if (popup->sprite != 0) {
        memcpy((u8 *)popup->sprite + 0x120, &pos, sizeof(LivesSpritePos));
    }

    /* the digits */
    for (i = 0; i < 10; i++) {
        glyphs[i] = D_800AAC94[i];
    }
    dig.x = -500.0f;
    dig.y = (D_800D2458 != 0) ? -15.0f : -62.0f;
    dig.color[8] = 0xFF;
    dig.u18 = 0xFF;
    dig.u12 = 300;
    dig.u14 = 0x20;
    dig.u16 = 1;
    dig.color[0] = 0xFF;
    dig.color[1] = 0xFF;
    dig.color[2] = 0xFF;
    dig.color[3] = 0xFF;
    dig.u1A = 0;
    dig.color[4] = 0xFF;
    dig.color[5] = 0xFF;
    dig.color[6] = 0xFF;
    dig.color[7] = 0xFF;
    dig.u24 = 0;
    dig.u28 = 0x200004;
    dig.u2C = 0x9F0601;
    dig.u40 = 0;
    dig.u41 = 0;
    dig.u30 = 0x19;
    dig.u34 = 0x13;
    dig.u38 = 0x80;
    dig.u3C = 0x20;
    dig.u44 = 0;
    dig.u50 = 0.0f;
    dig.u54 = 0.0f;
    dig.height = 16.0f;
    dig.width = 16.0f;
    dig.scaleX = 1.0f;
    dig.scaleY = 1.0f;
    if (digits[0] == 0) {
        dig.glyph = glyphs[digits[1]];
        popup->digit[0] = sprite2d_spawn(&dig, 0, 0, 0, 0, arg0, arg1);
        popup->digit[1] = 0;
        return;
    }
    for (i = 0; i < 2; i++) {
        dig.glyph = glyphs[digits[i]];
        popup->digit[i] = sprite2d_spawn(&dig, 0, 0, 0, 0, arg0, arg1);
    }
}

s32 screen_fade_alpha(s32, u8 *);
s32 hud_lens_is_off(s32);

/* was func_151BFDCC */
void lives_popup_update(u8 *arg0) {
    u8 *sp1C;
    f32 temp_f0;
    f32 var_f2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_v1;

    if ((D_800BEAC1 != 0) || (var_v1 = arg0 + 0x28, (g_game_paused != 0))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
        return;
    }
    if (!((*(u8 *)((u8 *)var_v1 + 0x14)) & 1)) {
        if (D_800C35EA != 1) {
            sp1C = var_v1;
            if (hud_lens_is_off(0) != 0) {
                sp1C = var_v1;
                if ((screen_fade_alpha(0, arg0) == 0) && (D_800BE9B4 == 0)) {
                    (*(u8 *)((u8 *)var_v1 + 0x14)) = (u8) ((*(u8 *)((u8 *)var_v1 + 0x14)) | 1);
                    goto block_9;
                }
            }
        }
    } else {
block_9:
        temp_f0 = (*(f32 *)((u8 *)var_v1 + 0xC));
        if (temp_f0 < 20.570002f) {
            sp1C = var_v1;
            var_f2 = sinf(temp_f0 * 0.048614483f * 1.9050001f);
        } else if (temp_f0 > 89.42999f) {
            sp1C = var_v1;
            var_f2 = sinf((110.0f - temp_f0) * 0.048614483f * 1.9050001f);
        } else {
            var_f2 = (*(f32 *)((u8 *)var_v1 + 0x10));
        }
        temp_v0 = (*(u8 **)((u8 *)var_v1 + 0));
        if (temp_v0 != NULL) {
            (*(f32 *)((u8 *)temp_v0 + 0x54)) = (f32) ((var_f2 * -85.0f) + 150.0f);
            if (D_800D2458 != 0) {
                (*(f32 *)((u8 *)((*(u8 **)((u8 *)var_v1 + 0))) + 0x58)) = 32.0f;
            } else {
                (*(f32 *)((u8 *)((*(u8 **)((u8 *)var_v1 + 0))) + 0x58)) = 79.0f;
            }
        }
        temp_v0_2 = (*(u8 **)((u8 *)var_v1 + 4));
        if (temp_v0_2 != NULL) {
            (*(f32 *)((u8 *)temp_v0_2 + 0x10)) = (f32) (((((var_f2 * -85.0f) + 150.0f) * 1.0f) + 48.0f) - 12.0f);
            if (D_800D2458 != 0) {
                (*(f32 *)((u8 *)((*(u8 **)((u8 *)var_v1 + 4))) + 0x14)) = -15.0f;
            } else {
                (*(f32 *)((u8 *)((*(u8 **)((u8 *)var_v1 + 4))) + 0x14)) = -62.0f;
            }
        }
        temp_v0_3 = (*(u8 **)((u8 *)var_v1 + 8));
        if (temp_v0_3 != NULL) {
            (*(f32 *)((u8 *)temp_v0_3 + 0x10)) = (f32) ((((var_f2 * -85.0f) + 150.0f) * 1.0f) + 48.0f + 12.0f);
            if (D_800D2458 != 0) {
                (*(f32 *)((u8 *)((*(u8 **)((u8 *)var_v1 + 8))) + 0x14)) = -15.0f;
            } else {
                (*(f32 *)((u8 *)((*(u8 **)((u8 *)var_v1 + 8))) + 0x14)) = -62.0f;
            }
        }
        (*(f32 *)((u8 *)var_v1 + 0xC)) = (f32) ((*(f32 *)((u8 *)var_v1 + 0xC)) - D_800BE9A4);
        if ((*(f32 *)((u8 *)var_v1 + 0xC)) < 0.0f) {
            (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
            (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
        }
    }
}
/* was func_151C00DC */
void lives_popup_free_sprites(u8 *arg0) {
    u8 *new_var; // fakematch: pointer temp keeps arg0 out of s-regs (permuter artifact)
    struct102 *temp_a0;
    u8 *v;
    s32 i;
    new_var = arg0 + 0x28;
    if (*(s32 *)new_var != 0) {
        node_destroy((struct102 *)*(s32 *)new_var);
    }
    v = arg0 + 0x28;
    i = 0;
    do {
        temp_a0 = *(struct102 **)((v + 4) + (i * 4));
        if (temp_a0 != 0) {
            node_destroy(temp_a0);
        }
        i = (i + 1) & 0xFF;
    } while (i < 2);
}

/* was func_151C0154 */
void lives_popup_retire(struct260 * arg0) {
    lives_popup_free_sprites(arg0);
    effect_node_retire(arg0);
}

/* was func_151C0180 */
void lives_popup_delete(struct260 * arg0) {
    lives_popup_free_sprites(arg0);
    effect_node_free(arg0);
}

/* was func_151C01AC */
void lives_popup_on_message(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x57) {
        node_destroy(arg0);
    }
}
