extern s32 (*D_8008FF30[])(u8 *, void *);   /* attach handlers: 0 func_151B7C28, 1 func_151B7C7C */
extern s32 D_800AA840[4];                    /* glow particle variants (low byte used) */
extern f32 D_800AA860;
/* glow particle spec read by func_151307F0 (same layout as SmokePuffSpec, one more byte at 0x66) */
typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 color[8];
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
    /* 0x60 */ s8 unk60[7];
} GlowSpec;
/* object spawn request for func_15147FF0 (as SA68D0) */
typedef struct {
    f32 pos[3];
    s16 u80;
    s16 u82;
    s32 u84;
    u8 u88;
    u8 u89;
} AttachSpawn;
/* the spawned object's +0x98 data block: glow handle, pointer to the copied attach data, attach type */
typedef struct {
    s32 glow;
    void *data;
    u8 type;
} AttachData;
// obj_attached_glow_spawn: spawns a helper object (func_15147FF0, extra size + 0x10) that follows something:
// its data block gets a copy of `size` bytes of `src` and the attach type; the type's handler (D_8008FF30[type],
// 0 = follow an object, 1 = follow a model point) places it, and if it fails the object is freed (returns NULL).
// Then a big glow particle (func_151307F0; variant D_800AA840[rand & 3], size rand * 800 + D_800AA860, life 300,
// random mirror flags) is started and its handle kept in the data block. Returns the object.
// Callers: func_1506AFCC (effect handler 12 of func_1506B04C, type 0), func_150B0574 (type 1).
u8 *func_151B78D8(void *src, u8 type, s32 size, u8 alpha, s32 arg4) {
    AttachSpawn a;
    AttachData d;
    AttachData *data;
    GlowSpec p;
    s32 flipX;
    s32 flipY;
    f32 glowSize;
    u8 *obj;

    d.glow = 0;
    d.data = NULL;
    d.type = type;
    a.u89 = 0x14;
    *(V368D0 *) a.pos = *(V368D0 *) D_800A5860;
    a.u80 = 300;
    a.u82 = 0x14;
    a.u84 = 0x10;
    a.u88 = 2;
    obj = (u8 *) func_15147FF0(&a, size + 0x10, 0x14, 0, 0xE, 0xE, 0, 0, 0, alpha, arg4);
    if (obj != NULL) {
        data = *(AttachData **) (obj + 0x98);
        memcpy(data, &d, sizeof(d));
        data->data = (u8 *) data + 0x10;
        memcpy(data->data, src, size);
        if (D_8008FF30[type](obj, obj + 0x10) == 0) {
            func_1516972C((struct102 *) obj);
            return NULL;
        }
        p.unk8 = 0x1303;
        p.type = 0x200005;
        p.unk1D = D_800AA840[func_150ADA20() & 3];
        p.unk4 = 0;
        p.life = 300;
        p.unkC = 0;
        p.unk10 = 0;
        p.color[0] = 0xFF;
        p.color[1] = 0xFF;
        p.color[2] = 0xFF;
        p.color[3] = 0xFF;
        p.color[4] = 0xFF;
        p.color[5] = 0xFF;
        p.color[6] = 0xFF;
        p.color[7] = 0xFF;
        p.unk1C = 0xFF;
        glowSize = func_150ADA68() * 800.0f + D_800AA860;
        p.size[1] = glowSize;
        p.size[0] = glowSize;
        p.pos[0] = a.pos[0];
        p.pos[1] = a.pos[1];
        p.pos[2] = a.pos[2];
        *(V368D0 *) p.vel = *(V368D0 *) D_800A5860;
        *(V368D0 *) p.accel = *(V368D0 *) D_800A5860;
        p.unk1E = 1;
        p.unk20 = 0xFF;
        p.unk22 = 1;
        p.unk54 = 0.0f;
        p.unk24 = 1.0f;
        flipX = (func_150ADA20() & 1) ? 0x40 : 0;
        flipY = (func_150ADA20() & 1) ? 0x80 : 0;
        p.flags = (flipY | flipX) | 0xC000 | 0x40000;
        p.unk60[0] = 6;
        p.unk60[1] = 5;
        p.unk60[2] = -1;
        p.unk60[3] = -1;
        p.unk60[4] = -1;
        p.unk60[5] = 0;
        p.unk5C = 0;
        p.unk60[6] = -1;
        data->glow = func_151307F0(&p, 1, 0, 0, alpha, arg4);
    }
    return obj;
}
