#ifdef NON_MATCHING
/* func_15157580's spec (0x58 bytes, the model effect it spawns). */
typedef struct {
    /* 0x00 */ u8 u00;
    /* 0x01 */ u8 u01;
    /* 0x02 */ u8 u02;
    /* 0x03 */ u8 u03;
    /* 0x04 */ u8 u04;
    /* 0x06 */ s16 span;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s32 u10;
    /* 0x14 */ s32 flagsA;
    /* 0x18 */ s32 flagsB;
    /* 0x1C */ s32 u1C;
    /* 0x20 */ s32 u20;
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ u8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ u8 col[8];
    /* 0x38 */ u8 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x44 */ struct { s32 x, y, z; } angle;
    /* 0x50 */ u8 pad50[4];
    /* 0x54 */ s16 u54;
    /* 0x56 */ s16 u56;
} ModelFxSpecFB398;

/* func_151559FC's spec (0x58 bytes; same layout as game_eu_FCE60's SpawnSpecCFB90). */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x12 */ s16 span;
    /* 0x14 */ s16 u14;
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
} SpriteSpecFB398;

s32 func_15157580(void *spec, s32, f32, s32, s32, s32, s32, s32);
s32 func_151559FC(void *spec, s32 list, s32, s32, s32, s32, s32);
extern s16 D_800A20F0[]; /* 8 sprite kinds: 0xCE, 0xC5, then 0xC4 */

// score_banner_spawn: spawns the model effect 0x61 (func_15157580) and a row of 8 sprites (list 0xE, kinds
// D_800A20F0, x = -65 + 24.75 * i, y = 62, scale 16) for `span`, copying `span` into each new record (+0x120 for the
// model effect, +0x70 for the sprites). `flag` / `owner` are passed through to both spawners.
void func_150FB398(s16 span, u8 flag, s32 owner) {
    ModelFxSpecFB398 fx;
    SpriteSpecFB398 spr;
    s32 rec;
    u8 i;

    fx.u00 = 0x61;
    fx.u01 = 3;
    fx.u02 = 4;
    fx.u03 = 2;
    fx.u04 = 0;
    fx.span = span;
    fx.u08 = 0xA5;
    fx.u0C = 0x17;
    fx.u10 = 0;
    fx.flagsA = 0x200405;
    fx.flagsB = 0x60200;
    fx.u1C = 1;
    fx.u20 = 0x38;
    fx.u24 = 0x80;
    fx.u28 = 0x20;
    fx.u2C = 0;
    fx.u2D = 8;
    for (i = 0; i < 8; i++) {
        fx.col[i] = 0xFF;
    }
    fx.u38 = 0;
    fx.u3C = 0;
    fx.u40 = 0;
    fx.u41 = 1;
    fx.angle.x = ((s32 *)D_800A5860)[0];
    fx.angle.y = ((s32 *)D_800A5860)[1];
    fx.angle.z = ((s32 *)D_800A5860)[2];
    fx.u54 = 0xA;
    fx.u56 = 0x19;
    rec = func_15157580(&fx, 0, 1.0f, 0, 0, 2, flag, owner);
    if (rec != 0) {
        memcpy((u8 *)rec + 0x120, &span, sizeof(span));
    }

    spr.y = 62.0f;
    spr.scaleA = 16.0f;
    spr.scaleB = 16.0f;
    spr.span = span;
    spr.u14 = 0x29;
    spr.u16 = 0xA;
    spr.u18 = 0x19;
    spr.u1A = 0;
    for (i = 0; i < 9; i++) {
        spr.col[i] = 0xFF;
    }
    spr.u24 = 0;
    spr.u28 = 0x200405;
    spr.u2C = 0x60200;
    spr.u30 = 0x19;
    spr.u34 = 0x22;
    spr.u38 = 0x80;
    spr.u3C = 0x20;
    spr.u40 = 0;
    spr.u41 = 7;
    spr.player = 0;
    spr.u48 = 1.0f;
    spr.u4C = 1.0f;
    spr.u50 = 0.0f;
    spr.u54 = 0.0f;
    for (i = 0; i < 8; i++) {
        spr.x = i * 24.75f + -65.0f;
        spr.kind = D_800A20F0[i];
        rec = func_151559FC(&spr, 0xE, 0, 0, 2, flag, owner);
        if (rec != 0) {
            memcpy((u8 *)rec + 0x70, &span, sizeof(span));
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB398.s")
#endif
