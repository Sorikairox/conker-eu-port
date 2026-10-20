#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_8008D960;
void func_1518AF80(u8 *arg0) {
    struct102 *n;
    struct102 *a2;
    s16 h;
    u8 k;

    if (*(s32 *)(arg0 + 0x1C) != 0) {
        h = *(s16 *)(arg0 + 0x22);
        if (h < 0) {
            a2 = *(struct102 **)(arg0 + 0x14);
            n = *(struct102 **)((u8 *)a2 + 0x18);
            if (n == NULL) {
                *(s32 *)(arg0 + 0x10) = 0;
                *(s32 *)(arg0 + 0x14) = 0;
            } else {
                *(s32 *)((u8 *)n + 0x14) = 0;
                *(s32 *)(arg0 + 0x14) = *(s32 *)((u8 *)a2 + 0x18);
            }
            k = *(u8 *)((u8 *)a2 + 0x1C);
            if (k != 0) {
                ((void (**)(s32))&D_8008D960)[k](*(s32 *)((u8 *)a2 + 0x10));
            }
            func_1516972C(a2);
            *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
            return;
        }
        if (*(u8 *)(arg0 + 0x24) & 1) {
            *(s16 *)(arg0 + 0x22) = h - D_800BE9E4;
        }
    }
}

u8 *func_1518AADC(s32 arg0, s16 arg1, u8 arg2)
{
  u8 *t;
  t = func_15167A68(0x1D, 0, 0x28, 1, 0xFFU, 1U);
  if (t == 0)
  {
    return 0;
  }
  *((s32 *) (t + 0x1C)) = 0;
  *((s32 *) (t + 0x18)) = arg0;
  *((s16 *) (t + 0x22)) = arg1;
  *((s16 *) (t + 0x20)) = arg1;
  *((s32 *) (t + 0x10)) = 0;
  *((s32 *) (t + 0x14)) = 0;
  *((u8 *) (t + 0x24)) = arg2;
  return t;
}

u8 *func_1518B0D0(s32 arg0, u8 arg1)
{
  u8 *temp_v0;
  temp_v0 = func_15167A68(0x1E, 0, 0x20, 1, 0xFFU, 1U);
  if (temp_v0 == 0)
  {
    return 0;
  }
  *((s32 *) (((u8 *) temp_v0) + 0x10)) = arg0;
  *((u8 *) (((u8 *) temp_v0) + 0x1C)) = arg1;
  *((s32 *) (((u8 *) temp_v0) + 0x14)) = 0;
  *((s32 *) (((u8 *) temp_v0) + 0x18)) = 0;
  return temp_v0;
}

s32 func_1518B140(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *a1;
    u8 *n;
    u8 *nx;
    u8 k;
    if (arg0 == NULL) {
        if (arg2 != 0) { ((void (**)(s32))&D_8008D960)[arg2](arg1); }
        return 0;
    }
    n = func_1518B0D0(arg1, arg2);
    if (n == NULL) {
        if (arg2 != 0) { ((void (**)(s32))&D_8008D960)[arg2](arg1); }
        return 0;
    }
    *(u8 **)(n + 0x14) = *(u8 **)(arg0 + 0x10);
    if (*(u8 **)(n + 0x14) != NULL) {
        *(u8 **)(*(u8 **)(n + 0x14) + 0x18) = n;
    } else {
        *(u8 **)(arg0 + 0x14) = n;
    }
    *(u8 **)(arg0 + 0x10) = n;
    *(s32 *)(n + 0x18) = 0;
    *(s16 *)(arg0 + 0x22) = *(s16 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
    if (*(s32 *)(arg0 + 0x18) < *(s32 *)(arg0 + 0x1C)) {
        a1 = *(u8 **)(arg0 + 0x14);
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
        nx = *(u8 **)(a1 + 0x18);
        if (nx == NULL) {
            *(s32 *)(arg0 + 0x10) = 0;
            *(s32 *)(arg0 + 0x14) = 0;
        } else {
            *(s32 *)(nx + 0x14) = 0;
            *(s32 *)(arg0 + 0x14) = *(s32 *)(a1 + 0x18);
        }
        k = *(u8 *)(a1 + 0x1C);
        if (k != 0) {
            ((void (**)(s32))&D_8008D960)[k](*(s32 *)(a1 + 0x10));
        }
        func_1516972C(a1);
    }
    return 1;
}
