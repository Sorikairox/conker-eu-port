#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_1514F878
typedef struct { s32 w[3]; } V3_1514F878;
extern V3_1514F878 D_800A5D50;
extern V3_1514F878 D_800A5D5C;
extern f32 D_800A6238;

s32 func_1514F2FC(u8 *, u8 *);

s32 func_1514F2AC(u8 *, s32, u8 **);

u8 *func_15160A58(struct127 *, s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void *func_1518A560(void *, void *, void *, s32, s32, s32, s32);


#ifdef NON_MATCHING
// character_handler_indices: picks the handler-table indices for a character (P151). By the character type
// (+0x4) it sets *outType (index into D_800A62B8, flag 4); by the game mode D_800BE9F0 it sets *outMode (index
// into D_800A62A0, flag 2) and, when the character's sub-type (+0x3B) matches the mode, *outSub (column of
// D_8008AF30[*outMode], flag 1). Returns the flags; outputs whose flag is clear are left unwritten.
s32 func_1514CFF0(struct127 *arg0, s32 *outSub, s32 *outMode, s32 *outType) {
    u8 *obj = (u8 *)arg0;
    u8 flags = 0;
    u8 sub;

    switch (obj[4]) {
        case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x96: *outType = 0; flags = 4; break;
        case 0x08: *outType = 2; flags = 4; break;
        case 0x0A: *outType = 3; flags = 4; break;
        case 0x29: case 0x2A: *outType = 4; flags = 4; break;
        case 0x53: *outType = 5; flags = 4; break;
        case 0x77: *outType = 6; flags = 4; break;
        case 0x47: *outType = 7; flags = 4; break;
        case 0x28: *outType = 8; flags = 4; break;
        case 0x7B: *outType = 9; flags = 4; break;
        case 0x12: *outType = 0xA; flags = 4; break;
        case 0x8D: *outType = 0xB; flags = 4; break;
        case 0x93: *outType = 0xC; flags = 4; break;
        case 0x9F: case 0xA0: *outType = 0xD; flags = 4; break;
        case 0x94: *outType = 0xE; flags = 4; break;
        case 0x92: *outType = 0xF; flags = 4; break;
        case 0x6B: *outType = 0x10; flags = 4; break;
        case 0xAD: *outType = 0x11; flags = 4; break;
        case 0x86: *outType = 0x12; flags = 4; break;
        case 0x52: *outType = 0x13; flags = 4; break;
        case 0x89: case 0xBA: *outType = 0x14; flags = 4; break;
        case 0x99: *outType = 0x15; flags = 4; break;
        case 0x7F: *outType = 0x16; flags = 4; break;
        case 0x10: case 0x2E: *outType = 0x17; flags = 4; break;
        case 0x9A: *outType = 0x18; flags = 4; break;
        case 0x5E: *outType = 0x19; flags = 4; break;
        case 0x25: *outType = 0x1A; flags = 4; break;
        case 0x5F: *outType = 0x1B; flags = 4; break;
    }

    sub = obj[0x3B];
    switch ((u32)D_800BE9F0) {
        case 0x00: *outMode = 0x10; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x02:
            *outMode = 0;
            flags |= 2;
            switch (sub) {
                case 7: *outSub = 1; flags |= 1; break;
                case 9: *outSub = 0; flags |= 1; break;
                case 0xD: *outSub = 3; flags |= 1; break;
                case 0xE: case 0xF: case 0x17: case 0x19: *outSub = 2; flags |= 1; break;
            }
            break;
        case 0x04: *outMode = 6; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x06: *outMode = 2; flags |= 2; break;
        case 0x07: *outMode = 5; flags |= 2; if (sub == 0x10) { *outSub = 0; flags |= 1; } break;
        case 0x0A:
            *outMode = 1;
            flags |= 2;
            switch (sub) {
                case 6: case 7: case 8: case 9: case 0xA: case 0xB: case 0xC: case 0xD:
                    *outSub = sub - 6; flags |= 1; break;
                case 0xF: *outSub = 8; flags |= 1; break;
            }
            break;
        case 0x0C: *outMode = 3; flags |= 2; break;
        case 0x0E:
            *outMode = 7;
            flags |= 2;
            if (sub == 1) {
                *outSub = 1; flags |= 1;
            } else if (sub == 8) {
                *outSub = 0; flags |= 1;
            }
            break;
        case 0x10: *outMode = 4; flags |= 2; if (sub == 6) { *outSub = 0; flags |= 1; } break;
        case 0x14: *outMode = 8; flags |= 2; if (sub == 0x10) { *outSub = 0; flags |= 1; } break;
        case 0x17: *outMode = 9; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x1B: *outMode = 0xA; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x1E: *outMode = 0xB; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x26: *outMode = 0xC; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x1C: *outMode = 0xD; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x28: *outMode = 0xE; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x23: *outMode = 0xF; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x2C: *outMode = 0x11; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x2F: *outMode = 0x12; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x35: *outMode = 0x13; flags |= 2; if (sub == 1) { *outSub = 0; flags |= 1; } break;
        case 0x1D: *outMode = 0x14; flags |= 2; if (sub == 9) { *outSub = 0; flags |= 1; } break;
        case 0x2B:
            *outMode = 0x15;
            flags |= 2;
            if (obj[4] == 0x9C || obj[4] == 0x9D) {
                *outSub = 0; flags |= 1;
            }
            break;
    }
    return flags;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514CFF0.s")
#endif

s32 func_1514CFF0(struct127 *, s32 *, s32 *, s32 *);
void func_15155CF0(s32, s32);
struct102 *func_15156544(s32);
extern void (*D_8008AE10[])(struct127 *);
extern void (*D_8008AE6C)(struct127 *);
extern u8 *D_8008AF30[];
extern u8 D_800A62A0[];
extern u8 D_800A62B8[];

s32 func_1514D6CC(struct127 *arg0) {
    s32 sp44 = -1;
    s32 sp40 = -1;
    s32 sp3C = -1;
    u8 r;
    s32 idx;
    s32 ret;
    struct102 *e;
    u8 v;

    if (*(s32 *)((u8 *)arg0 + 0x2F4) != 0) {
        return 0;
    }
    idx = arg0 - D_800CC2D0;
    do {
        e = func_15156544(idx);
        if (e != NULL) {
            func_1516972C(e);
        }
    } while (e != NULL);
    if (idx == 0 && D_800BE616 == 0) {
        func_15155CF0(idx, 0xFF);
    }
    D_8008AE6C(arg0);
    ret = func_1514CFF0(arg0, &sp44, &sp40, &sp3C);
    r = ret;
    if (ret == 0) {
        return 0;
    }
    if (r & 4) {
        v = D_800A62B8[sp3C];
        if (v != 0) {
            D_8008AE10[v](arg0);
        }
    }
    if (r & 2) {
        v = D_800A62A0[sp40];
        if (v != 0) {
            D_8008AE10[v](arg0);
        }
    }
    if ((r & 2) && (r & 1)) {
        if (D_8008AE10[D_8008AF30[sp40][sp44]] != NULL) {
            D_8008AE10[D_8008AF30[sp40][sp44]](arg0);
        }
    }
    return 1;
}

extern u8 *D_8008AF88[];
extern void (*D_8008AEF8[])(s32);

s32 func_1514D880(u8 *arg0) {
    struct102 *p;
    struct102 *next;

    p = *(struct102 **)(arg0 + 0x2F4);
    if (p != NULL) {
        do {
            next = *(struct102 **)((u8 *)p + 0x14);
            // fakematch: the s16 index is re-read for the call (no local) and compared as -1 != x; keeps the register order of the original
            if (-1 != *(s16 *)(D_8008AF88[*(s16 *)((u8 *)p + 0x1C)] + 2)) {
                D_8008AEF8[*(s16 *)(D_8008AF88[*(s16 *)((u8 *)p + 0x1C)] + 2)](*(s32 *)((u8 *)p + 0x10));
            }
            func_1516972C(p);
            p = next;
        } while (next != NULL);
    }
    return 1;
}

#ifdef NON_MATCHING
s32 func_1514DA28();   /* K&R definition below (s16 state, s16 base) */
extern s32 (*D_8008AF04[])(u8 *, s32, s32);   /* state event handlers: func_1514EE0C .. func_1514F0FC (8) */
// obj_state_event_dispatch: sends an event (arg2, arg3) to every state node of obj (list at +0x2F4, linked through
// +0x14) whose state (+0x1C) is `state` or derives from it (func_1514DA28 on the state table D_8008AF88); each
// matching node's state record names its handler (s16 at +0, -1 = none) in D_8008AF04, called with the node's data
// (+0x10). Returns whether the last handler called accepted the event (0 when none was called).
// The event values are full words (P218: the asm passes a2 / a3 to the handler unmasked).
// Callers: func_15079390 (game_A28B0), func_15024910 (game_eu_51190, state 0xD with an animation), func_150EDCC8.
s32 func_1514D3B0(s32 obj, s16 state, s32 arg2, s32 arg3) {
    u8 *node;
    s16 idx;
    s32 handled;

    handled = 0;
    for (node = *(u8 **) ((u8 *) obj + 0x2F4); node != NULL; node = *(u8 **) (node + 0x14)) {
        if (state != *(s16 *) (node + 0x1C)
            && func_1514DA28(*(s16 *) (D_8008AF88[state] + 4), *(s16 *) (node + 0x1C)) == 0) {
            continue;
        }
        idx = *(s16 *) D_8008AF88[*(s16 *) (node + 0x1C)];
        if (idx != -1) {
            handled = D_8008AF04[idx](*(u8 **) (node + 0x10), arg2, arg3) != 0;
        }
    }
    return handled;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514D3B0.s")
#endif

s32 func_1514DA28(arg0, arg1)
s16 arg0;
s16 arg1;
{
    if (arg0 == -1) {
        return 0;
    }
    if (arg0 == arg1) {
        return 1;
    }
    if (func_1514DA28(*(s16 *)(D_8008AF88[arg0] + 6), arg1, arg0) != 0) {
        return 1;
    }
    if (func_1514DA28(*(s16 *)(D_8008AF88[arg0] + 4), arg1) != 0) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
/* P241: readable C for func_1514DAD4 (game_eu_17A800, 58 insns). */
// object_fixed_beam_spawn: entry 16 of D_8008AE10 (`void (struct127 *)`): spawns a beam effect (func_150C5870,
// kind 0x46) from the fixed point (-477, -2015, 2244) to the object's position +0x14, width 0.32, gives it the
// record {object, its id byte +0x3B, 6, 0, -180, 77} at +0xC8 and attaches it to the object (func_1514F18C, slot
// 0x15). Constants: the ELF's D_800A61C4..D_800A61D0 (0xC3EE8000, 0xC4FBE000, 0x450C4000, 0x3EA3D70A).
typedef struct {
    f32 start[3];
    f32 end[3];
    u8 flag18;
    f32 width;
    u8 flag20;
} BeamSpawn_1514DAD4; /* func_150C5870 copies 0x24 bytes */
typedef struct {
    struct127 *owner;
    u8 ownerId;
    u8 kind;
    f32 f8;
    f32 fC;
    f32 f10;
} BeamRec_1514DAD4; /* 0x14 bytes at effect +0xC8 */
u8 *func_150C5870(s32, s32);
void func_1514DAD4(struct127 *obj) {
    BeamRec_1514DAD4 rec;
    BeamSpawn_1514DAD4 blk;
    u8 *fx;

    rec.owner = obj;
    rec.ownerId = ((u8 *) obj)[0x3B];
    rec.kind = 6;
    rec.f8 = 0.0f;
    rec.fC = -180.0f;
    rec.f10 = 77.0f;
    blk.start[0] = -477.0f;
    blk.start[1] = -2015.0f;
    blk.start[2] = 2244.0f;
    blk.end[0] = *(f32 *) ((u8 *) obj + 0x14);
    blk.end[1] = *(f32 *) ((u8 *) obj + 0x18);
    blk.end[2] = *(f32 *) ((u8 *) obj + 0x1C);
    blk.flag18 = 1;
    blk.width = 0.32f;
    blk.flag20 = 1;
    fx = func_150C5870((s32) &blk, 0x14);
    if (fx != NULL) {
        memcpy(fx + 0xC8, &rec, sizeof(rec));
        func_1514F18C(fx, obj, 0x15);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DAD4.s")
#endif

void func_1514DBBC(struct127 *arg0) {
    s32 pad; // fakematch: unused slot at the top of the frame
    struct {
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        u8 padC8[0x24];
        f32 uEC;
        u8 padF0[8];
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
    } b;
    struct {
        s8 u4C;
        u8 pad4D;
        s16 u4E;
        s16 u50;
        u8 pad52[2];
        s32 u54;
        s32 u58;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        u8 pad60[8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0xC];
        s32 u8C;
        u8 pad90;
        u8 u91;
        u8 pad92[0x12];
    } a;
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        struct127 *u44;
        s8 u48;
        u8 u49;
        s8 u4A;
        u8 pad4B;
    } c;

    a.u4C = 3;
    a.u54 = 0;
    a.u58 = 0;
    a.u8C = 0x12012;
    a.u50 = 0;
    a.u91 = 0xFF;
    a.u5C = 0xFF;
    a.u5D = 0;
    a.u5E = 0;
    a.u5F = 0xFF;
    a.u4E = 0x401;
    a.u68 = 0.0f;
    a.u6C = 0.0f;
    a.u70 = 0.0f;
    a.u74 = 0.0f;
    a.u78 = 0.0f;
    a.u7C = 0.0f;
    b.uA4 = 28.0f;
    b.uA8 = 28.0f;
    b.uAC = 4.0f;
    b.uB0 = 17.0f;
    b.uB4 = 0.5f;
    b.uB8 = 0.5f;
    b.uBC = 0.75f;
    b.uC0 = 0.25f;
    b.uC4 = 1e-06f;
    c.u49 = arg0->unique_id;
    c.u44 = arg0;
    c.u2C = 0.0f;
    c.u30 = 0.0f;
    c.u38 = 0.0f;
    c.u3C = 0.0f;
    c.u48 = 0x2B;
    b.uF8 = 0;
    b.uF9 = 0;
    b.uFA = 0;
    b.uFB = 0;
    c.u4A = 1;
    c.u34 = 25.0f;
    c.u40 = 75.0f;
    b.uEC = 1.0f;
    func_1514F18C(func_1518A560(&a, &b, &c, 2, 0, 0, 0), arg0, 9);
    a.u4C = 3;
    a.u54 = 0;
    a.u58 = 0;
    a.u8C = 0x12012;
    a.u50 = 0;
    a.u91 = 0xFF;
    a.u5C = 0xFF;
    a.u5D = 0;
    a.u5E = 0;
    a.u5F = 0xFF;
    a.u4E = 0x401;
    b.uA4 = 30.0f;
    b.uA8 = 30.0f;
    b.uAC = 10.0f;
    b.uB4 = 0.8f;
    b.uB8 = 0.8f;
    a.u68 = 0.0f;
    a.u6C = 0.0f;
    a.u70 = 0.0f;
    a.u74 = 0.0f;
    a.u78 = 0.0f;
    a.u7C = 0.0f;
    b.uBC = 0.6f;
    b.uC0 = 0.6f;
    b.uB0 = 16.0f;
    b.uC4 = 1e-06f;
    c.u49 = arg0->unique_id;
    c.u44 = arg0;
    c.u48 = 5;
    b.uF8 = 0;
    b.uF9 = 0;
    b.uFA = 0;
    b.uFB = 0;
    c.u4A = 0;
    c.u30 = 10.0f;
    c.u2C = 0.0f;
    c.u38 = 0.0f;
    c.u34 = -70.0f;
    c.u3C = 20.0f;
    c.u40 = -140.0f;
    b.uEC = 1.0f;
    func_1514F18C(func_1518A560(&a, &b, &c, 2, 0, 0, 0), arg0, 0xA);
    func_15160A58(arg0, 5, (s32 *)&c, 2, 0x12C, 0x28, 0xFF, 0, 0, 0xFF, 0, 1, 0, 0, 0xFF, 1);
}

void func_1514DEDC(s32 arg0) {
}

void func_1514DEE8(struct127 *arg0) {
    f32 buf[8];
    u8 *r;
    *(s32 *)&buf[0] = 0;
    *(s32 *)&buf[1] = 0;
    *(s32 *)&buf[2] = 0;
    *(s32 *)&buf[3] = 0;
    *(s32 *)&buf[5] = 0;
    *(s32 *)&buf[6] = 0;
    *(s32 *)&buf[7] = 0;
    buf[4] = 12.0f;
    r = func_15159140(arg0, 1, 0x20);
    if (r != NULL) {
        memcpy(r + 0x58, buf, 0x20);
        func_1514F18C(r, arg0, 0x13);
    }
}

#ifdef NON_MATCHING
u8 *func_151AD010(u8 *, f32, s32); /* P95 */
#endif
void func_1514DF64(struct127 *arg0) {
    func_1514DEE8(arg0);
#ifdef NON_MATCHING
    func_1514F18C(func_151AD010(arg0, 20.0f, 0), arg0, 0x14); /* P95: float literal (asm passes the bits 0x41A00000) */
#else
    func_1514F18C(func_151AD010(arg0, 0x41A00000, 0), arg0, 0x14);
#endif
}

void func_1514DFA8(struct127 *arg0) {
    u8 *r;
    s32 buf[7];
    buf[5] = 0;
    buf[6] = 0;
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    r = func_15159140(arg0, 1, 0x1C);
    if (r != NULL) {
        memcpy(r + 0x58, buf, 0x1C);
        func_1514F18C(r, arg0, 0x13);
    }
}

void func_1514E014(struct127 *arg0) {
    u8 *p;
    s32 buf[2];

    arg0->unk94 |= 2;
    buf[0] = 0;
    buf[1] = 0;
    if ((arg0 && arg0) && arg0) { // fakematch: permuter, moves the a2 = 8 setup before the memcpy call
    }
    p = func_15159140(arg0, 1, 8);
    if (p != NULL) {
        memcpy(p + 0x58, buf, 8);
        func_1514F18C(p, arg0, 0x13);
    }
}

void func_1514E088(struct127 *arg0) {
    s32 temp_v0 = func_15159140(arg0, 1, 0);
    if (temp_v0 != 0) {
        func_1514F18C(temp_v0, arg0, 0x13);
    }
}

void func_1514E0C8(s32 arg0) {
}

void func_1514E0D4(u8 *arg0) {   /* P76: callback; a0 passes through */
    if (D_800BE9F0 == 0x14) {
        func_151B2610(arg0);
    }
}

void func_1514E108(struct127 *arg0) {   /* P76: callback; a0 passes through */
    func_1514F704(arg0);
}

void func_1514E128(struct127 *arg0) {
    func_15160A58(arg0, 2, (s32 *)D_800A5C80, 2, 0x12C, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

void func_1514E1A8(struct127 *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}

void func_1514E1CC(s32 arg0) {
    func_151D1510(arg0, 0, 0xFF, 1);
}

void func_1514E1F4(u8 *arg0) {
    *(s32 *)(arg0 + 0x94) |= 2;
}

void func_1514E208(u8 *arg0) {
    *(s32 *)(arg0 + 0x94) |= 0x710;
}

void func_1514E21C(struct127 *arg0) {
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 1.0f, 0);
    func_15083568(arg0, 0x44, 1.0f, 0);
}

void func_1514E264(struct127 *arg0) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x31C);
    if (v != NULL) {
        v[0x94] = 1;
    }
    func_15083568(arg0, 0x17, 1.0f, 0);
}

void func_1514E29C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2BC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2DC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2FC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E31C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E33C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E35C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E37C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E39C(s32 arg0) {
}

void func_1514E3A8(s32 arg0) {
}

void func_1514E3B4(s32 arg0) {
}

void func_1514E3C0(struct127 *arg0) {
    if (((u8 *)D_800D2E4C)[0x11] & 8) {
        func_1514E21C(arg0);
    }
}

void func_1514E3F8(s32 arg0) {
}

extern u8 D_800A5C8C[];
extern u8 D_800A5C98[];
extern u8 D_800A5CA4[];
extern f32 D_800A61E4;
s32 func_15160CDC(struct127 *, s32, s32 *, s32 *, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1514E404(struct127 *arg0) {
    s32 temp_v0;

    func_15160CDC(arg0, 0xC, D_800A5C8C, D_800A5C98, D_800A61E4, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 1, 0xFF, 1);
    temp_v0 = func_15083568(arg0, 0x3C, 1.0f, 0);
    if (D_800BE9B4 == 0) {
        (*(s32 *)((u8 *)temp_v0 + 0x38)) = 0x7D0;
    }
    func_1514F18C(func_15160A58(arg0, 0, D_800A5CA4, 2, 0x12C, 0xB, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0, 0xFF, 1), arg0, 0x19);
}

void func_1514E540(u8 *arg0) {
    arg0[0x65] = func_15083FB0(9, arg0) + 1;
    arg0[0x101] |= 0x34;
}

extern f32 D_800A61E8;
extern f32 D_800A61EC;
void func_1514E57C(struct127 *arg0) {
    s32 pad; // fakematch: unused slot at the top of the frame
    struct {
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        u8 padC8[0x24];
        f32 uEC;
        u8 padF0[8];
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
    } b;
    struct {
        s8 u4C;
        u8 pad4D;
        s16 u4E;
        s16 u50;
        u8 pad52[2];
        s32 u54;
        s32 u58;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        u8 pad60[8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0xC];
        s32 u8C;
        u8 pad90;
        u8 u91;
        u8 pad92[0x12];
    } a;
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        struct127 *u44;
        s8 u48;
        u8 u49;
        s8 u4A;
        u8 pad4B;
    } c;

    a.u4C = 3;
    a.u54 = 0;
    a.u58 = 0;
    a.u8C = 0x12002;
    a.u50 = 0;
    a.u91 = 0xFF;
    a.u5C = 0xFF;
    a.u5D = 0x8E;
    a.u5E = 0x19;
    a.u5F = 0xFF;
    a.u4E = 0x401;
    a.u68 = 0.0f;
    a.u6C = 0.0f;
    a.u70 = 0.0f;
    a.u74 = 0.0f;
    a.u78 = 0.0f;
    a.u7C = 0.0f;
    b.uA4 = 20.0f;
    b.uA8 = 20.0f;
    b.uAC = 20.0f;
    b.uB0 = 20.0f;
    b.uB4 = 0.0f;
    b.uB8 = 0.0f;
    b.uBC = 0.5f;
    b.uC0 = 0.5f;
    b.uC4 = D_800A61E8;
    c.u49 = arg0->unique_id;
    c.u2C = 35.0f;
    c.u44 = arg0;
    c.u30 = 27.0f;
    c.u38 = 35.0f;
    c.u3C = 27.0f;
    c.u48 = 6;
    b.uF8 = 0;
    b.uF9 = 0;
    b.uFA = 0;
    b.uFB = 0;
    c.u4A = -1;
    c.u34 = 59.0f;
    c.u40 = D_800A61EC;
    b.uEC = 1.0f;
    func_1514F18C(func_1518A560(&a, &b, &c, 2, 0, 0, 0), arg0, 6);
    func_151D7A60(arg0, 5, -1, 0xFF, 1);
}

extern f32 D_800A61F0;
extern f32 D_800A61F4;
void func_1514E704(struct127 *arg0) {
    s32 pad; // fakematch: unused slot at the top of the frame
    struct {
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        u8 padC8[0x24];
        f32 uEC;
        u8 padF0[8];
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
    } b;
    struct {
        s8 u4C;
        u8 pad4D;
        s16 u4E;
        s16 u50;
        u8 pad52[2];
        s32 u54;
        s32 u58;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        u8 pad60[8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0xC];
        s32 u8C;
        u8 pad90;
        u8 u91;
        u8 pad92[0x12];
    } a;
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        struct127 *u44;
        s8 u48;
        u8 u49;
        s8 u4A;
        u8 pad4B;
    } c;

    a.u4C = 3;
    a.u54 = 0;
    a.u58 = 0;
    a.u8C = 0x12002;
    a.u50 = 0;
    a.u91 = 0xFF;
    a.u5C = 0xFF;
    a.u5D = 0x8E;
    a.u5E = 0x19;
    a.u5F = 0xFF;
    a.u4E = 0x401;
    a.u68 = 0.0f;
    a.u6C = 0.0f;
    a.u70 = 0.0f;
    a.u74 = 0.0f;
    a.u78 = 0.0f;
    a.u7C = 0.0f;
    b.uA4 = 16.0f;
    b.uA8 = 16.0f;
    b.uAC = 16.0f;
    b.uB0 = 16.0f;
    b.uB4 = 0.0f;
    b.uB8 = 0.0f;
    b.uBC = 0.5f;
    b.uC0 = 0.5f;
    b.uC4 = D_800A61F0;
    c.u49 = arg0->unique_id;
    c.u2C = 35.0f;
    c.u44 = arg0;
    c.u30 = 27.0f;
    c.u38 = 35.0f;
    c.u3C = 27.0f;
    c.u48 = 6;
    b.uF8 = 0;
    b.uF9 = 0;
    b.uFA = 0;
    b.uFB = 0;
    c.u4A = -1;
    c.u34 = 59.0f;
    c.u40 = D_800A61F4;
    b.uEC = 1.0f;
    func_1514F18C(func_1518A560(&a, &b, &c, 2, 0, 0, 0), arg0, 6);
    func_151D7A60(arg0, 5, -1, 0xFF, 1);
}

#ifdef NON_MATCHING
// object_glow_attach: handler (table EU 8008AE1C) that builds a sprite effect (func_1518A560 with the same
// three records as func_1514DBBC: render block a, size / fade block b, attachment c = {obj, its id, joint 0xC, mode
// 2, offset (0, 100, 0) .. (0, 600, 0)}), attaches it to the object in slot 7 (func_1514F18C), then adds a light
// (func_15160A58: joint 0xC, offset (0, 0, 150), then 300, 40, 255, 181, 0, 255, 0, 2, 0, 0, 255, 1).
void func_1514E88C(struct127 *obj) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        struct127 *u44;
        s8 u48;
        u8 u49;
        s8 u4A;
        u8 pad4B;
    } c;
    struct {
        s8 u4C;
        u8 pad4D;
        s16 u4E;
        s16 u50;
        u8 pad52[2];
        s32 u54;
        s32 u58;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        u8 pad60[8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0xC];
        s32 u8C;
        u8 pad90;
        u8 u91;
        u8 pad92[0x12];
    } a;
    struct {
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        u8 padC8[0x24];
        f32 uEC;
        u8 padF0[8];
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
    } b;
    f32 light[3];

    a.u4C = 3;
    a.u54 = 0;
    a.u58 = 0;
    a.u8C = 0x2012;
    a.u50 = 0;
    a.u91 = 0xFF;
    a.u5C = 0xFF;
    a.u5D = 0xE6;
    a.u5E = 0;
    a.u5F = 0xFF;
    a.u4E = 0x401;
    a.u68 = 0.0f;
    a.u6C = 0.0f;
    a.u70 = 0.0f;
    a.u74 = 0.0f;
    a.u78 = 0.0f;
    a.u7C = 0.0f;
    b.uA4 = 45.0f;
    b.uB0 = 45.0f;
    b.uB4 = 0.5f;
    b.uB8 = 0.5f;
    b.uC0 = 0.0f;
    b.uA8 = 55.0f;
    b.uAC = 25.0f;
    b.uBC = 0.9f;
    b.uC4 = 1e-06f;
    c.u49 = obj->unique_id;
    c.u2C = 0.0f;
    c.u30 = 0.0f;
    c.u38 = 0.0f;
    c.u3C = 0.0f;
    c.u48 = 0xC;
    b.uF8 = 0;
    b.uF9 = 0;
    b.uFA = 0;
    b.uFB = 0;
    c.u4A = 2;
    c.u34 = 100.0f;
    c.u40 = 600.0f;
    c.u44 = obj;
    b.uEC = 1.0f;
    func_1514F18C(func_1518A560(&a, &b, &c, 2, 3, 0, 0), obj, 7);
    light[0] = 0.0f;
    light[1] = 0.0f;
    light[2] = 150.0f;
    func_15160A58(obj, 0xC, (s32 *)light, 2, 0x12C, 0x28, 0xFF, 0xB5, 0, 0xFF, 0, 2, 0, 0, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E88C.s")
#endif

u8 * func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);
u8 * func_1518D1C0(struct127 *, s16, s32, u8, u8, s32, u8 *);

void func_1514EA78(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CB0), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EB28(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CC4), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EBD8(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CD8), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EC88(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CEC), arg0, 0xE);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}

void func_1514ED38(struct127 *arg0) {
    func_1514F18C(func_1518D1C0(arg0, 7, 0, 1, 0xFF, 1, D_800A5D00), arg0, 0xF);
}

void func_1514ED94(s32 arg0) {
}

void func_1514EDA0(struct102 *arg0) {
    func_1516972C(arg0);
}

void func_1514EDC0(struct102 *arg0) {
    func_1518E878(arg0);
    func_1516972C(arg0);
}

void func_1514EDEC(s32 arg0) {   /* P76: callback; a0 passes through */
    func_1515F10C(arg0);
}

s32 func_1514EE0C(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        if (*(s32 *)(arg0 + 0x10) & 1) {
            *(s32 *)(arg0 + 0x10) &= ~1;
        } else {
            *(s32 *)(arg0 + 0x10) |= 1;
        }
        break;
    case 2:
        *(s32 *)(arg0 + 0x10) &= ~1;
        break;
    case 1:
        *(s32 *)(arg0 + 0x10) |= 1;
        break;
    default:
        return 0;
    }
    return 1;
}

s32 func_1514EE90(u8 *arg0, s32 arg1, s32 arg2)
{
  u8 *v = arg0 + 0x110;
  s32 f;
  switch (arg1)
  {
    case 0:
      f = *((s32 *) (arg0 + 0x10));
      if (f & 1)
    {
      *((s32 *) (arg0 + 0x10)) = f & (~1);
      if ((*((u8 **) (v + 0x44))) != 0)
      {
        (*((u8 **) (v + 0x44)))[0x30] = 0;
      }
    }
    else
    {
      *((s32 *) (arg0 + 0x10)) = f | 1;
    }
      break;

    case 2:
      *((s32 *) (arg0 + 0x10)) &= ~1;
      if ((*((u8 **) (v + 0x44))) != 0)
    {
      (*((u8 **) (v + 0x44)))[0x30] = 0;
      v++; // fakematch: permuter
      v--;
    }
      break;

    case 1:
      *((s32 *) (arg0 + 0x10)) |= 1;
      break;

    default:
      return func_1514EE0C(arg0, arg1, arg2);

  }

  return 1;
}

s32 func_1514EF4C(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE90(arg0, arg1, arg2);
}

s32 func_1514EF6C(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE0C(arg0, arg1, arg2);
}

s32 func_1514EF8C(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 3:
        if (arg0[0x22] == 2) {
            func_1518E8EC(arg0, 3);
        } else {
            func_1518E8EC(arg0, 2);
        }
        break;
    case 4:
        func_1518E8EC(arg0, 3);
        break;
    case 5:
        func_1518E8EC(arg0, 2);
        break;
    case 6:
        if (arg0[0x22] == 2) {
            func_1518E8EC(arg0, 5);
        } else {
            func_1518E8EC(arg0, 2);
        }
        break;
    case 7:
        func_1518E8EC(arg0, 5);
        break;
    case 8:
        func_1518E8EC(arg0, 2);
        break;
    case 9:
        if (arg0[0x22] == 2) {
            func_1518E8EC(arg0, 6);
        } else {
            func_1518E8EC(arg0, 2);
        }
        break;
    case 10:
        func_1518E8EC(arg0, 6);
        break;
    case 11:
        func_1518E8EC(arg0, 2);
        break;
    case 12:
        func_1518E8EC(arg0, 2);
        break;
    default:
        return func_1514EE0C(arg0, arg1, arg2);
    }
    return 1;
}

s32 func_1514F0DC(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE0C(arg0, arg1, arg2);
}

s32 func_1514F0FC(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}

u8 *func_1514F114(s32 arg0, s16 arg1, s32 arg2)
{
  int new_var2;
  u8 *new_var;
  u8 *temp_v0;
  temp_v0 = func_15167A68(0x24, 1, arg2 + 0x20, 1, 0xFFU, 1U);
  if ((temp_v0 == 0) ^ 0)
  {
    return 0;
  }
  new_var = ((u8 *) temp_v0) + 0x10; // fakematch: permuter temp for the store order
  *((s32 *) new_var) = arg0;
  new_var2 = 0; // fakematch: permuter temp, zero kept in a register
 *((s32 *) (((u8 *) temp_v0) + ((unsigned int) 0x18))) = new_var2; *((s32 *) (((u8 *) temp_v0) + 0x14)) = new_var2;
  *((s16 *) (((u8 *) temp_v0) + 0x1C)) = arg1;
  return temp_v0;
}

s32 func_1514F18C(void *arg0, struct127 *arg1, s16 arg2) {
    u8 *ret;
    u8 *node;
    struct_eu_link *next;
    s16 idx;

    ret = NULL;
    if (arg0 != NULL) {
        node = (u8 *)func_1514F114(arg0, arg2, 0);
        ret = node;
        if (node != NULL) {
            *(struct_eu_link **)(node + 0x14) = arg1->unk2F4;
            arg1->unk2F4 = (struct_eu_link *)node;
            next = *(struct_eu_link **)(node + 0x14);
            *(s32 *)(node + 0x18) = 0;
            if (next != NULL) {
                *(u8 **)((u8 *)next + 0x18) = node;
            }
        } else {
            idx = *(s16 *)(D_8008AF88[arg2] + 2);
            if (idx != -1) {
                D_8008AEF8[idx](arg0);
            } else {
                func_1516972C((struct102 *)arg0);
            }
        }
    }
    return (s32)ret;
}

s32 func_1514F250(struct_eu_link *arg0, s16 arg1, struct_eu_link **arg2) {
    s32 found = 0;
    struct_eu_link *n = arg0;
    struct_eu_link *next;

    while (n != NULL && found == 0) {
        next = n->unk14;
        if (arg1 == *(s16 *)((u8 *)n + 0x1C)) {
            found = 1;
        } else {
            n = next;
        }
    }
    if (arg2 != NULL) {
        *arg2 = n;
    }
    return found;
}

s32 func_1514F2AC(u8 *arg0, s32 arg1, u8 **arg2) {
    s32 found = 0;
    u8 *node = arg0;
    u8 *next;

    while (node != NULL && found == 0) {
        next = *(u8 **)(node + 0x14);
        if (arg1 == *(s32 *)(node + 0x10)) {
            found = 1;
        } else {
            node = next;
        }
    }
    if (arg2 != NULL) {
        *arg2 = node;
    }
    return found;
}

s32 func_1514F2FC(u8 *arg0, u8 *arg1) {
    s32 sp1C;
    if (arg0 == *(u8 **)(arg1 + 0x2F4)) {
        *(u8 **)(arg1 + 0x2F4) = *(u8 **)(arg0 + 0x14);
    }
    if (*(u8 **)(arg0 + 0x14) != NULL) {
        *(u8 **)(*(u8 **)(arg0 + 0x14) + 0x18) = *(u8 **)(arg0 + 0x18);
    }
    if (*(u8 **)(arg0 + 0x18) != NULL) {
        *(u8 **)(*(u8 **)(arg0 + 0x18) + 0x14) = *(u8 **)(arg0 + 0x14);
    }
    sp1C = *(s32 *)(arg0 + 0x10);
    func_1516972C(arg0);
    return sp1C;
}

void func_1514EDF0(s32 arg0, u8 *arg1) {
    s32 temp_v0;
    u8 *var_s1;
    u8 *sp34;
    u8 temp_s0;
    var_s1 = (*(u8 **)((u8 *)arg1 + 0x2F4));
    sp34 = NULL;
    do {
        temp_v0 = func_1514F2AC(var_s1, arg0, &sp34);
        temp_s0 = temp_v0;
        if (temp_v0 != 0) {
            var_s1 = (*(u8 **)((u8 *)sp34 + 0x14));
            func_1514F2FC(sp34, arg1);
        }
    } while (temp_s0 != 0);
}

void func_1514F3E0(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        s16 unk6;
    } sp20;

    sp20.unk0 = arg0;
    sp20.unk4 = arg0[0x3B];
    sp20.unk5 = 0;
    sp20.unk6 = 300;
    func_1514F18C(func_1515C3C0(&sp20, 0, 255, 1), arg0, 0x16);
}

#ifdef NON_MATCHING
// character_fire_effect_start: handler (table EU 8008AE80): adds a light at (0, 90, 0) on joint 1 of the object
// (func_15160A58: 300, 2, 255, 0, 0, 255, 0, 3, 0, 0, 255, 1) attached in slot 0x19 (func_1514F18C), then a sprite
// effect (func_1518A560) with render block kind 0x69 / 3 / 0x4403, size 95 / 65, fade 0.15 / 0.7 / 0.4, attached to
// joint 1 from (0, 70, 0) to (0, 120, 0) (mode 3).
void func_1514F43C(struct127 *obj) {
    static const f32 sLightPos[3] = { 0.0f, 90.0f, 0.0f };
    static const f32 sFrom[3] = { 0.0f, 70.0f, 0.0f };
    static const f32 sTo[3] = { 0.0f, 120.0f, 0.0f };
    struct {
        f32 from[3];
        f32 to[3];
        struct127 *obj;
        u8 joint;
        u8 id;
        u8 mode;
        u8 pad1F;
    } c;
    struct {
        f32 u00;
        f32 u04;
        f32 u08;
        f32 u0C;
        f32 u10;
        f32 u14;
        f32 u18;
        f32 u1C;
        f32 u20;
        u8 pad24[0x24];
        f32 u48;
        u8 pad4C[8];
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
    } b;
    struct {
        u8 u00;
        u8 u01;
        s16 u02;
        s16 u04;
        u8 pad06[2];
        s32 u08;
        s32 u0C;
        u8 u10;
        u8 u11;
        u8 u12;
        u8 u13;
        f32 u14;
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        s32 u40;
        u8 u44;
        u8 u45;
        u8 u46;
        u8 u47;
        s32 u48;
        u8 u4C;
        u8 pad4D[3];
        s32 u50;
        s16 u54;
        s16 u56;
    } a;

    func_1514F18C(func_15160A58(obj, 1, (s32 *)sLightPos, 2, 0x12C, 2, 0xFF, 0, 0, 0xFF, 0, 3, 0, 0, 0xFF, 1), obj,
                  0x19);
    a.u00 = 0x69;
    a.u40 = 0x4ED200A;
    a.u04 = 0x12C;
    a.u08 = 0;
    a.u0C = 0;
    a.u45 = 0xFF;
    a.u10 = 0xFF;
    a.u11 = 0;
    a.u12 = 0;
    a.u13 = 0xFF;
    a.u02 = 0x4403;
    a.u1C = 0.0f;
    a.u20 = 0.0f;
    a.u24 = 0.0f;
    a.u28 = 0.0f;
    a.u2C = 0.0f;
    a.u30 = 0.0f;
    a.u01 = 3;
    a.u18 = 100.0f;
    a.u14 = 100.0f;
    a.u34 = 1.0f;
    a.u38 = 1.0f;
    a.u3C = 1.0f;
    a.u44 = 0xFF;
    a.u46 = 0;
    a.u47 = 6;
    a.u48 = 0;
    a.u4C = 0xFF;
    a.u50 = 0;
    a.u54 = 1;
    a.u56 = 0xFF;
    b.u04 = 95.0f;
    b.u00 = 95.0f;
    b.u0C = 65.0f;
    b.u08 = 65.0f;
    b.u10 = 0.15f;
    b.u14 = 0.15f;
    b.u18 = 0.7f;
    b.u1C = 0.4f;
    b.u20 = 1e-06f;
    c.obj = obj;
    c.id = obj->unique_id;
    c.from[0] = sFrom[0];
    c.from[1] = sFrom[1];
    c.from[2] = sFrom[2];
    c.to[0] = sTo[0];
    c.to[1] = sTo[1];
    c.to[2] = sTo[2];
    c.joint = 1;
    b.u54 = 0;
    b.u55 = 0;
    b.u56 = 0;
    b.u57 = 0;
    b.u48 = 1.0f;
    c.mode = 3;
    func_1518A560(&a, &b, &c, 2, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F43C.s")
#endif

void func_1514F680(struct127 *arg0) {   /* P76: callback; a0 passes through */
    func_1514F704(arg0);
}

s32 func_1514F6A0(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0xD:
        (*(u8 **)(arg0 + 0x14))[9] = 0;
        break;
    case 0xE:
        (*(u8 **)(arg0 + 0x14))[9] = 1;
        break;
    default:
        return func_1514EE0C(arg0, arg1, arg2);
    }
    return 1;
}

extern u8 D_800A5D38[];
extern u8 D_800A5D44[];

int func_1514F704(struct127 *arg0) { // int: callers use the implicit declaration
    u8 *r;

    func_151D1510(arg0, 1, 0xFF, 1);
    func_151D1510(arg0, 2, 0xFF, 1);
    func_151BB5F4(arg0);
    if (D_800BE616 == 0) {
        func_151BC624(arg0);
    }
    func_151BD8A8(arg0, 0xFF, 1);
    func_151BA4B0(arg0, 0xFF, 1);
    func_15160A58(arg0, 1, (s32 *)D_800A5D38, 2, 0x12C, 0xC, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0, 0xFF, 1);
    r = func_15160A58(arg0, 1, (s32 *)D_800A5D44, 2, 0x12C, 0xF, 0xFF, 0, 0, 0xFF, 1, -1, 0, 0, 0xFF, 1);
    if (r != NULL) {
        func_1514F18C(r, arg0, 0x19);
    }
}

void func_1514F878(struct127 *arg0) {
    V3_1514F878 sp54;
    V3_1514F878 sp48;
    sp54 = D_800A5D50;
    sp48 = D_800A5D5C;
    func_15160CDC(arg0, 5, &sp54, &sp48, D_800A6238, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
}

void func_1514F93C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x3A, -1, 0, 0x2B, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_1514F9BC(struct127 *arg0) {
    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5D68), arg0, 0xD);
}

void func_1514FA18(s32 arg0) {
    func_151D7A60(arg0, 1, -1, 0xFF, 1);
}

void func_1514FA48(s32 arg0) {
    func_151D7A60(arg0, 2, 1, 0xFF, 1);
}

void func_1514FA78(s32 arg0) {
    func_151D7A60(arg0, 3, 0, 0xFF, 1);
}

void func_1514FAA8(s32 arg0) {
    func_151D7A60(arg0, 4, -1, 0xFF, 1);
}

void func_1514FAD8(s32 arg0) {
    func_150C4620(arg0, -1, 0xFF, 1);
}

void func_1514FB00(struct127 *arg0) {
    func_1501175C(arg0, 0xFF, 1);
    func_15011A78(arg0, 0xFF, 1);
}

typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ f32 u4;
    /* 0x08 */ s32 u8_;
    /* 0x0C */ u8 uC;
    /* 0x10 */ f32 u10;
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ u8 u18;
} BlkFB3C;

#ifdef NON_MATCHING
u8 *func_150C0FC0(BlkFB3C *arg0, s32 arg1, s32 arg2);
#else
void func_150C0FC0(BlkFB3C *arg0, s32 arg1, s32 arg2);
#endif

void func_1514FB3C(u8 *arg0) {
    BlkFB3C b;

    b.u0 = 0;
    b.u4 = 0.0f;
    b.u8_ = (s32)arg0;
    b.uC = arg0[0x3B];
    b.u10 = 0.35f;
    b.u14 = 20;
    b.u16 = 300;
    b.u18 = 4;
    func_150C0FC0(&b, 0xFF, 1);
}
