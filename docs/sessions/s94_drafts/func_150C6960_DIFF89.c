typedef struct { f32 x, y, z; } V3_C6960;
extern V3_C6960 D_80088B70;
extern u8 D_800AB7F4[];
extern f32 D_800A080C;
extern f32 D_800A0810;
u8 func_151D8E20(void);
s32 func_15045AF0(f32 *, s32, f32, void *);
s32 memcpy(void *, void *, s32);
s32 func_150C6960(u8 *arg0) {
    struct210 *ret;
    f32 pos[3];
    u8 *o;
    V3_C6960 tmp;
    f32 v[3];
    u8 *rgb;
    s32 padA4;
    s32 padA0;
    struct {
        s32 u84;
        s16 u88;
        s8 u8A;
        s32 u8C;
        s32 u90;
        u8 u94;
        u8 u95;
        u8 u96;
        u8 u97;
        u8 u98;
        u8 u99;
        s8 u9A;
        s8 u9B;
        s32 u9C;
    } sp;
    struct {
        u8 *u64;
        s8 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        s16 u7C;
        f32 u80;
    } blk;
    f32 size;
    u8 c;
    s32 pad58;
    s32 r54;
    s32 r50;

    ret = NULL;
    o = *(u8 **)(arg0 + 0x18);
    if (*(u8 **)(o + 0x1D4) != NULL) {
        tmp = D_80088B70;
        func_15143134(&tmp, pos, *(u8 **)(o + 0x1D4));
    } else {
        pos[0] = *(f32 *)(o + 0x14);
        pos[1] = *(f32 *)(o + 0x18);
        pos[2] = *(f32 *)(o + 0x1C);
    }
    v[1] = pos[1] + 200.0f;
    v[0] = pos[0];
    v[2] = pos[2];
    if (func_15045AF0(v, 0, pos[1] - 200.0f, arg0 + 0x34) != 0) {
        c = func_151D8E20();
        v[1] = *(f32 *)(arg0 + 0x34);
        size = func_150ADA68() * 50.0f + 100.0f;
        blk.u68 = 1;
        blk.u7A = 10;
        blk.u7C = 10;
        rgb = &D_800AB7F4[c * 3];
        sp.u8A = 0x38;
        sp.u88 = 300;
        blk.u6C = D_800A080C;
        blk.u70 = 32768.0f;
        sp.u90 = blk.u70 * 0.5f + blk.u6C;
        sp.u84 = 0x20300;
        sp.u94 = 0x96;
        blk.u64 = arg0;
        blk.u78 = 0;
        sp.u8C = 0;
        sp.u95 = 0xFF;
        sp.u99 = 0xFF;
        sp.u9C = 0x440001;
        sp.u9A = 0;
        sp.u9B = 6;
        blk.u80 = D_800A0810;
        blk.u74 = 0.0f;
        sp.u96 = rgb[0];
        sp.u97 = rgb[1];
        sp.u98 = rgb[2];
        r50 = func_150ADA20();
        r54 = func_150ADA20();
        ret = func_1513C73C((s32)&sp, 8, 2, (s32)(arg0 + 0x38), v[0], v[1], v[2], size, size, (u8)(r50 & 0xFF), (u8)(((func_150ADA20() & 1) * 2) + (r54 & 1)), 0x20, arg0[0xC], arg0[1]);
        if (ret != NULL) {
            memcpy((u8 *)ret + 0xB0, &blk, 0x20);
        }
    }
    return (s32)ret;
}
