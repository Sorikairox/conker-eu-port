#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#define F(o) (*(f32 *)(p + (o)))
void func_15189E70(void *arg0, u8 arg1) {
    u8 *p;
    s32 flag;

    p = func_15167A68(0x1A, 1, 0x78, 1, 0xFF, 1);
    if (p != NULL) {
        memcpy(p + 0x10, arg0, 0x50);
        func_1510F800(0);
        *(s32 *)(p + 0x6C) = func_1510FD20((s32)(F(0x24) * 0.5f + F(0x18)), (s32)(F(0x2C) * 0.5f + F(0x20)));
        if (arg1 != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        p[0x70] = flag;
        *(s16 *)(p + 0x60) = 0;
        F(0x64) = 0.0f;
        if (F(0x28) < 0.0f) {
            F(0x68) = F(0x28) + F(0x1C);
        } else {
            F(0x68) = F(0x1C);
        }
    }
}
#undef F

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7680/func_15189F70.s")

typedef struct { f32 x, y, z; s32 a, b; } Node14;
u8 func_151D8E20(void);
extern f64 D_800A7788;
extern f32 D_800A7790;

s32 func_1518A42C(u8 *arg0) {
    s32 pad[2];
    u8 *obj;
    u8 *tbl;
    f32 pos[3];

    tbl = *(u8 **)(arg0 + 0x94);
    obj = *(u8 **)(arg0 + 0x98);
    if (*(f32 *)(tbl + *(s8 *)(arg0 + 0x2D) * 0x14 + 4) < *(f32 *)(obj + 0x48)) {
        if (func_150ADA68() < D_800A7788) {
            pos[0] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
            pos[1] = *(f32 *)(obj + 0x48);
            pos[2] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
            func_151DBCBC(func_151D8E20(), *(f32 *)(obj + 0) * 6.0f, *(u8 *)(obj + 0x1B), 0, pos, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
        }
        *(s8 *)(obj + 0x20) = 4;
        *(f32 *)(obj + 0x48) = D_800A7790;
    }
    return 1;
}

s32 func_1518A540(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 1;
}
