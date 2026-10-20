extern s16 D_800876C0[][3];
extern s8 D_80087688[];
extern s8 D_800E1000;
void func_1508EFEC(s32 arg0, s32 arg1, s32 arg2);

s32 func_1508DCAC(s32 arg0) {
    s32 *slots;
    s32 *timers;
    s32 *slot;
    s32 *timer;
    struct127 *obj;
    s32 idx;
    struct127 *other;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 cat;
    slots = (s32 *) (D_800D27D0 + 0x11C);
    timers = (s32 *) (D_800D27D0 + 0x29C);
    slot = &slots[arg0];
    obj = &D_800CC2D0[arg0];
    obj->unk31C->pad129[0] = *slot;
    idx = *slot;
    if (idx < 0) {
        return 0;
    }
    other = &D_800CC2D0[idx];
    dx = other->x_position - obj->x_position;
    dz = other->z_position - obj->z_position;
    dist = sqrtf((dx * dx) + (dz * dz));
    if (dist > 5000.0f) {
        cat = 0;
    } else if (dist > 2000.0f) {
        cat = 1;
    } else {
        cat = 2;
    }
    timer = &timers[arg0];
    if (D_800876C0[D_800E1000][cat] < *timer) {
        *timer = 0;
        if ((0x10000 << *slot) & ((s32 *) (D_800D27D0 + 0x16C0))[arg0]) {
            func_1508EFEC(arg0, 0x61, 0x2000);
        }
    }
    if (*timer == 0) {
        obj->unk31C->pad129[1] = 0;
        if (D_80087688[D_800E1000] < (s32) (func_150ADA68() * 100.0f)) {
            obj->unk31C->pad129[1] = 1;
        }
    }
}
