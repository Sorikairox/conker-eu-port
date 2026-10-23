extern s16 D_800DC630[4][4][4];
extern u8 D_800DC4F0[];

/* free_camera_turn: turn of camera `cam` from its player's four free-camera axis records (D_800DC4F0, 0x4C per
 * player: left +0, right +0xC, +0x18, +0x24, each with direction byte +0 and position +4; last side +0x30). Called by
 * func_1512B2C4 (`unused` is never read). Left only / right only sets the last side 0 / 1 (+0x18 / +0x24: 2 / 3).
 * With left or right blocked (direction 2): *turn = w - (left + 1) or (right + 1) - w (w = viewport width + 1); both
 * blocked: the nearer side (or the last one) decides, the countdown +0x5FE drops by D_800BE9E4 (unless the holder
 * +0x3D0 has +0xAD == 1 or +0x3D4 has +0x120 set) and +0x3F0 = 30 unless mode +0x2C is 0x80; +0x26C = 0.005,
 * returns 1. Neither: both directions = 4, *turn decays by 10 %, +0x5FE = 50, returns 0. While +0x3F0 counts down
 * the distances +0x374 / +0x348 are saved in +0x3F4 / +0x3F8 and set to 150 / 275, and restored after. */
s32 func_1512BCA0(u8 *cam, f32 *turn, f32 *unused) {
    u8 *e = D_800DC4F0 + cam[0x23D] * 0x4C;
    f32 left = (f32)*(s32 *)(e + 0x4) + 1.0f;
    f32 right = (f32)*(s32 *)(e + 0x10) + 1.0f;
    u8 dl = e[0x0];
    u8 dr = e[0xC];
    u8 d2 = e[0x18];
    u8 d3 = e[0x24];
    s32 hit = 0;
    f32 w;
    f32 saved;

    if (dl == 2 && dr != 2) {
        e[0x30] = 0;
    } else if (dl != 2 && dr == 2) {
        e[0x30] = 1;
    }
    if (d2 == 2 && d3 != 2) {
        e[0x30] = 2;
    } else if (d2 != 2 && d3 == 2) {
        e[0x30] = 3;
    }
    if (dl == 2 || dr == 2) {
        w = D_800DC630[cam[0x23D]][*(s16 *)(cam + 0x1B4)][0] + 1;
        if (dl == 2 && dr == 2) {
            if ((*(u8 **)(cam + 0x3D0))[0xAD] != 1 && (*(u8 **)(cam + 0x3D4))[0x120] == 0) {
                *(s16 *)(cam + 0x5FE) -= D_800BE9E4;
                if (*(s16 *)(cam + 0x5FE) < 0) {
                    *(s16 *)(cam + 0x5FE) = 0;
                }
            }
            if (*(s32 *)(cam + 0x2C) != 0x80) {
                *(s16 *)(cam + 0x3F0) = 30;
            }
            e = D_800DC4F0 + cam[0x23D] * 0x4C;
            if (*(s32 *)(e + 0x10) < *(s32 *)(e + 0x4)) {
                *turn = w - left;
            } else if (*(s32 *)(e + 0x4) < *(s32 *)(e + 0x10)) {
                *turn = right - w;
            } else if (e[0x30] == 0) {
                *turn = w - left;
            } else {
                *turn = right - w;
            }
        } else {
            *(s16 *)(cam + 0x3F0) = 0;
            *(s16 *)(cam + 0x5FE) = 50;
            e = D_800DC4F0 + cam[0x23D] * 0x4C;
            /* (the asm tests +0x23C here; both of its branches compute the same value) */
            if (e[0] == 2) {
                *turn = w - ((f32)*(s32 *)(e + 0x4) + 1.0f);
            } else {
                *turn = ((f32)*(s32 *)(e + 0x10) + 1.0f) - w;
            }
        }
        *(f32 *)(cam + 0x26C) = 0.005f;
        hit = 1;
    } else {
        e[0x0] = 4;
        e[0xC] = 4;
        *turn -= *turn * 0.1f;
        *(s16 *)(cam + 0x5FE) = 50;
    }
    if (*(s16 *)(cam + 0x3F0) != 0) {
        *(s16 *)(cam + 0x3F0) -= D_800BE9E4;
        if (*(s16 *)(cam + 0x3F0) < 0) {
            *(s16 *)(cam + 0x3F0) = 0;
        }
        if (*(f32 *)(cam + 0x3F4) == -1.0f) {
            *(f32 *)(cam + 0x3F4) = *(f32 *)(cam + 0x374);
            *(f32 *)(cam + 0x3F8) = *(f32 *)(cam + 0x348);
            *(f32 *)(cam + 0x374) = 150.0f;
            *(f32 *)(cam + 0x348) = 275.0f;
        }
    } else if (*(f32 *)(cam + 0x3F4) != -1.0f) {
        saved = *(f32 *)(cam + 0x3F8);
        *(f32 *)(cam + 0x374) = *(f32 *)(cam + 0x3F4);
        *(f32 *)(cam + 0x3F4) = -1.0f;
        *(f32 *)(cam + 0x3F8) = -1.0f;
        *(f32 *)(cam + 0x348) = saved;
    }
    return hit;
}
