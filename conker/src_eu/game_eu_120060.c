#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_150F2F14(s32 arg0, s32 arg1);
#endif


static const f32 D_800A1CF0_vec[3] = { 0.0f, -45.0f, 0.0f };

s32 func_150F2850(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 var_v0;

    switch (arg2) {
    case 3:
        var_v0 = 0x29;
        break;
    case 4:
        var_v0 = 0x2D;
        break;
    case 5:
        var_v0 = 0x31;
        break;
    case 6:
        var_v0 = 0x35;
        break;
    case 7:
        var_v0 = 0x39;
        break;
    case 8:
        var_v0 = 0x3D;
        break;
    default:
        return 0;
    }
    func_15143134((void *)D_800A1CF0_vec, arg0, *(s32 *)(arg1 + 0x1D4) + (var_v0 << 6));
    return 1;
}

s32 func_150F28FC(s32 arg0, s32 arg1) {
    return 0xE;
}

void func_150F2910(u8 *arg0, int arg1, s32 arg2)
{
  u8 sp1C[12];
  if ((*((s32 *) (arg0 + 0x1D4))) != 0)
  {
    func_150F2850(sp1C, arg0, arg1);
    func_151C384C(sp1C, 0xFF, 0);
  }
}

s32 func_150F2960(u8 *arg0) {
    f32 *temp_s0;

    temp_s0 = (f32 *)(arg0 + 0x170);
    *(f32 *)(arg0 + 0x20) = temp_s0[4] * sinf(*(f32 *)(arg0 + 0x170));
    *(f32 *)(arg0 + 0x28) = temp_s0[5] * sinf(temp_s0[1]);
    temp_s0[0] = func_15144B68((temp_s0[2] * D_800BE9A4) + temp_s0[0]);
    temp_s0[1] = func_15144B68((temp_s0[3] * D_800BE9A4) + temp_s0[1]);
    return 1;
}

s32 func_150F2A00(u8 *arg0) {
    u8 *q = arg0 + 0x50;
    u8 *p = arg0;
    p += *(s32 *)q;
    p += 0xF8;
    *(f32 *)(p + 0x24) = *(f32 *)(p + 0x10) * sinf(*(f32 *)(p + 0));
    *(f32 *)(p + 0x28) = *(f32 *)(p + 0x14) * sinf(*(f32 *)(p + 4));
    *(f32 *)(p + 0) = func_15144B68(*(f32 *)(p + 8) * D_800BE9A4 + *(f32 *)(p + 0));
    *(f32 *)(p + 4) = func_15144B68(*(f32 *)(p + 0xC) * D_800BE9A4 + *(f32 *)(p + 4));
    return 1;
}

void func_150A8050(f32 (*)[4], f32, f32, f32);

s32 func_150F2A98(u8 *arg0, s32 arg1) {
    f32 m[4][4];
    u8 *v;

    v = arg0;
    v += *(s32 *)(arg0 + 0x50);
    v += 0xF8;
    func_150A8050(m, *(f32 *)(v + 0x24), 0.0f, *(f32 *)(v + 0x28));
    m[3][0] = *(f32 *)(v + 0x18);
    m[3][1] = *(f32 *)(v + 0x1C);
    m[3][2] = *(f32 *)(v + 0x20);
    guMtxF2L(m, &((Mtx *)(arg0 + 0x78))[D_800BE9C0]);
    return 1;
}

s32 func_150F2B20(u8 *arg0) {
    u8 **p = (u8 **)(arg0 + 0x18);
    f32 z, y, x;
    f32 m[4][4];

    func_150A8050(m, *(f32 *)(*p + 0x20) * 3.0f, 0.0f, *(f32 *)(*p + 0x28) * 3.0f);
    m[3][0] = *(f32 *)(*p + 0x38);
    m[3][1] = *(f32 *)(*p + 0x3C);
    m[3][2] = *(f32 *)(*p + 0x40);
    func_150A7E40(m, 0.0f, -495.0f, 0.0f, &x, &y, &z);
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0xE) = x;
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x10) = y;
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x12) = z;
    return 1;
}

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);

void func_150F2C20(struct108 *arg0) {
    f32 temp_f0;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v0_2;
    struct127 *temp_v0;

    temp_v0 = arg0->unk3D0;
    if ((temp_v0->unk102 != 0) && (temp_v0->stunned == 0)) {
        func_150F2F14((s32) arg0, 1);
        if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
            if (camera_push_mode(arg0, 0x80, 0, 0, 3) != 0) {
                temp_t2 = arg0->unk84 | 0x300400;
                arg0->unk84 = temp_t2;
                arg0->unk84 = temp_t2 & ~6;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 3;
                camera_apply_zoom_level(arg0);
            }
            arg0->unk348 = 29.0f;
            arg0->unk34C = 29.0f;
            arg0->unk374 = 200.0f;
            arg0->unk190 = -19.0f;
            if (arg0->unk3E8 == 0) {
                temp_f0 = arg0->unk374;
                if ((0.5f * temp_f0) < ((*(f32 *)((u8 *)arg0 + 0x370)) - temp_f0)) {
                    camera_snap_to_object(arg0, arg0->unk3D0);
                }
            }
        }
    } else {
        temp_v0->unk7 = 0xFF;
        if (arg0->unk23E == 0x3B) {
            func_150F2F14((s32) arg0, 1);
            if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
                if (camera_push_mode(arg0, 8, 0, 0, 3) != 0) {
                    temp_t4 = arg0->unk84 | 0x300000;
                    arg0->unk84 = temp_t4;
                    arg0->unk84 = temp_t4 & ~4;
                    arg0->unk1B4 = 1;
                    arg0->unk1E0 = 3;
                }
                arg0->unk134 = 0;
                arg0->unk348 = 125.0f;
                arg0->unk34C = 125.0f;
                arg0->unk374 = 220.0f;
                arg0->unk190 = 30.0f;
            }
        } else {
            temp_v0_2 = arg0->unk2C;
            if (((temp_v0_2 == 8) || (temp_v0_2 == 0x80)) && (arg0->unk6C8 == 0)) {
                camera_pop_mode(arg0, 3);
            }
            if (arg0->unk1B4 == 1) {
                arg0->unk1B4 = 2;
                camera_apply_zoom_level(arg0);
            }
            func_150F2F14((s32) arg0, 0);
        }
    }
    if (func_1509BE40(1, 0x405A, 6, 0x9000) != 0) {
        arg0->unk84 |= 0x80000000;
    } else {
        arg0->unk84 &= 0x7FFFFFFF;
    }
    if (func_1509BE40(1, 0x405E, 6, 0x9000) != 0) {
        arg0->unk84 |= 0x10000;
    } else {
        arg0->unk84 &= 0xFFFEFFFF;
    }
    if (func_1509BE40(1, 0x405F, 6, 0x2000) != 0) {
        arg0->unk84 |= 0x10;
        return;
    }
    arg0->unk84 &= ~0x10;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2C20.s")
#endif
void func_150F2F14(s32 arg0, s32 arg1)
{
  int new_var;
  s32 var_s0;
  var_s0 = 0;
  if (1)
  {
    do
    {
      func_1509BFB0(0, var_s0 + 0x4016, arg1);
      var_s0 += 1;
    }
    while (var_s0 != 0xE);
  }
  new_var = 0x405D; // fakematch: constant in a variable (permuter)
  func_1509BFB0(0, new_var, arg1);
  func_1509BFB0(0, 0x405F, arg1);
  if (D_800D2E4C->pad15[0] & 8)
  {
    func_1509BFB0(0, 0x4063, arg1);
    func_1509BFB0(0, 0x4064, arg1);
    func_1509BFB0(0, 0x4065, arg1);
  }
}
