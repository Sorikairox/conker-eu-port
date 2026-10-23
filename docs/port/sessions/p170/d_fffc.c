void func_1503F6F4(Mtx *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
void func_15151FA8(u8 *, u8, s32);
void func_1515128C(u8 *, u8, s32);
void func_1504715C(void *, u8 *);
void func_151A9DE4(f32 *, f32, f32, void *, s32, u8, s32, u8, s32);
extern f32 D_800AB2CC[7][3]; /* spark offsets in the model's space */
extern s32 D_800AB320[7];    /* spark kinds 0x6F..0x75 (the asm copies it to the stack: a local initializer) */

/* func_15132FBC spark block */
typedef struct {
    f32 scale[2];     /* +00 */
    f32 size[2];      /* +08 */
    f32 pos[3];       /* +10 */
    f32 axis[3];      /* +1C */
    f32 offset[3];    /* +28: func_15143134 output */
    f32 dir[3];       /* +34: func_15143794 output */
    f32 u40;
    f32 u44;
    f32 u48;
    f32 u4C;
    s32 u50;
    s16 life;         /* +54 */
    s16 kind;         /* +56 */
    u8 u58;
    s32 u5C;
    u8 u60[8];
    u8 u68;
    u8 pad69;
    u8 u6A;
    u8 *owner;        /* +6C */
    u8 u70;
    s16 u72;
    s16 u74;
} SparkBlockFFFC;

/* func_15151FA8 flash block */
typedef struct {
    f32 pos[3];       /* +00 */
    f32 f0C[6];
    s16 s24[10];
    u8 b38[3];
    s32 w3C[6];
    u8 b54[3];
    s32 w58[9];
    u8 b7C[2];
    u8 pad7E[2];
    s16 s80[2];
} FlashBlockFFFC;

/* func_1515128C ring block */
typedef struct {
    s32 u00;
    s32 u04;
    f32 pos[3];       /* +08 */
    s16 s14[4];
    f32 f1C[3];
    s16 s28[2];
    u8 u2C;
} RingBlockFFFC;

// object_shatter_effects: the break-up effects of an object with a model (+0x1D4; nothing without one): 7 sparks
// (func_15132FBC, kinds 0x6F..0x75) from the model's root point (func_1503F6F4) at the D_800AB2CC offsets
// (func_15143134) with random directions (func_15143794), sizes from +0x14C / +0x150; then a flash (func_15151FA8)
// and a ring (func_1515128C) 200 units above the object's position, and 7..10 debris pieces (func_151A9DE4, kind
// 2) dropped from there onto the floor up to 2000 units below.
void func_151CFFFC(u8 *obj, u8 arg1, s32 arg2) {
    SparkBlockFFFC s;
    FlashBlockFFFC f;
    RingBlockFFFC r;
    s32 ground[9];
    f32 pos[3];
    f32 rot[3];
    f32 root[3];
    f32 scl[3];
    u32 a;
    u32 b;
    u8 debrisKind;
    u8 i;

    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x18) + 200.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    if (*(Mtx **) (obj + 0x1D4) == NULL) {
        return;
    }
    func_1503F6F4(*(Mtx **) (obj + 0x1D4), &rot[0], &rot[1], &rot[2], &root[0], &root[1], &root[2], &scl[0], &scl[1],
                  &scl[2]);
    s.scale[0] = 1.0f;
    s.scale[1] = 0.649000049f;
    s.size[1] = s.size[0] = (*(f32 *) (obj + 0x14C) + *(f32 *) (obj + 0x150)) * 0.5f;
    s.pos[0] = root[0];
    s.pos[1] = root[1];
    s.pos[2] = root[2];
    s.axis[0] = 1.0f;
    s.axis[1] = 0.0f;
    s.axis[2] = 1.0f;
    s.u44 = 0.0f;
    s.u58 = 0;
    s.u5C = 0;
    s.u60[0] = 0xFF;
    s.u60[1] = 0xD;
    s.u60[2] = 0;
    s.u60[3] = 7;
    s.u60[4] = 0;
    s.u60[5] = 0;
    s.u60[6] = 0;
    s.u60[7] = 0;
    s.u68 = 2;
    s.u6A = 1;
    s.owner = obj;
    s.u70 = obj[0x3B];
    s.u72 = 0xC;
    s.u74 = 0x15;
    s.u50 = 0x39E9;
    for (i = 0; i < 7; i++) {
        s.kind = D_800AB320[i];
        func_15143134(D_800AB2CC[i], s.offset, *(void **) (obj + 0x1D4));
        a = func_150ADA20();
        b = func_150ADA20();
        func_15143794((u8) a, b % 25 - 64, func_150ADA68() * 11.45f + 16.93f, s.dir);
        s.u40 = func_150ADA68() * 19.752f + -9.876f;
        s.u48 = func_150ADA68() * 19.752f + -9.876f;
        s.u4C = func_150ADA68() * 0.518f + -1.539f;
        s.life = (u32) func_150ADA20() % 101 + 100;
        func_15132FBC(&s, 3, 0xFF, 0, arg1, arg2);
    }

    f.pos[0] = pos[0];
    f.pos[1] = pos[1];
    f.pos[2] = pos[2];
    f.f0C[0] = 8.0f;
    f.f0C[1] = 13.0f;
    f.f0C[2] = 0.8f;
    f.f0C[3] = 0.4f;
    f.f0C[4] = 23.0f;
    f.f0C[5] = 7.0f;
    f.s24[0] = 0xD;
    f.s24[1] = 6;
    f.s24[2] = 0;
    f.s24[3] = 0xFF;
    f.s24[4] = -0x40;
    f.s24[5] = 0x32;
    f.s24[6] = 3;
    f.s24[7] = 2;
    f.s24[8] = 0x28;
    f.s24[9] = 0x19;
    f.b38[0] = 9;
    f.b38[1] = 1;
    f.b38[2] = 0x48;
    f.w3C[0] = 1;
    f.w3C[1] = 0;
    f.w3C[2] = 0;
    f.w3C[3] = 0;
    f.w3C[4] = 0;
    f.w3C[5] = 0;
    f.b54[0] = 0;
    f.b54[1] = 0x96;
    f.b54[2] = 0x69;
    f.w58[0] = 3;
    f.w58[1] = 0xFF;
    f.w58[2] = 0;
    f.w58[3] = 0x220005;
    f.w58[4] = 0x1D0600;
    f.w58[5] = 3;
    f.w58[6] = 0x3B;
    f.w58[7] = 0x80;
    f.w58[8] = 0x20;
    f.b7C[0] = 0;
    f.b7C[1] = 7;
    f.s80[0] = 10;
    f.s80[1] = 0x19;
    func_15151FA8((u8 *) &f, arg1, arg2);

    r.u00 = 0xF;
    r.u04 = 6;
    r.pos[0] = pos[0];
    r.pos[1] = pos[1];
    r.pos[2] = pos[2];
    r.s14[0] = 0;
    r.s14[1] = 0xFF;
    r.s14[2] = -0x1D;
    r.s14[3] = 0x28;
    r.f1C[0] = 375.0f;
    r.f1C[1] = 20.0f;
    r.f1C[2] = 40.0f;
    r.s28[0] = 0x78;
    r.s28[1] = 0x78;
    r.u2C = 2;
    func_1515128C((u8 *) &r, arg1, arg2);

    func_1504715C(ground, obj);
    debrisKind = 2;
    func_151A9DE4(pos, pos[1] - 2000.0f, 200.0f, ground, (func_150ADA20() & 3) + 7, 0, (s32) &debrisKind, arg1, arg2);
}
