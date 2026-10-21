#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_15164CF0(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *p;
    struct127 *obj;
    struct108 *e;

    e = &D_800DBFF0[arg0[6]];
    obj = e->unk3D0;
    if (obj != NULL && obj->unk31C != NULL && obj->unk31C->unk198 != 0) {
        return NULL;
    }
    p = func_15167A68(0x39, arg3, arg1 + 0x68, 1, arg2, 1);
    if (p == NULL) {
        return NULL;
    }
    memcpy(p + 0x10, arg0, 0x38);
    p[0x60] = 1;
    p[0x61] = 1;
    p[0x62] = 1;
    p[0x63] = 1;
    p[0x64] = 1;
    p[0x65] = 1;
    *(f32 *)(p + 0x48) = 0.0f;
    *(f32 *)(p + 0x4C) = 0.0f;
    *(f32 *)(p + 0x50) = 0.0f;
    *(f32 *)(p + 0x54) = 0.0f;
    *(f32 *)(p + 0x58) = 0.0f;
    *(f32 *)(p + 0x5C) = 0.0f;
    return p;
}

void func_15164DF8(u8 *arg0) {
    arg0[0x10] |= 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15164E0C.s")

void func_15165454(void) {
    bzero(D_800DD210, 0x60);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_1516547C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15165B98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15165E4C.s")

f32 func_15166120(void *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4);

void func_151660F0(u8 *arg0) {
    func_15166120(arg0, arg0 + 0x108, *(s32 *)(arg0 + 0x114), *(s32 *)(arg0 + 0x118), *(f32 *)(arg0 + 0x11C));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15166120.s")
