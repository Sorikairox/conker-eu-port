s32 func_150ADA20(void);
f32 func_150ADA68(void);
extern u8 (*D_80090070[])(void);
extern s32 D_800AB710;
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

// particle_spawn: spawns a particle effect of kind `kind` (texture from D_80090070[kind]()) through func_151307F0
// (draw 6, update 8; slot group `group`) at `pos` moving with `vel`, with half size `size` (x 0.7 for the textures
// 0x40 / 0x67), alpha `alpha`, value `arg3` (+0x54 of the request), life `life` + 0x12 frames (fade from 0x12 at rate
// 0xE), or with life -0x63 300 frames (fade from 1 at rate 0xFF, no flag 1). `lit` picks the light texture set
// (0x44 vs 0x22) and flag 0x10000; `additive` the blend 0x21 vs 0x22; flag 0x800000 when D_800AB710[kind]; random
// flip flags 0x40 / 0x80. On success the effect's +0xA8 gets the 0x1C-byte motion block (size, random phases and
// rates, growth (0.2..0.45) x size, `growX` / `growY`, kind, bit 0 unless `noFade`, bit 1 with `spin`). Returns the
// effect (0 when none).
s32 func_151D9014(void *pos, f32 *vel, u8 kind, f32 arg3, s16 life, u8 alpha, f32 size, u8 additive, f32 growX,
                  f32 growY, u8 lit, s32 group, u8 noFade, u8 spin, u8 room, s32 owner) {
    struct {
        f32 size;       /* +0x00 */
        u8 phase[2];    /* +0x04: random */
        u8 rate[2];     /* +0x06: 5..10 */
        f32 grow[2];    /* +0x08 */
        f32 growX;      /* +0x10 */
        f32 growY;      /* +0x14 */
        u8 kind;        /* +0x18 */
        u8 flags;       /* +0x19: bit 0 fade, bit 1 spin */
    } extra;
    struct {
        s32 handlers;   /* +0x00: 0x200005 */
        s32 u04;
        s16 texSet;     /* +0x08: (0x44 or 0x22) << 8 | 3 */
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
        s32 angle[3];   /* +0x3C: zero angles (D_800A5860) */
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
        s16 u68;
        f32 range;      /* +0x6C */
    } req;
    s32 fx;
    s32 flipA;
    s32 flipB;
    f32 s;

    req.texture = D_80090070[kind]();
    req.texSet = ((lit ? 0x44 : 0x22) << 8) + 3;
    req.handlers = 0x200005;
    req.u04 = 0;
    req.u0C = 0;
    req.u10 = 0;
    req.color[0] = 0;
    req.color[1] = 0;
    req.color[2] = 0;
    req.color[3] = 0xFF;
    req.u18[0] = 0;
    req.u18[1] = 0;
    req.u18[2] = 0;
    req.u1C = 0xFF;
    req.alpha = alpha;
    req.pos[0] = ((s32 *) pos)[0];
    req.pos[1] = ((s32 *) pos)[1];
    req.pos[2] = ((s32 *) pos)[2];
    req.angle[0] = ((s32 *) D_800A5860)[0];
    req.angle[1] = ((s32 *) D_800A5860)[1];
    req.angle[2] = ((s32 *) D_800A5860)[2];
    req.vel[0] = ((s32 *) vel)[0];
    req.vel[1] = ((s32 *) vel)[1];
    req.vel[2] = ((s32 *) vel)[2];
    req.u22 = 1;
    req.value = arg3;
    req.u24 = 1.0f;
    flipB = (func_150ADA20() & 1) ? 0x80 : 0;
    flipA = (func_150ADA20() & 1) ? 0x40 : 0;
    req.flags = (((u8 *) &D_800AB710)[kind] ? 0x800000 : 0) | (life != -0x63) | 6 | flipA | flipB | 0xC200 |
                (lit ? 0x10000 : 0);
    if (life == -0x63) {
        req.life = 300;
        req.fadeStart = 1;
        req.fadeRate = 0xFF;
    } else {
        req.life = life + 0x12;
        req.fadeStart = 0x12;
        req.fadeRate = 0xE;
    }
    req.draw = 6;
    req.update = 8;
    req.u64 = -1;
    if (additive) {
        req.blend = 0x21;
    } else {
        req.blend = 0x22;
    }
    req.u63 = -1;
    req.u65 = 0;
    req.u5C = 0;
    req.u66 = 0xFF;
    req.u68 = 0;
    req.range = 10000.0f;

    extra.phase[0] = func_150ADA20();
    extra.phase[1] = func_150ADA20();
    if (req.texture == 0x40 || req.texture == 0x67) {
        s = size * 0.7f;
    } else {
        s = size;
    }
    req.halfW = s;
    extra.size = s;
    req.halfH = s;
    extra.rate[0] = (u32) func_150ADA20() % 6 + 5;
    extra.rate[1] = (u32) func_150ADA20() % 6 + 5;
    extra.grow[0] = (func_150ADA68() * 0.25f + 0.2f) * extra.size;
    extra.grow[1] = (func_150ADA68() * 0.25f + 0.2f) * extra.size;
    extra.growX = growX;
    extra.kind = kind;
    extra.growY = growY;
    extra.flags = (spin ? 2 : 0) | (noFade ? 0 : 1);
    fx = func_151307F0((s32) &req, 1, group, 0x1C, room, owner);
    if (fx != 0) {
        memcpy((u8 *) fx + 0xA8, &extra, 0x1C);
    }
    return fx;
}
