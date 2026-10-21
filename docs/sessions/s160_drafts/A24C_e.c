typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ struct17 pos;
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s16 u1A;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ s16 u2C;
    /* 0x2E */ s16 u2E;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ u8 u40;
} BlkA24C;

typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s16 u4;
    /* 0x06 */ u8 u6;
    /* 0x08 */ s32 u8_;
} BlkA24C_b;

void func_15150D7C(BlkA24C *arg0, s32 arg1, s32 arg2, s32 arg3, BlkA24C_b *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, s32 argB, s32 argC, u8 argD, s32 argE);
void func_151343AC(s32 arg0, s32 arg1);

void func_1513A24C(struct17 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, u8 *arg7, s32 arg8, u8 arg9, s32 argA) {
    BlkA24C a;
    BlkA24C_b b;
    s32 v;

    a.u0 = 0x28;
    a.u4 = 0;
    a.pos = *arg0;
    a.u14 = 0;
    a.u16 = 0xFF;
    a.u18 = -0x40;
    a.u1A = 0xC;
    a.u1C = 13.0f;
    a.u20 = 5.0f;
    a.u24 = -1.00700009f;
    a.u28 = 0.252000004f;
    a.u2C = 400;
    a.u2E = 200;
    a.u30 = 1 * arg4;
    a.u34 = 0 * arg4;
    a.u38 = 16.1020012f;
    a.u3C = 1.0f;
    a.u40 = arg6;
    b.u0 = 4;
    v = -1;
    if (arg5 == 1) {
        u16 tbl[4] = { 0x83, 0x81, 0x82, 0x84 };
        s32 i = arg7[0x128];

        v = 1;
        if (i >= 4) {
            i = 3;
        }
        b.u4 = tbl[i];
        b.u6 = 6;
        b.u8_ = 3;
    } else if (arg5 == 0xD) {
        a.u18 = -0x2E;
        a.u1A = 0x14;
        a.u1C = 15.0f;
        a.u20 = 8.0f;
        a.u24 = -1.26200008f;
        a.u28 = 0.49000001f;
        a.u38 = 12.9110003f;
    } else if (arg5 == 0x13) {
        if (D_800BE9F0 == 60) {
            a.u3C = 0.0f;
        }
    }
    func_15150D7C(&a, arg1, arg2, arg3, &b, 0xC, 6, 1, v, arg8, 5.0f, 1, D_800BE616 ? 1 : 0, arg9, argA);
    func_151343AC(0, 0x45);
}
