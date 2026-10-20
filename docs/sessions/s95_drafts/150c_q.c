s32 func_1519150C(u8 *arg0) {
    f32 s;
    s32 pad; // fakematch: unknown slot at sp+0x20
    u8 *p;
    f32 c;

    arg0[0x131] += (s8)arg0[0x133] * D_800BE9E4;
    arg0[0x132] += (s8)arg0[0x134] * D_800BE9E4;
    p = arg0 + 0x110;
    s = func_151423D8((u8)(arg0[0x131] - 0x40));
    c = func_151423D8((u8)(p[0x22] - 0x40));
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(p + 0x28) + (*(f32 *)(p + 0x30) * s)) - *(f32 *)(arg0 + 0x2C)) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(p + 0x2C) + (*(f32 *)(p + 0x34) * c)) - *(f32 *)(arg0 + 0x30)) * 0.5f;
    return 1;
}
