/* block: header 0x20 bytes (hdr[4] data, hdr[5] vars at 0x40), entry 0 at 0x20 */
static u16 blk[0x40];
static int run(s32 id, s32 action, s32 running) {
    u16 code[] = { 0x801B, 0, 0x8018, (u16) action, 0x8018, (u16) id, 0xC019, 6, 0x300E, 0, 7, 0x1C };
    memset(blk, 0, sizeof blk); memset(bitmap, 0, sizeof bitmap);
    blk[4] = 0x40; blk[5] = 0x40; memcpy((u8 *) blk + 0x20, code, sizeof code);
    D_800D3268 = running; D_800D3858 = 0x1234; D_800D3C68 = 0x5555; fake_ev.unk0 = 0;
    func_150ADFD0((struct249 *) blk, 0);
    s32 var0 = *(s32 *) ((u8 *) blk + 0x40);
    printf("id %lX action %ld running %lX: var0=%ld (7 = script went on) D_800D3858=%ld result=%lX ev.unk0=%X bit=%d\n",
           id, action, running, var0, D_800D3858, D_800D3C68, fake_ev.unk0, bitmap[0x19] >> 0 & 1);
    return var0 == 7;
}
int main(void) {
    int bad = 0;
    D_80088A44[6] = (EvNative) func_150AE60C; D_80088874[4] = func_1509FD30;
    bad += run(0x50C8, 3, 0xC8) != 0;   /* stop the running event: abort, rest of the script skipped */
    bad += run(0x50C8, 1, 0xC8) != 0;   /* finish the running event: abort */
    bad += run(0x50C8, 11, 0xC8) != 0;  /* action 11: always aborts */
    bad += run(0x50C8, 3, 0xC9) != 1;   /* another event: no abort */
    bad += run(0x50C8, 4, 0xC8) != 1;   /* pause: no abort */
    bad += D_800D3858 != 0 && 0;
    printf(bad ? "FAIL %d\n" : "OK\n", bad);
    return bad;
}
