// P214 selftest case: port-b P210 draft of aiscript_find_visible_target (game_A28B0), first argument of math_atan2_u16 behind a
// branch between the write of f12 and the jal block (P214 jal-stub FPR compare, DIFFTEST_NOPROTO=math_atan2_u16).
int aiscript_find_by_kind(s32, s32);

// find_visible_target: P210: script command: looks for the nearest object the current one can see: live (state,
// health), targetable (unkF8 bit 0x20), not itself, of another id unless g_aiscript_arg1 is set, within 50 in height,
// closer than g_aiscript_arg0 * 8 (obj_dist_3d), and inside its view cone (width byte 0x17 of its type record
// D_800D1C90[id], in 1/256 turns around heading unk76 >> 8 + unk2CA). The nearest one is stored as unkA8 =
// 0x80 + its number; then the object's script jumps to g_aiscript_arg3 and, when g_aiscript_arg2 is set, the target's
// script to g_aiscript_arg2 with unk222 = the current object's number.
void aiscript_find_visible_target(void) {
    s32 self = ((s32)g_cur_obj - (s32)g_objects) / 0x32C;
    f32 best = g_aiscript_arg0 * 8;
    struct127 *o = g_objects;
    struct127 *t;
    s32 i;
    f32 d;
    f32 dx;
    s32 fov;
    u16 ang;

    g_cur_obj->unkA8 = 0;
    for (i = 0; i < 25; i++, o++) {
        if (o->interaction_state == 0 || o->health == 0 || !(o->unkF8 & 0x20) || i == self) {
            continue;
        }
        if (g_aiscript_arg1 == 0 && g_cur_obj->id == o->id) {
            continue;
        }
        if (50.0f < fabsf(g_cur_obj->y_position - o->y_position)) {
            continue;
        }
        d = obj_dist_3d(g_cur_obj, o);
        if (!(d < best)) {
            continue;
        }
        dx = o->x_position - g_cur_obj->x_position;
        fov = D_800D1C90[g_cur_obj->id]->unk17;
        if (fov < 0) {
            fov = 0;
        }
        ang = math_atan2_u16(dx, g_cur_obj->z_position - o->z_position, 0);
        if (((((g_cur_obj->unk76 >> 8) + g_cur_obj->unk2CA) - (ang >> 8) + fov / 2) & 0xFF) < fov) {
            g_cur_obj->unkA8 = i + 0x80;
            best = d;
        }
    }
    if (g_cur_obj->unkA8 != 0) {
        g_cur_obj->unk218 = (struct216 *)aiscript_find_by_kind(0, g_aiscript_arg3);
        g_cur_obj->unk218--;
        if (g_aiscript_arg2 != 0) {
            t = &g_objects[g_cur_obj->unkA8 & 0x7F];
            t->unk218 = NULL;
            t->unk232 = g_aiscript_arg2;
            t->unk222 = self;
        }
    }
}
