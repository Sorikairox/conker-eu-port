#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_151C0AA8
void func_15154728(u8 *, f32, s32, f32, f32, u8, s32);
// hoisted forward declaration(s) for func_151C0350
void func_151C09C8(u8 *, u8, s32);
void func_151C0B54(s32, u8, s32);
void func_151C0BA0(struct17 *, u8, s32);
void func_15150108(f32 *, u8, s32);
void func_151C01F0(f32 *, f32 *);
void func_151C0AA8(u8 *, u8, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C01F0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EDA00/func_151C0648.s")

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
