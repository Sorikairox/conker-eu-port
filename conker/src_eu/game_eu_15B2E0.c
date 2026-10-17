#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xA8];
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
} struct_eu_15B2E0; // size 0xB0

extern struct_eu_15B2E0 *D_800DC6E0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B2E0/func_1512DAD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B2E0/func_1512DB74.s")

void func_1512DBDC(u8 *arg0) {
    D_800DC6E0[arg0[0x23D]].unkA8 = 0;
    D_800DC6E0[arg0[0x23D]].unkAC = 0;
}

s32 func_1512DC20(u8 *arg0) {
    return D_800DC6E0[arg0[0x23D]].unkA8 == D_800DC6E0[arg0[0x23D]].unkAC;
}
