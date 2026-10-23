#define L6AC_PREV(n) (*(u8 **)((n) + 4))
#define L6AC_NEXT(n) (*(u8 **)((n) + 8))
#define L6AC_KEY(n) (((n)[0x18] << 8) + (*(s32 *)((n) + 0x20) >> 16))

/* Insertion sort of scene-node list D_800DD280[group][idx] by key (+0x18 << 8) + (+0x20 >> 16), ascending, stable;
 * a node moves behind the last earlier node whose key is not greater. A stack node stands in for the list head
 * (key 0, no prev); as in the asm the head's prev is set before the NULL test and the first node's prev is cleared
 * at the end, so an empty list writes word 4. `skip` != 0: nothing. Returns `ret` (a0) unchanged. */
s32 func_151406AC(s32 ret, s32 idx, s32 group, s16 skip) {
    s32 dummy[9];
    u8 *d = (u8 *)dummy;
    u8 **slot;
    u8 *head;
    u8 *node;
    u8 *prev;
    u8 *next;
    u8 *at;
    s32 key;

    if (skip != 0) {
        return ret;
    }
    slot = (u8 **)((u8 *)D_800DD280 + group * 0x1A0 + idx * 4);   /* D_800DD280[2][104] list heads */
    head = *slot;
    d[0x18] = 0;
    dummy[8] = 0;
    L6AC_PREV(d) = NULL;
    L6AC_NEXT(d) = head;
    L6AC_PREV(head) = d;
    if (head != NULL) {
        for (node = L6AC_NEXT(head); node != NULL; node = next) {
            key = L6AC_KEY(node);
            prev = L6AC_PREV(node);
            next = L6AC_NEXT(node);
            for (at = prev; at != NULL; at = L6AC_PREV(at)) {
                if (!(key < L6AC_KEY(at))) {
                    break;
                }
            }
            if (at == NULL || at == prev) {
                continue;
            }
            L6AC_NEXT(prev) = next;
            if (L6AC_NEXT(node) != NULL) {
                L6AC_PREV(L6AC_NEXT(node)) = L6AC_PREV(node);
            }
            L6AC_NEXT(node) = L6AC_NEXT(at);
            if (L6AC_NEXT(node) != NULL) {
                L6AC_PREV(L6AC_NEXT(node)) = node;
            }
            L6AC_PREV(node) = at;
            L6AC_NEXT(at) = node;
        }
    }
    *slot = L6AC_NEXT(d);
    L6AC_PREV(L6AC_NEXT(d)) = NULL;
    return ret;
}
