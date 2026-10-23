import random
random.seed(11)
L = []
cases = [(0,0,0,0),(0,1,0,700),(0,4,0,10),(0,2,0,599),(0,2,0,600),(0,3,0,100),
         (1,1,300,5),(1,1,0,5),(1,1,298,20),(1,1,100,11),(1,1,100,10),(1,0,150,-5),
         (2,1,300,5),(2,0,300,5),(2,2,300,119),(2,2,300,120),(2,3,300,50),(2,3,300,200),
         (3,0,0,5),(3,0,120,40),(3,0,3,0),(3,2,300,-7),(4,1,5,0),(4,0,0,0),(5,1,10,0),(6,0,0,0)]
for i, (st, req, cnt, tm) in enumerate(cases * 2):
    a0 = random.choice([0, 1, 2])
    gust = random.choice([1, 2, 50, 200]); strength = random.choice([10, 39, 40, 200])
    pause = random.choice([0, 0, 1])
    p = {0x800DD860: (random.randrange(1, 0xFFFF) << 16) | (gust << 8) | strength,
         0x800DD864: (req << 24) | (cnt & 0xFFFF), 0x800DD874: ((tm & 0xFFFF) << 16) | (st << 8),
         0x800DD870: random.choice([0, 0x80480000]), 0x800BEE04: random.choice([1, 2, 3]),
         0x800C3A08: pause << (8 * (1 - a0)) if a0 < 2 else pause << 24 , 0x800C3A0C: (pause << 24) if a0 == 2 else 0}
    ret = ['10003E90=80470000', '10011220=%X' % random.randrange(1, 0xFFFF), '150ADF00=%X;%X' % (random.randrange(1 << 31), random.randrange(1 << 31))]
    L.append('r%d ! 0=%X ! %s ! %s ! ! ! ' % (i, a0, ','.join('%08X=%08X' % kv for kv in p.items()), ','.join(ret)))
open('9008.txt', 'w').write('\n'.join(L) + '\n')
