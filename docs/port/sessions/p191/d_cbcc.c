void func_15143794(s16, s16, f32, void *);
extern s8 D_800A9400[][5];
/* owner block the debris spawner func_151AC3F0 passes through the burst emitter (argA of the D_8008ADA0 handlers) */
typedef struct {
    s32 src;   /* 0x0 */
    s32 arg;   /* 0x4 */
    u8 light;  /* 0x8 */
} SpawnOwnerACBCC;
/* dust particle definition (D_800A9560, 0x2C bytes, index D_800A9400[kind][3]) */
typedef struct {
    s16 u0;              /* 0x00: not read here */
    s16 u2;              /* 0x02 */
    s16 pitchBase;       /* 0x04 */
    u16 pitchRange;      /* 0x06 */
    f32 speedBase;       /* 0x08 */
    f32 speedRange;      /* 0x0C */
    s16 lifeBase;        /* 0x10 */
    u16 lifeRange;       /* 0x12 */
    u8 alphaBase;        /* 0x14 */
    u8 alphaRange;       /* 0x15 */
    f32 sizeBase;        /* 0x18 */
    f32 sizeRange;       /* 0x1C */
    f32 valBase;         /* 0x20 */
    f32 valRange;        /* 0x24 */
    f32 additiveChance;  /* 0x28 */
} DustDefACBCC;
extern DustDefACBCC D_800A9560[];

// debris_dust_emit: P191: D_8008ADA0 handler 0xC (the dust bursts of debris_burst_spawn func_151AC3F0): spawns one
// dust particle (particle_spawn func_151D9014, kind = the owner's light) at (x, y, z) with the definition
// D_800A9560[D_800A9400[kind][3]]: velocity from func_15143794(yaw = a, random pitch, random speed); random value,
// life, alpha and size from the def ranges; additive with probability additiveChance; grow 1.0 / 1.0, lit, group =
// the owner's src word, no fade, room argB, owner = the owner's arg. Returns 1 (keep emitting).
s32 func_151ACBCC(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 kind,
                  f32 arg9, s32 argA, s32 argB) {
    SpawnOwnerACBCC *owner = (SpawnOwnerACBCC *) argA;
    DustDefACBCC *def = &D_800A9560[D_800A9400[kind][3]];
    f32 pos[3];
    f32 vel[3];
    f32 speed;
    f32 fVal, fSize, fAdd;
    s32 rPitch, rLife, rAlpha;

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    rPitch = func_150ADA20();
    speed = func_150ADA68() * def->speedRange + def->speedBase;
    func_15143794(a, (u32) rPitch % (u32) (def->pitchRange + 1) + def->pitchBase, speed, vel);
    fVal = func_150ADA68();
    rLife = func_150ADA20();
    rAlpha = func_150ADA20();
    fSize = func_150ADA68();
    fAdd = func_150ADA68();
    func_151D9014(pos, vel, owner->light, fVal * def->valRange + def->valBase,
                  (u32) rLife % (u32) (def->lifeRange + 1) + def->lifeBase,
                  (u32) rAlpha % (u32) (def->alphaRange + 1) + def->alphaBase, fSize * def->sizeRange + def->sizeBase,
                  fAdd < def->additiveChance, 1.0f, 1.0f, 1, owner->src, 1, 0, argB & 0xFF, owner->arg);
    return 1;
}
