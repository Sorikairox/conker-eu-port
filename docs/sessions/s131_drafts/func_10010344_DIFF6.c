u16 func_10010344(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
    s32 result;
    s32 flags;
    u8 mode;
    s32 pan;
    s32 fn;

    flags = 0;
    if (arg1->interaction_state == 0 || arg1->interaction_state == 5) {
        return 0;
    }
    if (arg2 < 0) {
        arg2 = -arg2;
        flags = 0x100;
    }
    if (arg1->camera != NULL) {
        pan = (((u32)arg1->unk184 >> 3) & 0x30) * 2;
        mode = D_80041FD9;
        if (arg1->unk31C != NULL && *((u8 *)arg1->unk31C + 0x94) == 1) {
            mode = 1;
            arg2 = 0x7FFF;
        }
        result = func_10010BE8(arg1->unk8C, arg0, arg2, 0x40, 0, pan, mode);
    } else {
        if (arg1->id == 0x16) {
            arg3 *= 2;
            if (arg4 < arg3) {
                arg3 = arg4 - 200;
            }
        } else if (arg1->id == 0x8A && arg1->unk13C != 0) {
            flags |= 0x100;
        } else if (arg1->id == 0x4F || arg1->id == 0x83) {
            flags |= 4;
        }
        fn = (s32)func_1000EE70;
        func_1000FD38(fn, (s32)arg1, arg1->unique_id | 0x20000);
        result = func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, fn, arg1, arg1->unique_id | 0x20000, flags, 0);
    }
    arg1->unk8C = result;
    return result;
}
