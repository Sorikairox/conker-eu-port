#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);


f32 vec3_dot(u8 *, u8 *);
s32 tri_calc_normal(u8 *, u8 *, u8 *, u8 *);

/* was func_1514FBB0 */
void emit_disc_from_surface(u8 *arg0, u8 *arg1) {
    arg1[0] = 2;
    *(f32 *)(arg1 + 0x28) = *(f32 *)(arg0 + 0x20);
    if ((tri_calc_normal(arg0 + 0xC, arg1 + 0x10, arg1 + 0x1C, arg1 + 4) != 0) && (vec3_dot(arg1 + 4, arg0) < 0.0f)) {
        *(f32 *)(arg1 + 4) = -*(f32 *)(arg1 + 4);
        *(f32 *)(arg1 + 8) = -*(f32 *)(arg1 + 8);
        *(f32 *)(arg1 + 0xC) = -*(f32 *)(arg1 + 0xC);
    }
}

s32 vec3_normalize_len(u8 *, u8 *, void *, void *);
s32 vec3_make_basis(u8 *, s32 *, s32 *);
/* was func_1514FC58 */
s32 emit_disc_prepare(u8 *arg0) {
    s32 f;
    f = arg0[0];
    if (!(f & 1)) {
        if (vec3_normalize_len(arg0 + 4, arg0 + 4, 0, 0) == 0) {
            return 0;
        }
        *(f32 *)(arg0 + 4) *= 1000.0f;
        f = arg0[0] |= 1;
        *(f32 *)(arg0 + 8) *= 1000.0f;
        *(f32 *)(arg0 + 0xC) *= 1000.0f;
    }
    if (!(f & 2)) {
        if (vec3_make_basis(arg0 + 4, (s32 *)(arg0 + 0x10), (s32 *)(arg0 + 0x1C)) == 0) {
            return 0;
        }
        f = arg0[0] |= 6;
    }
    if (!(f & 4)) {
        if (vec3_normalize_len(arg0 + 0x10, arg0 + 0x10, 0, 0) == 0) {
            return 0;
        }
        if (vec3_normalize_len(arg0 + 0x1C, arg0 + 0x1C, 0, 0) == 0) {
            return 0;
        }
        arg0[0] |= 4;
    }
    return 1;
}

void vec2_from_angle_byte(s16, f32, f32 *, f32 *);

/* was func_1514FD78 */
f32 *emit_disc_random_point(f32 *arg0, f32 arg1, f32 *arg2) {
    f32 s;
    f32 c;

    vec2_from_angle_byte(random_int() & 0xFF, arg0[10] * random_float(), &c, &s);
    arg2[0] = (arg0[1] + (arg0[7] * s + arg0[4] * c)) * arg1;
    arg2[1] = (arg0[2] + (arg0[8] * s + arg0[5] * c)) * arg1;
    arg2[2] = (arg0[3] + (arg0[9] * s + arg0[6] * c)) * arg1;
    return arg2;
}

/* P159 */
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
void particle_burst_spawn_vec(s32, s32, f32, f32, s32, f32, f32, f32, f32, s16, s16, s16, s16, s16, s16, s8, u8, s32);
// spray_particles_spawn: scales `normal` by 1000 (in place) and spawns base + rand % (extra + 1) particles
// (particle_burst_spawn_vec) at p's point, each moving along normal plus a random offset in the plane of axisA / axisB
// (vec2_from_angle_byte: random angle, radius rand * spread), times a random speed; size, life and the rest come from
// the parameter block p (impact_spray_params_init fills one).
/* was func_1514FE68 */
void emit_spray_particles(u8 *p, u8 *normal, s32 *axisA, s32 *axisB, f32 spread, s32 arg5, s32 arg6) {
    typedef struct {
        s32 countBase;     /* 0x00 */
        s32 countExtra;    /* 0x04 */
        f32 pos[3];        /* 0x08 */
        f32 speedBase;     /* 0x14 */
        f32 speedRange;    /* 0x18 */
        f32 sizeBase;      /* 0x1C */
        f32 sizeRange;     /* 0x20 */
        f32 size2Base;     /* 0x24 */
        f32 size2Range;    /* 0x28 */
        s32 lifeBase;      /* 0x2C */
        s32 lifeExtra;     /* 0x30 */
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s8 u50;
    } SprayParams;
    SprayParams *sp = (SprayParams *)p;
    f32 *n = (f32 *)normal;
    f32 *a = (f32 *)axisA;
    f32 *b = (f32 *)axisB;
    f32 c;
    f32 s;
    f32 speed;
    f32 r1;
    f32 r2;
    f32 vel[3];
    u32 count;
    u32 angle;
    u32 life;

    n[0] *= 1000.0f;
    n[1] *= 1000.0f;
    n[2] *= 1000.0f;
    count = (u32)random_int() % (u32)(sp->countExtra + 1) + sp->countBase;
    for (; count != 0; count--) {
        speed = random_float() * sp->speedRange + sp->speedBase;
        angle = random_int();
        vec2_from_angle_byte(angle & 0xFF, random_float() * spread, &c, &s);
        vel[0] = (a[0] * c + b[0] * s + n[0]) * speed;
        vel[1] = (a[1] * c + b[1] * s + n[1]) * speed;
        vel[2] = (a[2] * c + b[2] * s + n[2]) * speed;
        r1 = random_float();
        r2 = random_float();
        life = (u32)random_int() % (u32)(sp->lifeExtra + 1) + sp->lifeBase;
        particle_burst_spawn_vec((s32)sp->pos, (s32)vel, r1 * sp->sizeRange + sp->sizeBase, r2 * sp->size2Range + sp->size2Base,
                      life, sp->u34, sp->u38, sp->u3C, sp->u40, sp->u44, sp->u46, sp->u48, sp->u4A, sp->u4C, sp->u4E,
                      sp->u50, (u8)arg5, arg6);
    }
}

s32 vec3_make_basis(u8 *, s32 *, s32 *);
void emit_spray_particles(u8 *, u8 *, s32 *, s32 *, f32, s32, s32);
/* was func_15150108 */
void emit_spray_along_normal(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp34[3];
    s32 sp28[3];
    if (vec3_make_basis(arg0, sp34, sp28) != 0) {
        emit_spray_particles(arg0 + 0x10, arg0, sp34, sp28, (*(f32 *)((u8 *)arg0 + 0xC)), (s32) arg1, arg2);
    }
}

s32 vec3_normalize_len(u8 *, u8 *, void *, void *);
/* was func_1515016C */
void emit_spray_from_surface(u8 *arg0, u8 arg1, s32 arg2) {
    f32 a[3];
    s32 a1;
    s32 a2;
    f32 b[3];
    s32 b1;
    s32 b2;
    f32 c[3];
    s32 c1;
    s32 c2;
    if (tri_calc_normal(arg0 + 0xC, (u8 *)a, (u8 *)b, (u8 *)c) != 0) {
        vec3_normalize_len((u8 *)a, (u8 *)a, &a1, &a2);
        vec3_normalize_len((u8 *)b, (u8 *)b, &b1, &b2);
        vec3_normalize_len((u8 *)c, (u8 *)c, &c1, &c2);
        if (vec3_dot((u8 *)c, arg0) < 0.0f) {
            c[0] = -c[0];
            c[1] = -c[1];
            c[2] = -c[2];
        }
        emit_spray_particles(arg0 + 0x24, (u8 *)c, (s32 *)a, (s32 *)b, *(f32 *)(arg0 + 0x20), arg1, arg2);
    }
}

s32 particle_burst_spawn_dir(u8 *, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
/* was func_15150258 */
void emit_random_sprites(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    n = *(s32 *)(arg0 + 8) + (random_int() % (u32)(*(s32 *)(arg0 + 0xC) + 1));
    while (n != 0) {
        particle_burst_spawn_dir(arg0 + 0x10,
            *(s16 *)(arg0 + 0) + (random_int() % (u32)(*(s16 *)(arg0 + 2) + 1)),
            *(s16 *)(arg0 + 4) + (random_int() % (u32)(*(s16 *)(arg0 + 6) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * random_float(),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * random_float(),
            *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * random_float(),
            *(s32 *)(arg0 + 0x34) + (random_int() % (u32)(*(s32 *)(arg0 + 0x38) + 1)),
            *(f32 *)(arg0 + 0x3C), *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x48),
            *(s16 *)(arg0 + 0x4C), *(s16 *)(arg0 + 0x4E), *(s16 *)(arg0 + 0x50), *(s16 *)(arg0 + 0x52),
            *(s16 *)(arg0 + 0x54), *(s16 *)(arg0 + 0x56), *(s8 *)(arg0 + 0x58), arg1, arg2);
        n--;
    }
}

void emit_disc_from_surface();
s32 emit_dust_on_disc();

/* was func_1515046C */
void emit_dust_on_surface_disc(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    emit_disc_from_surface(arg0, sp24);
    emit_dust_on_disc(sp24, arg1, arg2, arg3, arg4);
}

/* P153 */
s32 emit_disc_prepare(u8 *arg0);
f32 *emit_disc_random_point(f32 *arg0, f32 arg1, f32 *arg2);

// path_particles_spawn: P153: when the path / curve `path` is usable (emit_disc_prepare) spawns def +0xC + random
// [0, def +0xE] particles (impact_dust_cloud_spawn) along it: each at a random point (emit_disc_random_point at def +0x10 + random *
// +0x14) with sprite def +0x31, size +0x1C + random * +0x20, life +0x18 + random [0, +0x1A], alpha +0x24 + random
// [0, +0x25], speed +0x28 + random * +0x2C, flag 1 below chance +0x34, scale 1.4 x 1.4, owner / owner arg,
// +0x38, flag 2 below chance +0x3C. The asm returns nothing; the callers' prototypes say s32 (game_eu_1FB080): 0.
/* was func_151504B4 */
s32 emit_dust_on_disc(f32 *path, u8 *def, s32 owner, s32 arg3, s32 arg4) {
    f32 pos[3];
    f32 size;
    f32 speed;
    f32 chance1;
    f32 chance2;
    s32 rLife;
    s32 rAlpha;
    s32 n;

    if (emit_disc_prepare((u8 *) path) == 0) {
        return 0;
    }
    n = (u32) random_int() % (u32) (*(s16 *) (def + 0xE) + 1) + *(s16 *) (def + 0xC);
    while (n != 0) {
        emit_disc_random_point(path, random_float() * *(f32 *) (def + 0x14) + *(f32 *) (def + 0x10), pos);
        size = random_float();
        rLife = random_int();
        rAlpha = random_int();
        speed = random_float();
        chance1 = random_float();
        chance2 = random_float();
        impact_dust_cloud_spawn(def, pos, def[0x31], size * *(f32 *) (def + 0x20) + *(f32 *) (def + 0x1C),
                      (u32) rLife % (u32) (*(s16 *) (def + 0x1A) + 1) + *(s16 *) (def + 0x18),
                      (u32) rAlpha % (u32) (def[0x25] + 1) + def[0x24],
                      speed * *(f32 *) (def + 0x2C) + *(f32 *) (def + 0x28),
                      (chance1 < *(f32 *) (def + 0x34)) ? 1 : 0, 1.4f, 1.4f, 1, owner, def[0x38],
                      (chance2 < *(f32 *) (def + 0x3C)) ? 1 : 0, arg3 & 0xFF, arg4);
        n--;
    }
    return 0;
}

/* P155 */
void vec3_from_angles_byte(s16, s16, f32, void *);
typedef struct {
    u8 pad0[0xC];
    s16 countMin;  /* +0x0C */
    s16 countRange;
    f32 speedMin;  /* +0x10 */
    f32 speedRange;
    s16 lifeMin;   /* +0x18 */
    s16 lifeRange;
    f32 sizeMin;   /* +0x1C */
    f32 sizeRange;
    u8 alphaMin;   /* +0x24 */
    u8 alphaRange;
    u8 pad26[2];
    f32 spinMin;   /* +0x28 */
    f32 spinRange;
    u8 pad30;
    u8 kind;       /* +0x31 */
    u8 pad32[2];
    f32 chance7;   /* +0x34 */
    u8 b38;
    u8 pad39[3];
    f32 chanceD;   /* +0x3C */
} Def06E8;
// particle_spray_spawn: spawns countMin + rand(countRange + 1) particles of def (impact_dust_cloud_spawn), each with a random
// direction (yaw / pitch ranges `angles` = {yaw base, yaw range, pitch base, pitch range}) and speed turned into a
// velocity by vec3_from_angles_byte, and random size, life, alpha, spin and two chance flags from def; scale 1.4.
// Returns 0 (the asm leaves v0 unset; the callers ignore it).
/* was func_151506E8 */
s32 emit_dust_by_angles(void *angles, void *def, s32 arg2, u8 arg3, s32 arg4) {
    s16 *a = angles;
    Def06E8 *d = def;
    f32 vel[3];
    u32 n;
    u32 r1, r2;
    f32 f;
    f32 size;
    f32 spin;
    f32 c7;
    f32 cD;

    n = random_int() % (u32)(d->countRange + 1) + d->countMin;
    while (n != 0) {
        r1 = random_int();
        r2 = random_int();
        f = random_float();
        vec3_from_angles_byte(r1 % (u32)(a[1] + 1) + a[0], r2 % (u32)(a[3] + 1) + a[2], f * d->speedRange + d->speedMin, vel);
        size = random_float();
        r1 = random_int();
        r2 = random_int();
        spin = random_float();
        c7 = random_float();
        cD = random_float();
        impact_dust_cloud_spawn(d, vel, d->kind, size * d->sizeRange + d->sizeMin, r1 % (u32)(d->lifeRange + 1) + d->lifeMin,
                      r2 % (u32)(d->alphaRange + 1) + d->alphaMin, spin * d->spinRange + d->spinMin, c7 < d->chance7,
                      1.4f, 1.4f, 1, arg2, d->b38, cD < d->chanceD, arg3, arg4);
        n--;
    }
    return 0;
}

/* P181 */
void vec3_from_angles_byte(s16, s16, f32, void *);
s32 mdl_particle_spawn_ex(void *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

// spark_burst_spawn: P181: spawns def +0 + rand % (def +4 + 1) particles (0 = none) from the burst definition
// `arg0`: each at a random direction (angles ang[0] + rand % (ang[1] + 1), ang[2] + rand % (ang[3] + 1)) at
// distance def +0x54 from the centre def +8, moving that way at def +0x14 + random x +0x18, random rotation 0..360
// on all axes, spin +-def +0x30 about x / z, fade def +0x1C + random x +0x20, life def +0x24 + rand % (+0x26 + 1),
// texture ((s32 *)def +0x48)[k] for a random k < def +0x50 with size ((f32 *)def +0x4C)[k] x (def +0x28 + random x
// +0x2C) (+0 = def +0x44 x size), +4 = def +0x3C + random x +0x40. With chance def +0x38 the particle is solid
// (+0x61 = 13, +0x63 = def +0x59), else +0x61 = 8. Flags 0x121E9, plus 0x800 and effect kind 3 (else 0) when
// def +0x58 bit 0 is set. Effect via mdl_particle_spawn_ex (def +0x34, extra bytes def +0x5C copied from def +0x60 to
// +0x170, owner arg2 / arg3). The asm leaves a stale v0; the callers ignore it (s32 matches their prototype).
/* was func_15150970 */
s32 emit_spark_burst(s32 *arg0, s16 *ang, u8 arg2, s32 arg3) {
    u8 *def = (u8 *)arg0;
    struct {
        f32 u00;       /* +0x00 */
        f32 u04;       /* +0x04 */
        f32 sizeX;     /* +0x08 */
        f32 sizeY;     /* +0x0C */
        f32 rot[3];    /* +0x10 */
        f32 u1C[3];    /* +0x1C */
        f32 pos[3];    /* +0x28 */
        f32 vel[3];    /* +0x34 */
        f32 spinX;     /* +0x40 */
        f32 spinY;     /* +0x44 */
        f32 spinZ;     /* +0x48 */
        f32 fade;      /* +0x4C */
        s32 flags;     /* +0x50 */
        s16 life;      /* +0x54 */
        s16 texture;   /* +0x56 */
        u8 u58;
        s32 u5C;
        u8 u60;
        u8 u61;        /* +0x61 */
        u8 u62;
        u8 u63;        /* +0x63 */
        u8 u64[4];
        u8 u68;
        s8 u69;
        u8 u6A;
        s32 u6C;
        u8 u70;
        s16 u72;
        s16 u74;
        s32 u78;
    } p;
    s32 n;
    s16 angA;
    s16 angB;
    u32 k;
    u8 *e;

    p.u1C[0] = 1.0f;
    p.u1C[1] = 1.0f;
    p.u1C[2] = 1.0f;
    p.spinY = 0.0f;
    p.flags = ((def[0x58] & 1) ? 0x800 : 0) | 0x21E9 | 0x10000;
    p.u58 = 0;
    p.u5C = 0;
    p.u60 = 0xFF;
    p.u62 = 0;
    p.u64[0] = 0;
    p.u64[1] = 0;
    p.u64[2] = 0;
    p.u64[3] = 0;
    p.u68 = 2;
    p.u69 = -1;
    p.u6A = 0;
    p.u6C = 0;
    p.u70 = 0;
    p.u72 = 0xC;
    p.u74 = 0x15;
    p.u78 = 0;
    n = (u32) random_int() % (u32) (*(s32 *)(def + 4) + 1) + *(s32 *)(def + 0);
    while (n != 0) {
        angA = (u32) random_int() % (u32) (ang[1] + 1) + ang[0];
        angB = (u32) random_int() % (u32) (ang[3] + 1) + ang[2];
        if (random_float() < *(f32 *)(def + 0x38)) {
            p.u61 = 13;
            p.u63 = def[0x59];
        } else {
            p.u61 = 8;
            p.u63 = 0;
        }
        p.u04 = random_float() * *(f32 *)(def + 0x40) + *(f32 *)(def + 0x3C);
        p.rot[0] = random_float() * 360.0f;
        p.rot[1] = random_float() * 360.0f;
        p.rot[2] = random_float() * 360.0f;
        vec3_from_angles_byte(angA, angB, random_float() * *(f32 *)(def + 0x18) + *(f32 *)(def + 0x14), p.vel);
        p.spinX = random_float() * (*(f32 *)(def + 0x30) + *(f32 *)(def + 0x30)) - *(f32 *)(def + 0x30);
        p.spinZ = random_float() * (*(f32 *)(def + 0x30) + *(f32 *)(def + 0x30)) - *(f32 *)(def + 0x30);
        p.fade = random_float() * *(f32 *)(def + 0x20) + *(f32 *)(def + 0x1C);
        p.life = (u32) random_int() % (u32) (*(s16 *)(def + 0x26) + 1) + *(s16 *)(def + 0x24);
        vec3_from_angles_byte(angA, angB, *(f32 *)(def + 0x54), p.pos);
        p.pos[0] += *(f32 *)(def + 0x8);
        p.pos[1] += *(f32 *)(def + 0xC);
        p.pos[2] += *(f32 *)(def + 0x10);
        k = (u32) random_int() % *(u32 *)(def + 0x50);
        p.texture = (*(s32 **)(def + 0x48))[k];
        p.sizeY = (*(f32 **)(def + 0x4C))[k] * (*(f32 *)(def + 0x28) + random_float() * *(f32 *)(def + 0x2C));
        p.sizeX = p.sizeY;
        p.u00 = *(f32 *)(def + 0x44) * p.sizeX;
        e = (u8 *)mdl_particle_spawn_ex(&p, (def[0x58] & 1) ? 3 : 0, 0xFF, *(s32 *)(def + 0x34), *(s32 *)(def + 0x5C), arg2,
                                arg3);
        if (*(s32 *)(def + 0x5C) > 0 && e != NULL) {
            memcpy((s32)(e + 0x170), *(f32 **)(def + 0x60), *(s32 *)(def + 0x5C));
        }
        n--;
    }
    return 0;
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 allocate_memory(s32, s32, s32, s32);
s32 mdl_particle_spawn_ex(void *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

// base + rand % (extra + 1) (random_int, unsigned remainder)
#define RAND_SPREAD(base, extra) ((u32) random_int() % (u32) ((extra) + 1) + (base))

// debris_burst_spawn: spawns base + rand % (extra + 1) pieces (at most n) of the n kinds ids[] / scales[]; each
// piece takes a random kind not used yet in this burst (a temporary n-byte used map from allocate_memory), at the
// spec's point plus a random offset (vec3_from_angles_byte with length arg10) moving in a random direction, with random
// spins, sway, life and size (scales[k] x random), solid (+0x50 bit 0, +0x61 = 0xD, +0x63 = spec +0x40) with
// chance spec +0x3C; effect kind 3 via mdl_particle_spawn_ex (arg9, extra bytes arg5 copied from arg4 to +0x170, arg13 /
// arg14). Option bits: arg7 -> 0x80, arg11 -> 0x4000, arg12 -> 0x100000. The result is unused by all callers.
/* was func_15150D7C */
s32 emit_debris_burst(s32 *arg0, s32 *ids, s32 *scales, s32 n, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9, f32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    typedef struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        f32 pos[3];         /* 0x08 */
        s16 angXBase;       /* 0x14 */
        s16 angXExtra;      /* 0x16 */
        s16 angYBase;       /* 0x18 */
        s16 angYExtra;      /* 0x1A */
        f32 speedBase;      /* 0x1C */
        f32 speedRange;     /* 0x20 */
        f32 u24Base;        /* 0x24 */
        f32 u24Range;       /* 0x28 */
        s16 lifeBase;       /* 0x2C */
        s16 lifeExtra;      /* 0x2E */
        f32 sizeBase;       /* 0x30 */
        f32 sizeRange;      /* 0x34 */
        f32 sway;           /* 0x38 */
        f32 solidChance;    /* 0x3C */
        u8 solidKind;       /* 0x40 */
    } DebrisSpec;
    struct {
        f32 u00;            /* 0x00 = 1 */
        f32 u04;            /* 0x04 = 0.5610 */
        f32 size[2];        /* 0x08 */
        f32 spin[3];        /* 0x10 */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 vel[3];         /* 0x34 */
        f32 swayX;          /* 0x40 */
        f32 u44;            /* 0x44 = 0 */
        f32 swayZ;          /* 0x48 */
        f32 u4C;            /* 0x4C */
        u32 flags;          /* 0x50 */
        s16 life;           /* 0x54 */
        s16 id;             /* 0x56 */
        u8 u58;             /* 0x58 = arg6 */
        s32 u5C;            /* 0x5C = 0 */
        u8 u60;             /* 0x60 = 0xFF */
        u8 u61;             /* 0x61 = 8 / 0xD */
        u8 u62;             /* 0x62 = 0 */
        u8 u63;             /* 0x63 */
        u8 u64[4];          /* 0x64 = 0 */
        u8 u68;             /* 0x68 = 2 */
        s8 u69;             /* 0x69 = arg8 */
        u8 u6A;             /* 0x6A = 0 */
        s32 u6C;            /* 0x6C = 0 */
        u8 u70;             /* 0x70 = 0 */
        s16 u72;            /* 0x72 = 0xC */
        s16 u74;            /* 0x74 = 0x15 */
    } fx;
    DebrisSpec *sp = (DebrisSpec *) arg0;
    u8 *used;
    u8 *p;
    s32 count;
    s32 left;
    s32 i;
    u32 r;
    s16 a;
    s16 b;
    u8 *e;

    used = (u8 *) allocate_memory(n, 2, 2, 1);
    if (used == NULL) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        used[i] = 0;
    }
    left = n;
    fx.u00 = 1.0f;
    fx.u1C[0] = 1.0f;
    fx.u1C[1] = 1.0f;
    fx.u1C[2] = 1.0f;
    fx.u04 = 0.561000049f;
    fx.u44 = 0.0f;
    fx.flags = 0x13968 | ((u8) arg12 ? 0x100000 : 0) | ((u8) arg7 ? 0x80 : 0) | ((u8) arg11 ? 0x4000 : 0);
    count = RAND_SPREAD(sp->countBase, sp->countExtra);
    if (n < count) {
        count = n;
    }
    fx.u58 = arg6;
    fx.u5C = 0;
    fx.u60 = 0xFF;
    fx.u62 = 0;
    fx.u64[0] = 0;
    fx.u64[1] = 0;
    fx.u64[2] = 0;
    fx.u64[3] = 0;
    fx.u68 = 2;
    fx.u6A = 0;
    fx.u6C = 0;
    fx.u70 = 0;
    fx.u72 = 0xC;
    fx.u74 = 0x15;
    fx.u69 = arg8;
    for (; count != 0; count--) {
        a = RAND_SPREAD(sp->angXBase, sp->angXExtra);
        b = RAND_SPREAD(sp->angYBase, sp->angYExtra);
        vec3_from_angles_byte(a, b, random_float() * sp->speedRange + sp->speedBase, fx.vel);
        vec3_from_angles_byte(a, b, arg10, fx.pos);
        fx.pos[0] += sp->pos[0];
        fx.pos[1] += sp->pos[1];
        fx.pos[2] += sp->pos[2];
        fx.spin[0] = random_float() * 360.0f;
        fx.spin[1] = random_float() * 360.0f;
        fx.spin[2] = random_float() * 360.0f;
        fx.swayX = random_float() * (sp->sway + sp->sway) - sp->sway;
        fx.swayZ = random_float() * (sp->sway + sp->sway) - sp->sway;
        fx.u4C = random_float() * sp->u24Range + sp->u24Base;
        fx.life = RAND_SPREAD(sp->lifeBase, sp->lifeExtra);
        /* the r-th unused kind, counting round from 0 */
        r = (u32) random_int() % (u32) left;
        i = 0;
        p = used;
        for (;;) {
            while (*p != 0) {
                i++;
                p++;
            }
            if (r == 0) {
                break;
            }
            i++;
            r--;
            p++;
            if (i >= n) {
                i = 0;
                p = used;
            }
        }
        fx.id = ids[i];
        fx.size[1] = ((f32 *) scales)[i] * (sp->sizeBase + random_float() * sp->sizeRange);
        left--;
        fx.size[0] = fx.size[1];
        *p = 1;
        if (random_float() < sp->solidChance) {
            fx.flags |= 1;
            fx.u61 = 0xD;
            fx.u63 = sp->solidKind;
        } else {
            fx.flags &= ~1;
            fx.u63 = 0;
            fx.u61 = 8;
        }
        e = (u8 *) mdl_particle_spawn_ex(&fx, 3, 0xFF, arg9, arg5, (u8) arg13, arg14);
        if (arg4 != 0 && e != NULL) {
            memcpy((s32) (e + 0x170), (f32 *) arg4, arg5);
        }
    }
    return 0;
}
#undef RAND_SPREAD

void vec3_from_angles_byte(s16, s16, f32, void *);
/* P59: arg 2 (z) is f32 in the definition (src_eu/nm_asm/D5E90.c); wasm needs the exact signature. */
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
#define RAY_Z0(p) (*(f32 *)(p))
s32 prop_is_flagged(s32);

/* was func_1515128C */
void emit_debris_on_near_surfaces(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    f32 spC0[3];
    u8 spAC[0x14];
    f32 spA0[3];
    f32 sp9C;
    s32 sp98;
    u8 *hit;

    n = *(s32 *)(arg0 + 0) + (random_int() % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        vec3_from_angles_byte(*(s16 *)(arg0 + 0x14) + (random_int() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (random_int() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)), 100.0f, spC0);
        hit = spAC; // fakematch: named pointer to spAC (permuter), both calls use it
        if (collision_ray_cast(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0xC), RAY_Z0(arg0 + 0x10), spC0[0], spC0[1], spC0[2], 0,
                hit, &spA0[0], &spA0[1], &spA0[2], &sp9C, &sp98, 0, 0.0f) != 0) {
            if (prop_is_flagged(sp98) != 0) {
                if (sp9C < *(f32 *)(arg0 + 0x1C)) {
                    impact_debris_spawn(*(u8 *)(arg0 + 0x2C), *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * random_float(),
                        (random_int() % 156U) + 100, (s32)hit, (struct17 *)spA0,
                        *(s16 *)(arg0 + 0x28) + (random_int() % (u32)(*(s16 *)(arg0 + 0x2A) + 1)),
                        1, 1, 1, arg1, arg2);
                }
            }
        }
        n--;
    }
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 tumble_debris_spawn(u8 *, f32 *, f32, f32 *, f32 *, f32, f32, u8, s32, u8, s32, u8, s32);

/* was func_15151500 */
void emit_tumbling_pieces(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 spBC[3];
    f32 d;
    s32 n;
    f32 spA8[3];
    f32 sp9C[3];

    d = 2.0f * *(f32 *)(arg0 + 0x2C);
    spBC[1] = 0.0f;
    n = random_int();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        spA8[0] = random_float() * 360.0f;
        spA8[1] = random_float() * 360.0f;
        spA8[2] = random_float() * 360.0f;
        vec3_from_angles_byte(*(s16 *)(arg0 + 0x1C) + (random_int() % (u32)(*(s16 *)(arg0 + 0x1E) + 1)),
            *(s16 *)(arg0 + 0x20) + (random_int() % (u32)(*(s16 *)(arg0 + 0x22) + 1)),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * random_float(), sp9C);
        spBC[0] = random_float() * d - *(f32 *)(arg0 + 0x2C);
        spBC[2] = random_float() * d - *(f32 *)(arg0 + 0x2C);
        tumble_debris_spawn(arg0 + 8, spA8, *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0x18) * random_float(), sp9C, spBC,
            *(f32 *)(arg0 + 0x30) + *(f32 *)(arg0 + 0x34) * random_float(), *(f32 *)(arg0 + 0x38),
            *(u8 *)(arg0 + 0x3C), *(s16 *)(arg0 + 0x3E) + (random_int() % (u32)(*(s16 *)(arg0 + 0x40) + 1)),
            arg1, 0, arg2, arg3);
        n--;
    }
}

s32 memcpy(s32, f32 *, s32);

/* was func_1515176C */
void emit_effect3d_from_surface(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u84;
        f32 u88;
        u8 pad8C[0x4];
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        u8 uB0;
        u8 uB1;
        u16 uB2;
        s16 uB4;
        u8 padB6[0x2];
        s32 uB8;
        s32 uBC;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        s32 uF0;
        s8 uF4;
        s8 uF5;
        u8 uF6;
        u8 uF7;
        u8 padF8[0xC];
        s16 u104;
        s16 u106;
        s32 u108;
        s32 u10C;
        u8 u110;
        u8 pad111[0x3];
        f32 u114;
        f32 u118;
        s32 u11C;
        s32 u120;
        u8 u124;
        u8 pad125[0x3];
        s32 u128;
        s32 u12C;
        s32 u130;
        s32 u134;
        u8 u138;
        u8 pad139[0x3];
        s32 u13C;
        s32 u140;
    } sp;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 var_s2;
    u8 *temp_v0;

    sp.u104 = (*(s16 *)((u8 *)arg0 + 0x68));
    sp.u106 = (*(s16 *)((u8 *)arg0 + 0x6A));
    sp.uB0 = (*(u8 *)((u8 *)arg0 + 0x34));
    sp.uB1 = (*(u8 *)((u8 *)arg0 + 0x35));
    sp.uB8 = 0;
    sp.uBC = 0;
    sp.uC0 = 0xFF;
    sp.uC1 = 0xFF;
    sp.uC2 = 0xFF;
    sp.uC3 = 0xFF;
    sp.uB2 = (*(u16 *)((u8 *)arg0 + 0x36));
    (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0xC));
    sp.uE4 = 1.0f;
    sp.uE8 = 1.0f;
    sp.uEC = 1.0f;
    sp.uF5 = 0xFF;
    sp.uF0 = (*(s32 *)((u8 *)arg0 + 0x44)) | 0x08000000;
    sp.uF6 = (*(u8 *)((u8 *)arg0 + 0x5C));
    sp.uF7 = (*(u8 *)((u8 *)arg0 + 0x5D));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x6C));
    if (tri_calc_normal(arg0 + 0x1C, &sp.u138, &sp.u124, &sp.u110) != 0) {
        vec3_normalize_len(&sp.u138, &sp.u138, &sp.u134, &sp.u130);
        vec3_normalize_len(&sp.u124, &sp.u124, &sp.u120, &sp.u11C);
        vec3_normalize_len(&sp.u110, &sp.u110, &sp.u10C, &sp.u108);
        if (vec3_dot(&sp.u110, arg0 + 0x10) < 0.0f) {
            sp.u110 = -(*(f32 *)&(sp.u110));
            sp.u114 = -sp.u114;
            sp.u118 = -sp.u118;
        }
        sp.uA8 = 0.0f;
        sp.u110 = (*(f32 *)&(sp.u110)) * 1000.0f;
        sp.u114 *= 1000.0f;
        sp.u118 *= 1000.0f;
        var_s2 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 2)) + 1)) + (*(s16 *)((u8 *)arg0 + 0));
        if (var_s2 != 0) {
            do {
                temp_s1 = random_int();
                vec2_from_angle_byte((s16) (temp_s1 & 0xFF), random_float() * (*(f32 *)((u8 *)arg0 + 0x30)), &sp.u84, &sp.u88);
                temp_f20 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x58))) + (*(f32 *)((u8 *)arg0 + 0x54));
                sp.uB4 = (s16) (s32) ((random_float() * (f32) (*(s16 *)((u8 *)arg0 + 0x3A))) + (f32) (*(s16 *)((u8 *)arg0 + 0x38)));
                temp_f16 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x40))) + (*(f32 *)((u8 *)arg0 + 0x3C));
                sp.uC8 = temp_f16;
                sp.uC4 = temp_f16;
                sp.uD8 = random_float() * 360.0f;
                sp.uDC = random_float() * 360.0f;
                sp.uE0 = random_float() * 360.0f;
                sp.uF4 = (random_int() % (u32) ((*(u8 *)((u8 *)arg0 + 0x49)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x48));
                sp.u90 = (((*(f32 *)&(sp.u138)) * sp.u84) + ((*(f32 *)&(sp.u124)) * sp.u88) + sp.u110) * temp_f20;
                sp.u94 = ((sp.u13C * sp.u84) + (sp.u128 * sp.u88) + sp.u114) * temp_f20;
                sp.u98 = ((sp.u140 * sp.u84) + (sp.u12C * sp.u88) + sp.u118) * temp_f20;
                sp.u9C = (random_float() * (*(f32 *)((u8 *)arg0 + 0x50))) + (*(f32 *)((u8 *)arg0 + 0x4C));
                temp_f20_2 = (*(f32 *)((u8 *)arg0 + 0x70));
                sp.uA4 = (random_float() * (2.0f * temp_f20_2)) - temp_f20_2;
                temp_f20_3 = (*(f32 *)((u8 *)arg0 + 0x70));
                sp.uAC = (random_float() * (2.0f * temp_f20_3)) - temp_f20_3;
                temp_s1_2 = random_int();
                temp_v0 = effect3d_spawn_full(&sp.uB0, (s32) ((u8 *)&D_800A4AA0), 0x19U, 0U, 0U, 0x17U, (u8) ((random_int() & 1) + ((temp_s1_2 & 1) * 2)), (*(s32 *)((u8 *)arg0 + 0x60)), (*(s32 *)((u8 *)arg0 + 0x64)), 0x20, (u8) (arg1 & 0xFF), arg2);
                if (temp_v0 != NULL) {
    s32 pad;
                    memcpy(temp_v0 + 0x110, &sp.u90, 0x20);
                }
                var_s2 -= 1;
            } while (var_s2 != 0);
        }
    }
}
/* was func_15151BE0 */
void emit_sparks_from_surface(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u88;
        f32 u8C;
        u8 pad90[0x4];
        s32 u94;
        s32 u98;
        u8 u9C;
        u8 pad9D[0x3];
        f32 uA0;
        f32 uA4;
        s32 uA8;
        s32 uAC;
        u8 uB0;
        u8 padB1[0x3];
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        u8 uC4;
        u8 padC5[0x3];
        s32 uC8;
        s32 uCC;
        u8 padD0[0x4];
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        u8 padE8[0x4];
        u8 uEC;
        u8 uED;
        u8 uEE;
        s8 uEF;
        s16 uF0;
        s16 uF2;
        s32 uF4;
        u8 padF8[0x8];
        s16 u100;
        s16 u102;
        s32 u104;
        u8 pad108[0x1];
        s8 u109;
        u8 pad10A[0x2];
        s32 u10C;
    } sp;
    f32 temp_f20;
    s32 temp_s1;
    s32 var_s2;

    if (tri_calc_normal(arg0 + 0x18, &sp.uC4, &sp.uB0, &sp.u9C) != 0) {
        vec3_normalize_len(&sp.uC4, &sp.uC4, &sp.uC0, &sp.uBC);
        vec3_normalize_len(&sp.uB0, &sp.uB0, &sp.uAC, &sp.uA8);
        vec3_normalize_len(&sp.u9C, &sp.u9C, &sp.u98, &sp.u94);
        if (vec3_dot(&sp.u9C, arg0 + 0xC) < 0.0f) {
            sp.u9C = -(*(f32 *)&(sp.u9C));
            sp.uA0 = -sp.uA0;
            sp.uA4 = -sp.uA4;
        }
        sp.u104 = 1;
        sp.u9C = (*(f32 *)&(sp.u9C)) * 1000.0f;
        sp.uA0 *= 1000.0f;
        sp.uA4 *= 1000.0f;
        sp.u102 = (s16) (*(u8 *)((u8 *)arg0 + 0x55));
        sp.uED = (*(u8 *)((u8 *)arg0 + 0x54));
        sp.uEE = (*(u8 *)((u8 *)arg0 + 0x70));
        sp.uEC = (*(u8 *)((u8 *)arg0 + 0x56));
        sp.uF0 = (*(s16 *)((u8 *)arg0 + 0x9C));
        sp.uF2 = (*(s16 *)((u8 *)arg0 + 0x9E));
        (*(s32 *)((u8 *)(&sp.uF4) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
        (*(s32 *)((u8 *)(&sp.uF4) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
        (*(s32 *)((u8 *)(&sp.uF4) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
        sp.u10C = (*(s32 *)((u8 *)arg0 + 0xA0));
        var_s2 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x4A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x48));
        if (var_s2 != 0) {
            do {
                temp_s1 = random_int();
                vec2_from_angle_byte((s16) (temp_s1 & 0xFF), random_float() * (*(f32 *)((u8 *)arg0 + 0x2C)), &sp.u88, &sp.u8C);
                temp_f20 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x44))) + (*(f32 *)((u8 *)arg0 + 0x40));
                sp.uEF = (random_int() % (u32) ((*(u8 *)((u8 *)arg0 + 0x72)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x71));
                sp.u109 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x4E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x4C));
                sp.u100 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x52)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x50));
                sp.uD4 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x34))) + (*(f32 *)((u8 *)arg0 + 0x30));
                sp.uE4 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x3C))) + (*(f32 *)((u8 *)arg0 + 0x38));
                sp.uD8 = (((*(f32 *)&(sp.uC4)) * sp.u88) + ((*(f32 *)&(sp.uB0)) * sp.u8C) + sp.u9C) * temp_f20;
                sp.uDC = ((sp.uC8 * sp.u88) + (sp.uB4 * sp.u8C) + sp.uA0) * temp_f20;
                sp.uE0 = ((sp.uCC * sp.u88) + (sp.uB8 * sp.u8C) + sp.uA4) * temp_f20;
                trail_spawn(&sp.uF4, &sp.uD4, 0, (*(s32 *)((u8 *)arg0 + 0x58)), (*(s32 *)((u8 *)arg0 + 0x5C)), (*(s32 *)((u8 *)arg0 + 0x60)), (*(s32 *)((u8 *)arg0 + 0x64)), (*(s32 *)((u8 *)arg0 + 0x68)), (*(s32 *)((u8 *)arg0 + 0x6C)), (*(s32 *)((u8 *)arg0 + 0x74)), (*(s32 *)((u8 *)arg0 + 0x78)), arg0 + 0x7C, 0, arg1 & 0xFF, arg2);
                var_s2 -= 1;
            } while (var_s2 != 0);
        }
    }
}
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

/* was func_15151FA8 */
void emit_sparks_by_angles(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        u8 padD0[0x4];
        u8 uD4;
        u8 uD5;
        u8 uD6;
        s8 uD7;
        s16 uD8;
        s16 uDA;
        s32 uDC;
        u8 padE0[0x8];
        s16 uE8;
        s16 uEA;
        s32 uEC;
        u8 padF0[0x1];
        s8 uF1;
        u8 padF2[0x2];
        s32 uF4;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;

    sp.uEC = 1;
    sp.uEA = (s16) (*(u8 *)((u8 *)arg0 + 0x39));
    sp.uD5 = (*(u8 *)((u8 *)arg0 + 0x38));
    sp.uD6 = (*(u8 *)((u8 *)arg0 + 0x54));
    sp.uD4 = (*(u8 *)((u8 *)arg0 + 0x3A));
    (*(s32 *)((u8 *)(&sp.uDC) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.uDC) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uDC) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uD8 = (*(s16 *)((u8 *)arg0 + 0x80));
    sp.uDA = (*(s16 *)((u8 *)arg0 + 0x82));
    sp.uF4 = (*(s32 *)((u8 *)arg0 + 0x84));
    var_s3 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x26)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x24));
    if (var_s3 != 0) {
        do {
            temp_s1 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x28));
            temp_s2 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x2C));
            temp_f28 = angle_byte_cos(temp_s2 & 0xFF);
            temp_f22 = angle_byte_cos((temp_s2 - 0x40) & 0xFF);
            temp_f24 = angle_byte_cos(temp_s1 & 0xFF);
            temp_f26 = angle_byte_cos((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x20))) + (*(f32 *)((u8 *)arg0 + 0x1C));
            sp.uD7 = (random_int() % (u32) ((*(u8 *)((u8 *)arg0 + 0x56)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x55));
            sp.uF1 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x32)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x30));
            sp.uE8 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x36)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x34));
            sp.uBC = (random_float() * (*(f32 *)((u8 *)arg0 + 0x10))) + (*(f32 *)((u8 *)arg0 + 0xC));
            temp_f2 = temp_f20 * temp_f28;
            sp.uCC = (random_float() * (*(f32 *)((u8 *)arg0 + 0x18))) + (*(f32 *)((u8 *)arg0 + 0x14));
            sp.uC0 = temp_f2 * temp_f26;
            sp.uC4 = -temp_f20 * temp_f22;
            sp.uC8 = temp_f2 * temp_f24;
            trail_spawn(&sp.uDC, &sp.uBC, 0, (*(s32 *)((u8 *)arg0 + 0x3C)), (*(s32 *)((u8 *)arg0 + 0x40)), (*(s32 *)((u8 *)arg0 + 0x44)), (*(s32 *)((u8 *)arg0 + 0x48)), (*(s32 *)((u8 *)arg0 + 0x4C)), (*(s32 *)((u8 *)arg0 + 0x50)), (*(s32 *)((u8 *)arg0 + 0x58)), (*(s32 *)((u8 *)arg0 + 0x5C)), arg0 + 0x60, 0, arg1 & 0xFF, arg2);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
s32 vec3_normalize_len(u8 *, u8 *, void *, void *);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
s32 mdl_particle_spawn(void *, s32, s32, s32, s32, s32);

/* mdl_particle_spawn particle request built by emit_impact_flash_spray (0x7C bytes; layout as Spark9768 in game_161520) */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 scaleB;
    /* 0x0C */ f32 scaleA;
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 scl[3];
    /* 0x28 */ s32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 u40;
    /* 0x44 */ f32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ s32 u50;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 frame;
    /* 0x58 */ u8 u58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[8];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ s32 u6C;
    /* 0x70 */ u8 u70;
    /* 0x71 */ u8 pad71;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x76 */ u8 pad76[6];
} Flash22DC;

// impact_flash_spray: spawns def +0 + random [0, def +4] kind-3 particles (mdl_particle_spawn) at def +8 for an impact
// flash (def = the 0x58-byte request of shot_impact_effects). The surface record at def +0x20 gives three axes
// (tri_calc_normal, each normalised by vec3_normalize_len); the third is flipped to face def +0x14 and scaled by 1000. Each
// particle moves along (a0 * c + a1 * s + a2) * speed, (c, s) = vec2_from_angle_byte(random angle, random * def +0x34),
// speed = def +0x38 + random * def +0x3C; random rotation (0..360 per axis), a random keyframe v of `n`
// (frames[v] at +0x56, scales[v] * (def +0x4C + random * def +0x50) as both scales), drift +-def +0x54 on +0x40 /
// +0x48, +0x4C = def +0x40 + random * def +0x44, life def +0x48 + random [0, def +0x4A].
/* was func_151522DC */
void emit_impact_flash_spray(u8 *def, s32 *frames, f32 *scales, s32 n, u8 kind, s32 owner) {
    Flash22DC rec;
    f32 ax0[3];
    f32 ax1[3];
    f32 ax2[3];
    f32 c;
    f32 s;
    f32 speed;
    f32 r;
    f32 w;
    u32 count;
    u32 v;
    s32 ang;
    f32 unused0;
    f32 unused1;

    if (tri_calc_normal(def + 0x20, (u8 *) ax0, (u8 *) ax1, (u8 *) ax2) == 0) {
        return;
    }
    vec3_normalize_len((u8 *) ax0, (u8 *) ax0, &unused0, &unused1);
    vec3_normalize_len((u8 *) ax1, (u8 *) ax1, &unused0, &unused1);
    vec3_normalize_len((u8 *) ax2, (u8 *) ax2, &unused0, &unused1);
    if (vec3_dot((u8 *) ax2, def + 0x14) < 0.0f) {
        ax2[0] = -ax2[0];
        ax2[1] = -ax2[1];
        ax2[2] = -ax2[2];
    }
    ax2[0] *= 1000.0f;
    ax2[1] *= 1000.0f;
    ax2[2] *= 1000.0f;
    rec.u00 = 1.0f;
    rec.u04 = 1.0f;
    rec.scl[0] = 1.0f;
    rec.scl[1] = 1.0f;
    rec.scl[2] = 1.0f;
    rec.pos[0] = *(s32 *) (def + 0x8);
    rec.pos[1] = *(s32 *) (def + 0xC);
    rec.pos[2] = *(s32 *) (def + 0x10);
    rec.u44 = 0.0f;
    rec.u50 = 0x29E8;
    count = (u32) random_int() % (u32) (*(s32 *) (def + 4) + 1) + *(s32 *) def;
    rec.u58 = 0;
    rec.u5C = 0;
    rec.u60[0] = 0xFF;
    rec.u60[1] = 8;
    rec.u60[2] = 0;
    rec.u60[3] = 0;
    rec.u60[4] = 0;
    rec.u60[5] = 0;
    rec.u60[6] = 0;
    rec.u60[7] = 0;
    rec.u68 = 2;
    rec.u6A = 0;
    rec.u6C = 0;
    rec.u70 = 0;
    rec.u72 = 12;
    rec.u74 = 0x15;
    while (count != 0) {
        speed = random_float() * *(f32 *) (def + 0x3C) + *(f32 *) (def + 0x38);
        ang = random_int();
        r = random_float() * *(f32 *) (def + 0x34);
        vec2_from_angle_byte((s16) (ang & 0xFF), r, &c, &s);
        rec.vel[0] = (ax0[0] * c + ax1[0] * s + ax2[0]) * speed;
        rec.vel[1] = (ax0[1] * c + ax1[1] * s + ax2[1]) * speed;
        rec.vel[2] = (ax0[2] * c + ax1[2] * s + ax2[2]) * speed;
        rec.rot[0] = random_float() * 360.0f;
        rec.rot[1] = random_float() * 360.0f;
        rec.rot[2] = random_float() * 360.0f;
        v = (u32) random_int() % (u32) n;
        rec.frame = frames[v];
        rec.scaleA = scales[v] * (*(f32 *) (def + 0x4C) + random_float() * *(f32 *) (def + 0x50));
        rec.scaleB = rec.scaleA;
        w = *(f32 *) (def + 0x54);
        rec.u40 = random_float() * (w + w) - w;
        w = *(f32 *) (def + 0x54);
        rec.u48 = random_float() * (w + w) - w;
        rec.u4C = random_float() * *(f32 *) (def + 0x44) + *(f32 *) (def + 0x40);
        rec.life = (u32) random_int() % (u32) (*(s16 *) (def + 0x4A) + 1) + *(s16 *) (def + 0x48);
        mdl_particle_spawn(&rec, 3, 0xFF, 0, kind, owner);
        count--;
    }
}

/* P179 */
s32 mdl_particle_spawn(void *, s32, s32, s32, s32, s32);
void vec3_from_angles_byte(s16, s16, f32, void *);

// particle_burst_spawn: P179: spawns def +0 + random [0, def +4] kind-3 particles (mdl_particle_spawn record block,
/* 0x76 bytes) from the burst definition `arg0`: each at a random direction (angles def +0x14 + random [0, +0x16],
 * +0x18 + random [0, +0x1A]) `dist` from the centre def +8, moving that way at def +0x1C + random x +0x20, spin
 * +-def +0x38 about x / z, random rotation 0..360 on all axes, life def +0x2C + random [0, +0x2E], fade
 * def +0x24 + random x +0x28, texture tex[k] for a random k < ntex with size scale[k] x (def +0x30 + random x
 * +0x34). Flags 0x29E8, plus 0x100000 when `flag`; owner / owner arg arg6 / arg7. */
/* was func_15152700 */
void emit_textured_burst(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7) {
    u8 *def = arg0;
    s32 *tex = arg1;
    f32 *scale = arg2;
    struct {
        f32 u00[2];
        f32 sizeX;     /* +0x08 */
        f32 sizeY;     /* +0x0C */
        f32 rot[3];    /* +0x10 */
        f32 u1C[3];
        f32 pos[3];    /* +0x28 */
        f32 vel[3];    /* +0x34 */
        f32 spinX;     /* +0x40 */
        f32 spinY;     /* +0x44 */
        f32 spinZ;     /* +0x48 */
        f32 fade;      /* +0x4C */
        s32 flags;     /* +0x50 */
        s16 life;      /* +0x54 */
        s16 texture;   /* +0x56 */
        u8 u58;
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62[6];
        u8 u68;
        u8 u6A;        /* +0x6A */
        s32 u6C;
        u8 u70;
        s16 u72;
        s16 u74;
    } p;
    s32 n;
    s16 angA;
    s16 angB;
    u32 k;

    p.u00[0] = 1.0f;
    p.u00[1] = 1.0f;
    p.u1C[0] = 1.0f;
    p.u1C[1] = 1.0f;
    p.u1C[2] = 1.0f;
    p.spinY = 0.0f;
    p.flags = (arg5 ? 0x100000 : 0) | 0x29E8;
    p.u58 = 0;
    p.u5C = 0;
    p.u60 = 0xFF;
    p.u61 = 8;
    p.u62[0] = 0;
    p.u62[1] = 0;
    p.u62[2] = 0;
    p.u62[3] = 0;
    p.u62[4] = 0;
    p.u62[5] = 0;
    p.u68 = 2;
    p.u6A = 0;
    p.u6C = 0;
    p.u70 = 0;
    p.u72 = 0xC;
    p.u74 = 0x15;
    n = (u32) random_int() % (u32) (*(s32 *)(def + 4) + 1) + *(s32 *)(def + 0);
    while (n != 0) {
        angA = (u32) random_int() % (u32) (*(s16 *)(def + 0x16) + 1) + *(s16 *)(def + 0x14);
        angB = (u32) random_int() % (u32) (*(s16 *)(def + 0x1A) + 1) + *(s16 *)(def + 0x18);
        p.rot[0] = random_float() * 360.0f;
        p.rot[1] = random_float() * 360.0f;
        p.rot[2] = random_float() * 360.0f;
        vec3_from_angles_byte(angA, angB, random_float() * *(f32 *)(def + 0x20) + *(f32 *)(def + 0x1C), p.vel);
        p.spinX = random_float() * (*(f32 *)(def + 0x38) + *(f32 *)(def + 0x38)) - *(f32 *)(def + 0x38);
        p.spinZ = random_float() * (*(f32 *)(def + 0x38) + *(f32 *)(def + 0x38)) - *(f32 *)(def + 0x38);
        p.fade = random_float() * *(f32 *)(def + 0x28) + *(f32 *)(def + 0x24);
        p.life = (u32) random_int() % (u32) (*(s16 *)(def + 0x2E) + 1) + *(s16 *)(def + 0x2C);
        vec3_from_angles_byte(angA, angB, arg4, p.pos);
        p.pos[0] += *(f32 *)(def + 0x8);
        p.pos[1] += *(f32 *)(def + 0xC);
        p.pos[2] += *(f32 *)(def + 0x10);
        k = (u32) random_int() % (u32) arg3;
        p.texture = tex[k];
        p.sizeY = scale[k] * (*(f32 *)(def + 0x30) + random_float() * *(f32 *)(def + 0x34));
        p.sizeX = p.sizeY;
        mdl_particle_spawn(&p, 3, 0xFF, 0, arg6, arg7);
        n--;
    }
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 anim_model_fx_spawn_moving(s8 *, f32 *, s32, f32, s32, s32, s32, s32, s32);

// base + rand % (extra + 1) (random_int, unsigned remainder)
#define RAND_SPREAD(base, extra) ((u32) random_int() % (u32) ((extra) + 1) + (base))

// particle_burst_from_spec_b: as particle_burst_from_spec (emit_streaks_from_spec) for the second spec layout: base +
// rand % (extra + 1) particles (anim_model_fx_spawn_moving, kind spec +0x3C, size base + rand x range) at the spec's point,
// each with a random life, three random angles (0..360), a random scalar, a random direction (vec3_from_angles_byte),
// three random colour scalars and one more random scalar; flags / colours / the rest are copied once.
// arg1 / arg2 go to anim_model_fx_spawn_moving. The result is unused by its caller (game_eu_1C13E0).
/* was func_15152A90 */
s32 emit_burst_from_spec_b(s32 *arg0, u8 arg1, s32 arg2) {
    typedef struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        s32 pos[3];         /* 0x08 */
        s16 angXBase;       /* 0x14 */
        s16 angXExtra;      /* 0x16 */
        s16 angYBase;       /* 0x18 */
        s16 angYExtra;      /* 0x1A */
        f32 lenBase;        /* 0x1C */
        f32 lenRange;       /* 0x20 */
        f32 u24;            /* 0x24 */
        f32 u28Base;        /* 0x28 */
        f32 u28Range;       /* 0x2C */
        s16 lifeBase;       /* 0x30 */
        s16 lifeExtra;      /* 0x32 */
        s32 u34;            /* 0x34 */
        s32 u38;            /* 0x38 */
        s32 kind;           /* 0x3C */
        f32 sizeBase;       /* 0x40 */
        f32 sizeRange;      /* 0x44 */
        f32 u48Base;        /* 0x48 */
        f32 u48Range;       /* 0x4C */
        f32 colBase[3];     /* 0x50 */
        f32 colRange[3];    /* 0x5C */
        u8 colA[4];         /* 0x68 */
        u8 colB[4];         /* 0x6C */
        u8 flags;           /* 0x70 */
        u8 u71;             /* 0x71 */
        s16 u72;            /* 0x72 */
        s16 u74;            /* 0x74 */
    } BurstSpecB;
    struct {
        f32 ang[3];         /* 0x00 */
        f32 u0C;            /* 0x0C */
        f32 dir[3];         /* 0x10, vec3_from_angles_byte */
        f32 col[3];         /* 0x1C */
        f32 u28;            /* 0x28 */
        f32 u2C;            /* 0x2C */
        u8 u30;             /* 0x30 */
    } part;
    struct {
        u8 flags;           /* 0x00 */
        u8 u01;             /* 0x01 = 0 */
        u8 u02;             /* 0x02 = 1 */
        s8 u03;             /* 0x03 = -1 */
        s8 u04;             /* 0x04 = -1 */
        s16 life;           /* 0x06 */
        s32 u08;            /* 0x08 */
        s32 u0C;            /* 0x0C */
        s32 u10;            /* 0x10 = 0 */
        s32 u14;            /* 0x14 = 0x220405 */
        s32 u18;            /* 0x18 = 0x40200 */
        s32 u1C;            /* 0x1C = 1 */
        s32 u20;            /* 0x20 = 0x38 */
        s32 u24;            /* 0x24 = 0x80 */
        s32 u28;            /* 0x28 = 0x20 */
        u8 u2C;             /* 0x2C = 0 */
        u8 u2D;             /* 0x2D = 8 */
        u8 pad2E[2];
        u8 colA[4];         /* 0x30 */
        u8 colB[4];         /* 0x34 */
        u8 u38;             /* 0x38 = 0 */
        s32 u3C;            /* 0x3C = 0 */
        u8 u40;             /* 0x40 = 0 */
        u8 u41;             /* 0x41 = 2 */
        s32 pos[3];         /* 0x44 */
        u8 pad50[4];
        s16 u54;            /* 0x54 */
        s16 u56;            /* 0x56 */
    } blk;
    BurstSpecB *sp = (BurstSpecB *) arg0;
    u32 count;
    u32 ra;
    u32 rb;
    f32 len;
    f32 size;
    s32 i;

    blk.u38 = 0;
    blk.flags = sp->flags | 2;
    blk.u01 = 0;
    blk.u02 = 1;
    blk.u03 = -1;
    blk.u04 = -1;
    blk.u08 = sp->u34;
    blk.u0C = sp->u38;
    blk.u10 = 0;
    blk.u14 = 0x220405;
    blk.u18 = 0x40200;
    blk.u1C = 1;
    blk.u20 = 0x38;
    blk.u24 = 0x80;
    blk.u28 = 0x20;
    blk.u2C = 0;
    blk.u2D = 8;
    blk.u3C = 0;
    blk.u40 = 0;
    blk.u41 = 2;
    blk.pos[0] = sp->pos[0];
    blk.pos[1] = sp->pos[1];
    blk.pos[2] = sp->pos[2];
    part.u2C = sp->u24;
    for (i = 0; i < 4; i++) {
        blk.colA[i] = sp->colA[i];
        blk.colB[i] = sp->colB[i];
    }
    blk.u54 = sp->u72;
    blk.u56 = sp->u74;
    part.u30 = sp->u71;
    count = RAND_SPREAD(sp->countBase, sp->countExtra);
    for (; count != 0; count--) {
        blk.life = RAND_SPREAD(sp->lifeBase, sp->lifeExtra);
        part.ang[0] = random_float() * 360.0f;
        part.ang[1] = random_float() * 360.0f;
        part.ang[2] = random_float() * 360.0f;
        part.u0C = random_float() * sp->u48Range + sp->u48Base;
        ra = random_int();
        rb = random_int();
        len = random_float() * sp->lenRange + sp->lenBase;
        vec3_from_angles_byte(ra % (u32) (sp->angXExtra + 1) + sp->angXBase, rb % (u32) (sp->angYExtra + 1) + sp->angYBase,
                      len, part.dir);
        for (i = 0; i < 3; i++) {
            part.col[i] = random_float() * sp->colRange[i] + sp->colBase[i];
        }
        part.u28 = random_float() * sp->u28Range + sp->u28Base;
        size = random_float() * sp->sizeRange + sp->sizeBase;
        anim_model_fx_spawn_moving((s8 *) &blk, (f32 *) &part, sp->kind, size, 0, 0, 0, arg1, arg2);
    }
    return 0;
}
#undef RAND_SPREAD

void vec3_from_angles_byte(s16, s16, f32, void *);
void spark_record_spawn(void *, u8, u8);
extern void (*D_8008B000[])(u8 *);
typedef struct { f32 v[3]; } V3_2de4;
typedef struct {
    V3_2de4 v;
    f32 p[3];
    f32 a;
    f32 b;
    u8 c[4];
    s32 n;
    f32 x;
    f32 y;
    f32 z;
} S_2de4;

/* was func_15152DE4 */
void emit_coloured_points(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused slot above the struct (frame size)
    S_2de4 sp;
    s32 n;
    s8 i;

    n = random_int();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    sp.v = *(V3_2de4 *)(arg0 + 8);
    sp.a = *(f32 *)(arg0 + 0x24);
    sp.z = *(f32 *)(arg0 + 0x48);
    while (n != 0) {
        vec3_from_angles_byte(*(s16 *)(arg0 + 0x14) + (random_int() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (random_int() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * random_float(), sp.p);
        sp.b = *(f32 *)(arg0 + 0x28) + *(f32 *)(arg0 + 0x2C) * random_float();
        sp.n = *(s16 *)(arg0 + 0x32) + (random_int() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.x = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x40) * random_float();
        sp.y = *(f32 *)(arg0 + 0x3C) + *(f32 *)(arg0 + 0x44) * random_float();
        i = *(s8 *)(arg0 + 0x30);
        if (i != 0xFFFFFFFF) { // unsigned compare: "!= -1" gives beq v0,fp (permuter found -1U)
            D_8008B000[i](sp.c);
        } else {
            sp.c[0] = 0xFF;
            sp.c[1] = 0xFF;
            sp.c[2] = 0xFF;
            sp.c[3] = 0xFF;
        }
        spark_record_spawn(&sp, arg1, (u8)arg2);
        n--;
    }
}

extern u8 D_800A63C0[][3];

/* was func_1515302C */
void colour_pick_random_fire(u8 *arg0) {
    u8 i = random_int() % 5U;
    u8 *e = D_800A63C0[i];

    arg0[3] = random_int() % 101U + 0x9B;
    arg0[0] = e[0];
    arg0[1] = e[1];
    arg0[2] = e[2];
}

void vec3_from_angles_byte(s16, s16, f32, void *);
void *streak_spawn(s32 *, s32, void *, s32, u8, s32);

// base + rand % (extra + 1) (random_int, unsigned remainder)
#define RAND_SPREAD(base, extra) ((u32) random_int() % (u32) ((extra) + 1) + (base))

// particle_burst_from_spec: spawns base + rand % (extra + 1) particles (streak_spawn) at the spec's point; each
// one gets random life / flag byte, two random scalars, a random direction (vec3_from_angles_byte: two s16 angles and a
// length, each base + random) and two random 4-byte colours; the rest of the 0x3C-byte particle block is copied
// from the spec once. arg1 / arg2 go to streak_spawn (owner byte, extra word). The result is unused by all callers.
/* was func_151530A8 */
s32 emit_streaks_from_spec(s32 *arg0, u8 arg1, s32 arg2) {
    typedef struct {
        s32 countBase;      /* 0x00 */
        s32 countExtra;     /* 0x04 */
        s32 pos[3];         /* 0x08 */
        f32 aBase;          /* 0x14 */
        f32 aRange;         /* 0x18 */
        f32 bBase;          /* 0x1C */
        f32 bRange;         /* 0x20 */
        f32 lenBase;        /* 0x24 */
        f32 lenRange;       /* 0x28 */
        s16 angXBase;       /* 0x2C */
        s16 angXExtra;      /* 0x2E */
        s16 angYBase;       /* 0x30 */
        s16 angYExtra;      /* 0x32 */
        s32 flagBase;       /* 0x34 */
        s32 flagExtra;      /* 0x38 */
        s16 lifeBase;       /* 0x3C */
        s16 lifeExtra;      /* 0x3E */
        u16 u40;            /* 0x40 */
        u8 u42[3];          /* 0x42 */
        u8 colABase[4];     /* 0x45 */
        u8 colAExtra[4];    /* 0x49 */
        u8 colBBase[4];     /* 0x4D */
        u8 colBExtra[4];    /* 0x51 */
        u8 u55Base;         /* 0x55 */
        u8 u55Extra;        /* 0x56 */
        u8 u57[2];          /* 0x57 */
        s32 u5C;            /* 0x5C */
        s32 u60;            /* 0x60 */
        s16 u64;            /* 0x64 */
        s16 u66;            /* 0x66 */
        s16 u68;            /* 0x68 */
        u8 u6A;             /* 0x6A */
        f32 u6C;            /* 0x6C */
        s8 u70;             /* 0x70 */
        s8 u71;             /* 0x71 */
    } BurstSpec;
    struct {
        f32 a;              /* 0x00 */
        f32 dir[3];         /* 0x04, vec3_from_angles_byte */
        f32 b;              /* 0x10 */
        u8 u14[3];          /* 0x14 */
        u8 colA[4];         /* 0x17 */
        u8 colB[4];         /* 0x1B */
        u8 u1F;             /* 0x1F */
        u8 u20[2];          /* 0x20 */
        s32 u24;            /* 0x24 */
        s32 u28;            /* 0x28 */
        s16 u2C;            /* 0x2C */
        s16 u2E;            /* 0x2E */
        s16 u30;            /* 0x30 */
        u8 u32;             /* 0x32 */
        f32 u34;            /* 0x34 */
        s8 u38;             /* 0x38 */
        s8 u39;             /* 0x39 */
    } part;                 /* 0x3C bytes, copied by streak_spawn */
    struct {
        s32 pos[3];         /* 0x00 */
        s16 life;           /* 0x0C */
        u16 u0E;            /* 0x0E */
        s32 u10;            /* 0x10, streak_spawn also sets 10 */
        u8 pad14;
        u8 flag;            /* 0x15 */
    } spawn;
    BurstSpec *sp = (BurstSpec *) arg0;
    u32 count;
    u32 ra;
    u32 rb;
    f32 len;
    s32 i;

    count = RAND_SPREAD(sp->countBase, sp->countExtra);
    spawn.pos[0] = sp->pos[0];
    spawn.pos[1] = sp->pos[1];
    spawn.pos[2] = sp->pos[2];
    spawn.u10 = 10;
    spawn.u0E = sp->u40;
    part.u14[0] = sp->u42[0];
    part.u14[1] = sp->u42[1];
    part.u14[2] = sp->u42[2];
    part.u20[0] = sp->u57[0];
    part.u20[1] = sp->u57[1];
    part.u24 = sp->u5C;
    part.u28 = sp->u60;
    part.u2C = sp->u64;
    part.u2E = sp->u66;
    part.u38 = sp->u70;
    part.u39 = sp->u71;
    part.u30 = sp->u68;
    part.u32 = sp->u6A;
    part.u34 = sp->u6C;
    for (; count != 0; count--) {
        spawn.flag = RAND_SPREAD(sp->flagBase, sp->flagExtra);
        spawn.life = RAND_SPREAD(sp->lifeBase, sp->lifeExtra);
        part.a = random_float() * sp->aRange + sp->aBase;
        part.b = random_float() * sp->bRange + sp->bBase;
        ra = random_int();
        rb = random_int();
        len = random_float() * sp->lenRange + sp->lenBase;
        vec3_from_angles_byte(ra % (u32) (sp->angXExtra + 1) + sp->angXBase, rb % (u32) (sp->angYExtra + 1) + sp->angYBase,
                      len, part.dir);
        for (i = 0; i < 4; i++) {
            part.colA[i] = RAND_SPREAD(sp->colABase[i], sp->colAExtra[i]);
        }
        for (i = 0; i < 4; i++) {
            part.colB[i] = RAND_SPREAD(sp->colBBase[i], sp->colBExtra[i]);
        }
        part.u1F = RAND_SPREAD(sp->u55Base, sp->u55Extra);
        streak_spawn(spawn.pos, 0, &part, 0, arg1, arg2);
    }
    return 0;
}
#undef RAND_SPREAD

u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

/* was func_151534E0 */
void emit_sparks_by_angles_b(u8 *arg0, s32 arg1) {
    struct {
        s32 uA8;
        s32 uAC;
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        u8 padC6[0x6];
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        u8 padE0[0x4];
        u8 uE4;
        u8 uE5;
        u8 uE6;
        u8 uE7;
        u8 padE8[0x4];
        s32 uEC;
        u8 padF0[0x8];
        s16 uF8;
        s16 uFA;
        s32 uFC;
        u8 pad100[0x1];
        s8 u101;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;

    sp.uFC = 1;
    sp.uFA = 1;
    sp.uE5 = (*(u8 *)((u8 *)arg0 + 0x38));
    sp.uE6 = (*(u8 *)((u8 *)arg0 + 0x54));
    sp.uE4 = (*(u8 *)((u8 *)arg0 + 0x39));
    sp.uE7 = (*(u8 *)((u8 *)arg0 + 0x55));
    (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uA8 = 0;
    sp.uAC = 1;
    sp.uB0 = 0x160600;
    sp.uB4 = 3;
    sp.uB8 = 0x10;
    sp.uBC = 0x80;
    sp.uC0 = 0x20;
    sp.uC4 = 0;
    sp.uC5 = 9;
    var_s3 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x26)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x24));
    if (var_s3 != 0) {
        do {
            temp_s1 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x28));
            temp_s2 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x2C));
            temp_f22 = angle_byte_cos(temp_s2 & 0xFF);
            temp_f24 = angle_byte_cos((temp_s2 - 0x40) & 0xFF);
            temp_f26 = angle_byte_cos(temp_s1 & 0xFF);
            temp_f28 = angle_byte_cos((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x20))) + (*(f32 *)((u8 *)arg0 + 0x1C));
            sp.u101 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x32)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x30));
            sp.uF8 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x36)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x34));
            sp.uCC = (random_float() * (*(f32 *)((u8 *)arg0 + 0x10))) + (*(f32 *)((u8 *)arg0 + 0xC));
            temp_f2 = temp_f20 * temp_f22;
            sp.uDC = (random_float() * (*(f32 *)((u8 *)arg0 + 0x18))) + (*(f32 *)((u8 *)arg0 + 0x14));
            sp.uD0 = temp_f2 * temp_f28;
            sp.uD4 = -temp_f20 * temp_f24;
            sp.uD8 = temp_f2 * temp_f26;
            trail_spawn(&sp.uEC, &sp.uCC, 0, (*(s32 *)((u8 *)arg0 + 0x3C)), (*(s32 *)((u8 *)arg0 + 0x40)), (*(s32 *)((u8 *)arg0 + 0x44)), (*(s32 *)((u8 *)arg0 + 0x48)), (*(s32 *)((u8 *)arg0 + 0x4C)), (*(s32 *)((u8 *)arg0 + 0x50)), 0, 0, &sp.uA8, 0, arg1 & 0xFF, 1);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
s32 node_spawn_sprite(s32 *, s32, s32, s32, s32, s32);

/* was func_15153808 */
void emit_sprite_nodes_by_angles(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u88;
        u8 pad8C[0x8];
        s16 u94;
        s16 u96;
        s16 u98;
        s16 u9A;
        s16 u9C;
        s16 u9E;
        s16 uA0;
        u8 padA2[0x2];
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s8 uB2;
        u8 padB3[0x1];
        u8 uB4;
        u8 uB5;
        u8 uB6;
        u8 uB7;
        s8 uB8;
        s8 uB9;
        s8 uBA;
        u8 padBB[0x1];
        s16 uBC;
    } sp;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;

    sp.u98 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0));
    sp.u9A = (s16) (s32) (*(f32 *)((u8 *)arg0 + 4));
    sp.u9C = (s16) (s32) (*(f32 *)((u8 *)arg0 + 8));
    sp.uA4 = (s8) (s32) ((*(f32 *)((u8 *)arg0 + 0)) * 256.0f);
    sp.uA5 = (s8) (s32) ((*(f32 *)((u8 *)arg0 + 4)) * 256.0f);
    sp.uA6 = (s8) (s32) ((*(f32 *)((u8 *)arg0 + 8)) * 256.0f);
    sp.uB4 = (*(u8 *)((u8 *)arg0 + 0x3C));
    sp.uB5 = (*(u8 *)((u8 *)arg0 + 0x3C));
    sp.uB8 = 0;
    sp.uB9 = 0;
    sp.uBA = 0;
    sp.uB6 = (*(u8 *)((u8 *)arg0 + 0x3C));
    sp.uB7 = (*(u8 *)((u8 *)arg0 + 0x3D));
    sp.uA7 = (*(s8 *)((u8 *)arg0 + 0x28));
    sp.u94 = 0;
    sp.uBC = (s16) (*(u8 *)((u8 *)arg0 + 0x29));
    sp.u96 = (*(s16 *)((u8 *)arg0 + 0x2E));
    sp.u88 = (*(s32 *)((u8 *)arg0 + 0x38));
    var_s3 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0xE)) + 1)) + (*(s16 *)((u8 *)arg0 + 0xC));
    if (var_s3 != 0) {
        do {
            temp_s1 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x12)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x10));
            temp_s2 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x16)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x14));
            temp_f28 = angle_byte_cos(temp_s2 & 0xFF);
            temp_f22 = angle_byte_cos((temp_s2 - 0x40) & 0xFF);
            temp_f24 = angle_byte_cos(temp_s1 & 0xFF);
            temp_f26 = angle_byte_cos((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x1C))) + (*(f32 *)((u8 *)arg0 + 0x18));
            temp_f0 = temp_f20 * temp_f28;
            sp.uB0 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x22)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x20));
            sp.u9E = (s16) (s32) (temp_f0 * temp_f26);
            sp.uA8 = (s16) (s32) (-temp_f20 * temp_f22);
            sp.uA0 = (s16) (s32) (temp_f0 * temp_f24);
            sp.uAA = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x26)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x24));
            sp.uB2 = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2C)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x2A));
            sp.uAC = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x32)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x30));
            sp.uAE = (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x36)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x34));
            node_spawn_sprite(&sp.u88, 0, 0, -1, arg1 & 0xFF, arg2);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
/* P150 (hand C, replaces the batch m2c body) */
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, f32 *, s32);

// particle template handed to particle_spawn_ex (0x67 bytes used)
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 u08;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[7];
    /* 0x1B */ s8 u1B;
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 u1D;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 u58;
    /* 0x5C */ u8 pad5C[4];
    /* 0x60 */ u8 u60;
    /* 0x61 */ u8 u61;
    /* 0x62 */ s8 u62;
    /* 0x63 */ s8 u63;
    /* 0x64 */ u8 pad64[2];
    /* 0x66 */ u8 u66;
} BurstParticle;

// particle_burst_spawn: spawns a burst of particles from a request (e.g. the pickup flash of pickup_burst_spawn):
// count = +0 + random [0, +2]; each particle gets the request's fixed fields, a random life (+0x10 / +0x12),
// value +0x14 / +0x18, size (+0x30 + random * +0x34), byte +0x23 / +0x24 and +0x54 + random * +0x58, and a
// velocity of speed +0x4C + random * +0x50 along yaw +0x44 / +0x48 and pitch +0x46 / +0x4A (256 steps per
// turn). It is created through particle_spawn_ex(template, +0x64, 0, 4, owner, ownerArg) and its +0xA8 gets +0x68.
// tag = template byte 0x66.
/* was func_15153BA4 */
void emit_particle_burst_req(u8 *req, s32 tag, s32 owner, s32 ownerArg) {
    BurstParticle p;
    f32 spin;
    f32 speed;
    f32 sinPitch;
    f32 cosPitch;
    f32 sinYaw;
    f32 cosYaw;
    f32 size;
    f32 horiz;
    s16 yaw;
    s16 pitch;
    s32 part;
    s32 count;

    count = (u32) random_int() % (u32) (*(s16 *)(req + 0x2) + 1) + *(s16 *)(req + 0x0);
    spin = *(f32 *)(req + 0x68);
    p.u0 = *(s32 *)(req + 0x8);
    p.u4 = *(s32 *)(req + 0xC);
    p.u08 = *(u16 *)(req + 0x6);
    p.uC = 0;
    p.colour[0] = req[0x1C];
    p.colour[1] = req[0x1D];
    p.colour[2] = req[0x1E];
    p.colour[3] = req[0x1F];
    p.colour[4] = req[0x20];
    p.colour[5] = req[0x21];
    p.colour[6] = req[0x22];
    p.u1C = req[0x25];
    p.u1D = req[0x4];
    p.u1E = *(s16 *)(req + 0x26);
    p.u20 = *(s16 *)(req + 0x28);
    p.u22 = *(s16 *)(req + 0x2A);
    p.u24 = *(f32 *)(req + 0x2C);
    p.pos[0] = *(f32 *)(req + 0x38);
    p.pos[1] = *(f32 *)(req + 0x3C);
    p.pos[2] = *(f32 *)(req + 0x40);
    p.u58 = *(s32 *)(req + 0x5C);
    p.u60 = req[0x62];
    p.u61 = req[0x63];
    p.u62 = req[0x60];
    p.u63 = req[0x61];
    p.u66 = tag;

    for (; count != 0; count--) {
        yaw = (u32) random_int() % (u32) (*(s16 *)(req + 0x48) + 1) + *(s16 *)(req + 0x44);
        pitch = (u32) random_int() % (u32) (*(s16 *)(req + 0x4A) + 1) + *(s16 *)(req + 0x46);
        sinPitch = angle_byte_cos(pitch);
        cosPitch = angle_byte_cos(pitch - 0x40);
        sinYaw = angle_byte_cos(yaw);
        cosYaw = angle_byte_cos(yaw - 0x40);
        speed = random_float() * *(f32 *)(req + 0x50) + *(f32 *)(req + 0x4C);
        p.life = (u32) random_int() % (u32) (*(s16 *)(req + 0x12) + 1) + *(s16 *)(req + 0x10);
        p.u10 = (u32) random_int() % (u32) (*(s32 *)(req + 0x18) + 1) + *(s32 *)(req + 0x14);
        size = random_float() * *(f32 *)(req + 0x34) + *(f32 *)(req + 0x30);
        p.size[1] = size;
        p.size[0] = size;
        horiz = speed * sinPitch;
        p.vel[0] = horiz * cosYaw;
        p.vel[1] = -speed * cosPitch;
        p.vel[2] = horiz * sinYaw;
        p.u54 = random_float() * *(f32 *)(req + 0x58) + *(f32 *)(req + 0x54);
        p.u1B = (u32) random_int() % (u32) (req[0x24] + 1) + req[0x23];
        part = particle_spawn_ex((s32) &p, req[0x64], 0, 4, owner, ownerArg);
        if (part != 0) {
            memcpy(part + 0xA8, &spin, 4);
        }
    }
}
typedef struct { f32 v[3]; } V3_3f24;
typedef struct {
    V3_3f24 pos;
    f32 vel[3];
    f32 a;
    f32 b;
    u8 c[9];
    s16 d;
    u16 e;
    f32 f;
    s8 g;
    s16 h;
    s16 i;
} S_3f24;
s32 line_fx_spawn(S_3f24 *, u8, s32, u8, s32);

/* was func_15153F24 */
void emit_line_sparks_by_angles(u8 *arg0, u8 arg1) {
    S_3f24 sp;
    s32 n;
    s16 a;
    s16 b;
    f32 sb;
    f32 cb;
    f32 sa;
    f32 ca;

    n = *(s16 *)(arg0 + 0) + (random_int() % (u32)(*(s16 *)(arg0 + 2) + 1));
    sp.pos = *(V3_3f24 *)(arg0 + 4);
    sp.c[0] = *(u8 *)(arg0 + 0x28);
    sp.c[1] = *(u8 *)(arg0 + 0x29);
    sp.c[2] = *(u8 *)(arg0 + 0x2A);
    sp.c[3] = *(u8 *)(arg0 + 0x2B);
    sp.c[4] = *(u8 *)(arg0 + 0x2C);
    sp.c[5] = *(u8 *)(arg0 + 0x2D);
    sp.c[6] = *(u8 *)(arg0 + 0x2E);
    sp.c[7] = *(u8 *)(arg0 + 0x2F);
    sp.c[8] = *(u8 *)(arg0 + 0x30);
    sp.e = *(u16 *)(arg0 + 0x36);
    sp.h = *(s16 *)(arg0 + 0x42);
    sp.i = *(s16 *)(arg0 + 0x44);
    while (n != 0) {
        a = *(s16 *)(arg0 + 0x10) + (random_int() % (u32)(*(s16 *)(arg0 + 0x14) + 1));
        b = *(s16 *)(arg0 + 0x12) + (random_int() % (u32)(*(s16 *)(arg0 + 0x16) + 1));
        sb = angle_byte_cos(b);
        cb = angle_byte_cos(b - 0x40);
        sa = angle_byte_cos(a);
        ca = angle_byte_cos(a - 0x40);
        sp.vel[0] = 10.0f * sb * ca;
        sp.vel[1] = -10.0f * cb;
        sp.vel[2] = 10.0f * sb * sa;
        sp.a = *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * random_float();
        sp.b = *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * random_float();
        sp.d = *(s16 *)(arg0 + 0x32) + (random_int() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.f = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x3C) * random_float();
        sp.g = *(u8 *)(arg0 + 0x40) + (random_int() % (u32)(*(u8 *)(arg0 + 0x41) + 1));
        line_fx_spawn(&sp, *(u8 *)(arg0 + 0x46), 0, arg1, 0);
        n--;
    }
}

void emit_sparks_on_disc(u8 *, s32, s32, u8, s32);

/* was func_151541F4 */
void emit_sparks_on_surface_disc(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    emit_disc_from_surface(arg0, sp24);
    emit_sparks_on_disc(sp24, arg1, arg2, arg3, arg4);
}

s32 impact_spark_spawn(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

/* was func_1515423C */
void emit_sparks_on_disc(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    f32 spA8[3];

    if (emit_disc_prepare(arg0) != 0) {
        n = random_int();
        n = *(s16 *)((u8 *)arg1 + 0x24) + (n % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
        while (n != 0) {
            emit_disc_random_point((f32 *)arg0, *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * random_float(), spA8);
            impact_spark_spawn((struct17 *)arg1, (s32 *)spA8,
                *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * random_float(),
                *(s16 *)((u8 *)arg1 + 0x2C) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
                *(s16 *)((u8 *)arg1 + 0x30) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
                *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * random_float(),
                *(s16 *)((u8 *)arg1 + 0x28) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
                random_float() < *(f32 *)((u8 *)arg1 + 0x38),
                1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
                *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
            n--;
        }
    }
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 impact_spark_spawn(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

/* was func_15154488 */
void emit_sparks_in_angle_range(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    s32 spA8[3];

    n = *(s16 *)((u8 *)arg1 + 0x24) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
    while (n != 0) {
        vec3_from_angles_byte(arg0->unk0 + (random_int() % (u32)(arg0->unk2 + 1)),
            arg0->unk4 + (random_int() % (u32)(arg0->unk6 + 1)),
            *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * random_float(), spA8);
        impact_spark_spawn(arg1, spA8,
            *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * random_float(),
            *(s16 *)((u8 *)arg1 + 0x2C) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
            *(s16 *)((u8 *)arg1 + 0x30) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
            *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * random_float(),
            *(s16 *)((u8 *)arg1 + 0x28) + (random_int() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
            random_float() < *(f32 *)((u8 *)arg1 + 0x38),
            1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
            *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
        n--;
    }
}

/* P159 */
s32 mdl_particle_spawn(void *, s32, s32, s32, s32, s32);
// spark_shower_spawn: spawns a spark particle (mdl_particle_spawn, 0x18 extra bytes at +0x170) at pos lasting `time`
// (> 0, else nothing) with brightness `bright` (also its life byte, IDO f32 -> u8 conversion); `flat` != 0 makes it
// a flat spark turning around y (yaw / spin from it), else it gets random angles and a random x / z drift
// (+-4.256). The extra bytes keep time / size / brightness, the fade rate bright / time^2 and the flat flag.
// Returns the particle or 0.
/* was func_15154728 */
s32 spark_shower_spawn(f32 *pos, f32 time, f32 size, f32 bright, f32 flat, u8 arg5, s32 arg6) {
    struct {
        /* extra data copied to particle +0x170 (0x18 bytes) */
        f32 age;
        f32 time;
        f32 size;
        f32 bright;
        f32 fade;
        u8 isFlat;
        u8 pad3D[3];
        /* spawn block for mdl_particle_spawn */
        f32 scaleX;
        f32 scaleY;
        f32 u48;
        f32 flat;
        f32 rot[3];
        f32 scale[3];
        f32 pos[3];
        f32 u74[3];
        f32 vel[3];
        f32 u8C;
        s32 flags;
        s16 u94;
        s16 tex;
        u8 u98;
        u8 pad99[3];
        s32 u9C;
        u8 life;
        u8 uA1;
        u8 uA2;
        u8 uA3;
        u8 uA4;
        u8 uA5;
        u8 uA6;
        u8 uA7;
        u8 uA8;
        u8 padA9;
        u8 uAA;
        u8 padAB;
        s32 uAC;
        u8 uB0;
        u8 padB1;
        s16 uB2;
        s16 uB4;
    } sp;
    s32 p;

    if (time <= 0.0f) {
        return 0;
    }
    sp.age = 0.0f;
    sp.time = time;
    sp.bright = bright;
    sp.size = size;
    sp.fade = bright / (time * time);
    sp.isFlat = (flat != 0.0f) ? 1 : 0;
    sp.u48 = 0.0f;
    sp.flat = flat;
    sp.scaleX = 1.0f;
    sp.scaleY = 1.0f;
    sp.rot[0] = (flat != 0.0f) ? 0.0f : random_float() * 360.0f;
    sp.rot[1] = random_float() * 360.0f;
    sp.rot[2] = (flat != 0.0f) ? 0.0f : random_float() * 360.0f;
    sp.scale[0] = 1.0f;
    sp.scale[1] = 1.0f;
    sp.scale[2] = 1.0f;
    ((s32 *)sp.pos)[0] = ((s32 *)pos)[0];
    ((s32 *)sp.pos)[1] = ((s32 *)pos)[1];
    ((s32 *)sp.pos)[2] = ((s32 *)pos)[2];
    sp.u74[0] = 0.0f;
    sp.u74[1] = 0.0f;
    sp.u74[2] = 0.0f;
    sp.vel[0] = (flat != 0.0f) ? 0.0f : random_float() * 8.512f + -4.256f;
    sp.vel[1] = (flat != 0.0f) ? random_float() * 8.512f + -4.256f : 0.0f;
    sp.vel[2] = (flat != 0.0f) ? 0.0f : random_float() * 8.512f + -4.256f;
    sp.u8C = 0.0f;
    sp.flags = 0x100140;
    sp.tex = 0x54;
    sp.u98 = 0;
    sp.u9C = 0;
    /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
    sp.life = (bright <= -1.0f) ? 0xFF : (u8)(u32)bright;
    sp.uA1 = 0xF;
    sp.uA2 = 0;
    sp.uA3 = 0;
    sp.uA4 = 0;
    sp.uA5 = 0;
    sp.uA6 = 0;
    sp.uA7 = 0;
    sp.uA8 = 2;
    sp.uAA = 0;
    sp.uAC = 0;
    sp.uB0 = 0;
    sp.uB2 = 1;
    sp.uB4 = 0xFF;
    sp.u94 = 300;
    p = mdl_particle_spawn(&sp.scaleX, 0, 0, 0x18, arg5, arg6);
    if (p != 0) {
        memcpy((u8 *)p + 0x170, &sp, 0x18);
    }
    return p;
}

/* was func_15154A9C */
s32 spark_shower_update(u8 *arg0) {
    f32 *p;
    f32 s;
    f32 t;
    p = (f32 *)(arg0 + 0x170);
    s = *(f32 *)(arg0 + 0x178) * sqrtf(p[0]);
    *(f32 *)(arg0 + 0x18) = s;
    if (!(*(u8 *)(arg0 + 0x184) & 1)) {
        *(f32 *)(arg0 + 0x1C) = s;
    }
    do { t = p[0]; *(s8 *)(arg0 + 0x70) = (s8)(u32)(p[3] - p[4] * t * t); } while (0); // fakematch: same-line do-while(0) (permuter) keeps &D_800BE9A4 in v1 from the start
    p[0] += D_800BE9A4;
    if (p[1] < p[0]) {
        return 0;
    }
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

void vec3_from_angles_byte(s16, s16, f32, void *);
void debris_sprite_spawn(s32, void *, f32, f32, s32, s32, f32, s32, s32, u8, s32);
/* was func_15154BF4 */
void emit_rings_random_yaw(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp80[4];
    s32 n;
    n = *(s16 *)(arg0 + 0) + (random_int() % (u32)(*(s16 *)(arg0 + 2) + 1));
    if (n > 0) {
        do {
            vec3_from_angles_byte(random_int() & 0xFF, *(s16 *)(arg0 + 0xA) + (random_int() % (u32)(*(s16 *)(arg0 + 0xE) + 1)),
                *(f32 *)(arg0 + 0x10) + *(f32 *)(arg0 + 0x14) * random_float(), sp80);
            debris_sprite_spawn(*(s32 *)(arg0 + 4), sp80, *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * random_float(),
                *(f32 *)(arg0 + 0x20),
                *(u8 *)(arg0 + 0x24) + (random_int() % (u32)(*(u8 *)(arg0 + 0x25) + 1)),
                *(s16 *)(arg0 + 0x26) + (random_int() % (u32)(*(s16 *)(arg0 + 0x28) + 1)),
                *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * random_float(),
                random_float() < *(f32 *)(arg0 + 0x34), *(s32 *)(arg0 + 0x38), arg1, arg2);
            n--;
        } while (n > 0);
    }
}

typedef struct { f32 x, y, z; } V3;

/* was func_15154DF4 */
s32 glow_pulse_spawn(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, s32 arg5)
{
  s32 obj;
  struct 
  {
    f32 u2C[15];
    s32 u68;
    u8 pad6C[0x8];
    f32 u74;
    f32 u78;
    f32 u7C;
    f32 u80;
    f32 u84;
    f32 u88;
    f32 u8C;
    s32 u90;
    s16 u94;
    s16 u96;
    s8 u98;
    u8 pad99[0x3];
    s32 u9C;
    u8 uA0;
    s8 uA1;
    s8 uA2;
    s8 uA3;
    s8 uA4;
    s8 uA5;
    s8 uA6;
    s8 uA7;
    s8 uA8;
    u8 padA9[0x1];
    s8 uAA;
    u8 padAB[0x1];
    s32 uAC;
    s8 uB0;
    u8 padB1[0x1];
    s16 uB2;
    s16 uB4;
    u8 padB6[0x6];
  } sp;
  f32 temp_f0;
  if (arg1 <= 0.0f)
  {
    return 0;
  }
  sp.u2C[0] = arg1;
  sp.u2C[1] = arg2;
  sp.u2C[3] = 0.0f;
  sp.u2C[7] = 0.0f;
  sp.u2C[8] = 0.0f;
  sp.u2C[5] = 1.0f;
  sp.u2C[6] = 1.0f;
  sp.u2C[2] = arg3;
  sp.u2C[4] = 3.1415927f / arg1;
  sp.u2C[9] = random_float() * 360.0f;
  sp.u2C[10] = random_float() * 360.0f;
  temp_f0 = random_float();
  sp.u2C[12] = 1.0f;
  sp.u2C[13] = 1.0f;
  sp.u2C[14] = 1.0f;
  sp.u2C[11] = temp_f0 * 360.0f;
  *((V3 *) (&sp.u68)) = *((V3 *) arg0);
  sp.u74 = 0.0f;
  sp.u78 = 0.0f;
  sp.u7C = 0.0f;
  temp_f0 = random_float();
  sp.u84 = 0.0f;
  sp.u80 = (temp_f0 * 26.296001f) + (-13.148001f);
  sp.u88 = (random_float() * 26.296001f) + (-13.148001f);
  sp.u8C = 0.0f;
  sp.u90 = 0x140;
  sp.u96 = 0x55;
  sp.u98 = 0;
  sp.u9C = 0;
  sp.uA0 = 0xFF;
  sp.uA1 = 0x12;
  sp.uA2 = 0;
  sp.uA3 = 0;
  sp.uA4 = 0;
  sp.uA5 = 0;
  sp.uA6 = 0;
  sp.uA7 = 0;
  sp.uA8 = 2;
  sp.uAA = 0;
  sp.uAC = 0;
  sp.uB0 = 0;
  sp.uB2 = 1;
  sp.uB4 = 0xFF;
  sp.u94 = 0x12C;
  obj = mdl_particle_spawn((u8 *) (&sp.u2C[5]), 0, 0, 0x14, arg4, arg5);
  if (obj != 0)
  {
    memcpy(obj + 0x170, &sp, 0x14);
  }
  return obj;
}

/* was func_15154FF8 */
s32 glow_pulse_update(u8 *arg0) {
    f32 *p;
    f32 s;

    p = (f32 *)(arg0 + 0x170);
    s = sinf(p[3]);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x1C) = p[1] * s;
    *(s8 *)(arg0 + 0x70) = (s8)(u32)(((u32)p[2] & 0xFF) * s);
    p[0] -= D_800BE9A4;
    if (p[0] <= 0.0f) {
        return 0;
    }
    p[3] += p[4] * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
