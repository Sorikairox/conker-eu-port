#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150E4740 */
void camera_calc_point_ahead(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 pad; // fakematch: frame slot 0x30 (unknown named local)
    f32 vy;
    f32 vz;
    f32 s;
    f32 a;
    f32 c;
    f32 vx;
    s16 *p;

    x = D_800DBFF0->unk2F8;
    y = D_800DBFF0->unk2FC;
    z = D_800DBFF0->unk300;
    a = D_800DBFF0->unk398;
    s = sinf(a);
    c = cosf(a);
    vy = 500.0f * s;
    vz = -500.0f * c;
    vx = 0.0f;
    a = D_800DBFF0->unk3A0;
    s = sinf(a);
    c = cosf(a);
    x += (vx + (vz * s));
    z += ((vz * c) - vx);
    y += vy;
    p = (s16 *)D_800D9E10;
    p[0] = x;
    p[2] = z;
    p[1] = y;
}

#ifdef NON_MATCHING
s32 impact_effect_spawn(f32, f32, f32, s32, s32, s32, s32);
s32 floor_flags_surface_type(s32);
s32 collision_level_nearest_height(s32, s32, s32, s32 *);
extern s32 D_800DC26C;

/* was func_150E4878 */
void impact_scatter_random(s32 arg0) {
    struct {
        s32 u58;
        u8 pad5C[0xC];
        s32 u68;
        u8 pad6C[0x4];
        s32 u70;
    } sp;
    s32 temp_a2;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;

    sp.u58 = 0;
    var_s3 = 0;
    sp.u70 = (s32) (*(s16 *)((u8 *)D_800D9E10 + 0));
    sp.u68 = (s32) (*(s16 *)((u8 *)D_800D9E10 + 4));
    if (arg0 > 0) {
        do {
            temp_s0 = (random_int() % 500) + sp.u70;
            temp_a2 = (random_int() % 500) + sp.u68;
            temp_v0 = collision_level_nearest_height(temp_s0, 0x2710, temp_a2, &sp.u58);
            if (((f32) temp_v0 != -10000.0f) && (sp.u58 != 0)) {
                temp_lo = (s32) (sp.u58 - D_800DC26C) / 12;
                if ((temp_lo >= 0) && (temp_lo < D_800DBE4C)) {
                    temp_v0_2 = floor_flags_surface_type(*(s32 *)(D_800DBE5C + (temp_lo * 4)));
                    if (temp_v0_2 != 0) {
                        impact_effect_spawn((f32) temp_s0, (f32) temp_v0, (f32) temp_a2, 0, temp_v0_2, sp.u58, 0xFF);
                    }
                }
            }
            var_s3 += 1;
        } while (var_s3 != arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_111F50/impact_scatter_random.s")
#endif
/* was func_150E4A94 */
void impact_scatter_ahead(s32 arg0) {
    camera_calc_point_ahead();
    impact_scatter_random(arg0 / 30);
}
