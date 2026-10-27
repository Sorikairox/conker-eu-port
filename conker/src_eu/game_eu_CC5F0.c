#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void sound_loop_at_object(u16 arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4);
s32 world_record_find(u8);
s32 world_record_touched_by(s32, s32);
s32 world_record_first_toucher(s32);
s32 obj_slot_by_spawn(s32);


s32 rail_node_position(s32, f32 *, f32 *, f32 *);
s32 rail_node_find_by_tag(s32);
s32 impact_effect_at_world_object(s32);
void vtx_colour_record_blend(s32, s32, s32);
extern s32 g_world_obj_type_cbs; /* was D_80089030 */

/* was func_1509EDE0 */
s32 event_action_world_object(s32 arg0, u32 arg1, u8 *arg2) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        s32 u3C;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 temp_v1_12;
    s32 temp_v1_13;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_v1_9;
    u8 temp_t7;

    temp_v0 = world_record_find(arg0 & 0xFF);
    if (temp_v0 == 0) {
        goto block_62;
    }
    switch (arg1) {
    case 0:
        (*(s8 *)((u8 *)temp_v0 + 0x6E)) = 0;
        if ((*(s32 *)((u8 *)temp_v0 + 0x38)) != 0) {
            (*(u8 *)((u8 *)temp_v0 + 0x6F)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x6F)) | 0xF);
        }
        return 1;
    case 1:
        (*(s8 *)((u8 *)temp_v0 + 0x6E)) = 1;
        return 1;
    case 2:
        temp_v1 = (*(s32 *)((u8 *)arg2 + 8));
        if (temp_v1 != 0x7FFFFFFF) {
            (*(s16 *)((u8 *)temp_v0 + 0x10)) = (s16) temp_v1;
        }
        temp_v1_2 = (*(s32 *)((u8 *)arg2 + 0xC));
        if (temp_v1_2 != 0x7FFFFFFF) {
            (*(s16 *)((u8 *)temp_v0 + 0x12)) = (s16) temp_v1_2;
        }
        temp_v1_3 = (*(s32 *)((u8 *)arg2 + 0x10));
        if (temp_v1_3 != 0x7FFFFFFF) {
            (*(s16 *)((u8 *)temp_v0 + 0x14)) = (s16) temp_v1_3;
        }
        return 1;
    case 12:
        sp.u3C = temp_v0;
        temp_v0_2 = rail_node_find_by_tag((*(s32 *)((u8 *)arg2 + 8)));
        if (temp_v0_2 != -1) {
            rail_node_position(temp_v0_2, &sp.u38, &sp.u34, &sp.u30);
            (*(s16 *)((u8 *)sp.u3C + 0x10)) = (s16) (s32) sp.u38;
            (*(s16 *)((u8 *)sp.u3C + 0x12)) = (s16) ((*(s32 *)((u8 *)arg2 + 0xC)) + (s32) sp.u34);
            (*(s16 *)((u8 *)sp.u3C + 0x14)) = (s16) (s32) sp.u30;
        }
        return 1;
    case 3:
        temp_f0 = (f32) (*(s32 *)((u8 *)arg2 + 8));
        if (temp_f0 != 2.0132659e9f) {
            (*(f32 *)((u8 *)temp_v0 + 0x7C)) = (f32) (temp_f0 / 65536.0f);
        }
        temp_f0_2 = (f32) (*(s32 *)((u8 *)arg2 + 0xC));
        if (temp_f0_2 != 2.0132659e9f) {
            (*(f32 *)((u8 *)temp_v0 + 0x80)) = (f32) (temp_f0_2 / 65536.0f);
        }
        temp_f0_3 = (f32) (*(s32 *)((u8 *)arg2 + 0x10));
        if (temp_f0_3 != 2.0132659e9f) {
            (*(f32 *)((u8 *)temp_v0 + 0x84)) = (f32) (temp_f0_3 / 65536.0f);
        }
        return 1;
    case 4:
        temp_v1_4 = (*(s32 *)((u8 *)arg2 + 8));
        if (temp_v1_4 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0x7C)) = (*(f32 *)&(temp_v1_4));
        }
        temp_v1_5 = (*(s32 *)((u8 *)arg2 + 0xC));
        if (temp_v1_5 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0x80)) = (*(f32 *)&(temp_v1_5));
        }
        temp_v1_6 = (*(s32 *)((u8 *)arg2 + 0x10));
        if (temp_v1_6 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0x84)) = (*(f32 *)&(temp_v1_6));
        }
        return 1;
    case 5:
        (*(s32 *)((u8 *)temp_v0 + 0x3C)) = (s32) (*(s32 *)((u8 *)arg2 + 8));
        return 1;
    case 6:
        temp_t7 = (*(u8 *)((u8 *)temp_v0 + 0x73)) & 0xFFFC;
        (*(u8 *)((u8 *)temp_v0 + 0x73)) = temp_t7;
        (*(u8 *)((u8 *)temp_v0 + 0x73)) = (u8) (temp_t7 | ((*(s32 *)((u8 *)arg2 + 8)) & 3));
        return 1;
    case 7:
        if ((*(s32 *)((u8 *)arg2 + 8)) != 0) {
            (*(u8 *)((u8 *)temp_v0 + 0x73)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x73)) | 4);
            return 1;
        }
        (*(u8 *)((u8 *)temp_v0 + 0x73)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 0x73)) & 0xFFFB);
        return 1;
    case 8:
        temp_t8 = (*(s32 *)((u8 *)temp_v0 + 0x3C)) & 0xFFFF;
        (*(s32 *)((u8 *)temp_v0 + 0x3C)) = temp_t8;
        (*(s32 *)((u8 *)temp_v0 + 0x3C)) = (s32) (temp_t8 | ((*(s32 *)((u8 *)arg2 + 8)) << 0x10));
        (*(f32 *)((u8 *)temp_v0 + 0x7C)) = (*(f32 *)&((*(s32 *)((u8 *)arg2 + 0xC))));
        return 1;
    case 9:
        impact_effect_at_world_object(temp_v0);
    default:
block_62:
        return 0;
    case 10:
        (*(s32 *)((u8 *)temp_v0 + 0x38)) = (*(s32 *)((u8 *) &g_world_obj_type_cbs + (*(s32 *)((u8 *)arg2 + 8)) * 0xC));
        (*(s32 *)((u8 *)temp_v0 + 0x78)) = (s32) (*(s32 *)((u8 *) &g_world_obj_type_cbs + (*(s32 *)((u8 *)arg2 + 8)) * 0xC + 4));
        (*(s8 *)((u8 *)temp_v0 + 0x92)) = (s8) (*(s32 *)((u8 *) &g_world_obj_type_cbs + (*(s32 *)((u8 *)arg2 + 8)) * 0xC + 8));
        goto block_62;
    case 11:
        vtx_colour_record_blend((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), (*(u8 *)((u8 *)temp_v0 + 0x72)));
        goto block_62;
    case 13:
        (*(u8 *)((u8 *)temp_v0 + 0x4F)) = (u8) ((*(s32 *)((u8 *)arg2 + 8)) | ((*(u8 *)((u8 *)temp_v0 + 0x4F)) & ~(*(s32 *)((u8 *)arg2 + 0xC))));
        goto block_62;
    case 14:
        temp_v1_7 = (*(s32 *)((u8 *)arg2 + 8));
        if (temp_v1_7 != 0x7FFFFFFF) {
            (*(s16 *)((u8 *)temp_v0 + 0x5A)) = (s16) temp_v1_7;
        }
        temp_v1_8 = (*(s32 *)((u8 *)arg2 + 0xC));
        if (temp_v1_8 != 0x7FFFFFFF) {
            (*(s16 *)((u8 *)temp_v0 + 0x5C)) = (s16) temp_v1_8;
        }
        temp_v1_9 = (*(s32 *)((u8 *)arg2 + 0x10));
        if (temp_v1_9 != 0x7FFFFFFF) {
            (*(s16 *)((u8 *)temp_v0 + 0x5E)) = (s16) temp_v1_9;
        }
        goto block_62;
    case 15:
        temp_v1_10 = (*(s32 *)((u8 *)arg2 + 8));
        if (temp_v1_10 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0x60)) = (f32) temp_v1_10;
        }
        temp_v1_11 = (*(s32 *)((u8 *)arg2 + 0xC));
        if (temp_v1_11 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0x64)) = (f32) temp_v1_11;
        }
        temp_v1_12 = (*(s32 *)((u8 *)arg2 + 0x10));
        if (temp_v1_12 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0x68)) = (f32) temp_v1_12;
        }
        goto block_62;
    case 16:
        temp_v1_13 = (*(s32 *)((u8 *)arg2 + 8));
        if (temp_v1_13 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) temp_v1_13;
        }
        temp_v1_14 = (*(s32 *)((u8 *)arg2 + 0xC));
        if (temp_v1_14 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) temp_v1_14;
        }
        temp_v1_15 = (*(s32 *)((u8 *)arg2 + 0x10));
        if (temp_v1_15 != 0x7FFFFFFF) {
            (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) temp_v1_15;
        }
        goto block_62;
    case 17:
        (*(s16 *)((u8 *)temp_v0 + 0x88)) = (s16) (*(s32 *)((u8 *)arg2 + 8));
        goto block_62;
    case 18:
        (*(s8 *)((u8 *)temp_v0 + 0x8A)) = (s8) (*(s32 *)((u8 *)arg2 + 8));
        goto block_62;
    }
}
/* event_query_world_object: handler of g_event_query_fns for world records (event VM query; record id = the id word's
 * low byte, what = args[1], args[2] = operand). 19 = record touched by anything (world_record_touched_by(rec, -1)),
 * 20 = touched by the object whose spawn id is args[2] (obj_slot_by_spawn), 21 = touched by any game object whose
 * interaction_state is args[2], 22 = flags +0x4F bit 2, 23 = first toucher's slot | 0x2000 (-1 -> 0), 24 = flags +0x4F,
 * 25 = s32 +0x84 == s32 +0x7C, 26 = word +0x3C, 27 = +0x73 & 3, 28 = +0x6E == 0, 29..31 = s16 +0x10 / +0x12 / +0x14,
 * 32 = (s32) f32 +0x08, 33 = raw word +0x7C / +0x80 / +0x84 by args[2], 34 = the same three fields as f32 truncated to
 * s32, 35 = +0x73 bit 2; anything else / no record = 0. The VM uses the full 32-bit result.
 * P343: the conversion returned u8 (cut 0x2000 / the high bits / the sign), read case 34's +0x7C and +0x84 as s32 and
 * case 33's +0x80 as its first byte, ran case 19 / 20 as the 21 loop and stepped that loop by 0x32C objects. */
/* was func_1509F254 */
s32 event_query_world_object(s32 id, s32 what, s32 *args) {
    s32 rec;      /* was temp_v0 */
    s32 toucher;  /* was temp_v0_2 */
    s32 field;    /* was temp_v0_3 / temp_v0_4 */
    s32 i;        /* was var_s0 */

    rec = world_record_find(id & 0xFF);
    if (rec == 0) {
        return 0;
    }
    switch (what) {
    case 19:
        return world_record_touched_by(rec, -1);
    case 20:
        return world_record_touched_by(rec, obj_slot_by_spawn(args[2] & 0xFFFF0FFF));
    case 21:
        for (i = 0; i < 25; i++) {
            if (g_objects[i].interaction_state == args[2] && world_record_touched_by(rec, i) != 0) {
                return 1;
            }
        }
        return 0;
    case 22:
        return ((*(u8 *)(rec + 0x4F)) & 4) == 4;
    case 23:
        toucher = world_record_first_toucher(rec);
        if (toucher < 0) {
            return 0;
        }
        return toucher | 0x2000;
    case 24:
        return *(u8 *)(rec + 0x4F);
    case 25:
        return *(s32 *)(rec + 0x84) == *(s32 *)(rec + 0x7C);
    case 26:
        return *(s32 *)(rec + 0x3C);
    case 27:
        return (*(u8 *)(rec + 0x73)) & 3;
    case 28:
        return (*(u8 *)(rec + 0x6E)) == 0;
    case 29:
        return *(s16 *)(rec + 0x10);
    case 30:
        return *(s16 *)(rec + 0x12);
    case 31:
        return *(s16 *)(rec + 0x14);
    case 32:
        return (s32) *(f32 *)(rec + 8);
    case 33:
        field = args[2];
        if (field == 0) {
            return *(s32 *)(rec + 0x7C);
        }
        if (field == 1) {
            return *(s32 *)(rec + 0x80);
        }
        if (field == 2) {
            return *(s32 *)(rec + 0x84);
        }
        return 0;
    case 34:
        field = args[2];
        if (field == 0) {
            return (s32) *(f32 *)(rec + 0x7C);
        }
        if (field == 1) {
            return (s32) *(f32 *)(rec + 0x80);
        }
        if (field == 2) {
            return (s32) *(f32 *)(rec + 0x84);
        }
        return 0;
    case 35:
        return ((*(u8 *)(rec + 0x73)) & 4) != 0;
    }
    return 0;
}
u16 sound_play_plain(s32, s32, s32, s32);
u32 sound_play_random_on_object(s32, s32, u32, u32, s32, s16, s32);
void sound_play_random_world_object(s32, s32, s32, s32, s16, s32);
u16 sound_play_random_at_trigger(s32, s32, u16, s32, u32);
u16 sound_play_random(s32, s32, s32);
void sound_play_on_object(u16, s32, s32, s16, s32, s32);
u16 sound_play_at_object(s32, s32, u16, s32, s32);
void object_sound_play_cooldown(s32, s32, u32, s32, s32);
extern s32 g_event_arg_count;           /* sound mode; was D_800D3C60 */
/* event_sound_command: handler 7 of the event VM's native table g_event_native_start_fns (id = the command word without its
 * table nibble, args = the VM stack). In sound mode 1 (g_event_arg_count) every command just plays sound id (volume
 * 0x7FFF, sound_play_plain). Otherwise by args[1]: 0 = random / positional sound by the kind nibble of args[5]
 * (0x2000 random pick from the range id..args[2] on object args[4], returns the remaining mask; 0x3000 / 0x4000
 * positional variants sound_play_random_world_object / sound_play_random_at_trigger, the latter returns its handle unpacked; other kinds
 * sound_play_random), 1 = plain sound with the volume / pan arguments by mode (args[3] from mode 4, args[4] from mode
 * 5), 2 = object sound sound_play_on_object (forced with args[6] from mode 7), 3 = sound_play_at_object, 4 = object_sound_play_cooldown
 * (returns 0x7000). A sound handle h is returned as (h << 16) | 0x7000, 0 stays 0. */
/* was func_1509F4D0 */
s32 event_sound_command(s32 id, s32 *args, s32 *operand) {
    s32 h;
    s32 kind;
    s32 vol;
    s32 pan;
    s32 force;

    if (g_event_arg_count == 1) {
        h = sound_play_plain(id, 0x7FFF, 0, 0x40);
    } else {
        switch ((u32) args[1]) {
            case 0:
                kind = args[5];
                switch (kind & 0xF000) {
                    case 0x2000:
                        return sound_play_random_on_object(id, args[2] & 0xFFF, args[3], args[4], kind & 0xFFF, args[6], args[7]);
                    case 0x3000:
                        sound_play_random_world_object(id, args[2] & 0xFFF, args[4], kind & 0xFFF, args[6], args[7]);
                        return 0;
                    case 0x4000:
                        return sound_play_random_at_trigger(id, args[2] & 0xFFF, args[4], kind & 0xFFF, args[6]);
                    default:
                        h = sound_play_random(id, args[2] & 0xFFF, args[4]);
                        break;
                }
                break;
            case 1:
                pan = 0x40;
                if (g_event_arg_count < 4) {
                    vol = 0;
                } else {
                    vol = args[3];
                    if (g_event_arg_count == 5) {
                        pan = args[4];
                    }
                }
                h = sound_play_plain(id, args[2], vol, pan);
                break;
            case 2:
                force = 0;
                if (g_event_arg_count >= 7 && args[6] != 0) {
                    force = 1;
                }
                sound_play_on_object(id & 0xFFF, args[2], args[3] & 0xFFF, args[4], args[5], force);
                h = 0;
                break;
            case 3:
                h = sound_play_at_object(id, args[3] & 0xFFF, args[2], args[4], args[5]);
                break;
            case 4:
                object_sound_play_cooldown(id, args[3] & 0xFFF, args[2], args[4], args[5]);
                return 0x7000;
            default:
                return 0;
        }
    }
    if (h != 0) {
        h = (h << 16) | 0x7000;
    }
    return h;
}

/* was func_1509F728 */
s32 event_sound_stop(s32 arg0, s32 *arg1) {
    if (arg0 != 0) {
        sound_voice_stop((arg1[0] & 0xFFFF0000) >> 16);
    }
    return 1;
}

void sound_stop_on_object(s32, s32);
/* was func_1509F764 */
s32 event_action_sound(s32 arg0, s32 arg1, s32 *arg2) {
    switch (arg1) {
    case 1:
        sound_stop_on_object(arg2[2] & 0xFFF, 0);
        return 1;
    case 0:
        sound_stop_on_object(arg2[2] & 0xFFF, 1);
        return 1;
    case 2:
        sound_loop_at_object((u32)(arg2[0] & 0xFFFF0000) >> 16, arg2[2] & 0xFFF, arg2[3], arg2[4], arg2[5]);
        return 1;
    }
    return 0;
}

/* was func_1509F81C */
s32 event_query_sound(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

/* was func_1509F834 */
u32 sound_play_random_on_object(s32 arg0, s32 arg1, u32 mask, u32 arg3, s32 arg4, s16 arg5, s32 arg6) {
    struct127 *p;
    u8 n;
    u8 r;

    p = obj_find_by_spawn(arg4);
    if (arg3 >= 0x8000U) {
        arg3 = 0x7FFF;
    }
    if (p == NULL) {
        return mask;
    }
    if (actor_sound2_is_playing(p) == 0) {
        if (mask == 0) {
            mask = -1U >> (32 - (u8)(arg1 - arg0 + 1));
        }
        n = arg1 - arg0 + 1;
        do {
            r = random_int() % (u32)n;
        } while (!((1 << r) & mask));
        if (actor_sound_play2((u16)(r + arg0), p, arg3, arg5, arg6) != 0) {
            mask ^= 1 << r;
        }
    }
    return mask;
}

s32 sound_pick_variant(s32, s32);
s32 world_record_find(u8);
s32 world_object_sound_play(s32, s32, s32, s16, s16, s32);

/* was func_1509F95C */
void sound_play_random_world_object(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4, s32 arg5) {
    s32 sp24;

    sp24 = world_record_find(arg3);
    world_object_sound_play(sp24, sound_pick_variant(arg0, ((arg1 - arg0) + 1) & 0xFF), arg2, arg4, arg5, 0);
}

/* P226: the asm leaves sound_play_at's handle in v0 and event_sound_command returns it: NM returns it. */
/* was func_1509F9C8 */
u16 sound_play_random_at_trigger(s32 arg0, s32 arg1, u16 arg2, s32 arg3, u32 arg4) {
    u8 *temp_v1;
    s32 temp_t0;
    u8 *sp34;

    temp_v1 = (arg3 * 0x34) + g_level_zones;
    temp_t0 = (*(s16 *)((u8 *)temp_v1 + 6));
    if (arg4 >= (u32) temp_t0) {
        arg4 = temp_t0 - 1;
    }
    sp34 = temp_v1;
    return sound_play_at(sound_pick_variant(arg0, ((arg1 - arg0) + 1) & 0xFF), arg2, 0, 0U, 0, (s16) (s32) (*(s16 *)temp_v1), (s16) (s32) (*(s16 *)((u8 *)temp_v1 + 2)), (s16) (s32) (*(s16 *)((u8 *)temp_v1 + 4)), (s16) arg4, (s16) (s32) temp_t0);
}

/* was func_1509FA88 */
u16 sound_play_random(s32 arg0, s32 arg1, s32 arg2) {
    return sound_play_2d(sound_pick_variant(arg0, (u8)(arg1 - arg0 + 1)), arg2, 0x40, 0, 0);
}

/* was func_1509FAD4 */
void sound_play_on_object(u16 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    struct127 *obj = obj_find_by_spawn(arg2);

    if (obj != NULL) {
        if (arg5 || actor_sound2_is_playing(obj) == 0) {
            actor_sound_play2(arg0, obj, arg1, arg3, (u16) arg4);
        }
    }
}

/* was func_1509FB40 */
void sound_stop_on_object(s32 arg0, s32 arg1) {
    struct127 *temp_v0 = obj_find_by_spawn(arg0);

    if (temp_v0 != NULL) {
        if (arg1 != 0) {
            actor_sound2_stop(temp_v0);
        } else {
            actor_sound_stop(temp_v0);
        }
    }
}

/* was func_1509FB90 */
u16 sound_play_plain(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return sound_play_2d(arg0, arg1, arg3, arg2, 0);
}

/* was func_1509FBC8 */
u16 sound_play_at_object(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4) {
    struct127 *temp_v0;

    temp_v0 = obj_find_by_spawn(arg1);
    if (temp_v0 == NULL) {
        return 0;
    }
    return sound_play_at(arg0, arg2, 0, 0U, 0, (s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, (s16) arg3, (s16) arg4);
}
/* was func_1509FC5C */
void sound_loop_at_object(u16 arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4) {
    struct127 *temp_v0;

    temp_v0 = obj_find_by_spawn(arg1);
    sound_voice_update_3d(arg0, 0x7FFFU, arg2, 0U, 0, (s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, (s16) arg3, (s16) arg4);
}
/* was func_1509FCE0 */
s32 event_query_stub(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

s32 func_150ADC50();

/* was func_1509FCF8 */
s32 event_action_trap(s32 arg0, s32 arg1, s32 arg2) {
    func_150ADC50();
    return 0;
}
