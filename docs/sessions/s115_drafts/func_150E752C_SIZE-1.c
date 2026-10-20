void func_150E752C(f32 *out, u8 *obj) {
    struct_eu_link *m;
    f32 c;
    f32 r;
    u16 ang;
    f32 s;
    u8 *p;

    if (func_1514F250(*(struct_eu_link **)(obj + 0x2F4), 0x16, &m) != 0) {
        r = func_150ADA68() * 100.0f + 80.0f;
        ang = func_150ADA20() & 0xFF;
        s = func_151423D8(ang - 0x40);
        c = func_151423D8(ang);
        p = *(u8 **)((u8 *)m + 0x10);
        out[0] = *(f32 *)(obj + 0x14) + *(f32 *)(p + 0x38) * -80.0f + s * r;
        out[1] = *(f32 *)(obj + 0x18) + *(f32 *)(p + 0x3C) * -80.0f + 100.0f;
        out[2] = *(f32 *)(obj + 0x1C) + *(f32 *)(p + 0x40) * -80.0f + c * r;
    } else {
        out[0] = *(f32 *)(obj + 0x14);
        out[1] = *(f32 *)(obj + 0x18);
        out[2] = *(f32 *)(obj + 0x1C);
    }
}
