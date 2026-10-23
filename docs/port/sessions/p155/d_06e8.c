void func_15143794(s16, s16, f32, void *);
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
// particle_spray_spawn: spawns countMin + rand(countRange + 1) particles of def (func_151D9014), each with a random
// direction (yaw / pitch ranges `angles` = {yaw base, yaw range, pitch base, pitch range}) and speed turned into a
// velocity by func_15143794, and random size, life, alpha, spin and two chance flags from def; scale 1.4.
// Returns 0 (the asm leaves v0 unset; the callers ignore it).
s32 func_151506E8(void *angles, void *def, s32 arg2, u8 arg3, s32 arg4) {
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

    n = func_150ADA20() % (u32)(d->countRange + 1) + d->countMin;
    while (n != 0) {
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        f = func_150ADA68();
        func_15143794(r1 % (u32)(a[1] + 1) + a[0], r2 % (u32)(a[3] + 1) + a[2], f * d->speedRange + d->speedMin, vel);
        size = func_150ADA68();
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        spin = func_150ADA68();
        c7 = func_150ADA68();
        cD = func_150ADA68();
        func_151D9014(d, vel, d->kind, size * d->sizeRange + d->sizeMin, r1 % (u32)(d->lifeRange + 1) + d->lifeMin,
                      r2 % (u32)(d->alphaRange + 1) + d->alphaMin, spin * d->spinRange + d->spinMin, c7 < d->chance7,
                      1.4f, 1.4f, 1, arg2, d->b38, cD < d->chanceD, arg3, arg4);
        n--;
    }
    return 0;
}
