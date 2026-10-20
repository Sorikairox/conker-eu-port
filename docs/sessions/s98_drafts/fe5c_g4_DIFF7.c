s32 func_1516FE5C(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    s32 v;
    s16 t;

    v = ((s8)p[0x26] << 8) + p[0x27];
    v *= (u32)arg1;
    t = v >> 8;
    p[0x26] = t >> 8;
    p[0x27] = t;
    return v;
}
