#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern f32 D_80088D30[4];
extern f32 D_80088D40[4];
extern f32 D_80088D50[4];
extern s32 D_80088D60[4];
extern s32 D_80088D70[4];
s32 func_1509BE40(s32, s32, s32, s32);
void func_150498A0(f32 *, f32, f32 *, f32, f32, f32);

// door_lights_update: for each of the 4 lights, flag 0x9000 of event 0x4039 + i (func_1509BE40) picks the target
// level (192 on, 255 off); the level eases toward it (func_150498A0: speed 4, rate 6, frame step obj+0x7B4) and is
// sent as byte parameter 0x12 of sound / effect 0x30E4 + i (func_1509BFB0). obj+0x84 gets 0x10, plus 0x80021010
// while any light is on (else those bits are cleared); bit 31 is set unless event 0x403D has flag 0x2000.
void func_150E1DE0(u8 *obj) {
    s32 any = 0;
    s32 i;

    *(u32 *) (obj + 0x84) |= 0x10;
    for (i = 0; i < 4; i++) {
        if (func_1509BE40(1, D_80088D60[i], 6, 0x9000) != 0) {
            D_80088D40[i] = 192.0f;
            *(u32 *) (obj + 0x84) |= 0x80021010;
            any = 1;
        } else {
            D_80088D40[i] = 255.0f;
        }
        func_150498A0(&D_80088D30[i], D_80088D40[i], &D_80088D50[i], 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
        func_1509BFB0(1, D_80088D70[i], 0x12, (u8) (u32) D_80088D30[i]);
    }
    if (!any) {
        *(u32 *) (obj + 0x84) &= 0x7FFDEFFF;
    }
    if (func_1509BE40(1, 0x403D, 6, 0x2000) != 0) {
        *(u32 *) (obj + 0x84) &= 0x7FFFFFFF;
    } else {
        *(u32 *) (obj + 0x84) |= 0x80000000;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F5F0/func_150E1DE0.s")
#endif
