#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P241: readable C for sky_segments_flicker (game_eu_12E0D0, 73 insns). */
// sky_segments_flicker: level update handler (g_level_update_fns entry 10, `void (s32)`; does nothing for a non-zero
// argument): advances the sky animation frame g_level_anim_frame and toggles each of the 5 sky segment variants
// g_sky_segment_on[i] with chance 35 / 1000 (70 / 1000 while it is on). A segment that turns on gets command 0x18 for
// its id (g_sky_segment_light_ids = 9..13, light_ctrl_broadcast), one that turns off gets 0x1C then 0x17. random_int is the random
// number generator.
typedef struct {
    u8 id[5];
} SkyIds_151008C0;
extern SkyIds_151008C0 g_sky_segment_light_ids; /* was D_80088F60 */
extern u8 g_level_anim_frame; /* was D_800DD835 */
void light_ctrl_broadcast(u8, u8, s32);
/* was func_151008C0 */
void sky_segments_flicker(s32 arg0) {
    SkyIds_151008C0 ids = g_sky_segment_light_ids;
    s32 i;
    u32 chance;

    if (arg0 != 0) {
        return;
    }
    g_level_anim_frame++;
    for (i = 0; i < 5; i++) {
        chance = (g_sky_segment_on[i] != 0) ? 70 : 35;
        if ((u32) random_int() % 1000 < chance) {
            g_sky_segment_on[i] ^= 1;
            if (g_sky_segment_on[i] != 0) {
                light_ctrl_broadcast(ids.id[i], 0x18, 0);
            } else {
                light_ctrl_broadcast(ids.id[i], 0x1C, 0);
                light_ctrl_broadcast(ids.id[i], 0x17, 0);
            }
        }
    }
}

extern s32 g_sky_segment_tex_ids[]; /* asset ids: 3 animated frames, then the 5 segment textures' variants; was D_800906D4 */
extern u8 g_level_anim_frame; /* was D_800DD835 */
s32 texture_cache_lookup(s32, s32 *, s32, s32);

// sky_segments_set: points RSP segments 2 / 3 at two consecutive frames of a 3-frame animation (g_level_anim_frame / 4)
// and segments 4..8 at the assets picked by g_sky_segment_on[0..4] (texture_cache_lookup, mode 3). Returns the advanced DL.
/* was func_151009E4 */
Gfx *sky_segments_set(Gfx *gdl) {
    s32 size;
    s32 addr;
    s32 frame;
    s32 seg;
    s32 i;

    frame = g_level_anim_frame >> 2;
    addr = texture_cache_lookup(g_sky_segment_tex_ids[frame % 3], &size, 3, 0);
    gdl->words.w0 = 0xDB060008;
    gdl->words.w1 = addr;
    gdl++;
    addr = texture_cache_lookup(g_sky_segment_tex_ids[(frame + 1) % 3], &size, 3, 0);
    gdl->words.w0 = 0xDB06000C;
    gdl->words.w1 = addr;
    gdl++;
    for (i = 0, seg = 0x10; seg != 0x24; i++, seg += 4) {
        addr = texture_cache_lookup(g_sky_segment_tex_ids[3 + g_sky_segment_on[i]], &size, 3, 0);
        gdl->words.w0 = 0xDB060000 | (seg & 0xFFFF);
        gdl->words.w1 = addr;
        gdl++;
    }
    return gdl;
}
