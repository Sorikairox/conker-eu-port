s32 func_1512DC20(u8 *arg0);
s32 func_1509BE40(s32, s32, ...);
s32 func_1512DAD0(u8 *, s32, s32 *);
s32 func_151239CC(struct108 *arg0, s32 arg1);
u8 *func_1512DB74(u8 *arg0);
void func_15127EB8(struct108 *);
void func_1512DC60(struct108 *arg0);
void func_151CA484(u8 *arg0);
s32 func_15123934(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_15127FEC(struct108 *arg0, s32 arg1, s32 arg2);
void func_1512EE50(struct108 *);
void func_151CA150(u8 *arg0, s32 arg1);
void func_15126138(struct108 *);
void func_150A09D0(s32 arg0);
void func_150A16A4(struct127 *arg0);
void func_151283B8(struct108 *);
void func_15128D50(struct108 *, f32 *, f32 *);
f32 func_15048A70(f32 arg0, f32 arg1);
void func_1510B6A8(s32 player, f32 fovX, f32 fovY, f32 scale, f32 width);
void func_1501B300(s32 player);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
void func_151236D0(struct108 *arg0);
f32 sinf(f32);
f32 cosf(f32);
extern u8 *D_800DC440;       /* saved camera states, 0x9A0 bytes each */
extern u16 D_800BEB30[];     /* per player: view flags (camera +0x36A) */
extern s32 D_800898C0;       /* frames to skip the "restore saved camera" event */
extern s32 D_800898C4[];     /* per player: saved +0x3D4 byte 0x197 */
extern s32 D_800898D4[];     /* per player: saved +0x3D4 byte 0x198 */
extern f32 D_800898E4[3];    /* event 7 orbit offset {0, 0, -400} */
extern u8 D_800C3A92;
extern s32 D_800C3A98;
extern s32 D_800C3A9C;
extern f32 D_800C3A6C;

/* camera_process_events: per-frame camera event pump (called by func_15122C5C and the game camera setup in
 * game_eu_4A070.c). +0x6CC = 0; a pending script request +0x734 is started (func_1512DAD0 with record
 * D_800D34B8[id & 0xFFF], 0x34 bytes, id kept in +0x700) when func_1509BE40(1, id, 6, 0x9000) and +0x738 allow it,
 * else cleared. If the queue (func_1512DC20) is busy, only flag 1 of +0x2C sets mode 0xC; otherwise every queued
 * event (func_1512DB74: {type, data}) is handled until the queue is empty:
 *  1: copy a camera request (mode, values, point, ...) from the data into +0x6FC..+0x72C, +0x6CC = 1;
 *  5: save the camera: D_800DC440[data] = D_800DBFF0[player], keeping the target's +0x197 / +0x198 bytes in
 *     D_800898C4 / D_800898D4 (or resetting them, mode 1, when the target's +0x78 is 0); then mode 0xA;
 *  6: restore it (unless D_800898C0 counts down, only in camera mode 0x40000): with +0x834 set only the view flags
 *     and func_15127FEC; else D_800DBFF0[player] = D_800DC440[data], re-applies the request and the target bytes,
 *     resets eye / target history, and reruns the per-frame camera steps;
 *  7: place the camera at a fixed eye (+0x2F8) and target (data kind 0 / 2: given; else orbiting the eye at
 *     -400 by the data angles), then optional FOV (func_1510B6A8) and the camera collision probe func_1510ED24;
 *  8: +0x3A4 = data[3]; 9: +0x364 = data[0]; 10: +0x834 = data +0x10, +0x820 = data[3] (999: target heading - 180).
 */
void func_15129220(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    s32 *ev;
    u8 *d;
    u8 *tgt;
    s32 *dst;
    s32 *src;
    s32 i;
    u8 pl;
    f32 heading;
    f32 ang;
    f32 pos[3];
    f32 probe;

    *(s16 *)(p + 0x6CC) = 0;
    if (*(s32 *)(p + 0x734) != 0 && func_1512DC20(p) != 0) {
        if (func_1509BE40(1, *(s32 *)(p + 0x734), 6, 0x9000) != 0 && *(s32 *)(p + 0x738) != 0) {
            func_1512DAD0(p, 1, (s32 *)(D_800D34B8 + (*(s32 *)(p + 0x734) & 0xFFF) * 0x34));
            *(s16 *)(p + 0x700) = *(s32 *)(p + 0x734) & 0xFFF;
        } else {
            *(s32 *)(p + 0x734) = 0;
            *(s32 *)(p + 0x738) = 0;
        }
    }
    if (func_1512DC20(p) != 0) {
        if (*(s32 *)(p + 0x2C) & 1) {
            func_151239CC(arg0, 0xC);
        }
        return;
    }
    while (func_1512DC20(p) == 0) {
        ev = (s32 *)func_1512DB74(p);
        switch (ev[0]) {
        case 5: /* save the camera state */
            tgt = *(u8 **)(p + 0x3D4);
            p[0x23E] = tgt[0x78];
            if (p[0x23E] == 0) {
                func_151239CC(arg0, 1);
                (*(u8 **)(p + 0x3D4))[0x198] = 0;
                (*(u8 **)(p + 0x3D4))[0x197] = 0;
                *(s16 *)(p + 0x5F8) = 1;
                *(s16 *)(p + 0x5FC) = 2;
                (*(u8 **)(p + 0x3D4))[0x198] = 0;
                *(s16 *)(p + 0x73C) = 0;
                func_15127EB8(arg0);
                D_800898C4[p[0x23D]] = 0;
                D_800898D4[p[0x23D]] = 0;
            } else {
                D_800898C4[p[0x23D]] = tgt[0x197];
                D_800898D4[p[0x23D]] = (*(u8 **)(p + 0x3D4))[0x198];
            }
            func_1512DC60(arg0);
            if (p[0x84C] != 0) {
                func_151CA484(p);
                p[0x84C] = 0;
            }
            src = (s32 *)((u8 *)D_800DBFF0 + p[0x23D] * 0x9A0);
            dst = (s32 *)(D_800DC440 + ev[1] * 0x9A0);
            for (i = 0; i < 0x9A0 / 4; i++) {
                dst[i] = src[i];
            }
            func_15123934(arg0, 0x40000, 0, 0, 0xA);
            *(s32 *)(p + 0x5F0) |= 4;
            *(f32 *)(p + 0x3A4) = -1.0f;
            break;

        case 6: /* restore the saved camera state */
            p[0x23E] = (*(u8 **)(p + 0x3D4))[0x78];
            if (D_800898C0 != 0) {
                D_800898C0--;
                break;
            }
            if (*(s32 *)(p + 0x2C) != 0x40000) {
                break;
            }
            heading = *(f32 *)(p + 0x3A4);
            if (D_800D2DB0 != 999.0f) {
                heading = D_800D2DB0;
                D_800D2DB0 = 999.0f;
            }
            func_151239CC(arg0, 0xA);
            if (D_800C3A92 != 0) {
                *(f32 *)(p + 0x820) = 999.0f;
                *(s16 *)(p + 0x834) = 0;
                *(s16 *)(p + 0x7F4) = 0;
            }
            if (*(u16 *)(p + 0x834) != 0) {
                pl = p[0x23D];
                *(s32 *)(p + 0x36C) = ((s32 *)D_800BE728[0])[pl];
                *(u16 *)(p + 0x36A) = D_800BEB30[pl];
                func_15127FEC(arg0, D_800C3A9C, D_800C3A98);
                p[0x23C] = 0;
                break;
            }
            src = (s32 *)(D_800DC440 + ev[1] * 0x9A0);
            dst = (s32 *)((u8 *)D_800DBFF0 + p[0x23D] * 0x9A0);
            for (i = 0; i < 0x9A0 / 4; i++) {
                dst[i] = src[i];
            }
            pl = p[0x23D];
            tgt = *(u8 **)(p + 0x3D4);
            *(s32 *)(p + 0x36C) = ((s32 *)D_800BE728[0])[pl];
            *(u16 *)(p + 0x36A) = D_800BEB30[pl];
            p[0x23C] = 1;
            p[0x23E] = tgt[0x78];
            func_1512EE50(arg0);
            if (D_800898D4[p[0x23D]] != 0) {
                *(u16 *)(p + 0x36A) |= 0x10;
                **(u16 **)(p + 0x36C) |= 0x10;
                heading = *(f32 *)(p + 0x774);
            } else if (D_800898C4[p[0x23D]] != 0) {
                if ((p[0x23E] == 0xC && *(u16 *)(*(u8 **)(p + 0x3D0) + 0x84) != 0x76) || p[0x23E] == 0x1B
                    || (**(u16 **)(p + 0x36C) & 0x10)) {
                    *(u16 *)(p + 0x36A) |= 0x10;
                    **(u16 **)(p + 0x36C) |= 0x10;
                    (*(u8 **)(p + 0x3D4))[0x197] = D_800898C4[p[0x23D]];
                    func_151CA150(p, p[0x23E]);
                    heading = *(f32 *)(p + 0x774);
                } else {
                    (*(u8 **)(p + 0x3D4))[0x198] = 0;
                    *(s16 *)(p + 0x73C) = 0;
                    D_800898C4[p[0x23D]] = 0;
                    D_800898D4[p[0x23D]] = 0;
                    func_15127EB8(arg0);
                }
            } else {
                (*(u8 **)(p + 0x3D4))[0x198] = 0;
                *(s16 *)(p + 0x73C) = 0;
                func_15127EB8(arg0);
            }
            func_15126138(arg0);
            if (*(s32 *)(p + 0x5F0) & 2) {
                heading = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x40) - 180.0f;
            }
            *(f32 *)(p + 0x37C) = heading;
            *(f32 *)(p + 0x39C) = heading * 0.017453292f;
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x2E0))[i] = ((f32 *)(p + 0x2BC))[i];
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x2EC))[i] = ((f32 *)(p + 0x2F8))[i];
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x2C8))[i] = ((f32 *)(p + 0x2BC))[i];
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)(p + 0x304))[i] = ((f32 *)(p + 0x2F8))[i];
            }
            func_150A09D0(D_800BE9E4);
            func_150A16A4((struct127 *)((u8 *)D_800CC2D0 + p[0x23D] * 0x32C));
            func_1512EE50(arg0);
            func_15128D50(arg0, NULL, NULL);
            func_151283B8(arg0);
            func_15126138(arg0);
            *(s32 *)(p + 0x5F0) |= 4;
            *(f32 *)(p + 0x670) = 0.0f;
            *(f32 *)(p + 0x678) = 0.0f;
            p[0x8ED] = 1;
            p[0x23C] = 1;
            *(f32 *)(p + 0x674) = 1.0f;
            break;

        case 8:
            *(f32 *)(p + 0x3A4) = ((f32 *)ev[1])[3];
            break;

        case 9:
            *(f32 *)(p + 0x364) = ((f32 *)ev[1])[0];
            break;

        case 10:
            d = (u8 *)ev[1];
            *(s16 *)(p + 0x834) = *(s32 *)(d + 0x10);
            if (*(f32 *)(d + 0xC) == 999.0f) {
                *(f32 *)(p + 0x820) = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x40) - 180.0f;
            } else {
                *(f32 *)(p + 0x820) = *(f32 *)(d + 0xC);
            }
            break;

        case 7: /* fixed camera: eye from the data, target given or orbiting the eye */
            d = (u8 *)ev[1];
            *(f32 *)(p + 0x2F8) = *(f32 *)(d + 0x14);
            *(f32 *)(p + 0x2FC) = *(f32 *)(d + 0x18);
            *(f32 *)(p + 0x300) = *(f32 *)(d + 0x1C);
            if (*(s32 *)d == 0 || *(s32 *)d == 2) {
                *(f32 *)(p + 0x2A4) = *(f32 *)(d + 0x20);
                *(f32 *)(p + 0x2A8) = *(f32 *)(d + 0x24);
                *(f32 *)(p + 0x2AC) = *(f32 *)(d + 0x28);
                *(f32 *)(p + 0x19C) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x1A0) = *(f32 *)(d + 0x34);
                *(f32 *)(p + 0x1A4) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x1A8) = *(f32 *)(d + 0x34);
                for (i = 0; i < 3; i++) {
                    ((f32 *)(p + 0x2BC))[i] = ((f32 *)(p + 0x2A4))[i];
                }
                *(f32 *)(p + 0x3A8) = 0.0f;
                *(f32 *)(p + 0x5E8) = 0.0f;
                *(f32 *)(p + 0x38C) = 0.0f;
                *(f32 *)(p + 0x5EC) = *(f32 *)(d + 0x2C);
            } else {
                pos[0] = D_800898E4[0];
                pos[1] = D_800898E4[1];
                pos[2] = D_800898E4[2];
                while (*(f32 *)(d + 0x20) > 180.0f) {
                    *(f32 *)(d + 0x20) -= 360.0f;
                }
                while (*(f32 *)(d + 0x24) > 180.0f) {
                    *(f32 *)(d + 0x24) -= 360.0f;
                }
                while (*(f32 *)(d + 0x28) > 180.0f) {
                    *(f32 *)(d + 0x28) -= 360.0f;
                }
                *(f32 *)(p + 0x5EC) = *(f32 *)(d + 0x20);
                /* pitch by +0x24 */
                ang = *(f32 *)(d + 0x24) * 0.017453292f;
                pos[1] = sinf(ang) * -pos[2];
                pos[2] = cosf(ang) * pos[2];
                if (D_800DBFF4[0] != 0) {
                    *(f32 *)(p + 0x37C) = *(f32 *)(d + 0x28);
                    *(f32 *)(p + 0x380) = *(f32 *)(d + 0x28);
                    *(f32 *)(p + 0x39C) = *(f32 *)(p + 0x37C) * 0.017453292f;
                    *(f32 *)(p + 0x3A0) = *(f32 *)(p + 0x380) * 0.017453292f;
                }
                /* yaw: from the current heading +0x37C toward +0x28 */
                heading = *(f32 *)(p + 0x37C);
                ang = (heading + func_15048A70(heading, *(f32 *)(d + 0x28)) * 1.0f) * 0.017453292f;
                pos[0] = sinf(ang) * pos[2];
                pos[2] = cosf(ang) * pos[2];
                pos[0] += *(f32 *)(d + 0x14);
                pos[1] += *(f32 *)(d + 0x18);
                pos[2] += *(f32 *)(d + 0x1C);
                *(f32 *)(p + 0x19C) = *(f32 *)(d + 0x2C);
                *(f32 *)(p + 0x1A0) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x1A4) = *(f32 *)(d + 0x2C);
                *(f32 *)(p + 0x1A8) = *(f32 *)(d + 0x30);
                *(f32 *)(p + 0x2A4) = pos[0];
                *(f32 *)(p + 0x2A8) = pos[1];
                *(f32 *)(p + 0x2AC) = pos[2];
                for (i = 0; i < 3; i++) {
                    ((f32 *)(p + 0x2BC))[i] = ((f32 *)(p + 0x2A4))[i];
                }
                *(f32 *)(p + 0x3A8) = 0.0f;
                *(f32 *)(p + 0x5E8) = 0.0f;
                *(f32 *)(p + 0x38C) = 0.0f;
            }
            if ((&D_800C35EA)[*(s32 *)(d + 4)] == 1) {
                D_800C3A6C = *(f32 *)(d + 8);
                func_1510B6A8(p[0x23D], *(f32 *)(p + 0x19C), *(f32 *)(p + 0x1A0), 1.0f, 0.0f);
            }
            if (D_800DBFF4[0] != 0) {
                func_1501B300(0);
            }
            if (D_800BEAC0 == 0) {
                func_1510ED24((s32)(p + 0x644), (s32)(p + 0x648), (s32)&probe, (s32)(p + 0x360), (s32)(p + 0x640), 0,
                              *(f32 *)(p + 0x2F8), *(f32 *)(p + 0x2FC), *(f32 *)(p + 0x300), *(f32 *)(p + 0x2FC), 0, 0,
                              -10000.0f, *(f32 *)(p + 0x2FC));
                func_151236D0(arg0);
            }
            break;

        case 1: /* camera request */
            d = (u8 *)ev[1];
            *(s32 *)(p + 0x6FC) = d[0x17];
            *(s32 *)(p + 0x718) = *(s32 *)(d + 0x18);
            *(s32 *)(p + 0x71C) = *(s32 *)(d + 0x1C);
            *(s32 *)(p + 0x704) = *(s32 *)(d + 0x20);
            *(s16 *)(p + 0x70C) = *(s16 *)(d + 0x0);
            *(s16 *)(p + 0x70E) = *(s16 *)(d + 0x2);
            *(s16 *)(p + 0x710) = *(s16 *)(d + 0x4);
            *(s16 *)(p + 0x712) = *(s16 *)(d + 0x6);
            *(s16 *)(p + 0x714) = *(s16 *)(d + 0x8);
            *(s16 *)(p + 0x716) = *(s16 *)(d + 0xA);
            *(f32 *)(p + 0x720) = *(f32 *)(d + 0x28);
            *(f32 *)(p + 0x724) = *(f32 *)(d + 0x24);
            *(f32 *)(p + 0x728) = *(f32 *)(d + 0x30);
            *(s16 *)(p + 0x6CC) = 1;
            *(f32 *)(p + 0x72C) = *(f32 *)(d + 0x2C);
            break;
        }
    }
}
