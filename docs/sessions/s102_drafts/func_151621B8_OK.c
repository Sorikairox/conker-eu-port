void func_151621B8(u8 *volatile arg0) { // fakematch: volatile gives the arg0 home reload (s101 recipe)
    s32 pad; // fakematch: frame slot
    f32 s;
    f32 *p;

    s = sinf(*(f32 *)(arg0 + 0x40));
    p = (f32 *)(arg0 + 0x28);
    func_1515D4D4((u8)(s * p[3] + p[0]), (u8)(s * p[4] + p[1]), (u8)(s * p[5] + p[2]), 0);
    p[6] = p[7] * D_800BE9A4 + p[6];
    p[6] = func_15144B68(p[6]);
}
