# P127: setups for func_15023988 (scene_sfx_update). name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW
import itertools
out=[]
def emit(name, pl=0, tr=1, ue=0, fl=0, now=5, end=9, ep=0x11, gep=0x11, tab=0x80483000, left=0x10, total=0x40,
         fin=0, fout=0, vol=0x7000, step=2, skip=0, cvol=25):
    arg='0=80480000,1=0,2=80481000,3=80481100,4=0,5=0,6=80481010'
    p={0x80480010:fl,0x80480018:0x80482000,
       0x80482000:(pl<<24)|(tr<<16)|(ue<<8),0x80482004:(left<<16)|total,0x80482008:(fin<<16)|fout,0x8048200C:(vol<<16)|(ep<<8),
       0x800C39D0+4*pl:now,0x800C3A60+4*pl:end,0x800C3D78+4*pl:tab,0x800BEE04:step,0x800C40A8:(skip<<24)|(cvol<<16),
       0x80483000+tr*0x44:0x42C80000,0x80483004+tr*0x44:0x41200000,0x80483008+tr*0x44:0xC2480000,0x80483038+tr*0x44:0x40A00000}
    a=0x800C3A08+pl; w=a&~3; p[w]=p.get(w,0)|(gep<<(8*(3-(a&3))))
    out.append('%s ! %s ! %s ! ! ! ! !'%(name,arg,','.join('%08X=%08X'%kv for kv in sorted(p.items()))))
emit('base')
emit('ue_run',ue=1); emit('ue_end',ue=1,now=9); emit('ue_past',ue=1,now=10); emit('noue_past',now=10)
emit('fl80',fl=0x80); emit('fl7f',fl=0x7F); emit('p1',pl=1); emit('p1_ue_end',pl=1,ue=1,now=9)
emit('epoch_diff',gep=0x12); emit('tab0',tab=0); emit('tr0',tr=0); emit('tr3',tr=3)
for l in (0xFFFF,0x10,3,2,1,0): emit('left%x'%l,left=l)
emit('step0',step=0); emit('step5',step=5,left=6); emit('step5eq',step=5,left=5)
emit('fout_in',left=0x10,fout=0x20); emit('fout_eq',left=0x12,fout=0x10); emit('fout_last',left=3,fout=0x20)
emit('fin_in',left=0x40,total=0x40,fin=8); emit('fin_edge',left=0x3A,total=0x40,fin=8); emit('fin_out',left=0x30,total=0x40,fin=8)
emit('fout_eq_fin',left=0x3C,total=0x40,fin=8,fout=0x3A); emit('fin_fout',left=0x3F,total=0x40,fin=8,fout=4); emit('fin_big',left=0x10,total=0x8,fin=0x20)
for sk,cv,st in ((1,25,2),(1,10,2),(1,1,2),(1,2,2),(1,0,2),(0,10,2),(1,10,0x20)): emit('skip%d_cv%d_st%x'%(sk,cv,st),skip=sk,cvol=cv,step=st)
emit('skip_endless',skip=1,cvol=10,left=0xFFFF); emit('skip_fout',skip=1,cvol=10,left=0x10,fout=0x20)
emit('vol_max',vol=0xFFFF,left=0x10,fout=0x20); emit('vol_max_fin',vol=0xFFFF,left=0x40,total=0x40,fin=8)
print('\n'.join(out))
