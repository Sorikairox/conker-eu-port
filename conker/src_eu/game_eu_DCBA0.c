#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

/* was func_150AEEB0 */
void obj_trail_burst_spawn(struct127 *arg0, u8 arg1) {
    struct {
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s8 uD8;
        s8 uD9;
        u8 padDA[0xA];
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        u8 pad100[0x4];
        f32 u104;
        f32 u108;
        f32 u10C;
        s16 u110;
        s16 u112;
        s32 u114;
        u8 pad118[0x1];
        s8 u119;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s3;
    s32 var_s4;

    var_s3 = 0x1E;
    var_s4 = 1;
    if (arg0 != NULL) {
        sp.uBC = 0;
        sp.uC0 = 1;
        sp.uC4 = 0x160600;
        sp.uC8 = 3;
        sp.uCC = 0x10;
        sp.uD0 = 0x80;
        sp.uD4 = 0x20;
        sp.uD8 = 0;
        sp.uD9 = 9;
        sp.u114 = 1;
        sp.u112 = 1;
        sp.uFD = 8;
        sp.uFE = 0xFF - (((u32) arg0->unk184 >> 5) << 6);
        sp.uFC = 0x28;
        sp.uFF = 0xFF;
loop_2:
        temp_s0 = random_int() & 0xFF;
        temp_v1 = -0x28 - (random_int() % 21U);
        temp_f28 = angle_byte_cos(temp_v1 & 0xFF);
        temp_f26 = angle_byte_cos(((temp_v1 & 0xFF) - 0x40) & 0xFF);
        temp_f20 = angle_byte_cos(temp_s0 & 0xFF);
        temp_f22 = angle_byte_cos((temp_s0 - 0x40) & 0xFF);
        temp_f24 = (random_float() * 5.0f) + 10.0f;
        sp.u104 = arg0->x_position + (100.0f * temp_f22);
        sp.u108 = (random_float() * 15.0f) + arg0->y_position;
        sp.u10C = arg0->z_position + (100.0f * temp_f20);
        sp.u119 = (random_int() % 7U) + 3;
        sp.u110 = (random_int() % 26U) + 0x23;
        sp.uE4 = (random_float() * 6.0f) + 2.0f;
        temp_f2 = temp_f24 * temp_f28;
        sp.uF4 = random_float() + 1.0f;
        sp.uE8 = temp_f2 * temp_f22;
        sp.uEC = -temp_f24 * temp_f26;
        sp.uF0 = temp_f2 * temp_f20;
        var_s3 -= 1;
        if (trail_spawn(&sp.u104, &sp.uE4, 0, 1, 3, 0, 0, 0, 0, 0, 0, &sp.uBC, 0, (s32) arg1, 0) == 0) {
            var_s4 = 0;
        }
        if ((var_s4 != 0) && (var_s3 != 0)) {
            goto loop_2;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCBA0/obj_trail_burst_spawn.s")
#endif
/* was func_150AF6A0 */
s32 trail_alpha_from_life(struct_eu_sprite *arg0) {
    struct_eu_sprite_sub *sub = arg0->unk98;
    s32 v = arg0->unk1C * 32;

    if (v >= 0x100) {
        v = 0xFF;
    }
    sub->unk1B = v;
    if (sub->unk1B < 0) {
        return 0;
    }
    return 1;
}
