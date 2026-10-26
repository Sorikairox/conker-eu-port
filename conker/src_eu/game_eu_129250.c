#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* One star of the D_800DC2B0 field (8000 of them): the position is three halves of f32s (the upper 16 bits). */
typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8 tint;  /* 0 red, 1 blue, 2 green, other white */
    /* 0x07 */ u8 alpha; /* brightness, shared by the 4 pixels */
} StarPoint;

#define STAR_COUNT 8000

/* Camera record (D_800BE628, 0x180 bytes each) fields read here. */
#define STAR_CAM_F(cam, off) (*(f32 *) ((u8 *) (cam) + (off)))
#define STAR_CAM_WIDTH 0x04
#define STAR_CAM_HEIGHT 0x08
#define STAR_CAM_SCALE_X 0x0C
#define STAR_CAM_SCALE_Y 0x10
#define STAR_CAM_TOP 0x24
#define STAR_CAM_LEFT 0x2C

/* The list is written through KSEG1 (uncached) and the end handed back cached; wasm has no such segment. */
#ifdef PORT
#define STAR_UNCACHED(p) (p)
#define STAR_CACHED(p) (p)
#else
#define STAR_UNCACHED(p) ((Gfx *) ((u32) (p) | 0x20000000))
#define STAR_CACHED(p) ((Gfx *) ((u32) (p) ^ 0x20000000))
#endif

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even (|f| < 2^31) */
#define STAR_RINT(f)                                                                                       \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32) (f)                                                 \
     : ((f) >= 0.0f) ? (s32) (((f) + 8388608.0f) - 8388608.0f)                                            \
                     : -(s32) ((-(f) + 8388608.0f) - 8388608.0f))

/*
 * One pixel of a star: prim colour tint | alpha, then a G_FILLRECT of the pixel (x, y). The asm keeps the rectangle
 * in a 64-bit register and steps it with daddu / dsubu; for x, y < 2^17 (any real viewport) the halves never carry.
 */
static Gfx *star_pixel(Gfx *g, u32 tint, s32 alpha, s32 x, s32 y) {
    g->words.w0 = 0xFA000000;
    g->words.w1 = tint | alpha;
    g++;
    g->words.w0 = 0xF6000000 + ((x + 1) << 14) + ((y + 1) << 2);
    g->words.w1 = (x << 14) + (y << 2);
    g++;
    return g;
}

static f32 star_half_to_f32(s16 h) {
    union {
        u32 u;
        f32 f;
    } v;

    v.u = (u32) (u16) h << 16;
    return v.f;
}

/*
 * star_field_draw: draws the star field (Rare hand asm). Each of the STAR_COUNT points of D_800DC2B0 is transformed
 * by the view rotation mtx (no translation; w = the third column) and, when w > 203 and the projection lands
 * inside the current player's viewport (D_800BE628[g_cur_view_player]: scale +0xC / +0x10, origin +0x2C (+ scale x) /
 * +0x24 (+ scale y, y grows down), size +4 / +8), splatted as 4 one-pixel fill rectangles around the point with
 * bilinear weights: prim colour (tint | alpha * weight, rounded) then G_FILLRECT, 8 commands per star. The list is
 * padded to 16 bytes before and after with zero commands. Returns the new list end. Only caller camera_view_clear_draw.
 */
/* was func_150FBA40 */
Gfx *star_field_draw(Gfx *gdl, f32 (*mtx)[4]) {
    StarPoint *star;
    StarPoint *end;
    u8 *cam;
    f32 scaleX, scaleY, width, height, left, top;
    f32 x, y, z, w, inv, sx, sy, fx, fy, gx, gy, alpha, rowA;
    s32 ix, iy;
    u32 tint;
    Gfx *g;

    star = (StarPoint *) D_800DC2B0;
    end = star + STAR_COUNT;
    cam = (u8 *) D_800BE628 + g_cur_view_player * 0x180;
    scaleX = STAR_CAM_F(cam, STAR_CAM_SCALE_X);
    scaleY = STAR_CAM_F(cam, STAR_CAM_SCALE_Y);
    width = STAR_CAM_F(cam, STAR_CAM_WIDTH);
    height = STAR_CAM_F(cam, STAR_CAM_HEIGHT);
    left = STAR_CAM_F(cam, STAR_CAM_LEFT) + scaleX;
    top = STAR_CAM_F(cam, STAR_CAM_TOP) + scaleY;

    if ((u32) gdl & 8) {
        gdl->words.w0 = 0;
        gdl->words.w1 = 0;
        gdl++;
    }
    g = STAR_UNCACHED(gdl);
    do {
        x = star_half_to_f32(star->x);
        y = star_half_to_f32(star->y);
        z = star_half_to_f32(star->z);
        w = x * mtx[0][3] + y * mtx[1][3] + z * mtx[2][3];
        if (w <= 203.0f) {
            continue;
        }
        inv = 1.0f / w;
        sx = (x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0]) * scaleX * inv + left;
        if (sx < 0.0f || sx >= width) {
            continue;
        }
        sy = top - (x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1]) * scaleY * inv;
        if (sy < 0.0f || sy >= height) {
            continue;
        }
        ix = (s32) sx;
        iy = (s32) sy;
        fx = sx - (f32) ix;
        fy = sy - (f32) iy;
        gx = 1.0f - fx;
        gy = 1.0f - fy;
        alpha = (f32) star->alpha;
        switch (star->tint) {
            case 0:
                tint = 0xFFCDCD00;
                break;
            case 1:
                tint = 0xCDD3FF00;
                break;
            case 2:
                tint = 0xDAFBDC00;
                break;
            default:
                tint = 0xFFFFFF00;
                break;
        }

        rowA = alpha * gy;
        g = star_pixel(g, tint, STAR_RINT(rowA * gx), ix, iy);
        g = star_pixel(g, tint, STAR_RINT(rowA * fx), ix + 1, iy);
        rowA = alpha * fy;
        g = star_pixel(g, tint, STAR_RINT(rowA * fx), ix + 1, iy + 1);
        g = star_pixel(g, tint, STAR_RINT(rowA * gx), ix, iy + 1);
    } while (++star != end);

    if ((u32) g & 8) {
        g->words.w0 = 0;
        g->words.w1 = 0;
        g++;
    }
    return STAR_CACHED(g);
}
