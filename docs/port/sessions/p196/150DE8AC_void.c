extern u8 D_80088CF0[8];
extern u8 D_80088CF8[8];
s32 func_150A3794(u8 *, s32, s32, s32);
u8 *func_151149AC(u8);
void func_150A2D44(s32, s32);

// trigger_zones_check: hit callback (D_800E0D64, set in game_3DC30) for the point (x, y, z): for each of
// the 8 zones D_80088CF0 (D_800D34B8 records of 0x34 bytes) that contains it (func_150A3794), the matching
// D_80088CF8 object id gets state 3 in its +0x73 low bits (func_151149AC), or the zone itself is triggered
// (func_150A2D44(zone, 1)) when the id is 0. Returns 0 (the asm leaves the last helper's v0; the caller
// ignores it).
void func_150DE8AC(s32 x, s32 y, s32 z) {
    u8 *obj;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (func_150A3794(D_800D34B8 + D_80088CF0[i] * 0x34, x, y, z) != 0) {
            if (D_80088CF8[i] != 0) {
                obj = func_151149AC(D_80088CF8[i]);
                obj[0x73] = (obj[0x73] & ~3) | 3;
            } else {
                func_150A2D44(D_80088CF0[i], 1);
            }
        }
    }
}
