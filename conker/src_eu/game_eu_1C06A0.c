#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15192E90(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(0x23, -1, 0x14, 1, 0x10, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_1515C668(void *, f32 **);
extern f32 D_800BE9A4;
void func_15192F14(u8 *arg0) {
    u8 *p;
    s32 r; // fakematch: unused, keeps the s100 frame layout (two scalars above the struct)
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x8];
    } sp;
    s32 obj;
    f32 scale;
    f32 *out;
    u8 a;

    p = arg0 + 0x28;
    *(f32 *)(p + 8) += (312.0f + random_float() * 599.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 8) > 1.0f) {
        if (func_1515C668(*(u8 **)p, &out) != 0) {
            sp.u51 = 0x29;
            sp.u3C = 0xE03;
            sp.u34 = 0x200005;
            sp.u4C = 0xB0;
            sp.u4D = 0xA0;
            sp.u4E = 0x2A;
            sp.u48 = 0x40;
            sp.u49 = 0xB;
            sp.u4A = 0x6A;
            sp.u38 = 0;
            sp.u40 = 0;
            sp.u44 = 0;
            sp.u4B = 0xFF;
            sp.u50 = 0xFF;
            sp.u94 = 3;
            sp.u95 = 3;
            sp.u8C = 0xE05;
            sp.u96 = 0xA;
            sp.u97 = -1;
            sp.u52 = 0x14;
            sp.u54 = 0xC;
            sp.u56 = 0x23;
            sp.u88 = 0.0f;
            sp.u58 = 1.04f;
            scale = 0.95000005f;
            do {
                a = random_int() & 1;
                sp.u3E = (random_int() % 31U) + 0x14;
                sp.u4F = (random_int() % 156U) + 0x64;
                sp.u5C = sp.u60 = (random_float() * 150.0f) + 100.0f;
                func_15143874(*(u16 *)(*(u8 **)p + 0x7A) >> 8, a ? 20.0f : -20.0f, &sp.u64[0], &sp.u64[2]);
                sp.u64[0] += *(f32 *)(*(u8 **)p + 0x14);
                sp.u64[2] += *(f32 *)(*(u8 **)p + 0x1C);
                sp.u64[1] = *(f32 *)(*(u8 **)p + 0x180) + 20.0f;
                sp.u8C &= ~0xC0;
                if (random_int() & 1) {
                    sp.u8C |= 0x40;
                }
                if (random_int() & 1) {
                    sp.u8C |= 0x80;
                }
                sp.u7C[0] = out[0] * -1.516f;
                sp.u7C[1] = out[1] * -1.516f;
                sp.u7C[2] = out[2] * -1.516f;
                obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
                if (obj != 0) {
                    memcpy(obj + 0xA8, &scale, 4);
                }
                *(f32 *)(p + 8) -= 1.0f;
            } while (*(f32 *)(p + 8) > 1.0f);
        }
    }
}

struct260 *func_151932B8(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(arg1, -1, 0x18, 1, 0x16, 0xC, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
    return temp_v0;
}

void func_15143794(s16, s16, f32, void *);
void func_15193360(u8 *arg0) {
    u8 *p;
    s32 r;
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x8];
    } sp;
    s32 obj;
    f32 scale;
    s16 base;
    f32 v[3];
    s16 ang;

    p = arg0 + 0x28;
    *(f32 *)(p + 8) += (792.0f + random_float() * 1202.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 8) > 1.0f) {
        if (*(s32 *)(*(u8 **)p + 0x1D4) == 0) {
            while (*(f32 *)(p + 8) > 1.0f) {
            }
        } else {
            base = (*(u16 *)(*(u8 **)p + 0x7A) >> 8) + 0x40;
            sp.u51 = 0x29;
            sp.u3C = 0xE03;
            sp.u34 = 0x200005;
            sp.u4C = 0xB0;
            sp.u4D = 0xA0;
            sp.u4E = 0x2A;
            sp.u48 = 0x40;
            sp.u49 = 0xB;
            sp.u4A = 0x6A;
            sp.u38 = 0;
            sp.u40 = 0;
            sp.u44 = 0;
            sp.u4B = 0xFF;
            sp.u50 = 0xFF;
            sp.u94 = 3;
            sp.u95 = 3;
            sp.u8C = 0xE05;
            sp.u96 = 0xA;
            sp.u97 = -1;
            sp.u52 = 0x19;
            sp.u54 = 0xA;
            sp.u56 = 0x23;
            sp.u88 = 0.0f;
            sp.u58 = 1.02f;
            scale = 0.9709f;
            do {
                ang = (random_int() % 51U) - 0x82;
                v[0] = (random_float() * 20.0f) + 30.0f;
                v[1] = (random_float() * 60.0f) + -20.0f;
                v[2] = 0.0f;
                if (random_int() & 1) {
                    v[0] = -v[0];
                    ang = ang + base;
                } else {
                    ang = base - ang;
                }
                sp.u3E = (random_int() % 11U) + 0x1E;
                sp.u4F = (random_int() % 101U) + 0x64;
                sp.u5C = sp.u60 = (random_float() * 150.0f) + 100.0f;
                func_15143134(v, sp.u64, *(s32 *)(*(u8 **)p + 0x1D4) + 0x40);
                r = random_int();
                func_15143794(ang, (s16)((u32)r % 28U - 0x19), random_float() * 3998.0f * 0.001f, sp.u7C);
                sp.u8C &= ~0xC0;
                if (random_int() & 1) {
                    sp.u8C |= 0x40;
                }
                if (random_int() & 1) {
                    sp.u8C |= 0x80;
                }
                obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
                if (obj != 0) {
                    memcpy(obj + 0xA8, &scale, 4);
                }
                *(f32 *)(p + 8) -= 1.0f;
            } while (*(f32 *)(p + 8) > 1.0f);
        }
    }
}

void func_151937A4(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            node_destroy(arg0);
        }
    }
}

void func_15193850(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 new_var;
  u8 *v = arg0 + 0x28;
  if (arg2 == 0x2D)
  {
    if (arg1[0] == (*((s32 *) v)))
    {
      *((s32 *) v) = arg1[1];
      v[4] = ((u8 *) arg1)[9];
    }
    else
    {
      if (arg1[1] == (*((s32 *) v)))
      {
        *((s32 *) v) = arg1[0];
        v[4] = ((u8 *) arg1)[8];
 } dummy_label_982087: ; // fakematch: unused label
      ;
    }
  }
  else
    if (arg2 == 0)
  {
    new_var = arg1[0]; // fakematch: new_var pins the load order
    if (((*((s32 *) v)) == new_var) || ((v[4] ^ 0) == ((u8 *) arg1)[4])) // fakematch: ^ 0 operand order
    {
      node_destroy(arg0);
    }
  }
}
