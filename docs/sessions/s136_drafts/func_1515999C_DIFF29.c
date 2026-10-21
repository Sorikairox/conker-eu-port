u8 func_1515999C(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    struct_eu_link *sp38;
    u8 sp37;
    s32 m;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    u8 *temp_a1;
    u8 var_t2;

    sp37 = 0;
    var_t2 = sp37;
    if (func_1514F250((*(struct_eu_link **)((u8 *)arg0 + 0x2F4)), 0x13, &sp38) == 0) {
        return 0U;
    }
    temp_a1 = (u8 *)sp38->unk10;
    if (arg4 == -1) {
        var_t1 = 0x1E00;
    } else {
        var_t1 = 1 << (arg4 + 9);
    }
    if (arg3 == -1) {
        var_t0 = 0x1C0;
    } else {
        var_t0 = 1 << (arg3 + 6);
    }
    if (arg2 == -1) {
        var_a2 = 0x38;
    } else {
        var_a2 = 1 << (arg2 + 3);
    }
    if (arg1 == -1) {
        var_a3 = 7;
    } else {
        var_a3 = 1 << arg1;
    }
    if (arg5 == -1) {
        var_a0 = 0x3E000;
    } else {
        var_a0 = 1 << (arg5 + 0xD);
    }
    m = ((1 << temp_a1[0x2C]) | (1 << (temp_a1[0x2D] + 3)) | (1 << (temp_a1[0x2E] + 6)) | (1 << (temp_a1[0x2F] + 9)) | (1 << (temp_a1[0x30] + 0xD)));
    m |= var_a0 | var_a3 | var_a2 | var_t0 | var_t1;
    if ((var_a0 | var_a3 | var_a2 | var_t0 | var_t1) == m) {
        var_t2 = 1;
    }
    return var_t2;
}
