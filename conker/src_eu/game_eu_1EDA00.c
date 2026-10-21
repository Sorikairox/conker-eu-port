#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151C0BF4(s32 arg0, u8 arg1, s32 arg2);
void func_151C0910(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
#endif
// hoisted forward declaration(s) for func_151C0AA8
void func_15154728(u8 *, f32, s32, f32, f32, u8, s32);
// hoisted forward declaration(s) for func_151C0350
void func_151C09C8(u8 *, u8, s32);
void func_151C0B54(s32, u8, s32);
void func_151C0BA0(struct17 *, u8, s32);
void func_15150108(f32 *, u8, s32);
void func_151C01F0(f32 *, f32 *);
void func_151C0AA8(u8 *, u8, s32);


#ifdef NON_MATCHING
extern f32 D_800AAD5C;
extern f32 D_800AAD60;
extern f32 D_800AAD64;
extern f32 D_800AAD68;
extern f32 D_800AAD6C;
void func_151C01F0(f32 *arg0, f32 *arg1) {
    s32 var_v0;
    s32 var_v0_2;

    (*(f32 *)((u8 *)arg0 + 0)) = 4e-45f;
    if (D_80082FA0 >= 2) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) (4 >> var_v0);
    *arg1 = 494.0f;
    (*(f32 *)((u8 *)arg0 + 0x14)) = D_800AAD5C;
    (*(s32 *)((u8 *)arg0 + 0x2C)) = 7;
    (*(f32 *)((u8 *)arg0 + 0x18)) = D_800AAD60;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = 45.0f;
    (*(f32 *)((u8 *)arg0 + 0x20)) = 53.0f;
    (*(f32 *)((u8 *)arg0 + 0x24)) = 203.0f;
    (*(f32 *)((u8 *)arg0 + 0x28)) = 414.0f;
    if ((D_80082FA0 >= 2) || (var_v0_2 = 0, ((D_8008FD8C < 8) == 0))) {
        var_v0_2 = 1;
    }
    (*(s32 *)((u8 *)arg0 + 0x30)) = (s32) (3 >> var_v0_2);
    (*(f32 *)((u8 *)arg0 + 0x34)) = 15.0f;
    (*(f32 *)((u8 *)arg0 + 0x38)) = D_800AAD64;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = D_800AAD68;
    (*(s16 *)((u8 *)arg0 + 0x44)) = 0x19;
    (*(s16 *)((u8 *)arg0 + 0x46)) = 0xF;
    (*(s16 *)((u8 *)arg0 + 0x48)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4A)) = 0x64;
    (*(s16 *)((u8 *)arg0 + 0x4C)) = 0xC;
    (*(s16 *)((u8 *)arg0 + 0x4E)) = 0x14;
    (*(f32 *)((u8 *)arg0 + 0x40)) = D_800AAD6C;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
    s32 pad;
        (*(s8 *)((u8 *)arg0 + 0x50)) = -1;
        return;
    }
    (*(s8 *)((u8 *)arg0 + 0x50)) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C01F0.s")
#endif
typedef struct { s32 a[3]; } V3_151C0350;
void func_151C0350(u8 *arg0, f32 *arg1, u8 arg2, u8 arg3, s32 arg4) {
    f32 pad[16]; // fakematch: unused frame space
    f32 sp24[9];

    func_151C09C8(arg0, arg3, arg4);
    func_151C0AA8(arg0, arg3, arg4);
    func_151C0B54((s32)arg0, arg3, arg4);
    func_151C0BA0((struct17 *)arg0, arg3, arg4);
    if (arg2 != 0) {
        sp24[0] = -arg1[0];
        sp24[1] = -arg1[1];
        sp24[2] = -arg1[2];
        func_151C01F0(&sp24[4], &sp24[3]);
        *(V3_151C0350 *)&sp24[6] = *(V3_151C0350 *)arg0;
        func_15150108(sp24, arg3, arg4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0434.s")

#ifdef NON_MATCHING
s32 func_15046F70(s32 *, s32, f32, f32 *);
void func_1504715C(void *, u8 *);
void func_15150258(u8 *, u8, s32);

void func_151C0648(u8 *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4) {
    struct {
        s32 u28;
        f32 u2C;
        s32 u30;
        f32 u34;
        s32 u38;
        u8 pad3C[0x1C];
        s32 u58;
        f32 u5C;
        s32 u60;
        s16 u64;
        s16 u66;
        s16 u68;
        s16 u6A;
        s32 u6C;
        s32 u70;
        s32 u74;
        u8 pad78[0x8];
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        s32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        s16 uB0;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        s16 uB8;
        s16 uBA;
        s8 uBC;
    } sp;
    s32 temp_s1;

    temp_s1 = arg3 & 0xFF;
    func_151C09C8(arg0, temp_s1 & 0xFF, arg4);
    func_151C0AA8(arg0, temp_s1 & 0xFF, arg4);
    func_151C0B54((s32) arg0, temp_s1 & 0xFF, arg4);
    func_151C0BA0((struct17 *) arg0, temp_s1 & 0xFF, arg4);
    if (arg2 != 0) {
        sp.u64 = 0;
        sp.u66 = 0xFF;
        sp.u68 = -0x40;
        sp.u6A = 0x47;
        sp.u6C = 6;
        sp.u70 = 4;
        (*(s32 *)((u8 *)(&sp.u74) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)(&sp.u74) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
        (*(s32 *)((u8 *)(&sp.u74) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
        sp.u80 = 23.0f;
        sp.u84 = 30.0f;
        sp.u88 = 45.0f;
        sp.u8C = 53.0f;
        sp.u98 = 7;
        sp.u9C = 3;
        sp.uB0 = 0x19;
        sp.uB2 = 0xF;
        sp.uB4 = 0x64;
        sp.uB6 = 0x64;
        sp.uB8 = 0xC;
        sp.uBA = 0x14;
        sp.uBC = 0;
        sp.u90 = 203.0f;
        sp.u94 = 414.0f;
        sp.uA0 = 15.0f;
        sp.uA4 = 0.87200004f;
        sp.uA8 = -0.39800003f;
        sp.uAC = 0.36400002f;
        func_15150258(&sp.u64, temp_s1 & 0xFF, arg4);
    }
    if ((arg2 != 0) && (arg1 != 0)) {
        sp.u58 = (*(s32 *)((u8 *)arg0 + 0));
        sp.u5C = (*(f32 *)((u8 *)arg0 + 4)) + 100.0f;
        sp.u60 = (*(s32 *)((u8 *)arg0 + 8));
        func_1504715C(&sp.u34, arg1);
        if (func_15046F70(&sp.u58, 0, (*(f32 *)((u8 *)arg0 + 4)) - 1000.0f, &sp.u34) != 0) {
            sp.u28 = sp.u58;
            sp.u2C = sp.u34;
            sp.u30 = sp.u60;
            func_151C0910((s32) &sp.u38, (s32) &sp.u28, temp_s1 & 0xFF, arg4);
            func_151C0BF4((s32) arg0, temp_s1 & 0xFF, arg4);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0648.s")
#endif
s32 func_151C0894(u8 *arg0, u8 *arg1, s32 arg2, u8 **arg3) {
    u8 i;
    for (i = 0; i < arg2; i++) {
        if (arg0 == arg3[i]) {
            return 0;
        }
    }
    if (arg0 == arg1) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0)) == 0) {
        return 0;
    }
    if ((*(u8 *)((u8 *)arg0 + 4)) == 0xFF) {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
void func_150E856C(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);
#else
s32 func_150E856C(f32, s32, s32, s32, s16, u8, u8, u8, u8, u8, u8, s32);
#endif

void func_151C0910(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = func_150ADA68();
    sp40 = func_150ADA20();
    func_150E856C((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (func_150ADA20() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

void func_151C09C8(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 11U) + 0x14;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 121U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

void func_151C0AA8(u8 *arg0, u8 arg1, s32 arg2) {
    f32 temp_f12;
    f32 sp28;
    s32 temp_t7;
    sp28 = func_150ADA68();
    temp_t7 = (func_150ADA20() % 56U) + 0xC8;
    temp_f12 = sp28 * 4.0f + 14.0f;
    func_15154728(arg0, temp_f12, 0x3F974EB9, (f32) (u32) temp_t7, 0.0f, arg1, arg2);
}

void func_151D58E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);

void func_151C0B54(s32 arg0, u8 arg1, s32 arg2) {
    func_151D58E4(arg0, 800.0f, 2000.0f, 0.0005f, 5, arg1, arg2);
}

void func_151C0BA0(struct17 *arg0, u8 arg1, s32 arg2) {
    func_151D5404(arg0, 800.0f, 2000.0f, 0.0005f, 0xF, 0x14, (s32) arg1, arg2);
}

void func_150E892C(s32, s16, u8, s32);

void func_151C0BF4(s32 arg0, u8 arg1, s32 arg2) {
    func_150E892C(arg0, (s16) ((func_150ADA20() % 62U) + 0x78), arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0698.s")

s32 func_151C16BC(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && (*arg2 != 0)) {
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x38));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x3C));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x40));
        return 0;
    }
    *arg6 = 0;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1730.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1B20.s")

void func_151C1B20(void *arg0);
void func_15132AE0(void *arg0);
void func_15132B0C(void *arg0);

void func_151C1BAC(void *arg0) {
    func_151C1B20(arg0);
    func_15132AE0(arg0);
}

void func_151C1BD8(void *arg0) {
    func_151C1B20(arg0);
    func_15132B0C(arg0);
}

s32 func_151D4684(u8 *, s32, s32, s32, s32, s32, s32, s32);
s32 func_151D4898(u8 *, s32, s32, s32, s32);
extern s32 (*D_800E0D64)(s32, s32, s32);

void func_151C1C04(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    if (D_800E0D64 != NULL) {
        D_800E0D64((s32) (*(f32 *)((u8 *)arg0 + 0)), (s32) (*(f32 *)((u8 *)arg0 + 4)), (s32) (*(f32 *)((u8 *)arg0 + 8)));
    }
    switch (arg3) {                                 /* irregular */
    case 1:
        func_151D4898(arg0, arg1, arg2, arg4, 0x24);
        return;
    case 2:
        func_151D4898(arg0, arg1, arg2, arg4, 0x25);
        return;
    case 3:
        func_151D4684(arg0, arg1, arg2, 0, arg4, 0x16, 0x26, 0);
        return;
    default:
    case 0:
        func_151D4684(arg0, arg1, arg2, 0, arg4, 0x16, 0x15, 0);
        return;
    }
}

extern u8 D_800AAD34[];
extern u8 D_800AAD38[][12];
void func_151C1D48(u8 *arg0, u8 *arg1) {
    s32 var_v0;
    u8 temp_v0;
    u8 *p = arg0;
    temp_v0 = p[4];
    if (temp_v0 != 0x28) {
        if (temp_v0 != 0x77) {
            var_v0 = 0;
        } else {
            var_v0 = 1;
        }
    } else {
        var_v0 = 2;
    }
    func_15143134(D_800AAD38[var_v0], arg1, *(s32 *)(p + 0x1D4) + (D_800AAD34[var_v0] << 6));
}

void func_151C1DC4(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 *temp_v0 = (s32 *)(arg0 + 0x170);

    if (arg2 == 0x2D) {
        if (arg1[0] == temp_v0[0x1B]) {
            temp_v0[0x1B] = arg1[1];
        } else if (arg1[1] == temp_v0[0x1B]) {
            temp_v0[0x1B] = arg1[0];
        }
    }
}

void func_151C1E10(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 5U) + 5;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 11U) + 5, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

s32 func_151C0894();

void func_151C1EF0(s32 arg0, s32 arg1, s32 *arg2) {
    func_151C0894(arg0, arg1, *arg2, arg2 + 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C1F1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C230C.s")

void func_151C1FB8(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = (func_150ADA20() & 7) + 0xD;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        sp18[4] = ((u32)func_150ADA20() % 3) + 6;
        sp18[6] = -1;
        func_151D8E18(sp18, 0, 0xFF, 1);
    }
}
