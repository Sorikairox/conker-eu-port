s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_151A6900(u8 *arg0, s16 arg1) {
    u8 *sp4C;
    u8 *sp48;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    u8 sp37;
    s32 temp_f10;
    s32 temp_f4;
    u8 *temp_t0_2;
    u8 *temp_t2;
    u8 *temp_t5;

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
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2C));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x114));
    temp_f12 = D_800DD608[arg1] * temp_f2;
    temp_f14 = D_800DD618[arg1] * temp_f2;
    temp_f4 = (s32) temp_f0;
    temp_f10 = (s32) (temp_f0 + (*(f32 *)((u8 *)arg0 + 0x11C)));
    (*(s16 *)((u8 *)sp4C + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f14);
    (*(s16 *)((u8 *)sp4C + 2)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    (*(s16 *)((u8 *)sp4C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f12);
    (*(s16 *)((u8 *)sp4C + 8)) = (s16) temp_f4;
    (*(s16 *)((u8 *)sp4C + 0xA)) = 0x7C0;
    (*(u8 *)((u8 *)sp4C + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x126));
    (*(s16 *)((u8 *)sp4C + 6)) = 0;
    temp_t2 = sp4C + 0x10;
    sp4C = temp_t2;
    temp_t0_2 = temp_t2 + 0x10;
    (*(s16 *)((u8 *)temp_t2 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f14);
    (*(s16 *)((u8 *)temp_t2 + 2)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    (*(s16 *)((u8 *)temp_t2 + 0xA)) = 0;
    (*(s16 *)((u8 *)temp_t2 + 8)) = (s16) temp_f4;
    (*(s16 *)((u8 *)temp_t2 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f12);
    (*(s16 *)((u8 *)temp_t2 + 6)) = 0;
    (*(u8 *)((u8 *)temp_t2 + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x126));
    sp4C = temp_t0_2;
    (*(s16 *)((u8 *)temp_t0_2 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f14);
    (*(s16 *)((u8 *)sp4C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)));
    (*(s16 *)((u8 *)sp4C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f12);
    (*(s16 *)((u8 *)sp4C + 8)) = (s16) temp_f10;
    (*(s16 *)((u8 *)sp4C + 0xA)) = 0;
    (*(u8 *)((u8 *)sp4C + 0xF)) = 0U;
    (*(s16 *)((u8 *)temp_t0_2 + 6)) = 0;
    temp_t5 = sp4C + 0x10;
    sp4C = temp_t5;
    (*(s16 *)((u8 *)temp_t5 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f14);
    (*(s16 *)((u8 *)temp_t5 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)));
    (*(s16 *)((u8 *)temp_t5 + 0xA)) = 0x7C0;
    (*(s8 *)((u8 *)temp_t5 + 0xF)) = 0;
    (*(s16 *)((u8 *)temp_t5 + 6)) = 0;
    (*(s16 *)((u8 *)temp_t5 + 8)) = (s16) temp_f10;
    (*(s16 *)((u8 *)temp_t5 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f12);
    return sp48;
}
