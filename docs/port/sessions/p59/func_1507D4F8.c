//DROP s32 func_1507D4F8(s32);
//HOIST void func_1507D4F8(s32);
void func_15085710(s16, s16, s32);
s32 func_150859AC(s16 arg0, s32 arg1);
void func_1507D1D8(struct127 *);
void func_1501C710(s32, s32, s32, s32, s32);
void func_1509C3A0(void);
extern u16 D_8009015C;
extern s8 D_8008726C;
extern s8 D_80087260;
extern u8 D_800BE800;
extern s8 D_8008FDA8;
extern s8 D_800E1050;
extern u8 D_800BE616;
extern u16 D_800D18A0;
extern u8 D_800D2E43;
extern u8 D_800D18A8;
extern s8 D_80090134;
extern s8 D_800BEA38;
extern struct127 D_800CC2D0[];

/* A player record (index idx) has lost a life. With lives left (func_150859AC(idx, 3)) the life counter (5) is
 * reset and the record respawns: in multiplayer (D_800BE616) via func_1507D1D8 or a 10-frame timer, else a
 * checkpoint restart (func_1501C710). Out of lives: game over (single player) or the player is marked out in
 * D_800D18A0 (multiplayer); then the active-player counters drop. void: no caller uses a result. */
void func_1507D4F8(s32 idx) {
    struct127 *rec;
    u8 *ctl;

    if (!(D_8009015C & 1)) {
        func_15085710(idx, 4, 1);
    }
    if (func_150859AC(idx, 3) != 0) {
        func_15085710(idx, 5, D_8008726C);
        rec = &D_800CC2D0[idx];
        *(s16 *)((u8 *)rec + 0xB2) = 0;
        if (D_800BE616 != 0) {
            if (D_800E1050 == 0) {
                func_1507D1D8(rec);
                return;
            }
            *((u8 *)rec->unk31C + 0x120) = 10;
            return;
        }
        D_800D18A8 = 1;
        if (!(D_800D2E4C->unk19 & 4) && D_8008FDA8 >= 0) {
            func_1501C710(1, 0x22, 0, 0, 0);
        } else {
            func_1501C710(2, (s8)D_800BE3DF, D_800BE800, 0, 0);
        }
        return;
    }
    if (D_800BE616 == 0) {
        D_800D2E43 = 1;
        func_1509C3A0();
        D_800D18A8 = 1;
        func_15085710(idx, 5, D_8008726C);
        func_15085710(idx, 2, D_80087260);
        func_1501C710(1, 0x18, 0, 0, 0);
    } else {
        D_800D18A0 |= 1 << idx;
    }
    ctl = (u8 *)D_800CC2D0[idx].unk31C;
    if (ctl[0x84] == 0) {
        D_80090134--;
    }
    ctl[0x120] = 10;
    D_800BEA38--;
}
