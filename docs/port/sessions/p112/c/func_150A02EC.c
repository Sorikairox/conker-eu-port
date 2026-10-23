struct249 *func_1509B704(s16 arg0);
f32 func_150ADA68(void);
s32 func_151E6710(s32 arg0);
s32 func_1517F51C(s32 arg0);
extern s32 D_800D3C60;          /* values pushed for the current native call */
extern s8 D_800E0FE1;
extern u16 D_8009015C;
extern u16 D_800BED50[];
extern u16 D_800BED38[][3];
extern u8 D_800D3260;

/* event_query_game_state: game-state queries of the event scripts (native 5, D_80088838 entry 4, ids 0x5xxx), the
 * result goes to the VM's result register. id = the event id (for the event queries), args = the VM stack
 * (args[2].. = values pushed below the id and the query). */
s32 func_150A02EC(s32 id, s32 query, s32 *args) {
    s32 mask;
    s32 sum;
    s32 pick;
    s32 i;

    switch (query) {
        case 0x1A: /* the event's done bit */
            return ((u8 *) D_800D2E4C)[id >> 3] & (1 << (id & 7));
        case 0x1B: /* the event's state word (no NULL check in the asm) */
            return ((u16 *) func_1509B704(id))[1];
        case 0x1C:
            return D_800BE9F0;
        case 0x1D: /* bit mask of the D_8008FD8C slots whose D_80087270 byte is not 10, minus the D_800D18A0 bits */
            mask = 0;
            for (i = 0; i < D_8008FD8C; i++) {
                if (D_80087270[i] != 10) {
                    mask |= 1 << i;
                }
            }
            return mask & ~D_800D18A0;
        case 0x1E:
            return func_151E6710(args[2]);
        case 0x1F:
            return D_800BE9F8;
        case 0x20:
            return (s8) D_800BE3DF;
        case 0x21:
            return D_800BE800;
        case 0x22: /* weighted random pick: args[2] weights follow in args[3..] */
            sum = 0;
            for (i = 0; i < args[2]; i++) {
                sum += args[3 + i];
            }
            pick = func_150ADA68() * (f32) sum;
            sum = 0;
            for (i = 0; i < args[2]; i++) {
                sum += args[3 + i];
                if (sum >= pick && args[3 + i] != 0) {
                    return i;
                }
            }
            return args[2] - 1;
        case 0x23:
            return D_80090130;
        case 0x24:
            return D_800E0FE1;
        case 0x25:
            return D_8009015C & 0x10;
        case 0x26:
            return D_8008FD8C;
        case 0x27:
            return D_800BED50[args[2]];
        case 0x28:
            return D_800BED38[args[2]][0];
        case 0x29: /* game mode 2 */
            return D_800E0B94 == 2;
        case 0x2A:
            return args[2] & D_800E9D00;
        case 0x2B: /* the event is not paused (0x2000 clear); no event: 0 */
            {
                struct249 *ev = func_1509B704(id);

                if (ev == NULL) {
                    return 0;
                }
                return (ev->unk0 & 0x2000) == 0;
            }
        case 0x2C:
            return func_1517F51C((D_800D3C60 == 3) ? args[2] : 0);
        case 0x2D:
            return D_800D3260;
    }
    return 0;
}
