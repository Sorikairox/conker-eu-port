#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_800CC76A;

u8 *func_150B5DD0(u8 *arg0, s32 arg1) {
    if (D_800C35EA == 1) {
        return arg0;
    }
    (*(s16 *)arg0) = 0x1A;
    (*(u16 *)((u8 *)arg0 + 2)) = *(u16 *)((u8 *)&D_800CC76A + (arg1 * 0x32C));
    return arg0 + 4;
}
void func_150B5F1C(f32 *, u8, s32);
void func_150B60E0(u8 *, u8 *);
void func_150B5E30(u8 *arg0) {
    s32 pad; // fakematch: frame/spill slot padding
    f32 sp28[3];
    u8 *a3;
    a3 = *(u8 **)(arg0 + 0x28);
    if (*(s32 *)a3 == 0 || arg0[0x2C] != a3[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(a3 + 0x1D4) != 0) {
        if (func_150ADA68() < 0.10824f) {
            sp28[0] = *(f32 *)(a3 + 0x14);
            sp28[1] = *(f32 *)(a3 + 0x18);
            sp28[2] = *(f32 *)(a3 + 0x1C);
            func_150B5F1C(sp28, arg0[0xC], arg0[1]);
        }
        if (func_150ADA68() < 0.10824f) {
            func_150B60E0(a3, (u8 *)sp28);
            func_150B5F1C(sp28, arg0[0xC], arg0[1]);
        }
    }
}

#ifdef NON_MATCHING
void func_150B64E0(u8 *arg0, u8 arg1, s32 arg2);
s32 func_150B6314(u8 *, u8, s32);
s32 func_151530A8(s32 *, u8, s32);

// smoke_puff_spawn: like func_150B5C38 with other numbers: spawns particle record kind 5 / 5 at `pos`
// (func_151530A8: 20, 10.08, -1.353, 0.731, 39, 35, life -31 / 80, colours 255 / 0, ...) and then the two follow-up
// emitters func_150B6314 / func_150B64E0 at the same point.
void func_150B5F1C(f32 *pos, u8 arg1, s32 arg2) {
    struct {
        s32 kind;
        s32 sub;
        f32 pos[3];
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
        s8 u5E;
        s8 u5F;
        s8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        u8 u69;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        u8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
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
    } rec;

    rec.kind = 5;
    rec.sub = 5;
    rec.pos[0] = pos[0];
    rec.pos[1] = pos[1];
    rec.pos[2] = pos[2];
    rec.u30 = 20.0f;
    rec.u34 = 10.08f;
    rec.u38 = -1.353f;
    rec.u3C = 0.731f;
    rec.u40 = 39.0f;
    rec.u44 = 35.0f;
    rec.u48 = 0;
    rec.u4A = 0xFF;
    rec.u4C = -0x1F;
    rec.u4E = 0x50;
    rec.u50 = 3;
    rec.u54 = 2;
    rec.u58 = 0x14;
    rec.u5A = 0x1E;
    rec.u5C = 1;
    rec.u5E = 4;
    rec.u5F = 2;
    rec.u60 = 3;
    rec.u61 = 0xFF;
    rec.u62 = 0xFF;
    rec.u63 = 0xFF;
    rec.u64 = 0xFF;
    rec.u65 = 0;
    rec.u66 = 0;
    rec.u67 = 0;
    rec.u68 = 0;
    rec.u69 = 0xFF;
    rec.u6A = 0xFF;
    rec.u6B = 0xFF;
    rec.u6C = 0xFF;
    rec.u6D = 0;
    rec.u6E = 0;
    rec.u6F = 0;
    rec.u70 = 0;
    rec.u71 = 0xFF;
    rec.u72 = 0;
    rec.u73 = 3;
    rec.u74 = 0x24;
    rec.u78 = 0x200005;
    rec.u7C = 0x60600;
    rec.u80 = 8;
    rec.u82 = 0x1F;
    rec.u84 = 1;
    rec.u86 = 0;
    rec.u88 = 1.0f;
    rec.u8C = -1;
    rec.u8D = 0;
    rec.u8E = -1;
    rec.u8F = -1;
    func_151530A8(&rec.kind, arg1, arg2);
    func_150B6314((u8 *)pos, arg1, arg2);
    func_150B64E0((u8 *)pos, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B5F1C.s")
#endif

typedef struct { s32 x, y, z; } V3i;
void func_150B64E0(u8 *arg0, u8 arg1, s32 arg2);
s32 func_150B6314(u8 *, u8, s32);
s32 func_151530A8(s32 *, u8, s32);

void func_150B5C38(u8 *arg0, u8 arg1, s32 arg2) {

    struct {
        s32 u1C;
        s32 u20;
        s32 u24;
        u8 pad28[0x8];
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
        s8 u5E;
        s8 u5F;
        s8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        u8 u69;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        u8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
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

    sp.u1C = 0xD;
    sp.u20 = 8;
    *(V3i *) &sp.u24 = *(V3i *) arg0;
    sp.u30 = 15.88f;
    sp.u34 = 36.1f;
    sp.u38 = -3.6030002f;
    sp.u3C = 2.1660001f;
    sp.u40 = 152.0f;
    sp.u44 = 100.0f;
    sp.u48 = 0;
    sp.u4A = 0xFF;
    sp.u4C = -0x14;
    sp.u4E = 0x32;
    sp.u50 = 3;
    sp.u54 = 2;
    sp.u58 = 0x14;
    sp.u5A = 0xF;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u61 = 0xFF;
    sp.u62 = 0xFF;
    sp.u63 = 0xB4;
    sp.u64 = 0xFF;
    sp.u65 = 0;
    sp.u66 = 0;
    sp.u67 = 0;
    sp.u68 = 0;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xB4;
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
    func_151530A8(&sp.u1C, arg1, arg2);
    func_150B6314(arg0, arg1, arg2);
    func_150B64E0(arg0, arg1, arg2);
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

s32 func_150B6314(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u28;
        s32 u2C;
        s16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        s8 u3C;
        s8 u3D;
        s8 u3E;
        s8 u3F;
        s8 u40;
        s8 u41;
        s8 u42;
        s8 u43;
        s8 u44;
        s8 u45;
        s16 u46;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
        s32 u58;
        u8 pad5C[0x8];
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s32 u80;
        u8 pad84[0x4];
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
    } sp;
    s32 sp20;
    f32 temp_f6;
    s32 var_v0;
    s32 var_v1;

    sp.u45 = 0x2B;
    sp.u30 = 0x4403;
    sp.u28 = 0x200005;
    sp.u2C = 0x20000;
    sp.u32 = (func_150ADA20() % 7U) + 4;
    sp.u34 = 0;
    sp.u38 = 0;
    sp.u3C = 0xFF;
    sp.u3D = 0xFF;
    sp.u3E = 0xFF;
    sp.u3F = 0xFF;
    sp.u40 = 0xFF;
    sp.u41 = 0xFF;
    sp.u42 = 0xFF;
    sp.u43 = 0xFF;
    sp.u44 = 0xFF;
    temp_f6 = (func_150ADA68() * 500.0f) + 500.0f;
    sp.u54 = temp_f6;
    sp.u50 = temp_f6;
    (*(s32 *)((u8 *)(&sp.u58) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u58) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u58) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u46 = 3;
    sp.u48 = 0x55;
    sp.u4A = 1;
    sp.u64 = 0.0f;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    sp.u4C = 1.0f;
    var_v1 = 0;
    if (func_150ADA20() & 1) {
        var_v1 = 0x40;
    }
    sp20 = var_v1;
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    sp.u80 = var_v0 | 1 | var_v1 | 0xC200;
    sp.u88 = 6;
    sp.u89 = 6;
    sp.u8A = -1;
    sp.u8B = -1;
    sp.u8C = -1;
    sp.u8D = 4;
    return func_151307F0(&sp.u28, 1, 0, 0, (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B6314.s")
#endif
void func_150B64E0(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 9U) + 3;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg1, arg2);
}

void func_150B60E0(u8 *arg0, u8 *arg1) {
    func_15143134(D_800A0000, arg1, (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x140);
}

#ifdef NON_MATCHING
s32 func_15107518(f32 *, f32 *, s32, f32 *, f32, s32, s32, s32);
void func_1514373C(f32, f32, f32 *, f32 *);

void func_150B65F0(u8 *arg0) {
    struct {
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        s16 uA0;
        s16 uA2;
        s16 uA4;
        s16 uA6;
        s16 uA8;
        u8 padAA[0x2];
        s32 uAC;
        s32 uB0;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
    } sp;
    f32 var_f12;
    s32 temp_t1;
    s32 temp_v0_2;
    u8 temp_t6;
    u8 temp_v0;
    u8 *temp_s1;
    u8 *temp_s2;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_v0 = (*(u8 *)((u8 *)arg0 + 0x30));
    temp_t6 = (*(u8 *)((u8 *)temp_s1 + 0x14));
    (*(u8 *)((u8 *)arg0 + 0x30)) = temp_t6;
    if ((*(u8 *)((u8 *)temp_s1 + 0x14)) == 1) {
        if (temp_v0 != (temp_t6 & 0xFF)) {
            func_151494E0(0, 0x4AU);
        }
    } else {
        temp_s2 = arg0 + 0x28;
        (*(f32 *)((u8 *)temp_s2 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 4)) + ((0.15f + (func_150ADA68() * 0.155f)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s2 + 4)) > 1.0f) {
            sp.uA0 = 0x28;
            sp.u8C = 35.0f;
            sp.u90 = 35.0f;
            sp.uA2 = 0;
            sp.uA4 = 4;
            sp.uA6 = 3;
            sp.uA8 = 7;
            sp.uAC = 4;
            sp.uB0 = 3;
            sp.uB4 = 0x7E;
            sp.uB5 = 0xF9;
            sp.uB6 = 0xFF;
            sp.uB7 = 0x7F;
            sp.uB8 = 0x80;
            sp.u94 = 76.0f;
            sp.u98 = 103.0f;
            sp.u9C = 281.0f;
            sp.u84 = (f32) ((*(s16 *)((u8 *)temp_s1 + 2)) + (*(s16 *)((u8 *)temp_s1 + 8)));
            sp.u78 = (f32) ((*(s16 *)((u8 *)temp_s1 + 2)) + (*(s16 *)((u8 *)temp_s1 + 8)));
            do {
                temp_v0_2 = func_150ADA20();
                func_1514373C((f32) (temp_v0_2 & 0xFF), (f32) (*(s16 *)((u8 *)temp_s1 + 6)), &sp.u80, &sp.u88);
                sp.u80 += (f32) (*(s16 *)((u8 *)temp_s1 + 0));
                sp.u88 += (f32) (*(s16 *)((u8 *)temp_s1 + 4));
                temp_t1 = ((temp_v0_2 & 0xFF) + (func_150ADA20() % 129U) + 0x40) & 0xFF;
                var_f12 = (f32) temp_t1;
                if (temp_t1 < 0) {
                    var_f12 += 4294967296.0f;
                }
                func_1514373C(var_f12, (f32) (*(s16 *)((u8 *)temp_s1 + 6)), &sp.u74, &sp.u7C);
                sp.u74 += (f32) (*(s16 *)((u8 *)temp_s1 + 0));
                sp.u7C += (f32) (*(s16 *)((u8 *)temp_s1 + 4));
                func_15107518(&sp.u80, &sp.u74, 4, &sp.u8C, 0.43500003f, 1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s2 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 4)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s2 + 4)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B65F0.s")
#endif
void func_150B6930(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4A) {
        func_1516972C(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E35E0/func_150B696C.s")

s32 func_150B6BBC(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x18);
    s32 ret = 1;

    switch (p[0x68] - 15) {
    case 0:
        (*(u8 **)(arg0 + 0x14))[9] = 1;
        break;
    case 1:
        (*(u8 **)(arg0 + 0x14))[9] = 0;
        (*(u8 **)(arg0 + 0x14))[0x2F] = 0x14;
        break;
    default:
    case 2:
        (*(u8 **)(arg0 + 0x14))[9] = 0;
        (*(u8 **)(arg0 + 0x14))[0x2F] = 0x28;
        break;
    }
    return ret;
}

s32 func_15182BE0(u8, u8, u8, s32, s16, u8, u8, s32);

void func_150B6C34(u8 arg0, s32 arg1) {
    s32 pad;
    u32 sp28;

    sp28 = func_150ADA20();
    func_15182BE0(0xCC, 0xCC, 0xFF, ((sp28 % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 11U) + 0xF, 0, (s32) arg0, arg1);
}
