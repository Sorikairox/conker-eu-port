extern u8 D_800C3A92;
extern u8 D_800C40B8;

// event_query_scene: event-script scene queries (ids 0x1xxx; arg0 = scene, arg1 = query). P176 (browser P174):
// returns the asm's per-case answer (jtbl_8009E828); the m2c body was void and the s32 handler table read 0.
// 1: scene arg0 no longer playing (0 while D_800C35C4 is set), 2: scene arg0 playing (D_800C40B8), 3 / 6: cutscene
// arg0 playing (D_800C3A08), 4: no scene playing, 5: D_800C3A92 (debug skip). Other queries: the asm leaves v0
// unchanged (0 here).
s32 func_1509CBD8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        if (D_800C35C4 != 0) {
            return 0;
        }
        if (D_800C35EA == 0) {
            return 1;
        }
        if (arg0 == D_800C40B8) {
            return 0;
        }
        return 1;
    case 2:
        if (D_800C35EA == 1 && arg0 == D_800C40B8) {
            return 1;
        }
        return 0;
    case 3:
        if (D_800C35EA == 1 && arg0 == D_800C3A08) {
            return 1;
        }
        return 0;
    case 4:
        return D_800C35EA != 1;
    case 5:
        return D_800C3A92;
    case 6:
        if (D_800C35EA == 1 && arg0 == D_800C3A08) {
            return 1;
        }
        return 0;
    }
    return 0;
}
