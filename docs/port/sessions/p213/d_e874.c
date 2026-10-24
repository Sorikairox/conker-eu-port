// hit_reaction_advance: P213: plays the next phase of object `obj`'s current hit reaction (port P209: void; the
/* first argument is not read). Reaction row unk106 of the type's row table (D_800D1588[id] - 8, 0x18-byte rows:
 * +0 kind, +4 sound, +8 unk10F value, +0xA three phases {u16 anim, u8 speed %, u8 flags}). Phase 0 (unk105)
 * first: unk10F from the row, jump flag and the controller's byte 0x26 cleared, the row's sound (0x33 through
 * func_15060B04, others func_15060A30) when func_1506E46C allows it; type 0x5E held by a carrier blends with 0.
 * Move flags 0x000C014E cleared. Phases 0..2: hit bit unk10B bit 0 = the phase flag's bit 0; phase 0 of a living
 * player-like object (unk127 != 0xFF, controller byte 0x197) shakes the camera (func_1517F9F8). A living object
 * past its last phase gets an end action (func_1507CD64: type 0x9A 14, 0x53 10, swimming 4, ground kinds 14 / 19
 * outside level 0x34 13, else by the row kind) and phase 3. Otherwise the hit timer unk10C = flags x 100 (flags
 * 200: move flag 8 and hit bit 0) and the phase's animation starts (func_1505E650, speed % / 100, 1 when 0,
 * blend 6); no animation (or phase 3+, timer 20000) ends the reaction: stun, hit bits and unk10F cleared, a
 * player's controller byte 0x58 and flags 0x01000200 of unkF8 cleared. */
void func_1517F9F8(s32, s32, s32, s32, s32, s32);
void func_15060A30(s32, struct127 *);
void func_1505E874(u8 arg0, struct127 *obj) {
    f32 blend;
    u16 row;
    u8 *rows;
    u8 *r;
    u8 *cell;
    u8 phase;
    u8 flags;
    u8 player;
    s32 sound;
    s32 last;
    s32 end;
    f32 speed;
    u16 anim;
    s32 m;

    blend = 6.0f;
    if (obj->id == 0xFF) {
        return;
    }
    row = obj->unk106;
    rows = *(u8 **)((u8 *)D_800D1588[obj->id] - 8);
    if (rows == NULL) {
        return;
    }
    if (obj->unk105 == 0) {
        r = rows + row * 0x18;
        obj->disable_jump = 0;
        obj->unk10F = r[8];
        if (obj->unk31C != NULL) {
            ((u8 *)obj->unk31C)[0x26] = 0;
        }
        if (obj->id == 0x5E && obj->unk13D != 0) {
            blend = 0.0f;
        }
        sound = *(s32 *)(r + 4);
        if (sound != 0 && func_1506E46C(obj, &sound, 1) != 0) {
            if (sound == 0x33) {
                func_15060B04(sound, obj, 0x5DC0);
            } else {
                func_15060A30(sound, obj);
            }
        }
    }
    obj->unkF4 &= ~0x000C014E;
    phase = obj->unk105;
    if (phase < 3) {
        r = rows + row * 0x18;
        cell = r + phase * 4;
        flags = cell[0xD] & 0xFE;
        obj->unk10B = (obj->unk10B & 0xFE) | (cell[0xD] & 1);
        player = obj->unk127;
        if (player != 0xFF && phase == 0 && obj->unk31C != NULL && obj->camera != NULL
            && ((u8 *)obj->unk31C)[0x197] != 0) {
            func_1517F9F8(0xFF, 0, 0, 0xB4, 0x14, ((u8 *)obj->camera)[0x23D]);
            player = obj->unk127;
        }
        if (player != 0xFF && obj->health == 0) {
            phase = obj->unk105;
            last = phase;
            while (*(u16 *)(r + last * 4 + 0xA) != 0) {
                last++;
            }
            if (last < 2) {
                last = 2;
            }
            if (last == phase + 1) {
                if (obj->id == 0x9A) {
                    end = 14;
                } else if (obj->id == 0x53) {
                    end = 10;
                } else if (obj->in_water != 0) {
                    end = 4;
                } else {
                    m = obj->unk184 & 0x1F;
                    if ((m == 14 || m == 19) && D_800BE9F0 != 0x34) {
                        end = 13;
                    } else {
                        switch (r[0]) {
                            case 14:
                            case 15:
                                end = 16;
                                break;
                            case 16:
                                ((u8 *)obj->unk31C)[0x1AC] = 1;
                                D_800D1580 = (s32)0xFF010434;
                                func_1506E5FC();
                                D_800D1580 = (s32)0xFF070169;
                                func_1506E8D8();
                                end = 0;
                                break;
                            case 32:
                            case 33:
                            case 37:
                            case 38:
                            case 51:
                            case 52:
                            case 72:
                                end = 0;
                                break;
                            case 44:
                                end = 8;
                                break;
                            case 45:
                            case 46:
                            case 47:
                                end = 7;
                                break;
                            case 66:
                                end = 12;
                                break;
                            case 67:
                                end = 11;
                                break;
                            default:
                                end = 1;
                                break;
                        }
                    }
                }
                func_1507CD64(obj, end);
                obj->unk105 = 3;
                return;
            }
        }
        if (flags == 200) {
            obj->unkF4 |= 8;
            obj->unk10B |= 1;
        }
        obj->unk10C = flags * 100;
        phase = obj->unk105;
        cell = r + phase * 4;
        speed = cell[0xC] / 100.0f;
        anim = *(u16 *)(cell + 0xA);
        if (anim != 0) {
            obj->unk105 = phase + 1;
        }
        if (speed == 0.0f) {
            speed = 1.0f;
        }
    } else {
        obj->unk10C = 20000;
        speed = 1.0f;
        anim = 0;
    }
    if (anim == 0) {
        obj->unkF4 &= ~8;
        obj->stunned = 0;
        obj->unk10B = 0;
        obj->unk10F = 0;
        if (obj->interaction_state == 1) {
            ((u8 *)obj->unk31C)[0x58] = 0;
            obj->unkF8 &= ~0x01000200;
        }
    } else {
        func_1505E650(obj, anim, speed, blend, 0.0f, 0.0f, 0);
    }
}
