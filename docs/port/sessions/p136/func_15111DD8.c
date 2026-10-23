void *allocate_memory(s32, s32, s32, s32);
s32 func_150ADA20(void); /* random */
f32 func_150AD78C(f32);  /* sinf */
f32 func_150AD780(f32);  /* cosf */
extern f32 D_800A32F4; /* latitude spread scale */
extern f32 D_800A32F8; /* longitude: centidegrees -> radians */
extern f32 D_800A32FC; /* latitude: degrees -> radians */

/*
 * star_field_generate: allocates the overlay buffer D_800DC2B0 (8000 records of 8 bytes) and fills it with random
 * stars on a sphere of radius 256: longitude (rand % 36000) * D_800A32F8, latitude 89 - sqrt(t) or sqrt(-t) - 89
 * with t = ((rand % 1584400) - 792100) * D_800A32F4 (denser near the horizon). y = (s32) (sin(lat) * 256),
 * r = sqrt(0x10000 - y * y), x = (s32) (sin(lon) * r), z = (s32) (cos(lon) * r); byte +7 = 64 + rand % 191
 * (brightness), byte +6 = rand % 5.
 * Rare quirk kept: each coordinate is converted to float and the record gets the float's upper halfword (the asm
 * stores the value with swc1 and reads it back with lhu), not the integer; STAR_FLOAT_HI16 does that endian-neutrally.
 */
/* the upper halfword of (f32) v, endian-neutral (c: the function's float/word union) */
#define STAR_FLOAT_HI16(c, v) ((c).f = (f32) (v), (u16) ((c).u >> 16))

void func_15111DD8(void) {
    u8 *star;
    s32 i;
    f32 lon, lat, t, r;
    s32 y;
    union {
        f32 f;
        u32 u;
    } c;

    star = allocate_memory(0xFA00, 1, 0, 0);
    D_800DC2B0 = (s32) star;
    for (i = 0; i < 8000; i++, star += 8) {
        lon = (f32) ((u32) func_150ADA20() % 36000U) * D_800A32F8;
        t = (f32) (s32) (((u32) func_150ADA20() % 1584400U) - 792100) * D_800A32F4;
        if (t >= 0.0f) {
            lat = 89.0f - sqrtf(t);
        } else {
            lat = sqrtf(-t) + -89.0f;
        }
        y = (s32) (func_150AD78C(lat * D_800A32FC) * 256.0f);
        *(u16 *) (star + 2) = STAR_FLOAT_HI16(c, y);
        r = sqrtf((f32) (s32) (0x10000 - (u32) (y * y)));
        *(u16 *) (star + 0) = STAR_FLOAT_HI16(c, (s32) (func_150AD78C(lon) * r));
        *(u16 *) (star + 4) = STAR_FLOAT_HI16(c, (s32) (func_150AD780(lon) * r));
        star[7] = (u32) func_150ADA20() % 191U + 0x40;
        star[6] = (u32) func_150ADA20() % 5U;
    }
}
