#!/usr/bin/env python3
"""s109: m2c rand temps -> inline call arguments (IDO_SHAPES s106 recipe 1), plus variants.

usage: inlinerand.py draft.c outprefix [--rand f1,f2] [--keep-named]

For every `v = RAND();` statement (RAND = func_150ADA20 / func_150ADA68 by default) whose variable is read
exactly once afterwards, writes variants:
  <outprefix>_in.c     every such temp inlined at its single use (s106 recipe 1: IDO evaluates call args
                       left to right, so inline rands keep the ref's call order when they are used in order)
  <outprefix>_named.c  input unchanged except that m2c's `(u8) (v & 0xFF)` casts become `v & 0xFF`
  <outprefix>_mix<k>.c only the first k temps stay named (the ref often names the early rands and inlines
                       the last one: s109 func_150BA26C / func_150E9C9C / func_150D1714)
Also rewrites `(u8) (RAND() & 0xFF)` into `RAND() & 0xFF` (an explicit mask gives the ref's `andi`).
Screen the outputs with `m2c/tryall <func> <outprefix>_*.c`. Self-contained, no repo imports.
"""
import re, sys

def main():
    a = sys.argv[1:]
    if len(a) < 2:
        print(__doc__); sys.exit(1)
    src, pre = a[0], a[1]
    rands = ['func_150ADA20', 'func_150ADA68']
    if '--rand' in a:
        rands = a[a.index('--rand') + 1].split(',')
    text = open(src).read()
    rx = '|'.join(map(re.escape, rands))
    text = re.sub(r'\(u8\) \((\w+) & 0xFF\)', r'\1 & 0xFF', text)
    assigns = list(re.finditer(r'^([ \t]*)(\w+) = ((?:%s)\(\));[ \t]*\n' % rx, text, re.M))
    temps = []
    for m in assigns:
        v = m.group(2)
        rest = text[m.end():]
        uses = re.findall(r'\b%s\b' % re.escape(v), rest)
        if len(uses) == 1 and not re.search(r'\b%s\s*=[^=]' % re.escape(v), rest):
            temps.append(m)

    def inline(t, ms):
        for m in sorted(ms, key=lambda m: -m.start()):
            v, call = m.group(2), m.group(3)
            after = t[m.end():]
            after = re.sub(r'\b%s\b' % re.escape(v), call, after, count=1)
            t = t[:m.start()] + after
            t = re.sub(r'^[ \t]*\w+ %s;[ \t]*\n' % re.escape(v), '', t, count=1, flags=re.M)
        return t

    outs = {'named': text}
    if temps:
        # rematch on the current text for each variant (positions are from `text`)
        outs['in'] = inline(text, temps)
        for k in range(1, len(temps)):
            outs['mix%d' % k] = inline(text, temps[k:])
    for k, t in outs.items():
        open('%s_%s.c' % (pre, k), 'w').write(t)
    print('%d rand temps inlinable; wrote %s' % (len(temps), ' '.join('%s_%s.c' % (pre, k) for k in outs)))

if __name__ == '__main__':
    main()
