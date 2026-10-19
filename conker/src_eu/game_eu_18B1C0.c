#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_1515D5F8
s32 func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);

void func_1515F61C(f32, s32);

f32 func_1515F578(s16 *, s32);

s32 func_1505D024();


void *func_1515D9B0(void) {
    void *sp1C = allocate_memory(0x10, 1, 2, 0);
    bzero(sp1C, 0x10);
    return sp1C;
}

u8 *func_1515D9F0(s32 arg0) {
    u8 *p;
    s32 n;
    s32 *q = &arg0; // fakematch: address-taken arg
    n = *q * 0x60;
    p = allocate_memory(n, 1, 2, 0);
    bzero(p, n);
    return p;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515D4D4.s")

struct lnode_1515DA90 { struct lnode_1515DA90 *next; };
struct lnode_1515DA90 *func_1515DA90(void) {
    struct lnode_1515DA90 *p;
    struct lnode_1515DA90 *cur;

    p = allocate_memory(0x34, 1, 2, 2);
    if (p != NULL) {
        bzero(p, 0x34);
        if (D_800DCD78 != 0) {
            cur = (struct lnode_1515DA90 *)D_800DCD78;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = p;
        } else {
            D_800DCD78 = (s32)p;
        }
        p->next = NULL;
    }
    return p;
}


void func_1515DB1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    func_1515D5F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

s32 func_1515D5F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    u8 *temp_v0;


    temp_v0 = (u8 *)func_1515DA90();
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 4)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 5)) = (s8) arg4;
        (*(s8 *)((u8 *)temp_v0 + 6)) = (s8) arg5;
        (*(s8 *)((u8 *)temp_v0 + 7)) = (s8) arg6;
        (*(s8 *)((u8 *)temp_v0 + 8)) = (s8) arg7;
        (*(s8 *)((u8 *)temp_v0 + 9)) = (s8) arg8;
        (*(u8 *)((u8 *)temp_v0 + 0xB)) = arg9;
        (*(s8 *)((u8 *)temp_v0 + 0xA)) = 0;
        (*(s16 *)((u8 *)temp_v0 + 0xE)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x10)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x12)) = (s16) arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x2F)) = (s8) arg3;
        (*(s8 *)((u8 *)temp_v0 + 0x2C)) = 0x7F;
        (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 0x2E)) = 0;
    }
    return (s32) temp_v0;
}

void func_1515DC0C(void) {
    u8 *var_v0 = (u8 *)D_800DCD78;
    while (var_v0 != NULL) {
        var_v0[0xC] = 0;
        var_v0[0x30] = 0;
        var_v0 = *(u8 **)var_v0;
    }
}

void func_1515DC38(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515DC40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515DE84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515E7E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515E9AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515EAB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515EDF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515F0F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515F1E8.s")

void func_1515F5B0(f32, s32);

void func_1515F4E4(s16 *arg0) {
    func_1515F5B0(1.0f / func_1515F578(arg0, 0), 0);
    func_1515F5B0(1.0f / func_1515F578(arg0, 5), 1);
    func_1515F5B0(1.0f / func_1515F578(arg0, 0xA), 2);
    func_1515F61C(-func_1515F578(arg0, 0xE), 3);
}

f32 func_1515F578(s16 *arg0, s32 arg1) {
    s32 v = arg0[arg1];
    v = (u16)arg0[arg1 + 0x10] | (v << 16);
    return v * (1.0f / 65536.0f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515F5B0.s")

extern s32 D_800DD140;
void func_1515F61C(f32 arg0, s32 arg1) {
    if (arg0 >= 32767.0f) {
        arg0 = 32767.0f;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    *(s32 *)((u8 *)&D_800DD140 + (arg1 * 4)) = (s32) arg0;
}

void func_1515F10C(s32 **arg0) {
    s32 **prev = NULL;
    s32 **cur = (s32 **)D_800DCD78;

    while (cur != arg0) {
        prev = cur;
        cur = (s32 **)*cur;
    }
    if (prev != NULL) {
        *prev = *cur;
    } else {
        D_800DCD78 = (s32)*cur;
    }
    func_10004074(cur);
}

void func_1515F170(s32 arg0, u8 arg1) {
    u8 *var_v0 = (u8 *)D_800DCD78;
    while (var_v0 != NULL) {
        if (arg0 == var_v0[0xB]) {
            var_v0[9] = arg1;
        }
        var_v0 = *(u8 **)var_v0;
    }
}

u8 *func_1515F1B0(struct_eu_15144598 *arg0) {
    s32 var_v1;
    s32 temp_v0;
    s32 sp2C;

    temp_v0 = func_10003C6C(0x10, 1, 2, 0, 1);
    var_v1 = temp_v0;
    if (temp_v0 == 0) {
        return NULL;
    }
    (*(struct_eu_15144598 **)temp_v0) = arg0;
    if (arg0 != NULL) {
        sp2C = var_v1;
        (*(f32 *)((u8 *)var_v1 + 4)) = func_1514462C(arg0);
    } else {
        (*(f32 *)((u8 *)temp_v0 + 4)) = 0.0f;
    }
    if (arg0 != NULL) {
        sp2C = var_v1;
        (*(f32 *)((u8 *)var_v1 + 8)) = func_15144598(arg0);
    } else {
        (*(f32 *)((u8 *)var_v1 + 8)) = 0.0f;
    }
    (*(s32 *)((u8 *)var_v1 + 0xC)) = 0;
    return (u8 *) var_v1;
}

void func_1515F25C(s32 *arg0, s32 *arg1) {
    arg1[3] = *arg0;
    *arg0 = (s32)arg1;
}

void func_1515F7E0(void *arg0, u8 *arg1) {
    s32 idx = *(s32 *)(arg1 + 0x18);
    if ((idx >= 0) && (idx < 12)) {
        void (*fp)(void *, void *) = D_8008B430[idx];
        if (fp != NULL) {
            fp(arg0, arg1);
        }
    }
}

void func_1515F828(u8 *arg0, s32 arg1) {
    func_1505D024(arg0, 0x6001D, *(u16 *)(arg0 + 0x7A), -1);
}

extern void (*D_8008B460[])(u8 *, u8 *);
void func_1515F858(u8 *arg0, u8 *arg1) {
    s32 v;

    if (arg0[0x3B] == 1) {
        v = *(s32 *)(arg1 + 0x1C);
        if ((v >= 0) && (v < 3)) {
            D_8008B460[v](arg0, arg1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515F8A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515FB34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_1515FDC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_151600E0.s")

void func_15160104(u8 *arg0, s32 arg1) {
    func_1505D024(arg0, 0x6002D, *(u16 *)(arg0 + 0x7A), -1);
}

u8 *func_15105C24(s32);

void func_15160134(u8 *arg0, s32 arg1) {
    s32 pad; // fakematch: unused local moves v to sp18
    struct127 *v = NULL;
    u8 *t;
    s32 a3;
    t = func_15105C24(arg1);
    if (t != NULL) {
        v = *(struct127 **)(t + 0x98);
    }
    if (v != NULL) {
        a3 = v - D_800CC2D0;
    } else {
        a3 = -1;
    }
    func_1505D024(arg0, 0x6002E, *(u16 *)(arg0 + 0x7A), a3);
}

void func_151601A4(s32 arg0, s32 arg1) {
    func_1505D024(arg0, 0x33, 0xC000, -1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18B1C0/func_151601D0.s")
