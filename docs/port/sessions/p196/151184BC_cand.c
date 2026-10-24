// gate_swing_update: world mesh record (D_800DBEF4, 0xA0 bytes) handler at D_800893D8 for the per-level push gate / door
// (levels 1 / 0x29, 0xB, 0x17, 0x28, 0x2F, 0x35, 0x3C, 0x40, 0x41; other levels do nothing). The level case gives the
// open angle, the handle point (scaled by +0x2C..+0x34), the squared reach (scaled by +0x34 squared) and the creak
// sound; bit 3 of +0x73 marks gates that only close when told to (state 1). A player (D_800CC2D0, D_8008FD8C of them)
// near the handle and not busy (+0x31C byte +0x6B < 4) pushes it: state 2 (opening) waits 50 ticks (+0x7C bits 8..15)
// then swings +0x0 up to the open angle with speed +0x84 / acceleration +0x80, plays sound 0x14 and sets state 3
// (open). With bit 2 of +0x73 the gate is pushed from the other side and only drives the player's +0x6B state (3 -> 4).
// The player's +0x6C..+0x70 get the handle position. Without a player it swings shut (state 1 -> 0). +0x4F bit 5 is set
// while it is opening or waiting.
void func_15060A30(s32, void *);
void func_15118324(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4);

void func_151184BC(u8 *rec) {
    f32 pos[3];
    f32 open = 40.0f;
    f32 reach = 40000.0f;
    f32 x;
    f32 y;
    f32 z;
    f32 acc;
    f32 spd;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 sound = 0x4B8;
    s32 state = rec[0x73] & 3;
    s32 back = rec[0x73] & 4;
    s32 closeOnly = rec[0x73] & 8;
    s32 timer;
    s32 started;
    s32 n;
    s32 i;
    u8 *player;
    u8 *p;
    u8 *q;

    switch (D_800BE9F0) {
        case 0x1:
        case 0x29:
            x = -13.0f;
            y = 76.0f;
            z = 354.0f;
            reach = 10000.0f;
            break;
        case 0xB:
            x = 70.0f;
            y = 120.0f;
            z = 329.0f;
            sound = 0x4BA;
            closeOnly = 8;
            break;
        case 0x17:
            x = 0.0f;
            y = 125.0f;
            z = 322.0f;
            break;
        case 0x28:
            open = 55.0f;
            x = 0.0f;
            y = 99.0f;
            z = 168.0f;
            closeOnly = 8;
            break;
        case 0x35:
            open = 20.0f;
            x = 0.0f;
            y = -328.0f;
            z = 549.0f;
            break;
        case 0x2F:
            open = 90.0f;
            reach = 5625.0f;
            x = 0.0f;
            y = 61.0f;
            z = 104.0f;
            closeOnly = 8;
            break;
        case 0x3C:
            open = 30.0f;
            reach = 10000.0f;
            x = 22.0f;
            y = 13.0f;
            z = 419.0f;
            closeOnly = 8;
            break;
        case 0x41:
            open = 45.0f;
            if (back == 4) {
                reach = -1.0f;
            }
            x = 0.0f;
            y = 25.0f;
            z = 336.0f;
            closeOnly = 8;
            break;
        case 0x40:
            open = 45.0f;
            x = 0.0f;
            y = 47.0f;
            z = 72.0f;
            closeOnly = 8;
            reach = 10000.0f;
            break;
        default:
            return;
    }
    x *= *(f32 *) (rec + 0x2C);
    y *= *(f32 *) (rec + 0x30);
    z *= *(f32 *) (rec + 0x34);
    reach *= *(f32 *) (rec + 0x34) * *(f32 *) (rec + 0x34);
    if (*(s32 *) (rec + 0x7C) == 0) {
        *(s32 *) (rec + 0x7C) = 2;
        if (state == 3) {
            *(f32 *) rec = open;
        }
    }
    acc = *(f32 *) (rec + 0x80);
    timer = (*(s32 *) (rec + 0x7C) >> 8) & 0xFF;
    started = *(s32 *) (rec + 0x7C) & 1;
    spd = *(f32 *) (rec + 0x84);
    func_15118324(rec, x, y, z, (u8 *) pos);

    player = NULL;
    if (state != 3 && state != 1) {
        n = D_8008FD8C;
        for (p = (u8 *) D_800CC2D0; p < (u8 *) D_800CC2D0 + n * 0x32C; p += 0x32C) {
            if (p[0x65] != 0 || p[0x104] != 0) {
                continue;
            }
            q = *(u8 **) (p + 0x31C);
            if (q[0x17] != 0 || q[0x27] != 0 || q[0x6B] >= 4) {
                continue;
            }
            if (*(f32 *) (p + 0x18) + 40.0f < pos[1]) {
                dy = (*(f32 *) (p + 0x18) + *(s16 *) (p + 0xE6)) - pos[1];
                dz = *(f32 *) (p + 0x1C) - pos[2];
                dx = *(f32 *) (p + 0x14) - pos[0];
                if (dz * dz + (dx * dx + dy * dy) < reach) {
                    player = p;
                    break;
                }
            }
        }
    }
    if (player == NULL && state == 2) {
        n = D_8008FD8C;
        p = (u8 *) D_800CC2D0;
        for (i = 0; i < n; i++, p += 0x32C) {
            if ((*(u8 **) (p + 0x31C))[0x6B] != 0) {
                player = p;
                break;
            }
        }
    }

    if (player != NULL || state == 2) {
        if (player != NULL && !started) {
            func_15060A30(0x16B, player);
        }
        if (!back) {
            if (!started) {
                timer = 50;
                started++;
                acc = 0.0f;
            }
            state = 2;
            if (player != NULL) {
                (*(u8 **) (player + 0x31C))[0x6B] = (timer != 0) ? 1 : 2;
            }
            if (timer != 0) {
                timer = (D_800BE9E4 < timer) ? timer - D_800BE9E4 : 0;
            } else {
                spd += acc;
                if (spd > 30.0f) {
                    spd = 30.0f;
                }
                acc += 0.03f;
                if (acc > 0.2f && *(u16 *) (rec + 0x74) == 0) {
                    func_151152A4(rec, sound, 0x7D00, 0x5DC, 0xDAC, 0);
                }
                *(f32 *) rec += spd;
                if (open <= *(f32 *) rec) {
                    *(f32 *) rec = open;
                    state = 3;
                    started = 0;
                    spd = 0.0f;
                    acc = 0.0f;
                    func_151152A4(rec, 0x14, 0x7D00, 0x5DC, 0xDAC, 4);
                    if (player != NULL) {
                        (*(u8 **) (player + 0x31C))[0x6B] = 0;
                    }
                }
            }
            if (player != NULL) {
                func_15118324(rec, x, y, z, (u8 *) pos);
                q = *(u8 **) (player + 0x31C);
                *(s16 *) (q + 0x6C) = (s32) pos[0];
                *(s16 *) (q + 0x6E) = (s32) pos[1];
                *(s16 *) (q + 0x70) = (s32) pos[2];
            }
        } else if (player != NULL && (q = *(u8 **) (player + 0x31C)) != NULL) {
            if (!started && q[0x6B] == 0) {
                timer = 50;
                started++;
            }
            if (timer != 0) {
                q[0x6B] = 3;
            } else if (q[0x6B] == 3) {
                q[0x6B] = 4;
                started = 0;
            }
            if (timer != 0) {
                timer = (D_800BE9E4 < timer) ? timer - D_800BE9E4 : 0;
            }
        }
        if (player != NULL && *(u8 **) (player + 0x31C) != NULL) {
            func_15118324(rec, x, y, z, (u8 *) pos);
            q = *(u8 **) (player + 0x31C);
            *(s16 *) (q + 0x6C) = (s32) pos[0];
            *(s16 *) (q + 0x6E) = (s32) pos[1];
            *(s16 *) (q + 0x70) = (s32) pos[2];
        }
    } else if ((!closeOnly || state == 1) && *(f32 *) rec > 0.0f) {
        if (!started) {
            acc = 0.1f;
            started++;
        }
        spd += 0.1f;
        state = 1;
        if (spd > 30.0f) {
            spd = 30.0f;
        }
        acc += 0.05f;
        *(f32 *) rec -= spd;
        if (*(f32 *) rec <= 0.0f) {
            *(f32 *) rec = 0.0f;
            started = 0;
            state = 0;
            acc = 0.0f;
            spd = 0.0f;
        }
    }

    rec[0x73] = (rec[0x73] & ~3) | state;
    *(s32 *) (rec + 0x7C) = (*(s32 *) (rec + 0x7C) & 0xFE) | (timer << 8) | started;
    *(f32 *) (rec + 0x80) = acc;
    *(f32 *) (rec + 0x84) = spd;
    rec[0x4F] &= ~0x60;
    if (state == 2 || (state == 0 && timer != 0)) {
        rec[0x4F] |= 0x20;
    }
}
