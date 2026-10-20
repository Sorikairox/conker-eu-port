void func_150B15D0(struct127 *arg0) {
    s32 pad;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f0_2;
    f32 temp_f2;
    u16 temp_v1;

    arg0->unk174 = arg0->x_position;
    arg0->unk178 = arg0->z_position;
    arg0->immune = 0x64;
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    if (func_1505A6F8(D_800CC2D0, arg0) < 1100.0f) {
        temp_f0 = func_1505A6F8(arg0, D_800CC2D0);
        temp_f16 = temp_f0;
        temp_f2 = arg0->y_position - D_800CC2D0->y_position;
        if (temp_f2 < 0.0f) {
            temp_f2 = 1000.0f;
        } else {
            temp_f2 = 1050.0f - (temp_f2 * 0.7f);
        }
        if ((temp_f0 < temp_f2) && (D_800CC2D0->in_water == 1)) {
            
            temp_f0_2 = 1100.0f - temp_f16;
            temp_v1 = func_1505A630(arg0->unk174 - D_800CC2D0->x_position, D_800CC2D0->z_position - arg0->unk178, 0);
            if (temp_f0_2 > 850.0f) {
                temp_f2 = (temp_f0_2 - 820.0f) * 0.09f;
                *D_800CC2E8 = D_800CC2D0->y_position - *D_800D1550 * (0, temp_f2);
            }
            func_1505A184(temp_v1 - 0x3000, (temp_f0_2 * 0.045f) + 5.0f, 0.0f, &sp50, &sp4C, &sp48);
            D_800CC2D0->unk164 = sp50;
            D_800CC2D0->unk168 = sp4C;
        }
    }
    func_1505E650(arg0, 0U, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
