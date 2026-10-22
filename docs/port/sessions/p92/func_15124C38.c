/* Camera target height (camera `arg0`). With `out` the height is only returned through it (also while the
 * camera is frozen, +0x7F4); else it is eased into +0x2C0 (speed +0x2A0, func_150498A0 with the frame step +0x7B4).
 * The base offset is the target's (PL = +0x3D4) height +0x114 scaled per mode (first person +0x2C bit 0x100,
 * PL +0x4E kind 1, +0x23E / +0x23C / +0x600 states, look-up +0x77C) plus the holder's (HOLD = +0x3D0) +0xCC,
 * raised by 50 / 150 or set to 135 by +0x5F0 bits 0x100 / 0x200 / 0x800; without a target it is the holder's
 * model height (func_1507C7C0). A target on a vehicle (PL +0x120) follows the holder's position y
 * (func_1507E1D0) at once. Otherwise the height is the holder's y +0x18 + 1/4 offset (+0x2C bit 0x80 or
 * func_15125490), floor +0x180 + offset (+0x84 bit 0x20000000, or no water +0x360 and low / far:
 * +0x28 < 170, +0x370 > 300), y + offset (cutscene D_800C3671, HOLD +0x137 / +0x84 == 0x194 / swimming +0xAD),
 * else the floor + its height above it (+0x28) scaled by +0x28 / 300 (0..1) + offset. Hanging (HOLD +0x102):
 * close to the camera (+0x370 < 100) 10 below / above y by the camera's height +0x2FC, else y. */
void func_15124C38(struct108 *arg0, f32 *out) {
    u8 *p = (u8 *)arg0;
    u8 *pl;
    u8 *hold;
    s16 h;
    s16 w;
    s16 d;
    f32 ofs;
    f32 y;
    f32 k;
    f32 speed;
    f32 rate;
    f32 v[3];
    u8 hang;

    if (*(u16 *)(p + 0x7F4) != 0 && out == NULL) {
        return;
    }
    pl = PL;
    if (pl != NULL) {
        if ((pl[0x4E] & 0xF) == 1) {
            if (CAM_W(0x2C) & 0x100) {
                ofs = (f32)*(s16 *)(pl + 0x114) * 0.65f;
            } else {
                ofs = (f32)*(s16 *)(pl + 0x114) * 0.55f;
            }
        } else if (CAM_W(0x2C) & 0x100) {
            if (p[0x23E] == 0) {
                if (CAM_F(0x77C) < -15.0f) {
                    ofs = (f32)*(s16 *)(HOLD + 0xCC) + (f32)*(s16 *)(pl + 0x114) * 0.9f;
                } else {
                    ofs = (f32)*(s16 *)(HOLD + 0xCC) + (f32)*(s16 *)(pl + 0x114) * 0.75f;
                }
            } else {
                ofs = (f32)*(s16 *)(HOLD + 0xCC) + (f32)*(s16 *)(pl + 0x114) * 0.85f;
            }
        } else if (p[0x23C] == 0 && p[0x600] != 0) {
            ofs = (f32)*(s16 *)(HOLD + 0xCC) + (f32)*(s16 *)(pl + 0x114);
        } else {
            ofs = (f32)*(s16 *)(HOLD + 0xCC) + (f32)*(s16 *)(pl + 0x114) * 0.75f;
        }
        if (CAM_W(0x5F0) & 0x100) {
            ofs += 50.0f;
        } else if (CAM_W(0x5F0) & 0x200) {
            ofs += 150.0f;
        } else if (CAM_W(0x5F0) & 0x800) {
            ofs = 135.0f;
        }
    } else {
        func_1507C7C0((struct127 *)HOLD, &h, &w, &d);
        ofs = (f32)h;
        pl = PL;
    }
    if (pl[0x120] != 0) {
        func_1507E1D0(HOLD, &v[0], &v[1], &v[2]);
        func_150498A0((f32 *)(p + 0x2C0), v[1], (f32 *)(p + 0x2A0), 4.0f, 8.0f, CAM_F(0x7B4));
        return;
    }
    switch (p[0x23E]) {
        case 0xC: case 0x9: case 0x38: case 0x39: case 0x37: case 0x3B: case 0x12: case 0x15: case 0x26: case 0x3A:
            if (CAM_W(0x2C) & 0x100) {
                ofs += 30.0f;
            }
            break;
    }
    if ((CAM_W(0x2C) & 0x80) || func_15125490(arg0) != 0) {
        hold = HOLD;
        y = *(f32 *)(hold + 0x18) + ofs * 0.25f;
    } else {
        hold = HOLD;
        if (CAM_W(0x84) & 0x20000000) {
            y = *(f32 *)(hold + 0x180) + ofs;
        } else if (D_800C3671 != 0 || hold[0x137] != 0 || *(u16 *)(hold + 0x84) == 0x194 || hold[0xAD] == 1) {
            y = *(f32 *)(hold + 0x18) + ofs;
        } else if (-10000.0f == CAM_F(0x360) && !(CAM_W(0x84) & 0x200000) && *(f32 *)(hold + 0x28) < 170.0f &&
                   300.0f < CAM_F(0x370)) {
            y = *(f32 *)(hold + 0x180) + ofs;
        } else {
            k = *(f32 *)(hold + 0x28) * 0.0033333334f;
            if (k < 0.0f) {
                k = 0.0f;
            } else if (1.0f < k) {
                k = 1.0f;
            }
            y = (*(f32 *)(hold + 0x180) + *(f32 *)(hold + 0x28) * k) + ofs;
        }
    }
    hang = hold[0x102];
    if (hang != 0) {
        if (CAM_F(0x370) < 100.0f) {
            if (CAM_F(0x2FC) < *(f32 *)(hold + 0x18)) {
                y = *(f32 *)(hold + 0x18) - 10.0f;
            } else {
                y = *(f32 *)(hold + 0x18) + 10.0f;
            }
        } else {
            y = *(f32 *)(hold + 0x18);
        }
    }
    if (out != NULL) {
        *out = y;
        return;
    }
    if (p[0x23C] != 0) {
        CAM_F(0x2C0) = y;
        CAM_F(0x2A0) = 0.0f;
        return;
    }
    if (CAM_W(0x5F0) & 0x80) {
        speed = 5.0f;
        rate = 8.0f;
    } else if (CAM_W(0x2C) & 0x100) {
        speed = 5.0f;
        rate = 9.0f;
    } else if (hang != 0) {
        speed = 7.0f;
        rate = 9.0f;
    } else {
        speed = 4.0f;
        rate = 8.0f;
    }
    if ((CAM_W(0x84) & 0x200000) && y < CAM_F(0x2CC)) {
        speed += speed;
        rate += rate;
    }
    func_150498A0((f32 *)(p + 0x2C0), y, (f32 *)(p + 0x2A0), speed, rate, CAM_F(0x7B4));
}
