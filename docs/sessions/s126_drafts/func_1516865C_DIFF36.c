extern u8 *D_8008CDEC[];
typedef struct { Vtx v[8]; s16 unk80[4]; s16 unk88; s16 pad8A[7]; u16 unk98; s16 pad9A; s16 unk9C; s16 unk9E; u8 unkA0; } S865C;
void func_1516865C(S865C *arg0, u8 r, u8 g, u8 b, u8 a) {
    s32 i, j;
    Vtx *p;
    s16 s0, t0, s1, t1;
    u8 *tex;
    s0 = 0x2000;
    s1 = 0x2000;
    tex = D_8008CDEC[arg0->unkA0];
    t1 = (*(u16 *)(tex + 8) + 0x100) << 5;
    t0 = (*(u16 *)(tex + 6) + 0x100) << 5;
    p = arg0->v;
    for (i = 0; i < 2; i++) {
        p += 4;
        p[-3].v.flag = 0;
        p[-3].v.cn[0] = r;
        p[-3].v.cn[1] = g;
        p[-3].v.cn[2] = b;
        p[-3].v.cn[3] = a;
        p[-2].v.flag = 0;
        p[-2].v.cn[0] = r;
        p[-2].v.cn[1] = g;
        p[-2].v.cn[2] = b;
        p[-2].v.cn[3] = a;
        p[-1].v.flag = 0;
        p[-1].v.cn[0] = r;
        p[-1].v.cn[1] = g;
        p[-1].v.cn[2] = b;
        p[-1].v.cn[3] = a;
        p[-4].v.flag = 0;
        p[-4].v.cn[0] = r;
        p[-4].v.cn[1] = g;
        p[-4].v.cn[2] = b;
        p[-4].v.cn[3] = a;
    }
    if (arg0->unk98 & 0x80) {
        t1 = 0x2000;
        s0 = (*(u16 *)(D_8008CDEC[arg0->unkA0] + 8) + 0x100) << 5;
    }
    if (arg0->unk98 & 0x100) {
        t0 = 0x2000;
        s1 = (*(u16 *)(D_8008CDEC[arg0->unkA0] + 6) + 0x100) << 5;
    }
    arg0->v[1].v.tc[0] = arg0->v[5].v.tc[0] = arg0->v[2].v.tc[0] = arg0->v[6].v.tc[0] = s1;
    arg0->unk88 = 0;
    arg0->v[2].v.tc[1] = arg0->v[6].v.tc[1] = arg0->v[3].v.tc[1] = arg0->v[7].v.tc[1] = s0;
    arg0->unk9C = 0;
    arg0->unk9E = 0;
    arg0->v[0].v.tc[0] = arg0->v[4].v.tc[0] = arg0->v[3].v.tc[0] = arg0->v[7].v.tc[0] = t0;
    arg0->v[0].v.tc[1] = arg0->v[4].v.tc[1] = arg0->v[1].v.tc[1] = arg0->v[5].v.tc[1] = t1;
}
