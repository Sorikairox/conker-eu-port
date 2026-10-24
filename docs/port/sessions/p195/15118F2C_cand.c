// mover_swing_step: swings a world mesh record (D_800DBEF4, 0xA0 bytes) about its yaw +0x4 like a door. +0x3C: low 10 bits
// = signed open angle, bits 10..15 = D_80089600 sound row, top byte = light slot + 1 (0 = none). +0x73 bits 0..1 = state
// (0 closed, 1 closing, 2 opening, 3 open; bit 2 picks the other default constants, which hold the same values), +0x7C = acceleration (0 -> 0.3), +0x80 = top speed
// (0 -> 0.075), +0x84 = angular velocity. Starting from rest plays the row's open / close sound; arriving bounces back
// (velocity * -accel) until it is below 1, then snaps, sets state 3 / 0 and plays the open / close stop sound. The new
// yaw is stored unless the netplay owner check says otherwise; on level 2 it sets func_1000E75C's level from the open
// fraction, elsewhere a light slot is dimmed by it (func_151885BC / func_151741D0, plus func_15174200 for slot 0 on level 1).
// func_15118EEC / func_15118F0C pass arg1 (0 / 3) through to func_1511FF00. Reached through the D_800893D8 table.
void func_1511FF00(u8 *arg0, s32 arg1);
f32 func_15048A70(f32 arg0, f32 arg1);
s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags);
s32 func_15022BB0(s32 arg0, s32 arg1);
void func_1000E75C(s32 arg0);
void func_151885BC(s32 arg0, f32 arg1);
void func_151741D0(s32 arg0, s32 arg1);
void func_15174200(s32 arg0, s32 arg1, s32 arg2);

void func_15118F2C(s32 arg0, s32 arg1) {
    u8 *rec = (u8 *) arg0;
    MoverSfx *row;
    s32 bits;
    s32 angle;
    s32 kind;
    s32 state;
    s32 sound = 0;
    s32 slot;
    s32 level;
    f32 open;
    f32 target;
    f32 yaw;
    f32 vel;
    f32 accel;
    f32 top;
    f32 diff;
    f32 frac;

    func_1511FF00(rec, arg1);
    bits = *(s32 *) (rec + 0x3C);
    angle = (bits << 22) >> 22;
    kind = (bits & 0xFC00) >> 10;
    row = &D_80089600[kind];
    open = angle;
    target = open;
    state = rec[0x73] & 3;
    yaw = *(f32 *) (rec + 4);
    vel = *(f32 *) (rec + 0x84);
    if (state == 0 || state == 1) {
        target = 0.0f;
    }
    if (state == 0 || state == 3) {
        vel = 0.0f;
        yaw = target;
    }
    if (yaw == target && vel == 0.0f) {
        *(f32 *) (rec + 0x84) = vel;
    } else {
        if (*(f32 *) (rec + 0x7C) == 0.0f) {
            *(f32 *) (rec + 0x7C) = 0.3f;
        }
        accel = *(f32 *) (rec + 0x7C);
        if (*(f32 *) (rec + 0x80) == 0.0f) {
            *(f32 *) (rec + 0x80) = 0.075f;
        }
        top = *(f32 *) (rec + 0x80);
        if (vel == 0.0f) {
            sound = (target == 0.0f) ? row->unk2 : row->move_sfx;
        }
        yaw += vel;
        diff = func_15048A70(yaw, target);
        if (fabsf(diff) < fabsf(vel)) {
            vel = -vel * accel;
            if (fabsf(vel) < 1.0f) {
                vel = 0.0f;
                if (target == 0.0f) {
                    sound = row->unk6;
                    state = 0;
                } else {
                    sound = row->stop_sfx;
                    state = 3;
                }
                yaw = target;
            } else {
                *(f32 *) (rec + 0x80) = top * 0.5f;
            }
        } else if (diff > 0.0f) {
            vel += top;
            if (vel > 5.0f) {
                vel = 5.0f;
            }
        } else {
            vel -= top;
            if (vel < -5.0f) {
                vel = -5.0f;
            }
        }
        if (fabsf(diff) > 30.0f && diff * vel < 0.0f) {
            vel = 0.0f;
        }
        if (yaw < -180.0f) {
            yaw += 360.0f;
        } else if (yaw >= 180.0f) {
            yaw -= 360.0f;
        }
        rec[0x73] = (rec[0x73] & ~3) | state;
        if (sound != 0) {
            func_151152A4(rec, sound, 0x5DC0, 0x9C4, 0x1194, 0);
        }
        *(f32 *) (rec + 0x84) = vel;
    }
    if (D_800BE9B4 == 0 && yaw == *(f32 *) (rec + 4)) {
        return;
    }
    if (D_800C35EA == 1 && func_15022BB0((rec - (u8 *) D_800DBEF4) / 0xA0, 0) != 0) {
        yaw = *(f32 *) (rec + 4);
    } else {
        *(f32 *) (rec + 4) = yaw;
    }
    slot = (u8) (*(s32 *) (rec + 0x3C) >> 24);
    if (D_800BE9F0 == 2) {
        func_1000E75C((s32) (255.0f - fabsf((yaw - open) * 255.0f / open)));
        return;
    }
    if (slot == 0) {
        return;
    }
    frac = 1.0f - fabsf((fabsf(yaw) - (f32) (angle < 0 ? -angle : angle)) / open);
    func_151885BC(slot - 1, frac);
    level = (s32) (frac * 255.0f);
    func_151741D0(level, slot - 1);
    if (D_800BE9F0 == 1 && slot - 1 == 0) {
        func_15174200(level, 0, 0xF8);
    }
}
