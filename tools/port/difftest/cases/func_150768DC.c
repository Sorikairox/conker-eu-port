// P214 selftest case: port-b P210 draft of func_150768DC (game_A28B0), first argument of func_1505A630 behind a
// branch between the write of f12 and the jal block (P214 jal-stub FPR compare, DIFFTEST_NOPROTO=func_1505A630).
int func_1507BB28(s32, s32);

// find_visible_target: P210: script command: looks for the nearest object the current one can see: live (state,
// health), targetable (unkF8 bit 0x20), not itself, of another id unless D_800D1891 is set, within 50 in height,
// closer than D_800D1890 * 8 (func_1505A72C), and inside its view cone (width byte 0x17 of its type record
// D_800D1C90[id], in 1/256 turns around heading unk76 >> 8 + unk2CA). The nearest one is stored as unkA8 =
// 0x80 + its number; then the object's script jumps to D_800D1893 and, when D_800D1892 is set, the target's
// script to D_800D1892 with unk222 = the current object's number.
void func_150768DC(void) {
    s32 self = ((s32)D_800D154C - (s32)D_800CC2D0) / 0x32C;
    f32 best = D_800D1890 * 8;
    struct127 *o = D_800CC2D0;
    struct127 *t;
    s32 i;
    f32 d;
    f32 dx;
    s32 fov;
    u16 ang;

    D_800D154C->unkA8 = 0;
    for (i = 0; i < 25; i++, o++) {
        if (o->interaction_state == 0 || o->health == 0 || !(o->unkF8 & 0x20) || i == self) {
            continue;
        }
        if (D_800D1891 == 0 && D_800D154C->id == o->id) {
            continue;
        }
        if (50.0f < fabsf(D_800D154C->y_position - o->y_position)) {
            continue;
        }
        d = func_1505A72C(D_800D154C, o);
        if (!(d < best)) {
            continue;
        }
        dx = o->x_position - D_800D154C->x_position;
        fov = D_800D1C90[D_800D154C->id]->unk17;
        if (fov < 0) {
            fov = 0;
        }
        ang = func_1505A630(dx, D_800D154C->z_position - o->z_position, 0);
        if (((((D_800D154C->unk76 >> 8) + D_800D154C->unk2CA) - (ang >> 8) + fov / 2) & 0xFF) < fov) {
            D_800D154C->unkA8 = i + 0x80;
            best = d;
        }
    }
    if (D_800D154C->unkA8 != 0) {
        D_800D154C->unk218 = (struct216 *)func_1507BB28(0, D_800D1893);
        D_800D154C->unk218--;
        if (D_800D1892 != 0) {
            t = &D_800CC2D0[D_800D154C->unkA8 & 0x7F];
            t->unk218 = NULL;
            t->unk232 = D_800D1892;
            t->unk222 = self;
        }
    }
}
