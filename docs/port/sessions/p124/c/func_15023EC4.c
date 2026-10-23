extern s32 D_800C3AA8;
extern s32 D_eu_800C3A60;
extern s32 D_800C39D0;
extern s32 D_800C3A68;

/* an 8-byte scene event: s8 type, u8 delta time (0: same time as the previous event), s16 id (type 0 with delta 0:
 * absolute time), s8 b4, s8 b5, s16 w6 */
#define EV_MATCH(ev) ((s8) (ev)[0] == type && (useId == 0 || (useId == 1 && id == *(s16 *) ((ev) + 2))) && \
                      (useB4 == 0 || (useB4 == 1 && b4 == (s8) (ev)[4])))

// scene_event_find_around: on the player's track list (D_800C3AA8[player][track], D_800C39F8 entries after the
// 0x20-byte header) finds the last matching event at or before `now` (*prev, *prevTime) and the first one after it
// (*next, *nextTime, default the scene end D_eu_800C3A60[player]); type / optional id / optional b4 must match. Times
// are track ticks (60 per second) converted to and from frames (50). Inside a run of same-time events the split
// point is the scene limit (D_800C39D0[player] while the scene runs, else D_800C3A68), as in the asm.
void func_15023EC4(u8 **prev, u8 **next, s32 *prevTime, s32 *nextTime, s32 track, s32 type, s32 useId, s32 id,
                   s32 useB4, s32 b4, s32 now, s32 player) {
    u8 *list;
    u8 *ev;
    s32 t;
    s32 limit;
    s32 time;
    u32 n;
    u8 d;

    if (prev != NULL) {
        *prev = NULL;
    }
    *next = NULL;
    if (prevTime != NULL) {
        *prevTime = 0;
    }
    t = now * 60 / 50;
    *nextTime = (&D_eu_800C3A60)[player];
    if ((&D_800C39D0)[player] < (&D_eu_800C3A60)[player]) {
        limit = (&D_800C39D0)[player] * 60 / 50;
    } else {
        limit = D_800C3A68;
    }
    list = ((u8 **) &D_800C3AA8)[player * 30 + track];
    if (list == NULL) {
        return;
    }
    n = D_800C39F8[player][track];
    time = *(s16 *) (list + 2);
    for (ev = list + 0x20; (u32) ((ev - list) >> 3) < n; ev += 8) {
        d = ev[1];
        if (d == 0 && (s8) ev[0] == 0) {
            time = *(s16 *) (ev + 2);
            continue;
        }
        if (time <= t && EV_MATCH(ev)) {
            if (prev != NULL) {
                *prev = ev;
            }
            if (prevTime != NULL) {
                *prevTime = time * 50 / 60;
            }
        }
        if (t < time && EV_MATCH(ev)) {
            *next = ev;
            *nextTime = time * 50 / 60;
            return;
        }
        d = ev[1];
        while (d == 0) {
            if ((s8) ev[0] == 0) {
                time = *(s16 *) (ev + 2);
                break;
            }
            ev += 8;
            if ((u32) ((ev - list) >> 3) >= n) {
                d = ev[1];
                break;
            }
            if (time <= limit) {
                if (EV_MATCH(ev)) {
                    if (prev != NULL) {
                        *prev = ev;
                    }
                    if (prevTime != NULL) {
                        *prevTime = time * 50 / 60;
                    }
                }
            } else if (EV_MATCH(ev)) {
                *next = ev;
                *nextTime = time * 50 / 60;
                return;
            }
            d = ev[1];
        }
        time += d;
    }
}
#undef EV_MATCH
