#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2);
#endif

void func_151D7D78(u8 *);


struct260 *func_151D7760(s16 arg0, u8 arg1, u8 arg2, f32 arg3, u8 *arg4, u8 arg5, s32 arg6) {
    struct260 *temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
        u8 unk5;
        u8 pad6[2];
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = arg2;
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.0f;
    tmp.unk10 = 0.0f;
    tmp.unk14 = arg3;
    temp_v0 = func_15149130(arg0, -1, 0x42, -1, arg1, 0x36, (struct37 *)(arg4 + 0x18), arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7814.s")

extern void (*D_80090044[])(u8 *, s32, u8);
void func_151D7958(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *new_var;
  if (D_80090044[arg0[0x2C]] != 0)
  {
    new_var = &arg0[0x2C]; // fakematch: second index read must not be CSEd
    if (arg1)
    {
    }
    D_80090044[*new_var](arg0, arg1, arg2);
  }
}

void func_151D79B4(void *arg0) {
    func_151D7D78(arg0);
}

void func_151D79D4(void *arg0) {
    func_151D79B4(arg0);
    func_1514933C(arg0);
}

void func_151D7A00(void *arg0) {
    func_151D79B4(arg0);
    func_15149368(arg0);
}

void func_151D7A2C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3D);
}

void func_151D7A60(u8 *arg0, u8 arg1, s8 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        s8 unk6;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = *(u8 *)(arg0 + 0x3B);
    tmp.unk5 = arg1;
    tmp.unk6 = arg2;
    temp_v0 = func_151D7760(0x12C, 0, 0, 12.0f, (u8 *)8, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x40, &tmp, 8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7AE8.s")

extern u8 D_800AB660[];
extern u8 D_800AB6B4[];
extern s32 (*D_80090048[])(u8 *);

s32 func_151D7B74(u8 *arg0) {
    u8 *obj;
    u8 *s;
    u8 *f;

    f = arg0 + 0x28;
    obj = *(u8 **)(arg0 + 0x40);
    s = arg0 + 0x40;
    if (*(s32 *)obj == 0 || s[4] != obj[0x3B]) {
        return 0;
    }
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        f[5] &= ~1;
        return 1;
    }
    if (*(u8 **)(obj + 0x31C) != NULL && (*(u8 **)(obj + 0x31C))[0x197] != 0 && *(s32 *)(obj + 0x318) != 0) {
        f[5] &= ~1;
        return 1;
    }
    if (obj[7] != 0xFF) {
        f[5] &= ~1;
        return 1;
    }
    func_15143134(&D_800AB660[s[5] * 12], f + 8, *(u8 **)(obj + 0x1D4) + (D_800AB6B4[s[5]] << 6));
    f[5] |= 1;
    if ((s8)s[6] != -1) {
        return D_80090048[(s8)s[6]](arg0);
    }
    return 1;
}

s32 func_151D7CD4(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v0_2 = arg0 + 0x28;

    if ((*(s32 *)(temp_v0 + 0x94) & 2) || (*(u16 *)(temp_v0 + 0x84) == 4) ||
        (*(u16 *)(temp_v0 + 0x84) == 0xA) || (*(u16 *)(temp_v0 + 0x84) == 0xC)) {
        temp_v0_2[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D20(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (*(u16 *)(temp_v0 + 0x84) == 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D4C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (temp_v0[0xAD] != 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

void func_151D7D78(u8 *arg0) {
    u8 **v;
    s32 *q;
    v = (u8 **)(arg0 + 0x28);
    if (*(s32 *)(arg0 + 0x28) != 0) {
        q = *(s32 **)(*v + 0x98);
        *(s8 *)(*v + 0x30) = 0;
        *(u16 *)(*v + 0x1E) &= 0xFFFD;
        *(u16 *)(*v + 0x1E) |= 8;
        *(u16 *)(*v + 0x1E) |= 1;
        *(s16 *)(*v + 0x1C) = 0x14;
        *q = 0;
        *v = NULL;
    }
}

typedef struct { f32 x, y, z; } V37DE0;
typedef struct { V37DE0 pos; s16 u58; s16 u5A; s32 u5C; s8 u60; s8 u61; u8 pad62[2]; s32 u64; } SA7DE0;
typedef struct { u8 *u68; V37DE0 pos; f32 u78, u7C, u80; } SB7DE0;

void func_151D7DE0(u8 *arg0) {
    u8 *r;
    SB7DE0 b;
    SA7DE0 a;
    s32 pad[2]; // fakematch: frame padding below the param block

    b.u68 = arg0;
    b.pos = *(V37DE0 *)(arg0 + 0x30);
    b.u78 = 0.0f;
    b.u7C = 0.0f;
    b.u80 = 0.0f;
    a.u61 = 0x19;
    a.pos = *(V37DE0 *)(arg0 + 0x30);
    a.u58 = 0x12C;
    a.u5A = 0x76;
    a.u5C = 0x12;
    a.u60 = 4;
    a.u64 = 0;
    r = (u8 *)func_15147FF0(&a, 0x20, 0x1C, 0xD, 0x10, 0x10, 0, 0, 0, arg0[0xC], arg0[1]);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, 0x1C);
        *(u8 **)(arg0 + 0x28) = r;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7EDC.s")

#ifdef NON_MATCHING
s32 func_151D7FE8(u8 *arg0) {
    struct {
        f32 u88;
        f32 u8C;
        f32 u90;
        u8 pad94[0x20];
        f32 uB4;
        f32 uB8;
        f32 uBC;
    } sp;
    u8 *sp70;
    f32 sp64;
    f32 *temp_a0;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f22;
    f32 var_f2;
    s32 temp_s3;
    s8 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_v0 = (*(u8 **)((u8 *)temp_s1 + 0));
    if (!((*(u8 *)((u8 *)temp_v0 + 0x2D)) & 1)) {
        return 0;
    }
    (*(f32 *)((u8 *)(&sp.uB4) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0x30));
    (*(s32 *)((u8 *)(&sp.uB4) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x34));
    (*(s32 *)((u8 *)(&sp.uB4) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x38));
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)(&sp.uB4) + 0));
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (*(s32 *)((u8 *)(&sp.uB4) + 4));
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) (*(s32 *)((u8 *)(&sp.uB4) + 8));
    (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x14)) + (0.25f * D_800BE9A4));
    temp_f18 = (*(f32 *)((u8 *)temp_s1 + 0x14));
    if (temp_f18 > 1.0f) {
        temp_f0 = 1.0f / temp_f18;
        temp_v0_2 = temp_s1 + 4;
        (*(f32 *)((u8 *)(&sp.u88) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 0));
        var_f22 = (*(f32 *)((u8 *)temp_s1 + 0x10)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 4));
        (*(s32 *)((u8 *)(&sp.u88) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 8));
        temp_f26 = var_f22 * temp_f0;
        temp_f28 = (sp.uB4 - (*(f32 *)((u8 *)temp_s1 + 4))) * temp_f0;
        sp70 = temp_v0_2;
        temp_f30 = (sp.uB8 - (*(f32 *)((u8 *)temp_s1 + 8))) * temp_f0;
        var_f2 = (sp.uBC - (*(f32 *)((u8 *)temp_s1 + 0xC))) * temp_f0;
        do {
            temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x1C) + temp_s3;
            (*(f32 *)((u8 *)temp_a0 + 0)) = (*(f32 *)((u8 *)(&sp.u88) + 0));
            (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 4));
            (*(f32 *)((u8 *)temp_a0 + 0xC)) = 0.0f;
            (*(f32 *)((u8 *)temp_a0 + 0x10)) = 0.0f;
            (*(s8 *)((u8 *)temp_a0 + 0x14)) = 0;
            (*(f32 *)((u8 *)temp_a0 + 0x18)) = 0.0f;
            (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 8));
            sp64 = var_f2;
            func_151D8CC8(temp_a0, temp_a0 + 0xC, var_f22);
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            var_f22 -= temp_f26;
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.u88 += temp_f28;
            sp.u8C += temp_f30;
            sp.u90 += var_f2;
            (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x14)) > 1.0f);
        (*(f32 *)((u8 *)sp70 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u88) + 0));
        (*(s32 *)((u8 *)sp70 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 4));
        (*(s32 *)((u8 *)sp70 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 8));
        (*(f32 *)((u8 *)temp_s1 + 0x10)) = var_f22;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7FE8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8674.s")

void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 temp_f2 = *arg1;

    *arg1 += D_800AB6CC * arg2;
    arg0[1] += (temp_f2 * arg2) + (D_800AB6D0 * (arg2 * arg2));
}

void func_151D8D14(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x28 / 4] = 0;
    }
}

void func_151D8D30(void *arg0) {
    func_151D8D14(arg0);
    func_15147E64(arg0);
}

void func_151D8D5C(void *arg0) {
    func_151D8D14(arg0);
    func_15147E98(arg0);
}
