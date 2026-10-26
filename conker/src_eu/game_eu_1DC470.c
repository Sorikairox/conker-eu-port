#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 collision_floor_dynamic_b_full(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
void debris_burst_spawn(struct17 *, s32 *, s32, u8, s32);
void sound_play_for_actor(s32, s32, s32, s32, s32, u8 *);
/* was func_151AEC60 */
void char_ground_debris_5(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (-9500.0f < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = collision_floor_dynamic_b_full((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        debris_burst_spawn(&pos, (s32 *)(arg0 + 0x34), 5, arg0[0xC], arg0[1]);
        sound_play_for_actor(0, 17, 21000, 0, 0, obj);
    }
}
