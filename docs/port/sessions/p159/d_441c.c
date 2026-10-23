// object_sound_between: plays sound `sound` (func_1505D1C4) at the midpoint of a and b for object obj (its index
// in D_800CC2D0); the facing is obj's u16 at +0x76, minus the s16 at +0x12 of its parent (+0x31C) when it has one.
void func_151D441C(struct127 *obj, f32 *a, f32 *b, s32 sound) {
    u8 *parent;
    u16 facing;

    parent = *(u8 **)((u8 *)obj + 0x31C);
    if (parent != NULL) {
        facing = *(u16 *)((u8 *)obj + 0x76) - *(s16 *)(parent + 0x12);
    } else {
        facing = *(u16 *)((u8 *)obj + 0x76);
    }
    func_1505D1C4((a[0] + b[0]) * 0.5f, (a[1] + b[1]) * 0.5f, (a[2] + b[2]) * 0.5f, sound, obj - D_800CC2D0,
                  facing, 0, 0);
}
