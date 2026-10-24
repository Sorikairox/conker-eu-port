/* func_15083FB0 (s32 (u8), game_eu_AF2A0) is used undeclared in this file, like its other callers here */
int func_1507BB28(s32, s32);
u16 func_15079A98(s32 arg0);

// object_var_cmd: P210: script command on object `idx` (D_800D1891 0 / 1: the current one D_800C3E78, else
// func_15083FB0(D_800D1891 - 2); -1 = none). D_800D1892 selects: 1..3 counter unk2E4 / unk2E8 / unk2EC, updated by
// D_800D1893 (0 = D_800D1890, 1 -1, 2 + frame time D_800BE9E4, 3 +1, 4 - frame time, 5 - D_800CC264,
// 6 + D_800CC264); 4 / 5 start script D_800D1890 on the object (when it is not running it already); 6 unkC8 =
// D_800D1890; 7 unkB8 = 0; for the current object: 8 unk221 = D_800D1890 when the path point angle
// (func_15079A98) from object D_800C3E78 minus the one from object unk222 has bit 15 set, 9 unk244 = D_800D1893 << 8 | D_800D1890, 10 unk236 = unk23D + (s8)D_800D1890, 11 unk22A = D_800D1890.
// Other D_800D1892 values: the asm then updates a counter through an unset stack pointer; here nothing happens.
void func_15079B30(void) {
    s32 idx;
    s32 *var;
    struct127 *saved;
    u8 savedNum;
    u16 a;

    if (D_800D1891 == 0 || D_800D1891 == 1) {
        idx = D_800C3E78;
    } else {
        idx = func_15083FB0(D_800D1891 - 2);
        if (idx == -1) {
            return;
        }
    }
    switch (D_800D1892) {
        case 1:
            var = &D_800CC2D0[idx].unk2E4;
            break;
        case 2:
            var = &D_800CC2D0[idx].unk2E8;
            break;
        case 3:
            var = &D_800CC2D0[idx].unk2EC;
            break;
        case 4:
        case 5:
            saved = D_800D154C;
            savedNum = D_800C3E78;
            D_800D154C = &D_800CC2D0[idx];
            D_800C3E78 = idx;
            if (D_800D1890 != D_800D154C->unk232) {
                D_800D154C->unk232 = D_800D1890;
                D_800D154C->unk218 = (struct216 *)func_1507BB28(0, D_800D154C->unk232);
                D_800D154C->unk21C = 0;
            }
            D_800C3E78 = savedNum;
            D_800D154C = saved;
            return;
        case 6:
            D_800CC2D0[idx].unkC8 = D_800D1890;
            return;
        case 7:
            D_800CC2D0[idx].unkB8 = 0.0f;
            return;
        case 8:
            a = func_15079A98(D_800D154C->unk222);
            if ((func_15079A98(D_800C3E78) - a) & 0x8000) {
                D_800D154C->unk221 = D_800D1890;
            }
            return;
        case 9:
            D_800D154C->unk244 = (D_800D1893 << 8) | D_800D1890;
            return;
        case 10:
            D_800D154C->unk236 = D_800D154C->unk23D + (s8)D_800D1890;
            return;
        case 11:
            D_800D154C->unk22A = D_800D1890;
            return;
        default:
            return;
    }
    switch (D_800D1893) {
        case 0:
            *var = D_800D1890;
            break;
        case 1:
            *var -= 1;
            break;
        case 2:
            *var += D_800BE9E4;
            break;
        case 3:
            *var += 1;
            break;
        case 4:
            *var -= D_800BE9E4;
            break;
        case 5:
            *var -= D_800CC264;
            break;
        case 6:
            *var += D_800CC264;
            break;
    }
}
