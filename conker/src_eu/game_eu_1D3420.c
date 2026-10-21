#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151A6618(u8 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A5C10.s")

void func_151A62DC(u16);
void func_151A625C(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C); // fakematch: re-load of the field (no andi)
  if ((*new_var) != 0)
  {
    func_151A62DC(*new_var);
  }
  func_1514933C(p);
}

void func_151A62DC(u16);
void func_151A629C(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C); // fakematch: re-load of the field (no andi)
  if ((*new_var) != 0)
  {
    func_151A62DC(*new_var);
  }
  func_15149368(p);
}

void func_151A62DC(u16 arg0) {
    func_100111C8(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6308.s")

#ifdef NON_MATCHING
void func_151A6520(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *sp2C;
    s32 temp_a1;
    s32 var_a0;
    s32 var_v0;
    u8 *temp_a0;
    u8 *var_v1;
    u8 temp_v1;
    u8 *temp_v0;

    if ((arg2 & 0xFF) == 0x35) {
        temp_a1 = (*(s32 *)((u8 *)arg1 + 0));
        var_v0 = 0;
        var_a0 = 0;
        if (temp_a1 > 0) {
            var_v1 = (*(u8 **)((u8 *)arg1 + 4));
loop_3:
            if ((*(u8 *)((u8 *)arg0 + 0x2C)) == *var_v1) {
                var_a0 = 1;
            } else {
                var_v0 += 1;
                var_v1 += 1;
            }
            if ((var_v0 < temp_a1) && (var_a0 == 0)) {
                goto loop_3;
            }
        }
        if (var_a0 != 0) {
            temp_v0 = arg0 + 0x28;
            temp_a0 = (*(u8 **)((u8 *)temp_v0 + 0));
            if ((*(u8 *)((u8 *)temp_a0 + 0x14)) == 1) {
                temp_v1 = (*(u8 *)((u8 *)temp_v0 + 0xC));
                sp2C = temp_v0;
                func_151A6618(temp_a0, (*(s32 *)((u8 *)temp_v0 + 8)), temp_v1 & 1, temp_v1 & 2, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v0 + 0))) + 0x14)) = 0;
                (*(s32 *)((u8 *)temp_v0 + 0x10)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6520.s")
#endif
s32 func_1516284C(void *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *memcpy(void *, const void *, s32);
extern f32 D_800A9178;
extern f32 D_800A917C;
typedef struct { f32 x, y, z; } V3_6618;
typedef struct {
    u8 u0;
    s8 u1;
    s16 u2;
    s16 u4;
    s16 pad6;
    s32 u8;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    V3_6618 u1C;
    f32 u28[3];
    f32 u34[3];
    s32 u40;
    u8 u44;
    u8 u45;
    s8 u46;
    s8 u47;
    s32 u48;
    u8 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
} Blk58_6618;
typedef struct {
    u8 *p;
    f32 u4;
    f32 u8;
    f32 uC;
    s32 u10;
    u8 u14;
    u8 u15;
    u8 u16;
    u8 u17;
    f32 u18;
} Tmp_6618;
typedef struct { u8 u0; u8 u1; s16 u2; u8 u4; } Blk2_6618;

void func_151A6618(u8 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    Blk58_6618 blk;
    Tmp_6618 tmp;
    u8 *dst;
    u8 *temp_v0;

    tmp.p = arg0;
    tmp.u4 = 0.0f;
    tmp.u8 = (func_150ADA68() * 80.0f) + -380.0f;
    tmp.uC = (func_150ADA68() * D_800A9178) + D_800A917C;
    tmp.u10 = 0;
    tmp.u14 = func_150ADA20() & 0xFF;
    tmp.u15 = (func_150ADA20() & 3) + 4;
    tmp.u16 = 0xFF;
    tmp.u18 = 0.0f;
    tmp.u17 = arg3;
    blk.u0 = 0x6B;
    blk.u1 = 0xA;
    blk.u2 = 0x4C03;
    blk.u4 = 0xC8;
    blk.u8 = 0;
    blk.uC = 0;
    blk.u10[0] = 0xFF;
    blk.u10[1] = 0xFF;
    blk.u10[2] = 0xFF;
    blk.u10[3] = 0xFF;
    blk.u14 = *(s16 *)(arg0 + 6);
    blk.u18 = *(s16 *)(arg0 + 8);
    blk.u1C.x = *(s16 *)(arg0 + 0);
    blk.u1C.y = *(s16 *)(arg0 + 2);
    blk.u1C.z = *(s16 *)(arg0 + 4);
    blk.u28[0] = 0.0f;
    blk.u28[1] = 0.0f;
    blk.u28[2] = 0.0f;
    blk.u34[0] = 1.0f;
    blk.u34[1] = 1.0f;
    blk.u34[2] = 1.0f;
    blk.u40 = 0x01EC0009;
    blk.u44 = 0xFF;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 0;
    blk.u48 = arg1;
    blk.u4C = 0xFF;
    temp_v0 = func_1513D2F0(&blk, (s32)&D_800A4AA0, 0, 0x28, 0, 0x20, 0, 0, 0, 0x1C, arg4, arg5);
    if (temp_v0 != NULL) {
        dst = temp_v0 + 0x110;
        memcpy(dst, &tmp, 0x1C);
        if (arg2 != 0) {
            Blk2_6618 b2;
            s32 pos[3];

            pos[0] = *(s16 *)(arg0 + 0);
            pos[1] = (*(s16 *)(arg0 + 8) >> 1) + *(s16 *)(arg0 + 2);
            pos[2] = *(s16 *)(arg0 + 4);
            b2.u0 = 2;
            b2.u1 = 2;
            b2.u2 = 0x12C;
            b2.u4 = 6;
            *(s32 *)(dst + 0x10) = func_1516284C(&b2, pos, 0xFF, 0x79, 0, 0xFF, 0, 0, 0xE, arg4, arg5);
        }
    }
    if (arg2 != 0) {
        func_1000FA64(0x1AA, *(s16 *)(arg0 + 0), *(s16 *)(arg0 + 2), *(s16 *)(arg0 + 4), 0x4000, 0x3E8, 0x2EE, (s32)func_1000EF40, arg0, 0, 8, func_150ADA20() & 0x300);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6BB0.s")

void func_1000FD38(s32 (*)(struct57 *, struct57 *, s32 *, s32, s32, s32, u16 *), u8 *, s32, u8 *);

void func_151A7068(u8 *arg0) {
    struct102 *temp_a0;

    (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x110))) + 0x14)) = 1;
    func_1000FD38(func_1000EF40, (*(u8 **)((u8 *)arg0 + 0x110)), 0, arg0);
    temp_a0 = (*(struct102 **)((u8 *)arg0 + 0x120));
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
}

void func_151A70C0(struct210 * arg0) {
    func_151A7068(arg0);
    func_1513CA6C(arg0);
}

void func_151A70EC(struct210 * arg0) {
    func_151A7068(arg0);
    func_1513CAA0(arg0);
}

u8 *func_151A7188(s32);
s32 func_1505D024();
void func_151A7118(u8 *arg0, s32 arg1) {
    s32 pad; // fakematch: unused local moves v to sp18
    struct127 *v = NULL;
    u8 *t;
    s32 a3;
    t = func_151A7188(arg1);
    if (t != NULL) {
        v = *(struct127 **)(t + 0x38);
    }
    if (v != NULL) {
        a3 = v - D_800CC2D0;
    } else {
        a3 = -1;
    }
    func_1505D024(arg0, 0x60034, *(u16 *)(arg0 + 0x7A), a3);
}

u8 *func_151A7188(s32 arg0) {
    u8 i;
    u8 j;
    struct_eu_node *p;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (p = D_800DD280[j][(&D_800A5770)[i]]; p != NULL; p = p->next) {
                if ((*(u8 *)((u8 *)p + 0x13) == 0x2C) && (arg0 == *(s32 *)((u8 *)p + 0x28))) {
                    return (u8 *)p;
                }
            next: ; // fakematch: label at the end of the inner loop body moves the j/i increments into the exit block
            }
        }
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A7240.s")
