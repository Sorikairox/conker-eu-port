/* P281: readable C for func_10001194 (compiled C, 210 insns; EU version of the commented US draft below). It ends
   in func_15007830, which never returns (difftest stubs it, so the whole body is compared). */
extern OSMesgQueue D_8003B578;   /* VI retrace queue (reset path) */
extern OSMesg D_8003BC10[8];
extern OSViMode D_8002AF20;
extern u8 D_80043ED0[];          /* start of the memory cleared at boot (up to 0x80400000) */
extern u8 D_427B0[];             /* ROM: compressed game segment (header word: offset of the code blob) */
extern u8 D_19EDE8[];            /* ROM: end of the compressed game code */
extern u32 D_80082EB0;           /* header word read from D_427B0 */
extern u8 D_80033690[];
extern u8 D_80032E90[];
extern u8 *D_80035858;
extern u32 *D_8003585C;          /* per-4 KB-page offsets of the compressed game code */
extern u8 D_151FA920[];          /* end of the game segment's code */
void func_15000000(void);
void func_15007830(void);
void func_10003570(OSPri pri);
void func_10003BD0(void);
void func_1000738C(void);
void func_10005BE0(void);
s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_10006530(s32 arg0, s32 arg1, u32 arg2);
void func_10004074(s32 arg0);
// boot_thread_main: game boot thread. After a reset (osResetType != 0) the VI manager starts first, otherwise after
// the memory clear; clears memory up to 0x80400000 (after a reset only from the heap), sets up the heap and two
// frame buffers, reads and decompresses the game code's first part, reads the page offset table of the rest
// (decrypted: xor 0x8039CCCA, plus the segment's ROM address), sets up the TLB area (func_10005B04) and enters
// the game (func_15007830, no return).
void func_10001194(s32 arg0) {
    u32 len;
    u32 src;
    s32 size;
    s32 dst;
    u32 npages;
    u32 i;

    if (D_8000030C != 0) {
        osCreateMesgQueue(&D_8003B578, D_8003BC10, 8);
        func_10003570(OS_PRIORITY_VIMGR);
        osViSetMode(&D_8002AF20);
        osViBlack(TRUE);
        osViSetEvent(&D_8003B578, NULL, 1);
    }
    func_10005218();
    if (D_8000030C == 0) {
        len = 0x80400000 - (u32) D_80043ED0;
        bzero(D_80043ED0, len);
    } else {
        bzero(&D_800EA140, 0x80400000 - (u32) &D_800EA140);
        len = 0x80400000 - (u32) D_80043ED0;
    }
    osInvalICache(D_80043ED0, len);
    osInvalDCache(D_80043ED0, len);
    func_10003920();
    func_10003930();
    func_10003BD0();
    func_1000738C();
    D_8002AAE8[0] = func_10003C6C(0x1ECC0, 0xFF, 3, 1, 0);
    D_8002AAE8[1] = func_10003C6C(0x1ECC0, 0xFF, 3, 1, 0);
    if (D_8000030C == 0) {
        osCreateMesgQueue(&D_8003B578, D_8003BC10, 8);
        func_10003570(OS_PRIORITY_VIMGR);
        osViSetMode(&D_8002AF20);
        osViBlack(TRUE);
        osViSetEvent(&D_8003B578, NULL, 1);
    }
    func_10004514((s32) D_427B0, &D_80082EB0, 16, 1);
    src = D_80082EB0 + (u32) D_427B0;
    size = (u32) D_19EDE8 - src;
    dst = allocate_memory(size, 1, 2, 0);
    func_10004514(src, (void *) dst, size, 1);
    func_10006530(dst, (s32) &D_80082EB0, D_8003809C);
    func_10004074(dst);
    npages = ((u32) D_151FA920 - (u32) func_15000000 + 0xFFF) >> 12;
    D_80035858 = (u8 *) (((u32) D_80033690 + 0xF) & ~0xF);
    D_8003585C = (u32 *) (((u32) D_80032E90 + 0xF) & ~0xF);
    func_10004514((s32) D_427B0 + 4, D_8003585C, (((npages + 2) * 4 + 0xF) | 0xF) ^ 0xF, 1);
    for (i = 0; i < npages + 1; i++) {
        D_8003585C[i] = (D_8003585C[i] ^ 0x8039CCCA) + (u32) D_427B0;
    }
    D_8003BE74 = 0;
    func_10005B04(0xEB);
    func_10001420();
    func_10005BE0();
    func_15007830();
}
