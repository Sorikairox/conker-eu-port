int func_1507BB28(s32, s32);
extern f32 D_8009A5A4; /* 0.7 */

// follow_player_speed: P210: script command: when player 1 (D_800CC2D0[0]) rides nothing (unk65 0) or is slower
// than 5, jumps the current object's script to D_800D1891 (unk232, script pointer func_1507BB28 - one entry);
// otherwise copies the player's controller heading (unk31C +0x4C) into unk78 and starts func_15075F40 with speed
// parameter D_800D1892 = player speed (times 0.7 unless the player is chased), D_800D1893 + 1 and D_800D1890 = 8
// below 17; sets flag 0x40 in unkF4.
void func_15079FBC(void) {
    struct127 *player = &D_800CC2D0[0];
    s16 speed;

    if (player->unk65 == 0 || player->unk44 < 5.0f) {
        D_800D154C->unk232 = D_800D1891;
        D_800D154C->unk218 = (struct216 *)func_1507BB28(0, D_800D154C->unk232);
        D_800D154C->unk218--;
        return;
    }
    D_800D154C->unk78 = player->unk31C->unk4C;
    if (player->unk31C->chased != 0) {
        speed = player->unk44;
    } else {
        speed = player->unk44 * D_8009A5A4;
    }
    if (speed < 17) {
        D_800D1893++;
        D_800D1890 = 8;
    }
    D_800D1892 = speed;
    func_15075F40();
    D_800D154C->unkF4 |= 0x40;
}
