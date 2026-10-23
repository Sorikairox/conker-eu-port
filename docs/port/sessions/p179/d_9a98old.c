u16 func_1505A630(f32 arg0, f32 arg1, s32 arg2);
void func_15079A98(s32 arg0) {
    s16 *temp_v0 = (s16 *)D_800D2104[D_800D154C->unk13F];
    struct127 *temp_v1 = &D_800CC2D0[arg0];

    func_1505A630(temp_v0[0] - temp_v1->x_position, temp_v1->z_position - temp_v0[2], 0);
}
