#define I(o) (*(s32 *)((u8 *)arg0 + (o)))
#define H(o) (*(s16 *)((u8 *)arg0 + (o)))
#define F(o) (*(f32 *)((u8 *)arg0 + (o)))
void func_151C01F0(f32 *arg0, f32 *arg1) {
    I(0) = 3;
    I(4) = 4 >> ((D_80082FA0 >= 2) ? 1 : 0);
    *arg1 = 494.0f;
    F(0x14) = 0.0609f;
    I(0x2C) = 7;
    F(0x18) = 0.0252f;
    F(0x1C) = 45.0f;
    F(0x20) = 53.0f;
    F(0x24) = 203.0f;
    F(0x28) = 414.0f;
    I(0x30) = 3 >> ((D_80082FA0 >= 2 || D_8008FD8C >= 8) ? 1 : 0);
    F(0x34) = 15.0f;
    F(0x38) = 0.88f;
    F(0x3C) = -0.398f;
    H(0x44) = 0x19;
    H(0x46) = 0xF;
    H(0x48) = 0x64;
    H(0x4A) = 0x64;
    H(0x4C) = 0xC;
    H(0x4E) = 0x14;
    F(0x40) = 0.391f;
    if (D_80082FA0 >= 2 || D_8008FD8C >= 8) {
        *((s8 *)arg0 + 0x50) = -1;
    } else {
        *((s8 *)arg0 + 0x50) = 0;
    }
}
#undef I
#undef H
#undef F
