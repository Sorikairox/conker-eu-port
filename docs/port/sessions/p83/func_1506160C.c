/* Fade / visibility command for an object (struct127). Commands >= 8 work on player p's visibility:
 * 8 = hide (bit p of +0x0F set, target 0), 10 = hide at once (bit p + 4 set), others = show (bit p cleared,
 * target 0xFF); a pending "at once" bit p + 4 sets the byte +0x0B + p and is cleared; the byte also jumps to the
 * target when +0x2FD or D_800DBFF4[p] is set. Commands < 8 start an alpha fade (+0x0A mode, +0x07 alpha,
 * +0x08 target, +0x09 step) unless a fade of a higher mode runs: 4 = fade in from 0, 5 / 6 = fade out (then
 * removal, func_150617BC), 2 = fade to a2 by a3, 1 = set alpha a2 and stop. With D_800DBFF4 set the alpha
 * jumps to the target. */
void func_1506160C(struct127 *obj, u8 cmd, u8 a2, u8 a3, u8 p) {
    u8 *o = (u8 *)obj;
    u8 target;
    s32 bit;

    if (cmd >= 8) {
        if (cmd == 10) {
            o[0xF] |= (1 << p) << 4;
            target = 0;
        } else {
            bit = 1 << p;
            if (cmd == 8) {
                o[0xF] |= bit;
                target = 0;
            } else {
                o[0xF] &= ~bit;
                target = 0xFF;
            }
            if (o[0xF] & (bit << 4)) {
                o[0xB + p] = target;
            }
            o[0xF] &= ~(bit << 4);
        }
        if (o[0x2FD] != 0 || D_800DBFF4[p] != 0) {
            o[0xB + p] = target;
        }
        return;
    }
    if (cmd < o[0xA]) {
        return;
    }
    switch (cmd) {
        case 4:
            o[0xA] = cmd;
            o[7] = 0;
            o[8] = 0xFF;
            o[9] = 0x20;
            break;
        case 5:
            o[0xA] = cmd;
            o[8] = 0;
            o[9] = 0x20;
            break;
        case 6:
            o[0xA] = cmd;
            o[8] = 0;
            o[9] = 8;
            break;
        case 2:
            o[0xA] = cmd;
            o[8] = a2;
            o[9] = a3;
            break;
        case 1:
            o[0xA] = 0;
            o[7] = a2;
            o[8] = a2;
            break;
    }
    if (*(s32 *)D_800DBFF4 != 0) {
        o[7] = o[8];
    }
}
