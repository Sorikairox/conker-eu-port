extern u8 *D_80087000[];
extern u8 D_8009CF9C[];

// object_reach_hit: P179: whether attacker `arg0`'s reach point hits `target`'s hit spheres; the sphere's bone + 1
/* or 0. The point is `reach` (x attacker scale +0x14C) ahead of the attacker, turned by its angles +0xB8 and +0x40
 * (degrees), from its position +0x14. A bounding sphere around the target (radius D_800D1C90[target +4] +0xE x
 * target +0x14C, centre raised by +0x10 x +0x150) is tested first; then the target's sphere list for model kind
 * `kind` (D_80087000[kind], D_8009CF9C[kind] entries of 10 bytes, same layout as func_1508154C: +0 bone, +2 radius,
 * +4 centre in bone space, bone matrices at +0x1D4) with each radius x +0x14C plus `grow` (x attacker scale). The
 * first sphere containing the point wins; unless the target's +0x125 is set the hit is reported to it with
 * func_1505D1C4(target position, `arg5`, the attacker's index in D_800CC2D0, 0, 0, 0). */
s32 func_15081120(s32 arg0, u8 *target, s32 kind, f32 reach, f32 grow, s32 arg5) {
    u8 *att = (u8 *) arg0;
    u8 *type;
    u8 *rec;
    u8 *bones;
    f32 v[3];
    f32 local[3];
    f32 world[3];
    f32 scale;
    f32 angle;
    f32 s;
    f32 c;
    f32 radius;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    s32 count;
    s32 i;

    scale = *(f32 *)(att + 0x14C);
    reach *= scale;
    grow *= scale;
    angle = *(f32 *)(att + 0xB8) * 0.017453292f;
    s = sinf(angle);
    c = cosf(angle);
    v[0] = 0.0f;
    v[1] = -reach * s;
    v[2] = reach * c;
    angle = *(f32 *)(att + 0x40) * 0.017453292f;
    s = sinf(angle);
    c = cosf(angle);
    x = v[2] * s + v[0] * c;
    v[2] = v[2] * c + -v[0] * s;
    v[0] = x;
    v[0] += *(f32 *)(att + 0x14);
    v[1] += *(f32 *)(att + 0x18);
    v[2] += *(f32 *)(att + 0x1C);

    type = (u8 *) D_800D1C90[target[4]];
    radius = (f32) (u32) *(u16 *)(type + 0xE) * *(f32 *)(target + 0x14C);
    height = *(s16 *)(type + 0x10) * *(f32 *)(target + 0x150);
    dx = v[0] - *(f32 *)(target + 0x14);
    dy = v[1] - (*(f32 *)(target + 0x18) + height);
    dz = v[2] - *(f32 *)(target + 0x1C);
    if (radius * radius < dx * dx + dy * dy + dz * dz) {
        return 0;
    }
    count = D_8009CF9C[kind];
    rec = D_80087000[kind];
    bones = *(u8 **)(target + 0x1D4);
    for (i = 0; i < count; i++, rec += 10) {
        local[0] = *(s16 *)(rec + 4);
        local[1] = *(s16 *)(rec + 6);
        local[2] = *(s16 *)(rec + 8);
        func_15143134(local, world, bones + rec[0] * 64);
        dx = v[0] - world[0];
        dy = v[1] - world[1];
        dz = v[2] - world[2];
        radius = (f32) (u32) *(u16 *)(rec + 2) * *(f32 *)(target + 0x14C) + grow;
        if (!(radius * radius < dx * dx + dy * dy + dz * dz)) {
            if (target[0x125] == 0) {
                func_1505D1C4(*(f32 *)(target + 0x14), *(f32 *)(target + 0x18), *(f32 *)(target + 0x1C), arg5,
                              (struct127 *) att - D_800CC2D0, 0, 0, 0);
            }
            return rec[0] + 1;
        }
    }
    return 0;
}
