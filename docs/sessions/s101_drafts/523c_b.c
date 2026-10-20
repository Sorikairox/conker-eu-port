typedef struct {
    u8 pad0[0x90];
    s32 u90;
    s16 u94;
    s16 u96;
    s16 u98;
    u8 pad9A[0x8];
    s16 uA2;
    s16 uA4;
    u8 padA6[0xE];
    u8 uB4;
} E523S;

void func_150E523C(E523S *arg0) {
    if (arg0->u90 < 9) {
        arg0->uA4 = (((arg0->u90 * 90) / 9) * arg0->u96) * 0.00390625f;
    } else {
        arg0->uA4 = ((90 - ((arg0->u90 * 90) - 810) / 600) * arg0->u96) * 0.00390625f;
        if (D_800BE9E4 * 17 < arg0->uB4) {
            arg0->uB4 -= D_800BE9E4 * 17;
        } else {
            arg0->u98 = -1;
        }
    }
    arg0->uA2 = (s32)(arg0->u94 * 14.0f) >> 8;
    if (arg0->u90 >= 0x261) {
        arg0->u98 = -1;
    }
    arg0->u90 += D_800BE9E4;
}
