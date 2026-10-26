#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#ifdef NON_MATCHING
/* Impact effect kinds read by impact_effect_spawn (its .s owns this rodata; the NM link drops it). */
typedef struct {
    u16 sparkKind; /* +0 spark record kind for sprite_vtx_quads_init, 0 = none */
    u16 debris;    /* +2 debris effect id (func_151722BC / func_15172474), 0 = none, 0x13 = special burst */
    u8 smokePct;   /* +4 chance (percent) of a smoke puff when size != 0 */
    u8 subEffect;  /* +5 impact_dust_spawn effect, 0 = none */
    u8 countBase;  /* +6 debris count = base + rand % range + 1 */
    u8 countRange; /* +7 */
} ImpactKind;
static const ImpactKind D_800A1440[20] = {
    { 0x00, 0x00, 0x32, 0x00, 0x11, 0x28 }, { 0x3A, 0x3B, 0x02, 0x0A, 0x1E, 0x0C },
    { 0x3E, 0x00, 0x00, 0x0A, 0x3C, 0x14 }, { 0x00, 0x3F, 0x32, 0x04, 0x1E, 0x0C },
    { 0x00, 0x3F, 0x32, 0x04, 0x1E, 0x0C }, { 0x00, 0x3F, 0x32, 0x05, 0x11, 0x28 },
    { 0x00, 0x3F, 0x32, 0x09, 0x1E, 0x0C }, { 0x37, 0x00, 0x02, 0x00, 0x1E, 0x0C },
    { 0x3E, 0x13, 0x00, 0x08, 0x3C, 0x14 }, { 0x00, 0x3F, 0x64, 0x00, 0x14, 0x06 },
    { 0x3A, 0x3B, 0x02, 0x0A, 0x1E, 0x0C }, { 0x3A, 0x3B, 0x02, 0x0A, 0x1E, 0x0C },
    { 0x3A, 0x00, 0x00, 0x0A, 0x1E, 0x0C }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x37, 0x00, 0x00, 0x11, 0x1E, 0x0C }, { 0x37, 0x38, 0x01, 0x11, 0x1E, 0x0C },
    { 0x37, 0x38, 0x01, 0x11, 0x1E, 0x0C }, { 0x37, 0x38, 0x01, 0x11, 0x1E, 0x0C },
    { 0x37, 0x38, 0x00, 0x11, 0x1E, 0x0C }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};
static const u16 D_800A14E0[3][2] = { { 0x80, 0x60 }, { 0x100, 0x100 }, { 0x180, 0x180 } }; /* spark size per impact size */
static const f32 D_800A14EC[3] = { 0.33f, 1.0f, 2.0f }; /* 0x3EA8F5C3, 0x3F800000, 0x40000000: debris count scale */
static const f32 D_800A14F8[1] = { -10000.0f }; /* 0xC61C4000 (array: IDO puts scalar float statics in .data) */
#endif

#ifdef NON_MATCHING
typedef struct {
    u8 pad0[0x84];
    u16 u84, u86;    /* size (D_800A14E0) */
    u8 pad88[4];
    s16 x, y, z;     /* +0x8C */
    s16 u92, u94;
    u8 pad96[2];
    s16 u98;
    u8 pad9A[6];
    u8 kind;         /* +0xA0 */
    u8 padA1;
    u8 uA2;
    u8 padA3;
    u8 uA4;
    u8 padA5[3];
} ImpactSpark;
s32 func_151EFDD0(void);
s32 func_151722BC(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);
void func_15172474(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC);
void impact_dust_spawn(f32, f32, f32, s32, s32, s32 *, s32);
s32 sprite_vtx_quads_init(void *, s32, s32, s32, s32);
void *node_spawn_vtx_sprite(void *, u8, s32);
extern u8 D_800D9D83[]; /* byte +3 of the 28-byte records at D_800D9D80 */

// impact_effect_spawn: spawns the effects of an impact of kind `kind` (index into D_800A1440, flag 0x8000 passed on
// to the sub-effect) at (x, y, z). size (0..2) scales the debris count (D_800A14EC) and picks the spark size
// (D_800A14E0); size 1 gives the debris a wider spread (0x78 instead of 0x1E). Debris: the special burst for id 0x13,
// debris placed on the triangle `tri` (three vertex pointers) when there is one, else a free burst. Then the
// sub-effect (impact_dust_spawn), a random smoke puff 20 units up (not for size 0), which also sets byte +3 of record
// `slot` in D_800D9D80 to 100 (0 when no puff; slot 0xFF = none), and a spark record. Callers ignore v0 (v0use).
/* was func_150E4AD0 */
s32 impact_effect_spawn(f32 x, f32 y, f32 z, s32 size, s32 kind, s32 *tri, s32 slot) {
    const ImpactKind *k;
    s32 flag = 0;
    s32 spread = 0x78;
    s32 count;
    f32 pos[3];
    ImpactSpark spark;

    if (kind & 0x8000) {
        kind ^= 0x8000;
        flag = 0x8000;
    }
    k = &D_800A1440[kind];
    if (k->debris != 0) {
        count = (func_151EFDD0() % k->countRange) + k->countBase + 1;
        if (size != 1) {
            spread = 0x1E;
        }
        count = D_800A14EC[size] * count;
        if (k->debris == 0x13) {
            func_151722BC(x, y, z, 0x1E, 0, 0x13, 0.0f, 0, count, 0xF, 0x55, 0, 0xFF, 0);
        } else if (tri != NULL) {
            func_15172474(x, y, z, (s32) tri, spread, 0xB5AD, k->debris, count, 0, 0, 0, 0xFF, 0);
        } else {
            func_151722BC(x, y, z, (s16) spread, 0xB5AD, k->debris, 0.0f, 0, count, 0, 0, 0, 0xFF, 0);
        }
    }
    if (k->subEffect != 0) {
        impact_dust_spawn(x, y, z, k->subEffect | flag, size, tri, slot);
    }
    if (size != 0 && (func_151EFDD0() % 100) < k->smokePct) {
        pos[0] = x;
        pos[1] = y + 20.0f;
        pos[2] = z;
        func_151C384C(pos, 0xFF, 1);
        if (slot != 0xFF) {
            D_800D9D83[slot * 28] = 100;
        }
    } else if (slot != 0xFF) {
        D_800D9D83[slot * 28] = 0;
    }
    if (k->sparkKind != 0) {
        bzero(&spark, sizeof(spark));
        spark.u84 = D_800A14E0[size][0];
        spark.u86 = D_800A14E0[size][1];
        spark.x = x;
        spark.y = y;
        spark.z = z;
        spark.uA2 = 0xD;
        spark.kind = k->sparkKind;
        spark.u98 = 0x2A00;
        spark.u92 = 1;
        spark.u94 = 1;
        spark.uA4 = 0xFF;
        sprite_vtx_quads_init(&spark, 0xB4, 0xB4, 0xB4, 0xFF);
        node_spawn_vtx_sprite(&spark, 0xFF, 0);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/impact_effect_spawn.s")
#endif

#ifdef NON_MATCHING
void collision_select_area(s32);
s32 func_150A49D0(s32 count, s32 *idList, s32 force);
s32 func_150A48C0(s32, s32, s32, s32 *);
s32 floor_flags_surface_type(s32);
extern struct {
    s32 height;  /* floor height * 256 */
    s32 *tri;    /* collision triangle (12-byte records at D_800DC26C) */
    u8 pad8[8];
} D_800D3720[]; /* hits of the last func_150A48C0 probe */
extern s32 D_800DC26C;

// object_impact_effect: impact effect for the world object `obj` (0xA0-byte records at D_800DBEF4, count
// D_800DC320). Probes the object's floor (func_150A48C0, only this object's id in the list) at its x / z (+0x10 /
// +0x14) jittered by up to +-(+0x50) units, at most 5 tries. Takes the highest hit: its height (/ 256) becomes the
// effect y, and its triangle, moved into world space with the object's matrix (world_record_build_matrix; vertex offsets +
// the object's vertex base for the current frame buffer D_800BE9C0), carries the debris. The effect kind comes from
// the triangle's material (floor_flags_surface_type of the object's per-triangle table +0x44 indexed from base +0x58, or +0x40
// for all). Nothing when the object index is out of range or every probe missed. Callers ignore v0.
/* was func_150E4EA8 */
s32 impact_effect_at_world_object(u8 *obj) {
    s32 idx = ((u8 *) obj - (u8 *) D_800DBEF4) / 0xA0;
    u16 id;
    s32 tries = 5;
    s32 found;
    s32 x, z, n, i;
    s32 best;
    s32 *tri = NULL; /* the asm leaves it uninitialised when no hit is above -0x800000 */
    f32 height = D_800A14F8[0];
    s32 material;
    f32 mtx[4][4];
    f32 ox, oy, oz;
    s16 verts[3][8];
    s32 world[3];

    if (idx >= D_800DC320 || idx < 0) {
        return 0;
    }
    id = idx;
    collision_select_area(2);
    func_150A49D0(1, (s32 *) &id, 0);
    do {
        x = *(s16 *) (obj + 0x10);
        z = *(s16 *) (obj + 0x14);
        if (*(u16 *) (obj + 0x50) != 0) {
            n = *(u16 *) (obj + 0x50);
            x = x + (func_151EFDD0() % n) * 2 - n;
            n = *(u16 *) (obj + 0x50);
            z = z + (func_151EFDD0() % n) * 2 - n;
        }
        found = func_150A48C0(x, z, 1, (s32 *) &id);
        if (found != 0) {
            best = -0x800000;
            for (i = found - 1; i >= 0; i--) {
                if (best < D_800D3720[i].height) {
                    best = D_800D3720[i].height;
                    tri = D_800D3720[i].tri;
                    height = best * 0.00390625f;
                }
            }
            tries = 0;
            found = 1;
        } else {
            tries--;
        }
    } while (tries != 0);
    if (!found) {
        return 0;
    }
    if (*(s32 **) (obj + 0x44) != NULL) {
        material = (*(s32 **) (obj + 0x44))[((s32) tri - D_800DC26C) / 12 - *(u16 *) (obj + 0x58)];
    } else {
        material = *(s32 *) (obj + 0x40);
    }
    world_record_build_matrix(mtx, obj);
    if (tri != NULL) {
        world[0] = tri[0] + *(s32 *) (obj + 0x20 + D_800BE9C0 * 4);
        world[1] = tri[1] + *(s32 *) (obj + 0x20 + D_800BE9C0 * 4);
        world[2] = tri[2] + *(s32 *) (obj + 0x20 + D_800BE9C0 * 4);
        for (i = 0; i < 3; i++) {
            s16 *v = (s16 *) world[i];

            func_150A7E40(mtx, v[0], v[1], v[2], &ox, &oy, &oz);
            verts[i][0] = ox;
            verts[i][1] = oy;
            verts[i][2] = oz;
            world[i] = (s32) verts[i];
        }
        tri = world;
    }
    impact_effect_spawn(x, height, z, 1, floor_flags_surface_type(material), tri, 0);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/impact_effect_at_world_object.s")
#endif

typedef struct {
    u8 pad0[0x90];
    s32 u90;
    s16 u94;
    s16 u96;
    s16 u98;
    u8 pad9A[0x8];
    s16 uA2;
    s16 uA4;
    u8 padA6[0xE];
    u8 uB4;
} E523S;

/* was func_150E523C */
void fx_ring_sprite_update(E523S *arg0) {
    if (arg0->u90 < 9) {
        arg0->uA4 = (((arg0->u90 * 90) / 9) * arg0->u96) * 0.00390625f;
    } else {
        arg0->uA4 = ((90 - ((arg0->u90 * 90) - 810) / 600) * arg0->u96) * 0.00390625f;
        if (D_800BE9E4 * 17 < arg0->uB4) {
            arg0->uB4 -= D_800BE9E4 * 17;
        } else {
            arg0->u98 = -1;
        }
    }
    arg0->uA2 = (s32)(arg0->u94 * 14.0f) >> 8;
    if (arg0->u90 >= 0x261) {
        arg0->u98 = -1;
    }
    arg0->u90 += D_800BE9E4;
}

#ifdef NON_MATCHING
/* Dust particle record for node_spawn_sprite (0x38 bytes, cleared first). */
typedef struct {
    u8 *tex;        /* +0x00 texture / animation */
    u8 pad04[8];
    s16 u0C, u0E;   /* +0x0C */
    s16 x, y, z;    /* +0x10 position */
    s16 vx, vz;     /* +0x16 velocity x / z */
    u8 pad1A[5];
    u8 u1F;         /* +0x1F */
    s16 vy;         /* +0x20 velocity y */
    s16 gravity;    /* +0x22 */
    s16 size0;      /* +0x24 start size */
    s16 size1;      /* +0x26 end size */
    s16 u28;        /* +0x28 0x182 or 0x183 */
    u8 u2A;         /* +0x2A */
    u8 pad2B;
    u8 r, g, b, a;  /* +0x2C colour */
    u8 pad30[4];
    s16 u34;        /* +0x34 */
    u8 pad36[2];
} ImpactDust;
void tri_compute_plane(s32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
extern f32 D_800CC630, D_800CC634, D_800CC638; /* plane of the last tri_compute_plane triangle */
void mtxf_look_at(f32 mtx[4][4], f32 posx, f32 posy, f32 posz, f32 lookx, f32 looky, f32 lookz, f32 upx, f32 upy,
                   f32 upz);
f32 math_cos_u8(u8);
void *node_spawn_sprite(void *, s32, s32, s8, u8, s32);
void impact_dust_smoke_puff(f32, f32, f32, f32, f32, f32, s32);
extern u8 D_80091C2C[], D_80091C50[], D_80091C5C[], D_800908D0[];
extern u8 D_800D9D80[]; /* 28-byte records; +0x10..+0x18 a direction (f32 x3) */

// impact_dust_spawn: the dust sub-effect of an impact (impact_effect_spawn) at (x, y, z). Kind (flag 0x8000 = only update
// the record, spawn nothing) picks the texture: 0x11 D_80091C2C, 4 / 9 / 10 D_80091C50, 8 D_800908D0 (fixed sizes
// 180..380), else D_80091C5C. With the triangle `tri` (three s16 vertex pointers) the dust leaves along its normal
// (tri_compute_plane plane; nothing at all for a degenerate one): a lookat matrix on the normal turns the cone, and
// record `slot` of D_800D9D80 gets the normal's direction at +0x10. A flat (|ny| >= 0.9) or missing triangle, or
// slot 0xFF, sprays upwards, and the record's byte +3 is cleared. size 0 / 2 spray 12 particles (2: random speed
// scale, double speed, stronger gravity), size 1 one; it stops when node_spawn_sprite has no free record. Kinds 4 / 5 /
// 9 then add a smoke puff (impact_dust_smoke_puff) one time in five. The asm passes size as an 8th argument, which
// impact_dust_smoke_puff does not take. Callers ignore v0 (v0use).
/* was func_150E5384 */
void impact_dust_spawn(f32 x, f32 y, f32 z, s32 kind, s32 size, s32 *tri, s32 slot) {
    f32 v[3][3];
    f32 mtx[4][4];
    ImpactDust rec;
    f32 dx, dy, dz;
    f32 nx, ny, nz, len;
    f32 base = 815.0f;
    f32 sizeF, sizeBase, sizeRange;
    f32 speed, s, c, kx, kz;
    s32 flat = 0;
    s32 fast = 0;
    s32 count = 1;
    s32 more = 1;
    s32 quiet = 0;
    s32 i;
    u8 angle;

    bzero(&rec, sizeof(rec));
    if (kind & 0x8000) {
        quiet = 1;
        kind ^= 0x8000;
    }
    if (tri != NULL) {
        for (i = 0; i < 3; i++) {
            v[i][0] = ((s16 **) tri)[i][0];
            v[i][1] = ((s16 **) tri)[i][1];
            v[i][2] = ((s16 **) tri)[i][2];
        }
        tri_compute_plane(*(s32 *) &v[0][0], v[0][1], v[0][2], v[1][0], v[1][1], v[1][2], v[2][0], v[2][1], v[2][2]);
        nx = -D_800CC630;
        ny = -D_800CC634;
        nz = -D_800CC638;
        len = sqrtf(nx * nx + ny * ny + nz * nz);
        if (len < 0.0001f) {
            return;
        }
        dx = nx / len;
        dy = ny / len;
        dz = nz / len;
        if (slot != 0xFF && fabsf(dy) < 0.9f) {
            mtxf_look_at(mtx, 0.0f, 0.0f, 0.0f, dx, dy, dz, 0.0f, 1.0f, 0.0f);
            func_150A7E40(mtx, 0.0f, 0.0f, 1.0f, (f32 *) (D_800D9D80 + slot * 28 + 0x10),
                          (f32 *) (D_800D9D80 + slot * 28 + 0x14), (f32 *) (D_800D9D80 + slot * 28 + 0x18));
        } else {
            flat = 1;
        }
    } else {
        flat = 1;
    }
    if (slot != 0xFF && flat) {
        D_800D9D80[slot * 28 + 3] = 0;
    }
    if (quiet) {
        return;
    }
    rec.x = (s32) x;
    rec.y = (s32) y;
    rec.z = (s32) z;
    rec.r = 0xB4;
    rec.g = 0xB4;
    rec.b = 0xB4;
    rec.a = 0xFF;
    rec.u1F = 0xFF;
    rec.u34 = 0;
    rec.u0C = 0;
    rec.u0E = 0;
    sizeF = D_800A14E0[size][1];
    sizeBase = sizeF * 95.0f * 0.00390625f;
    sizeRange = sizeF * 130.0f * 0.00390625f;
    if (kind == 0x11) {
        rec.tex = D_80091C2C;
    } else if (kind == 10) {
        rec.tex = D_80091C50;
    } else if (kind == 4 || kind == 9) {
        rec.tex = D_80091C50;
    } else if (kind == 8) {
        rec.tex = D_800908D0;
        sizeBase = 180.0f;
        sizeRange = 200.0f;
    } else {
        rec.tex = D_80091C5C;
    }
    if (size == 2) {
        fast = 1;
        rec.gravity = -0x175;
        count = 12;
        base = base * (0.5f * (func_151EFDD0() % 3 + 1));
    } else if (size == 0) {
        rec.gravity = -0xDA;
        base = base * 0.5f;
        count = 12;
    } else {
        rec.gravity = -0xDA;
    }
    while (count-- != 0 && more) {
        speed = random_float() * 957.0f + base;
        angle = func_151EFDD0() % 256;
        if (fast) {
            speed += speed;
        }
        if (flat) {
            dx = math_sin_u8(angle);
            dy = 1.0f;
            dz = math_cos_u8(angle);
        } else {
            s = math_sin_u8(angle);
            c = math_cos_u8(angle);
            func_150A7E40(mtx, s * 0.5f, c * 0.5f, 1.0f, &dx, &dy, &dz);
        }
        kx = 0.315f * dx;
        kz = 0.315f * dz;
        rec.u28 = func_151EFDD0() % 2 + 0x182;
        rec.vx = (s32) (speed * kx);
        rec.vy = (s32) (speed * dy);
        rec.vz = (s32) (speed * kz);
        func_151EFDD0();
        rec.u2A = 10;
        rec.size0 = (s32) (random_float() * sizeRange + sizeBase);
        rec.size1 = (s32) (random_float() * sizeRange + sizeBase);
        if (node_spawn_sprite(&rec, 0, 0, -1, 0xFF, 0) == NULL) {
            more = 0;
        }
    }
    if (kind == 4 || kind == 9 || kind == 5) {
        if (func_151EFDD0() % 5 == 0) {
            impact_dust_smoke_puff(x, y, z, dx, dy, dz, kind);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/impact_dust_spawn.s")
#endif

s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
s32 func_151EFDD0(void);

/* was func_150E5AD8 */
void impact_dust_smoke_puff(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    struct {
        f32 u28[13];
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        u8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x6];
    } sp;
    f32 a;
    f32 b;
    f32 t;

    bzero(&sp, sizeof(sp));
    if (arg4 != 0.0f) {
        a = func_150484A0(arg3, arg4) * 57.295776f;
    } else {
        a = 90.0f;
    }
    if (arg5 != 0.0f) {
        b = func_150484A0(arg3, arg5) * 57.295776f;
    } else {
        b = 90.0f;
    }
    sp.u28[5] = b;
    sp.u28[6] = a;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u28[0] = 1.0f;
    sp.u28[2] = 0.17f;
    sp.u28[3] = 0.17f;
    sp.u28[10] = arg0;
    sp.u28[11] = arg1;
    sp.u28[12] = arg2;
    sp.u28[4] = 0.0f;
    if (arg6 == 4) {
        sp.u28[1] = 0.6f;
        sp.u7E = 6;
    } else if (arg6 == 9) {
        sp.u28[1] = 0.3f;
        sp.u7E = 8;
    } else {
        sp.u28[1] = 0.3f;
        sp.u7E = 7;
    }
    sp.u7C = (func_151EFDD0() % 60) + 60;
    sp.u78 = 0x29E9;
    t = (random_float() * 4.6f) + 1.5f;
    sp.u74 = -0.78f;
    sp.u5C = t * arg3;
    sp.u60 = -t * arg4;
    sp.u64 = t * arg5;
    sp.u68 = (random_float() * 6.0f) + -3.0f;
    sp.u70 = (random_float() * 6.0f) + -3.0f;
    sp.u6C = (random_float() * 6.0f) + -3.0f;
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = 0xFF;
    sp.u89 = 1;
    sp.u8A = 0;
    sp.u8B = 3;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 2;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 0x20;
    sp.u9C = 7;
    func_15132FBC(&sp, 3, 0xFF, 0, 0xFF, 0);
}

#ifdef NON_MATCHING
void tri_compute_plane(s32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
f32 func_150ADDE0(f32 *a, f32 *b);
extern f32 D_800CC630, D_800CC634, D_800CC638; /* plane of the last tri_compute_plane triangle */

// debris_ground_bounce: ground handler 4 of D_80089CD4 (`s32 (u8 *, f32, f32, f32, f32, u8 *)`, func_15132BBC's
// dispatcher; x / y / z unused). Puts the object on the ground (+0x3C = +0x10 * 1.1 + ground). Slower than 2 downwards
// it stops: velocities +0x44..+0x4C cleared, flags 0x6F of +0x60 dropped. Otherwise it bounces: with the ground
// triangle `tri` (nine s16) the velocity is reflected about the triangle's normal (v - 2 (v.n) n, from the
// tri_compute_plane plane D_800CC630; skipped when the normal is shorter than 1e-5) and scaled by +0x14 (x / z also
// by 0.8); without a triangle only the y velocity is flipped. The spin +0x50..+0x58 is scaled by +0x14 too.
// Returns 1 (keep the object).
/* was func_150E5D90 */
s32 debris_ground_bounce(u8 *p, f32 x, f32 y, f32 z, f32 ground, s16 *tri) {
    f32 vy = *(f32 *) (p + 0x48);
    f32 v[3][3];
    f32 n[3];
    f32 unit[3];
    f32 vel[3];
    f32 len;
    f32 fac;
    s32 i;

    *(f32 *) (p + 0x3C) = *(f32 *) (p + 0x10) * 1.1f + ground;
    if (-2.0f < vy) {
        *(f32 *) (p + 0x44) = 0.0f;
        *(s32 *) (p + 0x60) &= ~0x6F;
        *(f32 *) (p + 0x48) = 0.0f;
        *(f32 *) (p + 0x4C) = 0.0f;
        return 1;
    }
    if (tri != NULL) {
        for (i = 0; i < 3; i++) {
            v[i][0] = tri[i * 3 + 0];
            v[i][1] = tri[i * 3 + 1];
            v[i][2] = tri[i * 3 + 2];
        }
        tri_compute_plane(*(s32 *) &v[0][0], v[0][1], v[0][2], v[1][0], v[1][1], v[1][2], v[2][0], v[2][1], v[2][2]);
        n[0] = -D_800CC630;
        n[1] = -D_800CC634;
        n[2] = -D_800CC638;
        len = func_150AD930(n);
        if (1e-05f < len) {
            vec3_scale((struct17 *) n, 1.0f / len, (struct17 *) unit);
            vel[0] = *(f32 *) (p + 0x44);
            vel[1] = *(f32 *) (p + 0x48);
            vel[2] = *(f32 *) (p + 0x4C);
            len = func_150ADDE0(unit, vel);
            vec3_scale((struct17 *) unit, len + len, (struct17 *) n);
            vec3_sub((struct17 *) vel, (struct17 *) n, (struct17 *) n);
            fac = *(f32 *) (p + 0x14);
            *(f32 *) (p + 0x44) = fac * n[0] * 0.8f;
            *(f32 *) (p + 0x48) = fac * n[1];
            *(f32 *) (p + 0x4C) = fac * n[2] * 0.8f;
        }
        fac = *(f32 *) (p + 0x14);
    } else {
        fac = *(f32 *) (p + 0x14);
        *(f32 *) (p + 0x44) *= fac;
        *(f32 *) (p + 0x48) = -vy * fac;
        *(f32 *) (p + 0x4C) *= fac;
    }
    *(f32 *) (p + 0x50) *= fac;
    *(f32 *) (p + 0x54) *= fac;
    *(f32 *) (p + 0x58) *= fac;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/debris_ground_bounce.s")
#endif
