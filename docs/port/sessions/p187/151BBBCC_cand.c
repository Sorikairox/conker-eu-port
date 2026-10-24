void func_15055A2C(s32, f32, f32, f32, s32);
s32 func_15144E80(s32 *, s32 *, s32 *, s32 *);
void func_151C0AA8(u8 *, u8, s32);
void func_151C0B54(s32, u8, s32);
void func_151C0BA0(void *, u8, s32);
void func_151C0BF4(s32, u8, s32);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, void *, void *, s32, f32);
u8 func_15145C90(s32);
void func_1515016C(void *, u8, s32);
void func_151522DC(void *, s32 *, f32 *, s32, u8, s32);
typedef struct { s16 v[9]; } HitSurface; /* 0x12-byte surface record written by func_150ACEA0 */
/* impact flash keyframes for func_151522DC: frame numbers and scales (rodata D_800AAAF8 / D_800AAB1C) */
static const s32 sImpactFlashFrames[9] = { 4, 4, 7, 8, 0x18, 0x19, 0x1D, 0x1E, 0x20 };
static const f32 sImpactFlashScales[9] = { 1.0f, 1.0f, 0.15f, 0.15f, 1.0f, 1.0f, 0.097f, 1.0f, 0.2f };
// shot_impact_effects: effects of a shot fired from `pos` towards `target` (obj only gates it): sound
// func_15055A2C and the muzzle effects (func_151C0B54 / func_151C0BA0 / func_151C0AA8 / func_151BC494) at pos, then a
// ray cast (func_150ACEA0) along target - pos. On a hit: func_151BC56C when the hit object passes func_15145C90,
// func_151C0BF4 when the surface's third axis points down (func_15144E80), a spark spray off the surface
// (func_1515016C, 3 / 4 particles, range 494) and an animated impact flash (func_151522DC, 9 keyframes).
// Called by func_1506AAE4 (effect handler 2 of func_1506B04C) with D_800D1980 / D_eu_800D1990.
void func_151BBBCC(s32 obj, f32 *pos, f32 *target, u8 arg3, s32 arg4) {
    struct {
        f32 dir[3];
        HitSurface hit;
        f32 range;
        struct {
            s32 count;
            s32 u4;
            f32 pos[3];
            f32 f[6];
            s32 u24;
            s32 u28;
            f32 u2C;
            f32 u30[3];
            s16 s[6];
            s8 u48;
        } p;
    } spray; /* func_1515016C */
    struct {
        s32 u0;
        s32 u4;
        f32 pos[3];
        f32 dir[3];
        HitSurface hit;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
    } flash; /* func_151522DC */
    s32 frames[9];
    f32 scales[9];
    s32 i;
    f32 ax0[3];
    f32 ax1[3];
    f32 ax2[3];
    f32 dir[3];
    f32 hitPos[3];
    HitSurface hit;
    s32 hitObj;
    f32 nx;
    f32 ny;
    f32 nz;

    if (obj == 0) {
        return;
    }
    func_15055A2C(0, pos[0], pos[1], pos[2], 0);
    dir[0] = target[0] - pos[0];
    dir[1] = target[1] - pos[1];
    dir[2] = target[2] - pos[2];
    func_151C0B54((s32) pos, arg3, arg4);
    func_151C0BA0(pos, arg3, arg4);
    func_151C0AA8((u8 *) pos, arg3, arg4);
    func_151BC494((u8 *) pos, arg3, arg4);
    if (func_150ACEA0(pos[0], pos[1], pos[2], dir[0], dir[1], dir[2], 0, &hit, &hitPos[0], &hitPos[1], &hitPos[2],
                      NULL, &hitObj, 0, 0.0f) == 0) {
        return;
    }
    if (func_15145C90(hitObj) != 0) {
        func_151BC56C((s32) &hit, (s32) hitPos, arg3, arg4);
    }
    if (func_15144E80((s32 *) &hit, (s32 *) ax0, (s32 *) ax1, (s32 *) ax2) != 0 && ax2[1] < 0.0f) {
        func_151C0BF4((s32) hitPos, arg3, arg4);
    }
    nx = -dir[0];
    ny = -dir[1];
    nz = -dir[2];

    spray.dir[0] = nx;
    spray.dir[1] = ny;
    spray.dir[2] = nz;
    spray.hit = hit;
    spray.range = 494.0f;
    spray.p.count = 3;
    spray.p.u4 = 4;
    spray.p.pos[0] = hitPos[0];
    spray.p.pos[1] = hitPos[1];
    spray.p.pos[2] = hitPos[2];
    spray.p.f[0] = 0.0609f;
    spray.p.f[1] = 0.0252f;
    spray.p.f[2] = 45.0f;
    spray.p.f[3] = 53.0f;
    spray.p.f[4] = 203.0f;
    spray.p.f[5] = 414.0f;
    spray.p.u24 = 7;
    spray.p.u28 = 3;
    spray.p.u2C = 15.0f;
    spray.p.u30[0] = 0.88000005f;
    spray.p.u30[1] = -0.39800003f;
    spray.p.u30[2] = 0.39100003f;
    spray.p.s[0] = 0x19;
    spray.p.s[1] = 0xF;
    spray.p.s[2] = 0x64;
    spray.p.s[3] = 0x64;
    spray.p.s[4] = 0xC;
    spray.p.s[5] = 0x14;
    spray.p.u48 = 0;
    func_1515016C(&spray, arg3, arg4);

    flash.u0 = 6;
    flash.u4 = 6;
    flash.pos[0] = hitPos[0];
    flash.pos[1] = hitPos[1];
    flash.pos[2] = hitPos[2];
    flash.dir[0] = nx;
    flash.dir[1] = ny;
    flash.dir[2] = nz;
    flash.hit = hit;
    flash.u34 = 456.0f;
    flash.u38 = 0.020000001f;
    flash.u3C = 0.020000001f;
    flash.u40 = -1.71f;
    flash.u44 = 0.448f;
    flash.u48 = 0x32;
    flash.u4A = 0x14;
    flash.u4C = 0.499f;
    flash.u50 = 0.70100003f;
    flash.u54 = 21.502f;
    for (i = 0; i < 9; i++) {
        frames[i] = sImpactFlashFrames[i];
        scales[i] = sImpactFlashScales[i];
    }
    func_151522DC(&flash, frames, scales, 9, arg3, arg4);
}
