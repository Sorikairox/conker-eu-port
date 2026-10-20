s32 memcpy(s32, void *, s32);
struct S9 {u8 a[9];};
extern struct S9 D_800A0D60;

void func_150D2C9C(s32 arg0, s32 *arg1, u8 arg2, s32 arg3) {
    f32 sp48[24];
    struct S9 sp38;
    struct260 *temp_v0;

    *(s32 *)&sp48[0] = arg0;
    sp48[1] = 2.0f * func_150ADA68() * 3.1415927f;
    sp48[2] = (func_150ADA68() * 0.4f) + 0.3f;
    sp48[3] = 1.0f / sp48[2];
    sp48[4] = (func_150ADA68() * 0.13000001f) + 0.3f;
    if (func_150ADA20() & 1) {
        sp48[4] = -sp48[4];
    }
    sp48[5] = 0.0f;
    sp48[6] = 0.0f;
    memcpy(&sp48[7], arg1, 0x40);
    sp38 = D_800A0D60;
    temp_v0 = (struct260 *)((((func_150ADA20() % 3U) & 0xFF) * 3) + (u8 *)&sp38);
    ((u8 *)sp48)[0x5C] = (*(u8 *)((u8 *)(u8 *)temp_v0 + 0));
    ((u8 *)sp48)[0x5D] = (*(u8 *)((u8 *)(u8 *)temp_v0 + 1));
    ((u8 *)sp48)[0x5E] = (*(u8 *)((u8 *)(u8 *)temp_v0 + 2));
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 101U) + 0x64), -1, 0x32, -1, 1U, 0U, (struct37 *)0x60, (u8) (s32) arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x28, &sp48, 0x60);
    }
}
