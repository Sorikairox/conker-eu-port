// shockwave_hit_objects: P213: handler 1 of the effect node table D_80088C00 (dispatched by func_150C8F68 with the
/* node only; the node is freed when the result is 0). Every live object (state != 0) on the ground (unk28 < 20)
 * and not immune, that is a player (state 1) or type 0x53, is hit when the ring of radius node +0x44 has reached
 * it: ring - (horizontal distance to the node centre +0x10 / +0x18 - 100, 150 more for an unlifted type 0x53)
 * in [0, 250). Type 0x53 gets disable_run = 10, its script restarted (unk218 NULL) at command 0x13 (0x14 when its
 * holder D_800CC2D0[unk124] holds something, unk65); others the hit func_1505D024(obj, 0x6000E, facing, -1).
 * The asm returns its leftover v0: the state of the last object, or func_1505D024's result when that one was hit;
 * the C keeps that value. */
s32 func_1505D024(struct127 *obj, s32 flags, u16 val, s32 arg3);
s32 func_150CA0DC(u8 *node) {
    struct127 *o;
    s32 ret = 0;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 reach;

    for (o = D_800CC2D0; o != &D_800CC2D0[25]; o++) {
        ret = o->interaction_state;
        if (ret == 0 || !(o->unk28 < 20.0f) || o->immune != 0) {
            continue;
        }
        if (o->id != 0x53 && ret != 1) {
            continue;
        }
        dx = o->x_position - *(f32 *)(node + 0x10);
        dz = o->z_position - *(f32 *)(node + 0x18);
        dist = sqrtf(dx * dx + dz * dz) - 100.0f;
        if (o->id == 0x53 && o->unk13C == 0) {
            dist -= 150.0f;
        }
        reach = *(f32 *)(node + 0x44) - dist;
        if (!(0.0f <= reach) || !(reach < 250.0f)) {
            continue;
        }
        if (o->id == 0x53) {
            o->disable_run = 10;
            o->unk218 = NULL;
            o->unk232 = 0x13;
            if (D_800CC2D0[o->unk124].unk65 != 0) {
                o->unk232 = 0x14;
            }
        } else {
            ret = func_1505D024(o, 0x6000E, o->unk7A, -1);
        }
    }
    return ret;
}
