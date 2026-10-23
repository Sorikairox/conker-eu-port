s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern u8 D_800AB700[]; /* sprite per glow type */

// glow particle template of func_151307F0 (0x70 bytes, the func_15153BA4 layout)
typedef struct {
    s32 u0;           /* 0x00 */
    s32 u4;           /* 0x04 */
    u16 flags;        /* 0x08 */
    s16 life;         /* 0x0A */
    s32 uC;           /* 0x0C */
    s32 u10;          /* 0x10 */
    u8 colour[8];     /* 0x14: 7 bytes, alpha */
    u8 u1C;           /* 0x1C */
    u8 sprite;        /* 0x1D */
    s16 u1E;          /* 0x1E */
    s16 u20;          /* 0x20 */
    s16 u22;          /* 0x22 */
    f32 u24;          /* 0x24 */
    f32 size[2];      /* 0x28 */
    f32 pos[3];       /* 0x30 */
    f32 u3C[3];       /* 0x3C */
    f32 vel[3];       /* 0x48 */
    f32 u54;          /* 0x54 */
    s32 mode;         /* 0x58 */
    s32 u5C;          /* 0x5C */
    u8 u60[7];        /* 0x60 */
    u8 pad67;
    s16 u68;          /* 0x68 */
    u8 pad6A[2];
    f32 u6C;          /* 0x6C */
} GlowTmplC034;

// glow_particle_spawn: P153: spawns a glow particle (func_151307F0) at pos with size, alpha and life for glow
// `type` (sprite D_800AB700[type], flag 0x800000 when D_800AB710[type]); random flip bits 0x80 / 0x40, still
// (velocity D_800A5860). Returns func_151307F0's record.
s32 func_151DC034(f32 *pos, f32 size, u8 alpha, s16 life, u8 type, u8 arg5, s32 arg6) {
    GlowTmplC034 t;
    s32 bit80;
    s32 bit40;

    t.flags = 0x4403;
    t.u0 = 0x200005;
    t.sprite = D_800AB700[type];
    t.u4 = 0x9F0600;
    t.life = life;
    t.uC = 0;
    t.u10 = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    t.colour[4] = 0xFF;
    t.colour[5] = 0xFF;
    t.colour[6] = 0xFF;
    t.colour[7] = alpha;
    t.u1C = 0xFF;
    t.size[1] = size;
    t.size[0] = size;
    t.pos[0] = pos[0];
    t.pos[1] = pos[1];
    t.pos[2] = pos[2];
    t.u3C[0] = ((f32 *) D_800A5860)[0];
    t.u3C[1] = ((f32 *) D_800A5860)[1];
    t.u3C[2] = ((f32 *) D_800A5860)[2];
    t.vel[0] = ((f32 *) D_800A5860)[0];
    t.vel[1] = ((f32 *) D_800A5860)[1];
    t.vel[2] = ((f32 *) D_800A5860)[2];
    t.u1E = 4;
    t.u20 = 0x3F;
    t.u22 = 1;
    t.u54 = 0.0f;
    t.u24 = 1.0f;
    bit80 = 0;
    if (func_150ADA20() & 1) {
        bit80 = 0x80;
    }
    bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
    t.mode = (((u8 *) &D_800AB710)[type] != 0 ? 0x800000 : 0) | 1 | bit40 | bit80 | 0xC200 | 0x10000;
    t.u60[0] = 6;
    t.u60[1] = 8;
    t.u60[2] = 0xFF;
    t.u60[3] = 0xFF;
    t.u60[4] = 0xFF;
    t.u60[5] = 0;
    t.u5C = 0;
    t.u60[6] = 0xFF;
    t.u68 = 1000;
    t.u6C = 1000.0f;
    return func_151307F0((s32) &t, 1, 0, 0, arg5, arg6);
}
