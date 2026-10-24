#!/usr/bin/env python3
"""P105 (P140: also prints the scheduler frame count and gfx DL total: "last frame" is only the last log line
   that names a frame, NOT the game's progress; without PORT_P61CHECK node logs nothing after the padscript ends): compact summary of a node / Chrome log: deaths, level loads, scene, heap, null zone, traps, guard, position sanity.
   sum.py LOG"""
import re, sys, math
L = open(sys.argv[1], errors='replace').read().splitlines()
deaths = [re.search(r'frame (\d+)', l).group(1) for l in L if 'func_1507D4F8 call' in l and re.search(r'frame (\d+)', l)]
levels = [(m.group(2), m.group(1)) for l in L for m in [re.search(r'func_1501C710 call \d+ frame (\d+): a0 \S+ a1 0*([0-9A-Fa-f]+)', l)] if m]
scene = [l for l in L if re.search(r'\[p88\] scene', l)]
heap_bad = [l for l in L if '[heap]' in l and ' 0 errors' not in l]
nullz = [l for l in L if 'null zone' in l and '[mem]' not in l]
p78 = [l for l in L if '[p78]' in l]
traps = [l for l in L if re.search(r'RuntimeError|Aborted|abort\(|unreachable', l)]
guard = [l for l in L if '[p97]' in l]
stubs = [l for l in L if 'distinct asm stubs' in l]
bad = []; maxabs = 0.0; npos = 0
for l in L:
    for m in re.finditer(r'pos (\S+) (\S+) (\S+)', l):
        try: v = [float(x) for x in m.groups()]
        except ValueError: continue
        npos += 1
        for x in v:
            if not math.isfinite(x) or abs(x) > 1e5:
                bad.append(l[:150]); break
            maxabs = max(maxabs, abs(x))
frames = [int(x) for x in re.findall(r'frame (\d+)', '\n'.join(L[-400:]))]
print(f"deaths {len(deaths)} at {deaths[:6]} | levels {levels[:8]} | scene lines {len(scene)} | heap-bad {len(heap_bad)} | "
      f"nullzone {len(nullz)} | p78 {len(p78)} | traps {len(traps)} | p97 guard {len(guard)} | pos lines {npos} max|v| {maxabs:.0f} "
      f"bad {len(bad)} | last logged frame {max(frames) if frames else '?'}")
sched = [l for l in L if re.match(r'\[sched\] \d+ frames', l)]
sp = [l for l in L if l.startswith('[sp] tasks submitted')]
print('  progress: ' + (sched[-1][8:60] if sched else 'no [sched] summary') + ' | ' + (re.sub(r', \d+ commands.*', '', sp[-1][5:]) if sp else 'no [sp] summary'))
for l in (heap_bad[:2] + nullz[:2] + p78[:2] + traps[:3] + guard[:2] + bad[:3] + scene[:2] + scene[-1:] + stubs[-1:]):
    print('  ' + l[:200])
