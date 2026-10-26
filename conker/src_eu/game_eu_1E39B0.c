#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
typedef struct { f32 x, y, z; } V3_61A0;
s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
void *memcpy(void *, const void *, size_t);

// ripple_spawn_flat: P234. One of the two ripple models object_break_effects_floor picks at random (the other is
// func_151B65C0, same arguments): fills a 0x80-byte particle request on the stack (start at `pos`, velocity `vel` or
// 0 (flag 0x20), normal `dir`, accel `acc` or 0 (flag 0x40), size scale (x 24.7) / end size / alpha / life (0x12C, or
// `life` + 0x100 >> shift with flag 0x80), flag 1 for `additive`) and spawns it through func_15132FBC (kind 3, alpha
// 0xFF, 8 bytes of user data = the request's first 8 bytes, copied to the object's +0x170). Returns the object (0 if
// none). The N64 code also sums the code words of func_15002FB4..func_1500310C (anti-tamper) and on a mismatch writes
// -1 to D_8008FDA8 + 0x148; the port has no MIPS code there, so the NON_MATCHING build skips that check (as P127 did in
// func_151E86A4). arg8 is not used.
s32 func_151B61A0(V3_61A0 *pos, V3_61A0 *vel, f32 scale, V3_61A0 *dir, V3_61A0 *acc, f32 speed, s16 life, u8 alpha,
                  s32 arg8, f32 grow, u8 shift, u8 additive, u8 layer, s32 owner) {
    s32 obj;
    s32 n;
    struct {
        f32 u0;
        f32 scale;
        f32 size;      /* 0x08: the request func_15132FBC gets */
        f32 grow;
        f32 u10;
        f32 u14;
        V3_61A0 dir;   /* 0x18 */
        f32 one[3];    /* 0x24 */
        V3_61A0 pos;   /* 0x30 */
        V3_61A0 vel;   /* 0x3C */
        V3_61A0 acc;   /* 0x48 */
        f32 speed;     /* 0x54 */
        s32 flags;     /* 0x58 */
        s16 life;      /* 0x5C */
        s16 u5E;
        s8 u60;
        s32 u64;
        u8 alpha;      /* 0x68 */
        s8 u69;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        u8 pad71;
        s8 u72;
        s32 u74;
        s8 u78;
        s16 step;      /* 0x7A */
        s16 fade;      /* 0x7C */
    } req;

    req.u0 = 0.0f;
    req.scale = scale;
    req.size = 24.7f * scale;
    req.grow = grow;
    req.u10 = scale;
    req.u14 = scale;
    req.dir = *dir;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.pos = *pos;
    req.speed = speed;
    req.flags = 0xB908;
    if (life == -1) {
        req.life = 0x12C;
        n = 0x100 >> shift;
    } else {
        req.flags = 0xB988;
        n = 0x100 >> shift;
        req.life = life + n;
    }
    if (vel != NULL) {
        req.vel = *vel;
        req.flags |= 0x20;
    } else {
        req.vel.x = 0.0f;
        req.vel.y = 0.0f;
        req.vel.z = 0.0f;
    }
    if (acc != NULL) {
        req.acc = *acc;
        req.flags |= 0x40;
    } else {
        req.acc.x = 0.0f;
        req.acc.y = 0.0f;
        req.acc.z = 0.0f;
    }
    if (additive != 0) {
        req.flags |= 1;
    }
    req.u5E = 2;
    req.u60 = 0;
    req.u64 = 0;
    req.alpha = alpha;
    req.u69 = 5;
    req.u6A = 0;
    req.u6B = 6;
    req.u6C = 0;
    req.u6D = 0;
    req.u6E = 2;
    req.u6F = 0;
    req.u70 = 2;
    req.u72 = 0;
    req.u74 = 0;
    req.u78 = 0;
    req.step = n;
    req.fade = 0xFF / n;
    obj = func_15132FBC(&req.size, 3, 0xFF, 8, layer, owner);
    if (obj != 0) {
        memcpy((void *) (obj + 0x170), &req, 8);
    }
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E39B0/func_151B61A0.s")
#endif

#ifdef NON_MATCHING
s32 func_15133E04(u8 *); /* P98: the asm reads a0 = the object */

void func_151B6444(u8 *arg0) {
    u8 *sp38;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f12;
    u8 *temp_v0;

    (*(f32 *)((u8 *)arg0 + 0x170)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x170)) + (1.0020001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x170)) > 29.9f) {
        (*(f32 *)((u8 *)arg0 + 0x170)) = 0.0f;
        func_10010F88(0x502, 0x5DC0U, 0, 0U, -1, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x3C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x40)), 0x64, 0x1F4);
    }
    temp_v0 = arg0 + 0x170;
    var_f12 = (*(f32 *)((u8 *)temp_v0 + 0));
    if (var_f12 < 12.566371f) {
        sp38 = temp_v0;
        temp_f0 = sinf(var_f12);
        var_f12 = (*(f32 *)((u8 *)temp_v0 + 4));
        temp_f2 = var_f12 + (temp_f0 * (0.05f * var_f12));
        (*(f32 *)((u8 *)arg0 + 0x1C)) = temp_f2;
        (*(f32 *)((u8 *)arg0 + 0x18)) = temp_f2;
    } else {
        temp_f2_2 = (*(f32 *)((u8 *)temp_v0 + 4));
        (*(f32 *)((u8 *)arg0 + 0x1C)) = temp_f2_2;
        (*(f32 *)((u8 *)arg0 + 0x18)) = temp_f2_2;
    }
    func_15133E04(arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E39B0/func_151B6444.s")
#endif
void func_151B657C(u8 *arg0) {
    s32 temp_v0 = *(s32 *)(arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0);
        *(s32 *)(arg0 + 0x88) = 0;
    }
}
