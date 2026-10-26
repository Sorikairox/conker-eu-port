#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void *memcpy(void *, const void *, s32);
extern u8 g_bullet_glow_sprite[]; /* was D_800AA870 */
typedef struct { f32 x, y, z; } V3_151B89B0;

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
    V3_151B89B0 u1C;
    V3_151B89B0 u28;
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
} Blk58_89B0;

/* was func_151B89B0 */
u8 *bullet_glow_spawn(u8 *arg0) {
    s32 pad; // fakematch: 4-byte hole above tmp
    u8 *tmp;
    Blk58_89B0 blk;
    V3_151B89B0 pos;
    u8 *temp_v0;

    tmp = arg0;
    blk.u0 = 0xFF;
    blk.u1 = 0;
    blk.u2 = 0x5901;
    blk.u4 = 0x32;
    blk.u8 = 0;
    blk.uC = 0;
    blk.u10[0] = 0xFF;
    blk.u10[1] = 0xE6;
    blk.u10[2] = 0xB6;
    blk.u10[3] = 0xFF;
    blk.u14 = 9.0f;
    blk.u18 = 1.0f;
    pos = *(V3_151B89B0 *)(arg0 + 0x38);
    blk.u28 = pos;
    blk.u1C = pos;
    blk.u34[0] = *(f32 *)(arg0 + 0x44) * 0.25f;
    blk.u34[1] = *(f32 *)(arg0 + 0x48) * 0.25f;
    blk.u34[2] = *(f32 *)(arg0 + 0x4C) * 0.25f;
    blk.u40 = 0x0CCC0000;
    blk.u44 = 0xC8;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 6;
    blk.u48 = 0;
    blk.u4C = 0xFF;
    blk.u50 = 0;
    blk.u54 = 0x32;
    blk.u56 = 5;
    temp_v0 = effect3d_spawn_full(&blk, (s32)g_bullet_glow_sprite, 0x1B, 0, 0, 0x19, 0, 0, 0, 4, arg0[0xC], arg0[1]);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x110, &tmp, 4);
    }
    return temp_v0;
}

/* was func_151B8B5C */
s32 bullet_glow_follow_update(u8 *arg0)
{
    u8 *p = *(u8 **)(arg0 + 0x110);
    if (p != NULL) {
        *(vertex *)(arg0 + 0x34) = *(vertex *)(p + 0x38);
        *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * g_frame_step_f;
        *(f32 *)(arg0 + 0x44) += *(f32 *)(arg0 + 0x50) * g_frame_step_f;
        *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x54) * g_frame_step_f;
    } else {
        *(s32 *)(arg0 + 0x58) |= 1;
    }
    return 1;
}

/* P224: entry of draw table g_effect3d_draw_fns, whose dispatcher (func_1513DB70 area, game_169510) uses the result: the
   matching C is void, but its compiled code returns the callee's v0, so the NM variant returns it. */
/* was func_151B8BEC */
s32 bullet_glow_draw(s32 arg0, s16 arg1) {
    return beam_quad_build_b(arg0, arg1);
}

extern f32 g_fx_lod_scale_players; /* was D_800DCE54 */
/* was func_151B8C18 */
s32 bullet_smoke_emitter_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *p;
    struct_eu_EF410 sp18;

    p = arg0;

    sp18.unk0 = (s32) (p + 0x38);
    sp18.unk4 = (s32) (p + 0x3C);
    sp18.unk8 = (s32) (p + 0x40);
    sp18.unkC = 10.0f;
    sp18.unk10 = 0.2075f * g_fx_lod_scale_players;
    sp18.unk14 = 300;
    sp18.unk16 = 0;
    sp18.unk17 = 3;
    sp18.unk18 = 0;
    return point_emitter_spawn(&sp18, 0, arg1, arg2);
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 particle_puff_spawn(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */

/* was func_151B8CA4 */
void bullet_debris_spray_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    vec3_from_angles_byte((s16) (random_int() & 0xFF), (s16) ((random_int() % 65U) - 0x20), random_float() * 945.0f * 0.01f, &sp6C[3]);
    temp_f2 = (random_float() * 157.0f) + 604.0f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = temp_f2 * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
    particle_puff_spawn(&sp6C[6], sp6C, &sp6C[3], 1.0f, ((random_float() * 157.0f) + -151.0f) * 0.001f, (random_float() * 55.0f) + 75.0f, (random_int() % 26U) + 0x19, (random_int() % 101U) + 0x64, 0xA, 0x19, 0, -1, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1))); /* P95: float literal (asm passes the bits 0x3F800000) */
}

extern u8 g_bullet_smoke_textures[]; /* s32[4]: the 4 smoke textures; was D_800AA898 */
extern u8 g_vec3_zero[]; /* zero vector; was D_800A5860 */
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 random_int(void);
f32 random_float(void);

// smoke_puff_spawn: spawns one big smoke puff particle (random texture of the 4 in g_bullet_smoke_textures, half size
// 900..1400, white, alpha 0xFF, 300 frames, fade from 1 at rate 0xFF, draw 6 / update 5, random flip flags 0x40 /
// 0x80) at the object's position +0x38, in its room (+0xC) for its owner (+0x1) through particle_spawn_ex.
// Returns particle_spawn_ex's result (the new particle): P215, the asm returns it and port-b's asm caller projectile_fire
// stores it at its particle payload +0x84 (bullet_update dereferences it every frame).
/* was func_151B8EB8 */
s32 bullet_smoke_puff_spawn(u8 *obj) {
    s32 textures[4];
    struct {
        s32 handlers;   /* +0x00: 0x200005 */
        s32 u04;
        s16 texSet;     /* +0x08 */
        s16 life;       /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 color[4];    /* +0x14 */
        u8 u18[3];
        u8 alpha;       /* +0x1B */
        u8 u1C;
        u8 texture;     /* +0x1D */
        s16 fadeStart;  /* +0x1E */
        s16 fadeRate;   /* +0x20 */
        s16 u22;
        f32 u24;
        f32 halfW;      /* +0x28 */
        f32 halfH;      /* +0x2C */
        s32 pos[3];     /* +0x30 */
        s32 angle[3];   /* +0x3C */
        s32 vel[3];     /* +0x48 */
        f32 value;      /* +0x54 */
        s32 flags;      /* +0x58 */
        s32 u5C;
        u8 draw;        /* +0x60 */
        u8 update;      /* +0x61 */
        u8 blend;       /* +0x62 */
        s8 u63;
        s8 u64;
        u8 u65;
        u8 u66;
    } req;
    s32 flipA;
    s32 flipB;
    f32 s;

    textures[0] = ((s32 *) g_bullet_smoke_textures)[0];
    textures[1] = ((s32 *) g_bullet_smoke_textures)[1];
    textures[2] = ((s32 *) g_bullet_smoke_textures)[2];
    textures[3] = ((s32 *) g_bullet_smoke_textures)[3];
    req.texture = textures[random_int() & 3];
    req.texSet = 0x1303;
    req.handlers = 0x200005;
    req.u04 = 0;
    req.life = 300;
    req.u0C = 0;
    req.u10 = 0;
    req.color[0] = 0xFF;
    req.color[1] = 0xFF;
    req.color[2] = 0xFF;
    req.color[3] = 0xFF;
    req.u18[0] = 0xFF;
    req.u18[1] = 0xFF;
    req.u18[2] = 0xFF;
    req.alpha = 0xFF;
    req.u1C = 0xFF;
    s = random_float() * 500.0f + 900.0f;
    req.halfH = s;
    req.halfW = s;
    req.pos[0] = *(s32 *) (obj + 0x38);
    req.pos[1] = *(s32 *) (obj + 0x3C);
    req.pos[2] = *(s32 *) (obj + 0x40);
    req.angle[0] = ((s32 *) g_vec3_zero)[0];
    req.angle[1] = ((s32 *) g_vec3_zero)[1];
    req.angle[2] = ((s32 *) g_vec3_zero)[2];
    req.vel[0] = ((s32 *) g_vec3_zero)[0];
    req.vel[1] = ((s32 *) g_vec3_zero)[1];
    req.vel[2] = ((s32 *) g_vec3_zero)[2];
    req.fadeStart = 1;
    req.fadeRate = 0xFF;
    req.u22 = 1;
    req.value = 0.0f;
    req.u24 = 1.0f;
    flipA = (random_int() & 1) ? 0x40 : 0;
    flipB = (random_int() & 1) ? 0x80 : 0;
    req.flags = flipB | flipA | 0xC000 | 0x40000 | 0x800000;
    req.draw = 6;
    req.update = 5;
    req.blend = 0xFF;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 0;
    req.u5C = 0;
    req.u66 = 0xFF;
    return particle_spawn_ex((s32) &req, 1, 0, 0, obj[0xC], obj[1]);
}
