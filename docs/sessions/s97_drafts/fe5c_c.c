s32 func_1516FE5C(s32 arg0, s32 arg1) {
    s32 v;
    s32 t;

    v = ((s8)((u8 *)arg0)[0x26] << 8) + ((u8 *)arg0)[0x27];
    v *= (u32)arg1;
    t = v >> 8;
    ((u8 *)arg0)[0x26] = t >> 8;
    ((u8 *)arg0)[0x27] = t;
    return v;
}
