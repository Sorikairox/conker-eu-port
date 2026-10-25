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

#ifdef NON_MATCHING
/* Shared by func_150DCAD8 / func_150DD420 / func_150DDBC0 (the fountain effect of func_150DC2F0). */
/* The 0x11C-byte effect data of func_150DC2F0 (obj +0x98); same layout as its local `d`. */
typedef struct {
    f32 u00; u8 u04; s16 u06; f32 u08; u8 u0C; s16 u0E;
    f32 pos[2];             /* 0x10: emitter x / z */
    f32 u18; f32 u1C; f32 u20; f32 u24;
    u8 u28; u8 u29; f32 u2C; f32 u30; u8 u34; s16 u36; f32 u38; u8 u3C; s16 u3E;
    u8 u40; u8 u41; u8 u42; s32 u44; s32 u48; s32 u4C; s32 u50; s32 u54; s32 u58; s32 u5C;
    u8 u60; f32 u64; f32 u68; f32 u6C; s16 u70; s16 u72; f32 u74; f32 u78; s16 u7C; s16 u7E; f32 u80;
    s16 u84; s16 u86; s16 u88; f32 u8C; u8 *anim; s32 u94; s8 u98; f32 u9C; f32 uA0; f32 uA4; s16 uA8; s16 uAA;
    f32 uAC; f32 uB0; f32 uB4; f32 uB8; f32 uBC; f32 uC0; s16 uC4; s16 uC6; s16 uC8; u8 uCA; f32 uCC; f32 uD0;
    f32 uD4; s16 uD8; s16 uDA; f32 uDC; f32 uE0; s16 uE4; s16 uE6; s16 uE8; s16 uEA; s16 uEC; s16 uEE; f32 uF0;
    u8 *anim2; s32 uF8; s8 uFC; f32 u100; f32 u104; f32 u108; f32 u10C; f32 u110; u8 u114; s16 u116; s16 u118;
} FountainFx;
/* Particle record for func_15167D84 (0x38 bytes; fields the fountain code never sets stay as they are). */
typedef struct {
    u8 *tex;                /* 0x00 */
    u8 pad04[8];
    s16 u0C, u0E;           /* 0x0C */
    s16 x, y, z;            /* 0x10 position */
    s16 vx, vz;             /* 0x16 velocity x / z */
    u8 pad1A[2];
    u8 u1C, u1D, u1E, u1F;  /* 0x1C */
    s16 vy;                 /* 0x20 velocity y */
    s16 gravity;            /* 0x22 */
    s16 size0, size1;       /* 0x24 */
    s16 u28;                /* 0x28 */
    u8 u2A;                 /* 0x2A */
    u8 pad2B;
    u8 r, g, b, a;          /* 0x2C colour */
    u8 u30, u31, u32;       /* 0x30 */
    u8 pad33;
    s16 u34;                /* 0x34 */
    u8 pad36[2];
} FountainDrop;
void *func_15167D84(void *, s32, s32, s8, u8, s32);
#endif

#ifdef NON_MATCHING
/* Splash ring record for func_1513C5B0 (fields not set stay as they are). */
typedef struct {
    s32 u00;                /* 0x00 1 */
    s16 u04;                /* 0x04 0x64 */
    u8 u06;                 /* 0x06 0x1D / 0x1E */
    u8 pad07;
    s32 u08, u0C;           /* 0x08 */
    u8 r, g, b, u13, u14, a; /* 0x10 */
    u8 pad16[2];
    s32 u18;                /* 0x18 0x30001 */
} FountainSplash;
extern f32 D_800A10C0;
void *func_15167D84(void *, s32, s32, s8, u8, s32);
u8 *func_151DA6F8(f32 *, f32 *, f32, s16, u8, f32, s32, u8, f32, f32, u8, u8, s32, s16, s16, s32, u8, s32);

// fountain_step: step handler 4 of D_8008A5A0 (`s32 (u8 *)`, func_15147FF0's per-frame step) for the effect of
// func_150DC2F0. Moves the water points of the ring obj +0x94 (see func_150DD420) from the newest back to the oldest:
// vy (+0xC) gains d +0x18 per second, y follows. A point that drops below the water level d +0x24 lands: it makes
// sprites (func_151DA6F8, counter d +0xA0 / rate +0x9C; half alpha and tint 7 when d +0x41 is 0x18), drops
// (func_15167D84, counter +0xD0 / rate +0xCC) and splash rings (func_1513C5B0, counter +0x108 / rate +0x104) around
// it, and becomes the oldest point (older ones are dropped, y clamped to the level). The oldest four points then fade
// in (alpha 0 / 0x3F / 0x7F / 0xBE). When d +0x116 is a sound id it is replayed (func_10010F30, id + rand % 10)
// whenever the countdown +0x114 runs out. obj +0x54..+0x5C gets the oldest point (0 when the ring is empty).
// Always returns 1.
s32 func_150DCAD8(u8 *obj) {
    FountainFx *d = *(FountainFx **) (obj + 0x98);
    u8 *pts = *(u8 **) (obj + 0x94);
    FountainDrop drop;
    FountainSplash ring;
    f32 vel[3];
    f32 pos[3];
    f32 speed, sinA, cosA, sinB, cosB, r, h, scale, speed2, size;
    s32 i, t, more, r0, r1;
    u8 a, b, alpha, tint, r2;
    u8 *pt;

    i = *(s8 *) (obj + 0x2E);
    if (i != *(s8 *) (obj + 0x2D)) {
        i--;
        for (;;) {
            if (i < 0) {
                i = obj[0x25] - 1;
            }
            pt = pts + i * 0x18;
            *(f32 *) (pt + 0xC) += d->u18 * D_800BE9A4;
            *(f32 *) (pt + 0x4) += *(f32 *) (pt + 0xC) * D_800BE9A4;
            if (*(f32 *) (pt + 0x4) < d->u24) {
                /* landed: sprites */
                d->uA0 += d->u9C;
                while (1.0f < d->uA0) {
                    speed = func_150ADA68() * d->uB0 + d->uAC;
                    a = func_150ADA20();
                    sinA = func_151423D8(a);
                    cosA = func_151423D8(a - 0x40);
                    b = (u32) func_150ADA20() % (d->uAA + 1) + d->uA8;
                    sinB = func_151423D8(b);
                    cosB = func_151423D8(b - 0x40);
                    r = func_150ADA68() * d->uA4;
                    pos[0] = *(f32 *) (pt + 0x0) + r * cosA;
                    pos[1] = d->u24;
                    pos[2] = *(f32 *) (pt + 0x8) + r * sinA;
                    h = speed * sinB;
                    vel[0] = h * cosA;
                    vel[1] = -speed * cosB;
                    vel[2] = h * sinA;
                    scale = func_150ADA68();
                    alpha = (d->u41 == 0x18) ? 0x7D : 0xFF;
                    speed2 = func_150ADA68();
                    t = func_150ADA20();
                    tint = (d->u41 == 0x18) ? 7 : 2;
                    func_151DA6F8(pos, vel, scale * d->uC0 + d->uBC, d->uC4, alpha, speed2 * d->uB8 + d->uB4,
                                  (u32) t % (d->uC8 + 1) + d->uC6, 1, D_800A10C0, D_800A10C0, 1, tint, 0, 0x10, 0xF,
                                  0, obj[0xC], obj[1]);
                    d->uA0 -= 1.0f;
                }
                /* drops */
                d->uD0 += d->uCC;
                if (1.0f < d->uD0) {
                    drop.u1C = 0;
                    drop.u1E = 0;
                    drop.u1D = 0;
                    drop.r = 0xFF;
                    drop.g = 0xFF;
                    drop.b = 0xFF;
                    drop.u30 = 0;
                    drop.u31 = 0;
                    drop.u32 = 0;
                    drop.a = 0xFF;
                    drop.u1F = d->uFC;
                    drop.u34 = 0x12;
                    drop.u0C = 0;
                    more = 1;
                    drop.u0E = d->uF8;
                    drop.tex = d->anim2;
                    drop.y = (s32) d->u24;
                    drop.u28 = d->uE4;
                    do {
                        speed = func_150ADA68() * d->uE0 + d->uDC;
                        a = func_150ADA20();
                        sinA = func_151423D8(a);
                        cosA = func_151423D8(a - 0x40);
                        b = (u32) func_150ADA20() % (d->uDA + 1) + d->uD8;
                        sinB = func_151423D8(b);
                        cosB = func_151423D8(b - 0x40);
                        r = func_150ADA68() * d->uD4;
                        drop.x = (s32) (*(f32 *) (pt + 0x0) + r * cosA);
                        h = speed * sinB;
                        drop.vx = (s32) (h * cosA);
                        drop.z = (s32) (*(f32 *) (pt + 0x8) + r * sinA);
                        drop.vy = (s32) (-speed * cosB);
                        drop.vz = (s32) (h * sinA);
                        drop.gravity = (u32) func_150ADA20() % (d->uE8 + 1) + d->uE6;
                        drop.u2A = (u32) func_150ADA20() % (d->uEC + 1) + d->uEA;
                        drop.size1 = drop.size0 = (s32) (func_150ADA68() * d->uF0 + d->uEE);
                        if (func_15167D84(&drop, 0, 0, -1, obj[0xC], obj[1]) == NULL) {
                            more = 0;
                        }
                        d->uD0 -= 1.0f;
                    } while (1.0f < d->uD0 && more);
                    while (1.0f < d->uD0) {
                        d->uD0 -= 1.0f;
                    }
                }
                /* splash rings */
                d->u108 += d->u104;
                if (1.0f < d->u108) {
                    more = 1;
                    ring.u08 = 0;
                    ring.u0C = 0;
                    ring.u00 = 1;
                    ring.u04 = 0x64;
                    ring.r = 0xFF;
                    ring.g = 0xFF;
                    ring.b = 0;
                    ring.u13 = 0;
                    ring.u14 = 0;
                    ring.a = 0xFF;
                    ring.u18 = 0x30001;
                    do {
                        size = func_150ADA68() * d->u110 + d->u10C;
                        ring.u06 = (func_150ADA20() & 1) ? 0x1E : 0x1D;
                        r2 = func_150ADA20();
                        r1 = func_150ADA20();
                        r0 = func_150ADA20();
                        if (func_1513C5B0((s32) &ring, 0, 5, 0, *(f32 *) (pt + 0x0), d->u100, *(f32 *) (pt + 0x8),
                                          size, size, r2, (r0 & 1) + (r1 & 1), 0, 0xFF, 0) == NULL) {
                            more = 0;
                        }
                        d->u108 -= 1.0f;
                    } while (1.0f < d->u108 && more);
                    while (1.0f < d->u108) {
                        d->u108 -= 1.0f;
                    }
                }
                /* this point becomes the oldest */
                while (i != *(s8 *) (obj + 0x2D)) {
                    (*(s8 *) (obj + 0x2D))++;
                    if (*(s8 *) (obj + 0x2D) == obj[0x25]) {
                        *(s8 *) (obj + 0x2D) = 0;
                    }
                    (*(s8 *) (obj + 0x2C))--;
                }
                *(f32 *) (pts + *(s8 *) (obj + 0x2D) * 0x18 + 0x4) = d->u24;
            }
            if (i == *(s8 *) (obj + 0x2D)) {
                break;
            }
            i--;
        }
    }
    /* the oldest four points fade in */
    i = *(s8 *) (obj + 0x2D);
    *(s16 *) (pts + i * 0x18 + 0x14) = 0;
    i++;
    if (i == obj[0x25]) {
        i = 0;
    }
    pt = pts + i * 0x18;
    *(s16 *) (pt + 0x14) = 0x3F;
    i++;
    pt += 0x18;
    if (i == obj[0x25]) {
        i = 0;
        pt = pts;
    }
    *(s16 *) (pt + 0x14) = 0x7F;
    i++;
    pt += 0x18;
    if (i == obj[0x25]) {
        pt = pts;
    }
    *(s16 *) (pt + 0x14) = 0xBE;
    if (d->u116 != 0) {
        t = d->u114 - D_800BE9E4;
        if (t > 0) {
            d->u114 = t;
        } else {
            func_10010F30((u32) func_150ADA20() % 10 + d->u116, 0x7FFF, 0x40, 0, 0);
            d->u114 = func_150ADA20() & 0xC;
        }
    }
    if (*(s8 *) (obj + 0x2C) > 0) {
        pt = pts + *(s8 *) (obj + 0x2D) * 0x18;
        *(s32 *) (obj + 0x54) = *(s32 *) (pt + 0x0);
        *(s32 *) (obj + 0x58) = *(s32 *) (pt + 0x4);
        *(s32 *) (obj + 0x5C) = *(s32 *) (pt + 0x8);
    } else {
        *(f32 *) (obj + 0x54) = 0.0f;
        *(f32 *) (obj + 0x58) = 0.0f;
        *(f32 *) (obj + 0x5C) = 0.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DCAD8.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800A10C4;
void *func_15167D84(void *, s32, s32, s8, u8, s32);

// fountain_emit: emitter handler 4 of D_8008A5DC (`s32 (u8 *)`, func_15147FF0's per-frame step) for the effect of
// func_150DC2F0. The data d = obj +0x98 swings the emitter around obj +0x10 / +0x18 (angles +0x04 / +0x0C advance
// by a random step per frame, radii +0x00 / +0x08) and moves it there in +0x20 steps (+0x20 grows by rate +0x1C;
// nothing happens until it passes 0.99999). Each step adds a point to the ring obj +0x94 (0x18 bytes: x, y, z, vy,
// width, s16 alpha, byte; newest at obj +0x2E, oldest +0x2D, count +0x2C, ring size +0x25) and, while the drop
// counter +0x68 (rate +0x64) passes 1, sprays drops (func_15167D84) until the pool is full. Once the lifetime +0x118
// runs out the newest four points fade (alpha 0 / 0x3F / 0x7F / 0xBE), obj +0x30 is cleared (no more emitting) and
// flag 2 of obj +0x1E dropped. Always returns 1.
s32 func_150DD420(u8 *obj) {
    FountainFx *d = *(FountainFx **) (obj + 0x98);
    u8 *pts = *(u8 **) (obj + 0x94);
    FountainDrop drop;
    f32 inv, dt, step, x, z, dx, dz, sdx, sdz;
    f32 speed, sinA, cosA, sinB, cosB, h;
    u8 a, b;
    s32 more, i;
    u8 *pt;

    d->u04 += ((u32) func_150ADA20() % (d->u06 + 1)) * D_800BE9E4;
    d->u0C += ((u32) func_150ADA20() % (d->u0E + 1)) * D_800BE9E4;
    d->u20 += d->u1C * D_800BE9A4;
    if (D_800A10C4 < d->u20) {
        inv = 1.0f / d->u20;
        dt = D_800BE9A4;
        step = dt * inv;
        x = d->pos[0];
        z = d->pos[1];
        dx = func_151423D8(d->u04 - 0x40) * d->u00 + *(f32 *) (obj + 0x10) - d->pos[0];
        dz = func_151423D8(d->u0C - 0x40) * d->u08 + *(f32 *) (obj + 0x18) - d->pos[1];
        if (1.0f < d->u20) {
            sdx = dx * inv;
            sdz = dz * inv;
            do {
                d->u68 += d->u64;
                if (1.0f < d->u68) {
                    drop.u1C = 0;
                    drop.u1E = 0;
                    drop.u1D = 0;
                    drop.r = 0xFF;
                    drop.g = 0xFF;
                    drop.b = 0xFF;
                    drop.u30 = 0;
                    drop.u31 = 0;
                    drop.u32 = 0;
                    drop.a = 0xFF;
                    drop.u34 = 0x12;
                    drop.u0C = 0;
                    drop.u1F = d->u98;
                    more = 1;
                    drop.u0E = d->u94;
                    drop.tex = d->anim;
                    drop.y = (s32) *(f32 *) (obj + 0x14);
                    drop.u28 = d->u7C;
                    do {
                        speed = func_150ADA68() * d->u78 + d->u74;
                        a = func_150ADA20();
                        sinA = func_151423D8(a);
                        cosA = func_151423D8(a - 0x40);
                        b = (u32) func_150ADA20() % (d->u72 + 1) + d->u70;
                        sinB = func_151423D8(b);
                        cosB = func_151423D8(b - 0x40);
                        drop.x = (s32) (*(f32 *) (obj + 0x10) + d->u6C * cosA);
                        drop.z = (s32) (*(f32 *) (obj + 0x18) + d->u6C * sinA);
                        h = speed * sinB;
                        drop.vx = (s32) (h * cosA);
                        drop.vy = (s32) (-speed * cosB);
                        drop.vz = (s32) (h * sinA);
                        drop.gravity = (s32) (func_150ADA68() * d->u80 + d->u7E);
                        drop.u2A = (u32) func_150ADA20() % (d->u86 + 1) + d->u84;
                        drop.size1 = drop.size0 = (s32) (func_150ADA68() * d->u8C + d->u88);
                        if (func_15167D84(&drop, 0, 0, -1, obj[0xC], obj[1]) == NULL) {
                            more = 0;
                        }
                        d->u68 -= 1.0f;
                    } while (1.0f < d->u68 && more);
                    while (1.0f < d->u68) {
                        d->u68 -= 1.0f;
                    }
                }
                pt = pts + *(s8 *) (obj + 0x2E) * 0x18;
                *(f32 *) (pt + 0x0) = x;
                *(f32 *) (pt + 0x4) = *(f32 *) (obj + 0x14);
                *(f32 *) (pt + 0x8) = z;
                *(f32 *) (pt + 0xC) = d->u38;
                d->u34 += (u32) func_150ADA20() % (d->u36 + 1);
                *(f32 *) (pt + 0x10) = func_151423D8(d->u34 - 0x40) * d->u30 + d->u2C;
                *(s16 *) (pt + 0x14) = d->u29;
                pt[0x16] = d->u40;
                d->u40 = d->u40 + d->u3C + (u32) func_150ADA20() % (d->u3E + 1);
                *(f32 *) (pt + 0xC) += d->u18 * dt;
                *(f32 *) (pt + 0x4) += *(f32 *) (pt + 0xC) * dt;
                (*(s8 *) (obj + 0x2E))++;
                if (*(s8 *) (obj + 0x2E) == obj[0x25]) {
                    *(s8 *) (obj + 0x2E) = 0;
                }
                (*(s8 *) (obj + 0x2C))++;
                if (*(s8 *) (obj + 0x2D) == *(s8 *) (obj + 0x2E)) {
                    (*(s8 *) (obj + 0x2D))++;
                    if (*(s8 *) (obj + 0x2D) == obj[0x25]) {
                        *(s8 *) (obj + 0x2D) = 0;
                    }
                    (*(s8 *) (obj + 0x2C))--;
                }
                x += sdx;
                z += sdz;
                dt -= step;
                d->u20 -= 1.0f;
            } while (1.0f < d->u20);
        }
        d->pos[0] = x;
        d->pos[1] = z;
    }
    d->u118 -= D_800BE9E4;
    if (d->u118 < 0) {
        /* fade the newest four points, walking back around the ring */
        i = *(s8 *) (obj + 0x2E) - 1;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        pt = pts + i * 0x18;
        *(s16 *) (pt + 0x14) = 0;
        i--;
        pt -= 0x18;
        if (i < 0) {
            i = obj[0x25] - 1;
            pt = pts + i * 0x18;
        }
        i--;
        *(s16 *) (pt + 0x14) = 0x3F;
        pt -= 0x18;
        if (i < 0) {
            i = obj[0x25] - 1;
            pt = pts + i * 0x18;
        }
        i--;
        *(s16 *) (pt + 0x14) = 0x7F;
        pt -= 0x18;
        if (i < 0) {
            i = obj[0x25] - 1;
            pt = pts + i * 0x18;
        }
        *(s16 *) (pt + 0x14) = 0xBE;
        obj[0x30] = 0;
        *(u16 *) (obj + 0x1E) &= ~2;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DD420.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800DD608[], D_800DD618[]; /* per view: camera yaw sine / cosine */
extern s32 D_800D30BC;
extern s32 D_800A4EA8[];
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 func_15142E24(s32, struct_eu_80090F10 *, s32, s32, s32, s32, s32, u8, s32, s8 *, s32);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142C10(s32, s32, s32, s32, s32, s8 *);
s32 func_1513F4E4(s32, u8, s8 *);
u8 *func_15142FBC(s32, s32, s32, s8 *);

/* One strip vertex at (px, py, pz): texture s / t (swapped when d +0x60 is 2), white, alpha `alpha`. */
#define FOUNTAIN_VTX(px, py, pz, s, t, alpha) \
    do { \
        *(s16 *) (v + 0x0) = (s32) (px); \
        *(s16 *) (v + 0x2) = (s32) (py); \
        *(s16 *) (v + 0x4) = (s32) (pz); \
        *(s16 *) (v + 0x8 + sIdx * 2) = (s); \
        *(s16 *) (v + 0x8 + tIdx * 2) = (t); \
        v[0xC] = 0xFF; \
        v[0xD] = 0xFF; \
        v[0xE] = 0xFF; \
        v[0xF] = (alpha); \
        *(s16 *) (v + 0x6) = 0; \
        v += 0x10; \
    } while (0)

// fountain_draw: draw handler 4 of D_8008A644 (`s32 (u8 *, s32 gfx, s16 view)`, func_151481BC) for the effect of
// func_150DC2F0: the water points (obj +0x94, see func_150DD420) as one strip from the newest to the oldest, each
// point widened by its +0x10 sideways to the camera (D_800DD608 / D_800DD618[view]); while the effect still emits
// (obj +0x1E flag 2) the strip starts at the object itself. Texture D_80090F10[d +0x41] (s from the point byte
// +0x16; where s grows backwards the last pair is repeated with s - 0x4000 so the texture wraps), colour d +0x28,
// combine / render mode from the nibbles of d +0x42. Vertices come from func_151D6310. Returns the display list
// end; draws nothing with fewer than 2 points. The asm takes the head's alpha (emitting case) through an index it
// never sets (stack slot sp+0x98): this C uses the newest point there.
s32 func_150DDBC0(u8 *obj, s32 gfx, s16 view) {
    FountainFx *d;
    u8 *pts;
    u8 *v;
    u8 *p;
    u8 *head;
    f32 sinV, cosV, w;
    f32 hx, hy, hz;
    f32 px, py, pz;
    s32 i, k;
    u8 sIdx, tIdx, mode, comb, sPrev, sCur;
    s8 flag;

    if (*(s8 *) (obj + 0x2C) < 2) {
        return gfx;
    }
    func_151D6310((s32 *) (obj + 0x84), view, obj[0x25] * 0x20 + 0xA0, (s32 *) &v, NULL);
    if (v == NULL) {
        return gfx;
    }
    d = *(FountainFx **) (obj + 0x98);
    pts = *(u8 **) (obj + 0x94);
    flag = 1;
    mode = d->u42 & 0xF;
    comb = (d->u42 & 0xF0) >> 4;
    sinV = D_800DD608[view];
    cosV = D_800DD618[view];
    if (d->u60 == 2) {
        sIdx = 1;
        tIdx = 0;
    } else {
        sIdx = 0;
        tIdx = 1;
    }
    gfx = func_15142E24(gfx, &D_80090F10[d->u41], 0, 0, 0, 0, d->u41, 0, 0, &flag, 3);
    gfx = func_15142C10(gfx, d->u28, d->u28, d->u28, 0xFF, &flag);
    gfx = func_1513F4E4(gfx, comb, &flag);
    gfx = func_15142B7C(gfx, 1, 0x160600);
    gfx = (s32) func_15142FBC(gfx, D_800D30BC | 0x80000 | 0x2CA0, D_800A4EA8[mode * 2 + 1] | D_800A4EA8[mode * 2],
                              &flag);
    if (*(u16 *) (obj + 0x1E) & 2) {
        /* still emitting: the strip starts at the object */
        i = *(s8 *) (obj + 0x2E) - 1;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        hx = *(f32 *) (obj + 0x10);
        hy = *(f32 *) (obj + 0x14);
        hz = *(f32 *) (obj + 0x18);
        p = pts + i * 0x18;
        head = p;
        sCur = p[0x16];
        sPrev = sCur;
    } else {
        k = *(s8 *) (obj + 0x2E) - 1;
        if (k < 0) {
            k = obj[0x25] - 1;
        }
        i = k - 1;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        head = pts + k * 0x18;
        hx = *(f32 *) (head + 0x0);
        hy = *(f32 *) (head + 0x4);
        hz = *(f32 *) (head + 0x8);
        p = pts + i * 0x18;
        sPrev = head[0x16];
        sCur = p[0x16];
    }
    px = *(f32 *) (p + 0x0);
    py = *(f32 *) (p + 0x4);
    pz = *(f32 *) (p + 0x8);
    w = *(f32 *) (p + 0x10);
    FOUNTAIN_VTX(w * cosV + hx, hy, hz - w * sinV, sPrev << 6, 0, *(s16 *) (head + 0x14));
    FOUNTAIN_VTX(hx - w * cosV, hy, w * sinV + hz, sPrev << 6, (D_80090F10[d->u41].unk6 - 1) << 6,
                 *(s16 *) (head + 0x14));
    for (;;) {
        w = *(f32 *) (p + 0x10);
        FOUNTAIN_VTX(w * cosV + px, py, pz - w * sinV, sCur << 6, 0, *(s16 *) (p + 0x14));
        FOUNTAIN_VTX(px - w * cosV, py, w * sinV + pz, sCur << 6, (D_80090F10[d->u41].unk6 - 1) << 6,
                     *(s16 *) (p + 0x14));
        ((s32 *) gfx)[0] = 0x01004008; /* gSPVertex(v - 4, 4, 0) */
        ((s32 *) gfx)[1] = (s32) (v - 0x40);
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05000204; /* gSP1Triangle(0, 1, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020604; /* gSP1Triangle(1, 3, 2) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        if (sPrev < sCur) {
            /* s wrapped: repeat this pair for the next segment, this one ends at s - 0x4000 */
            memcpy(v, v - 0x20, 0x20);
            *(s16 *) (v - 0x20 + 0x8 + sIdx * 2) -= 0x4000;
            v += 0x10;
            *(s16 *) (v - 0x20 + 0x8 + sIdx * 2) -= 0x4000;
            v += 0x10;
        }
        sPrev = sCur;
        k = i;
        i--;
        p -= 0x18;
        if (i < 0) {
            i = obj[0x25] - 1;
            p = pts + i * 0x18;
        }
        px = *(f32 *) (p + 0x0);
        py = *(f32 *) (p + 0x4);
        pz = *(f32 *) (p + 0x8);
        sCur = p[0x16];
        if (k == *(s8 *) (obj + 0x2D)) {
            break;
        }
    }
    return gfx;
}
#undef FOUNTAIN_VTX
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_109770/func_150DDBC0.s")
#endif

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
