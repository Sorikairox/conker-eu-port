#include <ultra64.h>
#include "functions.h"
#include "variables.h"


f32 anim_events_run(struct127 *arg0, f32 arg1, s32 arg2);
extern u8 g_slowmo_divisor; /* was D_800BEE2C */
extern u8 D_800C3A82[];
extern f32 D_8009B860;

/* Advances an animation (anim: +4 flags (0x8000 = hold the last frame), +8 frame, +0x10 speed, +0x18 end,
 * +0x20 loop start, +0x28 current animation, +0 end-of-animation callback, +0x3A / +0x3C a countdown) by one
 * frame. With a record, the step is scaled by the frame time D_800BE9A4 (x 1.2, at most 2 frames), the record
 * becomes the current one (g_cur_obj_index / g_cur_obj), its flags +0xF4 (2 / 4 / 8) change the looping, and
 * anim_events_run (the record's frame hook) may replace the frame. The final frame is copied to rec->unkB4.
 * The callback's arguments are not set up by the asm (it sees anim / player, or scratch after the hook): it is
 * called with anim here (UNVERIFIED). */
/* was func_1507C170 */
void anim_advance_frame(struct197 *anim, f32 step, struct127 *rec, s32 player) {
    void (*cb)(struct197 *);
    f32 frame, end, f;
    s32 hold;
    s32 resync = 0;
    s32 prev;
    u16 turn;

    if (*(s32 *)((u8 *)anim + 0x28) == 0) {
        return;
    }
    if (rec != NULL) {
        if (D_800C35EA == 0) {
            step = ((D_800BE9A4 < 2.0f) ? D_800BE9A4 * step : step + step) * D_8009B860; /* 1.2 */
        } else {
            step = D_800BE9A4;
        }
    }
    if (g_slowmo_divisor != 0) {
        step = 0.0f;
    }
    frame = anim->unk10 * step;
    if (anim->unk18 < frame) {
        frame = anim->unk18 + anim->unk8;
    } else {
        frame = frame + anim->unk8;
    }
    hold = anim->unk4 & 0x8000;
    if (rec != NULL) {
        rec->unk1FC &= ~4;
        g_cur_obj_index = rec - g_objects;
        hold |= rec->unkF4 & 0xE;
        g_cur_obj = rec;
    }
    if (rec != NULL && ((&D_800C35EA)[player] != 1 || D_800C3A82[player] != 0)) {
        f = anim_events_run(g_cur_obj, frame, 0);
        if (f != 0.0f) {
            frame = f;
        }
    }
    if (anim->unk10 >= 0.0f) {
        end = anim->unk18 - 1.0f;
        cb = *(void (**)(struct197 *))anim;
        if (end <= frame && anim->unk8 < end && cb != NULL) {
            prev = *(s32 *)((u8 *)anim + 0x28);
            if (rec != NULL && (rec->unkF4 & 8)) {
                rec->unk10C = 0;
                rec->unk1C4 = 0;
                anim->unk10 = 0.0f;
            }
            if (D_800C35EA == 0) {
                cb(anim);
                if (rec != NULL && rec->interaction_state == 0) {
                    return;
                }
            }
            if (prev != *(s32 *)((u8 *)anim + 0x28)) {
                /* the callback started another animation */
                frame = anim->unk8;
                resync = 1;
            }
        }
        if (rec != NULL && rec->unk1FD != 0 && anim->unk18 - 1.0f <= frame) {
            /* end of a turning animation: apply the turn (unk1FD x 256) to the facing angles */
            turn = rec->unk76 + (rec->unk1FD << 8);
            rec->unk76 = turn;
            rec->unk7A = turn;
            rec->unk78 = turn;
            anim->unk8 = *(f32 *)((u8 *)anim + 0x20);
            if (rec->unkF4 & 4) {
                rec->unk21C = 0;
            }
        } else if (hold == 0 && anim->unk18 <= frame) {
            /* loop */
            resync = 1;
            anim->unk8 = (frame - anim->unk18) + *(f32 *)((u8 *)anim + 0x20);
            if (rec != NULL) {
                rec->unk1FC |= 4;
            }
        } else if (hold != 0 && (end = anim->unk18 - 1.0f) <= frame) {
            /* hold the last frame */
            if ((rec != NULL && (rec->unkF4 & 0xA)) || (anim->unk4 & 0x8000)) {
                anim->unk8 = end;
            } else if (anim->unk8 < end) {
                anim->unk8 = end;
                if (rec != NULL && (rec->unkF4 & 4)) {
                    rec->unk21C = 0;
                }
            } else {
                anim->unk8 = *(f32 *)((u8 *)anim + 0x20);
                if (rec != NULL) {
                    rec->unk138 = 0;
                    rec->unk1FC |= 2;
                }
            }
            if (rec != NULL && (rec->unkF4 & 8)) {
                rec->unk10C = 0;
                rec->unk1C4 = 0;
                anim->unk10 = 0.0f;
            }
            if (anim->unk8 < 0.0f) {
                anim->unk8 = 0.0f;
            }
        } else {
            anim->unk8 = frame;
        }
    } else if (frame < *(f32 *)((u8 *)anim + 0x20)) {
        /* playing backwards past the loop start */
        anim->unk8 = (frame - *(f32 *)((u8 *)anim + 0x20)) + anim->unk18;
    } else {
        anim->unk8 = frame;
    }
    if (*(s16 *)((u8 *)anim + 0x3C) > 0) {
        *(s16 *)((u8 *)anim + 0x3C) -= *(s16 *)((u8 *)anim + 0x3A) * D_800BE9E4;
    }
    if (rec != NULL) {
        if (resync) {
            anim_events_run(g_cur_obj, anim->unk8, 0);
        }
        rec->unkB4 = anim->unk8;
    }
}
s32 cutscene_obj_takes_part(struct127 *);
void anim_advance_frame(struct197 *, f32, struct127 *, s32); /* P59: void in the NM definition */
extern u8 D_800C3A78;

/* was func_1507C608 */
void obj_anims_advance_all(s32 arg0)
{
  struct127 *var_s0;
  struct197 *temp_a0;
  s32 *new_var;
  var_s0 = g_objects; ; do { // fakematch: permuter empty statement before the loop
    if ((((var_s0->interaction_state != 0) && (!(var_s0->unk25C & 0x200))) && ((arg0 == 0) || (var_s0->unk5 == 4))) && (((D_800C3638 == 0) || (D_800C3A78 != 0)) || (cutscene_obj_takes_part(var_s0) != 0)))
    {
      temp_a0 = var_s0->unk2D0;
      if ((temp_a0 != 0) && (var_s0->unk2FA != 0))
      {
        anim_advance_frame(temp_a0, var_s0->unk48, var_s0, arg0);
        if (&g_obj_scratch_rec) // fakematch: permuter empty if
        {
        }
      }
    }
    if (1) // fakematch: permuter empty if
    {
    }
    var_s0++;
  }
  while (var_s0 != ((struct127 *) (&g_obj_scratch_rec)));
}

/* was func_1507C700 */
void obj_sync_anim_frame(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x2D0));
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x2D0));
    if ((temp_v0 != NULL) && (temp_v1 != NULL)) {
        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x18)) - 1.0f;
        if (temp_f0 <= (*(f32 *)((u8 *)temp_v0 + 8))) {
            (*(f32 *)((u8 *)temp_v0 + 8)) = temp_f0;
        }
    }
}
