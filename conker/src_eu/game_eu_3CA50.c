#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
int func_151EFDD0(void);

void func_1500F240(f32 arg0, f32 arg1, f32 arg2) {
    struct {
        s32 u48;
        s16 u4C;
        s8 u4E;
        u8 pad4F[0x1];
        s32 u50;
        s32 u54;
        s8 u58;
        s8 u59;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        u8 pad5E[0x2];
        s32 u60;
    } sp;

    sp.u4E = 0x38;
    sp.u50 = 0;
    sp.u54 = (func_151EFDD0() % 4096) + 0x4000;
    sp.u48 = 0x20014;
    sp.u4C = 1;
    sp.u58 = 0xFF;
    sp.u59 = 0xFF;
    sp.u5A = 0;
    sp.u5B = 0;
    sp.u5C = 0;
    sp.u5D = 0xFF;
    sp.u60 = 0x30001;
    func_1513C5B0((s32) &sp.u48, 0, 0U, 0U, arg0, arg1, arg2, 110.0f, 110.0f, 0U, 0U, 0, 0xFFU, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3CA50/func_1500F240.s")
#endif
void func_1500F328(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct260 *temp_v0;

    temp_v0 = func_151491F4((s16) ((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1U, 0U, 0xA, 0xFFU, 0);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x2C)) = (s16) arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x2E)) = (s16) arg3;
        (*(s8 *)((u8 *)temp_v0 + 0x30)) = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3CA50/func_1500F3BC.s")
