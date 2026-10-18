#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct260 *func_151CD2C0(u8 *arg0, u8 arg1, s32 arg2) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        s32 unk4;
        s32 unk8;
        u8 unkC;
        u8 padD[3];
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = *(s32 *)(arg0 + 0x18);
    tmp.unk8 = 0;
    tmp.unkC = *(s32 *)(arg0 + 0x1C);
    temp_v0 = func_15149130(0x12C, -1, -1, -1, 0, 0x1E, 0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return temp_v0;
}

void func_151CD90C(s32 arg0) {
    s32 tmp;
    if ((arg0 >= 0) && (arg0 < 4)) {
        tmp = arg0;
        func_151494E0(&tmp, 0x17);
    }
}

void func_151CD944(s32 arg0) {
    s32 tmp;
    if ((arg0 >= 0) && (arg0 < 4)) {
        tmp = arg0;
        func_151494E0(&tmp, 0x18);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CD97C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDA70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDC24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDD6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CE144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CE3D0.s")

void func_151CEA2C(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
}

void func_151CEA4C(u8 *arg0) {
    s32 tmp;
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    tmp = *(s32 *)(temp_v0 + 0x48);
    func_151494E0(&tmp, 0x23);
    func_15147E64(arg0);
}

void func_151CEA8C(u8 *arg0) {
    s32 tmp;
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    tmp = *(s32 *)(temp_v0 + 0x48);
    func_151494E0(&tmp, 0x23);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEACC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEBE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEC80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEFD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF05C.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} struct_151CF1C0;

s32 func_151CF1C0(struct_151CF1C0 *arg0, u8 *arg1, u8 *arg2) {
    if (arg2 != NULL) {
        *arg0 = *(struct_151CF1C0 *)(arg2 + 0x40);
    } else {
        arg0->x = ((struct_151CF1C0 *)(arg1 + 0x14))->x;
        arg0->y = ((struct_151CF1C0 *)(arg1 + 0x14))->y;
        arg0->z = ((struct_151CF1C0 *)(arg1 + 0x14))->z;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF6D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF930.s")

void func_151CFDF4(u8 *arg0, s32 arg1, u8 arg2) {
    s32 *temp_t7;
    s32 *sp24;

    temp_t7 = (*(s32 **)((u8 *)arg0 + 0x98));
    sp24 = temp_t7;
    if (*temp_t7 != 0) {
        func_15169850(arg1, arg2, (s32) temp_t7, (s32) temp_t7 + 4, (s32) arg0);
    }
}

typedef struct { f32 x, y, z; } Vec3CFE48;
f32 func_15144AA8(s32 arg0);
s32 func_15046F70(Vec3CFE48 *, u16, f32, f32 *);
extern f32 D_800D9C80;

void func_151CFE48(s32 arg0, f32 arg1, f32 arg2) {
    u8 *p;
    Vec3CFE48 pos;
    f32 *base;
    f32 a;
    f32 angle;
    f32 dist;
    struct {
        Vec3CFE48 unk0;
        f32 unkC;
    } tmp;
    struct260 *temp_v0;

    p = *(u8 **)((u8 *)arg0 + 0x318);
    if (p != NULL && func_150ADA68() < 0.22200002f) {
        base = func_15144B34(p[0x23D]);
        a = func_15144AA8(p[0x23D]);
        angle = (func_150ADA68() * 80.0f + (a - 40.0f)) * 0.017453292f;
        dist = func_150ADA68() * 2000.0f;
        pos.x = base[0] - sinf(angle) * dist;
        pos.y = arg1;
        pos.z = base[2] - cosf(angle) * dist;
        if (func_15046F70(&pos, 0, arg2, &D_800D9C80) != 0) {
            pos.y = D_800D9C80;
            tmp.unk0 = pos;
            tmp.unkC = 0.0f;
            temp_v0 = func_15149130(func_150ADA20() % 131U + 51, -1, 0x20, -1, 1, 0, 0x10, 0xFF, 1);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CFFFC.s")

void func_151D0024(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x18);
}

void func_151D0058(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[1];
        s16 unk6;
        f32 unk8;
        u8 unkC;
        u8 unkD;
        u8 padE[2];
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = (*(f32 *)(arg0 + 0x150) + *(f32 *)(arg0 + 0x14C)) * 0.5f;
    tmp.unkD = arg1;
    tmp.unkC = (func_150ADA20() % 56U) + 200;
    tmp.unk6 = *(u16 *)(arg0 + 0x84);
    temp_v0 = func_15149130(0x12C, -1, 0x61, 4, 0, 0x31, 0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

void func_151D06D8(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);
    if (*(u16 *)(temp_v0 + 0x84) != *(u16 *)(arg0 + 0x2E)) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D06FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D0EA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D09A8.s")

void func_151D1488(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0xA8) != 0) { func_1516972C(*(struct102 **)(p + 0xA8)); } }

void func_151D14B8(void *arg0) {
    func_151D1488(arg0);
    func_15131CAC(arg0);
}

void func_151D14E4(void *arg0) {
    func_151D1488(arg0);
    func_15131CCC(arg0);
}

typedef struct {
    f32 x, y, z;
} Vec3_151D1510;
extern s32 (*D_8008FFD0[])(u8 *, Vec3_151D1510 *);

void func_151D1510(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        s32 unk8;
        Vec3_151D1510 unkC;
        Vec3_151D1510 unk18;
        Vec3_151D1510 unk24;
        f32 unk30;
        u8 unk34;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0;
    if (D_8008FFD0[arg1](arg0, &tmp.unk18) == 0) {
        tmp.unk18 = *(Vec3_151D1510 *)D_800A5860;
    }
    tmp.unkC = tmp.unk18;
    tmp.unk24 = *(Vec3_151D1510 *)D_800A5860;
    tmp.unk30 = 0.0f;
    tmp.unk34 = arg1;
    temp_v0 = func_15149130(300, -1, 0x5F, -1, 0, 0x48, 0x38, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x38);
    }
}

s32 func_151D1624(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[0x14 / 4];
    arg1[1] = arg0[0x180 / 4] + 8.0f;
    arg1[2] = arg0[0x1C / 4];
    return 1;
}

void func_151D1654(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 0);
}

void func_151D1674(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1694.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D16E8.s")

void func_151D18D8(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_151D1918(void *arg0) {
    func_151D1990(arg0);
}

void func_151D1938(void *arg0) {
    func_151D1918(arg0);
    func_1514933C(arg0);
}

void func_151D1964(void *arg0) {
    func_151D1918(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D19F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D2248.s")

void func_151D27EC(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x30 / 4] = 0;
    }
}

void func_151D2808(void *arg0) {
    func_151D27EC(arg0);
    func_15147E64(arg0);
}

void func_151D2834(void *arg0) {
    func_151D27EC(arg0);
    func_15147E98(arg0);
}
