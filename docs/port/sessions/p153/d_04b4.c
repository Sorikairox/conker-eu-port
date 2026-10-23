s32 func_1514FC58(u8 *arg0);
f32 *func_1514FD78(f32 *arg0, f32 arg1, f32 *arg2);

// path_particles_spawn: P153: when the path / curve `path` is usable (func_1514FC58) spawns def +0xC + random
// [0, def +0xE] particles (func_151D9014) along it: each at a random point (func_1514FD78 at def +0x10 + random *
// +0x14) with sprite def +0x31, size +0x1C + random * +0x20, life +0x18 + random [0, +0x1A], alpha +0x24 + random
// [0, +0x25], speed +0x28 + random * +0x2C, flag 1 below chance +0x34, scale 1.4 x 1.4, owner / owner arg,
// +0x38, flag 2 below chance +0x3C. The asm returns nothing; the callers' prototypes say s32 (game_eu_1FB080): 0.
s32 func_151504B4(f32 *path, u8 *def, s32 owner, s32 arg3, s32 arg4) {
    f32 pos[3];
    f32 size;
    f32 speed;
    f32 chance1;
    f32 chance2;
    s32 rLife;
    s32 rAlpha;
    s32 n;

    if (func_1514FC58((u8 *) path) == 0) {
        return 0;
    }
    n = (u32) func_150ADA20() % (u32) (*(s16 *) (def + 0xE) + 1) + *(s16 *) (def + 0xC);
    while (n != 0) {
        func_1514FD78(path, func_150ADA68() * *(f32 *) (def + 0x14) + *(f32 *) (def + 0x10), pos);
        size = func_150ADA68();
        rLife = func_150ADA20();
        rAlpha = func_150ADA20();
        speed = func_150ADA68();
        chance1 = func_150ADA68();
        chance2 = func_150ADA68();
        func_151D9014(def, pos, def[0x31], size * *(f32 *) (def + 0x20) + *(f32 *) (def + 0x1C),
                      (u32) rLife % (u32) (*(s16 *) (def + 0x1A) + 1) + *(s16 *) (def + 0x18),
                      (u32) rAlpha % (u32) (def[0x25] + 1) + def[0x24],
                      speed * *(f32 *) (def + 0x2C) + *(f32 *) (def + 0x28),
                      (chance1 < *(f32 *) (def + 0x34)) ? 1 : 0, 1.4f, 1.4f, 1, owner, def[0x38],
                      (chance2 < *(f32 *) (def + 0x3C)) ? 1 : 0, arg3 & 0xFF, arg4);
        n--;
    }
    return 0;
}
