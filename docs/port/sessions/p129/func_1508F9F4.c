/* P129: the six 16-byte bubble records D_800D2880 .. D_800D28E0 (drawn by func_15090630):
 *   +0 s16 x, +2 s16 y, +4 s16 x centre, +6 s16 size, +8 s16 sway amplitude, +A s16 timer,
 *   +C u8 rise speed, +D u8 state (0 free, 1 growing, 2 rising, 3 popped), +E u8 sway phase, +F u8 wobble phase.
 * D_800D28E0 = frames until the next bubble may spawn. */
#define BUB_S16(r, o) (*(s16 *)((r) + (o)))

// underwater_bubbles_update: spawns, grows, floats and pops the HUD air bubbles; a new bubble needs the player
// (object 0) under water for unkB2 >= 0x5B and a free spawn timer; its pop delay is (6 - min(unkB2 / 240, 6)) * 9.
void func_1508F9F4(void) {
    u8 *r;
    s32 value;
    s32 spawn;
    s32 delay;
    s32 frames;
    s32 v;
    s32 i;
    f32 sway;

    if (D_800D28E0 != 0) {
        D_800D28E0 -= D_800BE9E4;
        if (D_800D28E0 < 0) {
            D_800D28E0 = 0;
        }
    }
    value = D_800CC2D0[0].in_water ? D_800CC2D0[0].unkB2 : 0;
    /* The asm never sets the spawn flag (sp+0x44) to non-zero: it only clears it (value < 0x5B, or delay 0) and
     * otherwise reads whatever the stack slot holds. On the N64 that slot is always the s1 that func_1517ABB0
     * saved there just before (func_15019414 -> func_1517ABB0, then -> func_1508F0A4 -> func_1508F0D4, which
     * never writes it): func_1501878C's s1 = the address of its display list pointer (EU 0x800BEDF0), never 0. So the
     * flag is effectively "spawn allowed". The asm's delay (s7) is stack garbage only when value < 0x5B, where
     * it is never used (no spawn); 0 here. */
    delay = 0;
    spawn = 0;
    if (value >= 0x5B) {
        delay = value / 240;
        if (delay >= 7) {
            delay = 6;
        }
        delay = (6 - delay) * 9;
        spawn = (delay != 0);
    }
    for (r = D_800D2880; r != (u8 *)&D_800D28E0; r += 0x10) {
        if (r[0xD] == 2) {
            v = BUB_S16(r, 0xA) - D_800BE9E4;
            if (v > 0) {
                BUB_S16(r, 0xA) = v;
            } else {
                r[0xD] = 3;
                BUB_S16(r, 0xA) = 6;
            }
        }
        switch (r[0xD]) {
        case 0:
            if (spawn && D_800D28E0 == 0) {
                D_800D28E0 = 10;
                r[0xD] = 1;
                BUB_S16(r, 0) = 0xFC;
                BUB_S16(r, 2) = 0x60;
                BUB_S16(r, 6) = 0;
                r[0xC] = 0;
                r[0xE] = func_150ADA20();
                BUB_S16(r, 8) = 0x500;
                sway = func_15048A40(r[0xE]);
                r[0xF] = 0;
                BUB_S16(r, 0xA) = delay;
                BUB_S16(r, 4) = 0xFC - ((s32)(sway * BUB_S16(r, 8)) >> 8);
            }
            break;
        case 1:
            v = BUB_S16(r, 6) + D_800BE9E4 * 200;
            if (v >= 0x666) {
                r[0xD] = 2;
                v = 0x666;
            }
            BUB_S16(r, 6) = v;
            break;
        case 2:
            frames = D_800BE9E4;
            if (r[0xC] < 0x20) {
                v = r[0xC] + frames;
                if (v > 0x20) {
                    v = 0x20;
                }
                r[0xC] = v;
            }
            BUB_S16(r, 2) -= (s32)(frames * r[0xC]) >> 4;
            v = BUB_S16(r, 6);
            for (i = 0; i < frames; i++) {
                v = (v * 0x104) >> 8;
            }
            BUB_S16(r, 6) = v;
            r[0xE] += frames * 5;
            BUB_S16(r, 8) += frames * 30;
            sway = func_15048A40(r[0xE]);
            r[0xF] += D_800BE9E4 * 10;
            BUB_S16(r, 0) = ((s32)(sway * BUB_S16(r, 8)) >> 8) + BUB_S16(r, 4);
            break;
        case 3:
            if (BUB_S16(r, 0xA) == 0) {
                r[0xD] = 0;
            }
            break;
        }
    }
}
#undef BUB_S16
