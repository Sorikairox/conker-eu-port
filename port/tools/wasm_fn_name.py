"""P373: wasm function-table index (a C function pointer, as "[icall] ... fn #N" prints it) -> the function's name, from
the module's element and name sections (the build links with --profiling-funcs).
usage: python3 port/tools/wasm_fn_name.py port/build/web/conker.wasm N [N...]"""
import sys

def leb(d, p, signed=False):
    r = s = 0
    while True:
        b = d[p]; p += 1
        r |= (b & 0x7F) << s; s += 7
        if not b & 0x80:
            break
    if signed and b & 0x40:
        r -= 1 << s
    return r, p

def parse(path):
    d = open(path, 'rb').read()
    p = 8
    nimp = 0
    table = {}
    names = {}
    while p < len(d):
        sid = d[p]; p += 1
        sz, p = leb(d, p)
        end = p + sz
        if sid == 2:
            n, q = leb(d, p)
            for _ in range(n):
                l, q = leb(d, q); q += l
                l, q = leb(d, q); q += l
                k = d[q]; q += 1
                if k == 0:
                    _, q = leb(d, q); nimp += 1
                elif k == 1:
                    q += 1; f = d[q]; q += 1; _, q = leb(d, q)
                    if f & 1: _, q = leb(d, q)
                elif k == 2:
                    f = d[q]; q += 1; _, q = leb(d, q)
                    if f & 1: _, q = leb(d, q)
                elif k == 3:
                    q += 2
        elif sid == 9:
            n, q = leb(d, p)
            for _ in range(n):
                flags, q = leb(d, q)
                assert flags in (0, 2), flags
                if flags == 2:
                    _, q = leb(d, q)
                op = d[q]; q += 1
                off, q = leb(d, q, True)
                assert d[q] == 0x0B; q += 1
                if flags == 2:
                    q += 1
                cnt, q = leb(d, q)
                for i in range(cnt):
                    fi, q = leb(d, q)
                    table[off + i] = fi
        elif sid == 0:
            l, q = leb(d, p)
            nm = d[q:q + l]; q += l
            if nm == b'name':
                while q < end:
                    sub = d[q]; q += 1
                    ssz, q = leb(d, q)
                    se = q + ssz
                    if sub == 1:
                        n, r = leb(d, q)
                        for _ in range(n):
                            fi, r = leb(d, r)
                            l, r = leb(d, r)
                            names[fi] = d[r:r + l].decode(); r += l
                    q = se
        p = end
    return table, names

if __name__ == '__main__':
    t, n = parse(sys.argv[1])
    for a in sys.argv[2:]:
        i = int(a)
        print(i, n.get(t.get(i), '?'))
