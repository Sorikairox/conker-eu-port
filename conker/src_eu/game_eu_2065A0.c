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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D8E18.s")

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
