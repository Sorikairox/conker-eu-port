typedef struct { s16 x, y, z, w; } P4s64;
void func_15077F64(void) {
    s32 var_a0;
    s32 var_a1;
    u8 pad;
    u8 temp_t6;
    P4s64 *temp_v0;
    f32 dx;
    f32 dz;

    temp_t6 = D_800D1890 - 1;
    temp_v0 = ((P4s64 **)D_800D2104)[D_800D154C->unk13F] + D_800D154C->unk21E;
    dx = temp_v0[1].x - D_800D154C->x_position;
    dz = D_800D154C->z_position - temp_v0[1].z;
    D_800D154C->unk78 = func_1505A630(dx, dz, 0);
    var_a0 = var_a1 = ((s32) (D_800D154C->unk78 - D_800D154C->unk76) >> 8) & 0xFF;
    if ((var_a0 & 0x80) != 0) {
        var_a0 = var_a1 = -var_a0 & 0xFF;
    }
    if (D_80099DFC[temp_t6][0] < var_a0) {
        D_800D154C->unk250 = D_800D1891;
        func_15056A00(D_800D154C, var_a1, temp_t6);
    }
}
