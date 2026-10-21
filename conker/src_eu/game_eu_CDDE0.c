#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct { u32 active:1; u32 flag:1; u32 kind:4; u32 pad:26; u32 count; u32 timer; } SlotEnt; // 12 bytes, D_800D3434 = &D_800D3430[0].count
extern SlotEnt D_800D3430[];


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CDDE0/func_150A00F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CDDE0/func_150A067C.s")

s32 func_150A0744(s32 arg0, u8 *arg1)
{
    SlotEnt *v = &D_800D3430[arg0];

    if (v->active) {
        return 0;
    }
    v->active = 1;
    v->flag = 0;
    v->kind = *(s32 *)(arg1 + 4);
    v->count = 0;
    return 1;
}

s32 func_150A07B0(s32 arg0, s32 arg1, u8 *arg2)
{
    switch (arg1) {
    case 0:
        D_800D3430[arg0].flag = 1;
        return 1;
    case 1:
        D_800D3430[arg0].flag = 0;
        return 1;
    case 2:
        D_800D3430[arg0].count = *(s32 *)(arg2 + 8);
        return 1;
    }
    return 0;
}

s32 func_150A0854(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return D_800D3434[arg0].unk0;
    }
    return 0;
}
