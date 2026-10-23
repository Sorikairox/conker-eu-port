extern void (*D_8008FC80[])(u8 *, s32, s32, s32);
s32 func_15131C7C(u8 *, s32);
// particle_timed_event_update: particle update handler 17 (func_1513095C). While the age (+0x1A) is below +0xB0
// the alpha +0x2C ramps as age * +0xB2. While the age (+0x1A, counting down) is <= the trigger time +0xB4 (-1 = none) the event
// D_8008FC80[+0xB6] (-1 = none) is called once with (particle, trigger time, age, -1) and the trigger cleared;
// events are suppressed while D_800BE616 is set. Then the common update func_15131C7C(particle, arg) runs and its
// result is returned.
s32 func_151A2F10(u8 *part, s32 arg) {
    s16 age = *(s16 *)(part + 0x1A);
    s16 when;
    s8 event;

    if (age < *(s16 *)(part + 0xB0)) {
        part[0x2C] = age * *(s16 *)(part + 0xB2);
    }
    if (D_800BE616 == 0) {
        when = *(s16 *)(part + 0xB4);
        event = *(s8 *)(part + 0xB6);
        if (when != -1 && event != -1 && when >= age) {
            D_8008FC80[event](part, when, age, -1);
            *(s16 *)(part + 0xB4) = -1;
        }
    }
    return func_15131C7C(part, arg);
}
