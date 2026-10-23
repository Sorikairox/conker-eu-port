s32 memcpy(s32, f32 *, s32);
s32 func_15134070(struct127 *);
extern u8 D_800A43C6[];
// object_link_effect_spawn: spawns a type 0x13 effect tied to obj (func_151491F4, 0x98-byte state copied to +0x28)
// for the target's class: 4 without a target or for target types 0x53 / 0xA5, else func_15134070(target);
// class 0x63 or a class mode (D_800A43C6[class * 16]) of 2 spawns nothing. The state is {obj, obj[0x3B], zeros,
// 0.0f, mode == 1}. life = span, or 300 (not fixed) when span is -1. Returns the effect or 0. The type 0x13
// effects of obj are first cleared through func_151494E0({obj, obj[0x3B]}, 0x13).
s32 func_151B09BC(u8 *obj, u8 *target, s16 span, u8 arg3, s32 arg4) {
    struct {
        u8 *obj;
        u8 id;
    } key;
    struct {
        /* 0x00 */ u8 *obj;
        /* 0x04 */ u8 id;
        /* 0x08 */ s32 zero[0x22];
        /* 0x90 */ f32 f90;
        /* 0x94 */ u8 single;
    } state;
    u8 *part;
    s32 class;
    s32 mode;
    s32 life;
    s32 fixed;
    s32 i;

    if (obj == NULL) {
        return 0;
    }
    if (target == NULL || target[4] == 0x53 || target[4] == 0xA5) {
        class = 4;
    } else {
        class = func_15134070((struct127 *)target);
    }
    if (class == 0x63) {
        return 0;
    }
    mode = D_800A43C6[class * 16];
    if (mode == 2) {
        return 0;
    }
    state.single = (mode == 1) ? 1 : 0;
    key.obj = obj;
    key.id = obj[0x3B];
    func_151494E0((s32)&key, 0x13);
    if (span == -1) {
        fixed = 0;
        life = 300;
    } else {
        life = span;
        fixed = 1;
    }
    state.obj = obj;
    state.id = obj[0x3B];
    for (i = 0; i < 0x22; i++) {
        state.zero[i] = 0;
    }
    state.f90 = 0.0f;
    part = (u8 *)func_151491F4(life, -1, 0x13, fixed, 0xF, 0x98, arg3, arg4);
    if (part != NULL) {
        memcpy((s32)(part + 0x28), (f32 *)&state, 0x98);
    }
    return (s32)part;
}
