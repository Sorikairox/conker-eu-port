# P132: setups for func_151E0BBC (menu_mode_select_page). name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW
import struct
fb = lambda f: struct.unpack('>I', struct.pack('>f', f))[0]
out = []
def emit(n, page=1, inp=0, x41=0, ain=0xFF, pa=0xFF, pend=0xFF, dt=1, cur=0, f=0.0, cnt=(3, 5, 4, 2)):
    W = {0x80090174: 0x80481000, 0x80481020: inp << 16, 0x8048102C: (page & 0xFF) << 24,
         0x80481040: ((x41 & 0xFF) << 16) | 0x7700, 0x800E0EC4: (ain << 24) | (pa << 16) | (pend << 8),
         0x800BEE04: dt, 0x800901CC: (cur & 0xFF) << 24, 0x80090188: fb(f),
         0x80090248: (cnt[0] << 24) | (cnt[1] << 16) | (cnt[2] << 8) | cnt[3], 0x8009024C: 0x01010101,
         0x80090270: 0x0A000000, 0x80090274: 0x0B000000, 0x80090278: 0x0C000000, 0x8009027C: 0x0D000000}
    out.append('%s ! ! %s ! ! ! ! !' % (n, ','.join('%08X=%08X' % kv for kv in sorted(W.items()))))
emit('page0', page=0)
for pend in (0xFF, 2, 4):
    for pa in (0x10, 0x40, 0xFF):
        for ain in (0x80, 0xFF):
            emit('fade_p%x_a%x_i%x' % (pend, pa, ain), pend=pend, pa=pa, ain=ain, dt=2)
for page in (1, 2, 3, 4):
    for inp in (0, 1, 2, 4, 8, 0x10, 0x20, 0x11, 0x12):
        for cur in (0, 1):
            for x41 in (-1, 0, 2, 4):
                emit('g%d_i%x_c%d_r%d' % (page, inp, cur, x41 & 0xF), page=page, inp=inp, cur=cur, x41=x41)
for f in (0.0, 0.5, -0.5, 0.02, -0.02):
    for inp in (0, 1, 0x10):
        for cur in (0, 1):
            emit('slide_%s_i%x_c%d' % (str(f), inp, cur), page=2, inp=inp, cur=cur, f=f, x41=1)
emit('wrap_hi', page=1, x41=3); emit('wrap_lo2', page=4, x41=-2)
# P132 mutant gaps: alpha step reaching exactly 0x100; text alpha 0xFE (negative frame step)
emit('cap100', pend=0xFF, pa=0xE0, ain=0xFF, dt=1, inp=0x10)
emit('alphaFE', pend=2, pa=0xDE, dt=0xFFFFFFFF, inp=0x10)
print('\n'.join(out))
