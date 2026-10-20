void func_151AF064(); // K&R: the ref passes the flag unmasked (definition is K&R too)
void func_151AEF34(u8 *, f32, f32, f32, u8, u8);

void func_151AEE40(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 v[3];
    f32 r;
    s32 a;
    s32 b;

    v[0] = arg0;
    v[1] = arg1;
    v[2] = arg2;
    r = func_150ADA68();
    if (!(r < 0.15f)) {
        if (r < 0.25f) {
            a = (func_150ADA68() > 0.0f) ? 1 : 0;
            func_151AF064(v, a, arg6[0xC]);
        } else {
            b = (func_150ADA68() > 0.80500007f) ? 1 : 0;
            func_151AEF34((u8 *)v, arg3, arg4, arg5, b, arg6[0xC]);
        }
    }
}
