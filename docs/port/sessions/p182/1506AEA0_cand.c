// players_effect_at_point: for every player whose bit is set in D_800CC680, func_15137610(player, D_800D1980,
// D_eu_800D1990, NULL, 0xFF, 1) (the point / vector func_1506B04C fills in).
void func_1506AEA0(void) {
    s32 mask = D_800CC680;
    u8 *player = (u8 *) D_800CC2D0;

    while (mask != 0) {
        if (mask & 1) {
            func_15137610(player, (f32 *) D_800D1980, (f32 *) D_eu_800D1990, NULL, 0xFF, 1);
        }
        mask >>= 1;
        player += 0x32C;
    }
}
