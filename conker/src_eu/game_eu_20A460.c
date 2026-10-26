#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void flip_sprite_particle_spawn(s16, u8, f32, u8 *, u8, u8, s32);
s32 emit_dust_by_angles(s16 *, s32 *, s32, u8, s32);
s32 screen_colour_fade_fx_start(s32, s32, s32, s32, s32, s32, s32, s32);
void muzzle_light_small_spawn(u8 *, u8, s32);

/* was func_151DCC50 */
void flash_burst_effects(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s16 u38;
        s16 u3A;
        s16 u3C;
        s16 u3E;
        s32 u40;
        u8 pad44[0x8];
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        s8 u64;
        s8 u65;
        u8 pad66[0x2];
        f32 u68;
        f32 u6C;
        s8 u70;
        s8 u71;
        u8 pad72[0x2];
        f32 u74;
        s8 u78;
        u8 pad79[0x3];
        f32 u7C;
    } sp;
    s32 sp30;
    s32 sp2C;

    sp2C = random_int();
    sp30 = random_int();
    flip_sprite_particle_spawn((s16) (((u32) sp2C % 5U) + 0xC), (((u32) sp30 % 56U) + 0xC8) & 0xFF, (random_float() * 600.0f) + 1700.0f, arg0, 0xFF, (s32) arg1, arg2);
    (*(s32 *)((u8 *)(&sp.u40) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u40) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u40) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u50 = 8.0f;
    sp.u4E = 7;
    sp.u54 = 10.0f;
    sp.u4C = 0xC;
    sp.u38 = 0;
    sp.u3A = 0xFF;
    sp.u3C = -0x40;
    sp.u3E = 0x3C;
    sp.u58 = 0x24;
    sp.u5A = 0x3C;
    sp.u64 = 0xC8;
    sp.u65 = 0x37;
    sp.u70 = 0;
    sp.u71 = 0xC;
    sp.u78 = 1;
    sp.u5C = -1.097f;
    sp.u60 = 0.37f;
    sp.u68 = 280.0f;
    sp.u6C = 390.0f;
    sp.u74 = 0.6f;
    sp.u7C = 1.0f;
    emit_dust_by_angles(&sp.u38, &sp.u40, 0, arg1, arg2);
    muzzle_light_small_spawn(arg0, arg1, arg2);
    sp2C = random_int();
    screen_colour_fade_fx_start(0xFF, 0xFF, 0xFF, (((u32) sp2C % 51U) + 0x96) & 0xFF, (random_int() % 5U) + 8, 0, (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20A460/flash_burst_effects.s")
#endif
void flash_burst_effects(u8 *arg0, u8 arg1, s32 arg2);

/* was func_151DCE6C */
void flash_smoke_emitter_spawn(u8 *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    typedef struct {
        s32 w[3];
    } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
        u8 unk10;
    } tmp;
    struct260 *temp_v0;

    if (arg2 != 0) {
        flash_burst_effects(arg0, arg4, arg5);
    }
    tmp.unk0 = *(Blk12 *)arg0;
    tmp.unkC = 0.0f;
    tmp.unk10 = arg3;
    temp_v0 = func_15149130(arg1, -1, 0x5B, -1, 1, 0, 0x14, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
    }
}

#ifdef NON_MATCHING
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern s32 D_800AB8E0;
extern s32 D_800AB8EC;

/* was func_151DCF2C */
void flash_smoke_emitter_update(u8 *arg0) {
    struct {
        s32 u90;
        u8 pad94[0x8];
        s32 u9C;
        u8 padA0[0xC];
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        s32 uBC;
        s32 uC0;
        s16 uC4;
        s16 uC6;
        s32 uC8;
        s32 uCC;
        u8 uD0;
        u8 uD1;
        u8 uD2;
        s8 uD3;
        u8 uD4;
        u8 uD5;
        u8 uD6;
        s8 uD7;
        s8 uD8;
        s8 uD9;
        s16 uDA;
        s16 uDC;
        s16 uDE;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        u8 padF0[0x8];
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
        f32 u110;
        s32 u114;
        u8 pad118[0x4];
        s8 u11C;
        s8 u11D;
        s8 u11E;
        s8 u11F;
        s8 u120;
        s8 u121;
    } sp;
    f32 temp_f16;
    f32 temp_f4;
    s32 temp_lo;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_s1;
    u8 *temp_v1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((0.136f + (random_float() * 0.12100001f)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uD9 = 0x6C;
        sp.uC4 = 0x5103;
        sp.uBC = 0x200005;
        sp.uAC = 0;
        sp.uAD = 0;
        sp.uC0 = 0;
        sp.uC8 = 0;
        sp.uCC = 0;
        sp.uDA = 0x28;
        sp.uDC = 6;
        sp.u114 = 0x80DE07;
        sp.u11C = 8;
        sp.u11D = 6;
        sp.u11E = 0x16;
        sp.u11F = -1;
        sp.u120 = -1;
        sp.u121 = 0;
        sp.uDE = 0x78;
        sp.uD8 = 0xFF;
        sp.uB8 = 0.97047f;
        sp.uE0 = 1.006579f;
        (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uF8 = 0.0f;
        sp.uFC = 0.0f;
        sp.u100 = 0.0f;
        sp.u104 = 0.0f;
        sp.u108 = 0.0f;
        sp.u10C = 0.0f;
        if ((*(u8 *)((u8 *)temp_s1 + 0x10)) == 0) {
            sp.uD0 = 0xEF;
            sp.uD1 = 0xE0;
            sp.uD2 = 0xCD;
            sp.uD3 = 0xFF;
            sp.uD4 = 0x30;
            sp.uD5 = 0x30;
            sp.uD6 = 0x30;
        }
        do {
            sp.uAE = (random_int() % 5U) + 4;
            sp.uAF = (random_int() % 5U) + 4;
            sp.uB0 = random_float() * 50.0f;
            sp.uB4 = random_float() * 50.0f;
            temp_f4 = random_float() * 0.15100001f;
            sp.u114 &= ~0xC0;
            sp.u110 = temp_f4 + 0.19100001f;
            var_s0 = 0;
            if (random_int() & 1) {
                var_s0 = 0x80;
            }
            if (random_int() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.u114 |= var_v0 | var_s0;
            sp.uD7 = (random_int() % 56U) + 0xC8;
            sp.uC6 = (random_int() % 36U) + 0x6E;
            temp_f16 = (random_float() * 370.0f) + 403.0f;
            sp.uE8 = temp_f16;
            sp.uE4 = temp_f16;
            if ((*(u8 *)((u8 *)temp_s1 + 0x10)) != 0) {
                (*(s32 *)((u8 *)(&sp.u9C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AB8E0) + 0));
                (*(s32 *)((u8 *)(&sp.u9C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AB8E0) + 4));
                (*(u8 *)((u8 *)(&sp.u9C) + 8)) = (u8) (*(u8 *)((u8 *)(&D_800AB8E0) + 8));
                (*(s32 *)((u8 *)(&sp.u90) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800AB8EC) + 0));
                (*(s32 *)((u8 *)(&sp.u90) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800AB8EC) + 4));
                (*(u8 *)((u8 *)(&sp.u90) + 8)) = (u8) (*(u8 *)((u8 *)(&D_800AB8EC) + 8));
                temp_lo = ((random_int() % 3U) & 0xFF) * 3;
                temp_v1 = &sp.u9C + temp_lo;
                temp_a0 = &sp.u90 + temp_lo;
                sp.uD0 = (*(u8 *)((u8 *)temp_v1 + 0));
                sp.uD1 = (*(u8 *)((u8 *)temp_v1 + 1));
                sp.uD3 = 0xFF;
                sp.uD2 = (*(u8 *)((u8 *)temp_v1 + 2));
                sp.uD4 = (*(u8 *)((u8 *)temp_a0 + 0));
                sp.uD5 = (*(u8 *)((u8 *)temp_a0 + 1));
                sp.uD6 = (*(u8 *)((u8 *)temp_a0 + 2));
            }
            temp_v0 = particle_spawn_ex(&sp.uBC, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.uAC, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20A460/flash_smoke_emitter_update.s")
#endif