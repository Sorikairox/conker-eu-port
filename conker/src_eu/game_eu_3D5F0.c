#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *allocate_memory(s32, s32, s32, s32);
s32 func_150C851C(s32);
extern u8 *D_eu_800BE900;

typedef struct { s8 a; s8 p1; s8 b; s8 p3; s16 c; s16 d; s16 e; } S0A;
void func_1500FDE0(void) {
    s32 i;

    D_eu_800BE900 = allocate_memory(0x64, 1, 0, 0);
    bzero(D_eu_800BE900, 0x64);
    for (i = 0; i < 10; i++) {
        ((S0A *)D_eu_800BE900)[i].a = i / 5;
        ((S0A *)D_eu_800BE900)[i].b = -1;
        ((S0A *)D_eu_800BE900)[i].c = func_150ADA20() % 5U;
    }
    func_150C851C(0x64);
    for (i = 0; i < 10; i++) {
        ((S0A *)D_eu_800BE900)[i].d = ((S0A *)D_eu_800BE900)[i].e;
    }
}

void func_1500FF4C(void) {
    func_1510CA2C(D_80091B68, 0, 0xAD, 0x75);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3D5F0/func_1500FF7C.s")
