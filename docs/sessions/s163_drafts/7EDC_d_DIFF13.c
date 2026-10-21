typedef struct { f32 x, y, z; } V37EDC;
typedef struct { V37EDC a; V37EDC b; s32 u18; } E7EDC;
void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2);

s32 func_151D7EDC(u8 *arg0) {
    E7EDC *tbl;
    s32 i;

    tbl = *(E7EDC **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) < 2 && (*(u16 *)(arg0 + 0x1E) & 8)) {
        return 0;
    }
    i = *(s8 *)(arg0 + 0x2E);
    if (i != *(s8 *)(arg0 + 0x2D)) {
        do {
            i--;
            if (i < 0) {
                i = arg0[0x25] - 1;
            }
            func_151D8CC8(&tbl[i].a.x, &tbl[i].b.x, D_800BE9A4);
        } while (i != *(s8 *)(arg0 + 0x2D));
    }
    if (*(s8 *)(arg0 + 0x2C) > 0) {
        E7EDC *e = &tbl[*(s8 *)(arg0 + 0x2D)];

        *(V37EDC *)(arg0 + 0x54) = e->a;
    } else {
        *(f32 *)(arg0 + 0x54) = 0.0f;
        *(f32 *)(arg0 + 0x58) = 0.0f;
        *(f32 *)(arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
