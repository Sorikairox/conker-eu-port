/* P197 */
s32 memcpy(u8 *, u8 *, s32);
f32 sinf(f32);
f32 cosf(f32);

// ring_effect_create: P197: creates a kind-0x31 record (func_15167A68, view `view`, group arg3) for the 0x30-byte
// spec `spec` (copied to +0x10; spec +0x14 = n points) with `extra` more bytes: a table of n (sin, cos) pairs at
// +0x368 (+0x360 points at it) for angles 0, 2pi/n, ... (step at +0x48), then areas at +0x54 (+0x368 + 8n),
// +0x58 (+0x3B8 + 0x58n) and +0x364 (+0x408 + 0xA8n); +0x40 / +0x44 / +0x50 = 0, s16 +0x4C = s16 +0x28.
// Returns the record, NULL when there is none.
u8 *func_150C8DD0(u8 *spec, s32 extra, s32 view, s32 arg3) {
    u8 *rec;
    s32 i;
    f32 a;

    rec = (u8 *) func_15167A68(0x31, arg3, extra + *(s32 *) (spec + 0x14) * 0xA8 + 0x408, 1, view & 0xFF, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, spec, 0x30);
    *(u8 **) (rec + 0x360) = rec + 0x368;
    *(u8 **) (rec + 0x54) = rec + 0x368 + *(s32 *) (spec + 0x14) * 8;
    *(u8 **) (rec + 0x58) = rec + 0x3B8 + *(s32 *) (spec + 0x14) * 0x58;
    *(f32 *) (rec + 0x40) = 0.0f;
    *(f32 *) (rec + 0x44) = 0.0f;
    *(u8 **) (rec + 0x364) = rec + 0x408 + *(s32 *) (spec + 0x14) * 0xA8;
    *(f32 *) (rec + 0x50) = 0.0f;
    *(s16 *) (rec + 0x4C) = *(s16 *) (rec + 0x28);
    *(f32 *) (rec + 0x48) = 6.2831855f / (f32) *(s32 *) (rec + 0x24);
    for (i = 0, a = 0.0f; i < *(s32 *) (rec + 0x24); i++, a += *(f32 *) (rec + 0x48)) {
        (*(f32 **) (rec + 0x360))[i * 2] = sinf(a);
        (*(f32 **) (rec + 0x360))[i * 2 + 1] = cosf(a);
    }
    return rec;
}
