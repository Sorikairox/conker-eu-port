/* Scene teardown, player (func_1501E888): clears flag 0x200 of object 0 (+0x25C) and, unless D_800C39CA, resets
 * the player object func_15083E90(1) (D_800C3E78 = its index): speeds / timers cleared; in water (water level
 * +0x118 set, D_80096DCC = none, and above the feet +0x18): swimming (+0xAD = 1, func_1508F060 when the water
 * is deeper than 50 above the floor +0x1A6 or the model flag +0x31C->+0x20 bit 0 is set), else standing on the
 * floor +0x180 (+0x20 = -4, +0x24 = 5). Then the height above the floor (+0x28), cleared input / state bytes,
 * D_800D154C = the player and the idle animation (func_1507F640). `slot` is not read. */
void func_15023684(s32 slot) {
    u8 *p;
    f32 water;

    *(u32 *)((u8 *)D_800CC2D0 + 0x25C) &= ~0x200;
    if (D_800C39CA != 0) {
        return;
    }
    p = (u8 *)func_15083E90(1);
    if (p == NULL) {
        return;
    }
    D_800C3E78 = (p - (u8 *)D_800CC2D0) / 0x32C;
    *(f32 *)(p + 0x3C) = 0.0f;
    if (*(f32 **)(p + 0x31C) != NULL) {
        **(f32 **)(p + 0x31C) = 0.0f;
    }
    *(f32 *)(p + 0x54) = 0.0f;
    *(s16 *)(p + 0xCC) = 0;
    p[0xD0] = 0;
    water = *(f32 *)(p + 0x118);
    if (D_80096DCC != water && *(f32 *)(p + 0x18) < water) {
        p[0xAD] = 1;
        *(f32 *)(p + 0x20) = 0.0f;
        *(f32 *)(p + 0x24) = 0.0f;
        if (water - 50.0f < (f32)*(s16 *)(p + 0x1A6) || (*(u8 **)(p + 0x31C))[0x20] & 1) {
            *(s16 *)(p + 0xB2) = 0;
            func_1508F060();
        }
    } else {
        p[0xAD] = 0;
        *(s16 *)(p + 0xB2) = 0;
        *(f32 *)(p + 0x20) = -4.0f;
        *(f32 *)(p + 0x18) = *(f32 *)(p + 0x180);
        *(f32 *)(p + 0x1CC) = *(f32 *)(p + 0x180);
        *(f32 *)(p + 0x24) = 5.0f;
    }
    p[0x81] = 0;
    p[0x83] = 0;
    p[0x89] = 0;
    p[0x8A] = 0;
    p[0x104] = 0;
    *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18) - *(f32 *)(p + 0x180);
    D_800D154C = (struct127 *)p;
    func_1507F640();
    (*(u8 **)(p + 0x31C))[0x23] = 0;
    p[0x276] = 0;
    *(s16 *)(p + 0x282) = 0;
    *(s16 *)(p + 0x278) = 0;
    p[0x284] = p[0x285] = p[0x286] = p[0x287] = 0;
    (*(u8 **)(p + 0x31C))[0x31] = 0;
}
