# P127: setups for func_1000FA64 (sfx_start_positional). keys: func_10011624 = jal 10011914, func_15083E0C = jal 15084274
out=[]
def emit(n, c=5, cb='15023988', fl='0', a1='10', a2='FFEC', cents='64', ret='', ow=''):
    arg='0=1234,1=%s,2=%s,3=1E,4=7000,5=7D00,6=7918,7=%s,8=80486000,9=3,10=%s,11=%s'%(a1,a2,cb,fl,cents)
    out.append('%s ! %s ! 80042B00=%08X ! %s ! ! ! %s !'%(n,arg,c,ret,ow))
for c in (0,5,0x1F,0x20,0x21,0xFFFFFFFF): emit('c%x'%c,c=c); emit('c%x_chg'%c,c=c,ow='10011914=1:%X'%((c+3)&0xFFFFFFFF))
for fl in ('0','2','8','100','108','1FF','FFFF','1000','12'): emit('cb_fl%s'%fl,fl=fl); emit('nocb_fl%s'%fl,cb='0',fl=fl)
for r in ('FFFFFFFF','7','FFFF','0'): emit('j40_r%s'%r,fl='40',ret='15084274=%s'%r,a1='FF85'); emit('j40n_r%s'%r,cb='0',fl='148',ret='15084274=%s'%r)
for ce in ('0','FFFFFF9C','4B0'): emit('cents%s'%ce,cents=ce)
emit('neg_args',a1='8000',a2='7FFF'); emit('chg_same',ow='10011914=1:5')
print('\n'.join(out))
for s in (0x30, 0x40):
    print('ret_s%x ! 0=1234,1=10,2=FFEC,3=1E,4=7000,5=7D00,6=7918,7=15023988,8=80486000,9=3,10=0,11=64 ! 80042B00=00000005 ! ! ! ! 10011914=@%08X:ABCD1234 !' % (s, 0x80042380 + 5 * s + 0x22))
