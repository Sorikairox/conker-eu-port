void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
// bone_beam_spawn: unless obj has no bone matrices (+0x1D4) or is hidden (+0x74 low nibble 0xF), transforms the
// points a and b by bone `bone` (func_15145EA4, two points) and starts the effect func_151D49B8 at a's world
// position along b - a (with the bone matrix, obj, scale, alpha and flags).
void func_151D5714(struct127 *obj, f32 *a, f32 *b, u8 bone, f32 scale, u8 alpha, s32 flags) {
    f32 *outs[2];
    f32 *ins[2];
    u8 *mtx;
    f32 dir[3];
    f32 at[3];

    if (obj->unk1D4 == NULL || (((u8 *)obj)[0x74] & 0xF) == 0xF) {
        return;
    }
    outs[0] = at;
    outs[1] = dir;
    mtx = (u8 *)obj->unk1D4 + bone * 64;
    ins[0] = a;
    ins[1] = b;
    func_15145EA4(ins, outs, mtx, 2);
    dir[0] -= at[0];
    dir[1] -= at[1];
    dir[2] -= at[2];
    func_151D49B8((u8 *)at, (u8 *)dir, (s32)mtx, (u8 *)obj, scale, alpha, flags);
}
