extern u8 (*D_80090070[])(void);
extern s32 D_800AB710;
extern f32 D_800AB880;
extern f32 D_800AB884;
extern f32 D_800AB888;
extern f32 D_800AB88C;
// splash_ring_spawn: spawns a flat ring effect of kind `type` (texture from D_80090070[type](), life 100) at `pos`
// with half size `size`, alpha `alpha`, through func_1513D2F0 (update handler 0x14, draw 0xE, fade from life 0x20
// at rate 7; flag 0x40000000 when D_800AB710[type]). `lit` picks the light texture set (0x3B vs 0x22 in the high
// byte of +0x1A) and lit vertex colours. On success the effect's +0x110 gets {0, 6..8 random, growth speeds
// (random ranges from D_800AB880..D_800AB88C)}.
void func_151DAB58(u8 type, f32 size, u8 alpha, f32 *pos, u8 lit, u8 room, s32 owner) {
    struct {
        u8 texture;     /* -> effect +0x18 */
        u8 u1;
        s16 u2;         /* (0x3B or 0x22) << 8 | 3 */
        s16 life;       /* +0x1C */
        s32 frame;      /* +0x20 */
        s32 speed;      /* +0x24 */
        u8 color[4];    /* +0x28 */
        f32 halfW;      /* +0x2C */
        f32 halfH;      /* +0x30 */
        s32 pos[3];     /* +0x34 */
        f32 angle[3];   /* +0x40 */
        f32 scale[3];   /* +0x4C */
        s32 flags;      /* +0x58 */
        u8 alpha;       /* +0x5C */
        u8 u45;
        u8 u46;
        u8 u47;
        s32 u48;
        u8 u4C;
        s32 u50;
        s16 fadeStart;  /* +0x6C */
        s16 fadeRate;   /* +0x6E */
    } req;
    struct {
        u8 u0;
        u8 steps;
        f32 growA;
        f32 growB;
    } extra;
    u8 *fx;

    req.texture = D_80090070[type]();
    req.u2 = ((lit ? 0x3B : 0x22) << 8) + 3;
    req.life = 100;
    req.color[2] = 0;
    req.color[1] = 0;
    req.color[0] = 0;
    req.color[3] = 0xFF;
    req.u45 = 0xFF;
    req.alpha = alpha;
    req.pos[0] = ((s32 *)pos)[0];
    req.pos[1] = ((s32 *)pos)[1];
    req.pos[2] = ((s32 *)pos)[2];
    req.flags = (((u8 *)&D_800AB710)[type] ? 0x40000000 : 0) | 0x0CDC0009;
    req.angle[0] = 0.0f;
    req.angle[1] = 0.0f;
    req.angle[2] = 0.0f;
    req.scale[0] = 1.0f;
    req.scale[1] = 1.0f;
    req.scale[2] = 1.0f;
    req.frame = 0;
    req.speed = 0;
    req.halfH = size;
    req.halfW = size;
    req.u46 = 0;
    req.u47 = 7;
    extra.u0 = 0;
    extra.steps = (func_150ADA20() % 3U) + 6;
    extra.growA = func_150ADA68() * D_800AB880 + D_800AB884;
    extra.growB = func_150ADA68() * D_800AB888 + D_800AB88C;
    req.u1 = 0;
    req.u48 = 0;
    req.u4C = 0xFF;
    req.u50 = 0;
    req.fadeStart = 0x20;
    req.fadeRate = 7;
    fx = func_1513D2F0(&req, (s32)&D_800A4AA0, 0, 0x14, 0, 0xE, (func_150ADA20() & 1) | 2, lit ? 3 : 0,
                       lit ? 0xFF : 0, 0xC, room, owner);
    if (fx != NULL) {
        memcpy(fx + 0x110, &extra, 0xC);
    }
}
