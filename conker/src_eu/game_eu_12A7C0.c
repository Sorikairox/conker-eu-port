#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
extern u8 D_800A22BC[];


void view_sparkle_burst(u8);
s32 cam_wobble_start_preset(s32, s32, s32, s32, s32);
s32 sfx_cb_delayed_play_2d(s32, s32, s32, s32, s32, s32, s32); /* a function (init_EB00.c), not data */

/* was func_150FCFB0 */
void view_spots_flash_event(void) {
    s32 var_s0;
    struct { s8 u44; s8 u45; s16 u46; s8 u48; s8 u49; s8 u4A; } sp;

    view_sparkle_burst(0);
    view_sparkle_burst(1);
    view_sparkle_burst(2);
    sfx_emitter_start(0x2B8U, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328U, 0x1B58, (s32) &sfx_cb_delayed_play_2d, (u8 *)0x2D, 0, 0, 0);
    sfx_emitter_start(0x2B7U, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328U, 0x1B58, (s32) &sfx_cb_delayed_play_2d, NULL, 0, 0, 0);
    sfx_emitter_start(0x2B6U, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328U, 0x1B58, (s32) &sfx_cb_delayed_play_2d, (u8 *)0x5A, 0, 0, 0);
    var_s0 = 0;
    if ((D_80082FA0 + 1) > 0) {
        do {
            cam_wobble_start_preset(4, var_s0 & 0xFF, 0, 0xFF, 1);
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
    sp.u44 = 1;
    sp.u46 = 0x64;
    sp.u49 = 0xF;
    sp.u48 = 8;
    sp.u4A = -1;
    rumble_request((structEU_151D8E18 *) &sp, 0, 0xFFU, 0);
}

/* P179 */
extern s16 D_800A22B0[];
s32 spark_shower_spawn(f32 *, f32, f32, f32, f32, s32, s32);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
void emit_random_sprites(u8 *, u8, s32);

// view_sparkle_burst: P179: one flash plus 3..4 spark sprays at view `view`'s spot (D_800D9AA0[view], 0..2: s16 x, y,
/* z, radius +6, height +8; nothing when the slot is NULL). The flash (spark_shower_spawn) sits at the middle of the
 * height: size random * 4 + 12, brightness 200..255. Each spray (emit_random_sprites block, layout of emit_random_sprites in
 * game_eu_17D3C0) starts on the circle of the spot's radius at angle base + random [0, range] (D_800A22B0[view]:
 * s16 base, range; angle byte), at a random height in [y, y + height], and fans out from that angle - 40 over 80. */
/* was func_150FD140 */
void view_sparkle_burst(u8 view) {
    s16 *spot;
    s16 *arc;
    f32 pos[3];
    f32 size;
    u32 r;
    s16 n;
    struct {
        s16 angle;      /* +0x00 */
        s16 angleRange; /* +0x02 */
        s16 pitch;      /* +0x04 */
        s16 pitchRange; /* +0x06 */
        s32 count;      /* +0x08 */
        s32 countRange; /* +0x0C */
        f32 pos[3];     /* +0x10 */
        f32 f1C;
        f32 f20;
        f32 f24;
        f32 f28;
        f32 f2C;
        f32 f30;
        s32 i34;
        s32 i38;
        f32 f3C;
        f32 f40;
        f32 f44;
        f32 f48;
        s16 h4C;
        s16 h4E;
        s16 h50;
        s16 h52;
        s16 h54;
        s16 h56;
        s8 b58;
    } spray;
    u8 a;

    if (view >= 3) {
        return;
    }
    spot = (s16 *) D_800D9AA0[view];
    if (spot == NULL) {
        return;
    }
    pos[0] = spot[0];
    pos[1] = spot[1] + spot[4] * 0.5f;
    pos[2] = spot[2];
    size = random_float();
    r = random_int();
    spark_shower_spawn(pos, size * 4.0f + 12.0f, 6.6943097f, r % 56 + 200, 2.6090002f, 0xFF, 1);
    n = (random_int() & 1) + 3;
    if (n <= 0) {
        return;
    }
    spray.angleRange = 0x50;
    spray.pitch = -0x20;
    spray.pitchRange = 0x2B;
    spray.count = 1;
    spray.countRange = 8;
    spray.f1C = 249.0f;
    spray.f20 = 451.0f;
    spray.f24 = 506.0f;
    spray.f28 = 100.0f;
    spray.f2C = 1505.0f;
    spray.f30 = 1511.0f;
    spray.i34 = 3;
    spray.i38 = 2;
    spray.f3C = 90.0f;
    spray.f40 = 0.813f;
    spray.f44 = -2.0f;
    spray.f48 = 1.085f;
    spray.h4C = 0xC;
    spray.h4E = 0x32;
    spray.h50 = 0x64;
    spray.h52 = 0x64;
    spray.h54 = 0xC;
    spray.h56 = 0xC;
    spray.b58 = -1;
    arc = &D_800A22B0[view * 2];
    do {
        a = random_int() % (u32) (arc[1] + 1) + arc[0];
        spray.angle = a - 0x28;
        vec2_from_angle_byte(a, spot[3], &spray.pos[0], &spray.pos[2]);
        spray.pos[0] += spot[0];
        spray.pos[2] += spot[2];
        spray.pos[1] = random_float() * spot[4] + spot[1];
        emit_random_sprites((u8 *) &spray, 0xFF, 1);
        n--;
    } while (n > 0);
}

f32 cam_wobble_fade_by_distance(void *, void *, s32, s32, f32);

/* view_spot_distance_fade: P238: entry 0 of D_8008B734 (cam_wobble_update, asm, passes the object in a0 and stores f0).
 * Fade factor of `obj` against view 0's spot (D_800D9AA0[0], s16 x / y / z as floats): cam_wobble_fade_by_distance with near
 * distance 2007, range 9005 and scale 1 / 9005 (D_800A22FC, 0x38E8E334). 1.0 when there is no spot. The near /
 * range parameters are f32 bit patterns in cam_wobble_fade_by_distance's s32 slots (it reads them as floats). */
/* was func_150FD49C */
f32 view_spot_distance_fade(u8 *obj) {
    f32 pos[3];
    f32 nearDist = 2007.0f;
    f32 range = 9005.0f;
    s16 *spot = (s16 *) D_800D9AA0[0];

    if (spot == NULL) {
        return 1.0f;
    }
    pos[0] = spot[0];
    pos[1] = spot[1];
    pos[2] = spot[2];
    return cam_wobble_fade_by_distance(obj, pos, *(s32 *) &nearDist, *(s32 *) &range, 0.00011104942f);
}

/* was func_150FD530 */
void level_update_sfx_tick_a(s32 arg0) {
    sfx_cooldown_tick();
}

s32 collision_floor_probe(u8 *, u16, f32, u8 *);
void hitinfo_from_obj_floor(void *, u8 *);
s32 obj_send_hit(struct127 *, s32, u16, s32);
s32 light_create_flicker_preset(s8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 memcpy(u8 *, struct127 **, s32);

/* was func_150FD554 */
void bound_cloud_spawn(struct127 *arg0, u8 arg1, s32 arg2) {
    struct {
        s8 u60;
        s8 u61;
        s16 u62;
        s16 u64;
        u8 pad66[0x2];
        s32 u68;
        s32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        u8 pad8C[0x8];
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s32 uA8;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        s16 uB4;
        s16 uB6;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        s16 uC6;
        s8 uC8;
        u8 padC9[0xB];
        struct127 * uD4;
        u8 uD8;
        u8 padD9[0x3];
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 uF8;
        s32 uFC;
        f32 u100;
        struct_eu_bytes24 u104;
        u16 u128;
        u8 pad12A[0x2];
        s8 u12C;
        s8 u12D;
        u8 pad12E[0x2];
        s8 u130;
        s8 u131;
        s16 u132;
        s16 u134;
        u8 pad136[0x2];
        s32 u138;
        s32 u13C;
        s8 u140;
        s8 u141;
        s8 u142;
        s8 u143;
        f32 u144;
        f32 u148;
        s32 u14C;
        u8 pad150[0x8];
        s32 u158;
        u8 pad15C[0x8];
        f32 u164;
        f32 u168;
        f32 u16C;
        s32 u170;
        s8 u174;
        s8 u175;
        s8 u176;
        s8 u177;
        s32 u178;
        s8 u17C;
        u8 pad17D[0x3];
        s32 u180;
        s16 u184;
        s16 u186;
        f32 u188;
        f32 u18C;
        f32 u190;
        u8 pad194[0x3];
        u8 u197;
        f32 u198;
        f32 u19C;
        f32 u1A0;
        f32 u1A4;
        s32 u1A8;
    } sp;
    f32 temp_f0;
    f32 temp_f16;
    s8 var_v0;
    u8 *temp_t1;
    u8 *temp_t4;
    u8 *temp_s0;
    u8 *temp_v0;

    if ((s32) arg0->unk7 >= 0xFF) {
        sp.u198 = arg0->x_position;
        sp.u188 = sp.u198;
        sp.u18C = arg0->y_position + 100.0f;
        sp.u1A0 = arg0->z_position;
        sp.u190 = sp.u1A0;
        hitinfo_from_obj_floor(&sp.u1A4, arg0);
        if (collision_floor_probe(&sp.u188, 0, -10000.0f, &sp.u1A4) /* P93: was the bit pattern 0xC61C4000 as an int */ != 0) {
            sp.u197 = 1;
            sp.u19C = sp.u1A4;
        } else {
            sp.u197 = 0;
            sp.u19C = arg0->y_position;
        }
        obj_send_hit(arg0, 0x39, arg0->unk7A, -1);
        sp.uD4 = arg0;
        sp.uDC = 60.0f;
        sp.uD8 = arg0->unique_id;
        sp.uE0 = 50.0f;
        temp_f0 = random_float();
        sp.u12C = 0;
        sp.uE8 = -2048.0f;
        sp.uEC = -2048.0f;
        sp.uE4 = temp_f0 * 6.2831855f;
        sp.uF0 = random_float() * 6.2831855f;
        temp_f16 = random_float() * 6.2831855f;
        sp.uF8 = 0;
        sp.uFC = 0;
        sp.u100 = 0.0f;
        sp.uF4 = temp_f16;
        sp.u104 = *(struct_eu_bytes24 *)(&sp.u1A4);
        sp.u128 = sfx_emitter_start(0x69EU, (s16) (s32) sp.u198, (s16) (s32) sp.u19C, (s16) (s32) sp.u1A0, 0x7D00, 0xBB8U, 0x1F4, 0, NULL, 0, 0, 0);
        if (sp.u197 != 0) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        sp.u12D = var_v0;
        sp.u130 = 0x59;
        sp.u131 = 0xB;
        sp.u132 = 0x5B1A;
        sp.u134 = 0x12C;
        sp.u138 = 0;
        sp.u13C = 0;
        sp.u140 = 0xFF;
        sp.u141 = 0;
        sp.u142 = 0;
        sp.u143 = 0xFF;
        sp.u174 = 0xFF;
        sp.u144 = 0.0f;
        sp.u148 = 1500.0f;
        temp_t1 = ((u8 *)&D_800A5860);
        (*(f32 *)((u8 *)(&sp.u14C) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u198) + 0));
        (*(s32 *)((u8 *)(&sp.u14C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u198) + 4));
        (*(s32 *)((u8 *)(&sp.u14C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u198) + 8));
        (*(s32 *)((u8 *)(&sp.u158) + 0)) = (s32) (*(s32 *)((u8 *)temp_t1 + 0));
        (*(s32 *)((u8 *)(&sp.u158) + 4)) = (s32) (*(s32 *)((u8 *)temp_t1 + 4));
        (*(s32 *)((u8 *)(&sp.u158) + 8)) = (s32) (*(s32 *)((u8 *)temp_t1 + 8));
        sp.u168 = 0.0f;
        sp.u170 = 0x24EC0008;
        sp.u175 = 0xFF;
        sp.u176 = 0;
        sp.u177 = 6;
        sp.u178 = 0;
        sp.u17C = 0xFF;
        sp.u180 = 0;
        sp.u184 = 1;
        sp.u186 = 0xFF;
        sp.u164 = 1.0f;
        sp.u16C = 1.0f;
        temp_v0 = effect3d_spawn_full(&sp.u130, (s32) ((u8 *)&D_800A22BC), 0U, 0x2BU, 0U, 0x24U, 0U, 0, 0, 0x5C, (u8) (s32) arg1, arg2);
        temp_s0 = temp_v0 + 0x110;
        if (temp_v0 != NULL) {
            memcpy(temp_s0, &sp.uD4, 0x5C);
            sp.uC6 = 0x12C;
            sp.uC8 = 6;
            sp.uC4 = 2;
            sp.uC5 = 2;
            sp.uB8 = (s32) sp.u198;
            sp.uBC = (s32) sp.u19C;
            sp.uC0 = (s32) sp.u1A0;
            (*(s32 *)((u8 *)temp_s0 + 0x24)) = light_create_flicker_preset(&sp.uC4, &sp.uB8, 0xFF, 0, 0, 0xFF, 0, 0, 0x17, (s32) arg1, arg2);
            if (sp.u197 != 0) {
                temp_t4 = ((u8 *)&D_800A4AA0);
                sp.u60 = 3;
                sp.u61 = 0;
                sp.u62 = 0x3103;
                sp.u64 = 0x12C;
                sp.u68 = 0;
                sp.u6C = 0;
                sp.u70 = 0xFF;
                sp.u71 = 0;
                sp.u72 = 0;
                sp.u73 = 0xFF;
                sp.uA4 = 0xFF;
                sp.u74 = 1.0f;
                sp.u78 = 1.0f;
                sp.u80 = sp.u19C + 5.0f;
                sp.u7C = sp.u198;
                sp.u84 = sp.u1A0;
                (*(s32 *)((u8 *)(&sp.u88) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
                (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
                (*(s32 *)((u8 *)(&sp.u88) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
                sp.u94 = 1.0f;
                sp.u98 = 1.0f;
                sp.u9C = 1.0f;
                sp.uA0 = 0x04EC0008;
                sp.uA5 = 0xFF;
                sp.uA6 = 0;
                sp.uA7 = 6;
                sp.uA8 = 0;
                sp.uAC = 0xFF;
                sp.uB0 = 0;
                sp.uB4 = 1;
                sp.uB6 = 0xFF;
                (*(s32 *)((u8 *)temp_s0 + 0x28)) = effect3d_spawn_oriented((s32) &sp.u60, (s32) ((u8 *)&D_800A4AA0), 0U, 0U, 0U, 0U, 0, 50.0f, 50.0f, 0, (s32) &sp.u1A8, 0, 0, 0U, 0, (u8) (s32) arg1, arg2);
            }
        }
    }
}
/* P146 */
extern f32 D_800A2310;
extern f32 D_800A2314;
extern f32 D_800A2318;
extern f32 D_800A231C;
extern f32 D_800A2320;
extern f32 D_800A2324;
extern f32 D_800A2328;
extern f32 D_800A232C;
extern f32 D_800A2330;
extern f32 D_800A2334;
extern f32 D_800A2338;
void obj_tint_set_flash(u8 *, s32, s32, s32, s32, s32, s32);
void obj_angle_point_effect(u8 *, s16, s16, u8, s32);
void cam_shake_all_players(u8 *, f32, f32, f32, u8, u8, s32);
void fx_scorch_decal_spawn(f32, u8, s32, u8 *, s16, u8, u8, u8, u8, u8, u8, s32);
void fx_debris_emitter_spawn(f32 *, s16, u8, s32);
// bound_cloud_update: update handler (g_effect3d_update2_fns slot 43) of a cloud effect that can be bound to an object. The
// state block at +0x110 holds the object (+0x110, valid while its +0 is set and its id +0x3B equals +0x114), the
// peak alpha scale (+0x118), the remaining life (+0x11C), a pulse phase (+0x120), two wobble phases (+0x12C,
// +0x130) with their outputs (+0x124, +0x128), a linked effect (+0x138), a spawn accumulator (+0x13C), a height
// (+0x140), a sound block (+0x144), a "burst done" byte (+0x168) and flags (+0x169). A bound object is tinted
// and gets random particles (obj_angle_point_effect) at a random rate; the effect follows its x/z. The scale fades in
// over life 50..20, holds to 10, then fades out; at life 10 the burst fires once (object animation 0x16 and a
// sound, two shock waves, and with flag 1 a smoke puff + flash). Alpha +0x5C pulses (sin), the linked effect
// copies scale / alpha / x / z. Returns 0 once the life drops below 0.
/* was func_150FDA94 */
s32 bound_cloud_update(u8 *fx) {
    u8 *st = fx + 0x110;
    u8 *obj = *(u8 **)st;
    u8 *link;
    f32 x;
    f32 z;
    f32 pos[3];
    f32 life;
    f32 scale;
    f32 size;
    s32 r0;
    s32 r1;

    if (obj != NULL) {
        if (*(s32 *)obj == 0 || st[4] != obj[0x3B]) {
            *(u8 **)st = NULL;
            obj = NULL;
        }
        /* as the original: reads through obj even after clearing it */
        x = *(f32 *)(obj + 0x14);
        z = *(f32 *)(obj + 0x1C);
    } else {
        x = *(f32 *)(fx + 0x34);
        z = *(f32 *)(fx + 0x3C);
    }
    if (obj != NULL) {
        obj_tint_set_flash(obj, 0xFF, 0, 0, 0xFF, 0, 4);
        *(f32 *)(st + 0x2C) += (D_800A2310 + random_float() * D_800A2314) * D_800BE9A4;
        while (*(f32 *)(st + 0x2C) > 1.0f) {
            r0 = random_int();
            r1 = random_int();
            obj_angle_point_effect(obj, (s16)(r0 & 0xFF), (s16)((u32)r1 % 101 - 63), fx[0xC], fx[1]);
            *(f32 *)(st + 0x2C) -= 1.0f;
        }
    }
    life = *(f32 *)(st + 0xC);
    if (life > 20.0f) {
        *(f32 *)(fx + 0x2C) = (50.0f - life) * D_800A2318 * *(f32 *)(st + 0x8);
    } else if (life > 10.0f) {
        *(f32 *)(fx + 0x2C) = *(f32 *)(st + 0x8);
    } else {
        *(f32 *)(fx + 0x2C) = life * D_800A231C * *(f32 *)(st + 0x8);
        if (st[0x58] == 0) {
            if (obj != NULL) {
                obj_send_hit((struct127 *)obj, 0x16, *(u16 *)(obj + 0x7A), -1);
                sound_play_at(0x69D, 0x7D00, 0, 0, 0, (s16)(s32) * (f32 *)(fx + 0x34),
                              (s16)(s32) * (f32 *)(fx + 0x38), (s16)(s32) * (f32 *)(fx + 0x3C), 500, 3000);
            }
            st[0x58] = 1;
            rumble_all_players_at((struct17 *)(fx + 0x34), 506.0f, 1013.0f, 0.0009871669f, 15, 20, fx[0xC], fx[1]);
            cam_shake_all_players(fx + 0x34, 506.0f, 1013.0f, 0.0009871669f, 5, fx[0xC], fx[1]);
            if (st[0x59] & 1) {
                pos[0] = *(f32 *)(fx + 0x34);
                pos[1] = *(f32 *)(st + 0x30);
                pos[2] = *(f32 *)(fx + 0x3C);
                size = random_float();
                r0 = random_int();
                r1 = random_int();
                fx_scorch_decal_spawn(size * 78.0f + 125.0f, ((u32)r0 % 76 + 180) & 0xFF, (s32)(st + 0x34), (u8 *)pos,
                              (u32)r1 % 207 + 302, 0, 1, 0, 0, 0, fx[0xC], 0);
                fx_debris_emitter_spawn(pos, (s16)((u32)random_int() % 80 + 243), fx[0xC], fx[1]);
            }
        }
    }
    fx[0x5C] = (u32)(sinf(*(f32 *)(st + 0x10)) * 57.0f + 198.0f);
    *(f32 *)(st + 0x10) += D_800A2320 * D_800BE9A4;
    *(f32 *)(st + 0x10) = wrap_angle_rad(*(f32 *)(st + 0x10));
    *(f32 *)(st + 0x1C) += D_800A2324 * D_800BE9A4;
    *(f32 *)(st + 0x20) += D_800A2328 * D_800BE9A4;
    *(f32 *)(st + 0x1C) = wrap_angle_rad(*(f32 *)(st + 0x1C));
    *(f32 *)(st + 0x20) = wrap_angle_rad(*(f32 *)(st + 0x20));
    *(f32 *)(st + 0x14) = fast_sinf(*(f32 *)(st + 0x1C)) * D_800A232C + D_800A2330;
    *(f32 *)(st + 0x18) = fast_sinf(*(f32 *)(st + 0x20)) * 1192.0f + D_800A2334;
    link = *(u8 **)(st + 0x28);
    if (link != NULL) {
        scale = *(f32 *)(fx + 0x2C) * D_800A2338;
        *(f32 *)(link + 0x30) = scale;
        *(f32 *)(*(u8 **)(st + 0x28) + 0x2C) = scale;
        (*(u8 **)(st + 0x28))[0x5C] = fx[0x5C];
        *(f32 *)(*(u8 **)(st + 0x28) + 0x34) = x;
        *(f32 *)(*(u8 **)(st + 0x28) + 0x3C) = z;
    }
    *(f32 *)(fx + 0x34) = x;
    *(f32 *)(fx + 0x3C) = z;
    *(f32 *)(st + 0xC) -= D_800BE9A4;
    if (*(f32 *)(st + 0xC) < 0.0f) {
        return 0;
    }
    return 1;
}

/* was func_150FE08C */
void bound_cloud_handle_event(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 new_var2; // fakematch: permuter temp
  u8 new_var; // fakematch: permuter temp
  u8 *v = arg0 + 0x110;
  if (arg2 == 0x2D)
  {
    if ((*((s32 *) arg1)) == (*((s32 *) v)))
    {
      *((s32 *) v) = *((s32 *) (arg1 + 4));
      v[4] = arg1[9];
      return;
    }
    if ((*((s32 *) (arg1 + 4))) == (*((s32 *) v)))
    {
      *((s32 *) v) = *((s32 *) arg1);
      v[4] = arg1[8];
      dummy_label_617528: // fakematch: permuter artifact (unused label)
      ;

      ;
      ;
    }
  }
  else
    if (arg2 == 0)
  {
    new_var2 = *((s32 *) arg1);
    if ((new_var2 == (*((s32 *) v))) || ((new_var = v[4] ^ 0) == arg1[4])) // fakematch: ^ 0
    {
      *((s32 *) v) = 0;
    }
  }
}

/* was func_150FE120 */
u8 *bound_cloud_draw(u8 *arg0, s16 arg1) {
    u8 *v = (u8 *)sprite_quad_build_screen_b((s32)arg0, arg1);
    if (v != NULL) {
        *(s16 *)(v + 0x8) = *(f32 *)(arg0 + 0x124);
        *(s16 *)(v + 0x18) = *(f32 *)(arg0 + 0x128);
        *(s16 *)(v + 0x28) = *(f32 *)(arg0 + 0x128);
        *(s16 *)(v + 0x38) = *(f32 *)(arg0 + 0x124);
    }
    return v;
}

/* was func_150FE1AC */
void bound_cloud_free(u8 *arg0)
{
  u8 *v = arg0 + 0x110; // fakematch: v defined first so IDO keeps it as a separate pointer (not folded)
  
  if (*(s32 *)(arg0 + 0x134) != 0) { node_destroy(*(struct102 **)(arg0 + 0x134)); }
  if (*(struct102 **)(v + 0x28)) { node_destroy(*(struct102 **)(v + 0x28)); } // fakematch: pointer-typed test gives one load (s32 test double-loads like line above)
  if (*(u16 *)(v + 0x54) != 0) { sound_voice_stop(*(u16 *)(v + 0x54)); }
  if (*(u16 *)(v + 0x56) != 0) sound_voice_stop(*(u16 *)(v + 0x56));
}

/* was func_150FE22C */
void bound_cloud_retire(void *arg0) {
    bound_cloud_free(arg0);
    effect3d_retire(arg0);
}

/* was func_150FE258 */
void bound_cloud_delete(void *arg0) {
    bound_cloud_free(arg0);
    effect3d_free(arg0);
}
