u8 func_151D8E20(void);
extern u8 D_800AB7F4[][3];
extern f32 D_800A93C0;
extern f32 D_800A93C4;
extern f32 D_800A93C8;
typedef struct {
    s32 u0;
    s16 u4;
    u8 u6;
    s32 u8;
    s32 uC;
    u8 u10;
    u8 u11;
    u8 u12[3];
    u8 u15;
    u8 u16;
    u8 u17;
    s32 u18;
    s32 u1C;
    u8 u20;
    s16 u22;
    s16 u24;
} Blk28_B3A8;
typedef struct {
    u8 *p;
    u8 u4;
    f32 u8;
    f32 uC;
    f32 u10;
    s16 u14;
    s16 u16;
    s16 u18;
    f32 u1C;
} Tmp20_B3A8;

void func_151AB3A8(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    Blk28_B3A8 blk;
    Tmp20_B3A8 tmp;
    f32 size;
    u8 idx;
    s32 r1;
    s32 r0;
    struct210 *ret;

    if (*(s32 *)(arg0 + 0x70) != 0) {
        (*(u8 **)(arg0 + 0x70) + 0xB0)[4] = 1;
        return;
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A93C0 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        idx = func_151D8E20();
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        size = (func_150ADA68() * 30.0f) + 50.0f;
        tmp.p = arg0;
        tmp.u4 = 1;
        tmp.u8 = D_800A93C4;
        tmp.uC = 32768.0f;
        tmp.u10 = 0.0f;
        tmp.u14 = 0;
        tmp.u16 = 0xA;
        tmp.u18 = 0xA;
        tmp.u1C = D_800A93C8;
        blk.u0 = 0x60300;
        blk.u4 = 0x12C;
        blk.u6 = 0x38;
        blk.u8 = 0;
        blk.uC = (tmp.uC * 0.5f) + tmp.u8;
        blk.u10 = 0x96;
        blk.u11 = 0xFF;
        blk.u12[0] = D_800AB7F4[idx][0];
        blk.u12[1] = D_800AB7F4[idx][1];
        blk.u12[2] = D_800AB7F4[idx][2];
        blk.u15 = 0xFF;
        blk.u16 = 0;
        blk.u17 = 6;
        blk.u18 = 0x440001;
        r0 = func_150ADA20();
        r1 = func_150ADA20();
        ret = func_1513C73C((s32)&blk, 7, 1, (s32)(arg0 + 0x38), pos.unk0, pos.unk4, pos.unk8, size, size, r0 & 0xFF, ((func_150ADA20() & 1) * 2) + (r1 & 1), 0x20, 0xFF, 1);
        *(struct210 **)(arg0 + 0x58 + 0x18) = ret;
        if (ret != NULL) {
            memcpy((u8 *)ret + 0xB0, &tmp, 0x20);
        }
    }
}
