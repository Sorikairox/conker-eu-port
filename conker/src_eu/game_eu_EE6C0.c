#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150C0F48(void *);


void func_150C0EB0(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x20), (s32)(arg0 + 0x24), (s32)arg0);
}

void func_150C0EF0(void *arg0) {
    func_150C0F48(arg0);
    func_15169804(arg0);
}

void func_150C0F1C(void *arg0) {
    func_150C0F48(arg0);
    func_15169824(arg0);
}

void func_150C0F48(void *arg0) {
    s16 var_s0;
    s32 temp_s2;
    var_s0 = (*(s16 *)((u8 *)arg0 + 0x44));
    if (var_s0 != -1) {
        do {
            temp_s2 = var_s0 * 8;
            func_1516972C(*(void **)((*(u8 **)((u8 *)arg0 + 0x40)) + temp_s2));
            var_s0 = (*(s16 *)((u8 *)(*(u8 **)((u8 *)arg0 + 0x40)) + temp_s2 + 4));
        } while (var_s0 != -1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EE6C0/func_150C0FC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EE6C0/func_150C1138.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EE6C0/func_150C1698.s")
