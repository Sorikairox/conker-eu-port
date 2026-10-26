#!/usr/bin/env python3
"""P322: repo-wide function and global (D_ data symbol) rename driven by tools/eu_port/names.tsv (see docs/RENAMING.md).

names.tsv (tab separated, '#' comments): old<TAB>new<TAB>short description. It is the source of truth: add a row,
run `--check`, then apply (no flag), then `--verify`. Rows that are already applied are skipped, so the whole table
can be re-run at any time (e.g. after a merge brought new uses of an old name).

What a rename changes (P329: port-web has only this mode; the byte-matching build and its symbol lists / splat config
are on branch exact-byte-decomp-wip): every whole-word use of the old name in tracked files under conker/src_eu,
conker/include, port/ (Makefile --wrap and EXPORTED_FUNCTIONS lists, port/tools tables, platform C, and the frozen
symbol table port/symbols/symbols.tsv, so later builds and difftest see the new name at the same address) and tools/
(registries such as tools/port/verify_registry.tsv, platform_replaced.tsv, nm_folded.tsv, difftest selftest cases and
scripts, test inputs under tools/port/testdata), and the `/* was <old> */` comment above the definition.
  * a global (old name D_<ADDR>) has no C definition: `/* was <old> */` is appended to its file-scope declaration
    lines instead; the build tools find its address through names.tsv (n64mem.RENAMED_FROM).
  * tracked files whose path contains the old name (e.g. tools/port/difftest/cases/func_X.c) are `git mv`ed.
  * a function with no table row (a C-only helper split out of an asm routine) gets no row.
Not touched: docs/ (history), *.log, port_work/, and text of the form `was <old>`.
--verify = old names left in scope + tools/eu_port/check.sh. (--port, the P328 name of this mode, is accepted.)

Usage (repo root, after eval "$(tools/eu_port/wt.sh env <name>)"):
  tools/eu_port/rename.py --check [OLD ...]   dry run: every file/line it would change
  tools/eu_port/rename.py [OLD ...]           apply (all rows, or only the listed old names)
  tools/eu_port/rename.py --verify            old names left + tools/eu_port/check.sh
                                              no in-scope use of any old name left
"""
import os, re, subprocess, sys

ROOT = os.path.realpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
TABLE = 'tools/eu_port/names.tsv'
REG = 'tools/port/verify_registry.tsv'
SCOPE = ('conker/src_eu/', 'conker/include/', 'port/', 'tools/')
SKIP = (TABLE, 'tools/eu_port/rename.py', 'port_work/', 'docs/', 'port/symbols/ido_cc.tsv')
SKIP_EXT = ('.md', '.log', '.png', '.jpg', '.bin', '.z64', '.o', '.wasm', '.gz', '.zip')
IDENT = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*$')
PORT = True    # P328 port mode is the only mode since P329 (--port still accepted)
PORT_TABLE = 'port/symbols/symbols.tsv'


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
    if _MAP is None:   # P328: addresses from the frozen port symbol table
        _MAP = {}
        for line in open(os.path.join(ROOT, PORT_TABLE)):
            f = line.split('\t')
            if not line.startswith('#') and len(f) > 1:
                _MAP.setdefault(f[0], int(f[1], 16))
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
DEF2 = r'^[A-Za-z_][^\n;#/(){}=]*?\b%s\s*\('


def def2(t, name):
    """P329 (no GLOBAL_ASM pragmas any more): a definition DEF misses: `{` on a later line, multi-line parameters,
    K&R parameter declarations. The first declarator `name(` whose balanced `)` is followed by `{` (or by K&R
    declarations, then `{`)."""
    for m in re.finditer(DEF2 % re.escape(name), t, re.M):
        i, d = m.end() - 1, 0
        while i < len(t):
            d += {'(': 1, ')': -1}.get(t[i], 0); i += 1
            if d == 0: break
        rest = t[i:i + 400]
        if re.match(r'\s*\{', rest) or re.match(r'\s*([A-Za-z_][\w\s\*,\[\]]*;\s*)+\{', rest):
            return m
    return None


def comment_site(texts, old, new, cand=None):
    """(path, line index) above which `/* was old */` goes, or None when present already / no site"""
    for rx in (DEF, DEF2):
        for p, t in texts.items():
            if cand is not None and p not in cand:
                continue
            if not p.startswith('conker/src_eu/') or not p.endswith('.c'):
                continue
            m = re.search(rx % re.escape(new), t, re.M) if rx == DEF else def2(t, new)
            if m:
                ln = t.count('\n', 0, m.start())
                # P329: anywhere in the file (since the NM wrappers were stripped the comment can sit further up)
                if ('was ' + old) in t:
                    return 'present'
                return (p, ln)
    return None


_CMT = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:[^"\\\n]|\\.)*"', re.S)   # comments and string literals


def code_only(path, text):
    """text without comments (C / headers / asm-processor) or '#' note lines (tsv, txt, Makefile, yaml)"""
    if path.endswith(('.c', '.h', '.inc', '.cpp')):
        return _CMT.sub(' ', text)
    return re.sub(r'(^|\s)#[^\n]*', ' ', text)


_STR = re.compile(r'"(?:[^"\\\n]|\\.)*"')


def sub_line(rx, line, new, keep_strings):
    """rename on one line; for a global (keep_strings) not inside string literals (log texts such as
    port_log("... D_X %d") stay as they are, so the wasm stays byte-identical), except a literal that is exactly the
    name (an asm label: __asm__("D_X"))"""
    rep = lambda m: m.group(1) + new
    if not keep_strings or '"' not in line:
        return rx.sub(rep, line)
    out, pos = [], 0
    for m in _STR.finditer(line):
        out.append(rx.sub(rep, line[pos:m.start()]))
        s = m.group(0)
        out.append(rx.sub(rep, s) if rx.fullmatch(s[1:-1]) else s)
        pos = m.end()
    out.append(rx.sub(rep, line[pos:]))
    return ''.join(out)


def plan(rows, only):
    files = scope_files()
    texts = {p: read(p) for p in files}
    texts = {p: t for p, t in texts.items() if t is not None}
    edits = {}          # path -> new text
    report = []
    moves = []
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
        ours = (
            map_addr([new]) is not None and map_addr([new]) == map_addr([old])) or (
            # the table row was renamed already (new listed, old gone)
            map_addr([new]) is not None and map_addr([old]) is None) or (
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
                        nl = sub_line(rx, line, new, old.startswith('D_') and p.endswith(('.c', '.h')))
                        out.append(nl)
                        hits += 1
                        report.append('%s:%d: %s\n    -> %s' % (p, i, line.strip()[:150], nl.strip()[:150]))
                    else:
                        out.append(line)
                edits[p] = '\n'.join(out)
            if old in p and re.search(r'(?<![A-Za-z0-9_])' + re.escape(old) + r'(?![A-Za-z0-9_])', p):
                np_ = re.sub(r'(?<![A-Za-z0-9_])' + re.escape(old) + r'(?![A-Za-z0-9_])', new, p)
                moves.append((p, np_)); report.append('git mv %s %s' % (p, np_))
        # the table row (if any) was renamed with the other in-scope uses above
        if map_addr([old, new]) is None:
            report.append('NOTE: %s has no row in %s (NON_MATCHING-only): no table entry' % (old, PORT_TABLE))
        if hits == 0:
            report.append('%s -> %s: already applied' % (old, new))
        if old.startswith('D_'):
            # a global (data symbol): no single definition (the data comes from the ROM), so `/* was old */` goes at
            # the end of each file-scope declaration line (column 0: `extern u16 pad_held[];`, definitions)
            for p in sorted(inv.get(new, ())):
                if p not in edits or not p.endswith(('.c', '.h')):
                    continue
                out, n = [], 0
                for line in edits[p].split('\n'):
                    if (line[:1].isalpha() or line[:1] == '_') and line.rstrip()[-1:] != '\\' \
                            and word(new).search(line) and ('was ' + old) not in line:
                        s = line.rstrip()
                        c = min([i for i in (s.find('/*'), s.find('//')) if i >= 0], default=-1)
                        if c < 0:
                            line = s + ' /* was %s */' % old
                        elif s.endswith('*/') and s.startswith('/*', c) and '*/' not in s[c + 2:-2]:
                            line = s[:-2].rstrip() + '; was %s */' % old   # into the line's own trailing comment
                        else:   # a comment that goes on to the next line(s), or a // one: put it before it
                            line = s[:c].rstrip() + ' /* was %s */ ' % old + s[c:]
                        n += 1
                    out.append(line)
                if n:
                    edits[p] = '\n'.join(out)
                    report.append('%s: /* was %s */ on %d declaration line(s)' % (p, old, n))
            continue
        # `/* was old */` above the definition
        merged = dict(texts); merged.update(edits)
        site = comment_site(merged, old, new, inv.get(new, set()))
        if site is None:
            report.append('WARNING: no C definition of %s in conker/src_eu (asm-only?): add `/* was %s */` by hand if it has one'
                          % (new, old))
        elif site != 'present':
            p, ln = site
            lines = merged[p].split('\n')
            lines.insert(ln, '/* was %s */' % old)
            edits[p] = '\n'.join(lines)
            report.append('%s:%d: insert /* was %s */ above the definition of %s' % (p, ln + 1, old, new))
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
        tc = code_only(p, t)
        for old in sorted(olds & tokens(tc)):
            if word(old).search(tc):
                left.append('%s still uses %s' % (p, old))
    print('old names left in scope: %d' % len(left)); print('\n'.join(left[:20])); ok &= not left
    r = subprocess.run(['tools/eu_port/check.sh'], cwd=ROOT, env=env, capture_output=True, text=True)
    print(r.stdout.strip()[-1500:]); print('check.sh rc %d' % r.returncode); ok &= r.returncode == 0
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
