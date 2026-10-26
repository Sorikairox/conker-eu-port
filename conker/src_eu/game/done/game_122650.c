#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_80088B44;
extern s32 D_800CC454;

/* was func_150F51A0 */
void storm_thunder_flag_set(s32 arg0, s32 arg1) {
    D_80088B40 = 1;
}

/* was func_150F51BC */
s32 storm_thunder_flag_take(void) {
    if (D_80088B40 != 0) {
        D_80088B40 = 0;
        return 1;
    } else {
        return 0;
    }
}

/* was func_150F51E8 */
void storm_thunder_sfx_update(s32 arg0) {
    if (((D_800CC454 & 0X1F) == 3) || ((D_800CC454 & 0x1F) == 4)) {
        if (D_800BE9E4 < D_80088B44){
            if(D_800C35EA != 1) {
                D_80088B44 = (D_80088B44 - D_800BE9E4);
            }
        } else {
            D_80088B44 = ((random_int() & 0x3F) + 0xC0);
            sound_play_2d(15, 18000, ((random_int() & 0x3F) + 0x20), 0, 0);
        }
    }
}
