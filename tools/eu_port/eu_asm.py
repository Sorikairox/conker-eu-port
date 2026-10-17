"""Read function starts and sizes from splat/spimdisasm .s output."""
import glob
import re

GLABEL = re.compile(r"^glabel (\S+)")
INSN = re.compile(r"^\s+/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/")


def functions(pattern="asm/**/*.s"):
    """{name: (vram, size)} for every glabel'd function; size counts its instructions."""
    out = {}
    for path in glob.glob(pattern, recursive=True):
        cur, start, count = None, None, 0
        for line in open(path):
            m = GLABEL.match(line)
            if m:
                if cur is not None and start is not None:
                    out[cur] = (start, count * 4)
                cur, start, count = m.group(1), None, 0
                continue
            m = INSN.match(line)
            if m and cur is not None:
                if start is None:
                    start = int(m.group(1), 16)
                count += 1
            elif line.startswith(".section") and cur is not None:
                if start is not None:
                    out[cur] = (start, count * 4)
                cur = None
        if cur is not None and start is not None:
            out[cur] = (start, count * 4)
    return out


LABEL = re.compile(r"^\s*glabel (\S+)\n\s+/\* [0-9A-F]+ ([0-9A-F]{8}) ", re.M)


def labels(pattern="asm/**/*.s"):
    """Addresses of every glabel, including ones spimdisasm emits inside a function."""
    out = set()
    for path in glob.glob(pattern, recursive=True):
        out.update(int(m.group(2), 16) for m in LABEL.finditer(open(path).read()))
    return out
