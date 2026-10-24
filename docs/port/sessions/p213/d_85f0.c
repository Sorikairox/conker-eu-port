// object_stun_update: P210: per-frame stun / hit-recovery update of object `obj` (port P209: void, one argument).
/* Hover physics func_1505A3A8 (speed unk109 / 10); remembers the height in unk1CC while it is unset (>= 100000);
 * while lifted (+0xAD 1..9) no gravity, the upward speed fades (x0.9 below 60) and above unk118 - 20 the lift
 * ends (gravity 4). unk21C is cleared unless a player in multiplayer. Unless stunned 0xFF: the stun counter
 * counts down (0xFE stays; a dead player keeps it), the hit timer unk10C by D_800CC264 (cleared when unk28 < 0.2
 * with flag 0x100; at 0 the controller's byte 0x7D is cleared and func_1505E874 runs). Stun over: speeds and
 * turning stop (players: func_1506B078 when lifted, else gravity 4 and flag 0x8000 cleared), unk23A = unk238 when
 * set. Still stunned: the hit reaction func_150599C8(obj, 12, heading (turned round with unk10B bit 4)) unless
 * unk10B bit 2, with unk80 = 10. */
void func_150585F0(struct127 *obj) {
    u8 *b = (u8 *)obj;
    u8 lift;
    u8 stun;
    u8 hit;
    u16 heading;

    func_1505A3A8(0.0f, obj, 1.0f, obj->unk109 * 0.1f, 0);
    if (obj->unk1CC < 100000.0f) {
        obj->unk1CC = obj->y_position;
    }
    lift = b[0xAD];
    if (lift != 0 && lift < 10) {
        obj->gravity = 0.0f;
        if (obj->y_velocity < 60.0f) {
            obj->y_velocity *= 0.9f;
        }
        if (obj->unk118 - 60.0f + 40.0f < obj->y_position) {
            obj->unk81 = 0;
            obj->unk83 = 0;
            b[0xAD] = 0;
            obj->unkB8 = 0.0f;
            obj->gravity = 4.0f;
        }
    }
    if (D_800BE616 == 0 || obj->interaction_state != 1) {
        obj->unk21C = 0;
    }
    stun = obj->stunned;
    if (stun == 0xFF) {
        return;
    }
    if (stun != 0xFE && (obj->health != 0 || obj->interaction_state != 1)) {
        obj->stunned = stun - 1;
    }
    obj->unk10C -= D_800CC264;
    if (obj->unk28 < 0.2f && (obj->unkF4 & 0x100)) {
        obj->unk10C = 0;
    }
    if (obj->unk10C <= 0) {
        if (obj->unk31C != NULL) {
            ((u8 *)obj->unk31C)[0x7D] = 0;
        }
        obj->unk10C = 0;
        func_1505E874(D_800C3E78, obj);
    }
    if (obj->stunned == 0) {
        obj->xz_velocity = 0.0f;
        obj->unk81 = 0;
        obj->unk78 = obj->unk7A;
        obj->unk76 = obj->unk7A;
        if (b[0xAD] != 0) {
            obj->y_velocity = 0.0f;
            if (obj->interaction_state == 1) {
                func_1506B078();
            }
        } else if (obj->interaction_state == 1) {
            obj->unkF8 &= ~0x8000;
            obj->gravity = 4.0f;
        }
        if (obj->unk238 != 0) {
            obj->unk23A = obj->unk238;
        }
    } else {
        hit = obj->unk10B;
        if (!(hit & 2)) {
            heading = obj->unk76;
            if (hit & 4) {
                heading ^= 0x8000;
            }
            obj->unk80 = 10;
            func_150599C8(obj, 12, heading);
        }
    }
}
