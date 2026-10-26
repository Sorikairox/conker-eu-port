#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
void camera_set_followed_obj(struct108 *, s32);
extern s32 D_80088AB0;

// player_carry_state_update: player state handler. Without input flag 0x503C/0x1A it (once camera_push_mode allows)
// switches to mode 3 (+0x1B4, flag 0x20000 set / 4 cleared, camera_apply_zoom_level, +0x23C = 1) and sets the speeds
// (+0x374 = 650, +0x348 / +0x34C = 450). Otherwise it clears 0x4000, leaves for mode 2 on track 1 (camera_pop_mode),
// maps the pressed buttons 0x4024..0x4027 to an animation id in D_80088AB0 (0x9003 / 0x9009 / 0x900A / 0x900B; 999
// = none) and plays it, sets 0x2000 / 0x3B for 0x400C..0x400E or 0x4014, and sets 0x9000 / 0x10 to 0x55 while
// 0x4000 is held. Finally flag 0x100 of +0x5F0 follows "0x200A / 0xB7 and 0xBC set and 0xBB not -1": while it holds
// the player (camera_push_mode kind 3) is seated on the object's last slot (camera_set_followed_obj) with speeds as above and
// +0x190 = 0 / 135 by the animation flag 4; else on leaving (camera_pop_mode 3) it returns to slot +0x23D.
void func_150B6CC0(u8 *p) {
    s32 i;
    s32 on;
    s32 v;

    if (func_1509BE40(0, 0x503C, 0x1A) == 0) {
        if (camera_push_mode((struct108 *) p, *(s32 *) (p + 0x2C), 0, 0, 0) != 0) {
            *(s16 *) (p + 0x1B4) = 3;
            *(s32 *) (p + 0x84) |= 0x20000;
            *(s32 *) (p + 0x84) &= ~4;
            camera_apply_zoom_level((struct108 *) p);
            p[0x23C] = 1;
        }
        *(f32 *) (p + 0x374) = 650.0f; /* D_800A00C0 */
        *(f32 *) (p + 0x348) = 450.0f;
        *(f32 *) (p + 0x34C) = 450.0f;
    } else {
        func_1509BFB0(0, 0x4000, 0);
        if (*(s32 *) (p + 0x2C) == 1 && camera_pop_mode((struct108 *) p, 0) != 0) {
            *(s16 *) (p + 0x1B4) = 2;
            camera_apply_zoom_level((struct108 *) p);
        }
        if (func_1509BE40(1, 0x4024, 6, 0x2000) != 0) {
            D_80088AB0 = 0x9003;
        } else if (func_1509BE40(1, 0x4025, 6, 0x2000) != 0) {
            D_80088AB0 = 0x9009;
        } else if (func_1509BE40(1, 0x4026, 6, 0x2000) != 0) {
            D_80088AB0 = 0x900A;
        } else if (func_1509BE40(1, 0x4027, 6, 0x2000) != 0) {
            D_80088AB0 = 0x900B;
        }
        if (D_80088AB0 != 999) {
            func_1509BFB0(5, 0x4000, 4, 2, 0, D_80088AB0 & 0xFFF, 0, 0);
        }
        for (i = 0; i < 3; i++) {
            if (func_1509BE40(1, 0x400C + i, 6, 0x2000) != 0 || func_1509BE40(1, 0x4014, 6, 0x2000) != 0) {
                func_1509BFB0(1, 0x2000, 0x3B, 2);
            }
        }
        if (func_1509BE40(1, 0x4000, 6, 0x2000) != 0) {
            func_1509BFB0(2, 0x9000, 6, 1, 0x80000);
            func_1509BFB0(1, 0x9000, 0x10, 0x55);
        } else {
            func_1509BFB0(2, 0x9000, 6, 0, 0x80000);
            func_1509BFB0(1, 0x9000, 0x10, 0);
        }
    }
    on = func_1509BE40(0, func_1509BE40(0, 0x200A, 0xB7) | 0x2000, 0xBC);
    v = func_1509BE40(0, 0x2000, 0xBB);
    if (on != 0 && v != -1) {
        *(s32 *) (p + 0x5F0) |= 0x100;
    } else {
        *(s32 *) (p + 0x5F0) &= ~0x100;
    }
    if (on != 0 && v != -1) {
        if (camera_push_mode((struct108 *) p, *(s32 *) (p + 0x2C), 0, 0, 3) != 0) {
            *(s32 *) (p + 0x84) |= 0x100002;
            *(f32 *) (p + 0x674) = 0.0f;
            camera_set_followed_obj((struct108 *) p, (*(u8 **) (p + 0x3D0))[0x65] - 1);
            *(s32 *) (p + 0x134) = 0;
        }
        *(f32 *) (p + 0x34C) = 450.0f;
        *(f32 *) (p + 0x348) = 450.0f;
        *(f32 *) (p + 0x374) = 650.0f; /* D_800A00C4 */
        if (**(u16 **) (p + 0x36C) & 4) {
            *(f32 *) (p + 0x190) = 0.0f;
        } else {
            *(f32 *) (p + 0x190) = 135.0f;
        }
    } else if (camera_pop_mode((struct108 *) p, 3) != 0) {
        camera_set_followed_obj((struct108 *) p, p[0x23D]);
        *(f32 *) (p + 0x674) = 0.0f;
        *(f32 *) (p + 0x190) = 0.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E44D0/func_150B6CC0.s")
#endif
