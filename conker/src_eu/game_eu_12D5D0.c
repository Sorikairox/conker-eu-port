#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#ifdef NON_MATCHING
void func_15100248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151D56F8(u8 *arg0);
void func_151D44C4(u8 *arg0, u8 arg1, s32 arg2);
s32 func_151030B8(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_15100304(f32 *pos, f32 *dir, u8 flag, s32 arg3);
void func_151000EC(u8 *arg0, s32 arg1, struct127 *arg2, s32 arg3);
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15082278(u8 *obj, u8 *hit, s32 arg2); /* P197: s32 like its C (0 / 1 / 2; nobody reads it) */
void func_151001BC(u8 *arg0);
extern s32 D_800A2500;      /* f32[3] spray point (rodata; s32 as in func_1510015C below) */
extern f32 D_800A250C[9];

// gun_fire_effects: muzzle effects of obj's weapon: muzzle point / direction from func_15100248; with a visible
// model a flash, a spark spray (func_151030B8) and the shot effect (func_15100304); if `trail` three trail puffs
// along the direction (0.088 / 0.383 / 0.81); if `ray` a 2000-unit ray cast whose hit record (obj + 0x31C's block
// + 0xB0, or a local one) is applied (func_15082278); finally the shell drop (func_151001BC).
// Returns 0: game_981E0 calls it without a declaration (= int); the N64 result is func_151001BC's leftover v0.
s32 func_150FF840(u8 *obj, u8 trail, u8 ray, u8 flag, s32 arg4) {
    f32 pos[3];
    f32 dir[3];
    f32 v104[3];
    f32 vF8[3];
    f32 speed[2];
    f32 puff[3][3];
    u8 local_hit[0x48];
    u8 *hit;
    s32 r1;
    s32 r2;
    s32 i;

    func_15100248((s32)obj, (s32)pos, (s32)dir, (s32)v104, (s32)vF8);
    func_151D56F8(obj);
    if (*(void **)(obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        func_151D44C4((u8 *)pos, flag, arg4);
        speed[1] = (func_150ADA68() * 3400.0f + 4800.0f) * 0.001f;
        speed[0] = (func_150ADA68() * 220.0f + 320.0f) * 0.1f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_151030B8(obj, D_80088BB0, (f32 *)&D_800A2500, D_800A250C, speed, (u32)r1 % 3 + 4, (r2 & 0x7F) + 0x80,
                      func_150ADA68() * 450.0f + 780.0f, pos, 0xFF, 0, -1, flag, arg4);
        func_15100304(pos, dir, flag, arg4);
    }
    if (trail) {
        for (i = 0; i < 3; i++) {
            f32 k = (i == 0) ? 0.088000007f : (i == 1) ? 0.383000016f : 0.810000062f;

            puff[i][0] = dir[0] * k + pos[0];
            puff[i][1] = dir[1] * k + pos[1];
            puff[i][2] = dir[2] * k + pos[2];
        }
        func_151000EC((u8 *)puff[0], (s32)pos, (struct127 *)obj, 0x32);
        func_151000EC((u8 *)puff[1], (s32)pos, (struct127 *)obj, 0x30);
        func_151000EC((u8 *)puff[2], (s32)pos, (struct127 *)obj, 0x31);
    }
    if (ray) {
        hit = (*(u8 **)(obj + 0x31C) != NULL) ? *(u8 **)(obj + 0x31C) + 0xB0 : local_hit;
        func_15081A90((struct127 *)obj, pos[0], pos[1], pos[2], dir[0] * 0.001f, dir[1] * 0.001f, dir[2] * 0.001f,
                      hit, 2000.0f, 0, 0, 0, -1, 0, 0);
        func_15082278(obj, hit, 0x10);
    }
    func_151001BC(obj);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12D5D0/func_150FF840.s")
#endif

void func_151000EC(u8 *arg0, s32 arg1, struct127 *arg2, s32 arg3) {
    u16 w;
    s32 idx;
    w = *(u16 *)((u8 *)arg2 + 0x7A);
    idx = arg2 - D_800CC2D0;
    func_1505D1C4(*(f32 *)arg0, *(f32 *)(arg0 + 4), *(f32 *)(arg0 + 8), arg3 | 0x60000, idx, w, 0, arg1);
}

s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern s32 D_800A2500;

void func_1510015C(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *sp1C;
    s32 sp18;

    sp1C = &D_800A2500;
    sp18 = arg2;
    func_15145EA4(&sp1C, &sp18, (*(s32 *)((u8 *)arg0 + 0x1D4)) + (D_80088BB0 << 6), 1);
}

void func_151001BC(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = ((u32)func_150ADA20() % 11) + 0x14;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        sp18[4] = (func_150ADA20() & 1) + 7;
        sp18[6] = -1;
        func_151D8E18(sp18, 0, 0xFF, 1);
    }
}

s32 func_151D5FC8(struct127 *, s32, s32, s32, s32, s32, s32);
void func_151D441C(s32, s32, s32, s32);
extern s32 D_8009002C;
extern u8 *D_80090034;
void func_15100248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  func_151D5FC8(arg0, arg1, arg2, arg3, arg4, D_8009002C, *D_80090034);
  func_151D441C(arg0, arg1, arg1, 0x8003A);
}

void func_151002AC(s32 arg0, u8 *arg1, s32 arg2) {
    u8 temp_v0 = arg1[4];
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)(arg1 + 0x94) & 0x80)) {
        func_1508220C(arg1, 4, 0);
    }
}

#ifdef NON_MATCHING
/* P179 */
extern u32 D_800A2530[4];
void func_15145974(f32 *, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
s32 func_151307F0(s32 *, s32, s32, s32, s32, s32);

// gun_shot_sparks: P179: 10..18 kind-1 spark particles (func_151307F0 block, 0x67 bytes) at `pos`, sprayed around
/* the shot direction `dir` (its yaw from func_15145974; the pitch is forced to 0) within 21 / 256 turns: colour
 * D_800A2530[random 0..3], life 10..22, alpha 155..255, size 75 + random x 155, speed 20 + random x 20,
 * gravity -0.657 + random x 0.621, random mirror flags 0x80 / 0x40 on flags 0x4C207; owner / owner arg `flag` /
 * `arg3`. */
void func_15100304(f32 *pos, f32 *dir, u8 flag, s32 arg3) {
    struct {
        s32 u00;
        s32 u04;
        s16 u08;
        s16 life;      /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 u14[7];
        u8 alpha;      /* +0x1B */
        u8 u1C;
        u8 colour;     /* +0x1D */
        s16 u1E;
        s16 u20;
        s16 u22;
        f32 u24;
        f32 sizeX;     /* +0x28 */
        f32 sizeY;     /* +0x2C */
        f32 pos[3];    /* +0x30 */
        f32 u3C[3];
        f32 vel[3];    /* +0x48 */
        f32 gravity;   /* +0x54 */
        s32 flags;     /* +0x58 */
        s32 u5C;
        u8 u60;
        u8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        u8 u65;
        u8 u66;
    } p;
    u32 colours[4];
    f32 yaw;
    f32 pitch;
    s32 n;
    s16 yawBase;
    s16 pitchBase;
    u32 r1;
    u32 r2;
    s32 mirrorX;
    s32 mirrorY;
    f32 size;

    n = (u32) func_150ADA20() % 9 + 10;
    p.u08 = 0x2203;
    p.u00 = 0x200005;
    p.u04 = 0;
    p.u0C = 0;
    p.u10 = 0;
    p.u14[0] = 0xFF;
    p.u14[1] = 0xFF;
    p.u14[2] = 0xFF;
    p.u14[3] = 0xFF;
    p.u14[4] = 0xFF;
    p.u14[5] = 0xFF;
    p.u14[6] = 0xFF;
    p.u1C = 0xFF;
    p.pos[0] = pos[0];
    p.pos[1] = pos[1];
    p.pos[2] = pos[2];
    p.u3C[0] = ((f32 *) D_800A5860)[0];
    p.u3C[1] = ((f32 *) D_800A5860)[1];
    p.u3C[2] = ((f32 *) D_800A5860)[2];
    p.u1E = 7;
    p.u20 = 0x24;
    p.u22 = 1;
    p.flags = 0x4C207;
    p.u60 = 0;
    p.u61 = 7;
    p.u62 = -1;
    p.u63 = -1;
    p.u64 = -1;
    p.u65 = 0;
    p.u5C = 0;
    p.u66 = 0xFF;
    p.u24 = 1.0f;
    func_15145974(dir, &yaw, &pitch);
    pitch = 0.0f;
    yawBase = ((s16) (yaw * 182.04445f) >> 8) - 0x8A;
    pitchBase = ((s16) (pitch * 182.04445f) >> 8) - 0x8A;
    do {
        colours[0] = D_800A2530[0];
        colours[1] = D_800A2530[1];
        colours[2] = D_800A2530[2];
        colours[3] = D_800A2530[3];
        p.colour = colours[func_150ADA20() & 3];
        p.life = (u32) func_150ADA20() % 13 + 10;
        p.alpha = (u32) func_150ADA20() % 101 + 0x9B;
        size = func_150ADA68() * 155.0f + 75.0f;
        p.sizeX = size;
        p.sizeY = size;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794(r1 % 21 + yawBase, r2 % 21 + pitchBase, func_150ADA68() * 20.0f + 20.0f, p.vel);
        p.gravity = func_150ADA68() * 0.62100005f + -0.657f;
        p.flags &= ~0xC0;
        mirrorX = (func_150ADA20() & 1) ? 0x80 : 0;
        mirrorY = (func_150ADA20() & 1) ? 0x40 : 0;
        p.flags |= mirrorY | mirrorX;
        func_151307F0((s32 *) &p, 1, 0, 0, flag, arg3);
        n--;
    } while (n > 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12D5D0/func_15100304.s")
#endif
