#!/usr/bin/env python3
"""Automatic declaration fixing for clone / near-clone drafts (session 29).
usage (library):  declfix.fix(body, func, sibling_stem, target_stem) -> (new_body, [notes])
usage (CLI):      declfix.py FUNC SIBLING_STEM TARGET_STEM < draft.c > fixed.c   (debug)
Rules, for every identifier the draft uses that the target file does not see:
  * type / struct / extern / macro / prototype chunks are pulled from the sibling's file, then
    include/{functions,variables,structs}.h, then any other src_eu file (variables with an initializer become `extern`);
  * a callee defined *later* in the target file, or in the sibling's file, gets a forward prototype from its definition;
  * the draft's own definition is reconciled with a prototype in a header (pointer params keep the header type
    plus a local alias with the draft's type; scalar params take the header type);
  * the draft's own function called implicitly by an earlier C function of the target file gets a `//HOIST ` prototype
    (screen.py / apply.py move `//HOIST ` lines to the top of the file, after the last #include);
  * an #include the sibling's file has and the target lacks is hoisted when the draft uses a name from it (stdarg.h).
"""
import re, os, glob, sys
import sys as _gsys
def _conker_guard():
    # refuse to run on a checkout other than CONKER_ROOT (e.g. a worktree shell without the wt.sh env)
    import os as _o, subprocess as _s
    if _o.path.exists("/.dockerenv"):
        return  # inside a build container: paths are /conker, not the host checkout
    try:
        top = _s.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()
    except Exception:
        return
    root = _o.path.realpath(_o.path.expanduser(_o.environ.get("CONKER_ROOT", "~/conker")))
    if top and _o.path.realpath(top) != root:
        _gsys.stderr.write("refusing: cwd repo %s != CONKER_ROOT %s (eval the wt.sh env)\n" % (top, root))
        _gsys.exit(3)
_conker_guard()
R = os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker')
INCS = [R, R + '/include', R + '/include/2.0L', R + '/include/2.0L/PR', R + '/include/libc',
        R + '/src/libultra/os', R + '/src/libultra/audio', R + '/src/libultra/io']
_cache = {}

def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), t, flags=re.S)
    return re.sub(r'//[^\n]*', '', t)

def chunks(text):
    """top-level chunks: dict(kind=def|decl|type|define|pragma|include, name(s), text)"""
    t = strip_comments(text); out = []; buf = []; depth = 0; par = 0; i = 0; n = len(t)
    at_bol = True
    def flush(kind):
        s = ''.join(buf).strip(); buf.clear()
        if s: out.append(classify(s, kind))
    while i < n:
        c = t[i]
        if at_bol and depth == 0 and not ''.join(buf).strip() and c == '#' or (c == '#' and depth == 0 and not ''.join(buf).strip()):
            j = i
            while True:
                e = t.find('\n', j)
                if e < 0: e = n; break
                if t[e - 1] == '\\': j = e + 1; continue
                break
            line = t[i:e]; i = e
            out.append(classify_pp(line)); at_bol = True; continue
        if c == '(' : par += 1
        elif c == ')': par -= 1
        if c == '{':
            if depth == 0:
                pre = ''.join(buf).rstrip()
                isfun = pre.endswith(')') and not re.search(r'=\s*$', pre) and '=' not in pre.split('(')[0]
                if isfun:
                    # function body: skip to the matching brace
                    d = 0; j = i
                    while j < n:
                        if t[j] == '{': d += 1
                        elif t[j] == '}':
                            d -= 1
                            if d == 0: break
                        j += 1
                    fb = t[i:j + 1]; buf.append(' {}'); i = j + 1; flush('def'); out[-1]['body'] = fb; at_bol = True; continue
            depth += 1
        elif c == '}': depth -= 1
        buf.append(c)
        if c == ';' and depth == 0 and par == 0: flush('decl')
        at_bol = (c == '\n')
        i += 1
    flush('decl')
    return out

def classify_pp(line):
    m = re.match(r'#\s*include\s*([<"])([^>"]+)[>"]', line)
    if m: return dict(kind='include', names=[], text=line, inc=m.group(2), sys=(m.group(1) == '<'))
    m = re.match(r'#\s*pragma\s+GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', line)
    if m: return dict(kind='pragma', names=[m.group(1)], text=line)
    m = re.match(r'#\s*define\s+(\w+)', line)
    if m: return dict(kind='define', names=[m.group(1)], text=line)
    return dict(kind='pp', names=[], text=line)

def classify(s, kind):
    names = []; k = kind
    if kind == 'def':
        head = s[:s.rfind('{}')]
        m = re.search(r'(\w+)\s*\(', head)
        names = [m.group(1)] if m else []
    else:
        body = s
        if s.startswith('typedef'):
            k = 'type'
            for m in re.finditer(r'\b(?:struct|union|enum)\s+(\w+)', s): names.append(m.group(1))
            tail = re.sub(r'\{.*\}', '{}', s, flags=re.S)
            m = re.search(r'\(\s*\*\s*(\w+)\s*\)', tail) or re.search(r'(\w+)\s*(?:\[[^\]]*\])*\s*;$', tail)
            if m: names.append(m.group(1))
        elif re.match(r'(?:struct|union|enum)\s+\w+\s*\{', s):
            k = 'type'; names = [re.match(r'(?:struct|union|enum)\s+(\w+)', s).group(1)]
        else:
            h = re.sub(r'\{.*\}', '{}', s, flags=re.S)
            h = h.split('=')[0]
            m = re.search(r'\(\s*\*\s*(\w+)', h)
            if m: names = [m.group(1)]
            elif '(' in h:
                m = re.search(r'(\w+)\s*\(', h); names = [m.group(1)] if m else []
            else:
                h = re.sub(r'\[[^\]]*\]', '', h).strip().rstrip(';')
                m = re.search(r'(\w+)\s*$', h); names = [m.group(1)] if m else []
    return dict(kind=k, names=names, text=s)

def load(path):
    path = os.path.realpath(path)
    if path not in _cache:
        try: txt = open(path).read()
        except OSError: txt = ''
        _cache[path] = chunks(txt)
    return _cache[path]

def resolve_inc(inc, here):
    for d in [os.path.dirname(here)] + INCS:
        p = os.path.join(d, inc)
        if os.path.exists(p): return os.path.realpath(p)
    return None

def closure(path, seen=None):
    """files included (transitively) by path, incl. itself"""
    seen = set() if seen is None else seen
    path = os.path.realpath(path)
    if path in seen: return seen
    seen.add(path)
    for ch in load(path):
        if ch['kind'] == 'include':
            p = resolve_inc(ch['inc'], path)
            if p: closure(p, seen)
    return seen

def src_path(stem):
    for p in glob.glob(R + '/src_eu/**/%s.c' % stem, recursive=True): return p
    return None

_all = {}
def global_index():
    if not _all:
        files = [R + '/include/' + h for h in ('functions.h', 'variables.h', 'structs.h')]
        files += glob.glob(R + '/src_eu/**/*.c', recursive=True)
        for f in files:
            for ch in load(f):
                for nm in ch['names']: _all.setdefault(nm, []).append((f, ch))
    return _all

def sig_of_def(ch):
    head = ch['text'][:ch['text'].rfind('{}')].strip()
    return head

def proto_of_def(ch):
    h = sig_of_def(ch)
    if re.search(r'\)\s*\w+\s*;|\)\s*\w[^)]*;', h): return None   # K&R
    m = re.search(r'\(([^()]*)\)\s*$', h)
    if not m: return None
    ps = m.group(1).strip()
    if ps and ps != 'void' and not all(re.search(r'\w\s*\**\s*\w+\s*(\[\])?$|\.\.\.$|^\w+$', p.strip()) and
            re.search(r'[\w\*\]]\s+[\*\w]|\*', p.strip()) for p in ps.split(',')): return None   # K&R names only
    h = re.sub(r'^(?:static|extern)\s+', '', h)
    # drop parameter names:  `u8 *arg0` -> `u8 *`
    def noname(p):
        p = p.strip()
        if p in ('void', '...'): return p
        q = re.sub(r'\b(\w+)\s*(\[[^\]]*\])?\s*$', lambda mm: '' if re.search(r'[\w\*]', p[:mm.start()]) else mm.group(0), p)
        return (q.strip() + (' *' if '[' in p and mm_arr(p) else '')).strip() if False else p
    return h + ';'

def mm_arr(p): return False

def split_params(s):
    out = []; d = 0; cur = ''
    for c in s:
        if c in '([': d += 1
        elif c in ')]': d -= 1
        if c == ',' and d == 0: out.append(cur.strip()); cur = ''
        else: cur += c
    if cur.strip(): out.append(cur.strip())
    return out

def ptype(p):
    """(type text, name) of a parameter declaration"""
    m = re.match(r'^(.*?)(\w+)\s*(\[[^\]]*\])?$', p.strip(), re.S)
    if not m or not m.group(1).strip(): return p.strip(), ''
    return m.group(1).strip() + (' *' if m.group(3) else ''), m.group(2)

def norm(t): return re.sub(r'\s+', '', t)

CAND = re.compile(r'^(D_|func_|jtbl_|struct_|[A-Z_])')

def fix(body, a, sib_stem, tgt_stem):
    notes = []
    tgt = src_path(tgt_stem); sib = src_path(sib_stem)
    if not tgt: return body, ['no-target']
    tch = load(tgt)
    pos = next((i for i, ch in enumerate(tch) if ch['kind'] == 'pragma' and a in ch['names']), None)
    if pos is None: return body, ['no-pragma']
    vis_files = closure(tgt)
    vis = set()
    for f in vis_files:
        for ch in load(f):
            if f == os.path.realpath(tgt): continue
            vis.update(ch['names'])
    before = tch[:pos]; after = tch[pos + 1:]
    vis_before = set(nm for ch in before for nm in ch['names'] if ch['kind'] != 'pragma')
    visible = vis | vis_before
    deflater = {}   # name -> chunk, defs later in target
    for ch in after:
        if ch['kind'] == 'def':
            for nm in ch['names']: deflater.setdefault(nm, ch)
    sibch = load(sib) if sib else []
    sib_defs = {nm: ch for ch in sibch if ch['kind'] == 'def' for nm in ch['names']}
    gi = global_index()
    hoist = []; pre = []; drop = []
    # -- own definition vs header prototype / earlier implicit uses
    m = re.search(r'(?:^|\n)((?:[A-Za-z_]\w*[ \t\*]+)+?)%s\s*\(([^()]*)\)\s*\{' % re.escape(a), body)
    own_proto = None
    if m:
        ret, params = m.group(1).strip(), m.group(2).strip()
        hdr = [ch for f in vis_files if f != os.path.realpath(tgt) for ch in load(f)
               if ch['kind'] == 'decl' and a in ch['names'] and '(' in ch['text']]
        hdr += [ch for ch in tch if ch['kind'] == 'decl' and a in ch['names'] and '(' in ch['text']]
        for ch in tch:   # `extern s32 func_X;` (address taken) in the target file: drop it, the definition replaces it
            if ch['kind'] == 'decl' and a in ch['names'] and '(' not in ch['text']:
                drop.append(ch['text'].strip()); notes.append('drop-extern')
        loc = [ch for ch in tch if ch['kind'] == 'decl' and a in ch['names'] and '(' in ch['text']]
        if loc and not [ch for f in vis_files if f != os.path.realpath(tgt) for ch in load(f)
                        if ch['kind'] == 'decl' and a in ch['names'] and '(' in ch['text']]:
            # prototype only in the target file itself: the draft replaces it
            lp = re.search(r'\(((?:[^()]|\([^()]*\))*)\)\s*;$', loc[0]['text'])
            lret = re.match(r'^(?:extern\s+)?(.*?)\b%s\s*\(' % re.escape(a), loc[0]['text'], re.S)
            if norm(lp.group(1) if lp else '') != norm(params) or (lret and norm(lret.group(1)) != norm(ret)):
                drop.append(loc[0]['text'].strip()); hoist.append('%s %s(%s);' % (ret, a, params)); notes.append('replace-local-proto')
            hdr = []
        if hdr:
            hp = re.search(r'\(((?:[^()]|\([^()]*\))*)\)\s*;$', hdr[0]['text'])
            hps = split_params(hp.group(1)) if hp else None
            hret = re.match(r'^(?:extern\s+)?(.*?)\b%s\s*\(' % re.escape(a), hdr[0]['text'], re.S)
            if hret and norm(hret.group(1)) and norm(hret.group(1)) != norm(ret):
                body = body[:m.start(1)] + (' ' if body[m.start(1)] == ' ' else '') + hret.group(1).strip() + ' ' + body[m.end(1):].lstrip()
                notes.append('ret-from-proto')
                m = re.search(r'(?:^|\n)((?:[A-Za-z_]\w*[ \t\*]+)+?)%s\s*\(([^()]*)\)\s*\{' % re.escape(a), body)
            dps = split_params(params)
            if hps and hps != ['void'] and '...' not in params:
                if dps == ['void']: dps = []
                dps = dps[:len(hps)] + ['%s arg%d' % (ptype(hps[i])[0], i) for i in range(len(dps), len(hps))]
                newp = []; alias = []; changed = len(split_params(params)) != len(hps)
                for hpar, dpar in zip(hps, dps):
                    ht, hn = ptype(hpar); dt, dn = ptype(dpar)
                    if norm(ht) == norm(dt): newp.append(dpar); continue
                    changed = True
                    if '*' in dt:
                        newp.append('%s %s_' % (ht, dn)); alias.append('%s %s = (%s)%s_;' % (dt, dn, dt, dn))
                    else:
                        newp.append('%s %s' % (ht, dn))
                if changed:
                    body = body[:m.start(2)] + ', '.join(newp) + body[m.end(2):]
                    if alias:
                        k = body.index('{', body.index(', '.join(newp))) + 1
                        body = body[:k] + '\n    ' + '\n    '.join(alias) + body[k:]
                    notes.append('sig-from-proto')
        else:
            used_before = any(ch['kind'] == 'def' and _calls(tgt, ch, a) for ch in before)
            if used_before:
                hoist.append('%s %s(%s);' % (ret, a, params))
                notes.append('hoist-proto')
    # -- identifiers used by the draft
    code = strip_comments(body)
    code = re.sub(r'"(?:\\.|[^"\\])*"', '""', code)
    toks = [(mm.group(1), mm.start(), mm.end()) for mm in re.finditer(r'\b([A-Za-z_]\w*)\b', code)]
    used = []
    called = set()
    for nm, s, e in toks:
        if code[max(0, s - 2):s].strip() in ('.',) or code[max(0, s - 2):s] == '->': continue
        if code[s - 1:s] == '.': continue
        if nm not in used: used.append(nm)
        if re.match(r'\s*\(', code[e:]): called.add(nm)
    defined_in_draft = set(re.findall(r'(?:^|\n)[\w \t\*]+?\b(\w+)\s*\([^()]*\)\s*\{', body))
    added = set(); sibpre = []
    def add_name(nm, depth=0):
        if nm in added or nm in visible or nm == a or depth > 6: return
        # prefer: callee defined later in target / sibling file
        if nm in called and nm in deflater:
            p = proto_of_def(deflater[nm])
            if p: pre.append(p); added.add(nm); notes.append('later-proto:' + nm); return
        cands = gi.get(nm, [])
        order = sorted(cands, key=lambda fc: (0 if sib and os.path.realpath(fc[0]) == os.path.realpath(sib) else 1,
                                              0 if fc[0].endswith('.h') else 1))
        for f, ch in order:
            if os.path.realpath(f) == os.path.realpath(tgt): continue
            if ch['kind'] == 'def':
                if nm in called and os.path.realpath(f) == os.path.realpath(sib or ''):
                    p = proto_of_def(ch)
                    if p: pre.append(p); added.add(nm); notes.append('sib-def-proto:' + nm); return
                continue
            if ch['kind'] == 'pragma': continue
            txt = ch['text']
            if ch['kind'] == 'decl' and not re.match(r'(extern|static|typedef)\b', txt) and '(' not in txt.split('=')[0]:
                pass
            if ch['kind'] == 'decl' and '=' in txt and '(' not in txt.split('=')[0]:   # defined variable -> extern
                h = re.sub(r'^(static|const)\s+', '', txt.split('=')[0].strip())
                if not h.startswith('extern'): h = 'extern ' + h
                txt = h + ';'
            elif ch['kind'] == 'decl' and txt.startswith('static'):
                txt = txt.replace('static ', 'extern ', 1) if '(' not in txt else txt.replace('static ', '', 1)
            # dependencies of the chunk first
            for mm in re.finditer(r'\b([A-Za-z_]\w*)\b', strip_comments(txt)):
                dn = mm.group(1)
                if dn != nm and CAND.match(dn) and dn not in ch['names']: add_name(dn, depth + 1)
            pre.append(txt if txt.rstrip().endswith((';', '}')) or ch['kind'] == 'define' else txt + ';')
            added.add(nm); notes.append('pull:' + nm); return
    for nm in used:
        if nm in defined_in_draft: continue
        if CAND.match(nm) or nm in called: add_name(nm)
    # -- include differences
    tinc = set(os.path.basename(p) for p in vis_files)
    for ch in sibch:
        if ch['kind'] == 'include' and os.path.basename(ch['inc']) not in tinc and ch['inc'] not in ('functions.h', 'variables.h', 'structs.h'):
            p = resolve_inc(ch['inc'], sib)
            if p:
                names = set(nm for f in closure(p) for c2 in load(f) for nm in c2['names'])
                if any(u in names and u not in visible for u in used if u not in added and not CAND.match(u)):
                    hoist.append(ch['text'].strip()); notes.append('include:' + ch['inc'])
            elif ch['inc'] == 'stdarg.h' and any(u in ('va_list', 'va_start', 'va_end', 'va_arg') for u in used):
                hoist.append(ch['text'].strip()); notes.append('include:stdarg.h')
    # -- call arity: calls to prototyped callees get the prototype's argument count (pad with 0 / truncate)
    def arity(nm):
        for f, ch in gi.get(nm, []):
            if ch['kind'] == 'decl' and '(' in ch['text'] and not ch['text'].startswith('typedef') and (f in vis_files or f.endswith('.h') or True):
                hp = re.search(r'\(((?:[^()]|\([^()]*\))*)\)\s*;$', ch['text'])
                if not hp or '...' in hp.group(1): return None
                ps = split_params(hp.group(1))
                return 0 if ps == ['void'] else len(ps)
        return None
    def fixcalls(b):
        out = []; i = 0
        for mm in re.finditer(r'\b(func_\w+)\s*\(', b):
            if mm.start() < i: continue
            nm = mm.group(1)
            if nm == a: continue
            n = arity(nm)
            if n is None: continue
            j = mm.end(); d = 1; args = []; cur = ''
            while j < len(b) and d:
                c = b[j]
                if c in '([': d += 1
                elif c in ')]': d -= 1
                if d == 0: break
                if c == ',' and d == 1: args.append(cur.strip()); cur = ''
                else: cur += c
                j += 1
            if cur.strip(): args.append(cur.strip())
            if len(args) != n:
                new = args[:n] + ['0'] * (n - len(args))
                out.append((mm.end(), j, ', '.join(new))); notes.append('arity:%s %d->%d' % (nm, len(args), n))
        for st, en, txt in reversed(out): b = b[:st] + txt + b[en:]
        return b
    body = fixcalls(body)
    # -- assemble: keep a leading NEAR comment line first
    first = ''
    cm = re.match(r'(/\*.*?\*/\n)', body, re.S)
    if cm: first, body = cm.group(1), body[cm.end():]
    out = first + ''.join('//HOIST %s\n' % h for h in hoist) + ''.join('//DROP %s\n' % h for h in drop)
    # dedupe pre lines already present in body
    for p in pre:
        if p.strip() not in body: out += p.rstrip() + '\n'
    return out + body, notes

def _calls(tgt, ch, a):
    return re.search(r'\b%s\s*\(' % re.escape(a), ch.get('body', '')) is not None

if __name__ == '__main__':
    f, sib, tgt = sys.argv[1:4]
    nb, notes = fix(sys.stdin.read(), f, sib, tgt)
    sys.stdout.write(nb); sys.stderr.write(' '.join(notes) + '\n')
