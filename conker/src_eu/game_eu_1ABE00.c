#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *allocate_memory(s32, s32, s32, s32);

u8 *func_1517E080(s32 arg0, s32 arg1) {
    s32 *sp18;
    s32 *var_t0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_v0;

    var_v1 = D_800DDD64;
    if (var_v1 != 0) {
        var_v0 = (*(s32 *)((u8 *)var_v1 + 0x24));
        if (var_v0 != 0) {
            do {
                var_v1 = var_v0;
                var_v0 = (*(s32 *)((u8 *)var_v0 + 0x24));
            } while (var_v0 != 0);
        }
        var_t0 = var_v1 + 0x24;
    } else {
        var_t0 = &D_800DDD64;
    }
    sp18 = var_t0;
    temp_v0 = allocate_memory(0x34, 1, 0, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    *var_t0 = (s32) temp_v0;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x28)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2E)) = 0;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0xC)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0x2F)) = (s8) arg0;
    (*(s8 *)((u8 *)temp_v0 + 0x30)) = (s8) arg1;
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E71C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E7FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517EA18.s")

Gfx *func_1517EFBC(Gfx *arg0) {
    gDPPipeSync(arg0++);
    gDPSetCombine(arg0++, 0xFFB3FF, 0xFF65FEFF);
    gDPSetOtherMode(arg0++, 0x2C0F, 0x504344);
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517F01C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517F18C.s")
