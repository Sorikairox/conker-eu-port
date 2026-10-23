import struct,sys
def recs(rs, base=0x80460000):
    b = bytearray(100)
    for i,(d,p,s,t) in enumerate(rs):
        struct.pack_into('>bxhhh', b, 10*i+1, 0, p, s, t) if False else None
        b[10*i+2] = d & 0xFF
        struct.pack_into('>hhh', b, 10*i+4, p, s, t)
    return ','.join('%08X=%X' % (base+4*k, struct.unpack('>I', b[4*k:4*k+4])[0]) for k in range(25))
R=[(1,0x100,0x10,0x40),(-1,0x4F0,-0x10,0x15),(1,0x10,-0x100,-0x100),(1,-0x8000,0,0),(1,0x500,0,0),(1,0x200,0x40,0x10),(-1,0x300,-0x40,-0x10),(1,0x4000,0x7000,0x7000),(-2,0x20,0x30,0x30),(3,0x4FF,0,5)]
for name,fd,st in (('a',0x02000000,1),('snap',0x01000000,0x1000),('zero',0,1)):
    print('%s ! ! 800BE900=80460000,800BEDC0=%X,800BEE04=%X,%s ! ! ! ! !' % (name, fd, st, recs(R)))
