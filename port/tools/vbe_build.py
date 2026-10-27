"""Compile the game TUs for the vbe memory model (port/tools/vbe.py, docs/port/MEMORY.md):
    C --(-O0 IR, no optnone)--> .ll --vbe.py--> .v.ll --(-O1)--> port/build/vobj/<tag>.o
Inputs: the TUs that the census compiled ("ok" in port/build/census/files.tsv, minus
port/exclude.txt) plus the PC-side game TUs given on the command line (port/boot/*.c).
Writes port/build/vbe_report.txt (transform counts). Runs inside the conker-emsdk container.

P327, incremental: phase 1 (C -> .ll) is redone only when the key of the TU changes (flags + contents of the source
and of every header in its clang -MD depfile, port/tools/depkey.py; before P327 it compared mtimes of the .c and
port_prefix.h only, so header edits were missed). Phase 2 (canonical signatures) is skipped when no .ll changed and
the TU list is the same. Phase 3 (vbe.py + -O1) is redone only when the .ll key, the signature table or the vbe
tools change. When anything was rebuilt (or the report changed) it creates port/build/vbe.dirty; the Makefile then
touches vbe.stamp, so a no-op build relinks nothing."""
import json, os, subprocess, sys, collections, concurrent.futures as cf
sys.path.insert(0, os.path.dirname(__file__))
import census, srcfix, depkey

OUT = 'port/build'
LL, VOBJ = f'{OUT}/ll', f'{OUT}/vobj'


def tag_of(path):
    return os.path.relpath(path, census.SRC).replace('/', '__') if path.startswith(census.SRC) else \
        'port__' + os.path.basename(path)[:-2]


LL_FLAGS = ['-Wno-everything', '-S', '-emit-llvm', '-O0', '-Xclang', '-disable-O0-optnone']


def ll_key(src, deps):
    return depkey.key([' '.join(census.BASE + census.PORT_RELAX + LL_FLAGS), src], [src] + deps)


def to_ll(path):
    """phase 1: C -> -O0 IR (incremental, P327: content key of the source and its headers)"""
    tag = tag_of(path)
    ll, kf = f'{LL}/{tag}.ll', f'{LL}/{tag}.key'
    fx = srcfix.path_for(os.path.relpath(path, census.SRC)) if path.startswith(census.SRC) else path
    src = fx if path.startswith(census.SRC) and os.path.exists(fx) else path
    old = depkey.load(kf)
    if old and os.path.exists(ll) and old.get('key') == ll_key(src, old.get('deps', [])):
        return tag, 0, '', False
    base = [a for a in census.BASE if a not in ('-c', '-O1')]
    src = path
    if path.startswith(census.SRC):  # P23: census left a patched copy (port/tools/srcfix.py)
        fx = srcfix.path_for(os.path.relpath(path, census.SRC))
        if os.path.exists(fx):
            src = fx
            base = base + ['-iquote', os.path.dirname(path)]
    if os.path.exists(kf):
        os.remove(kf)
    dep = f'{LL}/{tag}.d'
    p = subprocess.run(base + census.PORT_RELAX + LL_FLAGS + ['-MD', '-MF', dep, src, '-o', ll],
                       capture_output=True, text=True)
    if p.returncode == 0:
        deps = [d for d in depkey.parse_depfile(dep) or [] if d != src]
        depkey.save(kf, {'key': ll_key(src, deps), 'deps': deps})
    return tag, p.returncode and 1, p.stderr[-2000:], True


TOOLS = ['port/tools/vbe.py', 'port/tools/sigs.py', 'port/tools/icall.py']
O1_FLAGS = ['-c', '-O1', '-g0', '-Wno-everything']


def build_one(tag, sig_hash=''):
    """phase 3: vbe rewrite (+ signature normalisation) and -O1 compile (P327: skipped when its key is unchanged)"""
    ll, vll, obj = f'{LL}/{tag}.ll', f'{LL}/{tag}.v.ll', f'{VOBJ}/{tag}.o'
    kf = f'{VOBJ}/{tag}.key'
    k = depkey.key([(depkey.load(f'{LL}/{tag}.key') or {}).get('key', 'none'), sig_hash, ' '.join(O1_FLAGS)], TOOLS)
    old = depkey.load(kf)
    if old and old.get('key') == k and os.path.exists(obj) and os.path.exists(vll + '.isig'):
        return tag, 0, old['stats'], False
    if os.path.exists(kf):
        os.remove(kf)
    p = subprocess.run([sys.executable, 'port/tools/vbe.py', ll, vll, SIGDB], capture_output=True, text=True)
    if p.returncode:
        return tag, 2, p.stderr[-2000:], True
    stats = p.stdout.strip()
    q = subprocess.run(['emcc'] + O1_FLAGS + [vll, '-o', obj], capture_output=True, text=True)
    if q.returncode and DBG_CFLAGS and O1_FLAGS[1] != '-O1':
        # P342 debug build: at -O0 the wasm backend rejects a function address with a constant offset that -O1 folds
        # (game_EF410.c bomb_explode: "Function addresses with offsets not supported"); such a TU is built at -O1 -g
        q = subprocess.run(['emcc', '-c', '-O1', '-g', '-Wno-everything', vll, '-o', obj], capture_output=True, text=True)
        stats += ' dbg_O1_fallback=1'
    if q.returncode:
        return tag, 3, q.stderr[-2000:], True
    depkey.save(kf, {'key': k, 'stats': stats})
    return tag, 0, stats, True


SIGDB = f'{OUT}/sigdb.json'

# P342: source-level debug build (tools/port/scripts/debug_build.sh runs this in its own copy of the tree,
# port/build-dbg/tree, never in the release tree). PORT_DBG_CFLAGS (e.g. "-g -fdebug-prefix-map=...") replaces -g0 in
# the C -> IR step, so the IR carries DWARF metadata through vbe.py; the object is compiled at PORT_DBG_OPT (default
# -O0) with -g. Unset (the release build): flags, keys and output are unchanged.
DBG_CFLAGS = os.environ.get('PORT_DBG_CFLAGS', '').split()
if DBG_CFLAGS:
    census.BASE = [a for a in census.BASE if a != '-g0'] + DBG_CFLAGS
    O1_FLAGS = ['-c', os.environ.get('PORT_DBG_OPT', '-O0'), '-g', '-Wno-everything']


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
    state_f = f'{OUT}/vbe_state.json'
    state = depkey.load(state_f) or {}
    nll = nobj = 0
    with cf.ThreadPoolExecutor(os.cpu_count() or 4) as pool:
        tags = []
        for tag, rc, msg, rebuilt in pool.map(to_ll, files):
            nll += rebuilt
            (fails.append((tag, rc, msg)) if rc else tags.append(tag))
        sigs_tool = depkey.file_hash('port/tools/sigs.py')  # P341: a sigs.py change re-runs phase 2
        if nll == 0 and not fails and state.get('tags') == tags and state.get('sigs') == sigs_tool and os.path.exists(SIGDB):
            tot['mismatched_functions'] = state['mismatched_functions']  # P327: same .ll set, same signatures
        else:
            defs, sites = {}, collections.defaultdict(collections.Counter)
            for tag in tags:  # phase 2: one canonical signature per function
                sigs.scan(open(f'{LL}/{tag}.ll').read(), defs, sites)
            can = sigs.canonical(defs, sites)
            depkey.write_if_changed(SIGDB, json.dumps(can))
            tot['mismatched_functions'] = sum(1 for f, c in sites.items() if len(c) > 1 or
                                              (f in defs and json.dumps(list(defs[f])[:2]) not in c))
            depkey.save(state_f, {'tags': tags, 'mismatched_functions': tot['mismatched_functions'], 'sigs': sigs_tool})
        depkey._memo.pop(SIGDB, None)
        sig_hash = depkey.file_hash(SIGDB)
        for tag, rc, msg, rebuilt in pool.map(lambda t: build_one(t, sig_hash), tags):
            nobj += rebuilt
            if rc:
                fails.append((tag, rc, msg))
                continue
            for kv in msg.split()[1:]:
                k, v = kv.split('=')
                tot[k] += int(v)
    rep = (f'vbe TUs: {len(files) - len(fails)} ok, {len(fails)} failed\n'
           '(call_fixed = call sites rewritten to the canonical signature, port/tools/sigs.py)\n'
           'transforms: ' + ' '.join(f'{k}={v}' for k, v in tot.most_common()) + '\n' +
           ''.join(f'--- {tag} (stage {rc})\n{msg}\n' for tag, rc, msg in fails))
    changed = depkey.write_if_changed(f'{OUT}/vbe_report.txt', rep)
    if nll or nobj or changed or fails or not os.path.exists(f'{OUT}/vbe.stamp'):
        open(f'{OUT}/vbe.dirty', 'w').close()
    print(f'vbe_build: {nll} .ll and {nobj} objects rebuilt of {len(files)} TUs')
    print(rep[:3000])
    if fails:
        sys.exit(1)


if __name__ == '__main__':
    main()
