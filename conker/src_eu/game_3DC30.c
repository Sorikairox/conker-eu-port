#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15010780 */
void level_obj_init_vertex_lights(void) {
    vtx_anim_light_create(1, 255,    0, 108, 0, 0.0f, 15000, 80.0f, 77, 15, 127, 127, 127, 127, 127, 127);
    vtx_anim_light_create(0, 255, 6628, 108, 0, 0.0f, 15000, 80.0f, 77, 15, 127, 127, 127, 127, 127, 127);
}

s32 memcpy(s32, s16 *, s32);
extern s32 *g_level_point_hit_cb; /* was D_800E0D64 */
s32 trigger_zones_check(s32, s32, s32); // hit callback (C since P196; was declared as data)

/* was func_15010880 */
void level_obj_init_d34b8_effect(void) {
    struct {
        s16 u54;
        u8 pad56[0x2];
        u8 * u58;
        u8 * u5C;
    } sp;
    struct260 *temp_v0;

    vtx_anim_light_create(0x10U, 0xE9U, -0x1B5, 0x463, -0xCBF, 90.0f, 0x3A98U, 36.0f, 0x4D, 0xF, 0x7FU, 0x7FU, 0x7FU, 0x7FU, 0x7FU, 0x7FU);
    g_level_point_hit_cb = (s32 *) trigger_zones_check;
    sp.u54 = 0;
    sp.u58 = D_800D34B8 + 0xEA0;
    sp.u5C = D_800D34B8 + 0xED4;
    temp_v0 = effect_node_create(0x12C, -1, 0x5E, -1, 0U, 0U, (struct37 *)0xC, 0xFFU, 1);
    if (temp_v0 != NULL) {
        memcpy(((struct260 *)((u8 *)temp_v0 + 0x28)), &sp.u54, 0xC);
    }
    if (g_save_progress_bits->unk12 & 0x40) {
        effect_node_create(5, 9, -1, -1, 1U, 0U, NULL, 0xFFU, 1);
    }
}
// NON-MATCHING: ops in wrong order
// void level_obj_init_d34b8_effect(void) {
//     struct177 tmp;
//     struct37 *temp_v0;

//     vtx_anim_light_create(0x10, 0xE9, -437, 0x463, -0xCBF, 90.0f, 15000, 36.0f, 0x4D, 15, 127, 127, 127, 127, 127, 127);
//     D_800E0934 = func_150DE32C;
    
//     tmp.unk0 = 0;
//     tmp.unk4 = *((s32*) &D_800D3098) + 0xEA0;
//     tmp.unk8 = *((s32*) &D_800D3098) + 0xED4;

//     temp_v0 = effect_node_create(300, -1, 94, -1, 0, 0, 12, 255, 1);
//     if (temp_v0 != NULL) {
//         memcpy(&temp_v0->unk28, &tmp, 12); // memcpy
//     }
//     if ((g_save_progress_bits->unk12 & 0x40) != 0) {
//         effect_node_create(5, 9, -1, -1, 1, 0, 0, 255, 1);
//     }
// }

/* was func_150109D0 */
void level_obj_init_rope(void) {
    struct179 tmp;

    tmp.unk20 = 0;  
    //g_level_rope_def listed as (struct180*), but used as (struct180) here;
    tmp.unk4 = *((struct180*) &g_level_rope_def); 

    tmp.unk0 = 1;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10); 
    rope_create(&tmp, 0);
    storm_controller_spawn();
}
