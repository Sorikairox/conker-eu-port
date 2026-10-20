#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15115630(s32 arg0) {
}

void func_1511563C(u8 *arg0) {
    f32 temp_f0;

    (*(f32 *)((u8 *)arg0 + 0x68)) = (f32) ((f32) (((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) * D_800BE9E4) * 0.00390625f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x68)) + (*(f32 *)((u8 *)arg0 + 8)));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 8));
    if (temp_f0 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0 - 360.0f);
    }
}

void func_151156DC(u8 *arg0) {
    f32 temp_f0;

    (*(f32 *)((u8 *)arg0 + 0x64)) = (f32) ((f32) (((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) * D_800BE9E4) * 0.00390625f);
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x64)) + (*(f32 *)((u8 *)arg0 + 4)));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 4));
    if (temp_f0 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0 - 360.0f);
    }
}

void func_1511577C(u8 *arg0) {
    f32 temp_f0;

    (*(f32 *)((u8 *)arg0 + 0x60)) = (f32) ((f32) (((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) * D_800BE9E4) * 0.00390625f);
    (*(f32 *)arg0) = (f32) ((*(f32 *)((u8 *)arg0 + 0x60)) + (*(f32 *)arg0));
    temp_f0 = (*(f32 *)arg0);
    if (temp_f0 < 0.0f) {
        (*(f32 *)arg0) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)arg0) = (f32) (temp_f0 - 360.0f);
    }
}

void func_1511581C(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151158E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115CDC.s")
void func_1511638C(u8 *arg0, u8 *arg1) {
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;

    sp1C = func_150AD780((*(f32 *)((u8 *)arg0 + 4)) * 0.017453292f);
    temp_f0 = func_150AD78C((*(f32 *)((u8 *)arg0 + 4)) * 0.017453292f);
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

void func_151182BC(u8 *arg0, u8 *arg1) {
    s32 lo = *(s32 *)(arg0 + 0x3C) & 0xFFFF;
    s32 f;
    if (*(s32 *)arg1 == 1 && (arg0[0x4F] & 4)) {
        f = arg0[0x73];
        if (!(f & 3) && !(f & 4) && (lo == 0 || (*(u8 **)(arg1 + 0x31C))[0x57] == 1)) {
            arg0[0x73] = f & 0xFFFC;
            arg0[0x73] |= 2;
        }
    }
}

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

s32 func_15022BB0(s32, s32);
s32 func_15116854(u8 *);

void func_1511ACC0(u8 *arg0) {
    if ((D_800C35EA == 1) && (func_15022BB0((arg0 - (u8 *)D_800DBEF4) / 160, 0) != 0)) {
        *(s32 *)(arg0 + 0x7C) = 0;
        *(f32 *)(arg0 + 0x18) = 0.0f;
    }
    func_15116854(arg0);
    func_1511AA1C(arg0, arg0 + 0x80, arg0 + 0x84);
}

void func_1511AD48(u8 *arg0) {
    s32 var_a1;
    s32 var_v1;
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x80));
    (*(s8 *)((u8 *)temp_v0 + 0x1E)) = 1;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0x1C)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x1D)) = 7;
    (*(f32 *)((u8 *)temp_v0 + 0x14)) = 260.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x18)) = 100.0f;
    var_v1 = 0;
    var_a1 = 0;
    if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
        do {
            var_v1 += 1;
            *(f32 *)((*(s32 *)((u8 *)temp_v0 + 4)) + var_a1) = 0.0f;
            var_a1 += 4;
        } while (var_v1 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ADC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511B4B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511B604.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BAA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BD5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BFAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C08C.s")

s32 func_1511C08C(u8 *, s32, s32, f32, f32);
void func_1511C37C(u8 *arg0)
{
  u8 *v;
  u8 *s;
  s = *(u8 **)(arg0 + 0x80);
  if (s != NULL) {
    v = s;
  } else {
    v = (u8 *)func_15083E90(arg0[0x3F]);
  }
  if (v != NULL) {
    func_1511C08C(arg0, *(s32 *)(v + 0x14), *(s32 *)(v + 0x1C), 1.0f, 1.0f);
  }
}

void func_1511C3E4(u8 *arg0) {
    *(f32 *)(arg0 + 4) = func_150484A0(*(s16 *)(arg0 + 0x10) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8),
                                       *(s16 *)(arg0 + 0x14) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)) * 57.295776f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C444.s")

void func_1511CAC8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511CAD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511CBC0.s")

void func_1511D0B4(s32 arg0, f32 *arg1) {
    *arg1 = 22000.0f;
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

void func_1511F30C(u8 *arg0) {
    s32 dir;
    f32 step;
    f32 lim;

    if (*(s32 *)(arg0 + 0x7C) == 0) {
        *(f32 *)(arg0 + 0x84) = (f32) *(s16 *)(arg0 + 0x14);
    }
    step = (f32) D_800BE9E4 * 4.0f;
    dir = 1 - (*(u8 *)(arg0 + 0x72) & 1);
    if (*(s32 *)(arg0 + 0x80) != 0) {
        if (dir & 1) {
            lim = *(f32 *)(arg0 + 0x84);
            *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) + step);
            if (lim < (f32) *(s16 *)(arg0 + 0x14)) {
                *(s16 *)(arg0 + 0x14) = (s32) lim;
            }
        } else {
            lim = *(f32 *)(arg0 + 0x84);
            *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) - step);
            if ((f32) *(s16 *)(arg0 + 0x14) < lim) {
                *(s16 *)(arg0 + 0x14) = (s32) lim;
            }
        }
    } else if (dir & 1) {
        *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) - step);
        lim = *(f32 *)(arg0 + 0x84) - 350.0f;
        if ((f32) *(s16 *)(arg0 + 0x14) < lim) {
            *(s16 *)(arg0 + 0x14) = (s32) lim;
        }
    } else {
        *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) + step);
        lim = *(f32 *)(arg0 + 0x84) + 350.0f;
        if (lim < (f32) *(s16 *)(arg0 + 0x14)) {
            *(s16 *)(arg0 + 0x14) = (s32) lim;
        }
    }
    *(s32 *)(arg0 + 0x7C) = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F4C8.s")

void func_15114E8C(f32 (*)[4], u8 *);
u8 *func_151149AC(u8);
void func_1511F8A4(u8 *arg0) {
    s32 pad[2]; // fakematch: frame pad
    f32 sp48[4][4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    u8 *temp_v0;
    u16 t = *(u16 *)(arg0 + 0x3E);
    if ((*(u16 *)(arg0 + 0x54) == 0x8005) && (D_800BE9F0 == 0x35)) {
        temp_v0 = func_151149AC(t);
        if (temp_v0 != 0) {
            func_15114E8C(sp48, temp_v0);
            func_150A7E40(sp48, -3.0f, 223.0f, 549.0f, &sp44, &sp40, &sp3C);
            *(s16 *)(arg0 + 0x10) = (s32)sp44;
            *(s16 *)(arg0 + 0x12) = (s32)sp40;
            *(s16 *)(arg0 + 0x14) = (s32)sp3C;
        }
    }
}

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
