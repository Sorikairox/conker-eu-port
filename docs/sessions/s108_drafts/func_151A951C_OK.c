void func_15143874(s16, f32, f32 *, f32 *);
void func_151A951C(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 *p;

    p = (f32 *)(arg0 + 0x28);
    func_15143874(func_150ADA20() & 0xFF, p[8] * func_150ADA68(), arg1, arg1 + 2);
    arg1[0] += p[4];
    arg1[2] += p[6];
    arg1[1] = p[5];
    *arg2 = p[5];
    *arg3 = p[7];
}
