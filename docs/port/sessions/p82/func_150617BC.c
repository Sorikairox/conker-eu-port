/* Per-frame fades of an object (struct127): per player i (0..D_80082FA0) the visibility byte +0x0B + i moves by
 * 50 towards 0 when bit i of +0x0F is set, else towards 0xFF (jumps there when D_800DBFF4[i] is set). With a
 * fade mode (+0x0A) the alpha +0x07 steps by +0x09 towards +0x08; on arrival mode 6 / 5 calls
 * func_15060F28(obj, 1 / 2), any other mode ends (+0x0A = 0). */
void func_150617BC(struct127 *obj) {
    u8 *o = (u8 *)obj;
    s32 i;
    s32 bit;
    s32 v;

    if (*(s32 *)o == 0) {
        return;
    }
    for (i = 0, bit = 1; i <= D_80082FA0; i++, bit <<= 1) {
        v = o[0xB + i];
        if (o[0xF] & bit) {
            if (v > 0) {
                if (D_800DBFF4[i] != 0) {
                    v = 0;
                } else {
                    v -= 50;
                    if (v < 0) {
                        v = 0;
                    }
                }
                o[0xB + i] = v;
            }
        } else if (v < 0xFF) {
            if (D_800DBFF4[i] != 0) {
                v = 0xFF;
            } else {
                v += 50;
                if (v > 0xFF) {
                    v = 0xFF;
                }
            }
            o[0xB + i] = v;
        }
    }
    if (o[0xA] == 0) {
        return;
    }
    if (o[8] != o[7]) {
        if (o[7] < o[8]) {
            v = o[7] + o[9];
            if (v > o[8]) {
                v = o[8];
            }
        } else {
            v = o[7] - o[9];
            if (v < o[8]) {
                v = o[8];
            }
        }
        o[7] = v;
    }
    if (o[8] != o[7]) {
        return;
    }
    if (o[0xA] == 6) {
        func_15060F28(obj, 1);
    } else if (o[0xA] == 5) {
        func_15060F28(obj, 2);
    } else {
        o[0xA] = 0;
    }
}
