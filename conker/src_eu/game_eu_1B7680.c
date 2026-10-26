#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#define F(o) (*(f32 *)(p + (o)))
/* was func_15189E70 */
void area_drift_emitter_create(void *arg0, u8 arg1) {
    u8 *p;
    s32 flag;

    p = node_alloc(0x1A, 1, 0x78, 1, 0xFF, 1);
    if (p != NULL) {
        memcpy(p + 0x10, arg0, 0x50);
        collision_select_area(0);
        *(s32 *)(p + 0x6C) = zone_tree_find_leaf((s32)(F(0x24) * 0.5f + F(0x18)), (s32)(F(0x2C) * 0.5f + F(0x20)));
        if (arg1 != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        p[0x70] = flag;
        *(s16 *)(p + 0x60) = 0;
        F(0x64) = 0.0f;
        if (F(0x28) < 0.0f) {
            F(0x68) = F(0x28) + F(0x1C);
        } else {
            F(0x68) = F(0x1C);
        }
    }
}
#undef F

s32 player_mask_hides_all(s32);
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern u8 D_800BEA50[];

/* particle spec passed to trail_spawn (argument 12), 0x5C bytes */
typedef struct {
    /* 0x00 */ s32 w00, w04, w08, w0C, w10, w14, w18;
    /* 0x1C */ u8 b1C, b1D;
    /* 0x1E */ u8 pad1E[2];
    /* 0x20 */ f32 floorY;          /* copied to the particle (+0x98 block + 0x48) */
    /* 0x24 */ f32 speed;           /* argument 2 points here */
    /* 0x28 */ f32 dir[3];
    /* 0x34 */ f32 f34;
    /* 0x38 */ f32 f38;
    /* 0x3C */ u8 b3C, b3D, b3E, b3F;
    /* 0x40 */ s16 h40, h42;
    /* 0x44 */ f32 pos[3];          /* argument 1 */
    /* 0x50 */ s16 h50, h52;
    /* 0x54 */ s32 w54;
    /* 0x58 */ u8 b58, b59;
    /* 0x5A */ u8 pad5A[2];
} DriftSpec;

/*
 * area_drift_emitter_update: P190. Per-frame update (D_8008B848 type 0x1A +0) of the emitter area_drift_emitter_create creates
 * (p + 0x10: the 0x50-byte area parameters: +0x18 / +0x1C / +0x20 corner, +0x24 / +0x28 / +0x2C size, +0x30 / +0x34
 * speed base / range, +0x38 / +0x3C rate base / range, +0x40 / +0x44, +0x48 / +0x4A, +0x4C / +0x50, +0x54 / +0x56,
 * +0x58 / +0x5C random bases / ranges, +0x10 / +0x12 yaw centre / spread, +0x14 / +0x16 pitch base / range).
 * Nothing while the trigger +0x6C is set and player_mask_hides_all says so. Every 50 frames (+0x60 countdown) it checks that
 * a player (D_800BEA50[0 .. D_80082FA0], records D_800DBFF0 0x9A0 bytes, position +0x2F8) is within 1581 units
 * (squared 2500000), else does nothing; then accumulates rate * D_800BE9A4 in +0x64 and spawns one particle per
 * whole unit above 1 (random point in the box, random direction from two byte angles, random sizes / colours).
 */
/* was func_15189F70 */
void area_drift_emitter_update(u8 *p) {
    DriftSpec spec;
    u8 *pl;
    u8 *part;
    s32 last, i, found;
    s16 yaw, pitch;
    f32 dx, dy, dz, f, speed, sinYaw, cosYaw, sinPitch, cosPitch, horiz;

    if (*(s32 *)(p + 0x6C) != 0 && player_mask_hides_all(*(s32 *)(p + 0x6C)) != 0) {
        return;
    }
    *(s16 *)(p + 0x60) -= D_800BE9E4;
    if (*(s16 *)(p + 0x60) < 0) {
        *(s16 *)(p + 0x60) += 50;
        last = D_80082FA0;
        found = FALSE;
        for (i = 0; i <= last && !found; i++) {
            pl = (u8 *)D_800DBFF0 + D_800BEA50[i] * 0x9A0 + 0x2F8;
            dx = *(f32 *)(pl + 0) - *(f32 *)(p + 0x18);
            dy = *(f32 *)(pl + 4) - *(f32 *)(p + 0x1C);
            dz = *(f32 *)(pl + 8) - *(f32 *)(p + 0x20);
            if (dx * dx + dy * dy + dz * dz < 2500000.0f) {
                found = TRUE;
            }
        }
        if (!found) {
            return;
        }
    }
    f = random_float();
    *(f32 *)(p + 0x64) += (*(f32 *)(p + 0x38) + f * *(f32 *)(p + 0x3C)) * D_800BE9A4;
    if (!(1.0f < *(f32 *)(p + 0x64))) {
        return;
    }
    spec.w00 = 0;
    spec.w04 = 1;
    spec.w08 = 0x160600;
    spec.w0C = 3;
    spec.w10 = 0x22;
    spec.w14 = 0x80;
    spec.w18 = 0x20;
    spec.b1C = 0;
    spec.b1D = 7;
    spec.floorY = *(f32 *)(p + 0x68);
    spec.f38 = -10000.0f;
    spec.b3C = 0x48;
    spec.b3D = 3;
    spec.b3E = 0xFF;
    spec.h40 = 0x10;
    spec.h42 = 0xF;
    spec.h52 = 5;
    spec.w54 = 1;
    do {
        spec.b59 = random_int() % (u32)(*(s32 *)(p + 0x5C) + 1) + *(s32 *)(p + 0x58);
        f = random_float();
        spec.pos[0] = *(f32 *)(p + 0x18) + f * *(f32 *)(p + 0x24);
        spec.pos[1] = *(f32 *)(p + 0x1C) + f * *(f32 *)(p + 0x28);
        spec.pos[2] = *(f32 *)(p + 0x20) + f * *(f32 *)(p + 0x2C);
        spec.speed = random_float() * *(f32 *)(p + 0x44) + *(f32 *)(p + 0x40);
        yaw = *(s16 *)(p + 0x10) - random_int() % (u32)(*(s16 *)(p + 0x12) * 2 + 1) + *(s16 *)(p + 0x12);
        pitch = random_int() % (u32)(*(s16 *)(p + 0x16) + 1) + *(s16 *)(p + 0x14);
        speed = random_float() * *(f32 *)(p + 0x34) + *(f32 *)(p + 0x30);
        sinYaw = angle_byte_cos(yaw);
        cosYaw = angle_byte_cos(yaw - 0x40);
        sinPitch = angle_byte_cos(pitch);
        cosPitch = angle_byte_cos(pitch - 0x40);
        horiz = speed * sinPitch;
        spec.dir[0] = horiz * cosYaw;
        spec.dir[1] = -speed * cosPitch;
        spec.dir[2] = horiz * sinYaw;
        spec.f34 = random_float() * *(f32 *)(p + 0x50) + *(f32 *)(p + 0x4C);
        spec.b3F = random_int() % (u32)(*(s16 *)(p + 0x4A) + 1) + *(s16 *)(p + 0x48);
        spec.h50 = random_int() % (u32)(*(s16 *)(p + 0x56) + 1) + *(s16 *)(p + 0x54);
        part = trail_spawn((u8 *)spec.pos, (s32)&spec.speed, 8, 1, (p[0x70] & 1) ? 10 : 0, 0, 0, 0, 0, 0, 0,
                             (u8 *)&spec, 0, p[0xC], p[1]);
        if (part != NULL) {
            memcpy(*(u8 **)(part + 0x98) + 0x48, &spec.floorY, 4);
        }
        *(f32 *)(p + 0x64) -= 1.0f;
    } while (1.0f < *(f32 *)(p + 0x64));
}

typedef struct { f32 x, y, z; s32 a, b; } Node14;
u8 impact_current_kind(void);
extern f64 D_800A7788;
extern f32 D_800A7790;

/* was func_1518A42C */
s32 drift_particle_hit_floor(u8 *arg0) {
    s32 pad[2];
    u8 *obj;
    u8 *tbl;
    f32 pos[3];

    tbl = *(u8 **)(arg0 + 0x94);
    obj = *(u8 **)(arg0 + 0x98);
    if (*(f32 *)(tbl + *(s8 *)(arg0 + 0x2D) * 0x14 + 4) < *(f32 *)(obj + 0x48)) {
        if (random_float() < D_800A7788) {
            pos[0] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
            pos[1] = *(f32 *)(obj + 0x48);
            pos[2] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
            impact_dust_particle_spawn(impact_current_kind(), *(f32 *)(obj + 0) * 6.0f, *(u8 *)(obj + 0x1B), 0, pos, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
        }
        *(s8 *)(obj + 0x20) = 4;
        *(f32 *)(obj + 0x48) = D_800A7790;
    }
    return 1;
}

/* was func_1518A540 */
s32 drift_particle_noop(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 1;
}
