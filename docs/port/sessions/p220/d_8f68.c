/* P220: readable C for func_150C8F68 (game_eu_F6060, 212 words): update of the kind-0x31 ring effect (descriptor
 * at D_8008C238: update func_150C8F68, draw func_150C92B8). */
extern void (*D_80088BF8[])(u8 *, f32 *, u8, f32, f32); /* spawn handlers: func_150C9EB4, func_150CA2C4 */
extern s32 (*D_80088C00[])(u8 *);                        /* node handlers (0 = free the node): [1] func_150CA0DC */
extern s32 (*D_80088C04[])(u8 *);                        /* = D_80088C00 + 1: [0] func_150CA0DC */
extern f32 D_800A08FC; /* 2 pi */
extern f32 D_800A0900; /* max squared horizontal distance of a spawn point: 10894295 (3300.6^2) */
extern f32 D_800A0904; /* 256 / 360: degrees -> angle byte */
f32 func_151423D8(u8);
s32 func_150ADA20(void);
void func_1516972C(struct102 *arg0);

// ring_effect_update: per frame for a ring effect node: counts the life timer (+0x28, flag +0x1C & 1) down, grows
// the radius +0x44 by +0x20 per second, sets the fade value +0x40 (+0x2C per tick after +0x2A, +0x34 per tick before
// +0x30), spawns handler +0x3C's particles at a rate of +0x38 per radian of ring per second (each at a random angle
// around the camera's view direction, only within D_800A0900 of the world origin), calls handler +0x3D with the old
// radius (the only entry ignores it) and handler +0x1D; frees the node when the timer runs out or +0x1D returns 0.
void func_150C8F68(u8 *node) {
    u8 dead = 0;

    if (node[0x1C] & 1) {
        *(s16 *)(node + 0x28) -= D_800BE9E4;
        if (*(s16 *)(node + 0x28) < 0) {
            dead = 1;
        }
    }
    if (!dead) {
        f32 oldRadius = *(f32 *)(node + 0x44);
        s16 t;
        *(f32 *)(node + 0x44) = oldRadius + *(f32 *)(node + 0x20) * D_800BE9A4;
        t = *(s16 *)(node + 0x28);
        if (*(s16 *)(node + 0x2A) < t) {
            *(f32 *)(node + 0x40) = (f32)(s16)(*(s16 *)(node + 0x4C) - t) * *(f32 *)(node + 0x2C);
        }
        if (t < *(s16 *)(node + 0x30)) {
            *(f32 *)(node + 0x40) = (f32)t * *(f32 *)(node + 0x34);
        }
        if ((s8)node[0x3C] != -1) {
            *(f32 *)(node + 0x50) += *(f32 *)(node + 0x38) * D_800BE9A4 * (D_800A08FC * *(f32 *)(node + 0x44));
            while (1.0f < *(f32 *)(node + 0x50)) {
                s32 view = (s32)(*(f32 *)((u8 *)D_800DBFF0 + D_80082FA4 * 0x9A0 + 0x380) * D_800A0904);
                s32 a = (u32)func_150ADA20() % 81 + view - 0x28;
                f32 s = func_151423D8((u8)(a - 0x40));
                f32 c = func_151423D8((u8)a);
                f32 pos[3]; /* sp74 */
                pos[0] = *(f32 *)(node + 0x10) + s * *(f32 *)(node + 0x44);
                pos[1] = *(f32 *)(node + 0x14);
                pos[2] = *(f32 *)(node + 0x18) + c * *(f32 *)(node + 0x44);
                if (pos[0] * pos[0] + pos[2] * pos[2] < D_800A0900) {
                    D_80088BF8[(s8)node[0x3C]](node, pos, (u8)a, s, c);
                }
                *(f32 *)(node + 0x50) -= 1.0f;
            }
        }
        if ((s8)node[0x3D] != -1) {
            /* the asm also passes oldRadius in a1; the table's only entry (func_150CA0DC) takes the node alone */
            D_80088C04[(s8)node[0x3D]](node);
        }
        if ((s8)node[0x1D] != -1) {
            if (D_80088C00[(s8)node[0x1D]](node) == 0) {
                dead = 1;
            }
        }
    }
    if (dead) {
        func_1516972C((struct102 *)node);
    }
}
