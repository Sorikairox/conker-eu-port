s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_1513F114(u8 *arg0, s16 arg1) {
    u8 *sp8C;
    u8 *ret;
    f32 h;
    f32 n;
    f32 sn;
    f32 cs;
    f32 ang;
    f32 dir;
    f32 sa;
    f32 ca;
    f32 x;
    f32 a;
    f32 b;
    f32 k;
    f32 t;
    u8 flag;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp8C, &flag);
    ret = sp8C;
    if (sp8C != NULL) {
        if (flag != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    n = -(*(f32 *)(arg0 + 0x50) * *(f32 *)(arg0 + 0x30));
    h = *(f32 *)(arg0 + 0x30) + n;
    sa = D_800DD608[arg1];
    ca = D_800DD618[arg1];
    dir = -1.0f;
    x = ((*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34)) * ca - sa * (*(f32 *)(arg0 + 0x48) - *(f32 *)(arg0 + 0x3C))) * D_800BEDC8;
    if (x < 0.0f) {
        dir = 1.0f;
        x = -x;
    }
    ang = sqrtf(x) * *(f32 *)(arg0 + 0x4C);
    if (ang > 1.5707964f) {
        ang = 1.5707964f;
    }
    ang *= dir;
    sn = sinf(ang);
    cs = cosf(ang);
    a = *(f32 *)(arg0 + 0x2C) * cs;
    b = *(f32 *)(arg0 + 0x2C) * sn;
    t = a - n * sn;
    *(s16 *)(sp8C + 0) = *(f32 *)(arg0 + 0x34) + t * ca;
    *(s16 *)(sp8C + 2) = *(f32 *)(arg0 + 0x38) + n * cs + b;
    *(s16 *)(sp8C + 4) = *(f32 *)(arg0 + 0x3C) - t * sa;
    *(s16 *)(sp8C + 6) = 0;
    t = -(a + n * sn);
    *(s16 *)(sp8C + 0x10) = *(f32 *)(arg0 + 0x34) + t * ca;
    *(s16 *)(sp8C + 0x12) = *(f32 *)(arg0 + 0x38) + n * cs - b;
    *(s16 *)(sp8C + 0x14) = *(f32 *)(arg0 + 0x3C) - t * sa;
    *(s16 *)(sp8C + 0x16) = 0;
    t = -(a + h * sn);
    *(s16 *)(sp8C + 0x20) = *(f32 *)(arg0 + 0x34) + t * ca;
    *(s16 *)(sp8C + 0x22) = *(f32 *)(arg0 + 0x38) + h * cs - b;
    *(s16 *)(sp8C + 0x24) = *(f32 *)(arg0 + 0x3C) - t * sa;
    *(s16 *)(sp8C + 0x26) = 0;
    t = a - h * sn;
    *(s16 *)(sp8C + 0x30) = *(f32 *)(arg0 + 0x34) + t * ca;
    *(s16 *)(sp8C + 0x32) = *(f32 *)(arg0 + 0x38) + h * cs + b;
    *(s16 *)(sp8C + 0x34) = *(f32 *)(arg0 + 0x3C) - t * sa;
    *(s16 *)(sp8C + 0x36) = 0;
    return ret;
}
