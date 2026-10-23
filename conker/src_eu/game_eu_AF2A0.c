#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern s32 D_8008704C;
void func_15036F60(u8 *arg0);
struct197 *allocate_memory(s32, s32, s32, s32);
void func_1505F188(struct127 *);
struct127 *func_1505ED34(void);
void func_150848F0(u8 *, s32, s32);
s32 func_151E6710(s32);
void func_15083E20(u8 *, u16, u8 *);
void func_15083C3C(s32, s32, s32);
s32 func_15083D54(struct127 *, u16, s32, f32);
s32 func_1503DD8C(struct127 *, s32, s32, s32);
void func_15083784(struct127 *, s32);
s32 func_15085118(s32);
s32 func_1514D6CC(struct127 *);
void func_15085098(u8 *);
extern s8 D_8008FD8C;
extern u8 *D_800D252C;
extern s8 D_800901E4[];
extern s8 D_800D2550;
extern u16 D_800D2132;
extern u8 D_800C67F0;
extern u8 D_80038080;
extern u8 D_800A7610[];
extern u8 D_800A7620[];
u8 func_15085170(u8 *arg0);
u8 *func_1502B020(s32 *arg0, s32 arg1, ...);
s32 func_15083F30(struct127 *, u8, u8, s32, s32, s32, s32, s32, f32);
struct127 *func_15030DE4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9, s32 argA, s32 argB, s32 argC);
extern s32 D_80087064;
#endif

typedef struct {
    /* 0x000 */ u8 pad0[0x1C9];
    /* 0x1C9 */ u8 unk1C9;
    /* 0x1CA */ u8 pad1CA[0xFA];
    /* 0x2C4 */ u8 *unk2C4;
    /* 0x2C8 */ u8 unk2C8;
} struct_eu_AF2A0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15081A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082020.s")

void func_1507DF10(u8 *, s32, u8);
void func_1508220C(u8 *arg0, u16 v, u8 arg2) {
    if (D_800BE616 == 0) {
        if (arg0[0x1CA] != 0) {
            arg0[0x1CA] = 7;
        }
        if (arg2 == 0 || v != 10) {
            func_1507DF10(arg0, v, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082278.s")

#ifdef NON_MATCHING
s32 func_15082E44(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);
s32 func_150A6840(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern s32 D_800DA030[];

/* P36: level-setup entry idx (0x30 bytes at D_800D20FC): spawn it with func_15082E44(e, idx, 0, 0, 0) and return
 * that, or return 0 when: already spawned (D_800D252C[idx] != 0); a placeholder (e[2] == 1); no position
 * (x == 0x7FFF); its respawn timer D_800D2530[idx] is running (lowered by D_800BE9A0 this frame); idx >= 5 with a
 * range class e[1] & 6 (2: 650, 4: 1300, else 2750 units) and no player object D_800CC2D0[0 .. D_8008FD8C)
 * (+0 != 0, +0x127 != 0xFF and enabled in the u16 mask at D_800D2138 + 0x208) within that XZ distance; or
 * e[1] & 8 and the spot (x, y + 150, z), radius 150, is in view of one of the cameras 0 .. D_80082FA0
 * (func_150A6840 on D_800BE628 + i * 0x180, D_800DA030 + i * 0x10). Player slots (idx < 5) skip the range test.
 * arg1 is unused. */
s32 func_150829C0(s32 idx, s32 arg1) {
    u8 *e;
    u16 *timer;
    u8 *obj;
    u8 *end;
    s32 x, flags, cls, n, ok, i, b;
    f32 r2, dx, dz;

    if (D_800D252C[idx] != 0) {
        return 0;
    }
    e = (u8 *) D_800D20FC + idx * 0x30;
    if (e[2] == 1) {
        return 0;
    }
    x = *(s16 *) (e + 6);
    if (x == 0x7FFF) {
        return 0;
    }
    timer = (u16 *) D_800D2530 + idx;
    if (*timer != 0) {
        if (D_800BE9A0 < *timer) {
            *timer = *timer - D_800BE9A0;
        } else {
            *timer = 0;
        }
        return 0;
    }
    flags = e[1];
    if (idx >= 5 && (cls = flags & 6) != 0) {
        if (cls == 2) {
            r2 = 422500.0f;
        } else if (cls == 4) {
            r2 = 1690000.0f;
        } else {
            r2 = 7562500.0f;
        }
        n = D_8008FD8C;
        ok = 1;
        if (n > 0) {
            obj = (u8 *) D_800CC2D0;
            end = (u8 *) D_800CC2D0 + n * 0x32C;
            do {
                if (*(s32 *) obj != 0) {
                    b = obj[0x127];
                    if (b != 0xFF && ((1 << b) & *(u16 *) ((u8 *) &D_800D2138 + 0x208))) {
                        dx = *(f32 *) (obj + 0x14) - (f32) x;
                        dz = *(f32 *) (obj + 0x1C) - (f32) *(s16 *) (e + 0xA);
                        if (dx * dx + dz * dz <= r2) {
                            ok = 0;
                            break;
                        }
                    }
                }
                obj += 0x32C;
            } while ((u32) obj < (u32) end);
        }
        if (ok) {
            return 0;
        }
    }
    if (flags & 8) {
        ok = 1;
        for (i = 0; i <= D_80082FA0; i++) {
            e = (u8 *) D_800D20FC + idx * 0x30;
            if (func_150A6840(D_800BE628 + i * 0x180, D_800DA030 + i * 0x10, (f32) *(s16 *) (e + 6),
                              (f32) (*(s16 *) (e + 8) + 150), (f32) *(s16 *) (e + 0xA), 150.0f, 150.0f, 20000.0f) != 0) {
                ok = 0;
            }
        }
        if (!ok) {
            return 0;
        }
    }
    return func_15082E44((u8 *) D_800D20FC + idx * 0x30, idx, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150829C0.s")
#endif

s32 func_150829C0(s32, s32);
extern u8 D_800D2520;
extern u8 D_800D2521;
void func_15082D5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 lo;
    s32 hi;
    s32 i;
    if (arg2 != 0) {
        lo = 0;
        hi = D_800D2521;
    } else {
        lo = D_800D2521;
        hi = D_800D2520;
    }
    i = lo;
    if (lo < hi) {
        do {
            func_150829C0(i, arg1);
            i += 1;
        } while (i != hi);
    }
}

void func_15082DD8(u8 *arg0) {
    u8 *temp_v0;

    *(s32 *)(arg0 + 0xF8) &= 0xF7FFFFFD;
    temp_v0 = *(u8 **)(arg0 + 0x31C);
    *(s32 *)(arg0 + 0xF8) |= 4;
    if ((temp_v0 != NULL) && (temp_v0[0x56] == 0)) {
        switch (D_800BE9F0) {
        case 0x0:
        case 0xA:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x19:
        case 0x1B:
        case 0x2C:
        case 0x3C:
        case 0x3D:
        case 0x42:
        case 0x43:
        case 0x44:
            break;
        default:
            *(s32 *)(arg0 + 0xF8) |= 2;
            break;
        }
    }
}

#ifdef NON_MATCHING
/* Spawns the level-setup object e (0x30-byte entry of D_800D20FC) into an object slot of D_800CC2D0 (0x32C each):
 * slot = reuse+reset (func_1505F188) of slot reuse - 1 when reuse != 0, of slot idx when idx < D_8008FD8C (the
 * player / character slots), else a new one (func_1505ED34). Returns slot + 1, or 0 when D_800D252C[idx] & 0x7F
 * (already spawned) or no slot is free (25). Fills position (+0x14.., from e+6/8/A), angle (e+0xC << 8), the setup
 * flags e+0x18 (+0xF8), model / type (e+4) via func_15083E20 / func_15083C3C / func_15083D54, the player record
 * (+0x31C, 0x1C0 bytes) for character slots and types 0x98 / 0x28, and the other per-type defaults. */
#define O8(o) (*(u8 *)(obj + (o)))
#define O16(o) (*(s16 *)(obj + (o)))
#define O32(o) (*(s32 *)(obj + (o)))
#define OF(o) (*(f32 *)(obj + (o)))
#define REC(o) (*(u8 *)(*(u8 **)(obj + 0x31C) + (o)))
s32 func_15082E44(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse) {
    u8 *obj;
    s32 type;
    s32 slot;
    s32 flags;
    s32 v;
    s32 n;
    s32 i;
    u8 *p;
    u8 *t;
    s32 found;
    void func_150836AC();
    u8 func_15084E08(struct_eu_AF2A0 *);

    if (D_800D252C[idx] & ~0x80) {
        return 0;
    }
    type = e[4];
    if (reuse != 0) {
        obj = (u8 *)D_800CC2D0 + reuse * 0x32C - 0x32C;
        func_1505F188((struct127 *)obj);
    } else if (idx != -1 && idx < D_8008FD8C) {
        obj = (u8 *)D_800CC2D0 + idx * 0x32C;
        func_1505F188((struct127 *)obj);
    } else {
        obj = (u8 *)func_1505ED34();
    }
    slot = (s32)(obj - (u8 *)D_800CC2D0) / 0x32C;
    if (slot == 0x19) {
        return 0;
    }
    if (idx != -1) {
        if (*(u16 *)e & 0x21) {
            D_800D252C[idx] = slot + 1;
        } else {
            D_800D252C[idx] = slot + 0x81;
        }
        O8(0x13F) = idx;
        if (idx < D_8008FD8C) {
            O8(0x127) = idx;
        } else {
            O8(0x127) = 0xFF;
        }
    }
    *(u8 **)(obj + 0x144) = e;
    func_150848F0(e, O8(0x13F), arg3);
    if (slot < D_8008FD8C || type == 0x98 || type == 0x28) {
        *(struct197 **)(obj + 0x31C) = allocate_memory(0x1C0, 1, 0, 0);
        bzero(*(void **)(obj + 0x31C), 0x1C0);
        *(f32 *)(*(u8 **)(obj + 0x31C) + 0x1B8) = 5.0f;
    }
    O8(0x1D0) = 2;
    O8(0x3B) = e[0x28];
    OF(0x14C) = *(f32 *)(e + 0x20);
    OF(0x150) = *(f32 *)(e + 0x24);
    OF(0x154) = *(f32 *)(e + 0x20);
    OF(0x158) = *(f32 *)(e + 0x24);
    O32(0x0) = e[3];
    OF(0x14) = *(s16 *)(e + 6);
    OF(0x18) = *(s16 *)(e + 8);
    O8(0x212) = 0xFF;
    O8(0x20F) = 0xFF;
    O8(0x210) = 0xFF;
    O8(0x211) = 0xFF;
    O8(0x128) = 0xFF;
    OF(0x2C) = OF(0x14);
    OF(0x30) = OF(0x18);
    OF(0x1CC) = OF(0x18);
    OF(0x1C) = *(s16 *)(e + 0xA);
    OF(0x34) = OF(0x1C);
    if (*(u16 *)e & 6) {
        func_1506160C((struct127 *)obj, 4, 0, 0, 0);
    }
    O8(0x232) = e[0xD];
    if (idx < D_8008FD8C && D_800901E4[idx] == -2) {
        REC(0x84) = 1;
        O8(0x232) = 1;
    }
    if (O8(0x127) != 0xFF) {
        O8(0x128) = func_151E6710(O8(0x127));
        REC(0x19A) = D_800D2550;
        REC(0x1AF) = 0x40;
        REC(0x1B0) = 0xFF;
    }
    O8(0x1CA) = e[0xE] & 0xF;
    O8(0x221) = 1;
    O8(0x1E5) = e[0xF];
    O8(0x1E6) = e[0xF];
    O8(0x23C) = e[0x1C];
    O8(0x23D) = e[0x1D];
    v = e[0xC] << 8;
    O16(0x76) = v;
    O16(0x7A) = v & 0xFFFF;
    O16(0x78) = v & 0xFFFF;
    OF(0x40) = (f32)((v & 0xFFFF) + 0x4000) * 0.0054931640625f;
    OF(0x24) = 6.0f;
    O8(0x140) = arg2;
    flags = *(s32 *)(e + 0x18);
    O32(0xF8) = flags;
    if (flags & 0x200000) {
        O16(0x224) = (s32)OF(0x18);
    }
    if (flags & 0x10000000) {
        O16(0x38) = (s32)(OF(0x18) - 500.0f);
    }
    if (flags & 0x800000) {
        D_800C67F0 = 1;
    }
    O8(0x1E4) = e[0x11];
    O8(0x1DD) = 0x78;
    O8(0x1DE) = 0x78;
    O8(0x1DF) = 0x78;
    O8(0x1E0) = 0xFF;
    O8(0x1E1) = 0xFF;
    O8(0x1E2) = 0xFF;
    O8(0x23E) = 4;
    O8(0x246) = 1;
    O8(0x247) = 0x64;
    O8(0x248) = 0x64;
    O8(0x1FC) |= 2;
    O8(0x66) = e[0x10];
    func_15083E20(obj, type, e);
    O16(0x92) = ((e[0x13] & 0x80) << 8) | (e[0x13] & 0x7F);
    O16(0x90) = *(s16 *)(e + 0x14);
    func_15083C3C(slot, type, 1);
    if (type != 0xFF) {
        func_15083D54((struct127 *)obj, 0, 0, 1.0f);
    } else {
        O8(5) = 3;
    }
    if (O32(0xF8) & 0x4000) {
        func_1503DD8C((struct127 *)obj, O8(4), 0, 0);
    }
    if (e[0x29] != 0) {
        func_15083568((struct127 *)obj, e[0x29], 1.0f, 0);
    }
    if (O8(0x127) != 0xFF) {
        O8(0x1CA) = func_150859AC((s16)O8(0x127), 4);
        O16(0xB2) = (s16)D_800D2132;
        func_15082DD8(obj);
        func_15083784((struct127 *)obj, func_150859AC((s16)slot, 1));
    }
    if ((O8(0x66) & 0xC) == 8 || (O8(0x66) & 0xC) == 0xC) {
        func_150836AC(obj);
    } else {
        O32(0x314) = 0;
    }
    O8(0x288) = func_15085118(type);
    if (D_800BE616 != 0) {
        v = func_151E6710(O8(0x127));
        if (v >= 4) {
            v = 3;
        }
        if (type == 0x3B) {
            O8(0x68) = v + 1;
        } else if (type == 0x77) {
            O8(0x68) = v + 0x10;
        }
    }
    if (D_80038080 == 0 && D_800BE9F0 != 0x1D && e[0x2E] == 0xFF) {
        n = O8(0x2C9);
        if (n == 0) {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            ((u8 *)D_800D2040)[(*(u8 **)(obj + 0x2C4))[i]] = 0xFF;
        }
    }
    if (D_800BE9F0 == 0x1D) {
        O8(0x66) &= 0xDF;
    }
    func_1514D6CC((struct127 *)obj);
    v = func_15084E08((struct_eu_AF2A0 *)obj);
    found = 0;
    for (t = D_800A7610; t != D_800A7620; t += 8) {
        if (v == t[0]) {
            found = 1;
            break;
        }
    }
    if (found) {
        p = (u8 *)allocate_memory(0xC, 1, 0, 2);
        *(u8 **)(obj + 0x260) = p;
        if (p != NULL) {
            p[8] = 0;
            p[9] = 0xFF;
            *(f32 *)(p + 0) = 0.0f;
            *(f32 *)(p + 4) = 1.0f;
        }
    }
    func_15085098(obj);
    return slot + 1;
}
#undef O8
#undef O16
#undef O32
#undef OF
#undef REC
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15082E44.s")
#endif
typedef struct {
    u8 pad0[0x127];
    u8 unk127;
    u8 pad128[0x1C];
    u8 *unk144;
    u8 pad148[0x1B8];
    u8 unk300;
    u8 unk301;
    u8 pad302[2];
    s32 unk304[4];
    s32 unk314;
} S836AC;
s32 func_1515D9F0(s32);
s32 func_1515D9B0(void);
void func_150836AC(S836AC *arg0)
{
    s32 i;
    s32 sel;
    u8 tmp;

    if (arg0->unk144 != NULL) {
        tmp = arg0->unk144[0x2F];
        if (tmp == 0) { if (arg0->unk127 == 0) sel = 5; else sel = 3; } else { sel = tmp; }
        for (i = 0; i <= D_80082FA0; i++) {
            arg0->unk304[i] = func_1515D9F0(sel);
        }
        if (arg0->unk304[i - 1] != 0) {
            arg0->unk301 = sel;
        }
        arg0->unk314 = func_1515D9B0();
    }
}

#ifdef NON_MATCHING
void func_15083784(struct127 *arg0, s32 arg1) {
    s32 sp1C;
    s32 temp_t5;
    s32 temp_v0_2;
    s32 temp_v1;
    struct126 *temp_v0;

    sp1C = -1;
    switch (arg1) {
    case 37:
    case 38:
        temp_v0 = arg0->unk31C;
        if (temp_v0 != NULL) {
            (*(s8 *)((u8 *)temp_v0 + 0x1B2)) = 1;
        }
        break;
    case 9:
        arg0->unk94 |= 2;
        break;
    case 13:
        sp1C = 0x76;
        break;
    case 14:
        sp1C = 0x78;
        break;
    case 15:
        sp1C = 0x77;
        arg0->unk94 |= 2;
        break;
    case 29:
    case 30:
    case 31:
    case 32:
        temp_v1 = arg1 - 0x1D;
        arg0->unk94 = 0x1E;
        if (temp_v1 < 2) {
            arg0->unk94 = 0x1E & ~0x14;
        } else {
            arg0->unk94 &= ~8;
        }
        if ((temp_v1 >> 1) != 0) {
            arg0->unk94 &= ~2;
        }
        break;
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
        temp_t5 = (s32) (arg1 - 0x11) >> 2;
        arg0->unk94 = 0x3E;
        switch (temp_t5) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            arg0->unk94 &= ~4;
            break;
        case 1:                                     /* switch 1 */
            arg0->unk94 &= ~8;
            break;
        case 2:                                     /* switch 1 */
            arg0->unk94 &= ~0x10;
            break;
        }
        temp_v0_2 = (arg1 - (temp_t5 * 4)) - 0x11;
        switch (temp_v0_2) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            arg0->unk94 &= ~2;
            break;
        case 2:                                     /* switch 2 */
            arg0->unk94 &= ~0x20;
            break;
        case 3:                                     /* switch 2 */
            arg0->unk94 &= ~0x22;
            break;
        }
        break;
    }
    if (sp1C != -1) {
        func_15083568(arg0, sp1C, 0.0f, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083784.s")
#endif
#ifdef NON_MATCHING
/* P36: run the setup command list D_80087064[arg1 - 1] ({list, count} of 0x10-byte commands) on obj: type 0 ->
 * func_15083F30, else func_15030DE4 (attachment spawn; arg10 = cmd[6] for type 2, else -1). Returns the last result. */

s32 func_15083568(struct127 *arg0, s32 arg1, f32 arg2, s32 arg3) {
    s32 temp_s4;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    u8 temp_v0;
    s32 var_v0_2;
    u8 *temp_s5;
    u8 *var_s0;

    temp_s4 = arg1 - 1;
    temp_s5 = ((s32 *)((u8 *)&D_80087064 + (temp_s4 * 8)));
    var_v1 = 0;
    var_s1 = 0;
    if ((s32) (*(u8 *)((u8 *)temp_s5 + 4)) > 0) {
        var_s0 = (*(u8 **)((u8 *)temp_s5 + 0));
        do {
            temp_v0 = (*(u8 *)((u8 *)var_s0 + 3));
            if (temp_v0 == 0) {
                var_v0 = func_15083F30(arg0, (*(u8 *)((u8 *)var_s0 + 1)), (*(u8 *)((u8 *)var_s0 + 0)), 0, (s32) (*(u8 *)((u8 *)var_s0 + 2)), (s32) (*(u8 *)((u8 *)var_s0 + 4)), (s32) (*(u8 *)((u8 *)var_s0 + 5)), (s32) (*(u8 *)((u8 *)var_s0 + 6)), arg2);
            } else {
                if (temp_v0 == 2) {
                    var_v0_2 = (*(u8 *)((u8 *)var_s0 + 6));
                } else {
                    var_v0_2 = -1;
                }
                var_v0 = (s32) func_15030DE4((u8 *) arg0, (*(u8 *)((u8 *)var_s0 + 0)), (*(u8 *)((u8 *)var_s0 + 1)), (*(u8 *)((u8 *)var_s0 + 7)), (s32) (*(u8 *)((u8 *)var_s0 + 4)), (s32) (*(u8 *)((u8 *)var_s0 + 5)), arg3, temp_s4 + 1, (s32) (*(u8 *)((u8 *)var_s0 + 2)), var_s0 + 8, (s32) var_v0_2, (s32) (*(u8 *)((u8 *)var_s0 + 0xE)), (s32) (*(u8 *)((u8 *)var_s0 + 0xF)));
            }
            var_v1 = var_v0;
            var_s1 += 1;
            var_s0 += 0x10;
        } while (var_s1 < (s32) (*(u8 *)((u8 *)temp_s5 + 4)));
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083568.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150836CC.s")

#ifdef NON_MATCHING
/* P36: set object slot's type (+4). 0xFF (no type): clears +0xE4/E6/E8, +0xD2 = +0xD4 = 0x46, +0xD6, +0x160, +0xC8 = 0.
 * Else +0xC8 = type record D_800D1C90[type]->+6 (s16), func_15062BDC(obj, +0x14C, +0x150), +5 = record +0x12.
 * Then +6 = func_15085170(obj) (model id); +0x58 = func_1502B020(0, 2, 2, id) when D_800C5A90[id] != 0. arg2 unused. */
void func_15083C3C(s32 slot, s32 type, s32 arg2) {
    u8 *obj = (u8 *) D_800CC2D0 + slot * 0x32C;
    u8 *rec;
    u8 id;

    obj[4] = type;
    if (type == 0xFF) {
        *(s16 *) (obj + 0xE4) = 0;
        *(s16 *) (obj + 0xE6) = 0;
        *(s16 *) (obj + 0xE8) = 0;
        *(s16 *) (obj + 0xD2) = 0x46;
        *(s16 *) (obj + 0xD4) = 0x46;
        *(s16 *) (obj + 0xD6) = 0;
        *(s16 *) (obj + 0x160) = 0;
        *(f32 *) (obj + 0xC8) = 0.0f;
    } else {
        rec = (u8 *) D_800D1C90[type];
        *(f32 *) (obj + 0xC8) = (f32) *(s16 *) (rec + 6);
        func_15062BDC((struct127 *) obj, *(f32 *) (obj + 0x14C), *(f32 *) (obj + 0x150));
        obj[5] = ((u8 *) D_800D1C90[type])[0x12];
    }
    id = func_15085170(obj);
    obj[6] = id;
    if ((u16) D_800C5A90[id] != 0) {
        *(u8 **) (obj + 0x58) = func_1502B020(0, 2, 2, id);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083C3C.s")
#endif
#ifdef NON_MATCHING
struct197 *allocate_memory(s32, s32, s32, s32);

s32 func_15083D54(struct127 *arg0, u16 arg1, s32 arg2, f32 arg3) {
    struct197 *temp_v0_2;
    u8 temp_v0;

    temp_v0 = arg0->id;
    if (D_800D1588[temp_v0] == 0) {
        goto block_7;
    }
    if ((u16) D_800C5A90[temp_v0] == 0) {
        goto block_7;
    }
    temp_v0_2 = allocate_memory(0x3E0, 1, 2, 0);
    arg0->unk2D0 = temp_v0_2;
    if (temp_v0_2 == NULL) {
        return 1;
    }
    bzero(arg0->unk2D0, 0x40);
    func_1505E650(arg0, arg1, arg3, 0.0f, 0.0f, 0.0f, arg2);
block_7:
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083D54.s")
#endif
#ifdef NON_MATCHING
/* Copy an object's per-type parameters from its type record D_800D1C90[type] (P15, hand C). */
void func_15083E20(u8 *arg0, u16 type, u8 *arg2) {
    u8 *t;

    if (type == 0xFF) {
        return;
    }
    t = (u8 *)D_800D1C90[type];
    if (arg2 != NULL) {
        u16 v = *(u16 *)(arg2 + 0x2C);

        if (v == 0) {
            *(u16 *)(arg0 + 0x10) = *(u16 *)(t + 0x2A);
        } else if (v == 1) {
            *(u16 *)(arg0 + 0x10) = 0;
        } else {
            *(u16 *)(arg0 + 0x10) = v;
        }
        if (D_800BE9F0 == 0x1D) {
            *(u16 *)(arg0 + 0x10) = 1000;
        }
    } else {
        *(u16 *)(arg0 + 0x10) = 0;
    }
    arg0[0x13B] = t[0x39];
    *(s8 *)(arg0 + 0x2CB) = *(s8 *)(t + 0x33);
    *(s32 *)(arg0 + 0x2CC) = *(s32 *)(t + 0x34);
    arg0[5] = t[0x12];
    arg0[0x68] = t[0x3B];
    arg0[0x69] = t[0x3C];
    *(s16 *)(arg0 + 0x160) = *(s16 *)(t + 2);
    if (t[4] != 0) {
        *(s32 *)(arg0 + 0x2C4) = (&D_8008704C)[t[5]];
        arg0[0x2C8] = t[4];
    }
    arg0[0x2C9] = arg0[0x2C8] + t[0x38];
    if (t[0x29] != 0) {
        func_15036F60(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E20.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083F30.s")

s32 func_15084208(void) {
    s32 id;
    s32 i;
    id = 1;
    i = 0;
    if (D_800D2520 > 0) {
        do {
            if (id == *((u8 *)D_800D20FC + i * 0x30 + 0x28)) {
                id++;
                i = 0;
            }
            i++;
        } while (i < D_800D2520);
    }
    if (id >= 0x100) {
        id = 0xFF;
    }
    return id;
}

#ifdef NON_MATCHING
/* P95: index of the level-setup entry (0x30 bytes at D_800D20FC, D_800D2520 of them) whose byte +0x28 is `id`;
 * -1 when id is 0 or not found. */
s32 func_15083E0C(u8 id) {
    s32 i;

    if (id == 0) {
        return -1;
    }
    for (i = 0; i < D_800D2520; i++) {
        if (((u8 *) D_800D20FC + i * 0x30)[0x28] == id) {
            return i;
        }
    }
    return -1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E0C.s")
#endif

#ifdef NON_MATCHING
extern u8 D_800CC72B;
extern struct127 D_800CCA1C;

struct127 *func_15083E90(u8 arg0) {
    s32 temp_t6;
    s32 var_a0;
    struct127 *temp_v1;
    struct127 *temp_v1_2;
    struct127 *temp_v1_3;
    struct127 *var_v1;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return NULL;
    }
    if ((D_800CC2D0->interaction_state != 0) && (temp_t6 == D_800CC72B)) {
        return D_800CC2D0;
    }
    var_a0 = 2;
    if ((D_800CCA1C.interaction_state != 0) && (temp_t6 == D_800CCA1C.unique_id)) {
        return &D_800CCA1C;
    }
    var_v1 = ((struct127 *)((u8 *)&D_800CCA1C + 0x32C));
loop_9:
    if ((var_v1->interaction_state != 0) && (temp_t6 == var_v1->unique_id)) {
        return var_v1;
    }
    temp_v1_3 = ((struct127 *)((u8 *)var_v1 + 0x32C));
    if ((var_v1[1].interaction_state != 0) && (temp_t6 == temp_v1_3->unique_id)) {
        return temp_v1_3;
    }
    temp_v1_2 = ((struct127 *)((u8 *)temp_v1_3 + 0x32C));
    if ((temp_v1_3[1].interaction_state != 0) && (temp_t6 == temp_v1_2->unique_id)) {
        return temp_v1_2;
    }
    temp_v1 = ((struct127 *)((u8 *)temp_v1_2 + 0x32C));
    var_a0 += 4;
    if ((temp_v1_2[1].interaction_state != 0) && (temp_t6 == temp_v1->unique_id)) {
        return temp_v1;
    }
    var_v1 = ((struct127 *)((u8 *)temp_v1 + 0x32C));
    if (var_a0 == 0x1A) {
        return NULL;
    }
    goto loop_9;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15083E90.s")
#endif
s32 func_15083FB0(u8 arg0) {
    struct127 *p = func_15083E90(arg0);

    if (p != NULL) {
        return p - D_800CC2D0;
    }
    return -1;
}

#ifdef NON_MATCHING
/* P73: one argument under NM (wasm needs one signature; every caller passes only the object id, the asm
 * forwards its unused a1..a3 to func_1505EEF4) */
s32 func_15084000(s32 id) {
    struct127 *obj = func_1505EEF4(id);

    if (obj != NULL) {
        return obj - D_800CC2D0;
    }
    return -1;
}
#else
/* P80: one argument (func_1505EEF4 reads only the id); the callers in game_CB1C0.c pass one */
s32 func_15084000(s32 arg0) {
    struct127 *temp_v0 = func_1505EEF4(arg0);

    if (temp_v0 != NULL) {
        return temp_v0 - D_800CC2D0;
    }
    return -1;
}
#endif

#ifdef NON_MATCHING
extern u16 D_800C5BC0[]; /* vertex block size of each model slot, in 16-byte vertices */
void func_10004074(void *);

/*
 * P62: vertex blocks of object o for variant var: the two frame words o +0x28C + var * 8 (+0 / +4) that
 * func_1502CFEC draws from. The model slot is ((u8 *)o +0x2C4)[var]; its shared block is D_800D19A0[slot] with the
 * user count D_800D1F80[slot]. The sharing mode is (rec +0x10) & 3, rec being the record +0x144 of the parent object
 * o[0x65] - 1 (or o's own when o[0x65] is 0); no record: mode 0; slot 0: mode 2.
 *   both words set, or no shared block: nothing (0);
 *   mode 0: both words share the block (count += 2);
 *   mode 1: word 0 (if 0 or the shared block): the first user shares it (count += 2), later users get a private copy;
 *           then word 1 = word 0;
 *   mode 2: each word that is 0 or the shared block (word 1 also when the two are equal): shared if the count is 0
 *           (count += 1), else a private copy; an allocation failure stops there and, on word 1, gives word 0 back
 *           (free its copy or count -= 1) and clears it;
 *   mode 3: nothing.
 * Returns 1 when an allocation failed, else 0.
 */
s32 func_150844AC(struct127 *o, s32 var) {
    u8 *obj = (u8 *)o;
    u32 *words = (u32 *)(obj + 0x28C + var * 8);
    u8 *rec;
    s32 slot;
    s32 mode;
    u32 *shared;
    u8 *count;
    s32 size;
    s32 failed;
    s32 w;

    if (obj[0x65] != 0) {
        rec = *(u8 **)((u8 *)&D_800CC2D0[obj[0x65] - 1] + 0x144);
    } else {
        rec = *(u8 **)(obj + 0x144);
    }
    slot = (*(u8 **)(obj + 0x2C4))[var];
    mode = 0;
    if (rec != NULL) {
        mode = rec[0x10] & 3;
    }
    if (slot == 0) {
        mode = 2;
    }
    shared = (u32 *)&D_800D19A0 + slot;
    if (words[0] != 0 && words[1] != 0) {
        return 0;
    }
    if (*shared == 0) {
        return 0;
    }
    failed = 0;
    count = (u8 *)D_800D1F80 + slot;

    if (mode == 0) {
        words[1] = *shared;
        words[0] = *shared;
        *count += 2;
    } else if (mode == 1) {
        if (words[0] == 0 || words[0] == *shared) {
            if (*count != 0) {
                size = D_800C5BC0[slot] * 16;
                words[0] = (u32)allocate_memory(size, 1, 2, 2);
                if (words[0] == 0) {
                    failed = 1;
                } else if (words[0] != 0) {
                    bcopy((void *)*shared, (void *)words[0], size);
                } else {
                    words[0] = *shared; /* not reached (the asm has it) */
                }
            } else {
                words[1] = *shared;
                words[0] = *shared;
                *count += 2;
            }
        }
        words[1] = words[0];
    } else if (mode == 2) {
        for (w = 0; w < 2; w++) {
            if (!(words[w] == 0 || words[w] == *shared || (w == 1 && words[0] == words[1]))) {
                continue;
            }
            if (*count != 0) {
                size = D_800C5BC0[slot] * 16;
                words[w] = (u32)allocate_memory(size, 1, 2, 2);
                if (words[w] == 0) {
                    failed = 1;
                    if (w == 1) {
                        if (words[0] != *shared) {
                            func_10004074((void *)words[0]);
                        } else {
                            *count -= 1;
                        }
                        words[0] = 0;
                    }
                    break;
                }
                if (words[w] != 0) {
                    bcopy((void *)*shared, (void *)words[w], size);
                } else {
                    words[w] = *shared; /* not reached (the asm has it) */
                }
            } else {
                words[w] = *shared;
                *count += 1;
            }
        }
    }
    return failed;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150844AC.s")
#endif

void func_15084814(struct127 *, s32);

void func_150847B4(u8 *arg0) {
    s32 var_s0;
    u8 var_s1;

    var_s1 = (*(u8 *)((u8 *)arg0 + 0x2C9));
    if (var_s1 == 0) {
        var_s1 = 1;
    }
    var_s0 = 0;
    if ((s32) var_s1 > 0) {
        do {
            func_15084814(arg0, var_s0);
            var_s0 += 1;
        } while (var_s0 != var_s1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084814.s")

s32 func_1503D950(s32, s32);
s32 func_1503DA64(s32, s32);
extern s32 D_8008704C;

void func_150848F0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s1;
    struct124 *temp_v0;
    u8 *var_s0;
    u8 *var_v1;
    u8 temp_s0;
    s32 var_s2;

    temp_s0 = arg0[4];
    if (temp_s0 != 0xFF) {
        func_1503DA64(temp_s0, arg2);
        temp_v0 = D_800D1C90[temp_s0];
        var_v1 = arg0 + 4;
        var_s2 = temp_v0->unk4;
        if (var_s2 == 0) {
            var_s2 = 1;
        } else {
            var_v1 = *(u8 **)(&D_8008704C + (u8) temp_v0->unk5);
        }
        var_s1 = 0;
        var_s0 = var_v1;
        var_s2 += *(u8 *)((u8 *)temp_v0 + 0x38);
        if (var_s2 > 0) {
            do {
                func_1503DA64(*var_s0, arg2);
                func_1503D950(*var_s0, arg2);
                var_s1 += 1;
                var_s0 += 1;
            } while (var_s1 != var_s2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_150849C0.s")

u8 func_15084E08(struct_eu_AF2A0 *arg0) {
    s32 temp_v1 = arg0->unk1C9;

    if (temp_v1 != 0) {
        return arg0->unk2C4[temp_v1 - 1];
    }
    return arg0->unk2C4[0];
}

u8 func_15084E34(struct_eu_AF2A0 *arg0, s32 *arg1) {
    s32 temp_v1;

    if (arg0->unk1C9 != 0) {
        temp_v1 = arg0->unk1C9 - 1;
    } else {
        temp_v1 = (arg0->unk2C8 != 0) ? arg0->unk2C8 - 1 : 0;
    }
    if (arg1 != NULL) {
        *arg1 = temp_v1;
    }
    return arg0->unk2C4[temp_v1];
}

#ifdef NON_MATCHING
/* Per-frame countdown of the 187 resource slots (P15, hand C from the asm). D_800D2040 holds one
 * byte timer per slot (0 = idle, 0xFF = pinned). When a timer reaches 1 and the slot owns a block
 * (D_800D19A0[i]) that is not locked (D_800C5C08[i] == 0), the block is released: object references to
 * it (struct127 words 0x28C.., two per entry, unk2C9 entries) are cleared, objects whose entry list
 * (unk2C4) names slot i are notified through func_15084814, the slot's 12-byte records
 * (D_800C5758[i], D_800C5A48[i] of them) free their texture through func_1510DCA0, then the block
 * (minus its 0x38-byte header) goes back to the allocator. */
void func_1510DCA0(s32);
extern u16 D_800C5A48[];         /* record count per slot */
extern u8 *D_800C5758[];         /* 12-byte records per slot */
void func_15084E80(void) {
    u8 *timers = (u8 *)D_800D2040;
    s32 *blocks = &D_800D19A0;
    u16 *counts = D_800C5A48;
    u8 **records = D_800C5758;
    s32 i;

    for (i = 0; i != 187; i++) {
        u8 t = timers[i];

        if (t == 0xFF || t == 0) {
            continue;
        }
        if (t == 1 && blocks[i] != 0 && D_800C5C08[i] == 0) {
            struct127 *obj;
            u8 *rec;
            s32 j;

            for (obj = D_800CC2D0; (u32)obj < (u32)&D_800D121C; obj++) {
                if (obj->interaction_state == 0) {
                    continue;
                }
                for (j = 0; j < obj->unk2C9; j++) {
                    s32 *ref = &obj->unk28C + j * 2;

                    if (ref[0] == blocks[i]) {
                        ref[0] = 0;
                    }
                    if (ref[1] == blocks[i]) {
                        ref[1] = 0;
                    }
                    if (((u8 *)obj->unk2C4)[j] == i) {
                        func_15084814(obj, j);
                    }
                }
            }
            rec = records[i];
            for (j = 0; j < counts[i]; j++, rec += 0xC) {
                if (*(u32 *)rec >= 0x10000000U) {
                    func_1510DCA0(*(s32 *)(rec + 4));
                }
            }
            func_10004074(blocks[i] - 0x38);
            ((u8 *)D_800D1F80)[i] = 0;
            blocks[i] = 0;
            t = timers[i];
        }
        timers[i] = t - 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AF2A0/func_15084E80.s")
#endif
void func_15085098(u8 *arg0) {
    u8 *p;
    f32 r;
    if (arg0[4] == 0x94) {
        p = *(u8 **)(arg0 + 0x2D0);
        r = (f32)((u32)func_150ADA20() % (u32)(s32)*(f32 *)(p + 0x18));
        *(f32 *)(p + 8) = r;
    }
}

extern u8 D_800BE9B0;
extern u16 D_800BE9B8[];
s32 func_15085118(s32 arg0) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < D_800BE9B0; i++) {
        if (arg0 == D_800BE9B8[i]) {
            ret = i;
            break;
        }
    }
    return ret;
}
