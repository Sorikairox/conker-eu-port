#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15132FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

void func_150BB760(u8 *arg0) {
    struct {
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        s16 uD0;
        s16 uD2;
        s8 uD4;
        u8 padD5[0x3];
        s32 uD8;
        s8 uDC;
        s8 uDD;
        s8 uDE;
        s8 uDF;
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s8 uE4;
        u8 padE5[0x1];
        s8 uE6;
        u8 padE7[0x1];
        u8 * uE8;
        u8 uEC;
        u8 padED[0x1];
        s16 uEE;
        s16 uF0;
    } sp;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    u8 sp63;
    f32 sp5C;
    f32 sp58;
    f32 sp50;
    f32 sp4C;
    u8 sp4B;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f6;
    u8 temp_t8;
    u8 temp_v0;

    if ((*(u8 *)((u8 *)arg0 + 4)) != 0x20) {
        return;
    }
    if ((arg0 != NULL) && ((*(s32 *)((u8 *)arg0 + 0)) != 0) && ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0)) {
        sp78 = (f32) (*(s16 *)((u8 *)arg0 + 0xE4));
        sp74 = (f32) (*(s16 *)((u8 *)arg0 + 0xE6));
        sp70 = angle_byte_cos(((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x3C));
        temp_f6 = temp_f2 * angle_byte_cos((((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) + 0x40) & 0xFF);
        sp68 = temp_f2 * sp70 * 0.5f;
        sp.uD2 = 1;
        sp.uCC = 0x29E9;
        sp.uD4 = 0;
        sp.uD8 = 0;
        sp.uDC = 0xFF;
        sp.uDD = 1;
        sp.uDE = 0;
        sp.uDF = 2;
        sp64 = temp_f6 * 0.5f;
        sp.uE0 = 0;
        sp.uE1 = 0;
        sp.uE2 = 0;
        sp.uE3 = 0;
        sp.uE4 = 0;
        sp.uE6 = 1;
        sp.uE8 = arg0;
        sp.u98 = 1.0f;
        sp.u9C = 1.0f;
        sp.uA0 = 1.0f;
        sp.uC4 = 0.0f;
        sp.uC8 = -1.0f;
        sp.uEE = 0x20;
        sp.uF0 = 7;
        sp.uEC = (*(u8 *)((u8 *)arg0 + 0x3B));
        temp_v0 = func_150ADA20();
        sp63 = temp_v0;
        sp5C = angle_byte_cos(temp_v0 & 0xFF);
        sp58 = angle_byte_cos((sp63 - 0x40) & 0xFF);
        temp_f2_2 = func_150ADA68() * sp78;
        sp50 = sp5C * temp_f2_2;
        sp4C = -sp58 * temp_f2_2;
        temp_t8 = (((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) - (func_150ADA20() & 0x3F)) - 0x20;
        sp4B = temp_t8;
        sp44 = angle_byte_cos(temp_t8 & 0xFF);
        sp40 = angle_byte_cos((sp4B - 0x40) & 0xFF);
        temp_f2_3 = (func_150ADA68() * 5.0f) + 3.0f;
        temp_f10 = sp40 * temp_f2_3;
        sp38 = temp_f10;
        sp34 = sp44 * temp_f2_3;
        temp_f12 = (func_150ADA68() * 0.05f) + 0.01f;
        sp30 = temp_f12;
        temp_f16 = func_150ADA68() * 0.05f;
        sp.u84 = temp_f12;
        temp_f2_4 = temp_f16 + 0.01f;
        sp.u88 = temp_f2_4;
        sp.u7C = (temp_f12 + temp_f2_4) * 0.5f;
        sp.u8C = func_150ADA68() * 360.0f;
        sp.u90 = func_150ADA68() * 360.0f;
        sp.u94 = func_150ADA68() * 360.0f;
        sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x14)) + sp50;
        sp.uA8 = (func_150ADA68() * sp74) + (*(f32 *)((u8 *)arg0 + 0x18)) + 4.0f;
        sp.uB0 = temp_f10 + sp68;
        sp.uAC = (*(f32 *)((u8 *)arg0 + 0x1C)) + sp4C;
        temp_f10_2 = (func_150ADA68() * 5.0f) + 3.0f;
        sp.uB8 = sp34 + sp64;
        sp.uB4 = temp_f10_2;
        sp.uBC = 25.0f - (func_150ADA68() * 50.0f);
        sp.uC0 = 25.0f - (func_150ADA68() * 50.0f);
        sp.uD0 = (func_150ADA20() & 0x1F) + 0x3C;
        sp.u80 = (func_150ADA68() * 0.2f) + 0.25f;
        func_15132FBC(&sp.u7C, 3, 0xFF, 0, 0xFF, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BB760.s")
#endif
#ifdef NON_MATCHING
/* func_15132FBC particle request (0x7C bytes; same layout as game_eu_E5830's BreakChunk) */
typedef struct {
    /* 0x00 */ f32 size;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 sizeX;
    /* 0x0C */ f32 sizeZ;
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 scale[3];
    /* 0x28 */ f32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8  u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  alpha;
    /* 0x61 */ u8  u61;
    /* 0x62 */ u8  u62[6];
    /* 0x68 */ u8  u68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  u6A;
    /* 0x6C */ void *owner;
    /* 0x70 */ u8  ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} ImpactChunk;

u8 *impact_spark_spawn(u8 *pos, u8 *vel, f32 scale, s16 sprite, u8 alpha, f32 speed, s32 tint, u8 fade, f32 sx, f32 sy,
                  u8 bright, u8 type, s32 argC, s16 t0, s16 t1, s32 owner, u8 arg10, s32 arg11);

/* sprite_vtx_quads_init / node_spawn_vtx_sprite sprite record (0xA8 bytes; only the fields set here are named) */
typedef struct {
    /* 0x00 */ u8  vtx[0x80];       /* two quads, filled by sprite_vtx_quads_init */
    /* 0x80 */ s32 alpha;
    /* 0x84 */ u8  pad84[4];
    /* 0x88 */ s16 u88;
    /* 0x8A */ s16 u8A;
    /* 0x8C */ s16 x;
    /* 0x8E */ s16 y;
    /* 0x90 */ s16 z;
    /* 0x92 */ s16 sizeX;
    /* 0x94 */ s16 sizeY;
    /* 0x96 */ s16 floorY;
    /* 0x98 */ s16 u98;
    /* 0x9A */ u8  pad9A[6];
    /* 0xA0 */ u8  texture;
    /* 0xA1 */ u8  uA1;
    /* 0xA2 */ s8  uA2;
    /* 0xA3 */ u8  padA3[5];
} ImpactShadow;

s32 sprite_vtx_quads_init(u8 *rec, s32 r, s32 g, s32 b, s32 a);
void *node_spawn_vtx_sprite(void *rec, u8 arg1, s32 arg2);

/* object_impact_debris: landing / crash effect of a type-0x20 object (func_1507D754 when its y speed (+0x20) is
 * not below -20): a sprite (texture 0x2E) at its position, 60 above the floor height +0x180, sized from +0xE4 /
 * +0xE6 (alpha 255, or fading with +0x184 when +0x1D4 is set); 6..9 debris chunks (sprite 1, life 120) and 10..13
 * sparks (impact_spark_spawn) thrown up and carried along by half the object's speed (+0x3C, heading +0x76); two dust
 * chunks (sprite 0) sized from +0x14C / +0x150; and sound 0x6590 at the object's position. The asm returns 1 for an
 * object of another type, else a scratch value; the only caller ignores it. */
void func_150BC03C(u8 *obj) {
    ImpactShadow shadow;
    ImpactChunk chunk;
    f32 vel[3];
    f32 pos[3];
    f32 height;
    f32 width;
    f32 ox;
    f32 oz;
    f32 s;
    f32 c;
    f32 ps;
    f32 pc;
    f32 r;
    f32 r2;
    f32 dx;
    f32 dz;
    f32 vx;
    f32 vz;
    f32 sx;
    f32 sz;
    s32 alpha;
    s32 n;
    s32 m;
    s32 a;
    s32 b;
    s32 rnd;
    s16 yaw;
    s16 pitch;
    s8 i;

    if (obj[4] != 0x20) {
        return;
    }
    if (obj == NULL || *(s32 *) obj == 0) {
        return;
    }
    height = *(s16 *) (obj + 0xE4);
    width = *(s16 *) (obj + 0xE6);
    n = (func_150ADA20() & 3) + 6;
    m = (func_150ADA20() & 3) + 10;
    s = angle_byte_cos((*(u16 *) (obj + 0x76) >> 8) & 0xFF);
    c = angle_byte_cos(((*(u16 *) (obj + 0x76) >> 8) + 0x40) & 0xFF);
    ox = *(f32 *) (obj + 0x3C) * s * 0.5f;
    oz = *(f32 *) (obj + 0x3C) * c * 0.5f;

    /* the sprite */
    alpha = 0xFF;
    if (*(s32 *) (obj + 0x1D4) != 0) {
        alpha = (0xFF - ((*(u32 *) (obj + 0x184) >> 5) << 6)) & 0xFF;
    }
    shadow.u8A = 0x80;
    shadow.u88 = 0;
    shadow.x = *(f32 *) (obj + 0x14);
    shadow.y = *(f32 *) (obj + 0x180) + 60.0f;
    shadow.z = *(f32 *) (obj + 0x1C);
    shadow.sizeX = height;
    shadow.sizeY = width;
    shadow.floorY = *(f32 *) (obj + 0x180);
    shadow.u98 = 0x34;
    shadow.texture = 0x2E;
    shadow.uA1 = 0;
    shadow.uA2 = -1;
    shadow.alpha = alpha;
    sprite_vtx_quads_init((u8 *) &shadow, 0xFF, 0xFF, 0xFF, 0xFF);
    node_spawn_vtx_sprite(&shadow, 0xFF, 0);

    /* debris chunks */
    chunk.sprite = 1;
    chunk.life = 120;
    chunk.flags = 0x29E9;
    chunk.u58 = 0;
    chunk.u5C = 0;
    chunk.alpha = 0xFF;
    chunk.u61 = 1;
    chunk.u62[0] = 0;
    chunk.u62[1] = 2;
    chunk.u62[2] = 0;
    chunk.u62[3] = 0;
    chunk.u62[4] = 0;
    chunk.u62[5] = 0;
    chunk.u68 = 0;
    chunk.u6A = 0;
    chunk.owner = NULL;
    chunk.ownerId = 0;
    chunk.u72 = 0x20;
    chunk.u74 = 7;
    chunk.u04 = 0.4f;
    chunk.scale[0] = 1.0f;
    chunk.scale[1] = 1.0f;
    chunk.scale[2] = 1.0f;
    chunk.spinZ = 0.0f;
    chunk.gravity = -1.5f;
    for (; n > 0; n--) {
        a = func_150ADA20() & 0xFF;
        s = angle_byte_cos(a);
        c = angle_byte_cos((a - 0x40) & 0xFF);
        r = func_150ADA68() * height;
        dx = s * r;
        dz = -c * r;

        a = func_150ADA20() & 0xFF;
        s = angle_byte_cos(a);
        c = angle_byte_cos((a - 0x40) & 0xFF);
        r = func_150ADA68() * 4.0f + 2.0f;
        vx = c * r;
        vz = s * r;

        sx = func_150ADA68() * 0.03f + 0.03f;
        sz = func_150ADA68() * 0.03f + 0.03f;
        chunk.sizeX = sx;
        chunk.sizeZ = sz;
        chunk.size = (sx + sz) * 0.5f;
        chunk.rot[0] = func_150ADA68() * 360.0f;
        chunk.rot[1] = func_150ADA68() * 360.0f;
        chunk.rot[2] = func_150ADA68() * 360.0f;
        chunk.pos[0] = *(f32 *) (obj + 0x14) + dx;
        chunk.pos[1] = func_150ADA68() * width + *(f32 *) (obj + 0x18) + 5.0f;
        chunk.pos[2] = *(f32 *) (obj + 0x1C) + dz;
        chunk.vel[0] = ox + vx;
        chunk.vel[1] = func_150ADA68() * 7.0f + 13.0f;
        chunk.vel[2] = oz + vz;
        chunk.spinX = 25.0f - func_150ADA68() * 50.0f;
        chunk.spinY = 25.0f - func_150ADA68() * 50.0f;
        func_15132FBC((s32) &chunk, 3, 0xFF, 0, 0xFF, 0);
    }

    /* sparks */
    for (; m > 0; m--) {
        r = func_150ADA68() * height;
        r2 = func_150ADA68() * 7.0f + 7.0f;
        a = func_150ADA20() & 0xFF;
        s = angle_byte_cos(a);
        c = angle_byte_cos((a - 0x40) & 0xFF);
        pos[0] = *(f32 *) (obj + 0x14) + s * r;
        pos[1] = func_150ADA68() * width + *(f32 *) (obj + 0x18) + 5.0f;
        vel[0] = c * r2 + ox;
        pos[2] = *(f32 *) (obj + 0x1C) - c * r;
        vel[1] = func_150ADA68() * 9.0f + 15.0f;
        vel[2] = s * r2 + oz;
        a = func_150ADA20();
        b = func_150ADA20();
        r = func_150ADA68();
        rnd = func_150ADA20();
        impact_spark_spawn((u8 *) pos, (u8 *) vel, 1.6f, (a & 7) + 0x19, (b & 0x7F) + 0x80, r * 0.2f * height + 13.0f,
                      (rnd & 3) + 2, 0, 1.0f, 1.0f, 1, 1, 0, 0x10, 0xF, 0, 0xFF, 0);
    }

    /* dust */
    chunk.sprite = 0;
    chunk.life = (func_150ADA20() & 0xF) + 0x10;
    chunk.u04 = 0.6f;
    chunk.rot[0] = *(f32 *) (obj + 0xB8);
    chunk.rot[1] = *(f32 *) (obj + 0x40);
    chunk.rot[2] = *(f32 *) (obj + 0xC4);
    chunk.flags = 0x39E8;
    chunk.scale[0] = 1.0f;
    chunk.scale[1] = 1.0f;
    chunk.scale[2] = 1.0f;
    chunk.spinZ = 0.0f;
    chunk.gravity = -1.6f;
    chunk.pos[0] = *(f32 *) (obj + 0x14);
    chunk.pos[1] = *(f32 *) (obj + 0x18);
    chunk.pos[2] = *(f32 *) (obj + 0x1C);
    chunk.size = *(f32 *) (obj + 0x14C) * 20.0f;
    chunk.sizeX = *(f32 *) (obj + 0x14C) + *(f32 *) (obj + 0x14C);
    chunk.sizeZ = chunk.sizeX;
    chunk.u58 = 0;
    chunk.u5C = 0;
    chunk.alpha = 0xFF;
    chunk.u61 = 1;
    chunk.u62[0] = 0;
    chunk.u62[1] = 0;
    chunk.u62[2] = 0;
    chunk.u62[3] = 0;
    chunk.u62[4] = 0;
    chunk.u62[5] = 0;
    chunk.u68 = 0;
    chunk.u6A = 0;
    chunk.owner = NULL;
    chunk.ownerId = 0;
    chunk.u72 = 0x10;
    chunk.u74 = 0xF;
    for (i = 0; i < 2; i++) {
        r = func_150ADA68() * 30.0f * *(f32 *) (obj + 0x150) + 10.0f;
        yaw = func_150ADA20() & 0x7F;
        pitch = -0x20 - (func_150ADA20() & 0x1F);
        s = angle_byte_cos(yaw & 0xFF);
        c = angle_byte_cos((yaw - 0x40) & 0xFF);
        ps = angle_byte_cos(pitch & 0xFF);
        pc = angle_byte_cos((pitch - 0x40) & 0xFF);
        chunk.vel[0] = r * ps * c + ox;
        chunk.vel[1] = -r * pc;
        chunk.vel[2] = r * ps * s + oz;
        chunk.spinX = 30.0f - func_150ADA68() * 60.0f;
        chunk.spinY = 30.0f - func_150ADA68() * 60.0f;
        func_15132FBC((s32) &chunk, 3, 0xFF, 0, 0xFF, 0);
    }
    func_10010F88(0xAA, 0x6590, 0, 0, 0, *(f32 *) (obj + 0x14), *(f32 *) (obj + 0x18), *(f32 *) (obj + 0x1C), 200,
                  2000);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BC03C.s")
#endif

#ifdef NON_MATCHING
/* object_impact_debris_hard: hard landing / crash effect of a type-0x20 object (func_1507D754 when its y speed
 * (+0x20) is below -20): 6..9 debris chunks (sprite 1) thrown out within the object's height (+0xE4) around its
 * position, upward speed 0.05 * the y speed, stop at the first failed spawn; 2..5 sparks (impact_spark_spawn, sprites
 * 0x19..0x20); then 0..2 dust chunks (sprite 0) sized from +0x14C, rotated like the object (+0xB8 / +0x40 / +0xC4).
 * The asm returns 1 for an object of another type, else a scratch value; the only caller ignores it. */
void func_150BC968(u8 *obj) {
    ImpactChunk chunk;
    f32 vel[3];
    f32 pos[3];
    f32 height;
    f32 s;
    f32 c;
    f32 r;
    f32 dx;
    f32 dz;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 sx;
    f32 sz;
    s32 n;
    s32 ok;
    s32 a;
    s32 b;
    s32 rnd;
    s16 pitch;
    s16 yaw;
    s8 i;
    s32 count;

    if (obj[4] != 0x20) {
        return;
    }
    if (obj == NULL || *(s32 *) obj == 0) {
        return;
    }
    height = *(s16 *) (obj + 0xE4);

    /* debris chunks */
    n = (func_150ADA20() & 3) + 6;
    chunk.sprite = 1;
    chunk.flags = 0x29E9;
    chunk.u58 = 0;
    chunk.u5C = 0;
    chunk.alpha = 0xFF;
    chunk.u61 = 1;
    chunk.u62[0] = 0;
    chunk.u62[1] = 2;
    chunk.u62[2] = 0;
    chunk.u62[3] = 0;
    chunk.u62[4] = 0;
    chunk.u62[5] = 0;
    chunk.u68 = 0;
    chunk.u6A = 0;
    chunk.owner = NULL;
    chunk.ownerId = 0;
    chunk.u72 = 0x20;
    chunk.u74 = 7;
    chunk.scale[0] = 1.0f;
    chunk.scale[1] = 1.0f;
    chunk.scale[2] = 1.0f;
    chunk.u04 = 0.4f;
    chunk.spinZ = 0.0f;
    chunk.gravity = -1.5f;
    ok = TRUE;
    while (n != 0) {
        a = func_150ADA20() & 0xFF;
        s = angle_byte_cos(a);
        c = angle_byte_cos((a - 0x40) & 0xFF);
        r = func_150ADA68() * height;
        dx = s * r;
        dz = -c * r;

        a = func_150ADA20() & 0xFF;
        s = angle_byte_cos(a);
        c = angle_byte_cos((a - 0x40) & 0xFF);
        r = func_150ADA68() * 4.0f + 4.0f;
        vx = c * r;
        vz = s * r;
        vy = *(f32 *) (obj + 0x20) * 0.05f;

        sx = func_150ADA68() * 0.04f + 0.02f;
        sz = func_150ADA68() * 0.04f + 0.02f;
        chunk.sizeX = sx;
        chunk.sizeZ = sz;
        chunk.size = (sx + sz) * 0.5f;
        chunk.rot[0] = func_150ADA68() * 360.0f;
        chunk.rot[1] = func_150ADA68() * 360.0f;
        chunk.rot[2] = func_150ADA68() * 360.0f;
        chunk.pos[0] = *(f32 *) (obj + 0x14) + dx;
        chunk.pos[1] = *(f32 *) (obj + 0x18);
        chunk.pos[2] = *(f32 *) (obj + 0x1C) + dz;
        chunk.vel[0] = vx;
        chunk.vel[1] = vy;
        chunk.vel[2] = vz;
        chunk.spinX = 25.0f - func_150ADA68() * 50.0f;
        chunk.spinY = 25.0f - func_150ADA68() * 50.0f;
        chunk.life = (func_150ADA20() & 0x3F) + 100;
        if (func_15132FBC((s32) &chunk, 3, 0xFF, 0, 0xFF, 0) == 0) {
            ok = FALSE;
        }
        n--;
        if (n == 0 || !ok) {
            break;
        }
    }

    /* sparks */
    n = (func_150ADA20() & 3) + 2;
    do {
        r = func_150ADA68() * 7.0f + 7.0f;
        a = func_150ADA20() & 0xFF;
        s = angle_byte_cos(a);
        c = angle_byte_cos((a - 0x40) & 0xFF);
        pos[0] = *(f32 *) (obj + 0x14);
        pos[1] = func_150ADA68() * 5.0f + *(f32 *) (obj + 0x18);
        pos[2] = *(f32 *) (obj + 0x1C);
        vel[0] = c * r;
        vel[1] = 0.0f;
        vel[2] = s * r;
        a = func_150ADA20();
        b = func_150ADA20();
        r = func_150ADA68();
        rnd = func_150ADA20();
        impact_spark_spawn((u8 *) pos, (u8 *) vel, 1.6f, (a & 7) + 0x19, (b & 0x7F) + 0x80, r * 0.2f * height + 5.0f,
                      (rnd & 1) + 2, 0, 1.0f, 1.0f, 1, 1, 0, 0x10, 0xF, 0, 0xFF, 0);
        n--;
    } while (n != 0);

    /* dust */
    a = func_150ADA20();
    b = func_150ADA20();
    count = (b & 1) + (a & 1);
    if (count == 0) {
        return;
    }
    chunk.sprite = 0;
    chunk.life = (func_150ADA20() & 0xF) + 0x10;
    chunk.u04 = 0.6f;
    chunk.rot[0] = *(f32 *) (obj + 0xB8);
    chunk.rot[1] = *(f32 *) (obj + 0x40);
    chunk.rot[2] = *(f32 *) (obj + 0xC4);
    chunk.flags = 0x39E8;
    chunk.scale[0] = 1.0f;
    chunk.scale[1] = 1.0f;
    chunk.scale[2] = 1.0f;
    chunk.spinZ = 0.0f;
    chunk.gravity = -1.6f;
    chunk.pos[0] = *(f32 *) (obj + 0x14);
    chunk.pos[1] = *(f32 *) (obj + 0x18);
    chunk.pos[2] = *(f32 *) (obj + 0x1C);
    chunk.size = *(f32 *) (obj + 0x14C) * 20.0f;
    chunk.sizeX = *(f32 *) (obj + 0x14C) + *(f32 *) (obj + 0x14C);
    chunk.sizeZ = chunk.sizeX;
    chunk.u58 = 0;
    chunk.u5C = 0;
    chunk.alpha = 0xFF;
    chunk.u61 = 1;
    chunk.u62[0] = 0;
    chunk.u62[1] = 0;
    chunk.u62[2] = 0;
    chunk.u62[3] = 0;
    chunk.u62[4] = 0;
    chunk.u62[5] = 0;
    chunk.u68 = 0;
    chunk.u6A = 0;
    chunk.owner = NULL;
    chunk.ownerId = 0;
    chunk.u72 = 0x10;
    chunk.u74 = 0xF;
    for (i = 0; i < count; i++) {
        r = func_150ADA68() * 5.0f + 8.0f;
        yaw = func_150ADA20() & 0x7F;
        pitch = 0x20 - (func_150ADA20() & 0x3F);
        s = angle_byte_cos(yaw & 0xFF);
        c = angle_byte_cos((yaw - 0x40) & 0xFF);
        dx = angle_byte_cos(pitch & 0xFF);
        dz = angle_byte_cos((pitch - 0x40) & 0xFF);
        chunk.vel[0] = r * dx * c;
        chunk.vel[1] = -r * dz;
        chunk.vel[2] = r * dx * s;
        chunk.spinX = 30.0f - func_150ADA68() * 60.0f;
        chunk.spinY = 30.0f - func_150ADA68() * 60.0f;
        func_15132FBC((s32) &chunk, 3, 0xFF, 0, 0xFF, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BC968.s")
#endif

#ifdef NON_MATCHING
void func_150BCBBC(u8 *arg0) {
    struct {
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        s16 uF8;
        s16 uFA;
        s8 uFC;
        u8 padFD[0x3];
        s32 u100;
        s8 u104;
        s8 u105;
        s8 u106;
        s8 u107;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s8 u10C;
        u8 pad10D[0x1];
        s8 u10E;
        u8 pad10F[0x1];
        s32 u110;
        s8 u114;
        u8 pad115[0x1];
        s16 u116;
        s16 u118;
        u8 pad11A[0xE];
        f32 u128;
        f32 u12C;
    } sp;
    f32 sp90;
    f32 sp8C;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f4_2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_s4;

    if ((*(u8 *)((u8 *)arg0 + 4)) != 0x20) {
        return;
    }
    if ((arg0 != NULL) && ((*(s32 *)((u8 *)arg0 + 0)) != 0)) {
        sp.u12C = (f32) (*(s16 *)((u8 *)arg0 + 0xE4));
        sp.u128 = (f32) (*(s16 *)((u8 *)arg0 + 0xE6));
        var_s2 = func_150ADA20() & 1;
        sp.uFA = 1;
        sp.uF8 = 0x96;
        sp.uF4 = 0x29E9;
        sp.uFC = 0;
        sp.u100 = 0;
        sp.u104 = 0xFF;
        sp.u105 = 1;
        sp.u106 = 0;
        sp.u107 = 2;
        sp.u108 = 0;
        sp.u109 = 0;
        sp.u10A = 0;
        sp.u10B = 0;
        sp.u10C = 0;
        sp.u10E = 0;
        sp.u110 = 0;
        sp.u114 = 0;
        sp.u116 = 0x20;
        sp.u118 = 7;
        var_s4 = 1;
        sp.uC0 = 1.0f;
        sp.uC4 = 1.0f;
        sp.uC8 = 1.0f;
        sp.uA8 = 0.3f;
        sp.uEC = 0.0f;
        sp.uF0 = -1.0f;
        if (var_s2 != 0) {
loop_6:
            temp_v0 = func_150ADA20();
            temp_f20 = angle_byte_cos(temp_v0 & 0xFF);
            temp_f22 = angle_byte_cos(((temp_v0 & 0xFF) - 0x40) & 0xFF);
            temp_f2 = func_150ADA68() * sp.u12C;
            sp90 = temp_f20 * temp_f2;
            sp8C = -temp_f22 * temp_f2;
            temp_f26 = (func_150ADA68() * 0.03f) + 0.01f;
            temp_f28 = (func_150ADA68() * 0.03f) + 0.01f;
            if (func_150ADA20() & 1) {
                var_s0 = ((8 - (func_150ADA20() & 0xF)) + ((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8)) & 0xFF;
            } else {
                var_s0 = (((8 - (func_150ADA20() & 0xF)) + ((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8)) - 0x80) & 0xFF;
            }
            temp_f20_2 = angle_byte_cos(var_s0 & 0xFF);
            temp_f22_2 = angle_byte_cos((var_s0 - 0x40) & 0xFF);
            temp_f4 = func_150ADA68() * 5.0f;
            sp.uAC = temp_f26;
            sp.uB0 = temp_f28;
            temp_f2_2 = temp_f4 + 3.0f;
            sp.uA4 = (temp_f26 + temp_f28) * 0.5f;
            sp.uB4 = func_150ADA68() * 360.0f;
            sp.uB8 = func_150ADA68() * 360.0f;
            sp.uBC = func_150ADA68() * 360.0f;
            sp.uCC = (*(f32 *)((u8 *)arg0 + 0x14)) + sp90;
            sp.uD0 = (func_150ADA68() * sp.u128) + (*(f32 *)((u8 *)arg0 + 0x18)) + 4.0f;
            sp.uD8 = temp_f22_2 * temp_f2_2;
            sp.uD4 = (*(f32 *)((u8 *)arg0 + 0x1C)) + sp8C;
            temp_f4_2 = func_150ADA68() * 5.0f;
            sp.uE0 = temp_f20_2 * temp_f2_2;
            sp.uDC = temp_f4_2 + 3.0f;
            sp.uE4 = 25.0f - (func_150ADA68() * 50.0f);
            sp.uE8 = 25.0f - (func_150ADA68() * 50.0f);
            var_s2 -= 1;
            if (func_15132FBC(&sp.uA4, 3, 0xFF, 0, 0xFF, 0) == 0) {
                var_s4 = 0;
            }
            if ((var_s2 != 0) && (var_s4 != 0)) {
                goto loop_6;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BCBBC.s")
#endif
/* P317: D_80089CD4's dispatcher type (wasm call_indirect); args 1..3 / 5 are unused, the code is unchanged */
s32 func_150BD498(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 *arg5) {
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) * 1.1f + arg4;
    if (*(f32 *)(arg0 + 0x48) > -2.0f) {
        *(f32 *)(arg0 + 0x44) = 0.0f;
        *(s32 *)(arg0 + 0x60) &= ~0x6F;
        *(f32 *)(arg0 + 0x48) = 0.0f;
        *(f32 *)(arg0 + 0x4C) = 0.0f;
    } else {
        f32 k = *(f32 *)(arg0 + 0x14);

        *(f32 *)(arg0 + 0x44) *= k;
        *(f32 *)(arg0 + 0x48) = -*(f32 *)(arg0 + 0x48) * k;
        *(f32 *)(arg0 + 0x4C) *= k;
        *(f32 *)(arg0 + 0x50) *= k;
        *(f32 *)(arg0 + 0x54) *= k;
        *(f32 *)(arg0 + 0x58) *= k;
    }
    return 1;
}

#ifdef NON_MATCHING
s32 func_15132BBC(void *, s32, s32, s32, s32, s32, s32);
s32 func_151307F0(s32 *, s32, s32, s32, s32, s32);
void func_1514470C(u8 *node, u8 *pos);
void func_15143794(s16, s16, f32, void *);
void func_151D58E4(struct17 *, f32, f32, f32, s16, s32, s32);
void *memcpy(void *, const void *, s32);

/* rodata of func_150BD550 (bit-exact copies: the NM link drops this file's .rodata / .late_rodata) */
static const u8 sBlastCyl[2] = { 0x4C, 0x4D };             /* D_800A0260: the two D_800D34B8 cylinders */
static const f32 sBlastSpinBase[1] = { -22.733002f };     /* D_800A02CC 0xC1B5DD30 */
static const f32 sBlastSpinRange[1] = { 45.466003f };     /* D_800A02D0 0x4235DD30 */
static const f32 sBlastSizeRange[1] = { 0.24700001f };    /* D_800A02D4 0x3E7CED92 */
static const f32 sBlastSizeBase[1] = { 0.20300001f };     /* D_800A02D8 0x3E4FDF3C */
static const f32 sBlastSpeedRange[1] = { 21.800001f };    /* D_800A02DC 0x41AE6667 */
static const f32 sBlastSpeedBase[1] = { 30.2f };          /* D_800A02E0 0x41F1999A */
static const f32 sBlastU4CRange[1] = { 1.1290001f };      /* D_800A02E4 0x3F908313 */
static const f32 sBlastU4CBase[1] = { -1.909f };          /* D_800A02E8 0xBFF45A1D */
static const f32 sSmokeU24[1] = { 1.012537f };            /* D_800A02EC 0x3F819AD0 */
static const f32 sSmokeTail[1] = { 0.917015f };           /* D_800A02F0 0x3F6AC17F */
static const f32 sSmokeSpeedRange[1] = { 45.600002f };    /* D_800A02F4 0x42366667 */
static const f32 sSmokeSizeBase[1] = { 1262.0f };         /* D_800A02F8 0x449DC000 */
static const f32 sSmokeSizeRange[1] = { 755.0f };         /* D_800A02FC 0x443CC000 */
static const f32 sSmokeSpeedBase[1] = { 18.800001f };     /* D_800A0300 0x41966667 */
static const f32 sSmokeU54Range[1] = { 0.559f };          /* D_800A0304 0x3F0F1AA0 */
static const f32 sSmokeU54Base[1] = { -0.777f };          /* D_800A0308 0xBF46E979 */

// blast_debris_and_smoke: an explosion at the two collision cylinders 0x4C / 0x4D: 13..21 tumbling debris pieces
// (func_15132BBC requests from a random point of either cylinder, func_1514470C, flying out at a random angle,
// func_15143794), 17..25 smoke puffs (func_151307F0, type 0x5103, its +0xA8 gets 0.917), then a light flash
// (func_151D58E4) and a shock ring (func_151D5404) at cylinder 0x4C. arg0 / owner are passed on to every spawn.
void func_150BD550(u8 arg0, s32 owner) {
    struct {
        f32 u00, u04;       /* 0x00: 1.0 */
        f32 size[2];        /* 0x08 */
        f32 rot[3];         /* 0x10: 0..360 */
        f32 u1C[3];         /* 0x1C: 1.0 */
        f32 pos[3];         /* 0x28 */
        f32 vel[3];         /* 0x34 */
        f32 spinA;          /* 0x40 */
        f32 u44;            /* 0x44: 0.0 */
        f32 spinB;          /* 0x48 */
        f32 u4C;            /* 0x4C */
        s32 u50;            /* 0x50: 0x12DE8 */
        s16 life;           /* 0x54 */
        s16 u56;            /* 0x56: 1 */
        u8 u58;             /* 0x58 */
        s32 u5C;            /* 0x5C */
        u8 u60[11];         /* 0x60 */
        s32 u6C;            /* 0x6C */
        u8 u70;             /* 0x70 */
        s16 u72;            /* 0x72: 0xC */
        s16 u74;            /* 0x74: 0x15 */
        s32 u78;            /* 0x78 */
    } debris;
    struct {
        s32 u00;            /* 0x00: 0x200005 */
        s32 u04;            /* 0x04 */
        s16 type;           /* 0x08: 0x5103 */
        s16 life;           /* 0x0A */
        s32 u0C;            /* 0x0C */
        s32 u10;            /* 0x10 */
        u8 u14[10];         /* 0x14: +0x17 = random 155..255 */
        s16 u1E;            /* 0x1E: 0x23 */
        s16 u20;            /* 0x20: 7 */
        s16 life2;          /* 0x22 */
        f32 u24;            /* 0x24 */
        f32 size[2];        /* 0x28 */
        f32 pos[3];         /* 0x30 */
        s32 dir[3];         /* 0x3C: D_800A5860 */
        f32 vel[3];         /* 0x48 */
        f32 u54;            /* 0x54 */
        s32 flags;          /* 0x58 */
        s32 u5C;            /* 0x5C */
        u8 u60[7];          /* 0x60 */
        s16 u68;            /* 0x68 */
        f32 u6C;            /* 0x6C */
    } smoke;
    f32 tail;
    u8 *cyl[2];
    f32 at[3];
    f32 at2[3];
    s32 r1, r2;
    f32 rf;
    s16 n;
    s32 bitA, bitB;
    s32 i;
    u8 *p;

    cyl[0] = D_800D34B8 + sBlastCyl[0] * 0x34;
    cyl[1] = D_800D34B8 + sBlastCyl[1] * 0x34;

    /* debris */
    n = func_150ADA20() % 9U + 13;
    debris.u50 = 0x12DE8;
    debris.u56 = 1;
    debris.u58 = 0;
    debris.u5C = 0;
    debris.u60[0] = 0xFF;
    debris.u60[1] = 8;
    for (i = 2; i < 8; i++) {
        debris.u60[i] = 0;
    }
    debris.u60[8] = 2;
    debris.u60[9] = 0xFF;
    debris.u60[10] = 2;
    debris.u6C = 0;
    debris.u70 = 0;
    debris.u72 = 0xC;
    debris.u74 = 0x15;
    debris.u78 = 0;
    debris.u00 = 1.0f;
    debris.u04 = 1.0f;
    debris.u1C[0] = 1.0f;
    debris.u1C[1] = 1.0f;
    debris.u1C[2] = 1.0f;
    debris.u44 = 0.0f;
    for (; n > 0; n--) {
        debris.life = func_150ADA20() % 26U + 40;
        debris.size[0] = debris.size[1] = func_150ADA68() * sBlastSizeRange[0] + sBlastSizeBase[0];
        debris.rot[0] = func_150ADA68() * 360.0f;
        debris.rot[1] = func_150ADA68() * 360.0f;
        debris.rot[2] = func_150ADA68() * 360.0f;
        debris.spinA = func_150ADA68() * sBlastSpinRange[0] + sBlastSpinBase[0];
        debris.spinB = func_150ADA68() * sBlastSpinRange[0] + sBlastSpinBase[0];
        func_1514470C(cyl[func_150ADA20() & 1], (u8 *) debris.pos);
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        rf = func_150ADA68();
        func_15143794((u32) r1 % 31 - 0x54, (u32) r2 % 26 - 0x2D, rf * sBlastSpeedRange[0] + sBlastSpeedBase[0],
                      debris.vel);
        debris.u4C = func_150ADA68() * sBlastU4CRange[0] + sBlastU4CBase[0];
        func_15132BBC(&debris, 3, 0xFF, 0, 0, arg0, owner);
    }

    /* smoke */
    n = func_150ADA20() % 9U + 17;
    smoke.u00 = 0x200005;
    smoke.type = 0x5103;
    smoke.u14[1] = 0xAA;
    smoke.u04 = 0;
    smoke.u0C = 0;
    smoke.u10 = 0;
    smoke.u14[0] = 0xD4;
    smoke.u14[2] = 8;
    smoke.u14[3] = 0xFF;
    smoke.u14[4] = 0x15;
    smoke.u14[5] = 4;
    smoke.u14[6] = 0;
    smoke.u14[8] = 0xFF;
    smoke.u14[9] = 0x6C;
    smoke.u1E = 0x23;
    smoke.u20 = 7;
    smoke.u24 = sSmokeU24[0];
    smoke.dir[0] = ((s32 *) D_800A5860)[0];
    smoke.dir[1] = ((s32 *) D_800A5860)[1];
    smoke.dir[2] = ((s32 *) D_800A5860)[2];
    bitA = (func_150ADA20() & 1) ? 0x40 : 0;
    bitB = (func_150ADA20() & 1) ? 0x80 : 0;
    smoke.flags = bitB | 7 | bitA | 0xCE00 | 0x20000 | 0x800000;
    smoke.u5C = 0;
    smoke.u60[0] = 8;
    smoke.u60[1] = 6;
    smoke.u60[2] = 0x10;
    smoke.u60[3] = 0xFF;
    smoke.u60[4] = 0xFF;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0xFF;
    smoke.u68 = 0;
    smoke.u6C = 0.0f;
    tail = sSmokeTail[0];
    for (; n > 0; n--) {
        smoke.life2 = smoke.life = func_150ADA20() % 31U + 0x1E;
        smoke.u14[7] = func_150ADA20() % 101U + 0x9B;
        smoke.size[0] = smoke.size[1] = func_150ADA68() * sSmokeSizeRange[0] + sSmokeSizeBase[0];
        func_1514470C(cyl[func_150ADA20() & 1], (u8 *) smoke.pos);
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        rf = func_150ADA68();
        func_15143794((u32) r1 % 41 - 0x59, (u32) r2 % 51 - 0x40, rf * sSmokeSpeedRange[0] + sSmokeSpeedBase[0],
                      smoke.vel);
        smoke.u54 = func_150ADA68() * sSmokeU54Range[0] + sSmokeU54Base[0];
        p = (u8 *) func_151307F0((s32 *) &smoke, 1, 0, 4, arg0, owner);
        if (p != NULL) {
            memcpy(p + 0xA8, &tail, 4);
        }
    }

    /* flash and shock ring at the first cylinder */
    at[0] = ((s16 *) cyl[0])[0];
    at[1] = ((s16 *) cyl[0])[1];
    at[2] = ((s16 *) cyl[0])[2];
    func_151D58E4((struct17 *) at, 0.0f, 1000.0f, 0.001f, 5, arg0, owner);
    at2[0] = ((s16 *) cyl[0])[0];
    at2[1] = ((s16 *) cyl[0])[1];
    at2[2] = ((s16 *) cyl[0])[2];
    func_151D5404((struct17 *) at2, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14, arg0, owner);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BD550.s")
#endif
