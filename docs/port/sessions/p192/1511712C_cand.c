// mover_step_sfx: func_15116F34's path for movers whose sound entry has a near-arrival sound: starts the move sound
// (entry +0, unless +0x74 says it already plays), steps the s16 position +0x10 towards the s32 target +0x7C by
// ((+0x3C & 0xFFFF03FF) * D_800BE9E4) / 2 per axis (clamped; +0x5A gets the per-axis delta) and plays the entry's
// +8 sound once the largest remaining distance minus +0xA * speed / 2 drops to 0 (on the frame it crosses, or
// when the move sound started this frame).
void func_1511712C(u8 *obj) {
    s32 bits = *(s32 *)(obj + 0x3C);
    s32 kind = bits >> 10;
    s32 speed = bits & 0xFFFF03FF;
    s16 *pos = (s16 *)(obj + 0x10);
    s32 *target = (s32 *)(obj + 0x7C);
    s16 *delta = (s16 *)(obj + 0x5A);
    s32 started = FALSE;
    s32 farthest = 0;
    s32 step;
    s32 dist;
    s32 i;

    if (kind != 0 && *(u16 *)(obj + 0x74) == 0 && D_80089600[kind].move_sfx != 0) {
        func_151152A4(obj, D_80089600[kind].move_sfx, 0x5DC0, 0x7D0, 0xFA0, 0);
        started = TRUE;
    }
    step = (speed * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        delta[i] = pos[i];
        if (pos[i] != target[i]) {
            if (target[i] < pos[i]) {
                pos[i] -= step;
                dist = pos[i] - target[i];
            } else {
                pos[i] += step;
                dist = target[i] - pos[i];
            }
            if (dist < 0) {
                pos[i] = target[i];
            }
            if (farthest < dist) {
                farthest = dist;
            }
        }
        delta[i] = pos[i] - delta[i];
    }
    if (kind != 0 && D_80089600[kind].near_sfx != 0) {
        farthest -= (D_80089600[kind].near_lead * speed) >> 1;
        if (farthest <= 0 && (-step < farthest || started)) {
            func_151152A4(obj, D_80089600[kind].near_sfx, 0x5DC0, 0x7D0, 0xFA0, 0);
        }
    }
}
