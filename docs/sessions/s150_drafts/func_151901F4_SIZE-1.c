void func_151901F4(u8 *arg0, f32 *arg1) {
    u8 *obj;
    s32 pad[2];
    u8 *sub;
    u8 *p;

    sub = *(u8 **)(arg0 + 0x30);
    obj = *(u8 **)(arg0 + 0x2C);
    if (sub == NULL) {
        func_1516972C((struct102 *)obj);
        return;
    }
    *(f32 *)(obj + 0x148) = *(f32 *)(sub + 0x60) * (arg1[0] - *(f32 *)(arg0 + 0x34));
    *(f32 *)(obj + 0x14C) = *(f32 *)(sub + 0x60) * (arg1[1] - *(f32 *)(arg0 + 0x38));
    *(f32 *)(obj + 0x150) = *(f32 *)(sub + 0x60) * (arg1[2] - *(f32 *)(arg0 + 0x3C));
    p = sub + 0x30;
    *(f32 *)(obj + 0x110 + 0x44) = func_150ADA68() * *(f32 *)(p + 0x38) + *(f32 *)(p + 0x34);
    *(f32 *)(obj + 0x110 + 0x48) = *(f32 *)(p + 0x3C);
    *(s16 *)(obj + 0x6C) = *(s16 *)(p + 0x40);
    *(s16 *)(obj + 0x6E) = *(s16 *)(p + 0x42);
    *(s16 *)(obj + 0x1C) = (u32)func_150ADA20() % (*(s16 *)(p + 0x46) + 1) + *(s16 *)(p + 0x44);
    if (p[0x4C] & 1) {
        obj[0x70] = 0x21;
    } else {
        obj[0x70] = 0x20;
    }
    obj[0x71] = 0x24;
    *(s32 *)(obj + 0x58) |= 0x8000001;
}
