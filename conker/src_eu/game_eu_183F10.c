#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_render_mode_pairs[]; /* was D_800A4EA8 */

void anim_model_fx_free_lights(u8 *arg0);


/* was func_15156700 */
s32 line_fx_spawn(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    struct {
        s32 u30;
        u8 pad34[0x10];
        u8 * u44;
    } sp;
    s32 temp_t6;
    s32 var_a0;
    u8 *temp_v0;

    temp_t6 = arg1 & 0xFF;
    if (temp_t6 != 0) {
        var_a0 = 0x53;
        if (temp_t6 != 1) {
            var_a0 = 0x2C;
        }
    } else {
        var_a0 = 0x2C;
    }
    temp_v0 = node_alloc(var_a0, arg4, arg2 + 0x98, 1, (u8) (s32) arg3, 1U);
    if (temp_v0 == NULL) {
        return 0;
    }
    (*(s16 *)((u8 *)temp_v0 + 0x5E)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x64)) = (u8) (*(u8 *)((u8 *)arg0 + 0x24));
    (*(u8 *)((u8 *)temp_v0 + 0x65)) = (u8) (*(u8 *)((u8 *)arg0 + 0x25));
    (*(u8 *)((u8 *)temp_v0 + 0x66)) = (u8) (*(u8 *)((u8 *)arg0 + 0x26));
    (*(s16 *)((u8 *)temp_v0 + 0x60)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x62)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x6E)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x67)) = (u8) (*(u8 *)((u8 *)arg0 + 0x27));
    (*(u8 *)((u8 *)temp_v0 + 0x74)) = (u8) (*(u8 *)((u8 *)arg0 + 0x20));
    (*(u8 *)((u8 *)temp_v0 + 0x75)) = (u8) (*(u8 *)((u8 *)arg0 + 0x21));
    (*(u8 *)((u8 *)temp_v0 + 0x76)) = (u8) (*(u8 *)((u8 *)arg0 + 0x22));
    (*(s16 *)((u8 *)temp_v0 + 0x7E)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x77)) = (u8) (*(u8 *)((u8 *)arg0 + 0x23));
    (*(u8 *)((u8 *)temp_v0 + 0x84)) = (u8) (*(u8 *)((u8 *)arg0 + 0x20));
    (*(u8 *)((u8 *)temp_v0 + 0x85)) = (u8) (*(u8 *)((u8 *)arg0 + 0x21));
    (*(u8 *)((u8 *)temp_v0 + 0x86)) = (u8) (*(u8 *)((u8 *)arg0 + 0x22));
    (*(u8 *)((u8 *)temp_v0 + 0x87)) = (u8) (*(u8 *)((u8 *)arg0 + 0x23));
    (*(s32 *)((u8 *)(&sp.u30) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u30) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u30) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    (*(s32 *)((u8 *)temp_v0 + 0x28)) = (s32) (*(s32 *)((u8 *)(&sp.u30) + 0));
    (*(s32 *)((u8 *)temp_v0 + 0x2C)) = (s32) (*(s32 *)((u8 *)(&sp.u30) + 4));
    (*(s32 *)((u8 *)temp_v0 + 0x30)) = (s32) (*(s32 *)((u8 *)(&sp.u30) + 8));
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = (s32) (*(s32 *)((u8 *)(&sp.u30) + 0));
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = (s32) (*(s32 *)((u8 *)(&sp.u30) + 4));
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = (s32) (*(s32 *)((u8 *)(&sp.u30) + 8));
    (*(f32 *)((u8 *)temp_v0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xC)) * (*(f32 *)((u8 *)arg0 + 0x18)));
    (*(f32 *)((u8 *)temp_v0 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) * (*(f32 *)((u8 *)arg0 + 0x18)));
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) * (*(f32 *)((u8 *)arg0 + 0x18)));
    (*(f32 *)((u8 *)temp_v0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xC)) * (*(f32 *)((u8 *)arg0 + 0x1C)));
    (*(f32 *)((u8 *)temp_v0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) * (*(f32 *)((u8 *)arg0 + 0x1C)));
    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) * (*(f32 *)((u8 *)arg0 + 0x1C)));
    (*(u8 *)((u8 *)temp_v0 + 0x40)) = (u8) (*(u8 *)((u8 *)arg0 + 0x28));
    (*(s16 *)((u8 *)temp_v0 + 0x42)) = (s16) (*(s16 *)((u8 *)arg0 + 0x2A));
    (*(u16 *)((u8 *)temp_v0 + 0x44)) = (u16) (*(u16 *)((u8 *)arg0 + 0x2C));
    (*(f32 *)((u8 *)temp_v0 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x30));
    (*(u8 *)((u8 *)temp_v0 + 0x4C)) = (u8) (*(u8 *)((u8 *)arg0 + 0x34));
    (*(s16 *)((u8 *)temp_v0 + 0x4E)) = (s16) (*(s16 *)((u8 *)arg0 + 0x36));
    (*(s16 *)((u8 *)temp_v0 + 0x50)) = (s16) (*(s16 *)((u8 *)arg0 + 0x38));
    sp.u44 = temp_v0;
    bzero(temp_v0 + 0x88, 0x10);
    return (s32) sp.u44;
}
s32 line_fx_spawn(s32, u8, s32, u8, s32);
/* was func_151568F8 */
void line_fx_spawn_default(s32 arg0, u8 arg1, s32 arg2) {
    line_fx_spawn(arg0, arg1, arg2, 0xFF, 0);
}

/* was func_15156928 */
void line_fx_update(struct102 *arg0p) {
    u8 *arg0 = (u8 *)arg0p;
    s32 done;
    s16 t;

    done = 0;
    if (arg0[0x40] & 1) {
        *(s16 *)(arg0 + 0x42) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x42) < 0) {
            done = 1;
        }
    }
    if (!done) {
        *(f32 *)(arg0 + 0x10) += *(f32 *)(arg0 + 0x1C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x14) += *(f32 *)(arg0 + 0x20) * D_800BE9A4;
        *(f32 *)(arg0 + 0x18) += *(f32 *)(arg0 + 0x24) * D_800BE9A4;
        *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x34) * D_800BE9A4;
        *(f32 *)(arg0 + 0x2C) += *(f32 *)(arg0 + 0x38) * D_800BE9A4;
        *(f32 *)(arg0 + 0x30) += *(f32 *)(arg0 + 0x3C) * D_800BE9A4;
        if (arg0[0x40] & 8) {
            if (*(s16 *)(arg0 + 0x42) < *(s16 *)(arg0 + 0x4E)) {
                t = *(s16 *)(arg0 + 0x50) * *(s16 *)(arg0 + 0x42);
                if (t < arg0[0x4C]) {
                    arg0[0x4C] = t;
                }
            }
        }
    }
    if (done) {
        node_destroy(arg0p);
    }
}

s32 gfx_set_combine_mode(s32, u8, s8 *);
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear);
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
s32 gfx_prim_color_cached(s32, s32, s32, s32, s32, s32, s32, s8 *);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);

/* was func_15156A68 */
u8 *line_fx_draw(s32 arg0, u8 *arg1, s16 arg2) {
    struct {
        u8 u59;
        u8 u5A;
        u8 u5B;
        u8 * u5C;
        u8 pad60[0x7];
        s8 u67;
        f32 u68;
        f32 * u6C;
        u8 pad70[0x8];
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        u8 pad88[0x4];
        f32 u8C;
        f32 u90;
    } sp;
    u8 *sp48;
    s32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f16;
    f32 var_f2;
    s16 temp_t3;
    s32 temp_a1;
    s32 var_v1;
    u16 temp_t6;
    u8 *temp_s1;
    u8 *temp_s1_2;
    u8 *temp_v1;
    u8 *temp_v1_2;

    vtx_slot_buffer_get(arg1 + 0x88, arg2, 0x30, &sp.u5C, &sp.u59);
    if (sp.u59 != 0) {
        temp_a1 = arg1 + 0x58;
        temp_v1 = arg1 + (arg2 * 4);
        sp44 = temp_a1;
        sp48 = temp_v1;
        memcpy((*(s32 *)((u8 *)temp_v1 + 0x88)), temp_a1, 0x30);
        memcpy((*(s32 *)((u8 *)temp_v1 + 0x88)) + 0x30, temp_a1, 0x30);
    }
    sp.u6C = &D_800DBFF0[arg2].unk2F8;
    sp.u67 = 1;
    temp_t6 = (*(u16 *)((u8 *)arg1 + 0x44));
    var_v1 = 0;
    temp_t3 = (*(u8 *)((u8 *)arg1 + 0x40)) & 6;
    sp.u5A = (u8) ((s32) (temp_t6 & 0xFF00) >> 8);
    sp.u5B = (u8) temp_t6;
    if (temp_t3 & 2) {
        var_v1 = 0x200;
    }
    if (temp_t3 & 4) {
        var_v1 |= 0x400;
    }
    temp_v1_2 = (sp.u5B * 8) + ((u8 *)&g_render_mode_pairs);
    temp_f12 = (*(f32 *)((u8 *)arg1 + 0x14));
    temp_f2 = (*(f32 *)((u8 *)arg1 + 0x10));
    temp_f14 = (*(f32 *)((u8 *)arg1 + 0x28));
    temp_s1_2 = gfx_other_mode_cached(gfx_set_combine_mode(gfx_prim_color_cached(gfx_env_color_cached(gfx_geometry_mode_cached(arg0, var_v1 | 5 | 0x200000, 0x1F0600), 0, 0, 0, (s32) (*(u8 *)((u8 *)arg1 + 0x4C)), &sp.u67), 0, 0, 0, 0, 0, 0, &sp.u67), sp.u5A, &sp.u67), 0x82CA0, (*(s32 *)((u8 *)temp_v1_2 + 4)) | (*(s32 *)((u8 *)temp_v1_2 + 0)), &sp.u67);
    temp_f16 = temp_f2 - temp_f14;
    sp.u8C = temp_f12 - (*(f32 *)((u8 *)arg1 + 0x2C));
    temp_f0 = (*(f32 *)((u8 *)arg1 + 0x18));
    temp_f10 = temp_f0 - (*(f32 *)((u8 *)arg1 + 0x30));
    sp.u90 = temp_f10;
    sp.u7C = temp_f2 - (*(f32 *)((u8 *)sp.u6C + 0));
    sp.u80 = temp_f12 - (*(f32 *)((u8 *)sp.u6C + 4));
    temp_f8 = temp_f0 - (*(f32 *)((u8 *)sp.u6C + 8));
    sp30 = sp.u80;
    sp3C = temp_f14;
    sp.u84 = temp_f8;
    temp_f14_2 = (sp.u8C * temp_f8) - (sp.u80 * temp_f10);
    temp_f18 = (temp_f10 * sp.u7C) - (temp_f8 * temp_f16);
    temp_f2_2 = (temp_f16 * sp30) - (sp.u7C * sp.u8C);
    sp40 = temp_f2_2;
    temp_f0_2 = (temp_f14_2 * temp_f14_2) + (temp_f18 * temp_f18) + (temp_f2_2 * temp_f2_2);
    sp.u68 = temp_f0_2;
    if (temp_f0_2 == 0.0f) {
        var_f2 = 0.0f;
        var_f12 = 0.0f;
        var_f16 = 0.0f;
    } else {
        temp_f2_3 = (*(f32 *)((u8 *)arg1 + 0x48)) / sqrtf(temp_f0_2);
        var_f12 = temp_f14_2 * temp_f2_3;
        var_f16 = temp_f18 * temp_f2_3;
        temp_f10_2 = sp40 * temp_f2_3;
        sp.u78 = temp_f10_2;
        var_f2 = temp_f10_2;
    }
    (*(s16 *)((u8 *)sp.u5C + 0)) = (s16) (s32) sp3C;
    (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x2C));
    (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (*(f32 *)((u8 *)arg1 + 0x30));
    (*(s16 *)((u8 *)sp.u5C + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)arg1 + 0x10)) + var_f12);
    (*(s16 *)((u8 *)sp.u5C + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg1 + 0x14)) + var_f16);
    (*(s16 *)((u8 *)sp.u5C + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg1 + 0x18)) + var_f2);
    (*(s16 *)((u8 *)sp.u5C + 0x20)) = (s16) (s32) ((*(f32 *)((u8 *)arg1 + 0x10)) - var_f12);
    (*(s16 *)((u8 *)sp.u5C + 0x22)) = (s16) (s32) ((*(f32 *)((u8 *)arg1 + 0x14)) - var_f16);
    (*(s16 *)((u8 *)sp.u5C + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg1 + 0x18)) - var_f2);
    (*(s32 *)((u8 *)temp_s1_2 + 0)) = 0x01003006;
    temp_s1 = temp_s1_2 + 8;
    (*(u8 **)((u8 *)temp_s1_2 + 4)) = sp.u5C;
    (*(s32 *)((u8 *)temp_s1 + 0)) = 0x05000204;
    (*(s32 *)((u8 *)temp_s1 + 4)) = 0;
    return temp_s1 + 8;
}
s32 particle_spawn_basic(void *, s32, s32, u8, s32);
typedef struct { f32 x, y, z; } V3_6E68;
typedef struct { s32 a, b; } V2_6E68;
/* was func_15156E68 */
void line_spark_burst_at(u8 *arg0, u8 arg1) {
    struct {
        s16 u98;
        s16 u9A;
        V3_6E68 u9C;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        u8 uC0;
        u8 uC1;
        u8 uC2;
        u8 uC3;
        u8 uC4;
        u8 uC5;
        u8 uC6;
        u8 uC7;
        u8 uC8;
        u8 padC9[0x1];
        s16 uCA;
        s16 uCC;
        u16 uCE;
        f32 uD0;
        f32 uD4;
        u8 uD8;
        u8 uD9;
        s16 uDA;
        s16 uDC;
        u8 uDE;
        u8 padDF[0x1];
    } B;
    struct {
        s32 u28;
        s32 u2C;
        u16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        u8 u3C;
        u8 u3D;
        u8 u3E;
        u8 u3F;
        u8 u40;
        u8 u41;
        u8 u42;
        u8 u43;
        u8 u44;
        u8 u45;
        s16 u46;
        s16 u48;
        s16 u4A;
        f32 u4C;
        V2_6E68 u50;
        V3_6E68 u58;
        u8 pad64[0xC];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s32 u80;
        u8 pad84[0x4];
        u8 u88;
        u8 u89;
        s8 u8A;
        s8 u8B;
        u8 pad8C[0xC];
    } sp;

    B.u98 = *(s16 *)(arg0 + 0xC);
    B.u9A = *(s16 *)(arg0 + 0xE);
    B.u9C = *(V3_6E68 *)(arg0 + 0x0);
    B.uA8 = *(s16 *)(arg0 + 0x10);
    B.uAC = *(s16 *)(arg0 + 0x14);
    B.uAA = *(s16 *)(arg0 + 0x12);
    B.uAE = *(s16 *)(arg0 + 0x16);
    B.uB0 = *(f32 *)(arg0 + 0x18);
    B.uB4 = *(f32 *)(arg0 + 0x1C);
    B.uB8 = *(f32 *)(arg0 + 0x20);
    B.uBC = *(f32 *)(arg0 + 0x24);
    B.uC0 = *(u8 *)(arg0 + 0x28);
    B.uC1 = *(u8 *)(arg0 + 0x29);
    B.uC2 = *(u8 *)(arg0 + 0x2A);
    B.uC3 = *(u8 *)(arg0 + 0x2B);
    B.uC4 = *(u8 *)(arg0 + 0x2C);
    B.uC5 = *(u8 *)(arg0 + 0x2D);
    B.uC6 = *(u8 *)(arg0 + 0x2E);
    B.uC7 = *(u8 *)(arg0 + 0x2F);
    B.uC8 = *(u8 *)(arg0 + 0x30);
    B.uCA = *(s16 *)(arg0 + 0x32);
    B.uCC = *(s16 *)(arg0 + 0x34);
    B.uCE = *(u16 *)(arg0 + 0x36);
    B.uD0 = *(f32 *)(arg0 + 0x38);
    B.uD4 = *(f32 *)(arg0 + 0x3C);
    B.uD8 = *(u8 *)(arg0 + 0x40);
    B.uD9 = *(u8 *)(arg0 + 0x41);
    B.uDA = *(s16 *)(arg0 + 0x42);
    B.uDC = *(s16 *)(arg0 + 0x44);
    B.uDE = *(u8 *)(arg0 + 0x46);
    emit_line_sparks_by_angles(&B, arg1);
    sp.u45 = *(u8 *)(arg0 + 0x47);
    sp.u30 = *(u16 *)(arg0 + 0x48);
    sp.u2C = *(s32 *)(arg0 + 0x50);
    sp.u28 = *(s32 *)(arg0 + 0x4C);
    sp.u34 = *(s32 *)(arg0 + 0x58);
    sp.u38 = *(s32 *)(arg0 + 0x5C);
    sp.u3C = *(u8 *)(arg0 + 0x60);
    sp.u3D = *(u8 *)(arg0 + 0x61);
    sp.u3E = *(u8 *)(arg0 + 0x62);
    sp.u3F = *(u8 *)(arg0 + 0x63);
    sp.u40 = *(u8 *)(arg0 + 0x64);
    sp.u41 = *(u8 *)(arg0 + 0x65);
    sp.u42 = *(u8 *)(arg0 + 0x66);
    sp.u58 = *(V3_6E68 *)(arg0 + 0x0);
    sp.u80 = *(s32 *)(arg0 + 0x80);
    sp.u43 = *(u8 *)(arg0 + 0x67);
    sp.u44 = *(u8 *)(arg0 + 0x68);
    sp.u8A = *(s8 *)(arg0 + 0x86);
    sp.u8B = *(s8 *)(arg0 + 0x87);
    sp.u46 = *(s16 *)(arg0 + 0x74);
    sp.u48 = *(s16 *)(arg0 + 0x76);
    sp.u88 = *(u8 *)(arg0 + 0x84);
    sp.u89 = *(u8 *)(arg0 + 0x85);
    sp.u4A = *(s16 *)(arg0 + 0x78);
    sp.u4C = *(f32 *)(arg0 + 0x7C);
    sp.u32 = *(s16 *)(arg0 + 0x54);
    sp.u50 = *(V2_6E68 *)(arg0 + 0x6C);
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    particle_spawn_basic(&sp, arg0[0x88], 0, arg1, 0);
}

// spark_point_flash_update: P256: counts the emitter `obj`'s timer (s16 +0x2C) down by the frame step D_800BE9E4;
// when it runs out, picks a random point of the table D_800DCE60 (3 groups x 10 points of x, y, z, w); a point with
// a zero coordinate spawns nothing, else line_spark_burst_random_flip(point, room obj[0xC]) and a light flash (light_create_with_ctrl:
// type 3, 5..15 frames, at the truncated point, radius 100..255, white, room obj[0xC], owner obj[1]). The timer then
// restarts at min +0x28 + rand % (range +0x2A + 1) (unsigned).
extern f32 D_800DCE60[][10][4];
void line_spark_burst_random_flip(u8 *, u8);
/* was func_151570C4 */
void spark_point_flash_update(u8 *obj) {
    Header flash;
    Header2 at;
    s16 *timer;
    f32 *pt;
    s32 group;

    *(s16 *)(obj + 0x2C) -= D_800BE9E4;
    if (*(s16 *)(obj + 0x2C) >= 0) {
        return;
    }
    group = random_int() % 3U;
    pt = D_800DCE60[group][random_int() % 10U];
    if (pt[0] != 0.0f && pt[1] != 0.0f && pt[2] != 0.0f) {
        line_spark_burst_random_flip((u8 *) pt, obj[0xC]);
        flash.unk0 = 3;
        flash.unk1 = -1;
        flash.unk2 = random_int() % 11U + 5;
        flash.unk4 = 0;
        at.unk0 = pt[0];
        at.unk4 = pt[1];
        at.unk8 = pt[2];
        light_create_with_ctrl(&flash, &at, random_int() % 156U + 100, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, obj[0xC], obj[1]);
    }
    timer = (s16 *)(obj + 0x28);
    timer[2] = random_int() % (u32) (timer[1] + 1) + timer[0];
}

/* was func_15157294 */
void line_spark_burst_random_flip(u8 *arg0, u8 arg1)
{
  struct 
  {
    f32 u18[3];
    s16 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s16 u2E;
    f32 u30;
    f32 u34;
    f32 u38;
    f32 u3C;
    u8 u40;
    u8 u41;
    u8 u42;
    u8 u43;
    u8 u44;
    u8 u45;
    u8 u46;
    u8 u47;
    u8 u48;
    s16 u4A;
    s16 u4C;
    s16 u4E;
    f32 u50;
    f32 u54;
    u8 u58;
    u8 u59;
    s16 u5A;
    s16 u5C;
    u8 u5E;
    u8 u5F;
    s16 u60;
    s32 u64;
    s32 u68;
    s16 u6C;
    s32 u70;
    s32 u74;
    u8 u78;
    u8 u79;
    u8 u7A;
    u8 u7B;
    u8 u7C;
    u8 u7D;
    u8 u7E;
    u8 u7F;
    u8 u80;
    f32 u84;
    f32 u88;
    s16 u8C;
    s16 u8E;
    s16 u90;
    f32 u94;
    s32 u98;
    u8 u9C;
    u8 u9D;
    s8 u9E;
    s8 u9F;
    u8 uA0;
    u8 uA1;
    u8 uA2;
    u8 uA3;
    u8 uA4;
    } sp;
    memcpy(&sp, arg0, 0xC);
    sp.u24 = 0xA;
    sp.u26 = 0x1E;
    sp.u28 = 0;
    sp.u2A = -0x3F;
    sp.u2C = 0xFF;
    sp.u2E = 0x80;
    sp.u30 = 6.97f;
    sp.u34 = 3.37f;
    sp.u38 = 1.6899999f;
    sp.u3C = 1.6899999f; sp.u7C = 0xFF; sp.u40 = 0xFF; sp.uA2 = 0xFF; // fakematch: same-line statements (IDO line numbers change the scheduling)
    sp.u7D = 0xFF; sp.u41 = 0xFF; sp.uA3 = 0xFF; // fakematch: same-line statements (IDO line numbers change the scheduling)
    sp.u7E = 0xFF; sp.u42 = 0xFF; sp.uA4 = 0xFF; // fakematch: same-line statements (IDO line numbers change the scheduling)
    sp.u43 = 0xFF;
    sp.u44 = 0xFF;
    sp.u45 = 0xFF;
    sp.u46 = 0xFF;
    sp.u47 = 0xFF;
    sp.u48 = 9;
    sp.u4A = 5;
    sp.u4C = 0xA;
    sp.u4E = 0x1601;
    sp.u50 = 2.01f;
    sp.u54 = 3.02f;
    sp.u58 = 0x64;
    sp.u59 = 0x9B;
    sp.u5A = 4;
    sp.u5C = 0x3F;
    sp.u5E = 0;
    sp.u5F = 0x2B;
    sp.u60 = 0x1A01;
    sp.u64 = 0x200005;
    sp.u68 = 0;
    sp.u6C = (random_int() % 3U) + 7;
    sp.u70 = 0;
    sp.u74 = 0;
    sp.u78 = 0xFF;
    sp.u79 = 0xFF;
    sp.u7A = 0xFF;
    sp.u7B = 0xFF;
    sp.u7F = (random_int() % 1U) + 0xFF;
    sp.u80 = 0xFF;
    sp.u84 = sp.u88 = random_float() * 150.0f + 196.0f;
    sp.u8C = 4;
    sp.u8E = 0x3F;
    sp.u90 = 0x16;
    sp.u98 = 0xE01;
    sp.u94 = 1.25f;
    if (random_int() & 1) {
        sp.u98 |= 0x40;
    }
    if (random_int() & 1) {
        sp.u98 |= 0x80;
    }
    sp.u9C = 4;
    sp.u9D = 4;
    sp.u9E = -1;
    sp.u9F = -1;
    sp.uA0 = 1;
    sp.uA1 = 1;
    line_spark_burst_at((u8 *)&sp, arg1);
}

/* was func_15157504 */
void line_fx_free_buffers(s32 arg0) {
    vtx_slot_buffers_free(arg0 + 0x88, arg0);
}

/* was func_15157528 */
void line_fx_retire(struct102 *arg0) {
    line_fx_free_buffers(arg0);
    node_retire(arg0);
}

/* was func_15157554 */
void line_fx_free(struct102 *arg0) {
    line_fx_free_buffers(arg0);
    node_unlink_free(arg0);
}

s32 animmodel_start_anim(u8 *, s32, s32, f32, f32, s32); /* P95: f32 (float bits were passed as an int) */
s32 animmodel_create(s32, s32, u8 *, u8 *, u8 *, u8 *, u8 *);
s32 light_alloc_lookat_buf();
s32 light_alloc_light_buf(s32);
/* was func_15157580 */
u8 *anim_model_fx_spawn(u8 *arg0, s32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) { /* P95: f32 (float bits were passed as an int) */
    u8 *obj;
    s32 type;
    s32 i;

    type = 0x36;
    if (arg0[0] & 0x80) {
        type = 0x5B;
    } else if (arg0[0] & 0x10) {
        type = 0x4C;
    }
    obj = node_alloc(type, arg7, arg5 + 0x120, 1, arg6, 1);
    if (obj == NULL) {
        return NULL;
    }
    memcpy(obj + 0x10, arg0, 0x58);
    animmodel_create(*(s32 *)(obj + 0x18), *(s32 *)(obj + 0x1C), obj + 0x6C, obj + 0x70, obj + 0x74, obj + 0x78, obj + 0x68);
    guMtxIdentF(obj + 0x7C);
    guMtxIdentF(obj + 0xBC);
    *(u8 **)(*(u8 **)(obj + 0x68) + 0x3E0) = obj + 0x7C;
    *(u8 **)(*(u8 **)(obj + 0x68) + 0x3E4) = obj + 0xBC;
    animmodel_start_anim(*(u8 **)(obj + 0x68), 1, arg1, arg2, 0.0f, 0);
    *(s32 *)(obj + 0xFC) = arg3;
    *(s32 *)(obj + 0x118) = arg4;
    obj[0x100] = 0;
    for (i = 0; i < 4; i++) {
        ((s32 *)(obj + 0x104))[i] = 0;
    }
    *(s32 *)(obj + 0x114) = 0;
    if (arg3 != 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            ((s32 *)(obj + 0x104))[i] = light_alloc_light_buf(arg3);
        }
        *(s32 *)(obj + 0x114) = light_alloc_lookat_buf();
    }
    return obj;
}

/* was func_15157734 */
void anim_model_fx_free_lights(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0x104))[i]) {
            heap_set_block_tag(((s32 *)(arg0 + 0x104))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0x114) != 0) {
        heap_set_block_tag(*(s32 *)(arg0 + 0x114), 4);
    }
}

/* was func_151577B8 */
void anim_model_fx_retire(struct102 *arg0) {
    anim_model_fx_free_lights(arg0);
    shared_dl_release(*(s32 *)((u8 *)arg0 + 0x18));
    animmodel_free(*(s32 *)((u8 *)arg0 + 0x68));
    node_retire(arg0);
}

/* was func_151577FC */
void anim_model_fx_free(struct102 *arg0) {
    anim_model_fx_free_lights(arg0);
    shared_dl_release(*(s32 *)((u8 *)arg0 + 0x18));
    animmodel_free(*(s32 *)((u8 *)arg0 + 0x68));
    node_unlink_free(arg0);
}
