# P127: setups for func_15188D80 (object_trail_start). keys: allocate_memory 10003E90, func_1502DE10 1502DE10, bzero 10022A10, func_10004074 100042C4
out=[]
def emit(n, head=0, nodes=(), fr='20', st='3', ret='10003E90=80486000;80487000,1502DE10=3'):
    p={0x800DFBF8:head, 0x80480004:0x4B000000}
    for addr, obj, u6, nxt in nodes:
        p[addr+4]=(0x07<<24)|(u6&0xFFFF); p[addr+0xC]=nxt; p[addr+0x10]=obj
    out.append('%s ! 0=80480000,1=%s,2=%s ! %s ! %s ! ! ! !'%(n,fr,st,','.join('%08X=%08X'%kv for kv in sorted(p.items())),ret))
O=0x80480000; X=0x80481000
emit('empty'); emit('empty_cnt0',ret='10003E90=80486000;80487000,1502DE10=0'); emit('empty_n0',ret='10003E90=0,1502DE10=3')
emit('empty_buf0',ret='10003E90=80486000;0,1502DE10=3'); emit('empty_cnt1',ret='10003E90=80486000;80487000,1502DE10=1')
emit('empty_fr_neg',fr='FFFFFFF0',st='FF')
for u6,tag in ((0x10,'lt'),(0x20,'eq'),(0x30,'gt'),(0xFFF0,'neg')):
    emit('first_'+tag,head=0x80482000,nodes=[(0x80482000,O,u6,0x80482100),(0x80482100,X,5,0)])
    emit('second_'+tag,head=0x80482000,nodes=[(0x80482000,X,5,0x80482100),(0x80482100,O,u6,0)])
emit('notfound',head=0x80482000,nodes=[(0x80482000,X,5,0x80482100),(0x80482100,X+0x10,5,0)])
emit('notfound_cnt0',head=0x80482000,nodes=[(0x80482000,X,5,0)],ret='10003E90=80486000;80487000,1502DE10=0')
emit('first_fr_big',head=0x80482000,nodes=[(0x80482000,O,0x10,0)],fr='12345')
print('\n'.join(out))
