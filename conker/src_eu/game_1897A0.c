#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void *func_1515C2F0(s32 *arg0, s32 arg1, void *arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;

    arg0[4] = 10;
    temp_v0 = func_15147FF0(arg0, arg1 + 0x40, 0x10, 8, 8, 8, 0, 0, arg3, arg4, arg5);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(*(void **)(temp_v0 + 0x98), arg2, 0x3C);
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C388.s")
extern s32 (*D_8008B424[])(u8 *, u8 *);

s32 func_1515C534(u8 *arg0) {
    u8 *b;
    s32 i;
    u8 done;
    s16 t;

    b = *(u8 **)(arg0 + 0x98);
    done = 0;
    if (((s8 *)b)[0x39] != -1) {
        done = D_8008B424[((s8 *)b)[0x39]](arg0, b) == 0;
    }
    if (!done) {
        if (b[0x14] & 4) {
            t = *(s16 *)(arg0 + 0x1C);
            if (t < *(s16 *)(b + 0x2C)) {
            dummy: ; // fakematch: label splits the block (permuter)
                if (t * *(s16 *)(b + 0x2E) < b[0x1A]) {
                    b[0x1A] = t * *(s16 *)(b + 0x2E);
                }
            }
        }
        if ((b[0x14] & 8) && *(s16 *)(arg0 + 0x1C) < *(s16 *)(b + 0x30) && b[0x32] == 0) {
            for (i = D_800BE9E4; i != 0; i--) {
                *(f32 *)b *= *(f32 *)(b + 0x34);
            }
        }
    }
    if (done) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C6F4.s")
#ifdef NON_MATCHING
s32 func_1515CF9C(u8 *arg0, u8 *arg1) {
    s32 temp_v1;
    s8 temp_v0;
    u8 *temp_t1;

    temp_v0 = (*(s8 *)((u8 *)arg0 + 0x2C));
    if (temp_v0 < ((*(u8 *)((u8 *)arg0 + 0x25)) - 1)) {
        temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) (temp_v0 + 1);
        temp_t1 = temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x10);
        (*(s32 *)((u8 *)temp_t1 + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
        (*(s32 *)((u8 *)temp_t1 + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
        (*(s32 *)((u8 *)temp_t1 + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x18));
        (*(f32 *)((u8 *)((temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x10))) + 0xC)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
        (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
            (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
        }
    } else {
        (*(s8 *)((u8 *)arg1 + 0x39)) = -1;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515CF9C.s")
#endif
// s32 func_1515CF9C(void *arg0, void *arg1) {
//     s32 temp_v1;
//     s8 temp_v0;
//     void *temp_t1;
//
//     temp_v0 = arg0->unk2C;
//     if ((s32) temp_v0 < (arg0->unk25 - 1)) {
//         temp_v1 = arg0->unk94;
//         arg0->unk2C = (s8) (temp_v0 + 1);
//         temp_t1 = temp_v1 + (arg0->unk2E * 0x10);
//         temp_t1->unk0 = (s32) arg0->unk10;
//         temp_t1->unk4 = (s32) arg0->unk14;
//         temp_t1->unk8 = (s32) arg0->unk18;
//         (temp_v1 + (arg0->unk2E * 0x10))->unkC = (f32) arg1->unk8;
//         arg0->unk2E = (s8) (arg0->unk2E + 1);
//         if (arg0->unk25 == arg0->unk2E) {
//             arg0->unk2E = (u8)0;
//         }
//     } else {
//         arg1->unk39 = (u8)-1;
//     }
//     return 1;
// }

s32 func_1515D030(struct_eu_1897A0 *arg0, s32 arg1) {
    s32 ret = 1;

    if (arg0->unk2C >= 3) {
        arg0->unk2C--;
        arg0->unk2E--;
        if (arg0->unk2E < 0) {
            arg0->unk2E = arg0->unk25 - 1;
        }
    } else {
        ret = 0;
    }
    return ret;
}

struct260 *func_1515D088(s32 *arg0) {
    struct260 *temp_v0;
    struct {
        s32 *unk0;
        f32 unk4;
        u8 unk8;
    } sp30;

    sp30.unk8 = arg0[6];
    if (sp30.unk8 < 0 || sp30.unk8 >= 2) {
        return NULL;
    }
    sp30.unk0 = arg0;
    sp30.unk4 = 0.0f;
    temp_v0 = func_151491F4(300, -1, 0x11, 0, 0xD, 0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp30, 0xC);
    }
    return temp_v0;
}

// fat struct
#ifdef NON_MATCHING
void func_15143794(s16, s16, f32, void *);
s32 func_151530A8(s32 *, u8, s32);

void func_1515D130(u8 *arg0) {
    struct {
        s32 u5C;
        s32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        s16 u88;
        s16 u8A;
        s16 u8C;
        s16 u8E;
        s32 u90;
        s32 u94;
        s16 u98;
        s16 u9A;
        s16 u9C;
        s8 u9E;
        s8 u9F;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        u8 padB5[0x3];
        s32 uB8;
        s32 uBC;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s8 uC6;
        u8 padC7[0x1];
        f32 uC8;
        s8 uCC;
        s8 uCD;
    } sp;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s0 = ((*(u8 *)((u8 *)arg0 + 0x30)) << 6) + ((u8 *)&D_800A6880);
    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) + ((*(f32 *)((u8 *)temp_s0 + 0)) + (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 4)))));
    if ((*(f32 *)((u8 *)temp_s1 + 4)) > 1.0f) {
        do {
            sp.u5C = (*(s32 *)((u8 *)temp_s0 + 8));
            sp.u60 = (*(s32 *)((u8 *)temp_s0 + 0xC));
            sp.u70 = (*(f32 *)((u8 *)temp_s0 + 0x10));
            sp.u74 = (*(f32 *)((u8 *)temp_s0 + 0x14));
            sp.u78 = (*(f32 *)((u8 *)temp_s0 + 0x18));
            sp.u7C = (*(f32 *)((u8 *)temp_s0 + 0x1C));
            sp.u80 = (*(f32 *)((u8 *)temp_s0 + 0x20));
            sp.u88 = 0;
            sp.u8A = 0xFF;
            sp.u8C = -0x3F;
            sp.u8E = 0x50;
            sp.u84 = (*(f32 *)((u8 *)temp_s0 + 0x24));
            sp.u90 = (*(s32 *)((u8 *)temp_s0 + 0x28));
            sp.u94 = (*(s32 *)((u8 *)temp_s0 + 0x2C));
            sp.u98 = (*(s16 *)((u8 *)temp_s0 + 0x30));
            sp.u9C = 1;
            sp.u9E = 0xC;
            sp.u9F = 2;
            sp.uA0 = 3;
            sp.uA1 = 0xB4;
            sp.uA4 = 0x9B;
            sp.u9A = (*(s16 *)((u8 *)temp_s0 + 0x32));
            sp.uA2 = 0;
            sp.uA3 = 0;
            sp.uA5 = 0x32;
            sp.uA6 = 0x64;
            sp.uA7 = 0;
            sp.uA8 = 0x64;
            sp.uA9 = 0xFF;
            sp.uAA = 0xFF;
            sp.uAB = 0xFF;
            sp.uAC = 0xFF;
            sp.uAD = 0;
            sp.uAE = 0;
            sp.uAF = 0;
            sp.uB0 = 0;
            sp.uB1 = 0xFF;
            sp.uB2 = 0;
            sp.uB3 = 1;
            sp.uB4 = 0x24;
            sp.uB8 = 0x200005;
            sp.uBC = 0x60600;
            sp.uC0 = (*(s16 *)((u8 *)temp_s0 + 0x34));
            sp.uC2 = (*(s16 *)((u8 *)temp_s0 + 0x36));
            sp.uC6 = 0;
            sp.uC4 = (*(s16 *)((u8 *)temp_s0 + 0x38));
            sp.uCC = -1;
            sp.uCD = 0;
            sp.uC8 = (*(f32 *)((u8 *)temp_s0 + 0x3C));
            temp_s2 = func_150ADA20();
            func_15143794((s16) (temp_s2 & 0xFF), (s16) (0x40 - (func_150ADA20() & 0x7F)), (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 6)), &sp.u64);
            sp.u64 += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 0));
            sp.u68 += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 2));
            sp.u6C += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 0))) + 4));
            func_151530A8(&sp.u5C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
            (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 4)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D130.s")
#endif