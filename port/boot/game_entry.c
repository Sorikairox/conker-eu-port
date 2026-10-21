/* PC version of the game entrypoint func_15007830 (game/entrypoint.c is still GLOBAL_ASM), plus
 * the memory-model self-test (docs/port/MEMORY.md "Endianness test"). Compiled as a game TU, i.e.
 * through the vbe IR pass, so it has the N64's big-endian memory semantics.
 *
 * Translated from asm/nonmatchings/game/entrypoint/func_15007830.s (EU symbols). The main loop's
 * switch is the asm jump table jtbl_80095DE0 read *from the ROM data* (game_data, loaded by
 * port_mem_load): its words are code labels inside func_15007830, which the loader leaves as N64
 * addresses, so this file maps them back to the cases. */
#include <ultra64.h>
#include "../ultra/pc_mem.h"

void port_glog(const char *fmt, ...);
#define port_log port_glog /* format strings live in vbe game memory */
const char *port_gstr(const char *gamestr);

/* data (EU addresses; all live in the n64_rdram mirror) */
extern s32 D_800D3048, D_800BEE24, D_800BEE20, D_800BE9F4, D_800BEE08;
extern OSMesgQueue D_800BEE30;
extern OSMesg D_800BEE48[16];
extern s16 D_800BEE88[];
extern u8 D_800BEA37, D_800BEECB, D_800BEA35, D_800BEECA, D_800E0B94;
extern s16 D_800BEEC8;

/* callees: prototypes must match the wasm signature of the definition (C body or stub) */
void func_15007A20(void);
void func_100050A0(OSMesgQueue *);
void func_15003570(void);
void func_10008180(void);
void func_15000000(void);
void func_15016588(void);
void func_151EF7B0(void);
void func_150061B0(void);
void func_15006234(void);
void func_151DDF20(void);
void func_150158D0(s32);
void func_15008A60(void);
void func_15042D50(void);
void func_1509C120(void);
void func_151E582C(void);
void func_15017498(void);
s32 func_150ADACC(s32);
void func_15007A70(s32, s32, s32);
void func_15007B3C(void);
void func_100051E8(void);
void func_150186D0(void);

int port_entry_iterations;
void port_wait_frame(void); /* main-loop passes (for the log) */

void func_15007830(void) {
    const u32 *jtbl = port_n64_to_wasm(0x80095DE0); /* jtbl_80095DE0_game, 5 entries */
    u32 target;

    port_log("[entry] func_15007830 (PC version) jtbl %08X %08X %08X %08X %08X\n", jtbl[0], jtbl[1],
             jtbl[2], jtbl[3], jtbl[4]);
    func_15007A20();
    D_800D3048 = 0;
    osCreateMesgQueue(&D_800BEE30, D_800BEE48, 16);
    D_800BEE88[0] = 2;     /* sh 0x0(D_800BEE88) */
    D_800BEE88[0x10] = 2;  /* sh 0x20(D_800BEE88) */
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
    port_log("[entry] init sequence done, entering main loop (state %d)\n", D_800BEA35);
    for (;;) {
        u32 idx = (u32)D_800BEA35 - 1;
        target = idx < 5 ? jtbl[idx] : 0x1500797C;
        if (port_entry_iterations++ < 3)
            port_log("[entry] loop state %d -> case %08X\n", D_800BEA35, target);
        switch (target) {
            case 0x1500793C:
                func_151E582C();
                /* fallthrough */
            case 0x15007944:
                func_15017498();
                if (D_800E0B94 == 2) func_150ADACC(0x81280783);
                /* lh 0x2(...): the low halves of three s32 globals (mixed-width access) */
                func_15007A70(((s16 *)&D_800BEE24)[1], ((s16 *)&D_800BEE20)[1], ((s16 *)&D_800BE9F4)[1]);
                /* fallthrough */
            case 0x15007970:
                func_15007B3C();
                D_800BEA35 = 0;
                /* fallthrough */
            case 0x1500797C:
                break;
            default:
                port_log("[entry] jump-table word %08X is not a case label\n", target);
                return;
        }
        func_100051E8();
        D_800BEE08 = 0;
        func_150186D0();
        port_wait_frame(); /* PC: the frame wait happens inside asm stubs today; pace one pass per frame */
    }
}

/* ---------------------------------------------------------------- memory-model self-test */

/* converted game functions (game_eu_CA630.c, game_eu_6EDC0.c) that read ROM-data fields */
s32 func_1509CE20(s32 i);  /* D_800877D0[i].unk0  s32 (a pointer in the data: relocated) */
u16 func_1509CE40(s32 i);  /* D_800877D0[i].unk8  u16 */
s32 func_1509CE60(s32 i);  /* *(u16 *)(&D_800877D0[i] + 0xA) & 0xFFF */
s32 func_1509CE88(s32 i);  /* D_800877D0[i].unk4  s32 */
s32 func_15041770(u8 c);   /* index of c in the u8 table D_80084C60 */
#include "../stubs/memtest_expect.h"

static int fails;
static void check(const char *what, int i, u32 got, u32 want) {
    if (got != want) fails++;
    if (got != want || i < 2)
        port_log("[memtest] %-30s i=%-3d got %08X want %08X %s\n", port_gstr(what), i, got, want,
                 port_gstr(got == want ? "ok" : "FAIL"));
}

int port_memtest(void) {
    int k;
    static s32 word; /* mixed-width semantics on a word written by game code */
    word = 0x12345678;
    check("s32 read as s16[1] (lh +2)", 0, (u16)((s16 *)&word)[1], 0x5678);
    check("s32 read as u8[0] (lbu +0)", 0, ((u8 *)&word)[0], 0x12);
    ((u8 *)&word)[3] = 0x9A;
    check("u8[3] store then s32 read", 0, (u32)word, 0x1234569A);
    for (k = 0; k < MEMTEST_N; k++) {
        const MemtestRow *r = &memtest_rows[k];
        u32 p = (u32)func_1509CE20(r->i), n = port_wasm_to_n64((void *)p);
        check("func_1509CE20 unk0 (ptr)", r->i, n ? n : p, r->unk0); /* relocated back to N64 */
        check("func_1509CE88 unk4 s32", r->i, (u32)func_1509CE88(r->i), r->unk4);
        check("func_1509CE40 unk8 u16", r->i, func_1509CE40(r->i), r->unk8);
        check("func_1509CE60 (u16 +0xA)&0xFFF", r->i, (u32)func_1509CE60(r->i), r->unkA);
    }
    for (k = 0; k < MEMTEST_NC; k++)
        check("func_15041770 u8 table", memtest_chars[k].c, (u32)func_15041770(memtest_chars[k].c), memtest_chars[k].idx);
    port_log("[memtest] %s (%d failures)\n", port_gstr(fails ? "FAIL" : "PASS"), fails);
    return fails;
}
