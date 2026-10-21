#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15147ECC(u8 *arg0);


extern s32 (*D_8008A5A0[])(u8 *);
extern s32 (*D_8008A5DC[])(u8 *);
extern s32 (*D_8008A624[])(u8 *);
void func_15147CB0(u8 *arg0) {
    s32 pad; // fakematch: moves the byte spill slot
    s8 done = 0;
    s8 w;

    if (*(u16 *)(arg0 + 0x1E) & 1) {
        *(s16 *)(arg0 + 0x1C) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x1C) < 0) {
            done = 1;
        }
    }
    if (arg0[0x2F] >= 15) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    if (arg0[0x2F] != 0 && !done) {
        if (!D_8008A5A0[arg0[0x2F]](arg0)) {
            done = 1;
        }
    }
    if (arg0[0x30] >= 18) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    if (arg0[0x30] != 0 && !done) {
        if (!D_8008A5DC[arg0[0x30]](arg0)) {
            done = 1;
        }
    }
    if (*(u16 *)(arg0 + 0x1E) & 0x10) {
        w = *(s8 *)(arg0 + 0x24);
        if (w < -1 || w >= 8) {
            func_1516972C((struct102 *)arg0);
            return;
        }
        if (w != -1 && !done) {
            if (!D_8008A624[w](arg0)) {
                done = 1;
            }
        }
    }
    if (done) {
        func_1516972C((struct102 *)arg0);
    }
}

void func_15147E40(u8 *arg0) {
    func_151D5E30(arg0 + 0x84, arg0);
}

void func_15147E64(void *arg0) {
    func_15147E40(arg0);
    func_15147ECC(arg0);
    func_15169804(arg0);
}

void func_15147E98(void *arg0) {
    func_15147E40(arg0);
    func_15147ECC(arg0);
    func_15169824(arg0);
}

void func_15147ECC(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0x3C))[i]) {
            func_100043B4(((s32 *)(arg0 + 0x3C))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0x4C) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0x4C), 4);
    }
}

void func_15147F50(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
    D_8008A690[idx]();
}

void func_15147FA0(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
    D_8008A6E0[idx]();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1754C0/func_15147FF0.s")

extern s32 (*D_8008A644[])(u8 *, s32, s16);
s32 func_151462C8(s32, u8 *, s32, s32, s32, s16, u8 *, s32, s32);

s32 func_151481BC(s32 arg0, u8 *arg1, s16 arg2) {

    arg0 = func_151462C8(arg0, arg1 + 0x34, 0, 0, 0, arg2, arg1 + 0x54, 2, (*(u16 *)(arg1 + 0x1E) & 0x20) ? *(s32 *)(arg1 + 0x28) : 0);
    if (arg1[0x31] >= 0x13) {
        func_1516972C((struct102 *)arg1);
        return arg0;
    }
    if (arg1[0x31] != 0) {
        return D_8008A644[arg1[0x31]](arg1, arg0, arg2);
    }
    return arg0;
}

void func_1514828C(u8 *arg0, s32 arg1, u8 arg2) {
    void (*func)(void *, s32, u8) = D_8008A730[*(s32 *)(arg0 + 0x20)];

    if (func != NULL) {
        func(arg0, arg1, arg2);
    }
}

void func_151482D4(s32 arg0, u8 arg1) {
    func_15169260(D_800A5B40, 2, arg0, arg1);
}
