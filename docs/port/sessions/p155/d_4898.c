// object_sound_at: plays sound `sound` (func_1505D1C4) at pos for object obj (its index in D_800CC2D0), with the
// direction of dir (x / z, binary angle - 0x4000, odd) or 0 without dir. arg3 is unused.
void func_151D4898(f32 *pos, f32 *dir, struct127 *obj, s32 arg3, s32 sound) {
    f32 a;
    u32 angle;
    s32 facing;

    facing = 0;
    if (dir != NULL) {
        a = func_150484A0(dir[0], dir[2]) * 10430.378f;
        /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
        angle = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
        facing = ((angle - 0x4000) | 1) & 0xFFFF;
    }
    func_1505D1C4(pos[0], pos[1], pos[2], sound, obj - D_800CC2D0, facing, 0, 0);
}
