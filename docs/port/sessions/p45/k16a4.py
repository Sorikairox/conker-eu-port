#!/usr/bin/env python3
# usage: k16a4.py SETUP -> DIFFTEST_POKE string for func_150A16A4 (EU addresses). Record = D_800CC2D0[0] (800CC6F0).
import sys
R = 0x800CC6F0; Z = 0x80490000; T = 0x804A8000
def w(a, v): return '%08X=%08X' % (a, v & 0xFFFFFFFF)
IN = (-1000, 1000, -1000, 1000, -1000, 1000); OUT = (500, 1000, -1000, 1000, -1000, 1000)
def zone(i, mask, prio, box):
    b = Z + i * 0x28; s = [w(b + 4 * k, (mask >> (32 * (5 - k))) & 0xFFFFFFFF) for k in range(6)]
    h = [x & 0xFFFF for x in box]
    s += [w(b + 0x18, (prio << 24) | h[0]), w(b + 0x1C, (h[1] << 16) | h[2]), w(b + 0x20, (h[3] << 16) | h[4]), w(b + 0x24, h[5] << 16)]
    return s
def trig(i, kind, sub, f18=0, f1c=0, f20=0, y2=0, y8=0, f10=0):
    b = T + i * 0x34
    return [w(b + 0x14, ((kind << 2) << 16) | sub), w(b + 0x18, f18), w(b + 0x1C, f1c), w(b + 0x20, f20),
            w(b + 0x0, y2 & 0xFFFF), w(b + 0x8, (y8 & 0xFFFF) << 16), w(b + 0x10, f10)]
def m3(lo, hi=0, top=0): return (top << 128) | (hi << 64) | lo   # w[2] w[1] w[0] -> stored w[0] first
def store(m):  # u64 w[0] (bits 0..63) at +0, w[1] at +8, w[2] at +0x10
    return ((m & (2**64 - 1)) << 128) | (((m >> 64) & (2**64 - 1)) << 64) | (m >> 128)
s = sys.argv[1]
B = [w(0x800D34BC, Z), w(0x800D34B8, T), w(R + 0x14, 0x42C80000), w(R + 0x18, 0x42480000), w(R + 0x1C, 0xC1F00000),
     w(R + 0x318, 0x804A0000), w(R + 0x31C, 0x804B0000), w(R + 0x124, 0), w(R + 0x104, 0), w(R + 0x1C8, 0x00000100),
     w(R + 0x88, 0), w(R + 0x44, 0x41200000), w(R + 0x28, 0), w(0x804B0094, 0), w(0x804B0118, 0), w(0x804B004C, 0x10000000),
     w(0x800D3694, 0), w(0x800C3A08, 0), w(0x800E0FC4, 0)]
n = 8; cached = 0; dflt = 0xFF; always = 0; prev = 0x5A
kinds = [(0, 1), (0, 0xC), (1, 0), (1, 2), (1, 3), (1, 5), (1, 8), (1, 9)]
zin = [IN] * 8; zmask = [2**192 - 1] * 8; prio = [9, 3, 5, 3, 7, 1, 8, 2]
if s == 'a': zin[3] = OUT
if s == 'b': kinds = [(2, 0), (3, 5), (3, 4), (4, 0), (7, 0), (8, 0), (11, 3), (12, 6)]; cached = 2
if s == 'c': kinds = [(13, 0), (13, 1), (14, 0), (14, 2), (25, 0), (25, 1), (26, 0), (1, 1)]; prev = 0xA4
if s == 'd': kinds = [(1, 4), (1, 6), (1, 7), (1, 8), (13, 0), (14, 3), (12, 1), (1, 5)]; zmask[1] = 2**192 - 1 - 0x30; zin[6] = OUT; always = 0x100
if s == 'e': n = 70; dflt = (1 << 69) | (1 << 66) | 0x81; zmask = [2**192 - 1 - (1 << 66)] * 8; cached = 1
if s == 'f': cached = 4; zin[3] = OUT  # cached zone not containing
if s == 'g': B[6:7] = [w(R + 0x31C, 0x804B0000)]; B[5] = w(R + 0x318, 0); kinds = [(0, 1), (13, 0), (14, 0), (12, 0), (4, 0), (1, 5), (1, 0), (2, 0)]
if s == 'h': B[7] = w(R + 0x124, 0x000000FF)
if s == 'j': kinds = [(1, 9), (1, 5), (1, 9), (1, 5), (1, 9), (1, 5), (1, 9), (1, 5)]
if s == 'i': B[3] = w(R + 0x18, 0x43480000); kinds[2] = (13, 0); prev = 0x18
B += [w(0x800D34B4, n), w(0x800D34F0, cached << 16)]
for k, v in enumerate([store(dflt)]): pass
d = store(dflt); a = store(always); p = store(prev)
for k in range(6):
    B.append(w(0x800D34D8 + 4 * k, d >> (32 * (5 - k)))); B.append(w(0x800D34C0 + 4 * k, a >> (32 * (5 - k))))
    B.append(w(0x800D3510 + 4 * k, p >> (32 * (5 - k))))
for i in range(8):
    B += zone(i, store(zmask[i]), prio[i], zin[i])
    k, sub = kinds[i]
    B += trig(i, k, sub, f18=i & 1, f1c=0x1234, f20=i & 2, y2=10, y8=20 + 300 * (i & 1), f10=0x42B40000 if i & 1 else 0x43870000)
if s == 'e':
    for i in (64, 66, 69):
        B += zone(i, store(zmask[0]), 4, IN); B += trig(i, 1, 3)
if s == 'i': B += [w(T + 5 * 0x34 + 0x10, 0x43920000)]
print(','.join(B))
