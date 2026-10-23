void func_1505D1C4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7);
// object_sounds_at: plays the sounds `sound1` and `sound2` (func_1505D1C4) at pos for object obj (its index in
// D_800CC2D0) with `flags` and a source point: with dir, pos - 90 * dir and dir's binary angle - 0x4000 (odd) as
// facing; without, pos raised by half the height of `model` (func_1507C7C0, when given) and facing 0. arg4 is
// unused. Returns 0 (the asm leaves v0 unset; the caller ignores it).
void func_151D4684(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags) {
    f32 at[3];
    s16 height;
    f32 a;
    u32 angle;
    s32 facing;
    s32 index;

    if (dir != NULL) {
        a = func_150484A0(dir[0], dir[2]) * 10430.378f;
        /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
        angle = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
        facing = ((angle - 0x4000) | 1) & 0xFFFF;
        at[0] = pos[0] + dir[0] * -90.0f;
        at[1] = pos[1] + dir[1] * -90.0f;
        at[2] = pos[2] + dir[2] * -90.0f;
    } else {
        ((s32 *)at)[0] = ((s32 *)pos)[0];
        ((s32 *)at)[1] = ((s32 *)pos)[1];
        ((s32 *)at)[2] = ((s32 *)pos)[2];
        if (model != NULL) {
            func_1507C7C0(model, &height, NULL, NULL);
            at[1] += height >> 1;
        }
        facing = 0;
    }
    index = obj - D_800CC2D0;
    func_1505D1C4(pos[0], pos[1], pos[2], sound1, index, facing, flags, (s32)at);
    func_1505D1C4(pos[0], pos[1], pos[2], sound2, index, facing, flags, (s32)at);

}
