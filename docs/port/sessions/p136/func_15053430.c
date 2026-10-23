s32 func_1507D754(struct127 *);
void func_15055B0C(struct127 *, s32);

/*
 * object_death_resolve: what happens to a dead object (called by func_150535F4 and the event natives). id 0xFF:
 * func_15060F28(obj, 1). Death timer +0x10E in 1..0xEF: func_1505D2B8(obj, 9), returns 0. Else by the type's
 * death flags (byte +0x28 of D_800D1C90[id]): 0x20 (timer < 0xF0) puffs an effect at the object (func_15166F10,
 * 50 above it, scale 0.5); 0x04 asks func_1507D754 for a result (1 / 0 below); then the first of 0x02 (state
 * 0x2A), 0x80 (func_15055B0C(obj, 1000)), 0x01 (func_15053694), 0x40 (respawn timer D_800D2530[+0x13F] = 1250 and
 * func_15060F28(obj, 1)); without those, result 1 -> func_150536D0, result 0 -> func_15060F28(obj, 1).
 * Returns 1.
 */
s32 func_15053430(struct127 *obj) {
    u8 flags;
    s32 res;

    if (obj->id == 0xFF) {
        func_15060F28(obj, 1);
        return 1;
    }
    flags = *((u8 *) D_800D1C90[obj->id] + 0x28);
    if (obj->unk10E != 0 && obj->unk10E < 0xF0) {
        func_1505D2B8(obj, 9);
        return 0;
    }
    res = 0;
    if (obj->unk10E < 0xF0 && (flags & 0x20)) {
        func_15166F10((s32) obj->x_position, (s32) (obj->y_position + 50.0f), (s32) obj->z_position, 0.5f, 0xFF, 0);
    }
    if (flags & 4) {
        res = func_1507D754(obj);
    }
    if (flags & 2) {
        obj->interaction_state = 0x2A;
        return 1;
    }
    if (flags & 0x80) {
        func_15055B0C(obj, 1000);
        return 1;
    }
    if (flags & 1) {
        func_15053694(obj);
        return 1;
    }
    if (flags & 0x40) {
        D_800D2530[obj->unk13F] = 1250;
        func_15060F28(obj, 1);
        return 1;
    }
    if (res == 1) {
        func_150536D0(obj);
        return 1;
    }
    if (res == 0) {
        func_15060F28(obj, 1);
    }
    return 1;
}
