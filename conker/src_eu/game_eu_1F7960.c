#include <ultra64.h>
#include "functions.h"
#include "variables.h"
void *memcpy(void *, const void *, unsigned int);

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA398.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA4E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CAC50.s")

void func_151CB07C(struct102 *arg0, u8 **arg1, u8 arg2) {
    void (*f)(void *, u8 **, u8);
    u8 *v;

    if (arg2 == 0x21) {
        if (*(s32 *)((u8 *)arg0 + 0x70) == (s32)arg1[0]) {
            func_1516972C(arg0);
        }
    dummy_label: ; // fakematch: empty label after the first arm makes IDO fill the b delay slot like the original
    } else if (arg2 == 0) {
        v = arg1[0];
        if (*(s32 *)((u8 *)arg0 + 0x70) == *(s32 *)(v + 0x318)) {
            func_1516972C(arg0);
        }
    }
    f = D_8008FFB0[*(u8 *)((u8 *)arg0 + 0x7D)];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB128.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB2D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB6C0.s")

void func_151CBA4C(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x18) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x18) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

void func_151CBAC0(u8 *arg0) {
    f32 target;
    u8 *t;
    u8 *p;

    p = arg0 + 0x70;
    t = *(u8 **)p;
    if ((**(u16 **)(t + 0x36C) & 0x2000) && *(u16 *)(*(u8 **)(t + 0x3D4) + 0x19E) == 0) {
        target = *(f32 *)(p + 8);
    } else {
        target = 0.0f;
    }
    *(f32 *)(p + 4) += (target - *(f32 *)(p + 4)) * 0.4f;
    arg0[0x2E] = *(f32 *)(p + 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CBBAC.s")

void func_151CBEC8(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if ((arg2 == 0x37) && (arg1[0] == temp_v0[0xE]) && (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0)) {
        *(f32 *)(temp_v0 + 0x10) = 0.0f;
        temp_v0[0xC] |= 1;
        *(f32 *)(temp_v0 + 0x14) = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CBF20.s")

void func_151CC11C(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x20) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x20) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

f32 func_151CC784(u8 *arg0);
void func_1514373C(f32 arg0, f32 arg1, u8 *arg2, u8 *arg3);

typedef struct {
    u8 pad0[0x18];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} Sub151CC190;

s32 func_151CC190(u8 *arg0) {
    f32 temp;
    f32 prod;
    Sub151CC190 *v;

    v = (Sub151CC190 *)(arg0 + 0x70);
    temp = func_151CC784(arg0);
    if (temp != v->unk28) {
        v->unk28 = temp;
        prod = (temp - v->unk18) * v->unk20 * 6.283186f;
        func_1514373C(v->unk24 + prod, 55.0f, arg0 + 0x10, arg0 + 0x14);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC784.s")

void func_151CC840(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_15155C9C((f32 *) &sp1C, 0x46);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC86C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCAD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCD2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCDF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CD2CC.s")

s32 func_151A5580(s32, s32, s32, s32, s32, s32, u8, s32);

void func_151CD444(u8 *arg0) {
    s32 temp_v0;
    u8 *sp28;

    if (D_800BE616 != 0) {
        sp28 = arg0;
        temp_v0 = func_151A5580(0, 0, 0, 0xFF, 0, (s32) (*(u8 *)((u8 *)arg0 + 0x23D)), 1, 4);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x20, &sp28, 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CD4B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CD7D4.s")
