# setups for func_151E7110 (text bank loader). Globals are byte / word pokes on their (EU = US name) addresses.
S1=0x80450000; S2=0x80460000; T1=0x80470000; T2=0x80480000
def words(addr, data):
    data = data + b'\0' * (-len(data) % 4)
    return {addr + i: int.from_bytes(data[i:i+4], 'big') for i in range(0, len(data), 4)}
bank1 = b'AB\0\0C\0DEF\0\0\0G\0'
bank2 = b''.join(b'%c\0' % (0x41 + (i % 26)) for i in range(80)) + b'Z'
def line(n, arg, cur, lang, loaded, have1004, have178, size):
    pk = {0x800BEEC8: cur, 0x800E1018: lang << 8, 0x800E1000: loaded << 0,
          0x800E1004: 0x80490000 if have1004 else 0, 0x80090178: 0x804A0000 if have178 else 0,
          0x800E0FB8: 0x804B0000, 0x800E1008: 0x804C0000}
    pk.update(words(S1, bank1)); pk.update(words(S2, bank2))
    ret = f"1502B8B8={S1:X};{S2:X},10003E90={T1:X};{T2:X}"
    outw = f"1502B8B8=0:{size:X};60"
    return f"{n} ! {0}={arg:X} ! " + ",".join(f"{a:X}={v:08X}" for a, v in pk.items()) + f" ! {ret} ! ! ! {outw} !"
i = 0
for arg in [0, 1, 2, 4]:
    for cur, lang in [(0, 0), (1, 0), (2, 2)]:
        for loaded in [0, 1, 2, 0xFF]:
            for h4, h8 in [(0, 0), (1, 0), (1, 1), (0, 1)]:
                for size in [1, 15]:
                    print(line(f"e{i}", arg, cur, lang, loaded, h4, h8, size)); i += 1
