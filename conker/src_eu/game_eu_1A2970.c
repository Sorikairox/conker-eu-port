#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15175EC8(u8 *);
s32 func_150ADE40(s32, s32, s32, s32);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175160.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175514.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175EC8.s")

#ifdef NON_MATCHING
void func_15176DCC(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    s32 temp_v1;
    u8 temp_v0;

    if (D_800DDF5C[(*(u8 *)((u8 *)arg0 + 0x90))] != 0) {
        D_800DDF68[(*(u8 *)((u8 *)arg0 + 0xED))] = 1;
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x91));
        switch (temp_v0) {                          /* irregular */
        case 0:
            if (func_150ADE40((s32) D_800CC2D0->x_position, (s32) D_800CC2D0->z_position, (s32) (*(f32 *)((u8 *)arg0 + 0x98)), (s32) (*(f32 *)((u8 *)arg0 + 0xA0))) < 0x190) {
                (*(u8 *)((u8 *)arg0 + 0x91)) = 1U;
                temp_f10 = (f32) (-1 - (func_150ADA20() & 3));
                (*(f32 *)((u8 *)arg0 + 0xA8)) = -8.0f;
                (*(f32 *)((u8 *)arg0 + 0xB4)) = temp_f10;
                return;
            }
            temp_f0 = (*(f32 *)((u8 *)arg0 + 0xCC));
            if (temp_f0 != 0.0f) {
                (*(f32 *)((u8 *)arg0 + 0xA8)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xA8)) + temp_f0);
                if (temp_f0 < 0.0f) {
                    (*(f32 *)((u8 *)arg0 + 0xAC)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xAC)) + (*(f32 *)((u8 *)arg0 + 0xB8)));
                }
                temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0xA8));
                if (temp_f0_2 > 45.0f) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = -5.0f;
                } else if (((*(f32 *)((u8 *)arg0 + 0xCC)) < 0.0f) && (temp_f0_2 > 25.0f) && ((func_150ADA20() & 0xFF) < 0x33)) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = 5.0f;
                }
                if ((*(f32 *)((u8 *)arg0 + 0xA8)) <= 10.0f) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = 0.0f;
                    return;
                }
            } else {
                temp_v1 = func_150ADA20() & 0xFF;
                if (temp_v1 < 0x19) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = 5.0f;
                    if (temp_v1 < 0xD) {
                        (*(f32 *)((u8 *)arg0 + 0xB8)) = (f32) ((func_150ADA20() % 6U) - 3);
                        return;
                    }
                    (*(f32 *)((u8 *)arg0 + 0xB8)) = 0.0f;
                    return;
                }
            }
            break;
        case 1:
            if ((300.0f + (*(f32 *)((u8 *)arg0 + 0xC8))) <= (*(f32 *)((u8 *)arg0 + 0x9C))) {
                (*(u8 *)((u8 *)arg0 + 0x91)) = 2U;
                (*(s16 *)((u8 *)arg0 + 0x92)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x92)) & 0xFFFE);
                (*(s16 *)((u8 *)arg0 + 0x92)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x92)) | 4);
                (*(f32 *)((u8 *)arg0 + 0xE4)) = (f32) ((f32) (func_150ADA20() & 0x7F) + (300.0f + (*(f32 *)((u8 *)arg0 + 0xC8))));
            }
            func_15175EC8(arg0);
            return;
        default:
        case 2:
        case 3:
            if ((*(f32 *)((u8 *)arg0 + 0x9C)) < (*(f32 *)((u8 *)arg0 + 0xE4))) {
                (*(f32 *)((u8 *)arg0 + 0xB4)) = -1.5f;
            } else if ((*(f32 *)((u8 *)arg0 + 0xA8)) < 0.0f) {
                (*(f32 *)((u8 *)arg0 + 0xB4)) = 1.5f;
            }
            func_15175EC8(arg0);
            return;
        }
    } else {
        func_1516972C((struct102 *) arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15176DCC.s")
#endif
s32 func_150ADE40(s32, s32, s32, s32);
void func_15175EC8(u8 *);
typedef struct { s32 x0; s32 pad[4]; } Row20;
extern Row20 D_800DE2B4[];
extern Row20 D_800DE2B8[];

void func_151770F4(u8 *arg0) {
    s32 v;

    if (((Row20 *)D_800DDE80)[arg0[0xED]].x0 == 0 || D_800DDF78[arg0[0xED]] == 0) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    v = arg0[0xF0];
    if (arg0[0xF1] == 0) {
        if (D_800DDF5C[arg0[0x90]] == 0) {
            arg0[0xF1] = 1;
        } else if (v != 0xFF) {
            v += D_800BE9E4 * 4;
            if (v > 0xFF) {
                v = 0xFF;
            }
            arg0[0xF0] = v;
        }
    } else {
        if (v == 0) {
            func_1516972C((struct102 *)arg0);
            return;
        }
        v -= D_800BE9E4 * 4;
        if (v < 0) {
            v = 0;
        }
        arg0[0xF0] = v;
    }
    D_800DDF68[arg0[0xED]] = 1;
    switch (arg0[0x91]) {
        case 0:
            if (func_150ADE40(*(f32 *)((u8 *)D_800CC2D0 + 0x14), *(f32 *)((u8 *)D_800CC2D0 + 0x1C),
                              *(f32 *)(arg0 + 0x98), *(f32 *)(arg0 + 0xA0)) < 200) {
                arg0[0x91] = 2;
                *(f32 *)(arg0 + 0xE4) = (f32)((u32)func_150ADA20() % *(s16 *)(arg0 + 0xDA));
                *(f32 *)(arg0 + 0xE4) += *(s16 *)(arg0 + 0xD2);
                *(s32 *)(arg0 + 0x94) = D_800DE2B8[arg0[0xED]].x0;
            } else {
                *(s32 *)(arg0 + 0x94) = D_800DE2B4[arg0[0xED]].x0;
            }
            return;
        case 2:
        case 3:
            break;
        case 4:
            if (*(f32 *)(arg0 + 0x9C) < *(f32 *)(arg0 + 0xC8)) {
                func_1516972C((struct102 *)arg0);
                return;
            }
            break;
    }
    func_15175EC8(arg0);
}

#ifdef NON_MATCHING
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);
extern u8 D_800A7550[4];
extern Row20 D_800DE2BC[];

// prop_model_draw: draws the object's model (kinds 1..3 of func_15177638) unless its row of D_800DDE80 / D_800DDF78
// (index obj[0xED]) is empty: matrix = yaw (+0xAC) after pitch / roll (+0xA8 / +0xB0), scaled by +0xC0, at +0x98..+0xA0
// (into the object's per-frame matrix slot +0x10 + D_800BE9C0 * 0x40), segment 1 = +0x94, render mode
// (func_15142FBC) and env colour (v, v, v, obj[0xF0]) where v (obj[0xEC]) fades by 4 per frame towards
// D_800A7550[(+0xE8 >> 5) & 3], then the row's display list (D_800DE2BC).
Gfx *func_15177360(Gfx *gdl, u8 *obj, s16 arg2) {
    f32 mf[4][4];
    f32 rot[4][4];
    s32 v;
    s32 target;
    u8 flag;

    if (((Row20 *)D_800DDE80)[obj[0xED]].x0 == 0 || D_800DDF78[obj[0xED]] == 0) {
        return gdl;
    }
    func_150A8050(mf, 0.0f, *(f32 *)(obj + 0xAC), 0.0f);
    func_150A8050(rot, *(f32 *)(obj + 0xA8), 0.0f, *(f32 *)(obj + 0xB0));
    func_150A7A48(rot, mf, mf);
    mf[3][0] = *(f32 *)(obj + 0x98);
    mf[3][1] = *(f32 *)(obj + 0x9C);
    mf[3][2] = *(f32 *)(obj + 0xA0);
    mf[0][0] *= *(f32 *)(obj + 0xC0);
    mf[0][1] *= *(f32 *)(obj + 0xC0);
    mf[0][2] *= *(f32 *)(obj + 0xC0);
    mf[1][0] *= *(f32 *)(obj + 0xC0);
    mf[1][1] *= *(f32 *)(obj + 0xC0);
    mf[1][2] *= *(f32 *)(obj + 0xC0);
    mf[2][0] *= *(f32 *)(obj + 0xC0);
    mf[2][1] *= *(f32 *)(obj + 0xC0);
    mf[2][2] *= *(f32 *)(obj + 0xC0);
    guMtxF2L(mf, (Mtx *)(obj + 0x10 + (D_800BE9C0 << 6)));
    gSPMatrix(gdl++, obj + 0x10 + (D_800BE9C0 << 6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gdl++, 1, *(s32 *)(obj + 0x94));
    gDPPipeSync(gdl++);

    v = obj[0xEC];
    target = D_800A7550[(*(u32 *)(obj + 0xE8) >> 5) & 3];
    if (v != target) {
        if (v < target) {
            v += D_800BE9E4 * 4;
            if (v > target) {
                v = target;
            }
        } else {
            v -= D_800BE9E4 * 4;
            if (v < 0) {
                v = 0;
            }
        }
        obj[0xEC] = v;
    }
    flag = 0;
    gdl = func_15142FBC(gdl, 0x82CA0, 0x504A50, &flag);
    gDPSetEnvColor(gdl++, v, v, v, obj[0xF0]);
    gSPDisplayList(gdl++, D_800DE2BC[obj[0xED]].x0);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15177360.s")
#endif

#ifdef NON_MATCHING
s32 func_1510B460(u8 *, f32, f32, f32, f32, f32, f32, f32, s32, s32);
#else
s32 func_1510B460(u8 *, s32, s32, s32, f32, f32, f32, f32, s32, s32);
#endif
Gfx *func_15177360(Gfx *, u8 *, s16);
extern f32 D_800D3A00;
extern f32 D_800D3A04;
extern f32 D_800D9F40;
extern u8 D_800DA030[];

Gfx *func_15177638(Gfx *gdl, u8 *arg1, s16 arg2) {
    f32 mf[4][4];
    s32 pad[2];

#ifdef NON_MATCHING
    if (func_1510B460(&D_800DA030[arg2 << 6], *(f32 *)(arg1 + 0x98), *(f32 *)(arg1 + 0x9C), *(f32 *)(arg1 + 0xA0), D_800D9F40, 4000.0f, D_800D3A00, D_800D3A04, 0, 0) == 0) {
#else
    if (func_1510B460(&D_800DA030[arg2 << 6], *(s32 *)(arg1 + 0x98), *(s32 *)(arg1 + 0x9C), *(s32 *)(arg1 + 0xA0), D_800D9F40, 4000.0f, D_800D3A00, D_800D3A04, 0, 0) == 0) {
#endif
        switch (arg1[0x91]) {
        case 0:
            func_150A8050(mf, *(f32 *)(arg1 + 0xA8), *(f32 *)(arg1 + 0xAC), *(f32 *)(arg1 + 0xB0));
            mf[3][0] = *(f32 *)(arg1 + 0x98);
            mf[3][1] = *(f32 *)(arg1 + 0x9C);
            mf[3][2] = *(f32 *)(arg1 + 0xA0);
            guMtxF2L(mf, arg1 + 0x10 + (D_800BE9C0 << 6));
            gSPMatrix(gdl++, arg1 + 0x10 + (D_800BE9C0 << 6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(gdl++, 1, D_800DDE80[0x33]);
            gSPDisplayList(gdl++, D_800DDE80[0x35]);
            break;
        case 1:
        case 2:
        case 3:
        default:
            gdl = func_15177360(gdl, arg1, arg2);
            break;
        }
    }
    return gdl;
}

#ifdef NON_MATCHING
extern s32 D_8008D450;

void func_151777CC(u8 arg0) {
    f32 sp28;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    s32 temp_a0;
    s32 temp_f16;
    s32 temp_f18;
    s32 temp_f6;
    s32 temp_f8;
    s32 temp_s1;
    s32 temp_t6;
    u8 *temp_s0;

    temp_t6 = arg0;
    temp_s0 = ((s32 *)((u8 *)&D_8008D450 + (temp_t6 * 0x38)));
    temp_s1 = D_800DE2B8[temp_t6].x0;
    temp_f2 = func_150AD78C((*(f32 *)((u8 *)temp_s0 + 0x24)) * 0.017453292f) * (*(f32 *)((u8 *)temp_s0 + 0x28));
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = temp_f2;
    temp_f20 = temp_f2 * 0.017453292f;
    sp28 = func_150AD78C(temp_f20);
    temp_f2_2 = (*(f32 *)((u8 *)temp_s0 + 0x30));
    temp_f18 = (s32) (temp_f2_2 * func_150AD780(temp_f20));
    temp_f8 = (s32) (temp_f2_2 * sp28);
    temp_a0 = -temp_f18;
    (*(s16 *)((u8 *)temp_s1 + 0xA0)) = (s16) temp_a0;
    (*(s16 *)((u8 *)temp_s1 + 0xB0)) = (s16) temp_a0;
    (*(s16 *)((u8 *)temp_s1 + 0x110)) = (s16) temp_f18;
    (*(s16 *)((u8 *)temp_s1 + 0x120)) = (s16) temp_f18;
    (*(s16 *)((u8 *)temp_s1 + 0x112)) = (s16) temp_f8;
    (*(s16 *)((u8 *)temp_s1 + 0x122)) = (s16) temp_f8;
    (*(s16 *)((u8 *)temp_s1 + 0xA2)) = (s16) temp_f8;
    (*(s16 *)((u8 *)temp_s1 + 0xB2)) = (s16) temp_f8;
    temp_f2_3 = func_150AD78C(((*(f32 *)((u8 *)temp_s0 + 0x24)) - 30.0f) * 0.017453292f) * (*(f32 *)((u8 *)temp_s0 + 0x28));
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = temp_f2_3;
    temp_f20_2 = temp_f2_3 * 0.017453292f;
    sp28 = func_150AD78C(temp_f20_2);
    temp_f2_4 = (*(f32 *)((u8 *)temp_s0 + 0x34));
    temp_f16 = (s32) (temp_f2_4 * func_150AD780(temp_f20_2));
    temp_f6 = (s32) (temp_f2_4 * sp28);
    (*(s16 *)((u8 *)temp_s1 + 0xE0)) = (s16) -temp_f16;
    (*(s16 *)((u8 *)temp_s1 + 0x130)) = (s16) temp_f16;
    (*(s16 *)((u8 *)temp_s1 + 0xE2)) = (s16) temp_f6;
    (*(s16 *)((u8 *)temp_s1 + 0x132)) = (s16) temp_f6;
    (*(f32 *)((u8 *)temp_s0 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x24)) + (*(f32 *)((u8 *)temp_s0 + 0x1C)));
    temp_f12 = (*(f32 *)((u8 *)temp_s0 + 0x24));
    if (temp_f12 >= 360.0f) {
        (*(f32 *)((u8 *)temp_s0 + 0x24)) = (f32) (temp_f12 - 360.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_151777CC.s")
#endif