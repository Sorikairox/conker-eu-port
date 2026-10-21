typedef struct {
    /* 0x00 */ f32 y;
    /* 0x04 */ f32 u4[5];
    /* 0x18 */ f32 u18;
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 u1D;
    /* 0x1E */ u8 pad1E[2];
} Gnd6404;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 z;
} Obj6404;

void func_15143874(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3);

void func_15136404(Obj6404 *arg0, f32 arg1, u8 arg2, s32 arg3) {
    struct17 v;
    struct17 pos;
    Gnd6404 g;
    f32 area;
    f32 n;

    if (arg0 != NULL) {
        area = 3.14159274f * arg1 * arg1;
        n = (((func_150ADA68() * 305.0f) + 108.0f) * 9.99999997e-07f) * area;
        func_1504715C(&g, arg0);
        while (n > 1.0f) {
            func_15143874((u8)func_150ADA20(), func_150ADA68() * arg1, &v.unk0, &v.unk8);
            v.unk0 += arg0->x;
            v.unk8 += arg0->z;
            v.unk4 = arg0->y + 500.0f;
            if (func_15046F70(&v.unk0, 0, arg0->y - 5000.0f, (s32)&g) != 0 && g.u1D != 3) {
                pos.unk0 = v.unk0;
                pos.unk4 = g.y;
                pos.unk8 = v.unk8;
                func_151D9B8C(0, (func_150ADA68() * 20.0f) + 10.0f, (func_150ADA20() % 101U) + 100, (s32)&g.u4[0], &pos,
                              (func_150ADA20() % 201U) + 400, 1, 1, 0, arg2, arg3);
            }
            n -= 1.0f;
        }
    }
}
