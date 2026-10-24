// mover_step: moves the object's s16 position +0x10 towards its s32 target +0x7C (+0x3C: sound entry index >> 10,
// speed in the other bits; +0x5A gets the per-axis delta). At the target the deltas are cleared and the entry's
// stop sound plays if the move sound was on (+0x74); entries with a near-arrival sound go to func_1511712C;
// otherwise the move sound starts (unless +0x74) and each axis steps by (speed * D_800BE9E4) / 2, clamped.
typedef struct {
    /* 0x0 */ s16 move_sfx;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 stop_sfx;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 near_sfx;
    /* 0xA */ s16 near_lead;
} MoverSfx; // 0xC
extern MoverSfx D_80089600[];
s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags);

void func_1511712C(u8 *obj);

void func_15116F34(u8 *obj) {
    s32 bits = *(s32 *)(obj + 0x3C);
    s32 kind = bits >> 10;
    s16 *pos = (s16 *)(obj + 0x10);
    s32 *target = (s32 *)(obj + 0x7C);
    s16 *delta = (s16 *)(obj + 0x5A);
    s32 step;
    s32 i;

    if (target[0] == pos[0] && target[1] == pos[1] && target[2] == pos[2]) {
        delta[2] = 0;
        delta[1] = delta[2];
        delta[0] = delta[2];
        if (*(u16 *)(obj + 0x74) != 0) {
            if (kind != 0 && D_80089600[kind].stop_sfx != 0) {
                func_151152A4(obj, D_80089600[kind].stop_sfx, 0x5DC0, 0x7D0, 0xFA0, 4);
            }
            *(u16 *)(obj + 0x74) = 0;
        }
        return;
    }
    if (kind != 0 && D_80089600[kind].near_sfx != 0) {
        func_1511712C(obj);
        return;
    }
    if (kind != 0 && *(u16 *)(obj + 0x74) == 0 && D_80089600[kind].move_sfx != 0) {
        func_151152A4(obj, D_80089600[kind].move_sfx, 0x5DC0, 0x7D0, 0xFA0, 0);
    }
    step = ((bits & 0xFFFF03FF) * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        delta[i] = pos[i];
        if (pos[i] != target[i]) {
            if (target[i] < pos[i]) {
                pos[i] -= step;
                if (pos[i] < target[i]) {
                    pos[i] = target[i];
                }
            } else {
                pos[i] += step;
                if (target[i] < pos[i]) {
                    pos[i] = target[i];
                }
            }
        }
        delta[i] = pos[i] - delta[i];
    }
}
