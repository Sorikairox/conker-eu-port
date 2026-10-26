#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150158C0 */
void glyph_count_reset(void) {
    D_800CC16C = 0;
}

void heap_free(s32);
void glyph_rle_to_texture(u8 *, s32, s32);
extern u32 D_80083310[][2];

/* load ROM range #idx (D_80083310[idx] = {start, end}) into a temporary buffer and hand each record
   (big-endian size at +4, at least 16 bytes) to glyph_rle_to_texture */
/* was func_150158D0 */
void glyph_set_load_rom(s16 idx) {
    u8 *buf = (u8 *)heap_alloc_tagged(0x2800, 1, 2, 1, 0);
    u32 *range = D_80083310[idx];
    u8 *rec;
    s32 i;

    rom_dma_read(range[0], buf, range[1] - range[0], 1);
    rec = buf;
    i = 0;
    while ((u32)(rec + 0xF) < (u32)(buf + range[1] - range[0])) {
        glyph_rle_to_texture(rec, i, idx);
        rec += (rec[4] << 24) + (rec[5] << 16) + (rec[6] << 8) + rec[7];
        i++;
    }
    heap_free((s32)buf);
}
extern u8 *D_80085D20[];
extern u8 *D_80085D24[];

/* Expand one RLE glyph record (font/sprite set `set`, glyph `idx`) into its 8-bit texture.
 * D_80085D24[set][idx*4..+3] = {width + 1, height + 1, src[2], src[3]}; the texture is
 * D_80085D20[set] + idx * 224, rows of (width + 7) & ~7 bytes. A blank row and a blank column frame
 * the glyph. Each RLE byte at src[8...] is (value & 0xF0) | (run - 1). Odd rows are stored with the
 * TMEM 8-byte word swap (x ^ 4). The tables are re-read for every access, as the original does. */
#define GLYPH(k) (D_80085D24[set][idx * 4 + (k)])
#define TEX(o) (D_80085D20[set][idx * 224 + (o)])
/* was func_150159E8 */
void glyph_rle_to_texture(u8 *src, s32 idx, s32 set) {
    s32 stride;
    s32 row;
    s32 x;
    s32 swap;
    s32 k;
    s32 n;
    u8 v;
    s32 in;

    GLYPH(0) = src[0] + 1;
    GLYPH(1) = src[1] + 1;
    GLYPH(2) = src[2];
    GLYPH(3) = src[3];
    stride = (GLYPH(0) + 7) & 0xFFF8;

    for (x = 0; x < GLYPH(0); x++) {
        TEX(x) = 0;
    }
    in = 8;
    for (row = 1; row < GLYPH(1) + 1; row++) {
        swap = (row & 1) ? 4 : 0;
        for (x = 0; x < GLYPH(0); x++) {
            if (x == 0) {
                TEX(row * stride + (x ^ swap)) = 0;
            } else {
                v = src[in] & 0xF0;
                n = (src[in] & 0xF) + 1;
                in++;
                for (k = 0; k < n; k++) {
                    TEX(row * stride + ((x + k) ^ swap)) = v;
                }
                x += n - 1;
            }
        }
        for (; x < stride; x++) {
            TEX(row * stride + (x ^ swap)) = 0;
        }
    }
    for (x = 0; x < stride; x++) {
        TEX(row * stride + x) = 0;
    }
}
#undef GLYPH
#undef TEX