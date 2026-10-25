#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
void func_151254F4(struct108 *, s32);
void func_15123070(struct108 *arg0);
extern s32 D_80088BA0;

// player_flight_mode_update: player state handler (D_80089A10 table) for a flag-driven mode with two variants.
// Event flags: b = 0x2010/0xB7 -> 0xBC, c = 0x2000/0xBB, e = 0x2010/0xB7 -> 0xBB.
// Without 0x5071/0x1A: c set and b clear enters state +0x2C (func_15123934(+0x2C, 0, +0x134, 3); success sets +0x84
// bit 0x1000000, anim D_800CC335 - 1, +0x674 = 0); c and b set: func_151239CC(.., 2), then state 8 (success: anim,
// +0x84 &= ~4, +0x674 = 0, func_15123070), +0x5F0 |= 0x200, speeds +0x348 / +0x34C = 500, +0x374 = 800; c clear
// leaves the state (func_151239CC(.., 3): anim 0, +0x84 &= ~0x1000000, +0x3D4->0x198 = 0, +0x73C = 0, +0x674 = 0
// unless +0x6C8 is busy) and clears +0x5F0 bit 0x200.
// With 0x5071 but not 0x5072: +0x190 = 20 when the pad (+0x36C) has bit 4; without event 0x2000/0x93 +0x190 = 0 and
// stop. Otherwise copies event 0x2011/0xB7 -> 0x9C into 0x9000/0x17, takes t = (0x2011/0xB7 -> 0x9A - 300) / 900
// clamped to 0..1; b clear: speeds 200, +0x190 = 100; b set: +0x190 = 287 + 103 t, +0x374 = 750 + 224 t, speeds
// 231 t. Sets 0x9000/6 slots 1 and 0, clears +0x670 when e is not -1, D_80088BA0 = 0, and with +0x5F0 bit 4 copies
// object 0x10's +0x14..+0x1C into +0x3D0 (if its +0x65 is set); leaves the state as above (also clearing 0x200).
// With 0x5072: when func_151239CC(.., 3) succeeds or D_80088BA0 is 0: +0x84 |= 4, D_80088BA0 = 1, anim 0,
// +0x3D4->0x198 = 0, +0x73C = 0, +0x1B4 = 3, func_15124B18, +0x190 = 0, +0x674 = 0 unless +0x6C8 is busy.
// Finally (except the early returns) +0x190 = 0 while the pad has bit 4.
void func_150C8300(u8 *obj) {
    s32 b;
    s32 c;
    s32 e;
    s32 v;
    f32 t;
    u8 *other;

    b = func_1509BE40(0, func_1509BE40(0, 0x2010, 0xB7) | 0x2000, 0xBC);
    c = func_1509BE40(0, 0x2000, 0xBB);
    e = func_1509BE40(0, func_1509BE40(0, 0x2010, 0xB7) | 0x2000, 0xBB);
    if (func_1509BE40(0, 0x5071, 0x1A) == 0) {
        if (c != -1 && b == 0) {
            if (func_15123934((struct108 *) obj, *(s32 *) (obj + 0x2C), 0, *(s32 *) (obj + 0x134), 3) == 0) {
                return;
            }
            *(s32 *) (obj + 0x84) |= 0x1000000;
            func_151254F4((struct108 *) obj, D_800CC335 - 1);
            *(f32 *) (obj + 0x674) = 0.0f;
        } else if (c != -1) {
            func_151239CC((struct108 *) obj, 2);
            if (func_15123934((struct108 *) obj, 8, 0, *(s32 *) (obj + 0x134), 3) != 0) {
                func_151254F4((struct108 *) obj, D_800CC335 - 1);
                *(s32 *) (obj + 0x84) &= ~4;
                *(f32 *) (obj + 0x674) = 0.0f;
                func_15123070((struct108 *) obj);
            }
            *(s32 *) (obj + 0x5F0) |= 0x200;
            *(f32 *) (obj + 0x348) = 500.0f;
            *(f32 *) (obj + 0x34C) = 500.0f;
            *(f32 *) (obj + 0x374) = 800.0f;
        } else {
            if (func_151239CC((struct108 *) obj, 3) != 0) {
                func_151254F4((struct108 *) obj, 0);
                *(s32 *) (obj + 0x84) &= ~0x1000000;
                (*(u8 **) (obj + 0x3D4))[0x198] = 0;
                *(s16 *) (obj + 0x73C) = 0;
                if (*(s32 *) (obj + 0x6C8) == 0) {
                    *(f32 *) (obj + 0x674) = 0.0f;
                }
            }
            *(s32 *) (obj + 0x5F0) &= ~0x200;
        }
        return;
    }
    if (func_1509BE40(0, 0x5072, 0x1A) == 0) {
        if (**(u16 **) (obj + 0x36C) & 4) {
            *(f32 *) (obj + 0x190) = 20.0f;
        }
        if (func_1509BE40(0, 0x2000, 0x93) == 0) {
            *(f32 *) (obj + 0x190) = 0.0f;
            return;
        }
        v = func_1509BE40(1, func_1509BE40(0, 0x2011, 0xB7) | 0x2000, 0x9C, 0x2000);
        func_1509BFB0(1, 0x9000, 0x17, v);
        v = func_1509BE40(1, func_1509BE40(0, 0x2011, 0xB7) | 0x2000, 0x9A, 0x2000);
        t = ((f32) v - 300.0f) / 900.0f;
        if (t < 0.0f) {
            t = 0.0f;
        } else if (1.0f < t) {
            t = 1.0f;
        }
        if (b == 0) {
            *(f32 *) (obj + 0x34C) = 200.0f;
            *(f32 *) (obj + 0x348) = 200.0f;
            *(f32 *) (obj + 0x190) = 100.0f;
        } else {
            *(f32 *) (obj + 0x190) = 103.0f * t + 287.0f;
            *(f32 *) (obj + 0x374) = 224.0f * t + 750.0f;
            *(f32 *) (obj + 0x34C) = 231.0f * t;
            *(f32 *) (obj + 0x348) = 231.0f * t;
        }
        func_1509BFB0(2, 0x9000, 6, 1, 0x20000);
        func_1509BFB0(2, 0x9000, 6, 0, 4);
        if (e != -1) {
            *(f32 *) (obj + 0x670) = 0.0f;
        }
        D_80088BA0 = 0;
        if (*(s32 *) (obj + 0x5F0) & 4) {
            other = (u8 *) func_15083E90(0x10);
            if (other != NULL && (*(u8 **) (obj + 0x3D0))[0x65] != 0) {
                *(f32 *) (*(u8 **) (obj + 0x3D0) + 0x14) = *(f32 *) (other + 0x14);
                *(f32 *) (*(u8 **) (obj + 0x3D0) + 0x18) = *(f32 *) (other + 0x18);
                *(f32 *) (*(u8 **) (obj + 0x3D0) + 0x1C) = *(f32 *) (other + 0x1C);
            }
        }
        if (func_151239CC((struct108 *) obj, 3) != 0) {
            *(s32 *) (obj + 0x5F0) &= ~0x200;
            func_151254F4((struct108 *) obj, 0);
            *(s32 *) (obj + 0x84) &= ~0x1000000;
            (*(u8 **) (obj + 0x3D4))[0x198] = 0;
            *(s16 *) (obj + 0x73C) = 0;
            if (*(s32 *) (obj + 0x6C8) == 0) {
                *(f32 *) (obj + 0x674) = 0.0f;
            }
        }
    } else if (func_151239CC((struct108 *) obj, 3) != 0 || D_80088BA0 == 0) {
        *(s32 *) (obj + 0x84) |= 4;
        D_80088BA0 = 1;
        func_151254F4((struct108 *) obj, 0);
        (*(u8 **) (obj + 0x3D4))[0x198] = 0;
        *(s16 *) (obj + 0x73C) = 0;
        *(s16 *) (obj + 0x1B4) = 3;
        func_15124B18((struct108 *) obj);
        *(f32 *) (obj + 0x190) = 0.0f;
        if (*(s32 *) (obj + 0x6C8) == 0) {
            *(f32 *) (obj + 0x674) = 0.0f;
        }
    }
    if (**(u16 **) (obj + 0x36C) & 4) {
        *(f32 *) (obj + 0x190) = 0.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5B10/func_150C8300.s")
#endif
