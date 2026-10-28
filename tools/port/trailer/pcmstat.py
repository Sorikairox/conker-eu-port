#!/usr/bin/env python3
"""P354 trailer: loudness of a captured shot's audio.pcm (stereo s16 LE at RATE) per WINDOW seconds, and a WAV copy.
   pcmstat.py SHOT_DIR [WINDOW=1] [--wav OUT.wav]"""
import sys, array, math, json, os, wave
d = sys.argv[1]; win = float(sys.argv[2]) if len(sys.argv) > 2 and not sys.argv[2].startswith('--') else 1.0
meta = json.load(open(os.path.join(d, 'meta.json'))); rate = meta['audio']['rate']
a = array.array('h'); a.frombytes(open(os.path.join(d, 'audio.pcm'), 'rb').read())
n = len(a) // 2; w = int(rate * win)
for i in range(0, n, w):
    seg = a[2 * i: 2 * min(n, i + w)]
    rms = math.sqrt(sum(v * v for v in seg) / max(1, len(seg)))
    print(f"{i / rate:6.1f}s rms {rms:7.0f} {'#' * int(rms / 150)}")
if '--wav' in sys.argv:
    out = sys.argv[sys.argv.index('--wav') + 1]
    with wave.open(out, 'wb') as f: f.setnchannels(2); f.setsampwidth(2); f.setframerate(rate); f.writeframes(a.tobytes())
    print('wav', out)
