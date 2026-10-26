extern f32 D_800AAE24[4]; /* the ember emitter's 4 float parameters (D_800AAE24..D_800AAE30) */
s32 func_151530A8(s32 *, u8, s32);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 random_int(void);
f32 random_float(void);

// fire_embers_spawn: the ember burst of a fire at `pos` (room `room`, owner `owner`): an ember emitter
// (func_151530A8, type 5 / 7, 4 parameters from D_800AAE24, sizes 15 / 30, colour block, handlers 0x200005 /
// 0x60600), one glow sprite (func_151307F0: texture 0x2B of set 0x4403, 6..12 frames, half size 106..302, fade from
// 3 at rate 0x55, random flip flags 0x40 / 0x80) and a light flash (light_create_with_ctrl: 6..12 frames, type 5 or 6) at the
// truncated position.
void func_151C384C(void *arg0, u8 room, s32 owner) {
    f32 *pos = arg0;
    struct {
        s32 type;       /* +0x00: 5 */
        s32 subtype;    /* +0x04: 7 */
        f32 pos[3];     /* +0x08 */
        f32 param[4];   /* +0x14: D_800AAE24..30 */
        f32 sizeA;      /* +0x24: 15 */
        f32 sizeB;      /* +0x28: 30 */
        s16 u2C;
        s16 u2E;
        s16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s16 u40;
        u8 u42;
        u8 u43;
        u8 u44;
        u8 u45[4];      /* +0x45 */
        u8 u49[4];
        u8 u4D[4];
        u8 u51[4];
        u8 u55;
        u8 u56;
        u8 u57;
        u8 u58;
        u8 pad59[3];    /* not written */
        s32 handlers;   /* +0x5C: 0x200005 */
        s32 u60;
        s16 u64;
        s16 u66;
        s16 u68;
        u8 u6A;
        u8 pad6B;       /* not written */
        f32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
    } emit;
    struct {
        s32 handlers;   /* +0x00: 0x200005 */
        s32 u04;
        s16 texSet;     /* +0x08 */
        s16 life;       /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 color[4];    /* +0x14 */
        u8 u18[3];
        u8 alpha;       /* +0x1B */
        u8 u1C;
        u8 texture;     /* +0x1D */
        s16 fadeStart;  /* +0x1E */
        s16 fadeRate;   /* +0x20 */
        s16 u22;
        f32 u24;
        f32 halfW;      /* +0x28 */
        f32 halfH;      /* +0x2C */
        f32 pos[3];     /* +0x30 */
        f32 angle[3];   /* +0x3C */
        f32 vel[3];     /* +0x48 */
        f32 value;      /* +0x54 */
        s32 flags;      /* +0x58 */
        s32 u5C;        /* not written */
        u8 draw;        /* +0x60 */
        u8 update;      /* +0x61 */
        s8 blend;       /* +0x62 */
        s8 u63;
        s8 u64;
        u8 u65;
    } req;
    Header flash;
    Header2 at;
    s32 flipA;
    s32 flipB;
    f32 s;
    s32 i;

    emit.type = 5;
    emit.subtype = 7;
    emit.pos[0] = pos[0];
    emit.pos[1] = pos[1];
    emit.pos[2] = pos[2];
    emit.param[0] = D_800AAE24[0];
    emit.param[1] = D_800AAE24[1];
    emit.param[2] = D_800AAE24[2];
    emit.param[3] = D_800AAE24[3];
    emit.sizeA = 15.0f;
    emit.sizeB = 30.0f;
    emit.u2C = 0;
    emit.u2E = 0xFF;
    emit.u30 = -0x40;
    emit.u32 = 0x50;
    emit.u34 = 3;
    emit.u38 = 1;
    emit.u3C = 0x14;
    emit.u3E = 0xF;
    emit.u40 = 1;
    emit.u42 = 4;
    emit.u43 = 2;
    emit.u44 = 3;
    for (i = 0; i < 4; i++) {
        emit.u45[i] = 0xFF;
        emit.u49[i] = 0;
        emit.u4D[i] = 0xFF;
        emit.u51[i] = 0;
    }
    emit.u55 = 0xFF;
    emit.u56 = 0;
    emit.u57 = 3;
    emit.u58 = 0x24;
    emit.handlers = 0x200005;
    emit.u60 = 0x60600;
    emit.u64 = 8;
    emit.u66 = 0x1F;
    emit.u68 = 1;
    emit.u6A = 0;
    emit.u6C = 1.0f;
    emit.u70 = -1;
    emit.u71 = 0;
    emit.u72 = -1;
    emit.u73 = -1;
    func_151530A8((s32 *) &emit, room, owner);

    req.texture = 0x2B;
    req.texSet = 0x4403;
    req.handlers = 0x200005;
    req.u04 = 0x20000;
    req.life = random_int() % 7U + 6;
    req.u0C = 0;
    req.u10 = 0;
    req.color[0] = 0xFF;
    req.color[1] = 0xFF;
    req.color[2] = 0xFF;
    req.color[3] = 0xFF;
    req.u18[0] = 0xFF;
    req.u18[1] = 0xFF;
    req.u18[2] = 0xFF;
    req.alpha = 0xFF;
    req.u1C = 0xFF;
    s = random_float() * 196.0f + 106.0f;
    req.halfH = s;
    req.halfW = s;
    req.pos[0] = pos[0];
    req.pos[1] = pos[1];
    req.pos[2] = pos[2];
    req.fadeStart = 3;
    req.fadeRate = 0x55;
    req.u22 = 1;
    req.angle[0] = 0.0f;
    req.angle[1] = 0.0f;
    req.angle[2] = 0.0f;
    req.vel[0] = 0.0f;
    req.vel[1] = 0.0f;
    req.vel[2] = 0.0f;
    req.value = 0.0f;
    req.u24 = 1.0f;
    flipA = (random_int() & 1) ? 0x40 : 0;
    flipB = (random_int() & 1) ? 0x80 : 0;
    req.flags = (flipB | 1) | flipA | 0xC200;
    req.draw = 6;
    req.update = 6;
    req.blend = -1;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 4;
    func_151307F0((s32) &req, 1, 0, 0, room, owner);

    flash.unk0 = 3;
    flash.unk1 = -1;
    flash.unk2 = random_int() % 7U + 6;
    flash.unk4 = 0;
    at.unk0 = pos[0];
    at.unk4 = pos[1];
    at.unk8 = pos[2];
    light_create_with_ctrl(&flash, &at, (random_int() & 1) + 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, room, owner);
}
