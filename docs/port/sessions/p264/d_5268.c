#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_15143794(s16, s16, f32, void *);
extern f32 D_800A0DE8;
extern f32 D_800A0DEC;
extern f32 D_800A0DF0;
extern f32 D_800A0DF4;
extern f32 D_800A0DF8;

/* func_151307F0's sprite particle template (the func_15153BA4 layout; +0x68.. is not filled here) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 flags;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[8]; /* 7 bytes, alpha */
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 sprite;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 u3C[3];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 mode;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[7];
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 u68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 u6C;
} SprTmpl5268;

// smoke_puff_burst: spawns 10..20 smoke sprites (func_151307F0, room / owner from arg3 / arg4) at pos. Each gets a
// random sprite of D_800A0D90, life 27..44, alpha 100..255, size 199..432 and a velocity from func_15143794 (yaw
// around the scaled heading byte (s16) (scale * D_800A0DE8) >> 8 + 0x40 plus 0..129, pitch -64..16, speed 5..15)
// minus the source's horizontal velocity (vel x / z) times a random drag; random flip flags 0x40 / 0x80.
void func_150D5268(f32 *pos, f32 *vel, f32 scale, u8 room, s32 owner) {
    SprTmpl5268 t;
    s32 n;
    s16 yaw;
    f32 drag;
    u32 r1;
    u32 r2;
    s32 bit80;
    s32 bit40;

    n = (u32) func_150ADA20() % 11 + 10;
    t.u0 = 0x200005;
    t.u4 = 0;
    t.flags = 0x2203;
    t.uC = 0;
    t.u10 = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    t.colour[4] = 0xFF;
    t.colour[5] = 0xFF;
    t.colour[6] = 0xFF;
    t.u1C = 0xFF;
    t.pos[0] = pos[0];
    t.pos[1] = pos[1];
    t.pos[2] = pos[2];
    t.u3C[0] = ((f32 *) D_800A5860)[0];
    t.u3C[1] = ((f32 *) D_800A5860)[1];
    t.u3C[2] = ((f32 *) D_800A5860)[2];
    t.u1E = 10;
    t.u20 = 0x19;
    t.u60[1] = 7;
    t.u60[2] = 0xFF;
    t.u22 = 1;
    t.mode = 0x4C207;
    t.u60[0] = 0;
    t.u60[3] = 0xFF;
    t.u60[4] = 0xFF;
    t.u60[5] = 0;
    t.u5C = 0;
    t.u60[6] = 0xFF;
    t.u24 = 1.0f;
    yaw = ((s16) (s32) (scale * D_800A0DE8) >> 8) + 0x40;
    do {
        drag = func_150ADA68() * D_800A0DF0 + D_800A0DEC;
        t.sprite = ((s32 *) D_800A0D90)[func_150ADA20() & 3];
        t.life = (u32) func_150ADA20() % 18 + 27;
        t.colour[7] = (u32) func_150ADA20() % 156 + 100;
        t.size[0] = t.size[1] = func_150ADA68() * 233.0f + 199.0f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794(r1 % 130 + yaw, r2 % 81 - 0x40, func_150ADA68() * 10.0f + 5.0f, t.vel);
        t.vel[0] -= vel[0] * drag;
        t.vel[2] -= vel[2] * drag;
        t.u54 = func_150ADA68() * D_800A0DF4 + D_800A0DF8;
        t.mode &= ~0xC0;
        bit80 = (func_150ADA20() & 1) ? 0x80 : 0;
        bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
        t.mode |= bit40 | bit80;
        func_151307F0((s32) &t, 1, 0, 0, room, owner);
        n--;
    } while (n > 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5268.s")
#endif
