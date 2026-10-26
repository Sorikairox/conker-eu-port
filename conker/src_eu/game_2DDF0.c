#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_level_colour_set_indices[]; /* was D_800A30A0 */

// loops...
extern s32 g_level_colour_table_a; /* was D_800A30B8 */
extern s32 g_level_colour_table_b; /* was D_800A30BC */
extern s32 g_level_colour_table_c; /* was D_800A30D4 */
extern s32 D_800DA290;
extern s32 D_800DA2A8;
extern s32 D_800DA2B8;
extern s32 D_800DA2C8;
extern s32 D_800DA2D4;
extern s32 g_level_colour_dst_inner_end; /* was D_800DA2D7 */
extern s32 D_800DA2D8;
extern s32 g_level_colour_dst_end; /* was D_800DA2E4 */

/* was func_15000940 */
void level_init_color_tables(s32 arg0) {
    s32 *var_a0;
    s32 *var_a1;
    s32 *var_a2;
    s32 *var_s0;
    s32 *var_s2;
    s32 *var_s4;
    s32 *var_s5;
    s32 *var_t3;
    s32 *var_t4;
    s32 *var_v0;
    s32 *var_v1;
    u8 *var_s1;
    u8 *var_s3;
    u8 *var_t5;
    u8 temp_t6;
    u8 temp_t7;
    u8 temp_t9;
    u8 *temp_t4;

    temp_t4 = (D_800B0DF0->unk29 * 3) + ((u8 *)&g_level_colour_set_indices);
    var_v0 = &D_800DA2D8;
    var_a2 = &D_800DA2C8;
    var_a1 = &D_800DA2B8;
    var_a0 = &D_800DA2A8;
    var_v1 = &D_800DA290;
    do {
        var_s2 = &D_800DA2D4;
        var_t3 = var_v1;
        var_t4 = var_a0;
        var_t5 = ((s32 *)((u8 *)&g_level_colour_table_a + ((*(u8 *)((u8 *)temp_t4 + 0)) * 3)));
        var_s0 = var_a1;
        var_s1 = ((s32 *)((u8 *)&g_level_colour_table_b + ((*(u8 *)((u8 *)temp_t4 + 1)) * 3)));
        var_s3 = ((s32 *)((u8 *)&g_level_colour_table_c + ((*(u8 *)((u8 *)temp_t4 + 2)) * 3)));
        var_s4 = var_a2;
        var_s5 = var_v0;
loop_2:
        temp_t9 = *var_s3;
        temp_t6 = *var_t5;
        temp_t7 = *var_s1;
        var_s2 = (s32 *)((u8 *)var_s2 + (1));
        var_t3 = (s32 *)((u8 *)var_t3 + (2));
        var_t4 = (s32 *)((u8 *)var_t4 + (1));
        var_t5 += 1;
        var_s0 = (s32 *)((u8 *)var_s0 + (1));
        var_s1 += 1;
        var_s3 += 1;
        var_s4 = (s32 *)((u8 *)var_s4 + (1));
        var_s5 = (s32 *)((u8 *)var_s5 + (1));
        (*(s16 *)((u8 *)var_t3 + -2)) = 0;
        (*(s8 *)((u8 *)var_s5 + -1)) = 0;
        (*(u8 *)((u8 *)var_s2 + -1)) = temp_t9;
        (*(u8 *)((u8 *)var_s4 + -1)) = temp_t9;
        (*(u8 *)((u8 *)var_t4 + -1)) = temp_t6;
        (*(u8 *)((u8 *)var_s0 + -1)) = temp_t7;
        if (var_s2 != &g_level_colour_dst_inner_end) {
            goto loop_2;
        }
        var_v0 = (s32 *)((u8 *)var_v0 + (3));
        var_v1 = (s32 *)((u8 *)var_v1 + (6));
        var_a0 = (s32 *)((u8 *)var_a0 + (3));
        var_a1 = (s32 *)((u8 *)var_a1 + (3));
        var_a2 = (s32 *)((u8 *)var_a2 + (3));
    } while (var_v0 != &g_level_colour_dst_end);
}