#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150BA4C0 */
void crumble_emitter_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = effect_node_create((random_int() % 9U) + 15, -1, 0x52, -1, 1, 0x3F, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#ifdef NON_MATCHING
void vec3_from_angles_byte(s16, s16, f32, void *);
void obj_get_fx_point_b(u8 *, f32 *, f32 *, f32 *);
s32 tumble_debris_spawn(f32 *, f32 *, f32, f32 *, f32 *, f32, f32, s32, s32, s32, s32, s32, s32);

/* was func_150BAA3C */
void crumble_emitter_update(u8 *arg0) {
    struct {
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        s32 uE8;
        s32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    f32 temp_f6;
    s32 temp_s0;
    s32 temp_s5;
    u8 *temp_s1;
    u8 *temp_s4;

    temp_s4 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s1 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s4 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s4 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if ((*(s32 *)((u8 *)temp_s4 + 0x1D4)) != 0) {
        (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((0.3143f + (random_float() * 0.58100003f)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f) {
            sp.uD8 = ((*(f32 *)((u8 *)temp_s4 + 0x14C)) + (*(f32 *)((u8 *)temp_s4 + 0x150))) * 0.5f;
            temp_s5 = ((s32) (*(u16 *)((u8 *)temp_s4 + 0x76)) >> 8) - 0x40;
            obj_get_fx_point_b(temp_s4, &sp.uF0, &sp.uEC, &sp.uE8);
            sp.uE0 = 0.0f;
            do {
                temp_s0 = random_int();
                vec3_from_angles_byte((s16) ((((u32) temp_s0 % 127U) + temp_s5) - 0x3F), (s16) ((random_int() % 31U) - 0x32), sp.uEC, &sp.uCC);
                temp_f6 = sp.uD0 * (*(f32 *)((u8 *)temp_s4 + 0xF0));
                sp.uCC += sp.uF0;
                sp.uD0 = temp_f6;
                sp.uD0 = temp_f6 + sp.uF4;
                sp.uD4 += sp.uF8;
                sp.uC0 = random_float() * 360.0f;
                sp.uC4 = random_float() * 360.0f;
                sp.uC8 = random_float() * 360.0f;
                temp_f2 = (random_float() * 0.094000004f) + 0.051000003f;
                sp.uB4 = (sp.uCC - sp.uF0) * temp_f2;
                sp.uB8 = (sp.uD0 - sp.uF4) * temp_f2;
                sp.uBC = (sp.uD4 - sp.uF8) * temp_f2;
                sp.uDC = (random_float() * 18.645f) + -9.3225f;
                sp.uE4 = (random_float() * 18.645f) + -9.3225f;
                temp_f22 = random_float();
                temp_f20 = random_float();
                tumble_debris_spawn(&sp.uCC, &sp.uC0, ((temp_f22 * 0.080000006f) + 0.1f) * sp.uD8, &sp.uB4, &sp.uDC, (temp_f20 * 0.324f) + -0.563f, 0.944854f, 7, (random_int() % 41U) + 0x3C, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1 + 8)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E81B0/crumble_emitter_update.s")
#endif
/* was func_150BADD0 */
void crumble_emitter_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    effect_node_link_message(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

s32 hitinfo_from_obj_floor(s32, u8 *);
s32 collision_floor_probe(f32 *, s32, f32, s32);
extern f32 D_800A0230;

/* was func_150BAE10 */
s32 obj_get_ground_point(f32 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    f32 sp24[3];

    arg0[0] = *(f32 *)(arg1 + 0x14);
    if (D_800A0230 < *(f32 *)(arg1 + 0x180)) {
        arg0[1] = *(f32 *)(arg1 + 0x180);
    } else {
        arg0[1] = *(f32 *)(arg1 + 0x18);
    }
    arg0[2] = *(f32 *)(arg1 + 0x1C);
    if (arg2 == 0) {
        return 1;
    }
    sp24[0] = arg0[0];
    sp24[1] = arg0[1] + 100.0f;
    sp24[2] = arg0[2];
    hitinfo_from_obj_floor(arg2, arg1);
    return collision_floor_probe(sp24, 0, arg0[1] - 100.0f, arg2);
}

/* was func_150BAEE0 */
s32 crumble_return_9(s32 arg0, s32 arg1) {
    return 9;
}

#ifdef NON_MATCHING
s32 fx_try_camera_shake(s32, s32);
void spawn_circle_random_emit(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
s32 water_ring_spawn(s32, s32, s32, s32, s32, s32, s32, s32, s32);

/* was func_150BAEF4 */
void obj_heavy_impact_fx(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u48;
        u8 pad4C[0x20];
        f32 u6C;
        f32 u70;
        f32 u74;
    } sp;
    s32 sp44;
    u8 sp43;
    f32 sp38;

    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        sp43 = obj_get_ground_point(&sp.u6C, arg0, (s32) &sp.u48, (s32) arg1);
        rumble_all_players_at((struct17 *) &sp.u6C, 1307.0f, 2000.0f, 0.0005f, 0xC, 0xF, 0xFF, 0);
        fx_try_camera_shake(5, 0x4022);
        if (sp43 != 0) {
            sp44 = (s32) (D_800DBFF0[D_80082FA4].unk380 * 0.7111111f);
            water_ring_spawn(-1, (s32) sp.u6C, (s32) (sp.u70 + 6.0f), (s32) sp.u74, 0x19, 0x12, 0, 0xFF, 1);
            sp38 = random_float();
            spawn_circle_random_emit(sp.u6C, sp.u70, sp.u74, (sp38 * 50.0f) + 40.0f, sp44 + 0x3C, sp44 - 0x3C, (random_int() % 11U) + 0x1E, 5, 0, 0.0f, 0, 0xFF);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E81B0/obj_heavy_impact_fx.s")
#endif