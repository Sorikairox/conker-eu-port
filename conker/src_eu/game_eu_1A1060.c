#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8 c[4];
    s16 v[4];
    u16 a;
    u16 b;
} Info3850;
extern Info3850 D_8008D010;
extern s8 D_800DD710;
s32 func_15173954(s32, s32, s32, s32, s32);
void func_15173850(s32 arg0) {
    if (*(s16 *)((u8 *)D_800B0DF0 + 0x40) == *(s16 *)((u8 *)D_800B0DF0 + 0x3C) && *(s16 *)((u8 *)D_800B0DF0 + 0x3C) == 0) {
        *(s16 *)((u8 *)D_800B0DF0 + 0x40) = 100;
    }
    D_8008D010.c[0] = D_800B0DF0->pad2A[0x18];
    D_8008D010.c[1] = D_800B0DF0->pad2A[0x19];
    D_8008D010.c[2] = D_800B0DF0->pad2A[0x1A];
    D_8008D010.c[3] = D_800B0DF0->pad2A[0x1B];
    D_8008D010.v[0] = *(s16 *)((u8 *)D_800B0DF0 + 0x3A);
    D_8008D010.v[1] = *(s16 *)((u8 *)D_800B0DF0 + 0x3C);
    D_8008D010.v[2] = *(s16 *)((u8 *)D_800B0DF0 + 0x3E);
    D_8008D010.v[3] = *(s16 *)((u8 *)D_800B0DF0 + 0x40);
    D_8008D010.a = *(u16 *)((u8 *)D_800B0DF0 + 2);
    D_8008D010.b = *(u16 *)((u8 *)D_800B0DF0 + 0);
    if ((s8)D_800B0DF0->pad2A[0x1C] != -1) {
        D_800DD710 = 1;
        func_15173954((s8)D_800B0DF0->pad2A[0x1C], (s8)D_800B0DF0->pad2A[0x1C], arg0, 0, -1);
    } else {
        D_800DD710 = 0;
        func_15173954(0, 0, arg0, 0, -1);
    }
}

s32 func_15173948(s32 arg0, s32 arg1)
{
  return arg0;
  if (arg0)
  {
  }
}

#ifdef NON_MATCHING
s8 func_15173F04(s32 arg0);
extern s32 D_800DD714;          /* current fog/colour state: c[4] at +0, then halfwords at +4..+0x10 */
extern s16 D_800DD718, D_800DD71A, D_800DD71C, D_800DD71E, D_800DD720;
extern u16 D_800DD722, D_800DD724;

/* Blend fog/colour preset `from` toward `to` by t/4096 into slot `dest` of D_8008D010 (or, for -1, the current
 * state D_800DD714; note its halfword order differs from a table entry). Presets 0x7C..0x7F are aliases. */
s32 func_15173954(s32 from, s32 to, s32 arg2, s32 t, s32 dest) {
    Info3850 *table = &D_8008D010;
    u8 *out;
    s16 *v0;
    s16 *v1;
    s16 *v2;
    s16 *v3;
    s16 *pa;
    s16 *pb;
    s32 *sel;
    s32 i;
    s32 a;
    s32 b;
    s32 a2;
    s32 b2;

    D_800DD720 = t;
    if (dest == -1) {
        out = (u8 *)&D_800DD714;
        v0 = &D_800DD71C;
        v1 = &D_800DD71E;
        v2 = &D_800DD718;
        v3 = &D_800DD71A;
        pa = (s16 *)&D_800DD722;
        pb = (s16 *)&D_800DD724;
    } else {
        out = (u8 *)&table[dest];
        v0 = (s16 *)(out + 4);
        v1 = (s16 *)(out + 6);
        v2 = (s16 *)(out + 8);
        v3 = (s16 *)(out + 0xA);
        pa = (s16 *)(out + 0xC);
        pb = (s16 *)(out + 0xE);
    }
    for (i = 0; i < 2; i++) {
        sel = (i == 0) ? &from : &to;
        switch (*sel) {
        case 0x7C:
            *sel = 1;
            break;
        case 0x7D:
        case 0x7F:
            *sel = 2;
            break;
        case 0x7E:
            *sel = func_15173F04(arg2);
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        a = table[from].c[i];
        out[i] = a + ((s32)((table[to].c[i] - a) * t) / 4096);
    }
    a = (u16)table[from].v[0];
    *v0 = a + ((s32)(((u16)table[to].v[0] - a) * t) / 4096);
    a = (u16)table[from].v[1];
    *v1 = a + ((s32)(((u16)table[to].v[1] - a) * t) / 4096);
    a = (u16)table[from].v[2];
    *v2 = a + ((s32)(((u16)table[to].v[2] - a) * t) / 4096);
    a = (u16)table[from].v[3];
    *v3 = a + ((s32)(((u16)table[to].v[3] - a) * t) / 4096);

    /* -1 means "the level default" (D_800B0DF0) */
    a = (s16)table[from].a;
    if (a == -1) {
        a = D_800B0DF0->unk2;
    }
    b = (s16)table[to].a;
    if (b == -1) {
        b = D_800B0DF0->unk2;
    }
    *pa = ((s32)((b - a) * t) / 4096) + a;
    a2 = (s16)table[from].b;
    if (a2 == -1) {
        a2 = D_800B0DF0->unk0;
    }
    b2 = (s16)table[to].b;
    if (b2 == -1) {
        b2 = D_800B0DF0->unk0;
    }
    *pb = ((s32)((b2 - a2) * t) / 4096) + a2;
    return a2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A1060/func_15173954.s")
#endif
s32 func_15173954(s32, s32, s32, s32, s32);
extern s32 D_800DC2D8;
extern s32 D_800DD714;

void func_15173E34(s32 arg0) {
    if ((s8) D_800B0DF0->pad2A[0x1C] == -1) {
        if (D_800DBFF0->unk5F0 & 1) {
            func_15173954(6, 6, arg0, 0, -1);
            (*(u8 *)((u8 *)(&D_800DC2D8) + 0)) = (u8) (*(u8 *)((u8 *)(&D_800DD714) + 0));
            (*(u8 *)((u8 *)(&D_800DC2D8) + 1)) = (u8) (*(u8 *)((u8 *)(&D_800DD714) + 1));
            (*(u8 *)((u8 *)(&D_800DC2D8) + 2)) = (u8) (*(u8 *)((u8 *)(&D_800DD714) + 2));
            return;
        }
        func_15173954(0, 0, arg0, 0, -1);
        (*(u8 *)((u8 *)(&D_800DC2D8) + 0)) = (u8) D_800B0DF0->unk5;
        (*(u8 *)((u8 *)(&D_800DC2D8) + 1)) = (u8) D_800B0DF0->unk6;
        (*(u8 *)((u8 *)(&D_800DC2D8) + 2)) = (u8) D_800B0DF0->unk7;
    }
}

s8 func_15173F04(s32 arg0) {
    return (s8) D_800B0DF0->pad2A[0x1C];
}
