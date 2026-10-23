s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern u8 D_800A5860[];
// object_glow_spawn: spawns effect 0x2B (func_151307F0, 0x14 extra bytes at +0xA8) at obj's position: size 250,
// the colour of D_800A5860, life 300, random flip flags 0x40 / 0x80; the extra bytes keep obj, its index (+0x3B)
// and three random angles 0..2pi.
void func_150F0BEC(u8 *obj) {
    struct {
        /* extra data copied to the effect +0xA8 (0x14 bytes) */
        u8 *obj;
        u8 index;
        u8 pad5[3];
        f32 angle[3];
        /* spawn block for func_151307F0 (0x70 bytes) */
        s32 u0;
        s32 u4;
        s16 u8_;
        s16 life;
        s32 uC;
        s32 u10;
        u8 u14[9];
        u8 type;
        s16 u1E;
        s16 u20;
        s16 u22;
        f32 u24;
        f32 size[2];
        f32 pos[3];
        s32 color1[3];
        s32 color2[3];
        f32 u54;
        s32 flags;
        s32 u5C;
        u8 u60[7];
        u8 pad67;
        s16 u68;
        u8 pad6A[2];
        f32 u6C;
    } sp;
    s32 flipX;
    s32 flipY;
    s32 p;
    f32 r;

    sp.u0 = 0x200005;
    sp.u4 = 0x70600;
    sp.u8_ = 0x4403;
    sp.life = 300;
    sp.uC = 0;
    sp.u10 = 0;
    sp.u14[0] = 0xFF;
    sp.u14[1] = 0xFF;
    sp.u14[2] = 0xFF;
    sp.u14[3] = 0xFF;
    sp.u14[4] = 0xFF;
    sp.u14[5] = 0xD9;
    sp.u14[6] = 0xA0;
    sp.u14[7] = 0xFF;
    sp.u14[8] = 0xFF;
    sp.type = 0x2B;
    sp.size[1] = 250.0f;
    sp.size[0] = 250.0f;
    sp.pos[0] = *(f32 *)(obj + 0x14);
    sp.pos[1] = *(f32 *)(obj + 0x18);
    sp.pos[2] = *(f32 *)(obj + 0x1C);
    sp.color1[0] = ((s32 *)D_800A5860)[0];
    sp.color1[1] = ((s32 *)D_800A5860)[1];
    sp.color1[2] = ((s32 *)D_800A5860)[2];
    sp.color2[0] = ((s32 *)D_800A5860)[0];
    sp.color2[1] = ((s32 *)D_800A5860)[1];
    sp.color2[2] = ((s32 *)D_800A5860)[2];
    sp.u1E = 1;
    sp.u20 = 0xFF;
    sp.u22 = 1;
    sp.u54 = 0.0f;
    sp.u24 = 1.0f;
    flipX = (func_150ADA20() & 1) ? 0x40 : 0;
    flipY = (func_150ADA20() & 1) ? 0x80 : 0;
    sp.flags = flipY | flipX | 0xC000 | 0x40000;
    sp.u60[0] = 6;
    sp.u60[1] = 6;
    sp.u60[2] = 0x25;
    sp.u60[3] = 0xFF;
    sp.u60[4] = 0xFF;
    sp.u60[5] = 0xA;
    sp.u5C = 0;
    sp.u60[6] = 0xFF;
    sp.u68 = 0;
    sp.u6C = 10000.0f;
    sp.obj = obj;
    sp.index = obj[0x3B];
    r = func_150ADA68();
    sp.angle[0] = (r + r) * 3.1415927f;
    r = func_150ADA68();
    sp.angle[1] = (r + r) * 3.1415927f;
    r = func_150ADA68();
    sp.angle[2] = (r + r) * 3.1415927f;
    p = func_151307F0((s32)&sp.u0, 1, 0, 0x14, 0xFF, 1);
    if (p != 0) {
        memcpy((u8 *)p + 0xA8, &sp.obj, 0x14);
    }
}
