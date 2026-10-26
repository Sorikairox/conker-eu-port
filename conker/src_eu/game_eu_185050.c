#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A4EA8[];
#endif

void func_1515835C(u8 *, u8 *);

extern s32 (*D_8008B130[])(u8 *);
extern s32 (*D_8008B140[])(u8 *);
void func_15157840(u8 *arg0)
{
  s32 pad;
  u8 done = 0;
  s16 v;
  if (arg0[0x10] & 1)
  {
    *((s16 *) (arg0 + 0x16)) -= D_800BE9E4;
    if ((*((s16 *) (arg0 + 0x16))) < 0)
    {
      done = 1;
    }
  }
  if (!done)
  {
    if ((*((s8 *) (arg0 + 0x11))) != (-1))
    {
      if (!D_8008B130[*((s8 *) (arg0 + 0x11))](arg0))
      {
        done = 1;
      }
    }
    if ((*((s8 *) (arg0 + 0x12))) != (-1))
    {
      if (!D_8008B140[*((s8 *) (arg0 + 0x12))](arg0))
      {
        done = 1;
      }
    }
  }
  if (!done)
  {
    func_1503F7A0(*((s32 *) (arg0 + 0x68)));
  }
  if ((!done) && (arg0[0x10] & 0x20))
  {
    v = *((s16 *) (arg0 + 0x16));
    if (v < (*((s16 *) (arg0 + 0x64))))
    {
      if ((v * (*((s16 *) (arg0 + 0x66)))) < arg0[0x43])
      {
        if (!(v * (*((s16 *) (arg0 + 0x66))))) // fakematch: empty if fixes the multu operand order
        {
        }
        arg0[0x43] = (v * (*((s16 *) (arg0 + 0x66))));
      }
    }
  }
  if (done)
  {
    node_destroy((struct102 *) arg0);
  }
}

#ifdef NON_MATCHING
s32 gfx_set_combine_mode(s32, u8, s8 *);
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
u8 *func_15142FBC(s32, s32, s32, s8 *);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
u8 *func_151462C8(u8 *, u8 *, u8, s32, s32, s32, u8 *, s32, s32);
extern s32 D_80083AD0;
extern s32 D_80083C50;
extern s32 D_80083DD0;
extern s32 D_80083F50;
extern s32 D_8008B15C;
extern s32 D_8008B16C;

s32 *func_15157990(s32 *arg0, u8 *arg1, s16 arg2) {
    struct {
        u8 u71;
        s16 u72;
        s16 u74;
        s16 u76;
        s16 u78;
        s16 u7A;
        s16 u7C;
        s16 u7E;
        s16 u80;
        u8 pad82[0x1];
        s8 u83;
    } sp;
    s32 *temp_v0;
    s32 *temp_v0_4;
    s32 *var_s1;
    s32 temp_s1;
    s32 var_a0;
    s32 var_v0_2;
    s32 var_v1;
    s8 temp_v0_2;
    s8 temp_v0_5;
    u8 temp_v1_2;
    u8 *temp_s1_2;
    u8 *temp_s1_3;
    u8 *temp_s1_4;
    u8 *temp_s1_5;
    u8 *temp_v0_3;
    u8 *temp_v1;
    u8 *var_v0;

    var_s1 = arg0;
    sp.u83 = 1;
    temp_v0_2 = (*(s8 *)((u8 *)arg1 + 0x13));
    if (temp_v0_2 != -1) {
        temp_v0 = (*(s32 (**)())((u8 *)&D_8008B15C + (temp_v0_2 * 4)))(var_s1, arg1, arg2, &sp.u83, &sp.u71);
        var_s1 = temp_v0;
        if (sp.u71 == 0) {
            return temp_v0;
        }
    }
    if (((*(u8 *)((u8 *)arg1 + 0x10)) & 8) && (temp_v0_3 = (*(u8 **)((u8 *)arg1 + 0x60)), (temp_v0_3 != NULL)) && !((*(s16 *)((u8 *)temp_v0_3 + 2)) & (1 << arg2))) {

    } else {
        temp_s1 = func_15142B7C(var_s1, (*(s32 *)((u8 *)arg1 + 0x24)), (*(s32 *)((u8 *)arg1 + 0x28)));
        func_151441A4(&sp.u80, &sp.u7E, &sp.u7C, &sp.u7A, (s32) (*(u8 *)((u8 *)arg1 + 0x40)), (s32) (*(u8 *)((u8 *)arg1 + 0x41)), (s32) (*(u8 *)((u8 *)arg1 + 0x42)), (s32) (*(u8 *)((u8 *)arg1 + 0x43)), (s32) (*(u8 *)((u8 *)arg1 + 0x44)), (s32) (*(u8 *)((u8 *)arg1 + 0x45)), (s32) (*(u8 *)((u8 *)arg1 + 0x46)), (s32) (*(u8 *)((u8 *)arg1 + 0x47)), 0xFF, (s32) (*(s8 *)((u8 *)arg1 + 0x3C)));
        func_151442FC(&sp.u78, &sp.u76, &sp.u74, &sp.u72, (s32) (*(u8 *)((u8 *)arg1 + 0x40)), (s32) (*(u8 *)((u8 *)arg1 + 0x41)), (s32) (*(u8 *)((u8 *)arg1 + 0x42)), (s32) (*(u8 *)((u8 *)arg1 + 0x43)), (s32) (*(u8 *)((u8 *)arg1 + 0x44)), (s32) (*(u8 *)((u8 *)arg1 + 0x45)), (s32) (*(u8 *)((u8 *)arg1 + 0x46)), (s32) (*(u8 *)((u8 *)arg1 + 0x47)), 0xFF, (s32) (*(s8 *)((u8 *)arg1 + 0x3D)));
        temp_v1 = ((*(s32 *)((u8 *)arg1 + 0x2C)) * 8) + ((u8 *)&D_800A4EA8);
        var_v0 = func_15142FBC(gfx_set_combine_mode(func_15142CF0(func_15142C10(temp_s1, sp.u78, sp.u76, sp.u74, (s32) sp.u72, &sp.u83), 0, 0, sp.u80, (s32) sp.u7E, (s32) sp.u7C, (s32) sp.u7A, &sp.u83), (*(u8 *)((u8 *)arg1 + 0x33)), &sp.u83), (*(s32 *)((u8 *)arg1 + 0x20)) | 0x80000 | 0x2C00 | (*(s32 *)((u8 *)arg1 + 0x34)) | (*(s32 *)((u8 *)arg1 + 0x38)), (*(s32 *)((u8 *)temp_v1 + 4)) | (*(s32 *)((u8 *)temp_v1 + 0)), &sp.u83);
        temp_v1_2 = (*(u8 *)((u8 *)arg1 + 0x10));
        if (temp_v1_2 & 2) {
            if (temp_v1_2 & 4) {
                var_v0_2 = 1;
            } else {
                var_v0_2 = 0;
            }
            var_v0 = func_151462C8(var_v0, arg1 + 0xFC, (*(u8 *)((u8 *)arg1 + 0x51)), (*(s32 *)((u8 *)arg1 + 0x4C)), (s32) (*(u8 *)((u8 *)arg1 + 0x50)), (s32) arg2, arg1 + 0x54, var_v0_2, 0);
        }
        (*(s32 *)((u8 *)var_v0 + 0)) = 0xE7000000;
        temp_s1_2 = var_v0 + 8;
        (*(s32 *)((u8 *)var_v0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_s1_2 + 4)) = 0xFF;
        (*(s32 *)((u8 *)temp_s1_2 + 0)) = 0xF8000000;
        temp_s1_3 = temp_s1_2 + 8;
        (*(s32 *)((u8 *)temp_s1_3 + 0)) = 0xDB06000C;
        temp_s1_4 = temp_s1_3 + 8;
        (*(s32 *)((u8 *)temp_s1_3 + 4)) = (s32) (*(s32 *)((u8 *)(((*(s32 *)((u8 *)arg1 + 0x68)) + (D_800BE9C0 * 4))) + 0x3E8));
        (*(s32 *)((u8 *)temp_s1_4 + 0)) = 0xDB060004;
        temp_s1_5 = temp_s1_4 + 8;
        (*(s32 *)((u8 *)temp_s1_4 + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 0x74));
        var_a0 = 0;
        if (((s32) (*(u8 *)((u8 *)arg1 + 0x43)) < 0xFF) || ((s32) (*(u8 *)((u8 *)arg1 + 0x47)) < 0xFF)) {
            (*(s32 *)((u8 *)temp_s1_5 + 0)) = 0xDB060020;
            var_s1 = temp_s1_5 + 8;
            if ((*(u8 *)((u8 *)arg1 + 0x10)) & 0x40) {
                (*(s32 **)((u8 *)temp_s1_5 + 4)) = &D_80083DD0;
            } else {
                (*(s32 **)((u8 *)temp_s1_5 + 4)) = &D_80083AD0;
            }
        } else {
            (*(s32 *)((u8 *)temp_s1_5 + 0)) = 0xDB060020;
            var_s1 = temp_s1_5 + 8;
            if ((*(u8 *)((u8 *)arg1 + 0x10)) & 0x40) {
                (*(s32 **)((u8 *)temp_s1_5 + 4)) = &D_80083F50;
            } else {
                (*(s32 **)((u8 *)temp_s1_5 + 4)) = &D_80083C50;
            }
        }
        var_v1 = 0;
        if ((s32) (*(u8 *)((u8 *)arg1 + 0x70)) > 0) {
            do {
                temp_v0_4 = var_s1;
                (*(s32 *)((u8 *)temp_v0_4 + 0)) = 0xDE000000;
                var_s1 += 2;   /* one 8-byte Gfx */
                (*(s32 *)((u8 *)temp_v0_4 + 4)) = (s32) *(s32 *)((*(s32 *)((u8 *)arg1 + 0x6C)) + var_a0);
                var_v1 += 1;
                var_a0 += 4;
            } while (var_v1 < (s32) (*(u8 *)((u8 *)arg1 + 0x70)));
        }
        temp_v0_5 = (*(s8 *)((u8 *)arg1 + 0x14));
        if (temp_v0_5 != -1) {
            var_s1 = (*(s32 (**)())((u8 *)&D_8008B16C + (temp_v0_5 * 4)))(var_s1, arg1, arg2, &sp.u83);
        }
    }
    return var_s1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_15157990.s")
#endif
s32 func_15157DD0(s32 arg0) {
    guMtxIdentF(&((f32 (*)[16])(arg0 + 0x7C))[D_800BE9C0]);
    return 1;
}

s32 func_15157580(s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_15157E08(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    u8 *v = func_15157580(arg0, arg2, arg3, arg4, arg5, arg6 + 0x38, arg7, arg8);
    if (v == NULL) {
        return 0;
    }
    memcpy(v + 0x120, arg1, 0x38);
    return v;
}

#define MTX_7E88(a) (((f32 (*)[16])((a) + 0x7C))[D_800BE9C0])
s32 func_15157E88(u8 *arg0) {
    u8 *p;

    mtxf_rotate_xyz_deg(&MTX_7E88(arg0), *(f32 *)(arg0 + 0x120), *(f32 *)(arg0 + 0x124), *(f32 *)(arg0 + 0x128));
    p = arg0 + 0x120;
    MTX_7E88(arg0)[12] = *(f32 *)(arg0 + 0x54);
    MTX_7E88(arg0)[13] = *(f32 *)(arg0 + 0x58);
    do {} while (0); // fakematch: block split keeps p live in a0
    MTX_7E88(arg0)[14] = *(f32 *)(arg0 + 0x5C);
    MTX_7E88(arg0)[0] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[1] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[2] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[4] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[5] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[6] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[8] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[9] *= *(f32 *)(p + 0xC);
    MTX_7E88(arg0)[10] *= *(f32 *)(p + 0xC);
    return 1;
}
#undef MTX_7E88

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3_15158018;

s32 func_15158018(u8 *arg0) {
    u8 *p = arg0 + 0x120;
    V3_15158018 old;
    s32 i;
    f32 g;
    f32 dx;
    f32 dz;

    if (p[0x30] & 1) {
        old = *(V3_15158018 *)(p + 0x10);
        if (p[0x30] & 8) {
            for (i = D_800BE9E4; i != 0; i--) {
                *(f32 *)(p + 0x10) *= *(f32 *)(p + 0x2C);
                *(f32 *)(p + 0x18) *= *(f32 *)(p + 0x2C);
            }
        }
        if (p[0x30] & 4) {
            *(f32 *)(p + 0x14) += *(f32 *)(p + 0x28) * D_800BE9A4;
            g = *(f32 *)(p + 0x28);
        } else {
            g = 0.0f;
        }
        dx = (*(f32 *)(p + 0x10) - old.x) * D_800BEDC8;
        dz = (*(f32 *)(p + 0x18) - old.z) * D_800BEDC8;
        *(f32 *)(arg0 + 0x54) += (old.x + 0.5f * dx * D_800BE9A4) * D_800BE9A4;
        *(f32 *)(arg0 + 0x58) += (old.y + 0.5f * g * D_800BE9A4) * D_800BE9A4;
        *(f32 *)(arg0 + 0x5C) += (old.z + 0.5f * dz * D_800BE9A4) * D_800BE9A4;
    }
    if (p[0x30] & 2) {
        *(f32 *)(p + 0x0) += *(f32 *)(p + 0x1C) * D_800BE9A4;
        *(f32 *)(p + 0x4) += *(f32 *)(p + 0x20) * D_800BE9A4;
        *(f32 *)(p + 0x8) += *(f32 *)(p + 0x24) * D_800BE9A4;
    }
    return 1;
}

void func_151582F8(s32 arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, arg0 + 0x4C, arg0 + 0x50, arg0);
}

s32 func_15158338(s32 arg0) {
    func_1515835C(arg0, arg0 + 0x120);
    return 1;
}

#define MTX_835C(a) (((f32 (*)[16])((a) + 0x7C))[D_800BE9C0])
void func_1515835C(u8 *arg0, u8 *arg1) {
    mtxf_rotate_xyz_deg(&MTX_835C(arg0), ((f32 *)arg1)[0], ((f32 *)arg1)[1], ((f32 *)arg1)[2]);
    MTX_835C(arg0)[12] = ((f32 *)arg0)[0x54 / 4];
    MTX_835C(arg0)[13] = ((f32 *)arg0)[0x58 / 4];
    MTX_835C(arg0)[14] = ((f32 *)arg0)[0x5C / 4];
    MTX_835C(arg0)[0] *= ((f32 *)arg1)[3];
    MTX_835C(arg0)[1] *= ((f32 *)arg1)[3];
    MTX_835C(arg0)[2] *= ((f32 *)arg1)[3];
    MTX_835C(arg0)[4] *= ((f32 *)arg1)[4];
    MTX_835C(arg0)[5] *= ((f32 *)arg1)[4];
    MTX_835C(arg0)[6] *= ((f32 *)arg1)[4];
    MTX_835C(arg0)[8] *= ((f32 *)arg1)[3];
    MTX_835C(arg0)[9] *= ((f32 *)arg1)[3];
    MTX_835C(arg0)[10] *= ((f32 *)arg1)[3];
}
#undef MTX_835C

Gfx *func_151584F0(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gdl++, &D_800DD040[arg2 * 64], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    *arg4 = 1;
    return gdl;
}

extern Mtx *D_800DC6D0[];

Gfx *func_15158558(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3) {
    gSPMatrix(gdl++, (u8 *)D_800BE628 + arg2 * 0x180 + (D_800BE9C0 << 6) + 0x100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gdl++, (u8 *)D_800DC6D0[D_800BE9C0] + (arg2 << 6), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    return gdl;
}

void func_151585E8(s32 arg0, u8 arg1) {
    node_broadcast_types(D_800A6440, 3, arg0, arg1);
}
