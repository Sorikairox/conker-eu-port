#!/usr/bin/env python3
"""Build the function / file names tables (see docs/names/README.md).

Scans src_eu/**/*.c of the port, portb and web worktrees for description
comments above func_XXXXXXXX definitions, mines docs/port/sessions/P*.md
tables, and writes docs/names/functions.tsv and docs/names/files.tsv.
Python 3 stdlib only.  Usage: python3 tools/eu_port/names_table.py
"""
import os, re, sys, glob, collections

HOME = os.path.expanduser("~")
OUT = os.path.join(HOME, "conker", "docs", "names")
TREES = [("port", HOME + "/conker-wt/port"), ("portb", HOME + "/conker-wt/portb"),
         ("web", HOME + "/conker-wt/web")]
MAXDESC = 200

DEF_RE = re.compile(r'^[A-Za-z_][\w\s\*]*?\b(func_([0-9A-F]{8}))\s*\(')
NAME_RE = re.compile(r'^([a-z][a-z0-9]*(?:_[a-z0-9]+)*)\s*:\s+(\S.*)$')
NAME_STOP = {"fakematch", "rodata_inject", "late_align8", "note", "todo", "fixme", "hack", "see", "warning", "caveat", "xxx", "nb",
             "why", "args", "arg", "returns", "return", "example", "e", "eg", "ok", "http", "https"}
STOP = set("""the a an of to for and in on with by from is it its this that when then per into at as or
be are was were not no if so but via using used use each all any also only more than their there
which what while after before about over under up down out off one two""".split())
GENERIC = STOP | set("function functions func handler handlers call calls code stub helper value values data "
                     "unused unknown state step current new set get".split())


def clean(s):
    s = s.replace("`", "").replace("**", "")
    return re.sub(r'\s+', ' ', s).strip()


def tidy(d):
    d = re.sub(r'^(func_[0-9A-Fa-f]{8}\s*(\([^)]*\))?\s*[:,-]?\s*)', '', d)
    d = re.sub(r'^P\d+\s*[:,]\s*', '', d)
    if len(re.findall(r'[A-Za-z]{2,}', d)) < 2 or d.startswith("???"):
        return ""
    return d


def short(s):
    s = clean(s)
    return s if len(s) <= MAXDESC else s[:MAXDESC - 3].rstrip() + "..."


def strip_comment(lines):
    out = []
    for l in lines:
        l = l.strip()
        l = re.sub(r'^/\*+', '', l)
        l = re.sub(r'\*+/$', '', l)
        l = re.sub(r'^//+', '', l)
        l = re.sub(r'^\*+', '', l)
        out.append(l.strip())
    return clean(" ".join(x for x in out if x))


def comment_above(lines, i):
    """Comment block immediately above line index i (0-based), or ''."""
    j = i - 1
    if j < 0:
        return "", 0
    t = lines[j].strip()
    block = []
    if t.startswith("//"):
        while j >= 0 and lines[j].strip().startswith("//"):
            block.append(lines[j]); j -= 1
        block.reverse()
        return strip_comment(block), j + 2
    if t.endswith("*/"):
        while j >= 0:
            block.append(lines[j])
            if "/*" in lines[j]:
                break
            j -= 1
        else:
            return "", 0
        block.reverse()
        return strip_comment(block), j + 1
    return "", 0


def is_definition(lines, i):
    """lines[i] starts a func_ head; true if a body follows (not a prototype)."""
    for k in range(i, min(i + 8, len(lines))):
        s = lines[k]
        if ";" in s:
            return False
        if s.rstrip().endswith("{") or s.strip() == "{":
            return True
        if "{" in s:
            return True
    return False


def split_name(desc):
    m = NAME_RE.match(desc)
    if m and m.group(1) not in NAME_STOP and "_" in m.group(1):
        return m.group(1), tidy(m.group(2))
    return "", tidy(desc)


def scan_sources(tree, root):
    res = []
    base = os.path.join(root, "conker", "src_eu")
    for dp, _, fns in os.walk(base):
        for fn in sorted(fns):
            if not fn.endswith(".c"):
                continue
            path = os.path.join(dp, fn)
            rel = os.path.relpath(path, base)
            try:
                lines = open(path, errors="replace").read().split("\n")
            except OSError:
                continue
            for i, l in enumerate(lines):
                m = DEF_RE.match(l)
                if not m or not is_definition(lines, i):
                    continue
                desc, cl = comment_above(lines, i)
                name, d = split_name(desc) if desc else ("", "")
                res.append(dict(addr=m.group(2), cur=m.group(1), file=fn, rel=rel, tree=tree,
                                name=name, desc=d, src="%s:%s:%d" % (tree, rel, cl or i + 1)))
    return res


ROW_FUNC = re.compile(r'^`?func_([0-9A-F]{8})`?\s*(?:\(([^)]*)\))?\s*$')
FILE_RE = re.compile(r'^`?[\w./-]+\.c`?$')


def doc_desc(text):
    t = clean(text)
    if not t or t.startswith("(") or re.match(r'^(EQUIV|NON_MATCHING|OK|n/a|-+)\b', t):
        return ""
    t = re.split(r'\.\s|;\s', t)[0]
    t = tidy(t.rstrip("."))
    return short(t) if len(t) >= 6 else ""


def scan_docs(tree, root):
    res = []
    for path in sorted(glob.glob(os.path.join(root, "docs", "port", "sessions", "P*.md"))):
        try:
            lines = open(path, errors="replace").read().split("\n")
        except OSError:
            continue
        for n, l in enumerate(lines, 1):
            if not l.startswith("|"):
                continue
            cells = [c.strip() for c in l.strip().strip("|").split("|")]
            if len(cells) < 2:
                continue
            m = ROW_FUNC.match(cells[0])
            if not m:
                continue
            addr, par = m.group(1), m.group(2)
            rest = cells[1:]
            f = ""
            if par and re.match(r'^[\w]+(\.c)?$', par.strip()):
                f = par.strip()
            if rest and FILE_RE.match(rest[0]):
                f = rest[0].strip("`"); rest = rest[1:]
            d = ""
            for c in rest[:2]:
                d = doc_desc(c)
                if d:
                    break
            if d:
                res.append(dict(addr=addr, cur="func_" + addr, file=f, rel="", tree=tree, name="",
                                desc=d, src="doc:%s:%s:%d" % (tree, os.path.relpath(path, root), n)))
    return res


def words(desc, limit):
    clause = re.split(r'[:;,(]| - | -> |\. ', desc)[0]
    for cand in (clause, desc):
        toks = []
        for w in re.findall(r"[A-Za-z][A-Za-z']*", cand.replace("-", " ")):
            w = w.lower()
            w = re.sub(r"'s$", "", w).replace("'", "")
            if w in STOP or len(w) < 2 or w.startswith("func"):
                continue
            toks.append(w)
        if len(toks) >= 2 or cand is desc:
            return toks[:limit]
    return []


def main():
    entries = collections.defaultdict(list)   # addr -> list of entries
    allfuncs = collections.defaultdict(list)
    for tree, root in TREES:
        if not os.path.isdir(root):
            print("missing", root, file=sys.stderr); continue
        for e in scan_sources(tree, root):
            allfuncs[e["addr"]].append(e)
            if e["desc"]:
                entries[e["addr"]].append(e)
        for e in scan_docs(tree, root):
            entries[e["addr"]].append(e)
    prio = {n: i for i, (n, _) in enumerate(TREES)}
    rows = []
    for addr in sorted(set(allfuncs) | set(entries)):
        defs = allfuncs.get(addr, [])
        defs.sort(key=lambda e: prio[e["tree"]])
        com = [e for e in entries.get(addr, []) if not e["src"].startswith("doc:")]
        doc = [e for e in entries.get(addr, []) if e["src"].startswith("doc:")]
        com.sort(key=lambda e: prio[e["tree"]])
        # named comments beat unnamed ones
        named = [e for e in com if e["name"]]
        best = (named or com or doc or [None])[0]
        conflicts = []
        if best:
            others = {(e["name"], e["desc"]) for e in com if (e["name"], e["desc"]) != (best["name"], best["desc"])}
            if others:
                conflicts.append("desc_differs:" + ",".join(sorted({e["tree"] for e in com
                                 if (e["name"], e["desc"]) != (best["name"], best["desc"])})))
            if best in com and doc and doc[0]["desc"].lower()[:30] != best["desc"].lower()[:30]:
                conflicts.append("doc_differs")
        files = sorted({e["file"] for e in defs})
        if len(files) > 1:
            conflicts.append("file_differs:" + "|".join(files))
        if len(defs) and len({e["tree"] for e in defs}) < 3:
            conflicts.append("missing_in:" + ",".join(t for t, _ in TREES if t not in {e["tree"] for e in defs}))
        file = defs[0]["file"] if defs else (best["file"] if best else "")
        rows.append(dict(addr=addr, cur="func_" + addr, file=file, name=best["name"] if best else "",
                         desc=short(best["desc"]) if best else "",
                         src=best["src"] if best else "", conflict=";".join(conflicts),
                         kind=("comment" if best and best in com else "doc" if best else "none")))
    # candidate names
    used = {r["name"] for r in rows if r["name"]}
    dup = collections.Counter(r["name"] for r in rows if r["name"])
    for r in rows:
        r["source_kind"] = "none"
        if r["name"]:
            r["source_kind"] = "comment"
            if dup[r["name"]] > 1:
                r["conflict"] = (r["conflict"] + ";" if r["conflict"] else "") + "dup_name"
        elif r["desc"]:
            w = words(r["desc"], 4)
            if len(w) >= 2:
                nm = "_".join(w)
                base, k = nm, 2
                while nm in used:
                    nm = "%s_%d" % (base, k); k += 1
                used.add(nm)
                r["name"] = nm
                r["source_kind"] = "candidate"
    os.makedirs(OUT, exist_ok=True)
    with open(os.path.join(OUT, "functions.tsv"), "w") as f:
        f.write("address\tcurrent_name\tfile\tproposed_name\tname_source\tdescription\tsource\tconflicts\n")
        for r in rows:
            f.write("\t".join([r["addr"], r["cur"], r["file"], r["name"], r["source_kind"],
                               r["desc"].replace("\t", " "), r["src"], r["conflict"]]) + "\n")
    # files table
    byfile = collections.OrderedDict()
    for r in rows:
        if r["file"]:
            byfile.setdefault(r["file"], []).append(r)
    with open(os.path.join(OUT, "files.tsv"), "w") as f:
        f.write("file\tcandidate_name\tconfidence\tfunctions\tdescribed\tevidence\n")
        for fn in sorted(byfile):
            rs = byfile[fn]
            desc = [r for r in rs if r["desc"]]
            cnt, first = collections.Counter(), {}
            for r in desc:
                seen = set()
                for w in words(r["desc"], 6):
                    if w in GENERIC or w in seen:
                        continue
                    seen.add(w); cnt[w] += 1; first.setdefault(w, len(first))
            top = sorted(cnt, key=lambda w: (-cnt[w], first[w]))[:2]
            top = sorted(top, key=lambda w: first[w])
            name = "_".join(top)
            if not top:
                conf = "none"
            elif len(desc) >= 3 and cnt[top[0]] >= 2 and cnt[top[0]] / len(desc) >= 0.3:
                conf = "ok"
            else:
                conf = "low"
            ev = ", ".join("%s=%d" % (w, cnt[w]) for w in sorted(cnt, key=lambda w: -cnt[w])[:5])
            f.write("\t".join([fn, name, conf, str(len(rs)), str(len(desc)), ev]) + "\n")
    c = collections.Counter(r["source_kind"] for r in rows)
    print("functions:", len(rows), dict(c), "files:", len(byfile))


if __name__ == "__main__":
    main()
