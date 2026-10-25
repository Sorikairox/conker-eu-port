/* func_1501175C records (stack images; pad bytes stay unset like the asm's) */
typedef struct {
    u8 *obj;        /* 0x00 */
    u8 room;        /* 0x04 obj +0x3B */
    u8 pad5[3];
    void *glow;     /* 0x08 func_1513D2F0 result */
    void *smoke;    /* 0x0C func_151602C0 result */
} Link175C;         /* 0x10, copied to the type 0x12C object +0x28 */

typedef struct {
    u8 u0;          /* 0x00 0x5F */
    u8 u1;          /* 0x01 9 */
    s16 u2;         /* 0x02 0x2203 */
    s16 u4;         /* 0x04 0x12C */
    u8 pad6[2];
    s32 u8_;        /* 0x08 */
    s32 uC;         /* 0x0C */
    u8 rgba[4];     /* 0x10 */
    f32 u14;        /* 0x14 */
    f32 u18;        /* 0x18 */
    f32 pos[3];     /* 0x1C D_800A5860 */
    f32 pos2[3];    /* 0x28 D_800A5860 */
    f32 scale[3];   /* 0x34 */
    f32 u40;        /* 0x40 */
    u8 u44;         /* 0x44 */
    u8 u45;         /* 0x45 */
    u8 u46;         /* 0x46 */
    u8 u47;         /* 0x47 */
    s32 u48;        /* 0x48 */
    u8 pad4C[0xC];
} Glow175C;         /* func_1513D2F0 template */

typedef struct {
    u8 *obj;        /* 0x00 */
    u8 room;        /* 0x04 */
    u8 pad5[3];
    f32 u8_;        /* 0x08 */
    f32 uC;         /* 0x0C */
    f32 u10;        /* 0x10 */
    f32 u14;        /* 0x14 */
    f32 u18;        /* 0x18 */
    f32 u1C;        /* 0x1C */
    f32 u20;        /* 0x20 */
    f32 u24;        /* 0x24 */
    f32 u28;        /* 0x28 */
    f32 u2C;        /* 0x2C */
    f32 u30;        /* 0x30 */
    f32 u34;        /* 0x34 */
    f32 u38;        /* 0x38 */
    f32 u3C;        /* 0x3C */
    f32 u40[4];     /* 0x40 */
    void *owner;    /* 0x50 the type 0x12C object */
    f32 height;     /* 0x54 */
    u8 u58;         /* 0x58 */
    u8 pad59[3];
} Glow175CTail;     /* 0x5C, copied to the glow +0x110 */

typedef struct {
    u8 u0;          /* 0x00 2 */
    s8 u1;          /* 0x01 -1 */
    s16 u2;         /* 0x02 0x12C */
    u8 u4;          /* 0x04 */
    u8 pad5[3];
} Smoke175C;

typedef struct {
    s32 w[3];
} Smoke175C2;

typedef struct {
    f32 v[3];
} Vec175C;

// object_glow_attach: spawns a type 0x12C object (func_15149130) linked to obj (record at +0x28: obj, room, glow,
// smoke), a glow (func_1513D2F0 with the D_800A4AA0 model, variant 1 or 3 at random; its +0x110 tail holds obj, the
// light constants, the new object and the mid height of obj +0x14C / +0x150) and a func_151602C0 effect, storing both
// at +0x30 / +0x34 of the new object.
void func_1501175C(u8 *obj, u8 arg1, s32 arg2) {
    Link175C link;
    Glow175CTail tail;
    Glow175C g;
    Smoke175C h;
    Smoke175C2 h2;
    u8 *o;
    Link175C *l;
    void *e;
    s32 v;

    link.obj = obj;
    link.room = obj[0x3B];
    link.glow = NULL;
    link.smoke = NULL;
    o = (u8 *) func_15149130(0x12C, -1, 0x54, -1, 0, 0x34, (struct37 *) 0x10, arg1, arg2);
    if (o == NULL) {
        return;
    }
    l = (Link175C *) (o + 0x28);
    memcpy(l, &link, 0x10);
    tail.u58 = 0;
    tail.obj = obj;
    tail.height = (*(f32 *) (obj + 0x14C) + *(f32 *) (obj + 0x150)) * 0.5f;
    tail.u8_ = 15.0452719f;   /* D_800968B8 */
    tail.uC = 0.396174014f;   /* D_800968C4 */
    tail.u10 = 5.86765575f;   /* D_800968BC */
    tail.u14 = 0.104256302f;  /* D_800968C8 */
    tail.u18 = 12.1114445f;   /* D_800968C0 */
    tail.room = obj[0x3B];
    tail.u1C = 0.344045877f;  /* D_800968D0 */
    tail.u20 = 0.519737124f;  /* D_800968CC */
    tail.u24 = 0.0f;
    tail.u28 = 0.0f;
    tail.u38 = 0.0f;
    tail.u3C = 0.0f;
    tail.u40[2] = 1.0f;
    tail.u40[0] = 1.0f;
    tail.u40[3] = 1.0f;
    tail.u40[1] = 1.0f;
    tail.owner = o;
    tail.u2C = 160.0f;
    tail.u30 = 95.0f;
    tail.u34 = 207.5f;        /* D_800968D4 */
    g.u14 = 0.0f;
    g.u18 = 0.0f;
    g.u0 = 0x5F;
    g.u1 = 9;
    g.u2 = 0x2203;
    g.u4 = 0x12C;
    g.u8_ = 0;
    g.uC = 0;
    g.rgba[0] = 0xFF;
    g.rgba[1] = 0xFF;
    g.rgba[2] = 0xFF;
    g.rgba[3] = 0xFF;
    *(Vec175C *) g.pos = *(Vec175C *) D_800A5860;
    *(Vec175C *) g.pos2 = *(Vec175C *) D_800A5860;
    g.scale[0] = 1.0f;
    g.scale[1] = 1.0f;
    g.scale[2] = 1.0f;
    g.u40 = 7.375f;
    g.u44 = 0;
    g.u45 = 0xFF;
    g.u46 = 0;
    g.u47 = 7;
    g.u48 = 0;
    v = (func_150ADA20() & 1) ? 2 : 0;
    e = func_1513D2F0(&g, (s32) &D_800A4AA0, 0, 0x25, 0, 0x1D, v + 1, 0, 0, 0x5C, arg1, arg2);
    l->glow = e;
    if (e != NULL) {
        memcpy((u8 *) e + 0x110, &tail, 0x5C);
    }
    h.u0 = 2;
    h.u1 = -1;
    h.u2 = 0x12C;
    h.u4 = 0;
    h2.w[0] = 0;
    h2.w[1] = 0;
    h2.w[2] = 0;
    l->smoke = func_151602C0((Header *) &h, (Header2 *) &h2, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, arg1, arg2);
}
