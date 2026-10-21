#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15188D80.s")

typedef struct Node8EBC { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8EBC *uC; s32 u10; } Node8EBC;
extern Node8EBC *D_800DFBFC;
void *allocate_memory(s32, s32, s32, s32);
s32 func_10004074(u8 *);
void func_15188FC8();
void func_15188EBC(s32 arg0, s32 arg1, s32 arg2) {
    Node8EBC *n;
    void *buf;

    for (n = D_800DFBFC; n != NULL; n = n->uC) {
        if (arg0 == n->u10) {
            if (n->u6 < arg1) {
                n->u6 = arg1;
            }
            n->u4 = arg2;
            return;
        }
    }
    n = allocate_memory(0x14, 1, 0, 0);
    if (n == NULL) {
        return;
    }
    buf = allocate_memory(0x180, 1, 1, 0);
    if (buf == NULL) {
        func_10004074((u8 *)n);
        return;
    }
    n->u0 = 1;
    n->u1 = 3;
    n->u2 = 0;
    n->u3 = 0x14;
    n->u4 = arg2;
    n->u6 = arg1;
    n->u8_ = buf;
    n->u10 = arg0;
    bzero(buf, 0x180);
    func_15188FC8(n, &D_800DFBFC);
}

typedef struct struct_15188FC8 {
    u8 pad0[0xC];
    struct struct_15188FC8 *unkC;
} struct_15188FC8;

void func_15188FC8(struct_15188FC8 *arg0, struct_15188FC8 **arg1) {
    struct_15188FC8 *var_v1;

    arg0->unkC = NULL;
    if (*arg1 != NULL) {
        for (var_v1 = *arg1; var_v1->unkC != NULL; var_v1 = var_v1->unkC) {
        }
        var_v1->unkC = arg0;
    } else {
        *arg1 = arg0;
    }
}

void func_1518900C(s32 arg0) {
    struct_eu_1B6590 *var_v0 = (struct_eu_1B6590 *)D_800DF7C8[0];
    while (var_v0 != NULL) {
        if (arg0 == var_v0->unk10) {
            var_v0->unk6 = 0;
        }
        var_v0 = var_v0->unkC;
    }
}

s32 func_10004074(u8 *);

void func_15189040(s32 arg0) {
    s32 temp_s0;
    s32 var_s1;
    u8 *var_s2;

    var_s1 = *D_800DF7C8;
    var_s2 = NULL;
    if (var_s1 != 0) {
        do {
            temp_s0 = (*(s32 *)((u8 *)var_s1 + 0xC));
            if (arg0 == (*(s32 *)((u8 *)var_s1 + 0x10))) {
                if (var_s2 == NULL) {
                    *D_800DF7C8 = temp_s0;
                } else {
                    (*(s32 *)((u8 *)var_s2 + 0xC)) = temp_s0;
                }
                func_100043B4((*(s32 **)((u8 *)var_s1 + 8)), 2U);
                func_10004074((u8 *) var_s1);
            } else {
                var_s2 = (u8 *) var_s1;
            }
            var_s1 = temp_s0;
        } while (temp_s0 != 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_151890E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189270.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_151893B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_151894F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189688.s")

void func_15189B14(u8 *arg0) {
    func_100043B4((*(s32 **)((u8 *)arg0 + 8)), 2U);
}

void func_15189B3C(u8 *arg0) {
    func_100043B4((*(s32 **)((u8 *)arg0 + 8)), 2U);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189B64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B6590/func_15189D14.s")

void func_151898C0(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = *D_800DF7C8;
    if (var_v0 != 0) {
loop_1:
        if (arg0 == (*(s32 *)((u8 *)var_v0 + 0x10))) {
            (*(s32 *)((u8 *)var_v0 + 0x14)) = arg1;
            return;
        }
        var_v0 = (*(s32 *)((u8 *)var_v0 + 0xC));
        if (var_v0 == 0) {

        } else {
            goto loop_1;
        }
    }
}
