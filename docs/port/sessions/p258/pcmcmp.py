#!/usr/bin/env python3
# P258: compare two ?p258pcm logs (grep -o '\[p258pcm\].*' chrome.log) window by window: hash same/diff, rms, mp3 cmds.
import sys, re
def rd(f):
    out = []
    for l in open(f):
        m = re.search(r'frames (\d+)-(\d+): (\d+) samples hash (\w+) rms ([\d.]+) peak (\d+) nonzero (\d+)% mp3 (\d+)', l)
        if m: out.append((int(m[1]), m[4], float(m[5]), int(m[6]), int(m[8])))
    return out
A, B = rd(sys.argv[1]), rd(sys.argv[2]); lim = int(sys.argv[3]) if len(sys.argv) > 3 else 10**9
st = {}; pa = pb = 0; shown = 0
for a, b in zip(A, B):
    if a[0] > lim: break
    da, db = a[4] - pa, b[4] - pb; pa, pb = a[4], b[4]
    k = ('same' if a[1] == b[1] else 'DIFF') + (' mp3' if da or db else ' nomp3')
    st[k] = st.get(k, 0) + 1
    if a[1] != b[1] and shown < int(sys.argv[4] if len(sys.argv) > 4 else 12):
        shown += 1
        print(f'{a[0]}: rms {a[2]} / {b[2]} ({100*(b[2]-a[2])/max(a[2],1):+.2f}%) peak {a[3]} / {b[3]} mp3 cmds {da} / {db}' + ('' if a[0] == b[0] else f' FRAME {b[0]}'))
print(st)
