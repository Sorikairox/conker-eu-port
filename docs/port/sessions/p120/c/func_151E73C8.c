s32 func_150871B8(s32 id);
s32 func_1508712C(s32 point, f32 *x, f32 *y, f32 *z);
f32 func_15049AD0(s32 points, s32 segment, f32 t);
void func_1000D96C(s32 sound, s32 prevSound, s32 arg2);
u8 *func_151149AC(u8 id);
f32 sinf(f32);
extern u8 D_800902F0[];         /* menu 0: carousel stop -> path point id (6 stops) */
extern f32 D_800902F8[];        /* menu 0: zoom speed per stop */
extern u8 D_80090338[];         /* menu 1: carousel stop -> path point id (8 stops) */
extern f32 D_80090340[];        /* menu 1: zoom speed per stop */
extern u16 D_800ABD04[][2];     /* menu 0: sound per stop: [0] accept, [1] back */
extern u16 D_800ABD1C[][2];     /* menu 1 */
extern f32 D_eu_80090310[];     /* menu 0: per-page zoom damping (scaled by D_80090170) */
extern f32 D_80090170;
extern s8 D_80090328[];         /* menu 0: per-page zoom percent that shows the page objects */
extern s8 D_80090330[];         /* menu 0: per-page zoom percent that hides them again */
extern u8 D_80090360[][6];      /* menu 0: 2 world objects (ids) per title page, 0xFF = none */
extern u8 D_800AB950[];         /* menu 1: carousel stop -> main menu page */
extern u8 D_800E0EC7;           /* last menu sound */

// menu_camera_update: the title / main menu camera (object behaviour of the menu camera, arg0 = camera index into
// D_800DBFF0). It is the carousel: left / right (input 4 / 8) slide the camera to the previous / next stop
// (rec->x0 runs 1 -> 0 or 0 -> 1 at rec->x4 per tick, rec->x2B is the target stop), accept (0x10) zooms in towards the
// stop (rec->fade 0 -> 1 at rec->xC, the zoom speed of the stop; the handler shows the page from fade 0.5), back
// (0x20) zooms out. A full zoom into stop 0 toggles title <-> main menu (rec->menu) and restarts at fade 0.99 going
// back out. The eye moves along a path of world points: from the base point (0 / 0x10) to the stop's point and
// on through the point graph D_800D2778 (5 links per 16-byte node, never back to the previous node), with a
// Catmull-Rom spline (func_15049AD0) when the path has 4+ points, linear otherwise; when not zoomed the look-at
// point follows the carousel between the previous, current and next stops. rec->x10 * (x14, x18, x1C) is a decaying
// offset used when the main menu camera jumps to the "back" stop 4 (rec->x2A modes 1 / 2 / 3). Writes
// rec->titlePage (the page shown: the stop, +1 past the slide midpoint; main menu through D_800AB950) and x2D,
// and the visibility (+0x80) of the page's world objects and of objects 0xF6 / 0xF7 / 0xF8 (+0x6E).
void func_151E73C8(s32 arg0) {
    MenuState *rec;
    struct108 *cam;
    s32 base;
    s32 stops;
    u8 *stopPoints;
    f32 *zoomSpeed;
    u16 (*sounds)[2];
    f32 slide;
    f32 zoom;
    f32 rawZoom;
    s8 ids[16];
    f32 x[16];
    f32 y[16];
    f32 z[16];
    u8 *node;
    u8 *cur;
    u8 next;
    s32 count;
    s32 i;
    s32 k;
    s32 segment;
    f32 t;
    f32 bx, by, bz;
    f32 px, py, pz;
    f32 qx, qy, qz;
    s32 jump;
    u8 *obj;
    u8 *objB;

    cam = &D_800DBFF0[arg0];
    if (((MenuState *) D_80090174)->menu == 0) {
        base = 0;
        stops = 6;
        stopPoints = D_800902F0;
        zoomSpeed = D_800902F8;
        sounds = D_800ABD04;
    } else {
        base = 0x10;
        stops = 8;
        stopPoints = D_80090338;
        zoomSpeed = D_80090340;
        sounds = D_800ABD1C;
    }
    func_1508712C(func_150871B8(base), &cam->unk2F8, &cam->unk2FC, &cam->unk300);

    rec = (MenuState *) D_80090174;
    if (rec->x4 != 0.0f) {
        /* sliding to the neighbouring stop */
        rec->x0 += rec->x4 * (f32) D_800BE9E4;
        if (rec->x0 <= 0.0f) {
            rec->x0 = 0.0f;
            rec->x4 = 0.0f;
        }
        if (rec->x0 >= 1.0f) {
            rec->x0 = 0.0f;
            rec->x4 = 0.0f;
            rec->x2B++;
            if (rec->x2B >= stops) {
                rec->x2B -= stops;
            }
        }
    } else if (rec->xC != 0.0f || rec->fade != 0.0f) {
        /* zoomed in or zooming: back zooms out, accept zooms in */
        if ((rec->input & 0x20) && (rec->menu == 0 || rec->x2B != 0)) {
            rec->xC = -zoomSpeed[rec->x2B];
            func_1000D96C(sounds[rec->x2B][1], D_800E0EC7, 0);
            D_800E0EC7 = sounds[rec->x2B][1];
        }
        if (rec->x2A != 0 && rec->menu == 1 && rec->x2B == 0) {
            if (rec->input & 0x20) {
                rec->xC = zoomSpeed[rec->x2B];
            }
        } else if (rec->input & 0x10) {
            rec->xC = zoomSpeed[rec->x2B];
        }
        rec->fade += rec->xC * (f32) D_800BE9E4;
        if (rec->fade >= 1.0f) {
            rec->fade = 1.0f;
            rec->xC = 0.0f;
        } else if (rec->fade < 0.0f) {
            rec->fade = 0.0f;
            rec->xC = 0.0f;
            if (rec->titlePage == 0 && rec->menu == 1 && rec->x44 != 0) {
                rec->x43 = 1;
                rec->x44 = 0;
            }
        }
    } else if (rec->input & 0x10) {
        /* at rest: accept starts the zoom */
        rec->xC = zoomSpeed[rec->x2B];
        func_1000D96C(sounds[rec->x2B][0], D_800E0EC7, 0);
        D_800E0EC7 = sounds[rec->x2B][0];
    } else {
        /* at rest: left goes back one stop (sliding 1 -> 0), right / x43 starts the slide to the next */
        if (rec->input & 4) {
            rec->x2B--;
            rec->x0 = 1.0f;
            rec->x4 = -0.05f;
            if (rec->x2B < 0) {
                rec->x2B += stops;
            }
        }
        if ((rec->input & 8) || rec->x43 != 0) {
            rec->x4 = 0.05f;
        }
        rec->x43 = 0;
        if (rec->x2B < 0) {
            rec->x2B += stops;
        }
        if (rec->x2B >= stops) {
            rec->x2B -= stops;
        }
    }

    rawZoom = rec->fade;
    if (rec->menu == 0) {
        rawZoom *= 1.0f - D_eu_80090310[rec->titlePage] * D_80090170;
    } else if (rec->titlePage != 0) {
        rawZoom *= 0.6f;
    }
    slide = sinf(rec->x0 * 3.14159f - 1.570795f) * 0.5f + 0.5f;
    zoom = sinf(rawZoom * 3.14159f - 1.570795f) * 0.5f + 0.5f;

    if (((MenuState *) D_80090174)->menu == 0) {
        /* the title page's world objects appear / disappear at the page's zoom percentages */
        for (i = 0; i < 2; i++) {
            if (D_80090360[i][rec->titlePage] != 0xFF) {
                obj = func_151149AC(D_80090360[i][rec->titlePage]);
                if (obj != NULL) {
                    rec = (MenuState *) D_80090174;
                    if (rec->xC > 0.0f || D_80090170 < 1.0f) {
                        if (D_80090328[rec->titlePage] < (s32) (rawZoom * 100.0f)) {
                            *(s32 *) (obj + 0x80) = 1;
                        }
                    } else if (rec->xC < 0.0f) {
                        if (D_80090330[rec->titlePage] >= (s32) (rawZoom * 100.0f)) {
                            *(s32 *) (obj + 0x80) = 0;
                        }
                    }
                }
            }
        }
    }

    cam->unk3D0->unk25C |= 0x200;
    cam->unk3D0->y_position = 1000.0f;

    if (rawZoom > 0.0f) {
        /* zooming: path from the base point through the stop's point along the point graph */
        ids[0] = func_150871B8(base);
        ids[1] = func_150871B8(stopPoints[((MenuState *) D_80090174)->x2B]);
        count = 1;
        node = (u8 *) D_800D2778 + ids[1] * 16;
        while (node != NULL) {
            cur = node;
            node = NULL;
            for (k = 0; k < 5; k++) {
                next = cur[9 + k];
                if (next != 0xFF && next != ids[count - 1]) {
                    ids[count + 1] = next;
                    count++;
                    k = 5;
                    node = (u8 *) D_800D2778 + next * 16;
                }
            }
        }
        count++;
        if (count >= 4) {
            t = zoom * ((f32) count - 2.0f);
            segment = (s32) t;
            t -= (f32) segment;
            if (segment >= count - 2) {
                segment--;
                t = 1.0f;
            }
            for (i = 0; i < count; i++) {
                func_1508712C(ids[i], &x[i + 1], &y[i + 1], &z[i + 1]);
            }
            /* end points mirrored for the spline */
            x[0] = x[1] - (x[2] - x[1]);
            y[0] = y[1] - (y[2] - y[1]);
            z[0] = z[1] - (z[2] - z[1]);
            x[count + 1] = (x[count - 1] - x[count]) + x[count];
            y[count + 1] = (y[count - 1] - y[count]) + y[count];
            z[count + 1] = (z[count - 1] - z[count]) + z[count];
            cam->unk2F8 = func_15049AD0((s32) x, segment, t);
            cam->unk2FC = func_15049AD0((s32) y, segment, t);
            cam->unk300 = func_15049AD0((s32) z, segment, t);
            cam->unk2A4 = func_15049AD0((s32) x, segment + 1, t);
            cam->unk2A8 = func_15049AD0((s32) y, segment + 1, t);
            *(f32 *) &cam->unk2AC = func_15049AD0((s32) z, segment + 1, t);
        } else {
            func_1508712C(ids[0], &x[0], &y[0], &z[0]);
            func_1508712C(ids[1], &x[1], &y[1], &z[1]);
            if (count == 3) {
                func_1508712C(ids[2], &x[2], &y[2], &z[2]);
            } else {
                x[2] = (x[1] - x[0]) + x[1];
                y[2] = (y[1] - y[0]) + y[1];
                z[2] = (z[1] - z[0]) + z[1];
            }
            cam->unk2F8 = (x[1] - x[0]) * zoom + x[0];
            cam->unk2FC = (y[1] - y[0]) * zoom + y[0];
            cam->unk300 = (z[1] - z[0]) * zoom + z[0];
            cam->unk2A4 = (x[2] - x[1]) * zoom + x[1];
            cam->unk2A8 = (y[2] - y[1]) * zoom + y[1];
            *(f32 *) &cam->unk2AC = (z[2] - z[1]) * zoom + z[1];
        }
    } else {
        /* not zoomed: look at the carousel (previous, current, next, next + 1 stops) */
        k = ((MenuState *) D_80090174)->x2B - 1;
        if (k < 0) {
            k += stops;
        }
        for (i = 0; i < 4; i++) {
            func_1508712C(func_150871B8(stopPoints[k]), &x[i], &y[i], &z[i]);
            k++;
            if (k >= stops) {
                k -= stops;
            }
        }
        cam->unk2A4 = func_15049AD0((s32) x, 0, slide);
        cam->unk2A8 = func_15049AD0((s32) y, 0, slide);
        *(f32 *) &cam->unk2AC = func_15049AD0((s32) z, 0, slide);
    }

    rec = (MenuState *) D_80090174;
    if (rec->x2A != 0) {
        /* look away from the eye: mirror the look-at point through it */
        cam->unk2A4 = cam->unk2F8 + (cam->unk2F8 - cam->unk2A4);
        cam->unk2A8 = cam->unk2FC + (cam->unk2FC - cam->unk2A8);
        *(f32 *) &cam->unk2AC = cam->unk300 + (cam->unk300 - *(f32 *) &cam->unk2AC);
    }
    cam->unk2A4 += rec->x10 * rec->x14;
    cam->unk2A8 += rec->x10 * rec->x18;
    *(f32 *) &cam->unk2AC += rec->x10 * rec->x1C;
    if (rec->x2A != 3) {
        rec->x10 *= 0.85f;
    } else {
        rec->x10 = -((0.25f - rec->fade) * 4.0f);
    }

    jump = 0;
    if (rec->menu == 1) {
        /* main menu: back at stop 0 jumps to stop 4 (x2A 1 -> 2 -> 3), with a decaying look-at offset */
        func_1508712C(func_150871B8(base), &bx, &by, &bz);
        k = rec->x2B;
        if (k >= stops) {
            k = 0;
        }
        func_1508712C(func_150871B8(stopPoints[k]), &px, &py, &pz);
        px -= bx;
        py -= by;
        pz -= bz;
        if (rec->x2A != 0) {
            px = -px;
            py = -py;
            pz = -pz;
        }
        if (rec->fade == 0.0f && (rec->input & 0x20) && rec->x10 < 0.01f && rec->x4 == 0.0f) {
            rec->x2B = 0;
            if (rec->x2D >= 2 && rec->x2D < 7) {
                rec->x2A = 2;
            }
            jump = 1;
            rec->xC = zoomSpeed[rec->x2B];
            func_1000D96C(sounds[rec->x2B][0], D_800E0EC7, 0);
            D_800E0EC7 = sounds[rec->x2B][0];
        }
        if (rec->fade < 0.25f && rec->x2A == 1) {
            rec->x2B = 4;
            jump = 2;
            rec->x2A = 0;
        }
        if (rec->fade == 0.0f && rec->x2A == 3) {
            rec->x2B = 4;
            rec->x2A = 0;
            rec->x10 = 0.0f;
        }
        if (jump != 0) {
            func_1508712C(func_150871B8(stopPoints[rec->x2B]), &qx, &qy, &qz);
            qx -= bx;
            qy -= by;
            qz -= bz;
            if (rec->x2A != 0) {
                qx = -qx;
                qy = -qy;
                qz = -qz;
            }
            rec->x10 = 1.0f;
            rec->x14 = px - qx;
            rec->x18 = py - qy;
            rec->x1C = pz - qz;
        }
        if (jump == 2) {
            rec->x10 = 0.0f;
            rec->x2B = 0;
            rec->x2A = 3;
        }
    }

    if (rec->fade >= 1.0f && rec->x2B == 0) {
        /* fully zoomed into stop 0: switch title <-> main menu and zoom back out */
        rec->menu = 1 - rec->menu;
        rec->fade = 0.99f;
        if (rec->menu != 0) {
            rec->xC = -D_80090340[0];
        } else {
            rec->xC = -D_800902F8[0];
        }
        if (rec->menu != 0) {
            rec->x2A = 1;
        } else {
            rec->x2A = 0;
        }
    }
    rec->titlePage = rec->x2B;
    if (rec->x0 > 0.5f) {
        rec->titlePage++;
    }
    if (rec->titlePage < 0) {
        rec->titlePage += stops;
    }
    if (rec->titlePage >= stops) {
        rec->titlePage -= stops;
    }
    rec->x2D = rec->titlePage;
    if (rec->menu == 1) {
        rec->titlePage = D_800AB950[rec->titlePage];
    }

    cam->unk2BC = cam->unk2A4;
    cam->unk2C0 = cam->unk2A8;
    cam->unk2C4 = *(f32 *) &cam->unk2AC;
    cam->unk390 = 0.0f;
    cam->unk1A4 = 20.0f;
    cam->unk19C = 20.0f;
    cam->unk1A8 = 15.0f;
    cam->unk1A0 = 15.0f;

    obj = func_151149AC(0xF8);
    if (obj != NULL) {
        obj[0x6E] = 1;
    }
    obj = func_151149AC(0xF6);
    objB = func_151149AC(0xF7);
    if (obj != NULL && objB != NULL) {
        if (((MenuState *) D_80090174)->menu == 0) {
            obj[0x6E] = 0;
            objB[0x6E] = 1;
        } else {
            obj[0x6E] = 1;
            objB[0x6E] = 0;
        }
    }
}
