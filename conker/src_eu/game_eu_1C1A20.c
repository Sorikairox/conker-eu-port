#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1518D1C0(u8 *, s16, s32, u8, u8, s32, char *);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194210.s")

void func_151942B0(s32 arg0, s32 arg1, s32 arg2) {
    func_15194210(arg1, 0, 0xFF, 1);
}

void func_15194858(s32 arg0, s32 arg1, s32 arg2) {
    func_15194210(arg1, 1, 0xFF, 1);
}


void func_15194890(s32 arg0, u8 *arg1, s32 arg2) {

    switch ((*(u8 *)((u8 *)arg1 + 4))) {
    s32 pad;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_1518D1C0(arg1, 0xA, 0, 1, 0xFF, 1, "effects_impact_lavaboulder");
        break;
    }
}

void func_15194904(s32 arg0, u8 *arg1, s32 arg2) {

    switch ((*(u8 *)((u8 *)arg1 + 4))) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_1518D1C0(arg1, 0xC, 0, 1, 0xFF, 1, "effects_impact_fireimp");
        break;
    }
}

s32 func_1504715C(s32 *, struct127 *);
void func_151AED60(u8 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_15194978(struct127 *arg0, struct127 *arg1) {
    struct_eu_15154488 sp4C;
    s32 sp28[9];

    switch (((u8 *) arg1)[4]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_151AED60((u8 *) arg1, 0.6f, 0x5A, 0xFF, 1);
        func_1504715C(sp28, arg1);
        sp4C.unk8.unk0 = *(f32 *)((u8 *) arg1 + 0x14);
        sp4C.unk8.unk4 = *(f32 *)((u8 *) arg1 + 0x18) + 50.0f;
        sp4C.unk8.unk8 = *(f32 *)((u8 *) arg1 + 0x1C);
        sp4C.unk14 = 6.0f;
        sp4C.unk18 = 3.0f;
        sp4C.unk1C = 0.21f;
        sp4C.unk20 = 0.406f;
        sp4C.unk24 = 13.0f;
        sp4C.unk28 = 8.0f;
        sp4C.unk2C = 0xC;
        sp4C.unk2E = 5;
        sp4C.unk2 = 0xFF;
        sp4C.unk4 = -0x3F;
        sp4C.unk0 = 0;
        sp4C.unk6 = 0x23;
        sp4C.unk30 = 3;
        sp4C.unk32 = 2;
        sp4C.unk34 = 0x1E;
        sp4C.unk36 = 0x1E;
        sp4C.unk38 = 0x64;
        sp4C.unk3A = 0x64;
        sp4C.unk44 = 0x10;
        sp4C.unk46 = 0xF;
        sp4C.unk48 = 0;
        sp4C.unk3C = 0;
        sp4C.unk40 = 0.3f;
        func_15154488(&sp4C, &sp4C.unk8, (s32) sp28, 0xFF, 1);
        break;
    }
}

void func_15194AF8(struct127 *arg0, struct127 *arg1, s32 arg2) {
    func_150C7520(arg0, 500, 0xFF, 1);
    func_15194978(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194B3C.s")

s32 func_151AF820(u8 *, u8, s32);
s32 func_151B01B8(s32, u8 *);
s32 func_151B09BC(s32, u8 *, s16, u8, s32);

void func_15194794(s32 arg0, u8 *arg1, s32 arg2) {

    func_151B01B8(arg0, arg1);
    func_151B09BC(arg0, arg1, 0x3E8, 0xFF, 0);
    switch ((*(u8 *)((u8 *)arg1 + 4))) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        func_151AF820(arg1, 0xFF, 1);
        break;
    }
}

void func_15194D80(s32 arg0, u8 *arg1, s32 arg2) {
    struct17 pos;
    struct_eu_15154488 sp50;
    s32 sp2C[9];
    structEU_151D8E18 sp24;

    switch (arg1[4]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x53:
        pos.unk0 = *(f32 *)(arg1 + 0x14);
        pos.unk4 = *(f32 *)(arg1 + 0x18) + 95.0f;
        pos.unk8 = *(f32 *)(arg1 + 0x1C);
    block_boundary: // fakematch: bare label = basic-block boundary (IDO_SHAPES s66 recipe 1), keeps addiu a0 in the jal slot
        func_1504715C(sp2C, (struct127 *) arg1);
        sp50.unk8 = pos;
        sp50.unk14 = 10.0f;
        sp50.unk18 = 5.0f;
        sp50.unk1C = 0.675f;
        sp50.unk20 = 0.231f;
        sp50.unk24 = 5.0f;
        sp50.unk28 = 25.1f;
        sp50.unk2C = 0xF;
        sp50.unk2E = 0xA;
        sp50.unk2 = 0xFF;
        sp50.unk4 = -0x3F;
        sp50.unk0 = 0;
        sp50.unk6 = 0x39;
        sp50.unk30 = 3;
        sp50.unk32 = 2;
        sp50.unk34 = 0x46;
        sp50.unk36 = 0x16;
        sp50.unk38 = 0x9B;
        sp50.unk3A = 0x64;
        sp50.unk44 = 0x10;
        sp50.unk46 = 0xF;
        sp50.unk48 = 0;
        sp50.unk3C = 0;
        sp50.unk40 = 0.5f;
        func_15154488(&sp50, &sp50.unk8, (s32) sp2C, 0xFF, 1);
        sp24.unk0 = 1;
        sp24.unk2 = (func_150ADA20() % 11U) + 20;
        sp24.unk4 = 8;
        sp24.unk6 = -1;
        sp24.unk5 = 1;
        func_151D8E18(&sp24, 0, 0xFF, 0);
        break;
    }
}

void func_15194F50(s32 arg0, s32 arg1, s32 arg2) {
}

void func_15194F64(s32 arg0, u8 *arg1, s32 arg2) {
    if ((D_80090130 == 1) && (arg1[0x127] == 0) && (D_800E9D00 & 8) && (*(u16 *)(*(u8 **)(arg1 + 0x31C) + 0x1A0) == 0)) {
        func_151046F0(arg0, (s32)arg1, arg2);
        *(s16 *)(*(u8 **)(arg1 + 0x31C) + 0x1A0) = 0x3E8;
    }
}

void func_15194FD8(s32 arg0, s32 arg1, s32 arg2) {
    func_1507DE4C(arg1);
    func_15138BC0(arg1, 0xFF, 1);
    func_15194F64(0, arg0, arg1);
}

s32 func_15195024(s32 arg0) {
    s32 r = *(u8 *)(arg0 + 4);
    s32 a;

    *(s32 *)(arg0 + 0x9C) |= 0xFFFE;
    a = -1;
    switch (r) {
    case 0x75:
        a = 0x73;
        break;
    case 0x80:
        a = 0x72;
        break;
    }
    if (a != -1) {
        r = func_15083568((struct127 *)arg0, a, 1.0f, 0);
    }
    // fakematch: no return statement, the result is left in v0 (IDO_SHAPES 3.9)
}

s32 func_15134070(s32);
s32 func_15136C3C(s32, u8, u8, u8, u8, u8, u8, s32);
s32 func_15138120(struct127 *, s32, u8);
s32 func_15195024(s32);

void func_1519508C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_15134070(arg0);
    if (temp_v0 != 0x63) {
        func_15138120(arg0, temp_v0, 0);
    }
    func_15136C3C(arg0, 1, 1, 1, 1, 1, 0xFF, 1);
    func_15195024(arg0);
}

void func_15195104(s32 arg0, u8 *arg1, s32 arg2) {
    if (arg1[4] == 0x53) {
        func_151942B0(arg0, arg1, arg2);
    } else {
        func_1519508C(arg1);
        func_15194F64(1, arg0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195160.s")

void func_151952F0(s32 arg0, s32 arg1, s32 arg2) {
    func_15195564(arg0, arg1, 0);
}

void func_15195314(s32 arg0, s32 arg1, s32 arg2) {
    func_15195564(arg0, arg1, 1);
}

s32 func_1514B8D4(s32, s32 *, u8, s32);

void func_15195338(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp2C[9];

    if (D_800BE616 != 0) {
        func_15195314(arg0, arg1, arg2);
    } else {
        func_1518D1C0((u8 *)arg1, 0xB, 0, 1, 0xFF, 1, "effects_impact_lava");
    }
    func_1504715C(sp2C, arg1);
    func_1514B8D4(arg1 + 0x14, sp2C, 0xFF, 1);
}

void func_151953C4(s32 arg0, u8 *arg1, s32 arg2) {
    u8 v = arg1[4];

    if ((v == 0x3E) || (v == 0xA6)) {
        func_150B0B90(arg1, arg0, 0xFF, 1);
    }
}

s32 func_15182BE0(u8, u8, u8, u8, s16, u8, u8, s32);
s32 func_15195160(s32, u8 *, s8 *);

void func_15195418(s32 arg0, u8 *arg1, s32 arg2) {
    s8 sp37;
    s32 pad;
    volatile s32 sp2C;

    sp37 = 0;
    if ((*(u8 **)((u8 *)arg1 + 0x318)) != NULL) {
        sp2C = func_150ADA20();
        func_15182BE0(0xFF, 0xFF, 0xFF, 0xFF, (func_150ADA20() % 11U) + 0x23, (s32) (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg1 + 0x318))) + 0x23D)), 0xFF, 1);
    }
    func_15195160(arg0, arg1, &sp37);
}

s32 func_1507CD64(struct127 *, s32);
s32 func_151C0648(f32 *, struct127 *, s32, s32, s32);
void func_151954B8(s32 arg0, struct127 *arg1, s32 arg2) {
    f32 sp34[3];

    sp34[0] = arg1->x_position;
    sp34[1] = arg1->y_position + 50.0f;
    sp34[2] = arg1->z_position;
    func_151C0648(sp34, arg1, 1, 0xFF, 1);
    func_15136C3C(arg1, 0, 0, 1, 0, 0, 0xFF, 1);
    func_15145A50(arg1);
    func_1507CD64(arg1, 6);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195750.s")

void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
void func_15137610(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5);
void func_15195A98(u8 *arg0, u8 *arg1, s32 arg2) {
    f32 angle;
    f32 a[3];
    f32 b[3];
    f32 dir[3];
    f32 x;
    f32 z;

    if (arg0 != NULL) {
        angle = *(f32 *)(arg0 + 0x40) - 90.0f;
    } else if (arg1 != NULL) {
        angle = *(f32 *)(arg1 + 0x40) - 90.0f;
    } else {
        angle = func_150ADA68() * 360.0f;
    }
    func_1514373C(angle * 0.017453292f, 1.0f, &dir[0], &dir[2]);
    dir[1] = 0.0f;
    x = dir[0] * 20.0f;
    a[0] = *(f32 *)(arg1 + 0x14) + x;
    a[1] = *(f32 *)(arg1 + 0x18) + 50.0f;
    z = dir[2] * 20.0f;
    a[2] = *(f32 *)(arg1 + 0x1C) + z;
    b[0] = *(f32 *)(arg1 + 0x14) - x;
    b[1] = *(f32 *)(arg1 + 0x18) + 50.0f;
    b[2] = *(f32 *)(arg1 + 0x1C) - z;
    func_15137610(arg1, a, b, dir, 0xFF, 1);
}

void func_15195BC0(s32 arg0, s32 arg1, s32 arg2) {
    func_151B01B8(arg0, arg1);
    func_151B09BC(arg0, arg1, 1000, 0xFF, 0);
}

s32 func_1507CD64(struct127 *, s32);

void func_15195C08(u8 *arg0, struct127 *arg1, s32 arg2) {
    if ((arg1->health == 0) && (arg1->unk127 != 0xFF)) {
        func_15136C3C((s32) arg1, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(arg1);
        func_1507CD64(arg1, 6);
    }
    if ((*(u8 *)((u8 *)arg0 + 4)) == 0x47) {
        (*(s8 *)((u8 *)arg0 + 0x1CA)) = 0;
    }
}

void func_15195CA8(s32 arg0, s32 arg1, s32 arg2) {
    structEU_151D8E18 sp18;

    sp18.unk0 = 1;
    sp18.unk2 = (func_150ADA20() % 11U) + 20;
    sp18.unk4 = 8;
    sp18.unk6 = -1;
    sp18.unk5 = 1;
    func_151D8E18(&sp18, 0, 0xFF, 0);
}
