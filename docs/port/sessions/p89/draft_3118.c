void *func_1505ED34(void);
u8 *func_15159140(u8 *arg0, u8 arg1, s32 arg2);
u8 *func_1515D9F0(s32 arg0);
void *func_1515D9B0(void);

#define O_U8(o, off)  (*(u8 *) ((u8 *) (o) + (off)))
#define O_S16(o, off) (*(s16 *) ((u8 *) (o) + (off)))
#define O_S32(o, off) (*(s32 *) ((u8 *) (o) + (off)))
#define O_F32(o, off) (*(f32 *) ((u8 *) (o) + (off)))

/* Spawns a child object (type 0x21) of `parent` at offset (x, y, z) from joint `joint` (the parent's position when it
 * has no joint matrices or joint == -1), yawed by `angle` degrees from the parent; scale-like fields 0x3C / 0x20 / 0x24
 * = s3c / s20 / s24, byte 0x83 = b83. Returns the new object. */
u8 *func_15073118(struct127 *parent, s32 joint, s32 kind, f32 x, f32 y, f32 z, f32 angle, f32 s3c, f32 s20, f32 s24,
                         s32 b83) {
    struct127 *o = func_1505ED34();
    f32 mf[4][4];
    f32 (*m)[4];
    f32 px, py, pz;
    f32 yaw;
    u32 a;
    s32 i;

    O_F32(o, 0x24) = s24;
    O_F32(o, 0x20) = s20;
    O_F32(o, 0x3C) = s3c;
    O_U8(o, 0x83) = b83;
    if (parent->unk1D4 != NULL && joint != -1) {
        m = (f32 (*)[4]) ((u8 *) parent->unk1D4 + joint * 64);
        if (D_800C42B0 != 0) {
            guMtxL2F(mf, (Mtx *) m);   /* fixed-point joint matrices */
            m = mf;
        }
        func_150A7E40(m, x, y, z, &px, &py, &pz);
    } else {
        px = O_F32(parent, 0x14);
        py = O_F32(parent, 0x18);
        pz = O_F32(parent, 0x1C);
    }
    O_F32(o, 0x14) = px;
    O_F32(o, 0x18) = py;
    O_F32(o, 0x1C) = pz;
    /* yaw in 1/65536 turns; float -> u32 as the asm: <= -1 gives 0xFFFFFFFF */
    yaw = (f32) *(u16 *) ((u8 *) parent + 0x7A) + angle * 182.04445f;
    a = yaw <= -1.0f ? 0xFFFFFFFF : (u32) yaw;
    *(u16 *) ((u8 *) o + 0x7A) = a;
    *(u16 *) ((u8 *) o + 0x76) = a;
    O_S32(o, 0x0) = 0x21;
    O_U8(o, 0x125) = 0xFF;
    O_S32(o, 0xF8) = 2;
    if (kind != 0x42) {
        O_S32(o, 0xF8) = 0x100E;
    }
    O_U8(o, 0x66) = O_U8(parent, 0x66) & 0xC;
    O_S16(o, 0xE4) = 10;
    O_S16(o, 0xE6) = 10;
    O_F32(o, 0xEC) = 1.0f;
    O_F32(o, 0xF0) = 1.0f;
    O_F32(o, 0xDC) = 1.0f;
    O_F32(o, 0xE0) = 1.0f;
    O_F32(o, 0x14C) = 0.5f;
    O_F32(o, 0x150) = 0.5f;
    if (kind == 0x1F) {
        O_F32(o, 0xC8) = 10.0f;
    }
    O_S16(o, 0x278) = kind;
    O_U8(o, 0x5) = 5;
    O_U8(o, 0x3B) = 0xFF - (s32) ((u8 *) o - (u8 *) D_800CC2D0) / 0x32C;
    func_15083568(o, kind, 1.0f, 0);
    for (i = 0; i <= D_80082FA0; i++) {
        O_S32(o, 0x304 + i * 4) = (s32) func_1515D9F0(1);
    }
    if (O_S32(o, 0x300 + i * 4) != 0) {   /* the last slot written (i == 0: the word at 0x300) */
        O_U8(o, 0x301) = 1;
    }
    O_S32(o, 0x314) = (s32) func_1515D9B0();
    func_1514F18C(func_15159140((u8 *) o, 1, 0), o, 0x13);
    return (u8 *) o;
}
