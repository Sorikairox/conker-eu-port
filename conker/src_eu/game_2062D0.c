#include <ultra64.h>

#include "functions.h"
#include "variables.h"


u8 func_151D8E20(void) {
    if ((D_800BE9F0 == 0) && (func_150A29C8(0, 0x1C) == 0)) {
        return 10;
    }
    return D_800E0A10;
}

u8 func_151D8E6C(void) {
    u8 tmp[3] = D_800AB340;
    return tmp[(func_150ADA20() % 3U)];
}

u8 func_151D8EB0(void) {
    return 117;
}

u8 func_151D8EBC(void) {
    return 29;
}

u8 func_151D8EC8(void) {
    s32 tmp;

    if (func_150ADA20() & 1) {
        tmp = 17;
    } else {
        tmp = 147;
    }
    return tmp;
}

u8 func_151D8EFC(void) {
    s32 tmp;

    if (func_150ADA20() & 1) {
        tmp = 90;
    } else {
        tmp = 91;
    }
    return tmp;
}

u8 func_151D8F30(void) {
    u8 tmp[5] = D_800AB344;
    return tmp[func_150ADA20() % 5U];
}

u8 func_151D8F7C(void) {
    s32 tmp;

    if ((func_150ADA20() & 1) != 0) {
        tmp = 102;
    } else {
        tmp = 103;
    }
    return tmp;
}

u8 func_151D8FB0(void) {
    return 149;
}

u8 func_151D8FBC(void) {
    return 159;
}

u8 func_151D8FC8(void) {
    return 179;
}

u8 func_151D8FD4(void) {
    return 117;
}

u8 func_151D8FE0(void) {
    u8 tmp[4] = D_800AB34C;
    return tmp[func_150ADA20() & 3];
}

// big struct definition
// void func_151D9014(void *arg0, f32 *arg1, u8 arg2, f32 arg3, s16 arg4, u8 arg5, f32 arg6, u8 arg7, f32 arg8, f32 arg9, u8 argA, s32 argB, u8 argC, u8 argD, u8 argE, s32 argF);
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9014.s")

s32 func_151D93F4(void *arg0, void *arg1) {
    s32 res;

    if (func_151D9450(arg0, arg1) != 0) {
        if (func_151D9534(arg0, arg1) != 0) {
            res = 1;
        } else {
            res = 0;
        }
    } else {
        res = 0;
    }
    return res;
}

s32 func_151D9450(struct_eu_2062D0_d *arg0, s32 arg1) {
    struct_eu_2062D0_d_sub *sub = &arg0->unkA8;

    if (arg0->unkC1 & 1) {
        return 1;
    }
    sub->unk4 += sub->unk6 * D_800BE9E4;
    sub->unk5 += sub->unk7 * D_800BE9E4;
    arg0->unk38 = func_151423D8(sub->unk4 - 0x40) * sub->unk8 + sub->unk0;
    arg0->unk3C = func_151423D8(sub->unk5 - 0x40) * sub->unkC + sub->unk0;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9534.s")

u8 func_151D97A8(void) {
    s32 tmp[7] = D_800AB350;
    return tmp[func_150ADA20() % 7U];
}

u8 func_151D9820(void) {
    s32 tmp[3] = D_800AB36C;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9878(void) {
    s32 tmp[3] = D_800AB378;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D98D0(void) {
    s32 tmp[2] = D_800AB384;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9918(void) {
    s32 tmp[2] = D_800AB38C;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9960(void) {
    s32 tmp[5] = D_800AB394;
    return tmp[func_150ADA20() % 5U];
}

u8 func_151D99C8(void) {
    s32 tmp[3] = D_800AB3A8;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9A20(void) {
    s32 tmp[2] = D_800AB3B4;
    return tmp[func_150ADA20() & 1];
}

u8 func_151D9A68(void) {
    s32 tmp[3] = D_800AB3BC;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9AC0(void) {
    s32 tmp[1] = D_800AB3C8;
    return tmp[0];
}

u8 func_151D9ADC(void) {
    s32 tmp[3] = D_800AB3CC;
    return tmp[func_150ADA20() % 3U];
}

u8 func_151D9B34(void) {
    s32 tmp[4] = D_800AB3D8;
    return tmp[func_150ADA20() & 3];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B8C.s")

void func_151D9EB0(struct_eu_2062D0_e *arg0) {
    struct_eu_2062D0_e_sub *sub = &arg0->unk28;

    sub->unk0 -= D_800BE9E4;
    if (sub->unk0 < 0) {
        func_151D9014(sub->unk8, (f32 *)D_800A5860, sub->unk16, func_150ADA68() * D_800AB844 + D_800AB848, (u32)func_150ADA20() % 41 + 0x23, sub->unk14, sub->unk4, 0, 1.0f, 1.0f, sub->unk15, 0, 1, 0, arg0->unkC, arg0->unk1);
        sub->unk0 = (u32)func_150ADA20() % 111 + 30;
    }
}

void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    func_151DBCBC(arg0, arg1 * 0.5f, arg2, arg3, arg4, arg5, arg6);
    if ((arg0 != 5) && (arg0 != 2)) {
        func_151DA08C(arg0, arg1 * D_800AB46C, 1.0099999904632568f, arg2, 100, arg3, arg4, arg5, arg6);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA08C.s")
#ifdef NON_MATCHING
s32 func_151DB5D0(u8, f32 *, f32 *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);

s32 func_151DA368(u8 *arg0) {
    struct {
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
    } sp;
    f32 sp98;
    f32 sp94;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f2;
    s16 temp_s0;
    s16 temp_s0_2;
    u8 temp_a0;
    u8 *temp_s2;

    temp_a0 = (*(u8 *)((u8 *)arg0 + 0x128)) + ((*(s8 *)((u8 *)arg0 + 0x12A)) * D_800BE9E4);
    (*(u8 *)((u8 *)arg0 + 0x128)) = temp_a0;
    (*(u8 *)((u8 *)arg0 + 0x129)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x129)) + ((*(s8 *)((u8 *)arg0 + 0x12B)) * D_800BE9E4));
    temp_s2 = arg0 + 0x128;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((func_151423D8((temp_a0 - 0x40) & 0xFF) * (*(f32 *)((u8 *)temp_s2 + 4))) + (*(f32 *)((u8 *)temp_s2 + 0x10)));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((func_151423D8(((*(u8 *)((u8 *)temp_s2 + 1)) - 0x40) & 0xFF) * (*(f32 *)((u8 *)temp_s2 + 8))) + (*(f32 *)((u8 *)temp_s2 + 0x10)));
    (*(f32 *)((u8 *)temp_s2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0xC)) + ((0.15f + (func_150ADA68() * 0.1f)) * D_800BE9A4));
    temp_f2 = ((*(f32 *)((u8 *)arg0 + 0x2C)) + (*(f32 *)((u8 *)arg0 + 0x30))) * 0.5f;
    if ((*(f32 *)((u8 *)temp_s2 + 0xC)) > 1.0f) {
        sp98 = temp_f2 * 500.0f;
        sp94 = temp_f2 * 471.0f;
        do {
            temp_s0 = func_150ADA20() & 0xFF;
            temp_f20 = func_150ADA68() * sp98;
            temp_f22 = func_151423D8((temp_s0 - 0x40) & 0xFF);
            sp.uC4 = (*(f32 *)((u8 *)arg0 + 0x34)) + (func_151423D8(temp_s0 & 0xFF) * temp_f20);
            sp.uC8 = (*(f32 *)((u8 *)arg0 + 0x38)) + -3.5f;
            sp.uCC = (*(f32 *)((u8 *)arg0 + 0x3C)) + (temp_f22 * temp_f20);
            sp.uB8 = 0.0f;
            sp.uBC = 0.0f;
            sp.uC0 = 0.0f;
            temp_s0_2 = (func_150ADA20() % 51U) + 0x96;
            temp_f20_2 = func_150ADA68();
            func_151DB5D0((*(u8 *)((u8 *)temp_s2 + 0x18)), &sp.uC4, &sp.uB8, sp94, ((temp_f20_2 * 154.0f) + 10106.0f) * 0.0001f, 1.0f, ((func_150ADA68() * 25.0f) + -50.0f) * 0.001f, (s32) temp_s0_2, 0x9B, (s32) temp_s0_2, 0xFF / temp_s0_2, 1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            (*(f32 *)((u8 *)temp_s2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s2 + 0xC)) > 1.0f);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA368.s")
#endif
// TODO when we know what arg0 is...
s32 func_151DA6A8(struct_eu_2062D0 *arg0) {
    s32 i;
    struct_eu_2062D0_sub *p;

    if (arg0->unk58 & 1) {
        p = &arg0->unk128;
        i = D_800BE9E4;
        while (i--) {
            p->unk10 *= p->unk14;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA6F8.s")
typedef struct { f32 x, y, z; s32 a, b; } Node14;
extern f32 D_800AB87C;
s32 func_151DAB58(u8, f32, u8, f32 *, s32, s32, s32);
s32 func_151DA938(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5)
{
  u8 *tbl;
  u8 *obj;
  f32 pos[3];
  u8 *p;
  s32 pad;
  pad = 0x48; // fakematch: keeps obj + 0x48 in v0 (permuter)
  tbl = *((u8 **) (arg0 + 0x94));
  obj = *((u8 **) (arg0 + 0x98));
  pos[0] = ((Node14 *) tbl)[*((s8 *) (arg0 + 0x2D))].x;
  pos[1] = arg4 + 2.0f;
  pos[2] = ((Node14 *) tbl)[*((s8 *) (arg0 + 0x2D))].z;
  if (func_150ADA20() & 1)
  {
    p = obj + pad;
    func_151D9B8C(*((u8 *) (p + 8)), (*((f32 *) p)) * ((*((f32 *) (obj + 0))) * 3.0f), *((u8 *) (obj + 0x1B)), arg5, (struct17 *) pos, 0x64, 0, 1, 0, *((u8 *) (arg0 + 0xC)), *((u8 *) (arg0 + 1)));
  }
  else
  {
    p = obj + pad;
    func_151DAB58(*((u8 *) (p + 8)), (*((f32 *) p)) * ((*((f32 *) (obj + 0))) * D_800AB87C), *((u8 *) (obj + 0x1B)), pos, 1, *((u8 *) (arg0 + 0xC)), *((u8 *) (arg0 + 1)));
  }
  *((s8 *) (obj + 0x20)) = 4;
  return 1;
}
s32 func_151DAA88(struct_eu_2062D0_c *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    struct_eu_2062D0_c_sub *sub = arg0->unk98;
    struct_eu_2062D0_pt *pts = arg0->unk94;
    struct17 sp34;

    sp34.unk0 = pts[arg0->unk2D].unk0;
    sp34.unk4 = arg4;
    sp34.unk8 = pts[arg0->unk2D].unk8;
    func_151D9FC0(sub->unk50, sub->unk0 * 11.0f * sub->unk4C, sub->unk1B, arg5, &sp34, arg0->unkC, arg0->unk1);
    sub->unk20 = 4;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAB58.s")
s32 func_151DADA0(struct_eu_2062D0_b *arg0) {
    struct_eu_2062D0_b_sub *sub = &arg0->unk110;
    f32 f0;

    sub->unk0 += sub->unk1 * D_800BE9E4;
    f0 = func_151423D8(sub->unk0 - 0x40);
    arg0->unk4C = sub->unk4 * f0 + 1.0f;
    arg0->unk50 = D_800AB890 - sub->unk8 * f0;
    return 1;
}
#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_151DAE28(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        u8 pad38[0x10];
        u8 * u48;
        u8 * u4C;
    } sp;
    u8 *sp30;
    s32 sp2C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f16;
    s32 temp_f16_2;
    s32 temp_f16_3;
    s32 temp_f6;
    s32 temp_f6_2;
    s32 temp_f8;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u4C, &sp.u37);
    sp.u48 = sp.u4C;
    if (sp.u4C != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C)) * (*(f32 *)((u8 *)arg0 + 0x4C));
        (*(s16 *)((u8 *)sp.u4C + 6)) = 0;
        (*(s16 *)((u8 *)sp.u4C + 0x16)) = 0;
        temp_f2 = *(&D_800DD608 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u4C + 0x26)) = 0;
        temp_f12 = *(&D_800DD618 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp.u4C + 0x36)) = 0;
        temp_f8 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
        (*(s16 *)((u8 *)sp.u4C + 0x30)) = (s16) temp_f8;
        (*(s16 *)((u8 *)sp.u4C + 0)) = (s16) temp_f8;
        temp_f16 = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(s16 *)((u8 *)sp.u4C + 0x12)) = (s16) temp_f16;
        (*(s16 *)((u8 *)sp.u4C + 2)) = (s16) temp_f16;
        temp_f6 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
        (*(s16 *)((u8 *)sp.u4C + 0x34)) = (s16) temp_f6;
        (*(s16 *)((u8 *)sp.u4C + 4)) = (s16) temp_f6;
        temp_f16_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
        (*(s16 *)((u8 *)sp.u4C + 0x20)) = (s16) temp_f16_2;
        (*(s16 *)((u8 *)sp.u4C + 0x10)) = (s16) temp_f16_2;
        temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x30)) * (*(f32 *)((u8 *)arg0 + 0x50))));
        (*(s16 *)((u8 *)sp.u4C + 0x32)) = (s16) temp_f6_2;
        (*(s16 *)((u8 *)sp.u4C + 0x22)) = (s16) temp_f6_2;
        temp_f16_3 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
        (*(s16 *)((u8 *)sp.u4C + 0x24)) = (s16) temp_f16_3;
        (*(s16 *)((u8 *)sp.u4C + 0x14)) = (s16) temp_f16_3;
        return sp.u48;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAE28.s")
#endif
void func_151DB004(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = 0;
    arg0->unk1A = 0;
}

void func_151DB068(struct218 *arg0) {
    arg0->unk14 = arg0->unk15 = (func_150ADA20() % 0x38U) + 100;
    arg0->unk16 = 0;
    arg0->unk18 = arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB0CC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB15C(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB1EC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB27C(struct218 *arg0) {
    arg0->unk14 = 0xFF;
    arg0->unk15 = 0xFF;
    arg0->unk16 = 0xFF;
    arg0->unk18 = 0xB4;
    arg0->unk19 = 0xC8;
    arg0->unk1A = 0xC8;
}

void func_151DB2A8(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = 200;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = 200;
    arg0->unk1A = 0;
}

void func_151DB2CC(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk1A = 0;
}

void func_151DB330(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x15U) + 95;
    arg0->unk15 = (func_150ADA20() % 0x15U) + 95;
    arg0->unk16 = (func_150ADA20() % 0xBU) + 45;
    arg0->unk18 = (func_150ADA20() & 0xF) + 58;
    arg0->unk19 = (func_150ADA20() & 0xF) + 60;
    arg0->unk1A = (func_150ADA20() % 0xBU) + 25;
}

void func_151DB3D8(struct218 *arg0) {
    arg0->unk14 = 0;
    arg0->unk15 = arg0->unk16 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk18 = 0;
    arg0->unk19 = arg0->unk1A = (func_150ADA20() % 0x2EU) + 180;
}

void func_151DB43C(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk15 = 0;
    arg0->unk16 = (func_150ADA20() % 0x38U) + 80;
    arg0->unk18 = (func_150ADA20() % 0x2EU) + 180;
    arg0->unk19 = 0;
    arg0->unk1A = (func_150ADA20() % 0x2EU) + 180;
}

void func_151DB4CC(struct218 *arg0) {
    arg0->unk14 = (func_150ADA20() % 56U) + 200;
    arg0->unk15 = (func_150ADA20() % 56U) + 200;
    arg0->unk16 = (func_150ADA20() % 56U) + 200;
    arg0->unk18 = (func_150ADA20() % 56U) + 200;
    arg0->unk19 = (func_150ADA20() % 56U) + 200;
    arg0->unk1A = (func_150ADA20() % 56U) + 200;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB5D0.s")
typedef struct { u8 fl; u8 pad1[3]; s32 unk4; u8 a[3]; u8 d[3]; u8 padE[2]; f32 s[3]; } S97C;
s32 func_15131E88(u8 *, s32);
s32 func_151DB97C(u8 *arg0, s32 arg1) {
    S97C *p;
    f32 z;
    f32 y;
    f32 x;
    p = (S97C *)(arg0 + 0xA8);
    if (p->fl & 2) {
        func_15131E88(arg0 + 0x58, *(s32 *)(arg0 + 0xAC));
    }
    if (p->fl & 1) {
        p->a[0] += p->d[0] * D_800BE9E4;
        p->a[1] += p->d[1] * D_800BE9E4;
        p->a[2] += p->d[2] * D_800BE9E4;
        x = func_151423D8(p->a[0] - 0x40);
        y = func_151423D8(p->a[1] - 0x40);
        z = func_151423D8(p->a[2] - 0x40);
        *(f32 *)(arg0 + 0x4C) = p->s[0] * x;
        *(f32 *)(arg0 + 0x50) = p->s[1] * y;
        *(f32 *)(arg0 + 0x54) = p->s[2] * z;
    }
    return 1;
}

extern f32 D_800AB8A0;
extern f32 D_800AB8A4;
extern f32 D_800AB8A8;
extern f32 D_800AB8AC;

void func_151DBAA8(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 s;

    s.unk8 = *arg0;
    s.unk14 = 5.5f;
    s.unk18 = D_800AB8A0;
    s.unk1C = D_800AB8A4;
    s.unk20 = D_800AB8A8;
    s.unk24 = 10.0f;
    s.unk28 = D_800AB8AC;
    s.unk2C = arg1;
    s.unk2E = 0;
    s.unk2 = 0xFF;
    s.unk4 = -0x40;
    s.unk6 = 0x2E;
    s.unk0 = 0;
    s.unk30 = 3;
    s.unk32 = 2;
    s.unk34 = 0x1E;
    s.unk36 = 0x1E;
    s.unk38 = 0x9B;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 0.5f;
    s.unk48 = 0;
    s.unk3C = arg2;
    func_15154488(&s, &s.unk8, 0, arg3, arg4);
}

void func_151DBBD4(struct17 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4) {
    struct17 tmp;
    struct217 tmp2;

    tmp.unk0 = arg0->unk0;
    tmp.unk4 = arg0->unk4 + 5.0f;
    tmp.unk8 = arg0->unk8;

    tmp2.unkF = *arg2;
    tmp2.unk0 = func_150ADA68();
    tmp2.unk4 = func_150ADA20();

    func_151D9B8C(tmp2.unkF, (tmp2.unk0 * 25.0f) + 10.0f, ((tmp2.unk4 % 0x38U) + 200), arg1 + 4, &tmp, (func_150ADA20() % 0x97U) + 150, 0, 1, 0, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBCBC.s")
#ifdef NON_MATCHING
extern s32 D_800AB7F4;

void func_151DBE80(s32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9) {
    struct {
        s8 u58;
        s8 u59;
        s16 u5A;
        s16 u5C;
        u8 pad5E[0x2];
        s32 u60;
        s32 u64;
        u8 u68;
        u8 u69;
        u8 u6A;
        s8 u6B;
        f32 u6C;
        f32 u70;
        s32 u74;
        u8 pad78[0x8];
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        u8 u9C;
        s8 u9D;
        s8 u9E;
        s8 u9F;
        s32 uA0;
        s8 uA4;
        u8 padA5[0x3];
        s32 uA8;
        s16 uAC;
        s16 uAE;
    } sp;
    s32 sp50;
    s32 sp4C;
    s32 var_v1;
    u8 *temp_v0;

    sp.u58 = 0x38;
    if (arg7 != 0) {
        var_v1 = 2;
    } else {
        var_v1 = 1;
    }
    temp_v0 = ((arg0 & 0xFF) * 3) + &D_800AB7F4;
    sp.u5A = var_v1 + 0x440000;
    sp.u5C = arg3;
    sp.u60 = 0;
    sp.u64 = 0x4000;
    sp.u6B = 0xFF;
    sp.u68 = (*(u8 *)((u8 *)temp_v0 + 0));
    sp.u6C = 1.0f;
    sp.u70 = 1.0f;
    sp.u69 = (*(u8 *)((u8 *)temp_v0 + 1));
    sp.u6A = (*(u8 *)((u8 *)temp_v0 + 2));
    (*(s32 *)((u8 *)(&sp.u74) + 0)) = (s32) (*(s32 *)((u8 *)arg4 + 0));
    (*(s32 *)((u8 *)(&sp.u74) + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
    (*(s32 *)((u8 *)(&sp.u74) + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
    sp.u8C = arg2;
    sp.u98 = 0x466C0001;
    sp.u9D = 0xFF;
    sp.u59 = 0;
    sp.u9E = 0;
    sp.u9F = 6;
    sp.uA0 = 0;
    sp.uA4 = 0xFF;
    sp.uA8 = 0;
    sp.uAC = 1;
    sp.uAE = 0xFF;
    sp.u90 = 1.0f;
    sp.u94 = 1.0f;
    sp.u80 = 0.0f;
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
    sp.u9C = arg6;
    sp4C = func_150ADA20();
    sp50 = func_150ADA20();
    func_1513D668((s32) &sp.u58, 0, 0xBU, 0x11U, 0U, (u8) ((sp50 & 1) + (sp4C & 1)), (s16) (func_150ADA20() & 0xFF), arg1, arg1, 0, arg5, 0U, 0, (u8) (s32) arg8, arg9);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBE80.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC034.s")
extern f32 D_800AB8B0;
extern f32 D_800AB8B4;
extern f32 D_800AB8B8;
extern f32 D_800AB8BC;
extern f32 D_800AB8C0;

typedef struct {
    s16 u0[4];
    struct17 pos;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S06E8;

s32 func_151506E8(S06E8 *, struct17 *, s32, u8, s32);

void func_151DC260(struct17 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 s;
    S06E8 t;

    s.unk8 = *arg0;
    s.unk14 = 3.0f;
    s.unk18 = 4.0f;
    s.unk1C = D_800AB8B0;
    s.unk20 = D_800AB8B4;
    s.unk24 = 12.0f;
    s.unk28 = 11.0f;
    s.unk2C = 10;
    s.unk2E = 10;
    s.unk2 = 0xFF;
    s.unk4 = -0x40;
    s.unk6 = 0x28;
    s.unk0 = 0;
    s.unk30 = 3;
    s.unk32 = 1;
    s.unk34 = 0x3C;
    s.unk36 = 0x28;
    s.unk38 = 0x64;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 1.0f;
    s.unk48 = 0;
    s.unk3C = arg2;
    func_15154488(&s, &s.unk8, arg1, arg3, arg4);
    {
    struct17 *p = &t.pos;
    *p = *arg0;
    t.u18 = 6.0f;
    t.u1C = 8.0f;
    t.u14 = 0xC;
    t.u16 = 6;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u24 = D_800AB8B8;
    t.u0[3] = 0x24;
    t.u20 = 0x23;
    t.u22 = 0xF;
    t.u28 = D_800AB8BC;
    t.u2C = 0x9B;
    t.u2D = 0x64;
    t.u38 = 1;
    t.u30 = 123.0f;
    t.u39 = arg2;
    t.u34 = 134.0f;
    t.u40 = 1;
    t.u3C = D_800AB8C0;
    t.u44 = 0.0f;
    func_151506E8(&t, p, arg1, arg3, arg4);
    }
}
extern f32 D_800AB8C4;
extern f32 D_800AB8C8;
extern f32 D_800AB8CC;
extern f32 D_800AB8D0;
extern f32 D_800AB8D4;



void func_151DC484(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 s;
    S06E8 t;

    s.unk8 = *(struct17 *)arg0;
    s.unk0 = 0;
    s.unk14 = 3.0f;
    s.unk18 = 2.0f;
    s.unk1C = D_800AB8C4;
    s.unk20 = D_800AB8C8;
    s.unk24 = 8.0f;
    s.unk28 = 5.0f;
    s.unk2C = 8;
    s.unk2E = 6;
    s.unk2 = 0xFF;
    s.unk4 = -0x40;
    s.unk6 = 0x28;
    s.unk30 = 3;
    s.unk32 = 0;
    s.unk34 = 0x3C;
    s.unk36 = 0x28;
    s.unk38 = 0x64;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 1.0f;
    s.unk48 = 0;
    s.unk3C = arg2;
    func_15154488(&s, &s.unk8, (s32)arg1, arg3, arg4);
    {
    struct17 *p = &t.pos;
    *p = *(struct17 *)arg0;
    t.u18 = 7.0f;
    t.u1C = 3.0f;
    t.u24 = D_800AB8CC;
    t.u28 = D_800AB8D0;
    t.u14 = 0xC;
    t.u16 = 6;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u0[3] = 0x1A;
    t.u20 = 0x23;
    t.u22 = 0xF;
    t.u2C = 0x9B;
    t.u2D = 0x64;
    t.u30 = 59.0f;
    t.u34 = 59.0f;
    t.u38 = 1;
    t.u39 = arg2;
    t.u3C = D_800AB8D4;
    t.u40 = 1;
    t.u44 = 0.0f;
    func_151506E8(&t, p, (s32)arg1, arg3, arg4);
    }
}

// typedef struct {
//     s16 unk10; // sp24
//     s16 unk12; // sp26
//     s16 unk14;
//     s16 unk16; // sp2A
//     s32 unk18[3];
//     s16 unk24; // sp38;
//     s16 unk26; // sp3A
//     f32 unk28; // sp3C
//     f32 unk2C; // sp40
//     s16 unk30; // sp44
//     s16 unk32; // sp46
//     f32 unk34; // sp48;
//     f32 unk38; // sp4C;
//     s8  unk3C; // sp50;
//     s8  unk3D; // sp51;
//     u8  unk3E[2]; //
//     f32 unk40; // sp54
//     f32 unk44; // sp58
//     s8  unk48; // sp5C
//     u8  unk49; // sp5D
//     u8  unk4A[2];
//     f32 unk4C; // sp60
//     s8  unk50; // sp64
//     u8  pad51[3];
//     f32 unk54; // sp68
// } struct217;
//
// typedef struct {
//     s16 unk58; // sp6C
//     s16 unk5A; // sp6E
//     s16 unk5C; // sp70
//     s16 unk5E; // sp72
//     s32 unk60[3]; // sp74
//     f32 unk6C; // sp80
//     f32 unk70; // sp84
//     f32 unk74; // sp88
//     f32 unk78; // sp8C
//     f32 unk7C; // sp90
//     f32 unk80; // sp94
//     s16 unk84; // sp98
//     s16 unk86; // sp9A
//     s16 unk88; // sp9C
//     s16 unk8A; // sp9E
//     s16 unk8C; // spA0
//     s16 unk8E; // spA2
//     s16 unk90; // spA4
//     s16 unk92; // spA6
//     u8  unk94; // spA8;
//     u8  pad95[3];
//     f32 unk98; // spAC;
//     s16 unk9C; // spB0
//     s16 unk9E; // spB2
//     s32 unkA0; // spB4
// } struct218;
//
// void func_151DC484(struct00 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
//     struct218 tmp2;
//     struct217 tmp;
//
//     tmp2.unk60[0] = arg0->unk0; // sp74.unk0 = (s32) arg0->unk0;
//     tmp2.unk60[1] = arg0->unk4; // sp74.unk4 = (s32) arg0->unk4;
//     tmp2.unk60[2] = arg0->unk8; // sp74.unk8 = (s32) arg0->unk8;
//
//     tmp2.unk5A = 0xFF;   // sp6E = 0xFF;
//     tmp2.unk5C = -0x40;  // sp70 = -0x40;
//     tmp2.unk84 = 8;      // sp98 = 8;
//     tmp2.unk86 = 6;      // sp9A = 6;
//     tmp2.unk58 = 0;      // sp6C = 0;
//     tmp2.unk88 = 3;      // sp9C = 3;
//     tmp2.unk8A = 0;      // sp9E = 0;
//     tmp2.unk5E = 0x28;   // sp72 = 0x28;
//     tmp2.unk8C = 0x3C;   // spA0 = 0x3C;
//     tmp2.unk8E = 0x28;   // spA2 = 0x28;
//
//     tmp2.unk6C = 3.0f;   // sp80 = 3.0f;
//     tmp2.unk90 = 100;     // spA4 = 0x64;
//     tmp2.unk92 = 100;     // spA6 = 0x64;
//     tmp2.unk9C = 16;      // spB0 = 0x10;
//     tmp2.unk9E = 15;      // spB2 = 0xF;
//     tmp2.unk70 = 2.0f;       // sp84 = 2.0f;
//     tmp2.unk74 = D_800AB4E4; // sp88 = D_800AB4E4;
//     tmp2.unk78 = D_800AB4E8; // sp8C = D_800AB4E8;
//     tmp2.unk7C = 8.0f;       // sp90 = 8.0f;
//     tmp2.unk80 = 5.0f;       // sp94 = 5.0f;
//     tmp2.unk98 = 1.0f;       // spAC = 1.0f; 0x3f80
//     tmp2.unk94 = arg2;       // spA8 = arg2;
//     tmp2.unkA0 = 0;      // spB4 = 0;
//
//     // func_15153F18(&sp6C, &sp74, arg1, arg3, arg4);
//     func_15153F18(&tmp2, &tmp2, arg1, arg3, arg4);
//
//     tmp.unk18[0] = arg0->unk0; // sp2C.unk0 = (s32) arg0->unk0;
//     tmp.unk18[1] = arg0->unk4; // sp2C.unk4 = (s32) arg0->unk4;
//     tmp.unk18[2] = arg0->unk8; // sp2C.unk8 = (s32) arg0->unk8;
//
//     tmp.unk24 = 0xC; // sp38 = 0xC;
//     tmp.unk12 = 0xFF;   // sp26 = 0xFF;
//     tmp.unk26 = 6;      // sp3A = 6;
//     tmp.unk10 = 0;      // sp24 = 0;
//     tmp.unk14 = -0x40;  // sp28 = -0x40;
//     tmp.unk16 = 0x1A;   // sp2A = 0x1A;
//     tmp.unk30 = 0x23;   // sp44 = 0x23;
//     tmp.unk32 = 0xF;    // sp46 = 0xF;
//     tmp.unk3C = 0x9B;   // sp50 = 0x9B;
//     tmp.unk3D = 0x64;   // sp51 = 0x64;
//     tmp.unk40 = 59.0f;  // sp54 = 59.0f;
//     tmp.unk44 = 59.0f;  // sp58 = 59.0f;
//     tmp.unk48 = 1;      // sp5C = 1;
//     tmp.unk50 = 1;      // sp64 = 1;
//     tmp.unk54 = 0.0f;   // sp68 = 0.0f;
//     tmp.unk28 = 7.0f;   // sp3C = 7.0f;
//     tmp.unk2C = 3.0f;   // sp40 = 3.0f;
//     tmp.unk34 = D_800AB4EC; // sp48 = D_800AB4EC;
//     tmp.unk38 = D_800AB4F0; // sp4C = D_800AB4F0;
//     tmp.unk49 = arg2;       // sp5D = arg2;
//     tmp.unk4C = D_800AB4F4; // sp60 = D_800AB4F4;
//     // func_15150178(&sp24, &sp2C, arg1, arg3, arg4);
//     func_15150178(&tmp, &tmp.unk18, arg1, arg3, arg4);
// }
