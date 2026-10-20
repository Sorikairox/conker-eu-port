void func_151E86A4(void);
extern s8 D_800E0FE1;
extern s8 D_800BEA38;
extern s8 D_80090134;
extern u8 D_800E0FC9;
extern s16 D_8009015C;
extern s8 D_800D27C8;
s32 func_1509D1EC(s32);
s32 func_1509D338(s8, s32 *);
s32 func_1509D49C(s8, u8, s32 *, s32 *);
extern s8 D_80090110;
extern s16 D_8009014C;
extern u8 D_80090154;
extern s8 D_800902B0;
extern u8 D_800902B4;
extern s32 D_800BE804;
extern u8 D_800E1001;

void func_151E3864(void) {

    s32 sp24[3];

    sp24[0] = 0;
    if (D_80090154 != 0) {
        sp24[1] = (s32) D_8009014C;
    } else {
        func_1509D338(D_800902B0, &sp24[2]);
        func_1509D49C(D_800902B0, D_800902B4, &sp24[1], sp24);
        func_1509D464();
    }
    func_15017790();
    func_1509D0A4(sp24[1]);
    func_1509D1EC(sp24[1]);
    D_800BE9F4 = func_1509CE40(sp24[1]);
    func_15085710(0, 9, sp24[0]);
    D_800BE804 = sp24[0];
    D_800DD2C0 = func_1509CE60(sp24[1]);
    if (D_80090154 == 2) {
        D_800DD2C0 = D_800E1001;
    }
    D_80090110 = 0;
    D_800D27C8 = 0;
    D_8009015C = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    D_800E0FC9 = 1;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_800BEA38 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_800D18A8 = 0;
    D_800E0FE1 = 1;
    func_151E86A4();
    D_800D3260 = 1;
    func_1501C710(6, (s32) D_800BE9F4, func_1509CE60(sp24[1]), 0, 1);
}
