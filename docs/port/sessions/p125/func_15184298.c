extern u8 D_8008D450[];
extern u8 *D_8008D760[];
void func_151661F0(f32 *angle, s16 *vtx, f32 amp, f32 *speed, f32 max, f32 min, u8 *rows, u8 n);
void func_1517A320(u8 i);
void func_151777CC(u8 arg0);
void func_15184198(s32 arg0);

/* anim_meshes_update: per frame, the 11 animated mesh slots (D_800DDE80: 5 words each, block +0, Vtx buffers +4 /
 * +8; display list D_800DDF78[i]; state D_800DDF68[i]: 1 = just set up, then 0, -1, -2 = gone).
 * A live slot that lost its block or display list becomes -2. The four byte timers D_800DDF60[0..3] count down by
 * the frame step. Slots 0..6 that are newly active swing buffer +8 (func_151661F0 with D_8008D450[i]: angle +0x18,
 * speed +0x24, max +0x28, min +0x2C, amplitude +0x30, rows D_8008D760[i], 2 * pairs), slots 2..4 also swing
 * buffer +4 with entry i + 9; slot 7 runs func_151777CC(7) and sets slot 10's state to 1; slots 8 / 9 wave
 * (func_1517A320); gone slots that still hold a block are released (func_15184198). Then every state ages:
 * > 0 -> 0, 0 / -1 -> one lower, -2 stays. */
void func_15184298(void) {
    static const u8 pairs[7] = { 2, 2, 2, 2, 2, 2, 4 };
    u8 *e;
    s32 v;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] >= -1 && (D_800DDE80[i * 5] == 0 || D_800DDF78[i] == 0)) {
            D_800DDF68[i] = -2;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_800DDF60[i] > 0) {
            v = D_800DDF60[i] - D_800BE9E4;
            if (v < 0) {
                v = 0;
            }
            D_800DDF60[i] = v;
        }
    }
    for (i = 0; i < 7; i++) {
        if (D_800DDF68[i] == 1) {
            e = D_8008D450 + i * 0x38;
            func_151661F0((f32 *) (e + 0x18), (s16 *) D_800DDE80[i * 5 + 2], *(f32 *) (e + 0x30), (f32 *) (e + 0x24),
                          *(f32 *) (e + 0x28), *(f32 *) (e + 0x2C), D_8008D760[i], pairs[i]);
        }
    }
    for (i = 2; i < 5; i++) {
        if (D_800DDF68[i] == 1) {
            e = D_8008D450 + (i + 9) * 0x38;
            func_151661F0((f32 *) (e + 0x18), (s16 *) D_800DDE80[i * 5 + 1], *(f32 *) (e + 0x30), (f32 *) (e + 0x24),
                          *(f32 *) (e + 0x28), *(f32 *) (e + 0x2C), D_8008D760[i], pairs[i]);
        }
    }
    if (D_800DDF68[7] == 1) {
        func_151777CC(7);
    }
    for (i = 0; i < 2; i++) {
        if (D_800DDF68[8 + i] == 1) {
            func_1517A320(i + 8);
        }
    }
    if (D_800DDF68[7] == 1) {
        D_800DDF68[10] = 1;
    }
    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] == -2 && D_800DDE80[i * 5] != 0) {
            func_15184198(i);
        }
    }
    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] > 0) {
            D_800DDF68[i] = 0;
        } else if (D_800DDF68[i] >= -1) {
            D_800DDF68[i]--;
        }
    }
}
