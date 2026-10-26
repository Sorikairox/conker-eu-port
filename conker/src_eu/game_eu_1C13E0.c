#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 emit_burst_from_spec_b(void *, u8, s32); /* P98: asm reads a0 = sp+0x20 block, a1 & 0xFF, a2 */

/* was func_15193660 */
void obj_head_particle_burst(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u20;
        s32 u24;
        s32 u28;
        u8 pad2C[0x8];
        s16 u34;
        s16 u36;
        s16 u38;
        s16 u3A;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s16 u50;
        s16 u52;
        s32 u54;
        s32 u58;
        s32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        s8 u91;
        s16 u92;
        s16 u94;
    } sp;
    s32 temp_v0;

    if ((arg0 != NULL) && ((*(s32 *)((u8 *)arg0 + 0)) != 0)) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x1D4));
        if (temp_v0 != 0) {
            mtx_get_translation(temp_v0, 0xA, &sp.u28);
            sp.u20 = 8;
            sp.u3C = 12.403001f;
            sp.u24 = 7;
            sp.u38 = -0x21;
            sp.u3A = 0x18;
            sp.u50 = 0x28;
            sp.u52 = 0x23;
            sp.u54 = 0xA0;
            sp.u58 = 0x13;
            sp.u90 = 0x21;
            sp.u88 = 0xFF;
            sp.u34 = 0;
            sp.u36 = 0xFF;
            sp.u5C = 0;
            sp.u89 = 0xFF;
            sp.u8A = 0xFF;
            sp.u8B = 0xFF;
            sp.u8C = 0xFF;
            sp.u8D = 0xFF;
            sp.u8E = 0xFF;
            sp.u8F = 0xFF;
            sp.u91 = 0xF;
            sp.u92 = 0x19;
            sp.u94 = 0xA;
            sp.u78 = -12.86f;
            sp.u70 = -12.86f;
            sp.u84 = 25.38f;
            sp.u7C = 25.38f;
            sp.u40 = 5.039f;
            sp.u44 = 0.908871f;
            sp.u48 = -0.707f;
            sp.u4C = 0.261f;
            sp.u64 = 1.96f;
            sp.u60 = 0.0f;
            sp.u6C = 0.0f;
            sp.u74 = 0.0f;
            sp.u80 = 0.0f;
            sp.u68 = 0.307f;
            emit_burst_from_spec_b(&sp.u20, arg1, arg2);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C13E0/obj_head_particle_burst.s")
#endif
typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} SpA3C;
s32 bone_emitter_spawn(SpA3C *, s32, ...);
extern f32 D_800A85C4;

/* was func_151937F4 */
void obj_bone_debris_emitter_attach(u8 *arg0, s32 arg1, s32 arg2) {
    SpA3C s;

    if (arg0 != NULL && *(s32 *)arg0 != 0) {
        s.u0 = arg0[0x3B];
        s.u4 = arg0;
        s.u8_ = 0;
        s.uC = -28.0f;
        s.u10 = 6.0f;
        s.u14 = 1.0f;
        s.u18 = -58.0f;
        s.u1C = -3.0f;
        s.u20 = -31.0f;
        s.u24 = 2;
        s.u26 = 30;
        s.u28 = 25;
        s.u2A = 750;
        s.u2E = 3;
        s.u2F = 3;
        s.u30 = -1;
        s.u34 = D_800A85C4;
        s.u38 = 4;
        s.u39 = -1;
        bone_emitter_spawn(&s, 0, arg0);
    }
}

/* was func_15193E54 */
s32 bone_debris_emitter_init(struct102 *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = D_800A85C8;
    return 1;
}

#ifdef NON_MATCHING
s32 anim_model_fx_spawn_moving(s8 *, f32 *, s32, f32, s32, s32, s32, s32, s32);
s32 motion_track_get_delta(u8 *, u8 **, u8 *);

/* was func_15193E6C */
void bone_debris_emit(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    struct {
        u8 * u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s8 u84;
        u8 pad85[0x3];
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        u8 pad8D[0x1];
        s16 u8E;
        s32 u90;
        s32 u94;
        s32 u98;
        s32 u9C;
        s32 uA0;
        s32 uA4;
        s32 uA8;
        s32 uAC;
        s32 uB0;
        s8 uB4;
        s8 uB5;
        u8 padB6[0x2];
        s8 uB8;
        s8 uB9;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        s8 uBD;
        s8 uBE;
        s8 uBF;
        s8 uC0;
        u8 padC1[0x3];
        u8 * uC4;
        u8 uC8;
        s8 uC9;
        u8 padCA[0x2];
        f32 uCC;
        f32 uD0;
        f32 uD4;
        u8 padD8[0x4];
        s16 uDC;
        s16 uDE;
    } sp;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;

    if ((motion_track_get_delta((*(u8 **)((u8 *)arg5 + 0x1C)), &sp.u50, arg0) != 0) && ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0xAD)) == 0)) {
        temp_f2 = (*(f32 *)((u8 *)sp.u50 + 0));
        temp_f12 = (*(f32 *)((u8 *)sp.u50 + 4));
        temp_f14 = (*(f32 *)((u8 *)sp.u50 + 8));
        if (!(sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12) + (temp_f14 * temp_f14)) < 8.1f)) {
            sp.uC0 = 0;
            sp.u88 = 0x27;
            sp.u89 = 0;
            sp.u8A = 1;
            sp.u8B = -1;
            sp.u8C = -1;
            sp.u8E = (random_int() % 41U) + 0x5A;
            sp.u90 = 0xA0;
            sp.u94 = 0x13;
            sp.u9C = 0x220405;
            sp.uA0 = 0x40200;
            sp.uB5 = 8;
            sp.uA4 = 1;
            sp.uA8 = 0x38;
            sp.u98 = 0;
            sp.uB4 = 0;
            sp.uAC = 0x80;
            sp.uB0 = 0x20;
            sp.uB8 = 0xFF;
            sp.uB9 = 0xFF;
            sp.uBA = 0xFF;
            sp.uBB = 0xFF;
            sp.uBC = 0xFF;
            sp.uBD = 0xFF;
            sp.uBE = 0xFF;
            sp.uBF = 0xFF;
            sp.uC4 = (*(u8 **)((u8 *)arg5 + 0x1C));
            sp.uC9 = 1;
            sp.uC8 = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg5 + 0x1C))) + 0x3B));
            (*(f32 *)((u8 *)(&sp.uCC) + 0)) = (*(f32 *)((u8 *)arg0 + 0));
            (*(f32 *)((u8 *)(&sp.uCC) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
            (*(f32 *)((u8 *)(&sp.uCC) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
            temp_f10 = ((*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0))) * (*(f32 *)((u8 *)arg5 + 0x74));
            sp.u64 = temp_f10;
            temp_f8 = ((*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4))) * (*(f32 *)((u8 *)arg5 + 0x74));
            sp.u68 = temp_f8;
            temp_f16 = ((*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8))) * (*(f32 *)((u8 *)arg5 + 0x74));
            sp.u6C = temp_f16;
            sp.uCC += temp_f10 * arg4;
            sp.uD0 += temp_f8 * arg4;
            sp.uD4 += temp_f16 * arg4;
            sp.u54 = random_float() * 360.0f;
            sp.u58 = random_float() * 360.0f;
            sp.u5C = random_float() * 360.0f;
            random_float();
            sp.u60 = 340.0f * 0.001f;
            temp_f6 = random_float() * 1000.0f;
            sp.u74 = 0.0f;
            sp.u70 = (temp_f6 + -500.0f) * 0.01f;
            sp.u78 = ((random_float() * 1000.0f) + -500.0f) * 0.01f;
            temp_f18 = (random_float() * 121.0f) + -135.0f;
            sp.uDC = 0x19;
            sp.uDE = 0xA;
            sp.u84 = 0xF;
            sp.u80 = 0.982883f;
            sp.u7C = temp_f18 * 0.001f;
            anim_model_fx_spawn_moving(&sp.u88, &sp.u54, 0, random_float() * 1814.0f * 0.001f, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg5 + 0xC)), (s32) (*(u8 *)((u8 *)arg5 + 1)));
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C13E0/bone_debris_emit.s")
#endif