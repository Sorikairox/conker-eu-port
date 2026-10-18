#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE110/func_15080900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE110/func_15080A20.s")

void func_15080AA8(s32 arg0) {
    struct127 *p;
    u8 b;
    p = &D_800CC2D0[arg0];
    if ((p->unk31C->pad6C[8] != 0) && (!(p->unk31C->pad6C[8] & 0x80))) {
        p->unk31C->pad6C[8] = 0;
    }
    b = p->unk31C->unk75;
    if ((b != 0) && (!(b & 0x80))) {
        p->unk31C->unk75 = 0;
    }
}

void func_15080B18(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg2 = 1 << (arg0 & 7);
    *arg1 = arg0 >> 3;
}

s32 func_15080B38(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    func_15080B18(arg0, &sp1C, &sp18);
    if (D_eu_800BE9A0[sp1C] & sp18) {
        return 1;
    }
    return 0;
}

void func_15080B84(void) {
    u16 new_var; // fakematch: permuter temp
    u16 *q;
    u16 temp_a0;
    q = (u16 *) D_800D1998;
    if (q != 0) {
        if (((unsigned short) D_800D1994) != D_800D1995) {
            temp_a0 = q[D_800D1994];
            new_var = temp_a0; // fakematch
            if (0 != temp_a0) {
                func_1001263C((s32) new_var, 0x7FFF, 0x40);
            }
            D_800D1994++;
        }
    }
}

void func_15080BF4(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x20) {
        func_15080B84();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE110/func_15080C28.s")

s32 func_10004074(s32);
void func_1516D850(s32);
void func_151F2D6C(s32, s32);

void func_15080FE8(void) {
    s32 r;
    D_800D1941 = 0;
    func_1516D850(D_800D1950);
    func_10004074(D_800D1944);
    if (D_800D1948 != 0) {
        r = D_800D1948;
        func_10004074(r);
        func_10004074(D_800D194C);
        func_10004074(D_800D1998);
        D_800D1948 = 0;
    }
    func_151F2D6C(0, 0x5622);
}

extern u8 *D_800D1DBC;

void func_15081064(void) {
    if ((D_800D1941 != 0) && ((*(u8 *)((u8 *)D_800D1950 + 0x15)) == 0)) {
        func_15080FE8();
        if ((D_800BE9F0 != 0x29) && (D_800BE9F0 != 0x2E)) {
            (*(u8 *)((u8 *)D_800D2E60 + 8)) = (u8) ((*(u8 *)((u8 *)D_800D2E60 + 8)) | 0x10);
        }
        if (D_800D1DBC != NULL) {
            (*(s8 *)((u8 *)D_800D1DBC + 0x14)) = 1;
            D_800D1DBC = NULL;
        }
    }
}

s32 func_150810F4(void) {
    if (D_800D1941 == 0) {
        return 1;
    }
    return 0;
}
