s32 func_100127D0(void);
void func_151F2BA8(void);
struct127 *func_15072208(struct127 *, s32);
void func_15060F28(struct127 *, s32);
void func_1501DE84(s32 slot);
void func_1517F3B0(s32, s32, s32, s32, s8, s32);
void func_1000E17C(void);

/* End of cutscene slot `slot` (called by func_1501E220 with the slot left in a0): func_151F2BA8 when
 * func_100127D0, remove object 0's attachment 0 (func_15072208 / func_15060F28), run func_1501DE84(slot) once and
 * again while D_800C40B9 was set before the call and no level change is pending (D_800C35C4); screen colour
 * func_1517F3B0(0, 0, 0, 0x19, 0, 0) unless D_800C39C9, D_800C40AA == 1 or D_800C40AD; clear +0xA4 of every live
 * object (D_800CC2D0, 25), D_800C3663 = 0, func_1000E17C, D_800DBFF4[0] = 4, D_800C3A92 = 1. */
void func_1501DF70(s32 slot) {
    struct127 *p;
    u8 flag;
    s32 i;

    if (func_100127D0() != 0) {
        func_151F2BA8();
    }
    p = func_15072208(D_800CC2D0, 0);
    if (p != NULL) {
        func_15060F28(p, 0);
    }
    do {
        flag = D_800C40B9;
        func_1501DE84(slot);
    } while (flag != 0 && D_800C35C4 == 0);
    if (D_800C39C9 == 0 && (s8)D_800C40AA != 1 && D_800C40AD == 0) {
        func_1517F3B0(0, 0, 0, 0x19, 0, 0);
    }
    for (i = 0; i < 25; i++) {
        if (D_800CC2D0[i].interaction_state != 0) {
            *((u8 *)&D_800CC2D0[i] + 0xA4) = 0;
        }
    }
    D_800C3663 = 0;
    func_1000E17C();
    D_800DBFF4[0] = 4;
    D_800C3A92 = 1;
}
