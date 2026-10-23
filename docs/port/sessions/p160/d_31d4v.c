extern u8 D_8008FC88[]; /* 4 colours, 3 bytes each */
typedef struct { u8 b[12]; } Blk12_151A31D4;
s32 func_151A2C9C(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151A3134(f32 *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 *arg5);
void func_151A3180(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, s32 arg5);

// particle_burst_spawn: spawns `count` particles (func_151A2C9C) at pos. For particle i (t = i / count) the
// velocity is a random direction (func_15143794) of random speed up to speedMax, the acceleration comes from
// `accel` (scaled by 1 - t) through func_151A3180 (useDir) or func_151A3134, the colour is one of the 4
// D_8008FC88 colours, about 8% of the particles get 0x19 as extra value (else -1), and the lives / periods are
// random within the given ranges. Returns 0 (the N64 code leaves func_151A2C9C's 0 in v0).
void func_151A31D4(s32 pos, s32 accel, s16 dirA, s16 dirB, f32 accelSpeed, f32 scaleBase, f32 scaleSlope, s32 count,
                  f32 speedMax, f32 arg9, f32 lifeBase, f32 lifeRange, s16 periodBase, s16 periodRange,
                  s16 fadeBase, s16 fadeRange, s16 period2, s16 fade2, s8 arg12, u8 arg13, s32 arg14, u8 useDir) {
    void (*accelFn)(f32 *, s16, s16, f32, f32, f32 *);
    u8 colors[12];
    f32 acc[3];
    f32 vel[3];
    s16 minPeriod;
    s16 period;
    f32 t;
    f32 step;
    f32 lifeRand;
    s32 a;
    s32 b;
    s32 c;
    s32 extra;

    if (useDir != 0) {
        accelFn = (void (*)(f32 *, s16, s16, f32, f32, f32 *))func_151A3180;
    } else {
        accelFn = func_151A3134;
    }
    minPeriod = (period2 < fade2) ? period2 : fade2;
    t = 0.0f;
    step = 1.0f / count;
    for (; count != 0; count--) {
        period = (u32)func_150ADA20() % (periodRange + 1) + periodBase;
        a = func_150ADA20();
        b = func_150ADA20();
        func_15143794((u8)a, (u8)b, func_150ADA68() * speedMax, (s32)vel);
        accelFn((f32 *)accel, dirA, dirB, accelSpeed, t, acc);
        *(Blk12_151A31D4 *)colors = *(Blk12_151A31D4 *)D_8008FC88;
        c = func_150ADA20() & 3;
        lifeRand = func_150ADA68();
        b = func_150ADA20();
        extra = (func_150ADA68() < 0.0802f) ? 0x19 : -1;
        func_151A2C9C((f32 *)pos, vel, acc, arg9, lifeRand * lifeRange + lifeBase, scaleSlope * t + scaleBase,
                      period + minPeriod, (u32)b % (fadeRange + 1) + fadeBase, period2, fade2, extra, arg12,
                      colors[c * 3 + 0], colors[c * 3 + 1], colors[c * 3 + 2], arg13, arg14);
        t += step;
    }

}
