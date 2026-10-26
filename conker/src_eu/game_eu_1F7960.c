#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void aim_hud_spawn_track_mode(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void aim_hud_clear(u8 *arg0);
void aim_hud_bar_spawn(u8 *obj, s32 kind, s32 wide, s32 arg3, s32 group);
s32 sprite2d_spawn(void *, s32, s32, s32, s32, s32, s32);
void *memcpy(void *, const void *, unsigned int);

void aim_hud_tint_spawn(u8 *arg0);
s32 aim_hud_quad_reticle_spawn(u8 *, s32);
void aim_hud_crosshair_spawn(u8 *, u8);
s32 aim_hud_lens_reticle_spawn(u8 *, u8);
void aim_hud_side_bars_spawn(u8 *, u8, u8, s8, u8);
void aim_hud_gauge_spawn(u8 *, u8, u8, u8, u8, u8);
s32 aim_hud_gauge_marks_spawn(u8 *, s32, s32, s32, s32, s32);
void aim_hud_gauge_small_spawn(u8 *, u8, u8, u8);
extern u8 D_800CC3C8[];

/* was func_151CA150 */
void aim_hud_spawn_for_mode(u8 *arg0, s32 arg1)
{
  s32 v; s32 t;
  aim_hud_clear(arg0);
  v = *((u8 *) (((u8 *) (*((u8 **) (((u8 *) arg0) + 0x3D0)))) + 0x65));
  if (v != 0) { t = D_800CC3C8[v * 0x32C]; if ((t == 0x23) || (t == 0x8A)) arg1 = 0x1B; }
  switch (arg1)
  {
    case 0x23:
      aim_hud_bar_spawn(arg0, 1, 1, -1, 0xFF);
      aim_hud_quad_reticle_spawn(arg0, 0);
      return;

    case 0x1F:

    case 0x29:
      aim_hud_bar_spawn(arg0, 2, 1, -1, 0xFF);
      aim_hud_lens_reticle_spawn(arg0, 0);
      return;

    case 0xC:

    case 0x16:
      aim_hud_lens_reticle_spawn(arg0, 0);
      aim_hud_tint_spawn(arg0);
      return;

    case 0x1B:
      if (D_800BE9F0 == 0x27)
    {
      aim_hud_spawn_track_mode(arg0, 1, -1, 0xFF, 1);
      return;
    }
      if (D_80082FA0 == 0)
    {
      aim_hud_gauge_spawn(arg0, 0xFF, 0, 0, 1, 0xFF);
      aim_hud_gauge_marks_spawn(arg0, 0xFF, 0, 0, 1, 0xFF);
    }
    else
    {
      aim_hud_gauge_small_spawn(arg0, 0xFF, 0, 0);
    }
      aim_hud_bar_spawn(arg0, 3, 1, -1, 0xFF);
      aim_hud_side_bars_spawn(arg0, 1, 1, -1, 0xFF);
      return;

    case 0x24:
      aim_hud_bar_spawn(arg0, 0, 1, -1, 0xFF);
      aim_hud_quad_reticle_spawn(arg0, 0);
      return;

    case 0x12:

    case 0x18:

    case 0x38:

    case 0x3B:
      break;

    case 9:

    default:
      aim_hud_crosshair_spawn(arg0, 0);
      break;

  }

}

void sprite2d_emitter_spawn(s32, u8, s32);
void aim_hud_slot_rows_spawn(u8 *, u8, s8, u8);

/* was func_151CA398 */
void aim_hud_spawn_track_mode(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s1;
    s32 temp_s2;

    temp_s1 = arg3 & 0xFF;
    temp_s2 = arg1 & 0xFF;
    aim_hud_bar_spawn(arg0, 4, temp_s2 & 0xFF, (s32) (s8) arg2, temp_s1);
    aim_hud_gauge_spawn(arg0, 0U, 0x32U, 0xFFU, (u8) temp_s2, (u8) temp_s1);
    aim_hud_gauge_marks_spawn(arg0, 0, 0x32, 0xFF, temp_s2, temp_s1);
    aim_hud_slot_rows_spawn(arg0, temp_s2 & 0xFF, (s8) arg2, temp_s1 & 0xFF);
    sprite2d_emitter_spawn(arg0, temp_s1 & 0xFF, arg4);
    aim_hud_side_bars_spawn(arg0, 2U, temp_s2 & 0xFF, (s8) arg2, (u8) temp_s1);
    if (D_800BE9F0 == 0x27) {
        D_8008D0A0 = 1;
    }
}
void fb_fx_broadcast(s32, u8);
void screen_tint_broadcast(s32, u8);

/* was func_151CA484 */
void aim_hud_clear(u8 *arg0) {
    struct {
        u8 * u24;
    } sp;

    sp.u24 = arg0;
    fb_fx_broadcast(&sp.u24, 0x21);
    sprite2d_broadcast(&sp.u24, 0x21U);
    screen_tint_broadcast(&sp.u24, 0x21);
    effect_nodes_broadcast((s32) &sp.u24, 0x21U);
    D_8008D0A0 = 0;
}
/* rodata of aim_hud_bar_spawn.s (D_800AB060..D_800AB268); D_800AB164 / 16C / 18C / 194 are also read by
   aim_hud_side_bars_spawn and the hud_slot_row spawner below, so they stay exported. */
static const f32 sBarColourInit[4] = { 255.0f, 0.0f, 0.0f, 255.0f };            /* D_800AB060 */
static const f32 sBarColour[5][4] = {                                           /* D_800AB070 */
    { 0.0f, 255.0f, 0.0f, 130.0f }, { 0.0f, 255.0f, 0.0f, 130.0f }, { 0.0f, 255.0f, 0.0f, 130.0f },
    { 255.0f, 255.0f, 0.0f, 90.0f }, { 0.0f, 0.0f, 180.0f, 90.0f },
};
static const f32 sBarBackColour[5][4] = {                                       /* D_800AB0C0 */
    { 0.0f, 255.0f, 0.0f, 65.0f }, { 0.0f, 255.0f, 0.0f, 65.0f }, { 0.0f, 255.0f, 0.0f, 65.0f },
    { 255.0f, 0.0f, 0.0f, 65.0f }, { 0.0f, 0.0f, 180.0f, 65.0f },
};
static const f32 sBarHeight[5] = { 2.0f, 2.0f, 2.0f, 1.0f, 1.0f };              /* D_800AB110 */
static const f32 sBarWidth[5] = { 60.0f, 60.0f, 60.0f, 30.0f, 30.0f };          /* D_800AB124 */
static const f32 sBarX[5] = { -90.0f, -90.0f, -90.0f, 37.0f, 37.0f };           /* D_800AB138 */
static const f32 sBarLayoutY[5][2] = {                                          /* D_800AB14C (+164, +16C) */
    { -50.0f, -62.0f }, { -38.0f, -46.5f }, { -38.0f, -46.0f }, { -25.0f, -31.0f }, { -25.0f, -31.0f },
};
static const f32 sBarLayoutScale[5][2] = {                                      /* D_800AB174 (+18C, +194) */
    { 0.02f, 0.016129032f }, { 0.02631579f, 0.021505376f }, { 0.02631579f, 0.02173913f },
    { 0.04f, 0.032258064f }, { 0.04f, 0.032258064f },
};
static const f32 sBarRange[1] = { 99999.0f };                                   /* D_800AB268 */
const f32 D_800AB164[2] = { -25.0f, -31.0f };
const f32 D_800AB16C[2] = { -25.0f, -31.0f };
const f32 D_800AB18C[2] = { 0.04f, 0.032258064f };
const f32 D_800AB194[2] = { 0.04f, 0.032258064f };

/* IDO's f32 -> u32 conversion: <= -1, >= 2^32 and NaN give 0xFFFFFFFF (undefined in C, wasm traps) */
#define BAR_F2U(f) ((!((f) > -1.0f) || (f) >= 4294967296.0f) ? 0xFFFFFFFFU : (u32) (f))

/* handler block copied to sprite + 0x70 (0x58 bytes) */
typedef struct {
    /* 0x00 */ u8 *owner;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ s8 mode;
    /* 0x0D */ s8 part;
    /* 0x0E */ u8 pad0E[0xA];
    /* 0x18 */ f32 layoutY;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 layoutScale;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ f32 range;
    /* 0x2C */ f32 colourInit[4];
    /* 0x3C */ f32 colour[4];
    /* 0x4C */ f32 widthM1;
    /* 0x50 */ u8 pad50[4];
    /* 0x54 */ s8 arg3;
    /* 0x55 */ u8 pad55[3];
} BarBlockCA4E8;

/* sprite request for sprite2d_spawn */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 h;
    /* 0x0C */ f32 w;
    /* 0x10 */ u8 u10;
    /* 0x11 */ u8 pad11;
    /* 0x12 */ s16 span;
    /* 0x14 */ u16 flags;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s8 u1A;
    /* 0x1B */ u8 rgba[4];
    /* 0x1F */ u8 u1F;
    /* 0x20 */ u8 u20[4];
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ s32 u2C;
    /* 0x30 */ s32 u30;
    /* 0x34 */ s32 u34;
    /* 0x38 */ s32 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ s8 u40;
    /* 0x41 */ s8 u41;
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ u8 player;
    /* 0x45 */ u8 pad45[3];
} BarSpecCA4E8;

// hud_bar_spawn: spawns a two-part HUD bar of kind `kind` (0..4) for player obj + 0x23D (list 0x58): first the
// front sprite (colour sBarColour[kind], height sBarHeight, width sBarWidth at x sBarX, part 3), then the back
// sprite (colour sBarBackColour[kind], both sizes + 2, part 0). Each sprite gets the 0x58-byte handler block at
// +0x70: owner, mode (0 when `arg3` is -1, else 4), layout constants (second entry when D_80082FA0 == 1), the
// colour and `arg3`. `wide` adds flag 0x40. The asm leaves memcpy's / sprite2d_spawn's v0; no caller reads it.
/* was func_151CA4E8 */
void aim_hud_bar_spawn(u8 *obj, s32 kind, s32 wide, s32 arg3, s32 group) {
    BarBlockCA4E8 blk;
    BarSpecCA4E8 spec;
    u8 *spr;
    s32 k = (u8) kind;
    s32 alt = (D_80082FA0 == 1);
    s32 i;

    arg3 = (s8) arg3;
    for (i = 0; i < 4; i++) {
        blk.colourInit[i] = sBarColourInit[i];
        blk.colour[i] = sBarColour[k][i];
    }
    blk.widthM1 = sBarWidth[k] - 1.0f;
    blk.u04 = 0.0f;
    blk.part = 0;
    blk.u08 = 130.0f;
    blk.owner = obj;
    blk.mode = (arg3 == -1) ? 0 : 4;
    blk.arg3 = arg3;

    spec.span = 300;
    spec.u16 = 1;
    spec.u1F = 0xFF;
    spec.u18 = 0xFF;
    spec.u1A = 7;
    spec.u20[3] = 0xFF;
    spec.u20[0] = 0xFF;
    spec.u20[1] = 0xFF;
    spec.u20[2] = 0xFF;
    spec.u2C = 0x1F0601;
    spec.u24 = 0;
    spec.u28 = 0x200004;
    spec.u38 = 0x80;
    spec.u3C = 0x20;
    spec.u40 = 0;
    spec.u41 = 0xA;
    spec.y = 0.0f;
    spec.w = sBarWidth[k];
    spec.u10 = 0xFF;
    spec.player = obj[0x23D];
    spec.x = sBarX[k];
    spec.h = sBarHeight[k];
    spec.flags = ((u8) wide ? 0x40 : 0) | 0x10 | (1 << (obj[0x23D] + 11));
    spec.u30 = 8;
    spec.u34 = 0x54;
    blk.u1C = 0.0f;
    blk.part = 3;
    blk.range = sBarRange[0];
    blk.layoutY = sBarLayoutY[k][alt];
    blk.layoutScale = sBarLayoutScale[k][alt];
    for (i = 0; i < 4; i++) {
        spec.rgba[i] = BAR_F2U(sBarColour[k][i]);
    }
    spr = (u8 *) sprite2d_spawn(&spec, 8, 0, 0, 0x58, (u8) group, 1);
    if (spr != NULL) {
        memcpy(spr + 0x70, &blk, 0x58);
    }

    blk.part = 0;
    spec.h = sBarHeight[k] + 2.0f;
    spec.w = sBarWidth[k] + 2.0f;
    for (i = 0; i < 4; i++) {
        spec.rgba[i] = BAR_F2U(sBarBackColour[k][i]);
    }
    spr = (u8 *) sprite2d_spawn(&spec, 0, 0, 0, 0x58, (u8) group, 0);
    if (spr != NULL) {
        memcpy(spr + 0x70, &blk, 0x58);
    }
}

/* was func_151CAC50 */
s32 aim_hud_quad_reticle_spawn(u8 *arg0, s32 arg1) {
    struct {
        u8 * u44;
        f32 u48;
        f32 u4C;
        s8 u50;
        s8 u51;
        u8 pad52[0xA];
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0x30];
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        s8 uB0;
        u8 padB1[0x1];
        s16 uB2;
        u16 uB4;
        s16 uB6;
        s16 uB8;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        s8 uBD;
        s8 uBE;
        s8 uBF;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s8 uE0;
        s8 uE1;
        u8 padE2[0x2];
        u8 uE4;
    } sp;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    u16 temp_t2;
    u16 temp_t6;

    temp_s0 = arg1 & 0xFF;
    sp.u51 = 0;
    sp.u50 = 0;
    sp.uAC = 25.0f;
    sp.uA8 = 25.0f;
    sp.u44 = arg0;
    sp.u48 = 0.0f;
    sp.u4C = 130.0f;
    if (D_80082FA0 > 0) {
        sp.uB0 = 0x73;
    } else {
        sp.uB0 = 0x5D;
    }
    sp.uB2 = 0x12C;
    temp_t6 = (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB)) | 0x50;
    sp.uB6 = 1;
    sp.uBA = 7;
    sp.uBC = 0xFF;
    sp.uBE = 0x82;
    sp.uBF = 0xFF;
    sp.uC0 = 0xFF;
    sp.uC1 = 0xFF;
    sp.uC2 = 0xFF;
    sp.uD0 = 8;
    sp.uB4 = temp_t6;
    sp.uB8 = 0xFF;
    sp.uBB = 0;
    sp.uBD = 0;
    sp.uC3 = 0xFF;
    sp.uC4 = 0;
    sp.uC8 = 0x200004;
    sp.uCC = 0x1F0601;
    sp.uD4 = 0x44;
    sp.uD8 = 0x80;
    sp.uDC = 0x20;
    sp.uE0 = 0;
    sp.uE1 = 0xA;
    temp_t2 = temp_t6 & 0xFFF9;
    sp.uB4 = temp_t2;
    sp.uB4 = temp_t2 | 6;
    sp.uA0 = 25.0f;
    sp.uA4 = 25.0f;
    sp.uE4 = (*(u8 *)((u8 *)arg0 + 0x23D));
    if (temp_s0 != 0) {
        var_v0_2 = 4;
    } else {
        var_v0_2 = 0;
    }
    temp_v0 = sprite2d_spawn(&sp.uA0, var_v0_2 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u44, 0x58U);
    }
    sp.uB4 = (sp.uB4 & 0xFFF9) | 4;
    sp.uA0 = -25.0f;
    sp.uA4 = 25.0f;
    if (temp_s0 != 0) {
        var_v0_3 = 4;
    } else {
        var_v0_3 = 0;
    }
    temp_v0_2 = sprite2d_spawn(&sp.uA0, var_v0_3 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u44, 0x58U);
    }
    sp.uB4 &= 0xFFF9;
    sp.uA0 = -25.0f;
    sp.uA4 = -25.0f;
    if (temp_s0 != 0) {
        var_v0_4 = 4;
    } else {
        var_v0_4 = 0;
    }
    temp_v0_3 = sprite2d_spawn(&sp.uA0, var_v0_4 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &sp.u44, 0x58U);
    }
    sp.uB4 = (sp.uB4 & 0xFFF9) | 2;
    sp.uA0 = 25.0f;
    sp.uA4 = -25.0f;
    if (temp_s0 != 0) {
        var_v0_5 = 4;
    } else {
        var_v0_5 = 0;
    }
    temp_v0_4 = sprite2d_spawn(&sp.uA0, var_v0_5 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_4 != 0) {
        memcpy(temp_v0_4 + 0x70, &sp.u44, 0x58U);
    }
    sp.uA0 = 0.0f;
    sp.uA4 = 0.0f;
    sp.uAC = 3.0f;
    sp.uA8 = 3.0f;
    sp.uB0 = 0x99;
    sp.uB4 = (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB)) | 0x50;
    sp.uD0 = 8;
    sp.uD4 = 0x44;
    sp.u6C = 99999.0f;
    if (D_80082FA0 == 1) {
        sp.u5C = -62.0f;
    } else {
        sp.u5C = -50.0f;
    }
    sp.u60 = 0.0f;
    if (D_80082FA0 == 1) {
        sp.u64 = 0.016129032f;
    } else {
        sp.u64 = 0.02f;
    }
    var_s0 = 0;
    sp.u68 = 0.0f;
    do {
        var_v0 = sprite2d_spawn(&sp.uA0, 7, 0, 0, 0x58, 0xFF, 1);
        if (var_v0 != 0) {
            var_v0 = memcpy(var_v0 + 0x70, &sp.u44, 0x58U);
        }
        var_s0 += 1;
        sp.u68 += 0.5235988f;
    } while (var_s0 != 0xC);
    return var_v0;
}
/* was func_151CB07C */
void aim_hud_sprite_on_message(struct102 *arg0, u8 **arg1, u8 arg2) {
    void (*f)(void *, u8 **, u8);
    u8 *v;

    if (arg2 == 0x21) {
        if (*(s32 *)((u8 *)arg0 + 0x70) == (s32)arg1[0]) {
            node_destroy(arg0);
        }
    dummy_label: ; // fakematch: empty label after the first arm makes IDO fill the b delay slot like the original
    } else if (arg2 == 0) {
        v = arg1[0];
        if (*(s32 *)((u8 *)arg0 + 0x70) == *(s32 *)(v + 0x318)) {
            node_destroy(arg0);
        }
    }
    f = D_8008FFB0[*(u8 *)((u8 *)arg0 + 0x7D)];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

s32 sprite2d_spawn(void *, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 u0;
    f32 u4;
    f32 u8;
    f32 uC;
    u8 u10;
    s16 u12;
    u16 u14;
    s16 u16;
    s16 u18;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    u8 u1E;
    u8 u1F;
    u8 u20;
    u8 u21;
    u8 u22;
    u8 u23;
    s32 u24;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s32 u38;
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    u8 u44;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
} Spawn559A;

typedef struct {
    u8 *u0;
    f32 u4;
    f32 u8;
    u8 uC;
    u8 uD;
    u8 uE;
    u8 padF;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    u8 pad24[0x30];
    s8 u54;
    u8 pad55[3];
} Spawn559B;

/* was func_151CB128 */
void aim_hud_crosshair_spawn(u8 *arg0, u8 arg1) {
    Spawn559A a;
    s32 pad2; // fakematch: 4-byte hole between blocks
    Spawn559B b;
    f32 f;
    s32 ret;

    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    b.uD = 0;
    b.uC = 0;
    if (D_80082FA0 > 0) {
        f = 2.0f;
    } else {
        f = 1.0f;
    }
    a.u10 = 0x64;
    a.u12 = 0x12C;
    a.uC = f * 12.0f;
    a.u8 = a.uC;
    a.u14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = 0xFF;
    a.u1C = 0xC8;
    a.u1D = 0;
    a.u1E = 0x82;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 8;
    a.u34 = 0x44;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0xA;
    a.u0 = 0.0f;
    a.u4 = 0.0f;
    a.u44 = arg0[0x23D];
    ret = sprite2d_spawn(&a, (u8)(arg1 ? 4 : 0), 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
}

s32 fb_fx_spawn(s8 *, s32, s32, s32);

/* was func_151CB2D8 */
s32 aim_hud_lens_reticle_spawn(u8 *arg0, u8 arg1) {
    struct {
        u8 * u30;
        u8 * u34;
        s32 u38;
        s32 u3C;
        s32 u40;
        s8 u44;
        s8 u45;
        s8 u46;
        u8 pad47[0x1];
        s16 u48;
        s8 u4A;
        u8 pad4B[0x1];
        u8 * u4C;
        f32 u50;
        f32 u54;
        s8 u58;
        s8 u59;
        u8 pad5A[0x4E];
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        s8 uB8;
        u8 padB9[0x1];
        s16 uBA;
        u16 uBC;
        s16 uBE;
        s16 uC0;
        s8 uC2;
        s8 uC3;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s32 uE0;
        s32 uE4;
        s8 uE8;
        s8 uE9;
        u8 padEA[0x2];
        u8 uEC;
    } sp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    u16 temp_t2;
    u16 temp_t6;
    u8 *temp_t5;

    sp.u59 = 0;
    sp.u58 = 0;
    sp.uB4 = 25.0f;
    sp.uB0 = 25.0f;
    sp.u4C = arg0;
    sp.u50 = 0.0f;
    sp.u54 = 130.0f;
    if (D_80082FA0 > 0) {
        sp.uB8 = 0x72;
    } else {
        sp.uB8 = 0x65;
    }
    sp.uBA = 0x12C;
    temp_t6 = (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB)) | 0x50;
    sp.uBE = 1;
    sp.uC2 = 7;
    sp.uC4 = 0xFF;
    sp.uC6 = 0x82;
    sp.uC8 = 0xFF;
    sp.uC7 = 0xFF;
    sp.uC9 = 0xFF;
    sp.uCA = 0xFF;
    sp.uD8 = 8;
    sp.uE0 = 0x80;
    sp.uBC = temp_t6;
    sp.uC0 = 0xFF;
    sp.uC3 = 0;
    sp.uC5 = 0;
    sp.uCB = 0xFF;
    sp.uCC = 0;
    sp.uD0 = 0x200004;
    sp.uD4 = 0x1F0601;
    sp.uDC = 0x44;
    sp.uE4 = 0x20;
    sp.uE8 = 0;
    sp.uE9 = 0xA;
    temp_t2 = temp_t6 & 0xFFF9;
    sp.uBC = temp_t2;
    sp.uBC = temp_t2 | 6;
    sp.uA8 = 25.0f;
    sp.uAC = 25.0f;
    sp.uEC = (*(u8 *)((u8 *)arg0 + 0x23D));
    if (arg1 != 0) {
        var_v0_2 = 4;
    } else {
        var_v0_2 = 0;
    }
    temp_v0 = sprite2d_spawn(&sp.uA8, var_v0_2 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u4C, 0x58U);
    }
    sp.uBC = (sp.uBC & 0xFFF9) | 4;
    sp.uA8 = -25.0f;
    sp.uAC = 25.0f;
    if (arg1 != 0) {
        var_v0_3 = 4;
    } else {
        var_v0_3 = 0;
    }
    temp_v0_2 = sprite2d_spawn(&sp.uA8, var_v0_3 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u4C, 0x58U);
    }
    sp.uBC &= 0xFFF9;
    sp.uA8 = -25.0f;
    sp.uAC = -25.0f;
    if (arg1 != 0) {
        var_v0_4 = 4;
    } else {
        var_v0_4 = 0;
    }
    temp_v0_3 = sprite2d_spawn(&sp.uA8, var_v0_4 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &sp.u4C, 0x58U);
    }
    sp.uBC = (sp.uBC & 0xFFF9) | 2;
    sp.uA8 = 25.0f;
    sp.uAC = -25.0f;
    if (arg1 != 0) {
        var_v0_5 = 4;
    } else {
        var_v0_5 = 0;
    }
    var_v0 = sprite2d_spawn(&sp.uA8, var_v0_5 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x70, &sp.u4C, 0x58U);
    }
    if (D_800BE616 == 0) {
        sp.u30 = arg0;
        temp_t5 = ((*(u8 *)((u8 *)arg0 + 0x23D)) * 0x180) + D_800BE628;
        sp.u34 = temp_t5;
        sp.u3C = (s32) ((*(f32 *)((u8 *)temp_t5 + 0x34)) - 12.0f);
        sp.u44 = 0xE;
        sp.u45 = -1;
        sp.u46 = 1;
        sp.u48 = 0x12C;
        sp.u4A = 1;
        sp.u40 = (s32) ((*(f32 *)((u8 *)temp_t5 + 0x38)) - 12.0f) * D_800BE620;
        var_v0 = fb_fx_spawn(&sp.u44, 0x498, 0xFF, 1);
        if (var_v0 != 0) {
            sp.u38 = var_v0 + 0x30;
            var_v0 = memcpy(var_v0 + 0x18, &sp.u30, 0x14U);
        }
    }
    return var_v0;
}
extern u8 D_800BEAC0;
extern u8 D_800BEAC1;
extern u8 D_800BEEE2;
extern s32 D_800BE620;
f32 curve_table_lookup(f32, f32, f32);

/*
 * fb_lens_warp_draw: framebuffer handler 1 of the type-0x34 effect list (called through D_8008B478 by
 * fb_fx_apply_all just before the buffer swap, args (effect, framebuffer)). Saves the 24x24 pixel block at
 * effect+0x24 + effect+0x28 into the effect's buffer (effect+0x20), then writes it back mirrored in the four
 * quadrants around the target's screen point (target = effect+0x1C, x / y floats at +0x34 / +0x38) with a
 * radial lens falloff from curve_table_lookup, sampling the saved block at 12 + offset * scale.
 * Skipped while D_800BEAC0 / D_800BEAC1 / D_800BEEE2 are set.
 */
/* was func_151CB6C0 */
void fb_lens_warp_draw(u8 *arg0, u16 *fb) {
    u8 *target;
    u16 *buf;
    s32 src;
    s32 i;
    f32 y, x;
    f32 ry, inv, k;
    f32 r, s;
    f32 dy, dx, sx, sy;
    s32 rowA, rowB, colA, colB;
    s32 u0, u1, v0, v1;

    if (D_800BEAC0 != 0 || D_800BEAC1 != 0 || D_800BEEE2 != 0) {
        return;
    }
    target = *(u8 **)(arg0 + 0x1C);
    src = *(s32 *)(arg0 + 0x24) + *(s32 *)(arg0 + 0x28);
    for (i = 0; i < 24; i++) {
        memcpy(*(u16 **)(arg0 + 0x20) + i * 24, fb + src, 48);
        src += D_800BE620;
    }
    for (y = -1.0f; y < 0.0f; y += 0.083333336f) {
        ry = curve_table_lookup(fabsf(y), 1.0f, 1.0f);
        if (ry == 0.0f) {
            continue;
        }
        dy = y * 12.0f;
        rowA = (s32)(*(f32 *)(target + 0x38) + dy) * D_800BE620;
        rowB = (s32)(*(f32 *)(target + 0x38) - dy) * D_800BE620;
        x = -ry;
        if (!(x < 0.0f)) {
            continue;
        }
        inv = 1.0f / ry;
        k = 1.0f - (1.0f - ry * 0.669312179f);
        do {
            r = curve_table_lookup(fabsf(x), ry, inv);
            dx = x * 12.0f;
            colA = (s32)(*(f32 *)(target + 0x34) + dx);
            colB = (s32)(*(f32 *)(target + 0x34) - dx);
            s = 1.0f - r * k;
            sx = x * s * 12.0f;
            sy = y * s * 12.0f;
            u0 = (s32)(sx + 12.0f);
            v0 = (s32)(sy + 12.0f) * 24;
            u1 = (s32)(12.0f - sx);
            v1 = (s32)(12.0f - sy) * 24;
            buf = *(u16 **)(arg0 + 0x20);
            fb[rowA + colA] = buf[u0 + v0];
            fb[rowA + colB] = buf[u1 + v0];
            fb[rowB + colB] = buf[u1 + v1];
            fb[rowB + colA] = buf[u0 + v1];
            x += 0.083333336f;
        } while (x < 0.0f);
    }
}

/* was func_151CBA4C */
void aim_fbfx_on_message(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x18) == *arg1) {
            node_destroy(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x18) == *(u8 **)(p + 0x318)) {
            node_destroy(arg0);
        }
    }
}

/* was func_151CBAC0 */
void aim_hud_fade_update(u8 *arg0) {
    f32 target;
    u8 *t;
    u8 *p;

    p = arg0 + 0x70;
    t = *(u8 **)p;
    if ((**(u16 **)(t + 0x36C) & 0x2000) && *(u16 *)(*(u8 **)(t + 0x3D4) + 0x19E) == 0) {
        target = *(f32 *)(p + 8);
    } else {
        target = 0.0f;
    }
    *(f32 *)(p + 4) += (target - *(f32 *)(p + 4)) * 0.4f;
    arg0[0x2E] = *(f32 *)(p + 4);
}

/* sprite2d_spawn's sprite spec (0x58 bytes). */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x12 */ s16 span;
    /* 0x14 */ u16 flags;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ u8 u1A;
    /* 0x1B */ u8 col[9];
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ s32 u2C;
    /* 0x30 */ s32 u30;
    /* 0x34 */ s32 u34;
    /* 0x38 */ s32 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ u8 player;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpriteSpecCBBAC;

/* the 0x58-byte block copied to the sprite's +0x70 (its handler state) */
typedef struct {
    /* 0x00 */ u8 *owner;
    /* 0x04 */ f32 alphaA;
    /* 0x08 */ f32 alphaB;
    /* 0x0C */ u8 mode;
    /* 0x0D */ u8 type;
    /* 0x0E */ u8 side;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ u8 pad24[0x30];
    /* 0x54 */ s8 u54;
    /* 0x55 */ u8 pad55[3];
} HudBlockCBBAC;

extern const f32 D_800AB164[2];
extern const f32 D_800AB18C[2];

// hud_side_bars_spawn: spawns four HUD sprites for player obj + 0x23D (list 5, span 300, scale 49 x 18): kind 0x7B
// (colour byte 0xFF) and 0x7C (0) at (88, 91), then the same pair mirrored at (-88, 91) without flag 2. Each gets the
// handler block above: owner, alpha 255, mode (0 when `arg3` is -1, else 4), `type`, side (0 right / 1 left), the
// layout constants of D_800AB164 / D_800AB18C (second entry when D_80082FA0 == 1) and `arg3`. `wide` adds flag 0x40.
/* was func_151CBBAC */
void aim_hud_side_bars_spawn(u8 *obj, u8 type, u8 wide, s8 arg3, u8 group) {
    HudBlockCBBAC blk;
    SpriteSpecCBBAC spec;
    u8 *rec;

    blk.alphaA = 255.0f;
    blk.alphaB = 255.0f;
    blk.type = type;
    blk.owner = obj;
    blk.mode = (arg3 == -1) ? 0 : 4;
    blk.u54 = arg3;
    blk.u14 = 255.0f;
    spec.span = 300;
    spec.scaleA = 49.0f;
    blk.u10 = 0.0f;
    spec.scaleB = 18.0f;
    spec.flags = (wide ? 0x40 : 0) | 0x32 | (1 << (obj[0x23D] + 11));
    spec.u1A = 7;
    spec.col[0] = 0xFF;
    spec.u16 = 1;
    spec.col[1] = 0xFF;
    spec.col[2] = 0xFF;
    spec.col[4] = 0xFF;
    spec.col[5] = 0xFF;
    spec.col[6] = 0xFF;
    spec.u18 = 0xFF;
    spec.col[7] = 0xFF;
    spec.col[8] = 0xFF;
    spec.u24 = 0;
    spec.u28 = 0x200004;
    spec.u2C = 0x1F0601;
    spec.u30 = 7;
    spec.u34 = 0x22;
    spec.u38 = 0x80;
    spec.u3C = 0x20;
    spec.u40 = 0;
    spec.u41 = 7;
    spec.player = obj[0x23D];
    blk.side = 0;
    spec.col[3] = 0xFF;
    spec.kind = 0x7B;
    blk.u1C = 0.0f;
    spec.x = 88.0f;
    spec.y = 91.0f;
    blk.u18 = D_800AB164[D_80082FA0 == 1];
    blk.u20 = D_800AB18C[D_80082FA0 == 1];
    rec = (u8 *) sprite2d_spawn(&spec, 5, 0, 0, 0x58, group, 0);
    if (rec != NULL) {
        memcpy(rec + 0x70, &blk, 0x58);
    }
    spec.col[3] = 0;
    spec.kind = 0x7C;
    rec = (u8 *) sprite2d_spawn(&spec, 5, 0, 0, 0x58, group, 0);
    if (rec != NULL) {
        memcpy(rec + 0x70, &blk, 0x58);
    }

    spec.flags &= ~2;
    spec.col[3] = 0xFF;
    spec.kind = 0x7B;
    blk.side = 1;
    spec.x = -88.0f;
    spec.y = 91.0f;
    rec = (u8 *) sprite2d_spawn(&spec, 5, 0, 0, 0x58, group, 0);
    if (rec != NULL) {
        memcpy(rec + 0x70, &blk, 0x58);
    }
    spec.col[3] = 0;
    spec.kind = 0x7C;
    rec = (u8 *) sprite2d_spawn(&spec, 5, 0, 0, 0x58, group, 0);
    if (rec != NULL) {
        memcpy(rec + 0x70, &blk, 0x58);
    }
}
/* was func_151CBEC8 */
void aim_hud_side_bar_on_message(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if ((arg2 == 0x37) && (arg1[0] == temp_v0[0xE]) && (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0)) {
        *(f32 *)(temp_v0 + 0x10) = 0.0f;
        temp_v0[0xC] |= 1;
        *(f32 *)(temp_v0 + 0x14) = 0.0f;
    }
}

f32 aim_hud_gauge_value(u8 *);
typedef struct { u8 pad0[0xC]; u8 unkC; u8 unkD; u8 padE[2]; f32 unk10; f32 unk14; f32 unk18; f32 unk1C; f32 unk20; } Sub151CBF20;
/* was func_151CBF20 */
s32 aim_hud_side_bar_update(u8 *arg0) {
    s32 pad; // frame padding
    Sub151CBF20 *v;
    f32 t;
    f32 k;
    f32 lo;
    u8 a;

    v = (Sub151CBF20 *)(arg0 + 0x70);
    k = (1.0f - ((aim_hud_gauge_value(arg0) - v->unk18) * v->unk20)) * 75.0f;
    if (v->unkC & 1) {
        lo = 91.0f + k;
        *(f32 *)(arg0 + 0x14) = (sinf(v->unk10) * ((112.0f + k) - lo)) + lo;
        v->unk10 += 0.505f * D_800BE9A4;
        if (v->unk10 >= 3.1415927f) {
            *(f32 *)(arg0 + 0x14) = lo;
            v->unkC &= 0xFFFE;
        }
    } else {
        *(f32 *)(arg0 + 0x14) = 91.0f + k;
    }
    if (v->unkD == 2) {
        *(f32 *)(arg0 + 0x14) -= 20.0f;
    }
    a = v->unk14;
    if (arg0[0x20] == 0x7C) {
        arg0[0x2E] = 0xFF - a;
    } else {
        arg0[0x2E] = a;
    }
    v->unk14 += (255.0f - v->unk14) * 0.67600006f;
    return 1;
}

/* was func_151CC11C */
void aim_tint_on_message(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x20) == *arg1) {
            node_destroy(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x20) == *(u8 **)(p + 0x318)) {
            node_destroy(arg0);
        }
    }
}

f32 aim_hud_gauge_value(u8 *arg0);
void vec2_from_angle_rad(f32 arg0, f32 arg1, u8 *arg2, u8 *arg3);

typedef struct {
    u8 pad0[0x18];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} Sub151CC190;

/* was func_151CC190 */
s32 aim_hud_dial_update(u8 *arg0) {
    f32 temp;
    f32 prod;
    Sub151CC190 *v;

    v = (Sub151CC190 *)(arg0 + 0x70);
    temp = aim_hud_gauge_value(arg0);
    if (temp != v->unk28) {
        v->unk28 = temp;
        prod = (temp - v->unk18) * v->unk20 * 6.283186f;
        vec2_from_angle_rad(v->unk24 + prod, 55.0f, arg0 + 0x10, arg0 + 0x14);
    }
    return 1;
}

/* was func_151CC210 */
s32 aim_hud_gauge_scale_update(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;

    temp_f0 = aim_hud_gauge_value(arg0);
    if (temp_f0 != (*(f32 *)((u8 *)(&arg0[0x70]) + 0x28))) {
        temp_f2 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x4C));
        (*(f32 *)((u8 *)(&arg0[0x70]) + 0x28)) = temp_f0;
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((temp_f2 - ((temp_f0 - (*(f32 *)((u8 *)(&arg0[0x70]) + 0x18))) * (*(f32 *)((u8 *)(&arg0[0x70]) + 0x20)) * temp_f2)) + 1.0f);
    }
    if ((*(u8 *)((u8 *)(&arg0[0x70]) + 0xC)) & 2) {
        (*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) = (f32) ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) - D_800BE9A4);
        temp_f18 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x50));
        if (temp_f18 <= 0.0f) {
            (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x3C));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x40));
            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x44));
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x48));
            (*(s8 *)((u8 *)(&arg0[0x70]) + 0xC)) = (s8) ((*(u8 *)((u8 *)(&arg0[0x70]) + 0xC)) & 0xFFFD);
        } else {
            temp_f0_2 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x3C));
            (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) (temp_f0_2 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x2C)) - temp_f0_2) * (temp_f18 * 0.028571429f)));
            temp_f2_2 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x40));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) (u32) (temp_f2_2 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x30)) - temp_f2_2) * ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) * 0.028571429f)));
            temp_f12 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x44));
            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (u32) (temp_f12 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x34)) - temp_f12) * ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) * 0.028571429f)));
            temp_f14 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x48));
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) (u32) (temp_f14 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x38)) - temp_f14) * ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) * 0.028571429f)));
        }
    }
    return 1;
}
/*
 * obj_height_in_range: P190. A height clamped to [obj +0x88, obj +0x8C]: with flag 4 of obj[0x7C] the point
 * D_800C3958[(s8)obj[0xC4]] +0x28 percent of the way from +0x88 to +0x8C, else the middle of +0x19C / +0x1A0 of
 * the object at obj +0x70.
 */
/* was func_151CC784 */
f32 aim_hud_gauge_value(u8 *arg0) {
    f32 lo, hi, h;
    u8 *o;

    if (arg0[0x7C] & 4) {
        lo = *(f32 *)(arg0 + 0x88);
        h = lo + (*(f32 *)(arg0 + 0x8C) - lo) * (*(f32 *)((u8 *)D_800C3958 + (s8)arg0[0xC4] * 0x44 + 0x28) * 0.01f);
    } else {
        o = *(u8 **)(arg0 + 0x70);
        lo = *(f32 *)(arg0 + 0x88);
        h = (*(f32 *)(o + 0x19C) + *(f32 *)(o + 0x1A0)) * 0.5f;
    }
    if (h < lo) {
        return lo;
    }
    hi = *(f32 *)(arg0 + 0x8C);
    if (hi < h) {
        return hi;
    }
    return h;
}

/* was func_151CC840 */
void aim_hud_send_flash(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    sprite2d_broadcast((f32 *) &sp1C, 0x46);
}

// glow_colour_on_message: message handler (same table row as aim_hud_side_bar_on_message). On message 0x46 whose key (*arg1)
// matches the record's (+0x70): sets flag 2 at +0x7C, the fade value +0xC0 to 35, and copies the four colour floats
// +0x9C .. +0xA8 (as u32 bytes) to the colour bytes +0x2B .. +0x2E.
/* was func_151CC86C */
void aim_hud_glow_on_message(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *rec = arg0 + 0x70;

    if (arg2 != 0x46 || *(s32 *) arg1 != *(s32 *) rec) {
        return;
    }
    rec[0xC] |= 2;
    *(f32 *) (rec + 0x50) = 35.0f;
    arg0[0x2B] = (u32) *(f32 *) (rec + 0x2C);
    arg0[0x2C] = (u32) *(f32 *) (rec + 0x30);
    arg0[0x2D] = (u32) *(f32 *) (rec + 0x34);
    arg0[0x2E] = (u32) *(f32 *) (rec + 0x38);
}

/* was func_151CCAD4 */
void aim_hud_gauge_spawn(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    struct {
        u8 * u2C;
        f32 u30;
        f32 u34;
        s8 u38;
        s8 u39;
        u8 pad3A[0x4E];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        s16 u9E;
        s16 uA0;
        s8 uA2;
        u8 uA3;
        u8 uA4;
        u8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s32 uAC;
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        u8 padCA[0x2];
        u8 uCC;
        u8 padCD[0x3];
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
    } sp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    sp.u30 = 0.0f;
    sp.u39 = 0;
    sp.u38 = 0;
    sp.uD8 = 0.0f;
    sp.uDC = 0.0f;
    sp.u9A = 0x12C;
    sp.u2C = arg0;
    sp.u34 = 130.0f;
    if (arg4 != 0) {
        var_v0 = 0x40;
    } else {
        var_v0 = 0;
    }
    sp.u9E = 1;
    sp.u9C = var_v0 | 0x390 | (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB));
    sp.uA3 = arg1;
    sp.uA4 = arg2;
    sp.uA2 = 7;
    sp.uA6 = 0x82;
    sp.uA7 = 0xFF;
    sp.uA8 = 0xFF;
    sp.uA9 = 0xFF;
    sp.uA5 = arg3;
    sp.uA0 = 0xFF;
    sp.uAA = 0xFF;
    sp.uAB = 0xFF;
    sp.uAC = 0;
    sp.uB0 = 0x200004;
    sp.uB4 = 0x1F0601;
    sp.uB8 = 8;
    sp.uBC = 0x44;
    sp.uC0 = 0x80;
    sp.uC4 = 0x20;
    sp.uC8 = 0;
    sp.uC9 = 0xA;
    sp.u98 = 0x9A;
    sp.u88 = 0.0f;
    sp.uD0 = 0.2f;
    sp.uCC = (*(u8 *)((u8 *)arg0 + 0x23D));
    sp.uD4 = 1.0f;
    sp.u90 = 28.0f;
    sp.u94 = 4.2f;
    sp.u8C = -37.0f;
    temp_v0 = sprite2d_spawn(&sp.u88, 9, 0, 0, 0x58, (s32) arg5, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9B;
    sp.u8C = 0.0f;
    sp.uD0 = 1.0f;
    sp.uD4 = 0.2f;
    sp.u90 = 4.2f;
    sp.u94 = 28.0f;
    sp.u88 = -37.0f;
    temp_v0_2 = sprite2d_spawn(&sp.u88, 9, 0, 0, 0x58, (s32) arg5, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u2C, 0x58U);
    }
}
void vec3_to_yaw_pitch_deg(void *, f32 *, f32 *);

/* was func_151CCD2C */
s32 aim_hud_target_angle_update(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
    } sp;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x70))) + 0x3D0));
    if (temp_v1 == NULL) {
        return 0;
    }
    temp_v0 = (*(s32 *)((u8 *)temp_v1 + 0x31C));
    if (temp_v0 == 0) {
        return 0;
    }
    vec3_to_yaw_pitch_deg(temp_v0 + 0x130, &sp.u24, &sp.u20);
    if ((*(u8 *)((u8 *)arg0 + 0x20)) == 0x9A) {
        (*(f32 *)((u8 *)arg0 + 0x60)) = (f32) (2.0f * -(sp.u24 * 0.0027777778f * 2560.0f));
        return 1;
    }
    (*(f32 *)((u8 *)arg0 + 0x64)) = (f32) (2.0f * (sp.u20 * 0.0027777778f * 2560.0f));
    return 1;
}
/* was func_151CCDF0 */
s32 aim_hud_gauge_marks_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        u8 * u2C;
        f32 u30;
        f32 u34;
        s8 u38;
        s8 u39;
        u8 pad3A[0x4E];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        u16 u9C;
        s16 u9E;
        s16 uA0;
        s8 uA2;
        u8 uA3;
        u8 uA4;
        u8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s32 uAC;
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        u8 padCA[0x2];
        u8 uCC;
    } sp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_v0;
    s32 var_v0_2;

    sp.u30 = 0.0f;
    sp.u39 = 0;
    sp.u38 = 0;
    sp.u9A = 0x12C;
    sp.u2C = arg0;
    sp.u34 = 130.0f;
    if ((u8) arg4 != 0) {
        var_v0_2 = 0x40;
    } else {
        var_v0_2 = 0;
    }
    sp.u9E = 1;
    sp.u9C = var_v0_2 | 0x10 | (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB));
    sp.uA3 = (u8) arg1;
    sp.uA4 = (u8) arg2;
    sp.uA2 = 7;
    sp.uA6 = 0xB4;
    sp.uA7 = 0xFF;
    sp.uA8 = 0xFF;
    sp.uA9 = 0xFF;
    sp.uA5 = (u8) arg3;
    sp.uA0 = 0xFF;
    sp.uAA = 0xFF;
    sp.uAB = 0xFF;
    sp.uAC = 0;
    sp.uB0 = 0x200004;
    sp.uB4 = 0x1F0601;
    sp.uB8 = 8;
    sp.uBC = 0x44;
    sp.uC0 = 0x80;
    sp.uC4 = 0x20;
    sp.uC8 = 0;
    sp.uC9 = 0xA;
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u98 = 0x64;
    sp.uCC = (*(u8 *)((u8 *)arg0 + 0x23D));
    sp.u94 = 12.0f;
    sp.u90 = 12.0f;
    temp_v0 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9D;
    sp.u9C &= 0xFFF9;
    sp.u94 = 7.0f;
    sp.u90 = 7.0f;
    sp.u88 = 55.0f;
    sp.u8C = 0.0f;
    temp_v0_2 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C = (sp.u9C & 0xFFF9) | 2;
    sp.u88 = -55.0f;
    sp.u8C = 0.0f;
    temp_v0_3 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9C;
    sp.u9C = (sp.u9C & 0xFFF9) | 4;
    sp.u88 = 0.0f;
    sp.u8C = 55.0f;
    temp_v0_4 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_4 != 0) {
        memcpy(temp_v0_4 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C &= 0xFFF9;
    sp.u88 = 0.0f;
    sp.u8C = -55.0f;
    temp_v0_5 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_5 != 0) {
        memcpy(temp_v0_5 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9E;
    sp.u9C |= 6;
    sp.u94 = 6.0f;
    sp.u90 = 6.0f;
    sp.u88 = 44.0f;
    sp.u8C = 44.0f;
    temp_v0_6 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_6 != 0) {
        memcpy(temp_v0_6 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C = (sp.u9C & 0xFFF9) | 4;
    sp.u88 = -44.0f;
    sp.u8C = 44.0f;
    temp_v0_7 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_7 != 0) {
        memcpy(temp_v0_7 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C &= 0xFFF9;
    sp.u88 = -44.0f;
    sp.u8C = -44.0f;
    temp_v0_8 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_8 != 0) {
        memcpy(temp_v0_8 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C = (sp.u9C & 0xFFF9) | 2;
    sp.u88 = 44.0f;
    sp.u8C = -44.0f;
    var_v0 = sprite2d_spawn(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x70, &sp.u2C, 0x58U);
    }
    return var_v0;
}
/* was func_151CD2CC */
void aim_hud_gauge_small_spawn(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    Spawn559A a;
    s32 pad2; // fakematch: 4-byte hole between blocks
    Spawn559B b;
    s32 ret;

    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    b.uD = 0;
    b.uC = 0;
    a.u12 = 0x12C;
    a.u14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = arg1;
    a.u1C = arg2;
    a.u1D = arg3;
    a.u1E = 0xB4;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 8;
    a.u34 = 0x44;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0xA;
    a.u0 = 0.0f;
    a.u4 = 0.0f;
    a.u44 = arg0[0x23D];
    a.u10 = 0xB4;
    a.u8 = 65.0f;
    a.uC = 65.0f;
    ret = sprite2d_spawn(&a, 0, 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
}

s32 screen_tint_create(s32, s32, s32, s32, s32, s32, u8, s32);

/* was func_151CD444 */
void aim_hud_tint_spawn(u8 *arg0) {
    s32 temp_v0;
    u8 *sp28;

    if (D_800BE616 != 0) {
        sp28 = arg0;
        temp_v0 = screen_tint_create(0, 0, 0, 0xFF, 0, (s32) (*(u8 *)((u8 *)arg0 + 0x23D)), 1, 4);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x20, &sp28, 4);
        }
    }
}

extern u8 D_8008FFC8[4];
extern const f32 D_800AB16C[2];
extern const f32 D_800AB194[2];

// hud_slot_row_spawn: spawns two rows of four HUD sprites for player obj + 0x23D (list 0xB, span 300, scale
// 35.75 x 16, kinds D_8008FFC8[0..3]) at x = 71.5 i - 107.25, y = -90 (row 0) and 92 (row 1, flag 4 added). Each
// gets the 0x58-byte handler block: owner, 0, 130, mode (0 when `arg2` is -1, else 4), 4 / 5 for the row, the layout
// constants of D_800AB16C / D_800AB194 (second entry when D_80082FA0 == 1) and `arg2`. `wide` adds flag 0x40.
/* was func_151CD4B8 */
void aim_hud_slot_rows_spawn(u8 *obj, u8 wide, s8 arg2, u8 group) {
    HudBlockCBBAC blk;
    union {
        s32 w;
        u8 b[4];
    } kinds;
    SpriteSpecCBBAC spec;
    u8 row;
    u8 i;
    u8 *rec;

    blk.u1C = 0.0f;
    blk.u18 = D_800AB16C[D_80082FA0 == 1];
    blk.u20 = D_800AB194[D_80082FA0 == 1];
    blk.owner = obj;
    blk.alphaA = 0.0f;
    blk.alphaB = 130.0f;
    blk.mode = (arg2 == -1) ? 0 : 4;
    blk.u54 = arg2;
    spec.span = 300;
    spec.flags = (wide ? 0x40 : 0) | 0x30;
    spec.u1A = 7;
    spec.col[0] = 0xFF;
    spec.u16 = 1;
    spec.col[1] = 0xFF;
    spec.col[2] = 0xFF;
    spec.col[3] = 0xFF;
    spec.col[4] = 0xFF;
    spec.u18 = 0xFF;
    spec.col[5] = 0xFF;
    spec.col[6] = 0xFF;
    spec.col[7] = 0xFF;
    spec.col[8] = 0xFF;
    spec.u24 = 0;
    spec.u28 = 0x200004;
    spec.u2C = 0x1F0601;
    spec.u30 = 8;
    spec.u34 = 0x13;
    spec.u38 = 0x80;
    spec.u3C = 0x20;
    spec.u40 = 0;
    spec.u41 = 0;
    spec.u50 = 0.0f;
    spec.u54 = 0.0f;
    spec.u48 = 1.0f;
    spec.u4C = 1.0f;
    spec.scaleA = 35.75f;
    spec.scaleB = 16.0f;
    spec.player = obj[0x23D];
    for (row = 0; row < 2; row++) {
        kinds.w = *(s32 *) D_8008FFC8;
        spec.y = row ? 92.0f : -90.0f;
        spec.flags |= row ? 4 : 0;
        blk.type = row ? 5 : 4;
        for (i = 0; i < 4; i++) {
            spec.x = (f32) i * 71.5f + 35.75f - 143.0f;
            spec.kind = kinds.b[i];
            rec = (u8 *) sprite2d_spawn(&spec, 0xB, 0, 0, 0x58, group, 1);
            if (rec != NULL) {
                memcpy(rec + 0x70, &blk, 0x58);
            }
        }
    }
}
f32 aim_hud_gauge_value(u8 *);
typedef struct { u8 pad0[0xD]; u8 unkD; u8 padE[0xA]; f32 unk18; f32 unk1C; f32 unk20; } SubCD;
/* was func_151CD7D4 */
void aim_hud_slot_row_update(u8 *arg0) {
    f32 k;
    SubCD *v;

    v = (SubCD *)(arg0 + 0x70);
    k = (1.0f - ((aim_hud_gauge_value(arg0) - v->unk18) * v->unk20)) * 75.0f;
    if (v->unkD == 5) {
        *(f32 *)(arg0 + 0x14) = 92.0f + k;
    } else if (v->unkD == 4) {
        *(f32 *)(arg0 + 0x14) = -92.0f - k;
    }
}
