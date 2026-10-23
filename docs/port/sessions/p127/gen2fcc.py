# P127: setups for func_151E2FCC (menu_game_start). Even trials only take the .game_data pokes (odd = ROM data).
# keys: func_150ADA20 = jal 150ADF00, func_151E2C88 = 151E2C88. Rows of D_800ABA70 come from the ROM (x42 0..12).
out=[]
def w(b): return ''.join('%02X'%(x&0xFF) for x in b)
def emit(n, row=0, q=(0,-1,-1,-1)+(-1,)*12, ids=tuple(range(16)), drop=0, nq=0, fbc=0, chars=(0,1,2,3), st=(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,1,1,0,1,0,0,0,0), ret=''):
    p={0x80090174:0x80481000,0x80481040:row<<8,0x8009013C:drop<<24,0x80090110:(nq&0xFF)<<24,0x800E0FBC:fbc<<24,0x800E0FC0:int(w(chars),16)}
    for k in range(4): p[0x800901E4+4*k]=int(w(q[4*k:4*k+4]),16); p[0x800E1030+4*k]=int(w(ids[4*k:4*k+4]),16)
    for k in range(6): p[0x800E1010+4*k]=int(w(st[4*k:4*k+4]),16)
    out.append('%s ! ! %s ! %s ! ! ! !'%(n,','.join('%08X=%08X'%kv for kv in sorted(p.items())),ret))
Q1=(0,)+(-1,)*15; Q4=(0,1,2,3)+(-1,)*12; QM=(0,-2,1,-1,-2,2,-1,-3)+(-1,)*8; QA=tuple(range(16)); QN=(0,-2,-2,5,-2,-1,7,-2,-2,-2,-1,-1,-2,-1,-1,-1)
ID0=(0,)*16; IDM=(0,1,0,2,0,0,3,1,0,1,0,0,2,0,1,0)
for r in range(13):
    for qn,q in (('q1',Q1),('q4',Q4),('qm',QM),('qa',QA),('qn',QN)):
        emit('r%d_%s'%(r,qn),row=r,q=q,ids=IDM,ret='150ADF00=00000005;0000001F;00000010,151E2C88=00000002')
    emit('r%d_id0'%r,row=r,q=QM,ids=ID0)
for nq in (1,2,4,7,8,9,0xFF):
    emit('drop%x'%nq,row=3,q=QA,drop=1,nq=nq); emit('nodrop%x'%nq,row=3,q=QA,drop=0,nq=nq)
for fq in (Q1,Q4,QM,(0,1,2,3,4)+(-1,)*11):
    emit('fbc_%d'%len([x for x in fq if x>=0]),row=3,q=fq,fbc=1,chars=(5,0x10,3,7))
    emit('fbc_r12_%d'%len([x for x in fq if x>=0]),row=12,q=fq,fbc=1,chars=(1,2,3,4))
for t3 in (0,2,3,7):
    for f in ((0,0,0),(5,1,9),(0xFF,0,4)):
        st=[1,2,t3,4,5,6,7,8,9,10,11,12,13,14,15,16,f[0],f[1],0,f[2],0,0,0,0]
        for r in (0,2,4,8,11,13 if False else 12):
            emit('st%d_%x%x%x_r%d'%(t3,f[0],f[1],f[2],r),row=r,q=Q4,st=st)
print('\n'.join(out))
