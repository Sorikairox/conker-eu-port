#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} struct_eu_vec3;

typedef struct {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ struct_eu_vec3 unk34;
} struct_eu_1BAAA0_c;

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ struct_eu_1BAAA0_c *unk2C;
} struct_eu_1BAAA0_d;

typedef struct {
    /* 0x000 */ u8 pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8 pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x28];
    /* 0x05C */ u8 unk5C;
    /* 0x05D */ u8 pad5D[0x2C];
    /* 0x089 */ s8 unk89;
    /* 0x08A */ u8 pad8A[0x9A];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ s16 unk126;
    /* 0x128 */ u8 pad128[0x2C];
    /* 0x154 */ f32 unk154;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk15A;
} struct_eu_1BAAA0_e;

typedef struct {
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ s32 unk84;
} struct_eu_1BAAA0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x24];
    /* 0x40 */ struct_eu_1BAAA0_b *unk40;
} struct_eu_1BAAA0;

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518D1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518DC50.s")

s32 func_1518E808(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x1C));
    if ((temp_v1 != NULL) && ((*(s32 *)temp_v1) != 0)) {
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x14));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x18));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x1C));
        return 0;
    }
    return 1;
}

void func_1518E878(u8 *arg0) {
    s32 i;
    struct102 **var_s0;

    var_s0 = (struct102 **)(arg0 + 0x48);
    *(s32 *)(arg0 + 0x28) = 0;
    *(f32 *)(arg0 + 0x24) = 0.0f;
    for (i = 0; i < 100; i++) {
        if (*var_s0 != NULL) {
            func_1516972C(*var_s0);
        }
        var_s0 = (struct102 **)((u8 *)var_s0 + 0x18);
    }
    bzero(arg0 + 0x48, 0x960);
}

void func_1518E8EC(u8 *arg0, u8 arg1) {
    if (arg1 != arg0[0x22]) {
        func_1518E878(arg0);
        arg0[0x22] = arg1;
    }
}

s32 memcpy(u8 *, u8 **, s32);

u8 *func_1518E934(u8 **arg0, u8 arg1) {
    u8 *temp_v0;
    u8 *sp24;

    if ((*(u8 *)((u8 *)(*arg0) + 4)) == 0x96) {
        return NULL;
    }
    temp_v0 = func_15167A68(0x21, 1, 0x9EC, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0xC);
    (*(s32 *)((u8 *)temp_v0 + 0x28)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2C)) = 8;
    (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 4;
    (*(s32 *)((u8 *)temp_v0 + 0x30)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x38)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x40)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x34)) = 1.0f;
    bzero(temp_v0 + 0x48, 0x960);
    return sp24;
}

void func_1518EA10(struct_eu_1BAAA0 *arg0) {
    func_1518E878(arg0);
    func_1514EDF0(arg0, arg0->unk18);
}

void func_1518EA3C(void *arg0) {
    func_1518EA10(arg0);
    func_15169804(arg0);
}

void func_1518EA68(void *arg0) {
    func_1518EA10(arg0);
    func_15169824(arg0);
}

void func_1518EA94(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, s16 *arg6) {
    s32 temp_v1;

    *arg1 = 2;
    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    temp_v1 = func_150ADA20() & 1;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *arg0 = 0x13;
        break;
    case 1:
        *arg0 = 0x14;
        break;
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    *arg5 = 0xFF;
    *arg6 = 0x301;
}

void func_151429E0(s32, s32, s32, s32);

void func_1518EB48(s8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s16 *arg6) {
    s32 var_v0;

    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    *arg0 = 0x16;
    if (func_150ADA20() & 1) {
        var_v0 = 3;
    } else {
        var_v0 = 4;
    }
    func_151429E0(var_v0 & 0xFF, arg2, arg3, arg4);
    *arg5 = 0xC8;
    *arg6 = 0x401;
}

s32 func_1518D1C0(s32, s32, s32, u8, s32, s32, s32 *);
extern s32 D_800A7840;

s32 func_1518EBDC(u8 *arg0) {
    func_1518D1C0((*(s32 *)((u8 *)arg0 + 0x18)), 3, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)), &D_800A7840);
    (*(s16 *)((u8 *)arg0 + 0x1E)) = 0x80;
    (*(s8 *)((u8 *)arg0 + 0x21)) = -1;
    return 0;
}

s32 func_1518D1C0(s32, s32, s32, u8, s32, s32, s32 *);
extern s32 D_800A787C;

s32 func_1518EC44(u8 *arg0) {
    func_1518D1C0((*(s32 *)((u8 *)arg0 + 0x18)), 4, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)), &D_800A787C);
    (*(s16 *)((u8 *)arg0 + 0x1E)) = 0x80;
    (*(s8 *)((u8 *)arg0 + 0x21)) = -1;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518ECAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518F080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518F4C4.s")

s32 func_1518F5C8(u8 *arg0) {
    f32 x;
    f32 y;
    f32 z;
    f32 f;
    u8 *q;

    f = *(f32 *)(arg0 + 0x150);
    q = arg0; // fakematch: second name for arg0 puts the D_800BE9A4 address in v1
    *(f32 *)(q + 0x140) *= f;
    *(f32 *)(q + 0x144) += *(f32 *)(q + 0x14C) * D_800BE9A4;
    *(f32 *)(q + 0x148) *= f;
    x = *(f32 *)(arg0 + 0x140) * D_800BE9A4;
    y = *(f32 *)(arg0 + 0x144) * D_800BE9A4;
    z = *(f32 *)(arg0 + 0x148) * D_800BE9A4;
    *(f32 *)(q + 0x34) += x;
    *(f32 *)(q + 0x38) += y;
    *(f32 *)(q + 0x3C) += z;
    *(f32 *)(q + 0x40) += x;
    *(f32 *)(q + 0x44) += y;
    *(f32 *)(q + 0x48) += z;
    return 1;
}

s32 func_1518F678(struct_eu_1BAAA0_e *arg0) {
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk154);
    arg0->unk2C = arg0->unk2C - (arg0->unk2C * arg0->unk154);
    if (arg0->unk1C < arg0->unk158) {
        arg0->unk5C = arg0->unk1C * arg0->unk15A;
    }
    return 1;
}

s32 func_1518F6CC(struct_eu_1BAAA0_e *arg0) {
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk154);
    if (arg0->unk1C < arg0->unk158) {
        arg0->unk5C = arg0->unk1C * arg0->unk15A;
    }
    return 1;
}

s32 func_1518F710(u8 *arg0) {
    u8 *p = arg0 + 0x110;
    s32 v;

    *(s16 *)(p + 0x1E) -= D_800BE9E4;
    if (*(s16 *)(p + 0x1E) < 0) {
        *(s16 *)(p + 0x1E) = func_150ADA20() % 6U;
        if (func_150ADA20() & 3) {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0x10) + (*(f32 *)(p + 0xC) - *(f32 *)(p + 0x10)) * func_150ADA68();
        } else {
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0xC) + (*(f32 *)(p + 0x14) - *(f32 *)(p + 0xC)) * func_150ADA68();
        }
    }
    *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.359f;
    *(s16 *)(p + 0x1C) -= D_800BE9E4;
    if (*(s16 *)(p + 0x1C) < 0) {
        *(s16 *)(p + 0x1C) = func_150ADA20() % 17U;
        *(f32 *)(p + 0x8) = *(f32 *)(p + 0x4) + (*(f32 *)(p + 0x0) - *(f32 *)(p + 0x4)) * func_150ADA68();
    }
    *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 0x8) - *(f32 *)(arg0 + 0x2C)) * 0.186f;
    *(s16 *)(p + 0x2C) -= D_800BE9E4;
    if (*(s16 *)(p + 0x2C) < 0) {
        *(s16 *)(p + 0x2C) = func_150ADA20() % 15U;
        *(f32 *)(p + 0x28) = *(f32 *)(p + 0x24) + (*(f32 *)(p + 0x20) - *(f32 *)(p + 0x24)) * func_150ADA68();
    }
    *(s32 *)(arg0 + 0x24) = (s32)((*(f32 *)(p + 0x28) - *(s32 *)(arg0 + 0x24)) * 0.231f) + *(s32 *)(arg0 + 0x24);
    return 1;
}

s32 func_1518F8F4(u8 *arg0) {
    u8 *p;

    if (*(s16 *)(arg0 + 0x12C) == 0) {
        p = arg0 + 0x110;
        *(f32 *)(p + 0x8) = *(f32 *)(p + 0x4) + (*(f32 *)(p + 0x0) - *(f32 *)(p + 0x4)) * func_150ADA68();
        *(s16 *)(p + 0x1C) = 1;
    }
    p = arg0 + 0x110;
    if (p) {} // fakematch: keeps p in v1 for the 0x1E test
    if (*(s16 *)(p + 0x1E) == 0) {
        *(f32 *)(p + 0x18) = *(f32 *)(p + 0x10) + (*(f32 *)(p + 0xC) - *(f32 *)(p + 0x10)) * func_150ADA68();
        *(s16 *)(p + 0x1E) = 1;
    }
    *(f32 *)(arg0 + 0x30) += (*(f32 *)(p + 0x18) - *(f32 *)(arg0 + 0x30)) * 0.359f;
    *(f32 *)(arg0 + 0x2C) += (*(f32 *)(p + 0x8) - *(f32 *)(arg0 + 0x2C)) * 0.186f;
    return 1;
}

// rodata_inject: size 0x24CB34 4
void func_1518F9CC(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x21};

    func_15169260(sp1C, 1, arg0, arg1);
}

void func_1518FA0C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 v0;
    s32 v1;
    u8 a0;
    u8 a1;
    func_15169850(arg1, arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
    if (arg2 == 0x49) {
        v0 = *(s32 *)(arg0 + 0x18);
        v1 = *(s32 *)arg1;
        a0 = arg0[0x1C];
        a1 = arg1[4];
        if (v0 == v1 || a0 == a1) {
            func_1516972C(arg0);
        }
    }
}

s32 func_1518FB40(s32, u8 *, s16, s8, s8, s8, u8, s32, u8, s32);
s32 func_15190334(s32, u8 *, u8);
extern u8 *D_8008D9D0[];
s32 func_1518FA8C(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s32 sfpad; // fakematch: unused local shifts sp33 to the ref slot
    u8 sp33;

    if (arg0 == 0) {
        return 0;
    }
    if (func_15190334(arg0, &sp33, arg1) == 0) {
        return 0;
    }
    return func_1518FB40(arg0, D_8008D9D0[sp33] + arg1 * 0x50, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518FB40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518FD34.s")

void func_1518FDC8(u8 *arg0)
{
  u8 *new_var;
  new_var = ((u8 *) arg0) + 0x89;
  if ((*((s8 *) new_var)) != (-1))
  {
    D_8008DA20[*((s8 *) new_var)](arg0);
  }
}

s32 func_1518FE50(s32);

void func_1518FE0C(s32 arg0)
{
  u8 *new_var;
  u8 *temp_v0;
  f32 *new_var2;
  temp_v0 = ((((((arg0 + 0x30) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF;
  new_var2 = (f32 *) (((u8 *) temp_v0) + 0);
  new_var = temp_v0;
  *new_var2 = (f32) ((*((f32 *) (((u8 *) new_var) + 0xC))) + ((*((f32 *) (((u8 *) temp_v0) + 0x10))) * func_150ADA68()));
  func_1518FE50(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1518FE50.s")

s32 func_15190174(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *arg1) {
    struct_eu_1BAAA0_c *temp_a0 = arg0->unk2C;

    temp_a0->unk34 = *arg1;
    func_1514C390(temp_a0, arg1, arg0);
    return 1;
}

s32 func_151901B4(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *arg1) {
    struct_eu_1BAAA0_c *temp_a0 = arg0->unk2C;

    temp_a0->unk34 = *arg1;
    func_1514C4C0(temp_a0, arg1, arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_151901F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_15190334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_151905AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_1519078C.s")

void func_15190940(u8 *arg0) {
    func_15163DEC(arg0, arg0 + 0x20);
    func_15163F50(arg0, arg0 + 0x18);
}

void func_15190970(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_a2;
    u8 temp_a3;

    if (arg2 == 0) {
        temp_v0 = *(s32 *)(arg0 + 0x18);
        temp_v1 = *(s32 *)arg1;
        temp_a2 = arg0[0x1C];
        temp_a3 = arg1[4];
        if ((temp_v0 == temp_v1) || (temp_a2 == temp_a3)) {
            func_1516972C(arg0);
        }
    }
}

void func_151909C4(struct_eu_1BAAA0 *arg0) {
    struct_eu_1BAAA0_b *temp_v0 = arg0->unk40;

    temp_v0->unk84 = 0;
}

void func_151909D4(void *arg0) {
    func_151909C4(arg0);
    func_151617C4(arg0);
}

void func_15190A00(void *arg0) {
    func_151909C4(arg0);
    func_151617E4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_15190A2C.s")

void func_15190A88(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_1516944C(0x3E, (s32)&tmp, 0x2A);
}

void func_151D33FC(u8 *, s32, u8);
extern void (*D_8008DA24[])(u8 *, s32, u8);
void func_15190AC0(u8 *arg0, s32 arg1, u8 arg2) {
    void (*f)(u8 *, s32, u8);
    if (arg2 == 0x2A) {
        func_151D33FC(arg0, arg1, arg2);
    }
    f = D_8008DA24[arg0[0x8A]];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAF40/func_15190B2C.s")

void func_15190C34(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x10))) + 0x31C));
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0x1AC)) = 0;
    }
}

void func_15190C50(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 *p = (s32 *)(arg0 + 0x90);
    if (arg2 == 0x2D) {
        if (arg1[0] == p[2]) {
            p[2] = arg1[1];
            return;
        }
        if (arg1[1] == p[2]) {
            p[2] = arg1[0];
        }
    }
}

void func_1519072C(u8 *arg0)
{
  u8 *sp20[2];
  s32 sp1C;
  sp1C = 1;
  sp20[0] = arg0;
 if (0) { }
  if (sp1C)
  {
    sp1C = (s32) sp20;
    ((u8 *) sp20)[4] = arg0[0x3B];
    func_151D343C(sp1C, 0x2A);
  }
  func_1518F9CC(0xFFFFFFFFFFFFFFFF & sp1C, 0x49);
}

typedef struct { u8 *p; u8 b; } S190770;
s32 func_151920FC(void *, s32);
u8 func_151D8E20();

u8 *func_15190770(u8 **arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *obj;
    S190770 s;
    u8 *q;

    s.p = *arg0;
    s.b = (*arg0)[0x3B];
    func_151920FC(&s, 0xE);
    obj = func_15167A68(0x20, arg3, arg1 + 0x300, 1, arg2, 1);
    if (obj == NULL) {
        return NULL;
    }
    memcpy(obj + 0x10, arg0, 0xC);
    q = obj + 0x30;
    *(u8 **)(obj + 0x24) = q;
    *(u8 **)(obj + 0x28) = obj + 0x300;
    *(s32 *)(obj + 0x20) = 0;
    *(f32 *)(obj + 0x1C) = 0.0f;
    bzero(q, 0x2D0);
    *(s8 *)(obj + 0x2C) = func_151D8E20();
    return obj;
}
