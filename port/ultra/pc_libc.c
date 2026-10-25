/* libc pieces of the PC libultra layer (session P25).
 *
 * bcopy and bzero are GLOBAL_ASM-only in the decomp (init_eu_23CC0.s, init_eu_22A10.s). Until P25 the
 * game's calls bound to emscripten's musl versions, which copy host bytes: wrong on virtual
 * big-endian game memory whenever the source and destination differ in alignment mod 4, or the
 * length is not a whole number of words (MEMORY.md, "libc"). port/tools/vbe.py (LIBC_VBE) renames the
 * game's references to vbe.bcopy / vbe.bzero, which are defined here on top of the vbe helpers, so
 * emscripten's libc stays untouched for the PC layer.
 *
 * libultra semantics: bcopy(src, dst, n) handles overlap (memmove); bzero(p, n) clears n bytes.
 */
void __vbe_memmove(unsigned char *d, const unsigned char *s, unsigned n);
void __vbe_memset(unsigned char *d, unsigned c, unsigned n);

/* P318: bcopy is game C now (init_eu_23CC0.c, vbe.bcopy via LIBC_VBE); PC copy kept for A/B (-DP318_PC_LIBC_OLD) */
#ifdef P318_PC_LIBC_OLD
void port_bcopy(const void *src, void *dst, int n) __asm__("vbe.bcopy");
void port_bcopy(const void *src, void *dst, int n) {
    if (n > 0) __vbe_memmove(dst, src, (unsigned)n);
}
#endif /* P318_PC_LIBC_OLD */

/* P318: bzero is game C now (init_eu_22A10.c, vbe.bzero via LIBC_VBE); PC copy kept for A/B (-DP318_PC_LIBC_OLD) */
#ifdef P318_PC_LIBC_OLD
void port_bzero(void *p, int n) __asm__("vbe.bzero");
void port_bzero(void *p, int n) {
    if (n > 0) __vbe_memset(p, 0, (unsigned)n);
}
#endif /* P318_PC_LIBC_OLD */
