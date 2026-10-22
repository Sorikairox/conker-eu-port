import struct
tri = {'gen': [(0,0,0),(10,5,3),(4,7,12)], 'neg': [(-300,40,-20),(120,-7,900),(-5,1000,33)],
       'xeq': [(5,1,0),(5,9,3),(5,2,8)], 'c0x': [(3,0,0),(9,4,1),(3,7,6)], 'c1x': [(3,0,0),(3,4,1),(8,7,6)],
       'col': [(0,0,0),(1,5,1),(2,9,2)], 'pt': [(7,7,7)]*3, 'big': [(-32768,32767,-32768),(32767,-32768,32767),(0,0,1)]}
out = []
for name, vs in tri.items():
    b = b''.join(struct.pack('>hhh', *v) for v in vs) + b'\0\0'
    words = ['%08X=%08X' % (0x80480000 + 4*i, struct.unpack('>I', b[4*i:4*i+4])[0]) for i in range(5)]
    # tris form: pointers to separate 8-aligned copies
    tw = []
    for k, v in enumerate(vs):
        a = 0x804A0100 + 0x10 * k
        bb = struct.pack('>hhhh', *v, 0)
        tw += ['%08X=%08X' % (a, struct.unpack('>I', bb[:4])[0]), '%08X=%08X' % (a+4, struct.unpack('>I', bb[4:])[0]),
               '%08X=%08X' % (0x804A0000 + 4*k, a)]
    out.append('v_%s ! 0=0,1=80480000,2=80490000,3=80490010 ! %s ! !' % (name, ','.join(words)))
    out.append('t_%s ! 0=804A0000,1=0,2=80490000,3=80490010 ! %s ! !' % (name, ','.join(tw)))
    out.append('vt_%s ! 0=804A0000,1=80480000,2=80490000,3=80490010 ! %s ! !' % (name, ','.join(words + ['804A0000=00000000'])))
out.append('null ! 0=0,1=0,2=80490000,3=80490010 ! ! !')
out.append('alias ! 0=0,1=80480000,2=80490000,3=80490000 ! %s ! !' % ','.join('%08X=%08X' % (0x80480000+4*i, w) for i, w in enumerate([0x0000000A, 0x00050003, 0x0004000B, 0x000C0000])))
print('\n'.join(out))
