// object_launch_player: launches the player record D_800CC2D0[obj->unk124] off object obj (a spring / bounce pad):
// unless the player is already airborne-locked (disable_run) or stunned, or its state block forbids it (+0x6B), sets
// immune / unk83 / disable_run to 0xFF, vertical speed vy and gravity, faces it along obj's angle, starts animation
// 0x32 (speed 1.3, blend 4), clears obj->unk218, sets obj->unk232 = timer and aims the state block at obj's x / z
// (or, when obj has a path table unk1D4 and point != -1, at path point `point` read by func_15043FF0), with mode 70
// and flag +0x27 = 1. The asm returns nothing; the s32 return type matches the callers' prototypes (0).
s32 func_1505327C(struct127 *obj, f32 vy, f32 gravity, s32 timer, s32 point) {
    struct127 *pl;
    vertex target;

    pl = &D_800CC2D0[obj->unk124];
    if (pl->disable_run != 0 || pl->stunned != 0) {
        return 0;
    }
    if (pl->unk31C != NULL && pl->unk31C->unk6B != 0) {
        return 0;
    }
    pl->immune = 0xFF;
    pl->y_velocity = vy;
    pl->gravity = gravity;
    pl->unk83 = 0xFF;
    pl->disable_run = 0xFF;
    pl->unk76 = obj->unk7A;
    obj->unk218 = NULL;
    obj->unk232 = timer;
    func_1505E650(pl, 0x32, 1.3f, 4.0f, 0.0f, 0.0f, 0);
    D_800CC2D0[obj->unk124].unk31C->unk30 = 70;
    *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk28 = obj->x_position;
    *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk2C = obj->z_position;
    if (obj->unk1D4 != NULL && point != -1) {
        func_15043FF0(&target, (struct113 *) ((u8 *) obj->unk1D4 + (point << 6)));
        *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk28 = target.x;
        *(f32 *) &D_800CC2D0[obj->unk124].unk31C->unk2C = target.z;
    }
    D_800CC2D0[obj->unk124].unk31C->unk27 = 1;
    return 0;
}
