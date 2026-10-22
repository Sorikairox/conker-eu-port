#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A0BC0[];
#endif


#ifdef NON_MATCHING
s32 memcpy(s32, u8 **, s32);

/* P80: arg3 goes on to func_151604E4 (its 2nd func_15167A68 argument); the only caller, func_150268BC, passes 0 */
s32 func_150CE660(u8 *arg0, s16 arg1, s32 arg2, s32 arg3) {
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
    var_v0 = func_151604E4(&sp.u910, 0x8F0, arg2 & 0xFF, arg3);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x18, &sp.u20, 0x8F0);
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE660.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800A0BD0;
s32 func_15144CEC(s32 *, u8 *, s32 *, s32 *, f32 *, s32);

s32 func_150CE710(u8 *arg0) {
    struct {
        f32 u34;
        s32 u38;
        s32 u3C;
        s32 u40;
    } sp;
    u8 *sp28;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f0;
    s32 temp_a3;
    s32 temp_f10;
    s32 temp_f18;
    s32 temp_f4;
    s32 temp_f8;
    u8 var_t5;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = arg0 + 0x18;
    if (*(*(s32 **)((u8 *)arg0 + 0x18)) == 0) {
        return 0;
    }
    temp_v0 = (*(u8 **)((u8 *)temp_v1 + 0));
    if ((*(u8 *)((u8 *)temp_v1 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) {
        return 0;
    }
    temp_a3 = (*(s32 *)((u8 *)temp_v0 + 0x1D4));
    if (temp_a3 == 0) {
        (*(u8 *)((u8 *)temp_v1 + 0x14)) = (u8) ((*(u8 *)((u8 *)temp_v1 + 0x14)) & 0xFFFE);
    } else {
        sp28 = temp_v1;
        func_15143134(((u8 *)&D_800A0BC0), &sp.u40, temp_a3 + 0xD00);
        if (func_15144CEC(&sp.u40, sp28 + 0x28, &sp.u3C, &sp.u38, &sp.u34, D_80082FA4) != 0) {
            temp_f12 = (*(f32 *)((u8 *)sp28 + 0x28));
            temp_f0 = (*(f32 *)((u8 *)sp28 + 8)) * sp.u34;
            temp_f14 = (*(f32 *)((u8 *)sp28 + 0x2C));
            temp_f2 = (*(f32 *)((u8 *)sp28 + 0xC)) * sp.u34;
            temp_f18 = (s32) (temp_f12 - temp_f0);
            temp_f8 = (s32) (temp_f14 - temp_f2);
            (*(s32 *)((u8 *)sp28 + 0x18)) = temp_f18;
            (*(s32 *)((u8 *)sp28 + 0x1C)) = temp_f8;
            temp_f10 = (s32) (temp_f12 + temp_f0);
            (*(s32 *)((u8 *)sp28 + 0x20)) = temp_f10;
            temp_f4 = (s32) (temp_f14 + temp_f2);
            (*(s32 *)((u8 *)sp28 + 0x24)) = temp_f4;
            if (((f32) temp_f18 > D_800A0BD0) || ((f32) temp_f10 < 0.0f) || (var_f0 = (f32) temp_f8, (var_f0 > 215.0f)) || ((f32) temp_f4 < 0.0f)) {
                var_t5 = (*(u8 *)((u8 *)sp28 + 0x14)) & 0xFFFE;
                goto block_22;
            }
            if ((f32) (*(s32 *)((u8 *)sp28 + 0x18)) < 0.0f) {
                (*(s32 *)((u8 *)sp28 + 0x18)) = 0;
                var_f0 = (f32) (*(s32 *)((u8 *)sp28 + 0x1C));
            }
            if (var_f0 < 0.0f) {
                (*(s32 *)((u8 *)sp28 + 0x1C)) = 0;
            }
            if ((f32) (*(s32 *)((u8 *)sp28 + 0x20)) > D_800A0BD0) {
                (*(s32 *)((u8 *)sp28 + 0x20)) = 0x123;
            }
            if ((f32) (*(s32 *)((u8 *)sp28 + 0x24)) > 215.0f) {
                (*(s32 *)((u8 *)sp28 + 0x24)) = 0xD7;
            }
            (*(u8 *)((u8 *)sp28 + 0x14)) = (u8) ((*(u8 *)((u8 *)sp28 + 0x14)) | 1);
        } else {
            var_t5 = (*(u8 *)((u8 *)sp28 + 0x14)) & 0xFFFE;
block_22:
            (*(u8 *)((u8 *)sp28 + 0x14)) = var_t5;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE710.s")
#endif
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
