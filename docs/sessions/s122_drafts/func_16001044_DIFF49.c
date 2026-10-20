typedef struct { s32 v[10]; } Pow10;
extern Pow10 D_16003B50;
extern u8 D_160047E4[];
extern u8 D_160047E8[];
extern u8 D_160047F0[];
extern u8 D_160047F4[];

void func_16001044(s32 arg0, s32 arg1, s32 arg2) {
    union { s32 i; f32 f; } u;
    u8 buf[0x30];
    Pow10 pw;
    s32 fb;
    s32 i;
    u8 c;
    s32 started;
    s32 q;
    s32 e;

    pw = D_16003B50;
    if (arg0 >= (D_160038A0 << 5) && arg0 < 0x341) {
        fb = func_1600160C(arg0);
        switch (arg1) {
        case 0:
            fb += 0x70;
            for (i = 0; i < 8; i++) {
                c = arg2 & 0xF;
                if (c >= 10) {
                    c += 7;
                }
                func_160014F0(fb, (u8)(c + '0'));
                arg2 >>= 4;
                fb -= 0x10;
            }
            break;
        case 1:
            if (arg2 < 0) {
                fb = func_160014F0(fb, '-');
                arg2 = -arg2;
            }
            started = 0;
            for (i = 9; i >= 0; i--) {
                q = arg2 / pw.v[i];
                arg2 = arg2 % pw.v[i];
                if (q > 0 || started || i == 0) {
                    fb = func_160014F0(fb, (u8)(q + '0'));
                    started = 1;
                }
            }
            break;
        case 2:
            e = (arg2 & 0x7F800000) >> 23;
            if ((e <= 0 || e >= 0xFF) && (e != 0 || (arg2 << 9) != 0)) {
                func_160012B0(arg0, D_160047E4);
                return;
            }
            u.i = arg2;
            func_16001B34(buf, D_160047E8, D_160047F0, D_160047F4, u.f);
            func_160012B0(arg0, buf);
            break;
        }
    }
}
