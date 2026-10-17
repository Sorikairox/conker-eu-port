#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_eu_1501C860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CC1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CDA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CE34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D044.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D2C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D330.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D348.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DB18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DE84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DF70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E0C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E220.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E46C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E5AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E7A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501EA84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501ECA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501F7D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FF10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020430.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020F6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021834.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021E60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150220CC.s")

void func_15022238(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C39B4 = arg3;
    D_800C39AC[0] = arg0;
    D_800C39AC[1] = arg1;
    D_800C39AC[2] = arg2;
    D_800C3663 = 1;
}

void func_15022290(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C39C0 = arg3;
    D_800C39B8[0] = arg0;
    D_800C39B8[1] = arg1;
    D_800C39B8[2] = arg2;
}

void func_150222DC(s32 arg0) {
    D_800C3930[arg0] = 0;
}

void func_150222F0(s32 arg0) {
    D_800C396A[arg0] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022304.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022388.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150225D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150226E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150227FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022864.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150228F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502298C.s")

void func_15022A40(s32 *arg0) {
    s32 v = arg0[0];

    if ((v == 27) || (v == 4)) {
        if (D_800863B4[v] != NULL) {
            D_800863B4[v]();
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022C4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502330C.s")

void func_15023464(void) {
    bzero(D_800C3CA0, 0xA8);
}

void func_1502348C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((s16)D_800C3CA0[i].unk0 != 0) {
            func_1516D850(*(s32 *)((u8 *)&D_800C3CA0[i] + 0x34));
            *(s32 *)((u8 *)&D_800C3CA0[i] + 0x34) = 0;
            D_800C3CA0[i].unk0 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150234E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502354C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15023684.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502378C.s")
