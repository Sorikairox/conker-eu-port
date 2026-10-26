#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 particle_emitter_spawn(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, s32, s32);

/* was func_1518A560 */
s32 bone_effect_spawn(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    s32 sp34;
    s32 temp_v0;

    (*(s8 *)((u8 *)arg1 + 0x58)) = 0xB;
    temp_v0 = particle_emitter_spawn(arg1, 0x80, arg0, arg3 & 0xFF, (s32) arg4, (s32) arg5, (s32) arg6, -1, 0xFF, 1);
    if (temp_v0 != 0) {
        sp34 = temp_v0;
        memcpy(temp_v0 + 0x170, arg2, 0x20);
        return sp34;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/bone_effect_spawn.s")
#endif
#ifdef NON_MATCHING
/* P143 */
extern s32 (*D_8008D940[])(u8 *, u8 *, s32);
// effect_follow_bone: update handler (D_8008A058 slot 2) that keeps an effect attached to a model bone. The
// attachment at +0x170 holds two local points (+0x170, +0x17C), the model (+0x188, looked up once from the id
// +0x18D with obj_find_by_setup_id), the bone (+0x18C) and an optional visibility check (+0x18E, index into D_8008D940,
// -1 = none). Ends (0) when the model is missing, gone (+0) or reused for another id (+0x3B); a failing check also
// ends it, a hidden one (*visible == 0) skips the update. With bone matrices (+0x1D4) both points are transformed
// to +0x34 and +0x40 and flag 2 set (flag 4 cleared); without them flag 2 is cleared.
/* was func_1518A604 */
s32 effect_follow_bone(u8 *fx) {
    u8 *att = fx + 0x170;
    u8 *model;
    u8 *bones;
    f32 (*mtx)[4];
    s32 check;
    u8 visible;

    if (*(u8 **)(fx + 0x188) == NULL) {
        model = (u8 *)obj_find_by_setup_id(att[0x1D]);
        *(u8 **)(att + 0x18) = model;
        if (model == NULL) {
            return 0;
        }
    }
    model = *(u8 **)(att + 0x18);
    if (*(s32 *)model == 0 || att[0x1D] != model[0x3B]) {
        return 0;
    }
    check = *(s8 *)(att + 0x1E);
    if (check != -1) {
        if (D_8008D940[check](fx, &visible, check) == 0) {
            return 0;
        }
        if (!visible) {
            return 1;
        }
        model = *(u8 **)(att + 0x18);
    }
    bones = *(u8 **)(model + 0x1D4);
    if (bones != NULL) {
        mtx = (f32 (*)[4])(bones + (att[0x1C] << 6));
        mtxf_transform_point(mtx, *(f32 *)(att + 0x0), *(f32 *)(att + 0x4), *(f32 *)(att + 0x8),
                      (f32 *)(fx + 0x34), (f32 *)(fx + 0x38), (f32 *)(fx + 0x3C));
        mtxf_transform_point(mtx, *(f32 *)(att + 0xC), *(f32 *)(att + 0x10), *(f32 *)(att + 0x14),
                      (f32 *)(fx + 0x40), (f32 *)(fx + 0x44), (f32 *)(fx + 0x48));
        *(s32 *)(fx + 0x58) |= 2;
        *(s32 *)(fx + 0x58) &= ~4;
    } else {
        *(s32 *)(fx + 0x58) &= ~2;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/effect_follow_bone.s")
#endif

extern f32 D_800A77A0;
extern f32 D_800A77A4;
extern f32 D_800A77A8;
/* was func_1518A784 */
s32 bone_effect_check_model_state(u8 *arg0, u8 *arg1) {
    s32 off; // fakematch: offset in a variable keeps v = arg0 + 0x110 in a register
    u8 *v;
    f32 f;

    off = 0x110;
    switch (*(u8 *)(*(u8 **)(arg0 + 0x188) + 0x68) - 0xF) {
    default:
        f = D_800A77A0;
        v = arg0 + off;
        *(f32 *)(v + 0x18) = f;
        *(f32 *)(v + 0x1C) = f;
        arg0[0x2A] = 0;
        arg0[0x29] = 0;
        arg0[0x28] = 0xFF;
        *arg1 = 1;
        break;
    case 0:
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
        break;
    case 1:
        f = D_800A77A4;
        v = arg0 + off;
        *(f32 *)(v + 0x18) = f;
        *(f32 *)(v + 0x1C) = f;
        arg0[0x28] = 0x80;
        arg0[0x29] = 0;
        arg0[0x2A] = 0;
        *arg1 = 1;
        break;
    case 2:
        f = D_800A77A8;
        v = arg0 + off;
        *(f32 *)(v + 0x18) = f;
        *(f32 *)(v + 0x1C) = f;
        arg0[0x28] = 0xFF;
        arg0[0x29] = 0;
        arg0[0x2A] = 0;
        *arg1 = 1;
        break;
    }
    return 1;
}

/* was func_1518A858 */
s32 bone_effect_check_flag6a(u8 *arg0, u8 *arg1) {
    if ((*(u8 **)(arg0 + 0x188))[0x6A] != 0) {
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

/* was func_1518A894 */
s32 bone_effect_check_flag6f(u8 *arg0, u8 *arg1) {
    if ((*(u8 **)(arg0 + 0x188))[0x6F] == 0) {
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

/* was func_1518A8D0 */
void bone_effect_on_model_swap(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x170;
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(p + 0x18)) {
            *(s32 *)(p + 0x18) = arg1[1];
            p[0x1D] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(p + 0x18)) {
            *(s32 *)(p + 0x18) = arg1[0];
            p[0x1D] = ((u8 *)arg1)[8];
        }
    }
}
