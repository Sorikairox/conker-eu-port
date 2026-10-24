s32 func_151559FC(s32 *, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x11 */ u8 pad11;
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
    /* 0x45 */ u8 pad45[3];
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpawnSpecCFB90; // size 0x58

typedef struct {
    u8 u0;
    u8 pad1[3];
    f32 u4;
    f32 u8;
    f32 uC;
} SpawnExtraCFB90; // copied to the record's +0x70

// screen_bar_spawn: spawns effect kind 0xC1 at (-300, 72), scale 7.5, with `span` at +0x12 (+0x14 = 0x31, white
// colour bytes, flags 0x200004 / 0x9F0601 and fixed defaults, current player D_80082FA0) through func_151559FC (list
// 0xC, `flag`, `arg2`) and copies the extra block (0, 0, -300, 0) to the new record's +0x70.
void func_150CFB90(s16 span, u8 flag, s32 arg2) {
    SpawnExtraCFB90 extra;
    SpawnSpecCFB90 spec;
    s32 rec;
    s32 i;

    extra.u0 = 0;
    extra.u4 = 0.0f;
    extra.u8 = -300.0f;
    extra.uC = 0.0f;
    spec.x = -300.0f;
    spec.y = 72.0f;
    spec.scaleA = 7.5f;
    spec.scaleB = 7.5f;
    spec.kind = 0xC1;
    spec.span = span;
    spec.u14 = 0x31;
    spec.u16 = 1;
    spec.u18 = 0xFF;
    spec.u1A = 8;
    for (i = 0; i < 9; i++) {
        spec.col[i] = 0xFF;
    }
    spec.u24 = 0;
    spec.u28 = 0x200004;
    spec.u2C = 0x9F0601;
    spec.u30 = 0x17;
    spec.u34 = 0x44;
    spec.u38 = 0x80;
    spec.u3C = 0x20;
    spec.u40 = 0;
    spec.u41 = 0xA;
    spec.player = D_80082FA0;
    spec.u48 = 1.0f;
    spec.u4C = 1.0f;
    spec.u50 = 0.0f;
    spec.u54 = 0.0f;
    rec = func_151559FC((s32 *) &spec, 0xC, 0, 0, 0x10, flag, arg2);
    if (rec != 0) {
        memcpy(rec + 0x70, &extra, 0x10);
    }
}
