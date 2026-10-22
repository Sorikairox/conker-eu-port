#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8 *p;
    u8 u4;
    s8 u5;
    u8 pad6[2];
    f32 v8[3];
    f32 u14;
    s16 u18;
    s16 u1A;
    s16 u1C;
    u8 pad1E[2];
    f32 u20;
    f32 u24;
    s8 u28;
    s8 u29;
    s8 u2A;
    s8 u2B;
    u8 u2C;
    s8 u2D;
    s8 u2E;
    u8 pad2F;
} S3940;
s32 func_151A3AB4();
s32 func_15160A58(u8 *, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_151A4B40(u8 *, u8);
void func_151A4F4C(u8 *arg0, u8 arg1);
void func_151A3940(u8 *arg0, u8 arg1) {
    S3940 s;
    f32 v[3];

    s.p = arg0;
    s.u4 = arg0[0x3B];
    s.u5 = 1;
    s.v8[0] = 0.0f;
    s.v8[1] = 0.0f;
    s.v8[2] = 0.0f;
    s.u2B = 1;
    s.u2C = 0xFF;
    s.u2D = 8;
    s.u2E = 0x1F;
    s.u18 = 0xAA;
    s.u1A = 0x28;
    s.u1C = 7;
    s.u28 = 2;
    s.u29 = 4;
    s.u2A = 1;
    s.u14 = 0.018000001f;
    s.u20 = 30.0f;
    s.u24 = 0.98100007f;
    func_151A3AB4(&s, arg1);
    func_151A4B40(arg0, arg1);
    func_151A4F4C(arg0, arg1);
    func_10010154(0x1AA, arg0, 0x55F0, 0x3E8, 0xFA0);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    func_15160A58(arg0, 1, v, 2, 0x12C, 0x50, 0xFF, 0xFF, 0x75, 0xFF, 0, -1, 0, 0, arg1, 1);
}

typedef struct { f32 x, y, z; } V33AB4;
typedef struct { V33AB4 pos; s16 u0C; u16 u0E; s32 u10; s8 u14; s8 u15; u8 pad16[2]; s32 u18; } SA3AB4;
typedef struct {
    u8 raw[0x30];
    u8 u30;
    u8 pad31[3];
    V33AB4 u34;
    f32 u40;
    u8 u44;
    u8 pad45[3];
    f32 u48;
    u8 u4C;
    u8 pad4D[3];
} SB3AB4;

s32 func_151A53E4(u8 *arg0, u8 *arg1);

s32 func_151A3AB4(arg0, arg1) u8 *arg0; u8 arg1; {
    SA3AB4 a;
    SB3AB4 b;
    u8 *r;

    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    memcpy(&b, arg0, 0x30);
    b.u44 = 0;
    a.u15 = 0x32;
    a.u0E = 2;
    a.u0C = 1000;
    b.u30 = 6;
    b.u4C = 0;
    b.u40 = 0.0f;
    b.u48 = 0.0f;
    if (func_151A53E4((u8 *)&b, (u8 *)&a.pos)) {
        b.u34 = a.pos;
        a.u0E |= 4;
    }
    a.u10 = 8;
    r = (u8 *)func_15147FF0(&a, 0x50, 0x18, 6, 6, 6, 0, 0, 0, arg1, 0);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, 0x50);
    }
    return (s32)r;
}

typedef struct { f32 x, y, z; } V3;
typedef struct {
    V3 pos;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    u8 unk14;
    u8 pad15[3];
} Trail18;
typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    u8 pad28[2];
    s8 unk2A;
    u8 pad2B[5];
    u8 flags;
    u8 pad31[0x1B];
    u8 unk4C;
} TrailDef18;
typedef struct {
    u8 pad0[0x25];
    u8 count;
    u8 pad26[6];
    s8 n;
    s8 head;
    s8 tail;
    u8 pad2F[0x25];
    V3 pos;
    u8 pad60[0x34];
    Trail18 *trails;
    TrailDef18 *def;
} TrailObj18;

s32 func_151A3BCC(TrailObj18 *arg0) {
    TrailDef18 *def = arg0->def;
    Trail18 *trails = arg0->trails;
    s32 i;
    Trail18 *t;
    s16 life;

    if (arg0->n < 2 && (def->flags & 1)) {
        return 0;
    }
    def->unk4C += def->unk2A * D_800BE9E4;
    i = arg0->tail;
    while (i != arg0->head) {
        i--;
        if (i < 0) {
            i = arg0->count - 1;
        }
        t = &trails[i];
        life = t->unk12;
        if (life > 0) {
            t->unk12 = life - D_800BE9E4;
        } else {
            t->unk10 -= D_800BE9E4 * def->unk1C;
        }
        t->unk14 = 0xFF;
        t->unkC += D_800BE9A4 * def->unk24;
        if (t->unk10 < 0) {
            def->flags &= ~2;
            while (i != arg0->head) {
                arg0->head++;
                if (arg0->head == arg0->count) {
                    arg0->head = 0;
                }
                arg0->n--;
            }
            trails[arg0->head].unk10 = 0;
        }
    }
    if (arg0->n > 0) {
        arg0->pos = trails[arg0->head].pos;
    } else {
        arg0->pos.x = 0.0f; arg0->pos.y = 0.0f; arg0->pos.z = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A3D70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4194.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4B40.s")

s32 func_151308E4(void *, s32, s32, u8, s32);
void func_151A4BE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        s8 u4C;
        s8 u4D;
        s8 u4E;
        u8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    f32 k;
    s16 sh[6];
    s32 obj;

    sp.u51 = 0x27;
    sp.u3C = 0x1401;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() % 5U) + 0xF;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u48 = 0x8A;
    sp.u49 = 0;
    sp.u4A = 0;
    sp.u4B = 0xFF;
    sp.u4C = 0;
    sp.u4D = 0;
    sp.u4E = 0;
    sp.u52 = 1;
    sp.u54 = 0xFF;
    sp.u56 = 1;
    sp.u58 = 1.0f;
    sp.u5C = sp.u60 = (func_150ADA68() * 50.0f) + 500.0f;
    sp.u64 = arg0;
    sp.u68 = arg1;
    sp.u6C = arg2;
    k = 0.087f * D_800BEDC8;
    sp.u7C = -arg3 * k;
    sp.u80 = -arg4 * k;
    sp.u8C = 0xD;
    sp.u94 = 1;
    sp.u95 = 1;
    sp.u84 = -arg5 * k;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u4F = 0xFF;
    sp.u50 = 0xFF;
    sp.u96 = 0;
    sp.u97 = -1;
    sh[0] = 0x10;
    sh[1] = 0xF;
    sh[2] = 0xD;
    sh[3] = 0x13;
    sh[4] = 0x11;
    sh[5] = -0x18;
    obj = func_151308E4(&sp, 0, 0xC, arg6[0xC], 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, sh, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4DEC.s")

s32 func_151A4EB0(u8 *arg0, s32 arg1)
{
  s16 temp_a1;
  u8 *temp_v1;
  temp_v1 = arg0 + 0xA8;
  if ((*((s16 *) (arg0 + 0x1A))) < (*((s16 *) (((u8 *) arg0) + 0xAC))))
  {
    *((s8 *) (((u8 *) arg0) + 0x2B)) = (s8) ((*((s16 *) (((u8 *) arg0) + 0xAE))) * (*((s16 *) (arg0 + 0x1A))));
  }
  if ((*((s16 *) (arg0 + 0x1A))) < (*((s16 *) (((u8 *) temp_v1) + 8))))
  {
    f32 temp_f0;
    temp_f0 = (f32) ((*((s16 *) (((u8 *) temp_v1) + 0xA))) * D_800BE9E4);
    *((f32 *) (((u8 *) arg0) + 0x38)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x38))) + temp_f0);
    *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x3C))) + temp_f0);
  }
  *((s8 *) (((u8 *) arg0) + 0x2C)) = (s8) ((*((s16 *) (((u8 *) temp_v1) + 2))) * (*((s16 *) (((u8 *) arg0) + 0x1A))));
  return 1;
}

void func_151A4F4C(u8 *arg0, u8 arg1) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
        u8 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.722f;
    tmp.unkC = 0.0f;
    tmp.unk10 = 1;
    tmp.unk14 = 0.0f;
    tmp.unk18 = 0.0f;
    tmp.unk1C = 0.0f;
    temp_v0 = func_151491F4(300, -1, 5, 0, 1, 0x20, arg1, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D1150/func_151A4FE8.s")

void func_151A544C(u8 *);
void func_151A5290(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 temp_a0;

    if (arg2 == 0) {
        if ((*(s32 *)(temp_v0 + 0) == *(s32 *)(arg1 + 0)) || (*(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4))) {
            func_151A544C(arg0);
        }
    } else if (arg2 == 0x2D) {
        temp_a0 = *(s32 *)(arg1 + 0);
        if (temp_a0 == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = temp_a0;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}

void func_151A5338(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            func_1516972C(arg0);
        }
    } else {
        v = arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}

s32 func_151A53E4(u8 *arg0, u8 *arg1) {
    s32 temp_v1;
    u32 idx;
    u8 *temp_v0;

    temp_v0 = *(u8 **)arg0;
    temp_v1 = *(s32 *)(temp_v0 + 0x1D4);
    if (temp_v1 == 0) {
        return 0;
    }
    if ((temp_v0[0x74] & 0xF) == 0xF) {
        return 0;
    }
    idx = arg0[5]; // permuter: unsigned local for the index
    func_15143134(arg0 + 8, arg1, temp_v1 + ((idx << 2) << 4));
    return 1;
}

void func_151A544C(u8 *arg0)
{
  u8 *temp_v0;
  temp_v0 = *((u8 **) (arg0 + 0x98));
  arg0[0x30] = 0;
  *((u16 *) (arg0 + 0x1E)) = *((u16 *) (arg0 + 0x1E)) & 0xFFFD;
  temp_v0[0x30] |= 1;
  temp_v0[0x30] |= 4;
}

s32 func_151A3AB4(); // K&R: defined with 2 params, called with 3

void func_151A547C(u8 *arg0) {
    u8 *temp_v0;
    u8 sp1B;
    u8 *temp_a0;

    sp1B = 0;
    temp_a0 = arg0 + 0x28;
    if (**(s32 **)(arg0 + 0x28) == 0) {
        sp1B = 1;
    }
    temp_v0 = *(u8 **)temp_a0;
    if (temp_a0[4] != temp_v0[0x3B]) {
        sp1B = 1;
    }
    if ((sp1B == 0) && (*(s32 *)(temp_v0 + 0x1D4) != 0) && ((temp_v0[0x74] & 0xF) != 0xF)) {
        sp1B = 1; // permuter: the flag is stored before and after the call
#ifdef NON_MATCHING
        func_151A3AB4(temp_a0, arg0[0xC]); /* the asm also loads a2 = arg0; the callee has 2 params */
#else
        func_151A3AB4(temp_a0, arg0[0xC], arg0);
#endif
        sp1B = 1;
    }
    if (sp1B) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}

void func_151A552C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0) && ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4]))) {
        func_1516972C(arg0);
    }
}

void *func_151A5580(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    u8 *temp_v0 = func_15167A68(0x5A, 0, arg7 + 0x20, 0, 0xFF, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_v0[0x14] = arg0;
    *(s32 *)(temp_v0 + 0x10) = arg1;
    temp_v0[0x15] = arg2;
    temp_v0[0x16] = arg3;
    temp_v0[0x17] = arg4;
    temp_v0[0x19] = arg6;
    temp_v0[0x18] = 0;
    temp_v0[0x1A] = arg5;
    return temp_v0;
}

void func_151A5620(u8 *arg0) {
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(arg0 + 0x10);
    if (v0 != 0) {
        v0 = v0 - D_800BE9E4;
        if (v0 <= 0) {
            func_1516972C(arg0);
            return;
        }
        *(s32 *)(arg0 + 0x10) = v0;
    }
    if (*(u8 *)(arg0 + 0x19) == 0) {
        func_10011FA0(2);
    }
    v1 = D_800BE9E4 * 2;
    v0 = *(u8 *)(arg0 + 0x15);
    if (*(u8 *)(arg0 + 0x18) == 0) {
        v0 = v0 - v1;
        if (v0 < 0x90) {
            v0 = 0x90;
            *(u8 *)(arg0 + 0x18) = 1;
        }
    } else {
        v0 = v0 + v1;
        if (v0 >= 0x100) {
            v0 = 0xFF;
            *(u8 *)(arg0 + 0x18) = 0;
        }
    }
    *(u8 *)(arg0 + 0x15) = v0;
}

void func_151A56E0(s32 arg0, u8 *arg1, s16 arg2) {
    D_8008FCA0[arg1[0x14]](arg0, arg1, arg2);
}
