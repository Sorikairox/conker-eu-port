/* First-person look toggle: the look button (control bit 0x10) enters the first-person view (func_15123934 mode
 * 0x100, then func_151201D0) unless something blocks it (camera flag 0x80, forced views, the player swimming /
 * holding / in some modes, func_15125490, ...). In the first-person mode (+0x2C == 0x100) the look state +0x73C
 * is kept, the zoom / look bits leave the control masks, and the view limits +0x74C / +0x754 ease towards
 * +0x79C / +0x7A0 (func_150498A0). */
void func_1512317C(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *hold = *(u8 **)(p + 0x3D0);
    s32 noLookA = *(s32 *)(p + 0x5F0) & 0x100;
    s32 noLookB = *(s32 *)(p + 0x5F0) & 0x200;
    u8 mode;
    s32 badMode;
    s32 blocked;

#define PL (*(u8 **)(p + 0x3D4))
#define HOLD (*(u8 **)(p + 0x3D0))
#define MASK (*(u16 *)(p + 0x36A))
#define CTL (**(u16 **)(p + 0x36C))
#define LOOK (*(s16 *)(p + 0x73C))
    badMode = hold[0x104] != 0;
    if (badMode) {
        mode = p[0x23E];
        badMode = mode != 9 && mode != 0x38 && mode != 0x39 && mode != 0x3B && mode != 0x37 && mode != 0x15 &&
                  mode != 0x26 && mode != 0x3A;
    }
    blocked = (*(s32 *)(p + 0x2C) & 0x80) || (*(s32 *)(p + 0x84) & 0x1000000) ||
              (*(f32 *)(hold + 0x28) != 0.0f && hold[0xAD] == 0 && *(s32 *)(PL + 0x9C) == 0 && !noLookA &&
               !noLookB && p[0x23E] != 3) ||
              (hold[0x65] != 0 && !noLookA && !noLookB) || badMode || func_15125490(arg0) != 0 ||
              HOLD[0x1CA] == 0 || ((PL[0x4E] & 0xF) == 1 && 15.0f < *(f32 *)(HOLD + 0x3C)) || PL[0x1AC] != 0;

    if ((CTL & 0x10) && !blocked) {
        if ((MASK & 0x10) && func_15123934(arg0, 0x100, 4, *(s32 *)(p + 0x134), 1) != 0) {
            func_151201D0(p);
        }
        return;
    }
    if (*(s32 *)(p + 0x2C) == 0x100 && LOOK == 0) {
        func_151239CC(arg0, 1);
        PL[0x198] = 0;
        PL[0x197] = 0;
        *(s16 *)(p + 0x5F8) = 1;
        *(s16 *)(p + 0x5FC) = 2;
        MASK &= 0xFFEF;
        CTL &= 0xFFEF;
    }
    if (*(s32 *)(p + 0x2C) == 0x100 || LOOK != 0) {
        MASK &= ~0x10;
        CTL &= ~0x10;
    }
    PL[0x198] = LOOK;
    if (LOOK != 0) { /* the asm also tests == 3 after != 0 (dead) */
        func_150498A0((f32 *)(p + 0x74C), 0.0f, (f32 *)(p + 0x79C), 4.0f, 9.0f, *(f32 *)(p + 0x7B4));
        func_150498A0((f32 *)(p + 0x754), 0.0f, (f32 *)(p + 0x7A0), 4.0f, 9.0f, *(f32 *)(p + 0x7B4));
    }
    if (*(s32 *)(p + 0x2C) != 0x100 && LOOK != 0) {
        LOOK = 0;
    }
#undef PL
#undef HOLD
#undef MASK
#undef CTL
#undef LOOK
}
