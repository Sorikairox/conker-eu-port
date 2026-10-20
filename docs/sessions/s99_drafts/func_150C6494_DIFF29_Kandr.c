typedef struct {
    s32 u40;
    s32 u44;
    u8 u48;
    s32 u4C;
    s8 u50;
    f32 u54;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    s16 u68;
    u8 u6A;
    u8 u6B;
    u8 u6C;
    u8 u6D;
} sp_C6494;
typedef struct {
    u8 *a;
    s8 b;
    f32 c;
} blk_C6494;
u8 *func_1513418C(void *, s32, u8, s32);
s32 func_15045AF0(f32 *, s32, f32, void *);
s32 memcpy(void *, void *, s32);
s32 func_150C6494(s32 arg0_, u8 *arg1) {
#define arg0 ((u8 *)arg0_)
    sp_C6494 sp;
    blk_C6494 blk;
    u8 *obj;
    f32 v[3];
    u8 **pa = &arg1; // fakematch: arg1 reloaded from its home

    blk.a = *pa;
    blk.b = 1;
    v[0] = *(f32 *)(arg0 + 0x14);
    v[1] = *(f32 *)(arg0 + 0x18) + 5000.0f;
    v[2] = *(f32 *)(arg0 + 0x1C);
    if (func_15045AF0(v, 0, *(f32 *)(arg0 + 0x18) - 100.0f, *pa + 0x34) != 0) {
        blk.c = *(f32 *)(*pa + 0x34);
    } else {
        blk.c = *(f32 *)(arg0 + 0x18) + 5000.0f;
    }
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u48 = arg0[0x3B];
    sp.u4C = arg0_;
    sp.u50 = 0;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 0.0f;
    sp.u60 = 25.0f;
    sp.u64 = 0.132485f;
    sp.u68 = 300;
    sp.u6A = 10;
    sp.u6B = 4;
    sp.u6C = 1;
    sp.u6D = 2;
    obj = func_1513418C(&sp, 0xC, 0xFF, 0);
    if (obj != NULL) {
        memcpy(obj + 0x58, &blk, 0xC);
    }
    return (s32)obj;
}
#undef arg0
