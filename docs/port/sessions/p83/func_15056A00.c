/* Hit reaction of an object: row D_80099DFC[row] gives an animation per strength (a1 above row[7]: heavy,
 * above row[2]: medium, else light) and side (front / back from the angles +0x76 / +0x78); 0xFF = none. Starts
 * it: health +0x218 -5, stun timer +0x21C, state 13, speed +0x44 = 0, move flags +0xF4 = 4, faces +0x76. */
void func_15056A00(struct127 *obj, s32 arg1, u8 row) {
    u8 *o = (u8 *)obj;
    u8 strength = arg1;
    u8 *anims = D_80099DFC[row];
    u8 idx;
    u16 angle;

    idx = 0;
    if (anims[7] < strength) {
        idx = 5;
    } else if (anims[2] < strength) {
        idx = 2;
    }
    angle = *(u16 *)(o + 0x76);
    if ((*(u16 *)(o + 0x78) - angle) & 0x8000) {
        idx += 3;
    } else {
        idx += 4;
    }
    if (anims[idx] != 0xFF) {
        *(s32 *)(o + 0x218) -= 5;
        *(s16 *)(o + 0x21C) = 20000;
        o[0x223] = 13;
        *(f32 *)(o + 0x44) = 0.0f;
        *(s32 *)(o + 0xF4) = (*(s32 *)(o + 0xF4) & ~0xE) | 4;
        *(u16 *)(o + 0x78) = angle;
        *(u16 *)(o + 0x7A) = angle;
        o[0x138] = 0;
        *(s16 *)(o + 0x244) = anims[idx];
    }
}
