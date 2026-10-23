/* trail_emitter_update: per-frame update of a trail / particle emitter object (list type 0x28, made by
 * func_1513418C). Lifetime +0x38 counts down by D_800BE9E4 when flag 4 is set (dies below 0). Position: the
 * parent's position (+0x1C, flag 1), the parent model's bone matrix obj[0x20] (flag 2; the emitter dies when the
 * parent is gone or its slot id changed), or its own double-buffered matrix +0x10/+0x14 (no flag 0x10); the point
 * +0x24 is transformed by func_15143134. The accumulator +0x50 grows with the distance moved since the last frame
 * (+0x40; flag 8 = no previous position) and the rate +0x4C / +0x34 (capped at 7); one D_80089E10[obj[0x3B]]
 * spawn per whole unit, spread along the movement and jittered by the size +0x30. Then the per-type handler
 * D_80089E40[(s8) obj[0x3C]] (-1 = none); a 0 result (or the lifetime) frees the emitter (func_1516972C). */
typedef void (*EmitterSpawnFn)(f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *obj);
typedef s32 (*EmitterTypeFn)(u8 *obj);
extern EmitterSpawnFn D_80089E10[];
extern EmitterTypeFn D_80089E40[];
void func_151342BC(u8 *obj) {
    u8 dead;
    f32 *prev;
    u8 *parent;
    u8 *matrix;
    f32 pos[3];
    f32 dx, dy, dz;
    f32 dist;
    f32 size2;
    f32 t, jx, jy, jz;
    u8 flags;

    dead = FALSE;
    prev = (f32 *) (obj + 0x40);
    if (obj[0x3A] & 4) {
        *(s16 *) (obj + 0x38) -= D_800BE9E4;
        if (*(s16 *) (obj + 0x38) < 0) {
            dead = TRUE;
        }
    }
    flags = obj[0x3A];
    if (flags & 8) {
        prev = pos;
    }
    if (flags & 1) {
        parent = *(u8 **) (obj + 0x1C);
        pos[0] = *(f32 *) (parent + 0x14);
        pos[1] = *(f32 *) (parent + 0x18);
        pos[2] = *(f32 *) (parent + 0x1C);
    } else if (flags & 2) {
        parent = *(u8 **) (obj + 0x1C);
        if (*(s32 *) parent == 0 || *(s32 *) parent == 8 || obj[0x18] != parent[0x3B]) {
            func_1516972C((struct102 *) obj);
            return;
        }
        matrix = *(u8 **) (parent + 0x1D4);
        if (matrix == NULL || (parent[0x74] & 0xF) == 0xF) {
            obj[0x3A] = flags | 8;
            return;
        }
        func_15143134(obj + 0x24, pos, matrix + (obj[0x20] << 6));
    } else {
        if (flags & 0x10) {
            return;
        }
        func_15143134(obj + 0x24, pos, *(u8 **) (obj + 0x10 + (D_800BE9C0 ? 0 : 1) * 4));
    }

    dx = prev[0] - pos[0];
    dy = prev[1] - pos[1];
    dz = prev[2] - pos[2];
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    *(f32 *) (obj + 0x50) += (*(f32 *) (obj + 0x4C) * dist + 1.0f) * D_800BE9A4 * *(f32 *) (obj + 0x34);
    if (*(f32 *) (obj + 0x50) > 7.0f) {
        *(f32 *) (obj + 0x50) = 7.0f;
    }
    if ((obj[0x3A] & 0x20) && D_800C35EA == 1) {
        // no spawning (D_800C35EA == 1): drop the whole units
        while (*(f32 *) (obj + 0x50) > 1.0f) {
            *(f32 *) (obj + 0x50) -= 1.0f;
        }
    } else {
        while (*(f32 *) (obj + 0x50) > 1.0f) {
            size2 = *(f32 *) (obj + 0x30) + *(f32 *) (obj + 0x30);
            t = func_150ADA68();
            if (D_80089E10[obj[0x3B]] != NULL) {
                jx = func_150ADA68();
                jy = func_150ADA68();
                jz = func_150ADA68();
                D_80089E10[obj[0x3B]](pos[0] + dx * t + *(f32 *) (obj + 0x30) - jx * size2,
                                      pos[1] + dy * t + *(f32 *) (obj + 0x30) - jy * size2,
                                      pos[2] + dz * t + *(f32 *) (obj + 0x30) - jz * size2, dx, dy, dz, obj);
            }
            *(f32 *) (obj + 0x50) -= 1.0f;
        }
    }
    ((f32 *) (obj + 0x40))[0] = pos[0];
    ((f32 *) (obj + 0x40))[1] = pos[1];
    ((f32 *) (obj + 0x40))[2] = pos[2];
    obj[0x3A] &= ~8;
    if (!dead && (s8) obj[0x3C] != -1) {
        if (D_80089E40[(s8) obj[0x3C]](obj) == 0) {
            dead = TRUE;
        }
    }
    if (dead) {
        func_1516972C((struct102 *) obj);
    }
}
