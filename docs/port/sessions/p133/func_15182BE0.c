void *memcpy(void *, const void *, size_t);

/*
 * colour_fade_start: starts a colour fade effect (func_15149130 type 0x39, 8-byte payload, lasting `frames`) with
 * the colour (r, g, b, a), the byte `mode` and the per-frame alpha step a / frames; arg6 / arg7 go to
 * func_15149130 as they are. Nothing when frames <= 0 or no effect slot is free. The asm leaves payload byte 5
 * uninitialised (stack garbage); the C writes 0 there.
 */
s32 func_15182BE0(u8 r, u8 g, u8 b, u8 a, s16 frames, u8 mode, u8 arg6, s32 arg7) {
    struct {
        u8 r, g, b, a, mode, pad;
        s16 step;
    } fade;
    struct260 *e;

    if (frames > 0) {
        fade.r = r;
        fade.step = a / frames;
        fade.a = a;
        fade.g = g;
        fade.b = b;
        fade.mode = mode;
        fade.pad = 0;
        e = func_15149130(frames, -1, 0x39, 3, 1, 0, (struct37 *) 8, arg6, arg7);
        if (e != NULL) {
            memcpy((u8 *) e + 0x28, &fade, 8);
        }
    }
    return 0;
}
