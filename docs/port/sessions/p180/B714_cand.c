// ambient_place_centre_sfx: placer type 1: one emitter at the triangle's centroid (integer mean), and a positional
// sound 0x4D there with volume `volume` (0x3E above 62.5).
s32 func_1500B714(s16 volume, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s16 x = (tri[2][0] + tri[0][0] + tri[1][0]) / 3;
    s16 y = (tri[2][1] + tri[0][1] + tri[1][1]) / 3;
    s16 z = (tri[2][2] + tri[0][2] + tri[1][2]) / 3;
    u16 vol;

    index = func_1500AF08(index, slot, mode, x, y, z, 0x80, kind, index);
    vol = volume;
    if (62.5f < (f32) (u16) volume) {
        vol = 0x3E;
    }
    func_1000FA64(0x4D, x, y, z, 0x8000, vol, vol >> 3, 0, NULL, 0, 0, 0);
    return index;
}
