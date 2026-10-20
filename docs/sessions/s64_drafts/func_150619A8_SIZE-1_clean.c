s32 func_150617BC(struct127 *);
s32 func_150623F4(struct127 *);

void func_150619A8(void) {
    u8 sp5C[25];
    s32 var_s6;
    s32 var_s4;
    s32 var_s0_2;
    struct127 *var_s0;
    struct127 *temp_s3;
    struct127 *temp_v0_2;
    u8 *var_s1;
    u8 *var_s5;
    u8 temp_v0;
    u8 temp_a0;

    var_s6 = 0;
    var_s0 = D_800CC2D0;
    var_s4 = 0;
    do {
        if (var_s0->interaction_state != 0) {
            temp_v0 = (*(u8 *)((u8 *)var_s0 + 0x2FD));
            if (temp_v0 != 0) {
                (*(u8 *)((u8 *)var_s0 + 0x2FD)) = (u8) (temp_v0 - 1);
            }
            func_150617BC(var_s0);
            if (func_150623F4(var_s0) != 0) {
                var_s0->unk2FA |= 1;
            } else {
                var_s0->unk2FA &= ~1;
                if ((var_s0->unk20B != 0) || (var_s0->unk20C != 0) || (var_s0->unk20D != 0) || (var_s0->unk20E != 0)) {
                    sp5C[var_s6] = var_s4;
                    var_s6 += 1;
                }
            }
        }
        var_s4 += 1;
        var_s0++;
    } while (var_s4 < 0x19);
    if (var_s6 != 0) {
        var_s4 = 0;
        if (var_s6 > 0) {
            var_s5 = sp5C;
            loop_outer:
                temp_s3 = &D_800CC2D0[*var_s5];
                var_s1 = (u8 *)temp_s3;
                var_s0_2 = 0;
loop_16:
                temp_a0 = var_s1[0x20B];
                if ((temp_a0 != 0) && (temp_v0_2 = func_15083E90(temp_a0), (temp_v0_2 != NULL)) && (temp_v0_2->unk2FA & 1)) {
                    temp_s3->unk2FA |= 1;
                } else {
                    var_s0_2 += 1;
                    var_s1 += 1;
                    if (var_s0_2 != 4) {
                        goto loop_16;
                    }
                }
                var_s4 += 1;
                var_s5 += 1;
            if (var_s4 != var_s6) goto loop_outer;
        }
    }
}
