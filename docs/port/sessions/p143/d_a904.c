// effect_fade_by_height: update handler (D_8008A100 slot 2) of a sprite effect: alpha +0x5C = min(life +0x1C * 16,
// height above +0x124 (y +0x38 minus floor) * 4, 255). Returns 0 (effect ends) once it is below the floor, else 1.
s32 func_150BA904(u8 *fx) {
    f32 height = *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x124);
    s32 byLife;
    s32 byHeight;

    if (height < 0.0f) {
        return 0;
    }
    byLife = *(s16 *)(fx + 0x1C) << 4;
    if (byLife >= 0x100) {
        byLife = 0xFF;
    }
    byHeight = (s32)height << 2;
    if (byHeight >= 0x100) {
        byHeight = 0xFF;
    }
    fx[0x5C] = (byHeight < byLife) ? byHeight : byLife;
    return 1;
}
