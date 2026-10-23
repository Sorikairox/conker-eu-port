/* P139: particle request passed to func_15132FBC (0x7C bytes; layout as game_eu_103160.c's DebrisParticle). */
typedef struct {
    /* 0x00 */ f32 scale[4];
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 one[3];
    /* 0x28 */ s32 pos[3];      /* copied as words */
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spin[3];
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8 colour;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 alpha;
    /* 0x61 */ u8 u61;
    /* 0x62 */ u8 u62[6];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6C */ void *owner;
    /* 0x70 */ u8 ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} ParticleReq1EC;

extern u8 D_8008FF60[3];   /* colours per index 0..2: 4, 2, 3 */
s32 func_15132FBC(void *req, s32, s32, s32, s32, s32);
s32 func_15133CD0(s32 arg0, u8 *arg1);

/*
 * ring_particle_spawn: spawns one ring particle (sprite 0x26, life 300, scale (1, 1, 0.923, 0.923; 0x3F6C49BB), rotated by
 * yaw about y, no motion) at the 3 words at pos (copied as they are), colour D_8008FF60[colour] (only colours 0..2;
 * else nothing and 0), flags 0xC1D00 | 0x4000 when flag (u8) is set, +0x5C = arg6, +0x61 = 0x18 in game mode 7
 * (D_800BE9F0). Request (arg2, (u8) arg3, 0, (u8) arg7, arg8). On success func_15133CD0(p + 0x90 + 0x40 * k, p)
 * for k = 0, 1. Returns the particle (0 on failure).
 */
s32 func_151BF490(f32 yaw, s32 posArg, s32 arg2, u8 arg3, s32 colour, s32 flag, s32 arg6, s32 arg7, s32 arg8) {
    s32 *pos = (s32 *) posArg;
    ParticleReq1EC req;
    u8 *p;
    s32 k;

    if ((u8) colour >= 3) {
        return 0;
    }
    req.scale[0] = 1.0f;
    req.scale[1] = 1.0f;
    req.scale[3] = 0.92300004f;
    req.scale[2] = 0.92300004f;
    req.rot[0] = 0.0f;
    req.rot[1] = yaw;
    req.rot[2] = 0.0f;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.pos[0] = pos[0];
    req.pos[1] = pos[1];
    req.pos[2] = pos[2];
    req.vel[0] = 0.0f;
    req.vel[1] = 0.0f;
    req.vel[2] = 0.0f;
    req.spin[0] = 0.0f;
    req.spin[1] = 0.0f;
    req.spin[2] = 0.0f;
    req.gravity = 0.0f;
    req.flags = ((u8) flag != 0 ? 0x4000 : 0) | 0x1D00 | 0x80000 | 0x40000;
    req.life = 300;
    req.sprite = 0x26;
    req.alpha = 0xFF;
    req.colour = D_8008FF60[(u8) colour];
    req.u5C = arg6;
    req.u61 = (D_800BE9F0 == 7) ? 0x18 : 0;
    req.u62[0] = 0;
    req.u62[1] = 0;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 2;
    req.u6A = 0;
    req.owner = NULL;
    req.ownerId = 0;
    req.u72 = 1;
    req.u74 = 0xFF;
    p = (u8 *) func_15132FBC(&req, arg2, arg3, 0, (u8) arg7, arg8);
    if (p != NULL) {
        for (k = 0; k != 0x80; k += 0x40) {
            func_15133CD0((s32) (p + 0x90 + k), p);
        }
    }
    return (s32) p;
}
