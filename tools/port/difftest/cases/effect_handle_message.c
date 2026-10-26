extern void (*g_effect_msg_fns[])(u8 *, u8 *, s32); /* was D_8008A3CC */

// effect_message_dispatch: message handler of an effect record (P151). Forwards (rec, msg, code) to the type's
// handler g_effect_msg_fns[rec +0x168] when there is one; then for messages addressed to this type (msg[0] == +0x168):
// 0x22 frees the record (node_destroy), 0x24 / 0x25 set its state +0x169 to -1 / 2.
void effect_handle_message(u8 *rec, u8 *msg, s32 code) {
    u8 c = code;

    if (g_effect_msg_fns[rec[0x168]] != NULL) {
        g_effect_msg_fns[rec[0x168]](rec, msg, c);
    }
    if ((c == 0x22 || c == 0x24 || c == 0x25) && msg[0] == rec[0x110 + 0x58]) {
        if (c == 0x22) {
            node_destroy((struct102 *)rec);
        } else if (c == 0x24) {
            rec[0x110 + 0x59] = -1;
        } else {
            rec[0x110 + 0x59] = 2;
        }
    }
}
