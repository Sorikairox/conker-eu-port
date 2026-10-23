void func_15145EA4(f32 **, f32 **, void *, s32);
// object_mouth_point: P155: func_15145740 (obj, dir, arg3, arg4, 0.811), then out = `point` transformed by obj's
// bone `bone` (func_15145EA4) or, without bone matrices, obj's position + 49 up + 34 to the side of dir (x / z
// normalised, (0, 1) when both are below 0.0001). Returns 0 (the asm leaves v0 unset; the caller ignores it).
void func_151D5FC8(struct127 *obj, f32 *out, f32 *dir, s32 arg3, s32 arg4, f32 *point, u8 bone) {
    f32 *ins[1];
    f32 *outs[1];
    f32 n;
    f32 sx, sz;

    func_15145740(obj, (s32)dir, arg3, arg4, 0.81100005f);
    if (obj->unk1D4 != NULL) {
        outs[0] = out;
        ins[0] = point;
        func_15145EA4(ins, outs, (u8 *)obj->unk1D4 + bone * 64, 1);
        return;
    }
    if (fabsf(dir[0]) > 0.0001f || fabsf(dir[2]) > 0.0001f) {
        n = 1.0f / sqrtf(dir[0] * dir[0] + dir[2] * dir[2]);
        sz = dir[2] * n;
        sx = -dir[0] * n;
    } else {
        sz = 1.0f;
        sx = 0.0f;
    }
    out[0] = obj->x_position + 34.0f * sx;
    out[1] = obj->y_position + 49.0f;
    out[2] = obj->z_position + 34.0f * sz;

}
