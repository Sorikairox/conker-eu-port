void func_150E3C3C(s32, s32 *, s32 *, s32 *);

s32 func_1509DFCC(s32 arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u34;
        s32 u38;
        s32 u3C;
    } sp;
    s32 temp_a0;
    s32 temp_t8;
    s32 var_t0;
    s32 var_v0;
    s8 var_a1;
    struct_eu_node *temp_v1;
    struct_eu_node *var_v0_2;

    var_v0 = 4;
    sp.u3C = 0;
    sp.u38 = 0;
    sp.u34 = 0;
    if ((arg0 != 4) && (arg0 != 5) && (arg0 != 6)) {
        if (arg0 == 0x19) {
            var_t0 = 0;
            if (arg1 == 4) {
loop_6:
                var_a1 = 0;
loop_7:
                var_v0_2 = D_800DD280[var_t0][*(s32 *)((u8 *)&D_800A6440 + var_a1 * 4)];
                var_a1 += 1;
                /* P176 (browser P174): test +0x48 of every node, then move to next (the m2c body advanced first:
                 * it skipped each list's first node and read NULL + 0x48 at the end) */
                for (; var_v0_2 != NULL; var_v0_2 = temp_v1) {
                    temp_v1 = var_v0_2->next;
                    if ((*(u8 *)((u8 *)var_v0_2 + 0x48)) == 2) {
                        return 0;
                    }
                }
                if (var_a1 >= 3) {
                    temp_t8 = (var_t0 + 1) & 0xFF;
                    var_t0 = temp_t8;
                    if (temp_t8 >= 2) {
                        return 1;
                    }
                    goto loop_6;
                }
                goto loop_7;
            }
        }
        /* Duplicate return node #20. Try simplifying control flow for better match */
        return var_v0;
    }
    if ((arg1 == 0) || (arg1 == 1)) {
        temp_a0 = arg0 >> 6;
        if (temp_a0 != 0) {
            func_150E3C3C(temp_a0, &sp.u3C, &sp.u38, &sp.u34);
            if (arg1 == 0) {
                sp.u38 = (sp.u3C << 0x10) | (sp.u34 & 0xFFFF);
            }
            var_v0 = sp.u38;
        }
    }
    return var_v0;
}
