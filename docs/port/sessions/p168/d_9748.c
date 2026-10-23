s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
s32 func_15133CD0(s32, u8 *);
s32 func_15144E80(u8 *, f32 *, f32 *, f32 *);
void func_15145974(f32 *, f32 *, f32 *);
s32 memcpy(s32, u8 *, s32);

// beam_end_pieces_spawn: the three pieces of one beam end (func_151C7B1C): from the hit triangle `tri`
// (func_15144E80: its normal / axes) the orientation of the base; spawns with func_15132FBC (kind 3) the base
// (sound 0x36, no delay) and two arm pieces (0x37 / 0x38, delay 0x14) at `pos`, writes them to out[0..2] and runs
// func_15133CD0 on both 0x40-byte parts of each; the arms also get the 0x14-byte animation list at +0x170 (alt set
// = the other model ids). out[] is left unchanged when func_15144E80 fails.
void func_151C9748(u8 **out, f32 *pos, u8 *tri, f32 *dir, s32 ground, u8 alt, u8 noshadow, u8 arg7, s32 arg8) {
    struct {
        f32 u00;     /* 0x00 = 1 */
        f32 u04;     /* 0x04 = 1 */
        f32 size[2]; /* 0x08 = 0.4 */
        f32 spin[3]; /* 0x10: tilt + 90, heading, 0 */
        f32 u1C[3];  /* 0x1C = 1 */
        f32 pos[3];  /* 0x28 */
        f32 u34[7];  /* 0x34 = 0 */
        s32 flags;   /* 0x50 */
        s16 life;    /* 0x54 = 300 */
        s16 sound;   /* 0x56 */
        u8 u58;      /* 0x58 = 0 */
        s32 ground;  /* 0x5C */
        u8 u60[8];   /* 0x60: FF, 0.. */
        u8 u68;      /* 0x68 */
        s8 u69;      /* 0x69 */
        u8 u6A;      /* 0x6A = 0 */
        s32 u6C;     /* 0x6C = 0 */
        u8 u70;      /* 0x70 = 0 */
        s16 u72;     /* 0x72 = 1 */
        s16 u74;     /* 0x74 = 0xFF */
    } blk;
    struct {
        u8 op0;      /* 0x00 = 2 */
        u8 pad1[3];
        s16 id0;     /* 0x04 */
        u8 op1;      /* 0x06 = 4 */
        u8 pad7;
        s32 v0;      /* 0x08 = 0x3E */
        s16 id1;     /* 0x0C */
        u8 op2;      /* 0x0E = 6 */
        u8 padF;
        s32 v1;      /* 0x10 = 0x3E */
    } anim;
    f32 ax[3];
    f32 ay[3];
    f32 az[3];
    s32 i;
    s32 k;

    if (func_15144E80(tri, ax, ay, az) == 0) {
        return;
    }
    func_15145974(az, &blk.spin[1], &blk.spin[0]);
    blk.u00 = 1.0f;
    blk.u04 = 1.0f;
    blk.spin[0] += 90.0f;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.size[1] = 0.4f;
    blk.size[0] = 0.4f;
    blk.spin[2] = 0.0f;
    blk.pos[0] = pos[0];
    blk.pos[1] = pos[1];
    blk.pos[2] = pos[2];
    for (i = 0; i < 7; i++) {
        blk.u34[i] = 0.0f;
    }
    blk.flags = (noshadow ? 0x400 : 0) | 0x900 | 0x14000 | 0x40000 | 0x80000;
    blk.ground = ground;
    blk.life = 300;
    blk.sound = 0x36;
    blk.u58 = 0;
    blk.u60[0] = 0xFF;
    for (i = 1; i < 8; i++) {
        blk.u60[i] = 0;
    }
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u69 = -1;
    out[0] = (u8 *) func_15132FBC(&blk, 3, 0xFF, 0, arg7, arg8);
    if (out[0] != NULL) {
        for (i = 0; i < 0x80; i += 0x40) {
            func_15133CD0((s32) (out[0] + i + 0x90), out[0]);
        }
    }
    blk.u69 = 2;
    anim.op0 = 2;
    anim.op1 = 4;
    anim.op2 = 6;
    anim.v0 = 0x3E;
    anim.v1 = 0x3E;
    blk.u68 = 0;
    for (k = 1; k < 3; k++) {
        if (k == 1) {
            anim.id0 = alt ? 0x87 : 0x8B;
            anim.id1 = alt ? 0x88 : 0x8C;
            blk.sound = 0x37;
        } else {
            anim.id0 = alt ? 0x89 : 0x8D;
            anim.id1 = alt ? 0x8A : 0x8E;
            blk.sound = 0x38;
        }
        out[k] = (u8 *) func_15132FBC(&blk, 3, 0xFF, 0x14, arg7, arg8);
        if (out[k] == NULL) {
            if (k == 1) {
                continue;
            }
            return;
        }
        for (i = 0; i < 0x80; i += 0x40) {
            func_15133CD0((s32) (out[k] + i + 0x90), out[k]);
        }
        memcpy((s32) (out[k] + 0x170), (u8 *) &anim, 0x14);
    }
}
