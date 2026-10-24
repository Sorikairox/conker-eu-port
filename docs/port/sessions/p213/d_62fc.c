// object_carried_update: P213: per-frame update of object `obj` while it is held by the object in slot unk13D - 100
/* (port P209: void, one argument). Sets 30 frames of immunity, copies the carrier's unk180, keeps the height in
 * unk1CC, gravity 4.5, no fall speed; the hold timer unk21C counts up by D_800BE9A0 to 30. Per type (0x57, 0x8C
 * after 10 frames - else nothing more; 0xA8 / 0xA9; 0x5E with offset 16) the carrier's animation unk84 picks the
 * column (0..2) of the reaction row and the carrier's grab is synced (func_15064D5C); other types use row 13
 * column 0. The reaction row comes from func_1505E7CC (0x24 for 0x57 with carrier anim 0x114, else 13); a
 * swimming player carrier (state 1, in_water) uses column 1 when the row has one. The object is moved towards
 * the point `offset` (unk10F, 204 for type 0x13) in front of the carrier along its facing unk7A + unk13E << 8,
 * by unk21C / 50 per frame (1 with D_800BE9B4) until 20 frames, then 0.8; a carrier with a model (unk1D4) lifts
 * it to the model's height + unk10C / 100 (ramped over 14 frames) after 7 frames. Carrier state 0x15: row 0x39,
 * same facing, 10 below the carrier, no forward speed, turn speed unkC4 eases to the carrier's; column 1 when
 * unk28 > 100 after 21 frames, else no animation offset. Starts the row's animation (func_1505E650) and marks
 * the holder in unk65 (slot + 1, unk101 bit 2) for the typed cases, else clears unk65. */
void func_15064D5C(s32, s32);
void func_150562FC(struct127 *obj) {
    u8 slot;
    s32 typed;
    f32 anim_offset;
    struct127 *holder;
    u16 anim;
    u32 col;
    u32 row;
    u8 *rows;
    u8 *cell;
    f32 weight;
    f32 offset;
    f32 dz;
    f32 dy;
    f32 lift;
    u16 t;
    u8 id;

    slot = obj->unk13D - 100;
    typed = 0;
    anim_offset = 5.0f;
    obj->immune = 30;
    holder = &D_800CC2D0[slot];
    obj->unk180 = holder->unk180;
    obj->unk1CC = obj->y_position;
    obj->gravity = 4.5f;
    obj->y_velocity = 0.0f;
    if (obj->unk21C < 30) {
        obj->unk21C += D_800BE9A0;
    }
    col = 0;
    row = 13;
    id = obj->id;
    if (id == 0x57) {
        obj->unk5C = 9;
        if (obj->unk21C < 10) {
            return;
        }
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x114) {
            row = 0x24;
        }
        if (anim == 0x116) {
            col = 1;
        }
        if (anim == 0x117) {
            col = 2;
        }
        func_15064D5C(slot, D_800C3E78);
    } else if (id == 0x8C) {
        obj->unk5C = 4;
        if (obj->unk21C < 10) {
            return;
        }
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x1A6) {
            col = 1;
        }
        if (anim == 0x1A7) {
            col = 2;
        }
        func_15064D5C(slot, D_800C3E78);
    } else if (id == 0xA8 || id == 0xA9) {
        obj->unk5C = 9;
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x1B0) {
            col = 1;
        }
        if (anim == 0x1B1) {
            col = 2;
        }
    } else if (id == 0x5E) {
        obj->unk5C = 9;
        anim_offset = 16.0f;
        anim = holder->unk84.uh;
        typed = 1;
        if (anim == 0x286) {
            col = 2;
        }
        if (anim == 0x27E) {
            col = 1;
        }
    }
    row = func_1505E7CC(row, obj);
    rows = *(u8 **)((u8 *)D_800D1588[obj->id] - 8);
    if (holder->interaction_state == 1 && holder->in_water != 0) {
        obj->unk5C = 4;
        typed = 1;
        if (*(u16 *)(rows + row * 0x18 + 0xE) != 0) {
            col = 1;
        }
    }
    t = obj->unk21C;
    if (t < 20) {
        weight = (f32)t / 50.0f;
        if (D_800BE9B4 != 0) {
            weight = 1.0f;
        }
    } else {
        weight = 0.8f;
    }
    offset = obj->unk10F;
    func_150599C8(obj, 0x10, holder->unk7A + (obj->unk13E << 8));
    if (holder->unk1D4 != NULL) {
        lift = obj->unk10C / 100;
        if (holder->interaction_state != 0x15) {
            t = obj->unk21C;
            if (t >= 7) {
                obj->y_position = *(s16 *)((u8 *)holder->unk1D4 + 0x240 + 0x1A);
                if (t < 14) {
                    lift = (t / 14.0f) * lift;
                }
                obj->y_position = obj->y_position + lift;
            }
            if (obj->id == 0xE) {
                obj->unkC4 = 0.0f;
            } else if (obj->id == 0x13) {
                offset = 204.0f;
                obj->unkC4 = 0.0f;
            }
        }
    }
    if (holder->interaction_state == 0x15) {
        row = func_1505E7CC(0x39, obj);
        obj->unk7A = holder->unk7A;
        obj->y_position = holder->y_position - 10.0f;
        if (obj->unk28 > 100.0f && obj->unk21C >= 21) {
            col = 1;
        } else {
            anim_offset = 0.0f;
        }
        offset = 0.0f;
        obj->xz_velocity = 0.0f;
        obj->unkC4 = obj->unkC4 + (holder->unkC4 - obj->unkC4) * 0.12f;
    }
    func_1505A184(holder->unk7A, offset, 0.0f, &offset, &dz, &dy);
    obj->x_position = obj->x_position + ((holder->x_position + offset) - obj->x_position) * weight;
    obj->z_position = obj->z_position + ((holder->z_position + dz) - obj->z_position) * weight;
    cell = rows + row * 0x18 + col * 4;
    func_1505E650(obj, *(u16 *)(cell + 0xA), cell[0xC] / 100.0f, anim_offset, 0.0f, 0.0f, 0);
    if (typed) {
        obj->unk65 = slot + 1;
        obj->unk101 |= 4;
    } else {
        obj->unk65 = 0;
    }
}
