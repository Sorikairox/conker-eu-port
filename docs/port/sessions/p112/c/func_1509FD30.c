struct249 *func_1509B704(s16 arg0);
struct249 *func_1509B5AC(s32 id, s32 arg1);
void func_150AE760(void);
void func_1501C710(s32, s32, s32, s32, s32);
void func_151733EC(struct127 *arg0, s32 arg1, s32 arg2);
void func_1517F3B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5);
void func_151E5B94(s32 arg0);
void func_151E89C0(void);
void func_151E5528(void);
void func_15042E3C(s32 arg0, ...);
extern s32 D_800D3268;          /* id of the event the VM is running */
extern s32 D_800D3378;          /* save bits changed */
extern s32 D_800D3C60;          /* values pushed for the current native call */
extern u8 D_800877B0[];
extern s32 D_800D3420;
extern s32 D_800D3424;
extern char D_8009F870[];       /* "%d" */

/* event_action_game_state: game-state actions of the event scripts (native 6, D_80088874 entry 4, ids 0x5xxx).
 * id = the event id the action applies to (call id without the nibble), args = the VM stack (args[2].. = values
 * pushed below the id and the action). Actions 1 / 3 / 11 abort the running script when they stop the event that
 * runs it: `func_150AE760(); return 0;` must stay at both sites (the VM checks the abort flag after the call). */
s32 func_1509FD30(s32 id, s32 action, s32 *args) {
    u8 *bits;
    struct249 *ev;
    s32 i;

    switch (action) {
        case 1: /* finish the event: set its done bit, then as 3 */
            if (D_800877B0[1] != 0) {
                D_800877B0[1] = 0;
                return 0;
            }
            bits = (u8 *) D_800D2E4C + (id >> 3);
            *bits |= 1 << (id & 7);
            D_800D3378 = 1;
            D_800D2E43 = 1;
            /* fallthrough */
        case 3: /* stop the event (abort when it is the one running) */
            ev = func_1509B704(id);
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x8000;
            if (id == D_800D3268) {
                func_150AE760();
                return 0;
            }
            return 1;
        case 2: /* stop the event and keep only its done bit (as the asm: byte & 7 & bit) */
            ev = func_1509B704(id);
            bits = (u8 *) D_800D2E4C + (id >> 3);
            *bits = (*bits & 7) & (1 << (id & 7));
            D_800D3378 = 1;
            D_800D2E43 = 1;
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x8000;
            return 1;
        case 4: /* pause the event */
            ev = func_1509B704(id);
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x4000;
            return 1;
        case 5: /* clear the event's variables */
            ev = func_1509B704(id);
            if (ev == NULL) {
                return 0;
            }
            bzero((u8 *) ev + ((u16 *) ev)[5], ((u16 *) ev)[3]);
            return 0;
        case 6: /* start the event */
            func_1509B5AC(id, 0);
            return 0;
        case 7: /* change level (four values pushed) */
            if (D_800D3C60 == 4) {
                func_1501C710(2, args[2], args[3], 0, 0);
            }
            return 0;
        case 8:
            if (D_800D3C60 == 4) {
                func_151733EC(D_800CC2D0, args[2] & 0xFFF, args[3] & 0xFFF);
            }
            return 0;
        case 9: /* set / clear a bit of D_800D2E60 */
            D_800D3289 = 1;
            bits = &D_800D2E60[args[3] >> 3];
            if (args[2] != 0) {
                *bits |= 1 << (args[3] & 7);
            } else {
                *bits = (*bits & 7) & (1 << (args[3] & 7));
            }
            D_800D2E43 = 1;
            return 0;
        case 10:
            func_151E5B94(args[2]);
            return 0;
        case 11: /* finish the event, func_151E5B94(0) and abort the running script */
            ev = func_1509B704(id);
            bits = (u8 *) D_800D2E4C + (id >> 3);
            *bits |= 1 << (id & 7);
            D_800D3378 = 1;
            D_800D2E43 = 1;
            if (ev == NULL) {
                return 0;
            }
            ev->unk0 |= 0x8000;
            func_151E5B94(0);
            func_150AE760();
            return 0;
        case 12: /* timer start: both stamps, or only the first */
            if (args[2] < 0) {
                D_800D3420 = D_800D3424 = osGetCount();
            } else {
                osGetCount();
                D_800D3420 = osGetCount();
            }
            return 0;
        case 13:
            D_800DDE38 = 1;
            return 0;
        case 14:
            D_800E9D00 |= args[2];
            return 0;
        case 15:
            if (args[3] == 0) {
                D_800D2120 &= ~(1 << args[2]);
            } else {
                D_800D2124 &= ~(1 << args[2]);
            }
            return 0;
        case 16:
            if (args[3] == 0) {
                D_800D2120 |= 1 << args[2];
            } else {
                D_800D2124 |= 1 << args[2];
            }
            return 0;
        case 17:
            func_1517F3B0(0, 0, 0, 0, 1, 0);
            return 0;
        case 18:
            for (i = 0; i <= D_80082FA0; i++) {
                func_1517F3B0(args[2], args[3], args[4], args[5], args[6], i);
            }
            return 0;
        case 19:
            D_800BE3DF = args[2];
            D_800BE800 = args[3];
            *(s32 *) &D_800BE9F4 = (s8) D_800BE3DF;
            return 0;
        case 20: /* attract idle check (-> mode 8) */
            func_151E89C0();
            return 0;
        case 21: /* -> mode 10 */
            func_151E5528();
            return 0;
        case 22: /* debug print */
            func_15042E3C((s32) D_8009F870, args[2]);
            return 0;
        case 23:
            D_800D2E44 = (args[2] != 0) ? 1 : 0;
            return 0;
    }
    return 0;
}
