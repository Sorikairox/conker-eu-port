extern u8 D_800AA898[]; /* s32[4]: the 4 smoke textures */
extern u8 D_800A5860[]; /* zero vector */
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 func_150ADA20(void);
f32 func_150ADA68(void);

// smoke_puff_spawn: spawns one big smoke puff particle (random texture of the 4 in D_800AA898, half size
// 900..1400, white, alpha 0xFF, 300 frames, fade from 1 at rate 0xFF, draw 6 / update 5, random flip flags 0x40 /
// 0x80) at the object's position +0x38, in its room (+0xC) for its owner (+0x1) through func_151307F0.
void func_151B8EB8(u8 *obj) {
    s32 textures[4];
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
        s32 pos[3];     /* +0x30 */
        s32 angle[3];   /* +0x3C */
        s32 vel[3];     /* +0x48 */
        f32 value;      /* +0x54 */
        s32 flags;      /* +0x58 */
        s32 u5C;
        u8 draw;        /* +0x60 */
        u8 update;      /* +0x61 */
        u8 blend;       /* +0x62 */
        s8 u63;
        s8 u64;
        u8 u65;
        u8 u66;
    } req;
    s32 flipA;
    s32 flipB;
    f32 s;

    textures[0] = ((s32 *) D_800AA898)[0];
    textures[1] = ((s32 *) D_800AA898)[1];
    textures[2] = ((s32 *) D_800AA898)[2];
    textures[3] = ((s32 *) D_800AA898)[3];
    req.texture = textures[func_150ADA20() & 3];
    req.texSet = 0x1303;
    req.handlers = 0x200005;
    req.u04 = 0;
    req.life = 300;
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
    s = func_150ADA68() * 500.0f + 900.0f;
    req.halfH = s;
    req.halfW = s;
    req.pos[0] = *(s32 *) (obj + 0x38);
    req.pos[1] = *(s32 *) (obj + 0x3C);
    req.pos[2] = *(s32 *) (obj + 0x40);
    req.angle[0] = ((s32 *) D_800A5860)[0];
    req.angle[1] = ((s32 *) D_800A5860)[1];
    req.angle[2] = ((s32 *) D_800A5860)[2];
    req.vel[0] = ((s32 *) D_800A5860)[0];
    req.vel[1] = ((s32 *) D_800A5860)[1];
    req.vel[2] = ((s32 *) D_800A5860)[2];
    req.fadeStart = 1;
    req.fadeRate = 0xFF;
    req.u22 = 1;
    req.value = 0.0f;
    req.u24 = 1.0f;
    flipA = (func_150ADA20() & 1) ? 0x40 : 0;
    flipB = (func_150ADA20() & 1) ? 0x80 : 0;
    req.flags = flipB | flipA | 0xC000 | 0x40000 | 0x800000;
    req.draw = 6;
    req.update = 5;
    req.blend = 0xFF;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 0;
    req.u5C = 0;
    req.u66 = 0xFF;
    func_151307F0((s32) &req, 1, 0, 0, obj[0xC], obj[1]);
}
