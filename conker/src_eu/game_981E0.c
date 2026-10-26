#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING
void player_lose_life(s32); /* P59: was implicitly int */
void player_idle_animation(void); /* P60: idle animation, was implicitly int */
s32 footstep_splash(struct127 *, s32); /* P192: C on port-b (returns 0), was implicit */
s32 landing_dust_burst(u8 *); /* P204: C on port-b (P201, returns 0), was implicit */
u8 *object_emitter_spawn(u8 *, s32, u8, s32); /* P230 (port-b P229): returns the emitter, was implicit */
void ground_puff_spawn(struct127 *, u8, s32, u8); /* P295: hand C (void), was implicit */
#endif
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 projectile_fire();   /* still asm; called by objfx_gun_fire */
void face_anim_start(struct127 *, u8, u8, u16, s32);
void objev_play_sound(void);  /* P68 hand C; called by objev_sound_if_above_water */
void *attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s16, u8, f32, u8 *, u8, s32, s16, u8, s32); /* P262: the C definition's exact types (game_eu_1306B0) */
extern u8 D_eu_80099F30[];
extern u8 D_80099F3C[];
void aura_group_spawn(u8 *, u8, s32);        /* P238: port-b hand C (void); called by objfx_f9bb0 */
void obj_point_burst_spawn(u8 *, u8, u8, s32);    /* P238: port-b hand C (void); called by objfx_fa520_0 / objfx_fa520_1 / objfx_fa520_2 */
#endif


#ifdef NON_MATCHING
extern s32 D_8008679C;
extern u8 D_80099DF0;
extern u8 D_800C3A82;

/* was func_1506AD30 */
f32 anim_events_run(struct127 *arg0, f32 arg1, s32 arg2) {
    f32 *var_v1;
    f32 var_f0;
    f32 var_f20;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_a2;
    struct197 *temp_a1;
    u8 *var_v0;
    u8 temp_v1;
    u8 var_a0;

    var_f20 = arg1;
    temp_s0 = arg2 & 0xFF;
    if (arg0->unk5 == 4) {
        return 0.0f;
    }
    D_800D1878 = 0.0f;
    if (var_f20 < arg0->unkB4) {
        arg0->unk138 = 0;
    }
    D_800D1880 = 1;
    temp_v0 = arg0->unk1C4;
    if (temp_v0 != 0) {
        var_v1 = temp_v0 + (arg0->unk138 * 0xC);
        var_f0 = *var_v1;
        if ((var_f0 <= var_f20) && (1 != 0)) {
loop_8:
            if (var_f0 < 900.0f) {
                D_800D1580 = (*(s32 *)((u8 *)var_v1 + 8));
                D_800D1874 = (*(f32 *)&(D_800D1580));
                temp_a1 = arg0->unk2D0;
                var_a2 = (*(s32 *)((u8 *)temp_a1 + 0x28));
                temp_s2 = var_a2;
                if ((D_800C35EA == 0) || (D_800C3A82 != 0)) {
                    var_a0 = (*(u8 *)((u8 *)((arg0->unk1C4 + (arg0->unk138 * 0xC))) + 7));
                    if ((temp_s0 != 0) && (temp_s0 != 0)) {
                        var_v0 = &D_80099DF0;
loop_14:
                        temp_v1 = *var_v0;
                        if (temp_v1 == 0) {
                            var_a0 = 0;
                        }
                        if (var_a0 != temp_v1) {
                            var_v0 += 1;
                            if (temp_s0 != 0) {
                                goto loop_14;
                            }
                        }
                    }
                    if (var_a0 != 0) {
                        (*(s32 (**)())((u8 *)&D_8008679C + (var_a0 * 4)))(var_a0, temp_a1, var_a2, &D_800D1880);
                        var_a2 = (*(s32 *)((u8 *)(arg0->unk2D0) + 0x28));
                    }
                }
                if (temp_s2 != var_a2) {
                    var_f20 = arg0->unk2D0->unk8;
                } else {
                    arg0->unk138 += 1;
                }
            }
            if (arg0->unk1C4 != 0) {
                var_v1 = arg0->unk1C4 + (arg0->unk138 * 0xC);
                var_f0 = *var_v1;
                if ((var_f0 <= var_f20) && (D_800D1880 != 0)) {
                    goto loop_8;
                }
            }
        }
    }
    return D_800D1878;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/anim_events_run.s")
#endif
/* was func_1506AF74 */
void objev_anim_38(void) {
    if ((D_800D154C->unk100 & 8) != 0) {
        D_800D154C->unk100 |= 4;
    }
    D_800D154C->unk100 &= 0xF7;
    obj_start_anim(D_800D154C, 0x38, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

/* was func_1506AFE0 */
void objev_anim_48(void) {
    obj_start_anim(D_800D154C, 0x48, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B020 */
void objev_anim_39(void) {
    D_800D154C->unk1CB = (u8)1;
    obj_start_anim(D_800D154C, 0x39, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B070 */
void objev_nop_1506b070(void) {
}

/* was func_1506B078 */
void objev_anim_d1_by_depth(void) {
    f32 tmp = (D_800D154C->y_position - (D_800D154C->unk118 - 150.0f)) * 0.005f;

    if (tmp < 0.0f) {
        tmp = 1.0f;
    } else {
        tmp +=  1.0f;
    }
    objev_play_anim(0xD1, tmp, 4.0f);
}

// triggered when entering water?
/* was func_1506B100 */
void objev_play_anim(s32 arg0, f32 arg1, f32 arg2) {
    obj_start_anim(D_800D154C, arg0, arg1, arg2, 0.0f, 0.0f, 0);
}

/* was func_1506B14C */
void objev_anim_next(void) {
    obj_start_anim(D_800D154C, D_800D154C->unk84.uh + 1, D_800D154C->animation_speed, 3.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B198 */
void objev_anim_next_flagged(void) {
    obj_start_anim(D_800D154C, D_800D154C->unk84.uh + 1, D_800D154C->animation_speed, 3.0f, 0.0f, 0.0f, 1);
}

/* was func_1506B1E8 */
void objev_anim_3c(void) {
    obj_start_anim(D_800D154C, 0x3C, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B228 */
void objev_anim_54(void) {
    obj_start_anim(D_800D154C, 0x54, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B268 */
void objev_anim_f_allow_run(void) {
    D_800D154C->unk83 = 0;
    D_800D154C->disable_run = 0;
    obj_start_anim(D_800D154C, 0xF, 1.0f, 6.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B2BC */
void objev_release_if_player_link(void) {
    struct127 *temp_v0 = obj_find_child(D_800D154C);
    if ((temp_v0 != 0) && (((((s32)temp_v0 - (s32)&D_800CC2D0) / 0x32C) + 1) == D_800CC2D0[0].unk274)) {
        D_800D154C->unk218 = 0;
        D_800D154C->unk232 = (u8)4;
    }
}

/* was func_1506B328 */
void objev_anim_3e(void) {
    obj_start_anim(D_800D154C, 0x3E, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

/* was func_1506B368 */
void objev_nop_1506b368(void) {
}

/* was func_1506B370 */
void objev_player_lose_life(void) {
    // return index of D_800D154C in structs array
    player_lose_life(((s32)D_800D154C - (s32)D_800CC2D0) / (s32)sizeof(struct127));
}

/* was func_1506B3B0 */
void objev_nop_1506b3b0(void) {
}

#ifdef NON_MATCHING
extern u8 D_80099DFE;
extern u8 D_80099E03;

/* was func_1506B3B8 */
void objev_pick_turn_to_player(void) {
    u8 sp19;
    s16 temp_t0;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a0_2;
    s32 var_a2;
    u8 var_a0;

    sp19 = 0;
    var_a0 = sp19;
    temp_t0 = (D_800D154C->unk7A + (D_800D154C->unk1FD << 8)) - math_atan2_u16(D_800CC2D0->x_position - D_800D154C->x_position, D_800D154C->z_position - D_800CC2D0->z_position, 0);
    temp_v1 = temp_t0 >> 8;
    temp_a3 = temp_v1 & 0xFF;
    var_a2 = temp_v1 & 0xFF;
    if (temp_a3 & 0x80) {
        var_a2 = -temp_a3 & 0xFF;
    }
    if (var_a2 < (s32) D_80099DFC[0][0]) {
        var_a0_2 = 1;
    } else {
        if ((s32) D_80099E03 < var_a2) {
            var_a0 = 5;
        } else if ((s32) D_80099DFE < var_a2) {
            var_a0 = 2;
        }
        if (temp_t0 < 0) {
            var_a0_2 = (var_a0 + 4) & 0xFF;
        } else {
            var_a0_2 = (var_a0 + 3) & 0xFF;
        }
    }
    D_800D154C->unk138 = 0;
    D_800D154C->unk244 = (s16) (*D_80099DFC)[var_a0_2];
    D_800D154C->unk21C = 0x4E20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_pick_turn_to_player.s")
#endif
// NON-MATCHING: 5% there...
// void objev_pick_turn_to_player(void) {
//     u8 sp19;
//     s16 temp_t0;
//     s32 temp_a3;
//     s32 temp_v0;
//     s32 temp_v1;
//     struct127 *temp_a1;
//     struct127 *temp_a1_2;
//     s32 phi_a2;
//     s32 phi_a0;
//     u8 phi_a0_2;
//
//     temp_a1 = D_800D154C;
//     sp19 = 0;
//     temp_a1_2 = D_800D154C;
//     temp_t0 = (temp_a1_2->unk7A + (temp_a1_2->unk1FD << 8)) - math_atan2_u16(D_800CC2D0[0].x_position - temp_a1->x_position, temp_a1->z_position - D_800CC2D0[0].z_position, temp_a1, 0);
//     temp_v1 = (s32) temp_t0 >> 8;
//     temp_a3 = temp_v1 & 0xFF;
//     phi_a2 = temp_v1 & 0xFF;
//     if ((temp_a3 & 0x80) != 0) {
//         phi_a2 = -temp_a3 & 0xFF;
//     }
//     temp_v0 = phi_a2;
//     if (phi_a2 < (s32) D_80099A3C) {
//         phi_a0 = 1;
//     } else {
//         if ((s32) D_80099A43 < temp_v0) {
//             phi_a0_2 = (u8)5U;
//         } else {
//             phi_a0_2 = sp19;
//             if ((s32) D_80099A3E < temp_v0) {
//                 phi_a0_2 = (u8)2U;
//             }
//         }
//         if ((s32) temp_t0 < 0) {
//             phi_a0 = (phi_a0_2 + 4) & 0xFF;
//         } else {
//             phi_a0 = (phi_a0_2 + 3) & 0xFF;
//         }
//     }
//     temp_a1_2->unk138 = (u8)0;
//     D_800D154C->unk244 = (s16) D_80099A3C[phi_a0]; // + 0x800A0000)->unk-65C4;
//     D_800D154C->unk21C = (u16)0x4E20;
// }

/* was func_1506B4EC */
void objev_pick_turn_to_player_wrap(void) {
    objev_pick_turn_to_player();
}

/* was func_1506B50C */
void objev_clear_21c(void) {
    D_800D154C->unk21C = 0;
}

/* was func_1506B520 */
void objev_hurt_or_die(void) {
    s32 tmp;

    if (D_800D154C->health != 0) {
        if ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk78 == 0x25)) {
            tmp = 427;
        } else {
            tmp = 240;
        }
        obj_start_anim(D_800D154C, tmp, 1.5f, 3.0f, 0.0f, 0.0f, 0);
    } else {
        player_hit_reaction(D_800D154C, 1);
    }
}

/* was func_1506B5A4 */
void objev_nop_1506b5a4(void) {
}

/* was func_1506B5AC */
void objev_nop_1506b5ac(void) {
}

/* was func_1506B5B4 */
void objev_set_1cb(void) {
    D_800D154C->unk1CB = (u8)1;
}

/* was func_1506B5CC */
void objev_set_1cb_b(void) {
    D_800D154C->unk1CB = (u8)1;
}

/* was func_1506B5E4 */
void objev_stop_anim(void) {
    obj_fade_command(D_800D154C, 2, 7, 8, 0);
    D_800D154C->animation_speed = 0.0f;
    D_800D154C->unk2D0->unk10 = 0.0f;
}

void objev_sound_alt_300_1800(void);

/* was func_1506B634 */
void objev_pick_random_idle(u8 arg0) {
    u8 i;
    struct126 *p;

    i = (u32)random_int() % arg0;
    p = D_800D154C->unk31C;
    if (p->unk16 != 0) {
        if ((D_800BE9F0 == 0x29) && (i == 7)) {
            i = 0;
        }
        p->unkE = D_80099E7C[i];
    } else {
        p->unkE = D_80099E74[i];
    }
    if (D_800D154C->unk31C->unkE == 0xA7) {
        D_800D1580 = 0xFF020144;
        D_800D154C->unk31C->unkC = (random_int() % 3U) + 2;
        objev_sound_alt_300_1800();
        D_800D154C->xz_velocity *= 0.2f;
    }
}
// NON-MATCHING: miles away
// void objev_pick_random_idle(u8 arg0) {
//     s32 temp_a0;
//     u32 temp_hi;
//     struct126 *temp_a1;
//     s32 phi_a0;
//     s32 phi_a0_2;
//
//     temp_hi = random_int() % (u32) arg0;
//     temp_a0 = temp_hi & 0xFF;
//     temp_a1 = D_800D154C->unk31C;
//     if (temp_a1->unk16 != 0) {
//         phi_a0 = temp_a0;
//         if (D_800BE9F0 == 0x29) {
//             phi_a0 = temp_a0;
//             if ((temp_hi & 0xFF) == 7) {
//                 phi_a0 = 0;
//             }
//         }
//         temp_a1->unkE = (s16) D_80099ABC[phi_a0]; // + 0x800A0000)->unk-6544;
//         phi_a0_2 = phi_a0;
//     } else {
//         temp_a1->unkE = (s16) D_80099AB4[(temp_hi & 0xFF)]; // + 0x800A0000)->unk-654C;
//         phi_a0_2 = temp_a0;
//     }
//     if (D_800D154C->unk31C->unkE == 0xA7) {
//         D_800D1580 = 0xFF020144; // 4278321476
//         D_800D154C->unk31C->unkC = (random_int(phi_a0_2, temp_a1, &D_800D154C) % 3U) + 2;
//         objev_sound_alt_300_1800();
//         D_800D154C->xz_velocity = (f32) (D_800D154C->xz_velocity * D_80099C38);
//     }
// }

/* was func_1506B740 */
void objev_random_idle_or_swim(void) {
    u8 res = random_int() & 0xFF;

    if ((-10000.0f != D_800D154C->unk118) && (D_800D154C->y_position < D_800D154C->unk118)) {
        D_800D154C->unk31C->unkE = 0x2D0;
    } else {
        if (D_800D154C->unk84.uh == 0xA7) {
            if (D_800D154C->unk31C->unkC == 0) {
                res = 0;
            } else {
                D_800D154C->unk31C->unkC--;
                res = 0xFF;
            }
        }
        if (res < 0x80) {
            objev_pick_random_idle(8);
        }
    }
}

/* was func_1506B7F4 */
void objev_allow_run_pick_idle(void) {
    D_800D154C->disable_run = 0;
    D_800D154C->unk83 = 0;
    objev_pick_random_idle(2);
}

/* was func_1506B82C */
void objev_allow_run_idle(void) {
    D_800D154C->disable_run = 0;
    D_800D154C->unk83 = 0;
    player_idle_animation();
}

/* was func_1506B860 */
void objev_anim_b5(void) {
    objev_play_anim(181, 0.6299999952316284f, 5.0f);
}

/* was func_1506B88C */
void objev_anim_b6(void) {
    objev_play_anim(182, 1.0f, 4.0f);
}

/* was func_1506B8B4 */
void objev_reset_state_idle(void) {
    D_800D154C->unk31C->unk78 = (u8)0;
    D_800D154C->disable_run = (u8)0;
    D_800D154C->unk83 = (u8)0;
    player_idle_animation();
}

/* was func_1506B8F4 */
void objev_anim_de(void) {
    objev_play_anim(222, 0.75f, 4.0f);
}

/* was func_1506B91C */
void objev_anim_bf(void) {
    objev_play_anim(191, 1.0f, 4.0f);
}

/* was func_1506B944 */
void objev_anim_c5_allow_run(void) {
    D_800D154C->disable_run = (u8)0;
    D_800D154C->unk83 = (u8)0;
    objev_play_anim(0xC5, 1.0f, 4.0f);
}

/* was func_1506B984 */
void objev_anim_af(void) {
    objev_play_anim(0xAF, 1.0f, 4.0f);
}

/* was func_1506B9AC */
void objev_clear_244(void) {
    D_800D154C->unk244 = (u16)0;
}

/* was func_1506B9C0 */
void objev_finish_and_idle(void) {
    struct126 *temp_a0;

    D_800BE720[D_800C3E78] |= 0x4000;
    temp_a0 = D_800D154C->unk31C;
    if (temp_a0 != 0) {
        temp_a0->unk78 = 0;
        D_800D2E60[D_800D1940 >> 3] |=  (1 << (D_800D1940 & 7));
    }
#ifdef NON_MATCHING
    player_idle_animation(); /* takes no arguments (a0 is left over) */
#else
    player_idle_animation(temp_a0);
#endif
}

/* was func_1506BA4C */
void objev_sound_or_stop(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        actor_sound_stop(D_800D154C);
    } else {
        if (D_800D154C->camera == 0) {
            actor_sound_play(D_800D1580, D_800D154C, 28000, arg0, arg1);
        } else {
            actor_sound_play(D_800D1580, D_800D154C, 24000, 500, 2500);
        }
    }
}

/* was func_1506BAD8 */
void objev_sound_alt_or_stop(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        actor_sound2_stop(D_800D154C);
    } else {
        if (D_800D154C->camera == 0) {
            actor_sound_play2(D_800D1580, D_800D154C, 28000, arg0, arg1);
        } else {
            actor_sound_play2(D_800D1580, D_800D154C, 24000, 500, 2500);
        }
    }
}

/* was func_1506BB64 */
void objev_sound_hi_word_3(s32 arg0, s32 arg1) {
    mp3_voice_play_at_object(D_800D1582, D_800D154C, 28000, arg0, arg1);
}

/* was func_1506BBA8 */
void objev_sound_hi_word(s32 arg0, s32 arg1) {
    if (D_800D154C->camera == 0) {
        actor_sound_play(D_800D1582, D_800D154C, 14000, arg0, arg1);
    } else {
        actor_sound_play(D_800D1582, D_800D154C, 12000, 500, 2500);
    }
}

/* was func_1506BC24 */
void objev_sound_hi_word_alt(s32 arg0, s32 arg1) {
    if (D_800D154C->camera == 0) {
        actor_sound_play2(D_800D1582, D_800D154C, 0x36B0, arg0, arg1);
    } else {
        actor_sound_play2(D_800D1582, D_800D154C, 0x2EE0, 0x1F4, 0x9C4);
    }
}

/* was func_1506BCA0 */
void objev_set_y_velocity(void) {
    D_800D154C->y_velocity = D_800D1580;
}

// ???
s32 game_gu_random(void);
/* was func_1506BCC8 */
void objev_hop(void)
{
  struct127 *p;
  f32 d;
  f32 v;
  if (D_800D154C->interaction_state == 0x16)
  {
    if (D_800D154C->y_position == D_800D154C->unk180)
    {
      D_800D154C->y_velocity = (f32) ((game_gu_random() % 8) + D_800D1580);
      if (0.0f != D_800D154C->xz_velocity)
      {
        D_800D154C->y_velocity = D_800D154C->y_velocity * (D_800D154C->xz_velocity / 40.0f);
      }
      else
      {
        D_800D154C->y_velocity = 0.0f;
      }
    }
  }
  else
  {
    p = D_800D154C;
    d = p->y_position - p->unk180;
    if ((d > (-5.0f)) && (d < 5.0f))
    {
      p->y_velocity = (f32) D_800D1580;
    }
  }
}

/* was func_1506BDE8 */
void objev_jump_if_low(void) {
    if (D_800D154C->y_position < -1750.0f) {
        D_800D154C->y_velocity = (f32) D_800D1580;
    }
}

/* was func_1506BE2C */
void objev_set_gravity(void) {
    D_800D154C->gravity = D_800D1580;
}

/* was func_1506BE54 */
void objev_set_gravity_tenth(void) {
    D_800D154C->gravity = D_800D1580 * 0.1f;
}

/* was func_1506BE84 */
void objev_allow_run(void) {
    D_800D154C->disable_run = 0;
}

/* was func_1506BE98 */
void objev_set_target_speed(void) {
    D_800D154C->target_speed = D_800D1580;
}

/* was func_1506BEC0 */
void objev_set_disable_run(void) {
    D_800D154C->disable_run = D_800D1580;
}

/* was func_1506BEDC */
void objev_set_d0_114(void) {
    D_800D154C->unkD0 = D_800D1580;
    D_800D154C->unk114 = (f32) ((s32) D_800D1580 >> 8);
}

/* was func_1506BF1C */
void objev_sound_if_above_water(void) {
    if (D_800D154C->unk118 <= D_800D154C->y_position) {
        objev_play_sound();
    }
}

#ifdef NON_MATCHING
/* Script command: play a sound for the current object D_800D154C. Command word D_800D1580:
 *   bits 0..10 sound id, 11..13 how to play it, 14..15 actor condition, 16 "defer", 24..31 actor type.
 * Condition 0x4000: only when the object's actor type (its id, or the alias D_8008704C[...] when
 * D_800D1C90[id]->unk4 is set) equals bits 24..31; 0x8000: only when it differs. With bit 16 the command
 * word + 1 is stored in D_800D1C9C (which is cleared otherwise) and nothing plays.
 * Modes (volume 0x7D00, 500 / 2500 = the distance / time arguments of the sound calls):
 *   0x0000 actor_sound_play, 0x1000 actor_sound_play2, 0x3000 actor_sound_play_untracked,
 *   0x3800 actor_sound_play unless sound_voice_get_id(obj->unk8E) already returns that sound,
 *   0x2000 footstep (at most 1 player, D_80082FA0 < 2): the sound comes from the floor surface
 *          (floor_flags_surface_type(obj->unk184) -> sound_surface_footstep, which may also lower the volume; in the air: surface 8;
 *          surface 12 = water while obj->unkCC > -17: sound_pick_variant(0x9C, 2)); the volume scales with the
 *          fall speed (obj->unk31C's first float, else y_velocity), 0.5 .. 1.0 over 0 .. 10 (water) or 30.
 *          Surface 8 plays with actor_sound_play_untracked, the others with actor_sound_play. */
extern s32 D_800D1C9C;
extern u8 *D_8008704C[];
s32 sound_pick_variant(s32, s32);
s32 sound_surface_footstep(s32 surface, u16 *volume, s32 sound);

/* was func_1506BF5C */
void objev_play_sound(void) {
    s32 cmd = D_800D1580;
    struct127 *obj = D_800D154C;
    s32 sound = cmd & 0x7FF;          /* sp4C, played as its low half */
    s32 want = (u32)cmd >> 24;
    s32 type = obj->id;
    s32 mode;
    s32 surface;
    u16 volume;                       /* sp46 */
    f32 speed;
    f32 limit;
    f32 scale;

    if (D_800D1C90[type]->unk4 != 0) {
        type = *D_8008704C[D_800D1C90[type]->unk5];
    }
    D_800D1C9C = 0;
    if ((cmd & 0xC000) == 0x4000) {
        if (type != want) {
            return;
        }
    } else if ((cmd & 0xC000) == 0x8000) {
        if (type == want) {
            return;
        }
    }
    if (cmd & 0x10000) {
        D_800D1C9C = cmd + 1;
        return;
    }

    volume = 0x7D00;
    mode = cmd & 0x3800;
    if (mode == 0x0000) {
        actor_sound_play(sound, obj, volume, 500, 2500);
        return;
    }
    if (mode == 0x1000) {
        actor_sound_play2(sound, obj, 0x7D00, 500, 2500);
        return;
    }
    if (mode == 0x3000) {
        actor_sound_play_untracked(sound, obj, 0x7D00, 500, 2500);
        return;
    }
    if (mode == 0x3800) {
        if (sound_voice_get_id(obj->unk8E) != sound) {
            actor_sound_play(sound, D_800D154C, volume, 500, 2500);
        }
        return;
    }
    if (mode != 0x2000) {
        return;
    }

    /* footstep */
    if (D_80082FA0 >= 2) {
        return;
    }
    surface = floor_flags_surface_type(obj->unk184);
    if (surface == 12 && -17.0f < D_800D154C->unkCC) {
        sound = sound_pick_variant(0x9C, 2);
    } else if (D_800D154C->unk118 != -10000.0f && D_800D154C->unk118 >= D_800D154C->y_position) {
        sound = sound_surface_footstep(8, NULL, sound);
        surface = 8;
    } else {
        sound = sound_surface_footstep(surface, &volume, sound);
    }
    if (sound == 0) {
        return;
    }
    obj = D_800D154C;
    if (obj->unk31C != NULL) {
        speed = *(f32 *)obj->unk31C;
    } else {
        speed = obj->y_velocity;
    }
    limit = (surface == 12) ? 10.0f : 30.0f;
    if (limit < speed) {
        speed = limit;
    }
    scale = 0.5f / limit;
    if (speed < 0.0f) {
        speed = 0.0f;
    }
    volume = (u32)volume * (speed * scale + 0.5f);
    if (surface == 8) {
        actor_sound_play_untracked(sound, obj, volume, 500, 2500);
        return;
    }
    actor_sound_play(sound, obj, volume, 500, 2500);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_play_sound.s")
#endif

#ifdef NON_MATCHING
extern s32 D_800D1C9C;
s32 sound_pick_variant(s32, s32);
/* objev_play_sound: void (P68 NM definition above; prototype at the top of the file) */

/*
 * P80: script command "random jump": while the counter D_800D1C9C is not 0, count it down and pick one of up to four
 * 11-bit targets: the counter's own low 11 bits (after the decrement) and the command word's fields 0..10 / 11..21
 * / 22..32; with n = the highest non-zero field (2 / 3 / 4, else 0) the pick is sound_pick_variant(base, n) - base.
 * A non-zero pick goes into D_800D1580 (with the counter's bits other than 0..10 and 16) and objev_play_sound runs.
 */
/* was func_1506C32C */
void objev_play_random_sound(void) {
    s32 v[4];
    s32 n;
    s32 keep;

    if (D_800D1C9C == 0) {
        return;
    }
    D_800D1C9C--;
    v[0] = D_800D1C9C & 0x7FF;
    v[1] = D_800D1580 & 0x7FF;
    v[2] = (D_800D1580 >> 11) & 0x7FF;
    v[3] = (D_800D1580 >> 22) & 0x7FF;
    if (v[3] != 0) {
        n = 4;
    } else if (v[2] != 0) {
        n = 3;
    } else if (v[1] != 0) {
        n = 2;
    } else {
        n = 0;
    }
    if (n != 0) {
        n = sound_pick_variant(v[0], n) - v[0];
    }
    if (v[n] != 0) {
        keep = D_800D1C9C & 0xFFFEF800;
        D_800D1C9C = keep;
        D_800D1580 = v[n] | keep;
        objev_play_sound();
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_play_random_sound.s")
#endif

/* was func_1506C418 */
void objev_stop_sound_alt(void) {
    actor_sound2_stop(D_800D154C);
}

/* was func_1506C43C */
void objev_stop_sound(void) {
    actor_sound_stop(D_800D154C);
}

// requires jump table
#ifdef NON_MATCHING
struct127 *obj_find_by_state(s32, s32 *);
void *obj_alloc_slot(void);
u8 *light_alloc_light_buf(s32 arg0);
void *light_alloc_lookat_buf(void);
s32 obj_find_visible_target(u8 *, u16 *, s32, s32, s32);
void *allocate_memory(s32, s32, s32, s32);
u8 *move_watch_spawn(u8 *arg0, u8 arg1, s32 arg2);
void obj_effect_run_handler(u8 *, s32, void *);
extern f32 D_800CC704;
extern f32 D_800CC70C;
extern u8 D_80099E84[];
extern s16 D_eu_80099E98[][4];
// P310: copies of the asm's injected rodata (D_8009A050 / D_8009A054); 1-element arrays so IDO keeps them in .rodata (P283)
static const f32 sCamDegToAngle[1] = { 182.04445f };
static const f32 sCamRadToAngle[1] = { 10430.378f };

// camera_object_spawn: P310: takes a camera object slot from the D_800CC2D0 pool (25 records of 0x32C; a recycled
// type-4 slot via obj_find_by_state when 5 or more cameras are live or the free slot is out of range), places it at
// `target`, above the player (+50), or at the player's mode attach point (D_eu_80099E98[mode] = x, y, z, matrix index
// in the player's +0x1D4 matrices; fixed-point when D_800C42B0), lifts it to at least player y + floor_off, starts
// its mode sound (not modes 0 / 1), then sets yaw (degrees -> binary angle - 90 deg), distance / rise / height with the
// flag bits (1 = no aim search, 2 = face the first object, 4 = aim height at it, 8 = random yaw jitter, 0x10 = orbit
// the object the player follows), the style fields and per-mode setup. `snap` (11th arg) allocates a 0x1C0 history
// buffer. Returns the camera object.
/* was func_1506C460 */
s32 camera_object_spawn(f32 yaw, f32 dist, f32 rise, f32 height, u8 alpha, s32 mode, f32 floor_off, f32 smooth, s32 target,
                  s32 flags, s32 snap) {
    u8 *base = (u8 *) D_800CC2D0;
    u8 *player;
    u8 *obj;
    u8 *rec;
    u8 *mtx;
    s16 *attach;
    f32 (*m)[4];
    f32 mf[4][4];
    f32 pos[3];
    f32 orbit[3];
    f32 lift;
    f32 aimY;
    f32 d;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 pitch;
    f32 unused;
    s32 count;
    s32 slot;
    s32 i;
    s32 sound;
    s32 hit;
    s16 angle;
    u16 aim;

    count = 0;
    for (rec = base; rec < (u8 *) &D_800D121C; rec += 0x32C) {
        if (*(s32 *) rec == 4) {
            count++;
        }
    }
    if (count >= 5) {
        obj = (u8 *) obj_find_by_state(4, &slot);
        obj_remove((struct127 *) obj, 0);
    } else {
        obj = (u8 *) obj_alloc_slot();
        if ((u32) ((obj - base) / 0x32C) >= 25 && count > 0) {
            obj = (u8 *) obj_find_by_state(4, &slot);
            obj_remove((struct127 *) obj, 0);
        }
    }
    obj[0x136] = 0xB;
    *(s32 *) obj = 4;
    obj[0x1CA] = 1;
    *(u16 *) (obj + 0x7A) = *(u16 *) ((u8 *) D_800D154C + 0x7A);
    if ((f32 *) target != NULL) {
        *(f32 *) (obj + 0x14) = ((f32 *) target)[0];
        *(f32 *) (obj + 0x18) = ((f32 *) target)[1];
        *(f32 *) (obj + 0x1C) = ((f32 *) target)[2];
    } else {
        player = (u8 *) D_800D154C;
        mtx = *(u8 **) (player + 0x1D4);
        if (mtx == NULL) {
            *(f32 *) (obj + 0x14) = *(f32 *) (player + 0x14);
            *(f32 *) (obj + 0x18) = *(f32 *) ((u8 *) D_800D154C + 0x18) + 50.0f;
            *(f32 *) (obj + 0x1C) = *(f32 *) ((u8 *) D_800D154C + 0x1C);
        } else {
            attach = D_eu_80099E98[mode];
            if (D_800C42B0 != 0) {
                guMtxL2F(mf, (Mtx *) (mtx + attach[3] * 0x40));
                m = mf;
            } else {
                m = (f32 (*)[4]) (mtx + attach[3] * 0x40);
            }
            mtxf_transform_point(m, (f32) attach[0], (f32) attach[1], (f32) attach[2], &pos[0], &pos[1], &pos[2]);
            *(f32 *) (obj + 0x14) = pos[0];
            *(f32 *) (obj + 0x18) = pos[1];
            *(f32 *) (obj + 0x1C) = pos[2];
        }
    }
    if (floor_off != 0.0f) {
        lift = *(f32 *) ((u8 *) D_800D154C + 0x18) + floor_off;
        if (*(f32 *) (obj + 0x18) < lift) {
            *(f32 *) (obj + 0x18) = lift;
        }
    }
    *(s16 *) (obj + 0x160) = 0x6E;
    obj[0x3B] = 0xFF - (obj - base) / 0x32C;
    if (mode == 0 || mode == 1) {
        obj[5] = 2;
        obj[0x103] = 1;
    } else {
        obj[5] = 5;
        for (i = 0; i <= D_80082FA0; i++) {
            *(u8 **) (obj + 0x304 + i * 4) = light_alloc_light_buf(1);
        }
        if (*(s32 *) (obj + 0x300 + i * 4) != 0) {
            obj[0x301] = 1;
        }
        *(void **) (obj + 0x314) = light_alloc_lookat_buf();
        switch (mode) {
        case 2:
            obj[0x103] = 1;
            *(f32 *) (obj + 0xB8) = 260.0f;
            sound = 0x2A;
            break;
        case 18:
            obj[0x103] = 1;
            *(f32 *) (obj + 0xB8) = 260.0f;
            sound = 0x22;
            break;
        case 11:
            sound = 0x6D;
            break;
        case 12:
            sound = 0x6B;
            break;
        case 3:
            sound = 0x39;
            break;
        case 6:
            sound = 0x51;
            break;
        case 15:
            sound = 0x93;
            break;
        case 17:
            sound = 0x39;
            break;
        default:
            sound = 0x50;
            break;
        }
        obj_setup_run((struct127 *) obj, sound, 1.0f, 0);
    }

    angle = (s32) (yaw * sCamDegToAngle[0]) - 0x4000;
    if (D_800BE616 != 0 && !(flags & 1) && mode != 5 && mode != 9 && mode != 10 && mode != 4) {
        aim = math_atan2_u16(dist, rise, 0);
        hit = obj_find_visible_target(obj, &aim, (aim >> 8) & 0xFF, 0xFF, 0x14);
        if (hit != 0xFF) {
            rec = base + (hit & 0xFF) * 0x32C;
            aimY = *(f32 *) (rec + 0x18);
            d = obj_dist_xz(D_800D154C, (struct127 *) rec);
            if (mode == 2 || mode == 18) {
                aimY -= 30.0f;
            }
            angle = aim;
            height = 0.0f;
            rise = (aimY - *(f32 *) ((u8 *) D_800D154C + 0x18)) / (d / dist);
        }
    }
    if (flags & 2) {
        angle = math_atan2_u16(D_800CC704 - *(f32 *) (obj + 0x14), *(f32 *) (obj + 0x1C) - D_800CC70C, 0);
    }
    if (flags & 4) {
        d = obj_dist_xz((struct127 *) obj, D_800CC2D0);
        rise = ((D_800CC2E8[0] + 60.0f) - *(f32 *) (obj + 0x18)) / (d / dist);
    }
    if (flags & 8) {
        angle = angle + (u32) random_int() % 0x1200 - 0x900;
    }
    if (flags & 0x10) {
        rec = base + *((u8 *) D_800D154C + 0x222) * 0x32C;
        vec_from_yaw_pitch(*(u16 *) (rec + 0x76), *(f32 *) (rec + 0x3C) * 4.0f, 0.0f, &orbit[0], &orbit[1], &orbit[2]);
        dx = (*(f32 *) (rec + 0x14) + orbit[0]) - *(f32 *) (obj + 0x14);
        dz = (*(f32 *) (rec + 0x1C) + orbit[1]) - *(f32 *) (obj + 0x1C);
        dy = ((*(f32 *) (rec + 0x18) + 30.0f) + *(f32 *) (rec + 0x20) * 4.0f) - *(f32 *) (obj + 0x18);
        pitch = math_atan2f(dy, sqrtf(dx * dx + dz * dz)) * sCamRadToAngle[0];
        angle = math_atan2_u16(dx, -dz, 0);
        vec_from_yaw_pitch((s32) pitch, dist, 0.0f, &dist, &rise, &unused);
        rise = -rise;
    }
    *(f32 *) (obj + 0x40) = (f32) (s16) (angle + 0x4000) * 0.0054931640625f;
    *(s16 *) (obj + 0x7A) = angle;
    *(s16 *) (obj + 0x76) = angle;
    *(f32 *) (obj + 0x24) = height;
    *(f32 *) (obj + 0x20) = rise;
    *(f32 *) (obj + 0x3C) = dist;
    obj[0x81] = 0;
    obj[0x7F] = 0;
    obj[0x80] = 0xFF;
    obj[0x83] = alpha;
    if (flags & 0x20) {
        obj[0x80] = obj[0x126] = *((u8 *) D_800D154C + 0x222);
    }
    obj[0x82] = 0x26;
    if (snap == 0) {
        obj[0xD0] = D_80099E84[mode] + 1;
    }
    *(f32 *) (obj + 0x28) = 100.0f;
    *(f32 *) (obj + 0x114) = 255.0f;
    *(s16 *) (obj + 0xE4) = 5;
    *(s16 *) (obj + 0xE6) = 5;
    *(f32 *) (obj + 0xEC) = 1.0f;
    *(f32 *) (obj + 0xF0) = 1.0f;
    *(f32 *) (obj + 0xDC) = 1.0f;
    *(f32 *) (obj + 0xE0) = 1.0f;
    obj[0x124] = D_800C3E78 + 1;
    obj[0x122] = 0x11;
    obj[0x232] = 0;
    obj[0x125] = 0xFF;
    *(s32 *) (obj + 0xF8) = 0x100E;
    if (snap != 0) {
        *(s32 *) (obj + 0xF8) = 0x100E | 0x8000;
        *(void **) (obj + 0x31C) = allocate_memory(0x1C0, 1, 0, 0);
        bzero(*(void **) (obj + 0x31C), 0x1C0);
        obj[0x103] = 1;
    }
    *(f32 *) (obj + 0x14C) = smooth;
    *(f32 *) (obj + 0x150) = smooth;
    obj[0x66] = *((u8 *) D_800D154C + 0x66) & 0xC;
    obj[0x284] = snap;
    *(s16 *) (obj + 0x278) = mode;
    if (mode == 2 || mode == 18) {
        *(s16 *) (obj + 0x282) = 0x3C;
    }
    switch (mode) {
    case 0:
        obj_effect_run_handler(obj, 8, NULL);
        char_fx_attach(move_watch_spawn(obj, 1, 0), (struct127 *) obj, 0x13);
        break;
    case 1:
        obj_effect_run_handler(obj, 1, NULL);
        char_fx_attach(move_watch_spawn(obj, 1, 0), (struct127 *) obj, 0x13);
        break;
    case 15:
        obj_effect_run_handler(obj, 0xD, NULL);
        break;
    case 13:
        actor_sound_play(0x237, (struct127 *) obj, 0x7530, 0x1F4, 0x7D0);
        // fall through
    case 5:
    case 9:
    case 10:
        obj_effect_run_handler(obj, 0xC, NULL);
        break;
    }
    return (s32) obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/camera_object_spawn.s")
#endif
// requires jump table
#ifdef NON_MATCHING
void vec3_to_yaw_pitch_deg(void *, f32 *, f32 *);
// player_camera_view_update: P259: sets up the player camera for D_800D154C (the args the callers leave in a0 / a1
// are not read) by event mode D_800D1580: yaw = facing angle +0x7A + 90 degrees, pitch 45, distance 323; in modes
// 5 / 9 / 10 yaw / pitch come from the direction of matrix 3 of the player's +0x1D4 matrices (degrees, folded to
// -180..180); otherwise the pitch follows the camera record's +0x780 (when its +0x2C is 0x100) or the player's tilt
// +0x1D1. Per mode: distance / height / smoothing (mode 3: aim at the D_800CCA0C target, distance 500), then
// vec_from_yaw_pitch turns pitch / distance into the offset and camera_object_spawn applies it (flag t1 = snap).
/* was func_1506CE6C */
void objev_player_camera_view(void) {
    struct127 *player;
    f32 (*mtx)[4];
    f32 target[3];
    f32 *target_ptr;
    f32 dir_x;
    f32 dir_y;
    f32 dir_z;
    f32 off_h;
    f32 off_y;
    f32 off_unused;
    f32 smooth;
    f32 yaw;
    f32 pitch;
    f32 dist;
    f32 height;
    f32 cam_pitch;
    f32 a;
    f32 b;
    s32 flags54;
    s32 view;
    s32 snap;
    s32 mode;
    struct108 *cam;

    player = D_800D154C;
    flags54 = 0;
    height = 0.0f;
    pitch = 45.0f;
    dist = 323.0f;
    smooth = 0.5f;
    yaw = (f32) (player->unk7A + 0x4000) * 0.0054931640625f;
    mode = D_800D1580;
    view = -1;
    snap = FALSE;
    target_ptr = NULL;
    if (mode == 5 || mode == 9 || mode == 10) {
        view = 3;
    }
    if (view != -1) {
        if (player->unk1D4 != NULL) {
            mtx = (f32 (*)[4]) ((u8 *) player->unk1D4 + view * 0x40);
            mtxf_transform_point(mtx, 0.0f, 0.0f, 1.0f, &dir_x, &dir_y, &dir_z);
            dir_x -= mtx[3][0];
            dir_y -= mtx[3][1];
            dir_z -= mtx[3][2];
            a = math_atan2f(dir_x, dir_z);
            b = math_atan2f(dir_y, sqrtf(dir_x * dir_x + dir_z * dir_z));
            a *= 57.295776f;
            b *= 57.295776f;
            if (180.0f < a) {
                a -= 360.0f;
            }
            if (180.0f < b) {
                b -= 360.0f;
            }
            yaw = a;
            pitch = b;
        }
    } else {
        cam = player->camera;
        if (cam != NULL && cam->unk2C == 0x100) {
            cam_pitch = cam->unk780;
            if (cam_pitch < 0.0f) {
                cam_pitch = cam_pitch * -0.5f + cam_pitch * -0.2333f + 7.0f;
            } else {
                cam_pitch = cam_pitch * -0.5f + (60.0f - cam_pitch) * 0.133f;
            }
            pitch = cam_pitch * 1.40625f;
        } else {
            pitch = (f32) -player->unk1D1;
        }
    }
    switch (mode) {
    case 2:
    case 11:
    case 12:
    case 18:
        snap = TRUE;
        break;
    case 15:
        pitch = pitch * 2.2f + 7.0f;
        height = 3.3f;
        break;
    case 1:
        height = 2.4f;
        break;
    case 3:
        dist = 500.0f;
        vec3_to_yaw_pitch_deg(D_800CCA0C + 0xE8, &yaw, &pitch);
        target[0] = *(f32 *) (D_800CCA0C + 0xDC);
        target[1] = *(f32 *) (D_800CCA0C + 0xE0);
        pitch = -pitch;
        snap = TRUE;
        target_ptr = target;
        target[2] = *(f32 *) (D_800CCA0C + 0xE4);
        break;
    case 6:
        snap = TRUE;
        pitch = 0.0f;
        dist = 500.0f;
        break;
    case 17:
        flags54 = 0x30;
        pitch = 0.0f;
        dist = 150.0f;
        break;
    case 4:
        dist = 250.0f;
        break;
    case 5:
    case 9:
    case 10:
        snap = TRUE;
        height = 5.0f;
        dist = 593.0f;
        smooth = 1.5f;
        break;
    }
    vec_from_yaw_pitch((u16) (s32) (pitch * 182.04445f), dist, 0.0f, &off_h, &off_y, &off_unused);
    off_y = -off_y;
    camera_object_spawn(yaw, off_h, off_y, height, 100, mode, 0.0f, smooth, (s32) target_ptr, flags54, snap);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_player_camera_view.s")
#endif

#ifdef NON_MATCHING
extern f32 D_8009A104;
void obj_burning_fx_start(u8 *, u8);

/* was func_1506D2E8 */
void objev_throw_object(void) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
    } sp;
    f32 sp2C;
    f32 var_f0;
    struct127 *temp_v0;
    u16 temp_v0_2;

    temp_v0 = obj_find_by_spawn(setup_entry_find_by_id(D_800D1580 & 0xFF));
    if (temp_v0 != NULL) {
        sp2C = 0.0f;
        obj_burning_fx_start(temp_v0, 0xFF);
        var_f0 = 0.0f;
        if (D_800D1580 & 0xFF00) {
            var_f0 = D_800D154C->camera->unk780 - 15.0f;
        }
        temp_v0_2 = D_800D154C->unk7A;
        temp_v0->unk78 = temp_v0_2;
        temp_v0->unk7A = temp_v0_2;
        temp_v0->unk76 = temp_v0_2;
        vec_from_yaw_pitch(temp_v0_2 & 0xFFFF, 5000.0f, var_f0, &sp.u40, &sp.u3C, &sp.u38);
        (*(s16 *)((u8 *)(D_800D2104[temp_v0->unk13F]) + 8)) = (s16) (s32) (D_800D154C->x_position + sp.u40);
        (*(s16 *)((u8 *)(D_800D2104[temp_v0->unk13F]) + 0xC)) = (s16) (s32) (D_800D154C->z_position + sp.u3C);
        (*(s16 *)((u8 *)(D_800D2104[temp_v0->unk13F]) + 0xA)) = (s16) (s32) (D_800D154C->y_position + sp.u38);
        temp_v0->unk65 = 0;
        temp_v0->unk218 = NULL;
        if (D_800D1580 & 0xFF00) {
            temp_v0->unk232 = 4;
            temp_v0->xz_scale = 0.25f;
            temp_v0->y_scale = 0.25f;
            temp_v0->y_position = D_800D154C->y_position + 70.0f;
            return;
        }
        temp_v0->unk232 = 2;
        temp_v0->xz_velocity = -15.0f;
        temp_v0->y_velocity = 34.0f;
        temp_v0->xz_scale = 0.5f;
        temp_v0->y_scale = 0.5f;
        temp_v0->gravity = D_8009A104;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_throw_object.s")
#endif

// mode_handler_noop: empty handler, entry 16 of the D_8008679C mode table (EU 0x1506D8AC; US 0x1506D4EC). It was
// glued to the end of objev_throw_object (split in P263), so the port had no function at that table address.
/* was func_1506D4EC */
void objev_nop_1506d4ec(void) {
}
// NON-MATCHING: plenty to figure out here
// void objev_throw_object(void) {
//     f32 sp40;
//     f32 sp3C;
//     f32 sp38;
//     f32 sp2C;
//     u16 temp_v0_2;
//     struct127 *temp_s0;
//     f32 phi_f0;
//
//     temp_s0 = obj_find_by_spawn(setup_entry_find_by_id(D_800D1580 & 0xFF));
//     if (temp_s0 != NULL) {
//         sp2C = 0.0f;
//         func_151A3390(temp_s0, 0xFF);
//         phi_f0 = 0.0f;
//         if ((D_800D1580 & 0xFF00) != 0) {
//             phi_f0 = D_800D154C->camera->unk780 - 15.0f;
//         }
//         temp_v0_2 = D_800D154C->unk7A;
//         temp_s0->unk78 = temp_v0_2;
//         temp_s0->unk7A = temp_v0_2;
//         temp_s0->unk76 = temp_v0_2;
//         vec_from_yaw_pitch(temp_v0_2, 5000.0f, phi_f0, &sp40, &sp3C, &sp38);
//         D_800D2104[temp_s0->unk13F]->unk8 = (s16) (s32) (D_800D154C->x_position + sp40);
//         D_800D2104[temp_s0->unk13F]->unkC = (s16) (s32) (D_800D154C->z_position + sp3C);
//         D_800D2104[temp_s0->unk13F]->unkA = (s16) (s32) (D_800D154C->y_position + sp38);
//         temp_s0->unk65 = (u8)0;
//         temp_s0->unk218 = 0;
//         if ((D_800D1580 & 0xFF00) != 0) {
//             temp_s0->unk232 = (u8)4;
//             temp_s0->unk14C = 0.25f;
//             temp_s0->unk150 = 0.25f;
//             temp_s0->y_position = (f32) (D_800D154C->y_position + 70.0f);
//         } else {
//             temp_s0->unk232 = (u8)2;
//             temp_s0->xz_velocity = -15.0f;
//             temp_s0->y_velocity = 34.0f;
//             temp_s0->unk14C = 0.5f;
//             temp_s0->unk150 = 0.5f;
//             temp_s0->gravity = (f32) D_80099D44;
//         }
//     }
// }

/* was func_1506D4F4 */
void objev_anim_slow(void) {
    obj_start_anim(D_800D154C, D_800D154C->unk84.uh, 0.009999999776482582f, 0.0f, 0.0f, 0.0f, 0);
}

/* was func_1506D538 */
void objev_lose_life_cur_player(void) {
    if (D_800C35EA != 1) {
        player_lose_life(D_800C3E78);
    }
}

/* was func_1506D570 */
void objev_clear_6e(void) {
    D_800D154C->unk6E = 0;
}

#ifdef NON_MATCHING
/* Re-issue the current object's packed command D_800D1580 (bytes 3 and 2, low half = a duration in
 * frames scaled by the speed at unk2D0 + 0x10, 0xFFFF = none) through face_anim_start, unless the object
 * is in state 0x2A (P15, hand C). The asm returns junk (a %hi) on the early path, so this is void. */
/* was func_1506D584 */
void objev_start_anim_cmd(void) {
    struct127 *obj = D_800D154C;
    f32 speed;
    u16 t;

    if (obj->unk70 == 0x2A) {
        return;
    }
    speed = *(f32 *)((u8 *)obj->unk2D0 + 0x10);
    if (speed == 0.0f) {
        speed = D_8009A108;
    }
    t = D_800D1580 & 0xFFFF;
    if (t != 0xFFFF) {
        t = (u32)(t / speed);
    }
    face_anim_start(obj, D_800D1580 >> 24, D_800D1580 >> 16, t, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_start_anim_cmd.s")
#endif
// ???
/* was func_1506D6B4 */
void objev_anim_in_water_by_health(void) {
    s32 var_v0;

    if ((-10000.0f != D_800D154C->unk118) && !(D_800D154C->unk118 < D_800D154C->unk1A6)) {
        if (D_800D154C->health >= 2) {
            var_v0 = 0x2C;
        } else {
            var_v0 = 0x29;
        }
        D_800D1580 = ((var_v0 & 0xFF) << 0x18) | (D_800D1580 & 0xFFFF);
        objev_start_anim_cmd();
    }
}
/* was func_1506D74C */
void objev_ledge_climb_up(void) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    if (D_800D154C->in_water == 0) {
        D_800D154C->gravity = 5.0f;
        D_800D154C->y_velocity = 0.0f;
    }
    D_800D154C->y_position += 70.0f;
    (*(s8 *)((u8 *)D_800D154C + 0x137)) = 0;
    D_800D154C->disable_run = 0;
    vec_from_yaw_pitch(D_800D154C->unk76, (f32) D_800D1580, 0.0f, &sp34, &sp30, &sp2C);
    obj_start_anim(D_800D154C, 0xFU, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    D_800D154C->x_position += sp34;
    D_800D154C->z_position += sp30;
    D_800D154C->unk100 |= 2;
    D_800D154C->unk28 = 0.0f;
    D_800D154C->unk83 = 0x14;
    D_800D154C->unk31C->unk44 = 0xC;
    D_800D154C->unk31C->unk54 = 0xA;
}

/* was func_1506D898 */
void objev_ledge_drop_down(void) {
    D_800D154C->y_position -= 80.0f;
    obj_start_anim(D_800D154C, 663, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    D_800D154C->unk100 &= 0xFFDF;
    D_800D154C->unk83 = 0;
    D_800D154C->disable_run = 0;
    D_800D154C->unk31C->unk97 = 0;
    D_800D154C->unk31C->unk44 = 12;
}

/* was func_1506D934 */
void objev_set_103(void) {
    D_800D154C->unk103 = D_800D1580;
}

/* was func_1506D950 */
void objev_nop_1506d950(void) {
}

/* was func_1506D958 */
void objev_set_owned_obj_flags(s32 arg0) {
    s32 i;
    s32 id;

    id = D_800D1580 & 0xFF;
    arg0 = (D_800D1580 >> 8) & 0xFF;
    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].interaction_state != 0) && (id == D_800CC2D0[i].unkAB) && ((D_800C3E78 + 1) == D_800CC2D0[i].unk65)) {
            D_800CC2D0[i].unk101 &= 0xFFFE;
            D_800CC2D0[i].unk101 |= arg0;
            return;
        }
    }
}

/* was func_1506DA78 */
void objev_set_immune(void) {
    D_800D154C->immune = D_800D1580;
}

/* was func_1506DA94 */
void objev_screen_effect_stop(void) {
    if (D_800D1580 != 0) {
        if ((D_800D154C->unk44 > 20.0f) && (D_800D154C->xz_velocity > 20.0f)) {
            D_800D154C->unk83 = (u8)0;
        }
    }
    fx_dust_puff_behind_obj(D_800C3E78, 0, 24, 0, 409, 4, 170, 0xFF, 0);
}

/* was func_1506DB30 */
void objev_set_1890_update(void) {
    D_800D1890 = (s8) D_800D1580;
    aiscript_nop_b();
}

/* was func_1506DB5C */
void objev_set_xz_velocity(void) {
    D_800D154C->xz_velocity = (f32) D_800D1580;
}

/* was func_1506DB84 */
void objev_set_239(void) {
    D_800D154C->unk239 = (s8) D_800D1580;
}

/* was func_1506DBA0 */
void objev_set_1e5_1e6(void) {
    D_800D154C->unk1E5 = D_800D1580 & 0xff;
    D_800D154C->unk1E6 = (D_800D1580 >> 8) & 0xff;
}

/* was func_1506DBD4 */
void objev_link_nearby_object(void) {
    struct127 *temp_v0 = obj_find_child_nth(D_800D154C, 0);
    if (temp_v0 != NULL) {
        obj_release_partner_remove(temp_v0, D_800D154C);
    }
}

/* was func_1506DC10 */
void objev_random_voice(void) {
    s32 v;
    s32 a;

    if (((D_800D154C->unk118 - 60.0f) < D_800D154C->y_position) || (-10000.0f == D_800D154C->unk118)) {
        v = random_int() & 3;
        if (v >= 2) {
            a = v + 0x612;
        } else {
            a = v + 0x8F;
        }
    } else {
        a = 9;
    }
    obj_sfx_play_alt(a, D_800D154C);
}

/* was func_1506DCA4 */
void objev_set_2e8(void) {
    D_800D154C->unk2E8 = D_800D1580;
}

/* was func_1506DCC0 */
void objev_set_2ec(void) {
    D_800D154C->unk2EC = (s32) D_800D1580;
}

/* was func_1506DCDC */
void objev_set_health(void) {
    D_800D154C->health = (s8) D_800D1580;
}

/* was func_1506DCF8 */
void objev_nop_1506dcf8(void) {
}

/* was func_1506DD00 */
void objev_set_flags_f8(void) {
    struct127 *temp_v1;

    if (D_800D1580 == 0) {
        temp_v1 = D_800D154C;
        temp_v1->unkF8 = (s32) temp_v1->unk144->unk18;
    } else {
        temp_v1 = D_800D154C;
        temp_v1->unkF8 |= D_800D1580;
    }
}

/* was func_1506DD44 */
void objev_clear_flags_f8(void) {
    D_800D154C->unkF8 &= ~D_800D1580;
}

/* was func_1506DD6C */
void objev_set_matrix_physics(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->matrix_physics = D_800D1580 & 0x7F;
    }
    if (D_800D1580 == 0) {
        D_800D154C->unk76 = D_800D154C->unk7A;
    }
}

/* was func_1506DDB8 */
void objev_nop_1506ddb8(void) {
}

/* was func_1506DDC0 */
void objev_level_screen_effect(void) {
    if (level_screen_effect_active(D_800BE9F0) != 0) {
        particle_emitter_preset_cooldown(D_800C3E78, D_800D1580, 0xFF, 0);
    }
}

/* was func_1506DE04 */
void objev_screen_effect_twice(void) {
    s32 i;
    for(i = 0; i < 2; i++) {
        fx_dust_puff_behind_obj(D_800C3E78, 10, 18, 12, 0x199, 4, 0xAA, 0xFF, 0);
    }
}

// jump table
void objev_dust_square_large(void);
void objev_shadow_square_small(void);
s32 nodes_destroy_for_player();
void player_joint_beam_spawn(s32 side);
void particle_emitter_preset_obj_burst(s32, s32, u8, s32);
s32 particle_emitter_preset_obj_pair(u8, s32, s32, s32, u8, s32);
#ifdef NON_MATCHING
void shard_ring_spawn(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7);
#else
s32 shard_ring_spawn(f32, f32, f32, s32, s32, s32, f32, f32);
#endif

/* was func_1506DE84 */
void objev_effect_by_mode(void) {
    switch (D_800D1580) {
    case 0:
        if (D_800D154C->unk28 == 0.0f) {
            shard_ring_spawn(D_800D154C->x_position, D_800D154C->y_position, D_800D154C->z_position, 0x1E, 0x1E, 7, 0.1f, 0.1f);
            return;
        }
    default:
        return;
    case 1:
        if ((u32) (random_int() & 0xFF) < 0x40U) {
            shard_ring_spawn(D_800D154C->x_position, D_800D154C->y_position, D_800D154C->z_position, 0xA, 0x14, 7, 0.03f, 0.02f);
            D_800D1580 = 0x106;
            objev_sound_or_stop(0x12C, 0x708);
            return;
        }
        break;
    case 2:
        particle_emitter_preset_obj_burst(D_800C3E78, 0x10, 0xFF, 0);
        return;
    case 3:
        particle_emitter_preset_obj_burst(D_800C3E78, 0x28, 0xFF, 0);
        return;
    case 4:
        particle_emitter_preset_obj_burst(D_800C3E78, 0x28, 0xFF, 0);
        return;
    case 5:
        particle_emitter_preset_obj_pair(D_800C3E78, 0x1E, 0x14, 2, 0xFF, 0);
        return;
    case 6:
        particle_emitter_preset_obj_pair(D_800C3E78, 0x12, 0xC, 2, 0xFF, 0);
        return;
    case 7:
        particle_emitter_preset_obj_pair(D_800C3E78, 0x3C, 0x78, 2, 0xFF, 0);
        return;
    case 8:
        objev_dust_square_large();
        return;
    case 9:
        player_joint_beam_spawn(0);
        return;
    case 10:
        player_joint_beam_spawn(1);
        return;
    case 11:
        objev_shadow_square_small();
        return;
    case 12:
        particle_emitter_preset_obj_pair(D_800C3E78, 0x12, 0xC, 0, 0xFF, 0);
        return;
    case 13:
        nodes_destroy_for_player();
        break;
    }
}

#ifdef NON_MATCHING
void mtxf_transform_point(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void shard_ring_spawn(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7);
void particle_quad_edge_sparks(f32 *quad, f32 x, f32 z, s32 arg3, f32 size, s32 arg5, s32 arg6, s32 arg7, s32 alpha, s32 arg9);

/*
 * P85: script command 8: as objev_shadow_square_small (command 11) with a 540 x 540 square (corners (+-270, 0, +-270) through
 * the object matrix +0x1D4, at the object's height +0x180); each corner also goes to shard_ring_spawn (corner x,
 * transformed y, z, 30, 20, 7, 0.13, 0.1), and particle_quad_edge_sparks gets 4 and the full +0x14C size.
 */
/* was func_1506E0EC */
void objev_dust_square_large(void) {
    f32 quad[4][3];
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (*(void **) ((u8 *) D_800D154C + 0x1D4) == NULL) {
        return;
    }
    x = 270.0f;
    z = 270.0f;
    for (i = 0; i < 4; i++) {
        y = 0.0f;
        mtxf_transform_point(*(f32 (**)[4]) ((u8 *) D_800D154C + 0x1D4), x, 0.0f, z, &x, &y, &z);
        quad[i][0] = x;
        quad[i][1] = *(f32 *) ((u8 *) D_800D154C + 0x180);
        quad[i][2] = z;
        shard_ring_spawn(x, y, z, 30, 20, 7, 0.13f, 0.1f);
        if (i == 0) {
            z = 270.0f;
            x = -270.0f;
        } else if (i == 1) {
            x = -270.0f;
            z = -270.0f;
        } else if (i == 2) {
            x = 270.0f;
            z = -270.0f;
        }
    }
    particle_quad_edge_sparks(&quad[0][0], *(f32 *) ((u8 *) D_800D154C + 0x14), *(f32 *) ((u8 *) D_800D154C + 0x1C), 4,
                  *(f32 *) ((u8 *) D_800D154C + 0x14C), 0, 4, 4, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_dust_square_large.s")
#endif
#ifdef NON_MATCHING
void mtxf_transform_point(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void particle_quad_edge_sparks(f32 *quad, f32 x, f32 z, s32 arg3, f32 size, s32 arg5, s32 arg6, s32 arg7, s32 alpha, s32 arg9);

/*
 * P85: script command 11: a 200 x 200 square around the current object (D_800D154C) in its model space
 * (corners (+-100, 0, +-100) through the object matrix +0x1D4, at the object's height +0x180) is passed to
 * particle_quad_edge_sparks with the object position (+0x14 / +0x1C) and half the object's +0x14C size. Nothing without a matrix.
 */
/* was func_1506E2CC */
void objev_shadow_square_small(void) {
    f32 quad[4][3];
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (*(void **) ((u8 *) D_800D154C + 0x1D4) == NULL) {
        return;
    }
    x = 100.0f;
    z = 100.0f;
    for (i = 0; i < 4; i++) {
        y = 0.0f;
        mtxf_transform_point(*(f32 (**)[4]) ((u8 *) D_800D154C + 0x1D4), x, 0.0f, z, &x, &y, &z);
        quad[i][0] = x;
        quad[i][1] = *(f32 *) ((u8 *) D_800D154C + 0x180);
        quad[i][2] = z;
        if (i == 0) {
            z = 100.0f;
            x = -100.0f;
        } else if (i == 1) {
            x = -100.0f;
            z = -100.0f;
        } else if (i == 2) {
            x = 100.0f;
            z = -100.0f;
        }
    }
    particle_quad_edge_sparks(&quad[0][0], *(f32 *) ((u8 *) D_800D154C + 0x14), *(f32 *) ((u8 *) D_800D154C + 0x1C), 5,
                  *(f32 *) ((u8 *) D_800D154C + 0x14C) * 0.5f, 0, 4, 4, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_shadow_square_small.s")
#endif
#ifdef NON_MATCHING
s32 actor_sound_is_playing(struct127 *arg0);
s32 actor_sound2_is_playing(struct127 *arg0);
s32 mp3_stream_get_state(void);
s32 sound_pick_variant(s32, s32);
s32 random_int(void);
extern s32 *D_800BE9C8[];

/* Resolves a sound / event word *slot for a record. Bit 21: conditional on mode (0 / 1: record tests, 2: a global
 * test). Ids >= 2000 come from the per-level table D_800BE9C8[rec->unk288] (high bits kept if set). Bits 24-31 are
 * a random-chance byte, bits 16-20 a variant count. Returns 1 and writes *slot, or 0 when it should not play. */
/* was func_1506E46C */
s32 sound_word_resolve(struct127 *rec, s32 *slot, s32 mode) {
    u32 w = *slot;
    u32 id = w & 0x7FFF;
    u32 v;
    u32 hi;

    if (w & 0x200000) {
        if (mode == 0) {
            if (actor_sound_is_playing(rec) != 0) {
                return 0;
            }
        } else if (mode == 1) {
            if (actor_sound2_is_playing(rec) != 0) {
                return 0;
            }
        } else if (mode == 2) {
            if (mp3_stream_get_state() == 1) {
                return 0;
            }
        }
    }
    if (id >= 2000) {
        v = D_800BE9C8[*((u8 *)rec + 0x288)][id - 2000];
        if (v == 0) {
            return 0;
        }
        hi = w & 0xFF200000;
        if (hi != 0) {
            w = hi | (v & 0xFFFFFF);
        } else {
            w = v;
        }
    }
    if ((w >> 16) != 0) {
        u32 variants = (w >> 16) & 0x1F;
        if ((w >> 24) < (u32)(random_int() & 0xFF)) {
            return 0;
        }
        w &= 0x7FFF;
        if (variants != 0) {
            w = sound_pick_variant(w, variants);
        }
    }
    *slot = w;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/sound_word_resolve.s")
#endif
/* was func_1506E5FC */
void objev_sound_300_1800(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_or_stop(300, 1800);
    }
}

/* was func_1506E63C */
void objev_sound_100_800(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_or_stop(100, 800);
    }
}

/* was func_1506E67C */
void objev_sound_190_1300(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_or_stop(190, 1300);
    }
}

/* was func_1506E6BC */
void objev_sound_300_3000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_or_stop(300, 3000);
    }
}

/* was func_1506E6FC */
void objev_sound_700_4000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_or_stop(700, 4000);
    }
}

/* was func_1506E73C */
void objev_sound_3000_8000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_or_stop(3000, 8000);
    }
}

/* was func_1506E77C */
void objev_sound_hi_300_1800(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_hi_word(300, 1800);
    }
}

/* was func_1506E7BC */
void objev_sound_hi_300_3000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) {
        objev_sound_hi_word(300, 3000);
    }
}

/* was func_1506E7FC */
void objev_sound_if_grounded(void) {
    if (D_800D154C->unk28 == 0.0f) {
        if (D_800D154C->unk107 == 0) {
            objev_sound_300_1800();
        }
    }
}

/* was func_1506E848 */
void objev_sound_if_not_playing(void) {
    if ((sound_word_resolve(D_800D154C, &D_800D1580, 0) != 0) && (sound_id_is_playing((u16)D_800D1582) == 0)) {
        objev_sound_or_stop(0x50, 800);
    }
}

/* was func_1506E898 */
void objev_sound_global_300_1800(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 2) != 0) {
        objev_sound_hi_word_3(300, 1800);
    }
}

/* was func_1506E8D8 */
void objev_sound_alt_300_1800(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_alt_or_stop(300, 1800);
    }
}

/* was func_1506E918 */
void objev_sound_alt_100_800(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_alt_or_stop(100, 800);
    }
}

/* was func_1506E958 */
void objev_sound_alt_190_1300(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_alt_or_stop(190, 1300);
    }
}

/* was func_1506E998 */
void objev_sound_alt_300_3000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_alt_or_stop(300, 3000);
    }
}

/* was func_1506E9D8 */
void objev_sound_alt_700_4000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_alt_or_stop(700, 4000);
    }
}

/* was func_1506EA18 */
void objev_sound_alt_3000_8000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_alt_or_stop(3000, 8000);
    }
}

/* was func_1506EA58 */
void objev_sound_alt_hi_300_3000(void) {
    if (sound_word_resolve(D_800D154C, &D_800D1580, 1) != 0) {
        objev_sound_hi_word_alt(300, 3000);
    }
}

/* was func_1506EA98 */
void objev_throw_carried(void) {
    u8 temp_t6;
    struct127 *temp_a1;

    temp_t6 = (D_800D154C->unk13C - 100);
    if (D_800D154C->unk13C != 0) {
        temp_a1 = &D_800CC2D0[temp_t6];
        if (D_800CC2D0[temp_t6].unk13D >= 100) {
            D_800CC2D0[temp_t6].unk13D = (u8)0U;
            D_800CC2D0[temp_t6].xz_velocity = 18.0f;
            D_800CC2D0[temp_t6].y_velocity = 40.0f;
            D_800CC2D0[temp_t6].gravity = 6.0f;
            D_800CC2D0[temp_t6].unk76 = (u16) D_800D154C->unk7A;
            D_800CC2D0[temp_t6].unk65 = (u8)0;
            if (D_800CC2D0[temp_t6].id  == 0x20) {
                D_800CC2D0[temp_t6].unkF8 |= 0x200;
                D_800CC2D0[temp_t6].y_velocity = 0.0f;
                D_800CC2D0[temp_t6].gravity = 0.0f;
                D_800CC2D0[temp_t6].xz_velocity = 0.0f;
            }
            D_800CC2D0[temp_t6].stunned = (u8)0xFE;
            D_800CC2D0[temp_t6].unk105 = (u8)0;
            D_800CC2D0[temp_t6].unk106 = obj_find_reaction_row(0xC, temp_a1); //, temp_t6);
            D_800CC2D0[temp_t6].unk84.uh = (u16)0xFFFF;
            D_800CC2D0[temp_t6].unk1CC = (f32) 1000000.0f;
            obj_hit_reaction_advance(temp_t6, temp_a1);
            D_800CC2D0[temp_t6].unk25C |= 0x40;
        }
        D_800D154C->unk13C = (u8)0;
    }
}

/* was func_1506EBC0 */
void objev_drop_carried(void) {
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C) {
        if ((s32) D_800CC2D0[temp_v0].unk13D >= 0x64) {
            D_800CC2D0[temp_v0].unk65 = 0;
            D_800CC2D0[temp_v0].unk13D = (u8)0U;
            D_800CC2D0[temp_v0].xz_velocity = 0.0f;
            D_800CC2D0[temp_v0].y_velocity = 0.0f;
            D_800CC2D0[temp_v0].gravity = 6.0f;
            D_800CC2D0[temp_v0].unk1CC = 1000000.0f; // 1000000.0
        }
        D_800D154C->unk13C = 0U;
    }
}

/* was func_1506EC50 */
void objev_hold_frame_airborne(void) {
    if (0.2f < D_800D154C->unk28) {
        if (((D_800D1580 & 0x8000) == 0) || (D_800CC2E8[0] < D_800D154C->y_position)) {
            D_800D1878 = D_800D1580 & 0xFF;
            D_800D1880 = 0;
            D_800D154C->unk138 -= 1;
        }
    }
}

/* was func_1506ECD0 */
void objev_anim_set_flag_8000(void) {
    D_800D154C->unk2D0->unk4 |= 0x8000;
}

/* was func_1506ECF0 */
void objev_set_3a(void) {
    D_800D154C->unk3A = (s8) D_800D1580;
}

/* was func_1506ED0C */
void objev_set_83_lock(void) {
    D_800D154C->unk83 = (s8) D_800D1580;
    D_800D154C->unk100 |= 0x10;
    D_800D154C->unk31C->unk31 = (u8)1;
}

/* was func_1506ED4C */
void objev_set_100(void) {
    D_800D154C->unk100 = (s8) D_800D1580;
}

/* was func_1506ED68 */
void objev_unlock_a9(void) {
    D_800D154C->unkA9 = (u8)5;
    D_800D154C->unk31C->unk31 = (u8)0;
}

/* was func_1506ED90 */
void objev_set_21c(void) {
    D_800D154C->unk21C = (s16) D_800D1580;
}

/* was func_1506EDAC */
void objev_set_flags_f4(void) {
    D_800D154C->unkF4 = (s32) D_800D1580;
}

/* was func_1506EDC8 */
void objev_clear_flags_f4(void) {
    D_800D154C->unkF4 &= ~D_800D1580;
}

/* was func_1506EDF0 */
void objev_or_flags_f4(void) {
    D_800D154C->unkF4 |= D_800D1580;
}

/* was func_1506EE14 */
void objev_or_flags_25c(void) {
    D_800D154C->unk25C |= D_800D1580;
}

/* was func_1506EE38 */
void objev_clear_flags_25c(void) {
    D_800D154C->unk25C &= ~D_800D1580;
}

/* was func_1506EE60 */
void objev_trail_start_or_stop(void) {
    s32 temp_a1 = D_800D1580 & 0xFFFF;

    if (D_800D1580 != 0) {
        afterimage_start(D_800D154C, temp_a1, D_800D1580 >> 0x10);
    } else {
        afterimage_stop(D_800D154C, temp_a1);
    }
}
// NON-MATCHING: same issue as earlier
// void objev_trail_start_or_stop(void) {
//     s32 temp_a1;
//     s32 temp_v0;
//
//     temp_v0 = D_800D1580;
//     temp_a1 = temp_v0 & 0xFFFF;
//     if (temp_v0 != 0) {
//         func_15188810(D_800D154C.unk0, temp_a1, temp_v0 >> 0x10);
//         return;
//     }
//     func_15188A9C(D_800D154C.unk154C, temp_a1);
// }

/* was func_1506EEAC */
void objev_trail_set(void) {
    afterimage_set_skin(D_800D154C, D_800D1580);
}

/* was func_1506EED8 */
void objev_set_24e(void) {
    D_800D154C->unk24E = (s8) D_800D1580;
}

/* was func_1506EEF4 */
void objev_set_path_cmd(void) {
    D_800D154C->unk276 = (D_800D1580 >> 16) & 0xFFFF;
    D_800D154C->unk278 = (D_800D1580 >> 24) & 0xFF;
    D_800D154C->unk282 = D_800D1580 & 0xFFFF;
    D_800D154C->unk284 = 0;
    D_800D154C->unk285 = 0;
    D_800D154C->unk286 = 0;
    D_800D154C->unk287 = 0;
}

// TBD whats goins on here
#ifdef NON_MATCHING
/*
 * P80: script command: +0x282 = 0xFFFF, +0x276 = 5, and the byte pair +0x284 + 2 * i (i = bits 16..23 of the
 * command word D_800D1580) = bits 8..15, bits 0..7.
 */
/* was func_1506EF5C */
void objev_set_path_pair(void) {
    s32 w = D_800D1580;
    s32 i = ((w >> 16) & 0xFF) * 2;

    *(u16 *) ((u8 *) D_800D154C + 0x282) = 0xFFFF;
    *((u8 *) D_800D154C + 0x276) = 5;
    *((u8 *) D_800D154C + 0x284 + i) = w >> 8;
    *((u8 *) D_800D154C + 0x285 + i) = w;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_set_path_pair.s")
#endif

/* was func_1506EFB4 */
void objev_clear_282(void) {
    D_800D154C->unk282 = (u16)0;
}

/* was func_1506EFC8 */
void objfx_bb760_unless_8c(s32 arg0) {
    if (D_800D154C->id != 0x8C) {
        obj20_trail_chunk_spawn(D_800D154C);
    }
}

/* was func_1506F004 */
void objfx_bcbbc(s32 arg0) {
    obj20_side_chunks_spawn(D_800D154C);
}

/* was func_1506F02C */
void objfx_ba4c0(s32 arg0) {
    crumble_emitter_spawn(D_800D154C, 0xFF, 0);
}

/* was func_1506F05C */
void objfx_dust_50(s32 arg0) {
    obj_dust_effect(D_800D154C, 0x32, 0xFF, 1);
}

/* was func_1506F090 */
void objfx_dust_default(s32 arg0) {
    obj_dust_effect(D_800D154C, -1, 0xFF, 1);
}

/* was func_1506F0C4 */
void objfx_c1260_0(s32 arg0) {
    foot_ring_debris_effect(D_800D154C, 0);
}

/* was func_1506F0F0 */
void objfx_c1260_1(s32 arg0) {
    foot_ring_debris_effect(D_800D154C, 1);
}

/* was func_1506F11C */
void objfx_spray_0(s32 arg0) {
    foot_splash_effect(D_800D154C, 0, 0xFF);
}

/* was func_1506F14C */
void objfx_spray_1(s32 arg0) {
    foot_splash_effect(D_800D154C, 1, 0xFF);
}

/* was func_1506F17C */
void objfx_aeeb0(s32 arg0) {
    obj_trail_burst_spawn(D_800D154C, 0xFF);
}

#ifdef NON_MATCHING
/* the emitter spec spec_emitter_spawn reads (layout as game_eu_1C3530's Emitter2Spec) */
typedef struct {
    /* 0x000 */ s32 u000;
    /* 0x004 */ u8 *u004;
    /* 0x008 */ u8 u008;
    /* 0x009 */ u8 u009;
    /* 0x00A */ u8 pad00A[2];
    /* 0x00C */ f32 u00C;
    /* 0x010 */ f32 u010;
    /* 0x014 */ f32 u014;
    /* 0x018 */ f32 u018;
    /* 0x01C */ f32 u01C;
    /* 0x020 */ f32 u020;
    /* 0x024 */ f32 u024;
    /* 0x028 */ f32 u028;
    /* 0x02C */ f32 u02C;
    /* 0x030 */ f32 u030;
    /* 0x034 */ f32 u034;
    /* 0x038 */ s8 u038;
    /* 0x039 */ u8 u039;
    /* 0x03A */ s8 u03A;
    /* 0x03B */ s8 u03B;
    /* 0x03C */ u8 u03C;
    /* 0x03D */ u8 u03D;
    /* 0x03E */ u8 u03E;
    /* 0x03F */ u8 pad03F[1];
    /* 0x040 */ f32 u040;
    /* 0x044 */ f32 u044;
    /* 0x048 */ f32 u048;
    /* 0x04C */ u8 u04C;
    /* 0x04D */ u8 pad04D[3];
    /* 0x050 */ u8 u050;
    /* 0x051 */ u8 u051;
    /* 0x052 */ u8 u052;
    /* 0x053 */ u8 u053;
    /* 0x054 */ u8 u054;
    /* 0x055 */ u8 pad055[3];
    /* 0x058 */ f32 u058;
    /* 0x05C */ f32 u05C;
    /* 0x060 */ s16 u060;
    /* 0x062 */ s16 u062;
    /* 0x064 */ f32 u064;
    /* 0x068 */ f32 u068;
    /* 0x06C */ f32 u06C;
    /* 0x070 */ f32 u070;
    /* 0x074 */ f32 u074;
    /* 0x078 */ f32 u078;
    /* 0x07C */ f32 u07C;
    /* 0x080 */ f32 u080;
    /* 0x084 */ f32 u084;
    /* 0x088 */ f32 u088;
    /* 0x08C */ s16 u08C;
    /* 0x08E */ s16 u08E;
    /* 0x090 */ f32 u090;
    /* 0x094 */ u8 u094;
    /* 0x095 */ u8 u095;
    /* 0x096 */ u8 pad096[2];
    /* 0x098 */ f32 u098;
    /* 0x09C */ f32 u09C;
    /* 0x0A0 */ f32 u0A0;
    /* 0x0A4 */ f32 u0A4;
    /* 0x0A8 */ f32 u0A8;
    /* 0x0AC */ f32 u0AC;
    /* 0x0B0 */ s32 u0B0;
    /* 0x0B4 */ s32 u0B4;
    /* 0x0B8 */ s16 u0B8;
    /* 0x0BA */ s16 u0BA;
    /* 0x0BC */ f32 u0BC;
    /* 0x0C0 */ f32 u0C0;
    /* 0x0C4 */ f32 u0C4;
    /* 0x0C8 */ f32 u0C8;
    /* 0x0CC */ f32 u0CC;
    /* 0x0D0 */ f32 u0D0;
    /* 0x0D4 */ f32 u0D4;
    /* 0x0D8 */ s16 u0D8;
    /* 0x0DA */ s16 u0DA;
    /* 0x0DC */ s16 u0DC;
    /* 0x0DE */ s16 u0DE;
    /* 0x0E0 */ f32 u0E0;
    /* 0x0E4 */ f32 u0E4;
    /* 0x0E8 */ f32 u0E8;
    /* 0x0EC */ f32 u0EC;
    /* 0x0F0 */ f32 u0F0;
    /* 0x0F4 */ s16 u0F4;
    /* 0x0F6 */ s16 u0F6;
    /* 0x0F8 */ s16 u0F8;
    /* 0x0FA */ s16 u0FA;
    /* 0x0FC */ f32 u0FC;
    /* 0x100 */ f32 u100;
    /* 0x104 */ f32 u104;
    /* 0x108 */ f32 u108;
    /* 0x10C */ f32 u10C;
    /* 0x110 */ f32 u110;
    /* 0x114 */ f32 u114;
    /* 0x118 */ s16 u118;
    /* 0x11A */ s16 u11A;
} EmitterSpec981E0;
u8 *spec_emitter_spawn(s32 arg0, u8 *spec, u8 arg2, s32 arg3);
#endif

#ifdef NON_MATCHING
// player_emitter_spawn_c: player action handler (void (s32), argument unused): spawns the kind-0xC emitter on the
// player D_800D154C (node byte its +0x3B) through spec_emitter_spawn (no extra data, layer 0xFF, owner 0) with a constant
// spec (all fields set except padding, as the asm fills them).
/* was func_1506F1A8 */
void objfx_emitter_c(s32 arg0) {
    EmitterSpec981E0 spec;

    spec.u000 = 0xF;
    spec.u004 = (u8 *) D_800D154C;
    spec.u008 = ((u8 *) D_800D154C)[0x3B];
    spec.u009 = 0xC;
    spec.u00C = 0.0f;
    spec.u010 = 0.0f;
    spec.u014 = 80.0f;
    spec.u018 = 0.0f;
    spec.u01C = 0.0f;
    spec.u020 = 102.0f;
    spec.u024 = 0.1223f;
    spec.u028 = 0.6f;
    spec.u02C = 1200.0f;
    spec.u030 = 26.0f;
    spec.u034 = 4.8f;
    spec.u038 = -1;
    spec.u039 = 2;
    spec.u03A = -1;
    spec.u03B = 0;
    spec.u03C = 0;
    spec.u03D = 0;
    spec.u03E = 0xC8;
    spec.u040 = 0.656f;
    spec.u044 = -187.0f;
    spec.u048 = 4.64f;
    spec.u04C = 0xFF;
    spec.u050 = 0x3C;
    spec.u051 = 0xFF;
    spec.u052 = 0xEB;
    spec.u053 = 0x52;
    spec.u054 = 1;
    spec.u058 = 0.00502f;
    spec.u05C = 0.003f;
    spec.u060 = 0x1E;
    spec.u062 = 0xF;
    spec.u064 = 0.606f;
    spec.u068 = 0.23900001f;
    spec.u06C = 0.418f;
    spec.u070 = 0.20500001f;
    spec.u074 = 1.177f;
    spec.u078 = 0.572f;
    spec.u07C = 0.81900007f;
    spec.u080 = 0.846f;
    spec.u084 = 0.94086f;
    spec.u088 = 0.942411f;
    spec.u08C = 0xC;
    spec.u08E = 0x15;
    spec.u090 = 0.39200002f;
    spec.u094 = 0x50;
    spec.u095 = 0x78;
    spec.u098 = 0.008f;
    spec.u09C = 0.0f;
    spec.u0A0 = 5.0f;
    spec.u0A4 = 100.0f;
    spec.u0A8 = 0.24900001f;
    spec.u0AC = 0.35200003f;
    spec.u0B0 = 4;
    spec.u0B4 = 2;
    spec.u0B8 = 0x1E;
    spec.u0BA = 0x11;
    spec.u0BC = 14.0f;
    spec.u0C0 = 9.0f;
    spec.u0C4 = 0.5f;
    spec.u0C8 = 0.5f;
    spec.u0CC = 25.0f;
    spec.u0D0 = 0.44000003f;
    spec.u0D4 = 0.45100003f;
    spec.u0D8 = 0x50;
    spec.u0DA = 0x78;
    spec.u0DC = 0x10;
    spec.u0DE = 0xF;
    spec.u0E0 = 0.0f;
    spec.u0E4 = 5.0f;
    spec.u0E8 = 100.0f;
    spec.u0EC = 0.30900002f;
    spec.u0F0 = 0.312f;
    spec.u0F4 = 0x28;
    spec.u0F6 = 0xF;
    spec.u0F8 = 0x50;
    spec.u0FA = 0x50;
    spec.u0FC = 402.0f;
    spec.u100 = 303.0f;
    spec.u104 = 0.101f;
    spec.u108 = 0.19800001f;
    spec.u10C = 45.0f;
    spec.u110 = -0.65500003f;
    spec.u114 = 0.30800003f;
    spec.u118 = 0x14;
    spec.u11A = 0xC;
    spec_emitter_spawn(0, (u8 *) &spec, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objfx_emitter_c.s")
#endif

/* was func_1506F524 */
void objfx_197a7c(s32 arg0) {
    emitter_stop_for_obj(D_800D154C);
}

#ifdef NON_MATCHING
// player_emitter_spawn_d: player action handler (void (s32), argument unused): as objfx_emitter_c with the kind-0xD
// spec (trail colour 3C FF EB 52).
/* was func_1506F54C */
void objfx_emitter_d(s32 arg0) {
    EmitterSpec981E0 spec;

    spec.u000 = 0xF;
    spec.u004 = (u8 *) D_800D154C;
    spec.u008 = ((u8 *) D_800D154C)[0x3B];
    spec.u009 = 0xD;
    spec.u00C = 22.0f;
    spec.u010 = 22.0f;
    spec.u014 = 165.0f;
    spec.u018 = 22.0f;
    spec.u01C = 22.0f;
    spec.u020 = 193.0f;
    spec.u024 = 1.138f;
    spec.u028 = 0.795f;
    spec.u02C = 370.0f;
    spec.u030 = 17.800001f;
    spec.u034 = 4.9f;
    spec.u038 = 0;
    spec.u039 = 0xFF;
    spec.u03A = 0;
    spec.u03B = 0;
    spec.u03C = 0;
    spec.u03D = 0;
    spec.u03E = 0x9F;
    spec.u040 = 0.615f;
    spec.u044 = -191.0f;
    spec.u048 = 7.85f;
    spec.u04C = 0xFF;
    spec.u050 = 0x3C;
    spec.u051 = 0xFF;
    spec.u052 = 0xEB;
    spec.u053 = 0x52;
    spec.u054 = 1;
    spec.u058 = 0.0029f;
    spec.u05C = 0.00235f;
    spec.u060 = 0x23;
    spec.u062 = 0xA;
    spec.u064 = 0.80200005f;
    spec.u068 = 0.58900005f;
    spec.u06C = 0.367f;
    spec.u070 = 0.307f;
    spec.u074 = 0.614f;
    spec.u078 = 0.29900002f;
    spec.u07C = 0.0f;
    spec.u080 = 0.73800004f;
    spec.u084 = 0.962646f;
    spec.u088 = 0.961868f;
    spec.u08C = 0xF;
    spec.u08E = 0x11;
    spec.u090 = 0.36900002f;
    spec.u094 = 0x50;
    spec.u095 = 0x50;
    spec.u098 = 0.024f;
    spec.u09C = 22.0f;
    spec.u0A0 = 58.0f;
    spec.u0A4 = 212.0f;
    spec.u0A8 = 0.2f;
    spec.u0AC = 0.105000004f;
    spec.u0B0 = 3;
    spec.u0B4 = 2;
    spec.u0B8 = 0x19;
    spec.u0BA = 0xA;
    spec.u0BC = 6.0f;
    spec.u0C0 = 10.0f;
    spec.u0C4 = 0.3f;
    spec.u0C8 = 0.2f;
    spec.u0CC = 37.0f;
    spec.u0D0 = 0.75100005f;
    spec.u0D4 = 0.32200003f;
    spec.u0D8 = 0x50;
    spec.u0DA = 0x50;
    spec.u0DC = 0xF;
    spec.u0DE = 0x11;
    spec.u0E0 = 22.0f;
    spec.u0E4 = 130.0f;
    spec.u0E8 = 306.0f;
    spec.u0EC = 0.208f;
    spec.u0F0 = 0.193f;
    spec.u0F4 = 0x23;
    spec.u0F6 = 0xF;
    spec.u0F8 = 0x50;
    spec.u0FA = 0x64;
    spec.u0FC = 198.0f;
    spec.u100 = 102.0f;
    spec.u104 = 0.040000003f;
    spec.u108 = 0.040000003f;
    spec.u10C = 89.0f;
    spec.u110 = -0.49500003f;
    spec.u114 = 0.44300002f;
    spec.u118 = 0xF;
    spec.u11A = 0x11;
    spec_emitter_spawn(0, (u8 *) &spec, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objfx_emitter_d.s")
#endif

/* was func_1506F8C0 */
void objfx_19ef70(s32 arg0) {
    objfx_nop_1519ef70(D_800D154C, 0, 0);
}

/* was func_1506F8F0 */
void objfx_arc_a(s32 arg0) {
    struct127* a0;
    beam_effect_spawn_attached_ex(a0 = D_800D154C, a0->unique_id, 0x14, -1, 482.0f, -127.0f, -45.0f, 659.0f, -211.0f, -114.0f, 3, 3, 5, 20.0f, (random_float() * 10.0f) + 40.0f, 0, 0.0f);
}

/* was func_1506F9C0 */
void objfx_arc_b(s32 arg0) {
    struct127* a0;
    beam_effect_spawn_attached_ex(a0 = D_800D154C, a0->unique_id, 0x14, -1, 241.0f, -127.0f, -45.0f, 418.0f, -211.0f, -114.0f, 3, 3, 5, 20.0f, (random_float() * 10.0f) + 40.0f, 0, 0.0f);
}

/* was func_1506FA90 */
void objfx_arc_c(s32 arg0) {
    struct127* a0;
    beam_effect_spawn_attached_ex(a0 = D_800D154C, a0->unique_id, 0x1A, -1, -181.0f, -218.0f, -1.0f, -681.0f, -584.0f, -2.0f, 3, 3, 5, 20.0f, (random_float() * 10.0f) + 40.0f, 0, 0.0f);
}

/* was func_1506FB60 */
void objfx_gun_shot(s32 arg0) {
    if (held_obj_byte7d_get() != 0) {
        object_muzzle_fire(D_800D154C, (arg0 - 0x13) & 0xFF, 0xFF, 0);
    } else {
        object_gun_fire(D_800D154C, (arg0 - 0x13) & 0xFF, 0, 0, -1, 0xFF, 0);
    }
}

/* was func_1506FBE8 */
void objfx_1a0a10_70(s32 arg0) {
    ground_dust_spawn(D_800D154C, 0x46, 0xFF, 0);
}

/* was func_1506FC1C */
void objfx_1a0a10_40(s32 arg0) {
    ground_dust_spawn(D_800D154C, 0x28, 0xFF, 0);
}

/* was func_1506FC50 */
void objfx_buddy_marker_clear(s32 arg0) {
    buddy_marker_clear_all();
}

/* was func_1506FC74 */
void objfx_buddy_marker_create(s32 arg0) {
    buddy_marker_create(D_800D154C);
}

/* was func_1506FC9C */
void objfx_b3ab0(s32 arg0) {
    obj_joint_blast_fx(D_800D154C, 0xFF);
}

/* was func_1506FCC8 */
void objfx_emitter_kind6(s32 arg0) {
    object_emitter_spawn((u8 *) D_800D154C, 6, 0xFF, 0);
}

/* was func_1506FCFC */
void objfx_emitter_kind5(s32 arg0) {
    object_emitter_spawn((u8 *) D_800D154C, 5, 0xFF, 0);
}

/* was func_1506FD30 */
void objfx_arc_d(s32 arg0) {
    struct127* a0;
    beam_effect_spawn_attached_ex(a0 = D_800D154C, a0->unique_id, 1, -1, 0.0f, 0.0, 345.0f, 0.0f, 0.0, 414.0f, 3, 3, 5, 20.0f, (random_float() * 10.0f) + 40.0f, 1, 50.0f);
}

/* was func_1506FDF0 */
void objfx_1aabc4_0(s32 arg0) {
    footstep_splash(D_800D154C, 0);
}

/* was func_1506FE1C */
void objfx_1aabc4_1(s32 arg0) {
    footstep_splash(D_800D154C, 1);
}

/* was func_1506FE48 */
void objfx_1aabc4_0_b(s32 arg0) {
    footstep_splash(D_800D154C, 0);
}

/* was func_1506FE74 */
void objfx_1aabc4_1_b(s32 arg0) {
    footstep_splash(D_800D154C, 1);
}

/* was func_1506FEA0 */
void objfx_1aabc4_2(s32 arg0) {
    footstep_splash(D_800D154C, 2);
}

/* was func_1506FECC */
void objfx_1aabc4_3(s32 arg0) {
    footstep_splash(D_800D154C, 3);
}

/* was func_1506FEF8 */
void objfx_1ab920_0(s32 arg0) {
    char_handler_nop_b(D_800D154C, 0);
}

/* was func_1506FF24 */
void objfx_1ab920_1(s32 arg0) {
    char_handler_nop_b(D_800D154C, 1);
}

/* was func_1506FF50 */
void objfx_1ab930(s32 arg0) {
    char_state_fx_start(D_800D154C);
}

/* was func_1506FF78 */
void objfx_cbf80_0(s32 arg0) {
    ground_puff_spawn(D_800D154C, 0, 1, 0xFF);
}

/* was func_1506FFAC */
void objfx_cbf80_1(s32 arg0) {
    ground_puff_spawn(D_800D154C, 1, 1, 0xFF);
}

/* was func_1506FFE0 */
void objfx_cbf80_2(s32 arg0) {
    ground_puff_spawn(D_800D154C, 2, 1, 0xFF);
}

/* was func_15070014 */
void objfx_ca150(s32 arg0) {
    landing_dust_burst((u8 *) D_800D154C);
}

/* was func_1507003C */
void objfx_1b01b8_1b09bc(s32 arg0) {
    object_hit_flash_spawn(D_800D154C, 0);
    object_link_effect_spawn(D_800D154C, 0, 0x3E8, 0xFF, 0);
}

/* was func_15070084 */
void objfx_1aeca0(s32 arg0) {
    ground_burst_spawn(D_800D154C, 0xFF, 1);
}

/* was func_150700B4 */
void objfx_1b03b8(s32 arg0) {
    ground_burst_spawn_b(D_800D154C, 0xFF, 1);
}

/* was func_150700E4 */
void objfx_193660(s32 arg0) {
    obj_head_particle_burst(D_800D154C, 0xFF, 1);
}

/* was func_15070114 */
void objfx_1937f4(s32 arg0) {
    obj_bone_debris_emitter_attach(D_800D154C, 0xFF, 1);
}

/* was func_15070144 */
void objfx_shot_self(s32 arg0) {
    struct198 tmp;
    s32 tmp0;

    tmp.unk0 = 1;
    tmp.unk8 = 0;
    tmp.unkC = 0;
    tmp.unk4 = D_800D154C;

    if (D_800BE9F0 == 0x2B) {
        tmp0 = 3;
    } else {
        tmp0 = 0;
    }
    projectile_fire(D_800D154C, 0, &tmp, tmp0 & 0xFF, 0xFF, 1);
    obj_rider_cam_shake(D_800D154C);
}

/* was func_150701C4 */
void objfx_1c5280(s32 arg0) {
    gun_muzzle_smoke_spawn(D_800D154C, 0xFF, 1);
}

/* was func_150701F4 */
void objfx_1c9740(s32 arg0) {
    object_explode_big(D_800D154C, 0xFF, 1);
}

/* was func_15070224 */
void objfx_debris_burst(s32 arg0) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (random_int() % 5U) + 4;
    header.unk4 = 0;
    header2.unk0 = D_800D154C->x_position;
    header2.unk4 = D_800D154C->y_position;
    header2.unk8 = D_800D154C->z_position;
    light_create_with_ctrl(&header, &header2, (random_int() % 3U) + 4, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
}
#ifdef NON_MATCHING
void objev_player_camera_view(void); // P259: reads D_800D154C itself (the asm ignores a0 / a1)
struct127 *player_find_owned_object(struct127 *, struct127 *, s32);
void mtx_transform_points(f32 **, f32 **, void *, s32);
void muzzle_flash_light_spawn(u8 *, u8, s32);
extern s32 D_800E0FFE;

/* was func_15070300 */
void objfx_gun_fire(s32 arg0) {
    struct {
        f32 * u58;
        u8 * u5C;
        f32 u60;
        u8 pad64[0x8];
        f32 u6C;
        f32 u70;
        s32 u74;
        u8 pad78[0x8];
        u8 u80;
        u8 pad81[0xB];
        s32 u8C;
        struct127 * u90;
        struct127 * u94;
        struct127 * u98;
        u8 pad9C[0x4];
        struct127 * uA0;
        u8 padA4[0x3];
        u8 uA7;
        struct127 * uA8;
        u8 padAC[0x3];
        u8 uAF;
    } sp;
    s32 sp50;
    s32 sp4C;
    s32 *temp_t4;
    s32 *temp_t8;
    f32 temp_f18;
    s32 temp_t7;
    s8 temp_v1;
    struct126 *temp_v0_3;
    struct127 *temp_v0_2;
    u8 temp_v0;
    u8 var_a1;
    u8 var_a3;
    u8 var_a3_2;

    sp.uA0 = NULL;
    temp_v0 = D_800D154C->id;
    var_a3 = 1;
    if (temp_v0 == 0x77) {
        temp_t7 = ((s32) (D_800D154C - D_800CC2D0) / 812) & 0xFF;
        sp.uA8 = D_800D154C;
        if ((temp_t7 < 2) && (temp_v1 = *((s8 *)&D_800E0FFE + temp_t7), var_a1 = 1, (temp_v1 != 0))) {
            sp.uA0 = &D_800CC2D0[temp_v1];
        } else {
            var_a1 = 0;
            if (sp.uA8->unk31C->unk197 != 0) {
                var_a1 = 1;
            }
        }
        goto block_10;
    }
    if (temp_v0 == 0x28) {
        temp_v0_2 = player_find_owned_object(D_800D154C, D_800CC2D0, 1);
        sp.uA8 = temp_v0_2;
        var_a3 = 0;
        var_a1 = 0;
        if (temp_v0_2->unk31C->unk197 != 0) {
            var_a1 = 1;
        }
block_10:
        sp.uAF = var_a1;
        sp.uA7 = var_a3;
        obj_rider_cam_shake(sp.uA8);
        var_a3_2 = var_a3;
        if (sp.uA0 != NULL) {
            sp.uAF = var_a1;
            sp.uA7 = var_a3_2;
            obj_rider_cam_shake(sp.uA0);
        }
        if (D_800BE616 != 0) {
            if (D_800D154C->unk31C->unk128 & 0x10) {
                D_800D1580 = 0xA;
                temp_v0_3 = D_800D154C->unk31C;
                var_a3_2 = 2;
                (*(u16 *)((u8 *)temp_v0_3 + 0x12C)) = (u16) ((*(u16 *)((u8 *)temp_v0_3 + 0x12C)) - 1);
            } else {
                D_800D1580 = 9;
            }
        } else {
            D_800D1580 = 5;
        }
        if (var_a1 != 0) {
            sp.u8C = 3;
            sp.u90 = sp.uA8;
            sp.u94 = sp.uA0;
            sp.u98 = D_800D154C;
            projectile_fire(sp.uA8, sp.uA0, &sp.u8C, var_a3_2, 0xFF, 1);
        } else {
            objev_player_camera_view();
        }
        if (D_800D154C->unk1D4 != NULL) {
            temp_t4 = ((u8 *)&D_eu_80099F30);
            if ((D_800D154C->unk74 & 0xF) != 0xF) {
                temp_t8 = ((u8 *)&D_80099F3C);
                (*(s32 *)((u8 *)(&sp.u80) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
                (*(s32 *)((u8 *)(&sp.u80) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
                (*(s32 *)((u8 *)(&sp.u80) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
                (*(s32 *)((u8 *)(&sp.u74) + 0)) = (*(s32 *)((u8 *)temp_t8 + 0));
                (*(s32 *)((u8 *)(&sp.u74) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
                (*(s32 *)((u8 *)(&sp.u74) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
                sp.u6C = (random_float() * 30.0f) + 40.0f;
                temp_f18 = random_float() * 2.512f;
                sp.u5C = &sp.u80;
                sp.u58 = &sp.u60;
                sp.u70 = temp_f18 + 3.5900002f;
                mtx_transform_points(&sp.u5C, &sp.u58, &D_800D154C->unk1D4->pad0[0x100], 1);
                sp4C = random_int();
                sp50 = random_int();
                attached_particle_spawn((u8 *)D_800D154C, 4U, (f32 *)&sp.u80, (f32 *)&sp.u74, &sp.u6C, ((u32) sp4C % 5U) + 5, ((u32) sp50 % 56U) + 0xC8, (random_float() * 510.0f) + 1296.0f, (u8 *)&sp.u60, 0xFF, 0, -1, 0xFF, 1);
                muzzle_flash_light_spawn(&sp.u60, 0xFF, 1);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objfx_gun_fire.s")
#endif
/* was func_15070690 */
void objfx_eee00(s32 arg0) {
    tether_start_with_flash(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}

/* was func_150706C4 */
void objfx_eef40(s32 arg0) {
    tether_stop(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}

/* was func_150706F8 */
void objfx_f03f8_both(s32 arg0) {
    if ((D_800D154C->unk94 & 0x10) == 0) {
        obj_arm_tracer_fire(D_800D154C, 0, 0xFF, 1);
    }
    if ((D_800D154C->unk94 & 8) == 0) {
        obj_arm_tracer_fire(D_800D154C, 1, 0xFF, 1);
    }
}

/* was func_15070760 */
void objfx_ebec0_0(s32 arg0) {
    gun_barrel_fire(D_800D154C, 0, 0xFF, 1);
}

/* was func_15070794 */
void objfx_ebec0_1(s32 arg0) {
    gun_barrel_fire(D_800D154C, 1, 0xFF, 1);
}

/* was func_150707C8 */
void objfx_fdda0(s32 arg0) {
    weapon_a_fire(D_800D154C, 0xFF, 1);
}

/* was func_150707F8 */
void objfx_fdf38(s32 arg0) {
    weapon_a_muzzle_effects(D_800D154C, 0xFF, 1, 0, 0);
}

/* was func_15070830 */
void objfx_fe320(s32 arg0) {
    weapon_b_fire(D_800D154C, 0xFF, 1);
}

/* was func_15070860 */
void objfx_fe49c(s32 arg0) {
    weapon_b_muzzle_effects(D_800D154C, 0xFF, 1, 0, 0);
}

#ifdef NON_MATCHING
// player_emitter_spawn_9: player action handler (void (s32), argument unused): as objfx_emitter_c with the kind-9
// spec (spec flags 0x11).
/* was func_15070898 */
void objfx_emitter_9(s32 arg0) {
    EmitterSpec981E0 spec;

    spec.u000 = 0xF;
    spec.u004 = (u8 *) D_800D154C;
    spec.u008 = ((u8 *) D_800D154C)[0x3B];
    spec.u009 = 9;
    spec.u00C = -4.734001f;
    spec.u010 = -111.957596f;
    spec.u014 = 33.473396f;
    spec.u018 = -8.837997f;
    spec.u01C = -159.75f;
    spec.u020 = 33.473396f;
    spec.u024 = 0.278f;
    spec.u028 = 0.82800007f;
    spec.u02C = 312.0f;
    spec.u030 = 7.1f;
    spec.u034 = 5.0f;
    spec.u038 = -1;
    spec.u039 = 1;
    spec.u03A = -1;
    spec.u03B = -1;
    spec.u03C = 0xFF;
    spec.u03D = 0xFF;
    spec.u03E = 0xB4;
    spec.u040 = 0.325f;
    spec.u044 = -232.0f;
    spec.u048 = 9.07f;
    spec.u04C = 0xFF;
    spec.u050 = 0x3C;
    spec.u051 = 0xFF;
    spec.u052 = 0xEB;
    spec.u053 = 0x52;
    spec.u054 = 0x11;
    spec.u058 = 0.00689f;
    spec.u05C = 0.01038f;
    spec.u060 = 0x19;
    spec.u062 = 0xA;
    spec.u064 = 0.367f;
    spec.u068 = 0.35000002f;
    spec.u06C = 0.256f;
    spec.u070 = 0.20500001f;
    spec.u074 = 0.776f;
    spec.u078 = 0.81100005f;
    spec.u07C = 0.125f;
    spec.u080 = 1.3110001f;
    spec.u084 = 0.935119f;
    spec.u088 = 0.943452f;
    spec.u08C = 0xC;
    spec.u08E = 0x15;
    spec.u090 = 0.307f;
    spec.u094 = 0x50;
    spec.u095 = 0x50;
    spec.u098 = 0.002f;
    spec.u09C = -8.837997f;
    spec.u0A0 = -159.75f;
    spec.u0A4 = 33.473396f;
    spec.u0A8 = 0.3f;
    spec.u0AC = 0.40100002f;
    spec.u0B0 = 4;
    spec.u0B4 = 2;
    spec.u0B8 = 0x1A;
    spec.u0BA = 0x10;
    spec.u0BC = 6.0f;
    spec.u0C0 = 5.0f;
    spec.u0C4 = 0.3f;
    spec.u0C8 = 0.3f;
    spec.u0CC = 50.0f;
    spec.u0D0 = 0.0f;
    spec.u0D4 = 0.712f;
    spec.u0D8 = 0x50;
    spec.u0DA = 0x78;
    spec.u0DC = 0xF;
    spec.u0DE = 0x11;
    spec.u0E0 = -8.837997f;
    spec.u0E4 = -159.75f;
    spec.u0E8 = 33.473396f;
    spec.u0EC = 0.20400001f;
    spec.u0F0 = 0.504f;
    spec.u0F4 = 0x1E;
    spec.u0F6 = 0xF;
    spec.u0F8 = 0x50;
    spec.u0FA = 0x50;
    spec.u0FC = 140.0f;
    spec.u100 = 182.0f;
    spec.u104 = 0.16000001f;
    spec.u108 = 0.113000005f;
    spec.u10C = 42.0f;
    spec.u110 = -0.518f;
    spec.u114 = 0.37600002f;
    spec.u118 = 0xA;
    spec.u11A = 0x19;
    spec_emitter_spawn(0, (u8 *) &spec, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objfx_emitter_9.s")
#endif

/* was func_15070C18 */
void objfx_199834(s32 arg0) {
    spec_emitter_stop_for_obj(D_800D154C);
}

/* was func_15070C40 */
void objfx_hit_at_self(u8 arg0) {
    f32 sp34[3];
    struct127 *var_a0;

    sp34[0] = D_800D154C->x_position;
    sp34[1] = D_800D154C->y_position;
    sp34[2] = D_800D154C->z_position;
    if (D_800D154C->unk124 != 0) {
        var_a0 = &D_800CC2D0[D_800D154C->unk124 - 1];
    } else {
        var_a0 = D_800D154C;
    }
    ground_explosion(var_a0, D_800D154C, sp34, arg0, 0, 0xFF, 0);
}
// NON-MATCHING: missing a move and a branch
// void func_15103E40(s32, s32, s32, u8, u8, u8, u8);
// void objfx_hit_at_self(u8 arg0) {
//     struct17 tmp;
//     struct127 *temp_a1;
//     struct127 *phi_a0;
//
//     phi_a0 = temp_a1 = D_800D154C;
//     tmp.unk0 = temp_a1->x_position;
//     tmp.unk4 = temp_a1->y_position;
//     tmp.unk8 = temp_a1->z_position;
//
//     if (temp_a1->unk124) {
//         phi_a0 = &D_800CC2D0[temp_a1->unk124 - 1];
//         func_15103E40(phi_a0, temp_a1, &tmp, arg0, 0, 0xFF, 0);
//     }
// }

/* was func_15070CDC */
void objfx_hit_at_self_1(s32 arg0) {
    objfx_hit_at_self(1);
}

/* was func_15070D00 */
void objfx_hit_at_self_0(s32 arg0) {
    objfx_hit_at_self(0);
}

#ifndef NON_MATCHING /* P262: the NM build uses the exact prototype hoisted at the top */
s32 attached_particle_spawn(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
#endif
extern struct17 D_80099F48;
extern struct17 D_80099F54;

/* was func_15070D24 */
void objfx_sparks_joint1(s32 arg0) {
    struct17 a;
    struct17 b;
    f32 f[2];
    f32 pos[3];
    Header header;
    Header2 header2;

    a = D_80099F48;
    b = D_80099F54;
    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        f[0] = (random_float() * 101.0f) + 151.0f;
        f[1] = (random_float() * 4.0f) + 4.0f;
        mtx_transform_point_or_origin(&a, pos, (u8 *)D_800D154C->unk1D4 + 0x40);
        attached_particle_spawn((u8 *)D_800D154C, 1, (f32 *)&a, (f32 *)&b, f, (random_int() % 6U) + 5, (random_int() % 156U) + 0x64, (random_float() * 2496.0f) + 3496.0f, (u8 *)pos, 0xFF, 0, -1, 0xFF, 0);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (random_int() % 6U) + 0xA;
        header.unk4 = 0;
        header2.unk0 = pos[0];
        header2.unk4 = pos[1];
        header2.unk8 = pos[2];
        light_create_with_ctrl(&header, &header2, (random_int() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
    }
}
void cam_shake_all_players(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
extern struct17 D_80099F60;
extern struct17 D_80099F6C;

/* was func_15070F60 */
void objfx_sparks_shake(u8 arg0) {
    struct17 a;
    struct17 b;
    f32 f[2];
    f32 pos[3];
    Header header;
    Header2 header2;

    a = D_80099F60;
    b = D_80099F6C;
    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        f[0] = (random_float() * 180.0f) + 150.0f;
        f[1] = (random_float() * 2.0f) + 2.5f;
        mtx_transform_point_or_origin(&a, pos, (u8 *)D_800D154C->unk1D4 + ((arg0 ? 1 : 2) << 6));
        attached_particle_spawn((u8 *)D_800D154C, arg0 ? 1 : 2, (f32 *)&a, (f32 *)&b, f, (random_int() % 5U) + 5, (random_int() % 156U) + 0x64, (random_float() * 4000.0f) + 4000.0f, (u8 *)pos, 0xFF, 0, -1, 0xFF, 0);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (random_int() % 5U) + 3;
        header.unk4 = 0;
        header2.unk0 = pos[0];
        header2.unk4 = pos[1];
        header2.unk8 = pos[2];
        light_create_with_ctrl(&header, &header2, (random_int() % 201U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
        rumble_all_players_at((struct17 *)pos, 506.0f, 1013.0f, 0.0009871668880805373f, 0xF, 0x14, 0xFF, 0);
        cam_shake_all_players((s32)pos, 506.0f, 1013.0f, 0.0009871668880805373f, 5, 0xFF, 0);
    }
}
/* was func_15071230 */
void objfx_sparks_shake_2(s32 arg0) {
    objfx_sparks_shake(0);
}

/* was func_15071254 */
void objfx_sparks_shake_1(s32 arg0) {
    objfx_sparks_shake(1);
}

/* was func_15071278 */
void objfx_fc438(s32 arg0) {
    gunfire_burst_spawn(D_800D154C, 0, 1, D_800D154C->unk84.ub[1]);
}

/* was func_150712AC */
void objfx_fede0_cam_shake(s32 arg0) {
    structEU_151D8E18 sp18;

    character_smoke_puff(D_800D154C, 0xFF, 1);
    if (D_800D154C->camera != NULL) {
        sp18.unk0 = 1;
        sp18.unk2 = (random_int() % 7U) + 10;
        sp18.unk5 = 1 << D_800D154C->camera->unk23D;
        sp18.unk4 = (random_int() % 7U) + 2;
        sp18.unk6 = -1;
        rumble_request(&sp18, 0, 0xFF, 1);
    }
}
/* was func_15071360 */
void objfx_ff2b0_cam_shake(s32 arg0) {
    structEU_151D8E18 sp18;

    if (held_obj_byte7d_get() != 0) {
        object_beam_fire(D_800D154C, 0xFF, 1);
    } else {
        object_bolt_fire(D_800D154C, 0xFF, 1);
    }
    if (D_800D154C->camera != NULL) {
        sp18.unk0 = 1;
        sp18.unk2 = (random_int() % 5U) + 15;
        sp18.unk5 = 1 << D_800D154C->camera->unk23D;
        sp18.unk4 = (random_int() & 3) + 3;
        sp18.unk6 = -1;
        rumble_request(&sp18, 0, 0xFF, 1);
    }
}

/* was func_15071434 */
void objfx_ff840_1_0(s32 arg0) {
    weapon_c_fire(D_800D154C, 1, 0, 0xFF, 1);
}

/* was func_15071470 */
void objfx_ff840_0_0(s32 arg0) {
    weapon_c_fire(D_800D154C, 0, 0, 0xFF, 1);
}

/* was func_150714AC */
void objfx_ff840_0_1(s32 arg0) {
    weapon_c_fire(D_800D154C, 0, 1, 0xFF, 1);
}

/* was func_150714E8 */
void objfx_1d5714_a(s32 arg0) {
    bone_beam_spawn(D_800D154C, &D_800A2148, &D_800A2154, D_80088BB0, 1.0f, 0xFF, 1);
}

/* was func_15071544 */
void objfx_1d469c_4(s32 arg0) {
    obj_point_fx_broadcast_kill(D_800D154C);
    object_point_effect_spawn(D_800D154C, 4, 0x78, 0xFF, 1);
}

/* was func_1507158C */
void objfx_1d469c_2(s32 arg0) {
    obj_point_fx_broadcast_kill(D_800D154C);
    object_point_effect_spawn(D_800D154C, 2, 0x78, 0xFF, 1);
}

/* was func_150715D4 */
void objfx_1d469c_3(s32 arg0) {
    obj_point_fx_broadcast_kill(D_800D154C);
    object_point_effect_spawn(D_800D154C, 3, 0x78, 0xFF, 1);
}

/* was func_1507161C */
void objfx_nop_1507161c(s32 arg0) {

}

/* was func_15071628 */
void objfx_1d0058(s32 arg0) {
    obj_aura_fx_spawn(D_800D154C, (arg0 - 0x55) & 0xFF, 0xFF, 1);
}

/* was func_15071668 */
void objfx_1d0024(s32 arg0) {
    obj_fx_broadcast_kill(D_800D154C);
}

/* was func_15071690 */
void objfx_b5c38(s32 arg0) {
    struct127 *temp_a0;
    s32 pad0;
    s32 sp1C;

    temp_a0 = D_800D154C;
    if ((temp_a0->unk1D4 != 0) && ((temp_a0->unk74 & 0xF) != 0xF)) {
        obj_get_skel_point_down205(temp_a0, &sp1C);
        zap_burst_spawn(&sp1C, 0xFF, 1);
    }
}

/* was func_150716EC */
void objfx_shake_large(s32 arg0) {
    struct17 tmp;
    struct127 *temp_v0;

    temp_v0 = D_800D154C;
    tmp.unk0 = temp_v0->x_position;
    tmp.unk4 = temp_v0->y_position;
    tmp.unk8 = temp_v0->z_position;
    rumble_all_players_at(&tmp, 1502.0f, 3000.0f, 0.00033333332976326346f, 0xC, 0xF, 0xFF, 0);
}

/* was func_15071764 */
void objfx_kind18_activate(s32 arg0) {
    struct127 *sp34 = obj_find_by_setup_id(18);
    if (sp34 != NULL) {
        obj_glow_spawn(sp34);
        obj_trail_emitter_spawn(sp34);
        light_create_obj_follow(sp34, 1, 2, 300, 70, 255, 130, 0, 255, 1);
    }
}

/* was func_150717E0 */
void objfx_kind18_notify_43(s32 arg0) {
    struct {
        struct127 *unk0;
        u8 unk4;
    } sp20;
    struct127 *temp_v0;

    temp_v0 = obj_find_by_setup_id(0x12);
    if (temp_v0 != NULL) {
        sp20.unk0 = temp_v0;
        sp20.unk4 = temp_v0->unique_id;
        particle_broadcast((s32)&sp20, 0x43);
        effect_nodes_broadcast((s32)&sp20, 0x43);
    }
}
// void objfx_kind18_notify_43(s32 arg0) {
//     u8 sp24;
//     void *sp20;
//     void **sp18;
//     void **temp_a0;
//     void *temp_v0;
//
//     temp_v0 = obj_find_by_setup_id(0x12);
//     temp_a0 = &sp20;
//     if (temp_v0 != 0) {
//         sp20 = temp_v0;
//         sp18 = temp_a0;
//         sp24 = temp_v0->unk3B;
//         func_15131D4C(temp_a0, 0x43);
//         effect_nodes_broadcast(temp_a0, 0x43);
//     }
// }

/* was func_15071830 */
void objfx_f9bb0(s32 arg0) {
    aura_group_spawn(D_800D154C, 0xFF, 1);
}

/* was func_15071860 */
void objfx_19072c(s32 arg0) {
    object_effects_detach_all(D_800D154C);
}

/* was func_15071888 */
void objfx_1d5714_b(s32 arg0) {
    bone_beam_spawn(D_800D154C, &D_800A1FB0, &D_800A1FBC, D_80088B90, 0.7f, 0xFF, 1);
}

/* was func_150718E4 */
void objfx_1c384c_random_joint(s32 arg0) {
    f32 sp24[3];
    s32 sp20;

    sp20 = D_80099F78;
    if ((D_800D154C->unk1D4 != NULL) || ((D_800D154C->unk74 & 0xF) == 0xF)) {
        mtx_transform_point_or_origin(D_800A5860, sp24, (u8 *)D_800D154C->unk1D4 + (((u8 *)&sp20)[random_int() & 3] << 6));
        sp24[1] = D_800D154C->unk180 + 20.0f;
        fire_embers_spawn(sp24, 0xFF, 1);
    }
}

/* was func_15071998 */
void objfx_fa520_0(s32 arg0) {
    obj_point_burst_spawn(D_800D154C, 0, 0xFF, 1);
}

/* was func_150719CC */
void objfx_fa520_1(s32 arg0) {
    obj_point_burst_spawn(D_800D154C, 1, 0xFF, 1);
}

/* was func_15071A00 */
void objfx_fa520_2(s32 arg0) {
    obj_point_burst_spawn(D_800D154C, 2, 0xFF, 1);
}

/* was func_15071A34 */
void objfx_1d09a8(s32 arg0) {
    objfx_joint_flash_burst(D_800D154C, 0xFF, 1);
}

/* was func_15071A64 */
void objfx_1dc484_vs_player(s32 arg0) {
    f32 sp4C[3];
    f32 sp28[9];

    if (!(random_int() & 1) && (D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF) &&
        (D_800CC2D0[0].stunned != 0) && (D_800CC2D0[0].health > 0)) {
        hitinfo_from_obj_floor(sp28, D_800D154C);
        mtx_transform_point_or_origin(D_80099F7C, sp4C, (u8 *)D_800D154C->unk1D4 + 0x3C0);
        impact_blast_spawn_small(sp4C, sp28, 0, 0xFF, 1);
    }
}
void impact_blast_spawn_large(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4);
void emit_textured_burst(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7);
extern f32 D_80099F88[3][3];
extern u8 D_80099FAC[];
extern u8 D_80099FC4[];

/* was func_15071B18 */
void objfx_joint7_burst(s32 arg0) {
    struct17 pos;
    f32 m[9];
    struct {
        s32 u34;
        s32 u38;
        struct17 u3C;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
    } s;

    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        mtx_transform_point_or_origin(D_80099F88[random_int() % 3U], &pos, (u8 *)D_800D154C->unk1D4 + 0x1C0);
        hitinfo_from_obj_floor(m, D_800D154C);
        if (random_int() & 1) {
            if (random_int() & 1) {
                impact_blast_spawn_large(&pos, m, 0, 0xFF, 1);
            } else {
                impact_blast_spawn_small(&pos, m, 0, 0xFF, 1);
            }
        }
        if (random_int() & 1) {
            s32 blk; // fakematch: unused block-scoped local (s69 basic-block boundary) schedules the 10.0f stores

            s.u34 = 8;
            s.u38 = 5;
            s.u3C = pos;
            s.u48 = 0;
            s.u4A = 0xFF;
            s.u4C = -0x40;
            s.u4E = 0x3C;
            s.u50 = 10.0f;
            s.u54 = 10.0f;
            s.u60 = 0x19;
            s.u62 = 0x14;
            s.u58 = -0.97800004f;
            s.u5C = 0.263f;
            s.u64 = 0.096f;
            s.u68 = 0.07f;
            s.u6C = 21.892f;
            emit_textured_burst(&s, D_80099FAC, D_80099FC4, 6, 25.0f, 0, 0xFF, 1);
        }
    }
}

/* was func_15071D08 */
void objfx_f2230(s32 arg0) {
    obj_bone_smoke_puff(D_800D154C, 0xFF, 1);
}

/* was func_15071D38 */
void objev_run_action(void) {
    void (*func)(s32);

    func = D_80086150[D_800D1580];
    if (func != 0) {
        func(D_800D1580);
    }
}

/* was func_15071D78 */
void objev_run_action_on_child(void) {
    struct127 *tmp;
    struct127 *orig;

    tmp = obj_find_child(D_800D154C);
    if (tmp != NULL) {
        orig = D_800D154C;
        D_800D154C = tmp;
        objev_run_action();
        D_800D154C = orig;
    }
}

/* was func_15071DC8 */
void objev_141a7c(void) {
    obj_interaction_update(D_800D154C, D_800D1580);
}

/* was func_15071DF4 */
void objev_192800(void) {
    obj_surface_handler_dispatch(D_800D154C, D_800D1580);
}

/* was func_15071E20 */
void objev_set_247(void) {
    D_800D154C->unk247 = (s8) D_800D1580;
}

/* was func_15071E3C */
void objev_set_248(void) {
    D_800D154C->unk248 = (s8) D_800D1580;
}

/* was func_15071E58 */
void objev_anim_at_frame(void) {
    D_800D1878 = D_800D1580 & 0xFF;
    D_800D154C->unk244 = (D_800D1580 >> 8) & 0xFF;
    obj_start_anim(D_800D154C, D_800D154C->unk244, 1.2000000476837158f, 3.0f, D_800D1878, 0.0f, 0);
}

/* was func_15071ED4 */
void objev_anim_59(void) {
    obj_start_anim(D_800D154C, 0x59, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

/* was func_15071F14 */
void objev_anim_24(void) {
    obj_start_anim(D_800D154C, 0x24, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

/* was func_15071F54 */
void objev_7c8e0(void) {
    player_set_respawn_wait(D_800D154C, D_800D1580);
}

/* was func_15071F80 */
void objev_skip_if_cutscene(void) {
    if (D_800C35EA == 1) {
        D_800D154C->unk138++;
    }
}

/* was func_15071FB0 */
void objev_clear_10c_grounded(void) {
    if (D_800D154C->unk28 == 0.0f) {
        D_800D154C->unk10C = (u16)0;
    }
}

#ifdef NON_MATCHING
extern f32 D_8009A308;
extern f32 D_800CC710;
extern f32 D_800CC714;
extern u16 D_800CC766;
extern s8 D_800CC771;
extern f32 D_800CC8BC;
extern u8 D_800CC964;
extern u8 *D_800CCA08;

/* was func_15071FDC */
void objev_player_react_anim(void) {
    struct127 *var_v1;
    s32 var_v0;
    s32 var_t1;
    s32 var_t0;
    s32 var_a2;
    s32 sp2C;

    var_t1 = 1;
    var_t0 = 0x194;
    if (D_800D1580 == 0) {
        var_a2 = -1;
        var_v1 = D_800CC2D0;
        var_v0 = 0;
loop_2:
        if ((D_800C3E78 + 1) == var_v1->unk65) {
            var_a2 = var_v0;
        } else {
            var_v0 += 1;
            var_v1 = (struct127 *)((u8 *)var_v1 + (0x32C));
            if (var_v0 != 0x19) {
                goto loop_2;
            }
        }
        if ((var_a2 + 1) == D_800CC964) {
            D_800CC766 = D_800D154C->unk76 + 0x8000;
            D_800CC8BC = D_8009A308;
            goto block_13;
        }
    } else {
        if (D_800D154C->unk2E8 >= 0x71) {
            var_t0 = 0x2E5;
            (*(f32 *)((u8 *)D_800D154C + 0x2E0)) = 0.0f;
        } else {
            var_t0 = 0x32;
            D_800CC766 = D_800D154C->unk76;
            var_t1 = 0;
            if (D_800D154C->unk251 != 0) {
                D_800CC8BC = *D_800CC2E8 + 800.0f;
            }
        }
        D_800D154C->unk2E4 = 0x32;
block_13:
        D_800CC710 = (*(f32 *)((u8 *)D_800D154C + 0x2D8));
        D_800CC714 = (*(f32 *)((u8 *)D_800D154C + 0x2DC));
        sp2C = var_t1;
        *D_800CC30C = (*(f32 *)((u8 *)D_800D154C + 0x2E0));
        D_800CC771 = 1;
        obj_start_anim(D_800CC2D0, var_t0 & 0xFFFF, 1.0f, 2.0f, 6.0f, 0.0f, 0);
        (*(s8 *)((u8 *)D_800CCA0C + 0x31)) = (s8) sp2C;
        if (D_800CCA08 != NULL) {
            (*(s32 *)((u8 *)D_800CCA08 + 0x5F0)) = (s32) ((*(s32 *)((u8 *)D_800CCA08 + 0x5F0)) | 0x400);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_player_react_anim.s")
#endif
/* was func_150721A4 */
void objev_fade_cmd(void)
{
  int new_var2;
  int new_var;
  new_var = D_800D1580 & 0xFF;
  new_var2 = (((s32) D_800D1580) >> 8) & 0xFF;
  obj_fade_command(D_800D154C, (((s32) D_800D1580) >> 0x10) & 0xFF, new_var, new_var2, 0);
}

/* was func_150721E8 */
struct127 *obj_find_child(struct127 *arg0) {
    return obj_find_child_nth(arg0, 0);
}

/* was func_15072208 */
struct127 *obj_find_child_nth(struct127 *arg0, s32 arg1) {
    s32 id = (arg0 - D_800CC2D0) + 1;
    s32 count = 0;
    s32 i;

    for (i = 0; i < 25; i++) {
        if (id == D_800CC2D0[i].unk65) {
            if (count == arg1) {
                return &D_800CC2D0[i];
            }
            count++;
        }
    }
    return NULL;
}

/* was func_150722F0 */
void objev_child_fade(void) {
    struct127 *temp_v0 = obj_find_child(D_800D154C);
    if (temp_v0 != 0) {
        s32 tmp0 = D_800D1580 >> 8;
        u16 tmp1 = D_800D1580;
        obj_fade_command(temp_v0, 2, tmp0, tmp1, 0);
    }
}

/* was func_1507233C */
void objev_set_mask_94(void) {
    D_800D154C->unk94 = (s32) ~(D_800D1580 | 1);
}

/* was func_15072360 */
void objev_clear_mask_94(void) {
    D_800D154C->unk94 &= ~D_800D1580;
}

/* was func_15072388 */
void objev_or_mask_94(void) {
    D_800D154C->unk94 |= D_800D1580;
}

/* was func_150723AC */
void objev_remove_kind(void) {
    struct127 *temp_v0 = obj_find_by_setup_id(D_800D1583);
    if (temp_v0 != NULL) {
        obj_remove(temp_v0, 0);
    }
}

/* was func_150723E0 */
void objev_remove_kind_owned(void) {
    struct127 *temp_v0 = obj_find_by_setup_id(D_800D1583);
    if ((temp_v0 != 0) && (temp_v0->unk65 != 0)) {
        obj_remove(temp_v0, 0);
    }
}

#ifdef NON_MATCHING
// event_respawn_record_object: P256: event-script command (request word D_800D1580): byte 0 = record id (looked up
// with setup_entry_find_by_id, -1 = none), bits 8..14 = the new object's +0x5C, bit 15 = no +0x101 mode (else 4), bits
// 16..23 = state (+0x232 gets the low 7 bits; bit 7 keeps the record's current object, otherwise that object is
// released first: obj_remove(obj, 0) + obj_reset). Clears the record's flag bytes (D_800D252C[rec], record
// +2), spawns it again (setup_entry_spawn, 1-based object number) and places the object on the current object
// D_800D154C, owned by it (+0x65 = its index + 1, +0x124 = D_800C3E78 + 1). With D_800BE616 set and the current
// object of kind 0x53 that one remembers the new index (+0x222); kind 0x16 objects on level 0x3F get +0x94 bit 2.
extern u8 *D_800D252C;
s32 setup_entry_spawn(u8 *, s32, s32, s32, s32);
void obj_reset(struct127 *);
/* was func_15072420 */
void objev_respawn_record_object(void) {
    s32 req = D_800D1580;
    s32 word5C = (req >> 8) & 0x7F;
    s32 noMode = (req >> 15) & 1;
    s32 state = (req >> 16) & 0xFF;
    s32 rec;
    s32 n;
    struct127 *old;
    struct127 *obj;

    rec = setup_entry_find_by_id(req & 0xFF);
    if (rec == -1) {
        return;
    }
    D_800D252C[rec] = 0;
    if (!(state & 0x80)) {
        old = obj_find_by_spawn(rec);
        if (old != NULL) {
            obj_remove(old, 0);
            obj_reset(old);
        }
    }
    ((u8 *) D_800D20FC + rec * 0x30)[2] = 0;
    n = setup_entry_spawn((u8 *) D_800D20FC + rec * 0x30, rec, 0, 0, 0);
    if (n == 0) {
        return;
    }
    obj = &D_800CC2D0[n - 1];
    if (obj == NULL) {
        return;
    }
    obj->unk65 = (D_800D154C - D_800CC2D0) + 1;
    obj->unk5C = word5C;
    obj->unk101 = noMode ? 0 : 4;
    obj->unk232 = state & 0x7F;
    obj->unk124 = D_800C3E78 + 1;
    obj->x_position = D_800D154C->x_position;
    obj->y_position = D_800D154C->y_position;
    obj->z_position = D_800D154C->z_position;
    if (D_800BE616 != 0 && D_800D154C->id == 0x53) {
        D_800D154C->unk222 = obj - D_800CC2D0;
    }
    if (D_800BE9F0 == 0x3F && obj->id == 0x16) {
        obj->unk94 |= 2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_respawn_record_object.s")
#endif
/* was func_1507266C */
void objev_adopt_remembered_obj(void)
{
  u8 new_var;
  s32 temp_a2;
  struct127 *temp_a1;
  if ((D_800BE616 != 0) || (D_800D154C->unk222 != 0))
  {
    new_var = (u8) D_800D1580;
    temp_a2 = ((s32) D_800D1580) >> 0x10;
    temp_a1 = &D_800CC2D0[D_800D154C->unk222];
    temp_a1->unk65 = D_800C3E78 + 1;
    temp_a1->unk5C = temp_a2;
    temp_a1->unk101 = 4;
    temp_a1->stunned = 0;
    temp_a1->immune = 0xFF;
    temp_a1->unk218 = 0;
    temp_a1->unkE4 = 0;
    temp_a1->unkE6 = 0;
    temp_a1->unk232 = new_var;
    temp_a1->unkEC = 1.0f;
    temp_a1->unkF0 = 1.0f;
    temp_a1->unkDC = 1.0f;
    temp_a1->unkE0 = 1.0f;
    obj_dust_trail_on_link(&D_800CC2D0[D_800C3E78], temp_a1);
  }
}

/* was func_15072740 */
void objev_own_remembered_obj(void) {
    s32 temp_v0;
    struct127 *temp_v1;

    temp_v0 = D_800D1580 >> 16;
    temp_v1 = &D_800CC2D0[D_800D154C->unk222];
    temp_v1->unk65 = D_800C3E78 + 1;
    temp_v1->unk5C = temp_v0;
    temp_v1->unk101 = 4;
}

/* was func_150727AC */
void objev_set_anim_speed(void) {
    D_800D154C->animation_speed = D_800D1580 * 0.1f;
    D_800D154C->unk2D0->unk10 = D_800D154C->animation_speed;
}

/* was func_150727F0 */
void objev_set_owned_state(void) {
    s32 i;

    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].interaction_state != 0) && ((D_800C3E78 + 1) == D_800CC2D0[i].unk65)) {
            D_800CC2D0[i].unk218 = NULL;
            D_800CC2D0[i].unk232 = D_800D1580;
        }
    }
}

/* was func_15072918 */
void objev_remove_self(void) {
    obj_remove(D_800D154C, 0);
}

/* was func_15072940 */
void objev_kill_self(void) {
    obj_remove(D_800D154C, 1);
}

/* was func_15072968 */
void objev_anim_2c_lock_run(void) {
    obj_start_anim(D_800D154C, 44, 1.5f, 12.0f, 0.0f, 0.0f, 0);
    D_800D154C->disable_run = 25;
}

/* was func_150729B4 */
void objev_set_2e4(void) {
    D_800D154C->unk2E4 = D_800D1580;
}

/* was func_150729D0 */
void objev_action21_idle(void) {
    D_800D154C->unk31C->unk8 = (u16)1;
    face_set_default_anim(D_800D154C, 21);
    objev_allow_run_idle();
}

/* was func_15072A14 */
void objev_clear_66_idle(void) {
    D_800D154C->unk31C->unk66 = (u16)0;
    player_idle_animation();
}

/* was func_15072A40 */
void objev_clear_19b_idle(void) {
    D_800D154C->unk31C->unk19B = (u8)0;
    D_800D154C->unk31C->unk78 = (u8)0;
    player_idle_animation();
}

/* was func_15072A7C */
void objev_maybe_anim_18a(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk1A9++;
        if ((random_int() & 7) < (u32) D_800D154C->unk31C->unk1A9) {
            obj_start_anim(D_800D154C, 394, 1.0f, 4.0f, 0.0f, 0.0f, 0);
        }
    }
}

/* was func_15072AF8 */
void objev_anim_next_blend6(void) {
    obj_start_anim(D_800D154C, D_800D154C->unk84.uh + 1, 1.0f, 6.0f, 0.0f, 0.0f, 0);
}

#ifdef NON_MATCHING
// player_anim_follow_up: when the player's (D_800D154C) animation +0x84 ends, start the one that follows it (blend 4):
// fixed pairs (0x35 / 0x3F -> 0x3A, 0x1CD / 0x1CF -> 0x1CE, the 0x26F..0x274 cycle, ...); for 0x10C, 0x156 and 0x167
// the follow-up depends on the player's flag +0x31C->+0x197, without it the idle animation (player_idle_animation) starts;
// 0xBE, and 0xC1 without flag 0x2000 in +0x31C->+0x38, go to 0xBF. Anything else starts nothing.
/* was func_15072B44 */
void objev_anim_follow_up(void) {
    s32 cur = D_800D154C->unk84.uh;
    s32 next = -1;

    switch (cur) {
        case 0x35:
        case 0x3F:
            next = 0x3A;
            break;
        case 0xFD:
            next = 0xFE;
            break;
        case 0x10A:
            next = 0x10A;
            break;
        case 0x10C:
            if (D_800D154C->unk31C->unk197 != 0) {
                next = 0x10A;
            } else {
                player_idle_animation();
            }
            break;
        case 0x12C:
        case 0x142:
            next = 0x12D;
            break;
        case 0x138:
            next = 0x3E;
            break;
        case 0x156:
            if (D_800D154C->unk31C->unk197 != 0) {
                next = 0x157;
            } else {
                player_idle_animation();
            }
            break;
        case 0x167:
            if (D_800D154C->unk31C->unk197 != 0) {
                next = 0x165;
            } else {
                player_idle_animation();
            }
            break;
        case 0x175:
        case 0x176:
            next = 0x177;
            break;
        case 0x1CD:
        case 0x1CF:
            next = 0x1CE;
            break;
        case 0x1D6:
            next = 0x1D7;
            break;
        case 0x1D7:
            next = 0x1D8;
            break;
        case 0x26F:
        case 0x270:
        case 0x271:
        case 0x272:
        case 0x273:
            next = cur + 1;
            break;
        case 0x274:
            next = 0x26F;
            break;
        case 0xBE:
            next = 0xBF;
            break;
        case 0xC1:
            if (!(D_800D154C->unk31C->unk38 & 0x2000)) {
                next = 0xBF;
            }
            break;
    }
    if (next != -1) {
        obj_start_anim(D_800D154C, next, 1.0f, 4.0f, 0.0f, 0.0f, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_anim_follow_up.s")
#endif
/* was func_15072DA0 */
void objev_set_2f8_low3(void) {
    D_800D154C->unk2F8 &= 0xFFF8;
    D_800D154C->unk2F8 |= D_800D1580;
}

/* was func_15072DD8 */
void objev_loop_sound_start(void) {
    obj_setup_run(D_800D154C, D_800D1580, 1.0f, 0);

    if ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk11A == 1)) {
        D_800D154C->unk31C->unk11A = (u8)2U;
    }
}

/* was func_15072E38 */
void objev_loop_sound_stop(void) {
    obj_setup_undo(D_800D154C, D_800D1580);

    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk11A = (u8)0;
    }
}

/* was func_15072E7C */
void objev_set_10c(void) {
    D_800D154C->unk10C = (s16) D_800D1580;
}

/* was func_15072E98 */
void objev_scale_anim_speed(void) {
    D_800D154C->unk2D0->unk10 *= D_800D1874;
}

/* was func_15072EC0 */
void objev_clear_10c_if_slow(void) {
    struct197 *tmp;

    tmp = D_800D154C->unk2D0;
    if (tmp->unk10 < D_800D1874) {
        D_800D154C->unk10C = 0;
    }
}

/* was func_15072EF4 */
void objev_set_stunned(void) {
    D_800D154C->stunned = (s8) D_800D1580;
}

s32 object_ray_hit_nearest(struct127 *, f32, f32, f32, f32, f32, f32, s32, s32);

/* was func_15072F10 */
void objev_fire_beam_forward(void) {
    f32 x;
    f32 z;
    f32 y;
    s16 angle;

    angle = D_800D154C->unk1D1 * 200;
    (*(s16 *)((u8 *)D_800D154C->unk31C + 0x24))--;
    vec_from_yaw_pitch(D_800D154C->unk7A - D_800D154C->unk31C->unk12, 2000.0f, angle * 0.005493164f, &x, &z, &y);
    x = x * 5000.0f + D_800D154C->x_position;
    z = z * 5000.0f + D_800D154C->z_position;
    y = y * 5000.0f + D_800D154C->y_position;
    object_ray_hit_nearest(D_800D154C, D_800D154C->x_position, D_800D154C->y_position + D_800D154C->unkD6, D_800D154C->z_position, x, y, z, D_800C3E78, 0x12);
}

/* was func_eu_1507340C */
void objev_nop_1507340c(void) {
}

/* was func_15073054 */
void objev_set_22e(void) {
    D_800D154C->unk22E = (s16) D_800D1580;
}

/* was func_15073070 */
void objev_nop_15073070(void) {

}

/* was func_15073078 */
void objev_12d748(void) {
    camera_shake_start(0, D_800D1580, 1);
}

/* was func_150730A4 */
void objev_set_1ff_200(void) {
    D_800D154C->unk1FF = (u8)3;
    D_800D154C->unk200 = (s8) D_800D1580;
}

/* was func_150730D0 */
void objev_toggle_2f8_100(void) {
    struct127 *temp_v0;

    if (D_800D1580 == 1) {
        temp_v0 = D_800D154C;
        temp_v0->unk2F8 |= 0x100;
    } else {
        temp_v0 = D_800D154C;
        temp_v0->unk2F8 &= 0xFEFF;
      }
}

#ifdef NON_MATCHING
void *obj_alloc_slot(void);
u8 *move_watch_spawn(u8 *arg0, u8 arg1, s32 arg2);
u8 *light_alloc_light_buf(s32 arg0);
void *light_alloc_lookat_buf(void);

#define O_U8(o, off)  (*(u8 *) ((u8 *) (o) + (off)))
#define O_S16(o, off) (*(s16 *) ((u8 *) (o) + (off)))
#define O_S32(o, off) (*(s32 *) ((u8 *) (o) + (off)))
#define O_F32(o, off) (*(f32 *) ((u8 *) (o) + (off)))

/* Spawns a child object (type 0x21) of `parent` at offset (x, y, z) from joint `joint` (the parent's position when it
 * has no joint matrices or joint == -1), yawed by `angle` degrees from the parent; scale-like fields 0x3C / 0x20 / 0x24
 * = s3c / s20 / s24, byte 0x83 = b83. Returns the new object. */
/* was func_15073118 */
u8 *obj_spawn_child_at_joint(struct127 *parent, s32 joint, s32 kind, f32 x, f32 y, f32 z, f32 angle, f32 s3c, f32 s20, f32 s24,
                         s32 b83) {
    struct127 *o = obj_alloc_slot();
    f32 mf[4][4];
    f32 (*m)[4];
    f32 px, py, pz;
    f32 yaw;
    u32 a;
    s32 i;

    O_F32(o, 0x24) = s24;
    O_F32(o, 0x20) = s20;
    O_F32(o, 0x3C) = s3c;
    O_U8(o, 0x83) = b83;
    if (parent->unk1D4 != NULL && joint != -1) {
        m = (f32 (*)[4]) ((u8 *) parent->unk1D4 + joint * 64);
        if (D_800C42B0 != 0) {
            guMtxL2F(mf, (Mtx *) m);   /* fixed-point joint matrices */
            m = mf;
        }
        mtxf_transform_point(m, x, y, z, &px, &py, &pz);
    } else {
        px = O_F32(parent, 0x14);
        py = O_F32(parent, 0x18);
        pz = O_F32(parent, 0x1C);
    }
    O_F32(o, 0x14) = px;
    O_F32(o, 0x18) = py;
    O_F32(o, 0x1C) = pz;
    /* yaw in 1/65536 turns; float -> u32 as the asm: <= -1 gives 0xFFFFFFFF */
    yaw = (f32) *(u16 *) ((u8 *) parent + 0x7A) + angle * 182.04445f;
    a = yaw <= -1.0f ? 0xFFFFFFFF : (u32) yaw;
    *(u16 *) ((u8 *) o + 0x7A) = a;
    *(u16 *) ((u8 *) o + 0x76) = a;
    O_S32(o, 0x0) = 0x21;
    O_U8(o, 0x125) = 0xFF;
    O_S32(o, 0xF8) = 2;
    if (kind != 0x42) {
        O_S32(o, 0xF8) = 0x100E;
    }
    O_U8(o, 0x66) = O_U8(parent, 0x66) & 0xC;
    O_S16(o, 0xE4) = 10;
    O_S16(o, 0xE6) = 10;
    O_F32(o, 0xEC) = 1.0f;
    O_F32(o, 0xF0) = 1.0f;
    O_F32(o, 0xDC) = 1.0f;
    O_F32(o, 0xE0) = 1.0f;
    O_F32(o, 0x14C) = 0.5f;
    O_F32(o, 0x150) = 0.5f;
    if (kind == 0x1F) {
        O_F32(o, 0xC8) = 10.0f;
    }
    O_S16(o, 0x278) = kind;
    O_U8(o, 0x5) = 5;
    O_U8(o, 0x3B) = 0xFF - (s32) ((u8 *) o - (u8 *) D_800CC2D0) / 0x32C;
    obj_setup_run(o, kind, 1.0f, 0);
    for (i = 0; i <= D_80082FA0; i++) {
        O_S32(o, 0x304 + i * 4) = (s32) light_alloc_light_buf(1);
    }
    if (O_S32(o, 0x300 + i * 4) != 0) {   /* the last slot written (i == 0: the word at 0x300) */
        O_U8(o, 0x301) = 1;
    }
    O_S32(o, 0x314) = (s32) light_alloc_lookat_buf();
    char_fx_attach(move_watch_spawn((u8 *) o, 1, 0), o, 0x13);
    return (u8 *) o;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/obj_spawn_child_at_joint.s")
#endif
#ifdef NON_MATCHING
/* Script command: spawn a projectile / effect object from the current object D_800D154C through
 * obj_spawn_child_at_joint (owner, type, model, then offsets and speeds; 100 = lifetime). D_800D1580 picks the kind:
 *   0: type 0x17 model 0x1F, flagged 0x1000000 in unkF8. When the owner's camera (unk318) is within 30
 *      of the owner (look_point_in_joint_range) and a 1-in-5 roll passes, it is aimed at the camera: unk2E4 = 1, no
 *      gravity, heading unk76 / unk7A from math_atan2f (degrees -> 0x10000 units, -0x4000), vertical
 *      speed = xz speed * dy / horizontal distance. Otherwise unk2E4 = 0.
 *   1: type 0xE model 0x42, offsets jittered by +-20 * owner->unk2E4 / 100.
 *   2: type 9 model 0x35, flagged 0x1000000, unkB8 = 180.
 *   3: type 0xE model 0x88, offsets jittered by +-200.
 * Jitter = (rand % 40 - 20) * scale (random_int, unsigned modulo). */
s32 look_point_in_joint_range(s32 index, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, void *out, f32 radius, s32 arg8, s32 arg9);
/* obj_spawn_child_at_joint (u8 *, defined above under NON_MATCHING since P89) returns the new object. */
#define JITTER(scale) ((f32)((s32)((u32)random_int() % 40) - 20) * (scale))

/* was func_1507342C */
void objev_spawn_shot_kind(void) {
    struct127 *obj;
    struct127 *shot;
    u8 *cam;
    s32 aim;
    u8 hitInfo[0x20];   /* sp68, filled by look_point_in_joint_range */
    f32 dx, dy, dz;
    f32 angle;
    f32 heading;
    f32 dist;
    f32 scale;
    f32 y, x;
    s16 dir;

    if (D_800D1580 == 0) {
        obj = D_800D154C;
        aim = FALSE;
        cam = (u8 *)obj->camera;
        if (look_point_in_joint_range(obj - D_800CC2D0, 0x17, 0x17, *(f32 *)(cam + 0x2F8), *(f32 *)(cam + 0x2FC),
                          *(f32 *)(cam + 0x300), hitInfo, 30.0f, 0, 0) != 0) {
            if ((u32)random_int() % 1000 < 200) {
                aim = TRUE;
            }
        }
        shot = (struct127 *) obj_spawn_child_at_joint(D_800D154C, 0x17, 0x1F, 0.0f, 0.0f, 16.0f, 0.0f, 42.8f, 49.9f, 2.9f, 100);
        shot->unkF8 |= 0x1000000;
        if (!aim) {
            shot->unk2E4 = 0;
            return;
        }
        dx = *(f32 *)(cam + 0x2F8) - shot->x_position;
        dy = *(f32 *)(cam + 0x2FC) - shot->y_position;
        dz = *(f32 *)(cam + 0x300) - shot->z_position;
        angle = math_atan2f(dx, dz) * 57.295776f;
        heading = angle;
        if (180.0f < angle) {
            heading = angle - 360.0f;
        }
        dist = sqrtf(dx * dx + dz * dz);
        shot->gravity = 0.0f;
        shot->unk2E4 = 1;
        shot->y_velocity = shot->xz_velocity * dy / dist;
        dir = (s32)(heading * 182.04445f) - 0x4000;
        shot->unk7A = dir;
        shot->unk76 = dir;
    } else if (D_800D1580 == 1) {
        scale = (f32)D_800D154C->unk2E4 * 0.01f;
        y = 58.4f + JITTER(scale);
        x = 42.8f + JITTER(scale);
        obj_spawn_child_at_joint(D_800D154C, 0xE, 0x42, 0.0f, 0.0f, 16.0f, JITTER(scale), x, y, 2.9f, 100);
    } else if (D_800D1580 == 2) {
        shot = (struct127 *) obj_spawn_child_at_joint(D_800D154C, 9, 0x35, 0.0f, 27.3f, 0.0f, 180.0f, 23.4f, 45.2f, 3.5f, 100);
        shot->unkF8 |= 0x1000000;
        shot->unkB8 = 180.0f;
    } else if (D_800D1580 == 3) {
        y = 58.4f + JITTER(10.0f);
        x = 42.8f + JITTER(10.0f);
        obj_spawn_child_at_joint(D_800D154C, 0xE, 0x88, 0.0f, 0.0f, 16.0f, JITTER(10.0f), x, y, 2.9f, 100);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_spawn_shot_kind.s")
#endif

/* was func_150738E8 */
void objev_toss_carried(void) {
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C != 0) {
        D_800D154C->unk13C = 0U;
        D_800CC2D0[temp_v0].unkF8 = 0x8200;
        D_800CC2D0[temp_v0].unk13D = 0;
        D_800CC2D0[temp_v0].unk76 = D_800D154C->unk7A;
        D_800CC2D0[temp_v0].unk65 = 0;
        D_800CC2D0[temp_v0].unk232 = 6;
        D_800CC2D0[temp_v0].unk218 = 0;
        D_800CC2D0[temp_v0].stunned = 0;
        D_800CC2D0[temp_v0].unk7A = 0xE000;
        obj_start_anim(D_800D154C, 0x97, 1.0f, 5.0f, 0.0f, 0.0f, 0);
    }
}

/* was func_150739A4 */
void objev_set_wait_timer(void) {
    D_800D154C->unk64 = (s8) D_800D1580;
}

/* was func_150739C0 */
void objev_wait_timer(void) {
    D_800D154C->unk64 -= D_800BE9A0;

    if (D_800D154C->unk64 >= 0) {
        D_800D1880 = 0;
        D_800D154C->unk138--;
        D_800D1878 = D_800D1580;
    }
}

/* was func_15073A28 */
void objev_set_44(void) {
    D_800D154C->unk44 = (f32) D_800D1580;
}

#ifdef NON_MATCHING
s32 obj_send_hit(struct127 *, s32, s32, u8);

/* was func_15073A50 */
void objev_launch_owner_obj(void) {
    s32 sp20;
    struct127 *sp18;
    s32 temp_v0;
    struct127 *temp_a0;

    temp_a0 = &D_800CC2D0[D_800D154C->unk124];
    if (temp_a0->unk65 != 0) {
        temp_v0 = D_800D1580;
        D_800D154C->unk13C = 0;
        temp_a0->immune = 0;
        sp18 = temp_a0;
        sp20 = temp_v0;
        obj_send_hit(temp_a0, D_800D1580 & 0xFF00FF, 0, D_800C3E78);
        temp_a0->unk1CC = 100000.0f;
        if (temp_v0 & 0x40000000) {
            temp_a0->unk1CC = D_800D154C->y_position;
        }
        temp_a0->immune = 0x14;
        temp_a0->unk76 = D_800D154C->unk7A + temp_v0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_launch_owner_obj.s")
#endif
/* was func_15073B38 */
void objev_set_31c_a8_ac_ad(void)
{
  f32 new_var; // fakematch: permuter temps (new_var/new_var2/new_var3) and ^ 0 set registers and load order
  f32 new_var3;
  f32 new_var2;
  new_var2 = (f32) (D_800D1580 & 0xFFFF);
  new_var = new_var2;
  D_800D154C->unk31C->unkA8 = new_var;
  new_var = (new_var3 = (f32) ((((s32) D_800D1580) >> 0x10) & 0xFF));
  D_800D154C->unk31C->unkAC = (u8) ((u32) new_var);
  D_800D154C->unk31C->unkAD = ((u8) (((s32) D_800D1580) >> 0x18)) ^ 0;
}

/* was func_15073C28 */
void objev_idle(void) {
    player_idle_animation();
}

/* was func_15073C48 */
void objev_nop_15073c48(void) {

}

// ???
/* was func_15073C50 */
void objev_set_height_above_remembered(void) {
    D_800D154C->unk224 = (s32)(D_800CC2D0[D_800D154C->unk222].y_position + D_800D1580);
}

/* was func_15073CB8 */
void objev_release_kind53_wait(void) {
    struct127 *tmp = obj_find_by_id(0x53);
    if ((tmp != 0) && ((u16)tmp->unk244 == 0x1F)) {
        tmp->unk21C = (u16)0;
    }
}

/* was func_15073CF4 */
void objev_set_inner_extent_width(void) {
    obj_set_inner_extent_width(D_800D154C, (f32) D_800D1580);
}


/* was func_15073D34 */
void objev_set_inner_extent_height(void) {
    obj_set_inner_extent_height(D_800D154C, (f32) D_800D1580);
}

/* was func_15073D74 */
void objev_unlink_kind(void) {
    struct127 *temp_v0;

    temp_v0 = obj_find_by_setup_id(D_800D1583);
    if (temp_v0 != 0) {
        temp_v0->unk65 = (u8)0;
    }
}

/* was func_15073DA4 */
void objev_camera_view_close(void) {
    s32 tmp;

    if (D_800D1580 != 0) {
        tmp = 18;
    } else {
        tmp = 2;
    }
    camera_object_spawn(D_800D154C->unk40, 150.0f, 0, 0, 100, tmp, 60.0f, 0.5f, 0, 0, 1);
}

/* was func_15073E2C */
void objev_camera_view_mode11(void) {
    camera_object_spawn(D_800D154C->unk40, 80.0f, 0, 0, 100, 11, 40.0f, 0.5f, 0, 14, 1);
}

/* was func_15073EA4 */
void objev_camera_view_mode12(void) {
    camera_object_spawn(D_800D154C->unk40, 60.0f, 0, 0, 100, 12, 40.0f, 0.5f, 0, 14, 1);
}

/* was func_15073F1C */
void objev_set_timer_3c_2000(void) {
    struct126 *temp_v0 = func_1503195C(D_800D154C, 0x3C, 0);
    if (temp_v0 != NULL) {
        temp_v0->unk38 = 2000;
    }
}

/* was func_15073F54 */
void objev_nop_15073f54(void) {
}

/* was func_15073F5C */
void objev_set_2cb(void) {
    D_800D154C->unk2CB = (s8) D_800D1580;
}

/* was func_15073F78 */
void objev_clear_flags_10b(void) {
    D_800D154C->unk10B &= ~D_800D1580;
}

#ifdef NON_MATCHING
extern u8 *D_800D252C;
extern f32 D_800CC704;
extern f32 D_800CC70C;
u8 *attachment_find_by_slot(u8 *, s32, s32);
s32 setup_entry_spawn(u8 *, s32, s32, s32, s32);
void sfx_emitter_replace_callback(s32, s32, s32, s32, s32, s32);
void obj_effect_run_handler(u8 *, s32, void *);
void obj_limb_muzzle_burst(u8 *, u8, u8, u8, s32);
s32 attachment_sound_cb();

/* struct126 (the owner's control block, me->unk31C) fields past the declared ones */
#define CTL_F32(c, off) (*(f32 *) ((u8 *) (c) + (off)))
#define CTL_U16(c, off) (*(u16 *) ((u8 *) (c) + (off)))
/* D_800D2104[obj->unk13F]: the object's model / anim block (s16 x/y/z offsets at +8/+A/+C) */
#define OBJ_MODEL_S16(o, off) (*(s16 *) ((u8 *) (D_800D2104[(o)->unk13F]) + (off)))

// event_spawn_helper_object: event-script command: spawns the helper object of record (arg & 0xFF) next to the
// current object D_800D154C (on its marker point 0x13 / 4 / arg byte 2 or 100 units above it), gives it the owner's
// heading, a throw speed (from the owner's charge +0x19C when D_800BE616 is set, with a launch sound), then applies
// the per-kind setup (0x4A, 0x7B, 0x9A), marks it active (+0x1CA bit 0x80) and stores its state in +0x232.
/* was func_15073FA0 */
void objev_spawn_helper_object(void) {
    s32 arg = D_800D1580 & 0xFFFF;
    s32 rec;
    s32 n;
    s32 state;
    s32 sel;
    s32 usePos;
    struct127 *me;
    struct127 *obj;
    struct126 *ctl;
    u8 *snd;
    f32 speed;
    s16 angle;
    f32 dx, dy, dz;
    s32 r1, r2, turn;

    rec = setup_entry_find_by_id(arg & 0xFF);
    if (rec == -1) {
        return;
    }
    state = 1;
    D_800D252C[rec] = 0;
    n = setup_entry_spawn((u8 *) D_800D20FC + rec * 0x30, rec, 0, 0, 0);
    if (n == 0) {
        return;
    }
    obj = &D_800CC2D0[n - 1];
    obj->unk124 = D_800C3E78 + 1;
    obj->unique_id = D_800C3E78 + 0x96;
    me = D_800D154C;
    speed = 40.0f;
    usePos = TRUE;
    if (me->unk1D4 != NULL) {
        usePos = FALSE;
        switch (me->id) {
        case 0x5A:
            sel = 0x13;
            break;
        case 0x75:
        case 0x80:
            sel = 4;
            break;
        case 0x7B:
            if (arg == 0x10) {
                sel = (D_800D1580 >> 16) & 0xFF;
            } else {
                usePos = TRUE;
            }
            break;
        default:
            usePos = TRUE;
            break;
        }
        if (!usePos) {
            mtx_transform_point_or_origin(NULL, &obj->x_position, (u8 *) me->unk1D4 + sel * 64);
            me = D_800D154C;
        }
    }
    if (usePos) {
        obj->x_position = me->x_position;
        obj->y_position = me->y_position + 100.0f;
        obj->z_position = me->z_position;
    }
    if (D_800BE616 != 0) {
        state = 5;
        obj->unk2E4 = CTL_U16(me->unk31C, 0x19C);
        me->unk31C->unk19B = 0;
        D_800D154C->unk31C->unk78 = 0;
        obj->gravity = 4.0f;
        me = D_800D154C;
        ctl = me->unk31C;
        speed = (f32) (200 - CTL_U16(ctl, 0x19C)) * 60.0f / 200.0f + 40.0f;
        if ((D_800D1580 >> 16) & 1) {
            speed = 0.0f;
        }
        if (ctl->unk198 != 0) {
            vec_from_yaw_pitch((u16) (s32) ((45.0f - CTL_F32(ctl, 0x170)) * 182.04445f), speed * 4.0f, 0.0f, &dx, &dy, &dz);
            obj->y_velocity = -dy;
        } else {
            obj->y_velocity = 50.0f;
        }
        snd = attachment_find_by_slot((u8 *) me, (me->id == 0x75) ? 0x64 : 0x2C, 0);
        if (snd != NULL) {
            obj->unk8E = *(s32 *) (snd + 0x3C);
            sfx_emitter_replace_callback((s32) attachment_sound_cb, (s32) snd, (s32) D_800D154C, (s32) sfx_cb_follow_object, (s32) obj,
                          obj->unique_id);
        }
        me = D_800D154C;
    }

    angle = me->unk7A;
    if (me->unk31C != NULL) {
        angle -= me->unk31C->unk12;
    }
    obj->unk7A = angle;
    obj->unk76 = angle;
    obj->xz_velocity = speed;
    obj->unk1CC = obj->y_position;

    switch (me->id) {
    case 0x4A:
        state = 5;
        obj->xz_velocity = 0.0f;
        obj_burning_fx_start((u8 *) obj, 0xFF);
        OBJ_MODEL_S16(obj, 8) = (s16) (s32) D_800CC704;
        OBJ_MODEL_S16(obj, 0xC) = (s16) (s32) D_800CC70C;
        break;
    case 0x7B:
        if (arg == 0x10) {
            state = 7;
            OBJ_MODEL_S16(obj, 8) = (s16) (s32) D_800CC704;
            OBJ_MODEL_S16(obj, 0xA) = 0x3D4;
            OBJ_MODEL_S16(obj, 0xC) = (s16) (s32) D_800CC70C;
            obj->unique_id = 0xFF - (n - 1);
            obj_effect_run_handler((u8 *) obj, 0xC, NULL);
            r1 = random_int();
            r2 = random_int();
            obj_limb_muzzle_burst((u8 *) D_800D154C, r1 & 1, r2 & 3, 0xFF, 1);
        } else if (arg == 0xA) {
            state = 0xE;
            obj->y_position = me->y_position;
        } else {
            state = 4;
            obj->unique_id = 0x12;
            obj->y_position = 1040.0f;
            obj->xz_velocity = 0.0f;
        }
        break;
    case 0x9A:
        turn = (random_int() & 0xFFF) - 0x800;
        r2 = (s16) ((u32) random_int() % 800);
        state = 7;
        vec_from_yaw_pitch((u16) (D_800D154C->unk76 + turn), 30.0f - (f32) r2 * 0.01f, 0.0f, &dx, &dy, &dz);
        obj->x_position -= dx;
        obj->z_position -= dy;
        me = D_800D154C;
        obj->xz_velocity = me->xz_velocity * 1.35f + 6.0f;
        obj->immune = 0xFF;
        obj->y_velocity = me->y_velocity;
        obj->y_position = me->y_position - 40.0f;
        obj->unk222 = me->unk222;
        break;
    }
    obj->health |= 0x80;
    obj->unk232 = state;
}
#undef CTL_F32
#undef CTL_U16
#undef OBJ_MODEL_S16
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_spawn_helper_object.s")
#endif

/* was func_15074644 */
void objev_set_31c_11a(void) {
    D_800D154C->unk31C->unk11A = (s8) D_800D1580;
}

/* was func_15074664 */
void objev_set_music_mode(void) {
    if (D_800D154C->unk31C != NULL) {
        if (D_800D1580 == 1) {
            audio_mixer_set_base_mode(5);
        } else if ((u8)D_800D154C->unk31C->unk94 == 1) {
            audio_mixer_set_base_mode(0);
        }
        D_800D154C->unk31C->unk94 = D_800D1580;
    }
}
/* was func_150746F0 */
void objev_damage(void) {
    struct127 *var_a0 = NULL;

    if (D_800BE616 != 0) {
        var_a0 = D_800D154C;
    } else if (D_800D154C->unk13C != 0) {
        var_a0 = D_800CC2D0;
    }
    if (var_a0 != NULL) {
        if (D_800D1580 >= var_a0->health) {
            var_a0->health = 0;
            D_800D154C->health = 0;
            if (var_a0->interaction_state == 1) {
                var_a0->immune = 0xFF;
                player_hit_reaction(var_a0, 6);
            }
        } else {
            var_a0->health -= D_800D1580;
            if (var_a0->unk31C != NULL) {
                if ((var_a0->camera != NULL) && (var_a0->unk31C->unk197 != 0)) {
                    screen_tint_start(0xFF, 0, 0, 0xB4, 0x14, var_a0->camera->unk23D);
                }
            }
        }
    }
}
// ?
#ifdef NON_MATCHING
/* was func_150747E4 */
void objev_set_owner_state(void) {
    struct127 *temp_a0;
    u8 temp_v0;

    temp_v0 = D_800D154C->unk65;
    if (temp_v0 != 0) {
        temp_a0 = &D_800CC2D0[temp_v0 - 1];
        temp_a0->unk218 = NULL;
        temp_a0->unk232 = (u8) D_800D1580;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_set_owner_state.s")
#endif
/* was func_15074840 */
void objev_add_31c_1aa(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk1AA += D_800D1580;
    }
}

/* was func_15074870 */
void objev_set_24f(void) {
    D_800D154C->unk24F = (s8) D_800D1580;
}

// ??
#ifdef NON_MATCHING
/*
 * P80: script command: add bits 24..31 of the command word D_800D1580 to the object's byte +0x138 when the flag
 * test (word +0x2E4 + 4 * bits 16..23) & bits 8..15 matches bit 0 (bit 0 set: the flags are clear; clear: any set).
 */
/* was func_1507488C */
void objev_skip_if_flags(void) {
    s32 w = D_800D1580;
    u8 *o = (u8 *) D_800D154C;
    s32 add = w & 1;

    if (*(s32 *) (o + 0x2E4 + ((w >> 16) & 0xFF) * 4) & ((w >> 8) & 0xFF)) {
        add ^= 1;
    }
    if (add) {
        o[0x138] += w >> 24;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_skip_if_flags.s")
#endif

/* was func_150748F4 */
void objev_set_cc3d7(void) {
    D_800CC3D7 = (s8) D_800D1580;
}

/* was func_1507490C */
void objev_set_carried_state(void) {
    struct127 *tmp;
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C != 0) {
        tmp = &D_800CC2D0[temp_v0 & 0xFF];
        if (D_800CC2D0[temp_v0].unk13D >= 0x64) {
            D_800CC2D0[temp_v0].unk232 = D_800D1580;
            D_800CC2D0[temp_v0].unk218 = 0;
            D_800CC2D0[temp_v0].stunned = 0;
        }
    }
}

/* was func_15074980 */
void objev_alert_players_near(void) {
    s32 i;
    f32 dist = D_800D1580 * 8;

    for (i = 0; i < D_8008FD8C; i++) {
        if (obj_dist_3d(D_800D154C, &D_800CC2D0[i]) < dist) {
            if (D_800CC2D0[i].unk31C != NULL) {
                D_800CC2D0[i].unk31C->chasing = 20;
            }
        }
    }
}

/* was func_15074A44 */
void objev_set_31c_26(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk26 = (s8) D_800D1580;
    }
}

/* was func_15074A6C */
void objev_skip_if_not_carrying(void) {
    if (D_800D154C->unk13C == 0) {
        D_800D154C->unk138++;
    }
}

#ifdef NON_MATCHING
/* was func_15074A94 */
void objev_speed_by_player_dist(void) {
    f32 temp_f0;
    f32 temp_f14;
    f32 var_f2;

    temp_f0 = obj_dist_3d(D_800CC2D0, D_800D154C);
    if (D_800D154C->unk148 < 0.2f) {
        D_800D154C->unk148 = D_800D154C->unk154;
    }
    if (temp_f0 < 200.0f) {
        var_f2 = 0.3f;
    } else {
        temp_f14 = D_800D154C->unk148;
        if (temp_f0 > 1500.0f) {
            var_f2 = temp_f14;
        } else {
            var_f2 = (((temp_f0 - 200.0f) / 1300.0f) * (temp_f14 - 0.3f)) + 0.3f;
        }
    }
    D_800D154C->unk158 = var_f2;
    D_800D154C->unk154 = D_800D154C->unk158;
    D_800D154C->unk15C = 0.02f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/objev_speed_by_player_dist.s")
#endif
// NON-MATCHING: JUSTREG
// void objev_speed_by_player_dist(void) {
//     f32 phi_f2;
//     f32 temp_f0;
//
//     temp_f0 = obj_dist_3d(&D_800CC2D0, D_800D154C);
//
//     if (D_800D154C->unk148 < D_8009A0E8) {
//         D_800D154C->unk148 = D_800D154C->unk154;
//     }
//
//     if (temp_f0 < 200.0f) {
//         phi_f2 = D_8009A0EC;
//     } else {
//         if (2.2f < temp_f0) {
//             phi_f2 = D_800D154C->unk148;
//         } else {
//             f32 tmp = 3.3f;
//             phi_f2 = D_800D154C->unk148;
//             phi_f2 = phi_f2 - tmp;
//             phi_f2 = phi_f2 * ((temp_f0 - 200.0f) / 2.4f);
//             phi_f2 = phi_f2 + tmp;
//         }
//     }
//     D_800D154C->unk154 = D_800D154C->unk158 = phi_f2;
//     D_800D154C->unk15C = 593.0f;
// }

/* was func_15074B7C */
void objev_hold_frame(void) {
    D_800D1880 = 0;
    D_800D1878 = D_800D1580;

    if (D_800D1580 == 0) {
        D_800D1878 = 0.1f;
        D_800D154C->unk1FC |= 4;
        D_800D154C->unk138 = 0;
    }
}

/* was func_15074BD8 */
void objhit_nop_15074bd8(s32 arg0, s32 arg1, s32 arg2) {
}

/* was func_15074BEC */
void objhit_nop_15074bec(s32 arg0, s32 arg1, s32 arg2) {
}

/* was func_15074C00 */
void objhit_burst_state5(s32 arg0, struct127 *arg1, s32 arg2) {
    struct199 tmp; // is this actually 2 structs?

    if (((u8)arg1->unk239 & 0x7F) == 5) {
        hitinfo_from_obj_floor(&tmp, arg1);   /* P80: a1 still holds arg1 at the jal; the callee reads the object */
        tmp.unk24 = D_800CC2C0;
        tmp.unk28 = D_800CC2C4;
        tmp.unk2C = D_800CC2C8;
        spark_burst_at(&tmp.unk24, &tmp, 0x16, 1, 0xFF, 0);
    }
}

s32 attachment_spawn_at_joint(u8 *, u8 *, s32, s32, s32, s32);
s32 water_ring_spawn_ex(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 hit_react_impact_small(u8 *, u8 *);

// P214: entry of hit-handler table D_80086A34, whose other 36 entries are void (a, b, s32): the NM build takes the
// third (unused) argument too, so the port's indirect call type matches. The extra parameter changes IDO's frame
// (0x10 bytes), so the default build keeps the 2-parameter definition.
#ifdef NON_MATCHING
/* was func_15074C80 */
void objhit_camera_object(u8 *arg0, u8 *arg1, s32 arg2) {
#else
void objhit_camera_object(u8 *arg0, u8 *arg1) {
#endif
    s32 var_a2;

    if ((*(u16 *)((u8 *)arg0 + 0x278)) == 0x11) {
        hit_react_impact_small(arg0, arg1);
    }
    if (((*(u16 *)((u8 *)arg0 + 0x278)) == 2) || ((*(u16 *)((u8 *)arg0 + 0x278)) == 0x12) || ((*(u16 *)((u8 *)arg0 + 0x278)) == 3) || ((*(u16 *)((u8 *)arg0 + 0x278)) == 6)) {
        if ((*(u8 *)((u8 *)arg1 + 0x1CA)) == 0) {
            if ((*(u16 *)((u8 *)arg0 + 0x278)) == 2) {
                var_a2 = 0x2A;
            } else if ((*(u16 *)((u8 *)arg0 + 0x278)) == 0x12) {
                var_a2 = 0x2F;
            } else if ((*(u16 *)((u8 *)arg0 + 0x278)) == 3) {
                var_a2 = 0x39;
            } else {
                var_a2 = 0x51;
            }
            attachment_spawn_at_joint(arg0, arg1, var_a2, 0xC, 1, 0);
        }
        (*(s8 *)((u8 *)arg0 + 0x1CA)) = 0;
    }
    if ((*(s32 *)((u8 *)arg1 + 0)) == 0x19) {
        water_ring_spawn_ex((s32) (256.0f - (math_atan2f((*(f32 *)((u8 *)arg0 + 0x20)), (*(f32 *)((u8 *)arg0 + 0x3C))) * 40.743664f)), 0xC0 - ((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8), (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s32) (*(f32 *)((u8 *)arg0 + 0x18)), (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), 0x10, 0x14, 0, 0xFF, 0);
    }
}

/* was func_15074DEC */
void objhit_set_2e8(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2E8 = 1;
}

/* was func_15074E04 */
void objhit_screen_flash_b(s32 arg0, s32 arg1, s32 arg2) {
    particle_emitter_preset_obj_twin((s32) (arg1 - (s32)&D_800CC2D0) / (s32) sizeof(struct127), 0xB4, 0xFF, 0);
    character_effect_attach(arg1, 0xB, 0, 1, 0xFF, 0, &D_80099C1C);
}

/* was func_15074E80 */
void objhit_grab_player_6(struct127 *arg0, struct127 *arg1, s32 arg2) {
    s8 sp1F = 0;
    hit_react_class_fx_steam(arg0, arg1, &sp1F);
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x60000; // 393216
        objev_own_remembered_obj();
    }
}

/* was func_15074EE8 */
void objhit_grab_player_7(struct127 *arg0, struct127 *arg1, s32 arg2) {
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x70000;
        objev_own_remembered_obj();
    }
}

/* was func_15074F30 */
void objhit_take_state_from_b(struct127 *arg0, struct127 *arg1, s32 arg2) {
    arg0->unk232 = arg1->unk109;
    arg0->unk218 = 0;
}

/* was func_15074F48 */
void objhit_fling_to_point(struct127 *arg0, struct127 *arg1, s32 arg2) {
    f32 dx = -2641.0f - arg0->x_position;
    f32 dz = arg0->z_position - 3039.0f;

    arg1->unk76 = math_atan2_u16(dx, dz, 0);
    arg1->xz_velocity = sqrtf((dx * dx) + (dz * dz)) * 0.03f;
    hit_react_puff_burst(arg0, arg1);
}

/* was func_15074FD4 */
void objhit_grab_player_and_hit(struct127 *arg0, struct127 *arg1, s32 arg2) {
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x60000;
        if (arg0->id == 0x8E) {
            D_800D1580 = 0x140000;
        }
        objev_own_remembered_obj();
    }
    hit_react_impact_large(arg0, arg1, arg2);
}

/* was func_15075050 */
void objhit_bounce(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->unkB8 = 5.0f;
    if (arg0->xz_velocity > 0.0f) {
        arg0->unkB8 = -5.0f;
    }
    arg0->gravity = 5.0f;
    arg0->y_velocity = 12.0f;
}

/* was func_150750A4 */
void objhit_set_gravity(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->gravity = 5.0f;
}

/* was func_150750C4 */
void objhit_kill_b(struct127 *arg0, struct127 *arg1, u8 *arg2) {

    if ((arg1->id  == 0x88) && ((s32) arg0->unk107 < 0x37)) {
        arg0->unk138 += 3;
    }
    hit_react_class_fx_steam(arg0, arg1, arg2);
    if (arg1->id != 0x53) {
        obj_set_destroyed(arg1);
        arg1->health = (u8)0;
        player_hit_reaction(arg1, 8);
        *arg2 = (u8)39;
    }
}

#ifdef NON_MATCHING
// player_find_owned_object: the first live object (state != 0, id != 0xFF) of D_800CC2D0[0..25] whose owner byte
// +0x65 is `owner`'s player number + 1, or NULL (P151). The other two arguments are not read.
/* was func_1507515C */
struct127 *player_find_owned_object(struct127 *owner, struct127 *unused1, s32 unused2) {
    struct127 *o;
    s32 i;

    for (i = 0; i < 26; i++) {
        o = &D_800CC2D0[i];
        if (o->interaction_state != 0 && o->id != 0xFF && o->unk65 == (owner - D_800CC2D0) + 1) {
            return o;
        }
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/player_find_owned_object.s")
#endif
