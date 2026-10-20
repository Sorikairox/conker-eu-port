#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C000.s")

void func_1518C164(u8 *arg0) {
    s32 i;
    struct_eu_node *node;

    if (arg0 != NULL) {
        for (i = 0; i < 2; i++) {
            u8 *new_var; // fakematch: permuter temp, turns the loop tail into bnel
            node = D_800DD280[i][0x1F];
            D_800DD5C0++;
            while (node != NULL) {
                D_800DD5C8[D_800DD5C0] = node->next;
                new_var = (u8 *)node;
                *(u8 **)(new_var + 0x24) = arg0;
                if ((arg0 != NULL) || (arg0[0x3B] == *((u8 *)node + 0x28))) {
                    func_1516972C((struct102 *)node);
                }
                node = D_800DD5C8[D_800DD5C0];
            }
            D_800DD5C0--;
        }
    }
}

s32 memcpy(u8 *, s32, s32);

u8 *func_1518C240(s32 arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x1F, arg2, 0x44, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x10, arg0, 0x1C);
    (*(s32 *)((u8 *)temp_v0 + 0x2C)) = (s32) (func_150ADA20() & 0x1F);
    (*(s32 *)((u8 *)temp_v0 + 0x30)) = (s32) (func_150ADA20() & 0x1F);
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C2D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C628.s")

s32 func_1518CAB0(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    temp_v0[0x1B] = var_v1;
    if (temp_v0[0x1B] < 0) {
        return 0;
    }
    return 1;
}

typedef struct { f32 x, y, z; s32 a, b; } Node14;
typedef struct {
    u8 pad0[0x80];
    s32 u80;
    u8 pad84[6];
    s16 u8A;
    s16 u8C;
    s16 u8E;
    s16 u90;
    s16 u92;
    s16 u94;
    s16 u96;
    s16 u98;
    u8 pad9A[6];
    s8 uA0;
    s8 uA1;
    s8 uA2;
    u8 padA3[5];
} SpawnCAEC;
s32 func_1516865C(SpawnCAEC *, s32, s32, s32, s32);
s32 func_15168800(SpawnCAEC *, u8, u8);

s32 func_1518CAEC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    SpawnCAEC sp;
    u8 *obj;
    u8 *tbl;

    obj = *(u8 **)(arg0 + 0x98);
    tbl = *(u8 **)(arg0 + 0x94);
    arg2 = arg4; // fakematch: the unused arg2 holds the truncated arg4 (spill slot layout, permuter)
    sp.u80 = 0;
    sp.u8A = 0x100;
    sp.u8C = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
    sp.u8E = arg2;
    sp.u90 = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
    sp.u92 = sp.u94 = func_150ADA20() % 21U + 0x23;
    sp.uA2 = -1;
    sp.uA0 = 0x12;
    sp.u98 = 0xC;
    sp.uA1 = 0;
    sp.u96 = arg2;
    func_1516865C(&sp, 0xFF, 0xFF, 0xFF, 0xFF);
    func_15168800(&sp, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    *(s8 *)(obj + 0x20) = 4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CC0C.s")

void func_1518CDC0(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 id;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x24)) {
            (*(s32 *)((u8 *)arg0 + 0x24)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
            arg0->unk28 = (*(u8 *)((u8 *)arg1 + 9));
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)((u8 *)arg0 + 0x24)) {
            (*(s32 *)((u8 *)arg0 + 0x24)) = *(s32 *)(arg1 + 0);
            arg0->unk28 = (*(u8 *)((u8 *)arg1 + 8));
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied delay slot
    } else if (arg2 == 0) {
        id = *(s32 *)(arg1 + 0);
        if ((id == (*(s32 *)((u8 *)arg0 + 0x24))) || (arg0->unk28 == *(u8 *)(arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
