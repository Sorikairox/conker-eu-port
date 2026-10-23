#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B2C20.s")

#ifdef NON_MATCHING
/* P139 */
/* P139: particle request passed to func_15132FBC by the pipe-explode spawn handlers (0x7C bytes; same layout as
 * game_eu_103160.c's DebrisParticle). */
typedef struct {
    /* 0x00 */ f32 scale[4];
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
    /* 0x58 */ u8 u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 alpha;
    /* 0x61 */ u8 u61;
    /* 0x62 */ u8 u62[6];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6C */ void *owner;
    /* 0x70 */ u8 ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} PipeParticleReq;

s32 func_15132FBC(void *req, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
f32 func_151423D8(u8);
/*
 * pipe_explode_spawn_chunk: D_8008ADA0 spawn handler 9 (called per ring point by func_1514C860 with (mode, index,
 * px, py, pz, cx, cy, cz, a, angle0, r, arg8, arg9, argA, argB)). Spawns one particle (func_15132FBC, request
 * (3, 0xFF, 0, argB, 0)) at the point (px, py, pz): sprite 0x1C, life 100, flags 0x9E8, scale (1, 0.2, s, s) with
 * s random in 29.8..102.3, random x / z spin in -40..40 and gravity -0.837..-2.589. It flies outwards at a random
 * speed 18..49 in the direction yaw = angle0 + 60 * sin(a) * r * arg9 - 0x40, pitch = 48 * cos(a) - 0x14 (byte
 * angles, func_151423D8 = sine). Returns 1 (keep emitting).
 */
s32 func_150B3394(s32 mode, s16 index, f32 px, f32 py, f32 pz, f32 cx, f32 cy, f32 cz, s32 a, s32 angle0, f32 r,
                  s32 arg8, f32 arg9, s32 argA, s32 argB) {
    PipeParticleReq req;
    f32 cosA;
    f32 sinA;
    f32 speed;
    f32 cosYaw;
    f32 sinYaw;
    f32 cosPitch;
    f32 horiz;
    f32 size;
    s16 yaw;
    s16 pitch;

    cosA = func_151423D8((a - 0x40) & 0xFF);
    sinA = func_151423D8(a & 0xFF);
    req.flags = 0x9E8;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.rot[0] = 0.0f;
    req.rot[1] = 0.0f;
    req.rot[2] = 0.0f;
    req.pos[0] = px;
    req.pos[1] = py;
    req.pos[2] = pz;
    req.scale[1] = 0.2f;
    speed = func_150ADA68() * 31.0f + 18.0f;
    yaw = angle0 + (s32) (60.0f * sinA * r * arg9) - 0x40;
    cosYaw = func_151423D8((yaw - 0x40) & 0xFF);
    sinYaw = func_151423D8(yaw & 0xFF);
    pitch = (s32) (48.0f * cosA) - 0x14;
    cosPitch = func_151423D8((pitch - 0x40) & 0xFF);
    horiz = speed * func_151423D8(pitch & 0xFF);
    req.vel[0] = horiz * cosYaw;
    req.vel[1] = -speed * cosPitch;
    req.vel[2] = horiz * sinYaw;
    req.spinX = func_150ADA68() * 80.0f - 40.0f;
    req.spinY = 0.0f;
    req.spinZ = func_150ADA68() * 80.0f - 40.0f;
    req.life = 100;
    req.gravity = func_150ADA68() * -1.7520001f - 0.837f;
    req.scale[0] = 1.0f;
    size = func_150ADA68() * 72.5f + 29.800001f;
    req.sprite = 0x1C;
    req.u58 = 0;
    req.scale[2] = size;
    req.u5C = 0;
    req.alpha = 0xFF;
    req.u61 = 1;
    req.u62[0] = 0;
    req.u62[1] = 0;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 0;
    req.u6A = 2;
    req.owner = NULL;
    req.ownerId = 0;
    req.u72 = 1;
    req.u74 = 0xFF;
    req.scale[3] = size;
    func_15132FBC(&req, 3, 0xFF, 0, argB & 0xFF, 0);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3394.s")
#endif

#ifdef NON_MATCHING
/* P139 */
extern char D_8009FD38[];   /* "life" */
extern char D_8009FD40[];   /* "../Effects/PipeExplode/pipeexplode.c" (one copy per tunable) */
extern char D_8009FD68[];   /* "min grav" */
extern char D_8009FD74[];
extern char D_8009FD9C[];   /* "grav range" */
extern char D_8009FDA8[];
extern char D_8009FDD0[];   /* "min speed" */
extern char D_8009FDDC[];
extern char D_8009FE04[];   /* "speeed range" */
extern char D_8009FE14[];
extern char D_8009FE3C[];   /* "min scale" */
extern char D_8009FE48[];
extern char D_8009FE70[];   /* "scale  range" */
extern char D_8009FE80[];
extern char D_8009FEA8[];   /* "xz angle" */
extern char D_8009FEB4[];
extern char D_8009FEDC[];   /* "yz angle" */
extern char D_8009FEE8[];
s32 func_151422DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/*
 * pipe_explode_spawn_debris: D_8008ADA0 spawn handler 10 (pipeexplode.c; called per ring point by func_1514C860
 * with (mode, index, px, py, pz, cx, cy, cz, a, angle0, r, arg8, arg9, argA, argB)). Reads its tunables through
 * func_151422DC (id, name, min, max, default, file, line): life (300), min grav / grav range (/1000), min speed /
 * speed range, min scale / scale range (/10), xz angle, yz angle. Spawns one particle (func_15132FBC, request
 * (3, 0xFF, 4, argB, 0)) at (px, py, pz): sprite 0x1C, life + 0x20, flags 0x29E9, scale (s / 10, 0.2, s, s) with
 * s = min scale + random * scale range, random x / z spin in -2..2, gravity min grav + random * grav range. It
 * flies at min speed + random * speed range in the direction yaw = angle0 + xz * sin(a) * r * arg9 - 0x40,
 * pitch = yz * cos(a) - 0x14 (byte angles, func_151423D8 = sine). The new particle's +0x170 gets -18.0
 * (memcpy). Returns 1 (keep emitting).
 */
s32 func_150B3668(s32 mode, s16 index, f32 px, f32 py, f32 pz, f32 cx, f32 cy, f32 cz, s32 a, s32 angle0, f32 r,
                  s32 arg8, f32 arg9, s32 argA, s32 argB) {
    PipeParticleReq req;
    f32 floorY;
    f32 cosA;
    f32 sinA;
    s16 life;
    f32 minGrav;
    f32 gravRange;
    f32 minSpeed;
    f32 speedRange;
    f32 minScale;
    f32 scaleRange;
    f32 xzAngle;
    f32 yzAngle;
    f32 speed;
    f32 cosYaw;
    f32 sinYaw;
    f32 cosPitch;
    f32 horiz;
    f32 size;
    s16 yaw;
    s16 pitch;
    s32 p;

    cosA = func_151423D8((a - 0x40) & 0xFF);
    sinA = func_151423D8(a & 0xFF);
    life = func_151422DC(6, (s32) D_8009FD38, 1, 500, 300, (s32) D_8009FD40, 1858);
    minGrav = func_151422DC(7, (s32) D_8009FD68, -5000, 0, 0, (s32) D_8009FD74, 1872) * 0.001f;
    gravRange = func_151422DC(8, (s32) D_8009FD9C, -5000, 0, 0, (s32) D_8009FDA8, 1874) * 0.001f;
    minSpeed = func_151422DC(9, (s32) D_8009FDD0, 0, 500, 0, (s32) D_8009FDDC, 1882);
    speedRange = func_151422DC(10, (s32) D_8009FE04, 0, 500, 0, (s32) D_8009FE14, 1884);
    minScale = func_151422DC(11, (s32) D_8009FE3C, 0, 5000, 1000, (s32) D_8009FE48, 1889) * 0.1f;
    scaleRange = func_151422DC(12, (s32) D_8009FE70, 0, 5000, 0, (s32) D_8009FE80, 1891) * 0.1f;
    xzAngle = func_151422DC(13, (s32) D_8009FEA8, -255, 255, 0, (s32) D_8009FEB4, 1897);
    yzAngle = func_151422DC(14, (s32) D_8009FEDC, -255, 255, 0, (s32) D_8009FEE8, 1903);
    req.flags = 0x29E9;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.rot[0] = 0.0f;
    req.rot[1] = 0.0f;
    req.rot[2] = 0.0f;
    floorY = -18.0f;
    req.pos[0] = px;
    req.pos[1] = py;
    req.pos[2] = pz;
    req.scale[1] = 0.2f;
    speed = func_150ADA68() * speedRange + minSpeed;
    yaw = angle0 + (s32) (xzAngle * sinA * r * arg9) - 0x40;
    cosYaw = func_151423D8((yaw - 0x40) & 0xFF);
    sinYaw = func_151423D8(yaw & 0xFF);
    pitch = (s32) (yzAngle * cosA) - 0x14;
    cosPitch = func_151423D8((pitch - 0x40) & 0xFF);
    horiz = speed * func_151423D8(pitch & 0xFF);
    req.vel[0] = horiz * cosYaw;
    req.vel[1] = -speed * cosPitch;
    req.vel[2] = horiz * sinYaw;
    req.spinX = func_150ADA68() * 4.0f - 2.0f;
    req.spinY = 0.0f;
    req.spinZ = func_150ADA68() * 4.0f - 2.0f;
    req.life = life + 0x20;
    req.gravity = func_150ADA68() * gravRange + minGrav;
    size = func_150ADA68() * scaleRange + minScale;
    req.scale[2] = size;
    req.sprite = 0x1C;
    req.u58 = 0;
    req.u5C = 0;
    req.alpha = 0xFF;
    req.u61 = 1;
    req.scale[0] = size * 0.1f;
    req.u62[0] = 0;
    req.u62[1] = 5;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 0;
    req.u6A = 2;
    req.owner = NULL;
    req.ownerId = 0;
    req.u72 = 0x20;
    req.u74 = 7;
    req.scale[3] = size;
    p = func_15132FBC(&req, 3, 0xFF, 4, argB & 0xFF, 0);
    if (p != 0) {
        memcpy((u8 *) p + 0x170, &floorY, 4);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3668.s")
#endif

#ifdef NON_MATCHING
s32 func_150B3B8C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t9;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x48));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) + arg4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) < temp_f0) {
        temp_t7 = (*(s32 *)((u8 *)arg0 + 0x60)) & ~7;
        temp_t9 = temp_t7 & ~8;
        temp_t1 = temp_t9 & ~0x40;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t7;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t9;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t1;
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) (temp_t1 & ~0x20);
        (*(f32 *)((u8 *)arg0 + 0x44)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x48)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
        if ((*(s16 *)((u8 *)arg0 + 0x64)) >= 0x21) {
            (*(s16 *)((u8 *)arg0 + 0x64)) = 0x20;
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (-temp_f0 * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x4C)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x54)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x58)) * temp_f2);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3B8C.s")
#endif
s32 func_150B3C6C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 16;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

#ifdef NON_MATCHING
struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s16 D_80088AA0[3];   /* splash colours (15, 16, 17) */

/* trail_hit_splash: trail hit handler (D_8008A7D0 [5]) of particle `obj` hitting the ground at height `y`: the trail
 * record (obj +0x98) goes to state 4 (shrink); a splash sprite (func_1513C73C kind 0x11, life 150, a random colour
 * of D_80088AA0, size 50..100, the record's alpha bytes +0x1A / +0x1B) at the trail's current point (obj +0x94,
 * 20-byte points, index +0x2D) and a falling child trail (func_15148310: 3/4 of the record's +0 width, +4, random
 * length 15..30, +0xC / +0x10, colour bytes +0x19..+0x1B, life 60, the obj's +0x25) are spawned. Returns 1. */
s32 func_150B3CA8(u8 *obj, s32 arg1, s32 arg2, s32 arg3, f32 y, s32 arg5) {
    u8 *pts = *(u8 **)(obj + 0x94);
    u8 *rec = *(u8 **)(obj + 0x98);
    s16 colours[3];
    f32 size;
    s32 r1;
    s32 r2;
    s32 r3;
    struct {
        s32 kind;       /* 0x00 */
        s16 life;       /* 0x04 */
        u8 colour;      /* 0x06 */
        s32 u8_;        /* 0x08 */
        s32 uC;         /* 0x0C */
        u8 alpha0;      /* 0x10 */
        u8 alpha1;      /* 0x11 */
        u8 u12;
        u8 u13;
        u8 u14;
        u8 u15;         /* 0x15 = 0xFF */
        s32 flags;      /* 0x18 */
    } splash;
    struct {
        s32 w[7];       /* 0x00 */
        u8 b1C;
        u8 b1D;
    } style;
    struct {
        f32 width;      /* 0x00 */
        f32 v4;
        f32 length;
        f32 vC;
        f32 v10;
        f32 v14;
        u8 b18;
        u8 col[3];      /* 0x19..0x1B */
    } shape;
    struct {
        f32 x;          /* 0x00 */
        f32 y;
        f32 z;
        s16 life;       /* 0x0C */
        s16 sE;
        s32 s10;
        u8 b14;
        u8 b15;
    } at;

    colours[0] = D_80088AA0[0];
    colours[1] = D_80088AA0[1];
    colours[2] = D_80088AA0[2];
    rec[0x20] = 4;
    size = func_150ADA68() * 50.0f + 50.0f;
    splash.colour = colours[(u32)func_150ADA20() % 3];
    splash.u8_ = 0;
    splash.uC = 0;
    splash.kind = 0x11;
    splash.life = 150;
    splash.alpha0 = rec[0x1B];
    splash.u12 = 0;
    splash.u13 = 0;
    splash.u14 = 0;
    splash.u15 = 0xFF;
    splash.flags = 0x30002;
    splash.alpha1 = rec[0x1A];
    r1 = func_150ADA20();
    r2 = func_150ADA20();
    r3 = func_150ADA20();
    func_1513C73C((s32)&splash, 1, 0, arg5, *(f32 *)(pts + (s8)obj[0x2D] * 20), y,
                  *(f32 *)(pts + (s8)obj[0x2D] * 20 + 8), size, size, r1 & 0xFF, (r3 & 1) + (r2 & 1), 0, obj[0xC],
                  obj[1]);

    style.w[0] = 0;
    style.w[1] = 1;
    style.w[2] = 0x160600;
    style.w[3] = 3;
    style.w[4] = 0x10;
    style.w[5] = 0x80;
    style.w[6] = 0x20;
    style.b1C = 0;
    style.b1D = 9;
    at.s10 = 1;
    at.sE = 1;
    shape.col[0] = rec[0x19];
    shape.b18 = 8;
    shape.col[1] = rec[0x1A];
    shape.col[2] = rec[0x1B];
    at.y = y;
    at.x = *(f32 *)(pts + (s8)obj[0x2D] * 20);
    at.z = *(f32 *)(pts + (s8)obj[0x2D] * 20 + 8);
    at.life = 60;
    at.b15 = obj[0x25];
    shape.width = *(f32 *)(rec + 0x0) * 0.75f;
    shape.v10 = *(f32 *)(rec + 0x10);
    shape.v4 = *(f32 *)(rec + 0x4);
    shape.length = func_150ADA68() * 15.0f + 15.0f;
    shape.vC = *(f32 *)(rec + 0xC);
    func_15148310((u8 *)&at, (s32)&shape, 0, 1, 7, 0, 0, 0, 0, 0, 0, (u8 *)&style, 0, obj[0xC], obj[1]);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3CA8.s")
#endif