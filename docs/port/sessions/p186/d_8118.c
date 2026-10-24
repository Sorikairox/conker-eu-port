Gfx *func_15142E24(Gfx *gfx, s32 tex, s32 frame, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *flag, s32 argA);
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_1513F4E4(Gfx *gfx, u8 combine, u8 *flag);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *flag);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *flag);
Gfx *func_15095B70(Gfx *gfx, u8 *quad);
extern s32 D_800D30BC;
extern s32 D_800A4EA8[]; /* render mode pairs (2 words each) */
extern u8 D_80090BAC[];
extern u8 D_800908EC[];

/* billboard_sprite_draw: P186: draws the camera-facing sprite of object record obj for player view `player`.
 * Texture obj +0x10 (word 0 = the image, or above 0x10000000 a frame table indexed by frame obj +0x1C >> 8;
 * byte +0xA = kind), position s16 obj +0x20 / +0x22 / +0x24, size s16 obj +0x34 (width) / +0x36 (height).
 * A negative width is a size scaled by how much the sprite faces the camera: |camera yaw (view +0x380) +
 * obj[0x1B] * 1.40625| folded into 0..90 degrees, times -width / 90, at least 1024. A negative height is
 * |view +0x388| * (max(width, 0) + height) / 90 - height. Render mode: flag 0x100 in u16 obj +0x44 takes the
 * combiner byte / D_800A4EA8 entry from obj +0x14 (bit 0x200: +0x100000), otherwise by texture kind (5 with
 * flag 0x10: combiner 13 / entry 18, 5: combiner 15 / entry 17 / +0x100000, other: combiner 13 / entry 3).
 * Primitive colour obj +0x3C..0x3F, environment colour obj +0x40..0x42 (flag 1) or by texture (D_80090BAC
 * (128, 128, 255), D_800908EC white, else black). Returns the display list end. */
s32 func_15168118(s32 gdl, u8 *obj, s16 player) {
    struct {
        s16 x, y, z;
        s16 w, h;
    } quad;
    u8 flag;
    Gfx *gfx = (Gfx *) gdl;
    u8 *tex = *(u8 **) (obj + 0x10);
    u8 *view = (u8 *) D_800DBFF0 + player * 0x9A0;
    u16 flags;
    s32 img;
    s32 w, h;
    s32 *mode;
    f32 ang;
    u8 r, g, b;

    flag = 1;
    img = *(s32 *) tex;
    if ((u32) img >= 0x10000000) {
        img = ((s32 *) img)[*(s16 *) (obj + 0x1C) >> 8];
    }
    gfx = func_15142E24(gfx, (s32) tex, *(s16 *) (obj + 0x1C) << 8, 2, 0x100, 0x100, img, 5, (s32) &quad, &flag, 3);

    quad.x = *(s16 *) (obj + 0x20);
    quad.y = *(s16 *) (obj + 0x22);
    quad.z = *(s16 *) (obj + 0x24);

    w = *(s16 *) (obj + 0x34);
    if (w < 0) {
        ang = fabsf(*(f32 *) (view + 0x380) + (f32) obj[0x1B] * 1.40625f);
        while (ang >= 360.0f) {
            ang -= 360.0f;
        }
        if (ang >= 180.0f) {
            ang -= 180.0f;
        }
        if (ang >= 90.0f) {
            ang = 180.0f - ang;
        }
        w = (s32) ((f32) w * ang * (-1.0f / 90.0f));
        if (w < 0x400) {
            w = 0x400;
        }
    }
    quad.w = w;

    h = *(s16 *) (obj + 0x36);
    if (h < 0) {
        w = *(s16 *) (obj + 0x34);
        if (w < 0) {
            w = 0;
        }
        h = (s32) (fabsf(*(f32 *) (view + 0x388)) * (f32) (w + h) * (1.0f / 90.0f) - (f32) h);
    }
    quad.h = h;

    flags = *(u16 *) (obj + 0x44);
    if (flags & 0x100) {
        u8 combine = obj[0x15];
        u8 entry = obj[0x17];

        gfx = func_15142B7C(gfx, 5, 0);
        gfx = func_1513F4E4(gfx, combine, &flag);
        mode = &D_800A4EA8[entry * 2];
        gfx = func_15142FBC(gfx, ((flags & 0x200) ? 0x100000 : 0) | D_800D30BC | 0x2CA0,
                            (mode[1] | mode[0]) | 4, &flag);
    } else if (tex[0xA] != 5) {
        gfx = func_1513F4E4(gfx, 13, &flag);
        gfx = func_15142FBC(gfx, D_800D30BC | 0x2CA0, (D_800A4EA8[3 * 2 + 1] | D_800A4EA8[3 * 2]) | 4, &flag);
    } else if (flags & 0x10) {
        /* (the asm also holds an unreachable kind 3 branch here: combiner 14 / entry 3) */
        gfx = func_1513F4E4(gfx, 13, &flag);
        gfx = func_15142FBC(gfx, D_800D30BC | 0x2CA0, (D_800A4EA8[18 * 2 + 1] | D_800A4EA8[18 * 2]) | 4, &flag);
    } else {
        gfx = func_1513F4E4(gfx, 15, &flag);
        gfx = func_15142FBC(gfx, D_800D30BC | 0x100000 | 0x2CA0, (D_800A4EA8[17 * 2 + 1] | D_800A4EA8[17 * 2]) | 4,
                            &flag);
    }

    gfx = func_15142CF0(gfx, 1, 0, obj[0x3C], obj[0x3D], obj[0x3E], obj[0x3F], &flag);
    if (flags & 1) {
        r = obj[0x40];
        g = obj[0x41];
        b = obj[0x42];
    } else if (*(u8 **) (obj + 0x10) == D_80090BAC) {
        r = 128;
        g = 128;
        b = 255;
    } else if (*(u8 **) (obj + 0x10) == D_800908EC) {
        r = 255;
        g = 255;
        b = 255;
    } else {
        r = g = b = 0;
    }
    gfx = func_15142C10(gfx, r, g, b, 0, &flag);
    return (s32) func_15095B70(gfx, (u8 *) &quad);
}
