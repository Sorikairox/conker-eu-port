#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 memcpy(u8 *, s32, s32);
extern f32 D_800AA770;

u8 *func_151B3660(s32 arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 *temp_v0;
    f32 temp_f0;
    u8 *sp24;

    temp_v0 = func_15167A68(0x33, arg4, arg2 + 0x150, 1, (u8) (s32) arg3, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x10, arg0, 0x38);
    temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x38));
    (*(u8 *)((u8 *)temp_v0 + 0x10)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x10)) | 0xE);
    (*(f32 *)((u8 *)temp_v0 + 0x138)) = (f32) (2.0f * ((temp_f0 * temp_f0) / D_800AA770));
    (*(s32 *)((u8 *)temp_v0 + 0x13C)) = (s32) (temp_f0 * arg1 * 4096.0f);
    bzero(temp_v0 + 0x140, 0x10);
    return sp24;
}

typedef struct { u8 pad0[0x10]; u8 flags; u8 pad11; s16 y; f32 x14[3]; f32 x20[3]; s8 x2C; s8 x2D; u8 pad2E[6]; s8 x34; } Obj_151B3734;
extern s32 (*D_8008FE90[])(Obj_151B3734 *, f32 *, s32);
extern s32 (*D_8008FE98[])(Obj_151B3734 *);
void func_151B3734(Obj_151B3734 *arg0) {
    s32 pad; // fakematch: moves the byte spill slot
    u8 done = 0;

    if (arg0->flags & 1) {
        arg0->y -= D_800BE9E4;
        if (arg0->y < 0) {
            done = 1;
        }
    }
    if (!done) {
        if (arg0->x2C != -1) {
            if (!D_8008FE90[arg0->x2C](arg0, arg0->x14, 1)) {
                done = 1;
            }
        }
        if (arg0->x2D != -1) {
            if (!D_8008FE90[arg0->x2D](arg0, arg0->x20, 0)) {
                done = 1;
            }
        }
        if ((arg0->flags & 4) || (arg0->flags & 8)) {
            arg0->flags |= 2;
        } else if (arg0->x34 != -1) {
            if (!D_8008FE98[arg0->x34](arg0)) {
                done = 1;
            }
        }
    }
    if (done) {
        func_1516972C((struct102 *)arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B3878.s")

void func_151B3FE4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008FF08[arg0[0x44]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B402C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B42A0.s")

extern f32 D_800AA78C;
s32 func_151B44D8(u8 *arg0, f32 *arg1, u8 arg2)
{
  s32 var_v1 = 1;
  u8 *p;
  if (arg2 != 0) {
    u8 *o;
    f32 *dst = arg1;
    p = arg0 + 0x150;
    if (**(s32 **)(arg0 + 0x150) != 0 && p[4] == (o = *(u8 **)p)[0x3B]) {
      dst[0] = *(f32 *)(o + 0x14);
      dst[1] = *(f32 *)(*(u8 **)p + 0x18);
      dst[2] = *(f32 *)(*(u8 **)p + 0x1C);
      arg0[0x10] &= 0xFFFB;
    } else {
      var_v1 = 0;
      arg0[0x10] |= 0xC;
    }
  } else {
    arg1[0] = 0.0f;
    arg1[1] = D_800AA78C;
    arg1[2] = 0.0f;
    arg0[0x10] &= 0xFFF7;
  }
  return var_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B458C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4D88.s")

#ifdef NON_MATCHING
s32 func_151B4E8C(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 var_f14;
    s32 var_v0;
    u8 *var_v1;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x48)) = temp_f0;
    (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x50)) = 0.0f;
    var_v0 = 2;
    temp_f12 = -(temp_f0 - (*(f32 *)((u8 *)arg0 + 0x20))) * 0.1f;
    var_v1 = arg0 + 0x30;
    (*(f32 *)((u8 *)arg0 + 0x68)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x64)) = 0.0f;
    temp_f14 = temp_f0 + temp_f12;
    (*(f32 *)((u8 *)arg0 + 0x60)) = temp_f14;
    var_f14 = temp_f14 + temp_f12;
    do {
        (*(f32 *)((u8 *)var_v1 + 0x48)) = var_f14;
        (*(f32 *)((u8 *)var_v1 + 0x4C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x50)) = 0.0f;
        temp_f14_2 = var_f14 + temp_f12;
        var_v0 += 4;
        (*(f32 *)((u8 *)var_v1 + 0x64)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x68)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x60)) = temp_f14_2;
        temp_f14_3 = temp_f14_2 + temp_f12;
        (*(f32 *)((u8 *)var_v1 + 0x7C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x80)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x94)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x78)) = temp_f14_3;
        temp_f14_4 = temp_f14_3 + temp_f12;
        (*(f32 *)((u8 *)var_v1 + 0x98)) = 0.0f;
        var_v1 += 0x60;
        (*(f32 *)((u8 *)var_v1 + 0x30)) = temp_f14_4;
        var_f14 = temp_f14_4 + temp_f12;
    } while (var_v0 != 0xA);
    (*(u8 *)((u8 *)arg0 + 0x10)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x10)) & 0xFFFD);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B4E8C.s")
#endif
s32 func_151B4F3C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s8 *argC, s8 *argD) {
    *arg1 = 0x220005;
    *arg2 = 0x40600;
    *arg3 = 0xFF;
    *arg4 = 0xFF;
    *arg5 = 0xFF;
    *arg6 = 0xFF;
    *arg7 = 0xFF;
    *arg8 = 0xFF;
    *arg9 = 0xFF;
    *argA = 0xFF;
    *argB = 0;
    *argC = 5;
    *argD = 0x2B;
    return 1;
}

s32 func_1502EF24(u8 *, s32 *, s32 *, s32 *, s32 *);
u8 func_151B4FC4(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s8 *argC, s8 *argD) {
    u8 ret;
    s32 pad[2]; // fakematch: frame slots between ret and t
    u8 *t;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    u32 sp48; // fakematch: unsigned puts the copy in v0
    s32 v;
    s32 pad2; // fakematch: frame slot below sp48

    ret = 1;
    t = *(u8 **)(arg0 + 0x150);
    func_1502EF24(t, &sp54, &sp50, &sp4C, (s32 *)&sp48);
    if (t[0xA4] & 1) {
        *arg1 = 0x200005;
        *arg2 = 0x60600;
        *arg3 = sp54;
        *arg4 = sp50;
        *arg5 = sp4C;
        *arg6 = 0xFF;
        *arg9 = v = sp48;
        *arg8 = v;
        *arg7 = v;
        *argA = 0xFF;
        *argB = 0x100000;
        *argC = 5;
        *argD = 0x2F;
    } else {
        ret = func_151B4F3C(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD);
    }
    return ret;
}

#ifdef NON_MATCHING
s32 func_151B5128(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 var_f0;
    s32 var_v0;
    u8 *var_v1;

    (*(f32 *)((u8 *)arg0 + 0x48)) = -1000.0f;
    temp_f0 = -1000.0f + 222.22223f;
    var_v0 = 2;
    var_v1 = arg0 + 0x30;
    (*(f32 *)((u8 *)arg0 + 0x60)) = temp_f0;
    var_f0 = temp_f0 + 222.22223f;
    (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x50)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x64)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x68)) = 0.0f;
    do {
        (*(f32 *)((u8 *)var_v1 + 0x48)) = var_f0;
        (*(f32 *)((u8 *)var_v1 + 0x4C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x50)) = 0.0f;
        temp_f0_2 = var_f0 + 222.22223f;
        var_v0 += 4;
        (*(f32 *)((u8 *)var_v1 + 0x64)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x68)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x60)) = temp_f0_2;
        temp_f0_3 = temp_f0_2 + 222.22223f;
        (*(f32 *)((u8 *)var_v1 + 0x7C)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x80)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x94)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x78)) = temp_f0_3;
        temp_f0_4 = temp_f0_3 + 222.22223f;
        (*(f32 *)((u8 *)var_v1 + 0x98)) = 0.0f;
        var_v1 += 0x60;
        (*(f32 *)((u8 *)var_v1 + 0x30)) = temp_f0_4;
        var_f0 = temp_f0_4 + 222.22223f;
    } while (var_v0 != 0xA);
    (*(u8 *)((u8 *)arg0 + 0x10)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x10)) & 0xFFFD);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E0E70/func_151B5128.s")
#endif
void func_151D5E30();

void func_151B51CC(void *arg0) {
    void (*fp)(void *);
    func_151D5E30((u8 *)arg0 + 0x140, arg0);
    fp = D_8008FF10[((u8 *)arg0)[0x44]];
    if (fp != NULL) {
        fp(arg0);
    }
}

void func_151B51CC(void *arg0);

void func_151B521C(void *arg0) {
    func_151B51CC(arg0);
    func_15169824(arg0);
}

void func_151B5248(void *arg0) {
    func_151B51CC(arg0);
    func_15169824(arg0);
}
