#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150D2620 */
void sky_flash_spawn(s16 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6) {
    struct {
        u8 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        u8 unk14;
        u8 unk15;
    } tmp;
    struct260 *temp_v0;

    D_800D9D20++;
    tmp.unk8 = arg1;
    tmp.unkC = arg2;
    tmp.unk10 = arg1 + arg2;
    tmp.unk0 = 0;
    tmp.unk4 = 0.0f;
    tmp.unk14 = arg3;
    tmp.unk15 = arg4;
    temp_v0 = effect_node_create(arg0, -1, 0x2F, 2, 1, 0x26, 0x18, arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
}

/* was func_150D26DC */
void sky_flash_update(u8 *arg0)
{
  u8 *temp_v0;
  u8 *temp_v0_2;
  temp_v0 = (temp_v0_2 = arg0 + 0x28); // fakematch: two pointers to the same address (permuter)
  *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x2C))) + D_800BE9A4);
  if ((*((f32 *) (((u8 *) arg0) + 0x38))) < (*((f32 *) (((u8 *) arg0) + 0x2C))))
  {
    do
    {
      *((f32 *) (((u8 *) temp_v0) + 4)) = (f32) ((*((f32 *) (((u8 *) temp_v0) + 4))) - (*((f32 *) (((u8 *) temp_v0) + 0x10))));
    }
    while ((*((f32 *) (((u8 *) temp_v0) + 0x10))) < (*((f32 *) (((u8 *) temp_v0) + 4))));
  }
  if ((*((f32 *) (((u8 *) temp_v0_2) + 4))) <= (*((f32 *) (((u8 *) temp_v0_2) + 8))))
  {
    *((s8 *) (((u8 *) temp_v0_2) + 0)) = 1;
    light_set_level_colour(0xFF, 0xFF, 0xFF, 0xFFU);
    return;
  }
  *((s8 *) (((u8 *) temp_v0_2) + 0)) = 0;
}

/* was func_150D278C */
void sky_flash_retire(struct260 *arg0) {
    sky_flash_uncount((s32)arg0);
    effect_node_retire(arg0);
}

/* was func_150D27B8 */
void sky_flash_delete(struct260 *arg0) {
    sky_flash_uncount((s32)arg0);
    effect_node_free(arg0);
}

/* was func_150D27E4 */
void sky_flash_uncount(s32 arg0) {
    D_800D9D20--;
}

Gfx *screen_view_fill_colour(Gfx *, s32, s32, s32, s32, s32);
/* was func_150D2804 */
u8 *sky_flash_draw(u8 *arg0, u8 *arg1, s16 arg2) {
    if (arg1[0x28] == 1) {
        arg0 = screen_view_fill_colour(arg0, arg1[0x3C], 0xFF, 0xFF, 0xFF, arg2);
    } else {
        arg0 = screen_view_fill_colour(arg0, arg1[0x3D], 0, 0, 0, arg2);
    }
    return arg0;
}

/* was func_150D2884 */
void sky_flash_spawner_update(u8 *arg0)
{
  u8 *temp_v1;
  *((s32 *) (arg0 + 0x30)) -= D_800BE9E4;
  if ((*((s32 *) (arg0 + 0x30))) < 0)
  {
    temp_v1 = arg0 + 0x28;
    sky_flash_spawn((s16)((*((s16 *) (((u8 *) temp_v1) + 0xC))) + (random_int() % ((u32) ((*((s16 *) (((u8 *) temp_v1) + 0xE))) + 1)))), *((f32 *) (((u8 *) temp_v1) + 0x10)), *((f32 *) (((u8 *) temp_v1) + 0x14)), *((u8 *) (((u8 *) temp_v1) + 0x18)), (u8) ((s32) (*((u8 *) (((u8 *) temp_v1) + 0x19)))), (u8) ((s32) (*((u8 *) (((u8 *) arg0) + 0xC)))), (s32) (*((u8 *) (((u8 *) arg0) + 1))));
    *((s32 *) (((u8 *) temp_v1) + 8)) = (s32) ((*((s32 *) (((u8 *) temp_v1) + 0))) + (random_int() % ((u32) ((*((s32 *) (((u8 *) temp_v1) + 4))) + 1))));
  }
}
