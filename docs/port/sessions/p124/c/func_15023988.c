extern s32 D_800C39D0;
extern s32 D_eu_800C3A60;
extern u8 D_800C40A9;

/* the 0x10-byte record a scene positional sound (handler C types 6 / 0xA) passes to func_1000FA64 */
typedef struct {
    u8 player;
    u8 track;
    u8 untilEnd;  /* stop when the scene time reaches its end */
    u8 pad3;
    u16 left;     /* frames left (0xFFFF = endless) */
    u16 total;    /* frames at the start */
    u16 fadeIn;   /* fade-in length (frames) */
    u16 fadeOut;  /* fade-out length: the last fadeOut frames */
    u16 volume;
    u8 epoch;     /* D_800C3A08[player] when started */
    u8 padF;
} SceneSfx;

// scene_sfx_update: positional sound callback (SfxEnt +0x14, game init_EB00): follows the track's position (D_800C3958 record:
// x, y + 0x38, z) while the player's scene epoch is unchanged, counts the frames left down, sets *vol from the
// record's volume with the fade-in / fade-out ramps and the cutscene volume D_800C40A9 / 25 while skipping
// (D_800C3C88). Stops (vol 0, *stop = 0, record freed, returns 1) at the end, on a stop request (flag 0x80) or when
// the scene ended; else returns 0.
s32 func_15023988(u8 *e, s32 *a1, u32 *vol, s32 *a3, s32 *a4, s32 *a5, u16 *stop) {
    SceneSfx *r;
    u8 *base;
    u16 left;

    r = *(SceneSfx **) (e + 0x18);
    if ((r->untilEnd != 0 && (&D_800C39D0)[r->player] >= (&D_eu_800C3A60)[r->player]) || (*(s32 *) (e + 0x10) & 0x80)) {
        goto stop;
    }
    if (r->epoch == (&D_800C3A08)[r->player] && (&D_800C3958)[r->player] != NULL) {
        *(s16 *) (e + 2) = *(f32 *) ((u8 *) (&D_800C3958)[r->player] + r->track * 0x44 + 0);
        base = (u8 *) (&D_800C3958)[r->player] + r->track * 0x44;
        *(s16 *) (e + 4) = *(f32 *) (base + 0x38) + *(f32 *) (base + 4);
        *(s16 *) (e + 6) = *(f32 *) ((u8 *) (&D_800C3958)[r->player] + r->track * 0x44 + 8);
    }
    left = r->left;
    if (left != 0xFFFF) {
        if (D_800BE9E4 < left) {
            r->left = left - D_800BE9E4;
        } else {
            goto stop;
        }
    }
    *vol = r->volume;
    if (r->left < r->fadeOut) {
        if (r->left != 0) {
            *vol = (u32) (r->volume * r->left) / r->fadeOut;
        }
    } else if (r->fadeIn != 0 && r->total - r->fadeIn < r->left) {
        *vol = (u32) (*vol * (r->total - r->left)) / r->fadeIn;
    }
    if (r->left == 0xFFFF || D_800C3C88 == 0) {
        return 0;
    }
    *vol = (u32) (*vol * D_800C40A9) / 25;
    if (D_800BE9E4 < D_800C40A9) {
        return 0;
    }
stop:
    *vol = 0;
    *stop = 0;
    func_10004074(r);
    return 1;
}
