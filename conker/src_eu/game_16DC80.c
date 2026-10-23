#include <ultra64.h>

#ifdef NON_MATCHING
/* P132: functions.h:772 declares func_1513D524 void; it returns the new record (port-b P128, game_169510.c). Hide
 * the old prototype until the functions.h fix merges (as game_eu_1772D0.c does). */
#define func_1513D524 func_1513D524_void_proto
#endif
#include "functions.h"
#ifdef NON_MATCHING
#undef func_1513D524
struct210 *func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);
#endif
#include "variables.h"


#ifdef NON_MATCHING
// particle_emitter_spawn: spawns a particle record from the spawn block (type byte 1 = 3, flags 0x40400000 set
// first) through func_1513D524, copies the emitter block (emitSize bytes) to rec + 0x110, clears its word +0x44,
// stores arg7 at +0x59 and counts the record in D_800DCE20. Returns the record or NULL. func_150113E0 passes
// (emit, 0x7C, spawn, 0, 0x20, 0, 0, -1, 0xFF, 1).
struct210 *func_151407D0(void *emit, s32 emitSize, u8 *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                         s32 arg9) {
    struct210 *rec;
    u8 *e;

    spawn[1] = 3;
    *(u32 *) (spawn + 0x40) |= 0x40400000;
    rec = func_1513D524((s32) spawn, arg3, arg4, arg5, 1, arg6, emitSize, arg8, arg9);
    if (rec == NULL) {
        return NULL;
    }
    e = (u8 *) rec + 0x110;
    memcpy(e, emit, emitSize);
    *(s32 *) (e + 0x44) = 0;
    e[0x59] = arg7;
    if (rec != NULL) {
        D_800DCE20++;
    }
    return rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151407D0.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151408A4.s")

void func_151411A4(struct210 *arg0) {
    func_1513CA6C(arg0);
}

void func_151411C4(struct210 *arg0) {
    func_1513CAA0(arg0);
}

void func_151411E4(structEU_16DC80 *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        func_1517E6A4(*(f32 **)((u8 *)arg0 + 0x154), arg0);
    }
    D_800DCE20 -= 1;
    D_8008A33C[arg0->unk168](arg0);
}

void func_15141250(structEU_16DC80 *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        func_1517E6A4(*(f32 **)((u8 *)arg0 + 0x154), arg0);
    }
    D_800DCE20 -= 1;
    D_8008A384[arg0->unk168](arg0);
}

#ifdef NON_MATCHING
/* Per-frame grid-cell lookup for the scene nodes (P13, hand C). For the two node tables D_800DD280[2][104]
 * and the four list heads named by the index table D_800A5168[0..3], walk each list (next at 0x08). A node with
 * flag 0x2000 (word 0x58) clears its four per-player cell values (u16 at 0x15C); with flag 0x10 too, each
 * player's (x, y) cell (s32 at 0x134 / 0x144) inside the D_800BE620 x D_800BE624 grid looks up the u16 grid
 * D_800BEDE4[y][x]; out of range gives 0x7FFF. */
void func_151412BC(void) {
    u8 *row;
    u8 *node;
    u8 k;
    u8 i;
    s32 x;
    s32 y;
    s32 flags;

    for (row = (u8 *)D_800DD280; row != (u8 *)&D_800DD5C0; row += 0x1A0) {
        for (k = 0; k < 4; k++) {
            node = ((u8 **)row)[((s32 *)&D_800A5168)[k]];
            for (; node != NULL; node = *(u8 **)(node + 0x8)) {
                flags = *(s32 *)(node + 0x58);
                if (!(flags & 0x2000)) {
                    continue;
                }
                *(s16 *)(node + 0x162) = 0;
                *(s16 *)(node + 0x160) = 0;
                *(s16 *)(node + 0x15E) = 0;
                *(s16 *)(node + 0x15C) = 0;
                if (!(flags & 0x10)) {
                    continue;
                }
                for (i = 0; i <= D_80082FA0; i++) {
                    x = *(s32 *)(node + 0x134 + i * 4);
                    y = *(s32 *)(node + 0x144 + i * 4);
                    if (x < 0 || x >= D_800BE620 || y < 0 || y >= D_800BE624) {
                        *(u16 *)(node + 0x15C + i * 2) = 0x7FFF;
                    } else {
                        *(u16 *)(node + 0x15C + i * 2) =
                            *(u16 *)((u8 *)D_800BEDE4 + (y * D_800BE620) * 2 + x * 2);
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151412BC.s")
#endif
s32 func_1514143C(u8 *arg0)
{
  u8 *p;
  if (*((s32 *) (arg0 + 0x154)))
  {
    p = arg0 + 0x111;
 if (0) { } // fakematch: empty if, scheduling
    p--;  // fakematch: dead addiu kept (p = arg0 + K+1; p--;)
    (*((f32 **) (p + 0x44)))[0] = *((f32 *) (arg0 + 0x34));
    (*((f32 **) (p + 0x44)))[1] = *((f32 *) (arg0 + 0x38));
    (*((f32 **) (p + 0x44)))[2] = *((f32 *) (arg0 + 0x3C));
  }
}

#ifdef NON_MATCHING
s32 func_15141478(u8 *arg0) {
    u8 *sp24;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    u8 *temp_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    (*(f32 *)((u8 *)arg0 + 0x180)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x180)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x180)) < 0.0f) {
        temp_v1 = arg0 + 0x170;
        (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) (func_150ADA68() * (*(f32 *)((u8 *)temp_v1 + 0x14)));
        sp24 = temp_v1;
        if (func_150ADA20() & 3) {
            sp24 = temp_v1;
            temp_f2 = (*(f32 *)((u8 *)temp_v1 + 4));
            (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((func_150ADA68() * ((*(f32 *)((u8 *)temp_v1 + 0)) - temp_f2)) + temp_f2);
        } else {
            sp24 = temp_v1;
            temp_f2_2 = (*(f32 *)((u8 *)temp_v1 + 0));
            (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((func_150ADA68() * ((*(f32 *)((u8 *)temp_v1 + 8)) - temp_f2_2)) + temp_f2_2);
        }
    }
    temp_a0 = arg0 + 0x110;
    temp_v1_2 = arg0 + 0x170;
    temp_f0 = (*(f32 *)((u8 *)temp_a0 + 0x48));
    (*(f32 *)((u8 *)temp_a0 + 0x48)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_v1_2 + 0xC)) - temp_f0) * (*(f32 *)((u8 *)temp_v1_2 + 0x18))));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141478.s")
#endif
s32 func_15141564(structEU_16DC80 *arg0) {
    struct { f32 unk0; f32 unk4; f32 unk8; f32 unkC; } *temp = &arg0->unk170.f;
    f32 s;
    s32 pad;

    s = sinf(temp->unk8);
    arg0->unk158 = temp->unk0 + (temp->unk4 * s);
    temp->unk8 += temp->unkC * D_800BE9A4;
    temp->unk8 = func_15144B68(temp->unk8);
    return 1;
}

typedef struct {
    f32 v0;
    f32 base;
    f32 amp;
    f32 t;
    f32 t0;
    f32 t1;
    f32 t2;
    f32 period;
    f32 scale;
} Env15D4;

s32 func_151415D4(u8 *arg0) {
    Env15D4 *e = (Env15D4 *)(arg0 + 0x170);
    f32 period;
    f32 f;

    if (e->t < e->t0) {
        *(f32 *)(arg0 + 0x158) = e->base;
    } else if (e->t < e->t1) {
        f = (e->t - e->t0) * e->scale;
        *(f32 *)(arg0 + 0x158) = e->base + e->amp * f;
    dummy: // fakematch: the label keeps the store out of the branch delay slot
        ;
    } else if (e->t < e->t2) {
        *(f32 *)(arg0 + 0x158) = e->v0;
    } else {
        f = 1.0f - (e->t - e->t2) * e->scale;
        *(f32 *)(arg0 + 0x158) = e->base + e->amp * f;
    }
    period = e->period;
    e->t += D_800BE9A4;
    while (period < e->t) {
        e->t -= period;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151416E8.s")

// ???
void func_151417C4(u8 arg0, u8 arg1) {
    u8 sp24[4];
    s32 sp1C[2] = {0x1C, 0x56};

    sp24[0] = arg0;
    func_15169260(sp1C, 2, (s32)sp24, arg1);
}

s32 func_15141818(s32 arg0, s32 arg1) {
    return 0;
}

void func_1514182C(structEU_16DC80 *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    f32 z;
    f32 y;
    f32 x;
    f32 mf[4][4];

    func_150A8050(mf, arg4, 0.0f, arg5);
    mf[3][0] = ((f32 *)arg1)[0];
    mf[3][1] = ((f32 *)arg1)[1];
    mf[3][2] = ((f32 *)arg1)[2];
    func_150A7E40(mf, 0.0f, *(f32 *)&arg2, 0.0f, &arg0->unk34, &arg0->unk38, &arg0->unk3C);
    x = *(f32 *)&arg3 * (arg0->unk34 - ((f32 *)arg1)[0]);
    y = *(f32 *)&arg3 * (arg0->unk38 - ((f32 *)arg1)[1]);
    z = *(f32 *)&arg3 * (arg0->unk3C - ((f32 *)arg1)[2]);
    *(f32 *)((u8 *)arg0 + 0x40) = arg0->unk34 + x * 500.0f;
    *(f32 *)((u8 *)arg0 + 0x44) = arg0->unk38 + y * 500.0f;
    *(f32 *)((u8 *)arg0 + 0x48) = arg0->unk3C + z * 500.0f;
}
// f32 func_1514182C(void *arg0, void *arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     ? sp34;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f2;
//
//     func_150A8050(&sp34, arg4, 0, arg5);
//     sp64 = arg1->unk0;
//     sp68 = arg1->unk4;
//     sp6C = arg1->unk8;
//     func_150A7960(&sp34, 0, arg2, 0, arg0 + 0x34, arg0 + 0x38, arg0 + 0x3C);
//     temp_f0 = arg0->unk34;
//     temp_f2 = arg0->unk38;
//     temp_f12 = arg0->unk3C;
//     arg0->unk40 = (f32) (temp_f0 + ((temp_f0 - arg1->unk0) * arg3 * 500.0f));
//     arg0->unk44 = (f32) (temp_f2 + ((temp_f2 - arg1->unk4) * arg3 * 500.0f));
//     arg0->unk48 = (f32) (temp_f12 + ((temp_f12 - arg1->unk8) * arg3 * 500.0f));
//     return temp_f0;
// }

s32 func_15141928(structEU_16DC80 *arg0) {
    f32 *temp_v0 = arg0->unk170.i.unk8;

    func_1514182C(arg0, arg0->unk170.i.unkC, arg0->unk170.i.unk0, arg0->unk170.i.unk4, temp_v0[0], temp_v0[2]);
    return 1;
}
// s32 func_15141928(void *arg0) {
//     void *temp_v0 = arg0->unk178;
//     func_1514182C(arg0, arg0->unk17C, arg0->unk170, arg0->unk174, temp_v0->unk0, temp_v0->unk8);
//     return 1;
// }
