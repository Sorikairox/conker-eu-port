#ifdef NON_MATCHING
void func_1508EF80(u8 *, u8 *, f32, u8 *);

/* Player sideways tilt: while button bit 0 or 1 of the pad word (*unk36C) is held (and flag 0x200000 of unk84 is
 * clear, and unk698 is 0), the direction +1 / -1 goes to unk6B0, a hold counter (+0x6C0) counts up and the tilt
 * angle (+0x6C4) moves by dir * 0.5 * D_800BE9A4 (frame scale), clamped to [-10, 10]. With unk2C bit 0x400 the
 * counter is set to 20 and nothing is rotated. Released, the angle decays by 0.2 * angle * D_800BE9A4 (D_800A3AC0)
 * until it is 0. Each step rotates the +0x2F8 vector about +0x2A4 by angle * D_800BE9A4 / 2.5 (func_1508EF80). */
void func_1512D900(struct108 *p) {
    s32 *count = (s32 *) ((u8 *) p + 0x6C0);
    f32 *angle = (f32 *) ((u8 *) p + 0x6C4);
    u16 pad = *p->unk36C;
    f32 a;

    if ((pad & 3) != 0 && !(p->unk84 & 0x200000)) {
        if (p->unk698 != 0) {
            return;
        }
        if (pad & 1) {
            p->unk6B0 = 1;
        } else {
            p->unk6B0 = -1;
        }
        *count += 1;
        *angle += (f32) p->unk6B0 * 0.5f * D_800BE9A4;
        a = *angle;
        if (a < -10.0f) {
            *angle = -10.0f;
        } else {
            *angle = (10.0f < a) ? 10.0f : a;
        }
        if (p->unk2C & 0x400) {
            *count = 20;
            return;
        }
    } else {
        a = *angle;
        if (a == 0.0f) {
            return;
        }
        *angle = a - a * 0.2f * D_800BE9A4;
    }
    func_1508EF80((u8 *) &p->unk2F8, (u8 *) &p->unk2A4, *angle * D_800BE9A4 / 2.5f, (u8 *) &p->unk2F8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B110/func_1512D900.s")
#endif
