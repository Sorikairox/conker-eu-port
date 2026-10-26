#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1508F120 */
s32 link_group_find_partner(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_t0;
    u16 temp_a1;
    u16 temp_t1;
    u32 var_a2;
    u32 var_v0;
    u32 var_v0_2;
    u8 *temp_t2;
    u8 *var_a0;
    u8 *var_t3;

    var_v0 = 0;
    if (g_link_group_count != 0) {
        var_t0 = g_link_groups;
loop_2:
        temp_t1 = (*(u16 *)((u8 *)var_t0 + 2));
        var_a2 = 0;
        if (temp_t1 != 0) {
            temp_t2 = g_link_groups + (var_v0 * 0x18);
            var_t3 = temp_t2;
loop_4:
            if (((((arg0 & 0xFFFF) << 0xC) + (arg1 & 0xFFFF)) & 0xFFFF) == (*(u16 *)((u8 *)var_t3 + 8))) {
                var_v0_2 = 0;
                if (temp_t1 != 0) {
                    var_a0 = temp_t2;
loop_7:
                    temp_a1 = (*(u16 *)((u8 *)var_a0 + 8));
                    if (((arg2 & 0xFFFF) == ((s32) temp_a1 >> 0xC)) && (var_v0_2 != var_a2)) {
                        return temp_a1 & 0xFFF;
                    }
                    var_v0_2 += 1;
                    var_a0 += 2;
                    if (var_v0_2 >= temp_t1) {
                        goto block_11;
                    }
                    goto loop_7;
                }
block_11:
                goto block_14;
            }
            var_a2 += 1;
            var_t3 += 2;
            if (var_a2 >= temp_t1) {
                goto block_13;
            }
            goto loop_4;
        }
block_13:
        var_v0 += 1;
        var_t0 += 0x18;
        if (var_v0 >= (u32) g_link_group_count) {
            goto block_14;
        }
        goto loop_2;
    }
block_14:
    return -1;
}
/* was func_1508F21C */
void link_group_clear(u32 arg0) {
    if (arg0 < g_link_group_count) {
        *(s16 *)(g_link_groups + arg0 * 0x18 + 2) = 0;
        *(s32 *)(g_link_groups + arg0 * 0x18 + 4) = 0;
        *(s16 *)(g_link_groups + arg0 * 0x18) = 0;
    }
}

void look_point_remove(s32);
void world_record_remove(u32);

/* was func_1508F26C */
void link_group_remove_members(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s1;
    s32 var_s3;
    u16 temp_v0;
    u16 var_a0;
    u32 var_s0;
    u32 var_s0_2;
    u32 var_s2;
    u8 *var_v0;

    var_s2 = 0;
    if (g_link_group_count != 0) {
        temp_a2 = g_link_groups;
        var_s3 = 0;
        var_a1 = temp_a2;
loop_2:
        var_a0 = (*(u16 *)((u8 *)var_a1 + 2));
        var_s0 = 0;
        if (var_a0 != 0) {
            var_v0 = temp_a2 + (var_s2 * 0x18);
loop_4:
            var_s0 += 1;
            if (((((arg0 & 0xFFFF) << 0xC) + (arg1 & 0xFFFF)) & 0xFFFF) == (*(u16 *)((u8 *)var_v0 + 8))) {
                var_s0_2 = 0;
                if (var_a0 != 0) {
                    var_s1 = 0;
                    do {
                        temp_v0 = (*(u16 *)((u8 *)((temp_a2 + (var_s2 * 0x18) + var_s1)) + 8));
                        temp_v1 = (s32) temp_v0 >> 0xC;
                        temp_a1 = temp_v0 & 0xFFF;
                        switch (temp_v1) {          /* irregular */
                        case 2:
                            world_record_remove(temp_a1);
                            var_a0 = (*(u16 *)((u8 *)((g_link_groups + var_s3)) + 2));
                            break;
                        case 3:
                            look_point_remove(temp_a1);
                            var_a0 = (*(u16 *)((u8 *)((g_link_groups + var_s3)) + 2));
                            break;
                        }
                        var_s0_2 += 1;
                        var_s1 += 2;
                    } while (var_s0_2 < var_a0);
                }
                link_group_clear(var_s2);
                return;
            }
            var_v0 += 2;
            if (var_s0 >= var_a0) {
                goto block_15;
            }
            goto loop_4;
        }
block_15:
        var_s2 += 1;
        var_s3 += 0x18;
        var_a1 += 0x18;
        if (var_s2 >= (u32) g_link_group_count) {

        } else {
            goto loop_2;
        }
    }
}