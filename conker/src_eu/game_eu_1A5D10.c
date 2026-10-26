#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* 0x38-byte particle template copied to rec +0x10 (swarm_spawn) */
typedef struct {
    s32 u0;         /* 0x00 D_8008CE04 */
    u8 *owner;      /* 0x04 the 0x3A emitter record */
    u8 pad8[4];     /* 0x08 not set */
    s16 u0C;        /* 0x0C */
    s16 u0E;        /* 0x0E */
    s16 pos[3];     /* 0x10 */
    s16 u16;        /* 0x16 */
    s16 u18;        /* 0x18 */
    s16 u1A;        /* 0x1A */
    u8 pad1C[3];    /* 0x1C not set */
    u8 u1F;         /* 0x1F */
    s16 u20;        /* 0x20 */
    s16 u22;        /* 0x22 */
    s16 size[2];    /* 0x24 */
    s16 span;       /* 0x28 */
    u8 u2A;         /* 0x2A */
    u8 life;        /* 0x2B */
    u8 rgba[4];     /* 0x2C */
    u8 pad30[4];    /* 0x30 not set */
    s16 u34;        /* 0x34 */
    u8 pad36[2];    /* 0x36 not set */
} Puff7F90;

extern s32 D_8008CE04;
f32 math_cos_u8(u8 arg0);
#endif

#ifdef NON_MATCHING
// debris_burst_spawn: makes a type 0x3A emitter record (attached to `pos` when given, else at the packed point x, y, z)
// and `count` type 0x3B particles around (x, z) within radius 50 at height y - 78 + [0, 255], each a copy of a 0x38-byte
// template (size 0x118, or 0x8C when w6 is set; life 7..14 frames). Stops at the first failed allocation.
/* was func_15177F90 */
void swarm_spawn(u8 count, u8 *pos, s32 arg2, s32 x, s32 y, s32 z, s32 arg6, s32 span, s32 flag, s32 arg9, s32 w6) {
    Puff7F90 t;
    u8 *rec;
    s16 size;
    s32 i;
    u8 a;
    f32 c;
    f32 s;
    f32 r;
    s32 px;
    s32 pz;
    s32 py;

    rec = node_alloc(0x3A, 0, 0x38, 0, (u8) flag, 1);
    if (rec == NULL) {
        return;
    }
    size = (w6 == 0) ? 0x118 : 0x8C;
    if (pos != NULL) {
        *(u8 **) (rec + 0x10) = pos;
        *(s32 *) (rec + 0x14) = 0x80000000;
    } else {
        *(s32 *) (rec + 0x10) = (x << 16) | (y & 0xFFFF);
        *(s32 *) (rec + 0x14) = z << 16;
    }
    *(s32 *) (rec + 0x18) = x;
    *(s32 *) (rec + 0x1C) = y;
    *(s32 *) (rec + 0x20) = z;
    *(s16 *) (rec + 0x30) = 0;
    *(s16 *) (rec + 0x32) = 0x3C0;
    rec[0x35] = count;
    rec[0x34] = (u8) arg2;
    rec[0x37] = (u8) arg9;
    *(s16 *) (rec + 0x2E) = 0;

    t.u0 = D_8008CE04;
    t.owner = rec;
    t.u16 = 0;
    t.u18 = 0;
    t.u1A = 0;
    t.u1F = 6;
    t.u20 = 0;
    t.u22 = 0;
    t.size[0] = size;
    t.size[1] = size;
    t.u2A = 0;
    t.rgba[0] = 0xFF;
    t.rgba[1] = 0xFF;
    t.rgba[2] = 0xFF;
    t.rgba[3] = 0xFF;
    t.u34 = 0;
    t.span = span;
    for (i = 0; i < count; i++) {
        a = random_int();
        c = math_sin_u8(a);
        s = math_cos_u8(a);
        r = (f32) (random_int() & 0xFFFF) * 50.0f * (1.0f / 65536.0f);
        px = (f32) x + r * c;
        pz = (f32) z + r * s;
        py = (u8) random_int() + y - 0x4E;
        t.life = (random_int() & 7) + 7;
        t.u0C = 0;
        t.u0E = 0;
        t.pos[0] = px;
        t.pos[1] = py;
        t.pos[2] = pz;
        rec = node_alloc(0x3B, 0, 0x4C, 0, (u8) flag, 1);
        if (rec == NULL) {
            return;
        }
        bcopy(&t, rec + 0x10, 0x38);
        rec[0x48] = 0xFF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/swarm_spawn.s")
#endif

#ifdef NON_MATCHING
s32 vec3_heading_u8(struct17 *arg0);
float sqrtf(float);
extern u8 *D_8008CDEC[];

// bird_follow_update: steering of a flying follower sprite (leader *+0x14: position s32 +0x18 / +0x1C / +0x20, height
// offset s16 +0x30, speed s16 +0x32; fast when the speed is above 0x3C0). Every 10 frames (2 when fast; counter in
// the low nibble of +0x18, heading target in bits 4..11) it re-aims at the leader (vec3_heading_u8 of leader - own
// x / z position +0x20 / +0x24, plus a random -15..16). The heading +0x2A (0..0xFF) turns towards the target by
// +0x3B (doubled when fast) the short way round; the velocity +0x26 / +0x28 = (cos, -sin)(heading) * leader speed.
// The climb +0x32 is 100..227, negated when the leader is lower than own +0x22 - 50 - random 0..63; +0x30 is
// clamped to +-0x400. The sprite frame +0x10 (D_8008CDEC[6..9]) and mirror flag +0x44 come from the velocity seen
// from the camera angle (D_800DBFF0 +0x380 in degrees); +0x1C bit 8 toggles every frame.
/* was func_151787D8 */
void swarm_follower_update(u8 *obj) {
    u8 *lead = *(u8 **) (obj + 0x14);
    s32 heading = *(s16 *) (obj + 0x2A);
    struct17 rel;
    f32 px;
    f32 py;
    f32 pz;
    f32 tx;
    f32 tz;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 inv;
    f32 speed;
    f32 s;
    f32 c;
    s32 fast;
    s32 count;
    s32 target;
    s32 step;
    s32 diff;
    s32 climb;
    s32 v;
    s32 frame;
    u8 view;

    tx = *(s32 *) (lead + 0x18);
    px = tx;
    py = *(s32 *) (lead + 0x1C);
    tz = *(s32 *) (lead + 0x20);
    pz = tz;
    fast = *(s16 *) (lead + 0x32) >= 0x3C1;
    py += *(s16 *) (lead + 0x30);
    /* distance from the leader to the aim point (always 0 here: the aim point is the leader) */
    dx = px - tx;
    dz = pz - tz;
    dist = sqrtf(dx * dx + dz * dz);
    if (100.0f < dist) {
        inv = 100.0f / dist;
        px = dx * inv + tx;
        pz = dz * inv + tz;
    }
    rel.unk0 = px - *(s16 *) (obj + 0x20);
    rel.unk8 = pz - *(s16 *) (obj + 0x24);
    count = *(s32 *) (obj + 0x18) & 0xF;
    if (count == 0) {
        target = vec3_heading_u8(&rel);
        target = target + (random_int() & 0x1F) - 0xF;
        count = fast ? 2 : 10;
    } else {
        target = (*(s32 *) (obj + 0x18) >> 4) & 0xFF;
        count--;
    }
    *(s32 *) (obj + 0x18) = ((target & 0xFF) << 4) | count;
    step = obj[0x3B];
    if (fast) {
        step *= 2;
    }
    step = (heading < target) ? step : -step;
    diff = target - heading;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x80) {
        step = -step;
    }
    heading += step;
    if (heading < 0) {
        heading += 0x100;
    } else if (heading >= 0x100) {
        heading -= 0x100;
    }
    speed = *(s16 *) (lead + 0x32);
    v = (s32) (math_sin_u8(heading & 0xFF) * speed);
    s = math_cos_u8(heading & 0xFF);
    *(s16 *) (obj + 0x26) = v;
    *(s16 *) (obj + 0x2A) = heading;
    *(s16 *) (obj + 0x28) = (s32) (-s * speed);
    climb = (random_int() & 0x7F) + 100;
    if ((f32) (u32) (random_int() & 0x3F) + (py + 50.0f) < (f32) *(s16 *) (obj + 0x22)) {
        *(s16 *) (obj + 0x32) = -climb;
    } else {
        *(s16 *) (obj + 0x32) = climb;
    }
    if (*(s16 *) (obj + 0x30) > 0x400) {
        *(s16 *) (obj + 0x30) = 0x400;
    } else if (*(s16 *) (obj + 0x30) < -0x400) {
        *(s16 *) (obj + 0x30) = -0x400;
    }
    view = (u32) (*(f32 *) ((u8 *) D_800DBFF0 + 0x380) * 0.7111111f); /* D_800A75C0 = 256 / 360 */
    c = math_sin_u8(view);
    s = math_cos_u8(view);
    v = (s32) ((f32) *(s16 *) (obj + 0x26) * s - (f32) *(s16 *) (obj + 0x28) * c);
    if (v >= 0) {
        *(s16 *) (obj + 0x44) = 0;
    } else {
        *(s16 *) (obj + 0x44) = 4;
        v = -v;
    }
    if (v > 0x200) {
        frame = 6;
    } else if (v > 0x100) {
        frame = 7;
    } else if ((s32) ((f32) *(s16 *) (obj + 0x26) * c + (f32) *(s16 *) (obj + 0x28) * s) >= 0) {
        frame = 8;
    } else {
        frame = 9;
    }
    *(s16 *) (obj + 0x1C) ^= 0x100;
    *(u8 **) (obj + 0x10) = D_8008CDEC[frame];
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/swarm_follower_update.s")
#endif

#ifdef NON_MATCHING
s32 node_billboard_draw(s32 gdl, u8 *obj, s16 player);

/* P186: the asm leaves arg1 / arg2 in a1 / a2 at the jal and node_billboard_draw reads them (object, player view):
 * pass them (dropped-arguments lesson). */
/* was func_15178CC0 */
s32 swarm_follower_draw(s32 arg0, u8 *arg1, s16 arg2) {
    u8 *p = *(u8 **)(arg1 + 0x14);
    if (p[0x36] & (1 << arg2)) {
        return node_billboard_draw(arg0, arg1, arg2);
    }
    return arg0;
}
#else
s32 swarm_follower_draw(s32 arg0, u8 *arg1, s16 arg2) {
    u8 *p = *(u8 **)(arg1 + 0x14);
    if (p[0x36] & (1 << arg2)) {
        return node_billboard_draw(arg0);
    }
    return arg0;
}
#endif

/* was func_eu_15178D14 */
void swarm_empty_stub(void) {}

#ifdef NON_MATCHING
extern s32 D_80082FA0;
extern u8 D_800DA030[];
s32 camera_view_test_sphere(s32, s32 *, f32, f32, f32, f32, f32, f32);

// debris_emitter_update: per-frame update of a swarm_spawn emitter record. Saves the position (+0x18..+0x20, s32)
// as the previous one (s16 +0x28..+0x2C) and moves it at most 16 units towards the target: the f32 point that +0x10
// points to when s16 +0x14 is -0x8000, else the s16 point at +0x10. Sets the per-view visibility mask +0x36
// (camera_view_test_sphere for views 0..D_80082FA0, radius 100, range 2500), keeps the rumble sound 0x4A2 (handle +0x2E)
// playing when +0x37 is set, and moves the s16 +0x32 by (frame step + 40) towards 0x780 while the target (raised by
// s16 +0x30) is more than 100 units away, else towards 0x3C0.
/* was func_15178D1C */
void swarm_leader_update(u8 *rec) {
    f32 *p;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 k;
    s32 mask;
    s32 i;
    s32 ix;
    s32 iy;
    s32 iz;
    s32 d2;

    *(s16 *) (rec + 0x28) = *(s32 *) (rec + 0x18);
    *(s16 *) (rec + 0x2A) = *(s32 *) (rec + 0x1C);
    *(s16 *) (rec + 0x2C) = *(s32 *) (rec + 0x20);
    if (*(s16 *) (rec + 0x14) == -0x8000) {
        p = *(f32 **) (rec + 0x10);
        tx = p[0];
        ty = p[1];
        tz = p[2];
    } else {
        tz = *(s16 *) (rec + 0x14);
        tx = *(s16 *) (rec + 0x10);
        ty = *(s16 *) (rec + 0x12);
    }
    x = *(s32 *) (rec + 0x18);
    y = *(s32 *) (rec + 0x1C);
    z = *(s32 *) (rec + 0x20);
    dx = tx - x;
    dy = ty - y;
    dz = tz - z;
    d = sqrtf(dx * dx + dy * dy + dz * dz);
    if (1.0f < d) {
        k = 16.0f / d;
        *(s32 *) (rec + 0x18) = x + dx * k;
        *(s32 *) (rec + 0x1C) = y + dy * k;
        *(s32 *) (rec + 0x20) = z + dz * k;
    }
    mask = 0;
    for (i = 0; i <= D_80082FA0; i++) {
        if (camera_view_test_sphere(D_800BE628 + i * 0x180, (s32 *) (D_800DA030 + i * 0x40), *(s32 *) (rec + 0x18),
                          *(s32 *) (rec + 0x1C), *(s32 *) (rec + 0x20), 100.0f, 100.0f, 2500.0f) != 0) {
            mask |= 1 << i;
        }
    }
    rec[0x36] = mask;
    if (rec[0x37] != 0) {
        if (*(u16 *) (rec + 0x2E) == 0) {
            *(u16 *) (rec + 0x2E) = sound_play_at(0x4A2, 10000, 0, 0, 0, *(s32 *) (rec + 0x18),
                                                  *(s32 *) (rec + 0x1C), *(s32 *) (rec + 0x20), 100, 800);
        } else {
            sound_voice_update_3d(*(u16 *) (rec + 0x2E), 10000, 0, 0, 0, *(s32 *) (rec + 0x18), *(s32 *) (rec + 0x1C),
                          *(s32 *) (rec + 0x20), 100, 800);
        }
    }
    if (*(s16 *) (rec + 0x14) == -0x8000) {
        p = *(f32 **) (rec + 0x10);
        ix = p[0];
        iy = p[1];
        iz = p[2];
    } else {
        ix = *(s16 *) (rec + 0x10);
        iy = *(s16 *) (rec + 0x12);
        iz = *(s16 *) (rec + 0x14);
    }
    ix -= *(s32 *) (rec + 0x18);
    iy = iy + *(s16 *) (rec + 0x30) - *(s32 *) (rec + 0x1C);
    iz -= *(s32 *) (rec + 0x20);
    d2 = ix * ix + iy * iy + iz * iz;
    if (d2 > 10000) {
        if (*(s16 *) (rec + 0x32) != 0x780) {
            *(s16 *) (rec + 0x32) += D_800BE9E4 + 0x28;
            if (*(s16 *) (rec + 0x32) > 0x780) {
                *(s16 *) (rec + 0x32) = 0x780;
            }
        }
    } else if (*(s16 *) (rec + 0x32) != 0x3C0) {
        *(s16 *) (rec + 0x32) -= D_800BE9E4 + 0x28;
        if (*(s16 *) (rec + 0x32) < 0x3C0) {
            *(s16 *) (rec + 0x32) = 0x3C0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/swarm_leader_update.s")
#endif

/* was func_15179108 */
u8 *swarm_find_by_id(u8 arg0) {
    u8 *var_v1 = D_800DD368;

    while (var_v1 != NULL) {
        if (arg0 == var_v1[0x34]) {
            return var_v1;
        }
        var_v1 = *(u8 **)(var_v1 + 8);
    }
    return NULL;
}

/* was func_15179154 */
void swarm_set_target_ptr(u8 arg0, s32 arg1, s16 arg2) {
    u8 *temp_v0;

    temp_v0 = swarm_find_by_id(arg0);
    if (temp_v0 != NULL) {
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0x80000000;
        (*(s16 *)((u8 *)temp_v0 + 0x30)) = arg2;
    }
}

/* was func_151791A4 */
void swarm_set_target_pos(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    u8 *temp_v0;
    temp_v0 = swarm_find_by_id(arg0);
    if (temp_v0 != NULL) {
        *(s32 *)(temp_v0 + 0x10) = (arg1 << 0x10) | (arg2 & 0xFFFF);
        *(s32 *)(temp_v0 + 0x14) = arg3 << 0x10;
        *(s16 *)(temp_v0 + 0x30) = arg4;
    }
}

#ifdef NON_MATCHING
/* was func_15178C9C */
s32 swarm_distance_to_obj(s32 arg0, s32 arg1) {
    s32 temp_f10;
    s32 temp_f16;
    s32 temp_f8;
    struct127 *temp_a2;
    u8 *temp_v0;

    temp_v0 = swarm_find_by_id(arg0 & 0xFF);
    if (temp_v0 != NULL) {
        temp_a2 = &D_800CC2D0[arg1];
        temp_f16 = (s32) (temp_a2->x_position - (f32) (*(s32 *)((u8 *)temp_v0 + 0x18)));
        temp_f10 = (s32) (temp_a2->y_position - (f32) (*(s32 *)((u8 *)temp_v0 + 0x1C)));
        temp_f8 = (s32) (temp_a2->z_position - (f32) (*(s32 *)((u8 *)temp_v0 + 0x20)));
        return (s32) sqrtf((f32) ((temp_f16 * temp_f16) + (temp_f10 * temp_f10) + (temp_f8 * temp_f8)));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/swarm_distance_to_obj.s")
#endif
extern s32 D_800DD36C;
/* was func_15179314 */
s32 swarm_destroy(u8 *arg0) {
    u8 *next; // fakematch: declared before p to move the spill slot to 0x20
    u8 *p = (u8 *)D_800DD36C;

    sound_voice_stop(*(u16 *)(arg0 + 0x2E));
    while (p != NULL) {
        next = *(u8 **)(p + 8);
        if (*(u8 **)(p + 0x14) == arg0) {
            node_destroy(p);
        }
        p = next;
    }
    node_unlink_free(arg0);
}

s32 swarm_destroy(u8 *);
/* was func_15178E14 */
void swarm_destroy_by_id(u8 arg0)
{
    swarm_destroy(swarm_find_by_id(arg0));
}
