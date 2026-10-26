#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_1515D5F8
s32 func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);

void func_1515F61C(f32, s32);

f32 func_1515F578(s16 *, s32);

s32 func_1505D024();

void func_1515FDC0(s32 arg0, s32 arg1) {
    f32 s;
    f32 r;
    f32 g;
    f32 b;
    u8 c[3];
    c[0] = ((u8 *)&D_800DCD20)[0];
    c[1] = ((u8 *)&D_800DCD20)[1];
    c[2] = ((u8 *)&D_800DCD20)[2];
    s = sinf(D_800DCDA0);
    r = (s * 29.5f) + 127.5f;
    g = (s * 71.0f) + 109.0f;
    b = (s * 26.0f) + 26.0f;
    D_800DCDA0 += 0.071f * D_800BE9A4;
    D_800DCDA0 = func_15144B68(D_800DCDA0);
    if (r != D_800DCD94) {
        D_800DCD94 += (r - D_800DCD94) * 0.5f;
        c[0] = D_800DCD94;
    }
    if (g != D_800DCD98) {
        D_800DCD98 += (g - D_800DCD98) * 0.5f;
        c[1] = D_800DCD98;
    }
    if (b != D_800DCD9C) {
        D_800DCD9C += (b - D_800DCD9C) * 0.5f;
        c[2] = D_800DCD9C;
    }
    func_1515D4D4(c[0], c[1], c[2], 0U);
}

#ifdef NON_MATCHING
// effect_noop_check: P237. Does nothing: the asm only loads obj +0x3B and arg1 +0x1C and tests them (an empty if,
// probably a stripped debug check). No caller reads v0 (no jal callers; v0 is a load or garbage).
void func_151600E0(u8 *obj, u8 *arg1) {
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18D5D0/func_151600E0.s")
#endif

void func_15160104(u8 *arg0, s32 arg1) {
    func_1505D024(arg0, 0x6002D, *(u16 *)(arg0 + 0x7A), -1);
}

u8 *scene_node_find_type2e(s32);

void func_15160134(u8 *arg0, s32 arg1) {
    s32 pad; // fakematch: unused local moves v to sp18
    struct127 *v = NULL;
    u8 *t;
    s32 a3;
    t = scene_node_find_type2e(arg1);
    if (t != NULL) {
        v = *(struct127 **)(t + 0x98);
    }
    if (v != NULL) {
        a3 = v - D_800CC2D0;
    } else {
        a3 = -1;
    }
    func_1505D024(arg0, 0x6002E, *(u16 *)(arg0 + 0x7A), a3);
}

void func_151601A4(s32 arg0, s32 arg1) {
    func_1505D024(arg0, 0x33, 0xC000, -1);
}

s32 func_1507CD64(struct127 *, s32);
s32 func_150ADE40(s16, s16, s32, s32);
s32 object_hit_effects(struct127 *, s32, s32, s32, s32, s32, s32, s32);
void func_151601D0(struct127 *arg0, u8 *arg1) {
    s32 pad[2]; // fakematch: frame
    f32 scale;
    f32 dist; // fakematch: assigned inside the comparison

    if (arg0->unk31C != NULL && arg0->unk31C->unk120 == 0) {
        if (*(u32 *)(arg1 + 0x1C) != 0) {
            scale = *(u32 *)(arg1 + 0x1C) * 0.01f;
            if (func_150ADE40(*(s16 *)(arg1 + 0), *(s16 *)(arg1 + 4), arg0->x_position, arg0->z_position) < (dist = *(s16 *)(arg1 + 6) * scale - arg0->unkE4)) {
                return;
            }
        }
        func_1505D024(arg0, 0x2F, 0, -1);
        object_hit_effects(arg0, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(arg0);
        func_1507CD64(arg0, 6);
    }
}
