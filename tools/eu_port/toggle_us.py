#!/usr/bin/env python3
"""Swap a '#if 0 // US version; EU code differs' block in/out.

    toggle_us.py on  <file.c> <func|all>   -> replace proto+GLOBAL_ASM+#if0 block by the C body
    toggle_us.py off <file.c> <func>       -> (needs a backup) restore from <file.c>.orig

The original is in git (git show HEAD:<file>).
"""
import re
import shutil
import sys
import os

MARK = "#if 0 // US version; EU code differs"


def find_blocks(lines):
    blocks = []
    i = 0
    while i < len(lines):
        if lines[i].strip() == MARK:
            # pragma on previous line, prototype on the one before
            assert "GLOBAL_ASM" in lines[i - 1], (i, lines[i - 1])
            m = re.search(r"/([A-Za-z0-9_]+)\.s", lines[i - 1])
            name = m.group(1)
            start = i - 1
            if i >= 2 and lines[i - 2].rstrip().endswith(";") and name in lines[i - 2]:
                start = i - 2
            depth = 0
            j = i
            while True:
                s = lines[j].strip()
                if s.startswith("#if"):
                    depth += 1
                elif s.startswith("#endif"):
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            blocks.append((name, start, i, j))
            i = j
        i += 1
    return blocks


def main():
    mode, path = sys.argv[1:3]
    func = sys.argv[3] if len(sys.argv) > 3 else "all"
    if mode == "on":
        lines = open(path).read().split("\n")
        blocks = find_blocks(lines)
        for name, start, ifl, endl in reversed(blocks):
            if func != "all" and name != func:
                continue
            lines[start:endl + 1] = lines[ifl + 1:endl]
            print("enabled", name)
        open(path, "w").write("\n".join(lines))
    elif mode == "list":
        lines = open(path).read().split("\n")
        for b in find_blocks(lines):
            print(b[0])


if __name__ == "__main__":
    main()
