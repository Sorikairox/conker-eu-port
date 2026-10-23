extern s8 D_80090210[];        /* settings minimum (0x1C bytes) */
extern s8 D_8009022C[];        /* settings maximum */

/*
 * P85: clamp the 0x1C settings bytes D_800E1010 (signed): a value outside [D_80090210[i], D_8009022C[i]] is reset to
 * its default D_800901F4[i] (as func_151DDF20 resets all of them). After a failed save checksum the settings are 0xFF
 * (-1) and this puts e.g. the language D_800E101A back in range. Callers pass arguments it ignores.
 */
void func_151DDF6C(void) {
    s32 i;

    for (i = 0; i < 0x1C; i++) {
        if (D_800E1010[i] < D_80090210[i] || D_8009022C[i] < D_800E1010[i]) {
            D_800E1010[i] = D_800901F4[i];
        }
    }
}
