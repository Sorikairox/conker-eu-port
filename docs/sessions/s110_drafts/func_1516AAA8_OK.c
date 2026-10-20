s32 func_151722BC(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_1516AAA8(u8 *arg0) {
    s32 pad; // fakematch: frame slot
    u32 sp48;
    s32 sp44;

    if ((*(s16 *)((u8 *)arg0 + 0x14)) >= 0x300) {
        sp48 = func_150ADA20() % 3U;
        sp44 = (s32) (*(u8 *)((u8 *)arg0 + 0x25));
        func_151722BC((f32) (*(s16 *)((u8 *)arg0 + 0x18)), (f32) ((*(s16 *)((u8 *)arg0 + 0x1A)) - 0xA), (f32) (*(s16 *)((u8 *)arg0 + 0x1C)), 0x64, 0, sp48 + 0x20, (f32) (func_150ADA20() % 360U), 0, ((s32) (sp44 * 0x19) / 255) + 0x19, 0, 0x100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    }
}
