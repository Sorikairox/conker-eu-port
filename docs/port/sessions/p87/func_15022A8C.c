/* Does object `obj` take part in the loaded cutscene? Slot 1 for object kind 4 (byte +5), else slot 0; its id
 * is the actor id of its owner D_800CC2D0[obj[0x65]] (byte at +0x12F) when it has one, else its own byte +0x3B.
 * Returns 2 (owned) / 1 when an active actor of that slot has entry type 2 (object) with that id (entry byte
 * +2), else 0 (also for no object, a free slot obj[0] == 0, or no scene loaded in slot 0). */
s32 func_15022A8C(s32 *obj) {
    u8 *ent;
    u8 owner;
    u8 id;
    s32 slot;
    s32 n;
    s32 i;

    if (obj == NULL || obj[0] == 0 || D_800C39E8[0] == NULL) {
        return 0;
    }
    slot = (((u8 *)obj)[5] == 4) ? 1 : 0;
    owner = ((u8 *)obj)[0x65];
    if (owner != 0) {
        id = (&D_800CC3FF)[owner * 0x32C];
    } else {
        id = ((u8 *)obj)[0x3B];
    }
    n = D_800C3A5A[slot];
    for (i = 0; i < n; i++) {
        if (D_800C39E8[slot][i] == 0) {
            continue;
        }
        ent = D_800C3A10[slot] + i * 8;
        if (*(u16 *)ent == 2 && ent[2] == id) {
            return (owner != 0) ? 2 : 1;
        }
    }
    return 0;
}
