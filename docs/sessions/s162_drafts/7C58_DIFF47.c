typedef struct {
    s16 u0;
    s16 u2;
    s16 u4;
    s16 u6;
    s16 u8;
    u8 uA;
    u8 padB;
    u8 padC;
    s8 uD;
    u8 padE[2];
} struct_7C58_a;
typedef struct {
    u8 pad0[0x10];
    s32 **u10;
    s16 u14;
    u8 pad16[2];
    s16 u18;
    s16 u1A;
    s16 u1C;
    s16 u1E;
    s16 u20;
    s8 u22;
    u8 u23;
} struct_7C58;
extern s32 D_800A4EA8[][2];
s32 func_15142E24(s32, s32 *, s32, s32, s32, s32, s32, s32, struct_7C58_a *, s32 *, s32);
s32 func_15142FBC(s32, s32, s32, s32 *);
s32 func_15095B70(s32, struct_7C58_a *);
s32 func_15167C58(s32 arg0, struct_7C58 *arg1, s32 arg2) {
    s32 pad0;
    struct_7C58_a a;
    s32 pad1[2];
    s32 flag;
    s32 i;

    flag = 1;
    arg0 = func_15142E24(arg0, (s32 *)arg1->u10, arg1->u14 << 8, 2, 0x100, 0x100, (*arg1->u10)[arg1->u14 >> 8], 5, &a, &flag, 3);
    a.u0 = arg1->u18;
    a.u2 = arg1->u1A;
    a.u4 = arg1->u1C;
    a.u6 = arg1->u1E;
    a.u8 = arg1->u20;
    a.uD = 0;
    a.uA = arg1->u23;
    if (arg1->u22 != 0xFF) {
        i = 3;
    } else if (arg1->u22 == 0xFF) {
        i = 9;
    }
    return func_15095B70(func_15142FBC(arg0, 0x2C00, D_800A4EA8[i][1] | D_800A4EA8[i][0] | 4, &flag), &a);
}
