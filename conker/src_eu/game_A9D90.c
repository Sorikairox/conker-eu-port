#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void obj_get_held_point(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void player_enter_dead_state(struct127 *arg0);
void player_lose_life(s32);
#endif


/* was func_1507C8E0 */
void player_set_respawn_wait(struct127 *arg0, s32 arg1) {
    arg0->unk31C->unk120 = (u8)2;
    arg0->unk31C->unk124 = arg1;
}

// "goto" hell
#ifdef NON_MATCHING
void func_1517FD84(s32, f32, f32, f32, s32);
extern u16 D_8009015C;
extern s32 D_800BEB30;
extern u16 D_800D1CC2;

/* was func_1507C8FC */
void player_update_life_states(void) {
    struct {
        f32 u60;
        f32 u64;
        f32 u68;
    } sp;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 var_s2;
    s8 var_v1;
    struct126 *temp_s0;
    struct126 *temp_s0_2;
    struct126 *temp_s0_3;
    struct126 *temp_s0_4;
    struct127 *var_s1;
    u8 var_v0;

    if (D_800BEAC0 == 0) {
        var_v1 = D_8008FD8C;
        var_s1 = D_800CC2D0;
        var_s2 = 0;
        if (var_v1 > 0) {
            do {
                temp_s0 = var_s1->unk31C;
                if (temp_s0 != NULL) {
                    var_v0 = temp_s0->unk120;
                    if (var_v0 == 0) {
                        temp_s0->pad126 = 0;
                        goto block_54;
                    }
                    if (var_v0 != 1) {
                        if (D_80082FA0 >= var_s2) {
                            if ((D_800BE616 != 0) && (D_800D1CC2 & (1 << var_s2))) {
                                temp_s0->unk120 = 2;
                                var_s1->unk31C->unk124 = 0x3C;
                                var_v0 = var_s1->unk31C->unk120;
                            }
                            if (var_v0 == 0xB) {
                                func_1517F3B0(0, 0, 0, 0xF, 1, var_s2);
                                var_s1->unk31C->unk120 = 0xC;
                            } else if (var_v0 == 0xC) {
                                if (func_1517F51C(var_s2, 0) != 0) {
                                    player_lose_life(var_s2);
                                }
                            } else {
                                if (var_v0 == 2) {
                                    temp_v0 = var_s1->unk31C->unk124;
                                    if (temp_v0 > 0) {
                                        var_s1->unk31C->unk124 = temp_v0 - D_800BE9E4;
                                    } else {
                                        player_enter_dead_state(var_s1);
                                    }
                                } else if (var_v0 == 7) {
                                    temp_v0_2 = var_s1->unk31C->unk124;
                                    if (temp_v0_2 > 0) {
                                        var_s1->unk31C->unk124 = temp_v0_2 - D_800BE9E4;
                                    } else {
                                        var_s1->unk31C->unk120 = 8;
                                        obj_fade_command(var_s1, 2U, 0U, 0x3CU, 0U);
                                    }
                                }
                                var_s1->unk31C->pad126 += D_800BE9E4;
                                if ((*(u16 *)((u8 *)&D_800BEB30 + (var_s2 * 2)) & 0x8000) || ((D_800BE616 != 0) && (var_s1->unk31C->unk84 == 0)) || (func_150859AC((s16) var_s2, 3) < 2) || ((temp_s0_2 = var_s1->unk31C, (temp_s0_2->unk84 == 1)) && ((s16) temp_s0_2->pad126 >= 0xB5))) {
                                    var_s1->unk31C->unk122 = 1;
                                }
                                if (D_8009015C & 0x80) {
                                    var_s1->unk31C->unk122 = 0;
                                }
                                obj_get_held_point((u8 *) var_s1, &sp.u68, &sp.u64, &sp.u60);
                                func_1517FD84(0, sp.u68, sp.u64, sp.u60, var_s2);
                                temp_s0_3 = var_s1->unk31C;
                                if ((temp_s0_3->unk122 != 0) && (temp_s0_3->unk120 == 5)) {
                                    temp_s0_3->unk120 = 6;
                                }
                                if (var_s1->unk31C->unk120 == 9) {
                                    player_lose_life(var_s2);
                                }
                            }
                        } else if (var_v0 == 0xB) {
                            player_lose_life(var_s2);
                        } else if (var_v0 == 2) {
                            temp_v0_3 = temp_s0->unk124;
                            if (temp_v0_3 > 0) {
                                temp_s0->unk124 = temp_v0_3 - D_800BE9E4;
                            } else {
                                temp_s0->unk120 = 7;
                            }
                        } else {
                            temp_s0->pad126 = (s16) temp_s0->pad126 + D_800BE9E4;
                            if ((var_s1->unk7 == 0xFF) && ((s16) var_s1->unk31C->pad126 >= 0x86)) {
                                obj_fade_command(var_s1, 2U, 0U, 0x3CU, 0U);
                            }
                            temp_s0_4 = var_s1->unk31C;
                            if (((s16) temp_s0_4->pad126 >= 0x97) && (temp_s0_4->unk120 != 0xA)) {
    s32 pad;
                                player_lose_life(var_s2);
                            }
                        }
block_54:
                        var_v1 = D_8008FD8C;
                    }
                }
                var_s2 += 1;
                var_s1 = (struct127 *)((u8 *)var_s1 + (0x32C));
            } while (var_s2 < var_v1);
        }
        D_8009015C &= 0xFF7F;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/player_update_life_states.s")
#endif
/* was func_1507CD0C */
void player_enter_dead_state(struct127 *arg0) {
    s32 temp_lo = ((s32)arg0 - (s32)&D_800CC2D0) / (s32)sizeof(struct127);

    arg0->unk31C->unk120 = 3;

    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo);
    }
}

#ifdef NON_MATCHING
void node_broadcast_all(s32 arg0, u8 arg1);
void func_1504BAF0(struct127 *);
u8 *screen_lightning_curve_spawn(s16 count, f32 scale, u8 arg2, s32 arg3);
extern u16 D_8009015C;
extern s16 D_800E0F00[];
extern u8 D_800D1CC9;

// player_hit_reaction: puts player object `obj` (D_800CC2D0 index below D_8008FD8C) into hit / death reaction
// `kind` (0..16; stored in its controller +0x121) unless it is already reacting (only kind 9 can override a
// different running reaction). In multiplayer it counts the hit (D_800E0F00[idx]) and may play sound 10; it
// sends message 3, picks the reaction animation (D_800D1CC9 = camera / blend mode), resets the object's motion
// fields, and sets the controller state (+0x120: 1, 2 via player_set_respawn_wait, 11, or player_lose_life for kind 15).
// Player 0 in mode 4 also spawns 4..6 random curve objects. Returns 0: every caller declares s32 but none
// reads it (the asm leaves a scratch value in v0) (P156).
/* was func_1507CD64 */
s32 player_hit_reaction(struct127 *obj, s32 kind) {
    u8 *ctl = (u8 *)obj->unk31C;
    struct {
        struct127 *obj;
        u8 uid;
    } msg;
    s32 idx;
    s32 rerun;
    s32 anim;
    s32 animFlag;
    s32 next;
    struct127 *saved;
    u32 r;
    f32 f;

    if (ctl == NULL) {
        return 0;
    }
    idx = ((s32)obj - (s32)D_800CC2D0) / 0x32C;
    if (idx >= D_8008FD8C) {
        return 0;
    }
    rerun = FALSE;
    if (ctl[0x120] != 0) {
        if (kind != 9 || ctl[0x121] == kind) {
            return 0;
        }
        rerun = TRUE;
    }
    ctl[0x121] = kind;
    if (D_800BE616 != 0 && !rerun) {
        if (idx < 16) {
            D_800E0F00[idx]++;
        }
        if ((D_8009015C & 0x20) && obj->unk128 == 0) {
            func_15085710(1, 10, 1);
        }
    }
    msg.obj = obj;
    msg.uid = obj->unique_id;
    node_broadcast_all((s32)&msg, 3);

    D_800D1CC9 = 0;
    if (((u8 *)obj->unk31C)[0x1AC] != 0) {
        D_800D1CC9 = 2;
    }
    anim = -1;
    animFlag = 0;
    next = 0;
    switch (kind) {
        case 0:
            anim = 0x58;
            break;
        case 1:
            anim = 0x13;
            animFlag = 1;
            break;
        case 2:
            anim = 7;
            animFlag = 1;
            break;
        case 3:
            D_800D1CC9 = 1;
            anim = 0x28;
            break;
        case 4:
            D_800D1CC9 = 1;
            anim = 0x24;
            next = 1;
            break;
        case 5:
            D_800D1CC9 = 3;
            anim = 0x24;
            next = 1;
            break;
        case 6:
            if (obj->interaction_state == 1 || obj->interaction_state == 0x15 || obj->unk5 == 3 || obj->unk65 != 0) {
                anim = 0x170;
            }
            next = 1;
            break;
        case 7:
            anim = 0x16F;
            break;
        case 8:
            D_800D1CC9 = 3;
            anim = 0x170;
            next = 1;
            break;
        case 9:
            next = 2;
            break;
        case 10:
            D_800D1CC9 = 3;
            anim = 0x2F;
            break;
        case 11:
            anim = 0x2D4;
            break;
        case 12:
            anim = 0x2D6;
            break;
        case 13:
            anim = 0x2D8;
            next = 1;
            break;
        case 14:
            anim = 0x1E;
            next = 1;
            break;
        case 15:
            D_800D1CC9 = 3;
            anim = 0x170;
            next = 3;
            break;
        case 16:
            anim = 0xF6;
            next = 1;
            break;
    }
    if (anim != -1) {
        obj_start_anim(obj, anim, 1.0f, 3.0f, 0.0f, 0.0f, animFlag);
    }

    obj->unkF8 |= 0x200;
    *((u8 *)obj + 0x1CA) = 0;
    *((u8 *)obj + 0x125) = 0xFF;
    *((u8 *)obj + 0x104) = 0xFF;
    *((u8 *)obj + 0x89) = 0xFF;
    obj->unkE4 = 0;
    obj->unkE6 = 0;
    *(f32 *)((u8 *)obj + 0x3C) = 0.0f;
    *(s16 *)((u8 *)obj->unk31C + 0x46) = 0;
    if (obj->unk13C != 0) {
        saved = D_800D154C;
        D_800D154C = obj;
        func_1504BAF0(obj);
        D_800D154C = saved;
    }

    if (next == 0 || next == 3) {
        ((u8 *)obj->unk31C)[0x120] = 1;
    } else {
        player_set_respawn_wait(obj, 0);
    }
    if (next == 2) {
        ((u8 *)obj->unk31C)[0x120] = 11;
    } else if (next == 3) {
        player_lose_life(idx);
    }

    if (idx == 0 && D_800BE9F0 == 4) {
        r = random_int();
        f = random_float();
        screen_lightning_curve_spawn(r % 3 + 4, f * 0.1f + 0.3f, 0xFF, 0);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/player_hit_reaction.s")
#endif
/* was func_1507D158 */
void player_send_event(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 tmp = D_800CC82F[arg0 * 812];
    event_dispatch_alt(3, tmp | 0x2000, arg1, arg2, arg3, arg4);
}
#ifdef NON_MATCHING
void func_15085710(s16, s16, s32);
s32 func_150859AC(s16 arg0, s32 arg1);
s32 func_15082E44(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);
void camera_controller_init(struct108 *arg0, s32 arg1, s16 arg2, s32 arg3);
void func_150858A0(void *arg0, s32 arg1, s32 arg2);
void func_15182338(s32);
void func_150891D4(u8 *arg0);
extern u8 D_800BE616;
extern s32 D_800BE9F0;
extern s8 D_8008726C;
extern u8 D_800D18A8;
extern s16 D_800BEE12;
extern struct127 D_800CC2D0[];

// mp_player_respawn: multiplayer respawn of a player object (D_800CC2D0[idx], 0x32C bytes) after a lost life.
// Keeps the character record's (+0x31C) +0x1AA / +0x1AF / +0x1B0 and the object's +0x328 across the reset; the team /
// colour byte is ctl +0x11B in multiplayer (D_800BE616), else -1. In level 0x2B a player whose stat 1 is 17..32 gets a
// random 17..32 back (func_15085710(idx, 0, n)) and its D_800D20FC entry +4 becomes 0x9C (n < 29) or 0x9D. Then the
// object is reset (obj_remove), its D_800D20FC entry re-placed at a start point (func_15082E44, under the
// D_800D18A8 flag), and human players (idx <= D_80082FA0) get their camera / HUD reset (camera_controller_init, func_15182338,
// two func_1517F3B0 fades), others func_150858A0. Finally the control state is cleared, flags +0x22C |= 0x100,
// health D_8008726C, and in multiplayer a 150-frame invulnerability (+0x125, ctl +0x1B1); in level 0x33 (race) also
// a 120-frame event (player_send_event) and a rail re-sync (func_150891D4). void: the callers ignore v0.
/* was func_1507D1D8 */
void mp_player_respawn(struct127 *rec) {
    u8 *obj = (u8 *) rec;
    u8 *ctl = *(u8 **) (obj + 0x31C);
    s32 keep1AA = *(s16 *) (ctl + 0x1AA);
    s8 keep1B0 = ctl[0x1B0];
    s8 keep328 = obj[0x328];
    s8 keep1AF = ctl[0x1AF];
    s8 team;
    s32 idx;
    s32 n;

    if (D_800BE616 != 0) {
        team = ctl[0x11B];
    } else {
        team = -1;
    }
    if (D_800BE9F0 == 0x2B) {
        idx = (s32) (obj - (u8 *) D_800CC2D0) / 0x32C;
        n = func_150859AC((s16) idx, 1);
        if (n >= 0x11 && n < 0x21) {
            n = (random_int() & 0xF) + 0x11;
            func_15085710((s16) idx, 0, n);
            if (n < 0x1D) {
                ((u8 *) D_800D20FC)[idx * 0x30 + 4] = 0x9C;
            } else {
                ((u8 *) D_800D20FC)[idx * 0x30 + 4] = 0x9D;
            }
        }
    }
    idx = (s32) (obj - (u8 *) D_800CC2D0) / 0x32C;
    obj_remove(rec, 0);
    D_800D18A8 = 1;
    func_15082E44((u8 *) D_800D20FC + idx * 0x30, idx, 0, 0, 0);
    (*(u8 **) (obj + 0x31C))[0x1B0] = keep1B0;
    (*(u8 **) (obj + 0x31C))[0x1AF] = keep1AF;
    obj[0x328] = keep328;
    if (idx <= D_80082FA0) {
        camera_controller_init((struct108 *) ((u8 *) D_800DBFF0 + idx * 0x9A0), idx, D_800BEE12, team);
        func_15182338(idx);
        func_1517F3B0(0, 0, 0, 0, 1, idx);
        func_1517F3B0(0, 0, 0, 0x1E, 0, idx);
    } else {
        func_150858A0(obj, team, 0);
    }
    D_800D18A8 = 0;
    (*(u8 **) (obj + 0x31C))[0x120] = 0;
    (*(u8 **) (obj + 0x31C))[0x122] = 0;
    *(s16 *) (*(u8 **) (obj + 0x31C) + 0x124) = 0;
    *(s16 *) (*(u8 **) (obj + 0x31C) + 0x1AA) = keep1AA;
    *(u16 *) (obj + 0x22C) |= 0x100;
    obj[0x1CA] = D_8008726C;
    (*(u8 **) (obj + 0x31C))[0x75] = 0;
    obj[0x20F] = 0xFF;
    obj[0x210] = 0xFF;
    obj[0x211] = 0xFF;
    obj[0x232] = 1;
    *(s32 *) (obj + 0x218) = 0;
    (*(u8 **) (obj + 0x31C))[0x11B] = team;
    if (D_800BE616 != 0) {
        obj[0x125] = 0x96;
        (*(u8 **) (obj + 0x31C))[0x1B1] = 0x96;
        if (D_800BE9F0 == 0x33) {
            player_send_event(idx, 0x78, 0, 0, 0);
            func_150891D4(obj);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/mp_player_respawn.s")
#endif

#ifdef NON_MATCHING
void func_15085710(s16, s16, s32);
s32 func_150859AC(s16 arg0, s32 arg1);
void mp_player_respawn(struct127 *);
void func_1501C710(s32, s32, s32, s32, s32);
void game_over_apply_pending(void);
extern u16 D_8009015C;
extern s8 D_8008726C;
extern s8 D_80087260;
extern u8 D_800BE800;
extern s8 D_8008FDA8;
extern s8 D_800E1050;
extern u8 D_800BE616;
extern u16 D_800D18A0;
extern u8 D_800D2E43;
extern u8 D_800D18A8;
extern s8 D_80090134;
extern s8 D_800BEA38;
extern struct127 D_800CC2D0[];

/* A player record (index idx) has lost a life. With lives left (func_150859AC(idx, 3)) the life counter (5) is
 * reset and the record respawns: in multiplayer (D_800BE616) via mp_player_respawn or a 10-frame timer, else a
 * checkpoint restart (func_1501C710). Out of lives: game over (single player) or the player is marked out in
 * D_800D18A0 (multiplayer); then the active-player counters drop. void: no caller uses a result. */
/* was func_1507D4F8 */
void player_lose_life(s32 idx) {
    struct127 *rec;
    u8 *ctl;

    if (!(D_8009015C & 1)) {
        func_15085710(idx, 4, 1);
    }
    if (func_150859AC(idx, 3) != 0) {
        func_15085710(idx, 5, D_8008726C);
        rec = &D_800CC2D0[idx];
        *(s16 *)((u8 *)rec + 0xB2) = 0;
        if (D_800BE616 != 0) {
            if (D_800E1050 == 0) {
                mp_player_respawn(rec);
                return;
            }
            *((u8 *)rec->unk31C + 0x120) = 10;
            return;
        }
        D_800D18A8 = 1;
        if (!(D_800D2E4C->unk19 & 4) && D_8008FDA8 >= 0) {
            func_1501C710(1, 0x22, 0, 0, 0);
        } else {
            func_1501C710(2, (s8)D_800BE3DF, D_800BE800, 0, 0);
        }
        return;
    }
    if (D_800BE616 == 0) {
        D_800D2E43 = 1;
        game_over_apply_pending();
        D_800D18A8 = 1;
        func_15085710(idx, 5, D_8008726C);
        func_15085710(idx, 2, D_80087260);
        func_1501C710(1, 0x18, 0, 0, 0);
    } else {
        D_800D18A0 |= 1 << idx;
    }
    ctl = (u8 *)D_800CC2D0[idx].unk31C;
    if (ctl[0x84] == 0) {
        D_80090134--;
    }
    ctl[0x120] = 10;
    D_800BEA38--;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/player_lose_life.s")
#endif
// NON-MATCHING: pretty far away!
// void player_lose_life(s16 arg0) { // struct126 *
//     // ?32 sp24;
//     struct127 *temp_a0;
//
//     if ((D_8008FDBC & 1) == 0) {
//         func_15085710(arg0, 4, 1);
//     }
//     // sp24 = (?32) arg0;
//     if (func_150859AC(arg0, 3) != 0) {
//         func_15085710(arg0, 5, D_8008726C); //temp_ret =
//         temp_a0 = &D_800CC2D0[arg0];
//         temp_a0->unkB2 = (u16)0;
//         if (D_800BE616 == 0) {
//             D_800D18A8 = (u8)1;
//             if (((D_800D2E4C->unk19 & 4) != 0) || (D_8008FDA8 < 0)) {
//                 func_1501C730(2, D_800BE3DF, D_800BE3E0, 0, 0);
//                 return;
//             }
//             func_1501C730(1, 0x22, 0, 0, 0);
//             return;
//         }
//         if (D_800E0C20 != 0) {
//             temp_a0->unk31C->unk120 = (u8)0xA;
//             return; // temp_ret;
//         }
//         mp_player_respawn(temp_a0);
//         return;
//     }
//     if (D_800BE616 == 0) {
//         D_800D2E43 = (u8)1;
//         game_over_apply_pending();
//         D_800D18A8 = (u8)1;
//         func_15085710(arg0, 5, D_8008726C);
//         func_15085710(arg0, 2, D_80087260);
//         func_1501C730(1, 0x18, 0, 0, 0);
//     } else {
//         D_800D18A0 = (u16) (D_800D18A0 | (1 << (s32) arg0));
//     }
//     // temp_a0 = &D_800CC2D0[arg0];
//     if (temp_a0->unk31C->unk84 == 0) {
//         D_8008FD94 -= 1; //(s8) (D_8008FD94 - 1);
//     }
//     temp_a0->unk31C->unk120 = (u8)0xA;
//     D_800BE618 -= 1; //(s8) (D_800BE618 - 1);
//     //return temp_a0_2->unk31C;
// }

#ifdef NON_MATCHING
extern u8 D_800BE616;
extern s32 D_800BE9F0;
extern u8 D_800C35EA;
void func_150B0828(u8 *arg0, u8 arg1, s32 arg2);
void func_150C04E0(u8 *obj);
void explosion_ground_effect(struct127 *arg0);
void fx_big_explosion_at_obj(u8 *arg0, s32 arg1, s32 arg2);
void func_151C9740(struct127 *obj, u8 arg1, s32 arg2);
void func_151CFFFC(u8 *obj, u8 flag, s32 arg2);
void func_150BE994(u8 *arg0, s32 arg1, s32 arg2);
void object_set_all_flags(s32 arg0, s32 arg1);
void owner_spawn_children(u8 *owner);
s32 player_hit_reaction(struct127 *obj, s32 kind);
void func_151BAAC8(u8 *obj, u8 arg1, s32 arg2);
void func_15145A50(struct127 *arg0);
u8 *world_record_find(u8 id);
struct127 *player_find_owned_object(struct127 *owner, struct127 *unused1, s32 unused2);
s32 object_hit_effects(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7);
void func_150B8020(u8 *obj, u8 owner, s32 arg2);
void func_150BC968(u8 *obj);
void func_150BC03C(u8 *obj);
void func_151A7240(u8 *obj, u8 arg1, s32 arg2);
void object_explode(u8 *obj, u8 owner, s32 arg2);
void func_151D2860(struct127 *arg0, u8 arg1, s32 arg2);
/* object_destroy_effects: the break / death effects of an object by its type (byte +4): one effect function per
 * type (owner 0xFF, flag 1), the type-0x20 crate picks the hard / soft debris by its y speed +0x20. Types 5 /
 * 0xAD..0xAF clear +0x328, release (object_set_all_flags / owner_spawn_children) and return 1. Types 0x28 / 0x77 shatter the
 * model, drop the held item and spawn a pickup record (world_record_find: multiplayer id obj[0x127] + 11 after
 * player_hit_reaction(obj, 6), else id 1 in level 0x23) placed at the object; multiplayer types 0x28 / 0x77 / 0x53 /
 * 0x90 (level 0x33 only) return 2 (respawn), everything else 0. */
/* was func_1507D754 */
s32 object_destroy_effects(struct127 *arg0) {
    u8 *obj = (u8 *) arg0;
    u8 *rec;
    struct127 *item;

    switch (obj[4]) {
        case 0x05:
        case 0xAD:
        case 0xAE:
        case 0xAF:
            obj[0x328] = 0;
            object_set_all_flags((s32) obj, 0);
            owner_spawn_children(obj);
            return 1;
        case 0x0D:
            func_150B8020(obj, 0xFF, 1);
            break;
        case 0x10:
        case 0x38:
        case 0x91:
            func_150C04E0(obj);
            break;
        case 0x20:
            if (*(f32 *) (obj + 0x20) < -20.0f) {
                func_150BC968(obj);
            } else {
                func_150BC03C(obj);
            }
            break;
        case 0x25:
            if (*(s32 *) (obj + 0x2EC) != 0 || D_800BE9F0 == 6 || D_800BE9F0 == 0x3B) {
                func_151CFFFC(obj, 0xFF, 1);
            }
            break;
        case 0x28:
        case 0x77:
            rec = NULL;
            func_151BAAC8(obj, 0xFF, 1);
            func_15145A50(arg0);
            if (D_800BE616 != 0) {
                player_hit_reaction(arg0, 6);
                rec = world_record_find(obj[0x127] + 0xB);
            } else {
                if (D_800BE9F0 == 0x23) {
                    rec = world_record_find(1);
                }
                item = player_find_owned_object(arg0, NULL, 0);
                if (item != NULL && D_800C35EA != 1) {
                    object_hit_effects((u8 *) item, 1, 1, 1, 1, 0, 0xFF, 1);
                }
            }
            if (rec != NULL) {
                rec[0x6E] = 0;
                *(s16 *) (rec + 0x10) = *(f32 *) (obj + 0x14);
                *(s16 *) (rec + 0x12) = *(f32 *) (obj + 0x18);
                *(s16 *) (rec + 0x14) = *(f32 *) (obj + 0x1C);
                *(f32 *) (rec + 0x0) = *(f32 *) (obj + 0xB8);
                *(f32 *) (rec + 0x4) = *(f32 *) (obj + 0x40);
                *(f32 *) (rec + 0x8) = *(f32 *) (obj + 0xC4);
                rec[0x8A] = 0xFF;
                *(s32 *) (rec + 0x7C) = 0;
                *(s32 *) (rec + 0x80) = 0;
                *(s32 *) (rec + 0x84) = 0;
            }
            return (D_800BE616 != 0) ? 2 : 0;
        case 0x34:
            object_explode(obj, 0xFF, 1);
            break;
        case 0x3A:
        case 0x3D:
            explosion_ground_effect(arg0);
            break;
        case 0x44:
            func_151D2860(arg0, 0xFF, 1);
            break;
        case 0x47:
            func_151C9740((struct127 *) obj, 0xFF, 1);
            break;
        case 0x4A:
            fx_big_explosion_at_obj(obj, 0xFF, 1);
            break;
        case 0x4F:
        case 0x83:
            func_151A7240(obj, 0xFF, 1);
            break;
        case 0x53:
            if (D_800BE616 != 0) {
                player_hit_reaction(arg0, 10);
                return 2;
            }
            break;
        case 0x79:
            func_150BE994(obj, 0xFF, 1);
            break;
        case 0x7F:
            func_150B0828(obj, 0xFF, 1);
            break;
        case 0x90:
            if (D_800BE616 != 0 && D_800BE9F0 == 0x33) {
                player_hit_reaction(arg0, 8);
                return 2;
            }
            break;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/object_destroy_effects.s")
#endif

/* was func_1507DB44 */
void object_set_all_flags(s32 arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

/* was func_1507DB64 */
void a9d90_stub(void) {
}

#ifdef NON_MATCHING
s32 texture_cache_lookup(s32 *, s32, s32, s32);
void func_15182338(s32);
extern s32 D_80086F20;
extern u16 D_800D1CC2;
extern s32 D_800D1CC4;
extern s32 D_D11;

/* was func_1507DB6C */
u8 *player_draw_out_overlay(u8 *arg0, s32 arg1) {
    s32 temp_a2_2;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 var_a1;
    u16 temp_a2;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 temp_a1;
    u8 temp_t5;
    u8 temp_t8;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_v1;
    u8 *var_s0;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)arg0 + 4)) = &D_80086F20;
    temp_s0 = arg0 + 8;
    temp_v0 = texture_cache_lookup(&D_D11, 0, 3, 0);
    (*(s32 *)((u8 *)temp_s0 + 0)) = 0xFD180000;
    (*(s32 *)((u8 *)temp_s0 + 4)) = temp_v0;
    temp_s0_2 = temp_s0 + 8;
    (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xF5180000;
    (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0x07080200;
    temp_s0_3 = temp_s0_2 + 8;
    (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xE6000000;
    (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0;
    temp_s0_4 = temp_s0_3 + 8;
    (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xF3000000;
    (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0x073FF000;
    temp_s0_5 = temp_s0_4 + 8;
    (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0;
    temp_s0_6 = temp_s0_5 + 8;
    (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF5181000;
    (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x80200;
    temp_s0_7 = temp_s0_6 + 8;
    (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xF2000000;
    (*(s32 *)((u8 *)temp_s0_7 + 4)) = 0x7C07C;
    temp_s0_8 = temp_s0_7 + 8;
    (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xEF002C3F;
    (*(s32 *)((u8 *)temp_s0_8 + 4)) = 0x0F0A4004;
    var_s0 = temp_s0_8 + 8;
    temp_a2 = D_800D1CC2;
    temp_t0 = 1 << arg1;
    if (temp_a2 & temp_t0) {
        temp_v0_2 = ((s32 *)((u8 *)&D_800D1CC4 + arg1));
        temp_a1 = *temp_v0_2;
        temp_t8 = temp_a1 - 4;
        if ((s32) temp_a1 >= 4) {
            *temp_v0_2 = temp_t8;
            var_a1 = temp_t8 & 0xFF;
            goto block_6;
        }
        D_800D1CC2 = temp_a2 & ~temp_t0;
        func_15182338(arg1);
        func_1517F3B0(0, 0, 0, 0x78, 0, arg1);
    } else {
        temp_v0_3 = ((s32 *)((u8 *)&D_800D1CC4 + arg1));
        temp_t5 = *temp_v0_3 + 4;
        var_a1 = temp_t5 & 0xFF;
        *temp_v0_3 = temp_t5;
        if (var_a1 >= 0x3D) {
            *temp_v0_3 = 0x3C;
            var_a1 = 0x3C & 0xFF;
        }
block_6:
        temp_v1 = D_800BE628 + (arg1 * 0x180);
        temp_v0_4 = var_a1 + 4;
        temp_s0_9 = var_s0 + 8;
        temp_s0_10 = temp_s0_9 + 8;
        temp_t2 = (s32) ((*(f32 *)((u8 *)temp_v1 + 0x30)) + (*(f32 *)((u8 *)temp_v1 + 0x2C))) * 2;
        temp_a3 = temp_t2 - temp_v0_4;
        temp_t4 = (s32) ((*(f32 *)((u8 *)temp_v1 + 0x28)) + (*(f32 *)((u8 *)temp_v1 + 0x24))) * 2;
        temp_a2_2 = temp_t2 + temp_v0_4;
        (*(s32 *)((u8 *)var_s0 + 0)) = (s32) (((temp_a2_2 & 0xFFF) << 0xC) | 0xE4000000 | ((temp_t4 + temp_v0_4) & 0xFFF));
        (*(s32 *)((u8 *)var_s0 + 4)) = (s32) (((temp_a3 & 0xFFF) << 0xC) | ((temp_t4 - temp_v0_4) & 0xFFF));
        (*(s32 *)((u8 *)temp_s0_9 + 0)) = 0xE1000000;
        (*(s32 *)((u8 *)temp_s0_9 + 4)) = 0;
        temp_t2_2 = (0x20000 / (s32) (temp_a2_2 - temp_a3)) & 0xFFFF;
        (*(s32 *)((u8 *)temp_s0_10 + 0)) = 0xF1000000;
        (*(s32 *)((u8 *)temp_s0_10 + 4)) = (s32) ((temp_t2_2 << 0x10) | temp_t2_2);
        var_s0 = temp_s0_10 + 8;
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/player_draw_out_overlay.s")
#endif
/* was func_1507DE4C */
void obj_set_dying_flags(struct127 *arg0) {

    if (arg0->interaction_state == 1) {
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        arg0->unk9C |= 0xF000;
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        return;
    }

    switch(arg0->id) {
        case 0x9F:
        case 0xa0:
            arg0->unk9C |= 0xF000;
            break;
        case 0x5A:
        case 0x74:
        case 0x7A:
            arg0->unk9C |= 0xFF8;
            break;
    }
}


/* was func_1507DF10 */
void obj_set_hit_flags_by_kind(u8 *arg0, s32 arg1) {
    switch (arg1) {
    case 9:
        *(s32 *)(arg0 + 0x94) |= 0x20;
        *(s32 *)(arg0 + 0x9C) |= 0x78;
        *(s32 *)(arg0 + 0x2E4) = 1;
        break;
    case 8:
        *(s32 *)(arg0 + 0x94) |= 0x40;
        *(s32 *)(arg0 + 0x94) &= ~0x200;
        *(s32 *)(arg0 + 0x9C) |= 0xF00;
        *(s32 *)(arg0 + 0x2E4) = 2;
        break;
    case 6:
    case 7:
        *(s32 *)(arg0 + 0x94) |= 0xE;
        *(s32 *)(arg0 + 0x94) &= ~0x410;
        *(s32 *)(arg0 + 0x9C) |= 0xEE0000;
        *(s32 *)(arg0 + 0x2E4) = 4;
        break;
    case 4:
    case 5:
        *(s32 *)(arg0 + 0x94) |= 0x80;
        *(s32 *)(arg0 + 0x94) &= ~0x500;
        *(s32 *)(arg0 + 0x2E4) = 8;
        break;
    }
}
#ifdef NON_MATCHING
void func_1501D348(s32, s32, s32, s32, s32);
void func_15022238(s16, s16, s16, f32);
s32 func_150851E0(s32, s32, s32, s16 *, s32 *, s32 *, u8 *, s32 *, s32 *, s32, s32 *);

/* was func_1507DFE4 */
void level_restart_at_start_point(s32 arg0, s32 arg1) {
    struct {
        s32 u38;
        s32 u3C;
        u8 pad40[0x4];
        s32 u44;
        s32 u48;
        u8 pad4C[0x2];
        u8 u4E;
        s32 u4F;
        u8 pad53[0x9];
        s16 u5C;
        s32 u5E;
        u8 pad62[0x2];
        s32 u64;
    } sp;
    s32 temp_t8;

    if (D_800C35EA != 1) {
        func_150851E0(0, arg0, 1, &sp.u5C, &(*(s32 *)((u8 *)&sp + 0x18)), &sp.u4F, &sp.u4E, &sp.u44, &sp.u48, 1, &sp.u38);
        if (sp.u38 == 0) {
            sp.u3C = 1;
            goto block_5;
        }
        if (sp.u38 == 1) {
            sp.u3C = 3;
block_5:
            func_15022238(sp.u5C, sp.u5E, (*(s32 *)((u8 *)&sp + 0x28)), ((f32) (sp.u4E - 0x40) * 1.40625f) + 180.0f);
            temp_t8 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            D_800C3671 = 1;
            sp.u64 = temp_t8;
            func_1501D348(0x25, sp.u3C, 0, 0, 0);
            D_800C3670 = 1;
            D_800BE9F0 = sp.u64;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/level_restart_at_start_point.s")
#endif
/* was func_1507E114 */
s32 checkpoint_get_restart_index(s32 arg0) {
    s32 sp5C;
    s32 sp54[2];
    s32 sp48[3];
    s32 sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;

    if (D_800D18A8 == 0) {
        return 0;
    }
    if ((s32)D_800BE9F4 == 0x22 || (s32)D_800BE9F4 == 0x18) {
        return 0;
    }
    D_800BE9F4 = (u16 *)(s32)(s8)D_800BE3DF;
    func_150851E0(0, D_800BE800, 1, sp54, sp48, &sp43, &sp42, &sp44, &sp3C, 1, &sp5C);
    return sp5C + 1;
}
/* was func_1507E1D0 */
void obj_get_held_point(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 *var_a2;
    f32 sp28[3];
    f32 sp1C[3];
    if ((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) {
        s32 temp_v0;
        sp28[0] = 0.0f;
        sp28[1] = (*(f32 *)((u8 *)arg0 + 0x150)) * 30.0f;
        sp28[2] = 0.0f;
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0));
        var_a2 = (*(u8 **)((u8 *)arg0 + 0x1D4));
        if (temp_v0 == 1) {
            var_a2 += 0x300;
        } else if (temp_v0 == 0x1E) {
            var_a2 += 0xC0;
        }
        func_15143134(sp28, sp1C, var_a2);
        *arg1 = sp1C[0];
        *arg2 = sp1C[1];
        *arg3 = sp1C[2];
    } else {
    *arg1 = (*(f32 *)((u8 *)arg0 + 0x14));
    *arg2 = (*(f32 *)((u8 *)arg0 + 0x18));
    *arg3 = (*(f32 *)((u8 *)arg0 + 0x1C));
    }
}
