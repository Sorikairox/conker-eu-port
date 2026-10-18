#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15177F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_151787D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178D1C.s")

u8 *func_15179108(u8 arg0) {
    u8 *var_v1 = D_800DD368;

    while (var_v1 != NULL) {
        if (arg0 == var_v1[0x34]) {
            return var_v1;
        }
        var_v1 = *(u8 **)(var_v1 + 8);
    }
    return NULL;
}

void func_15179154(u8 arg0, s32 arg1, s16 arg2) {
    u8 *temp_v0;

    temp_v0 = func_15179108(arg0);
    if (temp_v0 != NULL) {
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0x80000000;
        (*(s16 *)((u8 *)temp_v0 + 0x30)) = arg2;
    }
}

void func_151791A4(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    u8 *temp_v0;
    temp_v0 = func_15179108(arg0);
    if (temp_v0 != NULL) {
        *(s32 *)(temp_v0 + 0x10) = (arg1 << 0x10) | (arg2 & 0xFFFF);
        *(s32 *)(temp_v0 + 0x14) = arg3 << 0x10;
        *(s16 *)(temp_v0 + 0x30) = arg4;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178C9C.s")

extern s32 D_800DD36C;
s32 func_15179314(u8 *arg0) {
    u8 *next; // fakematch: declared before p to move the spill slot to 0x20
    u8 *p = (u8 *)D_800DD36C;

    func_100111C8(*(u16 *)(arg0 + 0x2E));
    while (p != NULL) {
        next = *(u8 **)(p + 8);
        if (*(u8 **)(p + 0x14) == arg0) {
            func_1516972C(p);
        }
        p = next;
    }
    func_15169824(arg0);
}

s32 func_15179314(u8 *);
void func_15178E14(u8 arg0)
{
    func_15179314(func_15179108(arg0));
}
