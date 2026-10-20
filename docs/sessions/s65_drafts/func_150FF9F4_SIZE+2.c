typedef struct { s32 x, y, z; } V3i;
void func_150FF9F4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {

    struct {
        s8 u84;
        s8 u85;
        s16 u86;
        s16 u88;
        u8 pad8A[0x2];
        s32 u8C;
        s32 u90;
        u8 u94;
        u8 u95;
        u8 u96;
        u8 u97;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x8];
        s32 uAC;
        u8 padB0[0x8];
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s8 uC8;
        u8 uC9;
        s8 uCA;
        s8 uCB;
        s32 uCC;
        u8 uD0;
    } sp;
    s32 temp_t5;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_t4;

    sp.u84 = 0x5F;
    sp.u85 = 5;
    sp.u86 = 0x2203;
    sp.u8C = 0;
    sp.u90 = 0;
    sp.u94 = 0xFF;
    sp.u95 = 0xFF;
    sp.u96 = 0xFF;
    sp.u97 = 0xFF;
    *(V3i *) &sp.uA0 = *(V3i *) arg0;
    sp.uB8 = 0.0f;
    sp.uBC = 0.0f;
    sp.uC0 = 0.0f;
    sp.uC4 = 0x40CC0009;
    sp.uC9 = 0xFF;
    sp.uCA = 0;
    sp.uCB = 7;
    sp.uD0 = 0xFF;
    sp.uCC = 0;
    sp.u88 = (func_150ADA20() & 3) + 3;
    var_s0 = 0;
    do {
        sp.u98 = (func_150ADA68() * 11.1f) + 5.0f;
        temp_t4 = arg1 + (var_s0 * 0xC);
        sp.u9C = (func_150ADA68() * 0.9990001f) + 2.483f;
        *(V3i *) &sp.uAC = *(V3i *) temp_t4;
        sp.uC8 = (func_150ADA20() % 156U) + 0x64;
        if (func_150ADA20() & 1) {
            var_v0 = 2;
        } else {
            var_v0 = 0;
        }
        func_1513D2F0(&sp.u84, (s32) "", 0U, 0U, 0U, 0x1BU, (u8) (var_v0 + 1), 0, 0, 0, (u8) (arg2 & 0xFF), arg3);
        temp_t5 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t5;
    } while (temp_t5 < 6);
}
