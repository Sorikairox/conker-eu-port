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
        node_destroy((struct102 *)arg0);
        return;
    }
    if (arg0[0x2F] != 0 && !done) {
        if (!D_8008A5A0[arg0[0x2F]](arg0)) {
            done = 1;
        }
    }
    if (arg0[0x30] >= 18) {
        node_destroy((struct102 *)arg0);
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
            node_destroy((struct102 *)arg0);
            return;
        }
        if (w != -1 && !done) {
            if (!D_8008A624[w](arg0)) {
                done = 1;
            }
        }
    }
    if (done) {
        node_destroy((struct102 *)arg0);
    }
}

void func_15147E40(u8 *arg0) {
    func_151D5E30(arg0 + 0x84, arg0);
}

void func_15147E64(void *arg0) {
    func_15147E40(arg0);
    func_15147ECC(arg0);
    node_retire(arg0);
}

void func_15147E98(void *arg0) {
    func_15147E40(arg0);
    func_15147ECC(arg0);
    node_unlink_free(arg0);
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

// record_free_dispatch: calls the record kind's (+0x20, 0..19, else 0) free handler D_8008A690 with the record.
void func_15147F50(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
#ifdef NON_MATCHING
    /* P173: the handlers take the record (the asm keeps a0 = arg0 at the jalr; browser P171: func_15147E64 freed
     * garbage at rec + 0x84 when it got no argument) */
    ((void (*)(u8 *)) D_8008A690[idx])(arg0);
#else
    D_8008A690[idx]();
#endif
}

// record_dispatch_b: calls the record kind's (+0x20, 0..19, else 0) D_8008A6E0 handler with the record.
void func_15147FA0(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
#ifdef NON_MATCHING
    /* P173: the handlers take the record (the asm keeps a0 = arg0 at the jalr; browser P171: func_15147E64 freed
     * garbage at rec + 0x84 when it got no argument) */
    ((void (*)(u8 *)) D_8008A6E0[idx])(arg0);
#else
    D_8008A6E0[idx]();
#endif
}

#ifdef NON_MATCHING
void * func_1515D9B0(void);
s32 func_1515D9F0(s32);
s32 memcpy(u8 *, u8 *, s32);

void * func_15147FF0(void * arg0_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, s32 argA) {
    u8 * arg0 = (u8 *) arg0_p;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_s0;
    u8 *var_s0_2;

    var_v0 = 0x22;
    if ((*(u16 *)((u8 *)arg0 + 0xE)) & 0x40) {
        var_v0 = 0x4D;
    }
    temp_v0 = node_alloc(var_v0, argA, arg1 + ((*(u8 *)((u8 *)arg0 + 0x15)) * arg2) + 0xA0, 1, (u8) (s32) arg9, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_v0_2 = temp_v0 + 0xA0;
    (*(u8 **)((u8 *)temp_v0 + 0x98)) = temp_v0_2;
    (*(u8 **)((u8 *)temp_v0 + 0x94)) = (u8 *) (temp_v0_2 + arg1);
    memcpy(temp_v0 + 0x10, arg0, 0x1C);
    (*(s8 *)((u8 *)temp_v0 + 0x2C)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2E)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2F)) = (s8) arg3;
    (*(s8 *)((u8 *)temp_v0 + 0x30)) = (s8) arg4;
    (*(s8 *)((u8 *)temp_v0 + 0x31)) = (s8) arg5;
    if (arg8 != 0) {
        *(struct_eu_bytes24 *)(temp_v0 + 0x60) = *(struct_eu_bytes24 *)(arg8);
    } else {
        (*(s8 *)((u8 *)temp_v0 + 0x7C)) = 0;
    }
    var_s1 = 0;
    var_s0 = temp_v0;
    (*(s32 *)((u8 *)temp_v0 + 0x34)) = arg6;
    (*(s8 *)((u8 *)temp_v0 + 0x38)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x50)) = arg7;
    do {
        var_s1 += 1;
        var_s0 += 4;
        (*(s32 *)((u8 *)var_s0 + 0x38)) = 0;
    } while (var_s1 < 4);
    (*(s32 *)((u8 *)temp_v0 + 0x4C)) = 0;
    if (arg6 != 0) {
        var_s1_2 = 0;
        var_s0_2 = temp_v0;
        if (D_80082FA0 >= 0) {
            do {
                (*(s32 *)((u8 *)var_s0_2 + 0x3C)) = func_1515D9F0(arg6);
                var_s1_2 += 1;
                var_s0_2 += 4;
            } while (D_80082FA0 >= var_s1_2);
        }
        (*(s32 *)((u8 *)temp_v0 + 0x4C)) = func_1515D9B0();
    }
    (*(f32 *)((u8 *)temp_v0 + 0x54)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x58)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x5C)) = 0.0f;
    bzero(temp_v0 + 0x84, 0x10);
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1754C0/func_15147FF0.s")
#endif
extern s32 (*D_8008A644[])(u8 *, s32, s16);
s32 func_151462C8(s32, u8 *, s32, s32, s32, s16, u8 *, s32, s32);

s32 func_151481BC(s32 arg0, u8 *arg1, s16 arg2) {

    arg0 = func_151462C8(arg0, arg1 + 0x34, 0, 0, 0, arg2, arg1 + 0x54, 2, (*(u16 *)(arg1 + 0x1E) & 0x20) ? *(s32 *)(arg1 + 0x28) : 0);
    if (arg1[0x31] >= 0x13) {
        node_destroy((struct102 *)arg1);
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
    node_broadcast_types(D_800A5B40, 2, arg0, arg1);
}
