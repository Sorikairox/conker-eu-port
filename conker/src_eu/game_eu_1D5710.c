#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A4EA8[];


/* P155 */
s32 memcpy(void *, void *, s32);
// path_record_create: allocates a path record (node_alloc kind 0x2D, 0x80 bytes + `extra` + 24 bytes per point
// of def's count at +2), copies the 0x50-byte definition to +0x10, points +0x64 at the point array (+0x80) and +0x60
// past it, zeroes the first point and +0x68 / +0x6C..+0x7B, sets the last point to (0, 0, 1) and +0x7C to
// count * 64 + 0x140. Returns the record or NULL.
/* was func_151A7F00 */
u8 *path_record_create(u8 *def, s32 extra, u8 arg2, s32 arg3) {
    u8 *rec;
    f32 *pt;
    s16 n = *(s16 *)(def + 2);

    rec = node_alloc(0x2D, arg3, n * 24 + extra + 0x80, 1, arg2, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, def, 0x50);
    *(u8 **)(rec + 0x64) = rec + 0x80;
    *(f32 *)(rec + 0x68) = 0.0f;
    *(u8 **)(rec + 0x60) = rec + 0x80 + *(s16 *)(def + 2) * 24;
    pt = *(f32 **)(rec + 0x64);
    pt[0] = 0.0f;
    pt[1] = 0.0f;
    pt[2] = 0.0f;
    pt = (f32 *)(*(u8 **)(rec + 0x64) + *(s16 *)(def + 2) * 24) - 6;
    pt[0] = 0.0f;
    pt[1] = 0.0f;
    pt[2] = 1.0f;
    bzero(rec + 0x6C, 0x10);
    *(s32 *)(rec + 0x7C) = *(s16 *)(rec + 0x12) * 64 + 0x140;
    return rec;
}

extern s32 (*D_8008FCE0[])(u8 *);
extern s32 (*D_8008FCE8[])(u8 *);
void bolt_subdivide(u8 *obj, s16 lo, s16 hi, f32 amp, s16 depth);

// bolt_path_update: per-frame update of a lightning bolt path record (path_record_create). Flag 1 counts the lifetime at
// +0x10 down (done below 0); the hooks D_8008FCE0[+0x2C] / D_8008FCE8[+0x2D] (-1 = none) end it by returning 0.
// While alive, the +0x68 timer counts down; at 0 the points are re-jittered (bolt_subdivide over [0, count - 1],
// amplitude +0x20, depth 100) and the timer restarts at +0x14 + rand * +0x18. Flag 2 then maps every point (stride
// 0x18: local x, y, z at +0, world at +0xC) from the local frame (x: side axis from vec3_cross * +0x58 scale, y: +0x48 up, z: end +0x3C - start +0x30)
// to the world, based at the start point. Finished records are freed (node_destroy).
/* was func_151A8040 */
void bolt_path_update(u8 *obj) {
    struct17 fwd;
    struct17 up;
    struct17 side;
    f32 *pt;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 done = 0;

    if (obj[0x1C] & 1) {
        *(s16 *) (obj + 0x10) -= D_800BE9E4;
        if (*(s16 *) (obj + 0x10) < 0) {
            done = 1;
        }
    }
    if ((s8) obj[0x2C] != -1 && !done) {
        done = D_8008FCE0[(s8) obj[0x2C]](obj) == 0;
    }
    if ((s8) obj[0x2D] != -1 && !done) {
        done = D_8008FCE8[(s8) obj[0x2D]](obj) == 0;
    }
    if (!done) {
        *(f32 *) (obj + 0x68) -= D_800BE9A4;
        if (*(f32 *) (obj + 0x68) < 0.0f) {
            bolt_subdivide(obj, 0, *(s16 *) (obj + 0x12) - 1, *(f32 *) (obj + 0x20), 100);
            *(f32 *) (obj + 0x68) = random_float() * *(f32 *) (obj + 0x18) + *(f32 *) (obj + 0x14);
        }
        if (obj[0x1C] & 2) {
            fwd.unk0 = *(f32 *) (obj + 0x3C) - *(f32 *) (obj + 0x30);
            fwd.unk4 = *(f32 *) (obj + 0x40) - *(f32 *) (obj + 0x34);
            fwd.unk8 = *(f32 *) (obj + 0x44) - *(f32 *) (obj + 0x38);
            up = *(struct17 *) (obj + 0x48);
            vec3_cross(&fwd, &up, &side);
            side.unk0 *= *(f32 *) (obj + 0x58);
            side.unk4 *= *(f32 *) (obj + 0x58);
            side.unk8 *= *(f32 *) (obj + 0x58);
            pt = *(f32 **) (obj + 0x64);
            for (i = 0; i < *(s16 *) (obj + 0x12); i++) {
                x = pt[0];
                y = pt[1];
                z = pt[2];
                pt[3] = *(f32 *) (obj + 0x30) + x * side.unk0 + y * up.unk0 + z * fwd.unk0;
                pt[4] = *(f32 *) (obj + 0x34) + x * side.unk4 + y * up.unk4 + z * fwd.unk4;
                pt[5] = *(f32 *) (obj + 0x38) + x * side.unk8 + y * up.unk8 + z * fwd.unk8;
                pt += 6;
            }
        }
    }
    if (done) {
        node_destroy((struct102 *) obj);
    }
}

s32 gfx_set_combine_mode(s32, s32, s8 *);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_env_color_cached(s32, u8, u8, u8, s32, s8 *);
s32 gfx_load_texture_cached(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void segment_closest_point(void *, void *, void *, void *, f32 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_80091120;
extern s32 D_800D30BC;

/* was func_151A831C */
u8 *bolt_path_draw(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s32 u78;
        u8 pad7C[0x8];
        s16 u84;
        u8 pad86[0x1];
        s8 u87;
        f32 u88;
        f32 * u8C;
        u8 pad90[0x18];
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        u8 * uC0;
    } sp;
    f32 sp58;
    f32 sp54;
    s32 *temp_v1;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s16 var_s1;
    s16 var_s2;
    s32 temp_lo;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_t0;
    u8 *temp_t0_2;
    u8 *temp_t0_3;
    u8 *temp_t0_4;
    u8 *temp_t7;
    u8 *temp_t8;
    u8 *temp_t9;
    u8 *temp_v1_2;
    u8 *var_s0;

    var_s0 = arg0;
    if ((*(u8 *)((u8 *)arg1 + 0x1C)) & 2) {
        vtx_slot_buffer_get(arg1 + 0x6C, arg2, (*(s32 *)((u8 *)arg1 + 0x7C)), &sp.uC0, 0);
        if (sp.uC0 != NULL) {
            sp.u8C = camera_get_pos((s32) arg2);
            sp.u87 = 1;
            sp.u84 = (*(s16 *)((u8 *)arg1 + 0x12)) - 1;
            var_s2 = 0;
            var_s1 = 1;
            temp_v1 = ((u8 *)&D_800A4EA8);
            temp_t0 = (*(u8 **)((u8 *)arg1 + 0x64));
            temp_lo = sp.u84 * 0x18;
            var_s0 = gfx_other_mode_cached(gfx_set_combine_mode(gfx_env_color_cached(gfx_geometry_mode_cached(gfx_load_texture_cached(var_s0, &D_80091120, 0, 0, 0, 0, 0x2C, 0, 0, &sp.u87, 3), 0x200005, 0x1F0600), (*(u8 *)((u8 *)arg1 + 0x24)), (*(u8 *)((u8 *)arg1 + 0x25)), (*(u8 *)((u8 *)arg1 + 0x26)), (s32) (*(u8 *)((u8 *)arg1 + 0x27)), &sp.u87), 0x19, &sp.u87), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1 + 0x1C)) | (*(s32 *)((u8 *)temp_v1 + 0x18)), &sp.u87);
            sp.uB4 = (*(f32 *)((u8 *)temp_t0 + 0xC)) - (*(f32 *)((u8 *)((temp_t0 + temp_lo)) + 0xC));
            temp_t0_2 = (*(u8 **)((u8 *)arg1 + 0x64));
            sp.uB8 = (*(f32 *)((u8 *)temp_t0_2 + 0x10)) - (*(f32 *)((u8 *)((temp_t0_2 + temp_lo)) + 0x10));
            temp_t0_3 = (*(u8 **)((u8 *)arg1 + 0x64));
            sp.uBC = (*(f32 *)((u8 *)temp_t0_3 + 0x14)) - (*(f32 *)((u8 *)((temp_t0_3 + temp_lo)) + 0x14));
            segment_closest_point((*(u8 **)((u8 *)arg1 + 0x64)) + temp_lo + 0xC, &sp.uB4, sp.u8C, &sp.uA8, &sp.u78);
            temp_f0 = (*(f32 *)((u8 *)sp.u8C + 0)) - sp.uA8;
            temp_f2 = (*(f32 *)((u8 *)sp.u8C + 4)) - sp.uAC;
            temp_f12 = (*(f32 *)((u8 *)sp.u8C + 8)) - sp.uB0;
            temp_f18 = (sp.uB8 * temp_f12) - (temp_f2 * sp.uBC);
            temp_f4 = (sp.uBC * temp_f0) - (temp_f12 * sp.uB4);
            sp58 = temp_f4;
            temp_f10 = (sp.uB4 * temp_f2) - (temp_f0 * sp.uB8);
            sp54 = temp_f10;
            temp_f14 = (temp_f18 * temp_f18) + (temp_f4 * temp_f4) + (temp_f10 * temp_f10);
            sp.u88 = temp_f14;
            if (temp_f14 == 0.0f) {
                var_f2 = 0.0f;
                var_f12 = 0.0f;
                var_f14 = 0.0f;
            } else {
                temp_f16 = (*(f32 *)((u8 *)arg1 + 0x28)) / sqrtf(sp.u88);
                var_f2 = temp_f18 * temp_f16;
                var_f12 = sp58 * temp_f16;
                var_f14 = sp54 * temp_f16;
            }
            if ((*(s16 *)((u8 *)arg1 + 0x12)) >= 2) {
                do {
                    temp_t0_4 = (*(u8 **)((u8 *)arg1 + 0x64));
                    temp_v1_2 = temp_t0_4 + (var_s1 * 0x18) + 0xC;
                    temp_a0 = temp_t0_4 + (var_s2 * 0x18);
                    temp_a0_2 = temp_a0 + 0xC;
                    (*(s16 *)((u8 *)sp.uC0 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a0 + 0xC)) + var_f2);
                    (*(s16 *)((u8 *)sp.uC0 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a0_2 + 4)) + var_f12);
                    (*(s16 *)((u8 *)sp.uC0 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a0_2 + 8)) + var_f14);
                    (*(s16 *)((u8 *)sp.uC0 + 8)) = 0;
                    (*(s16 *)((u8 *)sp.uC0 + 0xA)) = 0;
                    (*(s8 *)((u8 *)sp.uC0 + 0xC)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xD)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xE)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xF)) = 0xFF;
                    (*(s16 *)((u8 *)sp.uC0 + 6)) = 0;
                    temp_t9 = sp.uC0 + 0x10;
                    sp.uC0 = temp_t9;
                    (*(s16 *)((u8 *)temp_t9 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a0_2 + 0)) - var_f2);
                    (*(s16 *)((u8 *)sp.uC0 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a0_2 + 4)) - var_f12);
                    (*(s16 *)((u8 *)temp_t9 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_a0_2 + 8)) - var_f14);
                    (*(s16 *)((u8 *)sp.uC0 + 8)) = 0x3C0;
                    (*(s16 *)((u8 *)sp.uC0 + 0xA)) = 0;
                    (*(s8 *)((u8 *)sp.uC0 + 0xC)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xD)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xE)) = 0xFF;
                    (*(s8 *)((u8 *)temp_t9 + 0xF)) = 0xFF;
                    (*(s16 *)((u8 *)sp.uC0 + 6)) = 0;
                    temp_t8 = sp.uC0 + 0x10;
                    sp.uC0 = temp_t8;
                    (*(s16 *)((u8 *)temp_t8 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) - var_f2);
                    (*(s16 *)((u8 *)sp.uC0 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v1_2 + 4)) - var_f12);
                    (*(s16 *)((u8 *)temp_t8 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) - var_f14);
                    (*(s16 *)((u8 *)sp.uC0 + 8)) = 0x3C0;
                    (*(s16 *)((u8 *)sp.uC0 + 0xA)) = 0x3C0;
                    (*(s8 *)((u8 *)sp.uC0 + 0xC)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xD)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xE)) = 0xFF;
                    (*(s8 *)((u8 *)temp_t8 + 0xF)) = 0xFF;
                    (*(s16 *)((u8 *)sp.uC0 + 6)) = 0;
                    temp_t7 = sp.uC0 + 0x10;
                    sp.uC0 = temp_t7;
                    (*(s16 *)((u8 *)temp_t7 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) + var_f2);
                    (*(s16 *)((u8 *)sp.uC0 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v1_2 + 4)) + var_f12);
                    (*(s16 *)((u8 *)temp_t7 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) + var_f14);
                    (*(s16 *)((u8 *)sp.uC0 + 8)) = 0;
                    (*(s16 *)((u8 *)sp.uC0 + 0xA)) = 0x3C0;
                    (*(s8 *)((u8 *)sp.uC0 + 0xC)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xD)) = 0xFF;
                    (*(s8 *)((u8 *)sp.uC0 + 0xE)) = 0xFF;
                    (*(s8 *)((u8 *)temp_t7 + 0xF)) = 0xFF;
                    var_s1 += 1;
                    (*(s16 *)((u8 *)sp.uC0 + 6)) = 0;
                    sp.uC0 += 0x10;
                    (*(s32 *)((u8 *)var_s0 + 0)) = 0x01004008;
                    temp_s0 = var_s0 + 8;
                    (*(u8 **)((u8 *)var_s0 + 4)) = (u8 *) (sp.uC0 - 0x40);
                    temp_s0_2 = temp_s0 + 8;
                    (*(s32 *)((u8 *)temp_s0 + 0)) = 0x05000204;
                    (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
                    (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0x05000406;
                    (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
                    var_s0 = temp_s0_2 + 8;
                    var_s2 += 1;
                } while (var_s1 < (*(s16 *)((u8 *)arg1 + 0x12)));
            }
        }
    }
    return var_s0;
}
#define BOLT_PT(obj, i) ((f32 *) (*(u8 **) ((u8 *) (obj) + 0x64) + (i) * 0x18))

// bolt_subdivide: midpoint displacement of a lightning bolt's point list (obj+0x64, 0x18-byte points): the midpoint
// of [lo, hi] becomes the average of the two ends, x / y jittered by +-amp (random_float), z not; recurses on the
// left half and loops on the right half while the span has an inner point and depth (decremented per split) > 0.
/* was func_151A88F0 */
void bolt_subdivide(u8 *obj, s16 lo, s16 hi, f32 amp, s16 depth) {
    f32 *a;
    f32 *b;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 mid;

    while (hi - lo >= 2 && depth > 0) {
        mid = lo + ((hi - lo) >> 1);
        a = BOLT_PT(obj, lo);
        b = BOLT_PT(obj, hi);
        dx = b[0] - a[0];
        dy = b[1] - a[1];
        dz = b[2] - a[2];
        BOLT_PT(obj, mid)[0] = (random_float() * (amp + amp) + -amp) + (a[0] + dx * 0.5f);
        BOLT_PT(obj, mid)[1] = (random_float() * (amp + amp) + -amp) + (a[1] + dy * 0.5f);
        BOLT_PT(obj, mid)[2] = a[2] + dz * 0.5f;
        depth--;
        bolt_subdivide(obj, lo, mid, amp, depth);
        lo = mid;
    }
}
#undef BOLT_PT

/* was func_151A8B10 */
void bolt_path_release_buffers(u8 *arg0) {
    vtx_slot_buffers_free(arg0 + 0x6C, arg0);
}

/* was func_151A8B34 */
void bolt_path_retire(u8 *arg0) {
    u8 *new_var; // fakematch: permuter temp
    void (*fn)(void *) = D_8008FCEC[arg0[0x5C]];
    new_var = arg0;
    if (fn != NULL) {
        if (!arg0) { // fakematch: permuter empty branch
        }
        fn(new_var);
    }
    bolt_path_release_buffers(arg0);
    node_retire(arg0);
}

/* was func_151A8B84 */
void bolt_path_free(u8 *arg0) {
    u8 *new_var; // fakematch: permuter temp
    void (*fn)(void *) = D_8008FCF8[arg0[0x5C]];
    new_var = arg0;
    if (fn != NULL) {
        if (!arg0) { // fakematch: permuter empty branch
        }
        fn(new_var);
    }
    bolt_path_release_buffers(arg0);
    node_unlink_free(arg0);
}

// File-scope .rodata table (0x170 bytes); bolt_attach_create reads its first word (79.75f).
// rodata_inject: cdefined 0x24E440 0x24E5B0
const u32 D_800A91C0[92] = {
    0x429F8000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    0x00000000, 0x00000000, 0x00320000, 0x00320000, 0x00FF0000, 0x000100FF,
    0x3F800000, 0x00000000, 0x00000000, 0x3F4D0E57, 0x3F66A7F0, 0x3F67EF9E,
    0x3F33B646, 0x00100032, 0x00320032, 0x00500078, 0x0014000C, 0x3DCCCCCD,
    0x3E991688, 0x00000000, 0x3EFF7CEE, 0x3F4C0832, 0x3F4E5605, 0x3F020C4A,
    0x000A0032, 0x00320019, 0x00500096, 0x0010000F, 0x3DDB22D2, 0x3E810625,
    0x00000000, 0x3F50624E, 0x3F31EB86, 0x3EA4DD30, 0x3F0AC084, 0x000A0045,
    0x003C0019, 0x00500078, 0x0010000F, 0x3DAC0832, 0x3E970A3E, 0x00000000,
    0x3F80624E, 0x3FA53F7D, 0x3FA70A3E, 0x3F958107, 0x000A0032, 0x00220014,
    0x00500078, 0x0014000C, 0x3E8ED917, 0x3E9A1CAD, 0x00000000, 0x3FA9374C,
    0x3FE00001, 0x3F9E76C9, 0x3F8DD2F2, 0x0004005B, 0x003C0028, 0x00640064,
    0x001E0008, 0x3DD91688, 0x3E9C28F6, 0x00000000, 0x3F920C4A, 0x3F8B22D1,
    0x3FC51EB9, 0x3F3020C5, 0x002E004A, 0x00230019, 0x00640064, 0x001E0008,
    0x3D178D50, 0x3DCAC084, 0x00000000, 0x3ED58107, 0x3EFA5E36, 0x3EC28F5D,
    0x3EB020C5, 0x001E0078, 0x00310019, 0x00640064, 0x000F0011, 0x3DB851EC,
    0x3D4CCCCD, 0x00000000,
};

s32 memcpy(void *, void *, s32);
u8 *path_record_create(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);

typedef struct { f32 v[3]; } V3BD4;
typedef struct { u8 b[4]; } C4BD4;
typedef struct {
    u8 *obj;
    u8 id;
    u8 pad5[3];
    V3BD4 pos;
    u8 idx;
    u8 pad15[3];
    V3BD4 off;
    u8 b24;
    u8 fl;
} L8BD4;
typedef struct {
    s16 kind;
    s16 count;
    f32 f4;
    f32 f8;
    u8 uC;
    f32 f10;
    C4BD4 c14;
    f32 f18;
    u8 u1C;
    s8 s1D;
    f32 f20[10];
    f32 f48;
    u8 u4C;
} S8BD4;

/* was func_151A8BD4 */
u8 *bolt_attach_create(u8 *obj, V3BD4 *pos, u8 idx, s16 kind, f32 f4, f32 f8, C4BD4 *c, f32 f18, V3BD4 *off, u8 mode, u8 b24, s8 s1D, s32 a1, u8 a2, s32 a3) {
    u8 *ret;
    S8BD4 s;
    L8BD4 l;
    s32 k;
    s32 t;

    if (obj == NULL) {
        return NULL;
    }
    k = mode;
    if (k >= 2) {
        k = 0;
    }
    l.pos = *pos;
    l.idx = idx;
    l.fl = 0;
    l.obj = obj;
    l.id = obj[0x3B];
    l.b24 = b24;
    if (off != NULL) {
        l.off = *off;
    } else {
        l.off.v[0] = 0.0f;
        l.off.v[1] = 0.0f;
        l.off.v[2] = 0.0f;
    }
    s.kind = (kind == -1) ? 300 : kind;
    s.count = 9;
    s.f4 = f4;
    s.f8 = f8;
    if (kind == -1) {
        t = 0;
    } else {
        t = 1;
    }
    s.uC = t;
    s.f10 = *(f32 *)D_800A91C0;
    s.c14 = *c;
    s.f18 = f18;
    if (k != 0 && k == 1) {
        s.u1C = 1;
    } else {
        s.u1C = 1;
    }
    s.s1D = s1D;
    s.f20[0] = 0.0f;
    s.f20[1] = 0.0f;
    s.f20[2] = 0.0f;
    s.f20[3] = 0.0f;
    s.f20[4] = 0.0f;
    s.f20[5] = 0.0f;
    s.f20[6] = 0.0f;
    s.f20[7] = 0.0f;
    s.f20[8] = 0.0f;
    s.f20[9] = 0.0f;
    s.u4C = 2;
    s.f48 = 1.0f;
    ret = path_record_create((u8 *)&s, a1 + 0x28, a2, a3);
    if (ret != NULL) {
        memcpy(*(void **)(ret + 0x60), &l, 0x28);
    }
    return ret;
}

s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, s32, u8 *, u8 *, u8 *, s32, s32 *, s32, f32);
f32 vec3_length(f32 *);
s32 prop_is_flagged(s32);
s32 vec3_make_basis(f32 *, s32 *, u8 *);

/* was func_151A8DA8 */
s32 bolt_follow_owner(u8 *arg0) {
    struct {
        s32 u60;
        u8 pad64[0x14];
        s32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        u8 * u88;
        u8 * u8C;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    s32 temp_a3;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x60));
    temp_v0 = (*(u8 **)((u8 *)temp_v1 + 0));
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v1 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || ((*(u8 *)((u8 *)temp_v0 + 4)) == 0xFF)) {
        return 0;
    }
    temp_a3 = (*(s32 *)((u8 *)temp_v0 + 0x1D4));
    if (temp_a3 != 0) {
        sp.u8C = temp_v1;
        sp.u88 = temp_v0;
        mtx_transform_point_or_origin(temp_v1 + 8, arg0 + 0x30, temp_a3 + ((*(u8 *)((u8 *)temp_v1 + 0x14)) << 6));
        if (!((*(u8 *)((u8 *)sp.u8C + 0x25)) & 1)) {
            temp_f12 = (*(f32 *)((u8 *)arg0 + 0x30));
            temp_f0 = (*(f32 *)((u8 *)arg0 + 0x38));
            temp_f14 = (*(f32 *)((u8 *)arg0 + 0x34));
            if (collision_ray_cast(temp_f12, temp_f14, temp_f0, temp_f12 - ((*(f32 *)((u8 *)sp.u88 + 0x14)) + (*(f32 *)((u8 *)sp.u8C + 0x18))), temp_f14 - ((*(f32 *)((u8 *)sp.u88 + 0x18)) + (*(f32 *)((u8 *)sp.u8C + 0x1C))), temp_f0 - ((*(f32 *)((u8 *)sp.u88 + 0x1C)) + (*(f32 *)((u8 *)sp.u8C + 0x20))), 0, 0, arg0 + 0x3C, arg0 + 0x40, arg0 + 0x44, 0, &sp.u78, 0, 0.0f) != 0) {
                if (prop_is_flagged(sp.u78) != 0) {
                    (*(u8 *)((u8 *)sp.u8C + 0x25)) = (u8) ((*(u8 *)((u8 *)sp.u8C + 0x25)) | 1);
                    goto block_11;
                }
                (*(u8 *)((u8 *)arg0 + 0x1C)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x1C)) & 0xFFFD);
                return 1;
            }
            (*(u8 *)((u8 *)arg0 + 0x1C)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x1C)) & 0xFFFD);
            return 1;
        }
block_11:
        sp.u7C = (*(f32 *)((u8 *)arg0 + 0x3C)) - (*(f32 *)((u8 *)arg0 + 0x30));
        sp.u80 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u84 = (*(f32 *)((u8 *)arg0 + 0x44)) - (*(f32 *)((u8 *)arg0 + 0x38));
        temp_f0_2 = vec3_length(&sp.u7C);
        (*(f32 *)((u8 *)arg0 + 0x54)) = temp_f0_2;
        if (temp_f0_2 != 0.0f) {
            (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) (1.0f / (*(f32 *)((u8 *)arg0 + 0x54)));
            vec3_make_basis(&sp.u7C, &sp.u60, arg0 + 0x48);
            (*(u8 *)((u8 *)arg0 + 0x1C)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x1C)) | 2);
        } else {
            (*(u8 *)((u8 *)arg0 + 0x1C)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x1C)) & 0xFFFD);
        }
        goto block_15;
    }
    (*(u8 *)((u8 *)arg0 + 0x1C)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x1C)) & 0xFFFD);
block_15:
    return 1;
}
/* was func_151A8FD0 */
void bolt_path_handle_msg(u8 *arg0, s32 arg1, u8 arg2) {
    s32 idx = arg0[0x5C];
    void (*fn)(u8 *, s32, u8);

    if (idx >= 3) {
        idx = 0;
    }
    fn = (void (*)(u8 *, s32, u8))D_8008FD04[idx];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

/* was func_151A9028 */
void bolt_attach_handle_msg(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a0;
    s32 new_var; // fakematch: key temp pins the v1 register
    s32 temp_t6 = arg2;
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x60);

    if (arg2 == 0) {
        new_var = *(s32 *)(arg1 + 0);
        if ((new_var == *(s32 *)(temp_v0 + 0)) || (*(u8 *)(arg1 + 4) == *(u8 *)(temp_v0 + 4))) {
            node_destroy(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)(arg1 + 0);
        if (temp_a0 == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = temp_a0;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}

typedef struct {
    f32 x;
    u8 pad4[0x14];
    s32 u18;
    u8 u1C;
    u8 u1D;
    s32 u20;
} Obj9DE4;
s32 collision_floor_probe(f32 *, s32, f32, Obj9DE4 *);

s32 memcpy(void *, void *, s32);
void collision_select_area(s32);
s32 zone_tree_find_leaf(s32 arg0, s32 arg1);
f32 spawn_region_area(struct_eu_15144598 *arg0);
struct260 *effect_node_create(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);

typedef struct {
    u8 flags;
    u8 pad1[3];
    struct_eu_15144598 *src;
    u8 pad8[8];
    f32 x;
    f32 y14;
    f32 z;
    f32 f1C;
    f32 r;
    u8 pad24[4];
    f32 f28;
    f32 f2C;
    u8 pad30[0x14];
    s32 u44;
    u8 b48;
    u8 b49;
    s32 u4C;
    s32 u50;
    f32 f54;
} S8B20;

/* was func_151A8B20 */
struct260 *ground_emitter_spawn(void *arg0, s16 arg1, s32 arg2, u8 arg3, s32 arg4) {
    struct260 *ret;
    S8B20 sp;
    S8B20 *p;
    f32 z;

    memcpy(&sp, arg0, 0x28);
    sp.u44 = 0;
    sp.b48 = 0;
    sp.b49 = 0;
    sp.u4C = 0;
    sp.f28 = 0.0f;
    sp.f2C = 99999.9f;
    ret = effect_node_create((arg1 == -1) ? 0x12C : arg1, -1, 0x25, -1, (arg1 == -1) ? 0 : 1, 0x22, (struct37 *)(arg2 + 0x58), arg3, arg4);
    if (ret != NULL) {
        p = (S8B20 *)((u8 *)ret + 0x28);
        memcpy(p, &sp, 0x58);
        if (p->flags & 4) {
            f32 x;

            if ((p->flags & 2) && (p->src != NULL)) {
                x = *(s16 *)((u8 *)p->src + 0);
                z = *(s16 *)((u8 *)p->src + 4);
            } else {
                x = p->x;
                z = p->z;
            }
            collision_select_area(0);
            p->u50 = zone_tree_find_leaf(x, z);
        } else {
            p->u50 = 0;
        }
        if ((p->flags & 2) && (p->src != NULL)) {
            p->f54 = spawn_region_area(p->src);
        } else {
            p->f54 = p->r * p->r * 3.1415927f;
        }
    }
    return ret;
}

s32 player_mask_hides_all(s32);
void ground_emitter_point_bone(u8 *arg0, u8 *arg1, f32 *arg2, s32 arg3);
void ground_emitter_point_disc(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
typedef s32 (*Fn929C)(u8 *);
extern Fn929C D_8008FD20[];
typedef void (*Fn929C2)(u8 *, f32 *, f32, u8);
extern Fn929C2 D_8008FD10[];

typedef struct {
    u8 flags;
    u8 pad1[3];
    s32 src;
    f32 f8;
    f32 fC;
    u8 pad10[0x16];
    s8 s26;
    u8 pad27;
    f32 acc;
    Obj9DE4 obj;
    s32 u50;
    f32 f54;
} P929C;

/* was func_151A929C */
void ground_emitter_update(u8 *arg0) {
    P929C *p;
    void (*fn)(u8 *, f32 *, f32 *, f32 *);

    p = (P929C *)(arg0 + 0x28);
    if (*(s8 *)(arg0 + 0x4D) != -1 && !D_8008FD20[(s8)arg0[0x4D]](arg0)) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if ((p->flags & 4) && p->u50 != 0 && player_mask_hides_all(p->u50)) {
        return;
    }
    if (!(p->flags & 1)) {
        return;
    }
    p->acc += (p->f8 + random_float() * p->fC) * D_800BE9A4 * p->f54;
    if (p->acc > 1.0f) {
        f32 pos[3];
        f32 y;
        f32 w;
        u8 flag;

        if ((p->flags & 2) && p->src != 0) {
            fn = (void (*)(u8 *, f32 *, f32 *, f32 *))ground_emitter_point_bone;
        } else {
            fn = ground_emitter_point_disc;
        }
        do {
            fn(arg0, pos, &w, &y);
            if (p->flags & 8) {
                pos[1] = y;
                flag = 1;
            } else if (collision_floor_probe(pos, 0, y, &p->obj)) {
                pos[1] = p->obj.x;
            } else {
                pos[1] = y;
                flag = 1;
            }
            if (p->s26 != -1) {
                D_8008FD10[p->s26](arg0, pos, w, flag);
            }
            p->acc -= 1.0f;
        } while (p->acc > 1.0f);
    }
}

s32 spawn_region_random_point(s32, u8 *, u8 *, f32 *, s32);
/* was func_151A94CC */
void ground_emitter_point_bone(u8 *arg0, u8 *arg1, f32 *arg2, s32 arg3) {
    spawn_region_random_point(*(s32 *)(arg0 + 0x2C), arg1, arg1 + 8, arg2, arg3);
    *(f32 *)(arg1 + 4) = *arg2;
}

void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
/* was func_151A951C */
void ground_emitter_point_disc(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 *p;

    p = (f32 *)(arg0 + 0x28);
    vec2_from_angle_byte(random_int() & 0xFF, p[8] * random_float(), arg1, arg1 + 2);
    arg1[0] += p[4];
    arg1[2] += p[6];
    arg1[1] = p[5];
    *arg2 = p[5];
    *arg3 = p[7];
}

void ground_emitter_toggle_msg(u8 *, s32, u8);
/* was func_151A95D4 */
void ground_emitter_handle_msg(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg0[0x4C] == 1) {
        ground_emitter_toggle_msg(arg0, arg1, arg2);
    }
}

extern s32 (*D_8008FD24[])(u8 *, s32);

/* was func_151A9610 */
s32 obj_effect_dispatch(u8 *arg0) {
    s32 i;
    s32 (*fn)(u8 *, s32);

    arg0[0x16] |= 4;
    i = *(s32 *)(arg0 + 0x18);
    if (i < 0 || i >= 8) {
        return 1;
    }
    fn = D_8008FD24[i];
    if (fn != NULL) {
        fn(arg0, i);
    }
    return 1;
}

/* P241: readable C for object_effect_kind2_start (game_eu_1D5710, 59 insns). */
// object_effect_kind2_start: handler of D_8008FD24 entries 0..5 (`(u8 *, s32)`, dispatcher obj_effect_dispatch ignores the
// result): spawns a kind-2 effect owned by obj through ground_emitter_spawn (1 byte of extra data) with the two values
// 1.4e-6 / 8e-7 for an odd table index or 4e-7 / 6e-7 for an even one (the ELF's D_800A9338 / D_800A9340 and
// D_800A933C / D_800A9344), and stores the index byte in the new record at +0x80. The asm leaves the spawn block's
// padding bytes uninitialised, as here.
/* was func_151A9670 */
void object_effect_kind2_start(u8 *obj, s32 idx) {
    struct {
        u8 kind;
        u8 *owner;
        f32 a, b;
        f32 zero[5];
        s8 b24, b25, b26;
    } spawn;
    u8 extra;
    struct260 *p;

    spawn.kind = 2;
    spawn.owner = obj;
    spawn.a = (idx & 1) ? 1.4e-6f : 4e-7f;
    spawn.b = (idx & 1) ? 8e-7f : 6e-7f;
    spawn.zero[0] = spawn.zero[1] = spawn.zero[2] = spawn.zero[3] = spawn.zero[4] = 0.0f;
    spawn.b24 = 1;
    spawn.b25 = -1;
    spawn.b26 = 0;
    extra = idx;
    p = ground_emitter_spawn(&spawn, -1, 1, 0xFF, 0);
    if (p != NULL) {
        memcpy((u8 *) p + 0x80, &extra, 1);
    }
}

typedef struct {
    s32 u0;
    s16 u4;
    u8 u6;
    u8 u7;
    s32 u8_;
    s32 uC;
    u8 u10[8];
    s32 u18;
    s32 u1C;
    u8 u20;
    s16 u22;
    s16 u24;
} Spawn975C;
typedef struct { s16 v[3]; } Tbl975C;
extern Tbl975C D_8008FD44;

/* was func_151A975C */
void ground_emitter_spawn_sprite(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 pad;
    Spawn975C sp;
    f32 f;
    Tbl975C t;

    t = D_8008FD44;
    f = random_float() * 50.0f + 50.0f;
    sp.u6 = t.v[random_int() % 3U];
    sp.u7 = 0;
    sp.u10[6] = 0;
    sp.u10[7] = 7;
    sp.u8_ = 0;
    sp.uC = 0;
    sp.u0 = 0x1701;
    sp.u4 = 0x3C;
    sp.u10[0] = 0xA0;
    sp.u10[1] = 0xFF;
    sp.u10[2] = 0;
    sp.u10[3] = 0;
    sp.u10[4] = 0;
    sp.u10[5] = 0xFF;
    sp.u18 = 0x3B0002;
    sprite_fx_spawn_cam_at((s32)&sp, 1, 0, (s32)(arg0 + 0x58), *(f32 *)(arg1 + 0), *(f32 *)(arg1 + 4), *(f32 *)(arg1 + 8), f, f, random_int() & 0xFF, (random_int() & 1) + (random_int() & 1), 3, 0xFF, 0, arg0[0xC], arg0[1]);
}

/* was func_151A98CC */
void ground_emitter_toggle_msg(u8 *arg0, s32 arg1, u8 arg2)
{
  if (arg2 == 0x17) {
    u8 *p = arg0 + 0x28;
    if (((u8 *)arg1)[0] == arg0[0x80]) {
      *p |= 1;
    }
  } else if (arg2 == 0x18) {
    u8 *p = arg0 + 0x28;
    if (((u8 *)arg1)[0] == arg0[0x80]) {
      *p &= ~1;
    }
  }
}

/* P155 */
s32 light_create_flicker_preset(void *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct {
    f32 f0;    /* spawn record +0x08 */
    f32 f4;    /* spawn record +0x0C */
    u8 b8;     /* sound / emitter parameters for light_create_flicker_preset */
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    void *extra; /* 0x2C bytes copied behind the record (+0x80) */
} Kind9940;
extern Kind9940 D_8008FD4C[];
// kind_effect_spawn: spawns effect kind `kind` (< 9, table D_8008FD4C, 0x14 bytes each) through ground_emitter_spawn (life
// `life`, -1 = untimed 300) at `pos` (f32[3]) or, without pos, attached to `owner` (s16 position at +0); the
// 0x2C-byte kind data goes behind the record (+0x80), with flag bits 0x08 / 0x10 of `flags` as its +0x28 bits 1 / 2.
// flags bit 1 marks the record (bit 4), bit 2 (bit 8); bit 4 also starts the kind's sound / emitter
// (light_create_flicker_preset) at pos or the owner position.
/* was func_151A9940 */
void kind_effect_spawn(u8 flags, u8 kind, void *owner, s32 pos, f32 arg4, f32 arg5, s16 life, u8 arg7, s32 arg8) {
    struct {
        u8 flags;
        u8 pad1[3];
        void *owner;
        f32 f8;
        f32 fC;
        f32 pos[3];
        f32 f1C;
        f32 f20;
        s8 b24;
        s8 b25;
        s8 b26;
        u8 pad27;
    } spawn;
    struct {
        u8 flags;
        u8 b1;
        s16 life;
        u8 b4;
        u8 pad5[3];
    } snd;
    s32 at[3];
    Kind9940 *k;
    u8 *rec;
    f32 *p = (f32 *)pos;

    if (kind >= 9) {
        return;
    }
    k = &D_8008FD4C[kind];
    spawn.flags = ((flags & 2) ? 8 : 0) | 1 | ((owner != NULL) ? 2 : 0) | ((flags & 1) ? 4 : 0);
    spawn.owner = owner;
    spawn.f8 = k->f0;
    spawn.fC = k->f4;
    if (p != NULL) {
        spawn.pos[0] = p[0];
        spawn.pos[1] = p[1];
        spawn.pos[2] = p[2];
    } else {
        spawn.pos[0] = 0.0f;
        spawn.pos[1] = 0.0f;
        spawn.pos[2] = 0.0f;
    }
    spawn.b24 = 2;
    spawn.b25 = -1;
    spawn.b26 = 1;
    spawn.f1C = arg4;
    spawn.f20 = arg5;
    rec = (u8 *)ground_emitter_spawn(&spawn, life, 0x2C, arg7, arg8);
    if (rec != NULL) {
        memcpy(rec + 0x80, k->extra, 0x2C);
        if (flags & 8) {
            rec[0x80 + 0x28] |= 1;
        }
        if (flags & 0x10) {
            rec[0x80 + 0x28] |= 2;
        }
    }
    if (flags & 4) {
        snd.flags = ((life == -1) ? 0 : 1) | 2;
        snd.b1 = 2;
        snd.life = (life == -1) ? 300 : life;
        snd.b4 = k->bB;
        if (p != NULL) {
            at[0] = p[0];
            at[1] = p[1];
            at[2] = p[2];
        } else {
            at[0] = ((s16 *)owner)[0];
            at[1] = ((s16 *)owner)[1];
            at[2] = ((s16 *)owner)[2];
        }
        light_create_flicker_preset(&snd, at, k->b8, k->b9, k->bA, 0xFF, 0, 0, k->bC, 0xFF, 1);
    }
}

s32 flame_spawn(s32, f32 *, s16, s32, s32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

/* was func_151A9BE4 */
void ground_emitter_spawn_particle(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        f32 u7C;
        s16 u80;
        u8 pad82[0x6];
        f32 u88;
        f32 u8C;
    } sp;
    s32 sp68;
    s32 sp64;
    s32 temp_t1;
    s32 temp_v0;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x80;
    sp.u88 = (random_float() * (*(f32 *)((u8 *)arg0 + 0x88))) + (*(f32 *)((u8 *)arg0 + 0x80));
    sp.u8C = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0xC))) + (*(f32 *)((u8 *)temp_s0 + 4));
    sp.u7C = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x24))) + (*(f32 *)((u8 *)temp_s0 + 0x20));
    sp.u80 = (random_int() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x16)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x14));
    sp64 = random_int();
    temp_t1 = random_int();
    if ((*(u8 *)((u8 *)temp_s0 + 0x28)) & 1) {
        var_t0 = 0x71;
    } else {
        sp68 = temp_t1;
        if (random_int() & 1) {
            var_v0 = 0x13;
        } else {
            var_v0 = 0x14;
        }
        var_t0 = var_v0;
    }
    if ((*(u8 *)((u8 *)temp_s0 + 0x28)) & 2) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = 2;
    }
    temp_v0 = flame_spawn(arg1, &sp.u88, (s16) (((u32) sp64 % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x12)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x10))), (((u32) temp_t1 % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1A)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x18))) & 0xFF, 0, 0.0f, 1.0f, 1.0f, 0x21, 0x23, 2, var_t0, var_v0_2, (s32) (*(s16 *)((u8 *)temp_s0 + 0x1C)), (s32) (*(s16 *)((u8 *)temp_s0 + 0x1E)), 8, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x160, &sp.u7C, 8);
    }
}
void vec2_from_angle_rad(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
typedef void (*Fn9DE4)(f32 *, Obj9DE4 *, s32, u8, s32);
extern Fn9DE4 D_8008FE00[];

/* was func_151A9DE4 */
void ground_scatter_spawn(f32 *arg0, f32 arg1, f32 arg2, Obj9DE4 *arg3, s32 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    Obj9DE4 o;
    f32 pos[3];
    f32 v[3];
    f32 a;

    if (arg3 == NULL) {
        arg3 = &o;
        o.x = 99999.9f;
        o.u18 = 0;
        o.u1C = 7;
        o.u1D = 0;
        o.u20 = 0;
    }
    pos[1] = arg0[1];
    for (; arg4 > 0; arg4--) {
        a = random_float();
        vec2_from_angle_rad(2.0f * a * 3.1415927f, random_float() * arg2, &pos[0], &pos[2]);
        pos[0] += arg0[0];
        pos[2] += arg0[2];
        if (collision_floor_probe(pos, 0, arg1, arg3)) {
            v[0] = pos[0];
            v[1] = arg3->x;
            v[2] = pos[2];
            D_8008FE00[arg5](v, arg3, arg6, arg7, arg8);
        }
    }
}
