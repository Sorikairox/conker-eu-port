s32 func_150A2D44(u8);
u8 * func_151149AC(u8, s32);
extern struct_eu_s32x2 D_80088CF0;
extern struct_eu_s32x2 D_80088CF8;
void func_150DE8AC(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    u8 *p;
    struct_eu_s32x2 sp50 = D_80088CF0;
    struct_eu_s32x2 sp48 = D_80088CF8;
    u8 *temp_v0;

    p = (u8 *)&sp50;
    for (i = 0; i != 8; i++) {
        if (func_150A3794((*p * 0x34) + D_800D34B8, arg0, arg1, arg2) != 0) {
            if (((u8 *)&sp48)[i] != 0) {
                temp_v0 = func_151149AC(((u8 *)&sp48)[i], 1);
                temp_v0[0x73] = (temp_v0[0x73] & ~3) | 3;
            } else {
                func_150A2D44(*p);
            }
        }
        p++;
    }
}
