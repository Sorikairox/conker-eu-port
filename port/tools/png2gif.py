#!/usr/bin/env python3
"""P63: animated GIF (and cropped PNG zooms) from screenshot PNGs, standard library only (no host installs).

  python3 port/tools/png2gif.py OUT.gif X Y W H SCALE DELAY_CS in1.png in2.png ...
  python3 port/tools/png2gif.py --png OUT.png X Y W H SCALE in.png      (one cropped, scaled PNG)

Crops (X, Y, W, H) from every input, scales by an integer SCALE (nearest), quantizes to a fixed 6x7x6 colour cube and
writes a looping GIF89a (DELAY_CS = frame delay in 1/100 s). PNG input: 8-bit RGB / RGBA, not interlaced.
"""
import struct
import sys
import zlib


def read_png(path):
    data = open(path, 'rb').read()
    assert data[:8] == b'\x89PNG\r\n\x1a\n', path
    pos, idat, w = 8, b'', 0
    while pos < len(data):
        n, typ = struct.unpack('>I4s', data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        if typ == b'IHDR':
            w, h, depth, ctype, _, _, inter = struct.unpack('>IIBBBBB', body)
            assert depth == 8 and ctype in (2, 6) and inter == 0, (path, depth, ctype, inter)
            bpp = 3 if ctype == 2 else 4
        elif typ == b'IDAT':
            idat += body
        pos += 12 + n
    raw = zlib.decompress(idat)
    stride = w * bpp
    rows, prev = [], bytearray(stride)
    for y in range(h):
        f = raw[y * (stride + 1)]
        line = bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        for i in range(stride):
            a = line[i - bpp] if i >= bpp else 0
            b = prev[i]
            c = prev[i - bpp] if i >= bpp else 0
            if f == 1:
                line[i] = (line[i] + a) & 255
            elif f == 2:
                line[i] = (line[i] + b) & 255
            elif f == 3:
                line[i] = (line[i] + (a + b) // 2) & 255
            elif f == 4:
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                line[i] = (line[i] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        rows.append(line)
        prev = line
    return w, h, bpp, rows


def crop(img, x, y, cw, ch, scale):
    w, h, bpp, rows = img
    out = []
    for yy in range(y, y + ch):
        line = []
        for xx in range(x, x + cw):
            px = tuple(rows[yy][xx * bpp:xx * bpp + 3])
            line.extend([px] * scale)
        for _ in range(scale):
            out.append(line)
    return out


def write_png(path, pix):
    h, w = len(pix), len(pix[0])
    raw = b''.join(b'\x00' + bytes(c for px in row for c in px) for row in pix)
    def chunk(t, b):
        return struct.pack('>I', len(b)) + t + b + struct.pack('>I', zlib.crc32(t + b) & 0xFFFFFFFF)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)) +
                           chunk(b'IDAT', zlib.compress(raw, 9)) + chunk(b'IEND', b''))


def lzw(indices, min_size=8):
    clear, end = 1 << min_size, (1 << min_size) + 1
    out, bits, nbits = bytearray(), 0, 0
    size = min_size + 1
    def emit(code):
        nonlocal bits, nbits
        bits |= code << nbits
        nbits += size
        while nbits >= 8:
            out.append(bits & 255)
            bits >>= 8
            nbits -= 8
    table = {(i,): i for i in range(clear)}
    nxt = end + 1
    emit(clear)
    cur = (indices[0],)
    for k in indices[1:]:
        cand = cur + (k,)
        if cand in table:
            cur = cand
            continue
        emit(table[cur])
        if nxt < 4096:
            table[cand] = nxt
            nxt += 1
            if nxt > (1 << size) and size < 12:
                size += 1
        else:
            emit(clear)
            table = {(i,): i for i in range(clear)}
            nxt, size = end + 1, min_size + 1
        cur = (k,)
    emit(table[cur])
    emit(end)
    if nbits:
        out.append(bits & 255)
    blocks = bytearray([min_size])
    for i in range(0, len(out), 255):
        part = out[i:i + 255]
        blocks += bytes([len(part)]) + part
    return bytes(blocks + b'\x00')


def write_gif(path, frames, delay):
    pal = [(r * 51, g * 42, b * 51) for r in range(6) for g in range(7) for b in range(6)]
    pal += [(0, 0, 0)] * (256 - len(pal))
    h, w = len(frames[0]), len(frames[0][0])
    out = bytearray(b'GIF89a' + struct.pack('<HHBBB', w, h, 0xF7, 0, 0))
    out += bytes(c for p in pal for c in p)
    out += b'\x21\xFF\x0BNETSCAPE2.0\x03\x01\x00\x00\x00'
    for f in frames:
        idx = [((r * 5 + 127) // 255) * 42 + ((g * 6 + 127) // 255) * 6 + ((b * 5 + 127) // 255)
               for row in f for (r, g, b) in row]
        out += b'\x21\xF9\x04\x04' + struct.pack('<H', delay) + b'\x00\x00'
        out += b'\x2C' + struct.pack('<HHHHB', 0, 0, w, h, 0) + lzw(idx)
    out += b'\x3B'
    open(path, 'wb').write(out)


if __name__ == '__main__':
    a = sys.argv[1:]
    if a[0] == '--png':
        x, y, w, h, s = map(int, a[2:7])
        write_png(a[1], crop(read_png(a[7]), x, y, w, h, s))
    else:
        x, y, w, h, s, d = map(int, a[1:7])
        write_gif(a[0], [crop(read_png(p), x, y, w, h, s) for p in a[7:]], d)
