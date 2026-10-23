void func_15042D94(s32, s32, u8, s32, ...);
extern char D_8009E090[]; /* "%d" */
extern char D_8009E094[]; /* ":%02d" */
extern char D_8009E09C[]; /* ":%02d" */
extern char D_8009E0A4[]; /* "--" */
extern char D_8009E0A8[]; /* ": --" */
extern char D_8009E0B0[]; /* ": --" */

// hud_time_draw: P153: draws a time of `ticks` (50 per second, at most 99:00.00) as minutes ":" seconds ":"
// hundredths at (x, y) with alpha (func_15042D94); the minutes field moves 5 left from 10 minutes on. A negative
// time draws "--: --: --".
void func_150916B4(s32 x, s32 y, s32 ticks, u8 alpha) {
    s32 hundredths;
    s32 seconds;
    s32 minutes;
    s32 shift;

    if (ticks >= 297000) {
        ticks = 297000;
    }
    hundredths = (ticks % 50) * 100 / 50;
    if (hundredths >= 100) {
        hundredths = 99;
    }
    x -= 8;
    if (ticks >= 0) {
        seconds = ticks / 50;
        minutes = seconds / 60;
        if (minutes >= 10) {
            shift = 5;
        } else {
            shift = 0;
        }
        func_15042D94(x - shift - 8, y, alpha, (s32) D_8009E090, minutes);
        func_15042D94(x, y, alpha, (s32) D_8009E094, seconds % 60);
        func_15042D94(x + 0x10, y, alpha, (s32) D_8009E09C, hundredths);
        return;
    }
    func_15042D94(x - 8, y, alpha, (s32) D_8009E0A4);
    func_15042D94(x, y, alpha, (s32) D_8009E0A8);
    func_15042D94(x + 0x10, y, alpha, (s32) D_8009E0B0);
}
