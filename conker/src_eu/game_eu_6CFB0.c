#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 allocate_memory(s32, s32, s32, s32);
// the definition is void; one signature for wasm
void heap_free(s32);
// P51: both definitions are void (NM C); one signature for wasm
void anim_copy_keyframes(u8 *, s32, s32);
void anim_advance_frame(u8 *, f32, s32, s32); /* P59: void in the NM definition */
void anim_eval_joint_matrices(s32 *, s32, u8 *, s32, s32, s16 *, s32, s32);
s32 mtx_f_to_l_batch(s32, u8);

/* was func_1503F7A0 */
void animmodel_update_matrices(u8 *arg0)
{
  s32 sp44;
  s16 sp40[2];
  int new_var;
  s32 sp38;
  s32 temp_v0;
  u8 *temp_v0_2;
  sp44 = 0;
  if ((*((s32 *) (((u8 *) ((u8 *) (((u32) arg0) + (g_dl_buf_index * 4)))) + 0x3E0))) != 0)
  {
    temp_v0 = allocate_memory(0x320, 1, 2, 2);
    sp44 = temp_v0;
    anim_copy_keyframes(arg0, 0, temp_v0);
    sp40[0] = 0x1000;
    if (arg0) // fakematch: empty if from the permuter
    {
    }
    temp_v0_2 = (u8 *) (((u32) arg0) + (g_dl_buf_index * 4));
    temp_v0 = *((s32 *) (((u8 *) temp_v0_2) + 0x3E0));
    sp38 = *((s32 *) (((u8 *) temp_v0_2) + 0x3E8));
    anim_eval_joint_matrices(&sp38, temp_v0, arg0, *((s32 *) (((u8 *) arg0) + 0x3F0)), (s32) (*((u8 *) (((u8 *) arg0) + 0x3F4))), sp40, 0, 0);
    mtx_f_to_l_batch(*((s32 *) (((u8 *) ((u8 *) (((u32) arg0) + (g_dl_buf_index * 4)))) + 0x3E8)), *((u8 *) (((u8 *) arg0) + 0x3F4)));
    *((s8 *) (((u8 *) arg0) + 0x3F6)) = 1;
  }
  anim_advance_frame(arg0, g_frame_step_f, 0, 0);
  if (sp44 != 0)
  {
    heap_free(sp44);
  }
}

s32 anim_start_entry(struct127 *, s32, u8 *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
/* was func_1503F8A8 */
void animmodel_start_anim(u8 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    anim_start_entry(0, 0, arg0, 0, arg1, arg2, (s32) (*(u8 *)((u8 *)arg0 + 0x3F5)), arg3, arg4, 0.0f, 0.0f, arg5);
}

s32 model_asset9_load_refcounted(s32, s32, s32, s32, s32, s32, s32 *);

/* was func_1503F91C */
s32 animmodel_create(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 *arg6) {
    struct {
        s32 u3C;
    } sp;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_v0;

    temp_v0 = allocate_memory(0x3F8, 1, 2, 2);
    *arg6 = temp_v0;
    if (temp_v0 == 0) {
        return 1;
    }
    bzero((u8 *) *arg6, 0x40);
    (*(s8 *)((u8 *)(*arg6) + 0x215)) = 1;
    (*(s8 *)((u8 *)(*arg6) + 0x45)) = 1;
    model_asset9_load_refcounted(arg0, arg2, arg3, arg4, arg5, *arg6 + 0x3F0, &sp.u3C);
    (*(s8 *)((u8 *)(*arg6) + 0x3F4)) = (s8) sp.u3C;
    (*(s8 *)((u8 *)(*arg6) + 0x3F5)) = (s8) arg1;
    (*(s8 *)((u8 *)(*arg6) + 0x3F6)) = 0;
    (*(s32 *)((u8 *)(*arg6) + 0x3E8)) = allocate_memory(sp.u3C << 6, 1, 2, 2);
    (*(s32 *)((u8 *)(*arg6) + 0x3EC)) = allocate_memory(sp.u3C << 6, 1, 2, 2);
    temp_s0 = *arg6;
    temp_a0 = (*(s32 *)((u8 *)temp_s0 + 0x3E8));
    if ((temp_a0 == 0) || ((*(s32 *)((u8 *)temp_s0 + 0x3EC)) == 0)) {
        if (temp_a0 == 0) {
            heap_free(temp_a0);
        }
        temp_a0_2 = (*(s32 *)((u8 *)((u8 *) *arg6) + 0x3EC));
        if (temp_a0_2 == 0) {
            heap_free(temp_a0_2);
        }
        heap_free(*arg6);
        return 1;
    }
    animmodel_start_anim((u8 *) temp_s0, 1, 0, 1.0f, 0.0f, 0);
    return 0;
}
/* was func_1503FAA8 */
void animmodel_free(u8 *arg0) {
    heap_set_block_tag(*(s32 **)(arg0 + 0x3E8), 4);
    heap_set_block_tag(*(s32 **)(arg0 + 0x3EC), 4);
    heap_free(arg0);
}
