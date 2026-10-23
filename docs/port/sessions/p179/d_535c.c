void func_151C2600(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 arg4);
void func_15137610(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5);
void func_1507DE4C(struct127 *arg0);
void func_15138C80(struct127 *arg0, s32 arg1, s32 arg2);
s32 func_1505D024(struct127 *, s32, u16, s32);

// object_take_hit: P179: a hit on `obj` by `attacker` (or NULL) at `pos` / `pos2`, direction `dir`, hit record `rec`
/* (or NULL). Body kinds that react with a spark (the list below) get func_151C2600 (attacker, pos, dir, 9, rec +4
 * or 0). A kind-0xA / type-3 hit record (rec +0x58 / +0x59) wears down the shield count obj +0x1CA: at 3 or more it
 * loses one, else it is cleared, func_1507DE4C / func_15138C80 (obj, 0xFF, 1) run and the message flags become
 * 0x100020 (else `flags` | 0x60000). Then func_15137610 (obj, pos, pos2, dir, arg7, arg8); and only if the count
 * was non-zero on entry, the message func_1505D024(obj, flags | 0x80000, (dir angle - 0x4000) | 1, attacker index
 * or -1). The angle is func_150484A0(dir x, dir z) x 65536 / 2pi converted as IDO's float -> unsigned (negative ->
 * 0xFFFF). */
void func_151D535C(u8 *obj, u8 *attacker, u8 *pos, f32 *pos2, u8 *rec, s32 flags, f32 *dir, u8 arg7, s32 arg8) {
    u8 count;
    s32 untouched;
    s32 w;
    u16 angle;

    switch (obj[4]) {
        case 0x09: case 0x0F: case 0x10: case 0x12: case 0x17: case 0x1B: case 0x1E: case 0x28: case 0x29:
        case 0x2A: case 0x2B: case 0x2C: case 0x2E: case 0x38: case 0x41: case 0x42: case 0x4B: case 0x46:
        case 0x47: case 0x49: case 0x4A: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x52: case 0x5D:
        case 0x60: case 0x61: case 0x66: case 0x67: case 0x70: case 0x73: case 0x77: case 0x7B: case 0x89:
        case 0x8C: case 0x8E: case 0x8F: case 0x91: case 0x9E: case 0xA6: case 0xAB: case 0xAC: case 0xB2:
        case 0xB4: case 0x5B:
            func_151C2600(attacker, pos, (u8 *) dir, 9, (rec != NULL) ? *(f32 *)(rec + 4) : 0.0f);
            break;
    }
    count = obj[0x1CA];
    untouched = (count == 0) ? 1 : 0;
    flags |= 0x60000;
    if (rec != NULL && rec[0x59] == 3 && rec[0x58] == 0xA) {
        if (count >= 3) {
            obj[0x1CA] = count - 1;
        } else {
            obj[0x1CA] = 0;
            func_1507DE4C((struct127 *) obj);
            func_15138C80((struct127 *) obj, 0xFF, 1);
            flags = 0x100020;
        }
    }
    func_15137610(obj, (f32 *) pos, pos2, dir, arg7, arg8);
    if (untouched != 0) {
        return;
    }
    w = (s32) (func_150484A0(dir[0], dir[2]) * 10430.378f);
    angle = (w < 0) ? 0xFFFF : w;
    func_1505D024((struct127 *) obj, flags | 0x80000, (u16) ((angle - 0x4000) | 1),
                  (attacker != NULL) ? (struct127 *) attacker - D_800CC2D0 : -1);
}
