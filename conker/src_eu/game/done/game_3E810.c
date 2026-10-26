#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011360 */
void level_obj_init_area_points_23(void) {
    area_points_reset();
    area_points_alloc(2);
    area_points_alloc(3);
    if ((g_save_progress_bits->unk14 & 1) != 0) {
        g_level_header->unk5 = (u8)0x30;
        g_level_header->unk6 = (u8)0x38;
        g_level_header->unk7 = (u8)0x5F;
    }
}
