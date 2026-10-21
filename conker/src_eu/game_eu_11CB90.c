#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0x8];
    s32 *unk8;
    u8  unkC;
} struct_eu_11CB90_60;

typedef struct {
    u8  pad0[0x12C];
    s32 unk12C[1];
} struct_eu_11CB90_elem;

void func_150F0820(void *arg0);
void func_150F0898(void *arg0);
void func_150F0900(void *arg0);
void func_150F0968(void *arg0);
void func_151617C4(void *arg0);
void func_151617E4(void *arg0);


extern u8 D_800A1A0C[];
extern u8 D_800A1A08[];
extern struct17 D_800A19C0[];
void func_150EF500(struct127 *, u8, s32, s32);
void func_150F0FA4(u8 *);

void func_150EEE00(struct127 *arg0, u8 arg1) {
    struct17 pos;
    Header header;
    Header2 header2;

    if (D_800A1A0C[arg1] & arg0->unk94) {
        return;
    }
    func_150EF500(arg0, arg1, 0xFF, 1);
    if (arg0->unk1D4 == NULL) {
        return;
    }
    func_15143134(&D_800A19C0[arg1], &pos, (u8 *)(0, arg0->unk1D4) + (D_800A1A08[arg1] << 6)); // fakematch: comma from the permuter (register choice)
    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (u32)func_150ADA20() % 3 + 4;
    header.unk4 = 0;
    header2.unk0 = pos.unk0;
    header2.unk4 = pos.unk4;
    header2.unk8 = pos.unk8;
    func_151602C0(&header, &header2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
    func_150F0FA4((u8 *)&pos);
}

void func_150EEF40(u8 *arg0, u8 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = arg1;
    func_151403A8(&tmp, 0x43);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF90C.s")

s32 func_150EFD04(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x28) {
        return 1;
    }
    return 0;
}

void func_150EFD30(u8 *arg0) {
    u8 **q = &arg0; // fakematch: forces the arg0 home-slot reload
    s32 var_s0;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    struct102 *temp_a0_3;
    struct102 *temp_a0_4;
    u8 *temp_s3;
    u8 *var_s1;

    var_s0 = 0;
    temp_s3 = *q + 0x110;
    var_s1 = temp_s3;
    do {
        temp_a0 = (*(struct102 **)((u8 *)var_s1 + 0x1C));
        if (temp_a0 != NULL) {
            func_1516972C(temp_a0);
        }
        var_s0 += 4;
        var_s1 += 4;
    } while (var_s0 != 8);
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s3 + 0x24));
    if (temp_a0_2 != NULL) {
        func_1516972C(temp_a0_2);
    }
    temp_a0_3 = (*(struct102 **)((u8 *)temp_s3 + 0x28));
    if (temp_a0_3 != NULL) {
        func_1516972C(temp_a0_3);
    }
    temp_a0_4 = (*(struct102 **)((u8 *)temp_s3 + 0x2C));
    if (temp_a0_4 != NULL) {
        func_1516972C(temp_a0_4);
    }
    func_1513CA6C(*q);
}

void func_150EFDE0(u8 *arg0) {
    u8 **q = &arg0; // fakematch: forces the arg0 home-slot reload
    s32 var_s0;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    struct102 *temp_a0_3;
    struct102 *temp_a0_4;
    u8 *temp_s3;
    u8 *var_s1;

    var_s0 = 0;
    temp_s3 = *q + 0x110;
    var_s1 = temp_s3;
    do {
        temp_a0 = (*(struct102 **)((u8 *)var_s1 + 0x1C));
        if (temp_a0 != NULL) {
            func_1516979C(temp_a0);
        }
        var_s0 += 4;
        var_s1 += 4;
    } while (var_s0 != 8);
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s3 + 0x24));
    if (temp_a0_2 != NULL) {
        func_1516979C(temp_a0_2);
    }
    temp_a0_3 = (*(struct102 **)((u8 *)temp_s3 + 0x28));
    if (temp_a0_3 != NULL) {
        func_1516979C(temp_a0_3);
    }
    temp_a0_4 = (*(struct102 **)((u8 *)temp_s3 + 0x2C));
    if (temp_a0_4 != NULL) {
        func_1516979C(temp_a0_4);
    }
    func_1513CAA0(*q);
}

void func_150EFE90(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x110;
    if (arg2 == 0) {
        s32 x = *(s32 *)v; s32 y = *(s32 *)arg1; s32 p = v[4]; s32 q = arg1[4];
        if (x == y || q == p) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
        if (*(s32 *)arg1 == *(s32 *)(v + 8)) {
            *(s32 *)(v + 8) = *(s32 *)(arg1 + 4);
            v[0xC] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 8)) {
            *(s32 *)(v + 8) = *(s32 *)arg1;
            v[0xC] = arg1[8];
        }
        goto end; end: ; // fakematch: no-op label ends the 0x2D arm like the ref (b to the epilogue not delay-filled)
    } else if (arg2 == 0x43) {
        if (*(s32 *)arg1 == *(s32 *)v || arg1[4] == v[4]) {
            if (arg1[5] == v[0xD]) {
                func_1516972C(arg0);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFFCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0448.s")

#ifdef NON_MATCHING
s32 func_150F066C(u8 *arg0) {
    s32 temp_t4;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x178));
    if ((*(u8 *)((u8 *)temp_v0 + 0x128)) & 1) {
        temp_v1 = temp_v0 + 0x110;
        (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x34));
        (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x38));
        (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x3C));
        (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x34)) + ((*(f32 *)((u8 *)temp_v1 + 0x30)) * 500.0f));
        (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x38)) + ((*(f32 *)((u8 *)temp_v1 + 0x34)) * 500.0f));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x58)) | 6);
        (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x3C)) + ((*(f32 *)((u8 *)temp_v1 + 0x38)) * 500.0f));
    } else {
        temp_t4 = (*(s32 *)((u8 *)arg0 + 0x58)) & ~4;
        (*(s32 *)((u8 *)arg0 + 0x58)) = temp_t4;
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (temp_t4 & ~2);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F066C.s")
#endif
struct225 *func_150F0718(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    struct225 *r;
    s8 sp4C[8];
    s32 sp40[3];
    s32 sp3C;
    struct225 *sp54;

    sp3C = arg4;
    sp4C[0] = 2;
    sp4C[1] = -1;
    *(s16 *)(sp4C + 2) = 0x12C;
    sp4C[4] = 0x21;
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    r = func_151602C0(sp4C, sp40, arg0, arg1, arg2, arg3, 0xFF, 0, 4, arg5, arg6);
    if (r != NULL) {
        memcpy((u8 *)r + 0x18, &sp3C, 4);
        sp54 = r;
        r = sp54;
    }
    return r;
}

void func_150F07E0(void *arg0) {
    func_150F0820(arg0);
}

void func_150F0800(void *arg0) {
    func_150F0820(arg0);
}

void func_150F0820(void *arg0) {
    struct_eu_11CB90_60 *temp_v0 = *(struct_eu_11CB90_60 **)((u8 *)arg0 + 0x60);
    s32 *temp_v1 = temp_v0->unk8;
    ((struct_eu_11CB90_elem *)temp_v1)->unk12C[temp_v0->unkC] = 0;
}

void func_150F0840(void *arg0) {
    func_150F0898(arg0);
    func_1514933C(arg0);
}

void func_150F086C(void *arg0) {
    func_150F0898(arg0);
    func_15149368(arg0);
}

void func_150F0898(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x28);
    *(s32 *)(temp_v0 + 0x134) = 0;
}

void func_150F08A8(void *arg0) {
    func_150F0900(arg0);
    func_151411A4(arg0);
}

void func_150F08D4(void *arg0) {
    func_150F0900(arg0);
    func_151411C4(arg0);
}

void func_150F0900(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x178);
    *(s32 *)(temp_v0 + 0x138) = 0;
}

void func_150F0910(void *arg0) {
    func_150F0968(arg0);
    func_151617C4(arg0);
}

void func_150F093C(void *arg0) {
    func_150F0968(arg0);
    func_151617E4(arg0);
}

void func_150F0968(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x18);
    *(s32 *)(temp_v0 + 0x13C) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F03F8.s")

void func_150F0D64(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x60);
    s32 a;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        ; // fakematch: permuter artifact (empty statement)
        a = *(s32 *)arg1;
        if (a == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = a;
            v[4] = arg1[8];
        }
    }
}

void func_150F0E0C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x170;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
    }
}

s32 func_15160A58(s32, u8, s32 *, u8, s16, s32, s32, s32, s32, s32, s32, s8, s32, u8, u8, s32);
extern s32 D_800A1A44;
extern s32 D_800A1A50;

void func_150F0EB8(s32 arg0) {
    func_15160A58(arg0, 0x25, &D_800A1A44, 2, 0x12C, 4, 0, 0xFF, 0, 0xFF, 0, -1, 0, 0, 0xFF, 1);
    func_15160A58(arg0, 2, &D_800A1A50, 2, 0x12C, 0xD, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

typedef struct { s32 x, y, z; } V3i;
s32 func_151530A8(s32 *, s32, s32, u8 *);

void func_150F0FA4(u8 *arg0) {

    struct {
        s32 u1C;
        s32 u20;
        V3i u24;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        u8 u5E;
        u8 u5F;
        u8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        u8 u65;
        u8 u66;
        u8 u67;
        u8 u68;
        u8 u69;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        u8 u6D;
        u8 u6E;
        u8 u6F;
        u8 u70;
        u8 u71;
        u8 u72;
        u8 u73;
        u8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 9;
    sp.u20 = 6;
    sp.u24 = *(V3i *) arg0;
    sp.u30 = 14.88f;
    sp.u34 = 14.88f;
    sp.u38 = -1.353f;
    sp.u3C = 0.71800005f;
    sp.u40 = 39.0f;
    sp.u44 = 35.0f;
    sp.u48 = 0;
    sp.u4A = 0xFF;
    sp.u4C = -0x1F;
    sp.u4E = 0x50;
    sp.u50 = 3;
    sp.u54 = 4;
    sp.u58 = 0x14;
    sp.u5A = 0x1E;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u61 = 0xFF;
    sp.u62 = 0xFF;
    sp.u63 = 0xFF;
    sp.u64 = 0xFF;
    sp.u65 = 0;
    sp.u66 = 0;
    sp.u67 = 0;
    sp.u68 = 0;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xFF;
    sp.u6C = 0xFF;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u71 = 0xFF;
    sp.u72 = 0;
    sp.u73 = 3;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 8;
    sp.u82 = 0x1F;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u88 = 1.0f;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    func_151530A8(&sp.u1C, 0xFF, 1, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0BEC.s")

s32 func_150F13C8(u8 *arg0, s32 arg1)
{
  u8 *temp_s0;
  s32 pad;
  u8 *temp_v0;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0xA8));
  if ((*((u8 *) (((u8 *) arg0) + 0xAC))) != (*((u8 *) (((u8 *) temp_v0) + 0x3B))))
  {
    return 0;
  }
  *((f32 *) (((u8 *) arg0) + 0x40)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x14)));
  temp_s0 = arg0 + 0xA8;
  *((f32 *) (((u8 *) arg0) + 0x44)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x18)));
  if (arg0 && arg0)
  {
  }
  *((f32 *) (((u8 *) arg0) + 0x48)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x1C)));
  *((f32 *) (((u8 *) temp_s0) + 8)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 8))) + (0.263f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 0xC)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0xC))) + (0.303f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 0x10)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x10))) + (0.25f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 8)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 8)));
  *((f32 *) (((u8 *) temp_s0) + 0xC)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 0xC)));
  *((f32 *) (((u8 *) temp_s0) + 0x10)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 0x10)));
  *((f32 *) (((u8 *) arg0) + 0x38)) = (f32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 8))) * 243.0f) + 780.0f);
  *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 0xC))) * 243.0f) + 780.0f);
  *((s8 *) (((u8 *) arg0) + 0x2B)) = (s8) ((u32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 0x10))) * 50.0f) + 200.0f));
  return 1;
}

void func_150F15A0(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0xA8;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else {
            if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
                *(s32 *)v = *(s32 *)arg1;
                v[4] = arg1[8];
            }
            goto end; // fakematch: permuter artifact (no-op jump keeps this arm's exit)
end:        ;
        }
    } else {
        if (arg1) { // fakematch: permuter artifact (empty if)
        }
        if (arg2 == 0 || arg2 == 0x43) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}

void func_150F10D4(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = *(f32 *)(arg0 + 0x14);
    tmp.unk10 = *(f32 *)(arg0 + 0x18);
    tmp.unk14 = *(f32 *)(arg0 + 0x1C);
    temp_v0 = func_15149130(300, -1, 0x4C, -1, 0, 0x3A, 0x18, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F16F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1B78.s")

void func_150F1C04(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x18;
    s32 id;
    if (arg2 == 0x43) {
        id = arg1[0];
        if (id == *(s32 *)p || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1C5C.s")
