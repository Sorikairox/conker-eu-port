#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#ifdef NON_MATCHING
void obj_state_common_update(struct127 *);
f32 obj_carry_release(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
s32 obj_carry_pickup(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
void obj_hit_react_other_players(struct127 *);
extern u16 D_800BEB30[];
extern u8 *D_800CC6A4;
extern s32 D_800CC6A0;

/* rodata copies (NM link drops the asm rodata) */
/* D_800A0BDF[1..7]: state for (1 bump / 2 nudge) + 4 (rider type 0x21) + 2 (multiplayer) */
static const u8 D_800A0BE0_c[8] = { 0x06, 0x01, 0x21, 0x22, 0x11, 0x11, 0x00, 0x00 };
/* D_800A0BE8: per rider type (0: other, 1: type 0x21) [0] attack state, [2] / [4] its obj_carry_release arguments */
static const u8 D_800A0BE8_c[8] = { 0x10, 0x0C, 0x0A, 0x0D, 0x01, 0x19, 0x9C, 0xBE };
static const f32 D_800A0BF0_c[1] = { 182.04445f };  /* 0x43360B61, 0x10000 / 360 */
static const f32 D_800A0BF4_c[1] = { 0.005f };      /* 0x3BA3D70A */
static const f32 D_800A0BF8_c[1] = { 0.15f };       /* 0x3E19999A */

#define P(o, T) (*(T *) (obj + (o)))
// rider_ai_control: AI controller (table entry, `void (struct127 *)`) of a rider / vehicle object (type 0x21 =
// `twin`, else plain). Runs while +0x13C (pad index) is set or in multiplayer (D_800BE616). Reads the pad word
// D_800CC288 (multiplayer: ctl_decay_button_latches for human +0x31C[0x84] players, else D_800BEB30[player]; single player:
// D_800BEA68[+0x13C]): button 0x8000 with no +0x8A and no speed (+0x28) bumps, 0x6000 at rest nudges; either one
// starts the state D_800A0BDF[...] with a 180-frame cool-down (+0x89; state 0x22 counts +0x31C +0x1AA when +0x2E4
// is 0). Otherwise, once +0x89 is 0, it steers: multiplayer from the stick (D_800CC6A4: math_atan2_u16 heading +
// camera yaw, pad_stick_speed speed), single player follows player 0 (its speed * 1.75, yaw from +0x31C +0x4C).
// Type 0x21 riders wander (random yaw within +-5000, speed 20..80 when slow) and turn (state 0x10) when the target
// is behind; plain riders stop below speed 5 or turn (+0x223 == 1: states 3 / 4 / 5 by +0x3C vs 35). Then
// obj_state_common_update (unless a multiplayer +0x31C[0x120] player beyond D_8008FD8C), the attack (D_800A0BE8 state:
// obj_carry_release, or obj_carry_pickup on a 0x400 hit), a lean +0xC4 easing to the clamped yaw error * 0.005 and, for
// 0x21, the body sway +0x2E4 / +0x2E8; finally obj_hit_react_other_players for multiplayer human riders.
/* was func_150CEC50 */
void rider_ai_control(struct127 *self) {
    u8 *obj = (u8 *) self;
    u8 *pl;
    const u8 *atk;
    u16 prevYaw;
    u16 yaw;
    s32 twin;
    s32 act;
    s32 err;
    s32 sway;
    s32 target;
    u8 st;

    prevYaw = P(0x7A, u16);
    twin = (obj[4] == 0x21) ? 1 : 0;
    if (obj[0x13C] != 0 || D_800BE616 != 0) {
        act = 0;
        if (D_800BE616 != 0) {
            if ((*(u8 **) (obj + 0x31C))[0x84] != 0) {
                ctl_decay_button_latches(self);
            } else {
                D_800CC288 = D_800BEB30[D_800C3E78];
            }
        } else {
            D_800CC288 = ((u16 *) &D_800BEA68)[obj[0x13C]];
        }
        if ((D_800CC288 & 0x8000) && obj[0x8A] == 0 && P(0x28, f32) == 0.0f) {
            act = 1;
        }
        if ((D_800CC288 & 0x6000) && P(0x28, f32) == 0.0f) {
            if (twin) {
                if (obj[0x89] != 0xFF) {
                    act = 2;
                }
            } else if (obj[0x89] == 0) {
                act = 2;
            }
        }
        if (act != 0) {
            if (twin) {
                act = (u8) (act + 4);
            }
            if (D_800BE616 != 0) {
                act = (u8) (act + 2);
            }
            obj[0x89] = 0xB4;
            st = D_800A0BE0_c[act - 1];
            P(0x218, s32) = 0;
            obj[0x232] = st;
            if (st == 0x22 && P(0x2E4, s32) == 0) {
                (*(s16 *) (*(u8 **) (obj + 0x31C) + 0x1AA))++;
            }
        }

        obj[0x124] = 0;
        if (obj[0x89] == 0 && !(D_800BE616 != 0 && (*(u8 **) (obj + 0x31C))[0x84] != 0)) {
            if (D_800BE616 != 0) {
                D_800CC6A0 = (s32) (*(f32 *) ((u8 *) D_800DBFF0 + D_800C3E78 * 0x9A0 + 0x37C) * D_800A0BF0_c[0]);
                yaw = math_atan2_u16((s8) D_800CC6A4[2], (s8) D_800CC6A4[3], 0) + D_800CC6A0;
                P(0x44, f32) = pad_stick_speed((struct49 *) D_800CC6A4);
            } else {
                pl = (u8 *) D_800CC2D0 + obj[0x124] * 0x32C;
                P(0x44, f32) = *(f32 *) (pl + 0x44) * 1.75f;
                yaw = *(u16 *) (*(u8 **) (pl + 0x31C) + 0x4C);
            }
            if (obj[0x223] == 0xD) {
                P(0x44, f32) = 0.0f;
            }
            if (twin) {
                if (P(0x44, f32) < 5.0f) {
                    yaw = random_int();
                    P(0x44, f32) = (f32) ((u32) random_int() % 60) + 20.0f;
                }
                target = ((u32) random_int() % 10000) + yaw - 5000;
                P(0x78, s16) = target;
                P(0x44, f32) = P(0x44, f32) * 0.5f + 22.0f;
                if ((u8) (((s32) (P(0x76, u16) - target) >> 8) - 0x50) < 0x60) {
                    /* the target is behind: turn round */
                    P(0x218, s32) = 0;
                    obj[0x232] = 0x10;
                }
            } else if (P(0x44, f32) < 5.0f) {
                P(0x44, f32) = 0.0f;
                if (obj[0x232] != 5) {
                    P(0x78, u16) = P(0x76, u16);
                }
            } else {
                P(0x78, u16) = yaw;
                if (obj[0x223] == 1) {
                    st = (P(0x3C, f32) < 35.0f) ? 4 : 3;
                    obj[0x1E6] = st;
                    obj[0x1E5] = st;
                    if ((u8) (((s32) (P(0x76, u16) - P(0x78, u16)) >> 8) - 0x50) < 0x60) {
                        obj[0x232] = (35.0f < P(0x3C, f32)) ? 4 : 5;
                    } else {
                        obj[0x232] = 3;
                    }
                    P(0x218, s32) = 0;
                }
            }
        }
    }

    if (D_800BE616 == 0 || D_800C3E78 >= D_8008FD8C || (*(u8 **) (obj + 0x31C))[0x120] == 0) {
        obj_state_common_update(self);
    }
    pl = *(u8 **) ((u8 *) D_800CC2D0 + 0x31C);
    if (pl[0x27] != 0 && (obj[0x232] != D_800A0BE8_c[twin] || obj[0x104] != 0)) {
        /* the attack was interrupted: player 0 drops its hold */
        pl[0x27] = 0;
        ((u8 *) D_800CC2D0)[0x89] = 0;
        ((u8 *) D_800CC2D0)[0x83] = 0;
        ((u8 *) D_800CC2D0)[0x125] = 0;
        obj[0x232] = 0x11;
    }
    atk = &D_800A0BE8_c[twin];
    if (D_800BE616 == 0) {
        if (obj[0x232] == atk[0]) {
            obj_carry_release(self, 156.0f, atk[4], 4, 0, atk[2], 0xFF, 0, 0, 0);
        } else if ((D_800CC268 & 1) && ((u8 *) D_800CC2D0 + obj[0x124] * 0x32C)[0x65] == 0
                   && (P(0x25C, s32) & 0x400)) {
            obj[0x124] = 0;
            obj_carry_pickup(self, 50.0f, 3.0f, atk[0], atk[4]);
        }
    }

    /* lean into the turn */
    err = 0;
    if ((twin && 5.0f < P(0x3C, f32)) || (!twin && P(0x84, u16) == 0xA)) {
        err = (s16) (P(0x76, u16) - P(0x78, u16));
        if (err > 0x3000) {
            err = 0x3000;
        }
        if (err < -0x3000) {
            err = -0x3000;
        }
        if (twin && obj[0x13C] == 0) {
            err = (s16) (err >> 1);
        }
    }
    P(0xC4, f32) = P(0xC4, f32) + ((f32) err * D_800A0BF4_c[0] - P(0xC4, f32)) * D_800A0BF8_c[0];
    if (twin) {
        sway = (s16) ((prevYaw - P(0x7A, u16)) << 2);
        P(0x2E4, s32) = P(0x2E4, s32) + (sway - (s16) P(0x2E4, s32)) / 8;
        P(0x2E8, s32) = P(0x2E8, s32) + (-err - P(0x2E8, s32)) / 8;
    }
    if (D_800BE616 != 0 && D_800CC268 != 0 && *(u8 **) (obj + 0x31C) != NULL && (*(u8 **) (obj + 0x31C))[0x1AC] != 0) {
        obj_hit_react_other_players(self);
    }
}
#undef P
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FC460/rider_ai_control.s")
#endif
