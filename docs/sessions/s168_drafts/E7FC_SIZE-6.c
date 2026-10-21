typedef struct {
    u8 v[2];
} Pair7FC;
typedef struct {
    f32 x;
    f32 y;
    s32 z;
} Pos7FC;
extern Pair7FC D_8008D3A4;
extern Pair7FC D_8008D3A8;
extern Pair7FC D_8008D3AC;
extern u8 D_800DE190;
s32 func_1517EA18(s32, u8 *, u8, u8, u8, s32, u8 *);
s32 func_1517F01C(f32, f32, s32, f32 *, f32 *);
s32 func_1517F18C(u8 *, s32 *);

s32 func_1517E7FC(s32 arg0, s32 arg1) {
    s32 alpha;
    s32 dist;
    Pair7FC a;
    Pair7FC b;
    Pair7FC c;
    u8 *node;
    s32 skip;
    u8 *flag;
    Pos7FC *pos;

    a = D_8008D3A4;
    b = D_8008D3A8;
    c = D_8008D3AC;
    node = (u8 *)D_800DDD64;
    D_800DE190 = 0;
    while (node != NULL) {
        if (node[0x30] != 0) {
            skip = 0;
            if (node[0x2E] & 1) {
                if (D_800DCDD0 == 0) {
                    skip = 1;
                } else {
                    pos = (Pos7FC *)D_8008CFFC[D_800B0DF0->unk10];
                    alpha = 0xFF;
                    if (func_1517F01C(pos->x, pos->y, pos->z, (f32 *)(node + 0xC), (f32 *)(node + 0x10)) != 1) {
                        skip = 1;
                    }
                    if (*(u16 *)(node + 0x2A) != 0xFFFC) {
                        alpha = -1;
                    }
                }
            } else {
                if (func_1517F18C(node, &dist) != 1) {
                    skip = 1;
                }
                alpha = -1;
                if (*(u16 *)(node + 0x2C) - dist < 30) {
                    alpha = 0x100;
                }
            }
            flag = NULL;
            if (node[0x2E] & 2) {
                flag = &D_800DD2D0;
            }
            if (skip == 0) {
                arg0 = func_1517EA18(arg0, node, a.v[node[0x2F]], b.v[node[0x2F]], c.v[node[0x2F]], alpha, flag);
            } else if (flag != NULL) {
                *flag = 0;
            }
        }
        node = *(u8 **)(node + 0x24);
    }
    return arg0;
}
