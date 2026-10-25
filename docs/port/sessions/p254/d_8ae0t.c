#ifdef NON_MATCHING
s32 func_1505D024(struct127 *obj, s32 flags, u16 val, s32 arg3);
u8 *func_1518D1C0(u8 *obj, s16 type, s16 time, u8 clear, u8 view, s32 arg5, char *name);
// path_flame_touch_player: path handler 0 of D_8008FC20 (`s32 (*)(u8 *)`, result tested by the path updater).
// Walks back from the path's head point +0x2E to the current point +0x2D (ring of +0x25 points of 0x24 bytes at
// +0x94); when player 0 (D_800CC2D0[0]: x +0x14, y +0x18 + s16 +0xE8, z +0x1C) is within its radius s16 +0xE4 of a
// point (the height difference scaled by (1 + r / +0xE6) / 2), it is hurt (func_1505D024 flags 0x60006 with its u16
// +0x7A, by the owner object **(arg0 + 0x98)), gets the flame-thrower effect (func_1518D1C0 type 0xB with the
// emitter's +0x0C / +0x01), and the current point advances to that point (count +0x2C drops by one per step).
// Always returns 1.
s32 func_15198AE0(u8 *arg0) {
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *owner = *(u8 **) (arg0 + 0x98);
    u8 *player = (u8 *) D_800CC2D0;
    f32 *pt;
    f32 radius;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    i = *(s8 *) (arg0 + 0x2E);
    while (i != *(s8 *) (arg0 + 0x2D)) {
        i--;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        pt = (f32 *) (points + i * 0x24);
        radius = *(s16 *) (player + 0xE4);
        height = *(s16 *) (player + 0xE6);
        dx = pt[0] - *(f32 *) (player + 0x14);
        dz = pt[2] - *(f32 *) (player + 0x1C);
        dy = (pt[1] - (*(f32 *) (player + 0x18) + *(s16 *) (player + 0xE8))) * ((1.0f + radius / height) * 0.5f);
        if (dx * dx + dy * dy + dz * dz < radius * radius) {
            func_1505D024(D_800CC2D0, 0x60006, *(u16 *) (player + 0x7A),
                          (s32) (*(u8 **) owner - (u8 *) D_800CC2D0) / 0x32C);
            func_1518D1C0(player, 0xB, 0, 1, arg0[0xC], arg0[1], (char *) 0x800A8E64 /* difftest-only: the ROM string address */);
            while (i != *(s8 *) (arg0 + 0x2D)) {
                (*(s8 *) (arg0 + 0x2D))++;
                if (arg0[0x25] == *(s8 *) (arg0 + 0x2D)) {
                    *(s8 *) (arg0 + 0x2D) = 0;
                }
                (*(s8 *) (arg0 + 0x2C))--;
            }
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198AE0.s")
#endif
