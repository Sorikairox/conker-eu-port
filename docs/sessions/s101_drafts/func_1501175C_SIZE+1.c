extern f32 D_800968B8, D_800968BC, D_eu_800968C0, D_800968C4, D_800968C8, D_800968CC, D_800968D0, D_800968D4;
typedef struct { f32 x, y, z; } V3s101;

void func_1501175C(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *obj;
    struct {
        u8 *p;
        u8 b;
        s32 c;
        s32 d;
    } a;
    u8 *p;
    struct {
        u8 *p;
        u8 b;
        f32 f08;
        f32 f0C;
        f32 f10;
        f32 f14;
        f32 f18;
        f32 f1C;
        f32 f20;
        f32 f24;
        f32 f28;
        f32 f2C;
        f32 f30;
        f32 f34;
        f32 f38;
        f32 f3C;
        f32 f40;
        f32 f44;
        f32 f48;
        f32 f4C;
        u8 *obj;
        f32 f54;
        s8 b58;
    } b;
    s32 v;
    u8 *q;
    struct {
        s8 u00;
        s8 u01;
        s16 u02;
        s16 u04;
        s32 u08;
        s32 u0C;
        u8 u10;
        u8 u11;
        u8 u12;
        u8 u13;
        f32 u14;
        f32 u18;
        V3s101 u1C;
        V3s101 u28;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        s8 u44;
        u8 u45;
        s8 u46;
        s8 u47;
        s32 u48;
    } c;
    Header2 header2;
    Header header;

    a.p = arg0;
    a.c = 0;
    a.d = 0;
    a.b = arg0[0x3B];
    obj = (u8 *)func_15149130(0x12C, -1, 0x54, -1, 0, 0x34, (struct37 *)0x10, arg1, arg2);
    p = obj + 0x28;
    if (obj != NULL) {
        memcpy(p, &a, 0x10);
        b.b58 = 0;
        b.p = arg0;
        b.f54 = (*(f32 *)(arg0 + 0x14C) + *(f32 *)(arg0 + 0x150)) * 0.5f;
        b.f08 = D_800968B8;
        b.f10 = D_800968BC;
        b.f18 = D_eu_800968C0;
        b.f0C = D_800968C4;
        b.f24 = 0.0f;
        b.f28 = 0.0f;
        b.f38 = 0.0f;
        c.u14 = 0.0f;
        c.u18 = 0.0f;
        b.f3C = 0.0f;
        b.f48 = 1.0f;
        b.f40 = 1.0f;
        b.f4C = 1.0f;
        b.f44 = 1.0f;
        b.obj = obj;
        c.u00 = 0x5F;
        c.u01 = 9;
        c.u02 = 0x2203;
        c.u04 = 0x12C;
        c.u08 = 0;
        c.u0C = 0;
        c.u10 = 0xFF;
        c.u11 = 0xFF;
        c.u12 = 0xFF;
        c.u13 = 0xFF;
        b.b = arg0[0x3B];
        b.f14 = D_800968C8;
        b.f20 = D_800968CC;
        b.f1C = D_800968D0;
        b.f2C = 160.0f;
        b.f30 = 95.0f;
        b.f34 = D_800968D4;
        c.u1C = *(V3s101 *)D_800A5860;
        c.u28 = *(V3s101 *)D_800A5860;
        c.u34 = 1.0f;
        c.u38 = 1.0f;
        c.u3C = 1.0f;
        c.u40 = 7.375f;
        c.u44 = 0;
        c.u45 = 0xFF;
        c.u46 = 0;
        c.u47 = 7;
        c.u48 = 0;
        if (func_150ADA20() & 1) {
            v = 2;
        } else {
            v = 0;
        }
        *(void **)(p + 8) = q = func_1513D2F0(&c, &D_800A4AA0, 0, 0x25, 0, 0x1D, v + 1, 0, 0, 0x5C, arg1, arg2);
        if (q != NULL) {
            memcpy(q + 0x110, &b, 0x5C);
        }
        header.unk0 = 2;
        header.unk1 = -1;
        header.unk2 = 0x12C;
        header.unk4 = 0;
        header2.unk0 = 0;
        header2.unk4 = 0;
        header2.unk8 = 0;
        *(void **)(p + 0xC) = func_151602C0(&header, &header2, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, arg1, arg2);
    }
}
