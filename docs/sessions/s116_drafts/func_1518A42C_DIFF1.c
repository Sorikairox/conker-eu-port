typedef struct { f32 x, y, z; s32 a, b; } Node14;
u8 func_151D8E20(void);
extern f64 D_800A7788;
extern f32 D_800A7790;

s32 func_1518A42C(u8 *arg0) {
    s32 pad[2];
    u8 *obj;
    u8 *tbl;
    f32 pos[3];

    tbl = *(u8 **)(arg0 + 0x94);
    obj = *(u8 **)(arg0 + 0x98);
    if (*(f32 *)(tbl + *(s8 *)(arg0 + 0x2D) * 0x14 + 4) < *(f32 *)(obj + 0x48)) {
        if (func_150ADA68() < D_800A7788) {
            pos[0] = *(f32 *)(tbl + *(s8 *)(arg0 + 0x2D) * 0x14);
            pos[1] = *(f32 *)(obj + 0x48);
            pos[2] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
            func_151DBCBC(func_151D8E20(), *(f32 *)(obj + 0) * 6.0f, *(u8 *)(obj + 0x1B), 0, pos, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
        }
        *(s8 *)(obj + 0x20) = 4;
        *(f32 *)(obj + 0x48) = D_800A7790;
    }
    return 1;
}
