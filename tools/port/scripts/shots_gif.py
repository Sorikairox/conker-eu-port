#!/usr/bin/env python3
"""P347 test aid: turn browser-test screenshots (Chrome CDP PNGs) into an animated GIF and a contact-sheet PNG,
in pure Python (no Pillow / ffmpeg on the host). Crops the game picture of the page (default: the canvas box of a
1000x813 page screenshot), scales it down by an integer factor, and writes a 6x7x6-colour GIF.

  tools/port/scripts/shots_gif.py OUT.gif OUT_sheet.png [--scale 2] [--crop X0,Y0,X1,Y1] [--delay CS] [--cols N] PNG...
"""
import argparse
import struct
import zlib


def png_read(path):
    data = open(path, 'rb').read()
    assert data[:8] == b'\x89PNG\r\n\x1a\n', path
    pos, idat, w = 8, b'', 0
    while pos < len(data):
        n, kind = struct.unpack('>I4s', data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        if kind == b'IHDR':
            w, h, depth, ctype = struct.unpack('>IIBB', body[:10])
            assert depth == 8 and ctype in (2, 6), (path, depth, ctype)
            bpp = 3 if ctype == 2 else 4
        elif kind == b'IDAT':
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
                line[i] = (line[i] + ((a + b) >> 1)) & 255
            elif f == 4:
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                line[i] = (line[i] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        rows.append(line)
        prev = line
    return w, h, bpp, rows


def crop_scale(img, box, s):
    w, h, bpp, rows = img
    x0, y0, x1, y1 = box
    out = []
    for y in range(y0, y1 - s + 1, s):
        r = []
        for x in range(x0, x1 - s + 1, s):
            acc = [0, 0, 0]
            for dy in range(s):
                row = rows[y + dy]
                for dx in range(s):
                    o = (x + dx) * bpp
                    acc[0] += row[o]; acc[1] += row[o + 1]; acc[2] += row[o + 2]
            n = s * s
            r.append((acc[0] // n, acc[1] // n, acc[2] // n))
        out.append(r)
    return out


PAL = [(r * 255 // 5, g * 255 // 6, b * 255 // 5) for r in range(6) for g in range(7) for b in range(6)]


def quant(px):
    r, g, b = px
    return (min(5, (r * 5 + 127) // 255) * 7 + min(6, (g * 6 + 127) // 255)) * 6 + min(5, (b * 5 + 127) // 255)


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
    return bytes(out)


def gif_write(path, frames, delay):
    h, w = len(frames[0]), len(frames[0][0])
    g = bytearray(b'GIF89a' + struct.pack('<HHBBB', w, h, 0xF7, 0, 0))
    pal = PAL + [(0, 0, 0)] * (256 - len(PAL))
    for c in pal:
        g += bytes(c)
    g += b'\x21\xFF\x0BNETSCAPE2.0\x03\x01\x00\x00\x00'   # loop forever
    for f in frames:
        g += b'\x21\xF9\x04\x00' + struct.pack('<H', delay) + b'\x00\x00'
        g += b'\x2C' + struct.pack('<HHHHB', 0, 0, w, h, 0) + b'\x08'
        data = lzw([quant(p) for row in f for p in row])
        for i in range(0, len(data), 255):
            g += bytes([len(data[i:i + 255])]) + data[i:i + 255]
        g += b'\x00'
    g += b'\x3B'
    open(path, 'wb').write(g)


def png_write(path, rows):
    h, w = len(rows), len(rows[0])
    raw = b''.join(b'\x00' + bytes(v for p in row for v in p) for row in rows)
    def chunk(k, d):
        return struct.pack('>I', len(d)) + k + d + struct.pack('>I', zlib.crc32(k + d) & 0xFFFFFFFF)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0))
                           + chunk(b'IDAT', zlib.compress(raw, 6)) + chunk(b'IEND', b''))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('gif')
    ap.add_argument('sheet')
    ap.add_argument('pngs', nargs='+')
    ap.add_argument('--scale', type=int, default=2)
    ap.add_argument('--crop', default='56,66,944,736')
    ap.add_argument('--delay', type=int, default=40, help='GIF frame delay, 1/100 s')
    ap.add_argument('--cols', type=int, default=4)
    a = ap.parse_args()
    box = tuple(int(v) for v in a.crop.split(','))
    frames = [crop_scale(png_read(p), box, a.scale) for p in a.pngs]
    gif_write(a.gif, frames, a.delay)
    fh, fw = len(frames[0]), len(frames[0][0])
    cols = min(a.cols, len(frames))
    nrows = (len(frames) + cols - 1) // cols
    sheet = [[(255, 255, 255)] * (cols * (fw + 4)) for _ in range(nrows * (fh + 4))]
    for i, f in enumerate(frames):
        oy, ox = (i // cols) * (fh + 4), (i % cols) * (fw + 4)
        for y in range(fh):
            sheet[oy + y][ox:ox + fw] = f[y]
    png_write(a.sheet, sheet)
    print(f'{a.gif}: {len(frames)} frames {fw}x{fh}; {a.sheet}: {cols}x{nrows}')


if __name__ == '__main__':
    main()
