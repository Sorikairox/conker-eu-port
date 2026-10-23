#!/usr/bin/env python3
# P77 setups for func_150226E8 (id list of a sequence slot) and func_1501CDA0 (actor blocks). EU addresses = US here.
# a0 of func_150226E8 is a u8 (callers zero-extend); the random phase passes any word, so setups fix it.
import random
R=random.Random(2268)
def lst(slot,count,items):
    p={}
    b=0x800C396A+slot; p[b&~3]=(count<<(8*(3-(b&3))))
    base=0x800C3970+slot*30
    by={base+i:v for i,v in enumerate(items)}
    words={}
    for a,v in by.items(): words[a&~3]=words.get(a&~3,0)|(v<<(8*(3-(a&3))))
    p.update(words); return p
n=0
for slot in (0,1,2,3,5):
    for count,items,id_ in ((0,[],7),(1,[7],7),(3,[1,2,7],7),(3,[1,2,3],7),(5,[9,9,0xFF,4,0],0xFF),(5,[9,9,1,4,0],0),(29,list(range(29)),28),(29,list(range(29)),200),(12,[R.randint(0,255) for _ in range(12)],R.randint(0,255))):
        pk=lst(slot,count,items)
        print('l%d ! 0=%X,1=%X ! %s ! ! ! ! ! !'%(n,id_,slot,','.join('%08X=%08X'%kv for kv in sorted(pk.items())))); n+=1
