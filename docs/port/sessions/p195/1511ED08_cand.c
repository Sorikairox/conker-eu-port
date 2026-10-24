// mover_slide_step: world mesh record (D_800DBEF4, 0xA0 bytes) handler at D_8008936C for sliding / bobbing scenery.
// +0x80 is the command (1 = open, 0 = close, anything else keeps going with a 90x step); starting an open / close from
// the other end plays the D_80089600 row (+0x3C low half) move / start sound. +0x3C high half picks the motion; +0x84
// latches the rest position on the first call (+0x7C, set to 1 at the end) and +0x73 bits 0..1 hold the state
// (0 closed, 1 closing, 2 opening, 3 open). Types 0 / 3: move y +0x8 / x +0x4 down to -110 / 260; 2, 8: x up by at most
// 70 (80 for type 2); 4, 6, 7: x down by at most 70 (80 / 82, type 6 at half speed); 10, 11: y bobs as sin(phase) * 10
// with a splash sound when the phase wraps after 4 pi; 12, 13: y = 180 - sin(phase) * 10 (10 / 12 add a fixed step first).
void func_1511ED08(u8 *rec) {
    f32 *x = (f32 *) (rec + 4);
    f32 *y = (f32 *) (rec + 8);
    f32 *rest = (f32 *) (rec + 0x84);
    s32 cmd = *(s32 *) (rec + 0x80);
    s32 state = rec[0x73] & 3;
    s32 sfx = -1;
    s32 type;
    s16 sound;
    f32 dir;
    f32 dt;
    f32 range;
    f32 speed;
    f32 lim;

    if (cmd == 1) {
        if (state == 0 || state == 1) {
            state = 2;
            sfx = 0;
        }
        dir = 1.0f;
    } else if (cmd == 0) {
        if (state == 3 || state == 2) {
            state = 1;
            sfx = 1;
        }
        dir = -1.0f;
    } else {
        dir = 90.0f;
    }
    if (sfx != -1) {
        sound = ((s16 *) &D_80089600[*(s32 *) (rec + 0x3C) & 0xFFFF])[sfx];
        if (sound > 0) {
            func_151152A4(rec, sound, 0x5DC0, 0xC8, 0x9C4, 0);
        }
    }
    dt = D_800BE9E4;
    type = *(s32 *) (rec + 0x3C) >> 16;
    range = 70.0f;
    speed = 6.0f;
    dir *= dt;
    if (type == 2 || type == 4) {
        range = 80.0f;
    } else if (type == 6) {
        speed = 3.0f;
        range = 82.0f;
    }
    switch (type) {
        case 0:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *y;
            }
            *y -= dir * speed;
            if (*y > *rest) {
                *y = *rest;
                state = 0;
            }
            if (*y < -110.0f) {
                *y = -110.0f;
                state = 3;
            }
            break;
        case 3:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *x;
            }
            *x -= dir * 3.0f;
            if (*x < 260.0f) {
                *x = 260.0f;
                state = 3;
            }
            if (*x > *rest) {
                *x = *rest;
                state = 0;
            }
            break;
        case 2:
        case 8:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *x;
            }
            *x += dir * speed;
            lim = *rest + range;
            if (*x > lim) {
                *x = lim;
                state = 3;
            }
            if (*x < *rest) {
                *x = *rest;
                state = 0;
            }
            break;
        case 4:
        case 6:
        case 7:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *x;
            }
            *x -= dir * speed;
            lim = *rest - range;
            if (*x > *rest) {
                *x = *rest;
                state = 0;
            }
            if (*x < lim) {
                *x = lim;
                state = 3;
            }
            break;
        case 10:
            *rest += 0.01f;
            dt = D_800BE9E4;
            /* fallthrough */
        case 11:
            *rest += 0.04f * dt;
            *y = sinf(*rest) * 10.0f;
            if (*rest > 12.566371f) {
                *rest -= 12.566371f * ((func_150ADA20() & 4) + 1);
                func_151152A4(rec, 0x503, 0x1F40, 0x96, 0x258, 0);
            }
            break;
        case 12:
            *rest += 0.01f;
            dt = D_800BE9E4;
            /* fallthrough */
        case 13:
            *rest += 0.04f * dt;
            *y = 180.0 - sinf(*rest) * 10.0f;
            break;
    }
    *(s32 *) (rec + 0x7C) = 1;
    rec[0x73] = (rec[0x73] & ~3) | state;
}
