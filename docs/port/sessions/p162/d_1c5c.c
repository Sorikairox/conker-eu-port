s32 func_151030B8(u8 *, u8, u8 *, u8 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
extern u8 D_800A1A5C[];    /* [2 variant][4 slot][2 side] f32[3] points */
extern u8 D_800A1B1C[];    /* same layout, second point set */
extern u8 D_800A1BDC[];    /* [2 variant][2 side] bone index */
extern u8 D_800A1BE0[];    /* [2 side] obj + 0x94 flag mask (variant 0) */

// limb_burst_spawn: for side (0 / 1) and slot (0..3) of obj, takes the attachment point of the obj's variant
// (1 when obj[4] == 0x23, else 0 unless the side's flag D_800A1BE0 is set in obj + 0x94: then nothing), moves it to
// world space by the bone matrix, and spawns a flash there (func_151602C0) plus a spray (func_151030B8) along the
// second point set
void func_150F1C5C(u8 *obj, u8 side, u8 slot, u8 flag, s32 arg4) {
    u8 variant;
    u8 *points;
    u8 *bone;
    f32 *src;
    f32 *dst;
    f32 world[3];
    s32 pos[3];
    struct {
        u8 u0;
        s8 u1;
        s16 life;
        u8 u4;
    } flash;
    f32 speed[2];
    s32 r;

    if (obj == NULL || slot >= 4 || side >= 2) {
        return;
    }
    if (obj[4] == 0x23) {
        variant = 1;
    } else {
        if (D_800A1BE0[side] & *(s32 *)(obj + 0x94)) {
            return;
        }
        variant = 0;
    }
    if (*(void **)(obj + 0x1D4) == NULL) {
        return;
    }
    points = D_800A1A5C + variant * 0x60 + slot * 0x18;
    bone = &D_800A1BDC[variant * 2 + side];
    src = (f32 *)(points + side * 0xC);
    dst = world;
    func_15145EA4(&src, &dst, *(u8 **)(obj + 0x1D4) + (*bone << 6), 1);
    flash.u0 = 3;
    flash.u1 = -1;
    flash.life = (u32)func_150ADA20() % 5 + 4;
    flash.u4 = 0;
    pos[0] = world[0];
    pos[1] = world[1];
    pos[2] = world[2];
    func_151602C0((Header *)&flash, (Header2 *)pos, (u32)func_150ADA20() % 51 + 0x50, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                  flag, arg4);
    speed[1] = (func_150ADA68() * 701.0f + 1925.0f) * 0.001f;
    speed[0] = (func_150ADA68() * 1155.0f + 1526.0f) * 0.1f;
    r = func_150ADA20();
    func_150ADA20();
    func_151030B8(obj, *bone, points + side * 0xC,
                  D_800A1B1C + variant * 0x60 + slot * 0x18 + side * 0xC, speed, (u32)r % 6 + 8, 0xFF,
                  func_150ADA68() * 1877.0f + 2414.0f, world, 0xFF, 0, -1, flag, arg4);
}
