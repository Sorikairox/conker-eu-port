u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);
extern u8 (*D_800900A0)(void); /* kind-0 particle texture picker (func_151D8FE0 in ROM) */

// smoke_emitter_spawn: P181: starts a 30-tick particle emitter (func_151407D0, 0x6C-byte emitter block, owner
// arg6 / arg7) of texture D_800900A0() (life 300, flags 0x2203, kind 3), colour (r, g, b) = (arg2, arg3, arg4)
// alpha 0xFF, size 100 x 100, emit flags 0xCD2002; emitter ranges 160 / 80, rates 0.5, 1, fade 0.7, 1e-6,
// slots -1. The emitter's extra bytes (+0x170) keep obj, its index obj +0x3B, `arg1` and `arg5`. Returns the
// emitter (NULL when none).
u8 *func_150F0448(u8 *obj, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct {
        u8 *obj;
        u8 index;
        u8 arg1;
        s32 arg5;
    } pay;
    struct {
        u8 texture;    /* +0x00 */
        u8 kind;       /* +0x01 */
        s16 flags;     /* +0x02 */
        s16 life;      /* +0x04 */
        s32 u08;
        s32 u0C;
        u8 color[4];   /* +0x10 */
        f32 sizeX;     /* +0x14 */
        f32 sizeY;     /* +0x18 */
        f32 u1C[6];    /* +0x1C */
        f32 u34[3];    /* +0x34 */
        s32 emitFlags; /* +0x40 */
        u8 u44[4];     /* +0x44 */
        s32 u48;
    } spawn;
    struct {
        f32 range[4];  /* +0x00 */
        f32 u10;
        f32 u14;
        f32 u18;
        f32 u1C;
        f32 u20;
        s32 slots[8];  /* +0x24 */
        s32 u44;
        f32 u48;
        s16 u4C[4];
        u8 u54[6];
    } emit;
    u8 *e;

    pay.obj = obj;
    pay.index = obj[0x3B];
    pay.arg1 = arg1;
    pay.arg5 = arg5;
    spawn.texture = D_800900A0();
    spawn.color[3] = 0xFF;
    spawn.emitFlags = 0xCD2002;
    spawn.kind = 3;
    spawn.flags = 0x2203;
    spawn.life = 300;
    spawn.color[0] = arg2;
    spawn.u44[0] = 0xFF;
    spawn.u44[3] = 6;
    emit.slots[6] = -1;
    emit.slots[3] = -1;
    emit.slots[0] = -1;
    emit.slots[4] = -1;
    emit.slots[1] = -1;
    spawn.color[1] = arg3;
    spawn.color[2] = arg4;
    spawn.u08 = 0;
    spawn.u0C = 0;
    spawn.u44[1] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u48 = 0;
    emit.slots[7] = -1;
    emit.slots[2] = -1;
    emit.slots[5] = -1;
    emit.u44 = 0;
    emit.u4C[0] = 0;
    emit.u4C[1] = 0;
    emit.u4C[2] = 0;
    emit.u4C[3] = 0;
    emit.u54[0] = 0xFF;
    emit.u54[1] = 0xFF;
    emit.u54[2] = 0xFF;
    emit.u54[3] = 0xFF;
    emit.u54[4] = 10;
    emit.u54[5] = 0xFF;
    spawn.u34[0] = 1.0f;
    spawn.u34[1] = 1.0f;
    spawn.u34[2] = 1.0f;
    emit.u18 = 1.0f;
    emit.u48 = 1.0f;
    spawn.sizeY = 100.0f;
    spawn.sizeX = 100.0f;
    emit.range[1] = 160.0f;
    emit.range[0] = 160.0f;
    emit.range[3] = 80.0f;
    emit.range[2] = 80.0f;
    spawn.u1C[0] = 0.0f;
    spawn.u1C[1] = 0.0f;
    spawn.u1C[2] = 0.0f;
    spawn.u1C[3] = 0.0f;
    spawn.u1C[4] = 0.0f;
    spawn.u1C[5] = 0.0f;
    emit.u10 = 0.5f;
    emit.u14 = 0.5f;
    emit.u1C = 0.7f;
    emit.u20 = 1e-06f;
    e = func_151407D0(&emit, 0x6C, &spawn, 30, 0, 0, 0, -1, arg6, arg7);
    if (e != NULL) {
        memcpy(e + 0x170, &pay, 12);
    }
    return e;
}
