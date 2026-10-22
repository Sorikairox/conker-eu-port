#!/usr/bin/env python3
"""P60 setups for func_1505E0C4 -> e0c4.txt. obj = record 1 (0x800CCA1C) or 0, entry 0x8042A000, anim 0x8042B000,
header returned by the func_1502AF04 / func_1502B110 stubs = 0x8042C000 (data, size, next)."""
import sys, struct
sys.path.insert(0, '../p59'); from pk import build
F = lambda v: '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]
REC, ENT, AN, HDR = 0x800CCA1C, 0x8042A000, 0x8042B000, 0x8042C000
def setup(name, obj=True, ent=True, restart='0', idv='5', hold='0|1', blend=8.0, rec='', anim='', hdr='w:0=w:B0001000,4=w:40,8=w:7', ret='', glob=''):
    args = '0=%X,1=%X,2=%X,3=0,4=%s,5=%s,6=3,7=%s,8=%s,9=%s,A=%s,B=%s' % (REC if obj else 0, ENT if ent else 0, AN, restart, idv,
            F(1.5), F(blend), F(4.0), F(2.0), hold)
    args = ','.join(('%d=%s' % (int(a.split('=')[0], 16), a.split('=')[1])) for a in args.split(','))
    spec = 'r1:4=b:07,6=b:2,58=w:0,84=h:5,103=b:0,104=b:0,F4=w:FFFFFFFF,1FC=b:5,24E=b:9,31C=w:8042D000' + rec + ';'
    spec += '8042A000:0=h:0010,2=h:0003,4=w:12345678;'
    spec += '8042B000:0=w:0,4=h:0005,6=h:0005,8=f:3.0,10=f:1.0,18=f:20.0,20=f:0.0,28=w:0,38=b:2,3C=h:0,43=b:1E,45=b:1,47=b:20,4B=b:44' + anim + ';'
    spec += '8042C000:0=w:B0001000,4=w:%s,8=w:7;' % hdr
    spec += '800C3A08:2=b:0' + glob + ';'
    rets = ret or '1502B1F4=%X,1502B400=%X' % (HDR, HDR)
    return '%s ! %s ! %s ! %s !' % (name, args, build(spec), rets)
S = [
  ('a',  dict(hdr='40')),                                    # restart via obj->unk84 ok? id 5 == all: no restart (hold 0|1)
  ('a1', dict(hdr='40', glob=',2=b:1')),                     # D_800C35EA == 1: frame copied when held
  ('a2', dict(obj=False, hdr='40', glob=',2=b:1')),
  ('b',  dict(restart='1', hdr='40')),                       # forced restart, blend = 0
  ('b2', dict(restart='1', hdr='400')),                      # big header: func_10004514
  ('b3', dict(restart='1', hdr='0')),                        # size 0: func_1505DFDC
  ('c',  dict(idv='6', hdr='40', anim=',28=w:1,3C=h:0')),    # new id, blend 8 (step 62), countdown 0x3FF
  ('c2', dict(idv='6', hdr='40', anim=',28=w:1,3C=h:100')),  # countdown > 0, other id: 0x3FF
  ('c3', dict(idv='6', hdr='40', anim=',28=w:1,3C=h:300')),  # countdown >= 600: no copy
  ('c4', dict(idv='6', hdr='40', anim=',28=w:1,3C=h:100,6=h:8006')),  # blend back into the previous id: 0x3FF - n
  ('c5', dict(idv='6', blend=0.5, hdr='40', anim=',28=w:1,3C=h:100')),  # blend < 1: countdown 0
  ('c6', dict(idv='6', blend=0.5, hdr='40', anim=',28=w:1,3C=h:300')),
  ('d',  dict(idv='6', hdr='40', rec=',58=w:8042E000')),     # model header path func_1502AF04
  ('e',  dict(idv='6', hdr='40', anim=',43=b:FF')),          # last frame per type: other id
  ('e2', dict(idv='6', hdr='40', anim=',43=b:FF', rec=',4=b:92,84=h:3')),
  ('e3', dict(idv='6', hdr='40', anim=',43=b:FF', rec=',4=b:B8')),
  ('f',  dict(idv='6', hdr='40', rec=',104=b:1,F4=w:00000020', anim=',47=b:0,45=b:0')),
  ('f2', dict(idv='6', hdr='40', rec=',F4=w:FFFFFFDF')),
  ('g',  dict(hdr='40', rec=',103=b:1')),                   # obj +0x103 forces restart
  ('g2', dict(hdr='40', rec=',84=h:FFFF')),
  ('g3', dict(obj=False, idv='6', hdr='40')),                # no object
  ('g4', dict(obj=False, idv='6', hdr='40', ret='1502B400=0')),           # no header (asm: stack leftovers = 0 here)
  ('a3', dict(hdr='40', anim=',4=h:8005', hold='0')),       # held animation released
  ('b4', dict(restart='1', hdr='40', anim=',28=w:1,3C=h:100')),  # forced restart while blending: countdown 0
  ('b5', dict(restart='1', hdr='100')),                      # size 0x100 >= 200: func_10004514
  ('c7', dict(idv='6', hdr='40', anim=',28=w:1,3C=h:300,6=h:0006')),  # blend back with countdown >= 600
  ('c8', dict(idv='6', hdr='40', anim=',28=w:1,3C=h:258|257'.split('|')[0])),
  ('c9', dict(idv='6', hdr='40', anim=',28=w:1,3C=h:257')),
  ('c10', dict(idv='6', blend=0.5, hdr='40', anim=',28=w:1,3C=h:258')),
  ('g5', dict(obj=False, ent=False, idv='6', hdr='40')),     # no entry: file 2 * id, no callback
]
for n, kw in S: print(setup(n, **kw).replace(',!', ' !'))
