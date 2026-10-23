# P132: p127 copy + gap setups (end). P127: setups for func_151DE100 (game_pause_update). Byte globals share words: built per word.
# keys: osPiStartDma 10024CD0 (OUTA through arg 4 = the buffer), func_1517F54C 1517F54C, func_150ADA20 150ADF00
out=[]
def emit(n, ac0=0, ac1=0, d298=0, d29c=0, a0=0, eb5=0, q138=0, simple=0, d16d=0x80, cur=0, pad=0, ec9=0, b94=0, fca=0,
         e1013=0, c35ea=1, c3a08=1, be9f0=0x18, c3683=0, d18a0=0, d3268=0, be616=0, npads=0, fda8=0xFF, t118=0x1000,
         btn=(0,0,0,0), sticks=((0,0),(0,0),(0,0),(0,0)), ret='', outa=''):
    B={}
    def b(a,v): B[a]=v&0xFF
    b(0x800BEEE0,ac0); b(0x800BEEE1,ac1); b(0x80090298,d298); b(0x8009029C,d29c); b(0x800902A0,a0); b(0x800E0EB5,eb5)
    b(0x80090138,q138); b(0x80090158,simple); b(0x8009016D,d16d); b(0x800901CC,cur); b(0x800E0EC8,pad); b(0x800E0EC9,ec9)
    b(0x800E0FC4,b94); b(0x800E1013,e1013); b(0x800C3A0A,c35ea); b(0x800C3A08,c3a08); b(0x800C3AA3,c3683); b(0x800BEA36,be616)
    b(0x80090148,fda8)
    for k in range(4):
        b(0x800BED50+2*k,btn[k]>>8); b(0x800BED51+2*k,btn[k]); b(0x800BED3A+6*k,sticks[k][0]); b(0x800BED3B+6*k,sticks[k][1])
    W={}
    for a,v in B.items(): W[a&~3]=W.get(a&~3,0)|(v<<(8*(3-(a&3))))
    W[0x800BEE10]=be9f0; W[0x800D1CC0]=d18a0<<16; W[0x800D3268]=d3268; W[0x80083330]=npads&0xFFFFFFFF; W[0x80090118]=t118
    W[0x80090174]=0x80481000; W[0x800BEE04]=2; W[0x800BEE28]=0x20; W[0x800BE808]=0x100
    out.append('%s ! ! %s ! %s ! ! %s ! !'%(n,','.join('%08X=%08X'%kv for kv in sorted(W.items())),ret,outa))
# opening
for np_ in (0,1,3,-1):
    for k in range(4):
        bt=[0,0,0,0]; bt[k]=0x1000
        emit('open_n%d_p%d'%(np_ & 0xF,k),npads=np_,btn=tuple(bt),sticks=((1,-40),(2,40),(3,0),(4,-31)))
emit('open_two',npads=3,btn=(0,0x1000,0x1000,0)); emit('open_mask',npads=3,btn=(0x1000,0x1000,0,0),d18a0=1)
emit('open_mask_all',npads=1,btn=(0x1000,0x1000,0,0),d18a0=3); emit('open_other_btn',npads=1,btn=(0x0FFF,0xE000,0,0))
emit('open_delay',npads=1,btn=(0x1000,0,0,0),d298=3); emit('open_ac1',npads=1,btn=(0x1000,0,0,0),ac1=1)
emit('open_blk_c3683',npads=1,btn=(0x1000,0,0,0),c3683=1)
for c,l,a in ((0,0x18,1),(1,0x17,1),(1,0x18,0)):
    for r in ('0','1'):
        emit('open_chk_%d%x%d_r%s'%(c,l,a,r),npads=1,btn=(0x1000,0,0,0),c35ea=c,be9f0=l,c3a08=a,ret='1517F54C='+r)
emit('simple22',be9f0=0x22,ac0=1,ret='1517F54C=0')
# play time / time limit
for ec9 in (0,47,48,49,60): emit('time_%d'%ec9,ec9=ec9); emit('time_c7_%d'%ec9,ec9=ec9,d3268=0xC7)
for t in (0,1,0x20,0x21,3000,0xFFFFFF00):
    for np_ in (0,1): emit('limit_%x_n%d'%(t,np_),be616=1,e1013=3,t118=t,npads=np_)
emit('limit_e2',be616=1,e1013=2); emit('limit_ac1',be616=1,e1013=5,ac1=1)
# unpause countdown
for c in (1,2,3,0x7F): emit('cnt_%x'%c,d29c=c,ac1=1,ac0=1)
# menu running
for be in (0,1):
    for cur in range(-2,6):
        for sim in (0,1):
            for fca in (0,0x1000,0x4000,0x8000,0xC000,0x2000):
                emit('m%d_c%d_s%d_b%x'%(be,cur,sim,fca),ac0=1,be616=be,cur=cur,simple=sim,pad=1,btn=(0,fca,0,0),q138=cur&1,sticks=((0,0),(cur*10,-cur*10),(0,0),(0,0)))
for be in (0,1):
    for cur in (0,1,2,3):
        for (sx,sy,ax,ay) in ((31,0,30,0),(30,0,0,0),(-31,0,-30,0),(-30,0,0,0),(0,-31,0,-30),(0,31,0,30),(40,40,40,40),(-40,-40,-40,-40),(0,-31,0,-31),(31,31,-31,-31)):
            emit('st%d_c%d_%d_%d_%d_%d'%(be,cur,sx,sy,ax,ay),ac0=1,be616=be,cur=cur,pad=2,a0=ax,eb5=ay,sticks=((0,0),(0,0),(sx,sy),(0,0)))
emit('delay_menu',ac0=1,d298=2,pad=0,btn=(0x8000,0,0,0),cur=0)
# quit confirmation
for be in (0,1):
    for cur in (2,3,4):
        for fd in (0,5,0xFF):
            emit('quit%d_c%d_f%x'%(be,cur,fd),ac0=1,be616=be,cur=cur,q138=1,fda8=fd,btn=(0x8000,0,0,0))
for ok in (0,1):
    emit('no_chk%d'%ok,ac0=1,cur=2,q138=0,btn=(0x8000,0,0,0),ret='151DE074=00000F80,150ADF00=12345678;0ABCDEF0',
         outa=('10024CD0=4:6E5F923A;FB0BE5F6' if ok else '10024CD0=4:6E5F923A;FB0BE5F7'))
    emit('no_chk%d_b'%ok,ac0=1,be616=1,cur=3,q138=0,btn=(0x8000,0,0,0),outa=('10024CD0=4:6E5F923A;FB0BE5F6' if ok else '10024CD0=4:6E5F923B;FB0BE5F6'))
# P132 gap setups for the P127 survivors
for be in (0,1):
    for (sy,ay) in ((30,0),(-30,0),(30,31),(-31,-31)):
        emit('p132_sty%d_%d_%d'%(be,sy,ay),ac0=1,be616=be,cur=1,pad=2,a0=0,eb5=ay,sticks=((0,0),(0,0),(0,sy),(0,0)))
emit('p132_c3683_c0',npads=1,btn=(0x1000,0,0,0),c35ea=0,c3683=1,ret='1517F54C=0')
emit('p132_c3683_c2',npads=1,btn=(0x1000,0,0,0),c35ea=2,c3683=1,ret='1517F54C=0')
for fd in (0,1):
    for cur in (2,3):
        emit('p132_quit_f%d_c%d'%(fd,cur),ac0=1,be616=0,cur=cur,q138=1,fda8=fd,btn=(0x8000,0,0,0))
for r in ('12345679;0ABCDEF1','00000001;00000003'):
    emit('p132_no_odd_%s'%r[-1],ac0=1,cur=2,q138=0,btn=(0x8000,0,0,0),ret='151DE074=00000F80,150ADF00='+r,
         outa='10024CD0=4:6E5F923A;FB0BE5F7')
emit('p132_quit_872',ac0=1,be616=0,cur=2,q138=1,fda8=0,btn=(0x8000,0,0,0))   # + D_80087270 words nonzero (appended below)
out[-1]=out[-1].replace(' ! ! 8',' ! ! 80087610=11111111,80087614=22222222,8',1)
print('\n'.join(out))
