s32 func_15081974(s32 arg0, f32 arg1, f32 arg2, u8 **arg3, s32 arg4, s32 arg5);
void func_1514B30C(f32 *arg0, u8 arg1, s32 arg2);
void func_151DD390(u8 *arg0, u8 arg1, s32 arg2);
void func_15031C1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
// thrown_object_update: per-frame update of a thrown / falling object (kind obj->unk278: 0x1F rolling, spins with
// the frame time D_800BE9E4 and plays its sounds; 0x42 flies along its velocity, faces it, sticks into the ground
// at +25 and hits targets in range (func_15081974 -> func_15055260); 0x4E spins once above 25; 0x35 spins fast and
// breaks on the first move; 0x88 faces its velocity and may be caught (func_1505C7D8)). Common part: physics
// (func_15059C84 / func_1505A770 / func_15058898 collision), water entry at unk118 (slows down), ground contact
// (unk28 <= floor offset: bounce count unk7F, a 0xE ground type destroys it), facing unk40 from unk76, fade-out
// over the last 10 frames of the lifetime unk83 (or after 21..30 bounces), and the rolling kind hits Conker
// (D_800DBFF0) within 30 units.
void func_1505528C(struct127 *obj) {
    f32 x, y, z;
    s32 kind;
    f32 floor;
    s32 moved;
    u8 *target;
    s32 hit;
    f32 pos[3];
    f32 t;
    f32 dx, dy, dz;
    s32 alpha;
    u8 life;
    u8 bounces;

    kind = (u16)obj->unk278;
    moved = 0;
    floor = 0.0f;
    switch (kind) {
    case 0x1F:
        obj->unkB8 += obj->xz_velocity * (f32)D_800BE9E4;
        if (obj->unk2E4 == 1) {
            func_10010344(0x230, obj, 0x7D00, 0x1F4, 0x9C4);
            obj->unk2E4 = 0;
        }
        break;
    case 0x42:
        floor = 25.0f;
        if (obj->gravity != 0.0f && (obj->y_velocity > 0.0f || obj->unk28 > 25.0f)) {
            obj->unkB8 = -func_150484A0(obj->y_velocity, obj->xz_velocity) * 57.295776f;
        }
        hit = func_15081974((s32)obj, 40.0f, 10.0f, &target, 0xF, 0x53);
        if (hit != 0) {
            func_15055260((s32)obj, (s32)target, hit - 1);
            func_15060F28(obj, 1);
            return;
        }
        break;
    case 0x4E:
        floor = 25.0f;
        if (obj->unk28 > 25.0f) {
            obj->unkB8 += (f32)(D_800BE9E4 * 3);
        }
        break;
    case 0x35:
        obj->unkB8 += (f32)(D_800BE9E4 * 16);
        break;
    case 0x88:
        obj->unkB8 = -func_150484A0(obj->y_velocity, obj->xz_velocity) * 57.295776f;
        obj->unkD0 = 0x10;
        if (func_1505C7D8(obj, D_800C3E78) != 0) {
            func_15060F28(obj, 1);
            return;
        }
        break;
    }

    func_15059C84(obj);
    obj->stunned = 1;
    func_1505A770(obj);
    x = obj->x_position;
    y = obj->y_position;
    z = obj->z_position;
    func_15058898(obj, obj->old_y_position);
    if (obj->unk118 != -10000.0f && obj->y_position <= obj->unk118 && obj->unk118 <= obj->old_y_position) {
        /* entered the water this frame */
        obj->unk2E4 = 2;
        obj->gravity = 0.0f;
        obj->y_velocity = -3.0f;
        obj->xz_velocity *= 0.1f;
    } else if (x != obj->x_position || y != obj->y_position || z != obj->z_position) {
        moved = 1;
        if (kind == 0x1F && obj->unk2E4 != 2) {
            func_10010344((func_150ADA20() % 5U) + 0x3A4, obj, 0x7D00, 0x1F4, 0x9C4);
        }
    }
    func_1505B5F8(obj, obj->unk180);
    if (obj->unk28 <= floor) {
        obj->unk7F++;
        moved |= 2;
        if ((obj->unk184 & 0x1F) == 0xE) {
            func_1514B30C(&obj->x_position, 0xFF, 0);
            func_15060F28(obj, 1);
            return;
        }
        if (kind == 0x42) {
            /* stuck in the ground: place it at floor height along its last move */
            D_800D1580 = 0xFF0100B0;
            if (obj->gravity != 0.0f) {
                func_1506E5FC();
            }
            obj->gravity = 0.0f;
            obj->y_velocity = 0.0f;
            obj->xz_velocity = 0.0f;
            dy = obj->y_position - obj->old_y_position;
            obj->y_position = obj->unk180 + floor;
            if (dy != 0.0f) {
                t = (obj->y_position - obj->old_y_position) / dy;
            } else {
                t = 0.0f;
            }
            obj->x_position = obj->old_x_position + (obj->x_position - obj->old_x_position) * t;
            obj->z_position = obj->old_z_position + (obj->z_position - obj->old_z_position) * t;
        } else if (obj->y_position < obj->unk118) {
            obj->gravity = 0.0f;
            obj->y_velocity = 0.0f;
            obj->xz_velocity = 0.0f;
        } else if (obj->y_velocity > 5.0f && kind == 0x1F && obj->unk2E4 != 2) {
            func_10010344(0x39E, obj, 0x7D00, 0x1F4, 0x9C4);
            obj->unk2E4 = 2;
        }
    }
    obj->unk40 = (f32)(obj->unk76 + 0x4000) * 0.005493164f;
    if (moved != 0 && kind == 0x35) {
        func_10010630(0x360, obj, 0x4E20, 0x1F4, 0x9C4);
        if (obj->unk118 < obj->y_position) {
            pos[0] = obj->x_position;
            pos[1] = obj->y_position + 20.0f;
            pos[2] = obj->z_position;
            func_151DD390((u8 *)pos, 0xFF, 1);
        }
        func_15060F28(obj, 1);
        return;
    }
    life = --obj->unk83;
    if (life == 0 || (bounces = obj->unk7F) >= 0x1F) {
        func_15060F28(obj, 1);
        return;
    }
    if (life < 10) {
        alpha = (life * 0xFF) / 10;
    } else {
        alpha = 0xFF;
        if (bounces >= 0x15) {
            alpha = (bounces * -0xFF + 0x1DE2) / 10;
        }
    }
    func_15031C1C((s32)obj, kind, alpha, 0);
    if (kind == 0x1F) {
        dx = D_800DBFF0->unk2F8 - obj->x_position;
        dy = D_800DBFF0->unk2FC - obj->y_position;
        dz = D_800DBFF0->unk300 - obj->z_position;
        if (dx * dx + dy * dy + dz * dz < 900.0f) {
            func_1512D748(D_800DBFF0, 8, 0);
            func_10010F88(0x2E1, 0x6D60, 0, 0, 0, obj->x_position, obj->y_position, obj->z_position, 0x1F4, 0x3E8);
            func_10010A3C(obj);
            func_15060F28(obj, 1);
        }
    }
}
