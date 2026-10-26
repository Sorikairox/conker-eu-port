#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 tracer_tick_life(s32 arg0, u8 *arg1, f32 arg2);
void tracer_move(u8 *arg0, u8 *arg1, f32 arg2);
s32 tracer_check_hit_step(u8 *arg0, u8 *arg1, f32 arg2);
void tracer_ease_values(s32 arg0, u8 *arg1, s32 arg2);
s32 memcpy(s32, s32, s32);
#endif
// hoisted forward declaration(s) for tracer_tick_life
extern void (*D_8008FF70[])(s32);


#ifdef NON_MATCHING
s32 sound_calc_pan_from_xz(f32, f32, u32);
void music_post_event_request(u32, s32);
s32 floor_flags_surface_type(s32);

/* was func_151C2600 */
void hit_spark_sound_play(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 arg4) {
    struct {
        s32 u48;
        s32 u4C;
    } sp;
    s32 sp40;
    f32 sp34;
    f32 temp_f0;
    s16 temp_v0;
    s16 temp_v0_2;
    u8 *temp_v1;

    if (arg0 != NULL) {
        if ((D_800BE616 != 0) || (temp_v1 = (*(u8 **)((u8 *)arg0 + 0x318)), (temp_v1 == NULL))) {
            temp_v0 = (*(s16 *)((u8 *)D_800B0DF0 + 0x2C));
            if ((temp_v0 == 0x24) || (temp_v0 == 0x13) || (temp_v0 == 0x4D) || (temp_v0 == 0x85) || (temp_v0 == 0x93)) {
                sound_source_mix((s32) (*(f32 *)((u8 *)arg1 + 0)), (s32) (*(f32 *)((u8 *)arg1 + 4)), (s32) (*(f32 *)((u8 *)arg1 + 8)), 0x7FFF, 0x3E8, 0x64, &sp.u4C, &sp.u48, NULL);
                if ((u32) sp.u48 >= 0x1001U) {
                    sp.u48 = (s32) ((u32) sp.u48 >> 7);
                    music_post_event_request(8, (floor_flags_surface_type(arg3) + 1) | (sp.u48 << 8) | (sp.u4C << 0x10));
                }
            }
        } else {
            temp_v0_2 = (*(s16 *)((u8 *)D_800B0DF0 + 0x2C));
            if ((temp_v0_2 == 0x24) || (temp_v0_2 == 0x13)) {
                temp_f0 = 255.0f - (arg4 * 0.1f);
                if (temp_f0 > 16.0f) {
                    sp34 = temp_f0;
                    sp40 = sound_calc_pan_from_xz((*(f32 *)((u8 *)arg2 + 0)), (*(f32 *)((u8 *)arg2 + 8)), (u32) ((*(f32 *)((u8 *)temp_v1 + 0x3A0)) * 40.743664f));
                    music_post_event_request(8, (floor_flags_surface_type(arg3) + 1) | ((s32) temp_f0 << 8) | (sp40 << 0x10));
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/hit_spark_sound_play.s")
#endif
#ifdef NON_MATCHING
s32 vec3_normalize_len(u8 *, s32 *, s32, s32);
s32 tracer_hit_update(s32, s32 *, u8 *, s32 *, s32 *, f32, s32, u8 *, s32 *, s8 *, s32, f32, u8 *, s32, s32, s32, s32, s32);
s32 objects_hit_by_segment(u8 *, s32 *, u8 *, s8, s32);

/* was func_151C284C */
u8 *tracer_spawn(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, u8 argB, u8 *argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, s8 arg13, s32 arg14, f32 arg15, u8 arg16, s8 arg17, s32 arg18, u8 arg19, s32 arg1A) {
    struct {
        s32 u78;
        u8 pad7C[0xB];
        u8 u87;
        s32 u88;
        u8 pad8C[0x8];
        s8 u94;
        u8 pad95[0x3];
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        s32 uBC;
        u8 padC0[0x34];
        s32 uF4;
        s32 uF8;
        s32 uFC;
        u8 pad100[0x20];
        s32 u120;
        u8 * u124;
        u8 u128;
        u8 pad129[0x3];
        f32 u12C;
        s8 u130;
        u8 pad131[0x1];
        s16 u132;
        s8 u134;
        s8 u135;
        u8 pad136[0x2];
        s32 u138;
        s8 u13C;
        u8 pad13D[0x3];
        s32 u140;
        s8 u144;
        s8 u145;
        s16 u146;
        s16 u148;
        u8 pad14A[0x2];
        s32 u14C;
        s32 u150;
        s8 u154;
        s8 u155;
        s8 u156;
        s8 u157;
        f32 u158;
        f32 u15C;
        s32 u160;
        u8 pad164[0x8];
        f32 u16C;
        f32 u170;
        f32 u174;
        f32 u178;
        f32 u17C;
        f32 u180;
        s32 u184;
        u8 u188;
        s8 u189;
        s8 u18A;
        s8 u18B;
        u8 pad18C[0x4];
        u8 u190;
        u8 pad191[0xB];
        u8 * u19C;
    } sp;
    u8 sp77;
    u8 sp67;
    u8 *sp50;
    s32 *var_a1;
    s32 *var_a3_2;
    s32 *var_v0_3;
    s32 var_a0;
    s32 var_a3;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 temp_t1;
    u8 var_t1;
    u8 *var_a0_2;

    sp.u87 = 0;
    var_v0 = arg4 != 0;
    var_a0 = 0;
    if (var_v0 != 0) {
        var_v0 = arg3 != NULL;
    }
    temp_t1 = var_v0 & 0xFF;
    if (var_v0 & 0xFF) {
        (*(s32 *)((u8 *)(&sp.u78) + 0)) = (s32) (*(s32 *)((u8 *)arg3 + 0));
        (*(s32 *)((u8 *)(&sp.u78) + 4)) = (s32) (*(s32 *)((u8 *)arg3 + 4));
        (*(s32 *)((u8 *)(&sp.u78) + 8)) = (s32) (*(s32 *)((u8 *)arg3 + 8));
    }
    if (argE != 0) {
        var_a0 = 4;
    }
    var_v1 = 0;
    if (arg12 != 0) {
        var_v1 = 2;
    }
    var_a3 = 0;
    if (arg11 != 0) {
        var_a3 = 1;
    }
    var_v0_2 = 0;
    if (argF != 0) {
        var_v0_2 = 8;
    }
    sp.u94 = var_v0_2 | var_a3 | var_v1 | var_a0;
    sp.u140 = 0;
    sp77 = temp_t1;
    sp.u13C = arg17;
    sp.u130 = arg13;
    sp.u138 = arg14;
    var_t1 = temp_t1;
    if ((u32) (random_int() & 0xFF) < arg10) {
        sp.u134 = 1;
    } else {
        sp.u134 = 0;
    }
    sp.u132 = 0;
    sp.u135 = 0;
    if ((arg2 != NULL) && (arg3 != NULL)) {
        if (var_t1 == 0) {
            if (vec3_normalize_len(arg3, &sp.u78, 0, 0) != 0) {
                var_t1 = 1;
                goto block_21;
            }
            return NULL;
        }
block_21:
        var_a0_2 = arg2;
        var_a1 = &sp.u78;
        goto block_27;
    }
    if (arg1 != NULL) {
        sp77 = var_t1;
        var_t1 = sp77;
        if (vec3_normalize_len(arg1, &sp.u88, 0, 0) != 0) {
            sp.u87 = 1;
            goto block_26;
        }
        return NULL;
    }
block_26:
    var_a0_2 = arg0;
    var_a1 = &sp.u88;
block_27:
    var_t0 = -1;
    if (argE != 0) {
        sp77 = var_t1;
        var_t0 = objects_hit_by_segment(var_a0_2, var_a1, argC, arg17, 0);
    }
    if (sp.u87 != 0) {
        var_a3_2 = &sp.u88;
    } else {
        var_a3_2 = NULL;
    }
    if (var_t1 != 0) {
        var_v0_3 = &sp.u78;
    } else {
        var_v0_3 = NULL;
    }
    sp.u140 = var_t0;
    if (tracer_hit_update(arg5, &sp.uBC, arg0, var_a3_2, &sp.u120, arg7, (s32) argD, arg2, var_v0_3, &sp.u94, 3, argA, argC, (s32) arg17, (s32) argE, (s32) argF, var_t0, 0) == 0) {
        return NULL;
    }
    sp.u98 = sp.uF4 * arg6;
    sp.u9C = sp.uF8 * arg6;
    sp.uA0 = sp.uFC * arg6;
    sp.uA4 = 0.0f;
    sp.uB0 = sp.uF4 * arg9;
    sp.uA8 = 0.0f;
    sp.uAC = 0.0f;
    sp.uB4 = sp.uF8 * arg9;
    sp.u124 = argC;
    sp.uB8 = sp.uFC * arg9;
    if (argC != NULL) {
        sp.u128 = (*(u8 *)((u8 *)argC + 0x3B));
    } else {
        sp.u128 = 0x63;
    }
    sp.u144 = 0x41;
    sp.u12C = arg6;
    sp.u145 = 4;
    sp.u146 = 0x4503;
    sp.u148 = 0x12C;
    sp.u14C = 0;
    sp.u150 = 0;
    sp.u154 = 0;
    sp.u155 = 0;
    sp.u156 = 0;
    sp.u157 = 0xFF;
    sp.u189 = 0xFF;
    sp.u15C = arg9;
    sp.u188 = argB;
    sp.u158 = arg8;
    (*(s32 *)((u8 *)(&sp.u160) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u160) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u160) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u16C = 0.0f;
    sp.u170 = 0.0f;
    sp.u174 = 0.0f;
    sp.u178 = 0.0f;
    sp.u17C = 0.0f;
    sp.u180 = 0.0f;
    sp.u184 = 0xC04C0008;
    sp.u18A = 0;
    sp.u18B = 0;
    sp.u190 = arg16;
    temp_v0 = effect3d_spawn_full(&sp.u144, (s32) ((u8 *)&D_800A4AA0), 0x16U, 0U, 0U, 0x14U, 0U, 0, 0, arg18 + 0xB0, (u8) (s32) arg19, arg1A);
    sp.u19C = temp_v0;
    if (temp_v0 != NULL) {
        temp_a0 = temp_v0 + 0x110;
        sp67 = 0;
        sp50 = temp_a0;
        memcpy(temp_a0, &sp.u94, 0xB0);
        tracer_ease_values(sp.u19C, sp50, (s32) arg15);
        if (tracer_check_hit_step(sp.u19C, sp50, arg15) == 0) {
            sp67 = 1;
        }
        tracer_move(sp.u19C, sp50, arg15);
        if (tracer_tick_life((s32) sp.u19C, sp50, arg15) == 0) {
            sp67 = 1;
        }
        if (sp67 != 0) {
            node_destroy((struct102 *) sp.u19C);
            return NULL;
        }
        goto block_47;
    }
block_47:
    return sp.u19C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/tracer_spawn.s")
#endif
#ifdef NON_MATCHING
s32 sound_calc_pan_volume(s32, s32, s32, f32, s32, s32, s32, s32, s32, s32 *, s32 *, s32);
extern s32 D_8008FF88;

/* was func_151C2CE4 */
s8 tracer_update(u8 *arg0) {
    struct {
        s32 uA4;
        s32 uA8;
        u8 padAC[0x1C];
        s32 uC8;
        struct108 * uCC;
        u8 padD0[0x7];
        s8 uD7;
    } sp;
    f32 sp70;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;
    s32 temp_f6_2;
    s32 temp_f6_3;
    s32 temp_f6_4;
    s32 temp_v0;
    s8 var_v1;
    struct108 *var_a0;
    struct108 *var_t0;
    u16 temp_a0;
    u16 temp_a2;
    u8 *temp_s0;
    u8 *temp_a3;

    temp_s0 = arg0 + 0x110;
    sp.uD7 = 1;
    tracer_ease_values(arg0, temp_s0, D_800BE9E4);
    if (tracer_check_hit_step(arg0, temp_s0, D_800BE9A4) == 0) {
        sp.uD7 = 0;
    }
    tracer_move(arg0, temp_s0, D_800BE9A4);
    if (tracer_tick_life((s32) arg0, temp_s0, D_800BE9A4) == 0) {
        sp.uD7 = 0;
    }
    if (((*(u8 *)((u8 *)(&arg0[0x110]) + 0xA0)) != 0) && (sp.uD7 == 1)) {
        sp.uC8 = 0;
        temp_a0 = (*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E));
        if (temp_a0 == 0) {
            sp.uCC = NULL;
            temp_v0 = random_int();
            var_t0 = sp.uCC;
            var_v1 = 0;
            if (D_80082FA0 >= 0) {
                temp_a3 = (u8 *) &D_8008FF88 + (temp_v0 & 7) * 4;
                temp_a2 = (*(u16 *)((u8 *)temp_a3 + 2));
                var_a0 = D_800DBFF0;
                temp_f18 = (*(f32 *)((u8 *)(&arg0[0x110]) + 0x98));
                sp70 = (f32) temp_a2 * temp_f18;
loop_9:
                temp_f8 = var_a0->unk2FC;
                temp_f6 = var_a0->unk300;
                temp_f12 = var_a0->unk2F8 - (*(f32 *)((u8 *)arg0 + 0x34));
                var_t0 = var_a0;
                var_a0 += 0x9A0;
                temp_f14 = temp_f8 - (*(f32 *)((u8 *)arg0 + 0x38));
                temp_f16 = temp_f6 - (*(f32 *)((u8 *)arg0 + 0x3C));
                temp_f2 = ((*(f32 *)((u8 *)(&arg0[0x110]) + 0x60)) * temp_f12) + (temp_f14 * (*(f32 *)((u8 *)(&arg0[0x110]) + 0x64))) + (temp_f16 * (*(f32 *)((u8 *)(&arg0[0x110]) + 0x68)));
                if ((temp_f2 < sp70) && (((f32) (temp_a2 - 0xA) * temp_f18) < temp_f2) && (temp_f0 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16)), (temp_f0 != 0.0f)) && (temp_f0 < ((*(f32 *)((u8 *)(&arg0[0x110]) + 0x8C)) * temp_f18)) && ((temp_f2 / temp_f0) > 0.9f)) {
                    sp.uC8 = (s32) (*(u16 *)((u8 *)temp_a3 + 0));
                    (*(s8 *)((u8 *)(&arg0[0x110]) + 0xA1)) = var_v1;
                } else {
                    var_v1 += 1;
                    var_t0 = NULL;
                    if (D_80082FA0 < var_v1) {

                    } else {
                        goto loop_9;
                    }
                }
            }
        } else {
            sp.uCC = NULL;
            var_t0 = NULL;
            if (sound_voice_is_playing(temp_a0) != 0) {
                var_t0 = &D_800DBFF0[(*(u8 *)((u8 *)(&arg0[0x110]) + 0xA1))];
            } else {
                (*(s8 *)((u8 *)(&arg0[0x110]) + 0xA0)) = 0;
            }
        }
        if (var_t0 != NULL) {
            sp.uA8 = 0x40;
            temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_t0->unk2F8);
            temp_f6_3 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_t0->unk2FC);
            temp_f6_4 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_t0->unk300);
            sound_calc_pan_volume(temp_f6_2, temp_f6_3, temp_f6_4, var_t0->unk380, temp_f6_2, temp_f6_3, temp_f6_4, 0x2710, 0x270F, &sp.uA8, &sp.uA4, 0);
            if (sp.uC8 != 0) {
                (*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E)) = sound_play_2d(sp.uC8, 0x6590U, sp.uA8 & 0x7F, 0, (u8) (sp.uA8 & 0x80));
            } else {
                sound_voice_set_param((*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E)), 4, sp.uA8 & 0x7F);
                sound_voice_set_param((*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E)), 0x100, sp.uA8 & 0x80);
            }
        }
    }
    return sp.uD7;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/tracer_update.s")
#endif
#ifdef NON_MATCHING
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);

/* was func_151C3080 */
s16 *tracer_draw(u8 *arg0, s16 arg1) {
    struct {
        u8 u53;
        u8 pad54[0x4];
        s16 * u58;
        s16 * u5C;
        u8 pad60[0x4];
        f32 u64;
        u8 pad68[0xC];
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0x18];
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
    } sp;
    u8 *sp48;
    s32 sp44;
    f32 sp38;
    f32 sp34;
    f32 sp28;
    f32 *temp_v0;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_t2;
    s16 *temp_t2_2;
    s16 *temp_t6;
    s32 temp_a1;
    u8 *temp_v1;
    u8 *temp_v1_2;

    vtx_slot_buffer_get(arg0 + 0x100, arg1, 0x40, &sp.u5C, &sp.u53);
    sp.u58 = sp.u5C;
    if (sp.u5C != NULL) {
        if (sp.u53 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp44 = temp_a1;
            sp48 = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0 = camera_get_pos((s32) arg1);
        temp_v1_2 = arg0 + 0x110;
        (*(f32 *)((u8 *)(&sp.uA4) + 0)) = (*(f32 *)((u8 *)arg0 + 0x34));
        (*(f32 *)((u8 *)(&sp.uA4) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(f32 *)((u8 *)(&sp.uA4) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
        temp_f16 = (*(f32 *)((u8 *)arg0 + 0x34)) - (*(f32 *)((u8 *)temp_v1_2 + 0x10));
        temp_f18 = (*(f32 *)((u8 *)arg0 + 0x38)) - (*(f32 *)((u8 *)temp_v1_2 + 0x14));
        temp_f4 = (*(f32 *)((u8 *)arg0 + 0x3C)) - (*(f32 *)((u8 *)temp_v1_2 + 0x18));
        temp_f2 = temp_f16 - sp.uA4;
        sp.uA0 = temp_f4;
        temp_f12 = temp_f18 - sp.uA8;
        temp_f10 = ((temp_f2 * 0.5f) + sp.uA4) - (*(f32 *)((u8 *)temp_v0 + 0));
        sp.u74 = temp_f10;
        temp_f8 = ((temp_f12 * 0.5f) + sp.uA8) - (*(f32 *)((u8 *)temp_v0 + 4));
        sp.u78 = temp_f8;
        temp_f14 = temp_f4 - sp.uAC;
        sp28 = temp_f10;
        sp.u9C = temp_f18;
        temp_f4_2 = ((temp_f14 * 0.5f) + sp.uAC) - (*(f32 *)((u8 *)temp_v0 + 8));
        sp.u98 = temp_f16;
        sp.u7C = temp_f4_2;
        temp_f18_2 = (temp_f12 * temp_f4_2) - (temp_f8 * temp_f14);
        temp_f16_2 = (temp_f14 * sp28) - (temp_f4_2 * temp_f2);
        sp38 = temp_f16_2;
        temp_f8_2 = (temp_f2 * temp_f8) - (sp28 * temp_f12);
        sp34 = temp_f8_2;
        temp_f0 = (temp_f18_2 * temp_f18_2) + (temp_f16_2 * temp_f16_2) + (temp_f8_2 * temp_f8_2);
        sp.u64 = temp_f0;
        if (temp_f0 == 0.0f) {
            var_f16 = 0.0f;
            var_f12 = 0.0f;
            var_f14 = 0.0f;
        } else {
            temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(temp_f0);
            var_f12 = temp_f18_2 * temp_f2_2;
            var_f14 = sp38 * temp_f2_2;
            var_f16 = sp34 * temp_f2_2;
        }
        (*(s16 *)((u8 *)sp.u5C + 0)) = (s16) (s32) (sp.uA4 - var_f12);
        (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (sp.uA8 - var_f14);
        (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (sp.uAC - var_f16);
        (*(u8 *)((u8 *)sp.u5C + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x5C));
        (*(s16 *)((u8 *)sp.u5C + 6)) = 0;
        temp_t2 = (s16 *) ((u8 *) sp.u5C + 0x10);  /* P270: byte offset (was s16 stride) */
        sp.u5C = temp_t2;
        *temp_t2 = (s16) (s32) (sp.u98 - var_f12);
        (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (sp.u9C - var_f14);
        (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (sp.uA0 - var_f16);
        (*(u8 *)((u8 *)sp.u5C + 0xF)) = 0U;
        (*(s16 *)((u8 *)sp.u5C + 6)) = 0;
        temp_t2_2 = (s16 *) ((u8 *) sp.u5C + 0x10);  /* P270: byte offset (was s16 stride) */
        sp.u5C = temp_t2_2;
        (*(s8 *)((u8 *)temp_t2_2 + 0xF)) = 0;
        (*(s16 *)((u8 *)temp_t2_2 + 6)) = 0;
        (*(s16 *)((u8 *)temp_t2_2 + 0)) = (s16) (s32) (sp.u98 + var_f12);
        (*(s16 *)((u8 *)temp_t2_2 + 2)) = (s16) (s32) (sp.u9C + var_f14);
        (*(s16 *)((u8 *)temp_t2_2 + 4)) = (s16) (s32) (sp.uA0 + var_f16);
        temp_t6 = (s16 *) ((u8 *) temp_t2_2 + 0x10);  /* P270: byte offset (was s16 stride) */
        sp.u5C = temp_t6;
        *temp_t6 = (s16) (s32) (sp.uA4 + var_f12);
        (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (sp.uA8 + var_f14);
        (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (sp.uAC + var_f16);
        (*(u8 *)((u8 *)sp.u5C + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x5C));
        (*(s16 *)((u8 *)sp.u5C + 6)) = 0;
        return sp.u58;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/tracer_draw.s")
#endif
/* was func_151C33FC */
s32 tracer_filter_not_self(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

/* was func_151C3444 */
s32 tracer_filter_not_self_player(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    return 1;
}

/* was func_151C34A0 */
void tracer_hit_callback(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    object_take_hit(arg0, arg1, arg3, arg4, arg5, *(s32 *)(arg2 + 0x1B4), arg2 + 0x170, arg2[0xC], arg2[1]);
}

#ifdef NON_MATCHING
s32 cam_sprite_puff_spawn(f32, s32, u8 *, u8 *, s32, s32, s32, s32, s32, s32);
s32 emit_streaks_from_spec(s32 *, u8, s32);
extern u8 D_800DCE50;
extern f32 D_800DCE54;

/* was func_151C34F8 */
void tracer_impact_sparks(u8 *arg0) {
    struct {
        s32 u54;
        s32 u58;
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s16 u86;
        s32 u88;
        s32 u8C;
        s16 u90;
        s16 u92;
        s16 u94;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        s8 u9A;
        s8 u9B;
        s8 u9C;
        s8 u9D;
        s8 u9E;
        s8 u9F;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        s32 uB4;
        s16 uB8;
        s16 uBA;
        s16 uBC;
        s8 uBE;
        u8 padBF[0x1];
        f32 uC0;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        s16 uD6;
        s8 uD8;
    } sp;
    f32 sp4C;
    u8 *sp48;
    u8 *sp44;
    u8 *temp_a3;
    u8 *temp_v1;

    sp4C = random_float();
    temp_v1 = arg0 + 0x110;
    temp_a3 = temp_v1 + 0x30;
    sp44 = temp_a3;
    sp48 = temp_v1;
    cam_sprite_puff_spawn((sp4C * 30.0f) + 8.0f, 0xFF, temp_v1 + 0x6C, temp_a3, (random_int() % 46U) + 0x19, 1, 1, (*(s32 *)((u8 *)temp_v1 + 0x88)), (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    if (random_float() < (0.25300002f * D_800DCE54)) {
        sp.uD4 = 3;
        sp.uD5 = -1;
        sp48 = temp_v1;
        sp.uD6 = (random_int() % 7U) + 4;
        sp.uD8 = 0;
        sp.uC8 = (s32) (*(f32 *)((u8 *)temp_v1 + 0x30));
        sp.uCC = (s32) (*(f32 *)((u8 *)temp_v1 + 0x34));
        sp.uD0 = (s32) (*(f32 *)((u8 *)temp_v1 + 0x38));
        light_create_with_ctrl((Header *) &sp.uD4, (Header2 *) &sp.uC8, (random_int() % 9U) + 0xC, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        sp.u54 = 5 >> D_800DCE50;
        sp.u58 = 4 >> D_800DCE50;
        (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)sp44 + 0));
        (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)sp44 + 4));
        (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)sp44 + 8));
        sp.u86 = 0x50;
        sp.u88 = 3;
        sp.u84 = -0x3D;
        sp.u8C = 1;
        sp.u90 = 0xC;
        sp.u92 = 0xA;
        sp.u94 = 1;
        sp.u96 = 4;
        sp.u97 = 2;
        sp.u82 = 0xFF;
        sp.u9A = 0xFF;
        sp.u9B = 0xFF;
        sp.u99 = 0xFF;
        sp.u9C = 0xFF;
        sp.uA1 = 0xFF;
        sp.uA2 = 0xFF;
        sp.uA3 = 0xFF;
        sp.uA4 = 0xFF;
        sp.uA9 = 0xFF;
        sp.u70 = 0.0f;
        sp.u74 = 0.0f;
        sp.u80 = 0;
        sp.u98 = 3;
        sp.u9D = 0;
        sp.u9E = 0;
        sp.u9F = 0;
        sp.uA0 = 0;
        sp.uA5 = 0;
        sp.uA6 = 0;
        sp.uA7 = 0;
        sp.uA8 = 0;
        sp.uAA = 0;
        sp.uAB = 3;
        sp.uAC = 0x24;
        sp.uB0 = 0x200005;
        sp.uB4 = 0x60600;
        sp.uB8 = 0xA;
        sp.uBA = 0x19;
        sp.uBC = 1;
        sp.uBE = 0;
        sp.uC4 = -1;
        sp.uC5 = 0;
        sp.uC6 = -1;
        sp.uC7 = -1;
        sp.u68 = 8.25f;
        sp.u6C = 5.8599997f;
        sp.u78 = 7.0f;
        sp.u7C = 16.0f;
        sp.uC0 = 1.0f;
        emit_streaks_from_spec(&sp.u54, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/tracer_impact_sparks.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800AAE24[4]; /* the ember emitter's 4 float parameters (D_800AAE24..D_800AAE30) */
s32 emit_streaks_from_spec(s32 *, u8, s32);
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 random_int(void);
f32 random_float(void);

// fire_embers_spawn: the ember burst of a fire at `pos` (room `room`, owner `owner`): an ember emitter
// (emit_streaks_from_spec, type 5 / 7, 4 parameters from D_800AAE24, sizes 15 / 30, colour block, handlers 0x200005 /
// 0x60600), one glow sprite (particle_spawn_ex: texture 0x2B of set 0x4403, 6..12 frames, half size 106..302, fade from
// 3 at rate 0x55, random flip flags 0x40 / 0x80) and a light flash (light_create_with_ctrl: 6..12 frames, type 5 or 6) at the
// truncated position.
/* was func_151C384C */
void fire_embers_spawn(void *arg0, u8 room, s32 owner) {
    f32 *pos = arg0;
    struct {
        s32 type;       /* +0x00: 5 */
        s32 subtype;    /* +0x04: 7 */
        f32 pos[3];     /* +0x08 */
        f32 param[4];   /* +0x14: D_800AAE24..30 */
        f32 sizeA;      /* +0x24: 15 */
        f32 sizeB;      /* +0x28: 30 */
        s16 u2C;
        s16 u2E;
        s16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s16 u40;
        u8 u42;
        u8 u43;
        u8 u44;
        u8 u45[4];      /* +0x45 */
        u8 u49[4];
        u8 u4D[4];
        u8 u51[4];
        u8 u55;
        u8 u56;
        u8 u57;
        u8 u58;
        u8 pad59[3];    /* not written */
        s32 handlers;   /* +0x5C: 0x200005 */
        s32 u60;
        s16 u64;
        s16 u66;
        s16 u68;
        u8 u6A;
        u8 pad6B;       /* not written */
        f32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
    } emit;
    struct {
        s32 handlers;   /* +0x00: 0x200005 */
        s32 u04;
        s16 texSet;     /* +0x08 */
        s16 life;       /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 color[4];    /* +0x14 */
        u8 u18[3];
        u8 alpha;       /* +0x1B */
        u8 u1C;
        u8 texture;     /* +0x1D */
        s16 fadeStart;  /* +0x1E */
        s16 fadeRate;   /* +0x20 */
        s16 u22;
        f32 u24;
        f32 halfW;      /* +0x28 */
        f32 halfH;      /* +0x2C */
        f32 pos[3];     /* +0x30 */
        f32 angle[3];   /* +0x3C */
        f32 vel[3];     /* +0x48 */
        f32 value;      /* +0x54 */
        s32 flags;      /* +0x58 */
        s32 u5C;        /* not written */
        u8 draw;        /* +0x60 */
        u8 update;      /* +0x61 */
        s8 blend;       /* +0x62 */
        s8 u63;
        s8 u64;
        u8 u65;
    } req;
    Header flash;
    Header2 at;
    s32 flipA;
    s32 flipB;
    f32 s;
    s32 i;

    emit.type = 5;
    emit.subtype = 7;
    emit.pos[0] = pos[0];
    emit.pos[1] = pos[1];
    emit.pos[2] = pos[2];
    emit.param[0] = D_800AAE24[0];
    emit.param[1] = D_800AAE24[1];
    emit.param[2] = D_800AAE24[2];
    emit.param[3] = D_800AAE24[3];
    emit.sizeA = 15.0f;
    emit.sizeB = 30.0f;
    emit.u2C = 0;
    emit.u2E = 0xFF;
    emit.u30 = -0x40;
    emit.u32 = 0x50;
    emit.u34 = 3;
    emit.u38 = 1;
    emit.u3C = 0x14;
    emit.u3E = 0xF;
    emit.u40 = 1;
    emit.u42 = 4;
    emit.u43 = 2;
    emit.u44 = 3;
    for (i = 0; i < 4; i++) {
        emit.u45[i] = 0xFF;
        emit.u49[i] = 0;
        emit.u4D[i] = 0xFF;
        emit.u51[i] = 0;
    }
    emit.u55 = 0xFF;
    emit.u56 = 0;
    emit.u57 = 3;
    emit.u58 = 0x24;
    emit.handlers = 0x200005;
    emit.u60 = 0x60600;
    emit.u64 = 8;
    emit.u66 = 0x1F;
    emit.u68 = 1;
    emit.u6A = 0;
    emit.u6C = 1.0f;
    emit.u70 = -1;
    emit.u71 = 0;
    emit.u72 = -1;
    emit.u73 = -1;
    emit_streaks_from_spec((s32 *) &emit, room, owner);

    req.texture = 0x2B;
    req.texSet = 0x4403;
    req.handlers = 0x200005;
    req.u04 = 0x20000;
    req.life = random_int() % 7U + 6;
    req.u0C = 0;
    req.u10 = 0;
    req.color[0] = 0xFF;
    req.color[1] = 0xFF;
    req.color[2] = 0xFF;
    req.color[3] = 0xFF;
    req.u18[0] = 0xFF;
    req.u18[1] = 0xFF;
    req.u18[2] = 0xFF;
    req.alpha = 0xFF;
    req.u1C = 0xFF;
    s = random_float() * 196.0f + 106.0f;
    req.halfH = s;
    req.halfW = s;
    req.pos[0] = pos[0];
    req.pos[1] = pos[1];
    req.pos[2] = pos[2];
    req.fadeStart = 3;
    req.fadeRate = 0x55;
    req.u22 = 1;
    req.angle[0] = 0.0f;
    req.angle[1] = 0.0f;
    req.angle[2] = 0.0f;
    req.vel[0] = 0.0f;
    req.vel[1] = 0.0f;
    req.vel[2] = 0.0f;
    req.value = 0.0f;
    req.u24 = 1.0f;
    flipA = (random_int() & 1) ? 0x40 : 0;
    flipB = (random_int() & 1) ? 0x80 : 0;
    req.flags = (flipB | 1) | flipA | 0xC200;
    req.draw = 6;
    req.update = 6;
    req.blend = -1;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 4;
    particle_spawn_ex((s32) &req, 1, 0, 0, room, owner);

    flash.unk0 = 3;
    flash.unk1 = -1;
    flash.unk2 = random_int() % 7U + 6;
    flash.unk4 = 0;
    at.unk0 = pos[0];
    at.unk4 = pos[1];
    at.unk8 = pos[2];
    light_create_with_ctrl(&flash, &at, (random_int() & 1) + 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, room, owner);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/fire_embers_spawn.s")
#endif

#ifdef NON_MATCHING
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

/* was func_151C3C88 */
void fire_embers_spawn_b(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u48;
        s32 u4C;
        s32 u50;
        s8 u54;
        s8 u55;
        s16 u56;
        s8 u58;
        u8 pad59[0x3];
        s32 u5C;
        s32 u60;
        s16 u64;
        s16 u66;
        s32 u68;
        s32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        s8 u75;
        s8 u76;
        s8 u77;
        s8 u78;
        s8 u79;
        s16 u7A;
        s16 u7C;
        s16 u7E;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[0x8];
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        s32 uB4;
        u8 padB8[0x4];
        s8 uBC;
        s8 uBD;
        s8 uBE;
        s8 uBF;
        s8 uC0;
        s8 uC1;
        u8 padC2[0xA];
        s32 uCC;
        s32 uD0;
        s32 uD4;
        u8 padD8[0x8];
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s16 uF8;
        s16 uFA;
        s16 uFC;
        s16 uFE;
        s32 u100;
        s32 u104;
        s16 u108;
        s16 u10A;
        s16 u10C;
        s8 u10E;
        s8 u10F;
        s8 u110;
        s8 u111;
        s8 u112;
        s8 u113;
        s8 u114;
        s8 u115;
        s8 u116;
        s8 u117;
        s8 u118;
        s8 u119;
        s8 u11A;
        s8 u11B;
        s8 u11C;
        s8 u11D;
        s8 u11E;
        s8 u11F;
        s8 u120;
        s8 u121;
        s8 u122;
        s8 u123;
        s8 u124;
        u8 pad125[0x3];
        s32 u128;
        s32 u12C;
        s16 u130;
        s16 u132;
        s16 u134;
        s8 u136;
        u8 pad137[0x1];
        f32 u138;
        s8 u13C;
        s8 u13D;
        s8 u13E;
        s8 u13F;
    } sp;
    s32 sp40;
    f32 temp_f16;
    s32 var_v0;
    s32 var_v1;

    sp.uCC = 8;
    sp.uD0 = 6;
    (*(f32 *)((u8 *)(&sp.uD4) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.uD4) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.uD4) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    sp.uFC = -0x40;
    sp.uFE = 0x50;
    sp.u100 = 3;
    sp.u108 = 0xF;
    sp.u10A = 0xA;
    sp.u10C = 1;
    sp.u10E = 4;
    sp.u10F = 2;
    sp.u112 = 0xFF;
    sp.u113 = 0xFF;
    sp.uE0 = 2.6f;
    sp.uFA = 0xFF;
    sp.u111 = 0xFF;
    sp.u114 = 0xFF;
    sp.u119 = 0xFF;
    sp.u11A = 0xFF;
    sp.u11B = 0xFF;
    sp.u11C = 0xFF;
    sp.u121 = 0xFF;
    sp.uF8 = 0;
    sp.u104 = 0;
    sp.u110 = 3;
    sp.u115 = 0;
    sp.u116 = 0;
    sp.u117 = 0;
    sp.u118 = 0;
    sp.u11D = 0;
    sp.u11E = 0;
    sp.u11F = 0;
    sp.u120 = 0;
    sp.u122 = 0;
    sp.u123 = 3;
    sp.u124 = 0x24;
    sp.u128 = 0x200005;
    sp.u12C = 0x60600;
    sp.u130 = 8;
    sp.u132 = 0x1F;
    sp.u134 = 1;
    sp.u136 = 0;
    sp.u13C = -1;
    sp.u13D = 0;
    sp.u13E = -1;
    sp.u13F = -1;
    sp.uE4 = 2.1699998f;
    sp.uE8 = -0.96900004f;
    sp.uEC = 0.71800005f;
    sp.uF0 = 10.0f;
    sp.uF4 = 8.0f;
    sp.u138 = 1.0f;
    emit_streaks_from_spec(&sp.uCC, arg1, arg2);
    sp.u79 = 0x2B;
    sp.u64 = 0x4403;
    sp.u5C = 0x200005;
    sp.u60 = 0x20000;
    sp.u66 = (random_int() % 5U) + 4;
    sp.u68 = 0;
    sp.u6C = 0;
    sp.u70 = 0xFF;
    sp.u71 = 0xFF;
    sp.u72 = 0xFF;
    sp.u73 = 0xFF;
    sp.u74 = 0xFF;
    sp.u75 = 0xFF;
    sp.u76 = 0xFF;
    sp.u77 = 0xFF;
    sp.u78 = 0xFF;
    temp_f16 = (random_float() * 60.0f) + 80.0f;
    sp.u88 = temp_f16;
    sp.u84 = temp_f16;
    (*(f32 *)((u8 *)(&sp.u8C) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.u8C) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.u8C) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    sp.u7A = 2;
    sp.u7C = 0x7F;
    sp.u7E = 1;
    sp.u98 = 0.0f;
    sp.u9C = 0.0f;
    sp.uA0 = 0.0f;
    sp.uA4 = 0.0f;
    sp.uA8 = 0.0f;
    sp.uAC = 0.0f;
    sp.uB0 = 0.0f;
    sp.u80 = 1.0f;
    var_v1 = 0;
    if (random_int() & 1) {
        var_v1 = 0x40;
    }
    sp40 = var_v1;
    if (random_int() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    sp.uB4 = var_v0 | 1 | var_v1 | 0xC200;
    sp.uBC = 6;
    sp.uBD = 6;
    sp.uBE = -1;
    sp.uBF = -1;
    sp.uC0 = -1;
    sp.uC1 = 4;
    particle_spawn_ex(&sp.u5C, 1, 0, 0, (s32) arg1, arg2);
    sp.u54 = 3;
    sp.u55 = -1;
    sp.u56 = (random_int() % 7U) + 6;
    sp.u58 = 0;
    sp.u48 = (s32) (*(f32 *)((u8 *)arg0 + 0));
    sp.u4C = (s32) (*(f32 *)((u8 *)arg0 + 4));
    sp.u50 = (s32) (*(f32 *)((u8 *)arg0 + 8));
    light_create_with_ctrl((Header *) &sp.u54, (Header2 *) &sp.u48, (random_int() & 1) + 5, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, (u8) (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/fire_embers_spawn_b.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800AADB0[6]; /* per-surface texture byte of the spark burst */
extern s32 D_800AADC8[6]; /* per-surface texture byte of the smoke puff */
extern u8 D_800AADE0[6][3]; /* per-surface debris colour A */
extern u8 D_800AADF4[6][3]; /* per-surface debris colour B */
extern u8 D_800AAE08[2][3]; /* the two flash colours */
extern f32 D_800AAE44;
extern f32 D_800AAE48;
extern f32 D_800AAE4C;
extern f32 D_800AAE50;
extern f32 D_800AAE54;
extern f32 D_800AAE58;
void emit_particle_burst_req(u8 *req, s32 tag, s32 room, s32 owner);

// impact_effects_spawn: the impact effects at object `obj`'s position (+0x140), chosen by level (D_800BE9F0) and the
// object's surface bits (+0x198 & 0x1F) as one of 6 surface types: each of 4 effects is spawned when a random number
// is below its chance: a spark burst (sprite_fx_spawn_cam_at, scale 15..30), a smoke puff (effect3d_spawn_full, moving along
// +0x140 - +0x170), a debris spray (emit_particle_burst_req, two per-surface colours, `debrisTag`) and a light flash
// (light_create_with_ctrl, one of 2 colours). Unknown surfaces (type 0) only keep the flash chance.
/* was func_151C40BC */
void surface_impact_effects(s32 arg0, f32 sparkChance, f32 smokeChance, f32 debrisChance, f32 flashChance, u8 sparkTag,
                   u8 debrisTag, u8 smokeTag) {
    u8 *obj = (u8 *) arg0;
    f32 *pos = (f32 *) (obj + 0x140);
    f32 *prev = (f32 *) (obj + 0x170);
    s32 level = D_800BE9F0;
    s32 surface = *(s32 *) (obj + 0x198) & 0x1F;
    s32 type;
    struct {
        s32 flags;      /* +0x00 */
        s16 life;       /* +0x04 */
        u8 texture;     /* +0x06 */
        u8 u07;
        s32 u08;
        s32 u0C;
        u8 color[6];    /* +0x10 */
        u8 u16;
        u8 blend;       /* +0x17 */
        s32 frames;     /* +0x18 */
        s32 pad1C;      /* not written */
        u8 tag;         /* +0x20 */
        u8 pad21;       /* not written */
        s16 u22;
        s16 u24;
    } spark;
    struct {
        u8 texture;     /* +0x00 */
        u8 u01;
        s16 texSet;     /* +0x02 */
        s16 life;       /* +0x04 */
        s16 pad06;      /* not written */
        s32 u08;
        s32 u0C;
        u8 color[4];    /* +0x10 */
        f32 grow;       /* +0x14 */
        f32 size;       /* +0x18 */
        f32 pos[3];     /* +0x1C */
        f32 vel[3];     /* +0x28 */
        f32 u34;
        f32 u38;
        f32 u3C;
        s32 flags;      /* +0x40 */
        u8 alpha;       /* +0x44 */
        u8 u45;
        u8 u46;
        u8 u47;
        s32 u48;
        u8 tag;         /* +0x4C */
        u8 pad4D[7];    /* not written */
        s16 u54;
        s16 u56;
    } smoke;
    struct {
        s16 type;       /* +0x00 */
        s16 u02;
        u8 u04;
        u8 pad05;       /* not written */
        s16 texSet;     /* +0x06 */
        s32 handlers;   /* +0x08 */
        s32 u0C;
        s16 u10;
        s16 u12;
        s32 u14;
        s32 u18;
        u8 colorA[4];   /* +0x1C */
        u8 colorB[4];   /* +0x20 */
        u8 u24;
        u8 u25;
        s16 u26;
        s16 u28;
        s16 u2A;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 pos[3];     /* +0x38 */
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 flags;      /* +0x5C */
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        u8 pad65[3];    /* not written */
        f32 u68;
    } debris;
    Header flash;
    Header2 at;
    u8 i;
    f32 s;

    if (level == 0x2B || level == 0x30) {
        type = (surface == 1) ? 3 : 4;
    } else if (surface == 0xB && level == 4) {
        type = 1;
    } else if ((surface == 1 || surface == 0xA) && level == 0xE) {
        type = 2;
    } else if (level == 0x34) {
        type = 3;
    } else if (level == 0x27) {
        type = 5;
    } else {
        type = 0;
        sparkChance = 0.0f;
        smokeChance = 0.0f;
        debrisChance = 0.0f;
    }

    if (random_float() < sparkChance) {
        s = random_float() * 15.0f + 15.0f;
        spark.texture = D_800AADB0[type];
        spark.u07 = 0;
        spark.flags = (D_800BE616 ? 0x20000 : 0) | 0xBF01;
        spark.life = random_int() % 61U + 60;
        spark.u08 = 0;
        spark.u0C = 0;
        spark.color[0] = random_int() % 56U + 200;
        spark.color[1] = 0xFF;
        spark.color[2] = 0;
        spark.color[3] = 0;
        spark.color[4] = 0;
        spark.color[5] = 0xFF;
        spark.frames = (((type == 4) ? 0x48 : 0x3B) << 16) + 2;
        spark.u16 = 0;
        spark.blend = (type == 4) ? 6 : 7;
        spark.u22 = 0x20;
        spark.u24 = 7;
        spark.tag = sparkTag;
        sprite_fx_spawn_cam_at((s32) &spark, 0, 0, (s32) (obj + 0x17C), pos[0], pos[1], pos[2], s, s, random_int() & 0xFF,
                      0, 0, 0, 0, obj[0xC], obj[1]);
    }

    if (random_float() < smokeChance) {
        smoke.texture = D_800AADC8[type];
        smoke.u01 = 0;
        smoke.texSet = 0x3B03;
        smoke.life = random_int() % 6U + 13;
        smoke.u08 = 0;
        smoke.u0C = 0;
        smoke.color[0] = 0xFF;
        smoke.color[1] = 0xFF;
        smoke.color[2] = 0xFF;
        smoke.color[3] = 0xFF;
        smoke.grow = random_float() * 5.0f + 7.0f;
        smoke.size = random_float() * 40.0f + 10.0f;
        smoke.pos[0] = pos[0];
        smoke.pos[1] = pos[1];
        smoke.pos[2] = pos[2];
        smoke.vel[0] = pos[0] - prev[0];
        smoke.vel[1] = pos[1] - prev[1];
        smoke.vel[2] = pos[2] - prev[2];
        smoke.u34 = D_800AAE44;
        smoke.u38 = 1.0f;
        smoke.u3C = D_800AAE48;
        smoke.flags = (D_800BE616 ? 0x40000000 : 0) | 0x08DC0009;
        smoke.alpha = random_int() % 76U + 180;
        smoke.u45 = 0xFF;
        smoke.u46 = 0;
        smoke.u47 = 7;
        smoke.u48 = 0;
        smoke.u54 = 8;
        smoke.u56 = 0x1F;
        smoke.tag = smokeTag;
        effect3d_spawn_full(&smoke, (s32) &D_800A4AA0, 0x22, 0, 0, 0x1C, 2, 0, 0, 0, obj[0xC], obj[1]);
    }

    if (random_float() < debrisChance) {
        debris.type = 5;
        debris.u02 = 0xF;
        debris.u04 = 0x6C;
        debris.texSet = 0x5103;
        debris.handlers = 0x200005;
        debris.u0C = 0;
        debris.u10 = 0x14;
        debris.u12 = 0xF;
        debris.u14 = 0;
        debris.u18 = 0;
        debris.colorA[0] = D_800AADE0[type][0];
        debris.colorA[1] = D_800AADE0[type][1];
        debris.colorA[2] = D_800AADE0[type][2];
        debris.colorA[3] = 0xFF;
        debris.colorB[0] = D_800AADF4[type][0];
        debris.colorB[1] = D_800AADF4[type][1];
        debris.colorB[2] = D_800AADF4[type][2];
        debris.colorB[3] = 0xE6;
        debris.u24 = 0x14;
        debris.u25 = 0xFF;
        debris.u26 = 0x19;
        debris.u28 = 0xA;
        debris.u2A = 0x1E;
        debris.u2C = D_800AAE4C;
        debris.u30 = 60.0f;
        debris.u34 = 65.0f;
        debris.pos[0] = pos[0];
        debris.pos[1] = pos[1];
        debris.pos[2] = pos[2];
        debris.u44 = 0;
        debris.u46 = -0x28;
        debris.u48 = 0xFF;
        debris.u4A = 0x28;
        debris.u4C = 9.0f;
        debris.u50 = 17.0f;
        debris.u54 = D_800AAE50;
        debris.u58 = D_800AAE54;
        debris.flags = (D_800BE616 ? 0x800000 : 0) | 0x40E07;
        debris.u60 = 0x10;
        debris.u61 = -1;
        debris.u62 = 8;
        debris.u63 = 6;
        debris.u64 = 1;
        debris.u68 = D_800AAE58;
        emit_particle_burst_req((u8 *) &debris, debrisTag, obj[0xC], obj[1]);
    }

    if (random_float() < flashChance) {
        flash.unk0 = 3;
        flash.unk1 = -1;
        flash.unk2 = random_int() % 6U + 3;
        flash.unk4 = 0;
        at.unk0 = pos[0];
        at.unk4 = pos[1];
        at.unk8 = pos[2];
        i = random_int() & 1;
        light_create_with_ctrl(&flash, &at, random_int() % 6U + 10, D_800AAE08[i][0], D_800AAE08[i][1], D_800AAE08[i][2],
                      0xFF, 0, 0, obj[0xC], obj[1]);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/surface_impact_effects.s")
#endif

#ifdef NON_MATCHING
/* was func_151C491C */
void tracer_ease_values(s32 arg0, u8 *arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f16;
    s32 var_a2;

    var_a2 = arg2;
    if (var_a2 > 0) {
        do {
            temp_f0 = (*(f32 *)((u8 *)arg1 + 0x10));
            temp_f12 = (*(f32 *)((u8 *)arg1 + 0x14));
            temp_f16 = (*(f32 *)((u8 *)arg1 + 0x18));
            var_a2 -= 1;
            (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)arg1 + 0x1C)) - temp_f0) * 0.228659f));
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) (temp_f12 + (((*(f32 *)((u8 *)arg1 + 0x20)) - temp_f12) * 0.228659f));
            (*(f32 *)((u8 *)arg1 + 0x18)) = (f32) (temp_f16 + (((*(f32 *)((u8 *)arg1 + 0x24)) - temp_f16) * 0.228659f));
        } while (var_a2 > 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/tracer_ease_values.s")
#endif
#ifdef NON_MATCHING
s32 ray_cast_world(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
#else
s32 ray_cast_world(struct127 *, s32, s32, s32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
#endif
typedef struct { s32 w0; s32 w4; u8 b8[0x18]; u8 b20[0x39]; u8 x59; u8 pad5A[0x1A]; } Res_151C4990;
/* was func_151C4990 */
s32 tracer_check_hit_step(u8 *arg0, u8 *arg1, f32 arg2)
{
  u8 ret;
  struct127 *t;
  Res_151C4990 r;
  f32 f;
  t = *((struct127 **) (arg1 + 0x90));
  ret = 1;
  if (arg1[0] & 4)
  {
    if ((*((f32 *) (arg1 + 0x8C))) < arg2)
    {
      f = (*((f32 *) (arg1 + 0x8C))) * (*((f32 *) (arg1 + 0x98)));
    }
    else
    {
      f = (*((f32 *) (arg1 + 0x98))) * arg2;
    }
    if (f != 0.0f)
    {
#ifdef NON_MATCHING
      ray_cast_world(t, *((f32 *) (arg0 + 0x34)), *((f32 *) (arg0 + 0x38)), *((f32 *) (arg0 + 0x3C)), *((f32 *) (arg1 + 0x60)), *((f32 *) (arg1 + 0x64)), *((f32 *) (arg1 + 0x68)), (u8 *) (&r), f, 1, 0, !(arg1[0] & 8), *((s8 *) (arg1 + 0xA8)), 0, *((s32 *) (arg1 + 0xAC)));
#else
      ray_cast_world(t, *((s32 *) (arg0 + 0x34)), *((s32 *) (arg0 + 0x38)), *((s32 *) (arg0 + 0x3C)), *((f32 *) (arg1 + 0x60)), *((f32 *) (arg1 + 0x64)), *((f32 *) (arg1 + 0x68)), (u8 *) (&r), f, 1, 0, !(arg1[0] & 8), *((s8 *) (arg1 + 0xA8)), 0, *((s32 *) (arg1 + 0xAC)));
#endif
      if (r.x59 >= 2)
      {
        tracer_hit_callback(r.w0, (s32) t, arg0, (s32) r.b8, (s32) r.b20, (s32) (&r));
        ret = 0;
        if (arg1) // fakematch: register order of ret/flags
        {
        }
      }
    }
  }
  return ret;
}

/* was func_151C4AC0 */
void tracer_move(u8 *arg0, u8 *arg1, f32 arg2) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 4)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg1 + 8)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg1 + 0xC)) * arg2);
}

/* was func_151C4B0C */
s32 tracer_tick_life(s32 arg0, u8 *arg1, f32 arg2) {
    s32 temp_v1;
    s32 var_v1;
    s8 temp_v0;
    var_v1 = 1;
    (*(f32 *)((u8 *)arg1 + 0x8C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x8C)) - arg2);
    if ((*(f32 *)((u8 *)arg1 + 0x8C)) <= 0.0f) {
        if ((D_800E0940 != NULL) && ((*(u8 *)((u8 *)arg1 + 0)) & 1)) {
            temp_v1 = (*(s32 *)((u8 *)arg1 + 0x84));
            if (temp_v1 != 0) {
                ((void (*)(u8 *, s32)) D_800E0940)(arg1 + 0x30, (temp_v1 - (s32) D_800DBEF4) / 160);
            }
        }
        if ((*(u8 *)((u8 *)arg1 + 0)) & 2) {
            temp_v0 = (*(s8 *)((u8 *)arg1 + 0x9C));
            if (temp_v0 != -1) {
                D_8008FF70[temp_v0](arg0);
            }
        }
        var_v1 = 0;
    }
    return var_v1;
}

#ifdef NON_MATCHING
typedef struct {
    /* 0x00 */ s16 *pos;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 interval_min;
    /* 0x0C */ s32 interval_range;
    /* 0x10 */ s16 effect_min;
    /* 0x12 */ s16 effect_range;
    /* 0x14 */ f32 param9_min;
    /* 0x18 */ f32 param9_range;
    /* 0x1C */ f32 param0;
    /* 0x20 */ f32 param1;
    /* 0x24 */ f32 param23_range;
    /* 0x28 */ f32 param67;
    /* 0x2C */ f32 tail[3];
} TimedEmitter;

// timed_emitter_update: counts the emitter at obj+0x28 down by the frame time D_800BE9E4; when it runs out, spawns a
// random effect of type 0x2B (id effect_min + rand % (effect_range + 1)) with flags (1, 0), size 0x44, obj bytes
// +0xC / +1, and copies a 17-float parameter block into it at +0x28 (random spreads, the emitter position as floats,
// the three tail floats); then re-arms the timer to interval_min + rand % (interval_range + 1).
/* was func_151C4BF4 */
void timed_emitter_update(u8 *obj) {
    TimedEmitter *e = (TimedEmitter *)(obj + 0x28);
    f32 p[17];
    u8 *fx;

    e->timer -= D_800BE9E4;
    if (e->timer >= 0) {
        return;
    }
    p[0] = e->param0;
    p[1] = e->param1;
    p[2] = random_float() * e->param23_range;
    p[3] = random_float() * e->param23_range;
    p[4] = random_float() * 6.2831855f;
    p[5] = random_float() * 6.2831855f;
    p[6] = e->param67;
    p[7] = e->param67;
    p[8] = 0.0f;
    p[9] = random_float() * e->param9_range + e->param9_min;
    p[10] = 0.0f;
    p[11] = e->pos[0];
    p[12] = e->pos[1];
    p[13] = e->pos[2];
    p[14] = e->tail[0];
    p[15] = e->tail[1];
    p[16] = e->tail[2];
    fx = (u8 *)effect_node_create((s16)((u32)random_int() % (u32)(e->effect_range + 1) + e->effect_min), -1, 0x2B, -1, 1,
                             0, (struct37 *)0x44, obj[0xC], obj[1]);
    if (fx != NULL) {
        memcpy((s32)(fx + 0x28), (s32)p, 0x44);
    }
    e->timer = (u32)random_int() % (u32)(e->interval_range + 1) + e->interval_min;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/timed_emitter_update.s")
#endif

#ifdef NON_MATCHING
f32 sinf(f32);
void vec3_from_angles_rad(f32, f32, f32, f32 *);

// orbit_sparks_emit: emitter handler of object p (state at p + 0x28 = s). The emit accumulator s+0x28 grows by
// rate s+0x24 * dt; while it is above 1 one spark is emitted per unit: the spawn point swings on two sines
// (centre s+0 / s+4, amplitudes s+8 / s+0xC, phases s+0x10 / s+0x14 advanced by s+0x18 / s+0x1C * dt spread over
// the emitted sparks), vec3_from_angles_rad turns it into a position, and tracer_spawn launches the spark (s+0x2C, speed
// 55..95, size 250..550, life 200..255, time s+0x20 + dt counting down per spark). The phases are wrapped with
// wrap_angle_rad and the time stored back at the end.
/* was func_151C4DD0 */
void orbit_sparks_emit(u8 *p) {
    f32 vec[3];
    f32 db;
    f32 da;
    f32 step;
    f32 inv;
    f32 t;
    f32 a;
    f32 b;
    f32 r1;
    f32 r2;
    f32 sa;
    f32 *s;

    s = (f32 *) (p + 0x28);
    s[10] += s[9] * D_800BE9A4;
    if (!(1.0f < s[10])) {
        return;
    }
    inv = 1.0f / s[10];
    t = s[8] + D_800BE9A4;
    step = t * inv;
    a = s[4];
    b = s[5];
    da = s[6] * D_800BE9A4 * inv;
    db = s[7] * D_800BE9A4 * inv;
    do {
        sa = sinf(a);
        vec3_from_angles_rad(s[0] + sa * s[2], s[1] + sinf(b) * s[3], 5.0f, vec);
        r1 = random_float();
        r2 = random_float();
        tracer_spawn((u8 *) (s + 11), (u8 *) vec, NULL, NULL, 0, 0, s[14], s[15], r1 * 40.0f + 55.0f,
                      r2 * 300.0f + 250.0f, s[16], (u32) random_int() % 56 + 200, NULL, 0, 0, 0, 0, 0, 0, -1, 0, t,
                      0xFF, -1, 0, p[0xC], p[1]);
        s[10] -= 1.0f;
        a += da;
        b += db;
        t -= step;
    } while (1.0f < s[10]);
    s[4] = wrap_angle_rad(a);
    s[5] = wrap_angle_rad(b);
    s[8] = t;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/orbit_sparks_emit.s")
#endif

/* was func_151C5060 */
void tracer_on_obj_replaced(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x110;
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[1];
            p[0x94] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[0];
            p[0x94] = ((u8 *)arg1)[8];
        }
    }
}

#ifdef NON_MATCHING
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32 *, u8 *, f32 *, f32 *, f32 *, f32 *, s32 *, u8 *, f32);

typedef struct {
    u8 *object;         /* +0x00 */
    f32 dist;           /* +0x04 distance to the hit (-1 = none) */
    f32 point[3];       /* +0x08 */
    f32 normal[3];      /* +0x14 */
    f32 exit[3];        /* +0x20 */
    f32 start[3];       /* +0x2C */
    f32 dir[3];         /* +0x38 */
    u8 surface[0x15];   /* +0x44 level surface (collision_ray_cast) */
    u8 kind;            /* +0x59 0 none, 1 level, 2 object bounds, 3 object model */
    u8 pad5A[2];
    u8 *material;       /* +0x5C D_800DBEF4 entry (0xA0 bytes each) */
    s32 extra;          /* +0x60 level hit extra */
} RayHit;               /* 0x64 bytes, ray_cast_world's hit record */

// beam_hit_update: keeps a beam's hit record (hitArg) for this frame and writes its length (dist * lenScale, or
// missLen when nothing is hit) to *outArg. With a previous record (srcArg) it is copied; when the start moved to
// posArg the direction (point - pos) is renormalised (vec3_normalize_len, which also gives dist; failure -> 0), and with
// `recheck` an object hit (kind 2 / 3) is cast again against object bounds only (ray_cast_world, taken when it hits).
// Without one and without `cast` the record only gets the start (pos) and direction (dirArg, else toArg): returns
// whether there was one. Otherwise it casts from fromArg along toArg (both given) or from pos along dirArg
// (ray_cast_world: objects unless !objects, models unless !(models && objects), filter, skipMask). A level hit
// counts; an object hit is re-cast against the level from the hit point toward pos when from / to were given (the
// lengths add up), else from pos (collision_ray_cast). On a hit the direction is renormalised from pos if needed, the
// impact handled (hit_spark_sound_play) and the material pointer refreshed; on a miss flagMask is cleared in *flags and
// it returns whether dirArg or toArg was given. The argument types are the callers' (game_eu_1EFE10 /
// game_eu_125200 prototypes).
/* was func_151C50BC */
s32 tracer_hit_update(s32 srcArg, s32 *hitArg, u8 *posArg, s32 *dirArg, s32 *outArg, f32 lenScale, s32 castArg,
                  u8 *fromArg, s32 *toArg, s8 *flags, s32 flagMask, f32 missLen, u8 *caster, s32 filter,
                  s32 objects, s32 models, s32 skipMask, s32 recheck) {
    RayHit *src = (RayHit *) srcArg;
    RayHit *hit = (RayHit *) hitArg;
    f32 *pos = (f32 *) posArg;
    f32 *dir = (f32 *) dirArg;
    f32 *from = (f32 *) fromArg;
    f32 *to = (f32 *) toArg;
    RayHit tmp;
    f32 len;
    s32 matIdx;
    u8 found;

    if (src != NULL) {
        *hit = *src;
        if (hit->start[0] != pos[0] || hit->start[1] != pos[1] || hit->start[2] != pos[2]) {
            hit->dir[0] = hit->point[0] - pos[0];
            hit->dir[1] = hit->point[1] - pos[1];
            hit->dir[2] = hit->point[2] - pos[2];
            hit->start[0] = pos[0];
            hit->start[1] = pos[1];
            hit->start[2] = pos[2];
            if (vec3_normalize_len((u8 *) hit->dir, (s32 *) hit->dir, (s32) &hit->dist, 0) == 0) {
                return 0;
            }
        }
        if ((u8) recheck && (hit->kind == 2 || hit->kind == 3)) {
            ray_cast_world((struct127 *) caster, hit->start[0], hit->start[1], hit->start[2], hit->dir[0], hit->dir[1],
                          hit->dir[2], (u8 *) &tmp, 0.0f, 0, 1, 1, -1, 0, skipMask);
            if (tmp.kind != 0) {
                *hit = tmp;
            }
        }
        *(f32 *) outArg = hit->dist * lenScale;
        return 1;
    }
    if ((u8) castArg == 0) {
        *flags &= ~(u8) flagMask;
        *(f32 *) outArg = missLen;
        hit->start[0] = pos[0];
        hit->start[1] = pos[1];
        hit->start[2] = pos[2];
        if (dir != NULL) {
            hit->dir[0] = dir[0];
            hit->dir[1] = dir[1];
            hit->dir[2] = dir[2];
            return 1;
        }
        if (to != NULL) {
            hit->dir[0] = to[0];
            hit->dir[1] = to[1];
            hit->dir[2] = to[2];
            return 1;
        }
        return 0;
    }

    matIdx = -1;
    if (from != NULL && to != NULL) {
        hit->start[0] = from[0];
        hit->start[1] = from[1];
        hit->start[2] = from[2];
        hit->dir[0] = to[0];
        hit->dir[1] = to[1];
        hit->dir[2] = to[2];
    } else {
        hit->start[0] = pos[0];
        hit->start[1] = pos[1];
        hit->start[2] = pos[2];
        hit->dir[0] = dir[0];
        hit->dir[1] = dir[1];
        hit->dir[2] = dir[2];
    }
    ray_cast_world((struct127 *) caster, hit->start[0], hit->start[1], hit->start[2], hit->dir[0], hit->dir[1],
                  hit->dir[2], (u8 *) hit, 0.0f, 0, !(u8) objects, !((u8) models && (u8) objects), (s8) filter, 0,
                  skipMask);
    if (hit->material == NULL) {
        matIdx = -1;
    } else {
        matIdx = (hit->material - (u8 *) D_800DBEF4) / 0xA0;
    }
    if (hit->kind == 0) {
        found = 0;
    } else if (hit->kind == 1) {
        found = 1;
    } else if (from != NULL && to != NULL) {
        /* (the asm also saves a copy of the record here that is never read) */
        hit->start[0] = pos[0];
        hit->start[1] = pos[1];
        hit->start[2] = pos[2];
        hit->dir[0] = hit->point[0] - pos[0];
        hit->dir[1] = hit->point[1] - pos[1];
        hit->dir[2] = hit->point[2] - pos[2];
        if (vec3_normalize_len((u8 *) hit->dir, (s32 *) hit->dir, (s32) &hit->dist, 0) == 0) {
            return 0;
        }
        len = hit->dist;
        found = collision_ray_cast(hit->point[0], hit->point[1], hit->point[2], hit->dir[0], hit->dir[1], hit->dir[2], NULL,
                              hit->surface, &hit->point[0], &hit->point[1], &hit->point[2], &hit->dist, &matIdx,
                              (u8 *) &hit->extra, 0.0f);
        if (found) {
            hit->dist += len;
            hit->start[0] = pos[0];
            hit->start[1] = pos[1];
            hit->start[2] = pos[2];
        }
    } else {
        found = collision_ray_cast(pos[0], pos[1], pos[2], hit->dir[0], hit->dir[1], hit->dir[2], NULL, hit->surface,
                              &hit->point[0], &hit->point[1], &hit->point[2], &hit->dist, &matIdx,
                              (u8 *) &hit->extra, 0.0f);
    }
    if (!found) {
        *flags &= ~(u8) flagMask;
        *(f32 *) outArg = missLen;
        return dir != NULL || to != NULL;
    }
    *(f32 *) outArg = hit->dist * lenScale;
    if (hit->start[0] != pos[0] || hit->start[1] != pos[1] || hit->start[2] != pos[2]) {
        hit->dir[0] = hit->point[0] - pos[0];
        hit->dir[1] = hit->point[1] - pos[1];
        hit->dir[2] = hit->point[2] - pos[2];
        hit->start[0] = pos[0];
        hit->start[1] = pos[1];
        hit->start[2] = pos[2];
        if (vec3_normalize_len((u8 *) hit->dir, (s32 *) hit->dir, (s32) &hit->dist, 0) == 0) {
            return 0;
        }
    }
    hit_spark_sound_play(caster, (u8 *) hit->point, (u8 *) hit->dir, hit->extra, hit->dist);
    if (matIdx == -1) {
        hit->material = NULL;
    } else {
        hit->material = (u8 *) D_800DBEF4 + matIdx * 0xA0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/tracer_hit_update.s")
#endif
