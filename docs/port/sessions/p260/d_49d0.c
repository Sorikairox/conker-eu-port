#ifdef NON_MATCHING
/* point_emitter_update: per-frame update of a point emitter (list type 0x2A, made by func_15134908; type table
 * entry 0x8008C0D0). The emitter follows a point given as three f32 pointers (+0x10 / +0x14 / +0x18, x / y / z).
 * With flag 4 (+0x26) and a handler D_80089EB8[(s8) +0x29] (-1 = none), a 0 handler result frees it
 * (func_1516972C) at once. Flag 2 = no previous position this frame (cleared, nothing spawned). Otherwise the
 * accumulator +0x3C grows with the distance moved since the last frame (+0x2C) times +0x38 (= 1 / (2 * size)) plus
 * 1, scaled by D_800BE9A4 and the rate +0x20 (capped at 7); one D_80089E9C[+0x27] spawn per whole unit, spread
 * along the movement and jittered by the size +0x1C. Then the position is kept for the next frame; with flag 1 the
 * lifetime +0x24 counts down by D_800BE9E4 and the emitter is freed below 0. */
typedef void (*PointEmitterSpawnFn)(f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *obj);
typedef s32 (*PointEmitterTypeFn)(u8 *obj);
extern PointEmitterSpawnFn D_80089E9C[];
extern PointEmitterTypeFn D_80089EB8[];
void func_151349D0(u8 *obj) {
    f32 pos[3];
    f32 dx, dy, dz;
    f32 dist;
    f32 size2;
    f32 t, jx, jy, jz;
    f32 size;

    pos[0] = **(f32 **) (obj + 0x10);
    pos[1] = **(f32 **) (obj + 0x14);
    pos[2] = **(f32 **) (obj + 0x18);
    if ((obj[0x26] & 4) && (s8) obj[0x29] != -1) {
        if (D_80089EB8[(s8) obj[0x29]](obj) == 0) {
            func_1516972C((struct102 *) obj);
            return;
        }
    }
    if (obj[0x26] & 2) {
        obj[0x26] &= ~2;
    } else {
        dx = *(f32 *) (obj + 0x2C) - pos[0];
        dy = *(f32 *) (obj + 0x30) - pos[1];
        dz = *(f32 *) (obj + 0x34) - pos[2];
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        *(f32 *) (obj + 0x3C) += (*(f32 *) (obj + 0x38) * dist + 1.0f) * D_800BE9A4 * *(f32 *) (obj + 0x20);
        if (*(f32 *) (obj + 0x3C) > 7.0f) {
            *(f32 *) (obj + 0x3C) = 7.0f;
        }
        while (*(f32 *) (obj + 0x3C) > 1.0f) {
            size2 = *(f32 *) (obj + 0x1C) + *(f32 *) (obj + 0x1C);
            t = func_150ADA68();
            if (D_80089E9C[obj[0x27]] != NULL) {
                jx = func_150ADA68();
                jy = func_150ADA68();
                jz = func_150ADA68();
                size = *(f32 *) (obj + 0x1C);
                D_80089E9C[obj[0x27]](pos[0] + dx * t + size - jx * size2, pos[1] + dy * t + size - jy * size2,
                                      pos[2] + dz * t + size - jz * size2, dx, dy, dz, obj);
            }
            *(f32 *) (obj + 0x3C) -= 1.0f;
        }
    }
    *(f32 *) (obj + 0x2C) = pos[0];
    *(f32 *) (obj + 0x30) = pos[1];
    *(f32 *) (obj + 0x34) = pos[2];
    if (obj[0x26] & 1) {
        *(s16 *) (obj + 0x24) -= D_800BE9E4;
        if (*(s16 *) (obj + 0x24) < 0) {
            func_1516972C((struct102 *) obj);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151349D0.s")
#endif
