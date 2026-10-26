#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800D33E0[];
extern f32 D_800D33F8[];
extern u8 D_800D340C[];
extern s32 D_800D3C60;
void func_1509E330(s32 arg0, u8 *arg1) {
    if (*(s32 *)(arg1 + 4) == 1 && D_800D3C60 == 3) {
        D_800D33E0[*(s32 *)(arg1 + 8)] = (f32)*(s32 *)(arg1 + 0xC) * 0.000015258789f;
        D_800D33F8[*(s32 *)(arg1 + 8)] = (f32)*(s32 *)(arg1 + 0xC) * 0.000015258789f;
        D_800D340C[*(s32 *)(arg1 + 8)] = 1;
    }
}

void func_1509E3C4(s32 arg0, s32 arg1) {
}

#ifdef NON_MATCHING
s32 func_1508A040(void);
s32 func_1508A63C(void);
s32 func_1508AB7C(void);
s32 func_1508C370(void);
s32 func_1508C5F0(s32);
s32 func_1508CF34(s32, s32, s32, s32, s32, s32);
s32 func_1508DE78(void);
s32 func_1508E080(void);
s32 func_1508DF48(s32, s32);
s32 func_1508BE18(void);
s32 func_1508DCAC(s32);
s32 func_1508ECF8(s32, s32);
s32 func_150871B8(s32);
s32 func_1508712C(s32, f32 *, f32 *, f32 *);
void func_15087540(s32, s32, s32);
void func_150877C0(s32, s32, f32);
void func_1508823C(s32, s32);
void func_1508845C(s32, s32);
void func_15088434(s32, s32);
s32 func_15088568(s32, s32);
void func_1508B630(s32);
void func_15182388(s32);
void text_printf_at(s32, s32, u8, s32, ...);
void func_150498A0(f32 *, f32, f32 *, f32, f32, f32);
void func_15049978(f32 *, f32, f32 *, f32, f32, f32);
extern char D_8009F6D0[]; /* "%d" */
extern s32 D_800D2870;
extern u16 D_8009015C;

// rail_script_command: script command handler (pointer table at ROM 0x22DB2C, next to func_1509E7EC) for the rail
// race / camera commands. cmd selects the action; args is the command record (s32 words, parameters from +0x8).
// Commands 4..15 and 22 return the callee's result, 25 / 26 return the eased value * 65536, the rest return 0.
s32 func_1509E3D4(s32 arg0, u32 cmd, u8 *args) {
    s32 *a = (s32 *) args;
    f32 x;
    f32 y;
    f32 z;
    s32 point;
    struct127 *obj;

    switch (cmd) {
    case 0:
        func_15182388(0);
        return 0;
    case 1:
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        text_printf_at(0x96, 0x56, 1, (s32) D_8009F6D0, (a[2] + 59) / 60);
        D_8009015C |= 0x80;
        break;
    case 2:
        D_800D2870 = a[2];
        break;
    case 3:
        hud_clock_set_enabled(a[2]);
        return 0;
    case 4:
        return func_1508A040();
    case 5:
        return func_1508A63C();
    case 6:
        return func_1508AB7C();
    case 7:
        return func_1508C370();
    case 8:
        return func_1508C5F0(a[2]);
    case 9:
        return func_1508CF34(a[2], a[3], a[4], a[5], 0, 0);
    case 10:
        return func_1508DE78();
    case 11:
        return func_1508E080();
    case 12:
        return func_1508DF48(a[2], a[3]);
    case 13:
        return func_1508BE18();
    case 14:
        return func_1508DCAC(a[2]);
    case 15:
        return func_1508ECF8(a[2], a[3]);
    case 16:
        point = func_150871B8(a[2]);
        if (point != 0xFF) {
            func_1508712C(point, &x, &y, &z);
            func_1508B20C(x, y, z, (f32) a[3]);
            return 0;
        }
        break;
    case 17:
        func_15087540(a[2], a[3], a[4]);
        return 0;
    case 18:
        func_150877C0(a[2], a[3], 0.1f);
        return 0;
    case 19:
        func_1508823C(a[2], a[3]);
        return 0;
    case 20:
        func_1508845C(a[2], a[3]);
        return 0;
    case 21:
        func_15088434(a[2], a[3]);
        return 0;
    case 22:
        return func_15088568(a[2], a[3]);
    case 23:
        func_1508B630(a[2]);
        return 0;
    case 24:
        obj = func_15083E90(args[0xB]);
        if (obj != NULL) {
            obj_remove(obj, 0);
        }
        break;
    case 25:
        func_150498A0(&D_800D33F8[a[2]], a[3] * (1.0f / 65536.0f), &D_800D33E0[a[2]], a[4] * (1.0f / 65536.0f),
                      a[5] * (1.0f / 65536.0f), *(f32 *) ((u8 *) D_800DBFF0 + 0x7B4));
        return (s32) (D_800D33F8[a[2]] * 65536.0f);
    case 26:
        func_15049978(&D_800D33F8[a[2]], a[3] * (1.0f / 65536.0f), &D_800D33E0[a[2]], a[4] * (1.0f / 65536.0f),
                      a[5] * (1.0f / 65536.0f), *(f32 *) ((u8 *) D_800DBFF0 + 0x7B4));
        return (s32) (D_800D33F8[a[2]] * 65536.0f);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CBB40/func_1509E3D4.s")
#endif

#ifdef NON_MATCHING
s32 func_1508863C(s32);
s32 func_15088688(s32);
s32 func_150886E0(s32);
s32 func_1508872C(s32);
s32 func_15088760(s32, s32);
s32 func_15088C74(void);
s32 func_1508A41C(s32);
s32 func_1508B5F0(s32);
s32 func_1508CA14(s32, s32);
s32 func_1508CE28();
s32 func_1508CEE4(void);
s32 func_1508EB2C(s32);
f32 func_150CF550(s32, s32);
extern u16 D_8009015C;
extern s32 D_800CCA1C;
extern s8 D_800E1000;

s32 func_1509E7EC(s32 arg0, u32 arg1, u8 *arg2) {
    s32 *var_v0;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_v1;
    struct127 *temp_v0;
    struct127 *temp_v0_2;

    switch (arg1) {
    case 0:
        return (s32) func_150CF550((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
    case 1:
        temp_v1 = (*(s32 *)((u8 *)arg2 + 8)) - (*(s32 *)((u8 *)arg2 + 0x10));
        temp_a0 = (*(s32 *)((u8 *)arg2 + 0xC)) - (*(s32 *)((u8 *)arg2 + 0x14));
        return (s32) sqrtf((f32) ((temp_v1 * temp_v1) + (temp_a0 * temp_a0)));
    case 2:
        return func_1508CEE4();
    case 3:
        return func_1508CE28();
    case 4:
        return func_1508CA14((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
    case 5:
        return (s32) D_800E1000;
    case 6:
        return func_1508A41C((*(s32 *)((u8 *)arg2 + 8)));
    case 7:
        return func_1508EB2C((*(s32 *)((u8 *)arg2 + 8)));
    default:
block_45:
        return 0;
    case 9:
        return func_1508863C((*(s32 *)((u8 *)arg2 + 8)));
    case 10:
        return func_15088688((*(s32 *)((u8 *)arg2 + 8)));
    case 11:
        return func_150886E0((*(s32 *)((u8 *)arg2 + 8)));
    case 12:
        return func_1508872C((*(s32 *)((u8 *)arg2 + 8)));
    case 13:
        return func_15088760((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
    case 14:
        return func_15088C74();
    case 15:
        return D_8009015C & 0x40;
    case 16:
        return (s32) D_800E1010[(*(s32 *)((u8 *)arg2 + 8))];
    case 17:
        return func_1508B5F0((*(s32 *)((u8 *)arg2 + 8)));
    case 21:
    case 22:
        return (s32) (D_800D33F8[(*(s32 *)((u8 *)arg2 + 8))] * 65536.0f);
    case 18:
        temp_v0 = func_15083E90((*(u8 *)((u8 *)arg2 + 0xB)));
        if (temp_v0 != NULL) {
            return ((s32) temp_v0->x_position << 0x10) | ((s32) temp_v0->z_position & 0xFFFF);
        }
        goto block_45;
    case 19:
        temp_v0_2 = func_15083E90((*(u8 *)((u8 *)arg2 + 0xB)));
        if (temp_v0_2 != NULL) {
            return (s32) (s16) (s32) temp_v0_2->y_position;
        }
        goto block_45;
    case 20:
        var_v1 = 0;
        var_v0 = &D_800CCA1C;
        if ((D_800CC2D0->interaction_state != 0) && (*D_800CC2D4 == (*(s32 *)((u8 *)arg2 + 8)))) {
            var_v1 = 1;
        }
        do {
            if (((*(s32 *)((u8 *)var_v0 + 0)) != 0) && ((*(u8 *)((u8 *)var_v0 + 4)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            if (((*(s32 *)((u8 *)var_v0 + 0x32C)) != 0) && ((*(u8 *)((u8 *)var_v0 + 0x330)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            if (((*(s32 *)((u8 *)var_v0 + 0x658)) != 0) && ((*(u8 *)((u8 *)var_v0 + 0x65C)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            if (((*(s32 *)((u8 *)var_v0 + 0x984)) != 0) && ((*(u8 *)((u8 *)var_v0 + 0x988)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            var_v0 = (s32 *) ((u8 *) var_v0 + 0xCB0);
        } while (var_v0 != &D_800D121C);
        return var_v1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CBB40/func_1509E7EC.s")
#endif