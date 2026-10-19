#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_eu_1501C860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CC1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CDA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CE34.s")

s32 func_1501D064(s32 arg0) {
    s32 sum = 0;
    s32 i;

    for (i = 0; i < D_800C3A5A[arg0]; i++) {
        sum += D_800C39F8[arg0][i];
    }
    return sum;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D044.s")

s32 func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32, s32);
extern s32 D_800C3A88;

s32 func_1501D240(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 temp_v0;

    temp_v0 = func_1502B6BC(&sp30, 0, &sp34, 3, 6, arg0, arg1);
    if (temp_v0 != 0) {
        (&D_800C3A88)[arg2] = temp_v0;
    } else {
        (&D_800C3A88)[arg2] = 0;
    }
    return temp_v0;
}

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

extern u16 *D_800C39E8[];
extern u8 *D_800C3A10[];
void func_15022388(s32 arg0, s32 arg1) {
    struct127 *obj;
    u8 *e;
    if (D_800C39E8[arg1][arg0] != 0) {
        e = D_800C3A10[arg1] + arg0 * 8;
        if (*(u16 *)e == 2) {
            obj = func_15083E90(e[2]);
            if (obj != NULL) {
                *((u8 *)obj + 0x6C) = 0;
                *((u8 *)obj + 0x6D) = 0;
                *((u8 *)obj + 0x6A) = 0;
                *((u8 *)obj + 0x6B) = 0;
                *(s16 *)((u8 *)obj + 0x282) = 0;
                *(s16 *)((u8 *)obj + 0x27A) = 0;
                *(s16 *)((u8 *)obj + 0x27C) = 0;
                *(s16 *)((u8 *)obj + 0x27E) = 0;
                *(s16 *)((u8 *)obj + 0x280) = 0;
                func_1507E7E4(obj, 0, 3, 0xFFFF, 0xA);
                *((u8 *)obj + 0x71) = 0;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150225D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150226E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022764.s")

s32 func_15022764(s32, s32);

void func_150227FC(s32 arg0) {
    s32 var_s0;
    u8 *temp_s1;

    temp_s1 = &D_800C3A5A[arg0];
    var_s0 = 0;
    if ((s32) *temp_s1 > 0) {
        do {
            func_15022764(var_s0, arg0);
            var_s0 += 1;
        } while (var_s0 < (s32) *temp_s1);
    }
}

u8 *func_151149AC(u8);
extern u8 D_800C3970[];
void func_15022864(s32 arg0)
{
  s32 i;
  u8 *cnt;
  u8 *p;
  cnt = &D_800C396A[arg0];
 do { i = 0; if ((*cnt) > 0) { p = D_800C3970 + (arg0 * 0x1E); do { func_151149AC(*p)[0x6E] = 1; i += 1; p += 1; } while (i < (*cnt)); } } while (0);
}

void func_15022388(s32, s32);
s32 func_15022440(s32, s32);

void func_150228F0(s32 arg0) {
    s32 var_s0;
    u8 *temp_s2;

    if ((&D_800C35EA)[arg0] == 1) {
        D_800C3638 = 0;
        temp_s2 = &D_800C3A5A[arg0];
        var_s0 = 0;
        if ((s32) *temp_s2 > 0) {
            do {
                func_15022440(var_s0, arg0);
                func_15022388(var_s0, arg0);
                var_s0 += 1;
            } while (var_s0 < (s32) *temp_s2);
        }
        D_800C3638 = 1;
    }
}

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

void func_150234E8(s16 *arg0, s32 arg1) {
    if (arg1 != 0) {
        func_1516D850(*(s32 *)((u8 *)arg0 + 0x34));
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    } else if (*(u8 *)((u8 *)arg0 + 0xC) != 0) {
        func_1516D898(*(s32 *)((u8 *)arg0 + 0x34));
    } else {
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    }
    *(s16 *)((u8 *)arg0) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502354C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15023684.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502378C.s")
