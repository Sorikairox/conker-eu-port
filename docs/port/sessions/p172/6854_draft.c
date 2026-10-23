// object_bob_update: cosine bob around the base value +0x12 (s16): the offset +0x18 (f32) becomes
// cos(phase +0x7C * 360/65536) * amplitude (low half of +0x3C, s16), the phase advances by the speed (high half of
// +0x3C) * D_800BE9E4, and +0x5C (s16) = the change of the bobbed value (base + offset, truncated) this frame.
void func_15116854(u8 *obj) {
    s16 before;
    s32 cfg;
    f32 amplitude;
    u32 speed;
    f32 offset;

    before = (s32) ((f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18));
    cfg = *(s32 *) (obj + 0x3C);
    amplitude = (s16) cfg;
    speed = (cfg >> 16) & 0xFFFF;
    offset = cosf(*(s32 *) (obj + 0x7C) * 0.0054931640625f) * amplitude;
    *(f32 *) (obj + 0x18) = offset;
    *(s32 *) (obj + 0x7C) += speed * D_800BE9E4;
    *(s16 *) (obj + 0x5C) = (s32) (((f32) *(s16 *) (obj + 0x12) + offset) - before);
}
