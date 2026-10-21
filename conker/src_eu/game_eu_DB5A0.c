#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150ADD90(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 4));
    temp_f4 = (*(f32 *)((u8 *)arg1 + 0));
    temp_f6 = (*(f32 *)((u8 *)arg1 + 4));
    temp_f8 = (*(f32 *)((u8 *)arg1 + 8));
    temp_f10 = (*(f32 *)((u8 *)arg0 + 8));
    (*(f32 *)((u8 *)arg2 + 8)) = (f32) ((temp_f0 * temp_f6) - (temp_f2 * temp_f4));
    (*(f32 *)((u8 *)arg2 + 0)) = (f32) ((temp_f2 * temp_f8) - (temp_f10 * temp_f6));
    (*(f32 *)((u8 *)arg2 + 4)) = (f32) ((temp_f10 * temp_f4) - (temp_f0 * temp_f8));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DB5A0/func_150ADD90.s")
#endif