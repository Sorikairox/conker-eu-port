f32 func_150489B0();
s32 func_151705A4(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 mask;
    s32 v;
    f32 c;
    f32 s;

    mask = (arg0 & 0x40) ? 0x3F : 0x7F;
    v = func_150ADA20() & mask;
    *arg2 = func_150489B0(v & 0xFF);
    c = ((f32 (*)(u8))func_15048A40)(v); // fakematch: functions.h declares the cos helper void
    v = func_150ADA20() & 0xFF;
    s = func_150489B0(v & 0xFF);
    *arg1 = c * ((f32 (*)(u8))func_15048A40)(v); // fakematch: see above
    *arg3 = c * s;
}
