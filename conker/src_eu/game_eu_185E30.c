#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A4EA8[];
#endif

void func_15158F90(u8 *arg0);


s32 func_1515D9B0(void);
s32 func_1515D9F0(s32);
void *memcpy(void *, const void *, u32);

s32 func_15158620(s32 src, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    u8 *p;
    s32 i;

    p = node_alloc(arg3 ? 0x55 : 0x37, arg6, arg4 + 0xF8, 1, arg5, 1);
    if (p == NULL) {
        return 0;
    }
    memcpy(p + 0x10, (void *)src, 0x44);
    *(s32 *)(p + 0xD8) = arg1;
    *(s32 *)(p + 0xF4) = arg2;
    p[0xDC] = 0;
    for (i = 0; i < 4; i++) {
        ((s32 *)(p + 0xE0))[i] = 0;
    }
    *(s32 *)(p + 0xF0) = 0;
    if (arg1 != 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            ((s32 *)(p + 0xE0))[i] = func_1515D9F0(arg1);
        }
        *(s32 *)(p + 0xF0) = func_1515D9B0();
    }
    return (s32)p;
}

s32 func_15158620(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

void func_15158748(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_15158620(arg0, 0, 0, arg1, arg2, arg3, arg4);
}

extern s32 (*D_8008B1A0[])(void);
void func_15158794(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0x10] & 1) != 0) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0x12) != -1) && (D_8008B1A0[*(s8 *)(arg0 + 0x12)]() == 0)) {
        ret = 1;
    }
    if (ret) {
        node_destroy(arg0);
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
extern s32 D_8008B1AC;
extern s32 D_8008B358;

u8 *func_15158838(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s8 u5B;
        s16 u5C;
        s16 u5E;
        s16 u60;
        s16 u62;
        s16 u64;
        s16 u66;
        s16 u68;
        s16 u6A;
    } sp;
    s32 temp_s1_2;
    s32 var_v0;
    s8 temp_v0;
    u8 temp_v1_2;
    u8 *temp_s1;
    u8 *temp_v1;
    u8 *var_s1;

    sp.u5B = 1;
    temp_v0 = (*(s8 *)((u8 *)arg1 + 0x13));
    if (temp_v0 != -1) {
        if ((*(s32 (**)())((u8 *)&D_8008B1AC + (temp_v0 * 4)))(arg1 + (D_800BE9C0 << 6) + 0x58, arg1) == 0) {
            return arg0;
        }
        goto block_3;
    }
block_3:
    temp_s1_2 = func_15142B7C(arg0, (*(s32 *)((u8 *)arg1 + 0x1C)), (*(s32 *)((u8 *)arg1 + 0x20)));
    func_151441A4(&sp.u6A, &sp.u68, &sp.u66, &sp.u64, (s32) (*(u8 *)((u8 *)arg1 + 0x3C)), (s32) (*(u8 *)((u8 *)arg1 + 0x3D)), (s32) (*(u8 *)((u8 *)arg1 + 0x3E)), (s32) (*(u8 *)((u8 *)arg1 + 0x3F)), (s32) (*(u8 *)((u8 *)arg1 + 0x38)), (s32) (*(u8 *)((u8 *)arg1 + 0x39)), (s32) (*(u8 *)((u8 *)arg1 + 0x3A)), (s32) (*(u8 *)((u8 *)arg1 + 0x3B)), 0xFF, (s32) (*(s8 *)((u8 *)arg1 + 0x34)));
    func_151442FC(&sp.u62, &sp.u60, &sp.u5E, &sp.u5C, (s32) (*(u8 *)((u8 *)arg1 + 0x3C)), (s32) (*(u8 *)((u8 *)arg1 + 0x3D)), (s32) (*(u8 *)((u8 *)arg1 + 0x3E)), (s32) (*(u8 *)((u8 *)arg1 + 0x3F)), (s32) (*(u8 *)((u8 *)arg1 + 0x38)), (s32) (*(u8 *)((u8 *)arg1 + 0x39)), (s32) (*(u8 *)((u8 *)arg1 + 0x3A)), (s32) (*(u8 *)((u8 *)arg1 + 0x3B)), 0xFF, (s32) (*(s8 *)((u8 *)arg1 + 0x35)));
    temp_v1 = ((*(s32 *)((u8 *)arg1 + 0x24)) * 8) + ((u8 *)&D_800A4EA8);
    temp_v1_2 = (*(u8 *)((u8 *)arg1 + 0x10));
    var_s1 = func_15142FBC(gfx_set_combine_mode(func_15142CF0(func_15142C10(temp_s1_2, sp.u62, sp.u60, sp.u5E, (s32) sp.u5C, &sp.u5B), 0, 0, sp.u6A, (s32) sp.u68, (s32) sp.u66, (s32) sp.u64, &sp.u5B), (*(u8 *)((u8 *)arg1 + 0x2B)), &sp.u5B), (*(s32 *)((u8 *)arg1 + 0x18)) | 0x80000 | 0x2C00 | (*(s32 *)((u8 *)arg1 + 0x2C)) | (*(s32 *)((u8 *)arg1 + 0x30)), (*(s32 *)((u8 *)temp_v1 + 4)) | (*(s32 *)((u8 *)temp_v1 + 0)), &sp.u5B);
    if (temp_v1_2 & 2) {
        if (temp_v1_2 & 4) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        var_s1 = func_151462C8(var_s1, arg1 + 0xD8, (*(u8 *)((u8 *)arg1 + 0x45)), (*(s32 *)((u8 *)arg1 + 0x40)), (s32) (*(u8 *)((u8 *)arg1 + 0x44)), (s32) arg2, arg1 + 0x48, var_v0, 0);
    }
    (*(s32 *)((u8 *)var_s1 + 0)) = 0xDA380003;
    temp_s1 = var_s1 + 8;
    (*(u8 **)((u8 *)var_s1 + 4)) = (u8 *) (arg1 + (D_800BE9C0 << 6) + 0x58);
    (*(s32 *)((u8 *)temp_s1 + 0)) = 0xDE000000;
    (*(s32 *)((u8 *)temp_s1 + 4)) = (s32) *(((s32 *)((u8 *)&D_8008B358 + ((*(u8 *)((u8 *)arg1 + 0x16)) * 4))));
    return temp_s1 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158838.s")
#endif
s32 func_15158AFC(Mtx *arg0, u8 *arg1) {
    f32 *r;
    f32 mf[4][4];

    r = (f32 *)(arg1 + 0xF8);
    mtxf_rotate_xyz_deg(mf, r[0], r[1], r[2]);
    mf[3][0] = *(f32 *)(arg1 + 0x48);
    mf[3][1] = *(f32 *)(arg1 + 0x4C);
    mf[3][2] = *(f32 *)(arg1 + 0x50);
    mf[0][0] *= r[3];
    mf[0][1] *= r[3];
    mf[0][2] *= r[3];
    mf[1][0] *= r[3];
    mf[1][1] *= r[3];
    mf[1][2] *= r[3];
    mf[2][0] *= r[3];
    mf[2][1] *= r[3];
    mf[2][2] *= r[3];
    guMtxF2L(mf, arg0);
    return 1;
}

#ifdef NON_MATCHING
s32 func_15158BF4(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x4];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f18;
    f32 var_f16;
    f32 var_f18;
    f32 var_f18_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    (*(f32 *)((u8 *)(&sp.u20) + 0)) = (*(f32 *)((u8 *)arg0 + 0x108));
    (*(s32 *)((u8 *)(&sp.u20) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10C));
    (*(s32 *)((u8 *)(&sp.u20) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x110));
    var_v0 = D_800BE9E4;
    if (var_v0 != 0) {
        temp_a2 = -(var_v0 & 3);
        temp_a1 = temp_a2 + var_v0;
        if (temp_a2 != 0) {
            temp_v1 = arg0 + 0xF8;
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x2C));
            var_v0 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0;
            if (temp_a1 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0x10)) = var_f18;
                    (*(f32 *)((u8 *)temp_v1 + 0x18)) = var_f16;
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0x10)) * temp_f0;
                    var_v0 -= 1;
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 0x18)) * temp_f0;
                } while (temp_a1 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0x10)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 0x18)) = var_f16;
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_v1_2 = arg0 + 0xF8;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1_2 + 0x2C));
            var_v0_2 = var_v0 - 4;
            var_f18_2 = (*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = var_f18_2;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2);
                    var_f18_2 = (*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = var_f18_2;
            (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x10)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0x18)) * temp_f0_2);
        }
    }
    temp_v1_3 = arg0 + 0xF8;
    temp_f18 = (*(f32 *)((u8 *)temp_v1_3 + 0x28));
    (*(f32 *)((u8 *)temp_v1_3 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x14)) + (temp_f18 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + ((sp.u20 + (0.5f * (((*(f32 *)((u8 *)temp_v1_3 + 0x10)) - sp.u20) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x4C)) + ((sp.u24 + (0.5f * temp_f18 * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) + ((sp.u28 + (0.5f * (((*(f32 *)((u8 *)temp_v1_3 + 0x18)) - sp.u28) * D_800BEDC8) * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_v1_3 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x1C)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x20)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_v1_3 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 8)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x24)) * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158BF4.s")
#endif
typedef struct { f32 m[4][4]; } MtxF_s82;
extern MtxF_s82 D_8008B1B8;

s32 func_15158E90(Mtx *arg0, u8 *arg1) {
    f32 s;
    u8 *p;
    MtxF_s82 mf;

    p = arg1;
    mf = D_8008B1B8;
    s = *(f32 *)(p + 0xF8) * 0.003921569f;
    mf.m[3][0] = *(f32 *)(p + 0x48);
    mf.m[3][1] = *(f32 *)(p + 0x4C);
    mf.m[3][2] = *(f32 *)(p + 0x50);
    mf.m[0][0] *= s;
    mf.m[0][1] *= s;
    mf.m[0][2] *= s;
    mf.m[1][0] *= s;
    mf.m[1][1] *= s;
    mf.m[1][2] *= s;
    mf.m[2][0] *= s;
    mf.m[2][1] *= s;
    mf.m[2][2] *= s;
    guMtxF2L(mf.m, arg0);
    return 1;
}

void func_15158F90(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0xE0))[i]) {
            func_100043B4(((s32 *)(arg0 + 0xE0))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0xF0) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0xF0), 4);
    }
}

void func_15159014(void *arg0) {
    func_15158F90(arg0);
    node_retire(arg0);
}

void func_15159040(void *arg0) {
    func_15158F90(arg0);
    node_unlink_free(arg0);
}

s32 func_1515906C(u8 *arg0) {
    s32 temp_v1;
    if (*(s16 *)(arg0 + 0x14) < *(s16 *)(arg0 + 0xF8)) {
        temp_v1 = *(s32 *)(arg0 + 0xFC) * *(s16 *)(arg0 + 0x14);
        if (temp_v1 < arg0[0x3B]) {
            arg0[0x3B] = temp_v1;
        }
    }
    return 1;
}

void func_151590AC(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 a;
  if (arg2 == 0x2D) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x40)) {
      *(s32 *)(arg0 + 0x40) = arg1[1];
      arg0[0x44] = ((u8 *)arg1)[9];
      return;
    }
    if (arg1[1] == *(s32 *)(arg0 + 0x40)) {
      s32 *p = (s32 *)(arg0 + 0x40); // a declaration in the arm = basic-block boundary (unfilled jr ra delay slot, s69)
      *p = a;
      arg0[0x44] = ((u8 *)arg1)[8];
    }
    return;
  }
  if (arg2 == 0) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x40) || arg0[0x44] == ((u8 *)arg1)[4]) {
      *(s32 *)(arg0 + 0x40) = 0;
      arg0[0x44] = 0;
    }
  }
}

s32 func_151598E0(u8 *, u8 *, u8 *);

u8 *func_15159140(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *p;

    if (arg0 == NULL) {
        return NULL;
    }
    p = node_alloc(0x2E, 0, arg2 + 0x58, 1, 0xFF, 1);
    if (p == NULL) {
        return NULL;
    }
    *(u8 **)(p + 0x18) = arg0;
    p[0x1C] = arg0[0x3B];
    p[0x2C] = 2;
    p[0x2D] = 2;
    p[0x2E] = 2;
    p[0x2F] = 3;
    p[0x30] = 0;
    *(f32 *)(p + 0x20) = *(f32 *)(arg0 + 0x14);
    *(f32 *)(p + 0x24) = *(f32 *)(arg0 + 0x18);
    *(f32 *)(p + 0x28) = *(f32 *)(arg0 + 0x1C);
    p[0x31] = 0;
    if (arg1 != 0) {
        p[0x31] |= 1;
    }
    *(s32 *)(p + 0x10) = 1;
    *(s32 *)(p + 0x14) = 0;
    if (func_151598E0(arg0, p + 0x1D, p) == 0) {
        node_delete((struct102 *)p);
        return NULL;
    }
    p[0x50] = 0;
    return p;
}

void func_15159244(void **arg0) {
    func_1514EDF0(arg0, arg0[0x18 / 4]);
    node_retire(arg0);
}
