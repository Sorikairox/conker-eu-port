/* N64 memory model of the wasm build (docs/port/MEMORY.md).
 *
 * Game memory is "virtual big-endian": every aligned 32-bit word holds its N64 (big-endian) value
 * as a native i32. Game TUs get this for free (port/tools/vbe.py rewrites their IR). PC-layer code
 * that touches *sub-word* fields of game memory must use the vbe_* helpers below; 32-bit fields and
 * pointers are plain native accesses.
 *
 * N64 data lives at its N64 offset inside two mirror arrays (KSEG0 RDRAM, TLB 0x16 segment);
 * pointers stored in that data are rewritten to wasm addresses at load time (port_mem_load).
 * Safe to include from game TUs and PC TUs (no libc headers). */
#ifndef PC_MEM_H
#define PC_MEM_H

typedef struct { unsigned n64; void *fn; const char *name; } PortFn;
typedef struct { unsigned n64; unsigned size; void *p; const char *name; } PortCData;

extern unsigned char n64_rdram[0x800000]; /* KSEG0 0x80000000 / KSEG1 0xA0000000 / physical 0 */
extern unsigned char n64_seg16[0x10000];  /* TLB-mapped 0x16000000 (debugger data) */

void *port_n64_to_wasm(unsigned n64addr);      /* data or function; 0 if unknown */
unsigned port_wasm_to_n64(const void *p);      /* inverse for mirror addresses; 0 otherwise */
int port_mem_load(void);                       /* copy data segments from the ROM + relocate */
void port_rom_read(void *dst, unsigned romoff, unsigned size); /* ROM -> game memory (vbe layout) */
int port_inflate_raw(unsigned char *out, unsigned outlen, const unsigned char *in, unsigned inlen);

#define VBE8(p)  ((unsigned char *)((unsigned long)(p) ^ 3))
#define VBE16(p) ((unsigned short *)((unsigned long)(p) ^ 2))
static inline unsigned vbe_ld8(const void *p) { return *VBE8(p); }
static inline void vbe_st8(void *p, unsigned v) { *VBE8(p) = (unsigned char)v; }
static inline unsigned vbe_ld16(const void *p) { return *VBE16(p); }  /* p 2-aligned */
static inline void vbe_st16(void *p, unsigned v) { *VBE16(p) = (unsigned short)v; }

#endif
