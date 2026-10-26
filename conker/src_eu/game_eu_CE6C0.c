#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void trigger_sound_start(u8 *arg0);
s32 trigger_test_object(struct127 *arg0, u8 *arg1, s32 arg2);
s32 approx_dist3_int(s32, s32, s32);
s32 warp_request_start(struct127 *, u8, s32);
void trigger_zone_event_fire(u8 *, struct127 *, s32, u64);
void trigger_ambfx_start();
void context_action_clear(s32, s32);
void obj_set_spawn_flags(struct127 *);
void player_start_shrink_death(struct127 *);
void music_play_song(s32, s32, s32);
void context_action_set(struct127 *, u8 *, s32, s32, s32);
void rope_try_grab(struct127 *, u8 *);
void cutscene_scene_load(s32, s32, s32, s32, s32);
void os_pi_get_access(void);
void os_pi_rel_access(void);
s32 osPiRawReadIo(u32, u32 *);
extern u8 *D_800D34BC;
extern u64 D_800D34C0[3];
extern u64 D_800D34D8[3];
extern u16 D_800D34F0[16];
extern u8 **D_800D3690;
extern s32 D_800D3694;
extern s32 D_800D3698;
extern u8 D_800DF510;
extern u8 D_800DF511;
typedef struct { s16 x; s16 y; s16 z; s16 unk6; u8 pad8[8]; f32 unk10; u8 unk14; u8 unk15; u8 unk16; u8 unk17; s32 unk18; s32 unk1C; s32 unk20; f32 unk24; f32 unk28; f32 unk2C; f32 unk30; } Unk34B8; // 0x34 bytes, D_800D34B8[]
extern u64 D_800D3510[][3];


void sfx_emitter_stop_at(u16, s16, s16, s16, u16);

/* was func_150A09D0 */
void triggers_update(s32 arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a0;
    s32 var_a1;
    s32 var_s0;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_a0_2;
    u32 var_s6;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_v0;
    u8 temp_a0;
    u8 *temp_v0_3;

    var_a1 = D_800D3094;
    var_s6 = 0;
    var_s0 = 0;
    if (var_a1 != 0) {
        do {
            var_v0 = &D_800D34B8[var_s0];
            temp_a0 = (*(u8 *)((u8 *)var_v0 + 0x15));
            temp_v1 = (s32) temp_a0 >> 2;
            switch (temp_v1) {                      /* irregular */
            case 2:
                temp_v1_2 = (*(s32 *)((u8 *)var_v0 + 0x20));
                if (temp_v1_2 == 1) {
                    (*(s32 *)((u8 *)var_v0 + 0x20)) = (s32) (temp_v1_2 ^ 3);
                } else if (temp_v1_2 == 2) {
                    sfx_emitter_stop_at(((u32) (*(u32 *)((u8 *)var_v0 + 0x1C)) >> 0x10) & 0xFFFF, (*(s16 *)((u8 *)var_v0 + 0)), (*(s16 *)((u8 *)var_v0 + 2)), (*(s16 *)((u8 *)var_v0 + 4)), (*(s32 *)((u8 *)var_v0 + 0x18)));
                    (*(s32 *)((u8 *)(&D_800D34B8[var_s0]) + 0x20)) = 0;
                }
                if ((D_800C35EA == 1) && (trigger_test_object(D_800CC2D0, &D_800D34B8[var_s0], 0) == 0)) {
                    trigger_sound_start(&D_800D34B8[var_s0]);
                }
block_36:
                var_a1 = D_800D3094;
                break;
            case 7:
                if ((temp_a0 & 3) == 3) {
                    (*(s32 *)((u8 *)var_v0 + 0x20)) = 0;
                } else {
                    temp_v1_3 = (*(s32 *)((u8 *)var_v0 + 0x20));
                    if (temp_v1_3 == 1) {
                        (*(s32 *)((u8 *)var_v0 + 0x20)) = 2;
                    } else if ((temp_v1_3 == 2) && (music_song_set_chans_level((s32) (*(u8 *)((u8 *)var_v0 + 0x17)), 0, (*(s32 *)((u8 *)var_v0 + 0x18)), 0) != 0)) {
                        temp_v0 = &D_800D34B8[var_s0];
                        if (music_song_set_chans_level((s32) (*(u8 *)((u8 *)temp_v0 + 0x17)), 0x64, (*(s32 *)((u8 *)temp_v0 + 0x1C)), 0) != 0) {
                            (*(s32 *)((u8 *)(&D_800D34B8[var_s0]) + 0x20)) = 0;
                        }
                    }
                }
                goto block_36;
            case 4:
                if ((*(u8 *)((u8 *)var_v0 + 0x17)) != 9) {
                    temp_a0_2 = (*(u32 *)((u8 *)var_v0 + 0x1C));
                    temp_v1_4 = temp_a0_2 & 0xFF;
                    if (temp_v1_4 != 0) {
                        if ((*(u8 *)((u8 *)var_v0 + 0x14)) == 0) {
                            var_v1 = temp_v1_4 - 1;
                        } else {
                            var_v1 = 0;
                        }
                        (*(u32 *)((u8 *)var_v0 + 0x1C)) = (u32) ((temp_a0_2 & ~0xFF) | var_v1);
                        if (var_v1 == 0) {
                            temp_v0_2 = &D_800D34B8[var_s0];
                            D_800DDF5C[((u32) (*(u32 *)((u8 *)temp_v0_2 + 0x1C)) >> 8) & 0xFF] = 0;
                            (*(u32 *)((u8 *)temp_v0_2 + 0x1C)) = (u32) ((*(u32 *)((u8 *)temp_v0_2 + 0x1C)) & 0xFFFF0000);
                        }
                    }
                }
                var_v0 = &D_800D34B8[var_s0];
                /* fallthrough */
            case 0:
                if (((*(u8 *)((u8 *)var_v0 + 0x17)) == 0xC) && ((*(u8 *)((u8 *)var_v0 + 0x14)) == 0)) {
                    var_v1_2 = 0;
                    var_a0 = 0;
                    if (D_80082FA0 >= 0) {
                        do {
                            temp_v0_3 = var_a0 + D_800DBFF0;
                            (*(f32 *)((u8 *)temp_v0_3 + 0x93C)) = (f32) D_800D34B8[var_s0];
                            (*(f32 *)((u8 *)temp_v0_3 + 0x940)) = (f32) (*(s16 *)((u8 *)(&D_800D34B8[var_s0]) + 2));
                            (*(f32 *)((u8 *)temp_v0_3 + 0x944)) = (f32) (*(s16 *)((u8 *)(&D_800D34B8[var_s0]) + 4));
                            (*(f32 *)((u8 *)temp_v0_3 + 0x938)) = (f32) (*(s16 *)((u8 *)(&D_800D34B8[var_s0]) + 6));
                            (*(s8 *)((u8 *)temp_v0_3 + 0x948)) = 1;
                            (*(s8 *)((u8 *)temp_v0_3 + 0x949)) = (s8) (*(s32 *)((u8 *)(&D_800D34B8[var_s0]) + 0x18));
                            var_v1_2 += 1;
                            var_a0 += 0x9A0;
                        } while (D_80082FA0 >= var_v1_2);
                    }
                }
                goto block_36;
            }
            var_s6 += 1;
            var_s0 += 0x34;
        } while (var_s6 < (u32) var_a1);
    }
}
extern f32 D_8009F970;
extern f32 D_8009F974;
/* was func_150A11F4 */
void trigger_cache_angles(u8 *arg0)
{
  f32 temp_f20;
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0xC))) * D_8009F970;
  *((f32 *) (((u8 *) arg0) + 0x24)) = fast_sinf(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x28)) = fast_cosf(temp_f20);
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0x10))) * D_8009F974;
  *((f32 *) (((u8 *) arg0) + 0x2C)) = fast_sinf(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x30)) = fast_cosf(temp_f20);
}

extern f32 D_8009F978;
void reflect_queue_object(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);

/* was func_150A126C */
void trigger_reflect_queue_objects(void) {
    f32 temp_f2;
    f32 var_f0;
    s16 temp_v1;
    s32 var_s2;
    s32 var_s4;
    struct127 *var_s1;
    u32 var_s7;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 temp_v0;

    var_s7 = 0;
    var_s4 = 0;
    if (D_800D3094 != 0) {
        do {
            temp_s0 = &D_800D34B8[var_s4];
            if ((*(u8 *)((u8 *)temp_s0 + 0x14)) == 0) {
                var_s1 = D_800CC2D0;
                var_s2 = 0;
                if (((s32) (*(u8 *)((u8 *)temp_s0 + 0x15)) >> 2) == 6) {
                    do {
                        if ((var_s1->interaction_state != 0) && ((temp_v0 = var_s1->unk5, (temp_v0 == 0)) || (temp_v0 == 1)) && (trigger_test_object(var_s1, &D_800D34B8[var_s4], 1) == 0)) {
                            temp_s0_2 = &D_800D34B8[var_s4];
                            if ((*(u8 *)((u8 *)temp_s0_2 + 0x17)) == 0) {
                                temp_s0_3 = &D_800D34B8[var_s4];
                                temp_v1 = (*(s16 *)((u8 *)temp_s0_3 + 6));
                                if (approx_dist3_int((s16) (s32) (var_s1->x_position - (f32) (*(s16 *)((u8 *)temp_s0_2 + 0))), (s16) (s32) (var_s1->y_position - (f32) (*(s16 *)((u8 *)temp_s0_2 + 2))), (s16) (s32) (var_s1->z_position - (f32) (*(s16 *)((u8 *)temp_s0_2 + 4)))) < temp_v1) {
                                    temp_f2 = (f32) temp_v1;
                                    var_f0 = temp_f2 * D_8009F978;
                                    if (var_f0 > 100.0f) {
                                        var_f0 = 100.0f;
                                    }
                                    reflect_queue_object(2, var_s2, (f32) (*(s16 *)((u8 *)temp_s0_3 + 0)), (f32) (*(s16 *)((u8 *)temp_s0_3 + 2)), (f32) (*(s16 *)((u8 *)temp_s0_3 + 4)), 0.0f, (*(f32 *)((u8 *)temp_s0_3 + 0x10)), temp_f2 - var_f0, temp_f2, 255.0f);
                                }
                            } else {
                                reflect_queue_object(1, var_s2, var_s1->x_position, var_s1->unk180, var_s1->z_position, 0.0f, 0.0f, 100.0f, 150.0f, 255.0f);
                            }
                        }
                        var_s2 += 1;
                        var_s1 = (struct127 *)((u8 *)var_s1 + (0x32C));
                    } while (var_s2 != 0x19);
                }
            }
            var_s7 += 1;
            var_s4 += 0x34;
        } while (var_s7 < (u32) D_800D3094);
    }
}
/* was func_150A1520 */
u8 *ptr_offset_0x400(u8 *arg0) {
    return arg0 + 0x400;
}

s32 trigger_test_object(struct127 *, u8 *, s32);
extern f32 D_8009F97C;

/* was func_150A152C */
void trigger_camera_zones_apply(struct108 *arg0, u8 **arg1, s32 arg2) {
    struct127 sp;

    sp.x_position = arg0->unk2F8;
    sp.y_position = arg0->unk2FC;
    sp.z_position = arg0->unk300;
    sp.unk180 = sp.y_position;
    sp.old_x_position = arg0->unk304;
    sp.old_y_position = arg0->unk308;
    sp.old_z_position = arg0->unk30C;
    arg0->unk364 = D_8009F97C;
    arg0->unk84 &= ~0x40000;
    for (; arg2 != 0; arg2--, arg1++) {
        if (*arg1 == NULL) {
            continue;
        }
        if (trigger_test_object(&sp, *arg1, 0) != 0) {
            continue;
        }
        if (((*arg1)[0x15] >> 2) != 1) {
            continue;
        }
        switch ((*arg1)[0x17]) {
        case 2:
            if (1) { // fakematch: if (1) block from the permuter (constant allocation order)
                arg0->unk364 = *(s16 *)(*arg1 + 2) + *(s16 *)(*arg1 + 8);
            }
            break;
        case 0:
            arg0->unk84 |= 0x40000;
            break;
        case 6:
            arg0->unk84 &= ~0x40000;
            break;
        }
    }
}

// P45: trigger zones of a record, per frame, before its state handler (objects_run_state_handlers).
// Zones: D_800D34BC, 0x28 bytes each: u64 mask[3] (which triggers the zone allows), u8 +0x18 priority, s16 box
// +0x1A..+0x24 (x min/max, y min/max, z min/max, exclusive). w = the record's cached zone (D_800D34F0[player] - 1)
// if it still contains the position, else D_800D34D8; then every zone set in w that contains the position ANDs its
// mask in (the lowest priority one is cached for players), a zone that does not is cleared. w |= D_800D34C0 (always
// on). Then each trigger set in w (D_800D34B8, 0x34 bytes) that trigger_test_object says the record touches fires by
// kind (+0x15 >> 2) and is recorded in D_800D3510[player] (the bits of the previous frame are `prev`).
/* was func_150A16A4 */
void trigger_zones_update_object(struct127 *arg0) {
    u32 spCC;
    s32 spC8;
    struct108 *spB8;
    u64 w[3];
    u64 mask;
    u64 prev;
    u64 *ws;
    u64 *ps;
    u32 sp68;
    s32 player;
    s32 found;
    s16 x, y, z;
    u32 i;
    u32 next;
    u32 base;
    s32 k;
    u8 *zone;
    u8 *e;
    s32 off;
    s32 v;
    u32 ang;
    s32 flip;
    u8 *o;

    spCC = 1000;
    spC8 = arg0->unk127;
    spB8 = arg0->camera;
    if (spB8 == NULL) {
        spC8 = 0xFF;
    } else if (D_800D3694 != 0) {
        trigger_camera_zones_apply(spB8, D_800D3690, D_800D3694);
    }
    x = (s32)arg0->x_position;
    y = (s32)arg0->y_position;
    z = (s32)arg0->z_position;
    if (arg0->unk127 != 0xFF) {
        context_action_clear(arg0->unk127, arg0->unk127);
    }
    obj_set_spawn_flags(arg0);
    *(s16 *)((u8 *)arg0 + 0x120) = -10000;
    D_800D3698 = 0;
    player = arg0 - D_800CC2D0;
    found = 0;
    if (player < 16) {
        if (D_800D34F0[player] > 0) {
            zone = D_800D34BC + D_800D34F0[player] * 0x28 - 0x28;
            if (*(s16 *)(zone + 0x1A) < x && x < *(s16 *)(zone + 0x1C) && *(s16 *)(zone + 0x1E) < y &&
                y < *(s16 *)(zone + 0x20) && *(s16 *)(zone + 0x22) < z && z < *(s16 *)(zone + 0x24)) {
                for (k = 0; k < 3; k++) {
                    w[k] = ((u64 *)zone)[k];
                }
                found = 1;
            }
        }
        D_800D34F0[player] = 0;
    }
    ws = w;
    if (found == 0) {
        for (k = 0; k < 3; k++) {
            w[k] = D_800D34D8[k];
        }
    }
    i = 0;
    base = 0;
    mask = w[0];
    if (D_800D3094 != 0) {
        do {
            if (mask == 0) {
                base += 64;
                i = base;
                if (!(base < (u32)D_800D3094)) {
                    next = i + 1;
                    goto next1;
                }
                mask = ws[1];
                ws++;
            }
            if ((u32)mask & 1) {
                zone = D_800D34BC + i * 0x28;
                if (*(s16 *)(zone + 0x1A) < x && x < *(s16 *)(zone + 0x1C) && *(s16 *)(zone + 0x1E) < y &&
                    y < *(s16 *)(zone + 0x20) && *(s16 *)(zone + 0x22) < z && z < *(s16 *)(zone + 0x24)) {
                    for (k = 0; k < 3; k++) {
                        w[k] &= ((u64 *)zone)[k];
                    }
                    if (player < 16 && zone[0x18] < spCC) {
                        D_800D34F0[player] = i + 1;
                        spCC = zone[0x18];
                    }
                } else {
                    *ws ^= 1ULL << (i - base);
                }
            }
            next = i + 1;
            mask >>= 1;
        next1:
            i = next;
        } while (next < (u32)D_800D3094);
        ws = w;
        base = 0;
    }
    for (k = 0; k < 3; k++) {
        w[k] |= D_800D34C0[k];
    }
    if (player < 16) {
        ps = D_800D3510[player];
        prev = *ps;
        *ps = 0;
    } else {
        ps = NULL;
        prev = 0; // P47: the asm leaves prev (sp+0x80) uninitialised for players >= 16; 0 = what the zeroed difftest stack gives
    }
    i = 0;
    mask = w[0];
    if (D_800D3094 != 0) {
        do {
            if (mask == 0) {
                base += 64;
                i = base;
                if (!(base < (u32)D_800D3094)) {
                    next = i + 1;
                    goto next2;
                }
                mask = ws[1];
                ws++;
                if (ps != NULL) {
                    prev = ps[1];
                    ps++;
                    *ps = 0;
                }
            }
            if (((u32)mask & 1) && (off = i * 0x34, trigger_test_object(arg0, D_800D34B8 + off, 0) == 0)) {
                e = D_800D34B8 + off;
                v = e[0x15] >> 2;
                if (v < 26) {
                    switch (v) {
                    case 0:
                        if (spB8 != NULL && e[0x17] != 0xC) {
                            camera_queue_event(spB8, 1, D_800D34B8 + off);
                            *(u16 *)((u8 *)spB8 + 0x700) = i;
                        }
                        break;
                    case 1:
                        if (e[0x17] < 10) {
                            switch (e[0x17]) {
                            case 0:
                                arg0->unkF8 &= ~4;
                                break;
                            case 1:
                                arg0->unkF8 &= ~2;
                                break;
                            case 2:
                                *(s16 *)((u8 *)arg0 + 0x120) = *(s16 *)(e + 8) + *(s16 *)(e + 2);
                                break;
                            case 3:
                                arg0->unkF8 |= 2;
                                break;
                            case 4:
                                player_start_shrink_death(arg0);
                                break;
                            case 5:
                                o = (u8 *)arg0->unk31C;
                                if (o[0x95] == 0 && *((u8 *)arg0 + 0x104) == 0 && *((u8 *)arg0 + 0x1CA) != 0 &&
                                    *((u8 *)arg0 + 0x89) == 0 && (o[0x11A] == 0 || D_800BE9F0 == 6) &&
                                    8.0f < *(f32 *)((u8 *)arg0 + 0x44)) {
                                    flip = 0;
                                    ang = ((u32)(*(f32 *)(e + 0x10) * 182.04445f) - *(u16 *)(o + 0x4C)) & 0xFFFF;
                                    if ((f32)(*(s16 *)(e + 8) + *(s16 *)(e + 2)) < arg0->y_position + 250.0f &&
                                        *(f32 *)((u8 *)arg0 + 0x28) == 0.0f) {
                                        ang = (ang - 0x8000) & 0xFFFF;
                                        flip = 1;
                                    }
                                    if ((s32)ang >= 0x2001 && (s32)ang < 0x6000) {
                                        o[0x97] = flip;
                                        ((u8 *)arg0->unk31C)[0x96] = 0;
                                        *((u8 *)arg0 + 0x8A) = 0x12;
                                        ((u8 *)arg0->unk31C)[0x95] = i + 1;
                                        if (*(s32 *)(D_800D34B8 + off + 0x18) != 0) {
                                            o = (u8 *)arg0->unk31C;
                                            o[0x95] |= 0x80;
                                        }
                                    }
                                }
                                break;
                            case 6:
                                arg0->unkF8 |= 4;
                                break;
                            case 7:
                                arg0->unkF4 |= 0x100000;
                                break;
                            case 8:
                                if (*(s32 *)(e + 0x18) != 0) {
                                    D_800DF511 |= 1 << player;
                                } else {
                                    D_800DF510 |= 1 << player;
                                }
                                break;
                            case 9:
                                arg0->unkF8 |= 0x08000000;
                                break;
                            }
                        }
                        break;
                    case 2:
                        trigger_sound_start(D_800D34B8 + off);
                        break;
                    case 3:
                        if (e[0x17] == 5) {
                            rope_try_grab(arg0, D_800D34B8 + off);
                        }
                        break;
                    case 4:
                        trigger_ambfx_start(D_800D34B8 + off, spC8);
                        break;
                    case 7:
                        if (*(s32 *)(e + 0x20) == 0) {
                            if (music_song_set_chans_level(e[0x17], 100, *(s32 *)(e + 0x18), 0) != 0) {
                                e = D_800D34B8 + off;
                                if (music_song_set_chans_level(e[0x17], 0, *(s32 *)(e + 0x1C), 0) != 0) {
                                    *(s32 *)(D_800D34B8 + off + 0x20) = 1;
                                }
                            }
                        } else {
                            *(s32 *)(e + 0x20) = 1;
                        }
                        break;
                    case 8:
                        os_pi_get_access();
                        osPiRawReadIo((u32)ptr_offset_0x400((u8 *)0xB0000054), &sp68);
                        os_pi_rel_access();
                        if (ptr_offset_0x400((u8 *)sp68) == (u8 *)0x01090C2B && D_800C35EA == 0 &&
                            *((u8 *)arg0 + 0x1CA) != 0) {
                            e = D_800D34B8 + off;
                            warp_request_start(arg0, e[0x17], *(s32 *)(e + 0x18));
                            if (D_800BE9F0 != (D_800D34B8 + off)[0x17]) {
                                *((u8 *)arg0 + 0x125) = 0xFF;
                                *(f32 *)((u8 *)arg0 + 0x1CC) = arg0->y_position;
                            }
                        }
                        break;
                    case 11:
                        context_action_set(arg0, D_800D34B8 + off, 1, e[0x17], *(s32 *)(e + 0x18));
                        break;
                    case 12:
                        trigger_zone_event_fire(D_800D34B8 + off, arg0, spC8, prev);
                        break;
                    case 13:
                        if (spC8 != 0xFF && !((u32)prev & 1) && D_800E0B94 == 0 && *((u8 *)arg0 + 0x1CA) != 0 &&
                            D_800C35EA == 0) {
                            if (e[0x17] == 0) {
                                e[0x14] = 1;
                                e = D_800D34B8 + off;
                            }
                            cutscene_scene_load(D_800BE9F0, *(s32 *)(e + 0x18), 0, 0, 0);
                            e = D_800D34B8 + off;
                            *(s32 *)(e + 0x1C) += 1;
                        }
                        break;
                    case 14:
                        if (spC8 != 0xFF && !((u32)prev & 1)) {
                            music_play_song(e[0x17], *(s32 *)(e + 0x18), *(s32 *)(e + 0x1C) & 0xFF);
                            e = D_800D34B8 + off;
                            if (e[0x17] != 0) {
                                music_song_set_chans_level(e[0x17], 0, *(s32 *)(e + 0x20) & 0xFFFF, 0);
                            }
                        }
                        break;
                    case 25:
                        if (e[0x17] == 0) {
                            D_80041FD8 = *(s32 *)(e + 0x18);
                        }
                        break;
                    }
                }
                if (ps != NULL) {
                    *ps |= 1ULL << (i - base);
                }
            }
            next = i + 1;
            mask >>= 1;
            prev >>= 1;
        next2:
            i = next;
        } while (next < (u32)D_800D3094);
    }
}
s32 approx_dist3_int(s32, s32, s32);
s32 approx_dist2_int(s16, s16, s32, s32);

/* was func_150A2280 */
s32 trigger_test_object(struct127 *arg0, u8 *arg1, s32 arg2) {
    s16 sp5E;
    s16 sp5C;
    s16 sp5A;
    s16 sp58;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp2C;
    f32 sp24;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f10_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f16_4;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f18_3;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f6;
    s16 temp_v0;
    s16 temp_v1;
    s16 var_t0;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f4_3;
    s32 temp_f6_2;
    s32 temp_f8;
    s32 temp_f8_2;
    s32 temp_t2;

    if (((*(u8 *)((u8 *)arg1 + 0x14)) == 1) || (arg0 == NULL) || (arg1 == NULL)) {
        goto block_35;
    }
    var_t0 = 0;
    sp2C = (f32) (*(s16 *)((u8 *)arg1 + 0));
    sp5E = (s16) (s32) (arg0->x_position - sp2C);
    temp_f0 = arg0->y_position;
    sp24 = (f32) (*(s16 *)((u8 *)arg1 + 2));
    sp5C = (s16) (s32) (temp_f0 - sp24);
    sp20 = (f32) (*(s16 *)((u8 *)arg1 + 4));
    sp5A = (s16) (s32) (arg0->z_position - sp20);
    if (arg2 != 0) {
        var_t0 = arg0->unkE4;
    }
    if (!((*(u8 *)((u8 *)arg1 + 0x16)) & 1) || (((f32) (s32) temp_f0 - arg0->unk180) <= 5.0f)) {
        temp_t2 = (*(u8 *)((u8 *)arg1 + 0x15)) & 3;
        switch (temp_t2) {                          /* irregular */
        case 0:
            if (((*(f32 *)((u8 *)arg1 + 0xC)) > 0.01f) || ((*(f32 *)((u8 *)arg1 + 0x10)) > 0.01f)) {
                temp_f12 = (*(f32 *)((u8 *)arg1 + 0x30));
                temp_f0_2 = (f32) sp5E;
                temp_f2 = (*(f32 *)((u8 *)arg1 + 0x2C));
                temp_f14 = (f32) sp5A;
                sp44 = temp_f0_2;
                sp5E = (s16) (s32) ((temp_f0_2 * temp_f12) - (temp_f14 * temp_f2));
                temp_f18 = (temp_f14 * temp_f12) + (sp44 * temp_f2);
                temp_f12_2 = (*(f32 *)((u8 *)arg1 + 0x28));
                temp_f2_2 = (*(f32 *)((u8 *)arg1 + 0x24));
                temp_f16 = (f32) sp5C;
                sp5A = (s16) (s32) ((temp_f18 * temp_f12_2) - (temp_f16 * temp_f2_2));
                sp5C = (s16) (s32) ((temp_f16 * temp_f12_2) + (temp_f18 * temp_f2_2));
            }
            sp58 = var_t0;
            if ((approx_dist2_int(sp5E, sp5A, 0, 0) < ((*(s16 *)((u8 *)arg1 + 6)) + var_t0)) && (sp5C > 0) && (sp5C < (*(s16 *)((u8 *)arg1 + 8)))) {
                return 0;
            }
            goto block_35;
        case 1:
            sp58 = var_t0;
            if (approx_dist3_int(sp5E, sp5C, sp5A) < ((*(s16 *)((u8 *)arg1 + 6)) + var_t0)) {
                return 0;
            }
            goto block_35;
        case 2:
            temp_f12_3 = (*(f32 *)((u8 *)arg1 + 0x30));
            temp_f0_3 = (f32) sp5E;
            temp_f2_3 = (*(f32 *)((u8 *)arg1 + 0x2C));
            temp_f14_2 = (f32) sp5A;
            sp44 = temp_f0_3;
            temp_f4 = (s32) ((temp_f0_3 * temp_f12_3) - (temp_f14_2 * temp_f2_3));
            sp5E = (s16) temp_f4;
            temp_v0 = (*(s16 *)((u8 *)arg1 + 6));
            if (((s16) temp_f4 < (temp_v0 + var_t0)) && ((-temp_v0 - var_t0) < (s16) temp_f4)) {
                temp_f12_4 = (*(f32 *)((u8 *)arg1 + 0x28));
                temp_f2_4 = (*(f32 *)((u8 *)arg1 + 0x24));
                temp_f16_2 = (f32) sp5C;
                temp_f18_2 = (temp_f14_2 * temp_f12_3) + (sp44 * temp_f2_3);
                sp44 = temp_f16_2;
                temp_v1 = (*(s16 *)((u8 *)arg1 + 0xA));
                temp_f4_2 = (s32) ((temp_f18_2 * temp_f12_4) - (temp_f16_2 * temp_f2_4));
                if (((s16) temp_f4_2 < (temp_v1 + var_t0)) && ((-temp_v1 - var_t0) < (s16) temp_f4_2)) {
                    temp_f10 = (s32) ((sp44 * temp_f12_4) + (temp_f18_2 * temp_f2_4));
                    if (((s16) temp_f10 < (*(s16 *)((u8 *)arg1 + 8))) && ((s16) temp_f10 > 0)) {
                        return 0;
                    }
                }
            }
            goto block_35;
        case 3:
            temp_f12_5 = (*(f32 *)((u8 *)arg1 + 0x30));
            temp_f2_5 = (*(f32 *)((u8 *)arg1 + 0x2C));
            temp_f0_4 = (f32) sp5E;
            temp_f14_3 = (f32) sp5A;
            sp44 = temp_f0_4;
            temp_f16_3 = (f32) (s16) (s32) (arg0->old_x_position - sp2C);
            temp_f18_3 = (f32) (s16) (s32) (arg0->old_z_position - sp20);
            sp38 = temp_f16_3;
            temp_f8 = (s32) ((temp_f0_4 * temp_f12_5) - (temp_f14_3 * temp_f2_5));
            sp5E = (s16) temp_f8;
            temp_f10_2 = (s32) ((temp_f16_3 * temp_f12_5) - (temp_f18_3 * temp_f2_5));
            temp_f10_3 = (temp_f14_3 * temp_f12_5) + (sp44 * temp_f2_5);
            sp40 = temp_f10_3;
            temp_f6 = (temp_f18_3 * temp_f12_5) + (sp38 * temp_f2_5);
            sp34 = temp_f6;
            temp_f16_4 = (f32) sp5C;
            temp_f12_6 = (*(f32 *)((u8 *)arg1 + 0x28));
            temp_f2_6 = (*(f32 *)((u8 *)arg1 + 0x24));
            sp44 = temp_f16_4;
            temp_f0_5 = (f32) (s16) (s32) (arg0->old_y_position - sp24);
            temp_f8_2 = (s32) ((temp_f10_3 * temp_f12_6) - (temp_f16_4 * temp_f2_6));
            sp38 = temp_f0_5;
            temp_f6_2 = (s32) ((temp_f6 * temp_f12_6) - (temp_f0_5 * temp_f2_6));
            if (((s16) temp_f6_2 < 0) && ((s16) temp_f8_2 >= 0)) {
                temp_f14_4 = (f32) (s16) temp_f6_2 / (f32) ((s16) temp_f6_2 - (s16) temp_f8_2);
                if (fabsf((f32) (s16) temp_f10_2 + (temp_f14_4 * (f32) ((s16) temp_f8 - (s16) temp_f10_2))) < (f32) (*(s16 *)((u8 *)arg1 + 6))) {
                    temp_f4_3 = (s32) ((sp38 * temp_f12_6) + (sp34 * temp_f2_6));
                    temp_f0_6 = (f32) (s16) temp_f4_3 + (temp_f14_4 * (f32) ((s16) (s32) ((sp44 * temp_f12_6) + (temp_f10_3 * temp_f2_6)) - (s16) temp_f4_3));
                    if ((temp_f0_6 >= 0.0f) && (temp_f0_6 < (f32) (*(s16 *)((u8 *)arg1 + 8)))) {
                        return 0;
                    }
                }
            }
            goto block_35;
        }
    } else {
block_35:
        return 1;
    }
}
/* was func_150A28C4 */
void trigger_sound_start(u8 *arg0)
{
  int new_var;
  s32 var_t0;
  s32 var_v1;
  u32 temp_v0;
  u8 temp_t1;
  if ((*((s32 *) (((u8 *) arg0) + 0x20))) == 0)
  {
    var_v1 = 0;
    var_t0 = 8;
    if (!((*((u8 *) (((u8 *) arg0) + 0x15))) & 3))
    {
      var_v1 = 0x8000;
    }
    temp_t1 = *((u8 *) (((u8 *) arg0) + 0x17));
    if ((((s32) temp_t1) >> (new_var = 7)) != 0)
    {
      var_t0 = 0x108;
    }
    temp_v0 = *((u32 *) (((u8 *) arg0) + 0x1C));
    sfx_emitter_start((temp_v0 >> 0x10) & ((short) 0xFFFF), *((s16 *) (((u8 *) arg0) + 0)), *((s16 *) (((u8 *) arg0) + 2)), *((s16 *) (((u8 *) arg0) + 4)), (temp_t1 & 0x7F) * 0x147, (u16) ((*((s32 *) (((u8 *) arg0) + 0x18))) | var_v1), (s16) (temp_v0 & 0xFFFF), 0, 0, 0, var_t0, 0);
    *((s32 *) (((u8 *) arg0) + 0x20)) = 1;
 dummy_label_636436: ;
    return;
  }
  *((s32 *) (((u8 *) arg0) + 0x20)) = 1;
}

s32 ambfx_effect_start(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
/* was func_150A29A0 */
void trigger_ambfx_start(Unk34B8 *arg0, s32 arg1) {
    s32 v;
    s32 r;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 g;
    s32 w;

    if (arg1 != 0xFF) {
        w = arg0->unk1C;
        v = w & 0xFF;
        if (v == 0 || arg0->unk17 == 9) {
            g = arg0->unk17;
            a = arg0->unk18 & 0xFF;
            b = *(s16 *)&arg0->unk18;
            c = ((u8 *)&arg0->unk18)[2];
            d = ((u8 *)&arg0->unk1C)[0];
            e = ((u8 *)&arg0->unk1C)[1];
            f = arg0->unk20;
            r = ambfx_effect_start(arg0->x, arg0->y + (e << 4), arg0->z, a, g, arg0->unk6, arg1, b, c, d, f);
            if (r != -1 && arg0->unk17 != 9) {
                arg0->unk1C = ((r << 8) | 0xF0) | (arg0->unk1C & 0xFFFF0000);
            }
        } else {
            r = v;
            w = arg0->unk1C; // fakematch: re-read of the word swaps v/r into a0/v0
            if (v < 2) {
                r = 2;
            }
            arg0->unk1C = (w & ~0xFF) | r;
        }
    }
}

void arc_spark_spawn(struct127 *, s32, u8 *, u8);
void spout_check_obj_hit(struct127 *, u8 *);
extern u8 D_800D34B0;
extern s32 D_800DA2D8;

/* was func_150A2AB4 */
void trigger_zone_event_fire(u8 *arg0, struct127 *arg1, s32 arg2, u64 arg4) { // P45: was `s32 arg5` (read a3); the asm reads the low word of a u64 at sp+0x14
    u16 temp_v0_2;
    u8 temp_t1;
    u8 temp_t6;
    u8 *temp_v0;

    temp_t6 = (*(u8 *)((u8 *)arg0 + 0x17));
    switch (temp_t6) {
    case 1:
        if (arg2 != 0xFF) {
            screen_lightning_random_flash(arg2, 0xFF, 0);
            return;
        }
    default:
        return;
    case 2:
        if (arg2 != 0xFF) {
            temp_v0 = ((s32 *)((u8 *)&D_800DA2D8 + (arg2 * 3)));
            (*(s8 *)((u8 *)temp_v0 + 0)) = (s8) (*(s32 *)((u8 *)arg0 + 0x18));
            (*(s8 *)((u8 *)temp_v0 + 1)) = (s8) (*(s32 *)((u8 *)arg0 + 0x1C));
            (*(s8 *)((u8 *)temp_v0 + 2)) = (s8) (*(s32 *)((u8 *)arg0 + 0x20));
            return;
        }
        break;
    case 3:
        if (arg2 != 0xFF) {
            arc_spark_spawn(arg1, arg2, arg0, (*(u8 *)((u8 *)arg0 + 0x1B)));
            return;
        }
        break;
    case 6:
        if (!(arg4 & 1)) {
            D_800D34B0 = 0x19;
            actor_sound_play2(0x66FU, arg1, 0x5DC0, 0x190, 0x1F4U);
        }
        temp_t1 = (D_800D34B0 + D_800BE9E4) & 0xFF;
        D_800D34B0 = temp_t1;
        if ((s32) temp_t1 >= 0x1A) {
            temp_v0_2 = arg1->unkB2;
            if ((s32) temp_v0_2 >= 0x5A1) {
                arg1->unkB2 = 0x4B0;
            } else if ((s32) temp_v0_2 < 0xF1) {
                arg1->unkB2 = 0x5A;
            } else {
                arg1->unkB2 = temp_v0_2 - 0xF0;
            }
            D_800D34B0 = 0;
            return;
        }
        break;
    case 8:
        laser_test_obj_broadcast(arg1, arg0);
        return;
    case 9:
        obj_kind9_dispatch(arg1, arg0);
        return;
    case 10:
        spout_check_obj_hit(arg1, arg0);
        break;
    }
}
s32 trigger_test_object(struct127 *, u8 *, s32);
s32 warp_request_start(struct127 *, u8, s32);

/* was func_150A2C6C */
void trigger_warp_check(u8 *arg0)
{
  int new_var;
  s32 var_s0;
  u32 var_s1;
  u8 *temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0x65))) == 0)
  {
    var_s1 = 0;
    var_s0 = 0;
    if (D_800D3094 != 0)
    {
      do
      {
        new_var = var_s0 ^ 0;
        if (((((s32) (*((u8 *) (((u8 *) (&D_800D34B8[new_var])) + 0x15)))) >> 2) == 8) && (trigger_test_object(arg0, &D_800D34B8[var_s0 & 0xFFFFFFFF], 0) == 0))
        {
          temp_v0 = &D_800D34B8[var_s0];
          warp_request_start(arg0, *((u8 *) (((u8 *) temp_v0) + 0x17)), *((s32 *) (((u8 *) temp_v0) + 0x18)));
        }
        var_s1 += 1;
        var_s0 += 0x34;
      }
      while (var_s1 < ((u32) D_800D3094));
    }
  }
}

/* was func_150A2D44 */
void trigger_set_disabled(s32 arg0, s32 arg1) {
    s32 i;

    arg0 &= 0xFFF;
    if ((u32)arg0 < (u32)D_800D3094) {
        ((Unk34B8 *)D_800D34B8)[arg0].unk14 = arg1;
    }
    if (arg1 == 1) {
        for (i = 0; i < 16; i++) {
            D_800D3510[i][(u32)arg0 >> 6] &= ~(1ULL << ((u32)arg0 & 0x3F));
        }
    }
}

/* was func_150A2E20 */
void trigger_set_kind_args(s32 arg0, s32 arg1, int arg2)
{
  s32 temp_v0;
  int new_var;
  int new_var2;
  new_var = 1;
  arg0 = arg0 & 0xFFF;
  if (arg0 < ((u32) D_800D3094))
  {
    new_var2 = -new_var;
    if (arg1 != (-new_var))
    {
      *((s32 *) (((u8 *) (D_800D34B8 + ((13 * arg0) * 4))) + 0x18)) = arg1;
    }
    temp_v0 = arg0 * 0x34;
    if (arg2 != new_var2)
    {
      *((s8 *) (((u8 *) (D_800D34B8 + temp_v0)) + 0x17)) = arg2;
    }
    *((s32 *) (((u8 *) (D_800D34B8 + temp_v0)) + 0x1C)) = 0;
  }
}

extern u64 D_800D3510[][3];

/* was func_150A29C8 */
s32 trigger_test_player(s32 arg0, s32 arg1) {
    arg1 &= 0xFFF;
    if ((u32)D_800D3094 < (u32)arg1) {
        return 1;
    }
    if ((u32)arg0 < 16 && ((u16)D_800D2340 & (1 << arg0))) {
        if ((D_800D3510[(u32)arg0][(u32)arg1 >> 6] >> ((u32)arg1 & 0x3F)) & 1) {
            return 0;
        }
        return 1;
    }
    return trigger_test_object(&D_800CC2D0[arg0], D_800D34B8 + arg1 * 0x34, 1);
}

/* was func_150A2FCC */
s32 trigger_first_touched(u32 arg0, s32 arg1, s32 *arg2) {
    s32 i;
    u32 v;

    if (arg0 < 16 && ((u16)D_800D2340 & (1 << arg0))) {
        for (i = 0; i < arg1; i++) {
            v = arg2[i] & 0xFFF;
            if (v < (u32)D_800D3094) {
                if ((D_800D3510[arg0][v >> 6] >> (v & 0x3F)) & 1) {
                    return v;
                }
            }
        }
    } else {
    for (i = 0; i < arg1; i++) {
        v = arg2[i] & 0xFFF;
        if (v < (u32)D_800D3094) {
            if (trigger_test_object(&D_800CC2D0[arg0], D_800D34B8 + v * 0x34, 1) == 0) {
                return v;
            }
        }
    }
    }
    return -1;
}

/* was func_150A3184 */
s32 trigger_find_touching_player(s32 arg0) {
    s32 i;

    arg0 &= 0xFFF;
    if ((u32)D_800D3094 < arg0) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (*(u16 *)((u8 *)&D_800D2138 + 0x208) & (1 << i)) {
            if ((D_800D3510[i][(u32)arg0 >> 6] >> ((u32)arg0 & 0x3F)) & 1) {
                return i;
            }
        }
    }
    return -1;
}

s32 trigger_test_object(struct127 *, u8 *, s32);

/* was func_150A3264 */
s32 trigger_test_camera(s32 arg0, u32 arg1) {
    struct108 *e;
    struct127 sp;

    e = &D_800DBFF0[arg0];
    arg1 &= 0xFFF;
    if ((u32)D_800D3094 < arg1) {
        return 1;
    }
    sp.x_position = e->unk2F8;
    sp.y_position = e->unk2FC;
    sp.z_position = e->unk300;
    sp.unk180 = sp.y_position;
    sp.old_x_position = e->unk304;
    sp.old_y_position = e->unk308;
    sp.old_z_position = e->unk30C;
    return trigger_test_object(&sp, D_800D34B8 + arg1 * 0x34, 0);
}

/* was func_150A332C */
s32 trigger_plane_side(Unk34B8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_f14;

    temp_f14 = arg2 - (f32) arg0->y;
    arg3 = temp_f14 - (f32) arg0->z;
    if (((((arg3 * arg0->unk30) + ((arg1 - (f32) arg0->x) * arg0->unk2C)) * arg0->unk28) - (temp_f14 * arg0->unk24)) <= 0.0f) {
        return 1;
    }
    return 0;
}
s32 trigger_plane_side(Unk34B8 *, f32, f32, f32);
/* was func_150A33C4 */
s32 trigger_plane_side_object(s32 arg0, s32 arg1) {
    arg1 &= 0xFFF;
    if ((u32) D_800D3094 < arg1) {
        return 1;
    }
    if ((((Unk34B8 *) D_800D34B8)[arg1].unk15 & 3) == 3) {
        return trigger_plane_side(arg1 + (Unk34B8 *) D_800D34B8, D_800CC2D0[arg0].x_position, D_800CC2D0[arg0].y_position, D_800CC2D0[arg0].z_position);
    }
    return 0;
}

s32 trigger_plane_side(Unk34B8 *, f32, f32, f32);
/* was func_150A3484 */
s32 trigger_plane_side_camera(s32 arg0, s32 arg1) {
    struct108 *v = &D_800DBFF0[arg0];

    arg1 &= 0xFFF;
    if ((u32) D_800D3094 < arg1) {
        return 1;
    }
    if ((((Unk34B8 *) D_800D34B8)[arg1].unk15 & 3) == 3) {
        return trigger_plane_side(arg1 + (Unk34B8 *) D_800D34B8, v->unk2F8, v->unk2FC, v->unk300);
    }
    return 0;
}


/* was func_150A3538 */
s32 trigger_point_in_kind3(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u32 i;
    struct127 sp;

    sp.x_position = sp.old_x_position = (f32)arg1;
    sp.y_position = sp.old_y_position = (f32)arg2;
    sp.z_position = sp.old_z_position = (f32)arg3;
    sp.unk180 = sp.y_position;
    for (i = 0; i < (u32)D_800D3094; i++) {
        if (((Unk34B8 *)D_800D34B8)[i].unk14 == 0 && (((Unk34B8 *)D_800D34B8)[i].unk15 >> 2) == 3 && ((Unk34B8 *)D_800D34B8)[i].unk17 == arg0 && trigger_test_object(&sp, D_800D34B8 + i * 0x34, 0) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 trigger_test_object(struct127 *, u8 *, s32);

/* was func_150A3674 */
u8 *trigger_find_at_point(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 i;
    struct127 sp;

    sp.x_position = sp.old_x_position = (f32)arg2;
    sp.y_position = sp.old_y_position = (f32)arg3;
    sp.z_position = sp.old_z_position = (f32)arg4;
    sp.unk180 = sp.y_position;
    for (i = 0; i < (u32)D_800D3094; i++) {
        if (((Unk34B8 *)D_800D34B8)[i].unk14 == 0 && (((Unk34B8 *)D_800D34B8)[i].unk15 >> 2) == arg0 && ((Unk34B8 *)D_800D34B8)[i].unk17 == arg1 && trigger_test_object(&sp, D_800D34B8 + i * 0x34, 0) == 0) {
            return D_800D34B8 + i * 0x34;
        }
    }
    return NULL;
}

/* was func_150A3794 */
s32 trigger_contains_point(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 sp24;
    u8 *new_var; // fakematch: pointer to the local struct for the 0x180 store
    s32 pad[2];
    sp24.x_position = (sp24.old_x_position = (f32)arg1);
    sp24.y_position = (sp24.old_y_position = (f32)arg2);
    sp24.z_position = (sp24.old_z_position = (f32)arg3);
    new_var = (u8 *)&sp24;
    *(f32 *)(new_var + 0x180) = sp24.y_position;
    if (0 == trigger_test_object((u8 *)&sp24, arg0, 0)) {
        return (unsigned int)1; // fakematch: permuter artifact (cast)
    }
    return 0;
}

/* was func_150A3810 */
void trigger_get_fields(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *arg1 = (s32) (*(u8 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x17));
    *arg2 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x18));
    *arg3 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x1C));
    *arg4 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x20));
}

/* was func_150A3878 */
void trigger_set_fields_masked(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 & 1) {
        *(s8 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x17) = arg2;
    }
    if (arg1 & 2) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x18) = arg3;
    }
    if (arg1 & 4) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x1C) = arg4;
    }
    if (arg1 & 8) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x20) = arg5;
    }
}

/* was func_150A3924 */
void trigger_set_position(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *(s16 *)(D_800D34B8 + temp_v0) = arg1;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 2)) = arg2;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 4)) = arg3;
}

s32 trigger_cylinder_segment_hit(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);

/* was func_150A3990 */
s32 trigger_segment_hit(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (arg0[0x14] == 1) {
        return 0;
    }
    if (!(arg0[0x15] & 3)) {
        return trigger_cylinder_segment_hit(arg0, arg1, arg2, arg3);
    }
    return 0;
}

/* collision cylinder (0x34-byte entries of D_800D34B8, see trigger_set_position / trigger_cache_angles) */
typedef struct {
    s16 x, y, z;    /* base centre */
    s16 radius;
    s16 height;     /* top, above the base */
    s16 pad0A;
    f32 angleX;     /* 0x0C: degrees, sin/cos at 0x24/0x28 */
    f32 angleY;     /* 0x10: degrees, sin/cos at 0x2C/0x30 */
    u8 pad14[0x10];
    f32 sinX;       /* 0x24 */
    f32 cosX;
    f32 sinY;
    f32 cosY;       /* 0x30 */
} CollCylinder;

static const f32 D_8009FA44_nm[1] = { 0.017453292f }; /* 0x3C8EFA35: pi / 180 */
static const f32 D_8009FA48_nm[1] = { 0.017453292f }; /* 0x3C8EFA35 */

// cylinder_segment_hit: intersects the segment p0 -> p1 with the rotated cylinder cyl; on a hit writes the entry
// point (world coordinates) to out and returns 1, else returns 0 (out untouched).
/* was func_150A39E4 */
s32 trigger_cylinder_segment_hit(u8 *arg0, f32 *p0, f32 *p1, f32 *out) {
    CollCylinder *cyl = (CollCylinder *) arg0;
    f32 local[2][3]; /* p0, p1 in cylinder space */
    f32 *src;
    f32 dx, dy, dz;
    f32 x0, y0, z0;
    f32 sx, sy, sz;
    f32 inv;
    f32 tmin, tmax, tmp;
    f32 a, b, disc, root, half;
    f32 s0, s1;
    f32 t;
    f32 hx, hy, hz;
    f32 angle, sn, cs;
    s32 i;

    for (i = 0; i < 2; i++) {
        src = (i == 0) ? p0 : p1;
        dx = src[0] - cyl->x;
        dy = src[1] - cyl->y;
        dz = src[2] - cyl->z;
        local[i][0] = dx * cyl->cosY - dz * cyl->sinY;
        dz = dz * cyl->cosY + dx * cyl->sinY;
        local[i][2] = dz * cyl->cosX - dy * cyl->sinX;
        local[i][1] = dy * cyl->cosX + dz * cyl->sinX;
    }
    x0 = local[0][0];
    y0 = local[0][1];
    z0 = local[0][2];
    sx = local[1][0] - x0;
    sy = local[1][1] - y0;
    sz = local[1][2] - z0;

    /* segment range [tmin, tmax] between the base (y 0) and the top (y height) */
    if (sy != 0.0f) {
        inv = 1.0f / sy;
        tmin = -y0 * inv;
        tmax = (cyl->height - y0) * inv;
        if (tmax < tmin) {
            tmp = tmin;
            tmin = tmax;
            tmax = tmp;
        }
        if (tmax < 0.0f || 1.0f < tmin) {
            return 0;
        }
        if (tmin < 0.0f) {
            tmin = 0.0f;
        }
        if (1.0f < tmax) {
            tmax = 1.0f;
        }
    } else {
        if (y0 < 0.0f || (f32) cyl->height < y0) {
            return 0;
        }
        tmin = 0.0f;
        tmax = 1.0f;
    }

    /* segment range [s0, s1] inside the circle x^2 + z^2 = radius^2 */
    a = sz * sz + sx * sx;
    if (a == 0.0f) {
        return 0;
    }
    b = 2.0f * (z0 * sz + sx * x0);
    disc = b * b - ((z0 * z0 + x0 * x0) - (f32) (cyl->radius * cyl->radius)) * (4.0f * a);
    if (disc < 0.0f) {
        return 0;
    }
    root = sqrtf(disc);
    half = 0.5f / a;
    s0 = (-b + root) * half;
    s1 = (-b - root) * half;
    if (s1 < s0) {
        tmp = s0;
        s0 = s1;
        s1 = tmp;
    }
    if (s1 < 0.0f || 1.0f < s0) {
        return 0;
    }
    if (s0 < 0.0f) {
        s0 = 0.0f;
    }
    if (1.0f < s1) {
        s1 = 1.0f;
    }
    if (s1 < tmin || tmax < s0) {
        return 0;
    }
    t = (s0 < tmin) ? tmin : s0;

    hx = sx * t + x0;
    hy = sy * t + y0;
    hz = sz * t + z0;
    /* back to world space: undo the X tilt, then the Y turn */
    angle = -(cyl->angleX * D_8009FA44_nm[0]);
    sn = fast_sinf(angle);
    cs = fast_cosf(angle);
    out[2] = hz * cs - hy * sn;
    out[1] = hy * cs + hz * sn;
    angle = -(cyl->angleY * D_8009FA48_nm[0]);
    sn = fast_sinf(angle);
    cs = fast_cosf(angle);
    out[0] = hx * cs - out[2] * sn;
    out[2] = out[2] * cs + hx * sn;
    out[0] += cyl->x;
    out[1] += cyl->y;
    out[2] += cyl->z;
    return 1;
}
