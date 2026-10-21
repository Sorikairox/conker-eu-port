#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15063A54(struct127 *);


s16 func_15063740(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[(*(u8 *)((u8 *)arg0 + 0x222))];
    return func_1505A630(temp_v0->x_position - (*(f32 *)((u8 *)arg0 + 0x14)), (*(f32 *)((u8 *)arg0 + 0x1C)) - temp_v0->z_position, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_150637B4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063920.s")

s32 func_15081A90(struct127 *, s32, s32, s32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
void func_150639D8(u8 *arg0, f32 arg1) {
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    func_15081A90(arg0, (*(s32 *)((u8 *)temp_v0 + 0x13C)), (*(s32 *)((u8 *)temp_v0 + 0x140)), (*(s32 *)((u8 *)temp_v0 + 0x144)), (*(f32 *)((u8 *)temp_v0 + 0x130)), (*(f32 *)((u8 *)temp_v0 + 0x134)), (*(f32 *)((u8 *)temp_v0 + 0x138)), temp_v0 + 0xB0, arg1, 0, 0, 0, -1, 0, 0);
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064668.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064F50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15065E18.s")
