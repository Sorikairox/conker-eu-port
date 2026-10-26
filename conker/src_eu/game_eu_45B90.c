#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_eu_800BE9F4;   /* PVS row index: per row {s16 byte index, s16 bit} */
extern s32 D_eu_800BE9F8;   /* Huffman tree: 6-byte nodes {s16 symbol (-1: inner), s16 child 0, s16 child 1} */
u8 *allocate_memory(s32, s32, s32, s32);
void pvs_build_huffman_tree(s32 *table);

/* PVS setup (hand asm): builds the Huffman tree from `table` (pvs_build_huffman_tree), keeps the bit stream in
 * D_800BE5D0 and records, for each of `rows` rows, where the row starts in the stream ({byte index, bit}; the
 * first row is {-1, 0}). A row is `rowlen` symbols; bits are read MSB first. Both loops are do-while, as in the asm. */
/* was func_150183D0 */
void pvs_setup(s32 rowlen, s32 rows, s32 stream, s32 table) {
    s16 *ix;
    s16 *node;
    u8 *p;
    s32 byte;
    s32 bit;
    s32 row;
    s32 k;
    u32 cur;

    pvs_build_huffman_tree((s32 *) table);
    D_800BE5D0 = stream;
    ix = (s16 *) allocate_memory(rows * 4, 1, 0, 0);
    D_eu_800BE9F4 = (s32) ix;
    p = (u8 *) stream;
    byte = -1;
    bit = 0;
    row = 0;
    cur = 0;
    do {
        k = 0;
        ix[0] = byte;
        ix[1] = bit;
        ix += 2;
        do {
            node = (s16 *) D_eu_800BE9F8;
            while (node[0] < 0) {
                if (bit == 0) {
                    cur = *p++;
                    byte++;
                    bit = 7;
                } else {
                    bit--;
                }
                node = (s16 *) (D_eu_800BE9F8 + (((cur >> bit) & 1) ? node[2] : node[1]));
            }
            k++;
        } while (k != rowlen);
        row++;
    } while (row != rows);
}

/* (hand asm, called with the caller's registers) Huffman tree for 256 symbols: table[0] is the tree size in bytes,
 * then per symbol {u32 code, u32 length} (length 0: unused). Codes are inserted MSB first from the root
 * {-1, 0, 0}; a leaf met on the way is pushed down (copied to a new node) until the two codes differ.
 * Shift counts use the low 5 bits (srlv / sllv). */
/* was func_150184B0 */
void pvs_build_huffman_tree(s32 *table) {
    s16 *nodes;
    s16 *next;
    s16 *node;
    s16 *parent;
    s16 *a;
    s16 *b;
    u32 *e;
    u32 *base;
    u32 code;
    u32 ocode;
    s32 olen;
    s32 depth;
    s32 bit;
    s32 obit;
    s32 i;
    s32 off;
    s32 sym;

    nodes = (s16 *) allocate_memory(table[0], 1, 0, 0);
    D_eu_800BE9F8 = (s32) nodes;
    base = (u32 *) &table[1];
    e = base;
    next = nodes + 3;
    nodes[0] = -1;
    nodes[1] = 0;
    nodes[2] = 0;
    sym = 0;
    do {
        code = e[0];
        i = e[1];
        if (i != 0) {
            i--;
            node = nodes;
            for (;;) {
                bit = code & (1 << (i & 31));
                if (node[0] == -1) {
                    parent = node;
                    off = bit ? node[2] : node[1];
                    if (off == 0) {
                        node = next;
                        next += 3;
                        node[0] = sym;
                        node[1] = 0;
                        node[2] = 0;
                        if (bit) {
                            parent[2] = (u8 *) node - (u8 *) nodes;
                        } else {
                            parent[1] = (u8 *) node - (u8 *) nodes;
                        }
                        break;
                    }
                    node = (s16 *) ((u8 *) nodes + off);
                    if (i == 0) {
                        break;
                    }
                    i--;
                    continue;
                }
                ocode = base[(u16) node[0] * 2];
                olen = base[(u16) node[0] * 2 + 1];
                depth = e[1] - i;
                for (;;) {
                    bit = (code >> (i & 31)) & 1;
                    obit = (ocode >> ((olen - depth) & 31)) & 1;
                    if (bit != obit) {
                        break;
                    }
                    depth++;
                    i--;
                    a = next;
                    next += 3;
                    a[0] = node[0];
                    a[1] = node[1];
                    a[2] = node[2];
                    node[0] = -1;
                    if (obit) {
                        node[1] = 0;
                        node[2] = (u8 *) a - (u8 *) nodes;
                    } else {
                        node[1] = (u8 *) a - (u8 *) nodes;
                        node[2] = 0;
                    }
                    node = a;
                }
                a = next;
                next += 3;
                a[0] = node[0];
                a[1] = node[1];
                a[2] = node[2];
                b = next;
                next += 3;
                b[0] = sym;
                b[1] = 0;
                b[2] = 0;
                node[0] = -1;
                if (obit) {
                    node[1] = (u8 *) b - (u8 *) nodes;
                    node[2] = (u8 *) a - (u8 *) nodes;
                } else {
                    node[1] = (u8 *) a - (u8 *) nodes;
                    node[2] = (u8 *) b - (u8 *) nodes;
                }
                break;
            }
        }
        e += 2;
    } while (sym++ != 0xFF);
}
