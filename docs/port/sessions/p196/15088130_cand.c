extern s8 D_800D27C9;
void func_15089664(u8 *rec, u8 *player);
void func_15089B68(u8 *rec, u8 *player, s32 release);

// rail_cameras_update: clears D_800D27C9 and runs the rail camera of each of the D_800D27B8 player records
// (D_80087640, 0x84 bytes) whose player (D_800CC2D0 + rec[0x31]) has a camera (+0x318): records in state 2 or more
// (rec[0x30]) follow the rail (func_15089664), the others with rec[0x48] == 0 run the spline camera
// (func_15089B68), and the rest release the spline camera once while rec[0x49] is set.
void func_15088130(void) {
    u8 *rec;
    u8 *player;
    s32 i;

    D_800D27C9 = 0;
    if (D_80087640 == NULL) {
        return;
    }
    for (i = 0; i < D_800D27B8; i++) {
        rec = (u8 *) D_80087640 + i * 0x84;
        player = (u8 *) &D_800CC2D0[(s8) rec[0x31]];
        if (*(s32 *) (player + 0x318) == 0) {
            continue;
        }
        if ((s8) rec[0x30] >= 2) {
            func_15089664(rec, player);
        } else if (rec[0x48] == 0) {
            func_15089B68(rec, player, 0);
        } else if ((s8) rec[0x49] != 0) {
            func_15089B68(rec, player, 1);
        }
    }
}
