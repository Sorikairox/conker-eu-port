#include <ultra64.h>

#include "functions.h"
#include "variables.h"
s32 event_dispatch(s32, s32, ...);


/* was func_150AE5B0 */
void camera_update_event_modes(struct108 *arg0) {
    if ((g_save_progress_bits->unk4 & 0x80) == 0) {
        if (event_dispatch(0, 0x2000, 0xBB) != -1) {
            if (camera_push_mode(arg0, arg0->unk2C, 0, arg0->unk134, 8) != 0) {
                arg0->unk84 |= 0x1000000;
                camera_set_followed_obj(arg0, D_800CC335 - 1);
            }
        } else if (camera_pop_mode(arg0, 8) != 0) {
            camera_set_followed_obj(arg0, 0);
        }
    }
    arg0->unk84 &= -0x4001;
    if ((g_save_progress_bits->unk1 & 4) == 0) {
        if (event_dispatch(1, 0x2000, 0x95, event_dispatch(0, 0x2014, 0xB7) | 0x2000) != 0) {
            arg0->unk84 |= 0x1000000;
            if (((arg0->unk2C & 1) != 0) && (camera_push_mode(arg0, arg0->unk2C, 0, arg0->unk134, 0) != 0)) {
                arg0->unk1B4 = 3;
                arg0->unk84 &= -5;
                camera_apply_zoom_level(arg0);
            }
        } else if (camera_pop_mode(arg0, 0) != 0) {
            camera_apply_zoom_level(arg0);
            arg0->unk84 &= 0xFEFFFFFF;
        }
    }
    if (event_dispatch(1, 0x4080, 6, 0x9000) != 0) {
        arg0->unk84 |= 0x10000;
    } else {
        arg0->unk84 &= 0xFFFEFFFF;
    }
}


void mtx_get_translation(void *, s32, void *);
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
s32 node_spawn_sprite(s32 *, s32, s32, s32, s32, s32);
extern s32 g_owner_spark_sprite; /* was D_8008CEB4 */

/* was func_150AE790 */
void owner_child_spark_burst(u8 *arg0) {
    struct {
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s16 uC6;
        s16 uC8;
        s16 uCA;
        s16 uCC;
        s16 uCE;
        s8 uD0;
        s8 uD1;
        s8 uD2;
        s8 uD3;
        s16 uD4;
        s16 uD6;
        s16 uD8;
        s16 uDA;
        s16 uDC;
        s8 uDE;
        s8 uDF;
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s8 uE4;
        s8 uE5;
        s8 uE6;
        u8 padE7[0x1];
        s16 uE8;
        u8 padEA[0x1A];
        s32 u104;
        s32 u108;
        s32 u10C;
        s32 u110;
        s32 u114;
        s32 u118;
        s32 u11C;
        s8 u120;
        s8 u121;
        u8 pad122[0x6];
        f32 u128;
        f32 u12C;
        f32 u130;
        f32 u134;
        f32 u138;
        f32 u13C;
        s8 u140;
        s8 u141;
        s8 u142;
        s8 u143;
        u8 pad144[0x4];
        f32 u148;
        f32 u14C;
        f32 u150;
        s16 u154;
        s16 u156;
        s32 u158;
        u8 pad15C[0x1];
        s8 u15D;
    } sp;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_v1;
    s32 var_s2;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = arg0 + 0x28;
    if ((*(s32 *)((u8 *)arg0 + 0x28)) != 0) {
        temp_v0 = (*(u8 **)((u8 *)temp_s0 + 0));
        if ((*(s32 *)((u8 *)temp_v0 + 0)) != 0) {
            temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0x1D4));
            if ((temp_v1 != 0) && ((*(u8 *)((u8 *)temp_s0 + 4)) == (*(u8 *)((u8 *)temp_v0 + 0x3B)))) {
                mtx_get_translation(temp_v1, (*(u8 *)((u8 *)temp_s0 + 5)), &sp.u148);
                sp.u158 = 1;
                sp.u156 = 1;
                sp.u141 = 0;
                sp.u142 = 0xFF - (((u32) (*(u32 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 0x184)) >> 5) << 6);
                sp.u140 = 8;
                sp.u143 = 0xFF;
                sp.u13C = (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 0x180));
                var_s2 = (random_int() % 9U) + 0xC;
                sp.u104 = 0;
                sp.u108 = 1;
                sp.u10C = 0x160600;
                sp.u110 = 3;
                sp.u114 = 0x10;
                sp.u118 = 0x80;
                sp.u11C = 0x20;
                sp.u120 = 0;
                sp.u121 = 9;
                if (var_s2 != 0) {
                    do {
                        temp_s0_2 = random_int() & 0xFF;
                        temp_s1 = (random_int() % 51U) & 0xFF;
                        temp_f24 = angle_byte_cos(temp_s0_2 & 0xFF);
                        temp_f26 = angle_byte_cos((temp_s0_2 - 0x40) & 0xFF);
                        temp_f28 = angle_byte_cos(temp_s1 & 0xFF);
                        temp_f22 = angle_byte_cos((temp_s1 - 0x40) & 0xFF);
                        temp_f6 = random_float() * 0.5f;
                        sp.u15D = 4;
                        temp_f20 = temp_f6 + 18.8f;
                        sp.u154 = (random_int() & 0xF) + 0x23;
                        sp.u128 = (random_float() * 2.3f) + 2.9f;
                        temp_f2 = temp_f20 * temp_f28;
                        sp.u138 = (random_float() * 0.1f) + 0.7f;
                        sp.u12C = temp_f2 * temp_f26;
                        sp.u130 = -temp_f20 * temp_f22;
                        sp.u134 = temp_f2 * temp_f24;
                        trail_spawn(&sp.u148, &sp.u128, 0, 1, 2, 0, 0, 0, 0, 0, 0, &sp.u104, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                        var_s2 -= 1;
                    } while (var_s2 != 0);
                }
                temp_f20_2 = random_float() + 2.5f;
                temp_f18 = random_float() * 200.0f;
                sp.uE1 = 0xFF;
                temp_f2_2 = temp_f18 + 600.0f;
                sp.uE2 = 0xFF;
                sp.uDA = 0;
                sp.uD8 = 0;
                sp.uE0 = 0xFF;
                sp.uE4 = 0;
                sp.uE5 = 0;
                sp.uE6 = 0;
                sp.uCE = (s16) (s32) temp_f2_2;
                sp.uDC = 0x64;
                sp.uE3 = 0xFF;
                sp.uDE = 0;
                sp.uC0 = 0;
                sp.uC2 = 0;
                sp.uD0 = 0;
                sp.uD2 = 0;
                sp.uD1 = 0;
                sp.uCA = 0;
                sp.uCC = 0;
                sp.uD6 = 0;
                sp.uD4 = 0;
                sp.uD3 = 0xB;
                sp.uE8 = 0;
                sp.uB8 = (s32) (temp_f2_2 / temp_f20_2);
                sp.uDF = 0;
                sp.uBC = 0;
                sp.uB4 = g_owner_spark_sprite;
                sp.uC4 = (s16) (s32) sp.u148;
                sp.uC6 = (s16) (s32) sp.u14C;
                sp.uC8 = (s16) (s32) sp.u150;
                node_spawn_sprite(&sp.uB4, 0, 0, -1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
        }
    }
}
// some funky xor going on
// spawns the objects of g_owner_spawn_lists[0]; also checksums the code range
// quadtree_alloc_node_pool..D_15001B08 and, if it was modified, clears object list 35 (anti-tamper)
// owner_spawn_children: spawns the objects of spawn list g_owner_spawn_lists[0] (effect_node_create_nodraw kind 0x27) for `owner`
// (P151): each new object gets the owner (+0x28), its sub-type (+0x2C = owner +0x3B) and the entry byte (+0x2D);
// stops when a spawn fails. The N64 code also sums the code words quadtree_alloc_node_pool..D_15001B08 and on a mismatch
// (anti-tamper) clears the object lists g_node_lists +0x8C / +0x22C; the port has no MIPS code there, so the
// NON_MATCHING build skips the check (as menu_settings_apply_checked, P127).
/* was func_150AEB9C */
void owner_spawn_children(u8 *owner) {
    s32 i;
    u8 *obj;

    if (owner == NULL) {
        return;
    }
    for (i = 0; i < g_owner_spawn_lists[0].count; i++) {
        obj = (u8 *)effect_node_create_nodraw(g_owner_spawn_lists[0].entries[i].unk2, 0, -1, 1, 0x27, 8, 0xFF, 0);
        if (obj == NULL) {
            return;
        }
        *(u8 **)(obj + 0x28) = owner;
        obj[0x2C] = owner[0x3B];
        obj[0x2D] = g_owner_spawn_lists[0].entries[i].unk0;
    }
}
// NON-MATCHING: regalloc; checksums code quadtree_alloc_node_pool..D_15001B08 against 0x1B61AF60 (anti-tamper), clears object list 35 on mismatch
// void owner_spawn_children(u8 *arg0) {
//     u32 *p;
//     u32 sum;
//     s32 i;
//     u8 *obj;
//
//     if (arg0 == NULL) {
//         return;
//     }
//     sum = 0;
//     for (p = (u32 *)quadtree_alloc_node_pool; p < D_15001B08; p++) {
//         sum ^= *p;
//         sum <<= 1;
//     }
//     if (sum != 0x1B61AF60) {
//         g_node_lists[0][35] = NULL;
//         g_node_lists[1][35] = NULL;
//     }
//     for (i = 0; i < g_owner_spawn_lists[0].count; i++) {
//         obj = (u8 *)effect_node_create_nodraw(g_owner_spawn_lists[0].entries[i].unk2, 0, -1, 1, 0x27, 8, 0xFF, 0);
//         if (obj == NULL) {
//             return;
//         }
//         *(u8 **)(obj + 0x28) = arg0;
//         obj[0x2C] = arg0[0x3B];
//         obj[0x2D] = g_owner_spawn_lists[0].entries[i].unk0;
//     }
// }

/* was func_150AECCC */
void particle_fall_step(struct42 *arg0) {
    arg0->unk96 = arg0->unk96 + (arg0->unk94 * g_frame_ticks);
    if (arg0->unk96 >= 0x1401) {
        arg0->unk96 = 0x1400;
    }
    arg0->unk9E = arg0->unk9E - ((s32) arg0->unk96 >> 8);
    arg0->unkA4 = arg0->unkA4 + g_frame_ticks;
    if (arg0->unkA4 >= 0x1A) {
        arg0->unkA4 = 0x19;
    }
}

/* was func_150AED4C */
void sprite_grow_step(struct114 *arg0) {
    arg0->unk34 += arg0->unk14 * g_frame_ticks;
    if (arg0->unk2A < arg0->unk34) {
        arg0->unk3A = 70;
        arg0->unk34 = arg0->unk2A;
    }
    arg0->unk36 = arg0->unk34;
}

/* was func_150AED9C */
s32 sprite_fade_in_alpha(struct_eu_sprite *arg0) {
    struct_eu_sprite_sub *sub = arg0->unk98;
    s32 v = arg0->unk1C * 8;

    if (v >= 0x100) {
        v = 0xFF;
    }
    sub->unk1B = v;
    if (sub->unk1B < 0) {
        return 0;
    }
    return 1;
}

/* was func_150AEDD8 */
s32 sprite_fade_in_age(struct202 *arg0) {
    if (arg0->unk1C < 0x20) {
        arg0->unk28 = arg0->unk1C * 8;
    }
    return 1;
}

/* was func_150AEDF8 */
void owner_child_handle_msg(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 new_var;
  u8 *v = arg0 + 0x28;
  if (arg2 == 0x2D)
  {
    if (arg1[0] == (*((s32 *) v)))
    {
      *((s32 *) v) = arg1[1];
      v[4] = ((u8 *) arg1)[9];
    }
    else
    {
      if (arg1[1] == (*((s32 *) v)))
      {
        *((s32 *) v) = arg1[0];
        v[4] = ((u8 *) arg1)[8];
 } dummy_label_982087: ;
      ;
    }
  }
  else
    if (arg2 == 0)
  {
    new_var = arg1[0];
    if (((*((s32 *) v)) == new_var) || ((v[4] ^ 0) == ((u8 *) arg1)[4]))
    {
      node_destroy(arg0);
    }
  }
}
// void owner_child_handle_msg(void *arg0, void *arg1, s32 arg2) {
//     s32 temp_a0;
//     s32 temp_t6;
//     s32 temp_v1;
//     void *temp_v0;
//     void *temp_v0_2;
//
//     temp_t6 = arg2 & 0xFF;
//     if (temp_t6 == 0x2D) {
//         temp_v0 = arg0->unk28;
//         temp_a0 = temp_v0->unk0;
//         temp_v1 = arg1->unk0;
//         if (temp_v1 == temp_a0) {
//             temp_v0->unk0 = (s32) arg1->unk4;
//             temp_v0->unk4 = (u8) arg1->unk9;
//             return;
//         }
//         if (arg1->unk4 == temp_a0) {
//             temp_v0->unk0 = temp_v1;
//             temp_v0->unk4 = (u8) arg1->unk8;
//             return;
//         }
//     } else {
//         temp_v0 = arg0->unk28;
//         if (temp_t6 == 0) {
//             if ((arg1->unk0 == temp_v0->unk0) || ((temp_v0->unk4 == (u8) arg1->unk4))) {
//                 node_destroy(arg0, temp_t6, arg0);
//             }
//         }
//     }
// }
