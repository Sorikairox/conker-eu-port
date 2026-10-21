#include <ultra64.h>
#include "functions.h"
#include "variables.h"
void func_151D91B0(u8 *arg0, f32 *arg1);


extern u8 D_800BED64[];
s32 func_151D8D90(u8 arg0) {
    u8 i;
    u8 t;
    for (i = 0; i < 4; i++) {
        if (arg0 & (1 << i)) {
            t = D_800843F0[i];
            if (t >= 4) {
                return 0;
            }
            if (D_800BED64[t] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

#ifdef NON_MATCHING
s32 func_1501BFF0(s32, u8);
s32 func_1517F470(s32);
s32 func_15182238(s32);
s32 memcpy(u8 *, structEU_151D8E18 *, s32);
extern u8 D_800BEEE2;
extern u8 D_800BEEE3;

s32 func_151D8E18(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_v1;
    u8 *temp_v0;

    if (D_800E0B94 != 0) {
        return 0;
    }
    if (func_151D8D90(arg0->unk5) == 0) {
        return 0;
    }
    if ((D_800BEAC0 != 0) || (D_800BEAC1 != 0) || (D_800BEEE2 != 0) || (D_800BEEE3 != 0)) {
        return 0;
    }
    var_s1 = 0;
    var_s0 = 0;
    if (D_80082FA0 >= 0) {
loop_10:
        if ((arg0->unk5 & (1 << var_s0)) && ((func_15182238(var_s0) == 0) || (func_1517F470(var_s0) != 0))) {
            return 0;
        }
        var_s0 = (var_s1 + 1) & 0xFF;
        var_s1 = var_s0;
        if (D_80082FA0 < var_s0) {
            goto block_15;
        }
        goto loop_10;
    }
block_15:
    temp_v0 = func_15167A68(0x3F, arg3, arg1 + 0x18, 1, (u8) (s32) arg2, 1U);
    if (temp_v0 == NULL) {
        return 0;
    }
    memcpy(temp_v0 + 0xE, arg0, 8);
    var_s0_2 = 0;
    var_v1 = 0;
    do {
        if ((*(u8 *)((u8 *)temp_v0 + 0x13)) & (1 << var_v1)) {
            func_1501BFF0(var_s0_2 & 0xFF, arg0->unk4);
        }
        var_v1 = (var_s0_2 + 1) & 0xFF;
        var_s0_2 = var_v1;
    } while (var_v1 < 4);
    (*(u8 *)((u8 *)temp_v0 + 0x16)) = (u8) arg0->unk4;
    return (s32) temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D8E18.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_eu_151D8FD4.s")

void func_1501C15C(u8);
void func_151D90D4(u8 *arg0) {
    u8 i;
    for (i = 0; i < 4; i++) {
        if (arg0[0x13] & (1 << i)) {
            func_1501C15C(i);
        }
    }
}

void func_151D9138(void *arg0) {
    func_151D90D4(arg0);
    func_15169804(arg0);
}

void func_151D9164(void *arg0) {
    func_151D90D4(arg0);
    func_15169824(arg0);
}

void func_151D9190(u8 *arg0) {
    func_151D91B0(arg0, (f32 *)(arg0 + 0x18));
}

f32 func_15143E64(f32 *, f32 *);

void func_151D91B0(u8 *arg0, f32 *arg1) {
    f32 *p;
    f32 d[3];
    f32 dist;
    f32 lo;
    f32 v;

    p = func_15144B34(((u8 *)arg1)[0x18]);
    d[0] = arg1[0] - p[0];
    d[1] = arg1[1] - p[1];
    d[2] = arg1[2] - p[2];
    dist = func_15143E64(d, arg1);
    lo = arg1[3];
    if (dist < lo) {
        v = 1.0f;
    } else if ((lo + arg1[4]) < (0, dist)) { // fakematch: comma orders the add.s
        v = 0.0f;
    } else {
        v = 1.0f - (arg1[5] * (0, dist - lo)); // fakematch: comma swaps the f-regs
    }
    arg0[0x12] = v * 8.0f;
}

void func_151D930C(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x58) {
        func_1516972C(arg0);
    } else if (arg2 == 0x47) {
        func_1516972C(arg0);
    }
}

void func_151D9364(s32 arg0, u8 arg1) {
    func_15169260(&D_800AB6E0, 1, arg0, arg1);
}

extern s8 D_eu_800E0E30;

void func_151D9398(void) {
    D_eu_800E0E30 = 1;
    func_151D9364(0, 0x58U);
}
