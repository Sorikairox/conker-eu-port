void func_151E67A0(struct127 *, struct127 *, u8);
void func_151AE814(u8 *);
s32 func_1506E46C(struct127 *, s32 *, s32);
f32 func_1506AD30(struct127 *, f32, s32);
extern void (*D_80086A34[])(struct127 *, struct127 *, u8 *); /* hit handlers (void/3, tablesig) */
extern f32 D_800CC690;
extern f32 D_800CC694;
extern f32 D_800CC698;

/* P210: one hit descriptor (0x28 bytes): the attack tables of func_1505C1A4 (indexed by the attack number) and
 * D_8009A6D8. Fields 0x09..0x0E are the attack's hit volume (func_1505C7D8's AttackBox). */
typedef struct {
    /* 0x00 */ u8  kind;      /* & 0x7F: hit kind; 0x80: the entry's own kind wins over the base entry's */
    /* 0x01 */ u8  pad1[3];
    /* 0x04 */ s32 sound;     /* effect / sound id (func_1506E46C), 0 = none */
    /* 0x08 */ u8  handler;   /* index into D_80086A34; 0 = use the base entry's */
    /* 0x09 */ u8  pad9[6];
    /* 0x0F */ u8  damage;    /* low bits (masked by the caller): health taken; 0x20 flag, 0x40 keep the angle */
    /* 0x10 */ u8  push;      /* high byte added to the attacker's moving angle */
    /* 0x11 */ u8  pad11[3];
    /* 0x14 */ f32 xz_speed;
    /* 0x18 */ f32 y_speed;
    /* 0x1C */ f32 gravity;
    /* 0x20 */ u8  unk20;     /* -> obj->unk109 */
    /* 0x21 */ u8  pad21;
    /* 0x22 */ u8  immune;    /* 0x80: obj->immune = & 0x3F */
    /* 0x23 */ u8  pad23;
    /* 0x24 */ u16 flags;
    /* 0x26 */ u8  pad26[2];
} HitDesc;

// object_apply_hit: applies hit descriptor `idx` from attacker `self` to object `obj` (number `slot` - 1).
/* `base_tbl` is the attacker's own table, `cur_tbl` the one in effect (func_1505C1E4 may redirect it into
 * D_8009A6D8). Sets the knock-back (angle from the attacker, speeds, gravity), takes `damage & mask` health,
 * makes a ridden player drop off (and the carrier let go of it), runs the descriptor's handler (not for kind
 * 0x27), reports the hit (func_151E67A0 in multiplayer, two func_15169070 events), plays the sound and sets the
 * hit state of `obj` (stun 0xFE, func_1505E7CC / func_1505E874 reaction, flags in unk10B). Returns the base
 * entry's byte 0x22 (unused by the callers). */
u8 func_1505B9C4(struct127 *self, struct127 *obj, s32 base_tbl, s32 cur_tbl, u8 idx, s32 slot, u8 mask) {
    HitDesc *base = &((HitDesc *)base_tbl)[idx];
    HitDesc *cur = &((HitDesc *)cur_tbl)[idx];
    struct {
        struct127 *obj;
        u8 uid;
    } ev;
    u8 kind;
    u8 dmg;
    u8 handler;

    if (cur->kind & 0x80) {
        kind = cur->kind & 0x7F;
    } else {
        kind = base->kind & 0x7F;
    }
    obj->unk10B = 0;
    if ((base->flags & 1) && obj->stunned != 0) {
        mask = 0;
    }
    if (!(cur->damage & 0x40)) {
        obj->unk76 = (cur->push << 8) + self->unk76;
        if (base->flags & 0x10) {
            obj->unk76 = func_1505A630(obj->x_position - self->x_position, self->z_position - obj->z_position, 0);
        }
        if (self->id == 0x44) {
            obj->unk76 = 0;
        }
    }
    if ((cur->damage | base->damage) & 0x20) {
        obj->unk10B |= 2;
    }
    obj->unk3A = 0;
    obj->unk109 = cur->unk20;
    obj->y_velocity = cur->y_speed;
    obj->xz_velocity = cur->xz_speed;
    obj->unk100 &= 0xD6;
    obj->gravity = cur->gravity;
    dmg = cur->damage & mask;
    if (dmg < obj->health) {
        obj->health -= dmg;
    } else {
        obj->health = 0;
    }

    if (obj->interaction_state == 1) {
        /* a player: run its drop-off with obj as the current object, then clear its riding state */
        struct127 *saved = D_800D154C;
        u8 savedNum = D_800C3E78;
        s32 num = ((s32)obj - (s32)D_800CC2D0) / 0x32C;
        struct126 *ctl;

        D_800D154C = obj;
        D_800C3E78 = num;
        ctl = D_800CC2D0[(u8)num].unk31C;
        if (ctl->unk4E != 2) {
            ctl->unk4E = 0;
        }
        func_1506AD30(obj, 800.0f, 1);
        D_800D154C = saved;
        D_800C3E78 = savedNum;
        obj->unkF8 &= ~0x01008000;
        obj->unk31C->unk95 = 0;
        obj->unk31C->unk6B = 0;
        if (obj->unk31C->pad98[0] != 0) {
            func_151AE814((u8 *)obj);
        }
        obj->unk31C->unk54 = 0;
        obj->unk137 = 0;
        if (obj->unk65 != 0) {
            /* carried by object unk65 - 1: ids 0x8A / 0x23 only let go when the hit is hard enough */
            struct127 *carrier = &D_800CC2D0[(u8)(obj->unk65 - 1)];
            u8 id = carrier->id;

            if ((id != 0x8A && id != 0x23) || obj->health == 0 || (base->flags & 2)
                || (D_800BE616 != 0 && (30.0f < obj->y_velocity || 110.0f < obj->xz_velocity))) {
                s32 state = (id == 0x8A) ? 1 : 0;

                if (id == 0x23) {
                    state = 10;
                }
                if (id == 0xC) {
                    state = 15;
                }
                if (state != 0) {
                    carrier->unk232 = state;
                    carrier->unk218 = NULL;
                }
                carrier->unk2FC = 0;
                carrier->unk13C = 0;
                obj->unk239 = 0;
                obj->unk65 = 0;
            }
        }
    }

    handler = cur->handler;
    if (handler == 0) {
        handler = base->handler;
    }
    if (kind != 0x27) {
        D_80086A34[handler](self, obj, &kind);
    }
    if (D_800BE616 != 0) {
        func_151E67A0((self->unk124 != 0) ? &D_800CC2D0[self->unk124 - 1] : self, obj, kind);
    }
    ev.obj = self;
    ev.uid = self->unique_id;
    func_15169070(0, 0x68, (s32)&ev, 2);
    ev.obj = obj;
    ev.uid = obj->unique_id;
    func_15169070(0, 0x68, (s32)&ev, 2);

    if (base->sound != 0) {
        D_800D1580 = base->sound;
        if (func_1506E46C(obj, &D_800D1580, 0) != 0) {
            func_10010630(D_800D1582, obj, 0x6D60, 0x12C, 0x708);
        }
    } else if (cur->sound != 0) {
        D_800D1580 = cur->sound;
        if (func_1506E46C(obj, &D_800D1580, 0) != 0) {
            func_10010630(D_800D1582, obj, 0x6D60, 0x12C, 0x708);
        }
    }

    self->unk107 = 0x3C;
    if (D_800BE616 == 0 || obj->interaction_state != 1) {
        obj->unk21C = 0;
        if (base->flags & 0x100) {
            obj->unk218 = NULL;
        }
    }
    obj->unkD0 = 0;
    if (self->unk124 != 0) {
        obj->unk10A = self->unk124 + 0x7F;
    } else {
        obj->unk10A = D_800C3E78 | 0x80;
    }
    self->unk108 = (slot - 1) | 0x80;

    if (kind != 0x27) {
        if ((base->flags & 0x40) && obj->interaction_state == 1) {
            /* player hit by a player: halfword 0x46 of the attacker's controller */
            *(s16 *)((u8 *)D_800CC2D0[slot - 1].unk31C + 0x46) = 8000;
        } else {
            if (obj->unk23B != 0) {
                kind = obj->unk23B;
            }
            obj->stunned = 0xFE;
            obj->unk105 = 0;
            obj->unk106 = func_1505E7CC(kind, obj);
            obj->unk84.uh = 0xFFFF;
            func_1505E874(slot - 1, obj);
            if (base->flags & 0x200) {
                obj->unk10B |= 0x20;
            }
            if (0.0f < obj->y_velocity) {
                obj->unk28 += 0.1f;
            }
            if (base->flags & 8) {
                obj->unk10B |= 0x40;
                D_800CC690 = self->x_position;
                D_800CC694 = self->z_position;
                D_800CC698 = self->y_position;
            }
        }
        if (base->flags & 2) {
            obj->unk10B |= 0x80;
        }
    }
    if ((base->flags & 0x400) || (cur->flags & 0x400)) {
        obj->unk10B |= 4;
    }
    if (base->immune & 0x80) {
        obj->immune = base->immune & 0x3F;
    }
    return base->immune;
}
