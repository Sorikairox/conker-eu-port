#!/usr/bin/env python3
# P77 setups for func_1501CDA0: slot s, D_800C3A5A[s] = n actors, D_800C3D80[s][i] -> 16-byte blocks at 0x80420000 + 0x20 i (pre-filled 0x11..).
n=0
for s in (0,1,3,7):
    for cnt in (0,1,2,5,30):
        p={}
        b=0x800C3A5A+s; p[b&~3]=cnt<<(8*(3-(b&3)))
        for i in range(30):
            p[0x800C3D80+s*120+4*i]=0x80420000+0x20*i
            for k in range(0,0x20,4): p[0x80420000+0x20*i+k]=0x11223344+k
        print('a%d ! 0=%X ! %s ! ! ! ! ! !'%(n,s,','.join('%08X=%08X'%kv for kv in sorted(p.items())))); n+=1
