"""P327: content keys for the incremental web build (census.py --incremental, vbe_build.py).

A TU is rebuilt when its key changes. The key hashes the compile flags, the tool scripts that produce the output, and
the CONTENTS of the source and of every header it included last time (clang -MD depfile). So an edit to a .c or to
any header it includes (port_prefix.h, functions.h, variables.h, ...) rebuilds exactly the TUs that use it, while a
touch / git checkout that leaves contents unchanged rebuilds nothing. A new #include changes the .c, so the key
changes too; a deleted header hashes as 'missing'."""
import hashlib, json, os

_memo = {}


def file_hash(path):
    h = _memo.get(path)
    if h is None:
        try:
            with open(path, 'rb') as f:
                h = hashlib.sha1(f.read()).hexdigest()
        except OSError:
            h = 'missing'
        _memo[path] = h
    return h


def parse_depfile(path):
    """make-syntax depfile (clang -MD) -> list of prerequisite paths (normalised, relative to the cwd if inside)"""
    try:
        text = open(path).read()
    except OSError:
        return None
    text = text.replace('\\\n', ' ')
    deps = []
    for line in text.splitlines():
        if ':' not in line:
            continue
        rhs = line.split(':', 1)[1]
        rhs = rhs.replace('\\ ', '\0')
        for d in rhs.split():
            d = os.path.normpath(d.replace('\0', ' '))
            if d.startswith('/src/'):  # inside the conker-emsdk container the repo is /src
                d = d[5:]
            deps.append(d)
    return sorted(set(deps))


def key(parts, files):
    h = hashlib.sha1()
    for p in parts:
        h.update(p.encode() + b'\0')
    for f in sorted(set(files)):
        h.update(f.encode() + b'=' + file_hash(f).encode() + b'\0')
    return h.hexdigest()


def load(path):
    try:
        return json.load(open(path))
    except (OSError, ValueError):
        return None


def save(path, obj):
    tmp = path + '.tmp'
    with open(tmp, 'w') as f:
        json.dump(obj, f)
    os.replace(tmp, path)


def write_if_changed(path, text):
    """keeps the mtime when the content is the same (make then sees nothing new)"""
    try:
        if open(path).read() == text:
            return False
    except OSError:
        pass
    with open(path, 'w') as f:
        f.write(text)
    return True
