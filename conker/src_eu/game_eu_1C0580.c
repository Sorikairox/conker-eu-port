#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 floor_flags_surface_type(s32);
s32 obj_surface_handler_class(u8 *, s32 *);
extern void (**D_8008FC00[])(u8 *);
/* was func_15192800 */
void obj_surface_handler_dispatch(u8 *arg0, s32 arg1) {
    s32 sp2C;
    s32 sfpad; // fakematch: frame padding
    void (*fn)(u8 *);
    s32 idx;

    if ((arg0 != NULL) && (obj_surface_handler_class(arg0, &sp2C) != 0)) {
        switch (floor_flags_surface_type(*(s32 *)(arg0 + 0x184))) {
        case 5:
            if (D_800BE9F0 == 0x14) {
                idx = 2;
            } else {
                idx = 1;
            }
            break;
        case 6:
            idx = 3;
            break;
        default:
            idx = 1;
            break;
        }
        fn = D_8008FC00[sp2C][idx];
        if (fn != NULL) {
            fn(arg0);
        }
    }
}

#ifdef NON_MATCHING
/* was func_15192E20 */
s32 obj_surface_handler_class(u8 *arg0, s32 *arg1) {
    s32 var_v1;
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 4));
    var_v1 = 0;
    switch ((s32) temp_v0) {                        /* irregular */
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        var_v1 = 1;
        *arg1 = 0;
        break;
    case 0x53:
        var_v1 = 1;
        *arg1 = 1;
        break;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C0580/obj_surface_handler_class.s")
#endif