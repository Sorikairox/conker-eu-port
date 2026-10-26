#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1509DD10 */
s32 fxevt_nop_a(s32 arg0) {
    return 1;
}

/* was func_1509DD20 */
s32 fxevt_nop_b(s32 arg0) {
    return 1;
}

/* was func_1509DD30 */
s32 fxevt_nop_c(s32 arg0) {
    return 1;
}

/* was func_1509DD40 */
s32 fxevt_nop_d(s32 arg0) {
    return 1;
}

/* was func_1509DD50 */
s32 fxevt_debris_burst(s32 arg0, struct214 *arg1) {
    swarm_spawn(arg1->unk7, 0, arg1->unkB, arg1->unkC, arg1->unk10, arg1->unk14, arg1->unk18, 0x7FFF, 0xFF, arg1->unk1C, 0);
    return 1;
}

/* was func_1509DDC4 */
s32 fxevt_emitter_kill(s32 arg0, u8 arg1) {
    swarm_destroy_by_id(arg0 & 0xff);
    return 0;
}

s32 obj_slot_by_spawn(s32);
void func_15178C34(u8, s32, s32, s32, s32);
void func_15178BE4(u8, f32*, s32);
s32 swarm_distance_to_obj(u8 arg0, s32 arg1);
void swarm_set_target_ptr(u8, s32, s16);
void swarm_set_target_pos(u8, s32, s32, s32, s16);

/* was func_1509DDFC */
s32 fxevt_emitter_set_target(s32 arg0, s32 arg1, u8 *arg2) {
    switch (arg1) {                                 /* irregular */
    case 0:
        swarm_set_target_ptr(arg0 & 0xFF, &g_objects[obj_slot_by_spawn((*(s32 *)((u8 *)arg2 + 8)) & ~0x2000)].x_position, (*(s16 *)((u8 *)arg2 + 0xE)));
        return 1;
    case 1:
        swarm_set_target_pos(arg0 & 0xFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), (*(s32 *)((u8 *)arg2 + 0x10)), (*(s32 *)((u8 *)arg2 + 0x14)));
        return 1;
    default:
        return 0;
    }
}
// NON-MATCHING: what is the logic here!?
// s32 fxevt_emitter_set_target(s32 arg0, s32 arg1, struct215 *arg2) {
//     // if (arg1 == 1) {
//     //     return 0;
//     // }
//     // if (arg1 == 0) {
//     //     func_15178BE4(arg0 & 0xFF, &g_objects[obj_slot_by_spawn(arg2->unk8 & ~0x2000)].unk14, arg2->unkC.s.unk2);
//     //     return 1;
//     // }
//     // if (arg1 != 1) {
//     //     func_15178C34(arg0 & 0xFF, arg2->unk8, arg2->unkC.i.unk0, arg2->unk10, arg2->unk14);
//     //     return 1;
//     // }
//
//     switch (arg1) {
//         case 1:
//             return 0;
//         case 0:
//             func_15178BE4(arg0 & 0xFF, &g_objects[obj_slot_by_spawn(arg2->unk8 & ~0x2000)].unk14, arg2->unkC.s.unk2);
//             return 1;
//         default:
//             func_15178C34(arg0 & 0xFF, arg2->unk8, arg2->unkC.i.unk0, arg2->unk10, arg2->unk14);
//             return 1;
//     }
// }

/* was func_1509DEC4 */
s32 fxevt_emitter_dist_to_obj(s32 arg0, s32 arg1, struct215 *arg2) {
    if (arg1 == 0) {
        s32 mask = ~0x2000;
        return swarm_distance_to_obj(arg0 & 0xff, obj_slot_by_spawn(arg2->unk8 & mask));
    }
    return 0;
}
