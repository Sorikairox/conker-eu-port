#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4090/func_151C62D0.s")

#ifdef NON_MATCHING
/* P160: func_151C6F7C reads three arguments (the matching callers below leave a 4th in a3) */
void func_151C6F7C(u8 *obj, f32 *out, u8 kind);

// object_bone_point_0: D_80090010 handler 0 (func_151D469C): bone point 0 of obj into out (arg1 unused)
void func_151C6F24(u8 *obj, s32 arg1, f32 *out) {
    func_151C6F7C(obj, out, 0);
}

// object_bone_point_1: D_80090010 handler 1 (func_151D469C): bone point 1 of obj into out (arg1 unused)
void func_151C6F50(u8 *obj, s32 arg1, f32 *out) {
    func_151C6F7C(obj, out, 1);
}
#else
void func_151C6F7C();

void func_151C6F24(s32 arg0, s32 arg1, s32 arg2) {
    func_151C6F7C(arg0, arg2, 0, arg2);
}

void func_151C6F50(s32 arg0, s32 arg1, s32 arg2) {
    func_151C6F7C(arg0, arg2, 1, arg2);
}
#endif

#ifdef NON_MATCHING
/* P160 */
extern u32 D_800AAEE0[];
extern u8 D_800AAEE8[];

// object_bone_point: transforms point `kind` (0 or 1) of the D_800AAEE8 offset table (3 floats each) by the bone
// matrix at byte offset D_800AAEE0[kind] in the object's matrix block (obj+0x1D4) and writes it to out.
void func_151C6F7C(u8 *obj, f32 *out, u8 kind) {
    func_15143134(D_800AAEE8 + kind * 12, out, *(u8 **)(obj + 0x1D4) + D_800AAEE0[kind]);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4090/func_151C6F7C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4090/func_151C6A28.s")

s32 func_151030B8(s32, u8, u8 *, u8 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern u32 D_800AAEE0[];
extern u8 D_800AAEE8[];
extern u8 D_800AAF00[];
extern f32 D_800AAFF0;
extern f32 D_800AAFF4;
extern f32 D_800AAFF8;
extern f32 D_800AAFFC;
extern f32 D_800AB000;

void func_151C7320(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5)
{
  f32 v[2];
  f32 t; // fakematch: named rand temp (s162 recipe: named float temps)
  s32 r[2];
  v[1] = (func_150ADA68() * D_800AAFF0) + D_800AAFF4;
  v[0] = (func_150ADA68() * D_800AAFF8) + D_800AAFFC;
  r[0] = func_150ADA20();
  r[1] = func_150ADA20();
  t = func_150ADA68();
  func_151030B8(arg0, D_800AAEE0[arg1] >> 6, D_800AAEE8 + (arg1 * 12), D_800AAF00 + (arg1 * 12), v, (r[0] & 3) + 6, 0xFF, (t * 270.0f) + D_800AB000, arg2, 0xFF, 0, arg3, arg4, arg5);
}

void *memcpy(void *, const void *, s32);
typedef struct { f32 x, y, z; } V3_151C7450;

typedef struct {
    f32 u0[4];
    V3_151C7450 u10;
    f32 u1C[3];
    V3_151C7450 u28;
    V3_151C7450 u34;
    V3_151C7450 u40;
    f32 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
    s8 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    s8 u62[6];
    s8 u68;
    s8 u69;
    s8 u6A;
    u8 *u6C;
    u8 u70;
    s16 u72;
    s16 u74;
    s32 u78;
} Blk7C_7450;

void func_151C7450(u8 *arg0, u8 arg1, s32 arg2) {
    Blk7C_7450 blk;
    u8 tmp[1];
    void *temp_v0;

    tmp[0] = 0;
    blk.u0[0] = 1.0f;
    blk.u0[1] = 1.0f;
    blk.u0[3] = 1.0f;
    blk.u0[2] = 1.0f;
    blk.u10 = *(V3_151C7450 *)D_800A5860;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u28 = *(V3_151C7450 *)D_800A5860;
    blk.u34 = *(V3_151C7450 *)D_800A5860;
    blk.u40 = *(V3_151C7450 *)D_800A5860;
    blk.u4C = 0.0f;
    blk.u50 = 0x11900;
    blk.u54 = 0x12C;
    blk.u56 = 0xF;
    blk.u58 = 0;
    blk.u5C = 0;
    blk.u60 = 0x64;
    blk.u61 = 0x17;
    blk.u62[0] = 0;
    blk.u62[1] = 0;
    blk.u62[2] = 0;
    blk.u62[3] = 0;
    blk.u62[4] = 0;
    blk.u62[5] = 0;
    blk.u68 = 5;
    blk.u69 = -1;
    blk.u6A = 1;
    blk.u6C = arg0;
    blk.u70 = arg0[0x3B];
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u78 = 0;
    temp_v0 = func_15132BBC(&blk, 3, 0xFF, 0, 1, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x170, tmp, 1);
    }
}

s32 func_15142A5C(u8 *, u8 *);

s32 func_151C75E8(u8 *arg0) {
    u8 *p;
    f32 f;

    p = *(u8 **)(arg0 + 0x7C);
    if (*(u16 *)(p + 0x84) != 0xE9) {
        return 0;
    }
    if (func_15142A5C(p, arg0) != 0) {
        *(s32 *)(arg0 + 0x60) |= 0x20000;
    } else {
        *(s32 *)(arg0 + 0x60) &= ~0x20000;
    }
    f = *(f32 *)(p + 0x4C) * 35.0f;
    if (f > 255.0f) {
        f = 255;
    } else if (f < 0.0f) {
        f = 0.0f;
    }
    arg0[0x70] = f;
    if (!arg0 && !arg0 && !arg0) { // fakematch: empty if keeps arg0 live, schedules li v0,1 early (local permuter)
    }
    return 1;
}
