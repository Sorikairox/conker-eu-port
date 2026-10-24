/* P188: one face of the sky box (D_800A3170, 16 bytes): texture size in texels and two opposite corners; the axis
 * the face is perpendicular to is the one whose coordinate the corners share */
typedef struct {
    u16 w, h;
    s16 a[3];
    s16 b[3];
} SkyFace;
/* P188: a texture load the vertex builder func_1511127C queued (filled through its pointer argument) */
typedef struct {
    s32 addr; /* texture (palette at addr + tlut_offset[fmt]) */
    s32 fmt;  /* 0 = 8-bit CI (256 colours), 1 = 4-bit CI (16 colours) */
} SkyLoad;
extern SkyFace D_800A3170[];
extern s32 D_800DC2B8[];
extern s32 D_800DC2E0;
/* (one line: tools/port/protocheck.py reads single-line prototypes) */
Gfx *func_1511127C(Gfx *gdl, s32 *vtx, s32 tex, s32 arg3, s32 arg4, s32 w, s32 h, s32 arg7, s32 arg8, f32 x, f32 y, f32 z, s32 axis, f32 (*view)[4], s32 dist, s32 *count, s32 *first, SkyLoad *loads, s32 *last_fmt, u8 *arg19, u8 *arg20, s16 *tlut_offset, u8 *tlut_count, u8 *tile, s32 face);

/*
 * sky_box_draw: camera callback (D_80089578[], same signature as func_15110948) that draws the textured sky box of
 * the current player D_80082FA4. The position arguments are unused. Steps:
 *  - texture on, func_1501A490 (D_80083336) / func_1501A680; on level 60 (and on level 19 in mode D_800C35EA == 1
 *    with D_800C3A08 == 1 or 2) the viewport is first cleared to black through func_15110AC4 (the camera record
 *    D_800BE628[p] +0x24..0x30, as func_15110948);
 *  - on level 65 the pitch is turned by -119 degrees (wrapped into [0, 360));
 *  - pipe sync, combiner: plain texture when the sky colour (D_800B0DF0 +5..7) is white, else texture * env colour;
 *    other modes, the 4-bit / 8-bit tile descriptors;
 *  - view matrix: func_1511084C(yaw, pitch, roll) times the camera matrix (+0xBC) into the frame's Mtx
 *    D_800DC2E0[p * 2 + D_800BE9C0], D_80089810 as the projection, perspective normalisation (+0xB8);
 *  - faces `first`..`last - 1` (0..4; 4..4 on level 25; 0..5 on level 12): faces 0..3 (the sides, every 90 degrees
 *    of pitch) only when the pitch is within the field of view (95 degrees in mode D_80082FA0 == 1, else 80) of the
 *    face, faces 4 / 5 (down / up) by the yaw, face 5 only from distance `dist` >= 300. func_1511127C builds each
 *    face's quads into the frame's vertex buffer D_800DC2B8[p * 2 + D_800BE9C0] and queues the texture loads (the
 *    face's textures D_8008955C[sky +9][face, 0 for face 5]);
 *  - one G_VTX for all `count` vertices, then per quad (4 vertices): load its texture block and palette (tile
 *    changes only when the format does) and two triangles.
 */
Gfx *func_15112074(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 dist) {
    u8 tile[2];        /* {0, 1} */
    u8 tlut_count[2];  /* {0xFF, 0x0F} */
    s16 tlut_offset[2]; /* {0x800, 0x400} */
    u8 arg20[2];       /* {1, 2} */
    u8 arg19[2];       /* {1, 4} */
    f32 fov;
    u8 col[3];
    s32 last_fmt;
    SkyLoad loads[4];
    s32 first_vtx;
    s32 count;
    s32 vtx;
    f32 view[4][4];
    f32 m[4][4];
    s32 *texs;
    s32 i, last, axis, face, k, fmt;
    SkyFace *f;
    u8 *cam;
    u8 *sky;

    /* P188: the asm copies these from .data initialisers (D_8008958C..9C); set element-wise here because an
     * aggregate initialiser would put a .data section in the NM object, which the linker script discards */
    tile[0] = 0;
    tile[1] = 1;
    tlut_count[0] = 0xFF;
    tlut_count[1] = 0x0F;
    tlut_offset[0] = 0x800;
    tlut_offset[1] = 0x400;
    arg20[0] = 1;
    arg20[1] = 2;
    arg19[0] = 1;
    arg19[1] = 4;
    gdl->words.w0 = 0xD7000002;
    gdl->words.w1 = 0xFFFFFFFF;
    gdl = (Gfx *) func_1501A490((s32) (gdl + 1), D_80083336, 0, 0, 0, 0);
    gdl = (Gfx *) func_1501A680(gdl);
    if (D_80082FA0 == 1) {
        fov = 95.0f;
    } else {
        fov = 80.0f;
    }
    if (D_800BE9F0 == 65) {
        pitch -= 119.0f;
        if (pitch < 0.0f) {
            pitch += 360.0f;
        }
    } else if (D_800BE9F0 == 60 ||
               (D_800BE9F0 == 19 && D_800C35EA == 1 && (D_800C3A08 == 2 || D_800C3A08 == 1))) {
        cam = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
        gdl = func_15110AC4(gdl, (s32) *(f32 *) (cam + 0x2C), (s32) *(f32 *) (cam + 0x24),
                            (s32) (*(f32 *) (cam + 0x30) - 1.0f), (s32) *(f32 *) (cam + 0x28), 0, 0, 0);
    }
    sky = (u8 *) D_800B0DF0;
    col[0] = sky[5];
    col[1] = sky[6];
    col[2] = sky[7];
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    if (col[2] + col[0] + col[1] == 765) {
        gdl->words.w0 = 0xFCFFFFFF;
        gdl->words.w1 = 0xFFFCF279;
        gdl++;
    } else {
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = (col[0] << 24) | (col[1] << 16) | (col[2] << 8) | 0xFF;
        gdl++;
        gdl->words.w0 = 0xFC129A25;
        gdl->words.w1 = 0xFF37FFFF;
        gdl++;
    }
    gdl->words.w0 = 0xEF08AC0F;
    gdl->words.w1 = 0x0F0A4004;
    gdl++;
    gdl->words.w0 = 0xF5500000;
    gdl->words.w1 = 0x07000000;
    gdl++;
    gdl->words.w0 = 0xF5481000;
    gdl->words.w1 = 0x00080200;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x000F407C;
    gdl++;
    gdl->words.w0 = 0xF5400800;
    gdl->words.w1 = 0x01080200;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x010F407C;
    gdl++;
    gdl->words.w0 = 0xF5000100;
    gdl->words.w1 = 0x06000000;
    gdl++;
    func_1511084C(view, yaw, pitch, roll);
    func_150A7A48(view, (f32 (*)[4]) ((u8 *) D_800BE628 + D_80082FA4 * 0x180 + 0xBC), m);
    guMtxF2L(m, (Mtx *) D_800DC2E0 + (D_80082FA4 * 2 + D_800BE9C0));
    gdl->words.w0 = 0xDA380007;
    gdl->words.w1 = (u32) ((Mtx *) D_800DC2E0 + (D_80082FA4 * 2 + D_800BE9C0));
    gdl++;
    gdl->words.w0 = 0xDA380003;
    gdl->words.w1 = (u32) D_80089810;
    gdl++;
    gdl->words.w0 = 0xDB0E0000;
    gdl->words.w1 = *(u16 *) ((u8 *) D_800BE628 + D_80082FA4 * 0x180 + 0xB8);
    gdl++;
    texs = D_8008955C[sky[9]];
    count = 0;
    first_vtx = 0;
    last_fmt = -1;
    vtx = D_800DC2B8[D_80082FA4 * 2 + D_800BE9C0];
    if (dist < 0) {
        dist = 0;
    }
    last = (D_800BE9F0 == 12) ? 6 : 5;
    i = (D_800BE9F0 == 25) ? 4 : 0;
    for (; i < last; i++) {
        switch (i) {
            case 0:
                if (pitch <= 180.0f) {
                    if (fov < pitch) {
                        continue;
                    }
                } else if (pitch < 360.0f - fov) {
                    continue;
                }
                break;
            case 1:
                if (270.0f + fov < pitch || pitch < 270.0f - fov) {
                    continue;
                }
                break;
            case 2:
                if (180.0f + fov < pitch || pitch < 180.0f - fov) {
                    continue;
                }
                break;
            case 3:
                if (90.0f + fov < pitch || pitch < 90.0f - fov) {
                    continue;
                }
                break;
            case 4:
                if (-90.0f + fov < yaw || yaw < -90.0f - fov) {
                    continue;
                }
                break;
            case 5:
                if (90.0f + fov < yaw || yaw < 90.0f - fov || dist < 300) {
                    continue;
                }
                break;
        }
        f = &D_800A3170[i];
        if (f->a[0] == f->b[0]) {
            axis = 'x';
        } else if (f->a[1] == f->b[1]) {
            axis = 'y';
        } else {
            axis = 'z';
        }
        face = (i == 5) ? 0 : i;
        gdl = func_1511127C(gdl, &vtx, texs[face], 0, 2, f->w, f->h, 60, 30, f->a[0], f->a[1], f->a[2], axis, view, dist,
                            &count, &first_vtx, loads, &last_fmt, arg19, arg20, tlut_offset, tlut_count, tile, face);
    }
    if (count != 0) {
        gdl->words.w0 = 0x01000000 | ((count & 0xFF) << 12) | ((count & 0x7F) << 1);
        gdl->words.w1 = vtx + first_vtx * 0x10;
        gdl++;
        for (k = 0; k < count; k += 4) {
            fmt = loads[k >> 2].fmt;
            gdl->words.w0 = 0xE7000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xFD100000;
            gdl->words.w1 = loads[k >> 2].addr;
            gdl++;
            gdl->words.w0 = 0xF3000000;
            gdl->words.w1 = 0x077FF000;
            gdl++;
            gdl->words.w0 = 0xFD100000;
            gdl->words.w1 = loads[k >> 2].addr + tlut_offset[fmt];
            gdl++;
            gdl->words.w0 = 0xE6000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xF0000000;
            gdl->words.w1 = 0x06000000 | (tlut_count[fmt] << 14);
            gdl++;
            if (fmt != last_fmt) {
                last_fmt = fmt;
                gdl->words.w0 = 0xD7000002 | ((tile[fmt] & 7) << 8);
                gdl->words.w1 = 0xFFFFFFFF;
                gdl++;
            }
            /* two triangles (k + 2, k, k + 1) and (k + 3, k, k + 2); G_TRI1 indices are vertex * 2 */
            gdl->words.w0 = 0x05000000 | (((k * 2 + 4) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 2) & 0xFF);
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0x05000000 | (((k * 2 + 6) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 4) & 0xFF);
            gdl->words.w1 = 0;
            gdl++;
        }
    }
    return gdl;
}
