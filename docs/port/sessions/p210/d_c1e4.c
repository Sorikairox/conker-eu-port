s32 func_1506E46C(struct127 *, s32 *, s32);
void func_15060B04(s32 arg0, struct127 *arg1, s32 arg2);
s16 func_1505C140(struct127 *arg0, struct127 *arg1);
u8 func_1505B9C4(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
extern void (*D_80086A34[])(struct127 *, struct127 *, u8 *); /* hit handlers (void/3, tablesig) */

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

/* P210: one hit reaction rule (4 bytes) of the per-type lists D_80086E40[type] (D_8009AA60[type] rules each). */
typedef struct {
    u8 cond;    /* 1: obj faces the attacker (func_1505C140 <= 0x4000), 2: turned away (>= 0x4000), 3: obj stunned,
                 * 4: obj not stunned; other values: always */
    u8 kind;    /* the hit kind the rule is for */
    u8 action;  /* & 0x7F: reaction; 0x80: the rule is for every kind except `kind` */
    u8 param;
} HitRule;

extern u8 D_8009AA60[];
extern HitRule *D_80086E40[];

// object_receive_hit: hit descriptor `idx` of table `descs` from `self` hits object `obj` (number `slot` - 1).
/* The first matching rule of obj's reaction list (type obj->unk239 & 0x7F) may change the hit: actions 0 / 1
 * (attacker on the front / back side) and 2 / 4 pick another descriptor, 5 / 6 / 7 take descriptor `param` of
 * D_8009A6D8 (7 only when the damage reaches obj's health, then obj's health is cleared), 4 / 6 make it harmless
 * (mask 0); 3, 8 (obj catches the attacker), 10, 11, 12, 13 (handler only) handle it here. Rules whose action or
 * condition fails are skipped. Unless handled, func_1505B9C4 applies the hit. Returns `hits` with obj's bit set
 * when the hit landed (or when 8 / 13 handled it). */
s32 func_1505C1E4(struct127 *self, struct127 *obj, void *descs, s32 idx, s32 slot, s32 hits, s32 mask) {
    HitDesc *desc = &((HitDesc *)descs)[idx];
    HitDesc *tbl = descs;   /* tbl[idx] is the descriptor func_1505B9C4 applies */
    u8 kind = desc->kind & 0x7F;
    u8 type = obj->unk239 & 0x7F;
    s32 handled = FALSE;
    HitRule *rule;
    s32 count;
    s32 n;
    u8 action;
    u8 scratch[4]; /* the handler's kind byte; the asm passes an unset stack word and ignores it */

    if (type != 0 && (count = D_8009AA60[type]) > 0) {
        rule = D_80086E40[type];
        for (n = 0; n < count; n++, rule++) {
            if (rule->action & 0x80) {
                if (rule->kind == kind) {
                    continue;
                }
            } else if (rule->kind != kind) {
                continue;
            }
            action = rule->action & 0x7F;
            if (rule->cond == 1 && func_1505C140(self, obj) > 0x4000) {
                action = 0xFF;
            }
            if (rule->cond == 2 && func_1505C140(self, obj) < 0x4000) {
                action = 0xFF;
            }
            if (rule->cond == 3 && obj->stunned == 0) {
                action = 0xFF;
            }
            if (rule->cond == 4 && obj->stunned != 0) {
                action = 0xFF;
            }
            switch (action) {
                case 0:
                case 1: {
                    /* 0: the attacker is in front of obj, 1: behind it */
                    u16 ang = func_1505A630(self->x_position - obj->x_position, obj->z_position - self->z_position, 0);

                    if (action == ((((s32)ang - obj->unk7A + 0x4000) >> 15) & 0xFFFF)) {
                        idx = rule->param;
                    }
                    break;
                }
                case 2:
                    idx = rule->param;
                    break;
                case 3:
                    handled = TRUE;
                    break;
                case 4:
                    if (rule->param != 0xFF) {
                        idx = rule->param;
                    }
                    mask = 0;
                    break;
                case 5:
                    tbl = (HitDesc *)D_8009A6D8 + rule->param - idx;
                    break;
                case 6:
                    tbl = (HitDesc *)D_8009A6D8 + rule->param - idx;
                    mask = 0;
                    break;
                case 7:
                    if ((desc->damage & mask) < obj->health) {
                        continue;
                    }
                    tbl = (HitDesc *)D_8009A6D8 + rule->param - idx;
                    obj->health = 0;
                    break;
                case 8:
                    /* obj catches the attacker */
                    handled = TRUE;
                    obj->unkF4 &= ~0x00040040;
                    hits |= 1 << ((slot - 1) & 0x1F);
                    self->unk108 = slot + 0x7F;
                    self->unk107 = 0x3C;
                    obj->unk1C4 = 0;
                    obj->unk218 = NULL;
                    obj->disable_run = 1;
                    obj->unkD0 = 0;
                    obj->unk232 = rule->param;
                    D_800D1580 = desc->sound;
                    if (desc->sound != 0) {
                        func_1506E5FC();
                    }
                    if (obj->interaction_state == 1) {
                        struct126 *ctl = obj->unk31C;

                        if (ctl->unk4E == 2 && ctl->unk84 == 0) {
                            ctl->pad4F[1] = 30; /* byte 0x50 */
                            obj->unk81 = 0;
                            obj->y_velocity = 50.0f;
                            obj->gravity = 2.0f;
                        }
                    }
                    break;
                case 9:
                    break;
                case 10:
                    if (obj->unk84.uh == 0x283) {
                        obj->unk76 = self->unk7A;
                        obj->xz_velocity = 25.0f;
                        D_800D1580 = 0xFF0102E2;
                        func_1506E5FC();
                        self->unkD0 = 0;
                        self->unk232 = 0xD;
                        self->unk218 = NULL;
                        handled = TRUE;
                    }
                    break;
                case 11:
                    if (8.0f < obj->unk28) {
                        handled = TRUE;
                    }
                    break;
                case 12:
                    if (obj->unk28 == 0.0f) {
                        self->unk2EC = 100;
                        self->unkD0 = 0;
                    }
                    handled = TRUE;
                    break;
                case 13: {
                    /* only the descriptor's handler (and obj's effect unkFC) */
                    u8 handler = desc->handler;
                    s32 effect;

                    D_800D1580 = desc->sound;
                    if (desc->sound != 0) {
                        func_1506E5FC();
                    }
                    D_80086A34[handler](self, obj, scratch);
                    if (obj->unkFC != 0) {
                        effect = obj->unkFC;
                        if (func_1506E46C(self, &effect, 1) != 0) {
                            func_15060B04(effect, obj, 0x5DC0);
                        }
                    }
                    hits |= 1 << ((slot - 1) & 0x1F);
                    handled = TRUE;
                    break;
                }
                default:
                    continue; /* failed condition (0xFF) or no reaction */
            }
            break;
        }
    }
    if (handled) {
        return hits;
    }
    func_1505B9C4(self, obj, (s32)descs, (s32)tbl, idx, slot, mask);
    return hits | (1 << ((slot - 1) & 0x1F));
}
