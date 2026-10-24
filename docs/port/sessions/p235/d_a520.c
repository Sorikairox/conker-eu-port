#ifdef NON_MATCHING
/* func_151506E8's spec (same layout as game_2062D0's S06E8). */
typedef struct {
    /* 0x00 */ s16 u0[4];
    /* 0x08 */ struct17 pos;
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ u8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ u8 u38;
    /* 0x39 */ u8 u39;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x44 */ f32 u44;
} RingSpecFA520;

/* func_151307F0's particle request (same layout as game_2062D0's func_151D9014 request). */
typedef struct {
    /* 0x00 */ s32 handlers;
    /* 0x04 */ s32 u04;
    /* 0x08 */ s16 texSet;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 color[4];
    /* 0x18 */ u8 u18[3];
    /* 0x1B */ u8 alpha;
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 texture;
    /* 0x1E */ s16 fadeStart;
    /* 0x20 */ s16 fadeRate;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 halfW;
    /* 0x2C */ f32 halfH;
    /* 0x30 */ s32 pos[3];
    /* 0x3C */ s32 angle[3];
    /* 0x48 */ s32 vel[3];
    /* 0x54 */ f32 value;
    /* 0x58 */ s32 flags;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 draw;
    /* 0x61 */ u8 update;
    /* 0x62 */ u8 blend;
    /* 0x63 */ s8 u63;
    /* 0x64 */ s8 u64;
    /* 0x65 */ u8 u65;
    /* 0x66 */ u8 u66;
    /* 0x68 */ s16 u68;
    /* 0x6C */ f32 range;
} ParticleReqFA520;

void func_15143134(void *arg0, void *arg1, void *arg2);
void func_1504715C(void *, u8 *);
void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
s32 func_151506E8(RingSpecFA520 *, struct17 *, s32, u8, s32);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_151C384C(void *arg0, u8 arg1, s32 arg2);
s32 func_150ADA20(void);
f32 func_150ADA68(void);
void *memcpy(void *, const void *, size_t);
extern struct17 D_800A20CC[]; /* model-space points, indexed by `point` */
extern f32 D_800A2168;
extern f32 D_800A216C;
extern f32 D_800A2170;
extern f32 D_800A2174;
extern f32 D_800A2178;
extern f32 D_800A217C;
extern f32 D_800A2180;
extern f32 D_800A2184;

// object_point_burst_spawn: when `obj` has a matrix list (+0x1D4), takes model point D_800A20CC[point] through
// matrix 5 and spawns there: a func_15154488 burst and a func_151506E8 ring (both clipped to the object's bounds from
// func_1504715C), a glow particle (func_151307F0, texture 0x79, life 300, blend 0x27, random flip flags 0x40 / 0x80,
// alpha = size = 100..200 random) whose +0xA8 gets a 0x14-byte growth block (0, rate 10..13, D_800A2184, size,
// size / rate^2), and func_151C384C at the point. `alpha` / `owner` are passed to every spawner.
void func_150FA520(u8 *obj, u8 point, u8 alpha, s32 owner) {
    struct {
        f32 u00;
        f32 rate;
        f32 u08;
        f32 size;
        f32 accel;
    } extra;
    ParticleReqFA520 req;
    RingSpecFA520 ring;
    struct_eu_15154488 burst;
    s32 bounds[9];
    struct17 pos;
    u8 *mtx;
    s32 fx;
    s32 flipA;
    s32 flipB;
    f32 rate;
    f32 size;

    mtx = *(u8 **)(obj + 0x1D4);
    if (mtx == NULL) {
        return;
    }
    func_15143134(&D_800A20CC[point], &pos, mtx + 0x140);
    func_1504715C(bounds, obj);

    burst.unk8 = pos;
    burst.unk14 = 4.0f;
    burst.unk18 = D_800A2168;
    burst.unk1C = D_800A216C;
    burst.unk20 = D_800A2170;
    burst.unk24 = 12.0f;
    burst.unk28 = D_800A2174;
    burst.unk6 = 0x32;
    burst.unk2C = 9;
    burst.unk2E = 6;
    burst.unk2 = 0xFF;
    burst.unk4 = -0x28;
    burst.unk0 = 0;
    burst.unk30 = 3;
    burst.unk32 = 1;
    burst.unk34 = 0x1E;
    burst.unk36 = 0x32;
    burst.unk38 = 0x64;
    burst.unk3A = 0x64;
    burst.unk44 = 0x10;
    burst.unk46 = 0xF;
    burst.unk48 = 0;
    burst.unk3C = 1;
    burst.unk40 = 1.0f;
    func_15154488(&burst, &burst.unk8, (s32)bounds, alpha, owner);

    ring.pos = pos;
    ring.u18 = 8.0f;
    ring.u1C = 10.0f;
    ring.u24 = D_800A2178;
    ring.u28 = D_800A217C;
    ring.u30 = 123.0f;
    ring.u34 = 104.0f;
    ring.u3C = 1.0f;
    ring.u44 = D_800A2180;
    ring.u0[1] = 0xFF;
    ring.u14 = 7;
    ring.u16 = 6;
    ring.u0[0] = 0;
    ring.u0[2] = -0x3F;
    ring.u0[3] = 0x18;
    ring.u20 = 0x23;
    ring.u22 = 0xB;
    ring.u2C = 0x64;
    ring.u2D = 0x64;
    ring.u38 = 1;
    ring.u39 = 1;
    ring.u40 = 1;
    func_151506E8(&ring, &ring.pos, (s32)bounds, alpha, owner);

    extra.u00 = 0.0f;
    extra.u08 = D_800A2184;
    rate = func_150ADA68() * 3.0f + 10.0f;
    extra.rate = rate;
    size = func_150ADA68() * 100.0f + 100.0f;
    extra.accel = size / (rate * rate);
    req.alpha = (u32)size;
    req.texture = 0x79;
    req.handlers = 0x200005;
    req.texSet = 0x4403;
    req.u04 = 0;
    req.u0C = 0;
    req.u10 = 0;
    req.u18[0] = 0xDC;
    req.u18[1] = 0xDC;
    req.u18[2] = 0xFF;
    req.color[3] = 0xFF;
    req.color[0] = 0xFF;
    req.color[1] = 0xFF;
    req.color[2] = 0xFF;
    req.u1C = 0xFF;
    req.pos[0] = ((s32 *)&pos)[0];
    req.pos[1] = ((s32 *)&pos)[1];
    req.pos[2] = ((s32 *)&pos)[2];
    req.angle[0] = ((s32 *)D_800A5860)[0];
    req.angle[1] = ((s32 *)D_800A5860)[1];
    req.angle[2] = ((s32 *)D_800A5860)[2];
    req.fadeStart = 1;
    req.fadeRate = 0xFF;
    req.u22 = 1;
    extra.size = size;
    req.u24 = 1.0f;
    flipA = (func_150ADA20() & 1) ? 0x40 : 0;
    flipB = (func_150ADA20() & 1) ? 0x80 : 0;
    req.flags = flipB | 0x4C000 | flipA;
    req.draw = 6;
    req.update = 6;
    req.blend = 0x27;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 0;
    req.u5C = 0;
    req.u66 = 0xFF;
    req.vel[0] = ((s32 *)D_800A5860)[0];
    req.vel[1] = ((s32 *)D_800A5860)[1];
    req.vel[2] = ((s32 *)D_800A5860)[2];
    req.life = 300;
    req.halfW = 0.0f;
    req.halfH = 0.0f;
    req.value = 0.0f;
    fx = func_151307F0((s32)&req, 1, 0, 0x14, alpha, owner);
    if (fx != 0) {
        memcpy((u8 *)fx + 0xA8, &extra, 0x14);
    }
    func_151C384C(&pos, alpha, owner);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA520.s")
#endif
