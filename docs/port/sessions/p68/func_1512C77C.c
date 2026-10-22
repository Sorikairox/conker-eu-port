/* Camera collision with a cylinder (struct108 viewed as bytes, as the rest of this file does).
 * When the request flag +0x948 is set and the camera position (+0x2F8, a vec3) lies inside the circle of
 * radius +0x938 around (+0x93C, +0x944), the camera is pushed out onto the circle along the line from the
 * centre and turned 5 degrees around it (away from the side it came from) when the push direction is
 * within 35 degrees of the view direction. +0x930 = the new heading to the target (+0x2A4) or the old
 * heading +0x37C when outside; D_80089950 = horizontal distance to the target (0 when nothing was done).
 * The request flag is always cleared. The asm leaves v0 undefined: void under NM. */
extern f32 D_80089950;
void func_1508EF80(u8 *, u8 *, f32, u8 *);
#define C108_F32(o) (*(f32 *)(arg0 + (o)))
void func_1512C77C(u8 *arg0) {
    struct17 *camPos;
    struct17 *centre;
    struct17 pos;
    struct17 dir;
    struct17 toTarget;
    struct17 target;
    f32 dx, dz;
    f32 pushAngle;
    f32 heading;
    f32 delta;
    f32 targetDist;

    if (arg0[0x948] == 0) {
        D_80089950 = 0.0f;
        C108_F32(0x930) = 0.0f;
        arg0[0x948] = 0;
        return;
    }
    dx = C108_F32(0x2F8) - C108_F32(0x93C);
    dz = C108_F32(0x300) - C108_F32(0x944);
    camPos = (struct17 *)(arg0 + 0x2F8);
    pos = *camPos;
    if (!(sqrtf(dx * dx + dz * dz) < C108_F32(0x938))) {
        D_80089950 = 0.0f;
        C108_F32(0x930) = C108_F32(0x37C);
        arg0[0x948] = 0;
        return;
    }

    /* work in the horizontal plane */
    target = *(struct17 *)(arg0 + 0x2A4);
    target.unk4 = 0.0f;
    pos.unk4 = 0.0f;
    C108_F32(0x940) = 0.0f;
    centre = (struct17 *)(arg0 + 0x93C);

    func_150491EC(centre, &pos, &dir);
    pushAngle = func_15048FC8(&dir) - 180.0f;
    func_15048758(&pushAngle);
    func_150491EC(&target, &pos, &toTarget);

    /* onto the circle */
    func_15049148(&dir, C108_F32(0x938), &dir);
    pos.unk0 = C108_F32(0x93C) + dir.unk0;
    pos.unk4 = 0.0f;
    pos.unk8 = C108_F32(0x944) + dir.unk8;
    dx = target.unk0 - pos.unk0;
    dz = target.unk8 - pos.unk8;
    targetDist = sqrtf(dx * dx + dz * dz);

    func_15048F90(&pos, &target, &dir);
    heading = func_15048FC8(&dir);
    func_15048758(&heading);
    C108_F32(0x930) = heading;

    delta = func_15048A70(pushAngle, heading);
    if (fabsf(delta) < 35.0f) {
        func_1508EF80((u8 *)&pos, (u8 *)centre, (delta <= 0.0f) ? 5.0f : -5.0f, (u8 *)&pos);
    }
    D_80089950 = targetDist;
    pos.unk4 = C108_F32(0x2FC);
    *camPos = pos;
    arg0[0x948] = 0;
}
