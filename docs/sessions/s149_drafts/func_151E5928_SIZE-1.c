void func_10003C10(s32, s32, f32, f32);
void func_151E7110(s32);
extern f32 D_800ABE3C;
extern u8 D_800E100C;
extern u16 D_800BED50;
extern void (*D_8009018C[])(void);
extern u8 D_800E0FC5;

void func_151E5928(void) {
    u8 prev;
    f32 sx;
    f32 sy;
    s32 x;
    s32 y;

    prev = D_800E0B94;
    sx = D_800E1010[0x1A] * D_800ABE3C + 1.0f;
    sy = D_800E1010[0x1B] * D_800ABE3C + 1.0f;
    x = D_800E1010[0x17] - 16;
    y = D_800E1010[0x18] - 8;
    func_10003C10(x * 2, y * 2, sx, sy);
    D_8003C8E0 = 0x8000000;
    D_800E100C = 0xFF;
    func_15042D78(0x81);
    D_800E0FCA = D_800BED50;
    if (D_800901C8 != 0) {
        D_800901C8--;
        D_800E0FCA = 0;
    }
    if (D_800E0B94 == 0) {
        func_151E7110(2);
    } else if (D_800E0B94 == 8) {
        func_151E7110(4);
    } else {
        func_151E7110(1);
    }
    D_8009018C[D_800E0B94]();
    if (D_800E0B94 != 7) {
        D_800E0EC0 += D_800BE9E4;
        if (prev != D_800E0B94) {
            D_800E0FC5 = prev;
            D_800E0EC0 = 0;
        }
    }
    D_8003C8E0 = 0;
}
