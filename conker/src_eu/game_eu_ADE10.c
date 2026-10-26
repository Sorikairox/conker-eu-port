#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15080600 */
void lipsync_reset(void)
{
  g_lipsync_unk_1d50 = (g_lipsync_mode = (g_lipsync_shape_idx = 0));
}

// text_queue_tempo_events: drains the text queue (text_queue_read into a 0x100-byte buffer); every 'L' record carries a
// 28-bit big-endian 7-bit-packed value at bytes 4..7, divided by 441 (16 when that gives 0), which goes with the record's
// byte 3 minus one to lipsync_apply_event for the current player's object g_objects[g_lipsync_obj_idx].
void lipsync_apply_event(u8 *arg0, s32 arg1, s32 arg2);
/* was func_15080628 */
void lipsync_poll_text_queue(void) {
    u8 buf[0x100];
    s32 value;

    while (text_queue_read((s32)buf, 0x100) != 0) {
        if (buf[0] == 'L') {
            value = buf[4] & 0x7F;
            value = (buf[5] & 0x7F) | (value << 7);
            value = (buf[6] & 0x7F) | (value << 7);
            value = (buf[7] & 0x7F) | (value << 7);
            value /= 441;
            if (value == 0) {
                value = 16;
            }
            lipsync_apply_event((u8 *)&g_objects[g_lipsync_obj_idx], buf[3] - 1, value);
        }
    }
}

int game_gu_random(void);
extern s32 g_lipsync_voice_level; /* was D_80042B90 */
extern s32 g_lipsync_mouth_shapes; /* was D_8009C0E0 */

/* was func_15080748 */
void lipsync_update_mouth(u8 *arg0) {
    s32 sp1C;
    s32 var_v1;

    if ((g_lipsync_mode != 0) && (arg0 != NULL)) {
        if (g_lipsync_mode == 1) {
            if (g_lipsync_voice_level < 0x3E8) {
                (*(s8 *)((u8 *)arg0 + 0x1FF)) = 0;
            } else {
                (*(s8 *)((u8 *)arg0 + 0x1FF)) = 1;
            }
        } else if (g_lipsync_voice_level >= 0x3E9) {
            var_v1 = g_lipsync_shape_idx + 1;
            if (((*(u8 *)((u8 *)arg0 + 0x135)) - g_frame_ticks) < 0) {
                if (var_v1 >= 5) {
                    var_v1 = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x134)) = (s8) *(s32 *)((u8 *)&g_lipsync_mouth_shapes + (var_v1 * 4));
                sp1C = var_v1;
                (*(u8 *)((u8 *)arg0 + 0x135)) = (u8) ((game_gu_random() % 7) + 4);
                g_lipsync_shape_idx = var_v1;
            }
        }
        g_lipsync_voice_level = 0;
    }
}
void face_anim_set(u8 *arg0, s32 anim, s32 variant);
s32 face_anim_count();

/* was func_15080830 */
void lipsync_apply_event(u8 *arg0, s32 arg1, s32 arg2)
{
  int new_var;
  s32 temp_v0;
  if (arg0 != 0)
  {
    arg2 = arg2;
    if (face_anim_count(arg0) > 0)
    {
      new_var = 0xFFFE;
      if (arg1 == 0)
      {
        g_lipsync_mode = 0;
        *((s16 *) (((u8 *) arg0) + 0x72)) = 0x14;
        face_anim_set(arg0, 0, 0xA);
        return;
      }
      *((s16 *) (((u8 *) arg0) + 0x72)) = new_var;
      if (arg1 == 1)
      {
        g_lipsync_mode = 2;
        return;
      }
      if (arg2 != 0)
      {
        if (arg2 >= 0x15)
        {
          arg2 = 0x14;
        }
        if (arg2 <= 0)
        {
          arg2 = 1;
        }
      }
      face_anim_set(arg0, arg1, arg2);
      return;
    }
    temp_v0 = arg1 != 0;
    g_lipsync_mode = temp_v0;
    if (temp_v0 == 0)
    {
      *((s8 *) (((u8 *) arg0) + 0x1FF)) = 0;
    }
  }
}
