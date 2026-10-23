s32 func_1514654C(struct127 *, s32, s32, void **, void **, s32);
extern s32 D_800A0DA0;
extern s32 D_800A0DAC;

// object_get_beam_ends: the two end points of the object's beam: with a model (arg2->unk1D4) the positions of the
// two named joints D_800A0DA0 / D_800A0DAC (func_1514654C, 2 lookups, result 1 on success, else 0); without one,
// the object position + 100 and + 600 in y (result 2). P124: the joint name / output lists are 2-element arrays
// (m2c had 4 separate locals and passed the address of the first of each pair).
s32 func_150D4FF0(u8 *arg0, u8 *arg1, struct127 *arg2, s32 arg3) {
    void *names[2];
    void *outs[2];

    if (arg2->unk1D4 != NULL) {
        names[0] = &D_800A0DA0;
        names[1] = &D_800A0DAC;
        outs[0] = arg0;
        outs[1] = arg1;
        if (func_1514654C(arg2, arg3, 0, names, outs, 2) != 0) {
            return 1;
        }
        return 0;
    }
    *(f32 *)(arg0 + 0) = arg2->x_position;
    *(f32 *)(arg0 + 4) = arg2->y_position + 100.0f;
    *(f32 *)(arg0 + 8) = arg2->z_position;
    *(f32 *)(arg1 + 0) = arg2->x_position;
    *(f32 *)(arg1 + 4) = arg2->y_position + 100.0f + 500.0f;
    *(f32 *)(arg1 + 8) = arg2->z_position;
    return 2;
}
