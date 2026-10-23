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
