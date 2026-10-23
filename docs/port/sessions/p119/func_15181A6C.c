extern f32 D_800DDDC8;   /* [4] per player: HUD lens zoom (1 = none) */
extern f32 D_800DDDD8;   /* [4] per player: zoom rate per frame step */
extern u8 D_800DDE20;    /* [4] per player: scripted zoom (driven by the object's +0x31C state +0x120) */
extern u8 D_800DDE3C;    /* [4] per player: lens state 1..4 (0 = off) */
extern u8 D_800DE1A0[];  /* per player: wobble timer */
extern u8 D_800DE1A4[];  /* per player: wobble angle */
extern u16 D_800DE1B0[]; /* per player: hold timer of lens state 3 */
extern u8 D_800BE9B4;
f32 func_15048A40(u8);
void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_1517FD84(s32 project, f32 x, f32 y, f32 z, s32 player);

/* hud_lens_update: per frame (func_15019130 path) for every player: zoom D_800DDDC8[p] += rate D_800DDDD8[p] * step
 * (D_800BE9E4). Scripted zoom (D_800DDE20[p]) follows the player object's +0x31C record state +0x120 (no record:
 * zoom 1): 3 zooms in to the rest zoom (0.8 one player, 0.9 split screen) -> 4 (wobble 30 frames); 4 wobbles
 * sin(angle) * 0.01 (fading over the last 30 frames) around the rest zoom -> 5 (holds it); 6 zooms in at 0.009 to
 * 0.965 -> 7 (+0x124 = 30); 8 zooms out at 0.004 to 1 -> 9. Otherwise, with the lens on (D_800DDE3C[p]), its centre
 * D_800DE218[p] eases (factor 0.05, 1 with D_800BE9B4; at most 15 / 11.25 per frame) to the projection
 * (func_1517FD84) of a point 40 * y_scale above the object (its joint matrix +0x1D4, +0x300 when +0x00 == 1, else
 * its position); states: 1 zooming in to 0.9 -> 2 (wobble, angle running backwards) -> 3 (hold 50) -> 4 zooming
 * out at 0.009 -> 0 at zoom 0. Lens off: a non-zero rate runs the zoom up to 1 / down to 0 and stops there. */
void func_15181A6C(void) {
    static const f32 restZoom[4] = { 0.8f, 0.9f, 0.9f, 0.9f };
    static const f32 nearZoom[4] = { 0.965f, 0.965f, 0.965f, 0.965f };
    s32 p;
    f32 *zoom;
    f32 *rate;
    u8 *lens;
    u8 *rec;
    struct127 *obj;
    f32 amp;
    f32 px;
    f32 py;
    f32 pz;
    f32 ox;
    f32 oy;
    f32 dx;
    f32 dy;
    f32 k;
    u8 *mtx;

    for (p = 0; p <= D_80082FA0; p++) {
        zoom = &(&D_800DDDC8)[p];
        rate = &(&D_800DDDD8)[p];
        lens = &(&D_800DDE3C)[p];
        if ((&D_800DDE20)[p] != 0) {
            obj = &D_800CC2D0[p];
            *zoom += *rate * (f32) D_800BE9E4;
            rec = (u8 *) obj->unk31C;
            if (rec == NULL) {
                *zoom = 1.0f;
            } else if (rec[0x120] == 3) {
                if (restZoom[D_80082FA0] <= *zoom) {
                    *zoom = restZoom[D_80082FA0];
                    ((u8 *) obj->unk31C)[0x120] = 4;
                    D_800DE1A0[p] = 30;
                    D_800DE1A4[p] = 0;
                }
            } else if (rec[0x120] == 4) {
                if (D_800DE1A0[p] != 0) {
                    D_800DE1A0[p] = (D_800DE1A0[p] < D_800BE9E4) ? 0 : D_800DE1A0[p] - D_800BE9E4;
                    D_800DE1A4[p] += D_800BE9E4 * 20;
                    amp = (D_800DE1A0[p] < 30) ? D_800DE1A0[p] * 0.01f / 30.0f : 0.01f;
                    *zoom = func_15048A40(D_800DE1A4[p]) * amp + restZoom[D_80082FA0];
                } else {
                    *zoom = restZoom[D_80082FA0];
                    ((u8 *) obj->unk31C)[0x120] = 5;
                }
            } else if (rec[0x120] == 5) {
                *zoom = restZoom[D_80082FA0];
            } else if (rec[0x120] == 6) {
                *rate = 0.009f;
                if (nearZoom[D_80082FA0] <= *zoom) {
                    *zoom = nearZoom[D_80082FA0];
                    ((u8 *) obj->unk31C)[0x120] = 7;
                    *(u16 *) ((u8 *) obj->unk31C + 0x124) = 30;
                    *rate = 0.0f;
                }
            } else if (rec[0x120] == 8) {
                *rate = 0.004f;
                if (1.0f <= *zoom) {
                    *zoom = 1.0f;
                    ((u8 *) obj->unk31C)[0x120] = 9;
                }
            }
        } else if (*lens != 0) {
            obj = &D_800CC2D0[p];
            *zoom += *rate * (f32) D_800BE9E4;
            if (obj->unk1D4 != NULL) {
                mtx = (u8 *) obj->unk1D4;
                if (obj->interaction_state == 1) {
                    mtx += 0x300;
                }
                func_150A7E40((f32 (*)[4]) mtx, 0.0f, obj->y_scale * 40.0f, 0.0f, &px, &py, &pz);
            } else {
                px = obj->x_position;
                py = obj->y_position;
                pz = obj->z_position;
            }
            ox = D_800DE218[p][0];
            oy = D_800DE218[p][1];
            func_1517FD84(0, px, py, pz, p);
            px = D_800DE218[p][0];
            py = D_800DE218[p][1];
            k = (D_800BE9B4 != 0) ? 1.0f : 0.05f;
            dx = px - ox;
            if (fabsf(dx) > 15.0f) {
                dx = ((dx < 0.0f) ? -1 : 1) * 15.0f;
                ox = px - dx;
            }
            dy = py - oy;
            if (fabsf(dy) > 11.25f) {
                dy = ((dy < 0.0f) ? -1 : 1) * 11.25f;
                oy = py - dy;
            }
            D_800DE218[p][0] = ox + dx * k;
            D_800DE218[p][1] = oy + dy * k;
            if (*lens == 1) {
                if (*zoom <= 0.9f) {
                    D_800DE1A0[p] = 30;
                    *zoom = 0.9f;
                    *rate = 0.0f;
                    *lens = 2;
                }
            } else if (*lens == 2) {
                if (D_800DE1A0[p] != 0) {
                    D_800DE1A0[p] = (D_800DE1A0[p] < D_800BE9E4) ? 0 : D_800DE1A0[p] - D_800BE9E4;
                    D_800DE1A4[p] -= D_800BE9E4 * 20;
                    amp = (D_800DE1A0[p] < 30) ? D_800DE1A0[p] * 0.01f / 30.0f : 0.01f;
                    *zoom = func_15048A40(D_800DE1A4[p]) * amp + 0.9f;
                } else {
                    *zoom = 0.9f;
                    *lens = 3;
                    D_800DE1B0[p] = 50;
                }
            } else if (*lens == 3) {
                if (D_800BE9E4 < D_800DE1B0[p]) {
                    D_800DE1B0[p] -= D_800BE9E4;
                } else {
                    *lens = 4;
                    *rate = -0.009f;
                }
            } else if (*zoom <= 0.0f) {
                *lens = 0;
                *zoom = 0.0f;
            }
        } else if (*rate != 0.0f) {
            if (*rate > 0.0f) {
                if (*zoom >= 1.0f) {
                    *rate = 0.0f;
                    *zoom = 1.0f;
                }
            } else if (*zoom <= 0.0f) {
                *rate = 0.0f;
                *zoom = 0.0f;
            }
            *zoom += *rate * (f32) D_800BE9E4;
        }
    }
}
