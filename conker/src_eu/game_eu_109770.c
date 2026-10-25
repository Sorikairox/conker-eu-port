#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_151534E0(u8 *arg0, s32 arg1);
void func_15153808(u8 *arg0, s32 arg1, s32 arg2);
u8 *func_15196438(u8 *, s32, u8, s32);
extern u8 D_800908C4[];

// spark_effect_on_event: event effect for obj. mode 0: starts emitter kind 1 on obj (func_15196438), a spark burst
// (func_151534E0 spec at x 177.9 / z -1708), sound effect 0x1E (func_151491F4) and a sprite burst (func_15153808 spec,
// D_800908C4 animation); mode 1: emitter kind 2 only; other modes and a NULL obj do nothing. flag goes to every call.
void func_150DBF60(u8 *obj, s32 mode, u8 flag) {
    struct {
        f32 x, y, z;            // 0x00
        f32 u0C, u10;           // 0x0C
        f32 u14, u18;           // 0x14
        f32 u1C, u20;           // 0x1C
        s16 u24, u26, u28, u2A, u2C, u2E, u30, u32, u34, u36; // 0x24
        s8 u38, u39;            // 0x38
        s32 u3C, u40, u44, u48, u4C, u50; // 0x3C
        s8 u54, u55;            // 0x54
    } spark;                    // sp78
    struct {
        f32 x, y, z;            // 0x00
        s16 u0C, u0E, u10, u12, u14, u16; // 0x0C
        f32 u18, u1C;           // 0x18
        s16 u20, u22, u24, u26; // 0x20
        s8 u28;                 // 0x28
        u8 u29;                 // 0x29
        s16 u2A, u2C, u2E, u30, u32, u34, u36; // 0x2A
        u8 *anim;               // 0x38
        u8 u3C, u3D;            // 0x3C
    } burst;                    // sp38

    if (obj == NULL) {
        return;
    }
    if (mode == 0) {
        func_15196438(obj, 1, flag, 0);
        spark.x = 177.901749f;
        spark.y = -13.3882484f;
        spark.z = -1708.0238f;
        spark.u0C = 3.0f;
        spark.u10 = 3.0f;
        spark.u14 = 0.319999993f;
        spark.u18 = 0.0f;
        spark.u1C = 9.0f;
        spark.u20 = 8.0f;
        spark.u24 = 8;
        spark.u26 = 8;
        spark.u28 = -0x4B;
        spark.u2A = 0x16;
        spark.u2C = -0x26;
        spark.u2E = 0x23;
        spark.u30 = 3;
        spark.u32 = 2;
        spark.u34 = 0x29;
        spark.u36 = 0;
        spark.u38 = 0xA;
        spark.u39 = 0x28;
        spark.u3C = 1;
        spark.u40 = 0;
        spark.u44 = 0;
        spark.u48 = 0;
        spark.u4C = 0;
        spark.u50 = 0;
        spark.u54 = 0xFF;
        spark.u55 = 0xFF;
        func_151534E0((u8 *) &spark, flag);
        func_151491F4(0x1E, -1, 0, 1, 0, 0, flag, 0);
        burst.x = 177.901749f;
        burst.y = -13.3882484f;
        burst.z = -1708.0238f;
        burst.u0C = 6;
        burst.u0E = 3;
        burst.u10 = -0x4A;
        burst.u12 = 0x15;
        burst.u14 = -0x26;
        burst.u16 = 0x23;
        burst.u18 = 1285.0f;
        burst.u1C = 1149.0f;
        burst.u20 = 0xE;
        burst.u22 = 0xE;
        burst.u24 = -0x3D;
        burst.u26 = 0x1C;
        burst.u28 = -1;
        burst.u29 = 0x12;
        burst.u2A = 6;
        burst.u2C = 6;
        burst.u2E = 0;
        burst.u30 = 0xAE;
        burst.u32 = 0x73;
        burst.u34 = 0x73;
        burst.u36 = 0x87;
        burst.anim = D_800908C4;
        burst.u3C = 0xFF;
        burst.u3D = 0xFF;
        func_15153808((u8 *) &burst, flag, 1);
    } else if (mode == 1) {
        func_15196438(obj, 2, flag, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DBF60.s")
#endif

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
#ifdef NON_MATCHING
extern f32 D_800A1028, D_800A102C, D_800A1030, D_800A1034, D_800A1038, D_800A103C, D_800A1040, D_800A1044, D_800A1048,
    D_800A104C, D_800A1050, D_800A1054, D_800A1058, D_800A105C, D_800A1060, D_800A1064, D_800A1068, D_800A106C,
    D_800A1070, D_800A1074, D_800A1078, D_800A107C, D_800A1080, D_800A1084, D_800A1088, D_800A108C, D_800A1090,
    D_800A1094, D_800A1098, D_800A109C, D_800A10A0, D_800A10A4, D_800A10A8, D_800A10AC, D_800A10B0, D_800A10B4,
    D_800A10B8, D_800A10BC;
extern u8 D_80090778[], D_800907C4[];
struct127 *func_15083E90(u8 arg0);

// item_effect_spawn: starts the effect record of preset `kind` (func_15147FF0: kind 0x120, 300 frames... spec below)
// and fills its 0x11C-byte data (rec + 0x98). Presets 0 / 5 use the D_80090778 animation and positions of their own;
// presets 1..4 the D_800907C4 one, placed by the object func_15083E90(6) (y 736; z depends on kind, the x / z pair
// and +0x24 on whether that object's +0x84 is 6). Returns the record, NULL for an unknown preset, a missing
// object or a full pool. arg1 is unused (func_150DE508 passes its record).
u8 *func_150DC2F0(u8 kind, s32 arg1) {
    struct {
        f32 u00; u8 u04; s16 u06; f32 u08; u8 u0C; s16 u0E;
        f32 pos[2];             // 0x10: x / z of the spec
        f32 u18; f32 u1C; f32 u20; f32 u24;
        u8 u28; u8 u29; f32 u2C; f32 u30; u8 u34; s16 u36; f32 u38; u8 u3C; s16 u3E;
        u8 u40; u8 u41; u8 u42; s32 u44; s32 u48; s32 u4C; s32 u50; s32 u54; s32 u58; s32 u5C;
        u8 u60; f32 u64; f32 u68; f32 u6C; s16 u70; s16 u72; f32 u74; f32 u78; s16 u7C; s16 u7E; f32 u80;
        s16 u84; s16 u86; s16 u88; f32 u8C; u8 *anim; s32 u94; s8 u98; f32 u9C; f32 uA0; f32 uA4; s16 uA8; s16 uAA;
        f32 uAC; f32 uB0; f32 uB4; f32 uB8; f32 uBC; f32 uC0; s16 uC4; s16 uC6; s16 uC8; u8 uCA; f32 uCC; f32 uD0;
        f32 uD4; s16 uD8; s16 uDA; f32 uDC; f32 uE0; s16 uE4; s16 uE6; s16 uE8; s16 uEA; s16 uEC; s16 uEE; f32 uF0;
        u8 *anim2; s32 uF8; s8 uFC; f32 u100; f32 u104; f32 u108; f32 u10C; f32 u110; s16 u114; s16 u116; s16 u118;
    } d;                        // sp48
    struct {
        f32 x, y, z;            // 0x00
        s16 u0C;                // 0x0C
        u16 flags;              // 0x0E
        s32 u10;                // 0x10
        u8 pad14;
        u8 u15;                 // 0x15
    } spec;                     // sp164
    struct127 *obj;
    u8 *rec;

    d.u20 = 0.0f;
    d.u40 = 0;
    spec.flags = 0;
    d.u34 = 0;
    switch (kind) {
    case 0:
    case 5:
        if (kind == 0) {
            spec.x = 5.0f;
            spec.y = 115.0f;
            spec.z = D_800A1028;
            d.u24 = D_800A102C;
        } else {
            spec.x = D_800A1030;
            spec.y = D_800A1034;
            spec.z = D_800A1038;
            d.u24 = 90.0f;
        }
        d.pos[0] = spec.x;
        d.pos[1] = spec.z;
        d.u18 = D_800A103C;
        d.u1C = D_800A1040;
        d.u2C = 14.0f;
        d.u30 = 4.0f;
        d.u08 = D_800A1044;
        d.u6C = D_800A1048;
        d.u74 = 40.0f;
        d.u80 = -185.0f;
        d.u8C = D_800A104C;
        d.u9C = D_800A1050;
        d.uAC = D_800A1054;
        d.uB0 = D_800A1058;
        d.uB4 = 5.0f;
        d.uBC = D_800A105C;
        d.uC0 = D_800A1060;
        d.uCC = D_800A1064;
        d.uD4 = D_800A1068;
        d.uDC = 270.0f;
        d.uE0 = 154.0f;
        d.uF0 = 173.0f;
        d.u100 = 60.0f;
        spec.u15 = 0x19;
        spec.u0C = 0x85;
        d.u118 = 0x78;
        d.u28 = 0xFF;
        d.u29 = 0xFF;
        d.u36 = 0xC;
        d.u3C = 2;
        d.u3E = 2;
        d.u06 = 0xA;
        d.u0E = 5;
        spec.flags = 1;
        d.u41 = 0x18;
        d.u42 = 0x51;
        d.u44 = 8;
        d.u58 = 5;
        d.u60 = 1;
        d.u70 = 0x3F;
        d.u7C = 0x38;
        d.u7E = -0x80;
        d.u84 = 8;
        d.u86 = 0xA;
        d.u88 = 0x181;
        d.u98 = -1;
        d.uA8 = -0x3F;
        d.uAA = 0x2B;
        d.uC4 = 0x56;
        d.uC6 = 3;
        d.uC8 = 3;
        d.uCA = 0xC;
        d.uD8 = -0x3E;
        d.uDA = 7;
        d.uE4 = 0x38;
        d.uE6 = -0x39;
        d.uE8 = 0x15;
        d.uEA = 7;
        d.uEC = 3;
        d.uEE = 0x135;
        d.u38 = 0.0f;
        d.u04 = 0;
        d.u0C = 0;
        d.u48 = 0;
        d.u4C = 0;
        d.u50 = 0;
        d.u54 = 0;
        d.u5C = 0;
        d.u64 = 0.0f;
        d.u68 = 0.0f;
        d.u72 = 0;
        d.anim = D_80090778;
        d.u94 = 0;
        d.uA0 = 0.0f;
        d.uD0 = 0.0f;
        d.anim2 = D_80090778;
        d.uF8 = 0;
        d.uFC = -1;
        d.u104 = 0.0f;
        d.u108 = 0.0f;
        d.u00 = 6.0f;
        d.uB8 = 6.0f;
        d.u10C = 100.0f;
        d.u110 = 100.0f;
        d.u78 = 25.0f;
        d.uA4 = 25.0f;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        obj = func_15083E90(6);
        if (obj == NULL) {
            return NULL;
        }
        d.u24 = (*(u16 *) ((u8 *) obj + 0x84) == 6) ? 498.0f : -37.0f;
        spec.y = 736.0f;
        if (kind == 1) {
            spec.x = D_800A106C;
            spec.z = D_800A1070;
        } else if (kind == 2) {
            spec.x = D_800A1074;
            spec.z = D_800A1074;
        } else if (kind == 3) {
            spec.z = D_800A1078;
            spec.x = D_800A107C;
        } else {
            spec.x = D_800A1080;
            spec.z = D_800A1080;
        }
        d.pos[0] = spec.x;
        d.pos[1] = spec.z;
        d.u18 = -2.0f;
        d.u1C = D_800A1084;
        d.u2C = 132.0f;
        d.u30 = D_800A1088;
        d.u38 = D_800A108C;
        d.u64 = D_800A1090;
        d.u6C = D_800A1094;
        d.u74 = D_800A1098;
        d.u78 = D_800A109C;
        d.u80 = -51.0f;
        d.u9C = D_800A10A0;
        d.uA4 = D_800A10A4;
        d.uAC = D_800A10A8;
        d.uB4 = 15.0f;
        d.uB8 = 12.0f;
        d.uBC = 2.75f;
        spec.u15 = 0x1E;
        d.uC0 = D_800A10AC;
        spec.u0C = 0xA0;
        d.uCC = D_800A10B0;
        d.uD4 = 131.0f;
        d.uDC = D_800A10B4;
        d.uE0 = D_800A10B8;
        d.u118 = 0x6E;
        d.u28 = 0xFF;
        d.u29 = 0xFF;
        d.u36 = 0xC;
        d.u3C = 1;
        d.u3E = 3;
        d.u06 = 6;
        d.u0E = 6;
        spec.flags |= 1;
        d.u100 = 3.0f;
        d.u41 = 0x19;
        d.u42 = 0x51;
        d.u44 = 8;
        d.u4C = 6;
        d.u60 = 2;
        d.u70 = 0x24;
        d.u72 = 0x1A;
        d.u7C = 0x258;
        d.u7E = -0x48;
        d.u84 = 6;
        d.u104 = D_800A10BC;
        d.u86 = 3;
        d.u88 = 0x514;
        d.u94 = 0xAB;
        d.u98 = 0xC;
        d.uA8 = -0x3A;
        d.uAA = 0xB;
        d.uC4 = 0x46;
        d.uC6 = 4;
        d.uC8 = 2;
        d.uCA = 9;
        d.u04 = 0;
        d.u0C = 0;
        d.u48 = 0;
        d.u50 = 0;
        d.u54 = 0;
        d.u58 = 0;
        d.u5C = 0;
        d.u68 = 0.0f;
        d.anim = D_800907C4;
        d.uA0 = 0.0f;
        d.uD0 = 0.0f;
        d.uD8 = -0x38;
        d.uDA = 0xA;
        d.uE4 = 0x258;
        d.uE6 = -0xDF;
        d.uE8 = 0x40;
        d.uEA = 6;
        d.uEC = 4;
        d.uEE = 0x514;
        d.anim2 = D_800907C4;
        d.uF8 = 0xAB;
        d.uFC = 0xC;
        d.u108 = 0.0f;
        d.u00 = 22.0f;
        d.u08 = 22.0f;
        d.u10C = 100.0f;
        d.u110 = 100.0f;
        d.u8C = 500.0f;
        d.uF0 = 500.0f;
        d.uB0 = 25.0f;
        break;
    default:
        return NULL;
    }
    spec.u10 = 5;
    d.u116 = 0x1B8;
    rec = func_15147FF0(&spec, 0x120, 0x18, 4, 4, 4, 0, 0, 0, 0xFF, 1);
    if (rec != NULL) {
        memcpy(*(u8 **) (rec + 0x98), &d, 0x11C);
    }
    return rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DC2F0.s")
#endif

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
