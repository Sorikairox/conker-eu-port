f32 func_15049AD0(s32 points, s32 segment, f32 t);
f32 sinf(f32);
extern s8 D_800ABA2C[];         /* settings item table: per item label text, type, then (type >= 0) max + 1 choice texts */
extern s8 D_80090180;           /* settings changed */
extern s16 D_800E0EB2;          /* value fade: 0xFF = steady, -0xFF.. = fading in a changed value */
extern s8 D_800E0EB4;           /* the value before the change */
extern s8 D_800E1013;
extern u8 D_800ABC98[];         /* "#" */
extern u8 D_800ABC9C[];         /* "#" */
extern u8 D_800ABCA0[];         /* "%d" */
extern u8 D_800ABCA4[];         /* "%s" */
extern u8 D_800ABCA8[];         /* "%d" */
extern u8 D_800ABCAC[];         /* "%s" */
extern u8 D_800ABCB0[];         /* "%d" */
extern u8 D_800ABCB4[];         /* "%d" */
extern u8 D_800ABCB8[];         /* "%d %s" */
extern u8 D_800ABCC0[];         /* "#" */
extern u8 D_800ABCC4[];         /* "#" */

// settings_list_draw: draws and edits the settings list (28 items, bit i of mask = item i shown; values D_800E1010[i],
// clamped to D_80090210 / D_8009022C[i]). arg1 != 0: the items sit on a rotating ring (Catmull-Rom over 2 columns,
// x 74 / 148 / 222, scrolled by D_800901D8), up / down change the value and left / right move the selection;
// arg1 == 0: a plain column at x 0x94 from y 0x46 (0x22 apart), left / right change the value and up / down move.
// The selection D_800901D4 skips hidden items; a changed value fades in from its old value when arg4 != 0
// (D_800E0EB2 / D_800E0EB4). arg2 != 0 draws the "#" cursor arrows that slide to the selected row
// (D_80090184 / D_80090188). arg3 = alpha.
void func_151E3AE4(s32 mask, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 alpha = arg3;
    s8 fadeIn = arg4;
    MenuState *rec;
    f32 x[32];
    f32 y[32];
    s32 count;
    s32 half;
    s32 step;
    s32 pos;
    s32 i;
    s32 ring;
    f32 t;
    s32 itemAlpha;
    s32 a;
    s8 shownValue;
    s32 offset;
    s8 *item;
    s32 type;
    s32 value;
    s32 drawn;
    s32 cursorRow;
    s32 px;
    s32 py;
    s32 sel;
    s32 oldSel;
    s8 *p;
    s8 old;
    s32 changed;
    s32 forward;
    s32 arrowX;
    s32 arrowY;

    count = 0;
    for (i = 0; i < 0x1C; i++) {
        if ((1 << i) & mask) {
            count++;
        }
    }
    half = count >> 1;
    ring = half;
    if (arg2 != 0 && D_80090188 != 0.0f) {
        ((MenuState *) D_80090174)->input &= ~3;
    }
    pos = 0x46;
    if (arg1 != 0) {
        /* ring layout: column x per slot (148 top, 222 right side going down, 148 bottom, 74 left side going up) */
        a = half;
        if (count >= 4 && (count & 1)) {
            a = half + 1;
        }
        step = 0x82 / (a + 1);
        if (count >= 4) {
            step -= 5;
        }
        i = 0;
        if (count > 0) {
            if (count & 1) {
                i = 1;
                pos = step + 0x46;
                y[1] = (f32) 0x46;
                x[1] = 148.0f;
            }
            for (; i != count; i += 2) {
                y[i + 1] = (f32) pos;
                if (i == 0) {
                    pos += step;
                    x[i + 1] = 148.0f;
                } else if (i < half) {
                    x[i + 1] = 222.0f;
                    pos += step;
                    if (i + 1 != half || (count & 1)) {
                        pos += 0x10;
                    }
                } else if (i == half) {
                    if (count & 1) {
                        x[i + 1] = 222.0f;
                    } else {
                        pos -= step;
                        x[i + 1] = 148.0f;
                    }
                } else {
                    pos = pos - step - 0x10;
                    x[i + 1] = 74.0f;
                }
                y[i + 2] = (f32) pos;
                if (i < half - 1) {
                    x[i + 2] = 222.0f;
                    pos += step;
                    if (i + 2 != half || (count & 1)) {
                        pos += 0x10;
                    }
                } else if (i == half - 1) {
                    if (count & 1) {
                        x[i + 2] = 222.0f;
                    } else {
                        x[i + 2] = 148.0f;
                        pos -= step;
                    }
                } else {
                    pos = pos - step - 0x10;
                    x[i + 2] = 74.0f;
                }
            }
            pos = 0x46;
        }
        /* wrap the ring for the spline */
        x[0] = x[count];
        y[0] = y[count];
        x[count + 1] = x[1];
        y[count + 1] = y[1];
        x[count + 2] = x[2];
        y[count + 2] = y[2];
        t = sinf(D_800901D8 * 3.14159f - 1.570795f) * 0.5f + 0.5f;
        /* ring slot of the first item = number of shown items before the selection */
        ring = 0;
        for (i = 0; i < 0x1C; i++) {
            if (i < D_800901D4 && ((1 << i) & mask)) {
                ring++;
            }
        }
        if (ring >= count) {
            ring = 0;
        }
    }

    if (fadeIn != 0) {
        D_800E0EB2 += 0x5C;
        if (D_800E0EB2 >= 0x100) {
            D_800E0EB2 = 0xFF;
        }
        a = D_800E0EB2;
        if (a < 0) {
            a = -a;
        }
        a = (alpha * a) >> 8;
        if (a >= 0xFE) {
            a = 0xFF;
        }
        if (D_800E0EB2 < 0) {
            shownValue = D_800E0EB4;
        } else {
            shownValue = D_800E1010[D_800901D4];
        }
        itemAlpha = a;
    } else {
        D_800E0EB2 = 0xFF;
        itemAlpha = alpha;
    }

    cursorRow = 0;
    offset = 0;
    drawn = 0;
    for (i = 0; i < 0x1C; i++) {
        item = &D_800ABA2C[offset];
        type = item[1];
        if ((1 << i) & mask) {
            value = D_800E1010[i];
            if (i == D_800901D4) {
                cursorRow = drawn;
            }
            if (arg1 != 0) {
                px = (s32) func_15049AD0((s32) x, ring, t);
                py = (s32) func_15049AD0((s32) y, ring, t);
                ring--;
                if (ring < 0) {
                    ring += count;
                }
            } else {
                py = pos;
                px = 0x94;
                pos += 0x22;
            }
            /* label */
            func_1504332C(0xFF, 0xFF, 0xFF, (u8) itemAlpha);
            func_150432FC(px, py);
            if (item[0] >= 0) {
                func_15042E3C(((s32 *) D_800E1008)[item[0]]);
            } else if (item[0] < -1) {
                func_150432FC(px, py + 9);
                func_15042E3C((s32) D_800ABC98, -item[0]);
                func_150432FC(px, py + 0x16);
            }
            /* value */
            if (i == D_800901D4 && D_800901D8 <= 0.0f) {
                func_1504332C(0xFF, 0xFF, 0xFF, (u8) itemAlpha);
                if (fadeIn != 0) {
                    value = shownValue;
                }
            } else if (fadeIn != 0) {
                func_1504332C(0xFF, 0xFF, 0xFF, alpha);
            } else {
                func_1504332C(0xFF, 0xFF, 0xFF, (alpha >> 2) & 0xFF);
            }
            if (type < 0) {
                if (type < -1) {
                    func_15042E3C((s32) D_800ABC9C, value - type);
                }
            } else {
                switch (type) {
                    case 0x79:
                        break;
                    case 0x7A:
                        if (value == 0) {
                            func_15042E3C((s32) D_800ABCA4, ((s32 *) D_800E1008)[0x73]);
                        } else {
                            func_15042E3C((s32) D_800ABCA8, value);
                        }
                        break;
                    case 0x7B:
                        if (D_800E1013 >= 3) {
                            func_15042E3C((s32) D_800ABCAC, ((s32 *) D_800E1008)[0x2D]);
                        } else {
                            func_15042E3C((s32) D_800ABCB0, value);
                        }
                        break;
                    case 0x7C:
                        func_15042E3C((s32) D_800ABCB4, value * 1000);
                        break;
                    case 0x7D:
                        if (value >= 3) {
                            func_15042E3C((s32) D_800ABCB8, value, ((s32 *) D_800E1008)[0x72]);
                        } else {
                            func_15042E3C(((s32 *) D_800E1008)[0x73]);
                        }
                        break;
                    case 0x7E:
                        func_15042E3C((s32) D_800ABCA0, value);
                        break;
                    case 0x7F:
                        func_15042E3C(((s32 *) D_800E1008)[value != 0]);
                        break;
                    default:
                        func_15042E3C(((s32 *) D_800E1008)[item[1 + value]]);
                        break;
                }
            }
            drawn++;
        }
        /* next item: label + type, plus the choice texts of a list item */
        if (type >= 0x79 && type <= 0x7F) {
            offset += 2;
        } else if (type >= 0) {
            offset += D_8009022C[i] + 2;
        } else {
            offset += 2;
        }
        if (D_800E1010[i] < D_80090210[i]) {
            D_800E1010[i] = D_80090210[i];
            D_80090180 = 1;
        }
        if (D_8009022C[i] < D_800E1010[i]) {
            D_800E1010[i] = D_8009022C[i];
            D_80090180 = 1;
        }
    }

    /* input */
    sel = D_800901D4;
    forward = 1;
    rec = (MenuState *) D_80090174;
    if (D_800E0EB2 != 0xFF) {
        rec->input = 0;
    }
    p = &D_800E1010[sel];
    old = *p;
    oldSel = sel;
    if (D_800901D8 <= 0.0f) {
        changed = 0;
        rec = (MenuState *) D_80090174;
        if (arg1 != 0) {
            if (rec->input & 1) {
                *p = old + 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 2) {
                *p = old - 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 8) {
                D_800901DC = 0.075f;
            } else if (rec->input & 4) {
                sel--;
                p--;
                if (sel < 0) {
                    sel += 0x1C;
                    p += 0x1C;
                }
                forward = 0;
                D_800901DC = -0.075f;
                D_800901D8 = 1.0f;
            }
        } else {
            if (rec->input & 4) {
                *p = old - 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 8) {
                *p = old + 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 2) {
                D_800901DC = 1.0f;
            } else if (rec->input & 1) {
                sel--;
                p--;
                if (sel < 0) {
                    sel += 0x1C;
                    p += 0x1C;
                }
                forward = 0;
                D_800901D8 = 0.0f;
            }
        }
        if (changed != 0 && sel == 2) {
            D_800E1010[3] = 2;
        }
        if (rec->input & 0xF) {
            func_10010F30(0x4FF, 0x4650, 0x40, 0, 0);
        }
        /* values wrap around */
        if (*p < D_80090210[sel]) {
            *p = D_8009022C[sel];
            D_80090180 = 1;
        }
        if (D_8009022C[sel] < *p) {
            *p = D_80090210[sel];
            D_80090180 = 1;
        }
    }
    D_800901D8 += D_800901DC * (f32) D_800BE9E4;
    if (D_800901D8 >= 1.0f) {
        sel++;
        p++;
        if (sel >= 0x1C) {
            sel -= 0x1C;
            p -= 0x1C;
        }
        D_800901DC = 0.0f;
        D_800901D8 = 0.0f;
    } else if (D_800901D8 <= 0.0f) {
        D_800901DC = 0.0f;
        D_800901D8 = 0.0f;
    }
    /* skip hidden items */
    while (forward != 0 && !((1 << sel) & mask)) {
        sel++;
        p++;
        if (sel >= 0x1C) {
            sel -= 0x1C;
            p -= 0x1C;
        }
    }
    while (forward == 0 && !((1 << sel) & mask)) {
        sel--;
        p--;
        if (sel < 0) {
            sel += 0x1C;
            p += 0x1C;
        }
    }
    if (sel == oldSel && old != *p) {
        D_800E0EB2 = -0xFF;
        D_800E0EB4 = old;
    }
    D_800901D4 = sel;

    if (arg2 != 0) {
        /* cursor arrows left and right of the selected row */
        arrowX = (s32) ((100.0f + D_80090188 * (f32) 0) * 0.5f);
        arrowY = (s32) ((f32) (D_80090184 * 0x22 + 0x46) + D_80090188 * (f32) ((cursorRow - D_80090184) * 0x22));
        arrowX = (s32) ((f32) arrowX + 20.0f * sinf(D_80090188 * 3.1415f));
        func_1504332C(0xFF, 0xFF, 0xFF, alpha);
        func_15042D94(arrowX + 0x94, arrowY, 1, (s32) D_800ABCC0, 0x1A);
        func_15042D94(0x94 - arrowX, arrowY, 1, (s32) D_800ABCC4, 0x1A);
        if (cursorRow != D_80090184) {
            D_80090188 += 0.1f * (f32) D_800BE9E4;
            if (D_80090188 >= 1.0f) {
                D_80090184 = cursorRow;
                D_80090188 = 0.0f;
            }
        }
    }
}
