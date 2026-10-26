#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void level_hotspot_setup(s32 arg0);


/* was func_150091D0 */
void level_lights_reset(void) {
    int tmp0 = 127;

    g_light_list_head = 0;
    g_light_vertex_lighting = 1;
    g_light_colour_zones = 0;
    g_light_tint_zones = 0;

    light_set_level_colour(255, 255, 255, 0);

    g_level_light_dir[0] = 0;
    g_level_light_dir[1] = 0;
    g_level_light_dir[2] = 0;

    g_level_tint_colour[0] = 255;
    g_level_tint_colour[1] = 255;
    g_level_tint_colour[2] = 255;

    if (0) {};

    g_level_light_dirs = tmp0;
    g_level_light_dirs_0y = 0;
    g_level_light_dirs_0z = 0;

    g_level_light_dirs_1x = tmp0;
    g_level_light_dirs_1y = 0;
    g_level_light_dirs_1z = 0;

    g_level_light_dirs_2x = tmp0;
    g_level_light_dirs_2y = 0;
    g_level_light_dirs_2z = 0;

    g_level_light_dirs_3x = tmp0;
    g_level_light_dirs_3y = 0;
    g_level_light_dirs_3z = 0;
    g_level_tint_strength_b = 0;
    g_level_tint_strength_a = 0;
    bzero(&g_light_cmd_data, 56);
}

/* was func_150092DC */
void level_hotspots_setup_all(void) {
    u32 i;
    for (i = 0; i < g_level_zone_count; i++) {
        level_hotspot_setup(i);
    }
}

// requires jumptable
u8 *allocate_memory(s32, s32, s32, s32);

/* was func_15009334 */
void level_hotspot_setup(s32 arg0) {
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp44;
    s32 sp34;
    s32 temp_t0;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_v0_3;
    u32 temp_t0_2;
    u32 temp_v1;
    u32 temp_v1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;

    temp_t4 = arg0 * 0x34;
    temp_v0 = g_level_zones + temp_t4;
    temp_t7 = (s32) (*(u8 *)((u8 *)temp_v0 + 0x15)) >> 2;
    switch (temp_t7) {
    case 9:
    case 10:
    case 16:
        temp_v1 = (*(u32 *)((u8 *)temp_v0 + 0x18));
        sp70 = temp_v1 & 0xFF;
        sp6C = (temp_v1 >> 8) & 0xFF;
        sp68 = (temp_v1 >> 0x10) & 0xFF;
        (*(u8 *)((u8 *)temp_v0 + 0x16)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x16)) | 4);
        switch (temp_t7) {                          /* switch 1; irregular */
        case 10:                                    /* switch 1 */
            sp34 = temp_t4;
            light_set_level_colour(sp70, sp6C, sp68, 0U);
            temp_t0 = (*(s32 *)((u8 *)((g_level_zones + temp_t4)) + 0x20));
            if (temp_t0 != 0) {
                ambient_fx_dispatch(temp_t0);
                return;
            }
        default:
            return;
        case 9:                                     /* switch 1 */
            temp_v0_2 = g_level_zones + temp_t4;
            temp_v1_2 = (*(u32 *)((u8 *)temp_v0_2 + 0x18));
            temp_t0_2 = (*(u32 *)((u8 *)temp_v0_2 + 0x20));
            sp44 = temp_t0_2 & 0xFFFF;
            temp_v0_3 = light_add_point_ext((*(s16 *)((u8 *)temp_v0_2 + 0)), (*(s16 *)((u8 *)temp_v0_2 + 2)), (*(s16 *)((u8 *)temp_v0_2 + 4)), ((u32) (*(u32 *)((u8 *)temp_v0_2 + 0x1C)) >> 8) & 0xFF, sp70, sp6C, sp68, (temp_v1_2 >> 0x18) & 0x7F, (temp_v1_2 >> 0x1F) & 1, (temp_t0_2 >> 0x10) & 0xFFFF);
            if ((temp_v0_3 != 0) && (sp44 != 0)) {
                hotspot_fx_dispatch(temp_v0_3, sp44);
                return;
            }
            break;
        case 16:                                    /* switch 1 */
            (*(s8 *)((u8 *)g_level_light_dir + 0)) = (s8) sp70;
            g_level_light_dir[1] = (s8) sp6C;
            g_level_light_dir[2] = (s8) sp68;
            temp_v0_4 = g_level_zones + temp_t4;
            (*(u8 *)((u8 *)g_level_tint_colour + 0)) = (u8) (*(u32 *)((u8 *)temp_v0_4 + 0x1C));
            g_level_tint_colour[1] = (u8) ((u32) (*(u32 *)((u8 *)temp_v0_4 + 0x1C)) >> 8);
            g_level_tint_colour[2] = (u8) ((u32) (*(u32 *)((u8 *)temp_v0_4 + 0x1C)) >> 0x10);
            g_level_tint_strength_b = (u8) ((u32) (*(u32 *)((u8 *)temp_v0_4 + 0x1C)) >> 0x18);
            g_level_tint_strength_a = (u8) ((u32) (*(u32 *)((u8 *)temp_v0_4 + 0x18)) >> 0x18);
            return;
        }
        break;
    case 15:
        sp34 = temp_t4;
        temp_v0_5 = allocate_memory(8, 1, 0, 0);
        (*(u8 **)((u8 *)temp_v0_5 + 4)) = (u8 *) (temp_t4 + g_level_zones);
        (*(s32 *)((u8 *)temp_v0_5 + 0)) = (s32) g_light_colour_zones;
        g_light_colour_zones = (s32) temp_v0_5;
        return;
    case 24:
        sp34 = temp_t4;
        temp_v0_6 = allocate_memory(8, 1, 0, 0);
        (*(u8 **)((u8 *)temp_v0_6 + 4)) = (u8 *) (temp_t4 + g_level_zones);
        (*(s32 *)((u8 *)temp_v0_6 + 0)) = (s32) g_light_tint_zones;
        g_light_tint_zones = (s32) temp_v0_6;
        break;
    }
}
/* was func_150095D8 */
void hotspot_fx_type01(s32 arg0, s32 arg1) {
    light_spawn_pulse_a(arg0, 0xFF, 1);
}

/* was func_15009600 */
void hotspot_fx_type02(s32 arg0, s32 arg1) {
    light_spawn_flicker_a(arg0, 0xFF, 1);
}

/* was func_15009628 */
void hotspot_fx_type03_06(s32 arg0, s32 arg1) {
    struct220 tmp;
    u8 sp24[4] = {1, 2, 3, 4};
    tmp.unk0 = 0;
    tmp.unk1 = -1;
    tmp.unk2 = 300;
    tmp.unk4 = sp24[arg1 - 3];

    light_ctrl_alloc(&tmp, arg0, 0, 255, 1);
}

/* was func_1500969C */
void hotspot_fx_type07(s32 arg0, s32 arg1) {
    light_spawn_kind8(arg0, 0xFF, 1);
}

/* was func_150096C4 */
void hotspot_fx_type08_12(s32 arg0, s32 arg1) {
    struct220 tmp;
    u8 sp24[5] = {10, 9, 12, 11, 13};
    tmp.unk0 = 0;
    tmp.unk1 = -1;
    tmp.unk2 = 300;
    tmp.unk4 = sp24[arg1 - 8];

    light_ctrl_alloc(&tmp, arg0, 0, 255, 1);
}

/* was func_15009740 */
void hotspot_fx_type13(s32 arg0, s32 arg1) {
    light_spawn_pulse_b(arg0, 0xFF, 1);
}

/* was func_15009768 */
void hotspot_fx_type14(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 0, 0, 0xE, 0xFF, 1);
}

/* was func_150097A4 */
void hotspot_fx_type15(s32 arg0, s32 arg1) {
    light_spawn_pulse_c(arg0, 0xFF, 1);
}

/* was func_150097CC */
void hotspot_fx_type16(s32 arg0, s32 arg1) {
    s32 temp_v0 = light_spawn_lightning(arg0, 0, 2, 0xE, 0xFF, 1);
    if (temp_v0 != 0) {
        debris_spawn_linked(temp_v0);
    }
}

/* was func_15009818 */
void hotspot_fx_type17(s32 arg0, s32 arg1) {
    swinging_lamp_spawn(arg0, 0, 0xFF, 1);
}

/* was func_15009844 */
void hotspot_fx_type18(s32 arg0, s32 arg1) {
    swinging_lamp_spawn(arg0, 1, 0xFF, 1);
}

/* was func_15009870 */
void hotspot_fx_type19(s32 arg0, s32 arg1) {
    swing_lamp_spawn(arg0);
}

/* was func_15009894 */
void hotspot_fx_type20(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 1, 0, 0xE, 0xFF, 1);
}

/* was func_150098D0 */
void hotspot_fx_type21(s32 arg0, s32 arg1) {
    light_spawn_flicker_b(arg0, 0xFF, 1);
}

/* was func_150098F8 */
void hotspot_fx_type22(s32 arg0, s32 arg1) {
    light_spawn_colour_pulse(arg0, 1, 22, 0, -1, 300, 0xFF, 1);
}

/* was func_15009944 */
void hotspot_fx_type23(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 1, 6, 0, 300, 2, 0xFF, 1);
}

/* was func_15009990 */
void hotspot_fx_type24_27(s32 arg0, s32 arg1) {
    struct132 * temp_v0;
    u8 sp40[4];

    sp40[0] = g_area_drift_param_64[arg1];
    temp_v0 = light_spawn_envelope(arg0, g_area_drift_speed_k[arg1], g_area_drift_param_48[arg1], 2, 300, 12, -1, 0, -1, 1, 1, 255, 1);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->unk48, &sp40, 1);
    }
}

/* was func_15009A38 */
void hotspot_fx_type69_72(s32 arg0, s32 arg1) {
    struct220 tmp;

    tmp.unk0 = 2;
    tmp.unk1 = -1;
    tmp.unk2 = 300;
    tmp.unk4 = g_hotspot_light_levels[arg1];
    light_ctrl_alloc(&tmp, arg0, 0, 255, 1);
}

/* was func_15009AA0 */
void hotspot_fx_type28(s32 arg0, s32 arg1) {
    light_spawn_burst_flash(arg0, 1, 0, 2, 300, 0xD, 0xFF, 1);
}

/* was func_15009AEC */
void hotspot_fx_type29(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 2, 6, 0, 300, 2, 0xFF, 1);
}

/* was func_15009B38 */
void hotspot_fx_type76(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 20, 6, 0, 300, 2, 0xFF, 1);
}

/* was func_15009B84 */
void hotspot_fx_type30(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 3, 6, 0, 300, 2, 0xFF, 1);
}

/* was func_15009BD0 */
void hotspot_fx_type31(s32 arg0, s32 arg1) {
    struct00 *temp_v0; // dummy
    struct221 tmp;

    tmp.unk4 = 0.0f;
    tmp.unk8 = 90.0f;
    tmp.unk0 = light_fx_add(0, 0.0f, 0, 0, 0, 220, 220, 255);
    temp_v0 = light_ctrl_spawn(arg0, 2, 16, 300, 0, 12, 255, 1);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->unk18, &tmp, 12);
    }
}

/* was func_15009C7C */
void hotspot_fx_type32(s32 arg0, s32 arg1) {
    struct00 *temp_v0; // dummy
    struct221 tmp;

    tmp.unk4 = 0.0f;
    tmp.unk8 = 50.0f;
    tmp.unk0 = light_fx_add(0, 0.0f, 0, 0, 0, 220, 220, 255);
    temp_v0 = light_ctrl_spawn(arg0, 2, 16, 300, 0, 12, 255, 1);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->unk18, &tmp, 12);
    }
}

/* was func_15009D28 */
void hotspot_fx_type33(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 1, 5, 300, 0, 0, 255, 1);
}

/* was func_15009D6C */
void hotspot_fx_type34(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 2, 5, 300, 0, 0, 255, 1);
}

/* was func_15009DB0 */
void hotspot_fx_type35(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 4, 6, 0, 300, 2, 255, 1);
}

/* was func_15009DFC */
void hotspot_fx_type36(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 5, 6, 0, 300, 2, 255, 1);
}

/* was func_15009E48 */
void hotspot_fx_type37(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 1, 1, 14, 255, 1);
}

/* was func_15009E84 */
void hotspot_fx_type38(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 3, 5, 300, 0, 0, 255, 1);
}

/* was func_15009EC8 */
void hotspot_fx_type39(s32 arg0, s32 arg1) {
    light_ctrl_spawn_static(arg0, 32, 255, 1);
}

/* was func_15009EF4 */
void hotspot_fx_type40(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 1, 3, 35, 255, 1);
}

/* was func_15009F30 */
void hotspot_fx_type41(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 4, 36, 300, 0, 0, 255, 1);
}

/* was func_15009F74 */
void hotspot_fx_type42(s32 arg0, s32 arg1) {
    struct00 *temp_v0; // dummy
    struct221 tmp;

    tmp.unk4 = 0.0f;
    tmp.unk8 = 60.0f;
    tmp.unk0 = light_fx_add(1, 0.1f, 100, 100, 100, 255, 100, 100);
    temp_v0 = light_ctrl_spawn(arg0, 2, 16, 300, 0, 12, 255, 1);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->unk18, &tmp, 12);
    }
}

/* was func_1500A028 */
void hotspot_fx_type43(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 5, 5, 300, 0, 0, 255, 1);
}

/* was func_1500A06C */
void hotspot_fx_type44(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 6, 5, 300, 0, 0, 255, 1);
}

/* was func_1500A0B0 */
void hotspot_fx_type45(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 7, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A0FC */
void hotspot_fx_type46(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 9, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A148 */
void hotspot_fx_type47(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 10, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A194 */
void hotspot_fx_type48(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 11, 38, 0, 300, 2, 255, 1);
}

/* was func_1500A1E0 */
void hotspot_fx_type49(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 1, 4, 14, 255, 1);
}

/* was func_1500A21C */
void hotspot_fx_type50(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 7, 5, 300, 0, 0, 255, 1);
}

/* was func_1500A260 */
void hotspot_fx_type55(s32 arg0, s32 arg1) {
    light_spawn_burst_flash(arg0, 2, 0, 2, 300, 13, 255, 1);
}

/* was func_1500A2AC */
void hotspot_fx_type51_54(s32 arg0, s32 arg1) {
    u8 sp1C[4] = g_hotspot_swing_lamp_presets;

    swinging_lamp_spawn(arg0, sp1C[arg1 - 0x33], 0xFF, 1);
}

/* was func_1500A2F4 */
void hotspot_fx_type56_57(s32 arg0, s32 arg1) {
    u8 sp1C[2] = g_hotspot_flash_presets;
    light_spawn_flash(arg0, sp1C[arg1 - 0x38], 0xFF, 1);
}

/* was func_1500A33C */
void hotspot_fx_type58(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 8, 5, 300, 0, 0, 255, 1);
}

/* was func_1500A380 */
void hotspot_fx_type59(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 9, 0x28, 300, 0, 0, 255, 1);
}

/* was func_1500A3C4 */
void hotspot_fx_type60(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 15, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A410 */
void hotspot_fx_type61(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 10, 5, 300, 0, 0, 255, 1);
}

/* was func_1500A454 */
void hotspot_fx_type62(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 0, 5, 14, 255, 1);
}

/* was func_1500A490 */
void hotspot_fx_type63(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 11, 5, 300, 0, 0, 255, 1);
}

/* was func_1500A4D4 */
void hotspot_fx_type64(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 12, 41, 300, 0, 0, 255, 1);
}

/* was func_1500A518 */
void hotspot_fx_type77(s32 arg0, s32 arg1) {
    light_spawn_pulse_preset(arg0, 13, 41, 300, 0, 0, 255, 1);
}

/* was func_1500A55C */
void hotspot_fx_type65(s32 arg0, s32 arg1) {
    light_spawn_colour_pulse(arg0, 1, 22, 0, -1, 300, 255, 1);
}

/* was func_1500A5A8 */
void hotspot_fx_type66(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 17, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A5F4 */
void hotspot_fx_type67(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 18, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A640 */
void hotspot_fx_type68(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 19, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A68C */
void hotspot_fx_type78(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 21, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A6D8 */
void hotspot_fx_type73_75(s32 arg0, s32 arg1) {
    struct220 sp48;
    f32 sp30[6];
    s32 temp_v0;
    u8 sp24[2][3] = {{7, 8, 9}, {8, 9, 10}};
    s32 i;

    i = (g_level_id == 6) ? 1 : 0;
    if (world_record_anchor_init(sp24[i][arg1 - 0x49], sp30) != 0) {
        sp48.unk0 = 0;
        sp48.unk1 = 0x17;
        sp48.unk2 = 300;
        sp48.unk4 = 0;
        temp_v0 = light_ctrl_alloc(&sp48, arg0, 0x18, 255, 1);
        if (temp_v0 != 0) {
            memcpy((u8 *)temp_v0 + 0x18, sp30, 0x18);
        }
    }
}

/* was func_1500A79C */
void hotspot_fx_type79(s32 arg0, s32 arg1) {
    light_spawn_flicker_preset(arg0, 22, 6, 0, 300, 2, 255, 1);
}

/* was func_1500A7E8 */
void hotspot_fx_type80_85(s32 arg0, s32 arg1) {
    struct220 sp48;
    struct {
        f32 unk0;
        f32 unk4;
        u8 *unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } sp30;
    s32 temp_v0;
    u8 sp24[6] = {2, 3, 4, 5, 6, 7};

    sp30.unk8 = (u8 *)world_record_find(sp24[arg1 - 0x50]);
    if (sp30.unk8 != NULL) {
        sp30.unk0 = -400.0f;
        sp30.unk4 = 4.0f;
        sp30.unkC = *(s16 *)(sp30.unk8 + 0x10);
        sp30.unk10 = *(s16 *)(sp30.unk8 + 0x12);
        sp30.unk14 = *(s16 *)(sp30.unk8 + 0x14);
        sp48.unk0 = 0;
        sp48.unk1 = 0x17;
        sp48.unk2 = 300;
        sp48.unk4 = 0;
        temp_v0 = light_ctrl_alloc(&sp48, arg0, 0x18, 255, 1);
        if (temp_v0 != 0) {
            memcpy((u8 *)temp_v0 + 0x18, &sp30, 0x18);
        }
    }
}

/* was func_1500A8C8 */
void hotspot_fx_type86(s32 arg0, s32 arg1) {
    light_spawn_lightning(arg0, 0, 6, 0xE, 255, 1);
}

/* was func_1500A904 */
void hotspot_fx_type87_88(s32 arg0, s32 arg1) {
    u8 tmp = arg1 - 80;
    light_spawn_lightning(arg0, 1, tmp, 0xE, 255, 1);
}

/* was func_1500A94C */
void hotspot_fx_dispatch(s32 arg0, s32 arg1) {
    if ((arg1 > 0) && (arg1 < 89)) {
        if (g_hotspot_fx_fns[arg1]) {
            /* P76: the handlers read a1 too (still arg1 at the jalr) */
            ((void (*)(s32, s32)) g_hotspot_fx_fns[arg1])(arg0, arg1);
        }
    }
}

/* was func_1500A990 */
void ambient_fx_spawn_type2(s32 arg0) {
    struct164 tmp;
    f32 phi_f18;
    struct164 *temp_v0;

    tmp.unk0 = 35.0f;
    tmp.unk4 = 35.0f;
    tmp.unk8 = 60.0f;
    tmp.unkC = 34.0f;
    tmp.unk10 = 30.0f;
    tmp.unk14 = 50.0f;

    phi_f18 = (u32)(osGetCount() * random_int()) & 0xFFFF;
    phi_f18 *= 1.5259022e-05f;
    tmp.unk18 = (phi_f18 + phi_f18) * 3.1415927f;

    phi_f18 = (u32)(osGetCount() * random_int()) & 0xFFFF;
    phi_f18 *= 1.5259022e-05f;
    tmp.unk1C = (phi_f18 + phi_f18) * 3.1415927f;

    phi_f18 = (u32)(osGetCount() * random_int()) & 0xFFFF;
    phi_f18 *= 1.5259022e-05f;

    tmp.unk20 = (phi_f18 + phi_f18) * 3.1415927f;
    tmp.unk24 = -0.13700001f;
    tmp.unk28 = 0.048f;
    tmp.unk2C = 0.007f;

    temp_v0 = effect_node_create(300, -1, 45, -1, 0, 0, 48, 255, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 48);
    }
}

/* was func_1500AB5C */
void ambient_fx_dispatch(s32 arg0) {
    if ((arg0 > 0) && (arg0 < 6)) {
        if (g_ambient_fx_fns[arg0] != 0) {
            ((void (*)(s32)) g_ambient_fx_fns[arg0])(arg0);   /* P76: a0 still holds arg0 */
        }
    }
}

void ambient_fx_spawn_type4();
void ambient_pulse_spawn();

void hotspot_fx_type73_75(s32 arg0, s32 arg1);
void hotspot_fx_type80_85(s32 arg0, s32 arg1);

void (*g_hotspot_fx_fns[])(s32 arg0) = { /* was D_80082BFC */
    NULL, (void (*)(s32))hotspot_fx_type01, (void (*)(s32))hotspot_fx_type02, (void (*)(s32))hotspot_fx_type03_06,
    (void (*)(s32))hotspot_fx_type03_06, (void (*)(s32))hotspot_fx_type03_06, (void (*)(s32))hotspot_fx_type03_06, (void (*)(s32))hotspot_fx_type07,
    (void (*)(s32))hotspot_fx_type08_12, (void (*)(s32))hotspot_fx_type08_12, (void (*)(s32))hotspot_fx_type08_12, (void (*)(s32))hotspot_fx_type08_12,
    (void (*)(s32))hotspot_fx_type08_12, (void (*)(s32))hotspot_fx_type13, (void (*)(s32))hotspot_fx_type14, (void (*)(s32))hotspot_fx_type15,
    (void (*)(s32))hotspot_fx_type16, (void (*)(s32))hotspot_fx_type17, (void (*)(s32))hotspot_fx_type18, (void (*)(s32))hotspot_fx_type19,
    (void (*)(s32))hotspot_fx_type20, (void (*)(s32))hotspot_fx_type21, (void (*)(s32))hotspot_fx_type22, (void (*)(s32))hotspot_fx_type23,
    (void (*)(s32))hotspot_fx_type24_27, (void (*)(s32))hotspot_fx_type24_27, (void (*)(s32))hotspot_fx_type24_27, (void (*)(s32))hotspot_fx_type24_27,
    (void (*)(s32))hotspot_fx_type28, (void (*)(s32))hotspot_fx_type29, (void (*)(s32))hotspot_fx_type30, (void (*)(s32))hotspot_fx_type31,
    (void (*)(s32))hotspot_fx_type32, (void (*)(s32))hotspot_fx_type33, (void (*)(s32))hotspot_fx_type34, (void (*)(s32))hotspot_fx_type35,
    (void (*)(s32))hotspot_fx_type36, (void (*)(s32))hotspot_fx_type37, (void (*)(s32))hotspot_fx_type38, (void (*)(s32))hotspot_fx_type39,
    (void (*)(s32))hotspot_fx_type40, (void (*)(s32))hotspot_fx_type41, (void (*)(s32))hotspot_fx_type42, (void (*)(s32))hotspot_fx_type43,
    (void (*)(s32))hotspot_fx_type44, (void (*)(s32))hotspot_fx_type45, (void (*)(s32))hotspot_fx_type46, (void (*)(s32))hotspot_fx_type47,
    (void (*)(s32))hotspot_fx_type48, (void (*)(s32))hotspot_fx_type49, (void (*)(s32))hotspot_fx_type50, (void (*)(s32))hotspot_fx_type51_54,
    (void (*)(s32))hotspot_fx_type51_54, (void (*)(s32))hotspot_fx_type51_54, (void (*)(s32))hotspot_fx_type51_54, (void (*)(s32))hotspot_fx_type55,
    (void (*)(s32))hotspot_fx_type56_57, (void (*)(s32))hotspot_fx_type56_57, (void (*)(s32))hotspot_fx_type58, (void (*)(s32))hotspot_fx_type59,
    (void (*)(s32))hotspot_fx_type60, (void (*)(s32))hotspot_fx_type61, (void (*)(s32))hotspot_fx_type62, (void (*)(s32))hotspot_fx_type63,
    (void (*)(s32))hotspot_fx_type64, (void (*)(s32))hotspot_fx_type65, (void (*)(s32))hotspot_fx_type66, (void (*)(s32))hotspot_fx_type67,
    (void (*)(s32))hotspot_fx_type68, (void (*)(s32))hotspot_fx_type69_72, (void (*)(s32))hotspot_fx_type69_72, (void (*)(s32))hotspot_fx_type69_72,
    (void (*)(s32))hotspot_fx_type69_72, (void (*)(s32))hotspot_fx_type73_75, (void (*)(s32))hotspot_fx_type73_75, (void (*)(s32))hotspot_fx_type73_75,
    (void (*)(s32))hotspot_fx_type76, (void (*)(s32))hotspot_fx_type77, (void (*)(s32))hotspot_fx_type78, (void (*)(s32))hotspot_fx_type79,
    (void (*)(s32))hotspot_fx_type80_85, (void (*)(s32))hotspot_fx_type80_85, (void (*)(s32))hotspot_fx_type80_85, (void (*)(s32))hotspot_fx_type80_85,
    (void (*)(s32))hotspot_fx_type80_85, (void (*)(s32))hotspot_fx_type80_85, (void (*)(s32))hotspot_fx_type86, (void (*)(s32))hotspot_fx_type87_88,
    (void (*)(s32))hotspot_fx_type87_88,
};

void (*g_ambient_fx_fns[])(void) = { /* was D_80082D60 */
    NULL, (void (*)(void))ambient_pulse_spawn, (void (*)(void))ambient_fx_spawn_type2, (void (*)(void))ambient_fx_spawn_type3,
    (void (*)(void))ambient_fx_spawn_type4, (void (*)(void))ambient_fx_spawn_type5,
};
