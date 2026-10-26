#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15103800 */
void sfx_cooldown_clear(void) {
    bzero(D_800D9AB0, 8); // bzero
}

/* was func_15103828 */
void sfx_cooldown_tick(void) {
    u16 temp_v1;
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (D_800D9AB0[i]) {
            if (D_800D9AB0[i] > D_800BE9E4)
            {
                D_800D9AB0[i] -= D_800BE9E4;
            } else {
              D_800D9AB0[i] = 0;
            }
        }
    }
}

// need to figure out the structs
/* positional sound slot (SfxEnt in init_EB00.c, 0x30 bytes); only the fields the callbacks use are named */
typedef struct {
    u16 sound;      /* 0x00 */
    s16 x;          /* 0x02 */
    s16 y;          /* 0x04 */
    s16 z;          /* 0x06 */
    u16 unk8;       /* 0x08 */
    s16 unkA;       /* 0x0A */
    s32 vol;        /* 0x0C */
    s32 flags;      /* 0x10 */
    void *callback; /* 0x14 */
    s32 state;      /* 0x18: callback state (sfx_emitter_start's arg8: high half = queued sound, low half = timer) */
    u8 *obj;        /* 0x1C: sfx_emitter_start's arg9, the object that makes the sound */
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u16 voice;      /* 0x24 */
    u16 unk26;
    u16 unk28;
    u16 pad2A;
    f32 unk2C;
} SfxEnt_130CB0;
#ifdef NON_MATCHING
// object_sound_follow_cam: P253. sfx_emitter_start callback (s32 (SfxEnt *, s32 *pos, u32 *vol, s32 *pan, s32 *pitch,
// s32 *slot, u16 *sound), called from the sound update in init_EB00.c; non-zero = free the slot) of the sounds
// object_sound_play_cooldown starts for an object with a camera. The slot follows the object's position. With a timer (low half of
// state, signed): a sound the update is about to start is queued instead (high half) and sound 0x5B0 is started
// (volume 25000, 100, 0x78); otherwise the timer counts down by D_800BE9E4 and at 0 the queued sound is handed back
// (*sound, slot sound, *vol = slot volume, *pos = 1, state cleared). Without a timer: *vol = slot volume, *pos = 1;
// with no voice yet the slot ends (sound 0x5B1 started, returns 1); else the object's voice (+0x8C) is replaced by
// this slot's voice (the old one stopped with sound_voice_stop) and flag 0x80 is cleared.
/* was func_15103910 */
s32 object_sound_follow_cam(SfxEnt_130CB0 *e, s32 *pos, u32 *vol, s32 *pan, s32 *pitch, s32 *slot, u16 *sound) {
    u8 *obj = e->obj;
    s32 state = e->state;
    s16 timer = state;

    e->x = (s32) *(f32 *) (obj + 0x14);
    e->y = (s32) *(f32 *) (obj + 0x18);
    e->z = (s32) *(f32 *) (obj + 0x1C);
    if (timer != 0) {
        if (*sound != 0) {
            e->state = (*sound << 16) | (state & 0xFFFF);
            e->sound = 0;
            *sound = 0;
            actor_sound_play2(0x5B0, (struct127 *) obj, 25000, 100, 0x78);
            return 0;
        }
        timer -= D_800BE9E4;
        if (timer <= 0) {
            *sound = state >> 16;
            e->sound = state >> 16;
            *vol = e->vol;
            *pos = 1;
            e->state = 0;
            return 0;
        }
    } else {
        *vol = e->vol;
        *pos = 1;
        if (e->voice == 0) {
            actor_sound_play2(0x5B1, (struct127 *) obj, e->vol, e->unkA, e->unk8);
            return 1;
        }
        if (e->voice != *(u16 *) (obj + 0x8C)) {
            sound_voice_stop(*(u16 *) (obj + 0x8C));
            *(u16 *) (obj + 0x8C) = e->voice;
        }
        e->flags &= ~0x80;
        state = e->state;
    }
    e->state = (state & 0xFFFF0000) | timer;
    return 0;
}

#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/object_sound_follow_cam.s")
#endif

#ifdef NON_MATCHING
// object_sound_delayed: P253. sfx_emitter_start callback (same signature as object_sound_follow_cam) of the sounds object_sound_play_cooldown
// starts for an object without a camera (state = flag 0x8000 from its arg4 | 0x10). The slot follows the object's
// position. With a timer (state & 0x7FFF): a sound the update is about to start is queued (high half) and sound 0x5B0
// is started (volume -25000); otherwise the timer counts down by D_800BE9E4 and once it would reach 0 the queued
// sound is handed back (*sound, slot sound; the timer bits cleared). Without a timer: with no voice yet the slot ends
// (sound 0x5B1, returns 1); else, unless flag 0x8000 is set, sound_voice_set_param(voice, -0x8000, 2) once, the state is
// cleared and flag 0x80 of the slot is cleared.
/* was func_15103AA0 */
s32 object_sound_delayed(SfxEnt_130CB0 *e, s32 *pos, u32 *vol, s32 *pan, s32 *pitch, s32 *slot, u16 *sound) {
    u8 *obj = e->obj;
    s32 state = e->state;
    s32 timer = state & 0x7FFF;

    e->x = (s32) *(f32 *) (obj + 0x14);
    e->y = (s32) *(f32 *) (obj + 0x18);
    e->z = (s32) *(f32 *) (obj + 0x1C);
    if (timer != 0) {
        if (*sound != 0) {
            e->state = (*sound << 16) | (state & 0xFFFF);
            e->sound = 0;
            *sound = 0;
            actor_sound_play2(0x5B0, (struct127 *) obj, -25000, e->unkA, e->unk8);
            return 0;
        }
        if ((u32) timer <= (u32) D_800BE9E4) {
            *sound = state >> 16;
            e->sound = state >> 16;
            e->state &= ~0x7FFF;
            return 0;
        }
        timer -= D_800BE9E4;
    } else {
        if (e->voice == 0) {
            actor_sound_play2(0x5B1, (struct127 *) obj, -25000, e->unkA, e->unk8);
            return 1;
        }
        if (state != 0) {
            if (!(state & 0x8000)) {
                sound_voice_set_param(e->voice, -0x8000, 2);
            }
            e->state = 0;
        }
        e->flags &= ~0x80;
        state = e->state;
    }
    e->state = (state & ~0x7FFF) | timer;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/object_sound_delayed.s")
#endif
#ifdef NON_MATCHING

/* was func_15103C14 */
void object_sound_play_cooldown(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    s32 sp48;
    u16 *sp40;
    s32 var_s1;
    struct127 *temp_v0_2;
    u16 *temp_v0;

    var_s1 = arg0;
    temp_v0 = &D_800D9AB0[arg3];
    sp48 = 0;
    if ((*temp_v0 == 0) || (var_s1 == 0x58D)) {
        sp40 = temp_v0;
        temp_v0_2 = obj_find_by_spawn(arg1);
        if ((temp_v0_2 != NULL) && (actor_sound2_is_playing(temp_v0_2) == 0)) {
            if (arg2 != 0) {
                if (arg4 != 0) {
                    var_s1 += (random_int() % arg2) * 2;
                } else {
                    var_s1 += random_int() % arg2;
                }
            }
            if (temp_v0_2->camera != NULL) {
                sp48 = 1;
            } else if (arg4 != 0) {
                var_s1 += 1;
            }
            if (sp48 != 0) {
                sfx_emitter_start(var_s1 & 0xFFFF, (s16) (s32) temp_v0_2->x_position, (s16) (s32) temp_v0_2->y_position, (s16) (s32) temp_v0_2->z_position, 0x7530, 0x7FFFU, 0x7FFE, (s32) &object_sound_follow_cam, (u8 *)0x10, (s32) temp_v0_2, 0x100, 0);
            } else {
                sfx_emitter_start(var_s1 & 0xFFFF, (s16) (s32) temp_v0_2->x_position, (s16) (s32) temp_v0_2->y_position, (s16) (s32) temp_v0_2->z_position, 0x7FBC, 0x7FFFU, 0x7FFE, (s32) &object_sound_delayed, (u8 *) ((arg4 << 0xF) | 0x10), (s32) temp_v0_2, 0x100, 0);
            }
            *sp40 = 0x1F4;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/object_sound_play_cooldown.s")
#endif