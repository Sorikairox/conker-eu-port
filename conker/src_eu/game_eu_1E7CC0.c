#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151BC56C(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_151BC494(u8 *arg0, u8 arg1, s32 arg2);
#endif


typedef struct {
    s8 u0;
    s8 u1;
    s8 u2;
    s16 u4;
    s32 u8_;
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    s8 u24;
    s8 u25;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s8 u38;
    u8 u39;
} Sa4b0;
typedef struct {
    u8 *p;
    u8 b;
} Ba4b0;
extern s8 D_800E0FFE[];
u8 *func_1513B5E0(Sa4b0 *, s32, s32, u8, s32);
u8 *func_151BA4B0(u8 *arg0, u8 arg1, s32 arg2)
{
  u8 *ret;
  Sa4b0 s;
  Ba4b0 b;
  s32 idx;
  if (arg0 == 0)
  {
    return 0;
  }
  b.p = arg0;
  b.b = arg0[0x3B];
  s.u0 = 2;
  s.u1 = -1;
  s.u2 = 3;
  s.u4 = 300;
  s.u30 = 9;
  s.u34 = 0x1AD;
  s.u39 = 0xFF;
  idx = (arg0 - ((u8 *) D_800CC2D0)) / 812;
  goto dummy_label_283214; // fakematch: label barrier (permuter) puts sw a0 (b.p) before the arg0[0x3B] load
  dummy_label_283214:
  ;
  if ((idx < 2) && (D_800E0FFE[idx] != 0))
  {
    if (D_80090130 == 2)
    {
      s.u39 = 0xFD;
    }
    else
      if (D_80090130 == 4)
    {
      if (idx == 0)
      {
        s.u39 = 0xFB;
      }
      else
      {
        s.u39 = 0xF7;
      }
    }
  }
  s.u8_ = 1;
  s.uC = 0x200205;
  s.u10 = 0x60600;
  s.u24 = 0;
  s.u25 = 0;
  s.u14 = 1;
  s.u18 = 0x36;
  s.u1C = 0x80;
  s.u20 = 0x20;
  s.u38 = 2;
  ret = func_1513B5E0(&s, 1, 8, arg1, arg2);
  if (ret != 0)
  {
    memcpy((ret + (*((s32 *) (ret + 0x50)))) + ((0, 0xF8)), &b, 8); // fakematch: comma expression (permuter) gives addu a0,v0,t9
  }
  return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BA634.s")

void func_151BAA18(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *q;
  s32 *p;
  s32 id;
  s32 t;
  q = arg0;
  q += *(s32 *)(arg0 + 0x50);
  q += 0xF8;
  p = (s32 *)q;
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if ((t == ((s32 *)arg1)[0]) || (((u8 *) t)[0x3B] == ((u8 *) arg1)[4]))
    {
      func_1516972C((struct102 *)arg0);
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = ((s32 *)arg1)[0];
    if (t == *p)
    {
      p[0] = ((s32 *)arg1)[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
    }
    else if (((s32 *)arg1)[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

#ifdef NON_MATCHING
/* func_15150258 smoke burst request (0x5C bytes): each value is base + random(0..range) */
typedef struct {
    /* 0x00 */ s16 a, aRange;
    /* 0x04 */ s16 b, bRange;
    /* 0x08 */ s32 count, countRange;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 v0, v0Range;
    /* 0x24 */ f32 v1, v1Range;
    /* 0x2C */ f32 v2, v2Range;
    /* 0x34 */ s32 life, lifeRange;
    /* 0x3C */ f32 f3C, f40, f44, f48;
    /* 0x4C */ s16 s4C[6];
    /* 0x58 */ s8 u58;
} SmokeBurst;

/* func_15132BBC particle request (0x7C bytes; +0x34 velocity, +0x50 flags, +0x56 model id) */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 sizeX;
    /* 0x0C */ f32 sizeZ;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 scale[3];
    /* 0x28 */ f32 from[3];        /* launch point on the model (also the scratch for the direction) */
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 model;
    /* 0x58 */ u8  u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  alpha;
    /* 0x61 */ u8  u61;
    /* 0x62 */ u8  u62[6];
    /* 0x68 */ u8  u68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  u6A;
    /* 0x6C */ u8 *owner;
    /* 0x70 */ u8  ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} ShardRequest;

void func_1503F6F4(Mtx *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_1504715C(void *, u8 *);
void func_15150258(u8 *, u8, s32);
u8 *func_15132BBC(u8 *req, s32 nTrails, s32 arg2, s32 *bounds, s32 extraSize, u8 arg5, s32 owner);
/* model-space launch points (rodata of this function, read through the ROM image) */
extern f32 D_800AA970[3];       /* piece 0x27: from / to */
extern f32 D_800AA97C[3];
extern f32 D_800AA988[3];       /* piece 0x28: from, to = one of two */
extern f32 D_800AA994[2][3];
extern f32 D_800AA9AC[4][3];    /* pieces 0x29: from / to / size */
extern f32 D_800AA9DC[4][3];
extern f32 D_800AAA0C[4];
extern f32 D_800AAA1C[3];       /* pieces 0x2B: common from, to, position offset */
extern f32 D_800AAA28[2][3];
extern f32 D_800AAA40[2][3];
extern f32 D_800AAA58[4][3];    /* pieces 0x2C: from / to / position offset / size */
extern f32 D_800AAA88[4][3];
extern f32 D_800AAAB8[4][3];
extern f32 D_800AAAE8[4];

/* random launch speed factor 0.083..0.283 and spin -14.4..14.4 */
#define SHARD_SPEED() ((func_150ADA68() * 200.0f + 83.0f) * 0.001f)
#define SHARD_SPIN() ((func_150ADA68() * 28864.0f + -14432.0f) * 0.001f)

// object_model_shatter: an object's model breaks apart (func_1507D754, a0 = obj, 0xFF, 1): a smoke burst at the
// object (25 above its position) and, when it has a visible model instance (+0x1D4, +0x74 low nibble != 0xF),
// pieces 0x27 .. 0x2C flung from model-space points (transformed by the instance matrix +0x40) towards other
// points, spawned at the model's origin plus an offset, with random speed, life 30..65 and spin. The pieces
// 0x29 / 0x2B / 0x2C are each spawned with a 50 % chance.
void func_151BAAC8(u8 *obj, u8 arg1, s32 arg2) {
    SmokeBurst smoke;
    ShardRequest req;
    s32 bounds[9];
    f32 origin[3];
    f32 rot[3];
    f32 scl[3];
    Mtx *mtx;
    f32 speed;
    s32 i;

    smoke.a = 0;
    smoke.aRange = 0xFF;
    smoke.b = -0x3F;
    smoke.bRange = 0x34;
    smoke.count = 6;
    smoke.countRange = 5 >> ((D_80082FA0 >= 2) ? 1 : 0);
    smoke.pos[0] = *(f32 *)(obj + 0x14);
    smoke.pos[1] = *(f32 *)(obj + 0x18) + 25.0f;
    smoke.pos[2] = *(f32 *)(obj + 0x1C);
    smoke.life = 6;
    smoke.v0 = 50.0f;
    smoke.v0Range = 42.0f;
    smoke.v1 = 98.0f;
    smoke.v1Range = 68.0f;
    smoke.v2 = 609.0f;
    smoke.v2Range = 271.0f;
    smoke.lifeRange = 3 >> ((D_80082FA0 >= 2 || D_8008FD8C >= 8) ? 1 : 0);
    smoke.s4C[0] = 0x19;
    smoke.s4C[1] = 0xF;
    smoke.s4C[2] = 0x64;
    smoke.s4C[3] = 0x64;
    smoke.s4C[4] = 0xC;
    smoke.s4C[5] = 0x14;
    smoke.f3C = 18.0f;
    smoke.f40 = 0.76900005f;
    smoke.f44 = -0.16900001f;
    smoke.f48 = 0.0f;
    smoke.u58 = (D_80082FA0 >= 2 || D_8008FD8C >= 8) ? -1 : 0;
    func_15150258((u8 *)&smoke, arg1, arg2);

    if (*(u8 **)(obj + 0x1D4) == NULL || (obj[0x74] & 0xF) == 0xF) {
        return;
    }
    func_1504715C(bounds, obj);
    mtx = (Mtx *)(*(u8 **)(obj + 0x1D4) + 0x40);
    func_1503F6F4(mtx, &scl[0], &scl[1], &scl[2], &origin[0], &origin[1], &origin[2], &rot[0], &rot[1], &rot[2]);

    req.u00 = 1.0f;
    req.scale[0] = 1.0f;
    req.scale[1] = 1.0f;
    req.scale[2] = 1.0f;
    req.flags = 0x39E9;
    req.u58 = 0;
    req.u5C = 0;
    req.alpha = 0xFF;
    req.u61 = 0xD;
    req.u62[0] = 0;
    req.u62[1] = 0xC;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 2;
    req.u6A = 0;
    req.owner = obj;
    req.u04 = 0.7f;
    req.spinY = 0.0f;
    req.u72 = 0xC;
    req.u74 = 0x15;
    req.ownerId = obj[0x3B];

    /* piece 0x27 */
    speed = SHARD_SPEED();
    req.life = (func_150ADA20() % 36U) + 30;
    req.model = 0x27;
    req.sizeZ = 0.75f;
    req.sizeX = 0.75f;
    func_150ADA68();
    req.gravity = -0.48800004f; /* -488 * 0.001 */
    func_15143134(D_800AA970, req.from, mtx);
    func_15143134(D_800AA97C, req.vel, mtx);
    req.vel[0] = (req.vel[0] - req.from[0]) * speed;
    req.vel[1] = (req.vel[1] - req.from[1]) * speed;
    req.vel[2] = (req.vel[2] - req.from[2]) * speed;
    req.pos[0] = origin[0];
    req.pos[1] = origin[1];
    req.pos[2] = origin[2];
    req.pos[0] += 109.0f;
    req.spinX = SHARD_SPIN();
    req.spinZ = SHARD_SPIN();
    func_15132BBC((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);

    /* piece 0x28: towards one of two points */
    speed = SHARD_SPEED();
    req.life = (func_150ADA20() % 36U) + 30;
    req.model = 0x28;
    req.sizeZ = 0.5f;
    req.sizeX = 0.5f;
    func_150ADA68();
    req.gravity = -0.48800004f;
    func_15143134(D_800AA988, req.from, mtx);
    func_15143134(D_800AA994[func_150ADA20() & 1], req.vel, mtx);
    req.vel[0] = (req.vel[0] - req.from[0]) * speed;
    req.vel[1] = (req.vel[1] - req.from[1]) * speed;
    req.vel[2] = (req.vel[2] - req.from[2]) * speed;
    req.pos[0] = origin[0];
    req.pos[1] = origin[1];
    req.pos[2] = origin[2];
    req.spinX = SHARD_SPIN();
    req.spinZ = SHARD_SPIN();
    func_15132BBC((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);

    /* pieces 0x29 */
    req.model = 0x29;
    for (i = 0; i < 4; i++) {
        if (func_150ADA20() & 1) {
            speed = SHARD_SPEED();
            req.life = (func_150ADA20() % 36U) + 30;
            req.sizeX = D_800AAA0C[i];
            req.sizeZ = D_800AAA0C[i];
            func_150ADA68();
            req.gravity = -0.48800004f;
            func_15143134(D_800AA9AC[i], req.from, mtx);
            func_15143134(D_800AA9DC[i], req.vel, mtx);
            req.vel[0] = (req.vel[0] - req.from[0]) * speed;
            req.vel[1] = (req.vel[1] - req.from[1]) * speed;
            req.vel[2] = (req.vel[2] - req.from[2]) * speed;
            req.pos[0] = origin[0];
            req.pos[1] = origin[1];
            req.pos[2] = origin[2];
            req.spinX = SHARD_SPIN();
            req.spinZ = SHARD_SPIN();
            func_15132BBC((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);
        }
    }

    /* pieces 0x2B: from one common point */
    req.model = 0x2B;
    func_15143134(D_800AAA1C, req.from, mtx);
    req.sizeX = 0.551f;
    req.sizeZ = 0.551f;
    for (i = 0; i < 2; i++) {
        if (func_150ADA20() & 1) {
            speed = SHARD_SPEED();
            req.life = (func_150ADA20() % 36U) + 30;
            func_150ADA68();
            req.gravity = -0.48800004f;
            func_15143134(D_800AAA28[i], req.vel, mtx);
            req.vel[0] = (req.vel[0] - req.from[0]) * speed;
            req.vel[1] = (req.vel[1] - req.from[1]) * speed;
            req.vel[2] = (req.vel[2] - req.from[2]) * speed;
            req.pos[0] = origin[0];
            req.pos[1] = origin[1];
            req.pos[2] = origin[2];
            req.pos[0] += D_800AAA40[i][0];
            req.pos[1] += D_800AAA40[i][1];
            req.pos[2] += D_800AAA40[i][2];
            req.spinX = SHARD_SPIN();
            req.spinZ = SHARD_SPIN();
            func_15132BBC((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);
        }
    }

    /* pieces 0x2C */
    req.model = 0x2C;
    for (i = 0; i < 4; i++) {
        if (func_150ADA20() & 1) {
            speed = SHARD_SPEED();
            req.life = (func_150ADA20() % 36U) + 30;
            req.sizeX = D_800AAAE8[i];
            req.sizeZ = D_800AAAE8[i];
            func_150ADA68();
            req.gravity = -0.48800004f;
            func_15143134(D_800AAA58[i], req.from, mtx);
            func_15143134(D_800AAA88[i], req.vel, mtx);
            req.vel[0] = (req.vel[0] - req.from[0]) * speed;
            req.vel[1] = (req.vel[1] - req.from[1]) * speed;
            req.vel[2] = (req.vel[2] - req.from[2]) * speed;
            req.pos[0] = origin[0];
            req.pos[1] = origin[1];
            req.pos[2] = origin[2];
            req.pos[0] += D_800AAAB8[i][0];
            req.pos[1] += D_800AAAB8[i][1];
            req.pos[2] += D_800AAAB8[i][2];
            req.spinX = SHARD_SPIN();
            req.spinZ = SHARD_SPIN();
            func_15132BBC((u8 *)&req, 3, 0xFF, bounds, 0, arg1, arg2);
        }
    }
}
#undef SHARD_SPEED
#undef SHARD_SPIN
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BAAC8.s")
#endif

extern s32 func_151BB690;

void func_151BB5F4(u8 *arg0) {
    func_1000FA64(0x4A7U, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), 0x2000, 0x320U, 0xC8, (s32) &func_151BB690, arg0, 0, 8, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BB690.s")

#ifdef NON_MATCHING
void func_15055A2C(s32, f32, f32, f32, s32);
s32 func_15144E80(s32 *, s32 *, s32 *, s32 *);
void func_151C0AA8(u8 *, u8, s32);
void func_151C0B54(s32, u8, s32);
void func_151C0BA0(void *, u8, s32);
void func_151C0BF4(s32, u8, s32);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, void *, void *, s32, f32);
u8 func_15145C90(s32);
void func_1515016C(void *, u8, s32);
void func_151522DC(void *, s32 *, f32 *, s32, u8, s32);
typedef struct { s16 v[9]; } HitSurface; /* 0x12-byte surface record written by func_150ACEA0 */
/* impact flash keyframes for func_151522DC: frame numbers and scales (rodata D_800AAAF8 / D_800AAB1C) */
static const s32 sImpactFlashFrames[9] = { 4, 4, 7, 8, 0x18, 0x19, 0x1D, 0x1E, 0x20 };
static const f32 sImpactFlashScales[9] = { 1.0f, 1.0f, 0.15f, 0.15f, 1.0f, 1.0f, 0.097f, 1.0f, 0.2f };
// shot_impact_effects: effects of a shot fired from `pos` towards `target` (obj only gates it): sound
// func_15055A2C and the muzzle effects (func_151C0B54 / func_151C0BA0 / func_151C0AA8 / func_151BC494) at pos, then a
// ray cast (func_150ACEA0) along target - pos. On a hit: func_151BC56C when the hit object passes func_15145C90,
// func_151C0BF4 when the surface's third axis points down (func_15144E80), a spark spray off the surface
// (func_1515016C, 3 / 4 particles, range 494) and an animated impact flash (func_151522DC, 9 keyframes).
// Called by func_1506AAE4 (effect handler 2 of func_1506B04C) with D_800D1980 / D_eu_800D1990.
void func_151BBBCC(s32 obj, f32 *pos, f32 *target, u8 arg3, s32 arg4) {
    struct {
        f32 dir[3];
        HitSurface hit;
        f32 range;
        struct {
            s32 count;
            s32 u4;
            f32 pos[3];
            f32 f[6];
            s32 u24;
            s32 u28;
            f32 u2C;
            f32 u30[3];
            s16 s[6];
            s8 u48;
        } p;
    } spray; /* func_1515016C */
    struct {
        s32 u0;
        s32 u4;
        f32 pos[3];
        f32 dir[3];
        HitSurface hit;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
    } flash; /* func_151522DC */
    s32 frames[9];
    f32 scales[9];
    s32 i;
    f32 ax0[3];
    f32 ax1[3];
    f32 ax2[3];
    f32 dir[3];
    f32 hitPos[3];
    HitSurface hit;
    s32 hitObj;
    f32 nx;
    f32 ny;
    f32 nz;

    if (obj == 0) {
        return;
    }
    func_15055A2C(0, pos[0], pos[1], pos[2], 0);
    dir[0] = target[0] - pos[0];
    dir[1] = target[1] - pos[1];
    dir[2] = target[2] - pos[2];
    func_151C0B54((s32) pos, arg3, arg4);
    func_151C0BA0(pos, arg3, arg4);
    func_151C0AA8((u8 *) pos, arg3, arg4);
    func_151BC494((u8 *) pos, arg3, arg4);
    if (func_150ACEA0(pos[0], pos[1], pos[2], dir[0], dir[1], dir[2], 0, &hit, &hitPos[0], &hitPos[1], &hitPos[2],
                      NULL, &hitObj, 0, 0.0f) == 0) {
        return;
    }
    if (func_15145C90(hitObj) != 0) {
        func_151BC56C((s32) &hit, (s32) hitPos, arg3, arg4);
    }
    if (func_15144E80((s32 *) &hit, (s32 *) ax0, (s32 *) ax1, (s32 *) ax2) != 0 && ax2[1] < 0.0f) {
        func_151C0BF4((s32) hitPos, arg3, arg4);
    }
    nx = -dir[0];
    ny = -dir[1];
    nz = -dir[2];

    spray.dir[0] = nx;
    spray.dir[1] = ny;
    spray.dir[2] = nz;
    spray.hit = hit;
    spray.range = 494.0f;
    spray.p.count = 3;
    spray.p.u4 = 4;
    spray.p.pos[0] = hitPos[0];
    spray.p.pos[1] = hitPos[1];
    spray.p.pos[2] = hitPos[2];
    spray.p.f[0] = 0.0609f;
    spray.p.f[1] = 0.0252f;
    spray.p.f[2] = 45.0f;
    spray.p.f[3] = 53.0f;
    spray.p.f[4] = 203.0f;
    spray.p.f[5] = 414.0f;
    spray.p.u24 = 7;
    spray.p.u28 = 3;
    spray.p.u2C = 15.0f;
    spray.p.u30[0] = 0.88000005f;
    spray.p.u30[1] = -0.39800003f;
    spray.p.u30[2] = 0.39100003f;
    spray.p.s[0] = 0x19;
    spray.p.s[1] = 0xF;
    spray.p.s[2] = 0x64;
    spray.p.s[3] = 0x64;
    spray.p.s[4] = 0xC;
    spray.p.s[5] = 0x14;
    spray.p.u48 = 0;
    func_1515016C(&spray, arg3, arg4);

    flash.u0 = 6;
    flash.u4 = 6;
    flash.pos[0] = hitPos[0];
    flash.pos[1] = hitPos[1];
    flash.pos[2] = hitPos[2];
    flash.dir[0] = nx;
    flash.dir[1] = ny;
    flash.dir[2] = nz;
    flash.hit = hit;
    flash.u34 = 456.0f;
    flash.u38 = 0.020000001f;
    flash.u3C = 0.020000001f;
    flash.u40 = -1.71f;
    flash.u44 = 0.448f;
    flash.u48 = 0x32;
    flash.u4A = 0x14;
    flash.u4C = 0.499f;
    flash.u50 = 0.70100003f;
    flash.u54 = 21.502f;
    for (i = 0; i < 9; i++) {
        frames[i] = sImpactFlashFrames[i];
        scales[i] = sImpactFlashScales[i];
    }
    func_151522DC(&flash, frames, scales, 9, arg3, arg4);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BBBCC.s")
#endif

#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_1504715C(void *, u8 *);
void func_15055A2C(s32, f32, f32, f32, s32);
s32 func_15144E80(s32 *, s32 *, s32 *, s32 *);
void func_15150258(u8 *, u8, s32);
void func_151C0AA8(u8 *, u8, s32);
void func_151C0B54(s32, u8, s32);
void func_151C0BA0(void *, u8, s32);
void func_151C0BF4(s32, u8, s32);
extern s32 D_8008FF40;
extern s32 D_8008FF4C;

void func_151BC04C(s32 arg0, u8 *arg1, u8 *arg2, u8 arg3, s32 arg4) {
    struct {
        s32 u34;
        u8 pad38[0x8];
        s32 u40;
        u8 pad44[0x8];
        s32 u4C;
        s32 u50;
        s32 u54;
        u8 pad58[0x8];
        s16 u60;
        s16 u62;
        s16 u64;
        s16 u66;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        f32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        s32 u8C;
        u8 pad90[0x4];
        s32 u94;
        u8 pad98[0x8];
        s32 uA0;
        u8 padA4[0x8];
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        s32 uC8;
        u8 padCC[0x1C];
        s16 uE8;
        s16 uEA;
        s16 uEC;
        s16 uEE;
        s32 uF0;
        s32 uF4;
        s32 uF8;
        u8 padFC[0x8];
        f32 u104;
        f32 u108;
        f32 u10C;
        f32 u110;
        f32 u114;
        f32 u118;
        s32 u11C;
        s32 u120;
        f32 u124;
        f32 u128;
        f32 u12C;
        f32 u130;
        s16 u134;
        s16 u136;
        s16 u138;
        s16 u13A;
        s16 u13C;
        s16 u13E;
        s8 u140;
        u8 pad141[0x3];
        f32 u144;
        f32 u148;
        f32 u14C;
    } sp;
    s32 var_v0;
    s32 var_v0_2;

    if (arg0 != 0) {
        sp.u144 = ((*(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg2 + 0))) * 0.5f;
        sp.u148 = ((*(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg2 + 4))) * 0.5f;
        sp.u14C = ((*(f32 *)((u8 *)arg1 + 8)) + (*(f32 *)((u8 *)arg2 + 8))) * 0.5f;
        func_151C0AA8(&sp.u144, arg3, arg4);
        func_151C0B54(&sp.u144, arg3, arg4);
        func_151C0BA0(&sp.u144, arg3, arg4);
        func_15055A2C(1, sp.u144, sp.u148, sp.u14C, 0);
        func_151BC494((u8 *) &sp.u144, arg3, arg4);
        sp.uE8 = 0;
        sp.uEA = 0xFF;
        sp.uEC = -0x40;
        sp.uEE = 0x47;
        sp.uF0 = 6;
        if (D_80082FA0 >= 2) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        sp.uF4 = 4 >> var_v0;
        (*(f32 *)((u8 *)(&sp.uF8) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u144) + 0));
        (*(s32 *)((u8 *)(&sp.uF8) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 4));
        (*(s32 *)((u8 *)(&sp.uF8) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 8));
        sp.u11C = 7;
        sp.u104 = 23.0f;
        sp.u108 = 30.0f;
        sp.u10C = 45.0f;
        sp.u110 = 53.0f;
        sp.u114 = 203.0f;
        sp.u118 = 414.0f;
        if ((D_80082FA0 >= 2) || (var_v0_2 = 0, ((D_8008FD8C < 8) == 0))) {
            var_v0_2 = 1;
        }
        sp.u120 = 3 >> var_v0_2;
        sp.u134 = 0x19;
        sp.u136 = 0xF;
        sp.u138 = 0x64;
        sp.u13A = 0x64;
        sp.u13C = 0xC;
        sp.u13E = 0x14;
        sp.u124 = 15.0f;
        sp.u128 = 0.87200004f;
        sp.u12C = -0.39800003f;
        sp.u130 = 0.36400002f;
        if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
            sp.u140 = -1;
        } else {
            sp.u140 = 0;
        }
        func_15150258(&sp.uE8, arg3, arg4);
        func_1504715C(&sp.uC4, arg0);
        sp.uBC = sp.u148 + 100.0f;
        sp.uB8 = sp.u144;
        sp.uC0 = sp.u14C;
        if (func_15046F70(&sp.uB8, 0, sp.u148 - 1000.0f, &sp.uC4) != 0) {
            sp.uAC = sp.uB8;
            sp.uB0 = sp.uC4;
            sp.uB4 = sp.uC0;
            func_151BC56C((s32) &sp.uC8, (s32) &sp.uAC, arg3, arg4);
            if ((func_15144E80(&sp.uC8, &sp.uA0, &sp.u94, &sp.u88) != 0) && (sp.u8C < 0.0f)) {
                func_151C0BF4(&sp.uAC, arg3, arg4);
            }
        }
        (*(s32 *)((u8 *)(&sp.u40) + 0)) = (s32) (*(s32 *)((u8 *)(&D_8008FF40) + 0));
        (*(s32 *)((u8 *)(&sp.u40) + 4)) = (s32) (*(s32 *)((u8 *)(&D_8008FF40) + 4));
        (*(s32 *)((u8 *)(&sp.u40) + 8)) = (s32) (*(s32 *)((u8 *)(&D_8008FF40) + 8));
        (*(s32 *)((u8 *)(&sp.u34) + 0)) = (s32) (*(s32 *)((u8 *)(&D_8008FF4C) + 0));
        (*(s32 *)((u8 *)(&sp.u34) + 4)) = (s32) (*(s32 *)((u8 *)(&D_8008FF4C) + 4));
        (*(s32 *)((u8 *)(&sp.u34) + 8)) = (s32) (*(s32 *)((u8 *)(&D_8008FF4C) + 8));
        sp.u4C = 4;
        sp.u50 = 8;
        (*(f32 *)((u8 *)(&sp.u54) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u144) + 0));
        (*(s32 *)((u8 *)(&sp.u54) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 4));
        (*(s32 *)((u8 *)(&sp.u54) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u144) + 8));
        sp.u68 = 12.0f;
        sp.u6C = 6.0f;
        sp.u60 = 0;
        sp.u62 = 0xFF;
        sp.u64 = -0x3F;
        sp.u66 = 0x57;
        sp.u78 = 0x32;
        sp.u7A = 0xA;
        sp.u70 = -1.4380001f;
        sp.u74 = 0.44900003f;
        sp.u7C = 0.24800001f;
        sp.u80 = 0.09900001f;
        sp.u84 = 22.859001f;
        func_15152700(&sp.u4C, &sp.u40, &sp.u34, 3, 0.0f, 1U, (u8) (s32) arg3, arg4);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC04C.s")
#endif
void func_151BC494(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() & 0xF) + 5;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 21U) + 0x1E, 0xFF, 0x61, 0x36, 0xFFU, 0U, 0, arg1, arg2);
}

#ifdef NON_MATCHING
void func_150E856C(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);
#else
s32 func_150E856C(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);
#endif

void func_151BC56C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = func_150ADA68();
    sp40 = func_150ADA20();
    func_150E856C((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (func_150ADA20() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

struct225 *func_15160CDC(struct127 *arg0, u8 arg1, struct17 *arg2, struct17 *arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, u8 argC, u8 argD, u8 argE, s32 argF);
extern struct17 D_800AAB40;
extern struct17 D_800AAB4C;

void func_151BC624(struct127 *arg0) {
    if (arg0 != NULL) {
        func_15160CDC(arg0, 1, &D_800AAB40, &D_800AAB4C, 0.017699f, 2, 300, 255, 255, 255, 255, 1, 0, 0, 255, 1);
    }
}

#ifdef NON_MATCHING
s32 func_15163414(s8 *, u8 *, u8 *, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800DCE54;

void func_151BC6B4(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s8 u60;
        s8 u61;
        s16 u62;
        s8 u64;
        u8 pad65[0x7];
        u8 * u6C;
        u8 u70;
        u8 pad71[0x3];
        u8 * u74;
        u8 u78;
        u8 pad79[0x3];
        s32 u7C;
        u8 pad80[0x8];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        u8 pad98[0x4];
        s32 u9C;
        f32 uA0;
        f32 uA4;
        s16 uA8;
        s16 uAA;
        s32 uAC;
        u8 padB0[0x1];
        s8 uB1;
        u8 padB2[0x6];
        u8 * uB8;
        u8 uBC;
        u8 padBD[0x3];
        s32 uC0;
        s32 uC4;
        s32 uC8;
        f32 uCC;
        f32 uD0;
        s16 uD4;
        s8 uD6;
        s8 uD7;
        s8 uD8;
        s8 uD9;
    } sp;
    u8 *sp5C;
    u8 *sp58;
    u8 *sp54;
    s32 temp_v0;
    s32 temp_v0_3;
    u8 *temp_v0_2;

    if ((D_80082FA0 < 2) && (D_8008FD8C < 5)) {
        sp.uC0 = arg0 + 0x14;
        sp.uC4 = arg0 + 0x18;
        sp.uC8 = arg0 + 0x1C;
        sp.uD4 = 0x12C;
        sp.uD0 = 0.30339998f * D_800DCE54;
        sp.uD6 = 4;
        sp.uD7 = 4;
        sp.uD8 = 1;
        sp.uD9 = 0;
        sp.uB8 = arg0;
        sp.uCC = 15.0f;
        sp.uBC = (*(u8 *)((u8 *)arg0 + 0x3B));
        temp_v0 = func_15134908((struct_eu_EF410 *) &sp.uC0, 8, arg1, arg2);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x40, &sp.uB8, 8);
        }
    }
    sp.uB1 = 0x28;
    sp.u9C = (*(s32 *)((u8 *)arg0 + 0x14));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x18));
    sp.uA8 = 0x12C;
    sp.uAA = 6;
    sp.uAC = 0xC;
    sp.u74 = arg0;
    sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u78 = (*(u8 *)((u8 *)arg0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 8));
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u94 = -16384.0f;
    sp.u90 = -16384.0f;
    sp54 = arg0 + 0x1C;
    sp58 = arg0 + 0x18;
    sp5C = arg0 + 0x14;
    temp_v0_2 = func_15147FF0(&sp.u9C, 0x28, 0x14, 0xA, 0xA, 0xA, 0, 0, 0, (u8) (s32) arg1, arg2);
    if (temp_v0_2 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0_2 + 0x98)), &sp.u74, 0x24);
    }
    sp.u6C = arg0;
    sp.u60 = 2;
    sp.u61 = 0xE;
    sp.u70 = (*(u8 *)((u8 *)arg0 + 0x3B));
    sp.u62 = 0x12C;
    sp.u64 = 0x1F;
    temp_v0_3 = func_15163414(&sp.u60, sp5C, sp58, sp54, 0, 0, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, 8, (s32) arg1, arg2);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x28, &sp.u6C, 8);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC6B4.s")
#endif
void func_15143794(s16, s16, f32, void *);
#ifdef NON_MATCHING
s32 func_151A2C9C(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */
#else
s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif

void func_151BC920(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    func_15143794((s16) (func_150ADA20() & 0xFF), (s16) ((func_150ADA20() % 65U) - 0x20), func_150ADA68() * 1680.0f * 0.01f, &sp6C[3]);
    temp_f2 = (func_150ADA68() * 202.0f) + 208.0f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = temp_f2 * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
#ifdef NON_MATCHING
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 1.0f, ((func_150ADA68() * 1049.0f) + -1022.0f) * 0.001f, (func_150ADA68() * 124.0f) + 202.0f, (func_150ADA20() & 0xF) + 0x14, (func_150ADA20() % 201U) + 0x37, 0xF, 0xF, 0, -1, 0xCB, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1))); /* P95: float literal (asm passes the bits 0x3F800000) */
#else
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 0x3F800000, ((func_150ADA68() * 1049.0f) + -1022.0f) * 0.001f, (func_150ADA68() * 124.0f) + 202.0f, (func_150ADA20() & 0xF) + 0x14, (func_150ADA20() % 201U) + 0x37, 0xF, 0xF, 0, -1, 0xCB, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
#endif
}

s32 func_151BCB30(s32 **arg0) {
    s32 *temp_v0 = arg0[0x10];

    if (*temp_v0 == 0) {
        return 0;
    }
    return 1;
}

void func_151BCB54(void *arg0, void *arg1, u8 arg2) {
    s32 cur;
    u8 *temp_v0;
    cur = *(s32 *)((u8 *)arg0 + 0x40);
    if (arg2 == 0) {
        if (cur == (*(s32 *)((u8 *)arg1 + 0)) || ((*(u8 *)((u8 *)arg1 + 4)) == (*(u8 *)((u8 *)arg0 + 0x44)))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x40;
        if (arg2 == 0x2D) {
            if (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 0);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}

typedef struct { s32 x[3]; } S12_CBFC;
typedef struct { S12_CBFC pos; s16 t; u8 a; u8 pad[5]; } E20_CBFC;
s32 func_151BCBFC(u8 *arg0) {
    s16 temp_a2;
    s32 temp_lo;
    u8 *temp_v0;
    s32 var_a1;
    u8 *temp_t4;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u16 *)((u8 *)arg0 + 0x1E)) & 8)) {
        return 0;
    }
    var_a1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a1 -= 1;
            if (var_a1 < 0) {
                var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1 = (var_a1 * 0x14) + temp_v0;
            (*(s16 *)((u8 *)temp_v1 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v1 + 0xC)) - D_800BE9E4);
            temp_a2 = (*(s16 *)((u8 *)temp_v1 + 0xC));
            if (temp_a2 < 0) {
                if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
            } else if (temp_a2 < 0xA) {
                temp_lo = temp_a2 * 0x19;
                if (temp_lo < (s32) (*(u8 *)((u8 *)temp_v1 + 0xE))) {
                    (*(u8 *)((u8 *)temp_v1 + 0xE)) = (u8) temp_lo;
                }
            }
        } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(S12_CBFC *)(arg0 + 0x54) = ((E20_CBFC *)temp_v0)[*(s8 *)(arg0 + 0x2D)].pos;
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}

#ifdef NON_MATCHING
f32 func_15143E64(void *);

s32 func_151BCD44(u8 *arg0) {
    struct {
        f32 u6C;
        f32 u70;
        f32 u74;
        u8 pad78[0x10];
        f32 u88;
        f32 u8C;
        f32 u90;
        u8 pad94[0x4];
        s32 u98;
        u8 * u9C;
    } sp;
    f32 sp4C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f14;
    f32 var_f16;
    s8 temp_v1;
    u8 *temp_a2;
    u8 *temp_t3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if (((*(s32 *)((u8 *)temp_v0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_a2 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B)))) {
        (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) | 8);
        return 1;
    }
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    sp.u88 = (*(f32 *)((u8 *)arg0 + 0x10)) - (*(f32 *)((u8 *)temp_a2 + 8));
    sp.u8C = (*(f32 *)((u8 *)arg0 + 0x14)) - (*(f32 *)((u8 *)temp_a2 + 0xC));
    sp.u98 = (*(s32 *)((u8 *)arg0 + 0x94));
    sp.u9C = temp_a2;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x18)) - (*(f32 *)((u8 *)temp_a2 + 0x10));
    temp_f0 = func_15143E64(&sp.u88);
    (*(f32 *)((u8 *)sp.u9C + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.u9C + 0x14)) + (temp_f0 * 0.048708f * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)sp.u9C + 0x14));
    (*(f32 *)((u8 *)sp.u9C + 0x1C)) = (f32) ((*(f32 *)((u8 *)sp.u9C + 0x1C)) + (temp_f0 * 9.708836f));
    sp4C = temp_f2;
    if (temp_f2 > 1.0f) {
        temp_t3 = sp.u9C + 8;
        temp_f0_2 = 1.0f / sp4C;
        (*(f32 *)((u8 *)(&sp.u6C) + 0)) = (*(f32 *)((u8 *)temp_t3 + 0));
        (*(s32 *)((u8 *)(&sp.u6C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t3 + 4));
        var_f16 = (*(f32 *)((u8 *)sp.u9C + 0x18)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.u6C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t3 + 8));
        temp_f2_2 = (*(f32 *)((u8 *)sp.u9C + 0x20));
        var_f14 = temp_f2_2;
        temp_f20 = -(var_f16 * temp_f0_2);
        do {
            temp_v0_2 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x14) + sp.u98;
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u6C) + 0));
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 4));
            (*(s16 *)((u8 *)temp_v0_2 + 0xC)) = 0xC;
            (*(s8 *)((u8 *)temp_v0_2 + 0xE)) = 0x64;
            (*(f32 *)((u8 *)temp_v0_2 + 0x10)) = var_f14;
            (*(s32 *)((u8 *)temp_v0_2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 8));
            if (var_f14 > 16384.0f) {
                do {
                    (*(f32 *)((u8 *)temp_v0_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) - 32768.0f);
                } while ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) > 16384.0f);
            }
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            var_f14 += ((*(f32 *)((u8 *)sp.u9C + 0x1C)) - temp_f2_2) * temp_f0_2;
            sp.u6C += sp.u88 * temp_f0_2;
            sp.u70 += sp.u8C * temp_f0_2;
            var_f16 += temp_f20;
            sp.u74 += sp.u90 * temp_f0_2;
            (*(f32 *)((u8 *)sp.u9C + 0x14)) = (f32) ((*(f32 *)((u8 *)sp.u9C + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)sp.u9C + 0x14)) > 1.0f);
        (*(f32 *)((u8 *)temp_t3 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u6C) + 0));
        (*(s32 *)((u8 *)temp_t3 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 4));
        (*(s32 *)((u8 *)temp_t3 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u6C) + 8));
        (*(f32 *)((u8 *)sp.u9C + 0x20)) = var_f14;
        (*(f32 *)((u8 *)sp.u9C + 0x18)) = var_f16;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BCD44.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD040.s")

void func_151BD7CC(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 *p;
  s32 id;
  s32 t;
  p = *((s32 **) (arg0 + 0x98));
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if ((t == arg1[0]) || (((u8 *) p)[4] == ((u8 *) arg1)[4]))
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      arg0[0x30] = 0;
      *((u16 *) (arg0 + 0x1E)) |= 8;
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = arg1[0];
    if (t == *p)
    {
      p[0] = arg1[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
      return;
    }
    if (arg1[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

s32 func_151BD86C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if (*(s32 *)temp_v0 == 0) {
        return 0;
    }
    if (arg0[0x2C] != temp_v0[0x3B]) {
        return 0;
    }
    return 1;
}

typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} Sd8a8;
s32 func_15134DAC(Sd8a8 *, s32, ...);
void func_151BD8A8(u8 *arg0, s32 arg1, s32 arg2)
{
  Sd8a8 s;
  s16 zp; // fakematch: unused pad, puts z at sp+0x20
  s16 z;
  s32 v;
  if (arg0 != 0)
  {
    s.u0 = arg0[0x3B];
    s.u4 = arg0;
    s.u8_ = 1;
    s.u24 = 0;
    s.u26 = 0x32;
    s.u28 = 0x64;
    s.u2A = 0x12C;
    s.uC = 31.0f;
    s.u2E = 4;
    s.u2F = 4;
    s.u30 = 3;
    s.u38 = 5;
    s.u39 = -1;
    z = 0;
    s.u10 = -34.0f;
    s.u14 = -117.0f;
    s.u18 = 35.0f;
    s.u1C = -24.0f;
    s.u20 = -182.0f;
    s.u34 = 0.30061f;
    v = func_15134DAC(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
    s.uC = -s.uC;
    s.u18 = -s.u18;
    v = func_15134DAC(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
  }
}

s32 func_151BD9DC(s16 *arg0) {
    arg0[0x40] = 0;
    return 1;
}

#ifdef NON_MATCHING
s32 func_151308E4(s32 *, s32, s32, u8, s32);

void func_151BD9EC(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    struct {
        u8 * u38;
        u8 u3C;
        u8 pad3D[0x7];
        u8 * u44;
        s32 u48;
        s32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s16 u66;
        s16 u68;
        s16 u6A;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x4];
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
    } sp;
    s32 sp2C;
    f32 temp_f10;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    if (((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x74)) & 0xF) != 0xF) {
        sp.u65 = 0x29;
        sp.u50 = 0xE03;
        sp.u48 = 0x200005;
        sp.u4C = 0;
        sp.u54 = 0;
        sp.u58 = 0;
        temp_f6 = func_150ADA68() * 251.0f;
        sp.u66 = 0x14;
        sp.u68 = 0xC;
        sp.u9C = (temp_f6 + 44.0f) * 0.001f;
        var_v1 = 0;
        if (func_150ADA20() & 1) {
            var_v1 = 0x40;
        }
        sp2C = var_v1;
        if (func_150ADA20() & 1) {
            var_v0 = 0x80;
        } else {
            var_v0 = 0;
        }
        sp.uA0 = var_v0 | 7 | var_v1 | 0xDE00;
        sp.uA8 = 3;
        sp.uA9 = 3;
        sp.uAB = -1;
        sp.uAC = -1;
        sp.uAD = 7;
        sp.u6A = 0x22;
        sp.u5C = 0xDD;
        sp.u5D = 0xD3;
        sp.u5E = 0xCD;
        sp.u5F = 0xFF;
        sp.u60 = 0x57;
        sp.u61 = 0x55;
        sp.u62 = 0x5A;
        sp.u44 = (u8 *)0x3F6F49BF;
        sp.u6C = 1.034358f;
        sp.u63 = (func_150ADA20() % 156U) + 0x64;
        sp.u64 = 0xFF;
        sp.u52 = (func_150ADA20() % 18U) + 0x19;
        temp_f18 = (func_150ADA68() * 53.0f) + 49.0f;
        sp.u74 = temp_f18;
        sp.u70 = temp_f18;
        temp_f16 = ((*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0))) * (*(f32 *)((u8 *)arg5 + 0x74));
        sp.u90 = temp_f16;
        temp_f10 = ((*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4))) * (*(f32 *)((u8 *)arg5 + 0x74));
        sp.u94 = temp_f10;
        temp_f18_2 = ((*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8))) * (*(f32 *)((u8 *)arg5 + 0x74));
        sp.u98 = temp_f18_2;
        sp.u78 = (*(f32 *)((u8 *)arg0 + 0)) - (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x14));
        sp.u7C = (*(f32 *)((u8 *)arg0 + 4)) - (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x18));
        sp.u80 = (*(f32 *)((u8 *)arg0 + 8)) - (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x1C));
        sp.u78 += temp_f16 * arg4;
        sp.u7C += temp_f10 * arg4;
        sp.u80 += temp_f18_2 * arg4;
        sp.u38 = (*(u8 **)((u8 *)arg5 + 0x1C));
        sp.uAA = 0x13;
        sp.u3C = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x3B));
        sp.u84 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x14));
        sp.u88 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x18));
        sp.u8C = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x1C));
        temp_v0 = func_151308E4(&sp.u48, 1, 0x10, (*(u8 *)((u8 *)arg5 + 0xC)), (s32) (*(u8 *)((u8 *)arg5 + 1)));
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0xA8, &sp.u44, 4);
            memcpy(temp_v0 + 0xB0, &sp.u38, 8);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD9EC.s")
#endif
f32 func_151BDD00(s16 *arg0) {
    s16 temp_v0 = arg0[0x40];
    f32 ret = (f32)temp_v0 * 2 * D_800AAC40 + D_800AAC44;

    arg0[0x40] = temp_v0 + D_800BE9E4;
    return ret;
}

s32 func_15131C7C();

void func_151BDD4C(u8 *arg0, s32 arg1) {   /* P76: a0 / a1 pass through to func_15131C7C */
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0xB0));
    if (((*(s32 *)temp_v0) != 0) && ((*(u8 *)((u8 *)temp_v0 + 4)) != 0xFF)) {
        (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
        (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
        (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    }
    func_15131C7C(arg0, arg1);
}

void func_151BDDA4(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3B);
}

#ifdef NON_MATCHING
/* func_1513D2F0's particle spec and func_151407D0's spawn block (0x58 bytes). */
typedef struct {
    /* 0x00 */ u8 texture;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 texSet;
    /* 0x04 */ s16 life;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ f32 halfW;
    /* 0x18 */ f32 halfH;
    /* 0x1C */ s32 angle[3];
    /* 0x28 */ s32 vel[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 flags;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ s32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x4D */ u8 pad4D[0xB];
} PartSpecBDDD8;

/* func_151407D0's emitter block (filled up to 0x5A; the call passes size 0x78). */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 u24[8];
    /* 0x44 */ s32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ s16 u4C[4];
    /* 0x54 */ u8 u54[4];
    /* 0x58 */ u8 u58;
    /* 0x59 */ s8 u59;
    /* 0x5A */ u8 pad5A[2];
} EmitBDDD8;

/* 0x5C bytes copied to each particle's +0x110. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x05 */ u8 index;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 scale[4];
    /* 0x50 */ u8 *group;
    /* 0x54 */ f32 midY;
    /* 0x58 */ u8 u58;
} PartExtraBDDD8;

/* 0x18 bytes copied to each emitter's +0x170. */
typedef struct {
    /* 0x00 */ s16 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ u8 *group;
    /* 0x0C */ u8 index;
    /* 0x10 */ u8 *obj;
    /* 0x14 */ u8 room;
} EmitExtraBDDD8;

/* 0x18 bytes copied to the group object's +0x28; the effects are recorded in it. */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 room;
    /* 0x08 */ u8 *part[2];
    /* 0x10 */ u8 *emit[2];
} GroupBDDD8;

struct260 *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9);
s32 func_150ADA20(void);
extern s32 D_800A4AA0;

// object_aura_burst_spawn: the func_150F9BB0 (object_aura_spawn) effect without its func_151D8E18 / func_15160A58 calls: creates
// a group object (func_15149130 kind 300, flag 0, 0x18-byte block {obj, obj+0x3B}) and, when it exists, two particles
// (func_1513D2F0 texture 0x5F, D_800A4AA0 list, random blend 1 / 3; +0x110 gets index, object, room, group, mid height
// (obj +0x14C + +0x150) / 2 and this function's constants) and two emitters (func_151407D0 texture 0x60, 0x2A; +0x170
// gets index, object, room, group); the group records them at +0x30 / +0x38. `alpha` / `owner` go to every spawner.
s32 func_151BDDD8(u8 *obj, u8 alpha, s32 owner) {
    EmitExtraBDDD8 ee;
    PartSpecBDDD8 spawn;
    struct {
        EmitBDDD8 emit; /* func_151407D0 reads 0x78 bytes: on into spec */
        PartSpecBDDD8 spec;
        PartExtraBDDD8 extra; /* kept next to spec as in the asm frame */
    } fr;
    GroupBDDD8 init;
    u8 *group;
    GroupBDDD8 *g;

    init.obj = obj;
    init.room = obj[0x3B];
    init.part[0] = NULL;
    init.part[1] = NULL;
    init.emit[0] = NULL;
    init.emit[1] = NULL;
    group = (u8 *)func_15149130(300, -1, 0x40, -1, 0, 0x33, (struct37 *)0x18, alpha, owner);
    if (group != NULL) {
        g = (GroupBDDD8 *)(group + 0x28);
        memcpy((u8 *)g, (u8 *)&init, 0x18);

        fr.extra.u58 = 0;
        fr.extra.obj = obj;
        fr.extra.midY = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
        fr.extra.u08 = 15.045272f;
        fr.extra.u10 = 5.8676558f;
        fr.extra.u18 = 12.111444f;
        fr.extra.u0C = 0.396174f;
        fr.extra.room = obj[0x3B];
        fr.extra.u24 = 0.0f;
        fr.extra.u28 = 0.0f;
        fr.extra.u38 = 0.0f;
        fr.spec.halfW = 0.0f;
        fr.spec.halfH = 0.0f;
        fr.extra.u3C = 0.0f;
        fr.extra.scale[2] = 1.0f;
        fr.extra.scale[0] = 1.0f;
        fr.extra.scale[3] = 1.0f;
        fr.extra.scale[1] = 1.0f;
        fr.spec.texture = 0x5F;
        fr.spec.u01 = 8;
        fr.spec.texSet = 0x2203;
        fr.spec.life = 300;
        fr.spec.u08 = 0;
        fr.spec.u0C = 0;
        fr.spec.color[0] = 0xFF;
        fr.spec.color[1] = 0xFF;
        fr.spec.color[2] = 0xFF;
        fr.spec.color[3] = 0xFF;
        fr.extra.u14 = 0.1042563f;
        fr.extra.u20 = 0.5197371f;
        fr.extra.u1C = 0.34404588f;
        fr.extra.u2C = 160.0f;
        fr.extra.u30 = 95.0f;
        fr.extra.u34 = 207.5f;
        fr.extra.group = group;
        fr.spec.angle[0] = ((s32 *)D_800A5860)[0];
        fr.spec.angle[1] = ((s32 *)D_800A5860)[1];
        fr.spec.angle[2] = ((s32 *)D_800A5860)[2];
        fr.spec.vel[0] = ((s32 *)D_800A5860)[0];
        fr.spec.vel[1] = ((s32 *)D_800A5860)[1];
        fr.spec.vel[2] = ((s32 *)D_800A5860)[2];
        fr.spec.scale[0] = 1.0f;
        fr.spec.scale[1] = 1.0f;
        fr.spec.scale[2] = 1.0f;
        fr.spec.flags = 0x40EC0000;
        fr.spec.u44 = 0;
        fr.spec.u45 = 0xFF;
        fr.spec.u46 = 0;
        fr.spec.u47 = 7;
        fr.spec.u48 = 0;
        for (fr.extra.index = 0; fr.extra.index < 2; fr.extra.index++) {
            g->part[fr.extra.index] = func_1513D2F0(&fr.spec, (s32)&D_800A4AA0, 0, 0x25, 0, 0x1D,
                                              ((func_150ADA20() & 1) ? 2 : 0) + 1, 0, 0, 0x5C,
                                              alpha, owner);
            if (g->part[fr.extra.index] != NULL) {
                memcpy(g->part[fr.extra.index] + 0x110, (u8 *)&fr.extra, 0x5C);
            }
        }

        ee.u00 = 0;
        ee.u04 = 1.0f;
        ee.obj = obj;
        ee.group = group;
        ee.room = obj[0x3B];
        fr.emit.u24[0] = -1;
        fr.emit.u24[4] = -1;
        fr.emit.u24[1] = -1;
        fr.emit.u24[5] = -1;
        fr.emit.u24[2] = -1;
        fr.emit.u24[6] = -1;
        fr.emit.u24[3] = -1;
        fr.emit.u24[7] = -1;
        fr.emit.u59 = -1;
        fr.emit.u00 = 50.3f;
        fr.emit.u04 = 50.3f;
        fr.emit.u08 = 30.9f;
        fr.emit.u0C = 30.9f;
        fr.emit.u10 = 0.1f;
        fr.emit.u14 = 0.1f;
        fr.emit.u18 = 1.0f;
        fr.emit.u44 = 0;
        fr.emit.u48 = 1.0f;
        fr.emit.u4C[0] = 0;
        fr.emit.u4C[1] = 0;
        fr.emit.u4C[2] = 0;
        fr.emit.u4C[3] = 0;
        fr.emit.u54[0] = 0;
        fr.emit.u54[1] = 0;
        fr.emit.u54[2] = 0;
        fr.emit.u54[3] = 0;
        fr.emit.u58 = 0xF;
        spawn.texture = 0x60;
        spawn.u01 = 3;
        spawn.texSet = 0x2203;
        spawn.life = 300;
        spawn.u08 = 0;
        spawn.u0C = 0;
        spawn.color[0] = 0xFF;
        spawn.color[1] = 0xFF;
        spawn.color[2] = 0xFF;
        spawn.color[3] = 0xFF;
        spawn.halfW = 100.0f;
        spawn.halfH = 100.0f;
        fr.emit.u1C = 0.7f;
        fr.emit.u20 = 1e-06f;
        spawn.angle[0] = ((s32 *)D_800A5860)[0];
        spawn.angle[1] = ((s32 *)D_800A5860)[1];
        spawn.angle[2] = ((s32 *)D_800A5860)[2];
        spawn.vel[0] = ((s32 *)D_800A5860)[0];
        spawn.vel[1] = ((s32 *)D_800A5860)[1];
        spawn.vel[2] = ((s32 *)D_800A5860)[2];
        spawn.scale[0] = 1.0f;
        spawn.scale[1] = 1.0f;
        spawn.scale[2] = 1.0f;
        spawn.flags = 0xCD2002;
        spawn.u44 = 0xFF;
        spawn.u45 = 0xFF;
        spawn.u46 = 0;
        spawn.u47 = 7;
        spawn.u48 = 0;
        spawn.u4C = 0xFF;
        for (ee.index = 0; ee.index < 2; ee.index++) {
            g->emit[ee.index] = func_151407D0(&fr.emit, 0x78, &spawn, 0, 0x2A, 0, 0, -1, alpha, owner);
            if (g->emit[ee.index] != NULL) {
                memcpy(g->emit[ee.index] + 0x170, (u8 *)&ee, 0x18);
            }
        }
    }
    /* the asm returns what v0 last held: 0 without a group, else the final emitter index (2) */
    return group != NULL ? 2 : 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BDDD8.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BE33C.s")

typedef struct {
    s32 a;
    u8 b;
} K_E65C;
void func_1516972C(struct102 *arg0);
s32 func_15169850(s32, u8, s32, s32, s32);
void func_151BE65C(struct102 *arg0, K_E65C *arg1, u8 arg2) {
    s32 t;
    K_E65C *p;
    struct102 **pa0 = &arg0; // fakematch: address taken keeps arg0 in its home slot
    K_E65C **pa1 = &arg1; // fakematch: address taken keeps arg1 in its home slot
    u8 *pa2 = &arg2; // fakematch: address taken keeps arg2 in its home slot

    if (*pa2 == 0x3B) {
        p = (K_E65C *)((u8 *)*pa0 + 0x28);
        t = (*pa1)->a == p->a;
        if (1) { // fakematch: empty block keeps the first compare in its own basic block
        }
        if (t || (*pa1)->b == p->b) {
            func_1516972C(*pa0);
        }
    } else {
        p = (K_E65C *)((u8 *)*pa0 + 0x28);
        func_15169850((s32)*pa1, *pa2, (s32)p, (s32)p + 4, (s32)*pa0);
    }
}

void func_151BE6E8(u8 *arg0)
{
  u8 *v = arg0 + 0x28; // fakematch: v defined first so IDO keeps it as a separate pointer (not folded into offsets)
  if (*(s32 *)(arg0 + 0x30) != 0) { func_1516972C(*(struct102 **)(arg0 + 0x30)); }
  if (*(struct102 **)(v + 0xC)) { func_1516972C(*(struct102 **)(v + 0xC)); } // fakematch: pointer-typed test gives one load (s32 test double-loads like line above)
  if (*(struct102 **)(v + 0x10)) { func_1516972C(*(struct102 **)(v + 0x10)); }
  if (*(struct102 **)(v + 0x14)) { func_1516972C(*(struct102 **)(v + 0x14)); }
}

void func_151BE768(struct260 * arg0) {
    func_151BE6E8(arg0);
    func_1514933C(arg0);
}

void func_151BE794(struct260 * arg0) {
    func_151BE6E8(arg0);
    func_15149368(arg0);
}

s32 func_151BE7C0(u8 *arg0) {
    f32 *s = (f32 *)(arg0 + 0x110);

    s[9] -= D_800BE9A4;
    if (s[9] < 0.0f) {
        s[9] = func_150ADA68() * 4.0f;
        s[6] = s[2] + s[4] * func_150ADA68();
    }
    *(f32 *)(arg0 + 0x2C) += (s[6] - *(f32 *)(arg0 + 0x2C)) * 0.35f;
    s[10] -= D_800BE9A4;
    if (s[10] < 0.0f) {
        s[10] = func_150ADA68() * 9.0f;
        if (func_150ADA20() & 1) {
            s[7] = s[3] + s[5] * func_150ADA68();
        } else {
            s[7] = s[3] + s[8] * func_150ADA68();
        }
    }
    *(f32 *)(arg0 + 0x30) += (s[7] - *(f32 *)(arg0 + 0x30)) * 0.4f;
    s[14] -= D_800BE9A4;
    if (s[14] < 0.0f) {
        s[14] = func_150ADA68() * 10.0f;
        s[13] = s[11] + s[12] * func_150ADA68();
    }
    s[15] += (s[13] - s[15]) * 0.4f;
    arg0[0x5C] = s[15];
    s[16] += (s[18] - s[16]) * 0.65000004f;
    s[17] += (s[19] - s[17]) * 0.65000004f;
    return 1;
}

s32 func_1513FAB4(s32, s32, f32 *, s16);

s32 func_151BEA68(struct102 *arg0, s16 arg1) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    f32 sp20[2];

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x110));
    if (((*(u8 *)((u8 *)arg0 + 0x114)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) || (temp_v0_2 = (u8 *)arg0 + 0x110, ((*(s32 *)((u8 *)temp_v0 + 0)) == 0))) {
        func_1516972C(arg0);
        return 0;
    }
    if (!((*(u8 *)((u8 *)temp_v0_2 + 0x58)) & 1)) {
        return 0;
    }
    sp20[0] = (*(f32 *)((u8 *)temp_v0_2 + 0x54)) * (*(f32 *)((u8 *)temp_v0_2 + 0x40));
    sp20[1] = (*(f32 *)((u8 *)temp_v0_2 + 0x54)) * (*(f32 *)((u8 *)temp_v0_2 + 0x44));
    return func_1513FAB4(arg0, 0, sp20, arg1);
}

void func_151BEB08(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0xB0;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            func_1516972C(arg0);
        }
    }
}

void func_151BEBB4(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x110), (s32)(arg0 + 0x114), (s32)arg0);
}

void func_151BEBF4(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x110;

    if (*(s32 *)(arg0 + 0x160) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 0x50);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[5] * 4 + 8) = 0;
    }
}

void func_151BEC24(struct210 * arg0) {
    func_151BEBF4(arg0);
    func_1513CA6C(arg0);
}

void func_151BEC50(struct210 * arg0) {
    func_151BEBF4(arg0);
    func_1513CAA0(arg0);
}

typedef struct { s32 a[4]; } V4_151BEC7C;
extern V4_151BEC7C D_800AAB88;
s32 func_151BEC7C(u8 *arg0) {
    u8 *v = arg0 + 0x110;
    V4_151BEC7C sp24;
    f32 f;
    sp24 = D_800AAB88;
    *(s16 *)(arg0 + 0x170) = *(s16 *)(arg0 + 0x170) - D_800BE9E4;
    if (*(s16 *)(arg0 + 0x170) < 0) {
        *(s8 *)(arg0 + 0x18) = sp24.a[func_150ADA20() & 3];
        *(s16 *)(arg0 + 0x170) = (func_150ADA20() & 7) + 3;
    }
    f = *(f32 *)(v + 0x48);
    *(f32 *)(v + 0x48) += (*(f32 *)(arg0 + 0x174) - f) * 0.65000004f;
    return 1;
}

void func_151BED38(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x180), (s32)(arg0 + 0x184), (s32)arg0);
}

void func_151BED78(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x170;

    if (*(s32 *)(arg0 + 0x178) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 8);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[0xC] * 4 + 0x10) = 0;
    }
}

void func_151BEDA8(struct210 * arg0) {
    func_151BED78(arg0);
    func_151411A4(arg0);
}

void func_151BEDD4(struct210 * arg0) {
    func_151BED78(arg0);
    func_151411C4(arg0);
}
