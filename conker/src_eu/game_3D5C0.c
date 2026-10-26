#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// need to figure out the structs
s32 rope_create(s8 *, s32);
extern s32 D_80090648;
extern s32 D_80096750;

/* was func_15010110 */
void level_obj_init_ropes(void) {
    struct {
        s8 u4C;
        u8 pad4D[0x3];
        s32 u50;
        s32 u54;
        u8 pad58[0x8];
        s32 u60;
        u8 pad64[0x4];
        f32 u68;
        s8 u6C;
    } sp;
    s32 *var_s1;
    s8 temp_s2;
    s8 var_s0;

    level_dl_add_texture_scroll((*(s32 *)((u8 *)D_800B0E00 + 0)), (*(s32 *)((u8 *)(&D_80090648) + 0x50)), 0, -1, 0, 0, 0, -8);
    level_dl_add_texture_scroll((*(s32 *)((u8 *)D_800B0E00 + 4)), (*(s32 *)((u8 *)(&D_80090648) + 0x50)), 0, -1, 0, 1, 0, -8);
    sp.u6C = 0;
    var_s1 = &D_80096750;
    var_s0 = 0;
    do {
        temp_s2 = var_s0 + 1;
        (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)var_s1 + 0));
        (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)var_s1 + 4));
        (*(s32 *)((u8 *)(&sp.u50) + 0xC)) = (s32) (*(s32 *)((u8 *)var_s1 + 0xC));
        (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)var_s1 + 8));
        (*(s32 *)((u8 *)(&sp.u50) + 0x10)) = (s32) (*(s32 *)((u8 *)var_s1 + 0x10));
        (*(s32 *)((u8 *)(&sp.u50) + 0x14)) = (s32) (*(s32 *)((u8 *)var_s1 + 0x14));
        sp.u4C = temp_s2;
        sp.u68 = fabsf(sp.u54 - sp.u60);
        rope_create(&sp.u4C, 0);
        var_s0 = temp_s2;
        var_s1 += 6;   /* 0x18 bytes */
    } while (temp_s2 != 6);
}