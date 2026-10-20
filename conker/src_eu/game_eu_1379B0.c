#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct { f32 x, y, z; } V3;

void func_1510A1A0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5)
{
  f32 temp_f0;
  u8 *spA0;
  struct 
  {
    f32 u20[10];
    s32 u48;
    u8 pad4C[0x8];
    f32 u54;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    f32 u68;
    f32 u6C;
    s32 u70;
    s16 u74;
    s16 u76;
    s8 u78;
    u8 pad79[0x3];
    s32 u7C;
    u8 u80;
    s8 u81;
    s8 u82;
    s8 u83;
    s8 u84;
    s8 u85;
    s8 u86;
    s8 u87;
    s8 u88;
    u8 pad89[0x1];
    s8 u8A;
    u8 pad8B[0x1];
    u8 *u8C;
    u8 u90;
    u8 pad91[0x1];
    s16 u92;
    s16 u94;
    u8 pad96[0x6];
    f32 u9C;
  } sp;
  spA0 = *((u8 **) (((u8 *) arg0) - -0x28));
  sp.u9C = ((func_150ADA68() * 4611.0f) + 1581.0f) * 0.001f;
  sp.u20[0] = 1.0f;
  sp.u20[1] = 1.0f;
  sp.u20[3] = ((func_150ADA68() * 3522.0f) + 4599.0f) * 0.000001f;
  sp.u20[2] = sp.u20[3];
  sp.u20[4] = func_150ADA68() * 360.0f;
  sp.u20[5] = func_150ADA68() * 360.0f;
  temp_f0 = func_150ADA68();
  sp.u20[7] = 1.0f;
  sp.u20[8] = 1.0f;
  sp.u20[9] = 1.0f;
  sp.u20[6] = temp_f0 * 360.0f;
  temp_f0 = sp.u9C; // fakematch: reload u9C into the reused float temp
  *((V3 *) (&sp.u48)) = *((V3 *) arg1);
  sp.u54 = (*((f32 *) (((u8 *) arg5) + 0))) * temp_f0;
  sp.u58 = (*((f32 *) (((u8 *) arg5) + 4))) * temp_f0;
  sp.u5C = (*((f32 *) (((u8 *) arg5) + 8))) * temp_f0;
  sp.u60 = ((func_150ADA68() * 24546.0f) + (-12273.0f)) * 0.001f;
  sp.u64 = 0.0f;
  sp.u68 = ((func_150ADA68() * 24546.0f) + (-12273.0f)) * 0.001f;
  temp_f0 = (func_150ADA68() * 124.0f) + (-231.0f); // fakematch: permuter temp
  sp.u70 = 0x29E8;
  sp.u6C = temp_f0 * 0.001f;
 sp.u74 = (func_150ADA20() % 15U) + 0x14; if (func_150ADA20() & 1) { sp.u76 = 0x23; } else { sp.u76 = 0x24;
  }
  sp.u78 = 0;
  sp.u7C = 0;
  sp.u80 = 0xFF;
  sp.u81 = 8;
  sp.u82 = 0;
  sp.u83 = 0;
  sp.u84 = 0;
  sp.u85 = 0;
  sp.u86 = 0;
  sp.u87 = 0;
  sp.u88 = 2;
  if ((*((u8 *) (((u8 *) arg0) + 0x13))) == 0x1A)
  {
    sp.u8A = 1;
  }
  else
  {
    sp.u8A = 2;
  }
  sp.u8C = spA0;
  sp.u90 = *((u8 *) (((u8 *) spA0) + 0x3B));
  sp.u92 = 0xA;
  sp.u94 = 0x19;
  func_15132FBC(&sp, 3, 0xFF, 0, (s32) (*((u8 *) (((u8 *) arg0) + 0xC))), (s32) (*((u8 *) (((u8 *) arg0) + 1))));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1379B0/func_1510A454.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1379B0/func_1510A538.s")

struct260 *func_1510A8C4(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        f32 unk8;
        f32 unkC;
        f32 unk10;
    } tmp;

    if (arg0 == NULL) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.20400001f;
    tmp.unk10 = 0.822f;
    temp_v0 = func_15149130(arg1, -1, 0x1C, -1, 1, 0x1C, 0x14, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1379B0/func_1510A98C.s")

void func_1510ADF0(u8 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == arg1->unk0) {
            temp_v0->unk0 = arg1->unk4.i.unk0;
            temp_v0->unk4.b.unk0 = arg1->unk9;
        } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
            temp_v0->unk0 = arg1->unk0;
            temp_v0->unk4.b.unk0 = arg1->unk8;
        }
    }
}

void func_1510AE4C(u8 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == arg1->unk0) {
            temp_v0->unk0 = arg1->unk4.i.unk0;
            temp_v0->unk4.b.unk0 = arg1->unk9;
        } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
            temp_v0->unk0 = arg1->unk0;
            temp_v0->unk4.b.unk0 = arg1->unk8;
        }
    }
}
