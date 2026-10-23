s32 func_15132FBC(void *, s32, s32, s32, s32, s32);
// spark_shower_spawn: spawns a spark particle (func_15132FBC, 0x18 extra bytes at +0x170) at pos lasting `time`
// (> 0, else nothing) with brightness `bright` (also its life byte, IDO f32 -> u8 conversion); `flat` != 0 makes it
// a flat spark turning around y (yaw / spin from it), else it gets random angles and a random x / z drift
// (+-4.256). The extra bytes keep time / size / brightness, the fade rate bright / time^2 and the flat flag.
// Returns the particle or 0.
s32 func_15154728(f32 *pos, f32 time, f32 size, f32 bright, f32 flat, u8 arg5, s32 arg6) {
    struct {
        /* extra data copied to particle +0x170 (0x18 bytes) */
        f32 age;
        f32 time;
        f32 size;
        f32 bright;
        f32 fade;
        u8 isFlat;
        u8 pad3D[3];
        /* spawn block for func_15132FBC */
        f32 scaleX;
        f32 scaleY;
        f32 u48;
        f32 flat;
        f32 rot[3];
        f32 scale[3];
        f32 pos[3];
        f32 u74[3];
        f32 vel[3];
        f32 u8C;
        s32 flags;
        s16 u94;
        s16 tex;
        u8 u98;
        u8 pad99[3];
        s32 u9C;
        u8 life;
        u8 uA1;
        u8 uA2;
        u8 uA3;
        u8 uA4;
        u8 uA5;
        u8 uA6;
        u8 uA7;
        u8 uA8;
        u8 padA9;
        u8 uAA;
        u8 padAB;
        s32 uAC;
        u8 uB0;
        u8 padB1;
        s16 uB2;
        s16 uB4;
    } sp;
    s32 p;

    if (time <= 0.0f) {
        return 0;
    }
    sp.age = 0.0f;
    sp.time = time;
    sp.bright = bright;
    sp.size = size;
    sp.fade = bright / (time * time);
    sp.isFlat = (flat != 0.0f) ? 1 : 0;
    sp.u48 = 0.0f;
    sp.flat = flat;
    sp.scaleX = 1.0f;
    sp.scaleY = 1.0f;
    sp.rot[0] = (flat != 0.0f) ? 0.0f : func_150ADA68() * 360.0f;
    sp.rot[1] = func_150ADA68() * 360.0f;
    sp.rot[2] = (flat != 0.0f) ? 0.0f : func_150ADA68() * 360.0f;
    sp.scale[0] = 1.0f;
    sp.scale[1] = 1.0f;
    sp.scale[2] = 1.0f;
    ((s32 *)sp.pos)[0] = ((s32 *)pos)[0];
    ((s32 *)sp.pos)[1] = ((s32 *)pos)[1];
    ((s32 *)sp.pos)[2] = ((s32 *)pos)[2];
    sp.u74[0] = 0.0f;
    sp.u74[1] = 0.0f;
    sp.u74[2] = 0.0f;
    sp.vel[0] = (flat != 0.0f) ? 0.0f : func_150ADA68() * 8.512f + -4.256f;
    sp.vel[1] = (flat != 0.0f) ? func_150ADA68() * 8.512f + -4.256f : 0.0f;
    sp.vel[2] = (flat != 0.0f) ? 0.0f : func_150ADA68() * 8.512f + -4.256f;
    sp.u8C = 0.0f;
    sp.flags = 0x100140;
    sp.tex = 0x54;
    sp.u98 = 0;
    sp.u9C = 0;
    /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
    sp.life = (bright <= -1.0f) ? 0xFF : (u8)(u32)bright;
    sp.uA1 = 0xF;
    sp.uA2 = 0;
    sp.uA3 = 0;
    sp.uA4 = 0;
    sp.uA5 = 0;
    sp.uA6 = 0;
    sp.uA7 = 0;
    sp.uA8 = 2;
    sp.uAA = 0;
    sp.uAC = 0;
    sp.uB0 = 0;
    sp.uB2 = 1;
    sp.uB4 = 0xFF;
    sp.u94 = 300;
    p = func_15132FBC(&sp.scaleX, 0, 0, 0x18, arg5, arg6);
    if (p != 0) {
        memcpy((u8 *)p + 0x170, &sp, 0x18);
    }
    return p;
}
