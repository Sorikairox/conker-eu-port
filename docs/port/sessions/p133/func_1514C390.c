s32 func_15145128(f32 *, f32 *, s32 *, s32 *);

/*
 * camera_look_follow: moves the look point (cam + 0x40, 3 floats) towards the point 100 above the position
 * (cam + 0x34) by the factor at cam + 0x15C, then puts it back at distance 100 from the position along that
 * direction (normalised by func_15145128); when the direction cannot be normalised the look point becomes the
 * position.
 */
void func_1514C390(u8 *cam) {
    f32 *pos = (f32 *) (cam + 0x34);
    f32 *look = (f32 *) (cam + 0x40);
    f32 t = *(f32 *) (cam + 0x15C);
    f32 goal[3];
    f32 lerp[3];
    f32 dir[3];
    s32 len, unused;

    goal[1] = pos[1] + 100.0f;
    goal[2] = pos[2];
    lerp[0] = look[0] + (pos[0] - look[0]) * t;
    lerp[1] = look[1] + (goal[1] - look[1]) * t;
    lerp[2] = look[2] + (goal[2] - look[2]) * t;
    dir[0] = lerp[0] - pos[0];
    dir[1] = lerp[1] - pos[1];
    dir[2] = lerp[2] - pos[2];
    if (func_15145128(dir, dir, &len, &unused) != 0) {
        look[0] = pos[0] + dir[0] * 100.0f;
        look[1] = pos[1] + dir[1] * 100.0f;
        look[2] = pos[2] + dir[2] * 100.0f;
    } else {
        look[0] = pos[0];
        look[1] = pos[1];
        look[2] = pos[2];
    }
}
