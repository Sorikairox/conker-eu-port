#ifdef NON_MATCHING
s32 func_15106794(struct102 *);
void func_15106B90(struct102 *);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 func_150ADA20(void);
void *memcpy(void *, const void *, unsigned int);

/* The 0x70-byte particle spec func_151307F0 gets for each arc end. */
typedef struct {
    s32 w00;            /* 0x00 0x200005 */
    s32 w04;            /* 0x04 0 */
    s16 h08;            /* 0x08 0x4404 */
    s16 life;           /* 0x0A 300 */
    s32 w0C, w10;       /* 0x0C 0 */
    u8 rgba0[4];        /* 0x14 FF FF FF FF */
    u8 rgba1[4];        /* 0x18 the arc's colour (spec +0x48..+0x4B) */
    u8 b1C, b1D;        /* 0x1C 0xFF 0x2B */
    s16 h1E, h20, h22;  /* 0x1E 1, 0xFF, 1 */
    f32 f24;            /* 0x24 1.0 */
    f32 size[2];        /* 0x28 width * (1 / 13) * 200 (both) */
    f32 pos[3];         /* 0x30 the arc end */
    f32 f3C[3];         /* 0x3C D_800A5860 */
    f32 f48[3];         /* 0x48 D_800A5860 */
    f32 f54;            /* 0x54 0 */
    s32 flags;          /* 0x58 bits 0x40 / 0x80 random */
    s32 w5C;            /* 0x5C 0 */
    u8 b60, b61;        /* 0x60 6 6 */
    s8 b62, b63, b64;   /* 0x62 -1 -1 -1 */
    u8 b65, b66;        /* 0x65 0 0xFF */
    s16 h68;            /* 0x68 0 */
    f32 f6C;            /* 0x6C 1000000.0 */
} ArcEndSpec;

// bolt_arc_spawn: creates a lightning arc object (type 0x40, func_15167A68 layer `layer` / `arg3`) from the 0x50-byte
// arc spec `spec` (copied to +0x10; +0x38 = segment count n, +0x40 width, +0x44 / +0x46 life base / random range,
// +0x48 colour). The object's data area (+0x60) follows its 0x88-byte header, n * 0x34 + (n + 2) * 0xC bytes in and
// `extra` more bytes are reserved for the caller. Sets the step 1 / (n + 1) (+0x64) and the life (+0x68), builds the
// points (func_15106794, func_15106B90), clears +0x6C..+0x83, sets +0x84 = n * 0x30 + 0x60 and spawns one glow
// particle at each arc end (func_151307F0, handles at +0x6C / +0x70). Returns the object (NULL when none is free).
u8 *func_15106260(s16 *spec, s32 extra, u8 layer, s32 arg3) {
    ArcEndSpec ps;
    u8 *p = (u8 *)spec;
    u8 *obj;
    s32 n = *(s32 *)(p + 0x38);
    s32 flags;
    u8 i;

    obj = func_15167A68(0x40, arg3, n * 0x34 + (n + 2) * 0xC + extra + 0x88, 1, layer, 1);
    if (obj == NULL) {
        return NULL;
    }
    memcpy(obj + 0x10, p, 0x50);
    *(u8 **)(obj + 0x60) = obj + n * 0x34 + (n + 2) * 0xC + 0x88;
    *(f32 *)(obj + 0x64) = 1.0f / (f32)(*(s32 *)(p + 0x38) + 1);
    *(s16 *)(obj + 0x68) = (u32)func_150ADA20() % (u32)(*(s16 *)(p + 0x46) + 1) + *(s16 *)(p + 0x44);
    func_15106794((struct102 *)obj);
    func_15106B90((struct102 *)obj);
    *(s32 *)(obj + 0x6C) = 0;
    *(s32 *)(obj + 0x70) = 0;
    bzero(obj + 0x74, 0x10);
    *(s32 *)(obj + 0x84) = *(s32 *)(obj + 0x48) * 0x30 + 0x60;

    ps.w00 = 0x200005;
    ps.w04 = 0;
    ps.h08 = 0x4404;
    ps.life = 300;
    ps.w0C = 0;
    ps.w10 = 0;
    ps.rgba0[0] = 0xFF;
    ps.rgba0[1] = 0xFF;
    ps.rgba0[2] = 0xFF;
    ps.rgba0[3] = 0xFF;
    ps.rgba1[0] = p[0x48];
    ps.rgba1[1] = p[0x49];
    ps.rgba1[2] = p[0x4A];
    ps.rgba1[3] = p[0x4B];
    ps.b1C = 0xFF;
    ps.b1D = 0x2B;
    ps.h1E = 1;
    ps.h20 = 0xFF;
    ps.h22 = 1;
    ps.f24 = 1.0f;
    ps.f3C[0] = ((f32 *) D_800A5860)[0];
    ps.f3C[1] = ((f32 *) D_800A5860)[1];
    ps.f3C[2] = ((f32 *) D_800A5860)[2];
    ps.f48[0] = ((f32 *) D_800A5860)[0];
    ps.f48[1] = ((f32 *) D_800A5860)[1];
    ps.f48[2] = ((f32 *) D_800A5860)[2];
    ps.f54 = 0.0f;
    ps.w5C = 0;
    ps.b60 = 6;
    ps.b61 = 6;
    ps.b62 = -1;
    ps.b63 = -1;
    ps.b64 = -1;
    ps.b65 = 0;
    ps.b66 = 0xFF;
    ps.h68 = 0;
    ps.f6C = 1000000.0f;
    ps.size[1] = *(f32 *)(p + 0x40) * 0.07692308f * 200.0f;
    ps.size[0] = ps.size[1];

    for (i = 0; i < 2; i++) {
        f32 *end = (f32 *)(p + (i == 0 ? 0x04 : 0x28));   /* the arc start, then its end */

        ps.pos[0] = end[0];
        ps.pos[1] = end[1];
        ps.pos[2] = end[2];
        flags = func_150ADA20() ? 0x40 : 0;
        ps.flags = (func_150ADA20() ? 0x80 : 0) | flags;
        *(s32 *)(obj + 0x6C + i * 4) = func_151307F0((s32)&ps, 0, 0, 0, layer, arg3);
    }
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106260.s")
#endif
