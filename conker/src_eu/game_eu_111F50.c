#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150E4740(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 pad; // fakematch: frame slot 0x30 (unknown named local)
    f32 vy;
    f32 vz;
    f32 s;
    f32 a;
    f32 c;
    f32 vx;
    s16 *p;

    x = D_800DBFF0->unk2F8;
    y = D_800DBFF0->unk2FC;
    z = D_800DBFF0->unk300;
    a = D_800DBFF0->unk398;
    s = sinf(a);
    c = cosf(a);
    vy = 500.0f * s;
    vz = -500.0f * c;
    vx = 0.0f;
    a = D_800DBFF0->unk3A0;
    s = sinf(a);
    c = cosf(a);
    x += (vx + (vz * s));
    z += ((vz * c) - vx);
    y += vy;
    p = (s16 *)D_800D9E10;
    p[0] = x;
    p[2] = z;
    p[1] = y;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_111F50/func_150E4878.s")

void func_150E4A94(s32 arg0) {
    func_150E4740();
    func_150E4878(arg0 / 30);
}
