/* P114: struct_1502AB94_ref and D_800C3A10 are now in the hoisted NM block of game_eu_51190.c */
u8 *world_record_find(u8);
s32 scene_event_run_a(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32);
s32 scene_event_run_b(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32);
s32 scene_event_run_c(s32, u8, u16, s32, s32, struct127 *, u8 *, u8 *, s32, s32);

/* Runs entry arg1 of player `player` through the three handlers in turn; the first non-zero result is returned.
 * The entry may refer to an object (kind 2: its data at +0x14 replaces the player's D_800C3958 record) or to a
 * world_record_find record (kind 3); a missing reference returns 0. When D_800C3C88 == 2 the middle handler is skipped
 * and the last one gets 1 instead of 0. */
s32 scene_event_run(s32 arg0, u8 arg1, u16 arg2, s32 arg3, s32 player) {
    struct127 *obj;
    u8 *rec;
    u8 *data;
    s32 flag;
    s32 ret;
    struct_1502AB94_ref *ref;

    obj = NULL;
    rec = NULL;
    data = NULL;
    flag = (&D_800C3A08)[player];
    ref = &D_800C3A10[player][arg1];
    if (ref->kind == 2) {
        obj = obj_find_by_setup_id(ref->id);
        if (obj == NULL) {
            return 0;
        }
        data = (u8 *) obj + 0x14;
    } else if (ref->kind == 3) {
        rec = world_record_find(ref->id);
        if (rec == NULL) {
            return 0;
        }
    }
    if (data == NULL) {
        data = (u8 *) ((&D_800C3958)[player] + arg1);
    }
    if (D_800C3C88 != 2) {
        ret = scene_event_run_a(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
        if (ret != 0) {
            return ret;
        }
        ret = scene_event_run_b(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
        if (ret != 0) {
            return ret;
        }
        return scene_event_run_c(arg0, arg1, arg2, arg3, player, obj, rec, data, flag, 0);
    }
    ret = scene_event_run_a(arg0, arg1, arg2, arg3, player, obj, rec, data, flag);
    if (ret != 0) {
        return ret;
    }
    return scene_event_run_c(arg0, arg1, arg2, arg3, player, obj, rec, data, flag, 1);
}
