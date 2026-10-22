s32 func_1507CD64(struct127 *, s32);
void func_1507F3B0(void);
s32 func_1507F834(void);
extern u8 *D_80086F40[];
extern u8 D_8009BC80[][8];

/* P60: idle animation of the current player record D_800D154C (D_800C3E78 = its index, players only; not when
 * D_800C35EA == 1 or the record's +5 is 4). Marks the controller's idle state (ctl +0x58 = 1); while the idle
 * delay ctl +0x59 runs it counts down. Out of health: func_1507CD64(rec, 0). Else the run / jump locks and the
 * turn are reset and an idle animation is chosen: ctl +0x17 (random 0x4F / 0x4D), a per-character idle
 * (ctl +0x78, below), carried items / states (ctl +0x1B2, +0x4E, +0x8, +0x1A, +0x32), held by another record
 * (func_1507F92C), the cutscene idle 0xF (D_800BE616), else the idle sets D_80086F40 / D_8009BC80 (u16 anim,
 * speed / 100, blend / 10, delay) chosen by ctl +0x5C / +0x5D after func_1507F834 / func_1507F3B0. */
void func_1507F640(void) {
    struct127 *rec;
    struct126 *ctl;
    u8 *e;
    s32 anim;
    s32 ch;
    f32 speed = 1.0f;
    f32 blend = 4.0f;

    if (D_800C35EA == 1) {
        return;
    }
    rec = D_800D154C;
    if (rec->unk5 == 4 || D_800C3E78 >= D_8008FD8C) {
        return;
    }
    ctl = rec->unk31C;
    ctl->unk58 = 1;
    if ((D_800D154C->unk2F8 & 0x20) || D_800D154C->unk31C->unk120 != 0) {
        return;
    }
    if (ctl->unk59 > 0) {
        ctl->unk59--;
        ctl->unk5A = 0;
        return;
    }
    rec = D_800D154C;
    if (rec->health == 0) {
        func_1507CD64(rec, 0);
        return;
    }
    if (rec->disable_run >= 0xFA) {
        D_800D154C->disable_run = 0;
    }
    if (D_800D154C->disable_jump == 0xFF) {
        D_800D154C->disable_jump = 0;
    }
    D_800D154C->unk83 = 0;
    D_800D154C->unkAA = 0;
    D_800D154C->unk76 = D_800D154C->unk7A;
    D_800D154C->unk100 &= ~1;
    D_800D154C->unk2F8 &= ~7;

    rec = D_800D154C;
    ctl = rec->unk31C;
    if (ctl->pad17[0] != 0) {
        anim = (func_150ADA20() & 3) ? 0x4D : 0x4F;
        func_1505E650(D_800D154C, anim, 1.0f, 4.0f, 0.0f, 0.0f, 0);
        return;
    }
    ch = ctl->unk78;
    switch (ch) {
        case 0x02: case 0x13: anim = 0x3E; break;
        case 0x38: anim = 0x1DF; break;
        case 0x39: anim = 0x1EA; break;
        case 0x37: anim = 0x1F3; break;
        case 0x3B: anim = 0x221; break;
        case 0x26: anim = 0x177; break;
        case 0x3A: anim = 0x1FA; break;
        case 0x25: anim = 0xD8; break;
        case 0x2D: case 0x2E: anim = 0x1AF; break;
        case 0x15: anim = 0xE2; break;
        case 0x0C: anim = 0xBD; break;
        case 0x14: case 0x3F: anim = 0xF9; break;
        case 0x22: anim = 0x15A; break;
        case 0x21: anim = 0x122; break;
        case 0x19: case 0x40: anim = 0x10F; break;
        case 0x12: anim = 0x10A; break;
        case 0x18: case 0x41: anim = 0xC5; break;
        case 0x24: anim = 0x153; break;
        default: anim = -1; break;
    }
    if (ctl->unk1B2 != 0 && ch == 0x16) {
        anim = 0x2C5;
    }
    if (ctl->unk4E == 2) {
        anim = 5;
    }
    if (ctl->unk8 != 0) {
        blend = 8.0f;
        speed = 1.5f;
        anim = 0xAB;
    }
    if (ctl->pad17[3] != 0) {
        anim = 0x63;
        blend = 8.0f;
    }
    if (ctl->unk32 & 2) {
        anim = 0x6B;
        blend = 8.0f;
    } else if (ctl->unk32 & 1) {
        anim = 0xAF;
        blend = 8.0f;
    }
    if (anim != -1) {
        func_1505E650(rec, anim, speed, blend, 0.0f, 0.0f, 0);
        return;
    }
    if (rec->unk13C >= 100) {
        func_1507F92C(rec);
        return;
    }
    if (D_800BE616 != 0 && ch != 0x23 && ch != 0x16 && ch != 9) {
        func_1505E650(rec, 0xF, 1.0f, 3.0f, 0.0f, 0.0f, 0);
        return;
    }

    if (func_1507F834() != 0) {
        rec = D_800D154C;
        if (rec->unk31C->unk198 != 0 && ctl->unk5C == 0) {
            switch (rec->unk31C->unk78) {
                case 0x03: anim = 0x2C; break;
                case 0x09: anim = 0x7F; break;
                case 0x16: anim = 0xBD; break;
                case 0x23: anim = 0x165; break;
                default:
                    func_1507F92C(rec);
                    return;
            }
            func_1505E650(rec, anim, 1.0f, 4.0f, 0.0f, 0.0f, 0);
            return;
        }
        func_1507F3B0();
    }

    e = D_8009BC80[D_80086F40[ctl->unk5C][ctl->unk5D]];
    if (D_80086F40[ctl->unk5C][ctl->unk5D] == 0) {
        rec = D_800D154C;
        switch (rec->unk31C->unk78) {
            case 0x09: anim = 0x3A; break;
            case 0x23: anim = 0x42; break;
            case 0x16: anim = 0x44; break;
            default:
                if (rec->health == 1) {
                    anim = 0xE;
                } else if (rec->unk31C->pad17[3] != 0) {
                    anim = 0x25;
                }
                break;
        }
        if (anim != -1) {
            e = D_8009BC80[anim];
        }
    }
    func_1505E650(D_800D154C, *(u16 *) e, e[2] * 0.01f, e[3] * 0.1f, 0.0f, 0.0f, 0);
    ctl->unk58 = 1;
    ctl->unk59 = e[4];
}
