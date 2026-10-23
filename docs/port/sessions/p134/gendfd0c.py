# P134: setups for func_151DFD0C (title_chapter_select_page); EU addresses (D_800E9D00 = 800EA130, D_800BE9E4 = 800BEE04). name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW
out = []
def emit(n, dir=0xFF, pa=0xFF, ain=0xFF, cur=4, flags=0, found=1, cnt=2, d49c='1', sel=0, prev=1, scroll=0, sty=0,
         inp=0, b4=0xFF, b7fe=0, dt=1, blink=0):
    W = {0x80090174: 0x80481000, 0x80481020: inp << 16, 0x800E0EC4: (ain << 24) | (pa << 16) | ((dir & 0xFF) << 8),
         0x800902B0: (cur & 0xFF) << 24, 0x800902B4: (b4 & 0xFF) << 24, 0x800902D4: (scroll & 0xFF) << 24,
         0x800902D8: (prev & 0xFF) << 24, 0x800902E0: (blink & 0xFF) << 24, 0x80090150: (sel & 0xFF) << 24,
         0x800EA130: flags, 0x800BE7FC: b7fe << 8, 0x800BED38: sty & 0xFF, 0x800BEE04: dt}
    ret = '1509D338=%X,1509D49C=%s' % (found, d49c)
    out.append('%s ! ! %s ! %s ! ! ! 1509D338=1:%X !' % (n, ','.join('%08X=%08X' % kv for kv in sorted(W.items())), ret, cnt))
# G1 navigation / fades
for dir in (0xFF, 0, 1, 2, 3, 4):
    for pa in (0xFF, 0x10):
        for cur in (0, 4, 8):
            for found, d49c in ((0, '0'), (1, '0'), (1, '1;0;1;0;0;1')):
                emit('nav_d%x_p%x_c%d_f%d_%s' % (dir, pa, cur, found, d49c[:3].replace(';', '')), dir=dir, pa=pa, cur=cur, found=found, d49c=d49c)
for dt in (8, 0x20):
    for dir in (3, 4, 0xFF):
        emit('dt%x_d%x' % (dt, dir), dir=dir, pa=0x80, dt=dt)
emit('ain80', ain=0x80); emit('ainFF_paFE', pa=0xFE, dt=0)
# G2 list scrolling / drawing / input
for scroll in (0, 4, -4):
    for sty in (0, -0x40, 0x40, -0x31, 0x31, 0x32):
        for sel in (0, 2, -1, 0x20):
            emit('list_s%d_y%d_l%d' % (scroll, sty, sel), scroll=scroll, sty=sty, sel=sel, d49c='1')
for inp, b4 in ((0, 0xFF), (4, 0xFF), (8, 0xFF), (0xC, 0xFF), (0x10, 0xFF), (0x10, 3), (0x14, 3), (0x18, 0)):
    for pa in (0xFF, 0x80):
        emit('in%x_b%x_p%x' % (inp, b4, pa), inp=inp, b4=b4, pa=pa, d49c='1')
for cur in range(9):
    for sel in (0, 3, 6):
        for prev in (0, 3):
            emit('rows_c%d_l%d_p%d' % (cur, sel, prev), cur=cur, sel=sel, prev=prev, d49c='1', scroll=2, blink=0x30)
    emit('few_c%d' % cur, cur=cur, d49c='1;0;0;0;0;0;0;0;0;0;0;0', sel=0)
    emit('few2_c%d' % cur, cur=cur, d49c='0;1;0;1;0;0;0;0;0;0;0;0', sel=1, blink=0x50)
# G3 cheat flags / special scenes
for flags in (0, 0x8000, 2, 4, 0x1000, 0x4000, 0x1000000, 0x2000000, 0x4000000):
    for cur in range(9):
        emit('fl%x_c%d' % (flags, cur), flags=flags, cur=cur, found=1, d49c='0', dir=2)
for cur in (7, 8, 0):
    for b7fe in (0, 1):
        for d49c in ('0', '0;0;0;1;0', '1'):
            emit('b7fe%d_c%d_%s' % (b7fe, cur, d49c[:7].replace(';', '')), cur=cur, b7fe=b7fe, d49c=d49c)
for cnt in (0, 1, 5):
    emit('nofound_cnt%d' % cnt, found=0, cnt=cnt, cur=3, dir=1)
print('\n'.join(out))
