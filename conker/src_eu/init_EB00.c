#include <ultra64.h>

#include "functions.h"
#include "variables.h"
typedef struct { s32 x; s32 y; s32 z; s32 ex; s32 ey; s32 ez; f32 f; } SfxListener; // size 0x1C
extern SfxListener D_80042308[];
typedef struct {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    s32 (*unk14)(struct15 *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 pad2A;
    f32 unk2C;
} SfxEnt; // size 0x30
extern u8 D_800BEA35;
s32 sound_path_calc_pan_volume(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 *argA, u32 *argB, u32 *argC);

extern s32 D_80042B00;
void sound_stop_queue_process(void);
void sfx_emitters_update(struct15 *arg0, s32 *arg1, s32 arg2, s32 arg3);
typedef struct { s32 unk0; u8 pad4[0x10]; f32 unk14; f32 unk18; f32 unk1C; u8 pad20[0x64]; u16 unk84; u8 pad86[0xFE]; u32 unk184; } SfxObj;


/* was func_1000EB00 */
s32 sfx_cb_ambient_random_chirp(struct04 *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg6, s32 arg7, u16 *arg8) {
    if (arg0->unk24 != 0) {
        arg0->unk24 = 0;
    }
    *arg3 = 64;
    if (D_800CC37D || (*arg2 == 0)) {
        *arg2 = 0;
        *arg8 = 0;
        return 0;
    }
    arg0->unk18 -= g_frame_ticks;
    if (arg0->unk18 > 0) {
        *arg2 = 0;
        *arg8 = 0;
    } else {
        arg0->unk18 = (random_int() & 0x7F) + 0x80;
        arg0->unk0 = (random_int() % 3U) + 0x6C;
    }
    return 0;
}

/* was func_1000EBC4 */
s32 sfx_cb_fade_out(struct00 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0 = arg0->unkC;
    s32 temp_v1 = arg0->unk18;
    temp_v1 -= g_frame_ticks;

    if (temp_v1 <= 0) {
        temp_v0 = temp_v0 - g_frame_ticks * 1000;
        if (temp_v0 < 0) {
            return 1;
        }
        arg0->unkC = temp_v0;
    }
    arg0->unk18 = temp_v1;
    return 0;
}

/* was func_1000EC24 */
s32 sfx_cb_delayed_play_2d(struct251 *arg0, s32 arg1, s32 *arg2, struct11 *arg3, struct04 *arg4, s32 *arg5, u16 *arg6) {
    s16 temp_v1 = arg0->unk18.h[1];

    if (*arg6 != 0) {
        arg0->unk1C = *arg6;
        arg0->unk0 = 0;
        *arg6 = 0;
    }

    temp_v1 -= g_frame_ticks;

    if (temp_v1 <= 0) {
        if (*arg2 != 0) {
            sound_play_2d(arg0->unk1C, *arg2, arg3->unk3, arg4->unk2, *arg5);
        }
        return 1;
    }
    arg0->unk18.w = temp_v1;
    return 0;
}

/* was func_1000ECCC */
s32 sfx_cb_delayed_object_sound2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    struct_eu_sfx *sfx = arg0;
    s16 timer = sfx->unk18;

    if (*arg6 != 0) {
        sfx->unk18 = (*arg6 << 16) | (sfx->unk18 & 0xFFFF);
        sfx->unk0 = 0;
        *arg6 = 0;
    }
    timer -= g_frame_ticks;
    if (timer <= 0) {
        *arg6 = sfx->unk18 >> 16;
        sfx->unk0 = *arg6;
        if (actor_sound2_is_playing((struct127 *)sfx->unk1C) == 0) {
            actor_sound_play2(*arg6, (struct127 *)sfx->unk1C, sfx->unkC, sfx->unkA, sfx->unk8);
        }
        return 1;
    }
    sfx->unk18 = (sfx->unk18 & 0xFFFF0000) | timer;
    return 0;
}
// ? sfx_cb_delayed_object_sound2(void *arg0, ? arg1, ? arg2, ? arg3, void *arg6) {
//     s16 temp_a1;
//     s32 temp_t4;
//     s32 temp_v1;
//     u16 temp_v0;
//
//     temp_v1 = arg0->unk18;
//     temp_v0 = *arg6;
//     if (temp_v0 != 0) {
//         arg0->unk18 = (s32) ((temp_v0 << 0x10) | (temp_v1 & 0xFFFF));
//         arg0->unk0 = (u16)0;
//         *arg6 = (u16)0U;
//     }
//     temp_a1 = (s16) temp_v1 - *(void *)0x800BE9E4;
//     if ((s32) temp_a1 <= 0) {
//         temp_t4 = arg0->unk18 >> 0x10;
//         *arg6 = (u16) temp_t4;
//         arg0->unk0 = (s16) temp_t4;
//         if (actor_sound2_is_playing(arg0->unk1C, temp_a1, arg6) == 0) {
//             actor_sound_play2(*arg6, arg0->unk1C, arg0->unkC, arg0->unkA, (?32) arg0->unk8);
//         }
//         return 1;
//     }
//     arg0->unk18 = (s32) ((arg0->unk18 & 0xFFFF0000) | temp_a1);
//     return 0;
// }

/* was func_1000EDA0 */
s32 sfx_cb_delayed_object_sound(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    struct_eu_sfx *sfx = arg0;
    s16 timer = sfx->unk18;

    if (*arg6 != 0) {
        sfx->unk18 = (*arg6 << 16) | (sfx->unk18 & 0xFFFF);
        sfx->unk0 = 0;
        *arg6 = 0;
    }
    timer -= g_frame_ticks;
    if (timer <= 0) {
        sfx->unk0 = *arg6 = sfx->unk18 >> 16;
        actor_sound_play_untracked(*arg6, (struct127 *)sfx->unk1C, sfx->unkC, sfx->unkA, sfx->unk8);
        return 1;
    }
    sfx->unk18 = (sfx->unk18 & 0xFFFF0000) | timer;
    return 0;
}
/* was func_1000EE70 */
s32 sfx_cb_follow_object(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, void *arg5)
{
  unsigned short new_var; // fakematch
  struct_eu_sfx *sfx = arg0;
  SfxObj *obj = (SfxObj *) sfx->unk18;
  unsigned short id;
  if ((obj != 0) && ((*((s32 *) arg2)) != 0))
  {
    id = sfx->unk1C & 0xFF;
    if ((obj->unk0 != 0) && (((u8 *) obj)[0x3B] == (new_var = id)))
    {
      *((s32 *) arg5) = ((obj->unk184 >> 3) & 0x30) * 2;
      sfx->unk2 = obj->unk14;
      sfx->unk4 = obj->unk18;
      sfx->unk6 = obj->unk1C;
      return 0;
    }
    if (sound_voice_is_looping(sfx->unk24) == 0)
    {
      return 0;
    }
  }
  return 1;
}

/* was func_1000EF40 */
s32 sfx_cb_keep_until_silent(struct57 *arg0, struct57 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    if (arg0->unk10 & 0x80) {
        arg0->unk10 = (s32) (arg0->unk10 & -0x81);
    }
    if (*arg2 == 0) {
        if (arg0->unk24 != 0) {
            sound_voice_stop(arg0->unk24);
            arg0->unk24 = 0;
        }
        *arg6 = 0;
    }
    return 0;
}

/* was func_1000EFB4 */
s32 sfx_cb_follow_object_anim(struct_eu_sfx *arg0, s32 arg1, s32 *arg2, struct11 *arg3, s32 arg4, s32 *arg5, u16 *arg6) {
    SfxObj *obj = (SfxObj *)arg0->unk18;
    u16 *p;
    s32 id;

    if (obj != NULL && (id = *arg2) != 0) {
        if (obj->unk0 != 0) {
            for (p = (u16 *)arg0->unk1C; *p != 0; p++) {
                if (obj->unk84 == *p || !(arg0->unk10 & 1)) {
                    *arg5 = ((obj->unk184 >> 3) & 0x30) * 2;
                    arg0->unk2 = obj->unk14;
                    arg0->unk4 = obj->unk18;
                    arg0->unk6 = obj->unk1C;
                    return 0;
                }
            }
        }
        if (*arg6 == 0xCA) {
            sound_play_2d(0xCB, id, arg3->unk3, 0, *arg5);
        } else if (*arg6 == 0x2CF) {
            sound_play_2d(0x2D7, id, arg3->unk3, 0, *arg5);
            sound_play_2d((random_int() % 3U) + 0x2EB, 0x3E80, arg3->unk3, 0, *arg5);
        } else if (*arg6 == 0x2D2) {
            sound_play_2d(0x2DA, id, arg3->unk3, 0, *arg5);
            sound_play_2d((random_int() % 3U) + 0x2EB, 0x3E80, arg3->unk3, 0, *arg5);
        }
    }
    return 1;
}
/* was func_1000F1A8 */
void sound_voices_reset(void) {
    s32 i;

    D_80042760 = 0;
    D_80041FD9 = 1;
    D_80041FD8 = 0;
    bzero(D_800425E0, 0x180);
    for (i = 0; i < 16; i++) {
        D_800425E0[i].unk2 = i + 16;
    }
    D_80041F50 = 0;
    n_sndp_stop_all_looping();
    D_80041F60 = D_80041F61 = 0;
}

void n_sndp_set_group_volume(u8 arg0, u16 arg1);
s32* allocate_memory(s32, s32, s32, s32);
/* was func_1000F248 */
void sound_level_init(s32 arg0) {
    u16 tmp;

    sound_voices_reset();
    if (arg0 == 4) {
        D_80041F54 = 0;
        D_80041F58 = 0.01f; // 0.009999999776482582
    } else {
        D_80041F54 = 23000;
        D_80041F58 = 0.1f; // 0.10000000149011612
    }

    if (arg0 == 0x35) {
        D_80041FD9 = 0;
    } else if (arg0 == 0x36) {
        D_80041FD9 = 0;
    } else if (arg0 == 0x3C) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    } else if (arg0 == 0x27) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x28;
    } else if ((arg0 == 0x3A) || (arg0 == 0x40)) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    }

    D_80041F5C = allocate_memory(1762, 1, 0, 0);

    bzero(D_80041F5C, 1762);

    if (arg0 == 0x31) {
        D_80041FDC = 14000;
    } else {
        D_80041FDC = 23000;
    }
    sound_level_hook_nop(arg0);
    D_80041F60 = D_80041F61 = 0;
    n_sndp_set_group_volume(0, D_80041F56);
    n_sndp_set_group_volume(1, D_80041F56);
    n_sndp_set_group_volume(2, 23000);
    // fakematch
    if (arg0) {}
}

/* was func_1000F3D0 */
s32 sound_voice_is_playing(u16 arg0) {
    struct120 *temp_v1;

    temp_v1 = &D_800425E0[arg0 & 0xF];
    if (temp_v1->unk8 != 0) {
        if ((temp_v1->unk0 == arg0) || (arg0 == (arg0 & 0xF))) {
            if (n_sndp_get_handle_state(&temp_v1->unk8) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

/* was func_1000F44C */
s32 sound_voice_is_looping(u16 arg0) {
    u32 mask;
    struct120 *temp_a1;
    struct31 *temp_a2;

    mask = __osDisableInt();
    temp_a1 = &D_800425E0[arg0 & 0xF];
    temp_a2 = temp_a1->unk8;
    if ((temp_a2 != 0) && (temp_a1->unk0 == arg0) && ((temp_a2->unk53 & 2) != 0)) {
        __osRestoreInt(mask);
        return 1;
    }
    __osRestoreInt(mask);
    return 0;
}

/* was func_1000F4D8 */
s32 sound_id_is_playing(u16 arg0) {
    s32 i;

    arg0 &= 0x7FFF;
    for (i = 0; i < 16; i++) {
        if (D_800425E0[i].unk8 != NULL && arg0 == (D_800425E0[i].unk4 & 0x7FFF) &&
            n_sndp_get_handle_state(&D_800425E0[i].unk8)) {
            return 1;
        }
    }
    return 0;
}
// sound_pick_variant: picks one of n variants of sound `base` at random and returns base + pick. For n < 8 the byte
// D_80041F5C[base] remembers the variants already played (bit 7 = valid) so every variant plays once before one
// repeats, and the last one played is never picked first in the next round; for n >= 8 it only stores pick + 1.
// base >= 0x6E2 returns 1, n < 2 returns base.
s32 random_int(void);

/* was func_1000F568 */
u16 sound_pick_variant(s32 base, u16 n) {
    u8 *played;
    u32 pick;
    s32 mask;
    s32 bits;

    pick = (u32)random_int() % n;
    if (base >= 0x6E2) {
        return 1;
    }
    if (n < 2) {
        return base;
    }
    if (D_80041F5C == NULL) {
        return base + pick;
    }
    played = (u8 *)D_80041F5C + base;
    if (n < 8) {
        bits = *played;
        mask = (1 << n) - 1;
        if (!(bits & 0x80) || !(bits & mask)) {
            bits = 0xFF; /* fresh round */
        }
        while (!(bits & (1 << pick))) {
            pick = (s32)(pick + 1) % (s32)n;
        }
        *played = bits ^ (1 << pick);
        if (((bits ^ (1 << pick)) & 0xFF & mask) == 0) {
            /* round over: all but this pick are available again */
            ((u8 *)D_80041F5C)[base] = bits ^ mask;
        }
    } else {
        *played = pick + 1;
    }
    return base + pick;
}
s32 sound_calc_pan_volume(s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32 *, s32);

/* was func_1000F6B8 */
s32 sound_listener_volume_pan(s32 arg0, s16 x, s16 y, s16 z, s32 arg4, s16 arg5, s16 arg6) {
    s32 vol;
    SfxListener *best;
    s32 i;
    u32 min;
    u32 d;
    s32 dx, dy, dz;
    s32 tx, ty, tz;

    if (g_last_player_index != 0) {
        min = -1;
        for (i = 0; i <= g_last_player_index; i++) {
            tx = x - D_80042308[i].ex;
            ty = y - D_80042308[i].ey;
            tz = z - D_80042308[i].ez;
            d = tx * tx + ty * ty + tz * tz;
            if (d < min) {
                min = d;
                best = &D_80042308[i];
                dx = tx;
                dy = ty;
                dz = tz;
            }
        }
        goto block_end; // fakematch: empty goto moves the best->x reload into the b delay slot (permuter)
    block_end:;
    } else {
        best = D_80042308;
        dx = x - best->ex;
        dy = y - best->ey;
        dz = z - best->ez;
    }
    sound_calc_pan_volume(dx, dy, dz, best->f, x - best->x, y - best->y, z - best->z, arg6, arg5, arg4, &vol, 0);
    return vol;
}
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} EU42988;
extern EU42988 D_80042988[];
/* was func_1000F85C */
void sound_voice_set_param(u16 arg0, s16 arg1, s32 arg2) {
    if (arg0 >= 0x10) {
        if (sound_voice_is_playing(arg0) != 0) {
            if (arg1 == 0x10) {
                f32 sp1C;
                sp1C = alCents2Ratio(arg2);
                arg2 = *(s32 *)&sp1C;
            } else if (arg1 == 0x11) {
                arg1 = 0x10;
            }
            n_sndp_post_event(D_80042988[arg0 & 0xF].unk0, arg1, arg2);
        }
    }
}
// NON-MATCHING: not even close
// void sound_voice_set_param(s32 arg0, s16 arg1, s32 arg2) {
//     f32 sp1C;
//     s32 sp18;
//     s16 temp_a1;
//     s16 temp_a1_2;
//     s32 temp_t6;
//     s16 phi_a1;
//
//     temp_t6 = arg0 & 0xFFFF;
//     temp_a1 = arg1;
//     if (temp_t6 >= 16) {
//         sp18 = temp_t6;
//         arg1 = temp_a1;
//         temp_a1_2 = arg1;
//         if (sound_voice_is_playing(temp_t6) != 0) {
//             if (temp_a1_2 == 16) {
//                 sp18 = sp18;
//                 arg1 = temp_a1_2;
//                 sp1C = alCents2Ratio(arg2, temp_a1_2);
//                 arg2 = (s32) sp1C;
//                 phi_a1 = arg1;
//             } else {
//                 phi_a1 = temp_a1_2;
//                 if (temp_a1_2 == 0x11) {
//                     phi_a1 = (u16)0x10;
//                 }
//             }
//             n_sndp_post_event((((sp18 & 0xF) * 0xC) + 0x80040000) - 0x25E8, phi_a1, arg2);
//         }
//     }
// }

/* was func_1000F91C */
void sound_voice_update_3d(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4,
                   s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9) {
    s32 sp2C;
    s32 tmp = sound_listener_volume_pan(arg4, arg5, arg6, arg7, &sp2C, (s32) arg8, (s32) arg9);

    sound_voice_set_param(arg0, 8, (u32) (tmp * arg1) >> 0xF);
    sound_voice_set_param(arg0, 4, sp2C & 0x7F);
    sound_voice_set_param(arg0, 256, (sp2C & 0x80) | arg3);
    sound_voice_set_param(arg0, 16, arg2);
}

/* was func_1000F9D4 */
void sound_voice_update_pan(u16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u32 tmp;

    sound_listener_volume_pan(-1, arg1, arg2, arg3, &tmp, 32760, 32765);
    sound_voice_set_param(arg0, 4, tmp & 0x7F);
    sound_voice_set_param(arg0, 256, tmp & 0x80);
}

// sfx_start_positional: claims the next of the 32 positional sound slots (D_80041FE0[D_80042B00++]) for sound id
// arg0 at (arg1, arg2, arg3) with volume arg4, ranges arg5 / arg6, update callback arg7 (+ its data arg8, arg9) and
// flags argA (with a callback: flags | 0x12, else (flags & 0x108) | 2; flag 0x40: arg2 is a joint index resolved by
// setup_entry_find_by_id((u8) arg1), -1 = fail), pitch argB cents. sfx_emitters_update starts it; returns the voice handle (+0x24)
// when the slot count did not change meanwhile (and marks the slot 0x1000), else 0. 0 when all slots are used.
/* was func_1000FA64 */
u16 sfx_emitter_start(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s16 arg6, s32 arg7, void *arg8,
                  s32 arg9, s32 argA, s32 argB) {
    SfxEnt *e;
    s32 idx;
    s32 count;

    idx = D_80042B00;
    if (idx < 32) {
        D_80042B00 = idx + 1;
    } else {
        return 0;
    }
    e = &((SfxEnt *) D_80041FE0)[idx];
    if (arg7 != 0) {
        e->unk10 = argA | 0x12;
    } else {
        e->unk10 = (argA & 0x108) | 2;
    }
    if (argA & 0x40) {
        arg2 = setup_entry_find_by_id(arg1);
        if (arg2 == -1) {
            return 0;
        }
    }
    e->unk24 = 0;
    e->unk23 = 0;
    e->unk22 = 0;
    e->unk0 = arg0;
    e->unk2 = arg1;
    e->unk4 = arg2;
    e->unk6 = arg3;
    e->unk8 = arg5;
    e->unkA = arg6;
    e->unkC = arg4;
    e->unk14 = (void *) arg7;
    e->unk18 = (s32) arg8;
    e->unk1C = arg9;
    e->unk2C = alCents2Ratio(argB);
    e->unk26 = 0;
    e->unk28 = 0;
    e->unk20 = argB;
    count = D_80042B00;
    sfx_emitters_update(D_80041FE0, &D_80042B00, idx, idx + 1);
    if (count != D_80042B00) {
        return 0;
    }
    e->unk10 |= 0x1000;
    return e->unk24;
}
/* was func_1000FC18 */
void sfx_emitter_stop_at(u16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    s32 i;

    for (i = 0; i < D_80042B00; i++) {
        if (arg0 == ((SfxEnt *)D_80041FE0)[i].unk0 && arg1 == ((SfxEnt *)D_80041FE0)[i].unk2 && arg2 == ((SfxEnt *)D_80041FE0)[i].unk4 && arg3 == ((SfxEnt *)D_80041FE0)[i].unk6 && arg4 == (((SfxEnt *)D_80041FE0)[i].unk8 & 0x7FFF)) {
            if (((SfxEnt *)D_80041FE0)[i].unk24 != 0) {
                sound_voice_stop(((SfxEnt *)D_80041FE0)[i].unk24);
            }
            ((SfxEnt *)D_80041FE0)[i].unk10 |= 0x80;
        }
    }
}
/* was func_1000FD38 */
void sfx_emitter_stop_by_callback(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk14 && arg1 == D_80041FE0[i].unk18 && arg2 == D_80041FE0[i].unk1C) {
            if (D_80041FE0[i].unk24) {
                sound_voice_stop(D_80041FE0[i].unk24);
            }
            D_80041FE0[i].unk10 = D_80041FE0[i].unk10 | 0x80;
        }
    }
}
/* was func_1000FDF4 */
void sfx_emitter_stop_by_voice(u16 arg0) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk24) {
            if (D_80041FE0[i].unk24) {
                sound_voice_stop(D_80041FE0[i].unk24);
            }
            D_80041FE0[i].unk10 = D_80041FE0[i].unk10 | 0x80;
        }
    }
}
/* was func_1000FE88 */
s32 sfx_emitter_free_index(struct15 *arg0, s32 arg1, s32 *arg2) {
    if (arg1 < *arg2) {
        if (arg0[arg1].unk24 != 0) {
            sound_voice_stop(arg0[arg1].unk24);
        }
        arg0[arg1].unk10 |= 0x80;
        return 0;
    }
    return 1;
}

/* was func_1000FEF0 */
s32 sfx_emitter_find_by_voice(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_t6;
    s32 var_v1;
    struct15 *var_a2;

    temp_t6 = arg0 & 0xFFFF;
    if (temp_t6 == 0) {
        goto block_10;
    }
    var_v1 = 0;
    if (D_80042B00 > 0) {
        var_a2 = D_80041FE0;
loop_4:
        if ((temp_t6 == var_a2->unk24) && (arg1 == var_a2->unk18) && (arg2 == var_a2->unk1C) && !(var_a2->unk10 & 0x80)) {
            return var_v1;
        }
        var_v1 += 1;
        var_a2 = (struct15 *)((u8 *)var_a2 + (0x30));
        if (var_v1 >= D_80042B00) {
            goto block_10;
        }
        goto loop_4;
    }
block_10:
    return -1;
}
// NON-MATCHING: needs a re-work
// s32 sfx_emitter_find_by_voice(u16 arg0, struct127 *arg1, s32 arg2) {
//     s32 i;
//     struct15 *tmp;
//
//     if (arg0 == 0) {
//         // nothing
//     } else {
//         for (i = 0; i < D_80042760; i++) {
//             tmp = &D_80041FE0[i];
//             if ((arg0 == tmp->unk24) &&
//                 (arg1 == tmp->unk18) &&
//                 (arg2 == tmp->unk1C) &&
//                 ((tmp->unk10 & 0x80) == 0)) {
//                 return i;
//             }
//         }
//     }
//     return -1;
// }

extern s32 D_80042B00;
/* was func_1000FF90 */
s32 sfx_emitter_find_by_callback(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    u32 new_var; // fakematch: -1 kept in its own register

    for (i = 0; i < D_80042B00; i++) {
        new_var = -1;
        if ((arg0 == D_80041FE0[i].unk14) &&
            ((arg1 == D_80041FE0[i].unk18) || (arg1 == new_var)) &&
            ((arg2 == D_80041FE0[i].unk1C) || (arg2 == -1)) &&
            ((D_80041FE0[i].unk10 & 0x80) == 0)) {
            return i;
        }
    }
    return -1;
}
/* was func_1001001C */
void sfx_emitter_set_volume_pitch(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk14 && arg1 == D_80041FE0[i].unk18 && arg2 == D_80041FE0[i].unk1C) {
            *(f32 *)&D_80041FE0[i].unk2C = alCents2Ratio(arg4);
            D_80041FE0[i].unkC = arg3;
        }
    }
}
/* was func_100100E0 */
void sfx_emitter_replace_callback(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if (arg0 == D_80041FE0[i].unk14 && arg1 == D_80041FE0[i].unk18 && arg2 == D_80041FE0[i].unk1C) {
            D_80041FE0[i].unk14 = arg3;
            D_80041FE0[i].unk18 = arg4;
            D_80041FE0[i].unk1C = arg5;
        }
    }
}
// object_sound_play: plays sound sfx at object obj (volume vol, arg3 / arg4 = distance range) and keeps the handle in
// obj+0x8E. Players (+0x318) play it as a 2D sound through sound_voice_play with the player's pan; other objects
// get a 3D emitter that follows them (sfx_cb_follow_object, key unique_id | 0x10000). Dead objects (state 0 or 5) play nothing.
/* was func_10010154 */
u16 actor_sound_play(u16 sfx, struct127 *obj, s32 vol, s16 arg3, u16 arg4) {
    u16 handle = 0;
    s32 flags = 0;
    s16 near = arg3;
    u8 *o = (u8 *)obj;

    if (*(s32 *)o == 0 || *(s32 *)o == 5) {
        return 0;
    }
    if (*(s32 *)(o + 0x318) != 0) {
        handle = sound_voice_play(*(u16 *)(o + 0x8E), sfx, vol, 0x40, 0, ((*(u32 *)(o + 0x184) >> 3) & 0x30) << 1,
                               D_80041FD9);
        *(u16 *)(o + 0x8E) = handle;
        return handle;
    }
    if (o[4] == 0x16) {
        near = arg3 * 2;
        if (arg4 < near) {
            near = arg4 - 200;
        }
    } else if (o[4] == 5 || o[4] == 0x4F || o[4] == 0x83) {
        flags = 4;
    } else if (o[0x13C] != 0 && (o[4] == 0x8A || o[4] == 0x23)) {
        flags = 0x100;
    }
    sfx_emitter_stop_by_callback((s32)sfx_cb_follow_object, (s32)obj, obj->unique_id | 0x10000);
    if (*(s32 *)o != 0) {
        handle = sfx_emitter_start(sfx, (s32)obj->x_position, (s32)obj->y_position, (s32)obj->z_position, vol, arg4, near,
                               (s32)sfx_cb_follow_object, obj, obj->unique_id | 0x10000, flags, 0);
    }
    *(u16 *)(o + 0x8E) = handle;
    return handle;
}

// object_sound_play2: as object_sound_play for the object's second sound slot (handle in obj+0x8C, emitter key
// unique_id | 0x20000). A negative vol plays at -vol with flag 0x100; a player whose context has +0x94 == 1 plays at
// full volume (0x7FFF) in mono.
/* was func_10010344 */
u16 actor_sound_play2(u16 sfx, struct127 *obj, s32 vol, s16 arg3, u16 arg4) {
    u16 handle;
    s32 flags = 0;
    s16 near = arg3;
    u8 *o = (u8 *)obj;
    u8 *ctx;
    u8 mono;

    if (*(s32 *)o == 0 || *(s32 *)o == 5) {
        return 0;
    }
    if (vol < 0) {
        vol = -vol;
        flags = 0x100;
    }
    if (*(s32 *)(o + 0x318) != 0) {
        ctx = *(u8 **)(o + 0x31C);
        mono = D_80041FD9;
        if (ctx != NULL && ctx[0x94] == 1) {
            mono = 1;
            vol = 0x7FFF;
        }
        handle = sound_voice_play(*(u16 *)(o + 0x8C), sfx, vol, 0x40, 0, ((*(u32 *)(o + 0x184) >> 3) & 0x30) << 1, mono);
        *(u16 *)(o + 0x8C) = handle;
        return handle;
    }
    if (o[4] == 0x16) {
        near = arg3 * 2;
        if (arg4 < near) {
            near = arg4 - 200;
        }
    } else if (o[4] == 0x8A && o[0x13C] != 0) {
        flags |= 0x100;
    } else if (o[4] == 0x4F || o[4] == 0x83) {
        flags |= 4;
    }
    sfx_emitter_stop_by_callback((s32)sfx_cb_follow_object, (s32)obj, obj->unique_id | 0x20000);
    handle = sfx_emitter_start(sfx, (s32)obj->x_position, (s32)obj->y_position, (s32)obj->z_position, vol, arg4, near,
                           (s32)sfx_cb_follow_object, obj, obj->unique_id | 0x20000, flags, 0);
    *(u16 *)(o + 0x8C) = handle;
    return handle;
}
/* was func_10010558 */
void actor_sound_play2_delayed(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) {
    if (arg5 <= 0) {
        actor_sound_play2(arg0, arg1, arg2, arg3, arg4);
    } else {
        sfx_emitter_start(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, sfx_cb_delayed_object_sound2, arg5, arg1, 0, 0);
    }
}

/* was func_10010630 */
void actor_sound_play_untracked(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
    if (arg1->interaction_state != 0) {
        if (arg1->camera != NULL) {
            sound_play_2d((s32) arg0, arg2 & 0xFFFF, 0x40U, 0, (u8) ((((u32) arg1->unk184 >> 3) & 0x30) * 2));
            return;
        }
        sfx_emitter_start(arg0, (s16) (s32) arg1->x_position, (s16) (s32) arg1->y_position, (s16) (s32) arg1->z_position, arg2, (u16) (s32) arg4, (s16) (s32) arg3, (s32) sfx_cb_follow_object, arg1, (s32) arg1->unique_id, 0, 0);
    }
}
// void actor_sound_play_untracked(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
//     if (arg1->interaction_state != 0) {
//         if (arg1->camera != 0) {
//             sound_play_2d(arg0, arg2 & 0xFFFF, 64, 0, (((u32) arg1->unk184 >> 3) & 0x30) * 2); //
//         } else {
//             sfx_emitter_start(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, (void *)sfx_cb_follow_object, arg1, arg1->unique_id, 0, 0);
//         }
//     }
// }

/* was func_10010720 */
void actor_sound_play_untracked_delay(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) {
    if (arg5 <= 0) {
        actor_sound_play_untracked(arg0, arg1, arg2, arg3, arg4);
    } else {
        sfx_emitter_start(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, sfx_cb_delayed_object_sound, arg5, arg1, 0, 0);
    }
}

/* was func_100107F8 */
s32 actor_sound_is_playing(struct127 *arg0) {
    if (arg0->interaction_state == 0) {
        return 0;
    } else {
        if (arg0->camera != 0) {
            if (arg0->unk8E != 0) {
                if (sound_voice_is_playing(arg0->unk8E) != 0) {
                    return 1;
                }
            }
        } else {
            if (sfx_emitter_find_by_callback(sfx_cb_follow_object, arg0, arg0->unique_id | 0x10000) != -1) {
                return 1;
            }
        }
        arg0->unk8E = 0;
    }
    return 0;
}

/* was func_10010894 */
s32 actor_sound2_is_playing(struct127 *arg0) {
    if (arg0->camera != 0) {
        if (arg0->unk8C != 0) {
            if (sound_voice_is_playing(arg0->unk8C) != 0) {
                return 1;
            }
        }
    } else {
        if (sfx_emitter_find_by_callback(sfx_cb_follow_object, arg0, arg0->unique_id | 0x20000) != -1) {
            return 1;
        }
    }
    arg0->unk8C = 0;
    return 0;
}

extern s32 D_8004238C;

/* was func_1001091C */
void actor_sound_set_volume(u8 *arg0, s32 arg1) {
    s32 temp_v0;

    if (arg1 == 0) return;
    if (*(s32 *)arg0 == 0) return;
    if ((*(s32 *)((u8 *)arg0 + 0x318)) != 0) {
        if ((*(u16 *)((u8 *)arg0 + 0x8E)) != 0) {
            sound_voice_set_param((*(u16 *)((u8 *)arg0 + 0x8E)), 8, arg1);
        }
    } else {
        temp_v0 = sfx_emitter_find_by_callback((s32) sfx_cb_follow_object, (s32) arg0, (*(u8 *)((u8 *)arg0 + 0x3B)) | 0x10000);
        if (temp_v0 != -1) {
            *(s32 *)((u8 *)&D_8004238C + (temp_v0 * 0x30)) = arg1;
            return;
        }
        (*(u16 *)((u8 *)arg0 + 0x8E)) = 0U;
    }
}
// NON-MATCHING: something isnt right...
// void actor_sound_set_volume(struct127 *arg0, struct15 *arg1) {
//     s32 temp_v0;
//
//     if ((arg1 != NULL) && (arg0->unk0 != 0)) {
//         if (arg0->camera != 0) {
//             if (arg0->unk8E != 0) {
//                 sound_voice_set_param(arg0->unk8E, 8, arg1->unk1C); // help
//             }
//         } else {
//             temp_v0 = sfx_emitter_find_by_callback(sfx_cb_follow_object, arg0, arg0->unique_id | 0x10000);
//             if (temp_v0 != -1) {
//                 D_80041FEC[temp_v0][0] = arg1;
//             } else {
//                 arg0->unk8E = 0;
//             }
//         }
//     }
// }

/* was func_100109D0 */
void actor_sound_stop(struct127 *arg0) {
    if (arg0->camera) {
        if (arg0->unk8E) {
            sound_voice_stop(arg0->unk8E);
        }
    } else {
        sfx_emitter_stop_by_callback(sfx_cb_follow_object, arg0, arg0->unique_id | 0x10000);
    }
    arg0->unk8E = 0;
}

/* was func_10010A3C */
void actor_sound2_stop(struct127 *arg0) {
    if (arg0->camera) {
        if (arg0->unk8C) {
            sound_voice_stop(arg0->unk8C);
        }
    } else {
        sfx_emitter_stop_by_callback(sfx_cb_follow_object, arg0, arg0->unique_id | 0x20000);
    }
    arg0->unk8C = 0;
}

/* was func_10010AA8 */
void actor_sounds_stop_loops(struct127 *arg0) {
    s32 sp24;
    struct15 *tmp;

    if (arg0->camera != 0) {
        if (arg0->unk8C && sound_voice_is_looping(arg0->unk8C)) {
            sound_voice_stop(arg0->unk8C);
        }
        if (arg0->unk8E && sound_voice_is_looping(arg0->unk8E)) {
            sound_voice_stop(arg0->unk8E);
        }
    } else {
        sp24 = sfx_emitter_find_by_voice(arg0->unk8C, arg0, arg0->unique_id);
        if (sp24 != -1) {
            if (sound_voice_is_looping(arg0->unk8C)) {
                sound_voice_stop(arg0->unk8C);
            }
            tmp = &D_80041FE0[sp24];
            tmp->unk10 |= 0x80;
        }
        sp24 = sfx_emitter_find_by_voice(arg0->unk8E, arg0, arg0->unique_id);
        if (sp24 != -1) {
            if (sound_voice_is_looping(arg0->unk8E)) {
                sound_voice_stop(arg0->unk8E);
            }
            tmp = &D_80041FE0[sp24];
            tmp->unk10 |= 0x80;
        }
    }
    arg0->unk8C = 0;
    arg0->unk8E = 0;
}

s32 n_sndp_play_sound(s32, s16, u16, u8, f32, s32, s32, struct31 **);
extern s32 D_8003E708;
extern u16 D_80042984;

/* was func_10010BE8 */
u16 sound_voice_play(u16 arg0, s32 arg1, u16 arg2, u8 arg3, s16 arg4, u8 arg5, u8 arg6) {
    u16 sp4E;
    struct31 **sp38;
    s32 sp34;
    s32 temp_a0;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_s0;
    struct120 *temp_s0;
    struct120 *temp_s0_2;
    struct120 *temp_s0_3;
    struct31 **temp_t2;
    struct31 *temp_v0_2;
    u16 temp_t0;
    u16 var_t0;
    u16 var_v1;
    u32 var_s1;

    temp_t6 = arg0 & 0xFFFF;
    var_s1 = temp_t6 & 0xF;
    temp_s0 = &D_800425E0[var_s1];
    if ((temp_t6 == temp_s0->unk0) && (temp_t6 != 0)) {
        if ((temp_s0->unk8 != NULL) && (n_sndp_get_handle_state(&temp_s0->unk8) != 0)) {
            n_sndp_stop_sound(temp_s0->unk8);
            temp_s0->unk8 = NULL;
        }
    } else if ((((temp_s0->unk8 != NULL) && (n_sndp_get_handle_state(&temp_s0->unk8) != 0)) || (temp_s0->unk4 & 0x8000)) && (((var_s1 = 0, (D_80042988->unk0 != 0)) && (n_sndp_get_handle_state((struct31 **) D_80042988) != 0)) || (D_80042984 & 0x8000))) {
loop_11:
        var_s1 += 1;
        if (var_s1 < 0x10U) {
            temp_s0_2 = &D_800425E0[var_s1];
            if (((temp_s0_2->unk8 != NULL) && (n_sndp_get_handle_state(&temp_s0_2->unk8) != 0)) || (temp_s0_2->unk4 & 0x8000)) {
                goto loop_11;
            }
        }
    }
    if ((s32) arg2 < 0x64) {
        return 0U;
    }
    if (var_s1 >= 0x10U) {
        var_t0 = 0;
        goto block_31;
    }
    if (arg1 == 0) {
        return 0U;
    }
    temp_t3 = arg1 & 0x7FFF;
    if (temp_t3 >= 0x6E3) {
        return 0U;
    }
    temp_s0_3 = &D_800425E0[var_s1];
    temp_t0 = temp_s0_3->unk2;
    temp_t2 = &temp_s0_3->unk8;
    temp_v0 = temp_t0 + 0x10;
    temp_a0 = temp_v0 & 0xFFFF;
    var_v1 = temp_v0 & 0xFFFF;
    temp_s0_3->unk0 = temp_t0;
    if (temp_a0 < 0x10) {
        var_v1 = (temp_a0 + 0x10) & 0xFFFF;
    }
    temp_v0_2 = temp_s0_3->unk8;
    temp_s0_3->unk2 = var_v1;
    temp_s0_3->unk4 = (u16) arg1;
    if (temp_v0_2 != NULL) {
        temp_v0_2->unk54 = 5;
    }
    if (((arg5 & 0x7F) + (u8) D_80041FD8) < 0x80) {
        var_s0 = (arg5 + (u8) D_80041FD8) & 0xFF;
    } else {
        var_s0 = (arg5 | 0x7F) & 0xFF;
    }
    sp4E = temp_t0;
    sp34 = temp_t3;
    sp38 = temp_t2;
    n_sndp_play_sound(D_8003E708, (s16) temp_t3, arg2, arg3, alCents2Ratio((s32) arg4), var_s0, (s32) arg6, temp_t2);
    var_t0 = temp_t0;
block_31:
    return var_t0;
}
/* was func_10010E78 */
u16 sound_voice_play_at(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA)
{
  s32 sp2C;
  u32 temp_t1;
  temp_t1 = (u32) sound_listener_volume_pan(arg5, arg6, arg7, arg8, &sp2C, (s32) arg9, (s32) argA);
  temp_t1 = (((u32) arg2) * temp_t1) >> 0xF;
  if (temp_t1 != 0)
  {
    return sound_voice_play(arg0, arg1, temp_t1, sp2C & 0x7F, (s16) ((s32) arg3), (sp2C & 0x80) | arg4, (u8) ((s32) D_80041FD9));
  }
  return 0;
}

/* was func_10010F30 */
u16 sound_play_2d(s32 arg0, u16 arg1, u8 arg2, s16 arg3, u8 arg4) {
    sound_voice_play(0, arg0, arg1, arg2, arg3, arg4, D_80041FD9);
}

// sound_play_at: plays a sound with no owner (sound_voice_play_at with arg0 0). The asm passes sound_voice_play_at's v0
// through, and the asm callers keep it as the sound handle, so the NM version returns it.
/* was func_10010F88 */
u16 sound_play_at(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9) {
    return sound_voice_play_at(0, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
/* was func_10010FFC */
u16 sound_play_for_actor(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, u8 *arg5)
{
  f32 f;
  u8 idx;
  if ((arg5 == NULL) || (*(s32 *) (arg5 + 0) == 0))
  {
    return 0;
  }
  if (*(s32 *) (arg5 + 0x318) != 0)
  {
    arg0 = sound_voice_play(arg0, arg1, arg2, 0x40, arg3, arg4, D_80041FD9);
  }
  else
  {
    arg2 = (arg2 + arg2 + arg2) >> 2;
    idx = arg5[4];
    if (idx != 0xFF)
    {
      f = *(f32 *) (arg5 + 0x14C) * (u32) (u16) D_800D1C90[idx]->unkE;
    }
    else
    {
      f = 0.0f;
    }
    if (f > 256.0f)
    {
      f = 1.0f;
    }
    else if (f < 80.0f)
    {
      f = 0.3125f;
    }
    else
    {
      f = f * 0.00390625f;
    }
    arg0 = sound_voice_play_at(arg0, arg1, arg2, arg3, arg4, 0, *(f32 *) (arg5 + 0x14), *(f32 *) (arg5 + 0x18), *(f32 *) (arg5 + 0x1C), 500, (s32) (2000.0f * f) + 501);
  }
  return arg0;
}

/* was func_100111C8 */
void sound_voice_stop(u16 arg0) {
    struct120 *tmp = &D_800425E0[arg0 & 0xF];

    if ((tmp->unk8 != 0) && (tmp->unk0 == arg0)) {
        tmp->unk0 = 0;
        tmp->unk4 = 0;
        n_sndp_stop_sound(tmp->unk8);
        tmp->unk8 = 0;
    }
}

/* was func_1001123C */
void sound_voice_stop_deferred(u16 arg0) {
    struct120 *tmp = &D_800425E0[arg0 & 0xF];

    if ((tmp->unk8 != 0) && (tmp->unk0 == arg0)) {
        if (sound_stop_queue_push(arg0, 1) == 0) {
            n_sndp_stop_sound(tmp->unk8);
            tmp->unk8 = 0;
        }
    }
}

/* was func_100112BC */
s32 sound_stop_queue_push(s32 arg0, s32 arg1) {
    struct49 *temp_a0;
    s32 temp_v1 = D_80041F50;

    if (temp_v1 < 16) {
        temp_a0 = &D_80041F10[temp_v1];
        temp_a0->unk0 = arg0;
        temp_a0->unk2 = arg1;
        temp_a0->unk3 = arg0 & 0xF;
        D_80041F50 = temp_v1 + 1;
        return 1;
    } else {
        return 0;
    }
}

typedef struct { u16 id; u8 timer; u8 slot; } SfxPend;
#define PEND ((SfxPend *)D_80041F10)

/* was func_10011310 */
void sound_stop_queue_process(void)
{
  s32 slot;
  s32 removed;
  s32 j;
  s32 n;
  SfxPend *pend;
  s32 i;
  struct120 *e;
  removed = 0;
  j = 0;
  n = D_80041F50;
  for (i = 0; i < ((s32) D_80041F50); i++)
  {
    pend = (SfxPend *) D_80041F10; // fakematch: pointer local only for the timer test, slot read and copy (permuter)
    if (pend[i].timer > 0)
    {
      ((SfxPend *) D_80041F10)[i].timer--;
    }
    else
    {
      removed = 1;
      slot = pend[i].slot;
      if (D_800425E0[slot].unk0 == ((SfxPend *) D_80041F10)[i].id)
      {
        D_800425E0[slot].unk0 = 0;
        D_800425E0[slot].unk4 = 0;
        if (D_800425E0[slot].unk8 != 0)
        {
          n_sndp_stop_sound(D_800425E0[slot].unk8);
        }
        D_800425E0[slot].unk8 = 0;
      }
      n--;
      ; // fakematch: empty statement after n-- (permuter)
    }
    if (j != i)
    {
      ((SfxPend *) D_80041F10)[j] = pend[i];
    }
    if (removed)
    {
      j++;
    }
    else
    {
      removed = 0;
    }
  }

  D_80041F50 = n;
}

/* was func_1001147C */
s32 sound_voice_get_id(u16 arg0) {
    struct120 *tmp;

    if (arg0 != 0) {
        tmp = &D_800425E0[arg0 & 0xF];
        if (tmp->unk0 == arg0) {
            return tmp->unk4 & 0x7FFF;
        }
    }
    return -1;
}

// sound_source_mix: volume / pan / distance of a sound at (x, y, z) for the nearest listener (P151). With more than
// one listener (g_last_player_index = last index) it picks the one whose ear position (ex, ey, ez) is closest; then
// sound_calc_pan_volume with the source relative to the ear, the listener's heading and the source relative to the listener
// (x, y, z) for the distance falloff between `outer` and `inner`. *outVol = that volume scaled by gain / 0x8000.
// Returns the distance.
/* was func_100114D0 */
s32 sound_source_mix(s32 x, s32 y, s32 z, s32 gain, s32 outer, s32 inner, s32 *outPan, s32 *outVol, s32 *outDist) {
    SfxListener *best = D_80042308;
    SfxListener *l;
    u32 min;
    u32 d;
    s32 dx, dy, dz;
    s32 i;
    s32 vol;
    s32 dist;

    if (g_last_player_index != 0) {
        min = -1;
        for (i = 0, l = D_80042308; i <= g_last_player_index; i++, l++) {
            dx = x - l->ex;
            dy = y - l->ey;
            dz = z - l->ez;
            d = dx * dx + dy * dy + dz * dz;
            if (d < min) {
                min = d;
                best = l;
            }
        }
    }
    dist = sound_calc_pan_volume(x - best->ex, y - best->ey, z - best->ez, best->f, x - best->x, y - best->y, z - best->z, outer,
                         inner, (s32)outPan, &vol, (s32)outDist);
    *outVol = (u32)(vol * gain) >> 15;
    return dist;
}
/* SfxEnt.unk10 flags used by the update pass */
#define SFX_PLAYING     0x0001 /* unk24 holds a live voice */
#define SFX_REFRESH     0x0002 /* recompute even while playing */
#define SFX_SMOOTH      0x0004 /* pitch ratio follows the distance change (Doppler-like), smoothed */
#define SFX_KEEP        0x0008 /* keep the entry when the voice ends / goes silent */
#define SFX_CALLBACK    0x0010 /* unk14 may adjust the parameters (non-zero: the entry is freed) */
#define SFX_LISTENER    0x0040 /* position relative to listener D_80042308[0] (sound_path_calc_pan_volume) */
#define SFX_FREE        0x0080
#define SFX_FIXED_PAN   0x0100 /* pan 0x40, not computed */
#define SFX_MIRROR      0x0200 /* mirrored pan, flips the 0x80 bit */
#define SFX_FX_MASK     0x0C00 /* voice effect mode: 0 = D_80041FD9, 0x400 = 0, else 1 */
#define SFX_SKIP_ONCE   0x1000

/* Updates the sound entries [first, min(*count, end)): drops ended voices, computes volume / pan / pitch from the
 * position (sound_source_mix or the listener-relative sound_path_calc_pan_volume), starts a voice for an entry without one
 * (sound_voice_play) or sends the changed parameters to the playing one (sound_voice_set_param 8 = volume, 4 = pan,
 * 0x100 = pan high bit | slot, 0x11 = pitch ratio). Entries that fall silent are freed (sfx_emitter_free_index) or stopped. */
/* was func_10011624 */
void sfx_emitters_update(struct15 *arg0, s32 *count, s32 first, s32 end) {
    SfxEnt *e;
    SfxListener *lis;
    u32 flags;
    u16 voice;
    s32 pan;            /* sp BC */
    u32 vol;            /* sp B4 */
    u32 dist;           /* sp AC */
    s32 pos;            /* sp B0 (only the callback reads it) */
    s32 pitch;          /* sp A8, cents */
    s32 slot;           /* sp A0 */
    u16 sound;          /* sp A6 */
    s32 *panOut;
    s32 hi;
    s32 fx;
    s32 d;
    f32 k;
    union { f32 f; s32 i; } ratio;
    s32 i;

    for (i = first; i < *count && i < end; i++) {
        e = (SfxEnt *) arg0 + i;
        flags = e->unk10;
        if (flags & SFX_FREE) {
            continue;
        }
        if (flags & SFX_SKIP_ONCE) {
            e->unk10 = flags & ~SFX_SKIP_ONCE;
            continue;
        }
        voice = e->unk24;
        if ((flags & SFX_PLAYING) && voice != 0 && sound_voice_is_playing(voice) == 0) {
            /* the voice has ended */
            flags &= ~SFX_PLAYING;
            voice = 0;
            if (!(flags & SFX_KEEP)) {
                flags |= SFX_FREE;
                e->unk0 = 0;
            }
            e->unk26 = 0;
            e->unk22 = 0;
            e->unk24 = 0;
            e->unk10 = flags;
            e->unk2C = 1.0f;
        }
        if (!(flags & SFX_REFRESH) && voice != 0) {
            e->unk24 = voice;
            e->unk10 = flags;
            continue;
        }
        if (flags & SFX_FIXED_PAN) {
            pan = 0x40;
            panOut = NULL;
        } else {
            panOut = &pan;
        }
        if (flags & SFX_LISTENER) {
            lis = &D_80042308[0];
            pos = sound_path_calc_pan_volume(e->unk4, lis->ex, lis->ey, lis->ez, lis->f, lis->x, lis->y, lis->z, e->unk8, e->unkA,
                                &pan, &vol, &dist);
            vol = (e->unkC * vol) >> 15;
        } else {
            pos = sound_source_mix(e->unk2, e->unk4, e->unk6, e->unkC, e->unk8, e->unkA, panOut, (s32 *) &vol,
                                (s32 *) &dist);
        }
        if (D_800BEA35 != 0) {
            vol = 0;
        }
        pitch = e->unk20;
        slot = e->unk23;
        sound = e->unk0;
        if ((flags & SFX_CALLBACK) && e->unk14 != NULL) {
            e->unk10 = flags;
            if (e->unk14((struct15 *) e, &pos, &vol, &pan, &pitch, &slot, &sound) != 0) {
                sfx_emitter_free_index(arg0, i, count);
                continue;
            }
            voice = e->unk24;
            flags = e->unk10;
        }
        if (sound == 0) {
            e->unk24 = voice;
            e->unk10 = flags;
            continue;
        }
        if (vol == 0) {
            /* silent */
            if (!(flags & SFX_KEEP)) {
                sfx_emitter_free_index(arg0, i, count);
                continue;
            }
            if (voice != 0) {
                sound_voice_stop(voice);
            }
            flags &= ~SFX_PLAYING;
            e->unk24 = 0;
            e->unk10 = flags;
            continue;
        }
        hi = (pan & 0x80) | slot;
        pan &= 0x7F;
        if (flags & SFX_MIRROR) {
            pan = 0x80 - pan;
            if (pan == 0x80) {
                pan = 0x7F;
            }
            hi ^= 0x80;
        }
        ratio.f = alCents2Ratio(pitch);
        if (voice == 0) {
            switch (flags & SFX_FX_MASK) {
                case 0:
                    fx = D_80041FD9;
                    break;
                case 0x400:
                    fx = 0;
                    break;
                default:
                    fx = 1;
                    break;
            }
            voice = sound_voice_play(0, sound, vol, pan, pitch, hi, fx);
            if (voice != 0) {
                flags |= SFX_PLAYING;
                e->unk0 = sound;
            }
        } else {
            if (vol != e->unk26) {
                sound_voice_set_param(voice, 8, vol);
            }
            if (pan != (e->unk22 & 0x7F)) {
                sound_voice_set_param(voice, 4, pan);
            }
            if (hi != (e->unk23 | (e->unk22 & 0x80))) {
                sound_voice_set_param(voice, 0x100, hi);
            }
            if (flags & SFX_SMOOTH) {
                d = (s32) ((e->unk28 - dist) * g_frame_ticks) / 3;
                if (d >= 367) {
                    k = 2.0f;
                } else {
                    k = 367.0f / (f32) (367 - d);
                    if (2.0f < k) {
                        k = 2.0f;
                    } else if (k < 0.5f) {
                        k = 0.5f;
                    }
                }
                ratio.f *= k;
                ratio.f = e->unk2C + (ratio.f - e->unk2C) * 0.3f;
            }
            if (ratio.f != e->unk2C) {
                sound_voice_set_param(voice, 0x11, ratio.i);
            }
        }
        e->unk28 = dist;
        e->unk26 = vol;
        e->unk22 = pan | hi;
        e->unk23 = slot;
        e->unk2C = ratio.f;
        e->unk24 = voice;
        e->unk10 = flags;
    }
}
/* was func_10011BB8 */
void sound_update_frame(void) {
    s32 i;
    s32 j;
    s32 step;

    if (D_80041F60 == 0 && D_80041F61 == 0) {
        for (i = 0; i <= g_last_player_index; i++) {
            u8 *obj = (u8 *)&g_player_views[i];

            if (g_last_player_index != 0 || (*(s32 *)(obj + 0x2C) & 0x80000)) {
                D_80042308[i].x = *(f32 *)(obj + 0x2F8);
                D_80042308[i].y = *(f32 *)(obj + 0x2FC);
                D_80042308[i].z = *(f32 *)(obj + 0x300);
            } else {
                D_80042308[i].x = *(f32 *)(obj + 0x2A4);
                D_80042308[i].y = *(f32 *)(obj + 0x2A8);
                D_80042308[i].z = *(f32 *)(obj + 0x2AC);
            }
            D_80042308[i].ex = *(f32 *)(obj + 0x2F8);
            D_80042308[i].ey = *(f32 *)(obj + 0x2FC);
            D_80042308[i].ez = *(f32 *)(obj + 0x300);
            D_80042308[i].f = *(f32 *)(obj + 0x380);
        }
        sound_stop_queue_process();
        sfx_emitters_update(D_80041FE0, &D_80042B00, 0, D_80042B00);
        for (i = 0, j = 0; i < D_80042B00; i++) {
            D_80041FE0[j] = D_80041FE0[i];
            if (!(D_80041FE0[j].unk10 & 0x80)) {
                j++;
            }
        }
        D_80042B00 = j;
    }
    if (D_80041F54 != D_80041FDC || D_80041F60 != D_80041F61) {
        if (D_80041F61 == 1) {
            n_sndp_set_group_volume(0, 0);
            n_sndp_set_group_volume(1, 0);
        } else {
            n_sndp_set_group_volume(0, D_80041F54);
            n_sndp_set_group_volume(1, D_80041F54);
            step = (D_80041FDC - D_80041F54) * D_80041F58;
            if (step != 0) {
                D_80041F54 += step;
            } else {
                D_80041F54 = D_80041FDC;
            }
        }
        D_80041F60 = D_80041F61;
    }
}

/* was func_10011E88 */
void sound_level_hook_nop(s32 arg0) {
}

/* was func_10011E94 */
void sound_set_pause_mute(s32 arg0) {
    if (arg0) {
        D_80041F61 = 1;
    } else {
        D_80041F61 = 0;
    }
}

s32 floor_flags_surface_type(s32);
u16 sound_pick_variant(s32, u16); /* P157: two parameters (the asm reads a0 / a1 only, as every other caller declares) */
typedef struct { u16 a; u16 b; } SndPair;
// rodata_inject: cdefined 0x2C5A0 0x2C758
const SndPair D_8002C5A0[22][5] = {
    { { 0x0000, 0 }, { 0x0000, 0 }, { 0x0000, 0 }, { 0x0000, 0 }, { 0x0000, 0 } },
    { { 0x025A, 4 }, { 0x0254, 4 }, { 0x0258, 2 }, { 0x0253, 1 }, { 0x02AB, 4 } },
    { { 0x0248, 4 }, { 0x024C, 4 }, { 0x0250, 2 }, { 0x0252, 1 }, { 0x02AB, 4 } },
    { { 0x0270, 4 }, { 0x026A, 4 }, { 0x026E, 2 }, { 0x0269, 1 }, { 0x02AB, 4 } },
    { { 0x029C, 4 }, { 0x0296, 4 }, { 0x029A, 2 }, { 0x0295, 1 }, { 0x02AB, 4 } },
    { { 0x023D, 4 }, { 0x0241, 4 }, { 0x0245, 2 }, { 0x0247, 1 }, { 0x02AB, 4 } },
    { { 0x0265, 4 }, { 0x025F, 4 }, { 0x0263, 2 }, { 0x025E, 1 }, { 0x02AB, 4 } },
    { { 0x02A7, 4 }, { 0x02A1, 4 }, { 0x02A5, 2 }, { 0x02A0, 1 }, { 0x02AB, 4 } },
    { { 0x0248, 4 }, { 0x024C, 4 }, { 0x0250, 2 }, { 0x0252, 1 }, { 0x02AB, 4 } },
    { { 0x027B, 4 }, { 0x0275, 4 }, { 0x0279, 2 }, { 0x0274, 1 }, { 0x02AB, 4 } },
    { { 0x0286, 4 }, { 0x0280, 4 }, { 0x0284, 2 }, { 0x027F, 1 }, { 0x02AB, 4 } },
    { { 0x0286, 4 }, { 0x0280, 4 }, { 0x0284, 2 }, { 0x027F, 1 }, { 0x02AB, 4 } },
    { { 0x009E, 1 }, { 0x009E, 1 }, { 0x009E, 1 }, { 0x009E, 1 }, { 0x02AB, 4 } },
    { { 0x025A, 4 }, { 0x0254, 4 }, { 0x0258, 2 }, { 0x0253, 1 }, { 0x02AB, 4 } },
    { { 0x0000, 0 }, { 0x0000, 0 }, { 0x0000, 0 }, { 0x0000, 0 }, { 0x0000, 0 } },
    { { 0x0291, 4 }, { 0x028B, 4 }, { 0x028F, 2 }, { 0x028A, 1 }, { 0x02AB, 4 } },
    { { 0x009F, 0 }, { 0x009F, 0 }, { 0x009F, 0 }, { 0x009F, 0 }, { 0x02AB, 4 } },
    { { 0x0291, 4 }, { 0x028B, 4 }, { 0x028F, 2 }, { 0x028A, 1 }, { 0x02AB, 4 } },
    { { 0x00A0, 0 }, { 0x00A0, 0 }, { 0x00A0, 0 }, { 0x00A0, 0 }, { 0x02AB, 4 } },
    { { 0x0286, 4 }, { 0x0280, 4 }, { 0x0284, 2 }, { 0x027F, 1 }, { 0x02AB, 4 } },
    { { 0x0000, 10000 }, { 0x1D4C, 11000 }, { 0x2328, 11000 }, { 0x55F0, 16384 }, { 0x2328, 11000 } },
    { { 0x2328, 9000 }, { 0x3FFE, 9000 }, { 0x2328, 9000 }, { 0x2328, 9000 }, { 0x0000, 0 } },
};

/* was func_10011EB8 */
u16 sound_surface_footstep(s32 arg0, s16 *arg1, s32 arg2)
{
  s32 *new_var;
  s32 v;
  arg0 = floor_flags_surface_type(arg0);
  if (arg1 != 0)
  {
    if (g_last_player_index != 0)
    {
      *arg1 = 0x7FFF / (g_last_player_index + 1);
    }
    else
    {
      *arg1 = 0x7FFF;
    }
  }
  v = D_8002C5A0[arg0][arg2].a;
  if (D_8002C5A0[arg0][arg2].b >= 2)
  {
    new_var = &arg2; // fakematch: permuter, base table reg t0 and arg2 reloads
    if (!D_8002C5A0 && !D_8002C5A0 && !D_8002C5A0) { // fakematch: permuter, always false
    }
    v = sound_pick_variant(v, D_8002C5A0[arg0][*new_var].b);
  }
  return v;
}
// NON-MATCHING: whats going on here
// u16 sound_surface_footstep(s32 arg0, s16 *arg1, s32 arg2, s32 arg3) {
//     struct120 *temp_v1_2;
//     s32 temp_v0;
//     s32 temp_a0;
//
//     temp_v0 = func_1510F8CC(arg0);
//     if (arg1 != NULL) {
//         if (g_last_player_index != 0) {
//             *arg1 = 0x7FFF / (g_last_player_index + 1);
//         } else {
//             *arg1 = 0x7FFF;
//         }
//     }
//     temp_v1_2 = &D_8002C240[temp_v0 + arg2];
//     temp_a0 = temp_v1_2->unk0;
//     if (temp_v1_2->unk2 >= 2) {
//         temp_a0 = sound_pick_variant(temp_v0, temp_v1_2->unk2);
//     }
//     return temp_a0;
// }
