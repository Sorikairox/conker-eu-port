#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 osPiRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size) {
    register u32 stat;

    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS((u32)osRomBase | devAddr));
    switch (direction) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
    }
    return 0;
}

// osEPiRawStartDma
/* was func_10023DA0 */
s32 os_epi_raw_start_dma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size) {
    register u32 stat;

    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS(pihandle->baseAddress | devAddr));
    switch (direction) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
    }
    return 0;
}

#ifdef NON_MATCHING
/* P279: readable C for libultra's hand-asm bcopy (also replaced on PC by port/ultra/pc_libc.c vbe.bcopy). The asm
 * also returns dst in v0; the libultra prototype is void (v0use.py: only swarm_spawn passes it on as its own
 * return value, and nothing reads that). */
// bcopy: memmove(dst, src, n) for n >= 0: copies forward when dst is below src or past the source's end (signed
// address compares, as the asm), backward otherwise, so overlapping ranges are safe. The asm's word / 16-byte
// blocks for co-aligned ranges only change speed.
void bcopy(const void *src, void *dst, int n) {
    const u8 *s = src;
    u8 *d = dst;

    if (n == 0 || s == d) {
        return;
    }
    if ((s32) d < (s32) s || (s32) d >= (s32) s + n) {
        while (n-- > 0) {
            *d++ = *s++;
        }
    } else {
        s += n;
        d += n;
        while (n-- > 0) {
            *--d = *--s;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_23CC0/bcopy.s")
#endif

/* was func_10024190 */
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_23CC0/os_writeback_dcache.s")
