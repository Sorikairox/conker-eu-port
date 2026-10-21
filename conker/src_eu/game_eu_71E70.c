#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15044660(void) {
    D_800CC1BC = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044670.s")

#ifdef NON_MATCHING
void func_1504481C(s32 *arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 var_f12;
    s16 var_f16;
    s32 *var_v1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *var_a3;
    u8 *var_v0;

    var_v1 = arg0;
    var_a3 = arg1;
    var_a2 = 0xC;
    var_v0 = *var_v1 + arg7;
    var_f16 = (*(s16 *)((u8 *)var_v0 + 4));
    var_f12 = (f32) (*(s16 *)((u8 *)var_v0 + 0));
    if (0xC != 0x24) {
        do {
            var_a2 += 0xC;
            var_v1 = (s32 *)((u8 *)var_v1 + (4));
            temp_f6 = var_f12 - arg4;
            var_a3 += 0xC;
            temp_f10 = (f32) var_f16 - arg6;
            (*(f32 *)((u8 *)var_a3 + -8)) = (f32) ((f32) (*(s16 *)((u8 *)var_v0 + 2)) - arg5);
            (*(f32 *)((u8 *)var_a3 + -0xC)) = (f32) ((temp_f6 * arg3) + (temp_f10 * arg2));
            (*(f32 *)((u8 *)var_a3 + -4)) = (f32) ((temp_f10 * arg3) - (temp_f6 * arg2));
            var_v0 = *var_v1 + arg7;
            var_f16 = (*(s16 *)((u8 *)var_v0 + 4));
            var_f12 = (f32) (*(s16 *)((u8 *)var_v0 + 0));
        } while (var_a2 != 0x24);
    }
    temp_a3 = var_a3 + 0xC;
    temp_f6_2 = var_f12 - arg4;
    temp_f10_2 = (f32) var_f16 - arg6;
    (*(f32 *)((u8 *)temp_a3 + -0xC)) = (f32) ((temp_f6_2 * arg3) + (temp_f10_2 * arg2));
    (*(f32 *)((u8 *)temp_a3 + -4)) = (f32) ((temp_f10_2 * arg3) - (temp_f6_2 * arg2));
    (*(f32 *)((u8 *)temp_a3 + -8)) = (f32) ((f32) (*(s16 *)((u8 *)var_v0 + 2)) - arg5);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504481C.s")
#endif
void func_15044948(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044950.s")

u8 *func_15044C54(s32, s32, s32, s32, s32, s32, s32, s32);

u8 *func_15044BC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    u8 *temp_v0;

    temp_v0 = func_15044C54(0x20, 1, arg0, arg1, arg2, 0, 0, 0);
    if (temp_v0 == NULL) {
        return NULL;
    }
    (*(s16 *)((u8 *)temp_v0 + 0x10)) = (s16) arg3;
    (*(s16 *)((u8 *)temp_v0 + 0x12)) = (s16) arg4;
    (*(s16 *)((u8 *)temp_v0 + 0x14)) = (s16) arg5;
    (*(s8 *)((u8 *)temp_v0 + 0x16)) = (s8) arg6;
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = arg7;
    (*(s32 *)((u8 *)temp_v0 + 0x1C)) = arg8;
    return temp_v0;
}

u8 *func_15044C54(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 var_a0;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = allocate_memory(arg0, 1, 0, 0);
    if (temp_v0 == NULL) {
        return NULL;
    }
    (*(s32 *)((u8 *)temp_v0 + 0)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 4)) = (s16) arg2;
    (*(s8 *)((u8 *)temp_v0 + 0xC)) = (s8) arg1;
    (*(s8 *)((u8 *)temp_v0 + 0xD)) = (s8) arg4;
    (*(s8 *)((u8 *)temp_v0 + 0xE)) = (s8) arg3;
    (*(s16 *)((u8 *)temp_v0 + 6)) = (s16) arg5;
    (*(s16 *)((u8 *)temp_v0 + 8)) = (s16) arg6;
    (*(s16 *)((u8 *)temp_v0 + 0xA)) = (s16) arg7;
    if (D_800CBE00 == 0) {
        D_800CBE00 = (s32) temp_v0;
    } else {
        var_v1 = *(s32 *)D_800CBE00;
        var_a0 = D_800CBE00;
        if (var_v1 != 0) {
            do {
                var_a0 = var_v1;
                var_v1 = *(s32 *)var_v1;
            } while (var_v1 != 0);
        }
        *(s32 *)var_a0 = (s32)temp_v0;
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044D18.s")

#ifdef NON_MATCHING
f32 func_150489B0(u8, u8 *);

s32 func_15044E68(u8 *arg0) {
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_t6;
    s32 var_v0;

    sp1C = (s32) (s16) D_800CC2D0->unk31C->unk116;
    temp_t6 = (s16) D_800CC2D0->unk31C->unk114 >> 1;
    sp18 = (s32) (s16) D_800CC2D0->unk31C->unk118;
    temp_f2 = D_800CC2D0->x_position - (f32) (*(s16 *)((u8 *)arg0 + 6));
    sp34 = (D_800CC2D0->y_position - (f32) (*(s16 *)((u8 *)arg0 + 8))) + (f32) temp_t6;
    sp30 = D_800CC2D0->z_position - (f32) (*(s16 *)((u8 *)arg0 + 0xA));
    sp38 = temp_f2;
    sp20 = temp_t6;
    sp40 = func_15048A40((*(u8 *)((u8 *)arg0 + 0x16)));
    temp_f0 = func_150489B0((*(u8 *)((u8 *)arg0 + 0x16)), arg0);
    temp_f14 = (sp30 * temp_f0) + (temp_f2 * sp40);
    var_v0 = 0;
    temp_f2_2 = (temp_f2 * temp_f0) - (sp30 * sp40);
    if ((fabsf(sp34) < (f32) ((*(s16 *)((u8 *)arg0 + 0x14)) + sp20)) && (fabsf(temp_f2_2) < (f32) ((*(s16 *)((u8 *)arg0 + 0x12)) + sp1C)) && (fabsf(temp_f14) < (f32) ((*(s16 *)((u8 *)arg0 + 0x10)) + sp18))) {
        var_v0 = 1;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044E68.s")
#endif
void func_15044FD4(u8 *arg0) {
    s16 *temp_v0 = *(s16 **)(arg0 + 0x18);
    s16 temp_t0;

    *(s16 *)(arg0 + 6) = temp_v0[0];
    *(s16 *)(arg0 + 8) = temp_v0[1];
    *(s16 *)(arg0 + 0xA) = temp_v0[2];
    temp_t0 = **(s16 **)(arg0 + 0x1C) / 32;
    *(s16 *)(arg0 + 0x10) = temp_t0;
    *(s16 *)(arg0 + 0x12) = temp_t0;
    *(s16 *)(arg0 + 0x14) = temp_t0;
    func_15044E68(arg0);
}

s32 func_150472F4(u8 *, f32, u8 *);
s32 func_150A44A4(f32, f32, s32, u8 *, f32 *);
s32 func_150473A0(u8 *, f32, u8 *);
typedef struct { s32 unk0; s32 *unk4; s32 unk8; s32 unkC; } Unk3720;
typedef struct { f32 unk0; s16 unk4[3][3]; s32 unk18; u8 unk1C; u8 unk1D; s32 unk20; } Unk45674;
extern Unk3720 D_800D3720[];
extern f32 D_800990F8; // 99999.9f
extern f32 D_800990FC;
void func_1510F800(s32);
s32 func_150451C0(f32 *, f32, Unk45674 *);
s32 func_15046C6C(u8 *, u16, f32, u8 *);
s32 func_15046FF0(u8 *, u16, f32, u8 *);
s32 func_150469E8(u8 *, u16, f32, u8 *);

s32 func_15045030(u8 *arg0) {
    func_1505D1C4((f32)*(s16 *)(arg0 + 6), (f32)*(s16 *)(arg0 + 8), (f32)*(s16 *)(arg0 + 0xA), *(s16 *)(arg0 + 0x10), 0xFF, 0, 0, 0);
    return 0;
}

void func_15045090(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 5, D_800CC2D0->unk7A, -1);
        }
    }
}

void func_150450D8(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            if (D_800C35EA != 1) {
                func_1505D024(D_800CC2D0, 4, D_800CC2D0->unk7A, -1);
            }
        }
    }
}

void func_15045130(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 0x40, D_800CC2D0->unk7A, -1);
        }
    }
}

void func_15045178(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 1, D_800CC2D0->unk7A, -1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150451C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150453BC.s")

s32 func_150455FC(u8 *arg0, f32 arg1, u8 *arg2) {
    switch (func_150473A0(arg0, arg1, arg2)) {
        case 0:
            return func_150451C0(arg0, arg1, arg2);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}

s32 func_150A5480(s32, s32);

s32 func_15045674(f32 *arg0, f32 arg1, Unk45674 *arg2) {
    Unk45674 *out;
    s32 best;
    s32 n;
    s32 i;
    f32 d;
    s32 j;
    s32 *q;
    s32 off;

    if (arg1 < arg0[1]) {
        arg2->unk1C &= ~2;
        return 0;
    }
    arg2->unk0 = D_800990F8;
    best = -1;
    func_1510F800(3);
    n = func_150A5480((s32) arg0[0], (s32) arg0[2]);
    for (i = 0; i < n; i++) {
        d = D_800D3720[i].unk0 * 0.00390625f;
        if ((arg0[1] <= d) && (d < arg2->unk0)) {
            best = i;
            arg2->unk0 = d;
        }
    }
    if (best != -1) {
        q = D_800D3720[best].unk4;
        out = arg2;
        off = D_800D3720[best].unk8;
        for (j = 0; j < 3; j++) {
            s16 *p;

            p = (s16 *) (q[j] + off);
            out->unk4[j][0] = p[0];
            out->unk4[j][1] = p[1];
            out->unk4[j][2] = p[2];
        }
        out->unk18 = 0;
        out->unk1C |= 6;
        out->unk1D = 4;
        out->unk20 = 0;
        if (out->unk0 <= arg1) {
            arg2->unk1C |= 2;
            return 1;
        }
        return 0;
    }
    arg2->unk1C &= ~2;
    return 0;
}

s32 func_1504583C(f32 *arg0, f32 arg1, Unk45674 *arg2) {
    Unk45674 *out;
    s32 best;
    s32 n;
    s32 i;
    f32 d;
    s32 j;
    s32 *q;
    s32 off;

    if (arg0[1] < arg1) {
        arg2->unk1C &= ~2;
        return 0;
    }
    arg2->unk0 = D_800990FC;
    best = -1;
    func_1510F800(3);
    n = func_150A5480((s32) arg0[0], (s32) arg0[2]);
    for (i = 0; i < n; i++) {
        d = D_800D3720[i].unk0 * 0.00390625f;
        if ((d <= arg0[1]) && (arg2->unk0 < d)) {
            best = i;
            arg2->unk0 = d;
        }
    }
    if (best != -1) {
        q = D_800D3720[best].unk4;
        out = arg2;
        off = D_800D3720[best].unk8;
        for (j = 0; j < 3; j++) {
            s16 *p;

            p = (s16 *) (q[j] + off);
            out->unk4[j][0] = p[0];
            out->unk4[j][1] = p[1];
            out->unk4[j][2] = p[2];
        }
        out->unk18 = 0;
        out->unk1C |= 6;
        out->unk1D = 4;
        out->unk20 = 0;
        if (arg1 <= out->unk0) {
            arg2->unk1C |= 2;
            return 1;
        }
        return 0;
    }
    arg2->unk1C &= ~2;
    return 0;
}

s32 func_150A69E0(s16, s16, s32, u16);
void func_1510F800(s32);

void func_15045A04(u8 *arg0, u16 arg1, s32 *arg2, s32 arg3) {
    func_1510F800(2);
    *arg2 = func_150A69E0((s16) (s32) (*(f32 *)((u8 *)arg0 + 0)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 8)), arg3, arg1);
}

s32 func_1504627C(u8 *, f32, s32 *, u8 *);
s32 func_15045A70(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    s32 sp1C;
    s32 sp18;
    if (*(f32 *)(arg0 + 4) < arg2) {
        arg3[0x1C] &= 0xFFFD;
        return 0;
    }
    func_15045A04(arg0, arg1, &sp1C, &sp18);
    return func_1504627C(arg0, arg2, &sp18, arg3);
}

s32 func_15045AF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150472F4(arg0, arg2, arg3)) {
        case 0:
            return func_15045A70(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}

typedef struct {
    s16 v[9];
} HitPos;
typedef struct {
    f32 t;
    HitPos pos;
    s32 unk18;
    u8 flags;
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
} HitInfo;

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045DD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046038.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504627C.s")

u8 func_150464C0(u8 *, u16, f32, HitInfo *);

u8 func_15045B70(u8 *, f32, s32 *, HitInfo *);
u8 func_15046038(u8 *, f32, s32 *, HitInfo *);
u8 func_150464C0(u8 *arg0, u16 arg1, f32 arg2, HitInfo *arg3) {
    s32 sp74;
    s32 sp70;
    HitInfo a;
    HitInfo b;
    u8 r1;
    u8 r2;

    if (arg2 < *(f32 *)(arg0 + 4)) {
        arg3->flags &= ~2;
        return 0;
    }
    a = *arg3;
    b = *arg3;
    func_15045A04(arg0, arg1, &sp74, (s32)&sp70);
    r1 = func_15045B70(arg0, arg2, &sp74, &a);
    r2 = func_15046038(arg0, arg2, &sp70, &b);
    if (r1 != 0 && r2 != 0) {
        if (a.t < b.t) {
            *arg3 = a;
            return 1;
        }
        *arg3 = b;
        return 1;
    }
    if (r1) {
        *arg3 = a;
        return 1;
    }
    if (r2 != 0) {
        *arg3 = b;
        return 1;
    }
    if (a.t < b.t) {
        *arg3 = a;
    } else {
        *arg3 = b;
    }
    arg3->flags &= ~2;
    return 0;
}

u8 func_15045DD4(u8 *, f32, s32 *, HitInfo *);

s32 func_15046750(u8 *arg0, u16 arg1, f32 arg2, HitInfo *arg3) {
    s32 sp74;
    s32 sp70;
    HitInfo a;
    HitInfo b;
    u8 r1;
    u8 r2;

    if (*(f32 *)(arg0 + 4) < arg2) {
        arg3->unk1D = 0;
        arg3->unk20 = 0;
        arg3->flags &= ~2;
        return 0;
    }
    a = *arg3;
    b = *arg3;
    func_15045A04(arg0, arg1, &sp74, (s32)&sp70);
    r1 = func_15045DD4(arg0, arg2, &sp74, &a);
    r2 = func_1504627C(arg0, arg2, &sp70, (u8 *)&b);
    if (r1 != 0 && r2 != 0) {
        if (b.t < a.t) {
            *arg3 = a;
            return 1;
        }
        *arg3 = b;
        return 1;
    }
    if (r1) {
        *arg3 = a;
        return 1;
    }
    if (r2 != 0) {
        *arg3 = b;
        return 1;
    }
    if (b.t < a.t) {
        *arg3 = a;
    } else {
        *arg3 = b;
    }
    arg3->flags &= ~2;
    return 0;
}

s32 func_150469E8(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    HitInfo a;
    HitInfo b;
    u8 r1;
    u8 r2;

    if (arg2 < *(f32 *)(arg0 + 4)) {
        ((HitInfo *)arg3)->flags &= ~2;
        return 0;
    }
    a = *(HitInfo *)arg3;
    b = *(HitInfo *)arg3;
    r1 = func_150464C0(arg0, arg1, arg2, &a);
    r2 = func_150451C0(arg0, arg2, &b);
    if (r1 != 0 && r2 != 0) {
        if (a.t < b.t) {
            *(HitInfo *)arg3 = a;
            return 1;
        }
        *(HitInfo *)arg3 = b;
        return 1;
    }
    if (r1 != 0) {
        *(HitInfo *)arg3 = a;
        return 1;
    }
    if (r2 != 0) {
        *(HitInfo *)arg3 = b;
        return 1;
    }
    if (a.t < b.t) {
        *(HitInfo *)arg3 = a;
    } else {
        *(HitInfo *)arg3 = b;
    }
    ((HitInfo *)arg3)->flags &= ~2;
    return 0;
}

s32 func_15046750(u8 *, u16, f32, HitInfo *);
s32 func_150453BC(u8 *, f32, u8 *);

s32 func_15046C6C(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    HitInfo a;
    HitInfo b;
    u8 r1;
    u8 r2;

    if (*(f32 *)(arg0 + 4) < arg2) {
        ((HitInfo *)arg3)->flags &= ~2;
        return 0;
    }
    a = *(HitInfo *)arg3;
    b = *(HitInfo *)arg3;
    r1 = func_15046750(arg0, arg1, arg2, &a);
    r2 = func_150453BC(arg0, arg2, (u8 *)&b);
    if (r1 != 0 && r2 != 0) {
        if (b.t < a.t) {
            *(HitInfo *)arg3 = a;
            return 1;
        }
        *(HitInfo *)arg3 = b;
        return 1;
    }
    if (r1 != 0) {
        *(HitInfo *)arg3 = a;
        return 1;
    }
    if (r2 != 0) {
        *(HitInfo *)arg3 = b;
        return 1;
    }
    if (b.t < a.t) {
        *(HitInfo *)arg3 = a;
    } else {
        *(HitInfo *)arg3 = b;
    }
    ((HitInfo *)arg3)->flags &= ~2;
    return 0;
}

s32 func_15046EF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150473A0(arg0, arg2, arg3)) {
        case 0:
            return func_150469E8(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}

s32 func_15046F70(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150472F4(arg0, arg2, arg3)) {
        case 0:
            return func_15046C6C(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}


s32 func_15046FF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    HitInfo a;
    HitInfo b;
    u8 r1;
    u8 r2;

    if (*(f32 *)(arg0 + 4) < arg2) {
        ((HitInfo *)arg3)->flags &= ~2;
        return 0;
    }
    a = *(HitInfo *)arg3;
    b = *(HitInfo *)arg3;
    r1 = func_15046C6C(arg0, arg1, arg2, (u8 *)&a);
    r2 = func_1504583C((f32 *)arg0, arg2, (Unk45674 *)&b);
    if (r1 != 0 && r2 != 0) {
        if (b.t < a.t) {
            *(HitInfo *)arg3 = a;
            return 1;
        }
        *(HitInfo *)arg3 = b;
        return 1;
    }
    if (r1 != 0) {
        *(HitInfo *)arg3 = a;
        return 1;
    }
    if (r2 != 0) {
        *(HitInfo *)arg3 = b;
        return 1;
    }
    if (b.t < a.t) {
        *(HitInfo *)arg3 = a;
    } else {
        *(HitInfo *)arg3 = b;
    }
    ((HitInfo *)arg3)->flags &= ~2;
    return 0;
}

s32 func_15047274(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150472F4(arg0, arg2, arg3)) {
        case 0:
            return func_15046FF0(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}


s32 func_150472F4(u8 *arg0, f32 arg1, u8 *arg2) {
    f32 sp24;

    if ((arg2[0x1C] & 4) && (func_150A44A4(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 8), 0, arg2 + 4, &sp24) != 0)) {
        if ((arg1 <= sp24) && (sp24 <= *(f32 *)(arg0 + 4))) {
            *(f32 *)arg2 = sp24;
            arg2[0x1C] = arg2[0x1C] | 2;
            return 2;
        }
        return 1;
    }
    return 0;
}

s32 func_150A44A4(f32, f32, s32, u8 *, f32 *);

s32 func_150473A0(u8 *arg0, f32 arg1, u8 *arg2) {
    f32 sp24;

    if ((arg2[0x1C] & 4) && (func_150A44A4(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 8), 0, arg2 + 4, &sp24) != 0)) {
        if ((sp24 <= arg1) && (*(f32 *)(arg0 + 4) <= sp24)) {
            *(f32 *)arg2 = sp24;
            arg2[0x1C] = arg2[0x1C] | 2;
            return 2;
        }
        return 1;
    }
    return 0;
}

s32 func_15145C90(s32);

void func_1504715C(HitInfo *out, u8 *obj) {

    out->t = *(f32 *)(obj + 0x180);
    if (*(s32 *)(obj + 0xF8) & 0x200000) {
        s16 x = *(f32 *)(obj + 0x14);
        s16 y = *(f32 *)(obj + 0x180);
        s16 z = *(f32 *)(obj + 0x1C);

        out->pos.v[0] = x + 1000;
        out->pos.v[1] = y;
        out->pos.v[2] = z + 1000;
        out->pos.v[3] = x - 1000;
        out->pos.v[4] = y;
        out->pos.v[5] = z;
        out->pos.v[6] = x + 1000;
        out->pos.v[7] = y;
        out->pos.v[8] = z - 1000;
    } else {
        out->pos = *(HitPos *)(obj + 0x18C);
    }
    out->unk18 = *(s32 *)(obj + 0x184);
    out->flags = 6;
    if (*(u16 *)(obj + 0x1A0) != 0) {
        s32 idx = *(u16 *)(obj + 0x1A0) - 1;

        out->unk1D = 2;
        out->unk20 = (s32)&D_800DBEF4[idx];
        out->flags |= func_15145C90(idx) ? 1 : 0;
    } else {
        out->unk1D = 1;
        out->unk20 = 0;
        out->flags |= 1;
    }
}

void func_150475B0(HitInfo *out, u8 *in) {
    out->t = *(f32 *)(in + 0xC);
    out->pos = *(HitPos *)(in + 0x44);
    out->unk18 = *(s32 *)(in + 0x60);
    out->flags = (in[0x59] == 1 ? 1 : 0) | (in[0x59] == 1 ? 2 : 0) | (in[0x59] == 1 ? 4 : 0);
    out->unk1D = in[0x59] == 1 ? 1 : 0;
    out->unk20 = *(s32 *)(in + 0x5C);
}

#pragma function sqrtf
extern f32 D_80099110;
extern f32 D_80099114;
extern f32 D_80099118;
void func_15047680(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp) {
    f32 len, inv, xLook, yLook, zLook, xRight, yRight, zRight;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    len = sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    if (len == 0.0f) {
        len = D_80099110;
    }
    inv = -1.0f / len;
    xLook *= inv;
    yLook *= inv;
    zLook *= inv;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    if (len == 0.0f) {
        len = D_80099114;
    }
    inv = 1.0f / len;
    xRight *= inv;
    yRight *= inv;
    zRight *= inv;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    if (len == 0.0f) {
        len = D_80099118;
    }
    inv = 1.0f / len;
    xUp *= inv;
    yUp *= inv;
    zUp *= inv;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0;
    mf[1][3] = 0;
    mf[2][3] = 0;
    mf[3][3] = 1;
}

void func_15047680(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);

// fakematch: volatile arg3 makes IDO store and reload a3 like the original
void func_15047978(Mtx *arg0, f32 arg1, f32 arg2, volatile f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 sp30[16];
    func_15047680((f32 (*)[4])sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    guMtxF2L((f32 (*)[4]) sp30, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150479F0.s")

void func_150479F0(f32 (*)[4], LookAt *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_15047E70(Mtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA) {
    f32 sp38[4][4];
    func_150479F0(sp38, (LookAt *) arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    guMtxF2L(sp38, arg0);
}
