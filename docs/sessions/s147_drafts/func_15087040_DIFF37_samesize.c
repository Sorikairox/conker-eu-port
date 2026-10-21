f32 func_15087040(s32 arg0, s32 arg1) {
    struct_eu_800D2778 *a;
    struct_eu_800D2778 *b;
    f32 dx;
    f32 dy;
    f32 dz;

    if (arg0 == 0xFF) return 0.0f;
    if (arg1 == 0xFF) return 0.0f;
    a = &D_800D2778[arg0];
    b = &D_800D2778[arg1];
    dx = a->unk0 - b->unk0;
    dy = a->unk2 - b->unk2;
    dz = a->unk4 - b->unk4;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
