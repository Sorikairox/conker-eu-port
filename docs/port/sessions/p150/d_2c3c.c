s32 func_15100B80(u8 *, f32 *, f32 *, s32, s32, s32, s32, s32, f32, f32, f32, f32, s32, s32, s32);
extern f32 D_800A2570[][3];
extern f32 D_800A25C4[][3];
extern u8 D_800A2618[];
// object_effect_start: starts effect kind (D_800A2570 / D_800A25C4 / D_800A2618 entries) on obj through
// func_15100B80 with sizes 20, 20, 4 and rate 0.08. Object types 0x58, 0x5B and 0x80 use the pair (0x32, 0xFF),
// types 0x5A, 0x5F, 0x74, 0x75 and 0x7A (0xFF, 0); other types (0xFF, 0) when their record (+0x31C) byte +0x78 is
// 0x3B, else (0x32, 0xFF). Returns func_15100B80's result (0 without an object).
s32 func_15102C3C(u8 *obj, s32 arg1, s32 kind, s32 arg3, s32 arg4, s32 arg5) {
    s32 a;
    s32 b;

    if (obj == NULL) {
        return 0;
    }
    switch (obj[4]) {
        case 0x58:
        case 0x5B:
        case 0x80:
            a = 0x32;
            b = 0xFF;
            break;
        case 0x5A:
        case 0x5F:
        case 0x74:
        case 0x75:
        case 0x7A:
            a = 0xFF;
            b = 0;
            break;
        default:
            if ((*(u8 **)(obj + 0x31C))[0x78] == 0x3B) {
                a = 0xFF;
                b = 0;
            } else {
                a = 0x32;
                b = 0xFF;
            }
            break;
    }
    return func_15100B80(obj, D_800A2570[kind & 0xFF], D_800A25C4[kind & 0xFF], D_800A2618[kind & 0xFF], (s16)arg1,
                         a, b, 0, 20.0f, 20.0f, 4.0f, 0.08f, arg3 & 0xFF, arg4 & 0xFF, arg5);
}
