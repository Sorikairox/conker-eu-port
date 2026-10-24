// lightning_flash_update: weather record handler (table entry at ROM 0x230744; returns 1 = keep). Drives the sky flash
// of the area object +0x14 (skipped when its +0x9 is 1): its +0x2F gets the flash level +0x18, which decays by the
// factor +0x1C once per tick (D_800BE9E4). While a burst is running (+0x2C flashes left) +0x38 counts down by
// D_800BE9A4; at zero a new flash of level rand * +0x48 + +0x44 starts, the next one is due after rand * +0x40 + +0x3C,
// and a flash counter is used up (func_1000E770 is called with two NULL pointers; the asm also computes a thunder
// delay from func_151EFDD0 that EU's two-pointer func_1000E770 never reads). Between bursts +0x20 counts down; at zero
// a burst of rand % (+0x34 + 1) + +0x30 flashes is queued and the next pause is rand * +0x28 + +0x24.
s32 func_1000E770(s32 *arg0, s32 *arg1);
f32 func_150ADA68(void);
int func_151EFDD0(void);

s32 func_151630F4(u8 *rec) {
    u8 *obj = *(u8 **) (rec + 0x14);
    f32 *level = (f32 *) (rec + 0x18);
    u32 n;

    if (obj[9] == 1) {
        return 1;
    }
    obj[0x2F] = (u32) *level;
    for (n = D_800BE9E4; n != 0; n--) {
        *level -= *level * *(f32 *) (rec + 0x1C);
    }
    if (*(s32 *) (rec + 0x2C) > 0) {
        *(f32 *) (rec + 0x38) -= D_800BE9A4;
        if (*(f32 *) (rec + 0x38) < 0.0f) {
            *level = func_150ADA68() * *(f32 *) (rec + 0x48) + *(f32 *) (rec + 0x44);
            *(f32 *) (rec + 0x38) = func_150ADA68() * *(f32 *) (rec + 0x40) + *(f32 *) (rec + 0x3C);
            func_151EFDD0();
            func_1000E770(NULL, NULL);
            *(s32 *) (rec + 0x2C) -= 1;
        }
    } else {
        *(f32 *) (rec + 0x20) -= D_800BE9A4;
        if (*(f32 *) (rec + 0x20) < 0.0f) {
            *(s32 *) (rec + 0x2C) = (u32) func_150ADA20() % (u32) (*(s32 *) (rec + 0x34) + 1) + *(s32 *) (rec + 0x30);
            *(f32 *) (rec + 0x38) = 0.0f;
            *(f32 *) (rec + 0x20) = func_150ADA68() * *(f32 *) (rec + 0x28) + *(f32 *) (rec + 0x24);
        }
    }
    return 1;
}
