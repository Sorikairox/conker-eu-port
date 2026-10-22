void func_15131EC8(f32 *, f32);

/* P67: update of a debris piece that follows its owner (obj +0xA8 = owner record, +0xAC = the owner's unique_id when
 * spawned). Returns 0 when the owner is gone or reused; else follows it (func_150D71A8 into obj +0x40), adds gravity
 * (obj +0x64) to the velocity (obj +0x58), lets func_15131EC8 adjust it and moves obj +0x4C by the average of the
 * old and new velocity over the frame (D_800BE9A4; D_800BEDC8 scales the change). Returns 1. */
s32 func_150D71D4(u8 *arg0, s32 arg1) {
    struct127 *owner = *(struct127 **)(arg0 + 0xA8);
    f32 *pos = (f32 *)(arg0 + 0x4C);
    f32 *vel = (f32 *)(arg0 + 0x58);
    f32 old[3];

    if (owner->interaction_state == 0 || arg0[0xAC] != owner->unique_id) {
        return 0;
    }
    func_150D71A8((f32 *)owner, (f32 *)(arg0 + 0x40));
    old[0] = vel[0];
    old[1] = vel[1];
    old[2] = vel[2];
    vel[1] += *(f32 *)(arg0 + 0x64) * D_800BE9A4;
    func_15131EC8(vel, *(f32 *)(arg0 + 0xB0));
    pos[0] += old[0] * D_800BE9A4 + (vel[0] - old[0]) * D_800BEDC8 * D_800BE9A4 * D_800BE9A4 * 0.5f;
    pos[1] += old[1] * D_800BE9A4 + (vel[1] - old[1]) * D_800BEDC8 * D_800BE9A4 * D_800BE9A4 * 0.5f;
    pos[2] += old[2] * D_800BE9A4 + (vel[2] - old[2]) * D_800BEDC8 * D_800BE9A4 * D_800BE9A4 * 0.5f;
    return 1;
}
