#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A7F00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A831C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A88F0.s")

void func_151A8B10(u8 *arg0) {
    func_151D5E30(arg0 + 0x6C, arg0);
}

void func_151A8B34(u8 *arg0) {
    u8 *new_var; // fakematch: permuter temp
    void (*fn)(void *) = D_8008FCEC[arg0[0x5C]];
    new_var = arg0;
    if (fn != NULL) {
        if (!arg0) { // fakematch: permuter empty branch
        }
        fn(new_var);
    }
    func_151A8B10(arg0);
    func_15169804(arg0);
}

void func_151A8B84(u8 *arg0) {
    u8 *new_var; // fakematch: permuter temp
    void (*fn)(void *) = D_8008FCF8[arg0[0x5C]];
    new_var = arg0;
    if (fn != NULL) {
        if (!arg0) { // fakematch: permuter empty branch
        }
        fn(new_var);
    }
    func_151A8B10(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8BD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8DA8.s")

void func_151A8FD0(u8 *arg0, s32 arg1, u8 arg2) {
    s32 idx = arg0[0x5C];
    void (*fn)(u8 *, s32, u8);

    if (idx >= 3) {
        idx = 0;
    }
    fn = (void (*)(u8 *, s32, u8))D_8008FD04[idx];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

void func_151A9028(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a0;
    s32 new_var; // fakematch: key temp pins the v1 register
    s32 temp_t6 = arg2;
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x60);

    if (arg2 == 0) {
        new_var = *(s32 *)(arg1 + 0);
        if ((new_var == *(s32 *)(temp_v0 + 0)) || (*(u8 *)(arg1 + 4) == *(u8 *)(temp_v0 + 4))) {
            func_1516972C(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)(arg1 + 0);
        if (temp_a0 == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = temp_a0;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8B20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A929C.s")

s32 func_151432BC(s32, u8 *, u8 *, f32 *, s32);
void func_151A94CC(u8 *arg0, u8 *arg1, f32 *arg2, s32 arg3) {
    func_151432BC(*(s32 *)(arg0 + 0x2C), arg1, arg1 + 8, arg2, arg3);
    *(f32 *)(arg1 + 4) = *arg2;
}

void func_15143874(s16, f32, f32 *, f32 *);
void func_151A951C(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 *p;

    p = (f32 *)(arg0 + 0x28);
    func_15143874(func_150ADA20() & 0xFF, p[8] * func_150ADA68(), arg1, arg1 + 2);
    arg1[0] += p[4];
    arg1[2] += p[6];
    arg1[1] = p[5];
    *arg2 = p[5];
    *arg3 = p[7];
}

void func_151A98CC(u8 *, s32, u8);
void func_151A95D4(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg0[0x4C] == 1) {
        func_151A98CC(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9670.s")

typedef struct {
    s32 u0;
    s16 u4;
    u8 u6;
    u8 u7;
    s32 u8_;
    s32 uC;
    u8 u10[8];
    s32 u18;
    s32 u1C;
    u8 u20;
    s16 u22;
    s16 u24;
} Spawn975C;
typedef struct { s16 v[3]; } Tbl975C;
extern Tbl975C D_8008FD44;

void func_151A975C(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 pad;
    Spawn975C sp;
    f32 f;
    Tbl975C t;

    t = D_8008FD44;
    f = func_150ADA68() * 50.0f + 50.0f;
    sp.u6 = t.v[func_150ADA20() % 3U];
    sp.u7 = 0;
    sp.u10[6] = 0;
    sp.u10[7] = 7;
    sp.u8_ = 0;
    sp.uC = 0;
    sp.u0 = 0x1701;
    sp.u4 = 0x3C;
    sp.u10[0] = 0xA0;
    sp.u10[1] = 0xFF;
    sp.u10[2] = 0;
    sp.u10[3] = 0;
    sp.u10[4] = 0;
    sp.u10[5] = 0xFF;
    sp.u18 = 0x3B0002;
    func_1513C650((s32)&sp, 1, 0, (s32)(arg0 + 0x58), *(f32 *)(arg1 + 0), *(f32 *)(arg1 + 4), *(f32 *)(arg1 + 8), f, f, func_150ADA20() & 0xFF, (func_150ADA20() & 1) + (func_150ADA20() & 1), 3, 0xFF, 0, arg0[0xC], arg0[1]);
}

void func_151A98CC(u8 *arg0, s32 arg1, u8 arg2)
{
  if (arg2 == 0x17) {
    u8 *p = arg0 + 0x28;
    if (((u8 *)arg1)[0] == arg0[0x80]) {
      *p |= 1;
    }
  } else if (arg2 == 0x18) {
    u8 *p = arg0 + 0x28;
    if (((u8 *)arg1)[0] == arg0[0x80]) {
      *p &= ~1;
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9940.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9BE4.s")

typedef struct {
    f32 x;
    u8 pad4[0x14];
    s32 u18;
    u8 u1C;
    u8 u1D;
    s32 u20;
} Obj9DE4;
s32 func_15046F70(f32 *, s32, f32, Obj9DE4 *);
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
typedef void (*Fn9DE4)(f32 *, Obj9DE4 *, s32, u8, s32);
extern Fn9DE4 D_8008FE00[];

void func_151A9DE4(f32 *arg0, f32 arg1, f32 arg2, Obj9DE4 *arg3, s32 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    Obj9DE4 o;
    f32 pos[3];
    f32 v[3];
    f32 a;

    if (arg3 == NULL) {
        arg3 = &o;
        o.x = 99999.9f;
        o.u18 = 0;
        o.u1C = 7;
        o.u1D = 0;
        o.u20 = 0;
    }
    pos[1] = arg0[1];
    for (; arg4 > 0; arg4--) {
        a = func_150ADA68();
        func_1514373C(2.0f * a * 3.1415927f, func_150ADA68() * arg2, &pos[0], &pos[2]);
        pos[0] += arg0[0];
        pos[2] += arg0[2];
        if (func_15046F70(pos, 0, arg1, arg3)) {
            v[0] = pos[0];
            v[1] = arg3->x;
            v[2] = pos[2];
            D_8008FE00[arg5](v, arg3, arg6, arg7, arg8);
        }
    }
}
