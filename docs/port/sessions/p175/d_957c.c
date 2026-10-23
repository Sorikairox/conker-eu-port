u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);
s32 memcpy(s32, u8 *, s32);

// beam_glow_spawn: one glow of a beam (func_151C7B1C): a particle emitter (func_151407D0, kind 0x15, emitter size
/* 0x64) from `from` to `to` in colour r / g / b with the ground id, shadow flag 0x1000000 when `noshadow`; the
 * beam record is stored at the new record's +0x170. Returns the glow record or NULL. */
u8 *func_151C957C(u8 *rec, f32 *from, f32 *to, u8 r, u8 g, u8 b, s32 ground, u8 noshadow, u8 arg8, s32 arg9) {
    struct {
        u8 kind;     /* 0x00 = 0x15 */
        u8 u01;      /* 0x01 = 3 */
        u16 flags;   /* 0x02 = 0x3403 */
        u16 life;    /* 0x04 = 300 */
        u8 pad06[2];
        s32 u08;     /* 0x08 = 0 */
        s32 u0C;     /* 0x0C = 0 */
        u8 rgba[4];  /* 0x10 */
        f32 size[2]; /* 0x14 = 0 */
        f32 from[3]; /* 0x1C */
        f32 to[3];   /* 0x28 */
        f32 scale[3]; /* 0x34 = 1 */
        s32 u40;     /* 0x40 */
        u8 u44[4];   /* 0x44 = FF, FF, 0, 6 */
        s32 ground;  /* 0x48 */
        u8 pad4C[0xC];
    } spawn;
    struct {
        f32 range[4]; /* 0x00: 30.1, 30.1, 40, 40 */
        f32 u10[2];   /* 0x10 = 0 */
        f32 u18;      /* 0x18 = 1 */
        f32 u1C;      /* 0x1C = 0.3 */
        f32 u20;      /* 0x20 = 1e-6 */
        u8 pad24[0x24];
        f32 u48;      /* 0x48 = 1 */
        u8 pad4C[8];
        u8 u54[5];    /* 0x54 = 0 */
        u8 pad59[0xB];
    } emit;
    u8 *glow;

    emit.range[0] = 30.1f;
    emit.range[1] = 30.1f;
    emit.range[2] = 40.0f;
    emit.range[3] = 40.0f;
    emit.u18 = 1.0f;
    emit.u10[0] = 0.0f;
    emit.u10[1] = 0.0f;
    spawn.from[0] = from[0];
    spawn.from[1] = from[1];
    spawn.from[2] = from[2];
    spawn.to[0] = to[0];
    spawn.to[1] = to[1];
    spawn.to[2] = to[2];
    emit.u1C = 0.3f;
    spawn.kind = 0x15;
    spawn.flags = 0x3403;
    spawn.life = 300;
    spawn.u08 = 0;
    spawn.u0C = 0;
    spawn.rgba[0] = r;
    spawn.rgba[3] = 0xFF;
    spawn.size[0] = 0.0f;
    spawn.size[1] = 0.0f;
    spawn.scale[0] = 1.0f;
    spawn.scale[1] = 1.0f;
    spawn.scale[2] = 1.0f;
    spawn.rgba[1] = g;
    spawn.rgba[2] = b;
    spawn.u40 = (noshadow ? 0x1000000 : 0) | 0x24D2006 | 0x40000000;
    spawn.u44[1] = 0xFF;
    spawn.u44[0] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u44[3] = 6;
    spawn.u01 = 3;
    emit.u54[0] = 0;
    emit.u54[1] = 0;
    emit.u54[2] = 0;
    emit.u54[3] = 0;
    emit.u48 = 1.0f;
    emit.u54[4] = 0;
    spawn.ground = ground;
    emit.u20 = 0.000001f;
    glow = func_151407D0(&emit, 0x64, &spawn, 0, 0, 0, 0, 1, arg8, arg9);
    if (glow != NULL) {
        memcpy((s32) (glow + 0x170), (u8 *) &rec, 4);
    }
    return glow;
}
