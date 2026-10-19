s32 func_1000A420(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32);
extern s32 D_80042308;

s32 func_1000F6B8(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s16 arg5, s16 arg6) {
    s32 sp7C;
    s32 *sp78;
    s32 temp_v1;
    s32 temp_a0;
    s32 temp_a1;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 *var_t1;
    s32 *var_t1_2;
    s32 *var_v0;
    u32 temp_a2;
    u32 var_a3;

    var_t1 = &D_80042308;
    if (D_80082FA0 != 0) {
        var_a3 = -1U;
        if (D_80082FA0 >= 0) {
            var_v0 = &D_80042308;
            var_t1_2 = sp78;
            do {
                temp_v1 = arg1 - (*(s32 *)((u8 *)var_v0 + 0xC));
                temp_a0 = arg2 - (*(s32 *)((u8 *)var_v0 + 0x10));
                temp_a1 = arg3 - (*(s32 *)((u8 *)var_v0 + 0x14));
                temp_a2 = (temp_v1 * temp_v1) + (temp_a0 * temp_a0) + (temp_a1 * temp_a1);
                if (temp_a2 < var_a3) {
                    var_a3 = temp_a2;
                    var_t1_2 = var_v0;
                    sp68 = temp_v1;
                    sp64 = temp_a0;
                    sp60 = temp_a1;
                }
                var_v0 += 0x1C;
            } while ((u32) ((D_80082FA0 * 0x1C) + &D_80042308) >= (u32) var_v0);
            sp78 = var_t1_2;
        }
        var_t1 = sp78;
    } else {
        sp68 = arg1 - (*(s32 *)((u8 *)(&D_80042308) + 0xC));
        sp64 = arg2 - (*(s32 *)((u8 *)(&D_80042308) + 0x10));
        sp60 = arg3 - (*(s32 *)((u8 *)(&D_80042308) + 0x14));
    }
    func_1000A420(sp68, sp64, sp60, (*(s32 *)((u8 *)var_t1 + 0x18)), arg1 - (*(s32 *)((u8 *)var_t1 + 0)), arg2 - (*(s32 *)((u8 *)var_t1 + 4)), arg3 - (*(s32 *)((u8 *)var_t1 + 8)), (s32) arg6, (s32) arg5, arg4, &sp7C, 0);
    return sp7C;
}
