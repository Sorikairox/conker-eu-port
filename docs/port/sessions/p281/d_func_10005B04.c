/* P281: readable C for func_10005B04 (Rare hand asm, 55 insns, with the private entry func_10005E2C = the retry
   label). The two COP0 writes (Context = 0, Wired = 2: two wired TLB entries) have no C form; the port has no TLB
   and its platform layer does the boot setup (tools/port/platform_replaced.tsv). */
extern s16 D_8003C218;           /* size of the code / TLB area in 4 KB pages */
extern u8 *D_8003C21C;           /* last byte of the page bitmap */
extern s16 D_8003C220;
extern s16 D_8003C222;
s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
// tlb_area_init: reserves `pages` 4 KB pages (falling back to the previous page count, and retrying it for as long
// as that fails), keeps the area's physical address in D_8003BE74 and allocates its page bitmap (one bit per page,
// D_8003BE70 .. D_8003C21C).
void func_10005B04(s32 pages) {
    s16 prev;
    s32 area;

    /* COP0: Context = 0, Wired = 2 */
    D_8003C220 = 0x1FC;
    D_8003C222 = 0x3FF;
    prev = D_8003C218;
    while (TRUE) {
        D_8003C218 = pages;
        area = func_10003C6C(pages << 12, 0xFF, 4, 1, 2);
        if (area != 0) {
            break;
        }
        pages = prev;
    }
    D_8003BE74 = area & 0x0FFFFFFF;
    D_8003BE70 = allocate_memory((D_8003C218 + 7) >> 3, 0xFF, 0, 0);
    D_8003C21C = (u8 *) D_8003BE70 + ((D_8003C218 + 7) >> 3) - 1;
}
