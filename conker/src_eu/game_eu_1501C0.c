#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15048F90(struct17 *arg0, struct17 *arg1, struct17 *arg2);
f32 func_15048FC8(struct17 *arg0);
f32 func_15048A70(f32 arg0, f32 arg1);
void func_150498A0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_15123A54(u8 *);
void func_1512A390(u8 *);
void func_1512E6B0(u8 *);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1501C0/func_151229B0.s")

#ifdef NON_MATCHING
/* P41: camera mode 1 (follow). Unless 0xDC == 4: turn yaw 0x37C by the angle between eye->0x2C8 and eye->at
 * (func_15048A70 of the two headings) times the eased rate 0x8DC (toward 0x8D4: 0 when 0x298 is clear, 0.75 for
 * flag 0x100000 of 0x84 or 180 < 0x390 < 270, else 0.5); 0x39C = 0x37C in radians. Then the eye orbit
 * func_15123A54, func_1512E6B0 and func_1512A390. */
void func_15122EF0(u8 *arg0) {
    struct17 sp44;
    struct17 sp38;
    f32 a;
    f32 b;
    f32 v;

    if (*(s32 *)(arg0 + 0xDC) != 4) {
        func_15048F90((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2C8), &sp44);
        func_15048F90((struct17 *)(arg0 + 0x2F8), (struct17 *)(arg0 + 0x2BC), &sp38);
        a = func_15048FC8(&sp44);
        b = func_15048FC8(&sp38);
        if (*(s16 *)(arg0 + 0x298) == 0) {
            v = 0.0f;
        } else if ((*(s32 *)(arg0 + 0x84) & 0x100000) ||
                   (180.0f < *(f32 *)(arg0 + 0x390) && *(f32 *)(arg0 + 0x390) < 270.0f)) {
            v = 0.75f;
        } else {
            v = 0.5f;
        }
        *(f32 *)(arg0 + 0x8D4) = v;
        func_150498A0((f32 *)(arg0 + 0x8DC), *(f32 *)(arg0 + 0x8D4), (f32 *)(arg0 + 0x8D8), 1.0f, 2.0f,
                      *(f32 *)(arg0 + 0x7B4));
        *(f32 *)(arg0 + 0x37C) = *(f32 *)(arg0 + 0x37C) + func_15048A70(a, b) * *(f32 *)(arg0 + 0x8DC);
        *(f32 *)(arg0 + 0x39C) = *(f32 *)(arg0 + 0x37C) * 0.017453292f;
    }
    func_15123A54(arg0);
    func_1512E6B0(arg0);
    func_1512A390(arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1501C0/func_15122EF0.s")
#endif