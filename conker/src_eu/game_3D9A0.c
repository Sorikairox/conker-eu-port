#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// ???
u8 *world_record_find(s32);
extern s32 g_level_part_fades; /* was D_800D9D70 */

/* was func_150104F0 */
void level_obj_init_d9d70(void) {
    (*(s8 *)((u8 *)(&g_level_part_fades) + 1)) = 0;
    (*(s8 *)((u8 *)(&g_level_part_fades) + 0)) = 0;
    (*(s8 *)((u8 *)(&g_level_part_fades) + 2)) = 0;
    (*(f32 *)((u8 *)(world_record_find(0xF6)) + 0x7C)) = 2.0f;
    g_water_effect_started = 0;
}
/* was func_15010538 */
void obj_spawn_effect_80(struct127 *arg0) {
    struct175 tmp;
    struct37 *temp_v0;

    light_create_obj_follow(arg0, 2, 2, 300, 30, 100, 200, 255, 255, 1);
// FAKEMATCH but works...
dummy_label_927029:
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unique_id;
    tmp.unk6 = 0;
    tmp.unk8 = 0;
    tmp.unkA = 0;

    temp_v0 = effect_node_create(300, -1, 80, -1, 0, 61, 12, 255, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 12); // memcpy
    }
}

extern u8 D_800D9D40;
extern u8 g_level_flag_9d41; /* was D_800D9D41 */
extern u8 g_level_flag_9d48; /* was D_800D9D48 */
extern u8 g_level_flag_9d49; /* was D_800D9D49 */
extern u8 g_level_bytes_9d4a[]; /* was D_800D9D4A */
extern u8 g_level_flag_9d58; /* was D_800D9D58 */
extern u8 g_level_flag_9d59; /* was D_800D9D59 */
extern u8 g_level_bytes_9d5a[]; /* was D_800D9D5A */
/* was func_15010600 */
void level_clear_d9d40_flags(void)
{
  s32 i;
  g_level_flag_9d41 = 0;
  D_800D9D40 = 0;
  g_level_flag_9d48 = 0;
  g_level_flag_9d58 = 0;
  g_level_flag_9d49 = 0;
  for (i = 0; i < 12; i++)
  {
    g_level_flag_9d59 = 0; // fakematch: store inside the loop schedules after the pointer setup
    g_level_bytes_9d4a[i] = 0;
    g_level_bytes_9d5a[i] = 0;
  }

}
// NON-MATCHING: addresses are wrong :(
// void level_clear_d9d40_flags(void) {
//     s32 i;
//
//     for (i = 0; i < 11; i++) {
//         D_800D9930[i] = D_800D9920[i] = 0;
//     }
// }
