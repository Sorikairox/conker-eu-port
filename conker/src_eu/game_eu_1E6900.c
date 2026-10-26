#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151B90F0(f32 *arg0) {
    arg0[0x3C / 4] = arg0[0x48 / 4] + (arg0[0x5C / 4] * sinf(arg0[0x44 / 4]));
    arg0[0x44 / 4] += arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x44 / 4] = func_15144B68(arg0[0x44 / 4]);
    arg0[0x20 / 4] += arg0[0x50 / 4] * D_800BE9A4;
    arg0[0x28 / 4] += arg0[0x58 / 4] * D_800BE9A4;
    return 1;
}

void func_151B9190(f32 *arg0, s32 arg1)
{
  arg0[0x44 / 4] = arg0[0x5C / 4] + (arg0[0x64 / 4] * sinf(arg0[0x58 / 4]));
  arg0[0x58 / 4] += arg0[0x60 / 4] * D_800BE9A4;
  arg0[0x58 / 4] = func_15144B68(arg0[0x58 / 4]);
  impact_dust_cloud_wobble(arg0, arg1);
}

s32 func_151B9204(u8 *arg0) {
    
    u8 *v = arg0 + 0x120;
    *(f32 *)(arg0 + 0x58) = *(f32 *)(v + 0x14) + (*(f32 *)(v + 0x28) * sinf(*(f32 *)(arg0 + 0x130)));
    *(f32 *)(v + 0x10) = (*(f32 *)(v + 0x18) * D_800BE9A4) + *(f32 *)(v + 0x10);
    *(f32 *)(v + 0x10) = func_15144B68(*(f32 *)(v + 0x10));
    *(f32 *)(v + 0) = (*(f32 *)(v + 0x1C) * D_800BE9A4) + *(f32 *)(v + 0);
    *(f32 *)(v + 8) = (*(f32 *)(v + 0x24) * D_800BE9A4) + *(f32 *)(v + 8);
    return 1;
}

s32 func_151B92AC(u8 *arg0)
{
    f32 *v = (f32 *)(arg0 + 0x110);
    *(f32 *)(arg0 + 0x38) = v[0] + v[1] * sinf(*(f32 *)(arg0 + 0x118));
    v[2] = v[3] * D_800BE9A4 + v[2];
    v[2] = func_15144B68(v[2]);
    *(f32 *)(arg0 + 0x40) += v[4] * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += v[6] * D_800BE9A4;
    return 1;
}
