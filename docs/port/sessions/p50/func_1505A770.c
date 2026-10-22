//HOIST void func_1505A770(struct127 *);
/* P50: gravity. Airborne (+0x28 height != 0 or rising): D_800D1550 / 0.1 steps of vy -= g * 0.1, y += vy * 0.05
 * (IDO unrolled this loop by 4); on the ground: one step of the whole frame. vy is clamped at -500. */
void func_1505A770(struct127 *rec) {
    u8 *arg0 = (u8 *) rec;
    f32 g;
    s32 n;
    s32 i;
    f32 v;

    if (((*(f32 *)(arg0 + 0x28)) != 0.0f) || ((*(f32 *)(arg0 + 0x20)) > 0.0f)) {
        g = (*(f32 *)(arg0 + 0x24)) * 0.1f;
        n = (s32) (*D_800D1550 / 0.1f);
        for (i = 0; i < n; i++) {
            *(f32 *)(arg0 + 0x20) = *(f32 *)(arg0 + 0x20) - g;
            *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (*(f32 *)(arg0 + 0x20) * 0.05f);
        }
        if ((*(f32 *)(arg0 + 0x20)) < -500.0f) {
            *(f32 *)(arg0 + 0x20) = -500.0f;
        }
    } else {
        *(f32 *)(arg0 + 0x20) = *(f32 *)(arg0 + 0x20) - ((*(f32 *)(arg0 + 0x24)) * *D_800D1550);
        v = *(f32 *)(arg0 + 0x20);
        *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (v * *D_800D1550 * 0.5f);
        if (v < -500.0f) {
            *(f32 *)(arg0 + 0x20) = -500.0f;
        }
    }
}
