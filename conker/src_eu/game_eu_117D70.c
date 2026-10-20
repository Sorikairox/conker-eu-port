#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15134DAC(void *, s32, u8 *, s16);
s32 func_150EA560(u8 *arg0, s16 arg1, f32 arg2, u8 arg3) {
    struct {
        u8 u2C;
        u8 *u30;
        u8 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        u8 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        u8 u5A;
        u8 u5B;
        u8 u5C;
        f32 u60;
        u8 u64;
        s8 u65;
    } sp;
    s32 obj;
    struct {
        s32 u18;
        s32 u1C;
        f32 u20;
        f32 u24;
    } t;

    sp.u2C = arg0[0x3B];
    sp.u38 = -9.0f;
    sp.u30 = arg0;
    sp.u34 = 8;
    sp.u3C = -14.0f;
    sp.u48 = -14.0f;
    sp.u50 = 2;
    sp.u52 = 0x3C;
    sp.u54 = 0x3C;
    sp.u56 = arg1;
    sp.u5A = 2;
    sp.u5B = 2;
    sp.u5C = 2;
    sp.u64 = 3;
    sp.u65 = -1;
    t.u18 = 0;
    t.u1C = 0x11111;
    sp.u40 = 27.0f;
    sp.u44 = -21.0f;
    sp.u4C = 41.0f;
    sp.u60 = 0.5f;
    t.u20 = 0.2f;
    t.u24 = 0.060000002f;
    obj = func_15134DAC(&sp, 0x10, arg0, arg1);
    if (obj != 0) {
        memcpy(obj + 0x80, &t, 0x10);
    }
    return obj;
}

s32 func_150EA68C(u8 *arg0) {
    *(s32 *)(arg0 + 0x80) = 0;
    return 1;
}

typedef struct { f32 x, y, z; } V3s99;
s32 func_1513092C(void *, s32, s32);
void func_150EA69C(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        u8 u49;
        u8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        u8 u4E;
        u8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        V3s99 u64;
        f32 u70;
        f32 u74;
        f32 u78;
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
    s32 obj;
    struct {
        f32 scale;
        s8 u20;
        s8 u21;
        s8 u22;
        s8 u23;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        s8 u34;
        s8 u35;
        s8 u36;
        s8 u37;
        f32 u38;
        f32 u3C;
        f32 u40;
    } b;

    sp.u51 = 0x2F;
    sp.u3C = 0xC01;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u4E = 0;
    sp.u4D = 0;
    sp.u4C = 0;
    sp.u4B = 0;
    sp.u4A = 0;
    sp.u49 = 0;
    sp.u48 = 0;
    sp.u44 = 0;
    sp.u40 = 0;
    sp.u50 = 0xFF;
    sp.u56 = 0;
    sp.u58 = 0.0f;
    sp.u8C = 0x1207;
    sp.u94 = 5;
    sp.u95 = 5;
    sp.u96 = 4;
    sp.u97 = -1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u52 = 0x14;
    sp.u54 = 0xC;
    b.u20 = 0;
    b.u21 = 0;
    b.u34 = 0;
    b.u35 = 0;
    b.u2C = 3.5f;
    b.u30 = 0.2857143f;
    sp.u7C = *(f32 *)(arg5 + 0x74) * (arg1[0] - arg0[0]);
    sp.u80 = *(f32 *)(arg5 + 0x74) * (arg1[1] - arg0[1]);
    sp.u84 = *(f32 *)(arg5 + 0x74) * (arg1[2] - arg0[2]);
    sp.u64 = *(V3s99 *)arg0;
    sp.u64.x += sp.u7C * arg4;
    sp.u64.y += sp.u80 * arg4;
    sp.u64.z += sp.u84 * arg4;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u3E = (func_150ADA20() % 51U) + 0x32;
    sp.u4F = (func_150ADA20() % 101U) + 0x64;
    b.scale = sp.u5C = sp.u60 = (func_150ADA68() * 39.0f) + 31.0f;
    b.u22 = (func_150ADA20() % 5U) + 4;
    b.u23 = (func_150ADA20() % 5U) + 4;
    b.u24 = ((func_150ADA68() * 0.25f) + 0.15f) * b.scale;
    b.u28 = ((func_150ADA68() * 0.25f) + 0.15f) * b.scale;
    b.u36 = (func_150ADA20() % 5U) + 4;
    b.u37 = (func_150ADA20() % 5U) + 4;
    b.u38 = ((func_150ADA68() * 0.1f) + 0.08f) * b.scale;
    b.u3C = ((func_150ADA68() * 0.1f) + 0.08f) * b.scale;
    sp.u88 = ((func_150ADA68() * 70.0f) + 73.0f) * 0.001f;
    obj = func_1513092C(&sp, 2, 0x28);
    if (obj != 0) {
        memcpy(obj + 0xA8, &b, 0x28);
    }
}

f32 func_150EAA10(u8 *arg0) {
    u8 **q;
    u8 *p;
    f32 r;

    q = &arg0;
    r = func_151423D8((((u32) (*(u32 *)((u8 *)arg0 + 0x80)) >> 0x10) - 0x40));
    p = *q;
    r = (*(f32 *)((u8 *)p + 0x88)) + ((*(f32 *)((u8 *)p + 0x8C)) * (0, r)); // fakematch: (0, x) comma flips commutative operand order
    p += 0x80;
    *(s32 *)(p + 0) = (*(s32 *)((u8 *)p + 4)) * D_800BE9E4 + (*(u32 *)((u8 *)p + 0));
    return r;
}

typedef struct {
    s32 u40;
    s32 u44;
    u8 u48;
    s32 u4C;
    s8 u50;
    f32 u54;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    s16 u68;
    u8 u6A;
    u8 u6B;
    s8 u6C;
    u8 u6D;
} sp_EAA80;
u8 *func_1513418C(void *, s32, u8, s32);
void func_150EAA80(u8 *arg0, s16 arg1, f32 arg2, u8 arg3) {
    sp_EAA80 sp;
    s32 v;

    sp.u40 = 0;
    sp.u44 = 0;
    sp.u48 = arg0[0x3B];
    sp.u4C = (s32)arg0;
    sp.u50 = 1;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 0.0f;
    sp.u60 = 25.0f;
    sp.u64 = 0.26497f;
    if (arg1 == -1) {
        sp.u68 = 300;
    } else {
        sp.u68 = arg1;
    }
    if (arg1 == -1) {
        v = 0;
    } else {
        v = 4;
    }
    sp.u6A = v | 0xA;
    sp.u6B = 7;
    sp.u6C = -1;
    sp.u6D = 6;
    func_1513418C(&sp, 0, 0xFF, 0);
}

s32 func_1513092C(void *, s32, s32);
void func_150EAB4C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        u8 u49;
        u8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        u8 u4E;
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
        f32 u70;
        f32 u74;
        f32 u78;
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
    s32 obj;
    struct {
        f32 scale;
        s8 u20;
        s8 u21;
        s8 u22;
        s8 u23;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        s8 u34;
        s8 u35;
        s8 u36;
        s8 u37;
        f32 u38;
        f32 u3C;
        f32 u40;
    } b;

    sp.u51 = 0x2F;
    sp.u3C = 0xC01;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u4E = 0;
    sp.u4D = 0;
    sp.u4C = 0;
    sp.u4B = 0;
    sp.u4A = 0;
    sp.u49 = 0;
    sp.u48 = 0;
    sp.u44 = 0;
    sp.u40 = 0;
    sp.u50 = 0xFF;
    sp.u56 = 0;
    sp.u58 = 0.0f;
    sp.u8C = 0x3207;
    sp.u94 = 5;
    sp.u95 = 5;
    sp.u96 = 4;
    sp.u97 = -1;
    sp.u64 = arg0;
    sp.u68 = arg1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u52 = 0x1E;
    sp.u54 = 8;
    sp.u6C = arg2;
    b.u40 = 1000.0f;
    b.u2C = 4.0f;
    b.u30 = 0.25f;
    b.u20 = 0;
    b.u21 = 0;
    b.u34 = 0;
    b.u35 = 0;
    sp.u7C = -arg3 * 0.2f;
    sp.u80 = 0.0f;
    sp.u84 = -arg5 * 0.2f;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u3E = (func_150ADA20() % 51U) + 0x6A;
    sp.u4F = (func_150ADA20() % 101U) + 0x64;
    b.scale = sp.u5C = sp.u60 = (func_150ADA68() * 62.0f) + 41.0f;
    b.u22 = (func_150ADA20() % 5U) + 4;
    b.u23 = (func_150ADA20() % 5U) + 4;
    b.u24 = ((func_150ADA68() * 0.25f) + 0.15f) * b.scale;
    b.u28 = ((func_150ADA68() * 0.25f) + 0.15f) * b.scale;
    b.u36 = (func_150ADA20() % 5U) + 4;
    b.u37 = (func_150ADA20() % 5U) + 4;
    b.u38 = ((func_150ADA68() * 0.1f) + 0.08f) * b.scale;
    b.u3C = ((func_150ADA68() * 0.1f) + 0.08f) * b.scale;
    sp.u88 = ((func_150ADA68() * 60.0f) + 21.0f) * 0.001f;
    obj = func_1513092C(&sp, 2, 0x28);
    if (obj != 0) {
        memcpy(obj + 0xA8, &b, 0x28);
    }
}

void func_150EAE60(s32 arg0) {
    func_150E6060();
}

void func_150EA904(s32 arg0, s32 arg1)
{
  u8 *p;
  p = ((u8 *) D_800DBEF4) + (arg1 * 0xA0);
  if (p[0x72] == 224)
  {
    p[0x73] = (p[0x73] & 0xFFFF) | 3;
  }
}

typedef struct {
    f32 rot[3];
    u8 padC[4];
    s16 u10;
    s16 u12;
    s16 u14;
    u8 pad16[0x3C - 0x16];
    s32 u3C;
    u8 pad40[0x5A - 0x40];
    s16 u5A;
    s16 u5C;
    s16 u5E;
    f32 vel[3];
    u8 pad6C[2];
    s8 u6E;
    u8 pad6F[0x73 - 0x6F];
    u8 u73;
    u8 pad74[0x7C - 0x74];
    s32 u7C;
    u8 pad80[0x8A - 0x80];
    u8 u8A;
} S_EAEC4;
void func_150EAEC4(S_EAEC4 *arg0) {
    f32 f;
    s32 v;

    if ((arg0->u73 & 3) == 3) {
        f = D_800BE9E4;
        arg0->rot[0] += arg0->vel[0] * f;
        if (arg0->rot[0] < 0.0f) {
            arg0->rot[0] += 360.0f;
        } else if (arg0->rot[0] >= 360.0f) {
            arg0->rot[0] -= 360.0f;
        }
        arg0->rot[1] += arg0->vel[1] * f;
        if (arg0->rot[1] < 0.0f) {
            arg0->rot[1] += 360.0f;
        } else if (arg0->rot[1] >= 360.0f) {
            arg0->rot[1] -= 360.0f;
        }
        arg0->rot[2] += arg0->vel[2] * f;
        if (arg0->rot[2] < 0.0f) {
            arg0->rot[2] += 360.0f;
        } else if (arg0->rot[2] >= 360.0f) {
            arg0->rot[2] -= 360.0f;
        }
        arg0->u5C -= arg0->u3C * D_800BE9E4;
        arg0->u10 += arg0->u5A * D_800BE9E4;
        arg0->u7C += arg0->u5C * D_800BE9E4;
        arg0->u12 = arg0->u7C >> 3;
        arg0->u14 += arg0->u5E * D_800BE9E4;
        v = arg0->u8A;
        v -= D_800BE9E4 * 4;
        if (v > 0) {
            arg0->u8A = v;
            return;
        }
        arg0->u6E = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EB090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117D70/func_150EB3A4.s")
