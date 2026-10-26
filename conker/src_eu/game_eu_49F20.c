#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s8 D_800BEA35;
extern s32 D_800BEE20;
extern s32 D_800BEE24;
extern u16 D_800CC7A2;
void start_points_clear(void);
void rumble_stop_all(void);

/* was func_1501C710 */
void game_request_transition(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    rumble_stop_all();
    D_800D2132 = 0;
    switch (arg0) {
    case 0:
        break;
    case 4:
    case 6:
        D_800BEE20 = arg4;
        D_800BEE24 = arg3;
        D_800BE9F4 = arg1;
        D_800DD2C0 = (u8)arg2;
        D_800BEA35 = 2;
        break;
    case 1:
        D_800BEA35 = 3;
        D_800BE9F4 = arg1;
        D_800D2132 = D_800CC7A2;
        break;
    case 2:
        D_800BEA35 = 3;
        D_800BE9F4 = arg1;
        D_800DD2C0 = (u8)arg2;
        D_800D2132 = D_800CC7A2;
        break;
    case 3:
        if (D_800BE616 == 0) {
            D_800BEA35 = 4;
            start_points_clear();
        }
        break;
    case 5:
        D_800BE9F4 = (u16 *)5;
        D_800BEA35 = 1;
        break;
    }
}
