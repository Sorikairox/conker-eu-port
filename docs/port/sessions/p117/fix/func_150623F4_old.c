s32 func_15022A8C(struct127 *);
s32 func_150A6840(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern s32 D_800DA030;

s32 func_150623F4(struct127 *arg0) {
    s32 sp54;
    s32 sp4C;
    s32 *var_s1;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f22;
    s32 temp_t9;
    s32 var_a0;
    s32 var_s0;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    struct127 *var_v0_2;
    struct127 *var_v0_3;
    struct129 *temp_v0;
    u16 temp_t6;
    u16 temp_t7;
    u8 temp_a2;
    u8 temp_t1;

    temp_v0 = arg0->unk144;
    if (temp_v0 != NULL) {
        temp_t6 = (*(u16 *)((u8 *)temp_v0 + 0x2A));
        var_f22 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f22 += 4294967296.0f;
        }
    } else {
        var_f22 = 0.0f;
    }
    if (var_f22 == 0.0f) {
        return 1;
    }
    if (arg0->unk127 != 0xFF) {
        return 1;
    }
    if ((D_800C3638 != 0) && (func_15022A8C(arg0) != 0)) {
        return 1;
    }
    if (arg0->interaction_state == 0x27) {
        return 1;
    }
    var_a0 = 0;
    var_v0_2 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_t1 = var_v0_2->unkB;
            var_v0_2 += 1;
            var_a0 += temp_t1;
        } while ((u32) (D_80082FA0 + arg0) >= (u32) var_v0_2);
    }
    if (var_a0 == 0) {
        return 0;
    }
    if ((arg0->unk74 & 0xF) != 0xF) {
        return 1;
    }
    temp_a2 = arg0->unk13F;
    if (D_800D2528[temp_a2] != 0) {
        var_t0 = 1;
        var_v1 = 0;
        if (D_8008FD8C > 0) {
            temp_t9 = D_800D2104[temp_a2];
            var_v0_3 = D_800CC2D0;
            temp_t7 = (*(u16 *)((u8 *)temp_t9 + 6));
loop_22:
            var_v1 += 1;
            temp_f0 = (f32) (*(s16 *)((u8 *)temp_t9 + 0)) - var_v0_3->x_position;
            temp_f2 = (f32) (*(s16 *)((u8 *)temp_t9 + 4)) - var_v0_3->z_position;
            if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) < (f32) (temp_t7 * temp_t7)) {
                var_t0 = 0;
            } else {
                var_v0_3 += 0x32C;
                if (var_v1 < D_8008FD8C) {
                    goto loop_22;
                }
            }
        }
        sp4C = var_t0;
        if (var_t0 == 0) {
            return 1;
        }
        goto block_27;
    }
block_27:
    var_t0_2 = sp4C;
    var_s1 = &D_800DA030;
    var_v1_2 = 0;
    var_s0 = 0;
    temp_f20 = (f32) (*(s16 *)((u8 *)(D_800D1C90[arg0->id]) + 0x10)) * arg0->y_scale;
    if (D_80082FA0 >= 0) {
        sp4C = 1;
loop_29:
        sp54 = var_v1_2;
        if (func_150A6840(var_s0 + D_800BE628, var_s1, arg0->x_position, arg0->y_position + temp_f20, arg0->z_position, var_f22, var_f22, 20000.0f) != 0) {
            sp4C = 0;
            var_t0_2 = 0;
        } else {
            var_v1_2 += 1;
            var_s0 += 0x180;
            var_s1 += 0x40;
            if (D_80082FA0 < var_v1_2) {
                var_t0_2 = sp4C;
            } else {
                goto loop_29;
            }
        }
    }
    var_v0 = 0;
    if (var_t0_2 == 0) {
        var_v0 = 1;
    }
    return var_v0;
}

