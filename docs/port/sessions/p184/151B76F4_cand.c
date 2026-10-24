s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151307F0(void *spec, s32 count, s32 arg2, s32 arg3, s32 alpha, s32 arg5);
extern f32 D_800AA85C;
/* particle spec read by func_151307F0 (offsets from its start) */
typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 color[8];   /* two RGBA colours */
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 vel[3];
    /* 0x48 */ f32 accel[3];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 flags;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s8 unk60[6];
} SmokePuffSpec;
// obj_smoke_puff_spawn: one random smoke puff particle at obj's position (func_151307F0, alpha arg1, arg2 passed
// on): size 89..139 (func_150ADA68 * 50 + 89), life 30..39, colours DD D3 CD FF / 57 55 5A (200..255 alpha),
// random mirror flags 0x40 / 0x80. Called by func_1506ADC8 (with func_151B68D0), handler 8 of func_1506B04C.
void func_151B76F4(u8 *obj, s32 alpha, s32 arg2) {
    SmokePuffSpec p;
    s32 flipX;
    s32 flipY;
    f32 size;

    p.unk1D = 0x29;
    p.unk8 = 0xE03;
    p.type = 0x200005;
    p.unk4 = 0;
    p.unkC = 0;
    p.unk10 = 0;
    p.unk1E = 0x12;
    p.unk20 = 0xE;
    flipX = (func_150ADA20() & 1) ? 0x40 : 0;
    flipY = (func_150ADA20() & 1) ? 0x80 : 0;
    p.flags = flipY | 1 | flipX | 0xCE00 | 0x10000;
    p.unk60[0] = 3;
    p.unk60[1] = 3;
    p.unk60[2] = -1;
    p.unk60[3] = -1;
    p.unk60[4] = -1;
    p.unk60[5] = 0;
    p.unk22 = 0x28;
    p.color[0] = 0xDD;
    p.color[1] = 0xD3;
    p.color[2] = 0xCD;
    p.color[3] = 0xFF;
    p.color[4] = 0x57;
    p.color[5] = 0x55;
    p.color[6] = 0x5A;
    p.unk1C = 0xFF;
    p.unk54 = 0.0f;
    p.unk24 = D_800AA85C;
    p.pos[0] = *(f32 *) (obj + 0x14);
    p.pos[1] = *(f32 *) (obj + 0x18);
    p.pos[2] = *(f32 *) (obj + 0x1C);
    p.vel[0] = 0.0f;
    p.vel[1] = 0.0f;
    p.vel[2] = 0.0f;
    p.color[7] = (u32) func_150ADA20() % 0x38 + 0xC8;
    p.life = (u32) func_150ADA20() % 10 + 0x1E;
    size = func_150ADA68() * 50.0f + 89.0f;
    p.accel[0] = 0.0f;
    p.accel[1] = 0.0f;
    p.size[0] = size;
    p.size[1] = size;
    p.accel[2] = 0.0f;
    func_151307F0(&p, 1, 0, 0, alpha & 0xFF, arg2);
}
