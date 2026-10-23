s32 func_15195FB0(u8 *, s32, s32, s32, s32, s32, s32);

void func_15116690(u8 *obj) {
    s32 req;

    if (*(s32 *)(obj + 0x7C) != 0) {
        return;
    }
    req = *(s32 *)(obj + 0x3C);
    *(s32 *)(obj + 0x7C) = func_15195FB0(obj, req & 0x7FFF, req >> 15, -1, 0, (req >> 24) & 0xFF, (req >> 16) & 0xFF);
    *(s32 *)(obj + 0x3C) = 0;
}
