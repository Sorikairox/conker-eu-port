# P145: setups for func_1513095C (particle_update). obj 0x80490000; tables from ROM (DIFFTEST_ROMDATA=1).
def setup(name, flags, timer=5, frame=0x100, spd=0, anim=0, h=0, dh=0, ticks=2, ret='1', alpha=0xFF, a30=3, t2e=0x10, t32=0x10):
    w = {0x18: (0x1234 << 16) | (timer & 0xFFFF), 0x1C: frame & 0xFFFFFFFF, 0x20: spd & 0xFFFFFFFF, 0x28: alpha,
         0x2C: 0x10000000 | (anim << 16) | t2e, 0x30: (a30 << 16) | t32, 0x34: 0x3F8CCCCD, 0x38: 0x3F800000,
         0x3C: 0x40000000, 0x40: 0x41200000, 0x44: 0x41A00000, 0x48: 0x41F00000, 0x58: 0x3F800000, 0x5C: 0x40000000,
         0x60: 0x40400000, 0x64: 0xBF800000, 0x68: flags, 0x70: ((h & 0xFF) << 8) | (dh & 0xFF)}
    poke = ','.join('%X=%08X' % (0x80490000 + k, v) for k, v in sorted(w.items()))
    poke += ',800BEE04=%08X,800BEDC4=3F000000' % (ticks & 0xFFFFFFFF)
    print('%s ! 0=80490000 ! %s ! 151A4DEC=%s' % (name, poke, ret))
for nm, f in (('add', 0x607), ('mul', 0xE07), ('mul38', 0x80E07), ('mul3C', 0x100E07), ('add38', 0x80607), ('add3C', 0x100607),
              ('none', 0), ('only1', 1), ('only2', 2), ('only4', 4), ('a200', 0x200), ('a400', 0x400)):
    setup(nm, f)
setup('mul_t5', 0xE07, ticks=5); setup('mul_t0', 0xE07, ticks=0); setup('mul_t7', 0xE07, ticks=7)
setup('alpha_lo', 0x200, alpha=0x02); setup('alpha_eq', 0x200, timer=0x10, t2e=0x10)
setup('timer_hi', 0x601, timer=0x20); setup('dead', 0x607, timer=1); setup('dead_nodh', 0x607, timer=1, dh=-1)
setup('hret0', 0x607, ret='0'); setup('noh', 0x607, h=-1); setup('noh_dead', 0x607, h=-1, timer=1)
for nm, f in (('end_die', 0x10), ('end_bnc', 8), ('end_wrap', 0), ('end_bnc_die', 0x18)):
    setup(nm, f, frame=0xFFF0, spd=0x10)
setup('end_wrap3', 0, frame=0xFFF0, spd=0x10000); setup('end_bnc_big', 8, frame=0xFFF0, spd=0x18000)
for nm, f in (('st_die', 0x20), ('st_bnc', 8), ('st_wrap', 0), ('st_bnc_die', 0x28)):
    setup(nm, f, frame=0x10, spd=-0x20)
setup('st_wrap3', 0, frame=0x10, spd=-0x10000); setup('st_bnc_big', 8, frame=0x10, spd=-0x18000)
setup('anim_dead', 0x11, timer=1, frame=0xFFF0, spd=0x10); setup('anim1', 0, frame=0x100, spd=0x40, anim=1)
setup('anim_eq', 0x10, frame=0xFFFD, spd=1)
setup('t32_only', 0x607, t2e=0x2, t32=0x10); setup('t2e_only', 0x607, t2e=0x10, t32=0x2)
setup('end_eq', 0, frame=0x1FFDE, spd=0x10); setup('st_zero', 0, frame=0x20, spd=-0x10); setup('st_m1', 0, frame=0, spd=-0x8000)
