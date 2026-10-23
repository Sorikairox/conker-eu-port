#!/usr/bin/env python3
# P188: setups for func_15190E08 (drip_emitter_update). e=80400000, owner=80410000, owner matrices=80430000,
# slots=80420000 (12 bytes: obj, timer, next), hanging drop objects 80460000 + 0x200*i.
# EU data: dt int D_800BE9E4 = 800BEE04, dt f32 D_800BE9A4 = 800BEDC4, D_800BEDC8 = 800BEDC8; configs D_8008FE10
# (ROM .data, 4 entries: counts 0x33 / 0x36 / 0x1A / 0x26, max 0x33 / 0x36 / 0x14 / 0x26).
COUNT = [0x33, 0x36, 0x1A, 0x26]
def setup(name, cfg=2, flag=0, timer=100, accum=0x40600000, live=0, idx2c=3, own0=1, oid=5, eid=5, mtx=0x80430000,
          height=0, slots=None, ret='', dt=2):
    p = {0x80400010: 0x80410000, 0x80400014: (eid << 24) | (timer & 0xFFFF), 0x80400018: (flag << 24) | (cfg << 8),
         0x8040001C: accum, 0x80400020: live, 0x80400024: 0x80420000, 0x8040002C: idx2c << 24,
         0x80410000: own0, 0x80410038: oid, 0x804101D4: mtx, 0x80410118: height,
         0x800BEE04: dt, 0x800BEDC4: 0x3F800000, 0x800BEDC8: 0x41F00000}
    for i in range(COUNT[cfg]):
        st = (slots or {}).get(i, slots.get('*', None) if slots else None)
        b = 0x80420000 + 12 * i
        if st is None:
            p[b] = 0; p[b + 4] = 0
        else:
            o = 0x80460000 + 0x200 * i
            p[b] = o; p[b + 4] = st; p[o + 0x130] = (i % 3) << 24
        p[b + 8] = 0
    pk = ','.join('%08X=%08X' % kv for kv in p.items())
    return '%s ! 0=80400000 ! %s ! %s ! ! 151436A4=1:C1200000;43480000;41A00000 ! !' % (name, pk, ret)
D = '1513DA94=80440000'
out = [
    setup('spawn', ret=D),
    setup('spawn0', ret='1513DA94=0'),
    setup('spawnc0', cfg=0, ret=D),
    setup('spawnc1', cfg=1, ret=D, idx2c=7),
    setup('spawnc3', cfg=3, ret=D, idx2c=6),
    setup('high', ret=D, height=0x44000000),
    setup('maxed', ret=D, live=0x13),
    setup('noacc', ret=D, accum=0x3F000000),
    setup('hang', ret=D, slots={0: 50, 3: 50, 7: 9, 25: 40}),
    setup('expire', ret=D, slots={0: 1, 3: 2, 7: 9, 25: 1}, live=4),
    setup('expire3', cfg=3, ret=D, slots={1: 1, 2: 0, 10: 5, 37: 1}, live=4),
    setup('full', ret=D, slots={'*': 50}, live=0x1A),
    setup('fullx', ret=D, slots={'*': 1}, live=0x1A),
    setup('ktimer', flag=1, timer=1, ret=D),
    setup('timerok', flag=1, timer=100, ret=D),
    setup('ktimer0', flag=1, timer=2, ret=D),
    setup('hmid', ret=D, height=0x43140000),
    setup('kown0', own0=0, ret=D),
    setup('kid', eid=4, ret=D),
    setup('nomtx0', mtx=0, ret='15149764=80450000'),
    setup('nomtx1', mtx=0, flag=1, timer=77, ret='15149764=80450000'),
    setup('nomtxn', mtx=0, ret='15149764=0'),
]
print('\n'.join(out))
