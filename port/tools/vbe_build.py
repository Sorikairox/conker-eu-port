"""Compile the game TUs for the vbe memory model (port/tools/vbe.py, docs/port/MEMORY.md):
    C --(-O0 IR, no optnone)--> .ll --vbe.py--> .v.ll --(-O1)--> port/build/vobj/<tag>.o
Inputs: the TUs that the census compiled ("ok" in port/build/census/files.tsv, minus
port/exclude.txt) plus the PC-side game TUs given on the command line (port/boot/*.c).
Writes port/build/vbe_report.txt (transform counts). Runs inside the conker-emsdk container."""
import json, os, subprocess, sys, collections, concurrent.futures as cf
sys.path.insert(0, os.path.dirname(__file__))
import census

OUT = 'port/build'
LL, VOBJ = f'{OUT}/ll', f'{OUT}/vobj'


def tag_of(path):
    return os.path.relpath(path, census.SRC).replace('/', '__') if path.startswith(census.SRC) else \
        'port__' + os.path.basename(path)[:-2]


def to_ll(path):
    """phase 1: C -> -O0 IR (incremental)"""
    tag = tag_of(path)
    ll = f'{LL}/{tag}.ll'
    if os.path.exists(ll) and os.path.getmtime(ll) > max(os.path.getmtime(path), os.path.getmtime('port/ultra/port_prefix.h')):  # P19: prefix too
        return tag, 0, ''
    base = [a for a in census.BASE if a not in ('-c', '-O1')]
    p = subprocess.run(base + census.PORT_RELAX + ['-Wno-everything', '-S', '-emit-llvm', '-O0', '-Xclang',
                       '-disable-O0-optnone', path, '-o', ll], capture_output=True, text=True)
    return tag, p.returncode and 1, p.stderr[-2000:]


def build_one(tag):
    """phase 3: vbe rewrite (+ signature normalisation) and -O1 compile"""
    ll, vll, obj = f'{LL}/{tag}.ll', f'{LL}/{tag}.v.ll', f'{VOBJ}/{tag}.o'
    p = subprocess.run([sys.executable, 'port/tools/vbe.py', ll, vll, SIGDB], capture_output=True, text=True)
    if p.returncode:
        return tag, 2, p.stderr[-2000:]
    stats = p.stdout.strip()
    q = subprocess.run(['emcc', '-c', '-O1', '-g0', '-Wno-everything', vll, '-o', obj], capture_output=True, text=True)
    if q.returncode:
        return tag, 3, q.stderr[-2000:]
    return tag, 0, stats


SIGDB = f'{OUT}/sigdb.json'


def main():
    os.makedirs(LL, exist_ok=True); os.makedirs(VOBJ, exist_ok=True)
    ex = {l.split()[0] for l in open('port/exclude.txt') if l.strip() and not l.startswith('#')}
    files = []
    for l in open(f'{OUT}/census/files.tsv').read().splitlines()[1:]:
        f, _, _, ok = l.split('\t')
        if ok == 'ok' and f not in ex:
            files.append(f'{census.SRC}/{f}')
    files += sys.argv[1:]
    tot, fails = collections.Counter(), []
    import sigs
    with cf.ThreadPoolExecutor(os.cpu_count() or 4) as pool:
        tags = []
        for tag, rc, msg in pool.map(to_ll, files):
            (fails.append((tag, rc, msg)) if rc else tags.append(tag))
        defs, sites = {}, collections.defaultdict(collections.Counter)
        for tag in tags:  # phase 2: one canonical signature per function
            sigs.scan(open(f'{LL}/{tag}.ll').read(), defs, sites)
        can = sigs.canonical(defs, sites)
        json.dump(can, open(SIGDB, 'w'))
        tot['mismatched_functions'] = sum(1 for f, c in sites.items() if len(c) > 1 or
                                          (f in defs and json.dumps(list(defs[f])) not in c))
        for tag, rc, msg in pool.map(build_one, tags):
            if rc:
                fails.append((tag, rc, msg))
                continue
            for kv in msg.split()[1:]:
                k, v = kv.split('=')
                tot[k] += int(v)
    with open(f'{OUT}/vbe_report.txt', 'w') as f:
        f.write(f'vbe TUs: {len(files) - len(fails)} ok, {len(fails)} failed\n')
        f.write('(call_fixed = call sites rewritten to the canonical signature, port/tools/sigs.py)\n')
        f.write('transforms: ' + ' '.join(f'{k}={v}' for k, v in tot.most_common()) + '\n')
        for tag, rc, msg in fails:
            f.write(f'--- {tag} (stage {rc})\n{msg}\n')
    print(open(f'{OUT}/vbe_report.txt').read()[:3000])
    if fails:
        sys.exit(1)


if __name__ == '__main__':
    main()
