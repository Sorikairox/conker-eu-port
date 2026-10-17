#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15115630(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511563C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151156DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511577C.s")

void func_1511581C(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151158E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115CDC.s")

extern f32 D_800A3370;
extern f32 D_800A3374;

void func_1511638C(u8 *arg0, u8 *arg1) {
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;

    sp1C = func_150AD780((*(f32 *)((u8 *)arg0 + 4)) * D_800A3370);
    temp_f0 = func_150AD78C((*(f32 *)((u8 *)arg0 + 4)) * D_800A3374);
    temp_f12 = (*(f32 *)((u8 *)arg1 + 0x14)) - (f32) (*(s16 *)((u8 *)arg0 + 0x10));
    temp_f14 = (*(f32 *)((u8 *)arg1 + 0x1C)) - (f32) (*(s16 *)((u8 *)arg0 + 0x14));
    if (((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) == 4) {
        (*(f32 *)((u8 *)arg0 + 0x7C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7C)) + ((temp_f0 * temp_f12) + (sp1C * temp_f14)));
        (*(f32 *)((u8 *)arg0 + 0x80)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x80)) - ((temp_f0 * temp_f14) + (sp1C * temp_f12)));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511645C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151164E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151165D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116690.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151166FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116940.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116E08.s")

void func_15116EA4(s32 arg0) {
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F;
    u8 pad50[0x23];
    u8 unk73;
} struct_15116EB0;

typedef struct {
    u8 pad0[0x57];
    u8 unk57;
} struct_15116EB0_2;

typedef struct {
    u8 pad0[0x31C];
    struct_15116EB0_2 *unk31C;
} struct_15116EB0_1;

void func_15116EB0(struct_15116EB0 *arg0, struct_15116EB0_1 *arg1) {
    if (arg0->unk4F & 4) {
        if (!(arg0->unk73 & 3) && !(arg0->unk73 & 4)) {
            if (arg1->unk31C->unk57 == 1) {
                arg0->unk73 &= ~3;
                arg0->unk73 |= 2;
            }
        }
    }
}

void func_15116F04(u8 *arg0) {
    if (arg0[0x73] & 2) {
        func_15116F34(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116F34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511712C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151172FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117858.s")

void func_15117A20(f32 *arg0) {
    arg0[2] = func_15117858(arg0, arg0[2]);
}

void func_15117A48(f32 *arg0) {
    arg0[1] = func_15117858(arg0, arg0[1]);
}

void func_15117A70(f32 *arg0) {
    arg0[0] = func_15117858(arg0, arg0[0]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117A98.s")

void func_15117CF0(f32 *arg0) {
    arg0[0] = func_15117A98(arg0, arg0[0]);
}

void func_15117D18(f32 *arg0) {
    arg0[2] = func_15117A98(arg0, arg0[2]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117D40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117F3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151182BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15118324.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151184BC.s")

void func_15118EEC(s32 arg0) {
    func_15118F2C(arg0, 0);
}

void func_15118F0C(s32 arg0) {
    func_15118F2C(arg0, 3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15118F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151194A4.s")

void func_1511992C(u8 *arg0, s32 *arg1) {
    if ((arg1[0] == 1) && (((u8 *)arg1)[0x65] == 0) && !(arg0[0x73] & 3) && !(arg0[0x73] & 4)) {
        arg0[0x73] &= ~3;
        arg0[0x73] |= 2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119974.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119C54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119EB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511A540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511A998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511AA1C.s")

void func_1511AC84(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x3C) != 0) {
        func_15116690(arg0);
    }
    func_1511AA1C(arg0, arg0 + 0x80, arg0 + 0x84);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ACC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511AD48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ADC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511B4B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511B604.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BAA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BD5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BFAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C08C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C37C.s")

void func_1511C3E4(u8 *arg0) {
    *(f32 *)(arg0 + 4) = func_150484A0(*(s16 *)(arg0 + 0x10) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8),
                                       *(s16 *)(arg0 + 0x14) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)) * D_800A35B0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C444.s")

void func_1511CAC8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511CAD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511CBC0.s")

void func_1511D0B4(s32 arg0, f32 *arg1) {
    *arg1 = D_800A35C4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511D0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511D91C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511DD44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511DF6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511E14C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511E320.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511E4F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ED08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F1D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F30C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F4C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F8A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511FA68.s")

void func_1511FD00(s32 *arg0, s32 arg1) {
    if (arg0[0x80 / 4] == 0) {
        arg0[0x80 / 4] = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511FD20.s")

void func_1511FEA8(u8 *arg0) {
    u8 *temp_v0 = func_151149AC(arg0[0x3F]);

    if (temp_v0 != NULL) {
        *(s16 *)(arg0 + 0x10) = *(s16 *)(temp_v0 + 0x10);
        *(s16 *)(arg0 + 0x12) = *(s16 *)(temp_v0 + 0x12);
        *(s16 *)(arg0 + 0x14) = *(s16 *)(temp_v0 + 0x14);
    }
}

void func_1511FEF0(void) {
    D_800DC3F0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511FF00.s")
