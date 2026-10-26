#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_8009684E[];
#endif

// fat struct to decipher
#ifdef NON_MATCHING
extern f32 D_80096850;
extern f32 D_80096854;
extern f32 D_80096858;
extern f32 D_8009685C;
extern f32 D_80096860;
void storm_controller_spawn(void);
void collision_select_area(s32);
s32 mdl_particle_spawn(f32 *, s32, s32, s32, s32, s32);
u8 *mesh_effect_spawn(s8 *, s32, s32, s32, s32);
s32 memcpy(u8 *, f32 *, s32);
extern s32 D_80096800;
extern u8 D_80096848;

/* was func_15010A60 */
void level_obj_init_debris_table(void) {
    struct {
        s32 uA0;
        u8 padA4[0xC];
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s8 uC0;
        s8 uC1;
        s16 uC2;
        s8 uC4;
        u8 padC5[0xB];
        f32 uD0;
        f32 uD4;
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
        s32 u100;
        u8 pad104[0x8];
        f32 u10C;
        f32 u110;
        s8 u114;
        s8 u115;
        s8 u116;
        u8 pad117[0x1];
        s16 u118;
        u8 pad11A[0x2A];
        s32 u144;
        s32 u148;
        s8 u14C;
        u8 pad14D[0x7];
        f32 u154;
        f32 u158;
        f32 u15C;
        f32 u160;
        f32 u164;
        f32 u168;
        f32 u16C;
        f32 u170;
        f32 u174;
        f32 u178;
        f32 u17C;
        u8 pad180[0x4];
        f32 u184;
        f32 u188;
        f32 u18C;
        f32 u190;
        f32 u194;
        f32 u198;
        f32 u19C;
        f32 u1A0;
        s32 u1A4;
        s16 u1A8;
        s16 u1AA;
        s8 u1AC;
        u8 pad1AD[0x3];
        s32 u1B0;
        s8 u1B4;
        s8 u1B5;
        s8 u1B6;
        s8 u1B7;
        s8 u1B8;
        s8 u1B9;
        s8 u1BA;
        s8 u1BB;
        s8 u1BC;
        u8 pad1BD[0x1];
        s8 u1BE;
        u8 pad1BF[0x1];
        s32 u1C0;
        s8 u1C4;
        u8 pad1C5[0x1];
        s16 u1C6;
        s16 u1C8;
    } sp;
    s32 *var_s1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_t2;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f4;
    f32 var_f6;
    s32 temp_t1;
    s32 temp_t2_2;
    s32 temp_t2_3;
    s32 temp_t3;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_v0;
    struct225 *temp_v0_3;
    u32 temp_s0;
    u32 temp_s0_2;
    u32 temp_s0_3;
    u32 temp_s0_4;
    u32 temp_s0_5;
    u32 temp_s0_6;
    u8 *var_s2;
    u8 *temp_v0_2;

    storm_controller_spawn();
    sp.u115 = 3;
    sp.u116 = 6;
    sp.u118 = 0x12C;
    sp.u144 = 9;
    sp.u114 = 0;
    sp.u148 = 0x1AF;
    sp.u14C = 0;
    sp.u1A4 = 0xD00;
    sp.u1A8 = 0x12C;
    sp.u1AA = 0x56;
    sp.u1AC = 0;
    sp.u1B4 = 0xFF;
    sp.u1B5 = 0x10;
    sp.u1B6 = 0;
    sp.u1B7 = 0;
    sp.u1B8 = 0;
    sp.u1B9 = 0;
    sp.u1BA = 0;
    sp.u1BB = 0;
    sp.u1BC = 2;
    sp.u1BE = 2;
    sp.u1C0 = 0;
    sp.u1C4 = 0;
    sp.u1C6 = 1;
    sp.u1C8 = 0xFF;
    var_s2 = &D_80096848;
    var_s1 = &D_80096800;
    sp.u164 = 0.0f;
    sp.u168 = 0.0f;
    sp.u16C = 0.0f;
    sp.u188 = 0.0f;
    sp.u18C = 0.0f;
    sp.u190 = 0.0f;
    sp.u194 = 0.0f;
    sp.u198 = 0.0f;
    sp.u19C = 0.0f;
    sp.u1A0 = 0.0f;
    sp.u10C = 0.0f;
    sp.u110 = 0.0f;
    sp.u154 = 1.0f;
    sp.u158 = 1.0f;
    sp.u160 = 1.0f;
    sp.u15C = 1.0f;
    sp.u170 = 1.0f;
    sp.u174 = 1.0f;
    sp.u178 = 1.0f;
    do {
        temp_t2 = (*(f32 *)((u8 *)var_s1 + 4));
        (*(f32 *)((u8 *)(&sp.uA0) + 0)) = (f32) (*(f32 *)((u8 *)var_s1 + 0));
        (*(f32 *)((u8 *)(&sp.uA0) + 4)) = temp_t2;
        (*(f32 *)((u8 *)(&sp.u17C) + 4)) = temp_t2;
        (*(f32 *)((u8 *)(&sp.uA0) + 8)) = (f32) (*(f32 *)((u8 *)var_s1 + 8));
        (*(f32 *)((u8 *)(&sp.u100) + 4)) = temp_t2;
        (*(f32 *)((u8 *)(&sp.u17C) + 0)) = (*(f32 *)((u8 *)(&sp.uA0) + 0));
        (*(f32 *)((u8 *)(&sp.u17C) + 8)) = (f32) (*(f32 *)((u8 *)(&sp.uA0) + 8));
        (*(f32 *)((u8 *)(&sp.u100) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uA0) + 0));
        (*(f32 *)((u8 *)(&sp.u100) + 8)) = (f32) (*(f32 *)((u8 *)(&sp.uA0) + 8));
        collision_select_area(0);
        sp.u1B0 = zone_tree_find_leaf((s32) sp.u17C, (s32) sp.u184);
        temp_s0 = osGetCount();
        temp_t2_2 = (random_int() * temp_s0) & 0xFFFF;
        var_f18 = (f32) temp_t2_2;
        if (temp_t2_2 < 0) {
            var_f18 += 4294967296.0f;
        }
        temp_f2 = 2.0f * (var_f18 * D_80096860) * D_8009685C;
        sp.uE8 = temp_f2;
        sp.uD0 = temp_f2;
        temp_s0_2 = osGetCount();
        temp_t3 = (random_int() * temp_s0_2) & 0xFFFF;
        var_f10 = (f32) temp_t3;
        if (temp_t3 < 0) {
            var_f10 += 4294967296.0f;
        }
        temp_f2_2 = 2.0f * (var_f10 * D_80096860) * D_8009685C;
        sp.uEC = temp_f2_2;
        sp.uD4 = temp_f2_2;
        temp_s0_3 = osGetCount();
        temp_t7 = (random_int() * temp_s0_3) & 0xFFFF;
        var_f6 = (f32) temp_t7;
        if (temp_t7 < 0) {
            var_f6 += 4294967296.0f;
        }
        temp_f0 = (var_f6 * D_80096860 * D_80096858) + 2.0f;
        sp.uF8 = temp_f0;
        sp.uE0 = temp_f0;
        temp_s0_4 = osGetCount();
        temp_t8 = (random_int() * temp_s0_4) & 0xFFFF;
        var_f18_2 = (f32) temp_t8;
        if (temp_t8 < 0) {
            var_f18_2 += 4294967296.0f;
        }
        temp_f0_2 = (var_f18_2 * D_80096860 * D_80096858) + 2.0f;
        sp.uFC = temp_f0_2;
        sp.uE4 = temp_f0_2;
        temp_s0_5 = osGetCount();
        temp_t1 = (random_int() * temp_s0_5) & 0xFFFF;
        var_f4 = (f32) temp_t1;
        if (temp_t1 < 0) {
            var_f4 += 4294967296.0f;
        }
        temp_f0_3 = (var_f4 * D_80096860 * D_80096854) + D_80096850;
        sp.uF0 = temp_f0_3;
        sp.uD8 = temp_f0_3;
        temp_s0_6 = osGetCount();
        temp_t2_3 = (random_int() * temp_s0_6) & 0xFFFF;
        var_f10_2 = (f32) temp_t2_3;
        if (temp_t2_3 < 0) {
            var_f10_2 += 4294967296.0f;
        }
        temp_f0_4 = (var_f10_2 * D_80096860 * D_80096854) + D_80096850;
        sp.uF4 = temp_f0_4;
        sp.uDC = temp_f0_4;
        temp_v0 = mdl_particle_spawn(&sp.u154, 3, 0xFF, 0x18, 0xFF, 1);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x170, &sp.uD0, 0x18);
        }
        if (*var_s2 != 0) {
            temp_v0_2 = mesh_effect_spawn(&sp.u114, 0, 0x2C, 0xFF, 1);
            if (temp_v0_2 != NULL) {
                memcpy(temp_v0_2 + (*(s32 *)((u8 *)temp_v0_2 + 0x50)) + 0xF8, &sp.uE8, 0x2C);
            }
            sp.uB4 = (s32) (*(f32 *)((u8 *)var_s1 + 0));
            sp.uB8 = (s32) (*(f32 *)((u8 *)var_s1 + 4));
            sp.uB0 = temp_v0;
            sp.uC0 = 2;
            sp.uC1 = 0x16;
            sp.uC2 = 0x12C;
            sp.uC4 = 0;
            sp.uBC = (s32) (*(f32 *)((u8 *)var_s1 + 8));
            temp_v0_3 = light_create_with_ctrl((Header *) &sp.uC0, (Header2 *) &sp.uB4, 0xC, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 4, 0xFFU, 1);
            if (temp_v0_3 != NULL) {
                memcpy(((struct225 *)((u8 *)temp_v0_3 + 0x18)), (f32 *) &sp.uB0, 4);
            }
        }
        var_s2 += 1;
        var_s1 = (s32 *)((u8 *)var_s1 + (0xC));
    } while (var_s2 != ((u8 *)&D_8009684E));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_3DF10/level_obj_init_debris_table.s")
#endif