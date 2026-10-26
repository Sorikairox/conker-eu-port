#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150120B0 */
void ambient_fx_spawn_type4(s32 arg0) {
    struct37 *temp_v0;
    struct184 tmp;

    tmp.unk0 = 50.0f;
    tmp.unk4 = 50.0f;
    tmp.unk8 = 50.0f;
    tmp.unkC = 50.0f;
    tmp.unk10 = 50.0f;
    tmp.unk14 = 50.0f;
    tmp.unk18 = 0.0f;
    tmp.unk1C = D_80096540;

    temp_v0 = effect_node_create(300, -1, 30, -1, 0, 65, 32, 255, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 32);
    }
}

/* was func_1501214C */
void obj_drip_attach(struct127 *arg0) {
    struct185 tmp;

    if (D_800BE9F0 != 24) {
        tmp.unk0 = arg0;
        tmp.unk4 = arg0->unique_id;
        tmp.unk6 = 300;
        tmp.unk8 = 0;
        tmp.unk9 = 0;
        tmp.unkA = 2;
        model_drip_create(&tmp, 0, 255, 1);
    }
}
