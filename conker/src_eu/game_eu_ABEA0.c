#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void face_eye_blink_update(u8 *);
void face_anim_reset_default();
s32 face_blink_allowed(u8 *);
s32 face_anim_entry_get(s32 arg0, s32 arg1);
u32 face_anim_count(s32 arg0);
s32 *face_anim_body_table(s32 arg0, s32 *arg1);
void face_anim_start(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4);


/* P48: eye blink of object obj (+0x6A / +0x6B eyelid states, +0x6E countdown in frames of D_800BE9E4). Id 0x2B
 * and D_800C35EA == 1: nothing. A player-controlled object whose controller +0x120 is set keeps both eyes at 1.
 * When the countdown runs out (and +0x6C != 1) both states toggle; reopened eyes wait 10 + random % 140. */
/* was func_1507E690 */
void face_eye_blink_update(u8 *obj) {
    if (obj[4] == 0x2B || D_800C35EA == 1) {
        return;
    }
    if (obj[0x127] != 0xFF && (*(u8 **)(obj + 0x31C))[0x120] != 0) {
        obj[0x6A] = 1;
        obj[0x6B] = 1;
        return;
    }
    if (obj[0x6A] >= 3) {
        obj[0x6A] = 0;
    }
    if (obj[0x6B] >= 3) {
        obj[0x6B] = 0;
    }
    if (obj[0x6E] >= D_800BE9E4) {
        obj[0x6E] -= D_800BE9E4;
        return;
    }
    obj[0x6E] = 0;
    if (obj[0x6C] == 1) {
        return;
    }
    obj[0x6A] ^= 1;
    obj[0x6B] ^= 1;
    if (obj[0x6A] == 0) {
        obj[0x6E] = (u32)random_int() % 140 + 10;
    } else {
        obj[0x6E] = 1;
    }
}

/* face_update_hide_mask (P57): for model types 0xF / 0x46 / 0x4C, the DL hide mask +0x94 from the selector bytes +0x6C / +0x6D:
 * bits 1..6 set, then one of 8 / 0x10 / 4 (first selector 0 / 1 / other) and 0x20 / 0x40 / 2 (second) cleared.
 * Selector: >= 10: (v - 10) == 5 -> 0, == 1 -> 1, else 2; below 2: v + 1; else v. */
/* was func_1507E7A0 */
void face_update_hide_mask(struct127 *arg0) {
    u8 *o = (u8 *)arg0;
    s32 s[2];
    s32 i;
    s32 v;
    s32 type = o[4];

    if (type != 0xF && type != 0x46 && type != 0x4C) return;
    for (i = 0; i < 2; i++) {
        v = o[0x6C + i];
        s[i] = v;
        if (v >= 10) {
            v -= 10;
            if (v == 5) s[i] = 0;
            else if (v == 1) s[i] = 1;
            else s[i] = 2;
        } else if (v < 2) {
            s[i] = v + 1;
        }
    }
    *(u32 *)(o + 0x94) |= 0x7E;
    if (s[0] == 0) *(u32 *)(o + 0x94) &= ~8;
    else if (s[0] == 1) *(u32 *)(o + 0x94) &= ~0x10;
    else *(u32 *)(o + 0x94) &= ~4;
    if (s[1] == 0) *(u32 *)(o + 0x94) &= ~0x20;
    else if (s[1] == 1) *(u32 *)(o + 0x94) &= ~0x40;
    else *(u32 *)(o + 0x94) &= ~2;
}

void attachment_remove_by_slot(s32 arg0, s32 arg1);
void face_anim_apply(struct127 *, s32);

// obj_anim_set: switches the object to animation `anim` (+0x6F) if it is inside the object's table (face_anim_count):
// plays the old animation's first-frame sound (attachment_remove_by_slot), applies the new one (face_anim_apply) and sets the
// animation variant +0x135 to `variant`, or to the new entry's default (+3) when `variant` is 0. `void` under NM:
// the callers ignore the result.
/* was func_1507E8E0 */
void face_anim_set(u8 *arg0, s32 anim, s32 variant) {
    struct127 *obj = (struct127 *)arg0;
    u8 *entry;
    u8 *sounds;

    if (!(anim < (s32)face_anim_count((s32)obj))) {
        return;
    }
    entry = (u8 *)face_anim_entry_get((s32)obj, obj->unk6F);
    if (entry[4] != 0) {
        sounds = (u8 *)face_anim_body_table((s32)obj, NULL);
        if (sounds != NULL) {
            attachment_remove_by_slot((s32)obj, sounds[entry[4] - 1]);
        }
    }
    obj->unk6F = anim;
    face_anim_apply(obj, variant);
    if (variant != 0) {
        obj->unk135 = variant;
    } else {
        obj->unk135 = ((u8 *)face_anim_entry_get((s32)obj, anim))[3];
    }
}

void face_anim_play_body(s32, s32, s32);

/* Apply the current animation (+0x6F) of `obj`: its entry (face_anim_entry_get) gives a model / frame pair for
 * face_anim_play_body (entry +4 / +6), the animation set (+0x134, with +0x135 = `variant`, or the entry's default +3 when
 * `variant` is 0, only when the set changes), two bytes +0x6C / +0x6D = entry +0 / +1 plus 10, and +0x68 / +0x69
 * from entry +8 / +9, or the object type's defaults (D_800D1C90[id] +0x3B / +0x3C) when those are 0. */
/* was func_1507E9A8 */
void face_anim_apply(struct127 *obj, s32 variant) {
    u8 *entry = (u8 *) face_anim_entry_get((s32) obj, obj->unk6F);
    u8 *ob = (u8 *) obj;

    if (entry == NULL) {
        return;
    }
    face_anim_play_body((s32) obj, entry[4], *(u16 *) (entry + 6));
    if (entry[2] != obj->unk134) {
        obj->unk134 = entry[2];
        if (variant != 0) {
            obj->unk135 = variant;
        } else {
            obj->unk135 = entry[3];
        }
    }
    ob[0x6C] = entry[0] + 10;
    ob[0x6D] = entry[1] + 10;
    if (entry[8] != 0) {
        obj->unk68 = entry[8];
    } else {
        obj->unk68 = ((u8 *) D_800D1C90[obj->id])[0x3B];
    }
    if (entry[9] != 0) {
        obj->unk69 = entry[9];
    } else {
        obj->unk69 = ((u8 *) D_800D1C90[obj->id])[0x3C];
    }
}

s32 obj_current_part_model();

/* was func_1507EA98 */
s32 face_blink_allowed(u8 *arg0)
{
  s32 temp_v0;
  u8 new_var;
  if ((*((u8 *) (((u8 *) arg0) + 0x1CA))) == 0)
  {
    goto dummy_label_268708;
    dummy_label_268708:
    ;

    ;
    goto block_9;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x70))) == (*((u8 *) (((u8 *) arg0) + 0x6F))))
  {
    return 1;
  }
  temp_v0 = obj_current_part_model(arg0);
  new_var = *((u8 *) (((u8 *) arg0) + 0x6F));
  if (temp_v0 == 0)
  {
    if (new_var == 0x15)
    {
      return 1;
    }
    goto block_9;
  }
  if (temp_v0 == 0x52)
  {
    return 1;
  }
  block_9:
  return 0;

}

// P45: per-record animation / interaction timer step (after the state handler). +0x72 counts down by D_800BE9E4
// (0xFFFE = frozen: return; 0xFFFF = forever); when face_blink_allowed says so, face_eye_blink_update; once +0x72 is 0 and
// +0x70 != +0x6F, face_anim_reset_default. Records of type +5 == 2 are skipped.
/* was func_1507EB1C */
void face_anim_timer_step(u8 *arg0) {
    s32 t;
    u16 v;

    if (arg0[5] == 2) {
        return;
    }
    v = *(u16 *)(arg0 + 0x72);
    if (v != 0) {
        if (v == 0xFFFE) {
            return;
        }
        if (v != 0xFFFF) {
            t = D_800BE9E4;
            if (t < (s32)v) {
                *(u16 *)(arg0 + 0x72) = v - t;
            } else {
                *(u16 *)(arg0 + 0x72) = 0;
            }
        }
    }
    if (face_blink_allowed(arg0) != 0) {
        face_eye_blink_update(arg0);
    }
    if (*(u16 *)(arg0 + 0x72) == 0 && arg0[0x70] != arg0[0x6F]) {
        face_anim_reset_default(arg0);
    }
}
void attachment_remove_by_slot(s32 arg0, s32 arg1);
void face_anim_apply(struct127 *, s32);

/* P67: start animation `anim` (obj +0x6F) with priority `prio` (+0x71) for `time` frames (+0x72, 0xFFFF = until
 * replaced). Priority 3 always wins; otherwise a running timed animation of equal or higher priority is kept unless
 * it is the default one (+0x70) or `anim` itself. Animations past the object's table (face_anim_count) are ignored.
 * The first frame's sound of the new animation is played (attachment_remove_by_slot). `void` under NM: callers ignore the
 * result and the asm leaves v0 undefined on the early returns. */
/* was func_1507E7E4 */
void face_anim_start(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4) {
    u8 *entry;
    u8 *sounds;

    if (obj->unk6F == anim && obj->unk71 == prio && obj->unk72 == time) {
        return;
    }
    if (prio != 3 && obj->unk70 != obj->unk6F && anim != obj->unk6F && obj->unk72 != 0 && obj->unk71 >= prio) {
        return;
    }
    if (!((s32)anim < (s32)face_anim_count((s32)obj))) {
        return;
    }
    entry = (u8 *)face_anim_entry_get((s32)obj, obj->unk6F);
    if (entry[4] != 0) {
        sounds = (u8 *)face_anim_body_table((s32)obj, NULL);
        if (sounds != NULL) {
            attachment_remove_by_slot((s32)obj, sounds[entry[4] - 1]);
        }
    }
    obj->unk6F = anim;
    obj->unk72 = time;
    obj->unk71 = prio;
    face_anim_apply(obj, arg4);
}
/* was func_1507ECE8 */
s32 face_anim_entry_get(s32 arg0, s32 arg1) {
    s32 *p;
    s32 v;
    p = (s32 *)D_800D1C90[obj_current_part_model(arg0)];
    if (p != NULL) {
        p -= 2;
        v = *p;
        if (v != 0) {
            return (arg1 * 10) + v;
        }
    }
    return 0;
}

/* was func_1507ED48 */
u32 face_anim_count(s32 arg0)
{
  s32 *p;
  u32 r;
  s32 idx;
  idx = *((u8 *) (arg0 + 4));
  if (idx != 0x96)
  {
    idx = obj_current_part_model(arg0);
    arg0 = idx;
  }
  else
  {
    arg0 = idx;
  }
  if (arg0 == 0xFF)
  {
    return 0;
  }
  p = (s32 *) D_800D1C90[arg0];
  r = 0;
  if (p != 0)
  {
    p -= 2; return (u32)p[1] / 10U;
  }
  return r;
}

/* was func_1507EDC8 */
void face_anim_stub(s32 arg0, s32 arg1) {
}

/* was func_1507EDD8 */
s32 *face_anim_body_table(s32 arg0, s32 *arg1) {
    if (obj_current_part_model(arg0) == 0) {
        if (arg1 != NULL) {
            *arg1 = 5;
        }
        return &D_8009DCE0;
    }
    if (arg1 != NULL) {
        *arg1 = 0;
    }
    return NULL;
}

extern f32 D_8009BC70;
/* was func_1507EE24 */
void face_anim_play_body(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    if (arg1 != 0) {
        temp_v0 = face_anim_body_table(arg0, 0);
        if (temp_v0 != 0) {
            obj_setup_run((struct127 *) arg0, (s32) (*(u8 *)(arg1 + temp_v0 - 1)), (f32) arg2 * D_8009BC70, 0);
        }
    }
}

void face_anim_start(struct127 *, u8, u8, u16, s32);
void face_anim_reset_default(arg0)
u8 *arg0;
{
    face_anim_start(arg0, arg0[0x70], 3, 0xFFFF, 0xA);
    arg0[0x71] = 0;
    *(s16 *)(arg0 + 0x72) = 0;
    if (arg0[0x6C] >= 0xA) {
        arg0[0x6C] = 0;
        arg0[0x6A] = 0;
    }
    if (arg0[0x6D] >= 0xA) {
        arg0[0x6D] = 0;
        arg0[0x6B] = 0;
    }
}

/* was func_1507EF0C */
void face_clear_default_anim(struct127 *arg0) {
    face_set_default_anim(arg0, 0);
}

/* was func_1507EB4C */
void face_set_default_anim(struct127 *arg0, s32 arg1) {
    if (arg1 != arg0->unk70) {
        arg0->unk70 = arg1;
        face_anim_reset_default(arg0, arg1);
    }
}
