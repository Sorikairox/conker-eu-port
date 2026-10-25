#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_1510F800(s32);
s32 func_1510FE58(s32, s32, s32, s32 *);
void func_1518CF74(s32);
s32 func_15171770(s32, s32, f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, s32);
void func_15171E60(f32, f32, f32, f32, s32, f32, s32, s32, s32, s32);
void func_15170F24(s32, s32, s32, s32, f32, s32, s32);
extern f32 D_800A7090; /* 0.4: wobble amplitude */
extern f32 D_800A7094; /* 57.29578: radians -> degrees */
extern f32 D_800A7098; /* 57.29578 */
extern f32 D_800A709C; /* -0.4 */
extern f32 D_800A70A0; /* 0.7 */
extern f32 D_800A70A4; /* -0.7 */

// debris_update: moves a falling debris object (pos +0x90, velocity +0xA8, spin angles +0x9C..+0xA4 with rates
// +0xB4..+0xBC, gravity 0.5 per tick, ticks D_800BE9E4). Flag +0xE8 bit 1 wobbles the scale +0xC4 (phase +0xE7),
// bit 2 turns the object along its velocity (+0xA0 yaw, +0x9C pitch, degrees). When it falls below the ground
// (func_1510FE58 + radius +0xE9) it lands; by kind +0xEB: 1 = splash + two ripples, 4 = splash, 3 = splash + dust
// burst (all three free the object), 6 = stops and rests 60 ticks, 8 = freed; other kinds bounce (velocity scaled by
// +0xD8, vertical by +0xDC, a ripple; stop under 2.0; kind 2 may get a random spin, kind 5 a dust burst; spin rates
// scaled by +0xE0). The timer +0xCC then counts down; at 0 the object fades (+0xE5 by 4 per tick, +0xEC = 2) and is
// freed when the fade ends.
void func_1516A1E0(u8 *obj) {
    f32 dt;
    f32 ground;
    s32 left;

    dt = D_800BE9E4;
    *(f32 *) (obj + 0x90) += *(f32 *) (obj + 0xA8) * dt;
    *(f32 *) (obj + 0x98) += *(f32 *) (obj + 0xB0) * dt;
    *(f32 *) (obj + 0x9C) += *(f32 *) (obj + 0xB4) * dt;
    *(f32 *) (obj + 0xA0) += *(f32 *) (obj + 0xB8) * dt;
    *(f32 *) (obj + 0xA4) += *(f32 *) (obj + 0xBC) * dt;
    *(f32 *) (obj + 0xAC) += -0.5f * dt;
    *(f32 *) (obj + 0x94) += *(f32 *) (obj + 0xAC) * dt;

    if (obj[0xE8] & 1) {
        obj[0xE7] += D_800BE9E4 * 8;
        *(f32 *) (obj + 0xC4) = (func_15048A40(obj[0xE7]) * D_800A7090 + 1.0f) * *(f32 *) (obj + 0xD4);
    }
    if (obj[0xE8] & 2) {
        *(f32 *) (obj + 0xA0) = func_150484A0(*(f32 *) (obj + 0xA8), *(f32 *) (obj + 0xB0)) * D_800A7094;
        *(f32 *) (obj + 0x9C) =
            func_150484A0(-*(f32 *) (obj + 0xAC), sqrtf(*(f32 *) (obj + 0xA8) * *(f32 *) (obj + 0xA8) +
                                                        *(f32 *) (obj + 0xB0) * *(f32 *) (obj + 0xB0))) *
            D_800A7098;
    }

    func_1510F800(0);
    ground = func_1510FE58(*(f32 *) (obj + 0x90), *(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98), NULL) + obj[0xE9];
    if (*(f32 *) (obj + 0x94) < ground && *(f32 *) (obj + 0xAC) < 0.0f) {
        *(f32 *) (obj + 0x94) = ground;
        switch (obj[0xEB]) {
            case 1:
                func_15171770(4, 0xB, *(f32 *) (obj + 0x90), *(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98),
                              *(f32 *) (obj + 0xAC) * *(f32 *) (obj + 0xDC), 0.5f, 1.0f, 60.0f, 2, 0xFF, D_800A709C,
                              obj[0xC], obj[1]);
                func_15171E60(*(f32 *) (obj + 0x90), (*(f32 *) (obj + 0x94) - obj[0xE9]) + 30.0f,
                              *(f32 *) (obj + 0x98), 50.0f, 0x28, 0.0030517578f, 0, 0x14, obj[0xC], obj[1]);
                func_15171E60(*(f32 *) (obj + 0x90), (*(f32 *) (obj + 0x94) - obj[0xE9]) + 15.0f,
                              *(f32 *) (obj + 0x98), 30.0f, 0x28, 0.0030517578f, 0, 0xA, obj[0xC], obj[1]);
                func_1518CF74(obj[0xEA]);
                func_1516972C((struct102 *) obj);
                return;
            case 4:
                func_15171770(3, 0xB, *(f32 *) (obj + 0x90), *(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98),
                              *(f32 *) (obj + 0xAC) * *(f32 *) (obj + 0xDC), 0.5f, D_800A70A0, 40.0f, 2, 0x3C, -0.5f,
                              obj[0xC], obj[1]);
                func_1518CF74(obj[0xEA]);
                func_1516972C((struct102 *) obj);
                return;
            case 3:
                func_15171770(2, 0xCB, *(f32 *) (obj + 0x90), *(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98), 6.0f,
                              0.5f, 1.0f, 60.0f, 5, 0x3C, D_800A70A4, obj[0xC], obj[1]);
                func_15170F24(*(f32 *) (obj + 0x90), *(f32 *) (obj + 0x94) + 10.0f, *(f32 *) (obj + 0x98), 4,
                              *(f32 *) (obj + 0xAC) * 200.0f, obj[0xC], obj[1]);
                func_1518CF74(obj[0xEA]);
                func_1516972C((struct102 *) obj);
                return;
            case 6:
                *(f32 *) (obj + 0xB0) = 0.0f;
                *(f32 *) (obj + 0xAC) = 0.0f;
                *(f32 *) (obj + 0xA8) = 0.0f;
                *(f32 *) (obj + 0xBC) = 0.0f;
                *(f32 *) (obj + 0xB8) = 0.0f;
                *(f32 *) (obj + 0xB4) = 0.0f;
                *(f32 *) (obj + 0xDC) = 0.0f;
                obj[0xEB] = 0;
                *(s32 *) (obj + 0xCC) = 60;
                return;
            case 8:
                func_1518CF74(obj[0xEA]);
                func_1516972C((struct102 *) obj);
                return;
            default:
                *(f32 *) (obj + 0xA8) *= *(f32 *) (obj + 0xD8);
                *(f32 *) (obj + 0xB0) *= *(f32 *) (obj + 0xD8);
                *(f32 *) (obj + 0xAC) *= *(f32 *) (obj + 0xDC);
                if (*(f32 *) (obj + 0xAC) < 2.0f) {
                    *(f32 *) (obj + 0xA8) = 0.0f;
                    *(f32 *) (obj + 0xAC) = 0.0f;
                    *(f32 *) (obj + 0xB0) = 0.0f;
                    *(f32 *) (obj + 0xB4) = 0.0f;
                    *(f32 *) (obj + 0xB8) = 0.0f;
                    *(f32 *) (obj + 0xBC) = 0.0f;
                } else {
                    func_15171E60(*(f32 *) (obj + 0x90), (*(f32 *) (obj + 0x94) - obj[0xE9]) + 15.0f,
                                  *(f32 *) (obj + 0x98), 20.0f, 0x32, 0.00045776367f, 0, 4, obj[0xC], obj[1]);
                    if (obj[0xEB] == 2) {
                        if (func_150ADA20() & 0x8000) {
                            *(f32 *) (obj + 0xB4) = (func_150ADA20() >> 16) * 0.00015258789f + 40.0f;
                        }
                    } else if (obj[0xEB] == 5) {
                        func_15170F24(*(f32 *) (obj + 0x90), *(f32 *) (obj + 0x94) + 10.0f, *(f32 *) (obj + 0x98), 4,
                                      *(f32 *) (obj + 0xAC) * 200.0f, obj[0xC], obj[1]);
                    }
                }
                *(f32 *) (obj + 0xB4) *= *(f32 *) (obj + 0xE0);
                *(f32 *) (obj + 0xBC) *= *(f32 *) (obj + 0xE0);
                break;
        }
    }

    if (*(s32 *) (obj + 0xCC) != 0) {
        left = *(s32 *) (obj + 0xCC) - D_800BE9E4;
        if (left > 0) {
            *(s32 *) (obj + 0xCC) = left;
            return;
        }
        obj[0xEC] = 2;
        left = obj[0xE5] - D_800BE9E4 * 4;
        if (left > 0) {
            obj[0xE5] = left;
            *(s32 *) (obj + 0xCC) = 1;
            return;
        }
        func_1518CF74(obj[0xEA]);
        func_1516972C((struct102 *) obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1979F0/func_1516A1E0.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800A70A8;
extern s32 D_8008CE7C;

void func_1516A964(u8 *arg0) {
    struct {
        s32 u2C;
        s16 u30;
        s16 u32;
        s16 u34;
        s16 u36;
        s16 u38;
        s16 u3A;
        s16 u3C;
        s8 u3E;
        u8 pad3F[0x1];
        s8 u40;
        u8 u41;
        u8 pad42[0x6];
        s32 u48;
    } sp;
    u8 temp_v0_2;
    s32 var_v1;
    s32 var_t0;
    s32 temp_v0;
    s16 temp_v1;

    var_v1 = (*(s32 *)((u8 *)arg0 + 0x14));
    var_t0 = (*(s16 *)((u8 *)arg0 + 0x22)) + (*(s16 *)((u8 *)arg0 + 0x2A));
    if (var_v1 >= var_t0) {
        sp.u48 = var_t0;
        func_1510F800(0);
        temp_v0 = func_1510FE58((*(s16 *)((u8 *)arg0 + 0x20)), (*(s16 *)((u8 *)arg0 + 0x22)), (*(s16 *)((u8 *)arg0 + 0x24)), 0);
        var_t0 = sp.u48;
        (*(s32 *)((u8 *)arg0 + 0x14)) = temp_v0;
        var_v1 = temp_v0;
    }
    if (var_v1 >= var_t0) {
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0;
        if ((var_t0 - var_v1) < 0x32) {
            sp.u30 = 0;
            sp.u32 = 0x100;
            sp.u2C = D_8008CE7C;
            sp.u34 = (*(s16 *)((u8 *)arg0 + 0x20));
            sp.u36 = (*(s32 *)((u8 *)arg0 + 0x14)) + 0xA;
            sp.u38 = (*(s16 *)((u8 *)arg0 + 0x24));
            temp_v0_2 = (*(u8 *)((u8 *)arg0 + 0x3B));
            sp.u3E = 0;
            sp.u40 = 3;
            temp_v1 = ((s32) (temp_v0_2 << 0xC) / 5100) + 0xCC;
            sp.u3A = temp_v1;
            sp.u3C = temp_v1;
            sp.u41 = temp_v0_2;
            func_15167AD8(&sp.u2C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
        }
    } else {
        (*(s16 *)((u8 *)arg0 + 0x26)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x26)) * D_800A70A8);
        (*(s16 *)((u8 *)arg0 + 0x28)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x28)) * D_800A70A8);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1979F0/func_1516A964.s")
#endif
s32 func_151722BC(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_1516AAA8(u8 *arg0) {
    s32 pad; // fakematch: frame slot
    u32 sp48;
    s32 sp44;

    if ((*(s16 *)((u8 *)arg0 + 0x14)) >= 0x300) {
        sp48 = func_150ADA20() % 3U;
        sp44 = (s32) (*(u8 *)((u8 *)arg0 + 0x25));
        func_151722BC((f32) (*(s16 *)((u8 *)arg0 + 0x18)), (f32) ((*(s16 *)((u8 *)arg0 + 0x1A)) - 0xA), (f32) (*(s16 *)((u8 *)arg0 + 0x1C)), 0x64, 0, sp48 + 0x20, (f32) (func_150ADA20() % 360U), 0, ((s32) (sp44 * 0x19) / 255) + 0x19, 0, 0x100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    }
}

s32 func_1516ABB8(u8 *arg0) {
    s32 a;
    s32 h;

    a = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (a != 0xFF) {
            a += D_800BE9E4 * 16;
            if (a >= 0x100) {
                a = 0xFF;
            }
            arg0[0x1F] = a;
        }
    } else if (a != 0) {
        a -= D_800BE9E4 * 4;
        if (a < 0) {
            a = 0;
        }
        arg0[0x1F] = a;
    }
    if (arg0[0x24] == 0 && a == 0) {
        return 1;
    }
    *(s16 *)(arg0 + 0x18) -= 300;
    func_1516FDD4(arg0);
    h = func_1510FE58(*(s16 *)(arg0 + 0xE), *(s16 *)(arg0 + 0x10), *(s16 *)(arg0 + 0x12), 0) + 10;
    arg0[0x2C] = h >> 8;
    arg0[0x2D] = h & 0xFF;
    if (*(s16 *)(arg0 + 0x10) < h) {
        *(s16 *)(arg0 + 0x10) = h;
        *(s16 *)(arg0 + 0x18) = *(s16 *)(arg0 + 0x18) * -0.5f;
        func_1516FEBC(arg0, 0xE6);
    }
    return 0;
}
