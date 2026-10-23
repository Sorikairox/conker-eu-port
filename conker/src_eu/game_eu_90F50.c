#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15063A54(struct127 *);


s16 func_15063740(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[(*(u8 *)((u8 *)arg0 + 0x222))];
    return func_1505A630(temp_v0->x_position - (*(f32 *)((u8 *)arg0 + 0x14)), (*(f32 *)((u8 *)arg0 + 0x1C)) - temp_v0->z_position, 0);
}

#ifdef NON_MATCHING
/*
 * obj_knockdown_start: for object record rec (D_800CC2D0, 0x32C bytes): its state block (+0x31C) gets +0x78 = 9,
 * animations 0x1D then 0x1E at speed 1 (func_15083568), rec +0x8A = 20, +0x89 = +0x83 = 0, the block's +0x24 timer
 * = 60 and +0x11A = 2, then func_1505E650(rec, 0x7F, 1.0, 0, 0, 0, 0). As func_15063920, the asm finds the block
 * through the record index (rec - base) / 0x32C.
 */
void func_150637B4(struct127 *rec) {
    s32 idx = ((u8 *)rec - (u8 *)D_800CC2D0) / 0x32C;
    u8 *state;

    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x78] = 9;
    func_15083568(rec, 0x1D, 1.0f, 0);
    func_15083568(rec, 0x1E, 1.0f, 0);
    ((u8 *)rec)[0x8A] = 20;
    ((u8 *)rec)[0x89] = 0;
    ((u8 *)rec)[0x83] = 0;
    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    *(s16 *)(state + 0x24) = 60;
    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x11A] = 2;
    func_1505E650(rec, 0x7F, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_150637B4.s")
#endif

s32 func_150836CC(struct127 *, s32);
void func_15063894(struct127 *arg0) {
    struct127 *temp_v0;
    temp_v0 = &D_800CC2D0[arg0 - D_800CC2D0];
    temp_v0->unk31C->unk78 = 0;
    temp_v0->unk31C->unk11A = 0;
    func_150836CC(arg0, 0x1D);
    func_150836CC(arg0, 0x1E);
    *((u8 *)arg0 + 0x8A) = 0;
    *((u8 *)arg0 + 0x89) = 0;
    *((u8 *)arg0 + 0x83) = 0;
}

#ifdef NON_MATCHING
/*
 * obj_hit_react_start: P190. For object record rec (D_800CC2D0, 0x32C bytes): its state block (+0x31C) gets
 * +0x78 = 0x3B and +0x11A = 2, animation 0x89 at speed 1 (func_15083568), rec +0x8A = 20, +0x89 = +0x83 = 0, and
 * func_1505E650(rec, 0x221, 1.0, 0, 0, 0, 0). The asm finds the block through the record index (rec - base) / 0x32C.
 */
void func_15063920(struct127 *rec) {
    s32 idx = ((u8 *)rec - (u8 *)D_800CC2D0) / 0x32C;
    u8 *state;

    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x78] = 0x3B;
    state = *(u8 **)((u8 *)D_800CC2D0 + idx * 0x32C + 0x31C);
    state[0x11A] = 2;
    func_15083568(rec, 0x89, 1.0f, 0);
    ((u8 *)rec)[0x8A] = 20;
    ((u8 *)rec)[0x89] = 0;
    ((u8 *)rec)[0x83] = 0;
    func_1505E650(rec, 0x221, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063920.s")
#endif

#ifdef NON_MATCHING
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
#else
s32 func_15081A90(struct127 *, s32, s32, s32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
#endif
void func_150639D8(u8 *arg0, f32 arg1) {
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
#ifdef NON_MATCHING
    func_15081A90(arg0, (*(f32 *)((u8 *)temp_v0 + 0x13C)), (*(f32 *)((u8 *)temp_v0 + 0x140)), (*(f32 *)((u8 *)temp_v0 + 0x144)), (*(f32 *)((u8 *)temp_v0 + 0x130)), (*(f32 *)((u8 *)temp_v0 + 0x134)), (*(f32 *)((u8 *)temp_v0 + 0x138)), temp_v0 + 0xB0, arg1, 0, 0, 0, -1, 0, 0);
#else
    func_15081A90(arg0, (*(s32 *)((u8 *)temp_v0 + 0x13C)), (*(s32 *)((u8 *)temp_v0 + 0x140)), (*(s32 *)((u8 *)temp_v0 + 0x144)), (*(f32 *)((u8 *)temp_v0 + 0x130)), (*(f32 *)((u8 *)temp_v0 + 0x134)), (*(f32 *)((u8 *)temp_v0 + 0x138)), temp_v0 + 0xB0, arg1, 0, 0, 0, -1, 0, 0);
#endif
    func_15063A54((struct127 *)arg0);
}

void func_15063A54(struct127 *arg0) {
    u8 *v = *(u8 **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xB0);
    u8 *w;

    if (v != NULL) {
        w = *(u8 **)(v + 0x31C);
        if (w != NULL) {
            (*(u8 **)(v + 0x31C))[0x195] = 0x1E;
            (*(u8 **)(v + 0x31C))[0x196] = arg0 - D_800CC2D0;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063AA0.s")

extern s16 D_800CC6D2;

s16 func_15063D6C(u8 *arg0) {
    D_800CC6D2 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12))) - func_15063740(arg0);
    if (D_800CC6D2 >= 0x3E81) {
        D_800CC6D2 = 0x3E80;
    }
    if (D_800CC6D2 < -0x3E80) {
        D_800CC6D2 = -0x3E80;
    }
    return D_800CC6D2;
}

#ifdef NON_MATCHING
extern u8 *D_800CC6A4;
extern f32 D_800CC6D4;

s32 func_15063DE8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_v0;
    u16 temp_t0;
    u16 temp_t3;

    var_v0 = 0;
    if (arg1 & arg2) {
        D_800CC6D2 = (*(s8 *)((u8 *)D_800CC6A4 + 2)) * 0xC8;
        if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x84)) != 0) {
            D_800CC6D2 = func_15063D6C(arg0);
        }
        D_800CC6D4 = 12.0f;
        D_800CC6D2 = (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12)) + ((s32) (D_800CC6D2 * D_800CC264) / 2000);
        if (D_800CC6D2 < -0x2328) {
            temp_t0 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - D_800CC6D2) - 0x2328;
            (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t0;
            (*(u16 *)((u8 *)arg0 + 0x76)) = temp_t0;
            D_800CC6D2 = -0x2328;
        }
        if (D_800CC6D2 >= 0x2329) {
            temp_t3 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - D_800CC6D2) + 0x2328;
            (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t3;
            (*(u16 *)((u8 *)arg0 + 0x76)) = temp_t3;
            D_800CC6D2 = 0x2328;
        }
        var_v0 = 1;
        (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12)) = D_800CC6D2;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063DE8.s")
#endif
#ifdef NON_MATCHING
u8 * func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
#else
s32 func_15031C4C(struct127 *, s32, s32);
#endif
void func_1506B04C(struct127 *, s32, void *);

void func_15063F14(struct127 *arg0, s32 arg1) {
    s32 kind;
    struct {
        struct127 *obj;
        struct17 pos;
        s32 idx;
    } blk;

    if (arg0->id == 0x75 || arg0->id == 0xB1) {
        kind = 100;
    } else {
        kind = 44;
    }
    if (func_15031C4C(arg0, kind, 0) == 0 && arg1 == 0) {
        return;
    }
    if (arg0->unk1D4 != NULL) {
        func_15143134(NULL, &blk.pos, (u8 *)arg0->unk1D4 + 0x100);
    } else {
        blk.pos.unk0 = arg0->x_position;
        blk.pos.unk4 = arg0->y_position;
        blk.pos.unk8 = arg0->z_position;
    }
    blk.idx = (arg0 - D_800CC2D0) + 1;
    blk.obj = arg0;
    func_1506B04C(arg0, 0xB, &blk);
    if (func_150836CC(arg0, kind)) {} // fakematch: consuming the result frees v0 for the tail
    if (*(*(u8 **)((u8 *)arg0 + 0x31C) + 0x19A) != 0) {
        *(*(u8 **)((u8 *)arg0 + 0x31C) + 0x19A) -= 1;
    }
    *(*(u8 **)((u8 *)arg0 + 0x31C) + 0x11A) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_1506401C.s")

#ifdef NON_MATCHING
s32 func_15064240(struct127 *arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    s32 temp_t6;
    struct126 *temp_v0;
    u8 temp_a1;

    temp_t6 = arg1 & 0xFFFF;
    if ((arg4 & 0x4000) && (arg0->unk28 == 0.0f) && (arg0->y_velocity <= 0.0f)) {
        temp_v0 = arg0->unk31C;
        if (((u8) temp_v0->unk95 == 0) && (temp_t6 != arg0->unk84.uh) && ((temp_a1 = temp_v0->unk11A, (temp_a1 == 0)) || (temp_a1 == 2)) && (temp_v0->unk27 == 0)) {
            if ((arg3 != 0) && (arg0->disable_jump != 0)) {
                return 0x3E7;
            }
            if (arg2 & 0xFFFF & 1) {
                arg0->disable_jump = 0x14;
            }
            if (arg3 != 0) {
                if (arg0->unk31C->unk11A == 2) {
                    return 0x3E7;
                }
                arg0->unk31C->unk11A = 1;
                /* Duplicate return node #18. Try simplifying control flow for better match */
                arg0->unk31C->unk78 = (u8) arg3;
                arg0->disable_run = 0xFF;
                arg0->unk83 = 0xFF;
                return temp_t6;
            }
            arg0->unk31C->unk11A = 3;
            arg0->unk31C->unk78 = (u8) arg3;
            arg0->disable_run = 0xFF;
            arg0->unk83 = 0xFF;
            return temp_t6;
        }
    }
    return 0x3E7;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064240.s")
#endif
#ifdef NON_MATCHING
extern f32 D_80099B50;
extern f32 D_80099B54;
extern f32 D_80099B5C;
void func_1506435C(u8 *arg0, s32 arg1) {
    struct {
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
    } sp;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    f32 var_f2_2;
    u8 *temp_v0;

    var_f0 = 300.0f;
    var_f2 = 0.0f;
    var_f14 = 0.0f;
    switch (arg1) {                                 /* irregular */
    case 2:
        var_f14 = 27.0f;
        break;
    case 3:
    case 6:
        var_f2 = -11.0f;
        var_f0 = 500.0f;
        break;
    }
    sp5C = var_f14;
    sp60 = var_f2;
    temp_f12 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x16C)) * D_80099B50;
    sp.u78 = var_f0;
    sp58 = temp_f12;
    sp64 = sinf(temp_f12) * var_f14;
    sp68 = cosf(temp_f12) * var_f14;
    sp.u6C = sp64 + (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x13C));
    sp.u70 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x140)) + var_f2;
    sp.u74 = sp68 + (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x144));
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    if ((*(u8 *)((u8 *)temp_v0 + 0x109)) == 0) {
        var_f2_2 = -(*(f32 *)((u8 *)temp_v0 + 0x170));
        var_f12 = (*(f32 *)((u8 *)temp_v0 + 0x16C)) + 90.0f;
    } else {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0xB8)) - sp.u6C;
        temp_f16 = (*(f32 *)((u8 *)temp_v0 + 0xC0)) - sp.u74;
        sp4C = temp_f2;
        sp44 = temp_f16;
        temp_f2_2 = func_150484A0((*(f32 *)((u8 *)temp_v0 + 0xBC)) - sp.u70, sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16))) * D_80099B54;
        sp54 = temp_f2_2;
        var_f2_2 = temp_f2_2;
        var_f12 = func_150484A0(sp4C, sp44) * D_80099B54;
    }
    sp50 = var_f12;
    func_1505A184((s32) (var_f2_2 * D_80099B5C) & 0xFFFF, sp.u78, 0.0f, &sp.u84, &sp.u80, &sp.u7C);
    temp_f0 = -sp.u80;
    sp.u80 = temp_f0;
    func_1506C460(sp50, sp.u84, temp_f0, 0.0f, 0x64U, arg1, 0.0f, 0.5f, (s32) &sp.u6C, 1, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_1506435C.s")
#endif
s32 func_1505DADC(u8 *, u16 *, s32, s32, s32);

u16 func_15064594(u8 *arg0, u16 arg1, u16 arg2, u16 arg3) {
    u16 r;
    s32 pad; // fakematch: frame slot between r and s
    u16 s;

    s = 0;
    r = arg1;
    if (func_150ADA20() & 1) {
        r = arg2;
    }
    if (arg1 == *(u16 *)(arg0 + 0x84) || arg2 == *(u16 *)(arg0 + 0x84)) {
        if (arg0[0x107] < 0x28) {
            return 999;
        }
        r = arg3;
    }
    if (arg3 == *(u16 *)(arg0 + 0x84)) {
        r = 999;
    }
    if (func_1505DADC(arg0, &s, 0, 0xFE, 0x40) != 0xFF) {
        *(u16 *)(arg0 + 0x76) = s;
    }
    arg0[0x83] = 0xFF;
    return r;
}

#ifdef NON_MATCHING
extern s32 D_800CC6AC;               /* pad buttons pressed this frame */
void func_15074664(void);
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
void func_15060A30(s32 arg0, struct127 *arg1);

#define P_U8(o) (((u8 *)player)[o])
#define P_F32(o) (*(f32 *)((u8 *)player + (o)))
#define CTX(pl) (*(u8 **)((u8 *)(pl) + 0x31C)) /* the player's context / action state */

// player_context_action: B / context button of the player. First runs a pending context action (ctx+0x7B, set by
// the level: sit down, pick up / put down, open, push, ...), then, when B was pressed with nothing pending and the
// player is on the ground, starts the B animation (attack / slap, or a level variant). arg3 != 0 only updates the
// state (no animation); noPad != 0 swallows the B press (buttons and D_800CC6AC lose 0x4000).
void func_15064668(struct127 *player, s32 buttons, f32 height, s32 arg3, s32 noPad) {
    u8 *ctx;
    struct127 *o;
    s32 anim = 0;
    f32 speed = 1.0f;
    f32 blend = 4.0f;
    f32 dx, dz, dist;
    f32 x, y, z;
    u8 mode;
    s32 w;
    u8 *m;

    if (noPad) {
        buttons &= ~0x4000;
        D_800CC6AC &= ~0x4000;
    }
    ctx = CTX(player);
    if (ctx[0x7B] != 0) {
        switch (ctx[0x7B]) {
        case 1: /* sit down at the stored spot */
            w = *(s32 *)((u8 *)player + 0x2E4);
            P_U8(0x83) = 0xFF;
            P_U8(0x89) = 0xFF;
            *(s16 *)((u8 *)player + 0x84) = 0;
            ctx[0x30] = 0xD;
            *(f32 *)(CTX(player) + 0x28) = (s16)(w >> 16);
            *(f32 *)(CTX(player) + 0x2C) = (s16)w;
            anim = 0x96;
            *(s16 *)((u8 *)player + 0x76) = *(s32 *)((u8 *)player + 0x2E8);
            break;
        case 2:
            speed = 0.8f; /* D_80099B90 */
            anim = 0xDD;
            P_U8(0x89) = 0xFF;
            P_U8(0x83) = 0xFF;
            break;
        case 3:
            D_800D1580 = 1;
            func_15074664();
            if (P_U8(0xAD) != 0 || (s32)P_F32(0x28) != 0) {
                func_15083568(player, 0x17, 1.0f, 0);
                CTX(player)[0x11A] = 2;
            } else {
                P_U8(0x89) = 0xFF;
                P_U8(0x8A) = 0xFF;
                P_U8(0x83) = 0xFF;
                speed = 3.0f;
                anim = 0x151;
                CTX(player)[0x11A] = 1;
            }
            break;
        case 4:
            D_800D1580 = 0;
            func_15074664();
            if (P_U8(0xAD) != 0 || (s32)P_F32(0x28) != 0) {
                func_150836CC(player, 0x17);
                CTX(player)[0x11A] = 0;
            } else {
                P_U8(0x89) = 0xFF;
                P_U8(0x8A) = 0xFF;
                P_U8(0x83) = 0xFF;
                speed = 3.0f;
                anim = 0x14E;
                CTX(player)[0x11A] = 3;
            }
            break;
        case 5: /* ride object 0x6C */
            o = func_1505F0AC(0x6C);
            P_U8(0x81) = 1;
            w = *(s32 *)((u8 *)o + 0x2E4);
            if (w == 0) {
                P_F32(0x1CC) = P_F32(0x18);
                w = 100;
                anim = 0x38;
                *(s32 *)((u8 *)o + 0x2E4) = 100;
            }
            if (w >= 100) {
                m = *(u8 **)((u8 *)o + 0x1D4);
                if (m != NULL) {
                    P_F32(0x18) = *(s16 *)(m + 0x15A) + 20;
                }
            }
            if ((buttons & 0x8000) && *(s32 *)((u8 *)o + 0x2E4) == 100) {
                *(s32 *)((u8 *)o + 0x2E4) = 0x7A;
                *(s32 *)((u8 *)o + 0x2E8) = 0x7A;
                anim = 0x16;
                func_15060A30(0x38E, player);
            }
            break;
        case 6:
        case 8:
            if ((buttons & 0x4000) && height <= 0.0f) {
                speed = 2.0f;
                P_U8(0x83) = 0xFF;
                P_U8(0x89) = 0xFF;
                anim = 0x33;
            }
            break;
        case 9:
            anim = 0x22D;
            P_U8(0x89) = 0xFF;
            P_U8(0x83) = 0xFF;
            break;
        case 10:
        case 12:
            if (P_F32(0x28) <= 1.0f) {
                anim = (ctx[0x7B] == 10) ? 0x19A : 0x2E7;
                P_U8(0x83) = 0xFF;
            }
            P_U8(0x89) = 200;
            P_U8(0x8A) = 200;
            break;
        case 11: /* camera pull towards the point (-1884, 100) */
            dx = P_F32(0x14) - -1884.0f; /* D_80099B94 */
            dz = P_F32(0x1C) - 100.0f;
            dist = sqrtf(dx * dx + dz * dz);
            if (dist < 1000.0f) {
                func_1505A184(func_1505A630(-dx, dz, 0), 20.0f, 0.0f, &x, &y, &z);
                func_1505A250(x, y, (1200.0f - dist) * 0.001f /* D_80099B98 */, (f32 *)((u8 *)player + 0x16C),
                              (f32 *)((u8 *)player + 0x170));
            }
            break;
        }
        CTX(player)[0x7B] = 0;
    }

    ctx = CTX(player);
    if (ctx[0x198] == 0 && anim == 0 && (buttons & 0x4000)) {
        mode = ctx[0x4E];
        if ((mode & 0xF) != 1 && height <= 0.0f && P_U8(0x89) != 0xFF) {
            if (P_U8(0x13C) >= 100) {
                if (!(*(s32 *)((u8 *)player + 0x25C) & 0x20)) {
                    anim = 0xD6;
                    speed = 1.15f; /* D_80099B9C */
                    if (D_800BE616) {
                        anim = 0x118;
                        speed = 1.0f;
                    }
                    if (D_800BE9F0 == 0x30) {
                        anim = 0x28D;
                    }
                    P_U8(0x83) = 0xFF;
                    P_U8(0x89) = 0xFF;
                }
            } else if (((ctx[0x75] == 0 && ctx[0x7C] == 0) || mode == 2) && D_800BE9F0 != 0x2D &&
                       D_800BE9F0 != 0x2B && D_800BE9F0 != 0x30 && D_800BE9F0 != 0x34) {
                anim = 0x33;
                if (*(s16 *)(ctx + 8) != 0) {
                    P_U8(0x83) = 0xFF;
                    P_U8(0x89) = 0xFF;
                    speed = 1.6f; /* D_80099BA0 */
                } else {
                    P_U8(0x83) = 0xFF;
                    if (D_800BE616 == 0) {
                        anim = 0x1DC;
                    } else if (D_800E9D00 & 0x400) {
                        anim = 0x355;
                    } else if (D_800E9D00 & 0x800) {
                        anim = 0x1DC;
                    } else {
                        anim = 0x354;
                    }
                    ctx = CTX(player);
                    speed = 1.35f; /* D_80099BA4 */
                    if (ctx[0x84] == 0 && ctx[0x4E] == 0) {
                        P_U8(0x89) = 0xFF;
                        P_F32(0x20) = -4.0f;
                        *(u16 *)((u8 *)player + 0x76) = *(u16 *)(ctx + 0x4C);
                        speed = 1.0f;
                        anim = 0x46;
                    }
                    P_U8(0x80) = 1;
                    blend = 0.0f;
                }
            }
        }
    }
    if (anim != 0 && anim != 999 && arg3 == 0) {
        func_1505E650(player, anim, speed, blend, 0.0f, 0.0f, 0);
    }
}
#undef P_U8
#undef P_F32
#undef CTX
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064668.s")
#endif

void func_15064D5C(s32 arg0, s32 arg1) {
    f32 temp_f0;
    struct197 *temp_v0;
    struct197 *temp_v1;

    temp_v0 = D_800CC2D0[arg1].unk2D0;
    temp_v1 = D_800CC2D0[arg0].unk2D0;
    if ((temp_v0 != NULL) && (temp_v1 != NULL)) {
        temp_f0 = temp_v0->unk18;
        temp_v0->unk8 = temp_v1->unk8;
        if (temp_f0 <= temp_v0->unk8) {
            temp_v0->unk8 = temp_f0 - 1.0f;
        }
    }
}

#ifdef NON_MATCHING
void func_15064DD0(struct127 *arg0) {
    s32 *temp_a1;
    s32 var_v0;
    s32 var_v1;
    struct126 *temp_v0_4;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 temp_v0;

    temp_a1 = &(*(s32 *)((u8 *)(&D_800CC2D0[arg0->unk65]) + -0x32C));
    temp_v0 = (*(u8 *)((u8 *)temp_a1 + 4));
    var_v1 = 0xF;
    if (temp_v0 == 0xC) {
        temp_v0_2 = (*(u16 *)((u8 *)temp_a1 + 0x84));
        var_v1 = 0x5A;
        if (temp_v0_2 == 0xC) {
            var_v1 = 0x5B;
        } else if (temp_v0_2 == 0xD) {
            var_v1 = 0x5C;
        }
    } else if (temp_v0 == 0x53) {
        temp_v0_3 = (*(u16 *)((u8 *)temp_a1 + 0x84));
        var_v1 = 0x8C;
        if (temp_v0_3 == 0xB) {
            var_v1 = 0xA2;
        } else if (temp_v0_3 == 0xD) {
            var_v1 = 0xA3;
        }
    } else if (temp_v0 == 0x21) {
        var_v1 = 0x169;
    } else if (temp_v0 == 0x8A) {
        temp_v0_4 = arg0->unk31C;
        if ((temp_v0_4 != NULL) && ((*(u8 *)((u8 *)temp_v0_4 + 0x1B2)) != 0)) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        if ((*(u8 *)((u8 *)temp_a1 + 0x232)) == 4) {
            if (var_v0 != 0) {
                var_v1 = 0x350;
            } else {
                var_v1 = 0x1A4;
            }
        } else {
            var_v1 = 0x1A1;
            if (var_v0 != 0) {
                var_v1 = 0x34F;
            }
        }
    }
    func_1505E650(arg0, var_v1 & 0xFFFF, 1.0f, 6.0f, 0.0f, 0.0f, 0);
    func_15064D5C(arg0->unk65 - 1, (s32) D_800C3E78);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064DD0.s")
#endif
#ifdef NON_MATCHING
extern u8 D_800B89C4[];              /* per-player record (stride 0x32C): character kind byte */

#define P_U8(o) (((u8 *)player)[o])
#define P_F32(o) (*(f32 *)((u8 *)player + (o)))

// player_move_animation: picks the walk / run / carry animation of the player for this frame from the movement
// speed (vel = stick speed, ground speed at +0x44, +0x3C), the player's state (ctx = +0x31C: carried / held object
// kind at +0x78, swim, ladder, ...) and the multiplayer character kind, and starts it (func_1505E650) with a playback
// speed that follows the movement. moveAnim (when no object is held) overrides the choice; stickMag is the raw
// stick magnitude, pushSpeed the push speed (+0x32 bit 2). Returns the animation id, 0 for none, 999 for "keep".
s32 func_15064F50(struct127 *player, f32 vel, f32 stickMag, s32 moveAnim, f32 pushSpeed) {
    u8 *ctx = *(u8 **)((u8 *)player + 0x31C);
    s32 anim = 0;
    f32 speed = 1.0f;
    f32 blend = 4.0f;
    f32 v;

    if (*(s16 *)(ctx + 0x46) > 0) {
        anim = 0x4C;
        speed = vel / 24.0f;
    } else if (ctx[0x4E] == 2) {
        anim = (*(s8 *)(ctx + 0x50) > 0) ? 0x54 : 5;
        blend = 2.0f;
    } else if (P_U8(0x13C) >= 100) {
        /* multiplayer characters */
        v = P_F32(0x3C);
        if (v < 1.0f) {
            anim = func_1504C078();
        } else {
            switch (D_800B89C4[((u8 *)D_800D154C)[0x13C] * 0x32C]) {
            case 0x8C:
                P_U8(0xAA) = 0x5A;
                anim = 0x1A6;
                speed = vel / 6.0f + 0.4f;
                if (14.0f < v) {
                    anim = 0x1A7;
                    speed = vel / 26.0f + 0.5f;
                }
                break;
            case 0x57:
                P_U8(0xAA) = 0x5A;
                anim = 0x116;
                speed = vel / 6.0f + 0.4f;
                if (14.0f < v) {
                    anim = 0x117;
                    speed = vel / 26.0f + 0.5f;
                }
                break;
            case 0xA8:
            case 0xA9:
                if (14.0f < v) {
                    anim = 0x1B1;
                    speed = vel / 22.0f + 0.4f;
                } else {
                    anim = 0x1B0;
                    speed = vel * 0.0625f + 0.6f;
                }
                break;
            case 0x13:
                anim = 0x14C;
                speed = vel / 6.0f;
                break;
            case 0x89:
                anim = 0x1FB;
                speed = vel / 6.0f;
                break;
            default:
                if (14.0f < v) {
                    anim = 0x2E4;
                    speed = vel * 0.0625f + 0.5f;
                } else {
                    anim = 0xD7;
                    speed = vel / 6.0f + 0.4f;
                }
                break;
            }
        }
    } else if (moveAnim != 0 && ctx[0x78] == 0) {
        anim = moveAnim;
        speed = vel / 15.0f + 0.6f;
    } else if (v = P_F32(0x44), 2.6f < v && (*(u16 *)(ctx + 0x32) & 1)) {
        blend = 5.0f;
        P_U8(0xAA) = 0x28;
        speed = v / 15.0f + 0.5f;
        anim = func_1504C0B8();
    } else {
        /* walking while holding an object of kind ctx[0x78]: walk animation below 20, run animation from 20 */
        switch (ctx[0x78]) {
        case 0x16:
            if (1.0f <= v) {
                anim = ctx[0x1B2] ? 0x2C6 : 0xE8;
                P_U8(0xAA) = 0x1E;
                speed = vel * 0.0625f + 0.6f;
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x09:
            if (1.0f <= v) {
                if (!D_800BE616) {
                    P_U8(0xAA) = 0x37;
                }
                anim = 0x7E;
                if (!D_800BE616) {
                    speed = vel * 0.0625f + 0.6f;
                } else if (20.0f <= P_F32(0x44)) {
                    anim = 0x22C;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x38:
            if (1.0f <= v) {
                anim = 0x1E1;
                if (20.0f <= v) {
                    anim = 0x1E2;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x39:
            if (*(u16 *)((u8 *)player + 0x84) == 0x1EB) {
                anim = 999;
            } else if (1.0f <= v) {
                anim = 0x1EC;
                if (20.0f <= v) {
                    anim = 0x1ED;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x37:
            if (*(u16 *)((u8 *)player + 0x84) == 0x1F4) {
                anim = 999;
            } else if (1.0f <= v) {
                anim = 0x1F5;
                if (20.0f <= v) {
                    anim = 0x1F6;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x3B:
            if (*(u16 *)((u8 *)player + 0x84) == 0x222 || *(u16 *)((u8 *)player + 0x84) == 0x236) {
                anim = 999;
            } else if (1.0f <= v || *(s8 *)(ctx + 0x23) > 0) {
                P_U8(0xAA) = 0x37;
                anim = 0x223;
                if (20.0f <= v) {
                    anim = 0x224;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x12:
        case 0x18:
        case 0x41:
        case 0x24:
        case 0x22:
        case 0x26:
        case 0x23:
        case 0x15:
        case 0x25:
            if (1.0f <= v) {
                s32 walk, run;
                switch (ctx[0x78]) {
                case 0x24: walk = 0x158; run = 0x159; break;
                case 0x22: walk = 0x15B; run = 0x15C; break;
                case 0x26: walk = 0x178; run = 0x179; break;
                case 0x23: walk = 0x161; run = 0x162; break;
                case 0x15: walk = 0xED; run = 0xED; break;
                case 0x25: walk = 0xD7; run = 0xD7; break;
                default: walk = 0xEC; run = 0xF8; break;
                }
                P_U8(0xAA) = 0x50;
                anim = walk;
                speed = vel * 0.0625f + 0.6f;
                if (20.0f <= v) {
                    anim = run;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x21:
            if (1.0f <= v) {
                P_U8(0xAA) = 0x6E;
                anim = 0x123;
                speed = vel * 0.0625f + 0.6f;
                if (15.0f <= v) {
                    anim = 0x124;
                    speed = vel / 27.0f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x3A:
            if (1.0f <= v) {
                P_U8(0xAA) = 0x50;
                anim = 0x1FB;
                speed = vel * 0.0625f + 0.6f;
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x2D:
        case 0x2E:
            if (1.0f <= v) {
                anim = 0x1B0;
                speed = vel * 0.0625f + 0.6f;
                if (20.0f <= v) {
                    anim = 0x1B1;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        case 0x19:
        case 0x40:
            v = P_F32(0x3C);
            if (1.0f <= v) {
                blend = 8.0f;
                anim = 0x112;
                speed = vel * 0.125f + 0.3f;
                if (18.0f <= v) {
                    anim = 0x111;
                    speed = vel / 20.0f + 0.3f;
                }
            } else {
                anim = func_1504C078();
            }
            break;
        default:
            if (ctx[0x1A] != 0 && 1.0f < stickMag) {
                /* swimming */
                speed = vel / 6.5f + 0.3f;
                P_U8(0xAA) = 0x28;
                anim = 0x6D;
                blend = 8.0f;
            } else if (*(s16 *)(ctx + 8) > 0) {
                if (stickMag < 1.0f) {
                    anim = func_1504C078();
                } else {
                    speed = vel / 6.0f + 0.3f;
                    anim = *(u16 *)(ctx + 0xE);
                    blend = 16.0f;
                }
            } else if (ctx[0x17] != 0) {
                blend = 5.0f;
                if (*(u16 *)D_800CC6A4 & 0x2000) {
                    if (*(u16 *)((u8 *)player + 0x84) != 0x283) {
                        P_F32(0x3C) *= 0.2f;
                        D_800D1580 = 0xFF010604;
                        func_1506E5FC();
                    }
                    P_U8(0x89) = 3;
                    P_U8(0x8A) = 3;
                    anim = 0x283;
                } else {
                    if (*(u16 *)((u8 *)player + 0x84) == 0x283) {
                        D_800D1580 = 0xFF010604;
                        func_1506E5FC();
                        v = P_F32(0x44);
                    }
                    if (1.0f <= v && P_U8(0x89) == 0) {
                        P_U8(0xAA) = 0x2D;
                        anim = 0x4E;
                        speed = P_F32(0x3C) / 9.0f;
                    } else {
                        anim = func_1504C078();
                    }
                }
            } else if ((*(u16 *)(ctx + 0x32) & 2) && 1.0f <= v) {
                /* pushing */
                ctx[0x3C] = 0x1C;
                P_U8(0xAA) = 0xF;
                blend = 8.0f;
                speed = pushSpeed / 5.0f + 0.3f;
                anim = 100;
                if ((u32)func_150ADA20() % 1000 >= 988) {
                    anim = (func_150ADA20() & 1) + 0x65;
                    speed = 0.65f;
                    P_U8(0x89) = 0xFF;
                    P_U8(0x83) = 0xFF;
                }
            }
            break;
        }
    }
    if (anim != 0 && anim != 999) {
        func_1505E650(player, anim, speed, blend, 0.0f, 0.0f, 0);
    }
    return anim;
}
#undef P_U8
#undef P_F32
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064F50.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15065E18.s")
