#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_8009FC40;
void func_150B0F40(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5) {
    f32 r;
    f32 k;
    f32 s;
    f32 m;

    *arg5 = *(f32 *)(arg0 + 0x40) * D_8009FC40 - 128.0f;
    r = func_150ADA68() * 248.0f;
    s = func_150ADA68() + -0.5f;
    if (r < 122.0f) {
        arg4[0] = arg2[0] * -31.5f + arg3[0] * s * 122.0f;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * -31.5f + arg3[1] * s * 122.0f;
    } else {
        s32 step; // fakematch: permuter temp, schedules `r -= 122.0f` after the 63/61 loads

        m = 61.0f;
        r -= 122.0f;
        step = 0x40;
        k = m;
        if (r < 63.0f) {
            k = -m;
            *arg5 += step;
        } else {
            *arg5 -= 0x40;
        }
        arg4[0] = arg2[0] * 63.0f * s + arg3[0] * k;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * 63.0f * s + arg3[1] * k;
    }
    arg4[0] += *(f32 *)(arg0 + 0x14);
    arg4[1] += *(f32 *)(arg1 + 0x118);
    arg4[2] += *(f32 *)(arg0 + 0x1C);
}

void func_150B1114(u8 *arg0) {
    func_150B1138(arg0, 0xFF, 1);
}

void func_150B1138(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x58, -1, 0, 0x43, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_150B11C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

#ifdef NON_MATCHING
s32 func_1515C668(u8 *arg0, u8 **arg1);
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
void func_15143794(s16, s16, f32, void *);
s32 func_150ADA20(void);
f32 func_150ADA68(void);

// wake_spray_update: update handler of the effect func_150B1138 creates (+0x28 = the object, +0x2C its id, +0x30
// the spray accumulator). Ends the effect (+0xE = -1) when the object is gone or reused. While the owner rides in
// mode 2 (+0x31C +0x4F) faster than 26 (max of the object's +0x3C and owner +0x44 x 1.35), the accumulator grows
// by (1.259 + rand x 1.079) x D_800BE9A4 per frame (Rare indexes {1, 1.259} / {0, 1.079} by the flag, always 1
// here) and every whole unit spawns one spray particle (kind 5) at a point beside the object (func_150B0F40) thrown up / out (func_15143794) against the owner's ground velocity
// (func_1515C668, else zero) x 0.925.
void func_150B1200(u8 *fx) {
    u8 *obj = *(u8 **) (fx + 0x28);
    u8 *owner;
    u8 *ground;
    s32 fast;
    f32 speed;
    f32 boost;
    f32 r;
    f32 r2;
    f32 r3;
    u32 n1;
    u32 n2;
    f32 side[2];
    f32 fwd[2];
    f32 pos[3];
    f32 vel[3];
    s16 yaw;

    if (*(s32 *) obj == 0 || fx[0x2C] != obj[0x3B]) {
        *(s16 *) (fx + 0xE) = -1;
        return;
    }
    owner = (u8 *) &D_800CC2D0[obj[0x124]];
    fast = FALSE;
    if ((*(u8 **) (owner + 0x31C))[0x4F] == 2) {
        boost = *(f32 *) (owner + 0x44) * 1.35f;
        speed = *(f32 *) (obj + 0x3C);
        if (speed < boost) {
            speed = boost;
        }
        if (speed > 26.0f) {
            fast = TRUE;
        }
    }
    if (!fast) {
        return;
    }
    r = func_150ADA68();
    *(f32 *) (fx + 0x30) += (1.2590001f + r * 1.079f) * D_800BE9A4;
    if (!(*(f32 *) (fx + 0x30) > 1.0f)) {
        return;
    }
    if (func_1515C668(obj, &ground) == 0) {
        ground = D_800A5860;
    }
    func_1514373C(*(f32 *) (obj + 0x40) * 0.017453292f, 1.0f, side, &side[1]);
    fwd[1] = -side[0];
    fwd[0] = side[1];
    do {
        func_150B0F40(obj, owner, side, fwd, pos, &yaw);
        n1 = func_150ADA20();
        r = func_150ADA68() * 3.77f;
        func_15143794(yaw, n1 % 26 - 0x29, r + 4.06f, vel);
        vel[0] -= ((f32 *) ground)[0] * 0.9250001f;
        vel[2] -= ((f32 *) ground)[2] * 0.9250001f;
        r = func_150ADA68();
        n1 = func_150ADA20();
        n2 = func_150ADA20();
        r2 = func_150ADA68();
        r3 = func_150ADA68();
        func_151D9014(pos, vel, 5, r * 0.178f + -0.44200003f, n1 % 21 + 0x14, n2 % 101 + 0x9B, r2 * 50.0f + 80.0f,
                      r3 < 0.044000003f, 1.4f, 1.4f, 1, 0, 1, 0, fx[0xC], fx[1]);
        *(f32 *) (fx + 0x30) -= 1.0f;
    } while (*(f32 *) (fx + 0x30) > 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DE750/func_150B1200.s")
#endif
