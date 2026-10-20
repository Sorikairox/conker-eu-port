void func_15143794(s16, s16, f32, void *);
s32 func_151DA6F8(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    s32 spA8[3];

    n = *(s16 *)((u8 *)arg1 + 0x24) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
    while (n != 0) {
        func_15143794(arg0->unk0 + (func_150ADA20() % (u32)(arg0->unk2 + 1)),
            arg0->unk4 + (func_150ADA20() % (u32)(arg0->unk6 + 1)),
            *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * func_150ADA68(), spA8);
        func_151DA6F8(arg1, spA8,
            *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68(),
            *(s16 *)((u8 *)arg1 + 0x2C) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
            *(s16 *)((u8 *)arg1 + 0x30) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
            *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * func_150ADA68(),
            *(s16 *)((u8 *)arg1 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
            func_150ADA68() < *(f32 *)((u8 *)arg1 + 0x38),
            1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
            *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
        n--;
    }
}
