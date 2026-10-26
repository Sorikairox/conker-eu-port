extern u8 D_800E0FE8[];    /* per-racer input byte (bit 7 = trigger), consumed here */
extern s8 D_80087670[];    /* by difficulty D_800E1000: AI timer limit */
extern s8 D_80087680[];    /* by difficulty: AI timer restart value (negated) */
extern s16 D_80087664[];   /* by difficulty: boost time that forces a re-plan (-1 = never) */
extern s8 D_80087688[];    /* by difficulty: chance (percent) to keep the old steering offsets */
s32 rail_band_for_height(f32);
s32 rail_racer_steer(s32, s32, s32, s32, s32, s32);
void rail_events_assign_nodes(void);
s32 rail_pickup_slot_release(s32, s32);
void rail_racer_send_event_14(s32, s32);
void rail_racer_send_event_61(s32, s32);
// rail_racers_update: script command 6 (event_action_rail; its result is read by the scripts). For every racer i of the rail
// state D_800D27D0 (count +0x10): racers in the mask +0x14 (or newly seen ones, which are added to the mask +0x18) run
// their timers by the frame time D_800BE9E4, take their input byte D_800E0FE8[i] (bit 7 cleared), refresh their rail
// node (+0x9C) and activity (+0x39C); a racer that is not started (+0x35C) and becomes active (or is new, or its object
// has unk2FD set) is started: its team count moves, rail_pickup_slot_release(i, 1) resets its route, and bit i goes into the
// result. Racers with a target (+0x31C) steer through rail_racer_steer with smoothed s8 offsets (+0x1725 / +0x1735) and
// pick a new random offset when their AI timer runs out; state 5 of the object's +0x232 places a boost point near it
// (and its target). Racers neither in the mask nor new are deactivated (active 0, node -1). Afterwards the frame scale
// +0x16B4 is set and, in race mode 0xB9, each player's +0x1574 counter is drawn (/50) on its viewport.
// Returns the bit mask of the racers started this call.
s32 rail_racers_update(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 mask = *(s32 *) (rail + 0x14);
    s32 seen = *(s32 *) (rail + 0x18);
    s32 n = *(s32 *) (rail + 0x10);
    s32 *flash = (s32 *) (rail + 0x1C);
    s32 *node = (s32 *) (rail + 0x9C);
    s32 *state = (s32 *) (rail + 0x19C);
    s32 *boost = (s32 *) (rail + 0x21C);
    s32 *cooldown = (s32 *) (rail + 0x25C);
    s32 *aiTimer = (s32 *) (rail + 0x29C);
    s32 *target = (s32 *) (rail + 0x31C);
    s32 *started = (s32 *) (rail + 0x35C);
    s32 *active = (s32 *) (rail + 0x39C);
    s32 *input = (s32 *) (rail + 0x3DC);
    s32 *timerC = (s32 *) (rail + 0x41C);
    s32 *teamCount = (s32 *) (rail + 0xDDC);
    s32 *team = (s32 *) (rail + 0xE64);
    s32 *counter = (s32 *) (rail + 0x1574);
    s32 result = 0;
    s32 i;
    s32 bit;
    s32 isNew;
    s32 myTeam;
    s32 prevAi;
    s32 replan;
    s32 wrapped;
    s32 lvl;
    s32 limit;
    s32 st;
    s32 k;
    u8 *obj;
    u8 *other;
    u8 *view;
    s32 half;
    u16 flags;

    for (i = 0; i < n; i++) {
        bit = 1 << i;
        flash[i] = 0;
        isNew = FALSE;
        if (!(mask & bit)) {
            if (!(seen & bit)) {
                isNew = TRUE;
            }
            seen |= bit;
            if (!isNew) {
                active[i] = 0;
                node[i] = -1;
                continue;
            }
        }
        obj = (u8 *) &g_objects[i];
        myTeam = team[i];
        if (myTeam != 0 && *(s16 *) ((u8 *) D_800D27D0 + 0x16BC) == 0xB9) {
            obj[0x1E4] = 1;
        }
        prevAi = aiTimer[i];
        boost[i] += D_800BE9E4;
        aiTimer[i] += D_800BE9E4;
        cooldown[i] -= D_800BE9E4;
        if (cooldown[i] <= 0) {
            cooldown[i] = 0;
        }
        timerC[i] -= D_800BE9E4;
        if (timerC[i] <= 0) {
            timerC[i] = 0;
        }
        counter[i] -= D_800BE9E4;
        if (counter[i] < 0) {
            counter[i] = 0;
        }
        if (state[i] == 3 && (cooldown[i] & 0x1F) >= 0x1D) {
            rail_racer_send_event_61(i, 0x8000);
        }
        input[i] = D_800E0FE8[i];
        D_800E0FE8[i] &= 0x7F;
        ((s32 *) ((u8 *) D_800D27D0 + 0x4DC))[i] = (*(u8 **) (obj + 0x31C))[0x19A];
        active[i] = player_stat_get(i, 4);
        node[i] = rail_band_for_height(*(f32 *) (obj + 0x18));

        if (active[i] != 0 && !isNew && obj[0x2FD] == 0) {
            started[i] = 0;
        } else if (started[i] == 0) {
            /* the racer starts */
            if (obj[0x20F] != 0xFF) {
                ((s32 *) ((u8 *) D_800D27D0 + 0x59C))[i] = obj[0x20F];
            } else {
                ((s32 *) ((u8 *) D_800D27D0 + 0x59C))[i] = -1;
            }
            started[i] = 1;
            cooldown[i] = 0;
            state[i] = 0;
            ((s32 *) ((u8 *) D_800D27D0 + 0x5C))[i] = 1;
            ((s32 *) ((u8 *) D_800D27D0 + 0x11C))[i] = -1;
            teamCount[myTeam]--;
            k = input[i] & 0x7F;
            if (k < n && myTeam != team[k]) {
                teamCount[team[k]]++;
            }
            if (*(s16 *) ((u8 *) D_800D27D0 + 0x16BC) != 0xB9) {
                ((s32 *) ((u8 *) D_800D27D0 + 0xFF0))[i] = 0;
                rail_pickup_slot_release(i, 1);
            }
            result |= bit;
        }

        /* steering towards the target (racer index + 2) */
        wrapped = TRUE;
        if (target[i] != 0 && *(s16 *) ((u8 *) D_800D27D0 + 0x16BC) != 0xB8) {
            replan = FALSE;
            if (state[i] != 1 && boost[i] < 0x1E) {
                st = obj[0x232];
                obj[0x222] = target[i] - 2;
                if (st != 4 && st != 5) {
                    rail_racer_send_event_14(i, 4);
                }
                if (st == 4) {
                    boost[i] = 0;
                }
                if (st == 5) {
                    /* boost point: random spot within 50 of the racer, 40 above it, pulled halfway to the target */
                    boost[i] = 0x1E;
                    ((f32 *) ((u8 *) D_800D27D0 + 0x1868))[i] = ((f32 *) &D_80087698)[D_800E1000];
                    ((f32 *) ((u8 *) D_800D27D0 + 0x17A8))[i] = random_float() * 50.0f + *(f32 *) (obj + 0x14);
                    ((f32 *) ((u8 *) D_800D27D0 + 0x17E8))[i] = *(f32 *) (obj + 0x18) + 40.0f;
                    ((f32 *) ((u8 *) D_800D27D0 + 0x1828))[i] = random_float() * 50.0f + *(f32 *) (obj + 0x1C);
                    if (target[i] - 2 >= 2) {
                        other = (u8 *) &g_objects[target[i] - 2];
                        ((f32 *) ((u8 *) D_800D27D0 + 0x17A8))[i] +=
                            (*(f32 *) (other + 0x14) - *(f32 *) (obj + 0x14)) * 0.5f;
                        ((f32 *) ((u8 *) D_800D27D0 + 0x1828))[i] +=
                            (*(f32 *) (other + 0x1C) - *(f32 *) (obj + 0x1C)) * 0.5f;
                    }
                }
            }
            wrapped = FALSE;
            lvl = D_800E1000;
            limit = 0;
            if (D_80087670[lvl] < aiTimer[i]) {
                aiTimer[i] = 0;
                prevAi = -1;
            }
            /* the AI timer has just come round (negative before, not any more) */
            if (aiTimer[i] >= 0 && prevAi < 0) {
                limit = 1;
            }
            if (D_80087664[D_800E1000] != -1 && boost[i] >= D_80087664[D_800E1000]) {
                replan = TRUE;
            }
            rail = (u8 *) D_800D27D0;
            rail[0x1725 + i] += (s8) (((s8) rail[0x1705 + i] - (s8) rail[0x1725 + i]) >> 2);
            rail = (u8 *) D_800D27D0;
            rail[0x1735 + i] += (s8) (((s8) rail[0x1715 + i] - (s8) rail[0x1735 + i]) >> 2);
            rail = (u8 *) D_800D27D0;
            if (rail_racer_steer(i, target[i] - 2, limit, replan, (s8) rail[0x1725 + i], (s8) rail[0x1735 + i]) != 0
                && state[i] != 1) {
                boost[i] = 0;
            }
            if (aiTimer[i] == 0) {
                /* new random steering offsets */
                ((s8 *) D_800D27D0)[0x1705 + i] = 0;
                ((s8 *) D_800D27D0)[0x1715 + i] = 0;
                if (D_80087688[D_800E1000] < (s32) (random_float() * 100.0f)) {
                    if (0.5f < random_float()) {
                        ((s8 *) D_800D27D0)[0x1705 + i] = -50;
                    } else {
                        ((s8 *) D_800D27D0)[0x1705 + i] = 50;
                    }
                    if (0.5f < random_float()) {
                        ((s8 *) D_800D27D0)[0x1715 + i] = 50;
                    } else {
                        ((s8 *) D_800D27D0)[0x1715 + i] = 0;
                    }
                }
            }
        }
        if (wrapped && *(s16 *) ((u8 *) D_800D27D0 + 0x16BC) != 0xB8) {
            aiTimer[i] = -D_80087680[D_800E1000];
        }
        flags = *(u16 *) (obj + 0x22C);
        *(u16 *) (obj + 0x22C) = flags & ~0x200;
        if ((flags & 0x200) || (input[i] & 0x80)) {
            state[i] = 0;
            flash[i] = 1;
        }
        if ((*(u8 **) (obj + 0x31C))[0x1AC] != 0) {
            cooldown[i] = 20;
        }
    }
    rail = (u8 *) D_800D27D0;
    *(s32 *) (rail + 0x18) = seen;
    if (D_800BE9E4 != 0) {
        *(f32 *) ((u8 *) D_800D27D0 + 0x16B4) = D_800BE9E4;
    } else {
        *(f32 *) ((u8 *) D_800D27D0 + 0x16B4) = 1.0f;
    }
    rail_events_assign_nodes();
    if (*(s16 *) ((u8 *) D_800D27D0 + 0x16BC) == 0xB9) {
        /* each player's counter, centred on its viewport */
        view = *(u8 **) &D_800BE628;
        half = (s32) (*(f32 *) (view + 0x30) - *(f32 *) (view + 0x2C)) >> 1;
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        obj = (u8 *) g_objects;
        for (i = 0; i <= D_80082FA0; i++, obj += 0x32C) {
            if (obj[0x128] == 0) {
                view = *(u8 **) &D_800BE628 + i * 0x180;
                text_printf_at((s32) (*(f32 *) (view + 0x2C) + (f32) half), (s32) (*(f32 *) (view + 0x24) + 6.0f), 1,
                              (s32) "%d", counter[i] / 50);
            }
        }
    }
    return result;
}
