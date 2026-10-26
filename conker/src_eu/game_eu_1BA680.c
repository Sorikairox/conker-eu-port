#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 *asset_load_with_subfiles(s32, s32, s32, s32, s32, s32);
s32 texture_resolve_dl_ids(s32, s32, s32, s32, s32 *);
void gfx_dl_relocate(s32, s32 *);
extern u8 D_800DFC00[];
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
/* shared_dl_acquire (P57): reference-counted load of asset (9, arg0) (pair shared_dl_release releases it). First use:
 * asset_load_with_subfiles(0, 0, 0, 2, 9, arg0) (0 = not found: return 0), relocate the display list *p with
 * texture_resolve_dl_ids(*p, 0, 1, 0x3E, &D_800DFDE8[arg0]), gfx_dl_relocate(*p, p), keep p in D_800E0578[arg0].
 * The count D_800DFC00[arg0] saturates at 0xFF. Returns the display list *p (a G_DL target in hud_health_draw). */
/* was func_1518C900 */
s32 shared_dl_acquire(s32 arg0) {
    s32 *p;

    if (D_800DFC00[arg0] == 0) {
        p = asset_load_with_subfiles(0, 0, 0, 2, 9, arg0);
        if (p == NULL) {
            return 0;
        }
        texture_resolve_dl_ids(*p, 0, 1, 0x3E, &D_800DFDE8[arg0]);
        gfx_dl_relocate(*p, p);
        D_800E0578[arg0] = p;
    } else {
        p = D_800E0578[arg0];
    }
    if (D_800DFC00[arg0] != 0xFF) {
        D_800DFC00[arg0]++;
    }
    return *p;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BA680/shared_dl_acquire.s")
#endif

extern u8 D_800DFC00[];
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
/* was func_1518CF74 */
void shared_dl_release(s32 arg0) {
    if (arg0 != 0x1E4 && D_800DFC00[arg0] != 0) {
        if (--D_800DFC00[arg0] == 0) {
            texture_id_list_release(D_800DFDE8[arg0]);
            heap_set_block_tag(D_800E0578[arg0], 4);
        }
    }
}
