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

/* P64: advances the current idle set (ctl +0x5C) to its next entry. Returns 1 when a new set must be chosen
 * (no set, or the set's list ends with 0: then set and entry are cleared), else 0. */
s32 func_1507F834(void) {
    IdleState *st = (IdleState *)((u8 *)D_800D154C->unk31C + 0x58);

    if (st->set == 0) {
        return 1;
    }
    st->entry++;
    if (D_80086F40[st->set][st->entry] == 0) {
        st->set = 0;
        st->entry = 0;
        return 1;
    }
    return 0;
}
