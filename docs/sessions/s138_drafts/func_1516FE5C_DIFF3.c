void func_1516FE5C(s32 arg0, s32 arg1) {
    s32 v;
    s32 w;

    v = ((s8 *)arg0)[0x26];
    v <<= 8;
    v += ((u8 *)arg0)[0x27];
    v *= (u32)arg1;
    v >>= 8;
    ((u8 *)arg0)[0x26] = v >> 8;
    ((u8 *)arg0)[0x27] = v;
}
