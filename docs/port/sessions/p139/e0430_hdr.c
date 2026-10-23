/* P139: particle request passed to func_15132FBC by the pipe-explode spawn handlers (0x7C bytes; same layout as
 * game_eu_103160.c's DebrisParticle). */
typedef struct {
    /* 0x00 */ f32 scale[4];
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 one[3];
    /* 0x28 */ f32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8 u58;
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
} PipeParticleReq;

s32 func_15132FBC(void *req, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
f32 func_151423D8(u8);
