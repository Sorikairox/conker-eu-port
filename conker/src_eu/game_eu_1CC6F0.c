#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void *memcpy(void *, const void *, s32);
extern u8 g_vec3_zero[]; /* was D_800A5860 */


/* was func_1519EEE0 */
u8 *seqfx_timer_create(s16 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    u8 *temp_v0;
    temp_v0 = node_alloc(0x26, arg6, 0x2C, 1, (u8) (s32) arg5, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = arg3;
    (*(s32 *)((u8 *)temp_v0 + 0x1C)) = arg4;
    (*(s16 *)((u8 *)temp_v0 + 0x20)) = arg0;
    (*(u8 *)((u8 *)temp_v0 + 0x28)) = arg2;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = arg1;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    return temp_v0;
}

/* was func_1519EF74 */
void seqfx_timer_update(struct102 *arg0) {
    s32 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x10) & 1) {
        var_v0 = 0;
        *(s16 *)((u8 *)arg0 + 0x20) -= g_frame_ticks;
        if (*(s16 *)((u8 *)arg0 + 0x20) < 0) {
            var_v0 = 1;
        }
        if (var_v0 != 0) {
            if (arg0->unk28 == 0) {
                var_v0 = *(s32 *)((u8 *)arg0 + 0x24);
                *(s32 *)(var_v0 + 0x30) = 0;
            }
            node_destroy(arg0);
        }
    }
}

typedef struct { f32 x, y, z; } V3_1519EFE8;
typedef struct {
    s32 a;
    s32 b;
    V3_1519EFE8 pos;
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s16 x2C;
    s16 x2E;
    f32 x30;
    f32 x34;
    f32 x38;
} Sp_1519EFE8;
extern f32 g_seqfx_burst_k_90a0; /* was D_800A90A0 */
extern f32 g_seqfx_burst_k_90a4; /* was D_800A90A4 */
extern f32 g_seqfx_burst_k_90a8; /* was D_800A90A8 */
extern f32 g_seqfx_burst_k_90ac; /* was D_800A90AC */
extern f32 g_seqfx_burst_k_90b0; /* was D_800A90B0 */

/* was func_1519EFE8 */
void seqfx_burst_spawn(V3_1519EFE8 *arg0, u16 arg1, f32 arg2, u8 arg3, s32 arg4) {
    Sp_1519EFE8 s;
    s32 i;
    f32 f;

    s.a = 10;
    s.b = 7;
    s.pos = *arg0;
    s.x1C = 10.0f;
    s.x20 = 8.0f;
    s.x14 = 0;
    s.x16 = 0xFF;
    s.x18 = -0x35;
    s.x1A = 0x18;
    s.x2C = 0x32;
    s.x2E = 0x14;
    f = arg2;
    s.x24 = g_seqfx_burst_k_90a0;
    s.x28 = g_seqfx_burst_k_90a4;
    s.x30 = g_seqfx_burst_k_90a8;
    s.x34 = g_seqfx_burst_k_90ac;
    s.x38 = g_seqfx_burst_k_90b0;
    i = arg1;
    emit_textured_burst(&s, &i, &f, 1, 0.0f, 0, arg3, arg4);
}

s32 mdl_particle_spawn_ex(f32 *, s32, s32, s32, s32, s32, s32);

/* was func_1519F0FC */
void seqfx_track_effect_spawn(u8 *arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 * u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        s32 u70;
        u8 pad74[0x8];
        s32 u7C;
        u8 pad80[0x8];
        f32 u88;
        s32 u8C;
        s16 u90;
        u16 u92;
        s8 u94;
        u8 pad95[0x3];
        s32 u98;
        s8 u9C;
        s8 u9D;
        s8 u9E;
        s8 u9F;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        u8 padA5[0x1];
        s8 uA6;
        u8 padA7[0x1];
        s32 uA8;
        s8 uAC;
        u8 padAD[0x1];
        s16 uAE;
        s16 uB0;
        u8 padB2[0x2];
        s32 uB4;
    } sp;
    s32 temp_v0_2;
    u8 *temp_v0;

    temp_v0 = ((u8 *)&g_vec3_zero);
    sp.u38 = arg0;
    sp.u3C = 1.0f;
    sp.u40 = 1.0f;
    sp.u44 = (*(f32 *)((u8 *)arg0 + 0x18)) * 0.1f;
    sp.u48 = (*(f32 *)((u8 *)arg0 + 0x1C)) * 0.1f;
    sp.u4C = (*(f32 *)((u8 *)arg0 + 0xC));
    sp.u50 = (*(f32 *)((u8 *)arg0 + 0x10));
    sp.u58 = 1.0f;
    sp.u5C = 1.0f;
    sp.u60 = 1.0f;
    sp.u54 = (*(f32 *)((u8 *)arg0 + 0x14));
    sp.u64 = (*(f32 *)((u8 *)arg0 + 0));
    sp.u68 = (*(f32 *)((u8 *)arg0 + 4));
    sp.u6C = (*(f32 *)((u8 *)arg0 + 8));
    (*(s32 *)((u8 *)(&sp.u70) + 0)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0));
    (*(s32 *)((u8 *)(&sp.u70) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
    (*(s32 *)((u8 *)(&sp.u70) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
    sp.u8C = 0x980;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9C = 0xFF;
    sp.u9D = 0x15;
    sp.u9E = 0;
    sp.u9F = 0;
    sp.uA0 = 0;
    sp.uA1 = 0;
    sp.uA2 = 0;
    sp.uA3 = 0;
    sp.uA4 = 2;
    sp.uA6 = 0;
    sp.uA8 = 0;
    sp.uAC = 0;
    sp.uAE = 1;
    sp.uB0 = 0xFF;
    sp.uB4 = 0;
    sp.u88 = 0.0f;
    sp.u90 = arg2;
    sp.u92 = arg1;
    temp_v0_2 = mdl_particle_spawn_ex(&sp.u3C, 3, 0xFF, 0, 4, (s32) arg3, arg4);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x170, &sp.u38, 4);
    }
}
/* was func_1519F294 */
s32 seqfx_track_effect_sync(u8 *arg0) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x170));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * 0.1f);
    (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * 0.1f);
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    return 1;
}

void *memcpy(void *, const void *, s32);

typedef struct {
    s8 u0;
    s8 u1;
    s16 u2;
    s16 u4;
    s16 pad6;
    s32 u8;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    f32 u1C[6];
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
} Blk58;

/* was func_1519F2F4 */
void seqfx_track_sprite_spawn(u8 *arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    Blk58 blk;
    u8 *tmp;
    u8 *temp_v0;

    tmp = arg0;
    blk.u0 = arg1;
    blk.u1 = 0;
    blk.u2 = 0x3B03;
    blk.u4 = arg2;
    blk.u8 = 0;
    blk.uC = 0;
    blk.u10[0] = 0xFF;
    blk.u10[1] = 0xFF;
    blk.u10[2] = 0xFF;
    blk.u10[3] = 0xFF;
    blk.u14 = *(f32 *)(arg0 + 0x18) * 10.0f;
    blk.u18 = *(f32 *)(arg0 + 0x1C) * 10.0f;
    blk.u1C[0] = *(f32 *)(arg0 + 0);
    blk.u1C[1] = *(f32 *)(arg0 + 4);
    blk.u1C[2] = *(f32 *)(arg0 + 8);
    blk.u1C[3] = *(f32 *)(arg0 + 0xC);
    blk.u1C[4] = *(f32 *)(arg0 + 0x10);
    blk.u1C[5] = *(f32 *)(arg0 + 0x14);
    blk.u34[0] = 1.0f;
    blk.u34[1] = 1.0f;
    blk.u34[2] = 1.0f;
    blk.u40 = 0x045C0081;
    blk.u44 = 0xFF;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 7;
    blk.u48 = 0;
    blk.u4C = 0xFF;
    blk.u50 = 0;
    blk.u54 = 1;
    blk.u56 = 0xFF;
    temp_v0 = effect3d_spawn_full(&blk, (s32)&D_800A4AA0, 0x27, 0, 0, 0x17, 0, 3, 0xFF, 4, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x110, &tmp, 4);
    }
}

/* was func_1519F474 */
s32 seqfx_track_sprite_sync(u8 *arg0) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * 10.0f);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * 10.0f);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)temp_v1);
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    return 1;
}
