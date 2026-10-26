#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15017300 */
void level_lights_init(s16 arg0, s16 arg1) {
    s32 i;
    s16 tmp;

    tmp = arg0;
    bzero(&D_800D2138, 524);
    D_800D2138 = tmp;

    for (i = 0; i < 16; i++) {
        if ((1 << i) & arg1) {
            player_stat_modify(i, 0, D_80087270[i]);
            D_800D2457 = D_800D2456 = 6;
            player_stat_modify(i, 5, D_8008726C);
            player_stat_modify(i, 2, D_80087260);
            if (D_800BE616 != 0) {
                player_stat_modify(i, 9, D_80087264);
            }
        }
        level_lights_stub(arg1);
    }
    D_800D2340 = arg1;
    D_800D2132 = 0;
}

/* was func_1501748C */
void level_lights_stub(s16 arg0) {
}

/* was func_15017498 */
void level_lights_clear(void) {
    bzero(&D_800D2138, 524);
}

// double-loop
/* was func_150174C0 */
void level_table_relocate(s32 arg0) {
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;
    u16 temp_t2;
    u16 var_t0;
    u8 *temp_t1;

    var_v0 = 0;
    if ((s32) D_80087380 > 0) {
        var_a2 = 0;
        var_a3 = D_800D23C0;
        do {
            var_t0 = (*(u16 *)((u8 *)var_a3 + 2));
            var_a0 = 0;
            if ((s32) var_t0 > 0) {
                var_v1 = 0;
                do {
                    temp_t1 = D_800D23C0 + (var_v0 * 0x18) + var_v1;
                    temp_t2 = (*(u16 *)((u8 *)temp_t1 + 8));
                    var_a0 += 1;
                    if (((s32) temp_t2 >> 0xC) == 2) {
                        (*(u16 *)((u8 *)temp_t1 + 8)) = (u16) (temp_t2 + arg0);
                        var_a3 = D_800D23C0 + var_a2;
                        var_t0 = (*(u16 *)((u8 *)var_a3 + 2));
                    }
                    var_v1 += 2;
                } while (var_a0 < (s32) var_t0);
            }
            var_v0 += 1;
            var_a2 += 0x18;
            var_a3 += 0x18;
        } while (var_v0 < (s32) D_80087380);
    }
}
/* was func_15017578 */
void level_table_load(s32 arg0) {
    u32 tmp = 0;
    D_800D23C0 = asset_load(&tmp, 3, 12, arg0, 4);
    D_80087380 = tmp / 24;
    level_table_relocate(D_800DBF00);
}
