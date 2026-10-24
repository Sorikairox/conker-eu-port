void *allocate_memory(s32, s32, s32, s32);
u8 *func_151149AC(u8 id);
/* P188: IDO's f32 -> u32 conversion kept to a byte: values <= -1 give 0xFFFFFFFF */
#define P188_F2U8(v) (((v) <= -1.0f) ? 0xFF : (u8) (u32) (v))

/*
 * model_light_create: P188: creates a light record (44 bytes, allocate_memory) for the model `id`
 * (func_151149AC: origin s16 +0x10..+0x14, vertex count u16 +0x16, vertices +0x28, 16 bytes each, s16 x / y / z) and
 * appends it to the list D_800DD410 (count D_800DD418). Record: +0 id, +1 flags, +2 another light of the same model
 * was there before, +4 1 / (range * 0.01)^2 (0 for range 0), +8 intensity, +0xC range, +0xE..+0x12 light position
 * relative to the model origin, +0x14 0, +0x16 / +0x17 the two s8 factors, +0x18..+0x1D six colour bytes (kind 1).
 * Per vertex, with d = the vertex distance to the light * 0.01 (flag 0x10: the signed distance along the direction
 * `angle` degrees in the x / z plane): +0x24[i] = scale * d; flag 4: +0x20[i] = falloff * intensity * t^2 when
 * t = d - range * 0.01 is negative, else 0; kind 2: +0x28[i] = the direction byte (flag 0x10: angle * 256 / 360,
 * else func_150484A0 (atan2) of the squared x / z offsets * 128 / pi, as Rare wrote it).
 */
void func_15177410(u8 flags, u8 id, s16 x, s16 y, s16 z, f32 angle, u16 range, f32 intensity, s8 arg8, s8 scale,
                   u8 r0, u8 g0, u8 b0, u8 r1, u8 g1, u8 b1) {
    u8 *light;
    u8 *model;
    u8 found;
    s32 kind;
    s32 dir;
    s32 i, n;
    s32 d, ad, t;
    f32 dx, dy, dz;
    f32 ox, oz;
    f32 k, f;
    f32 s, c;
    u8 dirbyte;
    s16 *v;

    light = allocate_memory(44, 1, 0, 0);
    if (light == NULL) {
        return;
    }
    ((u8 **) D_800DD410)[D_800DD418] = light;
    D_800DD418++;
    model = func_151149AC(id);
    light[1] = flags;
    light[0] = id;
    found = 0;
    n = D_800DD418 - 1;
    for (i = 0; i < n; i++) {
        if (((u8 **) D_800DD410)[i][0] == id) {
            found = 1;
            break;
        }
    }
    light[2] = found;
    dx = (f32) (x - *(s16 *) (model + 0x10));
    dy = (f32) (y - *(s16 *) (model + 0x12));
    dz = (f32) (z - *(s16 *) (model + 0x14));
    kind = flags & 3;
    *(s16 *) (light + 0xE) = (s32) dx;
    *(s16 *) (light + 0x10) = (s32) dy;
    *(u16 *) (light + 0xC) = range;
    *(s16 *) (light + 0x12) = (s32) dz;
    *(s16 *) (light + 0x14) = 0;
    *(f32 *) (light + 8) = intensity;
    *(s8 *) (light + 0x16) = arg8;
    *(s8 *) (light + 0x17) = scale;
    k = 0.01f;
    if (range != 0) {
        f = range * k;
        *(f32 *) (light + 4) = 1.0f / (f * f);
    } else {
        *(f32 *) (light + 4) = 0.0f;
    }
    if (kind == 1) {
        light[0x18] = r0;
        light[0x19] = g0;
        light[0x1A] = b0;
        light[0x1B] = r1;
        light[0x1C] = g1;
        light[0x1D] = b1;
    }
    *(u8 **) (light + 0x24) = allocate_memory(*(u16 *) (model + 0x16), 1, 0, 0);
    if (kind == 2) {
        *(u8 **) (light + 0x28) = allocate_memory(*(u16 *) (model + 0x16), 1, 0, 0);
    }
    if ((flags & 4) == 4) {
        *(f32 **) (light + 0x20) = allocate_memory(*(u16 *) (model + 0x16) * 4, 1, 0, 0);
    }
    dir = flags & 0x10;
    if (dir == 0x10) {
        s = sinf(-angle * 0.017453292f);
        c = cosf(-angle * 0.017453292f);
        dirbyte = P188_F2U8(angle * 0.7111111f);
    }
    for (i = 0; i < *(u16 *) (model + 0x16); i++) {
        v = (s16 *) (*(u8 **) (model + 0x28) + i * 0x10);
        if (dir == 0) {
            ox = v[0] - dx;
            f = v[1] - dy;
            oz = v[2] - dz;
            ox = ox * ox;
            oz = oz * oz;
            d = (s32) (sqrtf(ox + f * f + oz) * k);
            ad = d;
        } else {
            ox = v[0] - dx;
            oz = v[2] - dz;
            oz = -ox * s + oz * c;
            d = (s32) (oz * k);
            ad = (d < 0) ? -d : d;
        }
        (*(u8 **) (light + 0x24))[i] = scale * d;
        if ((flags & 4) == 4) {
            t = (s32) (ad - range * k);
            if (t >= 0) {
                (*(f32 **) (light + 0x20))[i] = 0.0f;
            } else {
                (*(f32 **) (light + 0x20))[i] = *(f32 *) (light + 4) * intensity * (f32) (t * t);
            }
        }
        if (kind == 2) {
            if (dir == 0x10) {
                (*(u8 **) (light + 0x28))[i] = dirbyte;
            } else {
                f = func_150484A0(ox, oz) * 40.743664f;
                (*(u8 **) (light + 0x28))[i] = P188_F2U8(f);
            }
        }
    }
}
