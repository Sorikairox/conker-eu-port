s32 func_15022304(s32, s32);
s32 func_15082E44(u8 *, s32, s32, s32, s32);
extern u8 D_800D2520;
s32 func_15022440(s32 arg0, s32 arg1) {
    struct127 *sp3C;
    s32 sp38;
    s32 sp34;
    u8 **sp2C;
    s32 var_v0;
    u8 **temp_a2;
    u8 temp_v0;
    u8 *temp_v1;

    var_v0 = arg1;
    temp_a2 = &D_800C3A10[var_v0];
    if (D_800C39E8[var_v0][arg0] != 0) {
        temp_v1 = *temp_a2 + (arg0 * 8);
        if ((*(u16 *)((u8 *)temp_v1 + 0)) == 2) {
            temp_v0 = (*(u8 *)((u8 *)temp_v1 + 2));
            sp2C = temp_a2;
            sp34 = (s32) temp_v0;
            var_v0 = func_15083E0C(temp_v0);
            if (var_v0 != -1) {
                sp38 = var_v0;
                sp2C = temp_a2;
                var_v0 = func_1505EEF4(var_v0);
                if (var_v0 != 0) {
                    if ((*(u8 *)((u8 *)var_v0 + 5)) == 3) {
                        if (temp_a2 != D_800C3A10) {
                            (*(u8 *)((u8 *)var_v0 + 5)) = 4U;
                        } else {
                            (*(u8 *)((u8 *)var_v0 + 5)) = 0U;
                        }
                    }
                    if (sp34 == 1) {
                        (*(s32 *)((u8 *)var_v0 + 0xF4)) = (s32) ((*(s32 *)((u8 *)var_v0 + 0xF4)) & ~0x2A);
                        return var_v0;
                    }
                    /* Duplicate return node #13. Try simplifying control flow for better match */
                    return var_v0;
                }
                if (sp38 < (s32) D_800D2520) {
                    func_15082E44((u8 *) D_800D20FC + sp38 * 0x30, sp38, 0, arg1, 0);
                    var_v0 = func_1505EEF4(sp38);
                    if (var_v0 != 0) {
                        sp3C = (struct127 *) var_v0;
                        func_1505E650((struct127 *) var_v0, 0U, 0.0f, 0.0f, 0.0f, 0.0f, 1);
                        var_v0 = func_15022304(((u8 *) sp3C - (u8 *) D_800CC2D0) / 812, arg1);
                    }
                }
                /* Duplicate return node #13. Try simplifying control flow for better match */
                return var_v0;
            }
        }
    }
    return var_v0;
}
