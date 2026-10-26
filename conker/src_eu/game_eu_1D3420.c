#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void bubble_emitter_spawn(u8 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5);
#endif


#ifdef NON_MATCHING
s32 collision_floor_probe(f32 *, s32, f32, u8 *);
s32 player_mask_hides_all(s32);
s32 spark_spawn_from_desc(f32 *, s32, s32, s32, s32, s32);

/* was func_151A5C10 */
void bubble_zone_update(u8 *arg0) {
    struct {
        f32 u6C;
        f32 u70;
        f32 u74;
        u8 pad78[0x44];
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s16 uDC;
        s16 uDE;
        s16 uE0;
        s8 uE2;
        s8 uE3;
        s8 uE4;
        s8 uE5;
        s16 uE6;
        s8 uE8;
        s8 uE9;
        s8 uEA;
        s8 uEB;
        s32 uEC;
        s8 uF0;
        u8 padF1[0x3];
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
    } sp;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f24_3;
    f32 temp_f26;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 var_f14;
    f32 var_f20;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_4;
    s16 temp_a1;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s32 temp_a0;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_v0_6;
    s32 temp_v0_9;
    u8 *temp_s0;
    u8 *temp_v0;
    u8 *temp_v0_10;
    u8 *temp_v0_11;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_7;
    u8 *temp_v0_8;

    temp_s0 = arg0 + 0x28;
    if ((*(s32 *)((u8 *)arg0 + 0x28)) == 0) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if (((*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 0x14)) != 1) && ((temp_a0 = (*(s32 *)((u8 *)temp_s0 + 0x6C)), (temp_a0 == 0)) || (player_mask_hides_all(temp_a0) == 0))) {
        (*(f32 *)((u8 *)temp_s0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0xC)) + ((*(f32 *)((u8 *)temp_s0 + 8)) * (*(f32 *)((u8 *)temp_s0 + 4)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_s0 + 0xC)) > 1.0f) {
            sp.uDC = 0x6231;
            sp.uDE = 0x1A4D;
            sp.uE2 = 0;
            sp.uE3 = 0;
            sp.uE4 = 0;
            sp.uE5 = 0xFF;
            sp.uE6 = 1;
            sp.uE9 = 0xFF;
            sp.uEC = 0;
            sp.uEA = 0;
            sp.uEB = 0;
            sp.uF0 = 0x10;
            sp.uF8 = (*(f32 *)((u8 *)temp_s0 + 0x10));
            do {
                temp_v0 = (*(u8 **)((u8 *)temp_s0 + 0));
                temp_t6 = (*(u8 *)((u8 *)temp_v0 + 0x15)) & 3;
                switch (temp_t6) {                  /* irregular */
                default:
                    sp.uBC = (f32) (*(s16 *)((u8 *)temp_v0 + 0));
                    sp.uC4 = (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 4));
                    temp_v0_2 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_v1 = (*(s16 *)((u8 *)temp_v0_2 + 2));
                    temp_a0_2 = (*(s16 *)((u8 *)temp_v0_2 + 8));
                    var_f20 = (f32) (temp_v1 - temp_a0_2);
                    var_f14 = (f32) (temp_v1 + temp_a0_2);
                    break;
                case 2:
                    temp_t3 = (u32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) * 0.7111111f) & 0xFF;
                    temp_f22 = angle_byte_cos((temp_t3 - 0x40) & 0xFF);
                    temp_f24 = angle_byte_cos(temp_t3 & 0xFF);
                    temp_v0_3 = (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 6));
                    temp_f26 = (random_float() * (2.0f * (f32) temp_v0_3)) + (f32) -temp_v0_3;
                    temp_v0_4 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_a1 = (*(s16 *)((u8 *)temp_v0_4 + 0xA));
                    temp_f2 = (random_float() * (2.0f * (f32) temp_a1)) + (f32) -temp_a1;
                    sp.uBC = (f32) (*(s16 *)((u8 *)temp_v0_4 + 0)) + ((temp_f26 * temp_f24) + (temp_f2 * temp_f22));
                    sp.uC4 = (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 4)) + ((temp_f2 * temp_f24) - (temp_f26 * temp_f22));
                    temp_v0_5 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_v1_2 = (*(s16 *)((u8 *)temp_v0_5 + 2));
                    temp_a0_3 = (*(s16 *)((u8 *)temp_v0_5 + 8));
                    var_f14 = (f32) (temp_v1_2 + temp_a0_3);
                    var_f20 = (f32) (temp_v1_2 - temp_a0_3);
                    break;
                case 0:
                    temp_v0_6 = random_int();
                    temp_f22_2 = angle_byte_cos((temp_v0_6 - 0x40) & 0xFF);
                    temp_f24_2 = angle_byte_cos(temp_v0_6 & 0xFF & 0xFF);
                    temp_v0_7 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_f2_2 = random_float() * (f32) (*(s16 *)((u8 *)temp_v0_7 + 6));
                    sp.uBC = (f32) (*(s16 *)((u8 *)temp_v0_7 + 0)) + (temp_f2_2 * temp_f24_2);
                    sp.uC4 = (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 4)) - (temp_f2_2 * temp_f22_2);
                    temp_v0_8 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_v1_3 = (*(s16 *)((u8 *)temp_v0_8 + 2));
                    var_f20 = (f32) temp_v1_3;
                    var_f14 = (f32) (temp_v1_3 + (*(s16 *)((u8 *)temp_v0_8 + 8)));
                    break;
                case 1:
                    temp_v0_9 = random_int();
                    temp_f22_3 = angle_byte_cos((temp_v0_9 - 0x40) & 0xFF);
                    temp_f24_3 = angle_byte_cos(temp_v0_9 & 0xFF & 0xFF);
                    temp_v0_10 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_f2_3 = random_float() * (f32) (*(s16 *)((u8 *)temp_v0_10 + 6));
                    sp.uBC = (f32) (*(s16 *)((u8 *)temp_v0_10 + 0)) + (temp_f2_3 * temp_f24_3);
                    sp.uC4 = (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0))) + 4)) - (temp_f2_3 * temp_f22_3);
                    temp_v0_11 = (*(u8 **)((u8 *)temp_s0 + 0));
                    temp_v1_4 = (*(s16 *)((u8 *)temp_v0_11 + 2));
                    temp_a0_4 = (*(s16 *)((u8 *)temp_v0_11 + 8));
                    var_f14 = (f32) (temp_v1_4 + temp_a0_4);
                    var_f20 = (f32) (temp_v1_4 - temp_a0_4);
                    break;
                }
                if ((*(u8 *)((u8 *)temp_s0 + 0x40)) != 0) {
                    sp.u6C = sp.uBC;
                    sp.u70 = var_f14;
                    sp.u74 = sp.uC4;
                    if (collision_floor_probe(&sp.u6C, 0, var_f20, temp_s0 + 0x48) != 0) {
                        sp.uC0 = (*(f32 *)((u8 *)temp_s0 + 0x48));
                    } else {
                        sp.uC0 = var_f20;
                    }
                } else {
                    sp.uC0 = var_f20;
                }
                temp_f20 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x18))) + (*(f32 *)((u8 *)temp_s0 + 0x14));
                temp_f2_4 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x20))) + (*(f32 *)((u8 *)temp_s0 + 0x1C));
                temp_f18 = 57.969f * temp_f2_4;
                sp.uC8 = 22.6f * temp_f20;
                sp.uD0 = 13.786f * temp_f20;
                sp.uCC = temp_f18;
                sp.uD4 = 42.714f * temp_f2_4;
                sp.uD8 = 118.763f * temp_f2_4;
                sp.uE0 = (random_int() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x26)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x24));
                sp.uF4 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x2C))) + (*(f32 *)((u8 *)temp_s0 + 0x28));
                sp.uFC = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x34))) + (*(f32 *)((u8 *)temp_s0 + 0x30));
                sp.u100 = (random_float() * (*(f32 *)((u8 *)temp_s0 + 0x3C))) + (*(f32 *)((u8 *)temp_s0 + 0x38));
                sp.uE8 = (random_int() % (u32) ((*(u8 *)((u8 *)temp_s0 + 0x42)) + 1)) + (*(u8 *)((u8 *)temp_s0 + 0x41));
                spark_spawn_from_desc(&sp.uBC, 0xA, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0xC)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s0 + 0xC)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/bubble_zone_update.s")
#endif
void bubble_zone_sound_stop(u16);
/* was func_151A625C */
void bubble_zone_retire(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C); // fakematch: re-load of the field (no andi)
  if ((*new_var) != 0)
  {
    bubble_zone_sound_stop(*new_var);
  }
  effect_node_retire(p);
}

void bubble_zone_sound_stop(u16);
/* was func_151A629C */
void bubble_zone_free(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C); // fakematch: re-load of the field (no andi)
  if ((*new_var) != 0)
  {
    bubble_zone_sound_stop(*new_var);
  }
  effect_node_free(p);
}

/* was func_151A62DC */
void bubble_zone_sound_stop(u16 arg0) {
    sound_voice_stop(arg0);
}

#ifdef NON_MATCHING
/* was func_151A6308 */
struct210 *bubble_sprite_spawn(f32 arg0, u8 arg1, s32 arg2, u8 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, s32 arg8) {
    struct {
        s32 u5C;
        s16 u60;
        s8 u62;
        s8 u63;
        s32 u64;
        s32 u68;
        u8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s32 u74;
        u8 pad78[0x4];
        s8 u7C;
        u8 pad7D[0x1];
        s16 u7E;
        s16 u80;
    } sp;
    s32 sp4C;
    s32 sp48;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;

    if (arg4 <= 0) {
        return NULL;
    }
    sp.u7E = 0x14;
    sp.u80 = 0xC;
    sp.u62 = 0x38;
    sp.u63 = 0;
    if (arg4 == -1) {
        var_v1_2 = 0;
    } else {
        var_v1_2 = 1;
    }
    var_v0_2 = 0;
    if (arg5 != 0) {
        var_v0_2 = 0x400;
    }
    sp.u5C = var_v0_2 | var_v1_2 | 0x1300 | 0x2000 | 0x8000 | 0x20000;
    if (arg4 == -1) {
        sp.u60 = 0x12C;
    } else {
        sp.u60 = arg4 + 0x14;
    }
    sp.u64 = 0;
    if (arg4 == -1) {
        sp.u68 = 0;
    } else {
        sp.u68 = 0x140000 / (s32) (arg4 + 0x14);
    }
    sp.u6D = 0xFF;
    sp.u6E = 0xFF;
    sp.u6F = 0x83;
    sp.u70 = 0x1E;
    sp.u71 = 0xFF;
    sp.u6C = arg1;
    if (arg6 != 0) {
        var_v0_3 = 2;
    } else {
        var_v0_3 = 3;
    }
    sp.u74 = var_v0_3 + 0x440000;
    sp.u72 = 0;
    sp.u73 = 6;
    sp.u7C = 0xFF;
    sp48 = random_int();
    sp4C = random_int();
    temp_t0 = random_int();
    if (arg5 != 0) {
        var_v1 = 3;
    } else {
        var_v1 = 0;
    }
    if (arg5 != 0) {
        var_v0 = 0xFF;
    } else {
        var_v0 = 0;
    }
    return sprite_fx_spawn_cam_at((s32) &sp.u5C, 0U, 0U, arg2, (*(f32 *)((u8 *)arg3 + 0)), (*(f32 *)((u8 *)arg3 + 4)), (*(f32 *)((u8 *)arg3 + 8)), arg0, arg0, (u8) (sp48 & 0xFF), (u8) (((temp_t0 & 1) * 2) + (sp4C & 1)), var_v1, var_v0, 0, (u8) (s32) arg7, arg8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/bubble_sprite_spawn.s")
#endif
#ifdef NON_MATCHING
/* was func_151A6520 */
void bubble_zone_handle_msg(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *sp2C;
    s32 temp_a1;
    s32 var_a0;
    s32 var_v0;
    u8 *temp_a0;
    u8 *var_v1;
    u8 temp_v1;
    u8 *temp_v0;

    if ((arg2 & 0xFF) == 0x35) {
        temp_a1 = (*(s32 *)((u8 *)arg1 + 0));
        var_v0 = 0;
        var_a0 = 0;
        if (temp_a1 > 0) {
            var_v1 = (*(u8 **)((u8 *)arg1 + 4));
loop_3:
            if ((*(u8 *)((u8 *)arg0 + 0x2C)) == *var_v1) {
                var_a0 = 1;
            } else {
                var_v0 += 1;
                var_v1 += 1;
            }
            if ((var_v0 < temp_a1) && (var_a0 == 0)) {
                goto loop_3;
            }
        }
        if (var_a0 != 0) {
            temp_v0 = arg0 + 0x28;
            temp_a0 = (*(u8 **)((u8 *)temp_v0 + 0));
            if ((*(u8 *)((u8 *)temp_a0 + 0x14)) == 1) {
                temp_v1 = (*(u8 *)((u8 *)temp_v0 + 0xC));
                sp2C = temp_v0;
                bubble_emitter_spawn(temp_a0, (*(s32 *)((u8 *)temp_v0 + 8)), temp_v1 & 1, temp_v1 & 2, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v0 + 0))) + 0x14)) = 0;
                (*(s32 *)((u8 *)temp_v0 + 0x10)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/bubble_zone_handle_msg.s")
#endif
s32 light_create_flicker_preset(void *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *memcpy(void *, const void *, s32);
extern f32 D_800A9178;
extern f32 D_800A917C;
typedef struct { f32 x, y, z; } V3_6618;
typedef struct {
    u8 u0;
    s8 u1;
    s16 u2;
    s16 u4;
    s16 pad6;
    s32 u8;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    V3_6618 u1C;
    f32 u28[3];
    f32 u34[3];
    s32 u40;
    u8 u44;
    u8 u45;
    s8 u46;
    s8 u47;
    s32 u48;
    u8 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
} Blk58_6618;
typedef struct {
    u8 *p;
    f32 u4;
    f32 u8;
    f32 uC;
    s32 u10;
    u8 u14;
    u8 u15;
    u8 u16;
    u8 u17;
    f32 u18;
} Tmp_6618;
typedef struct { u8 u0; u8 u1; s16 u2; u8 u4; } Blk2_6618;

/* was func_151A6618 */
void bubble_emitter_spawn(u8 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    Blk58_6618 blk;
    Tmp_6618 tmp;
    u8 *dst;
    u8 *temp_v0;

    tmp.p = arg0;
    tmp.u4 = 0.0f;
    tmp.u8 = (random_float() * 80.0f) + -380.0f;
    tmp.uC = (random_float() * D_800A9178) + D_800A917C;
    tmp.u10 = 0;
    tmp.u14 = random_int() & 0xFF;
    tmp.u15 = (random_int() & 3) + 4;
    tmp.u16 = 0xFF;
    tmp.u18 = 0.0f;
    tmp.u17 = arg3;
    blk.u0 = 0x6B;
    blk.u1 = 0xA;
    blk.u2 = 0x4C03;
    blk.u4 = 0xC8;
    blk.u8 = 0;
    blk.uC = 0;
    blk.u10[0] = 0xFF;
    blk.u10[1] = 0xFF;
    blk.u10[2] = 0xFF;
    blk.u10[3] = 0xFF;
    blk.u14 = *(s16 *)(arg0 + 6);
    blk.u18 = *(s16 *)(arg0 + 8);
    blk.u1C.x = *(s16 *)(arg0 + 0);
    blk.u1C.y = *(s16 *)(arg0 + 2);
    blk.u1C.z = *(s16 *)(arg0 + 4);
    blk.u28[0] = 0.0f;
    blk.u28[1] = 0.0f;
    blk.u28[2] = 0.0f;
    blk.u34[0] = 1.0f;
    blk.u34[1] = 1.0f;
    blk.u34[2] = 1.0f;
    blk.u40 = 0x01EC0009;
    blk.u44 = 0xFF;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 0;
    blk.u48 = arg1;
    blk.u4C = 0xFF;
    temp_v0 = effect3d_spawn_full(&blk, (s32)&D_800A4AA0, 0, 0x28, 0, 0x20, 0, 0, 0, 0x1C, arg4, arg5);
    if (temp_v0 != NULL) {
        dst = temp_v0 + 0x110;
        memcpy(dst, &tmp, 0x1C);
        if (arg2 != 0) {
            Blk2_6618 b2;
            s32 pos[3];

            pos[0] = *(s16 *)(arg0 + 0);
            pos[1] = (*(s16 *)(arg0 + 8) >> 1) + *(s16 *)(arg0 + 2);
            pos[2] = *(s16 *)(arg0 + 4);
            b2.u0 = 2;
            b2.u1 = 2;
            b2.u2 = 0x12C;
            b2.u4 = 6;
            *(s32 *)(dst + 0x10) = light_create_flicker_preset(&b2, pos, 0xFF, 0x79, 0, 0xFF, 0, 0, 0xE, arg4, arg5);
        }
    }
    if (arg2 != 0) {
        sfx_emitter_start(0x1AA, *(s16 *)(arg0 + 0), *(s16 *)(arg0 + 2), *(s16 *)(arg0 + 4), 0x4000, 0x3E8, 0x2EE, (s32)sfx_cb_keep_until_silent, arg0, 0, 8, random_int() & 0x300);
    }
}

#ifdef NON_MATCHING
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800DD608;
extern s32 D_800DD618;

/* was func_151A6900 */
u8 *bubble_emitter_draw(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        u8 pad38[0x10];
        u8 * u48;
        u8 * u4C;
    } sp;
    u8 *sp30;
    u8 *sp2C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_t0;
    u8 *temp_a1;
    u8 *temp_t0_2;
    u8 *temp_t2;
    u8 *temp_t5;
    u8 *temp_v0;

    vtx_slot_buffer_get(arg0 + 0x100, arg1, 0x40, &sp.u4C, &sp.u37);
    sp.u48 = sp.u4C;
    if (sp.u4C != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(u8 **)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(u8 **)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x114));
        temp_f12 = *(&D_800DD608 + temp_t0) * temp_f2;
        temp_f14 = *(&D_800DD618 + temp_t0) * temp_f2;
        temp_f4 = (s32) temp_f0;
        temp_f10 = (s32) (temp_f0 + (*(f32 *)((u8 *)arg0 + 0x11C)));
        (*(s16 *)((u8 *)sp.u4C + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f14);
        (*(s16 *)((u8 *)sp.u4C + 2)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(s16 *)((u8 *)sp.u4C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f12);
        (*(s16 *)((u8 *)sp.u4C + 8)) = (s16) temp_f4;
        (*(s16 *)((u8 *)sp.u4C + 0xA)) = 0x7C0;
        (*(u8 *)((u8 *)sp.u4C + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x126));
        (*(s16 *)((u8 *)sp.u4C + 6)) = 0;
        temp_t2 = sp.u4C + 0x10;
        sp.u4C = temp_t2;
        temp_t0_2 = temp_t2 + 0x10;
        (*(s16 *)((u8 *)temp_t2 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f14);
        (*(s16 *)((u8 *)temp_t2 + 2)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(s16 *)((u8 *)temp_t2 + 0xA)) = 0;
        (*(s16 *)((u8 *)temp_t2 + 8)) = (s16) temp_f4;
        (*(s16 *)((u8 *)temp_t2 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f12);
        (*(s16 *)((u8 *)temp_t2 + 6)) = 0;
        (*(u8 *)((u8 *)temp_t2 + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x126));
        sp.u4C = temp_t0_2;
        (*(s16 *)((u8 *)temp_t0_2 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f14);
        (*(s16 *)((u8 *)sp.u4C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)));
        (*(s16 *)((u8 *)sp.u4C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f12);
        (*(s16 *)((u8 *)sp.u4C + 8)) = (s16) temp_f10;
        (*(s16 *)((u8 *)sp.u4C + 0xA)) = 0;
        (*(u8 *)((u8 *)sp.u4C + 0xF)) = 0U;
        (*(s16 *)((u8 *)temp_t0_2 + 6)) = 0;
        temp_t5 = sp.u4C + 0x10;
        sp.u4C = temp_t5;
        (*(s16 *)((u8 *)temp_t5 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f14);
        (*(s16 *)((u8 *)temp_t5 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)));
        (*(s16 *)((u8 *)temp_t5 + 0xA)) = 0x7C0;
        (*(s8 *)((u8 *)temp_t5 + 0xF)) = 0;
        (*(s16 *)((u8 *)temp_t5 + 6)) = 0;
        (*(s16 *)((u8 *)temp_t5 + 8)) = (s16) temp_f10;
        (*(s16 *)((u8 *)temp_t5 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f12);
        return sp.u48;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/bubble_emitter_draw.s")
#endif
#ifdef NON_MATCHING
/* P143 */
f32 wrap_float_range(f32, f32, f32);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
void vec3_from_angles_byte(s16, s16, f32, void *);
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern f32 D_800A9180;
extern f32 D_800A9184;
extern f32 D_800A9188;
extern f32 D_800A918C;
// bubble_emitter_update: update handler (D_8008A100 slot 40) of a particle emitter effect. Optional sound / light
// probe (rail_event_add, radius 500) when +0x127 is set; +0x114 angle advances by +0x118 * dt (wrapped by
// wrap_float_range to 2048); the pulse phase byte +0x124 advances by +0x125 per tick and sets the brightness +0x126
// (192 + 63 * sin). Unless player_mask_hides_all(+0x60) says the emitter is off, the spawn accumulator +0x128 grows by
// (D_800A9180 + rand * D_800A9184) * dt and each whole unit spawns one particle (particle_spawn_ex) at a random point of
// the disc in the s16 {x, y, z, radius} at *(+0x110), with random size, life, velocity (vec3_from_angles_byte) and fade.
// Always returns 1.
/* was func_151A6BB0 */
s32 bubble_emitter_update(u8 *fx) {
    struct {
        s32 render[2];  /* 0x200005, 0x1F0600 */
        s16 u8;         /* 0x2203 */
        s16 sprite;     /* 0x19 + rand & 0xF */
        s32 uC;
        s32 u10;
        u8 color[6];    /* 0xFF */
        u8 u1A;
        u8 life;        /* 100..200 */
        u8 u1C;
        u8 u1D;         /* 0x28 */
        s16 u1E;        /* 0xC */
        s16 u20;        /* 0x15 */
        s16 u22;        /* 1 */
        f32 u24;        /* 1.0 */
        f32 size[2];
        f32 pos[3];
        f32 u3C[3];
        f32 vel[3];
        f32 fade;
        s32 u58;        /* 0xC207 */
        s32 u5C;
        s8 u60[6];      /* 6, 8, -1, -1, -1, 0 */
    } req;
    f32 *mv = (f32 *)(fx + 0x110);
    s16 *src;
    s32 r0, r1;
    f32 rf;

    if (fx[0x127] != 0) {
        rail_event_add(*(f32 *)(fx + 0x34), *(f32 *)(fx + 0x38), *(f32 *)(fx + 0x3C), 500.0f);
    }
    mv[1] += mv[2] * D_800BE9A4;
    mv[1] = wrap_float_range(mv[1], 2048.0f, 0.0f);
    fx[0x124] += fx[0x125] * D_800BE9E4;
    fx[0x126] = (u32)(angle_byte_cos(fx[0x124] - 0x40) * 63.0f + 192.0f);
    if (player_mask_hides_all(*(s32 *)(fx + 0x60)) != 0) {
        return 1;
    }
    mv[6] += (D_800A9180 + random_float() * D_800A9184) * D_800BE9A4;
    if (mv[6] > 1.0f) {
        req.u1D = 0x28;
        req.u8 = 0x2203;
        req.render[0] = 0x200005;
        req.render[1] = 0x1F0600;
        req.color[0] = 0xFF;
        req.color[1] = 0xFF;
        req.color[2] = 0xFF;
        req.color[3] = 0xFF;
        req.color[4] = 0xFF;
        req.color[5] = 0xFF;
        req.u3C[0] = 0.0f;
        req.u3C[1] = 0.0f;
        req.u3C[2] = 0.0f;
        req.uC = 0;
        req.u10 = 0;
        req.u1A = 0xFF;
        req.u1E = 0xC;
        req.u20 = 0x15;
        req.u22 = 1;
        req.u24 = 1.0f;
        req.u58 = 0xC207;
        req.u60[0] = 6;
        req.u60[1] = 8;
        req.u60[2] = -1;
        req.u60[3] = -1;
        req.u60[4] = -1;
        req.u60[5] = 0;
        do {
            r0 = random_int();
            src = *(s16 **)(fx + 0x110);
            vec2_from_angle_byte(r0 & 0xFF, random_float() * src[3], &req.pos[0], &req.pos[2]);
            src = *(s16 **)(fx + 0x110);
            req.pos[0] += src[0];
            req.pos[1] = src[1];
            req.pos[2] += src[2];
            req.sprite = (random_int() & 0xF) + 0x19;
            req.life = (random_int() % 101U) + 100;
            req.size[0] = req.size[1] = random_float() * 205.0f + 98.0f;
            r0 = random_int();
            r1 = random_int();
            rf = random_float();
            vec3_from_angles_byte(r0 & 0xFF, ((u32)r1 % 35U) - 0x40, rf * 10.0f + 10.0f, req.vel);
            req.fade = random_float() * D_800A918C + D_800A9188;
            particle_spawn_ex((s32)&req, 1, 0, 0, fx[0xC], fx[1]);
            mv[6] -= 1.0f;
        } while (mv[6] > 1.0f);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/bubble_emitter_update.s")
#endif

void sfx_emitter_stop_by_callback(s32 (*)(struct57 *, struct57 *, s32 *, s32, s32, s32, u16 *), u8 *, s32, u8 *);

/* was func_151A7068 */
void bubble_emitter_stop(u8 *arg0) {
    struct102 *temp_a0;

    (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x110))) + 0x14)) = 1;
    sfx_emitter_stop_by_callback(sfx_cb_keep_until_silent, (*(u8 **)((u8 *)arg0 + 0x110)), 0, arg0);
    temp_a0 = (*(struct102 **)((u8 *)arg0 + 0x120));
    if (temp_a0 != NULL) {
        node_destroy(temp_a0);
    }
}

/* was func_151A70C0 */
void bubble_emitter_retire(struct210 * arg0) {
    bubble_emitter_stop(arg0);
    effect3d_retire(arg0);
}

/* was func_151A70EC */
void bubble_emitter_free(struct210 * arg0) {
    bubble_emitter_stop(arg0);
    effect3d_free(arg0);
}

u8 *zone_node_find_by_key(s32);
s32 obj_send_hit();
/* was func_151A7118 */
void zone_owner_send_hit(u8 *arg0, s32 arg1) {
    s32 pad; // fakematch: unused local moves v to sp18
    struct127 *v = NULL;
    u8 *t;
    s32 a3;
    t = zone_node_find_by_key(arg1);
    if (t != NULL) {
        v = *(struct127 **)(t + 0x38);
    }
    if (v != NULL) {
        a3 = v - D_800CC2D0;
    } else {
        a3 = -1;
    }
    obj_send_hit(arg0, 0x60034, *(u16 *)(arg0 + 0x7A), a3);
}

/* was func_151A7188 */
u8 *zone_node_find_by_key(s32 arg0) {
    u8 i;
    u8 j;
    struct_eu_node *p;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (p = D_800DD280[j][(&D_800A5770)[i]]; p != NULL; p = p->next) {
                if ((*(u8 *)((u8 *)p + 0x13) == 0x2C) && (arg0 == *(s32 *)((u8 *)p + 0x28))) {
                    return (u8 *)p;
                }
            next: ; // fakematch: label at the end of the inner loop body moves the j/i increments into the exit block
            }
        }
    }
    return NULL;
}

#ifdef NON_MATCHING
/* P153 */
s32 debris_spray_spawn(void *spray, s32 arg1, u8 arg2, s32 arg3);
void cam_shake_all_players(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
void explosion_light_spawn(u8 *, u8, s32);
s32 smoke_cloud_spawn(u8 *, u8, s32);
s32 spark_shower_spawn(u8 *, f32, f32, f32, f32, u8, s32);

/* the stack blocks of object_explosion_effects (sp40 spray block for debris_spray_spawn, then the position at sp9C) */
typedef struct {
    struct {
        s16 count;        /* 0x00: 6..9 */
        u8 pad2[2];
        f32 pos[3];       /* 0x04 */
        s16 u10;          /* 0x10 */
        u8 pad12[2];
        f32 u14;          /* 0x14 */
        s16 u18[4];       /* 0x18 */
        f32 u20[12];      /* 0x20 */
        f32 u50;          /* 0x50 */
        u8 u54;           /* 0x54 */
        u8 u55;           /* 0x55 */
        s16 u56;          /* 0x56 */
        s16 u58;          /* 0x58 */
        u8 pad5A[2];
    } spray;
    f32 pos[3];           /* sp9C */
} Frame7240;

// object_explosion_effects: P153: the effect set of an exploding object at obj's position (+0x14): a spray of 6..9
// pieces (debris_spray_spawn), the flash / sparks / smoke spawners cam_shake_all_players (506, 1013, 0.000987, 5),
// explosion_light_spawn and smoke_cloud_spawn, a random-sized burst (spark_shower_spawn: size 12..16, 1.641, brightness 200..255)
// and the screen shake rumble_all_players_at (1502, 3000, 1/3000, 12, 15). The original reads the position before its
// NULL test.
/* was func_151A7240 */
void object_explosion_effects(u8 *obj, u8 arg1, s32 arg2) {
    Frame7240 f;
    f32 r;
    f32 size;

    f.pos[0] = *(f32 *) (obj + 0x14);
    f.pos[1] = *(f32 *) (obj + 0x18);
    f.pos[2] = *(f32 *) (obj + 0x1C);
    if (obj == NULL) {
        return;
    }
    f.spray.count = (random_int() & 3) + 6;
    f.spray.pos[0] = f.pos[0];
    f.spray.pos[1] = f.pos[1];
    f.spray.pos[2] = f.pos[2];
    f.spray.u14 = 60.0f;
    f.spray.u20[0] = 0.0f;
    f.spray.u20[1] = 35.0f;
    f.spray.u10 = 0x50;
    f.spray.u18[0] = 0;
    f.spray.u18[1] = 0xFF;
    f.spray.u18[2] = -0x3F;
    f.spray.u18[3] = 0x50;
    f.spray.u54 = 0;
    f.spray.u55 = 0;
    f.spray.u56 = 0x32;
    f.spray.u58 = 0x19;
    f.spray.u20[9] = -1.0f;
    f.spray.u20[10] = -1.0f;
    f.spray.u20[4] = 0.0f;
    f.spray.u20[5] = 0.0f;
    f.spray.u20[6] = 0.0f;
    f.spray.u20[2] = 10.0f;
    f.spray.u20[3] = 40.0f;
    f.spray.u20[7] = 0.2f;
    f.spray.u20[8] = 0.5f;
    f.spray.u20[11] = -2.0f;
    f.spray.u50 = 4.0f;
    debris_spray_spawn(&f.spray, 0, arg1, arg2);
    cam_shake_all_players((u8 *) f.pos, 506.0f, 1013.0f, 0.0009871669f, 5, arg1, arg2);
    explosion_light_spawn((u8 *) f.pos, arg1, arg2);
    smoke_cloud_spawn((u8 *) f.pos, arg1, arg2);
    r = random_float();
    size = r * 4.0f + 12.0f;
    spark_shower_spawn((u8 *) f.pos, size, 1.6409999f, (f32) ((u32) random_int() % 56 + 200), 0.0f, arg1, arg2);
    rumble_all_players_at((struct17 *) f.pos, 1502.0f, 3000.0f, 0.00033333333f, 0xC, 0xF, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/object_explosion_effects.s")
#endif
