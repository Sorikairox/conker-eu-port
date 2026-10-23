u8 *func_15034174(u8 *arg0);

// object_catch_player: lands / catches the player record D_800CC2D0[obj->unk124] on object obj (lift, platform,
// carrier). Unless `force`, it only fires when the player is below obj's top (obj y + height * obj->y_scale) and
// falling. Then: obj->unk13C = player + 100, optional sound event D_800D1580 = sound (func_1506E5FC), the player
// remembers its y (+0x1CC) and faces obj's angle, its state block mode is cleared. Objects in state 0x20 stop both
// vertical speeds and align the player to obj's angle (+0x40 in degrees); type 0x48 objects carrying partner 0x7A
// (func_15034174) start the ride animation 5 / 0x79 and call func_15060F28(obj, 0) at the end, other objects squash
// (y_scale 0.75) and snap the player to obj's y (state 1, 0x81 in level 6). Other states hand the player over
// (unk65 = D_800C3E78 + 1, unk5C = anim, unk101 |= flags). Finally immune = immune, unk239 = arg7, obj->unk232 =
// timer; `reset` calls func_1506160C(player, 1, 0, 0, 0) and sets player flag 0x40. The asm returns nothing; the f32
// return type matches the callers' prototypes (0).
f32 func_15052F9C(struct127 *obj, f32 height, s32 anim, s32 flags, s32 reset, s32 timer, s32 immune, s32 arg7,
                  s32 force, s32 sound) {
    struct127 *pl;
    s32 partner;
    s32 ride;
    s32 state;
    u16 angle;

    ride = 0;
    partner = -1;
    if (obj->id == 0x48) {
        u8 *other = func_15034174((u8 *) obj);
        if (other != NULL) {
            partner = other[6];
        }
    }
    pl = &D_800CC2D0[obj->unk124];
    if (force != 0 ||
        (pl->y_position < obj->y_position + height * obj->y_scale && pl->y_velocity < 0.0f)) {
        obj->unk13C = obj->unk124 + 100;
        if (sound != 0) {
            D_800D1580 = sound;
            func_1506E5FC();
        }
        pl->unk1CC = pl->y_position;
        pl->unk76 = obj->unk7A;
        pl->unk31C->unk30 = 0;
        if (obj->interaction_state == 0x20) {
            pl->y_velocity = 0.0f;
            obj->y_velocity = 0.0f;
            if (obj->id == 0x48) {
                state = 2;
                if (partner == 0x7A) {
                    obj->unk65 = obj->unk124 + 1;
                    obj->unk5C = anim;
                    obj->unk101 |= flags;
                    func_1505E650(pl, 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
                    func_15083568(pl, 0x79, 1.0f, 0);
                    ride = 1;
                }
            } else {
                obj->y_scale = 0.75f;
                pl->y_position = obj->y_position;
                state = 1;
                if (D_800BE9F0 == 6) {
                    state = 0x81;
                }
            }
            angle = obj->unk7A;
            pl->unk76 = angle;
            pl->unk78 = angle;
            pl->unk7A = angle;
            pl->unk40 = (s16) (angle + 0x4000) * 0.0054931640625f; /* 360 / 65536 */
            pl->unk31C->unk4E = state;
            pl->unk83 = 0;
            pl->disable_run = 0;
        } else {
            pl->unk65 = D_800C3E78 + 1;
            pl->unk5C = anim;
            pl->disable_run = 0;
            pl->unk101 |= flags;
        }
        pl->immune = immune;
        pl->unk239 = arg7;
        pl->unk31C->unk27 = 0;
        obj->unk218 = NULL;
        obj->unk232 = timer;
        if (reset != 0) {
            func_1506160C(pl, 1, 0, 0, 0);
            pl->unk101 |= 0x40;
        }
    }
    if (ride != 0) {
        func_15060F28(obj, 0);
    }
    return 0.0f;
}
