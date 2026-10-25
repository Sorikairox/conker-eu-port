#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171100.s")

void func_15171434(s32 arg0, u8 arg1, s32 arg2) {
    switch (D_800BE9F0) {
    case 2:
        func_15171100(arg0, 1, 1, 1, arg1, arg2);
        break;
    case 16:
        func_15171100(arg0, 0xA9, 8, 0, arg1, arg2);
        break;
    }
}

#ifdef NON_MATCHING
s32 func_1518C900(s32);
void func_15168BE4(u8 *arg0, u8 arg1, s32 arg2);

/* D_800A72B8: the 6 pieces (model id, offset, velocity) */
typedef struct {
    u16 model;
    u8 pad2[2];
    f32 offset[3];
    f32 vel[3];
} Piece714BC;
extern Piece714BC D_800A72B8[6];

/* func_15168BE4's debris template */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 vel[3];
    /* 0x18 */ f32 spin[3];
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 scale[3];
    /* 0x3C */ s32 life;
    /* 0x40 */ s32 model;
    /* 0x44 */ s32 u44; /* not set */
    /* 0x48 */ f32 u48[3];
    /* 0x54 */ u8 u54[6];
    /* 0x5A */ u8 id;
    /* 0x5B */ u8 u5B;
    /* 0x5C */ u8 u5C;
    /* 0x5D */ u8 u5D;
} Debris714BC;

// barrel_break_pieces: breaks the object into the 6 pieces of D_800A72B8 (func_15168BE4 debris, model
// func_1518C900(id)) at the object position (+0x10 / +0x12 / +0x14) plus each piece offset, with the piece velocity,
// spin from the offset (x, |y|, z times 0.09 / 0.23 / 0.09), u24 = vel x * 0.1, random u28 -2..2 / u2C -5..5,
// scale 2, life 60; then sets +0x6E to 1. kind / arg2 go to func_15168BE4.
void func_151714BC(u8 *obj, u8 kind, s32 arg2) {
    Debris714BC t;
    Piece714BC *pc = D_800A72B8;
    f32 x, y, z;
    s32 i;

    t.u5C = 2;
    t.u5D = 1;
    t.u5B = 6;
    t.u54[5] = 0;
    x = *(s16 *) (obj + 0x10);
    y = *(s16 *) (obj + 0x12);
    z = *(s16 *) (obj + 0x14);
    t.vel[0] = 0.0f;
    t.vel[1] = 0.0f;
    t.vel[2] = 0.0f;
    t.scale[0] = 2.0f;
    t.scale[1] = 2.0f;
    t.scale[2] = 2.0f;
    t.life = 0x3C;
    t.u54[0] = 2;
    t.u54[1] = 0xFF;
    t.u54[2] = 0;
    t.u54[3] = 0;
    t.u54[4] = 0;
    t.u48[0] = 0.3f;  /* D_800A7378 */
    t.u48[1] = -0.7f; /* D_800A737C */
    t.u48[2] = -0.2f; /* D_800A7380 */
    for (i = 0; i < 6; i++, pc++) {
        t.model = func_1518C900(pc->model);
        t.id = pc->model;
        t.pos[0] = pc->offset[0] + x;
        t.pos[1] = pc->offset[1] + y;
        t.pos[2] = pc->offset[2] + z;
        t.spin[0] = pc->offset[0] * 0.09f;        /* D_800A738C */
        t.spin[1] = fabsf(pc->offset[1]) * 0.23f; /* D_800A7388 */
        t.spin[2] = pc->offset[2] * 0.09f;
        t.vel[0] = pc->vel[0];
        t.u24 = t.vel[0] * 0.1f;                  /* D_800A7384 */
        t.vel[1] = pc->vel[1];
        t.vel[2] = pc->vel[2];
        t.u28 = func_150ADA68() * 4.0f - 2.0f;
        t.u2C = func_150ADA68() * 10.0f - 5.0f;
        func_15168BE4((u8 *) &t, kind, arg2);
    }
    obj[0x6E] = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_151714BC.s")
#endif

void func_15171734(u8 *arg0) {
    if (arg0[4] == 0x33) {
        func_150C3D5C(arg0);
    }
    func_15060F28(arg0, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171770.s")

void func_15171D6C(s16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, u8 argB, s32 argC);
extern f32 D_800A73A0;
extern f32 D_800A73A4;

void func_15171B70(u8 *arg0, u8 arg1, s32 arg2) {
    switch (arg0[0x72]) {
    case 0xEB:
        func_15171D6C((s16 *)arg0, 400.0f, 500.0f, 0.0f, D_800A73A0, 0.0f, 2, 5, 20, 20, 1.0f, arg1, arg2);
        break;
    case 0xF6:
        func_15171D6C((s16 *)arg0, 200.0f, 400.0f, -1800.0f, -1000.0f, -1200.0f, 2, 5, 4, 10, 1.0f, arg1, arg2);
        break;
    case 0xF8:
        func_15171D6C((s16 *)arg0, 100.0f, 160.0f, -2500.0f, D_800A73A4, 0.0f, 2, 5, 4, 4, 0.5f, arg1, arg2);
        break;
    case 0xF9:
        func_15171D6C((s16 *)arg0, 200.0f, 100.0f, 100.0f, -300.0f, 0.0f, 1, 5, 4, 4, 1.0f, arg1, arg2);
        break;
    }
}

void func_15170648(f32 *, f32, f32, s32, f32, s32, s32, s32, u8, s32);
void func_15171D6C(s16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, u8 argB, s32 argC) {
    f32 pts[4][3];
    f32 x;
    f32 y;
    f32 z;

    x = arg0[8] + arg3;
    y = arg0[9] + arg4;
    z = arg0[10] + arg5;
    pts[0][0] = arg1 + x;
    pts[0][1] = y;
    pts[0][2] = arg2 + z;
    pts[1][0] = x - arg1;
    pts[1][1] = y;
    pts[1][2] = arg2 + z;
    pts[2][0] = x - arg1;
    pts[2][1] = y;
    pts[2][2] = z - arg2;
    pts[3][0] = arg1 + x;
    pts[3][1] = y;
    pts[3][2] = z - arg2;
    func_15170648(pts[0], x, z, arg7, argA, arg6, arg8, arg9, argB, argC);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171E60.s")

#ifdef NON_MATCHING
void func_150AEEB0(struct127 *, u8);
#else
s32 func_150AEEB0(struct127 *, u8);
#endif
#ifdef NON_MATCHING
void func_150BDC20(struct127 *, u8, s32);
#else
s32 func_150BDC20(struct127 *, u8, s32);
#endif
s32 func_150CE0C0(struct127 *, u8, s32);

void func_15172164(struct127 *arg0, u8 arg1) {
    switch (arg0->id) {
    case 0x13:
    case 0x23:
        func_150AEEB0(arg0, arg1);
        func_10010154(0x69, arg0, 0x7D00, 0xC8, 0x7D0);
        break;
    case 0x1E:
        func_150BDC20(arg0, arg1, 1);
        break;
    case 0x54:
        func_150CE0C0(arg0, arg1, 1);
        break;
    }
}
