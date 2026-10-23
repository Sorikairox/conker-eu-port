u8 func_151D8E20(void);
void func_1514CBE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9,
                   s32 argA, u8 argB);
void func_151DBE80(s32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9);
typedef struct {
    f32 size;         /* 0x0 */
    s16 count;        /* 0x4 */
    u16 countRange;   /* 0x6 */
} DebrisDefAC3F0;
typedef struct {
    f32 u0;           /* 0x0 */
    s16 u4;           /* 0x4 */
    f32 u8;           /* 0x8 */
} FlashDefAC3F0;
extern s8 D_800A9400[][5];          /* per kind: chunk def, dust def, flash def (-1 = none) */
extern DebrisDefAC3F0 D_800A9420[]; /* chunks (type 0xB) */
extern DebrisDefAC3F0 D_800A9538[]; /* dust (type 0xC) */
extern FlashDefAC3F0 D_800A963C[];  /* flash */

// debris_burst_spawn: P153: the debris of a broken object of `kind` at pos (src = the owner): per D_800A9400[kind]
// a chunk burst (func_1514CBE8 type 0xB, def D_800A9420) and a dust burst (type 0xC, D_800A9538) with count
// +4 + random [0, +6], each with the owner block {src, arg4, light} (light = func_151D8E20()), and when src +0x1C
// bit 0 is set a flash (func_151DBE80, D_800A963C, 150) at pos, src + 4.
void func_151AC3F0(f32 *pos, u8 *src, s32 kind, u8 arg3, s32 arg4) {
    struct {
        u8 *src;
        s32 arg;
        u8 light;
    } chunkOwner, dustOwner;
    s8 *def;
    DebrisDefAC3F0 *d;
    FlashDefAC3F0 *fl;
    u8 light;

    light = func_151D8E20();
    if (src == NULL) {
        return;
    }
    def = D_800A9400[kind];
    if (def[0] != -1) {
        chunkOwner.src = src;
        chunkOwner.light = light;
        chunkOwner.arg = arg4;
        d = &D_800A9420[def[0]];
        func_1514CBE8(pos[0], pos[1], pos[2], d->size, 0, 0xFF, (u32) func_150ADA20() % (u32) (d->countRange + 1) + d->count,
                      0xB, kind, 0.0f, (s32) &chunkOwner, arg3);
    }
    if (def[2] != -1) {
        dustOwner.src = src;
        dustOwner.arg = arg4;
        dustOwner.light = light;
        d = &D_800A9538[def[2]];
        func_1514CBE8(pos[0], pos[1], pos[2], d->size, 0, 0xFF, (u32) func_150ADA20() % (u32) (d->countRange + 1) + d->count,
                      0xC, kind, 0.0f, (s32) &dustOwner, arg3);
    }
    if (def[4] != -1 && (src[0x1C] & 1)) {
        fl = &D_800A963C[def[4]];
        func_151DBE80(light, fl->u0, fl->u8, fl->u4, (u8 *) pos, (s32) (src + 4), 0x96, 0, arg3, arg4);
    }
}
