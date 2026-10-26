#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// bit of a beast
/* spawn zone record (struct_eu_15144598 in game_39750 names only +0x6..+0x15) */
typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 sizeA;   /* radius (round shapes) / half width x (box) */
    /* 0x08 */ s16 height;  /* box / disc: height above y; cylinder: half height is sizeA */
    /* 0x0A */ s16 sizeB;   /* half depth (box) */
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ f32 angle;   /* box yaw in degrees */
    /* 0x14 */ u8 pad14;
    /* 0x15 */ u8 shape;    /* low 2 bits */
} SpawnZone8340;

// spawn_zone_pick_point: a random point of zone `zone` (x / z) and its height range (top / bottom), by the shape
// (+0x15 & 3): 0 = disc: random angle and distance up to sizeA around (x, z), y .. y + height; 1 = sphere-ish: the
// same with the range y - sizeA .. y + sizeA; 2 = box: random offsets within +-sizeA / +-sizeB rotated by `angle`,
// y .. y + height; 3 = no spread: (x, z), y - height .. y + height. Random values are 16 bits of
// osGetCount() * random_int(), scaled by 1 / 65535. The asm returns a leftover v0 that no caller reads.
/* was func_15008340 */
s32 spawn_zone_pick_point(struct_eu_15144598 *arg0, f32 *x, f32 *z, f32 *top, f32 *bottom) {
    SpawnZone8340 *zone = (SpawnZone8340 *) arg0;
    f32 ang;
    f32 s;
    f32 c;
    f32 u;
    f32 w;
    f32 r;
    u32 t;

    switch (zone->shape & 3) {
    case 0:
        t = osGetCount();
        r = (f32) (u16) (random_int() * t) * 1.5259022e-05f;
        ang = (r + r) * 3.1415927f;
        s = sinf(ang);
        c = cosf(ang);
        t = osGetCount();
        r = (f32) (u16) (random_int() * t) * 1.5259022e-05f * zone->sizeA;
        *x = zone->x + r * c;
        *z = zone->z - r * s;
        *top = zone->y + zone->height;
        *bottom = zone->y;
        break;
    case 1:
        t = osGetCount();
        r = (f32) (u16) (random_int() * t) * 1.5259022e-05f;
        ang = (r + r) * 3.1415927f;
        s = sinf(ang);
        c = cosf(ang);
        t = osGetCount();
        r = (f32) (u16) (random_int() * t) * 1.5259022e-05f * zone->sizeA;
        *x = zone->x + r * c;
        *z = zone->z - r * s;
        *top = zone->y + zone->sizeA;
        *bottom = zone->y - zone->sizeA;
        break;
    case 2:
        ang = zone->angle * 0.017453292f;
        s = sinf(ang);
        c = cosf(ang);
        t = osGetCount();
        u = (f32) (u16) (random_int() * t) * 1.5259022e-05f * ((f32) zone->sizeA + (f32) zone->sizeA)
            + (f32) -zone->sizeA;
        t = osGetCount();
        w = (f32) (u16) (random_int() * t) * 1.5259022e-05f * ((f32) zone->sizeB + (f32) zone->sizeB)
            + (f32) -zone->sizeB;
        *x = zone->x + (u * c + w * s);
        *z = zone->z + (w * c - u * s);
        *top = zone->y + zone->height;
        *bottom = zone->y;
        break;
    default:
        *x = zone->x;
        *z = zone->z;
        *top = zone->y + zone->height;
        *bottom = zone->y - zone->height;
        break;
    }
    return 0;
}
