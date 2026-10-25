/* P281: readable C for func_15007830 (game entry point, compiled C, 128 insns; replaces the commented US draft
   below). Verified with difftest up to the N-th frame (DIFFTEST_STOPCALL on func_150186D0): the loop never returns. */
extern s32 D_800D3048;
extern OSMesgQueue D_800BEE30;   /* main message queue */
extern OSMesg D_800BEE48[16];
extern s16 D_800BEE88[];         /* two s16 fields at 0x00 and 0x20 */
extern u8 D_800BEA37;
extern u8 D_800BEA35;            /* frame state: 1-5 run the frame steps, 0 / 4 idle */
extern u8 D_800BEECA;
extern u8 D_800BEECB;
extern s16 D_800BEEC8;
extern s32 D_800BEE24;
extern s32 D_800BEE20;
extern s32 D_800BEE08;
void func_15003570(void);
void func_10008180(void);
void func_15016588(void);
void func_151EF7B0(void);
void func_15006234(void);
void func_151DDF20(void);
void func_150158D0(s16 idx);
void func_151E582C(void);
void func_15017498(void);
void func_150ADACC(s32 arg0);
void func_15007B3C(void);
void func_150186D0(void);
// game_main: the game thread's entry. Initialises the subsystems and the message queue, then loops forever: frame
// states 1 / 5 run func_151E582C, then (from 2) the frame update, the 0x81280783 hook in mode 2 and func_15007A70
// with the low halves of D_800BEE24 / D_800BEE20 / D_800BE9F4, then (from 3) func_15007B3C and the state goes back
// to 0; every pass ends with func_100051E8, D_800BEE08 = 0 and func_150186D0.
void func_15007830(void) {
    func_15007A20();
    D_800D3048 = 0;
    osCreateMesgQueue(&D_800BEE30, D_800BEE48, 16);
    D_800BEE88[0] = 2;
    D_800BEE88[0x10] = 2;
    D_800BEA37 = 0;
    func_100050A0(&D_800BEE30);
    func_15003570();
    D_800BEECB = 0;
    func_10008180();
    func_15000000();
    func_15016588();
    func_151EF7B0();
    D_800BEEC8 = 0;
    func_150061B0();
    func_15006234();
    func_151DDF20();
    func_150158D0(0);
    func_15008A60();
    func_15042D50();
    D_800BEA35 = 5;
    D_800BEE24 = 0;
    D_800BEE20 = 1;
    D_800BEECA = 1;
    func_1509C120();
    while (TRUE) {
        switch (D_800BEA35) {
            case 1:
            case 5:
                func_151E582C();
                /* fallthrough */
            case 2:
                func_15017498();
                if (D_800E0B94 == 2) {
                    func_150ADACC(0x81280783);
                }
                /* D_800BE9F4 is declared `u16 *` in variables.h; the code reads the low half of the word */
                func_15007A70((s16) D_800BEE24, (s16) D_800BEE20, ((s16 *) &D_800BE9F4)[1]);
                /* fallthrough */
            case 3:
                func_15007B3C();
                D_800BEA35 = 0;
                break;
        }
        func_100051E8();
        D_800BEE08 = 0;
        func_150186D0();
    }
}
