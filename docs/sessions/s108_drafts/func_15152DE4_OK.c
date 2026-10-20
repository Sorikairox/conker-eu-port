void func_15143794(s16, s16, f32, void *);
void func_150CD3C0(void *, u8, u8);
extern void (*D_8008B000[])(u8 *);
typedef struct { f32 v[3]; } V3_2de4;
typedef struct {
    V3_2de4 v;
    f32 p[3];
    f32 a;
    f32 b;
    u8 c[4];
    s32 n;
    f32 x;
    f32 y;
    f32 z;
} S_2de4;

void func_15152DE4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused slot above the struct (frame size)
    S_2de4 sp;
    s32 n;
    s8 i;

    n = func_150ADA20();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    sp.v = *(V3_2de4 *)(arg0 + 8);
    sp.a = *(f32 *)(arg0 + 0x24);
    sp.z = *(f32 *)(arg0 + 0x48);
    while (n != 0) {
        func_15143794(*(s16 *)(arg0 + 0x14) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * func_150ADA68(), sp.p);
        sp.b = *(f32 *)(arg0 + 0x28) + *(f32 *)(arg0 + 0x2C) * func_150ADA68();
        sp.n = *(s16 *)(arg0 + 0x32) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.x = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x40) * func_150ADA68();
        sp.y = *(f32 *)(arg0 + 0x3C) + *(f32 *)(arg0 + 0x44) * func_150ADA68();
        i = *(s8 *)(arg0 + 0x30);
        if (i != 0xFFFFFFFF) { // unsigned compare: "!= -1" gives beq v0,fp (permuter found -1U)
            D_8008B000[i](sp.c);
        } else {
            sp.c[0] = 0xFF;
            sp.c[1] = 0xFF;
            sp.c[2] = 0xFF;
            sp.c[3] = 0xFF;
        }
        func_150CD3C0(&sp, arg1, (u8)arg2);
        n--;
    }
}
