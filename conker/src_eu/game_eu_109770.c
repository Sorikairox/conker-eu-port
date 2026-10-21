#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DBF60.s")

#ifdef NON_MATCHING
void func_151534E0(u8 *arg0, s32 arg1);

void func_150DC1E0(u8 *arg0) {
    struct {
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        s16 u3C;
        s16 u3E;
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s8 u50;
        s8 u51;
        u8 pad52[0x2];
        s32 u54;
        s32 u58;
        s32 u5C;
        s32 u60;
        s32 u64;
        s32 u68;
        s8 u6C;
        s8 u6D;
    } sp;

    sp.u18 = 177.90175f;
    sp.u3C = 1;
    sp.u3E = 2;
    sp.u40 = -0x4B;
    sp.u44 = -0x26;
    sp.u42 = 0x16;
    sp.u46 = 0x23;
    sp.u48 = 3;
    sp.u4A = 2;
    sp.u4C = 0x29;
    sp.u4E = 0;
    sp.u24 = 2.0f;
    sp.u28 = 2.0f;
    sp.u50 = 0xA;
    sp.u51 = 0x28;
    sp.u54 = 1;
    sp.u58 = 0;
    sp.u5C = 0;
    sp.u60 = 0;
    sp.u64 = 0;
    sp.u68 = 0;
    sp.u6C = 0xFF;
    sp.u6D = 0xFF;
    sp.u1C = -13.388248f;
    sp.u20 = -1708.0238f;
    sp.u34 = 7.0f;
    sp.u38 = 5.0f;
    sp.u2C = 0.32f;
    sp.u30 = 0.0f;
    func_151534E0((u8 *) &sp.u18, (*(u8 *)((u8 *)arg0 + 0xC)));   /* the callee never reads a2 */
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DC1E0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DC2F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DCAD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DD420.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DDBC0.s")

void func_150DE450(u8 *arg0) {
    struct260 *o;
    o = func_151491F4(0x64, 2, -1, 1U, 0U, 1, 0xFFU, 0);
    if (o != NULL) {
        switch (arg0[0x72]) {
        case 0xFB: *((s8 *)o + 0x28) = 1; break;
        case 0xFC: *((s8 *)o + 0x28) = 2; break;
        case 0xFD: *((s8 *)o + 0x28) = 4; break;
        case 0xFE: *((s8 *)o + 0x28) = 3; break;
        default: func_1516972C((struct102 *) o); break;
        }
    }
}

void func_150DE508(struct102 *arg0) {
    func_150DC2F0(arg0->unk28, arg0);
}

s32 func_150DE52C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {

    u8 *sp8C;
    struct {
        s32 u60;
        s16 u64;
        s8 u66;
        u8 pad67[0x1];
        s32 u68;
        s32 u6C;
        u8 u70;
        u8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 u75;
        u8 pad76[0x2];
        s32 u78;
        u8 pad7C[0xC];
        s32 u88;
    } sp;
    f32 size;
    s32 pad58; // fakematch: unused slot keeps size reload in f0
    s32 r54;
    s32 r50;

    sp8C = (*(u8 **)((u8 *)arg0 + 0x98));
    sp.u88 = (*(s32 *)((u8 *)arg0 + 0x94));
    size = (func_150ADA68() * 70.0f) + 10.0f;
    (*(s8 *)((u8 *)sp8C + 0x20)) = 4;
    switch (func_150ADA20() & 1) {
    case 0:
        sp.u66 = 0x1D;
        break;
    case 1:
        sp.u66 = 0x1E;
        break;
    }
    sp.u68 = 0;
    sp.u6C = 0;
    sp.u60 = 0x11;
    sp.u64 = 0x64;
    sp.u70 = 0xFF;
    sp.u71 = 0xFF;
    sp.u72 = 0;
    sp.u73 = 0;
    sp.u74 = 0;
    sp.u75 = 0xFF;
    sp.u78 = 0x30002;
    r50 = func_150ADA20();
    r54 = func_150ADA20();
    func_1513C73C((s32) &sp.u60, 5U, 0U, arg5, ((f32 (*)[5])sp.u88)[*(s8 *)(arg0 + 0x2D)][0], arg4, ((f32 (*)[5])sp.u88)[*(s8 *)(arg0 + 0x2D)][2], size, size, (u8) (r50 & 0xFF), (u8) ((func_150ADA20() & 1) + (r54 & 1)), 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    return 1;
}

s32 func_150DE6AC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {

    u8 *sp8C;
    struct {
        s32 u60;
        s16 u64;
        s8 u66;
        u8 pad67[0x1];
        s32 u68;
        s32 u6C;
        u8 u70;
        u8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 u75;
        u8 pad76[0x2];
        s32 u78;
        u8 pad7C[0xC];
        s32 u88;
    } sp;
    f32 size;
    s32 pad58; // fakematch: unused slot keeps size reload in f0
    s32 r54;
    s32 r50;

    sp8C = (*(u8 **)((u8 *)arg0 + 0x98));
    sp.u88 = (*(s32 *)((u8 *)arg0 + 0x94));
    size = (func_150ADA68() * 10.0f) + 10.0f;
    (*(s8 *)((u8 *)sp8C + 0x20)) = 4;
    switch (func_150ADA20() & 1) {
    case 0:
        sp.u66 = 0x1B;
        break;
    case 1:
        sp.u66 = 0x1C;
        break;
    }
    sp.u68 = 0;
    sp.u6C = 0;
    sp.u60 = 0x11;
    sp.u64 = 0x64;
    sp.u70 = 0xFF;
    sp.u71 = 0xFF;
    sp.u72 = 0;
    sp.u73 = 0;
    sp.u74 = 0;
    sp.u75 = 0xAA;
    sp.u78 = 0x30002;
    r50 = func_150ADA20();
    r54 = func_150ADA20();
    func_1513C73C((s32) &sp.u60, 5U, 0U, arg5, ((f32 (*)[5])sp.u88)[*(s8 *)(arg0 + 0x2D)][0], arg4, ((f32 (*)[5])sp.u88)[*(s8 *)(arg0 + 0x2D)][2], size, size, (u8) (r50 & 0xFF), (u8) ((func_150ADA20() & 1) + (r54 & 1)), 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    return 1;
}

s32 func_150DE824(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        arg0->unk28 = temp_v0 * 8;
    }
    return 1;
}

void func_150DE844(s16 *arg0) {
    arg0[0x34 / 2] -= 0x1A;
    arg0[0x36 / 2] -= 0x1A;
    if ((arg0[0x34 / 2] < 10) || (arg0[0x36 / 2] < 10)) {
        arg0[0x38 / 2] = 0;
    }
}
