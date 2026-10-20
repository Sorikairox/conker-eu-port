s32 func_1503F8A8(u8 *, s32, s32, s32, f32, s32);
s32 func_1503F91C(s32, s32, u8 *, u8 *, u8 *, u8 *, u8 *);
s32 func_1515D9B0();
s32 func_1515D9F0(s32);
u8 *func_15157580(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    u8 *obj;
    s32 type;
    s32 i;

    type = 0x36;
    if (arg0[0] & 0x80) {
        type = 0x5B;
    } else if (arg0[0] & 0x10) {
        type = 0x4C;
    }
    obj = func_15167A68(type, arg7, arg5 + 0x120, 1, arg6, 1);
    if (obj == NULL) {
        return NULL;
    }
    memcpy(obj + 0x10, arg0, 0x58);
    func_1503F91C(*(s32 *)(obj + 0x18), *(s32 *)(obj + 0x1C), obj + 0x6C, obj + 0x70, obj + 0x74, obj + 0x78, obj + 0x68);
    guMtxIdentF(obj + 0x7C);
    guMtxIdentF(obj + 0xBC);
    *(u8 **)(*(u8 **)(obj + 0x68) + 0x3E0) = obj + 0x7C;
    *(u8 **)(*(u8 **)(obj + 0x68) + 0x3E4) = obj + 0xBC;
    func_1503F8A8(*(u8 **)(obj + 0x68), 1, arg1, arg2, 0.0f, 0);
    *(s32 *)(obj + 0xFC) = arg3;
    *(s32 *)(obj + 0x118) = arg4;
    obj[0x100] = 0;
    for (i = 0; i < 4; i++) {
        ((s32 *)(obj + 0x104))[i] = 0;
    }
    *(s32 *)(obj + 0x114) = 0;
    if (arg3 != 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            ((s32 *)(obj + 0x104))[i] = func_1515D9F0(arg3);
        }
        *(s32 *)(obj + 0x114) = func_1515D9B0();
    }
    return obj;
}
