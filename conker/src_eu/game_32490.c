#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void *allocate_memory(s32, s32, s32, s32);
void heap_free(void *);
extern u8 *g_look_points;      /* look points, 0x14-byte records (LookPoint in game_eu_64770.c); was D_800C6A70 */
extern u32 D_800C6A74;      /* their count */

/*
 * P80: load the level's look points: asset block 3 / 0xC (asset_load_ptr, record type arg0) holds 6 floats per point
 * (x, y, z, reach, +0xC value, animation). Each becomes a 0x14-byte LookPoint in g_look_points: s16 x, y, z, usable
 * flag 0, u32 reach squared, s16 +0xC, x window (x + reach, x - reach), s16 animation. Frees the loaded block and
 * returns the number of points.
 */
/* was func_15004FE0 */
s32 level_load_look_points(s32 arg0) {
    f32 *src = NULL;
    u32 count;
    s32 i;
    f32 r;

    count = (u32) asset_load_ptr((s32 *) &src, 3, 0xC, arg0, 3) / 0x18;
    g_look_points = allocate_memory(count * 0x14, 1, 1, 0);
    D_800C6A74 = count;
    for (i = 0; i < (s32) count; i++) {
        *(s16 *) (g_look_points + i * 0x14 + 0x0) = src[i * 6 + 0];
        *(s16 *) (g_look_points + i * 0x14 + 0x2) = src[i * 6 + 1];
        *(s16 *) (g_look_points + i * 0x14 + 0x4) = src[i * 6 + 2];
        *(s16 *) (g_look_points + i * 0x14 + 0x6) = 0;
        r = src[i * 6 + 3];
        *(u32 *) (g_look_points + i * 0x14 + 0x8) = r * r;
        *(s16 *) (g_look_points + i * 0x14 + 0xC) = src[i * 6 + 4];
        *(s16 *) (g_look_points + i * 0x14 + 0xE) = src[i * 6 + 3] + src[i * 6 + 0];
        *(s16 *) (g_look_points + i * 0x14 + 0x10) = src[i * 6 + 0] - src[i * 6 + 3];
        *(s16 *) (g_look_points + i * 0x14 + 0x12) = src[i * 6 + 5];
    }
    if (src != NULL) {
        heap_free(src);
    }
    return i;
}
// NON-MATCHING: miles away
// s32 level_load_look_points(s32 arg0) {
//     struct161 **sp34;
//     u32 temp_lo;
//     s32 i;
//
//     sp34 = 0;
//     temp_lo = asset_load_ptr(&sp34, 3, 12, arg0, 3) / 24U;
//     D_800C6654 = temp_lo;
//     allocate_memory(temp_lo * 20, 1, 1, 0);
//
//     for(i = 0; i < D_800C6654; i++) {
//         D_800C6650[i].unk0 = sp34[i]->unk0;
//         D_800C6650[i].unk2 = sp34[i]->unk4;
//         D_800C6650[i].unk4 =  sp34[i]->unk8;
//         D_800C6650[i].unk6 = 0;
//         D_800C6650[i].unk8 = sp34[i]->unkC * sp34[i]->unkC;
//         D_800C6650[i].unkC = sp34[i]->unk10;
//         D_800C6650[i].unkE = sp34[i]->unkC + sp34[i]->unk0;
//         D_800C6650[i].unk10 = sp34[i]->unk0 - sp34[i]->unkC;
//         D_800C6650[i].unk12 = sp34[i]->unk14;
//     }
//     if (sp34 != NULL) {
//         heap_free(sp34);
//     }
//     return i;
// }
