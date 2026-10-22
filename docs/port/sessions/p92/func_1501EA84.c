/* Scene end, camera and objects of cutscene slot `slot` (called by func_1501E888). The camera event block
 * D_800C3A20 = {1, slot, .., eye = game camera +0x2F8..0x300, 0, +0x388, +0x37C} is sent to the game camera
 * (func_1512DAD0 event 7) unless D_800C3671; then event 8 with D_800C3A94 at +0xC unless it is unset
 * (D_80096D74), and event 10 with D_800C3A98 / D_800C3A9C unless that is unset (D_80096D78). Without a queued
 * follow-up scene (D_800C39E2) and D_800C3671: event 6 (with the slot number as its data), skipped once when
 * D_800C3AA0 is set (it is cleared). Then func_1502298C (unless D_800C3A7E[slot]) and func_15022864; every
 * object of the scene (func_15022A8C) gets byte +0xA4 and the floats +0xB8 / +0xC4 cleared. Without a follow-up
 * scene: D_eu_800C3E78 = 2, D_800C3663 = 0, the start angle / position D_800C39B4 / D_800C39AC come back from
 * D_800C39C0 / D_800C39B8. */
void func_1501EA84(s32 slot) {
    struct108 *cam;
    s32 *ev;
    u8 *obj;

    ev = &D_800C3A20;
    cam = D_800DBFF0;
    ev[0] = 1;
    ev[1] = slot;
    ((f32 *)ev)[5] = *(f32 *)((u8 *)cam + 0x2F8);
    ((f32 *)ev)[6] = *(f32 *)((u8 *)cam + 0x2FC);
    ((f32 *)ev)[7] = *(f32 *)((u8 *)cam + 0x300);
    ((f32 *)ev)[8] = 0.0f;
    ((f32 *)ev)[9] = *(f32 *)((u8 *)cam + 0x388);
    ((f32 *)ev)[10] = *(f32 *)((u8 *)cam + 0x37C);
    if (D_800C3671 == 0) {
        func_1512DAD0(cam, 7, ev);
        if (D_800C3A94 != D_80096D74) {
            ((f32 *)ev)[3] = D_800C3A94;
            func_1512DAD0(cam, 8, ev);
        }
        if (D_800C3A98 != D_80096D78) {
            ((f32 *)ev)[3] = D_800C3A98;
            ev[4] = D_800C3A9C;
            func_1512DAD0(cam, 10, ev);
        }
    }
    if (D_800C39E2 == 0 && D_800C3671 == 0) {
        if (D_800C3AA0 == 0) {
            func_1512DAD0(cam, 6, (void *)slot);
        } else {
            D_800C3AA0 = 0;
        }
    }
    if ((&D_800C3A7E)[slot] == 0) {
        func_1502298C(slot);
    }
    func_15022864(slot);
    for (obj = (u8 *)D_800CC2D0; obj != (u8 *)&D_800D121C; obj += 0x32C) {
        if (*(s32 *)obj != 0 && func_15022A8C((s32 *)obj) != 0) {
            obj[0xA4] = 0;
            *(f32 *)(obj + 0xB8) = 0.0f;
            *(f32 *)(obj + 0xC4) = 0.0f;
        }
    }
    if (D_800C39E2 == 0) {
        D_eu_800C3E78 = 2;
        D_800C3663 = 0;
        D_800C39B4 = D_800C39C0;
        D_800C39AC[0] = D_800C39B8[0];
        D_800C39AC[1] = D_800C39B8[1];
        D_800C39AC[2] = D_800C39B8[2];
    }
}
