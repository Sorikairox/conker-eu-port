void obj_remove(struct127 *obj, s32 mode);
s32 setup_entry_spawn(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);

// obj_model_swap_keep_pose: sets the object's model record (+0x144: +4 = `a1`, +3 = `a2`, +0x20 / +0x24 = `scale`,
// +2 = 0), resets the object (obj_remove mode 0) and reloads model slot +0x13F (setup_entry_spawn, owner = object
// index + 1), then puts back what the reset clears: position (+0x14..+0x1C, copied to +0x2C..+0x34, y also to
// +0x1CC), +0x318 (whose +0x3D4 gets the object's +0x31C), +0xB8, +0x40, +0xC4 and the yaw (+0x76, also +0x7A).
void obj_model_swap_keep_pose(struct127 *obj, s32 a1, s32 a2, f32 scale) {
    u8 *o = (u8 *) obj;
    u8 slot = o[0x13F];
    u8 *e = *(u8 **) (o + 0x144);
    u8 *link;
    f32 x;
    f32 y;
    f32 z;
    f32 fB8;
    f32 f40;
    f32 fC4;
    u16 yaw;

    e[4] = a1;
    e[3] = a2;
    *(f32 *) (e + 0x20) = scale;
    *(f32 *) (e + 0x24) = scale;
    e[2] = 0;
    link = *(u8 **) (o + 0x318);
    x = *(f32 *) (o + 0x14);
    y = *(f32 *) (o + 0x18);
    z = *(f32 *) (o + 0x1C);
    fB8 = *(f32 *) (o + 0xB8);
    f40 = *(f32 *) (o + 0x40);
    fC4 = *(f32 *) (o + 0xC4);
    yaw = *(u16 *) (o + 0x76);
    obj_remove(obj, 0);
    setup_entry_spawn(e, slot, 0, 0, (obj - g_objects) + 1);
    *(f32 *) (o + 0x14) = x;
    *(f32 *) (o + 0x18) = y;
    *(u8 **) (o + 0x318) = link;
    *(f32 *) (o + 0x1C) = z;
    *(f32 *) (o + 0xB8) = fB8;
    *(f32 *) (o + 0x40) = f40;
    *(u16 *) (o + 0x76) = yaw;
    *(u16 *) (o + 0x7A) = yaw;
    *(f32 *) (o + 0x2C) = x;
    *(f32 *) (o + 0x30) = y;
    *(f32 *) (o + 0x1CC) = *(f32 *) (o + 0x18);
    *(f32 *) (o + 0x34) = *(f32 *) (o + 0x1C);
    *(f32 *) (o + 0xC4) = fC4;
    *(s32 *) (link + 0x3D4) = *(s32 *) (o + 0x31C);
}
