/* selftest case: calls whose delay slot is an FPU instruction (Unicorn 2.1.x jumped to 0 after the stub) */
s32 memcpy(s32, s32, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *impact_splash_ring_verts(u8 *arg0, s16 arg1) {
    u8 *temp_v0;
    s32 temp_t0;
    s32 temp_f8;
    s32 temp_f6_2;
    s32 temp_f6;
    s32 temp_f16_3;
    s32 temp_f16_2;
    s32 temp_f16;
    s32 temp_a1;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f0;
    s32 sp2C;
    u8 *sp30;
    u8 sp37;
    u8 *sp48;
    u8 *sp4C;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp4C, &sp37);
    sp48 = sp4C;
    if (sp4C != NULL) {
        if (sp37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)sp30 + 0x100)) + 0x40, sp2C, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C)) * (*(f32 *)((u8 *)arg0 + 0x4C));
        (*(s16 *)((u8 *)sp4C + 6)) = 0;
        (*(s16 *)((u8 *)sp4C + 0x16)) = 0;
        temp_f2 = *(&D_800DD608 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp4C + 0x26)) = 0;
        temp_f12 = *(&D_800DD618 + temp_t0) * temp_f0;
        (*(s16 *)((u8 *)sp4C + 0x36)) = 0;
        temp_f8 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
        (*(s16 *)((u8 *)sp4C + 0x30)) = (s16) temp_f8;
        (*(s16 *)((u8 *)sp4C + 0)) = (s16) temp_f8;
        temp_f16 = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(s16 *)((u8 *)sp4C + 0x12)) = (s16) temp_f16;
        (*(s16 *)((u8 *)sp4C + 2)) = (s16) temp_f16;
        temp_f6 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
        (*(s16 *)((u8 *)sp4C + 0x34)) = (s16) temp_f6;
        (*(s16 *)((u8 *)sp4C + 4)) = (s16) temp_f6;
        temp_f16_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
        (*(s16 *)((u8 *)sp4C + 0x20)) = (s16) temp_f16_2;
        (*(s16 *)((u8 *)sp4C + 0x10)) = (s16) temp_f16_2;
        temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x30)) * (*(f32 *)((u8 *)arg0 + 0x50))));
        (*(s16 *)((u8 *)sp4C + 0x32)) = (s16) temp_f6_2;
        (*(s16 *)((u8 *)sp4C + 0x22)) = (s16) temp_f6_2;
        temp_f16_3 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
        (*(s16 *)((u8 *)sp4C + 0x24)) = (s16) temp_f16_3;
        (*(s16 *)((u8 *)sp4C + 0x14)) = (s16) temp_f16_3;
        return sp48;
    }
    return NULL;
}
