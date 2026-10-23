/* P129: the state tables live in the ROM's game_data (EU addresses). The rule table D_800A65E0 and the five s8
 * handler lists D_8008B3CC points to (0x800A66C0 + 0x1C * kind) sit in the GLOBAL_ASM's rodata_inject block in the
 * matching build. They are referenced by symbol only, never defined here: the browser keeps every undefined N64
 * data symbol inside its ROM mirror at the N64 address, and relocates D_8008B3CC's five words there. */
extern u32 D_800A65E0[28][2];     /* per rule: required old-state bits, required new-state bits */
extern s8 *D_8008B3CC[5];         /* per object kind (obj+0x1D): handler index per rule, -1 = none */
s32 func_151595F4(u8 *, u8);
s32 func_15159690(u8 *, u8);
s32 func_151596F4(u8 *, u8);
s32 func_151597A0(u8 *, u8 *, u8);
s32 func_15159828(u8 *, s32);

/* sllv uses the low 5 bits of the shift count */
#define STATE_BIT(n) (1 << ((n) & 0x1F))
#define STATE_MASK(s0, s1, s2, s3, s4) \
    (STATE_BIT(s0) | STATE_BIT((s1) + 3) | STATE_BIT((s2) + 6) | STATE_BIT((s3) + 9) | STATE_BIT((s4) + 13))

// watcher_state_update: recomputes the five state bytes (obj+0x2C..0x30) of a watcher object for its target
// (obj+0x18) and, when the watcher is armed (obj+0x31 bit 0), calls the transition handlers of its kind whose
// old/new state masks match.
void func_1515929C(u8 *obj) {
    u8 old0 = obj[0x2C];
    u8 old1 = obj[0x2D];
    u8 old2 = obj[0x2E];
    u8 old3 = obj[0x2F];
    u8 old4 = obj[0x30];
    u8 *target;
    u8 s4;
    s32 new_mask;
    s32 i;
    s8 h;

    obj[0x2C] = func_151595F4(*(u8 **)(obj + 0x18), obj[0x1D]);
    if (obj[0x2C] == 0) {
        obj[0x2D] = func_15159690(*(u8 **)(obj + 0x18), obj[0x1D]);
    } else {
        obj[0x2D] = 2;
    }
    if (obj[0x2C] != 0) {
        obj[0x2E] = 0;
    } else if (obj[0x2D] == 0) {
        obj[0x2E] = 1;
    } else {
        obj[0x2E] = func_151596F4(*(u8 **)(obj + 0x18), obj[0x1D]);
    }
    obj[0x2F] = func_151597A0(*(u8 **)(obj + 0x18), obj + 0x20, obj[0x2F]);
    target = *(u8 **)(obj + 0x18);
    *(f32 *)(obj + 0x20) = *(f32 *)(target + 0x14);
    *(f32 *)(obj + 0x24) = *(f32 *)(target + 0x18);
    *(f32 *)(obj + 0x28) = *(f32 *)(target + 0x1C);
    s4 = func_15159828(target, obj[0x1D]);
    obj[0x30] = s4;
    if (!(obj[0x31] & 1)) {
        return;
    }
    new_mask = STATE_MASK(obj[0x2C], obj[0x2D], obj[0x2E], obj[0x2F], s4);
    for (i = 0; i < 28; i++) {
        h = D_8008B3CC[obj[0x1D]][i];
        if (h == -1) {
            continue;
        }
        if ((D_800A65E0[i][0] | STATE_MASK(old0, old1, old2, old3, old4)) != D_800A65E0[i][0]) {
            continue;
        }
        if ((D_800A65E0[i][1] | new_mask) != D_800A65E0[i][1]) {
            continue;
        }
        ((void (*)(u8 *))D_8008B370[h])(obj);
    }
}
#undef STATE_MASK
#undef STATE_BIT
