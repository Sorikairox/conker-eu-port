/* Applies the camera records of cutscene slot `slot` (written by func_1501ECA4) to the game. D_800C3A18 = the
 * actor whose record drives the game camera (func_1502330C at the current script position, cached until reset
 * to 0xFF). Two passes over the active actors (D_800C39F0 / D_800C39E8 counts != 0): pass 0 every entry type
 * but 1, pass 1 type 1 (the camera; so the camera sees the objects already placed). Entry = 8 bytes at
 * D_800C3A10[slot] + i * 8: u16 type, u8 a, s8 b, s16 c.
 *   type 1 (camera, only actor D_800C3A18): clamps cam[13] / cam[15] / cam[16] to -20 .. 40, fills the camera
 *     event block D_800C3A20 (eye cam[0..2]; target by a: 1 = actor b's position raised by c (+ cam[14]),
 *     2 = object func_15083E90(b), 3 = entity func_151149AC(b) raised by c, 0 = angle mode) and sends it to the
 *     game camera D_800DBFF0 (func_1512DAD0 event 7; event 5 + func_15129220 first unless flag 0x40000).
 *   type 3: entity func_151149AC(a) gets position / angles / scale (* 0.01) / alpha from the record.
 *   type 2: object func_15083E90(a) takes its actor frame (func_15021834(obj, slot, i)).
 *   type 5: when cam[13] >= 1, func_1517DB6C at the record position with cam[6] / cam[7].
 * D_800C3638 = 0 while running, 1 after. */
void func_15020F6C(s32 slot) {
    f32 *cams;
    f32 *cam;
    f32 *other;
    u8 *ent;
    u8 *ev;
    u8 *e;
    struct108 *gameCam;
    s32 pass;
    s32 i;
    s32 a;
    f32 f;
    f32 v15;
    f32 v16;

    if ((&D_800C35EA)[slot] != 1) {
        return;
    }
    D_800C3638 = 0;
    if (D_800C3A18 == 0xFF) {
        D_800C3A18 = func_1502330C(slot, (&D_800C39D0)[slot]);
    }
    ev = (u8 *)&D_800C3A20;
    for (pass = 0; pass != 2; pass++) {
        for (i = 0; i < D_800C3A5A[slot]; i++) {
            if (D_800C39F0[slot][i] == 0 || D_800C39E8[slot][i] == 0) {
                continue;
            }
            ent = D_800C3A10[slot] + i * 8;
            if (pass == 0) {
                if (*(u16 *)ent == 1) {
                    continue;
                }
            } else if (*(u16 *)ent != 1) {
                continue;
            }
            switch (*(u16 *)ent) {
                case 1:
                    gameCam = D_800DBFF0;
                    if (i != D_800C3A18) {
                        break;
                    }
                    if (!(*(s32 *)((u8 *)gameCam + 0x2C) & 0x40000)) {
                        if (D_800C3671 == 0) {
                            func_1512DAD0(gameCam, 5, (void *)slot);
                        }
                        func_15129220(gameCam);
                    }
                    cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                    f = cam[13];
                    if (f == TRACK_NONE_F) {
                        *(f32 *)(ev + 8) = 0.0f;
                    } else {
                        cam[13] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                        *(f32 *)(ev + 8) = cam[13];
                    }
                    f = cam[15];
                    if (f == TRACK_NONE_F) {
                        v15 = 0.0f;
                    } else {
                        cam[15] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                        v15 = cam[15];
                    }
                    f = cam[16];
                    if (f == TRACK_NONE_F) {
                        v16 = 0.0f;
                    } else {
                        cam[16] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                        v16 = cam[16];
                    }
                    ent = D_800C3A10[slot] + i * 8;
                    *(s32 *)(ev + 4) = slot;
                    *(f32 *)(ev + 0x14) = cam[0];
                    *(f32 *)(ev + 0x18) = cam[1];
                    *(f32 *)(ev + 0x1C) = cam[2];
                    switch (ent[2]) {
                        case 1:
                            /* look at actor ent[3], raised by the entry's s16 */
                            *(s32 *)ev = 0;
                            cams = (f32 *)(&D_800C3958)[slot];
                            other = cams + (s8)ent[3] * 17;
                            *(f32 *)(ev + 0x20) = other[0];
                            *(f32 *)(ev + 0x24) = cam[14] + (other[1] + (f32)*(s16 *)(ent + 4));
                            *(f32 *)(ev + 0x28) = other[2];
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 2:
                            /* look at object ent[3] */
                            e = (u8 *)func_15083E90(ent[3]);
                            if (e == NULL) {
                                continue;
                            }
                            *(s32 *)ev = 0;
                            D_800C3A40 = *(f32 *)(e + 0x14);
                            ent = D_800C3A10[slot] + i * 8;
                            cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                            D_800C3A44 = cam[14] + (*(f32 *)(e + 0x18) + (f32)*(s16 *)(ent + 4));
                            D_800C3A48 = *(f32 *)(e + 0x1C);
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 3:
                            /* look at entity ent[3] (s16 position) */
                            e = func_151149AC(ent[3]);
                            if (e == NULL) {
                                continue;
                            }
                            *(s32 *)ev = 0;
                            D_800C3A40 = *(s16 *)(e + 0x10);
                            ent = D_800C3A10[slot] + i * 8;
                            cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                            D_800C3A44 = cam[14] + (f32)(*(s16 *)(e + 0x12) + *(s16 *)(ent + 4));
                            D_800C3A48 = *(s16 *)(e + 0x14);
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 0:
                            /* angle mode */
                            *(s32 *)ev = 1;
                            *(f32 *)(ev + 0x20) = -cam[5];
                            *(f32 *)(ev + 0x24) = cam[3];
                            *(f32 *)(ev + 0x28) = cam[4];
                            *(f32 *)(ev + 0x2C) = v15;
                            *(f32 *)(ev + 0x30) = v16;
                            *(f32 *)(ev + 0x18) = cam[1] + cam[14];
                            break;
                    }
                    if (D_800C3671 == 0) {
                        func_1512DAD0(gameCam, 7, ev);
                    }
                    break;
                case 3:
                    e = func_151149AC(ent[2]);
                    if (e == NULL) {
                        continue;
                    }
                    e[0x4E] = 0;
                    e[0x6F] &= 0x7F;
                    cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                    *(s16 *)(e + 0x10) = (s32)cam[0];
                    *(s16 *)(e + 0x12) = (s32)(cam[14] + cam[1]);
                    *(s16 *)(e + 0x14) = (s32)cam[2];
                    *(f32 *)(e + 0x0) = cam[3];
                    *(f32 *)(e + 0x4) = cam[4];
                    *(f32 *)(e + 0x8) = cam[5];
                    if (cam[6] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x2C) = cam[6] * 0.01f;
                    }
                    if (cam[7] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x30) = cam[7] * 0.01f;
                    }
                    if (cam[8] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x34) = cam[8] * 0.01f;
                    }
                    a = cam[13];
                    e[0x8A] = (a >= 0x100) ? 0xFF : (a >= 0) ? a : 0;
                    break;
                case 2:
                    func_15021834(func_15083E90(ent[2]), slot, i);
                    break;
                case 5:
                    cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                    if (1.0f <= cam[13]) {
                        func_1517DB6C((s32)cam[0], (s32)cam[1], (s32)cam[2], 0, (s32)cam[6], (s32)cam[7]);
                    }
                    break;
            }
        }
    }
    D_800C3638 = 1;
}
