#!/usr/bin/env python3
"""P322: repo-wide function rename driven by tools/eu_port/names.tsv (see docs/RENAMING.md).

names.tsv (tab separated, '#' comments): old<TAB>new<TAB>short description. It is the source of truth: add a row,
run `--check`, then apply (no flag), then `--verify`. Rows that are already applied are skipped, so the whole table
can be re-run at any time (e.g. after a merge brought new uses of an old name).

What a rename changes (sources of truth only; generated files are rebuilt by verify_all's clean re-split):
  * every whole-word use of the old name in tracked files in scope (SCOPE below): conker/src_eu (C, GLOBAL_ASM paths),
    conker/include, the EU symbol / undefined-symbol lists, conker/Makefile + conker.eu.yaml, port/ (Makefile --wrap
    and EXPORTED_FUNCTIONS lists, port/tools tables, platform C), tools/ (registries such as
    tools/port/verify_registry.tsv, platform_replaced.tsv, nm_folded.tsv, difftest selftest cases and scripts), and the
    difftest setup / mutant files that verify_registry.tsv points at (they are live inputs even under docs/).
    Also `_old` (emscripten exports) and `__wrap_old` / `__real_old` (ld --wrap).
  * conker/symbol_addrs.eu.txt: splat names an unlisted function func_<EU vram>. If the old name is listed there
    (a US name mapped to its EU address) the name is replaced in place; otherwise `new = 0x<EU addr>; // type:func`
    is appended (address from conker/build/conker.eu.map). The re-split then names the asm file, the glabel and every
    jal / table reference after the new name.
  * tracked files whose path contains the old name (e.g. tools/port/difftest/cases/func_X.c) are `git mv`ed.
  * `/* was <old> */` is inserted on the line above the C definition in conker/src_eu (or above the GLOBAL_ASM pragma
    when the function has no C body).
Left alone: conker/src (the US version), US/debug/ects symbol files, every *.md, docs/ (except registry-referenced
difftest inputs), *.log, port_work/, historical logs (tools/eu_port/repair_log.tsv, tools/port/pilot/, baseline/),
vendored tools (n64splat, asm-processor, asm-differ, mips_to_c, decomp-permuter), and text of the form `was <old>`.

Usage (repo root, after eval "$(tools/eu_port/wt.sh env <name>)"):
  tools/eu_port/rename.py --check [OLD ...]   dry run: every file/line it would change
  tools/eu_port/rename.py [OLD ...]           apply (all rows, or only the listed old names)
  tools/eu_port/rename.py --verify            verify_all.sh (clean re-split, must stay byte-identical) + NM link +
                                              no in-scope use of any old name left
"""
import os, re, subprocess, sys

ROOT = os.path.realpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
TABLE = 'tools/eu_port/names.tsv'
SYMS = 'conker/symbol_addrs.eu.txt'
MAP = 'conker/build/conker.eu.map'
REG = 'tools/port/verify_registry.tsv'
SCOPE = ('conker/src_eu/', 'conker/include/', 'conker/symbol_addrs.eu.txt', 'conker/undefined_funcs.eu.txt',
         'conker/undefined_syms.eu.txt', 'conker/conker.eu.yaml', 'conker/Makefile', 'Makefile', 'port/', 'tools/')
SKIP = ('tools/n64splat/', 'tools/asm-processor/', 'tools/asm-differ/', 'tools/mips_to_c/', 'tools/decomp-permuter/',
        'tools/eu_port/baseline/', 'tools/port/pilot/', 'tools/eu_port/repair_log.tsv', TABLE,
        'tools/eu_port/rename.py', 'port_work/', 'docs/', 'conker/src/')
SKIP_EXT = ('.md', '.log', '.png', '.jpg', '.bin', '.z64', '.o', '.wasm', '.gz', '.zip')
SYM_HDR = '// P322 rename.py: functions renamed through tools/eu_port/names.tsv (name = EU address)'
IDENT = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*$')


def word(name):
    """whole word, also as _name / __wrap_name / __real_name; never inside `was name` (the kept original name)"""
    return re.compile(r'(?<![A-Za-z0-9_])(?<!was )((?:__wrap_|__real_|_)?)' + re.escape(name) + r'(?![A-Za-z0-9_])')


def git(*a):
    return subprocess.run(('git',) + a, cwd=ROOT, capture_output=True, text=True, check=True).stdout


def read_table():
    rows = []
    for n, line in enumerate(open(os.path.join(ROOT, TABLE)), 1):
        line = line.rstrip('\n')
        if not line.strip() or line.startswith('#'):
            continue
        f = line.split('\t')
        if f[0] == 'old':
            continue
        if len(f) < 2 or not IDENT.match(f[0]) or not IDENT.match(f[1]):
            sys.exit('%s:%d: bad row %r (want old<TAB>new<TAB>description)' % (TABLE, n, line))
        rows.append((f[0], f[1], f[2] if len(f) > 2 else ''))
    olds = [r[0] for r in rows]; news = [r[1] for r in rows]
    for x in set(olds + news):
        if olds.count(x) > 1 or news.count(x) > 1 or (x in olds and x in news):
            sys.exit('%s: %s appears twice (chains / duplicates are not allowed)' % (TABLE, x))
    return rows


def scope_files():
    files = set()
    for p in git('ls-files').splitlines():
        if p.startswith(SCOPE) and not p.startswith(SKIP) and not p.endswith(SKIP_EXT):
            files.add(p)
    # difftest inputs named by the registry (setup_file / mutant_file columns, comma lists) are live, even under docs/
    try:
        for line in open(os.path.join(ROOT, REG)).read().splitlines()[1:]:
            f = line.split('\t')
            for col in (2, 4):
                for p in (f[col].split(',') if len(f) > col else []):
                    if p.strip() and os.path.isfile(os.path.join(ROOT, p.strip())):
                        files.add(p.strip())
    except OSError:
        pass
    return sorted(files)


def read(p):
    try:
        with open(os.path.join(ROOT, p), encoding='utf-8') as fh:
            return fh.read()
    except (UnicodeDecodeError, OSError):
        return None


_MAP = None


def map_addr(names):
    global _MAP
    if _MAP is None:    # parsed once: name -> address (re-reading the map per row made big tables take hours)
        _MAP = {}
        try:
            for m in re.finditer(r'^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_][A-Za-z0-9_]*)$', open(os.path.join(ROOT, MAP)).read(), re.M):
                _MAP.setdefault(m.group(2), int(m.group(1), 16))
        except OSError:
            pass
    for n in names:
        if n in _MAP:
            return _MAP[n]
    return None


_TOK = re.compile(r'[A-Za-z_][A-Za-z0-9_]*')


def tokens(text):
    """identifiers in text, also without a _ / __wrap_ / __real_ prefix (the forms word() matches)"""
    out = set()
    for w in set(_TOK.findall(text)):
        out.add(w)
        for pre in ('__wrap_', '__real_', '_'):
            if w.startswith(pre):
                out.add(w[len(pre):])
    return out


DEF = r'^[A-Za-z_][^\n;#/(){}=]*?\b%s\s*\([^;{]*?\)\s*\{'
PRAG = r'^#pragma GLOBAL_ASM\("[^"]*/%s\.s"\)'


def comment_site(texts, old, new, cand=None):
    """(path, line index) above which `/* was old */` goes, or None when present already / no site"""
    for rx in (DEF, PRAG):
        for p, t in texts.items():
            if cand is not None and p not in cand:
                continue
            if not p.startswith('conker/src_eu/') or not p.endswith('.c'):
                continue
            m = re.search(rx % re.escape(new), t, re.M)
            if m:
                ln = t.count('\n', 0, m.start())
                above = t.split('\n')[max(0, ln - 4):ln]
                if any(('was ' + old) in a for a in above):
                    return 'present'
                return (p, ln)
    return None


_CMT = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:[^"\\\n]|\\.)*"', re.S)   # comments and string literals


def code_only(path, text):
    """text without comments (C / headers / asm-processor) or '#' note lines (tsv, txt, Makefile, yaml)"""
    if path.endswith(('.c', '.h', '.inc', '.cpp')):
        return _CMT.sub(' ', text)
    return re.sub(r'(^|\s)#[^\n]*', ' ', text)


def plan(rows, only):
    files = scope_files()
    texts = {p: read(p) for p in files}
    texts = {p: t for p, t in texts.items() if t is not None}
    edits = {}          # path -> new text
    report = []
    moves = []
    symtxt = texts.get(SYMS, '')
    sym_add = []
    # identifier -> files using it, so each row only looks at the files that mention its names
    ren = {o: n for o, n, _ in rows}    # descriptions written to the symbol list use the new names
    inv = {}
    for p, t in texts.items():
        for w in tokens(t):
            inv.setdefault(w, set()).add(p)
    for old, new, desc in rows:
        if only and old not in only:
            continue
        rx = word(old)
        hits = 0
        # collision: the new name is already used for something else (fine when it is our own earlier rename,
        # i.e. the symbol list already maps new to old's address, e.g. a merge brought new uses of the old name)
        ours = re.search(r'^// was %s:' % re.escape(old), symtxt, re.M) or (
            # renamed in place (the old name was already listed, possibly a US name at another EU address):
            # the symbol list now has the new name and no longer the old one
            re.search(r'^%s\s*=' % re.escape(new), symtxt, re.M) and
            not re.search(r'^%s\s*=' % re.escape(old), symtxt, re.M)) or (
            map_addr([new]) is not None and map_addr([new]) == map_addr([old])) or (
            # NON_MATCHING-only functions get no symbol entry: the `/* was old */` comment marks them as done
            any(('/* was %s */' % old) in texts[p] for p in inv.get(new, ()) if p.startswith('conker/src_eu/')))
        if not ours:
            # only code counts: comments (naming proposals, notes that mention the same function) and '#' note lines
            # are not a use of the name
            used = [p for p in sorted(inv.get(new, ())) if word(new).search(edits.get(p, texts[p]))
                    and word(new).search(code_only(p, edits.get(p, texts[p])))]
            if used:
                sys.exit('%s: new name %s is already used in %s' % (old, new, ', '.join(used[:5])))
        for p in files:
            t = edits.get(p, texts.get(p))
            if t is None:
                continue
            if p in inv.get(old, ()) and rx.search(t):
                inv.setdefault(new, set()).add(p)
                out = []
                for i, line in enumerate(t.split('\n'), 1):
                    if rx.search(line):
                        nl = rx.sub(lambda m: m.group(1) + new, line)
                        out.append(nl)
                        hits += 1
                        report.append('%s:%d: %s\n    -> %s' % (p, i, line.strip()[:150], nl.strip()[:150]))
                    else:
                        out.append(line)
                edits[p] = '\n'.join(out)
            if old in p and re.search(r'(?<![A-Za-z0-9_])' + re.escape(old) + r'(?![A-Za-z0-9_])', p):
                np_ = re.sub(r'(?<![A-Za-z0-9_])' + re.escape(old) + r'(?![A-Za-z0-9_])', new, p)
                moves.append((p, np_)); report.append('git mv %s %s' % (p, np_))
        # symbol list: rename in place (old listed) or add new = EU address
        symnow = edits.get(SYMS, symtxt)
        if not re.search(r'^' + re.escape(new) + r'\s*=', symnow, re.M):
            a = map_addr([old, new])
            if a is None and hits:
                # NON_MATCHING-only function (code inside an asm routine split out as its own C function): the
                # matching build has no such symbol, so there is nothing to list; the source rename is enough
                report.append('NOTE: %s has no address in %s (NON_MATCHING-only): no symbol entry' % (old, MAP))
            elif a is None:
                sys.exit('%s: no address for %s in %s (build first: tools/eu_port/verify_all.sh)' % (old, old, MAP))
            else:
                if re.search(r'^\s*\S+\s*=\s*0x%08X\s*;' % a, symnow, re.M | re.I):
                    sys.exit('%s: address 0x%08X already has another name in %s' % (old, a, SYMS))
                d = _TOK.sub(lambda m: ren.get(m.group(0), m.group(0)), desc)
                sym_add.append('// was %s: %s\n%-31s = 0x%08X; // type:func' % (old, d, new, a))
                report.append('%s: add %s = 0x%08X' % (SYMS, new, a))
                hits += 1
        if hits == 0:
            report.append('%s -> %s: already applied' % (old, new))
        if sym_add:
            t = edits.get(SYMS, symtxt).rstrip('\n')
            if SYM_HDR not in t:
                t += '\n\n' + SYM_HDR
            edits[SYMS] = t + '\n' + '\n'.join(sym_add) + '\n'
            sym_add = []
        # `/* was old */` above the definition
        merged = dict(texts); merged.update(edits)
        site = comment_site(merged, old, new, inv.get(new, set()))
        if site is None:
            report.append('WARNING: no C definition or GLOBAL_ASM pragma of %s in conker/src_eu: add `/* was %s */` by hand'
                          % (new, old))
        elif site != 'present':
            p, ln = site
            lines = merged[p].split('\n')
            lines.insert(ln, '/* was %s */' % old)
            edits[p] = '\n'.join(lines)
            report.append('%s:%d: insert /* was %s */ above the definition of %s' % (p, ln + 1, old, new))
    # US source sharing a header: warn (the US build is left alone)
    for old, new, _ in rows:
        if (not only or old in only) and any(p.startswith('conker/include/') and word(old).search(t)
                                             for p, t in texts.items()):
            us = subprocess.run(['git', 'grep', '-lw', old, '--', 'conker/src'], cwd=ROOT, capture_output=True, text=True).stdout
            if us.strip():
                report.append('WARNING: conker/include changed while conker/src (US) still uses %s' % old)
    return edits, moves, report


def verify(rows):
    env = dict(os.environ, PATH='/Applications/Docker.app/Contents/Resources/bin:' + os.environ.get('PATH', ''))
    ok = True
    left = []
    olds = {old for old, new, _ in rows}
    for p in scope_files():
        t = read(p)
        if t is None:
            continue
        # comments (descriptions in the symbol list mention other functions) are not uses
        tc = code_only(p, t) if p != SYMS else re.sub(r'//[^\n]*', ' ', t)
        for old in sorted(olds & tokens(tc)):
            if word(old).search(tc):
                left.append('%s still uses %s' % (p, old))
    print('old names left in scope: %d' % len(left)); print('\n'.join(left[:20])); ok &= not left
    r = subprocess.run(['tools/eu_port/verify_all.sh'], cwd=ROOT, env=env, capture_output=True, text=True)
    print(r.stdout.strip()[-600:]); print('verify_all rc %d' % r.returncode); ok &= r.returncode == 0
    ct = os.environ.get('CONKERDEV')
    if not ct:
        print('NM link: skipped (CONKERDEV not set; eval "$(tools/eu_port/wt.sh env <name>)")'); ok = False
    else:
        r = subprocess.run(['docker', 'exec', '-w', '/conker', ct, 'make', '-C', 'conker', 'VERSION=eu',
                            'NON_MATCHING=1', '-j4'], cwd=ROOT, env=env, capture_output=True, text=True)
        print((r.stdout + r.stderr).strip()[-300:]); print('NM link rc %d' % r.returncode); ok &= r.returncode == 0
    print('VERIFY OK' if ok else 'VERIFY FAILED')
    return 0 if ok else 1


def main():
    args = sys.argv[1:]
    root = os.environ.get('CONKER_ROOT')
    if not os.path.exists('/.dockerenv') and (not root or os.path.realpath(os.path.expanduser(root)) != ROOT):
        sys.exit('refusing: CONKER_ROOT must be this checkout (%s); run eval "$(tools/eu_port/wt.sh env <name>)"' % ROOT)
    rows = read_table()
    if '--verify' in args:
        sys.exit(verify(rows))
    check = '--check' in args
    only = [a for a in args if not a.startswith('--')]
    for o in only:
        if o not in [r[0] for r in rows]:
            sys.exit('%s is not an old name in %s' % (o, TABLE))
    edits, moves, report = plan(rows, only)
    print('\n'.join(report))
    if check:
        print('--check: %d files would change, %d moves (nothing written)' % (len(edits), len(moves)))
        return
    for p, t in edits.items():
        with open(os.path.join(ROOT, p), 'w', encoding='utf-8') as fh:
            fh.write(t)
    for a, b in moves:
        git('mv', a, b)
    print('applied: %d files changed, %d moves. Next: tools/eu_port/rename.py --verify (clean re-split + checks)'
          % (len(edits), len(moves)))


if __name__ == '__main__':
    main()
