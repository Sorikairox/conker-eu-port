s32 func_1507F8A0(s32);
s32 func_150803E0(struct127 *);
u8 func_1515999C(u8 *, s16, s16, s16, s16, s16);
u8 *func_15031C4C(u8 *, s32, s32);
extern u8 *D_80086F40[];

/* P64: the idle-chooser state of a player controller, ctl +0x58 (func_1507F2D4 / F640 / F834 / F3B0). */
typedef struct {
    /* 0x0 */ u8  active;     /* ctl +0x58 */
    /* 0x1 */ u8  delay;      /* ctl +0x59 */
    /* 0x2 */ u16 timer;      /* ctl +0x5A: frames idle */
    /* 0x4 */ u8  set;        /* ctl +0x5C: idle set (D_80086F40 index, 0 = none) */
    /* 0x5 */ u8  entry;      /* ctl +0x5D: position inside the set */
    /* 0x6 */ u8  pad6;
    /* 0x7 */ u8  recent[5];  /* ctl +0x5F: last chosen sets, newest first */
    /* 0xC */ u8  mode;       /* ctl +0x64: 0 / 1 / 2 (func_1507F2D4) */
    /* 0xD */ u8  count;      /* ctl +0x65: sets played in this mode */
} IdleState;

/* P64: picks the next idle set. Collects candidate set ids into list[40] (func_1507EF60 adds one id,
 * func_1507EF98 appends the D_80086FC4 group n): a forced set (rec +0x13A / +0x139), the D_800D18C0 & 2
 * request (3), the "bored" set 0xB / 0xC (ctl +0x66 with no character idle, 0xC after 100 frames, which also
 * resets the mode and calls func_1508039C), 0 when hurt (health < 2), held (func_1515999C) or the timer is
 * still below func_1507F8A0(mode). Otherwise func_1507F2D4 updates the mode and a group is chosen: by state /
 * character / level (D_800BE9F0) / D_800D18C0 & 1, else by the mode (0, 1, plus 3 in mode 2 after 4 sets
 * when func_150803E0). func_1507F018 filters the list against the recent sets; a random survivor becomes
 * ctl +0x5C (entry 0) and is pushed onto recent[] (func_1507F238; func_1507F380 first drops it when
 * func_1507F018 says it was already there). */
void func_1507F3B0(void) {
    struct127 *rec = D_800D154C;
    IdleState *st = (IdleState *)((u8 *)rec->unk31C + 0x58);
    struct126 *ctl;
    u8 list[40];
    u8 picked[40];
    s32 n = 0;
    s32 npicked;
    s32 group;
    s32 seen;
    s32 i;

    if (rec->unk13A != 0) {
        if (rec->pad139 <= 0x20) {
            func_1507EF60(list, &n, rec->pad139);
        }
        goto choose;
    }
    if (D_800D18C0 & 2) {
        func_1507EF60(list, &n, 3);
        D_800D18C0 = 0;
        goto choose;
    }
    ctl = rec->unk31C;
    if ((s16)ctl->unk66 != 0 && ctl->unk78 == 0) {
        s32 id = 0xB;
        if (st->timer > 100) {
            ctl->unk66 = 0;
            id = 0xC;
            st->timer = 0;
            st->mode = 0;
            func_1508039C((u8 *)D_800D154C);
        }
        func_1507EF60(list, &n, id);
        goto choose;
    }
    if (rec->health < 2
        || func_1515999C((u8 *)&D_800CC2D0[D_800C3E78], 0, 0, -1, -1, -1) != 0
        || st->timer < func_1507F8A0(st->mode)) {
        func_1507EF60(list, &n, 0);
        goto choose;
    }

    func_1507F2D4();
    rec = D_800D154C;
    group = -1;
    if (rec->unk2F8 & 0x200) {
        group = 2;
    } else if (rec->unk31C->unk78 == 9) {
        group = 5;
    } else if (rec->unk31C->unk78 == 0x23) {
        group = 9;
    } else if (rec->unk31C->unk78 == 0x16) {
        group = 0xA;
    } else if (func_15031C4C((u8 *)rec, 0x17, 0) != NULL) {
        group = 6;
    } else if (D_800BE9F0 == 0x31) {
        group = (D_800D18C0 & 4) ? 8 : 7;
    } else if (D_800D154C->id == 0x96) {
        group = 2;
    } else {
        switch (D_800BE9F0) {
            case 0x0E: case 0x10: case 0x1B: case 0x1C: case 0x1E: case 0x23:
            case 0x26: case 0x28: case 0x2F: case 0x36: case 0x3A:
                group = 2;
                break;
            default:
                if (D_800D18C0 != 0) {
                    if (D_800D18C0 & 1) {
                        group = 4;
                    }
                    D_800D18C0 = 0;
                }
                break;
        }
    }
    if (group != -1) {
        func_1507EF98((s32)list, &n, group);
    } else if (st->mode == 1) {
        func_1507EF98((s32)list, &n, 0);
    } else {
        func_1507EF98((s32)list, &n, 1);
        if (st->mode == 2 && st->count >= 4 && func_150803E0(D_800D154C) != 0) {
            func_1507EF98((s32)list, &n, 3);
        }
    }

choose:
    seen = func_1507F018(list, n, picked, &npicked, st->recent);
    i = 0;
    if (npicked >= 2) {
        i = (u32)func_150ADA20() % (u32)npicked;
    }
    st->entry = 0;
    st->count++;
    st->set = picked[i];
    if (st->mode != 0) {
        st->timer = 0;
    }
    if (seen != 0) {
        func_1507F380(st->set, st->recent);
    }
    func_1507F238(st->set, st->recent);
}

