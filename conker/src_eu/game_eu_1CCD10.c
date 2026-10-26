#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
s32 foot_trail_get_foot_pos(u8 *arg0, u8 arg1, u8 *arg2);


extern f32 g_foot_trail_k_90c0; /* was D_800A90C0 */
extern f32 g_foot_trail_k_90c4; /* was D_800A90C4 */
/* was func_1519F500 */
s32 foot_trail_get_foot_pos(u8 *arg0, u8 arg1, u8 *arg2) {
    u8 *temp_v0;
    u8 temp_v0_2;
    struct127 *var_a3;
    f32 var_f18;
    f32 var_f16;
    f32 var_f0;
    f32 temp_f2_2;
    f32 temp_f2;
    f32 temp_f14;
    f32 temp_f12;
    u8 sp1F;
    f32 sp28;
    f32 sp2C;
    u8 *sp38;
    struct127 *sp3C;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0));
    sp38 = temp_v0 + 0x58;
    var_a3 = (*(struct127 **)((u8 *)temp_v0 + 0x18));
    if (var_a3->unk1D4 == NULL) {
        return 0;
    }
    var_f16 = var_a3->x_position;
    temp_f12 = var_f16 - (*(f32 *)((u8 *)arg0 + 0x20));
    temp_f14 = var_a3->z_position - (*(f32 *)((u8 *)arg0 + 0x24));
    if ((fabsf(temp_f12) > g_foot_trail_k_90c0) || (fabsf(temp_f14) > g_foot_trail_k_90c0)) {
        temp_f2 = 1.0f / sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14));
        var_f18 = temp_f14 * temp_f2;
        sp28 = temp_f12 * temp_f2;
    } else {
        sp3C = var_a3;
        temp_v0_2 = obj_get_yaw_byte(var_a3);
        sp1F = temp_v0_2;
        sp2C = angle_byte_cos(temp_v0_2 & 0xFF);
        var_a3 = sp3C;
        var_f18 = sp2C;
        sp28 = angle_byte_cos((sp1F - 0x40) & 0xFF);
        var_f16 = var_a3->x_position;
    }
    if (arg1 == 6) {
        var_f0 = (*(f32 *)((u8 *)sp38 + 0x10));
    } else {
        var_f0 = -(*(f32 *)((u8 *)sp38 + 0x10));
    }
    (*(f32 *)((u8 *)arg2 + 0)) = (f32) (var_f16 + (var_f0 * var_f18));
    (*(f32 *)((u8 *)arg2 + 8)) = (f32) (var_a3->z_position - (var_f0 * sp28));
    temp_f2_2 = var_a3->unk118;
    if (temp_f2_2 < g_foot_trail_k_90c4) {
        (*(f32 *)((u8 *)arg2 + 4)) = (f32) var_a3->y_position;
        return 1;
    }
    (*(f32 *)((u8 *)arg2 + 4)) = temp_f2_2;
    return 1;
}
/* was func_1519F678 */
void foot_trail_free(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    fxrec_die_retire(arg0);
}

/* was func_1519F6D8 */
void foot_trail_free_alt(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    fxrec_die_free(arg0);
}

u8 impact_current_kind(void);
s32 memcpy(s32, u8 **, s32);
extern s32 g_impact_kind_colours; /* was D_800AB7F4 */

/* was func_1519F738 */
s32 foot_trail_spawn(u8 *arg0, u8 arg1) {
    struct {
        u8 * u48;
        s8 u4C;
        u8 pad4D[0x3];
        f32 u50;
        f32 u54;
        s32 u58;
        u8 pad5C[0x8];
        f32 u64;
        f32 u68;
        f32 u6C;
        s16 u70;
        u8 u72;
        u8 u73;
        u8 u74;
        u8 pad75[0x1];
        s16 u76;
        s16 u78;
        s16 u7A;
        s16 u7C;
        u8 pad7E[0x2];
        f32 u80;
        f32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s16 u8E;
        s16 u90;
        s16 u92;
        f32 u94;
        s32 u98;
        u8 pad9C[0x8];
        s16 uA4;
        u16 uA6;
        s32 uA8;
        u8 padAC[0x1];
        s8 uAD;
        u8 padAE[0x6];
        u8 * uB4;
    } sp;
    u8 *sp44;
    u8 sp43;
    u8 temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v1;
    u8 *var_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    sp.uB4 = temp_v1;
    temp_v0 = impact_current_kind();
    sp.uA6 = 0x42;
    sp.uA4 = 0x12C;
    sp.uAD = 0xA;
    sp.u76 = 0xC8;
    sp.u88 = 3;
    sp.u48 = arg0;
    sp43 = temp_v0;
    sp.u4C = 6;
    sp.u89 = 0x55;
    sp.u8A = 3;
    sp.u8B = 0x55;
    sp.u8C = 0x88;
    sp.u8D = 0xC4;
    sp.u70 = 0;
    sp.u8E = 0;
    sp.u78 = 0xFF;
    sp.u7A = 0x28;
    sp.u7C = 0x19;
    sp.u90 = 6;
    sp.u92 = 0x325;
    sp.u50 = 0.015000001f;
    sp.u80 = 5.8f;
    sp.u84 = 1.0f;
    sp.u54 = 0.0f;
    sp.u64 = 0.0f;
    sp.uA8 = (s32) arg1;
    sp.u94 = 1.5f;
    sp.u68 = (*(f32 *)((u8 *)temp_v1 + 0x14));
    sp.u6C = (*(f32 *)((u8 *)temp_v1 + 0x1C));
    if (foot_trail_get_foot_pos(&sp.u48, arg1 & 0xFF, &sp.u98) != 0) {
        (*(s32 *)((u8 *)(&sp.u58) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u98) + 0));
        (*(s32 *)((u8 *)(&sp.u58) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u98) + 4));
        (*(s32 *)((u8 *)(&sp.u58) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u98) + 8));
        sp.uA6 |= 4;
    }
    temp_v0_2 = (u8 *) &g_impact_kind_colours + sp43 * 3;
    sp.u72 = (*(u8 *)((u8 *)temp_v0_2 + 0));
    sp.u73 = (*(u8 *)((u8 *)temp_v0_2 + 1));
    sp.u74 = (*(u8 *)((u8 *)temp_v0_2 + 2));
    temp_v0_3 = fxrec_spawn(&sp.u98, 0x50, 0x24, 5, 5, 5, 0, 0, (s32) (arg0 + 0x34), 0xFFU, 1);
    var_v1 = temp_v0_3;
    if (temp_v0_3 != NULL) {
        sp44 = temp_v0_3;
        memcpy((*(s32 *)((u8 *)temp_v0_3 + 0x98)), &sp.u48, 0x50);
        var_v1 = sp44;
    }
    return (s32) var_v1;
}
s32 foot_trail_spawn(u8 *, u8);
/* was func_1519F928 */
void foot_trails_start(u8 *arg0) {
    s32 *p = (s32 *)(arg0 + 0x58);
    p[0] = foot_trail_spawn(arg0, 6);
    p[1] = 0;
    p[2] = foot_trail_spawn(arg0, 7);
    p[3] = 0;
}

void foot_trail_marker_clear(u8 *);
void foot_trail_stop(u8 *);

/* was func_1519F970 */
void foot_trails_stop(u8 *arg0) {
    u8 *v = arg0 + 0x58;

    if (*(s32 *)(arg0 + 0x58) != 0) {
        foot_trail_stop(*(u8 **)(arg0 + 0x58));
    }
    if (*(u8 **)(v + 8) != NULL) {
        foot_trail_stop(*(u8 **)(v + 8));
    }
    if (*(u8 **)(v + 4) != NULL) {
        foot_trail_marker_clear(*(u8 **)(v + 4));
        node_destroy(*(struct102 **)(v + 4));
    }
    if (*(u8 **)(v + 0xC) != NULL) {
        foot_trail_marker_clear(*(u8 **)(v + 0xC));
        node_destroy(*(struct102 **)(v + 0xC));
    }
}

/* was func_1519F9FC */
void foot_trail_stop(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_a1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 + 0x58;
        if ((*(s32 *)((u8 *)arg0 + 0x20)) == 6) {
            (*(s32 *)((u8 *)temp_a1 + 0)) = 0;
        }
        if ((*(s32 *)((u8 *)arg0 + 0x20)) == 7) {
            (*(s32 *)((u8 *)temp_a1 + 8)) = 0;
        }
        (*(s32 *)((u8 *)temp_v0 + 0)) = 0;
    }
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) & 0xFFFD);
    (*(u8 *)((u8 *)temp_v0 + 4)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 4)) | 1);
}
extern f32 g_foot_trail_k_90d0; /* was D_800A90D0 */
s32 collision_floor_dynamic_b_full(f32 *, s32, f32, u8 *);

/* was func_1519FA60 */
s32 foot_trail_update_points(u8 *arg0) {
    struct {
        f32 u58;
        f32 u5C;
        f32 u60;
    } sp;
    f32 temp_f0;
    s16 temp_v0;
    s32 temp_fp;
    s32 var_s3;
    s8 var_s2;
    u8 *temp_s1;
    u8 *temp_s6;
    u8 *temp_v0_2;

    temp_s6 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_fp = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_s6 + 4)) & 1)) {
        return 0;
    }
    var_s2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_s2 -= 1;
            var_s3 = 0;
            if (var_s2 < 0) {
                var_s2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_s1 = (var_s2 * 0x24) + temp_fp;
            (*(s16 *)((u8 *)temp_s1 + 0x18)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 0x18)) - g_frame_ticks);
            if ((*(s16 *)((u8 *)temp_s1 + 0x18)) < 0) {
                var_s3 = 1;
            }
            temp_v0 = (*(s16 *)((u8 *)temp_s1 + 0x12));
            (*(s16 *)((u8 *)temp_s1 + 0x14)) = 0xFF;
            if (temp_v0 > 0) {
                (*(s16 *)((u8 *)temp_s1 + 0x12)) = (s16) (temp_v0 - g_frame_ticks);
            } else {
                (*(s16 *)((u8 *)temp_s1 + 0x10)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 0x10)) - ((*(s16 *)((u8 *)temp_s6 + 0x34)) * g_frame_ticks));
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((*(f32 *)((u8 *)temp_s6 + 0x3C)) * g_frame_step_f));
            (*(f32 *)((u8 *)temp_s1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0)) + ((*(f32 *)((u8 *)temp_s1 + 0x1C)) * g_frame_step_f));
            (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) + ((*(f32 *)((u8 *)temp_s1 + 0x20)) * g_frame_step_f));
            sp.u58 = (*(f32 *)((u8 *)temp_s1 + 0));
            temp_f0 = fabsf(sp.u58);
            sp.u5C = (*(f32 *)((u8 *)temp_s1 + 8)) + 30.0f;
            sp.u60 = (*(f32 *)((u8 *)temp_s1 + 4));
            if ((temp_f0 > g_foot_trail_k_90d0) || (fabsf(sp.u60) > g_foot_trail_k_90d0)) {
                goto block_17;
            }
            if (collision_floor_dynamic_b_full(&sp.u58, 0, (*(f32 *)((u8 *)temp_s1 + 8)) - 30.0f, arg0 + 0x60) != 0) {
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x60));
            } else {
block_17:
                var_s3 = 1;
            }
            if ((*(s16 *)((u8 *)temp_s1 + 0x10)) < 0) {
                var_s3 = 1;
            }
            if (var_s3 != 0) {
                if (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
                (*(s16 *)((u8 *)((temp_fp + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24))) + 0x10)) = 0;
            }
        } while (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    (*(s16 *)((u8 *)temp_s6 + 0x46)) = (s16) ((*(s16 *)((u8 *)temp_s6 + 0x46)) + ((*(s16 *)((u8 *)temp_s6 + 0x48)) * g_frame_ticks));
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_v0_2 = temp_fp + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0));
        (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 8));
        (*(f32 *)((u8 *)arg0 + 0x5C)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 4));
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}
/* P191 */
s32 random_int(void); /* also in functions.h: declared again so difftest knows its arity (the asm leaves rec + 0x10 in a1) */
/* footprint trail point (0x24 bytes, ring of t[0x25] points at t +0x94; head t +0x2E, tail +0x2D, count +0x2C) */
typedef struct {
    f32 x;        /* 0x00 */
    f32 z;        /* 0x04 */
    f32 y;        /* 0x08: ground height under the point */
    f32 width;    /* 0x0C */
    s16 alpha;    /* 0x10 */
    s16 hold;     /* 0x12 */
    s16 u14;      /* 0x14: 0xFF */
    s16 u16;      /* 0x16: texture phase (rec +0x28) */
    s16 life;     /* 0x18 */
    s16 pad1A;
    f32 vx;       /* 0x1C: drift (sideways) */
    f32 vz;       /* 0x20 */
} TrailPointFD60;

// foot_trail_update: P191: per-frame update of a foot trail effect t (side t +0x20: 6 = left, 7 = right) of the
// player owning the trail record rec (t +0x98; rec +0 = the owner object, whose +0x18 is the player): returns 0
// when the player is gone (no state / model) or the owner id no longer matches. The first frame takes the foot
// position (foot_trail_get_foot_pos into t +0x10) as the record's last point; later frames re-take it (when that fails the
// trail is ended, foot_trail_stop, and a new trail effect effect_node_create_nodraw(300, -1, 11, 0, 6, 8, 0xFF, 0) is started for
// the side). The distance moved times rec +0x8 accumulates in rec +0xC; while it is above 1 a point is laid every
// unit: position interpolated from the last point, width rec +0x38 + rec +0x3C * phase, alpha / hold / life /
// phase from the record (rec +0x28 advances by +0x44 + random [0, +0x45]), a sideways drift (the move direction
// turned left or right, times rec +0x4C), moved by drift * phase and dropped onto the ground (collision_floor_dynamic_b_full from
// 100 above the water surface, or above the player when there is no surface; points beyond +-20000 or without
// ground are not added). The point before the newest one gets the average of its drift and the new one. Returns 1.
// Rare reads the unit direction uninitialised when the foot did not move (asm: stack garbage); here it is 0.
/* was func_1519FD60 */
s32 foot_trail_update(u8 *t) {
    u8 *rec = *(u8 **) (t + 0x98);
    TrailPointFD60 *pts = *(TrailPointFD60 **) (t + 0x94);
    u8 *owner = *(u8 **) rec;
    struct127 *pl = *(struct127 **) (owner + 0x18);
    TrailPointFD60 *q;
    struct {
        u8 *owner;
        u8 side;
    } key;
    u8 *slots;
    u8 *e;
    s32 started;
    f32 d0, d1, d2;
    f32 len;
    f32 inv = 0.0f;
    f32 n;
    f32 phase, phaseStep;
    f32 pos[3];
    f32 probe[3];
    f32 drift[2];
    f32 w, wStep;
    f32 step0, step1, step2;
    s32 h, k;
    s32 ok;
    s32 r;

    if (pl->interaction_state == 0) {
        return 0;
    }
    if (pl->unk1D4 == NULL) {
        return 0;
    }
    if (owner[0x1C] != pl->unique_id) {
        return 0;
    }
    started = 0;
    if (!(*(u16 *) (t + 0x1E) & 4)) {
        if (foot_trail_get_foot_pos(rec, t[0x23], t + 0x10) == 0) {
            return 1;
        }
        started = 1;
        *(f32 *) (rec + 0x10) = *(f32 *) (t + 0x10);
        *(f32 *) (rec + 0x14) = *(f32 *) (t + 0x14);
        *(f32 *) (rec + 0x18) = *(f32 *) (t + 0x18);
        *(u16 *) (t + 0x1E) |= 4;
    }
    if (!started && foot_trail_get_foot_pos(rec, t[0x23], t + 0x10) == 0) {
        foot_trail_stop(t);
        key.owner = *(u8 **) rec;
        key.side = *(s32 *) (t + 0x20);
        slots = key.owner + 0x58;
        e = (u8 *) effect_node_create_nodraw(300, -1, 11, 0, 6, 8, 0xFF, 0);
        if (e != NULL) {
            memcpy((s32) (e + 0x28), (u8 **) &key, 8);
        }
        if (*(s32 *) (t + 0x20) == 6) {
            *(u8 **) (slots + 4) = e;
        } else {
            *(u8 **) (slots + 0xC) = e;
        }
        return 1;
    }

    *(f32 *) (rec + 0x20) = pl->x_position;
    *(f32 *) (rec + 0x24) = pl->z_position;
    d0 = *(f32 *) (t + 0x10) - *(f32 *) (rec + 0x10);
    d1 = *(f32 *) (t + 0x14) - *(f32 *) (rec + 0x14);
    d2 = *(f32 *) (t + 0x18) - *(f32 *) (rec + 0x18);
    if (fabsf(d0) > 0.0001f || fabsf(d1) > 0.0001f || fabsf(d2) > 0.0001f) {
        len = sqrtf(d0 * d0 + d1 * d1 + d2 * d2);
        inv = 1.0f / len;
        *(f32 *) (rec + 0xC) = *(f32 *) (rec + 0xC) + len * *(f32 *) (rec + 0x8);
    }
    if (!(1.0f < *(f32 *) (rec + 0xC))) {
        return 1;
    }
    n = 1.0f / *(f32 *) (rec + 0xC);
    phase = *(f32 *) (rec + 0x1C) + g_frame_step_f;
    phaseStep = phase * n;
    pos[0] = *(f32 *) (rec + 0x10);
    pos[1] = *(f32 *) (rec + 0x14);
    pos[2] = *(f32 *) (rec + 0x18);
    w = *(f32 *) (rec + 0x38) + *(f32 *) (rec + 0x3C) * phase;
    wStep = *(f32 *) (rec + 0x38) - w;
    if (*(s32 *) (t + 0x20) == 7) {
        drift[0] = -d2 * inv * *(f32 *) (rec + 0x4C);
        drift[1] = d0 * inv * *(f32 *) (rec + 0x4C);
    } else {
        drift[0] = d2 * inv * *(f32 *) (rec + 0x4C);
        drift[1] = -d0 * inv * *(f32 *) (rec + 0x4C);
    }
    h = *(s8 *) (t + 0x2E) - 1;
    if (h < 0) {
        h = t[0x25] - 1;
    }
    if (h != *(s8 *) (t + 0x2D) && *(s8 *) (t + 0x2C) != 0) {
        k = h - 1;
        if (k < 0) {
            k = t[0x25] - 1;
        }
        pts[k].vx = (pts[k].vx + drift[0]) * 0.5f;
        pts[k].vz = (pts[k].vz + drift[1]) * 0.5f;
    }
    step0 = d0 * n;
    step1 = d1 * n;
    step2 = d2 * n;
    wStep = wStep * n;
    do {
        q = &pts[*(s8 *) (t + 0x2E)];
        q->vx = drift[0];
        q->vz = drift[1];
        q->x = pos[0];
        q->z = pos[2];
        q->life = *(s16 *) (rec + 0x2E);
        q->width = w;
        q->alpha = *(s16 *) (rec + 0x30);
        q->u14 = 0xFF;
        q->hold = *(s16 *) (rec + 0x32);
        q->u16 = *(s16 *) (rec + 0x28);
        r = random_int();
        *(s16 *) (rec + 0x28) = *(s16 *) (rec + 0x28) + rec[0x44] + (u32) r % (u32) (rec[0x45] + 1);
        q->x = q->x + q->vx * phase;
        q->z = q->z + q->vz * phase;
        probe[0] = q->x;
        if (pl->unk118 < -9500.0f) {
            probe[1] = pl->y_position + 100.0f;
        } else {
            probe[1] = pl->unk118 + 100.0f;
        }
        probe[2] = q->z;
        ok = 1;
        if (fabsf(probe[0]) > 20000.0f || fabsf(probe[2]) > 20000.0f) {
            ok = 0;
        } else if (collision_floor_dynamic_b_full(probe, 0, probe[1] - 200.0f, t + 0x60) != 0) {
            q->y = *(f32 *) (t + 0x60);
        } else {
            ok = 0;
        }
        if (ok) {
            *(s8 *) (t + 0x2E) += 1;
            if (t[0x25] == *(s8 *) (t + 0x2E)) {
                *(s8 *) (t + 0x2E) = 0;
            }
            *(s8 *) (t + 0x2C) += 1;
            if (*(s8 *) (t + 0x2D) == *(s8 *) (t + 0x2E)) {
                /* ring full: drop the oldest point */
                *(s8 *) (t + 0x2D) += 1;
                if (t[0x25] == *(s8 *) (t + 0x2D)) {
                    *(s8 *) (t + 0x2D) = 0;
                }
                *(s8 *) (t + 0x2C) -= 1;
            }
        }
        pos[0] += step0;
        pos[1] += step1;
        pos[2] += step2;
        w += wStep;
        phase -= phaseStep;
        *(f32 *) (rec + 0xC) = *(f32 *) (rec + 0xC) - 1.0f;
    } while (1.0f < *(f32 *) (rec + 0xC));
    *(f32 *) (rec + 0x10) = pos[0];
    *(f32 *) (rec + 0x14) = pos[1];
    *(f32 *) (rec + 0x18) = pos[2];
    *(f32 *) (rec + 0x1C) = phase;
    return 1;
}

/* P204 */
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 gfx_load_texture_cached(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *gfx_geometry_mode_cached(Gfx *, s32, s32);
Gfx *gfx_env_color_cached(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *gfx_prim_color_cached(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *gfx_set_combine_mode(Gfx *, u8, u8 *);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);
extern u8 g_foot_trail_tex[]; /* was D_800911BC */
extern s32 g_gfx_tlut_mode; /* was D_800D30BC */
/* trail point (0x24 bytes): the same layout as port-b's TrailPointFD60 (foot_trail_update writes them) */
typedef struct {
    f32 x;        /* 0x00 */
    f32 z;        /* 0x04 */
    f32 y;        /* 0x08 */
    f32 width;    /* 0x0C */
    s16 alpha;    /* 0x10 */
    s16 hold;     /* 0x12 */
    s16 fade;     /* 0x14: alpha scale, 0xFF = full */
    s16 texU;     /* 0x16 */
    s16 life;     /* 0x18 */
    s16 pad1A;
    f32 vx;       /* 0x1C */
    f32 vz;       /* 0x20 */
} TrailPoint03DC;

// foot_trail_draw: g_fxrec_draw_fns draw handler (kind 5) of a foot trail / water ripple effect t (ring of t[0x25] points
// at t +0x94, tail t +0x2D, head t +0x2E, count t +0x2C; record rec = t +0x98). Returns gfx unchanged when there are
// fewer than 2 points or no vertex buffer (vtx_slot_buffer_get slot `slot` in t +0x84, 0x30 bytes per point + 0x120).
// Otherwise: rec flag 2 sets the points' fade (+0x14) from the tail on, 0, +rec[0x41], ... for rec[0x40] points;
// rec flag 4 scales the fade from the head back by 0, rec[0x43], ... / 256 for rec[0x42] points. Then the render
// state (texture g_foot_trail_tex, colour rec +0x2A..0x2C, combine) and a strip from the newest point back to the tail:
// three vertices per point (left edge, centre, right edge across the trail direction, half width = point width;
// edges alpha 0, centre alpha = alpha * fade / 256, texture v from rec +0x46 (wrapped to +-1024 when +0x46 + +0x4A
// overflows) / middle / +0x46 + +0x4A, mirrored for the right foot (t +0x20 != 6)), four triangles per segment.
// With t +0x1E bit 2 the strip starts at the live foot position t +0x10 (width rec +0x38) instead of the newest point.
/* was func_151A03DC */
s32 foot_trail_draw(u8 *t, s32 gfxArg, s16 slot) {
    Gfx *gfx = (Gfx *) gfxArg;
    u8 *rec;
    TrailPoint03DC *pts;
    TrailPoint03DC *p;
    TrailPoint03DC *q;
    Vtx *vtx;
    u8 flag;
    s16 tv[3];
    f32 cur[3];
    f32 nxt[3];
    f32 width;
    f32 qWidth;
    f32 dx;
    f32 dz;
    f32 inv;
    f32 ox;
    f32 oz;
    s32 i;
    s32 prev;
    s32 n;
    u8 step;
    s32 alpha;
    s32 qAlpha;
    s16 u;
    s16 qU;
    s32 l;
    s32 r;

    if (*(s8 *) (t + 0x2C) < 2) {
        return (s32) gfx;
    }
    vtx_slot_buffer_get((s32 *) (t + 0x84), slot, t[0x25] * 0x30 + 0x120, (s32 *) &vtx, NULL);
    if (vtx == NULL) {
        return (s32) gfx;
    }
    rec = *(u8 **) (t + 0x98);
    pts = *(TrailPoint03DC **) (t + 0x94);
    flag = 1;

    if (rec[4] & 2) {
        /* fade in from the tail */
        n = (s16) rec[0x40];
        i = *(s8 *) (t + 0x2D);
        step = 0;
        do {
            pts[i].fade = step;
            i++;
            n = (s16) (n - 1);
            step += rec[0x41];
            if (i == t[0x25]) {
                i = 0;
            }
            if (n == 0) {
                break;
            }
        } while (i != *(s8 *) (t + 0x2E));
    }
    if (rec[4] & 4) {
        /* fade out towards the head */
        i = *(s8 *) (t + 0x2E) - 1;
        n = (s16) rec[0x42];
        step = 0;
        if (i < 0) {
            i = t[0x25] - 1;
        }
        do {
            p = &pts[i];
            n = (s16) (n - 1);
            i--;
            p->fade = (p->fade * step) >> 8;
            step += rec[0x43];
            if (i < 0) {
                i = t[0x25] - 1;
            }
            if (n == 0) {
                break;
            }
        } while (i != *(s8 *) (t + 0x2E));
    }

    gfx = (Gfx *) gfx_load_texture_cached((s32) gfx, (s32) g_foot_trail_tex, 0, 0, 0, 0, 0x39, 0, 0, &flag, 0x3E);
    gfx = gfx_geometry_mode_cached(gfx, 1, 0x160600);
    gfx = gfx_env_color_cached(gfx, rec[0x2A], rec[0x2B], rec[0x2C], 0xFF, &flag);
    gfx = gfx_prim_color_cached(gfx, 0, 0, 0xFF, 0xFF, 0xFF, 0, &flag);
    gfx = gfx_set_combine_mode(gfx, 7, &flag);
    gfx = gfx_other_mode_cached(gfx, g_gfx_tlut_mode | 0x80000 | 0x2CA0, 0x5049D8, &flag);

    /* first cross-section: the live foot position or the newest point; q = the next point towards the tail */
    if (*(u16 *) (t + 0x1E) & 2) {
        prev = *(s8 *) (t + 0x2E) - 1;
        if (prev < 0) {
            prev = t[0x25] - 1;
        }
        cur[0] = *(f32 *) (t + 0x10);
        cur[1] = *(f32 *) (t + 0x14);
        cur[2] = *(f32 *) (t + 0x18);
        q = &pts[prev];
        alpha = (q->alpha * q->fade) >> 8;
        width = *(f32 *) (rec + 0x38);
        u = q->texU;
    } else {
        i = *(s8 *) (t + 0x2E) - 1;
        if (i < 0) {
            i = t[0x25] - 1;
        }
        prev = i - 1;
        if (prev < 0) {
            prev = t[0x25] - 1;
        }
        p = &pts[i];
        cur[0] = p->x;
        cur[1] = p->y;
        cur[2] = p->z;
        q = &pts[prev];
        alpha = (p->alpha * p->fade) >> 8;
        width = p->width;
        u = p->texU;
    }
    nxt[0] = q->x;
    nxt[1] = q->y;
    nxt[2] = q->z;
    dx = nxt[0] - cur[0];
    dz = nxt[2] - cur[2];
    qAlpha = (q->alpha * q->fade) >> 8;
    qU = q->texU;
    qWidth = q->width;
    if (fabsf(dx) > 0.0001f || fabsf(dz) > 0.0001f) {
        inv = 1.0f / sqrtf(dx * dx + dz * dz);
    } else {
        inv = 1.0f;
    }

    /* texture v across the trail */
    tv[0] = *(s16 *) (rec + 0x46);
    tv[2] = *(s16 *) (rec + 0x46) + *(s16 *) (rec + 0x4A);
    if (tv[2] < tv[0]) {
        tv[0] = tv[0] % 1024;
        *(s16 *) (rec + 0x46) = tv[0];
        tv[2] = *(s16 *) (rec + 0x46) + *(s16 *) (rec + 0x4A);
    }
    tv[1] = (tv[2] + tv[0]) >> 1;
    if (*(s32 *) (t + 0x20) == 6) {
        l = 0;
        r = 2;
    } else {
        l = 2;
        r = 0;
    }

    ox = -dz * inv * width;
    oz = dx * inv * width;
    vtx->v.ob[0] = (s32) (cur[0] + ox);
    vtx->v.ob[1] = (s32) cur[1];
    vtx->v.ob[2] = (s32) (cur[2] + oz);
    vtx->v.tc[0] = u;
    vtx->v.tc[1] = tv[l];
    vtx->v.cn[0] = 0xFF;
    vtx->v.cn[1] = 0xFF;
    vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = 0;
    vtx->v.flag = 0;
    vtx++;
    vtx->v.ob[0] = (s32) cur[0];
    vtx->v.ob[1] = (s32) cur[1];
    vtx->v.ob[2] = (s32) cur[2];
    vtx->v.tc[0] = u;
    vtx->v.tc[1] = tv[1];
    vtx->v.cn[0] = 0xFF;
    vtx->v.cn[1] = 0xFF;
    vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = alpha;
    vtx->v.flag = 0;
    vtx++;
    vtx->v.ob[0] = (s32) (cur[0] - ox);
    vtx->v.ob[1] = (s32) cur[1];
    vtx->v.ob[2] = (s32) (cur[2] - oz);
    vtx->v.tc[0] = u;
    vtx->v.tc[1] = tv[r];
    vtx->v.cn[0] = 0xFF;
    vtx->v.cn[1] = 0xFF;
    vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = 0;
    vtx->v.flag = 0;
    vtx++;

    /* one cross-section per older point, joined to the previous one by four triangles */
    for (;;) {
        ox = -dz * inv * qWidth;
        oz = dx * inv * qWidth;
        vtx->v.ob[0] = (s32) (nxt[0] + ox);
        vtx->v.ob[1] = (s32) nxt[1];
        vtx->v.ob[2] = (s32) (nxt[2] + oz);
        vtx->v.tc[0] = qU;
        vtx->v.tc[1] = tv[l];
        vtx->v.cn[0] = 0xFF;
        vtx->v.cn[1] = 0xFF;
        vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = 0;
        vtx->v.flag = 0;
        vtx++;
        vtx->v.ob[0] = (s32) nxt[0];
        vtx->v.ob[1] = (s32) nxt[1];
        vtx->v.ob[2] = (s32) nxt[2];
        vtx->v.tc[0] = qU;
        vtx->v.tc[1] = tv[1];
        vtx->v.cn[0] = 0xFF;
        vtx->v.cn[1] = 0xFF;
        vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = qAlpha;
        vtx->v.flag = 0;
        vtx++;
        vtx->v.ob[0] = (s32) (nxt[0] - ox);
        vtx->v.ob[1] = (s32) nxt[1];
        vtx->v.ob[2] = (s32) (nxt[2] - oz);
        vtx->v.tc[0] = qU;
        vtx->v.tc[1] = tv[r];
        vtx->v.cn[0] = 0xFF;
        vtx->v.cn[1] = 0xFF;
        vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = 0;
        vtx->v.flag = 0;
        vtx++;
        gSPVertex(gfx++, vtx - 6, 6, 0);
        gSP1Triangle(gfx++, 0, 3, 4, 0);
        gSP1Triangle(gfx++, 0, 4, 1, 0);
        gSP1Triangle(gfx++, 1, 4, 5, 0);
        gSP1Triangle(gfx++, 1, 5, 2, 0);

        i = prev;
        prev--;
        if (prev < 0) {
            prev = t[0x25] - 1;
        }
        if (i == *(s8 *) (t + 0x2D)) {
            break;
        }
        cur[0] = nxt[0];
        cur[1] = nxt[1];
        cur[2] = nxt[2];
        q = &pts[prev];
        nxt[0] = q->x;
        nxt[1] = q->y;
        nxt[2] = q->z;
        qAlpha = (q->alpha * q->fade) >> 8;
        qU = q->texU;
        dx = nxt[0] - cur[0];
        dz = nxt[2] - cur[2];
        if (nxt[0] == cur[0] && dz == 0.0f) {
            inv = 1.0f;
        } else {
            inv = 1.0f / sqrtf(dx * dx + dz * dz);
        }
        qWidth = q->width;
    }
    return (s32) gfx;
}

/* was func_151A0DBC */
void foot_trail_marker_update(u8 *arg0) {
    u8 *sp28;
    u8 sp23;
    u8 *sp18;
    s32 temp_v0_2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_a2;
    u8 *temp_t0;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x28));
    var_v1 = 0;
    temp_a2 = arg0 + 0x28;
    temp_a1 = (*(u8 **)((u8 *)temp_v0 + 0x18));
    temp_t0 = temp_v0 + 0x58;
    if ((*(s32 *)((u8 *)temp_a1 + 0)) == 0) {
        var_v1 = 1;
    }
    temp_a0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if ((*(u8 *)((u8 *)temp_a0 + 0x1C)) != (*(u8 *)((u8 *)temp_a1 + 0x3B))) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && ((*(s32 *)((u8 *)temp_a1 + 0x1D4)) != 0)) {
        sp23 = 1;
        sp28 = temp_t0;
        sp18 = temp_a2;
        temp_v0_2 = foot_trail_spawn(temp_a0, (*(u8 *)((u8 *)temp_a2 + 4)));
        var_v1 = 1;
        if ((*(u8 *)((u8 *)temp_a2 + 4)) == 6) {
            (*(s32 *)((u8 *)temp_t0 + 0)) = temp_v0_2;
        } else {
            (*(s32 *)((u8 *)temp_t0 + 8)) = temp_v0_2;
        }
    }
    if (var_v1 != 0) {
        foot_trail_marker_clear(arg0);
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
    }
}
/* was func_151A0E98 */
void foot_trail_marker_clear(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x28) + 0x58;
    if (arg0[0x2C] == 6) {
        *(s32 *)(p + 4) = 0;
    } else {
        *(s32 *)(p + 0xC) = 0;
    }
}

/* was func_151A0EC0 */
void foot_trail_handle_msg(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_t6;
    unsigned int new_var; // fakematch: field temp pins t7/v1 register choice
    unsigned int new_var2; // fakematch: same for the second branch
    u8 **temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_t6 = arg2;
    temp_v1 = *(u8 ***)(arg0 + 0x98);
    if (temp_t6 == 0xA) {
        temp_v0 = *temp_v1;
        if ((temp_v0 != NULL) && (((new_var = *(s32 *)(temp_v0 + 0x18)) == *(s32 *)(arg1 + 0)) || (*(u8 *)(temp_v0 + 0x1C) == *(u8 *)(arg1 + 4)))) {
            foot_trail_stop(arg0);
        }
    } else if (temp_t6 == 0) {
        temp_v0_2 = *temp_v1;
        if ((temp_v0_2 != NULL) && ((new_var2 = *(s32 *)(temp_v0_2 + 0x18)) == *(s32 *)(arg1 + 0))) {
            foot_trail_stop(arg0);
        }
    }
}

/* was func_151A0F5C */
void foot_trail_marker_handle_msg(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)(*(u8 **)(arg0 + 0x28) + 0x18);
    if (arg2 == 0) {
        if (((s32)v == *(s32 *)arg1) || (v[0x3B] == arg1[4])) {
            foot_trail_marker_clear(arg0);
            node_destroy(arg0);
        }
    }
}
