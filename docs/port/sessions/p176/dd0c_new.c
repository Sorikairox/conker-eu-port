extern s32 D_800A0D30;

// P176: s32 like the D_80088874 handler table. The asm sets v0 only on the case 0x1C / 5 out-of-range path (1);
// elsewhere v0 is a callee's result (undefined): 0 here.
s32 func_1509DD0C(s32 arg0, s32 arg1, u8 *arg2) {
    struct {
        f32 u2C;
        s8 u30;
        s8 u31;
        s8 u32;
        s8 u33;
        s8 u34;
        u8 pad35[0x3];
        s8 u38;
    } sp;
    s32 var_a0;
    s32 var_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    switch (arg0) {
    case 0x34:
        if (arg1 == 3) {
            func_15197A7C(func_1505EEF4((*(s32 *)((u8 *)arg2 + 4)) & 0xFFF));
            return 0;
        }
    default:
        return 0;
    case 0x32:
        if (arg1 == 2) {
            func_151403A8(0, 0x53U);
            return 0;
        }
        if (arg1 == 3) {
            func_151403A8(0, 0x54U);
            return 0;
        }
        break;
    case 0x2D:
        func_151645C4((arg1 == 6) & 0xFF);
        return 0;
    case 0x28:
        if (arg1 == 2) {
            func_1515F170(4, 1);
            func_1515F170(5, 0);
            return 0;
        }
        if (arg1 == 3) {
            func_1515F170(4, 0);
            func_1515F170(5, 1);
            return 0;
        }
        break;
    case 0x1F:
        if (arg1 == 5) {
            sp.u38 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            func_151403A8((s32) &sp.u38, 0x36U);
        }
        /* fallthrough */
    case 0x1E:
        if (arg1 == 2) {
            sp.u34 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            func_151494E0((s32) &sp.u34, 0x34U);
            return 0;
        }
        break;
    case 0x1D:
        if (arg1 == 5) {
            sp.u2C = (f32) (*(s32 *)((u8 *)arg2 + 0xC));
            sp.u30 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            sp.u31 = (s8) (*(s32 *)((u8 *)arg2 + 0x10));
            sp.u32 = (s8) (*(s32 *)((u8 *)arg2 + 0x14));
            sp.u33 = (s8) (*(s32 *)((u8 *)arg2 + 0x18));
            func_1516944C(0x35, (s32) &sp.u2C, 0x33U);
            return 0;
        }
        break;
    case 0x1C:
        if (arg1 == 5) {
            temp_v0 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_v0 < 0) || (temp_v0 >= 3)) {
                return 1;
            }
            func_151494E0((s32) ((u8 *) &D_800A0D30 + temp_v0 * 0x10), 0x32U);
            return 0;
        }
        break;
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
        temp_v0_2 = arg0 & 0x3F;
        if (temp_v0_2 == 0xB) {
            var_a0 = 1;
        } else if (temp_v0_2 == 0xC) {
            var_a0 = 2;
        } else if (temp_v0_2 == 0xD) {
            var_a0 = 3;
        } else {
            var_a0 = 0;
            if (temp_v0_2 == 0xE) {
                var_a0 = 4;
            }
        }
        if (arg1 == 2) {
            var_a1 = 0x17;
        } else {
            var_a1 = 0x17;
            if (arg1 == 3) {
                var_a1 = 0x18;
            }
        }
        func_151616D0(var_a0, var_a1, 0);
        return 0;
    case 0x11:
        func_150DF1A8((*(u8 *)((u8 *)arg2 + 0xB)), (arg1 == 3) & 0xFF);
        break;
    }
    return 0;
}
