// context_action_set: offers the context action `action` to the player obj (live, +0x127 != 0xFF) for slot 0 (B
// button, player +0x31C byte +0x74) or slot != 0 (+0x75, with +0x7A = the D_800D34B8 hotspot index of target, 0x34-byte
// entries); a slot whose bit 7 is set is locked. Actions 0x2B / 0x2C remember the hotspot in D_800D1DBC and show as
// 0x2A; other actions known to func_15080B38 are recorded in D_800D1940 and show as 0x1A until their D_800D2E60 bit is
// set (first use). arg4 is not used (P195).
s32 func_15080B38(s32 arg0);
extern u8 *D_800D1DBC;

void func_15080900(struct127 *obj, u8 *target, s32 slot, s32 action, s32 arg4) {
    u8 *ctl;

    if (obj == NULL || *(s32 *) obj == 0 || ((u8 *) obj)[0x127] == 0xFF) {
        return;
    }
    if (action == 0x2B || action == 0x2C) {
        D_800D1940 = action;
        D_800D1DBC = target;
        action = 0x2A;
    } else if (func_15080B38(action) != 0) {
        D_800D1940 = action;
        if (!(D_800D2E60[action >> 3] & (1 << (action & 7)))) {
            action = 0x1A;
        }
    }
    ctl = *(u8 **) ((u8 *) obj + 0x31C);
    if (slot == 0) {
        if (!(ctl[0x74] & 0x80)) {
            ctl[0x74] = action;
        }
    } else if (!(ctl[0x75] & 0x80)) {
        ctl[0x75] = action;
        (*(u8 **) ((u8 *) obj + 0x31C))[0x7A] = (target - D_800D34B8) / 0x34;
    }
}
