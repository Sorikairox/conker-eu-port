#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P249: readable C for func_150BE050 (game_eu_EB860, 205 insns). */
// rideable_vehicle_update: per-frame update of a rideable object (seen at the Colors start; id 0x23 uses the hit
// states 0xA / 0xB / 0xC and kind 1, other ids 1 / 2 / 3 and kind 3). Clears +0x2E8 / +0x2FC, eases the turret value
// +0x2E4 toward 0 (minus 1/8 per frame), clears +0x66 bit 0x20 in multiplayer. Rider = object slot +0x13C - 100
// (0 = none): its view (+0x318) marks the view's player bit in +0x2FC; when the rider's part (+0x31C) is in aim mode
// (+0x197), the heading +0x7A / +0x76 follows the part's yaw (+0x16C degrees, * 65536 / 360), +0x2E4 = its pitch
// (+0x170, above 180 minus 360) * 10, +0x2E8 = 1 and +0x66 bit 0x20 is set. It does not read a controller.
// Then the physics (func_15052590) and the hit states: +0x232 == state 2 -> func_15052F9C(o, 100, kind, 4, 0,
// state 3, 0, 0, 0, 0); +0x232 == state 1 -> unless func_15072208(o, 0) finds something, the first player slot
// (< 25) of D_800CC268 & ~D_800D18A0 that has a pad (+0x127 != 0xFF), +0x65 == 0, +0x13C == 0 and a part with
// +0x19B / +0x197 / +0x1AC == 0 and s16 +0x46 <= 0 becomes +0x124, gets func_1505327C(o, 44, 3.2, state 2, kind),
// part +0x24 = 500 and part +0x19E = 0.
void func_15052590(struct127 *);
f32 func_15052F9C(struct127 *, f32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_1505327C(struct127 *, f32, f32, s32, s32);
void func_150BE050(u8 *o) {
    s32 state1, state2, state3, kind;
    s32 v, i, mask;
    u8 *slot, *view, *part;
    f32 pitch;

    state1 = 1;
    if (o[4] == 0x23) {
        state1 = 0xA;
        state2 = 0xB;
        state3 = 0xC;
        kind = 1;
    } else {
        state2 = 2;
        state3 = 3;
        kind = 3;
    }
    v = *(s32 *) (o + 0x2E4);
    *(s32 *) (o + 0x2E8) = 0;
    o[0x2FC] = 0;
    *(s32 *) (o + 0x2E4) = v - (v >> 3);
    if (D_800BE616 != 0) {
        o[0x66] &= ~0x20;
    }
    if (o[0x13C] != 0) {
        slot = (u8 *) &D_800CC2D0[o[0x13C] - 100];
        view = *(u8 **) (slot + 0x318);
        if (view != NULL) {
            o[0x2FC] = 1 << view[0x23D];
        }
        part = *(u8 **) (slot + 0x31C);
        if (part != NULL && part[0x197] != 0) {
            v = (s32) (*(f32 *) (part + 0x16C) * 182.04445f);
            *(s16 *) (o + 0x7A) = v;
            *(s16 *) (o + 0x76) = v;
            pitch = *(f32 *) (*(u8 **) (slot + 0x31C) + 0x170);
            if (pitch > 180.0f) {
                pitch -= 360.0f;
            }
            *(s32 *) (o + 0x2E8) = 1;
            o[0x66] |= 0x20;
            *(s32 *) (o + 0x2E4) = (s32) (pitch * 10.0f);
        }
    }
    func_15052590((struct127 *) o);
    if (o[0x232] == state2) {
        func_15052F9C((struct127 *) o, 100.0f, kind, 4, 0, state3, 0, 0, 0, 0);
        return;
    }
    if (o[0x232] != state1 || !(~D_800D18A0 & D_800CC268)) {
        return;
    }
    if (func_15072208((struct127 *) o, 0) != NULL) {
        return;
    }
    mask = ~D_800D18A0 & D_800CC268;
    for (i = 0; i < 0x19; i++) {
        if (!(mask & (1 << i))) {
            continue;
        }
        slot = (u8 *) &D_800CC2D0[i];
        part = *(u8 **) (slot + 0x31C);
        if (slot[0x127] != 0xFF && slot[0x65] == 0 && part[0x19B] == 0 && part[0x197] == 0 && slot[0x13C] == 0
            && part[0x1AC] == 0 && *(s16 *) (part + 0x46) <= 0) {
            o[0x124] = i;
            func_1505327C((struct127 *) o, 44.0f, 3.2f, state2, kind);
            *(s16 *) (*(u8 **) (slot + 0x31C) + 0x24) = 500;
            *(s16 *) (*(u8 **) (slot + 0x31C) + 0x19E) = 0;
            return;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EB860/func_150BE050.s")
#endif
