#!/usr/bin/env python3
"""P354 trailer: rough tempo / beat grid of a captured shot's audio.pcm (pure Python: onset envelope at 100 Hz, autocorrelation
for the tempo, then the beat phase with the strongest onsets).  beats.py SHOT_DIR [FROM_S] [TO_S]"""
import sys, array, json, os, math
d = sys.argv[1]; t0 = float(sys.argv[2]) if len(sys.argv) > 2 else 0; t1 = float(sys.argv[3]) if len(sys.argv) > 3 else 1e9
rate = json.load(open(os.path.join(d, 'meta.json')))['audio']['rate']
a = array.array('h'); a.frombytes(open(os.path.join(d, 'audio.pcm'), 'rb').read())
n = len(a) // 2; hop = rate // 100
i0 = int(t0 * rate); i1 = min(n, int(t1 * rate))
env = []
for i in range(i0, i1 - hop, hop):
    s = 0
    for k in range(i, i + hop, 2): v = a[2 * k] + a[2 * k + 1]; s += v * v
    env.append(math.log1p(s / (hop / 2)))
on = [max(0.0, env[i] - env[i - 1]) for i in range(1, len(env))]
m = sum(on) / len(on); on = [x - m for x in on]
best = []
for lag in range(33, 101):   # 60..180 BPM
    c = sum(on[i] * on[i + lag] for i in range(len(on) - lag)) / (len(on) - lag)
    best.append((c, lag))
best.sort(reverse=True)
print('top lags (centiseconds -> BPM):', ', '.join(f'{l} ({6000 / l:.1f}) {c:.3f}' for c, l in best[:6]))
lag = best[0][1]
ph = max(range(lag), key=lambda p: sum(on[i] for i in range(p, len(on), lag)))
beats = [t0 + (ph + k * lag + 1) / 100 for k in range((len(on) - ph) // lag + 1)]
print(f'period {lag / 100:.2f} s, first beat {beats[0]:.2f} s')
print('beats:', ' '.join(f'{b:.2f}' for b in beats[:40]))
# strongest onsets (for accent cuts)
top = sorted(range(len(on)), key=lambda i: -on[i])[:25]
print('strongest onsets:', ' '.join(f'{t0 + (i + 1) / 100:.2f}' for i in sorted(top)))
