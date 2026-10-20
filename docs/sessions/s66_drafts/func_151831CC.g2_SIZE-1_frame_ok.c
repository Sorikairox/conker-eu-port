extern u8 D_800DE284[];
f32 func_151834C8(s32 arg0, s32 arg1);
extern s16 D_8008D400;
extern s16 D_8008D402;
extern u8 *D_800DE290[];

void func_151831CC(u8 *arg0) {
    s32 id;
    u8 *out;
    u8 *base;
    s32 i;
    s32 off;
    f32 w[2];
    s32 k;
    s32 k1;
    f32 mtx[4][4];
    f32 x;
    f32 y;
    f32 z;
    f32 f;
    u8 *v;
    u8 *p;
    u8 *tbl;
    u8 **tblp;

    id = *(s32 *)(arg0 + 0x3C);
    p = &D_800DE284[id];
    base = *(u8 **)(arg0 + D_800BE9C0 * 4 + 0x20);
    func_150A8050(mtx, 0.0f, -*(s16 *)((u8 *)&D_8008D400 + *p * 0x18), 0.0f);
    tblp = &D_800DE290[id];
    for (i = 0, off = 0, out = base; i < *(u16 *)((u8 *)&D_800DBEF4[*(s16 *)((u8 *)&D_8008D402 + *p * 0x18)] + 0x16); i++, off += 0x10, out += 0x10) {
        f = func_151834C8(*(s16 *)(*(u8 **)(arg0 + 0x28) + off + 4), id);
        k = f;
        k1 = k + 1;
        if (k1 >= 0x28) {
            k1 = 0x27;
        }
        f -= k;
        tbl = *tblp;
        w[0] = *(f32 *)(tbl + k * 0xC + 8) * (1.0f - f);
        w[1] = *(f32 *)(tbl + k1 * 0xC + 8) * f;
        v = *(u8 **)(arg0 + 0x28) + off;
        func_150A7E40(mtx, *(s16 *)(v + 0), *(s16 *)(v + 2) + ((s32)(w[1] + w[0]) >> 4), *(s16 *)(v + 4), &x, &y, &z);
        *(s16 *)(out + 0) = *(s16 *)(arg0 + 0x10) + x;
        *(s16 *)(out + 2) = *(s16 *)(arg0 + 0x12) + y;
        *(s16 *)(out + 4) = *(s16 *)(arg0 + 0x14) + z;
    }
}
