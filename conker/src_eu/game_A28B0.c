#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15075400 */
void aiscript_branch(s32 arg0) {
    s32 tmp;
    u8 i;

    if (arg0 < 247) {
        g_cur_obj->unk218 += arg0;
        return;
    }

    for (i = 0; i < 100; i++) {
        if (g_cur_obj->unk218->unk0 < 247) {
            g_cur_obj->unk218++;
        } else {
            tmp = g_cur_obj->unk218->unk0 & 0xFF;
            ((u8*)g_cur_obj->unk218) += 1;
            if (arg0 == tmp) {
                g_cur_obj->unk218 -= 1;
                return;
            }
        }
    }
}

/* was func_15075498 */
void aiscript_apply_move_flags(void) {
    s32 tmp = g_aiscript_arg3 & 0x7F;

    if (tmp != 0x7F) {
        g_cur_obj->unk244 = tmp;
    }
    g_cur_obj->unkF4 &= ~0x143E;
    if (g_aiscript_arg0 == 0xFA) {
        g_cur_obj->unkF4 |= 0x22;
    } else if (g_aiscript_arg0 == 0xFB) {
        g_cur_obj->unkF4 |= 4;
    }
    if ((g_aiscript_arg3 & 0x80) != 0) {
        g_cur_obj->unkF4 |= 16;
    }
}

/* was func_15075548 */
void aiscript_move_setup(void) {
    f32 temp_f6;
    u8 temp_a0;

    g_cur_obj->unk223 = 0;
    g_cur_obj->unk21C = g_aiscript_arg0 * 100;
    temp_a0 = g_aiscript_arg2;
    if (temp_a0 != 0xFF) {
        temp_f6 = temp_a0;
        g_cur_obj->unk44 = temp_f6;
        if (g_cur_obj->unk44 == 1.0f) {
            g_cur_obj->unk44 = 0.5f;
        }
        if (g_mp_mode_active != 0) {
            if ((g_cur_obj->id == 40) && ((g_cur_obj->unk31C->unk128 & 1) != 0)) {
                g_cur_obj->unk44 *= g_aiscript_speed_boost;
            }
        }
    }
    aiscript_apply_move_flags();
}

/* was func_15075650 */
void aiscript_move_setup_path_point(void) {
    u8 sp1F;
    u8 sp1D;
    f32 var_f6;
    s32 var_a0;
    struct127 *var_v1;
    u8 temp_a1;
    u8 temp_t2;
    u8 temp_t4;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 var_a2;

    var_v1 = g_cur_obj;
    temp_v0 = var_v1->unk21F;
    var_a0 = (g_path_point_counts[var_v1->unk13F] - 1) & 0xFF;
    if (temp_v0 != 0) {
        var_a0 = temp_v0 & 0xFF;
    }
    temp_a1 = var_v1->unk220;
    temp_t2 = (var_a0 - temp_a1) & 0xFF;
    if (g_aiscript_arg1 == 0xFF) {
        if (var_v1->unk223 != 0xD) {
            sp1F = temp_t2;
            g_cur_obj->unk21E = (random_int() % sp1F) + g_cur_obj->unk220;
            goto block_14;
        }
    } else if (g_aiscript_arg1 == 0xFE) {
        if (var_v1->unk223 != 0xD) {
            temp_v0_2 = var_v1->unk21E;
            var_a2 = (temp_v0_2 - 1) & 0xFF;
            if ((s32) temp_a1 >= (s32) temp_v0_2) {
                var_a2 = (var_a0 - 1) & 0xFF;
            }
            sp1D = var_a2;
            sp1F = temp_t2;
            var_v1 = g_cur_obj;
            temp_t4 = ((random_int() % temp_t2) + var_v1->unk220) & 0xFF;
            if (var_a2 != temp_t4) {
                var_v1->unk21E = temp_t4;
                var_v1 = g_cur_obj;
            }
        }
    } else {
        if (g_aiscript_arg1 == 0xFF) {
            var_v1->unk21E = var_a0 - 1;
        } else {
            var_v1->unk21E = g_aiscript_arg1;
        }
block_14:
        var_v1 = g_cur_obj;
    }
    var_v1->unk223 = 0;
    g_cur_obj->unk21C = g_aiscript_arg0 * 0x64;
    if (g_aiscript_arg2 != 0xFF) {
        var_f6 = (f32) g_aiscript_arg2;
        if ((s32) g_aiscript_arg2 < 0) {
            var_f6 += 4294967296.0f;
        }
        g_cur_obj->unk44 = var_f6;
        if (g_cur_obj->unk44 == 1.0f) {
            g_cur_obj->unk44 = 0.5f;
        }
    }
    temp_v0_3 = g_cur_obj->unk220;
    if ((s32) g_cur_obj->unk21E < (s32) temp_v0_3) {
        g_cur_obj->unk21E = temp_v0_3;
    }
    aiscript_apply_move_flags();
}
// NON-MATCHING: 95% there
// void aiscript_move_setup_path_point(void) {
//     u8 phi_a0;
//     u8 phi_a2;
//
//     phi_a0 = D_800D2108[g_cur_obj->unk13F] - 1;
//     if (g_cur_obj->unk21F != 0) {
//         phi_a0 = g_cur_obj->unk21F;
//     }
//     phi_a0 = phi_a0 - g_cur_obj->unk220;
//     if (g_aiscript_arg1 == 0xFF) { // -1
//         if (g_cur_obj->unk223 != 0xD) {
//             g_cur_obj->unk21E = (random_int() % (u32) phi_a0) + g_cur_obj->unk220;
//         }
//     } else if (g_aiscript_arg1 == 0xFE) { // -2
//         if (g_cur_obj->unk223 != 0xD) {
//             phi_a2 = g_cur_obj->unk21E - 1;
//             if (g_cur_obj->unk21E <= g_cur_obj->unk220) {
//                 phi_a2 = phi_a0 - 1;
//             }
//             phi_a0 = (random_int() % (u32) phi_a0) + g_cur_obj->unk220;
//             if (phi_a0 != phi_a2) {
//                 g_cur_obj->unk21E = phi_a0;
//             }
//         }
//     } else {
//         if (g_aiscript_arg1 == 0xFF) { // impossible?
//             g_cur_obj->unk21E = phi_a0 - 1;
//         } else {
//             g_cur_obj->unk21E = g_aiscript_arg1;
//         }
//     }
//
//     g_cur_obj->unk223 = 0;
//     g_cur_obj->unk21C = g_aiscript_arg0 * 0x64;
//
//     if (g_aiscript_arg2 != 0xFF) {
//         g_cur_obj->unk44 = g_aiscript_arg2;
//         if (g_cur_obj->unk44 == 1.0f) {
//             g_cur_obj->unk44 = 0.5f;
//         }
//     }
//
//     if (g_cur_obj->unk21E < g_cur_obj->unk220) {
//         g_cur_obj->unk21E = g_cur_obj->unk220;
//     }
//     aiscript_apply_move_flags();
// }

/* was func_15075884 */
void aiscript_move_timed_to_point(void) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f2;
    u8 *temp_v1;

    aiscript_move_setup();
    temp_v1 = g_path_points[g_cur_obj->unk13F] + (g_cur_obj->unk21E * 8);
    temp_f2 = (f32) (*(s16 *)((u8 *)temp_v1 + 8)) - g_cur_obj->x_position;
    temp_f12 = (f32) (*(s16 *)((u8 *)temp_v1 + 0xC)) - g_cur_obj->z_position;
    var_f2 = (f32) g_aiscript_arg1;
    temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    if ((s32) g_aiscript_arg1 < 0) {
        var_f2 += 4294967296.0f;
    }
    g_cur_obj->unk44 = 2.0f * (temp_f0 / var_f2);
}
// NON-MATCHING: array index is wrong
// void aiscript_move_timed_to_point(void) {
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f2;
//     struct169 *temp_v1;
//     f32 phi_f2;
//
//     aiscript_move_setup();
//     temp_v1 = g_path_points[(g_cur_obj->unk13F) + (g_cur_obj->unk21E)];
//     temp_f2 = temp_v1->unk8 - g_cur_obj->x_position;
//     temp_f12 = temp_v1->unkC - g_cur_obj->z_position;
//     temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
//     g_cur_obj->unk44 = 2.0f * (temp_f0 / g_aiscript_arg1);
// }

/* was func_15075938 */
void aiscript_if_path_offset(void) {
    s32 var_a0;
    s32 var_a2;
    u8 var_v0;
    u8 var_v1;

    var_a2 = 0;
    var_a0 = g_cur_obj->unk21E - g_cur_obj->unk221;
    if (var_a0 < 0) {
        var_v0 = g_path_point_counts[g_cur_obj->unk13F];
        var_a0 = (var_a0 + var_v0) - 1;
    } else {
        var_v0 = g_path_point_counts[g_cur_obj->unk13F];
        if (var_a0 >= (var_v0 - 1)) {
            var_a0 = (var_a0 - var_v0) + 1;
        }
    }
    var_v1 = g_aiscript_arg1;
    if (g_aiscript_arg1 == 0xFF) {
        var_v1 = var_v0 - 2;
    }
    if (g_aiscript_arg2 == 0) {
        if (var_v1 == var_a0) {
            goto block_16;
        }
    } else if (g_aiscript_arg2 == 1) {
        if (var_v1 != var_a0) {
            goto block_16;
        }
    } else if (g_aiscript_arg2 == 2) {
        if ((s32) var_v1 < var_a0) {
            goto block_16;
        }
    } else if (var_a0 < (s32) var_v1) {
block_16:
        var_a2 = 1;
    }
    if (var_a2 != 0) {
        aiscript_branch((s32) g_aiscript_arg0);
    }
}
// NON-MATCHING: 2nd half ok, 1st is a mystery
// void aiscript_if_path_offset(void) {
//     u8 tmp;
//     u8 changed;
//     s32 temp_a0;
//     s32 phi_v1;
//     u8 temp_v0;
//
//     changed = 0;
//
//     temp_a0 = g_cur_obj->unk21E - g_cur_obj->unk221;
//     if (temp_a0 < 0) {
//         temp_v0 = g_cur_obj->unk13F + D_800D2108;
//         temp_a0 = (temp_a0 + temp_v0) - 1;
//     } else {
//         temp_v0 = g_cur_obj->unk13F + D_800D2108;
//         if ((temp_v0 - 1) <= temp_a0) {
//             temp_a0 = (temp_a0 - temp_v0) + 1;
//         }
//     }
//
//     if (g_aiscript_arg1 == 0xFF) {
//         phi_v1 = temp_v0 - 2;
//     } else {
//         phi_v1 = g_aiscript_arg1;
//     }
//
//     if (g_aiscript_arg2 == 0) {
//         if (phi_v1 == temp_a0) {
//             changed = 1;
//         }
//     } else if (g_aiscript_arg2 == 1) {
//         if (phi_v1 != temp_a0) {
//             changed = 1;
//         }
//     } else if (g_aiscript_arg2 == 2) {
//         if (phi_v1 < temp_a0) {
//             changed = 1;
//         }
//     } else {
//         if (phi_v1 > temp_a0) {
//             changed = 1;
//         }
//     }
//
//     if (changed) {
//         aiscript_branch(g_aiscript_arg0);
//     }
// }

/* was func_15075A50 */
void aiscript_if_path_point(void) {
    u8 temp_v0 = g_cur_obj->unk21E;
    if (((g_aiscript_arg2 == 0) && (g_aiscript_arg1 == temp_v0)) ||
       ((g_aiscript_arg2 == 1) && (g_aiscript_arg1 != temp_v0))) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_15075AAC */
void aiscript_move_stop_near_point(void) {
    f32 dx;
    f32 dz;
    s16 *temp_v0;

    aiscript_move_setup();
    temp_v0 = ((s16 (*)[4])g_path_points[g_cur_obj->unk13F])[g_aiscript_arg1];
    dx = temp_v0[0] - g_cur_obj->x_position;
    dz = temp_v0[2] - g_cur_obj->z_position;
    if ((fabsf(dx) + fabsf(dz)) < 40.0f) {
        g_cur_obj->unk21C = 0;
        g_cur_obj->xz_velocity = 0.0f;
    }
}

/* was func_15075B60 */
void aiscript_mode10(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 10;
}

/* was func_15075B8C */
void aiscript_mode10_path_point(void) {
    aiscript_move_setup_path_point();
    g_cur_obj->unk223 = 10;
}

/* was func_15075BB8 */
void aiscript_move_setup_flag2(void) {
    aiscript_move_setup();
    g_cur_obj->unk22C |= 2;
}

/* was func_15075BE8 */
void aiscript_set_reaction_script(void) {
    if (g_aiscript_arg3 != 0) {
        g_cur_obj->unk22C |= 0x80;
    }
    g_cur_obj->unk233 = g_aiscript_arg0;
}

/* was func_15075C24 */
void aiscript_set_y_vel_gravity(void) {
    if (g_aiscript_arg3 != 1) {
        g_cur_obj->y_velocity = (s16)((g_aiscript_arg2 << 8) | g_aiscript_arg0);
    }
    if (g_aiscript_arg3 != 2) {
        g_cur_obj->gravity = (s16)(s8)g_aiscript_arg1;
    }
}

/* was func_15075CA0 */
void aiscript_chase_target(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 1;
}

/* was func_15075CCC */
void aiscript_intercept_target(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 16;
    g_cur_obj->unk231 = g_aiscript_arg1;
}

/* was func_15075D0C */
void aiscript_mode15(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 15;
}

/* was func_15075D38 */
void aiscript_mode14(void) {
    aiscript_chase_target();
    g_cur_obj->unk223 = 14;
}

/* was func_15075D64 */
void aiscript_mode12_player(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 12;
    g_cur_obj->unk222 = 0;
}

/* was func_15075D9C */
void aiscript_mode9(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 9;
}

/* was func_15075DC8 */
void aiscript_chase_target_alt(void) {
    aiscript_chase_target();
}

/* was func_15075DE8 */
void aiscript_goto_script(void) {
    if (g_aiscript_arg1 == 0) {
        g_aiscript_arg1 = g_cur_obj->unk232;
    }
    if (g_aiscript_arg3 != 0) {
        g_cur_obj->unk232 = g_aiscript_arg3;
    }
    g_cur_obj->unk218 = aiscript_find_by_kind(0, g_aiscript_arg1);
    g_cur_obj->unk218 -= 1;
}

/* was func_15075E6C */
void aiscript_flee_target(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 2;
}

/* was func_15075E98 */
void aiscript_set_reaction_script2(void) {
    g_cur_obj->unk235 = g_aiscript_arg0;
}

/* was func_15075EB4 */
void aiscript_if_random_percent(void) {
    if ((random_int() % 0x64U) < g_aiscript_arg2) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_15075F00 */
void aiscript_set_attack(void) {
    g_cur_obj->unk234 = g_aiscript_arg0;
    g_cur_obj->unk236 = g_aiscript_arg1;
    g_cur_obj->unk237 = g_aiscript_arg2;
}

/* was func_15075F40 */
void aiscript_mode3(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 3;
}

/* was func_15075F6C */
void aiscript_set_jump(void) {
    if (g_aiscript_arg0 != 0) {
        if (g_aiscript_arg2 == 0) {
            g_cur_obj->y_velocity = g_aiscript_arg0;
        } else {
            g_cur_obj->y_velocity = -g_aiscript_arg0;
        }
    }
    if (g_aiscript_arg1 != 0) {
        g_cur_obj->gravity = g_aiscript_arg1;
    }
    g_cur_obj->unk3A = g_aiscript_arg3;
}

extern f32 g_aiscript_one_twelfth; /* 1 / 12; was D_8009A500 */

// path_jump_to_point: P210: script command: jump (ballistic) to point g_aiscript_arg1 of the object's path
// (g_path_points[unk13F]); unk21E = that point. Flight time t = 2 * distance / speed (unk44); below 12 the speed is
// scaled by t / 12 and t = 12. unk21C = t * 100, upward velocity = gravity * t / 2, unk223 = 4.
/* was func_1507602C */
void aiscript_jump_to_point(void) {
    s16 *pt;
    f32 dx, dz;
    f32 t;

    aiscript_move_setup();
    g_cur_obj->unk21E = g_aiscript_arg1;
    pt = (s16 *)(g_path_points[g_cur_obj->unk13F] + g_aiscript_arg1 * 8 + 8);
    dx = pt[0] - g_cur_obj->x_position;
    dz = pt[2] - g_cur_obj->z_position;
    t = sqrtf(dx * dx + dz * dz) / g_cur_obj->unk44;
    t = t + t;
    if (t < 12.0f) {
        g_cur_obj->unk44 = g_cur_obj->unk44 * (t * g_aiscript_one_twelfth);
        t = 12.0f;
    }
    g_cur_obj->unk21C = t * 100.0f;
    g_cur_obj->y_velocity = g_cur_obj->gravity * t * 0.5f;
    g_cur_obj->unk223 = 4;
}
// NON-MATCHING: indexing is wrong
// void aiscript_jump_to_point(void) {
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f2;
//     struct169 *temp_v1;
//
//     aiscript_move_setup();
//     g_cur_obj->unk21E = g_aiscript_arg1;
//     temp_v1 = g_path_points[g_cur_obj->unk13F + g_aiscript_arg1]; // wrong
//     temp_f2 = temp_v1->unk8 - g_cur_obj->x_position;
//     temp_f12 = temp_v1->unkC - g_cur_obj->z_position;
//     temp_f14 = 2.0f * (sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12)) / g_cur_obj->unk44);
//     if (temp_f14 < 12.0f) {
//         g_cur_obj->unk44 *= temp_f14 * D_8009A140;
//         temp_f14 = 12.0f;
//     }
//     g_cur_obj->unk21C = temp_f14 * 100.0f;
//     g_cur_obj->y_velocity = g_cur_obj->gravity * temp_f14 * 0.5f;
//     g_cur_obj->unk223 = 4;
// }

/* was func_150761C8 */
void aiscript_walk_to_point(void) {
    aiscript_move_setup_path_point();
    g_cur_obj->unk223 = 5;
}

/* was func_150761F4 */
void aiscript_jump_at_target(void) {

    g_cur_obj->unk223 = 6;
    g_cur_obj->unk22C &= 0xFFFE;
}

/* was func_15076220 */
void aiscript_jump_at_point(void) {
    aiscript_jump_at_target();
    g_cur_obj->unk22C |= 1;
}

/* was func_15076250 */
void aiscript_play_sound_3d(void) {
    s32 tmp = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
    obj_sfx_play_attached(tmp, g_cur_obj, 0x7D00, -0x64, 0x1F4, 0x9C4, g_aiscript_arg2);
}

/* was func_150762B0 */
void aiscript_set_music_param(void) {
    music_players_set_fade_target(g_aiscript_arg0);
}

/* was func_150762D4 */
void aiscript_spawn_effect_above(void) {
    flash_blades_spawn(g_cur_obj->x_position, g_cur_obj->y_position + 100.0f, g_cur_obj->z_position, 0.45f, 0xFF, 0);
}

/* was func_15076340 */
void aiscript_if_flag107_clear(void) {
    if (g_cur_obj->unk107 == 0) {
        aiscript_branch(g_aiscript_arg0);
    }
    if (g_aiscript_arg1 != 0) {
        g_cur_obj->unk107 = 0;
    }
}

/* was func_15076394 */
void aiscript_set_attack_range(void) {
    g_cur_obj->unk236 = g_aiscript_arg0;
}

/* was func_150763B0 */
void aiscript_set_turn_rate(void) {

    if (g_aiscript_arg0 == 128) {
        g_cur_obj->unk1E5 = g_cur_obj->unk144->unkF;
    } else {
        g_cur_obj->unk1E5 = g_aiscript_arg0;
    }
    g_cur_obj->unk1E7 = 0;

    if (g_aiscript_arg2 != 0) {
        g_cur_obj->unk1E5 += (random_int() % (u32) g_aiscript_arg2);
    }
    if (g_aiscript_arg3 == 1) {
        g_cur_obj->unk1E6 = 0;
        g_cur_obj->unk1E8 = 0;
        return;
    }
    if (g_aiscript_arg3 == 2) {
        g_cur_obj->unk1E6 = g_aiscript_arg1;
        g_cur_obj->unk1E8 = 0;
        return;
    }
    if (g_aiscript_arg1 == 0) {
        g_cur_obj->unk1E6 = g_cur_obj->unk1E5;
        g_cur_obj->unk1E8 = 0;
    }
}

/* was func_150764C8 */
void aiscript_set_field238(void) {
    g_cur_obj->unk238 = g_aiscript_arg0;
}

/* was func_150764E4 */
void aiscript_set_field239(void) {
    g_cur_obj->unk239 = g_aiscript_arg0;
}

/* was func_15076500 */
void aiscript_set_field22e(void) {
    g_cur_obj->unk22E = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
}

/* was func_1507652C */
void aiscript_set_immune(void) {
    if (g_aiscript_arg1 != 0) {
        g_objects_immune[g_cur_obj->unk124 * 0x32C] = g_aiscript_arg0;
    } else {
        g_cur_obj->immune = g_aiscript_arg0;
    }
}

/* was func_1507659C */
void aiscript_raise_y(void) {
    g_cur_obj->y_position = g_cur_obj->y_position + g_aiscript_arg0 * 100;
    if (g_aiscript_arg3 != 0) {
        g_cur_obj->y_position = 1800.0f;
    }
}

/* was func_15076600 */
void aiscript_nop_a(void) {
}

/* was func_15076608 */
void aiscript_set_field24a(void) {
    g_cur_obj->unk24A = g_aiscript_arg0;
}

/* was func_15076624 */
void aiscript_set_flags_f8(void) {
    s32 tmp = (g_aiscript_arg0 << 0x18) | (g_aiscript_arg1 << 0x10) | (g_aiscript_arg2 << 8) | g_aiscript_arg3;
    g_cur_obj->unkF8 |= tmp;
}

/* was func_15076678 */
s32 aiscript_clear_flags_f8(void) {
    s32 tmp = (g_aiscript_arg0 << 0x18) | (g_aiscript_arg1 << 0x10) | (g_aiscript_arg2 << 8) | g_aiscript_arg3;
    g_cur_obj->unkF8 &= ~tmp;
}

/* was func_150766D0 */
void aiscript_wait_until_landed(void) {
    if (((g_cur_obj->unk28 > 0.0f) && (g_aiscript_arg0 == 0)) ||
        (((g_aiscript_arg0 * 0x32) < g_cur_obj->unk28) && (g_aiscript_arg0 != 0))) {
        g_cur_obj->unk21C = 99;
        g_cur_obj->unk218 -= 1;
    }
}

/* was func_15076760 */
void aiscript_nop_b(void) {
}

// ???
void hitinfo_from_obj_floor(f32 *, struct127 *);
s32 lava_splash_effect(f32 *, f32 *, s32, s32); /* P183: s32 as its C definition (stale v0, unused) */
void emitter_stop_for_obj(struct127 *);

/* was func_15076768 */
void aiscript_spawn_special_fx(void) {
    f32 pos[3];

    switch (g_aiscript_arg0) {
    case 0:
        emitter_stop_for_obj(g_cur_obj);
        break;
    case 1:
        pos[0] = *(f32 *)((u8 *)g_cur_obj + 0x14);
        pos[1] = -390.0f;
        pos[2] = *(f32 *)((u8 *)g_cur_obj + 0x1C);
        {
            f32 buf[9];
            hitinfo_from_obj_floor(buf, g_cur_obj);
            lava_splash_effect(pos, buf, 0xFF, 0);
        }
        break;
    }
}


/* was func_150767F4 */
void aiscript_if_facing_target(void) {
    struct127 *temp_v1 = &g_objects[g_cur_obj->unk222];
    u8 temp_t0 = math_atan2_u16(temp_v1->x_position - g_cur_obj->x_position, g_cur_obj->z_position - temp_v1->z_position, 0) >> 8;

    if ((((temp_t0 - (g_objects[g_cur_obj->unk222].unk7A >> 8)) + g_aiscript_arg1) & 0xFF) < (g_aiscript_arg1 * 2)) {
        aiscript_branch(g_aiscript_arg0);
    }
}

int aiscript_find_by_kind(s32, s32);

// find_visible_target: P210: script command: looks for the nearest object the current one can see: live (state,
// health), targetable (unkF8 bit 0x20), not itself, of another id unless g_aiscript_arg1 is set, within 50 in height,
// closer than g_aiscript_arg0 * 8 (obj_dist_3d), and inside its view cone (width byte 0x17 of its type record
// g_type_descs[id], in 1/256 turns around heading unk76 >> 8 + unk2CA). The nearest one is stored as unkA8 =
// 0x80 + its number; then the object's script jumps to g_aiscript_arg3 and, when g_aiscript_arg2 is set, the target's
// script to g_aiscript_arg2 with unk222 = the current object's number.
/* was func_150768DC */
void aiscript_find_visible_target(void) {
    s32 self = ((s32)g_cur_obj - (s32)g_objects) / 0x32C;
    f32 best = g_aiscript_arg0 * 8;
    struct127 *o = g_objects;
    struct127 *t;
    s32 i;
    f32 d;
    s32 fov;
    u16 ang;

    g_cur_obj->unkA8 = 0;
    for (i = 0; i < 25; i++, o++) {
        if (o->interaction_state == 0 || o->health == 0 || !(o->unkF8 & 0x20) || i == self) {
            continue;
        }
        if (g_aiscript_arg1 == 0 && g_cur_obj->id == o->id) {
            continue;
        }
        if (50.0f < fabsf(g_cur_obj->y_position - o->y_position)) {
            continue;
        }
        d = obj_dist_3d(g_cur_obj, o);
        if (!(d < best)) {
            continue;
        }
        fov = g_type_descs[g_cur_obj->id]->unk17;
        ang = math_atan2_u16(o->x_position - g_cur_obj->x_position, g_cur_obj->z_position - o->z_position, 0);
        if (((((g_cur_obj->unk76 >> 8) + g_cur_obj->unk2CA) - (ang >> 8) + fov / 2) & 0xFF) < fov) {
            g_cur_obj->unkA8 = i + 0x80;
            best = d;
        }
    }
    if (g_cur_obj->unkA8 != 0) {
        g_cur_obj->unk218 = (struct216 *)aiscript_find_by_kind(0, g_aiscript_arg3);
        g_cur_obj->unk218--;
        if (g_aiscript_arg2 != 0) {
            t = &g_objects[g_cur_obj->unkA8 & 0x7F];
            t->unk218 = NULL;
            t->unk232 = g_aiscript_arg2;
            t->unk222 = self;
        }
    }
}
// NON-MATCHING: almost JUSTREG
// void aiscript_find_visible_target(void) {
//     u8 temp_s2;
//     f32 temp_f20;
//     s32 temp_fp;
//     struct127 *temp_v0;
//     struct127 *current;
//     f32 phi_f22;
//     s32 i;
//     u8 tmp0;
//     struct124 *foo;
//     u8 tmp1;
//
//
//     phi_f22 = g_aiscript_arg0 * 8;
//     g_cur_obj->unkA8 = 0;
//     temp_fp = ((s32)g_cur_obj - (s32)g_objects) / (s32)sizeof(struct127);
//
//     for (i = 0; i < 25; i++) {
//         current = &g_objects[i];
//         if ((current->unk0 != 0) && (current->health != 0) && ((current->unkF8 & 0x20) != 0) && (i != temp_fp)) {
//             if ((g_aiscript_arg1 != 0) || (g_cur_obj->id != current->id)) {
//                 if (!(fabsf(g_cur_obj->y_position - current->y_position) > 50.0f)) {
//                     temp_f20 = obj_dist_3d(g_cur_obj, current);
//                     if (temp_f20 < phi_f22) {
//                         foo = g_type_descs[g_cur_obj->id];
//                         temp_s2 = foo->unk17;
//                         tmp1 = math_atan2_u16(current->x_position - g_cur_obj->x_position, g_cur_obj->z_position - current->z_position, 0) >> 8;
//                         if ((((((g_cur_obj->unk76 >> 8) + g_cur_obj->unk2CA) - tmp1) + (temp_s2 / 2)) & 0xFF) < temp_s2) {
//                             g_cur_obj->unkA8 = i;
//                             phi_f22 = temp_f20;
//                         }
//                     }
//                 }
//             }
//         }
//     }
//
//     if (g_cur_obj->unkA8 != 0) {
//         g_cur_obj->unk218 = aiscript_find_by_kind(0, g_aiscript_arg3);
//         g_cur_obj->unk218 -= 1;
//         tmp0 = g_aiscript_arg2;
//         if (tmp0 != 0) {
//             temp_v0 = &g_objects[g_cur_obj->unkA8 & 0x7F];
//             temp_v0->unk218 = 0;
//             temp_v0->unk232 = tmp0;
//             temp_v0->unk222 = temp_fp;
//         }
//     }
// }

/* was func_15076B5C */
void aiscript_target_seen_object(void) {
    g_cur_obj->unk222 = (g_cur_obj->unkA8 & 0x7F);
}

/* was func_15076B78 */
void aiscript_set_field5(void) {
    g_cur_obj->unk5 = g_aiscript_arg0;
}

/* was func_15076B94 */
void aiscript_goto_object_by_id(void) {
    s32 idx = ((s32)g_cur_obj - (s32)g_objects) / (s32)sizeof(struct127);

    if (g_aiscript_arg1) {
        idx = 25;
    }
    while (idx != 0) {
        if ((g_aiscript_arg0 == g_objects[idx-1].id) && (g_objects[idx-1].health != 0)) {
            aiscript_move_setup();
            g_cur_obj->unk223 = 9;
            g_cur_obj->unk222 = idx - 1;
            g_cur_obj->unk21C = 1000;
            return;
        }
        idx--;
    };
}

/* was func_15076C7C */
void aiscript_fade_cmd(void) {
    obj_fade_command(g_cur_obj, 1, g_aiscript_arg0, 0, 0);
}

/* was func_15076CB4 */
void aiscript_heading_to_target(void) {
    g_cur_obj->unk76 = g_cur_obj->unk78;
}

/* was func_15076CCC */
void aiscript_remove_wait_long(void) {
    g_cur_obj->unk21C = 10000;
    obj_remove(g_cur_obj, 1);
}

/* was func_15076D04 */
void aiscript_set_xz_velocity(void) {
    g_cur_obj->xz_velocity = g_aiscript_arg0;
}

// object_set_scale: P210: script command: sets the current object's scale from the command bytes (two s16 in
// hundredths: g_aiscript_arg0 / g_aiscript_arg1 = xz, g_aiscript_arg2 / g_aiscript_arg3 = y, low byte first; g_aiscript_hundredth = 0.01),
// copies it to unk154 / unk158 and applies it with obj_set_scale.
/* was func_15076D3C */
void aiscript_set_scale(void) {
    s16 xz = g_aiscript_arg0 | (g_aiscript_arg1 << 8);
    s16 y = g_aiscript_arg2 | (g_aiscript_arg3 << 8);

    g_cur_obj->xz_scale = xz * g_aiscript_hundredth;
    g_cur_obj->y_scale = y * g_aiscript_hundredth;
    g_cur_obj->unk154 = g_cur_obj->xz_scale;
    g_cur_obj->unk158 = g_cur_obj->y_scale;
    obj_set_scale(g_cur_obj, g_cur_obj->xz_scale, g_cur_obj->y_scale);
}
// ???
// void aiscript_set_scale(void) {
//     s32 temp_a3;
//     s32 tmp2;
//
//     temp_a3 = g_aiscript_arg2 | (g_aiscript_arg3 << 8);
//     tmp2 = g_aiscript_arg0 | (g_aiscript_arg1 << 8);
//     g_cur_obj->xz_scale = (s16)tmp2 * D_8009A144;
//     g_cur_obj->y_scale = (s16)temp_a3 * D_8009A144;
//     g_cur_obj->unk154 = g_cur_obj->xz_scale;
//     g_cur_obj->unk158 = g_cur_obj->y_scale;
//     obj_set_scale(&g_cur_obj, g_cur_obj->xz_scale, g_cur_obj->y_scale);
// }

/* was func_15076DF4 */
void aiscript_set_interaction_state(void) {
    g_cur_obj->interaction_state = g_aiscript_arg0;
}

/* was func_15076E10 */
void aiscript_set_field1d0(void) {
    g_cur_obj->unk1D0 = g_aiscript_arg0;
    g_cur_obj->unk22C |= g_aiscript_arg1;
}

/* was func_15076E48 */
void aiscript_nop_c(void) {
}

/* was func_15076E50 */
void aiscript_random_hop(void) {
    aiscript_move_setup();
    g_cur_obj->y_velocity = ((f32) (u32) (random_int() % 0x14U) + 55.0f);
    g_cur_obj->gravity = 2.0f;
    g_cur_obj->unk78 = random_int() % 0xFFFFU;
    g_cur_obj->xz_velocity = (u32) ((random_int() % 0x14U) + 0xF);
    g_cur_obj->unk44 = g_cur_obj->xz_velocity;
    g_cur_obj->unk223 = 7;
}

/* was func_15076F40 */
void aiscript_remove_wait(void) {
    g_cur_obj->unk21C = 1000;
    obj_remove(g_cur_obj, 1);
}

/* was func_15076F78 */
void aiscript_set_fieldcc(void) {
    s8 tmp;
    tmp = g_aiscript_arg0;
    g_cur_obj->unkCC = tmp;
    tmp = g_aiscript_arg1;
    g_cur_obj->unkCE = tmp;
}

/* was func_15076FA8 */
void aiscript_jitter_position(void) {
    if (g_aiscript_arg3 == 0) {
        s16 tmp;
        tmp = (random_int() % (u32) g_aiscript_arg0) - (g_aiscript_arg0 / 2);
        g_cur_obj->x_position += tmp * 3.0f;
        tmp = (random_int() % (u32) g_aiscript_arg1) - (g_aiscript_arg1 / 2);
        g_cur_obj->z_position += tmp * 3.0f;
    } else {
        if (g_cur_obj->xz_velocity < g_aiscript_arg3) {
            g_cur_obj->xz_velocity = g_aiscript_arg3;
        }
    }
}

/* was func_150770E4 */
void aiscript_if_target_slower(void) {
    if (g_objects[g_cur_obj->unk222].xz_velocity < (f32)(u32)g_aiscript_arg2) {
        aiscript_branch(g_aiscript_arg3);
    }
}

/* was func_15077174 */
void aiscript_set_field10e(void) {
    g_cur_obj->unk10E = g_aiscript_arg0;
}

/* was func_15077190 */
void aiscript_play_sound_3d_b(void) {
    s32 tmp0 = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
    if (tmp0 != 0) {
        s32 tmp1 = g_aiscript_arg2 << 7;
        actor_sound_play_untracked(tmp0, g_cur_obj, tmp1, 0x1F4, 0x9C4);
    }
}

/* was func_150771F0 */
void aiscript_fade_or_anim_cmd(void) {
    u8 var_a1;
    u8 a2, a3;

    if (g_aiscript_arg3 == 0) {
        a2 = g_aiscript_arg0;
        a3 = g_aiscript_arg1;
        if (g_aiscript_arg2 != 0) {
            var_a1 = 1;
        } else {
            var_a1 = 2;
        }
        obj_fade_command(g_cur_obj, var_a1, a2, a3, 0);
    } else if (g_aiscript_arg2 == 0) {
        obj_tint_fade_in(g_cur_obj, g_aiscript_arg0);
    } else {
        obj_tint_fade_out(g_cur_obj, g_aiscript_arg0);
    }
}

/* was func_15077294 */
void aiscript_set_health(void) {
    switch (g_aiscript_arg1) {
        case 0:
            g_cur_obj->health = g_aiscript_arg0;
            break;
        case 1:
            g_cur_obj->health--;
            break;
    }
}

/* was func_150772E8 */
void aiscript_set_flag_entry(void) {
    breakable_request_flag_entry(g_cur_obj, g_aiscript_arg0, -1);
}

/* was func_15077318 */
void aiscript_set_flag101_bit0(void) {
    if (g_aiscript_arg0 != 0) {
        g_cur_obj->unk101 |= 1;
    } else {
        g_cur_obj->unk101 &= 0xFFFE;
    }
}

/* was func_1507735C */
void aiscript_nop_d(void) {

}

/* was func_15077364 */
void aiscript_set_field246(void) {
    if (g_aiscript_arg3 != 0) {
        g_aiscript_arg0 += random_int() % (u32) g_aiscript_arg3;
    }
    g_cur_obj->unk246 = (u8) g_aiscript_arg0;
    g_cur_obj->unk249 = (u8) 0;
    g_cur_obj->unk247 = (u8) g_aiscript_arg1;
    g_cur_obj->unk248 = (u8) g_aiscript_arg2;
}

// ??
/* was func_15077404 */
void aiscript_adjust_field246(void) {
    s16 var_v0;

    if (g_aiscript_arg3 != 0) {
        var_v0 = ((g_cur_obj->unk246 & 0x1F) << 8) + g_cur_obj->unk249 + ((s16) ((g_aiscript_arg1 << 8) + g_aiscript_arg2) * g_frame_ticks);
        if (var_v0 < 0) {
            var_v0 = 0;
        }
        g_cur_obj->unk246 = (var_v0 >> 8) | 0x80;
        g_cur_obj->unk249 = (u8) var_v0;
        return;
    }
    g_cur_obj->unk246 = g_aiscript_arg0;
}
/* was func_150774B4 */
void aiscript_if_nav_arrived(void) {
    if ((g_cur_obj->unk20F == g_cur_obj->unk211) || (g_cur_obj->unk211 == 0xFF)) {
        g_cur_obj->unk25C |= 0x800;
        aiscript_branch(g_aiscript_arg0);
    }
}

s32 rail_point_pick(f32, f32, f32, s8, s8, u8 *, u8 *); /* P98: from the asm (f12, f14, a2 = z bits, a3, 3 stack words) */
s32 rail_route_next(u8, s8, s8, u8 *, u8 *);
s32 rail_node_position(s32, f32 *, f32 *, f32 *);
extern s32 g_rail_route_dist; /* was D_800D277C */

/* was func_15077508 */
void aiscript_nav_next_node(void) {
    struct {
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
    } sp;
    s8 sp76;
    s32 sp70;
    s32 sp6C;
    f32 sp58;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    struct_eu_800D2778 *sp3C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 var_f2;
    f32 var_f2_2;
    s32 var_a0;
    s32 var_a1_2;
    s32 var_v0;
    s32 var_v1_2;
    s8 var_a1;
    struct127 *temp_v0_2;
    struct_eu_800D2778 *var_v1;
    u8 temp_t2;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;

    sp.u84 = 0xFF;
    if (g_aiscript_arg0 != 1) {
        temp_v1 = g_cur_obj->unk211;
        if (temp_v1 == g_cur_obj->unk20F) {
            (*(s16 *)((u8 *)g_cur_obj + 0x216)) = 0;
            g_cur_obj->unk25C |= 0x800;
            return;
        }
        if (temp_v1 == 0xFF) {
            (*(s16 *)((u8 *)g_cur_obj + 0x216)) = 0;
        }
        goto block_5;
    }
block_5:
    g_cur_obj->unk25C &= ~0x800;
    if ((g_path_point_counts[g_cur_obj->unk13F] - 1) > 0) {
        sp76 = 0;
        var_a1 = 0;
        if (g_cur_obj->unk211 != 0xFF) {
            var_a1 = 1;
        }
        if (g_cur_obj->pad212 != 0xFF) {
            sp76 = 1;
        }
        temp_v1_2 = g_cur_obj->unk20F;
        if (temp_v1_2 == 0xFF) {
            if (g_aiscript_arg0 == 1) {
                sp76 = 0;
                var_a1 = 0;
                sp.u84 = (s32) g_cur_obj->unk210;
            }
            if (sp.u84 == 0xFF) {
                var_v0 = rail_point_pick(g_cur_obj->x_position, g_cur_obj->y_position, g_cur_obj->z_position, var_a1, sp76, &g_cur_obj->unk211, &g_cur_obj->pad212);
                goto block_28;
            }
        } else if (temp_v1_2 != 0xFF) {
            if (g_aiscript_arg0 == 1) {
                var_a1_2 = 0xFF;
                if (g_cur_obj->unk210 != 0xFF) {

                }
                var_f2 = 10.0f;
                var_a0 = 0;
                var_v1 = &g_rail_nodes[temp_v1_2];
                do {
                    temp_v0 = var_v1->pad8[1];
                    if ((temp_v0 != 0xFF) && (g_cur_obj->unk210 != temp_v0)) {
                        sp3C = var_v1;
                        sp70 = var_a0;
                        sp6C = var_a1_2;
                        sp58 = var_f2;
                        temp_f0 = random_float();
                        if (temp_f0 < var_f2) {
                            var_f2 = temp_f0;
                            var_a1_2 = (s32) var_v1->pad8[1];
                        }
                    }
                    var_a0 += 1;
                    var_v1 = (struct_eu_800D2778 *)((u8 *)var_v1 + (1));
                } while (var_a0 != 5);
                var_v1_2 = var_a1_2;
                if (var_a1_2 == 0xFF) {
                    g_cur_obj->unk25C |= 0x800;
                    var_v1_2 = (s32) g_cur_obj->unk210;
                }
                sp.u84 = var_v1_2;
            } else {
                var_v0 = rail_route_next(temp_v1_2, var_a1, sp76, &g_cur_obj->unk211, &g_cur_obj->pad212);
block_28:
                sp.u84 = var_v0;
            }
        }
        if (sp.u84 != 0xFF) {
            g_cur_obj->unk21E = 0;
            if (rail_node_position(sp.u84, &sp.u80, &sp.u7C, &sp.u78) != 0) {
                (*(s16 *)((u8 *)g_cur_obj + 0x216)) = (s16) g_rail_route_dist;
                g_cur_obj->unk210 = g_cur_obj->unk20F;
                g_cur_obj->unk20F = (u8) sp.u84;
                temp_t2 = g_rail_nodes[sp.u84].pad8[0];
                var_f2_2 = (f32) temp_t2;
                if ((s32) temp_t2 < 0) {
                    var_f2_2 += 4294967296.0f;
                }
                temp_v0_2 = g_cur_obj;
                temp_f14 = sp.u80 - temp_v0_2->x_position;
                temp_f16 = sp.u78 - temp_v0_2->z_position;
                temp_f18 = 2.0f * var_f2_2;
                temp_f12 = sqrtf((temp_f14 * temp_f14) + (temp_f16 * temp_f16));
                if (temp_f12 > 1.0f) {
                    sp40 = temp_f12;
                    sp48 = temp_f14;
                    sp44 = temp_f16;
                    sp4C = temp_f18;
                    temp_f12_2 = (random_float() * temp_f18) / temp_f12;
                    sp.u80 -= temp_f16 * temp_f12_2;
                    sp.u78 += temp_f14 * temp_f12_2;
                }
                (*(s16 *)((u8 *)(g_path_points[temp_v0_2->unk13F]) + 8)) = (s16) (s32) sp.u80;
                (*(s16 *)((u8 *)(g_path_points[g_cur_obj->unk13F]) + 0xA)) = (s16) (s32) sp.u7C;
                (*(s16 *)((u8 *)(g_path_points[g_cur_obj->unk13F]) + 0xC)) = (s16) (s32) sp.u78;
            }
        }
    }
}
/* was func_150778F0 */
void aiscript_path_advance(void) {
    u8 var_v0 = g_path_point_counts[g_cur_obj->unk13F] - 1;

    if (g_cur_obj->unk21F != 0) {
        var_v0 = g_cur_obj->unk21F;
    }
    g_cur_obj->unk21E += g_cur_obj->unk221;
    g_cur_obj->unk21E += var_v0;
    g_cur_obj->unk21E %= var_v0;
    if (g_cur_obj->unk21E < g_cur_obj->unk220) {
        g_cur_obj->unk21E = g_cur_obj->unk220;
    }
}

/* was func_150779A8 */
void aiscript_mode11_path_point(void) {
    aiscript_move_setup_path_point();
    g_cur_obj->unk223 = 0xB;
}

/* was func_150779D4 */
void aiscript_if_near_object(void) {
    u8 var_v0 = 0;
    struct127 *temp_a1;
    f32 dist;
    f32 range;

    if (g_aiscript_arg2 != 0) {
        var_v0 = g_cur_obj->unk222;
    }
    if (g_cur_obj_index != var_v0) {
        temp_a1 = &g_objects[var_v0];
        if ((temp_a1->interaction_state != 1) || (temp_a1->unk65 == 0)) {
            dist = obj_dist_xz(g_cur_obj, temp_a1);
            range = g_aiscript_arg3 * 8;
            if (dist < range) {
                aiscript_branch(g_aiscript_arg0);
            }
        }
    }
}

/* was func_15077AA0 */
void aiscript_set_field239_b(void) {
    g_cur_obj->unk239 = g_aiscript_arg0;
}

/* was func_15077ABC */
void aiscript_set_field258(void) {
    g_cur_obj->unk258 = g_aiscript_arg0;
    g_cur_obj->unk257 = g_aiscript_arg1;
    g_cur_obj->unk86 = random_int() % 0xFFU;
}

/* was func_15077B14 */
void aiscript_set_field24c(void) {
    g_cur_obj->unk24C = g_aiscript_arg0;
    g_cur_obj->unk24D = g_aiscript_arg1;
}

/* was func_15077B44 */
void aiscript_play_sound(void) {
    obj_sfx_play((g_aiscript_arg0 << 8) + g_aiscript_arg1, g_cur_obj);
}

/* was func_15077B80 */
void aiscript_set_flags_25c(void) {
    s32 tmp = (g_aiscript_arg0 << 8) + g_aiscript_arg1;
    g_cur_obj->unk25C |= tmp;
}

/* was func_15077BB4 */
void aiscript_send_script_to_id(void) {
    struct127 *tmp = obj_find_by_id(g_aiscript_arg1);
    tmp->unk218 = 0;
    tmp->unk232 = g_aiscript_arg0;
}

/* was func_15077BE4 */
void aiscript_clear_flags_25c(void) {
    s32 tmp = ~((g_aiscript_arg0 << 8) + g_aiscript_arg1);
    g_cur_obj->unk25C &= tmp;
}

/* was func_15077C1C */
void aiscript_set_sight_range(void) {
    g_cur_obj->unk23D = g_aiscript_arg0;
}

/* was func_15077C38 */
void aiscript_find_target(void) {
    struct127 *phi_s0;
    f32 tmp0;
    f32 distance;
    s32 i;

    tmp0 = g_aiscript_find_max_dist;
    g_cur_obj->unk222 = (u8)0;

    for (i = 0; i < 25; i++) {
        phi_s0 = &g_objects[i];
        if (((phi_s0->interaction_state != 0) && (phi_s0->health != 0)) &&
            ((phi_s0->immune == 0) || (phi_s0->immune == 0xFF)) &&
            ((phi_s0->unk65 == 0) || (g_aiscript_arg2 != 0)) &&
            ((phi_s0->id == g_aiscript_arg0) || ((phi_s0->interaction_state == g_aiscript_arg1) &&
            (phi_s0->stunned == 0)))) {
            if (g_aiscript_arg3 == 0) {
                g_cur_obj->unk222 = i;
                return;
            }
            distance = obj_dist_3d(g_cur_obj, phi_s0);
            if (tmp0 > distance) {
                g_cur_obj->unk222 = i;
                tmp0 = distance;
            }
        }
    }
}

/* was func_15077DA0 */
void aiscript_set_path_point(void) {
    g_cur_obj->unk21E = g_aiscript_arg0;
}

/* was func_15077DBC */
void aiscript_warp_to_path_point(void) {
    if (g_aiscript_arg0 != 0xFA) {
        g_cur_obj->unk21E = g_aiscript_arg0;
    }
    g_cur_obj->x_position = ((s16 (*)[4])g_path_points[g_cur_obj->unk13F])[g_cur_obj->unk21E][4];
    g_cur_obj->y_position = ((s16 (*)[4])g_path_points[g_cur_obj->unk13F])[g_cur_obj->unk21E][5];
    g_cur_obj->z_position = ((s16 (*)[4])g_path_points[g_cur_obj->unk13F])[g_cur_obj->unk21E][6];
}

/* was func_15077E9C */
void aiscript_play_sound_3d_c(void) {
    s32 tmp = ((g_aiscript_arg0 << 8) + g_aiscript_arg1);
    mp3_voice_play_at_object(tmp, g_cur_obj, 0x5DC0, 0x1F4, 0x9C4);
}

/* was func_15077EEC */
void aiscript_set_field254(void) {
    g_cur_obj->unk254 = g_aiscript_arg0;
}

/* was func_15077F08 */
void aiscript_set_field1ea(void) {
    g_cur_obj->unk1EA = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
}

/* was func_15077F34 */
void aiscript_set_field24f(void) {
    g_cur_obj->unk24F = g_aiscript_arg0;
    g_cur_obj->unk250 = g_aiscript_arg1;
}

/* was func_15077F64 */
void aiscript_turn_to_point_react(void) {
    u8 sp1E;
    s32 temp_t3;
    s32 var_a0;
    s32 var_a1;
    u8 temp_t6;
    u8 *temp_v0;

    temp_t6 = g_aiscript_arg0 - 1;
    temp_v0 = g_path_points[g_cur_obj->unk13F] + (g_cur_obj->unk21E * 8);
    sp1E = temp_t6;
    g_cur_obj->unk78 = math_atan2_u16((f32) (*(s16 *)((u8 *)temp_v0 + 8)) - g_cur_obj->x_position, g_cur_obj->z_position - (f32) (*(s16 *)((u8 *)temp_v0 + 0xC)), 0);
    temp_t3 = ((s32) (g_cur_obj->unk78 - g_cur_obj->unk76) >> 8) & 0xFF;
    var_a1 = temp_t3;
    var_a0 = temp_t3;
    if (temp_t3 & 0x80) {
        var_a0 = -temp_t3 & 0xFF;
        var_a1 = var_a0;
    }
    if ((s32) *g_hit_reaction_anims[temp_t6] < var_a0) {
        g_cur_obj->unk250 = g_aiscript_arg1;
        obj_start_hit_reaction(g_cur_obj, var_a1, temp_t6 & 0xFF);
    }
}
// NON-MATCHING: what is g_path_points ???
// void obj_start_hit_reaction(s32, s32, u8);
// void aiscript_turn_to_point_react(void) {
//     u8 temp_t6;
//     struct169 *temp_v0;
//     s32 phi_a0;
//     s32 phi_a1;
//
//     temp_t6 = g_aiscript_arg0 - 1;
//     temp_v0 = g_path_points[g_cur_obj->unk13F] + (g_cur_obj->unk21E);
//     g_cur_obj->unk78 = math_atan2_u16(temp_v0->unk8 - g_cur_obj->x_position, g_cur_obj->z_position - temp_v0->unkC, 0);
//     phi_a0 = phi_a1 = ((s32) (g_cur_obj->unk78 - g_cur_obj->unk76) >> 8) & 0xff;
//     if ((phi_a0 & 0x80) != 0) {
//         phi_a1 = phi_a0 = -phi_a0 & 0xFF;
//     }
//     if ((u8)D_80099A3C[temp_t6 * 0xA] < phi_a0) {
//         g_cur_obj->unk250 = (u8) g_aiscript_arg1;
//         obj_start_hit_reaction(g_cur_obj, phi_a1, temp_t6);
//     }
// }

/* was func_15078074 */
void aiscript_if_any_object_near(void) {
    f32 temp_f20;
    struct127 *tmp;
    s32 i;

    temp_f20 = 8 * g_aiscript_arg3;

    for (i = 0; i < 25; i++) {
        tmp = &g_objects[i];
        if ((tmp->interaction_state != 0) && (g_cur_obj_index != i)) {
            if (obj_dist_xz(g_cur_obj, tmp) < temp_f20) {
                aiscript_branch(g_aiscript_arg0);
                return;
            }
        }
    }
}

/* was func_1507813C */
void aiscript_if_target_gone(void) {
    s32 idx = g_cur_obj->unk222;
    if (g_objects[idx].interaction_state == 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_150781A4 */
void aiscript_set_fields23f(void) {
    g_cur_obj->unk23F = g_aiscript_arg1;
    g_cur_obj->unk240 = g_aiscript_arg2;
    g_cur_obj->unk241 = g_aiscript_arg0;
    g_cur_obj->unk242 = g_aiscript_arg3;
}

// another function with g_path_points
/* was func_150781F4 */
void aiscript_if_point_dist(void) {
    f32 dx;
    f32 dz;
    f32 dist;
    s16 *temp_v1;
    s32 idx = g_aiscript_arg1 + 1;

    temp_v1 = ((s16 (*)[4])g_path_points[g_cur_obj->unk13F])[idx];
    dx = temp_v1[0] - g_cur_obj->x_position;
    dz = temp_v1[2] - g_cur_obj->z_position;
    dist = sqrtf((dx * dx) + (dz * dz));
    dx = g_aiscript_arg3 * 8;
    if (((g_aiscript_arg2 == 0) && (dist < dx)) || ((g_aiscript_arg2 != 0) && (dx < dist))) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_150782CC */
void aiscript_set_field23e(void) {
    g_cur_obj->unk23E = g_aiscript_arg0;
}

/* was func_150782E8 */
void aiscript_if_unique_id(void) {
    if (((g_aiscript_arg2 == 0) && (g_cur_obj->unique_id == g_aiscript_arg1)) ||
        ((g_aiscript_arg2 == 1) && (g_cur_obj->unique_id != g_aiscript_arg1))) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_15078358 */
void aiscript_target_by_unique_id(void) {
    s32 tmp = obj_slot_by_setup_id(g_aiscript_arg0);
    g_cur_obj->unk222 = tmp;
    if (tmp == -1) {
        g_cur_obj->unk222 = 0;
    }
}

/* was func_1507839C */
void aiscript_if_target_dist(void) {
    f32 var_f0;
    f32 var_f2;

    if (g_aiscript_arg2 == 0) {
        var_f0 = obj_dist_xz(g_cur_obj, &g_objects[g_cur_obj->unk222]);
    } else if (g_aiscript_arg2 == 1) {
        var_f0 = obj_dist_3d(g_cur_obj, &g_objects[g_cur_obj->unk222]);
    } else {
        var_f0 = fabsf(g_cur_obj->y_position - *(f32 *)((u8 *)g_objects_y + g_cur_obj->unk222 * 0x32C));
    }
    var_f2 = (f32) (g_aiscript_arg3 * 8);
    if (g_aiscript_arg3 == 0xFF) {
        var_f2 = (f32) (g_cur_obj->unk23D * 8);
    }
    if (((g_aiscript_arg1 == 0) && (var_f0 < var_f2)) || ((g_aiscript_arg1 == 1) && (var_f2 < var_f0))) {
        aiscript_branch((s32) g_aiscript_arg0);
    }
}
// NON-MATCHING: JUSTREG
// void aiscript_if_target_dist(void) {
//     struct127 *tmp;
//     f32 phi_f0;
//     f32 phi_f2;
//
//     if (g_aiscript_arg2 == 0) {
//         tmp = &g_objects[g_cur_obj->unk222];
//         phi_f0 = obj_dist_xz(g_cur_obj, tmp);
//     } else if (g_aiscript_arg2 == 1) {
//         tmp = &g_objects[g_cur_obj->unk222];
//         phi_f0 = obj_dist_3d(g_cur_obj, tmp);
//     } else {
//         phi_f0 = fabsf(g_cur_obj->y_position - g_objects[g_cur_obj->unk222].y_position);
//     }
//
//     phi_f2 = g_aiscript_arg3 * 8;
//     if (g_aiscript_arg3 == 0xFF) {
//         phi_f2 = g_cur_obj->unk23D * 8;
//     }
//     if (((g_aiscript_arg1 == 0) && (phi_f0 > phi_f2)) ||
//         ((g_aiscript_arg1 == 1) && (phi_f0 > phi_f2))) {
//         aiscript_branch(g_aiscript_arg0);
//     }
// }

/* was func_15078520 */
void aiscript_jump(void) {
    aiscript_branch(g_aiscript_arg0);
}

f32 math_cos_u8(u8);

// path_point_from_object: P210: script command: sets point g_aiscript_arg0 & 0x3F of the current object's path
// (g_path_points[unk13F], s16 x / y / z after an 8-byte header) to an offset from object unk222 (g_objects). The
// offset is x = 8 * (s8 g_aiscript_arg1 << 4 | g_aiscript_arg3 >> 4), z = 8 * (s8 g_aiscript_arg2 << 4 | g_aiscript_arg3 & 0xF),
// rotated by the object's heading (g_aiscript_arg0 bits 6-7 = 0), not rotated (1), or by the direction from the
// object to the current one (2, 3); y is the object's height. g_aiscript_arg0 keeps the masked point number.
/* was func_15078544 */
void aiscript_path_point_from_target(void) {
    u8 cmd = g_aiscript_arg0;
    struct127 *o;
    s32 mode;
    f32 ox, oz;
    f32 x, y, z;
    f32 s, c;
    s16 *pt;

    g_aiscript_arg0 = cmd & 0x3F;
    o = &g_objects[g_cur_obj->unk222];
    ox = (((s8)g_aiscript_arg1 << 4) | (g_aiscript_arg3 >> 4)) << 3;
    oz = (((s8)g_aiscript_arg2 << 4) | (g_aiscript_arg3 & 0xF)) << 3;
    mode = cmd >> 6;
    y = o->y_position;
    x = o->x_position;
    z = o->z_position;
    if (mode == 0) {
        u8 a = (o->unk7A >> 8) - 0x40;

        s = math_sin_u8(a);
        c = math_cos_u8(a);
    } else if (mode == 1) {
        s = 0.0f;
        c = 1.0f;
    } else {
        f32 ang = math_atan2f(g_cur_obj->x_position - x, g_cur_obj->z_position - z);

        s = sinf(ang);
        c = cosf(ang);
    }
    x += ox * c + oz * s;
    z += oz * c - ox * s;
    pt = (s16 *)(g_path_points[g_cur_obj->unk13F] + g_aiscript_arg0 * 8 + 8);
    pt[0] = x;
    pt = (s16 *)(g_path_points[g_cur_obj->unk13F] + g_aiscript_arg0 * 8 + 8);
    pt[1] = y;
    pt = (s16 *)(g_path_points[g_cur_obj->unk13F] + g_aiscript_arg0 * 8 + 8);
    pt[2] = z;
}
/* was func_1507879C */
void aiscript_if_target_2d0_x(void) {
    struct197 *temp_v0 = g_objects[g_cur_obj->unk222].unk2D0;
    f32 temp_f0 = temp_v0->unk8;

    if (((g_aiscript_arg2 == 0) && (temp_f0 < (u32)g_aiscript_arg1)) || ((g_aiscript_arg2 == 1) && ((u32)g_aiscript_arg1 < temp_f0))) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_15078874 */
void aiscript_set_counter251(void) {
    g_cur_obj->unk251 = g_aiscript_arg0;
}

/* was func_15078890 */
void aiscript_if_counter251(void) {
    if (((g_aiscript_arg2 == 0) && (g_cur_obj->unk251 == g_aiscript_arg1)) ||
        ((g_aiscript_arg2 == 1) && (g_cur_obj->unk251 != g_aiscript_arg1))) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_15078900 */
void aiscript_if_target_counter251(void) {
    if (g_aiscript_arg3 != 0) {
        if (g_cur_obj->unk222 == 0) {
            aiscript_branch(g_aiscript_arg0);
        }
    } else {
        if (((g_aiscript_arg2 == 0) && (g_aiscript_arg1 == g_objects_counter_251[g_cur_obj->unk222 * 0x32C])) ||
            ((g_aiscript_arg2 == 1) && (g_aiscript_arg1 != g_objects_counter_251[g_cur_obj->unk222 * 0x32C]))) {
            aiscript_branch(g_aiscript_arg0);
        }
    }
}

/* was func_15078A08 */
void aiscript_copy_target_2d0_pos(void) {
    struct197 *temp_a0;
    struct197 *temp_v0;

    temp_v0 = g_cur_obj->unk2D0;
    temp_a0 = g_objects_2d0[g_cur_obj->unk222].interaction_state; // wtf
    temp_v0->unk8 = (f32) temp_a0->unk8;
    temp_v0->unkC = (f32) temp_a0->unkC;
}

// requires jump table
/* P183 */
f32 math_atan2f(f32, f32);
extern u8 g_objects_unk2e4[]; /* was D_800CC9D4 */
extern u8 g_obj2_unkb0[]; /* was D_800CC9D8 */
extern u8 g_obj2_unkb4[]; /* was D_800CC9DC */
extern u8 g_obj1_unk138[]; /* was D_800CC734 */
extern u8 g_held_item_obj_id[]; /* was D_800CC82C */
extern u8 g_obj1_unk11c[]; /* was D_800CC718 */
extern u8 g_obj1_unk1f6; /* was D_800CC7F2 */
extern u8 g_aiscript_cheat_value; /* was D_800BEE0C */
extern u8 g_player_health[]; /* was D_800CC8BA */
extern u8 g_obj1_unk326[]; /* was D_800CC922 */
extern u8 g_obj1_unk17d[]; /* was D_800CC779 */

// script_test_object_value: P183: script condition: reads value g_aiscript_arg2 (0..18) of object `idx` (0x32C-byte
// records of g_objects; some values come from the global object g_objects_state or the player's +0x222 object) and
// compares it with g_aiscript_arg3 by operator g_aiscript_arg1 (0 ==, 1 !=, 2 <, 3 >, 4 <=, 5 >=). Value 6 is the angle
// difference 0..128 (256 per turn) between the object's heading (+0x7A >> 8, - 0x40) and its direction to the
// player g_cur_obj; value 9 is 2 when the object's +0xCA0C record has +0x8 and +0x16 set. Returns 1 when true.
// For a value kind above 18 the asm compares an unset stack slot (kept: `v` uninitialised there).
/* was func_15078A60 */
s32 aiscript_test_object_value(s32 idx) {
    s32 v;
    s32 off = idx * 0x32C;
    u8 *obj;
    u8 *rec;
    u8 heading;
    u8 diff;

    switch (g_aiscript_arg2) {
        case 0:
            v = *(f32 *) ((u8 *) g_objects_xz_velocity + off);
            break;
        case 1:
            v = *(s32 *) (g_objects_unk2e4 + off);
            break;
        case 2:
            v = *(s32 *) (g_obj2_unkb0 + off);
            break;
        case 3:
            v = *(s32 *) (g_obj2_unkb4 + off);
            break;
        case 4:
            v = *(f32 *) ((u8 *) g_objects_y + off);
            break;
        case 5:
            v = *(f32 *) (g_obj1_unk138 + off);
            break;
        case 6:
            obj = (u8 *) g_objects + off;
            heading = (*(u16 *) (obj + 0x7A) >> 8) - 0x40;
            diff = (u32) (math_atan2f(*(f32 *) (obj + 0x14) - *(f32 *) ((u8 *) g_cur_obj + 0x14),
                                        *(f32 *) (obj + 0x1C) - *(f32 *) ((u8 *) g_cur_obj + 0x1C)) *
                          40.743664f) -
                   heading;
            v = diff;
            if (diff > 0x80) {
                v = 0x100 - diff;
            }
            break;
        case 7:
            v = g_held_item_obj_id[off];
            break;
        case 8:
            v = g_objects_stunned[off];
            break;
        case 9:
            rec = *(u8 **) ((u8 *) &g_objects_state + off);
            v = 0;
            if (*(s16 *) (rec + 0x8) != 0 && rec[0x16] != 0) {
                v = 2;
            }
            break;
        case 10:
            v = *(f32 *) (g_obj1_unk11c + off);
            break;
        case 11:
            v = g_objects_state[0x78];
            break;
        case 12:
            v = g_objects_state[0x7D];
            break;
        case 13:
            v = g_obj1_unk1f6;
            break;
        case 14:
            v = g_aiscript_cheat_value;
            break;
        case 15:
            v = g_objects_id[((u8 *) g_cur_obj)[0x222] * 0x32C];
            break;
        case 16:
            v = g_player_health[off];
            break;
        case 17:
            v = g_obj1_unk326[((u8 *) g_cur_obj)[0x222] * 0x32C];
            break;
        case 18:
            v = g_obj1_unk17d[off];
            break;
    }
    if ((g_aiscript_arg1 == 0 && v == g_aiscript_arg3) || (g_aiscript_arg1 == 1 && v != g_aiscript_arg3) ||
        (g_aiscript_arg1 == 2 && v < g_aiscript_arg3) || (g_aiscript_arg1 == 3 && g_aiscript_arg3 < v) ||
        (g_aiscript_arg1 == 4 && !(g_aiscript_arg3 < v)) || (g_aiscript_arg1 == 5 && !(v < g_aiscript_arg3))) {
        return 1;
    }
    return 0;
}

/* was func_1507900C */
void aiscript_if_value(void) {
    if (aiscript_test_object_value(0) != 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507903C */
void aiscript_goto_if_value(void) {
    if (aiscript_test_object_value(0) != 0) {
        g_cur_obj->unk218 = aiscript_find_by_kind(0, g_aiscript_arg0);
        g_cur_obj->unk218 -= 1;
    }
}

/* was func_15079090 */
void aiscript_if_self_value(void) {
    if (aiscript_test_object_value(g_cur_obj_index) != 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_150790C4 */
void aiscript_goto_if_self_value(void) {
    if (aiscript_test_object_value(g_cur_obj_index) != 0) {
        g_cur_obj->unk218 = aiscript_find_by_kind(0, g_aiscript_arg0);
        g_cur_obj->unk218 -= 1;
    }
}

/* was func_1507911C */
u8 aiscript_if_below_coord(void) {
    s16 temp_a2;
    s16 phi_a0;
    u8 idx;

    temp_a2 = (g_aiscript_arg1 << 8) | g_aiscript_arg2;
    idx =  g_aiscript_arg3 & 1;
    if (idx != 0) {
        idx = g_cur_obj_index;
    }
    phi_a0 = g_objects[idx].y_position;
    if ((g_aiscript_arg3 & 2) != 0) {
        phi_a0 = g_objects[idx].x_position;
    }
    if (phi_a0 < temp_a2) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_150791F0 */
void aiscript_set_field1c9(void) {
    if ((s32) g_cur_obj->unk2C9 < (s32) g_aiscript_arg0) {
        g_cur_obj->unk1C9 = (u8)0xFFU;
    } else {
        g_cur_obj->unk1C9 = g_aiscript_arg0;
    }
}

// ???
/* was func_15079228 */
void aiscript_send_dir_message(void) {
    s16 *temp_v0 = ((s16 (*)[26])g_level_zones)[g_cur_obj->unk251];
    f32 px = temp_v0[0];
    f32 pz = temp_v0[2];
    s32 temp_v0_2 = math_atan2_u16(g_cur_obj->x_position - px, pz - g_cur_obj->z_position, 0);
    s32 var_a2 = temp_v0_2 & 0xFFFF;

    if (temp_v0_2 == 0) {
        var_a2 = 1;
    }
    obj_send_hit(g_cur_obj, g_aiscript_arg0, var_a2, -1);
    g_cur_obj->unk218--;
    g_cur_obj->unk21C = 1;
}

/* was func_150792E0 */
void aiscript_set_script_kind(void) {
    g_cur_obj->unk232 = g_aiscript_arg0;
}

/* was func_150792FC */
void aiscript_set_field2f8_low(void) {
    g_cur_obj->unk2F8 &= 0xFFF8;
    g_cur_obj->unk2F8 |= g_aiscript_arg0;
}

/* was func_15079334 */
void aiscript_send_script_to_seen(void) {
    struct127 *tmp;

    if (g_cur_obj->unkA8 != 0) {
        tmp = &g_objects[g_cur_obj->unkA8 & 0x7F];
        tmp->unk218 = 0;
        tmp->unk232 = g_aiscript_arg0;
    }
}

/* was func_15079390 */
void aiscript_send_event(void) {
    u16 tmp0 = g_aiscript_arg0;
    u8 tmp1 = g_aiscript_arg1;
    u8 tmp2 = g_aiscript_arg2;
    char_fx_send_event(g_cur_obj, tmp0, tmp1, tmp2);
}

/* was func_150793D8 */
void aiscript_random_point_near_player(void) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
    } sp;
    s16 sp24;
    s16 sp22;
    s16 var_t0;
    s16 var_t0_2;
    s16 var_v1;
    s16 var_v1_2;
    s32 temp_f10;
    s32 temp_f6;

    temp_f6 = (s32) g_objects->x_position;
    temp_f10 = (s32) g_objects->z_position;
    var_v1 = (s16) temp_f6;
    var_t0 = (s16) temp_f10;
    if (((s16) temp_f6 < -0x49C) || ((s16) temp_f6 >= 0x49D) || ((s16) temp_f10 < -0x49C) || ((s16) temp_f10 >= 0x49D)) {
        var_v1 = 0;
        var_t0 = 0;
    }
    sp24 = var_v1;
    sp22 = var_t0;
    vec_from_yaw_pitch(random_int() & 0xFFFF, 550.0f, 0.0f, &sp.u34, &sp.u30, &sp.u2C);
    var_v1_2 = (s16) (s32) ((f32) sp24 + sp.u34);
    var_t0_2 = (s16) (s32) ((f32) sp22 + sp.u30);
    if (var_v1_2 < -0x4B0) {
        var_v1_2 = -0x4B0;
    }
    if (var_v1_2 >= 0x4B1) {
        var_v1_2 = 0x4B0;
    }
    if (var_t0_2 < -0x4B0) {
        var_t0_2 = -0x4B0;
    }
    if (var_t0_2 >= 0x4B1) {
        var_t0_2 = 0x4B0;
    }
    (*(s16 *)((u8 *)((g_path_points[g_cur_obj->unk13F] + (g_aiscript_arg0 * 8))) + 8)) = var_v1_2;
    (*(s16 *)((u8 *)((g_path_points[g_cur_obj->unk13F] + (g_aiscript_arg0 * 8))) + 0xC)) = var_t0_2;
}
/* was func_15079570 */
void aiscript_aim_jump_at_target(void) {
    f32 dist;
    f32 time;

    dist = obj_dist_xz(g_cur_obj, &g_objects[g_cur_obj->unk222]);
    g_cur_obj->unk44 = g_cur_obj->xz_velocity;
    time = 2.0f * (dist / g_cur_obj->unk44);
    g_cur_obj->y_velocity = g_cur_obj->gravity * time * 0.5f;
    g_cur_obj->y_velocity += 2.0f * ((g_objects[g_cur_obj->unk222].y_position - g_cur_obj->y_position) / time);
}

/* was func_1507965C */
void aiscript_send_script_to_uid(void) {
    s32 idx;
    struct127 *temp_v1;

    idx = obj_slot_by_setup_id(g_aiscript_arg0);
    if (idx != -1) {
        temp_v1 = &g_objects[idx];
        temp_v1->unk232 = g_aiscript_arg1;
        temp_v1->unk218 = 0;
        temp_v1->unk23A = 0;
    }
}

/* was func_150796CC */
void aiscript_uid_immune_or_if_stunned(void) {
    s32 idx = obj_slot_by_setup_id(g_aiscript_arg0);
    if (g_aiscript_arg2 != 0) {
        if (idx != -1) {
            g_objects_immune[idx * sizeof(struct127)] = g_aiscript_arg1;
        }
    } else if ((idx != -1) && (g_objects_stunned[idx * sizeof(struct127)] != 0)) {
        aiscript_branch(g_aiscript_arg1);
    }
}

/* was func_15079790 */
void aiscript_respawn_near_path(void) {
    s16 sp1E;
    s16 temp_t0;

    if (g_aiscript_arg2 != 0) {
        g_cur_obj->id = 0xFF;
    } else {
        g_cur_obj->id = 0x3A;
        sp1E = (random_int() % 500U) - 250;
        temp_t0 = (random_int() % 500U) - 250;
        g_cur_obj->x_position = ((s16 *)g_path_points[g_cur_obj->unk13F])[0] + sp1E;
        g_cur_obj->z_position = ((s16 *)g_path_points[g_cur_obj->unk13F])[2] + temp_t0;
    }
}

/* was func_15079880 */
void aiscript_move_at_player_speed(void) {
    s32 tmp = g_objects_xz_velocity[0] + (s8)g_aiscript_arg2;

    if (tmp < g_aiscript_arg1) {
        tmp = g_aiscript_arg1;
    } else if (tmp >= 251) {
        tmp = 250;
    }
    g_aiscript_arg2 = tmp;
    aiscript_move_setup();
}

/* was func_150798F8 */
void aiscript_if_current_point_dist(void) {
    g_aiscript_arg1 = g_cur_obj->unk21E;
    aiscript_if_point_dist();
}

/* was func_15079928 */
void aiscript_start_anim(void) {
    s32 phi_a3;

    phi_a3 = ((g_aiscript_arg1 << 0x10) + g_aiscript_arg2) & 0xFFFF;
    if (phi_a3 == 0) {
        phi_a3 = 0xFFFF;
    }
    face_anim_start(g_cur_obj, g_aiscript_arg0, g_aiscript_arg3, phi_a3, 0);
}

/* was func_15079988 */
void aiscript_set_anim_field70(void) {
    face_set_default_anim(g_cur_obj, g_aiscript_arg0);
}

/* was func_150799B4 */
void aiscript_play_sound_random(void) {
    s32 temp_a0 = (g_aiscript_arg0 << 8) + g_aiscript_arg1;
    if (g_aiscript_arg2 != 0) {
        temp_a0 += random_int() % (u32) g_aiscript_arg2;
    }
    obj_sfx_play(temp_a0, g_cur_obj);
}

/* was func_15079A28 */
void aiscript_set_field252(void) {
    g_cur_obj->unk252 = g_aiscript_arg0;
    g_cur_obj->unk253 = g_aiscript_arg1;
}

/* was func_15079A58 */
void aiscript_set_path_param(void) {
    g_setup_respawn_timers[g_cur_obj->unk13F] = (g_aiscript_arg0 << 8) + g_aiscript_arg1;
}

// path_point_angle: angle (u16, math_atan2_u16) from object arg0 (g_objects) to the current path point of the
// active character (g_path_points[g_cur_obj +0x13F]: x at +0, z at +4). P179: was `void` and dropped the return; its
// asm caller aiscript_object_var_cmd stores / subtracts the two results (`sh v0` / `subu` after the jal).
/* was func_15079A98 */
u16 aiscript_path_point_angle(s32 arg0) {
    s16 *temp_v0 = (s16 *)g_path_points[g_cur_obj->unk13F];
    struct127 *temp_v1 = &g_objects[arg0];

    return math_atan2_u16(temp_v0[0] - temp_v1->x_position, temp_v1->z_position - temp_v0[2], 0);
}

// requires jump table
/* obj_slot_by_setup_id (s32 (u8), game_eu_AF2A0) is used undeclared in this file, like its other callers here */
int aiscript_find_by_kind(s32, s32);
u16 aiscript_path_point_angle(s32 arg0);

// object_var_cmd: P210: script command on object `idx` (g_aiscript_arg1 0 / 1: the current one g_cur_obj_index, else
// obj_slot_by_setup_id(g_aiscript_arg1 - 2); -1 = none). g_aiscript_arg2 selects: 1..3 counter unk2E4 / unk2E8 / unk2EC, updated by
// g_aiscript_arg3 (0 = g_aiscript_arg0, 1 -1, 2 + frame time g_frame_ticks, 3 +1, 4 - frame time, 5 - g_obj_time_step_pct,
// 6 + g_obj_time_step_pct); 4 / 5 start script g_aiscript_arg0 on the object (when it is not running it already); 6 unkC8 =
// g_aiscript_arg0; 7 unkB8 = 0; for the current object: 8 unk221 = g_aiscript_arg0 when the path point angle
// (aiscript_path_point_angle) from object g_cur_obj_index minus the one from object unk222 has bit 15 set, 9 unk244 = g_aiscript_arg3 << 8 | g_aiscript_arg0, 10 unk236 = unk23D + (s8)g_aiscript_arg0, 11 unk22A = g_aiscript_arg0.
// Other g_aiscript_arg2 values: the asm then updates a counter through an unset stack pointer; here nothing happens.
/* was func_15079B30 */
void aiscript_object_var_cmd(void) {
    s32 idx;
    s32 *var;
    struct127 *saved;
    u8 savedNum;
    u16 a;

    if (g_aiscript_arg1 == 0 || g_aiscript_arg1 == 1) {
        idx = g_cur_obj_index;
    } else {
        idx = obj_slot_by_setup_id(g_aiscript_arg1 - 2);
        if (idx == -1) {
            return;
        }
    }
    switch (g_aiscript_arg2) {
        case 1:
            var = &g_objects[idx].unk2E4;
            break;
        case 2:
            var = &g_objects[idx].unk2E8;
            break;
        case 3:
            var = &g_objects[idx].unk2EC;
            break;
        case 4:
        case 5:
            saved = g_cur_obj;
            savedNum = g_cur_obj_index;
            g_cur_obj = &g_objects[idx];
            g_cur_obj_index = idx;
            if (g_aiscript_arg0 != g_cur_obj->unk232) {
                g_cur_obj->unk232 = g_aiscript_arg0;
                g_cur_obj->unk218 = (struct216 *)aiscript_find_by_kind(0, g_cur_obj->unk232);
                g_cur_obj->unk21C = 0;
            }
            g_cur_obj_index = savedNum;
            g_cur_obj = saved;
            return;
        case 6:
            g_objects[idx].unkC8 = g_aiscript_arg0;
            return;
        case 7:
            g_objects[idx].unkB8 = 0.0f;
            return;
        case 8:
            a = aiscript_path_point_angle(g_cur_obj->unk222);
            if ((aiscript_path_point_angle(g_cur_obj_index) - a) & 0x8000) {
                g_cur_obj->unk221 = g_aiscript_arg0;
            }
            return;
        case 9:
            g_cur_obj->unk244 = (g_aiscript_arg3 << 8) | g_aiscript_arg0;
            return;
        case 10:
            g_cur_obj->unk236 = g_cur_obj->unk23D + (s8)g_aiscript_arg0;
            return;
        case 11:
            g_cur_obj->unk22A = g_aiscript_arg0;
            return;
        default:
            return;
    }
    switch (g_aiscript_arg3) {
        case 0:
            *var = g_aiscript_arg0;
            break;
        case 1:
            *var -= 1;
            break;
        case 2:
            *var += g_frame_ticks;
            break;
        case 3:
            *var += 1;
            break;
        case 4:
            *var -= g_frame_ticks;
            break;
        case 5:
            *var -= g_obj_time_step_pct;
            break;
        case 6:
            *var += g_obj_time_step_pct;
            break;
    }
}

/* was func_15079F24 */
void aiscript_set_field48(void) {
    g_cur_obj->unk48 = g_aiscript_values[g_aiscript_arg0];
}

/* was func_15079F50 */
void aiscript_set_field23b(void) {
    g_cur_obj->unk23B = g_aiscript_arg0;
}

/* was func_15079F6C */
void aiscript_set_field224(void) {
    u8 temp_v0 = g_aiscript_arg0; s32 temp_v1 = g_aiscript_arg1 & 0xFF;

    g_cur_obj->unk224 = (temp_v0 << 8) | temp_v1;
    g_cur_obj->unk22B = g_aiscript_arg2;
    g_cur_obj->unk226 = g_aiscript_arg3;
}

int aiscript_find_by_kind(s32, s32);
extern f32 g_aiscript_follow_speed_scale; /* 0.7; was D_8009A5A4 */

// follow_player_speed: P210: script command: when player 1 (g_objects[0]) rides nothing (unk65 0) or is slower
// than 5, jumps the current object's script to g_aiscript_arg1 (unk232, script pointer aiscript_find_by_kind - one entry);
// otherwise copies the player's controller heading (unk31C +0x4C) into unk78 and starts aiscript_mode3 with speed
// parameter g_aiscript_arg2 = player speed (times 0.7 unless the player is chased), g_aiscript_arg3 + 1 and g_aiscript_arg0 = 8
// below 17; sets flag 0x40 in unkF4.
/* was func_15079FBC */
void aiscript_follow_player_speed(void) {
    struct127 *player = &g_objects[0];
    s16 speed;

    if (player->unk65 == 0 || player->unk44 < 5.0f) {
        g_cur_obj->unk232 = g_aiscript_arg1;
        g_cur_obj->unk218 = (struct216 *)aiscript_find_by_kind(0, g_cur_obj->unk232);
        g_cur_obj->unk218--;
        return;
    }
    g_cur_obj->unk78 = player->unk31C->unk4C;
    if (player->unk31C->chased != 0) {
        speed = player->unk44;
    } else {
        speed = player->unk44 * g_aiscript_follow_speed_scale;
    }
    if (speed < 17) {
        g_aiscript_arg3++;
        g_aiscript_arg0 = 8;
    }
    g_aiscript_arg2 = speed;
    aiscript_mode3();
    g_cur_obj->unkF4 |= 0x40;
}
// NON-MATCHING: JUSTREG
// void aiscript_follow_player_speed(void) {
//     s16 phi_v1;
//
//     if ((g_objects->unk65 == 0) || (g_objects->unk44 < 5.0f)) {
//         g_cur_obj->unk232 = g_aiscript_arg1;
//         g_cur_obj->unk218 = aiscript_find_by_kind(0, g_cur_obj->unk232, g_cur_obj);
//         g_cur_obj->unk218 -= 1;
//         return;
//     }
//
//     g_cur_obj->unk78 = g_objects->unk31C->unk4C;
//
//     if (g_objects->unk31C->unk4A) {
//         phi_v1 = g_objects->unk44;
//     } else {
//         phi_v1 = g_objects->unk44 * D_8009A1E4;
//     }
//     if (phi_v1 < 17) {
//         g_aiscript_arg3 += 1;
//         g_aiscript_arg0 = 8;
//     }
//     g_aiscript_arg2 = phi_v1;
//     aiscript_mode3();
//     g_cur_obj->unkF4 |= 0x40;
// }

// g_path_points!
/* was func_1507A100 */
void aiscript_set_path_point_coord(void) {
    s32 temp_v0 = ((s8)g_aiscript_arg2 << 8) | g_aiscript_arg3;

    ((s16 (*)[4])g_path_points[g_cur_obj->unk13F])[g_aiscript_arg0][g_aiscript_arg1 + 4] = temp_v0;
}

/* was func_1507A164 */
s32 aiscript_speed_from_player(void) {
    s32 tmp = g_objects_xz_velocity[0] + (s8)g_aiscript_arg2;

    if (tmp < g_aiscript_arg1) {
        tmp = g_aiscript_arg1;
    } else if (tmp > g_aiscript_arg0) {
        tmp = g_aiscript_arg0;
    }
    g_cur_obj->unk44 = tmp;
    if (g_cur_obj->unk44 == 1.0f) {
        g_cur_obj->unk44 = 0.5f;
    }
}

/* was func_1507A210 */
void aiscript_wait(void) {
    g_cur_obj->unk223 = 0;
    g_cur_obj->unk21C = g_aiscript_arg0 * 0x64;
    g_cur_obj->unk22C &= 0xFD;
    aiscript_apply_move_flags();
}

/* was func_1507A270 */
void aiscript_set_flag_entry_set(void) {
    breakable_request_flag_entry(g_cur_obj, g_aiscript_arg0, (s8)g_aiscript_arg1);
}

/* was func_1507A2A4 */
void aiscript_chase_random_arg3(void) {
    g_aiscript_arg3 = (random_int() % (u32) g_aiscript_arg1) + g_aiscript_arg3;
    aiscript_chase_target();
}

/* was func_1507A2F8 */
void aiscript_target_random_by_id(void) {
    s32 i;
    u32 used;
    u8 sp1C[25];

    used = 0;
    for (i = 0; i < 25; i++) {
        if ((g_objects[i].interaction_state != 0) && (g_objects[i].id == g_aiscript_arg0)) {
            sp1C[used] = i;
            used++;
        }
    }
    if (used != 0) {
        i = random_int();
        g_cur_obj->unkA8 = g_cur_obj->unk222;
        g_cur_obj->unk222 = sp1C[i % used];
    }
}

/* was func_1507A3B4 */
void aiscript_target_restore(void) {
    g_cur_obj->unk222 = g_cur_obj->unkA8;
}

/* was func_1507A3CC */
void aiscript_set_field229(void) {
    g_cur_obj->unk229 = g_aiscript_arg0;
}

//  what is up with these??
/* was func_1507A3E8 */
s32 aiscript_args_word(void) {
    return ((g_aiscript_arg0 & 0xFF) << 24) | ((g_aiscript_arg1 & 0xFF) << 16) | ((g_aiscript_arg2 & 0xFF) << 8) | (g_aiscript_arg3 & 0xFF);
}

/* was func_1507A428 */
void aiscript_set_flags_94_inv(void) {
    s32 temp_v0 = ((g_aiscript_arg0 & 0xFF) << 24) | ((g_aiscript_arg1 & 0xFF) << 16) | ((g_aiscript_arg2 & 0xFF) << 8) | (g_aiscript_arg3 & 0xFF);

    g_cur_obj->unk94 = ~(temp_v0 | 1);
}
/* was func_1507A47C */
void aiscript_clear_flags_94(void) {
    s32 temp_v0 = ((g_aiscript_arg0 & 0xFF) << 24) | ((g_aiscript_arg1 & 0xFF) << 16) | ((g_aiscript_arg2 & 0xFF) << 8) | (g_aiscript_arg3 & 0xFF);

    g_cur_obj->unk94 &= ~temp_v0;
}
/* was func_1507A4D4 */
void aiscript_set_flags_94(void) {
    s32 temp_v0 = ((g_aiscript_arg0 & 0xFF) << 24) | ((g_aiscript_arg1 & 0xFF) << 16) | ((g_aiscript_arg2 & 0xFF) << 8) | (g_aiscript_arg3 & 0xFF);

    g_cur_obj->unk94 |= temp_v0;
}

/* was func_1507A528 */
void aiscript_set_path_step(void) {
    s32 count;
    s32 pos;

    if (g_aiscript_arg0 == 0) {
        g_cur_obj->unk221 = g_aiscript_arg1;
    } else if (g_aiscript_arg0 == 1) {
        g_cur_obj->unk221 = -g_cur_obj->unk221;
    } else if (g_aiscript_arg0 == 2) {
        if (g_aiscript_arg2 != 0) {
            count = g_aiscript_arg2;
        } else {
            count = g_path_point_counts[g_cur_obj->unk13F] - 1;
        }
        g_cur_obj->unk221 = -g_cur_obj->unk221;
        pos = g_cur_obj->unk21E + g_cur_obj->unk221;
        if (g_cur_obj->unk221 > 0) {
            pos += g_aiscript_arg3;
        } else {
            pos -= g_aiscript_arg3;
        }
        if (pos >= count) {
            pos -= count;
        } else if (pos < 0) {
            pos += count;
        }
        g_cur_obj->unk21E = pos;
    }
}

/* was func_1507A620 */
void aiscript_if_target_angle(void) {
    u8 idx;
    u16 tmp;

    idx = g_cur_obj->unk222;
    if (g_aiscript_arg1 != 0) {
        tmp = g_cur_obj->unk78 >> 8;
    } else {
        tmp = (g_cur_obj->unk7A - math_atan2_u16(g_objects[idx].x_position - g_cur_obj->x_position, g_cur_obj->z_position - g_objects[idx].z_position, 0)) >> 8;
    }
    if ((u8)(tmp - g_aiscript_arg2) < (u8)(g_aiscript_arg3 - g_aiscript_arg2)) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507A6FC */
s32 aiscript_pad_buttons(s32 arg0) {
    // really??
    u32 tmp0 = (3 * arg0) & 0xFFFFFFFFFFFFFFFF;
    u32 tmp1 = tmp0 & 0xFFFFFFFFFFFFFFFF;
    return g_pad_states[tmp1 & 0xFFFFFFFFFFFFFFFF];
}

/* was func_1507A71C */
void aiscript_if_buttons_held(void) {
    u16 tmp0 = aiscript_pad_buttons(g_aiscript_arg0);
    u16 tmp1 = ((g_aiscript_arg1 << 8) | g_aiscript_arg2);

    if ((tmp0 & tmp1) == tmp1) {
        aiscript_branch(g_aiscript_arg3);
    }
}

/* was func_1507A774 */
void aiscript_if_level(void) {
    u16 temp_v0 = (g_aiscript_arg1 << 8) | g_aiscript_arg2;
    if (g_level_id == temp_v0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507A7C0 */
void aiscript_set_disable_run(void) {
    g_cur_obj->disable_run = (u8) g_aiscript_arg0;
}

/* was func_1507A7DC */
void aiscript_remove_spawned(void) {
    obj_setup_undo(g_cur_obj, g_aiscript_arg0);
}

/* was func_1507A808 */
void aiscript_mask_flags_22c(void) {
    g_cur_obj->unk22C = (g_cur_obj->unk22C & g_aiscript_arg0) | g_aiscript_arg1;
}

/* was func_1507A838 */
void aiscript_if_health(void) {
    if (g_cur_obj->health == g_aiscript_arg1) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507A878 */
void aiscript_call_15b470(void) {
    camera_shake_start(0, g_aiscript_arg0, g_aiscript_arg1);
}

/* was func_1507A8A8 */
void aiscript_if_mp_or_cc335(void) {
    if ((g_objects_parent_slot != 0) || (g_mp_mode_active != 0)) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507A8EC */
void aiscript_if_target_id(void) {
    if (g_aiscript_arg1 == g_objects_id[g_cur_obj->unk222 * sizeof(struct127)]) {
        g_aiscript_arg2 ^= 1;
    }
    if (g_aiscript_arg2 != 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507A984 */
void aiscript_attach_to_id(void) {
    s32 temp_v0;

    if (g_aiscript_arg0 != 0) {
        temp_v0 = obj_find_by_setup_id(g_aiscript_arg0);
        if (temp_v0 != 0) {
            if (g_aiscript_arg2 == 0) {
                g_cur_obj->unk101 |= 4;
            }
            if (g_aiscript_arg3 != 0) {
                g_cur_obj->unk101 |= 0x40;
            }
            g_cur_obj->unk65 = ((s32) (temp_v0 - (s32)&g_objects) / 0x32C) + 1;
            g_cur_obj->unk5C = g_aiscript_arg1;
        }
    } else {
        g_cur_obj->unk65 = 0;
    }
}

// requires jump table
extern f32 g_aiscript_rad_to_binang; /* 65536 / (2 pi); was D_8009A5CC */
/* IDO's f32 -> u32 conversion (cvt.w.s, then 2^31 offset): -1 for NaN, values <= -1 and >= 2^32 */
#define P210_F2U(v) (((v) > -1.0f && (v) < 4294967296.0f) ? (u32)(v) : 0xFFFFFFFF)

// set_heading_cmd: P210: script command: sets the current object's target heading unk78 (or its heading unk76)
// from the 16-bit value g_aiscript_arg0 << 8 | g_aiscript_arg1 by mode g_aiscript_arg2: 0 heading + value, 1 heading - value,
// 2 value, 3 turn now (unk76 = unk7A = unk78), 4 direction from path point g_aiscript_arg0 to point g_aiscript_arg1
// (g_path_points[unk13F]) + g_aiscript_arg3 << 8 + 0x4000, 5 random (random_int), 6 keep the heading, 7 unk76 = object
// unk222's facing + value, 8 unk76 = own facing unk7A.
/* was func_1507AA48 */
void aiscript_set_heading(void) {
    u16 v = (g_aiscript_arg0 << 8) | g_aiscript_arg1;

    switch (g_aiscript_arg2) {
        case 0:
            g_cur_obj->unk78 = g_cur_obj->unk76 + v;
            break;
        case 1:
            g_cur_obj->unk78 = g_cur_obj->unk76 - v;
            break;
        case 2:
            g_cur_obj->unk78 = v;
            break;
        case 3:
            g_cur_obj->unk76 = g_cur_obj->unk78;
            g_cur_obj->unk7A = g_cur_obj->unk78;
            break;
        case 4: {
            u8 *path = (u8 *)g_path_points[g_cur_obj->unk13F];
            s16 *from = (s16 *)(path + g_aiscript_arg0 * 8 + 8);
            s16 *to = (s16 *)(path + g_aiscript_arg1 * 8 + 8);
            f32 ang = math_atan2f(to[0] - from[0], to[2] - from[2]);

            g_cur_obj->unk78 = P210_F2U(ang * g_aiscript_rad_to_binang) + (g_aiscript_arg3 << 8) + 0x4000;
            break;
        }
        case 5:
            g_cur_obj->unk78 = random_int();
            break;
        case 6:
            g_cur_obj->unk78 = g_cur_obj->unk76;
            break;
        case 7:
            g_cur_obj->unk76 = g_objects[g_cur_obj->unk222].unk7A + v;
            break;
        case 8:
            g_cur_obj->unk76 = g_cur_obj->unk7A;
            break;
    }
}

/* was func_1507ACB0 */
void aiscript_set_path_range(void) {
    g_cur_obj->unk220 = g_aiscript_arg0;
    g_cur_obj->unk21F = g_aiscript_arg1;
}

/* was func_1507ACE0 */
void aiscript_set_turn_rate_exact(void) {
    g_cur_obj->unk1E5 = g_aiscript_arg0;
    g_cur_obj->unk1E6 = g_aiscript_arg0;
    g_cur_obj->unk1E7 = g_aiscript_arg1;
    g_cur_obj->unk1E8 = g_aiscript_arg1;
}

/* was func_1507AD30 */
void aiscript_set_field255(void) {
    g_cur_obj->unk255 = g_aiscript_arg0;
    g_cur_obj->unk256 = g_aiscript_arg1;
}

/* was func_1507AD60 */
void aiscript_set_field1e4(void) {
    g_cur_obj->unk1E4 = g_aiscript_arg0;
}

/* was func_1507AD7C */
void aiscript_set_flags_f4(void) {
    g_cur_obj->unkF4 |= aiscript_args_word();
}

/* was func_1507ADAC */
void aiscript_clear_flags_f4(void) {
    g_cur_obj->unkF4 &= ~aiscript_args_word();
}

/* was func_1507ADE0 */
void aiscript_turn_in_time(void) {
    s32 res;
    s32 temp_lo;
    s32 b = g_cur_obj->unk7A;
    s32 a = g_cur_obj->unk78;

    res = a - b;
    if (res < 0) {
        res = -res;
    }
    if (res >= 32769) {
        res = res + 0xFFFF0000;
    }
    if (res < 0) {
        res = -res;
    }
    temp_lo = res / (s32)g_aiscript_arg0;
    g_cur_obj->unk1E6 = temp_lo >> 8;
    g_cur_obj->unk1E8 = temp_lo & 0xFF;
}

/* was func_1507AE78 */
void aiscript_set_field229_b(void) {
    g_cur_obj->unk229 = g_aiscript_arg0;
}

/* was func_1507AE94 */
void aiscript_set_extent_d2(void) {
    g_cur_obj->unkD2 = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
    g_cur_obj->unkD4 = (g_aiscript_arg2 << 8) | g_aiscript_arg3;
    g_cur_obj->unkD2 *= g_cur_obj->xz_scale;
    g_cur_obj->unkD4 *= g_cur_obj->y_scale;
}

/* was func_1507AF3C */
void aiscript_set_extent_d6(void) {
    g_cur_obj->unkD6 = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
    g_cur_obj->unkD6 *= g_cur_obj->y_scale;
}

/* was func_1507AF98 */
void aiscript_set_extent_d8(void) {
    g_cur_obj->unkD8 = (g_aiscript_arg0 << 8) | g_aiscript_arg1;
    g_cur_obj->unkDA = (g_aiscript_arg2 << 8) | g_aiscript_arg3;
    g_cur_obj->unkD8 *= g_cur_obj->xz_scale;
    g_cur_obj->unkDA *= g_cur_obj->xz_scale;
}

/* was func_1507B040 */
void aiscript_heading_from_facing(void) {
    g_cur_obj->unk76 = g_cur_obj->unk7A;
}

/* was func_1507B058 */
void aiscript_rider_cmd(void) {
    struct127 *sp24 = g_cur_obj;
    s32 sp20 = g_cur_obj_index;

    g_cur_obj = obj_find_child_nth(g_cur_obj, 0);
    g_cur_obj_index = ((s32)g_cur_obj - (s32)&g_objects) / 0x32C;

    if (g_cur_obj != 0) {
        switch (g_aiscript_arg0) {
            case 0:
                obj_fade_command(g_cur_obj, 1, g_aiscript_arg1, 0, 0);
                break;
            case 1:
                g_cur_obj->unk232 = g_aiscript_arg1;
            case 2:
                g_cur_obj->unk218 = aiscript_find_by_kind(0, g_aiscript_arg1);
                g_cur_obj->unk21C = 0;
        }
    }
    g_cur_obj_index = sp20;
    g_cur_obj = sp24;
}

/* was func_1507B15C */
void aiscript_set_disable_jump(void) {
    g_cur_obj->disable_jump = g_aiscript_arg0;
}

/* was func_1507B178 */
void aiscript_set_inner_extent(void) {
    s16 tmp  = (g_aiscript_arg1 << 8) | g_aiscript_arg0;
    if (g_aiscript_arg3 == 2) {
        g_cur_obj->unkE8 = (s16) (tmp * g_cur_obj->y_scale);
    } else if (g_aiscript_arg3 == 1) {
        obj_set_inner_extent_height(g_cur_obj, tmp);
    } else {
        obj_set_inner_extent_width(g_cur_obj, tmp);
    }
}

/* was func_1507B234 */
void aiscript_sound_ev_300_1800(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 1) != 0) {
        objev_sound_alt_or_stop(300, 1800);
    }
}

/* was func_1507B280 */
void aiscript_sound_ev_300_3000(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 1) != 0) {
        objev_sound_alt_or_stop(300, 3000);
    }
}

/* was func_1507B2CC */
void aiscript_sound_ev_b_300_1800(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 0) != 0) {
        objev_sound_or_stop(300, 1800);
    }
}

/* was func_1507B318 */
void aiscript_sound_ev_b_300_3000(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 0) != 0) {
        objev_sound_or_stop(300, 0xBB8);
    }
}

/* was func_1507B364 */
void aiscript_sound_ev_700_4000(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 1) != 0) {
        objev_sound_alt_or_stop(0x2BC, 0xFA0);
    }
}

/* was func_1507B3B0 */
void aiscript_sound_ev_b_700_4000(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 0) != 0) {
        objev_sound_or_stop(0x2BC, 0xFA0);
    }
}

/* was func_1507B3FC */
void aiscript_sound_ev_3000_8000(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 1) != 0) {
        objev_sound_alt_or_stop(0xBB8, 0x1F40);
    }
}

/* was func_1507B448 */
void aiscript_sound_ev_190_1300(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 1) != 0) {
        objev_sound_alt_or_stop(0xBE, 0x514);
    }
}

/* was func_1507B494 */
void aiscript_sound_ev_b_190_1300(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 0) != 0) {
        objev_sound_or_stop(0xBE, 0x514);
    }
}

/* was func_1507B4E0 */
void aiscript_sound_ev_100_800(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 1) != 0) {
        objev_sound_alt_or_stop(100, 800);
    }
}

/* was func_1507B52C */
void aiscript_sound_ev_b_100_800(void) {
    g_cur_obj_cmd = aiscript_args_word();
    if (sound_word_resolve(g_cur_obj, &g_cur_obj_cmd, 0) != 0) {
        objev_sound_or_stop(100, 800);
    }
}

/* was func_1507B578 */
void aiscript_set_fieldd0(void) {
    g_cur_obj->unkD0 = g_aiscript_arg0;
    g_cur_obj->unk114 = g_aiscript_arg1;
}

/* was func_1507B5C4 */
void aiscript_if_player_field75(void) {
    if (g_cur_obj->unk31C->unk75 == g_aiscript_arg1) {
        g_aiscript_arg2 ^= 1;
    }
    if (g_aiscript_arg2 != 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507B630 */
void aiscript_player_jump_when_grounded(void) {
    if ((g_cur_obj->disable_run == 0) && (g_cur_obj->unk28 == 0.0f)) {
        if (g_cur_obj->unk31C->unk78 != 0) {
            g_aiscript_arg0 ^= 1;
        }
        if (g_aiscript_arg0 != 0) {
            g_cur_obj->unk31C->unk8C |= 0x4000;
            g_cur_obj->unk31C->unk8F = 0;
        }
    } else {
        g_cur_obj->unk218 -= 1;
    }
    g_cur_obj->unk21C = 100;
}

/* was func_1507B6E0 */
void aiscript_wait_grounded(void) {
    if ((g_cur_obj->disable_run != 0) || (g_cur_obj->unk28 > 5.0f)) {
        g_cur_obj->unk218 -= 1;
        g_cur_obj->unk21C = 0x64;
    }
}

/* was func_1507B734 */
void aiscript_set_player_input(void) {
    u16 tmp = ((g_aiscript_arg0 << 8) | g_aiscript_arg1);
    if (g_aiscript_arg3 != 0) {
        g_cur_obj->unk31C->unk8C = tmp;
        g_cur_obj->unk31C->unk8F = g_aiscript_arg2;
    } else {
        g_cur_obj->unk31C->unk8A = tmp;
        g_cur_obj->unk31C->unk8E = g_aiscript_arg2;
    }
}

/* was func_1507B7BC */
void aiscript_mode17(void) {
    aiscript_move_setup();
    g_cur_obj->unk223 = 17;
}

/* was func_1507B7E8 */
void aiscript_if_target_down(void) {
    struct127 *tmp = &g_objects[g_cur_obj->unk222];
    if ((tmp->stunned != 0) || (tmp->health == 0)) {
        g_aiscript_arg1 ^= 1;
    }
    if (g_aiscript_arg1 != 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507B884 */
u8 aiscript_call_hook(void) {
    s32 tmp0;
    s32 tmp1;
    u8 temp_v0;
    void (*func)(s32);

    temp_v0 = g_aiscript_arg0;
    func = g_objev_action_fns[temp_v0];
    if (func != 0) {
        tmp0 = g_cur_obj;
        tmp1 = g_cur_obj_index;
        func(temp_v0);
        g_cur_obj = tmp0;
        g_cur_obj_index = tmp1;
    }
}

/* was func_1507B8F4 */
void aiscript_if_mp_flag(void) {

    if (g_mp_mode_active != 0) {
        if ((g_aiscript_arg1 != 0) || ((g_cur_obj->unk31C != 0) && (g_cur_obj->unk31C->unk84 != 0))) {
            aiscript_branch(g_aiscript_arg0);
        }
    }
}

/* was func_1507B958 */
void aiscript_set_fieldb0(void) {
    g_cur_obj->unkB0 = g_aiscript_arg0;
}

/* was func_1507B974 */
void aiscript_if_point_tag(void) {
    struct127 *var_v1 = g_cur_obj;

    if (g_cur_obj->unk65 != 0) {
        var_v1 = &g_objects[g_cur_obj->unk65 - 1];
    }
    if (g_aiscript_arg1 == ((u16 (*)[4])g_path_points[var_v1->unk13F])[var_v1->unk21E + g_aiscript_arg3][3]) {
        g_aiscript_arg2 ^= 1;
    }
    if (g_aiscript_arg2 != 0) {
        aiscript_branch(g_aiscript_arg0);
    }
}

/* was func_1507BA48 */
void aiscript_play_sound_random_b(void) {
    u16 tmp = ((g_aiscript_arg2 << 8) | g_aiscript_arg3);
    if (g_aiscript_arg0 != 0) {
        tmp += random_int() % (u32) g_aiscript_arg0;
    }
    obj_sfx_play_alt(tmp, g_cur_obj);
}

/* was func_1507BAD0 */
void aiscript_set_flags_fc(void) {
    g_cur_obj->unkFC = aiscript_args_word();
}

/* was func_1507BAF8 */
void aiscript_set_field2cc(void) {
    g_cur_obj->unk2CC = aiscript_args_word();
}

/* was func_1507BB20 */
void aiscript_nop_e(void) {
}

// scary loops
/* P102 draft (game_A28B0.c is not a port-b file): producer of the script pointer that event_action_object (cases 0x14,
 * 0x35, 0x60) and func_1507B... (game_A28B0.c line ~423) store in object +0x218. */
extern u8 g_aiscript_empty[];          /* empty script; was D_8009A4E0 */
extern u8 g_aiscript_default_list[];          /* default script list, 8-byte entries {script, kind}; was D_80086E28 */

// object_find_script: returns the current object's script of a given kind (type list, then the default list).
/* (int: game_A28B0.c calls it before any prototype, i.e. as implicit int.) The script of kind `kind` for the current object g_cur_obj: its type's list (pointer 0x10 bytes before the
 * type's g_model_anim_banks entry) is searched first; a list without that kind (a NULL script ends it) falls back to the
 * default list g_aiscript_default_list, which must contain it (the asm spins forever otherwise). No type entry / list: the
 * empty script g_aiscript_empty. */
/* was func_1507BB28 */
int aiscript_find_by_kind(s32 unused, s32 kind) {
    u8 *type;
    u8 *list;
    s32 i;

    type = ((u8 **)g_model_anim_banks)[*((u8 *)g_cur_obj + 4)];
    if (type == NULL) {
        return (s32)g_aiscript_empty;
    }
    list = *(u8 **)(type - 0x10);
    if (list == NULL) {
        return (s32)g_aiscript_empty;
    }
    for (i = 0; list[i * 8 + 4] != kind; i++) {
        if (*(u8 **)(list + i * 8) == NULL) {
            for (i = 0; g_aiscript_default_list[i * 8 + 4] != kind; i++) {
                if (*(u8 **)(g_aiscript_default_list + i * 8) == NULL) {
                    for (;;) {
                    }
                }
            }
            return *(s32 *)(g_aiscript_default_list + i * 8);
        }
    }
    return *(s32 *)(list + i * 8);
}
/* was func_1507BC14 */
void aiscript_run(struct127 *arg0) {

    if (arg0->unk21C != 0) {
        if (arg0->unk218 != 0) {
            if (arg0->unk21C != 25500) {
                arg0->unk21C = arg0->unk21C - g_obj_time_step_pct;
            }
            if ((arg0->unk21C >= 50000) || (arg0->unk21C == 0)) {
                arg0->unk21C = 0;
                if ((arg0->unkF4 & 0x400) != 0) {
                    arg0->unk21C = 20000;
                    arg0->unkF4 &= ~0x400;
                    arg0->unkF4 |= 4;
                }
            } else {
                return;
            }
        }
    }

    if (arg0->unk218 == 0) {
        arg0->unk218 = aiscript_find_by_kind(0, arg0->unk232);
        arg0->unk21C = 0;
    }

    while (arg0->unk21C == 0) {
        if (arg0->unk218->unk0 >= 0xF7) {
            arg0->unk218 = (u8 *)(arg0->unk218) + 1;
        } else {
            g_aiscript_arg0 = arg0->unk218->unk1;
            g_aiscript_arg1 = arg0->unk218->unk2;
            g_aiscript_arg2 = arg0->unk218->unk3;
            g_aiscript_arg3 = arg0->unk218->unk4;
            g_aiscript_cmd_fns[arg0->unk218->unk0]();
            arg0->unk218 = (u8 *)(arg0->unk218) + 5;
        }
    }
}
