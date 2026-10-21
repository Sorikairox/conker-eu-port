#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 memcpy(s32, u8 **, s32);

s32 func_150CE660(u8 *arg0, s16 arg1, s32 arg2) {
    struct {
        u8 * u20;
        u8 u24;
        u8 pad25[0x3];
        f32 u28;
        f32 u2C;
        s32 u30;
        s8 u34;
        u8 pad35[0x8DB];
        s8 u910;
        s8 u911;
        s8 u912;
        u8 pad913[0x1];
        s16 u914;
        s8 u916;
    } sp;
    s32 var_v0;

    if (arg0 == NULL) {
        return 0;
    }
    sp.u910 = 1;
    sp.u911 = 1;
    sp.u912 = 0;
    sp.u916 = 2;
    sp.u30 = 0x2710;
    sp.u34 = 0;
    sp.u28 = 30000.0f;
    sp.u2C = 30000.0f;
    sp.u914 = arg1;
    sp.u20 = arg0;
    sp.u24 = (*(u8 *)((u8 *)arg0 + 0x3B));
    var_v0 = func_151604E4(&sp.u910, 0x8F0, arg2 & 0xFF);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x18, &sp.u20, 0x8F0);
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE660.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE960.s")

void func_150CEBA4(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x18;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else {
            if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
                *(s32 *)v = *(s32 *)arg1;
                v[4] = arg1[8];
            }
            goto end; // fakematch: permuter artifact (no-op jump)
end:        ;
        }
    } else {
        if (arg1) { // fakematch: permuter artifact (empty if)
        }
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}
