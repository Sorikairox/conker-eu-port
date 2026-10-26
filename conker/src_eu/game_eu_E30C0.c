#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void attach_fx_asset_acquire(s32 arg0);

struct260 *func_150B58B0(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
    } tmp;

    if (arg0 == NULL) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.0f;
    temp_v0 = func_15149130((arg1 == -1) ? 300 : arg1, -1, 0x24, -1, (arg1 == -1) ? 0 : 1, 0x23, 0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
        attach_fx_asset_acquire(6);
    }
    return temp_v0;
}

#ifdef NON_MATCHING
extern f32 D_8009FFF0;
extern f32 D_8009FFF4;
extern f32 D_8009FFF8;
extern f32 D_8009FFFC;
void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);
s32 object_arc_to_surface_spawn(u8 *, s16, s16, s16, s32, f32, f32, s32, s32, s8 *, s32, s32);
void obj_angle_point_effect(u8 *, s16, s16, u8, s32);

void func_150B5988(u8 *arg0) {
    struct {
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
    } sp;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_s3;
    u8 *temp_s1;
    u8 *temp_s6;

    temp_s6 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s1 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s6 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s6 + 0x3B))) || ((*(u8 *)((u8 *)temp_s6 + 4)) == 0xFF)) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    func_1502ED88(temp_s6, 0xFF, 0xFF, 0xFF, 0x1E, 0, 0xA);
    (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((D_8009FFF0 + (random_float() * D_8009FFF4)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f) {
        do {
            sp.u94 = 0xBA;
            sp.u95 = 0xD2;
            sp.u96 = 0xFF;
            sp.u97 = (random_int() % 126U) + 0x82;
            temp_s2 = random_int();
            temp_s0 = random_int();
            temp_s3 = random_int();
            object_arc_to_surface_spawn(temp_s6, (s16) (temp_s2 & 0xFF), (s16) (((u32) temp_s0 % 101U) - 0x3F), (s16) ((temp_s3 & 0xF) + 0xF), 4, 129.0f, (random_float() * 75.0f) + 35.0f, 0, 1, &sp.u94, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f);
    }
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((D_8009FFF8 + (random_float() * D_8009FFFC)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        do {
            temp_s0_2 = random_int();
            obj_angle_point_effect(temp_s6, (s16) (temp_s0_2 & 0xFF), (s16) ((random_int() % 101U) - 0x3F), (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E30C0/func_150B5988.s")
#endif
void func_150B5CA4(void *arg0) {
    attach_fx_asset_release(6);
}

void func_150B5CC8(void *arg0) {
    func_150B5CA4(arg0);
    func_1514933C(arg0);
}

void func_150B5CF4(void *arg0) {
    func_150B5CA4(arg0);
    func_15149368(arg0);
}

void func_150B5D20(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            node_destroy(arg0);
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
