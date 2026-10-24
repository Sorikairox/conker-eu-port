extern s32 (*D_80089C14[])(u8 *, s32, u8 *, u8 *); // only entry 0: func_151320EC (reads cfg as arg3)
s32 func_1514672C(f32 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);

// surface_hit_dispatch: when the hit config `cfg` is on (bit 0 of cfg[0]) with a handler (D_80089C14[(s8) cfg[1]],
// -1 = none) and the object (+0x40 / 0x44 / 0x48 x / y / z) is below `other`'s y (+4): probes the point (obj x,
// other y, obj z) (func_1514672C; 0 = outside: returns 0) and the floor down to obj y - 0.06 * obj +0x3C
// (func_15046F70, height into obj + 0x80); on a hit calls the handler with (obj, other, {x, floor height, z}, cfg)
// and returns its low byte. Returns 1 in every other case.
s32 func_15131F34(u8 *obj, u8 *other, u8 *cfg) {
    f32 p[3];
    f32 q[3];

    if (!(cfg[0] & 1) || (s8) cfg[1] == -1 || D_80089C14[(s8) cfg[1]] == NULL) {
        return 1;
    }
    if (!(*(f32 *) (obj + 0x44) < *(f32 *) (other + 4))) {
        return 1;
    }
    p[0] = *(f32 *) (obj + 0x40);
    p[1] = *(f32 *) (other + 4);
    p[2] = *(f32 *) (obj + 0x48);
    if (func_1514672C(p) == 0) {
        return 0;
    }
    if (func_15046F70(p, 0, *(f32 *) (obj + 0x44) - *(f32 *) (obj + 0x3C) * 0.060000002f, (f32 *) (obj + 0x80)) == 0) {
        return 1;
    }
    q[0] = p[0];
    q[1] = *(f32 *) (obj + 0x80);
    q[2] = p[2];
    return D_80089C14[(s8) cfg[1]](obj, (s32) other, (u8 *) q, cfg) & 0xFF;
}
