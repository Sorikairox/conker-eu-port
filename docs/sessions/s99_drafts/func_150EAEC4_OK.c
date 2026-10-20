typedef struct {
    f32 rot[3];
    u8 padC[4];
    s16 u10;
    s16 u12;
    s16 u14;
    u8 pad16[0x3C - 0x16];
    s32 u3C;
    u8 pad40[0x5A - 0x40];
    s16 u5A;
    s16 u5C;
    s16 u5E;
    f32 vel[3];
    u8 pad6C[2];
    s8 u6E;
    u8 pad6F[0x73 - 0x6F];
    u8 u73;
    u8 pad74[0x7C - 0x74];
    s32 u7C;
    u8 pad80[0x8A - 0x80];
    u8 u8A;
} S_EAEC4;
void func_150EAEC4(S_EAEC4 *arg0) {
    f32 f;
    s32 v;

    if ((arg0->u73 & 3) == 3) {
        f = D_800BE9E4;
        arg0->rot[0] += arg0->vel[0] * f;
        if (arg0->rot[0] < 0.0f) {
            arg0->rot[0] += 360.0f;
        } else if (arg0->rot[0] >= 360.0f) {
            arg0->rot[0] -= 360.0f;
        }
        arg0->rot[1] += arg0->vel[1] * f;
        if (arg0->rot[1] < 0.0f) {
            arg0->rot[1] += 360.0f;
        } else if (arg0->rot[1] >= 360.0f) {
            arg0->rot[1] -= 360.0f;
        }
        arg0->rot[2] += arg0->vel[2] * f;
        if (arg0->rot[2] < 0.0f) {
            arg0->rot[2] += 360.0f;
        } else if (arg0->rot[2] >= 360.0f) {
            arg0->rot[2] -= 360.0f;
        }
        arg0->u5C -= arg0->u3C * D_800BE9E4;
        arg0->u10 += arg0->u5A * D_800BE9E4;
        arg0->u7C += arg0->u5C * D_800BE9E4;
        arg0->u12 = arg0->u7C >> 3;
        arg0->u14 += arg0->u5E * D_800BE9E4;
        v = arg0->u8A;
        v -= D_800BE9E4 * 4;
        if (v > 0) {
            arg0->u8A = v;
            return;
        }
        arg0->u6E = 1;
    }
}
