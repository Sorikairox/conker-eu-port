#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 g_fx_model_emitter_recs[]; /* was D_800A13B0 */
u8 *world_record_find(u8);

/* was func_150E15E0 */
struct260 *fx_model_emitter_spawn(u8 arg0, u8 arg1, s32 arg2) {
    struct260 *temp_v0;
    struct {
        u8 unk0;
        u8 pad1[3];
        u8 *unk4;
        s32 unk8;
        f32 unkC;
    } tmp;

    if ((s32)arg0 < 0) {
        return NULL;
    }
    if (arg0 >= 2) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = world_record_find(g_fx_model_emitter_recs[arg0]);
    if (tmp.unk4 == NULL) {
        return NULL;
    }
    collision_select_area(0);
    tmp.unk8 = zone_tree_find_leaf(*(s16 *)(tmp.unk4 + 0x10), *(s16 *)(tmp.unk4 + 0x14));
    tmp.unkC = 0.0f;
    temp_v0 = effect_node_create(300, -1, 0x1F, -1, 0, 0x1F, 0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return temp_v0;
}

s32 particle_spawn_basic(s32 *, s32, s32, u8, s32);
void xform_points_ptrs(void *, void *, void *, s32);
extern s32 g_fx_model_emitter_pts_a; /* was D_800A13B4 */
extern s32 g_fx_model_emitter_pts_b; /* was D_800A13CC */

/* was func_150E16CC */
void fx_model_emitter_update(u8 *arg0) {
    struct {
        f32 * u94;
        f32 * u98;
        u8 * u9C;
        u8 * uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        s32 uB4;
        s32 uB8;
        s16 uBC;
        s16 uBE;
        s32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        s8 uCD;
        s8 uCE;
        s8 uCF;
        s8 uD0;
        s8 uD1;
        s16 uD2;
        s16 uD4;
        s16 uD6;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        s32 u10C;
        u8 pad110[0x4];
        s8 u114;
        s8 u115;
        s8 u116;
        s8 u117;
        s8 u118;
        s8 u119;
    } sp;
    f32 temp_f2;
    f32 temp_f2_2;
    s16 var_v1;
    s32 temp_t7;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((204.0f + (random_float() * 159.0f)) * 0.001f * g_frame_step_f));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        var_v0 = 0;
        var_v1 = 0;
        if (g_last_player_index >= 0) {
            do {
                temp_t7 = 1 << var_v0;
                var_v0 += 1;
                var_v1 |= temp_t7;
            } while (g_last_player_index >= var_v0);
        }
        if (!((*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s1 + 8))) + 2)) & var_v1)) {
            do {
                (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
            return;
        }
        sp.uD1 = 0x29;
        sp.uBC = 0x4403;
        sp.uB4 = 0x200005;
        sp.uD2 = 0x21;
        sp.uD4 = 7;
        sp.u10C = 0x1CE05;
        sp.u114 = 6;
        sp.u115 = 8;
        sp.u116 = 0x10;
        sp.u117 = -1;
        sp.uB8 = 0;
        sp.uC0 = 0;
        sp.uC4 = 0;
        sp.u108 = 0.0f;
        sp.u118 = -1;
        sp.u119 = 0;
        sp.uD6 = 0x27;
        sp.uC8 = 0xDD;
        sp.uC9 = 0xD3;
        sp.uCA = 0xCD;
        sp.uCB = 0xFF;
        sp.uCC = 0x57;
        sp.uCD = 0x55;
        sp.uCE = 0x5A;
        sp.uD0 = 0xFF;
        sp.uB0 = 0.962339f;
        sp.uD8 = 1.011462f;
        sp.u9C = (u8 *) &g_fx_model_emitter_pts_a + (*(u8 *)((u8 *)temp_s1 + 0)) * 0xC;
        sp.uA0 = (u8 *) &g_fx_model_emitter_pts_b + (*(u8 *)((u8 *)temp_s1 + 0)) * 0xC;
        sp.u94 = &sp.uE4;
        sp.u98 = &sp.uA4;
        xform_points_ptrs((*(s32 *)((u8 *)temp_s1 + 4)), &sp.u9C, &sp.u94, 2);
        sp.uA4 -= sp.uE4;
        sp.uA8 -= sp.uE8;
        sp.uAC -= sp.uEC;
        do {
            sp.u10C &= ~0xC0;
            var_s0 = 0;
            if (random_int() & 1) {
                var_s0 = 0x80;
            }
            if (random_int() & 1) {
                var_v0_2 = 0x40;
            } else {
                var_v0_2 = 0;
            }
            sp.u10C |= var_v0_2 | var_s0;
            sp.uF0 = 0.0f;
            sp.uF4 = 0.0f;
            sp.uF8 = 0.0f;
            sp.uCF = 0xFF;
            sp.uBE = (random_int() % 17U) + 0x32;
            temp_f2 = (random_float() * 165.0f) + 357.0f;
            sp.uDC = temp_f2;
            sp.uE0 = temp_f2;
            temp_f2_2 = ((random_float() * 195.0f) + 356.0f) * 0.001f;
            sp.uFC = sp.uA4 * temp_f2_2;
            sp.u100 = sp.uA8 * temp_f2_2;
            sp.u104 = sp.uAC * temp_f2_2;
            temp_v0 = particle_spawn_basic(&sp.uB4, 1, 4, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.uB0, 4);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}