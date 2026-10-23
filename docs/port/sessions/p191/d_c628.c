u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s8 D_800A9400[][5];
extern u8 D_800AB7D4[];
extern u8 D_800AB7E4[];
/* owner block the debris spawner func_151AC3F0 passes through the burst emitter (argA of the D_8008ADA0 handlers) */
typedef struct {
    s32 src;   /* 0x0 */
    s32 arg;   /* 0x4 */
    u8 light;  /* 0x8 */
} SpawnOwnerAC628;
/* chunk particle definition (D_800A9448, 0x30 bytes, index D_800A9400[kind][1]) */
typedef struct {
    u8 colBase;        /* 0x00: colour byte 2 = colBase + random [0, colRange] */
    u8 colRange;       /* 0x01 */
    s16 pitchBase;     /* 0x02: byte angle from vertical */
    u16 pitchRange;    /* 0x04 */
    f32 speedBase;     /* 0x08 */
    f32 speedRange;    /* 0x0C */
    s32 b15Base;       /* 0x10 */
    s32 b15Range;      /* 0x14 */
    s16 lifeBase;      /* 0x18 */
    u16 lifeRange;     /* 0x1A */
    f32 widthBase;     /* 0x1C */
    f32 widthRange;    /* 0x20 */
    f32 v10Base;       /* 0x24 */
    f32 v10Range;      /* 0x28 */
    f32 trailChance;   /* 0x2C */
} ChunkDefAC628;
extern ChunkDefAC628 D_800A9448[];

// debris_chunk_emit: P191: D_8008ADA0 handler 0xB (the chunk bursts of debris_burst_spawn func_151AC3F0, emitted by
// func_1514CBE8 / the ring, line and arc emitters): spawns one chunk particle (func_15148310, update kind 8) at
// (x, y, z) with the definition D_800A9448[D_800A9400[kind][1]]: speed (random in the def range) along the byte angle
// a (x / z) tilted by a random pitch (y = -speed * cos(pitch)); colour bytes D_800AB7D4[light], 0xFF, random; flag
// 0x20 when D_800AB7E4[light]; with probability trailChance flags 3 and the trail args (6, 2). y is also stored in
// the shape (+0x14). The owner block argA gives the owner (src, arg) and the light. Returns 1 (keep emitting).
s32 func_151AC628(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 kind,
                  f32 arg9, s32 argA, s32 argB) {
    SpawnOwnerAC628 *owner = (SpawnOwnerAC628 *) argA;
    ChunkDefAC628 *def = &D_800A9448[D_800A9400[kind][1]];
    struct {
        s32 w[7];   /* 0x00 */
        u8 b1C;
        u8 b1D;
    } style;
    struct {
        f32 width;  /* 0x00 */
        f32 vel[3]; /* 0x04 */
        f32 v10;    /* 0x10 */
        f32 y;      /* 0x14 */
        u8 flags;   /* 0x18 */
        u8 col[3];  /* 0x19 */
    } shape;
    struct {
        f32 x;      /* 0x00 */
        f32 y;
        f32 z;
        s16 life;   /* 0x0C */
        s16 sE;
        s32 s10;
        u8 b14;
        u8 b15;
    } at;
    f32 sinA, cosA, sinP, cosP, speed, hv;
    s32 trailA, trailB;
    s16 pitch;

    sinA = func_151423D8(a & 0xFF);
    cosA = func_151423D8((a - 0x40) & 0xFF);
    style.w[0] = 0;
    style.w[1] = 1;
    style.w[2] = 0x160600;
    style.w[3] = 1;
    style.w[4] = 0x10;
    style.w[5] = 0x80;
    style.w[6] = 0x20;
    style.b1C = 0;
    style.b1D = 9;
    at.s10 = 1;
    at.sE = 1;
    at.y = y;
    shape.y = y;
    at.x = x;
    at.z = z;
    shape.col[0] = D_800AB7D4[owner->light];
    shape.col[1] = 0xFF;
    shape.flags = (D_800AB7E4[owner->light] ? 0x20 : 0) | 8;
    if (func_150ADA68() < def->trailChance) {
        shape.flags |= 3;
        trailA = 6;
        trailB = 2;
    } else {
        trailA = 0;
        trailB = 0;
        shape.flags &= ~3;
    }
    shape.col[2] = (u32) func_150ADA20() % (u32) (def->colRange + 1) + def->colBase;
    pitch = (u32) func_150ADA20() % (u32) (def->pitchRange + 1) + def->pitchBase;
    sinP = func_151423D8(pitch & 0xFF);
    cosP = func_151423D8((pitch - 0x40) & 0xFF);
    speed = func_150ADA68() * def->speedRange + def->speedBase;
    hv = speed * sinP;
    shape.vel[0] = hv * cosA;
    shape.vel[1] = -speed * cosP;
    shape.vel[2] = hv * sinA;
    at.b15 = (u32) func_150ADA20() % (u32) (def->b15Range + 1) + def->b15Base;
    at.life = (u32) func_150ADA20() % (u32) (def->lifeRange + 1) + def->lifeBase;
    shape.width = func_150ADA68() * def->widthRange + def->widthBase;
    shape.v10 = func_150ADA68() * def->v10Range + def->v10Base;
    func_15148310((u8 *) &at, (s32) &shape, 0, 1, 8, 0, trailA, trailB, 0, 0, 0, (u8 *) &style, owner->src, argB & 0xFF,
                  owner->arg);
    return 1;
}
