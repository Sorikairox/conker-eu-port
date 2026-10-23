# P191: setups for func_1504B0FC player_swim_update. p = 80410000 (struct127), state block 80420000, input
# D_800CC6A4 -> 80430000; globals D_800D1550 (EU 800D1970), D_800BE9E4 (800BEE04), D_800CC264 (800CC684).
import struct
P, ST, IN = 0x80410000, 0x80420000, 0x80430000
def fb(v): return struct.pack('>f', v)
BASE = dict(y=300.0, yvel=0.0, grav=0.0, f28=50.0, oldy=290.0, xz=5.0, u76=0x1000, anim=0x10, inw=1, air=0, pitch=0.0,
            tspeed=7.0, stun=0, health=3, surf=500.0, s1a6=0, st1c=0.0, st20=0, st21=0, st22=0, st95=0, st120=0, st198=0,
            turn=0, dive=0, d1550=1.0, d9e4=2, dcc264=0x20, dt=1.0, fz=0.0, bot=0x80440000)
def row(name, **kw):
    s = dict(BASE); s.update(kw); m = {}
    def put(a, b):
        for i, x in enumerate(b): m[a + i] = x
    put(P + 0x18, fb(s['y'])); put(P + 0x20, fb(s['yvel'])); put(P + 0x24, fb(s['grav'])); put(P + 0x28, fb(s['f28']))
    put(P + 0x30, fb(s['oldy'])); put(P + 0x3C, fb(s['xz'])); put(P + 0x76, struct.pack('>H', s['u76']))
    put(P + 0x84, struct.pack('>H', s['anim'])); put(P + 0xAD, bytes([s['inw']])); put(P + 0xB2, struct.pack('>H', s['air']))
    put(P + 0xB8, fb(s['pitch'])); put(P + 0xC0, fb(s['tspeed'])); put(P + 0x104, bytes([s['stun']]))
    put(P + 0x118, fb(s['surf'])); put(P + 0x188, struct.pack('>I', s['bot'])); put(P + 0x1A6, struct.pack('>h', s['s1a6']))
    put(P + 0x1CA, bytes([s['health']])); put(P + 0x31C, struct.pack('>I', ST))
    put(ST + 0x1C, fb(s['st1c'])); put(ST + 0x20, bytes([s['st20'], s['st21'], s['st22'] & 0xFF]))
    put(ST + 0x95, bytes([s['st95']])); put(ST + 0x120, bytes([s['st120']])); put(ST + 0x198, bytes([s['st198']]))
    put(0x800CC6A4, struct.pack('>I', IN)); put(IN, bytes([0, 0, s['turn'] & 0xFF, s['dive'] & 0xFF]))
    put(0x800D1970, fb(s['d1550'])); put(0x800BEE04, struct.pack('>i', s['d9e4'])); put(0x800CC684, struct.pack('>h', s['dcc264']))
    words = {}
    for a in sorted(m):
        w = a & ~3
        if w not in words:
            words[w] = bytearray(b'\0\0\0\0')
        words[w][a - w] = m[a]
    poke = ','.join('%08X=%s' % (a, bytes(b).hex().upper()) for a, b in sorted(words.items()))
    arg = '0=%08X,1=%s' % (P, fb(s['dt']).hex().upper())
    outw = '1510FDA0=6:%s' % fb(s['fz']).hex().upper()
    retf = '15052478=%s' % fb(1.5).hex().upper()
    print('%s ! %s ! %s ! ! %s ! ! %s !' % (name, arg, poke, retf, outw))
row('deep')                                  # swimming deep: buoyancy rise, pitch to 0
row('nosurf', surf=-10000.0)                  # no water surface: func_15052408, 0
row('dive', dive=20, turn=30)                 # dive input: pitch target 45, turn
row('turnneg', turn=-40, dcc264=-0x33)
row('near', y=420.0)                          # near the surface line: bob, -30 pitch target
row('over', y=460.0, st1c=2.0)                # above the line + 14: clamp
row('bob', y=330.0, st1c=2.4)
row('bobmax', y=330.0, st1c=2.6)
row('anim28', y=330.0, anim=0x28, st1c=1.0)
row('anim22', anim=0x22, pitch=-50.0, dive=0)
row('anim22b', anim=0x22, dive=-20)
row('a262', anim=0x262)
row('stun', stun=1)
row('stun0h', stun=1, health=0, yvel=10.0)
row('stun0hv', stun=1, health=0, yvel=70.0)
row('float', st20=1, y=100.0, dive=30)        # float-up push
row('float21', st21=1, y=100.0, dive=5)
row('floatcap', st20=1, y=268.0, d1550=8.0)
row('st22', st22=0x70)
row('st198', st198=1, dive=9, turn=40)
row('bottom', f28=5.0, y=480.0, xz=20.0)      # touching the bottom: leave swim, clamp xz
row('bottom2', f28=5.0, y=480.0, xz=10.0)
row('notbottom', f28=5.0, y=200.0)
row('floor', f28=20.0, fz=-10.0)              # floor push lowers pitch
row('floor2', f28=20.0, fz=30.0)
row('surfgasp', s1a6=600, air=0x600)
row('surfgasp2', s1a6=600, air=0x300)
row('surfgasp3', s1a6=600, air=0x20)
row('surfh0', s1a6=600, health=0, air=0x600)
row('surf20', st20=1, air=0x100, y=100.0)
row('airout', air=0x604, d9e4=4)
row('airout4', air=0x604, d9e4=4, health=4)
row('airout1', air=0x604, d9e4=4, health=1)
row('airout1s', air=0x604, d9e4=4, health=1, stun=1)
row('airwarn', air=0x5A0, d9e4=2)
row('airwarn5', air=0x5A0, d9e4=2, health=5)
row('air0h', health=0, air=0x10)
row('air0h120', health=0, air=0x10, st120=1)
row('airwrap', air=0xFFFE, d9e4=4)
row('pitchfast', pitch=60.0, dive=0)
row('pitchslow', pitch=1.0, d1550=1.0)
row('pitchclamp', pitch=-95.0, dive=-60)
row('pitchhi', pitch=95.0)
row('gravneg', grav=-1.0, yvel=5.0)
row('notwater', inw=0, grav=-1.0, yvel=5.0)
row('notwater2', inw=0, grav=1.0, yvel=-5.0)
row('notwater3', inw=0, grav=1.0, yvel=5.0)
row('inw2', inw=2, y=100.0)
row('st95', st95=1, oldy=400.0)
row('st95b', st95=1, oldy=450.0)
row('st21', st21=1, turn=40)
row('dt2', dt=2.5, y=100.0)
# second set (P191 mutant survivors: exact boundaries; the pitch rate limit 2.7 hides target changes, so the pitch
# starts next to the target)
row('dive1', dive=1, turn=2, pitch=0.0)
row('st22b', st22=0x64)
row('st22c', st22=0x70, pitch=179.0)
row('floatcap2', st20=1, y=467.5)
row('floatdive', st20=1, y=100.0, dive=11, pitch=22.0)
row('line175', y=265.0, pitch=1.0)
row('stun60', stun=1, health=0, yvel=60.0)
row('bottom8', f28=8.0, y=480.0)
row('bottomy', f28=5.0, y=465.0)
row('gasp5d3', s1a6=600, air=0x5D3)
row('gasp2d1', s1a6=600, air=0x2D1)
row('air605', air=0x603, d9e4=2)
row('air5a1', air=0x59F, d9e4=2)
row('air5a1h4', air=0x59F, d9e4=2, health=4)
row('gravneg2', grav=-1.0, yvel=-5.0)
row('bob25', y=330.0, st1c=2.5)
row('line75', y=365.0, anim=0x28, pitch=0.0, dt=0.0)
row('a22m9', anim=0x22, dive=-9, pitch=-20.0)
row('a22m10', anim=0x22, dive=-10, pitch=-20.0)
row('pv265', pitch=-2.65, d1550=0.5)
row('pclamp', pitch=-88.0, dive=-60)
row('pclamphi', pitch=88.0, dive=60)
row('turn9', turn=9)
