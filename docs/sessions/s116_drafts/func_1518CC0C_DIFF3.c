typedef struct { f32 x, y, z; s32 a, b; } Node14;
typedef struct {
    u8 pad0[0x80];
    s32 u80;
    u8 pad84[6];
    s16 u8A;
    s16 u8C;
    s16 u8E;
    s16 u90;
    s16 u92;
    s16 u94;
    s16 u96;
    s16 u98;
    u8 pad9A[6];
    s8 uA0;
    s8 uA1;
    s8 uA2;
    u8 padA3[5];
} SpawnCC0C;
s32 func_1516865C(SpawnCC0C *, s32, s32, s32, s32);
s32 func_15168800(SpawnCC0C *, u8, u8);
u8 func_151D8E20(void);
void func_151DBCBC(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void *arg4, u8 arg5, s32 arg6);

s32 func_1518CC0C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    SpawnCC0C sp;
    u8 *obj;
    u8 *tbl;
    u8 id;
    f32 pos[3];

    obj = *(u8 **)(arg0 + 0x98);
    tbl = *(u8 **)(arg0 + 0x94);
    arg2 = arg4; // fakematch: the unused arg2 holds the truncated arg4
    sp.u80 = 0;
    sp.u8A = 0x100;
    sp.u8C = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
    sp.u8E = arg2;
    sp.u90 = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
    sp.u92 = sp.u94 = func_150ADA20() % 21U + 0x23;
    sp.uA2 = -1;
    sp.uA0 = 0x12;
    sp.u98 = 0xC;
    sp.uA1 = 0;
    sp.u96 = arg2;
    func_1516865C(&sp, 0xFF, 0xFF, 0xFF, 0xFF);
    func_15168800(&sp, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    *(s8 *)(obj + 0x20) = 4;
    pos[0] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
    pos[1] = arg4;
    pos[2] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
    id = func_151D8E20();
    func_151DBCBC(id, 100.0f + func_150ADA68() * 40.0f, 0xFF, arg5, pos, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    return 1;
}
