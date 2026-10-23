/* End of cutscene slot `slot` (skipped != 0: cut short, event 0xF, else 0x10 to func_15169040 with the scene
 * number): position back to the start D_800C40AE, scene marked as seen (func_1501D2C4), slot unloaded,
 * per-scene teardown (func_1501E7A8, func_1502348C, func_15023684, func_1501EA84, func_1501E5AC), view reset
 * (func_1510B8AC with the game camera's +0x19C / +0x1A0). A queued follow-up scene (D_800C39E2 = scene + 1,
 * level D_800C39E3, 0x25 = load it into level 0x25 temporarily) is loaded at once (func_1501D348, slot state
 * 2); otherwise the screen fade / pause flags are cleared. */
void func_1501E888(s32 skipped, s32 slot) {
    u8 *loaded;
    struct108 *gameCam;
    u8 scene;
    s32 level;
    s32 savedLevel;

    loaded = &D_800C35EA + slot;
    gameCam = D_800DBFF0;
    if (*loaded == 0) {
        return;
    }
    scene = (&D_800C3A08)[slot];
    func_15169040((s32)&scene, skipped ? 0xF : 0x10);
    D_800C39D8[slot] = -100;
    (&D_800C39D0)[slot] = D_800C40AE;
    func_1501D2C4(D_800BE9F0, (&D_800C3A08)[slot]);
    *loaded = 0;
    D_800C3638 = 0;
    func_1501E7A8(slot);
    func_1502348C();
    D_800C3A86 = 0;
    D_800C3683 = 0;
    func_15023684(slot);
    func_1501EA84(slot);
    func_1501E5AC(slot);
    D_800C3A6C = 0.0f;
    D_800C3A70 = 0.0f;
    D_800C3A74 = 0.0f;
    func_1510B8AC(0, *(f32 *)((u8 *)gameCam + 0x19C), *(f32 *)((u8 *)gameCam + 0x1A0), 1.0f);
    if (D_800C39E2 != 0) {
        *loaded = 2;
        level = D_800C39E3;
        if (level == 0x25) {
            savedLevel = D_800BE9F0;
            D_800BE9F0 = 0x25;
        }
        D_800C3671 = 0;
        func_1501D348(level, D_800C39E2 - 1, slot, D_800C3C90, D_800C3C94);
        if (D_800C39E3 == 0x25) {
            D_800BE9F0 = savedLevel;
        }
    } else {
        if (D_800C40AB != 0) {
            func_1517F3B0(0, 0, 0, 0x19, 0, 0);
        }
        D_80090124 = 0;
        D_800C3670 = 0;
        D_800C3671 = 0;
    }
}
