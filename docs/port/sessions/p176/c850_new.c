void func_1501D348(s32, s32, s32, s32, s32);
extern s8 D_800C39E2;
extern s8 D_800C39E3;
extern s8 D_800C40B9;
extern s8 D_800C40BC;
extern s32 D_800D3C60;

// event_action_scene: event-script scene actions (ids 0x1xxx). P176: s32 like the handler table; cases 1 / 3 / 4
// (start a scene) return 1, or 0 while a scene is playing (D_800C35EA), as the asm does. The asm leaves v0
// undefined in cases 2 / 5 / 6 / other (a callee's result or D_800D3C60): 0 here.
s32 func_1509C850(s32 arg0, s32 arg1, u8 *arg2) {
    s32 sp3C;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_v1;

    switch (arg1) {
    case 1:
        if (D_800C35EA == 0) {
            sp3C = D_800BE9F0;
            if (D_800D3C60 == 6) {
                func_15022238((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            } else if (D_800D3C60 == 3) {
                temp_a0 = (*(s32 *)((u8 *)arg2 + 8));
                if ((temp_a0 & 0xF000) == 0x2000) {
                    func_1509CD0C(temp_a0, 0);
                } else {
                    sp3C = temp_a0;
                }
            }
            func_1501D348(sp3C, arg0, 0, 0, 0);
            return 1;
        }
        return 0;
    case 4:
        if (D_800C35EA == 0) {
            if (D_800D3C60 == 6) {
                func_15022238((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            }
            temp_s0 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            func_1501D348(0x25, arg0, 0, 0, 0);
            D_800BE9F0 = temp_s0;
            return 1;
        }
        return 0;
    case 3:
        if (D_800C35EA == 0) {
            sp30 = (*(s32 *)((u8 *)arg2 + 8));
            temp_v1 = (*(s32 *)((u8 *)arg2 + 0xC));
            sp34 = D_800BE9F0;
            if (D_800D3C60 == 8) {
                sp2C = temp_v1;
                func_15022238((*(s16 *)((u8 *)arg2 + 0x12)), (*(s16 *)((u8 *)arg2 + 0x16)), (*(s16 *)((u8 *)arg2 + 0x1A)), (f32) (*(s32 *)((u8 *)arg2 + 0x1C)) * 0.000015258789f);
            } else if (D_800D3C60 == 5) {
                sp34 = (*(s32 *)((u8 *)arg2 + 0x10));
            }
            func_1501D348(sp34, arg0, 0, sp30, temp_v1);
            return 1;
        }
        return 0;
    case 2:
        D_800C39E2 = arg0 + 1;
        D_800C39E3 = (s8) D_800BE9F0;
        D_800C40B9 = 1;
        if (D_800D3C60 == 6) {
            func_15022290((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            return 0;
        }
        if (D_800D3C60 == 3) {
            temp_a0_2 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_a0_2 & 0xF000) == 0x2000) {
                func_1509CD0C(temp_a0_2, 1);
                return 0;
            }
            D_800C39E3 = (s8) temp_a0_2;
            return 0;
        }
    default:
        return 0;
    case 5:
        D_800C39E2 = arg0 + 1;
        D_800C39E3 = 0x25;
        if (D_800D3C60 == 6) {
            func_15022290((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            return 0;
        }
        break;
    case 6:
        D_800C40BC = 1;
        break;
    }
    return 0;
}
