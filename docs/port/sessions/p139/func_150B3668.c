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
