#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct { u8 a[3]; } Tri3;
typedef struct { u8 pad[0x14]; u8 u14; u8 pad2[0x1F]; } S34;
extern Tri3 D_80088D24;

/* was func_150DFE40 */
s32 level_part_is_active(s32 arg0) {
    Tri3 t = D_80088D24;

    if (((S34 *)D_800D34B8)[t.a[arg0]].u14 != 0) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
void level_anim_frame_counter_tick(s32 arg0, s32 arg1);
void trigger_set_disabled(s32, s32);
void trigger_set_position(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
extern u8 D_800D9D70[3];

// level_lights_and_scroll_update: per-frame level handler (table D_8008D0C0); does nothing unless arg0 is 0. Steps
// the D_800DD835 counter (level_anim_frame_counter_tick(5, 4)), places light slots 3 / 4 at objects 6 / 7 (200 above them; a slot
// whose object is missing is switched off with trigger_set_disabled(slot, 1)). Then for the three parts i (segment i + 2):
// the fade D_800D9D70[i] rises by D_800BE9E4 up to 0x60 while level_part_is_active(i) is on (else 0), and the first
// G_SETTILESIZE after the part's G_SETTIMG of segment address (i + 2) << 24 in the level display list D_800B0E00[0]
// gets its low coordinate advanced by fade / 16 * D_800BE9E4 (on) or both coordinates set to 2 (off).
/* was func_150DFEA0 */
void level_lights_and_scroll_update(s32 arg0) {
    u32 *dl;
    u8 *fade;
    u8 *obj;
    s32 i;
    s32 j;
    s32 on;
    s32 lo;
    s32 hi;
    s32 slot;
    s32 kind;

    if (arg0 != 0) {
        return;
    }
    level_anim_frame_counter_tick(5, 4);
    kind = 6;
    slot = 3;
    for (i = 0; i < 2; i++) {
        obj = (u8 *) obj_find_by_setup_id(kind);
        kind = 7;
        if (obj != NULL) {
            trigger_set_disabled(slot, 0);
            trigger_set_position(slot, (s32) *(f32 *) (obj + 0x14), (s32) (*(f32 *) (obj + 0x18) + 200.0f),
                          (s32) *(f32 *) (obj + 0x1C));
        } else {
            trigger_set_disabled(slot, 1);
        }
        slot = 4;
    }
    dl = (u32 *) D_800B0E00[0];
    fade = D_800D9D70;
    for (i = 0; i < 3; i++, fade++) {
        on = level_part_is_active(i);
        if (on) {
            if (*fade < 0x60) {
                *fade += D_800BE9E4;
                if (*fade > 0x60) {
                    *fade = 0x60;
                }
            }
        } else {
            *fade = 0;
        }
        /* the part's G_SETTIMG (0xFD) of segment i + 2; stop at G_ENDDL (0xDF) */
        j = 0;
        while (TRUE) {
            while ((s8) (dl[j * 2] >> 24) != (s8) 0xFD && (s8) (dl[j * 2] >> 24) != (s8) 0xDF) {
                j++;
            }
            if ((s8) (dl[j * 2] >> 24) == (s8) 0xDF) {
                j = -1;
                break;
            }
            if (dl[j * 2 + 1] == (u32) ((i << 24) + 0x2000000)) {
                break;
            }
            j++;
        }
        if (j == -1) {
            continue;
        }
        /* the next G_SETTILESIZE (0xF2) */
        do {
            j++;
        } while ((s8) (dl[j * 2] >> 24) != (s8) 0xF2);
        if (on) {
            hi = (dl[j * 2] >> 12) & 0xFFF;
            lo = (dl[j * 2] & 0xFFF) + (*fade >> 4) * D_800BE9E4;
        } else {
            lo = 2;
            hi = 2;
        }
        dl[j * 2] = 0xF2000000 | ((hi & 0xFFF) << 12) | (lo & 0xFFF);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/level_lights_and_scroll_update.s")
#endif

s32 texture_cache_lookup(s32, s32 *, s32, s32);
extern s32 D_800906D4[];
extern u8 D_800DD835;

/* was func_150E0150 */
Gfx *level_parts_set_segments(Gfx *gfx) {
    s32 a;
    s32 sp48[3];
    s32 k;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (level_part_is_active(i)) {
            k = D_800DD835;
            a = D_800906D4[k + 9];
        } else {
            a = D_800906D4[8];
        }
        a = texture_cache_lookup(a, sp48, 3, 0);
        gSPSegment(gfx++, i + 2, a);
    }
    return gfx;
}

typedef struct {
    u8 pad0[4];
    f32 u4;
    u8 pad8[0x5C];
    f32 u64;
    u8 pad68[0x14];
    f32 u7C;
} SE0228;

/* was func_150E0228 */
void obj_bob_update(SE0228 *arg0) {
    f32 t;
    f32 d;
    f32 m;

    m = 0.55f;
    d = arg0->u64 * D_800BE9E4;
    arg0->u4 += d;
    if (arg0->u4 < 11.0f) {
        t = m;
        arg0->u7C = t;
    } else if (arg0->u4 > 55.0f) {
        t = -m;
        arg0->u7C = t;
    } else {
        t = arg0->u7C;
    }
    if (arg0->u64 < t) {
        arg0->u64 += 0.05f;
        if (t < arg0->u64) {
            arg0->u64 = t;
        }
    } else if (t < arg0->u64) {
        arg0->u64 -= 0.05f;
        if (arg0->u64 < t) {
            arg0->u64 = t;
        }
    }
}

/* was func_150E0324 */
void obj_pin_root_height(u8 *arg0) {
    f32 *temp_v0 = (f32 *)(*(u8 **)(arg0 + 0x1D4) + 0x40);
    temp_v0[0x30 / 4] = *(f32 *)(arg0 + 0x14);
    temp_v0[0x34 / 4] = 2706.0f;
    temp_v0[0x38 / 4] = *(f32 *)(arg0 + 0x1C);
}

typedef struct { u32 w0; u32 w1; } G8;

/* was func_150E0350 */
s32 mat_hit_flash_update(u8 *arg0, u8 *arg1) {
    f32 s;
    G8 *g;
    s32 i;
    s32 t;
    u32 w;

    if (*(s32 *)(arg1 + 0x2EC) != 0) {
        arg0[0x13] = 2;
        *(f32 *)(arg1 + 0x2D8) -= D_800BE9A4;
        if (*(f32 *)(arg1 + 0x2D8) < 0.0f) {
            *(s32 *)(arg1 + 0x2EC) = 0;
            return 1;
        }
        s = 1.0f - *(f32 *)(arg1 + 0x2D8) * *(f32 *)(arg1 + 0x2DC);
    } else {
        s = 0.0f;
        arg0[0x13] = 0;
    }
    g = **(G8 ***)(arg0 + 0x24);
    if (g != NULL) {
        i = 0;
        while (*(s8 *)&g[i] != -0xE) {
            i++;
        }
        w = g[i].w0;
        t = 2 - (s32)((w >> 12) & 0xFFF) / 3;
        while (t < 0) {
            t += 0x40;
        }
        g[i].w0 = (((s32)(500.0f * s + 2.0f) & 0xFFF) << 12) | 0xF2000000 | (t & 0xFFF);
    }
    return 0;
}

#ifdef NON_MATCHING
s32 object_arc_to_surface_spawn(u8 *, s16, s16, s16, s32, f32, f32, s32, s32, s8 *, s32, s32);
void obj_angle_point_effect(u8 *, s16, s16, u8, s32);

/* was func_150E047C */
void fx_flicker_lights_update(u8 *arg0) {
    struct {
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        u8 pad90[0x4];
        s32 u94;
        s32 u98;
        s32 u9C;
        s8 uA0;
        s8 uA1;
        s16 uA2;
        s8 uA4;
        u8 padA5[0x3];
        u8 * uA8;
    } sp;
    u8 *sp78;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_s3;
    s8 var_s1;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_t6 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_v0 = arg0 + 0x28;
    sp.uA8 = temp_t6;
    if (((*(s32 *)((u8 *)temp_t6 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_t6 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    (*(s16 *)((u8 *)temp_v0 + 6)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 6)) - D_800BE9E4);
    sp78 = temp_v0;
    if ((*(s16 *)((u8 *)temp_v0 + 6)) < 0) {
        sp.u94 = (s32) (*(f32 *)((u8 *)sp.uA8 + 0x14));
        sp.u98 = (s32) (*(f32 *)((u8 *)sp.uA8 + 0x18));
        sp.uA0 = 3;
        sp.uA1 = -1;
        sp78 = temp_v0;
        sp.u9C = (s32) (*(f32 *)((u8 *)sp.uA8 + 0x1C));
        sp.uA2 = (random_int() % 11U) + 5;
        sp.uA4 = 0;
        light_create_with_ctrl((Header *) &sp.uA0, (Header2 *) &sp.u94, (random_int() % 121U) + 0x32, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(s16 *)((u8 *)sp78 + 6)) = (s16) ((random_int() % 81U) + 0x45);
    }
    (*(s16 *)((u8 *)sp78 + 8)) = (s16) ((*(s16 *)((u8 *)sp78 + 8)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)sp78 + 8)) < 0) {
        var_s1 = (random_int() % 3U) + 2;
        do {
            sp.u8C = 0xAE;
            sp.u8D = 0xD2;
            sp.u8E = 0xFF;
            sp.u8F = (random_int() % 61U) + 0x96;
            temp_s3 = random_int();
            temp_s0 = random_int();
            temp_s2 = random_int();
            object_arc_to_surface_spawn(sp.uA8, (s16) (temp_s3 & 0xFF), (s16) (((u32) temp_s0 % 129U) - 0x3F), (s16) (((u32) temp_s2 % 21U) + 0xA), 4, 40.0f, (random_float() * 20.0f) + 25.0f, 0, 2, &sp.u8C, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            var_s1 -= 1;
        } while (var_s1 > 0);
        (*(s16 *)((u8 *)sp78 + 8)) = (s16) ((random_int() % 141U) + 0x19);
    }
    (*(s16 *)((u8 *)sp78 + 0xA)) = (s16) ((*(s16 *)((u8 *)sp78 + 0xA)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)sp78 + 0xA)) < 0) {
        temp_s0_2 = random_int();
        obj_angle_point_effect(sp.uA8, (s16) (temp_s0_2 & 0xFF), (s16) ((random_int() & 0x7F) - 0x40), (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(s16 *)((u8 *)sp78 + 0xA)) = (s16) ((random_int() % 26U) + 0xF);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/fx_flicker_lights_update.s")
#endif
/* was func_150E0840 */
void effect_attach_to_obj(u8 *arg0, s32 arg1, u8 arg2) {
    effect_node_link_message(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

/* was func_150E0880 */
void water_effect_start_once(void) {
    if (D_80088D20 == 0) {
        light_group_set_disabled(6, 0);
        water_effect_spawn();
        D_80088D20 = 1;
    }
}

typedef struct { f32 x, y, z; } VecE08C8;
u8 *emitter_trail_spawn(void *, s32, u8, s32);

/* was func_150E08C8 */
void obj_emitter_trail_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u0;
        s32 u4;
        u8 u8;
        u8 pad9[3];
        u8 *uC;
        s8 u10;
        u8 pad11[3];
        VecE08C8 u14;
        f32 u20;
        f32 u24;
        s16 u28;
        u8 u2A;
        u8 u2B;
        s8 u2C;
        s8 u2D;
    } sp;

    sp.u0 = 0;
    sp.u4 = 0;
    sp.u8 = arg0[0x3B];
    sp.uC = arg0;
    sp.u10 = 0;
    sp.u14 = *(VecE08C8 *)D_800A5860;
    sp.u28 = 0x12C;
    sp.u2A = 0x1B;
    sp.u2B = 0xB;
    sp.u2C = -1;
    sp.u2D = 0;
    sp.u20 = 10.900001f;
    sp.u24 = 0.23121f;
    emitter_trail_spawn(&sp, 0, arg1, arg2);
}

void vec3_from_angles_byte(s16, s16, f32, void *);
#ifdef NON_MATCHING
s32 particle_puff_spawn(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */
#else
s32 particle_puff_spawn(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif

/* was func_150E0978 */
void fx_debris_spray_vel(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    vec3_from_angles_byte((s16) (random_int() & 0xFF), (s16) (((u32) random_int() % 65U) - 0x20), random_float() * 5.87f, &sp6C[3]);
    temp_f2 = (random_float() * 0.16900001f) + 0.186f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
#ifdef NON_MATCHING
    particle_puff_spawn(&sp6C[6], sp6C, &sp6C[3], 0.986891f, (random_float() * 0.23f) + -0.337f, (random_float() * 200.0f) + 150.0f, ((u32) random_int() % 26U) + 0x28, (random_int() % 201U) + 0x37, 0x1E, 0x14, 0, -1, 0x34, 0x35, 0x34, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1))); /* P95: float literal (asm passes the bits 0x3F7CA4E3) */
#else
    particle_puff_spawn(&sp6C[6], sp6C, &sp6C[3], 0x3F7CA4E3, (random_float() * 0.23f) + -0.337f, (random_float() * 200.0f) + 150.0f, ((u32) random_int() % 26U) + 0x28, (random_int() % 201U) + 0x37, 0x1E, 0x14, 0, -1, 0x34, 0x35, 0x34, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
#endif
}

/* was func_150E0B78 */
void fade_by_camera_distance(u8 *arg0)
{
  f32 temp_f0;
  f32 temp_f12;
  f32 temp_f14;
  f32 temp_f2;
  s32 var_v0;
  temp_f2 = D_800DBFF0->unk300 - ((f32) (*((s16 *) (((u8 *) arg0) + 0x14))));
  temp_f12 = D_800DBFF0->unk2F8 - ((f32) (*((s16 *) (((u8 *) arg0) + 0x10))));
  temp_f14 = D_800DBFF0->unk2FC - ((f32) (*((s16 *) (((u8 *) arg0) + 0x12))));
  temp_f0 = sqrtf((temp_f2 * temp_f2) + ((temp_f12 * temp_f12) + (temp_f14 * temp_f14)));
  if (temp_f0 <= 2570.0f)
  {
    var_v0 = 0xFF;
  }
  else
    if (temp_f0 >= 3850.0f)
  {
    var_v0 = 0;
  }
  else
  {
    temp_f14 = 2570.0f; // fakematch: temp reuse keeps 3850 - 2570 at run time (permuter)
    var_v0 = (s32) (255.0f - (((temp_f0 - 2570.0f) * (1.0f / (3850.0f - temp_f14))) * 255.f));
  }
  *((s8 *) (((u8 *) arg0) + 0x8A)) = (s8) var_v0;
}

#ifdef NON_MATCHING /* P262: the C definition's exact types (game_eu_1306B0) */
void *attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s16, u8, f32, u8 *, u8, s32, s16, u8, s32);
#else
s32 attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, s32 *, s32, s32, s32, s32, s32);
#endif
s32 mtx_transform_points(f32 **, s32 **, s32, s32);
extern u8 D_80088D28;
#ifdef NON_MATCHING
/* the rodata of level_lights_and_scroll_update.s (D_800A1340 / D_800A1358), gone from the NM build: local copies */
static const f32 D_800A1340[2][3] = { { 17.0f, 0.0f, 90.0f }, { -17.0f, 0.0f, 90.0f } };
static const f32 D_800A1358[2][3] = { { 17.0f, 0.0f, 150.0f }, { -17.0f, 0.0f, 150.0f } };
#else
extern f32 D_800A1340[][3];
extern f32 D_800A1358[][3];
#endif

/* was func_150E0C58 */
void obj_joint_spark_spray(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    s32 sp64[3];
    f32 sp58[3];
    f32 *sp54;
    s32 *sp50;

    if (*(s32 *)(arg0 + 0x1D4) == 0) {
        return;
    }
        sp54 = D_800A1340[arg1];
        sp50 = sp64;
        mtx_transform_points(&sp54, &sp50, *(s32 *)(arg0 + 0x1D4) + (D_80088D28 << 6), 1);
        sp58[1] = (random_float() * 1) + 2.0f;
        sp58[0] = (random_float() * 14.0f) + 28.0f;
        attached_particle_spawn(arg0, D_80088D28, (f32 *)((u8 *)D_800A1340 + arg1 * 12), (f32 *)((u8 *)D_800A1358 + arg1 * 12), sp58, (random_int() % 3U) + 4, (random_int() % 156U) + 0x64, (random_float() * 300.0f) + 400.0f, (u8 *)sp64, 0xFF, 0, -1, arg2, arg3);
}
