#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D658.s")

void func_1503D728(s32 *arg0, s32 arg1) {
    s32 temp_v0 = *arg0;
    if ((temp_v0 != 0) && !(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}

void func_1503D74C(s32 *arg0, s32 arg1) {
    while (*arg0 != 0) {
        *arg0 += arg1;
        arg0 += 2;
    }
}

void func_1503D774(u8 *arg0, s32 arg1)
{
  u8 *start = arg0;
  while (*(u16 *)arg0 != 0x3E7) {
    if (*(s32 *)(arg0 + 4) != 0) {
      func_1503D728(arg0 + 4, start);
    }
    arg0 += 8;
  }
  D_800C5A90[arg1] = (arg0 - start) >> 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D8E0.s")

s32 func_1503D8E0(s32);
void func_1503D800(s32);
s32 func_1502B350(u8 *, s32, s32 *);
s32 func_1502B5C8(s32 *, s32, ...);
void func_1503D74C(s32 *arg0, s32 arg1);
void func_1503D774(u8 *arg0, s32 arg1);

s32 func_1503D950(s32 arg0, s32 arg1) {
    s32 sp34;
    s32 *p;

    if (*(s32 **)&D_800D1588[arg0] != NULL) {
        return 0;
    }
    p = (s32 *)func_1502B5C8(&sp34, 2, 0xF, func_1503D8E0(arg0));
    if (p == NULL) {
        *(s32 **)&D_800D1588[arg0] = NULL;
        D_800C5A90[arg0] = 0;
        func_1503D800(arg0);
        return 4;
    }
    *(s32 **)&D_800D1588[arg0] = p;
    if ((*(s32 **)&D_800D1588[arg0])[0] != 0) {
        (*(s32 **)&D_800D1588[arg0])[0] += (s32)*(s32 **)&D_800D1588[arg0];
        func_1503D74C((s32 *)(*(s32 **)&D_800D1588[arg0])[0], (s32)*(s32 **)&D_800D1588[arg0] + 0x10);
    }
    if ((*(s32 **)&D_800D1588[arg0])[1] != 0) {
        (*(s32 **)&D_800D1588[arg0])[1] += (s32)*(s32 **)&D_800D1588[arg0];
    }
    if ((*(s32 **)&D_800D1588[arg0])[2] != 0) {
        (*(s32 **)&D_800D1588[arg0])[2] += (s32)*(s32 **)&D_800D1588[arg0];
    }
    *(s32 **)&D_800D1588[arg0] = (s32 *)((u8 *)*(s32 **)&D_800D1588[arg0] + 0x10);
    func_1503D774((u8 *)*(s32 **)&D_800D1588[arg0], arg0);
    func_1503D800(arg0);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DA64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DAF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DC74.s")

u8 func_1503DD2C(s32 arg0, s32 arg1) {
    u8 *p = ((u8 **)&D_800D19A0)[arg0];
    u8 *q = p - 0x38; // fakematch: computed before the NULL test (delay-slot addiu)
    u8 *r;
    u8 v;

    if (p == NULL) {
        return 0xFF;
    }
    if (*(u32 *)(q + 0x34) < arg1 + 1) {
        return 0xFF;
    }
    r = *(u8 **)(q + 0x30);
    if (r != NULL) {
        v = r[arg1];
    } else {
        v = 0xFF;
    }
    return v;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DD8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DF2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503E00C.s")
