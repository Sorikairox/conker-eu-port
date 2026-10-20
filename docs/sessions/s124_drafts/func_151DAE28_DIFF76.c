s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_151DAE28(u8 *arg0, s16 arg1) {
    u8 *sp4C;
    u8 *sp48;
    f32 s;
    f32 temp_f12;
    f32 temp_f2;
    u8 sp37;
    u8 *src;
    u8 **slot;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp4C, &sp37);
    sp48 = sp4C;
    if (sp4C != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f2 = D_800DD608[arg1] * (*(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x4C));
    temp_f12 = D_800DD618[arg1] * (*(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x4C));
    *(s16 *)(sp4C + 6) = 0;
    *(s16 *)(sp4C + 0x16) = 0;
    *(s16 *)(sp4C + 0x26) = 0;
    *(s16 *)(sp4C + 0x36) = 0;
    *(s16 *)(sp4C + 0) = *(s16 *)(sp4C + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp4C + 2) = *(s16 *)(sp4C + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp4C + 4) = *(s16 *)(sp4C + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp4C + 0x10) = *(s16 *)(sp4C + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp4C + 0x22) = *(s16 *)(sp4C + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)) * (*(f32 *)((u8 *)arg0 + 0x50)));
    *(s16 *)(sp4C + 0x14) = *(s16 *)(sp4C + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp48;
}
