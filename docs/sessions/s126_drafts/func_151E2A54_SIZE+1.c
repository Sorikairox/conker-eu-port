typedef struct { u8 b0; s8 b1; s8 b2; u8 b3; u8 b4; u8 b5; u8 b6; u8 b7; u8 b8; u8 b9; } R2A54;
s32 func_151DDF6C(s32, s32);
extern R2A54 *D_80082F4C;
extern s8 D_800ABA74[];
void func_151E2A54(void) {
    s8 k;
    u8 v;
    R2A54 *r;
    k = D_800ABA74[((s8 *)D_80090174)[0x42] * 10];
    r = &D_80082F4C[k];
    v = r->b3;
    if (v >= 5) {
        v = r->b3 = 4;
    }
    if (v < 0) {
        r->b3 = 0;
    }
    if (r->b1 <= 0) {
        r->b1 = 1;
    }
    D_800E1010[2] = r->b1;
    D_800E1010[0xB] = 0;
    D_800E1010[3] = r->b2;
    D_800E1010[0x10] = r->b3;
    D_800E1010[0x11] = r->b4;
    switch (k) {
    case 0:
        D_800E1010[4] = r->b5;
        break;
    case 1:
    case 2:
        D_800E1010[0xD] = r->b5;
        D_800E1010[0xE] = r->b6;
        break;
    case 7:
        D_800E1010[0x12] = r->b5;
        break;
    case 5:
        D_800E1010[0x11] = 0;
        D_800E1010[0x12] = r->b5;
        break;
    case 8:
    case 9:
        D_800E1010[7] = r->b5;
        D_800E1010[0x11] = 1;
        D_800E1010[3] = 2;
        D_800E1010[0x13] = r->b6;
        break;
    }
    D_800E1010[0x16] = r->b8;
    D_800E1010[6] = r->b9;
    func_151DDF6C(r->b1, k);
}
