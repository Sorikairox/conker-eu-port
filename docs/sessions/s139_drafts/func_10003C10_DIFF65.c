extern s32 D_8002AF20;
extern f32 D_8002C3F0;
extern f32 D_8002C3F4;
extern f32 D_eu_8002C3F8;

void func_10003C10(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 t;
    u32 u;
    s32 hh;

    if (D_8002AC5C == 0) {
        y = arg1 + 0x3F;
        hh = D_8002C3F0 * arg3;
        h = hh;
        x = arg0 + 0x8C;
        w = D_8002C3F4 * arg2;
        if (arg0 + w + 0x8C >= 0x31B) {
            w = 0x31A - x;
        }
        if (y + hh >= 0x272) {
            h = 0x271 - y;
        }
        *(s32 *)((u8 *)&D_8002AF20 + 0x1C) = (x << 0x10) | (x + w);
        t = (y << 0x10) | (y + h);
        *(u32 *)((u8 *)&D_8002AF20 + 0x20) = 512.0f - (f32)(w - 0x249);
        *(s32 *)((u8 *)&D_8002AF20 + 0x30) = t;
        *(s32 *)((u8 *)&D_8002AF20 + 0x44) = t;
        u = 1024.0f - (f32)(h - 0x1AB) * D_eu_8002C3F8;
        *(u32 *)((u8 *)&D_8002AF20 + 0x2C) = u;
        *(u32 *)((u8 *)&D_8002AF20 + 0x40) = u;
    }
}
