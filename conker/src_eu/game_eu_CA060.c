#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1509CD0C(s32 arg0, s32 arg1);
void func_15022290(s16, s16, s16, f32);
void func_15022238(s16, s16, s16, f32);
#endif


#ifdef NON_MATCHING
void func_1501D348(s32, s32, s32, s32, s32);
extern s8 D_800C39E2;
extern s8 D_800C39E3;
extern s8 D_800C40B9;
extern s8 D_800C40BC;
extern s32 D_800D3C60;

// event_action_scene: event-script scene actions (ids 0x1xxx). P176: s32 like the handler table; cases 1 / 3 / 4
// (start a scene) return 1, or 0 while a scene is playing (D_800C35EA), as the asm does. The asm leaves v0
// undefined in cases 2 / 5 / 6 / other (a callee's result or D_800D3C60): 0 here.
s32 func_1509C850(s32 arg0, s32 arg1, u8 *arg2) {
    s32 sp3C;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_v1;

    switch (arg1) {
    case 1:
        if (D_800C35EA == 0) {
            sp3C = D_800BE9F0;
            if (D_800D3C60 == 6) {
                func_15022238((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            } else if (D_800D3C60 == 3) {
                temp_a0 = (*(s32 *)((u8 *)arg2 + 8));
                if ((temp_a0 & 0xF000) == 0x2000) {
                    func_1509CD0C(temp_a0, 0);
                } else {
                    sp3C = temp_a0;
                }
            }
            func_1501D348(sp3C, arg0, 0, 0, 0);
            return 1;
        }
        return 0;
    case 4:
        if (D_800C35EA == 0) {
            if (D_800D3C60 == 6) {
                func_15022238((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            }
            temp_s0 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            func_1501D348(0x25, arg0, 0, 0, 0);
            D_800BE9F0 = temp_s0;
            return 1;
        }
        return 0;
    case 3:
        if (D_800C35EA == 0) {
            sp30 = (*(s32 *)((u8 *)arg2 + 8));
            temp_v1 = (*(s32 *)((u8 *)arg2 + 0xC));
            sp34 = D_800BE9F0;
            if (D_800D3C60 == 8) {
                sp2C = temp_v1;
                func_15022238((*(s16 *)((u8 *)arg2 + 0x12)), (*(s16 *)((u8 *)arg2 + 0x16)), (*(s16 *)((u8 *)arg2 + 0x1A)), (f32) (*(s32 *)((u8 *)arg2 + 0x1C)) * 0.000015258789f);
            } else if (D_800D3C60 == 5) {
                sp34 = (*(s32 *)((u8 *)arg2 + 0x10));
            }
            func_1501D348(sp34, arg0, 0, sp30, temp_v1);
            return 1;
        }
        return 0;
    case 2:
        D_800C39E2 = arg0 + 1;
        D_800C39E3 = (s8) D_800BE9F0;
        D_800C40B9 = 1;
        if (D_800D3C60 == 6) {
            func_15022290((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            return 0;
        }
        if (D_800D3C60 == 3) {
            temp_a0_2 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_a0_2 & 0xF000) == 0x2000) {
                func_1509CD0C(temp_a0_2, 1);
                return 0;
            }
            D_800C39E3 = (s8) temp_a0_2;
            return 0;
        }
    default:
        return 0;
    case 5:
        D_800C39E2 = arg0 + 1;
        D_800C39E3 = 0x25;
        if (D_800D3C60 == 6) {
            func_15022290((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            return 0;
        }
        break;
    case 6:
        D_800C40BC = 1;
        break;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA060/func_1509C850.s")
#endif
#ifdef NON_MATCHING
extern u8 D_800C3A92;
extern u8 D_800C40B8;

// event_query_scene: event-script scene queries (ids 0x1xxx; arg0 = scene, arg1 = query). P176 (browser P174):
// returns the asm's per-case answer (jtbl_8009E828); the m2c body was void and the s32 handler table read 0.
// 1: scene arg0 no longer playing (0 while D_800C35C4 is set), 2: scene arg0 playing (D_800C40B8), 3 / 6: cutscene
// arg0 playing (D_800C3A08), 4: no scene playing, 5: D_800C3A92 (debug skip). Other queries: the asm leaves v0
// unchanged (0 here).
s32 func_1509CBD8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        if (D_800C35C4 != 0) {
            return 0;
        }
        if (D_800C35EA == 0) {
            return 1;
        }
        if (arg0 == D_800C40B8) {
            return 0;
        }
        return 1;
    case 2:
        if (D_800C35EA == 1 && arg0 == D_800C40B8) {
            return 1;
        }
        return 0;
    case 3:
        if (D_800C35EA == 1 && arg0 == D_800C3A08) {
            return 1;
        }
        return 0;
    case 4:
        return D_800C35EA != 1;
    case 5:
        return D_800C3A92;
    case 6:
        if (D_800C35EA == 1 && arg0 == D_800C3A08) {
            return 1;
        }
        return 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA060/func_1509CBD8.s")
#endif
#ifdef NON_MATCHING
void func_15022238(s16, s16, s16, f32);
void func_15022290(s16, s16, s16, f32);

void func_1509CD0C(s32 arg0, s32 arg1) {
    f32 var_f0;
    struct127 *temp_v0;

    temp_v0 = func_1505EEF4(arg0 & 0xFFF);
    if (temp_v0 != NULL) {
        if (D_800DBFF0->unk2C & 0x100) {
            var_f0 = (*(f32 *)((u8 *)D_800DBFF0 + 0x760));
        } else {
            var_f0 = D_800DBFF0->unk37C;
        }
        if (arg1 != 0) {
            func_15022290((s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, var_f0 + 180.0f);
            return;
        }
        func_15022238((s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, var_f0 + 180.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA060/func_1509CD0C.s")
#endif