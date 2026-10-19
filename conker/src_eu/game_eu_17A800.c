#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_1514F878
typedef struct { s32 w[3]; } V3_1514F878;
extern V3_1514F878 D_800A5D50;
extern V3_1514F878 D_800A5D5C;
extern f32 D_800A6238;

s32 func_1514F2FC(u8 *, u8 *);

s32 func_1514F2AC(u8 *, s32, u8 **);

u8 *func_15160A58(struct127 *, s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514CFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514D6CC.s")

extern u8 *D_8008AF88[];
extern void (*D_8008AEF8[])(s32);

s32 func_1514D880(u8 *arg0) {
    struct102 *p;
    struct102 *next;

    p = *(struct102 **)(arg0 + 0x2F4);
    if (p != NULL) {
        do {
            next = *(struct102 **)((u8 *)p + 0x14);
            // fakematch: the s16 index is re-read for the call (no local) and compared as -1 != x; keeps the register order of the original
            if (-1 != *(s16 *)(D_8008AF88[*(s16 *)((u8 *)p + 0x1C)] + 2)) {
                D_8008AEF8[*(s16 *)(D_8008AF88[*(s16 *)((u8 *)p + 0x1C)] + 2)](*(s32 *)((u8 *)p + 0x10));
            }
            func_1516972C(p);
            p = next;
        } while (next != NULL);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514D3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DA28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DAD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DBBC.s")

void func_1514DEDC(s32 arg0) {
}

void func_1514DEE8(struct127 *arg0) {
    f32 buf[8];
    u8 *r;
    *(s32 *)&buf[0] = 0;
    *(s32 *)&buf[1] = 0;
    *(s32 *)&buf[2] = 0;
    *(s32 *)&buf[3] = 0;
    *(s32 *)&buf[5] = 0;
    *(s32 *)&buf[6] = 0;
    *(s32 *)&buf[7] = 0;
    buf[4] = 12.0f;
    r = func_15159140(arg0, 1, 0x20);
    if (r != NULL) {
        memcpy(r + 0x58, buf, 0x20);
        func_1514F18C(r, arg0, 0x13);
    }
}

void func_1514DF64(struct127 *arg0) {
    func_1514DEE8(arg0);
    func_1514F18C(func_151AD010(arg0, 0x41A00000, 0), arg0, 0x14);
}

void func_1514DFA8(struct127 *arg0) {
    u8 *r;
    s32 buf[7];
    buf[5] = 0;
    buf[6] = 0;
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    r = func_15159140(arg0, 1, 0x1C);
    if (r != NULL) {
        memcpy(r + 0x58, buf, 0x1C);
        func_1514F18C(r, arg0, 0x13);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E014.s")

void func_1514E088(struct127 *arg0) {
    s32 temp_v0 = func_15159140(arg0, 1, 0);
    if (temp_v0 != 0) {
        func_1514F18C(temp_v0, arg0, 0x13);
    }
}

void func_1514E0C8(s32 arg0) {
}

void func_1514E0D4(void) {
    if (D_800BE9F0 == 0x14) {
        func_151B2610();
    }
}

void func_1514E108(void) {
    func_1514F704();
}

void func_1514E128(struct127 *arg0) {
    func_15160A58(arg0, 2, (s32 *)D_800A5C80, 2, 0x12C, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

void func_1514E1A8(struct127 *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}

void func_1514E1CC(s32 arg0) {
    func_151D1510(arg0, 0, 0xFF, 1);
}

void func_1514E1F4(u8 *arg0) {
    *(s32 *)(arg0 + 0x94) |= 2;
}

void func_1514E208(u8 *arg0) {
    *(s32 *)(arg0 + 0x94) |= 0x710;
}

void func_1514E21C(struct127 *arg0) {
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 1.0f, 0);
    func_15083568(arg0, 0x44, 1.0f, 0);
}

void func_1514E264(struct127 *arg0) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x31C);
    if (v != NULL) {
        v[0x94] = 1;
    }
    func_15083568(arg0, 0x17, 1.0f, 0);
}

void func_1514E29C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2BC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2DC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2FC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E31C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E33C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E35C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E37C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E39C(s32 arg0) {
}

void func_1514E3A8(s32 arg0) {
}

void func_1514E3B4(s32 arg0) {
}

void func_1514E3C0(struct127 *arg0) {
    if (((u8 *)D_800D2E4C)[0x11] & 8) {
        func_1514E21C(arg0);
    }
}

void func_1514E3F8(s32 arg0) {
}

extern u8 D_800A5C8C[];
extern u8 D_800A5C98[];
extern u8 D_800A5CA4[];
extern f32 D_800A61E4;
s32 func_15160CDC(struct127 *, s32, s32 *, s32 *, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1514E404(struct127 *arg0) {
    s32 temp_v0;

    func_15160CDC(arg0, 0xC, D_800A5C8C, D_800A5C98, D_800A61E4, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 1, 0xFF, 1);
    temp_v0 = func_15083568(arg0, 0x3C, 1.0f, 0);
    if (D_800BE9B4 == 0) {
        (*(s32 *)((u8 *)temp_v0 + 0x38)) = 0x7D0;
    }
    func_1514F18C(func_15160A58(arg0, 0, D_800A5CA4, 2, 0x12C, 0xB, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0, 0xFF, 1), arg0, 0x19);
}

void func_1514E540(u8 *arg0) {
    arg0[0x65] = func_15083FB0(9, arg0) + 1;
    arg0[0x101] |= 0x34;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E57C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E88C.s")

u8 * func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);
u8 * func_1518D1C0(struct127 *, s16, s32, u8, u8, s32, u8 *);

void func_1514EA78(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CB0), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EB28(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CC4), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EBD8(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CD8), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EC88(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CEC), arg0, 0xE);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}

void func_1514ED38(struct127 *arg0) {
    func_1514F18C(func_1518D1C0(arg0, 7, 0, 1, 0xFF, 1, D_800A5D00), arg0, 0xF);
}

void func_1514ED94(s32 arg0) {
}

void func_1514EDA0(struct102 *arg0) {
    func_1516972C(arg0);
}

void func_1514EDC0(struct102 *arg0) {
    func_1518E878(arg0);
    func_1516972C(arg0);
}

void func_1514EDEC(void) {
    func_1515F10C();
}

s32 func_1514EE0C(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        if (*(s32 *)(arg0 + 0x10) & 1) {
            *(s32 *)(arg0 + 0x10) &= ~1;
        } else {
            *(s32 *)(arg0 + 0x10) |= 1;
        }
        break;
    case 2:
        *(s32 *)(arg0 + 0x10) &= ~1;
        break;
    case 1:
        *(s32 *)(arg0 + 0x10) |= 1;
        break;
    default:
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514EE90.s")

s32 func_1514EF4C(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE90(arg0, arg1, arg2);
}

s32 func_1514EF6C(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE0C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514EF8C.s")

s32 func_1514F0DC(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE0C(arg0, arg1, arg2);
}

s32 func_1514F0FC(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}

u8 *func_1514F114(s32 arg0, s16 arg1, s32 arg2)
{
  int new_var2;
  u8 *new_var;
  u8 *temp_v0;
  temp_v0 = func_15167A68(0x24, 1, arg2 + 0x20, 1, 0xFFU, 1U);
  if ((temp_v0 == 0) ^ 0)
  {
    return 0;
  }
  new_var = ((u8 *) temp_v0) + 0x10; // fakematch: permuter temp for the store order
  *((s32 *) new_var) = arg0;
  new_var2 = 0; // fakematch: permuter temp, zero kept in a register
 *((s32 *) (((u8 *) temp_v0) + ((unsigned int) 0x18))) = new_var2; *((s32 *) (((u8 *) temp_v0) + 0x14)) = new_var2;
  *((s16 *) (((u8 *) temp_v0) + 0x1C)) = arg1;
  return temp_v0;
}

s32 func_1514F18C(void *arg0, struct127 *arg1, s16 arg2) {
    u8 *ret;
    u8 *node;
    struct_eu_link *next;
    s16 idx;

    ret = NULL;
    if (arg0 != NULL) {
        node = (u8 *)func_1514F114(arg0, arg2, 0);
        ret = node;
        if (node != NULL) {
            *(struct_eu_link **)(node + 0x14) = arg1->unk2F4;
            arg1->unk2F4 = (struct_eu_link *)node;
            next = *(struct_eu_link **)(node + 0x14);
            *(s32 *)(node + 0x18) = 0;
            if (next != NULL) {
                *(u8 **)((u8 *)next + 0x18) = node;
            }
        } else {
            idx = *(s16 *)(D_8008AF88[arg2] + 2);
            if (idx != -1) {
                D_8008AEF8[idx](arg0);
            } else {
                func_1516972C((struct102 *)arg0);
            }
        }
    }
    return (s32)ret;
}

s32 func_1514F250(struct_eu_link *arg0, s16 arg1, struct_eu_link **arg2) {
    s32 found = 0;
    struct_eu_link *n = arg0;
    struct_eu_link *next;

    while (n != NULL && found == 0) {
        next = n->unk14;
        if (arg1 == *(s16 *)((u8 *)n + 0x1C)) {
            found = 1;
        } else {
            n = next;
        }
    }
    if (arg2 != NULL) {
        *arg2 = n;
    }
    return found;
}

s32 func_1514F2AC(u8 *arg0, s32 arg1, u8 **arg2) {
    s32 found = 0;
    u8 *node = arg0;
    u8 *next;

    while (node != NULL && found == 0) {
        next = *(u8 **)(node + 0x14);
        if (arg1 == *(s32 *)(node + 0x10)) {
            found = 1;
        } else {
            node = next;
        }
    }
    if (arg2 != NULL) {
        *arg2 = node;
    }
    return found;
}

s32 func_1514F2FC(u8 *arg0, u8 *arg1) {
    s32 sp1C;
    if (arg0 == *(u8 **)(arg1 + 0x2F4)) {
        *(u8 **)(arg1 + 0x2F4) = *(u8 **)(arg0 + 0x14);
    }
    if (*(u8 **)(arg0 + 0x14) != NULL) {
        *(u8 **)(*(u8 **)(arg0 + 0x14) + 0x18) = *(u8 **)(arg0 + 0x18);
    }
    if (*(u8 **)(arg0 + 0x18) != NULL) {
        *(u8 **)(*(u8 **)(arg0 + 0x18) + 0x14) = *(u8 **)(arg0 + 0x14);
    }
    sp1C = *(s32 *)(arg0 + 0x10);
    func_1516972C(arg0);
    return sp1C;
}

void func_1514EDF0(s32 arg0, u8 *arg1) {
    s32 temp_v0;
    u8 *var_s1;
    u8 *sp34;
    u8 temp_s0;
    var_s1 = (*(u8 **)((u8 *)arg1 + 0x2F4));
    sp34 = NULL;
    do {
        temp_v0 = func_1514F2AC(var_s1, arg0, &sp34);
        temp_s0 = temp_v0;
        if (temp_v0 != 0) {
            var_s1 = (*(u8 **)((u8 *)sp34 + 0x14));
            func_1514F2FC(sp34, arg1);
        }
    } while (temp_s0 != 0);
}

void func_1514F3E0(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        s16 unk6;
    } sp20;

    sp20.unk0 = arg0;
    sp20.unk4 = arg0[0x3B];
    sp20.unk5 = 0;
    sp20.unk6 = 300;
    func_1514F18C(func_1515C3C0(&sp20, 0, 255, 1), arg0, 0x16);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F43C.s")

void func_1514F680(void) {
    func_1514F704();
}

s32 func_1514F6A0(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0xD:
        (*(u8 **)(arg0 + 0x14))[9] = 0;
        break;
    case 0xE:
        (*(u8 **)(arg0 + 0x14))[9] = 1;
        break;
    default:
        return func_1514EE0C(arg0, arg1, arg2);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F704.s")

void func_1514F878(struct127 *arg0) {
    V3_1514F878 sp54;
    V3_1514F878 sp48;
    sp54 = D_800A5D50;
    sp48 = D_800A5D5C;
    func_15160CDC(arg0, 5, &sp54, &sp48, D_800A6238, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
}

void func_1514F93C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x3A, -1, 0, 0x2B, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_1514F9BC(struct127 *arg0) {
    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5D68), arg0, 0xD);
}

void func_1514FA18(s32 arg0) {
    func_151D7A60(arg0, 1, -1, 0xFF, 1);
}

void func_1514FA48(s32 arg0) {
    func_151D7A60(arg0, 2, 1, 0xFF, 1);
}

void func_1514FA78(s32 arg0) {
    func_151D7A60(arg0, 3, 0, 0xFF, 1);
}

void func_1514FAA8(s32 arg0) {
    func_151D7A60(arg0, 4, -1, 0xFF, 1);
}

void func_1514FAD8(s32 arg0) {
    func_150C4620(arg0, -1, 0xFF, 1);
}

void func_1514FB00(struct127 *arg0) {
    func_1501175C(arg0, 0xFF, 1);
    func_15011A78(arg0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514FB3C.s")
