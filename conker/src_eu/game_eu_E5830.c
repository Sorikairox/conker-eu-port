#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#ifdef NON_MATCHING
void func_15142314(Mtx *arg0, s32 arg1, struct17 *arg2);
f32 func_151423D8(u8 arg0);
void func_15143134(void *arg0, void *arg1, void *arg2);
void func_1515C7B4(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_1504715C(void *out, u8 *obj);
s32 func_15046F70(void *, u16, f32, void *);
void func_1514CBE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB);
s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
void func_15151FA8(u8 *arg0, s32 arg1, s32 arg2);
void func_150B8AA0(f32 *arg0, f32 *arg1, f32 *arg2, u8 arg3, s32 arg4);
void func_150B87B0(f32 *pos, f32 *unused, f32 *dist, f32 *yscale, u8 unused4, s32 unused5);

/* func_150B8020's model-space points (D_800A0100 / D_800A010C / D_800A0118) */
static const f32 sBreakCenter[3] = { 0.0f, 0.0f, 0.0f };
static const f32 sBreakTop[3] = { 0.0f, 83.0f, 0.0f };
static const f32 sBreakSide[3] = { 136.0f, -88.0f, 0.0f };

/* func_150B8020's chunk particle (func_15132FBC request, same layout as game_eu_103160's DebrisParticle) */
typedef struct {
    /* 0x00 */ f32 size;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 sizeX;
    /* 0x0C */ f32 sizeZ;
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 one[3];
    /* 0x28 */ f32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8  u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  alpha;
    /* 0x61 */ u8  u61;
    /* 0x62 */ u8  u62[6];
    /* 0x68 */ u8  u68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  u6A;
    /* 0x6C */ void *owner;
    /* 0x70 */ u8  ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} BreakChunk;

/* func_150B8020's smoke puff request (func_15151FA8, 0x88 bytes) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 sizeA;
    /* 0x10 */ f32 sizeB;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s16 u24[10];
    /* 0x38 */ u8  u38[3];
    /* 0x3C */ s32 u3C[6];
    /* 0x54 */ u8  u54[3];
    /* 0x58 */ s32 u58[9];
    /* 0x7C */ u8  u7C[2];
    /* 0x7E */ u8  pad7E[2];   /* P243: was missing, so u80 / u82 landed at 0x7E / 0x80 */
    /* 0x80 */ s16 u80;
    /* 0x82 */ s16 u82;
    /* 0x84 */ s32 u84;
} BreakSmoke;

// object_break_effects: the effects of a breaking / exploding object `obj` (u8 id `owner`, arg `arg2` passed to
// every spawner): finds its centre, half height and radius (from its model's bones when +0x1D4 is set, else
// func_1515C7B4) and two emit points (bones 4 / 5, or +-20 x / +130 y around +0x14), then spawns a debris burst
// (func_150B87B0), func_150B8AA0's effect, a ground ring under the centre (func_1514CBE8, if the floor is found
// within 2000 below) and, at each emit point, a big tumbling chunk (func_15132FBC) and a smoke puff (func_15151FA8)
// sized by the object's scale +0x14C / +0x150 (P156).
void func_150B8020(u8 *obj, u8 owner, s32 arg2) {
    f32 emit[2][3];
    f32 base[3];
    f32 center[3];
    f32 height;
    f32 radius;
    f32 ratio;
    f32 top[3];
    f32 side[3];
    f32 driftX;
    f32 driftZ;
    f32 ground[3];
    f32 hit[12];
    BreakChunk chunk;
    BreakSmoke smoke;
    Mtx *model;
    f32 sx, sz;
    f32 speed;
    f32 sinA, cosA, sinB, cosB;
    f32 scale;
    s16 a, b;
    s8 i;
    u32 r;

    if (obj == NULL) {
        return;
    }
    model = *(Mtx **)(obj + 0x1D4);
    if (model != NULL) {
        func_15142314(model, 4, (struct17 *)emit[0]);
        func_15142314(*(Mtx **)(obj + 0x1D4), 5, (struct17 *)emit[1]);
        func_15142314(*(Mtx **)(obj + 0x1D4), 0, (struct17 *)base);
    } else {
        base[0] = *(f32 *)(obj + 0x14);
        base[1] = *(f32 *)(obj + 0x18);
        base[2] = *(f32 *)(obj + 0x1C);
        emit[0][0] = base[0] + 20.0f;
        emit[0][1] = base[1] + 130.0f;
        emit[0][2] = base[2];
        emit[1][0] = base[0] - 20.0f;
        emit[1][1] = base[1] + 130.0f;
        emit[1][2] = base[2];
    }
    driftX = func_151423D8(*(u16 *)(obj + 0x76) >> 8);
    driftZ = func_151423D8((*(u16 *)(obj + 0x76) >> 8) + 0x40);
    driftX *= *(f32 *)(obj + 0x3C);
    driftZ *= *(f32 *)(obj + 0x3C);

    if (*(Mtx **)(obj + 0x1D4) != NULL) {
        model = *(Mtx **)(obj + 0x1D4);
        func_15143134((void *)sBreakCenter, center, (u8 *)model + 0x80);
        func_15143134((void *)sBreakTop, top, (u8 *)model + 0x80);
        func_15143134((void *)sBreakSide, side, (u8 *)model + 0x80);
        height = fabsf(center[1] - top[1]);
        radius = sqrtf((side[0] - top[0]) * (side[0] - top[0]) + (side[2] - top[2]) * (side[2] - top[2]));
    } else {
        func_1515C7B4(obj, center, &radius, &height);
    }
    if (radius == 0.0f) {
        ratio = 1.0f;
    } else {
        ratio = height / radius;
    }
    func_150B87B0(center, &height, &radius, &ratio, owner, arg2);
    func_150B8AA0(center, &height, &radius, owner, arg2);

    ground[0] = center[0];
    ground[1] = center[1] + 100.0f;
    ground[2] = center[2];
    func_1504715C(hit, obj);
    if (func_15046F70(ground, 0, center[1] - 2000.0f, hit) != 0) {
        ground[1] = *(f32 *)hit;
        r = func_150ADA20();
        func_1514CBE8(ground[0], ground[1] + 31.0f, ground[2], radius, 0, 0xFF, r % 11 + 30, 0x19, 0, 0.0f, 0, owner);
    }

    /* chunk size from the x / z scale, each clamped to 0.5 .. 1 */
    sx = *(f32 *)(obj + 0x14C);
    if (1.0f < sx) {
        sx = 1.0f;
    }
    if (sx < 0.5f) {
        sx = 0.5f;
    }
    sz = *(f32 *)(obj + 0x150);
    if (1.0f < sz) {
        sz = 1.0f;
    }
    if (sz < 0.5f) {
        sz = 0.5f;
    }
    chunk.size = (28.0f * sz + 28.0f * sx) * 0.5f;
    chunk.u04 = 0.6f;
    chunk.sizeX = 3.0f * sx;
    chunk.sizeZ = 3.0f * sz;
    chunk.rot[0] = *(f32 *)(obj + 0xB8);
    chunk.rot[1] = *(f32 *)(obj + 0x40);
    chunk.rot[2] = *(f32 *)(obj + 0xC4);
    chunk.one[0] = 1.0f;
    chunk.one[1] = 1.0f;
    chunk.one[2] = 1.0f;
    chunk.spinZ = 0.0f;
    chunk.gravity = -1.6f;
    chunk.flags = 0x197D;
    chunk.life = 300;
    chunk.sprite = 0;
    chunk.u58 = 0;
    chunk.u5C = 0;
    chunk.alpha = 0xFF;
    chunk.u61 = 1;
    chunk.u62[0] = 0;
    chunk.u62[1] = 1;
    chunk.u62[2] = 0;
    chunk.u62[3] = 1;
    chunk.u62[4] = 0;
    chunk.u62[5] = 0;
    chunk.u68 = 0;
    chunk.u6A = 0;
    chunk.owner = NULL;
    chunk.ownerId = 0;
    chunk.u72 = 1;
    chunk.u74 = 0xFF;

    for (i = 0; i < 2; i++) {
        speed = func_150ADA68() * 30.0f * *(f32 *)(obj + 0x150) + 10.0f;
        a = func_150ADA20() & 0x7F;
        b = -0x20 - (func_150ADA20() & 0x1F);
        sinA = func_151423D8(a);
        cosA = func_151423D8(a - 0x40);
        sinB = func_151423D8(b);
        cosB = func_151423D8(b - 0x40);
        chunk.pos[0] = emit[i][0];
        chunk.pos[1] = emit[i][1];
        chunk.pos[2] = emit[i][2];
        chunk.vel[0] = speed * sinB * cosA + driftX;
        chunk.vel[1] = -speed * cosB;
        chunk.vel[2] = speed * sinB * sinA + driftZ;
        chunk.spinX = 30.0f - func_150ADA68() * 60.0f;
        chunk.spinY = 30.0f - func_150ADA68() * 60.0f;
        func_15132FBC(&chunk, 3, 2, 0, owner, 0);

        scale = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f / 0.96f;
        smoke.pos[0] = emit[i][0];
        smoke.pos[1] = emit[i][1];
        smoke.pos[2] = emit[i][2];
        smoke.sizeA = 3.0f * scale;
        smoke.sizeB = 3.0f * scale;
        smoke.u14 = 0.6f;
        smoke.u18 = 0.231f;
        smoke.u1C = 15.0f * scale;
        smoke.u20 = 10.0f * scale;
        smoke.u24[0] = 4;
        smoke.u24[1] = 4;
        smoke.u24[2] = 0;
        smoke.u24[3] = 0xFF;
        smoke.u24[4] = -0x3F;
        smoke.u24[5] = 0x4B;
        smoke.u24[6] = 3;
        smoke.u24[7] = 3;
        smoke.u24[8] = 0x32;
        smoke.u24[9] = 0x14;
        smoke.u38[0] = 1;
        smoke.u38[1] = 0x21;
        smoke.u38[2] = 0x48;
        smoke.u3C[0] = 1;
        smoke.u3C[1] = 0;
        smoke.u3C[2] = 0;
        smoke.u3C[3] = 0;
        smoke.u3C[4] = 0;
        smoke.u3C[5] = 0;
        smoke.u54[0] = 0;
        smoke.u54[1] = 0x9B;
        smoke.u54[2] = 0x64;
        smoke.u58[0] = 3;
        smoke.u58[1] = 0xFF;
        smoke.u58[2] = 0;
        smoke.u58[3] = 0x220005;
        smoke.u58[4] = 0x1D0600;
        smoke.u58[5] = 1;
        smoke.u58[6] = 0x3B;
        smoke.u58[7] = 0x80;
        smoke.u58[8] = 0x20;
        smoke.u7C[0] = 0;
        smoke.u7C[1] = 7;
        smoke.u80 = 10;
        smoke.u82 = 0x19;
        smoke.u84 = *(s32 *)(obj + 0x184);
        func_15151FA8((u8 *)&smoke, owner, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E5830/func_150B8020.s")
#endif

#ifdef NON_MATCHING
void func_15143794(s16 yaw, s16 pitch, f32 dist, struct17 *out);
s32 func_1518A930(u8 *arg0, u8 *arg1, f32 arg2, u8 *arg3, u8 *arg4, f32 arg5, f32 arg6, u8 arg7, s16 arg8, u8 arg9, s32 argA, u8 argB, s32 argC);

// debris_burst_spawn: spawns 35..60 tumbling debris pieces (func_1518A930) around `pos`: each at a random
// direction (yaw 0..255, pitch -63..-3) `*dist` away with the height scaled by `*yscale`, random rotation, an
// outward speed of 12.21..30.27 along the same direction, random spin on x / z, size 0.078..0.182, and a life of
// 75..125 ticks. `unused` / `unused4` / `unused5` (func_150B8020 passes height, owner, arg) are not read (P156).
void func_150B87B0(f32 *pos, f32 *unused, f32 *dist, f32 *yscale, u8 unused4, s32 unused5) {
    f32 p[3];
    f32 rot[3];
    f32 vel[3];
    f32 spin[3];
    s32 n;
    s16 yaw;
    s16 pitch;
    f32 size;
    f32 drag;
    u32 r;

    for (n = func_150ADA20() % 26U + 35; n > 0; n--) {
        yaw = (u8)func_150ADA20();
        pitch = func_150ADA20() % 61U - 63;
        func_15143794(yaw, pitch, *dist, (struct17 *)p);
        p[1] *= *yscale;
        p[0] += pos[0];
        p[1] += pos[1];
        p[2] += pos[2];
        rot[0] = func_150ADA68() * 360.0f;
        rot[1] = func_150ADA68() * 360.0f;
        rot[2] = func_150ADA68() * 360.0f;
        func_15143794(yaw, pitch, (func_150ADA68() * 1221.0f + 1806.0f) * 0.01f, (struct17 *)vel);
        spin[1] = 0.0f;
        spin[0] = (func_150ADA68() * 3140.0f + -1570.0f) * 0.01f;
        spin[2] = (func_150ADA68() * 3140.0f + -1570.0f) * 0.01f;
        size = func_150ADA68();
        drag = func_150ADA68();
        r = func_150ADA20();
        func_1518A930((u8 *)p, (u8 *)rot, (size * 104.0f + 78.0f) * 0.001f, (u8 *)vel, (u8 *)spin,
                      (drag * 633.0f + -1064.0f) * 0.001f, 0.94253397f, 1, r % 51 + 75, 0, 0, 0xFF, 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E5830/func_150B87B0.s")
#endif

s32 func_151308E4(void *, s32, s32, u8, s32);
typedef struct {
    s32 x[3];
} V3i_B8AA0;
void func_150B8AA0(f32 *arg0, f32 *arg1, f32 *arg2, u8 arg3, s32 arg4) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        u8 pad9A[10];
    } sp;
    s32 b;
    s32 a;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() % 11U) + 0x23;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 51U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = *arg2 * 20.0f;
    sp.u60 = *arg1 * 20.0f;
    *(V3i_B8AA0 *)sp.u64 = *(V3i_B8AA0 *)arg0;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    sp.u80 = 0.0f;
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    if (func_150ADA20() & 1) {
        b = 0x80;
    } else {
        b = 0;
    }
    sp.u8C = b | 0xE01 | a | 0x8000 | 0x4000;
    sp.u96 = -1;
    sp.u97 = -1;
    sp.u52 = 0x19;
    sp.u54 = 0xA;
    sp.u56 = 0x28;
    sp.u98 = -1;
    sp.u99 = 0;
    sp.u58 = 1.009518f;
    func_151308E4(&sp, 1, 0, arg3, arg4);
}

s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143874(s16, f32, void *, void *);
s32 func_150B8C7C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    f32 scale;
    s32 pad;
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        u8 pad9A[10];
    } sp;
    s32 b;
    s32 obj;
    s32 a;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    scale = 0.917241f;
    sp.u3E = (func_150ADA20() & 0xF) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 71U) + 0x3C;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = ((func_150ADA68() * 15738.0f) + 24699.0f) * 0.01f;
    sp.u64[0] = arg2;
    sp.u64[1] = arg3;
    sp.u64[2] = arg4;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    func_15143874(arg8, ((func_150ADA68() * 154.0f) + 205.0f) * 0.1f, &sp.u7C, &sp.u84);
    sp.u80 = 0.0f;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    if (func_150ADA20() & 1) {
        b = 0x80;
    } else {
        b = 0;
    }
    sp.u8C = b | 0xE05 | a | 0x8000 | 0x4000;
    sp.u96 = 0xA;
    sp.u97 = -1;
    sp.u52 = 0x1C;
    sp.u54 = 9;
    sp.u56 = 0x19;
    sp.u98 = -1;
    sp.u99 = 0;
    sp.u58 = 1.033333f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}
