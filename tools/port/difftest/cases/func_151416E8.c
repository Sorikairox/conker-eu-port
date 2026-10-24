extern void (*D_8008A3CC[])(u8 *, u8 *, s32);

// effect_message_dispatch: message handler of an effect record (P151). Forwards (rec, msg, code) to the type's
// handler D_8008A3CC[rec +0x168] when there is one; then for messages addressed to this type (msg[0] == +0x168):
// 0x22 frees the record (func_1516972C), 0x24 / 0x25 set its state +0x169 to -1 / 2.
void func_151416E8(u8 *rec, u8 *msg, s32 code) {
    u8 c = code;

    if (D_8008A3CC[rec[0x168]] != NULL) {
        D_8008A3CC[rec[0x168]](rec, msg, c);
    }
    if ((c == 0x22 || c == 0x24 || c == 0x25) && msg[0] == rec[0x110 + 0x58]) {
        if (c == 0x22) {
            func_1516972C((struct102 *)rec);
        } else if (c == 0x24) {
            rec[0x110 + 0x59] = -1;
        } else {
            rec[0x110 + 0x59] = 2;
        }
    }
}
